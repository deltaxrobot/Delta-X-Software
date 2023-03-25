#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <device/robot.h>
#include <device/slider.h>
#include <device/conveyor.h>
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
    QList<QThread*> Threads;

    int SelectedRobotID = 0;
    int SelectedSliderID = 0;
    int SelectedDeviceID = 0;
    int SelectedConveyorID = 0;
signals:
    void DeviceResponded(QString id, QString response);
    void GotDeviceInfo(QString jsonDeviceInfo);
    void Log(QString msg);

public slots:
    void AddRobot();
    void AddConveyor(QString address);
    void AddSlider(QString address);
    void AddDevice(QString address);
    void SetDeviceState(int deviceType, bool isOpen, QString address);
    void RequestDeviceInfo(int deviceType);
    void SendGcode(int deviceType, QString gcode);
    void SendGcode(QString deviceName, QString gcode);
    void GetCommand(QString cmd);
};

#endif // DEVICEMANAGER_H
