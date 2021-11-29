#include <UnityTool.h>
#include "RobotWindow.h"
#include <qlist.h>
#include <QElapsedTimer>

QTextEdit* DebugLB;
QList<QTextEdit*> Debugs;

QString ConveyorString;

QElapsedTimer ElapsedTimer;

QString DeleteExcessSpace(QString text)
{
    if (text.length() == 0)
        return "";

    int b = 0;
    int e = text.length() - 1;

    while(text.at(b) == ' ')
    {
        ++b;
    }

    while(text.at(e) == ' ')
    {
        --e;
    }

    text = text.mid(b, e - b + 1);

    return text;
}

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
