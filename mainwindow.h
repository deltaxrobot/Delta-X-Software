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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitEvents();
    void InitVariables();

    ConnectionManager* DeltaPort;
	GcodeProgramManager* DeltaGcodeManager;
    GLWidget* VisualArea;
	DeltaVisualizer *DeltaParameter;
	ImageProcesser* DeltaImageProcesser;
	DrawingExporter* DeltaDrawingExporter;

	ConnectionManager* CurrentDeltaPort;

	QTimer* EditorTimer;
	QTimer* ConvenyorTimer;

private slots:
    void ConnectDeltaRobot();
	void AddNewProgram();
	void SaveProgram();
	void ExecuteProgram();
	void ExecuteCurrentLine();
	void UpdateZLineEditValue(int z);
	void UpdateWLineEditValue(int w);
	void UpdateDeltaPositionFromLineEditValue();
	void UpdatePositionFrom2DControl(float x, float y, float z, float w);
	void UpdatePositionControl(float x, float y, float z, float w);
	void UpdateGlobalHomePositionValueAndControlValue(float x, float y, float z, float w);
	void Grip();
	void SetPump(bool value);
	void Home();
	void UpdateConvenyorPosition(float x, float y);
	void DisplayGcodeVariable(QList<GcodeVariable> gcodeVariables);
	void SetConvenyorSpeed();
	void GetConvenyorPosition();
	void TurnEnoughConvenyorPositionGetting();
	void AddGcodeLine();
	void ChangeGcodeParameter();

	void TerminalTransmit();
	void PrintReceiveData(QString msg);

	void NoticeConnected();

	void RunSmartEditor();
	void StandardFormatEditor();

	void OpenGcodeReference();

	void ChangeDeltaDashboard(int index);
private:

	void hideExampleWidgets();
	void interpolateCircle();
	void makeEffectExample();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
