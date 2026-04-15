#include "conveyor.h"

Conveyor::Conveyor(QString COM, int baudrate, bool is_open, QObject *parent) : Device(COM, baudrate, "M310 1", "Ok", is_open, parent)
{
//    qDebug() << "Conveyor init";

    jsonObject["device"] = "conveyor";

    connect(this, SIGNAL(receivedMsg(QString, QString)), this, SLOT(ProcessResponse(QString, QString)));

}

Conveyor::~Conveyor()
{

}

QString Conveyor::GetInfo()
{
    jsonObject["id_name"] = idName;
    jsonObject["id"] = ID();

    jsonObject["type"] = type;

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);

    emit infoReady(jsonString);

    return jsonString;
}

void Conveyor::ProcessResponse(QString idName, QString response)
{
    if (response.contains("P"))
    {
        int id = response.mid(1,1).toInt() - 1;
        if (id < 0)
            id = 0;
        float value = response.mid(3).toFloat();

        Position = value;

        emit GotEncoderPosition(id, value);
    }
}
