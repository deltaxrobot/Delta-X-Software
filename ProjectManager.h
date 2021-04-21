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

class ProjectManager : public QWidget
{
    Q_OBJECT
public:
    ProjectManager(QWidget* parent = NULL);
    void InitTabManager(QTabWidget* tabWidget);
    void InitAddNewTab(QWidget* addNewTab);
    void AddNewTab(QWidget* newTab = NULL, QStackedWidget* stack = NULL);
    void AddNewTab(QStackedWidget* stack);
    QString GetProjectName(int index);
    QString GetProjectName(QWidget* widget);

    QStackedWidget *SubProject;

    bool IsNewTabSlotOutside = false;

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
