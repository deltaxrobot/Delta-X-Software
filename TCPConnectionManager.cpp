#include "TCPConnectionManager.h"

TCPConnectionManager::TCPConnectionManager()
{
	tcpServer = new QTcpServer();
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(CreatNewConnection()));
	
	RosSocketList = new QList<ROSConnection*>();
}

TCPConnectionManager::~TCPConnectionManager()
{
}

void TCPConnectionManager::OpenServer()
{
	tcpServer->listen(QHostAddress(serverName), port);
}

void TCPConnectionManager::OpenServer(QString s, int p)
{
	serverName = s;
	port = p;

	OpenServer();
}

void TCPConnectionManager::ReadDataFromClients()
{
	QTcpSocket* socket = (QTcpSocket*) sender();
	ReceivedString = socket->readAll();

	QStringList datas = ReceivedString.split('\n');
	for (int i = 0; i < datas.size(); i++)
	{
		processReceivedData(datas.at(i));
	}
	
}

void TCPConnectionManager::SendMessageToAll(QString msg)
{
	if (RosSocketList == NULL)
		return;

	for (int i = 0; i < RosSocketList->count(); i++)
	{
		RosSocketList->at(i)->socket->write(msg.toLocal8Bit());
	}
}

void TCPConnectionManager::processReceivedData(QString data)
{	
	if (data == "")
		return;

	if (data.at(0) == '#' && data.indexOf("="))
	{
		int symId = data.indexOf("=");
		QString name = data.mid(0, symId).replace(" ", "");
		float value = data.mid(symId + 1).replace(" ", "").toInt();
		emit ReceiveVariableChangeCommand(name, value);
	}
	else if (data.mid(0, 2) == "Ok" || (data.indexOf('k') > -1 && data.indexOf('O') > -1))
	{
		emit ReceiveOk();
	}
	else if (data.indexOf('x') > -1 && data.indexOf('y') > -1 && data.indexOf('z') > -1)
	{
		QStringList datas = data.split(' ');
		emit ReceivePosition(datas.at(1).toFloat(), datas.at(3).toFloat(), datas.at(5).toFloat(), NULL_NUMBER);
	}

}

void TCPConnectionManager::CreatNewConnection()
{
	QTcpSocket* socket = tcpServer->nextPendingConnection();
	connect(socket, SIGNAL(readyRead()), this, SLOT(ReadDataFromClients()));

	ROSConnection* rosConnection = new ROSConnection();
	rosConnection->ID = RosSocketList->size();
	rosConnection->socket = socket;

	RosSocketList->push_back(rosConnection);

	socket->write("deltax");
}