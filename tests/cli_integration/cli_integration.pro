# Exercise the actual application composition without opening hardware devices.
include(../../DeltaRobotSoftware.pro)
QT += testlib
CONFIG += console testcase
CONFIG -= app_bundle
TARGET = tst_cli_integration
RC_ICONS =
SOURCES -= $$clean_path($$PWD/../../src/main.cpp)
SOURCES += $$PWD/tst_cli_integration.cpp
