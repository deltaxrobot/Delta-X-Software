#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport opengl


INCLUDEPATH +=  F:\OpenCV\opencv-3.3.0\include
LIBS += -LF:\OpenCV\opencv-3.3.0\x64\vc14\lib \
    -lopencv_world330d

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeltaRobotSoftware
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ConnectionManager.cpp \
    DeltaVisualizer.cpp \
    glwidget.cpp \
    logo.cpp

HEADERS  += mainwindow.h \
    ConnectionManager.h \
    DeltaVisualizer.h \
    glwidget.h \
    logo.h \
    ImageUnity.h

FORMS    += mainwindow.ui
