QT += core gui \
        multimedia \
        xml

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = Timer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainWindow.cpp \
    Countdown.cpp \
    showtimer.cpp \
    database.cpp

HEADERS += \
    Countdown.hpp \
    mainWindow.h \
    showtimer.h \
    database.hpp

FORMS += mainWindow.ui \
    showtimer.ui

RESOURCES += \
    Rcs.qrc
