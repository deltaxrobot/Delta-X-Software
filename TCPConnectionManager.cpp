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
//    QString ipAddress;

//    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

//    for (int i = 0; i < ipAddressesList.size(); ++i)
//    {
//        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
//            ipAddressesList.at(i).toIPv4Address() &&
//            !ipAddressesList.at(i).isMulticast())
//        {
//            ipAddress = ipAddressesList.at(i).toString();
//            break;
//        }
//    }

//    if (ipAddress.isEmpty())
//    {
//        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
//    }

//    return ipAddress;

    return TcpServer->serverAddress().toString();
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
