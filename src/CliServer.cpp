#include "CliServer.h"
#include "CliProtocol.h"
#include <QTimer>

CliServer::CliServer(QObject* parent) : QObject(parent)
{
    m_server.setSocketOptions(QLocalServer::UserAccessOption);
    connect(&m_server, &QLocalServer::newConnection, this, [this]() {
        while (m_server.hasPendingConnections()) {
            auto* socket = m_server.nextPendingConnection();
            socket->setParent(this);
            if (m_connections >= 16) {
                socket->abort();
                socket->deleteLater();
                continue;
            }
            ++m_connections;
            socket->setReadBufferSize(CliProtocol::MaxMessageBytes + 1);
            auto* timer = new QTimer(socket);
            timer->setSingleShot(true);
            timer->start(5000);
            connect(timer, &QTimer::timeout, socket, &QLocalSocket::abort);
            connect(socket, &QLocalSocket::disconnected, this, [this, socket]() {
                --m_connections;
                socket->deleteLater();
            });
            connect(socket, &QLocalSocket::readyRead, this, [this, socket, timer]() {
                if (socket->property("requested").toBool()) {
                    socket->abort(); // No second request on a streaming connection.
                    return;
                }
                if (socket->bytesAvailable() > CliProtocol::MaxMessageBytes) {
                    reply(socket, {{"event", "error"}, {"message", "Request is too large"}}, true);
                    return;
                }
                if (!socket->canReadLine())
                    return;
                timer->stop();
                socket->setProperty("requested", true);
                QJsonParseError error;
                const auto document = QJsonDocument::fromJson(socket->readLine(), &error);
                if (error.error != QJsonParseError::NoError || !document.isObject() ||
                    socket->bytesAvailable() != 0 || document.object().value("version").toInt() != 1) {
                    reply(socket, {{"event", "error"}, {"message", "Invalid CLI v1 request"}}, true);
                    return;
                }
                emit requestReceived(socket, document.object());
            });
        }
    });
}

bool CliServer::listen(const QString& name, QString* error)
{
    // The process lock allows recovery of a stale Unix socket without removing
    // an endpoint still owned by another application instance.
    const auto key = QCryptographicHash::hash(name.toUtf8(), QCryptographicHash::Sha256).toHex();
    m_lock = std::make_unique<QLockFile>(QDir::tempPath() + "/deltax-cli-" + key + ".lock");
    if (!m_lock->tryLock(0)) {
        if (error) *error = "CLI endpoint is already owned by another Delta X instance";
        return false;
    }
    QLocalServer::removeServer(name);
    if (m_server.listen(name))
        return true;
    if (error) *error = m_server.errorString();
    m_lock->unlock();
    return false;
}

CliServer::~CliServer()
{
    m_server.close();
    // Disconnect child socket callbacks while this object's fields still exist.
    for (auto* socket : findChildren<QLocalSocket*>(QString(), Qt::FindDirectChildrenOnly)) {
        socket->disconnect(this);
        delete socket;
    }
}

void CliServer::reply(QLocalSocket* socket, const QJsonObject& message, bool final)
{
    if (socket->state() != QLocalSocket::ConnectedState)
        return;
    // A client that stops reading must not grow the application's memory forever.
    if (socket->bytesToWrite() > CliProtocol::MaxMessageBytes) {
        socket->abort();
        return;
    }
    socket->write(CliProtocol::encode(message));
    if (final)
        socket->disconnectFromServer();
}
