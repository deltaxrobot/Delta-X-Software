#include "GcodeProgramManager.h"


GcodeProgramManager::GcodeProgramManager()
{
	ProgramList = new QVector<GcodeProgram*>();
}

GcodeProgramManager::GcodeProgramManager(QWidget* container, QPlainTextEdit * gcodeArea, ConnectionManager* deltaPort) : GcodeProgramManager()
{
	wgProgramContainer = container;
	pteGcodeArea = gcodeArea;
	deltaConnection = deltaPort;

	connect(deltaConnection, SIGNAL(DeltaResponeGcodeDone()), this, SLOT(TransmitGcode()));
}

void GcodeProgramManager::AddGcodeLine(QString line)
{
	QString text = pteGcodeArea->toPlainText();
	QTextCursor curPos = pteGcodeArea->textCursor();
	int pos = curPos.position();
	int i = 0;

	for (i = pos; i > (pos - 500) && i > -1; i--)
	{
		if (text[i] == '\n')
		{
			curPos.setPosition(i + 1);
			break;
		}
	}

	if (i == -1)
		curPos.setPosition(0);

	pteGcodeArea->setTextCursor(curPos);
	pteGcodeArea->insertPlainText(line + "\n");
}

void GcodeProgramManager::AddG01(int  x, int y, int z)
{
	QString g01 = QString("G01 X") + QString::number(x) + " Y" + QString::number(y) + " Z" + QString::number(z);
	
	AddGcodeLine(g01);
}

void GcodeProgramManager::AddG28()
{
	QString g28 =  "G28";
	AddGcodeLine(g28);
}

void GcodeProgramManager::AddM03(int speed)
{
	QString m03 = QString("M03 S") + QString::number(speed);
	AddGcodeLine(m03);
}

void GcodeProgramManager::AddM204(int accel)
{
	QString m204 = QString("M204 A") + QString::number(accel);
	AddGcodeLine(m204);
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

void GcodeProgramManager::ExecuteGcode(QString gcodes)
{
	QList<QString> tempGcodeList = gcodes.split('\n');

	gcodeList.clear();

	for (int i = 0; i < tempGcodeList.size(); i++)
	{
		if (tempGcodeList.at(i) != "")
		{
			gcodeList.push_back(tempGcodeList.at(i));
		}
	}

	tempGcodeList.clear();

	TransmitGcode();
}

int GcodeProgramManager::NextOrder()
{
	QList<QString> valuePairs = gcodeList[gcodeOrder].split(' ');

	for (int i = 0; i < valuePairs.size() - 1; i++)
	{

		//------------ GOTO -----------

		if (valuePairs[i] == "GOTO")
		{
			bool isNumber;
			int goID;

			goID = valuePairs[i + 1].toInt(&isNumber, 10);

			if (isNumber == true)
			{
				for (int order = 0; order < gcodeList.size(); order++)
				{
					QList<QString> pairs = gcodeList[order].split(' ');
					if (pairs[0][0] == 'N')
					{
						int id = pairs[0].mid(1).toInt();

						if (id == goID)
						{
							return order;
						}
					}
				}
			}
		}

		// --------------- IF ---------------------

		// --------------- WHILE ------------------
	}

	gcodeOrder += 1;

	return gcodeOrder;
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

void GcodeProgramManager::TransmitGcode()
{
	if (gcodeList.empty())
		return;

	QString gcodeLine = gcodeList.at(gcodeOrder) + "\n";
	QString firstPair = gcodeLine.split(' ')[0];

	if (firstPair[0] == 'N')
	{
		gcodeLine.replace(firstPair + " ", "");
	}

	deltaConnection->Send(gcodeLine);
	Debug(gcodeLine);

	gcodeOrder = NextOrder();

	if (gcodeOrder == gcodeList.size())
	{
		//timer->stop();
		gcodeOrder = 0;
		gcodeList.clear();
	}
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
