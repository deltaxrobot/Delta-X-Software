//#include "ROS.h"

//#ifdef Q_OS_WIN

//HWND unityHWND;

//void ActivateUnityWindow()
//{
//	SendMessage(unityHWND, WM_ACTIVATE, WA_ACTIVE, 0);
//}

//BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
//	unityHWND = hwnd;
//	ActivateUnityWindow();
//	return 0;
//}

//ROS::ROS(QObject *parent, QFrame* panel, QString app)
//	: QObject(parent)
//{
//	display = panel;
//	displayParent = display->parentWidget();
//	appPath = app;
//	mParent = (MainWindow*)parent;

//	if (mParent->ID == 0)
//	{
//		displayLayout = new QHBoxLayout();
//		displayLayout->addWidget(display);
//	}

//	ROSTimer = new QTimer(this);
//	connect(ROSTimer, SIGNAL(timeout()), this, SLOT(ProcessROS()));
	
//}

//ROS::~ROS()
//{
//	SendMessage(unityHWND, WM_ACTIVATE, WA_INACTIVE, 0);
//}

//void ROS::Run()
//{
//	ROSTimer->start(200);
//}

//void ROS::initROS()
//{
//	// GET FILE
//	QString fileName = qApp->applicationDirPath() + appPath;

//	// PASS ARGS
//	QString _args = QString("-parentHWND %1").arg(display->winId());

//	//
//	PROCESS_INFORMATION procInfo = { 0 };
//	STARTUPINFO startupInfo = { 0 };
//	startupInfo.cb = sizeof(startupInfo);
//	startupInfo.dwFlags = STARTF_USESTDHANDLES;
//	startupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
//	startupInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//	startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);

//	//
//	HWND hwnd = (HWND)display->winId();
//	LPWSTR cmd = (LPWSTR)fileName.utf16();
//	LPWSTR args = (LPWSTR)_args.utf16();

//	BOOL bProcessStarted = CreateProcess(cmd, args, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &procInfo);

//	if (!bProcessStarted)
//	{
//		Debug("There was an error opening the ros program");
//	}

//	//					  //WAIT FOR START
//	//qint64 before = QDateTime::currentMSecsSinceEpoch();
//	//Sleep(100);
//	WaitForInputIdle(hwnd, 100);

//	//GET UNITY WINDOW HANDLE
//	//EnumChildWindows(hwnd, EnumChildProc, 0);
//	unityHWND = hwnd;

//	isRunning = true;
//}


//void ROS::SetConnectionManager(TCPConnectionManager * connectionMg)
//{
//	connectionManager = connectionMg;
//}

//void ROS::ResetView()
//{
//	MoveWindow(unityHWND, 0, 0, display->width()/2, display->height(), true);
//	ActivateUnityWindow();
//}

//void ROS::ProcessROS()
//{
//	static int  callingOrder = 0;

//	callingOrder += 1;

//	if (callingOrder == 1)
//	{
//		// if the new tab is open
//		if (mParent->ID != 0)
//		{
//			QMessageBox::information(mParent, "Sorry!", "The current version can only open ROS in the first robot");
//		}
//		else
//		{
//			initROS();
//		}
//	}

//	if (callingOrder == 10)
//	{
//		EnumChildWindows(unityHWND, EnumChildProc, 0);
//		//MoveWindow(unityHWND, 0, 0, display->width(), display->height(), true);
//		ActivateUnityWindow();
//	}

//	if (callingOrder == 10)
//	{
//		ROSTimer->stop();
//		callingOrder = 0;
//	}
//}

//QFrame * ROS::GetDisplay()
//{
//	return display;
//}

//void ROS::Foces()
//{
//	displayParent->setLayout(mParent->DeltaXMainWindows->at(0)->DeltaXROS->GetDisplayLayout());
//}

//QLayout * ROS::GetDisplayLayout()
//{
//	return displayLayout;
//}

//bool ROS::IsRunning()
//{
//	return isRunning;
//}

//void ROS::Close()
//{
//	QFrame* newFrameROS = new QFrame(display->parentWidget());
//	newFrameROS->setObjectName(QStringLiteral("frameROS"));
//	newFrameROS->setGeometry(QRect(0, 5, 400, 300));
//	newFrameROS->setStyleSheet(QStringLiteral(""));
//	newFrameROS->setFrameShape(QFrame::StyledPanel);
//	newFrameROS->setFrameShadow(QFrame::Raised);

//	delete display;
//	delete displayLayout;

//	display = newFrameROS;
//	displayLayout = new QHBoxLayout();
//	displayLayout->addWidget(display);
//	displayParent->setLayout(displayLayout);

//	isRunning = false;
//}

//void ROS::G01_Relative(float x, float y, float z)
//{
//	if (connectionManager == NULL)
//		return;

//	connectionManager->SendMessageToROS(QString("move triangle x ") + QString::number(x) + " y " + QString::number(y) + " z " + QString::number(z));
//}

//#endif
