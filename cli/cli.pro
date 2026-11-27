QT = core network
CONFIG += console c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = delta-x-cli
DELTA_X_ROOT = $$clean_path($$PWD/..)
INCLUDEPATH += $$DELTA_X_ROOT/include $$DELTA_X_ROOT
include($$DELTA_X_ROOT/config/version.pri)
SOURCES += $$PWD/main.cpp
HEADERS += $$PWD/../include/CliProtocol.h
HEADERS += $$PWD/../sdk/DeltaXVersion.h
