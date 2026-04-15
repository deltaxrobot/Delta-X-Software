#ifndef SOFTWAREMANAGER_H
#define SOFTWAREMANAGER_H

#include <QList>
#include "ProjectManager.h"

class ProjectManager;
class MainWindow;

class SoftwareManager
{

protected:
    SoftwareManager()
    {
    }

    static SoftwareManager* singleton_;

public:
    SoftwareManager(SoftwareManager &other) = delete;
    void operator=(const SoftwareManager &) = delete;

    static SoftwareManager *GetInstance();

    MainWindow* SoftwarePointer = NULL;

    ProjectManager* SoftwareProjectManager;

    QString SoftwarePath = "";
    int RunningScriptThreadNumber = 0;
};

#endif // SOFTWAREMANAGER_H
