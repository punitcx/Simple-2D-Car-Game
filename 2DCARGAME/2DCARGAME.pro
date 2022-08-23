#-------------------------------------------------
#
# Project created by QtCreator 2019-05-20T12:34:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia network

TARGET = 2DCARGAME
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    car.cpp \
    track.cpp \
    sun.cpp \
    cloud.cpp \
    battery.cpp \
    spawn.cpp

HEADERS  += mainwindow.h \
    car.h \
    track.h \
    sun.h \
    cloud.h \
    battery.h \
    spawn.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
