#ifndef ROBOTWINDOW_H
#define ROBOTWINDOW_H

// ========== SYSTEM INCLUDES ==========
#include <stdio.h>
#include <random>

// ========== QT INCLUDES ==========
#include <QCloseEvent>
#include <QComboBox>
#include <QDesktopServices>
#include <QDialogButtonBox>
#include <QElapsedTimer>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLayout>
#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QMovie>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPluginLoader>
#include <QProcess>
#include <QRandomGenerator>
#include <QSettings>
#include <QStackedWidget>
#include <QSvgWidget>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QVBoxLayout>
#include <QVersionNumber>
#include <QtMultimedia/QCameraInfo>
#include <QtOpenGL>
#include <qfiledialog.h>
#include <qmath.h>

// ========== OPENCV INCLUDES ==========
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// ========== PROJECT INCLUDES ==========
#include <SocketConnectionManager.h>
#include <UnityTool.h>
#include <DeltaVisualizer.h>
#include <FilterWindow.h>
#include <ImageUnity.h>
#include <GcodeReference.h>
#include <DrawingExporter.h>
#include <device/DeviceManager.h>
#include "device/camera.h"
#include "TrackingManager.h"
#include "ObjectInfo.h"
#include "PointTool.h"
#include "sdk/DeltaXPlugin.h"
#include "SmartDialog.h"
#include "GcodeHighlighter.h"
#include "ObjectInfoModel.h"
#include "ImageProcessing.h"
#include "GcodeScript.h"

// ========== DEFINES AND CONSTANTS ==========
#define DEFAULT_BAUDRATE 115200
#define DEFAULT_FPS			2
#define DEFAULT_INTERVAL	1000/DEFAULT_FPS

//#define JOY_STICK

// ========== CONDITIONAL INCLUDES ==========
#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        #include <QJoysticks.h>
    #endif
#endif

// ========== FORWARD DECLARATIONS ==========
class GcodeProgramManager;
class ObjectDetector;
class GcodeVariable;
class ROS;
class GcodeScript;
class SoftwareManager;

namespace Ui {
    class RobotWindow;
}

// ========== MAIN CLASS DEFINITION ==========
class RobotWindow : public QMainWindow
{
	Q_OBJECT

public:
    // ========== CONSTRUCTORS/DESTRUCTORS ==========
    explicit RobotWindow(QWidget *parent = 0, QString projectName = "project0");
    ~RobotWindow();

    // ========== INITIALIZATION METHODS ==========
    void setupUiBasic();           // Phase-0
    void createCoreManagers();     // Phase-1
    void initModules();            // Phase-2
    void wireUiEvents();           // Phase-3
    void loadSettings();

    void InitOtherThreadObjects();
	void InitEvents();
    void InitVariables();
    void InitSocketConnection();
    void InitObjectDetectingModule();
    void InitGcodeEditorModule();
    void InitGScriptHelp();
    void InitUIController();
    void InitCalibration();
    void LoadPlugin();
    void InitScriptThread();
    void AddScriptThread();
    void LoadScriptThread();
    void InitTrackingThread();
    void AddTrackingThread();
    void LoadTrackingThread();
    void InitDefaultValue();

    // ========== SETTINGS MANAGEMENT ==========
    void LoadSettings();
    void LoadGeneralSettings();
    void LoadJoggingSettings(QSettings* setting);
    void Load2DSettings(QSettings* setting);
    void Load3DSettings(QSettings* setting);
    void LoadExternalDeviceSettings();
    void LoadRobotSettings();
    void LoadTerminalSettings(QSettings* setting);
    void LoadGcodeEditorSettings(QSettings* setting);
    void LoadObjectDetectorSetting();
    void LoadDrawingSetting(QSettings* setting);
    void LoadPluginSetting(QSettings* setting);

    void SaveSettings(QSettings* setting);
    void SaveGeneralSettings(QSettings* setting);
    void SaveJoggingSettings(QSettings* setting);
    void Save2DSettings(QSettings* setting);
    void Save3DSettings(QSettings* setting);
    void SaveExternalDeviceSettings(QSettings* setting);
    void SaveTerminalSettings(QSettings* setting);
    void SaveGcodeEditorSettings(QSettings* setting);
    void SaveObjectDetectorSetting(QSettings* setting);
    void SaveDrawingSetting(QSettings* setting);
    void SavePluginSetting(QSettings* setting);

    // ========== UI MANAGEMENT ==========
    void SetID(QString id);
    void SetMainStackedWidgetAndPages(QStackedWidget* mainStack, QWidget* mainPage, QWidget* fullDisplayPage, QLayout* fullDisplayLayout);
    void SetSubStackedWidget(QStackedWidget* subStackedWidget);
    QWidget* GetWidget(QString name);
    QString GetRealNameWidget(QString name);
    QString GetRedefineNameWidget(QString name);
    QStringList GetShareDisplayWidgetNames();

    // ========== EVENT HANDLING ==========
    void DisablePositionUpdatingEvents();
    void EnablePositionUpdatingEvents();
    void closeEvent(QCloseEvent *event);

    // ========== PUBLIC MEMBER VARIABLES ==========
    SocketConnectionManager* ConnectionManager;
    DeviceManager* DeviceManagerInstance;
    QNetworkAccessManager HttpManager;
    QProcess* ExternalScriptProcess;
    
    QList<GcodeScript*> GcodeScripts;
    QTimer* UIEvent;
    int ChangedCounter = 0;
    bool IsGcodeEditorTextChanged = false;
    int baseFontSize;
    
    int RbID = 0;
    QVector<RobotPara> RobotParameters;
    QTimer* ShortcutKeyTimer;
    QTimer UpdateUITimer;
    bool isLoadingSettings = false;
    bool isCameraLoaded = false;  // Track camera state internally
    
    QString ProjectName = "project0";
    QString ProjectTitile = "Project 0";
    int DefaultBaudrate = DEFAULT_BAUDRATE;
    
    QStringList SentCommands;
    int SentCommandIndex = 0;
    
    ImageProcessing* ImageProcessingInstance;
    FilterWindow* ParameterPanel;
    QTimer* ConvenyorTimer;
    QWidget* ImageViewerWindow = NULL;
    Camera* CameraInstance;
    QThread* CameraThread;
    QTimer CameraTimer;
    
    TrackingManager* TrackingManagerInstance;
    DrawingExporter* DeltaDrawingExporter;
	ROS* DeltaXROS;
    
    QLabel* lbLoadingPopup;
    QMovie *mvLoadingPopup;
	QAction* SelectedAction = NULL;
    
	float UIScale = 1;
    SmartDialog* CloseDialog;
    QStackedWidget* MainWindowStackedWidget;
    QWidget* MainWindowPage;
    QWidget* FullDisplayPage;
    QLayout* FullDisplayLayout;
    QLabel* ImageLabel = NULL;
    QStackedWidget* SubWindowStackedWidget;
    QTime performanceTimer;
    
    QString copiedRobotPos[6];
    QMap<QString, QString> ParseNames;
    QStandardItemModel VarViewModel;
    ObjectInfoModel *ObjectModel;
    QTransform CalculatingTransform;
    QMatrix CalculatingTransform2;
    cv::Mat PointMatrix;
    QVector3D CalVector;
    
    Ui::RobotWindow *ui;

public slots:
    // ========== EXTERNAL CONTROL SLOTS ==========
    void ActivateButtonByName(const QString &buttonName);
    void ActiveWidgetByName(QString type, QString name, QString action);

    // ========== VIEW UPDATE SLOTS ==========
    void GetDeviceInfo(QString json);
    void GetDeviceResponse(QString id, QString response);
    void UpdateVarToView(QString fullKey, QVariant value);
    void UpdateObjectsToView();
    void Load3DComponents();

    // ========== ROBOT CONTROL SLOTS ==========
    void ConnectRobot();
    void ChangeSelectedRobot(int id);
    void ChangeRobotDOF(int id);
    void ChangeRobotModel(int id);
    void SetRobotState(bool isHold);
    void RequestPosition();
    void Home();
    void UpdatePositionControl(RobotPara robotPara);
    void ReceiveHomePosition(float x, float y, float z, float w, float u, float v);
	void UpdateVelocity();
	void UpdateAccel();
    void UpdateStartSpeed();
    void UpdateEndSpeed();
    void UpdateJerk();
	void AdjustGripperAngle(int angle);
	void Grip();
    void Jogging(QString direction, bool isMove);
    void MoveRobot(QString gcode);
    void MoveRobot(QString axis, float step);
    void MoveRobotFollowObject(float x, float y, float angle);
    void DoADemo();
    void UpdateRobotPositionToUI();

    // ========== END EFFECTOR SLOTS ==========
	void SetPump(bool value);
    void SetLaser(bool value);
    void SetOnOffOutput(bool result);
    void SetOutputX3(bool state);
    void SetValueOutput();
    void RequestValueInput();
    void GetInputX3();
    void GetValueInput(QString response);

    // ========== GCODE EDITOR SLOTS ==========
	void SaveProgram();
	void ExecuteProgram();
    void ClickExecuteButton(bool val);
    void ImportGcodeFilesFromComputer();
	void ExecuteSelectPrograms();
    void ExecuteCurrentLine(int, QString);
    void HighLineCurrentLine(int pos);
    void OnEditorTextChanged();
    void changeFontSize(int index);
    void RunSmartEditor();
    void StandardFormatEditor();
    void CleanTextFormatting();
    void OpenGcodeReference();
    void ExportBlocklyToGcode();
    void ExecuteRequestsFromExternal(QString request);
    void AddGcodeLine(QString gcode);
    void LoadGcodeFromFileToEditor(const QModelIndex &index);
    void LoadGcode(QString filePath);
    void SelectGcodeExplorer();
    void BackParentExplorer();
    void CreateNewGcodeFile();
    void SaveGcodeFile(QString fileName, QString content);
    void RefreshExplorer();
    void DeleteGcodeFile();
    void ChangeSelectedEditorThread(int id);

    // ========== VARIABLE MANAGEMENT SLOTS ==========
    void UpdateVariable(QString key, QVariant value);
    void UpdateVariables(QString cmd);
    void RespondVariableValue(QIODevice* s, QString name);
    void UpdateGcodeValueToDeviceUI(QString deviceName, QString gcode);

    // ========== CONVEYOR CONTROL SLOTS ==========
    void ChangeConveyorType(int index);
    void ChangeSelectedConveyor(int id);
    void ConnectConveyor();
    void SetConveyorMode(int mode);
    void SetConveyorMovingMode(int mode);
    void SetConveyorSpeed();
    void StopConveyor();
    void ForwardConveyor();
    void BackwardConveyor();
    void SetConveyorPosition();
    void SetConveyorAbsolutePosition();
    void TriggedCustomConveyor();
    void UpdatePointPositionOnConveyor(QLineEdit* x, QLineEdit* y, float angle, float distance);
    void UpdateCursorPosition(float x, float y);
    void ProcessShortcutKey();

    // ========== ENCODER CONTROL SLOTS ==========
    void ChangeEncoderType(int index);
    void ChangeConveyorLinkToEncoder(int);
    void ConnectEncoder();
    void ReadEncoder();
    void SetEncoderAutoRead();
    void ResetEncoderPosition();
    void SetEncoderVelocity();
    void CalculateEncoderVelocity(int id, float value);
    void ProcessProximitySensorValue(int value);
    void StartScheduledEncoder();

    // ========== SLIDER CONTROL SLOTS ==========
	void ConnectSliding();
	void GoHomeSliding();
	void DisableSliding();
	void SetSlidingSpeed();
	void SetSlidingPosition();

    // ========== EXTERNAL DEVICE SLOTS ==========
	void ConnectExternalMCU();
	void TransmitTextToExternalMCU();
    void DisplayTextFromExternalMCU(QString text);

    // ========== TERMINAL SLOTS ==========
    void TerminalTransmit();
    void RunExternalScript();
    void OpenExternalScriptFolder();
    void UpdateTermite(QString device, QString mess, int direction);
    void UpdateTermite(QString mess);

    // ========== OBJECT DETECTION SLOTS ==========
    void UpdateCameraConnectedState(bool isOpen);
    void StartContinuousCapture(bool isCheck);
    void ChangeOutputDisplay(QString outputName);
    void LoadWebcam();
    void LoadImages();
    void StopCapture();
    void OpenColorFilterWindow();
    void SelectObjectDetectingAlgorithm(int algorithm);
    void ConfigChessboard();
    void GetCalibPointsFromImage(QPointF p1, QPointF p2);
    void UpdateRealPositionOfCalibPoints();
    void GetObjectSizeFromImage(QRectF rect);
    void GetMappingPointFromImage(QPointF point);
    void GetNewImageSize();
    void UnselectToolButtons();
    void EditImage(bool isWarp, bool isCropTool);
    void SendImageToExternalScript(cv::Mat input);
    void AddDisplayObjectFromExternalScript(QString msg);

    // ========== TRACKING SLOTS ==========
    void ChangeSelectedTracking(int id);
    void ChangeSelectedTrackingEncoder(int id);
    void SaveTrackingManager();

    // ========== POINT TOOL SLOTS ==========
    void CalculateMappingMatrixTool();
    void CalculatePointMatrixTool();
    void CalculateTestPoint();
    void CalculateVector();
    void UpdateTestPoint(QVector3D testPoint);
    void MoveTestTrackingPoint();

    // ========== DISPLAY SLOTS ==========
    void OpenLoadingPopup();
    void CloseLoadingPopup();
    void MaximizeTab(int index);
    void OpenCameraWindow();
    void SelectImageProviderOption(int option);

    // ========== TIMER SLOTS ==========
    void ProcessUIEvent();

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
    // ========== JOYSTICK SLOTS ==========
    void ProcessJoystickButton(const QJoystickButtonEvent& event);
    void ProcessJoystickAxis(const QJoystickAxisEvent& event);
    void ProcessJoystickPOV(const QJoystickPOVEvent& event);
    #endif
#endif

signals:
    // ========== DEVICE SIGNALS ==========
    void ChangeDeviceState(QString deviceName, bool isOpen, QString address);
    void Send(int device, QString msg);
    void ScanAndConnectRobot();
    void DisconnectRobot();

    // ========== OBJECT DETECTION SIGNALS ==========
    void GotObjects(QVector<Object> objects);
    void GotResizePara(cv::Size size);
    void GotResizeImage(cv::Mat mat);
    void GotChessboardSize(cv::Size size);
    void GotCalibPoints(QPolygonF poly);
    void GotMappingMatrix(QMatrix matrix);
    void GotOjectFilterInfo(Object obj);
    void RequestClearObjects();
    void RequestDeleteObject(int index);
    void RequestFindChessboard();

protected:
    // ========== PROTECTED METHODS ==========
    void paintEvent(QPaintEvent *event) override;

private:
    // ========== PERFORMANCE & TESTING ==========
    void CheckSettingsSpeed();
    void SaveDetectingUI();
	void interpolateCircle();
	void makeEffectExample();

    // ========== GCODE EDITOR PRIVATE METHODS ==========
	QString boldKey(QString key, QString htmlText);
	QString boldPlusKey(QString key, QString plus, QString htmlText);
	QString italyKey(QString key, QString htmlText);
	QString replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText);

    // ========== DIALOG & UI PRIVATE METHODS ==========
    bool openConnectionDialog(QSerialPort* comPort, QTcpSocket* socket,QPushButton* connectButton, QLabel* comNameInfo = NULL);

    // ========== UTILITY PRIVATE METHODS ==========
    void sendGcode(QString prefix, QString para1, QString para2);
    QObject* getObjectByName(QObject* parent, QString name);
    void initInputValueLabels();
    void plugValue(QLineEdit* le, float value);
    bool isItemExit(QListWidget* lw, QString item);
    int getIDfromName(QString fullName);
    QString checkAndCreateDir(const QString& path);
    bool saveImageWithUniqueName(const cv::Mat& image, const QString& dirPath);
    void loadImages(const QString& dirPath, QListWidget* lwImageList);
    void onImageItemClicked(QListWidgetItem* item);
    void pastePointValues(QLineEdit* leX, QLineEdit* leY, QLineEdit* leZ);
    void pastePointValues(QLineEdit* lePoint);
    void runPythonFile(QString filePath);

    // ========== PLUGIN PRIVATE METHODS ==========
    QStringList getPlugins(QString path);
    void initPlugins(QStringList plugins);
    QList<DeltaXPlugin*>* getPluginList();

    // ========== PRIVATE MEMBER VARIABLES ==========
    
    // Controller
#ifdef Q_OS_WIN
    #ifdef JOY_STICK
    QJoysticks *joystick;
    #endif
#endif

    // Process
    QProcess *process = nullptr;

    // Plugin Management
    QList<DeltaXPlugin*>* pluginList;
    DeltaXPlugin* industrialCameraPlugin;

    // Widget Pointers
    QList<QLabel*>* lbInputValues;
    QLineEdit* leChessPoints[4][2];

    // Event Management
    QString positionEmitter = "";

    // Gcode Editor
    QFileSystemModel explorerModel;
    GCodeHighlighter *highlighter;

    // Buffer Values
    float encoderLastValue = 0;
    float scheduledStartEncoderValue = 0;
    bool isScheduledEncoder = false;
    QElapsedTimer encoderUpdateTimer;

    // Optimized Variable Management
    VariableManager* m_variableManager;
    mutable QHash<QString, QString> m_prefixCache;
    mutable QHash<QString, QVariant> m_pendingUpdates;
    mutable QTimer* m_batchUpdateTimer;
    
    // Prefix generation helpers
    QString getDevicePrefix(const QString& deviceType, int id = -1) const;
    QString getSelectedDevicePrefix(const QString& deviceType) const;
    QString getCachedPrefix(const QString& key) const;
    
    // Optimized variable operations
    void updateVariableOptimized(const QString& key, const QVariant& value);
    void updateVariablesOptimized(const QHash<QString, QVariant>& variables);
    void batchUpdateVariables(const QString& prefix, const QHash<QString, QVariant>& variables);
    QVariant getVariableOptimized(const QString& key, const QVariant& defaultValue = QVariant()) const;
    
    // Batch processing
    void flushPendingUpdates();
    void scheduleBatchUpdate();

private slots:
    void processBatchUpdates();
};

#endif // ROBOTWINDOW_H
