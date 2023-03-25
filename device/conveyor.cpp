#include "conveyor.h"

Conveyor::Conveyor(QString COM, int baudrate, bool is_open, QObject *parent) : Device(COM, baudrate, "M310 1", "Ok", is_open, parent)
{
    qDebug() << "Conveyor init";

    jsonObject["device"] = "conveyor";
}

Conveyor::~Conveyor()
{

}
