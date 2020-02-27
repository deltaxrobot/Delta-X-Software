#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
	init();
}

void ConnectionManager::init()
{
	timer = new QTimer();
	robotPort = new QSerialPort();
	
	connect(timer, SIGNAL(timeout()), this, SLOT(FindingTimeOut()));
}

void ConnectionManager::sendQueue()
{
	if (transmitLines.size() == 0)
		return; 

	transmitLines.pop_front();

	if (transmitLines.size() > 0)
	{
		transmitLine = transmitLines.at(0);

		QString msg;
		msg = transmitLine + "\n";

		if (robotPort->isOpen())
		{
			robotPort->write(msg.toStdString().c_str(), msg.size());
		}
		else
			Debug("Serial port is not available !");
	}
}

bool ConnectionManager::IsConnect()
{
	if (robotPort->isOpen())
		return true;

	return false;
}

void ConnectionManager::Disconnect()
{
	if (robotPort->isOpen())
	{
		robotPort->close();
		isDeltaPortConnected = false;
	}
}

QString ConnectionManager::GetNamePort()
{
	if (robotPort == NULL || robotPort == Q_NULLPTR)
		return QString("Null");
	
	return robotPort->portName();
}

void ConnectionManager::SetBaudrate(int baud)
{
	this->baudrate = baud;
}

int ConnectionManager::GetBaudrate()
{
	return baudrate;
}

void ConnectionManager::FindDeltaRobot()
{
	Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
	{
		QSerialPort* sP = new QSerialPort();

		QString portName = portInfo.portName();
		sP->setPortName(portName);
		sP->setBaudRate(baudrate);

		portList.push_back(sP);

		if (sP->open((QIODevice::ReadWrite)) == true)
		{
			connect(sP, SIGNAL(readyRead()), this, SLOT(ReadData()));

			QString name = sP->portName();

			sP->write("IsDelta\n");
			sP->write("IsDelta\n");
		}
	}

	timer->start(200);
}

void ConnectionManager::Send(QString msg)
{
	if (msg == "")
		return;

	if (transmitLines.size() > 0)
	{
		if (transmitLines.at(transmitLines.size() - 1) == "Position")
			return;
	}

	if (msg == "M701" && transmitLines.size() > 0)
	{
		if (transmitLines.back() == "M701")
		{
			return;
		}
	}
	/*
	if (transmitLines.size() > 1)
	{
		transmitLines.clear();
		emit DeltaResponeGcodeDone();
	}	*/

	if (msg == "G28")
	{
		transmitLines.clear();
	}

	transmitLines.push_back(msg);

	if (transmitLines.size() > 1)
	{
		return;
	}

	transmitLine = msg;

	msg += "\n";
	if (robotPort->isOpen())
	{
		robotPort->write(msg.toStdString().c_str(), msg.size());
	}
	else
		Debug("Serial port is not available !");
}

void ConnectionManager::ConveyorSend(QString msg)
{
	if (ConveyorPort == NULL || ConveyorPort->isOpen() == false)
		return;

	msg += "\n";
	ConveyorPort->write(msg.toStdString().c_str(), msg.size());
}

void ConnectionManager::SlidingSend(QString msg)
{
	if (ConveyorPort == NULL || ConveyorPort->isOpen() == false)
		return;

	msg += "\n";
	SlidingPort->write(msg.toStdString().c_str(), msg.size());
}

void ConnectionManager::ReadData()
{
	QSerialPort* sP = qobject_cast<QSerialPort*>(sender());

	while (sP->canReadLine())
	{
		receiveLine = sP->readLine();
		QString name = sP->portName();
		emit FinishReadLine(receiveLine);

		if (receiveLine.mid(0, 8) == "YesDelta")
		{
			if (isDeltaPortConnected != true)
			{
				delete robotPort;
				robotPort = sP;
				emit DeltaResponeReady();

				isDeltaPortConnected = true;

			}			
		}

		if (receiveLine.mid(0, 2) == "Ok" || (receiveLine.indexOf('k') > -1 && receiveLine.indexOf('O') > -1))
		{
			emit DeltaResponeGcodeDone();

			sendQueue();

			if (transmitLine == "G28")
			{
				Send("Position");
			}
		}

		if (receiveLine.indexOf(",") > -1 && transmitLine == "Position")
		{
			QList<QString> nums = receiveLine.split(",");
			
			if (nums.size() == 3)
			{
				emit InHomePosition(nums[0].toFloat(), nums[1].toFloat(), nums[2].toFloat(), 0);
			}

			sendQueue();
			
		}
		if (receiveLine.at(0) == 'P' && transmitLine == "M701")
		{
			QString convenyorPosS = receiveLine.mid(1);
			float convenyorPos = convenyorPosS.toFloat();

			emit ReceiveConvenyorPosition(convenyorPos, 0);

			sendQueue();

		}
	}	
}



void ConnectionManager::FindingTimeOut()
{
	static int order = 0;
	
	order++;

	QString waitS = "";

	for (int i = 0; i < order; i++)
	{
		waitS += ".";
	}

	Debug(waitS);

	if (order < 20 && isDeltaPortConnected == false)
		return;

	order = 0;

	for(int i = 0; i < portList.length(); i++)
	{
		if (portList.at(i)->portName() != robotPort->portName())
		{
			portList.at(i)->close();
			delete portList.at(i);
		}
	}

	portList.clear();

	timer->stop();
}
