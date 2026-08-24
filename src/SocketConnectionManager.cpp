#include "SocketConnectionManager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QtMath>
#include <cctype>
#include <cmath>
#include <limits>

namespace {
constexpr qint64 kMaxVisionMessageBytes = 32 * 1024 * 1024;
constexpr qint64 kMaxSocketBacklogBytes = 16 * 1024 * 1024;
constexpr int kMaxDetectionObjects = 10000;
constexpr int kMaxDetectorTextLength = 256;

int completeJsonObjectLength(const QByteArray& data)
{
    int start = 0;
    while (start < data.size() && std::isspace(static_cast<unsigned char>(data.at(start))))
        ++start;
    if (start >= data.size() || data.at(start) != '{')
        return -1;

    int depth = 0;
    bool inString = false;
    bool escaped = false;
    for (int i = start; i < data.size(); ++i) {
        const char ch = data.at(i);
        if (inString) {
            if (escaped)
                escaped = false;
            else if (ch == '\\')
                escaped = true;
            else if (ch == '"')
                inString = false;
            continue;
        }
        if (ch == '"')
            inString = true;
        else if (ch == '{')
            ++depth;
        else if (ch == '}' && --depth == 0)
            return i + 1;
    }
    return 0;
}

quint64 jsonUInt64(const QJsonObject& object, const QString& key, bool* ok)
{
    const QJsonValue value = object.value(key);
    bool converted = false;
    quint64 result = 0;
    if (value.isString())
        result = value.toString().toULongLong(&converted);
    else if (value.isDouble()) {
        const double number = value.toDouble();
        // JSON numbers are IEEE-754 doubles. Accept only the exactly representable
        // integer range; larger identifiers must be encoded as strings.
        constexpr double kMaxExactJsonInteger = 9007199254740991.0;
        if (std::isfinite(number) && number >= 0.0 &&
            number <= kMaxExactJsonInteger && std::floor(number) == number) {
            result = static_cast<quint64>(number);
            converted = true;
        }
    }
    if (ok)
        *ok = converted;
    return result;
}
}

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
        // Accept only active, non-loopback network interfaces.
        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
                !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {

            for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
                // Exclude IPv6 and loopback addresses.
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

    externalVisionClock.start();

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

    // Remove a destroyed client from the list.
    connect(clientSocket, &QTcpSocket::disconnected, [this, clientSocket]() {
        unregisterExternalVisionClient(clientSocket);
        clients.removeOne(clientSocket);
        clientBuffers.remove(clientSocket);
    });

    // Send the "deltax\n" greeting to the client.
    clientSocket->write("deltax\n");
}

QString SocketConnectionManager::socketPeerName(const QTcpSocket* socket) const
{
    if (!socket)
        return QStringLiteral("unknown");
    return QStringLiteral("%1:%2")
        .arg(socket->peerAddress().toString())
        .arg(socket->peerPort());
}

QString SocketConnectionManager::visionFrameKey(quint64 frameId, quint64 requestId,
                                                 int trackingId)
{
    return QStringLiteral("%1:%2:%3").arg(trackingId).arg(requestId).arg(frameId);
}

bool SocketConnectionManager::registerExternalVisionClient(QTcpSocket* socket,
                                                            const QString& protocol)
{
    if (!socket || !socket->isOpen())
        return false;
    if (externalVisionClients.contains(socket))
        return true;

    if (primaryExternalVisionClient && primaryExternalVisionClient != socket &&
        primaryExternalVisionClient->isOpen()) {
        reportExternalVisionError(
            socket,
            QStringLiteral("Another External Vision detector is already active"));
        QJsonObject error;
        error.insert(QStringLiteral("type"), QStringLiteral("error"));
        error.insert(QStringLiteral("protocol"), QStringLiteral("DXV1"));
        error.insert(QStringLiteral("message"),
                     QStringLiteral("Another External Vision detector is already active"));
        writeFramedJson(socket, error);
        socket->disconnectFromHost();
        return false;
    }

    socket->setObjectName(QStringLiteral("ExternalVisionClient"));
    socket->setProperty("externalVisionProtocol", protocol);
    externalVisionClients.insert(socket);
    primaryExternalVisionClient = socket;
    emit externalVisionStatusChanged(true, socketPeerName(socket));
    return true;
}

void SocketConnectionManager::unregisterExternalVisionClient(QTcpSocket* socket)
{
    if (!externalVisionClients.remove(socket))
        return;
    if (primaryExternalVisionClient == socket) {
        primaryExternalVisionClient.clear();
        pendingVisionFrames.clear();
        emit externalVisionStatusChanged(false, socketPeerName(socket));
    }
}

void SocketConnectionManager::reportExternalVisionError(QTcpSocket* socket,
                                                         const QString& message)
{
    const QString peer = socketPeerName(socket);
    qWarning() << "External Vision protocol error from" << peer << message;
    emit externalVisionProtocolError(peer, message);

    if (!socket || !socket->isOpen() || !externalVisionClients.contains(socket))
        return;
    QJsonObject error;
    error.insert(QStringLiteral("type"), QStringLiteral("error"));
    error.insert(QStringLiteral("protocol"), QStringLiteral("DXV1"));
    error.insert(QStringLiteral("message"), message);
    writeFramedJson(socket, error);
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
    if (!senderSocket)
        return;

    QByteArray& buffer = clientBuffers[senderSocket];
    buffer.append(senderSocket->readAll());
    if (buffer.size() > kMaxVisionMessageBytes * 2) {
        qWarning() << "Closing client with oversized input buffer";
        senderSocket->disconnectFromHost();
        return;
    }

    while (!buffer.isEmpty()) {
        const QByteArray registrationLine("ExternalVision DXV1\n");
        const QByteArray legacyRegistrationLine("ExternalScript\n");
        const QByteArray framedPrefix("DXV1 ");
        if ((registrationLine.startsWith(buffer) && buffer.size() < registrationLine.size()) ||
            (legacyRegistrationLine.startsWith(buffer) &&
             buffer.size() < legacyRegistrationLine.size()) ||
            (framedPrefix.startsWith(buffer) && buffer.size() < framedPrefix.size())) {
            // TCP may split even a short protocol prefix across packets.
            return;
        }

        if (buffer.startsWith(registrationLine)) {
            buffer.remove(0, registrationLine.size());
            if (!registerExternalVisionClient(senderSocket, QStringLiteral("DXV1")))
                return;
            continue;
        }

        if (buffer.startsWith("ExternalScript\n")) {
            buffer.remove(0, QByteArray("ExternalScript\n").size());
            if (!registerExternalVisionClient(senderSocket, QStringLiteral("DXV1-legacy-handshake")))
                return;
            continue;
        }

        if (buffer.startsWith("DXV1 ")) {
            if (!externalVisionClients.contains(senderSocket) &&
                !registerExternalVisionClient(senderSocket, QStringLiteral("DXV1-implicit")))
                return;
            const int newline = buffer.indexOf('\n');
            if (newline < 0)
                return;
            bool ok = false;
            const qint64 payloadSize = buffer.mid(5, newline - 5).trimmed().toLongLong(&ok);
            if (!ok || payloadSize < 0 || payloadSize > kMaxVisionMessageBytes) {
                qWarning() << "Invalid DXV1 payload length";
                senderSocket->disconnectFromHost();
                return;
            }
            if (buffer.size() < newline + 1 + payloadSize)
                return;
            const QByteArray payload = buffer.mid(newline + 1, payloadSize);
            buffer.remove(0, newline + 1 + payloadSize);
            if (!processDetectionJson(senderSocket, payload, true))
                reportExternalVisionError(senderSocket,
                                          QStringLiteral("Rejected malformed DXV1 detector message"));
            continue;
        }

        const int jsonLength = completeJsonObjectLength(buffer);
        if (jsonLength == 0)
            return;
        if (jsonLength > 0) {
            const QByteArray payload = buffer.left(jsonLength).trimmed();
            buffer.remove(0, jsonLength);
            processDetectionJson(senderSocket, payload);
            continue;
        }

        QByteArray payload = buffer;
        buffer.clear();
        processClientPayload(senderSocket, payload);
    }
}

void SocketConnectionManager::processClientPayload(QTcpSocket* senderSocket, QByteArray data)
{

    if (data.startsWith("ExternalVision DXV1\n")) {
        registerExternalVisionClient(senderSocket, QStringLiteral("DXV1"));
        return;
    }

    if (data.startsWith("ExternalScript\n")) {
        registerExternalVisionClient(senderSocket, QStringLiteral("DXV1-legacy-handshake"));
        return;
    }

    // Apply a client name supplied as ClientName=<name>.
    if (data.startsWith("ClientName=")) {
        QString clientName = QString(data).split("=")[1];
        senderSocket->setObjectName(clientName);
        return;
    }

    // JSON object message: { "type": "objects", "list": [ {..}, ... ] }
    if (data.trimmed().startsWith("{")) {
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(data, &err);
        if (err.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject obj = doc.object();
            if (obj.value("type").toString() == "objects" && obj.value("list").isArray()) {
                QJsonArray arr = obj.value("list").toArray();
                const QString listName = obj.value("listName").toString("#Objects");
                const QString coordinateSpace = obj.value("coordinateSpace")
                                                    .toString("image")
                                                    .trimmed()
                                                    .toLower();
                QList<QStringList> objects;
                QStringList blobStrings;
                for (const QJsonValue& v : arr) {
                    if (!v.isObject()) continue;
                    QJsonObject o = v.toObject();
                    int type = o.value("type").toInt();
                    double x = o.value("x").toDouble();
                    double y = o.value("y").toDouble();
                    double z = o.value("z").toDouble(0.0);
                    double w = o.value("w").toDouble();
                    double h = o.value("h").toDouble();
                    double angle = o.value("angle").toDouble();
                    bool isPicked = o.value("isPicked").toBool(false);
                    QStringList fields;
                    fields << QString::number(type)
                           << QString::number(x)
                           << QString::number(y)
                           << QString::number(z)
                           << QString::number(w)
                           << QString::number(h)
                           << QString::number(angle)
                           << (isPicked ? "1" : "0");
                    objects.append(fields);
                    QStringList imageFields;
                    imageFields << QString::number(type)
                                << QString::number(x)
                                << QString::number(y)
                                << QString::number(w)
                                << QString::number(h)
                                << QString::number(angle);
                    blobStrings << imageFields.join(",");
                }

                // Image-space detections must pass through the configured camera
                // mapping. Conveyor-space detections are already calibrated and
                // can be sent straight to tracking. Never emit both: doing so
                // creates duplicate tracks in two coordinate systems.
                if (coordinateSpace == "conveyor" || coordinateSpace == "world")
                    emit objectUpdated(listName, objects);
                else
                    emit blobUpdated(blobStrings);
                return;
            }
        }
    }

    // Locate the empty line between HTTP headers and body.
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
            QString value = VariableManager::instance().getVarScoped(ProjectName, QString(data).trimmed()).toString();
            senderSocket->write((value + "\n").toUtf8());
        }
    }
    else if (!data.isEmpty()) {
        // Call a function by its name using Qt's meta-object system
        QMetaObject::invokeMethod(this, data.trimmed().toStdString().c_str());
    }
}

bool SocketConnectionManager::processDetectionJson(QTcpSocket* socket, const QByteArray& json,
                                                    bool requireFrameMetadata)
{
    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(json, &error);
    if (error.error != QJsonParseError::NoError || !document.isObject())
        return false;

    const QJsonObject root = document.object();
    if (requireFrameMetadata && primaryExternalVisionClient != socket)
        return false;
    if (root.contains(QStringLiteral("protocol")) &&
        root.value(QStringLiteral("protocol")).toString() != QStringLiteral("DXV1"))
        return false;
    if (root.contains(QStringLiteral("schemaVersion"))) {
        const QJsonValue schema = root.value(QStringLiteral("schemaVersion"));
        if (!schema.isDouble() || schema.toDouble() != 1.0)
            return false;
    }
    if (root.value("type").toString() != QStringLiteral("objects") ||
        !root.value("list").isArray())
        return false;

    const QString coordinateSpace = root.value("coordinateSpace")
                                        .toString("image").trimmed().toLower();
    if (coordinateSpace != "image" && coordinateSpace != "conveyor" &&
        coordinateSpace != "world")
        return false;

    QVector<ObjectInfo> packetObjects;
    QList<QStringList> legacyObjects;
    QStringList legacyBlobs;
    const QJsonArray objectList = root.value("list").toArray();
    if (objectList.size() > kMaxDetectionObjects)
        return false;
    for (const QJsonValue& value : objectList) {
        if (!value.isObject())
            return false;
        const QJsonObject object = value.toObject();
        const QStringList required = { "x", "y", "w", "h", "angle" };
        for (const QString& key : required) {
            if (!object.value(key).isDouble() || !qIsFinite(object.value(key).toDouble()))
                return false;
        }
        if (!object.value("type").isDouble())
            return false;
        const double typeNumber = object.value("type").toDouble();
        if (!qIsFinite(typeNumber) || std::floor(typeNumber) != typeNumber ||
            typeNumber < std::numeric_limits<int>::min() ||
            typeNumber > std::numeric_limits<int>::max())
            return false;
        const int type = static_cast<int>(typeNumber);
        const double x = object.value("x").toDouble();
        const double y = object.value("y").toDouble();
        if (object.contains(QStringLiteral("z")) &&
            !object.value(QStringLiteral("z")).isDouble())
            return false;
        const double z = object.value("z").toDouble(0.0);
        const double width = object.value("w").toDouble();
        const double height = object.value("h").toDouble();
        const double angle = object.value("angle").toDouble();
        if (!qIsFinite(z) || width < 0.0 || height < 0.0)
            return false;
        const QJsonValue confidenceValue = object.value(QStringLiteral("confidence"));
        if (!confidenceValue.isUndefined() && !confidenceValue.isDouble())
            return false;
        const double confidence = confidenceValue.isUndefined()
            ? 1.0 : confidenceValue.toDouble(-1.0);
        if (!qIsFinite(confidence) || confidence < 0.0 || confidence > 1.0)
            return false;
        const QJsonValue labelValue = object.value(QStringLiteral("label"));
        if (!labelValue.isUndefined() && !labelValue.isString())
            return false;
        const QString label = labelValue.toString();
        if (label.size() > kMaxDetectorTextLength)
            return false;
        QString externalId;
        const QJsonValue externalIdValue = object.value(QStringLiteral("externalId"));
        if (externalIdValue.isString()) {
            externalId = externalIdValue.toString();
        } else if (externalIdValue.isDouble() &&
                   qIsFinite(externalIdValue.toDouble())) {
            externalId = QString::number(externalIdValue.toDouble(), 'g', 16);
        } else if (!externalIdValue.isUndefined() && !externalIdValue.isNull()) {
            return false;
        }
        if (externalId.size() > kMaxDetectorTextLength)
            return false;
        const QJsonValue pickedValue = object.value(QStringLiteral("isPicked"));
        if (!pickedValue.isUndefined() && !pickedValue.isBool())
            return false;
        const bool isPicked = pickedValue.toBool(false);
        packetObjects.append(ObjectInfo(-1, type, QVector3D(x, y, z),
                                        width, height, angle, isPicked, QVector3D(),
                                        QString(), 0, confidence, label, externalId));
        legacyObjects.append({ QString::number(type), QString::number(x),
                               QString::number(y), QString::number(z),
                               QString::number(width), QString::number(height),
                               QString::number(angle), isPicked ? "1" : "0" });
        legacyBlobs.append(QStringList({ QString::number(type), QString::number(x),
                                        QString::number(y), QString::number(width),
                                        QString::number(height), QString::number(angle) }).join(','));
    }

    bool frameOk = false;
    bool requestOk = false;
    const quint64 frameId = jsonUInt64(root, "frameId", &frameOk);
    const quint64 requestId = jsonUInt64(root, "requestId", &requestOk);
    const int trackingId = root.value("trackingId").toInt(-1);
    if (requireFrameMetadata && frameOk && frameId != 0 && requestOk && trackingId >= 0) {
        VisionDetections detections;
        detections.frameId = frameId;
        detections.requestId = requestId;
        detections.trackingId = trackingId;
        detections.coordinateSpace = coordinateSpace;
        detections.objects = packetObjects;
        const QString key = visionFrameKey(frameId, requestId, trackingId);
        qint64 latencyMs = -1;
        const auto pending = pendingVisionFrames.find(key);
        if (pending != pendingVisionFrames.end()) {
            latencyMs = externalVisionClock.elapsed() - pending.value();
            pendingVisionFrames.erase(pending);
        }
        emit externalDetectionsReceived(detections);
        emit externalVisionResultReceived(frameId, requestId, trackingId,
                                          packetObjects.size(), latencyMs);
        return true;
    }

    if (requireFrameMetadata)
        return false;

    // Compatibility path for old detector clients. Correlated G-Script jobs
    // must use DXV1 metadata; legacy data remains useful for manual injection.
    const QString listName = root.value("listName").toString("#Objects");
    if (coordinateSpace == "conveyor" || coordinateSpace == "world")
        emit objectUpdated(listName, legacyObjects);
    else
        emit blobUpdated(legacyBlobs);
    return true;
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
            QString value = VariableManager::instance().getVarScoped(ProjectName, QString(data)).toString();
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
    else if (imageSendingMethod == 1)
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
    else if (imageSendingMethod == 2)
    {
        sendImageAsJson(mat);
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

void SocketConnectionManager::sendImageAsJson(cv::Mat mat)
{
    if (mat.empty())
        return;

    std::vector<uchar> buf;
    if (!cv::imencode(".jpg", mat, buf))
        return;

    QByteArray binary(reinterpret_cast<const char*>(buf.data()), static_cast<int>(buf.size()));
    QByteArray b64 = binary.toBase64();

    QJsonObject obj;
    obj.insert("type", "image");
    obj.insert("encoding", "jpg");
    obj.insert("width", mat.cols);
    obj.insert("height", mat.rows);
    obj.insert("channels", mat.channels());
    obj.insert("payload", QString::fromLatin1(b64));

    QJsonDocument doc(obj);
    QByteArray json = doc.toJson(QJsonDocument::Compact);

    for (QTcpSocket* client : clients) {
        if (!client || !client->isOpen())
            continue;
        if (client->objectName().contains("ImageClient")) {
            client->write("ImageJson\n");
            client->write(json);
            client->flush();
        }
    }
}

bool SocketConnectionManager::writeFramedJson(QTcpSocket* socket, const QJsonObject& object)
{
    if (!socket || !socket->isOpen())
        return false;
    const QByteArray payload = QJsonDocument(object).toJson(QJsonDocument::Compact);
    if (payload.size() > kMaxVisionMessageBytes || socket->bytesToWrite() > kMaxSocketBacklogBytes) {
        qWarning() << "Dropping vision frame for slow image client" << socket->peerAddress();
        return false;
    }
    const QByteArray wire = "DXV1 " + QByteArray::number(payload.size()) + "\n" + payload;
    return socket->write(wire) == wire.size();
}

void SocketConnectionManager::sendVisionFrame(VisionFrame frame)
{
    if (!frame.isValid()) {
        emit externalVisionFrameFailed(frame.trackingId, frame.frameId, frame.requestId,
                                       QStringLiteral("Invalid camera frame"));
        return;
    }

    QTcpSocket* detector = primaryExternalVisionClient.data();
    if (!detector || !detector->isOpen()) {
        emit externalVisionFrameFailed(
            frame.trackingId, frame.frameId, frame.requestId,
            QStringLiteral("External Vision detector is not connected"));
        return;
    }

    std::vector<uchar> encoded;
    if (!cv::imencode(".jpg", frame.image, encoded)) {
        emit externalVisionFrameFailed(frame.trackingId, frame.frameId, frame.requestId,
                                       QStringLiteral("Could not encode camera frame as JPEG"));
        return;
    }
    const QByteArray binary(reinterpret_cast<const char*>(encoded.data()),
                            static_cast<int>(encoded.size()));

    QJsonObject object;
    object.insert("type", "image");
    object.insert("protocol", "DXV1");
    object.insert("schemaVersion", 1);
    object.insert("frameId", QString::number(frame.frameId));
    object.insert("requestId", QString::number(frame.requestId));
    object.insert("trackingId", frame.trackingId);
    object.insert("capturedAtMonotonicNs", QString::number(frame.capturedAtMonotonicNs));
    object.insert("source", frame.source);
    object.insert("encoding", "jpg");
    object.insert("width", frame.image.cols);
    object.insert("height", frame.image.rows);
    object.insert("channels", frame.image.channels());
    object.insert("payload", QString::fromLatin1(binary.toBase64()));

    if (!writeFramedJson(detector, object)) {
        emit externalVisionFrameFailed(
            frame.trackingId, frame.frameId, frame.requestId,
            QStringLiteral("External Vision detector is too slow or disconnected"));
        return;
    }

    if (pendingVisionFrames.size() > 128)
        pendingVisionFrames.clear();
    pendingVisionFrames.insert(visionFrameKey(frame.frameId, frame.requestId,
                                              frame.trackingId),
                               externalVisionClock.elapsed());
    emit externalVisionFrameSent(frame.frameId, frame.requestId, frame.trackingId,
                                 binary.size());
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

    const bool remoteControlEnabled = VariableManager::instance().getVarScoped(
        ProjectName, QStringLiteral("Network.AllowLegacyRemoteControl"), false).toBool();

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
        if (!remoteControlEnabled) {
            emit remoteControlRejected(QStringLiteral("GScriptEditor"),
                                       QStringLiteral("Legacy remote control is disabled"));
            return;
        }
        latestGscript = processedValue;
        emit gscriptEditorReceived(processedValue);
    }
    else if (varName.contains("GScript"))
    {
        if (!remoteControlEnabled) {
            emit remoteControlRejected(QStringLiteral("GScript"),
                                       QStringLiteral("Legacy remote execution is disabled"));
            return;
        }
        emit gcodeReceived(processedValue);
    }
    else if (varName.contains("Event"))
    {
        if (!remoteControlEnabled) {
            emit remoteControlRejected(QStringLiteral("Event"),
                                       QStringLiteral("Legacy remote control is disabled"));
            return;
        }
        QStringList values = processedValue.split(",");
        if (values.size() >= 3)
        {
            emit eventReceived(values.at(0).trimmed(), values.at(1).trimmed(), values.at(2).trimmed());
        }
    }
    else
    {
        if (!remoteControlEnabled) {
            emit remoteControlRejected(QStringLiteral("VariableWrite"),
                                       QStringLiteral("Legacy remote variable writes are disabled"));
            return;
        }
        QString normalizedName = varName;
        normalizedName.replace("#", "");
        VariableManager::instance().updateVarScoped(ProjectName, normalizedName, processedValue);
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
