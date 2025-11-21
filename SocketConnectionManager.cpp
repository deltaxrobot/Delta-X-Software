#include "SocketConnectionManager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

SocketConnectionManager::~SocketConnectionManager()
{
    delete Server;
    delete WebServer;
    delete BlocklyServer;
}

bool SocketConnectionManager::IsServerOpen()
{
    return Server->isListening();
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

    return QStringLiteral("127.0.0.1");
}

SocketConnectionManager::SocketConnectionManager(const QString &address, int port, QObject *parent)
    : QObject(parent), hostAddress(address), port(port) {

    if (hostAddress.isEmpty() || hostAddress == "0.0.0.0")
    {
        hostAddress = printLocalIpAddresses();
    }
    if (hostAddress.isEmpty())
    {
        hostAddress = QStringLiteral("127.0.0.1");
    }

    indexPath = resolveIndexFile(indexPath);
    latestGscript.clear();

    Server = new QTcpServer(this);
    Connect(hostAddress, port);

    WebServer = new QTcpServer(this);
    bool result = WebServer->listen(QHostAddress(hostAddress), 5000);
    qDebug() << "Create web server: " << result;
    connect(WebServer, &QTcpServer::newConnection, this, &SocketConnectionManager::newWebClientConnected);

    BlocklyServer = new QTcpServer(this);
    bool blocklyResult = startBlocklyServer(5050);
    qDebug() << "Create Blockly server:" << blocklyResult << "port" << blocklyPort;
    if (blocklyResult)
    {
        connect(BlocklyServer, &QTcpServer::newConnection, this, &SocketConnectionManager::newBlocklyClientConnected);
    }
}

bool SocketConnectionManager::Connect(QString address, int port)
{
    for (int i = 0; i < 10; i++)
    {
        bool isSuccess = Server->listen(QHostAddress(hostAddress), port + i);
        if (isSuccess == true)
        {
            connect(Server, &QTcpServer::newConnection, this, &SocketConnectionManager::newClientConnected);
            return true;
        }
    }

    return false;
}

QString SocketConnectionManager::resolveIndexFile(const QString &fileName) const
{
    QStringList candidates;
    QFileInfo providedInfo(fileName);

    const QString resourcePath = QString(":/%1").arg(fileName);
    QFile resourceFile(resourcePath);
    if (resourceFile.exists())
    {
        qDebug() << "Using web control index file from resources:" << resourcePath;
        return resourcePath;
    }

    if (providedInfo.isAbsolute())
    {
        candidates << providedInfo.absoluteFilePath();
    }

    const QString currentDir = providedInfo.isAbsolute()
            ? providedInfo.absoluteFilePath()
            : QDir::current().absoluteFilePath(fileName);
    candidates << currentDir;

    const QString appDir = QCoreApplication::applicationDirPath();
    candidates << QDir(appDir).absoluteFilePath(fileName);
    candidates << QDir(appDir + "/../Resources").absoluteFilePath(fileName);

    QDir walker(appDir);
    for (int i = 0; i < 4; ++i)
    {
        candidates << walker.absoluteFilePath(fileName);
        if (!walker.cdUp())
            break;
    }

    for (const QString &path : candidates)
    {
        QFileInfo info(path);
        if (info.exists() && info.isFile())
        {
            qDebug() << "Using web control index file at:" << info.absoluteFilePath();
            return info.absoluteFilePath();
        }
    }

    qDebug() << "Web control" << fileName << "not found in common locations, fallback to:" << currentDir;
    return currentDir;
}

void SocketConnectionManager::setIndexFileName(const QString &fileName)
{
    indexPath = resolveIndexFile(fileName);
}

void SocketConnectionManager::newClientConnected() {
    QTcpSocket* clientSocket = Server->nextPendingConnection();
    clients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead, this, &SocketConnectionManager::readFromClient);

    // Nếu client bị hủy thì xóa nó khỏi danh sách
    connect(clientSocket, &QTcpSocket::disconnected, [this, clientSocket]() {
        clients.removeOne(clientSocket);
    });

    // Gửi "deltax\n" cho client
    clientSocket->write("deltax\n");
}

void SocketConnectionManager::newWebClientConnected()
{
    QTcpSocket *socket = WebServer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, [this, socket]() {
        QByteArray requestData = socket->readAll();
        QString request = QString::fromUtf8(requestData);
        
        qDebug() << "Web client request:" << request;
        
        // Check if it's a POST request
        if (request.startsWith("POST")) {
            // Extract the body from POST request
            int bodyStart = request.indexOf("\r\n\r\n");
            if (bodyStart != -1) {
                QString body = request.mid(bodyStart + 4);
                qDebug() << "POST body:" << body;
                
                // Process the POST data like a regular TCP client
                processWebPostData(body);
                
                // Send HTTP response
                QString httpResponse = "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-Type: text/plain\r\n";
                httpResponse += "Access-Control-Allow-Origin: *\r\n";
                httpResponse += "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n";
                httpResponse += "Access-Control-Allow-Headers: Content-Type\r\n";
                httpResponse += "Content-Length: 2\r\n";
                httpResponse += "\r\n";
                httpResponse += "OK";
                
                socket->write(httpResponse.toUtf8());
                socket->flush();
                socket->waitForBytesWritten();
            }
            socket->disconnectFromHost();
        }
        // Handle CORS preflight request
        else if (request.startsWith("OPTIONS")) {
            QString httpResponse = "HTTP/1.1 200 OK\r\n";
            httpResponse += "Access-Control-Allow-Origin: *\r\n";
            httpResponse += "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n";
            httpResponse += "Access-Control-Allow-Headers: Content-Type\r\n";
            httpResponse += "Content-Length: 0\r\n";
            httpResponse += "\r\n";
            
            socket->write(httpResponse.toUtf8());
            socket->flush();
            socket->waitForBytesWritten();
            socket->disconnectFromHost();
        }
        else {
            QString requestLine = request.section("\r\n", 0, 0);
            QString targetPath = "/";
            if (requestLine.startsWith("GET")) {
                const QStringList tokens = requestLine.split(' ');
                if (tokens.size() >= 2) {
                    targetPath = tokens.at(1);
                }
            }
            int queryIndex = targetPath.indexOf('?');
            if (queryIndex != -1) {
                targetPath = targetPath.left(queryIndex);
            }

            if (targetPath == "/gscript") {
                QString script = latestGscript;
                QByteArray body = script.toUtf8();
                QString response = QString("HTTP/1.1 200 OK\r\n"
                                           "Content-Type: text/plain; charset=utf-8\r\n"
                                           "Access-Control-Allow-Origin: *\r\n"
                                           "Content-Length: %1\r\n"
                                           "\r\n").arg(body.size());
                socket->write(response.toUtf8());
                socket->write(body);
                socket->flush();
                socket->waitForBytesWritten();
                socket->disconnectFromHost();
                return;
            }

            QString fileToServe = indexPath;
            if (targetPath.startsWith("/blockly")) {
                fileToServe = resolveIndexFile(QStringLiteral("script-example/blockly/blockly.html"));
            }

            QFile file(fileToServe);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Could not open HTML file:" << fileToServe;
                QString response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found";
                socket->write(response.toUtf8());
                socket->flush();
                socket->waitForBytesWritten();
                socket->disconnectFromHost();
                return;
            }

            QTextStream in(&file);
            QString htmlContent = in.readAll();
            file.close();

            QString response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + htmlContent;
            response.replace("127.0.0.1", hostAddress);
            socket->write(response.toUtf8());
            socket->flush();
            socket->waitForBytesWritten();
            socket->disconnectFromHost();
        }
    });
}

void SocketConnectionManager::newBlocklyClientConnected()
{
    QTcpSocket *socket = BlocklyServer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, [this, socket]() {
        QByteArray requestData = socket->readAll();
        QString request = QString::fromUtf8(requestData);

        qDebug() << "Blockly client request:" << request;

        if (request.startsWith("POST")) {
            int bodyStart = request.indexOf("\r\n\r\n");
            if (bodyStart != -1) {
                QString body = request.mid(bodyStart + 4);
                processWebPostData(body);

                QString httpResponse = "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-Type: text/plain\r\n";
                httpResponse += "Access-Control-Allow-Origin: *\r\n";
                httpResponse += "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n";
                httpResponse += "Access-Control-Allow-Headers: Content-Type\r\n";
                httpResponse += "Content-Length: 2\r\n";
                httpResponse += "\r\n";
                httpResponse += "OK";

                socket->write(httpResponse.toUtf8());
                socket->flush();
                socket->waitForBytesWritten();
            }
            socket->disconnectFromHost();
        }
        else if (request.startsWith("OPTIONS")) {
            QString httpResponse = "HTTP/1.1 200 OK\r\n";
            httpResponse += "Access-Control-Allow-Origin: *\r\n";
            httpResponse += "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n";
            httpResponse += "Access-Control-Allow-Headers: Content-Type\r\n";
            httpResponse += "Content-Length: 0\r\n";
            httpResponse += "\r\n";

            socket->write(httpResponse.toUtf8());
            socket->flush();
            socket->waitForBytesWritten();
            socket->disconnectFromHost();
        }
        else {
            QString httpResponse = "HTTP/1.1 200 OK\r\n";
            httpResponse += "Content-Type: text/plain\r\n";
            httpResponse += "Access-Control-Allow-Origin: *\r\n";
            httpResponse += "Content-Length: 17\r\n";
            httpResponse += "\r\n";
            httpResponse += "Blockly endpoint";
            socket->write(httpResponse.toUtf8());
            socket->flush();
            socket->waitForBytesWritten();
            socket->disconnectFromHost();
        }
    });
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

    // Tìm vị trí của dòng trống giữa headers và body
    int headerEnd = data.indexOf("\r\n\r\n") + 4;
    QByteArray body = data.mid(headerEnd);

    if (data.contains("POST"))
    {
        data = body;
        senderSocket->close();
        clients.removeOne(senderSocket);
    }

    QString decodedData = QString::fromUtf8(data);
    QString varName;
    QString value;
    if (extractAssignment(decodedData, varName, value)) {
        handleAssignment(varName, value);
    }
    else if (data.length() >= 2)
    {
        if (data.at(0) == '#')
        {
            QString value = VariableManager::instance().getVar(QString(data).trimmed()).toString();
            senderSocket->write((value + "\n").toUtf8());
        }
    }
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

void SocketConnectionManager::processWebPostData(const QString& data)
{
    qDebug() << "Processing web POST data:" << data;
    
    // Process the POST data using the same logic as readFromClient
    QString varName;
    QString value;
    if (extractAssignment(data, varName, value)) {
        handleAssignment(varName, value);
    }
    else if (data.length() >= 2)
    {
        if (data.at(0) == '#')
        {
            QString value = VariableManager::instance().getVar(QString(data)).toString();
            // For web POST, we don't send response back as it's HTTP request
            qDebug() << "Variable query result:" << value;
        }
    }
    else if (!data.isEmpty()) {
        // Call a function by its name using Qt's meta-object system
        QMetaObject::invokeMethod(this, data.trimmed().toStdString().c_str());
    }
}

void SocketConnectionManager::sendImageToImageClients(cv::Mat mat)
{
    if (imageSendingMethod == 0)
    {
        sendImageToExternalScript(mat);
    }
    else
    {
        std::vector<uchar> buf;
        cv::imencode(".png", mat, buf);
        QByteArray data(reinterpret_cast<const char*>(buf.data()), buf.size());
        for (QTcpSocket* client : clients) {
            if (client->isOpen() == false)
                continue;
            if (client->objectName().contains("ImageClient")) {
                client->write("Image\n" + data);
                client->flush();
            }
        }
    }
}

void SocketConnectionManager::sendImageToExternalScript(cv::Mat input)
{
    for (QTcpSocket* client : clients) {
        if (client->isOpen() == false)
            continue;
        if (client->objectName().contains("ImageClient")) {

            if (client == NULL || input.empty())
                return;

            int paras[3];
            paras[0] = input.cols;
            paras[1] = input.rows;
            paras[2] = input.channels();

            int len = 3 * sizeof(int);

            client->write((char*)paras, len);

            int colByte = input.cols*input.channels() * sizeof(uchar);
            for (int i = 0; i < input.rows; i++)
            {
                char* data = (char*)input.ptr<uchar>(i); //first address of the i-th line
                int sedNum = 0;
                char buf[1024] = { 0 };

                while (sedNum < colByte)
                {
                    int sed = (1024 < colByte - sedNum) ? 1024 : (colByte - sedNum);
                    memcpy(buf, &data[sedNum], sed);
                    int SendSize = client->write(buf, sed);

                    if (SendSize == -1)
                        return;
                    sedNum += SendSize;
                }
            }
        }
    }

}

void SocketConnectionManager::updateLatestGscript(const QString& script)
{
    latestGscript = script;
}

bool SocketConnectionManager::extractAssignment(const QString &data, QString &varName, QString &value) const
{
    int index = data.indexOf('=');
    if (index <= 0)
        return false;

    varName = data.left(index).trimmed();
    value = data.mid(index + 1);
    return !varName.isEmpty();
}

void SocketConnectionManager::handleAssignment(const QString &varName, QString value)
{
    QString processedValue = value;
    if (varName.contains("GScriptEditor"))
    {
        processedValue.replace("\r\n", "\n");
    }
    else
    {
        processedValue = processedValue.trimmed();
    }

    if (varName.contains("Objects"))
    {
        QList<QStringList> objects;
        QStringList objectsString = processedValue.split(";");
        for (int i = 0; i < objectsString.size(); i++)
        {
            QStringList objectString = objectsString[i].split(",");
            objects.append(objectString);
        }

        emit objectUpdated(varName, objects);
    }
    else if (varName.contains("Blobs") || varName.contains("Object"))
    {
        QStringList blobs = processedValue.split(";");
        emit blobUpdated(blobs);
    }
    else if (varName.contains("GScriptEditor"))
    {
        latestGscript = processedValue;
        emit gscriptEditorReceived(processedValue);
    }
    else if (varName.contains("GScript"))
    {
        emit gcodeReceived(processedValue);
    }
    else if (varName.contains("Event"))
    {
        QStringList values = processedValue.split(",");
        if (values.size() >= 3)
        {
            emit eventReceived(values.at(0).trimmed(), values.at(1).trimmed(), values.at(2).trimmed());
        }
    }
    else
    {
        QString normalizedName = varName;
        normalizedName.replace("#", "");
        VariableManager::instance().updateVar(normalizedName, processedValue);
        emit variableChanged(normalizedName, processedValue);
    }
}

bool SocketConnectionManager::startBlocklyServer(quint16 startPort)
{
    if (!BlocklyServer)
        return false;

    for (int i = 0; i < 10; ++i) {
        quint16 tryPort = startPort + i;
        if (BlocklyServer->listen(QHostAddress(hostAddress), tryPort)) {
            blocklyPort = tryPort;
            return true;
        }
    }

    blocklyPort = 0;
    return false;
}
