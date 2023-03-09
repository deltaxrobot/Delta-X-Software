#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <device/robot.h>
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
        MCU
    };

    DeviceManager();
    ~DeviceManager();

    QList<Robot*> Robots;
    QList<QThread*> Threads;

    int SelectedRobotID = 0;
signals:
    void DeviceResponded(QString id, QString response);
    void GotDeviceInfo(QString jsonDeviceInfo);

public slots:
    void AddRobot();
    void SetDeviceState(int deviceType, bool isOpen);
    void RequestDeviceInfo(int deviceType);
    void SendGcode(int deviceType, QString gcode);
    void SendGcode(QString deviceName, QString gcode);
    void GetCommand(QString cmd);
};

#endif // DEVICEMANAGER_H
