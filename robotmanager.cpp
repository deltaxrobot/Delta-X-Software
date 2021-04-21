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
