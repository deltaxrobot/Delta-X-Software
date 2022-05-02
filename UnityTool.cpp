#include <UnityTool.h>
#include "RobotWindow.h"
#include <qlist.h>
#include <QElapsedTimer>

QTextEdit* DebugLB;
QTextEdit* teSoftwareLog;
QList<QTextEdit*> Debugs;

QString ConveyorString;

QElapsedTimer ElapsedTimer;

QString DeleteExcessSpace(QString text)
{
    if (text.length() == 0)
        return "";

    int b = 0;
    int e = text.length() - 1;

    while(text.at(b) == ' ' && b < text.length() - 1)
    {
        ++b;
    }

    while(text.at(e) == ' ' && e > 1)
    {
        --e;
    }

    if (b == text.length() || e == 0)
    {
        return "";
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

void SoftwareLog(QString msg, bool isNewLine)
{
    if (msg == "")
        return;

    if (teSoftwareLog->document()->blockCount() > 200)
        teSoftwareLog->setText("");

    if (isNewLine == true)
    {
        if (msg[msg.length() - 1] != "\n")
            msg += "\n";
    }

    teSoftwareLog->moveCursor (QTextCursor::End);
    teSoftwareLog->insertPlainText(msg);
    teSoftwareLog->moveCursor(QTextCursor::End);
}

QString GetValueInGcode(QString key, QString gcode)
{
    QStringList pairs = gcode.split(' ');

    foreach(QString pair, pairs)
    {
        if (pair.contains(key))
        {
            return pair.mid(1);
        }
    }

    return "";
}

bool IsInRange(QPolygonF poly)
{
    foreach(QPointF p, poly)
    {
        if (p.x() > 1 || p.y() > 1)
            return false;
    }

    return true;
}
