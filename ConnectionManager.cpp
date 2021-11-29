#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
	init();
}

void ConnectionManager::init()
{
	RobotPort = new QSerialPort();
	connect(RobotPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	RobotSocket = new QTcpSocket();
	connect(RobotSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));
	
    connectionTimer = new QTimer();
    connect(connectionTimer, SIGNAL(timeout()), this, SLOT(FindingRobotTimeOut()));

    callfuntionTimer = new QTimer();
//    connect(callfuntionTimer, SIGNAL(timeout()), this, SLOT(()));

	ExternalControllerPort = new QSerialPort();
	connect(ExternalControllerPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	ExternalControllerSocket = new QTcpSocket();
	connect(ExternalControllerSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

	SlidingPort = new QSerialPort();
	connect(SlidingPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	SlidingSocket = new QTcpSocket();
	connect(SlidingSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

	ConveyorPort = new QSerialPort();
	connect(ConveyorPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
	ConveyorSocket = new QTcpSocket();
	connect(ConveyorSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));

	TCPConnection = new TCPConnectionManager();
	OpenAvailableServer();

	TcpServer = TCPConnection->TcpServer;
	connect(TCPConnection, SIGNAL(NewConnection(QTcpSocket*)), this, SLOT(ReceiveNewConnectionFromServer(QTcpSocket*)));
}

void ConnectionManager::sendQueue()
{
	
}

void ConnectionManager::processReceiveData()
{
	if (receiveLine.mid(0, 2) == "Ok" || (receiveLine.indexOf('k') > -1 && receiveLine.indexOf('O') > -1) || receiveLine.mid(0, 7) == "Unknown")
	{
		if (!(IsRobotConnect() == true && IsRosSocket(IOSender)))
		{
			emit DeltaResponeGcodeDone();
		}		

		//sendQueue();

		if (transmitLine == "G28")
		{
			SendToRobot("Position");
		}
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

    if (receiveLine.indexOf(" V") > -1 && (receiveLine.indexOf("A") > -1 || receiveLine.indexOf(" V") > -1))
    {
        emit ReceiveInputIO(receiveLine);
    }

	if (receiveLine.at(0) == '#' && receiveLine.indexOf("=") > -1)
	{
		int symId = receiveLine.indexOf("=");
		QString name = receiveLine.mid(0, symId).replace(" ", "");
        QString valueS = receiveLine.mid(symId + 1).replace(" ", "");

        if (name == "#StartCapture" && valueS.toInt() == 1)
        {
            ReceiveCaptureSignalFromExternalAI();
        }

        if (name == "#Label")
        {
            emit ReceiveObjectInfoFromExternalAI(valueS);
        }
        if (name == "#Object")
        {
            emit ReceiveDisplayObjectFromExternalScript(valueS);
        }
        else
        {
            int value = valueS.toInt();
            emit ReceiveVariableChangeCommand(name, valueS);
        }
	}
	if (receiveLine.at(0) == '#' && receiveLine.indexOf("=") == -1)
	{
		receiveLine = receiveLine.replace(" ", "");
		receiveLine = receiveLine.replace("\n", "");
		receiveLine = receiveLine.replace("\r", "");

		QString name = receiveLine;
		emit RequestVariableValue(IOSender, name);
	}
	if (receiveLine.at(0) == 'r' && receiveLine.indexOf(":") > -1)
	{
		int symId = receiveLine.indexOf(":");

		QString request = receiveLine.mid(symId + 1);

		emit ReceiveRequestsFromExternal(request);
	}
}

void ConnectionManager::sendData(QSerialPort * com, QTcpSocket * socket, QString msg)
{
	if (msg[msg.length() - 1] != "\n")
		msg += "\n";

	Debug(QString("Software: ") + msg);	

	if (com != NULL)
	{
		if (com->isOpen())
		{
			com->write(msg.toStdString().c_str(), msg.size());
			return;
		}
	}
	if (socket != NULL)
	{
		if (socket->isOpen())
		{
			socket->write(msg.toStdString().c_str(), msg.size());
		}
	}
}

void ConnectionManager::OpenAvailableServer()
{
	int port = 8844;
	for (int i = 0; i < 10; i++)
	{
		bool isSuccess = TCPConnection->OpenServer("localhost", port + i);
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
	Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
	{
		QSerialPort* sP = new QSerialPort();

		QString portName = portInfo.portName();
		sP->setPortName(portName);
		sP->setBaudRate(baudrate);

		portList.push_back(sP);

		if (sP->open((QIODevice::ReadWrite)) == true)
		{
			connect(sP, SIGNAL(readyRead()), this, SLOT(ReadData()));

            QString name = sP->portName();

//            QThread::msleep(500);
//            sP->write("IsDelta\n");


		}
	}

    QTimer::singleShot(500, this, &ConnectionManager::SendRobotMsgToCOMPort);

}

void ConnectionManager::SendToRobot(QString msg)
{
	TCPConnection->SendMessageToROS("gcode " + msg);
	
	transmitLine = msg;

	sendData(RobotPort, RobotSocket, msg);
}

void ConnectionManager::ConveyorSend(QString msg)
{
	sendData(ConveyorPort, ConveyorSocket, msg);
}

void ConnectionManager::SlidingSend(QString msg)
{
	sendData(SlidingPort, SlidingSocket, msg);
}

void ConnectionManager::ExternalMCUSend(QString msg)
{
	sendData(ExternalControllerPort, ExternalControllerSocket, msg);
}

void ConnectionManager::ReadData()
{
	IOSender = qobject_cast<QIODevice*>(sender());

	QSerialPort* sP = qobject_cast<QSerialPort*>(sender());

	if (sP)
	{
		while (sP->canReadLine())
		{
			receiveLine = sP->readLine();

            if (sP == RobotPort)
            {
                emit ReceiveVariableChangeCommand("Response", receiveLine.replace("\n", "").replace("\r", ""));
            }

			if (sP == ExternalControllerPort)
			{
                emit ExternalMCUTransmitText(receiveLine);
			}

			emit FinishReadLine(receiveLine);

			if (receiveLine.mid(0, 8) == "YesDelta")
			{
				if (isDeltaPortConnected != true)
				{
					delete RobotPort;
					RobotPort = sP;
					emit DeltaResponeReady();

					isDeltaPortConnected = true;

				}
			}

			processReceiveData();
		}

		return;
	}
	
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	
	if (socket)
	{
		while (socket->canReadLine())
		{
			receiveLine = socket->readLine();

			for (int i = 0; i < TCPConnection->ClientList->size(); i++)
			{
				if (TCPConnection->ClientList->at(i)->socket == socket)
				{
					if (receiveLine.indexOf("ros") > -1)
					{
						TCPConnection->ClientList->at(i)->IsROS = true;
						break;
					}
				}
			}

			if (IsRosSocket(socket) == true)
			{
				TCPConnection->ProcessReceivedData(receiveLine);

                if (receiveLine.contains("ExternalScript"))
                {
                    emit ExternalScriptOpened(socket);
                }
			}

			if (socket == ExternalControllerSocket)
			{
                emit ExternalMCUTransmitText(receiveLine);
			}

			processReceiveData();
			
		}
	}
}



void ConnectionManager::FindingRobotTimeOut()
{
    static int order = 0;
	
	order++;

//	QString waitS = "";

//	for (int i = 0; i < order; i++)
//	{
//		waitS += ".";
//	}

//	Debug(waitS);

	if (order < 20 && isDeltaPortConnected == false)
		return;

	order = 0;

	for(int i = 0; i < portList.length(); i++)
	{
		if (portList.at(i)->portName() != RobotPort->portName())
		{
			portList.at(i)->close();
			delete portList.at(i);
		}
	}

	portList.clear();

    connectionTimer->stop();

    emit FinishFindingRobot();
}

void ConnectionManager::ReceiveNewConnectionFromServer(QTcpSocket * socket)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void ConnectionManager::SendRobotMsgToCOMPort()
{
    foreach(QSerialPort* sp, portList)
    {
        if (sp->isOpen())
        {
          sp->write("IsDelta\n");
        }
    }
    connectionTimer->start(200);
}
