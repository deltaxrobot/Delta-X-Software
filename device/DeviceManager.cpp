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
    connect(robot, &Robot::gcodeDone, [=](QString id, QString response){ emit DeviceResponded(id, response); });
    connect(robot, &Robot::infoReady, this, &DeviceManager::GotDeviceInfo);

    robotThread->start();
}

void DeviceManager::SetDeviceState(int deviceType, bool isOpen)
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

}

void DeviceManager::SendGcode(int deviceType, QString gcode)
{
    if (deviceType == ROBOT)
    {
        QMetaObject::invokeMethod(Robots[SelectedRobotID], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));
        emit Log(QString("Robot %1<< ").arg(SelectedRobotID + 1) + gcode);
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
    }

    if (device.toLower() == "robot")
    {
        QMetaObject::invokeMethod(Robots[id], "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));

        emit Log(QString("Robot %1<< ").arg(id + 1) + gcode);
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
    }
    else if (paras[0].contains("robot"))
    {
        QString gcode = cmd.mid(paras[0].length() + 1);
        int id = paras[0].mid(5).toInt();
        Robot* robot = Robots[id];
        QMetaObject::invokeMethod(robot, "SendGcode", Qt::QueuedConnection, Q_ARG(QString, gcode));
//        robot->SendGcode(gcode);
    }
    else if (paras[0].contains("move"))
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
