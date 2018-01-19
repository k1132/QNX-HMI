#include "Core.h"

#include <QDebug>
#include <QGlobalStatic>
#include <QThread>

Core* Core::s_instance = 0;

Core::Core(WindowManager *windowManager,
           ApplicationManager *applicationManager)
    : QObject(0)
    , m_windowManager(windowManager)
    , m_applicationManager(applicationManager)
{
    s_instance = this;
}

Core::~Core()
{
    s_instance = 0;
}

Core* Core::self()
{
    if (!s_instance) {
        qWarning() << Q_FUNC_INFO << "Accessing Core::self() in uninitialized state";
    }
    return s_instance;
}

WindowManager *Core::windowManager() const
{
    return m_windowManager;
}

ApplicationManager *Core::applicationManager() const
{
    return m_applicationManager;
}
