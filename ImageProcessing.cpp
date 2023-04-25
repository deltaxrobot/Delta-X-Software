#include "ImageProcessing.h"


ImageProcessing::ImageProcessing()
{

}

ImageProcessing::~ImageProcessing()
{
    foreach(TaskNode* node, taskNodeList.values())
    {
        delete node;
    }
}

void ImageProcessing::MoveToThread(QThread *thread)
{
    moveToThread(thread);

    foreach(TaskNode* taskNode, taskNodeList)
    {
        taskNode->moveToThread(thread);
    }
}

TaskNode *ImageProcessing::CreatTaskNode(QString name, int type, QString previousTasks)
{
    TaskNode* taskNode = new TaskNode(name, type);
    taskNode->ProjectName = ProjectName;
    taskNode->moveToThread(thread());
    taskNodeList.insert(name, taskNode);

    if (previousTasks != "")
    {
        QStringList previousTaskList = previousTasks.split("|");
        foreach(QString previousTask, previousTaskList)
        {
            taskNodeList.value(previousTask)->SetNextNode(taskNode);
        }
    }

    return taskNode;
}

TaskNode *ImageProcessing::GetNode(QString name)
{
    return taskNodeList.value(name);
}
