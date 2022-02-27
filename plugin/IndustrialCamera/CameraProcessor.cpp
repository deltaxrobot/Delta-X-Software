#include "CameraProcessor.h"

CameraProcessor::CameraProcessor(QObject *parent) : QObject(parent)
{
}

void CameraProcessor::run()
{
    ShotImage();
}

void CameraProcessor::UpdateLabelImage(cv::Mat mat, QLabel *label)
{
    QImage img = ImageTool::cvMatToQImage(mat);
    qDebug() << "Convert time: " << elapseTime.elapsed();
    int width3 = label->parentWidget()->parentWidget()->parentWidget()->geometry().width();

    int ratio = (float)width3/mat.cols * 100;

//    if (lbRatio != NULL)
//    {
//        lbRatio->setText(QString::number(ratio) + "%");
//    }
    emit UpdatedRatio(QString::number(ratio) + "%");
    emit FinishReadingImage(QPixmap::fromImage(img).scaledToWidth(width3));
//    label->setPixmap(QPixmap::fromImage(img).scaledToWidth(width3));
}

void CameraProcessor::ShotImage()
{
    emit StartedCapture();
    QMutex mutex;
    mutex.lock();
    qDebug() << "Shot start time: " << elapseTime.restart();
    uint8_t* imageData = IndustryCamera->Capture();
    qDebug() << "Capture time: " << elapseTime.elapsed();
//    if (openCvImage != NULL)
//        delete openCvImage;

    if (imageData == NULL)
        return;

    Height = IndustryCamera->Height();
    Width = IndustryCamera->Width();
//        openCvImage = new cv::Mat(Height, Width, CV_8UC3, imageData);
    //cv::Mat mat(Height, Width, CV_8UC3, imageData);
    cv::Mat openCvImage = cv::Mat(Height, Width, CV_8UC3, imageData);
    qDebug() << "Mat time: " << elapseTime.elapsed();
    if (MatWidth != - 1)
    {
        MatHeight = Height * ((float)MatWidth/ Width);
        resize(openCvImage, openCvImage, cv::Size(MatWidth, MatHeight), cv::INTER_NEAREST);
        qDebug() << "Resize time: " << elapseTime.elapsed();
    }

    emit CapturedImage(openCvImage);

    qDebug() << "Emit time: " << elapseTime.elapsed();
    if (cameraWidget != NULL)
    {
        UpdateLabelImage(openCvImage, cameraWidget);
        qDebug() << "Display time: " << elapseTime.elapsed();
    }

    qDebug() << "Shot time: " << elapseTime.elapsed();
    mutex.unlock();

    emit FinishJob(true);
}
