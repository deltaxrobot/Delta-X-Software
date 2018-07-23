#include "GcodeProgramManager.h"


GcodeProgramManager::GcodeProgramManager()
{
	ProgramList = new std::vector<GcodeProgram*>();	
}

GcodeProgramManager::GcodeProgramManager(QWidget* container, QTextEdit * gcodeArea) : GcodeProgramManager()
{
	wgProgramContainer = container;
	teGcodeArea = gcodeArea;
}

void GcodeProgramManager::AddNewProgram()
{
	GcodeProgram* newProgram = new GcodeProgram(wgProgramContainer);
	newProgram->SetPosition(10, 10 + 90 * ProgramCounter);
	newProgram->SetName(QString("program ") + QString::number(ProgramCounter + 1));
	newProgram->GcodeData = "PROG " + QString::number(ProgramCounter);
	ProgramList->push_back(newProgram);

	wgProgramContainer->setGeometry(QRect(0, 0, 279, 90 * (ProgramCounter + 1) + 10));

	connect(newProgram, SIGNAL(Selected(GcodeProgram*)), this, SLOT(ChangeSelectingProgram(GcodeProgram*)));

	ProgramCounter++;
}

void GcodeProgramManager::ChangeSelectingProgram(GcodeProgram * ptr)
{
	if (SelectingProgram != NULL)
	{
		SelectingProgram->SetColor(DEFAULT_COLOR);
	}

	SelectingProgram = ptr;

	teGcodeArea->setText(SelectingProgram->GcodeData);
}


GcodeProgramManager::~GcodeProgramManager()
{
	for (int i = 0; i < ProgramCounter; i++)
	{
		delete ProgramList->at(i);
	}

	ProgramList->clear();

	delete ProgramList;
}
