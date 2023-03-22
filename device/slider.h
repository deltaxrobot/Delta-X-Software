#ifndef SLIDER_H
#define SLIDER_H

#include "device.h"
#include <QObject>
#include <string>
#include <math.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <ScurveInterpolator.h>
#include <QtMath>
#include <QVector3D>

class Slider : public Device
{
    Q_OBJECT
public:
    explicit Slider(QString COM = "auto", int baudrate = 115200, bool is_open = true, QObject *parent = nullptr);
    ~Slider(){};
};

#endif // SLIDER_H
