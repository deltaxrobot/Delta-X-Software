#include "VirtualDeviceServer.h"

#include <QHostAddress>
#include <QPointer>
#include <utility>

VirtualDeviceServer::VirtualDeviceServer(const QString &deviceName, quint16 defaultPort, QObject *parent)
    : QObject(parent)
    , m_deviceName(deviceName)
    , m_defaultPort(defaultPort)
{
    connect(&m_server, &QTcpServer::newConnection, this, &VirtualDeviceServer::handleNewConnection);
}

void VirtualDeviceServer::setLineHandler(LineHandler handler)
{
    m_handler = std::move(handler);
}

bool VirtualDeviceServer::start(quint16 port)
{
    const quint16 requestedPort = port == 0 ? m_defaultPort : port;
    if (m_server.isListening()) {
        if (m_server.serverPort() == requestedPort)
            return true;
        stop();
    }

    const bool ok = m_server.listen(QHostAddress::LocalHost, requestedPort);
    if (ok) {
        emit logMessage(QString("[%1] listening on 127.0.0.1:%2").arg(m_deviceName).arg(m_server.serverPort()));
    } else {
        emit logMessage(QString("[%1] failed to listen on 127.0.0.1:%2: %3")
                            .arg(m_deviceName)
                            .arg(requestedPort)
                            .arg(m_server.errorString()));
    }
    return ok;
}

void VirtualDeviceServer::stop()
{
    for (QTcpSocket *socket : std::as_const(m_clients)) {
        socket->disconnect(this);
        socket->disconnectFromHost();
        if (socket->state() != QAbstractSocket::UnconnectedState)
            socket->waitForDisconnected(100);
        socket->deleteLater();
    }
    m_clients.clear();
    m_buffers.clear();

    if (m_server.isListening()) {
        emit logMessage(QString("[%1] stopped listening on port %2").arg(m_deviceName).arg(m_server.serverPort()));
        m_server.close();
    }

    emit clientCountChanged(0);
}

QString VirtualDeviceServer::deviceName() const
{
    return m_deviceName;
}

quint16 VirtualDeviceServer::defaultPort() const
{
    return m_defaultPort;
}

quint16 VirtualDeviceServer::port() const
{
    return m_server.isListening() ? m_server.serverPort() : 0;
}

bool VirtualDeviceServer::isListening() const
{
    return m_server.isListening();
}

int VirtualDeviceServer::clientCount() const
{
    return m_clients.count();
}

void VirtualDeviceServer::handleNewConnection()
{
    while (m_server.hasPendingConnections()) {
        QTcpSocket *socket = m_server.nextPendingConnection();
        if (!socket)
            continue;

        m_clients.append(socket);
        m_buffers.insert(socket, QByteArray());

        connect(socket, &QTcpSocket::readyRead, this, &VirtualDeviceServer::handleReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &VirtualDeviceServer::handleDisconnected);
        connect(socket,
                qOverload<QAbstractSocket::SocketError>(&QTcpSocket::errorOccurred),
                this,
                &VirtualDeviceServer::handleSocketError);

        emit logMessage(QString("[%1] client connected from %2:%3")
                            .arg(m_deviceName)
                            .arg(socket->peerAddress().toString())
                            .arg(socket->peerPort()));
        emit clientCountChanged(m_clients.count());
    }
}

void VirtualDeviceServer::handleReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;

    QByteArray &buffer = m_buffers[socket];
    buffer.append(socket->readAll());

    int newlineIndex = -1;
    while ((newlineIndex = buffer.indexOf('\n')) != -1) {
        QByteArray rawLine = buffer.left(newlineIndex);
        buffer.remove(0, newlineIndex + 1);

        QString line = QString::fromUtf8(rawLine).trimmed();
        if (line.isEmpty())
            continue;

        emit logMessage(QString("[%1] <= %2").arg(m_deviceName, line));
        QPointer<QTcpSocket> guardedSocket(socket);
        const ResponseSender respond = [this, guardedSocket](const QString &response) {
            if (!guardedSocket || response.isEmpty())
                return;
            sendLine(guardedSocket.data(), response);
        };
        if (m_handler) {
            m_handler(line, respond);
        } else {
            respond(QStringLiteral("Ok"));
        }
    }
}

void VirtualDeviceServer::handleDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;

    emit logMessage(QString("[%1] client disconnected from %2:%3")
                        .arg(m_deviceName)
                        .arg(socket->peerAddress().toString())
                        .arg(socket->peerPort()));

    m_clients.removeAll(socket);
    m_buffers.remove(socket);
    socket->deleteLater();
    emit clientCountChanged(m_clients.count());
}

void VirtualDeviceServer::handleSocketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;

    emit logMessage(QString("[%1] socket error from %2:%3: %4")
                        .arg(m_deviceName)
                        .arg(socket->peerAddress().toString())
                        .arg(socket->peerPort())
                        .arg(socket->errorString()));
}

void VirtualDeviceServer::sendLine(QTcpSocket *socket, const QString &line)
{
    if (!socket)
        return;

    QByteArray payload = line.toUtf8();
    payload.append('\n');
    socket->write(payload);
    socket->flush();

    emit logMessage(QString("[%1] => %2").arg(m_deviceName, line));
}
