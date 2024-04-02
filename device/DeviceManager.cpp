#include "DeviceManager.h"

DeviceManager::DeviceManager()
{
    for (int var = 0; var < 3; ++var) {
        AddRobot("auto");
        AddConveyor("auto");
        AddEncoder("auto");
        AddSlider("auto");
        AddDevice("auto");
    }
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
    for (int i = 0; i < Devices.count(); i++)
    {
        Devices.at(i)->thread()->quit();
        Devices.at(i)->thread()->wait();
        delete Devices.at(i);
    }
}

void DeviceManager::AddRobot(QString address="auto")
{
//    qDebug() << "Add robot";
    Robot* robot = new Robot(address, 115200, false);
    robot->ProjectName = ProjectName;
    robot->SetIDName(QString("robot") + QString::number(Robots.count()));
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
//    qDebug() << "Add Conveyor";
    Conveyor* conveyor = new Conveyor(address, 115200, false);
    conveyor->ProjectName = ProjectName;
    conveyor->SetIDName(QString("conveyor") + QString::number(Conveyors.count()));
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
//    qDebug() << "Add Encoder";
    Encoder* encoder = new Encoder(address, 115200, false);
    encoder->ProjectName = ProjectName;
    encoder->SetIDName(QString("encoder") + QString::number(Encoders.count()));
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
//    qDebug() << "Add slider";
    Slider* slider = new Slider(address, 115200, false);
    slider->ProjectName = ProjectName;
    slider->SetIDName(QString("slider") + QString::number(Sliders.count()));
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
//    qDebug() << "Add device";
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

void DeviceManager::SetDeviceState(QString deviceName, bool isOpen, QString address = "auto")
{
    // deviceName = "robot0", deviceName = "conveyor12"
    QRegularExpression re("(\\D+)(\\d+)");
    QRegularExpressionMatch match = re.match(deviceName);

    QString device = match.captured(1);
    int id = match.captured(2).toInt();

    if (device == "robot")
    {
        if (id > Robots.count() - 1)
        {
            AddRobot(address);
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Robots[id], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Robots[id], "Disconnect", Qt::QueuedConnection);
    }

    if (device == "slider")
    {
        if (id > Sliders.count() - 1)
        {
            AddSlider(address);
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Sliders[id], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Sliders[id], "Disconnect", Qt::QueuedConnection);
    }

    if (device == "conveyor")
    {
        if (id > Conveyors.count() - 1)
        {
            AddConveyor(address);
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Conveyors[id], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Conveyors[id], "Disconnect", Qt::QueuedConnection);
    }

    if (device == "device")
    {
        if (id > Devices.count() - 1)
        {
            AddDevice(address);
        }

        if (isOpen == true)
            QMetaObject::invokeMethod(Devices[id], "Connect", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(Devices[id], "Disconnect", Qt::QueuedConnection);
    }

    if (device == "encoder")
    {
        if (id > Encoders.count() - 1)
        {
            AddEncoder(address);
        }

        if (isOpen == true)
        {
            Encoders[id]->SetSerialPortName(address);
            QMetaObject::invokeMethod(Encoders[id], "Connect", Qt::QueuedConnection);
        }
        else
        {
            QMetaObject::invokeMethod(Encoders[id], "Disconnect", Qt::QueuedConnection);
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
            emit Log(QString("device%1").arg(SelectedDeviceID), gcode, 1);
        }
    }

    if (deviceType == CONVEYOR)
    {
        if (Conveyors.count() > SelectedConveyorID)
        {
            QMetaObject::invokeMethod(Conveyors[SelectedConveyorID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
            emit Log(QString("conveyor%1").arg(SelectedConveyorID), gcode, 1);
        }
    }

    if (deviceType == ENCODER)
    {
        if (Encoders.count() > SelectedEncoderID)
        {
            if (Encoders[SelectedEncoderID]->LinkedConveyor == -1)
            {
                if (Encoders[SelectedEncoderID]->IsOpen() == false)
                {
                    emit GotEncoderPosition(SelectedEncoderID, Encoders[SelectedEncoderID]->Position);
                }
                else
                {
                    QMetaObject::invokeMethod(Encoders[SelectedEncoderID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
                    emit Log(QString("encoder%1").arg(SelectedEncoderID), gcode, 1);
                }
            }
            else
            {
                if (Conveyors[Encoders[SelectedEncoderID]->LinkedConveyor]->IsOpen() == false)
                {
                    emit GotEncoderPosition(SelectedEncoderID, Conveyors[Encoders[SelectedEncoderID]->LinkedConveyor]->Position);
                }
                else
                {
                    QMetaObject::invokeMethod(Conveyors[Encoders[SelectedEncoderID]->LinkedConveyor], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
                    emit Log(QString("conveyor%1").arg(SelectedEncoderID), gcode, 1);
                }
            }
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

            emit Log(QString("slider%1").arg(id), gcode, 1);
        }
    }

    if (device.toLower() == "device")
    {
        if (id < Devices.count())
        {
            QMetaObject::invokeMethod(Devices[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

            emit Log(QString("device%1").arg(id), gcode, 1);
        }
    }

    if (device.toLower() == "conveyor")
    {
        if (id < Conveyors.count())
        {
            if (Conveyors[id]->IsOpen() == false)
            {
                emit GotEncoderPosition(id, Conveyors[id]->Position);
            }
            else
            {
                QMetaObject::invokeMethod(Conveyors[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

                emit Log(QString("conveyor%1").arg(id), gcode, 1);
            }
        }
    }

    if (device.toLower() == "encoder")
    {
        if (id < Encoders.count())
        {
            if (Encoders[id]->LinkedConveyor == -1)
            {
                if (Encoders[id]->IsOpen() == false)
                {
                    emit GotEncoderPosition(id, Encoders[id]->Position);
                }
                else
                {
                    QMetaObject::invokeMethod(Encoders[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

                    emit Log(QString("encoder%1").arg(id), gcode, 1);
                }
            }
            else
            {
                if (Conveyors[Encoders[id]->LinkedConveyor]->IsOpen() == false)
                {
                    emit GotEncoderPosition(id, Conveyors[Encoders[id]->LinkedConveyor]->Position);
                }
                else
                {
                    QMetaObject::invokeMethod(Conveyors[Encoders[id]->LinkedConveyor], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

                    emit Log(QString("conveyor%1").arg(id), gcode, 1);
                }
            }


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
