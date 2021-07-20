#ifndef ROBOTWINDOW_H
#define ROBOTWINDOW_H

#include <QMainWindow>
#include "ConnectionManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <stdio.h>
#include <UnityTool.h>
#include <GcodeProgramManager.h>
#include <DeltaVisualizer.h>
#include <qmath.h>
#include <hsvwindow.h>
#include <qfiledialog.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>
#include "ImageProcesser.h"
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

#ifdef Q_OS_WIN
    #include <QJoysticks.h>
#endif

#include <QMap>
#include <QLayout>
#include <QStackedWidget>

#include "Robot.h"
#include "robotmanager.h"
#include "SoftwareManager.h"

#include "ComDevice.h"

class RobotWindow;
class ImageProcesser;
class GcodeProgramManager;
class GcodeVariable;
class ROS;
class RobotManager;

namespace Ui {
    class RobotWindow;
}

class RobotWindow : public QMainWindow
{
	Q_OBJECT

public:
    explicit RobotWindow(QWidget *parent = 0);
    ~RobotWindow();

	void InitEvents();
    void DisablePositionUpdatingEvents();
    void EnablePositionUpdatingEvents();
    void InitVariables();
	void closeEvent(QCloseEvent *event);
    void LoadPlugin();
    void SetMainStackedWidgetAndPages(QStackedWidget* mainStack, QWidget* mainPage, QWidget* fullDisplayPage, QLayout* fullDisplayLayout);
    void SetSubStackedWidget(QStackedWidget* subStackedWidget);

    void SetID(int id);
    void SetName(QString name);
    void InitTabs();

    //--------- Single ton ---------

    //------------------------------

	ConnectionManager* DeltaConnectionManager;
	GcodeProgramManager* DeltaGcodeManager;
	DeltaVisualizer *Delta2DVisualizer;
	ImageProcesser* DeltaImageProcesser;
	DrawingExporter* DeltaDrawingExporter;
	ObjectVariableTable* TrackingObjectTable;

    Robot RobotParamter;
    RobotManager* RobotObjectManager;

	ConnectionManager* CurrentDeltaPort;
    COMDevice* COMEncoder;
    QElapsedTimer ElapsedTimeEncoder;

	ROS* DeltaXROS;

	QTimer* EditorTimer;
	QTimer* ConvenyorTimer;
	QTimer* ShortcutKeyTimer;

    QLabel* lbLoadingPopup;
    QMovie *mvLoadingPopup;

    RobotManager* RobotManagerPointer = NULL;
	QAction* SelectedAction = NULL;
	int ID = 0;
    QString Name = "robot 1";

	QNetworkAccessManager *HttpManager;
	QString SoftwareVersion = "0.9.5";

	float UIScale = 1;

    SmartDialog* CloseDialog;

    QStackedWidget* MainWindowStackedWidget;
    QWidget* MainWindowPage;
    QWidget* FullDisplayPage;
    QLayout* FullDisplayLayout;

    QStackedWidget* SubWindowStackedWidget;

private slots:
    // ---- Setting ----
    void SaveSetting();
    void LoadSetting();

    // ---- Robot ----
    void ConnectDeltaRobot();

    // ---- Gcode Editor ----
	void AddNewProgram();
	void SaveProgram();
	void ExecuteProgram();
	void ImportGcodeFilesFromComputer();
	void UploadGcodeFileToServer();
	void SearchGcodeFile();

	void ExecuteSelectPrograms();
	void ExecuteCurrentLine();
	void UpdateZLineEditValue(int z);
	void UpdateWLineEditValue(int w);
	void UpdateDeltaPositionFromLineEditValue();
    void UpdatePositionToLabel();
    void UpdateTextboxFrom2DControl(float x, float y, float z, float w, float u, float v);
    void UpdateTextboxFrom3DControl(float x, float y, float z, float w, float u, float v);
    void UpdatePositionControl(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e);
    void UpdateGlobalHomePositionValueAndControlValue(float x, float y, float z, float w, float u, float v);
	void UpdateVelocity();
	void UpdateAccel();
    void UpdateStartSpeed();
    void UpdateEndSpeed();
	void AdjustGripperAngle(int angle);
	void Grip();

    //------ Gcode button -------
	void SetPump(bool value);
	void SetLaser(bool value);
	void Home();
    void SetOnOffOutput(bool result);
    void SetValueOutput();
    void RequestValueInput();
    void GetValueInput(QString response);
    //-------------------------

	void DisplayGcodeVariable(QList<GcodeVariable> gcodeVariables);
    void SetConvenyorSpeed();
    void ConnectEncoder();
    void ResetEncoderPosition();
	void AddGcodeLine();
	void ChangeGcodeParameter();

    void ReceiveConveyorResponse(QString response);

    void UpdateDetectObjectSize();

    void UpdateCursorPosition(float x, float y);

	void ConnectConveyor();
	void SetConveyorMode(int mode);
	void SetConveyorMovingMode(int mode);
	void SetSpeedOfPositionMode();
	void MoveConveyor();

	void ProcessShortcutKey();	
	

	void ConnectSliding();
	void GoHomeSliding();
	void DisableSliding();
	void SetSlidingSpeed();
	void SetSlidingPosition();

	void ConnectExternalMCU();
	void TransmitTextToExternalMCU();
	void DisplayTextFromExternalMCU(QString text);

	void TerminalTransmit();
	void PrintReceiveData(QString msg);

	void NoticeConnected();

	void RunSmartEditor();
	void StandardFormatEditor();

	void OpenGcodeReference();
	void ConfigConnection();

	void ChangeDeltaDashboard(int index);
	void SelectTrueTabName(int index);

	void FinishedRequest(QNetworkReply *reply);

	void ExportBlocklyToGcode();

	void OpenROS();
	void ChangeROSCameraView(int index);
	void ChangeEndEffector(int index);
	void ChangeRobotVersion(int index);
	void AddObjectsToROS(std::vector<cv::RotatedRect> ObjectContainer);
	void DeleteAllObjectsInROS();

	void ScaleUI();

	void ExecuteRequestsFromExternal(QString request);

	void ChangeParentForWidget(bool state);

    void OpenLoadingPopup();
    void CloseLoadingPopup();

#ifdef Q_OS_WIN
    //--------Joystick-----------
    void ProcessJoystickButton(const QJoystickButtonEvent& event);
    void ProcessJoystickAxis(const QJoystickAxisEvent& event);
    void ProcessJoystickPOV(const QJoystickPOVEvent& event);
#endif
    //-------- Tab UX ---------
    void MaximizeTab(int index);

private:

	QString boldKey(QString key, QString htmlText);
	QString boldPlusKey(QString key, QString plus, QString htmlText);
	QString italyKey(QString key, QString htmlText);
	QString replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText);

    bool OpenConnectionDialog(QSerialPort* comPort, QTcpSocket* socket,QPushButton* connectButton, QLabel* comNameInfo = NULL);


	void hideExampleWidgets();
	void interpolateCircle();
	void makeEffectExample();

    //--------- Controller -------
#ifdef Q_OS_WIN
    QJoysticks *joystick;
#endif
    //--------- IO ----------
    void sendGcode(QString prefix, QString para1, QString para2);
    QObject* getObjectByName(QObject* parent, QString name);
    void initInputValueLabels();

    //--------- Plugin -----------
    QStringList getPlugins(QString path);
    void initPlugins(QStringList plugins);
    QList<DeltaXPlugin*>* getPluginList();

    QList<DeltaXPlugin*>* pluginList;
    //------------------

    QList<QLabel*>* lbInputValues;

    //----- Event Variables ----
    QString positionEmitter = "";

public:
    Ui::RobotWindow *ui;
};


#endif // ROBOTWINDOW_H
