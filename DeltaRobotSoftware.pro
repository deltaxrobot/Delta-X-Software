#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T23:50:40
#
#-------------------------------------------------

QT       += core gui serialport opengl network printsupport multimedia svg concurrent

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
    QMAKE_CFLAGS += -include arm_acle.h
    QMAKE_CXXFLAGS += -include arm_acle.h
}

windows {
    INCLUDEPATH += $$PWD/3rd-party/opencv/build/include
    LIBS += $$PWD/3rd-party/opencv/build/x64/vc15/lib/opencv_world400.lib
    LIBS += $$PWD/3rd-party/opencv/build/x64/vc15/lib/opencv_world400d.lib

#    include ($$PWD/3rd-party/QJoysticks/QJoysticks.pri)
}

linux {
    INCLUDEPATH += /usr/local/include/opencv4
    LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_calib3d
}

macx {
    isEmpty(OPENCV_DIR) {
        OPENCV_CANDIDATES = \
            /opt/homebrew \
            /usr/local \
            $$clean_path($$getenv(HOME))/micromamba/envs/deltax-build

        for(candidate, OPENCV_CANDIDATES) {
            isEmpty(OPENCV_DIR): exists($$candidate/include/opencv4/opencv2/core.hpp) {
                OPENCV_DIR = $$candidate
            }
        }
    }

    OPENCV_INCLUDE_DIR = $$OPENCV_DIR/include/opencv4
    OPENCV_LIB_DIR = $$OPENCV_DIR/lib

    exists($$OPENCV_INCLUDE_DIR/opencv2/core.hpp) {
        message("Linking against OpenCV found at $$OPENCV_DIR")
        INCLUDEPATH += $$OPENCV_INCLUDE_DIR
        LIBS += -L$$OPENCV_LIB_DIR -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_calib3d
        QMAKE_RPATHDIR += $$OPENCV_LIB_DIR
    } else {
        message("Warning: OpenCV headers not found under $$OPENCV_DIR. Override OPENCV_DIR when running qmake if OpenCV is installed elsewhere.")
    }
}

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

DISTFILES +=
