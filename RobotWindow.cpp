#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include "ChessboardConfigDialog.h"
#include "SoftwareManager.h"
#include "MainWindow.h"
#include "ModernDialog.h"
#include "CameraSelectionDialog.h"
#include "UnityTool.h"  // ✅ For SoftwareLog function
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <cmath>      // ✅ For Z-plane calculations
#include <QInputDialog>  // ✅ For test input dialog
#include <QtMath>      // ✅ For qAbs function

RobotWindow::RobotWindow(QWidget *parent, QString projectName) :
    QMainWindow(parent),
    ui(new Ui::RobotWindow),
    ProjectName(projectName),
    m_variableManager(&VariableManager::instance()),
    m_batchUpdateTimer(new QTimer(this))
{
    ui->setupUi(this);

    SoftwareLog("Load project: " + ProjectName);
    
    // Initialize batch update timer
    m_batchUpdateTimer->setSingleShot(true);
    m_batchUpdateTimer->setInterval(50); // 50ms batching window
    connect(m_batchUpdateTimer, &QTimer::timeout, this, &RobotWindow::processBatchUpdates);
    
    // Set prefix once for this window
    m_variableManager->Prefix = ProjectName;

    InitVariables();
    InitOtherThreadObjects();
    InitEvents();

    LoadSettings();
    InitDefaultValue();
    
    // Initialize Cloud Point Mapping UI after all other objects are ready
    if (m_pointToolController) {
        m_pointToolController->initializeUI(ui->tPointTool);
    }
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

    ImageProcessingInstance->thread()->quit();
    ImageProcessingInstance->thread()->wait();

    CameraThread->quit();
    CameraThread->wait();
    delete CameraThread;

    for (int i = 0; i < GcodeScripts.count(); i++)
    {
        GcodeScripts.at(i)->thread()->quit();
        GcodeScripts.at(i)->thread()->wait();
    }

    // Clean up Python process
    if (process != nullptr && process->state() == QProcess::Running) {
        qDebug() << "Terminating Python process on application close...";
        process->terminate();
        
        // Đợi process terminate, nếu không thành công thì kill
        if (!process->waitForFinished(2000)) { // Đợi 2 giây
            process->kill();
            process->waitForFinished(1000); // Đợi thêm 1 giây cho kill
        }
        
        qDebug() << "Python process terminated";
    }

    // Clean up Point Tool Controller
    delete m_pointToolController;

    // ✅ Fix: Cleanup plugins to prevent memory leak
    if (pluginList) {
        SoftwareLog(QString("Plugin System: Cleaning up %1 plugins").arg(pluginList->count()));
        for (int i = 0; i < pluginList->count(); i++) {
            DeltaXPlugin* plugin = pluginList->at(i);
            if (plugin) {
                qDebug() << "Cleaning up plugin:" << plugin->GetName();
                SoftwareLog(QString("Cleaned up plugin: %1").arg(plugin->GetName()));
                delete plugin;
            }
        }
        delete pluginList;
        pluginList = nullptr;
    }
    
    // Reset plugin pointers
    industrialCameraPlugin = nullptr;

    delete ui;
}

void RobotWindow::InitVariables()
{
    //--------- Register ----------
    qRegisterMetaType< QList<QStringList>>("QList<QStringList>");
    qRegisterMetaType< QVector<Object> >("QVector<ObjectInfo>");
    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< cv::Size >("cv::Size");
    qRegisterMetaType< Object >("Object");
    qRegisterMetaType< QVector<Object>* >("QVector<Object>*");
    qRegisterMetaType< QVector<Object> >("QVector<Object>&");
    qRegisterMetaType< QVector<Object>* >("QVector<Object>");
    qRegisterMetaType< QVector<QSharedPointer<Object>> >("QVector<QSharedPointer<Object>>");
    qRegisterMetaType< QList<QPolygonF> >("QList<QPolygonF>");
    qRegisterMetaType< QVector<Object> >("QVector<ObjectInfo>");
    qRegisterMetaType< QList<int> >("QList<int>");

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
    
    // Initialize context menu for object table
    initObjectTableContextMenu();

    performanceTimer.start();


    //---- Init pointer --------
    initInputValueLabels();

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        //------Joystick-----
        joystick = QJoysticks::getInstance();
        joystick->setVirtualJoystickRange(ui->leJoystickRange->text().toDouble());
        joystick->setVirtualJoystickAxisSensibility(ui->leJoystickSensibility->text().toDouble());
//        qDebug() << "joystick device: " << joystick->deviceNames();
        ui->cbJoystickDevice->addItems(joystick->deviceNames());
    #endif
#endif

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
    DeltaDrawingExporter->SetDrawingPointInPlane(ui->leADrawingPoint, ui->leBDrawingPoint, ui->leCDrawingPoint);

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

    // Initialize Point Tool Controller
    m_pointToolController = new PointToolController(this);
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

    connect(DeviceManagerInstance, SIGNAL(GotDeviceInfo(QString)), this, SLOT(GetDeviceInfo(QString)));
    connect(this, SIGNAL(ChangeDeviceState(QString,bool,QString)), DeviceManagerInstance, SLOT(SetDeviceState(QString,bool,QString)));
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
    CameraThread = new QThread(this);
    CameraInstance->moveToThread(CameraThread);
    connect(CameraThread, &QThread::finished, CameraInstance, &QObject::deleteLater);
    connect(CameraInstance, &Camera::StopCameraRequest, this, &RobotWindow::StopCapture);

    CameraThread->start();

    connect(CameraInstance, &Camera::connectedResult, this, &RobotWindow::UpdateCameraConnectedState);

    connect(&CameraTimer, SIGNAL(timeout()), CameraInstance, SLOT(GeneralCapture()));
//    SelectImageProviderOption(0);

//    connect(ui->cbTrackingThreadForCamera, SIGNAL(currentIndexChanged(int)), CameraInstance, SLOT(setTracking(int)));

    //------- New image processing thread --------
    InitObjectDetectingModule();

        //-------- Robot ---------
    connect(ui->pbConnectRobot, SIGNAL(clicked(bool)), this, SLOT(ConnectRobot()));
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
    connect(ui->pbStopConveyor, SIGNAL(clicked(bool)), this, SLOT(StopConveyor()));
    connect(ui->cbConveyorType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeConveyorType(int)));
    ChangeConveyorType(0);
    connect(ui->pbForwardConveyor, SIGNAL(pressed()), this, SLOT(ForwardConveyor()));
    connect(ui->pbForwardConveyor, SIGNAL(released()), this, SLOT(StopConveyor()));
    connect(ui->pbBackwardConveyor, SIGNAL(pressed()), this, SLOT(BackwardConveyor()));
    connect(ui->pbBackwardConveyor, SIGNAL(released()), this, SLOT(StopConveyor()));

    connect(ui->leSubConveyor1Speed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));
    connect(ui->leSubConveyor2Speed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));
    connect(ui->leSubConveyor3Speed, SIGNAL(returnPressed()), this, SLOT(SetConveyorSpeed()));

    connect(ui->leSubConveyor1Position, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));
    connect(ui->leSubConveyor2Position, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));
    connect(ui->leSubConveyor3Position, SIGNAL(returnPressed()), this, SLOT(SetConveyorPosition()));

    connect(ui->cbSubConveyor1Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));
    connect(ui->cbSubConveyor2Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));
    connect(ui->cbSubConveyor3Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(SetConveyorMovingMode(int)));

    connect(ui->pbStartCustomConveyor1, SIGNAL(clicked(bool)), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStartCustomConveyor1Command, SIGNAL(returnPressed()), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStartCustomConveyor2, SIGNAL(clicked(bool)), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStartCustomConveyor2Command, SIGNAL(returnPressed()), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStartCustomConveyor3, SIGNAL(clicked(bool)), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStartCustomConveyor3Command, SIGNAL(returnPressed()), this, SLOT(TriggedCustomConveyor()));

    connect(ui->pbStopCustomConveyor1, SIGNAL(clicked(bool)), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStopCustomConveyor1Command, SIGNAL(returnPressed()), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStopCustomConveyor2, SIGNAL(clicked(bool)), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStopCustomConveyor2Command, SIGNAL(returnPressed()), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStopCustomConveyor3, SIGNAL(clicked(bool)), this, SLOT(TriggedCustomConveyor()));
    connect(ui->pbStopCustomConveyor3Command, SIGNAL(returnPressed()), this, SLOT(TriggedCustomConveyor()));



        //-------- Encoder --------
    connect(ui->pbConnectEncoder, SIGNAL(clicked(bool)), this, SLOT(ConnectEncoder()));

    connect(ui->pbReadEncoder, SIGNAL(clicked(bool)), this, SLOT(ReadEncoder()));
    connect(ui->pbSetEncoderInterval, SIGNAL(clicked(bool)), this, SLOT(SetEncoderAutoRead()));
    connect(ui->pbResetEncoder, SIGNAL(clicked(bool)), this, SLOT(ResetEncoderPosition()));
    connect(ui->pbSetEncoderVelocity, SIGNAL(clicked(bool)), this, SLOT(SetEncoderVelocity()));

    connect(ui->cbEncoderType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeEncoderType(int)));
    connect(ui->cbLinkToConveyorX, SIGNAL(stateChanged(int)), this, SLOT(ChangeConveyorLinkToEncoder(int)));

    connect(ui->pbStartScheduledEncoder, SIGNAL(clicked(bool)), this, SLOT(StartScheduledEncoder()));

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
    // localhost:8844
    QStringList ipAndPort = ui->leIP->text().split(":");
    QString port = ipAndPort.at(1);

    ConnectionManager = new SocketConnectionManager(localIP, port.toInt());
    ConnectionManager->ProjectName = ProjectName;
    QString appDirPath = QCoreApplication::applicationDirPath();
    ConnectionManager->indexPath = appDirPath + "/Jogging.html";

    QThread* thread = new QThread(this);

    ConnectionManager->moveToThread(thread);

    connect(ConnectionManager->thread(), &QThread::finished, ConnectionManager, &QObject::deleteLater);

    thread->start();

    connect(ConnectionManager, &SocketConnectionManager::eventReceived, this, &RobotWindow::ActiveWidgetByName);

    if (ConnectionManager->IsServerOpen())
    {
        ui->leIP->setText(ConnectionManager->Server->serverAddress().toString() + ":" + QString::number(ConnectionManager->Server->serverPort()));
    }

    connect(ui->tbServerConfig, &QPushButton::clicked, [=](bool checked)
    {
        ui->leIP->setFrame(true);
        ui->leIP->setReadOnly(false);
    });

    connect(ui->leIP, &QLineEdit::returnPressed, [=]()
    {
        ui->leIP->setFrame(false);
        ui->leIP->setReadOnly(true);
    });

    // Connect Web Control button
    connect(ui->pbOpenWebControl, &QPushButton::clicked, [=]()
    {
        if (ConnectionManager && ConnectionManager->WebServer->isListening())
        {
            QString webUrl = QString("http://%1:5000").arg(ConnectionManager->hostAddress);
            QDesktopServices::openUrl(QUrl(webUrl));
            SoftwareLog("Opening web control at: " + webUrl);
        }
        else
        {
            QMessageBox::warning(this, "Web Control", "Web server is not running. Please start the server first.");
        }
    });
}

void RobotWindow::InitObjectDetectingModule()
{
    // ---------- Image Processing Thread ---------

    ImageProcessingInstance = new ImageProcessing();
    ImageProcessingInstance->ProjectName = ProjectName;

    // --------- Init Task Node --------

    ImageProcessingInstance->CreateTaskNode("GetImageNode", TaskNode::GET_IMAGE_NODE);
    ImageProcessingInstance->CreateTaskNode("ResizeImageNode", TaskNode::RESIZE_IMAGE_NODE, "GetImageNode");
    ImageProcessingInstance->CreateTaskNode("FindChessboardNode", TaskNode::FIND_CHESSBOARD_NODE);
    ImageProcessingInstance->CreateTaskNode("GetPerspectiveNode", TaskNode::GET_PERSPECTIVE_NODE, "FindChessboardNode");
    ImageProcessingInstance->CreateTaskNode("WarpImageNode", TaskNode::WARP_IMAGE_NODE, "ResizeImageNode|GetPerspectiveNode");
    ImageProcessingInstance->CreateTaskNode("CropImageNode", TaskNode::CROP_IMAGE_NODE, "WarpImageNode");

    ImageProcessingInstance->CreateTaskNode("MappingMatrixNode", TaskNode::MAPPING_MATRIX_NODE);
    ImageProcessingInstance->CreateTaskNode("ColorFilterNode", TaskNode::COLOR_FILTER_NODE, "CropImageNode");
    ImageProcessingInstance->CreateTaskNode("GetObjectsNode", TaskNode::GET_OBJECTS_NODE, "ColorFilterNode");
    ImageProcessingInstance->CreateTaskNode("FindCirclesNode", TaskNode::FIND_CIRCLES_NODE, "ColorFilterNode");
    ImageProcessingInstance->CreateTaskNode("VisibleObjectsNode", TaskNode::VISIBLE_OBJECTS_NODE, "GetObjectsNode|FindCirclesNode|MappingMatrixNode");

    ImageProcessingInstance->CreateTaskNode("DisplayImageNode", TaskNode::DISPLAY_IMAGE_NODE, "CropImageNode");

    ImageProcessingInstance->GetNode("WarpImageNode")->IsPass = true;
    ImageProcessingInstance->GetNode("CropImageNode")->IsPass = true;

    connect(CameraInstance, SIGNAL(GotImage(cv::Mat)), ImageProcessingInstance->GetNode("GetImageNode"), SLOT(Input(cv::Mat)));
//    connect(CameraInstance, SIGNAL(GotImage(cv::Mat)), ImageProcessingInstance, SLOT(GotImage(cv::Mat)));
//    connect(this, SIGNAL(GotResizePara(cv::Size)), ImageProcessingInstance, SLOT(GotResizeValue(cv::Size)));
//    connect(ImageProcessingInstance->GetNode("GetPerspectiveNode"), SIGNAL(HadOutput(cv::Mat)), ImageProcessingInstance, SLOT(GotPerspectiveMatrix(cv::Mat)));



    // ---------- Blob Filter Window---------
    ParameterPanel = new FilterWindow(this, ProjectName);

    // ---------- Main UI -------

    connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), this, SLOT(LoadWebcam()));
    connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), this, SLOT(LoadImages()));
    connect(ui->cbDetectingAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectObjectDetectingAlgorithm(int)));

    connect(ui->cbSendingImageMethod, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index){
        ConnectionManager->imageSendingMethod = index;
    });

    ui->cbDetectingAlgorithm->setCurrentIndex(0);
    SelectObjectDetectingAlgorithm(0);

    ui->gvImageViewer->ProjectName = ProjectName;

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

    connect(ui->pbClearDetectObjects, &QPushButton::clicked, [=](bool checked)
    {
        int id = ui->cbTrackingThreadForCamera->currentIndex();
        QMetaObject::invokeMethod(TrackingManagerInstance->Trackings[id], "ClearTrackedObjects", Qt::QueuedConnection);
        VariableManager::instance().removeVar(ui->leDetectingObjectListName->text());

        QTimer::singleShot(300, [this](){
            ui->pbCapture->clicked();
        });
    });

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
        ui->fCapturingImages->setVisible(true);
        ui->lwImageList->setVisible(true);

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
        ui->fCapturingImages->setVisible(true);
        ui->lwImageList->setVisible(true);

        QString absolutePath = checkAndCreateDir(ui->leImageFolder->text());
        loadImages(absolutePath, ui->lwImageList);
    });

    connect(ui->lwImageList, &QListWidget::itemClicked, this, &RobotWindow::onImageItemClicked);

    connect(this, SIGNAL(GotResizePara(cv::Size)), ImageProcessingInstance->GetNode("ResizeImageNode"), SLOT(Input(cv::Size)));
    connect(ImageProcessingInstance->GetNode("FindChessboardNode"), SIGNAL(HadOutput(QPolygonF)), ui->gvImageViewer, SLOT(SetQuadrangle(QPolygonF)));
    connect(this, SIGNAL(GotChessboardSize(cv::Size)), ImageProcessingInstance->GetNode("FindChessboardNode"), SLOT(Input(cv::Size)));
    connect(this, SIGNAL(GotResizeImage(cv::Mat)), ImageProcessingInstance->GetNode("FindChessboardNode"), SLOT(Input(cv::Mat)));
    connect(this, SIGNAL(GotCalibPoints(QPolygonF)), ImageProcessingInstance->GetNode("MappingMatrixNode"), SLOT(Input(QPolygonF)));

    connect(ui->gvImageViewer, SIGNAL(changedQuadrangle(QPolygonF)), ImageProcessingInstance->GetNode("GetPerspectiveNode"), SLOT(Input(QPolygonF)));

    connect(ui->gvImageViewer, SIGNAL(changedArea(QRectF)), ImageProcessingInstance->GetNode("CropImageNode"), SLOT(Input(QRectF)));

    connect(ui->leImageWidth, &QLineEdit::returnPressed,
    [=] (){
        int newW = ui->leImageWidth->text().toInt();

        QSize imageSize = ImageProcessingInstance->GetNode("GetImageNode")->GetImageSize();

        int newH = ImageTool::Map(newW, imageSize.width(), imageSize.height());

        ui->leImageHeight->setText(QString::number(newH));

        emit GotResizePara(cv::Size(newW, newH));

        SaveDetectingUI();
    });

    connect(ui->leImageHeight, &QLineEdit::returnPressed,
    [=] (){
        int newH = ui->leImageHeight->text().toInt();

        QSize imageSize = ImageProcessingInstance->GetNode("GetImageNode")->GetImageSize();

        int newW = ImageTool::Map(newH, imageSize.height(), imageSize.width());

        ui->leImageWidth->setText(QString::number(newW));

        emit GotResizePara(cv::Size(newW, newH));

        SaveDetectingUI();
    });

    connect(ui->tbAutoResizeImage, &QToolButton::toggled, [=](bool checked)
    {
        TaskNode* resizeImageNode = ImageProcessingInstance->GetNode("ResizeImageNode");

        if (checked)
        {
            resizeImageNode->IsPass = false;
        }
        else
        {
            resizeImageNode->IsPass = true;
        }
    });
        
    connect(ImageProcessingInstance->GetNode("DisplayImageNode"), SIGNAL(HadOutput(QPixmap)), ui->gvImageViewer, SLOT(SetImage(QPixmap)));

    connect(ParameterPanel, SIGNAL(ColorFilterValueChanged(QList<int>)), ImageProcessingInstance->GetNode("ColorFilterNode"), SLOT(Input(QList<int>)));
    connect(ParameterPanel, SIGNAL(BlurSizeChanged(int)), ImageProcessingInstance->GetNode("ColorFilterNode"), SLOT(Input(int)));
    connect(ParameterPanel, SIGNAL(ColorInverted(bool)), ImageProcessingInstance->GetNode("ColorFilterNode"), SLOT(Input(bool)));

    connect(this, SIGNAL(GotObjects(QVector<Object>)), ImageProcessingInstance->GetNode("VisibleObjectsNode"), SLOT(Input(QVector<Object>)));

    connect(this, SIGNAL(GotMappingMatrix(QMatrix)), ImageProcessingInstance->GetNode("VisibleObjectsNode"), SLOT(Input(QMatrix)));
    connect(this, SIGNAL(GotOjectFilterInfo(Object)), ImageProcessingInstance->GetNode("GetObjectsNode"), SLOT(Input(Object)));

    connect(ImageProcessingInstance->GetNode("GetObjectsNode"), SIGNAL(HadOutput(QList<QPolygonF>)), ui->gvImageViewer, SLOT(DrawObjects(QList<QPolygonF>)));
    connect(ImageProcessingInstance->GetNode("FindCirclesNode"), SIGNAL(HadOutput(QList<QPolygonF>)), ui->gvImageViewer, SLOT(DrawObjects(QList<QPolygonF>)));
    connect(ImageProcessingInstance->GetNode("VisibleObjectsNode"), SIGNAL(HadOutput(QVector<Object>)), ImageProcessingInstance, SLOT(GotVisibleObjects(QVector<Object>)));

    connect(ui->leDetectingObjectListName, &QLineEdit::returnPressed, this, [=]()
    {
        ImageProcessingInstance->ObjectsName = ui->leDetectingObjectListName->text();
    });

    // ========== CIRCLE DETECTION PARAMETERS ==========
    connect(ui->leEdgeThreshold, &QLineEdit::returnPressed, this, &RobotWindow::UpdateCircleParameters);
    connect(ui->leCenterThreshold, &QLineEdit::returnPressed, this, &RobotWindow::UpdateCircleParameters);
    connect(ui->leMinRadius, &QLineEdit::returnPressed, this, &RobotWindow::UpdateCircleParameters);
    connect(ui->leMaxRadius, &QLineEdit::returnPressed, this, &RobotWindow::UpdateCircleParameters);
    
    // Load default circle parameters
    ui->leEdgeThreshold->setText("100");
    ui->leCenterThreshold->setText("30"); 
    ui->leMinRadius->setText("10");
    ui->leMaxRadius->setText("100");


    // Khai báo và khởi tạo luồng
    QThread* thread = new QThread;
    ImageProcessingInstance->moveToThread(thread);

    // Kết nối để đảm bảo sự sạch sẽ
    connect(thread, &QThread::finished, ImageProcessingInstance, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater); // Đảm bảo luồng cũng tự hủy khi kết thúc

    // Bắt đầu luồng
    thread->start();

//    qDebug() << "Main Thread id: " << QThread::currentThreadId();

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
    
    // Initialize GScript Help documentation
    InitGScriptHelp();
}

void RobotWindow::InitGScriptHelp()
{
    // Load GScript documentation HTML file into tbGcodeScriptHelp
    QString htmlFilePath = QCoreApplication::applicationDirPath() + "/GScript_Documentation.html";
    
    // Check if HTML file exists
    QFile htmlFile(htmlFilePath);
    if (htmlFile.exists() && htmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read HTML content
        QString htmlContent = htmlFile.readAll();
        htmlFile.close();
        
        // Set the HTML content to QTextBrowser
        ui->tbGcodeScriptHelp->setHtml(htmlContent);
        
        SoftwareLog("GScript Help documentation loaded successfully");
    } else {
        // Simple error message if file not found
        QString errorMessage = QString(
            "<html><body style='font-family: Arial; color: #ff6b6b; text-align: center; padding: 50px;'>"
            "<h2>⚠️ GScript Documentation Not Found</h2>"
            "<p>Could not load: <strong>%1</strong></p>"
            "<p>Please ensure GScript_Documentation.html is in the application directory.</p>"
            "</body></html>"
        ).arg(htmlFilePath);
        
        ui->tbGcodeScriptHelp->setHtml(errorMessage);
        SoftwareLog("GScript Help: HTML file not found at " + htmlFilePath);
    }
    
    // Set properties for better display
    ui->tbGcodeScriptHelp->setOpenExternalLinks(false);
    ui->tbGcodeScriptHelp->setSearchPaths(QStringList() << QCoreApplication::applicationDirPath());
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

    connect(ui->leX, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].X = ui->leX->text().toFloat();
//        UpdateVariable("X", QString::number(RobotParameters[RbID].X));
        emit Send(DeviceManager::ROBOT, QString("G01 X") + ui->leX->text());});
    connect(ui->leY, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].Y = ui->leY->text().toFloat();
//        UpdateVariable("Y", QString::number(RobotParameters[RbID].Y));
        emit Send(DeviceManager::ROBOT, QString("G01 Y") + ui->leY->text());});
    connect(ui->leZ, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].Z = ui->leZ->text().toFloat();
//        UpdateVariable("Z", QString::number(RobotParameters[RbID].Z));
        emit Send(DeviceManager::ROBOT, QString("G01 Z") + ui->leZ->text());});
    connect(ui->leW, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].W = ui->leW->text().toFloat();
//        UpdateVariable("W", QString::number(RobotParameters[RbID].W));
        emit Send(DeviceManager::ROBOT, QString("G01 W") + ui->leW->text());});
    connect(ui->leU, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].U = ui->leU->text().toFloat();
//        UpdateVariable("U", QString::number(RobotParameters[RbID].U));
        emit Send(DeviceManager::ROBOT, QString("G01 U") + ui->leU->text());});
    connect(ui->leV, &QLineEdit::returnPressed, this, [=](){RobotParameters[RbID].V = ui->leV->text().toFloat();
//        UpdateVariable("V", QString::number(RobotParameters[RbID].V));
        emit Send(DeviceManager::ROBOT, QString("G01 V") + ui->leV->text());});

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

    connect(ui->pbContinuousLeft, &QPushButton::pressed, [=](){Jogging("left", true);});
    connect(ui->pbContinuousLeft, &QPushButton::released, [=](){Jogging("left", false);});
    connect(ui->pbContinuousRight, &QPushButton::pressed, [=](){Jogging("right", true);});
    connect(ui->pbContinuousRight, &QPushButton::released, [=](){Jogging("right", false);});
    connect(ui->pbContinuousForward, &QPushButton::pressed, [=](){Jogging("forward", true);});
    connect(ui->pbContinuousForward, &QPushButton::released, [=](){Jogging("forward", false);});
    connect(ui->pbContinuousBackward, &QPushButton::pressed, [=](){Jogging("backward", true);});
    connect(ui->pbContinuousBackward, &QPushButton::released, [=](){Jogging("backward", false);});
    connect(ui->pbContinuousUp, &QPushButton::pressed, [=](){Jogging("up", true);});
    connect(ui->pbContinuousUp, &QPushButton::released, [=](){Jogging("up", false);});
    connect(ui->pbContinuousDown, &QPushButton::pressed, [=](){Jogging("down", true);});
    connect(ui->pbContinuousDown, &QPushButton::released, [=](){Jogging("down", false);});
}

void RobotWindow::InitCalibration()
{
    connect(ui->pbImageMapping, &QPushButton::clicked, this, &RobotWindow::UpdateRealPositionOfCalibPoints);

    // ========== Z-PLANE LIMITING CONNECTIONS ==========
    connect(ui->pbGetCurrentP1, &QPushButton::clicked, this, &RobotWindow::onGetCurrentPositionP1);
    connect(ui->pbGetCurrentP2, &QPushButton::clicked, this, &RobotWindow::onGetCurrentPositionP2);
    connect(ui->pbGetCurrentP3, &QPushButton::clicked, this, &RobotWindow::onGetCurrentPositionP3);
    connect(ui->pbCalculateZPlane, &QPushButton::clicked, this, &RobotWindow::onCalculateZPlane);
    connect(ui->pbTestZPlane, &QPushButton::clicked, this, &RobotWindow::onTestZPlane);
    connect(ui->gbZPlaneLimiting, &QGroupBox::toggled, this, &RobotWindow::onZPlaneLimitingToggled);

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


    // ----------GScript----------
    connect(ui->pbSaveGcode, SIGNAL(clicked(bool)), this, SLOT(SaveProgram()));


    connect(ui->pbExecuteGcodes, SIGNAL(clicked(bool)), this, SLOT(ExecuteProgram()));
    connect(ui->pteGcodeArea, SIGNAL(lineClicked(int, QString)), this, SLOT(ExecuteCurrentLine(int, QString)));
    connect(ui->pteGcodeArea, SIGNAL(textChanged()), this, SLOT(OnEditorTextChanged()));
    // ------------ Jogging -----------

    //---------- End effector -----------
	connect(ui->hsGripperAngle, SIGNAL(valueChanged(int)), this, SLOT(AdjustGripperAngle(int)));
	connect(ui->pbGrip, SIGNAL(clicked(bool)), this, SLOT(Grip()));
	connect(ui->pbPump, SIGNAL(clicked(bool)), this, SLOT(SetPump(bool)));
    connect(ui->pbPumpX3, SIGNAL(clicked(bool)), this, SLOT(SetPump(bool)));
	connect(ui->pbLaser, SIGNAL(clicked(bool)), this, SLOT(SetLaser(bool)));

    //----- Delta X 3 IO -----
    connect(ui->cbX3D0, SIGNAL(clicked(bool)), this, SLOT(SetOutputX3(bool)));
    connect(ui->cbX3D1, SIGNAL(clicked(bool)), this, SLOT(SetOutputX3(bool)));
    connect(ui->cbX3D2, SIGNAL(clicked(bool)), this, SLOT(SetOutputX3(bool)));
    connect(ui->cbX3D3, SIGNAL(clicked(bool)), this, SLOT(SetOutputX3(bool)));

    connect(ui->pbReadI0X3, SIGNAL(clicked()), this, SLOT(GetInputX3()));
    connect(ui->pbReadI1X3, SIGNAL(clicked()), this, SLOT(GetInputX3()));
    connect(ui->pbReadI2X3, SIGNAL(clicked()), this, SLOT(GetInputX3()));
    connect(ui->pbReadI3X3, SIGNAL(clicked()), this, SLOT(GetInputX3()));
    connect(ui->pbReadA0X3, SIGNAL(clicked()), this, SLOT(GetInputX3()));
    connect(ui->pbReadA1X3, SIGNAL(clicked()), this, SLOT(GetInputX3()));

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
	connect(ui->pbOpenGcodeDocs, SIGNAL(clicked(bool)), this, SLOT(OpenGcodeReference()));

    connect(ui->cbEditGcodeLock, SIGNAL(stateChanged(int)), ui->pteGcodeArea, SLOT(setLockState(int)));
    connect(ui->cbGScriptEditorZoom, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RobotWindow::changeFontSize);

    //------------ Image Processing -----------


    connect(ui->pbRunExternalScript, SIGNAL(clicked(bool)), this, SLOT(RunExternalScript()));
    connect(ui->pbExternalScriptOpen, SIGNAL(clicked(bool)), this, SLOT(OpenExternalScriptFolder()));

    connect(ui->cbSourceForImageProvider, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectImageProviderOption(int)));

//    SelectImageProviderOption(0);

    // -------- Point Tool -------

    connect(ui->tbCopyEncoderPosition, &QPushButton::clicked, [=]()
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ui->leEncoderCurrentPosition->text());

    });

    connect(ui->tbCopyTestTrackingPoint, &QPushButton::clicked, [=]()
    {
        // Copy giá trị vào clipboard
        QString text = QString("%1, %2, %3").arg(ui->leTestTrackingPointX->text()).arg(ui->leTestTrackingPointY->text()).arg(ui->leTestTrackingPointZ->text());
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(text);

    });

    connect(ui->tbPasteTestTrackingPoint, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leTestTrackingPointX, ui->leTestTrackingPointY, ui->leTestTrackingPointZ);
        }
    });

    connect(ui->pbMoveTestTrackingPoint, &QPushButton::clicked, this, &RobotWindow::MoveTestTrackingPoint);

    connect(ui->tbAutoMove, &QToolButton::toggled, [=](bool checked)
    {
        TrackingManagerInstance->Trackings.at(0)->IsUpateTestPoint = checked;
    });

    connect(ui->pbCalculateMappingMatrixTool, SIGNAL(clicked(bool)), this, SLOT(CalculateMappingMatrixTool()));
    connect(ui->pbCalculatePointMatrixTool, SIGNAL(clicked(bool)), this, SLOT(CalculatePointMatrixTool()));
    connect(ui->pbCalculateTestPoint, SIGNAL(clicked(bool)), this, SLOT(CalculateTestPoint()));
    connect(ui->pbCalVector, SIGNAL(clicked(bool)), this, SLOT(CalculateVector()));

    connect(ui->pbAnglePoint1, &QPushButton::clicked, [=](){
        if (m_pointToolController) {
            m_pointToolController->setCurrentRobotPosition(ui->leVectorPoint1X, ui->leVectorPoint1Y, ui->leVectorPoint1Z);
        }
    });
    connect(ui->pbAnglePoint2, &QPushButton::clicked, [=](){
        if (m_pointToolController) {
            m_pointToolController->setCurrentRobotPosition(ui->leVectorPoint2X, ui->leVectorPoint2Y, ui->leVectorPoint2Z);
        }
    });

    connect(ui->tbPasteVectorPoint1, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leVectorPoint1X, ui->leVectorPoint1Y, ui->leVectorPoint1Z);
        }
    });

    connect(ui->tbPasteVectorPoint2, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leVectorPoint2X, ui->leVectorPoint2Y, ui->leVectorPoint2Z);
        }
    });

    connect(ui->tbPasteSourcePoint1, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leSourcePoint1X, ui->leSourcePoint1Y, nullptr);
        }
    });
    connect(ui->tbPasteSourcePoint2, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leSourcePoint2X, ui->leSourcePoint2Y, nullptr);
        }
    });
    connect(ui->tbPasteDestinationPoint1, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leDestinationPoint1X, ui->leDestinationPoint1Y, nullptr);
        }
    });
    connect(ui->tbPasteDestinationPoint2, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leDestinationPoint2X, ui->leDestinationPoint2Y, nullptr);
        }
    });

    connect(ui->pbAddMappingMatrix, &QPushButton::clicked, [=]()
    {
        QString prefix = ProjectName + "." + ui->cbSelectedTracking->currentText() + ".";

        QString transformString = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9")
                .arg(m_currentMappingTransform.m11())
                .arg(m_currentMappingTransform.m12())
                .arg(m_currentMappingTransform.m13())
                .arg(m_currentMappingTransform.m21())
                .arg(m_currentMappingTransform.m22())
                .arg(m_currentMappingTransform.m23())
                .arg(m_currentMappingTransform.m31())
                .arg(m_currentMappingTransform.m32())
                .arg(m_currentMappingTransform.m33());

        VariableManager::instance().updateVar(prefix + ui->leMatrixName->text(), m_currentMappingTransform);
        VariableManager::instance().updateVar(prefix + ui->leMatrixName->text() + "String", transformString);

        if (!isItemExit(ui->lwMappingMatrixList, ui->leMatrixName->text())) {
            ui->lwMappingMatrixList->addItem(ui->leMatrixName->text());
        }
    });

    connect(ui->pbAddPointMatrix, &QPushButton::clicked, [=]()
    {
        QString prefix = ProjectName + "." + ui->cbSelectedTracking->currentText() + ".";

        std::vector<double> matrixArray;
        matrixArray.assign(m_currentPerspectiveMatrix.begin<double>(), m_currentPerspectiveMatrix.end<double>());

        // Tạo một QVariant từ mảng và lưu trữ ma trận
        QVariant matrixVariant = QVariant::fromValue(matrixArray);

        VariableManager::instance().updateVar(prefix + ui->lePointMatrixName->text(), matrixVariant);

        if (!isItemExit(ui->lwPointMatrixList, ui->lePointMatrixName->text()))
        {
            ui->lwPointMatrixList->addItem(ui->lePointMatrixName->text());
        }
    });

    connect(ui->pbAddVector, &QPushButton::clicked, [=]()
    {
        m_currentCalculatedVector.setX(ui->leVectorX->text().toFloat());
        m_currentCalculatedVector.setY(ui->leVectorY->text().toFloat());
        m_currentCalculatedVector.setZ(ui->leVectorZ->text().toFloat());

        QString prefix = ProjectName + "." + ui->cbSelectedTracking->currentText() + ".";

        VariableManager::instance().updateVar(prefix + ui->leVectorName->text(), QVector3D(m_currentCalculatedVector.x(), m_currentCalculatedVector.y(), m_currentCalculatedVector.z()));

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
            QVector<ObjectInfo> list;
            QVector3D position(x, y, z);

            ObjectInfo object(-1, 0, position, 20, 40, angle);
            list.append(object);
            TrackingManagerInstance->Trackings.at(selectedEncoderID)->UpdateTrackedObjects(list, ui->leObjectListName->text());
        }
        else
        {
            QString listName = ui->leObjectListName->text();
            int counter = VariableManager::instance().getVar(listName + ".Count", 0).toInt();
            VariableManager::instance().updateVar((listName + ".%1.X").arg(counter), x);
            VariableManager::instance().updateVar((listName + ".%1.Y").arg(counter), y);
            VariableManager::instance().updateVar((listName + ".%1.Z").arg(counter), z);
            VariableManager::instance().updateVar((listName + ".%1.W").arg(counter), 20);
            VariableManager::instance().updateVar((listName + ".%1.L").arg(counter), 40);
            VariableManager::instance().updateVar((listName + ".%1.A").arg(counter), angle);

            VariableManager::instance().updateVar(listName + ".Count", counter + 1);
        }
    });

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
    connect(ui->pbGetPlaneAPoint, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leADrawingPoint);
    });
    connect(ui->pbGetPlaneBPoint, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leBDrawingPoint);
    });
    connect(ui->pbGetPlaneCPoint, &QPushButton::clicked, [=]()
    {
        pastePointValues(ui->leCDrawingPoint);
    });


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

    if (IsGcodeEditorTextChanged == true)
    {
        SaveProgram();
    }



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
        ui->twGcodeEditor->setTabText(0, fileName);

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
//    connect(GcodeScriptThread, SIGNAL(SaveVariable(QString, QString)), this, SLOT(UpdateVariable(QString, QString)));

//    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects()), this, SLOT(ClearObjectsToVariableTable()));
//    connect(GcodeScriptThread, SIGNAL(DeleteObject1()), this, SLOT(DeleteFirstVariable()));
//    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects()), ImageProcessingInstance->GetNode("TrackingObjectsNode"), SLOT(ClearOutput()));
//    connect(GcodeScriptThread, SIGNAL(DeleteObject(int)), ImageProcessingInstance->GetNode("TrackingObjectsNode"), SLOT(DeleteOutput(int)));

    connect(GcodeScriptThread, &GcodeScript::PauseCamera, [=](){ CameraTimer.stop();});
    connect(GcodeScriptThread, &GcodeScript::ResumeCamera, [=](){ CameraTimer.start(ui->leCaptureInterval->text().toInt());});
    connect(GcodeScriptThread, &GcodeScript::CaptureCamera, CameraInstance, &Camera::GeneralCapture);
    connect(GcodeScriptThread, &GcodeScript::CaptureAndDetectRequest, CameraInstance, &Camera::CaptureAndDetect);

    connect(GcodeScriptThread, &GcodeScript::GetObjectsRequest, TrackingManagerInstance, &TrackingManager::GetObjectsInArea);
    connect(GcodeScriptThread, &GcodeScript::UpdateTrackingRequest, TrackingManagerInstance, &TrackingManager::UpdateTracking);
    connect(GcodeScriptThread, &GcodeScript::ChangeExternalVariable, TrackingManagerInstance, &TrackingManager::UpdateVariable);
    connect(GcodeScriptThread, &GcodeScript::AddObject, TrackingManagerInstance, &TrackingManager::AddObject);
    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects(QString)), TrackingManagerInstance, SLOT(ClearObjects(QString)));
    connect(ConnectionManager, &SocketConnectionManager::objectUpdated, TrackingManagerInstance, &TrackingManager::AddObject);
    connect(ConnectionManager, SIGNAL(blobUpdated(QStringList)), ImageProcessingInstance->GetNode("GetObjectsNode"), SLOT(Input(QStringList)));
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


    connect(ui->pbSaveTrackingManager, &QPushButton::clicked, this, &RobotWindow::SaveTrackingManager);
    connect(ui->cbReverseEncoderValue, SIGNAL(clicked(bool)), tracking, SLOT(SetEncoderReverse(bool)));

    connect(tracking, SIGNAL(SendGcodeRequest(QString, QString)), DeviceManagerInstance, SLOT(SendGcode(QString, QString)));
    connect(tracking, SIGNAL(UpdateTrackingDone()), TrackingManagerInstance, SLOT(OnDoneUpdateTracking()));

    connect(ImageProcessingInstance, SIGNAL(mappedDetectedObjects(QVector<ObjectInfo>, QString)), tracking, SLOT(UpdateTrackedObjects(QVector<ObjectInfo>, QString)));
    connect(tracking, SIGNAL(TestPointUpdated(QVector3D)), this, SLOT(UpdateTestPoint(QVector3D)));

    trackingThread->start();

    tracking->ID = TrackingManagerInstance->Trackings.count();
    TrackingManagerInstance->Trackings.append(tracking);

    if (tracking->ID > 0)
    {
        tracking->ListName = QString("#Objects") + QString::number(tracking->ID + 1);
    }

    VariableManager::instance().ObjectInfos.insert(tracking->ListName.mid(1), &tracking->TrackedObjects);
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
    LoadExternalDeviceSettings();
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
                    emit ChangeDeviceState(device + QString::number(id), true, comName);
                }
            }
            else
            {
                break;
            }
        }
    }
    
    // Load robot settings after general settings
    LoadRobotSettings();
    
    // ========== LOAD Z-PLANE SETTINGS ==========
    LoadZPlaneSettings();
}

void RobotWindow::LoadZPlaneSettings()
{
    if (!ui) return;
    
    QString prefix = ProjectName + ".ZPlane.";
    
    // Load Z-plane points
    m_zPlane.p1.x = VariableManager::instance().getVar(prefix + "P1.X", 0.0).toDouble();
    m_zPlane.p1.y = VariableManager::instance().getVar(prefix + "P1.Y", 0.0).toDouble();
    m_zPlane.p1.z = VariableManager::instance().getVar(prefix + "P1.Z", 0.0).toDouble();
    
    m_zPlane.p2.x = VariableManager::instance().getVar(prefix + "P2.X", 100.0).toDouble();
    m_zPlane.p2.y = VariableManager::instance().getVar(prefix + "P2.Y", 0.0).toDouble();
    m_zPlane.p2.z = VariableManager::instance().getVar(prefix + "P2.Z", 0.0).toDouble();
    
    m_zPlane.p3.x = VariableManager::instance().getVar(prefix + "P3.X", 0.0).toDouble();
    m_zPlane.p3.y = VariableManager::instance().getVar(prefix + "P3.Y", 100.0).toDouble();
    m_zPlane.p3.z = VariableManager::instance().getVar(prefix + "P3.Z", 0.0).toDouble();
    
    // Load plane equation parameters
    m_zPlane.a = VariableManager::instance().getVar(prefix + "A", 0.0).toDouble();
    m_zPlane.b = VariableManager::instance().getVar(prefix + "B", 0.0).toDouble();
    m_zPlane.c = VariableManager::instance().getVar(prefix + "C", 1.0).toDouble();
    m_zPlane.d = VariableManager::instance().getVar(prefix + "D", 0.0).toDouble();
    
    // Load status flags
    m_zPlane.isValid = VariableManager::instance().getVar(prefix + "IsValid", false).toBool();
    m_zPlane.isEnabled = VariableManager::instance().getVar(prefix + "IsEnabled", false).toBool();
    
    // Update UI with loaded values
    ui->leZPlaneP1X->setText(QString::number(m_zPlane.p1.x, 'f', 1));
    ui->leZPlaneP1Y->setText(QString::number(m_zPlane.p1.y, 'f', 1));
    ui->leZPlaneP1Z->setText(QString::number(m_zPlane.p1.z, 'f', 1));
    
    ui->leZPlaneP2X->setText(QString::number(m_zPlane.p2.x, 'f', 1));
    ui->leZPlaneP2Y->setText(QString::number(m_zPlane.p2.y, 'f', 1));
    ui->leZPlaneP2Z->setText(QString::number(m_zPlane.p2.z, 'f', 1));
    
    ui->leZPlaneP3X->setText(QString::number(m_zPlane.p3.x, 'f', 1));
    ui->leZPlaneP3Y->setText(QString::number(m_zPlane.p3.y, 'f', 1));
    ui->leZPlaneP3Z->setText(QString::number(m_zPlane.p3.z, 'f', 1));
    
    ui->gbZPlaneLimiting->setChecked(m_zPlane.isEnabled);
    
    // Update equation display
    updateZPlaneEquationDisplay();
    
    SoftwareLog(QString("Z-Plane: Settings loaded - Valid=%1, Enabled=%2")
               .arg(m_zPlane.isValid ? "true" : "false")
               .arg(m_zPlane.isEnabled ? "true" : "false"));
}

void RobotWindow::LoadRobotSettings()
{
    // Set flag to prevent saving while loading
    isLoadingSettings = true;
    
    // Load robot model and DOF settings for the currently selected robot
    int currentRobotId = ui->cbSelectedRobot->currentIndex();
    QString robotPrefix = ProjectName + ".robot" + QString::number(currentRobotId);
    
    // Load robot model
    int savedModelIndex = VariableManager::instance().getVar(robotPrefix + ".Model", 0).toInt();
    if (savedModelIndex >= 0 && savedModelIndex < ui->cbRobotModel->count())
    {
        ui->cbRobotModel->setCurrentIndex(savedModelIndex);
        // Apply model changes without saving again
        ChangeRobotModel(savedModelIndex);
    }
    
    // Load robot DOF
    int savedDOFIndex = VariableManager::instance().getVar(robotPrefix + ".DOF", 0).toInt();
    if (savedDOFIndex >= 0 && savedDOFIndex < ui->cbRobotDOF->count())
    {
        ui->cbRobotDOF->setCurrentIndex(savedDOFIndex);
        // Apply DOF changes without saving again
        ChangeRobotDOF(savedDOFIndex);
    }
    
    // Reset flag after loading
    isLoadingSettings = false;
    isCameraLoaded = false;
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

void RobotWindow::LoadExternalDeviceSettings()
{
    //---- Conveyor -----
    QString prefix = ProjectName + "." + ui->cbSelectedConveyor->currentText() + ".";

    ui->cbConveyorType->setCurrentIndex(VariableManager::instance().getVar(prefix + "ConveyorType").toInt());
    ui->cbConveyorMode->setCurrentIndex(VariableManager::instance().getVar(prefix + "ConveyorMode").toInt());
    ui->leConveyorXSpeed->setText(VariableManager::instance().getVar(prefix + "ConveyorSpeed").toString());
    ui->leConveyorXPosition->setText(VariableManager::instance().getVar(prefix + "ConveyorPosition").toString());
    ui->leConveyorXAbsolutePosition->setText(VariableManager::instance().getVar(prefix + "ConveyorAbsolutePosition").toString());

    //---- Encoder -----

    prefix = ProjectName + "." + ui->cbSelectedEncoder->currentText() + ".";

    ui->cbEncoderType->setCurrentIndex(VariableManager::instance().getVar(prefix + "EncoderType").toInt());
    Qt::CheckState checkState = static_cast<Qt::CheckState>(VariableManager::instance().getVar(prefix + "ConveyorLinkToEncoder").toInt());
    ui->cbLinkToConveyorX->setCheckState(checkState);
    ui->leEncoderInterval->setText(VariableManager::instance().getVar(prefix + "Interval").toString());
    ui->leEncoderVelocity->setText(VariableManager::instance().getVar(prefix + "Velocity").toString());

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
    }
    else
    {
        ui->pbWarpTool->setChecked(false);
    }

    if (VariableManager::instance().getVar(prefix + "CropEnable", false).toBool() == true)
    {
        ui->pbCropTool->setChecked(true);
    }
    else
    {
        ui->pbCropTool->setChecked(false);
    }

    EditImage(ui->pbWarpTool->isChecked(), ui->pbCropTool->isChecked());

//    QString imageSource = VariableManager::instance().getVar(prefix + "ImageSource", ui->cbSourceForImageProvider->currentText()).toString();
    QString imageSource = VariableManager::instance().getVar(prefix + "ImageSource", "source").toString();

    int index = ui->cbSourceForImageProvider->findText(imageSource);
    ui->cbSourceForImageProvider->setCurrentIndex(index);

    ui->leCaptureInterval->setText(VariableManager::instance().getVar(prefix + "WebcamInterval", ui->leCaptureInterval->text()).toString());

    ui->leImageWidth->setText(VariableManager::instance().getVar(prefix + "ResizeWidth", ui->leImageWidth->text()).toString());
    ui->leImageHeight->setText(VariableManager::instance().getVar(prefix + "ResizeHeight", ui->leImageHeight->text()).toString());

    emit GotResizePara(cv::Size(ui->leImageWidth->text().toInt(), ui->leImageHeight->text().toInt()));

    bool IsCameraOpen = VariableManager::instance().getVar(prefix + "IsOpen", false).toBool();
    int cameraID = VariableManager::instance().getVar(prefix + "CameraID", 0).toInt();

//    if (IsCameraOpen == true)
//    {
//        if (imageSource == "Industrial Camera")
//        {
//            DeltaXPlugin* camera = industrialCameraPlugin;
//            QTimer::singleShot(2000, [camera, cameraID]() {
//                emit camera->RequestConnect(cameraID);
//            });
//        }
//        else if (imageSource == "Webcam")
//        {
//            QMetaObject::invokeMethod(CameraInstance, "OpenCamera", Qt::QueuedConnection, Q_ARG(int, cameraID));
//        }
//    }



//    Object& obj = ImageProcessingInstance->GetNode("GetObjectsNode")->GetInputObject();

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

    ui->cbDetectingAlgorithm->setCurrentText(VariableManager::instance().getVar(prefix + "DetectAlgorithm", ui->cbDetectingAlgorithm->currentText()).toString());

    //    ui->lePythonUrl->setText(setting->value("ExternalScriptUrl", ui->lePythonUrl->text()).toString());
    
    // Load model path setting (for future UI field)
    // QString savedModelPath = setting->value("ExternalScript/ModelPath", "").toString();
    // if (!savedModelPath.isEmpty()) {
    //     qDebug() << "Loaded model path from settings:" << savedModelPath;
    // }
    ui->cbImageSource->setCurrentText(VariableManager::instance().getVar(prefix + "ImageSource", ui->cbImageSource->currentText()).toString());

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
    if (!setting || !pluginList) {
        qWarning() << "Cannot load plugin settings: null parameters";
        return;
    }
    
    setting->beginGroup("Plugin");
    
    for (int i = 0; i < pluginList->count(); i++)
    {
        DeltaXPlugin* plugin = pluginList->at(i);
        if (!plugin) {
            qWarning() << "Null plugin at index" << i;
            continue;
        }
        
        // ✅ Fix: Consistent settings key format
        QString settingKey = plugin->GetName() + "-" + QString::number(i);
        setting->beginGroup(settingKey);
        
        try {
            plugin->LoadSettings(setting);
            qDebug() << "Loaded settings for plugin:" << plugin->GetName();
        } catch (const std::exception& e) {
            qWarning() << "Exception loading settings for plugin" << plugin->GetName() << ":" << e.what();
        } catch (...) {
            qWarning() << "Unknown exception loading settings for plugin" << plugin->GetName();
        }
        
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
    
    // ========== SAVE Z-PLANE SETTINGS ==========
    SaveZPlaneSettings();
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
//    setting->setValue("DisplayOutput", ui->cbImageOutput->currentText());


//----------
    setting->setValue("ImageSource", ui->cbSourceForImageProvider->currentText());

    setting->setValue("WebcamInterval", ui->leCaptureInterval->text());

    setting->setValue("ResizeWidth", ui->leImageWidth->text());
    setting->setValue("ResizeHeight", ui->leImageHeight->text());

    Object& obj = ImageProcessingInstance->GetNode("GetObjectsNode")->GetInputObject();

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
    
    // Save model path setting
    QString currentModelPath = getModelPath();
    if (!currentModelPath.isEmpty()) {
        setting->setValue("ExternalScript/ModelPath", currentModelPath);
    }
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
    if (!setting || !pluginList) {
        qWarning() << "Cannot save plugin settings: null parameters";
        return;
    }
    
    setting->beginGroup("Plugin");
    
    for (int i = 0; i < pluginList->count(); i++)
    {
        DeltaXPlugin* plugin = pluginList->at(i);
        if (!plugin) {
            qWarning() << "Null plugin at index" << i;
            continue;
        }
        
        // ✅ Fix: Consistent settings key format (same as LoadPluginSetting)
        QString settingKey = plugin->GetName() + "-" + QString::number(i);
        setting->beginGroup(settingKey);
        
        try {
            plugin->SaveSettings(setting);
            qDebug() << "Saved settings for plugin:" << plugin->GetName();
        } catch (const std::exception& e) {
            qWarning() << "Exception saving settings for plugin" << plugin->GetName() << ":" << e.what();
        } catch (...) {
            qWarning() << "Unknown exception saving settings for plugin" << plugin->GetName();
        }
        
        setting->endGroup();
    }
    
    setting->endGroup();
}

void RobotWindow::InitDefaultValue()
{
    ChangeEncoderType(0);

    ui->pbSaveTrackingManager->click();

    ui->twModule->setCurrentIndex(0);
    ui->twDevices->setCurrentIndex(0);

    IsGcodeEditorTextChanged = false;
    baseFontSize = ui->cbGScriptEditorZoom->font().pointSize();

    ChangeRobotModel(ui->cbRobotModel->currentIndex());
    SelectImageProviderOption(0);

    //------ Hide UI ----
    ui->fCapturingImages->setVisible(false);
    ui->lwImageList->setVisible(false);

    // ------- Tracking -------
    SaveTrackingManager();
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

void RobotWindow::ActivateButtonByName(const QString &buttonName)
{
    QPushButton *button = findChild<QPushButton*>(buttonName);
    if (button) {
        button->click();
    }
}

void RobotWindow::ActiveWidgetByName(QString type, QString name, QString action)
{
    SoftwareLog(QString("ActiveWidgetByName called: %1 %2 %3").arg(type).arg(name).arg(action));
    qDebug() << "ActiveWidgetByName called:" << type << name << action;
    
    bool buttonFound = false;
    
    if (type == "QPushButton")
    {
        QPushButton *button = findChild<QPushButton*>(name);
        if (button && action == "click")
        {
            qDebug() << "Clicking QPushButton:" << name;
            SoftwareLog(QString("Successfully clicked QPushButton: %1").arg(name));
            button->click();
            buttonFound = true;
        }
        else
        {
            qDebug() << "QPushButton not found or invalid action:" << name << action;
            // Try as QToolButton fallback
            QToolButton *toolButton = findChild<QToolButton*>(name);
            if (toolButton && action == "click")
            {
                qDebug() << "Fallback: Clicking as QToolButton:" << name;
                SoftwareLog(QString("Fallback: Successfully clicked QToolButton: %1").arg(name));
                toolButton->click();
                buttonFound = true;
            }
        }
    }
    else if (type == "QToolButton")
    {
        QToolButton *button = findChild<QToolButton*>(name);
        if (button && action == "click")
        {
            qDebug() << "Clicking QToolButton:" << name;
            SoftwareLog(QString("Successfully clicked QToolButton: %1").arg(name));
            button->click();
            buttonFound = true;
        }
        else if (button && action == "toggle")
        {
            qDebug() << "Toggling QToolButton:" << name;
            SoftwareLog(QString("Successfully toggled QToolButton: %1").arg(name));
            button->setChecked(!button->isChecked());
            buttonFound = true;
        }
        else
        {
            qDebug() << "QToolButton not found or invalid action:" << name << action;
            // Try as QPushButton fallback
            QPushButton *pushButton = findChild<QPushButton*>(name);
            if (pushButton && action == "click")
            {
                qDebug() << "Fallback: Clicking as QPushButton:" << name;
                SoftwareLog(QString("Fallback: Successfully clicked QPushButton: %1").arg(name));
                pushButton->click();
                buttonFound = true;
            }
        }
    }
    else if (type == "QRadioButton")
    {
        QRadioButton *button = findChild<QRadioButton*>(name);
        if (button && action == "toggle")
        {
            qDebug() << "Toggling QRadioButton:" << name;
            SoftwareLog(QString("Successfully toggled QRadioButton: %1").arg(name));
            button->toggle();
            buttonFound = true;
        }
        else if (button && action == "check")
        {
            qDebug() << "Checking QRadioButton:" << name;
            SoftwareLog(QString("Successfully checked QRadioButton: %1").arg(name));
            button->setChecked(true);
            buttonFound = true;
        }
        else
        {
            qDebug() << "QRadioButton not found or invalid action:" << name << action;
        }
    }
    else if (type == "QCheckBox")
    {
        QCheckBox *checkBox = findChild<QCheckBox*>(name);
        if (checkBox && action == "toggle")
        {
            qDebug() << "Toggling QCheckBox:" << name;
            checkBox->toggle();
        }
        else if (checkBox && (action == "true" || action == "false"))
        {
            qDebug() << "Setting QCheckBox:" << name << "to" << action;
            checkBox->setChecked(action == "true");
        }
        else
        {
            qDebug() << "QCheckBox not found or invalid action:" << name << action;
        }
    }
    else if (type == "QLineEdit")
    {
        QLineEdit *lineEdit = findChild<QLineEdit*>(name);
        if (lineEdit)
        {
            qDebug() << "Setting QLineEdit:" << name << "to" << action;
            lineEdit->setText(action);
            emit lineEdit->returnPressed();
        }
        else
        {
            qDebug() << "QLineEdit not found:" << name;
        }
    }
    else if (type == "QComboBox")
    {
        QComboBox *comboBox = findChild<QComboBox*>(name);
        if (comboBox)
        {
            // Try to set by text first
            int index = comboBox->findText(action);
            if (index >= 0)
            {
                qDebug() << "Setting QComboBox:" << name << "to text:" << action;
                comboBox->setCurrentIndex(index);
            }
            else
            {
                // Try to set by index
                bool ok;
                int indexValue = action.toInt(&ok);
                if (ok && indexValue >= 0 && indexValue < comboBox->count())
                {
                    qDebug() << "Setting QComboBox:" << name << "to index:" << indexValue;
                    comboBox->setCurrentIndex(indexValue);
        }
                else
                {
                    qDebug() << "QComboBox invalid value:" << name << action;
                }
            }
        }
        else
        {
            qDebug() << "QComboBox not found:" << name;
        }
    }
    else if (type == "QSpinBox")
    {
        QSpinBox *spinBox = findChild<QSpinBox*>(name);
        if (spinBox)
        {
            bool ok;
            int value = action.toInt(&ok);
            if (ok)
            {
                qDebug() << "Setting QSpinBox:" << name << "to" << value;
                spinBox->setValue(value);
            }
            else
            {
                qDebug() << "QSpinBox invalid value:" << name << action;
            }
        }
        else
        {
            qDebug() << "QSpinBox not found:" << name;
        }
    }
    else if (type == "QDoubleSpinBox")
    {
        QDoubleSpinBox *doubleSpinBox = findChild<QDoubleSpinBox*>(name);
        if (doubleSpinBox)
        {
            bool ok;
            double value = action.toDouble(&ok);
            if (ok)
            {
                qDebug() << "Setting QDoubleSpinBox:" << name << "to" << value;
                doubleSpinBox->setValue(value);
            }
            else
            {
                qDebug() << "QDoubleSpinBox invalid value:" << name << action;
            }
        }
        else
        {
            qDebug() << "QDoubleSpinBox not found:" << name;
        }
    }
    else if (type == "QSlider")
    {
        QSlider *slider = findChild<QSlider*>(name);
        if (slider)
        {
            bool ok;
            int value = action.toInt(&ok);
            if (ok)
            {
                qDebug() << "Setting QSlider:" << name << "to" << value;
                slider->setValue(value);
            }
            else
            {
                qDebug() << "QSlider invalid value:" << name << action;
            }
        }
        else
        {
            qDebug() << "QSlider not found:" << name;
        }
    }
    else
    {
        qDebug() << "Unsupported widget type:" << type;
        SoftwareLog(QString("Unsupported widget type: %1 %2 %3").arg(type).arg(name).arg(action));
    }
    
    // Log if no button was found
    if (!buttonFound && (type == "QPushButton" || type == "QToolButton"))
    {
        SoftwareLog(QString("ERROR: Button not found: %1 %2 %3").arg(type).arg(name).arg(action));
    }
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
    QString response = jsonObject.value("response").toString();
    QString gcode = jsonObject.value("gcode").toString();

            QString devicePrefix = getDevicePrefix(device, id);
        QHash<QString, QVariant> deviceUpdates;
        deviceUpdates["COM.Name"] = com_name;
        deviceUpdates["COM.State"] = state;
        batchUpdateVariables(devicePrefix, deviceUpdates);

    QString prefix = devicePrefix;

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
            ui->pbConnectRobot->setText("Disconnect");
            ui->pbConnectRobot->setEnabled(true);
        }
        else
        {
            ui->pbConnectRobot->setText("Connect");
            ui->pbConnectRobot->setEnabled(true);
        }

        ui->lbComName->setText(jsonObject.value("com_name").toString());

        if (gcode.contains("connect"))
        {
            emit Send(DeviceManager::ROBOT, "Position");
        }



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

    else if (device == "slider" && id == getIDfromName(ui->cbSelectedSlider->currentText()))
    {
        if (state == "open")
        {
            ui->pbSlidingConnect->setText("Disconnect");
        }
        else
        {
            ui->pbSlidingConnect->setText("Connect");
        }

        ui->lbSliderCOMName->setText(jsonObject.value("com_name").toString());
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
                // ----- Scheduled Encoder ---------
                if (abs(value.toFloat() - scheduledStartEncoderValue) > ui->leScheduledDistance->text().toFloat() && isScheduledEncoder == true)
                {
                    QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, ui->leScheduledGcode->text()));
                    isScheduledEncoder = false;
                    ui->pbStartScheduledEncoder->setText("Start");
                }
                // ---------------------------------

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
    try {
    if (ui->tbAutoScanRobot->isChecked() == true)
    {
        OpenLoadingPopup();
            emit ChangeDeviceState(ui->cbSelectedRobot->currentText(), (ui->pbConnectRobot->text() == "Connect")?true:false, "auto");
        return;
    }

        if (ui->pbConnectRobot->text() != "Connect")
    {
        emit ChangeDeviceState(ui->cbSelectedRobot->currentText(), false, "");
        return;
    }

    QStringList items;
        bool hasAvailablePorts = false;

    Q_FOREACH(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial(portInfo);
        if(serial.open(QIODevice::ReadWrite))
        {
            items << portInfo.portName() + " - " + portInfo.description();
            serial.close();
                hasAvailablePorts = true;
            }
        }

        if (!hasAvailablePorts)
        {
            QMessageBox::warning(this, tr("Connection Error"), 
                                tr("No available COM ports found. Please check your device connections."));
            return;
    }

    bool ok;
    QString item = QInputDialog::getItem(this, tr("COM Connection"), tr("COM Ports:"), items, 0, false, &ok);
        
        if (!ok || item.isEmpty())
        {
            return; // User cancelled
        }

        // Validate COM port name
        int separatorIndex = item.indexOf(" - ");
        if (separatorIndex == -1)
        {
            QMessageBox::warning(this, tr("Connection Error"), tr("Invalid COM port format."));
            return;
        }
        
        QString comName = item.mid(0, separatorIndex);
        if (comName.isEmpty())
    {
            QMessageBox::warning(this, tr("Connection Error"), tr("Empty COM port name."));
            return;
        }

        bool ok2;
        QString baudrate = QInputDialog::getText(this, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
        
        if (!ok2 || baudrate.isEmpty())
        {
            return; // User cancelled
        }

        // Validate baudrate
        bool validBaudrate = false;
        int baudrateValue = baudrate.toInt(&validBaudrate);
        if (!validBaudrate || baudrateValue <= 0)
        {
            QMessageBox::warning(this, tr("Connection Error"), tr("Invalid baudrate value."));
            return;
        }

        // Disable button during connection attempt
        ui->pbConnectRobot->setEnabled(false);
        ui->pbConnectRobot->setText("Connecting...");

        emit ChangeDeviceState(ui->cbSelectedRobot->currentText(), true, comName);

        // Re-enable button after a timeout (will be updated by device response)
        QTimer::singleShot(5000, [this]() {
            if (ui->pbConnectRobot->text() == "Connecting...")
            {
                ui->pbConnectRobot->setEnabled(true);
                ui->pbConnectRobot->setText("Connect");
                QMessageBox::warning(this, tr("Connection Timeout"), 
                                    tr("Connection attempt timed out. Please try again."));
        }
        });
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, tr("Connection Error"), 
                             tr("An error occurred while connecting: %1").arg(e.what()));
        ui->pbConnectRobot->setEnabled(true);
        ui->pbConnectRobot->setText("Connect");
    }
    catch (...)
    {
        QMessageBox::critical(this, tr("Connection Error"), 
                             tr("An unknown error occurred while connecting."));
        ui->pbConnectRobot->setEnabled(true);
        ui->pbConnectRobot->setText("Connect");
    }
}

void RobotWindow::SelectImageProviderOption(int option)
{
    ui->fImageSource->setHidden(true);
    ui->fWebcamSource->setHidden(true);

    QString text = ui->cbSourceForImageProvider->itemText(option);

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    UpdateVariable(prefix + "ImageSource", text);
//    VariableManager::instance().updateVar(prefix + "ImageSource",text);

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
    // Safety check for UI widget
    if (!ui || !ui->pteGcodeArea) {
        QMessageBox::warning(this, "Error", "G-code editor is not available.");
        return;
    }
    
    // ---- Clean Rich Text First -----
    // Get plain text to ensure no rich formatting remains
    QString editorText = ui->pteGcodeArea->toPlainText();
    
    // Clear the editor completely and set plain text to ensure clean state
    ui->pteGcodeArea->clear();
    ui->pteGcodeArea->setPlainText(editorText);
    
    // Reset text formatting to ensure clean state
    QTextCursor cursor = ui->pteGcodeArea->textCursor();
    cursor.select(QTextCursor::Document);
    QTextCharFormat format;
    format.setForeground(QColor("#DBDBDC")); // Set default text color
    cursor.setCharFormat(format);
    cursor.clearSelection();
    ui->pteGcodeArea->setTextCursor(cursor);

    // ---- Number -----
    editorText = ui->pteGcodeArea->toPlainText();

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
    
    // Additional safety check for extremely large content
    if (editorText.length() > 1000000) { // 1MB limit
        QMessageBox::warning(this, "Error", "G-code content is too large to format safely. Please reduce file size.");
        return;
    }

    editorText = "";

    int i = 0;
    const int lineIncrement = 5;  // Make increment configurable
    int actualGcodeLines = 0;     // Track actual G-code lines
    int controlStructureLines = 0; // Track control structure lines (FOR, IF, WHILE, etc.)

    foreach(QString line, lines)
    {
        line = line.trimmed();
        
        // Safety check for empty lines
        if (line.isEmpty()) {
            editorText += "\n";
            continue;
        }
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

        // Safe bounds checking before accessing line[0]
        if (!line.isEmpty() && line[0] == 'N')
        {
            int spacePos = line.indexOf(' ');
            // Validate spacePos before using it
            if (spacePos > 0 && spacePos < line.length()) {
                QString mS = line.mid(0, spacePos + 1);
                oldNumber = line.mid(1, spacePos - 1);  // Fix bounds
                line.replace(mS, "");
                line = line.trimmed(); // Clean any extra spaces after removing number
            }
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

        if (!line.isEmpty())
        {
            // Safe bounds checking before accessing line[0]
            if (!line.isEmpty() && line[0] != ';')
            {
                // Skip lines that are only whitespace or special characters
                QString trimmedCheck = line.trimmed().toUpper();
                if (!trimmedCheck.isEmpty() && 
                    !trimmedCheck.startsWith("(") &&    // Skip parentheses comments
                    !trimmedCheck.startsWith("%") &&    // Skip program markers
                    !trimmedCheck.startsWith("FOR") &&    // Skip FOR loops
                    !trimmedCheck.startsWith("ENDFOR") && // Skip ENDFOR statements
                    !trimmedCheck.startsWith("IF") &&     // Skip IF statements
                    !trimmedCheck.startsWith("ELSE") &&   // Skip ELSE statements  
                    !trimmedCheck.startsWith("ENDIF") &&  // Skip ENDIF statements
                    !trimmedCheck.startsWith("WHILE") &&  // Skip WHILE loops
                    !trimmedCheck.startsWith("ENDWHILE")) // Skip ENDWHILE statements
                {
                    QString numberS = QString("N") + QString::number(i);
                    newNumbers.push_back(QString::number(i));
                    oldNumbers.push_back(oldNumber);
                    line = numberS + " " + line;
                    
                    // Only increment counter for actual G-code lines (not comments)
                    i += lineIncrement;
                    actualGcodeLines++;
                }
                else
                {
                    // Check if this is a control structure line that we're intentionally skipping
                    if (trimmedCheck.startsWith("FOR") || trimmedCheck.startsWith("ENDFOR") ||
                        trimmedCheck.startsWith("IF") || trimmedCheck.startsWith("ELSE") || 
                        trimmedCheck.startsWith("ENDIF") || trimmedCheck.startsWith("WHILE") || 
                        trimmedCheck.startsWith("ENDWHILE"))
                    {
                        controlStructureLines++;
                    }
                }
            }
        }
        else
        {
            // Handle empty lines - don't increment counter
        }

        editorText += line + "\n";
    }

    int gotoCursor = 0;
    gotoCursor = editorText.indexOf("GOTO", gotoCursor);
    
    // Safe GOTO processing with bounds checking and infinite loop prevention
    int maxIterations = 1000; // Prevent infinite loops
    int currentIteration = 0;

    while (gotoCursor > -1 && currentIteration < maxIterations)
    {
        currentIteration++;
        
        //gotoEnd = editorText.indexOf("\n", gotoCursor);
        QString gotoIndexS = "";
        
        // Safe bounds checking for character extraction
        int startPos = gotoCursor + 5; // Position after "GOTO "
        if (startPos >= editorText.length()) {
            break; // Invalid position, exit loop
        }
        
        for (int i = 0; i < 20; i++)
        {
            int charPos = startPos + i;
            if (charPos >= editorText.length()) {
                break; // Prevent out-of-bounds access
            }
            
            QChar c = editorText.at(charPos);
            if (c.isDigit())
                gotoIndexS += c;
            else
                break;
        }

        // Find next GOTO occurrence - safe advancement
        int nextGoto = editorText.indexOf("GOTO", gotoCursor + 4);
        if (nextGoto == gotoCursor) {
            // Same position, force advancement to prevent infinite loop
            nextGoto = editorText.indexOf("GOTO", gotoCursor + 5);
        }
        gotoCursor = nextGoto;

        // Process number replacement only if we found a valid number
        if (!gotoIndexS.isEmpty())
        {
            for (int i = 0; i < oldNumbers.size(); i++)
            {
                if (oldNumbers.at(i).toInt() == gotoIndexS.toInt())
                {
                    QString old = QString("GOTO ") + gotoIndexS;
                    QString replace = QString("GOTO ") + newNumbers.at(i);
                    editorText.replace(old, replace);
                    break; // Exit inner loop after first match
                }
            }
        }
    }
    
    // Warning if we hit max iterations
    if (currentIteration >= maxIterations) {
        QMessageBox::warning(this, "Warning", "G-code formatting reached maximum iterations for GOTO processing. Some GOTO statements may not be updated correctly.");
    }
    
    // Provide user feedback about formatting results
    QString formatSummary = QString("G-code formatting completed:\n")
                          + QString("• Total lines processed: %1\n").arg(lines.size())
                          + QString("• G-code lines numbered: %1\n").arg(actualGcodeLines)
                          + QString("• Control structures skipped: %1\n").arg(controlStructureLines)
                          + QString("• Line increment: %1\n").arg(lineIncrement)
                          + QString("• GOTO processing iterations: %1").arg(currentIteration);
    
    // Show summary in status bar or as tooltip (non-blocking)
    if (this->statusBar()) {
        this->statusBar()->showMessage(
            QString("Formatted %1 G-code lines (skipped %2 control structures) with increment %3")
            .arg(actualGcodeLines)
            .arg(controlStructureLines)
            .arg(lineIncrement), 
            3000); // Show for 3 seconds
    }

    // Set the formatted text as plain text to ensure clean state
    ui->pteGcodeArea->clear();
    ui->pteGcodeArea->setPlainText(editorText);

    // Reset palette to ensure proper text color
    QPalette p = ui->pteGcodeArea->palette();
    p.setColor(QPalette::Text, QColor("#DBDBDC"));
    ui->pteGcodeArea->setPalette(p);

    // Reset document formatting completely to ensure syntax highlighter works properly
    QTextDocument* doc = ui->pteGcodeArea->document();
    QTextCursor docCursor(doc);
    docCursor.select(QTextCursor::Document);
    QTextCharFormat defaultFormat;
    defaultFormat.setForeground(QColor("#DBDBDC"));
    docCursor.setCharFormat(defaultFormat);
    docCursor.clearSelection();

    // Force syntax highlighter to re-highlight the entire document
    if (highlighter) {
        highlighter->rehighlight();
    }
    
    // Move cursor to beginning
    QTextCursor finalCursor = ui->pteGcodeArea->textCursor();
    finalCursor.movePosition(QTextCursor::Start);
    ui->pteGcodeArea->setTextCursor(finalCursor);
}

void RobotWindow::CleanTextFormatting()
{
    // Get current text as plain text
    QString plainText = ui->pteGcodeArea->toPlainText();
    
    // Clear the editor completely and set plain text to ensure clean state
    ui->pteGcodeArea->clear();
    ui->pteGcodeArea->setPlainText(plainText);

    // Reset palette to default colors
    QPalette p = ui->pteGcodeArea->palette();
    p.setColor(QPalette::Text, QColor("#DBDBDC"));
    ui->pteGcodeArea->setPalette(p);
    
    // Reset document formatting completely
    QTextDocument* doc = ui->pteGcodeArea->document();
    QTextCursor docCursor(doc);
    docCursor.select(QTextCursor::Document);
    QTextCharFormat defaultFormat;
    defaultFormat.setForeground(QColor("#DBDBDC"));
    docCursor.setCharFormat(defaultFormat);
    docCursor.clearSelection();
    
    // Force syntax highlighter to re-highlight the entire document
    if (highlighter) {
        highlighter->rehighlight();
    }
    
    // Move cursor to beginning
    QTextCursor finalCursor = ui->pteGcodeArea->textCursor();
    finalCursor.movePosition(QTextCursor::Start);
    ui->pteGcodeArea->setTextCursor(finalCursor);
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
    
    // Load robot settings for the newly selected robot
    LoadRobotSettings();
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
    
    // Save robot DOF setting to VariableManager (only if not loading)
    if (!isLoadingSettings)
    {
        int currentRobotId = ui->cbSelectedRobot->currentIndex();
        QString robotPrefix = ProjectName + ".robot" + QString::number(currentRobotId);
        VariableManager::instance().updateVar(robotPrefix + ".DOF", id);
    }
}

void RobotWindow::ChangeRobotModel(int id)
{
    DeviceManagerInstance->Robots.at(ui->cbSelectedRobot->currentIndex())->SetRobotModel(ui->cbRobotModel->currentText());

    if (id == 0 || id == 1)
    {
        ui->gbX1->setVisible(true);
        ui->gbOutputXS->setVisible(false);
        ui->gbInputXS->setVisible(false);
        ui->gbOutputX3->setVisible(false);
        ui->gbInputX3->setVisible(false);
    }
    else if (id == 2)
    {
        ui->gbX1->setVisible(false);
        ui->gbOutputXS->setVisible(false);
        ui->gbInputXS->setVisible(false);
        ui->gbOutputX3->setVisible(true);
        ui->gbInputX3->setVisible(true);
    }
    else if (id == 3)
    {
        ui->gbX1->setVisible(false);
        ui->gbOutputXS->setVisible(true);
        ui->gbInputXS->setVisible(true);
        ui->gbOutputX3->setVisible(false);
        ui->gbInputX3->setVisible(false);
    }
    
    // Save robot model setting to VariableManager (only if not loading)
    if (!isLoadingSettings)
    {
        int currentRobotId = ui->cbSelectedRobot->currentIndex();
        QString robotPrefix = ProjectName + ".robot" + QString::number(currentRobotId);
        VariableManager::instance().updateVar(robotPrefix + ".Model", id);
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

    IsGcodeEditorTextChanged = false;
}

void RobotWindow::ExecuteProgram()
{
//    SaveProgram();

    if (ui->leZ->text().toFloat() > -200 && ui->pbConnectRobot->text() == "Disconnect")
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

void RobotWindow::ExecuteCurrentLine(int linNumber, QString lineText)
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    GcodeScript* currentScript = GcodeScripts.at(threadId);

    if (ui->cbEditGcodeLock->isChecked() == false)
	{
		return;
	}

    QMetaObject::invokeMethod(currentScript, "ExecuteGcode", Qt::QueuedConnection, Q_ARG(QString, lineText), Q_ARG(int, GcodeScript::BEGIN));

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

void RobotWindow::OnEditorTextChanged()
{
    if (ChangedCounter > 0)
        IsGcodeEditorTextChanged = true;

    ChangedCounter++;
}

void RobotWindow::changeFontSize(int index)
{
    // Lấy nội dung text từ QComboBox
    QString text = ui->cbGScriptEditorZoom->currentText();

    // Loại bỏ dấu % và chuyển thành số nguyên
    text.chop(1);  // Xóa ký tự '%' cuối cùng
    bool ok;
    int percentage = text.toInt(&ok);

    // Nếu chuyển đổi thành công, tính toán tỷ lệ phần trăm
    if (ok) {
        qreal scaleFactor = percentage / 100.0;
        QTextCursor cursor = ui->pteGcodeArea->textCursor();
        ui->pteGcodeArea->selectAll(); // Chọn toàn bộ văn bản
        ui->pteGcodeArea->setFontPointSize(baseFontSize * scaleFactor); // Thay đổi kích thước chữ
        ui->pteGcodeArea->setTextCursor(cursor); // Đặt lại con trỏ văn bản
    }
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
        emit Send(DeviceManager::ROBOT, QString("M03"));
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
        emit Send(DeviceManager::ROBOT, QString("M03"));
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

void RobotWindow::SetOutputX3(bool state)
{
    QString widgetName = sender()->objectName();
    if (widgetName.indexOf("X3D") > -1)
    {
        QString outputName = widgetName.mid(4);

        if (state == true)
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

void RobotWindow::GetInputX3()
{
    QString inputName = sender()->objectName().mid(6, 2);
    QString inputID = inputName.mid(1);
    QCheckBox* cbInputType = (QCheckBox*)getObjectByName(sender()->parent(), QString("cbToggle") + inputID + QString("X3"));
    QLineEdit* leDelay = (QLineEdit*)getObjectByName(sender()->parent(), QString("leA") + inputID + "Delay" + QString("X3"));
    QLineEdit* leInputName;

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
    // Use optimized version
    updateVariableOptimized(key, value);
}

void RobotWindow::UpdateVariables(QString cmd)
{
    if (cmd.isEmpty())
        return;

    QStringList vars = cmd.split(';');
    QHash<QString, QVariant> batchUpdates;

    foreach(QString var, vars)
    {
        var = var.replace(" ", "");
        QStringList paras = var.split('=');
        if (paras.count() < 2)
            continue; // Skip invalid entries instead of returning

        batchUpdates[paras.at(0)] = paras.at(1);
    }

    // Batch update all variables at once
    if (!batchUpdates.isEmpty())
        updateVariablesOptimized(batchUpdates);
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
    QString prefix = getSelectedDevicePrefix("Conveyor");
    updateVariableOptimized(prefix + "ConveyorType", index);

    ui->fConveyorX->setHidden(true);
    ui->fConveyorXHub->setHidden(true);
    ui->fConveyorCustom->setHidden(true);

    ui->leConveyorXAbsolutePosition->setEnabled(false);
//    ui->lbConveyorAbsolutePosition->setEnabled(false);
    ui->lbUnitOfConveyorMoving2->setEnabled(false);
    ui->pbMoveConveyorPosition->setEnabled(false);

    ui->leConveyorXPosition->setEnabled(false);
//    ui->lbConveyorPosition->setEnabled(false);
    ui->lbUnitOfConveyorMoving->setEnabled(false);
    ui->pbMoveConveyorByDistance->setEnabled(false);

    if (index == 0)
    {
        ui->fConveyorX->setHidden(false);

        ui->leConveyorXPosition->setEnabled(true);
//        ui->lbConveyorPosition->setEnabled(true);
        ui->lbUnitOfConveyorMoving->setEnabled(true);
        ui->pbMoveConveyorByDistance->setEnabled(true);
    }
    else if (index == 1)
    {
        ui->fConveyorX->setHidden(false);

        ui->leConveyorXAbsolutePosition->setEnabled(true);
//        ui->lbConveyorAbsolutePosition->setEnabled(true);
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
        emit ChangeDeviceState(ui->cbSelectedEncoder->currentText(), false, "");
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
            emit ChangeDeviceState(ui->cbSelectedEncoder->currentText(), (ui->pbConnectEncoder->text() == "Connect")?true:false, comName);
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
    QString prefix = getSelectedDevicePrefix("Encoder");
    updateVariableOptimized(prefix + "Interval", ui->leEncoderInterval->text());

    int interval = ui->leEncoderInterval->text().toInt();
    int id = ui->cbSelectedEncoder->currentText().toInt();

    if (ui->cbEncoderType->currentText() == "Sub Encoder")
    {
        QString cmd = QString("M421 C%1:%2").arg(id + 1).arg(interval);
        emit Send(DeviceManager::CONVEYOR, cmd);
    }
    if (ui->cbEncoderType->currentText() == "X Encoder")
    {
        if (interval < 0)
            interval = 0;
        emit Send(DeviceManager::ENCODER, QString("M317 T%1").arg(interval));

        if (interval == 0)
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
    QString prefix = ProjectName + "." + ui->cbSelectedEncoder->currentText() + ".";
    UpdateVariable(prefix + "Velocity", ui->leEncoderVelocity->text());
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
    try {
        QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
        
    if (isCheck == true)
    {
            // Check if camera is loaded first
            if (CameraInstance->RunningCamera == -1 && CameraInstance->Source == "Webcam")
            {
                SoftwareLog("Warning: No camera loaded. Please load a camera first.");
                ui->pbStartAcquisition->setChecked(false);
                return;
            }
            
            // Start continuous capture
        ui->lbCameraState->setEnabled(true);
        CameraInstance->IsCameraPause = false;
            
            // Validate capture interval
            int interval = ui->leCaptureInterval->text().toInt();
            if (interval < 10 || interval > 10000)
            {
                interval = 500; // Default to 500ms
                ui->leCaptureInterval->setText("500");
                SoftwareLog("Invalid capture interval, reset to 500ms");
            }
            
            CameraTimer.start(interval);
        UpdateVariable(prefix + "IsOpen", true);
            SoftwareLog(QString("Continuous capture started with %1ms interval").arg(interval));
    }
    else
    {
            // Stop continuous capture
        CameraInstance->IsCameraPause = true;
        CameraTimer.stop();
        UpdateVariable(prefix + "IsOpen", false);
            SoftwareLog("Continuous capture stopped");
        }
        
    } catch (const std::exception& e) {
        SoftwareLog(QString("Error in StartContinuousCapture: %1").arg(e.what()));
        ui->pbStartAcquisition->setChecked(false);
    } catch (...) {
        SoftwareLog("Unknown error in StartContinuousCapture");
        ui->pbStartAcquisition->setChecked(false);
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
    // Debug: Log current button state
    SoftwareLog(QString("LoadWebcam called - Button text: '%1', Checked: %2, isCameraLoaded: %3")
                .arg(ui->pbLoadCamera->text())
                .arg(ui->pbLoadCamera->isChecked() ? "true" : "false")
                .arg(isCameraLoaded ? "true" : "false"));
    
    // Check if camera is currently loaded using internal flag
    if (isCameraLoaded)
    {
        // Stop camera
        SoftwareLog("Stopping camera...");
        
        if (CameraTimer.isActive())
        {
            SoftwareLog("Stopping active camera capture...");
        }
        
        // Call the improved StopCapture function
        StopCapture();
    }
    else
    {
        // Load camera
        SoftwareLog("Loading camera...");

        bool ok;
        int cameraID = CameraSelectionDialog::getCameraID(this, &ok);

        if (ok && cameraID >= 0)
        {
            SoftwareLog(QString("Loading camera %1...").arg(cameraID));

            CameraInstance->RunningCamera = cameraID;
            CameraInstance->Width = ui->leImageWidth->text().toInt();
            CameraInstance->Height = ui->leImageHeight->text().toInt();

            QMetaObject::invokeMethod(CameraInstance, "OpenCamera", Q_ARG(int, cameraID));
            OpenLoadingPopup();

            QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
            UpdateVariable(prefix + "CameraID", cameraID);
        }
        else
        {
            // User cancelled or invalid camera
            ui->pbLoadCamera->setChecked(false);
            CameraInstance->IsCameraPause = false;
            CameraInstance->RunningCamera = -1;
            isCameraLoaded = false;  // Reset internal flag
            
            if (!ok)
            {
                SoftwareLog("Camera selection cancelled");
    }
    else
    {
                SoftwareLog("Invalid camera ID selected");
            }
        }
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
    try {
        // Stop camera timer first
        CameraTimer.stop();
        
        // Update UI state
    ui->lbCameraState->setEnabled(false);
    ui->pbLoadCamera->setText("Load Camera");
    ui->pbStartAcquisition->setChecked(false);

        // Stop different camera types safely
        if (CameraInstance->Source == "Webcam")
        {
            // Thread-safe webcam release
            QMetaObject::invokeMethod(CameraInstance, [this]() {
                if (CameraInstance->WebcamInstance && CameraInstance->WebcamInstance->isOpened())
                {
                    CameraInstance->WebcamInstance->release();
                }
            }, Qt::QueuedConnection);
        }
        else if (CameraInstance->Source == "Industrial Camera")
        {
            // Stop industrial camera if plugin exists
            if (industrialCameraPlugin)
            {
                QMetaObject::invokeMethod(industrialCameraPlugin, "StopCapture", Qt::QueuedConnection);
            }
        }
        
        // Reset camera state
        CameraInstance->RunningCamera = -1;
        CameraInstance->IsCameraPause = false;
        CameraInstance->OriginWidth = 0;
        CameraInstance->OriginHeight = 0;
        isCameraLoaded = false;  // Reset internal flag
        
        // Update settings
    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    UpdateVariable(prefix + "IsOpen", false);
        UpdateVariable(prefix + "CameraID", -1);
        
        // Log the action
        SoftwareLog("Camera stopped successfully");
        
    } catch (const std::exception& e) {
        SoftwareLog(QString("Error stopping camera: %1").arg(e.what()));
    } catch (...) {
        SoftwareLog("Unknown error occurred while stopping camera");
    }
}

void RobotWindow::OpenColorFilterWindow()
{
    ParameterPanel->SetImage(ImageProcessingInstance->GetNode("ColorFilterNode")->GetInputImage());
    ParameterPanel->show();
}

void RobotWindow::SelectObjectDetectingAlgorithm(int algorithm)
{
    ui->fBlobPanel->setHidden(true);
    ui->fExternalScriptPanel->setHidden(true);
    ui->fCirclePanel->setHidden(true);

    QString text = ui->cbDetectingAlgorithm->itemText(algorithm);
    
    // Disconnect all previous connections
    disconnect(ImageProcessingInstance->GetNode("CropImageNode"), SIGNAL(HadOutput(cv::Mat)), ConnectionManager, SLOT(sendImageToImageClients(cv::Mat)));
    disconnect(ImageProcessingInstance->GetNode("ColorFilterNode"), SIGNAL(HadOutput(cv::Mat)), ImageProcessingInstance->GetNode("GetObjectsNode"), SLOT(Input(cv::Mat)));
    disconnect(ImageProcessingInstance->GetNode("ColorFilterNode"), SIGNAL(HadOutput(cv::Mat)), ImageProcessingInstance->GetNode("FindCirclesNode"), SLOT(Input(cv::Mat)));

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    VariableManager::instance().updateVar(prefix + "DetectAlgorithm",text);

    if (text == "Find Blobs")
    {
        ui->fBlobPanel->setHidden(false);
        connect(ImageProcessingInstance->GetNode("ColorFilterNode"), SIGNAL(HadOutput(cv::Mat)), ImageProcessingInstance->GetNode("GetObjectsNode"), SLOT(Input(cv::Mat)));
    }
    if (text == "Find Circles")
    {
        ui->fCirclePanel->setHidden(false);
        connect(ImageProcessingInstance->GetNode("ColorFilterNode"), SIGNAL(HadOutput(cv::Mat)), ImageProcessingInstance->GetNode("FindCirclesNode"), SLOT(Input(cv::Mat)));
        
        // Apply current circle parameters
        UpdateCircleParameters();
    }
    if (text == "External Script")
    {
        ui->fExternalScriptPanel->setHidden(false);
        connect(ImageProcessingInstance->GetNode("CropImageNode"), SIGNAL(HadOutput(cv::Mat)), ConnectionManager, SLOT(sendImageToImageClients(cv::Mat)));
    }
}

void RobotWindow::UpdateCircleParameters()
{
    if (!ImageProcessingInstance || !ImageProcessingInstance->GetNode("FindCirclesNode"))
        return;

    int edgeThreshold = ui->leEdgeThreshold->text().toInt();
    int centerThreshold = ui->leCenterThreshold->text().toInt();
    int minRadius = ui->leMinRadius->text().toInt(); 
    int maxRadius = ui->leMaxRadius->text().toInt();

    // Validate parameters
    if (edgeThreshold <= 0) edgeThreshold = 100;
    if (centerThreshold <= 0) centerThreshold = 30;
    if (minRadius <= 0) minRadius = 10;
    if (maxRadius <= minRadius) maxRadius = minRadius + 50;

    // Apply parameters to FindCirclesNode
    ImageProcessingInstance->GetNode("FindCirclesNode")->Input(edgeThreshold, centerThreshold, minRadius, maxRadius);
    
    // Save parameters to variables
    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    VariableManager::instance().updateVar(prefix + "EdgeThreshold", edgeThreshold);
    VariableManager::instance().updateVar(prefix + "CenterThreshold", centerThreshold);
    VariableManager::instance().updateVar(prefix + "MinRadius", minRadius);
    VariableManager::instance().updateVar(prefix + "MaxRadius", maxRadius);
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
        ChessboardConfigDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted)
        {
            QString text = dialog.getChessboardSize();
            if (!text.isEmpty())
            {
                QStringList paras = text.split("x");
                if (paras.size() == 2)
                {
                    cv::Size size(paras[0].toInt(), paras[1].toInt());

//                    ImageProcessingInstance->GetNode("FindChessboardNode")->Input(size);
                    emit GotChessboardSize(size);

                    emit GotResizeImage(ImageProcessingInstance->GetNode("ResizeImageNode")->GetOutputImage());

                    if (ui->pbWarpTool->isChecked() == false)
                    {
                        ui->gvImageViewer->SelectQuadrangleTool();
                    }
                }
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

    QMatrix matrix = ImageProcessingInstance->GetNode("VisibleObjectsNode")->GetMatrix();
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

        QSize imageSize = ImageProcessingInstance->GetNode("GetImageNode")->GetImageSize();

        int newH = ImageTool::Map(newW, imageSize.width(), imageSize.height());

        ui->leImageHeight->setText(QString::number(newH));

        emit GotResizePara(cv::Size(newW, newH));
    }
    else
    {
        int newH = ui->leImageHeight->text().toInt();

        QSize imageSize = ImageProcessingInstance->GetNode("GetImageNode")->GetImageSize();

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

    TaskNode* cropImageNode = ImageProcessingInstance->GetNode("CropImageNode");
    TaskNode* warpImageNode = ImageProcessingInstance->GetNode("WarpImageNode");

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
        emit ChangeDeviceState(ui->cbSelectedConveyor->currentText(), false, "");
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
            emit ChangeDeviceState(ui->cbSelectedConveyor->currentText(), (ui->pbConveyorConnect->text() == "Connect")?true:false, comName);
        }
    }
}

void RobotWindow::SetConveyorMode(int mode)
{
    QString prefix = ProjectName + "." + ui->cbSelectedConveyor->currentText() + ".";
    UpdateVariable(prefix + "ConveyorMode", mode);

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
    QString prefix = ProjectName + "." + ui->cbSelectedConveyor->currentText() + ".";
    UpdateVariable(prefix + "ConveyorSpeed", ui->leConveyorXSpeed->text());

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

void RobotWindow::StopConveyor()
{
    ui->leConveyorXSpeed->setText("0");
    SetConveyorSpeed();
}

void RobotWindow::ForwardConveyor()
{
    float speed = ui->leConveyorXSpeed->text().toFloat();
    if (speed == 0)
    {
        speed = 50;
    }

    speed = abs(speed);
    ui->leConveyorXSpeed->setText(QString::number(speed));

    SetConveyorSpeed();
}

void RobotWindow::BackwardConveyor()
{
    float speed = ui->leConveyorXSpeed->text().toFloat();
    if (speed == 0)
    {
        ui->leConveyorXSpeed->setText("50");
        speed = 50;
    }

    speed = abs(speed) * -1;

    ui->leConveyorXSpeed->setText(QString::number(speed));
    SetConveyorSpeed();
}

void RobotWindow::SetConveyorPosition()
{
    QString prefix = ProjectName + "." + ui->cbSelectedConveyor->currentText() + ".";
    UpdateVariable(prefix + "ConveyorPosition", ui->leConveyorXPosition->text());

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
    QString prefix = ProjectName + "." + ui->cbSelectedConveyor->currentText() + ".";
    UpdateVariable(prefix + "ConveyorAbsolutePosition", ui->leConveyorXAbsolutePosition->text());

    if (ui->cbConveyorType->currentText() == "X Conveyor")
    {
        emit Send(DeviceManager::CONVEYOR, QString("M312 ") + ui->leConveyorXAbsolutePosition->text());
    }
}

void RobotWindow::TriggedCustomConveyor()
{
    QObject *senderObj = sender(); // Lấy đối tượng kích hoạt

    if (qobject_cast<QPushButton*>(senderObj) == ui->pbStartCustomConveyor1 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStartCustomConveyor1Command)
    {
        QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, ui->pbStartCustomConveyor1Command->text()));

    }
    else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStartCustomConveyor2 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStartCustomConveyor2Command)
    {
        QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, ui->pbStartCustomConveyor2Command->text()));
    }
    else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStartCustomConveyor3 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStartCustomConveyor3Command)
    {
        QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, ui->pbStartCustomConveyor3Command->text()));
    }
    if (qobject_cast<QPushButton*>(senderObj) == ui->pbStopCustomConveyor1 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStopCustomConveyor1Command)
    {
        QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, ui->pbStopCustomConveyor1Command->text()));

    } else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStopCustomConveyor2 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStopCustomConveyor2Command)
    {
        QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, ui->pbStopCustomConveyor2Command->text()));
    } else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStopCustomConveyor3 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStopCustomConveyor3Command)
    {
        QMetaObject::invokeMethod(DeviceManagerInstance, "GetCommand", Qt::QueuedConnection, Q_ARG(QString, ui->pbStopCustomConveyor1Command->text()));
    }
}

void RobotWindow::ProcessShortcutKey()
{

}

void RobotWindow::ChangeEncoderType(int index)
{
    QString prefix = ProjectName + "." + ui->cbSelectedEncoder->currentText() + ".";
    UpdateVariable(prefix + "EncoderType", index);

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

void RobotWindow::ChangeConveyorLinkToEncoder(int state)
{
    QString prefix = ProjectName + "." + ui->cbSelectedEncoder->currentText() + ".";
    UpdateVariable(prefix + "ConveyorLinkToEncoder", state);

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
}

/*!
After software send image to external script. AI will detect objects and send info back to software
 */

void RobotWindow::AddDisplayObjectFromExternalScript(QString msg)
{
    if (msg == "\n")
        return;

    QStringList objectInfos = msg.split(";");

    QVector<Object> Objects;

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

void RobotWindow::SaveTrackingManager()
{
    int selectedEncoderID = ui->cbSelectedTracking->currentText().toInt();

    TrackingManagerInstance->Trackings.at(selectedEncoderID)->VelocityVector = VariableManager::instance().getVar(ui->leVelocityVector->text()).value<QVector3D>();
    TrackingManagerInstance->Trackings.at(selectedEncoderID)->VectorName = ui->leVectorName->text();
}

void RobotWindow::CalculateMappingMatrixTool()
{
    if (m_pointToolController) {
        m_pointToolController->calculateMappingMatrix();
    }
}

void RobotWindow::CalculatePointMatrixTool()
{
    if (m_pointToolController) {
        m_pointToolController->calculatePerspectiveMatrix();
    }
}

void RobotWindow::CalculateTestPoint()
{
    if (m_pointToolController) {
        m_pointToolController->calculateTestPoint();
    }
}

void RobotWindow::CalculateVector()
{
    if (m_pointToolController) {
        m_pointToolController->calculateVector();
    }
}

void RobotWindow::UpdateTestPoint(QVector3D testPoint)
{
    if (m_pointToolController) {
        m_pointToolController->updateTestPoint(testPoint);
    }
}

void RobotWindow::MoveTestTrackingPoint()
{
    if (m_pointToolController) {
        m_pointToolController->moveTestTrackingPoint();
    }
}

void RobotWindow::ProcessProximitySensorValue(int value)
{

}

void RobotWindow::StartScheduledEncoder()
{
    if (ui->pbStartScheduledEncoder->text() == "Start")
    {
        scheduledStartEncoderValue = ui->leEncoderCurrentPosition->text().toFloat();
        isScheduledEncoder = true;
        ui->pbStartScheduledEncoder->setText("Stop");
    }
    else
    {
        isScheduledEncoder = false;
        ui->pbStartScheduledEncoder->setText("Start");
    }

}

void RobotWindow::ConnectSliding()
{
    if (ui->pbSlidingConnect->text() != "Connect")
    {
        emit ChangeDeviceState(ui->cbSelectedSlider->currentText(), false, "");
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
            emit ChangeDeviceState(ui->cbSelectedSlider->currentText(), (ui->pbSlidingConnect->text() == "Connect")?true:false, comName);
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
        emit ChangeDeviceState(ui->cbSelectedDevice->currentText(), false, "");
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
            emit ChangeDeviceState(ui->cbSelectedDevice->currentText(), (ui->pbExternalControllerConnect->text() == "Connect")?true:false, comName);
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
    // Kiểm tra button state để quyết định action
    if (ui->pbRunExternalScript->isChecked()) {
        // Button được check - start Python script
        QString pythonPath = ui->lePythonUrl->text();
        
        if (pythonPath.isEmpty()) {
            // Không có path, uncheck button
            ui->pbRunExternalScript->setChecked(false);
            qDebug() << "No Python script path specified";
            return;
        }
        
        runPythonFile(pythonPath);
    } else {
        // Button được uncheck - stop Python script
        if (process != nullptr && process->state() == QProcess::Running) {
            qDebug() << "Stopping Python script...";
            
            process->terminate();
            
            // Đợi process terminate, nếu không thành công thì kill
            if (!process->waitForFinished(3000)) { // Đợi 3 giây
                process->kill();
                process->waitForFinished(1000); // Đợi thêm 1 giây cho kill
            }
            
            qDebug() << "Python script stopped";
        }
    }
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
        ui->pbLoadCamera->setChecked(true);  // Set button to checked state
        isCameraLoaded = true;  // Set internal flag

        // ui->leImageWidth->setText(QString::number(CameraInstance->Width));
        // ui->leImageHeight->setText(QString::number(CameraInstance->Height));

        QTimer::singleShot(2000, this, [this]() {
            ui->leImageWidth->returnPressed();
        });

        // Log the resolution being used
        SoftwareLog(QString("Camera resolution set to: %1x%2").arg(CameraInstance->Width).arg(CameraInstance->Height));

        ui->pbStartAcquisition->setChecked(true);
        ui->pbStartAcquisition->clicked(true);

        SoftwareLog("Camera connected and ready to capture");
    }
    else
    {
        // Camera failed to connect
        ui->pbLoadCamera->setText("Load Camera");
        ui->pbLoadCamera->setChecked(false);
        isCameraLoaded = false;  // Reset internal flag
        
        SoftwareLog("Camera connection failed");
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


  QListWidgetItem* item = new QListWidgetItem(ui->lwImageList);
  // Tách tên ảnh từ fileName
    QString imageName = QFileInfo(fileName).fileName();
  item->setText(imageName);
  item->setData(Qt::UserRole, fileName);
  QPixmap pixmap(fileName);
  item->setIcon(pixmap.scaled(QSize(64, 64), Qt::KeepAspectRatio));

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

    // Hiển thị ảnh từ imagePath trên cửa sổ ImageLabel, 
    // khi người dùng chọn một ảnh khác thì ảnh được load vào cửa sổ đó
    // Khi người dùng tắt thì xóa cửa sổ đó


    if (ImageLabel == NULL)
    {
        ImageLabel = new QLabel();
        ImageLabel->setWindowTitle("Image Viewer");
        ImageLabel->setAttribute(Qt::WA_DeleteOnClose);
        ImageLabel->show();
    }

    ImageLabel->hide();

    ImageLabel->setPixmap(QPixmap(imagePath));
    // Chỉnh cửa sổ ImageLabel sao cho vừa với ảnh
    ImageLabel->adjustSize();
    //Hiển thị cửa sổ ImageLabel (QLabel) trên cửa sổ chính
    ImageLabel->show();;
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

void RobotWindow::pastePointValues(QLineEdit *lePoint)
{
    QString x = ui->leX->text();
    QString y = ui->leY->text();
    QString z = ui->leZ->text();

    // convert x, y z to text "x,y,z"
    QString pointText = QString("%1, %2, %3").arg(x).arg(y).arg(z);
    lePoint->setText(pointText);
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
    
    // Trích xuất IP và port từ UI
    QStringList ipAndPort = ui->leIP->text().split(":");
    if (ipAndPort.size() >= 2) {
        QString host = ipAndPort.at(0);
        QString port = ipAndPort.at(1);
        
        // Thêm các tham số cho Python script
        arguments << "-ip" << host;
        arguments << "-port" << port;
        
        // Thêm image source type
        if (ui->cbImageSource) {
            QString imageSource = ui->cbImageSource->currentText();
            arguments << "-type" << imageSource;
        }
        
        // Thêm model path - tự động detect từ project folder hoặc setting
        QString modelPath = getModelPath();
        if (!modelPath.isEmpty()) {
            arguments << "-model" << modelPath;
        }
        
        // Thêm object dimensions nếu có trong UI
        if (ui->leWRec && ui->leLRec) {
            QString objectWidth = ui->leWRec->text();
            QString objectHeight = ui->leLRec->text();
            if (!objectWidth.isEmpty() && !objectHeight.isEmpty()) {
                arguments << "-ow" << objectWidth;
                arguments << "-oh" << objectHeight;
            }
        }
        
        // Thêm project name
        arguments << "-project" << ProjectName;
        
        qDebug() << "Running Python script with arguments:" << arguments;
    }

    // Kiểm tra đường dẫn tương đối hay tuyệt đối
    QFileInfo fileInfo(filePath);
    if (!fileInfo.isAbsolute()) {
        QDir dir(QCoreApplication::applicationDirPath());
        filePath = dir.absoluteFilePath(filePath);
    }

    // Nếu quá trình chạy file python đã tồn tại thì tắt nó
    if (process != nullptr && process->state() == QProcess::Running) {
        process->terminate();
        
        // Đợi process terminate, nếu không thành công thì kill
        if (!process->waitForFinished(3000)) { // Đợi 3 giây
            process->kill();
            process->waitForFinished(1000); // Đợi thêm 1 giây cho kill
        }
        
        // Cleanup process cũ
        process->deleteLater();
        process = nullptr;
    }

    // Cleanup process cũ nếu nó đã finished
    if (process != nullptr && process->state() == QProcess::NotRunning) {
        process->deleteLater();
        process = nullptr;
    }

    // Tạo quá trình mới để chạy file python
    process = new QProcess(this); // Set parent để tự động cleanup
    
    // Connect signals để theo dõi process state
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                qDebug() << "Python script finished with exit code:" << exitCode;
                
                // Update button state if needed
                if (ui->pbRunExternalScript->isChecked()) {
                    ui->pbRunExternalScript->setChecked(false);
                }
            });
    
    connect(process, QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
            [=](QProcess::ProcessError error) {
                qDebug() << "Python process error:" << error;
                
                // Update button state
                if (ui->pbRunExternalScript->isChecked()) {
                    ui->pbRunExternalScript->setChecked(false);
                }
            });
    
    process->start(pythonExePath, arguments);
    
    // Kiểm tra xem process có start thành công không
    if (!process->waitForStarted(5000)) { // Đợi 5 giây
        qDebug() << "Failed to start Python script:" << process->errorString();
        
        // Update button state
        if (ui->pbRunExternalScript->isChecked()) {
            ui->pbRunExternalScript->setChecked(false);
        }
        
        process->deleteLater();
        process = nullptr;
    } else {
        qDebug() << "Python script started successfully";
    }
}

QString RobotWindow::getModelPath()
{
    // 1. Kiểm tra từ setting trước
    QSettings settings;
    QString savedModelPath = settings.value("ExternalScript/ModelPath", "").toString();
    if (!savedModelPath.isEmpty() && QFile::exists(savedModelPath)) {
        return savedModelPath;
    }
    
    // 2. Tự động detect từ project folder
    QStringList possiblePaths = {
        "models/best.pt",           // Relative to app directory
        "models/yolov8n.pt",        // Common YOLO model
        "models/model.pt",          // Generic model name
        "script-example/best.pt",   // In script example folder
        "../models/best.pt",        // Parent directory
        "./best.pt"                 // Current directory
    };
    
    QString appDirPath = QCoreApplication::applicationDirPath();
    
    for (const QString& relativePath : possiblePaths) {
        QString fullPath = QDir(appDirPath).absoluteFilePath(relativePath);
        if (QFile::exists(fullPath)) {
            qDebug() << "Found model at:" << fullPath;
            return fullPath;
        }
    }
    
    // 3. Fallback - return empty hoặc default path
    qDebug() << "No model file found, using default path";
    return "models/best.pt"; // Default fallback
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

    QVector<Object> objects;

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

//    qDebug() << "var" << elapse.elapsed();
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

    // Get actual image size from CaptureImage to ensure accuracy
    int width = 0;
    int height = 0;
    
    // Add null check for CameraInstance to prevent memory access violation
    if (CameraInstance != nullptr)
    {
        if (!CameraInstance->CaptureImage.empty())
        {
            width = CameraInstance->CaptureImage.cols;
            height = CameraInstance->CaptureImage.rows;
        }
        else
        {
            // Fallback to stored origin size if CaptureImage is empty
            width = CameraInstance->OriginWidth;
            height = CameraInstance->OriginHeight;
        }
    }
    
    float ratio = ui->gvImageViewer->GetRatio() * 100;
    ui->lbMatSize->setText(QString("Original: %1x%2").arg(width).arg(height));
    ui->lbDisplayRatio->setText(QString("Ratio: %1%").arg(ratio));

    if (ui->cbAutoUpdateObjectsDisplay->currentIndex() == 1)
    {
        UpdateObjectsToView();
    }
}

void RobotWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event); // Gọi hàm cơ bản

//    int elapsed = performanceTimer.elapsed(); // Lấy thời gian đã trôi qua từ lần cuối
//    qDebug() << "Thời gian giữa hai lần gọi paintEvent:" << elapsed << "milliseconds";
//    performanceTimer.restart(); // Khởi động lại timer cho lần gọi kế tiếp
}

void RobotWindow::SaveDetectingUI()
{
    QString prefix = getSelectedDevicePrefix("Detecting");
    QHash<QString, QVariant> updates;
    updates["ResizeWidth"] = ui->leImageWidth->text();
    updates["ResizeHeight"] = ui->leImageHeight->text();
    
    batchUpdateVariables(prefix, updates);
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
    int successCount = 0;
    QStringList failedPlugins;
    
    foreach (QString file, plugins)
    {
        QFileInfo fileInfo(file);
        QString pluginName = fileInfo.baseName();
        
        qDebug() << "Loading plugin:" << pluginName;
        
        QPluginLoader loader(file);
        if (!loader.load())
        {
            QString error = QString("Failed to load plugin '%1': %2")
                           .arg(pluginName)
                           .arg(loader.errorString());
            
            qWarning() << error;
            failedPlugins << pluginName;
            continue;
        }

        DeltaXPlugin* pluginWidget = qobject_cast<DeltaXPlugin*>(loader.instance());
        if (!pluginWidget)
        {
            QString error = QString("Plugin '%1' does not implement DeltaXPlugin interface").arg(pluginName);
            qWarning() << error;
            failedPlugins << pluginName;
            continue;
        }

        // ✅ Safe UI creation with validation
        QWidget* pluginUI = nullptr;
        try {
            pluginUI = pluginWidget->GetUI();
        } catch (const std::exception& e) {
            qWarning() << "Exception creating UI for plugin" << pluginWidget->GetName() << ":" << e.what();
            failedPlugins << pluginWidget->GetName();
            continue;
        } catch (...) {
            qWarning() << "Unknown exception creating UI for plugin" << pluginWidget->GetName();
            failedPlugins << pluginWidget->GetName();
            continue;
        }
        
        if (!pluginUI)
        {
            qWarning() << "Plugin" << pluginWidget->GetName() << "returned null UI";
            failedPlugins << pluginWidget->GetName();
            continue;
        }

        // ✅ Success - add plugin safely
        QString pluginTitle = pluginWidget->GetTitle();
        if (pluginTitle.isEmpty()) {
            pluginTitle = pluginWidget->GetName(); // Fallback to name
        }
        
        ui->twModule->addTab(pluginUI, pluginTitle);
        pluginList->append(pluginWidget);
        
        // ✅ Connect plugin signals safely
        connectPluginSignals(pluginWidget);
        
        successCount++;
        qInfo() << "Successfully loaded plugin:" << pluginWidget->GetName();
        SoftwareLog(QString("Successfully loaded plugin: %1").arg(pluginWidget->GetName()));
    }
    
    // ✅ User feedback
    if (successCount > 0) {
        qInfo() << QString("Successfully loaded %1 plugins").arg(successCount);
        SoftwareLog(QString("Plugin System: Successfully loaded %1 plugins").arg(successCount));
    }
    
    if (!failedPlugins.isEmpty()) {
        QString failedList = failedPlugins.join(", ");
        qWarning() << QString("Failed to load plugins: %1").arg(failedList);
        
        // ✅ Log failed plugins to software debug (no popup)
        if (failedPlugins.size() > 0) {
            SoftwareLog(QString("Plugin Loading Warning: Failed to load plugins: %1")
                       .arg(failedList));
        }
    }
}

QList<DeltaXPlugin*> *RobotWindow::getPluginList()
{
    return pluginList;
}

// ✅ Safe plugin signal connection
void RobotWindow::connectPluginSignals(DeltaXPlugin* plugin)
{
    if (!plugin) {
        qWarning() << "Cannot connect signals for null plugin";
        return;
    }
    
    QString pluginName = plugin->GetName();
    qDebug() << "Connecting signals for plugin:" << pluginName;
    
    try {
        if (pluginName == "industrialcamera") {
            industrialCameraPlugin = plugin;
            
            // Connect plugin to camera system
            connect(plugin, &DeltaXPlugin::CapturedImage, 
                    CameraInstance, &Camera::GetImageFromExternal);
            connect(CameraInstance, &Camera::RequestCapture, 
                    plugin, &DeltaXPlugin::RequestCapture);
            
            qDebug() << "Connected IndustrialCamera plugin signals";
            SoftwareLog("Plugin System: Connected IndustrialCamera plugin signals");
        }
        // Add other plugin connections here as needed
        
    } catch (const std::exception& e) {
        qWarning() << "Exception connecting signals for plugin" << pluginName << ":" << e.what();
    } catch (...) {
        qWarning() << "Unknown exception connecting signals for plugin" << pluginName;
    }
}

// ✅ Find plugin by name safely
DeltaXPlugin* RobotWindow::findPluginByName(const QString& name)
{
    if (!pluginList || name.isEmpty()) {
        return nullptr;
    }
    
    for (int i = 0; i < pluginList->count(); i++) {
        DeltaXPlugin* plugin = pluginList->at(i);
        if (plugin && plugin->GetName().compare(name, Qt::CaseInsensitive) == 0) {
            return plugin;
        }
    }
    
    return nullptr;
}

// ===========================================
// OPTIMIZED VARIABLE MANAGEMENT METHODS
// ===========================================

QString RobotWindow::getDevicePrefix(const QString& deviceType, int id) const
{
    QString key = deviceType + QString::number(id);
    return getCachedPrefix(key);
}

QString RobotWindow::getSelectedDevicePrefix(const QString& deviceType) const
{
    QString deviceName;
    if (deviceType == "Conveyor")
        deviceName = ui->cbSelectedConveyor->currentText();
    else if (deviceType == "Encoder")
        deviceName = ui->cbSelectedEncoder->currentText();
    else if (deviceType == "Detecting")
        deviceName = ui->cbSelectedDetecting->currentText();
    else if (deviceType == "Tracking")
        deviceName = ui->cbSelectedTracking->currentText();
    else
        deviceName = deviceType;

    QString key = deviceType + "_" + deviceName;
    return getCachedPrefix(key);
}

QString RobotWindow::getCachedPrefix(const QString& key) const
{
    if (m_prefixCache.contains(key))
        return m_prefixCache[key];

    QString prefix = ProjectName + "." + key + ".";
    m_prefixCache[key] = prefix;
    return prefix;
}

void RobotWindow::updateVariableOptimized(const QString& key, const QVariant& value)
{
    if (key.isEmpty())
        return;

    // Add to pending updates for batching
    m_pendingUpdates[key] = value;
    scheduleBatchUpdate();
}

void RobotWindow::updateVariablesOptimized(const QHash<QString, QVariant>& variables)
{
    if (variables.isEmpty())
        return;

    // Add all to pending updates
    for (auto it = variables.begin(); it != variables.end(); ++it)
    {
        m_pendingUpdates[it.key()] = it.value();
    }
    scheduleBatchUpdate();
}

void RobotWindow::batchUpdateVariables(const QString& prefix, const QHash<QString, QVariant>& variables)
{
    if (variables.isEmpty())
        return;

    for (auto it = variables.begin(); it != variables.end(); ++it)
    {
        QString fullKey = prefix + it.key();
        m_pendingUpdates[fullKey] = it.value();
    }
    scheduleBatchUpdate();
}

QVariant RobotWindow::getVariableOptimized(const QString& key, const QVariant& defaultValue) const
{
    if (key.isEmpty())
        return defaultValue;

    return m_variableManager->getVar(key, defaultValue);
}

void RobotWindow::scheduleBatchUpdate()
{
    if (!m_batchUpdateTimer->isActive())
        m_batchUpdateTimer->start();
}

void RobotWindow::processBatchUpdates()
{
    if (m_pendingUpdates.isEmpty())
        return;

    // Process all pending updates in one batch
    for (auto it = m_pendingUpdates.begin(); it != m_pendingUpdates.end(); ++it)
    {
        m_variableManager->updateVar(it.key(), it.value());
    }

    m_pendingUpdates.clear();
}

void RobotWindow::flushPendingUpdates()
{
    if (m_batchUpdateTimer->isActive())
        m_batchUpdateTimer->stop();
    processBatchUpdates();
}



// ===========================================
// OBJECT TABLE CONTEXT MENU METHODS
// ===========================================

void RobotWindow::initObjectTableContextMenu()
{
    // Set context menu policy for table view
    ui->tvObjectTable->setContextMenuPolicy(Qt::CustomContextMenu);
    
    // Connect context menu signal
    connect(ui->tvObjectTable, &QTableView::customContextMenuRequested, 
            this, &RobotWindow::showObjectTableContextMenu);
    
    // Create context menu actions
    actionCopyCellValue = new QAction("Copy Cell Value", this);
    actionCopyCellValue->setShortcut(QKeySequence::Copy);
    connect(actionCopyCellValue, &QAction::triggered, this, &RobotWindow::copyCellValue);
    
    actionCopyRowData = new QAction("Copy Row Data", this);
    actionCopyRowData->setShortcut(QKeySequence("Ctrl+Shift+C"));
    connect(actionCopyRowData, &QAction::triggered, this, &RobotWindow::copyRowData);
    
    actionGoToObject = new QAction("Go to Object", this);
    actionGoToObject->setShortcut(QKeySequence("Ctrl+G"));
    connect(actionGoToObject, &QAction::triggered, this, &RobotWindow::goToObject);
    
    actionTogglePickedStatus = new QAction("Toggle Picked Status", this);
    actionTogglePickedStatus->setShortcut(QKeySequence("Ctrl+P"));
    connect(actionTogglePickedStatus, &QAction::triggered, this, &RobotWindow::togglePickedStatus);
    
    actionDeleteObject = new QAction("Delete Object", this);
    actionDeleteObject->setShortcut(QKeySequence::Delete);
    connect(actionDeleteObject, &QAction::triggered, this, &RobotWindow::deleteObject);
    
    actionShowObjectDetails = new QAction("Show Details", this);
    actionShowObjectDetails->setShortcut(QKeySequence("Ctrl+I"));
    connect(actionShowObjectDetails, &QAction::triggered, this, &RobotWindow::showObjectDetails);
    
    actionExportObjectData = new QAction("Export Object Data", this);
    actionExportObjectData->setShortcut(QKeySequence("Ctrl+E"));
    connect(actionExportObjectData, &QAction::triggered, this, &RobotWindow::exportObjectData);
    
    // Add actions to table view for keyboard shortcuts
    ui->tvObjectTable->addAction(actionCopyCellValue);
    ui->tvObjectTable->addAction(actionCopyRowData);
    ui->tvObjectTable->addAction(actionGoToObject);
    ui->tvObjectTable->addAction(actionTogglePickedStatus);
    ui->tvObjectTable->addAction(actionDeleteObject);
    ui->tvObjectTable->addAction(actionShowObjectDetails);
    ui->tvObjectTable->addAction(actionExportObjectData);
}

void RobotWindow::showObjectTableContextMenu(const QPoint& pos)
{
    QModelIndex index = ui->tvObjectTable->indexAt(pos);
    if (!index.isValid())
        return;
    
    // Store the context menu index for use in actions
    contextMenuIndex = index;
    
    // Create and show context menu
    QMenu contextMenu(this);
    
    // Add actions to menu
    contextMenu.addAction(actionCopyCellValue);
    contextMenu.addAction(actionCopyRowData);
    contextMenu.addSeparator();
    contextMenu.addAction(actionGoToObject);
    contextMenu.addAction(actionTogglePickedStatus);
    contextMenu.addSeparator();
    contextMenu.addAction(actionDeleteObject);
    contextMenu.addSeparator();
    contextMenu.addAction(actionShowObjectDetails);
    contextMenu.addAction(actionExportObjectData);
    
    // Update action states based on selection
    bool hasSelection = index.isValid();
    actionCopyCellValue->setEnabled(hasSelection);
    actionCopyRowData->setEnabled(hasSelection);
    actionGoToObject->setEnabled(hasSelection);
    actionTogglePickedStatus->setEnabled(hasSelection);
    actionDeleteObject->setEnabled(hasSelection);
    actionShowObjectDetails->setEnabled(hasSelection);
    actionExportObjectData->setEnabled(hasSelection);
    
    // Show context menu
    contextMenu.exec(ui->tvObjectTable->mapToGlobal(pos));
}

void RobotWindow::copyCellValue()
{
    if (!contextMenuIndex.isValid())
        return;
    
    QVariant data = ObjectModel->data(contextMenuIndex);
    QString text = data.toString();
    
    QApplication::clipboard()->setText(text);
    
    // Show status message
    UpdateTermite(QString("Copied cell value: %1").arg(text));
}

void RobotWindow::copyRowData()
{
    if (!contextMenuIndex.isValid())
        return;
    
    int row = contextMenuIndex.row();
    QStringList rowData;
    
    // Get data from all columns in the row
    for (int col = 0; col < ObjectModel->columnCount(); ++col)
    {
        QModelIndex index = ObjectModel->index(row, col);
        QVariant data = ObjectModel->data(index);
        rowData << data.toString();
    }
    
    // Create formatted string
    QString text = rowData.join("\t"); // Tab-separated for easy pasting into spreadsheet
    
    QApplication::clipboard()->setText(text);
    
    // Show status message
    UpdateTermite(QString("Copied row data: %1 values").arg(rowData.size()));
}

void RobotWindow::goToObject()
{
    if (!contextMenuIndex.isValid())
        return;
    
    int row = contextMenuIndex.row();
    
    // Get object coordinates
    QModelIndex xIndex = ObjectModel->index(row, 2); // X column
    QModelIndex yIndex = ObjectModel->index(row, 3); // Y column
    QModelIndex angleIndex = ObjectModel->index(row, 7); // Angle column
    
    if (!xIndex.isValid() || !yIndex.isValid() || !angleIndex.isValid())
        return;
    
    float x = ObjectModel->data(xIndex).toFloat();
    float y = ObjectModel->data(yIndex).toFloat();
    float angle = ObjectModel->data(angleIndex).toFloat();
    
    // Move robot to object position
    MoveRobotFollowObject(x, y, angle);
    
    // Show status message
    UpdateTermite(QString("Moving to object at position: X=%1, Y=%2, Angle=%3").arg(x).arg(y).arg(angle));
}

void RobotWindow::togglePickedStatus()
{
    if (!contextMenuIndex.isValid())
        return;
    
    int row = contextMenuIndex.row();
    QModelIndex pickedIndex = ObjectModel->index(row, 8); // Is Picked column
    
    if (!pickedIndex.isValid())
        return;
    
    bool currentStatus = ObjectModel->data(pickedIndex).toBool();
    bool newStatus = !currentStatus;
    
    // Update the model (assuming ObjectInfoModel has a method to update picked status)
    // This would require adding a method to ObjectInfoModel to modify data
    // For now, we'll just show a message
    
    QString statusText = newStatus ? "Picked" : "Not Picked";
    UpdateTermite(QString("Object %1 status changed to: %2").arg(row).arg(statusText));
    
    // TODO: Implement actual status update in ObjectInfoModel
    // ObjectModel->setData(pickedIndex, newStatus);
}

void RobotWindow::deleteObject()
{
    if (!contextMenuIndex.isValid())
        return;
    
    int row = contextMenuIndex.row();
    
    // Show confirmation dialog
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Delete Object");
    msgBox.setText(QString("Are you sure you want to delete object at row %1?").arg(row + 1));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    
    if (msgBox.exec() == QMessageBox::Yes)
    {
        // Emit signal to delete object
        emit RequestDeleteObject(row);
        
        UpdateTermite(QString("Object %1 deleted").arg(row + 1));
    }
}

void RobotWindow::showObjectDetails()
{
    if (!contextMenuIndex.isValid())
        return;
    
    int row = contextMenuIndex.row();
    
    // Get all object data
    QStringList details;
    QStringList headers;
    
    // Get headers
    for (int col = 0; col < ObjectModel->columnCount(); ++col)
    {
        headers << ObjectModel->headerData(col, Qt::Horizontal).toString();
    }
    
    // Get row data
    for (int col = 0; col < ObjectModel->columnCount(); ++col)
    {
        QModelIndex index = ObjectModel->index(row, col);
        QVariant data = ObjectModel->data(index);
        details << QString("%1: %2").arg(headers[col]).arg(data.toString());
    }
    
    // Show details dialog
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(QString("Object Details - Row %1").arg(row + 1));
    msgBox.setText(details.join("\n"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void RobotWindow::exportObjectData()
{
    if (!contextMenuIndex.isValid())
        return;
    
    // Get save file path
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Export Object Data", 
        QString("object_data_%1.csv").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")),
        "CSV Files (*.csv);;Text Files (*.txt)");
    
    if (fileName.isEmpty())
        return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Export Error", "Could not open file for writing.");
        return;
    }
    
    QTextStream stream(&file);
    
    // Write headers
    QStringList headers;
    for (int col = 0; col < ObjectModel->columnCount(); ++col)
    {
        headers << ObjectModel->headerData(col, Qt::Horizontal).toString();
    }
    stream << headers.join(",") << "\n";
    
    // Write all rows
    for (int row = 0; row < ObjectModel->rowCount(); ++row)
    {
        QStringList rowData;
        for (int col = 0; col < ObjectModel->columnCount(); ++col)
        {
            QModelIndex index = ObjectModel->index(row, col);
            QVariant data = ObjectModel->data(index);
            rowData << data.toString();
        }
        stream << rowData.join(",") << "\n";
    }
    
    file.close();
    
    UpdateTermite(QString("Object data exported to: %1").arg(fileName));
}

void RobotWindow::Jogging(QString direction, bool isMove)
{
    float step = RobotParameters[RbID].Step;
    if (isMove == false)
    {
        step = 0;
    }

    if (direction.contains("left"))
    {
        //format: jogging (step, 0, 0)
        emit Send(DeviceManager::ROBOT, QString("jogging (%1, 0, 0)").arg(-step));
    }
    else if (direction.contains("right"))
    {
        emit Send(DeviceManager::ROBOT, QString("jogging (%1, 0, 0)").arg(step));
    }
    else if (direction.contains("forward"))
    {
        emit Send(DeviceManager::ROBOT, QString("jogging (0, %1, 0)").arg(step));
    }
    else if (direction.contains("backward"))
    {
        emit Send(DeviceManager::ROBOT, QString("jogging (0, %1, 0)").arg(-step));
    }
    else if (direction.contains("up"))
    {
        emit Send(DeviceManager::ROBOT, QString("jogging (0, 0, %1)").arg(step));
    }
    else if (direction.contains("down"))
    {
        emit Send(DeviceManager::ROBOT, QString("jogging (0, 0, %1)").arg(-step));
    }
}

// ===============================================================
// Z-PLANE LIMITING IMPLEMENTATIONS
// ===============================================================

void RobotWindow::onGetCurrentPositionP1() {
    if (!ui || !m_pointToolController) return;
    
    // Use PointToolController to set current robot position to P1 inputs
    m_pointToolController->setCurrentRobotPosition(
        ui->leZPlaneP1X, 
        ui->leZPlaneP1Y, 
        ui->leZPlaneP1Z
    );
    
    SoftwareLog("Z-Plane: Set current robot position to Point 1");
}

void RobotWindow::onGetCurrentPositionP2() {
    if (!ui || !m_pointToolController) return;
    
    // Use PointToolController to set current robot position to P2 inputs
    m_pointToolController->setCurrentRobotPosition(
        ui->leZPlaneP2X, 
        ui->leZPlaneP2Y, 
        ui->leZPlaneP2Z
    );
    
    SoftwareLog("Z-Plane: Set current robot position to Point 2");
}

void RobotWindow::onGetCurrentPositionP3() {
    if (!ui || !m_pointToolController) return;
    
    // Use PointToolController to set current robot position to P3 inputs
    m_pointToolController->setCurrentRobotPosition(
        ui->leZPlaneP3X, 
        ui->leZPlaneP3Y, 
        ui->leZPlaneP3Z
    );
    
    SoftwareLog("Z-Plane: Set current robot position to Point 3");
}

bool RobotWindow::calculateZPlane() {
    if (!ui) return false;
    
    try {
        // Get coordinates from UI
        m_zPlane.p1.x = ui->leZPlaneP1X->text().toDouble();
        m_zPlane.p1.y = ui->leZPlaneP1Y->text().toDouble();
        m_zPlane.p1.z = ui->leZPlaneP1Z->text().toDouble();
        
        m_zPlane.p2.x = ui->leZPlaneP2X->text().toDouble();
        m_zPlane.p2.y = ui->leZPlaneP2Y->text().toDouble();
        m_zPlane.p2.z = ui->leZPlaneP2Z->text().toDouble();
        
        m_zPlane.p3.x = ui->leZPlaneP3X->text().toDouble();
        m_zPlane.p3.y = ui->leZPlaneP3Y->text().toDouble();
        m_zPlane.p3.z = ui->leZPlaneP3Z->text().toDouble();
        
        // Calculate plane equation from 3 points
        // Vector v1 = P2 - P1
        double v1x = m_zPlane.p2.x - m_zPlane.p1.x;
        double v1y = m_zPlane.p2.y - m_zPlane.p1.y;
        double v1z = m_zPlane.p2.z - m_zPlane.p1.z;
        
        // Vector v2 = P3 - P1
        double v2x = m_zPlane.p3.x - m_zPlane.p1.x;
        double v2y = m_zPlane.p3.y - m_zPlane.p1.y;
        double v2z = m_zPlane.p3.z - m_zPlane.p1.z;
        
        // Normal vector n = v1 × v2 (cross product)
        m_zPlane.a = v1y * v2z - v1z * v2y;
        m_zPlane.b = v1z * v2x - v1x * v2z;
        m_zPlane.c = v1x * v2y - v1y * v2x;
        
        // Check if points are collinear (invalid plane)
        double magnitude = sqrt(m_zPlane.a * m_zPlane.a + 
                               m_zPlane.b * m_zPlane.b + 
                               m_zPlane.c * m_zPlane.c);
        
        if (magnitude < 1e-10) {
            SoftwareLog("Z-Plane: Error - Points are collinear, cannot define a plane");
            m_zPlane.isValid = false;
            return false;
        }
        
        // Normalize the normal vector
        m_zPlane.a /= magnitude;
        m_zPlane.b /= magnitude;
        m_zPlane.c /= magnitude;
        
        // Calculate d using point P1: ax + by + cz + d = 0
        m_zPlane.d = -(m_zPlane.a * m_zPlane.p1.x + 
                       m_zPlane.b * m_zPlane.p1.y + 
                       m_zPlane.c * m_zPlane.p1.z);
        
        m_zPlane.isValid = true;
        updateZPlaneEquationDisplay();
        
        SoftwareLog(QString("Z-Plane: Calculated successfully - a=%1, b=%2, c=%3, d=%4")
                   .arg(m_zPlane.a, 0, 'f', 4)
                   .arg(m_zPlane.b, 0, 'f', 4)
                   .arg(m_zPlane.c, 0, 'f', 4)
                   .arg(m_zPlane.d, 0, 'f', 4));
        
        return true;
        
    } catch (const std::exception& e) {
        SoftwareLog(QString("Z-Plane: Calculation error - %1").arg(e.what()));
        m_zPlane.isValid = false;
        return false;
    }
}

void RobotWindow::updateZPlaneEquationDisplay() {
    if (!ui || !ui->lbPlaneEquation) return;
    
    if (!m_zPlane.isValid) {
        ui->lbPlaneEquation->setText("Plane Equation: Invalid");
        ui->lbPlaneEquation->setStyleSheet("color: rgb(255, 100, 100);");
        return;
    }
    
    // Format equation for display
    QString equation;
    if (std::abs(m_zPlane.c) > 1e-10) {
        // Z-form: Z = (-ax - by - d) / c
        double za = -m_zPlane.a / m_zPlane.c;
        double zb = -m_zPlane.b / m_zPlane.c;
        double zd = -m_zPlane.d / m_zPlane.c;
        
        equation = QString("Z = %1X %2 %3Y %4 %5")
                   .arg(za, 0, 'f', 3)
                   .arg(zb >= 0 ? "+" : "-")
                   .arg(qAbs(zb), 0, 'f', 3)
                   .arg(zd >= 0 ? "+" : "-")
                   .arg(qAbs(zd), 0, 'f', 3);
    } else {
        // General form: ax + by + cz + d = 0
        equation = QString("%1X %2 %3Y %4 %5Z %6 %7 = 0")
                   .arg(m_zPlane.a, 0, 'f', 3)
                   .arg(m_zPlane.b >= 0 ? "+" : "-")
                   .arg(qAbs(m_zPlane.b), 0, 'f', 3)
                   .arg(m_zPlane.c >= 0 ? "+" : "-")
                   .arg(qAbs(m_zPlane.c), 0, 'f', 3)
                   .arg(m_zPlane.d >= 0 ? "+" : "-")
                   .arg(qAbs(m_zPlane.d), 0, 'f', 3);
    }
    
    ui->lbPlaneEquation->setText("Plane: " + equation);
    ui->lbPlaneEquation->setStyleSheet("color: rgb(100, 200, 255);");
}

void RobotWindow::onCalculateZPlane() {
    SoftwareLog("Z-Plane: Starting plane calculation...");
    
    if (calculateZPlane()) {
        SoftwareLog("Z-Plane: Plane calculated successfully");
    } else {
        SoftwareLog("Z-Plane: Failed to calculate plane");
    }
}

void RobotWindow::onTestZPlane() {
    if (!m_zPlane.isValid) {
        SoftwareLog("Z-Plane: Cannot test - plane is not calculated");
        return;
    }
    
    // Get test point from user
    bool ok;
    QString input = QInputDialog::getText(this, "Test Z-Plane", 
                                         "Enter test point (X,Y):", 
                                         QLineEdit::Normal, "0,0", &ok);
    
    if (!ok || input.isEmpty()) return;
    
    QStringList coords = input.split(",");
    if (coords.size() != 2) {
        SoftwareLog("Z-Plane: Invalid input format. Use: X,Y");
        return;
    }
    
    double testX = coords[0].trimmed().toDouble(&ok);
    if (!ok) {
        SoftwareLog("Z-Plane: Invalid X coordinate");
        return;
    }
    
    double testY = coords[1].trimmed().toDouble(&ok);
    if (!ok) {
        SoftwareLog("Z-Plane: Invalid Y coordinate");
        return;
    }
    
    // Calculate Z on the plane
    double planeZ = m_zPlane.calculateZ(testX, testY);
    
    SoftwareLog(QString("Z-Plane Test: At point (%1, %2), plane Z = %3")
               .arg(testX, 0, 'f', 2)
               .arg(testY, 0, 'f', 2)
               .arg(planeZ, 0, 'f', 3));
}

void RobotWindow::onZPlaneLimitingToggled(bool enabled) {
    m_zPlane.isEnabled = enabled;
    
    if (enabled && !m_zPlane.isValid) {
        SoftwareLog("Z-Plane: Warning - Enabled but plane is not calculated");
    }
    
    SoftwareLog(QString("Z-Plane Limiting: %1").arg(enabled ? "ENABLED" : "DISABLED"));
}

QString RobotWindow::filterGcodeForZPlane(const QString& gcode) {
    if (!m_zPlane.isEnabled || !m_zPlane.isValid) {
        return gcode; // No filtering needed
    }
    
    QStringList lines = gcode.split('\n');
    QStringList filteredLines;
    
    for (const QString& line : lines) {
        QString trimmed = line.trimmed().toUpper();
        
        // Check for G-code movement commands (G0, G1, G2, G3)
        if (trimmed.startsWith("G0 ") || trimmed.startsWith("G1 ") ||
            trimmed.startsWith("G2 ") || trimmed.startsWith("G3 ")) {
            
            // Parse coordinates
            double x = 0, y = 0, z = 0;
            bool hasX = false, hasY = false, hasZ = false;
            
            // Extract X, Y, Z values
            QRegularExpression xRegex("X([+-]?\\d*\\.?\\d+)");
            QRegularExpression yRegex("Y([+-]?\\d*\\.?\\d+)");
            QRegularExpression zRegex("Z([+-]?\\d*\\.?\\d+)");
            
            QRegularExpressionMatch xMatch = xRegex.match(trimmed);
            QRegularExpressionMatch yMatch = yRegex.match(trimmed);
            QRegularExpressionMatch zMatch = zRegex.match(trimmed);
            
            if (xMatch.hasMatch()) {
                x = xMatch.captured(1).toDouble();
                hasX = true;
            }
            if (yMatch.hasMatch()) {
                y = yMatch.captured(1).toDouble();
                hasY = true;
            }
            if (zMatch.hasMatch()) {
                z = zMatch.captured(1).toDouble();
                hasZ = true;
            }
            
            // Apply Z-limiting if we have X, Y, Z coordinates
            if (hasX && hasY && hasZ) {
                double limitZ = m_zPlane.calculateZ(x, y);
                
                if (z < limitZ) {
                    // Z is below the limiting plane, clamp it
                    QString originalLine = line;
                    QString modifiedLine = line;
                    modifiedLine.replace(zRegex, QString("Z%1").arg(limitZ, 0, 'f', 3));
                    
                    filteredLines.append(modifiedLine);
                    
                    SoftwareLog(QString("Z-Plane: Limited Z from %1 to %2 at (%3, %4)")
                               .arg(z, 0, 'f', 3)
                               .arg(limitZ, 0, 'f', 3)
                               .arg(x, 0, 'f', 2)
                               .arg(y, 0, 'f', 2));
                    continue;
                }
            }
        }
        
        // No modification needed
        filteredLines.append(line);
    }
    
    return filteredLines.join('\n');
}

void RobotWindow::SaveZPlaneSettings()
{
    QString prefix = ProjectName + ".ZPlane.";
    
    // Save Z-plane points
    VariableManager::instance().updateVar(prefix + "P1.X", m_zPlane.p1.x);
    VariableManager::instance().updateVar(prefix + "P1.Y", m_zPlane.p1.y);
    VariableManager::instance().updateVar(prefix + "P1.Z", m_zPlane.p1.z);
    
    VariableManager::instance().updateVar(prefix + "P2.X", m_zPlane.p2.x);
    VariableManager::instance().updateVar(prefix + "P2.Y", m_zPlane.p2.y);
    VariableManager::instance().updateVar(prefix + "P2.Z", m_zPlane.p2.z);
    
    VariableManager::instance().updateVar(prefix + "P3.X", m_zPlane.p3.x);
    VariableManager::instance().updateVar(prefix + "P3.Y", m_zPlane.p3.y);
    VariableManager::instance().updateVar(prefix + "P3.Z", m_zPlane.p3.z);
    
    // Save plane equation parameters
    VariableManager::instance().updateVar(prefix + "A", m_zPlane.a);
    VariableManager::instance().updateVar(prefix + "B", m_zPlane.b);
    VariableManager::instance().updateVar(prefix + "C", m_zPlane.c);
    VariableManager::instance().updateVar(prefix + "D", m_zPlane.d);
    
    // Save status flags
    VariableManager::instance().updateVar(prefix + "IsValid", m_zPlane.isValid);
    VariableManager::instance().updateVar(prefix + "IsEnabled", m_zPlane.isEnabled);
    
    SoftwareLog(QString("Z-Plane: Settings saved - Valid=%1, Enabled=%2")
               .arg(m_zPlane.isValid ? "true" : "false")
               .arg(m_zPlane.isEnabled ? "true" : "false"));
}

