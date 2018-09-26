#pragma once

#include <qwidget.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qscrollarea.h>
#include <qobject.h>
#include <qlistwidget.h>
#include <vector>
#include <qlayout.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qplaintextedit.h>
#include <qurl.h>
#include <qvector.h>
#include <qdir.h>
#include <UnityTool.h>
#include <GcodeProgram.h>
#include <qtimer.h>
#include <ConnectionManager.h>

class GcodeVariable
{
public:
	QString Name;
	int Value;
};

class GcodeProgramManager : public QObject
{
	Q_OBJECT

public:
	GcodeProgramManager();
	~GcodeProgramManager();
	GcodeProgramManager(QWidget* container, QPlainTextEdit* gcodeArea, ConnectionManager* deltaPort = NULL);
	void AddGcodeLine(QString line);
	void AddG01(int  x, int y, int z);
	void AddG28();
	void AddM03(int speed);
	void AddM204(int accel);
	void AddNewProgram();
	void LoadPrograms();
	void ExecuteGcode(QString gcodes);
	void Stop();

	QWidget* wgProgramContainer;
	QPlainTextEdit* pteGcodeArea;

	GcodeProgram* SelectingProgram = NULL;
	int ProgramCounter = 0;
	QVector<GcodeProgram*>* ProgramList;

	QList<QString> gcodeList;
	int gcodeOrder = 0;

	public slots:
	void ChangeSelectingProgram(GcodeProgram* ptr);
	void SaveGcodeIntoFile();
	void DeleteProgram(GcodeProgram* ptr);
	void TransmitNextGcode();

private:
	ConnectionManager* deltaConnection;
	QList<GcodeVariable> gcodeVariables;
	QString currentLine;

	void findExeGcodeAndTransmit();
	int calculateExpressions(QString expression);
	QString getLeftWord(QString s, int pos);
	QString getRightWord(QString s, int pos);
	QString deleteSpaces(QString s);
	bool isNotNegative(QString s);
};

