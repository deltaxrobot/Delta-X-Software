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

TaskNode *ImageProcessing::CreatTaskNode(QString name, int type, QString previousTasks)
{
    TaskNode* taskNode = new TaskNode(name, type);

    QThread* taskThread = new QThread;

    taskNode->moveToThread(taskThread);

    connect(taskThread, &QThread::finished, taskNode, &QObject::deleteLater);
    connect(taskThread, &QThread::finished, taskThread, &QObject::deleteLater);

    taskThread->start();

    taskNode->ProjectName = ProjectName;
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

void ImageProcessing::GotVisibleObjects(QVector<Object> objects)
{
    objectInfos.clear();
    for(const Object& visibleObject : objects)
    {
        QVector3D position(visibleObject.X.Real, visibleObject.Y.Real, 0);
        objectInfos.append(ObjectInfo(-1, visibleObject.Type.toInt(), position, visibleObject.Width.Real, visibleObject.Length.Real, visibleObject.Angle.Real));
    }

    emit mappedDetectedObjects(objectInfos, ObjectsName);
}

void ImageProcessing::GotImage(cv::Mat image)
{
    cv::Mat mat = image.clone();
//    qDebug() << "Image Thread id: " << QThread::currentThreadId();

    qDebug() << "In thread start: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

    if (resizeValue != cv::Size(0, 0))
    {
        resizeValue.height = resizeValue.width * ((float)mat.rows / mat.cols);

        cv::resize(mat, mat, resizeValue, cv::INTER_NEAREST);
    }

    cv::warpPerspective(mat, mat, perspectiveMatrix, mat.size(), cv::INTER_NEAREST);


    QThread::sleep(1);
    qDebug() << "In thread end: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
}

void ImageProcessing::GotResizeValue(cv::Size size)
{
    resizeValue = size;
}

void ImageProcessing::GotPerspectiveMatrix(cv::Mat matrix)
{
    perspectiveMatrix = matrix.clone();
}
