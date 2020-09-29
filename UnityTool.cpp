#include <UnityTool.h>
#include "mainwindow.h"
#include <qlist.h>

QLabel* DebugLB;
QList<QLabel*> Debugs;

QString ConveyorString;

void Debug(QString msg)
{
    foreach (QLabel* debugLB, Debugs)
	{
		debugLB->setText(msg);
	}
}
