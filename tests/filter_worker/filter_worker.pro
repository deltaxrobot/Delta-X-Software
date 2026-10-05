QT += core testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_filter_worker

INCLUDEPATH += $$PWD/../../include

DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)

SOURCES += \
    $$PWD/tst_filter_worker.cpp \
    $$PWD/../../src/FilterWork.cpp

HEADERS += $$PWD/../../include/FilterWork.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
