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
#include <GcodeProgram.h>

class GcodeProgramManager : public QObject
{
	Q_OBJECT

public:
	GcodeProgramManager();
	~GcodeProgramManager();
	GcodeProgramManager(QWidget* container, QTextEdit* gcodeArea);
	void AddNewProgram();

	QWidget* wgProgramContainer;
	QTextEdit* teGcodeArea;

	GcodeProgram* SelectingProgram = NULL;
	int ProgramCounter = 0;
	std::vector<GcodeProgram*>* ProgramList;

public slots:
	void ChangeSelectingProgram(GcodeProgram* ptr);
};

