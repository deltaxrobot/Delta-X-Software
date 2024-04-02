#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <device/robot.h>
#include <device/slider.h>
#include <device/conveyor.h>
#include <device/encoder.h>
#include <QThread>

class DeviceManager : public QObject
{
    Q_OBJECT
public:
    enum
    {
        ROBOT = 0,
        CONVEYOR,
        ENCODER,
        SLIDER,
        DEVICE
    };

    DeviceManager();
    ~DeviceManager();

    QList<Robot*> Robots;
    QList<Slider*> Sliders;
    QList<Device*> Devices;
    QList<Conveyor*> Conveyors;
    QList<Encoder*> Encoders;
    QList<QThread*> Threads;

    int SelectedRobotID = 0;
    int SelectedSliderID = 0;
    int SelectedDeviceID = 0;
    int SelectedConveyorID = 0;
    int SelectedEncoderID = 0;
    QString ProjectName = "project0";
signals:
    void GotEncoderPosition(int id, float position);
    void DeviceNotAvailable(QString device);
    void DeviceResponded(QString id, QString response);
    void GotDeviceInfo(QString jsonDeviceInfo);
    void Log(QString device, QString msg, int direction);

public slots:
    void AddRobot(QString address);
    void AddConveyor(QString address);
    void AddEncoder(QString address);
    void AddSlider(QString address);
    void AddDevice(QString address);
    void SetDeviceState(QString deviceName, bool isOpen, QString address);
    void RequestDeviceInfo(int deviceType);
    void SendGcode(int deviceType, QString gcode);
    void SendGcode(QString deviceName, QString gcode);
    void GetCommand(QString cmd);
};

#endif // DEVICEMANAGER_H
