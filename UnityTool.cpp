#include <UnityTool.h>
#include "RobotWindow.h"
#include <qlist.h>

QTextEdit* DebugLB;
QList<QTextEdit*> Debugs;

QString ConveyorString;

void Debug(QString msg)
{
    foreach (QTextEdit* debugLB, Debugs)
	{
		QString lastText = debugLB->toPlainText();
		if (lastText.split('\n').count() > 50)
			lastText = "";
		debugLB->setText(lastText + msg);
		debugLB->moveCursor(QTextCursor::End);
	}
}

void Debug(int id, QString msg)
{	
	QString lastText = Debugs[id]->toPlainText();
	if (lastText.split('\n').count() > 50)
		lastText = "";
	Debugs[id]->setText(lastText + msg);
	Debugs[id]->moveCursor(QTextCursor::End);
}
