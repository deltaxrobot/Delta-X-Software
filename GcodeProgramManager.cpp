#include "GcodeProgramManager.h"

GcodeProgramManager::GcodeProgramManager(RobotWindow *parent)
{
	ProgramList = new QVector<GcodeProgram*>();
	mParent = parent;
}

GcodeProgramManager::GcodeProgramManager(RobotWindow *parent, QScrollArea* scrolArea, QWidget* container, CodeEditor * gcodeArea, QPushButton* executeButton, ConnectionManager* deltaPort, DeltaVisualizer* deltaVisualize) : GcodeProgramManager(parent)
{
    mParent = parent;

	saProgramFilesScrollArea = scrolArea;
	wgProgramContainer = container;
	pteGcodeArea = gcodeArea;
	deltaConnection = deltaPort;
	deltaParameter = deltaVisualize;
    pbExecuteGcodes = executeButton;

}

void GcodeProgramManager::AddGcodeLine(QString line)
{
	QString text = pteGcodeArea->toPlainText();
	QTextCursor curPos = pteGcodeArea->textCursor();
	int pos = curPos.position();
	int i = 0;

	for (i = pos; i > (pos - 500) && i > -1; i--)
	{
        if (text.at(i) == '\n')
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

void GcodeProgramManager::AddG01(float  x, float y, float z)
{
	QString g01 = QString("G01 X") + QString::number(x) + " Y" + QString::number(y) + " Z" + QString::number(z);
	
	AddGcodeLine(g01);
}

void GcodeProgramManager::AddG28()
{
	QString g28 =  "G28";
	AddGcodeLine(g28);
}

void GcodeProgramManager::AddM204(float accel)
{
	QString m204 = QString("M204 A") + QString::number(accel);
	AddGcodeLine(m204);
}

GcodeProgram* GcodeProgramManager::AddNewProgram()
{
	for (int i = 0; i < ProgramList->size(); i++)
	{
		ProgramList->at(i)->SetPosition(10, 10 + 90 * (i + 1));
		ProgramList->at(i)->ID = i + 1;
	}

	GcodeProgram* newProgram = new GcodeProgram(wgProgramContainer);
	newProgram->SetPosition(10, 10);
	newProgram->SetName(QString("program ") + QString::number(ProgramCounter + 1));
    newProgram->GcodeData = "G28";
	newProgram->ID = 0;
	ProgramList->push_front(newProgram);

	wgProgramContainer->setGeometry(QRect(0, 0, 279, 90 * (ProgramCounter + 1) + 10));

	connect(newProgram, SIGNAL(Selected(GcodeProgram*)), this, SLOT(ChangeSelectingProgram(GcodeProgram*)));
	connect(newProgram, SIGNAL(Deleted(GcodeProgram*)), this, SLOT(DeleteProgram(GcodeProgram*)));

	ProgramCounter++;


	newProgram->SelectNewProgram();
	saProgramFilesScrollArea->verticalScrollBar()->setValue(0);

    return newProgram;
}

void GcodeProgramManager::LoadPrograms()
{
    QDir dir(getTrueProgramPath());
	
    LoadPrograms(dir);
}

void GcodeProgramManager::LoadPrograms(QDir directory)
{
    if (sortMethod == 0)
    {
        DeltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Time);
    }
    if (sortMethod == 1)
    {
        DeltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Time | QDir::Reversed);
    }
    if (sortMethod == 2)
    {
        DeltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Name);
    }
    if (sortMethod == 3)
    {
        DeltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Name | QDir::Reversed);
    }

    ProgramCounter = 0;

    foreach(QString gcodeFile, DeltaGcodeFiles)
    {
        QFile file(directory.path() + "/" + gcodeFile);

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

void GcodeProgramManager::SaveSettings(QSettings *setting)
{
    setting->setValue("GcodeProgramPath", leGcodeProgramPath->text());
    setting->setValue("Content", pteGcodeArea->toPlainText());

    QString selectingProgramName = "NULL";
    if (selectingProgram != NULL)
        selectingProgramName = selectingProgram->GetName();
    setting->setValue("SelectedProgram", selectingProgramName);
}

void GcodeProgramManager::LoadSettings(QSettings *setting)
{
    if (leGcodeProgramPath != NULL)
    {
        leGcodeProgramPath->setText(setting->value("GcodeProgramPath", leGcodeProgramPath->text()).toString());
    }

    pteGcodeArea->setText(setting->value("Content", pteGcodeArea->toPlainText()).toString());

    EraserAllProgramItems();
    LoadPrograms(QDir(getTrueProgramPath()));

    QString selectedProgramName = setting->value("SelectedProgram").toString();

    if (selectedProgramName != "NULL")
    {
        foreach(GcodeProgram* gp, *ProgramList)
        {
            if (gp->GetName() == selectedProgramName)
            {
                gp->SelectNewProgram();
            }
        }
    }
}

void GcodeProgramManager::SelectProgram(QString name)
{
    if (name != "")
    {
        foreach(GcodeProgram* gp, *ProgramList)
        {
            if (gp->GetName() == name)
            {
                gp->SelectNewProgram();
            }
        }
    }
}

QStringList GcodeProgramManager::GetProgramNames()
{
    return DeltaGcodeFiles;
}

void GcodeProgramManager::SaveGcodeIntoFile()
{
    SaveGcodeIntoFile(selectingProgram);
}

void GcodeProgramManager::SaveGcodeIntoFile(GcodeProgram *program)
{
    SoftwareLog("Save");

    if (program == NULL)
    {
        SoftwareLog("No program is selected !");
        return;
    }

    QString fullFileName = getTrueProgramPath() + "/" + program->GetName() + ".dtgc";
    fullFileName = fullFileName.replace("//", "/");

    QFile file(fullFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        SoftwareLog("Cant not open file to save !");
        return;
    }

    QTextStream out(&file);
    out << pteGcodeArea->toPlainText();

    program->GcodeData = pteGcodeArea->toPlainText();
    program->CoutingGcodeLines();

    SoftwareLog("Saved");
}

void GcodeProgramManager::DeleteProgram(GcodeProgram* ptr)
{
	QFile file(ptr->GetName() + ".dtgc");
	file.remove();

	if (ptr == selectingProgram)
		selectingProgram = NULL;

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

void GcodeProgramManager::EraserAllProgramItems()
{
	selectingProgram = NULL;

	for (int i = 0; i < ProgramList->size(); i++)
	{
		delete ProgramList->at(i);
	}
	ProgramList->clear();
	wgProgramContainer->setGeometry(QRect(0, 0, 279, 10));
}

void GcodeProgramManager::SortProgramFiles()
{
	sortMethod++;
	if (sortMethod == 4)
	{
		sortMethod = 0;
	}

	EraserAllProgramItems();
	LoadPrograms();
}

void GcodeProgramManager::RefreshGcodeProgramList()
{
	EraserAllProgramItems();
	LoadPrograms();
}

void GcodeProgramManager::SelectGcodeProgramPath()
{
    QString path;
    if (leGcodeProgramPath == NULL)
    {
        path = QApplication::applicationDirPath();
    }
    else
    {
        if (QDir(leGcodeProgramPath->text()).exists())
            path = leGcodeProgramPath->text();

        QString path2 = QApplication::applicationDirPath() + "/" + leGcodeProgramPath->text();

        path2 = path2.replace("/", "");
        if (QDir(path2).exists())
            path = path2;
    }

    QString dir = QFileDialog::getExistingDirectory(mParent, tr("Open G-code program directory"),
                                                 path,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if (dir == "")
    {

    }

    if (leGcodeProgramPath != NULL)
    {
        leGcodeProgramPath->setText(dir);
    }

    EraserAllProgramItems();
    LoadPrograms(QDir(dir));
}

QString GcodeProgramManager::getTrueProgramPath()
{
    QString path = "";
    QString softwarePath = QApplication::applicationDirPath();

    if (leGcodeProgramPath == NULL)
    {
        path = softwarePath;
    }
    else
    {
        QString subpath = leGcodeProgramPath->text();

        QDir subDir(subpath);
        QDir fullDir(softwarePath + "/" + subpath);
        if (subDir.exists())
        {
            path = subpath;
        }

        fullDir.mkpath(".");
        path = softwarePath + "/" + subpath;
        path = path.replace("//", "/");
    }

    return path;
}

void GcodeProgramManager::ChangeSelectingProgram(GcodeProgram * ptr)
{
	SaveGcodeIntoFile();

	if (selectingProgram != NULL && ptr != selectingProgram)
	{
		selectingProgram->SetColor(DEFAULT_COLOR);
	}

    SoftwareLog(QString("#") + QString::number(ptr->ID) + " is selected !");

	selectingProgram = ptr;

	pteGcodeArea->setPlainText(selectingProgram->GcodeData);
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
