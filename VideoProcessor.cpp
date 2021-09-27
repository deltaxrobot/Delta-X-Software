#include "VideoProcessor.h"

VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent)
{

}

void VideoProcessor::getCamera(cv::VideoCapture *cam)
{
    camera = cam;
}

void VideoProcessor::putInfoOnImage(cv::Mat& mat, QList<cv::RotatedRect> objects, cv::Scalar color)
{

}

void VideoProcessor::startVideo()
{
    stopped = false;

    while(!stopped)
    {
        if (camera == NULL)
            continue;

        if (camera->isOpened() == false)
        {
            emit cameraClosed();
            continue;
        }

        cv::Mat inFrame;

        if (!camera->read(inFrame))
        {
            emit readImageFailed();
        }

        if(inFrame.empty())
            continue;

        emit captureImage(inFrame);
    }
}

void VideoProcessor::stopVideo()
{
    stopped = true;
    camera = NULL;
}
