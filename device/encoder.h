#ifndef ENCODER_H
#define ENCODER_H

#include "device.h"
#include <QObject>

class Encoder : public Device
{
    Q_OBJECT
public:
    explicit Encoder(QString COM = "auto", int baudrate = 115200, bool is_open = true, QObject *parent = nullptr);

signals:
    void GotPosition(int id, float value);
public slots:
    void ProcessResponse(QString id, QString response = "");
};

#endif // ENCODER_H
