#include "ImageProcessing.h"


void ImageProcessing::CaptureCamera(cv::VideoCapture *Camera)
{
    if (!Camera->isOpened())
        return;

    cv::Mat captureImage;

    if (!Camera->read(captureImage))
    {
//            emit StopCamera();
    }
    else
    {
//            emit capturedImage(captureImage.clone());
    }
}

void ImageProcessing::GetImage(cv::Mat mat)
{
    TaskList[TaskOrder]->OutputMat = mat.clone();

    FindNextTask();
}

void ImageProcessing::ResizeImage(cv::Mat mat)
{

}

void ImageProcessing::ExecuteTaskFlow()
{
    for (int i = 0; i < TaskList.count(); i++)
    {

    }
}

void ImageProcessing::FindNextTask()
{
    TaskOrder++;

    Task* task = TaskList[TaskOrder];

    if (task->getName() == "ResizeImage")
    {
        ResizeImage(TaskList[TaskOrder - 1]->OutputMat);
    }
    if (task->getName() == "TransformPerspective")
    {

    }
    if (task->getName() == "HSVFilter")
    {

    }
    if (task->getName() == "ThresholdFilter")
    {

    }
    if (task->getName() == "InvertColor")
    {

    }
    if (task->getName() == "DetectBlobs")
    {

    }
    if (task->getName() == "DetectCircles")
    {

    }
    if (task->getName() == "SendImageToOtherProcess")
    {

    }
    if (task->getName() == "ReceiveObjectInfoFromOtherProcess")
    {

    }
    if (task->getName() == "MapImagePositionToRealPosition")
    {

    }
    if (task->getName() == "DisplayObjectOnImage")
    {

    }
    if (task->getName() == "ReadConveyorAndUpdateToObject")
    {

    }
}
