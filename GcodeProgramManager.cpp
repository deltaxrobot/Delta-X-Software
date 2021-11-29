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

    UpdateSystemVariable("#X", "0");
    UpdateSystemVariable("#Y", "0");
    UpdateSystemVariable("#Z", "0");
    UpdateSystemVariable("#W", "0");
    UpdateSystemVariable("#U", "0");
    UpdateSystemVariable("#V", "0");
    UpdateSystemVariable("#F", "200");
    UpdateSystemVariable("#A", "1200");
    UpdateSystemVariable("#S", "12");
    UpdateSystemVariable("#E", "12");
    UpdateSystemVariable("#ConveyorSpeed", "0");
    UpdateSystemVariable("#ConveyorDirection", "0");

    UpdateSystemVariable("#O0_X", QString::number(NULL_NUMBER));
    UpdateSystemVariable("#O0_Y", QString::number(NULL_NUMBER));
    UpdateSystemVariable("#O0_A", QString::number(NULL_NUMBER));

	connect(deltaConnection, SIGNAL(DeltaResponeGcodeDone()), this, SLOT(TransmitNextGcode()));
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
    QStringList deltaGcodeFiles;

    if (sortMethod == 0)
    {
        deltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Time);
    }
    if (sortMethod == 1)
    {
        deltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Time | QDir::Reversed);
    }
    if (sortMethod == 2)
    {
        deltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Name);
    }
    if (sortMethod == 3)
    {
        deltaGcodeFiles = directory.entryList(QStringList() << "*.dtgc" << "*.DTGC", QDir::Files, QDir::Name | QDir::Reversed);
    }

    ProgramCounter = 0;

    foreach(QString gcodeFile, deltaGcodeFiles)
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

void GcodeProgramManager::ExecuteGcode(QString gcodes, bool isFromGE)
{
	isFromGcodeEditor = isFromGE;

	QList<QString> tempGcodeList = gcodes.split('\n');

	gcodeList.clear();
    if (startingMode == "beginning")
	{
		gcodeOrder = 0;
	}
	else
	{
		gcodeOrder = currentGcodeEditorCursor;
	}

	for (int i = 0; i < tempGcodeList.size(); i++)
	{
		QString line = tempGcodeList.at(i);

        line = DeleteExcessSpace(line);

		gcodeList.push_back(line);
	}

	tempGcodeList.clear();

	TransmitNextGcode();
}

void GcodeProgramManager::Stop()
{	
	gcodeList.clear();
    gcodeOrder = 0;
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

QString GcodeProgramManager::GetVariableValue(QString name)
{	
	if (name == "NULL")
        return QString::number(NULL_NUMBER);

    if (mParent->RobotManagerPointer != NULL)
    {
        if (mParent->RobotManagerPointer->RobotWindows.size() > 0)
        {
            if (mParent != mParent->RobotManagerPointer->RobotWindows.at(0))
            {
                if (isGlobalVariable(name))
                {
                    return mParent->RobotManagerPointer->RobotWindows.at(0)->DeltaGcodeManager->GetVariableValue(name);
                }
            }
        }
    }

    float result = GetResultOfMathFunction(name);
    if (result != NULL_NUMBER)
    {
        return QString::number(result, 'f', 2);
    }

    foreach(GcodeVariable var, GcodeVariables)
	{
        if (var.Name.replace("#", "") == name.replace("#", ""))
		{
			return var.Value;
		}
	}
    return name;
}

float GcodeProgramManager::GetResultOfMathFunction(QString expression)
{
    if (expression == "")
        return NULL_NUMBER;

    if (expression[0] != "#")
        return NULL_NUMBER;

    int p1 = expression.indexOf('(');
    int p2 = expression.lastIndexOf(')');

    if (p1 == -1 && p2 == -1)
        return NULL_NUMBER;



    QString functionName = expression.mid(1, p1 - 1);
    QString value = expression.mid(p1 + 1,  p2 - p1 - 1);
    QStringList values = value.replace(" ", "").split(',');

    if (value.lastIndexOf(',') < value.lastIndexOf(')'))
    {
        values.clear();
        values.append(value);
    }

    for (int i = 0; i < values.size(); i++)
    {
        if (values[i] != "")
        {
            if (values[i][0] == "#")
            {
                values[i] = GetVariableValue(values[i]);
            }
        }
    }

    if (functionName.toLower() == "sin")
    {
        return sin((values[0].toFloat()/180) * M_PI);
    }

    if (functionName.toLower() == "cos")
    {
        return cos((values[0].toFloat()/180) * M_PI);
    }

    if (functionName.toLower() == "abs")
    {
        return abs(values[0].toFloat());
    }

    if (functionName.toLower() == "sqrt")
    {
        return sqrt(values[0].toFloat());
    }

    if (functionName.toLower() == "pow")
    {
        if (values.length() >= 2)
        {
            return pow(values[0].toFloat(), values[1].toFloat());
        }
        else
        {
            return NULL_NUMBER;
        }
    }

    return NULL_NUMBER;
}

bool GcodeProgramManager::isGlobalVariable(QString name)
{
	if (name == NULL)
		return false;

	if (name.length() > 6)
	{
		if (name.indexOf("#GLOBAL") == 0)
			return true;
	}
	
	return false;
}

bool GcodeProgramManager::isConveyorGcode(QString gcode)
{
	QString conveyorGcodes = "M310 M311 M312 M313";
	QString prefix = gcode.mid(0, gcode.indexOf(" "));
	if (conveyorGcodes.indexOf(prefix) > -1)
		return true;
	return false;
}

bool GcodeProgramManager::isSlidingGcode(QString gcode)
{
	QString conveyorGcodes = "M320 M321 M322 M323";
	QString prefix = gcode.mid(0, gcode.indexOf(" "));
	if (conveyorGcodes.indexOf(prefix) > -1)
		return true;
	return false;
}

bool GcodeProgramManager::isMovingGcode(QString gcode)
{
	QString movingGcodes = "G01 G00 G1 G0 G02 G03";
	QString prefix = gcode.mid(0, gcode.indexOf(" "));
	if (movingGcodes.indexOf(prefix) > -1)
		return true;
	return false;
}

bool GcodeProgramManager::findExeGcodeAndTransmit()
{
	if (isFromGcodeEditor == true)
	{
		currentGcodeEditorCursor = gcodeOrder;
		QTextCursor textCursor = pteGcodeArea->textCursor();
		textCursor.movePosition(QTextCursor::Start);
		textCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, currentGcodeEditorCursor);
		pteGcodeArea->setTextCursor(textCursor);
		pteGcodeArea->highlightCurrentLine();
	}

	currentLine = currentLine.replace("  ", " ");

	if (currentLine == "")
	{
		gcodeOrder += 1;
		return false;
	}

	if (currentLine[0] == ';')
	{
		gcodeOrder += 1;
		return false;
	}

	//-----------------------------------
	int openBracIndex = currentLine.indexOf('[');
	QString expressInBracket = "";
    QString resultInBracket;
	int subBracNum = 0;

	// ------------- Conlapse Gcode Line by calculating all expression in [ ... ] ---------------

	while (openBracIndex > -1)
	{
		/*int thenIndex = currentLine.indexOf("THEN");

		if (thenIndex < -1)
			thenIndex = currentLine.length();*/

		for (int i = openBracIndex; i < currentLine.length(); i++)
		{
			expressInBracket += currentLine[i];

			if (currentLine[i] == '[')
			{
				subBracNum++;
			}

			if (currentLine[i] == ']')
			{
				subBracNum--;				
			}

			if (subBracNum == 0)
				break;
		}

		resultInBracket = calculateExpressions(expressInBracket);				

        currentLine.replace(expressInBracket, resultInBracket);

		expressInBracket = "";

		openBracIndex = currentLine.indexOf('[');
	}

	//-------------- Find programing statement ------------------------

	QList<QString> valuePairs = currentLine.split(' ');
	QString transmitGcode = currentLine;

	for (int i = 0; i < valuePairs.size(); i++)
	{
		if (valuePairs[i] == "")
			continue;
		//------------ GOTO -----------

		if (valuePairs[i] == "GOTO" && valuePairs.size() > (i + 1))
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
							gcodeOrder = order;
							//TransmitNextGcode();
							return false;
						}
					}
				}
			}
		}

		// --------------- IF ---------------------
		if (valuePairs[i] == "IF" && valuePairs.size() > (i + 3))
		{
			if (valuePairs[i + 2] == "THEN")
			{
				QString statement = currentLine.mid(currentLine.indexOf("THEN") + 5);

				bool result = false;

				if (valuePairs[i + 1] == "1")
				{
					result = true;
				}

				if (result == true)
				{
					transmitGcode = statement;
					currentLine = transmitGcode;
					return findExeGcodeAndTransmit();		 
				}
				else
				{
					gcodeOrder++;
					//TransmitNextGcode();
					return false;
				}
			}
		}

		//------------ VARIABLE ------------

		// #100 = 2 
		// #100 = #100 + 2 
		// #100 = #101 - #102

		if (valuePairs[i].at(0) == '#' && valuePairs.size() > (i + 2))
		{
			if (valuePairs[i + 1] == "=")
			{
				QString varName = valuePairs[i];
				QString expression = currentLine.mid(currentLine.indexOf("=") + 2);
				GcodeVariable newVar;

				newVar.Name = varName;
				newVar.Value = calculateExpressions(expression);

				SaveGcodeVariable(newVar);

				if (GetVariableValue("#O1_X") == NULL_NUMBER && GetVariableValue("#O1_Y") == NULL_NUMBER && GetVariableValue("#O1_A") == NULL_NUMBER)
				{
					emit OutOfObjectVariable();
				}

				gcodeOrder++;
				return false;
			}

		}
		
		// --------------- WHILE ------------------

		// --------------- DEFINE SUBPROGRAM ------

		// N15 O2000
		// ....
		// N45 M99

		if (valuePairs[i].at(0) == 'O')
		{
			/*QString subProName = valuePairs[i].mid(1);

			bool isNumber;
			int subProID;

			subProID = subProName.toInt(&isNumber, 10);

			if (isNumber == true)
			{*/
				for (int order = gcodeOrder + 1; order < gcodeList.size(); order++)
				{
					if (gcodeList[order].indexOf("M99") > -1)
					{
						gcodeOrder = order + 1;
						//TransmitNextGcode();
						return false;
					}	
				}
			/*}*/
		}

		// --------------- CALL SUBPROGRAM --------

		// N50 M98 P2000
		
		if (valuePairs[i] == "M98" && valuePairs.size() > (i + 1))
		{
			if (valuePairs[i + 1].at(0) == 'P')
			{
				QString subProName = valuePairs[i + 1].mid(1);

				if (subProName == "clearObjects")
				{
					emit DeleteAllObjects();
					gcodeOrder++;
					return false;
				}

				if (subProName == "deleteFirstObject")
				{
					emit DeleteObject1();
					gcodeOrder++;
					return false;
				}

				if (subProName == "pauseCamera")
				{
					emit PauseCamera();
					gcodeOrder++;
					return false;
				}

				if (subProName == "captureCamera")
				{
					emit CaptureCamera();
					gcodeOrder++;
					return false;
				}

				if (subProName == "resumeCamera")
				{
					emit ResumeCamera();
					gcodeOrder++;
					return false;
				}

                if (subProName == "syncConveyor")
                {
                    IsConveyorSync = true;
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "stopSyncConveyor")
                {
                    IsConveyorSync = false;
                    gcodeOrder++;
                    return false;
                }

                QString funcName = "sendExternalMCU";

                if (subProName.contains(funcName) == true)
                {
                    int pos1 = subProName.indexOf("\"") + 1;
                    int pos2 = subProName.lastIndexOf("\"");
                    QString msg = subProName.mid(pos1, pos2 - pos1);

                    deltaConnection->ExternalMCUSend(msg);

                    gcodeOrder++;
                    return false;
                }

				for (int order = 0; order < gcodeList.size(); order++)
				{
					if (gcodeList[order].indexOf(QString("O") + subProName) > -1)
					{
						returnPointerOrder++;
						returnSubProPointer[returnPointerOrder] = gcodeOrder;

						gcodeOrder = order + 1;

						//TransmitNextGcode();

						return false;
					}
				}
			}

			if (valuePairs[i + 1].at(0) == 'F')
			{
				QString subProName = valuePairs[i + 1].mid(1);

				for (int i = 0; i < ProgramList->size(); i++)
				{
					if (ProgramList->at(i)->GetName() == subProName)
					{
						disconnect(deltaConnection, SIGNAL(DeltaResponeGcodeDone()), this, SLOT(TransmitNextGcode()));

						InsideGcodeProgramManager = new GcodeProgramManager(mParent, saProgramFilesScrollArea, wgProgramContainer, pteGcodeArea, pbExecuteGcodes, deltaConnection, deltaParameter);

						connect(InsideGcodeProgramManager, SIGNAL(FinishExecuteGcodes()), this, SLOT(TransmitNextGcode()));
						InsideGcodeProgramManager->IsFromOtherGcodeProgram = true;
						InsideGcodeProgramManager->OutsideGcodeProgramManager = this;
						isFileProgramRunning = true;
						
						QString exeGcodes = ProgramList->at(i)->GcodeData;

						pteGcodeArea->setText(exeGcodes);

						InsideGcodeProgramManager->ExecuteGcode(exeGcodes, true);

						gcodeOrder++;
						return true;
					}
				}
			}
		}

		if (valuePairs[i] == "M99")
		{
			gcodeOrder = returnSubProPointer[returnPointerOrder] + 1;
			returnPointerOrder--;
			//TransmitNextGcode();
			return false;
		}

		if (isConveyorGcode(transmitGcode))
		{
			gcodeOrder++;
			deltaConnection->ConveyorSend(transmitGcode);
			return true;
		}

		if (isSlidingGcode(transmitGcode))
		{
			gcodeOrder++;
			deltaConnection->SlidingSend(transmitGcode);
			return true;
		}
		/*if (deltaConnection->IsConnect() == false && !isMovingGcode(transmitGcode))
		{
			gcodeOrder++;
			return false;
		}*/
	}

    transmitGcode = convertGcodeToSyncConveyor(transmitGcode);

	updatePositionIntoSystemVariable(transmitGcode);

	deltaConnection->SendToRobot(transmitGcode);
	gcodeOrder += 1;
	return true;
}


void GcodeProgramManager::SaveGcodeIntoFile()
{
    SaveGcodeIntoFile(selectingProgram);
}

void GcodeProgramManager::SaveGcodeIntoFile(GcodeProgram *program)
{
    Debug("Save");
    if (program == NULL)
    {
        Debug("No program is selected !");
        return;
    }

    QString fullFileName = getTrueProgramPath() + "/" + program->GetName() + ".dtgc";
    fullFileName = fullFileName.replace("//", "/");

    QFile file(fullFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        Debug("Cant not open file to save !");
        return;
    }

    QTextStream out(&file);
    out << pteGcodeArea->toPlainText();

    program->GcodeData = pteGcodeArea->toPlainText();
    program->CoutingGcodeLines();

    Debug("Saved");
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

void GcodeProgramManager::TransmitNextGcode()
{
	if (gcodeList.empty())
		return;

	if (gcodeOrder >= gcodeList.size())
	{
		if (pbExecuteGcodes->isChecked() == true)
			pbExecuteGcodes->click();
		return;
	}		

	while (true)
	{
		currentLine = gcodeList.at(gcodeOrder);
		QString firstPair = currentLine.split(' ')[0];

		if (firstPair[0] == 'N')
		{
			QString line = currentLine;
			currentLine = line.replace(firstPair + " ", "");
		}

		bool isGcode = findExeGcodeAndTransmit();

		if (gcodeOrder == gcodeList.size())
		{
			//timer->stop();
			gcodeOrder = 0;
			gcodeList.clear();

			if (IsFromOtherGcodeProgram == true)
			{
				pteGcodeArea->setText(OutsideGcodeProgramManager->selectingProgram->GcodeData);
				emit FinishExecuteGcodes();
				connect(deltaConnection, SIGNAL(DeltaResponeGcodeDone()), OutsideGcodeProgramManager, SLOT(TransmitNextGcode()));
			}
			else
			{
				if (pbExecuteGcodes->isChecked() == true)
					pbExecuteGcodes->click();
			}			

			break;
		}

		if (isGcode == true)
		{
			break;
		}
	}
	//Debug(currentLine);
}

void GcodeProgramManager::UpdateSystemVariable(QString name, QString value)
{
	SaveGcodeVariable(name, value);
    emit JustUpdateVariable();
}

void GcodeProgramManager::RespondVariableValue(QIODevice* s, QString name)
{
    QString value = GetVariableValue(name) + '\n';

	s->write(value.toStdString().c_str(), value.size());
}

void GcodeProgramManager::SetStartingGcodeEditorCursor(QString value)
{
	startingMode = value;
}


QString GcodeProgramManager::calculateExpressions(QString expression)
{
	expression = expression.replace("  ", " ");
	
	while (1)
	{
		int openIndex = expression.lastIndexOf('[');

		int multiplyIndex = expression.indexOf('*');
		int divideIndex = expression.indexOf('/');
		int moduloIndex = expression.indexOf('%');
		int plusIndex = expression.indexOf('+');
		int subIndex = expression.indexOf("- ");

		int andIndex = expression.indexOf("AND");
		int orIndex = expression.indexOf("OR");
		int xorIndex = expression.indexOf("XOR");

		int eqIndex = expression.indexOf("EQ");
		int neIndex = expression.indexOf("NE");
		int ltIndex = expression.indexOf("LT");
		int leIndex = expression.indexOf("LE");
		int gtIndex = expression.indexOf("GT");
		int geIndex = expression.indexOf("GE");

		if (eqIndex == -1)
		{
			eqIndex = expression.indexOf("==");
		}
		if (neIndex == -1)
		{
			neIndex = expression.indexOf("!=");
		}
		if (ltIndex == -1)
		{
			ltIndex = expression.indexOf("<");
		}
		if (leIndex == -1)
		{
			leIndex = expression.indexOf("<=");
		}
		if (gtIndex == -1)
		{
			gtIndex = expression.indexOf(">");
		}
		if (geIndex == -1)
		{
			geIndex = expression.indexOf(">=");
		}

		if (openIndex > -1)
		{
			int closeIndex = expression.indexOf(']', openIndex);
			QString subExpression = expression.mid(openIndex + 1, closeIndex - openIndex -1);
            QString result = calculateExpressions(subExpression);

			subExpression = QString("[") + subExpression + "]";

            expression.replace(subExpression, result);
			 
			continue;
		}
		else if ((multiplyIndex > -1 || divideIndex > -1 || moduloIndex > -1 || plusIndex > -1 || subIndex > -1 || andIndex > -1 || orIndex > -1 || xorIndex > -1) && isNotNegative(expression))
		{
			// 3 + 2 * 5 - 4 / 2			

			int operaIndex = subIndex;

			operaIndex = (plusIndex > -1) ? plusIndex : operaIndex;
			operaIndex = (andIndex > -1) ? andIndex : operaIndex;
			operaIndex = (orIndex > -1) ? orIndex : operaIndex;
			operaIndex = (xorIndex > -1) ? xorIndex : operaIndex;
			operaIndex = (multiplyIndex > -1) ? multiplyIndex : operaIndex;
			operaIndex = (divideIndex > -1) ? divideIndex : operaIndex;
			operaIndex = (moduloIndex > -1) ? moduloIndex : operaIndex;

			QString value1S = getLeftWord(expression, operaIndex);
			QString value2S = getRightWord(expression, operaIndex);

            float value1 = GetVariableValue(value1S).toFloat();
            float value2 = GetVariableValue(value2S).toFloat();

			float result = value1 - value2;
			QString resultS = QString::number(result);

			QString operaExpression = value1S + " - " + value2S;

			if (multiplyIndex > -1)
			{
				result = value1 * value2;
				resultS = QString::number(result);

				operaExpression = value1S + " * " + value2S;
			}
			else if (divideIndex > -1)
			{
				if (value2 != 0)
					result = value1 / value2;
				else
					result = 0;
				resultS = QString::number(result);

				operaExpression = value1S + " / " + value2S;
			}
			else if (moduloIndex > -1)
			{
				if (value2 != 0)
					result = (int)value1 % (int)value2;
				else
					result = 0;
				resultS = QString::number(result);

				operaExpression = value1S + " % " + value2S;
			}
			else if (plusIndex > -1)
			{
				result = value1 + value2;
				resultS = QString::number(result);

				operaExpression = value1S + " + " + value2S;
			}
			else if (andIndex > -1)
			{
				result = value1 * value2;
				result = (result > 0) ? 1 : 0;
				resultS = QString::number(result);

				operaExpression = value1S + " AND " + value2S;
			}
			else if (orIndex > -1)
			{
				result = value1 + value2;
				result = (result > 0) ? 1 : 0;
				resultS = QString::number(result);

				operaExpression = value1S + " OR " + value2S;
			}

			if (xorIndex > -1)
			{
				value1 = (value1 > 0) ? 1 : 0;
				value2 = (value2 > 0) ? 1 : 0;
				result = (value1 != value2) ? 1 : 0;

				resultS = QString::number(result);

				operaExpression = value1S + " XOR " + value2S;
			}
			
			expression.replace(operaExpression, QString::number(result));

			continue;
		}

		else if (eqIndex > -1 || ltIndex > -1 || gtIndex > -1 || neIndex > -1 || leIndex > -1 || geIndex > -1)
		{
			QString value1S;
			QString opeS;
			QString value2S;

			float value1;
            float value2;

			int operatorIndex = eqIndex;

			operatorIndex = (neIndex > -1) ? neIndex : operatorIndex;
			operatorIndex = (ltIndex > -1) ? ltIndex : operatorIndex;
			operatorIndex = (leIndex > -1) ? leIndex : operatorIndex;
			operatorIndex = (gtIndex > -1) ? gtIndex : operatorIndex;
			operatorIndex = (geIndex > -1) ? geIndex : operatorIndex;

			value1S = getLeftWord(expression, operatorIndex);
			value2S = getRightWord(expression, operatorIndex);

            value1 = GetVariableValue(value1S).toFloat();
			
            value2 = GetVariableValue(value2S).toFloat();
			
			int returnValue = -1;

			returnValue = (eqIndex > -1) ? ((value1 == value2) ? 1 : 0 ) : returnValue;
			returnValue = (neIndex > -1) ? ((value1 != value2) ? 1 : 0) : returnValue;
			returnValue = (ltIndex > -1) ? ((value1 < value2) ? 1 : 0) : returnValue;
			returnValue = (leIndex > -1) ? ((value1 <= value2) ? 1 : 0) : returnValue;
			returnValue = (gtIndex > -1) ? ((value1 > value2) ? 1 : 0) : returnValue;
			returnValue = (geIndex > -1) ? ((value1 >= value2) ? 1 : 0) : returnValue;

			if (returnValue != -1)
                return QString::number(returnValue);
		}

		else
		{

            float value = GetVariableValue(deleteSpaces(expression)).toFloat();

			if (deleteSpaces(expression) == "NULL")
			{
				value = NULL_NUMBER;
			}

            return QString::number(value);
		}

        return expression;
	}
}

void GcodeProgramManager::SaveGcodeVariable(GcodeVariable gvar)
{
    gvar.Name = gvar.Name.replace("#", "");
    if (mParent->RobotManagerPointer != NULL)
    {

        if (mParent->RobotManagerPointer->RobotWindows.size() > 0)
        {
            if (mParent != mParent->RobotManagerPointer->RobotWindows.at(0))
            {
                if (isGlobalVariable(gvar.Name))
                {
                    mParent->RobotManagerPointer->RobotWindows.at(0)->DeltaGcodeManager->SaveGcodeVariable(gvar);
                    return;
                }
            }
        }
    }

    QString projectName = SoftwareManager::GetInstance()->SoftwareProjectManager->GetProjectName(mParent->SubWindowStackedWidget);
    QString robotName = mParent->Name;
    QString fullName = projectName + "." + robotName + "." + gvar.Name;
    fullName = fullName.replace(" ", "");
    SoftwareManager::GetInstance()->ProgramVariableManager->AddVariable(fullName, gvar.Value);

	bool isNewVar = true;

    for (int i = 0; i < GcodeVariables.length(); i++)
	{
        if (GcodeVariables[i].Name == gvar.Name)
		{
            GcodeVariables[i].Value = gvar.Value;
			isNewVar = false;
		}
	}

	if (isNewVar == true)
        GcodeVariables.push_back(gvar);
}

void GcodeProgramManager::SaveGcodeVariable(QString name, QString value)
{
	GcodeVariable gvar;
	gvar.Name = name;
	gvar.Value = value;
    SaveGcodeVariable(gvar);
}

void GcodeProgramManager::SaveGcodeVariable(QString cmd)
{
    if (cmd == "")
        return;

    QStringList vars = cmd.split(';');

    foreach(QString var, vars)
    {
        var = var.replace(" ", "");
        QStringList paras = var.split('=');
        if (paras.count() < 2)
            return;

        SaveGcodeVariable(GcodeVariable(paras[0], paras[1]));
    }
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

void GcodeProgramManager::updatePositionIntoSystemVariable(QString statement)
{
	QList<QString> pairs = statement.split(' ');

    float x, y, z, w, u, v, f, a, s, e;

    x = GetVariableValue("#X").toFloat();
    y = GetVariableValue("#Y").toFloat();
    z = GetVariableValue("#Z").toFloat();
    w = GetVariableValue("#W").toFloat();
    u = GetVariableValue("#U").toFloat();
    v = GetVariableValue("#V").toFloat();
    f = GetVariableValue("#F").toFloat();
    a = GetVariableValue("#A").toFloat();
    s = GetVariableValue("#S").toFloat();
    e = GetVariableValue("#E").toFloat();

	if (statement == "G28")
	{
		UpdateSystemVariable("#X", 0);
		UpdateSystemVariable("#Y", 0);
		UpdateSystemVariable("#Z", 0);
		UpdateSystemVariable("#W", 0);
        UpdateSystemVariable("#U", 0);
        UpdateSystemVariable("#V", 0);

        emit MoveToNewPosition(0, 0, 0, 0, 0, 0, f, a, s, e);
		return;
	}

    foreach (QString pair, pairs)
	{
		QChar prefix = pair[0];
		QString value = pair.mid(1);

		if (pair[0] == 'X')
		{
			x = value.toFloat();
            UpdateSystemVariable("#X", value);
		}
		else if (pair[0] == 'Y')
		{
			y = value.toFloat();
            UpdateSystemVariable("#Y", value);
		}
		else if (pair[0] == 'Z')
		{
			z = value.toFloat();
            UpdateSystemVariable("#Z", value);
		}
		else if (pair[0] == 'W')
		{
			w = value.toFloat();
            UpdateSystemVariable("#W", value);
		}
        else if (pair[0] == 'U')
        {
            u = value.toFloat();
            UpdateSystemVariable("#U", value);
        }
        else if (pair[0] == 'V')
        {
            v = value.toFloat();
            UpdateSystemVariable("#V", value);
        }
		else if (pair[0] == 'F')
		{
			f = value.toFloat();
            UpdateSystemVariable("#F", value);
		}
		else if (pair[0] == 'A')
		{
			a = value.toFloat();
            UpdateSystemVariable("#A", value);
		}
        else if (pair[0] == 'S')
        {
            s = value.toFloat();
            UpdateSystemVariable("#S", value);
        }
        else if (pair[0] == 'E')
        {
            e = value.toFloat();
            UpdateSystemVariable("#E", value);
        }
	}

    emit MoveToNewPosition(x, y, z, w, u, v, f, a, s, e);
}

QString GcodeProgramManager::getLeftWord(QString s, int pos)
{
	if (pos < 0)
		return "0";

	if (pos > s.length() - 1)
		return "0";

	QString word;

	while (1)
	{
		if (s[pos] != ' ')
		{
			pos--;
			if (pos < 0)
			{
				return "0";
			}
		}
		else
		{
			break;
		}
	}

	for (int index = pos; index >= 0; index--)
	{
		if (s[index] != ' ')
		{
			word.insert(0, s[index]);
		}
		else if (word.length() > 0)
		{
			break;
		}
	}

	return word;
}

QString GcodeProgramManager::getRightWord(QString s, int pos)
{
	if (pos < 0)
		return "0";

	if (pos > s.length() - 1)
		return "0";

	QString word;

	while (1)
	{
		if (s[pos] != ' ')
		{
			pos++;
			if (pos == s.length())
			{
				return "0";
			}
		}
		else
		{
			break;
		}
	}

	for (int index = pos + 1; index < s.length(); index++)
	{
		if (s[index] != ' ')
		{
			word += s[index];
		}
		else if (word.length() > 0)
		{
			break;
		}
	}

	return word;
}

QString GcodeProgramManager::deleteSpaces(QString s)
{
	while (s.indexOf(' ') > -1)
	{
		s.replace(" ", "");
	}
	return s;
}

bool GcodeProgramManager::isNotNegative(QString s)
{
	bool isNumeric = false;
	s.toDouble(&isNumeric);
									 
    return !isNumeric;
}

QString GcodeProgramManager::convertGcodeToSyncConveyor(QString gcode)
{
    if (IsConveyorSync == false)
        return gcode;

    if (!(gcode.indexOf("G01 ") > -1 || gcode.indexOf("G1 ") > -1 || gcode.indexOf("G0 ") > -1 || gcode.indexOf("G00 ") > -1 || gcode.indexOf("G04 ") > -1 || gcode.indexOf("G4 ") > -1))
        return gcode;

    float velocity = GetVariableValue("F").toFloat();
    float accel = GetVariableValue("A").toFloat();
    float startSpeed = GetVariableValue("S").toFloat();
    float endSpeed = GetVariableValue("E").toFloat();
    float conveyorSpeed = GetVariableValue("ConveyorSpeed").toFloat();

    if (conveyorSpeed == 0)
        return gcode;

    QString conveyorDirection = (GetVariableValue("ConveyorDirection").toFloat() == 0) ? "X":"Y";
    
    float currentX = GetVariableValue("X").toFloat();
    float currentY = GetVariableValue("Y").toFloat();
    float currentZ = GetVariableValue("Z").toFloat();
    
    float time = 1;

    float desireX = currentX;
    float desireY = currentY;
    float desireZ = currentZ;

    float xy = 0;
    float xyz = 0;
    
    QString newGcode = "";
    
    if (gcode.indexOf("G01 ") > -1 || gcode.indexOf("G1 ") > -1 || gcode.indexOf("G0 ") > -1 || gcode.indexOf("G00 ") > -1)
    {
        QStringList paras = gcode.split(' ');
        
        for(int i = 0; i < paras.size(); i++)
        {
            if (paras[i][0] == 'X')
            {
                desireX = paras[i].mid(1).toFloat();
            }
            if (paras[i][0] == 'Y')
            {
                desireY = paras[i].mid(1).toFloat();
            }
            if (paras[i][0] == 'Z')
            {
                desireZ = paras[i].mid(1).toFloat();
            }
            if (paras[i][0] == 'F')
            {
                velocity = paras[i].mid(1).toFloat();
            }
            if (paras[i][0] == 'A')
            {
                accel = paras[i].mid(1).toFloat();
            }
            if (paras[i][0] == 'S')
            {
                startSpeed = paras[i].mid(1).toFloat();
            }
            if (paras[i][0] == 'E')
            {
                endSpeed = paras[i].mid(1).toFloat();
            }
        }        

        DeltaXSMoving.setMaxAcc(accel);
        DeltaXSMoving.setVelEnd(endSpeed);
        DeltaXSMoving.setVelStart(startSpeed);
        DeltaXSMoving.setMaxVel(velocity);
        
        float distanceConveyor = 0;
        float distanceRobot = 0;
        float increaseValue = conveyorSpeed / abs(conveyorSpeed);



        while (abs(distanceConveyor) < 2000)
        {
            xy = qSqrt(qPow(desireX - currentX, 2) + qPow(desireY - currentY, 2));
            xyz = qSqrt(qPow(xy, 2) + qPow(desireZ - currentZ, 2));

            distanceConveyor += increaseValue;

            // S2 = S1^2 - 2.S.S1.cos(alpha) + S^2
            float alpha = atan(abs(desireY - currentY) / abs(desireX - currentX));
            distanceRobot = sqrt(pow(distanceConveyor, 2) - 2 * xyz * distanceConveyor * cos(alpha) + pow(xyz, 2));

            time = distanceConveyor / abs(conveyorSpeed);

            DeltaXSMoving.setTarget(distanceRobot);

            DeltaXSMoving.start();

            if ((time) > (DeltaXSMoving.t_target + 0.005))
            {
                break;
            }
        }
        
        if (conveyorDirection == "X")
        {
            desireX += distanceConveyor;
        }
        if (conveyorDirection == "Y")
        {
            desireY += distanceConveyor;
        }

        for(int i = 0; i < paras.size(); i++)
        {
            if (paras[i][0] == 'X')
            {
                paras[i] = QString("X%1").arg(desireX);
            }
            if (paras[i][0] == 'Y')
            {
                paras[i] = QString("Y%1").arg(desireY);
            }
            if (paras[i][0] == 'Z')
            {
                paras[i] = QString("Z%1").arg(desireZ);
            }

            newGcode += paras[i] + " ";
        }

        if (newGcode.indexOf('X') == -1)
        {
            newGcode += QString(" X%1").arg(desireX);;
        }

        if (newGcode.indexOf('Y') == -1)
        {
            newGcode += QString(" Y%1").arg(desireY);;
        }
        
        //newGcode = QString("G01 X%1 Y%2 Z%3 F%4 A%5 S%6 E%7").arg(desireX).arg(desireY).arg(desireZ).arg(velocity).arg(accel).arg(startSpeed).arg(endSpeed);
    }

    if (gcode.indexOf("G04 ") > -1 || gcode.indexOf("G4 ") > -1)
    {
        QStringList paras = gcode.split(' ');

        for(int i = 0; i < paras.size(); i++)
        {
            if (paras[i][0] == 'P')
            {
                time = paras[i].mid(1).toFloat() / 1000;
            }
        }

        float distanceConveyor = time * conveyorSpeed;

        if (conveyorDirection == "X")
        {
            desireX += distanceConveyor;
            newGcode = QString("G01 X%1 F%2").arg(desireX).arg(conveyorSpeed);
        }
        if (conveyorDirection == "Y")
        {
            desireY += distanceConveyor;
            newGcode = QString("G01 Y%1 F%2").arg(desireY).arg(conveyorSpeed);;
        }
    }

    return newGcode;
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

	Debug(QString("#") + QString::number(ptr->ID) + " is selected !");

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
