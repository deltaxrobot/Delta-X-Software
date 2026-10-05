#ifndef ENCODER_H
#define ENCODER_H

#include "device.h"
#include <QObject>
#include <atomic>

class Encoder : public Device
{
    Q_OBJECT
public:
    explicit Encoder(QString COM = "auto", int baudrate = 115200, bool is_open = true, QObject *parent = nullptr);
    int LinkedConveyorId() const;
    float CurrentPosition() const;
signals:
    void GotPosition(int id, float value);
public slots:
    void SetLinkedConveyor(int conveyorId);
    void ProcessResponse(QString id, QString response = "");

private:
    std::atomic_int linkedConveyor{-1};
    std::atomic<float> position{0.0f};

};

#endif // ENCODER_H
