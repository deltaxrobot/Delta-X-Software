#include "SocketConnectionManager.h"

bool SocketConnectionManager::IsServerOpen()
{
    return server->isListening();
}

QString SocketConnectionManager::printLocalIpAddresses() {
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        // Kiểm tra xem giao diện mạng có hoạt động không và không phải là loopback
        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
                !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {

            for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
                // Loại trừ địa chỉ IPv6 và loopback
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol &&
                        entry.ip() != localhost) {
                    return entry.ip().toString();
                }
            }
        }
    }
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

    // Gửi "deltax\n" cho client
    clientSocket->write("deltax\n");
}

void SocketConnectionManager::readFromClient() {
    QTcpSocket* senderSocket = static_cast<QTcpSocket*>(sender());
    QByteArray data = senderSocket->readAll();

    qDebug() << "Received data from client: " << data;

    if (data.startsWith("ExternalScript\n")) {
        senderSocket->setObjectName("ImageClient");
        return;
    }

    // kiểm tra nếu client gửi thông điệp ClientName=tên thì đặt tên cho nó
    if (data.startsWith("ClientName=")) {
        QString clientName = QString(data).split("=")[1];
        senderSocket->setObjectName(clientName);
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
            if (varName.contains("Objects"))
            {
                QList<QStringList> objects;
                QStringList objectsString = value.split(";");
                for (int i = 0; i < objectsString.size(); i++)
                {
                    QStringList objectString = objectsString[i].split(",");
                    
                    objects.append(objectString);
                }

                emit objectUpdated(varName, objects);
            }
            else if (varName.contains("Blobs"))
            {
                QStringList blobs = value.split(";");

                emit blobUpdated(blobs);
            }
            else if (varName.contains("GScript"))
            {
                emit gcodeReceived(value);
            }
            else
            {
                VariableManager::instance().UpdateVarToModel(varName, value);
                emit variableChanged(varName, value);
            }
        }
    } /*
    else if (data.contains("M98"))
    {
        emit gcodeReceived(data);
    }*/
    else if (!data.isEmpty()) {
        // Call a function by its name using Qt's meta-object system
        QMetaObject::invokeMethod(this, data.trimmed().toStdString().c_str());
    }
}

void SocketConnectionManager::sendImageToImageClients(const QImage &image) {
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");

    for (QTcpSocket* client : clients) {
        if (client->objectName().contains("ImageClient")) {
            client->write("Image\n" + data);
            client->flush();
        }
    }
}

void SocketConnectionManager::sendImageToImageClients(cv::Mat mat)
{
//    // Chuyển mat sang QImage
//    QImage image = QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
//    sendImageToImageClients(image);
    std::vector<uchar> buf;
    cv::imencode(".png", mat, buf);
    QByteArray data(reinterpret_cast<const char*>(buf.data()), buf.size());
    for (QTcpSocket* client : clients) {
        if (client->objectName().contains("ImageClient")) {
            client->write("Image\n" + data);
            client->flush();
        }
    }

}
