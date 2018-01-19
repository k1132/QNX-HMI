DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

SOURCES += \
           $$PWD/Exception.cpp \
           $$PWD/WindowManager_qnx.cpp

HEADERS += \
    $$PWD/Exception.h \
    $$PWD/WindowManager.h \
    $$PWD/Optional.h \

qnx {
    LIBS += -lscreen
}
