#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include "SoftwareManager.h"
#include "MainWindow.h"
#include "ModernDialog.h"
#include "CameraSelectionDialog.h"
#include "CameraCalibration.h"
#include "GScriptEditorSupport.h"
#include "UnityTool.h"  // ? For SoftwareLog function
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>
#include <QRegularExpression>
#include <cmath>      // ? For Z-plane calculations
#include <QInputDialog>  // ? For test input dialog
#include <QtMath>      // ? For qAbs function
#include <random>      // For random number generation
#include <QElapsedTimer> // For performance timing
#include <QMessageBox>  // For dialog boxes
#include <QDebug>       // For debug logging
#include <QFont>
#include <QVector3D>
#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollBar>
#include <QFormLayout>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QTextBrowser>
#include <QTabWidget>
#include <QCheckBox>
#include <QProcessEnvironment>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include "sdk/DeltaXVersion.h"

RobotWindow::RobotWindow(QWidget *parent, QString projectName) :
    QMainWindow(parent),
    ui(new Ui::RobotWindow),
    ProjectName(projectName),
    m_variableManager(&VariableManager::instance()),
    m_batchUpdateTimer(new QTimer(this))
{
    ui->setupUi(this);
    setWindowTitle(tr("Delta X Software - Version %1")
                       .arg(QString::fromLatin1(DeltaXVersion::Application)));

    m_deviceCommandBroker = new DeviceCommandBroker(this);
    m_cellSupervisor = new CellSupervisor(this);

    SoftwareLog("Load project: " + ProjectName);
    
    // Initialize batch update timer
    m_batchUpdateTimer->setSingleShot(true);
    m_batchUpdateTimer->setInterval(50); // 50ms batching window
    connect(m_batchUpdateTimer, &QTimer::timeout, this, &RobotWindow::processBatchUpdates);
    
    InitVariables();
    InitOtherThreadObjects();
    InitEvents();

    LoadSettings();
    InitDefaultValue();

    if (m_imagePipelineController) {
        QString detectingKey = ui->cbSelectedDetecting->currentText();
        if (detectingKey.isEmpty())
            detectingKey = QStringLiteral("tracking0");
        const QString matrixKey = detectingKey + QStringLiteral(".ImageToRealWorldMatrix");
        if (VariableManager::instance().containsFullKeyScoped(ProjectName, matrixKey)) {
            m_imagePipelineController->inputMappingMatrix(
                VariableManager::instance().getVarScoped(ProjectName, matrixKey).value<QMatrix>());
        }
    }
    
    // Initialize Cloud Point Mapping UI after all other objects are ready
    if (m_pointToolController) {
        m_pointToolController->initializeUI(ui->tPointTool);
    }
}

RobotWindow::~RobotWindow()
{
    qDebug() << "RobotWindow::~RobotWindow" << ProjectName;

    // Stop the capture producer before the frame coordinator. StartedCapture
    // uses a blocking hand-off so a frame cannot overtake its encoder snapshot;
    // shutting the manager down first could otherwise strand the camera thread.
    CameraTimer.stop();
    disconnect(CameraInstance, &Camera::StartedCapture,
               TrackingManagerInstance, &TrackingManager::SaveCapturePosition);
    CameraThread->quit();
    CameraThread->wait();
    delete CameraThread;

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

    for (int i = 0; i < GcodeScripts.count(); i++)
    {
        GcodeScripts.at(i)->thread()->quit();
        GcodeScripts.at(i)->thread()->wait();
    }

    // Clean up Python process
    if (process != nullptr && process->state() == QProcess::Running) {
        qDebug() << "Terminating Python process on application close...";
        process->terminate();
        
        // �?i process terminate, n?u kh�ng th�nh c�ng th� kill
        if (!process->waitForFinished(2000)) { // �?i 2 gi�y
            process->kill();
            process->waitForFinished(1000); // �?i th�m 1 gi�y cho kill
        }
        
        qDebug() << "Python process terminated";
    }

    // Clean up Point Tool Controller
    delete m_pointToolController;

    // ? Fix: Cleanup plugins to prevent memory leak
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
    qRegisterMetaType< QVector<ObjectInfo> >("QVector<ObjectInfo>");
    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< cv::Size >("cv::Size");
    qRegisterMetaType< Object >("Object");
    qRegisterMetaType< QVector<Object>* >("QVector<Object>*");
    qRegisterMetaType< QVector<Object> >("QVector<Object>&");
    qRegisterMetaType< QVector<Object>* >("QVector<Object>");
    qRegisterMetaType< QVector<QSharedPointer<Object>> >("QVector<QSharedPointer<Object>>");
    qRegisterMetaType< QList<QPolygonF> >("QList<QPolygonF>");
    qRegisterMetaType< QVector<ObjectInfo> >("QVector<ObjectInfo>");
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
    connect(ui->pbAddPositionVariable, &QPushButton::clicked,
            this, &RobotWindow::openPositionVariableDialog);

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
    QFont debugFont = ui->teDebug->document()->defaultFont();
    if (debugFont.pointSize() <= 0)
        debugFont.setPointSize(11);
    debugFont.setPointSize(14); // ensure debug console is readable
    ui->teDebug->document()->setDefaultFont(debugFont);
    ui->teDebug->setFont(debugFont);

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
    CameraOpenTimeoutTimer.setSingleShot(true);
    connect(&CameraOpenTimeoutTimer, &QTimer::timeout, this, &RobotWindow::HandleCameraOpenTimeout);

    //---------- Object Detector Init -------------

//    TrackingObjectTable = new ObjectVariableTable(this);

    connect(ui->pbUpdateObjectToView, &QPushButton::clicked, this, &RobotWindow::UpdateObjectsToView);

//    ui->gbCameraCalibration->setChecked(false);
//    ui->gbCameraObject->setChecked(false);
//    ui->gbCameraVariable->setChecked(false);

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

    for (int i = 0; i < 3; i++)
    {
        RobotPara robotPara;
        RobotParameters.append(robotPara);
    }

    //------------ Devices --------

        //-------- Camera --------
    CameraInstance = new Camera();
    CameraInstance->ProjectName = ProjectName;
    CameraThread = new QThread(this);
    CameraInstance->moveToThread(CameraThread);
    connect(CameraThread, &QThread::finished, CameraInstance, &QObject::deleteLater);
    connect(CameraInstance, &Camera::StopCameraRequest, this, &RobotWindow::StopCapture);

    CameraThread->start();

    InitControlPlane();

    connect(CameraInstance, &Camera::connectedResult, this, &RobotWindow::UpdateCameraConnectedState);
    connect(CameraInstance, &Camera::connectedResult, this, [this](bool, int) {
        updateCameraInfoDisplay();
    });

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
    connect(ui->cbSelectedEncoder, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int id) {
        QMetaObject::invokeMethod(DeviceManagerInstance, "SetSelectedDevice",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, DeviceManager::ENCODER), Q_ARG(int, id));
    });

    connect(ui->pbReadEncoder, SIGNAL(clicked(bool)), this, SLOT(ReadEncoder()));
    connect(ui->pbSetEncoderInterval, SIGNAL(clicked(bool)), this, SLOT(SetEncoderAutoRead()));
    connect(ui->pbResetEncoder, SIGNAL(clicked(bool)), this, SLOT(ResetEncoderPosition()));
    connect(ui->pbSetEncoderVelocity, SIGNAL(clicked(bool)), this, SLOT(SetEncoderVelocity()));
    if (QPushButton* calibrateEncoderButton = findChild<QPushButton*>(QStringLiteral("pbCalibrateEncoder"))) {
        connect(calibrateEncoderButton, &QPushButton::clicked, this, &RobotWindow::CalibrateEncoder);
    }

    connect(ui->cbEncoderType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeEncoderType(int)));
    connect(ui->cbLinkToConveyorX, SIGNAL(stateChanged(int)), this, SLOT(ChangeConveyorLinkToEncoder(int)));

    connect(ui->pbStartScheduledEncoder, SIGNAL(clicked(bool)), this, SLOT(StartScheduledEncoder()));

    //-------- Slider --------

    connect(ui->pbSlidingConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectSliding()));
    connect(ui->cbSelectedSlider, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int id) {
        QMetaObject::invokeMethod(DeviceManagerInstance, "SetSelectedDevice",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, DeviceManager::SLIDER), Q_ARG(int, id));
    });
    connect(ui->pbSlidingHome, SIGNAL(clicked(bool)), this, SLOT(GoHomeSliding()));
    connect(ui->pbSlidingDisable, SIGNAL(clicked(bool)), this, SLOT(DisableSliding()));
    connect(ui->leSlidingSpeed, SIGNAL(returnPressed()), this, SLOT(SetSlidingSpeed()));
    connect(ui->leSlidingPosition, SIGNAL(returnPressed()), this, SLOT(SetSlidingPosition()));

        //-------- MCU --------
    connect(ui->pbExternalControllerConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectExternalMCU()));
    connect(ui->cbSelectedDevice, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int id) {
        QMetaObject::invokeMethod(DeviceManagerInstance, "SetSelectedDevice",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, DeviceManager::DEVICE), Q_ARG(int, id));
    });
    connect(ui->leTransmitToMCU, SIGNAL(returnPressed()), this, SLOT(TransmitTextToExternalMCU()));

    //----- Tracking -----
    InitTrackingThread();
    connect(ui->cbSelectedTracking, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedTracking(int)));
    connect(ui->cbTrackingEncoderSource, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedTrackingEncoder(int)));
    
    // Setup visualizations AFTER TrackingManager is initialized
    setupConveyorVisualization();

    //----- Gcode Programing----------

    InitGcodeEditorModule();

    //----- Plugin ------
    LoadPlugin();
}

void RobotWindow::InitControlPlane()
{
    if (!m_deviceCommandBroker || !m_cellSupervisor || !DeviceManagerInstance)
        return;

    connect(m_deviceCommandBroker, &DeviceCommandBroker::DispatchCommand,
            DeviceManagerInstance,
            QOverload<QString, QString>::of(&DeviceManager::SendGcode),
            Qt::QueuedConnection);
    connect(DeviceManagerInstance, &DeviceManager::DeviceResponded,
            m_deviceCommandBroker, &DeviceCommandBroker::HandleDeviceResponse,
            Qt::QueuedConnection);

    connect(this, &RobotWindow::Send, this,
            [this](int deviceType, const QString& command) {
        if (!m_deviceCommandBroker)
            return;
        const QString device = selectedDeviceName(deviceType);
        m_deviceCommandBroker->Submit(QStringLiteral("manual/ui"), device, command,
                                      DeviceCommandBroker::Origin::Manual, true, 5000);
    });

    connect(m_cellSupervisor, &CellSupervisor::StateChanged, this,
            [this](CellSupervisor::State state, const QString& stateName,
                   const QString& reason) {
        if (m_deviceCommandBroker)
            m_deviceCommandBroker->SetCellState(stateName);
        updateCellStateUi(state, stateName, reason);

        QHash<QString, QVariant> values;
        values.insert(QStringLiteral("Cell.State"), stateName);
        values.insert(QStringLiteral("Cell.FaultReason"),
                      state == CellSupervisor::State::Faulted ? reason : QString());
        values.insert(QStringLiteral("Cell.UpdatedAt"),
                      QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
        VariableManager::instance().updateBatchScoped(
            ProjectName, values, VariableManager::Persistence::Runtime);
    });
    connect(m_cellSupervisor, &CellSupervisor::ActiveOwnersChanged, this,
            [this](const QStringList& owners) {
        QHash<QString, QVariant> values;
        values.insert(QStringLiteral("Cell.ActiveWorkers"), owners);
        values.insert(QStringLiteral("Cell.ActiveWorkerCount"), owners.size());
        VariableManager::instance().updateBatchScoped(
            ProjectName, values, VariableManager::Persistence::Runtime);
        if (cellResetButton)
            cellResetButton->setEnabled(owners.isEmpty() && m_cellSupervisor &&
                                        m_cellSupervisor->state() == CellSupervisor::State::Faulted);
    });
    connect(m_cellSupervisor, &CellSupervisor::ControlledStopRequested,
            this, &RobotWindow::performControlledCellStop);

    connect(m_deviceCommandBroker, &DeviceCommandBroker::CommandRejected, this,
            [this](const QString& owner, const QString& device,
                   const QString& command, const QString& reason) {
        const QString message = tr("Command rejected [%1 → %2]: %3 (%4)")
                                    .arg(owner, device, command, reason);
        SoftwareLog(message);
        QHash<QString, QVariant> values;
        values.insert(QStringLiteral("Cell.LastRejectedCommand"), command);
        values.insert(QStringLiteral("Cell.LastRejectedDevice"), device);
        values.insert(QStringLiteral("Cell.LastRejectedOwner"), owner);
        values.insert(QStringLiteral("Cell.LastRejectedReason"), reason);
        VariableManager::instance().updateBatchScoped(
            ProjectName, values, VariableManager::Persistence::Runtime);
    });
    connect(m_deviceCommandBroker, &DeviceCommandBroker::CommandTimedOut, this,
            [this](quint64, const QString& owner, const QString& device,
                   const QString& command) {
        const QString fault = tr("Command broker timeout [%1 → %2]: %3")
                                  .arg(owner, device, command);
        SoftwareLog(fault);
        if (m_cellSupervisor) {
            QMetaObject::invokeMethod(m_cellSupervisor,
                                      [this, fault]() {
                if (m_cellSupervisor)
                    m_cellSupervisor->ReportFault(fault);
            }, Qt::QueuedConnection);
        }
    });

    for (int index = 0; index < 3; ++index) {
        m_deviceCommandBroker->RegisterDevice(QString("robot%1").arg(index));
        m_deviceCommandBroker->RegisterDevice(QString("conveyor%1").arg(index));
        m_deviceCommandBroker->RegisterDevice(QString("slider%1").arg(index));
        m_deviceCommandBroker->RegisterDevice(QString("encoder%1").arg(index));
        m_deviceCommandBroker->RegisterDevice(QString("device%1").arg(index));
    }

    m_deviceCommandBroker->SetCellState(m_cellSupervisor->stateName());
    updateCellStateUi(m_cellSupervisor->state(), m_cellSupervisor->stateName(), QString());
    QHash<QString, QVariant> initialState;
    initialState.insert(QStringLiteral("Cell.State"), m_cellSupervisor->stateName());
    initialState.insert(QStringLiteral("Cell.ActiveWorkerCount"), 0);
    initialState.insert(QStringLiteral("Cell.FaultReason"), QString());
    VariableManager::instance().updateBatchScoped(
        ProjectName, initialState, VariableManager::Persistence::Runtime);
}

QString RobotWindow::selectedDeviceName(int deviceType) const
{
    QString prefix;
    QComboBox* combo = nullptr;
    switch (deviceType) {
    case DeviceManager::ROBOT:
        prefix = QStringLiteral("robot");
        combo = ui->cbSelectedRobot;
        break;
    case DeviceManager::CONVEYOR:
        prefix = QStringLiteral("conveyor");
        combo = ui->cbSelectedConveyor;
        break;
    case DeviceManager::ENCODER:
        prefix = QStringLiteral("encoder");
        combo = ui->cbSelectedEncoder;
        break;
    case DeviceManager::SLIDER:
        prefix = QStringLiteral("slider");
        combo = ui->cbSelectedSlider;
        break;
    case DeviceManager::DEVICE:
        prefix = QStringLiteral("device");
        combo = ui->cbSelectedDevice;
        break;
    default:
        return QString();
    }

    const QString selected = combo ? combo->currentText().trimmed().toLower() : QString();
    const QRegularExpression exact(QStringLiteral("^%1\\d+$")
                                       .arg(QRegularExpression::escape(prefix)),
                                   QRegularExpression::CaseInsensitiveOption);
    if (exact.match(selected).hasMatch())
        return selected;
    const int index = combo ? qMax(0, combo->currentIndex()) : 0;
    return prefix + QString::number(index);
}

bool RobotWindow::submitManualDeviceCommand(const QString& commandLine,
                                            const QString& owner)
{
    if (!m_deviceCommandBroker)
        return false;

    const QString line = commandLine.trimmed();
    const int separator = line.indexOf(QRegularExpression(QStringLiteral("\\s")));
    if (separator <= 0) {
        SoftwareLog(tr("Manual command rejected: use '<device><index> <G-code>', "
                       "for example 'conveyor0 M310 100'."));
        return false;
    }

    const QString device = line.left(separator).trimmed().toLower();
    static const QRegularExpression devicePattern(
        QStringLiteral("^(robot|device|conveyor|slider|encoder)\\d+$"),
        QRegularExpression::CaseInsensitiveOption);
    const QString command = line.mid(separator).trimmed();
    if (!devicePattern.match(device).hasMatch() || command.isEmpty()) {
        SoftwareLog(tr("Manual command rejected: invalid device-qualified command '%1'.")
                        .arg(commandLine));
        return false;
    }

    m_deviceCommandBroker->RegisterDevice(device);
    return m_deviceCommandBroker->Submit(owner, device, command,
                                         DeviceCommandBroker::Origin::Manual,
                                         true, 5000) != 0;
}

void RobotWindow::performControlledCellStop(const QString& reason)
{
    SoftwareLog(tr("Controlled cell stop: %1").arg(reason));
    CameraTimer.stop();
    if (m_deviceCommandBroker)
        m_deviceCommandBroker->RequestControlledStop(reason);

    for (GcodeScript* script : std::as_const(GcodeScripts)) {
        if (script && script->IsRunning())
            QMetaObject::invokeMethod(script, "Stop", Qt::QueuedConnection);
    }
}

void RobotWindow::updateCellStateUi(CellSupervisor::State state,
                                    const QString& stateName,
                                    const QString& reason)
{
    if (cellStateLabel) {
        QString color = QStringLiteral("#d4d4d4");
        if (state == CellSupervisor::State::Ready)
            color = QStringLiteral("#69d18b");
        else if (state == CellSupervisor::State::AutoRunning)
            color = QStringLiteral("#73b7ff");
        else if (state == CellSupervisor::State::Paused ||
                 state == CellSupervisor::State::Recovering)
            color = QStringLiteral("#f0b24a");
        else if (state == CellSupervisor::State::Faulted)
            color = QStringLiteral("#ff6b6b");
        cellStateLabel->setStyleSheet(QStringLiteral("color: %1; font-weight: bold;").arg(color));
        cellStateLabel->setText(reason.isEmpty()
            ? tr("CELL: %1").arg(stateName.toUpper())
            : tr("CELL: %1 — %2").arg(stateName.toUpper(), reason));
        cellStateLabel->setToolTip(reason);
    }
    if (cellResetButton) {
        cellResetButton->setVisible(state == CellSupervisor::State::Faulted);
        cellResetButton->setEnabled(state == CellSupervisor::State::Faulted &&
                                    m_cellSupervisor &&
                                    m_cellSupervisor->activeOwners().isEmpty());
    }
}

void RobotWindow::InitSocketConnection()
{
    // ---------- Server ---------

    // T�m ip local c?a m�y
    QSettings networkSettings;
    const bool allowLanControl = networkSettings.value(
        QStringLiteral("Network/AllowLanControl"), false).toBool();
    QString localIP = allowLanControl
        ? networkSettings.value(QStringLiteral("Network/ListenAddress"),
                                SocketConnectionManager::printLocalIpAddresses()).toString()
        : QStringLiteral("127.0.0.1");
    // localhost:8844
    QStringList ipAndPort = ui->leIP->text().split(":");
    QString port = ipAndPort.at(1);

    ConnectionManager = new SocketConnectionManager(localIP, port.toInt());
    ConnectionManager->ProjectName = ProjectName;
    ConnectionManager->setIndexFileName(QStringLiteral("Jogging.html"));

    QThread* thread = new QThread(this);

    ConnectionManager->moveToThread(thread);

    connect(ConnectionManager->thread(), &QThread::finished, ConnectionManager, &QObject::deleteLater);

    thread->start();

    connect(ConnectionManager, &SocketConnectionManager::eventReceived, this, &RobotWindow::ActiveWidgetByName);
    connect(ConnectionManager, &SocketConnectionManager::remoteControlRejected,
            this, [this](const QString& operation, const QString& reason) {
        SoftwareLog(tr("Remote control rejected [%1]: %2").arg(operation, reason));
    });

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
        if (!ConnectionManager)
        {
            QMessageBox::warning(this, "Web Control", "Connection manager is unavailable.");
            return;
        }

        if (!ConnectionManager->WebServer->isListening())
        {
            if (!ConnectionManager->WebServer->listen(QHostAddress(ConnectionManager->hostAddress), 5000))
            {
                QMessageBox::warning(this, "Web Control", "Web server is not running. Please start the server first.");
                return;
            }
        }

        QString webUrl = QString("http://%1:5000").arg(ConnectionManager->hostAddress);
        QDesktopServices::openUrl(QUrl(webUrl));
        SoftwareLog("Opening web control at: " + webUrl);
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
    ImageProcessingInstance->CreateTaskNode("GetPerspectiveNode", TaskNode::GET_PERSPECTIVE_NODE);
    ImageProcessingInstance->CreateTaskNode("WarpImageNode", TaskNode::WARP_IMAGE_NODE, "ResizeImageNode|GetPerspectiveNode");
    ImageProcessingInstance->CreateTaskNode("CropImageNode", TaskNode::CROP_IMAGE_NODE, "WarpImageNode");

    ImageProcessingInstance->CreateTaskNode("MappingMatrixNode", TaskNode::MAPPING_MATRIX_NODE);
    ImageProcessingInstance->CreateTaskNode("ColorFilterNode", TaskNode::COLOR_FILTER_NODE, "CropImageNode");
    ImageProcessingInstance->CreateTaskNode("GetObjectsNode", TaskNode::GET_OBJECTS_NODE, "ColorFilterNode");
    ImageProcessingInstance->CreateTaskNode("FindCirclesNode", TaskNode::FIND_CIRCLES_NODE, "ColorFilterNode");
    ImageProcessingInstance->CreateTaskNode("VisibleObjectsNode", TaskNode::VISIBLE_OBJECTS_NODE, "GetObjectsNode|FindCirclesNode|MappingMatrixNode");

    ImageProcessingInstance->CreateTaskNode("DisplayImageNode", TaskNode::DISPLAY_IMAGE_NODE, "CropImageNode");

    // Initialize pipeline controller after nodes are ready
    m_imagePipelineController = new ImagePipelineController(ImageProcessingInstance, this);
    connect(m_imagePipelineController, &ImagePipelineController::mappingMatrixUpdated,
            this, &RobotWindow::onMappingMatrixUpdated);
    connect(m_imagePipelineController, &ImagePipelineController::mappingValidityChanged,
            this, [this](bool valid, const QString& reason) {
        QString detectingKey = ui->cbSelectedDetecting->currentText();
        if (detectingKey.isEmpty())
            detectingKey = QStringLiteral("tracking0");
        if (!valid) {
            m_mappingMatrices.remove(detectingKey);
            VariableManager::instance().updateVarScoped(
                ProjectName, detectingKey + QStringLiteral(".Calibration.Mapping.IsValid"), false);
            statusBar()->showMessage(reason, 7000);
            SoftwareLog(QStringLiteral("Camera mapping invalidated: ") + reason);
        }
    });
    m_imagePipelineController->configureWarpCrop(false, false);
    CameraCalibration::Profile intrinsicProfile;
    if (CameraCalibration::loadFromVariables(ProjectName, QStringLiteral("Camera.Intrinsic"),
                                             intrinsicProfile)) {
        m_imagePipelineController->setIntrinsicCalibration(intrinsicProfile);
    }
    QString initialDetectingKey = ui->cbSelectedDetecting->currentText();
    if (initialDetectingKey.isEmpty())
        initialDetectingKey = QStringLiteral("tracking0");
    const QString initialMatrixKey = initialDetectingKey + QStringLiteral(".ImageToRealWorldMatrix");
    if (VariableManager::instance().containsFullKeyScoped(ProjectName, initialMatrixKey)) {
        const QMatrix savedMatrix = VariableManager::instance()
            .getVarScoped(ProjectName, initialMatrixKey).value<QMatrix>();
        m_imagePipelineController->inputMappingMatrix(savedMatrix);
    }
    if (m_imagePipelineController) {
        connect(CameraInstance, &Camera::FrameCaptured,
                m_imagePipelineController, &ImagePipelineController::inputFrame);
        connect(m_imagePipelineController, &ImagePipelineController::externalFrameReady,
                ConnectionManager, &SocketConnectionManager::sendVisionFrame);
    } else {
        connect(CameraInstance, SIGNAL(GotImage(cv::Mat)), ImageProcessingInstance->GetNode("GetImageNode"), SLOT(Input(cv::Mat)));
    }
    connect(CameraInstance, SIGNAL(GotImage(cv::Mat)), this, SLOT(updateCameraInfoDisplay()));
//    connect(CameraInstance, SIGNAL(GotImage(cv::Mat)), ImageProcessingInstance, SLOT(GotImage(cv::Mat)));
//    connect(this, SIGNAL(GotResizePara(cv::Size)), ImageProcessingInstance, SLOT(GotResizeValue(cv::Size)));
//    connect(ImageProcessingInstance->GetNode("GetPerspectiveNode"), SIGNAL(HadOutput(cv::Mat)), ImageProcessingInstance, SLOT(GotPerspectiveMatrix(cv::Mat)));



    // ---------- Blob Filter Window---------
    ParameterPanel = new FilterWindow(this, ProjectName);

    // ---------- Main UI -------

    connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), this, SLOT(LoadWebcam()));
    connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), this, SLOT(LoadImages()));
    if (QPushButton* intrinsicButton = findChild<QPushButton*>(QStringLiteral("pbIntrinsicCalibration"))) {
        connect(intrinsicButton, &QPushButton::clicked,
                this, &RobotWindow::CalibrateCameraIntrinsics);
    }
    connect(ui->cbDetectingAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectObjectDetectingAlgorithm(int)));

    connect(ui->cbSendingImageMethod, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index){
        ConnectionManager->imageSendingMethod = index;
    });

    InitExternalVisionUI();

    ui->cbDetectingAlgorithm->setCurrentIndex(0);
    SelectObjectDetectingAlgorithm(0);

    ui->gvImageViewer->ProjectName = ProjectName;

    connect(ui->pbGetSizeTool, &QPushButton::toggled,  [=](bool checked)
    {
        if (checked == true)
        {
            ui->pbMappingPointTool->setChecked(false);

            ui->gvImageViewer->SelectRectTool();

            ui->pbCapture->clicked();
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

    connect(ui->pbClearDetectObjects, &QPushButton::clicked, this, &RobotWindow::ClearDetectObjects);

    connect(ui->gvImageViewer, &ImageViewer::selectedNoTool, this, &RobotWindow::UnselectToolButtons);

    connect(ui->gvImageViewer, &ImageViewer::changedRect, this, &RobotWindow::GetObjectSizeFromImage);
    connect(ui->gvImageViewer, &ImageViewer::changedMappingPoint, this, &RobotWindow::GetMappingPointFromImage);

    auto applyThresholdsToCurrentTracking = [=]()
    {
        if (!TrackingManagerInstance)
            return;
        int index = ui->cbSelectedTracking->currentIndex();
        if (index < 0 || index >= TrackingManagerInstance->Trackings.count())
            return;
        QMetaObject::invokeMethod(
            TrackingManagerInstance->Trackings.at(index),
            "SetAssociationThresholds", Qt::QueuedConnection,
            Q_ARG(float, ui->leIoUThreshold->text().toFloat()),
            Q_ARG(float, ui->leDistanceThreshold->text().toFloat()));
    };

    connect(ui->leIoUThreshold, &QLineEdit::returnPressed, this, [=](){ applyThresholdsToCurrentTracking(); });
    connect(ui->leDistanceThreshold, &QLineEdit::returnPressed, this, [=](){ applyThresholdsToCurrentTracking(); });

    connect(ui->pbZoomInCameraView, &QPushButton::clicked, [=](bool checked)
    {
        ui->gvImageViewer->ZoomIn(2);
        updateCameraInfoDisplay(); // Update ratio display
//        ui->graphicsView->ZoomIn(2);
    });
    connect(ui->pbZoomOutCameraView, &QPushButton::clicked, [=](bool checked)
    {
        ui->gvImageViewer->ZoomOut(2);
        updateCameraInfoDisplay(); // Update ratio display
//        ui->graphicsView->ZoomOut(2);
    });

    const auto applyTrackingBounds = [this]() {
        if (!TrackingManagerInstance || TrackingManagerInstance->Trackings.isEmpty())
            return;
        QMetaObject::invokeMethod(
            TrackingManagerInstance->Trackings.at(0),
            "SetTrackingBounds", Qt::QueuedConnection,
            Q_ARG(float, ui->leLimitMinX->text().toFloat()),
            Q_ARG(float, ui->leLimitMaxX->text().toFloat()),
            Q_ARG(float, ui->leLimitMinY->text().toFloat()),
            Q_ARG(float, ui->leLimitMaxY->text().toFloat()));
    };
    connect(ui->leLimitMinX, &QLineEdit::returnPressed, this, applyTrackingBounds);
    connect(ui->leLimitMaxX, &QLineEdit::returnPressed, this, applyTrackingBounds);
    connect(ui->leLimitMinY, &QLineEdit::returnPressed, this, applyTrackingBounds);
    connect(ui->leLimitMaxY, &QLineEdit::returnPressed, this, applyTrackingBounds);


    // ---------- Image Provider -------

    connect(ui->pbCapture, &QPushButton::clicked, CameraInstance, &Camera::GeneralCapture);
    connect(ui->pbStartAcquisition, &QPushButton::clicked, this, &RobotWindow::StartContinuousCapture);

    connect(ui->pbSaveImage, &QPushButton::clicked, [=](bool checked)
    {
        ui->fCapturingImages->setVisible(true);
        ui->lwImageList->setVisible(true);

        QString absolutePath = checkAndCreateDir(ui->leImageFolder->text());

        if (CameraInstance && !CameraInstance->CaptureImage.empty()) {
        saveImageWithUniqueName(CameraInstance->CaptureImage, absolutePath);
        }
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

    if (m_imagePipelineController) {
        connect(this, SIGNAL(GotResizePara(cv::Size)), m_imagePipelineController, SLOT(inputResize(cv::Size)));
        connect(ui->gvImageViewer, SIGNAL(changedQuadrangle(QPolygonF)), m_imagePipelineController, SLOT(inputPerspectiveQuadrangle(QPolygonF)));
        connect(ui->gvImageViewer, SIGNAL(changedArea(QRectF)), m_imagePipelineController, SLOT(inputCropArea(QRectF)));
    }

    connect(ui->leImageWidth, &QLineEdit::returnPressed,
    [=] (){
        int newW = ui->leImageWidth->text().toInt();

       int imgW = 0;
       int imgH = 0;
       if (m_imagePipelineController) {
           FrameSnapshot snap = m_imagePipelineController->currentFrameSnapshot();
           imgW = snap.width;
           imgH = snap.height;
       }

        int newH = ImageTool::Map(newW, imgW, imgH);

        ui->leImageHeight->setText(QString::number(newH));

        emit GotResizePara(cv::Size(newW, newH));

        SaveDetectingUI();
    });

    connect(ui->leImageHeight, &QLineEdit::returnPressed,
    [=] (){
        int newH = ui->leImageHeight->text().toInt();

       int imgW = 0;
       int imgH = 0;
       if (m_imagePipelineController) {
           FrameSnapshot snap = m_imagePipelineController->currentFrameSnapshot();
           imgW = snap.width;
           imgH = snap.height;
       }

        int newW = ImageTool::Map(newH, imgH, imgW);

        ui->leImageWidth->setText(QString::number(newW));

        emit GotResizePara(cv::Size(newW, newH));

        SaveDetectingUI();
    });

    connect(ui->tbAutoResizeImage, &QToolButton::toggled, [=](bool checked)
    {
        if (m_imagePipelineController) {
            m_imagePipelineController->configureAutoResize(checked);
        } else {
            TaskNode* resizeImageNode = ImageProcessingInstance->GetNode("ResizeImageNode");
            if (resizeImageNode) {
                QMetaObject::invokeMethod(resizeImageNode,
                                          [resizeImageNode, checked]() {
                                              resizeImageNode->SetPassThrough(!checked);
                                          },
                                          Qt::QueuedConnection);
            }
        }
    });
        
    // Image display handled by pipeline controller
    if (m_imagePipelineController) {
        m_imagePipelineController->setDisplayTarget(ui->gvImageViewer);
    } else {
        connect(ImageProcessingInstance->GetNode("DisplayImageNode"), SIGNAL(HadOutput(QPixmap)), ui->gvImageViewer, SLOT(SetImage(QPixmap)));
    }

    connect(ParameterPanel, SIGNAL(ColorFilterValueChanged(QList<int>)), m_imagePipelineController, SLOT(inputColorFilterValues(QList<int>)));
    connect(ParameterPanel, SIGNAL(BlurSizeChanged(int)), m_imagePipelineController, SLOT(inputColorFilterBlur(int)));
    connect(ParameterPanel, SIGNAL(ColorInverted(bool)), m_imagePipelineController, SLOT(inputColorFilterInvert(bool)));

    connect(this, SIGNAL(GotObjects(QVector<Object>)), m_imagePipelineController, SLOT(inputVisibleObjects(QVector<Object>)));
    connect(this, &RobotWindow::GotMappingMatrix,
            m_imagePipelineController, &ImagePipelineController::inputMappingMatrix);
    connect(this, SIGNAL(GotOjectFilterInfo(Object)), m_imagePipelineController, SLOT(inputObjectFilter(Object)));
    m_imagePipelineController->setOverlayTarget(ui->gvImageViewer);
    // VisibleObjects forwarding handled by controller via pipeline

    connect(ui->leDetectingObjectListName, &QLineEdit::returnPressed, this, [=]()
    {
        QMetaObject::invokeMethod(
            ImageProcessingInstance, "SetObjectsName", Qt::QueuedConnection,
            Q_ARG(QString, ui->leDetectingObjectListName->text()));
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


    // Khai b�o v� kh?i t?o lu?ng
    QThread* thread = new QThread;
    ImageProcessingInstance->moveToThread(thread);

    // K?t n?i d? d?m b?o s? s?ch s?
    connect(thread, &QThread::finished, ImageProcessingInstance, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater); // �?m b?o lu?ng cung t? h?y khi k?t th�c

    // B?t d?u lu?ng
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
    connect(ConnectionManager, &SocketConnectionManager::gcodeReceived,
            this, &RobotWindow::DispatchRemoteGScript, Qt::UniqueConnection);
    connect(ConnectionManager, &SocketConnectionManager::gscriptEditorReceived,
            this, &RobotWindow::LoadGscriptFromRemote, Qt::UniqueConnection);
    connect(ui->cbProgramThreadID, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeSelectedEditorThread(int)));

    //----- Gcode Editor -----

    // T?o m?t QPalette m?i t? QPalette hi?n t?i c?a textEdit
    QPalette p = ui->pteGcodeArea->palette();

    // Thi?t l?p m�u cho van b?n
    p.setColor(QPalette::Text, QColor("#888888"));

    // �p d?ng QPalette m?i cho textEdit
    ui->pteGcodeArea->setPalette(p);

    highlighter = new GCodeHighlighter(ui->pteGcodeArea->document());

    ui->pteGcodeArea->setTabWidth(4);
    InitGScriptWorkspace();

    // ------- Gcode Explorer -----

    QString openPath = QCoreApplication::applicationDirPath() + "/gcode";

    QDir dir(openPath);
    if (!dir.exists())
        dir.mkpath(openPath);

    ui->leGcodeExplorer->setText(openPath);

    explorerModel.setRootPath(QDir::currentPath());
    ui->tvGcodeExplorer->setModel(&explorerModel);
    ui->tvGcodeExplorer->setRootIndex(explorerModel.index(openPath));

    ui->tvGcodeExplorer->setHeaderHidden(true); // Hi?n th? header
    ui->tvGcodeExplorer->header()->setSectionResizeMode(0, QHeaderView::Stretch); // Ch?nh d? r?ng c?t
    ui->tvGcodeExplorer->header()->setSectionHidden(1, true); // ?n c?t Size
    ui->tvGcodeExplorer->header()->setSectionHidden(2, true); // ?n c?t Type
    ui->tvGcodeExplorer->header()->setSectionHidden(3, true); // ?n c?t Type

    QObject::connect(ui->tvGcodeExplorer, &QTreeView::clicked, this, &RobotWindow::LoadGcodeFromFileToEditor);

    QObject::connect(ui->tbBackGcodeFolder, &QPushButton::clicked, this, &RobotWindow::BackParentExplorer);

    QObject::connect(ui->tbNewGcodeFile, &QPushButton::clicked, this, &RobotWindow::CreateNewGcodeFile);

    QObject::connect(ui->tbOpenGcodePath, &QPushButton::clicked, this, &RobotWindow::SelectGcodeExplorer);

    QObject::connect(ui->tbRefreshExplorer, &QPushButton::clicked, this, &RobotWindow::RefreshExplorer);

    QObject::connect(ui->tbDeleteGcodeFile, &QPushButton::clicked, this, &RobotWindow::DeleteGcodeFile);
    
    // Initialize GScript Help documentation
    InitGScriptHelp();
}

void RobotWindow::InitExternalVisionUI()
{
    ui->cbSendingImageMethod->clear();
    ui->cbSendingImageMethod->addItem(QStringLiteral("DXV1 JSON + JPEG/Base64 (required)"));
    ui->cbSendingImageMethod->setEnabled(false);
    ui->cbSendingImageMethod->setToolTip(
        tr("External Vision tracking always uses the correlated DXV1 protocol."));
    ui->pbExternalScriptHelp->setToolTip(tr("Open the External Vision setup and protocol guide"));
    ui->pbOpenScriptExample->setToolTip(tr("Open the supplied DXV1 Python examples"));
    ui->pbRunExternalScript->setToolTip(tr("Start or stop the selected Python detector"));
    ui->pbExternalScriptOpen->setToolTip(tr("Select a Python detector script"));

    if (QGridLayout* layout = qobject_cast<QGridLayout*>(ui->fExternalScriptPanel->layout())) {
        QLabel* statusTitle = new QLabel(tr("Detector status"), ui->fExternalScriptPanel);
        externalVisionStatusLabel = new QLabel(ui->fExternalScriptPanel);
        externalVisionStatusLabel->setWordWrap(true);
        externalVisionMetricsLabel = new QLabel(ui->fExternalScriptPanel);
        externalVisionMetricsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        externalVisionMetricsLabel->setStyleSheet(QStringLiteral("color: rgb(170, 170, 170);"));
        layout->addWidget(statusTitle, 8, 0);
        layout->addWidget(externalVisionStatusLabel, 8, 1, 1, 4);
        layout->addWidget(new QLabel(tr("Activity"), ui->fExternalScriptPanel), 9, 0);
        layout->addWidget(externalVisionMetricsLabel, 9, 1, 1, 4);

        externalVisionPythonEdit = new QLineEdit(ui->fExternalScriptPanel);
        externalVisionPythonEdit->setText(
            QSettings().value(QStringLiteral("ExternalVision/PythonExecutable"),
                              QStringLiteral("python")).toString());
        externalVisionPythonEdit->setToolTip(
            tr("Python executable name or full path used by the Play button"));
        QPushButton* pythonBrowse = new QPushButton(QStringLiteral("..."),
                                                    ui->fExternalScriptPanel);
        pythonBrowse->setMaximumWidth(32);
        layout->addWidget(new QLabel(tr("Python executable"), ui->fExternalScriptPanel), 10, 0);
        layout->addWidget(externalVisionPythonEdit, 10, 1, 1, 3);
        layout->addWidget(pythonBrowse, 10, 4);
        connect(externalVisionPythonEdit, &QLineEdit::editingFinished, this, [this]() {
            QSettings().setValue(QStringLiteral("ExternalVision/PythonExecutable"),
                                 externalVisionPythonEdit->text().trimmed());
        });
        connect(pythonBrowse, &QPushButton::clicked, this, [this]() {
            const QString executable = QFileDialog::getOpenFileName(
                this, tr("Select Python executable"), QString(),
#ifdef Q_OS_WIN
                tr("Executable (*.exe);;All files (*)"));
#else
                tr("All files (*)"));
#endif
            if (!executable.isEmpty()) {
                externalVisionPythonEdit->setText(QDir::toNativeSeparators(executable));
                QSettings().setValue(QStringLiteral("ExternalVision/PythonExecutable"),
                                     executable);
            }
        });
    }

    const quint16 serverPort = ConnectionManager && ConnectionManager->Server
        ? ConnectionManager->Server->serverPort() : 0;
    setExternalVisionStatus(
        QStringLiteral("NOT CONNECTED"),
        tr("Listening at %1:%2").arg(ConnectionManager->hostAddress).arg(serverPort),
        QStringLiteral("#e0a030"));
    if (externalVisionMetricsLabel)
        externalVisionMetricsLabel->setText(tr("Frames sent: 0 | Results: 0 | Last latency: --"));

    connect(ConnectionManager, &SocketConnectionManager::externalVisionStatusChanged,
            this, [this](bool connected, const QString& peer) {
        if (connected) {
            setExternalVisionStatus(QStringLiteral("CONNECTED"), peer,
                                    QStringLiteral("#4caf50"));
        } else {
            setExternalVisionStatus(QStringLiteral("NOT CONNECTED"),
                                    tr("Detector disconnected: %1").arg(peer),
                                    QStringLiteral("#e0a030"));
        }
    });
    connect(ConnectionManager, &SocketConnectionManager::externalVisionFrameSent,
            this, [this](quint64 frameId, quint64 requestId, int trackingId, qint64 payloadBytes) {
        ++externalVisionFramesSent;
        QHash<QString, QVariant> values;
        values.insert(QStringLiteral("ExternalVision.FramesSent"),
                      QVariant::fromValue<qulonglong>(externalVisionFramesSent));
        values.insert(QStringLiteral("ExternalVision.LastFrameId"),
                      QVariant::fromValue<qulonglong>(frameId));
        values.insert(QStringLiteral("ExternalVision.LastRequestId"),
                      QVariant::fromValue<qulonglong>(requestId));
        values.insert(QStringLiteral("ExternalVision.LastTrackingId"), trackingId);
        values.insert(QStringLiteral("ExternalVision.LastPayloadBytes"), payloadBytes);
        VariableManager::instance().updateBatchScoped(
            ProjectName, values, VariableManager::Persistence::Runtime);
        if (externalVisionMetricsLabel) {
            externalVisionMetricsLabel->setText(
                tr("Frames sent: %1 | Results: %2 | Last TX: F%3/R%4/T%5 (%6 KB)")
                    .arg(externalVisionFramesSent).arg(externalVisionResultsReceived)
                    .arg(frameId).arg(requestId).arg(trackingId)
                    .arg(payloadBytes / 1024.0, 0, 'f', 1));
        }
    });
    connect(ConnectionManager, &SocketConnectionManager::externalVisionResultReceived,
            this, [this](quint64 frameId, quint64 requestId, int trackingId,
                         int objectCount, qint64 latencyMs) {
        ++externalVisionResultsReceived;
        QHash<QString, QVariant> values;
        values.insert(QStringLiteral("ExternalVision.ResultsReceived"),
                      QVariant::fromValue<qulonglong>(externalVisionResultsReceived));
        values.insert(QStringLiteral("ExternalVision.LastFrameId"),
                      QVariant::fromValue<qulonglong>(frameId));
        values.insert(QStringLiteral("ExternalVision.LastRequestId"),
                      QVariant::fromValue<qulonglong>(requestId));
        values.insert(QStringLiteral("ExternalVision.LastTrackingId"), trackingId);
        values.insert(QStringLiteral("ExternalVision.LastObjectCount"), objectCount);
        values.insert(QStringLiteral("ExternalVision.LastLatencyMs"), latencyMs);
        VariableManager::instance().updateBatchScoped(
            ProjectName, values, VariableManager::Persistence::Runtime);
        setExternalVisionStatus(
            QStringLiteral("CONNECTED"),
            tr("Last result: %1 object(s), frame %2").arg(objectCount).arg(frameId),
            QStringLiteral("#4caf50"));
        if (externalVisionMetricsLabel) {
            const QString latency = latencyMs >= 0 ? tr("%1 ms").arg(latencyMs)
                                                   : QStringLiteral("--");
            externalVisionMetricsLabel->setText(
                tr("Frames sent: %1 | Results: %2 | Last: F%3/R%4/T%5 | Latency: %6")
                    .arg(externalVisionFramesSent).arg(externalVisionResultsReceived)
                    .arg(frameId).arg(requestId).arg(trackingId).arg(latency));
        }
    });
    connect(ConnectionManager, &SocketConnectionManager::externalVisionProtocolError,
            this, [this](const QString& peer, const QString& message) {
        setExternalVisionStatus(QStringLiteral("PROTOCOL ERROR"),
                                tr("%1: %2").arg(peer, message),
                                QStringLiteral("#ef5350"));
        SoftwareLog(QStringLiteral("External Vision error: %1: %2").arg(peer, message));
    });
    if (m_imagePipelineController) {
        connect(m_imagePipelineController, &ImagePipelineController::externalResponseIgnored,
                this, [this](quint64 frameId, quint64 requestId, int trackingId,
                             const QString& reason) {
            setExternalVisionStatus(
                QStringLiteral("STALE RESULT IGNORED"),
                tr("F%1/R%2/T%3: %4").arg(frameId).arg(requestId).arg(trackingId).arg(reason),
                QStringLiteral("#ff9800"));
        });
    }

    connect(ui->lePythonUrl, &QLineEdit::editingFinished, this, [this]() {
        QString detectingKey = ui->cbSelectedDetecting->currentText();
        if (detectingKey.isEmpty())
            detectingKey = QStringLiteral("tracking0");
        VariableManager::instance().updateVarScoped(
            ProjectName, detectingKey + QStringLiteral(".ExternalVision.Script"),
            ui->lePythonUrl->text().trimmed());
    });
}

void RobotWindow::setExternalVisionStatus(const QString& state, const QString& detail,
                                           const QString& color)
{
    QHash<QString, QVariant> values;
    values.insert(QStringLiteral("ExternalVision.State"), state);
    values.insert(QStringLiteral("ExternalVision.Detail"), detail);
    values.insert(QStringLiteral("ExternalVision.Connected"), state == QStringLiteral("CONNECTED"));
    values.insert(QStringLiteral("ExternalVision.UpdatedAt"),
                  QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    VariableManager::instance().updateBatchScoped(
        ProjectName, values, VariableManager::Persistence::Runtime);

    if (!externalVisionStatusLabel)
        return;
    externalVisionStatusLabel->setText(
        detail.isEmpty() ? state : QStringLiteral("%1 — %2").arg(state, detail));
    externalVisionStatusLabel->setStyleSheet(
        QStringLiteral("color: %1; font-weight: bold;").arg(color));
}

void RobotWindow::InitGScriptWorkspace()
{
    gscriptValidationTimer = new QTimer(this);
    gscriptValidationTimer->setSingleShot(true);
    gscriptValidationTimer->setInterval(350);
    connect(gscriptValidationTimer, &QTimer::timeout,
            this, &RobotWindow::ValidateGScriptNow);

    gscriptCompletionRefreshTimer = new QTimer(this);
    gscriptCompletionRefreshTimer->setSingleShot(true);
    gscriptCompletionRefreshTimer->setInterval(750);
    connect(gscriptCompletionRefreshTimer, &QTimer::timeout,
            this, &RobotWindow::RefreshGScriptAssistant);

    QWidget* programTab = ui->twGcodeEditor->widget(0);
    if (!programTab)
        return;
    QVBoxLayout* programLayout = qobject_cast<QVBoxLayout*>(programTab->layout());
    if (!programLayout)
        return;

    QFrame* statusBar = new QFrame(programTab);
    statusBar->setObjectName("gscriptStatusBar");
    statusBar->setStyleSheet(
        "QFrame#gscriptStatusBar { background: #252526; border-top: 1px solid #3c3c3c; }"
        "QLabel { color: #d4d4d4; padding: 2px 6px; }"
        "QPushButton { padding: 3px 10px; }");
    QHBoxLayout* statusLayout = new QHBoxLayout(statusBar);
    statusLayout->setContentsMargins(6, 3, 6, 3);
    statusLayout->setSpacing(8);

    gscriptStatusLabel = new QLabel(tr("Ready"), statusBar);
    gscriptStatusLabel->setObjectName("gscriptStatusLabel");
    cellStateLabel = new QLabel(statusBar);
    cellStateLabel->setObjectName("cellStateLabel");
    cellResetButton = new QPushButton(tr("Reset fault"), statusBar);
    cellResetButton->setObjectName("cellResetButton");
    cellResetButton->setVisible(false);
    cellResetButton->setToolTip(
        tr("Acknowledge a software fault after external safety and hardware conditions are verified"));
    gscriptSignatureLabel = new QLabel(statusBar);
    gscriptSignatureLabel->setObjectName("gscriptSignatureLabel");
    gscriptSignatureLabel->setStyleSheet("color: #9cdcfe;");
    gscriptSignatureLabel->setMinimumWidth(220);
    gscriptSignatureLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    gscriptCursorLabel = new QLabel(tr("Ln 1, Col 1"), statusBar);
    gscriptTemplateButton = new QPushButton(tr("New from template"), statusBar);
    gscriptTemplateButton->setToolTip(
        tr("Generate a validated vision or robot worker skeleton"));
    gscriptValidateButton = new QPushButton(tr("Validate"), statusBar);
    gscriptValidateButton->setToolTip(tr("Analyze the program without moving any device"));
    statusLayout->addWidget(cellStateLabel);
    statusLayout->addWidget(cellResetButton);
    statusLayout->addWidget(gscriptStatusLabel, 1);
    statusLayout->addWidget(gscriptSignatureLabel, 2);
    statusLayout->addWidget(gscriptCursorLabel);
    statusLayout->addWidget(gscriptTemplateButton);
    statusLayout->addWidget(gscriptValidateButton);

    gscriptInspectionTabs = new QTabWidget(programTab);
    gscriptInspectionTabs->setObjectName("gscriptInspectionTabs");
    gscriptInspectionTabs->setMaximumHeight(190);
    gscriptInspectionTabs->setDocumentMode(true);

    QWidget* problemsPage = new QWidget(gscriptInspectionTabs);
    QVBoxLayout* problemsLayout = new QVBoxLayout(problemsPage);
    problemsLayout->setContentsMargins(0, 0, 0, 0);
    gscriptProblemsTable = new QTableWidget(0, 4, problemsPage);
    gscriptProblemsTable->setObjectName("gscriptProblemsTable");
    gscriptProblemsTable->setHorizontalHeaderLabels(
        {tr("Severity"), tr("Line"), tr("Code"), tr("Message")});
    gscriptProblemsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    gscriptProblemsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    gscriptProblemsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    gscriptProblemsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    gscriptProblemsTable->verticalHeader()->setVisible(false);
    gscriptProblemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    gscriptProblemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    gscriptProblemsTable->setAlternatingRowColors(true);
    problemsLayout->addWidget(gscriptProblemsTable);
    gscriptInspectionTabs->addTab(problemsPage, tr("Problems (0)"));

    QWidget* watchPage = new QWidget(gscriptInspectionTabs);
    QVBoxLayout* watchLayout = new QVBoxLayout(watchPage);
    watchLayout->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout* watchControls = new QHBoxLayout;
    gscriptWatchEdit = new QLineEdit(watchPage);
    gscriptWatchEdit->setPlaceholderText(tr("Pin variable, e.g. Tracking.0.State"));
    QPushButton* addWatchButton = new QPushButton(tr("Add"), watchPage);
    QPushButton* removeWatchButton = new QPushButton(tr("Remove"), watchPage);
    watchControls->addWidget(gscriptWatchEdit, 1);
    watchControls->addWidget(addWatchButton);
    watchControls->addWidget(removeWatchButton);
    gscriptWatchTable = new QTableWidget(0, 3, watchPage);
    gscriptWatchTable->setObjectName("gscriptWatchTable");
    gscriptWatchTable->setHorizontalHeaderLabels({tr("Variable"), tr("Value"), tr("Type")});
    gscriptWatchTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    gscriptWatchTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    gscriptWatchTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    gscriptWatchTable->verticalHeader()->setVisible(false);
    gscriptWatchTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    gscriptWatchTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    watchLayout->addLayout(watchControls);
    watchLayout->addWidget(gscriptWatchTable);
    gscriptInspectionTabs->addTab(watchPage, tr("Watch"));

    QWidget* threadsPage = new QWidget(gscriptInspectionTabs);
    QVBoxLayout* threadsLayout = new QVBoxLayout(threadsPage);
    threadsLayout->setContentsMargins(0, 0, 0, 0);
    gscriptThreadTable = new QTableWidget(0, 5, threadsPage);
    gscriptThreadTable->setObjectName("gscriptThreadTable");
    gscriptThreadTable->setHorizontalHeaderLabels(
        {tr("Thread"), tr("State"), tr("Line"), tr("Device"), tr("Detail")});
    for (int column = 0; column < 4; ++column)
        gscriptThreadTable->horizontalHeader()->setSectionResizeMode(
            column, QHeaderView::ResizeToContents);
    gscriptThreadTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    gscriptThreadTable->verticalHeader()->setVisible(false);
    gscriptThreadTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    gscriptThreadTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    threadsLayout->addWidget(gscriptThreadTable);
    gscriptInspectionTabs->addTab(threadsPage, tr("Threads"));
    connect(gscriptThreadTable, &QTableWidget::cellDoubleClicked,
            this, [this](int row, int) {
        if (row >= 0 && row < GcodeScripts.size())
            ui->cbProgramThreadID->setCurrentIndex(row);
    });

    programLayout->addWidget(gscriptInspectionTabs);
    programLayout->addWidget(statusBar);

    connect(gscriptValidateButton, &QPushButton::clicked,
            this, &RobotWindow::ValidateGScriptNow);
    connect(cellResetButton, &QPushButton::clicked, this, [this]() {
        if (!m_cellSupervisor || m_cellSupervisor->state() != CellSupervisor::State::Faulted)
            return;
        const QMessageBox::StandardButton answer = QMessageBox::warning(
            this, tr("Reset software fault"),
            tr("Confirm that E-stop, guards, robot controllers, conveyor and end effector are safe before resetting the software cell state."),
            QMessageBox::Reset | QMessageBox::Cancel, QMessageBox::Cancel);
        if (answer == QMessageBox::Reset)
            m_cellSupervisor->ResetFault();
    });
    connect(gscriptTemplateButton, &QPushButton::clicked,
            this, &RobotWindow::ShowGScriptTemplateWizard);
    connect(gscriptProblemsTable, &QTableWidget::cellDoubleClicked,
            this, [this](int row, int) {
        if (row >= 0 && row < gscriptDiagnostics.size())
            ui->pteGcodeArea->goToLine(gscriptDiagnostics.at(row).line);
    });
    connect(ui->pteGcodeArea, &QTextEdit::cursorPositionChanged, this, [this]() {
        const QTextCursor cursor = ui->pteGcodeArea->textCursor();
        if (gscriptCursorLabel)
            gscriptCursorLabel->setText(tr("Ln %1, Col %2")
                .arg(cursor.blockNumber() + 1).arg(cursor.positionInBlock() + 1));
        if (gscriptSignatureLabel) {
            const QString signature = GScriptEditorSupport::signatureHelp(
                cursor.block().text(), cursor.positionInBlock());
            gscriptSignatureLabel->setText(signature);
            gscriptSignatureLabel->setToolTip(signature);
        }
    });
    connect(ui->pteGcodeArea, &QTextEdit::textChanged, this, [this]() {
        if (gscriptCompletionRefreshTimer && !gscriptCompletionRefreshTimer->isActive())
            gscriptCompletionRefreshTimer->start();
    });

    auto pinWatch = [this]() {
        if (!gscriptWatchEdit)
            return;
        const QString name = GScriptEditorSupport::normalizeWatchName(gscriptWatchEdit->text());
        if (name.isEmpty()) {
            gscriptWatchEdit->setStyleSheet("border: 1px solid #ff6b6b;");
            return;
        }
        gscriptWatchEdit->setStyleSheet(QString());
        gscriptPinnedWatch.insert(name);
        gscriptWatchEdit->clear();
        RefreshGScriptRuntimePanels();
    };
    connect(addWatchButton, &QPushButton::clicked, this, pinWatch);
    connect(gscriptWatchEdit, &QLineEdit::returnPressed, this, pinWatch);
    connect(removeWatchButton, &QPushButton::clicked, this, [this]() {
        if (!gscriptWatchTable)
            return;
        const auto rows = gscriptWatchTable->selectionModel()->selectedRows();
        for (const QModelIndex& row : rows) {
            if (QTableWidgetItem* item = gscriptWatchTable->item(row.row(), 0))
                gscriptPinnedWatch.remove(item->data(Qt::UserRole).toString());
        }
        RefreshGScriptRuntimePanels();
    });

    VariableManager& variables = VariableManager::instance();
    auto scheduleCompletionRefresh = [this]() {
        if (gscriptCompletionRefreshTimer && !gscriptCompletionRefreshTimer->isActive())
            gscriptCompletionRefreshTimer->start();
    };
    connect(&variables, &VariableManager::varAdded, this,
            [this, scheduleCompletionRefresh](const QString& key, const QVariant&) {
        if (!gscriptKnownCompletionKeys.contains(key))
            scheduleCompletionRefresh();
    });
    connect(&variables, &VariableManager::varsUpdated, this,
            [this, scheduleCompletionRefresh](const QHash<QString, QVariant>& values) {
        for (auto it = values.cbegin(); it != values.cend(); ++it) {
            if (!gscriptKnownCompletionKeys.contains(it.key())) {
                scheduleCompletionRefresh();
                break;
            }
        }
    });
    connect(&variables, &VariableManager::varsRemoved, this,
            [scheduleCompletionRefresh](const QStringList&) {
        scheduleCompletionRefresh();
    });

    gscriptRuntimeUiTimer = new QTimer(this);
    gscriptRuntimeUiTimer->setTimerType(Qt::CoarseTimer);
    gscriptRuntimeUiTimer->setInterval(200);
    connect(gscriptRuntimeUiTimer, &QTimer::timeout,
            this, &RobotWindow::RefreshGScriptRuntimePanels);
    gscriptRuntimeUiTimer->start();

    ui->pbExecuteGcodes->setText(tr("Run"));
    ui->pbExecuteGcodes->setToolTip(tr("Validate and run the complete program"));
    ui->cbEditGcodeLock->setText(tr("Safe line run"));
    ui->cbEditGcodeLock->setToolTip(
        tr("When enabled, clicking a source line can execute only that line"));
    if (m_cellSupervisor)
        updateCellStateUi(m_cellSupervisor->state(), m_cellSupervisor->stateName(),
                          m_cellSupervisor->faultReason());
    RefreshGScriptAssistant();
    RefreshGScriptRuntimePanels();
    ValidateGScriptNow();
}

void RobotWindow::RefreshGScriptAssistant()
{
    if (!ui || !ui->pteGcodeArea)
        return;

    QStringList completions = GScriptEditorSupport::builtInCompletions();
    const QString root = VariableManager::normalizeKey(ProjectName);
    const QString prefix = root.isEmpty() ? QString() : root + '.';
    const QStringList variableKeys = VariableManager::instance().keys(ProjectName, true);
    gscriptKnownCompletionKeys.clear();
    for (const QString& key : variableKeys)
        gscriptKnownCompletionKeys.insert(key);
    int addedVariables = 0;
    for (const QString& absoluteKey : variableKeys) {
        QString relative = absoluteKey;
        if (!prefix.isEmpty() && relative.startsWith(prefix))
            relative.remove(0, prefix.size());
        if (relative.isEmpty() || relative.size() > 160)
            continue;
        completions.append('#' + relative);
        if (++addedVariables >= 6000)
            break;
    }
    const QStringList referenced = GScriptEditorSupport::referencedVariables(
        ui->pteGcodeArea->toPlainText());
    for (const QString& name : referenced)
        completions.append('#' + name);

    ui->pteGcodeArea->setCompletionWords(completions);
}

void RobotWindow::RefreshGScriptRuntimePanels()
{
    if (!ui)
        return;

    VariableManager& variables = VariableManager::instance();
    if (gscriptWatchTable && ui->pteGcodeArea) {
        const int documentRevision = ui->pteGcodeArea->document()->revision();
        if (documentRevision != gscriptWatchDocumentRevision) {
            gscriptAutomaticWatch = GScriptEditorSupport::referencedVariables(
                ui->pteGcodeArea->toPlainText());
            gscriptWatchDocumentRevision = documentRevision;
        }
        QSet<QString> watched = gscriptPinnedWatch;
        for (const QString& name : gscriptAutomaticWatch)
            watched.insert(name);
        QStringList names(watched.cbegin(), watched.cend());
        names.sort(Qt::CaseInsensitive);

        QSet<QString> selectedNames;
        const auto selectedRows = gscriptWatchTable->selectionModel()->selectedRows();
        for (const QModelIndex& selectedRow : selectedRows) {
            if (QTableWidgetItem* item = gscriptWatchTable->item(selectedRow.row(), 0))
                selectedNames.insert(item->data(Qt::UserRole).toString());
        }

        gscriptWatchTable->setUpdatesEnabled(false);
        gscriptWatchTable->setRowCount(names.size());
        for (int row = 0; row < names.size(); ++row) {
            const QString& name = names.at(row);
            const QVariant value = variables.getVarScoped(ProjectName, name);
            QTableWidgetItem* nameItem = new QTableWidgetItem('#' + name);
            nameItem->setData(Qt::UserRole, name);
            if (!gscriptPinnedWatch.contains(name)) {
                QFont automaticFont = nameItem->font();
                automaticFont.setItalic(true);
                nameItem->setFont(automaticFont);
                nameItem->setToolTip(tr("Automatically watched because the variable appears in the editor"));
            }

            QString displayValue;
            QString typeName;
            if (!value.isValid()) {
                displayValue = tr("<not published>");
                typeName = tr("unknown/local");
            } else {
                displayValue = value.toString();
                if (displayValue.isEmpty() && value.userType() != QMetaType::QString) {
                    QDebug debug(&displayValue);
                    debug.noquote().nospace() << value;
                }
                typeName = QString::fromLatin1(value.typeName() ? value.typeName() : "QVariant");
            }
            QTableWidgetItem* valueItem = new QTableWidgetItem(displayValue);
            valueItem->setToolTip(displayValue);
            if (!value.isValid())
                valueItem->setForeground(QColor("#888888"));
            gscriptWatchTable->setItem(row, 0, nameItem);
            gscriptWatchTable->setItem(row, 1, valueItem);
            gscriptWatchTable->setItem(row, 2, new QTableWidgetItem(typeName));
            if (selectedNames.contains(name))
                gscriptWatchTable->selectRow(row);
        }
        gscriptWatchTable->setUpdatesEnabled(true);
    }

    if (gscriptThreadTable) {
        gscriptThreadTable->setUpdatesEnabled(false);
        gscriptThreadTable->setRowCount(GcodeScripts.size());
        for (int row = 0; row < GcodeScripts.size(); ++row) {
            GcodeScript* script = GcodeScripts.at(row);
            const QString id = script ? script->ID : QString("thread%1").arg(row);
            const QString runtimePrefix = QString("GScript.%1.").arg(id);
            QString state = variables.getVarScoped(
                ProjectName, runtimePrefix + "State").toString();
            if (state.isEmpty() && script) {
                const QMetaEnum stateMeta = QMetaEnum::fromType<GcodeScript::ExecutionState>();
                state = QString::fromLatin1(
                    stateMeta.valueToKey(static_cast<int>(script->State())));
            }
            const QVariant line = variables.getVarScoped(
                ProjectName, runtimePrefix + "CurrentLine");
            const QString device = variables.getVarScoped(
                ProjectName, runtimePrefix + "ActiveDevice").toString();
            QString detail = variables.getVarScoped(
                ProjectName, runtimePrefix + "StateMessage").toString();
            const QString command = variables.getVarScoped(
                ProjectName, runtimePrefix + "ActiveCommand").toString();
            const QString error = variables.getVarScoped(
                ProjectName, runtimePrefix + "LastError").toString();
            if (state.compare("Faulted", Qt::CaseInsensitive) == 0 && !error.isEmpty())
                detail = error;

            QTableWidgetItem* stateItem = new QTableWidgetItem(state);
            if (state == "Running" || state == "Completed")
                stateItem->setForeground(QColor("#69d18b"));
            else if (state.startsWith("Waiting"))
                stateItem->setForeground(QColor("#73b7ff"));
            else if (state == "Faulted")
                stateItem->setForeground(QColor("#ff6b6b"));
            else if (state == "Stopping")
                stateItem->setForeground(QColor("#f0b24a"));

            QTableWidgetItem* deviceItem = new QTableWidgetItem(device);
            deviceItem->setToolTip(command);
            gscriptThreadTable->setItem(row, 0, new QTableWidgetItem(id));
            gscriptThreadTable->setItem(row, 1, stateItem);
            gscriptThreadTable->setItem(row, 2,
                new QTableWidgetItem(line.isValid() ? line.toString() : QStringLiteral("—")));
            gscriptThreadTable->setItem(row, 3, deviceItem);
            gscriptThreadTable->setItem(row, 4, new QTableWidgetItem(detail));
        }
        gscriptThreadTable->setUpdatesEnabled(true);
    }
}

void RobotWindow::ShowGScriptTemplateWizard()
{
    if (!ui || !ui->pteGcodeArea)
        return;

    QDialog dialog(this);
    dialog.setWindowTitle(tr("New G-Script from template"));
    dialog.setMinimumWidth(520);
    QVBoxLayout* root = new QVBoxLayout(&dialog);
    QLabel* explanation = new QLabel(
        tr("Generate a safe starting point. Calibration variables, zones, poses and limits must still be verified on the real cell."),
        &dialog);
    explanation->setWordWrap(true);
    root->addWidget(explanation);

    QFormLayout* form = new QFormLayout;
    QComboBox* role = new QComboBox(&dialog);
    role->addItems({tr("Vision / tracking worker"), tr("Robot pick worker")});
    QSpinBox* trackingId = new QSpinBox(&dialog);
    trackingId->setRange(0, 999);
    QSpinBox* loopDelay = new QSpinBox(&dialog);
    loopDelay->setRange(0, 60000);
    loopDelay->setValue(10);
    loopDelay->setSuffix(tr(" ms"));
    QSpinBox* robotId = new QSpinBox(&dialog);
    robotId->setRange(0, 999);
    QSpinBox* typeFilter = new QSpinBox(&dialog);
    typeFilter->setRange(-1, 999999);
    typeFilter->setSpecialValueText(tr("Any type"));
    typeFilter->setValue(-1);
    QDoubleSpinBox* minX = new QDoubleSpinBox(&dialog);
    QDoubleSpinBox* maxX = new QDoubleSpinBox(&dialog);
    QDoubleSpinBox* minY = new QDoubleSpinBox(&dialog);
    QDoubleSpinBox* maxY = new QDoubleSpinBox(&dialog);
    for (QDoubleSpinBox* spin : {minX, maxX, minY, maxY}) {
        spin->setRange(-1000000.0, 1000000.0);
        spin->setDecimals(3);
        spin->setSuffix(tr(" mm"));
    }
    minX->setValue(-180.0);
    maxX->setValue(180.0);
    minY->setValue(300.0);
    maxY->setValue(450.0);
    QCheckBox* vacuumFeedback = new QCheckBox(tr("Require vacuum confirmation"), &dialog);
    QLineEdit* vacuumVariable = new QLineEdit(QStringLiteral("Vacuum.R0.OK"), &dialog);

    form->addRow(tr("Template"), role);
    form->addRow(tr("Tracking ID"), trackingId);
    form->addRow(tr("Vision loop delay"), loopDelay);
    form->addRow(tr("Robot ID"), robotId);
    form->addRow(tr("Object type"), typeFilter);
    form->addRow(tr("Claim min X"), minX);
    form->addRow(tr("Claim max X"), maxX);
    form->addRow(tr("Claim min Y"), minY);
    form->addRow(tr("Claim max Y"), maxY);
    form->addRow(QString(), vacuumFeedback);
    form->addRow(tr("Vacuum variable"), vacuumVariable);
    root->addLayout(form);

    const QList<QWidget*> robotFields = {
        robotId, typeFilter, minX, maxX, minY, maxY, vacuumFeedback, vacuumVariable
    };
    auto updateRole = [role, loopDelay, robotFields, vacuumFeedback, vacuumVariable]() {
        const bool robotWorker = role->currentIndex() == 1;
        loopDelay->setEnabled(!robotWorker);
        for (QWidget* field : robotFields)
            field->setEnabled(robotWorker);
        vacuumVariable->setEnabled(robotWorker && vacuumFeedback->isChecked());
    };
    connect(role, QOverload<int>::of(&QComboBox::currentIndexChanged),
            &dialog, [updateRole](int) { updateRole(); });
    connect(vacuumFeedback, &QCheckBox::toggled,
            &dialog, [updateRole](bool) { updateRole(); });
    connect(robotId, QOverload<int>::of(&QSpinBox::valueChanged),
            &dialog, [vacuumVariable](int id) {
        vacuumVariable->setText(QString("Vacuum.R%1.OK").arg(id));
    });
    updateRole();

    QDialogButtonBox* buttons = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok, &dialog);
    buttons->button(QDialogButtonBox::Ok)->setText(tr("Generate"));
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    root->addWidget(buttons);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QString generated;
    if (role->currentIndex() == 0) {
        generated = GScriptEditorSupport::visionTemplate(
            trackingId->value(), loopDelay->value());
    } else {
        GScriptRobotTemplateOptions options;
        options.trackingId = trackingId->value();
        options.robotId = robotId->value();
        options.typeFilter = typeFilter->value();
        options.minX = minX->value();
        options.maxX = maxX->value();
        options.minY = minY->value();
        options.maxY = maxY->value();
        options.useVacuumFeedback = vacuumFeedback->isChecked();
        options.vacuumVariable = vacuumVariable->text();
        generated = GScriptEditorSupport::robotTemplate(options);
    }

    const QString current = ui->pteGcodeArea->toPlainText();
    if (!current.trimmed().isEmpty()) {
        QMessageBox choice(this);
        choice.setIcon(QMessageBox::Question);
        choice.setWindowTitle(tr("Insert generated G-Script"));
        choice.setText(tr("The current editor is not empty."));
        QPushButton* replaceButton = choice.addButton(tr("Replace editor"), QMessageBox::AcceptRole);
        QPushButton* appendButton = choice.addButton(tr("Append"), QMessageBox::ActionRole);
        choice.addButton(QMessageBox::Cancel);
        choice.setDefaultButton(replaceButton);
        choice.exec();
        if (choice.clickedButton() == replaceButton)
            ui->pteGcodeArea->setPlainText(generated);
        else if (choice.clickedButton() == appendButton)
            ui->pteGcodeArea->setPlainText(current.trimmed() + "\n\n" + generated);
        else
            return;
    } else {
        ui->pteGcodeArea->setPlainText(generated);
    }
    ui->pteGcodeArea->moveCursor(QTextCursor::Start);
    ValidateGScriptNow();
    RefreshGScriptAssistant();
    RefreshGScriptRuntimePanels();
}

void RobotWindow::InitGScriptHelp()
{
    const QStringList docCandidates = {
        QStringLiteral(":/docs/gscript-runtime.md"),
        QCoreApplication::applicationDirPath() + "/docs/gscript-runtime.md",
        QDir::current().absoluteFilePath("docs/gscript-runtime.md"),
        QStringLiteral(":/GScript_Documentation.html"),
        QCoreApplication::applicationDirPath() + "/GScript_Documentation.html",
        QDir::current().absoluteFilePath("GScript_Documentation.html")
    };

    QString documentContent;
    QString loadedFrom;

    for (const QString &path : docCandidates)
    {
        QFile htmlFile(path);
        if (htmlFile.exists() && htmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            documentContent = QString::fromUtf8(htmlFile.readAll());
            if (!documentContent.isEmpty() && documentContent.at(0) == QChar(0xFEFF)) {
                documentContent.remove(0, 1);
            }
            htmlFile.close();
            loadedFrom = path;
            break;
        }
    }

    if (!documentContent.isEmpty()) {
        if (loadedFrom.endsWith(QStringLiteral(".md"), Qt::CaseInsensitive))
            ui->tbGcodeScriptHelp->setMarkdown(documentContent);
        else
            ui->tbGcodeScriptHelp->setHtml(documentContent);
        SoftwareLog("GScript Help documentation loaded from: " + loadedFrom);
    } else {
        QString errorMessage = QString(
            "<html><body style='font-family: Arial; color: #ff6b6b; text-align: center; padding: 50px;'>"
            "<h2>GScript Documentation Not Found</h2>"
            "<p>Could not load: <strong>%1</strong></p>"
            "<p>Please ensure GScript_Documentation.html is available in the application folder or resources.</p>"
            "</body></html>"
        ).arg(docCandidates.at(1));

        ui->tbGcodeScriptHelp->setHtml(errorMessage);
        SoftwareLog("GScript Help: HTML file not found in resources or file system.");
    }

    ui->tbGcodeScriptHelp->setOpenExternalLinks(false);
    ui->tbGcodeScriptHelp->setSearchPaths(QStringList()
                                          << ":/"
                                          << QCoreApplication::applicationDirPath()
                                          << QDir::currentPath());
}

void RobotWindow::InitUIController()
{
    connect(&UpdateUITimer, &QTimer::timeout, this, &RobotWindow::UpdateRobotPositionToUI);
    UpdateUITimer.start(100);

    connect(ui->pbHome, &QPushButton::clicked, this, [=](){emit Send(DeviceManager::ROBOT, "G28");});    

    connect(ui->tbCopyRobotPosition, &QPushButton::clicked, [=]()
    {
        // Copy gi� tr? v�o clipboard
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

void RobotWindow::InitEvents()
{
    // -------- Debug Log --------
//    connect(ui->tbExpandLogBox, &QToolButton::toggled, this, &RobotWindow::ExpandLogBox);


    // ----------GScript----------
    connect(ui->pbSaveGcode, SIGNAL(clicked(bool)), this, SLOT(SaveProgram()));


    connect(ui->pbExecuteGcodes, SIGNAL(clicked(bool)), this, SLOT(ExecuteProgram()));
    connect(ui->pbBlockly, &QToolButton::clicked, this, &RobotWindow::OpenBlocklyEditor);
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
    connect(ui->pbExternalScriptHelp, &QPushButton::clicked,
            this, &RobotWindow::OpenExternalVisionGuide);
    connect(ui->pbOpenScriptExample, &QPushButton::clicked,
            this, &RobotWindow::OpenExternalVisionExample);

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
        // Copy gi� tr? v�o clipboard
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
        if (TrackingManagerInstance && !TrackingManagerInstance->Trackings.isEmpty()) {
            QMetaObject::invokeMethod(
                TrackingManagerInstance->Trackings.at(0),
                "SetUpdateTestPoint", Qt::QueuedConnection,
                Q_ARG(bool, checked));
        }
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
            m_pointToolController->pastePointValues(ui->leMappingSourcePoint1X, ui->leMappingSourcePoint1Y, nullptr);
        }
    });
    connect(ui->tbPasteSourcePoint2, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leMappingSourcePoint2X, ui->leMappingSourcePoint2Y, nullptr);
        }
    });
    connect(ui->tbPasteDestinationPoint1, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leMappingDestinationPoint1X, ui->leMappingDestinationPoint1Y, nullptr);
        }
    });
    connect(ui->tbPasteDestinationPoint2, &QPushButton::clicked, [=]()
    {
        if (m_pointToolController) {
            m_pointToolController->pastePointValues(ui->leMappingDestinationPoint2X, ui->leMappingDestinationPoint2Y, nullptr);
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

        // T?o m?t QVariant t? m?ng v� luu tr? ma tr?n
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
        const int selectedEncoderID = ui->cbSelectedTracking->currentIndex();
        if (!TrackingManagerInstance || selectedEncoderID < 0 ||
            selectedEncoderID >= TrackingManagerInstance->Trackings.count())
            return;

        float x = ui->leObjectX->text().isEmpty() ? QRandomGenerator::global()->generate() % 1000 : ui->leObjectX->text().toFloat();
        float y = ui->leObjectY->text().isEmpty() ? QRandomGenerator::global()->generate() % 1000 : ui->leObjectY->text().toFloat();
        float z = ui->leObjectZ->text().isEmpty() ? QRandomGenerator::global()->generate() % 1000 : ui->leObjectZ->text().toFloat();

        std::default_random_engine generator;  // You can seed it if you want: generator(seed);
        std::uniform_int_distribution<int> distribution(-180, 180);
        int angle = distribution(generator);

        if (ui->leObjectListName->text() ==
            TrackingManagerInstance->Trackings.at(selectedEncoderID)->GetListName())
        {
            QVector3D position(x, y, z);
            ObjectInfo object(-1, 0, position, 20, 40, angle); // UID will be assigned automatically

            // Add object directly to TrackedObjects (allows multiple objects)
            TrackingManagerInstance->AddObjectToTracking(ui->leObjectListName->text(), object);
        }
        else
        {
            QString listName = ui->leObjectListName->text();
            int counter = VariableManager::instance().getVarScoped(ProjectName, listName + ".Count", 0).toInt();
            const QString objectName = QString("%1.%2.").arg(listName).arg(counter);
            QHash<QString, QVariant> values;
            values.insert(objectName + "X", x);
            values.insert(objectName + "Y", y);
            values.insert(objectName + "Z", z);
            values.insert(objectName + "W", 20);
            values.insert(objectName + "L", 40);
            values.insert(objectName + "A", angle);
            values.insert(listName + ".Count", counter + 1);
            VariableManager::instance().updateBatchScoped(ProjectName, values);
        }
    });

    // ---- Object Detector Add Object Panel ----
    connect(ui->pbAddObjectHere, &QPushButton::clicked, this, &RobotWindow::AddObjectAtPosition);
    connect(ui->pbAddRandomObject, &QPushButton::clicked, this, &RobotWindow::AddRandomObject);
    connect(ui->pbClearAllObjects, &QPushButton::clicked, this, &RobotWindow::ClearAllTrackedObjects);

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
    connect(ui->pbEraserAll, SIGNAL(clicked(bool)), ui->lbDrawingArea, SLOT(EraserAll()));
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

void RobotWindow::OpenBlocklyEditor()
{
    if (!ConnectionManager || !ConnectionManager->WebServer) {
        QMessageBox::warning(this, tr("Web Control"),
                             tr("The web server is not ready."));
        return;
    }

    if (!ConnectionManager->WebServer->isListening()) {
        if (!ConnectionManager->WebServer->listen(QHostAddress(ConnectionManager->hostAddress), 5000)) {
            QMessageBox::warning(this, tr("Web Control"),
                                 tr("The web server could not be started."));
            return;
        }
    }

    QString host = ConnectionManager->hostAddress;
    if (host.isEmpty() || host == "0.0.0.0") {
        host = SocketConnectionManager::printLocalIpAddresses();
    }
    if (host.isEmpty()) {
        host = "127.0.0.1";
    }

    quint16 webServerPort = ConnectionManager->WebServer->serverPort();
    if (webServerPort == 0) {
        webServerPort = 5000;
    }

    quint16 blocklyPortValue = ConnectionManager->blocklyPort;
    if (blocklyPortValue == 0) {
        QMessageBox::warning(this, tr("Web Control"),
                             tr("The Blockly data server could not be started."));
        return;
    }

    const QString blocklyUrl = QString("http://%1:%2/blockly?host=%3&port=%4")
            .arg(host)
            .arg(webServerPort)
            .arg(host)
            .arg(blocklyPortValue);

    if (!QDesktopServices::openUrl(QUrl(blocklyUrl))) {
        QMessageBox::warning(this,
                             tr("Unable to Open Blockly"),
                             tr("The browser could not open this URL: %1").arg(blocklyUrl));
    } else {
        SoftwareLog(QString("Open Blockly via web server: %1").arg(blocklyUrl));
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
    if (!gcode.endsWith(QLatin1Char('\n')))
        gcode += QLatin1Char('\n');

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


    }
    StandardFormatEditor();
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
    const QString fileName = QInputDialog::getText(nullptr,
                                                   tr("Enter the file name you want to create"),
                                                   tr("Gcode file name:"),
                                                   QLineEdit::Normal,
                                                   QString(),
                                                   nullptr,
                                                   Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    // L?y du?ng d?n d?n thu m?c dang ch?n tr�n dir view

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

    // T?o d?i tu?ng QFile d? t?o file m?i v� m? file d? vi?t d? li?u v�o
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
    qDebug() << "RobotWindow::closeEvent triggered for" << ProjectName;
    bool result = CloseDialog->PopUp("Close software", "Do you want to close the software?");
    qDebug() << "RobotWindow::closeEvent dialog result =" << result;

    if(result == false)
    {
        qDebug() << "RobotWindow::closeEvent ignored";
        event->ignore();
    }
    else
    {        
        qDebug() << "RobotWindow::closeEvent accepting and calling qApp->exit()";
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
    GcodeScriptThread->ID = QString("thread%1").arg(GcodeScripts.count());
    const QString commandOwner = QStringLiteral("gscript/") + GcodeScriptThread->ID;
    GcodeScriptThread->moveToThread(new QThread(this));

    connect(GcodeScriptThread->thread(), SIGNAL(finished()), GcodeScriptThread, SLOT(deleteLater()));

    connect(GcodeScriptThread, SIGNAL(Moved(int)), this, SLOT(HighLineCurrentLine(int)));
    connect(GcodeScriptThread, &GcodeScript::SendGcodeToDevice,
            m_deviceCommandBroker,
            [this, commandOwner](const QString& device, const QString& command) {
        if (m_deviceCommandBroker) {
            m_deviceCommandBroker->Submit(commandOwner, device, command,
                                          DeviceCommandBroker::Origin::GScript,
                                          true, 120000);
        }
    });
    connect(m_deviceCommandBroker, &DeviceCommandBroker::ResponseForOwner,
            GcodeScriptThread,
            [GcodeScriptThread, commandOwner](const QString& owner,
                                               const QString& device,
                                               const QString& response,
                                               quint64) {
        if (owner == commandOwner)
            GcodeScriptThread->GetResponse(device, response);
    });
    connect(m_deviceCommandBroker, &DeviceCommandBroker::CommandRejected,
            GcodeScriptThread,
            [GcodeScriptThread, commandOwner](const QString& owner,
                                               const QString& device,
                                               const QString&,
                                               const QString& reason) {
        if (owner == commandOwner)
            GcodeScriptThread->GetResponse(device, QStringLiteral("error: ") + reason);
    });
    connect(GcodeScriptThread, &GcodeScript::Finished,
            this, [this, GcodeScriptThread, commandOwner]() {
        if (m_deviceCommandBroker)
            m_deviceCommandBroker->CancelOwner(commandOwner, QStringLiteral("G-Script finished"));
        if (m_cellSupervisor)
            m_cellSupervisor->EndAutomation(commandOwner);
        const int selected = ui->cbProgramThreadID->currentIndex();
        if (selected >= 0 && selected < GcodeScripts.size() &&
            GcodeScripts.at(selected) == GcodeScriptThread)
            ui->pbExecuteGcodes->setChecked(false);
    });
    connect(GcodeScriptThread, &GcodeScript::DiagnosticsReady,
            this, [this, GcodeScriptThread](const QList<GScriptDiagnostic>& diagnostics) {
        const int threadId = ui->cbProgramThreadID->currentIndex();
        if (threadId >= 0 && threadId < GcodeScripts.size() &&
            GcodeScripts.at(threadId) == GcodeScriptThread)
            ShowGScriptDiagnostics(diagnostics);
    });
    connect(GcodeScriptThread, &GcodeScript::ExecutionStateChanged,
            this, [this, GcodeScriptThread, commandOwner](GcodeScript::ExecutionState state,
                                                          const QString& message) {
        const bool active = state == GcodeScript::ExecutionState::Running ||
                            state == GcodeScript::ExecutionState::WaitingForDevice ||
                            state == GcodeScript::ExecutionState::WaitingForTimer ||
                            state == GcodeScript::ExecutionState::WaitingForCondition ||
                            state == GcodeScript::ExecutionState::Stopping;
        if (m_cellSupervisor) {
            if (state == GcodeScript::ExecutionState::Faulted) {
                m_cellSupervisor->ReportFault(
                    message.isEmpty() ? tr("%1 faulted").arg(GcodeScriptThread->ID) : message);
                m_cellSupervisor->EndAutomation(commandOwner);
            } else if (active) {
                if (!m_cellSupervisor->BeginAutomation(commandOwner))
                    QMetaObject::invokeMethod(GcodeScriptThread, "Stop", Qt::QueuedConnection);
            } else {
                m_cellSupervisor->EndAutomation(commandOwner);
            }
        }
        const int threadId = ui->cbProgramThreadID->currentIndex();
        if (threadId >= 0 && threadId < GcodeScripts.size() &&
            GcodeScripts.at(threadId) == GcodeScriptThread)
            UpdateGScriptExecutionState(state, message);
    });
    connect(GcodeScriptThread, SIGNAL(SendGcodeToDevice(QString, QString)), this, SLOT(UpdateGcodeValueToDeviceUI(QString, QString)));
    
    
    // Connect log message
    connect(GcodeScriptThread, &GcodeScript::LogMessage, this, &RobotWindow::handleLogMessage);
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
    connect(GcodeScriptThread, &GcodeScript::ClaimObjectRequest, TrackingManagerInstance, &TrackingManager::ClaimObject);
    connect(GcodeScriptThread, &GcodeScript::ReleaseObjectRequest, TrackingManagerInstance, &TrackingManager::ReleaseObject);
    connect(GcodeScriptThread, &GcodeScript::CompleteObjectRequest, TrackingManagerInstance, &TrackingManager::CompleteObject);
    connect(GcodeScriptThread, &GcodeScript::ChangeExternalVariable, TrackingManagerInstance, &TrackingManager::UpdateVariable);
    connect(GcodeScriptThread, &GcodeScript::AddObject, TrackingManagerInstance, &TrackingManager::AddObject);
    connect(GcodeScriptThread, SIGNAL(DeleteAllObjects(QString)), TrackingManagerInstance, SLOT(ClearObjects(QString)));


    connect(TrackingManagerInstance, &TrackingManager::GotResponse, GcodeScriptThread, &GcodeScript::GetResponse);

    GcodeScriptThread->thread()->start();

    GcodeScripts.append(GcodeScriptThread);

    connect(GcodeScriptThread, &GcodeScript::CatchVariable2, this, &RobotWindow::UpdateVarToView);
}

void RobotWindow::LoadScriptThread()
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    if (threadId < 0 || threadId >= GcodeScripts.size())
        return;
    ui->pteGcodeArea->setPlainText(GcodeScripts.at(threadId)->GetGcodeScript());
    ui->pbExecuteGcodes->setChecked(GcodeScripts.at(threadId)->IsRunning());
    UpdateGScriptExecutionState(GcodeScripts.at(threadId)->State(), QString());
    ValidateGScriptNow();
}

void RobotWindow::LoadGscriptFromRemote(QString gcode)
{
    if (!ui || !ui->pteGcodeArea)
        return;

    ui->pteGcodeArea->setPlainText(gcode);
    ui->pteGcodeArea->moveCursor(QTextCursor::Start);
    SoftwareLog(QString("Received a Blockly script from the web server (%1 characters).").arg(gcode.length()));
}

void RobotWindow::DispatchRemoteGScript(QString gcode)
{
    const int threadId = ui ? ui->cbProgramThreadID->currentIndex() : -1;
    if (threadId < 0 || threadId >= GcodeScripts.size()) {
        SoftwareLog(QStringLiteral("Remote G-Script rejected: no selected worker"));
        return;
    }
    if (m_cellSupervisor && !m_cellSupervisor->automationAllowed()) {
        SoftwareLog(tr("Remote G-Script rejected while cell is %1")
                        .arg(m_cellSupervisor->stateName()));
        return;
    }

    GcodeScript* target = GcodeScripts.at(threadId);
    QMetaObject::invokeMethod(target, "ReceivedGcode", Qt::QueuedConnection,
                              Q_ARG(QString, gcode));
    SoftwareLog(tr("Remote G-Script routed to %1 only").arg(target->ID));
}

void RobotWindow::InitTrackingThread()
{
    TrackingManagerInstance = new TrackingManager();
    TrackingManagerInstance->ProjectName = ProjectName;
    QThread* thread = new QThread(this);
    TrackingManagerInstance->moveToThread(thread);
    connect(thread, &QThread::finished, TrackingManagerInstance, &QObject::deleteLater);
    thread->start();

    AddTrackingThread();

    ObjectModel->setObjectInfoList({});

    // Frame creation must complete before the camera publishes the image. This
    // prevents a fast detector from arriving before its encoder capture slot.
    connect(CameraInstance, &Camera::StartedCapture,
            TrackingManagerInstance, &TrackingManager::SaveCapturePosition,
            Qt::BlockingQueuedConnection);
    connect(CameraInstance, &Camera::CaptureFailed,
            TrackingManagerInstance, &TrackingManager::OnCaptureFailed);
    connect(m_imagePipelineController, &ImagePipelineController::detectionsReady,
            TrackingManagerInstance, &TrackingManager::SubmitDetections);
    connect(m_imagePipelineController, &ImagePipelineController::frameRejected,
            TrackingManagerInstance, &TrackingManager::RejectVisionFrame);
    connect(DeviceManagerInstance, &DeviceManager::GotEncoderPosition, TrackingManagerInstance, &TrackingManager::SetEncoderPosition);
    connect(DeviceManagerInstance, &DeviceManager::GotEncoderPosition,
            this, &RobotWindow::OnEncoderPositionReceived, Qt::QueuedConnection);
    connect(ConnectionManager, &SocketConnectionManager::objectUpdated,
            TrackingManagerInstance, &TrackingManager::AddObject,
            Qt::UniqueConnection);
    connect(ConnectionManager, SIGNAL(blobUpdated(QStringList)),
            ImageProcessingInstance->GetNode("GetObjectsNode"), SLOT(Input(QStringList)),
            Qt::UniqueConnection);
}

void RobotWindow::AddTrackingThread()
{
    Tracking* tracking = new Tracking();
    tracking->ProjectName = ProjectName;
    tracking->ID = TrackingManagerInstance->Trackings.count();
    if (tracking->ID > 0)
        tracking->ListName = QString("#Objects%1").arg(tracking->ID + 1);

    const QString realtimePrefix = QString("tracking%1.Realtime.").arg(tracking->ID);
    tracking->publishIntervalMs = qBound(0, VariableManager::instance()
        .getVarScoped(ProjectName, realtimePrefix + "PublishIntervalMs", 50).toInt(), 5000);
    tracking->detectionStaleTimeoutMs = qBound(50, VariableManager::instance()
        .getVarScoped(ProjectName, realtimePrefix + "VisionStaleMs", 2000).toInt(), 120000);
    tracking->encoderStaleTimeoutMs = qBound(50, VariableManager::instance()
        .getVarScoped(ProjectName, realtimePrefix + "EncoderStaleMs", 2000).toInt(), 120000);
    tracking->frameTimeoutMs = qBound(100, VariableManager::instance()
        .getVarScoped(ProjectName, realtimePrefix + "FrameTimeoutMs", 3000).toInt(), 120000);
    tracking->maxPendingFrames = qBound(1, VariableManager::instance()
        .getVarScoped(ProjectName, realtimePrefix + "MaxPendingFrames", 8).toInt(), 1024);
    tracking->maxPendingEncoderReads = qBound(2, VariableManager::instance()
        .getVarScoped(ProjectName, realtimePrefix + "MaxPendingEncoderReads", 24).toInt(), 4096);

    QThread* trackingThread = new QThread(this);
    tracking->MoveToThread(trackingThread);
    connect(tracking->thread(), &QThread::finished, tracking, &QObject::deleteLater);
    connect(trackingThread, &QThread::started,
            tracking, &Tracking::StartRealtimeMonitor);


    connect(ui->pbSaveTrackingManager, &QPushButton::clicked, this, &RobotWindow::SaveTrackingManager);
    connect(ui->cbReverseEncoderValue, SIGNAL(clicked(bool)), tracking, SLOT(SetEncoderReverse(bool)));

    const QString trackingOwner = QString("tracking/%1").arg(tracking->ID);
    connect(tracking, &Tracking::SendGcodeRequest, m_deviceCommandBroker,
            [this, trackingOwner](const QString& device, const QString& command) {
        if (m_deviceCommandBroker) {
            m_deviceCommandBroker->Submit(trackingOwner, device, command,
                                          DeviceCommandBroker::Origin::Tracking,
                                          false, 5000);
        }
    });
    connect(tracking, SIGNAL(UpdateTrackingDone()), TrackingManagerInstance, SLOT(OnDoneUpdateTracking()));
    connect(tracking, &Tracking::DetectionFrameCommitted,
            TrackingManagerInstance, &TrackingManager::OnDetectionFrameCommitted);
    connect(tracking, &Tracking::DetectionFrameRejected,
            TrackingManagerInstance, &TrackingManager::OnDetectionFrameRejected);
    connect(tracking, &Tracking::SnapshotPublished, this,
            [this](int id, const QVector<ObjectInfo>& objects) {
        if (!ui || ui->cbSelectedTracking->currentIndex() != id)
            return;

        if (ui->cbAutoUpdateObjectsDisplay->currentIndex() == 1)
            ObjectModel->setObjectInfoList(objects);

        const QString prefix = QString("Tracking.%1.").arg(id);
        const VariableManager& variables = VariableManager::instance();
        const QString state = variables.getVarScoped(ProjectName, prefix + "State", "-").toString();
        const qint64 encoderAge = variables.getVarScoped(ProjectName, prefix + "EncoderAgeMs", -1).toLongLong();
        const qint64 visionAge = variables.getVarScoped(ProjectName, prefix + "VisionAgeMs", -1).toLongLong();
        const int pendingFrames = variables.getVarScoped(ProjectName, prefix + "PendingFrames", 0).toInt();
        const int pendingEncoder = variables.getVarScoped(ProjectName, prefix + "PendingEncoderReads", 0).toInt();
        const qint64 latency = variables.getVarScoped(ProjectName, prefix + "LastCommitLatencyMs", 0).toLongLong();
        const QString lastFault = variables.getVarScoped(ProjectName, prefix + "LastFault").toString();
        ui->lbTrackingRealtimeState->setText(
            tr("Runtime: %1 | encoder %2 ms | vision %3 ms | frame queue %4 | encoder queue %5 | commit %6 ms%7")
                .arg(state).arg(encoderAge).arg(visionAge).arg(pendingFrames)
                .arg(pendingEncoder).arg(latency)
                .arg(lastFault.isEmpty() ? QString() : tr(" | last fault: %1").arg(lastFault)));
    }, Qt::QueuedConnection);
    connect(tracking, &Tracking::VirtualEncoderPositionUpdated,
            this, &RobotWindow::OnEncoderPositionReceived, Qt::QueuedConnection);

    connect(tracking, SIGNAL(TestPointUpdated(QVector3D)), this, SLOT(UpdateTestPoint(QVector3D)));

    // Initialize thresholds from current UI values
    tracking->IoUThreshold = ui->leIoUThreshold->text().toFloat();
    tracking->DistanceThreshold = ui->leDistanceThreshold->text().toFloat();
    TrackingManagerInstance->Trackings.append(tracking);
    trackingThread->start();

    // Keep detection list name in sync with the currently created tracking
    if (ui && ui->leDetectingObjectListName)
    {
        ui->leDetectingObjectListName->setText(tracking->GetListName());
    }
    if (ImageProcessingInstance)
    {
        QMetaObject::invokeMethod(
            ImageProcessingInstance, "SetObjectsName", Qt::QueuedConnection,
            Q_ARG(QString, tracking->GetListName()));
    }
}

void RobotWindow::LoadTrackingThread()
{
    int id = ui->cbSelectedTracking->currentIndex();
    if (!TrackingManagerInstance || id < 0 || id >= TrackingManagerInstance->Trackings.count())
        return;
    Tracking* tracking = TrackingManagerInstance->Trackings.at(id);
    ui->leSelectedTrackingObjectList->setText(tracking->GetListName());
    ui->cbTrackingEncoderSource->setCurrentText(tracking->GetEncoderName());
    ui->leVectorName->setText(tracking->GetVectorName());

    const QString prefix = QString("tracking%1.Realtime.").arg(id);
    VariableManager& variables = VariableManager::instance();
    ui->sbTrackingPublishInterval->setValue(
        variables.getVarScoped(ProjectName, prefix + "PublishIntervalMs", 50).toInt());
    ui->sbTrackingVisionStale->setValue(
        variables.getVarScoped(ProjectName, prefix + "VisionStaleMs", 2000).toInt());
    ui->sbTrackingEncoderStale->setValue(
        variables.getVarScoped(ProjectName, prefix + "EncoderStaleMs", 2000).toInt());
    ui->sbTrackingFrameTimeout->setValue(
        variables.getVarScoped(ProjectName, prefix + "FrameTimeoutMs", 3000).toInt());
    ui->sbTrackingMaxFrames->setValue(
        variables.getVarScoped(ProjectName, prefix + "MaxPendingFrames", 8).toInt());
    ui->sbTrackingMaxEncoderReads->setValue(
        variables.getVarScoped(ProjectName, prefix + "MaxPendingEncoderReads", 24).toInt());

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
    if (index < 0 ||
        (imageSource == QStringLiteral("Industrial Camera") &&
         !industrialCameraBackendAvailable)) {
        index = ui->cbSourceForImageProvider->findText(QStringLiteral("Webcam"));
        imageSource = QStringLiteral("Webcam");
        UpdateVariable(prefix + QStringLiteral("ImageSource"), imageSource);
    }
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


    ui->cbDetectingAlgorithm->setCurrentText(VariableManager::instance().getVar(prefix + "DetectAlgorithm", ui->cbDetectingAlgorithm->currentText()).toString());

    ui->lePythonUrl->setText(
        VariableManager::instance()
            .getVar(prefix + QStringLiteral("ExternalVision.Script"),
                    QStringLiteral("script-example/receive_image_json.py"))
            .toString());
    
    // Load model path setting (for future UI field)
    // QString savedModelPath = setting->value("ExternalScript/ModelPath", "").toString();
    // if (!savedModelPath.isEmpty()) {
    //     qDebug() << "Loaded model path from settings:" << savedModelPath;
    // }
    ui->cbImageSource->setCurrentText(VariableManager::instance().getVar(prefix + "ImageSource", ui->cbImageSource->currentText()).toString());

    // Push thresholds from UI to current tracking instance
    if (TrackingManagerInstance)
    {
        int idx = ui->cbSelectedTracking->currentIndex();
        if (idx >= 0 && idx < TrackingManagerInstance->Trackings.count())
        {
            QMetaObject::invokeMethod(
                TrackingManagerInstance->Trackings.at(idx),
                "SetAssociationThresholds", Qt::QueuedConnection,
                Q_ARG(float, ui->leIoUThreshold->text().toFloat()),
                Q_ARG(float, ui->leDistanceThreshold->text().toFloat()));
        }
    }

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
        
        // ? Fix: Consistent settings key format
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

    Object obj = ImageProcessingInstance->GetNode("GetObjectsNode")->GetInputObject();

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
        
        // ? Fix: Consistent settings key format (same as LoadPluginSetting)
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
    StandardFormatEditor();
    ui->cbGScriptEditorZoom->setCurrentIndex(2); // select "100%" and emit currentIndexChanged

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

    QHash<QString, QVariant> runtimeDeviceState;
    runtimeDeviceState.insert(devicePrefix + QStringLiteral("Connected"), state == QStringLiteral("open"));
    runtimeDeviceState.insert(devicePrefix + QStringLiteral("State"), state);
    runtimeDeviceState.insert(devicePrefix + QStringLiteral("LastResponse"), response);
    runtimeDeviceState.insert(devicePrefix + QStringLiteral("LastCommand"), gcode);
    runtimeDeviceState.insert(devicePrefix + QStringLiteral("UpdatedAt"),
                              QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    if (device == QStringLiteral("robot")) {
        runtimeDeviceState.insert(devicePrefix + QStringLiteral("Position.X"), jsonObject.value("x").toDouble());
        runtimeDeviceState.insert(devicePrefix + QStringLiteral("Position.Y"), jsonObject.value("y").toDouble());
        runtimeDeviceState.insert(devicePrefix + QStringLiteral("Position.Z"), jsonObject.value("z").toDouble());
        runtimeDeviceState.insert(devicePrefix + QStringLiteral("Position.W"), jsonObject.value("w").toDouble());
        runtimeDeviceState.insert(devicePrefix + QStringLiteral("Position.U"), jsonObject.value("u").toDouble());
        runtimeDeviceState.insert(devicePrefix + QStringLiteral("Position.V"), jsonObject.value("v").toDouble());
    }
    VariableManager::instance().updateBatchScoped(
        ProjectName, runtimeDeviceState, VariableManager::Persistence::Runtime);

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

    QHash<QString, QVariant> responseState;
    responseState.insert(idName + QStringLiteral(".LastResponse"), response);
    responseState.insert(idName + QStringLiteral(".LastResponseAt"),
                         QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    responseState.insert(idName + QStringLiteral(".HasError"),
                         response.contains(QStringLiteral("error"), Qt::CaseInsensitive));
    VariableManager::instance().updateBatchScoped(
        ProjectName, responseState, VariableManager::Persistence::Runtime);

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
                ui->leEncoderCurrentPosition->setText(
                    QString::number(applyEncoderCalibration(id, value), 'f', 4));
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
                const float calibratedValue = applyEncoderCalibration(index, value.toFloat());
                // ----- Scheduled Encoder ---------
                if (qAbs(calibratedValue - scheduledStartEncoderValue) > ui->leScheduledDistance->text().toFloat() && isScheduledEncoder == true)
                {
                    submitManualDeviceCommand(ui->leScheduledGcode->text(),
                                              QStringLiteral("manual/scheduled-encoder"));
                    isScheduledEncoder = false;
                    ui->pbStartScheduledEncoder->setText("Start");
                }
                // ---------------------------------

                ui->leEncoderCurrentPosition->setText(QString::number(calibratedValue, 'f', 4));
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
        if (ui->leDetectingObjectListName->text() ==
            TrackingManagerInstance->Trackings.at(i)->GetListName())
        {
            QVector<ObjectInfo> snapshot;
            Tracking* tracking = TrackingManagerInstance->Trackings.at(i);
            if (tracking->thread() == QThread::currentThread()) {
                snapshot = tracking->getTrackedObjectsCopy();
            } else {
                QMetaObject::invokeMethod(tracking, "getTrackedObjectsCopy",
                                          Qt::BlockingQueuedConnection,
                                          Q_RETURN_ARG(QVector<ObjectInfo>, snapshot));
            }
            ObjectModel->setObjectInfoList(snapshot);
        }
    }
}

void RobotWindow::Load3DComponents()
{

}

QString RobotWindow::promptSerialPortPath(const QString& dialogTitle, const QString& defaultPath)
{
    QStringList items;
    for (const QSerialPortInfo& portInfo : QSerialPortInfo::availablePorts())
    {
        QSerialPort serial(portInfo);
        if (serial.open(QIODevice::ReadWrite))
        {
            items << portInfo.portName() + " - " + portInfo.description();
            serial.close();
        }
    }

    const QString customOption = tr("Enter custom device path...");
    items << customOption;

    bool ok = false;
    QString item = QInputDialog::getItem(
        nullptr,
        dialogTitle,
        tr("Serial Ports:"),
        items,
        0,
        false,
        &ok,
        Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint
    );

    if (!ok || item.isEmpty())
        return QString();

    if (item == customOption)
    {
        bool ok2 = false;
        const QString path = QInputDialog::getText(
            nullptr,
            tr("Custom Serial Device"),
            tr("Device path:"),
            QLineEdit::Normal,
            defaultPath,
            &ok2,
            Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint
        ).trimmed();
        return ok2 ? path : QString();
    }

    const int separatorIndex = item.indexOf(" - ");
    return separatorIndex > -1 ? item.left(separatorIndex) : item.trimmed();
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

    // Choose connection type for Robot
    {
        QStringList connectionItems; connectionItems << "Serial" << "Socket";
        bool ok = false;
        QString connectionType = QInputDialog::getItem(nullptr, tr("Connection"), tr("Type:"), connectionItems, 0, false, &ok, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        if (!ok || connectionType.isEmpty()) return;
        if (connectionType == "Socket")
        {
            bool ok2 = false;
            QString address = QInputDialog::getText(nullptr, tr("Socket Address"), tr("IP:PORT"), QLineEdit::Normal, "127.0.0.1:8855", &ok2, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            if (ok2 && !address.isEmpty())
            {
                emit ChangeDeviceState(ui->cbSelectedRobot->currentText(), true, address);
            }
            return;
        }
    }

        const QString comName = promptSerialPortPath(tr("Serial Connection"));
        if (comName.isEmpty())
        {
            return;
        }

        bool ok2;
        QString baudrate = QInputDialog::getText(nullptr, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        
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

    QString cameraSource = QStringLiteral("Other");
    if (text == "Webcam")
    {
        ui->fWebcamSource->setHidden(false);
        cameraSource = QStringLiteral("Webcam");
    }
    else if (text == "Industrial Camera")
    {
        ui->fWebcamSource->setHidden(true);
        if (industrialCameraBackendAvailable) {
            cameraSource = QStringLiteral("Industrial Camera");
        } else {
            cameraSource = QStringLiteral("Unavailable");
            const QString reason = industrialCameraBackendStatus.isEmpty()
                ? QStringLiteral("Industrial camera runtime is unavailable")
                : industrialCameraBackendStatus;
            SoftwareLog(QStringLiteral("Industrial camera disabled: %1").arg(reason));
            if (statusBar())
                statusBar()->showMessage(reason, 8000);
        }
    }
    else if (text == "Images")
    {
        ui->fImageSource->setHidden(false);
        ui->fWebcamSource->setHidden(true);
        cameraSource = QStringLiteral("Images");

    }
    else
    {
        ui->fImageSource->setHidden(true);
        ui->fWebcamSource->setHidden(true);
    }
    QMetaObject::invokeMethod(CameraInstance, [camera = CameraInstance, cameraSource]() {
        camera->SetSource(cameraSource);
    }, Qt::QueuedConnection);
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
    
    auto captureCurrentFont = [this]() {
        QTextCharFormat fmt = ui->pteGcodeArea->currentCharFormat();
        QFont font = fmt.font();
        if (font.pointSizeF() <= 0) {
            font = ui->pteGcodeArea->font();
        }
        if (font.pointSizeF() <= 0) {
            font = ui->pteGcodeArea->document()->defaultFont();
        }
        if (font.pointSizeF() <= 0) {
            font.setPointSizeF(baseFontSize);
        }
        return font;
    };
    
    const QFont preservedFont = captureCurrentFont();
    QTextCharFormat preservedFormat;
    preservedFormat.setFont(preservedFont);
    
    // ---- Clean Rich Text First -----
    // Get plain text to ensure no rich formatting remains
    QString editorText = ui->pteGcodeArea->toPlainText();
    
    // Clear the editor completely and set plain text to ensure clean state
    ui->pteGcodeArea->clear();
    ui->pteGcodeArea->setPlainText(editorText);
    ui->pteGcodeArea->setFont(preservedFont);
    ui->pteGcodeArea->document()->setDefaultFont(preservedFont);
    
    // Reset text formatting to ensure clean state
    QTextCursor cursor = ui->pteGcodeArea->textCursor();
    cursor.select(QTextCursor::Document);
    QTextCharFormat format = preservedFormat;
    format.setForeground(QColor("#DBDBDC")); // Set default text color
    cursor.setCharFormat(format);
    cursor.clearSelection();
    ui->pteGcodeArea->setTextCursor(cursor);

    // ---- Number -----
    editorText = ui->pteGcodeArea->toPlainText();

    // X�a c�c d�ng tr?ng kh�ng c� k� t?
    editorText.replace(QRegularExpression("(\\n[ \\t]*){3,}"), "\n\n");

    // G?p c�c k� t? tr?ng li�n ti?p th�nh m?t k� t? tr?ng
    editorText.replace(QRegularExpression("[\\t ]+"), " ");

    QList<QString> lines = editorText.split('\n');
    QList<QString> oldGcodes;
    QMap<int,int> lineRemap;  // old N -> new N

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
            if (spacePos > 0 && spacePos < line.length()) {
                // Pattern: N<number> <rest>
                QString mS = line.mid(0, spacePos + 1);
                oldNumber = line.mid(1, spacePos - 1);
                line.replace(mS, "");
                line = line.trimmed();
            } else {
                // Pattern: label-only line like "N123"
                // Extract digits after 'N' and clear content so we re-number cleanly
                bool ok = false;
                int lbl = line.mid(1).toInt(&ok);
                if (ok) {
                    oldNumber = QString::number(lbl);
                    line = ""; // no content after label
                } else {
                    oldNumber.clear();
                }
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
                // Detect subprogram declaration like O2000
                bool isSubprogramLine = QRegularExpression("^O\\d+\\b").match(trimmedCheck).hasMatch();
                if (!trimmedCheck.isEmpty() && 
                    !trimmedCheck.startsWith("(") &&    // Skip parentheses comments
                    !trimmedCheck.startsWith("%") &&    // Skip program markers
                    !trimmedCheck.startsWith("FOR") &&    // Skip FOR loops
                    !trimmedCheck.startsWith("ENDFOR") && // Skip ENDFOR statements
                    !trimmedCheck.startsWith("IF") &&     // Skip IF statements
                    !trimmedCheck.startsWith("ELSE") &&   // Skip ELSE statements  
                    !trimmedCheck.startsWith("ENDIF") &&  // Skip ENDIF statements
                    !trimmedCheck.startsWith("WHILE") &&  // Skip WHILE loops
                    !trimmedCheck.startsWith("ENDWHILE") && // Skip ENDWHILE statements
                    !trimmedCheck.startsWith("FUNCTION") && // Skip FUNCTION declarations
                    !trimmedCheck.startsWith("ENDFUNCTION") &&
                    !trimmedCheck.startsWith("RETURN") &&   // Skip RETURN statements
                    !trimmedCheck.startsWith("LABEL") &&    // Skip LABEL lines from numbering
                    !isSubprogramLine)
                {
                    QString numberS = QString("N") + QString::number(i);
                    // Record mapping only if original had a number
                    if (!oldNumber.isEmpty()) {
                        bool ok = false;
                        int oldN = oldNumber.toInt(&ok);
                        if (ok) lineRemap.insert(oldN, i);
                    }
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
                        trimmedCheck.startsWith("ENDWHILE") || trimmedCheck.startsWith("FUNCTION") ||
                        trimmedCheck.startsWith("ENDFUNCTION") || trimmedCheck.startsWith("RETURN") ||
                        isSubprogramLine)
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

    // Replace GOTO targets using boundary-aware regex
    QRegularExpression gotoRe("\\bGOTO\\s+(\\d+)");
    QRegularExpressionMatchIterator it = gotoRe.globalMatch(editorText);
    QString rebuilt;
    int lastPos = 0;
    int gotoReplacements = 0;
    while (it.hasNext()) {
        QRegularExpressionMatch m = it.next();
        int start = m.capturedStart();
        int end = m.capturedEnd();
        rebuilt += editorText.mid(lastPos, start - lastPos);
        QString numStr = m.captured(1);
        bool ok = false;
        int oldN = numStr.toInt(&ok);
        if (ok && lineRemap.contains(oldN)) {
            rebuilt += QString("GOTO %1").arg(lineRemap.value(oldN));
            gotoReplacements++;
        } else {
            rebuilt += m.captured(0);
        }
        lastPos = end;
    }
    rebuilt += editorText.mid(lastPos);
    editorText = rebuilt;
    
    // Provide user feedback about formatting results
    QString formatSummary = QString("G-code formatting completed:\n")
                          + QString("� Total lines processed: %1\n").arg(lines.size())
                          + QString("� G-code lines numbered: %1\n").arg(actualGcodeLines)
                          + QString("� Control structures skipped: %1\n").arg(controlStructureLines)
                          + QString("� Line increment: %1\n").arg(lineIncrement)
                          + QString("� GOTO targets updated: %1").arg(gotoReplacements);
    
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
    ui->pteGcodeArea->setFont(preservedFont);
    ui->pteGcodeArea->document()->setDefaultFont(preservedFont);

    // Reset palette to ensure proper text color
    QPalette p = ui->pteGcodeArea->palette();
    p.setColor(QPalette::Text, QColor("#DBDBDC"));
    ui->pteGcodeArea->setPalette(p);

    // Reset document formatting completely to ensure syntax highlighter works properly
    QTextDocument* doc = ui->pteGcodeArea->document();
    QTextCursor docCursor(doc);
    docCursor.select(QTextCursor::Document);
    QTextCharFormat defaultFormat;
    defaultFormat.setFont(preservedFont);
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

    QMetaObject::invokeMethod(DeviceManagerInstance, "SetSelectedDevice",
                              Qt::QueuedConnection,
                              Q_ARG(int, DeviceManager::ROBOT), Q_ARG(int, id));
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
    QMetaObject::invokeMethod(DeviceManagerInstance, "SetRobotModel",
                              Qt::QueuedConnection,
                              Q_ARG(int, ui->cbSelectedRobot->currentIndex()),
                              Q_ARG(QString, ui->cbRobotModel->currentText()));

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
            lineEdit->setFixedWidth(500); // �?t ki?u d�ng cho QLineEdit
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

    int threadId = ui->cbProgramThreadID->currentIndex();
    if (threadId < 0 || threadId >= GcodeScripts.size()) {
        ui->pbExecuteGcodes->setChecked(false);
        if (gscriptStatusLabel) {
            gscriptStatusLabel->setStyleSheet("color: #ff6b6b;");
            gscriptStatusLabel->setText(tr("No GScript thread is available"));
        }
        return;
    }
    GcodeScript* currentScript = GcodeScripts.at(threadId);

    if (ui->pbExecuteGcodes->isChecked() == false)
    {
        QMetaObject::invokeMethod(currentScript, "Stop", Qt::QueuedConnection);

        return;
    }

    if (m_cellSupervisor && !m_cellSupervisor->automationAllowed()) {
        ui->pbExecuteGcodes->setChecked(false);
        if (gscriptStatusLabel) {
            gscriptStatusLabel->setStyleSheet("color: #ff6b6b;");
            gscriptStatusLabel->setText(
                tr("Cannot run while cell is %1").arg(m_cellSupervisor->stateName()));
        }
        return;
    }

    const GScriptAnalysisResult analysis = GScriptAnalyzer::analyze(
        ui->pteGcodeArea->toPlainText());
    ShowGScriptDiagnostics(analysis.diagnostics);
    if (analysis.hasErrors())
    {
        ui->pbExecuteGcodes->setChecked(false);
        if (gscriptStatusLabel)
            gscriptStatusLabel->setText(
                tr("Cannot run: %1 error(s)").arg(analysis.errorCount()));
        if (!analysis.diagnostics.isEmpty())
            ui->pteGcodeArea->goToLine(analysis.diagnostics.first().line);
        return;
    }

    if (ui->leZ->text().toFloat() > -200 && ui->pbConnectRobot->text() == "Disconnect")
    {
        QMessageBox confirmDialog(this);
        confirmDialog.setIcon(QMessageBox::Warning);
        confirmDialog.setWindowTitle(tr("Confirm Program Run"));
        confirmDialog.setText(tr("The robot has not returned to Home."));
        confirmDialog.setInformativeText(
            tr("You can cancel this run and return the robot to Home first, or continue running the program anyway."));
        QPushButton *cancelButton = confirmDialog.addButton(tr("Cancel Run"), QMessageBox::RejectRole);
        QPushButton *continueButton = confirmDialog.addButton(tr("Run Anyway"), QMessageBox::AcceptRole);
        confirmDialog.setDefaultButton(qobject_cast<QPushButton*>(cancelButton));
        confirmDialog.exec();

        if (confirmDialog.clickedButton() != continueButton)
        {
            ui->pbExecuteGcodes->setChecked(false);

            return;
        }
    }

    int startMode = GcodeScript::BEGIN;

    currentScript->DefaultRobot = ui->cbSelectedRobot->currentText();
    currentScript->DefaultConveyor = ui->cbSelectedConveyor->currentText();
    currentScript->DefaultEncoder = ui->cbSelectedEncoder->currentText();
    currentScript->DefaultSlider = ui->cbSelectedSlider->currentText();
    currentScript->DefaultDevice = ui->cbSelectedDevice->currentText();

    // Z-plane filtering will be applied at individual G-code level in handleGCODE()
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
    if (threadId < 0 || threadId >= GcodeScripts.size())
        return;
    GcodeScript* currentScript = GcodeScripts.at(threadId);

    if (m_cellSupervisor && !m_cellSupervisor->automationAllowed())
        return;

    if (ui->cbEditGcodeLock->isChecked() == false)
	{
		return;
	}

    const GScriptAnalysisResult analysis = GScriptAnalyzer::analyze(lineText);
    if (analysis.hasErrors()) {
        ShowGScriptDiagnostics(analysis.diagnostics);
        return;
    }

    QMetaObject::invokeMethod(currentScript, "ExecuteGcode", Qt::QueuedConnection, Q_ARG(QString, lineText), Q_ARG(int, GcodeScript::BEGIN));

}

void RobotWindow::HighLineCurrentLine(int pos)
{
    int threadId = ui->cbProgramThreadID->currentIndex();
    if (threadId < 0 || threadId >= GcodeScripts.size())
        return;
    GcodeScript* scriptThread = qobject_cast<GcodeScript*>(sender());
    if (scriptThread != GcodeScripts.at(threadId))
        return;

    ui->pteGcodeArea->setExecutionLine(pos + 1);
    ui->pteGcodeArea->goToLine(pos + 1);
}

void RobotWindow::OnEditorTextChanged()
{
    if (ChangedCounter > 0)
        IsGcodeEditorTextChanged = true;

    ChangedCounter++;

    if (gscriptValidationTimer)
        gscriptValidationTimer->start();

    if (ConnectionManager)
    {
        ConnectionManager->updateLatestGscript(ui->pteGcodeArea->toPlainText());
    }
}

void RobotWindow::ValidateGScriptNow()
{
    const GScriptAnalysisResult analysis = GScriptAnalyzer::analyze(
        ui->pteGcodeArea->toPlainText());
    ShowGScriptDiagnostics(analysis.diagnostics);
    if (!gscriptStatusLabel)
        return;

    if (analysis.hasErrors()) {
        gscriptStatusLabel->setStyleSheet("color: #ff6b6b;");
        gscriptStatusLabel->setText(
            tr("%1 error(s), %2 warning(s)")
                .arg(analysis.errorCount()).arg(analysis.warningCount()));
    } else if (analysis.warningCount() > 0) {
        gscriptStatusLabel->setStyleSheet("color: #f0b24a;");
        gscriptStatusLabel->setText(
            tr("Valid with %1 warning(s)").arg(analysis.warningCount()));
    } else {
        gscriptStatusLabel->setStyleSheet("color: #69d18b;");
        gscriptStatusLabel->setText(
            tr("Valid · %1 executable line(s)").arg(analysis.executableLineCount));
    }
}

void RobotWindow::ShowGScriptDiagnostics(QList<GScriptDiagnostic> diagnostics)
{
    gscriptDiagnostics = diagnostics;
    if (!gscriptProblemsTable)
        return;

    gscriptProblemsTable->setRowCount(diagnostics.size());
    QHash<int, int> diagnosticLines;
    for (int row = 0; row < diagnostics.size(); ++row) {
        const GScriptDiagnostic& diagnostic = diagnostics.at(row);
        diagnosticLines[diagnostic.line] = qMax(
            diagnosticLines.value(diagnostic.line, 0), int(diagnostic.severity));
        const QColor color = diagnostic.severity == GScriptDiagnostic::Error
            ? QColor("#ff6b6b")
            : diagnostic.severity == GScriptDiagnostic::Warning
                ? QColor("#f0b24a") : QColor("#73b7ff");
        QTableWidgetItem* severityItem = new QTableWidgetItem(diagnostic.severityName());
        severityItem->setForeground(color);
        QTableWidgetItem* messageItem = new QTableWidgetItem(diagnostic.message);
        messageItem->setToolTip(diagnostic.hint.isEmpty()
                                    ? diagnostic.message
                                    : diagnostic.message + "\n" + diagnostic.hint);
        gscriptProblemsTable->setItem(row, 0, severityItem);
        gscriptProblemsTable->setItem(row, 1,
            new QTableWidgetItem(QString::number(diagnostic.line)));
        gscriptProblemsTable->setItem(row, 2,
            new QTableWidgetItem(diagnostic.code));
        gscriptProblemsTable->setItem(row, 3, messageItem);
    }
    ui->pteGcodeArea->setDiagnosticLines(diagnosticLines);
    gscriptProblemsTable->setVisible(true);
    if (gscriptInspectionTabs) {
        const int problemTab = gscriptInspectionTabs->indexOf(
            gscriptProblemsTable->parentWidget());
        if (problemTab >= 0) {
            gscriptInspectionTabs->setTabText(
                problemTab, tr("Problems (%1)").arg(diagnostics.size()));
            if (!diagnostics.isEmpty() && diagnostics.first().severity == GScriptDiagnostic::Error)
                gscriptInspectionTabs->setCurrentIndex(problemTab);
        }
    }
}

void RobotWindow::UpdateGScriptExecutionState(GcodeScript::ExecutionState state,
                                               QString message)
{
    if (!gscriptStatusLabel)
        return;
    QString stateName;
    QString color = "#d4d4d4";
    switch (state) {
    case GcodeScript::ExecutionState::Validating: stateName = tr("Validating"); break;
    case GcodeScript::ExecutionState::Running: stateName = tr("Running"); color = "#69d18b"; break;
    case GcodeScript::ExecutionState::WaitingForDevice: stateName = tr("Waiting"); color = "#73b7ff"; break;
    case GcodeScript::ExecutionState::WaitingForTimer: stateName = tr("Delay"); color = "#73b7ff"; break;
    case GcodeScript::ExecutionState::WaitingForCondition: stateName = tr("Waiting condition"); color = "#73b7ff"; break;
    case GcodeScript::ExecutionState::Stopping: stateName = tr("Stopping"); color = "#f0b24a"; break;
    case GcodeScript::ExecutionState::Completed: stateName = tr("Completed"); color = "#69d18b"; break;
    case GcodeScript::ExecutionState::Faulted: stateName = tr("Faulted"); color = "#ff6b6b"; break;
    default: stateName = tr("Ready"); break;
    }
    gscriptStatusLabel->setStyleSheet("color: " + color + ";");
    gscriptStatusLabel->setText(message.isEmpty() ? stateName
                                                  : stateName + " · " + message);
    const bool active = state == GcodeScript::ExecutionState::Running ||
                        state == GcodeScript::ExecutionState::WaitingForDevice ||
                        state == GcodeScript::ExecutionState::WaitingForTimer ||
                        state == GcodeScript::ExecutionState::WaitingForCondition ||
                        state == GcodeScript::ExecutionState::Stopping;
    if (active)
        ui->pteGcodeArea->setReadOnly(true);
    else
        ui->pteGcodeArea->setLockState(ui->cbEditGcodeLock->checkState());
    ui->pbExecuteGcodes->setText(active ? tr("Stop") : tr("Run"));
    if (!active)
        ui->pteGcodeArea->setExecutionLine(-1);
}

void RobotWindow::changeFontSize(int index)
{
    // L?y n?i dung text t? QComboBox
    QString text = ui->cbGScriptEditorZoom->currentText();

    // Lo?i b? d?u % v� chuy?n th�nh s? nguy�n
    text.chop(1);  // X�a k� t? '%' cu?i c�ng
    bool ok;
    int percentage = text.toInt(&ok);

    // N?u chuy?n d?i th�nh c�ng, t�nh to�n t? l? ph?n tram
    if (ok) {
        qreal scaleFactor = percentage / 100.0;
        QTextCursor cursor = ui->pteGcodeArea->textCursor();
        ui->pteGcodeArea->selectAll(); // Ch?n to�n b? van b?n
        ui->pteGcodeArea->setFontPointSize(baseFontSize * scaleFactor); // Thay d?i k�ch thu?c ch?
        ui->pteGcodeArea->setTextCursor(cursor); // �?t l?i con tr? van b?n
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
    // Use safe access to RobotParameters
    if (!isRobotParametersValid()) {
        return; // Skip update if not ready
    }
    
    RobotPara currentParams = getSafeRobotParameters();

    DisablePositionUpdatingEvents();

    if (!ui->leX->hasFocus())
    {
        ui->leX->setText(QString::number(currentParams.X));
    }
    if (!ui->leY->hasFocus())
    {
        ui->leY->setText(QString::number(currentParams.Y));
    }
    if (!ui->leZ->hasFocus())
    {
        ui->leZ->setText(QString::number(currentParams.Z));
    }
    if (!ui->leW->hasFocus())
    {
        ui->leW->setText(QString::number(currentParams.W));
    }
    if (!ui->leU->hasFocus())
    {
        ui->leU->setText(QString::number(currentParams.U));
    }
    if (!ui->leV->hasFocus())
    {
        ui->leV->setText(QString::number(currentParams.V));
    }
    if (!ui->leVelocity->hasFocus())
    {
        ui->leVelocity->setText(QString::number(currentParams.F));
    }
    if (!ui->leAccel->hasFocus())
    {
        ui->leAccel->setText(QString::number(currentParams.A));
    }
    if (!ui->leJerk->hasFocus())
    {
        ui->leJerk->setText(QString::number(currentParams.J));
    }
    if (!ui->leStartSpeed->hasFocus())
    {
        ui->leStartSpeed->setText(QString::number(currentParams.S));
    }
    if (!ui->leEndSpeed->hasFocus())
    {
        ui->leEndSpeed->setText(QString::number(currentParams.E));
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
    QString value = VariableManager::instance().getVarScoped(ProjectName, name).toString() + '\n';

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

    QMetaObject::invokeMethod(DeviceManagerInstance, "SetSelectedDevice",
                              Qt::QueuedConnection,
                              Q_ARG(int, DeviceManager::CONVEYOR), Q_ARG(int, id));

    QMetaObject::invokeMethod(DeviceManagerInstance, "RequestDeviceInfo", Qt::QueuedConnection, Q_ARG(int, DeviceManager::CONVEYOR));
}

void RobotWindow::ConnectEncoder()
{
    if (ui->pbConnectEncoder->text() != "Connect")
    {
        emit ChangeDeviceState(ui->cbSelectedEncoder->currentText(), false, "");
        return;
    }

    // Choose connection type for Encoder
    {
        QStringList connectionItems; connectionItems << "Serial" << "Socket";
        bool ok = false;
        QString connectionType = QInputDialog::getItem(nullptr, tr("Connection"), tr("Type:"), connectionItems, 0, false, &ok);
        if (!ok || connectionType.isEmpty()) return;
        if (connectionType == "Socket")
        {
            bool ok2 = false;
            QString address = QInputDialog::getText(nullptr, tr("Socket Address"), tr("IP:PORT"), QLineEdit::Normal, "127.0.0.1:8857", &ok2);
            if (ok2 && !address.isEmpty())
            {
                emit ChangeDeviceState(ui->cbSelectedEncoder->currentText(), true, address);
            }
            return;
        }
    }

    const QString comName = promptSerialPortPath(tr("Serial Connection"));
    if (!comName.isEmpty())
    {
        bool ok2; Q_UNUSED(ok2);
        QString baudrate = QInputDialog::getText(nullptr, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
        emit ChangeDeviceState(ui->cbSelectedEncoder->currentText(), true, comName);
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

        if (!TrackingManagerInstance || id < 0 ||
            id >= TrackingManagerInstance->Trackings.size())
            return;
        Tracking* tracking = TrackingManagerInstance->Trackings.at(id);
        if (interval > 0) {
            QMetaObject::invokeMethod(tracking, "StartVirtualEncoder", Qt::QueuedConnection,
                                      Q_ARG(int, interval));
        } else {
            QMetaObject::invokeMethod(tracking, "StopVirtualEncoder", Qt::QueuedConnection);
        }
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
        if (TrackingManagerInstance && selectedEncoderID >= 0 &&
            selectedEncoderID < TrackingManagerInstance->Trackings.size()) {
            QMetaObject::invokeMethod(
                TrackingManagerInstance->Trackings.at(selectedEncoderID),
                "ResetVirtualEncoder", Qt::QueuedConnection);
        }
    }
}

void RobotWindow::SetEncoderVelocity()
{
    QString prefix = ProjectName + "." + ui->cbSelectedEncoder->currentText() + ".";
    UpdateVariable(prefix + "Velocity", ui->leEncoderVelocity->text());
    int selectedEncoderID = ui->cbSelectedEncoder->currentIndex();

    if (TrackingManagerInstance && selectedEncoderID >= 0 &&
        selectedEncoderID < TrackingManagerInstance->Trackings.size()) {
        QMetaObject::invokeMethod(
            TrackingManagerInstance->Trackings.at(selectedEncoderID),
            "SetVirtualEncoderVelocity", Qt::QueuedConnection,
            Q_ARG(float, ui->leEncoderVelocity->text().toFloat()));
    }
}

void RobotWindow::CalibrateEncoder()
{
    if (ui->cbSelectedEncoder->currentText() == QStringLiteral("+")) {
        QMessageBox::warning(this, tr("Encoder calibration"), tr("Select an encoder first."));
        return;
    }
    if (ui->cbEncoderType->currentText() == QStringLiteral("Virtual Encoder")) {
        QMessageBox::information(this, tr("Encoder calibration"),
                                 tr("Virtual Encoder already uses millimetres. Set its velocity directly."));
        return;
    }

    const int id = getIDfromName(ui->cbSelectedEncoder->currentText());
    const QString prefix = QStringLiteral("encoder%1.Calibration.").arg(id);
    const float latestRaw = m_encoderLastRawPositions.value(id, ui->leEncoderCurrentPosition->text().toFloat());

    QDialog dialog(this);
    dialog.setWindowTitle(tr("Calibrate %1").arg(ui->cbSelectedEncoder->currentText()));
    dialog.setMinimumWidth(500);
    QVBoxLayout* root = new QVBoxLayout(&dialog);
    QLabel* instructions = new QLabel(
        tr("1. Stop the conveyor and capture Start. 2. Move it a precisely measured distance. "
           "3. Capture End. The sign is controlled by Reverse direction."), &dialog);
    instructions->setWordWrap(true);
    root->addWidget(instructions);

    QFormLayout* form = new QFormLayout;
    auto rawRow = [&dialog, latestRaw](const QString& buttonText, QDoubleSpinBox*& editor,
                                       QPushButton*& captureButton) {
        QWidget* row = new QWidget(&dialog);
        QHBoxLayout* layout = new QHBoxLayout(row);
        layout->setContentsMargins(0, 0, 0, 0);
        editor = new QDoubleSpinBox(row);
        editor->setRange(-1000000000.0, 1000000000.0);
        editor->setDecimals(4);
        editor->setValue(latestRaw);
        editor->setKeyboardTracking(false);
        captureButton = new QPushButton(buttonText, row);
        layout->addWidget(editor, 1);
        layout->addWidget(captureButton);
        return row;
    };
    QDoubleSpinBox* rawStart = nullptr;
    QDoubleSpinBox* rawEnd = nullptr;
    QPushButton* captureStart = nullptr;
    QPushButton* captureEnd = nullptr;
    form->addRow(tr("Raw start"), rawRow(tr("Use current"), rawStart, captureStart));
    form->addRow(tr("Raw end"), rawRow(tr("Use current"), rawEnd, captureEnd));

    QDoubleSpinBox* measuredDistance = new QDoubleSpinBox(&dialog);
    measuredDistance->setRange(0.001, 1000000.0);
    measuredDistance->setDecimals(4);
    measuredDistance->setValue(100.0);
    measuredDistance->setSuffix(tr(" mm"));
    measuredDistance->setKeyboardTracking(false);
    QCheckBox* reverse = new QCheckBox(tr("Reverse direction (raw increase means negative travel)"), &dialog);
    QLabel* preview = new QLabel(&dialog);
    preview->setTextInteractionFlags(Qt::TextSelectableByMouse);
    form->addRow(tr("Measured travel"), measuredDistance);
    form->addRow(QString(), reverse);
    form->addRow(tr("Calculated scale"), preview);
    root->addLayout(form);

    const bool currentValid = VariableManager::instance()
                                  .getVarScoped(ProjectName, prefix + QStringLiteral("IsValid"), false).toBool();
    QLabel* currentStatus = new QLabel(
        currentValid
            ? tr("Current profile: VALID, scale %1 mm/raw-unit")
                  .arg(VariableManager::instance()
                           .getVarScoped(ProjectName, prefix + QStringLiteral("Scale"), 1.0).toDouble(),
                       0, 'g', 10)
            : tr("Current profile: NOT CALIBRATED"),
        &dialog);
    currentStatus->setStyleSheet(currentValid
        ? QStringLiteral("color: rgb(80, 220, 120); font-weight: bold;")
        : QStringLiteral("color: rgb(255, 190, 70); font-weight: bold;"));
    root->addWidget(currentStatus);

    auto updatePreview = [rawStart, rawEnd, measuredDistance, reverse, preview]() {
        const double rawDelta = rawEnd->value() - rawStart->value();
        if (qAbs(rawDelta) <= 1.0e-9) {
            preview->setText(QObject::tr("Capture two different readings"));
            preview->setStyleSheet(QStringLiteral("color: rgb(255, 100, 100);"));
            return;
        }
        const double signedDistance = measuredDistance->value() * (reverse->isChecked() ? -1.0 : 1.0);
        preview->setText(QObject::tr("%1 mm/raw-unit").arg(signedDistance / rawDelta, 0, 'g', 10));
        preview->setStyleSheet(QStringLiteral("color: rgb(80, 220, 120); font-weight: bold;"));
    };
    connect(captureStart, &QPushButton::clicked, this, [this, id, rawStart, updatePreview]() {
        rawStart->setValue(m_encoderLastRawPositions.value(id, rawStart->value()));
        updatePreview();
    });
    connect(captureEnd, &QPushButton::clicked, this, [this, id, rawEnd, updatePreview]() {
        rawEnd->setValue(m_encoderLastRawPositions.value(id, rawEnd->value()));
        updatePreview();
    });
    connect(rawStart, QOverload<double>::of(&QDoubleSpinBox::valueChanged), &dialog, updatePreview);
    connect(rawEnd, QOverload<double>::of(&QDoubleSpinBox::valueChanged), &dialog, updatePreview);
    connect(measuredDistance, QOverload<double>::of(&QDoubleSpinBox::valueChanged), &dialog, updatePreview);
    connect(reverse, &QCheckBox::toggled, &dialog, updatePreview);
    updatePreview();

    QDialogButtonBox* buttons = new QDialogButtonBox(
        QDialogButtonBox::Save | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    root->addWidget(buttons);
    if (dialog.exec() != QDialog::Accepted)
        return;

    const double rawDelta = rawEnd->value() - rawStart->value();
    if (qAbs(rawDelta) <= 1.0e-9) {
        QMessageBox::warning(this, tr("Encoder calibration"), tr("Start and end readings must be different."));
        return;
    }
    const double signedDistance = measuredDistance->value() * (reverse->isChecked() ? -1.0 : 1.0);
    const double scale = signedDistance / rawDelta;
    if (!qIsFinite(scale) || qFuzzyIsNull(scale)) {
        QMessageBox::warning(this, tr("Encoder calibration"), tr("Calculated scale is invalid."));
        return;
    }

    QHash<QString, QVariant> values;
    values.insert(prefix + QStringLiteral("SchemaVersion"), 1);
    values.insert(prefix + QStringLiteral("IsValid"), true);
    values.insert(prefix + QStringLiteral("Scale"), scale);
    values.insert(prefix + QStringLiteral("RawReference"), rawStart->value());
    values.insert(prefix + QStringLiteral("WorldReference"), 0.0);
    values.insert(prefix + QStringLiteral("RawDelta"), rawDelta);
    values.insert(prefix + QStringLiteral("MeasuredDistanceMm"), signedDistance);
    values.insert(prefix + QStringLiteral("EncoderType"), ui->cbEncoderType->currentText());
    values.insert(prefix + QStringLiteral("UpdatedAt"),
                  QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    VariableManager::instance().updateBatchScoped(ProjectName, values);
    QMetaObject::invokeMethod(TrackingManagerInstance, "ReloadEncoderCalibration",
                              Qt::QueuedConnection, Q_ARG(int, id));
    statusBar()->showMessage(
        tr("%1 calibrated: %2 mm/raw-unit").arg(ui->cbSelectedEncoder->currentText())
            .arg(scale, 0, 'g', 10), 7000);
    SoftwareLog(tr("Encoder %1 calibration saved (scale=%2 mm/raw-unit)").arg(id).arg(scale, 0, 'g', 10));
}

float RobotWindow::applyEncoderCalibration(int id, float rawValue) const
{
    const QString prefix = QStringLiteral("encoder%1.Calibration.").arg(id);
    if (!VariableManager::instance()
             .getVarScoped(ProjectName, prefix + QStringLiteral("IsValid"), false).toBool())
        return rawValue;
    const double scale = VariableManager::instance()
                             .getVarScoped(ProjectName, prefix + QStringLiteral("Scale"), 1.0).toDouble();
    const double rawReference = VariableManager::instance()
                                    .getVarScoped(ProjectName, prefix + QStringLiteral("RawReference"), 0.0).toDouble();
    const double worldReference = VariableManager::instance()
                                      .getVarScoped(ProjectName, prefix + QStringLiteral("WorldReference"), 0.0).toDouble();
    const double calibrated = (rawValue - rawReference) * scale + worldReference;
    return qIsFinite(calibrated) ? static_cast<float>(calibrated) : rawValue;
}

void RobotWindow::OnEncoderPositionReceived(int id, float rawValue)
{
    m_encoderLastRawPositions.insert(id, rawValue);
    const float calibrated = applyEncoderCalibration(id, rawValue);
    const qint64 nowMs = QDateTime::currentMSecsSinceEpoch();
    double velocity = 0.0;
    if (m_encoderLastSampleEpochMs.contains(id)) {
        const qint64 elapsedMs = nowMs - m_encoderLastSampleEpochMs.value(id);
        if (elapsedMs > 0)
            velocity = (calibrated - m_encoderLastCalibratedPositions.value(id, calibrated))
                       * 1000.0 / static_cast<double>(elapsedMs);
    }
    m_encoderLastSampleEpochMs.insert(id, nowMs);
    m_encoderLastCalibratedPositions.insert(id, calibrated);

    const QString prefix = QString("Encoder.%1.").arg(id);
    QHash<QString, QVariant> encoderState;
    encoderState.insert(prefix + QStringLiteral("RawPosition"), rawValue);
    encoderState.insert(prefix + QStringLiteral("Position"), calibrated);
    encoderState.insert(prefix + QStringLiteral("Velocity"), qIsFinite(velocity) ? velocity : 0.0);
    encoderState.insert(prefix + QStringLiteral("LastUpdateAt"),
                        QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    encoderState.insert(prefix + QStringLiteral("Fresh"), true);
    VariableManager::instance().updateBatchScoped(
        ProjectName, encoderState, VariableManager::Persistence::Runtime);

    if (ui->cbSelectedEncoder->currentText() == QStringLiteral("+") ||
        getIDfromName(ui->cbSelectedEncoder->currentText()) != id)
        return;
    ui->leEncoderCurrentPosition->setText(QString::number(calibrated, 'f', 4));
    CalculateEncoderVelocity(id, calibrated);
}

void RobotWindow::CalculateEncoderVelocity(int id, float value)
{
    Q_UNUSED(id)
    if (!encoderUpdateTimer.isValid()) {
        encoderLastValue = value;
        encoderUpdateTimer.start();
        return;
    }
    const qint64 elapsed = encoderUpdateTimer.restart();
    if (elapsed <= 0)
        return;
    const float velocity = (value - encoderLastValue) * 1000.0f / elapsed;
    encoderLastValue = value;
    if (qIsFinite(velocity))
        ui->leEncoderVelocity->setText(QString::number(velocity, 'f', 3));
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
            isCameraOpenPending = true;
            cameraOpenRequestId++;

            OpenLoadingPopup();
            CameraOpenTimeoutTimer.start(8000);
            QMetaObject::invokeMethod(CameraInstance, "OpenCamera",
                                      Q_ARG(int, cameraID),
                                      Q_ARG(int, cameraOpenRequestId));

            QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
            UpdateVariable(prefix + "CameraID", cameraID);
        }
        else
        {
            // User cancelled or invalid camera
            CameraOpenTimeoutTimer.stop();
            isCameraOpenPending = false;
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
        bool opened = false;
        int actualWidth = 0;
        int actualHeight = 0;
        const QString videoPath = imageNames.first();
        const int requestedWidth = ui->leImageWidth->text().toInt();
        const int requestedHeight = ui->leImageHeight->text().toInt();
        QMetaObject::invokeMethod(CameraInstance,
                                  [camera = CameraInstance, videoPath, requestedWidth,
                                   requestedHeight, &opened, &actualWidth, &actualHeight]() {
            opened = camera->OpenVideoFile(videoPath, requestedWidth, requestedHeight);
            actualWidth = camera->Width;
            actualHeight = camera->Height;
        }, Qt::BlockingQueuedConnection);
        if (!opened) {
            SoftwareLog(QStringLiteral("Cannot open video file: %1").arg(videoPath));
            return;
        }
        ui->leImageWidth->setText(QString::number(actualWidth));
        ui->leImageHeight->setText(QString::number(actualHeight));

        CameraTimer.start(ui->leCaptureInterval->text().toInt());
    }
    else
    {
//        if (imageName.isEmpty())
//        {
//            qDebug() << "Kh�ng ch?n ?nh";
//            return;
//        }

        // Add safety check for CameraInstance
        if (!CameraInstance) {
            qDebug() << "Warning: CameraInstance is null, cannot load images";
            return;
        }

        QList<cv::Mat> loadedImages;
        for (const QString &imageName : imageNames) {
            QImage qImage(imageName);
            if (!qImage.isNull()) {
                try {
                    cv::Mat convertedMat = ImageTool::QImageToCvMat(qImage, true);
                    if (!convertedMat.empty()) {
                        loadedImages.append(convertedMat.clone());
                    }
                } catch (...) {
                    qDebug() << "Warning: Failed to convert image:" << imageName;
                    continue;
                }
            }
        }

        if (!loadedImages.isEmpty()) {
            QMetaObject::invokeMethod(CameraInstance,
                                      [camera = CameraInstance, loadedImages]() {
                camera->SetImages(loadedImages);
            }, Qt::BlockingQueuedConnection);
        } else {
            qDebug() << "Warning: No valid images loaded, CaptureImage remains empty";
            return;
        }

//        QImage qImage(imageName);

//        if (qImage.isNull())
//        {
//            qDebug() << "Kh�ng th? d?c ?nh";
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
        CameraOpenTimeoutTimer.stop();
        isCameraOpenPending = false;

        // Stop camera timer first
        CameraTimer.stop();
        
        // Update UI state
    ui->lbCameraState->setEnabled(false);
    ui->pbLoadCamera->setText("Load Camera");
    ui->pbStartAcquisition->setChecked(false);

        // Stop different camera types safely
        if (CameraInstance->Source == "Webcam" || CameraInstance->Source == "Video")
        {
            QMetaObject::invokeMethod(CameraInstance, "ReleaseCamera",
                                      Qt::BlockingQueuedConnection);
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

        QHash<QString, QVariant> cameraState;
        cameraState.insert(QStringLiteral("Camera.Connected"), false);
        cameraState.insert(QStringLiteral("Camera.State"), QStringLiteral("STOPPED"));
        cameraState.insert(QStringLiteral("Camera.UpdatedAt"),
                           QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
        VariableManager::instance().updateBatchScoped(
            ProjectName, cameraState, VariableManager::Persistence::Runtime);
        
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
    if (m_imagePipelineController) {
        connect(m_imagePipelineController, &ImagePipelineController::colorFilterInputReady,
                ParameterPanel, &FilterWindow::SetImage,
                Qt::UniqueConnection);
        m_imagePipelineController->requestColorFilterInput();
    } else {
        ParameterPanel->SetImage(ImageProcessingInstance->GetNode("ColorFilterNode")->GetInputImage());
    }
    ParameterPanel->show();
}

void RobotWindow::onMappingMatrixUpdated(QMatrix matrix)
{
    QString detectingKey = ui->cbSelectedDetecting->currentText();
    if (detectingKey.isEmpty())
        detectingKey = "tracking0";

    m_mappingMatrices[detectingKey] = matrix;

    // Persist to VariableManager for external uses
    QString prefix = ProjectName + "." + detectingKey + ".";
    VariableManager::instance().updateVar(prefix + "ImageToRealWorldMatrix", matrix);
    VariableManager::instance().updateVar(prefix + "ImageToRealWorldMatrixString",
                                          QString("%1,%2,%3,%4,%5,%6")
                                          .arg(matrix.m11())
                                          .arg(matrix.m12())
                                          .arg(matrix.m21())
                                          .arg(matrix.m22())
                                          .arg(matrix.dx())
                                          .arg(matrix.dy()));
    VariableManager::instance().updateVar(
        prefix + QStringLiteral("Calibration.Mapping.IsValid"), true);

    SoftwareLog(QString("Mapping matrix updated for %1").arg(detectingKey));
}

void RobotWindow::SelectObjectDetectingAlgorithm(int algorithm)
{
    ui->fBlobPanel->setHidden(true);
    ui->fExternalScriptPanel->setHidden(true);
    ui->fCirclePanel->setHidden(true);

    QString text = ui->cbDetectingAlgorithm->itemText(algorithm);

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    VariableManager::instance().updateVar(prefix + "DetectAlgorithm",text);

    if (m_imagePipelineController)
    {
        m_imagePipelineController->configureAlgorithm(text, ConnectionManager);
    }

    if (text == "Find Blobs")
    {
        ui->fBlobPanel->setHidden(false);
    }
    if (text == "Find Circles")
    {
        ui->fCirclePanel->setHidden(false);

        // Apply current circle parameters
        UpdateCircleParameters();
    }
    if (text == "External Script")
    {
        ui->fExternalScriptPanel->setHidden(false);
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
    TaskNode* findCirclesNode = ImageProcessingInstance->GetNode("FindCirclesNode");
    QMetaObject::invokeMethod(findCirclesNode,
                              [findCirclesNode, edgeThreshold, centerThreshold, minRadius, maxRadius]() {
                                  findCirclesNode->Input(edgeThreshold, centerThreshold, minRadius, maxRadius);
                              },
                              Qt::QueuedConnection);
    
    // Save parameters to variables
    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    VariableManager::instance().updateVar(prefix + "EdgeThreshold", edgeThreshold);
    VariableManager::instance().updateVar(prefix + "CenterThreshold", centerThreshold);
    VariableManager::instance().updateVar(prefix + "MinRadius", minRadius);
    VariableManager::instance().updateVar(prefix + "MaxRadius", maxRadius);
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

    QString detectingKey = ui->cbSelectedDetecting->currentText();
    QMatrix matrix;
    bool hasMatrix = m_mappingMatrices.contains(detectingKey);
    if (hasMatrix)
        matrix = m_mappingMatrices.value(detectingKey);
    if (!hasMatrix && m_imagePipelineController && m_imagePipelineController->hasValidMapping()) {
        matrix = m_imagePipelineController->currentMappingMatrix();
        hasMatrix = true;
    }

    // Fallback: load from VariableManager if runtime cache is empty
    const QString scopedMatrixKey = detectingKey + ".ImageToRealWorldMatrix";
    const bool calibrationMarkedValid = VariableManager::instance().getVarScoped(
        ProjectName, detectingKey + QStringLiteral(".Calibration.Mapping.IsValid"), false).toBool();
    if (!hasMatrix && calibrationMarkedValid &&
        VariableManager::instance().containsFullKeyScoped(ProjectName, scopedMatrixKey)) {
        matrix = VariableManager::instance().getVarScoped(ProjectName, scopedMatrixKey).value<QMatrix>();
        hasMatrix = !qFuzzyIsNull(matrix.determinant());
    }

    // If we do not have a valid mapping matrix, warn and stop
    if (!hasMatrix || qFuzzyIsNull(matrix.determinant())) {
        SoftwareLog("Mapping matrix is not available for this detecting. Please calculate calibration matrix first.");
        return;
    }
    QPointF realPoint = matrix.map(point);

    //L�m tr�n realPoint d?n 2 ch? s? th?p ph�n
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
//            // T�m t�m c?a poly
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

    if (m_imagePipelineController)
    {
        m_imagePipelineController->configureWarpCrop(isWarp, isCropTool);
    }
    else
    {
        // Fallback to previous behaviour if controller is unavailable
        if (isWarp == false && isCropTool == true)
        {
            if (warpImageNode) QMetaObject::invokeMethod(warpImageNode, [warpImageNode]() { warpImageNode->SetPassThrough(true); }, Qt::QueuedConnection);
            if (cropImageNode) QMetaObject::invokeMethod(cropImageNode, [cropImageNode]() { cropImageNode->SetPassThrough(false); }, Qt::QueuedConnection);
        }
        else if (isWarp == true && isCropTool == true)
        {
            if (warpImageNode) QMetaObject::invokeMethod(warpImageNode, [warpImageNode]() { warpImageNode->SetPassThrough(false); }, Qt::QueuedConnection);
            if (cropImageNode) QMetaObject::invokeMethod(cropImageNode, [cropImageNode]() { cropImageNode->SetPassThrough(false); }, Qt::QueuedConnection);
        }
        else if (isWarp == false && isCropTool == false)
        {
            if (warpImageNode) QMetaObject::invokeMethod(warpImageNode, [warpImageNode]() { warpImageNode->SetPassThrough(true); }, Qt::QueuedConnection);
            if (cropImageNode) QMetaObject::invokeMethod(cropImageNode, [cropImageNode]() { cropImageNode->SetPassThrough(true); }, Qt::QueuedConnection);
        }
        else if (isWarp == true && isCropTool == false)
        {
            if (warpImageNode) QMetaObject::invokeMethod(warpImageNode, [warpImageNode]() { warpImageNode->SetPassThrough(false); }, Qt::QueuedConnection);
            if (cropImageNode) QMetaObject::invokeMethod(cropImageNode, [cropImageNode]() { cropImageNode->SetPassThrough(true); }, Qt::QueuedConnection);
        }
    }

    if (isWarp == false && isCropTool == true)
    {
        ui->gvImageViewer->SelectNoTool();
        ui->gvImageViewer->TurnOnObjects(true);
    }
    else if (isWarp == true && isCropTool == true)
    {
        ui->gvImageViewer->SelectNoTool();
        ui->gvImageViewer->TurnOnObjects(true);
    }
    else if (isWarp == false && isCropTool == false)
    {
        UnselectToolButtons();
        ui->gvImageViewer->SelectAreaTool();

        ui->gvImageViewer->TurnOnObjects(false);
    }
    else if (isWarp == true && isCropTool == false)
    {
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
                char* data = (char*)input.ptr<uchar>(i); //first Socket Address of the i-th line
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

    // Choose connection type for Conveyor
    {
        QStringList connectionItems; connectionItems << "Serial" << "Socket";
        bool ok=false; QString connectionType = QInputDialog::getItem(nullptr, tr("Connection"), tr("Type:"), connectionItems, 0, false, &ok);
        if (!ok || connectionType.isEmpty()) return;
        if (connectionType == "Socket") {
            bool ok2=false; QString address = QInputDialog::getText(nullptr, tr("Socket Address"), tr("IP:PORT"), QLineEdit::Normal, "127.0.0.1:8856", &ok2);
            if (ok2 && !address.isEmpty()) {
                emit ChangeDeviceState(ui->cbSelectedConveyor->currentText(), true, address);
            }
            return;
        }
    }

    const QString comName = promptSerialPortPath(tr("Serial Connection"));
    if (!comName.isEmpty())
    {
        bool ok2; Q_UNUSED(ok2);
        QString baudrate = QInputDialog::getText(nullptr, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
        emit ChangeDeviceState(ui->cbSelectedConveyor->currentText(), true, comName);
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

        if (TrackingManagerInstance && !TrackingManagerInstance->Trackings.isEmpty()) {
            QMetaObject::invokeMethod(
                TrackingManagerInstance->Trackings.at(0),
                "SetVirtualEncoderPosition", Qt::QueuedConnection,
                Q_ARG(float, currentPos));
        }
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
    QObject *senderObj = sender(); // L?y d?i tu?ng k�ch ho?t

    if (qobject_cast<QPushButton*>(senderObj) == ui->pbStartCustomConveyor1 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStartCustomConveyor1Command)
    {
        submitManualDeviceCommand(ui->pbStartCustomConveyor1Command->text(),
                                  QStringLiteral("manual/custom-conveyor"));

    }
    else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStartCustomConveyor2 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStartCustomConveyor2Command)
    {
        submitManualDeviceCommand(ui->pbStartCustomConveyor2Command->text(),
                                  QStringLiteral("manual/custom-conveyor"));
    }
    else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStartCustomConveyor3 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStartCustomConveyor3Command)
    {
        submitManualDeviceCommand(ui->pbStartCustomConveyor3Command->text(),
                                  QStringLiteral("manual/custom-conveyor"));
    }
    if (qobject_cast<QPushButton*>(senderObj) == ui->pbStopCustomConveyor1 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStopCustomConveyor1Command)
    {
        submitManualDeviceCommand(ui->pbStopCustomConveyor1Command->text(),
                                  QStringLiteral("manual/custom-conveyor"));

    } else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStopCustomConveyor2 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStopCustomConveyor2Command)
    {
        submitManualDeviceCommand(ui->pbStopCustomConveyor2Command->text(),
                                  QStringLiteral("manual/custom-conveyor"));
    } else if (qobject_cast<QPushButton*>(senderObj) == ui->pbStopCustomConveyor3 || qobject_cast<QLineEdit*>(senderObj) == ui->pbStopCustomConveyor3Command)
    {
        submitManualDeviceCommand(ui->pbStopCustomConveyor3Command->text(),
                                  QStringLiteral("manual/custom-conveyor"));
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
    if (!TrackingManagerInstance || selectedEncoderID < 0 ||
        selectedEncoderID >= TrackingManagerInstance->Trackings.size())
        return;
    Tracking* tracking = TrackingManagerInstance->Trackings.at(selectedEncoderID);
    if (ui->cbEncoderType->currentText() == "X Encoder")
    {
        ui->cbLinkToConveyorX->setHidden(false);
        ui->cbConveyorLinkToEncoder->setHidden(false);
        ui->pbConnectEncoder->setHidden(false);
        ui->pbSetEncoderVelocity->setHidden(true);

        QMetaObject::invokeMethod(tracking, "SetEncoderSourceType", Qt::QueuedConnection,
                                  Q_ARG(QString, QStringLiteral("X Encoder")));
    }
    else if (ui->cbEncoderType->currentText() == "Sub Encoder")
    {
        ui->pbConnectEncoder->setHidden(false);
        ui->pbSetEncoderVelocity->setHidden(true);
        QMetaObject::invokeMethod(tracking, "SetEncoderSourceType", Qt::QueuedConnection,
                                  Q_ARG(QString, QStringLiteral("Sub Encoder")));
    }
    else if (ui->cbEncoderType->currentText() == "Virtual Encoder")
    {
        QMetaObject::invokeMethod(tracking, "SetEncoderSourceType", Qt::QueuedConnection,
                                  Q_ARG(QString, QStringLiteral("Virtual Encoder")));
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
        int enid = getIDfromName(ui->cbSelectedEncoder->currentText());

        QMetaObject::invokeMethod(DeviceManagerInstance,
                                  "SetEncoderLinkedConveyor", Qt::QueuedConnection,
                                  Q_ARG(int, enid), Q_ARG(int, conid));
        ui->pbConnectEncoder->setHidden(true);
    } else
    {
        int enid = getIDfromName(ui->cbSelectedEncoder->currentText());

        QMetaObject::invokeMethod(DeviceManagerInstance,
                                  "SetEncoderLinkedConveyor", Qt::QueuedConnection,
                                  Q_ARG(int, enid), Q_ARG(int, -1));
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
        if (objectInfo.trimmed().isEmpty())
            continue;

        Object object;

        QStringList paras = objectInfo.split(",");
        if (paras.count() >= 6)
        {
            bool valuesValid = true;
            const auto parseFinite = [&valuesValid](const QString& value) {
                bool ok = false;
                const float parsed = value.trimmed().toFloat(&ok);
                valuesValid = valuesValid && ok && std::isfinite(parsed);
                return parsed;
            };
            object.X.Image = parseFinite(paras[1]);
            object.Y.Image = parseFinite(paras[2]);
            object.Length.Image = parseFinite(paras[3]);
            object.Width.Image = parseFinite(paras[4]);
            object.Angle.Image = parseFinite(paras[5]);

            if (!valuesValid)
                continue;

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

    // Reflect selected tracking thresholds to UI
    if (TrackingManagerInstance && id >= 0 && id < TrackingManagerInstance->Trackings.count())
    {
        ui->leIoUThreshold->setText(
            QString::number(TrackingManagerInstance->Trackings.at(id)->GetIoUThreshold()));
        ui->leDistanceThreshold->setText(
            QString::number(TrackingManagerInstance->Trackings.at(id)->GetDistanceThreshold()));
    }

    // Sync detecting list name and image processing target with selected tracking
    if (TrackingManagerInstance && id >= 0 && id < TrackingManagerInstance->Trackings.count())
    {
        const QString listName = TrackingManagerInstance->Trackings.at(id)->GetListName();
        if (ui && ui->leDetectingObjectListName)
        {
            ui->leDetectingObjectListName->setText(listName);
        }
        if (ImageProcessingInstance)
        {
            QMetaObject::invokeMethod(
                ImageProcessingInstance, "SetObjectsName", Qt::QueuedConnection,
                Q_ARG(QString, listName));
        }
    }
}

void RobotWindow::ChangeSelectedTrackingEncoder(int id)
{
    Q_UNUSED(id)
    const int trackingId = ui->cbSelectedTracking->currentIndex();
    if (!TrackingManagerInstance || trackingId < 0 ||
        trackingId >= TrackingManagerInstance->Trackings.count())
        return;
    Tracking* tracking = TrackingManagerInstance->Trackings.at(trackingId);
    const QString encoderName = ui->cbTrackingEncoderSource->currentText();
    QMetaObject::invokeMethod(tracking, "SetEncoderName", Qt::QueuedConnection,
                              Q_ARG(QString, encoderName));
}

void RobotWindow::SaveTrackingManager()
{
    const int selectedEncoderID = ui->cbSelectedTracking->currentIndex();
    if (!TrackingManagerInstance || selectedEncoderID < 0 ||
        selectedEncoderID >= TrackingManagerInstance->Trackings.count())
        return;

    Tracking* tracking = TrackingManagerInstance->Trackings.at(selectedEncoderID);
    const QVector3D velocityVector = VariableManager::instance()
        .getVarScoped(ProjectName, ui->leVelocityVector->text()).value<QVector3D>();
    const QString vectorName = ui->leVectorName->text();
    const QString listName = ui->leSelectedTrackingObjectList->text().trimmed();
    const QString encoderName = ui->cbTrackingEncoderSource->currentText();
    const int publishMs = ui->sbTrackingPublishInterval->value();
    const int visionStaleMs = ui->sbTrackingVisionStale->value();
    const int encoderStaleMs = ui->sbTrackingEncoderStale->value();
    const int frameTimeoutMs = ui->sbTrackingFrameTimeout->value();
    const int maxFrames = ui->sbTrackingMaxFrames->value();
    const int maxEncoderReads = ui->sbTrackingMaxEncoderReads->value();

    QMetaObject::invokeMethod(tracking,
        [tracking, velocityVector, vectorName, listName, encoderName,
         publishMs, visionStaleMs, encoderStaleMs, frameTimeoutMs,
         maxFrames, maxEncoderReads]() {
            tracking->VelocityVector = velocityVector;
            tracking->SetVectorName(vectorName);
            if (!listName.isEmpty())
                tracking->SetListName(listName);
            tracking->SetEncoderName(encoderName);
            tracking->ConfigureRealtime(publishMs, visionStaleMs, encoderStaleMs,
                                        frameTimeoutMs, maxFrames, maxEncoderReads);
        }, Qt::QueuedConnection);

    const QString prefix = QString("tracking%1.Realtime.").arg(selectedEncoderID);
    VariableManager::instance().updateBatchScoped(ProjectName, {
        {prefix + "PublishIntervalMs", publishMs},
        {prefix + "VisionStaleMs", visionStaleMs},
        {prefix + "EncoderStaleMs", encoderStaleMs},
        {prefix + "FrameTimeoutMs", frameTimeoutMs},
        {prefix + "MaxPendingFrames", maxFrames},
        {prefix + "MaxPendingEncoderReads", maxEncoderReads}
    }, VariableManager::Persistence::Persistent);
    VariableManager::instance().scheduleSave();
}

void RobotWindow::CalculateMappingMatrixTool()
{
    if (m_pointToolController) {
        if (m_pointToolController->calculateMappingMatrix())
            emit GotMappingMatrix(m_currentMappingMatrix);
    }
}

void RobotWindow::CalculatePointMatrixTool()
{
    if (m_pointToolController) {
        m_pointToolController->calculatePerspectiveMatrix();
    }
}

void RobotWindow::CalibrateCameraIntrinsics()
{
    if (!CameraInstance || !m_imagePipelineController) {
        QMessageBox::warning(this, tr("Lens calibration"), tr("Camera pipeline is not available."));
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle(tr("Camera lens calibration"));
    dialog.setMinimumWidth(560);
    QVBoxLayout* root = new QVBoxLayout(&dialog);
    QLabel* instructions = new QLabel(
        tr("Use a flat chessboard. Columns and rows are INNER corners, not squares. "
           "Capture at least 8 diverse views: center, all corners, different distances and tilts."),
        &dialog);
    instructions->setWordWrap(true);
    root->addWidget(instructions);

    QFormLayout* settings = new QFormLayout;
    QSpinBox* columns = new QSpinBox(&dialog);
    columns->setRange(3, 30);
    columns->setValue(9);
    QSpinBox* rows = new QSpinBox(&dialog);
    rows->setRange(3, 30);
    rows->setValue(6);
    QDoubleSpinBox* squareSize = new QDoubleSpinBox(&dialog);
    squareSize->setRange(0.001, 1000.0);
    squareSize->setDecimals(3);
    squareSize->setValue(25.0);
    squareSize->setSuffix(tr(" mm"));
    settings->addRow(tr("Inner corner columns"), columns);
    settings->addRow(tr("Inner corner rows"), rows);
    settings->addRow(tr("Square size"), squareSize);
    root->addLayout(settings);

    QLabel* liveStatus = new QLabel(tr("Waiting for a camera frame..."), &dialog);
    QLabel* sampleStatus = new QLabel(tr("Accepted samples: 0 / 8 minimum"), &dialog);
    QLabel* profileStatus = new QLabel(&dialog);
    CameraCalibration::Profile existingProfile;
    if (CameraCalibration::loadFromVariables(ProjectName, QStringLiteral("Camera.Intrinsic"),
                                             existingProfile)) {
        profileStatus->setText(
            tr("Current profile: READY — %1x%2, RMS %3 px, %4 samples")
                .arg(existingProfile.imageSize.width()).arg(existingProfile.imageSize.height())
                .arg(existingProfile.rmsErrorPx, 0, 'f', 3).arg(existingProfile.sampleCount));
        profileStatus->setStyleSheet(QStringLiteral("color: rgb(80, 220, 120); font-weight: bold;"));
    } else {
        profileStatus->setText(tr("Current profile: NOT CALIBRATED"));
        profileStatus->setStyleSheet(QStringLiteral("color: rgb(255, 190, 70); font-weight: bold;"));
    }
    root->addWidget(liveStatus);
    root->addWidget(sampleStatus);
    root->addWidget(profileStatus);

    QHBoxLayout* actions = new QHBoxLayout;
    QPushButton* capture = new QPushButton(tr("Capture sample"), &dialog);
    QPushButton* removeLast = new QPushButton(tr("Remove last"), &dialog);
    QPushButton* clear = new QPushButton(tr("Clear samples"), &dialog);
    QPushButton* calculate = new QPushButton(tr("Calculate and apply"), &dialog);
    calculate->setEnabled(false);
    removeLast->setEnabled(false);
    clear->setEnabled(false);
    actions->addWidget(capture);
    actions->addWidget(removeLast);
    actions->addWidget(clear);
    actions->addStretch();
    actions->addWidget(calculate);
    root->addLayout(actions);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    root->addWidget(buttons);

    cv::Mat latestFrame;
    QList<cv::Mat> calibrationImages;
    QVector<QVector3D> viewDescriptors;
    const QMetaObject::Connection frameConnection = connect(
        CameraInstance, &Camera::FrameCaptured, &dialog,
        [&latestFrame, liveStatus](const VisionFrame& frame) {
        latestFrame = frame.image.clone();
        liveStatus->setText(QObject::tr("Live frame: %1 x %2")
                                .arg(latestFrame.cols).arg(latestFrame.rows));
        liveStatus->setStyleSheet(QStringLiteral("color: rgb(100, 200, 255);"));
    });
    if (!CameraInstance->CaptureImage.empty()) {
        latestFrame = CameraInstance->CaptureImage.clone();
        liveStatus->setText(tr("Current frame: %1 x %2").arg(latestFrame.cols).arg(latestFrame.rows));
    }

    auto refreshSampleState = [=, &calibrationImages]() {
        sampleStatus->setText(QObject::tr("Accepted samples: %1 / 8 minimum")
                                  .arg(calibrationImages.size()));
        const bool hasSamples = !calibrationImages.isEmpty();
        removeLast->setEnabled(hasSamples);
        clear->setEnabled(hasSamples);
        calculate->setEnabled(calibrationImages.size() >= 8);
        columns->setEnabled(!hasSamples);
        rows->setEnabled(!hasSamples);
        squareSize->setEnabled(!hasSamples);
    };

    connect(capture, &QPushButton::clicked, &dialog,
            [&, refreshSampleState]() {
        if (latestFrame.empty()) {
            QMessageBox::warning(&dialog, tr("Lens calibration"),
                                 tr("No camera frame is available. Start camera capture first."));
            return;
        }
        cv::Mat gray;
        if (latestFrame.channels() == 1)
            gray = latestFrame;
        else if (latestFrame.channels() == 4)
            cv::cvtColor(latestFrame, gray, cv::COLOR_BGRA2GRAY);
        else
            cv::cvtColor(latestFrame, gray, cv::COLOR_BGR2GRAY);
        std::vector<cv::Point2f> corners;
        const cv::Size board(columns->value(), rows->value());
        const bool found = cv::findChessboardCorners(
            gray, board, corners,
            cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_FAST_CHECK);
        if (!found) {
            liveStatus->setText(tr("Chessboard not found — improve lighting/focus and show the full board"));
            liveStatus->setStyleSheet(QStringLiteral("color: rgb(255, 100, 100); font-weight: bold;"));
            return;
        }

        const cv::Rect bounds = cv::boundingRect(corners);
        const QVector3D descriptor(
            (bounds.x + bounds.width * 0.5f) / latestFrame.cols,
            (bounds.y + bounds.height * 0.5f) / latestFrame.rows,
            static_cast<float>(bounds.area()) / (latestFrame.cols * latestFrame.rows));
        for (const QVector3D& existing : viewDescriptors) {
            if ((existing - descriptor).length() < 0.015f) {
                liveStatus->setText(tr("View is too similar to an existing sample — move or tilt the board"));
                liveStatus->setStyleSheet(QStringLiteral("color: rgb(255, 190, 70); font-weight: bold;"));
                return;
            }
        }
        calibrationImages.append(latestFrame.clone());
        viewDescriptors.append(descriptor);
        liveStatus->setText(tr("Chessboard accepted (%1 corners)")
                                .arg(static_cast<qulonglong>(corners.size())));
        liveStatus->setStyleSheet(QStringLiteral("color: rgb(80, 220, 120); font-weight: bold;"));
        refreshSampleState();
    });
    connect(removeLast, &QPushButton::clicked, &dialog, [&, refreshSampleState]() {
        if (!calibrationImages.isEmpty()) {
            calibrationImages.removeLast();
            viewDescriptors.removeLast();
            refreshSampleState();
        }
    });
    connect(clear, &QPushButton::clicked, &dialog, [&, refreshSampleState]() {
        calibrationImages.clear();
        viewDescriptors.clear();
        refreshSampleState();
    });
    connect(calculate, &QPushButton::clicked, &dialog, [&]() {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        const CameraCalibration::Result result = CameraCalibration::calibrate(
            calibrationImages, QSize(columns->value(), rows->value()), squareSize->value());
        QApplication::restoreOverrideCursor();
        if (!result.isValid) {
            QMessageBox::warning(&dialog, tr("Lens calibration"), result.errorMessage);
            return;
        }
        if (!CameraCalibration::saveToVariables(ProjectName, QStringLiteral("Camera.Intrinsic"),
                                                result.profile)) {
            QMessageBox::critical(&dialog, tr("Lens calibration"),
                                  tr("Calibration succeeded but the profile could not be saved."));
            return;
        }
        m_imagePipelineController->setIntrinsicCalibration(result.profile);
        VariableManager::instance().updateVarScoped(
            ProjectName, QStringLiteral("Camera.IntrinsicStatus.IsValid"), true);
        VariableManager::instance().updateVarScoped(
            ProjectName, QStringLiteral("Camera.IntrinsicStatus.RmsErrorPx"), result.profile.rmsErrorPx);
        VariableManager::instance().updateVarScoped(
            ProjectName, QStringLiteral("Camera.IntrinsicStatus.MaximumViewErrorPx"),
            result.profile.maximumViewErrorPx);
        dialog.accept();
        QMessageBox::information(
            this, tr("Lens calibration"),
            tr("Profile applied successfully. RMS: %1 px; worst view: %2 px.\n\n"
               "Image-to-world mapping is now invalid and must be calibrated again.")
                .arg(result.profile.rmsErrorPx, 0, 'f', 3)
                .arg(result.profile.maximumViewErrorPx, 0, 'f', 3));
    });

    dialog.exec();
    disconnect(frameConnection);
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

void RobotWindow::ClearDetectObjects()
{
    int id = ui->cbTrackingThreadForCamera->currentIndex();
    QMetaObject::invokeMethod(TrackingManagerInstance->Trackings[id], "ClearTrackedObjects", Qt::QueuedConnection);
    VariableManager::instance().removeVarScoped(ProjectName, ui->leDetectingObjectListName->text());

    QTimer::singleShot(300, [this](){
        ui->pbCapture->clicked();
    });
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

    // Choose connection type for Slider
    {
        QStringList connectionItems; connectionItems << "Serial" << "Socket";
        bool ok=false; QString connectionType = QInputDialog::getItem(nullptr, tr("Connection"), tr("Type:"), connectionItems, 0, false, &ok);
        if (!ok || connectionType.isEmpty()) return;
        if (connectionType == "Socket") {
            bool ok2=false; QString address = QInputDialog::getText(nullptr, tr("Socket Address"), tr("IP:PORT"), QLineEdit::Normal, "127.0.0.1:8858", &ok2);
            if (ok2 && !address.isEmpty()) {
                emit ChangeDeviceState(ui->cbSelectedSlider->currentText(), true, address);
            }
            return;
        }
    }

    const QString comName = promptSerialPortPath(tr("Serial Connection"));
    if (!comName.isEmpty())
    {
        bool ok2; Q_UNUSED(ok2);
        QString baudrate = QInputDialog::getText(nullptr, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
        emit ChangeDeviceState(ui->cbSelectedSlider->currentText(), true, comName);
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

    // Ask for connection type (COM or WIFI)
    QStringList connectionItems;
    connectionItems << "Serial" << "Socket";
    bool ok = false;
    QString connectionType = QInputDialog::getItem(nullptr, tr("Connection"), tr("Type:"), connectionItems, 0, false, &ok);
    if (!ok || connectionType.isEmpty()) return;

    if (connectionType == "Socket")
    {
        bool ok2 = false;
        QString address = QInputDialog::getText(nullptr, tr("Socket Address"), tr("IP:PORT"), QLineEdit::Normal, "127.0.0.1:8859", &ok2);
        if (ok2 && !address.isEmpty())
        {
            emit ChangeDeviceState(ui->cbSelectedDevice->currentText(), true, address);
        }
        return;
    }

    const QString comName = promptSerialPortPath(tr("Serial Connection"));
    if (!comName.isEmpty())
    {
        bool ok2;
        QString baudrate = QInputDialog::getText(nullptr, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
        if (ok2 && !baudrate.isEmpty())
        {
            emit ChangeDeviceState(ui->cbSelectedDevice->currentText(), true, comName);
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

    if (text[text.length() - 1] != '\n')
        text += '\n';

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
        submitManualDeviceCommand(msg, QStringLiteral("manual/terminal"));
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
    // Ki?m tra button state d? quy?t d?nh action
    if (ui->pbRunExternalScript->isChecked()) {
        // Button du?c check - start Python script
        QString pythonPath = ui->lePythonUrl->text();
        
        if (pythonPath.isEmpty()) {
            // Kh�ng c� path, uncheck button
            ui->pbRunExternalScript->setChecked(false);
            qDebug() << "No Python script path specified";
            return;
        }
        
        runPythonFile(pythonPath);
    } else {
        QPointer<QProcess> runningProcess(process);
        if (runningProcess && runningProcess->state() == QProcess::Running) {
            setExternalVisionStatus(QStringLiteral("STOPPING SCRIPT"), QString(),
                                    QStringLiteral("#e0a030"));
            runningProcess->terminate();
            if (runningProcess && !runningProcess->waitForFinished(3000)) {
                runningProcess->kill();
                runningProcess->waitForFinished(1000);
            }
        }
    }
}

void RobotWindow::OpenExternalScriptFolder()
{
    QString current = ui->lePythonUrl->text().trimmed();
    const QString resolved = resolveExternalVisionFile(current);
    if (!resolved.isEmpty())
        current = resolved;
    const QString selected = QFileDialog::getOpenFileName(
        this, tr("Select External Vision detector script"),
        QFileInfo(current).absolutePath(),
        tr("Python scripts (*.py);;All files (*)"));
    if (selected.isEmpty())
        return;
    ui->lePythonUrl->setText(QDir::toNativeSeparators(selected));
    QString detectingKey = ui->cbSelectedDetecting->currentText();
    if (detectingKey.isEmpty())
        detectingKey = QStringLiteral("tracking0");
    VariableManager::instance().updateVarScoped(
        ProjectName, detectingKey + QStringLiteral(".ExternalVision.Script"), selected);
}

QString RobotWindow::resolveExternalVisionFile(const QString& relativePath) const
{
    const QFileInfo provided(relativePath);
    if (provided.isAbsolute() && provided.exists())
        return provided.absoluteFilePath();

    const QString appDir = QCoreApplication::applicationDirPath();
    const QStringList candidates = {
        QDir::current().absoluteFilePath(relativePath),
        QDir(appDir).absoluteFilePath(relativePath),
        QDir(appDir).absoluteFilePath(QStringLiteral("../") + relativePath),
        QDir(appDir).absoluteFilePath(QStringLiteral("../Resources/") + relativePath),
        QDir(appDir).absoluteFilePath(QStringLiteral("../../") + relativePath),
        QDir(appDir).absoluteFilePath(QStringLiteral("../../../") + relativePath)
    };
    for (const QString& candidate : candidates) {
        const QFileInfo info(QDir::cleanPath(candidate));
        if (info.exists())
            return info.absoluteFilePath();
    }
    return QString();
}

void RobotWindow::OpenExternalVisionGuide()
{
    QFile guide(QStringLiteral(":/docs/external-vision.md"));
    if (!guide.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("External Vision"),
                             tr("The embedded External Vision guide is unavailable."));
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle(tr("External Vision — Setup and DXV1 protocol"));
    dialog.resize(920, 720);
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QTextBrowser* browser = new QTextBrowser(&dialog);
    browser->setOpenExternalLinks(true);
    browser->setMarkdown(QString::fromUtf8(guide.readAll()));
    layout->addWidget(browser);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Close, &dialog);
    QPushButton* examplesButton = buttons->addButton(tr("Open examples"),
                                                      QDialogButtonBox::ActionRole);
    connect(examplesButton, &QPushButton::clicked,
            this, &RobotWindow::OpenExternalVisionExample);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttons);
    dialog.exec();
}

void RobotWindow::OpenExternalVisionExample()
{
    const QString example = resolveExternalVisionFile(
        QStringLiteral("script-example/receive_image_json.py"));
    if (example.isEmpty()) {
        QMessageBox::warning(
            this, tr("External Vision"),
            tr("The DXV1 example folder was not found. Reinstall the script-example component."));
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(example).absolutePath()));
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

	QString connectionType = QInputDialog::getItem(nullptr, tr("Connection"), tr("Type:"), connectionItems, 0, false, &ok);

	if (ok)
	{
		if (connectionType == "Socket")
		{
			bool ok2;
			QString address = QInputDialog::getText(nullptr, tr("Socket Address"), tr("IP:PORT"), QLineEdit::Normal, "192.168.1.12:80", &ok2);

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
			QString item = QInputDialog::getItem(nullptr, tr("Serial Connection"), tr("Serial Ports:"), items, 0, false, &ok);
            QString comName = item.mid(0, item.indexOf(" - "));

			if (ok && !item.isEmpty())
			{
				bool ok2;
				QString baudrate = QInputDialog::getText(nullptr, tr("Select Baudrate"), tr("Baudrate:"), QLineEdit::Normal, "115200", &ok2);
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

    if (!msg.endsWith(QLatin1Char('\n')))
        msg += QLatin1Char('\n');

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

void RobotWindow::UpdateCameraConnectedState(bool isOpen, int requestId)
{
    if (!isCameraOpenPending || requestId != cameraOpenRequestId)
    {
        SoftwareLog(QString("Ignoring stale camera open result for request %1").arg(requestId));
        return;
    }

    isCameraOpenPending = false;
    CameraOpenTimeoutTimer.stop();

    QHash<QString, QVariant> cameraState;
    cameraState.insert(QStringLiteral("Camera.Connected"), isOpen);
    cameraState.insert(QStringLiteral("Camera.State"),
                       isOpen ? QStringLiteral("READY") : QStringLiteral("OPEN_FAILED"));
    cameraState.insert(QStringLiteral("Camera.Width"), CameraInstance->Width);
    cameraState.insert(QStringLiteral("Camera.Height"), CameraInstance->Height);
    cameraState.insert(QStringLiteral("Camera.UpdatedAt"),
                       QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    VariableManager::instance().updateBatchScoped(
        ProjectName, cameraState, VariableManager::Persistence::Runtime);

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

void RobotWindow::HandleCameraOpenTimeout()
{
    if (!isCameraOpenPending)
        return;

    isCameraOpenPending = false;
    SoftwareLog("Camera open timed out. Resetting camera state.");

    ui->pbLoadCamera->setText("Load Camera");
    ui->pbLoadCamera->setChecked(false);
    ui->lbCameraState->setEnabled(false);
    ui->pbStartAcquisition->setChecked(false);
    isCameraLoaded = false;
    CameraInstance->IsCameraPause = false;
    CameraInstance->RunningCamera = -1;

    QHash<QString, QVariant> cameraState;
    cameraState.insert(QStringLiteral("Camera.Connected"), false);
    cameraState.insert(QStringLiteral("Camera.State"), QStringLiteral("OPEN_TIMEOUT"));
    cameraState.insert(QStringLiteral("Camera.UpdatedAt"),
                       QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    VariableManager::instance().updateBatchScoped(
        ProjectName, cameraState, VariableManager::Persistence::Runtime);

    QString prefix = ProjectName + "." + ui->cbSelectedDetecting->currentText() + ".";
    UpdateVariable(prefix + "IsOpen", false);

    QMetaObject::invokeMethod(CameraInstance, [this]() {
        if (CameraInstance->WebcamInstance && CameraInstance->WebcamInstance->isOpened())
            CameraInstance->WebcamInstance->release();
    }, Qt::QueuedConnection);

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
  // T�ch t�n ?nh t? fileName
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

    // Hi?n th? ?nh t? imagePath tr�n c?a s? ImageLabel, 
    // khi ngu?i d�ng ch?n m?t ?nh kh�c th� ?nh du?c load v�o c?a s? d�
    // Khi ngu?i d�ng t?t th� x�a c?a s? d�


    if (ImageLabel == NULL)
    {
        ImageLabel = new QLabel();
        ImageLabel->setWindowTitle("Image Viewer");
        ImageLabel->setAttribute(Qt::WA_DeleteOnClose);
        ImageLabel->show();
    }

    ImageLabel->hide();

    ImageLabel->setPixmap(QPixmap(imagePath));
    // Ch?nh c?a s? ImageLabel sao cho v?a v?i ?nh
    ImageLabel->adjustSize();
    //Hi?n th? c?a s? ImageLabel (QLabel) tr�n c?a s? ch�nh
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

void RobotWindow::openPositionVariableDialog()
{
    if (!ui) {
        return;
    }

    QDialog dialog;
    dialog.setWindowTitle(tr("Position Variable"));
    dialog.setModal(true);
    dialog.setWindowModality(Qt::ApplicationModal);

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);

    QLineEdit* nameEdit = new QLineEdit(&dialog);
    nameEdit->setPlaceholderText("#PickPoint");
    if (!m_lastPositionVariableName.isEmpty()) {
        nameEdit->setText(m_lastPositionVariableName);
    }
    mainLayout->addWidget(nameEdit);

    auto createSpinBox = [&dialog]() {
        QDoubleSpinBox* sb = new QDoubleSpinBox(&dialog);
        sb->setDecimals(3);
        sb->setRange(-10000.0, 10000.0);
        sb->setSingleStep(1.0);
        return sb;
    };

    QDoubleSpinBox* xSpin = createSpinBox();
    QDoubleSpinBox* ySpin = createSpinBox();
    QDoubleSpinBox* zSpin = createSpinBox();

    QGridLayout* coordsLayout = new QGridLayout();
    coordsLayout->addWidget(new QLabel("X", &dialog), 0, 0);
    coordsLayout->addWidget(xSpin, 0, 1);
    coordsLayout->addWidget(new QLabel("Y", &dialog), 1, 0);
    coordsLayout->addWidget(ySpin, 1, 1);
    coordsLayout->addWidget(new QLabel("Z", &dialog), 2, 0);
    coordsLayout->addWidget(zSpin, 2, 1);
    mainLayout->addLayout(coordsLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* useCurrentButton = new QPushButton(tr("Use Current"), &dialog);
    QPushButton* loadButton = new QPushButton(tr("Load"), &dialog);
    QPushButton* saveButton = new QPushButton(tr("Save"), &dialog);
    QPushButton* cancelButton = new QPushButton(tr("Cancel"), &dialog);
    buttonLayout->addWidget(useCurrentButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    auto captureRobotPosition = [this, xSpin, ySpin, zSpin]() {
        if (!isRobotParametersValid()) {
            QMessageBox::warning(this, tr("Robot Position"),
                                 tr("Robot position is not available yet."));
            return;
        }
        RobotPara params = getSafeRobotParameters();
        xSpin->setValue(params.X);
        ySpin->setValue(params.Y);
        zSpin->setValue(params.Z);
    };

    auto loadVariable = [this, nameEdit, xSpin, ySpin, zSpin]() {
        const QString varName = normalizePositionVariableName(nameEdit->text());
        if (varName.isEmpty()) {
            QMessageBox::warning(this, tr("Position Variable"),
                                 tr("Please enter a variable name."));
            return;
        }
        QVariant value = VariableManager::instance().getVarScoped(ProjectName, varName, QVariant());
        QVector3D vector;
        if (!tryConvertVariantToVector3D(value, vector)) {
            QMessageBox::warning(this, tr("Position Variable"),
                                 tr("Variable \"%1\" is missing or is not a 3D position.").arg(varName));
            return;
        }
        xSpin->setValue(vector.x());
        ySpin->setValue(vector.y());
        zSpin->setValue(vector.z());
    };

    auto saveVariable = [this, &dialog, nameEdit, xSpin, ySpin, zSpin]() {
        const QString varName = normalizePositionVariableName(nameEdit->text());
        if (varName.isEmpty()) {
            QMessageBox::warning(&dialog, tr("Position Variable"),
                                 tr("Please enter a variable name."));
            return;
        }
        QVector3D vector(xSpin->value(), ySpin->value(), zSpin->value());
        VariableManager::instance().updateVarScoped(ProjectName, varName, QVariant::fromValue(vector));
        VariableManager::instance().scheduleSave();
        insertOrUpdatePositionDeclaration(varName, vector);
        m_lastPositionVariableName = varName;
        SoftwareLog(QString("Saved %1 = (%2, %3, %4)")
                        .arg(varName)
                        .arg(vector.x(), 0, 'f', 3)
                        .arg(vector.y(), 0, 'f', 3)
                        .arg(vector.z(), 0, 'f', 3));
        dialog.accept();
    };

    connect(useCurrentButton, &QPushButton::clicked, this, captureRobotPosition);
    connect(loadButton, &QPushButton::clicked, this, loadVariable);
    connect(saveButton, &QPushButton::clicked, this, saveVariable);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

QString RobotWindow::normalizePositionVariableName(const QString &rawName) const
{
    QString name = rawName;
    name.replace(" ", "");
    return name.trimmed();
}

bool RobotWindow::tryConvertVariantToVector3D(const QVariant &value, QVector3D &out) const
{
    if (!value.isValid()) {
        return false;
    }

    if (value.canConvert<QVector3D>()) {
        out = value.value<QVector3D>();
        return true;
    }

    if (value.canConvert<QString>()) {
        QString text = value.toString().trimmed();
        if (text.isEmpty()) {
            return false;
        }
        const QStringList parts = text.split(QRegularExpression("[,\\s]+"), Qt::SkipEmptyParts);
        if (parts.size() < 3) {
            return false;
        }

        bool okX = false, okY = false, okZ = false;
        double x = parts[0].toDouble(&okX);
        double y = parts[1].toDouble(&okY);
        double z = parts[2].toDouble(&okZ);
        if (okX && okY && okZ) {
            out = QVector3D(x, y, z);
            return true;
        }
    }

    return false;
}

void RobotWindow::insertOrUpdatePositionDeclaration(const QString &varName, const QVector3D &vector)
{
    if (!ui || varName.isEmpty()) {
        return;
    }

    QString text = ui->pteGcodeArea->toPlainText();
    QStringList lines = text.split('\n');
    QString declaration = QString("%1 = (%2, %3, %4)")
        .arg(varName)
        .arg(vector.x(), 0, 'f', 3)
        .arg(vector.y(), 0, 'f', 3)
        .arg(vector.z(), 0, 'f', 3);

    bool found = false;
    int insertIndex = 0;

    static const QRegularExpression lineNumberRegex("^N\\d+\\s*",
                                                    QRegularExpression::CaseInsensitiveOption);

    for (int i = 0; i < lines.size(); ++i) {
        QString trimmed = lines[i].trimmed();
        if (trimmed.isEmpty()) {
            if (insertIndex == i) {
                insertIndex = i + 1;
            }
            continue;
        }
        QString numberPrefix;
        QString content = trimmed;
        QRegularExpressionMatch match = lineNumberRegex.match(content);
        if (match.hasMatch()) {
            int prefixLen = match.capturedLength();
            numberPrefix = content.left(prefixLen).trimmed();
            content.remove(0, prefixLen);
            content = content.trimmed();
        }
        if (content.startsWith("#")) {
            insertIndex = i + 1;
            if (content.startsWith(varName)) {
                QString linePrefix = numberPrefix.isEmpty() ? QString() : numberPrefix + " ";
                lines[i] = linePrefix + declaration;
                found = true;
                break;
            }
            continue;
        }
        break;
    }

    if (!found) {
        lines.insert(insertIndex, declaration);
    }

    QString newText = lines.join("\n");
    if (newText == text) {
        return;
    }

    QScrollBar* vBar = ui->pteGcodeArea->verticalScrollBar();
    int oldValue = vBar ? vBar->value() : 0;

    ui->pteGcodeArea->setPlainText(newText);

    if (vBar) {
        vBar->setValue(qMin(oldValue, vBar->maximum()));
    }
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
    QStringList idParts = fullName.split(QRegularExpression("[^\\d]+"), Qt::SkipEmptyParts);
    QString id = idParts.isEmpty() ? QString() : idParts.last();
    return id.toInt();
}

void RobotWindow::runPythonFile(QString filePath)
{
    filePath = filePath.trimmed();
    if (!QFileInfo(filePath).isAbsolute())
        filePath = resolveExternalVisionFile(filePath);
    const QFileInfo fileInfo(filePath);
    if (filePath.isEmpty() || !fileInfo.isFile()) {
        ui->pbRunExternalScript->setChecked(false);
        setExternalVisionStatus(QStringLiteral("SCRIPT NOT FOUND"),
                                ui->lePythonUrl->text().trimmed(),
                                QStringLiteral("#ef5350"));
        QMessageBox::warning(this, tr("External Vision"),
                             tr("Detector script not found:\n%1")
                                 .arg(ui->lePythonUrl->text().trimmed()));
        return;
    }

    const QString pythonExePath = externalVisionPythonEdit
        ? externalVisionPythonEdit->text().trimmed()
        : QSettings().value(QStringLiteral("ExternalVision/PythonExecutable"),
                            QStringLiteral("python")).toString();
    const QString host = ConnectionManager->hostAddress;
    const QString port = QString::number(ConnectionManager->Server->serverPort());
    const QStringList arguments = {
        fileInfo.absoluteFilePath(),
        QStringLiteral("--host"), host,
        QStringLiteral("--port"), port
    };

    // N?u qu� tr�nh ch?y file python d� t?n t?i th� t?t n�
    QPointer<QProcess> previousProcess(process);
    if (previousProcess && previousProcess->state() == QProcess::Running) {
        previousProcess->terminate();
        if (previousProcess && !previousProcess->waitForFinished(3000)) {
            previousProcess->kill();
            previousProcess->waitForFinished(1000);
        }
    }

    if (process != nullptr && process->state() == QProcess::NotRunning) {
        process->deleteLater();
        process = nullptr;
    }

    process = new QProcess(this);
    QProcess* launchedProcess = process;
    launchedProcess->setWorkingDirectory(fileInfo.absolutePath());
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    environment.insert(QStringLiteral("DELTAX_PROJECT"), ProjectName);
    environment.insert(QStringLiteral("DELTAX_IMAGE_SOURCE"), ui->cbImageSource->currentText());
    environment.insert(QStringLiteral("DELTAX_MODEL_PATH"), getModelPath());
    environment.insert(QStringLiteral("DELTAX_OBJECT_WIDTH"), ui->leWRec->text());
    environment.insert(QStringLiteral("DELTAX_OBJECT_HEIGHT"), ui->leLRec->text());
    launchedProcess->setProcessEnvironment(environment);

    connect(launchedProcess, &QProcess::started, this, [this, fileInfo]() {
        setExternalVisionStatus(QStringLiteral("SCRIPT RUNNING"), fileInfo.fileName(),
                                QStringLiteral("#42a5f5"));
        SoftwareLog(QStringLiteral("External Vision script started: ") +
                    fileInfo.absoluteFilePath());
    });
    connect(launchedProcess, &QProcess::readyReadStandardOutput, this,
            [launchedProcess]() {
        const QString output = QString::fromUtf8(launchedProcess->readAllStandardOutput()).trimmed();
        if (!output.isEmpty())
            SoftwareLog(QStringLiteral("External Vision: ") + output);
    });
    connect(launchedProcess, &QProcess::readyReadStandardError, this,
            [launchedProcess]() {
        const QString output = QString::fromUtf8(launchedProcess->readAllStandardError()).trimmed();
        if (!output.isEmpty())
            SoftwareLog(QStringLiteral("External Vision stderr: ") + output);
    });
    connect(launchedProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, launchedProcess](int exitCode, QProcess::ExitStatus exitStatus) {
        const QString detail = tr("Exit code %1 (%2)")
            .arg(exitCode)
            .arg(exitStatus == QProcess::NormalExit ? tr("normal") : tr("crashed"));
        setExternalVisionStatus(QStringLiteral("SCRIPT STOPPED"), detail,
                                exitCode == 0 ? QStringLiteral("#e0a030")
                                              : QStringLiteral("#ef5350"));
        ui->pbRunExternalScript->setChecked(false);
        if (process == launchedProcess)
            process = nullptr;
        launchedProcess->deleteLater();
    });
    connect(launchedProcess, &QProcess::errorOccurred, this,
            [this, launchedProcess](QProcess::ProcessError processError) {
        setExternalVisionStatus(QStringLiteral("SCRIPT ERROR"),
                                launchedProcess->errorString(),
                                QStringLiteral("#ef5350"));
        ui->pbRunExternalScript->setChecked(false);
        if (processError == QProcess::FailedToStart) {
            if (process == launchedProcess)
                process = nullptr;
            launchedProcess->deleteLater();
        }
    });

    setExternalVisionStatus(QStringLiteral("STARTING SCRIPT"), fileInfo.fileName(),
                            QStringLiteral("#42a5f5"));
    launchedProcess->start(pythonExePath, arguments);
}

QString RobotWindow::getModelPath()
{
    // 1. Ki?m tra t? setting tru?c
    QSettings settings;
    QString savedModelPath = settings.value("ExternalScript/ModelPath", "").toString();
    if (!savedModelPath.isEmpty() && QFile::exists(savedModelPath)) {
        return savedModelPath;
    }
    
    // 2. T? d?ng detect t? project folder
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
    
    // 3. Fallback - return empty ho?c default path
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

    if (ui->cbAutoUpdateObjectsDisplay->currentIndex() == 1)
    {
        UpdateObjectsToView();
    }
}

bool RobotWindow::isRobotParametersValid() const
{
    return !RobotParameters.isEmpty() && RbID >= 0 && RbID < RobotParameters.size();
}

RobotPara RobotWindow::getSafeRobotParameters() const
{
    if (isRobotParametersValid()) {
        return RobotParameters[RbID];
    }
    return RobotPara(); // Return default-constructed RobotPara if not valid
}

void RobotWindow::updateCameraInfoDisplay()
{
    // Get actual image size from CaptureImage to ensure accuracy
    int width = 0;
    int height = 0;
    
    if (CameraInstance != nullptr)
    {
        if (!CameraInstance->CaptureImage.empty())
        {
            width = CameraInstance->CaptureImage.cols;
            height = CameraInstance->CaptureImage.rows;
        }
        else
        {
            width = CameraInstance->OriginWidth;
            height = CameraInstance->OriginHeight;
        }
    }
    
    float ratio = ui->gvImageViewer->GetRatio() * 100;
    ui->lbMatSize->setText(QString("Original: %1x%2").arg(width).arg(height));
    ui->lbDisplayRatio->setText(QString("Ratio: %1%").arg(ratio));
}



void RobotWindow::handleLogMessage(QString message)
{
    // Display log message in software log with GScript prefix
    QString logEntry = QString("[GScript] %1").arg(message);
    SoftwareLog(logEntry);
}

void RobotWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event); // G?i h�m co b?n

//    int elapsed = performanceTimer.elapsed(); // L?y th?i gian d� tr�i qua t? l?n cu?i
//    qDebug() << "Th?i gian gi?a hai l?n g?i paintEvent:" << elapsed << "milliseconds";
//    performanceTimer.restart(); // Kh?i d?ng l?i timer cho l?n g?i k? ti?p
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
        const QString compatibilityError =
            DeltaXPluginContract::compatibilityError(loader.metaData());
        if (!compatibilityError.isEmpty())
        {
            const QString error = QString("Plugin '%1' is incompatible: %2")
                                      .arg(pluginName, compatibilityError);
            qWarning() << error;
            failedPlugins << pluginName;
            continue;
        }

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

        // ? Safe UI creation with validation
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

        // ? Success - add plugin safely
        QString pluginTitle = pluginWidget->GetTitle();
        if (pluginTitle.isEmpty()) {
            pluginTitle = pluginWidget->GetName(); // Fallback to name
        }
        
        ui->twModule->addTab(pluginUI, pluginTitle);
        pluginList->append(pluginWidget);
        
        // ? Connect plugin signals safely
        connectPluginSignals(pluginWidget);
        
        successCount++;
        qInfo() << "Successfully loaded plugin:" << pluginWidget->GetName();
        SoftwareLog(QString("Successfully loaded plugin: %1").arg(pluginWidget->GetName()));
    }
    
    // ? User feedback
    if (successCount > 0) {
        qInfo() << QString("Successfully loaded %1 plugins").arg(successCount);
        SoftwareLog(QString("Plugin System: Successfully loaded %1 plugins").arg(successCount));
    }
    
    if (!failedPlugins.isEmpty()) {
        QString failedList = failedPlugins.join(", ");
        qWarning() << QString("Failed to load plugins: %1").arg(failedList);
        
        // ? Log failed plugins to software debug (no popup)
        if (failedPlugins.size() > 0) {
            SoftwareLog(QString("Plugin Loading Warning: Failed to load plugins: %1")
                       .arg(failedList));
        }
    }

    updateIndustrialCameraAvailability();
}

void RobotWindow::updateIndustrialCameraAvailability()
{
    industrialCameraBackendAvailable = false;
    industrialCameraBackendStatus = QStringLiteral(
        "GigE/USB3 Vision unavailable: industrial camera plugin is not installed");

    if (industrialCameraPlugin) {
        const QVariant availableProperty =
            industrialCameraPlugin->property("cameraBackendAvailable");
        industrialCameraBackendAvailable = availableProperty.isValid()
            ? availableProperty.toBool() : true;
        const QString pluginStatus =
            industrialCameraPlugin->property("cameraBackendStatus").toString();
        if (!pluginStatus.isEmpty())
            industrialCameraBackendStatus = pluginStatus;
        else if (industrialCameraBackendAvailable)
            industrialCameraBackendStatus = QStringLiteral(
                "GigE/USB3 Vision backend is ready");
    }

    const int industrialIndex =
        ui->cbSourceForImageProvider->findText(QStringLiteral("Industrial Camera"));
    const int webcamIndex =
        ui->cbSourceForImageProvider->findText(QStringLiteral("Webcam"));
    if (webcamIndex >= 0) {
        ui->cbSourceForImageProvider->setItemData(
            webcamIndex,
            QStringLiteral("USB/USB3 UVC camera via Media Foundation/DirectShow; no vendor SDK required"),
            Qt::ToolTipRole);
    }
    if (industrialIndex >= 0) {
        ui->cbSourceForImageProvider->setItemData(
            industrialIndex, industrialCameraBackendStatus, Qt::ToolTipRole);
        if (auto* model = qobject_cast<QStandardItemModel*>(
                ui->cbSourceForImageProvider->model())) {
            if (QStandardItem* item = model->item(industrialIndex))
                item->setEnabled(industrialCameraBackendAvailable);
        }

        if (!industrialCameraBackendAvailable &&
            ui->cbSourceForImageProvider->currentIndex() == industrialIndex) {
            if (webcamIndex >= 0)
                ui->cbSourceForImageProvider->setCurrentIndex(webcamIndex);
        }
    }

    QHash<QString, QVariant> backendState;
    backendState.insert(QStringLiteral("Camera.Backends.UvcUsb.Available"), true);
    backendState.insert(QStringLiteral("Camera.Backends.Industrial.Available"),
                        industrialCameraBackendAvailable);
    backendState.insert(QStringLiteral("Camera.Backends.Industrial.Status"),
                        industrialCameraBackendStatus);
    VariableManager::instance().updateBatchScoped(ProjectName, backendState);

    SoftwareLog(QStringLiteral("Camera backend: %1")
                    .arg(industrialCameraBackendStatus));
}

QList<DeltaXPlugin*> *RobotWindow::getPluginList()
{
    return pluginList;
}

// ? Safe plugin signal connection
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
            connect(plugin, &DeltaXPlugin::CaptureError,
                    CameraInstance, &Camera::OnExternalCaptureFailed);
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

// ? Find plugin by name safely
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

    return m_variableManager->getVarScoped(ProjectName, key, defaultValue);
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

    // Commit the whole UI/device change with one lock acquisition.
    m_variableManager->updateBatchScoped(ProjectName, m_pendingUpdates);
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

// ========== CONVEYOR VISUALIZATION IMPLEMENTATION ==========

void RobotWindow::setupConveyorVisualization()
{
    // Create conveyor visualization widget
    conveyorViz = new ConveyorVisualization(this);
    
    // Replace the placeholder widget in UI
    QWidget* placeholder = ui->wConveyorCanvas;
    if (placeholder && placeholder->parentWidget()) {
        QLayout* layout = placeholder->parentWidget()->layout();
        if (layout) {
            // Remove placeholder and add our visualization
            layout->removeWidget(placeholder);
            layout->addWidget(conveyorViz);
            placeholder->deleteLater();
        }
    }
    
    // Configure visualization bounds with (0,0) at center
    // X-axis: ±400mm (vertical in real world), Y-axis: ±800mm (horizontal conveyor)
    conveyorViz->setConveyorBounds(-400, 400, -800, 800);
    
    // Set conveyor direction along Y-axis (horizontal movement)
    conveyorViz->setConveyorDirection(QVector3D(0, 1, 0));  // Positive Y direction
    
    // Setup update timer to refresh visualization periodically
    // Reduced frequency to minimize performance impact
    QTimer* vizTimer = new QTimer(this);
    connect(vizTimer, &QTimer::timeout, this, &RobotWindow::updateConveyorVisualization);
    vizTimer->start(200); // Update every 200ms (5 FPS) - reduced from 100ms for better performance
    
    // Start conveyor animation AFTER everything is set up
    conveyorViz->startAnimation();
    
    SoftwareLog("Conveyor visualization setup completed");
}

void RobotWindow::updateConveyorVisualization()
{
    // Enhanced null checks to prevent crashes
    if (!conveyorViz) {
        return;
    }
    
    if (!TrackingManagerInstance) {
        // Clear visualization if no tracking manager
        conveyorViz->updateObjects(QVector<ObjectInfo>());
        return;
    }
    
    // Additional safety check for Trackings container
    if (TrackingManagerInstance->Trackings.isEmpty()) {
        // Clear visualization if no tracking instances
        conveyorViz->updateObjects(QVector<ObjectInfo>());
        return;
    }
    
    // Get objects from all tracking instances with minimal copying
    QVector<ObjectInfo> allObjects;
    allObjects.reserve(100); // Pre-allocate to avoid reallocations
    
    // Safe iteration with bounds checking
    int trackingCount = TrackingManagerInstance->Trackings.count();
    for (int i = 0; i < trackingCount; i++) {
        // Additional bounds check
        if (i >= TrackingManagerInstance->Trackings.size()) {
            break; // Safety exit if container changed during iteration
        }
        
        Tracking* tracking = TrackingManagerInstance->Trackings.at(i);
        if (tracking) {
            try {
                // Thread-safe copy of objects using public method
                QVector<ObjectInfo> trackingObjects = tracking->getTrackedObjectsCopy();
                
                // Only process if there are objects to avoid unnecessary operations
                if (!trackingObjects.isEmpty()) {
                    allObjects.append(trackingObjects);
                }
            } catch (...) {
                // Handle any exceptions during object copying
                qDebug() << "Warning: Exception occurred while copying tracking objects from instance" << i;
                continue;
            }
        }
    }
    
    // Only update visualization if objects changed or every few cycles
    static int updateCounter = 0;
    static int lastObjectCount = -1;
    
    bool forceUpdate = (++updateCounter % 5 == 0); // Force update every 5 cycles (1 second)
    bool objectsChanged = (allObjects.size() != lastObjectCount);
    
    if (forceUpdate || objectsChanged) {
        try {
            // Update visualization with all objects
            if (conveyorViz) { // Double-check conveyorViz is still valid
                conveyorViz->updateObjects(allObjects);
            }
            
            // Update object count display
            updateObjectCount();
            
            lastObjectCount = allObjects.size();
        } catch (...) {
            qDebug() << "Warning: Exception occurred during conveyor visualization update";
        }
    }
}

// ========== OBJECT MANAGEMENT IMPLEMENTATIONS ==========

void RobotWindow::AddObjectAtPosition()
{
    SoftwareLog("AddObjectAtPosition() called");
    
    // Check if TrackingManager is available
    if (!TrackingManagerInstance) {
        SoftwareLog("Error: TrackingManagerInstance is null");
        return;
    }
    
    if (TrackingManagerInstance->Trackings.isEmpty()) {
        SoftwareLog("Error: No tracking instances available");
        return;
    }
    
    // Get input values from the new UI controls
    float x = ui->leAddObjectX->text().isEmpty() ? 0.0f : ui->leAddObjectX->text().toFloat();
    float y = ui->leAddObjectY->text().isEmpty() ? 0.0f : ui->leAddObjectY->text().toFloat();
    float width = ui->leAddObjectWidth->text().toFloat();
    float height = ui->leAddObjectHeight->text().toFloat();
    
    // Validate inputs
    if (width <= 0) width = 20.0f;
    if (height <= 0) height = 40.0f;
    
    SoftwareLog(QString("Input values: x=%1, y=%2, w=%3, h=%4").arg(x).arg(y).arg(width).arg(height));
    
    // Get current tracking instance - use first available if cbSelectedTracking is empty
    int selectedEncoderID = ui->cbSelectedTracking->currentIndex();
    
    if (selectedEncoderID < 0 || selectedEncoderID >= TrackingManagerInstance->Trackings.count()) {
        SoftwareLog(QString("Warning: Selected tracking ID %1 invalid, using first tracking instance (0)").arg(selectedEncoderID));
        selectedEncoderID = 0;
    }
    
    // Create object at specified position
    QVector3D position(x, y, 0); // Z = 0 for 2D tracking
    
    // Random angle for variety
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(-180, 180);
    int angle = distribution(generator);
    
    ObjectInfo object(-1, 0, position, width, height, angle); // UID will be assigned automatically
    
    // Add object to tracking instance
    QString listName = TrackingManagerInstance->Trackings.at(selectedEncoderID)->GetListName();
    SoftwareLog(QString("Adding object to tracking list: %1").arg(listName));
    
    TrackingManagerInstance->AddObjectToTracking(listName, object);
    
    SoftwareLog(QString("Object added at position (%1, %2) with size %3x%4mm to list '%5'")
                .arg(x).arg(y).arg(width).arg(height).arg(listName));
}

void RobotWindow::AddRandomObject()
{
    SoftwareLog("AddRandomObject() called - starting random object generation");
    
    // Check if TrackingManager is available
    if (!TrackingManagerInstance) {
        SoftwareLog("Error: TrackingManagerInstance is null");
        return;
    }
    
    if (TrackingManagerInstance->Trackings.isEmpty()) {
        SoftwareLog("Error: No tracking instances available");
        return;
    }
    
    // Generate random position within conveyor bounds
    std::random_device rd;  // Better seed
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> xDist(-200, 200);  // X range
    std::uniform_real_distribution<float> yDist(-200, 200);  // Y range
    std::uniform_real_distribution<float> sizeDist(15, 50);  // Size range
    std::uniform_int_distribution<int> angleDist(-180, 180);
    
    float x = xDist(generator);
    float y = yDist(generator);
    float width = sizeDist(generator);
    float height = sizeDist(generator);
    int angle = angleDist(generator);
    
    SoftwareLog(QString("Generated random values: x=%1, y=%2, w=%3, h=%4, angle=%5")
                .arg(x, 0, 'f', 1).arg(y, 0, 'f', 1).arg(width, 0, 'f', 1).arg(height, 0, 'f', 1).arg(angle));
    
    // Update UI fields to show generated values
    ui->leAddObjectX->setText(QString::number(x, 'f', 1));
    ui->leAddObjectY->setText(QString::number(y, 'f', 1));
    ui->leAddObjectWidth->setText(QString::number(width, 'f', 1));
    ui->leAddObjectHeight->setText(QString::number(height, 'f', 1));
    
    // Get current tracking instance - use first available if cbSelectedTracking is empty
    int selectedEncoderID = ui->cbSelectedTracking->currentIndex();
    
    if (selectedEncoderID < 0 || selectedEncoderID >= TrackingManagerInstance->Trackings.count()) {
        SoftwareLog(QString("Warning: Selected tracking ID %1 invalid, using first tracking instance (0)").arg(selectedEncoderID));
        selectedEncoderID = 0;
    }
    
    // Create and add object
    QVector3D position(x, y, 0);
    ObjectInfo object(-1, 0, position, width, height, angle);
    
    QString listName = TrackingManagerInstance->Trackings.at(selectedEncoderID)->GetListName();
    SoftwareLog(QString("Adding object to tracking list: %1").arg(listName));
    
    TrackingManagerInstance->AddObjectToTracking(listName, object);
    
    SoftwareLog(QString("Random object added at (%1, %2) with size %3x%4mm to list '%5'")
                .arg(x, 0, 'f', 1).arg(y, 0, 'f', 1).arg(width, 0, 'f', 1).arg(height, 0, 'f', 1).arg(listName));
}

void RobotWindow::ClearAllTrackedObjects()
{
    // Clear objects from all tracking instances
    for (int i = 0; i < TrackingManagerInstance->Trackings.count(); i++) {
        QString listName = TrackingManagerInstance->Trackings.at(i)->GetListName();
        TrackingManagerInstance->ClearObjects(listName);
    }
    
    // Clear input fields
    ui->leAddObjectX->clear();
    ui->leAddObjectY->clear();
    
    SoftwareLog("All tracked objects cleared");
}

void RobotWindow::updateObjectCount()
{
    if (!TrackingManagerInstance || TrackingManagerInstance->Trackings.isEmpty()) {
        ui->lblObjectCount->setText("Objects: 0");
        return;
    }
    
    // Performance optimization: Cache object count to avoid frequent expensive operations
    static int cachedObjectCount = -1;
    static QElapsedTimer lastUpdateTime;
    
    // Only recalculate if enough time has passed (500ms minimum)
    if (!lastUpdateTime.isValid() || lastUpdateTime.elapsed() > 500) {
        int totalObjects = 0;
        
        // Count total objects across all tracking instances with safety checks
        int trackingCount = TrackingManagerInstance->Trackings.count();
        for (int i = 0; i < trackingCount; i++) {
            // Additional bounds check
            if (i >= TrackingManagerInstance->Trackings.size()) {
                break; // Safety exit if container changed during iteration
            }
            
            Tracking* tracking = TrackingManagerInstance->Trackings.at(i);
            if (tracking) {
                try {
                    // Use more efficient method if available, or cache the result
                    QVector<ObjectInfo> objects = tracking->getTrackedObjectsCopy();
                    totalObjects += objects.size();
                } catch (...) {
                    qDebug() << "Warning: Exception occurred while counting objects from tracking instance" << i;
                    continue;
                }
            }
        }
        
        // Only update UI if count actually changed
        if (totalObjects != cachedObjectCount) {
            ui->lblObjectCount->setText(QString("Objects: %1").arg(totalObjects));
            cachedObjectCount = totalObjects;
        }
        
        lastUpdateTime.restart();
    }
}
