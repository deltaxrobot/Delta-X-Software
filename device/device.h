#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTcpSocket>
#include <QIODevice>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include <QTime>
#include <QElapsedTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QThread>
#include <QString>

class Device : public QObject
{
    Q_OBJECT

public:
    enum class ConnectionType { None, Serial, Socket };

    explicit Device(QString COM = "auto", int baudrate = 115200, QString confirm_cmd = "", QString rev_msg = "Ok", bool is_open = true, QObject *parent = nullptr);
    ~Device();

    void SetSerialPortName(QString name);
    QString GetSerialPortName();
    int GetSerialPortBaudrate();
    bool IsOpen();
    int ID();
    void SetIDName(QString idName);
    QSerialPort* GetPort();
    // Optional: set socket endpoint explicitly
    void SetSocketAddress(const QString& host, int port);
    ConnectionType connectionType() const { return connType; }
    // Block or unblock IO device signals (serial or socket)
    void BlockIODeviceSignals(bool block);

    void MoveToThread(QThread* thread);

    QString ProjectName = "project0";

    bool IsGcodeDone = true;

    static QElapsedTimer DebugTimer;

signals:
    void receivedMsg(QString idName, QString);
    void infoReady(QString infoJson);

public slots:
    void Run();
    void Connect();
    void Disconnect();

    void Delay(int msec);

    QString GetResponse(int timeout = 2000);
    void WriteData(QString data);
    void ReadData();
    QString ReadLine();

protected:
    QSerialPort* serialPort = nullptr;
    QTcpSocket* tcpSocket = nullptr;
    QMetaObject::Connection readDataConnection;
    QJsonObject jsonObject;
    QString idName;

private:
    QString serialPortName;
    int baudrate;
    QString confirmRequest;
    QString confirmResponse;
    QString feedback;
    QString rxBuffer; // line buffer for partial reads (serial/socket)
    // Socket endpoint
    QString hostName;
    int tcpPort = 0;
    ConnectionType connType = ConnectionType::None;

    QIODevice* activeIODevice() const;
};

#endif // DEVICE_H
