#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <qthread.h>
#include <UnityTool.h>
#include <qtimer.h>
#include <TCPConnectionManager.h>
#include <QList>

class ConnectionManager : public QObject
{
	Q_OBJECT
public:
    ConnectionManager();

	QSerialPort* RobotPort;
	QTcpSocket* RobotSocket;

	QSerialPort* ConveyorPort;
	QTcpSocket* ConveyorSocket;

	QSerialPort* SlidingPort;
	QTcpSocket* SlidingSocket;

	QSerialPort* ExternalControllerPort;
	QTcpSocket* ExternalControllerSocket;

	QIODevice* IOSender;

	TCPConnectionManager* TCPConnection;
    QTcpServer* TcpServer;

    QList<QSerialPort*> Ports;

	bool IsRobotConnect();
	void DisconnectRobot();
	bool IsRosClientAvailable();
	bool IsRosSocket(QIODevice* socket);
	QString GetNamePort();
	void SetBaudrate(int baud);
	int GetBaudrate();
    void FindDeltaRobot();
	void SendToRobot(QString msg);

    void SendToConveyor(QString msg);
    void SendToSlider(QString msg);
    void SendToExternalMCU(QString msg);


public slots:
	void ReadData();
    void FindingRobotTimeOut();

    void ReceiveNewConnectionFromServer(QTcpSocket* socket);

    void SendRobotMsgToCOMPort();

signals:
	void FinishReadLine(QString msg);
	void ExternalMCUTransmitText(QString text);
	void DeltaResponeReady();
    void FailTransmit();
    void FinishFindingRobot();
	void DeltaResponeGcodeDone();
    void Responsed(QString msg);
    void InHomePosition(float x, float y, float z, float w, float u, float v);
	void ReceiveConvenyorPosition(float x, float y);

    void ReceiveInputIO(QString response);

    void ReceiveVariableChangeCommand(QString name, QString value);
    void ReceiveObjectInfoFromExternalAI(QString msg);
    void ReceiveDisplayObjectFromExternalScript(QString msg);
    void ReceiveCaptureSignalFromExternalAI();
	void RequestVariableValue(QIODevice* sender, QString name);

	void ReceiveRequestsFromExternal(QString request);

    void CaptureFromExternalCamera();
    void ExternalScriptOpened(QTcpSocket* socket);

    void Log(QString msg);
private:
	void init();
	void sendQueue();
	void processReceiveData();
	void sendData(QSerialPort* com, QTcpSocket* socket, QString msg);
	void OpenAvailableServer();

	QString receiveLine;
	QString transmitLine;
	QList<QString> transmitLines;
    QTimer* connectionTimer;
    QTimer* callfuntionTimer;
	QList<QSerialPort*> portList;

	bool isDeltaPortConnected = false;
	int baudrate = 9600;
};

#endif // CONNECTIONMANAGER_H
