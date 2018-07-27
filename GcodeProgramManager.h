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
#include <qdir>
#include <qurl.h>
#include <qvector.h>
#include <UnityTool.h>
#include <GcodeProgram.h>

class GcodeProgramManager : public QObject
{
	Q_OBJECT

public:
	GcodeProgramManager();
	~GcodeProgramManager();
	GcodeProgramManager(QWidget* container, QPlainTextEdit* gcodeArea);
	void AddNewProgram();
	void LoadPrograms();

	QWidget* wgProgramContainer;
	QPlainTextEdit* pteGcodeArea;

	GcodeProgram* SelectingProgram = NULL;
	int ProgramCounter = 0;
	QVector<GcodeProgram*>* ProgramList;

public slots:
	void ChangeSelectingProgram(GcodeProgram* ptr);
	void SaveGcodeIntoFile();
	void DeleteProgram(GcodeProgram* ptr);
};

