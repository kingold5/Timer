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
    myspinbox.cpp \
    projectsmodel.cpp \
    showtimer.cpp \
    database.cpp \
    temphistory.cpp \
    uisingleplan.cpp \
    userplans.cpp \
    userprojectmodel.cpp

HEADERS += \
    Countdown.hpp \
    mainWindow.h \
    myspinbox.h \
    projectsmodel.h \
    projectsstruct.h \
    showtimer.h \
    database.hpp \
    temphistory.h \
    uisingleplan.h \
    userplans.h \
    userprojectmodel.h

FORMS += mainWindow.ui \
    showtimer.ui \
    temphistory.ui \
    uisingleplan.ui \
    userplans.ui

RESOURCES += \
    Rcs.qrc

DISTFILES +=
