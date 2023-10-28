#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent)
{
    WebcamInstance = new cv::VideoCapture();
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

    if (Source == "Webcam")
    {
        CaptureWebcam();
    }
    if (Source == "Images")
    {
        emit GotImage(CaptureImage);
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
