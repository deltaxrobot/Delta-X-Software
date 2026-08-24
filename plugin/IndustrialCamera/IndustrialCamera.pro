QT += gui core widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

win32:msvc*: QMAKE_CXXFLAGS += /wd4828

# Plugin configuration
TARGET = IndustrialCameraPlugin
DESTDIR = $$OUT_PWD/plugin

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
    ../../sdk/DeltaXPlugin.h \
    ../../sdk/DeltaXPluginV2.h \
    ../../sdk/DeltaXPanelProvider.h \
    ../../sdk/DeltaXCommandProvider.h \
    CameraReader.h \
    ImageUnity.h \
    IndustrialCameraPlugin.h \
    form.h \
    xcam.h \
    xcambasler.h \
    xcamhik.h \
    xcammanager.h

DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)

# Public builds use SDKs installed outside the repository. Set these as qmake
# variables or environment variables. The legacy snapshots require an explicit
# CONFIG+=legacy_vendor_sdks opt-in and must not be redistributed.
isEmpty(DELTA_X_PYLON_ROOT): DELTA_X_PYLON_ROOT = $$(DELTA_X_PYLON_ROOT)
isEmpty(DELTA_X_MVS_ROOT): DELTA_X_MVS_ROOT = $$(DELTA_X_MVS_ROOT)

contains(CONFIG, legacy_vendor_sdks) {
    isEmpty(DELTA_X_PYLON_ROOT): DELTA_X_PYLON_ROOT = $$PWD/3rd-party/pylon
    isEmpty(DELTA_X_MVS_ROOT): DELTA_X_MVS_ROOT = $$PWD/3rd-party/mvs
    warning("Using quarantined legacy camera SDKs; do not redistribute them")
}

isEmpty(DELTA_X_PYLON_ROOT): error("Set DELTA_X_PYLON_ROOT to the Basler pylon Development directory")
isEmpty(DELTA_X_MVS_ROOT): error("Set DELTA_X_MVS_ROOT to the Hikrobot MVS Development directory")
!exists($$DELTA_X_PYLON_ROOT/include/pylon/PylonIncludes.h): \
    error("Invalid DELTA_X_PYLON_ROOT: pylon/PylonIncludes.h was not found")
!exists($$DELTA_X_MVS_ROOT/Includes/MvCameraControl.h): \
    error("Invalid DELTA_X_MVS_ROOT: MvCameraControl.h was not found")
!exists($$DELTA_X_MVS_ROOT/Libraries/win64/MvCameraControl.lib): \
    error("Invalid DELTA_X_MVS_ROOT: win64/MvCameraControl.lib was not found")

INCLUDEPATH += \
    $$DELTA_X_PYLON_ROOT/include \
    $$DELTA_X_PYLON_ROOT/include/pylon \
    $$DELTA_X_MVS_ROOT/Includes

LIBS += -L"$$DELTA_X_PYLON_ROOT/lib/x64"
LIBS += "$$DELTA_X_MVS_ROOT/Libraries/win64/MvCameraControl.lib"

# Keep the plugin loadable when one or both vendor runtimes are absent. The
# manager probes and preloads each SDK before any delayed symbol is called, so
# a machine can use Hikrobot without pylon, Basler without MVS, or neither
# backend without preventing Delta X Software from starting.
win32:msvc* {
    QMAKE_LFLAGS += \
        /DELAYLOAD:MVCameraControl.dll \
        /DELAYLOAD:GCBase_MD_VC141_v3_1_Basler_pylon.dll \
        /DELAYLOAD:PylonUtility_v9.dll \
        /DELAYLOAD:PylonBase_v9.dll
    LIBS += Delayimp.lib
}

DISTFILES += IndustrialCameraPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    form.ui
