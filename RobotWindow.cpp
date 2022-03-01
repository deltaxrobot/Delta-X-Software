#include "RobotWindow.h"
#include "ui_RobotWindow.h"

RobotWindow::RobotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RobotWindow)
{
    ui->setupUi(this);

//    InitVariables();
//    InitEvents();

    hideExampleWidgets();
}

RobotWindow::~RobotWindow()
{
    delete DeltaImageProcesser;
    lbLoadingPopup->thread()->quit();
    lbLoadingPopup->thread()->wait();
}

void RobotWindow::InitVariables()
{
    //---------- Connection -----------
    DeltaConnectionManager = new ConnectionManager();
    DeltaConnectionManager->SetBaudrate(DefaultBaudrate);

    COMEncoder = new COMDevice();
    COMEncoder->DefaultBaudrate = DefaultBaudrate;
    connect(COMEncoder, SIGNAL(FinishedReadLine(QString)), this, SLOT(ReceiveEncoderResponse(QString)));
    ElapsedTimeEncoder.start();

    Encoder1 = new Encoder();
    Encoder2 = new Encoder();

    //--------- Init Dialog -------------
    CloseDialog = new SmartDialog(this);
    CloseDialog->SetType(CloseDialog->CLOSE_DIALOG);

    //--------- Init Plugin ----------
    LoadPlugin();

    // ---- Init UI ----
    ui->lbBaudrate->setText(QString::number(DeltaConnectionManager->GetBaudrate()));
    ui->lbIP->setText(TCPConnectionManager::GetIP());
    ui->lbLocalPort->setText(QString::number(DeltaConnectionManager->TCPConnection->Port));
    ui->mbRobot->setVisible(false);

    QDir directory(QDir::currentPath());
    ui->cbSetting->clear();
    QStringList iniFiles = directory.entryList(QStringList() << "*.ini" << "*.INI",QDir::Files);
    foreach(QString filename, iniFiles)
    {
        ui->cbSetting->addItem(filename);
    }

    InitParseNames();



    //---- Init pointer --------
    initInputValueLabels();

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        //------Joystick-----
        joystick = QJoysticks::getInstance();
        joystick->setVirtualJoystickRange(ui->leJoystickRange->text().toDouble());
        joystick->setVirtualJoystickAxisSensibility(ui->leJoystickSensibility->text().toDouble());
        ui->cbJoystickDevice->addItems(joystick->deviceNames());
    #endif
#endif

    //----- Gcode Programing----------

    DeltaGcodeManager = new GcodeProgramManager(this, ui->saProgramFiles, ui->wgProgramContainer, ui->pteGcodeArea, ui->pbExecuteGcodes, DeltaConnectionManager, Delta2DVisualizer);



    DeltaGcodeManager->leGcodeProgramPath = ui->leGcodeProgramPath;

    DeltaGcodeManager->LoadPrograms();

    // ------- Log and Debug -----
    Debugs.push_back(ui->teDebug);

    //-------- 2D controler ------------

    Delta2DVisualizer = new DeltaVisualizer(ui->wg2D);
    Delta2DVisualizer->setObjectName(QStringLiteral("2DArea"));
    Delta2DVisualizer->setGeometry(QRect(0, 0, 300, 300));
    Delta2DVisualizer->SetDivisionComboBox(ui->cbDivision);

    DeltaDrawingExporter = new DrawingExporter(this);
    DeltaDrawingExporter->SetDrawingParameterPointer(ui->lbImageForDrawing, ui->lbImageWidth, ui->lbImageHeight, ui->leHeightScale, ui->leWidthScale, ui->leSpace, ui->leDrawingThreshold, ui->hsDrawingThreshold, ui->cbReverseDrawing, ui->cbDrawMethod, ui->cbConversionTool);
    DeltaDrawingExporter->SetDrawingAreaWidget(ui->lbDrawingArea);
    DeltaDrawingExporter->SetGcodeEditor(ui->pteGcodeArea);
    DeltaDrawingExporter->SetEffector(ui->cbDrawingEffector);
    DeltaDrawingExporter->SetGcodeExportParameterPointer(ui->leSafeZHeight, ui->leTravelSpeed, ui->leDrawingSpeed, ui->leDrawingAcceleration);

    //--------------Timer-------------

    VirtualEncoderTimer = new QTimer(this);
    connect(VirtualEncoderTimer, SIGNAL(timeout()), this, SLOT(VirtualEncoder()));
    VirtualEncoderTimer->start(100);

    UIEvent = new QTimer(this);
    connect(UIEvent, SIGNAL(timeout()), this, SLOT(ProcessUIEvent()));
    UIEvent->start(100);

    ConvenyorTimer = new QTimer(this);
    connect(ConvenyorTimer, SIGNAL(timeout()), this, SLOT(GetConvenyorPosition()));

    ShortcutKeyTimer = new QTimer(this);
    connect(ShortcutKeyTimer, SIGNAL(timeout()), this, SLOT(ProcessShortcutKey()));
    ShortcutKeyTimer->start(100);

    //------------ Loading Popup ------------
    lbLoadingPopup = new QLabel();
    mvLoadingPopup = new QMovie(":/icon/deltax-loading.gif");

    lbLoadingPopup->setMovie(mvLoadingPopup);
    lbLoadingPopup->setMinimumHeight(120);
    lbLoadingPopup->setMinimumWidth(200);
    lbLoadingPopup->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    lbLoadingPopup->setStyleSheet("border: 1px solid black;");
//    lbLoadingPopup->moveToThread(new QThread(this));
    //connect(lbLoadingPopup->thread(), SIGNAL(finished()), lbLoadingPopup, SLOT(deleteLater()));
//    connect(lbLoadingPopup->thread(), SIGNAL(started()), lbLoadingPopup, SLOT(show()));
//    connect(lbLoadingPopup->thread(), SIGNAL(started()), mvLoadingPopup, SLOT(start()));
//    connect(lbLoadingPopup->thread(), SIGNAL(quit()), lbLoadingPopup, SLOT(hide()));
//    connect(lbLoadingPopup->thread(), SIGNAL(quit()), mvLoadingPopup, SLOT(stop()));

    //---------- Object Detector Init -------------

    DeltaImageProcesser = new ObjectDetector(this);
    DeltaImageProcesser->SetResultScreenPointer(ui->cameraWidget);
    DeltaImageProcesser->SetObjectScreenPointer(ui->lbTrackingObject);
    DeltaImageProcesser->SetCameraInfoWidget(ui->leFPS, ui->lbCameraState, ui->pbPlayPauseCamera, ui->pbLoadCamera);
    DeltaImageProcesser->SetObjectSizePointer(ui->leWRec, ui->leLRec, ui->leHRec);
    DeltaImageProcesser->SetObjectErrorPointer(ui->leObjectErrorSize, ui->leTrackingError);
    DeltaImageProcesser->SetCalibLinePointer(ui->leRealDistance, ui->leImageDistance);
    DeltaImageProcesser->SetScaleRoateEnablePointer(ui->cbScaleRotateTool);
    DeltaImageProcesser->SetRealityCalibPointPointer(ui->leRealityPoint1X, ui->leRealityPoint1Y, ui->leRealityPoint2X, ui->leRealityPoint2Y);
    DeltaImageProcesser->SetImageCalibPointPointer(ui->leImagePoint1X, ui->leImagePoint1Y, ui->leImagePoint2X, ui->leImagePoint2Y);
    DeltaImageProcesser->SetTrackingWidgetPointer(ui->lbTrackingObjectNumber, ui->lbVisibleObjectNumber);
    DeltaImageProcesser->CameraScrollArea = ui->saCamera;
    DeltaImageProcesser->SetResolutionWidget(ui->leCameraWidth, ui->leCameraHeight);
    DeltaImageProcesser->SetDisplayInfoWidget(ui->lbDisplayRatio, ui->lbMatSize);
    DeltaImageProcesser->SetXAngleWidget(ui->leXAxisAngle);
    DeltaImageProcesser->SetObjectFilterWidget(ui->rbBlobFilter, ui->rbExternalFilter, ui->rbCircleFilter);
    DeltaImageProcesser->SetFilterParaWidget(ui->lePythonUrl);
    DeltaImageProcesser->cbExternalCamera = ui->cbExternalImageSource;
    DeltaImageProcesser->cbImageSourceForExternal = ui->cbImageSource;
    DeltaImageProcesser->Encoder1 = Encoder1;


    leChessPoints[0][0] = ui->leCorner1X;
    leChessPoints[0][1] = ui->leCorner1Y;
    leChessPoints[1][0] = ui->leCorner2X;
    leChessPoints[1][1] = ui->leCorner2Y;
    leChessPoints[2][0] = ui->leCorner3X;
    leChessPoints[2][1] = ui->leCorner3Y;
    leChessPoints[3][0] = ui->leCorner4X;
    leChessPoints[3][1] = ui->leCorner4Y;

    DeltaImageProcesser->SetChessboardWidget(ui->leChessWidth, ui->leChessHeight, ui->leChessRealSize, leChessPoints);



    TrackingObjectTable = new ObjectVariableTable(this);

    ui->gbCameraCalibration->setChecked(false);
    ui->gbCameraObject->setChecked(false);
    ui->gbCameraVariable->setChecked(false);
    ui->gbConveyorForTracking->setChecked(false);

    //----------------ROS-------------------
#ifdef Q_OS_WIN
//    DeltaXROS = new ROS(this, ui->frameROS, "/ros/Delta X Ros.exe");
//	DeltaXROS->SetConnectionManager(DeltaConnectionManager->TCPConnection);
    //DeltaXROS->Run();
#endif
    //---------------Socket------------------------


    //---------------------- Update ----------------------

//    HttpManager = new QNetworkAccessManager(this);
//    connect(HttpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(FinishedRequest(QNetworkReply*)));

//    QNetworkRequest request = QNetworkRequest(QUrl("http://imwi.space/admin/login.php"));
//    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
//    QUrlQuery params;
//    params.addQueryItem("user", "trungdoanhong");
//    params.addQueryItem("pass", "doanhongtrung");
//    HttpManager->post(request, params.query().toUtf8());

    //------------ UI ----------------
    Delta2DVisualizer->ChangeXY(0, 0);

    ui->twDeltaGeometry->setTabVisible(0, false);
    ui->twModule->setTabVisible(2, false);
    ui->gbRelay->setVisible(false);
    ui->gbGripper->setVisible(false);

    SelectImageProviderOption(0);

    //------------------- Linux -----------------
//    QString cmd = "stty -F /dev/ttyACM0 -hupcl";
//    QProcess *process = new QProcess;
//    process->start(cmd);
//    process->waitForBytesWritten();
//    process->waitForFinished();

    //------------ Robot --------

    //----- Process ------
    ExternalScriptProcess = new QProcess(this);
}

void RobotWindow::InitEvents()
{
    // -------- Debug Log --------
//    connect(ui->tbExpandLogBox, &QToolButton::toggled, this, &RobotWindow::ExpandLogBox);


    // ------------- --------------
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
    //connect(ui->cbPositionToExecuteGcode, SIGNAL(currentIndexChanged(const QString &)), DeltaGcodeManager, SLOT(SetStartingGcodeEditorCursor(QString)));

    // ------------ Jogging -----------
	connect(ui->pbHome, SIGNAL(clicked(bool)), this, SLOT(Home()));
	connect(ui->pbW, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->pbZ, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->pbY, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->pbX, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->pbU, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->pbV, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leW, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leZ, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leY, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
	connect(ui->leX, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leU, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leV, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));

    connect(ui->pbUp, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveUp()));
    connect(ui->pbDown, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveDown()));
    connect(ui->pbForward, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveForward()));
    connect(ui->pbBackward, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveBackward()));
    connect(ui->pbLeft, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveLeft()));
    connect(ui->pbRight, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveRight()));
    connect(ui->leVelocity, SIGNAL(returnPressed()), this, SLOT(UpdateVelocity()));
    connect(ui->leAccel, SIGNAL(returnPressed()), this, SLOT(UpdateAccel()));
    connect(ui->leStartSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateStartSpeed()));
    connect(ui->leEndSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateEndSpeed()));

    connect(ui->pbsubX, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveLeft()));
    connect(ui->pbsubY, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveBackward()));
    connect(ui->pbsubZ, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveDown()));
    connect(ui->pbsubW, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(SubW()));
    connect(ui->pbsubU, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(SubU()));
    connect(ui->pbsubV, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(SubV()));

    connect(ui->pbplusX, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveRight()));
    connect(ui->pbplusY, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveForward()));
    connect(ui->pbplusZ, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveUp()));
    connect(ui->pbplusW, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(PlusW()));
    connect(ui->pbplusU, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(PlusU()));
    connect(ui->pbplusV, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(PlusV()));

    //---------- End effector -----------
	connect(ui->hsGripperAngle, SIGNAL(valueChanged(int)), this, SLOT(AdjustGripperAngle(int)));
	connect(ui->pbGrip, SIGNAL(clicked(bool)), this, SLOT(Grip()));
	connect(ui->pbPump, SIGNAL(clicked(bool)), this, SLOT(SetPump(bool)));
	connect(ui->pbLaser, SIGNAL(clicked(bool)), this, SLOT(SetLaser(bool)));

    //----- Delta X S IO -----
    connect(ui->cbD0, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD1, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD2, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD3, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD4, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD5, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD6, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD7, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD8, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD9, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD10, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD11, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD12, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD13, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD14, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbD15, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));

    connect(ui->cbDx, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbRx, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));

    connect(ui->leP0Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
    connect(ui->leP1Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
    connect(ui->lePxValue, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));

    connect(ui->leS0Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
    connect(ui->leS1Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
    connect(ui->leSxValue, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));

    connect(ui->pbReadI0, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI1, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI2, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI3, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI4, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI5, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadIx, SIGNAL(clicked()), this, SLOT(RequestValueInput()));

    connect(ui->pbReadA0, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadA1, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadAx, SIGNAL(clicked()), this, SLOT(RequestValueInput()));

    connect(DeltaConnectionManager, SIGNAL(ReceiveInputIO(QString)), this, SLOT(GetValueInput(QString)));

    //---------- External Devices ------------
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

    //------------- 2D control ----------------
	connect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZLineEditValue(int)));
	connect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->vsAngleAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateAngleLineEditValue(int)));
	connect(ui->vsAngleAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->vs5AxisAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateAngleLineEditValue(int)));
    connect(ui->vs5AxisAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->vs6AxisAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateAngleLineEditValue(int)));
    connect(ui->vs6AxisAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(Delta2DVisualizer, SIGNAL(Moved(float, float, float, float, float, float)), this, SLOT(UpdateTextboxFrom2DControl(float, float, float, float, float, float)));


	connect(Delta2DVisualizer, SIGNAL(FinishMoving()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    //connect(Delta2DVisualizer, SIGNAL(CursorMoved(float, float)), SLOT(UpdateCursorPosition(float, float)));
    connect(ui->cbWorkingSize, SIGNAL(currentIndexChanged(int)), Delta2DVisualizer, SLOT(ChangeWorkingSize(int)));
	
    //------------- 3D control -------------------
	connect(ui->pbTurnOnROS, SIGNAL(clicked(bool)), this, SLOT(OpenROS()));
	connect(ui->cbROSCameraView, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeROSCameraView(int))); 
	connect(ui->cbEndEffector, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeEndEffector(int)));
	connect(ui->cbRobotVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRobotVersion(int)));
	connect(ui->btDeleteAllObjects, SIGNAL(clicked(bool)), this, SLOT(DeleteAllObjectsInROS()));
	connect(ui->pbClearDetectObjects, SIGNAL(clicked(bool)), this, SLOT(DeleteAllObjectsInROS()));

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        //------------- Joystick -----------
        connect(joystick, SIGNAL(buttonEvent (const QJoystickButtonEvent&)), SLOT(ProcessJoystickButton(const QJoystickButtonEvent&)));
        connect(joystick, SIGNAL(axisEvent(const QJoystickAxisEvent&)), SLOT(ProcessJoystickAxis(const QJoystickAxisEvent&)));
        connect(joystick, SIGNAL(POVEvent(const QJoystickPOVEvent&)), SLOT(ProcessJoystickPOV(const QJoystickPOVEvent&)));
    #endif
#endif
    //------------- Terminal ---------------
	connect(ui->leTerminal, SIGNAL(returnPressed()), this, SLOT(TerminalTransmit()));

    //------------- Connection --------------
	connect(DeltaConnectionManager, SIGNAL(FinishReadLine(QString)), this, SLOT(PrintReceiveData(QString)));
	connect(DeltaConnectionManager, SIGNAL(DeltaResponeReady()), this, SLOT(NoticeConnected()));
    connect(DeltaConnectionManager, SIGNAL(InHomePosition(float, float, float, float, float, float)), this, SLOT(UpdateGlobalHomePositionValueAndControlValue(float, float, float, float, float, float)));
    connect(DeltaConnectionManager, SIGNAL(ReceiveVariableChangeCommand(QString, QString)), DeltaGcodeManager, SLOT(UpdateSystemVariable(QString, QString)));
	connect(DeltaConnectionManager, SIGNAL(RequestVariableValue(QIODevice*, QString)), DeltaGcodeManager, SLOT(RespondVariableValue(QIODevice*, QString)));
	connect(DeltaConnectionManager, SIGNAL(ReceiveRequestsFromExternal(QString)), this, SLOT(ExecuteRequestsFromExternal(QString)));

    connect(DeltaConnectionManager, SIGNAL(ReceiveCaptureSignalFromExternalAI()), Encoder1, SLOT(MarkPosition()));
    connect(DeltaConnectionManager, SIGNAL(ReceiveObjectInfoFromExternalAI(QString)), this, SLOT(ProcessDetectedObjectFromExternalAI(QString)));
    connect(DeltaConnectionManager, SIGNAL(ExternalScriptOpened(QTcpSocket*)), DeltaImageProcesser, SLOT(GetExternalScriptSocket(QTcpSocket*)));
    connect(DeltaConnectionManager, SIGNAL(ReceiveDisplayObjectFromExternalScript(QString)), this, SLOT(AddDisplayObjectFromExternalScript(QString)));


    //------------- Gcode Editor -------------
	connect(ui->pbFormat, SIGNAL(clicked(bool)), this, SLOT(StandardFormatEditor()));
    connect(ui->cbLockGcodeEditor, SIGNAL(clicked(bool)), ui->pteGcodeArea, SLOT(setLockState(bool)));
    connect(ui->pbOpenGcodeProgramPath, SIGNAL(clicked(bool)), DeltaGcodeManager, SLOT(SelectGcodeProgramPath()));


    //------------ Image Processing -----------
	connect(ui->pbFilter, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenParameterPanel()));
    connect(ui->pbFilterTool, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenParameterPanel()));
	connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadTestImage()));
    connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadCamera2()));
    connect(ui->pbObjectRect, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectObjectTool()));
    connect(ui->pbGetSizeTool, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectObjectTool()));
    connect(ui->pbObjectLine, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectLineTool()));
    connect(ui->pbCalibLineTool, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectLineTool()));
    connect(ui->pbObjectOrigin, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectPointTool()));
    connect(ui->pbCalibPointTool, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectPointTool()));
	connect(ui->lbCameraLayer, SIGNAL(currentIndexChanged(int)), DeltaImageProcesser, SLOT(SelectLayer(int )));
    connect(ui->pbRotateAxis90, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(changeAxisDirection()));
    connect(ui->pbDirectionTool, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(changeAxisDirection()));
	connect(ui->leFPS, SIGNAL(returnPressed()), DeltaImageProcesser, SLOT(SaveFPS()));
	connect(ui->pbClearDetectObjects, SIGNAL(clicked(bool)), DeltaImageProcesser->ObjectManager, SLOT(RemoveAllDetectObjects()));
	connect(ui->pbViewDataObjects, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
    connect(ui->pbClearObject, SIGNAL(clicked(bool)), DeltaImageProcesser->ObjectManager, SLOT(RemoveAllDetectObjects()));
    connect(ui->pbOpenObjectTable, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));

    connect(DeltaImageProcesser, SIGNAL(ObjectValueChanged(std::vector<cv::RotatedRect>)), TrackingObjectTable, SLOT(UpdateTable(std::vector<cv::RotatedRect>)));
	connect(DeltaImageProcesser, SIGNAL(ObjectValueChanged(std::vector<cv::RotatedRect>)), this, SLOT(AddObjectsToROS(std::vector<cv::RotatedRect>)));
	connect(ui->pbTransformPerspective, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnTransformPerspective(bool)));
    connect(ui->pbWarpTool, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnTransformPerspective(bool)));
	connect(ui->cbDisplayCalibInfo, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnCalibDisplay(bool)));
//	connect(ui->pbExpandCameraWidget, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(ExpandCameraWidget(bool)));
    connect(ui->pbCameraWindowMode, SIGNAL(clicked(bool)), this, SLOT(OpenCameraWindow()));
    connect(ui->cameraWidget, SIGNAL(SizeChanged()), DeltaImageProcesser, SLOT(UpdateRatios()));

    connect(ui->pbFindChessboard, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(FindChessboard()));

    connect(ui->leTrackingError, &QLineEdit::returnPressed, DeltaImageProcesser->ObjectManager, &BlobManager::UpdateTrackingError);
    connect(ui->leObjectErrorSize, &QLineEdit::returnPressed, DeltaImageProcesser, &ObjectDetector::GetObjectError);

    connect(ui->pbConnectEncdoer, SIGNAL(clicked(bool)), this, SLOT(ConnectEncoder()));
    connect(ui->pbCalibConveyorAngle, SIGNAL(clicked(bool)), this, SLOT(CalculateConveyorDeviationAngle()));
	connect(ui->leConvenyorSpeed, SIGNAL(returnPressed()), this, SLOT(SetConvenyorSpeed()));
    connect(ui->cbConveyorDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConvenyorSpeed()));
    connect(ui->pbResetEncoderPosition, SIGNAL(clicked(bool)), this, SLOT(ResetEncoderPosition()));

    connect(ui->leMovingDistanceConveyorControl, SIGNAL(returnPressed()), this, SLOT(MoveExternalConveyor()));
    connect(ui->pbForwardConveyor, SIGNAL(clicked(bool)), this, SLOT(ForwardExternalConveyor()));
    connect(ui->pbBackwardConveyor, SIGNAL(clicked(bool)), this, SLOT(BackwardExternalConveyor()));
    connect(ui->pbTurnOffConveyor, SIGNAL(clicked(bool)), this, SLOT(TurnOffExternalConveyor()));

    connect(ui->pbImageMapping, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(CalculateMappingMatrix()));
    connect(ui->pbMapping, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(CalculateMappingMatrix()));
    connect(ui->pbPointToolOnBar, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectMappingTool()));
    connect(ui->pbExternalScriptOpen, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenExternalFilterScript()));
    connect(ui->pbRunExternalScript, SIGNAL(clicked(bool)), this, SLOT(RunExternalScript()));

    connect(ui->cbExternalImageSource, SIGNAL(toggled(bool)), this, SLOT(UseCameraFromPlugin(bool)));

    connect(ui->cbSourceForImageProvider, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectImageProviderOption(int)));

    // ---- Setting ----
    connect(ui->pbLoadCameraSetting, SIGNAL(clicked(bool)), this, SLOT(LoadSetting()));
    connect(ui->pbSaveCameraSetting, SIGNAL(clicked(bool)), this, SLOT(SaveSetting()));

    //----------- Camera -----------
    connect(ui->cameraWidget, SIGNAL(ObjectChanged(int, int, int, int)), DeltaImageProcesser, SLOT(GetObjectInfo(int, int, int, int)));
    connect(ui->cameraWidget, SIGNAL(DistanceChanged(int)), DeltaImageProcesser, SLOT(GetDistance(int)));
    connect(ui->cameraWidget, SIGNAL(QuadrangleChanged(QPoint, QPoint, QPoint, QPoint)), DeltaImageProcesser, SLOT(GetPerspectivePoints(QPoint, QPoint, QPoint, QPoint)));
    connect(ui->cameraWidget, SIGNAL(AreaChanged(QRect)), DeltaImageProcesser, SLOT(GetProcessArea(QRect)));
    connect(ui->cameraWidget, SIGNAL(LineChanged(QPoint, QPoint)), DeltaImageProcesser, SLOT(GetCalibLine(QPoint, QPoint)));
    connect(ui->cameraWidget, SIGNAL(PointChanged(QPoint, QPoint)), DeltaImageProcesser, SLOT(GetCalibPoint(QPoint, QPoint)));
    connect(ui->cameraWidget, SIGNAL(MappingPointChanged(QPoint)), DeltaImageProcesser, SLOT(GetMappingPoint(QPoint)));

	
//    connect(ui->leRealityPoint1X, SIGNAL(returnPressed()), ui->lbScreenStreamer, SLOT(ChangePoint()));
//    connect(ui->leRealityPoint1Y, SIGNAL(returnPressed()), ui->lbScreenStreamer, SLOT(ChangePoint()));
    connect(ui->leRealDistance, SIGNAL(returnPressed()), ui->cameraWidget, SLOT(ChangeLine()));
	connect(ui->leWRec, SIGNAL(returnPressed()), this, SLOT(UpdateDetectObjectSize()));
    connect(ui->leLRec, SIGNAL(returnPressed()), this, SLOT(UpdateDetectObjectSize()));

    connect(ui->cbCameraWidgetHeight, SIGNAL(currentIndexChanged(QString)), DeltaImageProcesser, SLOT(ChangeCameraWidgetHeight(QString)));

    connect(ui->cameraWidget, SIGNAL(RequestUpdate()), DeltaImageProcesser, SLOT(UpdateToCameraWidget()));

    //---------- Menu -----------
	connect(ui->actionBaudrate, SIGNAL(triggered()), this, SLOT(ConfigConnection()));
	connect(ui->actionGcode, SIGNAL(triggered()), this, SLOT(OpenGcodeReference()));
	connect(ui->actionExecute_All, SIGNAL(triggered()), this, SLOT(ExecuteSelectPrograms()));
	connect(ui->actionExecute, SIGNAL(triggered()), this, SLOT(ExecuteProgram()));
    connect(ui->actionScale, SIGNAL(triggered(bool)), this, SLOT(ScaleUI()));

	connect(DeltaGcodeManager, SIGNAL(OutOfObjectVariable()), DeltaImageProcesser->ObjectManager, SLOT(RemoveOldestObject()));
    connect(DeltaGcodeManager, SIGNAL(MoveToNewPosition(float, float, float, float, float, float, float, float, float, float)), this, SLOT(UpdatePositionControl(float, float, float, float, float, float, float, float, float, float)));
	connect(DeltaGcodeManager, SIGNAL(DeleteAllObjects()), ui->pbClearDetectObjects, SLOT(click()));
	connect(DeltaGcodeManager, SIGNAL(DeleteObject1()), DeltaImageProcesser->ObjectManager, SLOT(RemoveOldestObject()));
	connect(DeltaGcodeManager, SIGNAL(PauseCamera()), DeltaImageProcesser, SLOT(PauseCamera()));
	connect(DeltaGcodeManager, SIGNAL(CaptureCamera()), DeltaImageProcesser, SLOT(CaptureCamera()));
	connect(DeltaGcodeManager, SIGNAL(ResumeCamera()), DeltaImageProcesser, SLOT(ResumeCamera()));

	connect(ui->pbPlayPauseCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(PlayCamera(bool)));
	connect(ui->pbCaptureCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(CaptureCamera()));

    connect(DeltaImageProcesser->ObjectManager, SIGNAL(NewUpdateObjectPosition(QString)), DeltaGcodeManager, SLOT(SaveGcodeVariable(QString)));

    //----------- Drawing -----------
	connect(ui->pbOpenPicture, SIGNAL(clicked(bool)), DeltaDrawingExporter, SLOT(OpenImage()));
	connect(ui->pbPainting, SIGNAL(clicked(bool)), DeltaDrawingExporter, SLOT(ConvertToDrawingArea()));

	connect(ui->pbDrawLine, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectLineTool()));
	connect(ui->pbDrawRectangle, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectRectangleTool()));
	connect(ui->pbDrawCircle, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectCircleTool()));
	connect(ui->pbDrawArc, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectArcTool()));
	connect(ui->pbZoomIn, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectZoomInTool()));
	connect(ui->pbZoomOut, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectZoomOutTool()));
	connect(ui->pbCursor, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(SelectCursor()));

    connect(ui->pbExportDrawingGcodes, SIGNAL(clicked(bool)), DeltaDrawingExporter, SLOT(ExportGcodes()));

	connect(ui->twDeltaManager, SIGNAL(tabBarClicked(int)), this, SLOT(ChangeDeltaDashboard(int)));
	connect(ui->twDeltaManager, SIGNAL(currentChanged(int)), this, SLOT(SelectTrueTabName(int)));

    connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceivePosition(float, float, float, float, float, float)), this, SLOT(UpdateTextboxFrom3DControl(float, float, float, float, float, float)));
	connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceiveVariableChangeCommand(QString, float)), DeltaGcodeManager, SLOT(UpdateSystemVariable(QString, float)));
	connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceiveOk()), this, SLOT(ROSResponse()));

    //------------ Loading ------------
    connect(DeltaConnectionManager, SIGNAL(FinishFindingRobot()), this, SLOT(CloseLoadingPopup()));

}

void RobotWindow::DisablePositionUpdatingEvents()
{
    disconnect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZLineEditValue(int)));
    disconnect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    disconnect(ui->leW, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    disconnect(ui->leZ, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    disconnect(ui->leY, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    disconnect(ui->leX, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    disconnect(ui->leU, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    disconnect(ui->leV, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));

    disconnect(ui->leVelocity, SIGNAL(returnPressed()), this, SLOT(UpdateVelocity()));
    disconnect(ui->leAccel, SIGNAL(returnPressed()), this, SLOT(UpdateAccel()));
    disconnect(ui->leStartSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateStartSpeed()));
    disconnect(ui->leEndSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateEndSpeed()));
}

void RobotWindow::EnablePositionUpdatingEvents()
{
    connect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZLineEditValue(int)));
    connect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leW, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leZ, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leY, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leX, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leU, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
    connect(ui->leV, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));

    connect(ui->leVelocity, SIGNAL(returnPressed()), this, SLOT(UpdateVelocity()));
    connect(ui->leAccel, SIGNAL(returnPressed()), this, SLOT(UpdateAccel()));
    connect(ui->leStartSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateStartSpeed()));
    connect(ui->leEndSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateEndSpeed()));
}


void RobotWindow::FinishedRequest(QNetworkReply *reply)
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
            reply = QMessageBox::question(this, "There is a new version of Delta X Software", "Do you want to update?",
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

void RobotWindow::ExportBlocklyToGcode()
{
	/*QWebEnginePage* clone = new QWebEnginePage();
	
	ui->wevBlockly->page()->runJavaScript("document.getElementsByTagName(\"body\")[0].innerHTML = document.getElementById(\"content_javascript\").innerText");

	ui->wevBlockly->page()->toPlainText([this](const QString &result)
	{
		ui->pteGcodeArea->setText(result);
	});*/
}

void RobotWindow::OpenROS()
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


void RobotWindow::ChangeROSCameraView(int index)
{
	DeltaConnectionManager->TCPConnection->SendMessageToROS(QString("update camera_position ") + QString::number(index));
}

void RobotWindow::ChangeEndEffector(int index)
{
	DeltaConnectionManager->TCPConnection->SendMessageToROS(QString("update end_effector ") + QString::number(index));
}

void RobotWindow::ChangeRobotVersion(int index)
{
	DeltaConnectionManager->TCPConnection->SendMessageToROS(QString("update robot ") + QString::number(index));
}

void RobotWindow::ScaleUI()
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

void RobotWindow::ExecuteRequestsFromExternal(QString request)
{
	request = request.replace("\n", "");
	request = request.replace("\r", "");

	if (request == "Execute All")
	{
		ExecuteSelectPrograms();
	}
}

void RobotWindow::ChangeParentForWidget(bool state)
{
	
}

void RobotWindow::closeEvent(QCloseEvent * event)
{
    bool result = CloseDialog->PopUp("Close software", "Do you want to close the software?");

    if(result == false)
    {
        event->ignore();
    }
    else
    {        
        qApp->exit();
        event->accept();
    }
}

bool RobotWindow::Run()
{
    if (!DeltaConnectionManager->RobotPort->isOpen())
    {
        if (DeltaConnectionManager->RobotPort->open(QIODevice::ReadWrite))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool RobotWindow::Stop()
{
    if (DeltaConnectionManager->RobotPort->isOpen())
    {
        DeltaConnectionManager->RobotPort->close();
    }

    return true;
}

void RobotWindow::LoadPlugin()
{
    pluginList = new QList<DeltaXPlugin*>();

    QDir dir(QApplication::applicationDirPath());
    dir.cd("plugin");

    QStringList plugins = getPlugins(dir.path());

    initPlugins(plugins);
}

void RobotWindow::InitParseNames()
{
    ParseNames.insert("CameraWindow", "cameraWidget");
}

void RobotWindow::LoadSettings(QSettings *setting)
{
    LoadGeneralSettings(setting);
    LoadJoggingSettings(setting);
    Load2DSettings(setting);
    Load3DSettings(setting);
    LoadExternalDeviceSettings(setting);
    LoadTerminalSettings(setting);
    LoadGcodeEditorSettings(setting);
    LoadObjectDetectorSetting(setting);
    LoadDrawingSetting(setting);
    LoadPluginSetting(setting);
}

void RobotWindow::LoadGeneralSettings(QSettings *setting)
{
    QString comName = setting->value("ComName", "None").toString();
    int defaultBaudrate = setting->value("DefaultBaudrate", 115200).toInt();
    QString ip = setting->value("IP").toString();
    int port = setting->value("TCPPort").toInt();
    bool state = setting->value("RobotState", false).toBool();

    DeltaConnectionManager->RobotPort->setPortName(comName);
    DeltaConnectionManager->RobotPort->setBaudRate(defaultBaudrate);
    DeltaConnectionManager->TCPConnection->ServerName = ip;
    DeltaConnectionManager->TCPConnection->Port = port;

    if (state == true)
    {
        if (DeltaConnectionManager->RobotPort->open((QIODevice::ReadWrite)) == true)
        {
            connect(DeltaConnectionManager->RobotPort, SIGNAL(readyRead()), DeltaConnectionManager, SLOT(ReadData()));
            ui->pbConnect->setText("Disconnect");
        }
    }

    ui->lbComName->setText(comName);
    ui->lbBaudrate->setText(QString::number(defaultBaudrate));
    ui->cbRobotModel->setCurrentText(setting->value("RobotModel").toString());

    DeltaConnectionManager->RobotPort->setBaudRate(ui->lbBaudrate->text().toInt());
    DeltaConnectionManager->RobotPort->setPortName(ui->lbComName->text());
    DeltaConnectionManager->TCPConnection->ServerName = ui->lbComName->text();
    DeltaConnectionManager->TCPConnection->Port = ui->lbLocalPort->text().toInt();

    Name = setting->value("Name").toString();

    // ---- Tracking ----
    ui->rbEncoderEnable->setChecked(setting->value("EncoderEnable").toBool());
    ui->cbEncoderPositionInverse->setText(setting->value("InverseEncoderEnable", ui->cbEncoderPositionInverse->text()).toString());
    ui->leConvenyorSpeed->setText(setting->value("ConstantConveyorSpeed", ui->leConvenyorSpeed->text()).toString());
    ui->cbConveyorDirection->setCurrentText(setting->value("ConveyorDirection", ui->cbConveyorDirection->currentText()).toString());
    ui->leConveyorDeviationAngle->setText(setting->value("ConveyorDeviationAngle", ui->leConveyorDeviationAngle->text()).toString());
    ui->leForwardConveyorGcode->setText(setting->value("ForwardConveyorGcode", ui->leForwardConveyorGcode->text()).toString());
    ui->leBackwardConveyorGcode->setText(setting->value("BackwardConveyorGcode", ui->leBackwardConveyorGcode->text()).toString());
    ui->leTurnOffConveyorGcode->setText(setting->value("TurnOffConveyorGcode", ui->leTurnOffConveyorGcode->text()).toString());

    ui->leConvenyorSpeed->returnPressed();
}

void RobotWindow::LoadJoggingSettings(QSettings *setting)
{

}

void RobotWindow::Load2DSettings(QSettings *setting)
{

}

void RobotWindow::Load3DSettings(QSettings *setting)
{

}

void RobotWindow::LoadExternalDeviceSettings(QSettings *setting)
{
    setting->beginGroup("ExternalDevice");

    //---- Conveyor -----
    setting->beginGroup("Conveyor");

    bool connectionState = setting->value("State", false).toBool();
    QString comPort = setting->value("ComPort", "COM1").toString();
    int baudrate = setting->value("Baudrate", 115200).toInt();

    ui->cbConveyorMode->setCurrentText(setting->value("ControlMode").toString());
    ui->cbConveyorValueType->setCurrentText(setting->value("MovingMode").toString());
    ui->leConveyorvMovingValue->setText(setting->value("MovingValue").toString());

    DeltaConnectionManager->ConveyorPort->setPortName(comPort);
    DeltaConnectionManager->ConveyorPort->setBaudRate(baudrate);

    if (connectionState == true)
    {
        if (DeltaConnectionManager->ConveyorPort->open(QIODevice::ReadWrite) == true)
        {
            ui->pbConveyorConnect->setText("Disconnect");
            ui->lbConveyorCOMName->setText(comPort);
        }
    }

    setting->endGroup();

    //---- Encoder -----

    setting->beginGroup("Encoder");

    connectionState = setting->value("State", false).toBool();
    comPort = setting->value("ComPort", "COM1").toString();
    baudrate = setting->value("Baudrate", 115200).toInt();

    COMEncoder->COMPort->setPortName(comPort);
    COMEncoder->COMPort->setBaudRate(baudrate);

    if (connectionState == true)
    {
        if (COMEncoder->COMPort->open((QIODevice::ReadWrite)) == true)
        {
            ui->pbConnectEncdoer->setText("Disconnect");
            ui->leEncoderCom->setText(comPort);
        }
    }

    setting->endGroup();

    //---- Slider -----

    setting->beginGroup("Slider");

    connectionState = setting->value("State", false).toBool();
    comPort = setting->value("ComPort", "COM1").toString();
    baudrate = setting->value("Baudrate", 115200).toInt();

    DeltaConnectionManager->SlidingPort->setPortName(comPort);
    DeltaConnectionManager->SlidingPort->setBaudRate(baudrate);

    if (connectionState == true)
    {
        if (DeltaConnectionManager->SlidingPort->open((QIODevice::ReadWrite)) == true)
        {
            ui->pbSlidingConnect->setText("Disconnect");
            ui->lbSliderCOMName->setText(comPort);
        }
    }

    setting->endGroup();

    //---- MCU -----

    setting->beginGroup("MCU");

    connectionState = setting->value("State", false).toBool();
    comPort = setting->value("ComPort", "COM1").toString();
    baudrate = setting->value("Baudrate", 115200).toInt();

    DeltaConnectionManager->ExternalControllerPort->setPortName(comPort);
    DeltaConnectionManager->ExternalControllerPort->setBaudRate(baudrate);

    if (connectionState == true)
    {
        if (DeltaConnectionManager->ExternalControllerPort->open((QIODevice::ReadWrite)) == true)
        {
            ui->pbExternalControllerConnect->setText("Disconnect");
            ui->lbExternalCOMName->setText(comPort);
        }
    }

    setting->endGroup();

    //-------------

    setting->endGroup();
}

void RobotWindow::LoadTerminalSettings(QSettings *setting)
{

}

void RobotWindow::LoadGcodeEditorSettings(QSettings *setting)
{
    setting->beginGroup("GcodeEditor");
    DeltaGcodeManager->LoadSettings(setting);
    setting->endGroup();
}

void RobotWindow::LoadObjectDetectorSetting(QSettings *setting)
{
    setting->beginGroup("ObjectDetector");

    ui->cbCameraWidgetHeight->setCurrentText(setting->value("CameraWidgetHeight", "300").toString());

    DeltaImageProcesser->LoadSetting(setting);
    ui->cameraWidget->LoadSetting(setting);    

    if (setting->value("WarpEnable", false).toBool() == true)
    {
        ui->pbWarpTool->clicked(true);
        ui->pbWarpTool->setChecked(true);
    }
    else
    {
        ui->pbWarpTool->clicked(false);
        ui->pbWarpTool->setChecked(false);
    }

    if (setting->value("CalibDisplayEnable", false).toBool() == true)
    {
        ui->cbDisplayCalibInfo->clicked(true);
        ui->cbDisplayCalibInfo->setChecked(true);
    }
    else
    {
        ui->cbDisplayCalibInfo->setChecked(false);
        ui->cbDisplayCalibInfo->clicked(false);
    }

    setting->endGroup();
}

void RobotWindow::LoadDrawingSetting(QSettings *setting)
{

}

void RobotWindow::LoadPluginSetting(QSettings *setting)
{
    setting->beginGroup("Plugin");

    int id = 0;

    for (int i = 0; i < pluginList->count(); i++)
    {
        DeltaXPlugin* plugin = pluginList->at(i);
        setting->beginGroup(plugin->GetName() + "-" + QString::number(id++));

        plugin->LoadSettings(setting);

        setting->endGroup();
    }

    setting->endGroup();
}

void RobotWindow::SaveSettings(QSettings *setting)
{
    SaveGeneralSettings(setting);
    SaveJoggingSettings(setting);
    Save2DSettings(setting);
    Save3DSettings(setting);
    SaveExternalDeviceSettings(setting);
    SaveTerminalSettings(setting);
    SaveGcodeEditorSettings(setting);
    SaveObjectDetectorSetting(setting);
    SaveDrawingSetting(setting);
    SavePluginSetting(setting);
}

void RobotWindow::SaveGeneralSettings(QSettings *setting)
{
    setting->setValue("ComName", DeltaConnectionManager->RobotPort->portName());
    setting->setValue("DefaultBaudrate", DeltaConnectionManager->RobotPort->baudRate());
    setting->setValue("IP", TCPConnectionManager::GetIP());
    setting->setValue("TCPPort", DeltaConnectionManager->TCPConnection->Port);
    setting->setValue("RobotModel", ui->cbRobotModel->currentText());
    setting->setValue("RobotState", DeltaConnectionManager->RobotPort->isOpen());

    setting->setValue("Name", Name);

    //---- Tracking ----
    setting->setValue("EncoderEnable", ui->rbEncoderEnable->isChecked());
    setting->setValue("InverseEncoderEnable", ui->cbEncoderPositionInverse->isChecked());
    setting->setValue("ConstantConveyorSpeed", ui->leConvenyorSpeed->text());
    setting->setValue("ConveyorDirection", ui->cbConveyorDirection->currentText());
    setting->setValue("ConveyorDeviationAngle", ui->leConveyorDeviationAngle->text());
    setting->setValue("ForwardConveyorGcode", ui->leForwardConveyorGcode->text());
    setting->setValue("BackwardConveyorGcode", ui->leBackwardConveyorGcode->text());
    setting->setValue("TurnOffConveyorGcode", ui->leTurnOffConveyorGcode->text());
}

void RobotWindow::SaveJoggingSettings(QSettings *setting)
{
    setting->beginGroup("Jogging");
    setting->endGroup();
}

void RobotWindow::Save2DSettings(QSettings *setting)
{
    setting->beginGroup("Jogging");
    setting->setValue("2DSize", Delta2DVisualizer->geometry());
    setting->endGroup();
}

void RobotWindow::Save3DSettings(QSettings *setting)
{
    setting->beginGroup("3D");

    setting->endGroup();
}

void RobotWindow::SaveExternalDeviceSettings(QSettings *setting)
{
    setting->beginGroup("ExternalDevice");

    //---- Conveyor -----
    setting->beginGroup("Conveyor");

    bool connectionState = DeltaConnectionManager->ConveyorPort->isOpen();
    QString comPort = DeltaConnectionManager->ConveyorPort->portName();
    int baudrate = DeltaConnectionManager->ConveyorPort->baudRate();

    setting->setValue("State", connectionState);
    setting->setValue("ComPort", comPort);
    setting->setValue("Baudrate", baudrate);
    setting->setValue("ControlMode", ui->cbConveyorMode->currentText());
    setting->setValue("MovingMode", ui->cbConveyorValueType->currentText());
    setting->setValue("MovingValue", ui->leConveyorvMovingValue->text());

    setting->endGroup();

    //---- Encoder -----

    setting->beginGroup("Encoder");

    connectionState = COMEncoder->COMPort->isOpen();
    comPort = COMEncoder->COMPort->portName();
    baudrate = COMEncoder->COMPort->baudRate();

    setting->setValue("State", connectionState);
    setting->setValue("ComPort", comPort);
    setting->setValue("Baudrate", baudrate);

    setting->endGroup();

    //---- Slider -----

    setting->beginGroup("Slider");

    connectionState = DeltaConnectionManager->SlidingPort->isOpen();
    comPort = DeltaConnectionManager->SlidingPort->portName();
    baudrate = DeltaConnectionManager->SlidingPort->baudRate();

    setting->setValue("State", connectionState);
    setting->setValue("ComPort", comPort);
    setting->setValue("Baudrate", baudrate);

    setting->endGroup();

    //---- MCU -----

    setting->beginGroup("MCU");

    connectionState = DeltaConnectionManager->ExternalControllerPort->isOpen();
    comPort = DeltaConnectionManager->ExternalControllerPort->portName();
    baudrate = DeltaConnectionManager->ExternalControllerPort->baudRate();

    setting->setValue("State", connectionState);
    setting->setValue("ComPort", comPort);
    setting->setValue("Baudrate", baudrate);

    setting->endGroup();

    //-------------

    setting->endGroup();
}

void RobotWindow::SaveTerminalSettings(QSettings *setting)
{
    setting->beginGroup("Terminal");

    setting->endGroup();
}

void RobotWindow::SaveGcodeEditorSettings(QSettings *setting)
{
    setting->beginGroup("GcodeEditor");
    DeltaGcodeManager->SaveSettings(setting);

    setting->endGroup();
}

void RobotWindow::SaveObjectDetectorSetting(QSettings *setting)
{
    setting->beginGroup("ObjectDetector");

    setting->setValue("CameraWidgetHeight", ui->cbCameraWidgetHeight->currentText());

    setting->setValue("ConveyorPoint1", QPointF(ui->leConveyorPoint1X->text().toFloat(), ui->leConveyorPoint1Y->text().toFloat()));
    setting->setValue("ConveyorPoint2", QPointF(ui->leConveyorPoint2X->text().toFloat(), ui->leConveyorPoint2Y->text().toFloat()));
    setting->setValue("ConveyorPoint3", QPointF(ui->leConveyorPoint3X->text().toFloat(), ui->leConveyorPoint3Y->text().toFloat()));

    setting->setValue("ConveyorDeviationAngle", ui->leConveyorDeviationAngle->text());

    setting->setValue("WarpEnable", DeltaImageProcesser->IsPerspectiveMode);
    setting->setValue("CalibDisplayEnable", DeltaImageProcesser->IsCalibInfoVisible);


    DeltaImageProcesser->SaveSetting(setting);
    ui->cameraWidget->SaveSetting(setting);
    setting->endGroup();
}

void RobotWindow::SaveDrawingSetting(QSettings *setting)
{
    setting->beginGroup("Drawing");

    setting->endGroup();
}

void RobotWindow::SavePluginSetting(QSettings *setting)
{
    setting->beginGroup("Plugin");

    for (int i = 0; i < pluginList->count(); i++)
    {
        DeltaXPlugin* plugin = pluginList->at(i);

        QString name = plugin->GetName();

        setting->beginGroup(name + "-" + QString::number(i));

        plugin->SaveSettings(setting);

        setting->endGroup();
    }

    setting->endGroup();
}

void RobotWindow::SetMainStackedWidgetAndPages(QStackedWidget *mainStack, QWidget *mainPage, QWidget *fullDisplayPage, QLayout *fullDisplayLayout)
{
    this->MainWindowStackedWidget = mainStack;
    this->MainWindowPage = mainPage;
    this->FullDisplayPage = fullDisplayPage;
    this->FullDisplayLayout = fullDisplayLayout;
    connect(ui->twDeltaGeometry, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(MaximizeTab(int)));
    connect(ui->twModule, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(MaximizeTab(int)));
}

void RobotWindow::SetSubStackedWidget(QStackedWidget *subStackedWidget)
{
    this->SubWindowStackedWidget = subStackedWidget;
}

QWidget *RobotWindow::GetWidget(QString name)
{
    QWidget* widget = this->findChild<QWidget*>(GetRealNameWidget(name));

    return widget;
}

QString RobotWindow::GetRealNameWidget(QString name)
{
    QMapIterator<QString, QString> i(ParseNames);
    while (i.hasNext()) {
        i.next();
        if (i.key() == name)
            return i.value();
    }

    return "";
}

QString RobotWindow::GetRedefineNameWidget(QString name)
{
    QMapIterator<QString, QString> i(ParseNames);
    while (i.hasNext()) {
        i.next();
        if (i.key() == name)
            return i.key();
    }

    return "";
}

QStringList RobotWindow::GetShareDisplayWidgetNames()
{
    QStringList list;
    list.append("CameraWidget");

    return list;
}

void RobotWindow::SelectImageProviderOption(int option)
{
    ui->fPluginSource->setHidden(true);
    ui->fWebcamSource->setHidden(true);
    ui->fImageSource->setHidden(true);

    QString text = ui->cbSourceForImageProvider->itemText(option);

    if (text == "Webcam")
    {
        ui->fWebcamSource->setHidden(false);
    }
    if (text == "Plugin")
    {
        ui->fPluginSource->setHidden(false);
    }
    if (text == "Images")
    {
        ui->fImageSource->setHidden(false);
    }
}

void RobotWindow::SetID(int id)
{
    ID = id;
    RobotParamter.ID = id;
    ui->lbID->setText(QString::number(id));
}

void RobotWindow::SetName(QString name)
{
    RobotParamter.Name = name;
    Name = name;
}

void RobotWindow::ConnectDeltaRobot()
{
	if (ui->cbAutoConnect->isChecked() == false)
	{
        bool isConnect = openConnectionDialog(DeltaConnectionManager->RobotPort, DeltaConnectionManager->RobotSocket, ui->pbConnect);

		if (isConnect == true)
		{
			DeltaConnectionManager->SendToRobot("IsDelta");
			DeltaConnectionManager->SendToRobot("IsDelta");
		}

		return;
	}

	if (ui->pbConnect->text() == "Connect" && !DeltaConnectionManager->IsRobotConnect())
	{
        OpenLoadingPopup();
        DeltaConnectionManager->FindDeltaRobot();
	}

	else if (ui->pbConnect->text() == "Disconnect")
	{
		ui->pbConnect->setText("Connect");

		if (DeltaConnectionManager->IsRobotConnect())
			DeltaConnectionManager->DisconnectRobot();
	}
}

void RobotWindow::RunSmartEditor()
{
	
}

void RobotWindow::StandardFormatEditor()
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
                if ((oldNumbers.at(i).toInt() == gotoIndexS.toInt()) && gotoIndexS != "")
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

		ui->pteGcodeArea->setHtml(htmlText);
    }
}

void RobotWindow::OpenGcodeReference()
{
//	GcodeReference* gcodeReferenceWindow = new GcodeReference();
//	gcodeReferenceWindow->show();
    QUrl myUrl("https://www.deltaxrobot.com/p/gcode.html");
    QDesktopServices::openUrl(myUrl);
}

void RobotWindow::ConfigConnection()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Baudrate for COM"),
		tr("Baudrate:"), QLineEdit::Normal,
		QString::number(DeltaConnectionManager->GetBaudrate()), &ok);
	if (ok && !text.isEmpty())
		DeltaConnectionManager->SetBaudrate(text.toInt());
}

void RobotWindow::ChangeDeltaDashboard(int index)
{
    // ---- If press "Add new robot" --------
    if (ui->twDeltaManager->tabText(index) == "+")
    {
        //----- Creat new robot window -----------
        RobotManagerPointer->CreatNewRobotWindow();
	}
    // -------- Select other robot ---------
	else
    {
        if (RobotManagerPointer->SubWindowStackedWidget != NULL)
        {
            RobotManagerPointer->SubWindowStackedWidget->setCurrentIndex(index);

            RobotManagerPointer->RobotWindows.at(index)->ui->twDeltaManager->setCurrentIndex(index);
        }
    }
}

void RobotWindow::SelectTrueTabName(int index)
{

}

void RobotWindow::AddNewProgram()
{
	DeltaGcodeManager->AddNewProgram();
}

void RobotWindow::SaveProgram()
{
	DeltaGcodeManager->SaveGcodeIntoFile();
}

void RobotWindow::ExecuteProgram()
{
    if (ui->rbEditorStart->isChecked() == true)
    {
        DeltaGcodeManager->SetStartingGcodeEditorCursor("beginning");
    }
    else
    {
        DeltaGcodeManager->SetStartingGcodeEditorCursor("current");
    }

	QPushButton* pbExe = qobject_cast<QPushButton*>(sender());

    if (pbExe != NULL)
    {
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
    }

	SaveProgram();

	QString exeGcodes = ui->pteGcodeArea->toPlainText();
    DeltaGcodeManager->ExecuteGcode(exeGcodes, true);
}

void RobotWindow::ClickExecuteButton(bool val)
{
    //ui->pbExecuteGcodes->setChecked(val);
    if (ui->pbExecuteGcodes->isChecked() == false && val == true)
        ui->pbExecuteGcodes->click();

    if (ui->pbExecuteGcodes->isChecked() == true && val == false)
        ui->pbExecuteGcodes->click();
    //ui->pbExecuteGcodes->setChecked(val);
}

void RobotWindow::ImportGcodeFilesFromComputer()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open G-code Files"), "",	tr("G-code file (*.dtgc);;All Files (*)"));

    foreach (QString fileName, fileNames)
	{
		QFileInfo fileInfo(fileName);
		QString newFullName = QDir::currentPath() + "/" + fileInfo.fileName();

        if (QFile::exists(newFullName) && fileName != newFullName)
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

void RobotWindow::UploadGcodeFileToServer()
{
	QMessageBox::information(this, "Sorry!", "This function is not yet available");
}

void RobotWindow::SearchGcodeFile()
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

void RobotWindow::ExecuteSelectPrograms()
{
    // If only one robot, execute program for it
    if (RobotManagerPointer != NULL)
    {
        if (RobotManagerPointer->RobotWindows.size() == 1)
        {
            ui->pbExecuteGcodes->click();
            return;
        }
    }
    // Execute selected robots
	QList<QAction*> actions = ui->menuExecute->actions();
	for (int i = 0; i < actions.size(); i++)
	{
        if (actions.at(i)->isChecked() == true)
        {
            QString actionName = actions.at(i)->text();

            if (RobotManagerPointer == NULL)
                break;

            for (int j = 0; j < RobotManagerPointer->RobotWindows.size(); j++)
            {
                if (RobotManagerPointer->RobotWindows.at(j)->Name == actionName)
                {
                    RobotManagerPointer->RobotWindows.at(j)->ui->pbExecuteGcodes->click();
                }
            }
        }
	}
}

void RobotWindow::ExecuteCurrentLine()
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

void RobotWindow::UpdateZLineEditValue(int z)
{
	ui->leZ->setText(QString::number(Delta2DVisualizer->ZHome - z));
}

void RobotWindow::UpdateAngleLineEditValue(int w)
{
    ui->leW->setText(QString::number(ui->vsAngleAdjsution->value()));
    ui->leU->setText(QString::number(ui->vs5AxisAdjsution->value()));
    ui->leV->setText(QString::number(ui->vs6AxisAdjsution->value()));

    ui->lb4AxisValue->setText(QString::number(ui->vsAngleAdjsution->value()));
    ui->lb5AxisValue->setText(QString::number(ui->vs5AxisAdjsution->value()));
    ui->lb6AxisValue->setText(QString::number(ui->vs6AxisAdjsution->value()));
}

void RobotWindow::UpdateDeltaPositionFromLineEditValue()
{
    DisablePositionUpdatingEvents();

    //---- 1. Delta 2D Visualizer Values----
    if (positionEmitter != "Delta2DVisualizer")
    {
        Delta2DVisualizer->X = ui->leX->text().toFloat();
        Delta2DVisualizer->Y = ui->leY->text().toFloat();
        Delta2DVisualizer->Z = ui->leZ->text().toFloat();
        Delta2DVisualizer->W = ui->leW->text().toFloat();
        Delta2DVisualizer->U = ui->leU->text().toFloat();
        Delta2DVisualizer->V = ui->leV->text().toFloat();
    }

    //---- 2. Z Slider -----
	ui->vsZAdjsution->setValue(Delta2DVisualizer->ZHome - Delta2DVisualizer->Z);

    //---- 3. Delta 2D Visualizer Display ------
    Delta2DVisualizer->ChangeXY(ui->leX->text().toFloat(), ui->leY->text().toFloat());

    //---- 4. Position Label ---
    UpdatePositionToLabel();

    //---- 5. Gcode Editor Para ----

    QString gcode = QString("G01 X%1 Y%2 Z%3 W%4 U%5 V%6\n").arg(Delta2DVisualizer->X).arg(Delta2DVisualizer->Y).arg(Delta2DVisualizer->Z).arg(Delta2DVisualizer->W).arg(Delta2DVisualizer->U).arg(Delta2DVisualizer->V);

    DeltaConnectionManager->SendToRobot(gcode);

    EnablePositionUpdatingEvents();

    positionEmitter = "";
}

void RobotWindow::UpdatePositionToLabel()
{
    ui->lbX->setText(QString::number(Delta2DVisualizer->X));
    ui->lbY->setText(QString::number(Delta2DVisualizer->Y));
    ui->lbZ->setText(QString::number(Delta2DVisualizer->Z));
    ui->lbW->setText(QString::number(Delta2DVisualizer->W));
    ui->lbU->setText(QString::number(Delta2DVisualizer->U));
    ui->lbV->setText(QString::number(Delta2DVisualizer->V));
}

void RobotWindow::UpdateTextboxFrom2DControl(float x, float y, float z, float w, float u, float v)
{
    positionEmitter = "Delta2DVisualizer";

    DisablePositionUpdatingEvents();
	ui->leX->setText(QString::number(x));
	ui->leY->setText(QString::number(y));
	ui->leZ->setText(QString::number(z));
	ui->leW->setText(QString::number(w));
    ui->leU->setText(QString::number(u));
    ui->leV->setText(QString::number(v));
    EnablePositionUpdatingEvents();

    UpdateDeltaPositionFromLineEditValue();
}

void RobotWindow::UpdateTextboxFrom3DControl(float x, float y, float z, float w, float u, float v)
{
    positionEmitter = "Delta3DVisualizer";
    DisablePositionUpdatingEvents();

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
    EnablePositionUpdatingEvents();

	UpdateDeltaPositionFromLineEditValue();
}

void RobotWindow::UpdatePositionControl(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e)
{
    DisablePositionUpdatingEvents();

    if (x == 0 && y == 0 && z == 0 && w == 0 && u == 0 && v == 0)
	{
		x = Delta2DVisualizer->XHome;
		y = Delta2DVisualizer->YHome;
		z = Delta2DVisualizer->ZHome;
		w = Delta2DVisualizer->WHome;
        u = Delta2DVisualizer->UHome;
        v = Delta2DVisualizer->VHome;
	}

	ui->leX->setText(QString::number(x));
	ui->leY->setText(QString::number(y));
	ui->leZ->setText(QString::number(z));
	ui->leW->setText(QString::number(w));
    ui->leU->setText(QString::number(u));
    ui->leV->setText(QString::number(v));
	ui->leVelocity->setText(QString::number(f));
	ui->leAccel->setText(QString::number(a));
    ui->leStartSpeed->setText(QString::number(s));
    ui->leEndSpeed->setText(QString::number(e));

	Delta2DVisualizer->X = x;
	Delta2DVisualizer->Y = y;
	Delta2DVisualizer->Z = z;
	Delta2DVisualizer->W = w;
    Delta2DVisualizer->U = u;
    Delta2DVisualizer->V = v;
    Delta2DVisualizer->F = f;
    Delta2DVisualizer->A = a;
    Delta2DVisualizer->S = s;
    Delta2DVisualizer->E = e;

	ui->vsZAdjsution->setValue(Delta2DVisualizer->ZHome - Delta2DVisualizer->Z);
	Delta2DVisualizer->ChangeXY(x, y);

    EnablePositionUpdatingEvents();
}

void RobotWindow::UpdateGlobalHomePositionValueAndControlValue(float x, float y, float z, float w, float u, float v)
{
    Delta2DVisualizer->XHome = Delta2DVisualizer->X = x;
    Delta2DVisualizer->YHome = Delta2DVisualizer->Y = y;
    Delta2DVisualizer->ZHome = Delta2DVisualizer->Z = z;
    Delta2DVisualizer->WHome = Delta2DVisualizer->W = w;
    Delta2DVisualizer->UHome = Delta2DVisualizer->U = u;
    Delta2DVisualizer->VHome = Delta2DVisualizer->V = v;

    UpdateTextboxFrom2DControl(x, y, z, w, u, v);
}

void RobotWindow::UpdateVelocity()
{
    QString value = ui->leVelocity->text();
    DeltaGcodeManager->SaveGcodeVariable("#F", value);
    DeltaConnectionManager->SendToRobot(QString("G01 F") + value);
}

void RobotWindow::UpdateAccel()
{
    QString value = ui->leAccel->text();
    DeltaGcodeManager->SaveGcodeVariable("#A", value);
    DeltaConnectionManager->SendToRobot(QString("M204 A") + ui->leAccel->text());
}

void RobotWindow::UpdateStartSpeed()
{
    QString value = ui->leStartSpeed->text();
    DeltaGcodeManager->SaveGcodeVariable("#S", value);
    DeltaConnectionManager->SendToRobot(QString("M205 S") + ui->leStartSpeed->text());
}

void RobotWindow::UpdateEndSpeed()
{
    QString value = ui->leEndSpeed->text();
    DeltaGcodeManager->SaveGcodeVariable("#E", value);
    DeltaConnectionManager->SendToRobot(QString("M205 E") + ui->leEndSpeed->text());
}

void RobotWindow::AdjustGripperAngle(int angle)
{
	DeltaConnectionManager->SendToRobot(QString("M360 E1"));
	DeltaConnectionManager->SendToRobot(QString("M03 S") + QString::number(angle * 5));

	ui->lbGripperValue->setText(QString::number(angle * 5));
}

void RobotWindow::Grip()
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

void RobotWindow::SetPump(bool value)
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

void RobotWindow::SetLaser(bool value)
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

void RobotWindow::Home()
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

void RobotWindow::SetOnOffOutput(bool result)
{
    QString widgetName = sender()->objectName();
    if (widgetName.indexOf("D") > -1 || widgetName.indexOf("R") > -1)
    {
        // R1, R2, ... D1, D2, ... checkbox

        QString outputName = widgetName.mid(2);
        if (outputName.indexOf("Dx") > -1)
        {
            outputName = ui->leDx->text();
        }
        if (outputName.indexOf("Rx") > -1)
        {
            outputName = ui->leRx->text();
        }

        if (result == true)
        {
            sendGcode("M03", outputName, "");
        }
        else
        {
            sendGcode("M05", outputName, "");
        }
    }
}

void RobotWindow::SetValueOutput()
{
    // lePxValue, leSxValue, leP0Value, leS0Value, ...
    QLineEdit* leValue = qobject_cast<QLineEdit*>(sender());
    QString valueName = "W" + leValue->text();
    QString outputName = leValue->objectName().mid(2, leValue->objectName().indexOf("Value") - 2);

    if (outputName.indexOf("Px") > -1)
    {
        outputName = ui->lePx->text();
    }
    if (outputName.indexOf("Sx") > -1)
    {
        outputName = ui->leSx->text();
    }

    sendGcode("M03", outputName, valueName);
}

void RobotWindow::RequestValueInput()
{
    // pbReadI0, pbReadI1, ... pbReadIx
    QString inputName = sender()->objectName().mid(6);
    QString inputID = inputName.mid(1);
    QCheckBox* cbInputType = (QCheckBox*)getObjectByName(sender()->parent(), QString("cbToggle") + inputID);
    QLineEdit* leDelay = (QLineEdit*)getObjectByName(sender()->parent(), QString("leA") + inputID + "Delay");
    QLineEdit* leInputName = (QLineEdit*)getObjectByName(sender()->parent(), QString("leAx"));

    if (inputName.indexOf("I") > - 1)
    {
        leInputName = (QLineEdit*)getObjectByName(sender()->parent(), QString("leIx"));
    }

    if (inputID == "x" && leInputName != NULL)
    {
        inputName = leInputName->text();
    }

    if (inputName.indexOf("I") > -1)
    {
        if (cbInputType->isChecked() == true)
        {
            DeltaConnectionManager->SendToRobot("M08 " + inputName);
        }
        else
        {
            DeltaConnectionManager->SendToRobot("M07 " + inputName);
        }
    }
    else
    {
        if (leDelay->text() == "")
        {
            DeltaConnectionManager->SendToRobot("M08 " + inputName);
        }
        else
        {
            DeltaConnectionManager->SendToRobot("M08 " + inputName + " W" + leDelay->text());
        }
    }

}

void RobotWindow::GetValueInput(QString response)
{
    response = response.replace("\n", "");
    response = response.replace("\r", "");

    // Ix Vy, Ax Vy, ...
    QString value = response.mid(response.indexOf("V") + 1);

    QString pinName = response.mid(1, response.indexOf(" V"));
    QString pin = response.mid(0, response.indexOf(" V"));
    DeltaGcodeManager->UpdateSystemVariable(pin, value);
    // lbI1Vlaue, lbIxValue, lbA0Value, lbAxValue
    QLabel* lbValue;

    if (response.indexOf("I") > - 1)
    {
        if (pinName.toInt() > 5)
        {
            lbValue = lbInputValues->at(6);
        }
        else
        {
            lbValue = lbInputValues->at(pinName.toInt());
        }
    }

    if (response.indexOf("A") > - 1)
    {
        if (pinName.toInt() > 1)
        {
            lbValue = lbInputValues->at(9);
        }

        else
        {
            lbValue = lbInputValues->at(pinName.toInt() + 7);
        }
    }

    lbValue->setText(value);
}

void RobotWindow::SetConvenyorSpeed()
{
    QString vel = ui->leConvenyorSpeed->text();
	QString directionName = ui->cbConveyorDirection->currentText();

    DeltaImageProcesser->SetConvenyorVelocity(vel.toFloat(), directionName);

    DeltaGcodeManager->SaveGcodeVariable("#ConveyorSpeed", vel);
    DeltaGcodeManager->SaveGcodeVariable("#ConveyorDirection", (directionName.toLower()=="x") ? "0" : "1");
}

void RobotWindow::ConnectEncoder()
{
    bool result = COMEncoder->Connect();

    if (result == true)
    {
        ui->pbConnectEncdoer->setText("Disconnect Encoder");
        COMEncoder->Send(QString("M317 T100\n"));

        ui->leEncoderCom->setText(COMEncoder->COMPort->portName());

    }
    else
    {
        ui->pbConnectEncdoer->setText("Connect Encoder");
    }
}

void RobotWindow::ResetEncoderPosition()
{
    COMEncoder->Send(QString("M316\n"));
}

void RobotWindow::ReceiveEncoderResponse(QString response)
{
    if (ui->rbEncoderEnable->isChecked() == false)
        return;

    // Ex: P200
    if (response.at(0) == "P")
    {

        float pos = response.mid(1).toFloat();
        ProcessEncoderValue(pos);
    }
}

void RobotWindow::UpdatePointPositionOnConveyor(QLineEdit *x, QLineEdit *y, float angle, float distance)
{
    QPointF point3;

    point3.setX(x->text().toFloat());
    point3.setY(y->text().toFloat());


    QLineF line;
    line.setP1(point3);
    line.setAngle(angle);

    if (distance == 0)
        return;

    line.setLength(distance);

    if (point3 == QPointF(0, 0))
    {
        float cosa = qCos(qDegreesToRadians(360 - angle));
        float sina = qSin(qDegreesToRadians(360 - angle));

        line.setP2(QPointF(distance * cosa, distance * sina));
    }

    float p2X = ((float)((int)(line.p2().x() * 100))) / 100;
    float p2Y = ((float)((int)(line.p2().y() * 100))) / 100;

    x->setText(QString::number(p2X));
    y->setText(QString::number(p2Y));
}

void RobotWindow::CalculateConveyorDeviationAngle()
{
    QPointF point1, point2, point3;
    point1.setX(ui->leConveyorPoint1X->text().toFloat());
    point1.setY(ui->leConveyorPoint1Y->text().toFloat());

    point2.setX(ui->leConveyorPoint2X->text().toFloat());
    point2.setY(ui->leConveyorPoint2Y->text().toFloat());

    QLineF line(point1, point2);

    ui->leConveyorDeviationAngle->setText(QString::number(line.angle()));

    DeltaImageProcesser->DeviationAngle = line.angle();
}

void RobotWindow::UpdateDetectObjectSize()
{
	float realObjLength = ui->leLRec->text().toFloat();
	float realObjWidth = ui->leWRec->text().toFloat();

	float lObjectInWidget = realObjLength * DeltaImageProcesser->DnRratio;
	float wObjectInWidget = realObjWidth * DeltaImageProcesser->DnRratio;

    DeltaImageProcesser->GetObjectInfo(lObjectInWidget, wObjectInWidget);
}

void RobotWindow::UpdateCursorPosition(float x, float y)
{
//	ui->lbXCursor->setText(QString::number(x));
//	ui->lbYCursor->setText(QString::number(y));
}

void RobotWindow::AddObjectsToROS(std::vector<cv::RotatedRect> ObjectContainer)
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

void RobotWindow::DeleteAllObjectsInROS()
{
    DeltaConnectionManager->TCPConnection->SendMessageToROS("delete all");
}

void RobotWindow::GetImageFromExternal(cv::Mat mat)
{
    if (ui->cbExternalImageSource->isChecked() == false)
        return;

    ElapsedTimer.start();
    DeltaImageProcesser->TaskOrder = 0;
    DeltaImageProcesser->GetImage(mat);

    qDebug() << "Get Image Time: " << ElapsedTimer.elapsed();
    DeltaImageProcesser->TaskExecute();
    qDebug() << "Update Event time: " << ElapsedTimer.elapsed();
}

void RobotWindow::ConnectConveyor()
{
    openConnectionDialog(DeltaConnectionManager->ConveyorPort, DeltaConnectionManager->ConveyorSocket, ui->pbConveyorConnect, ui->lbConveyorCOMName);
}

void RobotWindow::SetConveyorMode(int mode)
{
	DeltaConnectionManager->ConveyorSend(QString("M310 ") + QString::number(mode));
}

void RobotWindow::SetConveyorMovingMode(int mode)
{
	if (mode == 0)
    {
        ui->leSpeedOfPositionMode->setEnabled(false);
        ui->lbUnitOfConveyorMoving->setText("mm/s");
	}
	else
    {
        ui->leSpeedOfPositionMode->setEnabled(true);
        ui->lbUnitOfConveyorMoving->setText("mm");
	}
}

void RobotWindow::SetSpeedOfPositionMode()
{
	DeltaConnectionManager->ConveyorSend(QString("M313 ") + ui->leSpeedOfPositionMode->text());
}

void RobotWindow::MoveConveyor()
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

void RobotWindow::ProcessShortcutKey()
{

}

void RobotWindow::ProcessDetectedObjectFromExternalAI(QString msg)
{
    QStringList paras = msg.split(",");
    if (paras.count() >= 4)
    {
        //QString label = paras[0];
        QString x = paras[0];
        QString y = paras[1];
        QString w = paras[2];
        QString h = paras[3];

        float delta = DeltaImageProcesser->EncoderPosition - DeltaImageProcesser->EncoderPositionAtCameraCapture;

        if (ui->cbConveyorDirection->currentText() == "Y")
        {
            DeltaImageProcesser->ObjectManager->AddNewObject(x.toFloat(), y.toFloat() + delta, w.toFloat(), h.toFloat());
        }
        else
        {
            DeltaImageProcesser->ObjectManager->AddNewObject(x.toFloat()  + delta, y.toFloat(), w.toFloat(), h.toFloat());
        }

    }
}

void RobotWindow::AddDisplayObjectFromExternalScript(QString msg)
{
    DeltaImageProcesser->DisplayObjects->clear();
    QStringList objectInfos = msg.split(";");
    foreach(QString objectInfo, objectInfos)
    {
        if (objectInfo.replace(" ", "").replace("/n", "") == "")
            continue;

        QStringList paras = objectInfo.split(",");
        if (paras.count() >= 5)
        {
            //QString label = paras[0];
            float x = paras[0].toFloat();
            float y = paras[1].toFloat();
            float w = paras[2].toFloat();
            float h = paras[3].toFloat();
            float a = paras[4].toFloat();

            cv::RotatedRect object(cv::Point2f(x, y), cv::Size(w, h), a);
            DeltaImageProcesser->DisplayObjects->append(object);

        }
    }

//    qDebug() << ElapsedTimer.elapsed();
    DeltaImageProcesser->ProcessDisplayAfterReceivingObjectData();
    DeltaImageProcesser->DisplayObjects->clear();
}

void RobotWindow::MoveExternalConveyor()
{
    QString direction = ui->cbConveyorDirectionControl->currentText();
    ConveyorPositionBeforeMove = Encoder1->GetPosition();
    ConveyorDistanceToMove = ui->leMovingDistanceConveyorControl->text().toFloat();

    if (direction == "Backward")
    {
        BackwardExternalConveyor();
    }
    else
    {
        ForwardExternalConveyor();
    }
}

void RobotWindow::CheckForTurnOffExternalConveyor()
{
    if (ConveyorDistanceToMove != 0)
    {
        float movedDistance = abs(Encoder1->GetPosition() - ConveyorPositionBeforeMove);
        if (movedDistance >= abs(ConveyorDistanceToMove))
        {
            TurnOffExternalConveyor();
            ConveyorDistanceToMove = 0;
        }
    }
}

void RobotWindow::ForwardExternalConveyor()
{
    QString command = ui->leForwardConveyorGcode->text();
    QStringList gcodes = command.split(',');

    foreach(QString gcode, gcodes)
    {
        gcode = DeleteExcessSpace(gcode);
        DeltaConnectionManager->SendToRobot(gcode);
    }
}

void RobotWindow::BackwardExternalConveyor()
{
    QString command = ui->leBackwardConveyorGcode->text();
    QStringList gcodes = command.split(',');

    foreach(QString gcode, gcodes)
    {
        gcode = DeleteExcessSpace(gcode);
        DeltaConnectionManager->SendToRobot(gcode);
    }
}

void RobotWindow::TurnOffExternalConveyor()
{
    QString command = ui->leTurnOffConveyorGcode->text();
    QStringList gcodes = command.split(',');

    foreach(QString gcode, gcodes)
    {
        gcode = DeleteExcessSpace(gcode);
        DeltaConnectionManager->SendToRobot(gcode);
    }
}

void RobotWindow::VirtualEncoder()
{
    if (ui->rbVirtualEncoderEnable->isChecked() == false)
        return;

    float velocity = ui->leConvenyorSpeed->text().toFloat();
    float distance = velocity * 0.1f;
    ProcessEncoderValue(distance);
}

void RobotWindow::ProcessEncoderValue(float value)
{
    float pos = value;
    float deviationAngle = ui->leConveyorDeviationAngle->text().toFloat();

    Encoder1->SetDeviationAngle(deviationAngle);

    if (ui->cbEncoderPositionInverse->isChecked() == true)
    {
        Encoder1->SetPosition(pos * -1);
    }
    else
    {
        Encoder1->SetPosition(pos);
    }

    CheckForTurnOffExternalConveyor();

    updateEncoderUI();

    DeltaGcodeManager->SaveGcodeVariable("#EncoderMoving", QString::number(DeltaImageProcesser->MovingDistance));
    DeltaGcodeManager->SaveGcodeVariable("#EncoderPosition", QString::number(DeltaImageProcesser->EncoderPosition));

    DeltaImageProcesser->UpdateObjectPositionOnConveyor(Encoder1->GetOffset());
}

void RobotWindow::ConnectSliding()
{
    openConnectionDialog(DeltaConnectionManager->SlidingPort, DeltaConnectionManager->SlidingSocket, ui->pbSlidingConnect, ui->lbSliderCOMName);
}

void RobotWindow::GoHomeSliding()
{
	DeltaConnectionManager->SlidingSend("M320");
}

void RobotWindow::DisableSliding()
{
	DeltaConnectionManager->SlidingSend("M323");
}

void RobotWindow::SetSlidingSpeed()
{
	DeltaConnectionManager->SlidingSend(QString("M321 ") + ui->leSlidingSpeed->text());
}

void RobotWindow::SetSlidingPosition()
{
	DeltaConnectionManager->SlidingSend(QString("M322 ") + ui->leSlidingPosition->text());
}

void RobotWindow::ConnectExternalMCU()
{
    openConnectionDialog(DeltaConnectionManager->ExternalControllerPort, DeltaConnectionManager->ExternalControllerSocket, ui->pbExternalControllerConnect, ui->lbExternalCOMName);
}

void RobotWindow::TransmitTextToExternalMCU()
{
    DeltaConnectionManager->ExternalMCUSend(ui->leTransmitToMCU->text());
	ui->leTransmitToMCU->setText("");
}

void RobotWindow::DisplayTextFromExternalMCU(QString text)
{
    QString lastText = ui->teReceiveFromMCU->toPlainText();
    if (lastText.split('\n').count() > 50)
        lastText = "";

    ui->teReceiveFromMCU->setText(lastText + text);
    ui->teReceiveFromMCU->moveCursor(QTextCursor::End);
}

void RobotWindow::TerminalTransmit()
{
	DeltaConnectionManager->SendToRobot(ui->leTerminal->text());
	ui->leTerminal->setText("");
}

void RobotWindow::PrintReceiveData(QString msg)
{
	//msg.replace("\n", "");
    Debug(ID, QString("Robot: ") + msg);
}

void RobotWindow::RunExternalScript()
{
    if (ui->pbRunExternalScript->isChecked() == false)
    {
        ExternalScriptProcess->terminate();

        delete DeltaImageProcesser->PythonTcpClient;

        DeltaImageProcesser->PythonTcpClient = NULL;

        return;
    }

    QString appPath = QCoreApplication::applicationDirPath();
    QString command("python");
    QStringList params = QStringList() << ui->lePythonUrl->text() << "-ip" << ui->lbIP->text() << "-port" << ui->lbLocalPort->text();
    params << "-type" << ui->cbImageSource->currentText().replace(" ", "");
    params << "-ow" << QString::number(DeltaImageProcesser->PobjectRec.width);
    params << "-oh" << QString::number(DeltaImageProcesser->PobjectRec.height);
    params << "-err" << ui->leObjectErrorSize->text();

    //QString imageParas = QString("-h %1 -w %2 -c %3").arg(resizeImage.rows).arg(resizeImage.cols).arg(resizeImage.channels());

    //params << imageParas.split(' ');

    if (ui->lePythonUrl->text().contains(":") == false)
        ExternalScriptProcess->start(QString("cd ") + appPath);

    ExternalScriptProcess->start(command, params);

//    ExternalScriptProcess->waitForFinished(); // sets current thread to sleep and waits for pingProcess end
//    QString output(ExternalScriptProcess->readAllStandardOutput());
//    Debug(output);
//    ExternalScriptProcess->waitForFinished();
//    ExternalScriptProcess->close();

//    QProcess *process = new QProcess(this);
//    QString program = "python";
//    QString folder = "T:\\Delta X Software\\mushroom-1.0.py";
//    process->start(program, QStringList() << folder << "-ip" << ui->lbIP->text() << "-port" << ui->lbLocalPort->text() << "-type" << ui->cbImageSource->currentText().replace(" ", ""));
}

void RobotWindow::NoticeConnected()
{
	Debug(DeltaConnectionManager->GetNamePort());

	ui->pbConnect->setText("Disconnect");

    ui->lbComName->setText(DeltaConnectionManager->GetNamePort());

    CloseLoadingPopup();
}

QString RobotWindow::boldKey(QString key, QString htmlText)
{
	int keyOrder = htmlText.indexOf(key);

	if (keyOrder > -1)
	{
		htmlText = htmlText.replace(key, QString("<span style = \" font-weight:600;\">") + key + "</span>");
	}

	return htmlText;
}

QString RobotWindow::boldPlusKey(QString key, QString plus, QString htmlText)
{
	int keyOrder = htmlText.indexOf(key);

	if (keyOrder > -1)
	{
		htmlText = htmlText.replace(key, QString("<span style = \" font-weight:600;") + plus + "\">" + key + "</span>");
	}

	return htmlText;
}

QString RobotWindow::italyKey(QString key, QString htmlText)
{
	int keyOrder = htmlText.indexOf(key);

	if (keyOrder > -1)
	{
		htmlText = htmlText.replace(key, QString("<span style=\" font - style:italic; \">") + key + "</span>");
	}

	return htmlText;
}

QString RobotWindow::replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText)
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

bool RobotWindow::openConnectionDialog(QSerialPort * comPort, QTcpSocket* socket, QPushButton* connectButton, QLabel* comNameInfo)
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
        comNameInfo->setText("");
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
                items << portInfo.portName() + " - " + portInfo.description();
			}

			bool ok;
			QString item = QInputDialog::getItem(this, tr("COM Connection"), tr("COM Ports:"), items, 0, false, &ok);
            QString comName = item.mid(0, item.indexOf(" - "));

			if (ok && !item.isEmpty())
			{
				bool ok2;
				QString baudrate = QInputDialog::getText(this, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
				if (ok2 && !baudrate.isEmpty())
				{
                    comPort->setPortName(comName);
					comPort->setBaudRate(baudrate.toInt());

					if (comPort->open((QIODevice::ReadWrite)) == true)
					{
						//QMessageBox::information(this, "Noti", "Connected");

						connectButton->setText("Disconnect");

                        comNameInfo->setText(comName);

						return true;
					}
				}
			}
		}
	}

	return false;
}

void RobotWindow::InitTabs()
{
    ui->twDeltaManager->clear();

    QStringList robotNames = RobotManagerPointer->GetRobotNames();

    for (int i = 0; i < robotNames.size(); i++)
    {
        QAction *actionNewDelta_X;
        actionNewDelta_X = new QAction(this);

        actionNewDelta_X->setCheckable(true);
        actionNewDelta_X->setChecked(true);
        actionNewDelta_X->setText(robotNames.at(i));
        ui->menuExecute->addAction(actionNewDelta_X);

        QWidget *newDeltaTab = new QWidget();
        ui->twDeltaManager->addTab(newDeltaTab, robotNames.at(i));
    }

    QWidget *newDeltaTab = new QWidget();
    ui->twDeltaManager->addTab(newDeltaTab, QString());
    ui->twDeltaManager->setTabText(ui->twDeltaManager->indexOf(newDeltaTab), "+");
}

void RobotWindow::SaveSetting()
{
    QString currentName = ui->cbSetting->currentText();

    bool isNewSetting = true;
    for (int i = 0; i < ui->cbSetting->count(); i++)
    {
        if (ui->cbSetting->itemText(i) == currentName)
            isNewSetting = false;
    }

    if (currentName.indexOf(".ini") != (currentName.length() - 4))
    {
        currentName += ".ini";
    }

    if (isNewSetting == true)
    {
        ui->cbSetting->addItem(currentName);
    }

    DeltaImageProcesser->SaveSetting(currentName);
    ui->cameraWidget->SaveSetting(currentName);
}

void RobotWindow::LoadSetting()
{
    QString settingFileName = ui->cbSetting->currentText();
    QString filePath = QDir::currentPath() + "/" + settingFileName;
    if (!QFileInfo::exists(filePath))
        return;

    DeltaImageProcesser->LoadSetting(settingFileName);
    ui->cameraWidget->LoadSetting(settingFileName);
}

void RobotWindow::ExpandLogBox(bool value)
{
    if (value == true)
    {

    }
}

void RobotWindow::hideExampleWidgets()
{
    ui->frExProgram->setVisible(false);
}

void RobotWindow::updateEncoderUI()
{
    QPointF offset = Encoder1->GetOffset();

    plugValue(ui->leConveyorPoint3X, offset.x());
    plugValue(ui->leConveyorPoint3Y, offset.y());

    if (ui->cbMoveOnConveyor1->isChecked() == true)
    {
        plugValue(ui->leRealityPoint2X, offset.x());
        plugValue(ui->leRealityPoint2Y, offset.x());

        plugValue(ui->leRealityPoint1X, offset.x());
        plugValue(ui->leRealityPoint1Y, offset.x());
    }

    ui->leEncoderVelocity->setText(QString::number(Encoder1->GetVelocity()));
    ui->leEncoderPosition->setText(QString::number(Encoder1->GetPosition()));

}

void RobotWindow::interpolateCircle()
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

void RobotWindow::makeEffectExample()
{
	QCursor cursorTarget = QCursor(QPixmap("icon/Zoom In_16px.png"));
    ui->lbDrawingArea->setCursor(cursorTarget);
}

void RobotWindow::sendGcode(QString prefix, QString para1, QString para2)
{
    if (para1 != "")
        prefix += " ";
    if (para2 != "")
        para1 += " ";

    DeltaConnectionManager->SendToRobot(prefix + para1 + para2);
}

QObject* RobotWindow::getObjectByName(QObject* parent, QString name)
{
    QObjectList objList = parent->children();

    Q_FOREACH(QObject* obj, objList)
    {
        if (obj->objectName() == name)
            return obj;
    }

    return NULL;
}

void RobotWindow::initInputValueLabels()
{
    lbInputValues = new QList<QLabel*>();

    lbInputValues->append(ui->lbI0Value);
    lbInputValues->append(ui->lbI1Value);
    lbInputValues->append(ui->lbI2Value);
    lbInputValues->append(ui->lbI3Value);
    lbInputValues->append(ui->lbI4Value);
    lbInputValues->append(ui->lbI5Value);
    lbInputValues->append(ui->lbIxValue);

    lbInputValues->append(ui->lbA0Value);
    lbInputValues->append(ui->lbA1Value);
    lbInputValues->append(ui->lbAxValue);
}

void RobotWindow::plugValue(QLineEdit *le, float value)
{
    le->setText(QString::number(le->text().toFloat() + value));
}

void RobotWindow::OpenLoadingPopup()
{    
    lbLoadingPopup->show();
    mvLoadingPopup->start();
}

void RobotWindow::CloseLoadingPopup()
{
    lbLoadingPopup->hide();
    mvLoadingPopup->stop();
}

#ifdef Q_OS_WIN
    #ifdef JOY_STICK

void RobotWindow::ProcessJoystickButton(const QJoystickButtonEvent& event)
{
    Debug(QString::number(event.button) + ": " + ((event.pressed == true)?"1":"0") + "\n");

    if (event.pressed == true)
    {
        int index = ui->cbDivision->currentIndex();

        switch (event.button)
        {
            case 0:
                ui->cbD0->click();
                break;
            case 1:
                ui->cbDx->click();
                break;
            case 4:
                ui->pbHome->click();
                break;
            case 6:
                ui->pbUp->click();
                break;

            case 7:
                index++;
                if (index == ui->cbDivision->count())
                    index = 0;
                ui->cbDivision->setCurrentIndex(index);
                break;

            case 8:
                ui->pbDown->click();
                break;

            case 9:
                index = ui->cbDivision->currentIndex();
                index--;
                if (index < 0)
                        index = ui->cbDivision->count();
                ui->cbDivision->setCurrentIndex(index);
                break;
            case 10:
//                AddGcodeLine();
                break;
        }
    }
}

void RobotWindow::ProcessJoystickAxis(const QJoystickAxisEvent &event)
{
    Debug(QString::number(event.axis) + ": " + QString::number(event.value) + "\n");

    switch(event.axis)
    {
        case 0:
            Delta2DVisualizer->JumpOneStep(&Delta2DVisualizer->X, event.value);
            break;
        case 1:
            Delta2DVisualizer->JumpOneStep(&Delta2DVisualizer->Y, -event.value);
            break;
        case 2:
            break;
        case 3:
            Delta2DVisualizer->JumpOneStep(&Delta2DVisualizer->Z, -event.value);
            break;
    }

}

void RobotWindow::ProcessJoystickPOV(const QJoystickPOVEvent &event)
{
    Debug(QString::number(event.pov) + ": " + QString::number(event.angle) + "\n");

    switch (event.angle)
    {
        case 0:
            ui->pbForward->click();
            break;
        case 90:
            ui->pbRight->click();
            break;
        case 180:
            ui->pbBackward->click();
            break;
        case 270:
            ui->pbLeft->click();
            break;
    }
}
    #endif
#endif

void RobotWindow::MaximizeTab(int index)
{
    QTabWidget* selectedTabWidget = qobject_cast<QTabWidget*>(sender());

    bool isFull = false;

    if (FullDisplayLayout->count() > 0)
    {
        isFull = true;
    }

    if (isFull == false)
    {
        FullDisplayLayout->addWidget(selectedTabWidget);
        MainWindowStackedWidget->setCurrentWidget(FullDisplayPage);
    }
    else
    {
        if (selectedTabWidget == ui->twDeltaGeometry)
        {
            ui->GeometryTabManagerLayout->addWidget(selectedTabWidget);
        }
        if (selectedTabWidget == ui->twModule)
        {
            ui->ModuleTabManagerLayout->addWidget(selectedTabWidget);
        }

        MainWindowStackedWidget->setCurrentWidget(MainWindowPage);
    }
}

void RobotWindow::OpenCameraWindow()
{
    if (ImageViewerWindow == NULL)
    {
        ImageViewerWindow = new QWidget();
    }
    ui->fImageViewer->setParent(ImageViewerWindow);
    ImageViewerWindow->show();
}

void RobotWindow::ProcessUIEvent()
{
    if (ImageViewerWindow != NULL && ImageViewerWindow->isHidden() && ui->fImageViewer->parent() == ImageViewerWindow)
    {
        ui->vlImageViewer->addWidget(ui->fImageViewer);
    }
}

void RobotWindow::UseCameraFromPlugin(bool checked)
{
    if (checked == true)
    {
        DeltaImageProcesser->ProcessingImageTimer->stop();

        DeltaImageProcesser->UpdateRatios();
    }
    else
    {
        DeltaImageProcesser->ProcessingImageTimer->start();
    }
}

QStringList RobotWindow::getPlugins(QString path)
{
    QStringList filter;
    filter << "*.dll" << "*.so" << "*.dylib";
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filter);
    QStringList plugins;

    foreach (QFileInfo file, list) {
        plugins.append(file.filePath());
        //Mac - if(!file.isSymLink()) plugins.append(file.filePath());
    }

    return plugins;
}

void RobotWindow::initPlugins(QStringList plugins)
{
    foreach (QString file,plugins)
    {
        //qInfo() << "Loading: " << file;

        QPluginLoader loader(file);
        if(!loader.load())
        {
            QString msg = "";
            msg += "Error: " +  loader.fileName() + " Error: " + loader.errorString();
            Debug(msg);
            continue;
        }

        qInfo() << "Loaded: " << loader.fileName();

        DeltaXPlugin* pluginWidget = qobject_cast<DeltaXPlugin*>(loader.instance());

        if(pluginWidget)
        {
            ui->twModule->addTab(pluginWidget->GetUI(), pluginWidget->GetTitle());

            pluginList->append(pluginWidget);

            if (pluginWidget->GetTitle() == "3D Printing")
            {
                pluginWidget->ProcessCommand("-23");
                connect(pluginWidget, SIGNAL(EmitCommand(QString)), this, SLOT(PrintReceiveData(QString)));
            }
            else
            {
            // general init
                qRegisterMetaType< cv::Mat >("cv::Mat");
                connect(pluginWidget, SIGNAL(CapturedImage(cv::Mat)), this, SLOT(GetImageFromExternal(cv::Mat)));
                connect(pluginWidget, SIGNAL(StartedCapture()), Encoder1, SLOT(MarkPosition(cv::Mat)));
            }
        }
        else
        {
            qInfo() << "load fail";
        }
    }
}

QList<DeltaXPlugin*> *RobotWindow::getPluginList()
{
    return pluginList;
}

