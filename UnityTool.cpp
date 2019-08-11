#include <UnityTool.h>
#include "mainwindow.h"
#include <qlist.h>

QLabel* DebugLB;
QList<QLabel*> Debugs;

QString ConvenyorString;

void Debug(QString msg)
{
	for each (QLabel* debugLB in Debugs)
	{
		debugLB->setText(msg);
	}
}