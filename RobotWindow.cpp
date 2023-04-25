#include "RobotWindow.h"
#include "ui_RobotWindow.h"

RobotWindow::RobotWindow(QWidget *parent, QString projectName) :
    QMainWindow(parent),
    ui(new Ui::RobotWindow)
{
    ui->setupUi(this);

    this->ProjectName = projectName;

    InitVariables();
    InitOtherThreadObjects();
    InitEvents();

    hideExampleWidgets();
}

RobotWindow::~RobotWindow()
{
    DeviceManagerInstance->thread()->quit();
    DeviceManagerInstance->thread()->wait();

    for (int i = 0; i < TrackingManagerInstance->Trackings.count(); i++)
    {
        TrackingManagerInstance->Trackings[i]->thread()->quit();
        TrackingManagerInstance->Trackings[i]->thread()->wait();
    }

    TrackingManagerInstance->thread()->quit();
    TrackingManagerInstance->thread()->wait();

    ImageProcessingThread->thread()->quit();
    ImageProcessingThread->thread()->wait();

    CameraInstance->thread()->quit();
    CameraInstance->thread()->wait();

    DeltaConnectionManager->thread()->quit();
    DeltaConnectionManager->thread()->wait();


    for (int i = 0; i < GcodeScripts.count(); i++)
    {
        GcodeScripts.at(i)->thread()->quit();
        GcodeScripts.at(i)->thread()->wait();
    }

    delete ui;
}

void RobotWindow::InitOtherThreadObjects()
{

    //------ Device Managers ----------
    DeviceManagerInstance = new DeviceManager();
    DeviceManagerInstance->ProjectName = ProjectName;

    QThread* thread = new QThread(this);
    DeviceManagerInstance->moveToThread(thread);
    connect(thread, &QThread::finished, DeviceManagerInstance, &QObject::deleteLater);
    thread->start();

    QMetaObject::invokeMethod(DeviceManagerInstance, "AddRobot", Qt::QueuedConnection);

    connect(DeviceManagerInstance, SIGNAL(GotDeviceInfo(QString)), this, SLOT(GetDeviceInfo(QString)));
    connect(this, SIGNAL(ChangeDeviceState(int, bool, QString)), DeviceManagerInstance, SLOT(SetDeviceState(int, bool, QString)));
    connect(DeviceManagerInstance, SIGNAL(Log(QString, QString, int)), this, SLOT(UpdateTermite(QString, QString, int)));
    connect(DeviceManagerInstance, SIGNAL(DeviceResponded(QString, QString)), this, SLOT(GetDeviceResponse(QString, QString)));
    connect(this, SIGNAL(Send(int, QString)), DeviceManagerInstance, SLOT(SendGcode(int, QString)));
    //------------ Devices --------

        //-------- Camera --------
    CameraInstance = new Camera();
    CameraInstance->moveToThread(new QThread(this));
    connect(CameraInstance->thread(), &QThread::finished, CameraInstance, &QObject::deleteLater);
    connect(CameraInstance, &Camera::StopCameraRequest, this, &RobotWindow::StopCapture);

    CameraInstance->thread()->start();

    connect(CameraInstance, SIGNAL(GotImage(cv::Mat)), ImageProcessingThread->GetNode("GetImageNode"), SLOT(Input(cv::Mat)));
    connect(&CameraTimer, SIGNAL(timeout()), CameraInstance, SLOT(GeneralCapture()));
    SelectImageProviderOption(0);
        //-------- Robot ---------
    connect(ui->cbSelectedRobot, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedRobot(int)));
    connect(ui->tbDisableRobot, SIGNAL(clicked(bool)), this, SLOT(SetRobotState(bool)));
    connect(ui->tbRequestPosition, SIGNAL(clicked(bool)), this, SLOT(RequestPosition()));
    connect(ui->cbRobotDOF, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRobotDOF(int)));

        //-------- Conveyor --------
    connect(ui->cbSelectedConveyor, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedConveyor(int)));
    connect(ui->pbConveyorConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectConveyor()));
    connect(ui->cbConveyorMode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMode(int)));
    connect(ui->cbConveyorValueType, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));
    connect(ui->leConveyorXPosition, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));
    connect(ui->leConveyorXSpeed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));
    connect(ui->cbConveyorType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeConveyorType(int)));
    ChangeConveyorType(0);

    connect(ui->leSubConveyor1Speed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));
    connect(ui->leSubConveyor2Speed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));
    connect(ui->leSubConveyor3Speed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));

    connect(ui->leSubConveyor1Position, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));
    connect(ui->leSubConveyor2Position, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));
    connect(ui->leSubConveyor3Position, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));

    connect(ui->cbSubConveyor1Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));
    connect(ui->cbSubConveyor2Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));
    connect(ui->cbSubConveyor3Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));

        //-------- Encoder --------
    connect(ui->pbConnectEncoder, SIGNAL(clicked(bool)), this, SLOT(ConnectEncoder()));

    connect(ui->pbReadEncoder, SIGNAL(clicked(bool)), this, SLOT(ReadEncoder()));
    connect(ui->pbSetEncoderInterval, SIGNAL(clicked(bool)), this, SLOT(SetEncoderAutoRead()));
    connect(ui->pbResetEncoder, SIGNAL(clicked(bool)), this, SLOT(ResetEncoderPosition()));
    connect(ui->pbSetEncoderVelocity, SIGNAL(clicked(bool)), this, SLOT(ResetEncoderPosition()));

    connect(ui->cbEncoderType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeEncoderType(int)));

    //-------- Slider --------

    connect(ui->pbSlidingConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectSliding()));
    connect(ui->pbSlidingHome, SIGNAL(clicked(bool)), this, SLOT(GoHomeSliding()));
    connect(ui->pbSlidingDisable, SIGNAL(clicked(bool)), this, SLOT(DisableSliding()));
    connect(ui->leSlidingSpeed, SIGNAL(returnPressed()), this, SLOT(SetSlidingSpeed()));
    connect(ui->leSlidingPosition, SIGNAL(returnPressed()), this, SLOT(SetSlidingPosition()));

        //-------- MCU --------
    connect(ui->pbExternalControllerConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectExternalMCU()));
//    connect(DeltaConnectionManager, SIGNAL(ExternalMCUTransmitText(QString)), this, SLOT(DisplayTextFromExternalMCU(QString)));
    connect(ui->leTransmitToMCU, SIGNAL(returnPressed()), this, SLOT(TransmitTextToExternalMCU()));

    //----- Tracking -----
    InitTrackingThread();
    connect(ui->cbSelectedTracking, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedTracking(int)));


    //----- Gcode Programing----------

    InitGcodeEditorModule();

    //----- Plugin ------
    LoadPlugin();
}

void RobotWindow::InitVariables()
{
    QElapsedTimer time;
    qint64 start = time.elapsed();
    //---------- Connection -----------
    InitConnectionModule();

    //--------- Init Dialog -------------
    CloseDialog = new SmartDialog(this);
    CloseDialog->SetType(CloseDialog->CLOSE_DIALOG);

    //--------- Init Plugin ----------
//    QTimer::singleShot(1000, [this](){
//        LoadPlugin();
//    });

    // ---- Init UI ----
    ui->lbBaudrate->setText(QString::number(DeltaConnectionManager->GetBaudrate()));
    ui->leIP->setText(DeltaConnectionManager->TCPConnection->GetIP());
    ui->lePort->setText(QString::number(DeltaConnectionManager->TCPConnection->Port));

    InitParseNames();

    //---- Init pointer --------
    initInputValueLabels();

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        //------Joystick-----
        joystick = QJoysticks::getInstance();
        joystick->setVirtualJoystickRange(ui->leJoystickRange->text().toDouble());
        joystick->setVirtualJoystickAxisSensibility(ui->leJoystickSensibility->text().toDouble());
        qDebug() << "joystick device: " << joystick->deviceNames();
        ui->cbJoystickDevice->addItems(joystick->deviceNames());
    #endif
#endif



    connect(ui->pbCalculateMappingMatrixTool, SIGNAL(clicked(bool)), this, SLOT(CalculateMappingMatrixTool()));
    connect(ui->pbCalculatePointMatrixTool, SIGNAL(clicked(bool)), this, SLOT(CalculatePointMatrixTool()));
    connect(ui->pbCalculateTestPoint, SIGNAL(clicked(bool)), this, SLOT(CalculateTestPoint()));
    connect(ui->pbCalculateAngle, SIGNAL(clicked(bool)), this, SLOT(CalculateAngle()));

    connect(ui->pbAnglePoint1, &QPushButton::clicked, [=](){ ui->leAnglePoint1X->setText(QString::number(RobotParameter.X)); ui->leAnglePoint1Y->setText(QString::number(RobotParameter.Y)); UpdateRealPositionOfCalibPoints();});
    connect(ui->pbAnglePoint2, &QPushButton::clicked, [=](){ ui->leAnglePoint2X->setText(QString::number(RobotParameter.X)); ui->leAnglePoint2Y->setText(QString::number(RobotParameter.Y)); UpdateRealPositionOfCalibPoints();});

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

    UIEvent = new QTimer(this);
    connect(UIEvent, SIGNAL(timeout()), this, SLOT(ProcessUIEvent()));
    UIEvent->start(500);

    ConvenyorTimer = new QTimer(this);
//    connect(ConvenyorTimer, SIGNAL(timeout()), this, SLOT(GetConvenyorPosition()));

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

    //---------- Object Detector Init -------------

    TrackingObjectTable = new ObjectVariableTable(this);

    ui->gbCameraCalibration->setChecked(false);
    ui->gbCameraObject->setChecked(false);
    ui->gbCameraVariable->setChecked(false);

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

    //------------------- Linux -----------------


    //----- Process ------
//    ExternalScriptProcess = new QProcess(this);

    LoadSettings();
}

void RobotWindow::InitConnectionModule()
{
    DeltaConnectionManager = new ConnectionManager();
    DeltaConnectionManager->moveToThread(new QThread(this));

    DeltaConnectionManager->thread()->start();

    DeltaConnectionManager->SetBaudrate(DefaultBaudrate);


//    connect(this, &RobotWindow::Send, DeltaConnectionManager, &ConnectionManager::Send);

    connect(this, &RobotWindow::ScanAndConnectRobot, DeltaConnectionManager, &ConnectionManager::FindDeltaRobot);
    connect(this, &RobotWindow::DisconnectRobot, DeltaConnectionManager, &ConnectionManager::DisconnectRobot);
    connect(DeltaConnectionManager->thread(), SIGNAL(finished()), DeltaConnectionManager, SLOT(deleteLater()));

    connect(DeltaConnectionManager, SIGNAL(Log(QString)), this, SLOT(UpdateTermite(QString)));

    connect(DeltaConnectionManager, SIGNAL(ReceiveInputIO(QString)), this, SLOT(GetValueInput(QString)));

    connect(DeltaConnectionManager, SIGNAL(DeltaResponeReady()), this, SLOT(NoticeConnected()));
    connect(DeltaConnectionManager, SIGNAL(InHomePosition(float, float, float, float, float, float)), this, SLOT(ReceiveHomePosition(float, float, float, float, float, float)));

    connect(DeltaConnectionManager, SIGNAL(RequestVariableValue(QIODevice*, QString)), this, SLOT(RespondVariableValue(QIODevice*, QString)));

    connect(DeltaConnectionManager, SIGNAL(ReceiveRequestsFromExternal(QString)), this, SLOT(ExecuteRequestsFromExternal(QString)));


    connect(DeltaConnectionManager, SIGNAL(ReceiveObjectInfoFromExternalAI(QString)), this, SLOT(ProcessDetectedObjectFromExternalAI(QString)));
//    connect(DeltaConnectionManager, SIGNAL(ExternalScriptOpened(QTcpSocket*)), DeltaImageProcesser, SLOT(GetExternalScriptSocket(QTcpSocket*)));
    connect(DeltaConnectionManager, SIGNAL(ReceiveDisplayObjectFromExternalScript(QString)), this, SLOT(AddDisplayObjectFromExternalScript(QString)));

//    connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceivePosition(float, float, float, float, float, float)), this, SLOT(UpdateTextboxFrom3DControl(float, float, float, float, float, float)));

//    connect(DeltaConnectionManager->TCPConnection, SIGNAL(ReceiveOk()), this, SLOT(ROSResponse()));

    connect(DeltaConnectionManager, SIGNAL(FinishFindingRobot()), this, SLOT(CloseLoadingPopup()));

    connect(DeltaConnectionManager, SIGNAL(ReceivedEncoderPosition(float)), this, SLOT(ProcessEncoderValue(float)));



//    connect(DeltaConnectionManager, SIGNAL(ReceiveCaptureSignalFromExternalAI()), Encoder1, SLOT(MarkPosition()));

    // ---------- Server ---------
    connect(ui->tbServerConfig, &QPushButton::clicked, [=](bool checked)
    {
        ui->leIP->setFrame(true);
        ui->leIP->setReadOnly(false);
        ui->lePort->setFrame(true);
        ui->lePort->setReadOnly(false);
    });

    connect(ui->leIP, &QLineEdit::returnPressed, [=]()
    {
        ui->leIP->setFrame(false);
        ui->lePort->setFrame(false);
        ui->leIP->setReadOnly(true);
        ui->lePort->setReadOnly(true);
    });
    connect(ui->lePort, &QLineEdit::returnPressed, [=]()
    {
        ui->leIP->setFrame(false);
        ui->lePort->setFrame(false);
        ui->leIP->setReadOnly(true);
        ui->lePort->setReadOnly(true);
    });
}

void RobotWindow::InitObjectDetectingModule()
{
    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< cv::Size >("cv::Size");
    qRegisterMetaType< Object >("Object");
    qRegisterMetaType< QList<Object>* >("QList<Object>*");
    qRegisterMetaType< QList<Object> >("QList<Object>&");
    qRegisterMetaType< QList<int> >("QList<int>");

    // ---------- Image Processing Thread ---------

    ImageProcessingThread = new ImageProcessing();
    ImageProcessingThread->ProjectName = ProjectName;
    ImageProcessingThread->MoveToThread(new QThread(this));
    connect(ImageProcessingThread->thread(), &QThread::finished, ImageProcessingThread, &QObject::deleteLater);

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
    ParameterPanel->ProjectName = ProjectName;

    // ---------- Main UI -------
//    connect(ui->cbImageOutput, SIGNAL(currentTextChanged(QString)), this, SLOT(ChangeOutputDisplay()));
    connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), this, SLOT(LoadWebcam()));
    connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), this, SLOT(LoadImages()));
    connect(ui->cbDetectingAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectObjectDetectingAlgorithm(int)));

    ui->cbDetectingAlgorithm->setCurrentIndex(0);
    SelectObjectDetectingAlgorithm(0);

    ui->gvImageViewer->ProjectName = ProjectName;

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

        ui->pbCapture->clicked();

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

    ui->pbWarpTool->click();

    connect(ui->pbFilterTool, SIGNAL(clicked(bool)), this, SLOT(OpenColorFilterWindow()));
    connect(ui->pbViewDataObjects, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
    connect(ui->pbClearObject, &QPushButton::clicked, [=](bool checked)
    {
        QMetaObject::invokeMethod(ImageProcessingThread->GetNode("TrackingObjectsNode"), "ClearVariable", Qt::QueuedConnection, Q_ARG(QString, "outputObjects"));
        QTimer::singleShot(300, [this](){
            ui->pbCapture->clicked();
        });
    });
    connect(ui->pbOpenObjectTable, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
    connect(ui->pbClearDetectObjects, &QPushButton::clicked, ui->pbClearObject, &QPushButton::clicked);

    connect(TrackingObjectTable, SIGNAL(TakeObjectPosition(float, float, float)), this, SLOT(MoveRobotFollowObject(float, float, float)));

    connect(ui->gvImageViewer, &ImageViewer::selectedNoTool, this, &RobotWindow::UnselectToolButtons);

    connect(ui->gvImageViewer, &ImageViewer::changedPoints, this, &RobotWindow::GetCalibPointsFromImage);
    connect(ui->gvImageViewer, &ImageViewer::changedRect, this, &RobotWindow::GetObjectSizeFromImage);
    connect(ui->gvImageViewer, &ImageViewer::changedMappingPoint, this, &RobotWindow::GetMappingPointFromImage);

    connect(ui->leRealityPoint1X, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint1Y, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint2X, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint2Y, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);

    connect(ui->leObjectOverlay, &QLineEdit::returnPressed,
    [=] (){
        QMetaObject::invokeMethod(ImageProcessingThread->GetNode("TrackingObjectsNode"), "Input", Qt::QueuedConnection, Q_ARG(float, ui->leObjectOverlay->text().toFloat()));
    });

    // ---------- Image Provider -------

    connect(ImageProcessingThread->thread(), SIGNAL(finished()), ImageProcessingThread, SLOT(deleteLater()));

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

    connect(this, SIGNAL(GotObjects(QList<Object>&)), ImageProcessingThread->GetNode("VisibleObjectsNode"), SLOT(Input(QList<Object>&)));

    connect(this, SIGNAL(GotMappingMatrix(QMatrix)), ImageProcessingThread->GetNode("VisibleObjectsNode"), SLOT(Input(QMatrix)));
    connect(this, SIGNAL(GotOjectFilterInfo(Object)), ImageProcessingThread->GetNode("GetObjectsNode"), SLOT(Input(Object)));

    connect(ImageProcessingThread->GetNode("VisibleObjectsNode"), SIGNAL(HadOutput(QList<Object>&)), this, SLOT(UpdateObjectsToImageViewer(QList<Object>&)));
    connect(ImageProcessingThread->GetNode("GetObjectsNode"), &TaskNode::Done, [=]()
    {
        int id = ui->cbEncoderForCamera->currentText().toInt();
        QMetaObject::invokeMethod(TrackingManagerInstance, "SaveDetectPosition", Qt::QueuedConnection, Q_ARG(int, id));
    });

    connect(ImageProcessingThread->GetNode("TrackingObjectsNode"), SIGNAL(HadOutput(QList<Object>&)), TrackingObjectTable, SLOT(UpdateTable(QList<Object>&)));
    QTimer::singleShot(1000, [this](){
        connect(ImageProcessingThread->GetNode("TrackingObjectsNode"), SIGNAL(Done()), TrackingManagerInstance, SLOT(OnDoneUpdateTracking()));
    });
    RearrangeTaskFlow();

    ImageProcessingThread->thread()->start();    

    ParameterPanel->RequestValue();

    // ----------- init para ----------
    emit GotResizePara(cv::Size(ui->leImageWidth->text().toInt(), ui->leImageHeight->text().toInt()));

    // --------- init gcode script -----
}

void RobotWindow::InitGcodeEditorModule()
{
    // ------- Script ---------
    InitScriptThread();
    connect(ui->cbProgramThreadID, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedEditorThread(int)));

    //----- Gcode Editor -----
    highlighter = new GCodeHighlighter(ui->pteGcodeArea->document());

    // ------- Gcode Explorer -----

    QString openPath = QCoreApplication::applicationDirPath() + "/gcode";

    QDir dir(openPath);
    if (!dir.exists())
        dir.mkpath(openPath);

    ui->leGcodeExplorer->setText(openPath);

    explorerModel.setRootPath(QDir::currentPath());
    ui->tvGcodeExplorer->setModel(&explorerModel);
    ui->tvGcodeExplorer->setRootIndex(explorerModel.index(openPath));

    ui->tvGcodeExplorer->setHeaderHidden(true); // Hiển thị header
    ui->tvGcodeExplorer->header()->setSectionResizeMode(0, QHeaderView::Stretch); // Chỉnh độ rộng cột
    ui->tvGcodeExplorer->header()->setSectionHidden(1, true); // Ẩn cột Size
    ui->tvGcodeExplorer->header()->setSectionHidden(2, true); // Ẩn cột Type
    ui->tvGcodeExplorer->header()->setSectionHidden(3, true); // Ẩn cột Type

    QObject::connect(ui->tvGcodeExplorer, &QTreeView::clicked, this, &RobotWindow::LoadGcodeFromFileToEditor);

    QObject::connect(ui->tbBackGcodeFolder, &QPushButton::clicked, this, &RobotWindow::BackParentExplorer);

    QObject::connect(ui->tbNewGcodeFile, &QPushButton::clicked, this, &RobotWindow::CreateNewGcodeFile);

    QObject::connect(ui->tbOpenGcodePath, &QPushButton::clicked, this, &RobotWindow::SelectGcodeExplorer);

    QObject::connect(ui->tbRefreshExplorer, &QPushButton::clicked, this, &RobotWindow::RefreshExplorer);

    QObject::connect(ui->tbDeleteGcodeFile, &QPushButton::clicked, this, &RobotWindow::DeleteGcodeFile);

    QObject::connect(ui->pbCreateNewGcode, &QPushButton::clicked, this, &RobotWindow::CreateNewGcodeFile);
}

void RobotWindow::InitUIController()
{
    connect(ui->pbConnect, &QPushButton::clicked, this, [=]()
    {
        OpenLoadingPopup();
        emit ChangeDeviceState(DeviceManager::ROBOT, (ui->pbConnect->text() == "Connect")?true:false, "auto");
    });

    connect(&UpdateUITimer, &QTimer::timeout, this, &RobotWindow::UpdateRobotPositionToUI);
    UpdateUITimer.start(100);

    connect(ui->pbHome, &QPushButton::clicked, this, [=](){emit Send(DeviceManager::ROBOT, "G28");});

    connect(ui->leX, &QLineEdit::returnPressed, this, [=](){RobotParameter.X = ui->leX->text().toFloat(); UpdateVariable("X", QString::number(RobotParameter.X)); emit Send(DeviceManager::ROBOT, QString("G01 X") + ui->leX->text());});
    connect(ui->leY, &QLineEdit::returnPressed, this, [=](){RobotParameter.Y = ui->leY->text().toFloat(); UpdateVariable("Y", QString::number(RobotParameter.Y));emit Send(DeviceManager::ROBOT, QString("G01 Y") + ui->leY->text());});
    connect(ui->leZ, &QLineEdit::returnPressed, this, [=](){RobotParameter.Z = ui->leZ->text().toFloat(); UpdateVariable("Z", QString::number(RobotParameter.Z));emit Send(DeviceManager::ROBOT, QString("G01 Z") + ui->leZ->text());});
    connect(ui->leW, &QLineEdit::returnPressed, this, [=](){RobotParameter.W = ui->leW->text().toFloat(); UpdateVariable("W", QString::number(RobotParameter.W));emit Send(DeviceManager::ROBOT, QString("G01 W") + ui->leW->text());});
    connect(ui->leU, &QLineEdit::returnPressed, this, [=](){RobotParameter.U = ui->leU->text().toFloat(); UpdateVariable("U", QString::number(RobotParameter.U));emit Send(DeviceManager::ROBOT, QString("G01 U") + ui->leU->text());});
    connect(ui->leV, &QLineEdit::returnPressed, this, [=](){RobotParameter.V = ui->leV->text().toFloat(); UpdateVariable("V", QString::number(RobotParameter.V));emit Send(DeviceManager::ROBOT, QString("G01 V") + ui->leV->text());});

    connect(ui->vsZAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.Z = RobotParameter.ZHome - value;});
    connect(ui->vsZAdjsution, &QSlider::sliderReleased, [=](){emit Send(DeviceManager::ROBOT, QString("G01 Z%1").arg(RobotParameter.Z));});
    connect(ui->vsAngleAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.W = value;});
    connect(ui->vsAngleAdjsution, &QSlider::sliderReleased, [=](){emit Send(DeviceManager::ROBOT, QString("G01 W%1").arg(RobotParameter.W));});
    connect(ui->vs5AxisAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.U = value;});
    connect(ui->vs5AxisAdjsution, &QSlider::sliderReleased, [=](){emit Send(DeviceManager::ROBOT, QString("G01 U%1").arg(RobotParameter.U));});
    connect(ui->vs6AxisAdjsution, &QSlider::valueChanged, [=](int value){RobotParameter.V = value;});
    connect(ui->vs6AxisAdjsution, &QSlider::sliderReleased, [=](){emit Send(DeviceManager::ROBOT, QString("G01 V%1").arg(RobotParameter.V));});

    connect(Delta2DVisualizer, &DeltaVisualizer::CursorMoved, [=](float x, float y){RobotParameter.X = x; RobotParameter.Y = y; emit Send(DeviceManager::ROBOT, QString("G01 X%1 Y%2").arg(x).arg(y));});

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
    connect(ui->pbCalibPoint1, &QPushButton::clicked, [=](){ ui->leRealityPoint1X->setText(QString::number(RobotParameter.X)); ui->leRealityPoint1Y->setText(QString::number(RobotParameter.Y)); UpdateRealPositionOfCalibPoints();});
    connect(ui->pbCalibPoint2, &QPushButton::clicked, [=](){ ui->leRealityPoint2X->setText(QString::number(RobotParameter.X)); ui->leRealityPoint2Y->setText(QString::number(RobotParameter.Y)); UpdateRealPositionOfCalibPoints();});
    connect(ui->pbImageMapping, &QPushButton::clicked, this, &RobotWindow::UpdateRealPositionOfCalibPoints);

}

void RobotWindow::InitEvents()
{
    // -------- Debug Log --------
//    connect(ui->tbExpandLogBox, &QToolButton::toggled, this, &RobotWindow::ExpandLogBox);


    // ------------- --------------
    connect(ui->pbSaveGcode, SIGNAL(clicked(bool)), this, SLOT(SaveProgram()));

    connect(ui->pbExecuteGcodes, SIGNAL(clicked(bool)), this, SLOT(ExecuteProgram()));
	connect(ui->pteGcodeArea, SIGNAL(cursorPositionChanged()), this, SLOT(ExecuteCurrentLine()));

    // ------------ Jogging -----------

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

    connect(ui->cbDx, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));
    connect(ui->cbRx, SIGNAL(clicked(bool)), this, SLOT(SetOnOffOutput(bool)));

//    connect(ui->leP0Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
//    connect(ui->leP1Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
//    connect(ui->lePxValue, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));

//    connect(ui->leS0Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
//    connect(ui->leS1Value, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));
//    connect(ui->leSxValue, SIGNAL(returnPressed()), this, SLOT(SetValueOutput()));

    connect(ui->pbReadI0, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI1, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI2, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI3, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadIx, SIGNAL(clicked()), this, SLOT(RequestValueInput()));

    connect(ui->pbReadA0, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadA1, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadAx, SIGNAL(clicked()), this, SLOT(RequestValueInput()));


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
//	connect(ui->pbTurnOnROS, SIGNAL(clicked(bool)), this, SLOT(OpenROS()));
//	connect(ui->cbROSCameraView, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeROSCameraView(int)));
//	connect(ui->cbEndEffector, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeEndEffector(int)));
//	connect(ui->cbRobotVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRobotVersion(int)));
//	connect(ui->btDeleteAllObjects, SIGNAL(clicked(bool)), this, SLOT(DeleteAllObjectsInROS()));
//	connect(ui->pbClearDetectObjects, SIGNAL(clicked(bool)), this, SLOT(DeleteAllObjectsInROS()));

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        //------------- Joystick -----------
        connect(joystick, SIGNAL(buttonEvent (const QJoystickButtonEvent&)), SLOT(ProcessJoystickButton(const QJoystickButtonEvent&)));
//        connect(joystick, SIGNAL(axisEvent(const QJoystickAxisEvent&)), SLOT(ProcessJoystickAxis(const QJoystickAxisEvent&)));
        connect(joystick, SIGNAL(POVEvent(const QJoystickPOVEvent&)), SLOT(ProcessJoystickPOV(const QJoystickPOVEvent&)));
    #endif
#endif
    //------------- Terminal ---------------
	connect(ui->leTerminal, SIGNAL(returnPressed()), this, SLOT(TerminalTransmit()));

    //------------- Connection --------------

    //------------- Gcode Editor -------------
	connect(ui->pbFormat, SIGNAL(clicked(bool)), this, SLOT(StandardFormatEditor()));
    connect(ui->cbEditGcodeEditor, SIGNAL(clicked(bool)), ui->pteGcodeArea, SLOT(setLockState(bool)));

    //------------ Image Processing -----------


    connect(ui->pbRunExternalScript, SIGNAL(clicked(bool)), this, SLOT(RunExternalScript()));
    connect(ui->pbExternalScriptOpen, SIGNAL(clicked(bool)), this, SLOT(OpenExternalScriptFolder()));

    connect(ui->cbSourceForImageProvider, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectImageProviderOption(int)));

    // ---- Setting ----

    //----------- Camera -----------


    //---------- Menu -----------
	connect(ui->actionBaudrate, SIGNAL(triggered()), this, SLOT(ConfigConnection()));
	connect(ui->actionGcode, SIGNAL(triggered()), this, SLOT(OpenGcodeReference()));
    connect(ui->pbOpenGcodeDocs, SIGNAL(clicked(bool)), this, SLOT(OpenGcodeReference()));

	connect(ui->actionExecute_All, SIGNAL(triggered()), this, SLOT(ExecuteSelectPrograms()));
	connect(ui->actionExecute, SIGNAL(triggered()), this, SLOT(ExecuteProgram()));
    connect(ui->actionScale, SIGNAL(triggered(bool)), this, SLOT(ScaleUI()));

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

    // ------ Ui to Detector ----
    connect(ui->pbCapture, &QPushButton::clicked, CameraInstance, &Camera::GeneralCapture);
    connect(ui->pbStartAcquisition, &QPushButton::clicked, this, &RobotWindow::StartContinuousCapture);
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
                ui->leConveyorXPosition->setText(paras[i + 2]);
                emit ui->leConveyorXPosition->returnPressed();
            }
        }

        if (paras[i] == "Update")
        {
            if (paras[i + 1] == "ConveyorCalibPoint1")
            {

            }
            if (paras[i + 1] == "ConveyorCalibPoint2")
            {

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

                emit Send(DeviceManager::ROBOT, gcode);
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

void RobotWindow::LoadGcodeFromFileToEditor(const QModelIndex &index)
{
    if (ui->pbExecuteGcodes->isChecked() == true)
    {
        ui->pbExecuteGcodes->click();
    }

    SaveProgram();

    QString filePath = explorerModel.filePath(index);
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString content = stream.readAll();
        ui->pteGcodeArea->setPlainText(content);

        int threadId = ui->cbProgramThreadID->currentIndex();
        GcodeScripts.at(threadId)->SetGcodeScript(content);
        GcodeScripts.at(threadId)->SetProgramPath(filePath);

        file.close();
    }
}

void RobotWindow::SelectGcodeExplorer()
{
    QString path = QApplication::applicationDirPath() + "/gcode";

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open G-code program directory"),
                                                 path,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    if (dir != "")
    {
        ui->leGcodeExplorer->setText(dir);
        ui->tvGcodeExplorer->setRootIndex(explorerModel.index(dir));
    }
}

void RobotWindow::BackParentExplorer()
{
    QModelIndex rootIndex = ui->tvGcodeExplorer->rootIndex();
    QModelIndex parentIndex = rootIndex.parent();
    if (parentIndex.isValid())
    {
        ui->tvGcodeExplorer->setRootIndex(parentIndex);
    }
}

void RobotWindow::CreateNewGcodeFile()
{
    QString fileName = QInputDialog::getText(this, "Enter the file name you want to create", "Gcode file name:", QLineEdit::Normal, "");
    // Lấy đường dẫn đến thư mục đang chọn trên dir view

    if (fileName == "")
        return;

    QString content = "G28\n";

    SaveGcodeFile(fileName, content);
}

void RobotWindow::SaveGcodeFile(QString fileName, QString content)
{
    QModelIndex index = ui->tvGcodeExplorer->currentIndex();
    QString path = explorerModel.filePath(index);

    if (path == "")
    {
        path = ui->leGcodeExplorer->text();
    }
    else
    {
        QFileInfo fileInfo(path);
        if (fileInfo.isFile())
            path = fileInfo.absolutePath();
    }

    // Tạo đối tượng QFile để tạo file mới và mở file để viết dữ liệu vào
    QFile file(path + QString("/") + fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << content;
        file.close();
    }
}

void RobotWindow::RefreshExplorer()
{
    ui->tvGcodeExplorer->setRootIndex(explorerModel.index(ui->leGcodeExplorer->text()));
}

void RobotWindow::DeleteGcodeFile()
{
    int ret = QMessageBox::warning(this, tr("Delete file"), tr("Are you sure you want to delete this file?"), QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        QString filePath = explorerModel.filePath(ui->tvGcodeExplorer->currentIndex());
        QFile file(filePath);
        if (file.remove())
        {

        } else
        {

        }
    } else
    {

    }

}

void RobotWindow::ChangeSelectedEditorThread(int id)
{
    if (ui->cbProgramThreadID->currentText() == "+")
    {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->cbProgramThreadID->model());
        QStandardItem *item = model->item(id);
        item->setText(QString::number(id));

        AddScriptThread();

        ui->cbProgramThreadID->addItem("+");
    }

    LoadScriptThread();
}

void RobotWindow::SetRobotState(bool isHold)
{
    if (isHold == false)
    {
        emit Send(DeviceManager::ROBOT, "M84");
    }
    else
    {
        emit Send(DeviceManager::ROBOT, "M85");
    }
}

void RobotWindow::RequestPosition()
{
    emit Send(DeviceManager::ROBOT, "Position");
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

void RobotWindow::InitScriptThread()
{
    AddScriptThread();
}

void RobotWindow::AddScriptThread()
{
    GcodeScript* GcodeScriptThread = new GcodeScript();

    GcodeScriptThread->ProjectName = ProjectName;
    GcodeScriptThread->ID = QString("thread") + GcodeScripts.count();
    GcodeScriptThread->moveToThread(new QThread(this));

    connect(GcodeScriptThread->thread(), SIGNAL(finished()), GcodeScriptThread, SLOT(deleteLater()));
    connect(DeviceManagerInstance, SIGNAL(DeviceResponded(QString, QString)), GcodeScriptThread, SLOT(GetResponse(QString, QString)));
    connect(DeltaConnectionManager, SIGNAL(FailTransmit()), GcodeScriptThread, SLOT(TransmitNextGcode()));

    connect(GcodeScriptThread, SIGNAL(Moved(int)), this, SLOT(HighLineCurrentLine(int)));
    connect(GcodeScriptThread, SIGNAL(SendGcodeToDevice(QString, QString)), DeviceManagerInstance, SLOT(SendGcode(QString, QString)));
    connect(GcodeScriptThread, &GcodeScript::Finished, [=](){ ui->pbExecuteGcodes->setChecked(false);});
    connect(GcodeScriptThread, SIGNAL(SendGcodeToDevice(QString, QString)), this, SLOT(UpdateGcodeValueToDeviceUI(QString, QString)));
    connect(GcodeScriptThread, SIGNAL(SaveVariable(QString, QString)), this, SLOT(UpdateVariable(QString, QString)));

//    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects()), this, SLOT(ClearObjectsToVariableTable()));
//    connect(GcodeScriptThread, SIGNAL(DeleteObject1()), this, SLOT(DeleteFirstVariable()));
    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects()), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(ClearOutput()));
    connect(GcodeScriptThread, SIGNAL(DeleteObject(int)), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(DeleteOutput(int)));

    connect(GcodeScriptThread, &GcodeScript::PauseCamera, [=](){ CameraTimer.stop();});
    connect(GcodeScriptThread, &GcodeScript::ResumeCamera, [=](){ CameraTimer.start(ui->leCaptureInterval->text().toInt());});
    connect(GcodeScriptThread, &GcodeScript::CaptureCamera, CameraInstance, &Camera::GeneralCapture);

    connect(GcodeScriptThread, &GcodeScript::UpdateTrackingRequest, TrackingManagerInstance, &TrackingManager::UpdateTracking);

    GcodeScriptThread->thread()->start();

    GcodeScripts.append(GcodeScriptThread);
}

void RobotWindow::LoadScriptThread()
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    ui->pteGcodeArea->setPlainText(GcodeScripts.at(threadId)->GetGcodeScript());
    ui->pbExecuteGcodes->setChecked(GcodeScripts.at(threadId)->IsRunning());
}

void RobotWindow::InitTrackingThread()
{
    TrackingManagerInstance = new TrackingManager();
    QThread* thread = new QThread(this);
    TrackingManagerInstance->moveToThread(thread);
    connect(thread, &QThread::finished, TrackingManagerInstance, &QObject::deleteLater);
    connect(DeviceManagerInstance, SIGNAL(GotEncoderPosition(int , float)), TrackingManagerInstance, SLOT(SetEncoderPosition(int, float)));
    thread->start();

    AddTrackingThread();

    connect(TrackingManagerInstance->Trackings[0], SIGNAL(GotCaptureDetectOffset(QPointF)), ImageProcessingThread->GetNode("VisibleObjectsNode"), SLOT(Input(QPointF)));
}

void RobotWindow::AddTrackingThread()
{
    Tracking* tracking = new Tracking();
    QThread* trackingThread = new QThread(this);
    tracking->moveToThread(trackingThread);
    connect(tracking->thread(), &QThread::finished, tracking, &QObject::deleteLater);

    connect(ui->leDeviationAngle, &QLineEdit::returnPressed, [=](){tracking->DeviationAngle = ui->leDeviationAngle->text().toFloat();});
    tracking->DetectDelayOffsetPoint = ImageProcessingThread->GetNode("VisibleObjectsNode")->GetInputPointPointer();
    connect(tracking, SIGNAL(DistanceMoved(QPointF)), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(Input(QPointF)));
    connect(tracking, SIGNAL(SendGcodeRequest(QString, QString)), DeviceManagerInstance, SLOT(SendGcode(QString, QString)));

    trackingThread->start();

    tracking->ID = TrackingManagerInstance->Trackings.count();
    TrackingManagerInstance->Trackings.append(tracking);
}

void RobotWindow::LoadTrackingThread()
{
    int id = ui->cbSelectedTracking->currentIndex();
    ui->leSelectedTrackingObjectList->setText(TrackingManagerInstance->Trackings.at(id)->ListName);
    ui->cbTrackingEncoderSource->setCurrentText(QString::number(TrackingManagerInstance->Trackings.at(id)->EncoderID));
    ui->cbTrackingDirection->setCurrentText(TrackingManagerInstance->Trackings.at(id)->Direction);
    ui->leDeviationAngle->setText(QString::number(TrackingManagerInstance->Trackings.at(id)->DeviationAngle));

}

void RobotWindow::LoadSettings()
{    
    //------ Image Detecting Module -----
    ui->gvImageViewer->LoadSetting();
    QPointF calibPoint1 = VarManager::getInstance()->getVar("RealCalibPoint1").toPointF();
    QPointF calibPoint2 = VarManager::getInstance()->getVar("RealCalibPoint2").toPointF();
    ui->leRealityPoint1X->setText(QString::number(calibPoint1.x()));
    ui->leRealityPoint1Y->setText(QString::number(calibPoint1.y()));
    ui->leRealityPoint2X->setText(QString::number(calibPoint2.x()));
    ui->leRealityPoint2Y->setText(QString::number(calibPoint2.y()));

    UpdateRealPositionOfCalibPoints();

    //------------
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

    UpdateVariable("O0.X", QString::number(NULL_NUMBER));
    UpdateVariable("O0.Y", QString::number(NULL_NUMBER));
    UpdateVariable("O0.A", QString::number(NULL_NUMBER));
    UpdateVariable("O0.W", QString::number(NULL_NUMBER));
    UpdateVariable("O0.L", QString::number(NULL_NUMBER));

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
//        if (DeltaConnectionManager->RobotPort->open((QIODevice::ReadWrite)) == true)
//        {
//            connect(DeltaConnectionManager->RobotPort, SIGNAL(readyRead()), DeltaConnectionManager, SLOT(ReadData()));
//            ui->pbConnect->setText("Disconnect");
//        }
    }

    ui->lbComName->setText(comName);
    ui->lbBaudrate->setText(QString::number(defaultBaudrate));
    ui->cbRobotModel->setCurrentText(setting->value("RobotModel").toString());

    DeltaConnectionManager->RobotPort->setBaudRate(ui->lbBaudrate->text().toInt());
    DeltaConnectionManager->RobotPort->setPortName(ui->lbComName->text());
    DeltaConnectionManager->TCPConnection->ServerName = ui->lbComName->text();
    DeltaConnectionManager->TCPConnection->Port = ui->lePort->text().toInt();

    GcodeScripts.at(ui->cbProgramThreadID->currentIndex())->ProjectName = ProjectName;

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
    ui->leConveyorXPosition->setText(setting->value("MovingValue").toString());

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


    ui->leCaptureInterval->setText(setting->value("WebcamInterval", ui->leCaptureInterval->text()).toString());

    ui->leImageWidth->setText(setting->value("ResizeWidth", ui->leImageWidth->text()).toString());
    ui->leImageHeight->setText(setting->value("ResizeHeight", ui->leImageHeight->text()).toString());

    emit GotResizePara(cv::Size(ui->leImageWidth->text().toInt(), ui->leImageHeight->text().toInt()));

    Object& obj = ImageProcessingThread->GetNode("GetObjectsNode")->GetInputObject();

    obj.Width.Image = setting->value("ObjectWidth", obj.Width.Image).toFloat();
    obj.Length.Image = setting->value("ObjectLength", obj.Length.Image).toFloat();

    obj.Width.Real = setting->value("RealObjectWidth", ui->leWRec->text()).toFloat();
    obj.Length.Real = setting->value("RealObjectLength", ui->leLRec->text()).toFloat();


    obj.RangeWidth.Max.Image = setting->value("ImageMaxObjectWidth", ui->leMaxWRec->text()).toFloat();
    obj.RangeWidth.Min.Image = setting->value("ImageMinObjectWidth", ui->leMinWRec->text()).toFloat();
    obj.RangeLength.Max.Image = setting->value("ImageMaxObjectLength", ui->leMaxLRec->text()).toFloat();
    obj.RangeLength.Min.Image = setting->value("ImageMinObjectLength", ui->leMinLRec->text()).toFloat();

    ui->leWRec->setText(QString::number(obj.Width.Real));
    ui->leLRec->setText(QString::number(obj.Length.Real));


    obj.RangeWidth.Max.Real = setting->value("MaxObjectWidth", ui->leMaxWRec->text()).toFloat();
    obj.RangeWidth.Min.Real = setting->value("MinObjectWidth", ui->leMinWRec->text()).toFloat();
    obj.RangeLength.Max.Real = setting->value("MaxObjectLength", ui->leMaxLRec->text()).toFloat();
    obj.RangeLength.Min.Real = setting->value("MinObjectLength", ui->leMinLRec->text()).toFloat();

    ui->leMinWRec->setText(QString::number(obj.RangeWidth.Min.Real));
    ui->leMaxWRec->setText(QString::number(obj.RangeWidth.Max.Real));
    ui->leMinLRec->setText(QString::number(obj.RangeLength.Min.Real));
    ui->leMaxLRec->setText(QString::number(obj.RangeLength.Max.Real));

    emit GotOjectFilterInfo(obj);

    ui->leObjectOverlay->setText(setting->value("TrackingError", ui->leObjectOverlay->text()).toString());


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

    ParameterPanel->RequestValue();

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
    for (int i = 0; i < DeviceManagerInstance->Robots.count(); i++)
    {
        setting->setValue("ComName", DeviceManagerInstance->Robots.at(i)->GetSerialPortName());
        setting->setValue("DefaultBaudrate", DeviceManagerInstance->Robots.at(i)->GetSerialPortBaudrate());
        setting->setValue("RobotModel", ui->cbRobotModel->currentText());
        setting->setValue("RobotState", DeviceManagerInstance->Robots.at(i)->IsOpen());
    }

    setting->setValue("IP", DeltaConnectionManager->TCPConnection->GetIP());
    setting->setValue("TCPPort", DeltaConnectionManager->TCPConnection->Port);

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
    setting->setValue("MovingValue", ui->leConveyorXPosition->text());

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


    setting->endGroup();
}

void RobotWindow::SaveObjectDetectorSetting(QSettings *setting)
{
    setting->beginGroup("ObjectDetector");



    setting->setValue("WarpEnable", ui->pbWarpTool->isChecked());
    setting->setValue("DisplayOutput", ui->cbImageOutput->currentText());


//----------
    setting->setValue("ImageSource", ui->cbSourceForImageProvider->currentText());

    setting->setValue("WebcamInterval", ui->leCaptureInterval->text());

    setting->setValue("ResizeWidth", ui->leImageWidth->text());
    setting->setValue("ResizeHeight", ui->leImageHeight->text());

    Object& obj = ImageProcessingThread->GetNode("GetObjectsNode")->GetInputObject();

    setting->setValue("ObjectWidth", obj.Width.Image);
    setting->setValue("ObjectLength", obj.Length.Image);

    setting->setValue("ImageMinObjectWidth", obj.RangeWidth.Min.Image);
    setting->setValue("ImageMaxObjectWidth", obj.RangeWidth.Max.Image);
    setting->setValue("ImageMinObjectLength", obj.RangeLength.Min.Image);
    setting->setValue("ImageMaxObjectLength", obj.RangeLength.Max.Image);

    setting->setValue("RealObjectWidth", ui->leWRec->text());
    setting->setValue("RealObjectLength", ui->leLRec->text());


    setting->setValue("MinObjectWidth", ui->leMinWRec->text());
    setting->setValue("MaxObjectWidth", ui->leMaxWRec->text());
    setting->setValue("MinObjectLength", ui->leMinLRec->text());
    setting->setValue("MaxObjectLength", ui->leMaxLRec->text());

    setting->setValue("TrackingError", ui->leObjectOverlay->text());

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
    connect(ui->twDevices, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(MaximizeTab(int)));
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

void RobotWindow::GetDeviceInfo(QString json)
{
    CloseLoadingPopup();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    int id = jsonObject.value("id").toInt();
    QString device = jsonObject.value("device").toString();

    if (device == "robot" && id == ui->cbSelectedRobot->currentText().toInt())
    {
        float x = jsonObject.value("x").toDouble();
        float y = jsonObject.value("y").toDouble();
        float z = jsonObject.value("z").toDouble();
        float w = jsonObject.value("w").toDouble();
        float u = jsonObject.value("u").toDouble();
        float v = jsonObject.value("v").toDouble();

        ReceiveHomePosition(x, y, z, w, u, v);

        QString state = jsonObject.value("state").toString();
        if (state == "open")
        {
            ui->pbConnect->setText("Disconnect");
        }
        else
        {
            ui->pbConnect->setText("Connect");
        }

        ui->lbComName->setText(jsonObject.value("com_name").toString());

    }

    else if (device == "device" && id == ui->cbSelectedDevice->currentText().toInt())
    {

        QString state = jsonObject.value("state").toString();
        if (state == "open")
        {
            ui->pbExternalControllerConnect->setText("Disconnect");
        }
        else
        {
            ui->pbExternalControllerConnect->setText("Connect");
        }

        ui->lbExternalCOMName->setText(jsonObject.value("com_name").toString());

    }

    else if (device == "conveyor" && id == ui->cbSelectedConveyor->currentText().toInt())
    {
        QString state = jsonObject.value("state").toString();
        if (state == "open")
        {
            ui->pbConveyorConnect->setText("Disconnect");
        }
        else
        {
            ui->pbConveyorConnect->setText("Connect");
        }

        ui->lbConveyorCOMName->setText(jsonObject.value("com_name").toString());
    }

    else if (device == "encoder" && id == ui->cbSelectedEncoder->currentText().toInt())
    {
        QString state = jsonObject.value("state").toString();
        if (state == "open")
        {
            ui->pbConnectEncoder->setText("Disconnect");
        }
        else
        {
            ui->pbConnectEncoder->setText("Connect");
        }

        ui->lbEncoderCOMname->setText(jsonObject.value("com_name").toString());
    }
}

void RobotWindow::GetDeviceResponse(QString id, QString response)
{
    UpdateTermite(id, response, 1);

    if (id.contains("device"))
    {
        DisplayTextFromExternalMCU(response);
    }

    if (id.contains("conveyor"))
    {
        if (response.contains("P"))
        {
            static QTime previousConveyorUITime;
            if (previousConveyorUITime.msecsTo(QTime::currentTime()) < 500)
                return;

            int id = response.mid(1,1).toInt() - 1;
            float value = response.mid(3).toFloat();

            if (ui->cbSelectedEncoder->currentText() == QString::number(id))
            {
                ui->leEncoderCurrentPosition->setText(QString::number(value));
            }
        }
    }

    if (id.contains("encoder"))
    {
        static QTime previousEncoderUITime = QTime::currentTime();
        int timeDiff = previousEncoderUITime.msecsTo(QTime::currentTime());
        if (timeDiff < 500)
            return;
        previousEncoderUITime = QTime::currentTime();

        id = id.mid(7);
        if (response.contains("P"))
        {
            int index = id.toInt() - 1;
            QString value = response.mid(1);

            if (ui->cbSelectedEncoder->currentText() == id)
            {
                ui->leEncoderCurrentPosition->setText(value);
            }
        }
    }
}

void RobotWindow::SelectImageProviderOption(int option)
{
    ui->fImageSource->setHidden(true);
    ui->fWebcamSource->setHidden(false);

    QString text = ui->cbSourceForImageProvider->itemText(option);

    if (text == "Webcam")
    {
        ui->fWebcamSource->setHidden(false);
        CameraInstance->Source = "Webcam";
    }
    else if (text == "Industrial Camera")
    {
        ui->fWebcamSource->setHidden(true);
        CameraInstance->Source = "Industrial Camera";
    }
    else if (text == "Images")
    {
        ui->fImageSource->setHidden(false);
        ui->fWebcamSource->setHidden(true);
        CameraInstance->Source = "Images";
    }
    else
    {
        ui->fImageSource->setHidden(true);
        ui->fWebcamSource->setHidden(true);
        CameraInstance->Source = "Other";
    }
}

void RobotWindow::RunSmartEditor()
{
	
}

void RobotWindow::StandardFormatEditor()
{
    // ---- Number -----
    QString editorText = ui->pteGcodeArea->toPlainText();

    // Xóa các dòng trống không có kí tự
    editorText.replace(QRegularExpression("(\\n[ \\t]*){3,}"), "\n\n");

    // Gộp các kí tự trống liên tiếp thành một kí tự trống
    editorText.replace(QRegularExpression("[\\t ]+"), " ");

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
        line = line.trimmed();
//        line = line.replace("  ", " ");
//        oldNumber = "";
//        while (1)
//        {
//            if (line[0] == ' ')
//            {
//                line.replace(" ", "");
//            }
//            else
//            {
//                break;
//            }
//        }

        if (line[0] == 'N')
        {
            int spacePos = line.indexOf(' ');
            QString mS = line.mid(0, spacePos + 1);
            oldNumber = line.mid(1, spacePos);

            line.replace(mS, "");
        }

//        while (1)
//        {
//            if (line[0] == ' ')
//            {
//                line.replace(" ", "");
//            }
//            else
//            {
//                break;
//            }
//        }

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

    // ---- Color ----
//	QTextCharFormat reset;
//	ui->pteGcodeArea->setCurrentCharFormat(reset);
//	ui->pteGcodeArea->currentCharFormat();

//	if (ui->cbFormatColor->isChecked() == true)
//	{
//		QString htmlText = ui->pteGcodeArea->toHtml();

//		htmlText = replaceHtmlSection(">;", 1, 200, "<", "<span style=\"font-style:italic;color:#00aa00;\">", "</span>", htmlText);
//		htmlText = replaceHtmlSection(" O", 1, 50, "<", "<span style =\"font-weight:600;\">", "</span>", htmlText);
//		htmlText = replaceHtmlSection("#", 0, 6, "&&&", "<span style=\"font-style:italic;\">", "</span>", htmlText);

//		htmlText = boldKey("G01", htmlText);
//		htmlText = boldKey("G02", htmlText);
//		htmlText = boldKey("G03", htmlText);
//		htmlText = boldKey("G04", htmlText);
//		htmlText = boldKey("G28", htmlText);
//		htmlText = boldKey("M204", htmlText);
//		htmlText = boldKey("M360", htmlText);
//		htmlText = boldPlusKey("GOTO", "color:#ff5500;", htmlText);
//		htmlText = boldPlusKey("IF", "color:#00aa00;", htmlText);
//		htmlText = boldPlusKey("THEN", "color:#00aa00;", htmlText);
//		htmlText = boldKey("M99", htmlText);
//		htmlText = boldKey("M98", htmlText);
//		htmlText = boldKey("M05", htmlText);
//		htmlText = boldKey("M04", htmlText);
//		htmlText = boldKey("M03", htmlText);

//		ui->pteGcodeArea->setHtml(htmlText);
//    }
}

void RobotWindow::OpenGcodeReference()
{
//	GcodeReference* gcodeReferenceWindow = new GcodeReference();
//	gcodeReferenceWindow->show();
    QUrl myUrl("https://docs.deltaxrobot.com/");
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

void RobotWindow::ChangeSelectedRobot(int id)
{
    if (ui->cbSelectedRobot->currentText() == "+")
    {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->cbSelectedRobot->model());
        QStandardItem *item = model->item(id);
        item->setText(QString::number(id));

        ui->cbSelectedRobot->addItem("+");
    }

    DeviceManagerInstance->SelectedRobotID = id;

    QMetaObject::invokeMethod(DeviceManagerInstance, "RequestDeviceInfo", Qt::QueuedConnection, Q_ARG(int, DeviceManager::ROBOT));
}

void RobotWindow::ChangeRobotDOF(int id)
{
    if (id == 0)
    {
        emit Send(DeviceManager::ROBOT, QString("M60 D0"));
        emit Send(DeviceManager::ROBOT, QString("M61 D0"));
        emit Send(DeviceManager::ROBOT, QString("M62 D0"));
    }
    else if (id == 1)
    {
        emit Send(DeviceManager::ROBOT, QString("M60 D1"));
        emit Send(DeviceManager::ROBOT, QString("M61 D0"));
        emit Send(DeviceManager::ROBOT, QString("M62 D0"));
    }
    else if (id == 2)
    {
        emit Send(DeviceManager::ROBOT, QString("M60 D1"));
        emit Send(DeviceManager::ROBOT, QString("M61 D1"));
        emit Send(DeviceManager::ROBOT, QString("M62 D0"));
    }
    else if (id == 3)
    {
        emit Send(DeviceManager::ROBOT, QString("M60 D1"));
        emit Send(DeviceManager::ROBOT, QString("M61 D1"));
        emit Send(DeviceManager::ROBOT, QString("M62 D1"));
    }
}


void RobotWindow::SaveProgram()
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    QString name = GcodeScripts.at(threadId)->GetProgramName();
    GcodeScripts.at(threadId)->SetGcodeScript(ui->pteGcodeArea->toPlainText());

    if (name == "")
    {
        QInputDialog *inputDialog = new QInputDialog(this);
        inputDialog->setWindowTitle("Do you want to save program in Gcode Editor?");

        inputDialog->setInputMode(QInputDialog::TextInput);
        inputDialog->setLabelText("Gcode file name:");
        QLineEdit *lineEdit = inputDialog->findChild<QLineEdit *>();
        if (lineEdit) {
            lineEdit->setFixedWidth(500); // Đặt kiểu dáng cho QLineEdit
        }

        if (inputDialog->exec() == QDialog::Accepted) {
            name = inputDialog->textValue();
        }

    }
    SaveGcodeFile(name, ui->pteGcodeArea->toPlainText());
}

void RobotWindow::ExecuteProgram()
{
    SaveProgram();

    int threadId = ui->cbProgramThreadID->currentIndex();
    GcodeScript* currentScript = GcodeScripts.at(threadId);

    int startMode = GcodeScript::BEGIN;

    if (ui->rbEditorStart->isChecked() != true)
    {
        startMode = GcodeScript::CURSOR_POSITION;
    }

    if (ui->pbExecuteGcodes->isChecked() == false)
    {
        QMetaObject::invokeMethod(currentScript, "Stop", Qt::QueuedConnection);

        return;
    }

    currentScript->DefaultRobot = QString("robot") + ui->cbSelectedRobot->currentText();
    currentScript->DefaultConveyor = QString("conveyor") + ui->cbSelectedConveyor->currentText();
    currentScript->DefaultEncoder = QString("encoder") + ui->cbSelectedEncoder->currentText();
    currentScript->DefaultSlider = QString("slider") + ui->cbSelectedSlider->currentText();
    currentScript->DefaultDevice = QString("device") + ui->cbSelectedDevice->currentText();

    QMetaObject::invokeMethod(currentScript, "ExecuteGcode", Qt::QueuedConnection, Q_ARG(QString, ui->pteGcodeArea->toPlainText()), Q_ARG(int, startMode));

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

}

void RobotWindow::ExecuteSelectPrograms()
{

}

void RobotWindow::ExecuteCurrentLine()
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    GcodeScript* currentScript = GcodeScripts.at(threadId);


    if (ui->cbEditGcodeEditor->isChecked() == true)
	{
		return;
	}

	QTextCursor cursor;
	QString line;

	cursor = ui->pteGcodeArea->textCursor();
	cursor.movePosition(QTextCursor::StartOfBlock);
	cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    line = cursor.selectedText();

    QMetaObject::invokeMethod(currentScript, "ExecuteGcode", Qt::QueuedConnection, Q_ARG(QString, line), Q_ARG(int, GcodeScript::BEGIN));

}

void RobotWindow::HighLineCurrentLine(int pos)
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    GcodeScript* scriptThread = qobject_cast<GcodeScript*>(sender());
    if (scriptThread != GcodeScripts.at(threadId))
        return;

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

//    UpdateVariables(QString("X=%1;Y=%2;Z=%3;W=%4;U=%5;V=%6").arg(x).arg(y).arg(z).arg(w).arg(u).arg(v));
}

void RobotWindow::UpdateVelocity()
{
    QString value = ui->leVelocity->text();
    UpdateVariable("F", value);
    emit Send(DeviceManager::ROBOT, QString("G01 F") + value);
}

void RobotWindow::UpdateAccel()
{
    QString value = ui->leAccel->text();
    UpdateVariable("A", value);
    emit Send(DeviceManager::ROBOT, QString("M204 A") + ui->leAccel->text());
}

void RobotWindow::UpdateStartSpeed()
{
    QString value = ui->leStartSpeed->text();
    UpdateVariable("S", value);
    emit Send(DeviceManager::ROBOT, QString("M205 S") + ui->leStartSpeed->text());
}

void RobotWindow::UpdateEndSpeed()
{
    QString value = ui->leEndSpeed->text();
    UpdateVariable("E", value);
    emit Send(DeviceManager::ROBOT, QString("M205 E") + ui->leEndSpeed->text());
}

void RobotWindow::AdjustGripperAngle(int angle)
{
    emit Send(DeviceManager::ROBOT, QString("M360 E1"));
    emit Send(DeviceManager::ROBOT, QString("M03 S") + QString::number(angle * 5));

	ui->lbGripperValue->setText(QString::number(angle * 5));
}

void RobotWindow::Grip()
{
    emit Send(DeviceManager::ROBOT, QString("M360 E1"));
	if (ui->pbGrip->text() == "Grip")
	{
		ui->pbGrip->setText("Release");
        emit Send(DeviceManager::ROBOT, QString("M03 S") + ui->leGripperMax->text());

		ui->hsGripperAngle->blockSignals(true);
		ui->hsGripperAngle->setValue(ui->leGripperMax->text().toInt() / 5);
		ui->hsGripperAngle->blockSignals(false);
		
		ui->lbGripperValue->setText(ui->leGripperMax->text());
	}
	else
	{
		ui->pbGrip->setText("Grip");
        emit Send(DeviceManager::ROBOT, QString("M03 S") + ui->leGripperMin->text());

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

    emit Send(DeviceManager::ROBOT, QString("G01 ") + axis + QString::number(value));
}

void RobotWindow::MoveRobotFollowObject(float x, float y, float angle)
{
//    emit Send(DeviceManager::ROBOT, QString("G01 X%1 Y%2 W%3").arg(x).arg(y).arg(angle));
    RobotParameter.X = x;
    RobotParameter.Y = y;

    UpdateVariable("X", QString::number(x));
    UpdateVariable("Y", QString::number(y));
    emit Send(DeviceManager::ROBOT, QString("G01 X%1 Y%2").arg(x).arg(y));
}

void RobotWindow::DoADemo()
{

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

    if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        int selectedEncoderID = ui->cbSelectedEncoder->currentText().toInt() - 1;

        ui->leEncoderCurrentPosition->setText(QString::number(TrackingManagerInstance->Trackings.at(selectedEncoderID)->VirtualEncoderPosition));

    }

    EnablePositionUpdatingEvents();
}

void RobotWindow::SetPump(bool value)
{
    emit Send(DeviceManager::ROBOT, QString("M360 E0"));
	if (value == true)
	{
        emit Send(DeviceManager::ROBOT, QString("M04"));
	}
	else
	{
        emit Send(DeviceManager::ROBOT, QString("M05"));
	}
}

void RobotWindow::SetLaser(bool value)
{
    emit Send(DeviceManager::ROBOT, QString("M360 E3"));
	if (value == true)
	{
        emit Send(DeviceManager::ROBOT, QString("M04"));
	}
	else
	{
        emit Send(DeviceManager::ROBOT, QString("M05"));
	}
}

void RobotWindow::Home()
{
    emit Send(DeviceManager::ROBOT, "G28");

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
            emit Send(DeviceManager::ROBOT, "M08 " + inputName);
        }
        else
        {
            emit Send(DeviceManager::ROBOT, "M07 " + inputName);
        }
    }
    else
    {
        if (leDelay->text() == "")
        {
            emit Send(DeviceManager::ROBOT, "M08 " + inputName);
        }
        else
        {
            emit Send(DeviceManager::ROBOT, "M08 " + inputName + " W" + leDelay->text());
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
    VarManager::getInstance()->Prefix = ProjectName;

    VarManager::getInstance()->addVar(key, value);
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
    QString value = VarManager::getInstance()->getVar(name).toString() + '\n';

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

void RobotWindow::ChangeConveyorType(int index)
{
    ui->fConveyorX->setHidden(true);
    ui->fConveyorXHub->setHidden(true);
    ui->fConveyorCustom->setHidden(true);
    if (index == 0)
    {
        ui->fConveyorX->setHidden(false);
    }
    else if (index == 1)
    {
        ui->fConveyorXHub->setHidden(false);
    }
    else
    {
        ui->fConveyorCustom->setHidden(false);
    }
}

void RobotWindow::ChangeSelectedConveyor(int id)
{
    if (ui->cbSelectedConveyor->currentText() == "+")
    {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->cbSelectedConveyor->model());
        QStandardItem *item = model->item(id);
        item->setText(QString::number(id));

        ui->cbSelectedConveyor->addItem("+");
    }

    DeviceManagerInstance->SelectedConveyorID = id;

    QMetaObject::invokeMethod(DeviceManagerInstance, "RequestDeviceInfo", Qt::QueuedConnection, Q_ARG(int, DeviceManager::CONVEYOR));
}

void RobotWindow::ConnectEncoder()
{
    if (ui->pbConnectEncoder->text() != "Connect")
    {
        emit ChangeDeviceState(DeviceManager::ENCODER, false, "");
        return;
    }

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
            emit ChangeDeviceState(DeviceManager::ENCODER, (ui->pbConnectEncoder->text() == "Connect")?true:false, comName);
        }
    }
}

void RobotWindow::ReadEncoder()
{
    int id = ui->cbSelectedEncoder->currentText().toInt();
    if (ui->cbEncoderType->currentText() == "Sub Encoder")
    {
        QString cmd = QString("M422 C%1").arg(id + 1);
        emit Send(DeviceManager::CONVEYOR, cmd);
    }
    if (ui->cbEncoderType->currentText() == "Encoder X")
    {
        emit Send(DeviceManager::ENCODER, "M317");
    }
    if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        QMetaObject::invokeMethod(TrackingManagerInstance->Trackings[id], "GetVirtualEncoderPosition", Qt::QueuedConnection);
    }
}

void RobotWindow::SetEncoderAutoRead()
{
    int interval = ui->leEncoderInterval->text().toInt();
    int id = ui->cbSelectedEncoder->currentText().toInt();

    if (ui->cbEncoderType->currentText() == "Sub Encoder")
    {
        QString cmd = QString("M421 C%1:%2").arg(id + 1).arg(interval);
        emit Send(DeviceManager::CONVEYOR, cmd);
    }
    if (ui->cbEncoderType->currentText() == "Encoder X")
    {
        emit Send(DeviceManager::ENCODER, QString("M317 T%1").arg(interval));
    }
    if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        if (interval < 1000)
        {
            interval = 1000;
            ui->leEncoderInterval->setText(QString::number(1000));
        }

        TrackingManagerInstance->Trackings[id]->VirtualEncoderTimer->start(interval);
    }
}

void RobotWindow::ResetEncoderPosition()
{
    QString interval = ui->leEncoderInterval->text();
    int selectedEncoderID = ui->cbSelectedEncoder->currentText().toInt() - 1;

    if (ui->cbEncoderType->currentText() == "Sub Encoder")
    {
        QString name = ui->cbSelectedEncoder->currentText();

        QString cmd = QString("M423 C%1").arg(name);
        emit Send(DeviceManager::CONVEYOR, cmd);
    }
    if (ui->cbEncoderType->currentText() == "Encoder X")
    {
        emit Send(DeviceManager::ENCODER, "M316 0");
//        ui->pbSetEncoderInterval->clicked(true);
    }
    if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        TrackingManagerInstance->Trackings[selectedEncoderID]->VirtualEncoderPosition = 0;
    }
}

void RobotWindow::SetEncoderVelocity()
{
    int selectedEncoderID = ui->cbSelectedEncoder->currentText().toInt() - 1;

    TrackingManagerInstance->Trackings[selectedEncoderID]->VirtualEncoderVelocity = ui->leEncoderVelocity->text().toFloat();
}

void RobotWindow::CalculateEncoderVelocity(int id, float value)
{

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
        rosGcode += "20 ";

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

void RobotWindow::StartContinuousCapture(bool isCheck)
{
    if (isCheck == true)
    {
        ui->lbCameraState->setEnabled(true);
        CameraInstance->IsCameraPause = false;
        CameraTimer.start(ui->leCaptureInterval->text().toInt());
    }
    else
    {
        CameraInstance->IsCameraPause = true;

        CameraTimer.stop();
    }
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

//            if (cameraItems.count() > 2)
//            {
//                if (cameraID == 0)
//                {
//                    cameraID = 1;
//                }
//                else if(cameraID == 1)
//                {
//                    cameraID = 0;
//                }
//            }

            CameraInstance->RunningCamera = cameraID;


            if (CameraInstance->WebcamInstance->open(cameraID) == true)
            {
                ui->pbLoadCamera->setText("Stop Camera");

                CameraInstance->WebcamInstance->set(cv::CAP_PROP_FRAME_WIDTH, ui->leImageWidth->text().toInt());
                CameraInstance->WebcamInstance->set(cv::CAP_PROP_FRAME_HEIGHT, ui->leImageHeight->text().toInt());

                ui->leImageWidth->setText(QString::number((int)CameraInstance->WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH)));
                ui->leImageHeight->setText(QString::number((int)CameraInstance->WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT)));

                ui->pbStartAcquisition->setChecked(true);
                ui->pbStartAcquisition->clicked(true);
            }

        }
        else
        {
            ui->pbLoadCamera->setChecked(false);
            CameraInstance->IsCameraPause = false;
            CameraInstance->RunningCamera = -1;
        }
    }
    else
    {
        StopCapture();
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
        CameraInstance->WebcamInstance->open(imageName.toStdString());

        if (!CameraInstance->WebcamInstance->isOpened())
        {
            return;
        }

        CameraInstance->WebcamInstance->open(imageName.toStdString());
        CameraInstance->WebcamInstance->set(cv::CAP_PROP_FRAME_WIDTH, ui->leImageWidth->text().toInt());
        CameraInstance->WebcamInstance->set(cv::CAP_PROP_FRAME_HEIGHT, ui->leImageHeight->text().toInt());

        ui->leImageWidth->setText(QString::number((int)CameraInstance->WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH)));
        ui->leImageHeight->setText(QString::number((int)CameraInstance->WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT)));

        CameraTimer.start(ui->leCaptureInterval->text().toInt());
    }
    else
    {
        cv::String imgName = imageName.toStdString();
        CameraInstance->CaptureImage = cv::imread(imgName);
        ui->pbCapture->clicked();
    }
}

void RobotWindow::StopCapture()
{
    ui->lbCameraState->setEnabled(false);
    CameraInstance->WebcamInstance->release();
    CameraInstance->RunningCamera = -1;
    CameraInstance->IsCameraPause = false;
    ui->pbLoadCamera->setText("Load Camera");
    ui->pbStartAcquisition->setChecked(false);

    CameraTimer.stop();
}

void RobotWindow::RearrangeTaskFlow()
{

}

void RobotWindow::OpenColorFilterWindow()
{
    ParameterPanel->SetImage(CameraInstance->CaptureImage);
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
        QString chessboardSize = QString("7x7");
        QString text = QInputDialog::getText(this, tr("Find Chessboard"),
                                             tr("Chessboard size:"), QLineEdit::Normal,
                                             chessboardSize, &ok);
        if (ok && !text.isEmpty())
        {
            QStringList paras = text.split("x");
            cv::Size size(paras[0].toInt(), paras[1].toInt());

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

    VarManager::getInstance()->updateVar("RealCalibPoint1", rpoint1);
    VarManager::getInstance()->updateVar("RealCalibPoint2", rpoint2);

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
    Object obj;

    int length = rect.height();
    int width = rect.width();

    if (rect.height() < rect.width())
    {

        length = rect.height();
        width = rect.width();
    }

    ui->leWRec->setText(QString::number(width));
    ui->leLRec->setText(QString::number(length));

    obj.RangeLength.Min.Image = length * ui->leMinLRec->text().toFloat();
    obj.RangeLength.Max.Image = length * ui->leMaxLRec->text().toFloat();
    obj.RangeWidth.Min.Image = length * ui->leMinWRec->text().toFloat();
    obj.RangeWidth.Max.Image = length * ui->leMaxWRec->text().toFloat();

    emit GotOjectFilterInfo(obj);
}

void RobotWindow::GetMappingPointFromImage(QPointF point)
{
    point.setY(0 - point.y());

    QMatrix matrix = ImageProcessingThread->GetNode("VisibleObjectsNode")->GetMatrix();
    QPointF realPoint = matrix.map(point);

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

void RobotWindow::UpdateObjectsToImageViewer(QList<Object>& objects)
{
    QList<QPolygonF> polys;
    QMap<QString, QPointF> texts;
    int counter = 0;

    foreach(Object obj, objects)
    {
        counter++;
        if (counter > 100)
            return;
        polys.append(obj.ToPolygon());
        texts.insert(QString("X=%1\nY=%2\nA=%3").arg(obj.X.Real, 0, 'f', 2).arg(obj.Y.Real, 0, 'f', 2).arg(obj.Angle.Real, 0, 'f', 2), QPointF(obj.X.Image, obj.Y.Image));
    }

    ui->gvImageViewer->DrawPolygons(polys);
    ui->gvImageViewer->DrawTexts(texts);
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

    ui->pbCapture->clicked();
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
//    openConnectionDialog(DeltaConnectionManager->ConveyorPort, DeltaConnectionManager->ConveyorSocket, ui->pbConveyorConnect, ui->lbConveyorCOMName);

    if (ui->pbConveyorConnect->text() != "Connect")
    {
        emit ChangeDeviceState(DeviceManager::CONVEYOR, false, "");
        return;
    }

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
            emit ChangeDeviceState(DeviceManager::CONVEYOR, (ui->pbConveyorConnect->text() == "Connect")?true:false, comName);
        }
    }
}

void RobotWindow::SetConveyorMode(int mode)
{
    emit Send(DeviceManager::CONVEYOR, QString("M310 ") + QString::number(mode));
}

void RobotWindow::SetConveyorMovingMode(int mode)
{
    if (ui->cbConveyorType->currentText() == "Conveyor X")
    {
        if (mode == 0)
        {
            ui->leConveyorXPosition->setEnabled(false);
        }
        else
        {
            ui->leConveyorXPosition->setEnabled(true);
        }
    }
    else if (ui->cbConveyorType->currentText() == "Conveyor Hub X")
    {
        mode = (mode == 0)?1:0;

        QComboBox *cb = qobject_cast<QComboBox *>(sender());
        if (cb == ui->cbSubConveyor1Mode)
        {
            emit Send(DeviceManager::CONVEYOR, QString("M400 C1:") + QString::number(mode));
        }
        if (cb == ui->cbSubConveyor2Mode)
        {
            emit Send(DeviceManager::CONVEYOR, QString("M400 C2:") + QString::number(mode));
        }
        if (cb == ui->cbSubConveyor3Mode)
        {
            emit Send(DeviceManager::CONVEYOR, QString("M400 C3:") + QString::number(mode));
        }
    }
}

void RobotWindow::SetConveyorSpeed()
{
    if (ui->cbConveyorType->currentText() == "Conveyor X")
    {
        if (ui->cbConveyorValueType->currentIndex() == 0)
        {
            emit Send(DeviceManager::CONVEYOR, QString("M311 ") + ui->leConveyorXSpeed->text());
        }
        else
        {
            emit Send(DeviceManager::CONVEYOR, QString("M313 ") + ui->leConveyorXSpeed->text());
        }
    }
    else if (ui->cbConveyorType->currentText() == "Conveyor Hub X")
    {
        QLineEdit *le = qobject_cast<QLineEdit *>(sender());

        if (le == ui->leSubConveyor1Speed)
        {
            QString speed = ui->leSubConveyor1Speed->text();

            if (ui->cbSubConveyor1Mode->currentText() == "Continuous")
            {

                emit Send(DeviceManager::CONVEYOR, QString("M401 C1:") + speed);
            }
            else
            {
                emit Send(DeviceManager::CONVEYOR, QString("M402 C1:") + speed);
            }

        }
        if (le == ui->leSubConveyor2Speed)
        {
            QString speed = ui->leSubConveyor2Speed->text();

            if (ui->cbSubConveyor2Mode->currentText() == "Continuous")
            {

                emit Send(DeviceManager::CONVEYOR, QString("M401 C2:") + speed);
            }
            else
            {
                emit Send(DeviceManager::CONVEYOR, QString("M402 C2:") + speed);
            }

        }
        if (le == ui->leSubConveyor3Speed)
        {
            QString speed = ui->leSubConveyor3Speed->text();

            if (ui->cbSubConveyor3Mode->currentText() == "Continuous")
            {

                emit Send(DeviceManager::CONVEYOR, QString("M401 C3:") + speed);
            }
            else
            {
                emit Send(DeviceManager::CONVEYOR, QString("M402 C3:") + speed);
            }

        }

    }
}

void RobotWindow::SetConveyorPosition()
{
    if (ui->cbConveyorType->currentText() == "Conveyor X")
    {
        emit Send(DeviceManager::CONVEYOR, QString("M312 ") + ui->leConveyorXPosition->text());
    }
    else if (ui->cbConveyorType->currentText() == "Conveyor Hub X")
    {
        QLineEdit *le = qobject_cast<QLineEdit *>(sender());

        if (le == ui->leSubConveyor1Position)
        {
            QString position = ui->leSubConveyor1Position->text();
            emit Send(DeviceManager::CONVEYOR, QString("M403 C1:") + position);
        }
        if (le == ui->leSubConveyor2Position)
        {
            QString position = ui->leSubConveyor2Position->text();
            emit Send(DeviceManager::CONVEYOR, QString("M403 C2:") + position);
        }
        if (le == ui->leSubConveyor3Position)
        {
            QString position = ui->leSubConveyor3Position->text();
            emit Send(DeviceManager::CONVEYOR, QString("M403 C3:") + position);
        }
    }
}

void RobotWindow::ProcessShortcutKey()
{

}

void RobotWindow::ChangeEncoderType(int index)
{
    ui->pbConnectEncoder->setHidden(true);
    ui->pbSetEncoderVelocity->setHidden(true);
    if (index == 0)
    {
        ui->pbConnectEncoder->setHidden(false);
    }
    else if (index == 1)
    {

    }
    else
    {
        ui->pbSetEncoderVelocity->setHidden(false);
    }
}

/*!
After software send image to external script. AI will detect objects and send info back to software
 */

void RobotWindow::AddDisplayObjectFromExternalScript(QString msg)
{
    if (msg == "\n")
        return;

    QStringList objectInfos = msg.split(";");

    QList<Object> Objects;

    foreach(QString objectInfo, objectInfos)
    {
        if (objectInfo.replace(" ", "").replace("/n", "") == "")
            continue;

        Object object;

        QStringList paras = objectInfo.split(",");
        if (paras.count() >= 5)
        {
            //QString label = paras[0];
            object.X.Image = paras[1].toFloat();
            object.Y.Image = paras[2].toFloat();
            object.Length.Image = paras[3].toFloat();
            object.Width.Image = paras[4].toFloat();
            object.Angle.Image = paras[5].toFloat();

            object.Type = paras[0];

            object.ToPoints();

//            object->Offset = Encoder1->CalculateOffset(Encoder1->GetMeasuredDistance());

            Objects.append(object);

        }
    }

    emit GotObjects(Objects);
}

void RobotWindow::ChangeSelectedTracking(int id)
{
    if (ui->cbSelectedTracking->currentText() == "+")
    {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->cbSelectedTracking->model());
        QStandardItem *item = model->item(id);
        item->setText(QString::number(id));

        AddTrackingThread();

        ui->cbSelectedTracking->addItem("+");
    }

    LoadTrackingThread();
}

void RobotWindow::CalculateMappingMatrixTool()
{
    QPointF sp1(ui->leSourcePoint1X->text().toFloat(), ui->leSourcePoint1Y->text().toFloat());
    QPointF sp2(ui->leSourcePoint2X->text().toFloat(), ui->leSourcePoint2Y->text().toFloat());
    QPointF tp1(ui->leDestinationPoint1X->text().toFloat(), ui->leDestinationPoint1Y->text().toFloat());
    QPointF tp2(ui->leDestinationPoint2X->text().toFloat(), ui->leDestinationPoint2Y->text().toFloat());

    QTransform transformMatrix = calculateTransformMatrix(sp1, sp2, tp1, tp2);

    VarManager::getInstance()->addVar(ui->leMatrix1Name->text(), transformMatrix);
}

void RobotWindow::CalculatePointMatrixTool()
{

}

void RobotWindow::CalculateTestPoint()
{
    QTransform matrix = VarManager::getInstance()->getVar(ui->leTestMatrixName->text()).value<QTransform>();

    QPointF testPoint(ui->leTestPointX->text().toFloat(), ui->leTestPointY->text().toFloat());
    QPointF target = matrix.map(testPoint);
    ui->leTargetTestPointX->setText(QString::number(target.x()));
    ui->leTargetTestPointY->setText(QString::number(target.y()));
}

void RobotWindow::CalculateAngle()
{
    QPointF start(ui->leAnglePoint1X->text().toFloat(), ui->leAnglePoint1Y->text().toFloat());
    QPointF end(ui->leAnglePoint2X->text().toFloat(), ui->leAnglePoint2Y->text().toFloat());

    QVector2D vector(end - start);
    float angle = qRadiansToDegrees(qAtan2(vector.y(), vector.x()));
    ui->leAngleResult->setText(QString::number(angle));
}

void RobotWindow::ProcessProximitySensorValue(int value)
{

}

void RobotWindow::ConnectSliding()
{
    openConnectionDialog(DeltaConnectionManager->SlidingPort, DeltaConnectionManager->SlidingSocket, ui->pbSlidingConnect, ui->lbSliderCOMName);
}

void RobotWindow::GoHomeSliding()
{
    emit Send(DeviceManager::SLIDER, "M320");
}

void RobotWindow::DisableSliding()
{
    emit Send(DeviceManager::SLIDER, "M323");
}

void RobotWindow::SetSlidingSpeed()
{
    emit Send(DeviceManager::SLIDER, QString("M321 ") + ui->leSlidingSpeed->text());
}

void RobotWindow::SetSlidingPosition()
{
    emit Send(DeviceManager::SLIDER, QString("M322 ") + ui->leSlidingPosition->text());
}

void RobotWindow::ConnectExternalMCU()
{
//    openConnectionDialog(DeltaConnectionManager->ExternalControllerPort, DeltaConnectionManager->ExternalControllerSocket, ui->pbExternalControllerConnect, ui->lbExternalCOMName);
    if (ui->pbExternalControllerConnect->text() != "Connect")
    {
        emit ChangeDeviceState(DeviceManager::DEVICE, false, "");
        return;
    }

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
            emit ChangeDeviceState(DeviceManager::DEVICE, (ui->pbExternalControllerConnect->text() == "Connect")?true:false, comName);
        }
    }

}

void RobotWindow::TransmitTextToExternalMCU()
{
    emit Send(DeviceManager::DEVICE, ui->leTransmitToMCU->text());
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

    if (SentCommands.count() > 500)
        SentCommands.clear();

    SentCommands.append(msg);

    QString target = ui->cbDeviceSender->currentText();

    if (target == "Software")
    {
        QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, msg));
    }

    if (target == "Robot")
    {
        emit Send(DeviceManager::ROBOT, msg);
    }

    if (target == "Conveyor")
    {
        emit Send(DeviceManager::CONVEYOR, msg);
    }

    if (target == "Slider")
    {
        emit Send(DeviceManager::SLIDER, msg);
    }

    if (target == "External MCU")
    {
        emit Send(DeviceManager::DEVICE, msg);
    }

    if (target == "Encoder")
    {
        emit Send(DeviceManager::ENCODER, msg);
    }

	ui->leTerminal->setText("");
}

void RobotWindow::RunExternalScript()
{
    runPythonFile(ui->lePythonUrl->text());
}

void RobotWindow::OpenExternalScriptFolder()
{
    QString filePath = ui->lePythonUrl->text();
    QFileInfo fileInfo(filePath);
    QString folderPath = fileInfo.absolutePath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
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

void RobotWindow::UpdateTermite(QString device, QString mess, int direction)
{
    QString selectedTermite = ui->cbDeviceSender->currentText().toLower();
    if (!selectedTermite.contains("software") && !device.contains(selectedTermite))
        return;

    QString msg = "";

    if (direction == 0)
        msg = QString("%1 << %2").arg(device).arg(mess);
    else
        msg = QString("%1 >> %2").arg(device).arg(mess);

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

    emit Send(DeviceManager::ROBOT, prefix + para1 + para2);
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
    lbInputValues->append(ui->lbIxValue);

    lbInputValues->append(ui->lbA0Value);
    lbInputValues->append(ui->lbA1Value);
    lbInputValues->append(ui->lbAxValue);
}

void RobotWindow::plugValue(QLineEdit *le, float value)
{
    le->setText(QString::number(le->text().toFloat() + value));
}

QTransform RobotWindow::calculateTransformMatrix(QPointF sourcePoint1, QPointF sourcePoint2, QPointF targetPoint1, QPointF targetPoint2)
{
    qreal a = (targetPoint2.y() - targetPoint1.y()) / (sourcePoint2.y() - sourcePoint1.y());
    qreal b = (targetPoint2.x() - a * sourcePoint2.x()) - targetPoint1.x();
    qreal c = (targetPoint2.x() - targetPoint1.x()) / (sourcePoint2.x() - sourcePoint1.x());
    qreal d = (targetPoint2.y() - c * sourcePoint2.y()) - targetPoint1.y();

    QTransform transformMatrix(a, c, b, d, 0, 0);
    return transformMatrix;
}

void RobotWindow::runPythonFile(QString filePath)
{
    QString pythonExePath = "python"; // đường dẫn tới file python
    QStringList arguments;
    arguments << filePath;

    // Kiểm tra đường dẫn tương đối hay tuyệt đối
    QFileInfo fileInfo(filePath);
    if (!fileInfo.isAbsolute()) {
        QDir dir(QCoreApplication::applicationDirPath());
        filePath = dir.absoluteFilePath(filePath);
    }

    // Nếu quá trình chạy file python đã tồn tại thì tắt nó
    if (process != nullptr && process->state() == QProcess::Running) {
        process->terminate();
        process->waitForFinished();
    }

    // Tạo quá trình mới để chạy file python
    process = new QProcess();
    process->start(pythonExePath, arguments);
    process->waitForStarted();
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
            case 1:
                ui->cbD0->click();
                break;
            case 2:
                ui->cbDx->click();
                break;
            case 9:
                ui->pbHome->click();
                break;
            case 4:
                ui->pbUp->click();
                break;

            case 5:
                index++;
                if (index == ui->cbDivision->count())
                    index = 0;
                ui->cbDivision->setCurrentIndex(index);
                break;

            case 6:
                ui->pbDown->click();
                break;

            case 7:
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
    if (abs(event.value) < 0.2f)
        return;
    SoftwareLog(QString::number(event.axis) + ": " + QString::number(event.value) + "\n");

    switch(event.axis)
    {
        case 0:
            MoveRobot("X", event.value);
            break;
        case 1:
            MoveRobot("Y", -event.value);
            break;
        case 2:
            break;
        case 3:
            MoveRobot("Z", -event.value);
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
        if (selectedTabWidget == ui->twDevices)
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
            // general init
            qRegisterMetaType< cv::Mat >("cv::Mat");
            connect(pluginWidget, SIGNAL(CapturedImage(cv::Mat)), CameraInstance, SLOT(GetImageFromExternal(cv::Mat)));
            connect(pluginWidget, &DeltaXPlugin::StartedCapture, [=]()
            {
                int id = ui->cbEncoderForCamera->currentText().toInt();
                QMetaObject::invokeMethod(TrackingManagerInstance, "SaveCapturePosition", Qt::QueuedConnection, Q_ARG(int, id));
            });
            connect(CameraInstance, &Camera::RequestCapture, pluginWidget, &DeltaXPlugin::RequestCapture);

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

