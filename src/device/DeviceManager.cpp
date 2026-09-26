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
        Robot* obj = Robots.at(i);
        QMetaObject::invokeMethod(obj, "Disconnect", Qt::BlockingQueuedConnection);
        QMetaObject::invokeMethod(obj, "deleteLater", Qt::QueuedConnection);
        QThread* th = obj->thread();
        th->quit();
        th->wait();
        // Thread object was created with parent=this; it will be deleted with DeviceManager
    }

    for (int i = 0; i < Sliders.count(); i++)
    {
        Slider* obj = Sliders.at(i);
        QMetaObject::invokeMethod(obj, "Disconnect", Qt::BlockingQueuedConnection);
        QMetaObject::invokeMethod(obj, "deleteLater", Qt::QueuedConnection);
        QThread* th = obj->thread();
        th->quit();
        th->wait();
    }

    for (int i = 0; i < Conveyors.count(); i++)
    {
        Conveyor* obj = Conveyors.at(i);
        QMetaObject::invokeMethod(obj, "Disconnect", Qt::BlockingQueuedConnection);
        QMetaObject::invokeMethod(obj, "deleteLater", Qt::QueuedConnection);
        QThread* th = obj->thread();
        th->quit();
        th->wait();
    }

    for (int i = 0; i < Encoders.count(); i++)
    {
        Encoder* obj = Encoders.at(i);
        QMetaObject::invokeMethod(obj, "Disconnect", Qt::BlockingQueuedConnection);
        QMetaObject::invokeMethod(obj, "deleteLater", Qt::QueuedConnection);
        QThread* th = obj->thread();
        th->quit();
        th->wait();
    }
    for (int i = 0; i < Devices.count(); i++)
    {
        Device* obj = Devices.at(i);
        QMetaObject::invokeMethod(obj, "Disconnect", Qt::BlockingQueuedConnection);
        QMetaObject::invokeMethod(obj, "deleteLater", Qt::QueuedConnection);
        QThread* th = obj->thread();
        th->quit();
        th->wait();
    }
}

void DeviceManager::SetSelectedDevice(int deviceType, int id)
{
    id = qMax(0, id);
    switch (deviceType) {
    case ROBOT: SelectedRobotID = id; break;
    case CONVEYOR: SelectedConveyorID = id; break;
    case ENCODER: SelectedEncoderID = id; break;
    case SLIDER: SelectedSliderID = id; break;
    case DEVICE: SelectedDeviceID = id; break;
    default: break;
    }
}

void DeviceManager::SetRobotModel(int id, QString model)
{
    if (id < 0 || id >= Robots.size())
        return;
    Robot* robot = Robots.at(id);
    QMetaObject::invokeMethod(robot, [robot, model]() {
        robot->SetRobotModel(model);
    }, Qt::QueuedConnection);
}

void DeviceManager::SetEncoderLinkedConveyor(int encoderId, int conveyorId)
{
    if (encoderId < 0 || encoderId >= Encoders.size())
        return;
    Encoders.at(encoderId)->SetLinkedConveyor(conveyorId);
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
    device->SetIDName(QString("device") + QString::number(Devices.count()));
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
        {
            QMetaObject::invokeMethod(Robots[id], "OpenAtAddress", Qt::QueuedConnection,
                                      Q_ARG(QString, address));
        }
        else
        {
            QMetaObject::invokeMethod(Robots[id], "Disconnect", Qt::QueuedConnection);
        }
    }

    if (device == "slider")
    {
        if (id > Sliders.count() - 1)
        {
            AddSlider(address);
        }

        if (isOpen == true)
        {
            QMetaObject::invokeMethod(Sliders[id], "OpenAtAddress", Qt::QueuedConnection,
                                      Q_ARG(QString, address));
        }
        else
        {
            QMetaObject::invokeMethod(Sliders[id], "Disconnect", Qt::QueuedConnection);
        }
    }

    if (device == "conveyor")
    {
        if (id > Conveyors.count() - 1)
        {
            AddConveyor(address);
        }

        if (isOpen == true)
        {
            QMetaObject::invokeMethod(Conveyors[id], "OpenAtAddress", Qt::QueuedConnection,
                                      Q_ARG(QString, address));
        }
        else
        {
            QMetaObject::invokeMethod(Conveyors[id], "Disconnect", Qt::QueuedConnection);
        }
    }

    if (device == "device")
    {
        if (id > Devices.count() - 1)
        {
            AddDevice(address);
        }

        if (isOpen == true)
        {
            QMetaObject::invokeMethod(Devices[id], "OpenAtAddress", Qt::QueuedConnection,
                                      Q_ARG(QString, address));
        }
        else
        {
            QMetaObject::invokeMethod(Devices[id], "Disconnect", Qt::QueuedConnection);
        }
    }

    if (device == "encoder")
    {
        if (id > Encoders.count() - 1)
        {
            AddEncoder(address);
        }

        if (isOpen == true)
        {
            QMetaObject::invokeMethod(Encoders[id], "OpenAtAddress", Qt::QueuedConnection,
                                      Q_ARG(QString, address));
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

    if (deviceType == SLIDER)
    {
        if (Sliders.count() > SelectedSliderID)
        {
            QMetaObject::invokeMethod(Sliders[SelectedSliderID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
            emit Log(QString("slider%1").arg(SelectedSliderID), gcode, 1);
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
            const int linkedConveyor =
                Encoders[SelectedEncoderID]->LinkedConveyorId();
            if (linkedConveyor == -1)
            {
                if (Encoders[SelectedEncoderID]->IsOpen() == false)
                {
                    emit GotEncoderPosition(
                        SelectedEncoderID,
                        Encoders[SelectedEncoderID]->CurrentPosition());
                }
                else
                {
                    QMetaObject::invokeMethod(Encoders[SelectedEncoderID], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));
                    emit Log(QString("encoder%1").arg(SelectedEncoderID), gcode, 1);
                }
            }
            else
            {
                if (linkedConveyor < 0 || linkedConveyor >= Conveyors.size()) {
                    emit DeviceNotAvailable(QString("conveyor%1").arg(linkedConveyor),
                                            QStringLiteral("Linked conveyor is not registered"));
                    return;
                }
                if (Conveyors[linkedConveyor]->IsOpen() == false)
                {
                    emit GotEncoderPosition(
                        SelectedEncoderID,
                        Conveyors[linkedConveyor]->CurrentPosition());
                }
                else
                {
                    QMetaObject::invokeMethod(Conveyors[linkedConveyor], "WriteData",
                                              Qt::QueuedConnection, Q_ARG(QString, gcode));
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
            if (!Robots[id]->IsOpen()) {
                emit DeviceNotAvailable(deviceName,
                                        QStringLiteral("Robot is not connected"));
                return;
            }
            QMetaObject::invokeMethod(Robots[id], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));

//            emit Log(QString("Robot %1").arg(id), gcode, 1);
        }
        else
        {
            emit DeviceNotAvailable(deviceName,
                                    QStringLiteral("Robot is not registered"));
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
                emit GotEncoderPosition(id, Conveyors[id]->CurrentPosition());
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
            const int linkedConveyor = Encoders[id]->LinkedConveyorId();
            if (linkedConveyor == -1)
            {
                if (Encoders[id]->IsOpen() == false)
                {
                    emit GotEncoderPosition(id, Encoders[id]->CurrentPosition());
                }
                else
                {
                    QMetaObject::invokeMethod(Encoders[id], "WriteData", Qt::QueuedConnection, Q_ARG(QString, gcode));

                    emit Log(QString("encoder%1").arg(id), gcode, 1);
                }
            }
            else
            {
                if (linkedConveyor < 0 || linkedConveyor >= Conveyors.size()) {
                    emit DeviceNotAvailable(QString("conveyor%1").arg(linkedConveyor),
                                            QStringLiteral("Linked conveyor is not registered"));
                    return;
                }
                if (Conveyors[linkedConveyor]->IsOpen() == false)
                {
                    emit GotEncoderPosition(id, Conveyors[linkedConveyor]->CurrentPosition());
                }
                else
                {
                    QMetaObject::invokeMethod(Conveyors[linkedConveyor], "WriteData",
                                              Qt::QueuedConnection, Q_ARG(QString, gcode));

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
