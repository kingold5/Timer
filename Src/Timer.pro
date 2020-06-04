QT += core gui \
        multimedia \
        xml

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = Timer
TEMPLATE = app

SOURCES += \
    addplan.cpp \
    main.cpp \
    mainWindow.cpp \
    Countdown.cpp \
    projectsmodel.cpp \
    showtimer.cpp \
    database.cpp \
    temphistory.cpp \
    userplans.cpp \
    userprojectmodel.cpp

HEADERS += \
    Countdown.hpp \
    addplan.h \
    mainWindow.h \
    projectsmodel.h \
    projectsstruct.h \
    showtimer.h \
    database.hpp \
    temphistory.h \
    userplans.h \
    userprojectmodel.h

FORMS += mainWindow.ui \
    addplan.ui \
    showtimer.ui \
    temphistory.ui \
    userplans.ui

RESOURCES += \
    Rcs.qrc

DISTFILES +=
