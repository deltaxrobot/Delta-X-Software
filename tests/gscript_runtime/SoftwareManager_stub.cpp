#include "SoftwareManager.h"

SoftwareManager* SoftwareManager::GetInstance()
{
    static SoftwareManager instance;
    return &instance;
}
