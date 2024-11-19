#include "slider.h"

Slider::Slider(QString COM, int baudrate, bool is_open, QObject *parent) : Device(COM, baudrate, "M323", "Ok", is_open, parent)
{
//    qDebug() << "Slider init";
    connect(this, SIGNAL(receivedMsg(QString, QString)), this, SLOT(ProcessResponse(QString, QString)));

}

void Slider::ProcessResponse(QString id, QString response)
{
//    qDebug() << response;
}

QString Slider::SendGcode(QString gcode, bool is_wait, int time_out)
{
    if (!gcode.endsWith("\n"))
        gcode.append("\n");

//    qDebug() << gcode;

    if (this->serialPort->isOpen())
        this->serialPort->write(gcode.toLocal8Bit());

    if (is_wait)
    {
        serialPort->blockSignals(true);

        QString response = this->GetResponse(time_out);
//        qDebug() << response;
        serialPort->blockSignals(false);
        return response;
    }
    else
    {

    }

    return "";
}
