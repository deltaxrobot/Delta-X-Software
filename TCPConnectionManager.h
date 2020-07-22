#pragma once

#include <QObject>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <UnityTool.h>

class ROSConnection
{
public:
	QString ID;
	QTcpSocket* socket;
};

class TCPConnectionManager : public QObject
{
	Q_OBJECT

public:
	TCPConnectionManager();
	~TCPConnectionManager();

	void OpenServer();
	void OpenServer(QString s, int p);

	QString serverName = "localhost";
	int port = 8844;

	QString ReceivedString = "";

	QTcpServer* tcpServer;
	QList<ROSConnection*>* RosSocketList = NULL;

public slots:
	void CreatNewConnection();
	void ReadDataFromClients();
	void SendMessageToAll(QString msg);

signals:
	void ReceiveVariableChangeCommand(QString name, float value);
	void ReceivePositionUpdateCommand(float x, float y, float z, float w);
	void ReceiveOk();
	void ReceivePosition(float x, float y, float z, float w);

private:
	void processReceivedData(QString data);
};
