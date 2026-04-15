#ifndef VIRTUALDEVICESERVER_H
#define VIRTUALDEVICESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <functional>

class VirtualDeviceServer : public QObject
{
    Q_OBJECT

public:
    using ResponseSender = std::function<void(const QString &)>;
    using LineHandler = std::function<void(const QString &, ResponseSender)>;

    explicit VirtualDeviceServer(const QString &deviceName, quint16 defaultPort, QObject *parent = nullptr);

    void setLineHandler(LineHandler handler);
    bool start(quint16 port = 0);
    void stop();

    QString deviceName() const;
    quint16 defaultPort() const;
    quint16 port() const;
    bool isListening() const;
    int clientCount() const;

signals:
    void logMessage(const QString &message);
    void clientCountChanged(int clientCount);

private slots:
    void handleNewConnection();
    void handleReadyRead();
    void handleDisconnected();
    void handleSocketError(QAbstractSocket::SocketError socketError);

private:
    void sendLine(QTcpSocket *socket, const QString &line);

    QString m_deviceName;
    quint16 m_defaultPort;
    QTcpServer m_server;
    QList<QTcpSocket *> m_clients;
    QHash<QTcpSocket *, QByteArray> m_buffers;
    LineHandler m_handler;
};

#endif // VIRTUALDEVICESERVER_H
