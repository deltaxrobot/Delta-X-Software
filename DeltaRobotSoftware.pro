#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport opengl network multimedia

windows {
    INCLUDEPATH += E:\OpenCV\opencv-4.0\build\include
    LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400.lib
    LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400d.lib
}

linux {
    INCLUDEPATH += "/usr/local/include/opencv4"
    INCLUDEPATH += "/"
    LIBS += $(shell pkg-config opencv --libs)
    LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio
}

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
    MainWindow.cpp \
    ObjectVariableTable.cpp \
    ProjectManager.cpp \
    ProjectWindow.cpp \
    SmartDialog.cpp \
    TCPConnectionManager.cpp \
    TabDashboard.cpp \
    TextLayer.cpp \
    codeeditor.cpp \
    ConnectionManager.cpp \
    DeltaVisualizer.cpp \
    GcodeProgramManager.cpp \
    GcodeProgram.cpp \
    UnityTool.cpp \
    geisttextedit.cpp \
    highlighter.cpp \
    hsvwindow.cpp \
    robotmanager.cpp

HEADERS  += \
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
    MainWindow.h \
    ObjectVariableTable.h \
    ProjectManager.h \
    ProjectWindow.h \
    SmartDialog.h \
    TCPConnectionManager.h \
    TabDashboard.h \
    TextLayer.h \
    codeeditor.h \
    geisttextedit.h \
    highlighter.h \
    hsvwindow.h \
    GcodeReference.h \
    robotmanager.h \
    sdk/DeltaXPlugin.h

FORMS    += \
    MainWindow.ui \
    ProjectWindow.ui \
    hsvwindow.ui \
        GcodeReference.ui

RESOURCES += \
    resource.qrc

include ($$PWD/3rd-party/QJoysticks/QJoysticks.pri)

