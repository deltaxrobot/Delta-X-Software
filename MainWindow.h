#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robotmanager.h"
#include "TabDashboard.h"
#include "ProjectManager.h"
#include "ProjectWindow.h"
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitVariables();
    bool IsLastProject();

    TabDashboard* Dashboard;
    ProjectManager* RobotProjectManager;
    QSettings* ProjectSetting;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
