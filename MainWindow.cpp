#include "MainWindow.h"
#include "SoftwareManager.h"
#include "ui_MainWindow.h"
#include "SettingsManager.h"
#include "SettingsPanel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitVariables();
}

void MainWindow::InitVariables()
{
    //-------- Variable -----------

    ui->tvVariables->setModel(&VariableTreeModel);
    VariableManager::instance().addItemModel(&VariableTreeModel);

    // Initialize and style the variable tree view
    InitVariableTreeView();

    VariableManager::instance().loadFromQSettings();

    connect(ui->tvVariables, &QTreeView::clicked, this, &MainWindow::onTreeViewItemClicked);
    
    // Enable context menu for better user interaction
    ui->tvVariables->setContextMenuPolicy(Qt::ActionsContextMenu);
    
    // Add context menu actions
    QAction* expandAllAction = new QAction("Expand All", this);
    QAction* collapseAllAction = new QAction("Collapse All", this);
    QAction* copyKeyAction = new QAction("Copy Key", this);
    QAction* copyValueAction = new QAction("Copy Value", this);
    
    ui->tvVariables->addAction(expandAllAction);
    ui->tvVariables->addAction(collapseAllAction);
    ui->tvVariables->addAction(copyKeyAction);
    ui->tvVariables->addAction(copyValueAction);
    
    connect(expandAllAction, &QAction::triggered, ui->tvVariables, &QTreeView::expandAll);
    connect(collapseAllAction, &QAction::triggered, ui->tvVariables, &QTreeView::collapseAll);
    connect(copyKeyAction, &QAction::triggered, [this]() {
        if (!ui->leUpdateKey->text().isEmpty()) {
            QApplication::clipboard()->setText(ui->leUpdateKey->text());
        }
    });
    connect(copyValueAction, &QAction::triggered, [this]() {
        if (!ui->leUpdateValue->text().isEmpty()) {
            QApplication::clipboard()->setText(ui->leUpdateValue->text());
        }
    });

    // -------------------------

    QElapsedTimer time;
    qint64 start = time.elapsed();

    connect(&timer1, &QTimer::timeout, this, &MainWindow::SaveProjectToFile);
//    timer1.start(5000);

    SetLoadingIconRun(true);

    // ---- Check software version ----

    DeltaXVersionManager = new VersionManager(this);
    DeltaXVersionManager->CurrentVersion = "1.3.0";
    DeltaXVersionManager->SoftwareName = "DeltaXSoftware";
    DeltaXVersionManager->CheckNewVersion(true);

    // ----- Init Pointer -----
    SoftwareManager::GetInstance()->SoftwarePointer = this;
    SoftwareManager::GetInstance()->SoftwarePath = QApplication::applicationDirPath();

    // ----- Init Settings Panel -----
    m_settingsPanel = new SettingsPanel(ui->twSettingsCategories, this);
    
    // Connect settings buttons
    connect(ui->pbSaveSetting, &QPushButton::clicked, m_settingsPanel, &SettingsPanel::onSaveSettings);
    connect(ui->pbResetSettings, &QPushButton::clicked, m_settingsPanel, &SettingsPanel::onResetSettings);
    connect(ui->pbBackupSettings, &QPushButton::clicked, m_settingsPanel, &SettingsPanel::onBackupSettings);
    connect(ui->pbRestoreSettings, &QPushButton::clicked, m_settingsPanel, &SettingsPanel::onRestoreSettings);

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
    
    // Set Project page as default startup page
    SetDefaultPage(PAGE_PROJECT);

//    ui->tbHome->click();

    //-------- UX --------

    teSoftwareLog = ui->teLoggingBox;




    //------- Project Manager --------
    SoftwareProjectManager = new ProjectManager();
    SoftwareProjectManager->InitTabManager(ui->twProjectManager);
    SoftwareProjectManager->InitAddNewTab(ui->tabAddNewButton);
    SoftwareProjectManager->IsNewTabSlotOutside = true;

    SoftwareManager::GetInstance()->SoftwareProjectManager = SoftwareProjectManager;

    connect(SoftwareProjectManager, SIGNAL(NewTab_Signal(int)), SLOT(AddNewProjectAndRobot(int)));

    QString projectPrefix = "project";
    for (int i = 0; i < 10; i++)
    {
        QString projectName = projectPrefix + QString::number(i);

        VariableManager::instance().Prefix = projectName;

        if (VariableManager::instance().containsSubKey(projectName) == true)
        {
            RobotWindow* robotWindow = AddNewProjectAndRobot(i);
        }
        else
        {
            QString projectName = projectPrefix + QString::number(i - 1);

            VariableManager::instance().Prefix = projectName;
            break;
        }
    }    

    InitProjectUX();

    //------------- Init Widgets -----------
    // Expand only top level items for better performance
    ui->tvVariables->expandToDepth(1);

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

//    InitProjectToOperator();

//    on_pbApplyOperator_clicked();

    SetLoadingIconRun(false);

//    qDebug() << time.elapsed() - start;
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
        // Auto-save settings before closing
        if (m_settingsPanel) {
            m_settingsPanel->autoSaveSettings();
        }
        
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
    ui->tbSetting->setVisible(false);
    ui->tbHome->setVisible(false);
    ui->tbCommunity->setVisible(false);
    ui->tbDocument->setVisible(false);
    ui->tbMarket->setVisible(false);
    ui->tbAuthority->setVisible(false);
    ui->tbSaveProject->setVisible(true);
    ui->tbOpenProject->setVisible(false);

    // ----- Load custom UI ----
//    QSettings settings("customUI.ini", QSettings::IniFormat);
//    QString softwareName = settings.value("SoftwareName", "Delta X Software").toString();

//    softwareName = QString("%1 - %2").arg(softwareName).arg(DeltaXVersionManager->CurrentVersion);
//    this->setWindowTitle(softwareName);

//    QString systemName = settings.value("SystemName", "Delta Robot System").toString();
//    ui->leOperatorTitle->setText(systemName);
//    ui->lbOperatorTitile->setText(systemName);

//    LoadOperatorSettings();
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

    VariableManager::instance().scheduleSave(750);

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
            // Style parent/folder items
            child->setForeground(QColor(150, 255, 150)); // Light green for folders
            child->setFont(QFont("Consolas", 10, QFont::Bold));
            parent->appendRow(child);
        }
        parent = child;
    }
    bool found = false;
    for (int i = 0; i < parent->rowCount(); ++i) {
        if (parent->child(i)->text() == parts.last()) {
            // Update existing value with proper styling
            QStandardItem* valueItem = parent->child(i, 1);
            if (valueItem) {
                valueItem->setText(value.toString());
                valueItem->setForeground(QColor(255, 255, 180)); // Light yellow for values
                valueItem->setFont(QFont("Consolas", 10, QFont::Normal));
            }
            found = true;
            break;
        }
    }
    if (!found) {
        QStandardItem* keyItem = new QStandardItem(parts.last());
        QStandardItem* valueItem = new QStandardItem(value.toString());
        
        // Style the key item
        keyItem->setForeground(QColor(180, 180, 255)); // Light blue for keys
        keyItem->setFont(QFont("Consolas", 10, QFont::Bold));
        
        // Style the value item  
        valueItem->setForeground(QColor(255, 255, 180)); // Light yellow for values
        valueItem->setFont(QFont("Consolas", 10, QFont::Normal));
        
        parent->appendRow(QList<QStandardItem*>() << keyItem << valueItem);
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
    if (!index.isValid()) {
        return;
    }

    QStandardItem *item = VariableTreeModel.itemFromIndex(index);
    if (!item) {
        return;
    }

    QStandardItem *parentItem = item->parent();
    if (!parentItem) {
        return;
    }

    if (index.row() < 0 || index.row() >= parentItem->rowCount() || parentItem->columnCount() < 2) {
        return;
    }

    QStandardItem *keyItem = parentItem->child(index.row(), 0);
    if (!keyItem) {
        return;
    }

    QString key = keyItem->text();
    if (key.isEmpty()) {
        return;
    }

    // Lấy tên của các item cha của item hiện tại và gán lại thành mẫu như sau "item1.item2.item3"
    for (QStandardItem *parent = parentItem; parent != nullptr; parent = parent->parent()) {
        key = parent->text() + "." + key;
    }

    QStandardItem *valueItem = parentItem->child(index.row(), 1);
    if (!valueItem) {
        return;
    }

    QString value = valueItem->text();
    if (value.isEmpty()) {
        return;
    }

    ui->leUpdateKey->setText(key);
    ui->leUpdateValue->setText(value);
}


MainWindow::~MainWindow()
{
    // Auto-save settings before destroying
    if (m_settingsPanel) {
        m_settingsPanel->autoSaveSettings();
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

void MainWindow::SetDefaultPage(PageType pageType)
{
    QWidget* targetPage = nullptr;
    QAbstractButton* targetButton = nullptr;
    
    switch (pageType) {
        case PAGE_VARIABLE:
            targetPage = ui->pVariable;
            targetButton = ui->tbVariable;
            break;
        case PAGE_OPERATOR:
            targetPage = ui->pOperator;
            targetButton = ui->tbHome; // Note: tbHome shows Operator page
            break;
        case PAGE_HOME:
            // PAGE_HOME is not implemented in current UI
            break;
        case PAGE_MARKET:
            targetPage = ui->pMarket;
            targetButton = ui->tbMarket;
            break;
        case PAGE_DOCUMENT:
            targetPage = ui->pDocument;
            targetButton = ui->tbDocument;
            break;
        case PAGE_AUTHORITY:
            targetPage = ui->pAuthority;
            targetButton = ui->tbAuthority;
            break;
        case PAGE_COMMUNITY:
            targetPage = ui->pCommunity;
            targetButton = ui->tbCommunity;
            break;
        case PAGE_SETTING:
            targetPage = ui->pSetting;
            targetButton = ui->tbSetting;
            break;
        case PAGE_PROJECT:
            targetPage = ui->pProject;
            targetButton = ui->tbProject;
            break;
        default:
            targetPage = ui->pProject; // Default fallback
            targetButton = ui->tbProject;
            break;
    }
    
    if (targetPage) {
        ui->swPageStack->setCurrentWidget(targetPage);
    }
    
    if (targetButton) {
        // Clear all button styles first
        ui->tbHome->setStyleSheet("");
        ui->tbProject->setStyleSheet("");
        ui->tbVariable->setStyleSheet("");
        ui->tbSetting->setStyleSheet("");
        ui->tbMarket->setStyleSheet("");
        ui->tbDocument->setStyleSheet("");
        ui->tbCommunity->setStyleSheet("");
        ui->tbAuthority->setStyleSheet("");
        
        // Apply selected state to target button
        targetButton->setStyleSheet("background-color: rgb(24, 70, 139);");
    }
}

void MainWindow::InitVariableTreeView()
{
    // Set up headers for the tree view
    QStringList headers;
    headers << "Variable Key" << "Value";
    VariableTreeModel.setHorizontalHeaderLabels(headers);
    
    // Configure visual properties
    ui->tvVariables->setAlternatingRowColors(true);
    ui->tvVariables->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvVariables->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvVariables->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvVariables->setUniformRowHeights(true);
    ui->tvVariables->setSortingEnabled(false);
    
    // Set header properties
    ui->tvVariables->header()->setStretchLastSection(false);
    ui->tvVariables->header()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->tvVariables->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tvVariables->header()->setDefaultSectionSize(200);
    ui->tvVariables->header()->setMinimumSectionSize(100);
    
    // Style the tree view with improved appearance
    ui->tvVariables->setStyleSheet(
        "QTreeView {"
            "background-color: rgb(40, 40, 43);"
            "alternate-background-color: rgb(45, 45, 48);"
            "color: rgb(220, 220, 220);"
            "border: 1px solid rgb(60, 60, 63);"
            "gridline-color: rgb(60, 60, 63);"
            "selection-background-color: rgb(0, 122, 255);"
            "selection-color: white;"
            "font-family: 'Consolas', 'Courier New', monospace;"
            "font-size: 10pt;"
            "padding: 2px;"
        "}"
        "QTreeView::item {"
            "height: 22px;"
            "border: none;"
            "padding: 2px 4px;"
        "}"
        "QTreeView::item:hover {"
            "background-color: rgb(55, 55, 58);"
        "}"
        "QTreeView::item:selected {"
            "background-color: rgb(0, 122, 255);"
            "color: white;"
        "}"
        "QTreeView::branch {"
            "background: transparent;"
        "}"
        "QTreeView::branch:has-children:!has-siblings:closed,"
        "QTreeView::branch:closed:has-children:has-siblings {"
            "background: transparent;"
            "border: none;"
        "}"
        "QTreeView::branch:open:has-children:!has-siblings,"
        "QTreeView::branch:open:has-children:has-siblings {"
            "background: transparent;"
            "border: none;"
        "}"
        "QTreeView::branch:has-siblings:!adjoins-item {"
            "background: transparent;"
            "border: none;"
        "}"
        "QTreeView::branch:has-siblings:adjoins-item {"
            "background: transparent;"
            "border: none;"
        "}"
        "QTreeView::branch:!has-children:!has-siblings:adjoins-item {"
            "background: transparent;"
            "border: none;"
        "}"
        "QHeaderView::section {"
            "background-color: rgb(50, 50, 53);"
            "color: rgb(220, 220, 220);"
            "border: 1px solid rgb(60, 60, 63);"
            "padding: 4px 8px;"
            "font-weight: bold;"
            "font-size: 10pt;"
        "}"
        "QHeaderView::section:hover {"
            "background-color: rgb(60, 60, 63);"
        "}"
    );
    
    // Set default column widths
    ui->tvVariables->setColumnWidth(0, 300);  // Key column
    ui->tvVariables->setColumnWidth(1, 200);  // Value column
    
    // Enable grid lines for better visibility
    ui->tvVariables->setRootIsDecorated(true);
    ui->tvVariables->setIndentation(20);
    
    // Add tooltips to headers
    VariableTreeModel.setHeaderData(0, Qt::Horizontal, "Variable keys in hierarchical structure", Qt::ToolTipRole);
    VariableTreeModel.setHeaderData(1, Qt::Horizontal, "Current values of the variables", Qt::ToolTipRole);
}
