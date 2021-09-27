#pragma once
#include <qstring.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <QElapsedTimer>

#define NULL_NUMBER -6789

extern QString ConveyorString;

extern QTextEdit* DebugLB;

extern QList<QTextEdit*> Debugs;

extern QElapsedTimer ElapsedTimer;

void Debug(QString msg);
void Debug(int id, QString msg);
