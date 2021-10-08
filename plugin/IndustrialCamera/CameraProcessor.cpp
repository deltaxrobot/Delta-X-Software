#include "CameraProcessor.h"

CameraProcessor::CameraProcessor(QObject *parent) : QObject(parent)
{

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


    Height = IndustryCamera.Height();
    Width = IndustryCamera.Width();
    openCvImage = new cv::Mat(Height, Width, CV_8UC3, imageData);

    emit CapturedImage(*openCvImage);

    if (cameraWidget != NULL)
    {
        UpdateLabelImage(*openCvImage, cameraWidget);
    }
}

void CameraProcessor::Loop()
{
    while (IsLoopRunning)
    {
//        if (IndustryCamera.IsOpen() == false)
//            continue;

        if (CaptureSignal == true)
        {
            qDebug() << "Capture";
            ShotImage();
            CaptureSignal = false;
        }
    }
}
