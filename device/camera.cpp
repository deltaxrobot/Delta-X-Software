#include "camera.h"
#include <vector>

Camera::Camera(QObject *parent) : QObject(parent)
{
    WebcamInstance = new cv::VideoCapture();
}

void Camera::OpenCamera(int id)
{
    if (WebcamInstance->open(id) == true)
    {
        // Get maximum resolution supported by the camera
        cv::Size maxRes = GetMaxResolution(WebcamInstance);
        
        // Set maximum resolution
        WebcamInstance->set(cv::CAP_PROP_FRAME_WIDTH, maxRes.width);
        WebcamInstance->set(cv::CAP_PROP_FRAME_HEIGHT, maxRes.height);

        // Get actual resolution after setting
        Width = WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH);
        Height = WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT);

        qDebug() << "Camera opened with resolution:" << Width << "x" << Height;
        emit connectedResult(true);
    }
    else
    {
        emit connectedResult(false);
    }
}

void Camera::OpenCameraWithResolution(int id, int width, int height)
{
    if (WebcamInstance->open(id) == true)
    {
        // Set custom resolution
        WebcamInstance->set(cv::CAP_PROP_FRAME_WIDTH, width);
        WebcamInstance->set(cv::CAP_PROP_FRAME_HEIGHT, height);

        // Get actual resolution after setting
        Width = WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH);
        Height = WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT);

        qDebug() << "Camera opened with custom resolution:" << Width << "x" << Height;
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

    // Update origin size for industrial camera
    OriginWidth = CaptureImage.cols;
    OriginHeight = CaptureImage.rows;

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

            // Update origin size for image source
            OriginWidth = CaptureImage.cols;
            OriginHeight = CaptureImage.rows;

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
    // Safety checks
    if (WebcamInstance == NULL)
    {
        qDebug() << "Warning: WebcamInstance is null";
        return;
    }

    if (WebcamInstance->isOpened() == false)
    {
        qDebug() << "Warning: Camera not opened or disconnected";
        emit StopCameraRequest();
        return;
    }

    // Attempt to read frame with error handling
    try {
        if (WebcamInstance->read(CaptureImage))
        {
            // Validate captured image
            if (!CaptureImage.empty() && CaptureImage.cols > 0 && CaptureImage.rows > 0)
            {
                OriginWidth = CaptureImage.cols;
                OriginHeight = CaptureImage.rows;
                emit GotImage(CaptureImage);
            }
            else
            {
                qDebug() << "Warning: Captured empty or invalid image";
            }
        }
        else
        {
            qDebug() << "Warning: Failed to read frame from camera";
            // Don't immediately stop, just skip this frame
        }
    } catch (const cv::Exception& e) {
        qDebug() << "OpenCV error in CaptureWebcam:" << e.what();
        emit StopCameraRequest();
    } catch (...) {
        qDebug() << "Unknown error in CaptureWebcam";
        emit StopCameraRequest();
    }
}

cv::Size Camera::GetMaxResolution(cv::VideoCapture* cap)
{
    if (!cap || !cap->isOpened())
        return cv::Size(640, 480); // Default fallback
    
    // List of common resolutions from highest to lowest
    std::vector<cv::Size> resolutions = {
        cv::Size(3840, 2160), // 4K
        cv::Size(2560, 1440), // 1440p
        cv::Size(1920, 1080), // 1080p
        cv::Size(1280, 720),  // 720p
        cv::Size(800, 600),   // SVGA
        cv::Size(640, 480),   // VGA
        cv::Size(320, 240)    // QVGA
    };
    
    for (const auto& res : resolutions)
    {
        // Try to set the resolution
        cap->set(cv::CAP_PROP_FRAME_WIDTH, res.width);
        cap->set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
        
        // Check if the resolution was accepted
        int actualWidth = cap->get(cv::CAP_PROP_FRAME_WIDTH);
        int actualHeight = cap->get(cv::CAP_PROP_FRAME_HEIGHT);
        
        // If the resolution matches or is close enough, use it
        if (abs(actualWidth - res.width) <= 10 && abs(actualHeight - res.height) <= 10)
        {
            qDebug() << "Maximum resolution found:" << actualWidth << "x" << actualHeight;
            return cv::Size(actualWidth, actualHeight);
        }
    }
    
    // If no resolution worked, return whatever the camera currently supports
    int currentWidth = cap->get(cv::CAP_PROP_FRAME_WIDTH);
    int currentHeight = cap->get(cv::CAP_PROP_FRAME_HEIGHT);
    
    qDebug() << "Using current resolution:" << currentWidth << "x" << currentHeight;
    return cv::Size(currentWidth, currentHeight);
}
