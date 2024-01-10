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

    for (int i = 0; i < Conveyors.count(); i++)
    {
        Conveyors.at(i)->thread()->quit();
        Conveyors.at(i)->thread()->wait();
        delete Conveyors.at(i);
    }

    for (int i = 0; i < Encoders.count(); i++)
    {
        Encoders.at(i)->thread()->quit();
        Encoders.at(i)->thread()->wait();
        delete Encoders.at(i);
    }
}

void DeviceManager::AddRobot(QString address="auto")
{
    qDebug() << "Add robot";
    Robot* robot = new Robot(address, 115200, false);
    robot->ProjectName = ProjectName;
    robot->SetIDName(QString("robot") + QString::number(SelectedRobotID));
    Robots.append(robot);
    QThread* robotThread = new QThread(this);
    robot->moveToThread(robotThread);
    connect(robotThread, SIGNAL(started()), robot, SLOT(Run()));
    connect(robot, &Robot::receivedMsg, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(robot, &Robot::infoReady, this, &DeviceManager::GotDeviceInfo);
    connect(robot, &Robot::Log, this, &DeviceManager::Log);

    robotThread->start();
}

void DeviceManager::AddConveyor(QString address="auto")
{
    qDebug() << "Add Conveyor";
    Conveyor* conveyor = new Conveyor(address, 115200, false);
    conveyor->ProjectName = ProjectName;
    conveyor->SetIDName(QString("conveyor") + QString::number(SelectedConveyorID));
    Conveyors.append(conveyor);
    QThread* conveyorThread = new QThread(this);
    conveyor->moveToThread(conveyorThread);
    connect(conveyorThread, SIGNAL(started()), conveyor, SLOT(Run()));
    connect(conveyor, &Conveyor::receivedMsg, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(conveyor, &Conveyor::infoReady, this, &DeviceManager::GotDeviceInfo);
    connect(conveyor, &Conveyor::GotEncoderPosition, this, &DeviceManager::GotEncoderPosition);

    conveyorThread->start();
}

void DeviceManager::AddEncoder(QString address = "auto")
{
    qDebug() << "Add Encoder";
    Encoder* encoder = new Encoder(address, 115200, false);
    encoder->ProjectName = ProjectName;
    encoder->SetIDName(QString("encoder") + QString::number(SelectedEncoderID));
    Encoders.append(encoder);
    QThread* encoderThread = new QThread(this);
    encoder->moveToThread(encoderThread);
    connect(encoderThread, SIGNAL(started()), encoder, SLOT(Run()));
    connect(encoder, &Encoder::receivedMsg, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(encoder, &Encoder::infoReady, this, &DeviceManager::GotDeviceInfo);
    connect(encoder, &Encoder::GotPosition, this, &DeviceManager::GotEncoderPosition);

    encoderThread->start();
}

void DeviceManager::AddSlider(QString address="auto")
{
    qDebug() << "Add slider";
    Slider* slider = new Slider(address, 115200, false);
    slider->ProjectName = ProjectName;
    slider->SetIDName(QString("slider") + QString::number(SelectedSliderID));
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
    device->ProjectName = ProjectName;
    device->SetIDName(QString("device") + QString::number(SelectedDeviceID));
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
            AddRobot(address);
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
            AddSlider(address);
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
        {
            Conveyors[SelectedConveyorID]->SetSerialPortName(address);
            QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "Connect", Qt::QueuedConnection);
        }
        else
            QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "Disconnect", Qt::QueuedConnection);
    }

    if (deviceType == ENCODER)
    {
        if (SelectedEncoderID > Encoders.count() - 1)
        {
            AddEncoder(address);
        }

        if (isOpen == true)
        {
            Encoders[SelectedEncoderID]->SetSerialPortName(address);
            QMetaObject::invokeMethod(Encoders[SelectedEncoderID], "Connect", Qt::QueuedConnection);
        }
        else
        {
            QMetaObject::invokeMethod(Encoders[SelectedEncoderID], "Disconnect", Qt::QueuedConnection);
        }
    }
}

void DeviceManager::RequestDeviceInfo(int deviceType)
{
    if (deviceType == ROBOT)
    {
        while (SelectedRobotID > Robots.count() - 1)
        {
            AddRobot();
        }

        QMetaObject::invokeMethod(Robots[SelectedRobotID], "GetInfo", Qt::QueuedConnection);
    }

    if (deviceType == SLIDER)
    {
        while (SelectedSliderID > Sliders.count() - 1)
        {
            AddSlider();
        }

        QMetaObject::invokeMethod(Sliders[SelectedSliderID], "GetInfo", Qt::QueuedConnection);
    }

    if (deviceType == CONVEYOR)
    {
        while (SelectedConveyorID > Conveyors.count() - 1)
        {
            AddConveyor();
        }
        QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "GetInfo", Qt::QueuedConnection);
    }

    if (deviceType == ENCODER)
    {
        while (SelectedEncoderID > Encoders.count() - 1)
        {
            AddEncoder();
        }
        QMetaObject::invokeMethod(Encoders[SelectedEncoderID], "GetInfo", Qt::QueuedConnection);
    }

}

void DeviceManager::SendGcode(int deviceType, QString gcode)
{
    if (deviceType == ROBOT)
    {
        if (Robots.count() > SelectedRobotID)
        {
            QMetaObject::invokeMethod(Robots[SelectedRobotID], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));
//            emit Log(QString("Robot %1").arg(SelectedRobotID), gcode, 1);
        }
    }

    if (deviceType == DEVICE)
    {
        if (Devices.count() > SelectedDeviceID)
        {
            QMetaObject::invokeMethod(Devices[SelectedDeviceID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
            emit Log(QString("Device %1").arg(SelectedDeviceID), gcode, 1);
        }
    }

    if (deviceType == CONVEYOR)
    {
        if (Conveyors.count() > SelectedConveyorID)
        {
            QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
            emit Log(QString("Conveyor %1").arg(SelectedConveyorID), gcode, 1);
        }
    }

    if (deviceType == ENCODER)
    {
        if (Encoders.count() > SelectedEncoderID)
        {
            QMetaObject::invokeMethod(Encoders[SelectedEncoderID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
            emit Log(QString("Encoder %1").arg(SelectedEncoderID), gcode, 1);
        }
    }
}

void DeviceManager::SendGcode(QString deviceName, QString gcode)
{
    QRegularExpression re("(\\D+)(\\d+)");
    QRegularExpressionMatch match = re.match(deviceName);

    QString device = deviceName;
    int id = 0;

    if (match.hasMatch())
    {
        device = match.captured(1);
        id = match.captured(2).toInt();
        if (id < 0)
            id = 0;
    }

    if (device.toLower() == "robot")
    {
        if (id < Robots.count())
        {
            QMetaObject::invokeMethod(Robots[id], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));

//            emit Log(QString("Robot %1").arg(id), gcode, 1);
        }
        else
        {
            // Delay 100ms
            QThread::msleep(100);
            emit DeviceResponded(deviceName, "Ok");
        }
    }

    if (device.toLower() == "slider")
    {
        if (id < Sliders.count())
        {
            QMetaObject::invokeMethod(Sliders[id], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));

            emit Log(QString("Slider %1").arg(id), gcode, 1);
        }
    }

    if (device.toLower() == "device")
    {
        if (id < Devices.count())
        {
            QMetaObject::invokeMethod(Devices[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

            emit Log(QString("Device %1").arg(id), gcode, 1);
        }
    }

    if (device.toLower() == "conveyor")
    {
        if (id < Conveyors.count())
        {
            QMetaObject::invokeMethod(Conveyors[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

            emit Log(QString("Conveyor %1").arg(id), gcode, 1);
        }
    }

    if (device.toLower() == "encoder")
    {
        if (id < Encoders.count())
        {
            QMetaObject::invokeMethod(Encoders[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

            emit Log(QString("Encoder %1").arg(id), gcode, 1);
        }
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
