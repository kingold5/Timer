QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

TARGET = Timer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainWindow.cpp \
    Countdown.cpp

HEADERS += \
    Countdown.hpp \
    mainWindow.h \

FORMS += mainWindow.ui \
    mainWindow.ui
