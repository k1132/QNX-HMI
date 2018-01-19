#include "qnxcar/DatabaseManager.h"
#include "qnxcar/Hvac.h"
#include "qnxcar/LampStatus.h"
#include "qnxcar/Geolocation.h"
#include "qnxcar/SmartDevice.h"
#include "qnxcar/ThemeControl.h"
#include "qnxcar/SeatControl.h"
#include "qnxcar/MusicControl.h"
#include "qnxcar/DoorControl.h"
#include "qnxcar/AppStatus.h"
#include "qnxcar/CameraControl.h"
#include "qnxcar/ProfileManager.h"
#include "qnxcar/ProfileModel.h"
#include "qnxcar/Radio.h"
#include "qnxcar/Sensors.h"
#include "qnxcar/Settings.h"
#include "qnxcar/Theme.h"
#include "qnxcar/User.h"
#include "services/AudioControl.h"
#include "services/Bluetooth.h"
#include "services/Wifi.h"
#include "services/Hotspot.h"
#include "services/Phone.h"
#include "services/AudioPlayer.h"
#include "services/VideoPlayer.h"
#include "services/HmiNotificationManager.h"
#include "qnxcarui/KeyboardAutoCloser.h"
#include "qnxcarui/Palette.h"
#include "qnxcarui/PaletteManager.h"
#include "qnxcarui/Fonts.h"
#include "qnxcarui/ResolutionManager.h"
#include "qnxcarui/ThemeManager.h"
#include "qnxcarui/qtresourceinit.h"
#include "util/ModelMonitor.h"
#include "util/StandardDirs.h"
#include "AppLauncherServer.h"
#include "ApplicationManager.h"
#include "CommunicationsModule.h"
#include "Core.h"
#include "ExternalApplication.h"
#include "ExternalWindow.h"
#include "KeyboardProcess.h"
#include "ModuleManager.h"
#include "ProfileSettingsManager.h"
#include "RendererControl.h"
#include "ScreenManager.h"
#include "Status.h"
#include "Util.h"
#include "VoiceInput.h"
#include "WindowManager.h"
#include "Layout.h"
#include "MediaPlayerModule.h"
#include "SmartDeviceWorkflow.h"
#include <QTextCodec>

#ifdef Q_OS_QNX
#include <screen/screen.h>
#endif

#include <QSocketNotifier>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

#include <QDebug>
#include <QFont>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QRect>
#include <QStringListModel>
#include <QThread>
#include <QDateTime>

#include <qqml.h>

#include <iostream>

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QFile>
#include <QString>
#include <QDebug>

#ifndef NO_APP_SETTINGS
/* setting app includes **/
//#include "networkinfoinitthread.h"
#include <QFontDatabase>
#include <QDir>
#include "system/SystemInfo.h"
#include "system/NetworkInfo.h"
#include "services/BluetoothDevicesModel.h"
#include "BtWifi_SettingsModule.h"
#include "BtWifi_SettingsWorkflow.h"
#endif

int sigFd[2];

static void signalHandler(int)
{
    char a = 1;
    ::write(sigFd[0], &a, sizeof(a));
}

static int setup_unix_signal_handlers()
{
    struct sigaction sa;

    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGHUP, &sa, 0) > 0) {
        return 1;
    }

    if (sigaction(SIGTERM, &sa, 0) > 0) {
        return 2;
    }

    return 0;
}

class QuickViewStateHandler : public QObject
{
    Q_OBJECT
public:
    explicit QuickViewStateHandler(QQuickView *hmiView, QQuickView *speechView, QObject *parent = 0): QObject(parent), m_hmiView(hmiView), m_speechView(speechView), m_frameSwappedHandled(false) {}

public Q_SLOTS:
    void frameSwapped();

    void handleWindowGroupPosted(const QString &windowGroup, Q_PID pid);

private:
    QQuickView *m_hmiView;
    QQuickView *m_speechView;
    bool m_frameSwappedHandled;
};

// For notifying the navigation and cameraOverlay that the gui is drawn,
// so that the navigation window can be shown underneath
// the GUI
void QuickViewStateHandler::frameSwapped()
{
    if (m_frameSwappedHandled)
        return;
    m_frameSwappedHandled = true;

    // Quickly disconnect from it again, so that we dont disturb too much
    m_speechView->disconnect(this);

#ifdef Q_OS_QNX
    /*
     * This is workaround for QCARTWO-5474, this kind of logic should be internal to ApplicationManager,
     * but currently we have no ability to start ExternalApplication via ApplicationManager
     * https://jira.bbqnx.net/browse/QCARTWO-5767 created to improve ApplicationManager
    */
    Core::self()->applicationManager()->setExternalApplicaionLaunching(true);
#endif
}

void QuickViewStateHandler::handleWindowGroupPosted(const QString &windowGroup, Q_PID pid)
{
#ifdef Q_OS_QNX
    screen_window_t hmiWinHandle = (screen_window_t)(m_hmiView->winId());
    QByteArray hmiName(256, 0);
    int rc = screen_get_window_property_cv(hmiWinHandle, SCREEN_PROPERTY_GROUP, hmiName.size(), hmiName.data());
    if (rc != 0) {
        qDebug() << "Error querieng window group name";
        return;
    }

    if (windowGroup == QLatin1String(hmiName)) {
        Core::self()->windowManager()->setZValue(windowGroup, ZORDER_MAIN_HMI);
    }

    screen_window_t winHandle = (screen_window_t)(m_speechView->winId());

    QByteArray name(256, 0);
    rc = screen_get_window_property_cv(winHandle, SCREEN_PROPERTY_GROUP, name.size(), name.data());
    if (rc != 0) {
        qDebug() << "Error querieng window group name";
        return;
    }

    if (windowGroup == QLatin1String(name)) {
        Core::self()->windowManager()->setZValue(windowGroup, ZORDER_ASR);
    }
#endif
}

//#define  DEBUG_TEST
int main(int argc, char **argv)
{
#ifdef DEBUG_TEST
    QString sFilePath = QStringLiteral( "/var/logg.txt");

    QFile file(sFilePath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, "提示", "无法创建文件");
        return -1;
    }
    QTextStream out(&file);
    QTime current_time ;
    current_time = QTime::currentTime();
    int hournow = current_time.hour();//当前的小时
    int minutenow = current_time.minute();//当前的分
    int secondnow = current_time.second();//当前的秒
    int msecnow = current_time.msec();//当前的毫秒
    out << "start:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
    qDebug() << "start:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow;
#endif
    WindowManager windowManager;
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "window Manager initover:" << hournow << ":"<<minutenow << ":" <<secondnow<< msecnow;
    out << "window Manager initover:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    if (!windowManager.init()) {
        std::cerr << "Initializing window management failed" << std::endl;
        return 1;
    }

    // register QML types
    qmlRegisterType<QnxCar::ModelMonitor>("com.qnx.car.ui", 2, 0, "ModelMonitor");
    qmlRegisterUncreatableType<ApplicationManager>("com.qnx.car.ui", 2, 0, "ApplicationManager", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCar::AudioPlayer>("com.qnx.car.ui", 2, 0, "AudioPlayer", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCarUi::PaletteItem>("com.qnx.car.ui", 2, 0, "Palette", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCarUi::PaletteManager>("com.qnx.car.ui", 2, 0, "PaletteManager", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCar::Phone>("com.qnx.car.ui", 2, 0, "Phone", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<QnxCar::ProfileManager>("com.qnx.car.ui", 2, 0, "ProfileManager", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCar::ProfileModel>("com.qnx.car.ui", 2, 0, "ProfileListModel", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<QnxCar::Radio>("com.qnx.car.ui", 2, 0, "Radio", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<ScreenManager>("com.qnx.car.ui", 2, 0, "ScreenManager", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<QnxCar::Settings>("com.qnx.car.ui", 2, 0, "Settings", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<QnxCarUi::ThemeManager>("com.qnx.car.ui", 2, 0, "Theme", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<QnxCar::VideoPlayer>("com.qnx.car.ui", 2, 0, "VideoPlayer", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCar::VoiceControl>("com.qnx.car.ui", 2, 0, "VoiceControl", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<VoiceInput>("com.qnx.car.ui", 2, 0, "VoiceInput", QStringLiteral("Access to enums"));
    qmlRegisterUncreatableType<QnxCar::HmiNotificationManager>("com.qnx.car.ui",2,0,"HmiNotificationManager", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<SmartDeviceWorkflow>("com.qnx.car.ui", 2, 0, "SmartDeviceWorkflow", QStringLiteral("Access to enums"));
#ifndef NO_APP_SETTINGS
    // QML types about setting bt/wifi
    qmlRegisterUncreatableType<QnxCar::Bluetooth>("com.qnx.car.core", 2, 0, "Bluetooth", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCar::BluetoothDevicesModel>("com.qnx.car.core", 2, 0, "BluetoothDevicesModel", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<BtWifi_SettingsModule>("com.qnx.car.ui", 2, 0, "BtWifi_SettingsModule", QStringLiteral("Access to object"));
    qmlRegisterUncreatableType<QnxCar::NetworkInfo>("com.qnx.car.ui", 2, 0, "NetworkInfo", QStringLiteral("Access to object"));
#endif

    QGuiApplication app(argc, argv);

    // init Qt Resources from QnxCarUi library
    QnxCarUi::initQtResources();

    const QString assetsPath = QnxCar::StandardDirs::assetsDirectory();

    if (assetsPath.isEmpty()) {
        std::cerr << "Could not find assets path, exiting" << std::endl;
        return 1;
    }
    ApplicationManager applicationManager(&windowManager);

    applicationManager.setExternalApplicaionLaunching(false);
    QnxCarUi::ResolutionManager resolutionManager;
    if (!resolutionManager.parseArguments(app.arguments())) {
        std::cerr << qPrintable(QObject::tr("Could not parse resolution: %1").arg(resolutionManager.errorString())) << std::endl;
        return 1;
    }

    const QSize screensize = resolutionManager.sizeForResolution();
    // initialize core instance
    Core core(&windowManager, &applicationManager);

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "283" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "281:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    Q_UNUSED(core);
/*
    if (!QnxCarUi::loadFonts(assetsPath + QStringLiteral("/fonts"))) {
        std::cerr << "Could not load fonts, exiting" << std::endl;
        return 1;
    }

    */

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "295" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "293:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    QThread windowManagerThread;
    windowManagerThread.moveToThread(&windowManagerThread);
    windowManager.moveToThread(&windowManagerThread);
    QObject::connect(&windowManager, SIGNAL(quit(int,QString)), &windowManagerThread, SLOT(quit()), Qt::QueuedConnection);
    windowManagerThread.start();
    QMetaObject::invokeMethod(&windowManager, "run", Qt::QueuedConnection);
    QFont font(QLatin1String("arial"));
    font.setPixelSize(resolutionManager.defaultPixelSize());
    app.setFont(font);
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "308:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    if (setup_unix_signal_handlers() != 0)
        qFatal("Couldn't register unix signal handlers!");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigFd))
        qFatal("Couldn't create signal socketpair");
    QSocketNotifier *sn = new QSocketNotifier(sigFd[1], QSocketNotifier::Read);
    KeyboardProcess keyboardProcess(&windowManager);

    if (!app.arguments().contains(QStringLiteral("--no-keyboard"))) {
        QObject::connect(sn, SIGNAL(activated(int)), &keyboardProcess, SLOT(kill()));
        QObject::connect(sn, SIGNAL(activated(int)), &app, SLOT(quit()));
        const QString keyboardExecutable = assetsPath + QStringLiteral("/../../bin/qnxcar2-keyboard");
        keyboardProcess.start(keyboardExecutable, QStringList());
        if (!keyboardProcess.waitForStarted()) {
            std::cerr << "Could not start screen keyboard process " << qPrintable(keyboardExecutable) << " - " << qPrintable(keyboardProcess.errorString()) << std::endl;
            windowManager.requestQuit();
            windowManagerThread.wait();
            return 1;
        }

        windowManager.setZValue(keyboardProcess.pid(), ZORDER_KEYBOARD);

        //keyboard is initially invisible, so put it to the left of the screen (-screensize.width())
        //to anchor it at the bottom of the screen, subtract the height, which is 190 (800x480), resp. 304 pixels (720p)

        const QPoint bottomLeft = QPoint(-screensize.width(), screensize.height());
        const QPoint topLeft = bottomLeft - QPoint(0, resolutionManager.mapPixels(470));

        windowManager.setPosition(keyboardProcess.pid(), topLeft);
        applicationManager.addToUnmanagedProcesses(keyboardProcess.pid());
    } else {
        qDebug() << "Not starting keyboard process as requested by '--no-keyboard' option";
    }
    applicationManager.setApplicationGeometry(resolutionManager.externalApplicationGeometry());
    applicationManager.setScreenGeometry(resolutionManager.sizeForResolution());
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "349:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    ScreenManager screenManager;
    AppLauncherServer appLauncherServer;

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "357:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
#ifndef NO_APP_SETTINGS
    QnxCar::SystemInfo systemInfo;

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "357:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    // QnxCar::NetworkInfo networkInfo;

    // networkInfoInitThread.wait();

#endif

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "367:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    QnxCar::AudioControl audioControl;

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "374:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    QnxCar::Bluetooth bluetooth;

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "364:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    QnxCar::Wifi wifi;
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "371:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    QnxCar::HotSpot hotspot;

    QnxCar::NetworkInfo networkInfo;

    QnxCar::Hvac hvac;
    QnxCar::SmartDevice smartdevice;
    QnxCar::ThemeControl themecontrol;
    QnxCar::SeatControl seatcontrol;
    QnxCar::MusicControl musiccontrol;
    QnxCar::CarDoorControl cardoorcontrol;
    QnxCar::AppStatus appstatus;
    QnxCar::CameraControl cameracontrol;
    QnxCar::LampStatus lampstatus;
    QnxCar::Geolocation geolocation;
    QnxCar::Phone phone;
    QnxCar::ProfileModel profileModel(QnxCar::DatabaseManager::database(QStringLiteral("personalization.db")));
    QnxCar::ProfileManager profileManager(&profileModel);
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "391:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    QnxCar::Radio radio;
    radio.setSimulationModeEnabled(false);
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "309 font over" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "399:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    QnxCar::Sensors sensors;
    QnxCar::Settings settings;
    Status status;
    QnxCar::Theme theme;
    Util util;
    QnxCarUi::ThemeManager themeManager(resolutionManager.resolution(), &theme);
    themeManager.setAssetsDirectory(assetsPath);
    QnxCarUi::PaletteManager paletteManager(&themeManager);
    QnxCar::User user;
    QnxCar::VoiceControl voiceControl;
    VoiceInput voiceInput;
    QnxCar::HmiNotificationManager hmiNotificationManager;
    SmartDeviceWorkflow smartDevices;

    ProfileSettingsManager profileSettingsManager;
    profileSettingsManager.setHvac(&hvac);
    profileSettingsManager.setAudioControl(&audioControl);
    profileSettingsManager.setRadio(&radio);
    profileManager.addSettingsListener(&profileSettingsManager);

    screenManager.setCameraControl(&cameracontrol);
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "417wifi" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "426:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
#ifndef NO_APP_SETTINGS
    // create list of available pages
    QMap<int,bool> availPages;

    availPages[BtWifi_SettingsWorkflow::BluetoothConnectivityPage] = bluetooth.active();
    availPages[BtWifi_SettingsWorkflow::SoftwareUpdatesPage] = true; // alvays available
    availPages[BtWifi_SettingsWorkflow::WiredNetworkPage] = true; // alvays available
    availPages[BtWifi_SettingsWorkflow::WifiClientPage] = wifi.isAvailable();
    availPages[BtWifi_SettingsWorkflow::HotSpotPage] = hotspot.isAvailable();

    BtWifi_SettingsModule bt_wifi_settingsModule(&bluetooth, availPages);
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "433wifiover" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "414:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
#endif

    QQuickView view;
    view.setColor(Qt::transparent);
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    //NetWorkInfo
    //    NetWorkInfoInitThread networkInfoInitThread;
    //    networkInfoInitThread.start();
    //    networkInfoInitThread.wait();
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    //qDebug() << "458" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "425:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    ModuleManager moduleManager(&appLauncherServer, view.rootContext());
    QObject::connect(&appLauncherServer, &AppLauncherServer::selectScreen, &screenManager, &ScreenManager::setCurrentScreen);
    QObject::connect(&screenManager, &ScreenManager::screenSelected, &moduleManager, &ModuleManager::screenSelected);
    QObject::connect(&moduleManager, &ModuleManager::selectScreenRequested, &screenManager, &ScreenManager::setCurrentScreen);

    //Restore tab selection state from PPS
    moduleManager.applyNavigatorCommandState();
    cameracontrol.setCapture(QStringLiteral("stop"));

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    // qDebug() << "462" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "439:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    // export business logic objects
    view.rootContext()->setContextProperty(QStringLiteral("_applicationManager"), &applicationManager);
    view.rootContext()->setContextProperty(QStringLiteral("_audioControl"), &audioControl);
    view.rootContext()->setContextProperty(QStringLiteral("_bluetooth"), &bluetooth);
    view.rootContext()->setContextProperty(QStringLiteral("_wifi"), &wifi);
    view.rootContext()->setContextProperty(QStringLiteral("_hotspot"), &hotspot);
    view.rootContext()->setContextProperty(QStringLiteral("_hvac"), &hvac);
    view.rootContext()->setContextProperty(QStringLiteral("_smartdevice"), &smartdevice);
    view.rootContext()->setContextProperty(QStringLiteral("_themecontrol"), &themecontrol);
    view.rootContext()->setContextProperty(QStringLiteral("_seatcontrol"), &seatcontrol);
    view.rootContext()->setContextProperty(QStringLiteral("_musiccontrol"), &musiccontrol);
    view.rootContext()->setContextProperty(QStringLiteral("_cardoorcontrol"), &cardoorcontrol);
    view.rootContext()->setContextProperty(QStringLiteral("_appstatus"), &appstatus);
    view.rootContext()->setContextProperty(QStringLiteral("_cameracontrol"), &cameracontrol);
    view.rootContext()->setContextProperty(QStringLiteral("_lampStatus"), &lampstatus);
    view.rootContext()->setContextProperty(QStringLiteral("_geolocation"), &geolocation);
    view.rootContext()->setContextProperty(QStringLiteral("_palette"), paletteManager.palette());
    view.rootContext()->setContextProperty(QStringLiteral("_phone"), &phone);
    view.rootContext()->setContextProperty(QStringLiteral("_profileManager"), &profileManager);
    view.rootContext()->setContextProperty(QStringLiteral("_profileModel"), &profileModel);
    view.rootContext()->setContextProperty(QStringLiteral("_radio"), &radio);
    view.rootContext()->setContextProperty(QStringLiteral("_screenManager"), &screenManager);
    view.rootContext()->setContextProperty(QStringLiteral("_sensors"), &sensors);
    view.rootContext()->setContextProperty(QStringLiteral("_settings"), &settings);
    view.rootContext()->setContextProperty(QStringLiteral("_status"), &status);
    view.rootContext()->setContextProperty(QStringLiteral("_theme"), &theme);
    view.rootContext()->setContextProperty(QStringLiteral("_themeManager"), &themeManager);
    view.rootContext()->setContextProperty(QStringLiteral("_user"), &user);
    view.rootContext()->setContextProperty(QStringLiteral("_util"), &util);
    view.rootContext()->setContextProperty(QStringLiteral("_voiceInput"), &voiceInput);

    view.rootContext()->setContextProperty(QStringLiteral("_hmiNotificationManager"), &hmiNotificationManager);
    view.rootContext()->setContextProperty(QStringLiteral("_smartDevices"), &smartDevices);
#ifndef NO_APP_SETTINGS
    view.rootContext()->setContextProperty(QStringLiteral("_networkInfo"), &networkInfo);
    view.rootContext()->setContextProperty(QStringLiteral("_systemInfo"), &systemInfo);
    view.rootContext()->setContextProperty(QStringLiteral("_bt_wifi_settingsModule"), &bt_wifi_settingsModule);
#endif
    resolutionManager.setupQmlContext(view.rootContext());

    view.setSource(QUrl::fromLocalFile(assetsPath + QStringLiteral("/qml/main.qml")));

#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    // qDebug() << "517qml" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
    out << "487:" << hournow << ":"<<minutenow << ":"<<secondnow << msecnow << endl;
#endif
    MediaPlayerModule::ScreenManager = &screenManager;
    ApplicationManager::ScreenManager = &screenManager;

    QQuickView speechView;
    speechView.setColor(Qt::transparent);
    speechView.setResizeMode(QQuickView::SizeRootObjectToView);

    QuickViewStateHandler quickViewStateHandler(&view, &speechView);
    QObject::connect(&speechView, &QQuickView::frameSwapped, &quickViewStateHandler, &QuickViewStateHandler::frameSwapped);
    QObject::connect(&windowManager, &WindowManager::windowGroupPosted, &quickViewStateHandler, &QuickViewStateHandler::handleWindowGroupPosted);

    speechView.rootContext()->setContextProperty(QStringLiteral("_util"), &util);
    speechView.rootContext()->setContextProperty(QStringLiteral("_voiceInput"), &voiceInput);
    speechView.rootContext()->setContextProperty(QStringLiteral("_theme"), &theme);
    speechView.rootContext()->setContextProperty(QStringLiteral("_themeManager"), &themeManager);
    speechView.rootContext()->setContextProperty(QStringLiteral("_palette"), paletteManager.palette());
    resolutionManager.setupQmlContext(speechView.rootContext());

    ApplicationManager::ScreenManager->setCurrentScreen(ScreenManager::HomeScreen);

    view.resize(resolutionManager.sizeForResolution());
    view.show();
    // Create this late in case input methods are initialized late at startup
    QnxCarUi::KeyboardAutoCloser keyboardAutoCloser;
#ifdef DEBUG_TEST
    current_time = QTime::currentTime();
    hournow = current_time.hour();//当前的小时
    minutenow = current_time.minute();//当前的分
    secondnow = current_time.second();//当前的秒
    out.flush();
    file.close();
    qDebug() << "551" << hournow << ":"<<minutenow << ":"<<secondnow<< msecnow;
#endif
    const int returnCode = app.exec();

    windowManager.requestQuit();
    windowManagerThread.wait();
    return returnCode;
}

#include "main.moc"
