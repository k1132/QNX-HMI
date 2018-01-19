#ifndef APP_CORE_H
#define APP_CORE_H

#include <QObject>

class ApplicationManager;
class WindowManager;

class Core : public QObject
{
    Q_OBJECT

public:
    /// Construct this instance
    Core(WindowManager *windowManager,
         ApplicationManager *applicationManager);
    virtual ~Core();

    /// Access the single instance of this class
    static Core *self();

    WindowManager *windowManager() const;
    ApplicationManager *applicationManager() const;

private:
    static Core *s_instance;

    WindowManager *m_windowManager;
    ApplicationManager *m_applicationManager;
};

#endif
