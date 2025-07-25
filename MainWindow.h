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
#include <QHeaderView>
#include <QAbstractItemView>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColor>
#include <QFont>

class SettingsPanel;

namespace Ui {
class MainWindow;
}

//class SoftwareManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Page identifiers for better code readability
    enum PageType {
        PAGE_VARIABLE = 0,
        PAGE_OPERATOR = 1,
        PAGE_HOME = 2,
        PAGE_MARKET = 3,
        PAGE_DOCUMENT = 4,
        PAGE_AUTHORITY = 5,
        PAGE_COMMUNITY = 6,
        PAGE_SETTING = 7,
        PAGE_PROJECT = 8
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitVariables();
    void closeEvent(QCloseEvent *event);
    void InitProjectUX();
    void InitVisible();
    void InitProjectToOperator();
    void SaveOperatorSettings();
    void LoadOperatorSettings();
    void SetDefaultPage(PageType pageType);
    void InitVariableTreeView();

    TabDashboard* Dashboard;
    ProjectManager* SoftwareProjectManager;
    VersionManager* DeltaXVersionManager;
    SmartDialog* CloseDialog;
    Authority* SoftwareAuthority;
    SettingsPanel* m_settingsPanel;

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
