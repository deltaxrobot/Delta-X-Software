       #ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QTabBar>
#include <QInputDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QSettings>
#include "RobotWindow.h"

class RobotWindow;

class ProjectManager : public QWidget
{
    Q_OBJECT
public:
    ProjectManager(QWidget* parent = NULL);
    void InitTabManager(QTabWidget* tabWidget);
    void InitAddNewTab(QWidget* addNewTab);
    void AddNewTab(QWidget* newTab = NULL, QStackedWidget* stack = NULL);
    void AddNewTab(QStackedWidget* stack, int id, QString name);
    void RemoveTab(int tabIndex);
    QString GetProjectName(int index);
    QString GetProjectName(QWidget* widget);
    RobotWindow *GetProject(QString name);

    QStackedWidget *SubProject;

    bool IsNewTabSlotOutside = false;


    RobotWindow* CurrentRobotWindow;
    QList<RobotWindow*> RobotWindows;

public slots:
    void ChangeProjectTab(int index);
    void ChangeProjectName(int tabIndex);
    void CloseProject(int tabIndex);

    signals:
    void NewTab_Signal(int index);

private:
    QTabWidget* twProjectManager;
    QWidget* tabAddNewButton;
};

#endif // PROJECTMANAGER_H
