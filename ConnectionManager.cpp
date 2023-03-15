#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
	init();
}

void ConnectionManager::init()
{
    // ---- Robot -----
	RobotPort = new QSerialPort();
	connect(RobotPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	RobotSocket = new QTcpSocket();
	connect(RobotSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));
	
    // ---- Timer for robot scanning -----
//    connectionTimer = new QTimer();
//    connect(connectionTimer, SIGNAL(timeout()), this, SLOT(FindingRobotTimeOut()));

    // ---- MCU -----
	ExternalControllerPort = new QSerialPort();
	connect(ExternalControllerPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	ExternalControllerSocket = new QTcpSocket();
	connect(ExternalControllerSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

    // ----- Slider -----
	SlidingPort = new QSerialPort();
	connect(SlidingPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	SlidingSocket = new QTcpSocket();
	connect(SlidingSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

    // ---- Conveyor ----
	ConveyorPort = new QSerialPort();
	connect(ConveyorPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	ConveyorSocket = new QTcpSocket();
	connect(ConveyorSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

    // ---- Encoder ----
    EncoderPort = new QSerialPort();
    connect(EncoderPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
    EncoderSocket = new QTcpSocket();
    connect(EncoderSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

    // ---- Software Server ----
	TCPConnection = new TCPConnectionManager();
	OpenAvailableServer();

	TcpServer = TCPConnection->TcpServer;
	connect(TCPConnection, SIGNAL(NewConnection(QTcpSocket*)), this, SLOT(ReceiveNewConnectionFromServer(QTcpSocket*)));

    // ------
    Ports.append(RobotPort);
    Ports.append(ConveyorPort);
    Ports.append(SlidingPort);
    Ports.append(ExternalControllerPort);
    Ports.append(EncoderPort);
}

void ConnectionManager::processRobotData()
{
    emit GcodeDone();
    receiveLine = receiveLine.replace("\n", "");
    VarManager::getInstance()->updateVar("Response", receiveLine);
    emit ReceiveVariableChangeCommand("Response", receiveLine);
    emit Log(QString("Robot << ") + receiveLine);

    // ---- Receive robot position after homing ----
    if (transmitLine == "G28")
    {
        SendToRobot("Position");
    }

    if (receiveLine.indexOf(",") > -1 && transmitLine == "Position")
	{
		QList<QString> nums = receiveLine.split(",");

        if (nums.size() >= 3)
		{
            float w = 0, u = 0, v = 0;
            if (nums.size() == 4)
                w = nums[3].toFloat();
            if (nums.size() == 5)
                u = nums[4].toFloat();
            if (nums.size() == 6)
                v = nums[5].toFloat();

            emit InHomePosition(nums[0].toFloat(), nums[1].toFloat(), nums[2].toFloat(), w, u, v);
		}
    }
    // ---- Input Output Feedback -----
    else if (receiveLine.indexOf(" V") > -1 && (receiveLine.indexOf("A") > -1 || receiveLine.indexOf(" V") > -1))
    {
        emit ReceiveInputIO(receiveLine);
    }
}

void ConnectionManager::processConveyorData()
{
    emit GcodeDone();
    emit Log(QString("Conveyor << ") + receiveLine);
}

void ConnectionManager::processSliderData()
{
    emit Log(QString("Slider << ") + receiveLine);
}

void ConnectionManager::processMCUData()
{
    emit ExternalMCUTransmitText(receiveLine);

    emit Log(QString("MCU << ") + receiveLine);
}

void ConnectionManager::processEncoderData()
{
    if (receiveLine.at(0) == "P")
    {
        float pos = receiveLine.mid(1).toFloat();
//        ProcessEncoderValue(pos);
        emit ReceivedEncoderPosition(pos);
    }
    else if (receiveLine.at(0) == '0' || receiveLine.at(0) == '1')
    {
        emit ReceivedProximitySensorValue(receiveLine.mid(0, 1).toInt());
    }
}

void ConnectionManager::processOtherSoftwareData()
{
    // ---- receive variable values or signal ----
    if (receiveLine.at(0) == '#' && receiveLine.indexOf("=") > -1)
    {
        int symId = receiveLine.indexOf("=");
        QString name = receiveLine.mid(0, symId).replace(" ", "");
        QString valueS = receiveLine.mid(symId + 1).replace(" ", "");

        // ---- Captured image signal from other processing ----
        if (name == "#StartCapture" && valueS.toInt() == 1)
        {
            ReceiveCaptureSignalFromExternalAI();
        }
        // ---- Receive real object info from other processing ----
        else if (name == "#Label")
        {
            emit ReceiveObjectInfoFromExternalAI(valueS);
        }
        // ---- Receive decting object info from other processing ----
        else if (name == "#Object")
        {
            emit ReceiveDisplayObjectFromExternalScript(valueS);
        }
        // ---- Request to change variable ----
        else
        {
//            int value = valueS.toInt();
            VarManager::getInstance()->updateVar(name, valueS);
            emit ReceiveVariableChangeCommand(name, valueS);
        }
    }

    // ---- Request variable value ----
    if (receiveLine.at(0) == '#' && receiveLine.indexOf("=") == -1)
    {
        receiveLine = receiveLine.replace(" ", "");
        receiveLine = receiveLine.replace("\n", "");
        receiveLine = receiveLine.replace("\r", "");

        QString name = receiveLine;
        emit RequestVariableValue(EmitIOSender, name);
    }

    // ---- Request event on software ----
    if (receiveLine.at(0) == 'r' && receiveLine.indexOf(":") > -1)
    {
        int symId = receiveLine.indexOf(":");

        QString request = receiveLine.mid(symId + 1);

        emit ReceiveRequestsFromExternal(request);
    }

    // ---- Connect ROS -----
    for (int i = 0; i < TCPConnection->ClientList->size(); i++)
    {
        if (TCPConnection->ClientList->at(i)->socket == EmitIOSender)
        {
            if (receiveLine.indexOf("ros") > -1)
            {
                TCPConnection->ClientList->at(i)->IsROS = true;
                break;
            }
        }
    }

    if (IsRosSocket(EmitIOSender) == true)
    {
        TCPConnection->ProcessReceivedData(receiveLine);

        if (receiveLine.contains("ExternalScript"))
        {
            ExternalScriptSocket = qobject_cast<QTcpSocket*>(EmitIOSender);
            emit ExternalScriptSocket;
        }
    }
}

void ConnectionManager::sendData(QSerialPort * com, QTcpSocket * socket, QString msg)
{
    transmitLine = msg;

    if (msg == "")
        return;

	if (msg[msg.length() - 1] != "\n")
        msg += "\n";

    bool result = false;

	if (com != NULL)
	{
		if (com->isOpen())
		{
			com->write(msg.toStdString().c_str(), msg.size());
            result = true;
		}
	}
    else if (socket != NULL)
	{
		if (socket->isOpen())
		{
			socket->write(msg.toStdString().c_str(), msg.size());
            result = true;
		}
	}

    if (result == false)
    {
        emit Log(QString("Robot >> ") + com->portName() + " fail");
        emit FailTransmit();
    }
}

void ConnectionManager::OpenAvailableServer()
{
	int port = 8844;
	for (int i = 0; i < 10; i++)
	{
        bool isSuccess = TCPConnection->OpenServer("127.0.0.1", port + i);
		if (isSuccess == true)
		{
			return;
		}
			
	}	
}

bool ConnectionManager::IsRobotConnect()
{
	if (RobotPort->isOpen() || RobotSocket->isOpen())
		return true;

	return false;
}

void ConnectionManager::DisconnectRobot()
{
	if (RobotPort->isOpen())
	{
		RobotPort->close();
		isDeltaPortConnected = false;
	}
	if (RobotSocket->isOpen())
	{
		RobotSocket->close();
		isDeltaPortConnected = false;
	}
}

bool ConnectionManager::IsRosClientAvailable()
{
	bool result = false;
	for (int i = 0; i < TCPConnection->ClientList->size(); i++)
	{
		if (TCPConnection->ClientList->at(i)->IsROS == true)
			result = true;
	}
	return result;
}

bool ConnectionManager::IsRosSocket(QIODevice* socket)
{
	bool result = false;
	for (int i = 0; i < TCPConnection->ClientList->size(); i++)
	{
		if (TCPConnection->ClientList->at(i)->socket == socket)
			result = true;
	}
	return result;
}

QString ConnectionManager::GetNamePort()
{
	if (RobotPort == NULL || RobotPort == Q_NULLPTR)
		return QString("Null");
	
	return RobotPort->portName();
}

void ConnectionManager::SetBaudrate(int baud)
{
	this->baudrate = baud;
}

int ConnectionManager::GetBaudrate()
{
	return baudrate;
}

void ConnectionManager::FindDeltaRobot()
{
    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
	{
		QSerialPort* sP = new QSerialPort();

		QString portName = portInfo.portName();
		sP->setPortName(portName);
		sP->setBaudRate(baudrate);

		portList.push_back(sP);

        if (sP->open((QIODevice::ReadWrite)) == true)
        {
            connect(sP, SIGNAL(readyRead()), this, SLOT(CheckScanningRobotRespone()));

            QString name = sP->portName();

//            QThread::msleep(500);
//            sP->write("IsDelta\n");


		}
	}

    QTimer::singleShot(500, this, &ConnectionManager::SendRobotConfirmCommand);

}

void ConnectionManager::SendToRobot(QString msg)
{
//	TCPConnection->SendMessageToROS("gcode " + msg);

    emit Log(QString("Robot >> ") + msg);

	sendData(RobotPort, RobotSocket, msg);
}

void ConnectionManager::SendToConveyor(QString msg)
{
    emit Log(QString("Conveyor >> ") + msg);

	sendData(ConveyorPort, ConveyorSocket, msg);
}

void ConnectionManager::SendToSlider(QString msg)
{
    emit Log(QString("Slider >> ") + msg);

	sendData(SlidingPort, SlidingSocket, msg);
}

void ConnectionManager::SendToExternalMCU(QString msg)
{
    emit Log(QString("MCU >> ") + msg);

    sendData(ExternalControllerPort, ExternalControllerSocket, msg);
}

void ConnectionManager::SendToEncoder(QString msg)
{
    emit Log(QString("Encoder >> ") + msg);

    sendData(EncoderPort, EncoderSocket, msg);
}

void ConnectionManager::ReadData()
{
    EmitIOSender = qobject_cast<QIODevice*>(sender());

    if (EmitIOSender)
    {
        while (EmitIOSender->canReadLine())
        {
            receiveLine = EmitIOSender->readLine();

            if (receiveLine == "")
                continue;

            if (EmitIOSender == RobotPort || EmitIOSender == RobotSocket)
            {
                processRobotData();
            }

            else if (EmitIOSender == ConveyorPort || EmitIOSender == ConveyorSocket)
            {
                processConveyorData();
            }

            else if (EmitIOSender == SlidingPort || EmitIOSender == SlidingSocket)
            {
                processSliderData();
            }

            else if (EmitIOSender == ExternalControllerPort || EmitIOSender == ExternalControllerSocket)
            {
                processMCUData();
            }

            else if (EmitIOSender == EncoderPort || EmitIOSender == EncoderSocket)
            {
                processEncoderData();
            }

            processOtherSoftwareData();

            receiveLine = "";
        }
    }
}

void ConnectionManager::CheckScanningRobotRespone()
{
    EmitIOSender = qobject_cast<QIODevice*>(sender());
    QString response = EmitIOSender->readLine();

    if (response.mid(0, 8) == "YesDelta")
    {
        if (isDeltaPortConnected == false)
        {
            delete RobotPort;

            RobotPort = qobject_cast<QSerialPort*>(sender());

            RobotPort->disconnect();

            connect(RobotPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
            connect(RobotSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

            emit DeltaResponeReady();

            isDeltaPortConnected = true;

            SendToRobot("Position");
        }
    }
}



void ConnectionManager::FindingRobotTimeOut()
{
    foreach(QSerialPort* port, portList)
	{
        if (port->portName() != RobotPort->portName())
		{
            port->close();
            delete port;
            port = NULL;
		}
	}

	portList.clear();

//    connectionTimer->stop();

    emit FinishFindingRobot();
}

void ConnectionManager::ReceiveNewConnectionFromServer(QTcpSocket * socket)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void ConnectionManager::SendRobotConfirmCommand()
{
    foreach(QSerialPort* sp, portList)
    {
        if (sp == NULL)
            continue;

        if (sp->isOpen())
        {
          sp->write("IsDelta\n");
          sp->write("IsDelta\n");
        }
    }

    QTimer::singleShot(2000, this, &ConnectionManager::FindingRobotTimeOut);
//    connectionTimer->start(200);
}

void ConnectionManager::Send(int device, QString msg)
{
    switch (device)
    {
        case ROBOT :
            SendToRobot(msg);
            break;
        case CONVEYOR :
            SendToConveyor(msg);
            break;
        case SLIDER :
            SendToSlider(msg);
            break;
        case MCU :
            SendToExternalMCU(msg);
            break;
        case ENCODER :
            SendToEncoder(msg);
            break;
    }
}

void ConnectionManager::SendGcode(QString deviceName, QString msg)
{
    if (deviceName == "Robot")
    {
        SendToRobot(msg);
    }

    if (deviceName == "Conveyor")
    {
        SendToConveyor(msg);
    }

    if (deviceName == "Slider")
    {
        SendToSlider(msg);
    }

    if (deviceName == "ExternalMCU")
    {
        SendToExternalMCU(msg);
    }
}
