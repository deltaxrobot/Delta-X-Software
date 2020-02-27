#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ConnectionManager.h"
#include "glwidget.h"
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
#include <qwebengineview.h>

namespace Ui {
class MainWindow;
}

class MainWindow;
class ImageProcesser;
class GcodeProgramManager;
class GcodeVariable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitEvents();
    void InitVariables();
	void AddInstance(QList<MainWindow*>* deltaXMainWindows = NULL);

    ConnectionManager* DeltaPort;
	GcodeProgramManager* DeltaGcodeManager;
    GLWidget* VisualArea;
	DeltaVisualizer *DeltaParameter;
	ImageProcesser* DeltaImageProcesser;
	DrawingExporter* DeltaDrawingExporter;

	ConnectionManager* CurrentDeltaPort;

	QTimer* EditorTimer;
	QTimer* ConvenyorTimer;

	//QList<DeltaXDashboard*> DeltaXDashboards;
	QList<MainWindow*>* DeltaXMainWindows = NULL;
	QAction* SelectedAction = NULL;
	int ID = 0;
	QString Name = "Delta X 1";

	QNetworkAccessManager *HttpManager;
	QString SoftwareVersion = "0.9.1.2";
private slots:
    void ConnectDeltaRobot();
	void AddNewProgram();
	void SaveProgram();
	void ExecuteProgram();
	void ExecuteSelectPrograms();
	void ExecuteCurrentLine();
	void UpdateZLineEditValue(int z);
	void UpdateWLineEditValue(int w);
	void UpdateDeltaPositionFromLineEditValue();
	void UpdatePositionFrom2DControl(float x, float y, float z, float w);
	void UpdatePositionControl(float x, float y, float z, float w);
	void UpdateGlobalHomePositionValueAndControlValue(float x, float y, float z, float w);
	void UpdateVelocity();
	void UpdateAccel();
	void AdjustGripperAngle(int angle);
	void Grip();
	void SetPump(bool value);
	void SetLaser(bool value);
	void Home();
	void UpdateConvenyorPosition(float x, float y);
	void DisplayGcodeVariable(QList<GcodeVariable> gcodeVariables);
	void SetConvenyorSpeed();
	void GetConvenyorPosition();
	void TurnEnoughConvenyorPositionGetting();
	void AddGcodeLine();
	void ChangeGcodeParameter();

	void ConnectConveyor();
	void SetConveyorMode(int mode);
	void MoveConveyor();

	void ConnectSliding();
	void GoHomeSliding();
	void DisableSliding();
	void SetSlidingSpeed();
	void SetSlidingPosition();

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
private:

	QString boldKey(QString key, QString htmlText);
	QString boldPlusKey(QString key, QString plus, QString htmlText);
	QString italyKey(QString key, QString htmlText);
	QString replaceHtmlSection(QString start, int offset, int maxlen, QString finish, QString beforeSection, QString afterSection, QString htmlText);

	void initTabs();
	void hideExampleWidgets();
	void interpolateCircle();
	void makeEffectExample();
public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
