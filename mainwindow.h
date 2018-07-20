#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ConnectionManager.h"
#include "glwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

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

private slots:
    void ConnectDeltaRobot();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
