QT += core gui \
        multimedia

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

TARGET = Timer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainWindow.cpp \
    Countdown.cpp \
    showtimer.cpp

HEADERS += \
    Countdown.hpp \
    mainWindow.h \
    showtimer.h

FORMS += mainWindow.ui \
    showtimer.ui

RESOURCES += \
    res.qrc
