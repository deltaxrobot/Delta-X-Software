#include "device.h"

QElapsedTimer Device::DebugTimer;

Device::Device(QString COM, int baudrate, QString confirm_cmd, QString rev_msg, bool is_open, QObject *parent) : QObject(parent),
    serialPortName(COM), baudrate(baudrate), confirmRequest(confirm_cmd), confirmResponse(rev_msg)
{

    jsonObject["device"] = "device";

    if (is_open == true) {
        Run();
    }
}

Device::~Device()
{
//    if (serialPort != NULL)
//        if (serialPort->isOpen())
//            serialPort->close();

//    delete serialPort;
}

void Device::SetSerialPortName(QString name)
{
    serialPortName = name;
}

void Device::Connect()
{
    if (serialPort == nullptr)
    {
        serialPort = new QSerialPort();
    }

    if (serialPort->isOpen())
        return;

    if (serialPortName.toLower() == "auto" && confirmRequest != "")
    {
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

        for (int i = 0; i < availablePorts.size(); ++i)
        {
            QString portName = availablePorts.at(i).portName();
            serialPort->setPortName(portName);
            serialPort->setBaudRate(baudrate);

            if (serialPort->open(QIODevice::ReadWrite))
            {
                int counter = 0;
                QThread::msleep(500);
                serialPort->blockSignals(true);
                serialPort->write((confirmRequest + "\n").toLocal8Bit());
                serialPort->waitForReadyRead(500);
                QString response = QString(serialPort->readLine());
                if (response.contains("Init"))
                {
                    response = QString(serialPort->readLine());
                }
                if (response.indexOf(confirmResponse) > -1) {
                    qDebug() << availablePorts.at(i).portName() << "is connected";
                    readDataConnection = connect(serialPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
                    serialPort->blockSignals(false);
//                    serialPort->readAll();
                    break;
                }
                else
                {
                    serialPort->blockSignals(false);
                    serialPort->close();
                    continue;
                }

            }
        }
    }

    if (serialPortName.toLower() != "auto")
    {
        serialPort->setPortName(serialPortName);
        serialPort->setBaudRate(baudrate);

        if (serialPort->open(QIODevice::ReadWrite))
        {
//            qDebug() << serialPortName << "is connected";
            readDataConnection = connect(serialPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
        }
        else
        {
//            qDebug() << serialPortName << "is not connected";
        }
    }

    jsonObject["id"] = ID();
    jsonObject["state"] = (serialPort->isOpen())?"open":"close";
    jsonObject["com_name"] = serialPort->portName();
    jsonObject["baudrate"] = serialPort->baudRate();
    jsonObject["gcode"] = "connect";

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);
    emit infoReady(jsonString);

}

void Device::Disconnect()
{
    if (serialPort->isOpen())
    {
        serialPort->close();
        jsonObject["state"] = "close";

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);
        emit infoReady(jsonString);
    }
}

void Device::Delay(int msec) {
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

QString Device::GetResponse(int timeout_ms) {
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() < timeout_ms) {
        serialPort->waitForReadyRead(1);
        if (serialPort->canReadLine() == true) {
            break;
        }
    }

    return ReadLine();
}

void Device::WriteData(QString data)
{
    if (serialPort == nullptr)
    {
        return;
    }

    if (!data.endsWith("\n"))
        data.append("\n");

//    qDebug() << "Write time:" << DebugTimer.elapsed();
//    qDebug() << data;
    if (this->serialPort->isOpen())
    {
        IsGcodeDone = false;
        this->serialPort->write(data.toLocal8Bit());
    }
}

void Device::ReadData()
{
    if (serialPort->canReadLine())
    {
        ReadLine();
    }
}

QString Device::ReadLine(){
    QString data = QString(serialPort->readAll());
    QStringList lines = data.split("\n");
    foreach(QString line, lines)
    {
        line.replace("\n", "").replace("\r", "");

        if (line == "")
            continue;

        IsGcodeDone = true;
        emit receivedMsg(idName, line);
    }
    return data;
}

QString Device::GetSerialPortName()
{
    return serialPortName;
}

int Device::GetSerialPortBaudrate()
{
    return baudrate;
}

bool Device::IsOpen()
{
    if (serialPort == nullptr)
    {
        serialPort = new QSerialPort();
    }

    return serialPort->isOpen();
}

int Device::ID()
{    
    QString num = idName.right(idName.length() - idName.indexOf(QRegExp("\\d")));
    int value = num.toInt();
    return value;
}

void Device::SetIDName(QString idName)
{
    this->idName = idName;
    jsonObject["id"] = ID();
}

QSerialPort *Device::GetPort()
{
    return serialPort;
}

void Device::MoveToThread(QThread *thread)
{
    serialPort->setParent(nullptr);
    this->moveToThread(thread);
    serialPort->moveToThread(thread);
    serialPort->setParent(this);
}

void Device::Run()
{
//    qDebug() << "Device run";

    feedback  = "";
}
