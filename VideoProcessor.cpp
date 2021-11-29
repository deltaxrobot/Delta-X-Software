#include "VideoProcessor.h"

VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent)
{
    Timer = new QTimer(NULL);
    Timer->connect(Timer, SIGNAL(timeout()), this, SLOT(TimerFunction()));
    Timer->start(10);
}

void VideoProcessor::getCamera(cv::VideoCapture *cam)
{
    camera = cam;
}

void VideoProcessor::getCamera(cv::VideoCapture *cam, int id, QLineEdit* w, QLineEdit* h)
{
    emit startingOpenCamera();
    camera = cam;
    camera->open(id);
    camera->set(cv::CAP_PROP_FRAME_WIDTH, w->text().toInt());
    camera->set(cv::CAP_PROP_FRAME_HEIGHT, h->text().toInt());

    w->setText(QString::number((int)camera->get(cv::CAP_PROP_FRAME_WIDTH)));
    h->setText(QString::number((int)camera->get(cv::CAP_PROP_FRAME_HEIGHT)));

    emit finishingOpenCamera();
}

void VideoProcessor::putInfoOnImage(cv::Mat& mat, QList<cv::RotatedRect> objects, cv::Scalar color)
{

}

void VideoProcessor::startVideo()
{
    return;
    while(!loopRunning)
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
    camera = NULL;
}

void VideoProcessor::CloseLoop()
{
    loopRunning = true;
}

void VideoProcessor::TimerFunction()
{
    try
    {
        if (!loopRunning)
        {
            if (camera == NULL)
                return;

            if (camera->isOpened() == false)
            {
                emit cameraClosed();
                return;
            }

            cv::Mat inFrame;

            if (!camera->read(inFrame))
            {
                emit readImageFailed();
            }

            if(inFrame.empty())
                return;

            emit captureImage(inFrame);
        }
    }  catch (...)
    {

    }
}
