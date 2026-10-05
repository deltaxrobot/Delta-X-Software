#ifndef SOFTWAREMANAGER_H
#define SOFTWAREMANAGER_H

#include <QList>
#include <atomic>
#include "ProjectManager.h"

class ProjectManager;
class MainWindow;

class SoftwareManager
{

protected:
    SoftwareManager()
    {
    }

public:
    SoftwareManager(SoftwareManager &other) = delete;
    void operator=(const SoftwareManager &) = delete;

    static SoftwareManager *GetInstance();
    void ScriptStarted()
    {
        runningScriptThreadNumber.fetch_add(1, std::memory_order_relaxed);
    }
    void ScriptFinished()
    {
        int current = runningScriptThreadNumber.load(std::memory_order_relaxed);
        while (current > 0 &&
               !runningScriptThreadNumber.compare_exchange_weak(
                   current, current - 1, std::memory_order_relaxed)) {
        }
    }
    int RunningScriptCount() const
    {
        return runningScriptThreadNumber.load(std::memory_order_relaxed);
    }

    MainWindow* SoftwarePointer = NULL;

    ProjectManager* SoftwareProjectManager = nullptr;

    QString SoftwarePath = "";
private:
    std::atomic_int runningScriptThreadNumber{0};
};

#endif // SOFTWAREMANAGER_H
