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
    // ---- Check software version ----

    DeltaXVersionManager = new VersionManager(this);
    DeltaXVersionManager->CurrentVersion = "0.9.6";
    DeltaXVersionManager->SoftwareName = "DeltaXSoftware";
    DeltaXVersionManager->CheckVersionUrl = "http://imwi.space/admin/server.php";
    DeltaXVersionManager->NewVersionSoftwareUrl = "https://sourceforge.net/projects/delta-x-software/files/";
    DeltaXVersionManager->CheckNewVersion(true);

    // ----- Init Pointer -----
    SoftwareManager::GetInstance()->SoftwarePointer = this;
    //------- Dasboard --------
    Dashboard = new TabDashboard();
    Dashboard->InitPanel(ui->wgLeftPanel, ui->swPageStack);
    Dashboard->InitPage(ui->tbHome, ui->pOperator);
    Dashboard->InitPage(ui->tbProject, ui->pProject);
    Dashboard->InitPage(ui->tbVariable, ui->pVariable);
    Dashboard->InitPage(ui->tbSetting, ui->pSetting);
    Dashboard->InitPage(ui->tbMarket, ui->pMarket);
    Dashboard->InitPage(ui->tbDocument, ui->pDocument);
    Dashboard->InitPage(ui->tbCommunity, ui->pCommunity);
    Dashboard->InitPage(ui->tbAuthority, ui->pAuthority);
    Dashboard->SetSelectedState("background-color: rgb(24, 70, 139);");

    connect(Dashboard, &TabDashboard::TabChanged, this, &MainWindow::SelectedTab);

    InitVisible();

    ui->tbHome->click();

    //-------- UX --------
    Ux = new UXManager();

    //-------- Variable Table -----------
    ProgramVariableManager = new VariableManager();
    ProgramVariableManager->SetTreeWidget(ui->trwProgramVariableTable);
    SoftwareManager::GetInstance()->ProgramVariableManager = ProgramVariableManager;

    //------- Project Manager --------
    SoftwareProjectManager = new ProjectManager();
    SoftwareProjectManager->InitTabManager(ui->twProjectManager);
    SoftwareProjectManager->InitAddNewTab(ui->tabAddNewButton);
    SoftwareProjectManager->IsNewTabSlotOutside = true;

    SoftwareManager::GetInstance()->SoftwareProjectManager = SoftwareProjectManager;
    //SoftwareManager::GetInstance()->RobotManagers = &RobotManagers;

    connect(SoftwareProjectManager, SIGNAL(NewTab_Signal(int)), SLOT(AddNewProjectAndrobot(int)));

    if (!IsLastProject())
    {
        RobotManager* robotManager = NewProject_Slot(0);
        robotManager->CreatNewRobotWindow();
    }
    else
    {
        openProject(LastProject);
    }

    InitProjectUX();

    //------------- Init Widgets -----------
    ui->trwProgramVariableTable->expandAll();
    ui->trwProgramVariableTable->setColumnWidth(0, 150);



    //--------- Init Dialog -------------
    CloseDialog = new SmartDialog(this);
    CloseDialog->SetType(CloseDialog->CLOSE_DIALOG);

    //--------- Authority ---------
    SoftwareAuthority = new Authority();
    SoftwareAuthority->wgOperatorDisplay = ui->wgOperatorDisplay;
    SoftwareAuthority->twOperatorParameter = ui->twOperatorParameter;
    SoftwareAuthority->lwOperatorDisplayWidget = ui->lwOperatorDisplayWidget;
    SoftwareAuthority->lwOperatorDisplayVariable = ui->lwOperatorDisplayVariable;
    SoftwareAuthority->lwOperatorGcodeProgram = ui->lwOperatorRobotGcodeProgram;
    SoftwareAuthority->fOperatorRobotOnOffPanel = ui->fOperatorRobotOnOffPanel;
    SoftwareAuthority->layoutOperatorRobotOnOff = ui->layoutOperatorRobotOnOff;

    connect(ProgramVariableManager, SIGNAL(variableChanged(QString, QString)), SoftwareAuthority, SLOT(UpdateVariableToDisplay(QString, QString)));

    Dashboard->SoftwareAuthority = SoftwareAuthority;

    InitProjectToOperator();

    on_pbApplyOperator_clicked();
}

bool MainWindow::IsLastProject()
{
    QSettings* settings = new QSettings("customUI.ini", QSettings::IniFormat);
    LastProject = settings->value("LastProject", "").toString();

    if (LastProject == "")
        return false;
    else
        return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool result = CloseDialog->PopUp("Close software", "Do you want to close the software?");

    if(result == false)
    {
        event->ignore();
    }
    else
    {
        qApp->exit();
        event->accept();
    }
}

void MainWindow::InitProjectUX()
{
    connect(ui->tbOpenProject, SIGNAL(clicked()), this, SLOT(OpenProjectFromFile()));
    connect(ui->tbSaveProject, SIGNAL(clicked()), this, SLOT(SaveProjectToFile()));
}

void MainWindow::InitVisible()
{
    ui->tbSetting->setVisible(false);
    ui->tbCommunity->setVisible(false);
    ui->tbDocument->setVisible(false);
    ui->tbMarket->setVisible(false);

    // ----- Load custom UI ----
    QSettings* settings = new QSettings("customUI.ini", QSettings::IniFormat);
    QString softwareName = settings->value("SoftwareName", "Delta X Software").toString();

    softwareName = QString("%1 - %2").arg(softwareName).arg(DeltaXVersionManager->CurrentVersion);
    this->setWindowTitle(softwareName);

    QString systemName = settings->value("SystemName", "Delta Robot System").toString();
    ui->leOperatorTitle->setText(systemName);
    ui->lbOperatorTitile->setText(systemName);

    LoadOperatorSettings();
}

void MainWindow::InitProjectToOperator()
{
    if (ui->cbOperatorProject->count() > 0)
        ui->cbOperatorProject->clear();

    if (ui->cbOperatorRobotDisplay->count() > 0)
        ui->cbOperatorRobotDisplay->clear();

    if (ui->cbOperatorRobot->count() > 0)
        ui->cbOperatorRobot->clear();

    foreach(RobotManager* robotManager, SoftwareProjectManager->RobotManagers)
    {
        ui->cbOperatorProject->addItem(robotManager->Name);
    }

    if (ui->cbOperatorProject->count() > 0)
    {
        ui->cbOperatorProject->setCurrentIndex(0);
    }
}

void MainWindow::SaveOperatorSettings()
{
    QSettings* settings = new QSettings("customUI.ini", QSettings::IniFormat);
    settings->setValue("AdminPassword", ui->leAuthorityPassword->text());

    QString widgetList = "";
    for (int i = 0; i < ui->lwOperatorDisplayWidget->count(); i++)
    {
        widgetList += ui->lwOperatorDisplayWidget->item(i)->text() + "\n";
    }
    settings->setValue("OperatorDisplayWidget", widgetList);

    QString variableList = "";
    for (int i = 0; i < ui->lwOperatorDisplayVariable->count(); i++)
    {
        variableList += ui->lwOperatorDisplayVariable->item(i)->text() + "\n";
    }
    settings->setValue("OperatorDisplayVariable", variableList);

    QString propramList = "";
    for (int i = 0; i < ui->lwOperatorRobotGcodeProgram->count(); i++)
    {
        propramList += ui->lwOperatorRobotGcodeProgram->item(i)->text() + "\n";
    }
    settings->setValue("OperatorRobotGcodeProgram", propramList);
}

void MainWindow::LoadOperatorSettings()
{
    QSettings* settings = new QSettings("customUI.ini", QSettings::IniFormat);

    ui->leAuthorityPassword->setText(settings->value("AdminPassword", "1234").toString());

    QString widgetList = settings->value("OperatorDisplayWidget", "").toString();

    foreach(QString str, widgetList.split('\n'))
    {
        if (str == "")
            continue;

        ui->lwOperatorDisplayWidget->addItem(str);
    }

    QString variableList = settings->value("OperatorDisplayVariable", "").toString();

    foreach(QString str, variableList.split('\n'))
    {
        if (str == "")
            continue;

        ui->lwOperatorDisplayVariable->addItem(str);
    }

    QString propramList = settings->value("OperatorRobotGcodeProgram", "").toString();

    foreach(QString str, propramList.split('\n'))
    {
        if (str == "")
            continue;

        ui->lwOperatorRobotGcodeProgram->addItem(str);
    }
}

RobotManager* MainWindow::NewProject_Slot(int index)
{
    QStackedWidget* stack = new QStackedWidget();

    //------- Make new robot manager ----------
    RobotManager* robotManager = new RobotManager(this);
    robotManager->SetMainStackedWidgetAndPages(ui->stackedWidget, ui->page, ui->pFullTabDisplay, ui->layoutFullTabDisplay);
    robotManager->SetSubStackedWidget(stack);
    robotManager->twProjectManager = ui->twProjectManager;

    robotManager->ID = ui->twProjectManager->count() - 1;
    robotManager->Name = QString("project " + QString::number(robotManager->ID));

    //Insert robot manager in this project to robot manager list ----------
    SoftwareProjectManager->RobotManagers.append(robotManager);

    //------ Create new robot project tab ---------
    SoftwareProjectManager->AddNewTab(stack, robotManager->ID, robotManager->Name);    

    SoftwareProjectManager->CurrentRobotManager = robotManager;

    return robotManager;
}

RobotWindow *MainWindow::AddNewProjectAndrobot(int index)
{
    RobotManager* robotManager = NewProject_Slot(index);
    return robotManager->CreatNewRobotWindow();
}

void MainWindow::OpenProjectFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Delta X Project"), QCoreApplication::applicationDirPath() + "/project/", tr("Project File (*.prx)"));

    if (fileName.isEmpty())
        return;

    openProject(fileName);
}

void MainWindow::SaveProjectToFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Delta X Project (*.prx)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName;
    fileName = dialog.getSaveFileName(this, "Save delta robot project", QApplication::applicationDirPath() + "/project", "Delta X Project (*.prx)");

    QSettings settings(fileName, QSettings::IniFormat);

    SoftwareProjectManager->CurrentRobotManager->SaveSettings(&settings);

    QSettings* settings2 = new QSettings("customUI.ini", QSettings::IniFormat);
    settings2->setValue("LastProject", fileName);
}

void MainWindow::SelectedTab(QAbstractButton *tabButton)
{
    if (tabButton->text() == "Admin")
    {
        QString currentProject = ui->cbOperatorProject->currentText();

        InitProjectToOperator();

        ui->cbOperatorProject->setCurrentText(currentProject);

        on_cbOperatorProject_currentIndexChanged(ui->cbOperatorProject->currentIndex());
    }
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < SoftwareProjectManager->RobotManagers.count(); i++)
    {
        for (int j = 0; j < SoftwareProjectManager->RobotManagers.at(i)->RobotWindows.count(); j++)
        {
            delete SoftwareProjectManager->RobotManagers.at(i)->RobotWindows.at(j);
        }
    }

    delete ui;
}

void MainWindow::on_pbApplyOperator_clicked()
{
    SoftwareAuthority->SetPassword(ui->leAuthorityPassword->text());
    SoftwareAuthority->ApplyOperatorSettings();

    Dashboard->Pass = ui->leAuthorityPassword->text();

    SaveOperatorSettings();

    ui->tbHome->click();

    Dashboard->Lock = true;

    SoftwareAuthority->Name = ui->leOperatorTitle->text();
    ui->lbOperatorTitile->setText(SoftwareAuthority->Name);

}


void MainWindow::on_pbSwitchProgramer_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Permission"),
                                         tr("Password (default \"1234\"):"), QLineEdit::Password, "", &ok);
    if (ok && !text.isEmpty())
    {
        if (SoftwareAuthority->IsPassword(text) == true)
        {
            SoftwareAuthority->ReturnProgramer();
            Dashboard->Lock = false;
            ui->tbAuthority->click();
        }
        else
        {
            QMessageBox::information(this, "Wrong", "You have entered the wrong password!");
            return;
        }
    }


}


void MainWindow::on_pbAddVarToOperatorDisplay_clicked()
{
    QString projectName = ui->cbOperatorProject->currentText().replace(" ", "");
    QString robotName = ui->cbOperatorRobotDisplay->currentText().replace(" ", "");
    QString var = ui->leOperatorVar->text().replace("#", "");
    QString fullVarName = projectName + "." + robotName + "." + var + ":" + ui->leOperatorVarName->text();
    ui->lwOperatorDisplayVariable->addItem(fullVarName);
}


void MainWindow::on_pbAddOperatorDisplayWidget_clicked()
{
    QString projectName = ui->cbOperatorProject->currentText();
    QString robotName = ui->cbOperatorRobotDisplay->currentText();
    QString fullVarName = projectName + "/" + robotName + "/" + ui->cbOperatorDisplayWidget->currentText();
    ui->lwOperatorDisplayWidget->addItem(fullVarName);
}


void MainWindow::on_pbDeleteOperatorDisplayWidget_clicked()
{
    QList<QListWidgetItem*> items = ui->lwOperatorDisplayWidget->selectedItems();

    foreach(QListWidgetItem* item, items)
    {
        ui->lwOperatorDisplayWidget->takeItem(ui->lwOperatorDisplayVariable->currentRow());
    }
}


void MainWindow::on_pbDeleteOperatorVar_clicked()
{
    QList<QListWidgetItem*> items = ui->lwOperatorDisplayVariable->selectedItems();

    foreach(QListWidgetItem* item, items)
    {
        ui->lwOperatorDisplayVariable->takeItem(ui->lwOperatorDisplayVariable->currentRow());
    }
}


void MainWindow::on_cbOperatorProject_currentIndexChanged(int index)
{
    if (index == -1)
        return;

    ui->cbOperatorRobotDisplay->clear();
    ui->cbOperatorRobot->clear();

    foreach(RobotWindow* robotWindow, SoftwareProjectManager->RobotManagers[index]->RobotWindows)
    {
        ui->cbOperatorRobotDisplay->addItem(robotWindow->Name);
        ui->cbOperatorRobot->addItem(robotWindow->Name);
    }

    ui->cbOperatorGcodeProgram->clear();

    ui->cbOperatorGcodeProgram->addItems(SoftwareProjectManager->RobotManagers[index]->RobotWindows[0]->DeltaGcodeManager->GetProgramNames());
}

void MainWindow::on_pbStartSystem_clicked()
{
    for(int i = 0; i < SoftwareAuthority->RobotEnableList.count(); i++)
    {
        QCheckBox* robotEnable = SoftwareAuthority->RobotEnableList.at(i);
        if (robotEnable->isChecked() == false)
            continue;

        RobotWindow* robotWindow = SoftwareAuthority->robotManager->GetRobot(robotEnable->text());

        foreach(QString robotGcode, SoftwareAuthority->operatorGcodeProgram)
        {
            QStringList paras = robotGcode.split(':');
            if (robotWindow->Name == paras[0])
            {
                robotWindow->DeltaGcodeManager->SelectProgram(paras[1]);
                robotWindow->ClickExecuteButton(true);
            }
        }

    }
}

void MainWindow::on_pbStopSystem_clicked()
{
    SoftwareAuthority->robotManager->Stop();
}

void MainWindow::openProject(QString fullName)
{
    QSettings* settings = new QSettings(fullName, QSettings::IniFormat);

    int robotNumber = settings->value("Project/RobotNumber").toInt();
    int tabID = ui->twProjectManager->count() - 1; // x
    RobotManager* robotManager = NewProject_Slot(tabID);
    robotManager->LoadSettings(settings);
}


void MainWindow::on_pbAddOperatorGcodeProgram_clicked()
{
    QString projectName = ui->cbOperatorProject->currentText().replace(" ", "");
    QString robotName = ui->cbOperatorRobot->currentText().replace(" ", "");
    QString programName = ui->cbOperatorGcodeProgram->currentText();
    QString fullVarName = robotName + ":\"" + programName + "\"";

    bool isNew = true;

    for (int i = 0; i < ui->lwOperatorRobotGcodeProgram->count(); i++)
    {
        QString row = ui->lwOperatorRobotGcodeProgram->item(i)->text();
        QStringList paras = row.split(':');

        if (paras[0] == robotName)
        {
            isNew = false;
            ui->lwOperatorRobotGcodeProgram->takeItem(i);
            break;
        }
    }

    ui->lwOperatorRobotGcodeProgram->addItem(fullVarName);
}


void MainWindow::on_pbDeleteOperatorGcodeProgram_clicked()
{
    QList<QListWidgetItem*> items = ui->lwOperatorRobotGcodeProgram->selectedItems();

    ui->lwOperatorRobotGcodeProgram->takeItem(ui->lwOperatorRobotGcodeProgram->currentRow());

}

