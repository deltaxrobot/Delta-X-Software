#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport opengl network

windows {
    INCLUDEPATH += E:\OpenCV\opencv-4.0\build\include
    LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400.lib
    LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400d.lib
}

linux {
    INCLUDEPATH += "/usr/local/inlcude/"
    LIBS += `pkg-config --libs opencv`
}
#INCLUDEPATH +=  F:\OpenCV\opencv-3.3.0\include
#LIBS += -LF:\OpenCV\opencv-3.3.0\x64\vc14\lib \
#    -lopencv_world330d



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
    robotmanager.cpp

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
    TCPConnectionManager.h \
    TextLayer.h \
    codeeditor.h \
    hsvwindow.h \
    GcodeReference.h \
    robotmanager.h

FORMS    += mainwindow.ui \
    hsvwindow.ui \
        GcodeReference.ui \

RESOURCES += \
    resource.qrc

