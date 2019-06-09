#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <qthread.h>
#include <UnityTool.h>
#include <qtimer.h>

class ConnectionManager : public QObject
{
	Q_OBJECT
public:
    ConnectionManager();
	bool IsConnect();
	void Disconnect();
	QString GetNamePort();
	void SetBaudrate(int baud);
    void FindDeltaRobot();
	void Send(QString msg);
	
public slots:
	void ReadData();
	void FindingTimeOut();
signals:
	void FinishReadLine(QString msg);
	void DeltaResponeReady();
	void DeltaResponeGcodeDone();
	void InHomePosition(float x, float y, float z);
	void ReceiveConvenyorPosition(float x, float y);
private:
	void init();
	void sendQueue();

    QSerialPort* serialPort;
	QString receiveLine;
	QString transmitLine;
	QList<QString> transmitLines;
	QTimer* timer;
	QList<QSerialPort*> portList;

	bool isDeltaPortConnected = false;
	int baudrate = 9600;
};

#endif // CONNECTIONMANAGER_H
