#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TabDashboard.h"
#include "RobotWindow.h"
#include <QSettings>
#include "QStackedWidget"
#include <QList>

#include "VersionManager.h"
#include "Authority.h"
#include "UnityTool.h"
#include <QFileInfo>

#include <QSettings>
#include <QElapsedTimer>
#include <QTimer>

namespace Ui {
class MainWindow;
}

//class SoftwareManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitVariables();
    void closeEvent(QCloseEvent *event);
    void InitProjectUX();
    void InitVisible();
    void InitProjectToOperator();
    void SaveOperatorSettings();
    void LoadOperatorSettings();

    TabDashboard* Dashboard;
    ProjectManager* SoftwareProjectManager;
    VersionManager* DeltaXVersionManager;
    SmartDialog* CloseDialog;
    Authority* SoftwareAuthority;

    QStandardItemModel VariableTreeModel;

public slots:
    QStackedWidget* CreateNewProject(int index);
    RobotWindow *AddNewProjectAndRobot(int index);
    void OpenProjectFromFile();
    void SaveProjectToFile();
    void SelectedTab(QAbstractButton* tabButton);
    void Log(QString msg);

    void UpdateVarToTreeView(QString key, QVariant value);
    void RemoveVarFromTreeView(const QString &key);
    void SetLoadingIconRun(bool isRun);

    void onTreeViewItemClicked(const QModelIndex &index);

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

    void on_tbExpandLoggingBox_clicked();

    void on_pbUpdateVarDisplay_clicked();

    void on_pbDeleteSelectedVar_clicked();

private:
    QTimer timer1;

    void openProject(QString fullName);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
