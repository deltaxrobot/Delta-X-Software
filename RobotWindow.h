#ifndef ROBOTWINDOW_H
#define ROBOTWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>
#include "ConnectionManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <stdio.h>
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
#include <ObjectVariableTable.h>
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
#include "Encoder.h"
#include "FilterWindow.h"
#include "GcodeHighlighter.h"
#include <QList>

#define JOY_STICK

#ifdef Q_OS_WIN
    #ifdef JOY_STICK
        #include <QJoysticks.h>
    #endif
#endif

#include <QMap>
#include <QLayout>
#include <QStackedWidget>

#include "SoftwareManager.h"

#include "ComDevice.h"
#include "ImageProcessing.h"

#include <QSettings>
#include "GcodeScript.h"


#include <QDialogButtonBox>
#include <device/DeviceManager.h>
#include "VarManager.h"

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
    explicit RobotWindow(QWidget *parent = 0);
    ~RobotWindow();

    //----- Init ----
    void InitOtherThreadObjects();
	void InitEvents();
    void InitVariables();
    void InitConnectionModule();
    void InitObjectDetectingModule();
    void InitGcodeEditorModule();
    void InitUIController();
    void InitCalibration();
    void LoadPlugin();
    void InitParseNames();
    void InitScriptThread();
    void AddScriptThread();
    void LoadScriptThread();

    void LoadSettings();
    void LoadSettings(QSettings* setting);
    void LoadGeneralSettings(QSettings* setting);
    void LoadJoggingSettings(QSettings* setting);
    void Load2DSettings(QSettings* setting);
    void Load3DSettings(QSettings* setting);
    void LoadExternalDeviceSettings(QSettings* setting);
    void LoadTerminalSettings(QSettings* setting);
    void LoadGcodeEditorSettings(QSettings* setting);
    void LoadObjectDetectorSetting(QSettings* setting);
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

    void InitTabs();
    void SetID(QString id);

    // ----- Event ----
    void DisablePositionUpdatingEvents();
    void EnablePositionUpdatingEvents();
    void closeEvent(QCloseEvent *event);

    bool Run();
    bool Stop();

    // ---- UI pointer -----
    void SetMainStackedWidgetAndPages(QStackedWidget* mainStack, QWidget* mainPage, QWidget* fullDisplayPage, QLayout* fullDisplayLayout);
    void SetSubStackedWidget(QStackedWidget* subStackedWidget);

    QWidget* GetWidget(QString name);
    QString GetRealNameWidget(QString name);
    QString GetRedefineNameWidget(QString name);
    QStringList GetShareDisplayWidgetNames();

    //---- Object in other threads ----
    DeviceManager* DeviceManagerInstance;

    //---- Connection ----
    ConnectionManager* DeltaConnectionManager;
    QNetworkAccessManager HttpManager;

    //---- Process -----

    QProcess* ExternalScriptProcess;

    // ---- Gcode ----
    QList<GcodeScript*> GcodeScripts;
    QTimer* VirtualEncoderTimer;
    QTimer* UIEvent;

    // ---- Robot ----
    RobotPara RobotParameter;
    DeltaVisualizer *Delta2DVisualizer;
    QTimer* ShortcutKeyTimer;

    QTimer UpdateUITimer;

    int ID = 0;
    QString Name = "robot 1";
    QString ProjectName = "project 0";
    QString SoftwareVersion = "0.9.5";

    int DefaultBaudrate = DEFAULT_BAUDRATE;

    //----- Termite ------
    QStringList SentCommands;
    int SentCommandIndex = 0;

    // ---- Vision ----
    ImageProcessing* ImageProcessingThread;
    FilterWindow* ParameterPanel;

    ObjectVariableTable* TrackingObjectTable;
    QTimer* ConvenyorTimer;

    Encoder* Encoder1;
    Encoder* Encoder2;

    float ConveyorDistanceToMove = 0;
    float ConveyorPositionBeforeMove = 0;

    QWidget* ImageViewerWindow = NULL;

    int RunningCamera = -1;
    bool IsCameraPause = false;
    cv::VideoCapture* Camera;
    cv::Mat CaptureImage;
    float CameraFPS = DEFAULT_FPS;
    float CameraTimerInterval = DEFAULT_INTERVAL;
    QTimer CameraTimer;

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
//    QMap<QString, QString>* GcodeVariables;

public slots:
    // ---- View update ----
    void GetDeviceInfo(QString json);

    // ---- Robot ----
    void ConnectDeltaRobot();
    void NoticeConnected();

    void ConfigConnection();
    void ChangeSelectedRobot(int id);
    void ChangeRobotDOF(int id);

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
    void UpdatePositionToLabel();
    void UpdatePositionControl(RobotPara robotPara);
    void ReceiveHomePosition(float x, float y, float z, float w, float u, float v);
	void UpdateVelocity();
	void UpdateAccel();
    void UpdateStartSpeed();
    void UpdateEndSpeed();
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
    void UpdateVariable(QString key, QString value);
    void UpdateVariables(QString cmd);
    void RespondVariableValue(QIODevice* s, QString name);

    //----- Device ----
    void UpdateGcodeValueToDeviceUI(QString deviceName, QString gcode);

    // ---- Conveyor ----
    void ChangeConveyorType(int index);

    void ConnectConveyor();
    void SetConveyorMode(int mode);
    void SetConveyorMovingMode(int mode);
    void SetSpeedOfPositionMode();
    void MoveConveyor();

    void SetConvenyorSpeed();
    void ConnectEncoder();
    void ResetEncoderPosition();
    void UpdatePointPositionOnConveyor(QLineEdit* x, QLineEdit* y, float angle, float distance);

    void CalculateConveyorDeviationAngle();

    void UpdateCursorPosition(float x, float y);

    void ProcessShortcutKey();



    void MoveExternalConveyor();
    void CheckForTurnOffExternalConveyor();
    void ForwardExternalConveyor();
    void BackwardExternalConveyor();
    void TurnOffExternalConveyor();

    void VirtualEncoder();
    void ProcessEncoderValue(float value);
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
    void Log(QString msg);

    // ---- Connection ----
	void FinishedRequest(QNetworkReply *reply);

    // ---- ROS ----
	void OpenROS();
	void ChangeROSCameraView(int index);
	void ChangeEndEffector(int index);
	void ChangeRobotVersion(int index);
	void AddObjectsToROS(std::vector<cv::RotatedRect> ObjectContainer);
	void DeleteAllObjectsInROS();

    // ----- Object Detecting ----
    void GeneralCapture();
    void StartContinuousCapture();
    void GetImageFromExternal(cv::Mat mat);
    void GetCapturedSignal();
    void ChangeOutputDisplay(QString outputName);
    void LoadWebcam();
    void LoadImages();
    void StopCapture();
    void CaptureWebcam();
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
    void UpdateObjectsToImageViewer(QList<Object*>* objects);
    void UpdateObjectsToVariableTable(QList<Object*>* objects);
    void ClearObjectsToVariableTable();
    void DeleteFirstVariable();
    void EditImage(bool isWarp, bool isCropTool);

    void SendImageToExternalScript(cv::Mat input);
    void AddDisplayObjectFromExternalScript(QString msg);
    // ----- Display ----

    void ScaleUI();

    void OpenLoadingPopup();
    void CloseLoadingPopup();

    void MaximizeTab(int index);

    void OpenCameraWindow();

    void SelectImageProviderOption(int option);

    // ------ Timer -----
    void ProcessUIEvent();

    // -------- Object Detecting --------
    void UseCameraFromPlugin(bool checked);
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
    void ChangeDeviceState(int deviceType, bool isOpen);
    // ----
    void RequestCapture();
    void GotImage(cv::Mat mat);
    void GotObjects(QList<Object*>* objects);
    void GotResizePara(cv::Size size);
    void GotResizeImage(cv::Mat mat);
    void GotChessboardSize(cv::Size size);
    void GotCalibPoints(QPolygonF poly);
    void GotMappingMatrix(QMatrix matrix);
    void GotOjectFilterInfo(Object obj);
    void RequestClearObjects();
    void RequestDeleteObject(int index);
    void RequestFindChessboard();
    void StopGcodeProgram();
    void RunGcodeProgram(QString gcodes, int pos, bool isEditor);
    void Send(int device, QString msg);
    void ScanAndConnectRobot();
    void DisconnectRobot();

private:

    // ---- Gcode Editor -----
	QString boldKey(QString key, QString htmlText);
	QString boldPlusKey(QString key, QString plus, QString htmlText);
	QString italyKey(QString key, QString htmlText);
	QString replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText);

    // ---- Display ----
    bool openConnectionDialog(QSerialPort* comPort, QTcpSocket* socket,QPushButton* connectButton, QLabel* comNameInfo = NULL);

	void hideExampleWidgets();

    // ---- Encoder/Conveyor ----
    void updateEncoderUI();

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

public:
    Ui::RobotWindow *ui;
};


#endif // ROBOTWINDOW_H
