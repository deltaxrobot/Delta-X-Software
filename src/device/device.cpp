#include "device.h"
#include <QRegularExpression>

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
    if (tcpSocket) {
        if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
            tcpSocket->disconnectFromHost();
            tcpSocket->waitForDisconnected(100);
        }
    }
    if (serialPort) {
        if (serialPort->isOpen()) {
            serialPort->close();
        }
    }
}

void Device::SetSerialPortName(QString name)
{
    serialPortName = name;
    // Detect and parse optional socket endpoint formatted as "host:port" or "tcp://host:port"
    QString n = name.trimmed();
    if (n.startsWith("tcp://", Qt::CaseInsensitive)) {
        n = n.mid(6);
    }
    int idx = n.indexOf(':');
    if (idx > 0 && !n.startsWith("COM", Qt::CaseInsensitive)) {
        hostName = n.left(idx);
        bool ok = false;
        int p = n.mid(idx + 1).toInt(&ok);
        if (ok) {
            tcpPort = p;
        }
    }
}

void Device::Connect()
{
    // Determine if this should be a socket connection based on provided name
    bool looksLikeSocket = false;
    QString n = serialPortName.trimmed();
    if (n.startsWith("tcp://", Qt::CaseInsensitive)) n = n.mid(6);
    int idx = n.indexOf(':');
    if (idx > 0 && !n.startsWith("COM", Qt::CaseInsensitive)) {
        looksLikeSocket = true;
        if (hostName.isEmpty()) hostName = n.left(idx);
        if (tcpPort == 0) tcpPort = n.mid(idx + 1).toInt();
    }

    if (looksLikeSocket && !hostName.isEmpty() && tcpPort > 0) {
        if (tcpSocket == nullptr) {
            tcpSocket = new QTcpSocket(this);
        }
        if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
            connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));
            tcpSocket->connectToHost(hostName, tcpPort);
            tcpSocket->waitForConnected(500);
        }
        connType = ConnectionType::Socket;

        jsonObject["id"] = ID();
        jsonObject["state"] = (tcpSocket->state() == QAbstractSocket::ConnectedState)?"open":"close";
        jsonObject["com_name"] = hostName + ":" + QString::number(tcpPort);
        jsonObject["baudrate"] = 0;
        jsonObject["gcode"] = "connect";

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);
        emit infoReady(jsonString);
        return;
    }

    // Serial path (default)
    if (serialPort == nullptr)
    {
        serialPort = new QSerialPort(this);
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
                QThread::msleep(500);
                serialPort->blockSignals(true);
                serialPort->write((confirmRequest + "\n").toLocal8Bit());
                serialPort->waitForReadyRead(200);
                QString response = QString(serialPort->readLine());
                if (response.contains("Init"))
                {
                    serialPort->write((confirmRequest + "\n").toLocal8Bit());
                    serialPort->waitForReadyRead(200);
                    response = QString(serialPort->readLine());
                }
                if (response.indexOf(confirmResponse) > -1) {
                    qDebug() << availablePorts.at(i).portName() << "is connected";
                    readDataConnection = connect(serialPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
                    serialPort->blockSignals(false);
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
            readDataConnection = connect(serialPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
        }
        else
        {
        }
    }

    connType = ConnectionType::Serial;

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
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        tcpSocket->disconnectFromHost();
        if (tcpSocket->state() != QAbstractSocket::UnconnectedState)
            tcpSocket->waitForDisconnected(200);
        jsonObject["state"] = "close";

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);
        emit infoReady(jsonString);
        connType = ConnectionType::None;
    }
    if (serialPort && serialPort->isOpen())
    {
        serialPort->close();
        jsonObject["state"] = "close";

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);
        emit infoReady(jsonString);
        connType = ConnectionType::None;
    }
}

void Device::Delay(int msec) {
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

QString Device::GetResponse(int timeout_ms) {
    QIODevice* dev = activeIODevice();
    if (!dev) return QString();
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() < timeout_ms) {
        dev->waitForReadyRead(1);
        if (dev->canReadLine()) {
            break;
        }
    }
    return ReadLine();
}

void Device::WriteData(QString data)
{
    if (!data.endsWith("\n"))
        data.append("\n");

//    qDebug() << "Write time:" << DebugTimer.elapsed();
    QIODevice* dev = activeIODevice();
    if (!dev) return;
    IsGcodeDone = false;
    dev->write(data.toLocal8Bit());
}

void Device::ReadData()
{
    QIODevice* dev = activeIODevice();
    if (!dev) return;
    QByteArray chunk = dev->readAll();
    if (chunk.isEmpty()) return;

    rxBuffer.append(QString::fromLocal8Bit(chunk));

    int idx = -1;
    while ((idx = rxBuffer.indexOf('\n')) != -1) {
        QString line = rxBuffer.left(idx);
        rxBuffer.remove(0, idx + 1);
        line.replace("\r", "");
        if (line.isEmpty()) continue;
        IsGcodeDone = true;
        emit receivedMsg(idName, line);
    }
}

QString Device::ReadLine(){
    QIODevice* dev = activeIODevice();
    if (!dev) return QString();
    QString data = QString(dev->readAll());
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
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::ConnectedState)
        return true;
    if (serialPort == nullptr)
    {
        serialPort = new QSerialPort();
    }
    return serialPort->isOpen();
}

int Device::ID()
{
    QRegularExpression re("\\d+");
    QRegularExpressionMatch match = re.match(idName);
    if (match.hasMatch()) {
        return match.captured(0).toInt();
    }
    return 0;
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
    if (serialPort) serialPort->setParent(nullptr);
    this->moveToThread(thread);
    if (serialPort) {
        serialPort->moveToThread(thread);
        serialPort->setParent(this);
    }
    if (tcpSocket) {
        tcpSocket->setParent(nullptr);
        tcpSocket->moveToThread(thread);
        tcpSocket->setParent(this);
    }
}

void Device::Run()
{
//    qDebug() << "Device run";

    feedback  = "";
}

void Device::SetSocketAddress(const QString &host, int port)
{
    hostName = host;
    tcpPort = port;
}

void Device::BlockIODeviceSignals(bool block)
{
    QIODevice* dev = activeIODevice();
    if (dev) dev->blockSignals(block);
}

QIODevice* Device::activeIODevice() const
{
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::ConnectedState) return tcpSocket;
    if (serialPort && serialPort->isOpen()) return serialPort;
    return nullptr;
}
