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

void ImageProcessing::GotVisibleObjects(QList<Object> objects)
{
    objectInfos.clear();
    for(Object visibleObject : objects)
    {
        QVector3D position(visibleObject.X.Real, visibleObject.Y.Real, 0);
        objectInfos.append(ObjectInfo(-1, position, visibleObject.Width.Real, visibleObject.Length.Real, visibleObject.Angle.Real));
    }

    emit mappedDetectedObjects(objectInfos, ObjectsName);
}
