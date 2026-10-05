#include "SoftwareManager.h"
#include "MainWindow.h"

SoftwareManager *SoftwareManager::GetInstance()
{
    static SoftwareManager instance;
    return &instance;
}
