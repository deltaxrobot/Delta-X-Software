#pragma once

#include <QObject>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <UnityTool.h>
#include <QHostInfo>
#include <QNetworkInterface>

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

	bool OpenServer();
	bool OpenServer(QString s, int p);

	void ProcessReceivedData(QString data);

	QString ServerName = "null";
	int Port = 8844;

	QString ReceivedString = "";

	QTcpServer* TcpServer;
	QList<QTcpSocket*>* TcpClients;
	QList<Client*>* ClientList = NULL;

    QString GetIP();

public slots:
	void CreatNewConnection();
	void ReadDataFromClients();
	void SendMessageToROS(QString msg);
	

signals:
	void ReceiveVariableChangeCommand(QString name, float value);
    void ReceivePositionUpdateCommand(float x, float y, float z, float w, float u, float v);
	void ReceiveOk();
    void ReceivePosition(float x, float y, float z, float w, float u, float v);
	void NewConnection(QTcpSocket* socket);

private:
	
};
