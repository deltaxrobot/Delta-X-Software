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
    GLWidget* VisualArea;
    QTimer* Timer1;
    cv::VideoCapture cap;

private slots:
    void ConnectDeltaRobot();
    void UpdateCameraScreen();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
