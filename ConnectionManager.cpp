#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
    SerialPort = new QSerialPort();
}

ConnectionManager::ConnectionManager(QObject* parent)
{
    SerialPort = new QSerialPort(parent);
}

bool ConnectionManager::FindDeltaRobot()
{
    Q_FOREACH(QSerialPortInfo portName, QSerialPortInfo::availablePorts())
    {
        SerialPort->setPortName(portName.portName());
        if (SerialPort->open((QIODevice::ReadWrite)) == true)
        {
            SerialPort->write("IsDelta\n");
        }
    }

    return true;
}
