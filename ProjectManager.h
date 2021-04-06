       #ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QTabBar>
#include <QInputDialog>
#include <QMessageBox>
#include <QHBoxLayout>

class ProjectManager : public QWidget
{
    Q_OBJECT
public:
    ProjectManager(QWidget* parent);
    void InitTabManager(QTabWidget* tabWidget);
    void InitDefaultTab(QWidget* defaultTab);
    void InitAddNewTab(QWidget* addNewTab);
    void InitDefaultProject(QWidget* defaultProject);

public slots:
    void ChangeProjectTab(int index);
    void ChangeProjectName(int tabIndex);
    void CloseProject(int tabIndex);

private:
    QTabWidget* twProjectManager;
    QWidget* tabDefaultProject;
    QWidget* tabAddNewButton;
};

#endif // PROJECTMANAGER_H
