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
	int GetBaudrate();
    void FindDeltaRobot();
	void Send(QString msg);
	void ConveyorSend(QString msg);
	void SlidingSend(QString msg);
	QSerialPort* ConveyorPort;
	QSerialPort* SlidingPort;

public slots:
	void ReadData();
	void FindingTimeOut();
signals:
	void FinishReadLine(QString msg);
	void DeltaResponeReady();
	void DeltaResponeGcodeDone();
	void InHomePosition(float x, float y, float z, float w);
	void ReceiveConvenyorPosition(float x, float y);
private:
	void init();
	void sendQueue();

    QSerialPort* robotPort;

	QString receiveLine;
	QString transmitLine;
	QList<QString> transmitLines;
	QTimer* timer;
	QList<QSerialPort*> portList;

	bool isDeltaPortConnected = false;
	int baudrate = 9600;
};

#endif // CONNECTIONMANAGER_H
