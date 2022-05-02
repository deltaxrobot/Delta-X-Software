QT += gui core widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CameraProcessor.cpp \
    CameraReader.cpp \
    IndustrialCameraPlugin.cpp \
    camerawidget.cpp \
    form.cpp \
    xcam.cpp \
    xcambasler.cpp \
    xcamhik.cpp \
    xcammanager.cpp

HEADERS += \
    ../../../DeltaXSoftware/sdk/DeltaXPlugin.h \
    CameraProcessor.h \
    CameraReader.h \
    ImageUnity.h \
    IndustrialCameraPlugin.h \
    camerawidget.h \
    form.h \
    xcam.h \
    xcambasler.h \
    xcamhik.h \
    xcammanager.h

INCLUDEPATH += \
$$(PYLON_DEV_DIR)/include \
$$(PYLON_DEV_DIR)/include/pylon \
"C:/Program Files (x86)/MVS/Development/Includes"

LIBS += \
-L$$(PYLON_DEV_DIR)/lib/x64

INCLUDEPATH += E:\OpenCV\opencv-4.0\build\include
LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400.lib
LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400d.lib
LIBS += "C:\Program Files (x86)\MVS\Development\Libraries\win64\MvCameraControl.lib"

DISTFILES += IndustrialCameraPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    form.ui
