#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <QObject>
#include <QList>
#include "Robot.h"
#include "RobotWindow.h"
#include <QAction>
#include <QTabWidget>

namespace Ui {
    class RobotWindow;
}

class RobotManager : public QObject
{
    Q_OBJECT
public:
    explicit RobotManager(QObject *parent = nullptr);

    void AddRobotWindow(RobotWindow* robotWindow);
    RobotWindow* CreatNewRobotWindow();
    void SetMainStackedWidgetAndPages(QStackedWidget* mainStack, QWidget* mainPage, QWidget* fullDisplayPage, QLayout* fullDisplayLayout);
    void SetSubStackedWidget(QStackedWidget* subStackedWidget);

    void LoadSettings(QSettings* setting);
    void SaveSettings(QSettings* setting);

    void Run();
    void Run(QStringList robotProgramList);
    void Stop();

    QStringList GetRobotNames();
    void SetName(QString name);
    RobotWindow *GetRobot(QString name);

    QList<RobotWindow*> RobotWindows;
    int ID = 0;
    QString Name;

    QStackedWidget* MainWindowStackedWidget;
    QWidget* MainWindowPage;
    QWidget* FullDisplayPage;
    QLayout* FullDisplayLayout;

    QStackedWidget* SubWindowStackedWidget;    

    QSettings* Setting;

    QTabWidget* twProjectManager;

};

#endif // ROBOTMANAGER_H
