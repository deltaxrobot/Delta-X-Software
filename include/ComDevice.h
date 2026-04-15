#ifndef COMDEVICE_H
#define COMDEVICE_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QInputDialog>

class COMDevice : public QWidget
{
    Q_OBJECT
public:
    explicit COMDevice(QWidget *parent = nullptr);
    bool Connect();
    void Send(QString msg);
    
    QSerialPort* COMPort;
    QIODevice* IOSender;
    int DefaultBaudrate = 115200;
    int Baudrate = 115200;

public slots:
    void ReadData();

signals:
    void FinishedReadLine(QString msg);

private:
    QString receiveLine;
    QString transmitLine;
    QList<QString> transmitLines;
    QTimer* connectionTimer;
    QList<QSerialPort*> portList;

};

#endif // COMDEVICE_H
