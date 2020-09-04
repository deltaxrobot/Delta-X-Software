#pragma once

#include <QObject>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <UnityTool.h>
#include <QHostInfo>

class Client
{
public:
	QString ID;
	QTcpSocket* socket;
	bool IsROS = false;
};

class TCPConnectionManager : public QObject
{
	Q_OBJECT

public:
	TCPConnectionManager();
	~TCPConnectionManager();

	void OpenServer();
	void OpenServer(QString s, int p);

	void ProcessReceivedData(QString data);

	QString serverName = "localhost";
	int port = 8844;

	QString ReceivedString = "";

	QTcpServer* TcpServer;
	QList<QTcpSocket*>* TcpClients;
	QList<Client*>* ClientList = NULL;

	static QString GetLocalIP();

public slots:
	void CreatNewConnection();
	void ReadDataFromClients();
	void SendMessageToROS(QString msg);
	

signals:
	void ReceiveVariableChangeCommand(QString name, float value);
	void ReceivePositionUpdateCommand(float x, float y, float z, float w);
	void ReceiveOk();
	void ReceivePosition(float x, float y, float z, float w);
	void NewConnection(QTcpSocket* socket);

private:
	
};
