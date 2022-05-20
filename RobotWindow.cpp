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
//    delete DeltaImageProcesser;
    lbLoadingPopup->thread()->quit();
    lbLoadingPopup->thread()->wait();

    GcodeScriptThread->thread()->quit();
    GcodeScriptThread->thread()->wait();

    DeltaConnectionManager->thread()->quit();
    DeltaConnectionManager->thread()->wait();

    ImageProcessingThread->thread()->quit();
}

void RobotWindow::InitVariables()
{
    //---------- Connection -----------
    InitConnectionModule();

    //--------- Init Dialog -------------
    CloseDialog = new SmartDialog(this);
    CloseDialog->SetType(CloseDialog->CLOSE_DIALOG);

    //--------- Init Plugin ----------
    LoadPlugin();

    // ---- Init UI ----
    ui->lbBaudrate->setText(QString::number(DeltaConnectionManager->GetBaudrate()));
    ui->lbIP->setText(DeltaConnectionManager->TCPConnection->GetIP());
    ui->lbLocalPort->setText(QString::number(DeltaConnectionManager->TCPConnection->Port));
    ui->mbRobot->setVisible(false);

//    QDir directory(QDir::currentPath());
//    ui->cbSetting->clear();
//    QStringList iniFiles = directory.entryList(QStringList() << "*.ini" << "*.INI",QDir::Files);
//    foreach(QString filename, iniFiles)
//    {
//        ui->cbSetting->addItem(filename);
//    }

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

    InitGcodeEditorModule();



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

    // --------- UI Update -------

    InitUIController();

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

//    DeltaImageProcesser = new ObjectDetector(this);
//    DeltaImageProcesser->SetResultScreenPointer(ui->cameraWidget);
//    DeltaImageProcesser->SetObjectScreenPointer(ui->lbTrackingObject);
//    DeltaImageProcesser->SetCameraInfoWidget(ui->leFPS, ui->lbCameraState, ui->pbPlayPauseCamera, ui->pbLoadCamera);
//    DeltaImageProcesser->SetObjectSizePointer(ui->leWRec, ui->leLRec, ui->leHRec);
//    DeltaImageProcesser->SetObjectErrorPointer(ui->leObjectErrorSize, ui->leTrackingError);
//    DeltaImageProcesser->SetCalibLinePointer(ui->leRealDistance, ui->leImageDistance);
//    DeltaImageProcesser->SetScaleRoateEnablePointer(ui->cbScaleRotateTool);
//    DeltaImageProcesser->SetRealityCalibPointPointer(ui->leRealityPoint1X, ui->leRealityPoint1Y, ui->leRealityPoint2X, ui->leRealityPoint2Y);
//    DeltaImageProcesser->SetImageCalibPointPointer(ui->leImagePoint1X, ui->leImagePoint1Y, ui->leImagePoint2X, ui->leImagePoint2Y);
//    DeltaImageProcesser->SetTrackingWidgetPointer(ui->lbTrackingObjectNumber, ui->lbVisibleObjectNumber);
//    DeltaImageProcesser->CameraScrollArea = ui->saCamera;
//    DeltaImageProcesser->SetResolutionWidget(ui->leCameraWidth, ui->leCameraHeight);
//    DeltaImageProcesser->SetDisplayInfoWidget(ui->lbDisplayRatio, ui->lbMatSize);
//    DeltaImageProcesser->SetXAngleWidget(ui->leXAxisAngle);
////    DeltaImageProcesser->SetObjectFilterWidget(ui->rbBlobFilter, ui->rbExternalFilter, ui->rbCircleFilter);
//    DeltaImageProcesser->SetFilterParaWidget(ui->lePythonUrl);
//    DeltaImageProcesser->cbExternalCamera = ui->cbExternalImageSource;
//    DeltaImageProcesser->cbImageSourceForExternal = ui->cbImageSource;
//    DeltaImageProcesser->Encoder1 = Encoder1;

//    DeltaImageProcesser->SetChessboardWidget(ui->leChessWidth, ui->leChessHeight, ui->leChessRealSize, leChessPoints);



    TrackingObjectTable = new ObjectVariableTable(this);

    ui->gbCameraCalibration->setChecked(false);
    ui->gbCameraObject->setChecked(false);
    ui->gbCameraVariable->setChecked(false);
    ui->gbConveyorForTracking->setChecked(false);

    //------- New image processing thread --------

    InitObjectDetectingModule();

    InitCalibration();

    //----------------ROS-------------------
#ifdef Q_OS_WIN
//    DeltaXROS = new ROS(this, ui->frameROS, "/ros/Delta X Ros.exe");
//	DeltaXROS->SetConnectionManager(DeltaConnectionManager->TCPConnection);
    //DeltaXROS->Run();
#endif
    //---------------Socket------------------------


    //------------ UI ----------------
    Delta2DVisualizer->ChangeXY(0, 0);

//    ui->twDeltaGeometry->setTabVisible(0, false);
//    ui->twModule->setTabVisible(2, false);
//    ui->gbRelay->setVisible(false);
//    ui->gbGripper->setVisible(false);

    SelectImageProviderOption(0);

    //------------------- Linux -----------------


    //------------ Robot --------

    //----- Process ------
    ExternalScriptProcess = new QProcess(this);
}

void RobotWindow::InitConnectionModule()
{
    DeltaConnectionManager = new ConnectionManager();
    DeltaConnectionManager->moveToThread(new QThread(this));

    DeltaConnectionManager->thread()->start();

    DeltaConnectionManager->SetBaudrate(DefaultBaudrate);


    connect(this, &RobotWindow::Send, DeltaConnectionManager, &ConnectionManager::Send);
    connect(this, &RobotWindow::ScanAndConnectRobot, DeltaConnectionManager, &ConnectionManager::FindDeltaRobot);
    connect(this, &RobotWindow::DisconnectRobot, DeltaConnectionManager, &ConnectionManager::DisconnectRobot);
    connect(DeltaConnectionManager->thread(), SIGNAL(finished()), DeltaConnectionManager, SLOT(deleteLater()));

    connect(DeltaConnectionManager, SIGNAL(Log(QString)), this, SLOT(Log(QString)));

    connect(DeltaConnectionManager, SIGNAL(ReceiveInputIO(QString)), this, SLOT(GetValueInput(QString)));

    connect(DeltaConnectionManager, SIGNAL(DeltaResponeReady()), this, SLOT(NoticeConnected()));
    connect(DeltaConnectionManager, SIGNAL(InHomePosition(float, float, float, float, float, float)), this, SLOT(ReceiveHomePosition(float, float, float, float, float, float)));

    connect(DeltaConnectionManager, SIGNAL(RequestVariableValue(QIODevice*, QString)), this, SLOT(RespondVariableValue(QIODevice*, QString)));

    connect(DeltaConnectionManager, SIGNAL(ReceiveRequestsFromExternal(QString)), this, SLOT(ExecuteRequestsFromExternal(QString)));


    connect(DeltaConnectionManager, SIGNAL(ReceiveObjectInfoFromExternalAI(QString)), this, SLOT(ProcessDetectedObjectFromExternalAI(QString)));
//    connect(DeltaConnectionManager, SIGNAL(ExternalScriptOpened(QTcpSocket*)), DeltaImageProcesser, SLOT(GetExternalScriptSocket(QTcpSocket*)));
    connect(DeltaConnectionManager, SIGNAL(ReceiveDisplayObjectFromExternalScript(QString)), this, SLOT(AddDisplayObjectFromExternalScript(QString)));

    connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceivePosition(float, float, float, float, float, float)), this, SLOT(UpdateTextboxFrom3DControl(float, float, float, float, float, float)));

    connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceiveOk()), this, SLOT(ROSResponse()));

    connect(DeltaConnectionManager, SIGNAL(FinishFindingRobot()), this, SLOT(CloseLoadingPopup()));

    connect(DeltaConnectionManager, SIGNAL(ReceivedEncoderPosition(float)), this, SLOT(ProcessEncoderValue(float)));

    Encoder1 = new Encoder();
    Encoder2 = new Encoder();

    connect(DeltaConnectionManager, SIGNAL(ReceiveCaptureSignalFromExternalAI()), Encoder1, SLOT(MarkPosition()));
}

void RobotWindow::InitObjectDetectingModule()
{
    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< cv::Size >("cv::Size");
    qRegisterMetaType< Object >("Object");
    qRegisterMetaType< QList<Object*>* >("QList<Object*>*");
    qRegisterMetaType< QList<int> >("QList<int>");

    // ---------- Image Processing Thread ---------

    ImageProcessingThread = new ImageProcessing();
    ImageProcessingThread->MoveToThread(new QThread(this));

    // --------- Init Task Node --------

    ImageProcessingThread->CreatTaskNode("GetImageNode", TaskNode::GET_IMAGE_NODE);
    ImageProcessingThread->CreatTaskNode("ResizeImageNode", TaskNode::RESIZE_IMAGE_NODE, "GetImageNode");
    ImageProcessingThread->CreatTaskNode("FindChessboardNode", TaskNode::FIND_CHESSBOARD_NODE);
    ImageProcessingThread->CreatTaskNode("GetPerspectiveNode", TaskNode::GET_PERSPECTIVE_NODE, "FindChessboardNode");
    ImageProcessingThread->CreatTaskNode("WarpImageNode", TaskNode::WARP_IMAGE_NODE, "ResizeImageNode|GetPerspectiveNode");
    ImageProcessingThread->CreatTaskNode("CropImageNode", TaskNode::CROP_IMAGE_NODE, "ResizeImageNode");

    ImageProcessingThread->CreatTaskNode("MappingMatrixNode", TaskNode::MAPPING_MATRIX_NODE);
    ImageProcessingThread->CreatTaskNode("ColorFilterNode", TaskNode::COLOR_FILTER_NODE, "CropImageNode");
    ImageProcessingThread->CreatTaskNode("GetObjectsNode", TaskNode::GET_OBJECTS_NODE, "ColorFilterNode");
    ImageProcessingThread->CreatTaskNode("VisibleObjectsNode", TaskNode::VISIBLE_OBJECTS_NODE, "GetObjectsNode|MappingMatrixNode");
    ImageProcessingThread->CreatTaskNode("TrackingObjectsNode", TaskNode::TRACKING_OBJECTS_NODE, "VisibleObjectsNode");

    ImageProcessingThread->CreatTaskNode("DisplayImageNode", TaskNode::DISPLAY_IMAGE_NODE, "CropImageNode");

    // ---------- Blob Filter Window---------
    ParameterPanel = new FilterWindow(this);

    // ---------- Main UI -------
    connect(ui->cbImageOutput, SIGNAL(currentTextChanged(QString)), this, SLOT(ChangeOutputDisplay()));
    connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), this, SLOT(LoadWebcam()));
    connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), this, SLOT(LoadImage()));
    connect(ui->cbDetectingAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectObjectDetectingAlgorithm(int)));

    ui->cbDetectingAlgorithm->setCurrentIndex(0);
    SelectObjectDetectingAlgorithm(0);

    connect(&WebcamTimer, SIGNAL(timeout()), this, SLOT(CaptureWebcam()));

    ui->gvImageViewer->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

    connect(ui->pbCalibPointTool, &QPushButton::clicked, [=](bool checked)
    {
        if (checked == true)
        {
            UnselectToolButtons();
            ui->pbCalibPointTool->setChecked(true);
            ui->gvImageViewer->SelectPointTool();
        }
        else
        {
            ui->gvImageViewer->SelectNoTool();
        }

    });
    connect(ui->pbGetSizeTool, &QPushButton::clicked,  [=](bool checked)
    {
        if (checked == true)
        {
            UnselectToolButtons();
            ui->pbGetSizeTool->setChecked(true);
            ui->gvImageViewer->SelectRectTool();
        }
        else
        {
            ui->gvImageViewer->SelectNoTool();
        }

    });
    connect(ui->pbFindChessboardTool, &QPushButton::clicked,  [=](bool checked)
    {
        if (checked == true)
        {
            UnselectToolButtons();
            ui->pbFindChessboardTool->setChecked(true);
            ConfigChessboard();
        }
        else
        {
            ui->gvImageViewer->SelectNoTool();
        }

    });
    connect(ui->pbAreaTool, &QPushButton::clicked, [=](bool checked)
    {
        EditImage(ui->pbWarpTool->isChecked(), checked);

    });
    connect(ui->pbMappingPointTool, &QPushButton::clicked, [=](bool checked)
    {
        if (checked == true)
        {
            UnselectToolButtons();
            ui->pbMappingPointTool->setChecked(true);
            ui->gvImageViewer->SelectMappingTool();
        }
        else
        {
            ui->gvImageViewer->SelectNoTool();
        }

    });

    connect(ui->pbWarpTool, &QPushButton::clicked, [=](bool checked)
    {
        EditImage(checked, ui->pbAreaTool->isChecked());
    });

    connect(ui->pbFilterTool, SIGNAL(clicked(bool)), this, SLOT(OpenColorFilterWindow()));
    connect(ui->pbViewDataObjects, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
    connect(ui->pbClearObject, &QPushButton::clicked, [=](bool checked)
    {
        ImageProcessingThread->GetNode("TrackingObjectsNode")->ClearVariable("outputObjects");
    });
    connect(ui->pbOpenObjectTable, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
    connect(TrackingObjectTable, SIGNAL(TakeObjectPosition(float, float, float)), this, SLOT(MoveRobotFollowObject(float, float, float)));

    connect(ui->gvImageViewer, &ImageViewer::selectedNoTool, this, &RobotWindow::UnselectToolButtons);

    connect(ui->gvImageViewer, &ImageViewer::changedPoints, this, &RobotWindow::GetCalibPointsFromImage);
    connect(ui->gvImageViewer, &ImageViewer::changedRect, this, &RobotWindow::GetObjectSizeFromImage);
    connect(ui->gvImageViewer, &ImageViewer::changedMappingPoint, this, &RobotWindow::GetMappingPointFromImage);

    connect(ui->leRealityPoint1X, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint1Y, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint2X, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint2Y, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);

    connect(ui->leTrackingError, &QLineEdit::returnPressed,
    [=] (){
        ImageProcessingThread->GetNode("TrackingObjectsNode")->Input(ui->leTrackingError->text().toFloat());
    });

    // ---------- Image Provider -------
    Camera = new cv::VideoCapture();

    connect(ImageProcessingThread->thread(), SIGNAL(finished()), ImageProcessingThread, SLOT(deleteLater()));

    connect(this, SIGNAL(GotImage(cv::Mat)), ImageProcessingThread->GetNode("GetImageNode"), SLOT(Input(cv::Mat)));
    connect(this, SIGNAL(GotResizePara(cv::Size)), ImageProcessingThread->GetNode("ResizeImageNode"), SLOT(Input(cv::Size)));
    connect(ImageProcessingThread->GetNode("FindChessboardNode"), SIGNAL(HadOutput(QPolygonF)), ui->gvImageViewer, SLOT(SetQuadrangle(QPolygonF)));
    connect(this, SIGNAL(GotChessboardSize(cv::Size)), ImageProcessingThread->GetNode("FindChessboardNode"), SLOT(Input(cv::Size)));
    connect(this, SIGNAL(GotResizeImage(cv::Mat)), ImageProcessingThread->GetNode("FindChessboardNode"), SLOT(Input(cv::Mat)));
    connect(this, SIGNAL(GotCalibPoints(QPolygonF)), ImageProcessingThread->GetNode("MappingMatrixNode"), SLOT(Input(QPolygonF)));

    connect(ui->gvImageViewer, SIGNAL(changedQuadrangle(QPolygonF)), ImageProcessingThread->GetNode("GetPerspectiveNode"), SLOT(Input(QPolygonF)));

    connect(ui->gvImageViewer, SIGNAL(changedArea(QRectF)), ImageProcessingThread->GetNode("CropImageNode"), SLOT(Input(QRectF)));
    connect(ImageProcessingThread->GetNode("CropImageNode"), SIGNAL(HadOutput(cv::Mat)), this, SLOT(SendImageToExternalScript(cv::Mat)));
//    connect(ImageProcessingThread->GetNode("ColorFilterNode"), SIGNAL(HadOutput(cv::Mat)), this, SLOT(SendImageToExternalScript(cv::Mat)));

    connect(ui->leImageWidth, &QLineEdit::returnPressed,
    [=] (){
        int newW = ui->leImageWidth->text().toInt();

        QSize imageSize = ImageProcessingThread->GetNode("GetImageNode")->GetImageSize();

        int newH = ImageTool::Map(newW, imageSize.width(), imageSize.height());

        ui->leImageHeight->setText(QString::number(newH));

        emit GotResizePara(cv::Size(newW, newH));
    });
    connect(ui->leImageHeight, &QLineEdit::returnPressed,
    [=] (){
        int newH = ui->leImageHeight->text().toInt();

        QSize imageSize = ImageProcessingThread->GetNode("GetImageNode")->GetImageSize();

        int newW = ImageTool::Map(newH, imageSize.height(), imageSize.width());

        ui->leImageWidth->setText(QString::number(newW));

        emit GotResizePara(cv::Size(newW, newH));
    });

    connect(ImageProcessingThread->GetNode("DisplayImageNode"), SIGNAL(HadOutput(QPixmap)), ui->gvImageViewer, SLOT(SetImage(QPixmap)));

    connect(ParameterPanel, SIGNAL(ColorFilterValueChanged(QList<int>)), ImageProcessingThread->GetNode("ColorFilterNode"), SLOT(Input(QList<int>)));
    connect(ParameterPanel, SIGNAL(BlurSizeChanged(int)), ImageProcessingThread->GetNode("ColorFilterNode"), SLOT(Input(int)));
    connect(ParameterPanel, SIGNAL(ColorInverted(bool)), ImageProcessingThread->GetNode("ColorFilterNode"), SLOT(Input(bool)));

    connect(this, SIGNAL(GotObjects(QList<Object*>*)), ImageProcessingThread->GetNode("VisibleObjectsNode"), SLOT(Input(QList<Object*>*)));
    connect(this, SIGNAL(GotMappingMatrix(QMatrix)), ImageProcessingThread->GetNode("VisibleObjectsNode"), SLOT(Input(QMatrix)));
    connect(this, SIGNAL(GotOjectFilterInfo(Object)), ImageProcessingThread->GetNode("GetObjectsNode"), SLOT(Input(Object)));
    connect(ImageProcessingThread->GetNode("VisibleObjectsNode"), SIGNAL(HadOutput(QList<Object*>*)), this, SLOT(UpdateObjectsToImageViewer(QList<Object*>*)));
    connect(ImageProcessingThread->GetNode("VisibleObjectsNode"), &TaskNode::DebugEvent, [=] () { qDebug() << "End: " << Encoder1->GetMeasuredDistance();});

    connect(Encoder1, SIGNAL(DistanceMoved(QPointF)), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(Input(QPointF)));

    connect(ImageProcessingThread->GetNode("TrackingObjectsNode"), SIGNAL(HadOutput(QList<Object*>*)), TrackingObjectTable, SLOT(UpdateTable(QList<Object*>*)));
    connect(ImageProcessingThread->GetNode("TrackingObjectsNode"), SIGNAL(HadOutput(QList<Object*>*)), this, SLOT(UpdateObjectsToVariableTable(QList<Object*>*)));
    connect(this, SIGNAL(RequestClearObjects()), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(ClearOutput()));
    connect(this, SIGNAL(RequestDeleteObject(int)), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(DeleteOutput(int)));

    RearrangeTaskFlow();

    ImageProcessingThread->thread()->start();

    // ----------- init para ----------
    emit GotResizePara(cv::Size(ui->leImageWidth->text().toInt(), ui->leImageHeight->text().toInt()));
    Encoder1->OffsetPoint = ImageProcessingThread->GetNode("VisibleObjectsNode")->GetInputPointPointer();
    UpdateRealPositionOfCalibPoints();// ---------
}

void RobotWindow::InitGcodeEditorModule()
{

//    UpdateVariable("X", "0");
//    UpdateVariable("Y", "0");
//    UpdateVariable("Z", "0");
//    UpdateVariable("W", "0");
//    UpdateVariable("U", "0");
//    UpdateVariable("V", "0");
//    UpdateVariable("F", "200");
//    UpdateVariable("A", "1200");
//    UpdateVariable("S", "12");
//    UpdateVariable("E", "12");
//    UpdateVariable("ConveyorSpeed", "0");
//    UpdateVariable("ConveyorDirection", "0");

//    UpdateVariable("O0_X", QString::number(NULL_NUMBER));
//    UpdateVariable("O0_Y", QString::number(NULL_NUMBER));
//    UpdateVariable("O0_A", QString::number(NULL_NUMBER));
//    UpdateVariable("O0_W", QString::number(NULL_NUMBER));
//    UpdateVariable("O0_L", QString::number(NULL_NUMBER));

    GcodeScriptThread = new GcodeScript();
    GcodeScriptThread->GcodeVariables = SoftwareManager::GetInstance()->ProgramVariableManager->GetMap();
    GcodeScriptThread->VariableAddress = ProjectName + "." + Name;
    GcodeScriptThread->ProgramList = DeltaGcodeManager->ProgramList;
    GcodeScriptThread->moveToThread(new QThread(this));

    connect(GcodeScriptThread->thread(), SIGNAL(finished()), GcodeScriptThread, SLOT(deleteLater()));
    connect(this, SIGNAL(StopGcodeProgram()), GcodeScriptThread, SLOT(Stop()));
    connect(this, SIGNAL(RunGcodeProgram(QString, int, bool)), GcodeScriptThread, SLOT(ExecuteGcode(QString, int, bool)));
    connect(DeltaConnectionManager, SIGNAL(GcodeDone()), GcodeScriptThread, SLOT(TransmitNextGcode()));
    connect(DeltaConnectionManager, SIGNAL(FailTransmit()), GcodeScriptThread, SLOT(TransmitNextGcode()));

    connect(GcodeScriptThread, SIGNAL(Moved(int)), this, SLOT(HighLineCurrentLine(int)));
    connect(GcodeScriptThread, &GcodeScript::SendGcodeToDevice, DeltaConnectionManager, &ConnectionManager::SendGcode);
    connect(GcodeScriptThread, &GcodeScript::Finished, [=](){ ui->pbExecuteGcodes->setChecked(false);});
    connect(GcodeScriptThread, SIGNAL(SendGcodeToDevice(QString, QString)), this, SLOT(UpdateGcodeValueToDeviceUI(QString, QString)));
    connect(GcodeScriptThread, SIGNAL(SaveVariable(QString, QString)), this, SLOT(UpdateVariable(QString, QString)));

    GcodeScriptThread->thread()->start();

    DeltaGcodeManager = new GcodeProgramManager(this, ui->saProgramFiles, ui->wgProgramContainer, ui->pteGcodeArea, ui->pbExecuteGcodes, DeltaConnectionManager, Delta2DVisualizer);
    DeltaGcodeManager->leGcodeProgramPath = ui->leGcodeProgramPath;
    DeltaGcodeManager->LoadPrograms();

    connect(DeltaConnectionManager, SIGNAL(ReceiveVariableChangeCommand(QString, QString)), DeltaGcodeManager, SLOT(UpdateSystemVariable(QString, QString)));
    connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceiveVariableChangeCommand(QString, float)), DeltaGcodeManager, SLOT(UpdateSystemVariable(QString, float)));
}

void RobotWindow::InitUIController()
{
    connect(&UpdateUITimer, &QTimer::timeout, this, &RobotWindow::UpdateRobotPositionToUI);
    UpdateUITimer.start(100);

    connect(ui->pbHome, &QPushButton::clicked, this, [=](){emit Send(ConnectionManager::ROBOT, "G28");});

    connect(ui->leX, &QLineEdit::returnPressed, this, [=](){RobotParameter.X = ui->leX->text().toFloat(); emit Send(ConnectionManager::ROBOT, QString("G01 X") + ui->leX->text());});
    connect(ui->leY, &QLineEdit::returnPressed, this, [=](){RobotParameter.Y = ui->leY->text().toFloat(); emit Send(ConnectionManager::ROBOT, QString("G01 Y") + ui->leY->text());});
    connect(ui->leZ, &QLineEdit::returnPressed, this, [=](){RobotParameter.Z = ui->leZ->text().toFloat(); emit Send(ConnectionManager::ROBOT, QString("G01 Z") + ui->leZ->text());});
    connect(ui->leW, &QLineEdit::returnPressed, this, [=](){RobotParameter.W = ui->leW->text().toFloat(); emit Send(ConnectionManager::ROBOT, QString("G01 W") + ui->leW->text());});
    connect(ui->leU, &QLineEdit::returnPressed, this, [=](){RobotParameter.U = ui->leU->text().toFloat(); emit Send(ConnectionManager::ROBOT, QString("G01 U") + ui->leU->text());});
    connect(ui->leV, &QLineEdit::returnPressed, this, [=](){RobotParameter.V = ui->leV->text().toFloat(); emit Send(ConnectionManager::ROBOT, QString("G01 V") + ui->leV->text());});

    connect(ui->vsZAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.Z = RobotParameter.ZHome - value;});
    connect(ui->vsZAdjsution, &QSlider::sliderReleased, [=](){emit Send(ConnectionManager::ROBOT, QString("G01 Z%1").arg(RobotParameter.Z));});
    connect(ui->vsAngleAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.W = value;});
    connect(ui->vsAngleAdjsution, &QSlider::sliderReleased, [=](){emit Send(ConnectionManager::ROBOT, QString("G01 W%1").arg(RobotParameter.W));});
    connect(ui->vs5AxisAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.U = value;});
    connect(ui->vs5AxisAdjsution, &QSlider::sliderReleased, [=](){emit Send(ConnectionManager::ROBOT, QString("G01 U%1").arg(RobotParameter.U));});
    connect(ui->vs6AxisAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.V = value;});
    connect(ui->vs6AxisAdjsution, &QSlider::sliderReleased, [=](){emit Send(ConnectionManager::ROBOT, QString("G01 V%1").arg(RobotParameter.V));});

    connect(Delta2DVisualizer, &DeltaVisualizer::CursorMoved, [=](float x, float y){RobotParameter.X = x; RobotParameter.Y = y; emit Send(ConnectionManager::ROBOT, QString("G01 X%1 Y%2").arg(x).arg(y));});

    connect(ui->pbUp, &QPushButton::clicked, [=](){MoveRobot("Z", ui->cbDivision->currentText().toFloat());});
    connect(ui->pbDown, &QPushButton::clicked, [=](){MoveRobot("Z", 0 - ui->cbDivision->currentText().toFloat());});
    connect(ui->pbForward, &QPushButton::clicked, [=](){MoveRobot("Y", ui->cbDivision->currentText().toFloat());});
    connect(ui->pbBackward, &QPushButton::clicked, [=](){MoveRobot("Y", 0 - ui->cbDivision->currentText().toFloat());});
    connect(ui->pbLeft, &QPushButton::clicked, [=](){MoveRobot("X", 0 - ui->cbDivision->currentText().toFloat());});
    connect(ui->pbRight, &QPushButton::clicked, [=](){MoveRobot("X", ui->cbDivision->currentText().toFloat());});
    connect(ui->leVelocity, &QLineEdit::returnPressed, [=](){MoveRobot("F", ui->leVelocity->text().toFloat() - RobotParameter.F);});
    connect(ui->leAccel, &QLineEdit::returnPressed, [=](){MoveRobot("A", ui->leAccel->text().toFloat() - RobotParameter.A);});
    connect(ui->leStartSpeed, &QLineEdit::returnPressed, [=](){MoveRobot("S", ui->leStartSpeed->text().toFloat() - RobotParameter.S);});
    connect(ui->leEndSpeed, &QLineEdit::returnPressed, [=](){MoveRobot("E", ui->leEndSpeed->text().toFloat() - RobotParameter.E);});

    connect(ui->pbsubX, &QPushButton::clicked, [=](){emit ui->pbLeft->clicked(); ui->leX->setText(QString::number(RobotParameter.X));});
    connect(ui->pbsubY, &QPushButton::clicked, [=](){emit ui->pbBackward->clicked(); ui->leY->setText(QString::number(RobotParameter.Y));});
    connect(ui->pbsubZ, &QPushButton::clicked, [=](){emit ui->pbDown->clicked(); ui->leZ->setText(QString::number(RobotParameter.Z));});
    connect(ui->pbsubW, &QPushButton::clicked, [=](){MoveRobot("W", 0 - ui->cbDivision->currentText().toFloat()); ui->leW->setText(QString::number(RobotParameter.W));});
    connect(ui->pbsubU, &QPushButton::clicked, [=](){MoveRobot("U", 0 - ui->cbDivision->currentText().toFloat()); ui->leU->setText(QString::number(RobotParameter.U));});
    connect(ui->pbsubV, &QPushButton::clicked, [=](){MoveRobot("V", 0 - ui->cbDivision->currentText().toFloat()); ui->leV->setText(QString::number(RobotParameter.V));});

    connect(ui->pbplusX, &QPushButton::clicked, [=](){emit ui->pbRight->clicked(); ui->leX->setText(QString::number(RobotParameter.X));});
    connect(ui->pbplusY, &QPushButton::clicked, [=](){emit ui->pbForward->clicked(); ui->leY->setText(QString::number(RobotParameter.Y));});
    connect(ui->pbplusZ, &QPushButton::clicked, [=](){emit ui->pbUp->clicked(); ui->leZ->setText(QString::number(RobotParameter.Z));});
    connect(ui->pbplusW, &QPushButton::clicked, [=](){MoveRobot("W", ui->cbDivision->currentText().toFloat()); ui->leW->setText(QString::number(RobotParameter.W));});
    connect(ui->pbplusU, &QPushButton::clicked, [=](){MoveRobot("U", ui->cbDivision->currentText().toFloat()); ui->leU->setText(QString::number(RobotParameter.U));});
    connect(ui->pbplusV, &QPushButton::clicked, [=](){MoveRobot("V", ui->cbDivision->currentText().toFloat()); ui->leV->setText(QString::number(RobotParameter.V));});

}

void RobotWindow::InitCalibration()
{
    connect(ui->pbGetConveyorPoint1X, &QPushButton::clicked, [=](){ ui->leConveyorPoint1X->setText(QString::number(RobotParameter.X)); });
    connect(ui->pbGetConveyorPoint1Y, &QPushButton::clicked, [=](){ ui->leConveyorPoint1Y->setText(QString::number(RobotParameter.Y)); });
    connect(ui->pbGetConveyorPoint2X, &QPushButton::clicked, [=](){ ui->leConveyorPoint2X->setText(QString::number(RobotParameter.X)); });
    connect(ui->pbGetConveyorPoint2Y, &QPushButton::clicked, [=](){ ui->leConveyorPoint2Y->setText(QString::number(RobotParameter.Y)); });

    connect(ui->pbCalibPoint1, &QPushButton::clicked, [=](){ ui->leRealityPoint1X->setText(QString::number(RobotParameter.X)); ui->leRealityPoint1Y->setText(QString::number(RobotParameter.Y));});
    connect(ui->pbCalibPoint2, &QPushButton::clicked, [=](){ ui->leRealityPoint2X->setText(QString::number(RobotParameter.X)); ui->leRealityPoint2Y->setText(QString::number(RobotParameter.Y));});
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
//	connect(ui->pbHome, SIGNAL(clicked(bool)), this, SLOT(Home()));
//	connect(ui->pbW, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//	connect(ui->pbZ, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//	connect(ui->pbY, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//	connect(ui->pbX, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(ui->pbU, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(ui->pbV, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//	connect(ui->leW, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//	connect(ui->leZ, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//	connect(ui->leY, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//	connect(ui->leX, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(ui->leU, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(ui->leV, SIGNAL(returnPressed()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));

//    connect(ui->pbUp, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveUp()));
//    connect(ui->pbDown, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveDown()));
//    connect(ui->pbForward, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveForward()));
//    connect(ui->pbBackward, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveBackward()));
//    connect(ui->pbLeft, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveLeft()));
//    connect(ui->pbRight, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveRight()));
//    connect(ui->leVelocity, SIGNAL(returnPressed()), this, SLOT(UpdateVelocity()));
//    connect(ui->leAccel, SIGNAL(returnPressed()), this, SLOT(UpdateAccel()));
//    connect(ui->leStartSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateStartSpeed()));
//    connect(ui->leEndSpeed, SIGNAL(returnPressed()), this, SLOT(UpdateEndSpeed()));

//    connect(ui->pbsubX, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveLeft()));
//    connect(ui->pbsubY, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveBackward()));
//    connect(ui->pbsubZ, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveDown()));
//    connect(ui->pbsubW, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(SubW()));
//    connect(ui->pbsubU, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(SubU()));
//    connect(ui->pbsubV, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(SubV()));

//    connect(ui->pbplusX, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveRight()));
//    connect(ui->pbplusY, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveForward()));
//    connect(ui->pbplusZ, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(MoveUp()));
//    connect(ui->pbplusW, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(PlusW()));
//    connect(ui->pbplusU, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(PlusU()));
//    connect(ui->pbplusV, SIGNAL(clicked(bool)), Delta2DVisualizer, SLOT(PlusV()));

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
//	connect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZLineEditValue(int)));
//	connect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(ui->vsAngleAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateAngleLineEditValue(int)));
//	connect(ui->vsAngleAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(ui->vs5AxisAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateAngleLineEditValue(int)));
//    connect(ui->vs5AxisAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(ui->vs6AxisAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateAngleLineEditValue(int)));
//    connect(ui->vs6AxisAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
//    connect(Delta2DVisualizer, SIGNAL(Moved(float, float, float, float, float, float)), this, SLOT(UpdateTextboxFrom2DControl(float, float, float, float, float, float)));


//	connect(Delta2DVisualizer, SIGNAL(FinishMoving()), this, SLOT(UpdateDeltaPositionFromLineEditValue()));
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

    //------------- Gcode Editor -------------
	connect(ui->pbFormat, SIGNAL(clicked(bool)), this, SLOT(StandardFormatEditor()));
    connect(ui->cbLockGcodeEditor, SIGNAL(clicked(bool)), ui->pteGcodeArea, SLOT(setLockState(bool)));
    connect(ui->pbOpenGcodeProgramPath, SIGNAL(clicked(bool)), DeltaGcodeManager, SLOT(SelectGcodeProgramPath()));

    //------------ Image Processing -----------
//	connect(ui->pbFilter, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenParameterPanel()));
//    connect(ui->pbFilterTool, SIGNAL(clicked(bool)), this, SLOT(OpenColorFilterWindow()));
//	connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadTestImage()));
//    connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadCamera2()));
//    connect(ui->pbObjectRect, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectObjectTool()));
//    connect(ui->pbGetSizeTool, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectObjectTool()));
//    connect(ui->pbObjectLine, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectLineTool()));
//    connect(ui->pbCalibLineTool, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectLineTool()));
//    connect(ui->pbObjectOrigin, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectPointTool()));
//    connect(ui->pbCalibPointTool, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectPointTool()));
//	connect(ui->lbCameraLayer, SIGNAL(currentIndexChanged(int)), DeltaImageProcesser, SLOT(SelectLayer(int )));
//    connect(ui->pbRotateAxis90, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(changeAxisDirection()));
//    connect(ui->pbDirectionTool, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(changeAxisDirection()));
//	connect(ui->leFPS, SIGNAL(returnPressed()), DeltaImageProcesser, SLOT(SaveFPS()));
//    connect(ui->pbClearDetectObjects, SIGNAL(clicked(bool)), DeltaImageProcesser->ObjectManager1, SLOT(RemoveAllDetectObjects()));
//	connect(ui->pbViewDataObjects, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
//    connect(ui->pbClearObject, SIGNAL(clicked(bool)), DeltaImageProcesser->ObjectManager1, SLOT(RemoveAllDetectObjects()));
//    connect(ui->pbOpenObjectTable, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));

//    connect(DeltaImageProcesser, SIGNAL(ObjectValueChanged(std::vector<cv::RotatedRect>)), TrackingObjectTable, SLOT(UpdateTable(std::vector<cv::RotatedRect>)));
//	connect(DeltaImageProcesser, SIGNAL(ObjectValueChanged(std::vector<cv::RotatedRect>)), this, SLOT(AddObjectsToROS(std::vector<cv::RotatedRect>)));
//	connect(ui->pbTransformPerspective, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnTransformPerspective(bool)));
//    connect(ui->pbWarpTool, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnTransformPerspective(bool)));
//	connect(ui->cbDisplayCalibInfo, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(TurnCalibDisplay(bool)));
//	connect(ui->pbExpandCameraWidget, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(ExpandCameraWidget(bool)));
    connect(ui->pbCameraWindowMode, SIGNAL(clicked(bool)), this, SLOT(OpenCameraWindow()));
//    connect(ui->cameraWidget, SIGNAL(SizeChanged()), DeltaImageProcesser, SLOT(UpdateRatios()));

//    connect(ui->pbFindChessboard, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(FindChessboard()));

//    connect(ui->leTrackingError, &QLineEdit::returnPressed, DeltaImageProcesser->ObjectManager1, &ObjectManager::UpdateTrackingError);
//    connect(ui->leObjectErrorSize, &QLineEdit::returnPressed, DeltaImageProcesser, &ObjectDetector::GetObjectError);

    connect(ui->pbConnectEncdoer, SIGNAL(clicked(bool)), this, SLOT(ConnectEncoder()));
    connect(ui->pbCalibConveyorAngle, SIGNAL(clicked(bool)), this, SLOT(CalculateConveyorDeviationAngle()));
	connect(ui->leConvenyorSpeed, SIGNAL(returnPressed()), this, SLOT(SetConvenyorSpeed()));
//    connect(ui->cbConveyorDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConvenyorSpeed()));
    connect(ui->pbResetEncoderPosition, SIGNAL(clicked(bool)), this, SLOT(ResetEncoderPosition()));

    connect(ui->leMovingDistanceConveyorControl, SIGNAL(returnPressed()), this, SLOT(MoveExternalConveyor()));
    connect(ui->pbForwardConveyor, SIGNAL(clicked(bool)), this, SLOT(ForwardExternalConveyor()));
    connect(ui->pbBackwardConveyor, SIGNAL(clicked(bool)), this, SLOT(BackwardExternalConveyor()));
    connect(ui->pbTurnOffConveyor, SIGNAL(clicked(bool)), this, SLOT(TurnOffExternalConveyor()));

//    connect(ui->pbImageMapping, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(CalculateMappingMatrix()));
//    connect(ui->pbMapping, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(CalculateMappingMatrix()));
//    connect(ui->pbPointToolOnBar, SIGNAL(clicked(bool)), ui->cameraWidget, SLOT(SelectMappingTool()));
//    connect(ui->pbExternalScriptOpen, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenExternalFilterScript()));
    connect(ui->pbRunExternalScript, SIGNAL(clicked(bool)), this, SLOT(RunExternalScript()));

    connect(ui->cbExternalImageSource, SIGNAL(toggled(bool)), this, SLOT(UseCameraFromPlugin(bool)));

    connect(ui->cbSourceForImageProvider, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectImageProviderOption(int)));

    // ---- Setting ----
//    connect(ui->pbLoadCameraSetting, SIGNAL(clicked(bool)), this, SLOT(LoadSetting()));
//    connect(ui->pbSaveCameraSetting, SIGNAL(clicked(bool)), this, SLOT(SaveSetting()));

    //----------- Camera -----------
//    connect(ui->cameraWidget, SIGNAL(ObjectChanged(int, int, int, int)), DeltaImageProcesser, SLOT(GetObjectInfo(int, int, int, int)));
//    connect(ui->cameraWidget, SIGNAL(DistanceChanged(int)), DeltaImageProcesser, SLOT(GetDistance(int)));
//    connect(ui->cameraWidget, SIGNAL(QuadrangleChanged(QPoint, QPoint, QPoint, QPoint)), DeltaImageProcesser, SLOT(GetPerspectivePoints(QPoint, QPoint, QPoint, QPoint)));
//    connect(ui->cameraWidget, SIGNAL(AreaChanged(QRect)), DeltaImageProcesser, SLOT(GetProcessArea(QRect)));
//    connect(ui->cameraWidget, SIGNAL(LineChanged(QPoint, QPoint)), DeltaImageProcesser, SLOT(GetCalibLine(QPoint, QPoint)));
//    connect(ui->cameraWidget, SIGNAL(PointChanged(QPoint, QPoint)), DeltaImageProcesser, SLOT(GetCalibPoint(QPoint, QPoint)));
//    connect(ui->cameraWidget, SIGNAL(MappingPointChanged(QPoint)), DeltaImageProcesser, SLOT(GetMappingPoint(QPoint)));

	
//    connect(ui->leRealityPoint1X, SIGNAL(returnPressed()), ui->lbScreenStreamer, SLOT(ChangePoint()));
//    connect(ui->leRealityPoint1Y, SIGNAL(returnPressed()), ui->lbScreenStreamer, SLOT(ChangePoint()));
//    connect(ui->leRealDistance, SIGNAL(returnPressed()), ui->cameraWidget, SLOT(ChangeLine()));

//    connect(ui->cbCameraWidgetHeight, SIGNAL(currentIndexChanged(QString)), DeltaImageProcesser, SLOT(ChangeCameraWidgetHeight(QString)));

//    connect(ui->cameraWidget, SIGNAL(RequestUpdate()), DeltaImageProcesser, SLOT(UpdateToCameraWidget()));

    //---------- Menu -----------
	connect(ui->actionBaudrate, SIGNAL(triggered()), this, SLOT(ConfigConnection()));
	connect(ui->actionGcode, SIGNAL(triggered()), this, SLOT(OpenGcodeReference()));
	connect(ui->actionExecute_All, SIGNAL(triggered()), this, SLOT(ExecuteSelectPrograms()));
	connect(ui->actionExecute, SIGNAL(triggered()), this, SLOT(ExecuteProgram()));
    connect(ui->actionScale, SIGNAL(triggered(bool)), this, SLOT(ScaleUI()));

//    connect(DeltaGcodeManager, SIGNAL(OutOfObjectVariable()), DeltaImageProcesser->ObjectManager1, SLOT(RemoveOldestObject()));
//    connect(DeltaGcodeManager, SIGNAL(MoveToNewPosition(float, float, float, float, float, float, float, float, float, float)), this, SLOT(UpdatePositionControl(float, float, float, float, float, float, float, float, float, float)));
    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects()), this, SLOT(ClearObjectsToVariableTable()));
    connect(GcodeScriptThread, SIGNAL(DeleteObject1()), this, SLOT(DeleteFirstVariable()));
//	connect(DeltaGcodeManager, SIGNAL(PauseCamera()), DeltaImageProcesser, SLOT(PauseCamera()));
//	connect(DeltaGcodeManager, SIGNAL(CaptureCamera()), DeltaImageProcesser, SLOT(CaptureCamera()));
//	connect(DeltaGcodeManager, SIGNAL(ResumeCamera()), DeltaImageProcesser, SLOT(ResumeCamera()));

//	connect(ui->pbPlayPauseCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(PlayCamera(bool)));
//	connect(ui->pbCaptureCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(CaptureCamera()));

//    connect(DeltaImageProcesser->ObjectManager1, SIGNAL(NewUpdateObjectPosition(QString)), DeltaGcodeManager, SLOT(SaveGcodeVariable(QString)));

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
    connect(ui->twDeltaManager, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(ChangeRobotName(int)));
    connect(ui->twDeltaManager, SIGNAL(tabCloseRequested(int)), this, SLOT(DeleteRobot(int)));




}

void RobotWindow::DisablePositionUpdatingEvents()
{
    ui->leX->blockSignals(true);
    ui->leY->blockSignals(true);
    ui->leZ->blockSignals(true);
    ui->leW->blockSignals(true);
    ui->leU->blockSignals(true);
    ui->leV->blockSignals(true);

    ui->vsZAdjsution->blockSignals(true);
    ui->vsAngleAdjsution->blockSignals(true);
    ui->vs5AxisAdjsution->blockSignals(true);
    ui->vs6AxisAdjsution->blockSignals(true);

    ui->leVelocity->blockSignals(true);
    ui->leAccel->blockSignals(true);
    ui->leStartSpeed->blockSignals(true);
    ui->leEndSpeed->blockSignals(true);
}

void RobotWindow::EnablePositionUpdatingEvents()
{
    ui->leX->blockSignals(false);
    ui->leY->blockSignals(false);
    ui->leZ->blockSignals(false);
    ui->leW->blockSignals(false);
    ui->leU->blockSignals(false);
    ui->leV->blockSignals(false);

    ui->vsZAdjsution->blockSignals(false);
    ui->vsAngleAdjsution->blockSignals(false);
    ui->vs5AxisAdjsution->blockSignals(false);
    ui->vs6AxisAdjsution->blockSignals(false);

    ui->leVelocity->blockSignals(false);
    ui->leAccel->blockSignals(false);
    ui->leStartSpeed->blockSignals(false);
    ui->leEndSpeed->blockSignals(false);
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
//        if (RobotManagerPointer != NULL)
//        {
//            foreach(RobotWindow* robot, RobotManagerPointer->RobotWindows)
//            {

//                if (robot->ui->cbRobotModel->currentText() == "Delta X 1")
//                {
//                   robot->DeltaGcodeManager->SelectProgram("X 1 - Shark Tank");
//                   robot->ui->pbExecuteGcodes->setChecked(true);
//                   robot->ExecuteProgram();
//                }

//                if (robot->ui->cbRobotModel->currentText() == "Delta X 2")
//                {
//                   robot->DeltaGcodeManager->SelectProgram("X 2 - Shark Tank");
//                   robot->ui->pbExecuteGcodes->setChecked(true);
//                   robot->ExecuteProgram();
//                }

//                if (robot->ui->cbRobotModel->currentText() == "Delta X S")
//                {
//                   //DeltaGcodeManager->SelectProgram("X S - Shark Tank");
//                }
//            }
//        }

        return;
	}

    QStringList paras = request.split(" ");

    for (int i = 0; i < paras.length() - 1; i++)
    {
        if (paras[i] == "Move")
        {
            if (paras[i + 1] == "Up")
            {
                ui->pbUp->click();
            }
            if (paras[i + 1] == "Down")
            {
                ui->pbDown->click();
            }
            if (paras[i + 1] == "Left")
            {
                ui->pbLeft->click();
            }
            if (paras[i + 1] == "Right")
            {
                ui->pbRight->click();
            }
            if (paras[i + 1] == "Forward")
            {
                ui->pbForward->click();
            }
            if (paras[i + 1] == "Backward")
            {
                ui->pbBackward->click();
            }
            if (paras[i + 1] == "Home")
            {
                ui->pbHome->click();
            }

            if (paras[i + 1] == "Demo")
            {

                DoADemo();
            }
        }

        if (paras[i] == "Change")
        {
            if (paras[i + 1] == "Division")
            {
                ui->cbDivision->setCurrentText(paras[i + 2]);
            }

            if (paras[i + 1] == "ConveyorPosition")
            {
                ui->leConveyorvMovingValue->setText(paras[i + 2]);
                emit ui->leConveyorvMovingValue->returnPressed();
            }
        }

        if (paras[i] == "Update")
        {
            if (paras[i + 1] == "ConveyorCalibPoint1")
            {
                ui->pbGetConveyorPoint1X->click();
                ui->pbGetConveyorPoint1Y->click();
            }
            if (paras[i + 1] == "ConveyorCalibPoint2")
            {
                ui->pbGetConveyorPoint2X->click();
                ui->pbGetConveyorPoint2Y->click();
            }
        }

        if (paras[i] == "Add")
        {
            if (paras[i + 1] == "Gcode")
            {
                if (paras[i + 2] == "G01")
                {
                    QString gcode = QString("G01 X%1 Y%2 Z%3").arg(RobotParameter.X).arg(RobotParameter.Y).arg(RobotParameter.Z);

                    AddGcodeLine(gcode);
                }

                if (paras[i + 2] == "M03")
                {
                    QString gcode = QString("M03 %1").arg(paras[i + 3]);

                    AddGcodeLine(gcode);
                }

                if (paras[i + 2] == "M05")
                {
                    QString gcode = QString("M05 %1").arg(paras[i + 3]);

                    AddGcodeLine(gcode);
                }
            }
        }

        if (paras[i] == "Send")
        {
            if (paras[i + 1] == "Robot")
            {
                QString gcode = paras[i + 2];
                for (int j = i + 3; j < paras.count(); j++)
                {
                    gcode += QString(" ") + paras[j];
                }

                emit Send(ConnectionManager::ROBOT, gcode);
            }
        }
    }


}

void RobotWindow::AddGcodeLine(QString gcode)
{
    if (gcode[gcode.length() - 1] != "\n")
        gcode += "\n";

    ui->pteGcodeArea->moveCursor (QTextCursor::End);
    ui->pteGcodeArea->insertPlainText(gcode);
    ui->pteGcodeArea->moveCursor(QTextCursor::End);
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
    UpdateVariable("X", "0");
    UpdateVariable("Y", "0");
    UpdateVariable("Z", "0");
    UpdateVariable("W", "0");
    UpdateVariable("U", "0");
    UpdateVariable("V", "0");
    UpdateVariable("F", "200");
    UpdateVariable("A", "1200");
    UpdateVariable("S", "12");
    UpdateVariable("E", "12");
    UpdateVariable("ConveyorSpeed", "0");
    UpdateVariable("ConveyorDirection", "0");

    UpdateVariable("O0_X", QString::number(NULL_NUMBER));
    UpdateVariable("O0_Y", QString::number(NULL_NUMBER));
    UpdateVariable("O0_A", QString::number(NULL_NUMBER));
    UpdateVariable("O0_W", QString::number(NULL_NUMBER));
    UpdateVariable("O0_L", QString::number(NULL_NUMBER));

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

    GcodeScriptThread->VariableAddress = ProjectName + "." + Name;

    ui->twDeltaManager->setTabText(ID, Name);

    for (int i = 0; i < RobotManagerPointer->RobotWindows.size() - 1; i++)
    {
        RobotManagerPointer->RobotWindows.at(i)->ui->twDeltaManager->setTabText(ID, Name);
    }

    // ---- Tracking ----
    bool isEncoderOn = setting->value("EncoderEnable").toBool();
    if (isEncoderOn == true)
    {
        ui->rbEncoderEnable->setChecked(true);
    }
    else
    {
        ui->rbVirtualEncoderEnable->setChecked(true);
    }

    ui->cbEncoderPositionInverse->setChecked(setting->value("InverseEncoderEnable", ui->cbEncoderPositionInverse->isChecked()).toBool());

    ui->leConvenyorSpeed->setText(setting->value("ConstantConveyorSpeed", ui->leConvenyorSpeed->text()).toString());
//    ui->cbConveyorDirection->setCurrentText(setting->value("ConveyorDirection", ui->cbConveyorDirection->currentText()).toString());
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
    comPort = setting->value("ComPort", "").toString();
    baudrate = setting->value("Baudrate", 115200).toInt();

    DeltaConnectionManager->EncoderPort->setPortName(comPort);
    DeltaConnectionManager->EncoderPort->setBaudRate(baudrate);

    if (connectionState == true && comPort != "")
    {
        if (DeltaConnectionManager->EncoderPort->open((QIODevice::ReadWrite)) == true)
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

    ui->cbSourceForImageProvider->setCurrentText(setting->value("ImageSource", ui->cbSourceForImageProvider->currentText()).toString());

    ui->leCameraWidth->setText(setting->value("WebcamWidth", ui->leCameraWidth->text()).toString());
    ui->leCameraHeight->setText(setting->value("WebcamHeight", ui->leCameraHeight->text()).toString());
    ui->leFPS->setText(setting->value("WebcamFPS", ui->leFPS->text()).toString());

    ui->leImageWidth->setText(setting->value("ResizeWidth", ui->leCameraWidth->text()).toString());
    ui->leImageHeight->setText(setting->value("ResizeHeight", ui->leCameraHeight->text()).toString());

    emit GotResizePara(cv::Size(ui->leImageWidth->text().toInt(), ui->leImageHeight->text().toInt()));

    ui->cbExternalImageSource->setChecked(setting->value("ExternalImageSourceEnable", ui->cbExternalImageSource->isChecked()).toBool());

    ui->leChessWidth->setText(setting->value("ChessWidth", ui->leChessWidth->text()).toString());
    ui->leChessHeight->setText(setting->value("ChessHeight", ui->leChessHeight->text()).toString());

    Object obj = ImageProcessingThread->GetNode("GetObjectsNode")->GetInputObject();

    obj.Width.Image = setting->value("ObjectWidth", obj.Width.Image).toFloat();
    obj.Length.Image = setting->value("ObjectLength", obj.Length.Image).toFloat();

    obj.Width.Real = setting->value("RealObjectWidth", ui->leWRec->text()).toFloat();
    obj.Length.Real = setting->value("RealObjectLength", ui->leLRec->text()).toFloat();
    obj.Height.Real = setting->value("RealObjectHeight", ui->leHRec->text()).toFloat();

    obj.RangeWidth.Max.Image = setting->value("ImageMaxObjectWidth", ui->leMaxWRec->text()).toFloat();
    obj.RangeWidth.Min.Image = setting->value("ImageMinObjectWidth", ui->leMinWRec->text()).toFloat();
    obj.RangeLength.Max.Image = setting->value("ImageMaxObjectLength", ui->leMaxLRec->text()).toFloat();
    obj.RangeLength.Min.Image = setting->value("ImageMinObjectLength", ui->leMinLRec->text()).toFloat();

    ui->leWRec->setText(QString::number(obj.Width.Real));
    ui->leLRec->setText(QString::number(obj.Length.Real));
    ui->leHRec->setText(QString::number(obj.Height.Real));

    obj.RangeWidth.Max.Real = setting->value("MaxObjectWidth", ui->leMaxWRec->text()).toFloat();
    obj.RangeWidth.Min.Real = setting->value("MinObjectWidth", ui->leMinWRec->text()).toFloat();
    obj.RangeLength.Max.Real = setting->value("MaxObjectLength", ui->leMaxLRec->text()).toFloat();
    obj.RangeLength.Min.Real = setting->value("MinObjectLength", ui->leMinLRec->text()).toFloat();

    ui->leMinWRec->setText(QString::number(obj.RangeWidth.Min.Real));
    ui->leMaxWRec->setText(QString::number(obj.RangeWidth.Max.Real));
    ui->leMinLRec->setText(QString::number(obj.RangeLength.Min.Real));
    ui->leMaxLRec->setText(QString::number(obj.RangeLength.Max.Real));

    emit GotOjectFilterInfo(obj);

    ui->leTrackingError->setText(setting->value("TrackingError", ui->leTrackingError->text()).toString());

    QPointF calibPoint1 = setting->value("RealCalibPoint1", QPointF(ui->leRealityPoint1X->text().toFloat(), ui->leRealityPoint1Y->text().toFloat())).toPointF();
    QPointF calibPoint2 = setting->value("RealCalibPoint2", QPointF(ui->leRealityPoint2X->text().toFloat(), ui->leRealityPoint2Y->text().toFloat())).toPointF();
    ui->leRealityPoint1X->setText(QString::number(calibPoint1.x()));
    ui->leRealityPoint1Y->setText(QString::number(calibPoint1.y()));
    ui->leRealityPoint2X->setText(QString::number(calibPoint2.x()));
    ui->leRealityPoint2Y->setText(QString::number(calibPoint2.y()));

    ui->cbDetectingAlgorithm->setCurrentText(setting->value("Algorithm", ui->cbDetectingAlgorithm->currentText()).toString());

    ui->lePythonUrl->setText(setting->value("ExternalScriptUrl", ui->lePythonUrl->text()).toString());
    ui->cbImageSource->setCurrentText(setting->value("TransmissionImageSource", ui->cbImageSource->currentText()).toString());

    ui->leEdgeThreshold->setText(setting->value("EdgeThreshold", ui->leEdgeThreshold->text()).toString());
    ui->leCenterThreshold->setText(setting->value("CenterThreshold", ui->leCenterThreshold->text()).toString());
    ui->leMinRadius->setText(setting->value("MinRadius", ui->leMinRadius->text()).toString());
    ui->leMaxRadius->setText(setting->value("MaxRadius", ui->leMaxRadius->text()).toString());

    setting->beginGroup("Parameter");
    ParameterPanel->LoadSetting(setting);
    setting->endGroup();

    ParameterPanel->RequestValue();

    setting->beginGroup("ImageViewer");
    ui->gvImageViewer->LoadSetting(setting);
    setting->endGroup();

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
    setting->setValue("IP", DeltaConnectionManager->TCPConnection->GetIP());
    setting->setValue("TCPPort", DeltaConnectionManager->TCPConnection->Port);
    setting->setValue("RobotModel", ui->cbRobotModel->currentText());
    setting->setValue("RobotState", DeltaConnectionManager->RobotPort->isOpen());

    setting->setValue("Name", Name);

    //---- Tracking ----
    setting->setValue("EncoderEnable", ui->rbEncoderEnable->isChecked());
    setting->setValue("InverseEncoderEnable", ui->cbEncoderPositionInverse->isChecked());
    setting->setValue("ConstantConveyorSpeed", ui->leConvenyorSpeed->text());
//    setting->setValue("ConveyorDirection", ui->cbConveyorDirection->currentText());
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

    connectionState = DeltaConnectionManager->EncoderPort->isOpen();
    comPort = DeltaConnectionManager->EncoderPort->portName();
    baudrate = DeltaConnectionManager->EncoderPort->baudRate();

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

    setting->setValue("ConveyorPoint1", QPointF(ui->leConveyorPoint1X->text().toFloat(), ui->leConveyorPoint1Y->text().toFloat()));
    setting->setValue("ConveyorPoint2", QPointF(ui->leConveyorPoint2X->text().toFloat(), ui->leConveyorPoint2Y->text().toFloat()));
    setting->setValue("ConveyorPoint3", QPointF(ui->leConveyorPoint3X->text().toFloat(), ui->leConveyorPoint3Y->text().toFloat()));

    setting->setValue("ConveyorDeviationAngle", ui->leConveyorDeviationAngle->text());

    setting->setValue("WarpEnable", ui->pbWarpTool->isChecked());
    setting->setValue("DisplayOutput", ui->cbImageOutput->currentText());


//----------
    setting->setValue("ImageSource", ui->cbSourceForImageProvider->currentText());

    setting->setValue("WebcamWidth", ui->leCameraWidth->text());
    setting->setValue("WebcamHeight", ui->leCameraHeight->text());
    setting->setValue("WebcamFPS", ui->leFPS->text());

    setting->setValue("ResizeWidth", ui->leImageWidth->text());
    setting->setValue("ResizeHeight", ui->leImageHeight->text());
    setting->setValue("ExternalImageSourceEnable", ui->cbExternalImageSource->isChecked());

    setting->setValue("ChessWidth", ui->leChessWidth->text());
    setting->setValue("ChessHeight", ui->leChessHeight->text());

    Object obj = ImageProcessingThread->GetNode("GetObjectsNode")->GetInputObject();

    setting->setValue("ObjectWidth", obj.Width.Image);
    setting->setValue("ObjectLength", obj.Length.Image);

    setting->setValue("ImageMinObjectWidth", obj.RangeWidth.Min.Image);
    setting->setValue("ImageMaxObjectWidth", obj.RangeWidth.Max.Image);
    setting->setValue("ImageMinObjectLength", obj.RangeLength.Min.Image);
    setting->setValue("ImageMaxObjectLength", obj.RangeLength.Max.Image);

    setting->setValue("RealObjectWidth", ui->leWRec->text());
    setting->setValue("RealObjectLength", ui->leLRec->text());
    setting->setValue("RealObjectHeight", ui->leHRec->text());

    setting->setValue("MinObjectWidth", ui->leMinWRec->text());
    setting->setValue("MaxObjectWidth", ui->leMaxWRec->text());
    setting->setValue("MinObjectLength", ui->leMinLRec->text());
    setting->setValue("MaxObjectLength", ui->leMaxLRec->text());

    setting->setValue("TrackingError", ui->leTrackingError->text());

    setting->setValue("RealCalibPoint1", QPointF(ui->leRealityPoint1X->text().toFloat(), ui->leRealityPoint1Y->text().toFloat()));
    setting->setValue("RealCalibPoint2", QPointF(ui->leRealityPoint2X->text().toFloat(), ui->leRealityPoint2Y->text().toFloat()));

    setting->setValue("Algorithm", ui->cbDetectingAlgorithm->currentText());

    setting->setValue("ExternalScriptUrl", ui->lePythonUrl->text());
    setting->setValue("TransmissionImageSource", ui->cbImageSource->currentText());

    setting->setValue("EdgeThreshold", ui->leEdgeThreshold->text());
    setting->setValue("CenterThreshold", ui->leCenterThreshold->text());
    setting->setValue("MinRadius", ui->leMinRadius->text());
    setting->setValue("MaxRadius", ui->leMaxRadius->text());

//----------

    setting->beginGroup("Parameter");
    ParameterPanel->SaveSetting(setting);
    setting->endGroup();

    setting->beginGroup("ImageViewer");
    ui->gvImageViewer->SaveSetting(setting);
    setting->endGroup();

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
    ui->lbID->setText(QString::number(id));
}

void RobotWindow::SetName(QString name)
{
    Name = name;
}

void RobotWindow::ConnectDeltaRobot()
{
	if (ui->cbAutoConnect->isChecked() == false)
	{
        bool isConnect = openConnectionDialog(DeltaConnectionManager->RobotPort, DeltaConnectionManager->RobotSocket, ui->pbConnect, ui->lbComName);

		if (isConnect == true)
		{
            if (ui->cbRobotModel->currentText() == "Delta X 1")
            {
                QTimer::singleShot(2000, [=](){emit Send(ConnectionManager::ROBOT, "IsDelta"); emit Send(ConnectionManager::ROBOT, "IsDelta");});
                QTimer::singleShot(2000, [=](){emit Send(ConnectionManager::ROBOT, "IsDelta");});
            }
            else
            {
                emit Send(ConnectionManager::ROBOT, "IsDelta");
            }
		}

		return;
	}

	if (ui->pbConnect->text() == "Connect" && !DeltaConnectionManager->IsRobotConnect())
	{
        OpenLoadingPopup();
        emit ScanAndConnectRobot();
	}

	else if (ui->pbConnect->text() == "Disconnect")
	{
		ui->pbConnect->setText("Connect");

//        DeltaConnectionManager->DisconnectRobot();
        emit DisconnectRobot();
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

void RobotWindow::ChangeRobotName(int tabIndex)
{
    QString oldRobotName = ui->twDeltaManager->tabText(tabIndex);

    bool ok;
    QString newRobotName = QInputDialog::getText(this, tr("Change project name"), tr("New name:"), QLineEdit::Normal, oldRobotName, &ok);

    if (ok && !newRobotName.isEmpty())
    {
        Name = newRobotName;

        foreach(RobotWindow* robot, RobotManagerPointer->RobotWindows)
        {
            robot->ui->twDeltaManager->setTabText(tabIndex, newRobotName);
        }
    }
}

void RobotWindow::DeleteRobot(int tabIndex)
{
    QString projectName = ui->twDeltaManager->tabText(tabIndex);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, projectName, "Do you want to delete this robot?",
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        ui->twDeltaManager->removeTab(tabIndex);
//        foreach(RobotWindow* robotWindow, RobotManagers.at(tabIndex)->RobotWindows)
//        {
//            delete robotWindow;
//        }

        //delete RobotManagers.at(tabIndex);

        RobotManagerPointer->RobotWindows.removeAt(tabIndex);
    }
    else
    {
        return;
    }

    if (tabIndex > 0)
    {
        ui->twDeltaManager->setCurrentIndex(tabIndex - 1);
    }
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
    int startMode = GcodeScript::BEGIN;

    if (ui->rbEditorStart->isChecked() != true)
    {
        startMode = GcodeScript::CURSOR_POSITION;
    }

    if (ui->pbExecuteGcodes->isChecked() == false)
    {
        emit StopGcodeProgram();

//        if (DeltaGcodeManager->InsideGcodeProgramManager != NULL)
//        {
//            DeltaGcodeManager->InsideGcodeProgramManager->Stop();
//        }
        return;
    }

	SaveProgram();

//	QString exeGcodes = ui->pteGcodeArea->toPlainText();
//    DeltaGcodeManager->ExecuteGcode(exeGcodes, true);

    emit RunGcodeProgram(ui->pteGcodeArea->toPlainText(), startMode, true);
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
            SoftwareLog(QString("Can't import ") + fileName);
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
            SoftwareLog("No result");
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

    emit RunGcodeProgram(line, GcodeScript::BEGIN, false);
}

void RobotWindow::HighLineCurrentLine(int pos)
{
    QTextCursor textCursor = ui->pteGcodeArea->textCursor();
    textCursor.movePosition(QTextCursor::Start);
    textCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, pos);
    ui->pteGcodeArea->setTextCursor(textCursor);
    ui->pteGcodeArea->highlightCurrentLine();
}

//void RobotWindow::UpdateZLineEditValue(int z)
//{
//	ui->leZ->setText(QString::number(Delta2DVisualizer->ZHome - z));
//}

//void RobotWindow::UpdateAngleLineEditValue(int w)
//{
//    ui->leW->setText(QString::number(ui->vsAngleAdjsution->value()));
//    ui->leU->setText(QString::number(ui->vs5AxisAdjsution->value()));
//    ui->leV->setText(QString::number(ui->vs6AxisAdjsution->value()));

//    ui->lb4AxisValue->setText(QString::number(ui->vsAngleAdjsution->value()));
//    ui->lb5AxisValue->setText(QString::number(ui->vs5AxisAdjsution->value()));
//    ui->lb6AxisValue->setText(QString::number(ui->vs6AxisAdjsution->value()));
//}

//void RobotWindow::UpdateDeltaPositionFromLineEditValue()
//{
//    DisablePositionUpdatingEvents();

//    //---- 1. Delta 2D Visualizer Values----
//    if (positionEmitter != "Delta2DVisualizer")
//    {
//        Delta2DVisualizer->X = ui->leX->text().toFloat();
//        Delta2DVisualizer->Y = ui->leY->text().toFloat();
//        Delta2DVisualizer->Z = ui->leZ->text().toFloat();
//        Delta2DVisualizer->W = ui->leW->text().toFloat();
//        Delta2DVisualizer->U = ui->leU->text().toFloat();
//        Delta2DVisualizer->V = ui->leV->text().toFloat();
//    }

//    //---- 2. Z Slider -----
//	ui->vsZAdjsution->setValue(Delta2DVisualizer->ZHome - Delta2DVisualizer->Z);

//    //---- 3. Delta 2D Visualizer Display ------
//    Delta2DVisualizer->ChangeXY(ui->leX->text().toFloat(), ui->leY->text().toFloat());

//    //---- 4. Position Label ---
//    UpdatePositionToLabel();

//    //---- 5. Gcode Editor Para ----

//    QString gcode = QString("G01 X%1 Y%2 Z%3 W%4 U%5 V%6\n").arg(Delta2DVisualizer->X).arg(Delta2DVisualizer->Y).arg(Delta2DVisualizer->Z).arg(Delta2DVisualizer->W).arg(Delta2DVisualizer->U).arg(Delta2DVisualizer->V);

//    DeltaConnectionManager->SendToRobot(gcode);

//    EnablePositionUpdatingEvents();

//    positionEmitter = "";
//}

void RobotWindow::UpdatePositionToLabel()
{
    ui->lbX->setText(QString::number(RobotParameter.X));
    ui->lbY->setText(QString::number(RobotParameter.Y));
    ui->lbZ->setText(QString::number(RobotParameter.Z));
    ui->lbW->setText(QString::number(RobotParameter.W));
    ui->lbU->setText(QString::number(RobotParameter.U));
    ui->lbV->setText(QString::number(RobotParameter.V));


}

//void RobotWindow::UpdateTextboxFrom2DControl(float x, float y, float z, float w, float u, float v)
//{
//    positionEmitter = "Delta2DVisualizer";

//    DisablePositionUpdatingEvents();
//	ui->leX->setText(QString::number(x));
//	ui->leY->setText(QString::number(y));
//	ui->leZ->setText(QString::number(z));
//	ui->leW->setText(QString::number(w));
//    ui->leU->setText(QString::number(u));
//    ui->leV->setText(QString::number(v));
//    EnablePositionUpdatingEvents();

//    UpdateDeltaPositionFromLineEditValue();
//}

//void RobotWindow::UpdateTextboxFrom3DControl(float x, float y, float z, float w, float u, float v)
//{
//    positionEmitter = "Delta3DVisualizer";
//    DisablePositionUpdatingEvents();

//	if (x != NULL_NUMBER)
//	{
//		ui->leX->setText(QString::number(x));
//	}
//	if (y != NULL_NUMBER)
//	{
//		ui->leY->setText(QString::number(y));
//	}
	
//	if (z != NULL_NUMBER)
//	{
//		ui->leZ->setText(QString::number(z + Delta2DVisualizer->ZHome));
//	}
//	if (w != NULL_NUMBER)
//	{
//		ui->leW->setText(QString::number(w));
//	}
//    EnablePositionUpdatingEvents();

//	UpdateDeltaPositionFromLineEditValue();
//}

//void RobotWindow::UpdatePositionControl(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e)
//{
//    DisablePositionUpdatingEvents();

//    if (x == 0 && y == 0 && z == 0 && w == 0 && u == 0 && v == 0)
//	{
//		x = Delta2DVisualizer->XHome;
//		y = Delta2DVisualizer->YHome;
//		z = Delta2DVisualizer->ZHome;
//		w = Delta2DVisualizer->WHome;
//        u = Delta2DVisualizer->UHome;
//        v = Delta2DVisualizer->VHome;
//	}

//	ui->leX->setText(QString::number(x));
//	ui->leY->setText(QString::number(y));
//	ui->leZ->setText(QString::number(z));
//	ui->leW->setText(QString::number(w));
//    ui->leU->setText(QString::number(u));
//    ui->leV->setText(QString::number(v));
//	ui->leVelocity->setText(QString::number(f));
//	ui->leAccel->setText(QString::number(a));
//    ui->leStartSpeed->setText(QString::number(s));
//    ui->leEndSpeed->setText(QString::number(e));

//	Delta2DVisualizer->X = x;
//	Delta2DVisualizer->Y = y;
//	Delta2DVisualizer->Z = z;
//	Delta2DVisualizer->W = w;
//    Delta2DVisualizer->U = u;
//    Delta2DVisualizer->V = v;
//    Delta2DVisualizer->F = f;
//    Delta2DVisualizer->A = a;
//    Delta2DVisualizer->S = s;
//    Delta2DVisualizer->E = e;

//	ui->vsZAdjsution->setValue(Delta2DVisualizer->ZHome - Delta2DVisualizer->Z);
//	Delta2DVisualizer->ChangeXY(x, y);

//    EnablePositionUpdatingEvents();
//}

void RobotWindow::UpdatePositionControl(RobotPara robotPara)
{
    RobotParameter = robotPara;
}

void RobotWindow::ReceiveHomePosition(float x, float y, float z, float w, float u, float v)
{
    RobotParameter.X = RobotParameter.XHome = x;
    RobotParameter.Y = RobotParameter.YHome = y;
    RobotParameter.Z = RobotParameter.ZHome = z;
    RobotParameter.W = RobotParameter.WHome = w;
    RobotParameter.U = RobotParameter.UHome = u;
    RobotParameter.V = RobotParameter.VHome = v;

    UpdateVariables(QString("X=%1;Y=%2;Z=%3;W=%4;U=%5;V=%6").arg(x).arg(y).arg(z).arg(w).arg(u).arg(v));
}

void RobotWindow::UpdateVelocity()
{
    QString value = ui->leVelocity->text();
    UpdateVariable("F", value);
    emit Send(ConnectionManager::ROBOT, QString("G01 F") + value);
}

void RobotWindow::UpdateAccel()
{
    QString value = ui->leAccel->text();
    UpdateVariable("A", value);
    emit Send(ConnectionManager::ROBOT, QString("M204 A") + ui->leAccel->text());
}

void RobotWindow::UpdateStartSpeed()
{
    QString value = ui->leStartSpeed->text();
    UpdateVariable("S", value);
    emit Send(ConnectionManager::ROBOT, QString("M205 S") + ui->leStartSpeed->text());
}

void RobotWindow::UpdateEndSpeed()
{
    QString value = ui->leEndSpeed->text();
    UpdateVariable("E", value);
    emit Send(ConnectionManager::ROBOT, QString("M205 E") + ui->leEndSpeed->text());
}

void RobotWindow::AdjustGripperAngle(int angle)
{
    emit Send(ConnectionManager::ROBOT, QString("M360 E1"));
    emit Send(ConnectionManager::ROBOT, QString("M03 S") + QString::number(angle * 5));

	ui->lbGripperValue->setText(QString::number(angle * 5));
}

void RobotWindow::Grip()
{
    emit Send(ConnectionManager::ROBOT, QString("M360 E1"));
	if (ui->pbGrip->text() == "Grip")
	{
		ui->pbGrip->setText("Release");
        emit Send(ConnectionManager::ROBOT, QString("M03 S") + ui->leGripperMax->text());

		ui->hsGripperAngle->blockSignals(true);
		ui->hsGripperAngle->setValue(ui->leGripperMax->text().toInt() / 5);
		ui->hsGripperAngle->blockSignals(false);
		
		ui->lbGripperValue->setText(ui->leGripperMax->text());
	}
	else
	{
		ui->pbGrip->setText("Grip");
        emit Send(ConnectionManager::ROBOT, QString("M03 S") + ui->leGripperMin->text());

		ui->hsGripperAngle->blockSignals(true);
		int vl = ui->leGripperMin->text().toInt() / 5;
		ui->hsGripperAngle->setValue(vl);
		ui->hsGripperAngle->blockSignals(false);

		ui->lbGripperValue->setText(ui->leGripperMin->text());
		
    }
}

void RobotWindow::MoveRobot(QString gcode)
{
    if (gcode.toUpper() == "G28")
    {
        return;
    }

    QString prefixS = "X Y Z W U V F A S E";
    QStringList prefixs = prefixS.split(' ');

    foreach(QString prefix, prefixs)
    {
        QString value = GetValueInGcode(prefix, gcode);

        if (value != "")
        {
            UpdateVariable(prefix, value);
            RobotParameter.Set(prefix, value.toFloat());
        }
    }
}

void RobotWindow::MoveRobot(QString axis, float step)
{
    float value = RobotParameter.Get(axis) + step;
    RobotParameter.Set(axis, value);

    UpdateVariable(axis, QString::number(value));

    emit Send(ConnectionManager::ROBOT, QString("G01 ") + axis + QString::number(value));
}

void RobotWindow::MoveRobotFollowObject(float x, float y, float angle)
{
//    emit Send(ConnectionManager::ROBOT, QString("G01 X%1 Y%2 W%3").arg(x).arg(y).arg(angle));
    emit Send(ConnectionManager::ROBOT, QString("G01 X%1 Y%2").arg(x).arg(y));
}

void RobotWindow::DoADemo()
{
    static bool FirstRun1 = true;
    static bool FirstRun2 = true;
    static bool FirstRun3 = true;


    if (ui->cbRobotModel->currentText() == "Delta X 1" && FirstRun1 == true)
    {
       DeltaGcodeManager->SelectProgram("X 1 - Demo");
    }

    if (ui->cbRobotModel->currentText() == "Delta X 2" && FirstRun1 == true)
    {
       DeltaGcodeManager->SelectProgram("X 2 - Demo");
    }

    if (ui->cbRobotModel->currentText() == "Delta X S" && FirstRun1 == true)
    {
       DeltaGcodeManager->SelectProgram("X S - Demo");
    }

    ui->pbExecuteGcodes->setChecked(true);
    ExecuteProgram();

//    FirstRun1 = false;
//    FirstRun2 = false;
//    FirstRun3 = false;
}

void RobotWindow::UpdateRobotPositionToUI()
{
    DisablePositionUpdatingEvents();

    if (!ui->framePositionParameter->underMouse())
    {
        ui->leX->setText(QString::number(RobotParameter.X));
        ui->leY->setText(QString::number(RobotParameter.Y));
        ui->leZ->setText(QString::number(RobotParameter.Z));
        ui->leW->setText(QString::number(RobotParameter.W));
        ui->leU->setText(QString::number(RobotParameter.U));
        ui->leV->setText(QString::number(RobotParameter.V));
    }

    if (!ui->wg2D->underMouse())
        Delta2DVisualizer->ChangeXY(RobotParameter.X, RobotParameter.Y);

    if (!ui->vsZAdjsution->underMouse())
        ui->vsZAdjsution->setValue(RobotParameter.ZHome - RobotParameter.Z);

    ui->vsAngleAdjsution->setValue(RobotParameter.W);
    ui->vs5AxisAdjsution->setValue(RobotParameter.U);
    ui->vs6AxisAdjsution->setValue(RobotParameter.V);

    UpdatePositionToLabel();

    EnablePositionUpdatingEvents();
}

void RobotWindow::SetPump(bool value)
{
    emit Send(ConnectionManager::ROBOT, QString("M360 E0"));
	if (value == true)
	{
        emit Send(ConnectionManager::ROBOT, QString("M04"));
	}
	else
	{
        emit Send(ConnectionManager::ROBOT, QString("M05"));
	}
}

void RobotWindow::SetLaser(bool value)
{
    emit Send(ConnectionManager::ROBOT, QString("M360 E3"));
	if (value == true)
	{
        emit Send(ConnectionManager::ROBOT, QString("M04"));
	}
	else
	{
        emit Send(ConnectionManager::ROBOT, QString("M05"));
	}
}

void RobotWindow::Home()
{
    emit Send(ConnectionManager::ROBOT, "G28");

//	ui->leX->setText(QString::number(Delta2DVisualizer->XHome));
//	ui->leY->setText(QString::number(Delta2DVisualizer->YHome));
//	ui->leZ->setText(QString::number(Delta2DVisualizer->ZHome));
//	ui->leW->setText(QString::number(Delta2DVisualizer->WHome));

//	Delta2DVisualizer->X = Delta2DVisualizer->XHome;
//	Delta2DVisualizer->Y = Delta2DVisualizer->YHome;
//	Delta2DVisualizer->Z = Delta2DVisualizer->ZHome;
//	Delta2DVisualizer->W = Delta2DVisualizer->WHome;

//	Delta2DVisualizer->ChangeXY(0, 0);
//    ui->vsZAdjsution->setValue(0);
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
            emit Send(ConnectionManager::ROBOT, "M08 " + inputName);
        }
        else
        {
            emit Send(ConnectionManager::ROBOT, "M07 " + inputName);
        }
    }
    else
    {
        if (leDelay->text() == "")
        {
            emit Send(ConnectionManager::ROBOT, "M08 " + inputName);
        }
        else
        {
            emit Send(ConnectionManager::ROBOT, "M08 " + inputName + " W" + leDelay->text());
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
    UpdateVariable(pin, value);
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

void RobotWindow::UpdateVariable(QString key, QString value)
{
    QString fullName = ProjectName + "." + Name + "." + key;
    fullName = fullName.replace(" ", "");

    SoftwareManager::GetInstance()->ProgramVariableManager->AddVariable(fullName, value);
}

void RobotWindow::UpdateVariables(QString cmd)
{
    if (cmd == "")
        return;

    QStringList vars = cmd.split(';');

    foreach(QString var, vars)
    {
        var = var.replace(" ", "");
        QStringList paras = var.split('=');
        if (paras.count() < 2)
            return;

        UpdateVariable(paras.at(0), paras.at(1));
    }
}

void RobotWindow::RespondVariableValue(QIODevice *s, QString name)
{
    QString value = SoftwareManager::GetInstance()->ProgramVariableManager->GetValue(name) + '\n';

    s->write(value.toStdString().c_str(), value.size());
}

void RobotWindow::UpdateGcodeValueToDeviceUI(QString deviceName, QString gcode)
{
    if (deviceName == "Robot")
    {
        MoveRobot(gcode);
    }

    if (deviceName == "Conveyor")
    {
    }

    if (deviceName == "Slider")
    {
    }

    if (deviceName == "ExternalMCU")
    {
    }
}

void RobotWindow::SetConvenyorSpeed()
{
    QString vel = ui->leConvenyorSpeed->text();
//	QString directionName = ui->cbConveyorDirection->currentText();

//    DeltaImageProcesser->SetConvenyorVelocity(vel.toFloat(), directionName);

    UpdateVariable("ConveyorSpeed", vel);
//    UpdateVariable("ConveyorDirection", (directionName.toLower()=="x") ? "0" : "1");
}

void RobotWindow::ConnectEncoder()
{
    bool result = openConnectionDialog(DeltaConnectionManager->EncoderPort, DeltaConnectionManager->EncoderSocket, ui->pbConnectEncdoer, ui->leEncoderCom);

    if (result == true)
    {
        emit Send(ConnectionManager::ENCODER, "M317 T100");
    }
}

void RobotWindow::ResetEncoderPosition()
{
    emit Send(ConnectionManager::ENCODER, "M316");
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

//    DeltaImageProcesser->DeviationAngle = line.angle();
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
//    qDebug() << "Start: " << Encoder1->GetPosition();

    Encoder1->MarkPosition();

    CaptureImage = mat;

    if (!CaptureImage.empty())
        emit GotImage(CaptureImage.clone());
}

void RobotWindow::GetCapturedSignal()
{
//    qDebug() << "Start: " << Encoder1->GetPosition();
    Encoder1->MarkPosition();
}

void RobotWindow::ChangeOutputDisplay(QString outputName)
{
    if (outputName == "Calibrating")
    {
        ui->gvImageViewer->TurnOnTool(true);
//        ui->gvImageViewer->TurnOnObjects(true);
    }

    if (outputName == "Detecting")
    {
        ui->gvImageViewer->TurnOnTool(false);
//        ui->gvImageViewer->TurnOnObjects(true);
    }

    if (outputName == "Original")
    {
        ui->gvImageViewer->TurnOnTool(false);
//        ui->gvImageViewer->TurnOnObjects(false);
    }
}

void RobotWindow::LoadWebcam()
{
    if (ui->cbExternalImageSource != NULL)
    {
        if(ui->cbExternalImageSource->isChecked() == true)
        {
            QMessageBox::information(this, "Notify", "You are using the camera from the outside. Please uncheck the box below if you want to use the webcam.");
            return;
        }
    }

    if (ui->pbLoadCamera->isChecked())
    {
        QStringList cameraItems;

        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        for (int i = 0; i < cameras.size(); i++)
        {
            cameraItems.append(QString::number(i) + QString(" - ") + cameras[i].description());
        }

        bool ok;
        QString text = QInputDialog::getItem(this, tr("Open camera"), tr("Camera ID: "), cameraItems, 0, false, &ok);

        if (ok && !text.isEmpty())
        {
            // Get webcam ID
            QString cameraIDText = text.mid(0, text.indexOf(" - "));
            int cameraID = cameraIDText.toInt();

            if (cameraItems.count() > 2)
            {
                if (cameraID == 0)
                {
                    cameraID = 1;
                }
                else if(cameraID == 1)
                {
                    cameraID = 0;
                }
            }

            RunningCamera = cameraID;

            ui->lbCameraState->setEnabled(true);
            ui->pbPlayPauseCamera->setChecked(true);

            ui->pbLoadCamera->setText("Stop Camera");

            bool isCameraUsingByOtherRobot = false;

            if (RobotManagerPointer != NULL)
            {
                if (RobotManagerPointer->RobotWindows.size() > 0)
                {
                    for (int i = 0; i < RobotManagerPointer->RobotWindows.size(); i++)
                    {
                        if (this == RobotManagerPointer->RobotWindows.at(i))
                            continue;

                        if (RobotManagerPointer->RobotWindows.at(i)->RunningCamera == RunningCamera)
                        {
                            Camera = RobotManagerPointer->RobotWindows.at(i)->Camera;
                            isCameraUsingByOtherRobot = true;
                        }
                    }
                }
            }

            if (isCameraUsingByOtherRobot == false)
            {
                Camera->open(cameraID);
                Camera->set(cv::CAP_PROP_FRAME_WIDTH, ui->leCameraWidth->text().toInt());
                Camera->set(cv::CAP_PROP_FRAME_HEIGHT, ui->leCameraHeight->text().toInt());

                ui->leCameraWidth->setText(QString::number((int)Camera->get(cv::CAP_PROP_FRAME_WIDTH)));
                ui->leCameraHeight->setText(QString::number((int)Camera->get(cv::CAP_PROP_FRAME_HEIGHT)));

                WebcamTimer.start(1000 / ui->leFPS->text().toInt());
            }

            IsCameraPause = false;
        }
        else
        {
            ui->pbLoadCamera->setChecked(false);
            IsCameraPause = false;
            RunningCamera = -1;
        }
    }
    else
    {
        StopWebcam();
    }
}

void RobotWindow::LoadImages()
{
    QString imageName;
    imageName = QFileDialog::getOpenFileName(this, tr("Open Image/Video"), "", tr("Image Files (*.png *.jpg *.bmp *.avi *.mp4)"));

    if (imageName == "")
        return;

    if (imageName.contains(".avi") || imageName.contains(".mp4"))
    {
        Camera->open(imageName.toStdString());

        if (!Camera->isOpened())
        {
            return;
        }

        Camera->open(imageName.toStdString());
        Camera->set(cv::CAP_PROP_FRAME_WIDTH, ui->leCameraWidth->text().toInt());
        Camera->set(cv::CAP_PROP_FRAME_HEIGHT, ui->leCameraHeight->text().toInt());

        ui->leCameraWidth->setText(QString::number((int)Camera->get(cv::CAP_PROP_FRAME_WIDTH)));
        ui->leCameraHeight->setText(QString::number((int)Camera->get(cv::CAP_PROP_FRAME_HEIGHT)));

        WebcamTimer.start(1000 / ui->leFPS->text().toInt());
    }
    else
    {
        cv::String imgName = imageName.toStdString();
        CaptureImage = cv::imread(imgName, cv::IMREAD_COLOR);
        emit GotImage(CaptureImage);
    }
}

void RobotWindow::StopWebcam()
{
    ui->lbCameraState->setEnabled(false);
    Camera->release();
    RunningCamera = -1;
    IsCameraPause = false;
    ui->pbLoadCamera->setText("Load Camera");

    WebcamTimer.stop();
}

void RobotWindow::CaptureWebcam()
{
    if (Camera == NULL)
        return;

    if (Camera->isOpened() == false)
    {
        StopWebcam();
        return;
    }

    if (Camera->read(CaptureImage))
    {
        emit GotImage(CaptureImage);
    }
}

void RobotWindow::RearrangeTaskFlow()
{

}

void RobotWindow::OpenColorFilterWindow()
{
    ParameterPanel->SetImage(CaptureImage);
    ParameterPanel->show();
}

void RobotWindow::SelectObjectDetectingAlgorithm(int algorithm)
{
    ui->fBlobPanel->setHidden(true);
    ui->fExternalScriptPanel->setHidden(true);
    ui->fCirclePanel->setHidden(true);

    QString text = ui->cbDetectingAlgorithm->itemText(algorithm);

    if (text == "Find Blobs")
    {
        ui->fBlobPanel->setHidden(false);
    }
    if (text == "Find Circles")
    {
        ui->fCirclePanel->setHidden(false);
    }
    if (text == "External Script")
    {
        ui->fExternalScriptPanel->setHidden(false);
    }
}

void RobotWindow::ConfigChessboard()
{
    ui->pbAreaTool->clicked(true);
    ui->pbWarpTool->clicked(false);
    QMessageBox box;

    box.setText("Chessboard will be used to correct the distortion of the image due to perspective.");

    QPushButton* FindBt = box.addButton("Find new chessboard", QMessageBox::AcceptRole);
    QPushButton* EditBt = box.addButton("Edit chessboard", QMessageBox::RejectRole);

    int result = box.exec();

    if (result == QMessageBox::AcceptRole) // Find
    {
        bool ok;
        QString chessboardSize = QString("%1x%2").arg(ui->leChessWidth->text()).arg(ui->leChessHeight->text());
        QString text = QInputDialog::getText(this, tr("Find Chessboard"),
                                             tr("Chessboard size:"), QLineEdit::Normal,
                                             chessboardSize, &ok);
        if (ok && !text.isEmpty())
        {
            QStringList paras = text.split("x");
            cv::Size size(paras[0].toInt(), paras[1].toInt());

            ui->leChessWidth->setText(paras[0]);
            ui->leChessHeight->setText(paras[1]);

//            ImageProcessingThread->GetNode("FindChessboardNode")->Input(size);
            emit GotChessboardSize(size);

            emit GotResizeImage(ImageProcessingThread->GetNode("ResizeImageNode")->GetOutputImage());

            if (ui->pbWarpTool->isChecked() == false)
            {
                ui->gvImageViewer->SelectQuadrangleTool();
            }

        }
    }
    else // Edit
    {
        ui->gvImageViewer->SelectQuadrangleTool();
    }
}

void RobotWindow::GetCalibPointsFromImage(QPointF p1, QPointF p2)
{
    float xx1 = ui->leRealityPoint1X->text().toFloat();
    float yy1 = ui->leRealityPoint1Y->text().toFloat();
    float xx2 = ui->leRealityPoint2X->text().toFloat();
    float yy2 = ui->leRealityPoint2Y->text().toFloat();

    QPolygonF poly;

    poly.append(p1);
    poly.append(p2);
    poly.append(QPointF(xx1, yy1));
    poly.append(QPointF(xx2, yy2));

    emit GotCalibPoints(poly);
}

void RobotWindow::UpdateRealPositionOfCalibPoints()
{
    QPointF rpoint1(ui->leRealityPoint1X->text().toFloat(), ui->leRealityPoint1Y->text().toFloat());
    QPointF rpoint2(ui->leRealityPoint2X->text().toFloat(), ui->leRealityPoint2Y->text().toFloat());

    QString p1Text = QString("P1: X = %1, Y = %2").arg(rpoint1.x()).arg(rpoint1.y());
    QString p2Text = QString("P2: X = %1, Y = %2").arg(rpoint2.x()).arg(rpoint2.y());

    ui->gvImageViewer->SetPointTitles(p1Text, p2Text);

    QPolygonF poly;

    poly.append(ui->gvImageViewer->GetPoint1());
    poly.append(ui->gvImageViewer->GetPoint2());
    poly.append(rpoint1);
    poly.append(rpoint2);

    emit GotCalibPoints(poly);
}

void RobotWindow::GetObjectSizeFromImage(QRectF rect)
{
    QMatrix matrix = ImageProcessingThread->GetNode("VisibleObjectsNode")->GetMatrix();
    Object obj;

    float maxWidthRatio = ui->leMaxWRec->text().toFloat() / ui->leWRec->text().toFloat();
    float minWidthRatio = ui->leMinWRec->text().toFloat() / ui->leWRec->text().toFloat();
    float maxLengthRatio = ui->leMaxLRec->text().toFloat() / ui->leLRec->text().toFloat();
    float minLengthRatio = ui->leMinLRec->text().toFloat() / ui->leLRec->text().toFloat();

    if (rect.height() < rect.width())
    {
        obj.Width.Image = rect.height();
        obj.Length.Image = rect.width();
    }
    else
    {
        obj.Width.Image = rect.width();
        obj.Length.Image = rect.height();
    }

    obj.RangeWidth.Max.Image = obj.Width.Image * maxWidthRatio;
    obj.RangeWidth.Min.Image = obj.Width.Image * minWidthRatio;
    obj.RangeLength.Max.Image = obj.Length.Image * maxLengthRatio;
    obj.RangeLength.Min.Image = obj.Length.Image * minLengthRatio;

    if (!matrix.isIdentity())
    {
        obj.Map(matrix);

        ui->leWRec->setText(QString::number(obj.Width.Real));
        ui->leLRec->setText(QString::number(obj.Length.Real));
    }
    else
    {
        obj.Width.Real = ui->leWRec->text().toFloat();
        obj.Length.Real = ui->leLRec->text().toFloat();
    }

    obj.RangeWidth.Max.Real = obj.Width.Real * maxWidthRatio;
    obj.RangeWidth.Min.Real = obj.Width.Real * minWidthRatio;
    obj.RangeLength.Max.Real = obj.Length.Real * maxLengthRatio;
    obj.RangeLength.Min.Real = obj.Length.Real * minLengthRatio;

    ui->leMaxWRec->setText(QString::number(obj.RangeWidth.Max.Real));
    ui->leMinWRec->setText(QString::number(obj.RangeWidth.Min.Real));
    ui->leMaxLRec->setText(QString::number(obj.RangeLength.Max.Real));
    ui->leMinLRec->setText(QString::number(obj.RangeLength.Min.Real));

    emit GotOjectFilterInfo(obj);
}

void RobotWindow::GetMappingPointFromImage(QPointF point)
{
    point.setY(0 - point.y());

    QMatrix matrix = ImageProcessingThread->GetNode("VisibleObjectsNode")->GetMatrix();
    QPointF realPoint = matrix.map(point);

    ui->leConveyorPoint3X->setText(QString::number(realPoint.x()));
    ui->leConveyorPoint3Y->setText(QString::number(realPoint.y()));

    ui->gvImageViewer->SetMappingPointTitle(QString("X=%1,Y=%2").arg(realPoint.x()).arg(realPoint.y()));
}

void RobotWindow::GetNewImageSize()
{
    QLineEdit *leSender = qobject_cast<QLineEdit*>(sender());

    if (leSender == ui->leImageWidth)
    {
        int newW = ui->leImageWidth->text().toInt();

        QSize imageSize = ImageProcessingThread->GetNode("GetImageNode")->GetImageSize();

        int newH = ImageTool::Map(newW, imageSize.width(), imageSize.height());

        ui->leImageHeight->setText(QString::number(newH));

        emit GotResizePara(cv::Size(newW, newH));
    }
    else
    {
        int newH = ui->leImageHeight->text().toInt();

        QSize imageSize = ImageProcessingThread->GetNode("GetImageNode")->GetImageSize();

        int newW = ImageTool::Map(newH, imageSize.height(), imageSize.width());

        ui->leImageWidth->setText(QString::number(newW));

        emit GotResizePara(cv::Size(newW, newH));
    }
}

void RobotWindow::UnselectToolButtons()
{
    ui->pbCalibPointTool->setChecked(false);
    ui->pbAreaTool->setChecked(false);
    ui->pbFindChessboardTool->setChecked(false);
    ui->pbGetSizeTool->setChecked(false);
    ui->pbMappingPointTool->setChecked(false);
}

void RobotWindow::UpdateObjectsToImageViewer(QList<Object*>* objects)
{
    QList<QPolygonF> polys;
    QMap<QString, QPointF> texts;
    int counter = 0;

    foreach(Object* obj, *objects)
    {
        counter++;
        if (counter > 100)
            return;
        polys.append(obj->ToPolygon());
        texts.insert(QString("X=%1,Y=%2,A=%3").arg(obj->X.Real).arg(obj->Y.Real).arg(obj->Angle.Real), QPointF(obj->X.Image, obj->Y.Image));
    }

    ui->gvImageViewer->DrawPolygons(polys);
    ui->gvImageViewer->DrawTexts(texts);
}

void RobotWindow::UpdateObjectsToVariableTable(QList<Object *> *objects)
{
    int counter = 0;

    foreach(Object* obj, *objects)
    {

        UpdateVariable(QString("O%1_X").arg(counter), QString::number(obj->X.Real));
        UpdateVariable(QString("O%1_Y").arg(counter), QString::number(obj->Y.Real));
        UpdateVariable(QString("O%1_W").arg(counter), QString::number(obj->Width.Real));
        UpdateVariable(QString("O%1_L").arg(counter), QString::number(obj->Length.Real));
        UpdateVariable(QString("O%1_A").arg(counter), QString::number(obj->Angle.Real));

        counter++;
    }

    for(int i = counter; i < 100; i++)
    {
        QString fullName = ProjectName + "." + Name + "." + QString("O%1_X").arg(i);
        fullName = fullName.replace(" ", "");

        if (SoftwareManager::GetInstance()->ProgramVariableManager->GetMap()->contains(fullName) == false)
            break;

        UpdateVariable(QString("O%1_X").arg(i), "-6789");
        UpdateVariable(QString("O%1_Y").arg(i), "-6789");
        UpdateVariable(QString("O%1_W").arg(i), "-6789");
        UpdateVariable(QString("O%1_L").arg(i), "-6789");
        UpdateVariable(QString("O%1_A").arg(i), "-6789");
    }
}

void RobotWindow::ClearObjectsToVariableTable()
{
    emit RequestClearObjects();
}

void RobotWindow::DeleteFirstVariable()
{
    emit RequestDeleteObject(0);
}

void RobotWindow::EditImage(bool isWarp, bool isCropTool)
{
    TaskNode* cropImageNode = ImageProcessingThread->GetNode("CropImageNode");
    cropImageNode->ClearInputConnections();

    TaskNode* displayImageNode = ImageProcessingThread->GetNode("DisplayImageNode");
    displayImageNode->ClearInputConnections();

    if (isWarp == false && isCropTool == false)
    {
        cropImageNode->SetPreviousNode(ImageProcessingThread->GetNode("ResizeImageNode"));
        displayImageNode->SetPreviousNode(ImageProcessingThread->GetNode("CropImageNode"));

        ui->gvImageViewer->SelectNoTool();

        ui->gvImageViewer->TurnOnObjects(true);
    }
    else if (isWarp == true && isCropTool == false)
    {
        cropImageNode->SetPreviousNode(ImageProcessingThread->GetNode("WarpImageNode"));
        displayImageNode->SetPreviousNode(ImageProcessingThread->GetNode("CropImageNode"));

        ui->gvImageViewer->SelectNoTool();

        ui->gvImageViewer->TurnOnObjects(true);
    }
    else if (isWarp == false && isCropTool == true)
    {
        cropImageNode->SetPreviousNode(ImageProcessingThread->GetNode("ResizeImageNode"));
        displayImageNode->SetPreviousNode(ImageProcessingThread->GetNode("ResizeImageNode"));

        UnselectToolButtons();
        ui->pbAreaTool->setChecked(true);
        ui->gvImageViewer->SelectAreaTool();

        ui->gvImageViewer->TurnOnObjects(false);
    }
    else if (isWarp == true && isCropTool == true)
    {
        cropImageNode->SetPreviousNode(ImageProcessingThread->GetNode("WarpImageNode"));
        displayImageNode->SetPreviousNode(ImageProcessingThread->GetNode("WarpImageNode"));

        UnselectToolButtons();
        ui->pbAreaTool->setChecked(true);
        ui->gvImageViewer->SelectAreaTool();

        ui->gvImageViewer->TurnOnObjects(false);
    }
}

void RobotWindow::SendImageToExternalScript(cv::Mat input)
{
    if (ui->cbDetectingAlgorithm->currentText() != "External Script")
        return;

    if (DeltaConnectionManager->ExternalScriptSocket == NULL || input.empty())
        return;

    int paras[3];
    paras[0] = input.cols;
    paras[1] = input.rows;
    paras[2] = input.channels();

    int len = 3 * sizeof(int);

    DeltaConnectionManager->ExternalScriptSocket->write((char*)paras, len);

    int colByte = input.cols*input.channels() * sizeof(uchar);
    for (int i = 0; i < input.rows; i++)
    {
        char* data = (char*)input.ptr<uchar>(i); //first address of the i-th line
        int sedNum = 0;
        char buf[1024] = { 0 };

        while (sedNum < colByte)
        {
            int sed = (1024 < colByte - sedNum) ? 1024 : (colByte - sedNum);
            memcpy(buf, &data[sedNum], sed);
            int SendSize = DeltaConnectionManager->ExternalScriptSocket->write(buf, sed);

            if (SendSize == -1)
                return;
            sedNum += SendSize;
        }
    }
}

void RobotWindow::ConnectConveyor()
{
    openConnectionDialog(DeltaConnectionManager->ConveyorPort, DeltaConnectionManager->ConveyorSocket, ui->pbConveyorConnect, ui->lbConveyorCOMName);
}

void RobotWindow::SetConveyorMode(int mode)
{
    emit Send(ConnectionManager::CONVEYOR, QString("M310 ") + QString::number(mode));
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
    emit Send(ConnectionManager::CONVEYOR, QString("M313 ") + ui->leSpeedOfPositionMode->text());
}

void RobotWindow::MoveConveyor()
{
	if (ui->cbConveyorValueType->currentIndex() == 0)
	{
        emit Send(ConnectionManager::CONVEYOR, QString("M311 ") + ui->leConveyorvMovingValue->text());
	}
	else
	{
        emit Send(ConnectionManager::CONVEYOR, QString("M312 ") + ui->leConveyorvMovingValue->text());
	}
}

void RobotWindow::ProcessShortcutKey()
{

}

void RobotWindow::ProcessDetectedObjectFromExternalAI(QString msg)
{
//    QStringList paras = msg.split(",");
//    if (paras.count() >= 4)
//    {
//        //QString label = paras[0];
//        QString x = paras[0];
//        QString y = paras[1];
//        QString w = paras[2];
//        QString h = paras[3];

//        float delta = DeltaImageProcesser->EncoderPosition - DeltaImageProcesser->EncoderPositionAtCameraCapture;

//        if (ui->cbConveyorDirection->currentText() == "Y")
//        {
//            DeltaImageProcesser->ObjectManager1->AddNewObject(x.toFloat(), y.toFloat() + delta, w.toFloat(), h.toFloat());
//        }
//        else
//        {
//            DeltaImageProcesser->ObjectManager1->AddNewObject(x.toFloat()  + delta, y.toFloat(), w.toFloat(), h.toFloat());
//        }
//    }
}

/*!
After software send image to external script. AI will detect objects and send info back to software
 */

void RobotWindow::AddDisplayObjectFromExternalScript(QString msg)
{
    if (msg == "\n")
        return;

    QStringList objectInfos = msg.split(";");

    QList<Object*>* Objects = new QList<Object*>();

    foreach(QString objectInfo, objectInfos)
    {
        if (objectInfo.replace(" ", "").replace("/n", "") == "")
            continue;

        Object* object = new Object();

        QStringList paras = objectInfo.split(",");
        if (paras.count() >= 5)
        {
            //QString label = paras[0];
            object->X.Image = paras[1].toFloat();
            object->Y.Image = paras[2].toFloat();
            object->Length.Image = paras[3].toFloat();
            object->Width.Image = paras[4].toFloat();
            object->Angle.Image = paras[5].toFloat();

            object->Type = paras[0];

            object->ToPoints();

            object->Offset = Encoder1->CalculateOffset(Encoder1->GetMeasuredDistance());

            Objects->append(object);

        }
    }



    emit GotObjects(Objects);
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
        emit Send(ConnectionManager::ROBOT, gcode);
    }
}

void RobotWindow::BackwardExternalConveyor()
{
    QString command = ui->leBackwardConveyorGcode->text();
    QStringList gcodes = command.split(',');

    foreach(QString gcode, gcodes)
    {
        gcode = DeleteExcessSpace(gcode);
        emit Send(ConnectionManager::ROBOT, gcode);
    }
}

void RobotWindow::TurnOffExternalConveyor()
{
    QString command = ui->leTurnOffConveyorGcode->text();
    QStringList gcodes = command.split(',');

    foreach(QString gcode, gcodes)
    {
        gcode = DeleteExcessSpace(gcode);
        emit Send(ConnectionManager::ROBOT, gcode);
    }
}

void RobotWindow::VirtualEncoder()
{
    if (ui->rbVirtualEncoderEnable->isChecked() == false)
        return;

    static float VirtualEncoderPosition = 0;

    float velocity = ui->leConvenyorSpeed->text().toFloat();
    float distance = velocity * 0.1f;

    VirtualEncoderPosition += distance;

    ProcessEncoderValue(VirtualEncoderPosition);
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

//    DeltaGcodeManager->SaveGcodeVariable("#EncoderMoving", QString::number(DeltaImageProcesser->MovingDistance));
//    DeltaGcodeManager->SaveGcodeVariable("#EncoderPosition", QString::number(DeltaImageProcesser->EncoderPosition));

    //    DeltaImageProcesser->UpdateObjectPositionOnConveyor(Encoder1->GetOffset());
}

void RobotWindow::ProcessProximitySensorValue(int value)
{
    ui->lbProximitySensorValue->setText(QString::number(value));
}

void RobotWindow::ConnectSliding()
{
    openConnectionDialog(DeltaConnectionManager->SlidingPort, DeltaConnectionManager->SlidingSocket, ui->pbSlidingConnect, ui->lbSliderCOMName);
}

void RobotWindow::GoHomeSliding()
{
    emit Send(ConnectionManager::SLIDER, "M320");
}

void RobotWindow::DisableSliding()
{
    emit Send(ConnectionManager::SLIDER, "M323");
}

void RobotWindow::SetSlidingSpeed()
{
    emit Send(ConnectionManager::SLIDER, QString("M321 ") + ui->leSlidingSpeed->text());
}

void RobotWindow::SetSlidingPosition()
{
    emit Send(ConnectionManager::SLIDER, QString("M322 ") + ui->leSlidingPosition->text());
}

void RobotWindow::ConnectExternalMCU()
{
    openConnectionDialog(DeltaConnectionManager->ExternalControllerPort, DeltaConnectionManager->ExternalControllerSocket, ui->pbExternalControllerConnect, ui->lbExternalCOMName);
}

void RobotWindow::TransmitTextToExternalMCU()
{
    emit Send(ConnectionManager::MCU, ui->leTransmitToMCU->text());
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
    QString msg = ui->leTerminal->text();

    if (SentCommands.count() > 50)
        SentCommands.clear();

    SentCommands.append(msg);

    if (ui->cbDeviceSender->currentText() == "Robot")
    {
        emit Send(ConnectionManager::ROBOT, msg);
    }

    if (ui->cbDeviceSender->currentText() == "Conveyor")
    {
        emit Send(ConnectionManager::CONVEYOR, msg);
    }

    if (ui->cbDeviceSender->currentText() == "Slider")
    {
        emit Send(ConnectionManager::SLIDER, msg);
    }

    if (ui->cbDeviceSender->currentText() == "External MCU")
    {
        emit Send(ConnectionManager::MCU, msg);
    }

    if (ui->cbDeviceSender->currentText() == "Encoder")
    {
        emit Send(ConnectionManager::ENCODER, msg);
    }

	ui->leTerminal->setText("");
}

void RobotWindow::RunExternalScript()
{
//    if (ui->pbRunExternalScript->isChecked() == false)
//    {
//        ExternalScriptProcess->terminate();

//        delete DeltaImageProcesser->PythonTcpClient;

//        DeltaImageProcesser->PythonTcpClient = NULL;

//        return;
//    }

//    QString appPath = QCoreApplication::applicationDirPath();
//    QString command("python");
//    QStringList params = QStringList() << ui->lePythonUrl->text() << "-ip" << ui->lbIP->text() << "-port" << ui->lbLocalPort->text();
//    params << "-type" << ui->cbImageSource->currentText().replace(" ", "");
//    params << "-ow" << QString::number(DeltaImageProcesser->PobjectRec.width);
//    params << "-oh" << QString::number(DeltaImageProcesser->PobjectRec.height);
//    params << "-err" << ui->leObjectErrorSize->text();

//    //QString imageParas = QString("-h %1 -w %2 -c %3").arg(resizeImage.rows).arg(resizeImage.cols).arg(resizeImage.channels());

//    //params << imageParas.split(' ');

//    if (ui->lePythonUrl->text().contains(":") == false)
//        ExternalScriptProcess->start(QString("cd ") + appPath);

//    ExternalScriptProcess->start(command, params);

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
//    DEBUG(DeltaConnectionManager->GetNamePort());
    SoftwareLog(DeltaConnectionManager->GetNamePort());

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
    if (comPort == NULL)
        return false;

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

void RobotWindow::Log(QString msg)
{
    if (msg[msg.length() - 1] != "\n")
        msg += "\n";

    if (ui->teDebug->document()->blockCount() > 200)
        ui->teDebug->setText("");

    ui->teDebug->moveCursor (QTextCursor::End);
    ui->teDebug->insertPlainText(msg);
    ui->teDebug->moveCursor(QTextCursor::End);
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
        plugValue(ui->leRealityPoint2Y, offset.y());

        plugValue(ui->leRealityPoint1X, offset.x());
        plugValue(ui->leRealityPoint1Y, offset.y());

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

    emit Send(ConnectionManager::ROBOT, prefix + para1 + para2);
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
//    SoftwareLog(QString::number(event.button) + ": " + ((event.pressed == true)?"1":"0") + "\n");

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
//    SoftwareLog(QString::number(event.axis) + ": " + QString::number(event.value) + "\n");

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
//    SoftwareLog(QString::number(event.pov) + ": " + QString::number(event.angle) + "\n");

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

    QSize size = ui->gvImageViewer->GetImageSize();
    float ratio = ui->gvImageViewer->GetRatio() * 100;
    ui->lbMatSize->setText(QString("Re: %1x%2").arg(size.width()).arg(size.height()));
    ui->lbDisplayRatio->setText(QString("Ratio: %1%").arg(ratio));
}

void RobotWindow::UseCameraFromPlugin(bool checked)
{
//    if (checked == true)
//    {
//        DeltaImageProcesser->ProcessingImageTimer->stop();

//        DeltaImageProcesser->UpdateRatios();
//    }
//    else
//    {
//        DeltaImageProcesser->ProcessingImageTimer->start();
//    }
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
            SoftwareLog(msg);
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
            }
            else
            {
            // general init
                qRegisterMetaType< cv::Mat >("cv::Mat");
                connect(pluginWidget, SIGNAL(CapturedImage(cv::Mat)), this, SLOT(GetImageFromExternal(cv::Mat)));
                connect(pluginWidget, SIGNAL(StartedCapture()), this, SLOT(GetCapturedSignal()));

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

