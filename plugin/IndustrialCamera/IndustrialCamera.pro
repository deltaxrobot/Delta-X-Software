QT += gui core widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CameraReader.cpp \
    IndustrialCameraPlugin.cpp \
    form.cpp \
    xcam.cpp \
    xcambasler.cpp \
    xcamhik.cpp \
    xcammanager.cpp

HEADERS += \
    ../../../DeltaXSoftware/sdk/DeltaXPlugin.h \
    CameraReader.h \
    ImageUnity.h \
    IndustrialCameraPlugin.h \
    form.h \
    xcam.h \
    xcambasler.h \
    xcamhik.h \
    xcammanager.h

INCLUDEPATH += \
$$PWD\3rd-party\pylon\include \
$$PWD\3rd-party\pylon\include\pylon \
$$PWD\3rd-party\mvs\Includes

LIBS += -L$$PWD\3rd-party\pylon\lib\x64
LIBS += $$PWD\3rd-party\mvs\Libraries\win64\MvCameraControl.lib

INCLUDEPATH += $$PWD\3rd-party\opencv\build\include
LIBS += $$PWD\3rd-party\opencv\build\x64\vc15\lib\opencv_world400.lib
LIBS += $$PWD\3rd-party\opencv\build\x64\vc15\lib\opencv_world400d.lib


DISTFILES += IndustrialCameraPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    form.ui
