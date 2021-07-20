#ifndef SOFTWAREMANAGER_H
#define SOFTWAREMANAGER_H

#include "VariableManager.h"
#include "robotmanager.h"
#include <QList>
#include "ProjectManager.h"

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

    VariableManager* ProgramVariableManager;
    //QList<RobotManager*>* RobotManagers;
    ProjectManager* RobotProjectManager;
};

#endif // SOFTWAREMANAGER_H