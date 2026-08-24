#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "device.h"
#include <QObject>
#include <atomic>

class Conveyor : public Device
{
    Q_OBJECT
public:
    explicit Conveyor(QString COM = "auto", int baudrate = 115200, bool is_open = true, QObject *parent = nullptr);
    ~Conveyor();

    void SetType(QString type);
    QString GetType();    

    float CurrentPosition() const;

public slots:
    QString GetInfo();
    void ProcessResponse(QString idName, QString response = "");

signals:
    void GotEncoderPosition(int id, float position);

private:
    QString type;
    std::atomic<float> position{0.0f};
};

#endif // CONVEYOR_H
