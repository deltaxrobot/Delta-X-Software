#ifndef SOCKETCONNECTIONMANAGER_H
#define SOCKETCONNECTIONMANAGER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QImage>
#include <QBuffer>
#include <QMetaObject>
#include <QNetworkInterface>
#include <VariableManager.h>
#include <opencv2/opencv.hpp>
#include <QFile>

class SocketConnectionManager : public QObject
{
    Q_OBJECT

public:
    QTcpServer* Server;
    QTcpServer* WebServer;
    QList<QTcpSocket*> clients;
    QString hostAddress;
    int port;

    QString ProjectName = "project0";

    int imageSendingMethod = 0;
    QString indexPath = "index.html";

    ~SocketConnectionManager();
    bool IsServerOpen();
    static QString printLocalIpAddresses();

public:
    SocketConnectionManager(const QString& address = "127.0.0.1", int port = 12345, QObject* parent = nullptr);
    bool Connect(QString address = "127.0.0.1", int port = 8844);

private slots:
    void newClientConnected();
    void newWebClientConnected();

    void readFromClient();

public slots:
    void sendImageToImageClients(const QImage& image);
    void sendImageToImageClients(cv::Mat);
    void sendImageToExternalScript(cv::Mat input);

signals:
    void variableChanged(const QString& varName, const QVariant& value);
    void objectUpdated(QString listName, QList<QStringList> list);
    void blobUpdated(QStringList blobs);
    void gcodeReceived(QString gcode);
    void eventReceived(QString type, QString name, QString action);
};

#endif // SOCKETCONNECTIONMANAGER_H
