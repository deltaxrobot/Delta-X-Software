#include "GcodeProgramManager.h"


GcodeProgramManager::GcodeProgramManager()
{
	ProgramList = new QVector<GcodeProgram*>();	
}

GcodeProgramManager::GcodeProgramManager(QWidget* container, QPlainTextEdit * gcodeArea) : GcodeProgramManager()
{
	wgProgramContainer = container;
	pteGcodeArea = gcodeArea;
}

void GcodeProgramManager::AddNewProgram()
{
	GcodeProgram* newProgram = new GcodeProgram(wgProgramContainer);
	newProgram->SetPosition(10, 10 + 90 * ProgramCounter);
	newProgram->SetName(QString("program ") + QString::number(ProgramCounter + 1));
	newProgram->GcodeData = "#" + QString::number(ProgramCounter);
	newProgram->ID = ProgramCounter;
	ProgramList->push_back(newProgram);

	wgProgramContainer->setGeometry(QRect(0, 0, 279, 90 * (ProgramCounter + 1) + 10));

	connect(newProgram, SIGNAL(Selected(GcodeProgram*)), this, SLOT(ChangeSelectingProgram(GcodeProgram*)));
	connect(newProgram, SIGNAL(Deleted(GcodeProgram*)), this, SLOT(DeleteProgram(GcodeProgram*)));

	ProgramCounter++;
}

void GcodeProgramManager::LoadPrograms()
{
	QDir directory(QDir::currentPath());
	QStringList deltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files);

	ProgramCounter = 0;

	foreach(QString gcodeFile, deltaGcodeFiles)
	{
		QFile file(gcodeFile);

		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			continue;
		}

		GcodeProgram* newProgram = new GcodeProgram(wgProgramContainer);

		newProgram->SetPosition(10, 10 + 90 * ProgramCounter);

		QString nameWithExtension = QUrl(gcodeFile).fileName();
		newProgram->SetName(nameWithExtension.left(nameWithExtension.lastIndexOf(".")));
		newProgram->ID = ProgramCounter;
		ProgramList->push_back(newProgram);

		wgProgramContainer->setGeometry(QRect(0, 0, 279, 90 * (ProgramCounter + 1) + 10));
		
		connect(newProgram, SIGNAL(Selected(GcodeProgram*)), this, SLOT(ChangeSelectingProgram(GcodeProgram*)));
		connect(newProgram, SIGNAL(Deleted(GcodeProgram*)), this, SLOT(DeleteProgram(GcodeProgram*)));

		ProgramCounter++;

		QTextStream in(&file);

		while (!in.atEnd())
		{
			QString line = in.readLine();

			newProgram->GcodeData += line + "\n";
		}

		newProgram->CoutingGcodeLines();
	}
}

void GcodeProgramManager::SaveGcodeIntoFile()
{
	Debug("Save");
	if (SelectingProgram == NULL)
	{
		Debug("No program is selected !");
		return;
	}		

	QFile file(SelectingProgram->GetName() + ".dtgc");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Debug("Cant not open file to save !");
		return;
	}
		
	QTextStream out(&file);
	out << pteGcodeArea->toPlainText();

	SelectingProgram->GcodeData = pteGcodeArea->toPlainText();
	SelectingProgram->CoutingGcodeLines();

	Debug("Saved");
}

void GcodeProgramManager::DeleteProgram(GcodeProgram* ptr)
{
	QFile file(ptr->GetName() + ".dtgc");
	file.remove();

	if (ptr == SelectingProgram)
		SelectingProgram = NULL;

	int deleteID = ptr->ID;

	delete ProgramList->at(deleteID);

	ProgramList->remove(deleteID);

	ProgramCounter--;

	for (int i = deleteID; i < ProgramCounter; i++)
	{
		ProgramList->at(i)->ID = i;
		ProgramList->at(i)->SetPosition(10, 10 + 90 * i);
	}

	wgProgramContainer->setGeometry(QRect(0, 0, 279, 90 * ProgramCounter + 10));
}

void GcodeProgramManager::ChangeSelectingProgram(GcodeProgram * ptr)
{
	if (SelectingProgram != NULL)
	{
		SelectingProgram->SetColor(DEFAULT_COLOR);
	}

	Debug(QString("#") + QString::number(ptr->ID) + " is selected !");

	SelectingProgram = ptr;

	pteGcodeArea->setPlainText(SelectingProgram->GcodeData);
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
