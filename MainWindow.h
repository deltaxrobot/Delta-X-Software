#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TabDashboard.h"
#include "RobotWindow.h"
#include <QSettings>
#include "UXManager.h"
#include "QStackedWidget"
#include <QList>
#include "VariableManager.h"
#include "SoftwareManager.h"
#include "VersionManager.h"
#include "Authority.h"

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
    void closeEvent(QCloseEvent *event);
    void InitProjectUX();
    void InitVisible();
    void InitProjectToOperator();
    void SaveOperatorSettings();
    void LoadOperatorSettings();

    TabDashboard* Dashboard;
    ProjectManager* SoftwareProjectManager;
    QSettings* ProjectSetting;
    UXManager* Ux;
    VariableManager* ProgramVariableManager;
    VersionManager* DeltaXVersionManager;
    SmartDialog* CloseDialog;
    Authority* SoftwareAuthority;

    QString LastProject = "";

public slots:
    RobotManager* NewProject_Slot(int index);
    RobotWindow *AddNewProjectAndrobot(int index);
    void OpenProjectFromFile();
    void SaveProjectToFile();
    void SelectedTab(QAbstractButton* tabButton);

private slots:
    void on_pbApplyOperator_clicked();

    void on_pbSwitchProgramer_clicked();

    void on_pbAddVarToOperatorDisplay_clicked();

    void on_pbAddOperatorDisplayWidget_clicked();

    void on_pbDeleteOperatorDisplayWidget_clicked();

    void on_pbDeleteOperatorVar_clicked();

    void on_cbOperatorProject_currentIndexChanged(int index);

    void on_pbStartSystem_clicked();

    void on_pbStopSystem_clicked();

    void on_pbAddOperatorGcodeProgram_clicked();

    void on_pbDeleteOperatorGcodeProgram_clicked();

private:
    void openProject(QString fullName);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
