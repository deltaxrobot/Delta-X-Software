#ifndef SOFTWAREMANAGER_H
#define SOFTWAREMANAGER_H

#include <QList>
#include "ProjectManager.h"

class ProjectManager;

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

    QObject* SoftwarePointer = NULL;

    ProjectManager* SoftwareProjectManager;

    QString SoftwarePath = "";
};

#endif // SOFTWAREMANAGER_H
