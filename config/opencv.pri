# Shared OpenCV discovery for the application and test projects.
# The including .pro file must set DELTA_X_ROOT to the repository root.

isEmpty(DELTA_X_ROOT) {
    error("DELTA_X_ROOT must be set before including config/opencv.pri")
}

win32 {
    isEmpty(OPENCV_DIR) {
        OPENCV_DIR = $$DELTA_X_ROOT/3rd-party/opencv/build
    }
    isEmpty(OPENCV_WORLD_VERSION) {
        OPENCV_WORLD_VERSION = 400
    }

    OPENCV_INCLUDE_DIR = $$OPENCV_DIR/include
    OPENCV_LIB_CANDIDATES = \
        $$OPENCV_DIR/x64/vc17/lib \
        $$OPENCV_DIR/x64/vc16/lib \
        $$OPENCV_DIR/x64/vc15/lib \
        $$OPENCV_DIR/x64/vc14/lib
    OPENCV_LIB_DIR =
    for(candidate, OPENCV_LIB_CANDIDATES) {
        isEmpty(OPENCV_LIB_DIR):exists($$candidate/opencv_world$${OPENCV_WORLD_VERSION}.lib) {
            OPENCV_LIB_DIR = $$candidate
        }
    }
    !exists($$OPENCV_INCLUDE_DIR/opencv2/core.hpp) {
        error("OpenCV headers not found under $$OPENCV_INCLUDE_DIR. Pass OPENCV_DIR=...")
    }
    isEmpty(OPENCV_LIB_DIR) {
        error("OpenCV library opencv_world$${OPENCV_WORLD_VERSION}.lib was not found under $$OPENCV_DIR/x64/vc*/lib")
    }

    INCLUDEPATH += $$OPENCV_INCLUDE_DIR
    CONFIG(debug, debug|release) {
        exists($$OPENCV_LIB_DIR/opencv_world$${OPENCV_WORLD_VERSION}d.lib) {
            LIBS += $$OPENCV_LIB_DIR/opencv_world$${OPENCV_WORLD_VERSION}d.lib
        } else {
            warning("OpenCV debug library is unavailable; using the release library")
            LIBS += $$OPENCV_LIB_DIR/opencv_world$${OPENCV_WORLD_VERSION}.lib
        }
    } else {
        LIBS += $$OPENCV_LIB_DIR/opencv_world$${OPENCV_WORLD_VERSION}.lib
    }
}

unix {
    CONFIG += link_pkgconfig
    packagesExist(opencv4) {
        PKGCONFIG += opencv4
    } else {
        error("OpenCV 4 was not found by pkg-config. Install opencv4 or set PKG_CONFIG_PATH.")
    }
}
