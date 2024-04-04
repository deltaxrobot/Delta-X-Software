#include "ProjectManager.h"

ProjectManager::ProjectManager(QWidget* parent) : QWidget(parent)
{
    this->setStyleSheet("QPushButton{min-width:60px;min-height:20px;}");

    SubProject = new QStackedWidget();
}

void ProjectManager::InitTabManager(QTabWidget *tabWidget)
{
    twProjectManager = tabWidget;

    connect(twProjectManager, SIGNAL(tabBarClicked(int)), this, SLOT(ChangeProjectTab(int)));
    connect(twProjectManager, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(ChangeProjectName(int)));
    connect(twProjectManager, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseProject(int)));
}

void ProjectManager::InitAddNewTab(QWidget *addNewTab)
{
    tabAddNewButton = addNewTab;

    if (twProjectManager != NULL)
    {
        int index = twProjectManager->indexOf(addNewTab);
        QTabBar* tb = twProjectManager->tabBar();
        tb->tabButton(index, QTabBar::RightSide)->deleteLater();
        tb->setTabButton(index, QTabBar::RightSide, 0);
    }
}

void ProjectManager::AddNewTab(QWidget* newTab, QStackedWidget* stack)
{
    if (newTab == NULL)
    {
        newTab = new QWidget();
    }

    int tabID = twProjectManager->count() - 1;

    if (stack != NULL)
    {
        twProjectManager->insertTab(tabID, stack, QString("project " + QString::number(tabID)));
        twProjectManager->setCurrentWidget(stack);

        stack->addWidget(newTab);
    }
    else
    {
        twProjectManager->insertTab(tabID, newTab, QString("project " + QString::number(tabID)));
    }
}

void ProjectManager::AddNewTab(QStackedWidget *stack,  int id, QString name = "")
{
    if (name == "")
    {
        name = QString("project " + QString::number(id));
    }

    twProjectManager->insertTab(id, stack, name);
    twProjectManager->setCurrentWidget(stack);
}

void ProjectManager::RemoveTab(int tabIndex)
{

}

QString ProjectManager::GetProjectName(int index)
{
    return twProjectManager->tabText(index);
}

QString ProjectManager::GetProjectName(QWidget *widget)
{
    return GetProjectName(twProjectManager->indexOf(widget));
}

RobotWindow *ProjectManager::GetProject(QString name)
{
    foreach(RobotWindow* robot, RobotWindows)
    {
        if (robot->ProjectName == name)
            return robot;
    }

    return NULL;
}

void ProjectManager::ChangeProjectTab(int index)
{
    if (twProjectManager->widget(index) == tabAddNewButton)
    {
        if (IsNewTabSlotOutside == false)
        {
            AddNewTab();
        }

        NewTab_Signal(index);
    }
    else
    {
        CurrentRobotWindow = RobotWindows.at(index);
    }
}

void ProjectManager::ChangeProjectName(int tabIndex)
{
    QString oldTabName = twProjectManager->tabText(tabIndex);

    bool ok;
    QString newTabName = QInputDialog::getText(this, tr("Change project name"), tr("New name:"), QLineEdit::Normal, oldTabName, &ok);

    if (ok && !newTabName.isEmpty())
    {
        twProjectManager->setTabText(tabIndex, newTabName);
//        RobotManagers[tabIndex]->Name = newTabName;
    }
}

void ProjectManager::CloseProject(int tabIndex)
{
    QString projectName = twProjectManager->tabText(tabIndex);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, projectName, "Do you want to close this project?",
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        twProjectManager->removeTab(tabIndex);

        VariableManager::instance().removeVar(QString("project") + QString::number(tabIndex));
        delete SoftwareManager::GetInstance()->SoftwareProjectManager->RobotWindows.at(tabIndex);

        SoftwareManager::GetInstance()->SoftwareProjectManager->RobotWindows.removeAt(tabIndex);
    }
    else
    {
        return;
    }

    if (tabIndex > 0)
    {
        twProjectManager->setCurrentIndex(tabIndex - 1);
    }
}
