#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
	init();
}

void ConnectionManager::init()
{
	timer = new QTimer();
	serialPort = new QSerialPort();
	
	connect(timer, SIGNAL(timeout()), this, SLOT(FindingTimeOut()));
}

bool ConnectionManager::IsConnect()
{
	if (serialPort->isOpen())
		return true;

	return false;
}

void ConnectionManager::Disconnect()
{
	if (serialPort->isOpen())
	{
		serialPort->close();
		isDeltaPortConnected = false;
	}
}

QString ConnectionManager::GetNamePort()
{
	return serialPort->portName();
}

void ConnectionManager::Send(QString msg)
{
	if (serialPort->isOpen())
	{
		serialPort->write(msg.toStdString().c_str(), msg.size());
	}
	else
		Debug("Serial port is not available !");
}

void ConnectionManager::ReadData()
{
	QSerialPort* sP = qobject_cast<QSerialPort*>(sender());

	while (sP->canReadLine())
	{
		receiveLine = sP->readLine();
		emit FinishReadLine(receiveLine);

		if (receiveLine.mid(0, 8) == "YesDelta")
		{
			delete serialPort;
			serialPort = sP;
			emit DeltaResponeReady();

			isDeltaPortConnected = true;
		}			
	}	
}

void ConnectionManager::FindDeltaRobot()
{
	Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
	{
		QSerialPort* sP = new QSerialPort();

		QString portName = portInfo.portName();
		sP->setPortName(portName);
		sP->setBaudRate(9600);

		portList.push_back(sP);				

		if (sP->open((QIODevice::ReadWrite)) == true)
		{
			connect(sP, SIGNAL(readyRead()), this, SLOT(ReadData()));

			sP->write("IsDelta\n");
		}	
	}

	timer->start(200);
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
		if (portList.at(i)->portName() != serialPort->portName())
		{
			portList.at(i)->close();
			delete portList.at(i);
		}
	}
	portList.clear();

	timer->stop();
}
