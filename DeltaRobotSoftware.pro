#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport opengl network multimedia quick3d quickwidgets

windows {
    INCLUDEPATH += E:\OpenCV\opencv-4.0\build\include
    LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400.lib
    LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400d.lib

    include ($$PWD\3rd-party\QJoysticks\QJoysticks.pri)
}

#linux
#{
#    INCLUDEPATH += "/usr/local/include"
#    INCLUDEPATH += "/"
#    LIBS += $(shell pkg-config opencv --libs)
#    LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio
#}

#unix:!macx
#{
#    INCLUDEPATH += "/usr/local/include"
##    LIBS += $(shell pkg-config opencv --libs)
#    LIBS += -L/home/trungdoanhong/Documents/opencv-4.0/sources/build/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio

#}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeltaRobotSoftware
TEMPLATE = app


SOURCES += main.cpp\
    AccountWindow.cpp \
    Authority.cpp \
    BlobManager.cpp \
    CameraWidget.cpp \
    ComDevice.cpp \
    DrawingExporter.cpp \
    DrawingWidget.cpp \
    GcodeReference.cpp \
    Layer.cpp \
    MainWindow.cpp \
    ObjectDetector.cpp \
    ObjectVariableTable.cpp \
    ProjectManager.cpp \
    Robot.cpp \
    RobotWindow.cpp \
    SmartDialog.cpp \
    SoftwareManager.cpp \
    TCPConnectionManager.cpp \
    TabDashboard.cpp \
    TextLayer.cpp \
    UXManage.cpp \
    VariableManager.cpp \
    VersionManager.cpp \
    VideoDisplay.cpp \
    VideoProcessor.cpp \
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
    AccountWindow.h \
    Authority.h \
    BlobManager.h \
    CameraWidget.h \
    ComDevice.h \
    ConnectionManager.h \
    DeltaVisualizer.h \
    DrawingExporter.h \
    DrawingWidget.h \
    GcodeReference.h \
    ImageUnity.h \
    GcodeProgram.h \
    GcodeProgramManager.h \
    Layer.h \
    MainWindow.h \
    ObjectDetector.h \
    ObjectVariableTable.h \
    ProjectManager.h \
    Robot.h \
    RobotWindow.h \
    ScurveInterpolator.h \
    SmartDialog.h \
    SoftwareManager.h \
    TCPConnectionManager.h \
    TabDashboard.h \
    TextLayer.h \
    UXManager.h \
    VariableManager.h \
    VersionManager.h \
    VideoDisplay.h \
    VideoProcessor.h \
    codeeditor.h \
    geisttextedit.h \
    highlighter.h \
    hsvwindow.h \
    GcodeReference.h \
    robotmanager.h \
    sdk/DeltaXPlugin.h

FORMS    += \
    AccountWindow.ui \
    HSVWindow.ui \
    MainWindow.ui \
    RobotWindow.ui \
    hsvwindow.ui \
        GcodeReference.ui \

RESOURCES += \
    resource.qrc

RC_ICONS = delta_x_logo_96x96.ico

DISTFILES += \
    SettingTree.json



