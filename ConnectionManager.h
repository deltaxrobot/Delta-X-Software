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

    enum
    {
        ROBOT = 0,
        CONVEYOR,
        ENCODER,
        SLIDER,
        MCU
    };

    ConnectionManager();

	QSerialPort* RobotPort;
	QTcpSocket* RobotSocket;

	QSerialPort* ConveyorPort;
	QTcpSocket* ConveyorSocket;

	QSerialPort* SlidingPort;
	QTcpSocket* SlidingSocket;

	QSerialPort* ExternalControllerPort;
	QTcpSocket* ExternalControllerSocket;

    QSerialPort* EncoderPort;
    QTcpSocket* EncoderSocket;

    QSerialPort* ControllerPort;
    QTcpSocket* ControllerSocket;

    QTcpSocket* ExternalScriptSocket = NULL;

    QIODevice* EmitIOSender;

	TCPConnectionManager* TCPConnection;
    QTcpServer* TcpServer;

    QList<QSerialPort*> Ports;

    bool IsRobotConnect();
	bool IsRosClientAvailable();
	bool IsRosSocket(QIODevice* socket);
	QString GetNamePort();
	void SetBaudrate(int baud);
    int GetBaudrate();
	void SendToRobot(QString msg);

    void SendToConveyor(QString msg);
    void SendToSlider(QString msg);
    void SendToExternalMCU(QString msg);
    void SendToEncoder(QString msg);


public slots:
    void FindDeltaRobot();    
    void DisconnectRobot();
	void ReadData();
    void CheckScanningRobotRespone();
    void FindingRobotTimeOut();

    void ReceiveNewConnectionFromServer(QTcpSocket* socket);

    void SendRobotConfirmCommand();
    void Send(int device, QString msg);
    void SendGcode(QString device, QString msg);

signals:
	void ExternalMCUTransmitText(QString text);
	void DeltaResponeReady();
    void FailTransmit();
    void FinishFindingRobot();
    void GcodeDone();
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

    void ReceivedEncoderPosition(float pos);
    void ReceivedProximitySensorValue(int value);

    void Log(QString msg);
private:
    void init();

    void processRobotData();
    void processConveyorData();
    void processSliderData();
    void processMCUData();
    void processEncoderData();
    void processOtherSoftwareData();

	void sendData(QSerialPort* com, QTcpSocket* socket, QString msg);
	void OpenAvailableServer();

	QString receiveLine;
	QString transmitLine;
	QList<QString> transmitLines;
    QTimer* connectionTimer;
	QList<QSerialPort*> portList;

	bool isDeltaPortConnected = false;
	int baudrate = 9600;
};

#endif // CONNECTIONMANAGER_H
