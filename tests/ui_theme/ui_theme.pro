QT += core gui widgets multimedia network concurrent testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_ui_theme
INCLUDEPATH += $$PWD/form_widgets $$PWD/../../include
DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)
QT += svg
greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets
win32:LIBS += strmiids.lib ole32.lib oleaut32.lib
SOURCES += $$PWD/../../src/DrawingProgram.cpp \
    $$PWD/../../src/DrawingVectorImporter.cpp \
    $$PWD/../../src/DrawingWidget.cpp \
    $$PWD/../../src/DrawingExporter.cpp \
    $$PWD/../../src/CameraSelectionDialog.cpp \
    $$PWD/../../src/PhoneCameraDialog.cpp \
    $$PWD/../../src/PhoneCameraServer.cpp
HEADERS += $$PWD/../../include/DrawingWidget.h \
    $$PWD/../../include/DrawingVectorImporter.h \
    $$PWD/../../include/DrawingExporter.h \
    $$PWD/../../include/CameraSelectionDialog.h \
    $$PWD/../../include/PhoneCameraDialog.h \
    $$PWD/../../include/PhoneCameraServer.h
SOURCES += $$PWD/tst_ui_theme.cpp \
    $$PWD/../../src/UiTheme.cpp \
    $$PWD/../../src/RobotPanelLayout.cpp \
    $$PWD/../../src/GcodeHighlighter.cpp \
    $$PWD/../../src/SettingsPanel.cpp \
    $$PWD/../../src/SettingsManager.cpp \
    $$PWD/../../src/ModernDialog.cpp
HEADERS += $$PWD/../../include/UiTheme.h \
    $$PWD/../../include/RobotPanelLayout.h \
    $$PWD/../../include/GcodeHighlighter.h \
    $$PWD/../../include/SettingsPanel.h \
    $$PWD/../../include/SettingsManager.h \
    $$PWD/../../include/ModernDialog.h
FORMS += $$PWD/../../ui/RobotWindow.ui $$PWD/../../ui/MainWindow.ui \
    $$PWD/../../ui/FilterWindow.ui
RESOURCES += $$PWD/../../resource.qrc
