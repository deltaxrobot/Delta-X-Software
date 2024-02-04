#ifndef ROBOTWINDOW_H
#define ROBOTWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <stdio.h>

#include <SocketConnectionManager.h>

#include <UnityTool.h>
#include <DeltaVisualizer.h>
#include <qmath.h>
#include <FilterWindow.h>
#include <qfiledialog.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>
//#include "ObjectDetector.h"
#include <GcodeReference.h>
#include <DrawingExporter.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QVersionNumber>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QInputDialog>
#include <QUrl>
#include <TCPConnectionManager.h>
//#include <ROS.h>
#include <QCloseEvent>
//#include <ObjectVariableTable.h>
#include <QProcess>
#include <QSettings>
#include <QtMultimedia/QCameraInfo>
#include <QMovie>
#include "sdk/DeltaXPlugin.h"
#include <QPluginLoader>
#include "SmartDialog.h"
#include <QElapsedTimer>
#include <QProcess>
#include <QComboBox>
#include "GcodeHighlighter.h"
#include <QList>
#include <random>
#include <ObjectInfoModel.h>
#include <QRandomGenerator>

//#define JOY_STICK

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        #include <QJoysticks.h>
    #endif
#endif

#include <QMap>
#include <QLayout>
#include <QStackedWidget>

//#include "SoftwareManager.h"

#include "ImageProcessing.h"

#include "GcodeScript.h"

#include <QDialogButtonBox>
#include <device/DeviceManager.h>
#include "device/camera.h"
#include "TrackingManager.h"
#include"ObjectInfo.h"

#include "PointTool.h"

#define DEFAULT_BAUDRATE 115200

#define DEFAULT_FPS			2
#define DEFAULT_INTERVAL	1000/DEFAULT_FPS

class GcodeProgramManager;
class ObjectDetector;

class GcodeVariable;
class ROS;
class GcodeScript;
class SoftwareManager;

namespace Ui {
    class RobotWindow;
}

class RobotWindow : public QMainWindow
{
	Q_OBJECT

public:
    explicit RobotWindow(QWidget *parent = 0, QString projectName = "project0");
    ~RobotWindow();

    //----- Init ----
    void InitOtherThreadObjects();
	void InitEvents();
    void InitVariables();
    void InitSocketConnection();
    void InitObjectDetectingModule();
    void InitGcodeEditorModule();
    void InitUIController();
    void InitCalibration();
    void LoadPlugin();
    void InitScriptThread();
    void AddScriptThread();
    void LoadScriptThread();
    void InitTrackingThread();
    void AddTrackingThread();
    void LoadTrackingThread();

    void LoadSettings();
    void LoadGeneralSettings(QSettings* setting);
    void LoadJoggingSettings(QSettings* setting);
    void Load2DSettings(QSettings* setting);
    void Load3DSettings(QSettings* setting);
    void LoadExternalDeviceSettings(QSettings* setting);
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

    void SetID(QString id);

    void InitDefaultValue();

    // ----- Event ----
    void DisablePositionUpdatingEvents();
    void EnablePositionUpdatingEvents();
    void closeEvent(QCloseEvent *event);

    // ---- UI pointer -----
    void SetMainStackedWidgetAndPages(QStackedWidget* mainStack, QWidget* mainPage, QWidget* fullDisplayPage, QLayout* fullDisplayLayout);
    void SetSubStackedWidget(QStackedWidget* subStackedWidget);

    QWidget* GetWidget(QString name);
    QString GetRealNameWidget(QString name);
    QString GetRedefineNameWidget(QString name);
    QStringList GetShareDisplayWidgetNames();

    // ---- Server ----
    SocketConnectionManager* ConnectionManager;

    //---- Object in other threads ----
    DeviceManager* DeviceManagerInstance;

    //---- Connection ----
    QNetworkAccessManager HttpManager;

    //---- Process -----

    QProcess* ExternalScriptProcess;

    // ---- Gcode ----
    QList<GcodeScript*> GcodeScripts;
    QTimer* UIEvent;

    // ---- Robot ----
    int RbID = 0;
    QVector<RobotPara> RobotParameters;
    QTimer* ShortcutKeyTimer;

    QTimer UpdateUITimer;

    QString ProjectName = "project0";

    int DefaultBaudrate = DEFAULT_BAUDRATE;

    //----- Termite ------
    QStringList SentCommands;
    int SentCommandIndex = 0;

    // ---- Vision ----
    ImageProcessing* ImageProcessingThread;
    FilterWindow* ParameterPanel;

//    ObjectVariableTable* TrackingObjectTable;
    QTimer* ConvenyorTimer;

    Encoder* Encoder1;
    Encoder* Encoder2;

    QWidget* ImageViewerWindow = NULL;

    Camera* CameraInstance;

    QTimer CameraTimer;

    // ----- Tracking -----
    TrackingManager* TrackingManagerInstance;

    // ---- Drawing ----
    DrawingExporter* DeltaDrawingExporter;

    // ---- ROS ----
	ROS* DeltaXROS;

    // ---- Loading ----
    QLabel* lbLoadingPopup;
    QMovie *mvLoadingPopup;

    // ---- Menu ----
	QAction* SelectedAction = NULL;

    // ---- Display -----
	float UIScale = 1;
    SmartDialog* CloseDialog;

    QStackedWidget* MainWindowStackedWidget;
    QWidget* MainWindowPage;
    QWidget* FullDisplayPage;
    QLayout* FullDisplayLayout;

    QStackedWidget* SubWindowStackedWidget;

    // ----- Data ----
    QMap<QString, QString> ParseNames;

    QStandardItemModel VarViewModel;
    ObjectInfoModel *ObjectModel;
    QTransform CalculatingTransform;
    QMatrix CalculatingTransform2;
    QMatrix PointMatrix;
    QVector3D CalVector;

public slots:
    // ---- View update ----
    void GetDeviceInfo(QString json);
    void GetDeviceResponse(QString id, QString response);
    void UpdateVarToView(QString fullKey, QVariant value);
    void UpdateObjectsToView();

    //----- 3D -----
    void Load3DComponents();

    // ---- Robot ----
    void ConnectRobot();

    void ChangeSelectedRobot(int id);
    void ChangeRobotDOF(int id);
    void ChangeRobotModel(int id);

    // ---- Gcode Editor ----
	void SaveProgram();
	void ExecuteProgram();
    void ClickExecuteButton(bool val);
    void ImportGcodeFilesFromComputer();

	void ExecuteSelectPrograms();
    void ExecuteCurrentLine();
    void HighLineCurrentLine(int pos);

    void RunSmartEditor();
    void StandardFormatEditor();

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

    // ---- Robot Controller ----
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

    void MoveRobot(QString gcode);
    void MoveRobot(QString axis, float step);

    void MoveRobotFollowObject(float x, float y, float angle);
    void DoADemo();
    // ------ Robot Position -----

    void UpdateRobotPositionToUI();

    //------ End Effector Robot -------
	void SetPump(bool value);
    void SetLaser(bool value);
    void SetOnOffOutput(bool result);
    void SetValueOutput();
    void RequestValueInput();
    void GetValueInput(QString response);

    //----- Variable -----
    void UpdateVariable(QString key, QVariant value);
    void UpdateVariables(QString cmd);
    void RespondVariableValue(QIODevice* s, QString name);

    //----- Device ----
    void UpdateGcodeValueToDeviceUI(QString deviceName, QString gcode);

    // ---- Conveyor ----
    void ChangeConveyorType(int index);
    void ChangeSelectedConveyor(int id);

    void ConnectConveyor();
    void SetConveyorMode(int mode);
    void SetConveyorMovingMode(int mode);
    void SetConveyorSpeed();
    void SetConveyorPosition();

    void UpdatePointPositionOnConveyor(QLineEdit* x, QLineEdit* y, float angle, float distance);


    void UpdateCursorPosition(float x, float y);

    void ProcessShortcutKey();

    //----- Encoder -----
    void ChangeEncoderType(int index);

    void ConnectEncoder();
    void ReadEncoder();
    void SetEncoderAutoRead();
    void ResetEncoderPosition();
    void SetEncoderVelocity();
    void CalculateEncoderVelocity(int id, float value);
    void ProcessProximitySensorValue(int value);
	
    // ---- Slider ----
	void ConnectSliding();
	void GoHomeSliding();
	void DisableSliding();
	void SetSlidingSpeed();
	void SetSlidingPosition();

    // ---- External Device ----
	void ConnectExternalMCU();
	void TransmitTextToExternalMCU();
    void DisplayTextFromExternalMCU(QString text);

    // ---- Termite ----
    void TerminalTransmit();
    void RunExternalScript();
    void OpenExternalScriptFolder();
    void UpdateTermite(QString device, QString mess, int direction);
    void UpdateTermite(QString mess);

    // ---- Connection ----

    // ---- ROS ----

    // ----- Object Detecting ----
    void UpdateCameraConnectedState(bool isOpen);

    void StartContinuousCapture(bool isCheck);
    void ChangeOutputDisplay(QString outputName);
    void LoadWebcam();
    void LoadImages();
    void StopCapture();
    void RearrangeTaskFlow();
    void OpenColorFilterWindow();
    void SelectObjectDetectingAlgorithm(int algorithm);
    void ConfigChessboard();
    void GetCalibPointsFromImage(QPointF p1, QPointF p2);
    void UpdateRealPositionOfCalibPoints();
    void GetObjectSizeFromImage(QRectF rect);
    void GetMappingPointFromImage(QPointF point);
    void GetNewImageSize();

    void UnselectToolButtons();
    void UpdateObjectsToImageViewer(QList<Object> objects);
//    void UpdateObjectsToVariableTable(QList<Object*>* objects);
    void EditImage(bool isWarp, bool isCropTool);

    void SendImageToExternalScript(cv::Mat input);
    void AddDisplayObjectFromExternalScript(QString msg);

    //------ Tracking --------
    void ChangeSelectedTracking(int id);
    void ChangeSelectedTrackingEncoder(int id);

    //------ Point Tool -----
    void CalculateMappingMatrixTool();
    void CalculatePointMatrixTool();
    void CalculateTestPoint();
    void CalculateVector();

    // ----- Display ----

    void OpenLoadingPopup();
    void CloseLoadingPopup();

    void MaximizeTab(int index);

    void OpenCameraWindow();

    void SelectImageProviderOption(int option);

    // ------ Timer -----
    void ProcessUIEvent();

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        //--------Joystick-----------
        void ProcessJoystickButton(const QJoystickButtonEvent& event);
        void ProcessJoystickAxis(const QJoystickAxisEvent& event);
        void ProcessJoystickPOV(const QJoystickPOVEvent& event);
    #endif
#endif

signals:
    // ---- Device ----
    void ChangeDeviceState(int deviceType, bool isOpen, QString address);
    // ----
    void GotObjects(QList<Object> objects);
    void GotResizePara(cv::Size size);
    void GotResizeImage(cv::Mat mat);
    void GotChessboardSize(cv::Size size);
    void GotCalibPoints(QPolygonF poly);
    void GotMappingMatrix(QMatrix matrix);
    void GotOjectFilterInfo(Object obj);
    void RequestClearObjects();
    void RequestDeleteObject(int index);
    void RequestFindChessboard();
    void Send(int device, QString msg);
    void ScanAndConnectRobot();
    void DisconnectRobot();

private:
    // ----- Check Performence ----
    void CheckSettingsSpeed();

    // ---- Gcode Editor -----
	QString boldKey(QString key, QString htmlText);
	QString boldPlusKey(QString key, QString plus, QString htmlText);
	QString italyKey(QString key, QString htmlText);
	QString replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText);

    // ---- Display ----
    bool openConnectionDialog(QSerialPort* comPort, QTcpSocket* socket,QPushButton* connectButton, QLabel* comNameInfo = NULL);

    // ---- Encoder/Conveyor ----

    // ---- Test ----
	void interpolateCircle();
	void makeEffectExample();

    // ---- Tool ----

    //--------- Controller -------
#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        QJoysticks *joystick;
    #endif
#endif
    //--------- Utils ----------
    void sendGcode(QString prefix, QString para1, QString para2);
    QObject* getObjectByName(QObject* parent, QString name);
    void initInputValueLabels();
    void plugValue(QLineEdit* le, float value);
    bool isItemExit(QListWidget* lw, QString item);

    //--------- Tool -------

    void runPythonFile(QString filePath);
    QProcess *process = nullptr;

    //--------- Plugin -----------
    QStringList getPlugins(QString path);
    void initPlugins(QStringList plugins);
    QList<DeltaXPlugin*>* getPluginList();

    QList<DeltaXPlugin*>* pluginList;

    //---- Widget Pointer ----

    QList<QLabel*>* lbInputValues;
    QLineEdit* leChessPoints[4][2];

    //----- Event Robot Controller ----
    QString positionEmitter = "";

    // ---- Gcode Editor ----
    QFileSystemModel explorerModel;
    GCodeHighlighter *highlighter;

    // ---- Last Values ----
    float encoderLastValue = 0;

public:
    Ui::RobotWindow *ui;
};


#endif // ROBOTWINDOW_H
