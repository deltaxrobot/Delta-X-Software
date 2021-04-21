#include "SoftwareManager.h"

SoftwareManager* SoftwareManager::singleton_= nullptr;;

SoftwareManager *SoftwareManager::GetInstance()
{
    if(singleton_==nullptr){
        singleton_ = new SoftwareManager();
    }
    return singleton_;
}
