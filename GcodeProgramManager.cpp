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
	gcodeOrder = 0;

	for (int i = 0; i < tempGcodeList.size(); i++)
	{
		if (tempGcodeList.at(i) != "")
		{
			gcodeList.push_back(tempGcodeList.at(i));
		}
	}

	tempGcodeList.clear();

	TransmitNextGcode();
}

void GcodeProgramManager::Stop()
{
	gcodeList.clear();
	gcodeOrder = 0;
}

void GcodeProgramManager::findExeGcodeAndTransmit()
{
	int openBracIndex = currentLine.indexOf('[');
	QString expressInBracket = "";
	int resultInBracket;
	int subBracNum = 0;

	while (openBracIndex > -1)
	{
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

	QList<QString> valuePairs = currentLine.split(' ');
	QString transmitGcode = currentLine;

	for (int i = 0; i < valuePairs.size() - 1; i++)
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
							TransmitNextGcode();
							return;
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
				}
				else
				{
					gcodeOrder++;
					TransmitNextGcode();
					return;
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

				bool isNewVar = true;

				for (int i = 0; i < gcodeVariables.length(); i++)
				{
					if (gcodeVariables[i].Name == newVar.Name)
					{
						gcodeVariables[i].Value = newVar.Value;
						isNewVar = false;
					}
				}

				if (isNewVar == true)
					gcodeVariables.push_back(newVar);

				gcodeOrder++;
				TransmitNextGcode();
				return;
			}

		}
		
		// --------------- WHILE ------------------
	}

	deltaConnection->Send(transmitGcode);
	gcodeOrder += 1;
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

	currentLine = gcodeList.at(gcodeOrder) + "\n";
	QString firstPair = currentLine.split(' ')[0];

	if (firstPair[0] == 'N')
	{
		currentLine.replace(firstPair + " ", "");
	}

	findExeGcodeAndTransmit();

	Debug(currentLine);

	if (gcodeOrder == gcodeList.size())
	{
		//timer->stop();
		gcodeOrder = 0;
		gcodeList.clear();
	}
}

int GcodeProgramManager::calculateExpressions(QString expression)
{
	int index = 0;

	while (1)
	{
		int openIndex = expression.lastIndexOf('[');
		int multiplyIndex = expression.indexOf('*');
		int divideIndex = expression.indexOf('/');
		int plusIndex = expression.indexOf('+');
		int subIndex = expression.indexOf('-');
		int eqIndex = expression.indexOf("EQ");
		int leIndex = expression.indexOf("LE");
		int gtIndex = expression.indexOf("GT");

		if (openIndex > -1)
		{
			int closeIndex = expression.indexOf(']', openIndex);
			QString subExpression = expression.mid(openIndex + 1, closeIndex - openIndex -1);
			int result = calculateExpressions(subExpression);

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

			int value1 = value1S.toInt();
			int value2 = value2S.toInt();

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

			int result = value1 - value2;
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

			int value1;
			int value2;
			int result;

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

			value1 = value1S.toInt();
			value2 = value2S.toInt();

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
			int value = deleteSpaces(expression).toInt();

			foreach(GcodeVariable var, gcodeVariables)
			{
				if (var.Name == value)
				{
					value = var.Value;
				}
			}

			return value;
		}

		return expression.toInt();
	}
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
