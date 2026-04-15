#include "ComDevice.h"

COMDevice::COMDevice(QWidget *parent) : QWidget(parent)
{
    COMPort = new QSerialPort();
    connect(COMPort, SIGNAL(readyRead()), this, SLOT(ReadData()));

}

bool COMDevice::Connect()
{
    if (COMPort->isOpen() == true)
    {
        COMPort->close();
        return false;
    }

    QStringList items;

    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
    {
        items << portInfo.portName() + " - " + portInfo.description();
    }

    bool ok;
    QString item = QInputDialog::getItem(this, tr("COM Connection"), tr("COM Ports:"), items, 0, false, &ok);
    QString comName = item.mid(0, item.indexOf(" - "));

    if (ok && !item.isEmpty())
    {
        bool ok2;
        QString baudrate = QInputDialog::getText(this, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, QString::number(DefaultBaudrate), &ok2);
        if (ok2 && !baudrate.isEmpty())
        {
            Baudrate = baudrate.toInt();
            COMPort->setPortName(comName);
            COMPort->setBaudRate(Baudrate);

            if (COMPort->open((QIODevice::ReadWrite)) == true)
            {
                return true;
            }
        }
    }

    return false;
}

void COMDevice::Send(QString msg)
{
    if (msg[msg.length() - 1] != "\n")
        msg += "\n";

    if (COMPort != NULL)
    {
        if (COMPort->isOpen())
        {
            COMPort->write(msg.toStdString().c_str(), msg.size());
        }
    }
}

void COMDevice::ReadData()
{
    IOSender = qobject_cast<QIODevice*>(sender());

    QSerialPort* sP = qobject_cast<QSerialPort*>(sender());

    if (sP)
    {
        while (sP->canReadLine())
        {
            receiveLine = sP->readLine();

            emit FinishedReadLine(receiveLine);
        }

        return;
    }
}
