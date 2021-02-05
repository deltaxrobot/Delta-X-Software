#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitVariables();
    InitEvents();

	hideExampleWidgets();
	//interpolateCircle();
	//makeEffectExample();
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitEvents()
{
    connect(ui->pbConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectDeltaRobot()));
	connect(ui->pbAddNewProgram, SIGNAL(clicked(bool)), this, SLOT(AddNewProgram()));
	connect(ui->pbRefreshGcodeFiles, SIGNAL(clicked(bool)), DeltaGcodeManager, SLOT(RefreshGcodeProgramList()));
	connect(ui->pbSortGcodeFiles, SIGNAL(clicked(bool)), DeltaGcodeManager, SLOT(SortProgramFiles()));
	connect(ui->pbSaveGcode, SIGNAL(clicked(bool)), this, SLOT(SaveProgram()));
	connect(ui->pbImportGcodeFiles, SIGNAL(clicked(bool)), this, SLOT(ImportGcodeFilesFromComputer()));
	connect(ui->pbUploadProgram, SIGNAL(clicked(bool)), this, SLOT(UploadGcodeFileToServer()));
	connect(ui->pbFindGcodeFile, SIGNAL(clicked(bool)), this, SLOT(SearchGcodeFile()));

	connect(ui->pbExecuteGcodes, SIGNAL(clicked(bool)), this, SLOT(ExecuteProgram()));
	connect(ui->pteGcodeArea, SIGNAL(cursorPositionChanged()), this, SLOT(ExecuteCurrentLine()));
	connect(ui->cbPositionToExecuteGcode, SIGNAL(currentIndexChanged(const QString &)), DeltaGcodeManager, SLOT(SetStartingGcodeEditorCursor(QString)));

	connect(ui->pbHome, SIGNAL(clicked(bool)), this, SLOT(Home()));
	connect(ui->pbW, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->pbZ, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->pbY, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->pbX, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leW, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leZ, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leY, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leX, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));

	connect(ui->hsGripperAngle, SIGNAL(valueChanged(int)), this, SLOT(AdjustGripperAngle(int)));
	connect(ui->pbGrip, SIGNAL(clicked(bool)), this, SLOT(Grip()));
	connect(ui->pbPump, SIGNAL(clicked(bool)), this, SLOT(SetPump(bool)));
	connect(ui->pbLaser, SIGNAL(clicked(bool)), this, SLOT(SetLaser(bool)));

	//connect(ui->pbSetSpeedConvenyor, SIGNAL(clicked(bool)), this, SLOT(SetConvenyorSpeed()));
	//connect(ui->pbGetPositionConvenyor, SIGNAL(clicked(bool)), this, SLOT(GetConvenyorPosition()));

	connect(ui->pbConveyorConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectConveyor()));
	connect(ui->cbConveyorMode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMode(int)));
	connect(ui->cbConveyorValueType, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));
	connect(ui->leConveyorvMovingValue, SIGNAL(returnPressed()), this, SLOT(MoveConveyor()));
	connect(ui->leSpeedOfPositionMode, SIGNAL(returnPressed()), this, SLOT(SetSpeedOfPositionMode()));

	connect(ui->pbSlidingConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectSliding()));
	connect(ui->pbSlidingHome, SIGNAL(clicked(bool)), this, SLOT(GoHomeSliding()));
	connect(ui->pbSlidingDisable, SIGNAL(clicked(bool)), this, SLOT(DisableSliding()));
	connect(ui->leSlidingSpeed, SIGNAL(returnPressed()), this, SLOT(SetSlidingSpeed()));
	connect(ui->leSlidingPosition, SIGNAL(returnPressed()), this, SLOT(SetSlidingPosition()));

	connect(ui->pbExternalControllerConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectExternalMCU()));
	connect(DeltaConnectionManager, SIGNAL(ExternalMCUTransmitText(QString)), this, SLOT(DisplayTextFromExternalMCU(QString)));
	connect(ui->leTransmitToMCU, SIGNAL(returnPressed()), this, SLOT(TransmitTextToExternalMCU()));

	connect(ui->pbUp, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveUp()));
	connect(ui->pbDown, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveDown()));
	connect(ui->pbForward, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveForward()));
	connect(ui->pbBackward, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveBackward()));
	connect(ui->pbLeft, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveLeft()));
	connect(ui->pbRight, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveRight()));
	connect(ui->leVelocity, SIGNAL(returnPressed()), this, SLOT(UpdateVelocity()));
	connect(ui->leAccel, SIGNAL(returnPressed()), this, SLOT(UpdateAccel()));

	connect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZLineEditValue(int)));
	connect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->vsAngleAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateWLineEditValue(int)));
	connect(ui->vsAngleAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(Delta2DVisualizer, SIGNAL(Moved(float, float, float, float)), this, SLOT(UpdateTextboxFrom2DControl(float, float, float, float)));
	
	
	connect(Delta2DVisualizer, SIGNAL(FinishMoving()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(Delta2DVisualizer, SIGNAL(CursorMoved(int, int)), SLOT(UpdateCursorPosition(int, int)));
	
	connect(ui->pbTurnOnROS, SIGNAL(clicked(bool)), this, SLOT(OpenROS()));
	connect(ui->cbROSCameraView, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeROSCameraView(int))); 
	connect(ui->cbEndEffector, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeEndEffector(int)));
	connect(ui->cbRobotVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRobotVersion(int)));
	connect(ui->btDeleteAllObjects, SIGNAL(clicked(bool)), this, SLOT(DeleteAllObjectsInROS()));
	connect(ui->pbClearDetectObjects, SIGNAL(clicked(bool)), this, SLOT(DeleteAllObjectsInROS()));

	connect(ui->leTerminal, SIGNAL(returnPressed()), this, SLOT(TerminalTransmit()));

	connect(DeltaConnectionManager, SIGNAL(FinishReadLine(QString)), this, SLOT(PrintReceiveData(QString)));
	connect(DeltaConnectionManager, SIGNAL(DeltaResponeReady()), this, SLOT(NoticeConnected()));
	connect(DeltaConnectionManager, SIGNAL(InHomePosition(float, float, float, float)), this, SLOT(UpdateGlobalHomePositionValueAndControlValue(float, float, float, float)));
	connect(DeltaConnectionManager, SIGNAL(ReceiveVariableChangeCommand(QString, float)), DeltaGcodeManager, SLOT(UpdateSystemVariable(QString, float)));
	connect(DeltaConnectionManager, SIGNAL(RequestVariableValue(QIODevice*, QString)), DeltaGcodeManager, SLOT(RespondVariableValue(QIODevice*, QString)));
	connect(DeltaConnectionManager, SIGNAL(ReceiveRequestsFromExternal(QString)), this, SLOT(ExecuteRequestsFromExternal(QString)));

	connect(ui->pbAddGcode, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));
	connect(ui->cbGcode, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeGcodeParameter()));

	connect(ui->pbFormat, SIGNAL(clicked(bool)), this, SLOT(StandardFormatEditor()));

	connect(ui->pbFilter, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenParameterPanel()));
	connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadTestImage()));
	connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadCamera()));
	connect(ui->pbObjectRect, SIGNAL(clicked(bool)), ui->lbScreenStreamer, SLOT(rectObject()));
	connect(ui->pbObjectLine, SIGNAL(clicked(bool)), ui->lbScreenStreamer, SLOT(lineObject()));
	connect(ui->pbObjectOrigin, SIGNAL(clicked(bool)), ui->lbScreenStreamer, SLOT(circleObject()));
	connect(ui->lbCameraLayer, SIGNAL(currentIndexChanged(int)), DeltaImageProcesser, SLOT(SelectLayer(int )));
	connect(ui->pbChangeXAxis, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(changeAxisDirection()));
	connect(ui->leFPS, SIGNAL(returnPressed()), DeltaImageProcesser, SLOT(SaveFPS()));
	connect(ui->pbClearDetectObjects, SIGNAL(clicked(bool)), DeltaImageProcesser->ObjectManager, SLOT(RemoveAllDetectObjects()));
	connect(ui->pbViewDataObjects, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
	connect(DeltaImageProcesser, SIGNAL(ObjectValueChanged(std::vector<cv::RotatedRect>)), TrackingObjectTable, SLOT(UpdateTable(std::vector<cv::RotatedRect>)));
	connect(DeltaImageProcesser, SIGNAL(ObjectValueChanged(std::vector<cv::RotatedRect>)), this, SLOT(AddObjectsToROS(std::vector<cv::RotatedRect>)));
	connect(ui->pbTransformPerspective, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnTransformPerspective(bool)));
	connect(ui->cbDisplayCalibInfo, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnCalibDisplay(bool)));
	connect(ui->pbExpandCameraWidget, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(ExpandCameraWidget(bool)));
	connect(ui->pbCameraWindowMode, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenCameraWindow()));
	connect(ui->lbScreenStreamer, SIGNAL(SizeChanged()), DeltaImageProcesser, SLOT(UpdateRatios())); 
	connect(ui->pbLoadCameraSetting, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadSetting()));
	connect(ui->pbSaveCameraSetting, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(SaveSetting()));

	connect(ui->leConvenyorSpeed, SIGNAL(returnPressed()), this, SLOT(SetConvenyorSpeed()));
	connect(ui->cbConveyorDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConvenyorSpeed()));

	connect(ui->lbScreenStreamer, SIGNAL(FinishDrawObject(int, int, int, int)), DeltaImageProcesser, SLOT(GetObjectInfo(int, int, int, int)));
	connect(ui->lbScreenStreamer, SIGNAL(FinishMeasureSpace(int)), DeltaImageProcesser, SLOT(GetDistance(int)));
	connect(ui->lbScreenStreamer, SIGNAL(FinishSelectPerspectivePoints(QPoint, QPoint, QPoint, QPoint)), DeltaImageProcesser, SLOT(GetPerspectivePoints(QPoint, QPoint, QPoint, QPoint)));
	connect(ui->lbScreenStreamer, SIGNAL(FinishSelectProcessRectangle(QRect)), DeltaImageProcesser, SLOT(GetProcessArea(QRect)));
	connect(ui->lbScreenStreamer, SIGNAL(FinishSelectCalibLine(QPoint, QPoint)), DeltaImageProcesser, SLOT(GetCalibLine(QPoint, QPoint)));
	connect(ui->lbScreenStreamer, SIGNAL(FinishSelectCalibPoint(int, int)), DeltaImageProcesser, SLOT(GetCalibPoint(int, int)));
	
	connect(ui->leXCoordinate, SIGNAL(textChanged(QString)), ui->lbScreenStreamer, SLOT(ChangeXCalibPoint(QString)));
	connect(ui->leYCoordinate, SIGNAL(textChanged(QString)), ui->lbScreenStreamer, SLOT(ChangeYCalibPoint(QString)));
	connect(ui->leWRec, SIGNAL(returnPressed()), this, SLOT(UpdateDetectObjectSize()));
	connect(ui->leLRec, SIGNAL(returnPressed()), this, SLOT(UpdateDetectObjectSize()));

	connect(ui->actionBaudrate, SIGNAL(triggered()), this, SLOT(ConfigConnection()));
	connect(ui->actionGcode, SIGNAL(triggered()), this, SLOT(OpenGcodeReference()));
	connect(ui->actionExecute_All, SIGNAL(triggered()), this, SLOT(ExecuteSelectPrograms()));
	connect(ui->actionExecute, SIGNAL(triggered()), this, SLOT(ExecuteProgram()));
	connect(ui->pbGcodeReference, SIGNAL(clicked(bool)), this, SLOT(OpenGcodeReference()));
	connect(ui->actionScale, SIGNAL(triggered(bool)), this, SLOT(ScaleUI()));

	connect(DeltaGcodeManager, SIGNAL(OutOfObjectVariable()), DeltaImageProcesser->ObjectManager, SLOT(RemoveOldestObject()));
	connect(DeltaGcodeManager, SIGNAL(JustUpdateVariable(QList<GcodeVariable>)), this, SLOT(DisplayGcodeVariable(QList<GcodeVariable>)));
	connect(DeltaGcodeManager, SIGNAL(MoveToNewPosition(float, float, float, float, float, float)), this, SLOT(UpdatePositionControl(float, float, float, float, float, float)));
	connect(DeltaGcodeManager, SIGNAL(DeleteAllObjects()), ui->pbClearDetectObjects, SLOT(click()));
	connect(DeltaGcodeManager, SIGNAL(DeleteObject1()), DeltaImageProcesser->ObjectManager, SLOT(RemoveOldestObject()));
	connect(DeltaGcodeManager, SIGNAL(PauseCamera()), DeltaImageProcesser, SLOT(PauseCamera()));
	connect(DeltaGcodeManager, SIGNAL(CaptureCamera()), DeltaImageProcesser, SLOT(CaptureCamera()));
	connect(DeltaGcodeManager, SIGNAL(ResumeCamera()), DeltaImageProcesser, SLOT(ResumeCamera()));

	connect(ui->pbPlayPauseCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(PlayCamera(bool)));
	connect(ui->pbCaptureCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(CaptureCamera()));

	connect(DeltaImageProcesser->ObjectManager, SIGNAL(NewUpdateObjectPosition(QString, float)), DeltaGcodeManager, SLOT(UpdateSystemVariable(QString, float)));

	connect(ui->pbOpenPicture, SIGNAL(clicked(bool)), DeltaDrawingExporter, SLOT(OpenImage()));
	connect(ui->pbPainting, SIGNAL(clicked(bool)), DeltaDrawingExporter, SLOT(ConvertToDrawingArea()));

	connect(ui->pbDrawLine, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectLineTool()));
	connect(ui->pbDrawRectangle, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectRectangleTool()));
	connect(ui->pbDrawCircle, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectCircleTool()));
	connect(ui->pbDrawArc, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectArcTool()));
	connect(ui->pbZoomIn, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectZoomInTool()));
	connect(ui->pbZoomOut, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectZoomOutTool()));
	connect(ui->pbCursor, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectCursor()));

	connect(ui->pbExportDrawingGcodes, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(ExportGcodes()));

	connect(ui->twDeltaManager, SIGNAL(tabBarClicked(int)), this, SLOT(ChangeDeltaDashboard(int)));
	connect(ui->twDeltaManager, SIGNAL(currentChanged(int)), this, SLOT(SelectTrueTabName(int)));

	connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceivePosition(float, float, float, float)), this, SLOT(UpdateTextboxFrom3DControl(float, float, float, float)));
	connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceiveVariableChangeCommand(QString, float)), DeltaGcodeManager, SLOT(UpdateSystemVariable(QString, float)));
	connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceiveOk()), this, SLOT(ROSResponse()));

}

void MainWindow::InitVariables()
{
    DeltaConnectionManager = new ConnectionManager();
	DeltaConnectionManager->SetBaudrate(115200);
	ui->lbIP->setText(QString("IP: ") + TCPConnectionManager::GetIP());
	ui->lbPort->setText(QString("Port: ") + QString::number(DeltaConnectionManager->TCPConnection->Port));

	DeltaGcodeManager = new GcodeProgramManager(this, ui->saProgramFiles, ui->wgProgramContainer, ui->pteGcodeArea, ui->pbExecuteGcodes, DeltaConnectionManager, Delta2DVisualizer);
	
	//DebugLB = ui->lbDebug;
	Debugs.push_back(ui->teDebug);

	DeltaGcodeManager->LoadPrograms();
	
    Delta2DVisualizer = new DeltaVisualizer(ui->wg2D);
    Delta2DVisualizer->setObjectName(QStringLiteral("2DArea"));
    Delta2DVisualizer->setGeometry(QRect(0, 0, 300, 300));
	Delta2DVisualizer->SetDivisionComboBox(ui->cbDivision);

	DeltaDrawingExporter = new DrawingExporter(this);
	DeltaDrawingExporter->SetDrawingParameterPointer(ui->lbImageForDrawing, ui->lbImageWidth, ui->lbImageHeight, ui->leHeightScale, ui->leWidthScale, ui->leSpace, ui->leDrawingThreshold, ui->hsDrawingThreshold, ui->cbDrawMethod, ui->cbConversionTool);
	DeltaDrawingExporter->SetDrawingAreaWidget(ui->lbDrawingArea);

	ui->lbDrawingArea->InitGrid();
	ui->lbDrawingArea->SetGcodeEditor(ui->pteGcodeArea);
	ui->lbDrawingArea->SetEffector(ui->cbDrawingEffector);

	//--------------Timer-------------

	EditorTimer = new QTimer(this);
	//connect(EditorTimer, SIGNAL(timeout()), this, SLOT(RunSmartEditor()));
	//EditorTimer->start(500);

	ConvenyorTimer = new QTimer(this);
	connect(ConvenyorTimer, SIGNAL(timeout()), this, SLOT(GetConvenyorPosition()));

	ShortcutKeyTimer = new QTimer(this);
	connect(ShortcutKeyTimer, SIGNAL(timeout()), this, SLOT(ProcessShortcutKey()));
	ShortcutKeyTimer->start(100);

	//EditorTimer->start(500);
	//------------ OpenGl Init ----------
	
	/*VisualArea = new GLWidget();
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(VisualArea);
    ui->wgOpenGl->setLayout(container);*/

	//---------- OpenCV Init -------------    

	DeltaImageProcesser = new ImageProcesser(this);
	DeltaImageProcesser->SetResultScreenPointer(ui->lbScreenStreamer);
	DeltaImageProcesser->SetObjectScreenPointer(ui->lbTrackingObject);
	DeltaImageProcesser->SetCameraInfoWidget(ui->leFPS, ui->lbCameraState, ui->pbPlayPauseCamera);
	DeltaImageProcesser->SetDetectParameterPointer(ui->leWRec, ui->leLRec, ui->leRealDistance, ui->leXCoordinate, ui->leYCoordinate);
	DeltaImageProcesser->SetTrackingWidgetPointer(ui->lbTrackingObjectNumber, ui->lbVisibleObjectNumber);
	DeltaImageProcesser->CameraScrollArea = ui->saCamera;

	TrackingObjectTable = new ObjectVariableTable(this);

	//------------------Blockly---------------
	//ui->wevBlockly->setUrl(QUrl(QStringLiteral("C:/Users/Admin/Downloads/blockly-master/blockly-master/demos/code/index.html")));

	//----------------ROS-------------------
#ifdef Q_OS_WIN
//    DeltaXROS = new ROS(this, ui->frameROS, "/ros/Delta X Ros.exe");
//	DeltaXROS->SetConnectionManager(DeltaConnectionManager->TCPConnection);
	//DeltaXROS->Run();
#endif
	//---------------Socket------------------------
	

	//---------------------- Update ----------------------

	HttpManager = new QNetworkAccessManager(this);
	connect(HttpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(FinishedRequest(QNetworkReply*)));

	QNetworkRequest request = QNetworkRequest(QUrl("http://imwi.space/admin/login.php"));
	request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
	QUrlQuery params;
	params.addQueryItem("user", "trungdoanhong");
	params.addQueryItem("pass", "doanhongtrung");
	HttpManager->post(request, params.query().toUtf8());

	//------------ UI ----------------
	Delta2DVisualizer->ChangeXY(0, 0);

    //------------------- Linux -----------------
    QString cmd = "stty -F /dev/ttyACM0 -hupcl";
    QProcess *process = new QProcess;
    process->start(cmd);
    process->waitForBytesWritten();
    process->waitForFinished();
}

void MainWindow::FinishedRequest(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		return;
	}

	QString respondString = QString(reply->readAll());

	if (respondString.indexOf(("ok")) > -1)
	{
		QNetworkRequest request = QNetworkRequest(QUrl("http://imwi.space/admin/server.php?software=DeltaXSoftware&info=version"));
		request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
		HttpManager->get(request);
	}
	else
	{
		QVersionNumber currentVersion = QVersionNumber::fromString(respondString);
		QVersionNumber appVersion = QVersionNumber::fromString(SoftwareVersion);
		int compare = QVersionNumber::compare(appVersion, currentVersion);

		if (compare != 0)
		{
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, "Have a new version of Delta X Software", "Do you want to update?",
				QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes) {
				QUrl myUrl("https://sourceforge.net/projects/delta-x-software/files/");
				QDesktopServices::openUrl(myUrl);
				QApplication::closeAllWindows();
				QApplication::quit();
			}
		}
	}
}

void MainWindow::ExportBlocklyToGcode()
{
	/*QWebEnginePage* clone = new QWebEnginePage();
	
	ui->wevBlockly->page()->runJavaScript("document.getElementsByTagName(\"body\")[0].innerHTML = document.getElementById(\"content_javascript\").innerText");

	ui->wevBlockly->page()->toPlainText([this](const QString &result)
	{
		ui->pteGcodeArea->setText(result);
	});*/
}

void MainWindow::OpenROS()
{
#ifdef Q_OS_WIN
//    if (DeltaXROS->IsRunning())
//    {
//        DeltaXROS->Close();
//        ui->pbTurnOnROS->setText("Turn on ROS");
//    }
//    else
//    {
//        DeltaXROS->Run();
//        ui->pbTurnOnROS->setText("Turn off ROS");
//    }
#else
    QMessageBox::information(this, "Noti", "Currently, ROS is not available on Linux");
#endif
}


void MainWindow::ChangeROSCameraView(int index)
{
	DeltaConnectionManager->TCPConnection->SendMessageToROS(QString("update camera_position ") + QString::number(index));
}

void MainWindow::ChangeEndEffector(int index)
{
	DeltaConnectionManager->TCPConnection->SendMessageToROS(QString("update end_effector ") + QString::number(index));
}

void MainWindow::ChangeRobotVersion(int index)
{
	DeltaConnectionManager->TCPConnection->SendMessageToROS(QString("update robot ") + QString::number(index));
}

void MainWindow::ScaleUI()
{
	QSettings settings("setting.ini", QSettings::IniFormat);

	UIScale = settings.value("scale").toFloat();

	bool ok;
	QString text = QInputDialog::getText(this, tr("Scale"),
	tr("Value:"), QLineEdit::Normal,
	QString::number(UIScale), &ok);
	if (ok && !text.isEmpty())
	{
		float scale = text.toFloat();

		if (scale < 1.0f)
		{
			QMessageBox::information(this, "Refuse", "The scale value must be >= 1.0");
			return;
		}

		std::string scaleAsString = text.toStdString();
		QByteArray scaleAsQByteArray(scaleAsString.c_str(), scaleAsString.length());
		qputenv("QT_SCALE_FACTOR", scaleAsQByteArray);

		settings.setValue("scale", text);

		qApp->quit();
		QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
	}
}

void MainWindow::ExecuteRequestsFromExternal(QString request)
{
	request = request.replace("\n", "");
	request = request.replace("\r", "");

	if (request == "Execute All")
	{
		ExecuteSelectPrograms();
	}
}

void MainWindow::ChangeParentForWidget(bool state)
{
	
}

void MainWindow::AddInstance(QList<MainWindow*>* deltaXMainWindows)
{
	if (deltaXMainWindows == NULL)
	{
		DeltaXMainWindows = new QList<MainWindow*>();
		DeltaXMainWindows->push_back(this);
	}
	else
	{
		DeltaXMainWindows = deltaXMainWindows;
		DeltaXMainWindows->push_back(this);
		initTabs();
	}
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Delta X Software",
		tr("Are you sure?\n"), QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		qApp->exit();
		event->accept();
	}
}

void MainWindow::ConnectDeltaRobot()
{
	if (ui->cbAutoConnect->isChecked() == false)
	{
		bool isConnect = OpenConnectionDialog(DeltaConnectionManager->RobotPort, DeltaConnectionManager->RobotSocket, ui->pbConnect);

		if (isConnect == true)
		{
			DeltaConnectionManager->SendToRobot("IsDelta");
			DeltaConnectionManager->SendToRobot("IsDelta");
		}

		return;
	}

	if (ui->pbConnect->text() == "Connect" && !DeltaConnectionManager->IsRobotConnect())
	{
		DeltaConnectionManager->FindDeltaRobot();
	}

	else if (ui->pbConnect->text() == "Disconnect")
	{
		ui->pbConnect->setText("Connect");

		if (DeltaConnectionManager->IsRobotConnect())
			DeltaConnectionManager->DisconnectRobot();
	}
}

void MainWindow::RunSmartEditor()
{
	
}

void MainWindow::StandardFormatEditor()
{
	if (ui->cbAutoNumbering->isChecked() == true)
	{
		QString editorText = ui->pteGcodeArea->toPlainText();

		QList<QString> lines = editorText.split('\n');
		QList<QString> oldNumbers;
		QList<QString> newNumbers;
		QList<QString> oldGcodes;

		QString oldNumber = "";

		if (lines.size() > 4000)
		{
			QMessageBox::information(this, "Warning", "Too many g-code lines ( > 4000 ) will take time to format. You should divide the program into multiple files and use M98 F[filename] to execute each files.");
			return;
		}

		editorText = "";

		int i = 0;

		foreach(QString line, lines)
		{
			line = line.replace("  ", " ");
			oldNumber = "";
			while (1)
			{
				if (line[0] == ' ')
				{
					line.replace(" ", "");
				}
				else
				{
					break;
				}
			}

			if (line[0] == 'N')
			{
				int spacePos = line.indexOf(' ');
				QString mS = line.mid(0, spacePos + 1);
				oldNumber = line.mid(1, spacePos);

				line.replace(mS, "");
			}

			while (1)
			{
				if (line[0] == ' ')
				{
					line.replace(" ", "");
				}
				else
				{
					break;
				}
			}

			if (line != "")
			{
				if (line[0] != ';')
				{
					QString numberS = QString("N") + QString::number(i);
					newNumbers.push_back(QString::number(i));
					oldNumbers.push_back(oldNumber);
					line = numberS + " " + line;
				}
			}

			editorText += line + "\n";
			i += 5;
		}

		int gotoCursor = 0;
		gotoCursor = editorText.indexOf("GOTO", gotoCursor);
		int gotoEnd = 0;

		while (gotoCursor > -1)
		{
			//gotoEnd = editorText.indexOf("\n", gotoCursor);
			QString gotoIndexS = "";
			for (int i = 0; i < 20; i++)
			{
				QChar c = editorText.at(gotoCursor + 5 + i);
				if (c.isDigit())
					gotoIndexS += c;
				else
					break;
			}

			gotoCursor = editorText.indexOf("GOTO", gotoCursor + 5);

			for (int i = 0; i < oldNumbers.size(); i++)
			{
				if (oldNumbers.at(i).toInt() == gotoIndexS.toInt())
				{
					QString old = QString("GOTO ") + gotoIndexS;
					QString replace = QString("GOTO ") + newNumbers.at(i);
					editorText.replace(old, replace);
				}
			}
		}
		ui->pteGcodeArea->setPlainText(editorText);
	}

	QTextCharFormat reset;
	ui->pteGcodeArea->setCurrentCharFormat(reset);
	ui->pteGcodeArea->currentCharFormat();

	if (ui->cbFormatColor->isChecked() == true)
	{
		QString htmlText = ui->pteGcodeArea->toHtml();

		htmlText = replaceHtmlSection(">;", 1, 200, "<", "<span style=\"font-style:italic;color:#00aa00;\">", "</span>", htmlText);
		htmlText = replaceHtmlSection(" O", 1, 50, "<", "<span style =\"font-weight:600;\">", "</span>", htmlText);
		htmlText = replaceHtmlSection("#", 0, 6, "&&&", "<span style=\"font-style:italic;\">", "</span>", htmlText);

		htmlText = boldKey("G01", htmlText);
		htmlText = boldKey("G02", htmlText);
		htmlText = boldKey("G03", htmlText);
		htmlText = boldKey("G04", htmlText);
		htmlText = boldKey("G28", htmlText);
		htmlText = boldKey("M204", htmlText);
		htmlText = boldKey("M360", htmlText);
		htmlText = boldPlusKey("GOTO", "color:#ff5500;", htmlText);
		htmlText = boldPlusKey("IF", "color:#00aa00;", htmlText);
		htmlText = boldPlusKey("THEN", "color:#00aa00;", htmlText);
		htmlText = boldKey("M99", htmlText);
		htmlText = boldKey("M98", htmlText);
		htmlText = boldKey("M05", htmlText);
		htmlText = boldKey("M04", htmlText);
		htmlText = boldKey("M03", htmlText);		

		int beginKey = -1;
		int endKey = 0;

		ui->pteGcodeArea->setHtml(htmlText);
	}
	/*QList<QString> lines = htmlText.split('\n');

	foreach(QString line, lines)
	{
		int beginKey = line.indexOf("G01");
		int endKey = line.indexOf(" ", beginKey);
	}*/
}

void MainWindow::OpenGcodeReference()
{
	GcodeReference* gcodeReferenceWindow = new GcodeReference();
	gcodeReferenceWindow->show();
}

void MainWindow::ConfigConnection()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Baudrate for COM"),
		tr("Baudrate:"), QLineEdit::Normal,
		QString::number(DeltaConnectionManager->GetBaudrate()), &ok);
	if (ok && !text.isEmpty())
		DeltaConnectionManager->SetBaudrate(text.toInt());
}

void MainWindow::ChangeDeltaDashboard(int index)
{
	if (ui->twDeltaManager->count() == index + 1)
	{
		if (ID == 0)
		{
			if (DeltaXMainWindows == NULL)
			{
				DeltaXMainWindows = new QList<MainWindow*>();
				DeltaXMainWindows->push_back(this);
			}
		}

		MainWindow* mainWindow = new MainWindow();
		mainWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainWindow->ID = DeltaXMainWindows->size();
		mainWindow->Name = QString("Delta X ") + QString::number(mainWindow->ID + 1);

		QAction *actionNewDelta_X;
		actionNewDelta_X = new QAction(mainWindow);

		actionNewDelta_X->setCheckable(true);
		actionNewDelta_X->setChecked(true);
		actionNewDelta_X->setText(QString("Delta X ") + QString::number(mainWindow->ID + 1));
		DeltaXMainWindows->at(0)->ui->menuExecute->addAction(actionNewDelta_X);

		mainWindow->AddInstance(this->DeltaXMainWindows);
		mainWindow->ui->lbID->setText(QString("ID: ") + QString::number(mainWindow->ID));
		mainWindow->SelectedAction = actionNewDelta_X;

		mainWindow->show();

		for (int i = 0; i < DeltaXMainWindows->size() - 1; i++)
		{
			DeltaXMainWindows->at(i)->ui->twDeltaManager->setTabText(index, QString("Delta") + QString::number(index + 1));
			QWidget *newDeltaTab = new QWidget();
			DeltaXMainWindows->at(i)->ui->twDeltaManager->addTab(newDeltaTab, QString());
			DeltaXMainWindows->at(i)->ui->twDeltaManager->setTabText(DeltaXMainWindows->at(i)->ui->twDeltaManager->indexOf(newDeltaTab), "+");
		}

		/*DeltaXDashboard* dashBoard = new DeltaXDashboard(ui, this);
		dashBoard->InitVariable();
		DeltaXDashboards.push_back(dashBoard);*/
	}
	else
	{
		if (DeltaXMainWindows == NULL)
			return;
		if (DeltaXMainWindows->count() == 0)
			return;

		//DeltaXMainWindows->at(index)->setWindowFlags(Qt::WindowStaysOnTopHint);
		DeltaXMainWindows->at(index)->activateWindow();
		DeltaXMainWindows->at(index)->show();
        DeltaXMainWindows->at(index)->setFocus();
	}
	Debug(QString::number(index));
}

void MainWindow::SelectTrueTabName(int index)
{
	for (int i = 0; i < DeltaXMainWindows->size(); i++)
	{
		if (DeltaXMainWindows->at(i) != NULL)
		{
			if (DeltaXMainWindows->at(i)->ui != NULL)
			{
				if (DeltaXMainWindows->at(i)->ui->twDeltaManager != NULL)
				{
					DeltaXMainWindows->at(i)->ui->twDeltaManager->setCurrentIndex(i);
				}
			}
		}
	}
}

void MainWindow::AddNewProgram()
{
	DeltaGcodeManager->AddNewProgram();
}

void MainWindow::SaveProgram()
{
	DeltaGcodeManager->SaveGcodeIntoFile();
}

void MainWindow::ExecuteProgram()
{
	QPushButton* pbExe = qobject_cast<QPushButton*>(sender());

	if (pbExe->isChecked())
	{

	}
	else
	{
		DeltaGcodeManager->Stop();
		if (DeltaGcodeManager->InsideGcodeProgramManager != NULL)
		{
			DeltaGcodeManager->InsideGcodeProgramManager->Stop();
		}
		return;
	}

	SaveProgram();

	QString exeGcodes = ui->pteGcodeArea->toPlainText();
	DeltaGcodeManager->ExecuteGcode(exeGcodes, true);
}

void MainWindow::ImportGcodeFilesFromComputer()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open G-code Files"), "",	tr("G-code file (*.dtgc);;All Files (*)"));

    foreach (QString fileName, fileNames)
	{
		QFileInfo fileInfo(fileName);
		QString newFullName = QDir::currentPath() + "/" + fileInfo.fileName();

		if (QFile::exists(newFullName))
		{
			QFile::remove(newFullName);
		}


		if (QFile::copy(fileName, newFullName) == false)
		{
			Debug(QString("Can't import ") + fileName);
		}
	}

	DeltaGcodeManager->RefreshGcodeProgramList();
}

void MainWindow::UploadGcodeFileToServer()
{
	QMessageBox::information(this, "Sorry!", "This function is not yet available");
}

void MainWindow::SearchGcodeFile()
{
	bool ok;
	QString searchValue = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("File Name:"), QLineEdit::Normal, "", &ok);
	if (ok && !searchValue.isEmpty())
	{
		QStringList nameList;
		for(int i = 0; i < DeltaGcodeManager->ProgramList->count(); i++)
		{
			nameList.push_back(DeltaGcodeManager->ProgramList->at(i)->GetName().toLower());
		}		

		QStringList result = nameList.filter(searchValue.toLower(), Qt::CaseSensitive);

		if (result.count() == 0)
		{
			Debug("No result");
			return;
		}

		for (int i = 0; i < DeltaGcodeManager->ProgramList->count(); i++)
		{
			QString name1 = DeltaGcodeManager->ProgramList->at(i)->GetName().toLower();
			QString name2 = result.at(0);
			if (name1 == name2)
			{
				QPoint pos = DeltaGcodeManager->ProgramList->at(i)->GetPosition();
				DeltaGcodeManager->saProgramFilesScrollArea->verticalScrollBar()->setValue(pos.y());

				DeltaGcodeManager->ProgramList->at(i)->SelectNewProgram();
				return;
			}
		}
	};
}

void MainWindow::ExecuteSelectPrograms()
{
	if (DeltaXMainWindows == NULL)
	{
		ui->pbExecuteGcodes->click();
		return;
	}
	QList<QAction*> actions = ui->menuExecute->actions();
	for (int i = 0; i < actions.size(); i++)
	{
		if (actions.at(i)->text().indexOf("Delta X") > -1)
		{
			QString actionName = actions.at(i)->text();
			if (actions.at(i)->isChecked() == true)
			{				
				for (int j = 0; j < DeltaXMainWindows->size(); j++)
				{
					if (DeltaXMainWindows->at(j)->Name == actionName)
					{
						DeltaXMainWindows->at(j)->ui->pbExecuteGcodes->click();
					}
				}
			}
		}
	}
}

void MainWindow::ExecuteCurrentLine()
{
	if (ui->cbLockGcodeEditor->isChecked() == false)
	{
		return;
	}

	QTextCursor cursor;
	QString line;

	cursor = ui->pteGcodeArea->textCursor();
	cursor.movePosition(QTextCursor::StartOfBlock);
	cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
	line = cursor.selectedText();

	DeltaGcodeManager->ExecuteGcode(line);
}

void MainWindow::UpdateZLineEditValue(int z)
{
	ui->leZ->setText(QString::number(Delta2DVisualizer->ZHome - z));

	if (ui->cbGcode->currentText() == "G01")
	{
		ui->leAg3->setText(QString::number(Delta2DVisualizer->Z));
	}
}

void MainWindow::UpdateWLineEditValue(int w)
{
	ui->leW->setText(QString::number(w));

	if (ui->cbGcode->currentText() == "G01")
	{
		ui->leAg4->setText(QString::number(Delta2DVisualizer->W));
	}
}

void MainWindow::UpdateDeltaPositionFromLineEditValue()
{
	Delta2DVisualizer->X = ui->leX->text().toFloat();
	Delta2DVisualizer->Y = ui->leY->text().toFloat();
	Delta2DVisualizer->Z = ui->leZ->text().toFloat();
	Delta2DVisualizer->W = ui->leW->text().toFloat();

	ui->vsZAdjsution->setValue(Delta2DVisualizer->ZHome - Delta2DVisualizer->Z);
	Delta2DVisualizer->ChangeXY(ui->leX->text().toFloat(), ui->leY->text().toFloat());

	if (ui->cbGcode->currentText() == "G01")
	{
		ui->leAg1->setText(QString::number(Delta2DVisualizer->X));
		ui->leAg2->setText(QString::number(Delta2DVisualizer->Y));
		ui->leAg3->setText(QString::number(Delta2DVisualizer->Z));
		ui->leAg4->setText(QString::number(Delta2DVisualizer->W));
	}

	DeltaConnectionManager->SendToRobot(QString("G01 X") + ui->leX->text() + QString(" Y") + ui->leY->text() + QString(" Z") + ui->leZ->text() + QString(" W") + ui->leW->text() + "\n");
}

void MainWindow::UpdateTextboxFrom2DControl(float x, float y, float z, float w)
{
	ui->leX->setText(QString::number(x));
	ui->leY->setText(QString::number(y));
	ui->leZ->setText(QString::number(z));
	ui->leW->setText(QString::number(w));
}

void MainWindow::UpdateTextboxFrom3DControl(float x, float y, float z, float w)
{
	if (x != NULL_NUMBER)
	{
		ui->leX->setText(QString::number(x));
	}
	if (y != NULL_NUMBER)
	{
		ui->leY->setText(QString::number(y));
	}
	
	if (z != NULL_NUMBER)
	{
		ui->leZ->setText(QString::number(z + Delta2DVisualizer->ZHome));
	}
	if (w != NULL_NUMBER)
	{
		ui->leW->setText(QString::number(w));
	}

	UpdateDeltaPositionFromLineEditValue();
}

void MainWindow::UpdatePositionControl(float x, float y, float z, float w, float f, float a)
{
	if (x == 0 && y == 0 && z == 0 && w == 0)
	{
		x = Delta2DVisualizer->XHome;
		y = Delta2DVisualizer->YHome;
		z = Delta2DVisualizer->ZHome;
		w = Delta2DVisualizer->WHome;
	}

	ui->leX->setText(QString::number(x));
	ui->leY->setText(QString::number(y));
	ui->leZ->setText(QString::number(z));
	ui->leW->setText(QString::number(w));
	ui->leVelocity->setText(QString::number(f));
	ui->leAccel->setText(QString::number(a));

	Delta2DVisualizer->X = x;
	Delta2DVisualizer->Y = y;
	Delta2DVisualizer->Z = z;
	Delta2DVisualizer->W = w;

	ui->vsZAdjsution->setValue(Delta2DVisualizer->ZHome - Delta2DVisualizer->Z);
	Delta2DVisualizer->ChangeXY(x, y);

	if (ui->cbGcode->currentText() == "G01")
	{
		ui->leAg1->setText(QString::number(Delta2DVisualizer->X));
		ui->leAg2->setText(QString::number(Delta2DVisualizer->Y));
		ui->leAg3->setText(QString::number(Delta2DVisualizer->Z));
		ui->leAg4->setText(QString::number(Delta2DVisualizer->W));
	}
}

void MainWindow::UpdateGlobalHomePositionValueAndControlValue(float x, float y, float z, float w)
{
	Delta2DVisualizer->XHome = x;
	Delta2DVisualizer->YHome = y;
	Delta2DVisualizer->ZHome = z;
	Delta2DVisualizer->WHome = w;

	UpdateTextboxFrom2DControl(x, y, z, w);
	UpdateDeltaPositionFromLineEditValue();
}

void MainWindow::UpdateVelocity()
{
	DeltaConnectionManager->SendToRobot(QString("G01 F") + ui->leVelocity->text());
}

void MainWindow::UpdateAccel()
{
	DeltaConnectionManager->SendToRobot(QString("M204 A") + ui->leAccel->text());
}

void MainWindow::AdjustGripperAngle(int angle)
{
	DeltaConnectionManager->SendToRobot(QString("M360 E1"));
	DeltaConnectionManager->SendToRobot(QString("M03 S") + QString::number(angle * 5));

	ui->lbGripperValue->setText(QString::number(angle * 5));
}

void MainWindow::Grip()
{
	DeltaConnectionManager->SendToRobot(QString("M360 E1"));
	if (ui->pbGrip->text() == "Grip")
	{
		ui->pbGrip->setText("Release");
		DeltaConnectionManager->SendToRobot(QString("M03 S") + ui->leGripperMax->text());

		ui->hsGripperAngle->blockSignals(true);
		ui->hsGripperAngle->setValue(ui->leGripperMax->text().toInt() / 5);
		ui->hsGripperAngle->blockSignals(false);
		
		ui->lbGripperValue->setText(ui->leGripperMax->text());
	}
	else
	{
		ui->pbGrip->setText("Grip");
		DeltaConnectionManager->SendToRobot(QString("M03 S") + ui->leGripperMin->text());

		ui->hsGripperAngle->blockSignals(true);
		int vl = ui->leGripperMin->text().toInt() / 5;
		ui->hsGripperAngle->setValue(vl);
		ui->hsGripperAngle->blockSignals(false);

		ui->lbGripperValue->setText(ui->leGripperMin->text());
		
	}
}

void MainWindow::SetPump(bool value)
{
	DeltaConnectionManager->SendToRobot(QString("M360 E0"));
	if (value == true)
	{
		DeltaConnectionManager->SendToRobot(QString("M04"));
	}
	else
	{
		DeltaConnectionManager->SendToRobot(QString("M05"));
	}
}

void MainWindow::SetLaser(bool value)
{
	DeltaConnectionManager->SendToRobot(QString("M360 E3"));
	if (value == true)
	{
		DeltaConnectionManager->SendToRobot(QString("M04"));
	}
	else
	{
		DeltaConnectionManager->SendToRobot(QString("M05"));
	}
}

void MainWindow::Home()
{
	DeltaConnectionManager->SendToRobot("G28");

	ui->leX->setText(QString::number(Delta2DVisualizer->XHome));
	ui->leY->setText(QString::number(Delta2DVisualizer->YHome));
	ui->leZ->setText(QString::number(Delta2DVisualizer->ZHome));
	ui->leW->setText(QString::number(Delta2DVisualizer->WHome));

	Delta2DVisualizer->X = Delta2DVisualizer->XHome;
	Delta2DVisualizer->Y = Delta2DVisualizer->YHome;
	Delta2DVisualizer->Z = Delta2DVisualizer->ZHome;
	Delta2DVisualizer->W = Delta2DVisualizer->WHome;

	Delta2DVisualizer->ChangeXY(0, 0);
	ui->vsZAdjsution->setValue(0);
}

void MainWindow::UpdateConvenyorPosition(float x, float y)
{
	//ui->leCurrentConvenyoPosition->setText(QString::number(x));
}

void MainWindow::DisplayGcodeVariable(QList<GcodeVariable> gcodeVariables)
{
    foreach (GcodeVariable var, gcodeVariables)
	{
		if (var.Name == ui->leVariable1->text())
		{
			ui->lbVar1->setText(QString::number(var.Value));
		}
		if (var.Name == ui->leVariable2->text())
		{
			ui->lbVar2->setText(QString::number(var.Value));
		}
		if (var.Name == ui->leVariable3->text())
		{
			ui->lbVar3->setText(QString::number(var.Value));
		}
		if (var.Name == ui->leVariable4->text())
		{
			ui->lbVar4->setText(QString::number(var.Value));
		}
		if (var.Name == ui->leVariable5->text())
		{
			ui->lbVar5->setText(QString::number(var.Value));
		}
		if (var.Name == ui->leVariable6->text())
		{
			ui->lbVar6->setText(QString::number(var.Value));
		}
	}
}

void MainWindow::SetConvenyorSpeed()
{
	float vel = ui->leConvenyorSpeed->text().toInt();
	QString directionName = ui->cbConveyorDirection->currentText();

	DeltaImageProcesser->SetConvenyorVelocity(vel, directionName);
}

void MainWindow::GetConvenyorPosition()
{
	
}

void MainWindow::TurnEnoughConvenyorPositionGetting()
{
	
}

void MainWindow::AddGcodeLine()
{
	QString gcodeName = ui->cbGcode->currentText();

	QString ag1 = ui->leAg1->text() != "" ? (QString(" ") + ui->lbAg1->text() + ui->leAg1->text()) : "";
	QString ag2 = ui->leAg2->text() != "" ? (QString(" ") + ui->lbAg2->text() + ui->leAg2->text()) : "";
	QString ag3 = ui->leAg3->text() != "" ? (QString(" ") + ui->lbAg3->text() + ui->leAg3->text()) : "";
	QString ag4 = ui->leAg4->text() != "" ? (QString(" ") + ui->lbAg4->text() + ui->leAg4->text()) : "";
	QString ag5 = ui->leAg5->text() != "" ? (QString(" ") + ui->lbAg5->text() + ui->leAg5->text()) : "";
	QString ag6 = ui->leAg6->text() != "" ? (QString(" ") + ui->lbAg6->text() + ui->leAg6->text()) : "";

	DeltaGcodeManager->AddGcodeLine(gcodeName + ag1 + ag2 + ag3 + ag4 + ag5 + ag6);
}

void MainWindow::ChangeGcodeParameter()
{
	QString gcodeName = ui->cbGcode->currentText();

	ui->lbAg1->setText("");
	ui->lbAg2->setText("");
	ui->lbAg3->setText("");
	ui->lbAg4->setText("");
	ui->lbAg5->setText("");
	ui->lbAg6->setText("");

	ui->leAg1->setText("");
	ui->leAg2->setText("");
	ui->leAg3->setText("");
	ui->leAg4->setText("");
	ui->leAg5->setText("");
	ui->leAg6->setText("");

	if (gcodeName == "G01")
	{
		ui->lbAg1->setText("X");
		ui->lbAg2->setText("Y");
		ui->lbAg3->setText("Z");
		ui->lbAg4->setText("W");
		ui->lbAg5->setText("F");

		ui->leAg1->setText(QString::number(Delta2DVisualizer->X));
		ui->leAg2->setText(QString::number(Delta2DVisualizer->Y));
		ui->leAg3->setText(QString::number(Delta2DVisualizer->Z));
	}
	else if (gcodeName == "G02" || gcodeName == "G03")
	{
		ui->lbAg1->setText("F");
		ui->lbAg2->setText("I");
		ui->lbAg3->setText("J");
		ui->lbAg4->setText("X");
		ui->lbAg5->setText("Y");
	}
	else if (gcodeName == "G05")
	{
		ui->lbAg1->setText("I");
		ui->lbAg2->setText("J");
		ui->lbAg3->setText("P");
		ui->lbAg4->setText("Q");
		ui->lbAg5->setText("X");
		ui->lbAg6->setText("Y");
	}
	else if (gcodeName == "M03" || gcodeName == "M04")
	{
		ui->lbAg1->setText("S");
	}
	else if (gcodeName == "M204")
	{
		ui->lbAg1->setText("A");
	}
}

void MainWindow::UpdateDetectObjectSize()
{
	float realObjLength = ui->leLRec->text().toFloat();
	float realObjWidth = ui->leWRec->text().toFloat();

	float lObjectInWidget = realObjLength * DeltaImageProcesser->DnRratio;
	float wObjectInWidget = realObjWidth * DeltaImageProcesser->DnRratio;

	DeltaImageProcesser->GetObjectInfo(lObjectInWidget, wObjectInWidget);
}

void MainWindow::UpdateCursorPosition(int x, int y)
{
	ui->lbXCursor->setText(QString::number(x));
	ui->lbYCursor->setText(QString::number(y));
}

void MainWindow::AddObjectsToROS(std::vector<cv::RotatedRect> ObjectContainer)
{
	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		QString rosGcode = "update object O_" + QString::number(i) + " ";
		rosGcode += ui->leWRec->text() + " ";
		rosGcode += ui->leLRec->text() + " ";
		rosGcode += ui->leHRec->text() + " ";

		rosGcode += QString::number(ObjectContainer.at(i).center.x) + " ";
		rosGcode += QString::number(ObjectContainer.at(i).center.y) + " ";
		rosGcode += "0 ";
		
		int angle = ObjectContainer.at(i).angle + 180;

		if (ObjectContainer.at(i).size.width > ObjectContainer.at(i).size.height)
		{
			angle = ObjectContainer.at(i).angle + 90;
		}

		rosGcode += QString::number(angle);

		DeltaConnectionManager->TCPConnection->SendMessageToROS(rosGcode);
	}
}

void MainWindow::DeleteAllObjectsInROS()
{
	DeltaConnectionManager->TCPConnection->SendMessageToROS("delete all");
}

void MainWindow::ConnectConveyor()
{
	OpenConnectionDialog(DeltaConnectionManager->ConveyorPort, DeltaConnectionManager->ConveyorSocket, ui->pbConveyorConnect);
}

void MainWindow::SetConveyorMode(int mode)
{
	DeltaConnectionManager->ConveyorSend(QString("M310 ") + QString::number(mode));
}

void MainWindow::SetConveyorMovingMode(int mode)
{
	if (mode == 0)
	{
		ui->lbSpeedOfPositionMode->setEnabled(false);
		ui->leSpeedOfPositionMode->setEnabled(false);
	}
	else
	{
		ui->lbSpeedOfPositionMode->setEnabled(true);
		ui->leSpeedOfPositionMode->setEnabled(true);
	}
}

void MainWindow::SetSpeedOfPositionMode()
{
	DeltaConnectionManager->ConveyorSend(QString("M313 ") + ui->leSpeedOfPositionMode->text());
}

void MainWindow::MoveConveyor()
{
	if (ui->cbConveyorValueType->currentIndex() == 0)
	{
		DeltaConnectionManager->ConveyorSend(QString("M311 ") + ui->leConveyorvMovingValue->text());
	}
	else
	{
		DeltaConnectionManager->ConveyorSend(QString("M312 ") + ui->leConveyorvMovingValue->text());		
	}
}

void MainWindow::ProcessShortcutKey()
{

}

void MainWindow::ConnectSliding()
{
	OpenConnectionDialog(DeltaConnectionManager->SlidingPort, DeltaConnectionManager->SlidingSocket, ui->pbSlidingConnect);
}

void MainWindow::GoHomeSliding()
{
	DeltaConnectionManager->SlidingSend("M320");
}

void MainWindow::DisableSliding()
{
	DeltaConnectionManager->SlidingSend("M323");
}

void MainWindow::SetSlidingSpeed()
{
	DeltaConnectionManager->SlidingSend(QString("M321 ") + ui->leSlidingSpeed->text());
}

void MainWindow::SetSlidingPosition()
{
	DeltaConnectionManager->SlidingSend(QString("M322 ") + ui->leSlidingPosition->text());
}

void MainWindow::ConnectExternalMCU()
{
	OpenConnectionDialog(DeltaConnectionManager->ExternalControllerPort, DeltaConnectionManager->ExternalControllerSocket, ui->pbExternalControllerConnect);
}

void MainWindow::TransmitTextToExternalMCU()
{
	DeltaConnectionManager->ExternalMCUSend(ui->leTransmitToMCU->text());
	ui->leTransmitToMCU->setText("");
}

void MainWindow::DisplayTextFromExternalMCU(QString text)
{
	ui->leReceiveFromMCU->setText(text);
}

void MainWindow::TerminalTransmit()
{
	DeltaConnectionManager->SendToRobot(ui->leTerminal->text());
	ui->leTerminal->setText("");
}

void MainWindow::PrintReceiveData(QString msg)
{
	//msg.replace("\n", "");
	Debug(ID, QString("Robot: ") + msg);
}

void MainWindow::NoticeConnected()
{
	Debug(DeltaConnectionManager->GetNamePort());

	ui->pbConnect->setText("Disconnect");
}

QString MainWindow::boldKey(QString key, QString htmlText)
{
	int keyOrder = htmlText.indexOf(key);

	if (keyOrder > -1)
	{
		htmlText = htmlText.replace(key, QString("<span style = \" font-weight:600;\">") + key + "</span>");
	}

	return htmlText;
}

QString MainWindow::boldPlusKey(QString key, QString plus, QString htmlText)
{
	int keyOrder = htmlText.indexOf(key);

	if (keyOrder > -1)
	{
		htmlText = htmlText.replace(key, QString("<span style = \" font-weight:600;") + plus + "\">" + key + "</span>");
	}

	return htmlText;
}

QString MainWindow::italyKey(QString key, QString htmlText)
{
	int keyOrder = htmlText.indexOf(key);

	if (keyOrder > -1)
	{
		htmlText = htmlText.replace(key, QString("<span style=\" font - style:italic; \">") + key + "</span>");
	}

	return htmlText;
}

QString MainWindow::replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText)
{
	int beginKey = -1;
	int endKey = 0;

	beginKey = htmlText.indexOf(start);

	while (beginKey > -1)
	{
		if (finish != "&&&")
		{
			endKey = htmlText.indexOf(finish, beginKey);
		}
		else
		{
			endKey = beginKey + 1;
			while (htmlText.at(endKey).isLetterOrNumber())
			{
				endKey++;
			}
		}

		QString cmtSentence = htmlText.mid(beginKey + offset, endKey - beginKey - offset);
		QString cmtSentenceAfter = beforeSection + cmtSentence + afterSection;
		if (cmtSentence.length() < maxlen)
			htmlText = htmlText.replace(beginKey + offset, endKey - beginKey - offset, cmtSentenceAfter);
		int panOrder = htmlText.indexOf("</p>", beginKey + cmtSentenceAfter.length());
		beginKey = htmlText.indexOf(start, panOrder);
	}
	return htmlText;
}

bool MainWindow::OpenConnectionDialog(QSerialPort * comPort, QTcpSocket* socket, QPushButton* connectButton)
{
	if (connectButton->text() == "Disconnect")
	{
		if (comPort->isOpen())
		{
			comPort->close();
		}
		if (socket->isOpen())
		{
			socket->close();
		}

		connectButton->setText("Connect");
		return false;
	}

	QStringList connectionItems;
	connectionItems.append("COM");
	connectionItems.append("WIFI");
	bool ok;

	QString connectionType = QInputDialog::getItem(this, tr("Connection"), tr("Type:"), connectionItems, 0, false, &ok);

	if (ok)
	{
		if (connectionType == "WIFI")
		{
			bool ok2;
			QString address = QInputDialog::getText(this, tr("ADDRESS"), tr("IP:PORT"), QLineEdit::Normal, "192.168.1.12:80", &ok2);

			if (address.indexOf(':') > -1)
			{
				QString ip = address.split(':').at(0);
				QString Port = address.split(':').at(1);
				socket->connectToHost(QHostAddress(ip), Port.toInt());

				if (socket->open((QIODevice::ReadWrite)) == true)
				{
					connectButton->setText("Disconnect");
					return true;
				}
			}
			
		}
		else if (connectionType == "COM")
		{
			QStringList items;

			Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
			{
				items << portInfo.portName();
			}

			bool ok;
			QString item = QInputDialog::getItem(this, tr("COM Connection"), tr("COM Ports:"), items, 0, false, &ok);
			if (ok && !item.isEmpty())
			{
				bool ok2;
				QString baudrate = QInputDialog::getText(this, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
				if (ok2 && !baudrate.isEmpty())
				{
					comPort->setPortName(item);
					comPort->setBaudRate(baudrate.toInt());

					if (comPort->open((QIODevice::ReadWrite)) == true)
					{
						//QMessageBox::information(this, "Noti", "Connected");

						connectButton->setText("Disconnect");

						return true;
					}
				}
			}
		}
	}

	return false;
}

void MainWindow::initTabs()
{
	ui->twDeltaManager->removeTab(1);

	ui->menuExecute->clear();

	delete ui->menuExecute;

	ui->menuEditor->addMenu(DeltaXMainWindows->at(0)->ui->menuExecute);

	for (int i = 1; i < DeltaXMainWindows->size(); i++)
	{
		QWidget *newDeltaTab = new QWidget();
		ui->twDeltaManager->addTab(newDeltaTab, QString());
		ui->twDeltaManager->setTabText(i, QString("Delta") + QString::number(i + 1));
	}

	QWidget *newDeltaTab = new QWidget();
	ui->twDeltaManager->addTab(newDeltaTab, QString());
	ui->twDeltaManager->setTabText(ui->twDeltaManager->indexOf(newDeltaTab), "+");
}

void MainWindow::hideExampleWidgets()
{
	ui->frExProgram->setVisible(false);
}

void MainWindow::interpolateCircle()
{
	float r = 120;
	int resolution = 120;
	float raMinAngle;
	int xO = 0;
	int yO = 0;
	int x;
	int y;
	float raAngle;
	QString gcode;

	raMinAngle = qDegreesToRadians(360.0f / resolution);

	for (int i = 0; i < resolution; i++)
	{
		raAngle = raMinAngle * i;
		x = xO + r * qCos(raAngle);
		y = yO + r * qSin(raAngle);
		gcode += QString("G01 X") + QString::number(x) + " Y" + QString::number(y) + "\n";
	}

	ui->pteGcodeArea->setPlainText(gcode);
}

void MainWindow::makeEffectExample()
{
	QCursor cursorTarget = QCursor(QPixmap("icon/Zoom In_16px.png"));
	ui->lbDrawingArea->setCursor(cursorTarget);
}
