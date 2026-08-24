#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport network printsupport multimedia svg concurrent

greaterThan(QT_MAJOR_VERSION, 5) {
    QT += svgwidgets
    qtHaveModule(core5compat): QT += core5compat
}

# Drop Qt Creator's qml_debug instrumentation to shrink debug builds (helps avoid C1060)
CONFIG -= qml_debug
DEFINES -= QT_QML_DEBUG

# Ensure C++17 and proper __cplusplus value for MSVC (required by Qt 6)
CONFIG += c++17
win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus /permissive- /bigobj /Zm800 /FS
    QMAKE_CXXFLAGS_RELEASE += /std:c++17 /Zc:__cplusplus /permissive- /bigobj /Zm800 /FS
    QMAKE_CXXFLAGS_DEBUG += /std:c++17 /Zc:__cplusplus /permissive- /bigobj /Zm800 /FS

    # Use /Z7 for debug info to reduce compiler memory usage (instead of /Zi)
    QMAKE_CFLAGS_DEBUG -= -Zi /Zi
    QMAKE_CXXFLAGS_DEBUG -= -Zi /Zi
    QMAKE_CFLAGS_DEBUG += /Z7
    QMAKE_CXXFLAGS_DEBUG += /Z7
}

macx {
    QMAKE_INFO_PLIST = $$PWD/resources/macos/Info.plist
}

DELTA_X_ROOT = $$PWD
include($$DELTA_X_ROOT/config/version.pri)
include($$DELTA_X_ROOT/config/opencv.pri)

#unix:!macx
#{
#    INCLUDEPATH += "/usr/local/include"
##    LIBS += $(shell pkg-config opencv --libs)
#    LIBS += -L/home/trungdoanhong/Documents/opencv-4.0/sources/build/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio

#}



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeltaRobotSoftware
TEMPLATE = app

INCLUDEPATH += \
    $$PWD \
    $$PWD/include \
    $$PWD/include/device \
    $$PWD/sdk

DEPENDPATH += $$INCLUDEPATH

SOURCES += \
    $$files($$PWD/src/*.cpp) \
    $$files($$PWD/src/device/*.cpp)

HEADERS += \
    $$files($$PWD/include/*.h) \
    $$files($$PWD/include/device/*.h) \
    $$files($$PWD/sdk/*.h)

FORMS += \
    $$files($$PWD/ui/*.ui)

RESOURCES += $$PWD/resource.qrc

RC_ICONS = delta_x_logo_96x96.ico

DISTFILES += \
    $$PWD/docs/external-vision.md \
    $$PWD/docs/gscript-design.md \
    $$PWD/docs/gscript-runtime.md \
    $$PWD/docs/multi-robot-conveyor-sorting.md \
    $$PWD/docs/plugin-system.md \
    $$PWD/docs/variable-manager.md \
    $$PWD/script-example/dxv1_client.py \
    $$PWD/script-example/multi-robot-sorting/00-vision-tracking.gcode \
    $$PWD/script-example/multi-robot-sorting/10-robot0-type0.gcode \
    $$PWD/script-example/multi-robot-sorting/11-robot1-type1.gcode \
    $$PWD/script-example/multi-robot-sorting/README.md \
    $$PWD/script-example/receive_image_json.py \
    $$PWD/script-example/yolov8_detect.py
