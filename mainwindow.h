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

	QTimer* EditorTimer;

private slots:
    void ConnectDeltaRobot();
	void AddNewProgram();
	void SaveProgram();
	void ExecuteProgram();
	void UpdateZValue(int z);
	void UpdateDeltaPosition();
	void UpdatePositionValue(float x, float y, float z);
	void UpdateHomePosition(float x, float y, float z);
	void Grip();
	void SetPump(bool value);
	void Home();

	void AddGcodeLine();

	void TerminalTransmit();
	void PrintReceiveData(QString msg);

	void NoticeConnected();

	void RunSmartEditor();
	void StandardFormatEditor();

	void OpenGcodeReference();
private:

	void hideExampleWidgets();
	void interpolateCircle();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
