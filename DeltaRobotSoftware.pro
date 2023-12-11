#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport opengl network quickwidgets printsupport multimedia

windows {
    INCLUDEPATH += $$PWD\3rd-party\opencv\build\include
    LIBS += $$PWD\3rd-party\opencv\build\x64\vc15\lib\opencv_world400.lib
    LIBS += $$PWD\3rd-party\opencv\build\x64\vc15\lib\opencv_world400d.lib

#    include ($$PWD\3rd-party\QJoysticks\QJoysticks.pri)
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
    ComDevice.cpp \
    DrawingExporter.cpp \
    DrawingWidget.cpp \
    FilterWindow.cpp \
    GcodeHighlighter.cpp \
    GcodeReference.cpp \
    GcodeScript.cpp \
    ImageProcessing.cpp \
    ImageViewer.cpp \
    Layer.cpp \
    MainWindow.cpp \
    Object.cpp \
    ObjectInfo.cpp \
    ObjectVariableTable.cpp \
    Parameter.cpp \
    PointTool.cpp \
    ProjectManager.cpp \
    RobotWindow.cpp \
    SmartDialog.cpp \
    SocketConnectionManager.cpp \
    SoftwareManager.cpp \
    TCPConnectionManager.cpp \
    TabDashboard.cpp \
    TaskNode.cpp \
    TestCode.cpp \
    TextLayer.cpp \
    TrackingManager.cpp \
    VariableManager.cpp \
    VersionManager.cpp \
    codeeditor.cpp \
    DeltaVisualizer.cpp \
    UnityTool.cpp \
    device/DeviceManager.cpp \
    device/camera.cpp \
    device/conveyor.cpp \
    device/device.cpp \
    device/encoder.cpp \
    device/robot.cpp \
    device/slider.cpp \
    geisttextedit.cpp \
    global.cpp \
    highlighter.cpp \
    testwindow.cpp

HEADERS  += \
    AccountWindow.h \
    Authority.h \
    ComDevice.h \
    DeltaVisualizer.h \
    DrawingExporter.h \
    DrawingWidget.h \
    FilterWindow.h \
    GcodeHighlighter.h \
    GcodeReference.h \
    GcodeScript.h \
    ImageUnity.h \
    ImageViewer.h \
    Layer.h \
    MainWindow.h \
    Object.h \
    ImageProcessing.h \
    ObjectInfo.h \
    ObjectInfoModel.h \
    ObjectVariableTable.h \
    Parameter.h \
    PointTool.h \
    ProjectManager.h \
    RobotWindow.h \
    ScurveInterpolator.h \
    SmartDialog.h \
    SocketConnectionManager.h \
    SoftwareManager.h \
    TCPConnectionManager.h \
    TabDashboard.h \
    TaskNode.h \
    TextLayer.h \
    TrackingManager.h \
    VariableManager.h \
    VersionManager.h \
    codeeditor.h \
    device/DeviceManager.h \
    device/camera.h \
    device/conveyor.h \
    device/device.h \
    device/encoder.h \
    device/robot.h \
    device/slider.h \
    geisttextedit.h \
    global.h \
    highlighter.h \
    GcodeReference.h \
    sdk/DeltaXPlugin.h \
    testcode.h \
    testwindow.h

FORMS    += \
    AccountWindow.ui \
    FilterWindow.ui \
    MainWindow.ui \
    RobotWindow.ui \
    GcodeReference.ui \
    testwindow.ui

RESOURCES += \
    resource.qrc

RC_ICONS = delta_x_logo_96x96.ico

DISTFILES +=



