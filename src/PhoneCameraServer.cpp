#include "PhoneCameraServer.h"
#include <QBuffer>
#include <QDateTime>
#include <QFile>
#include <QImageReader>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslKey>
#include <QSslSocket>
#include <QUrl>
#include <QUuid>

PhoneCameraServer::PhoneCameraServer(QObject* parent) : QTcpServer(parent)
{
    // Timers must follow this object when Camera moves to its worker thread.
    m_timeout.setParent(this);
    m_heartbeat.setParent(this);
    m_timeout.setSingleShot(true);
    m_timeout.setInterval(3500);
    m_heartbeat.setSingleShot(true);
    m_heartbeat.setInterval(6000);
    connect(&m_timeout, &QTimer::timeout, this,
            [this]
            {
                if (!m_pending)
                    return;
                m_pending = false;
                emit frameFailed(m_request, m_tracking, "Phone camera capture timed out");
            });
    connect(&m_heartbeat, &QTimer::timeout, this,
            [this]
            {
                m_client.clear();
                if (m_pending)
                {
                    m_pending = false;
                    m_timeout.stop();
                    emit frameFailed(m_request, m_tracking, "Phone disconnected");
                }
                emit pairedChanged(false);
                emit statusChanged("Phone disconnected. Use Load Camera to pair again.");
            });
}

bool PhoneCameraServer::start(const QHostAddress& address, quint16 port, const QString& certificate,
                              const QString& key, QString* error)
{
    auto fail = [&](QString text)
    {
        if (error)
            *error = text;
        return false;
    };
    if (!QSslSocket::supportsSsl())
        return fail("TLS support is unavailable. Install a Qt TLS backend.");
    if (certificate.isEmpty() || key.isEmpty())
        return fail("Create or select certificates in HTTPS Setup first.");
    QFile certFile(certificate), keyFile(key);
    if (!certFile.open(QIODevice::ReadOnly) || !keyFile.open(QIODevice::ReadOnly))
        return fail("Choose a readable PEM certificate and private key in HTTPS Setup.");
    const auto certs = QSslCertificate::fromData(certFile.readAll());
    const auto keyBytes = keyFile.readAll();
    QSslKey privateKey(keyBytes, QSsl::Rsa);
    if (privateKey.isNull())
        privateKey = QSslKey(keyBytes, QSsl::Ec);
    if (certs.isEmpty() || privateKey.isNull())
        return fail("Invalid PEM certificate or unencrypted RSA/EC private key.");
    if (certs.first().effectiveDate() > QDateTime::currentDateTimeUtc())
        return fail("The HTTPS certificate is not yet valid. Check the computer clock.");
    if (certs.first().expiryDate() < QDateTime::currentDateTimeUtc())
        return fail("The HTTPS certificate has expired.");
    if (!certs.first()
             .subjectAlternativeNames()
             .values(QSsl::IpAddressEntry)
             .contains(address.toString()))
        return fail("Certificate does not cover this network IP. Select the original interface or "
                    "create new certificates.");
    stop();
    m_tls = QSslConfiguration::defaultConfiguration();
    m_tls.setLocalCertificateChain(certs);
    m_tls.setPrivateKey(privateKey);
    m_tls.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_tls.setProtocol(QSsl::TlsV1_2OrLater);
    m_token =
        QUuid::createUuid().toString(QUuid::Id128) + QUuid::createUuid().toString(QUuid::Id128);
    if (!listen(address, port))
    {
        m_token.clear();
        return fail(errorString());
    }
    emit statusChanged("Waiting for phone. Scan the QR on the same Wi-Fi.");
    return true;
}
void PhoneCameraServer::stop()
{
    close();
    m_token.clear();
    m_client.clear();
    m_timeout.stop();
    m_heartbeat.stop();
    if (m_pending)
    {
        m_pending = false;
        emit frameFailed(m_request, m_tracking, "Phone camera stopped");
    }
    const auto sockets = findChildren<QSslSocket*>();
    for (auto* socket : sockets)
        socket->abort();
    emit pairedChanged(false);
    emit statusChanged("Phone camera stopped");
}
QString PhoneCameraServer::pairingUrl() const
{
    if (!isListening())
        return {};
    return QString("https://%1:%2/#%3")
        .arg(serverAddress().toString())
        .arg(serverPort())
        .arg(m_token);
}
bool PhoneCameraServer::requestFrame(quint64 request, int tracking)
{
    if (!paired() || m_pending)
        return false;
    m_pending = true;
    m_request = request;
    m_tracking = tracking;
    ++m_sequence;
    m_timeout.start();
    return true;
}
void PhoneCameraServer::incomingConnection(qintptr descriptor)
{
    auto* socket = new QSslSocket(this);
    if (!socket->setSocketDescriptor(descriptor))
    {
        socket->deleteLater();
        return;
    }
    if (m_connections >= 8)
    {
        socket->abort();
        socket->deleteLater();
        return;
    }
    ++m_connections;
    connect(socket, &QSslSocket::disconnected, this,
            [this, socket]
            {
                --m_connections;
                socket->deleteLater();
            });
    socket->setReadBufferSize(2 * 1024 * 1024 + 16384);
    socket->setSslConfiguration(m_tls);
    QTimer::singleShot(5000, socket, [socket] { socket->abort(); });
    connect(socket, &QSslSocket::readyRead, this,
            [this, socket]
            {
                if (socket->property("answered").toBool())
                    return;
                QByteArray bytes = socket->property("request").toByteArray() + socket->readAll();
                const int split = bytes.indexOf("\r\n\r\n");
                if (split < 0)
                {
                    if (bytes.size() > 8192)
                        respond(socket, 413, "{}");
                    else
                        socket->setProperty("request", bytes);
                    return;
                }
                if (split > 8192)
                {
                    respond(socket, 413, "{}");
                    return;
                }
                const auto header = bytes.left(split);
                qint64 length = 0;
                bool lengthSeen = false;
                for (auto line : header.split('\n'))
                {
                    line = line.trimmed();
                    if (line.toLower().startsWith("transfer-encoding:"))
                    {
                        respond(socket, 400, "{}");
                        return;
                    }
                    if (line.toLower().startsWith("content-length:"))
                    {
                        bool ok = false;
                        length = line.mid(15).trimmed().toLongLong(&ok);
                        if (!ok || length < 0 || length > 2 * 1024 * 1024 || lengthSeen)
                        {
                            respond(socket, 413, "{}");
                            return;
                        }
                        lengthSeen = true;
                    }
                }
                if (bytes.size() < split + 4 + length)
                {
                    socket->setProperty("request", bytes);
                    return;
                }
                socket->setProperty("request", QByteArray());
                handle(socket, header, bytes.mid(split + 4, length));
            });
    socket->startServerEncryption();
}
void PhoneCameraServer::respond(QSslSocket* socket, int status, const QByteArray& body,
                                const QByteArray& type)
{
    socket->setProperty("answered", true);
    socket->write("HTTP/1.1 " + QByteArray::number(status) + " Response\r\nContent-Type: " + type +
                  "\r\nContent-Length: " + QByteArray::number(body.size()) +
                  "\r\nCache-Control: no-store\r\nReferrer-Policy: "
                  "no-referrer\r\nX-Content-Type-Options: nosniff\r\n"
                  "Permissions-Policy: camera=(self), microphone=()\r\nConnection: close\r\n\r\n" +
                  body);
    socket->disconnectFromHost();
}
void PhoneCameraServer::handle(QSslSocket* socket, const QByteArray& header, const QByteArray& body)
{
    const auto lines = header.split('\n');
    const auto start = lines.first().trimmed().split(' ');
    if (start.size() != 3)
    {
        respond(socket, 400, "{}");
        return;
    }
    const auto method = start[0], path = start[1];
    if (method == "GET" && path == "/")
    {
        QFile page(":/phone-camera/index.html");
        if (!page.open(QIODevice::ReadOnly))
        {
            respond(socket, 500, "{}");
            return;
        }
        respond(socket, 200, page.readAll(), "text/html; charset=utf-8");
        return;
    }
    QByteArray authorization, client, sequence, contentType;
    for (auto line : lines)
    {
        line = line.trimmed();
        const int colon = line.indexOf(':');
        if (colon < 0)
            continue;
        const auto name = line.left(colon).toLower(), value = line.mid(colon + 1).trimmed();
        if (name == "authorization")
            authorization = value;
        if (name == "x-phone-client")
            client = value;
        if (name == "x-frame-sequence")
            sequence = value;
        if (name == "content-type")
            contentType = value;
    }
    if (m_token.isEmpty() || authorization != "Bearer " + m_token.toUtf8())
    {
        respond(socket, 401, "{}");
        return;
    }
    if (client.size() < 16 || client.size() > 128)
    {
        respond(socket, 400, "{}");
        return;
    }
    if (path == "/pair" && method == "POST")
    {
        if (!m_client.isEmpty() && m_client != QString::fromLatin1(client))
        {
            respond(socket, 409, "{}");
            return;
        }
        m_client = QString::fromLatin1(client);
        m_heartbeat.start();
        respond(socket, 200, "{}");
        emit pairedChanged(true);
        emit statusChanged("Phone connected");
        return;
    }
    if (m_client.isEmpty() || m_client != QString::fromLatin1(client))
    {
        respond(socket, 409, "{}");
        return;
    }
    if (path == "/stop" && method == "POST")
    {
        respond(socket, 200, "{}");
        m_client.clear();
        m_heartbeat.stop();
        if (m_pending)
        {
            m_pending = false;
            m_timeout.stop();
            emit frameFailed(m_request, m_tracking, "Phone stopped sharing");
        }
        emit pairedChanged(false);
        emit statusChanged("Phone stopped sharing. Use Load Camera to pair again.");
        return;
    }
    if (path == "/next" && method == "GET")
    {
        m_heartbeat.start();
        respond(socket, 200,
                QJsonDocument(
                    QJsonObject{{"sequence", m_pending ? QString::number(m_sequence) : QString()}})
                    .toJson(QJsonDocument::Compact));
        return;
    }
    if (path == "/frame" && method == "POST")
    {
        if (!m_pending || sequence != QByteArray::number(m_sequence))
        {
            respond(socket, 409, "{}");
            return;
        }
        if (contentType != "image/jpeg" || !body.startsWith("\xff\xd8"))
        {
            respond(socket, 415, "{}");
            return;
        }
        QBuffer buffer;
        buffer.setData(body);
        buffer.open(QIODevice::ReadOnly);
        QImageReader reader(&buffer, "jpeg");
        const auto size = reader.size();
        if (size.width() < 1 || size.height() < 1 || size.width() > 1920 || size.height() > 1920 ||
            qint64(size.width()) * size.height() > 2073600)
        {
            respond(socket, 413, "{}");
            return;
        }
        const QImage image = reader.read();
        if (image.isNull())
        {
            respond(socket, 422, "{}");
            return;
        }
        m_pending = false;
        m_timeout.stop();
        m_heartbeat.start();
        respond(socket, 200, "{}");
        emit frameReady(image, m_request, m_tracking);
        return;
    }
    respond(socket, 404, "{}");
}
