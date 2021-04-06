#include "TCPConnectionManager.h"

TCPConnectionManager::TCPConnectionManager()
{
	TcpServer = new QTcpServer();
	connect(TcpServer, SIGNAL(newConnection()), this, SLOT(CreatNewConnection()));
	
	ClientList = new QList<Client*>();

	TcpClients = new QList<QTcpSocket*>();
}

TCPConnectionManager::~TCPConnectionManager()
{
}

bool TCPConnectionManager::OpenServer()
{
	return TcpServer->listen(QHostAddress(ServerName), Port);
}

bool TCPConnectionManager::OpenServer(QString s, int p)
{
	ServerName = s;
	Port = p;

	return OpenServer();
}

QString TCPConnectionManager::GetIP()
{
	QString localhostname = QHostInfo::localHostName();
	QString localhostIP;
	QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
	foreach(const QHostAddress& address, hostList) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
			 localhostIP = address.toString();
			 return localhostIP;
		}
	}
}

void TCPConnectionManager::ReadDataFromClients()
{

}

void TCPConnectionManager::SendMessageToROS(QString msg)
{
	if (ClientList == NULL)
		return;

	msg += "\n";

	for (int i = 0; i < ClientList->count(); i++)
	{
		if (ClientList->at(i)->IsROS == true)
		{
			ClientList->at(i)->socket->write(msg.toStdString().c_str(), msg.size());
		}		
	}
}

void TCPConnectionManager::ProcessReceivedData(QString data)
{	
	if (data == "")
		return;

    else if (data.indexOf('x') > -1 && data.indexOf('y') > -1 && data.indexOf('z') > -1 )
	{
		QStringList datas = data.split(' ');
        emit ReceivePosition(datas.at(1).toFloat(), datas.at(3).toFloat(), datas.at(5).toFloat(), NULL_NUMBER, NULL_NUMBER, NULL_NUMBER);
	}

}

void TCPConnectionManager::CreatNewConnection()
{
	QTcpSocket* socket = TcpServer->nextPendingConnection();

	emit NewConnection(socket);

	connect(socket, SIGNAL(readyRead()), this, SLOT(ReadDataFromClients()));

	Client* rosConnection = new Client();
	rosConnection->ID = ClientList->size();
	rosConnection->socket = socket;

	ClientList->push_back(rosConnection);

	socket->write("deltax");
}
