#include "robotmanager.h"

RobotManager::RobotManager(QObject *parent) : QObject(parent)
{

}

RobotManager *RobotManager::getInstance()
{
    if (instance == NULL)
    {
        instance = new RobotManager();
    }

    return instance;
}
