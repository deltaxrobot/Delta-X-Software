#include "robotmanager.h"
#include "ui_RobotWindow.h"

RobotManager::RobotManager(QObject *parent) : QObject(parent)
{
    Robots = new QList<Robot*>();
}

void RobotManager::AddRobotWindow(RobotWindow* robotWindow)
{
    robotWindow->RobotManagerPointer = this;
    this->Robots->append(&(robotWindow->RobotParamter));
}

RobotWindow* RobotManager::CreatNewRobotWindow()
{
    //ElapsedTimer.start();
    RobotWindow* robotWindow = new RobotWindow();
    robotWindow->RobotManagerPointer = this;

    robotWindow->SetMainStackedWidgetAndPages(MainWindowStackedWidget, MainWindowPage, FullDisplayPage, FullDisplayLayout);
    robotWindow->SetSubStackedWidget(SubWindowStackedWidget);

    RobotWindows.append(robotWindow);

    int robotID = RobotWindows.size() - 1;
    QString robotName = QString("robot ") + QString::number(robotID + 1);

    robotWindow->SetName(robotName);
    robotWindow->SetID(robotID);

    robotWindow->InitVariables();
    robotWindow->InitEvents();

    //----- Add new robot to menu ------
    for (int i = 0; i < RobotWindows.size() - 1; i++)
    {
        QAction *actionNewDelta_X;
        actionNewDelta_X = new QAction(robotWindow);

        actionNewDelta_X->setCheckable(true);
        actionNewDelta_X->setChecked(true);
        actionNewDelta_X->setText(robotName);
        RobotWindows.at(i)->ui->menuExecute->addAction(actionNewDelta_X);
    }

    //----- Creat new tab widget in other robot window -------
    for (int i = 0; i < RobotWindows.size() - 1; i++)
    {
        RobotWindows.at(i)->ui->twDeltaManager->setTabText(robotID, robotName);
        QWidget *newDeltaTab = new QWidget();
        RobotWindows.at(i)->ui->twDeltaManager->addTab(newDeltaTab, QString("+"));
    }

    robotWindow->InitTabs();

    SubWindowStackedWidget->addWidget(robotWindow);
    SubWindowStackedWidget->setCurrentWidget(robotWindow);

    robotWindow->ui->twDeltaManager->setCurrentIndex(robotID);

    //robotWindow->ConnectDeltaRobot();

    //qDebug() << ElapsedTimer.elapsed();

    return robotWindow;
}

QStringList RobotManager::GetRobotNames()
{
    QStringList nameList;

    for(int i = 0; i < RobotWindows.count(); i++)
    {
        nameList.append(RobotWindows.at(i)->Name);
    }

    return nameList;
}

void RobotManager::SetName(QString name)
{
    Name = name;
    twProjectManager->setTabText(ID, name);
}

RobotWindow *RobotManager::GetRobot(QString name)
{
    foreach(RobotWindow* robotWindow, RobotWindows)
    {
        if (robotWindow->Name.replace(" ", "") == name.replace(" ", ""))
            return robotWindow;
    }

    return NULL;
}

void RobotManager::SetMainStackedWidgetAndPages(QStackedWidget *mainStack, QWidget *mainPage, QWidget *fullDisplayPage, QLayout *fullDisplayLayout)
{
    this->MainWindowStackedWidget = mainStack;
    this->MainWindowPage = mainPage;
    this->FullDisplayPage = fullDisplayPage;
    this->FullDisplayLayout = fullDisplayLayout;
}

void RobotManager::SetSubStackedWidget(QStackedWidget *subStackedWidget)
{
    this->SubWindowStackedWidget = subStackedWidget;
}

void RobotManager::LoadSettings(QSettings *setting)
{
    setting->beginGroup("Project");

    Setting = setting;

    SetName(setting->value("Name", "project 1").toString());

    int robotNumber = setting->value("RobotNumber", 1).toInt();

    for (int i = 0; i < robotNumber; i++)
    {
        setting->beginGroup(QString("Robot%1").arg(i));

        RobotWindow* robotWindow = CreatNewRobotWindow();
        robotWindow->SetName(setting->value("Name", "robot " + QString::number(i + 1)).toString());

        robotWindow->LoadSettings(setting);

        setting->endGroup();
    }

    setting->endGroup();
}

void RobotManager::SaveSettings(QSettings *setting)
{
    setting->beginGroup("Project");
    setting->setValue("Name", Name);
    setting->setValue("RobotNumber", RobotWindows.size());

    for(int i = 0; i < RobotWindows.size(); i++)
    {
        setting->beginGroup(QString("Robot%1").arg(i));

        setting->setValue(QString("Name").arg(i), RobotWindows[i]->Name);

        RobotWindows[i]->SaveSettings(setting);        

        setting->endGroup();
    }
    setting->endGroup();
}

void RobotManager::Run()
{
    foreach(RobotWindow* robotWindow, RobotWindows)
    {

        // ---- Camera

        // ---- Gcode Program

        if (!robotWindow->Run())
        {
            QMessageBox::information(NULL, QString("Cannot connect %").arg(robotWindow->Name), "Unable to open the COM port");
        }
    }
}

void RobotManager::Run(QStringList robotProgramList)
{
    foreach(RobotWindow* robotWindow, RobotWindows)
    {
        foreach(QString robotGcode, robotProgramList)
        {
            QStringList paras = robotGcode.split(':');
            if (robotWindow->Name == paras[0])
            {
                robotWindow->DeltaGcodeManager->SelectProgram(paras[1]);
                robotWindow->ExecuteProgram();
            }
        }
    }
}

void RobotManager::Stop()
{
    foreach(RobotWindow* robotWindow, RobotWindows)
    {
        robotWindow->ClickExecuteButton(false);
    }
}
