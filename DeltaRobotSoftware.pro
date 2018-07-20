#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeltaRobotSoftware
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ConnectionManager.cpp

HEADERS  += mainwindow.h \
    ConnectionManager.h

FORMS    += mainwindow.ui
