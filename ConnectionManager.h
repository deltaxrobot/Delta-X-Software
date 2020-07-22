#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <qthread.h>
#include <UnityTool.h>
#include <qtimer.h>
#include <TCPConnectionManager.h>

class ConnectionManager : public QObject
{
	Q_OBJECT
public:
    ConnectionManager();

	QSerialPort* ConveyorPort;
	QSerialPort* SlidingPort;
	QSerialPort* ExternalControllerPort;
	TCPConnectionManager* TCPConnection;

	bool IsConnect();
	void Disconnect();
	QString GetNamePort();
	void SetBaudrate(int baud);
	int GetBaudrate();
    void FindDeltaRobot();
	void Send(QString msg);

	void ConveyorSend(QString msg);
	void SlidingSend(QString msg);
	void ECSend(QString msg);

	bool ConnectExternalController(QString name, int baudrate);

public slots:
	void ReadData();
	void FindingTimeOut();

	void ReadDataFromExternalController();
signals:
	void FinishReadLine(QString msg);
	void DeltaResponeReady();
	void DeltaResponeGcodeDone();
	void InHomePosition(float x, float y, float z, float w);
	void ReceiveConvenyorPosition(float x, float y);

	void ReceiveVariableChangeCommand(QString name, float value);
	void ResponseVariableValue(QObject* sender, QString name);
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
