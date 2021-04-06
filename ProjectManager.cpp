#include "ProjectManager.h"

ProjectManager::ProjectManager(QWidget* parent) : QWidget(parent)
{
    this->setStyleSheet("QPushButton{min-width:60px;min-height:20px;}");
}

void ProjectManager::InitTabManager(QTabWidget *tabWidget)
{
    twProjectManager = tabWidget;

    connect(twProjectManager, SIGNAL(tabBarClicked(int)), this, SLOT(ChangeProjectTab(int)));
    connect(twProjectManager, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(ChangeProjectName(int)));
    connect(twProjectManager, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseProject(int)));
}

void ProjectManager::InitDefaultTab(QWidget *defaultTab)
{
    tabDefaultProject = defaultTab;
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

void ProjectManager::InitDefaultProject(QWidget *defaultProject)
{
    if (tabDefaultProject != NULL)
    {
        twProjectManager->removeTab(twProjectManager->indexOf(tabDefaultProject));
    }

    twProjectManager->insertTab(0, defaultProject, "project 1");
    twProjectManager->setCurrentWidget(defaultProject);
}

void ProjectManager::ChangeProjectTab(int index)
{
    if (twProjectManager->widget(index) == tabAddNewButton)
    {
        QWidget* newTab = new QWidget();
        twProjectManager->insertTab(index, newTab, "new Project");
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
