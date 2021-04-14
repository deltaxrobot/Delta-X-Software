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
    }
    else
    {

    }
}
