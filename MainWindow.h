#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robotmanager.h"
#include "TabDashboard.h"
#include "ProjectManager.h"
#include "ProjectWindow.h"
#include <QSettings>
#include "UXManager.h"
#include "QStackedWidget"

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
    UXManager* Ux;

public slots:
    void NewProject_Slot(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
