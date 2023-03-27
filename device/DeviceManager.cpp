#include "DeviceManager.h"

DeviceManager::DeviceManager()
{

}

DeviceManager::~DeviceManager()
{
    for (int i = 0; i < Robots.count(); i++)
    {
        Robots.at(i)->thread()->quit();
        Robots.at(i)->thread()->wait();
        delete Robots.at(i);
    }

    for (int i = 0; i < Sliders.count(); i++)
    {
        Sliders.at(i)->thread()->quit();
        Sliders.at(i)->thread()->wait();
        delete Sliders.at(i);
    }
}

void DeviceManager::AddRobot()
{
    qDebug() << "Add robot";
    Robot* robot = new Robot("auto", 115200, false);
    robot->SetID(QString("robot") + QString::number(Robots.count() + 1));
    Robots.append(robot);
    QThread* robotThread = new QThread(this);
    robot->moveToThread(robotThread);
    connect(robotThread, SIGNAL(started()), robot, SLOT(Run()));
    connect(robot, &Robot::receivedMsg, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(robot, &Robot::infoReady, this, &DeviceManager::GotDeviceInfo);

    robotThread->start();
}

void DeviceManager::AddConveyor(QString address="auto")
{
    qDebug() << "Add Conveyor";
    Conveyor* conveyor = new Conveyor(address, 115200, false);
    conveyor->SetID(QString("conveyor") + QString::number(Conveyors.count() + 1));
    Conveyors.append(conveyor);
    QThread* conveyorThread = new QThread(this);
    conveyor->moveToThread(conveyorThread);
    connect(conveyorThread, SIGNAL(started()), conveyor, SLOT(Run()));
    connect(conveyor, &Conveyor::receivedMsg, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(conveyor, &Conveyor::infoReady, this, &DeviceManager::GotDeviceInfo);

    conveyorThread->start();
}

void DeviceManager::AddSlider(QString address="auto")
{
    qDebug() << "Add slider";
    Slider* slider = new Slider(address, 115200, false);
    slider->SetID(QString("slider") + QString::number(Sliders.count() + 1));
    Sliders.append(slider);
    QThread* sliderThread = new QThread(this);
    slider->moveToThread(sliderThread);
    connect(sliderThread, SIGNAL(started()), slider, SLOT(Run()));
    connect(slider, &Slider::receivedMsg, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(slider, &Slider::infoReady, this, &DeviceManager::GotDeviceInfo);

    sliderThread->start();
}

void DeviceManager::AddDevice(QString address)
{
    qDebug() << "Add device";
    Device* device = new Device(address);
    device->SetID(QString("device") + QString::number(Devices.count() + 1));
    Devices.append(device);

    QThread* deviceThread = new QThread(this);
    device->moveToThread(deviceThread);
    connect(deviceThread, SIGNAL(started()), device, SLOT(Run()));
    connect(device, &Device::receivedMsg, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(device, &Device::infoReady, this, &DeviceManager::GotDeviceInfo);

    deviceThread->start();
}

void DeviceManager::SetDeviceState(int deviceType, bool isOpen, QString address = "auto")
{
    if (deviceType == ROBOT)
    {
        if (SelectedRobotID > Robots.count() - 1)
        {
            AddRobot();
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Robots[SelectedRobotID], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Robots[SelectedRobotID], "Disconnect", Qt::QueuedConnection);
    }

    if (deviceType == SLIDER)
    {
        if (SelectedSliderID > Sliders.count() - 1)
        {
            AddSlider();
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Sliders[SelectedSliderID], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Sliders[SelectedSliderID], "Disconnect", Qt::QueuedConnection);
    }

    if (deviceType == DEVICE)
    {
        if (SelectedDeviceID > Devices.count() - 1)
        {
            AddDevice(address);
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Devices[SelectedDeviceID], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Devices[SelectedDeviceID], "Disconnect", Qt::QueuedConnection);
    }

    if (deviceType == CONVEYOR)
    {
        if (SelectedConveyorID > Conveyors.count() - 1)
        {
            AddConveyor(address);
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "Disconnect", Qt::QueuedConnection);
    }
}

void DeviceManager::RequestDeviceInfo(int deviceType)
{
    if (deviceType == ROBOT)
    {
        if (SelectedRobotID > Robots.count() - 1)
        {
            AddRobot();
        }

        QMetaObject::invokeMethod(Robots[SelectedRobotID], "GetInfo", Qt::QueuedConnection);
    }

    if (deviceType == SLIDER)
    {
        if (SelectedSliderID > Sliders.count() - 1)
        {
            AddSlider();
        }

        QMetaObject::invokeMethod(Sliders[SelectedSliderID], "GetInfo", Qt::QueuedConnection);
    }

    if (deviceType == CONVEYOR)
    {
        if (SelectedConveyorID > Conveyors.count() - 1)
        {
            AddConveyor();
        }

        QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "GetInfo", Qt::QueuedConnection);
    }

}

void DeviceManager::SendGcode(int deviceType, QString gcode)
{
    if (deviceType == ROBOT)
    {
        QMetaObject::invokeMethod(Robots[SelectedRobotID], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));
        emit Log(QString("Robot %1<< ").arg(SelectedRobotID + 1) + gcode);
    }

    if (deviceType == DEVICE)
    {
        QMetaObject::invokeMethod(Devices[SelectedDeviceID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
        emit Log(QString("Device %1<< ").arg(SelectedDeviceID + 1) + gcode);
    }

    if (deviceType == CONVEYOR)
    {
        QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
        emit Log(QString("Conveyor %1<< ").arg(SelectedConveyorID + 1) + gcode);
    }
}

void DeviceManager::SendGcode(QString deviceName, QString gcode)
{
    QRegularExpression re("(\\D+)(\\d+)");
    QRegularExpressionMatch match = re.match(deviceName);

    QString device = deviceName;
    int id = SelectedRobotID;

    if (match.hasMatch())
    {
        device = match.captured(1);
        id = match.captured(2).toInt() - 1;
        if (id < 0)
            id = 0;
    }

    if (device.toLower() == "robot")
    {
        QMetaObject::invokeMethod(Robots[id], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));

        emit Log(QString("Robot %1<< ").arg(id + 1) + gcode);
    }

    if (device.toLower() == "slider")
    {
        QMetaObject::invokeMethod(Sliders[id], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));

        emit Log(QString("Slider %1<< ").arg(id + 1) + gcode);
    }

    if (device.toLower() == "device")
    {
        QMetaObject::invokeMethod(Devices[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

        emit Log(QString("Device %1<< ").arg(id + 1) + gcode);
    }
}

void DeviceManager::GetCommand(QString cmd)
{
    QStringList paras = cmd.split(" ");

    if (paras.isEmpty()) {
        return;
    }

    if (paras[0].contains("info"))
    {
//        get_info();
        return;
    }

    QStringList deviceNames = {"robot", "device", "conveyor", "slider", "encoder"};
    bool isSendDevice = false;
    for (int j = 0; j < deviceNames.count(); j++)
    {
        if (paras.at(0).contains(deviceNames[j]))
        {
            isSendDevice = true;
            break;
        }
    }

    if (isSendDevice == true)
    {
        QString msg = cmd.mid(paras[0].length() + 1);

        SendGcode(paras.at(0), msg);
    }

    if (paras[0].contains("move"))
    {
        if (paras[1].contains("C"))
        {
            if (paras.length() == 4)
            {
//                conveyor_station.move(paras[1], false, paras[2].toFloat(), paras[3].toFloat());
            }
            else
            {
//                conveyor_station.move(paras[1], true, 0.0, paras[2].toFloat());
            }
        }
        else if (paras[1].contains("robot"))
        {
            QString pos = cmd.mid(5 + paras[1].length() + 1);
            int id = paras[1].mid(5).toInt();
            Robot* robot = Robots[id];
            if (pos.contains("home"))
            {
                robot->GoHome();
            }
            else
            {
                QString dir = paras[2];
                float step = paras[3].toFloat();
                robot->MoveStep(dir, step);
            }
        }
    }
    else if (paras[0].contains("read"))
    {
        if (paras[1].contains("C"))
        {
            int id = paras[1].mid(1).toInt() - 1;
//            qDebug() << conveyor_station.sub_encoders[id].read_position();
        }
    }

}
