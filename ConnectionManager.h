#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class ConnectionManager
{
public:
    ConnectionManager();
    ConnectionManager(QObject* parent);

    bool FindDeltaRobot();

    QSerialPort* SerialPort;
};

#endif // CONNECTIONMANAGER_H
