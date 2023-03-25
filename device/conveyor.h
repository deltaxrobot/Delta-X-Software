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
};

#endif // CONVEYOR_H
