#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport opengl webview webenginewidgets


#INCLUDEPATH +=  F:\OpenCV\opencv-3.3.0\include
#LIBS += -LF:\OpenCV\opencv-3.3.0\x64\vc14\lib \
#    -lopencv_world330d

INCLUDEPATH += "/usr/local/inlcude/"

LIBS += `pkg-config --libs opencv`

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeltaRobotSoftware
TEMPLATE = app


SOURCES += main.cpp\
    BlobManager.cpp \
    CameraWidget.cpp \
    DrawingExporter.cpp \
    DrawingWidget.cpp \
    GcodeReference.cpp \
    ImageProcesser.cpp \
    Layer.cpp \
    ObjectVariableTable.cpp \
    ROS.cpp \
    TCPConnectionManager.cpp \
    TextLayer.cpp \
    codeeditor.cpp \
        mainwindow.cpp \
    ConnectionManager.cpp \
    DeltaVisualizer.cpp \
    GcodeProgramManager.cpp \
    GcodeProgram.cpp \
    UnityTool.cpp \
    hsvwindow.cpp \

HEADERS  += mainwindow.h \
    BlobManager.h \
    CameraWidget.h \
    ConnectionManager.h \
    DeltaVisualizer.h \
    DrawingExporter.h \
    DrawingWidget.h \
    GcodeReference.h \
    ImageProcesser.h \
    ImageUnity.h \
    GcodeProgram.h \
    GcodeProgramManager.h \
    Layer.h \
    ObjectVariableTable.h \
    ROS.h \
    TCPConnectionManager.h \
    TextLayer.h \
    codeeditor.h \
    hsvwindow.h \
    GcodeReference.h \

FORMS    += mainwindow.ui \
    hsvwindow.ui \
        GcodeReference.ui \

