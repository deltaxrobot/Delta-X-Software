#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qtimer.h>
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

	void ExecuteGcode(QString gcodes);

public slots:
	void TransmitGcode();

private:
    QSerialPort* serialPort;
	QTimer* timer;
	QList<QString> gcodeList;
	int gcodeOrder = 0;
};

#endif // CONNECTIONMANAGER_H
