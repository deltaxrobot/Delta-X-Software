#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitVariables();
}

void MainWindow::InitVariables()
{
    //------- Dasboard --------
    Dashboard = new TabDashboard(this);
    Dashboard->InitPanel(ui->wgLeftPanel, ui->swPageStack);
    Dashboard->InitPage(ui->tbHome, ui->pHome);
    Dashboard->InitPage(ui->tbProject, ui->pProject);
    Dashboard->InitPage(ui->tbVariable, ui->pVariable);
    Dashboard->InitPage(ui->tbSetting, ui->pSetting);
    Dashboard->InitPage(ui->tbMarket, ui->pMarket);
    Dashboard->InitPage(ui->tbDocument, ui->pDocument);
    Dashboard->InitPage(ui->tbCommunity, ui->pCommunity);
    Dashboard->InitPage(ui->tbAccount, ui->pAccount);
    Dashboard->SetSelectedState("background-color: rgb(0, 110, 255);");

    //------- Project Manager --------
    RobotProjectManager = new ProjectManager(this);
    RobotProjectManager->InitTabManager(ui->twProjectManager);
    RobotProjectManager->InitAddNewTab(ui->tabAddNewButton);

    if (!IsLastProject())
    {
        RobotProjectManager->InitDefaultTab(ui->tabDefaultProject);
        RobotProjectManager->InitDefaultProject(new ProjectWindow());
    }

}

bool MainWindow::IsLastProject()
{
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
