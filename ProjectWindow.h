 #ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

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
#include <QJoysticks.h>
#include <QMap>
#include <QLayout>
#include <QStackedWidget>

class ProjectWindow;
class ImageProcesser;
class GcodeProgramManager;
class GcodeVariable;
class ROS;

namespace Ui {
    class ProjectWindow;
}

class ProjectWindow : public QMainWindow
{
	Q_OBJECT

public:
    explicit ProjectWindow(QWidget *parent = 0);
    ~ProjectWindow();

	void InitEvents();
	void InitVariables();
    void AddInstance(QList<ProjectWindow*>* deltaXMainWindows = NULL);
	void closeEvent(QCloseEvent *event);
    void LoadPlugin();
    void SetMainStackedWidgetAndPages(QStackedWidget* mainStack, QWidget* mainPage, QWidget* fullDisplayPage, QLayout* fullDisplayLayout);
    void SetSubStackedWidget(QStackedWidget* subStackedWidget);

	ConnectionManager* DeltaConnectionManager;
	GcodeProgramManager* DeltaGcodeManager;
	DeltaVisualizer *Delta2DVisualizer;
	ImageProcesser* DeltaImageProcesser;
	DrawingExporter* DeltaDrawingExporter;
	ObjectVariableTable* TrackingObjectTable;

	ConnectionManager* CurrentDeltaPort;

	ROS* DeltaXROS;

	QTimer* EditorTimer;
	QTimer* ConvenyorTimer;
	QTimer* ShortcutKeyTimer;

    QLabel* lbLoadingPopup;
    QMovie *mvLoadingPopup;

	//QList<DeltaXDashboard*> DeltaXDashboards;
    QList<ProjectWindow*>* DeltaXMainWindows = NULL;
	QAction* SelectedAction = NULL;
	int ID = 0;
	QString Name = "Delta X 1";

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
    void ConnectDeltaRobot();
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
    void UpdatePositionControl(float x, float y, float z, float w, float u, float v, float f, float a);
    void UpdateGlobalHomePositionValueAndControlValue(float x, float y, float z, float w, float u, float v);
	void UpdateVelocity();
	void UpdateAccel();
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

	void UpdateConvenyorPosition(float x, float y);
	void DisplayGcodeVariable(QList<GcodeVariable> gcodeVariables);
	void SetConvenyorSpeed();
	void GetConvenyorPosition();
	void TurnEnoughConvenyorPositionGetting();
	void AddGcodeLine();
	void ChangeGcodeParameter();

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

    //--------Joystick-----------
    void ProcessJoystickButton(const QJoystickButtonEvent& event);
    void ProcessJoystickAxis(const QJoystickAxisEvent& event);
    void ProcessJoystickPOV(const QJoystickPOVEvent& event);

    //-------- Tab UX ---------
    void MaximizeTab(int index);

private:

	QString boldKey(QString key, QString htmlText);
	QString boldPlusKey(QString key, QString plus, QString htmlText);
	QString italyKey(QString key, QString htmlText);
	QString replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText);

    bool OpenConnectionDialog(QSerialPort* comPort, QTcpSocket* socket,QPushButton* connectButton, QLabel* comNameInfo = NULL);

	void initTabs();
	void hideExampleWidgets();
	void interpolateCircle();
	void makeEffectExample();

    //--------- Controller -------
    QJoysticks *joystick;

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

public:
    Ui::ProjectWindow *ui;
};


#endif // PROJECTWINDOW_H
