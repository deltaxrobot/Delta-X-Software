#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
    serialPort = new QSerialPort();
}

ConnectionManager::ConnectionManager(QObject* parent)
{
    serialPort = new QSerialPort(parent);
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
	serialPort->write(gcodes.toStdString().c_str(), gcodes.size());
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
			while (serialPort->waitForReadyRead(500))
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
