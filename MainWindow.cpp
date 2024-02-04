#include "MainWindow.h"
#include "SoftwareManager.h"
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
    VariableManager::instance().loadFromQSettings();

    QElapsedTimer time;
    qint64 start = time.elapsed();

    connect(&timer1, &QTimer::timeout, this, &MainWindow::SaveProjectToFile);
//    timer1.start(5000);

    SetLoadingIconRun(true);

    // ---- Check software version ----

    DeltaXVersionManager = new VersionManager(this);
    DeltaXVersionManager->CurrentVersion = "1.2 Beta";
    DeltaXVersionManager->SoftwareName = "DeltaXSoftware";
    DeltaXVersionManager->CheckVersionUrl = "http://imwi.space/admin/server.php";
    DeltaXVersionManager->NewVersionSoftwareUrl = "https://sourceforge.net/projects/delta-x-software/files/";
//    DeltaXVersionManager->CheckNewVersion(true);

    // ----- Init Pointer -----
    SoftwareManager::GetInstance()->SoftwarePointer = this;
//    ui->tvVariables->setModel(&SoftwareManager::GetInstance()->SoftwarePointer->VariableTreeModel);
    SoftwareManager::GetInstance()->SoftwarePath = QApplication::applicationDirPath();

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

//    ui->tbHome->click();

    //-------- UX --------

    teSoftwareLog = ui->teLoggingBox;

    //-------- Variable Table -----------
//    VariableTreeModel.setHorizontalHeaderLabels(QStringList() << "Name" << "Value");
//    connect(&VariableManager::instance(), SIGNAL(varUpdated(QString, QVariant)), this, SLOT(UpdateVarToTreeView(QString, QVariant)));
//    connect(&VariableManager::instance(), SIGNAL(varAdded(QString, QVariant)), this, SLOT(UpdateVarToTreeView(QString, QVariant)));
//    connect(&VariableManager::instance(), SIGNAL(varRemoved(QString)), this, SLOT(RemoveVarFromTreeView(QString)));

    ui->tvVariables->setModel(&VariableTreeModel);
    VariableManager::instance().addItemModel(&VariableTreeModel);
    VariableManager::instance().loadFromQSettings();

    connect(ui->tvVariables, &QTreeView::clicked, this, &MainWindow::onTreeViewItemClicked);


    //------- Project Manager --------
    SoftwareProjectManager = new ProjectManager();
    SoftwareProjectManager->InitTabManager(ui->twProjectManager);
    SoftwareProjectManager->InitAddNewTab(ui->tabAddNewButton);
    SoftwareProjectManager->IsNewTabSlotOutside = true;

    SoftwareManager::GetInstance()->SoftwareProjectManager = SoftwareProjectManager;

    connect(SoftwareProjectManager, SIGNAL(NewTab_Signal(int)), SLOT(AddNewProjectAndRobot(int)));

    if (!IsLastProject())
    {
        RobotWindow* robotWindow = AddNewProjectAndRobot(0);
    }
    else
    {
        openProject(LastProject);
    }

    InitProjectUX();

    //------------- Init Widgets -----------
    ui->tvVariables->expandAll();

    //--------- Init Dialog -------------
    CloseDialog = new SmartDialog(this);
    CloseDialog->SetType(CloseDialog->CLOSE_DIALOG);

    //--------- Authority ---------
    SoftwareAuthority = new Authority();
    SoftwareAuthority->wgOperatorDisplay = ui->wgOperatorDisplay;
    SoftwareAuthority->gvOperatorViewer = ui->gvOperatorViewer;
    SoftwareAuthority->twOperatorParameter = ui->twOperatorParameter;
    SoftwareAuthority->lwOperatorDisplayWidget = ui->lwOperatorDisplayWidget;
    SoftwareAuthority->lwOperatorDisplayVariable = ui->lwOperatorDisplayVariable;
    SoftwareAuthority->lwOperatorGcodeProgram = ui->lwOperatorRobotGcodeProgram;
    SoftwareAuthority->fOperatorRobotOnOffPanel = ui->fOperatorRobotOnOffPanel;
    SoftwareAuthority->layoutOperatorRobotOnOff = ui->layoutOperatorRobotOnOff;


    connect(&VariableManager::instance(), SIGNAL(varUpdated(QString, QVariant)), SoftwareAuthority, SLOT(UpdateVariableToDisplay(QString, QVariant)));

    Dashboard->SoftwareAuthority = SoftwareAuthority;

    InitProjectToOperator();

//    on_pbApplyOperator_clicked();

    SetLoadingIconRun(false);

    qDebug() << time.elapsed() - start;
}

bool MainWindow::IsLastProject()
{
    QSettings settings("customUI.ini", QSettings::IniFormat);
    LastProject = settings.value("LastProject", "").toString();

    if(QFileInfo::exists(LastProject))
    {
        return true;
    }
    else
    {
        return false;
    }
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
//    connect(ui->tbOpenProject, SIGNAL(clicked()), this, SLOT(OpenProjectFromFile()));
    connect(ui->tbSaveProject, SIGNAL(clicked()), this, SLOT(SaveProjectToFile()));
}

void MainWindow::InitVisible()
{
//    ui->tbSetting->setVisible(false);
    ui->tbHome->setVisible(false);
    ui->tbCommunity->setVisible(false);
    ui->tbDocument->setVisible(false);
    ui->tbMarket->setVisible(false);
    ui->tbAuthority->setVisible(false);
    ui->tbSaveProject->setVisible(true);
    ui->tbOpenProject->setVisible(false);

    // ----- Load custom UI ----
    QSettings settings("customUI.ini", QSettings::IniFormat);
    QString softwareName = settings.value("SoftwareName", "Delta X Software").toString();

    softwareName = QString("%1 - %2").arg(softwareName).arg(DeltaXVersionManager->CurrentVersion);
    this->setWindowTitle(softwareName);

    QString systemName = settings.value("SystemName", "Delta Robot System").toString();
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

    foreach(RobotWindow* robotWindow, SoftwareProjectManager->RobotWindows)
    {
        ui->cbOperatorProject->addItem(robotWindow->ProjectName);
    }

    if (ui->cbOperatorProject->count() > 0)
    {
        ui->cbOperatorProject->setCurrentIndex(0);
    }
}

void MainWindow::SaveOperatorSettings()
{
    QFile file(QCoreApplication::applicationDirPath() + "/customUI.ini");
    if (!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    QSettings settings("customUI.ini", QSettings::IniFormat);
    settings.setValue("AdminPassword", ui->leAuthorityPassword->text());

    QString widgetList = "";
    for (int i = 0; i < ui->lwOperatorDisplayWidget->count(); i++)
    {
        widgetList += ui->lwOperatorDisplayWidget->item(i)->text() + "\n";
    }
    settings.setValue("OperatorDisplayWidget", widgetList);

    QString variableList = "";
    for (int i = 0; i < ui->lwOperatorDisplayVariable->count(); i++)
    {
        variableList += ui->lwOperatorDisplayVariable->item(i)->text() + "\n";
    }
    settings.setValue("OperatorDisplayVariable", variableList);

    QString propramList = "";
    for (int i = 0; i < ui->lwOperatorRobotGcodeProgram->count(); i++)
    {
        propramList += ui->lwOperatorRobotGcodeProgram->item(i)->text() + "\n";
    }
    settings.setValue("OperatorRobotGcodeProgram", propramList);
}

void MainWindow::LoadOperatorSettings()
{
    QSettings settings("customUI.ini", QSettings::IniFormat);

    ui->leAuthorityPassword->setText(settings.value("AdminPassword", "1234").toString());

    QString widgetList = settings.value("OperatorDisplayWidget", "").toString();

    foreach(QString str, widgetList.split('\n'))
    {
        if (str == "")
            continue;

        ui->lwOperatorDisplayWidget->addItem(str);
    }

    QString variableList = settings.value("OperatorDisplayVariable", "").toString();

    foreach(QString str, variableList.split('\n'))
    {
        if (str == "")
            continue;

        ui->lwOperatorDisplayVariable->addItem(str);
    }

    QString propramList = settings.value("OperatorRobotGcodeProgram", "").toString();

    foreach(QString str, propramList.split('\n'))
    {
        if (str == "")
            continue;

        ui->lwOperatorRobotGcodeProgram->addItem(str);
    }
}

QStackedWidget* MainWindow::CreateNewProject(int index)
{
    QStackedWidget* stack = new QStackedWidget();
    int projectTabID = ui->twProjectManager->count() - 1;
    QString projectName = QString("project") + QString::number(projectTabID);
    SoftwareProjectManager->AddNewTab(stack, projectTabID, projectName);

    return stack;
}

RobotWindow *MainWindow::AddNewProjectAndRobot(int index)
{
    QStackedWidget *stack = CreateNewProject(index);

    RobotWindow* robotWindow = new RobotWindow(this, SoftwareProjectManager->GetProjectName(index));
    SoftwareProjectManager->RobotWindows.append(robotWindow);

    robotWindow->SetMainStackedWidgetAndPages(ui->stackedWidget, ui->page, ui->pFullTabDisplay, ui->layoutFullTabDisplay);
    robotWindow->SetSubStackedWidget(ui->swPageStack);

    stack->addWidget(robotWindow);
    stack->setCurrentWidget(robotWindow);

    return robotWindow;
}

void MainWindow::OpenProjectFromFile()
{
//    QDir dir = QCoreApplication::applicationDirPath() + "/project/";
//    if (!dir.exists())
//        dir.mkpath(".");

//    QString fileName = QFileDialog::getOpenFileName(this,
//        tr("Open Delta X Project"), dir.path(), tr("Project File (*.prx)"));

//    if (fileName.isEmpty())
//        return;

//    openProject(fileName);
}

void MainWindow::SaveProjectToFile()
{
    if (SoftwareManager::GetInstance()->RunningScriptThreadNumber > 0)
        return;

    VariableManager::instance().saveToQSettings();

    SaveOperatorSettings();
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

void MainWindow::Log(QString msg)
{
    ui->teLoggingBox->moveCursor (QTextCursor::End);
    ui->teLoggingBox->insertPlainText(msg);
    ui->teLoggingBox->moveCursor(QTextCursor::End);
}

void MainWindow::UpdateVarToTreeView(QString key, QVariant value)
{
    QStandardItem *parent = VariableTreeModel.invisibleRootItem();
    QStringList parts = key.split('.');

    for (int i = 0; i < parts.count() - 1; ++i) {
        QString part = parts[i];
        QStandardItem *child = nullptr;
        for (int j = 0; j < parent->rowCount(); ++j) {
            if (parent->child(j)->text() == part) {
                child = parent->child(j);
                break;
            }
        }
        if (!child) {
            child = new QStandardItem(part);
            parent->appendRow(child);
        }
        parent = child;
    }
    bool found = false;
    for (int i = 0; i < parent->rowCount(); ++i) {
        if (parent->child(i)->text() == parts.last()) {
            parent->child(i, 1)->setText(value.toString());
            found = true;
            break;
        }
    }
    if (!found) {
        parent->appendRow(QList<QStandardItem*>() << new QStandardItem(parts.last()) << new QStandardItem(value.toString()));
    }
}

void MainWindow::RemoveVarFromTreeView(const QString &key)
{
    QStandardItem *parent = VariableTreeModel.invisibleRootItem();
    QStringList parts = key.split('.');

    for (int i = 0; i < parts.count() - 1; ++i) {
        QString part = parts[i];
        QStandardItem *child = nullptr;
        for (int j = 0; j < parent->rowCount(); ++j) {
            if (parent->child(j)->text() == part) {
                child = parent->child(j);
                break;
            }
        }
        if (!child) {
            // Nếu không tìm thấy phần nào của key, thì thoát khỏi hàm
            return;
        }
        parent = child;
    }

    // Tìm và xóa mục cần thiết
    for (int i = 0; i < parent->rowCount(); ++i) {
        if (parent->child(i)->text() == parts.last()) {
            parent->removeRow(i);
            break;
        }
    }
}

void MainWindow::SetLoadingIconRun(bool isRun)
{
//    QMovie* movie = ui->lbLoadingIcon->movie();

//    if (movie == NULL)
//    {
//        movie = new QMovie(":/icon/deltax-loading.gif");
//        ui->lbLoadingIcon->setMovie(movie);
//    }

//    if (isRun == false)
//    {
//        ui->lbLoadingIcon->hide();
//        movie->stop();
//    }
//    else
//    {
//        ui->lbLoadingIcon->show();
//        movie->start();
//    }

}

void MainWindow::onTreeViewItemClicked(const QModelIndex &index)
{
    QStandardItem *item = VariableTreeModel.itemFromIndex(index);
    QString key = item->parent()->child(index.row(), 0)->text();
    // Lấy tên của các item cha của item hiện tại và gán lại thành mẫu như sau "item1.item2.item3"
    for (QStandardItem *parent = item->parent(); parent != nullptr; parent = parent->parent()) {
        key = parent->text() + "." + key;
    }

    QString value = item->parent()->child(index.row(), 1)->text();

    ui->leUpdateKey->setText(key);
    ui->leUpdateValue->setText(value);

}

MainWindow::~MainWindow()
{
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
                                         tr("Password (default \"1234\"):"), QLineEdit::Password, "1234", &ok);
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
    ui->lwOperatorDisplayWidget->takeItem(ui->lwOperatorDisplayWidget->currentRow());
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

    ui->cbOperatorGcodeProgram->clear();

//    ui->cbOperatorGcodeProgram->addItems("");
}

void MainWindow::on_pbStartSystem_clicked()
{
//    if (SoftwareAuthority->robotManager == NULL)
//        return;

    for(int i = 0; i < SoftwareAuthority->RobotEnableList.count(); i++)
    {
        QCheckBox* robotEnable = SoftwareAuthority->RobotEnableList.at(i);
        if (robotEnable->isChecked() == false)
            continue;

//        RobotWindow* robotWindow = SoftwareAuthority->robotManager->GetRobot(robotEnable->text());

//        foreach(QString robotGcode, SoftwareAuthority->operatorGcodeProgram)
//        {
//            QStringList paras = robotGcode.split(':');
//            if (robotWindow->Name == paras[0])
//            {
//                robotWindow->ClickExecuteButton(true);
//            }
//        }

    }
}

void MainWindow::on_pbStopSystem_clicked()
{
//    if (SoftwareAuthority->robotManager == NULL)
//        return;

//    SoftwareAuthority->robotManager->Stop();
}

void MainWindow::openProject(QString fullName)
{
    QSettings* settings = new QSettings(fullName, QSettings::IniFormat);

    SoftwareLog(QString("Load project: ") + fullName);

    int robotNumber = settings->value("Project/RobotNumber").toInt();
    int tabID = ui->twProjectManager->count() - 1; // x
    RobotWindow* robotWindow = AddNewProjectAndRobot(tabID);
//    robotWindow->LoadSettings(settings);
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


void MainWindow::on_tbExpandLoggingBox_clicked()
{
    if (ui->teLoggingBox->minimumHeight() == 300)
        ui->teLoggingBox->setMinimumHeight(0);
    else
        ui->teLoggingBox->setMinimumHeight(300);
}

void MainWindow::on_pbUpdateVarDisplay_clicked()
{
    VariableManager::instance().updateVar(ui->leUpdateKey->text(), ui->leUpdateValue->text());
}


void MainWindow::on_pbDeleteSelectedVar_clicked()
{
    QModelIndexList selectedIndexes = ui->tvVariables->selectionModel()->selectedIndexes();
    if(!selectedIndexes.isEmpty())
    {
        // Assuming you are using QStandardItemModel
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tvVariables->model());
        if(model)
        {
            // Get the index of the selected item
            QModelIndex index = selectedIndexes.first();
            // Get the item of the model
            QStandardItem* item = model->itemFromIndex(index);
            // Remove the item
            model->removeRow(item->row(), index.parent());

            VariableManager::instance().removeVar(ui->leUpdateKey->text());
        }
    }
}

