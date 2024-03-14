#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include "SoftwareManager.h"
#include "MainWindow.h"

RobotWindow::RobotWindow(QWidget *parent, QString projectName) :
    QMainWindow(parent),
    ui(new Ui::RobotWindow)
{
    ui->setupUi(this);

    this->ProjectName = projectName;

    InitVariables();
    InitOtherThreadObjects();
    InitEvents();

    LoadSettings();
    InitDefaultValue();
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

    ConnectionManager->thread()->quit();
    ConnectionManager->thread()->wait();

    ImageProcessingThread->thread()->quit();
    ImageProcessingThread->thread()->wait();

    CameraInstance->thread()->quit();
    CameraInstance->thread()->wait();

    for (int i = 0; i < GcodeScripts.count(); i++)
    {
        GcodeScripts.at(i)->thread()->quit();
        GcodeScripts.at(i)->thread()->wait();
    }

    delete ui;
}

void RobotWindow::InitVariables()
{
    //--------- Register ----------
    qRegisterMetaType< QList<QStringList>>("QList<QStringList>");
    qRegisterMetaType< QList<Object> >("QList<ObjectInfo>");

    //---------- Connection -----------
    InitSocketConnection();

    //--------- Init Dialog -------------
    CloseDialog = new SmartDialog(this);
    CloseDialog->SetType(CloseDialog->CLOSE_DIALOG);

    // ---- Init UI ----

    VarViewModel.setHorizontalHeaderLabels(QStringList() << "Name" << "Value");
    ui->tvCurrentVariable->setModel(&VarViewModel);

    connect(ui->cbVariableDisplayOption, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index){
        if (index == 1)
        {
            ui->tvCurrentVariable->setModel(&SoftwareManager::GetInstance()->SoftwarePointer->VariableTreeModel);
        }
        else
        {
            ui->tvCurrentVariable->setModel(&VarViewModel);
        }
    });

    ObjectModel = new ObjectInfoModel(this);
    ui->tvObjectTable->setModel(ObjectModel);

    performanceTimer.start();


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

    // -------- Point Tool -------

    connect(ui->tbCopyTestTrackingPoint, &QPushButton::clicked, [=]()
    {
        // Copy giá trị vào clipboard
        QString text = QString("%1, %2, %3").arg(ui->leTestTrackingPointX->text()).arg(ui->leTestTrackingPointY->text()).arg(ui->leTestTrackingPointZ->text());
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(text);

    });

    connect(ui->tbPasteTestTrackingPoint, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leTestTrackingPointX, ui->leTestTrackingPointY, ui->leTestTrackingPointZ);
    });

    connect(ui->pbMoveTestTrackingPoint, &QPushButton::clicked, [=]()
    {
        QVector3D initialPoint;
        initialPoint.setX(ui->leTestTrackingPointX->text().toFloat());
        initialPoint.setY(ui->leTestTrackingPointY->text().toFloat());
        initialPoint.setZ(ui->leTestTrackingPointZ->text().toFloat());

        QVector3D direction = VariableManager::instance().getVar(ui->leVelocityVector->text()).value<QVector3D>();

        double distance = ui->leMovingValue->text().toFloat();

        QVector3D normalizedDirection = direction.normalized();

        // Tính tọa độ mới
        QVector3D newPoint = initialPoint + normalizedDirection * distance;
        ui->leTestTrackingPointX->setText(QString::number(newPoint.x()));
        ui->leTestTrackingPointY->setText(QString::number(newPoint.y()));
        ui->leTestTrackingPointZ->setText(QString::number(newPoint.z()));
    });

    connect(ui->tbAutoMove, &QToolButton::toggled, [=](bool checked)
    {
        TrackingManagerInstance->Trackings.at(0)->IsUpateTestPoint = checked;
    });

    connect(ui->pbCalculateMappingMatrixTool, SIGNAL(clicked(bool)), this, SLOT(CalculateMappingMatrixTool()));
    connect(ui->pbCalculatePointMatrixTool, SIGNAL(clicked(bool)), this, SLOT(CalculatePointMatrixTool()));
    connect(ui->pbCalculateTestPoint, SIGNAL(clicked(bool)), this, SLOT(CalculateTestPoint()));
    connect(ui->pbCalVector, SIGNAL(clicked(bool)), this, SLOT(CalculateVector()));

    connect(ui->pbAnglePoint1, &QPushButton::clicked, [=](){ ui->lePointAtT1X->setText(QString::number(RobotParameters[RbID].X)); ui->lePointAtT1Y->setText(QString::number(RobotParameters[RbID].Y)); ui->lePointAtT1Z->setText(QString::number(RobotParameters[RbID].Z));});
    connect(ui->pbAnglePoint2, &QPushButton::clicked, [=](){ ui->lePointAtT2X->setText(QString::number(RobotParameters[RbID].X)); ui->lePointAtT2Y->setText(QString::number(RobotParameters[RbID].Y)); ui->lePointAtT2Z->setText(QString::number(RobotParameters[RbID].Z));});

    connect(ui->tbPasteVectorPoint1, &QPushButton::clicked, [=]()
    { 
        pastePointValues(ui->lePointAtT1X, ui->lePointAtT1Y, ui->lePointAtT1Z);
    });

    connect(ui->tbPasteVectorPoint2, &QPushButton::clicked, [=]()
    { 
        pastePointValues(ui->lePointAtT2X, ui->lePointAtT2Y, ui->lePointAtT2Z);
    });

    connect(ui->tbPasteSourcePoint1, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leSourcePoint1X, ui->leSourcePoint1Y, NULL);
    });
    connect(ui->tbPasteSourcePoint2, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leSourcePoint2X, ui->leSourcePoint2Y, NULL);
    });
    connect(ui->tbPasteDestinationPoint1, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leDestinationPoint1X, ui->leDestinationPoint1Y, NULL);
    });
    connect(ui->tbPasteDestinationPoint2, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leDestinationPoint2X, ui->leDestinationPoint2Y, NULL);
    });

    connect(ui->pbAddMappingMatrix, &QPushButton::clicked, [=]()
    {
        QString prefix = ProjectName + "." + ui->cbSelectedTracking->currentText() + ".";

        VariableManager::instance().updateVar(prefix + ui->leMatrixName->text(), CalculatingTransform);

        if (!isItemExit(ui->lwMappingMatrixList, ui->leMatrixName->text())) {
            ui->lwMappingMatrixList->addItem(ui->leMatrixName->text());
        }
    });

    connect(ui->pbAddPointMatrix, &QPushButton::clicked, [=]()
    {
        QString prefix = ProjectName + "." + ui->cbSelectedTracking->currentText() + ".";

        VariableManager::instance().updateVar(prefix + ui->lePointMatrixName->text(), PointMatrix);

        if (!isItemExit(ui->lwPointMatrixList, ui->lePointMatrixName->text()))
        {
            ui->lwPointMatrixList->addItem(ui->lePointMatrixName->text());
        }
    });

    connect(ui->pbAddVector, &QPushButton::clicked, [=]()
    {
        CalVector.setX(ui->leVectorX->text().toFloat());
        CalVector.setY(ui->leVectorY->text().toFloat());
        CalVector.setZ(ui->leVectorZ->text().toFloat());

        QString prefix = ProjectName + "." + ui->cbSelectedTracking->currentText() + ".";

        VariableManager::instance().updateVar(prefix + ui->leVectorName->text(), QVector3D(CalVector.x(), CalVector.y(), CalVector.z()));

        if (!isItemExit(ui->lwVectorList, ui->leVectorName->text())) {
            ui->lwVectorList->addItem(ui->leVectorName->text());
        }

    });


    connect(ui->pbAddVariablePoint, &QPushButton::clicked, [=]()
    {
        int selectedEncoderID = ui->cbSelectedTracking->currentText().toInt();

        float x = ui->leObjectX->text().isEmpty() ? QRandomGenerator::global()->generate() % 1000 : ui->leObjectX->text().toFloat();
        float y = ui->leObjectY->text().isEmpty() ? QRandomGenerator::global()->generate() % 1000 : ui->leObjectY->text().toFloat();
        float z = ui->leObjectZ->text().isEmpty() ? QRandomGenerator::global()->generate() % 1000 : ui->leObjectZ->text().toFloat();

        std::default_random_engine generator;  // You can seed it if you want: generator(seed);
        std::uniform_int_distribution<int> distribution(-180, 180);
        int angle = distribution(generator);

        if (ui->leObjectListName->text() == TrackingManagerInstance->Trackings.at(selectedEncoderID)->ListName)
        {
            QList<ObjectInfo> list;
            QVector3D position(x, y, z);

            ObjectInfo object(-1, 0, position, 20, 40, angle);
            list.append(object);
            TrackingManagerInstance->Trackings.at(selectedEncoderID)->UpdateTrackedObjects(list, ui->leObjectListName->text());
        }
        else
        {
            QString listName = ui->leObjectListName->text();
            int counter = VariableManager::instance().getVariable(listName + ".Count", 0).toInt();
            VariableManager::instance().updateVar((listName + ".%1.X").arg(counter), x);
            VariableManager::instance().updateVar((listName + ".%1.Y").arg(counter), y);
            VariableManager::instance().updateVar((listName + ".%1.Z").arg(counter), z);
            VariableManager::instance().updateVar((listName + ".%1.W").arg(counter), 20);
            VariableManager::instance().updateVar((listName + ".%1.L").arg(counter), 40);
            VariableManager::instance().updateVar((listName + ".%1.A").arg(counter), angle);

            VariableManager::instance().updateVar(listName + ".Count", counter + 1);
        }
    });

    // ------- Log and Debug -----
    Debugs.push_back(ui->teDebug);

    //-------- Jogging -------

    QList<QRadioButton*> stepRBs = {
        ui->rb01,
        ui->rb05,
        ui->rb10,
        ui->rb50,
        ui->rb100,
        ui->rb500,
        ui->rb1000
    };

    // Sử dụng vòng lặp để kết nối tất cả
    for (auto* rb : stepRBs) {
        connect(rb, &QRadioButton::toggled, [=](bool checked) {
            if (checked) RobotParameters[RbID].Step = rb->text().toFloat();
        });
    }


    //-------- 2Drawing Module ------------

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

//    TrackingObjectTable = new ObjectVariableTable(this);

    connect(ui->pbUpdateObjectToView, &QPushButton::clicked, this, &RobotWindow::UpdateObjectsToView);

//    ui->gbCameraCalibration->setChecked(false);
//    ui->gbCameraObject->setChecked(false);
//    ui->gbCameraVariable->setChecked(false);

    InitCalibration();
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
    connect(this, SIGNAL(ChangeDeviceState(int,bool,QString)), DeviceManagerInstance, SLOT(SetDeviceState(int,bool,QString)));
    connect(DeviceManagerInstance, SIGNAL(Log(QString,QString,int)), this, SLOT(UpdateTermite(QString,QString,int)));
    connect(DeviceManagerInstance, SIGNAL(DeviceResponded(QString,QString)), this, SLOT(GetDeviceResponse(QString,QString)));
    connect(this, SIGNAL(Send(int,QString)), DeviceManagerInstance, SLOT(SendGcode(int,QString)));

    for (int i = 0; i < 3; i++)
    {
        RobotPara robotPara;
        RobotParameters.append(robotPara);
    }

    //------------ Devices --------

        //-------- Camera --------
    CameraInstance = new Camera();
    CameraInstance->moveToThread(new QThread(this));
    connect(CameraInstance->thread(), &QThread::finished, CameraInstance, &QObject::deleteLater);
    connect(CameraInstance, &Camera::StopCameraRequest, this, &RobotWindow::StopCapture);

    CameraInstance->thread()->start();

    connect(CameraInstance, &Camera::connectedResult, this, &RobotWindow::UpdateCameraConnectedState);

    connect(&CameraTimer, SIGNAL(timeout()), CameraInstance, SLOT(GeneralCapture()));
    SelectImageProviderOption(0);

    connect(ui->cbTrackingThreadForCamera, SIGNAL(currentIndexChanged(int)), CameraInstance, SLOT(setTracking(int)));

    //------- New image processing thread --------
    InitObjectDetectingModule();

        //-------- Robot ---------
    connect(ui->pbConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectRobot()));
    connect(ui->cbSelectedRobot, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedRobot(int)));
    connect(ui->tbDisableRobot, SIGNAL(clicked(bool)), this, SLOT(SetRobotState(bool)));
    connect(ui->tbRequestPosition, SIGNAL(clicked(bool)), this, SLOT(RequestPosition()));
    connect(ui->cbRobotDOF, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRobotDOF(int)));
    connect(ui->cbRobotModel, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRobotModel(int)));

        //-------- Conveyor --------
    connect(ui->cbSelectedConveyor, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedConveyor(int)));
    connect(ui->pbConveyorConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectConveyor()));
    connect(ui->cbConveyorMode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMode(int)));
    connect(ui->pbSetConveyorMode, &QPushButton::clicked, [=](bool checked)
    {
        SetConveyorMode(ui->cbConveyorMode->currentIndex());
    });

    connect(ui->leConveyorXPosition, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));
    connect(ui->pbMoveConveyorByDistance, SIGNAL(clicked(bool)), this, SLOT(SetConveyorPosition()));
    connect(ui->leConveyorXAbsolutePosition, SIGNAL(returnPressed()), this, SLOT(SetConveyorAbsolutePosition()));
    connect(ui->pbMoveConveyorPosition, SIGNAL(clicked(bool)), this, SLOT(SetConveyorAbsolutePosition()));
    connect(ui->leConveyorXSpeed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));
    connect(ui->pbSetConveyorSpeed, SIGNAL(clicked(bool)), this, SLOT(SetConveyorSpeed()));
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
    connect(ui->pbSetEncoderVelocity, SIGNAL(clicked(bool)), this, SLOT(SetEncoderVelocity()));

    connect(ui->cbEncoderType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeEncoderType(int)));

    connect(ui->cbLinkToConveyorX, &QCheckBox::stateChanged, [=](int state){
        if(state == Qt::Checked)
        {
            int conid = getIDfromName(ui->cbConveyorLinkToEncoder->currentText());
            int enid = getIDfromName(ui->cbConveyorLinkToEncoder->currentText());

            DeviceManagerInstance->Encoders.at(enid)->LinkedConveyor = conid;
            ui->pbConnectEncoder->setHidden(true);
        } else
        {
            int enid = getIDfromName(ui->cbConveyorLinkToEncoder->currentText());

            DeviceManagerInstance->Encoders.at(enid)->LinkedConveyor = -1;
            ui->pbConnectEncoder->setHidden(false);
        }
    });
    

    //-------- Slider --------

    connect(ui->pbSlidingConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectSliding()));
    connect(ui->pbSlidingHome, SIGNAL(clicked(bool)), this, SLOT(GoHomeSliding()));
    connect(ui->pbSlidingDisable, SIGNAL(clicked(bool)), this, SLOT(DisableSliding()));
    connect(ui->leSlidingSpeed, SIGNAL(returnPressed()), this, SLOT(SetSlidingSpeed()));
    connect(ui->leSlidingPosition, SIGNAL(returnPressed()), this, SLOT(SetSlidingPosition()));

        //-------- MCU --------
    connect(ui->pbExternalControllerConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectExternalMCU()));
    connect(ui->leTransmitToMCU, SIGNAL(returnPressed()), this, SLOT(TransmitTextToExternalMCU()));

    //----- Tracking -----
    InitTrackingThread();
    connect(ui->cbSelectedTracking, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedTracking(int)));
    connect(ui->cbTrackingEncoderSource, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedTrackingEncoder(int)));

    //----- Gcode Programing----------

    InitGcodeEditorModule();

    //----- Plugin ------
    LoadPlugin();
}

void RobotWindow::InitSocketConnection()
{
    // ---------- Server ---------

    // Tìm ip local của máy
    QString localIP = SocketConnectionManager::printLocalIpAddresses();
    ui->leIP->setText(localIP);

    ConnectionManager = new SocketConnectionManager(localIP, ui->lePort->text().toInt(), this);
    QString appDirPath = QCoreApplication::applicationDirPath();
    ConnectionManager->indexPath = appDirPath + "/script-example/webpage/websocket.html";

    /// Chuyển ConnectionManager vào một thread mới
    ConnectionManager->moveToThread(new QThread(this));
    /// Kết nối sự kiện khi thread kết thúc với việc xóa ConnectionManager
    connect(ConnectionManager->thread(), &QThread::finished, ConnectionManager, &QObject::deleteLater);
    /// Khởi động thread
    ConnectionManager->thread()->start();    

    if (ConnectionManager->IsServerOpen())
    {
        ui->leIP->setText(ConnectionManager->server->serverAddress().toString());
        ui->lePort->setText(QString::number(ConnectionManager->server->serverPort()));
    }

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
    qRegisterMetaType< QList<Object>* >("QList<Object>");
    qRegisterMetaType< QList<QSharedPointer<Object>> >("QList<QSharedPointer<Object>>");
    qRegisterMetaType< QList<QPolygonF> >("QList<QPolygonF>");
    qRegisterMetaType< QList<Object> >("QList<ObjectInfo>");
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
    ImageProcessingThread->CreatTaskNode("CropImageNode", TaskNode::CROP_IMAGE_NODE, "WarpImageNode");

    ImageProcessingThread->CreatTaskNode("MappingMatrixNode", TaskNode::MAPPING_MATRIX_NODE);
    ImageProcessingThread->CreatTaskNode("ColorFilterNode", TaskNode::COLOR_FILTER_NODE, "CropImageNode");
    ImageProcessingThread->CreatTaskNode("GetObjectsNode", TaskNode::GET_OBJECTS_NODE, "ColorFilterNode");
    ImageProcessingThread->CreatTaskNode("VisibleObjectsNode", TaskNode::VISIBLE_OBJECTS_NODE, "GetObjectsNode|MappingMatrixNode");

    ImageProcessingThread->CreatTaskNode("DisplayImageNode", TaskNode::DISPLAY_IMAGE_NODE, "CropImageNode");

    ImageProcessingThread->GetNode("WarpImageNode")->IsPass = true;
    ImageProcessingThread->GetNode("CropImageNode")->IsPass = true;

    connect(CameraInstance, SIGNAL(GotImage(cv::Mat)), ImageProcessingThread->GetNode("GetImageNode"), SLOT(Input(cv::Mat)));

    // ---------- Blob Filter Window---------
    ParameterPanel = new FilterWindow(this);
    ParameterPanel->ProjectName = ProjectName;

    // ---------- Main UI -------
//    connect(ui->cbImageOutput, SIGNAL(currentTextChanged(QString)), this, SLOT(ChangeOutputDisplay()));
    connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), this, SLOT(LoadWebcam()));
    connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), this, SLOT(LoadImages()));
    connect(ui->cbDetectingAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectObjectDetectingAlgorithm(int)));

    connect(ui->cbSendingImageMethod, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index){
        ConnectionManager->imageSendingMethod = index;
    });

    ui->cbDetectingAlgorithm->setCurrentIndex(0);
    SelectObjectDetectingAlgorithm(0);

    ui->gvImageViewer->ProjectName = ProjectName;

//    ui->gvImageViewer->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

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
    connect(ui->pbGetSizeTool, &QPushButton::toggled,  [=](bool checked)
    {
        if (checked == true)
        {
            ui->pbCalibPointTool->setChecked(false);
            ui->pbFindChessboardTool->setChecked(false);
            ui->pbMappingPointTool->setChecked(false);

            ui->gvImageViewer->SelectRectTool();

            ui->pbCapture->clicked();
        }
        else
        {
            ui->gvImageViewer->SelectNoTool();
        }
    });
    connect(ui->pbFindChessboardTool, &QPushButton::clicked,  [=](bool checked)
    {
        if (ui->pbFindChessboardTool->isChecked() == true)
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
    connect(ui->pbMappingPointTool, &QPushButton::clicked, [=](bool checked)
    {
        if (checked == true)
        {
            ui->pbCalibPointTool->setChecked(false);
            ui->pbFindChessboardTool->setChecked(false);
            ui->pbGetSizeTool->setChecked(false);

            ui->gvImageViewer->SelectMappingTool();
        }
        else
        {
            ui->gvImageViewer->SelectNoTool();
        }

    });
    connect(ui->pbCropTool, &QPushButton::clicked, [=](bool checked)
    {
        EditImage(ui->pbWarpTool->isChecked(), ui->pbCropTool->isChecked());

    });

    connect(ui->pbWarpTool, &QPushButton::clicked, [=](bool checked)
    {
        EditImage(ui->pbWarpTool->isChecked(), ui->pbCropTool->isChecked());
    });

    connect(ui->pbFilterTool, SIGNAL(clicked(bool)), this, SLOT(OpenColorFilterWindow()));
//    connect(ui->pbViewDataObjects, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
    connect(ui->pbClearDetectObjects, &QPushButton::clicked, [=](bool checked)
    {
        int id = ui->cbTrackingThreadForCamera->currentIndex();
        QMetaObject::invokeMethod(TrackingManagerInstance->Trackings[id], "ClearTrackedObjects", Qt::QueuedConnection);

        QTimer::singleShot(300, [this](){
            ui->pbCapture->clicked();
        });
    });
//    connect(ui->pbOpenObjectTable, SIGNAL(clicked(bool)), TrackingObjectTable, SLOT(DisplayDialog()));
//    connect(ui->pbClearDetectObjects, &QPushButton::clicked, ui->pbClearObject, &QPushButton::clicked);

//    connect(TrackingObjectTable, SIGNAL(TakeObjectPosition(float, float, float)), this, SLOT(MoveRobotFollowObject(float, float, float)));

    connect(ui->gvImageViewer, &ImageViewer::selectedNoTool, this, &RobotWindow::UnselectToolButtons);

    connect(ui->gvImageViewer, &ImageViewer::changedPoints, this, &RobotWindow::GetCalibPointsFromImage);
    connect(ui->gvImageViewer, &ImageViewer::changedRect, this, &RobotWindow::GetObjectSizeFromImage);
    connect(ui->gvImageViewer, &ImageViewer::changedMappingPoint, this, &RobotWindow::GetMappingPointFromImage);

    connect(ui->leRealityPoint1X, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint1Y, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint2X, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);
    connect(ui->leRealityPoint2Y, &QLineEdit::returnPressed, this, &RobotWindow::UpdateRealPositionOfCalibPoints);

    connect(ui->leIoUThreshold, &QLineEdit::returnPressed,
    [=] (){
        TrackingManagerInstance->Trackings.at(0)->IoUThreshold = ui->leIoUThreshold->text().toFloat();
    });
    connect(ui->leDistanceThreshold, &QLineEdit::returnPressed,
    [=] (){
        TrackingManagerInstance->Trackings.at(0)->DistanceThreshold = ui->leDistanceThreshold->text().toFloat();
    });

    connect(ui->pbZoomInCameraView, &QPushButton::clicked, [=](bool checked)
    {
        ui->gvImageViewer->ZoomIn(2);
//        ui->graphicsView->ZoomIn(2);
    });
    connect(ui->pbZoomOutCameraView, &QPushButton::clicked, [=](bool checked)
    {
        ui->gvImageViewer->ZoomOut(2);
//        ui->graphicsView->ZoomOut(2);
    });

    connect(ui->leLimitMinX, &QLineEdit::returnPressed,
    [=] (){
        TrackingManagerInstance->Trackings.at(0)->X_min = ui->leLimitMinX->text().toFloat();
    });
    connect(ui->leLimitMaxX, &QLineEdit::returnPressed,
    [=] (){
        TrackingManagerInstance->Trackings.at(0)->X_max = ui->leLimitMaxX->text().toFloat();
    });
    connect(ui->leLimitMinY, &QLineEdit::returnPressed,
    [=] (){
        TrackingManagerInstance->Trackings.at(0)->Y_min = ui->leLimitMinY->text().toFloat();
    });
    connect(ui->leLimitMaxY, &QLineEdit::returnPressed,
    [=] (){
        TrackingManagerInstance->Trackings.at(0)->Y_max = ui->leLimitMaxY->text().toFloat();
    });


    // ---------- Image Provider -------

    connect(ui->pbCapture, &QPushButton::clicked, CameraInstance, &Camera::GeneralCapture);
    connect(ui->pbStartAcquisition, &QPushButton::clicked, this, &RobotWindow::StartContinuousCapture);

    connect(ui->pbSaveImage, &QPushButton::clicked, [=](bool checked)
    {
        QString absolutePath = checkAndCreateDir(ui->leImageFolder->text());

        saveImageWithUniqueName(CameraInstance->CaptureImage, absolutePath);
    });

    connect(ui->tbOpenSaveFolder, &QPushButton::clicked, [=](bool checked)
    {
        QString absolutePath = checkAndCreateDir(ui->leImageFolder->text());
        QDesktopServices::openUrl(QUrl::fromLocalFile(absolutePath));
    });

    connect(ui->pbRefreshImageFolder, &QPushButton::clicked, [=](bool checked)
    {
        QString absolutePath = checkAndCreateDir(ui->leImageFolder->text());
        loadImages(absolutePath, ui->lwImageList);
    });

    connect(ui->lwImageList, &QListWidget::itemClicked, this, &RobotWindow::onImageItemClicked);

    connect(this, SIGNAL(GotResizePara(cv::Size)), ImageProcessingThread->GetNode("ResizeImageNode"), SLOT(Input(cv::Size)));
    connect(ImageProcessingThread->GetNode("FindChessboardNode"), SIGNAL(HadOutput(QPolygonF)), ui->gvImageViewer, SLOT(SetQuadrangle(QPolygonF)));
    connect(this, SIGNAL(GotChessboardSize(cv::Size)), ImageProcessingThread->GetNode("FindChessboardNode"), SLOT(Input(cv::Size)));
    connect(this, SIGNAL(GotResizeImage(cv::Mat)), ImageProcessingThread->GetNode("FindChessboardNode"), SLOT(Input(cv::Mat)));
    connect(this, SIGNAL(GotCalibPoints(QPolygonF)), ImageProcessingThread->GetNode("MappingMatrixNode"), SLOT(Input(QPolygonF)));

    connect(ui->gvImageViewer, SIGNAL(changedQuadrangle(QPolygonF)), ImageProcessingThread->GetNode("GetPerspectiveNode"), SLOT(Input(QPolygonF)));

    connect(ui->gvImageViewer, SIGNAL(changedArea(QRectF)), ImageProcessingThread->GetNode("CropImageNode"), SLOT(Input(QRectF)));
//    connect(ImageProcessingThread->GetNode("CropImageNode"), SIGNAL(HadOutput(cv::Mat)), this, SLOT(SendImageToExternalScript(cv::Mat)));
//    connect(ImageProcessingThread->GetNode("CropImageNode"), SIGNAL(HadOutput(cv::Mat)), ConnectionManager, SLOT(sendImageToImageClients(cv::Mat)));

//    connect(ImageProcessingThread->GetNode("ColorFilterNode"), SIGNAL(HadOutput(cv::Mat)), this, SLOT(SendImageToExternalScript(cv::Mat)));

    connect(ui->leImageWidth, &QLineEdit::returnPressed,
    [=] (){
        int newW = ui->leImageWidth->text().toInt();

        QSize imageSize = ImageProcessingThread->GetNode("GetImageNode")->GetImageSize();

        int newH = ImageTool::Map(newW, imageSize.width(), imageSize.height());

        ui->leImageHeight->setText(QString::number(newH));

        emit GotResizePara(cv::Size(newW, newH));

        SaveDetectingUI();
    });
    connect(ui->leImageHeight, &QLineEdit::returnPressed,
    [=] (){
        int newH = ui->leImageHeight->text().toInt();

        QSize imageSize = ImageProcessingThread->GetNode("GetImageNode")->GetImageSize();

        int newW = ImageTool::Map(newH, imageSize.height(), imageSize.width());

        ui->leImageWidth->setText(QString::number(newW));

        emit GotResizePara(cv::Size(newW, newH));

        SaveDetectingUI();
    });

    connect(ui->tbAutoResizeImage, &QToolButton::toggled, [=](bool checked)
    {
        TaskNode* resizeImageNode = ImageProcessingThread->GetNode("ResizeImageNode");

        if (checked)
        {
            resizeImageNode->IsPass = false;
        }
        else
        {
            resizeImageNode->IsPass = true;
        }
    });
        
    connect(ImageProcessingThread->GetNode("DisplayImageNode"), SIGNAL(HadOutput(QPixmap)), ui->gvImageViewer, SLOT(SetImage(QPixmap)));
//    connect(ImageProcessingThread->GetNode("DisplayImageNode"), SIGNAL(HadOutput(QPixmap)), ui->graphicsView, SLOT(SetImage(QPixmap)));

    connect(ParameterPanel, SIGNAL(ColorFilterValueChanged(QList<int>)), ImageProcessingThread->GetNode("ColorFilterNode"), SLOT(Input(QList<int>)));
    connect(ParameterPanel, SIGNAL(BlurSizeChanged(int)), ImageProcessingThread->GetNode("ColorFilterNode"), SLOT(Input(int)));
    connect(ParameterPanel, SIGNAL(ColorInverted(bool)), ImageProcessingThread->GetNode("ColorFilterNode"), SLOT(Input(bool)));

    connect(this, SIGNAL(GotObjects(QList<Object>)), ImageProcessingThread->GetNode("VisibleObjectsNode"), SLOT(Input(QList<Object>)));

    connect(this, SIGNAL(GotMappingMatrix(QMatrix)), ImageProcessingThread->GetNode("VisibleObjectsNode"), SLOT(Input(QMatrix)));
    connect(this, SIGNAL(GotOjectFilterInfo(Object)), ImageProcessingThread->GetNode("GetObjectsNode"), SLOT(Input(Object)));

//    connect(ImageProcessingThread->GetNode("GetObjectsNode"), SIGNAL(HadOutput(QList<Object>)), this, SLOT(UpdateObjectsToImageViewer(QList<Object>)));
//    connect(ImageProcessingThread->GetNode("GetObjectsNode"), SIGNAL(QList<QSharedPointer<Object>>), this, SLOT(UpdateObjectsToImageViewer(QList<QSharedPointer<Object>>)));
    connect(ImageProcessingThread->GetNode("GetObjectsNode"), SIGNAL(HadOutput(QList<QPolygonF>)), ui->gvImageViewer, SLOT(DrawObjects(QList<QPolygonF>)));
//    connect(ImageProcessingThread->GetNode("VisibleObjectsNode"), SIGNAL(HadOutput(QList<ObjectInfo>)), ImageProcessingThread, SLOT(GotVisibleObjects2(QList<ObjectInfo>)));
    connect(ImageProcessingThread->GetNode("VisibleObjectsNode"), SIGNAL(HadOutput(QList<Object>)), ImageProcessingThread, SLOT(GotVisibleObjects(QList<Object>)));

    connect(ui->leDetectingObjectListName, &QLineEdit::returnPressed, this, [=](){ImageProcessingThread->ObjectsName = ui->leDetectingObjectListName->text();});

//    connect(ImageProcessingThread->GetNode("GetObjectsNode"), SIGNAL(Done(int)), TrackingManagerInstance, SLOT(SaveDetectPosition(int)));

//    connect(ImageProcessingThread->GetNode("TrackingObjectsNode"), SIGNAL(HadOutput(QList<Object>&)), TrackingObjectTable, SLOT(UpdateTable(QList<Object>&)));
//    QTimer::singleShot(1000, [this](){

//    });

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

    // Tạo một QPalette mới từ QPalette hiện tại của textEdit
    QPalette p = ui->pteGcodeArea->palette();

    // Thiết lập màu cho văn bản
    p.setColor(QPalette::Text, QColor("#888888"));

    // Áp dụng QPalette mới cho textEdit
    ui->pteGcodeArea->setPalette(p);

    highlighter = new GCodeHighlighter(ui->pteGcodeArea->document());

    ui->pteGcodeArea->setTabWidth(4);
    ui->pteScriptFunction->setTabWidth(4);

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
}

void RobotWindow::InitUIController()
{
    connect(&UpdateUITimer, &QTimer::timeout, this, &RobotWindow::UpdateRobotPositionToUI);
    UpdateUITimer.start(100);

    connect(ui->pbHome, &QPushButton::clicked, this, [=](){emit Send(DeviceManager::ROBOT, "G28");});    

    connect(ui->tbCopyRobotPosition, &QPushButton::clicked, [=]()
    {
        // Copy giá trị vào clipboard
        QString text = QString("%1, %2, %3, %4, %5, %6").arg(ui->leX->text()).arg(ui->leY->text()).arg(ui->leZ->text()).arg(ui->leW->text()).arg(ui->leU->text()).arg(ui->leV->text());
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(text);
        
    });

    connect(ui->leX, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].X = ui->leX->text().toFloat(); UpdateVariable("X", QString::number(RobotParameters[RbID].X)); emit Send(DeviceManager::ROBOT, QString("G01 X") + ui->leX->text());});
    connect(ui->leY, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].Y = ui->leY->text().toFloat(); UpdateVariable("Y", QString::number(RobotParameters[RbID].Y));emit Send(DeviceManager::ROBOT, QString("G01 Y") + ui->leY->text());});
    connect(ui->leZ, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].Z = ui->leZ->text().toFloat(); UpdateVariable("Z", QString::number(RobotParameters[RbID].Z));emit Send(DeviceManager::ROBOT, QString("G01 Z") + ui->leZ->text());});
    connect(ui->leW, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].W = ui->leW->text().toFloat(); UpdateVariable("W", QString::number(RobotParameters[RbID].W));emit Send(DeviceManager::ROBOT, QString("G01 W") + ui->leW->text());});
    connect(ui->leU, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].U = ui->leU->text().toFloat(); UpdateVariable("U", QString::number(RobotParameters[RbID].U));emit Send(DeviceManager::ROBOT, QString("G01 U") + ui->leU->text());});
    connect(ui->leV, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].V = ui->leV->text().toFloat(); UpdateVariable("V", QString::number(RobotParameters[RbID].V));emit Send(DeviceManager::ROBOT, QString("G01 V") + ui->leV->text());});

    connect(ui->pbSubPitch, &QPushButton::clicked, [=](){MoveRobot("V", 0 - RobotParameters[RbID].Step);});
    connect(ui->pbPlusPitch, &QPushButton::clicked, [=](){MoveRobot("V", RobotParameters[RbID].Step);});
    connect(ui->pbSubYaw, &QPushButton::clicked, [=](){MoveRobot("U", 0 - RobotParameters[RbID].Step);});
    connect(ui->pbPlusYaw, &QPushButton::clicked, [=](){MoveRobot("U", RobotParameters[RbID].Step);});
    connect(ui->pbSubRoll, &QPushButton::clicked, [=](){MoveRobot("W", 0 - RobotParameters[RbID].Step);});
    connect(ui->pbPlusRoll, &QPushButton::clicked, [=](){MoveRobot("W", RobotParameters[RbID].Step);});
    connect(ui->pbUp, &QPushButton::clicked, [=](){MoveRobot("Z", RobotParameters[RbID].Step);});
    connect(ui->pbDown, &QPushButton::clicked, [=](){MoveRobot("Z", 0 - RobotParameters[RbID].Step);});
    connect(ui->pbForward, &QPushButton::clicked, [=](){MoveRobot("Y", RobotParameters[RbID].Step);});
    connect(ui->pbBackward, &QPushButton::clicked, [=](){MoveRobot("Y", 0 - RobotParameters[RbID].Step);});
    connect(ui->pbLeft, &QPushButton::clicked, [=](){MoveRobot("X", 0 - RobotParameters[RbID].Step);});
    connect(ui->pbRight, &QPushButton::clicked, [=](){MoveRobot("X", RobotParameters[RbID].Step);});
    connect(ui->leVelocity, &QLineEdit::returnPressed, this, &RobotWindow::UpdateVelocity);
    connect(ui->leAccel, &QLineEdit::returnPressed, this, &RobotWindow::UpdateAccel);
    connect(ui->leStartSpeed, &QLineEdit::returnPressed, this, &RobotWindow::UpdateStartSpeed);
    connect(ui->leEndSpeed, &QLineEdit::returnPressed, this, &RobotWindow::UpdateEndSpeed);
    connect(ui->leJerk, &QLineEdit::returnPressed, this, &RobotWindow::UpdateJerk);
}

void RobotWindow::InitCalibration()
{
    connect(ui->pbImageMapping, &QPushButton::clicked, this, &RobotWindow::UpdateRealPositionOfCalibPoints);

    QObject::connect(ui->cbCalibType, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
            QString selectedText = ui->cbCalibType->itemText(index);
            if (index == 1)
            {
                ui->leCalibOffset_X->setText("-230");
                ui->leCalibOffset_Y->setText("0");
                ui->leRealityP1P2Distance->setText("80");
            }
            else if (index == 0)
            {
                ui->leCalibOffset_X->setText("0");
                ui->leCalibOffset_Y->setText("0");
                ui->leRealityP1P2Distance->setText("100");
            }
        });

    connect(ui->tbPastePoint1, &QPushButton::clicked, [=]()
    { 
        pastePointValues(ui->leRealityPoint1X, ui->leRealityPoint1Y, NULL);

        UpdateRealPositionOfCalibPoints();
    });

    connect(ui->tbPastePoint2, &QPushButton::clicked, [=]()
    { 
        pastePointValues(ui->leRealityPoint2X, ui->leRealityPoint2Y, NULL);

        UpdateRealPositionOfCalibPoints();
    });

    connect(ui->tbPasteOffsetPoint, &QPushButton::clicked, [=]()
    { 
        pastePointValues(ui->leCalibOffset_X, ui->leCalibOffset_Y, NULL);

        UpdateRealPositionOfCalibPoints();
    });
}

void RobotWindow::InitEvents()
{
    // -------- Debug Log --------
//    connect(ui->tbExpandLogBox, &QToolButton::toggled, this, &RobotWindow::ExpandLogBox);


    // ------------- --------------
    connect(ui->pbSaveGcode, SIGNAL(clicked(bool)), this, SLOT(SaveProgram()));
    connect(ui->pbSaveFunctionScripts, SIGNAL(clicked(bool)), this, SLOT(SaveProgram()));


    connect(ui->pbExecuteGcodes, SIGNAL(clicked(bool)), this, SLOT(ExecuteProgram()));
    connect(ui->pteGcodeArea, SIGNAL(lineClicked(int, QString)), this, SLOT(ExecuteCurrentLine(int, QString)));

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

    connect(ui->pbReadI0, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI1, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI2, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadI3, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadIx, SIGNAL(clicked()), this, SLOT(RequestValueInput()));

    connect(ui->pbReadA0, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadA1, SIGNAL(clicked()), this, SLOT(RequestValueInput()));
    connect(ui->pbReadAx, SIGNAL(clicked()), this, SLOT(RequestValueInput()));


    //------------- 2D control ----------------

    //------------- 3D control -------------------

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

    connect(ui->cbEditGcodeLock, SIGNAL(stateChanged(int)), ui->pteGcodeArea, SLOT(setLockState(bool)));

    //------------ Image Processing -----------


    connect(ui->pbRunExternalScript, SIGNAL(clicked(bool)), this, SLOT(RunExternalScript()));
    connect(ui->pbExternalScriptOpen, SIGNAL(clicked(bool)), this, SLOT(OpenExternalScriptFolder()));

    connect(ui->cbSourceForImageProvider, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectImageProviderOption(int)));

    // ---- Setting ----

    //----------- Camera -----------


    //---------- Menu -----------

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

}

void RobotWindow::DisablePositionUpdatingEvents()
{
    ui->leX->blockSignals(true);
    ui->leY->blockSignals(true);
    ui->leZ->blockSignals(true);
    ui->leW->blockSignals(true);
    ui->leU->blockSignals(true);
    ui->leV->blockSignals(true);

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
                RobotParameters[RbID].Step = paras[i + 2].toFloat();
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
                    QString gcode = QString("G01 X%1 Y%2 Z%3").arg(RobotParameters[RbID].X).arg(RobotParameters[RbID].Y).arg(RobotParameters[RbID].Z);

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
    LoadGcode(filePath);
}

void RobotWindow::LoadGcode(QString filePath)
{
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

        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        ui->lbSelectedProgram->setText(fileName);

        ui->pbFormat->click();
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
        item->setText(QString("program") + QString::number(id));

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

void RobotWindow::LoadPlugin()
{
    pluginList = new QList<DeltaXPlugin*>();

    QDir dir(QApplication::applicationDirPath());
    dir.cd("plugin");

    QStringList plugins = getPlugins(dir.path());

    initPlugins(plugins);
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

    connect(GcodeScriptThread, SIGNAL(Moved(int)), this, SLOT(HighLineCurrentLine(int)));
    connect(GcodeScriptThread, SIGNAL(SendGcodeToDevice(QString, QString)), DeviceManagerInstance, SLOT(SendGcode(QString, QString)));
    connect(GcodeScriptThread, &GcodeScript::Finished, [=](){ ui->pbExecuteGcodes->setChecked(false);});
    connect(GcodeScriptThread, SIGNAL(SendGcodeToDevice(QString, QString)), this, SLOT(UpdateGcodeValueToDeviceUI(QString, QString)));
    connect(GcodeScriptThread, SIGNAL(SaveVariable(QString, QString)), this, SLOT(UpdateVariable(QString, QString)));

//    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects()), this, SLOT(ClearObjectsToVariableTable()));
//    connect(GcodeScriptThread, SIGNAL(DeleteObject1()), this, SLOT(DeleteFirstVariable()));
//    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects()), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(ClearOutput()));
//    connect(GcodeScriptThread, SIGNAL(DeleteObject(int)), ImageProcessingThread->GetNode("TrackingObjectsNode"), SLOT(DeleteOutput(int)));

    connect(GcodeScriptThread, &GcodeScript::PauseCamera, [=](){ CameraTimer.stop();});
    connect(GcodeScriptThread, &GcodeScript::ResumeCamera, [=](){ CameraTimer.start(ui->leCaptureInterval->text().toInt());});
    connect(GcodeScriptThread, &GcodeScript::CaptureCamera, CameraInstance, &Camera::GeneralCapture);
    connect(GcodeScriptThread, &GcodeScript::CaptureAndDetectRequest, CameraInstance, &Camera::CaptureAndDetect);

    connect(GcodeScriptThread, &GcodeScript::UpdateTrackingRequest, TrackingManagerInstance, &TrackingManager::UpdateTracking);
    connect(GcodeScriptThread, &GcodeScript::ChangeExternalVariable, TrackingManagerInstance, &TrackingManager::UpdateVariable);
    connect(GcodeScriptThread, &GcodeScript::AddObject, TrackingManagerInstance, &TrackingManager::AddObject);
    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects(QString)), TrackingManagerInstance, SLOT(ClearObjects(QString)));
    connect(ConnectionManager, &SocketConnectionManager::objectUpdated, TrackingManagerInstance, &TrackingManager::AddObject);
    connect(ConnectionManager, SIGNAL(blobUpdated(QStringList)), ImageProcessingThread->GetNode("GetObjectsNode"), SLOT(Input(QStringList)));
    connect(ConnectionManager, SIGNAL(gcodeReceived(QString)), GcodeScriptThread, SLOT(ReceivedGcode(QString)));


    connect(TrackingManagerInstance, &TrackingManager::GotResponse, GcodeScriptThread, &GcodeScript::GetResponse);

    GcodeScriptThread->thread()->start();

    GcodeScripts.append(GcodeScriptThread);

    connect(GcodeScriptThread, &GcodeScript::CatchVariable2, this, &RobotWindow::UpdateVarToView);
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
    thread->start();

    AddTrackingThread();

    ObjectModel->setObjectInfoList(TrackingManagerInstance->Trackings.at(0)->TrackedObjects);

    connect(CameraInstance, SIGNAL(StartedCapture(int)), TrackingManagerInstance, SLOT(SaveCapturePosition(int)));
    connect(DeviceManagerInstance, &DeviceManager::GotEncoderPosition, TrackingManagerInstance, &TrackingManager::SetEncoderPosition);
}

void RobotWindow::AddTrackingThread()
{
    Tracking* tracking = new Tracking();
    QThread* trackingThread = new QThread(this);
    tracking->moveToThread(trackingThread);
    connect(tracking->thread(), &QThread::finished, tracking, &QObject::deleteLater);

    connect(ui->pbSaveTrackingManager, &QPushButton::clicked, [=]()
    {
        int selectedEncoderID = ui->cbSelectedTracking->currentText().toInt();

        TrackingManagerInstance->Trackings.at(selectedEncoderID)->VelocityVector = VariableManager::instance().getVariable(ui->leVelocityVector->text()).value<QVector3D>();
        TrackingManagerInstance->Trackings.at(selectedEncoderID)->VectorName = ui->leVectorName->text();
    });
    connect(ui->cbReverseEncoderValue, SIGNAL(clicked(bool)), tracking, SLOT(SetEncoderReverse(bool)));

    connect(tracking, SIGNAL(SendGcodeRequest(QString, QString)), DeviceManagerInstance, SLOT(SendGcode(QString, QString)));
    connect(tracking, SIGNAL(UpdateTrackingDone()), TrackingManagerInstance, SLOT(OnDoneUpdateTracking()));

    connect(ImageProcessingThread, SIGNAL(mappedDetectedObjects(QList<ObjectInfo>, QString)), tracking, SLOT(UpdateTrackedObjects(QList<ObjectInfo>, QString)));
    connect(tracking, SIGNAL(TestPointUpdated(QVector3D)), this, SLOT(UpdateTestPoint(QVector3D)));

    trackingThread->start();

    tracking->ID = TrackingManagerInstance->Trackings.count();
    TrackingManagerInstance->Trackings.append(tracking);


}

void RobotWindow::LoadTrackingThread()
{
    int id = ui->cbSelectedTracking->currentIndex();
    ui->leSelectedTrackingObjectList->setText(TrackingManagerInstance->Trackings.at(id)->ListName);
    ui->cbTrackingEncoderSource->setCurrentText(TrackingManagerInstance->Trackings.at(id)->EncoderName);
    ui->leVectorName->setText(TrackingManagerInstance->Trackings.at(id)->VectorName);

}

void RobotWindow::LoadSettings()
{
    LoadGeneralSettings();
//    LoadJoggingSettings(setting);
//    Load2DSettings(setting);
//    Load3DSettings(setting);
//    LoadExternalDeviceSettings(setting);
//    LoadTerminalSettings(setting);
//    LoadGcodeEditorSettings(setting);
    LoadObjectDetectorSetting();
//    LoadDrawingSetting(setting);
//    LoadPluginSetting(setting);
}

void RobotWindow::LoadGeneralSettings()
{
    QStringList devices = QStringList() << "robot" << "conveyor" << "encoder" << "slider" << "device";

    for (int i = 0; i < devices.count(); i++)
    {
        QString device = devices.at(i);
        
        for (int id = 0; id < 20; id++)
        {
            QString prefix = ProjectName + "." + device + QString::number(id);

            if (VariableManager::instance().containsSubKey(prefix))
            {
                QString comName = VariableManager::instance().getVar(prefix + ".COM.Name", "NONE").toString();
                QString state = VariableManager::instance().getVar(prefix + ".COM.State", false).toString();

                if (state == "open" && comName != "NONE")
                {
                    emit ChangeDeviceState(i, true, comName);
                }
            }
            else
            {
                break;
            }
        }
    }
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
    ui->leConveyorXPosition->setText(setting->value("MovingValue").toString());

    if (connectionState == true)
    {

    }

    setting->endGroup();

    //---- Encoder -----

    setting->beginGroup("Encoder");

    connectionState = setting->value("State", false).toBool();
    comPort = setting->value("ComPort", "").toString();
    baudrate = setting->value("Baudrate", 115200).toInt();

    if (connectionState == true && comPort != "")
    {

    }

    setting->endGroup();

    //---- Slider -----

    setting->beginGroup("Slider");

    connectionState = setting->value("State", false).toBool();
    comPort = setting->value("ComPort", "COM1").toString();
    baudrate = setting->value("Baudrate", 115200).toInt();

    if (connectionState == true)
    {

    }

    setting->endGroup();

    //---- MCU -----

    setting->beginGroup("MCU");

    connectionState = setting->value("State", false).toBool();
    comPort = setting->value("ComPort", "COM1").toString();
    baudrate = setting->value("Baudrate", 115200).toInt();

    if (connectionState == true)
    {

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

void RobotWindow::LoadObjectDetectorSetting()
{
    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";

    ui->gvImageViewer->LoadSetting(prefix);

    QPointF calibPoint1 = VariableManager::instance().getVar(prefix + "RealCalibPoint1").toPointF();
    QPointF calibPoint2 = VariableManager::instance().getVar(prefix + "RealCalibPoint2").toPointF();
    ui->leRealityPoint1X->setText(QString::number(calibPoint1.x()));
    ui->leRealityPoint1Y->setText(QString::number(calibPoint1.y()));
    ui->leRealityPoint2X->setText(QString::number(calibPoint2.x()));
    ui->leRealityPoint2Y->setText(QString::number(calibPoint2.y()));

    UpdateRealPositionOfCalibPoints();

    //------------

    if (VariableManager::instance().getVar(prefix + "WarpEnable", false).toBool() == true)
    {
        ui->pbWarpTool->setChecked(true);
//        ui->pbWarpTool->click();
    }
    else
    {
        ui->pbWarpTool->setChecked(false);
//        ui->pbWarpTool->click();
    }

    if (VariableManager::instance().getVar(prefix + "CropEnable", false).toBool() == true)
    {
        ui->pbCropTool->setChecked(true);
//        ui->pbCropTool->click();
    }
    else
    {
        ui->pbCropTool->setChecked(false);
//        ui->pbCropTool->click();
    }

    EditImage(ui->pbWarpTool->isChecked(), ui->pbCropTool->isChecked());

    ui->cbSourceForImageProvider->setCurrentText(VariableManager::instance().getVar(prefix + "ImageSource", ui->cbSourceForImageProvider->currentText()).toString());

    ui->leCaptureInterval->setText(VariableManager::instance().getVar(prefix + "WebcamInterval", ui->leCaptureInterval->text()).toString());

    ui->leImageWidth->setText(VariableManager::instance().getVar(prefix + "ResizeWidth", ui->leImageWidth->text()).toString());
    ui->leImageHeight->setText(VariableManager::instance().getVar(prefix + "ResizeHeight", ui->leImageHeight->text()).toString());

    emit GotResizePara(cv::Size(ui->leImageWidth->text().toInt(), ui->leImageHeight->text().toInt()));



//    Object& obj = ImageProcessingThread->GetNode("GetObjectsNode")->GetInputObject();

//    obj.Width.Image = setting->value("ObjectWidth", obj.Width.Image).toFloat();
//    obj.Length.Image = setting->value("ObjectLength", obj.Length.Image).toFloat();

//    obj.Width.Real = setting->value("RealObjectWidth", ui->leWRec->text()).toFloat();
//    obj.Length.Real = setting->value("RealObjectLength", ui->leLRec->text()).toFloat();


//    obj.RangeWidth.Max.Image = setting->value("ImageMaxObjectWidth", ui->leMaxWRec->text()).toFloat();
//    obj.RangeWidth.Min.Image = setting->value("ImageMinObjectWidth", ui->leMinWRec->text()).toFloat();
//    obj.RangeLength.Max.Image = setting->value("ImageMaxObjectLength", ui->leMaxLRec->text()).toFloat();
//    obj.RangeLength.Min.Image = setting->value("ImageMinObjectLength", ui->leMinLRec->text()).toFloat();

//    ui->leWRec->setText(QString::number(obj.Width.Real));
//    ui->leLRec->setText(QString::number(obj.Length.Real));


//    obj.RangeWidth.Max.Real = setting->value("MaxObjectWidth", ui->leMaxWRec->text()).toFloat();
//    obj.RangeWidth.Min.Real = setting->value("MinObjectWidth", ui->leMinWRec->text()).toFloat();
//    obj.RangeLength.Max.Real = setting->value("MaxObjectLength", ui->leMaxLRec->text()).toFloat();
//    obj.RangeLength.Min.Real = setting->value("MinObjectLength", ui->leMinLRec->text()).toFloat();

//    ui->leMinWRec->setText(QString::number(obj.RangeWidth.Min.Real));
//    ui->leMaxWRec->setText(QString::number(obj.RangeWidth.Max.Real));
//    ui->leMinLRec->setText(QString::number(obj.RangeLength.Min.Real));
//    ui->leMaxLRec->setText(QString::number(obj.RangeLength.Max.Real));

//    emit GotOjectFilterInfo(obj);

//    ui->leObjectOverlay->setText(setting->value("TrackingError", ui->leObjectOverlay->text()).toString());


//    QPointF calibPoint1 = setting->value("RealCalibPoint1", QPointF(ui->leRealityPoint1X->text().toFloat(), ui->leRealityPoint1Y->text().toFloat())).toPointF();
//    QPointF calibPoint2 = setting->value("RealCalibPoint2", QPointF(ui->leRealityPoint2X->text().toFloat(), ui->leRealityPoint2Y->text().toFloat())).toPointF();
//    ui->leRealityPoint1X->setText(QString::number(calibPoint1.x()));
//    ui->leRealityPoint1Y->setText(QString::number(calibPoint1.y()));
//    ui->leRealityPoint2X->setText(QString::number(calibPoint2.x()));
//    ui->leRealityPoint2Y->setText(QString::number(calibPoint2.y()));

    ui->cbDetectingAlgorithm->setCurrentText(VariableManager::instance().getVariable(prefix + "DetectAlgorithm", ui->cbDetectingAlgorithm->currentText()).toString());

//    ui->lePythonUrl->setText(setting->value("ExternalScriptUrl", ui->lePythonUrl->text()).toString());
    ui->cbImageSource->setCurrentText(VariableManager::instance().getVariable(prefix + "ImageSource", ui->cbImageSource->currentText()).toString());

//    ui->leEdgeThreshold->setText(setting->value("EdgeThreshold", ui->leEdgeThreshold->text()).toString());
//    ui->leCenterThreshold->setText(setting->value("CenterThreshold", ui->leCenterThreshold->text()).toString());
//    ui->leMinRadius->setText(setting->value("MinRadius", ui->leMinRadius->text()).toString());
//    ui->leMaxRadius->setText(setting->value("MaxRadius", ui->leMaxRadius->text()).toString());

//    ParameterPanel->RequestValue();

//    setting->endGroup();
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

}

void RobotWindow::SaveJoggingSettings(QSettings *setting)
{
    setting->beginGroup("Jogging");
    setting->endGroup();
}

void RobotWindow::Save2DSettings(QSettings *setting)
{
    setting->beginGroup("Jogging");
    setting->endGroup();
}

void RobotWindow::Save3DSettings(QSettings *setting)
{
    setting->beginGroup("3D");

    setting->endGroup();
}

void RobotWindow::SaveExternalDeviceSettings(QSettings *setting)
{

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

    setting->setValue("IoUThreshold", ui->leIoUThreshold->text());
    setting->setValue("DistanceThreshold", ui->leDistanceThreshold->text());

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

void RobotWindow::InitDefaultValue()
{
    ChangeEncoderType(0);

    ui->pbSaveTrackingManager->click();
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
    QString com_name = jsonObject.value("com_name").toString();
    QString state = jsonObject.value("state").toString();

    UpdateVariable(device + QString::number(id) + "." + "COM.Name", com_name);
    UpdateVariable(device + QString::number(id) + "." + "COM.State", state);

    QString prefix = ProjectName + "." + device + QString::number(id) + ".";

    if (device == "robot" && id == ui->cbSelectedRobot->currentIndex())
    {
        float x = jsonObject.value("x").toDouble();
        float y = jsonObject.value("y").toDouble();
        float z = jsonObject.value("z").toDouble();
        float w = jsonObject.value("w").toDouble();
        float u = jsonObject.value("u").toDouble();
        float v = jsonObject.value("v").toDouble();

        float home_x = jsonObject.value("home_x").toDouble();
        float home_y = jsonObject.value("home_y").toDouble();
        float home_z = jsonObject.value("home_z").toDouble();
        float home_w = jsonObject.value("home_w").toDouble();
        float home_u = jsonObject.value("home_u").toDouble();
        float home_v = jsonObject.value("home_v").toDouble();

        ReceiveHomePosition(home_x, home_y, home_z, home_w, home_u, home_v);

        RobotParameters[RbID].X = x;
        RobotParameters[RbID].Y = y;
        RobotParameters[RbID].Z = z;
        RobotParameters[RbID].W = w;
        RobotParameters[RbID].U = u;
        RobotParameters[RbID].V = v;

        if (state == "open")
        {
            ui->pbConnect->setText("Disconnect");
        }
        else
        {
            ui->pbConnect->setText("Connect");
        }

        ui->lbComName->setText(jsonObject.value("com_name").toString());

//        VariableManager::instance().updateVar(prefix + "Port", com_name);
//        VariableManager::instance().updateVar(prefix + "State", state);
    }

    else if (device == "device" && id == getIDfromName(ui->cbSelectedDevice->currentText()))
    {
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

    else if (device == "conveyor" && id == getIDfromName(ui->cbSelectedConveyor->currentText()))
    {
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

    else if (device == "encoder" && id == getIDfromName(ui->cbSelectedEncoder->currentText()))
    {
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

void RobotWindow::GetDeviceResponse(QString idName, QString response)
{
    UpdateTermite(idName, response, 0);

    static QTime previousEncoderUITime = QTime::currentTime();
    int timeDiff = previousEncoderUITime.msecsTo(QTime::currentTime());
    if (timeDiff < 500)
        return;
    previousEncoderUITime = QTime::currentTime();

    if (idName.contains("device"))
    {
        DisplayTextFromExternalMCU(response);
    }

    if (idName.contains("conveyor"))
    {
        if (response.contains("P"))
        {
            int id = response.mid(1,1).toInt();
            float value = response.mid(3).toFloat();

            if (getIDfromName(ui->cbSelectedEncoder->currentText()) == id)
            {
                ui->leEncoderCurrentPosition->setText(QString::number(value));
                float velocity = (value - encoderLastValue) * 1000/ timeDiff;
                encoderLastValue = value;
                ui->leEncoderVelocity->setText(QString::number(velocity));
            }
        }
    }

    if (idName.contains("encoder"))
    {


        idName = idName.mid(7);
        if (response.contains("P"))
        {
            int index = idName.toInt();
            QString value;
            if (response.contains(":"))
            {
                value = response.mid(3);
            }
            else
            {
                value = response.mid(1);
            }

            if (ui->cbSelectedEncoder->currentIndex() == index)
            {
                ui->leEncoderCurrentPosition->setText(value);
                float velocity = (value.toFloat() - encoderLastValue) * 1000 / timeDiff;
                encoderLastValue = value.toFloat();
                ui->leEncoderVelocity->setText(QString::number(velocity));
            }
        }
    }
}

void RobotWindow::UpdateVarToView(QString fullKey, QVariant value)
{
    QStandardItem *parent = VarViewModel.invisibleRootItem();
    UnityTool::UpdateVarToModel(parent, fullKey, value);
}

void RobotWindow::UpdateObjectsToView()
{
    for (int i = 0; i < TrackingManagerInstance->Trackings.count();i++)
    {
        if (ui->leDetectingObjectListName->text() == TrackingManagerInstance->Trackings.at(i)->ListName)
        {
            ObjectModel->setObjectInfoList(TrackingManagerInstance->Trackings.at(i)->TrackedObjects);
        }
    }
}

void RobotWindow::Load3DComponents()
{

}

void RobotWindow::ConnectRobot()
{
    if (ui->tbAutoScanRobot->isChecked() == true)
    {
        OpenLoadingPopup();
        emit ChangeDeviceState(DeviceManager::ROBOT, (ui->pbConnect->text() == "Connect")?true:false, "auto");
        return;
    }

    if (ui->pbConnect->text() != "Connect")
    {
        emit ChangeDeviceState(DeviceManager::ROBOT, false, "");
        return;
    }

    QStringList items;

    Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial(portInfo);
        if(serial.open(QIODevice::ReadWrite))
        {
            items << portInfo.portName() + " - " + portInfo.description();
            serial.close();
        }
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
            emit ChangeDeviceState(DeviceManager::ROBOT, (ui->pbConnect->text() == "Connect")?true:false, comName);
        }
    }
}

void RobotWindow::SelectImageProviderOption(int option)
{
    ui->fImageSource->setHidden(true);
    ui->fWebcamSource->setHidden(false);

    QString text = ui->cbSourceForImageProvider->itemText(option);

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    VariableManager::instance().updateVar(prefix + "ImageSource",text);

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

    QPalette p = ui->pteGcodeArea->palette();

    // Thiết lập màu cho văn bản
    p.setColor(QPalette::Text, QColor("#DBDBDC"));

    // Áp dụng QPalette mới cho textEdit
    ui->pteGcodeArea->setPalette(p);

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

void RobotWindow::ChangeSelectedRobot(int id)
{
    if (ui->cbSelectedRobot->currentText() == "+")
    {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->cbSelectedRobot->model());
        QStandardItem *item = model->item(id);
        item->setText(QString("robot") + QString::number(id));

        RobotPara robotPara;
        RobotParameters.append(robotPara);

        ui->cbSelectedRobot->addItem("+");
    }

    DeviceManagerInstance->SelectedRobotID = id;
    RbID = id;

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

void RobotWindow::ChangeRobotModel(int id)
{
    DeviceManagerInstance->Robots.at(ui->cbSelectedRobot->currentIndex())->SetRobotModel(ui->cbRobotModel->currentText());

    if (id == 0 || id == 1)
    {
        ui->gbOutput->setVisible(false);
        ui->gbInput->setVisible(false);
    }
    else if (id == 2)
    {
        ui->gbOutput->setVisible(true);
        ui->gbInput->setVisible(true);
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
//    SaveProgram();

    if (ui->leZ->text().toFloat() > -200)
    {
        QMessageBox::information(
                this,
                tr("Required Action"),
                tr("The robot must return to Home before running the program.")
            );

        ui->pbExecuteGcodes->setChecked(false);

        return;
    }

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

    currentScript->DefaultRobot = ui->cbSelectedRobot->currentText();
    currentScript->DefaultConveyor = ui->cbSelectedConveyor->currentText();
    currentScript->DefaultEncoder = ui->cbSelectedEncoder->currentText();
    currentScript->DefaultSlider = ui->cbSelectedSlider->currentText();
    currentScript->DefaultDevice = ui->cbSelectedDevice->currentText();

    QMetaObject::invokeMethod(currentScript, "ExecuteGcode", Qt::QueuedConnection, Q_ARG(QString, ui->pteGcodeArea->toPlainText()), Q_ARG(int, startMode), Q_ARG(QString, ui->pteScriptFunction->toPlainText()));

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

void RobotWindow::ExecuteCurrentLine(int linNumber, QString lineText)
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    GcodeScript* currentScript = GcodeScripts.at(threadId);

    if (ui->cbEditGcodeLock->isChecked() == false)
	{
		return;
	}

    QMetaObject::invokeMethod(currentScript, "ExecuteGcode", Qt::QueuedConnection, Q_ARG(QString, lineText), Q_ARG(int, GcodeScript::BEGIN), Q_ARG(QString, ui->pteScriptFunction->toPlainText()));

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

void RobotWindow::UpdatePositionControl(RobotPara robotPara)
{
    RobotParameters[RbID] = robotPara;
}

void RobotWindow::ReceiveHomePosition(float x, float y, float z, float w, float u, float v)
{
    RobotParameters[RbID].X = RobotParameters[RbID].XHome = x;
    RobotParameters[RbID].Y = RobotParameters[RbID].YHome = y;
    RobotParameters[RbID].Z = RobotParameters[RbID].ZHome = z;
    RobotParameters[RbID].W = RobotParameters[RbID].WHome = w;
    RobotParameters[RbID].U = RobotParameters[RbID].UHome = u;
    RobotParameters[RbID].V = RobotParameters[RbID].VHome = v;

//    UpdateVariables(QString("X=%1;Y=%2;Z=%3;W=%4;U=%5;V=%6").arg(x).arg(y).arg(z).arg(w).arg(u).arg(v));
}

void RobotWindow::UpdateVelocity()
{
    QString value = ui->leVelocity->text();
    RobotParameters[RbID].Set("F", value.toFloat());
    UpdateVariable("F", value);
    emit Send(DeviceManager::ROBOT, QString("G01 F") + value);
}

void RobotWindow::UpdateAccel()
{
    QString value = ui->leAccel->text();
    RobotParameters[RbID].Set("A", value.toFloat());
    UpdateVariable("A", value);
    emit Send(DeviceManager::ROBOT, QString("M204 A") + ui->leAccel->text());
}

void RobotWindow::UpdateStartSpeed()
{
    QString value = ui->leStartSpeed->text();
    RobotParameters[RbID].Set("S", value.toFloat());
    UpdateVariable("S", value);
    emit Send(DeviceManager::ROBOT, QString("M205 S") + ui->leStartSpeed->text());
}

void RobotWindow::UpdateEndSpeed()
{
    QString value = ui->leEndSpeed->text();
    RobotParameters[RbID].Set("E", value.toFloat());
    UpdateVariable("E", value);
    emit Send(DeviceManager::ROBOT, QString("G01 E") + ui->leEndSpeed->text());
}

void RobotWindow::UpdateJerk()
{
    QString value = ui->leJerk->text();
    RobotParameters[RbID].Set("J", value.toFloat());
    UpdateVariable("J", value);
    emit Send(DeviceManager::ROBOT, QString("G01 J") + ui->leJerk->text());
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

    QString prefixS = "X Y Z W U V F A S E J";
    QStringList prefixs = prefixS.split(' ');

    foreach(QString prefix, prefixs)
    {
        QString value = GetValueInGcode(prefix, gcode);

        if (value != "")
        {
            UpdateVariable(prefix, value);
            RobotParameters[RbID].Set(prefix, value.toFloat());
        }
    }
}

void RobotWindow::MoveRobot(QString axis, float step)
{
    float value = RobotParameters[RbID].Get(axis) + step;
    RobotParameters[RbID].Set(axis, value);

    UpdateVariable(axis, QString::number(value));

    emit Send(DeviceManager::ROBOT, QString("G01 ") + axis + QString::number(value));
}

void RobotWindow::MoveRobotFollowObject(float x, float y, float angle)
{
//    emit Send(DeviceManager::ROBOT, QString("G01 X%1 Y%2 W%3").arg(x).arg(y).arg(angle));
    RobotParameters[RbID].X = x;
    RobotParameters[RbID].Y = y;

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

    if (!ui->leX->hasFocus())
    {
        ui->leX->setText(QString::number(RobotParameters[RbID].X));
    }
    if (!ui->leY->hasFocus())
    {
        ui->leY->setText(QString::number(RobotParameters[RbID].Y));
    }
    if (!ui->leZ->hasFocus())
    {
        ui->leZ->setText(QString::number(RobotParameters[RbID].Z));
    }
    if (!ui->leW->hasFocus())
    {
        ui->leW->setText(QString::number(RobotParameters[RbID].W));
    }
    if (!ui->leU->hasFocus())
    {
        ui->leU->setText(QString::number(RobotParameters[RbID].U));
    }
    if (!ui->leV->hasFocus())
    {
        ui->leV->setText(QString::number(RobotParameters[RbID].V));
    }
    if (!ui->leVelocity->hasFocus())
    {
        ui->leVelocity->setText(QString::number(RobotParameters[RbID].F));
    }
    if (!ui->leAccel->hasFocus())
    {
        ui->leAccel->setText(QString::number(RobotParameters[RbID].A));
    }
    if (!ui->leJerk->hasFocus())
    {
        ui->leJerk->setText(QString::number(RobotParameters[RbID].J));
    }
    if (!ui->leStartSpeed->hasFocus())
    {
        ui->leStartSpeed->setText(QString::number(RobotParameters[RbID].S));
    }
    if (!ui->leEndSpeed->hasFocus())
    {
        ui->leEndSpeed->setText(QString::number(RobotParameters[RbID].E));
    }

    if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        int id = ui->cbSelectedEncoder->currentText().toInt();
        if (TrackingManagerInstance->Trackings[id]->VirEncoder.IsActive() == true)
        {
            if (encoderUpdateTimer.elapsed() >= TrackingManagerInstance->Trackings[id]->VirEncoder.readInterval())
            {
                encoderUpdateTimer.restart();

                int selectedEncoderID = ui->cbSelectedEncoder->currentIndex();
                ui->leEncoderCurrentPosition->setText(QString::number(TrackingManagerInstance->Trackings.at(selectedEncoderID)->VirEncoder.readPosition()));
            }
        }
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

void RobotWindow::UpdateVariable(QString key, QVariant value)
{
    VariableManager::instance().Prefix = ProjectName;

    VariableManager::instance().updateVar(key, value);
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
    QString value = VariableManager::instance().getVar(name).toString() + '\n';

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

    ui->leConveyorXAbsolutePosition->setEnabled(false);
    ui->lbConveyorAbsolutePosition->setEnabled(false);
    ui->lbUnitOfConveyorMoving2->setEnabled(false);
    ui->pbMoveConveyorPosition->setEnabled(false);

    ui->leConveyorXPosition->setEnabled(false);
    ui->lbConveyorPosition->setEnabled(false);
    ui->lbUnitOfConveyorMoving->setEnabled(false);
    ui->pbMoveConveyorByDistance->setEnabled(false);

    if (index == 0)
    {
        ui->fConveyorX->setHidden(false);

        ui->leConveyorXPosition->setEnabled(true);
        ui->lbConveyorPosition->setEnabled(true);
        ui->lbUnitOfConveyorMoving->setEnabled(true);
        ui->pbMoveConveyorByDistance->setEnabled(true);
    }
    else if (index == 1)
    {
        ui->fConveyorX->setHidden(false);

        ui->leConveyorXAbsolutePosition->setEnabled(true);
        ui->lbConveyorAbsolutePosition->setEnabled(true);
        ui->lbUnitOfConveyorMoving2->setEnabled(true);
        ui->pbMoveConveyorPosition->setEnabled(true);
    }
    else if (index == 2)
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
        QSerialPort serial(portInfo);
        if(serial.open(QIODevice::ReadWrite))
        {
            items << portInfo.portName() + " - " + portInfo.description();
            serial.close();
        }
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
    if (ui->cbEncoderType->currentText() == "X Encoder")
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
    if (ui->cbEncoderType->currentText() == "X Encoder")
    {
        if (interval > 0)
            emit Send(DeviceManager::ENCODER, QString("M317 T%1").arg(interval));
        else
            emit Send(DeviceManager::ENCODER, QString("M317").arg(interval));
    }
    if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        if (interval < 100 && interval > 0)
        {
            interval = 100;
            ui->leEncoderInterval->setText(QString::number(interval));
        }

        if (interval > 0)
            TrackingManagerInstance->Trackings[id]->VirEncoder.start(interval);
        else
            TrackingManagerInstance->Trackings[id]->VirEncoder.stop();
    }
}

void RobotWindow::ResetEncoderPosition()
{
    QString interval = ui->leEncoderInterval->text();
    int selectedEncoderID = ui->cbSelectedEncoder->currentIndex();

    if (ui->cbEncoderType->currentText() == "Sub Encoder")
    {
        QString name = ui->cbSelectedEncoder->currentText();

        QString cmd = QString("M423 C%1").arg(name);
        emit Send(DeviceManager::CONVEYOR, cmd);
    }
    if (ui->cbEncoderType->currentText() == "X Encoder")
    {
        emit Send(DeviceManager::ENCODER, "M316 0");
//        ui->pbSetEncoderInterval->clicked(true);
    }
    if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        TrackingManagerInstance->Trackings[selectedEncoderID]->VirEncoder.reset();
    }
}

void RobotWindow::SetEncoderVelocity()
{
    int selectedEncoderID = ui->cbSelectedEncoder->currentIndex();

    TrackingManagerInstance->Trackings[selectedEncoderID]->VirEncoder.setVelocity(ui->leEncoderVelocity->text().toFloat());
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

            CameraInstance->RunningCamera = cameraID;

            CameraInstance->Width = ui->leImageWidth->text().toInt();
            CameraInstance->Height = ui->leImageHeight->text().toInt();

            QMetaObject::invokeMethod(CameraInstance, "OpenCamera", Qt::QueuedConnection, Q_ARG(int, cameraID));
            OpenLoadingPopup();
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
    QStringList imageNames;
    imageNames = QFileDialog::getOpenFileNames(this, tr("Open Image/Video"), "", tr("Image Files (*.png *.jpg *.bmp *.avi *.mp4)"));

    if (imageNames.empty())
        return;

    if (imageNames.at(0).contains(".avi") || imageNames.at(0).contains(".mp4"))
    {
        CameraInstance->WebcamInstance->open(imageNames.at(0).toStdString());

        if (!CameraInstance->WebcamInstance->isOpened())
        {
            return;
        }

        CameraInstance->WebcamInstance->open(imageNames.at(0).toStdString());
        CameraInstance->WebcamInstance->set(cv::CAP_PROP_FRAME_WIDTH, ui->leImageWidth->text().toInt());
        CameraInstance->WebcamInstance->set(cv::CAP_PROP_FRAME_HEIGHT, ui->leImageHeight->text().toInt());

        ui->leImageWidth->setText(QString::number((int)CameraInstance->WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH)));
        ui->leImageHeight->setText(QString::number((int)CameraInstance->WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT)));

        CameraTimer.start(ui->leCaptureInterval->text().toInt());
    }
    else
    {
//        if (imageName.isEmpty())
//        {
//            qDebug() << "Không chọn ảnh";
//            return;
//        }

        for (const QString &imageName : imageNames) {
            QImage qImage(imageName);
            if (!qImage.isNull()) {
                CameraInstance->CaptureImages.append(ImageTool::QImageToCvMat(qImage, true));
            }
        }

        CameraInstance->CaptureImage = CameraInstance->CaptureImages.at(0);
        CameraInstance->FrameID = 0;

//        QImage qImage(imageName);

//        if (qImage.isNull())
//        {
//            qDebug() << "Không thể đọc ảnh";
//            return;
//        }

//        CameraInstance->CaptureImage = ImageTool::QImageToCvMat(qImage, true);
        ui->pbCapture->clicked();
        ui->pbStartAcquisition->setChecked(true);
        ui->pbStartAcquisition->clicked(true);
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
    ParameterPanel->SetImage(ImageProcessingThread->GetNode("ColorFilterNode")->GetInputImage());
    ParameterPanel->show();
}

void RobotWindow::SelectObjectDetectingAlgorithm(int algorithm)
{
    ui->fBlobPanel->setHidden(true);
    ui->fExternalScriptPanel->setHidden(true);
    ui->fCirclePanel->setHidden(true);

    QString text = ui->cbDetectingAlgorithm->itemText(algorithm);
    disconnect(ImageProcessingThread->GetNode("CropImageNode"), SIGNAL(HadOutput(cv::Mat)), ConnectionManager, SLOT(sendImageToImageClients(cv::Mat)));

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    VariableManager::instance().updateVar(prefix + "DetectAlgorithm",text);

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
        connect(ImageProcessingThread->GetNode("CropImageNode"), SIGNAL(HadOutput(cv::Mat)), ConnectionManager, SLOT(sendImageToImageClients(cv::Mat)));
    }
}

void RobotWindow::ConfigChessboard()
{
    if (ui->pbCropTool->isChecked() == true)
        ui->pbCropTool->click();
    if (ui->pbWarpTool->isChecked() == true)
        ui->pbWarpTool->click();

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
        ui->pbWarpTool->setChecked(true);
        ui->pbWarpTool->click();
        ui->gvImageViewer->SelectQuadrangleTool();
    }
}

void RobotWindow::GetCalibPointsFromImage(QPointF p1, QPointF p2)
{
    float xx1 = ui->leRealityPoint1X->text().toFloat();
    float yy1 = ui->leRealityPoint1Y->text().toFloat();
    float xx2 = ui->leRealityPoint2X->text().toFloat();
    float yy2 = ui->leRealityPoint2Y->text().toFloat();
    float ox = ui->leCalibOffset_X->text().toFloat();
    float oy = ui->leCalibOffset_Y->text().toFloat();

    QPointF _p1(xx1, yy1);
    QPointF _p2(xx2, yy2);

    if (ui->cbCalibType->currentIndex() == 1)
    {
        QPointF offset(ox,oy);
        QTransform transform = PointTool::calculateTransform(QPointF(0, 0), offset, _p1, _p2);
        _p1 = transform.map(_p1);
        _p2 = transform.map(_p1);
    }

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";

    VariableManager::instance().updateVar(prefix + "Point1", p1);
    VariableManager::instance().updateVar(prefix + "Point2", p2);


    QPolygonF poly;

    poly.append(p1);
    poly.append(p2);
    poly.append(_p1);
    poly.append(_p2);

    emit GotCalibPoints(poly);
}

void RobotWindow::UpdateRealPositionOfCalibPoints()
{
    QPointF rpoint1(ui->leRealityPoint1X->text().toFloat(), ui->leRealityPoint1Y->text().toFloat());
    QPointF rpoint2(ui->leRealityPoint2X->text().toFloat(), ui->leRealityPoint2Y->text().toFloat());

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";

    VariableManager::instance().updateVar(prefix + "RealCalibPoint1", rpoint1);
    VariableManager::instance().updateVar(prefix + "RealCalibPoint2", rpoint2);

    if (ui->cbCalibType->currentIndex() == 1)
    {
        float ox = ui->leCalibOffset_X->text().toFloat();
        float oy = ui->leCalibOffset_Y->text().toFloat();

        QPointF offset(ox,oy);
        QTransform transform = PointTool::calculateTransform(QPointF(0, 0), offset, rpoint1, rpoint2);
        rpoint1 = transform.map(rpoint1);
        rpoint2 = transform.map(rpoint2);
    }

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
    obj.RangeWidth.Min.Image = width * ui->leMinWRec->text().toFloat();
    obj.RangeWidth.Max.Image = width * ui->leMaxWRec->text().toFloat();

    emit GotOjectFilterInfo(obj);
}

void RobotWindow::GetMappingPointFromImage(QPointF point)
{
    point.setY(0 - point.y());

    QMatrix matrix = ImageProcessingThread->GetNode("VisibleObjectsNode")->GetMatrix();
    QPointF realPoint = matrix.map(point);

    //Làm tròn realPoint đến 2 chữ số thập phân
    realPoint.setX(((float)((int)(realPoint.x() * 100))) / 100);
    realPoint.setY(((float)((int)(realPoint.y() * 100))) / 100);    

    UpdateVariable("#Test_Point.X", realPoint.x());
    UpdateVariable("#Test_Point.Y", realPoint.y());

    ui->gvImageViewer->SetMappingPointTitle(QString("X=%1,Y=%2").arg(realPoint.x()).arg(realPoint.y()));

    QString text = QString("%1, %2, %3").arg(QString::number(realPoint.x())).arg(QString::number(realPoint.y())).arg(QString::number(0));
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);
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
    ui->pbFindChessboardTool->setChecked(false);
    ui->pbGetSizeTool->setChecked(false);
    ui->pbMappingPointTool->setChecked(false);
}

//void RobotWindow::UpdateObjectsToImageViewer(QList<Object> objects)
//{
//    QList<QPolygonF> polys;
//    QMap<QString, QPointF> texts;

//    try
//    {
//        int counter = 0;

//        foreach(Object obj, objects)
//        {
//            counter++;
//            if (counter > 100)
//                return;
//            polys.append(obj.ToPolygon());
//            texts.insert(QString::number(counter - 1), QPointF(obj.X.Image, obj.Y.Image));
//        }
//    }
//    catch(const std::exception& e)
//    {
//        std::cerr << e.what() << '\n';
//    }

//    ui->gvImageViewer->DrawPolygons(polys);
//    ui->gvImageViewer->DrawTexts(texts);
//}

//void RobotWindow::UpdateObjectsToImageViewer(QList<QSharedPointer<Object>> objects)
//{
//    QList<QPolygonF> polys;
//    QMap<QString, QPointF> texts;

//    try
//    {
//        int counter = 0;

//        foreach(const QSharedPointer<Object>& obj, objects) {
//            counter++;
//            if (counter > 100)
//                return;
//            polys.append(obj->ToPolygon());
//            texts.insert(QString::number(counter - 1), QPointF(obj->X.Image, obj->Y.Image));
//        }
//    }
//    catch(const std::exception& e)
//    {
//        std::cerr << e.what() << '\n';
//    }

//    ui->gvImageViewer->DrawPolygons(polys);
//    ui->gvImageViewer->DrawTexts(texts);
//}

//void RobotWindow::UpdateObjectsToImageViewer(QList<QPolygonF> polys)
//{
//    QList<QPolygonF> pls;
//    QMap<QString, QPointF> texts;

//    try
//    {
//        int counter = 0;

//        foreach(QPolygonF poly, polys) {
//            counter++;
//            if (counter > 100)
//                return;
//            pls.append(poly);
//            // Tìm tâm của poly
//            QPointF center = PointTool::GetCenterOfPolygon(poly);
//            texts.insert(QString::number(counter - 1), QPointF(center.x(), center.y()));
//        }
//    }
//    catch(const std::exception& e)
//    {
//        std::cerr << e.what() << '\n';
//    }

//    ui->gvImageViewer->DrawPolygons(pls);
//    ui->gvImageViewer->DrawTexts(texts);
//}

void RobotWindow::EditImage(bool isWarp, bool isCropTool)
{
    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";

    VariableManager::instance().updateVar(prefix + "WarpEnable", isWarp);
    VariableManager::instance().updateVar(prefix + "CropEnable", isCropTool);

    TaskNode* cropImageNode = ImageProcessingThread->GetNode("CropImageNode");
    TaskNode* warpImageNode = ImageProcessingThread->GetNode("WarpImageNode");

    if (isWarp == false && isCropTool == true)
    {
        warpImageNode->IsPass = true;
        cropImageNode->IsPass = false;

        ui->gvImageViewer->SelectNoTool();

        ui->gvImageViewer->TurnOnObjects(true);
    }
    else if (isWarp == true && isCropTool == true)
    {
        warpImageNode->IsPass = false;
        cropImageNode->IsPass = false;

        ui->gvImageViewer->SelectNoTool();

        ui->gvImageViewer->TurnOnObjects(true);
    }
    else if (isWarp == false && isCropTool == false)
    {
        warpImageNode->IsPass = true;
        cropImageNode->IsPass = true;

        UnselectToolButtons();
        ui->gvImageViewer->SelectAreaTool();

        ui->gvImageViewer->TurnOnObjects(false);
    }
    else if (isWarp == true && isCropTool == false)
    {
        warpImageNode->IsPass = false;
        cropImageNode->IsPass = true;

        UnselectToolButtons();
        ui->gvImageViewer->SelectAreaTool();

        ui->gvImageViewer->TurnOnObjects(false);
    }

    ui->pbCapture->clicked();
}

void RobotWindow::SendImageToExternalScript(cv::Mat input)
{
    if (ui->cbDetectingAlgorithm->currentText() != "External Script")
        return;

    for (QTcpSocket* client : ConnectionManager->clients) {
        if (client->objectName() == "ImageClient") {

            if (client == NULL || input.empty())
                return;

            int paras[3];
            paras[0] = input.cols;
            paras[1] = input.rows;
            paras[2] = input.channels();

            int len = 3 * sizeof(int);

            client->write((char*)paras, len);

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
                    int SendSize = client->write(buf, sed);

                    if (SendSize == -1)
                        return;
                    sedNum += SendSize;
                }
            }
        }
    }

}

void RobotWindow::ConnectConveyor()
{
    if (ui->pbConveyorConnect->text() != "Connect")
    {
        emit ChangeDeviceState(DeviceManager::CONVEYOR, false, "");
        return;
    }

    QStringList items;

    Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial(portInfo);
        if(serial.open(QIODevice::ReadWrite))
        {
            items << portInfo.portName() + " - " + portInfo.description();
            serial.close();
        }
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
    if (ui->cbConveyorType->currentText().contains("Desktop Conveyor"))
    {
        if (mode > 0)
            mode = 1;
        emit Send(DeviceManager::CONVEYOR, QString("M310 ") + QString::number(mode));
    }
    else
        emit Send(DeviceManager::CONVEYOR, QString("M310 ") + QString::number(3 - mode));
}

void RobotWindow::SetConveyorMovingMode(int mode)
{
    if (ui->cbConveyorType->currentText() == "Desktop Conveyor")
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
    if (ui->cbLinkToConveyorX->isChecked() == true && ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        ui->leEncoderVelocity->setText(ui->leConveyorXSpeed->text());
        ui->pbSetEncoderVelocity->click();
    }

    if (ui->cbConveyorType->currentText() == "Desktop Conveyor")
    {
        if (ui->cbConveyorMode->currentIndex() == 1)
        {
            emit Send(DeviceManager::CONVEYOR, QString("M311 ") + ui->leConveyorXSpeed->text());
        }
        else if (ui->cbConveyorMode->currentIndex() == 2)
        {
            emit Send(DeviceManager::CONVEYOR, QString("M313 ") + ui->leConveyorXSpeed->text());
        }
    }
    else if (ui->cbConveyorType->currentText() == "X Conveyor")
    {
        if (ui->cbConveyorMode->currentIndex() == 1)
        {
            emit Send(DeviceManager::CONVEYOR, QString("M311 ") + ui->leConveyorXSpeed->text());
        }
        else if (ui->cbConveyorMode->currentIndex() == 2)
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
    if (ui->cbLinkToConveyorX->isChecked() == true && ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        float moving = ui->leConveyorXPosition->text().toFloat();
        float currentPos = ui->leEncoderCurrentPosition->text().toFloat() + moving;
        ui->leEncoderCurrentPosition->setText(QString::number(currentPos));

        TrackingManagerInstance->Trackings.at(0)->VirEncoder.setPosition(currentPos);
    }

    if (ui->cbConveyorType->currentText() == "Desktop Conveyor")
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

void RobotWindow::SetConveyorAbsolutePosition()
{
    if (ui->cbConveyorType->currentText() == "X Conveyor")
    {
        emit Send(DeviceManager::CONVEYOR, QString("M312 ") + ui->leConveyorXAbsolutePosition->text());
    }
}

void RobotWindow::ProcessShortcutKey()
{

}

void RobotWindow::ChangeEncoderType(int index)
{
    ui->pbConnectEncoder->setHidden(true);
    ui->pbSetEncoderVelocity->setHidden(true);
    ui->cbLinkToConveyorX->setHidden(true);
    ui->cbConveyorLinkToEncoder->setHidden(true);
    int selectedEncoderID = ui->cbSelectedEncoder->currentIndex();
    if (ui->cbEncoderType->currentText() == "X Encoder")
    {
        ui->cbLinkToConveyorX->setHidden(false);
        ui->cbConveyorLinkToEncoder->setHidden(false);
        ui->pbConnectEncoder->setHidden(false);
        ui->pbSetEncoderVelocity->setHidden(true);

        TrackingManagerInstance->Trackings.at(selectedEncoderID)->EncoderType = "X Encoder";
        TrackingManagerInstance->Trackings.at(selectedEncoderID)->VirEncoder.stop();
    }
    else if (ui->cbEncoderType->currentText() == "Sub Encoder")
    {
        ui->pbConnectEncoder->setHidden(false);
        ui->pbSetEncoderVelocity->setHidden(true);
        TrackingManagerInstance->Trackings.at(selectedEncoderID)->EncoderType = "Sub Encoder";
        TrackingManagerInstance->Trackings.at(selectedEncoderID)->VirEncoder.stop();
    }
    else if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        TrackingManagerInstance->Trackings.at(selectedEncoderID)->EncoderType = "Virtual Encoder";
        TrackingManagerInstance->Trackings.at(selectedEncoderID)->VirEncoder.start();
        ui->cbLinkToConveyorX->setHidden(false);
        ui->cbConveyorLinkToEncoder->setHidden(false);
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

void RobotWindow::ChangeSelectedTrackingEncoder(int id)
{
    TrackingManagerInstance->Trackings.at(id)->EncoderName = ui->cbTrackingEncoderSource->currentText();
}

void RobotWindow::CalculateMappingMatrixTool()
{
    QPointF sp1(ui->leSourcePoint1X->text().toFloat(), ui->leSourcePoint1Y->text().toFloat());
    QPointF sp2(ui->leSourcePoint2X->text().toFloat(), ui->leSourcePoint2Y->text().toFloat());
    QPointF tp1(ui->leDestinationPoint1X->text().toFloat(), ui->leDestinationPoint1Y->text().toFloat());
    QPointF tp2(ui->leDestinationPoint2X->text().toFloat(), ui->leDestinationPoint2Y->text().toFloat());

//    CalculatingTransform = PointTool::calculateTransform(sp1, sp2, tp1, tp2);
    CalculatingTransform2 = PointTool::calculateTransform2(sp1, sp2, tp1, tp2);
    CalculatingTransform.setMatrix(CalculatingTransform2.m11(), CalculatingTransform2.m12(), 0,
                                   CalculatingTransform2.m21(), CalculatingTransform2.m22(), 0,
                                   CalculatingTransform2.dx(), CalculatingTransform2.dy(), 1);

    QString transformAsString = QString("Matrix:\n"
                                        "| %1, %2, %3 |\n"
                                        "| %4, %5, %6 |\n"
                                        "| %7, %8, %9 |")
                                    .arg(CalculatingTransform.m11()).arg(CalculatingTransform.m12()).arg(CalculatingTransform.m13())
                                    .arg(CalculatingTransform.m21()).arg(CalculatingTransform.m22()).arg(CalculatingTransform.m23())
                                    .arg(CalculatingTransform.m31()).arg(CalculatingTransform.m32()).arg(CalculatingTransform.m33());

    ui->lbMatrixDisplay->setText(transformAsString);

}

void RobotWindow::CalculatePointMatrixTool()
{
    QPointF sp1(ui->leSPoint1X->text().toFloat(), ui->leSPoint1Y->text().toFloat());
    QPointF sp2(ui->leSPoint2X->text().toFloat(), ui->leSPoint2Y->text().toFloat());
    QPointF sp3(ui->leSPoint3X->text().toFloat(), ui->leSPoint3Y->text().toFloat());
    QPointF sp4(ui->leSPoint4X->text().toFloat(), ui->leSPoint4Y->text().toFloat());

    QPointF dp1(ui->leDPoint1X->text().toFloat(), ui->leDPoint1Y->text().toFloat());
    QPointF dp2(ui->leDPoint2X->text().toFloat(), ui->leDPoint2Y->text().toFloat());
    QPointF dp3(ui->leDPoint3X->text().toFloat(), ui->leDPoint3Y->text().toFloat());
    QPointF dp4(ui->leDPoint4X->text().toFloat(), ui->leDPoint4Y->text().toFloat());

    QPolygonF source;
    source << sp1 << sp2 << sp3 << sp4;

    QPolygonF dest;
    dest << dp1 << dp2 << dp3 << dp4;

    PointMatrix = PointTool::calculateMatrix(source, dest);

    qreal m11 = PointMatrix.m11();  // x scaling
    qreal m12 = PointMatrix.m12();  // y rotation
    qreal m21 = PointMatrix.m21();  // x rotation
    qreal m22 = PointMatrix.m22();  // y scaling
    qreal dx = PointMatrix.dx();    // x translation
    qreal dy = PointMatrix.dy();    // y translation

    QString matrixString = QString("m11: %1, m12: %2\nm21: %3, m22: %4\ndx: %5, dy: %6")
                             .arg(m11).arg(m12).arg(m21).arg(m22).arg(dx).arg(dy);

    ui->lbPointMatrixDisplay->setText(matrixString);
}

void RobotWindow::CalculateTestPoint()
{
    QTransform matrix = VariableManager::instance().getVar(ui->leTestMatrixName->text()).value<QTransform>();

    QPointF testPoint(ui->leTestPointX->text().toFloat(), ui->leTestPointY->text().toFloat());
    QPointF target = matrix.map(testPoint);
    ui->leTargetTestPointX->setText(QString::number(target.x()));
    ui->leTargetTestPointY->setText(QString::number(target.y()));
}

void RobotWindow::CalculateVector()
{
    QVector3D P1(ui->lePointAtT1X->text().toFloat(), ui->lePointAtT1Y->text().toFloat(), ui->lePointAtT1Z->text().toFloat());
    QVector3D P2(ui->lePointAtT2X->text().toFloat(), ui->lePointAtT2Y->text().toFloat(), ui->lePointAtT2Z->text().toFloat());
    float vectorValue = ui->leVectorValue->text().toFloat();

    QVector3D deltaPosition = P2 - P1;

    // Tính độ lớn của deltaPosition
    double deltaMagnitude = deltaPosition.length();

    // Tính vector đơn vị
    QVector3D unitVector = deltaPosition / deltaMagnitude;

    // Tính vector vận tốc của băng tải
    CalVector = unitVector * vectorValue;

    ui->leVectorX->setText(QString::number(CalVector.x()));
    ui->leVectorY->setText(QString::number(CalVector.y()));
    ui->leVectorZ->setText(QString::number(CalVector.z()));
}

void RobotWindow::UpdateTestPoint(QVector3D testPoint)
{
    if (ui->tbAutoMove->isChecked() == false)
        return;

    QVector3D currentTestPoint(ui->leTestTrackingPointX->text().toFloat(), ui->leTestTrackingPointY->text().toFloat(), ui->leTestTrackingPointZ->text().toFloat());
    currentTestPoint += testPoint;

    ui->leTestTrackingPointX->setText(QString::number(currentTestPoint.x()));
    ui->leTestTrackingPointY->setText(QString::number(currentTestPoint.y()));
    ui->leTestTrackingPointZ->setText(QString::number(currentTestPoint.z()));
}

void RobotWindow::ProcessProximitySensorValue(int value)
{

}

void RobotWindow::ConnectSliding()
{
    if (ui->pbSlidingConnect->text() != "Connect")
    {
        emit ChangeDeviceState(DeviceManager::SLIDER, false, "");
        return;
    }

    QStringList items;

    Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial(portInfo);
        if(serial.open(QIODevice::ReadWrite))
        {
            items << portInfo.portName() + " - " + portInfo.description();
            serial.close();
        }
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
            emit ChangeDeviceState(DeviceManager::SLIDER, (ui->pbSlidingConnect->text() == "Connect")?true:false, comName);
        }
    }
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
    if (ui->pbExternalControllerConnect->text() != "Connect")
    {
        emit ChangeDeviceState(DeviceManager::DEVICE, false, "");
        return;
    }

    QStringList items;

    Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial(portInfo);
        if(serial.open(QIODevice::ReadWrite))
        {
            items << portInfo.portName() + " - " + portInfo.description();
            serial.close();
        }
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
                QSerialPort serial(portInfo);
                if(serial.open(QIODevice::ReadWrite))
                {
                    items << portInfo.portName() + " - " + portInfo.description();
                    serial.close();
                }
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

    UpdateTermite(msg);
}

void RobotWindow::UpdateTermite(QString mess)
{
    if (ui->teDebug->document()->blockCount() > 200)
        ui->teDebug->setText("");

    ui->teDebug->moveCursor (QTextCursor::End);
    ui->teDebug->insertPlainText(mess);
    ui->teDebug->moveCursor(QTextCursor::End);
}

void RobotWindow::UpdateCameraConnectedState(bool isOpen)
{
    if (isOpen == true)
    {
        ui->pbLoadCamera->setText("Stop Camera");

        ui->leImageWidth->setText(QString::number(CameraInstance->Width));
        ui->leImageHeight->setText(QString::number(CameraInstance->Height));

        ui->pbStartAcquisition->setChecked(true);
        ui->pbStartAcquisition->clicked(true);

    }
    CloseLoadingPopup();
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

QString RobotWindow::checkAndCreateDir(const QString &path)
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QDir imagesDir(appDirPath + "/Images");

    if (imagesDir.exists()) {
    return imagesDir.absolutePath();  // Return absolute path if it exists
    }

    // The directory doesn't exist, create it.
    bool success = imagesDir.mkdir(".");
    if (!success) {
    return QString(); // Return an empty string if creation fails
    }

    return imagesDir.absolutePath();  // Return absolute path after creation

}

bool RobotWindow::saveImageWithUniqueName(const cv::Mat &image, const QString &dirPath) {
  // Check if the directory exists, create if not.
  if (!QDir(dirPath).exists()) {
    QDir().mkdir(dirPath);
  }

  // Generate a unique filename with increasing number.
  int count = 1;
  QString fileName;
  do {
    fileName = QString("%1/%2.png").arg(dirPath).arg(count);
    count++;
  } while (QFile::exists(fileName));

  // Save the image.
  bool success = cv::imwrite(fileName.toStdString(), image);

  return success;
}

void RobotWindow::loadImages(const QString &dirPath, QListWidget *lwImageList)
{
    if (!QDir(dirPath).exists()) {
    return;
    }

    lwImageList->clear();

      QDir dir(dirPath);
      foreach (const QFileInfo& fileInfo, dir.entryInfoList()) {
        if (!fileInfo.isDir()) {
          QListWidgetItem* item = new QListWidgetItem(lwImageList);

          QString fileName = fileInfo.fileName();

          item->setText(fileName);

          item->setData(Qt::UserRole, fileInfo.absoluteFilePath());

           QPixmap pixmap(fileInfo.absoluteFilePath());
           item->setIcon(pixmap.scaled(QSize(64, 64), Qt::KeepAspectRatio));
        }
      }
}

void RobotWindow::onImageItemClicked(QListWidgetItem *item)
{
    QString imagePath = item->data(Qt::UserRole).toString();
}

void RobotWindow::pastePointValues(QLineEdit *leX, QLineEdit *leY, QLineEdit *leZ)
{
    QClipboard *clipboard = QApplication::clipboard();
    QString data = clipboard->text();
    // data = "%1, %2, %3"
    QStringList list = data.split(", ");

    if (list.count() < 2)
        return;

    if (list.count() == 2 || leZ == NULL )
    {
        QString x = list[0];
        QString y = list[1];

        leX->setText(QString::number(x.toFloat()));
        leY->setText(QString::number(y.toFloat()));
    }
    else if (leZ != NULL)
    {
        QString x = list[0];
        QString y = list[1];
        QString z = list[2];

        leX->setText(QString::number(x.toFloat()));
        leY->setText(QString::number(y.toFloat()));
        leZ->setText(QString::number(z.toFloat()));
    }
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

bool RobotWindow::isItemExit(QListWidget *lw, QString item)
{
    bool itemExists = false;
    for (int i = 0; i < lw->count(); ++i) {
        if (lw->item(i)->text() == item) {
            itemExists = true;
            break;
        }
    }

    return itemExists;
}

int RobotWindow::getIDfromName(QString fullName)
{
    QString id = fullName.split(QRegExp("[^\\d]")).last();
    return id.toInt();
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

void RobotWindow::CheckSettingsSpeed()
{
    QElapsedTimer elapse;
    elapse.start();

    QList<Object> objects;

    for (int counter = 0; counter < 1000; counter++)
    {
//        VariableManager::instance().updateVar(QString("ObjectTests.%1.X").arg(counter), 12);
//        VariableManager::instance().updateVar(QString("ObjectTests.%1.Y").arg(counter), 143);
//        VariableManager::instance().updateVar(QString("ObjectTests.%1.W").arg(counter), 21);
//        VariableManager::instance().updateVar(QString("ObjectTests.%1.L").arg(counter), 33);
//        VariableManager::instance().updateVar(QString("ObjectTests.%1.A").arg(counter), 100);

        Object object;
        object.X.Real = 34;
        object.Y.Real =33;
        object.Height.Real = 34;
        object.Width.Real = 34;
        object.Angle.Real = 21;

        objects.append(object);
    }

    qDebug() << "var" << elapse.elapsed();
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

    int width = CameraInstance->CaptureImage.cols;
    int height = CameraInstance->CaptureImage.rows;
    float ratio = ui->gvImageViewer->GetRatio() * 100;
    ui->lbMatSize->setText(QString("Re: %1x%2").arg(width).arg(height));
    ui->lbDisplayRatio->setText(QString("Ratio: %1%").arg(ratio));

    if (ui->cbAutoUpdateObjectsDisplay->currentIndex() == 1)
    {
        UpdateObjectsToView();
    }
}

void RobotWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event); // Gọi hàm cơ bản

    int elapsed = performanceTimer.elapsed(); // Lấy thời gian đã trôi qua từ lần cuối
    qDebug() << "Thời gian giữa hai lần gọi paintEvent:" << elapsed << "milliseconds";
    performanceTimer.restart(); // Khởi động lại timer cho lần gọi kế tiếp
}

void RobotWindow::SaveDetectingUI()
{
    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    VariableManager::instance().updateVar(prefix + "ResizeWidth", ui->leImageWidth->text());
    VariableManager::instance().updateVar(prefix + "ResizeHeight", ui->leImageHeight->text());
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
//            SoftwareLog(msg);
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

