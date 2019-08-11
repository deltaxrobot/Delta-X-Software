#pragma once
#include <qstring.h>
#include <qlabel.h>

#define NULL_NUMBER -6789

extern QString ConvenyorString;

extern QLabel* DebugLB;

extern QList<QLabel*> Debugs;

void Debug(QString msg);
