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

namespace UnityTool
{
    void UpdateVarToModel(QStandardItem *parent, QString fullKey, QVariant value)
    {
        QStringList parts = fullKey.split('.');
        QString valueString = value.toString();
        if (value.canConvert<QVector3D>())
        {
            QVector3D vector = value.value<QVector3D>();
            valueString = QString("(%1, %2, %3)")
                    .arg(vector.x())
                    .arg(vector.y())
                    .arg(vector.z());
        }
        else if (value.canConvert<QPointF>())
        {
            QPointF point = value.value<QPointF>();
            valueString = QString("(%1, %2)")
                    .arg(point.x())
                    .arg(point.y());
        }
        else if (value.canConvert<QPolygonF>())
        {
            QPolygonF poly = value.value<QPolygonF>();
            valueString = "";
            for (const QPointF &point : poly) {
                valueString += QString("(%1, %2)")
                        .arg(point.x())
                        .arg(point.y());
            }
        }
        else if (value.canConvert<QRectF>())
        {
            QRectF rect = value.value<QRectF>();
            valueString = "";
            valueString += QString("(x:%1, y:%2), (h:%3, w:%4)")
                        .arg(rect.x())
                        .arg(rect.y())
                        .arg(rect.height())
                        .arg(rect.width());

        }
        else if (value.canConvert<QTransform>())
        {
            QTransform transform = value.value<QTransform>();
            valueString = "";
            valueString += QString("(%1, %2, %3, %4, %5, %6)")
                        .arg(transform.m11())
                        .arg(transform.m12())
                        .arg(transform.m13())
                        .arg(transform.m21())
                        .arg(transform.m22())
                        .arg(transform.m23());
        }

        for (int i = 0; i < parts.count() - 1; ++i) {
            QString part = parts[i];
            QStandardItem *child = nullptr;
            for (int j = 0; j < parent->rowCount(); ++j) {
                if (parent->child(j)->text() == part) {
                    child = parent->child(j);
                    break;
                }
            }
            if (!child) {
                child = new QStandardItem(part);
                parent->appendRow(child);
            }
            parent = child;
        }
        bool found = false;
        for (int i = 0; i < parent->rowCount(); ++i) {
            if (parent->child(i)->text() == parts.last()) {
                parent->child(i, 1)->setText(valueString);
                found = true;
                break;
            }
        }
        if (!found) {
            parent->appendRow(QList<QStandardItem*>() << new QStandardItem(parts.last()) << new QStandardItem(valueString));
        }
    }
}


