#include "CameraProcessor.h"

CameraProcessor::CameraProcessor(QObject *parent) : QObject(parent)
{
    Timer = new QTimer(NULL);
    Timer->connect(Timer, SIGNAL(timeout()), this, SLOT(TimerFunction()));
    Timer->start(10);
}

void CameraProcessor::UpdateLabelImage(cv::Mat mat, QLabel *label)
{
    QImage img = ImageTool::cvMatToQImage(mat);
    int width3 = label->parentWidget()->parentWidget()->parentWidget()->geometry().width();

    int ratio = (float)width3/mat.cols * 100;

    if (lbRatio != NULL)
    {
        lbRatio->setText(QString::number(ratio) + "%");
    }

    label->setPixmap(QPixmap::fromImage(img).scaledToWidth(width3));

}



void CameraProcessor::ShotImage()
{
    uint8_t* imageData = IndustryCamera.Capture();
    if (openCvImage != NULL)
        delete openCvImage;

    if (imageData == NULL)
        return;

    try
    {
        Height = IndustryCamera.Height();
        Width = IndustryCamera.Width();
        openCvImage = new cv::Mat(Height, Width, CV_8UC3, imageData);
        //cv::Mat mat(Height, Width, CV_8UC3, imageData);

        cv::Mat mat;
        MatHeight = Height * ((float)MatWidth/ Width);
        resize(*openCvImage, mat, cv::Size(MatWidth, MatHeight), cv::INTER_LINEAR);

        emit CapturedImage(mat);

        if (cameraWidget != NULL)
        {
            UpdateLabelImage(mat, cameraWidget);
        }
    }  catch (...)
    {

    }
}

void CameraProcessor::Loop()
{
    return;
    while (IsLoopRunning)
    {
//        if (IndustryCamera.IsOpen() == false)
//            continue;

        if (CaptureSignal == true)
        {
            //qDebug() << "Capture";
            ShotImage();
            CaptureSignal = false;
        }
    }
}

void CameraProcessor::TimerFunction()
{
    if (IsLoopRunning)
    {
        if (CaptureSignal == true)
        {
            //qDebug() << "Capture";
            ShotImage();
            CaptureSignal = false;
        }
    }
}
