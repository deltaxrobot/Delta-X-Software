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
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>

class SocketConnectionManager : public QObject
{
    Q_OBJECT

public:
    QTcpServer* Server = nullptr;
    QTcpServer* WebServer = nullptr;
    QTcpServer* BlocklyServer = nullptr;
    QList<QTcpSocket*> clients;
    QString hostAddress;
    int port;

    QString ProjectName = "project0";

    int imageSendingMethod = 0;
    QString indexPath = "Jogging.html";
    quint16 blocklyPort = 0;
    QString latestGscript;

    ~SocketConnectionManager();
    bool IsServerOpen();
    static QString printLocalIpAddresses();

public:
    SocketConnectionManager(const QString& address = "127.0.0.1", int port = 12345, QObject* parent = nullptr);
    bool Connect(QString address = "127.0.0.1", int port = 8844);
    void setIndexFileName(const QString &fileName);

private:
    QString resolveIndexFile(const QString &fileName) const;
    bool extractAssignment(const QString &data, QString &varName, QString &value) const;
    void handleAssignment(const QString &varName, QString value);
    bool startBlocklyServer(quint16 startPort = 5050);

private slots:
    void newClientConnected();
    void newWebClientConnected();
    void newBlocklyClientConnected();

    void readFromClient();
    void processWebPostData(const QString& data);

public slots:
    void sendImageToImageClients(const QImage& image);
    void sendImageToImageClients(cv::Mat);
    void sendImageToExternalScript(cv::Mat input);
    void updateLatestGscript(const QString& script);

signals:
    void variableChanged(const QString& varName, const QVariant& value);
    void objectUpdated(QString listName, QList<QStringList> list);
    void blobUpdated(QStringList blobs);
    void gcodeReceived(QString gcode);
    void gscriptEditorReceived(QString gcode);
    void eventReceived(QString type, QString name, QString action);

private:
    void sendImageAsJson(cv::Mat mat);
};

#endif // SOCKETCONNECTIONMANAGER_H
