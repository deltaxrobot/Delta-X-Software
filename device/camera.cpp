#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent)
{
    WebcamInstance = new cv::VideoCapture();
}

void Camera::OpenCamera(int id)
{
    if (WebcamInstance->open(id) == true)
    {
        WebcamInstance->set(cv::CAP_PROP_FRAME_WIDTH, Width);
        WebcamInstance->set(cv::CAP_PROP_FRAME_HEIGHT, Height);

        Width = WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH);
        Height = WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT);

        emit connectedResult(true);
    }
    else
    {
        emit connectedResult(false);
    }
}

void Camera::GetImageFromExternal(cv::Mat mat)
{
    if (Source != "Industrial Camera")
        return;

    CaptureImage.release();
    CaptureImage = mat;

    emit GotImage(CaptureImage);
}

void Camera::GeneralCapture()
{
    emit StartedCapture(trackingThreadId);
//    qDebug() << "Capture: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

    if (Source == "Webcam")
    {
        CaptureWebcam();
    }
    if (Source == "Images")
    {
        if (CaptureImages.count() > 0)
        {
            CaptureImage = CaptureImages.at(FrameID);
            FrameID++;
            if (CaptureImages.count() <= FrameID)
                FrameID = 0;

            emit GotImage(CaptureImage);
        }
    }
    else if (Source == "Industrial Camera")
    {
        emit RequestCapture();
    }
}

void Camera::CaptureAndDetect()
{
    GeneralCapture();
}

void Camera::SetTracking(int id)
{
    trackingThreadId = id;
}

void Camera::CaptureWebcam()
{
    if (WebcamInstance == NULL)
        return;

    if (WebcamInstance->isOpened() == false)
    {
        emit StopCameraRequest();
        return;
    }

    if (WebcamInstance->read(CaptureImage))
    {
        emit GotImage(CaptureImage);
    }
}
