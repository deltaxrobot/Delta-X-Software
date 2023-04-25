#include "encoder.h"

Encoder::Encoder(QString COM, int baudrate, bool is_open, QObject *parent) : Device(COM, baudrate, "M316 0", "Ok", is_open, parent)
{
    qDebug() << "Encoder init";
    connect(this, SIGNAL(receivedMsg(QString, QString)), this, SLOT(ProcessResponse(QString, QString)));

    jsonObject["device"] = "encoder";
}

void Encoder::ProcessResponse(QString id, QString response)
{
    if (response.contains("P"))
    {
        float value = response.mid(1).toFloat();
        emit GotPosition(ID(), value);
    }
}
