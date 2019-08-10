#include "GcodeProgramManager.h"


GcodeProgramManager::GcodeProgramManager()
{
	ProgramList = new QVector<GcodeProgram*>();
}

GcodeProgramManager::GcodeProgramManager(QWidget* container, CodeEditor * gcodeArea, ConnectionManager* deltaPort, DeltaVisualizer* deltaVisualize) : GcodeProgramManager()
{
	wgProgramContainer = container;
	pteGcodeArea = gcodeArea;
	deltaConnection = deltaPort;
	deltaParameter = deltaVisualize;

	UpdateSystemVariable("#1001", -1000);
	UpdateSystemVariable("#1002", -1000);
	UpdateSystemVariable("#1003", -1000);

	UpdateSystemVariable("#1010", NULL_NUMBER);
	UpdateSystemVariable("#1011", NULL_NUMBER);
	UpdateSystemVariable("#1012", NULL_NUMBER);

	UpdateSystemVariable("#X", 0);
	UpdateSystemVariable("#Y", 0);
	UpdateSystemVariable("#Z", 0);
	UpdateSystemVariable("#W", 0);
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
	if (startingMode == "Begin")
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

float GcodeProgramManager::GetVariableValue(QString name)
{
	foreach(GcodeVariable var, gcodeVariables)
	{
		if (var.Name == name)
		{
			return var.Value;
		}
	}
}

bool GcodeProgramManager::findExeGcodeAndTransmit()
{
	currentGcodeEditorCursor = gcodeOrder;
	QTextCursor textCursor = pteGcodeArea->textCursor();
	textCursor.movePosition(QTextCursor::Start);
	textCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, currentGcodeEditorCursor);
	pteGcodeArea->setTextCursor(textCursor);
	pteGcodeArea->highlightCurrentLine();

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
	float resultInBracket;
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

		currentLine.replace(expressInBracket, QString::number(resultInBracket));

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

				if (GetVariableValue("#1010") == NULL_NUMBER && GetVariableValue("#1011") == NULL_NUMBER && GetVariableValue("#1012") == NULL_NUMBER)
				{
					emit OutOfObjectVariable();
				}

				gcodeOrder++;
				//TransmitNextGcode();
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
		}

		if (valuePairs[i] == "M99")
		{
			gcodeOrder = returnSubProPointer[returnPointerOrder] + 1;
			returnPointerOrder--;
			//TransmitNextGcode();
			return false;
		}
	}

	updatePositionIntoSystemVariable(transmitGcode);

	deltaConnection->Send(transmitGcode);
	gcodeOrder += 1;
	return true;
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

void GcodeProgramManager::TransmitNextGcode()
{
	if (gcodeList.empty())
		return;

	if (gcodeOrder >= gcodeList.size())
		return;

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
			break;
		}

		if (isGcode == true)
		{
			break;
		}
	}
	//Debug(currentLine);
}

void GcodeProgramManager::UpdateSystemVariable(QString name, float value)
{
	for (int i = 0; i < gcodeVariables.size(); i++)
	{
		if (name == gcodeVariables[i].Name)
		{
			gcodeVariables[i].Value = value;
			emit JustUpdateVariable(gcodeVariables);
			return;
		}
	}

	GcodeVariable var;
	var.Name = name;
	var.Value = value;

	gcodeVariables.push_back(var);
	emit JustUpdateVariable(gcodeVariables);
}

void GcodeProgramManager::SetStartingGcodeEditorCursor(QString value)
{
	startingMode = value;
}


float GcodeProgramManager::calculateExpressions(QString expression)
{
	int index = 0;
	
	while (1)
	{
		int openIndex = expression.lastIndexOf('[');
		int multiplyIndex = expression.indexOf('*');
		int divideIndex = expression.indexOf('/');
		int plusIndex = expression.indexOf('+');
		int subIndex = expression.indexOf("- ");
		int eqIndex = expression.indexOf("EQ");
		int leIndex = expression.indexOf("LE");
		int gtIndex = expression.indexOf("GT");

		if (eqIndex == -1)
		{
			eqIndex = expression.indexOf("=");
		}
		if (leIndex == -1)
		{
			leIndex = expression.indexOf("<");
		}
		if (gtIndex == -1)
		{
			gtIndex = expression.indexOf(">");
		}

		if (openIndex > -1)
		{
			int closeIndex = expression.indexOf(']', openIndex);
			QString subExpression = expression.mid(openIndex + 1, closeIndex - openIndex -1);
			float result = calculateExpressions(subExpression);

			subExpression = QString("[") + subExpression + "]";

			expression.replace(subExpression, QString::number(result));
			 
			continue;
		}
		else if ((multiplyIndex > -1 || divideIndex > -1 || plusIndex > -1 || subIndex > -1) && isNotNegative(expression))
		{
			// 3 + 2 * 5 - 4 / 2
			QString value1S = getLeftWord(expression, subIndex);
			QString value2S = getRightWord(expression, subIndex);

			if (multiplyIndex > -1)
			{
				value1S = getLeftWord(expression, multiplyIndex);
				value2S = getRightWord(expression, multiplyIndex);
			}
			else if (divideIndex > -1)
			{
				value1S = getLeftWord(expression, divideIndex);
				value2S = getRightWord(expression, divideIndex);
			}
			else if (plusIndex > -1)
			{
				value1S = getLeftWord(expression, plusIndex);
				value2S = getRightWord(expression, plusIndex);
			}
			else
			{

			}

			float value1 = value1S.toFloat();
			float value2 = value2S.toFloat();

			foreach(GcodeVariable var, gcodeVariables)
			{
				if (var.Name == value1S)
				{
					value1 = var.Value;
				}

				if (var.Name == value2S)
				{
					value2 = var.Value;
				}
			}

			float result = value1 - value2;
			QString resultS = QString::number(result);

			QString subExpression = value1S + " - " + value2S;

			if (multiplyIndex > -1)
			{
				result = value1 * value2;
				resultS = QString::number(result);

				subExpression = value1S + " * " + value2S;
			}
			else if (divideIndex > -1)
			{
				if (value2 != 0)
					result = value1 / value2;
				else
					result = 0;
				resultS = QString::number(result);

				subExpression = value1S + " / " + value2S;
			}
			else if (plusIndex > -1)
			{
				result = value1 + value2;
				resultS = QString::number(result);

				subExpression = value1S + " + " + value2S;
			}
			
			expression.replace(subExpression, QString::number(result));

			continue;
		}

		else if (eqIndex > -1 || leIndex > -1 || gtIndex > -1)
		{
			QString value1S;
			QString opeS;
			QString value2S;

			float value1;
			float value2;
			float result;

			if (eqIndex > -1)
			{
				value1S = getLeftWord(expression, eqIndex);
				value2S = getRightWord(expression, eqIndex);
			}
			else if (leIndex > -1)
			{
				value1S = getLeftWord(expression, leIndex);
				value2S = getRightWord(expression, leIndex);
			}
			else
			{
				value1S = getLeftWord(expression, gtIndex);
				value2S = getRightWord(expression, gtIndex);
			}

			if (value1S == "NULL")
			{
				value1 = NULL_NUMBER;
			}
			else
			{
				value1 = value1S.toFloat();
			}
			
			if (value2S == "NULL")
			{
				value2 = NULL_NUMBER;
			}
			else
			{
				value2 = value2S.toFloat();
			}

			foreach(GcodeVariable var, gcodeVariables)
			{
				if (var.Name == value1S)
				{
					value1 = var.Value;
				}

				if (var.Name == value2S)
				{
					value2 = var.Value;
				}
			}

			if (eqIndex > -1)
			{
				if (value1 == value2)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (leIndex > -1)
			{
				if (value1 < value2)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (value1 > value2)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}

		else
		{

			float value = deleteSpaces(expression).toFloat();

			if (deleteSpaces(expression) == "NULL")
			{
				value = NULL_NUMBER;
			}

			foreach(GcodeVariable var, gcodeVariables)
			{
				if (var.Name == expression)
				{
					value = var.Value;
				}
			}

			return value;
		}

		return expression.toInt();
	}
}

void GcodeProgramManager::SaveGcodeVariable(GcodeVariable gvar)
{
	bool isNewVar = true;

	for (int i = 0; i < gcodeVariables.length(); i++)
	{
		if (gcodeVariables[i].Name == gvar.Name)
		{
			gcodeVariables[i].Value = gvar.Value;
			isNewVar = false;
		}
	}

	if (isNewVar == true)
		gcodeVariables.push_back(gvar);
}

void GcodeProgramManager::updatePositionIntoSystemVariable(QString statement)
{
	QList<QString> pairs = statement.split(' ');

	float x, y, z, w;

	if (statement == "G28")
	{
		UpdateSystemVariable("#X", 0);
		UpdateSystemVariable("#Y", 0);
		UpdateSystemVariable("#Z", 0);
		UpdateSystemVariable("#W", 0);

		emit MoveToNewPosition(0, 0, 0, 0);
		return;
	}

	x = GetVariableValue("#X");
	y = GetVariableValue("#Y");
	z = GetVariableValue("#Z");
	w = GetVariableValue("#W");

	for each (QString pair in pairs)
	{
		QChar prefix = pair[0];
		QString value = pair.mid(1);

		if (pair[0] == 'X')
		{
			x = value.toFloat();
			UpdateSystemVariable("#X", x);
		}
		else if (pair[0] == 'Y')
		{
			y = value.toFloat();
			UpdateSystemVariable("#Y", y);
		}
		else if (pair[0] == 'Z')
		{
			z = value.toFloat();
			UpdateSystemVariable("#Z", z);
		}
		else if (pair[0] == 'W')
		{
			w = value.toFloat();
			UpdateSystemVariable("#W", w);
		}
	}

	emit MoveToNewPosition(x, y, z, w);
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

void GcodeProgramManager::ChangeSelectingProgram(GcodeProgram * ptr)
{
	if (SelectingProgram != NULL && ptr != SelectingProgram)
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
