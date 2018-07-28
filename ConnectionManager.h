#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qthread.h>

class ConnectionManager : public QThread
{
	Q_OBJECT
public:
    ConnectionManager();
    ConnectionManager(QObject* parent);
	bool IsConnect();
	void Disconnect();
	QString GetNamePort();
    bool FindDeltaRobot();

	void ExecuteGcode(QString gcodes);

private:
    QSerialPort* serialPort;
};

#endif // CONNECTIONMANAGER_H
