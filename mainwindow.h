#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ConnectionManager.h"
#include "glwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>
#include <stdio.h>
#include <UnityTool.h>
#include <GcodeProgramManager.h>
#include <DeltaVisualizer.h>
#include <qmath.h>
#include <hsvwindow.h>

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

    QTimer* Timer1;
	QTimer* EditorTimer;
    cv::VideoCapture cap;

private slots:
    void ConnectDeltaRobot();
    void UpdateCameraScreen();
	void AddNewProgram();
	void SaveProgram();
	void ExecuteProgram();
	void UpdateZValue(int z);
	void UpdateDeltaPosition();
	void UpdatePositionValue(float x, float y, float z);
	void Home();

	void AddGcodeLine();

	void TerminalTransmit();
	void PrintReceiveData(QString msg);

	void NoticeConnected();

	void OpenHSVPanel();

	void RunSmartEditor();
	void StandardFormatEditor();

private:
	void HideExampleWidgets();
	void InterpolateCircle();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
