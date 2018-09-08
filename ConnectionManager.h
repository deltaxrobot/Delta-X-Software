#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <qthread.h>
#include <UnityTool.h>

class ConnectionManager : public QObject
{
	Q_OBJECT
public:
    ConnectionManager();
    ConnectionManager(QObject* parent);
	bool IsConnect();
	void Disconnect();
	QString GetNamePort();
    bool FindDeltaRobot();
	void Send(QString msg);

	

public slots:

private:
    QSerialPort* serialPort;
};

#endif // CONNECTIONMANAGER_H
