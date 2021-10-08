#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robotmanager.h"
#include "TabDashboard.h"
#include "ProjectManager.h"
#include "RobotWindow.h"
#include <QSettings>
#include "UXManager.h"
#include "QStackedWidget"
#include "robotmanager.h"
#include <QList>
#include "VariableManager.h"
#include "SoftwareManager.h"
#include "VersionManager.h"

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
    void closeEvent(QCloseEvent *event);

    TabDashboard* Dashboard;
    ProjectManager* RobotProjectManager;
    QList<RobotManager*> RobotManagers;
    QSettings* ProjectSetting;
    UXManager* Ux;
    VariableManager* ProgramVariableManager;
    VersionManager* DeltaXVersionManager;
    SmartDialog* CloseDialog;

public slots:
    void NewProject_Slot(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
