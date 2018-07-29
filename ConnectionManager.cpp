#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(TransmitGcode()));
}

ConnectionManager::ConnectionManager(QObject* parent) : ConnectionManager()
{
	if (parent != NULL)
		serialPort = new QSerialPort(parent);
	else
		serialPort = new QSerialPort();
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
		serialPort->close();
}

QString ConnectionManager::GetNamePort()
{
	return serialPort->portName();
}

void ConnectionManager::ExecuteGcode(QString gcodes)
{
	QList<QString> tempGcodeList = gcodes.split('\n');
	for (int i = 0; i < tempGcodeList.size(); i++)
	{
		if (tempGcodeList.at(i) != "")
		{
			gcodeList.push_back(tempGcodeList.at(i));
		}
	}

	tempGcodeList.clear();

	timer->start(200);
}

void ConnectionManager::TransmitGcode()
{
	QString gcodeLine = gcodeList.at(gcodeOrder) + "\n";
	serialPort->write(gcodeLine.toStdString().c_str(), gcodeLine.size());
	Debug(gcodeLine);
	gcodeOrder++;
	if (gcodeOrder == gcodeList.size())
	{
		timer->stop();
		gcodeOrder = 0;
		gcodeList.clear();
	}		
}

bool ConnectionManager::FindDeltaRobot()
{
	/*serialPort->setPortName("COM10");
	serialPort->setBaudRate(QSerialPort::Baud115200);
	if (serialPort->open((QIODevice::ReadWrite)) == true)
	{
		return true;
	}
	return false;*/

	Q_FOREACH(QSerialPortInfo portName, QSerialPortInfo::availablePorts())
	{
		serialPort->setPortName(portName.portName());
		serialPort->setBaudRate(9600);
		if (serialPort->open((QIODevice::ReadWrite)) == true)
		{
			serialPort->write("IsDelta\n");

			QByteArray receiveData = serialPort->readAll();
			while (serialPort->waitForReadyRead(300))
			{
				receiveData.append(serialPort->readAll());
				if (receiveData.toStdString().compare("YesDelta"))
					return true;
			}

			serialPort->close();
		}
		
	}

	return false;
}
