#pragma once
#include <qstring.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <QElapsedTimer>
#include <QStandardItem>

#define NULL_NUMBER -6789

extern QString ConveyorString;

extern QTextEdit* DebugLB;

extern QList<QTextEdit*> Debugs;

extern QElapsedTimer ElapsedTimer;
extern QTextEdit* teSoftwareLog;

QString DeleteExcessSpace(QString text);
QString GetValueInGcode(QString key, QString gcode);
bool IsInRange(QPolygonF poly);

void Debug(QString msg);
void Debug(int id, QString msg);
void SoftwareLog(QString msg, bool isNewLine = true);

namespace UnityTool
{
    void UpdateVarToModel(QStandardItem *parent, QString fullKey, QVariant value);
}

