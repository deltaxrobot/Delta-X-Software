#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <QObject>
#include <QList>
#include "Robot.h"
#include "RobotWindow.h"
#include <QAction>

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

    QStringList GetRobotNames();

    QList<Robot*> *Robots;
    QList<RobotWindow*> RobotWindows;
    int ProjectID = 0;

    QStackedWidget* MainWindowStackedWidget;
    QWidget* MainWindowPage;
    QWidget* FullDisplayPage;
    QLayout* FullDisplayLayout;

    QStackedWidget* SubWindowStackedWidget;

};

#endif // ROBOTMANAGER_H
