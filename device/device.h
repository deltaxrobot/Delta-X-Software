#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include <QTime>
#include <QElapsedTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Device : public QObject
{
    Q_OBJECT

public:
    explicit Device(QString COM = "auto", int baudrate = 115200, QString confirm_cmd = "", QString rev_msg = "Ok", bool is_open = true, QObject *parent = nullptr);
    ~Device();

signals:
    void receivedMsg(QString);
    void gcodeDone(QString id, QString response);
    void infoReady(QString infoJson);

public slots:
    void Run();
    void Connect();
    void Disconnect();

    void Delay(int msec);

    QString GetResponse(int timeout = 2000);
    void ReadData();
    QString ReadLine();
    QString GetSerialPortName();
    int GetSerialPortBaudrate();
    bool IsOpen();
    QString ID();
    void SetID(QString);

protected:
    QSerialPort* serialPort;
    QMetaObject::Connection readDataConnection;
    QJsonObject jsonObject;
    QString id;

private:
    QString serialPortName;
    int baudrate;
    QString confirmRequest;
    QString confirmResponse;
    QString feedback;
};

#endif // DEVICE_H
