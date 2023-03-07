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

class Device : public QObject
{
    Q_OBJECT

public:
    explicit Device(QString COM = "auto", int baudrate = 115200, QString confirm_cmd = "", QString rev_msg = "Ok", bool is_open = true, QObject *parent = nullptr);
    ~Device();

signals:
    void receivedMsg(QString);

public slots:
    void Run();
    void Connect(QString port = "COM1", int baudrate = 115200, bool autoRead = false);

    void Delay(int msec);

    QString GetResponse(int timeout = 2000);
    void ReadData();
    QString ReadLine();
    QString GetSerialPortName();

protected:
    QSerialPort* serialPort;
    QMetaObject::Connection readDataConnection;

private:
    QString serialPortName;
    int baudrate;
    QString confirmRequest;
    QString confirmResponse;
    QString feedback;


};

#endif // DEVICE_H
