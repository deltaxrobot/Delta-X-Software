#include "SocketConnectionManager.h"

bool SocketConnectionManager::IsServerOpen()
{
    return server->isListening();
}

SocketConnectionManager::SocketConnectionManager(const QString &address, int port, QObject *parent)
    : QObject(parent), hostAddress(address), port(port) {

    server = new QTcpServer(this);
    Connect(address, port);
}

bool SocketConnectionManager::Connect(QString address, int port)
{
    for (int i = 0; i < 10; i++)
    {
        bool isSuccess = server->listen(QHostAddress(hostAddress), port + i);
        if (isSuccess == true)
        {
            connect(server, &QTcpServer::newConnection, this, &SocketConnectionManager::newClientConnected);
            return true;
        }
    }

    return false;
}

void SocketConnectionManager::newClientConnected() {
    QTcpSocket* clientSocket = server->nextPendingConnection();
    clients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead, this, &SocketConnectionManager::readFromClient);
}

void SocketConnectionManager::readFromClient() {
    QTcpSocket* senderSocket = static_cast<QTcpSocket*>(sender());
    QByteArray data = senderSocket->readAll();

    if (data.startsWith("ExternalScript\n")) {
        senderSocket->setObjectName("ImageClient");
        return;
    }

    // Handling variable assignment
    if (data.contains('=')) {
        QStringList parts = QString(data).split('=');
        if (parts.size() == 2) {
            QString varName = parts[0].trimmed();
            QString value = parts[1].trimmed();

            // You might need a mapping mechanism to link variable names to actual variables in your program

            // Example:
            // if(varName == "counter") {
            //     counter = value.toInt();
            // }

            emit variableChanged(varName, value);
        }
    } else if (!data.isEmpty()) {
        // Call a function by its name using Qt's meta-object system
        QMetaObject::invokeMethod(this, data.trimmed().toStdString().c_str());
    }
}

void SocketConnectionManager::sendImageToImageClients(const QImage &image) {
//    QByteArray byteArray;
//    QBuffer buffer(&byteArray);
//    buffer.open(QIODevice::WriteOnly);
//    image.save(&buffer, "JPG");

//    for (QTcpSocket* client : clients) {
//        if (client->objectName() == "ImageClient") {
//            client->write(byteArray);
//            client->waitForBytesWritten();
//        }
//    }
}
