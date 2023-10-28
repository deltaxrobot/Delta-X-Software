#ifndef SOCKETCONNECTIONMANAGER_H
#define SOCKETCONNECTIONMANAGER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QImage>
#include <QBuffer>
#include <QMetaObject>

class SocketConnectionManager : public QObject
{
    Q_OBJECT

public:
    QTcpServer* server;
    QList<QTcpSocket*> clients;
    QString hostAddress;
    int port;

    bool IsServerOpen();

public:
    SocketConnectionManager(const QString& address = "127.0.0.1", int port = 12345, QObject* parent = nullptr);
    bool Connect(QString address = "127.0.0.1", int port = 8844);
private slots:
    void newClientConnected();

    void readFromClient();

public slots:
    void sendImageToImageClients(const QImage& image);

signals:
    void variableChanged(const QString& varName, const QVariant& value);
};

#endif // SOCKETCONNECTIONMANAGER_H
