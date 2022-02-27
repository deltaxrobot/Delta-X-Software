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
