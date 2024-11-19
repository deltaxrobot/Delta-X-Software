#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "device.h"
#include <QObject>

class Conveyor : public Device
{
    Q_OBJECT
public:
    explicit Conveyor(QString COM = "auto", int baudrate = 115200, bool is_open = true, QObject *parent = nullptr);
    ~Conveyor();

    void SetType(QString type);
    QString GetType();    

    float Position = 0;

public slots:
    QString GetInfo();
    void ProcessResponse(QString idName, QString response = "");

signals:
    void GotEncoderPosition(int id, float position);

private:
    QString type;
};

#endif // CONVEYOR_H
