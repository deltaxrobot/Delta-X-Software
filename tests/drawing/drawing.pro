QT += core gui widgets svg testlib
greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_drawing
INCLUDEPATH += $$PWD/../../include
DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)
SOURCES += $$PWD/tst_drawing.cpp \
    $$PWD/../../src/DrawingProgram.cpp \
    $$PWD/../../src/DrawingVectorImporter.cpp \
    $$PWD/../../src/DrawingWidget.cpp \
    $$PWD/../../src/DrawingExporter.cpp
HEADERS += $$PWD/../../include/DrawingProgram.h \
    $$PWD/../../include/DrawingVectorImporter.h \
    $$PWD/../../include/DrawingWidget.h \
    $$PWD/../../include/DrawingExporter.h
