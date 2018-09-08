#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
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

void ConnectionManager::Send(QString msg)
{
	if (serialPort->isOpen())
	{
		serialPort->write(msg.toStdString().c_str(), msg.size());
	}
	else
		Debug("Serial port is not available !");
}

bool ConnectionManager::FindDeltaRobot()
{
	Q_FOREACH(QSerialPortInfo portName, QSerialPortInfo::availablePorts())
	{
		serialPort->setPortName(portName.portName());
		serialPort->setBaudRate(9600);
		if (serialPort->open((QIODevice::ReadWrite)) == true)
		{
			serialPort->write("IsDelta\n");

			QByteArray receiveData = serialPort->readAll();
			while (serialPort->waitForReadyRead(2000))
			{
				receiveData = serialPort->readAll();
				//Debug(receiveData);
				receiveData = receiveData.mid(0, QString("YesDelta").length());
				if (receiveData == "YesDelta")
					return true;
			}

			serialPort->close();
		}
		
	}

	return false;
}
