#include "camera.h"
#include <vector>
#include <VariableManager.h>

namespace {
bool tryOpenCameraIndex(cv::VideoCapture *capture, int id)
{
    if (!capture)
        return false;

    capture->release();

#ifdef Q_OS_MACOS
    if (capture->open(id, cv::CAP_AVFOUNDATION))
        return true;
#endif

    return capture->open(id);
}

bool openPreferredCameraBackend(cv::VideoCapture *capture, int requestedId, int *openedId)
{
    if (!capture)
        return false;

    std::vector<int> candidateIds;
    candidateIds.push_back(requestedId);

#ifdef Q_OS_MACOS
    for (int fallbackId = 0; fallbackId < 8; ++fallbackId) {
        if (fallbackId != requestedId)
            candidateIds.push_back(fallbackId);
    }
#endif

    for (const int candidateId : candidateIds) {
        qDebug() << "Trying camera id" << candidateId;
        if (tryOpenCameraIndex(capture, candidateId)) {
            if (openedId)
                *openedId = candidateId;

            if (candidateId != requestedId) {
                qDebug() << "Requested camera id" << requestedId
                         << "failed, fallback camera id" << candidateId
                         << "opened successfully";
            }
            return true;
        }
    }

    return false;
}

bool applyResolution(cv::VideoCapture *capture, int width, int height)
{
    if (!capture || !capture->isOpened() || width <= 0 || height <= 0)
        return false;

    capture->set(cv::CAP_PROP_FRAME_WIDTH, width);
    capture->set(cv::CAP_PROP_FRAME_HEIGHT, height);

    const int actualWidth = capture->get(cv::CAP_PROP_FRAME_WIDTH);
    const int actualHeight = capture->get(cv::CAP_PROP_FRAME_HEIGHT);

    qDebug() << "Requested resolution:" << width << "x" << height
             << "actual:" << actualWidth << "x" << actualHeight;

    return actualWidth > 0 && actualHeight > 0;
}
}

Camera::Camera(QObject *parent) : QObject(parent)
{
    WebcamInstance = new cv::VideoCapture();
}

void Camera::OpenCamera(int id, int requestId)
{
    int openedId = id;
    if (openPreferredCameraBackend(WebcamInstance, id, &openedId) == true)
    {
        RunningCamera = openedId;

        configureOpenedCameraResolution();

        qDebug() << "Camera opened with resolution:" << Width << "x" << Height;
        qDebug() << "Using camera id:" << openedId;
        qDebug() << "OpenCV backend:" << QString::fromStdString(WebcamInstance->getBackendName());
        emit connectedResult(true, requestId);
    }
    else
    {
        qDebug() << "Failed to open camera id" << id;
        emit connectedResult(false, requestId);
    }
}

void Camera::OpenCameraWithResolution(int id, int width, int height, int requestId)
{
    int openedId = id;
    if (openPreferredCameraBackend(WebcamInstance, id, &openedId) == true)
    {
        RunningCamera = openedId;
        Width = width;
        Height = height;
        configureOpenedCameraResolution();

        qDebug() << "Camera opened with custom resolution:" << Width << "x" << Height;
        qDebug() << "Using camera id:" << openedId;
        qDebug() << "OpenCV backend:" << QString::fromStdString(WebcamInstance->getBackendName());
        emit connectedResult(true, requestId);
    }
    else
    {
        qDebug() << "Failed to open camera id" << id << "with custom resolution";
        emit connectedResult(false, requestId);
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
    // Allow external script to select tracking ID via VariableManager
    QString prefix = VariableManager::instance().Prefix;
    QString key = prefix.isEmpty() ? QString("Camera.TrackingID") : prefix + ".Camera.TrackingID";
    int id = VariableManager::instance().getVar(key, trackingThreadId).toInt();
    trackingThreadId = id;
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

bool Camera::configureOpenedCameraResolution()
{
    if (!WebcamInstance || !WebcamInstance->isOpened())
        return false;

    int targetWidth = Width;
    int targetHeight = Height;

#ifdef Q_OS_MACOS
    if (targetWidth <= 0 || targetHeight <= 0) {
        targetWidth = 1280;
        targetHeight = 720;
    }

    applyResolution(WebcamInstance, targetWidth, targetHeight);
#else
    if (targetWidth > 0 && targetHeight > 0) {
        applyResolution(WebcamInstance, targetWidth, targetHeight);
    } else {
        const cv::Size maxRes = GetMaxResolution(WebcamInstance);
        targetWidth = maxRes.width;
        targetHeight = maxRes.height;
        applyResolution(WebcamInstance, targetWidth, targetHeight);
    }
#endif

    Width = WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH);
    Height = WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT);
    return Width > 0 && Height > 0;
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
