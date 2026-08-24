#include "camera.h"
#include <vector>
#include <VariableManager.h>

namespace {
bool tryOpenBackend(cv::VideoCapture* capture, int id, int backend,
                    const char* backendName)
{
    try {
        if (!capture->open(id, backend))
            return false;
        capture->set(cv::CAP_PROP_BUFFERSIZE, 1);
        capture->set(cv::CAP_PROP_CONVERT_RGB, 1);
        qInfo() << "Opened USB/UVC camera" << id << "using" << backendName;
        return true;
    } catch (const cv::Exception& error) {
        qWarning() << "Cannot open camera" << id << "using" << backendName
                   << ":" << error.what();
        capture->release();
        return false;
    }
}

bool tryOpenCameraIndex(cv::VideoCapture *capture, int id)
{
    if (!capture)
        return false;

    capture->release();

#ifdef Q_OS_MACOS
    if (tryOpenBackend(capture, id, cv::CAP_AVFOUNDATION, "AVFoundation"))
        return true;
#endif

#ifdef Q_OS_WIN
    // UVC cameras use the same path whether connected through USB 2 or USB 3.
    // MSMF is preferred for modern high-resolution devices; DirectShow is a
    // valuable fallback for older drivers and cameras exposing MJPEG modes.
    if (tryOpenBackend(capture, id, cv::CAP_MSMF, "Media Foundation"))
        return true;
    capture->release();
    if (tryOpenBackend(capture, id, cv::CAP_DSHOW, "DirectShow"))
        return true;
    capture->release();
#endif

    return tryOpenBackend(capture, id, cv::CAP_ANY, "OpenCV auto");
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

    try {
        capture->set(cv::CAP_PROP_FRAME_WIDTH, width);
        capture->set(cv::CAP_PROP_FRAME_HEIGHT, height);

        int actualWidth = capture->get(cv::CAP_PROP_FRAME_WIDTH);
        int actualHeight = capture->get(cv::CAP_PROP_FRAME_HEIGHT);

#ifdef Q_OS_WIN
        if (qAbs(actualWidth - width) > 10 || qAbs(actualHeight - height) > 10) {
            // Many USB3 UVC cameras expose their high-resolution modes only as
            // MJPEG. Retry that format while retaining the raw/YUYV fallback.
            capture->set(cv::CAP_PROP_FOURCC,
                         cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
            capture->set(cv::CAP_PROP_FRAME_WIDTH, width);
            capture->set(cv::CAP_PROP_FRAME_HEIGHT, height);
            actualWidth = capture->get(cv::CAP_PROP_FRAME_WIDTH);
            actualHeight = capture->get(cv::CAP_PROP_FRAME_HEIGHT);
        }
#endif

        qDebug() << "Requested resolution:" << width << "x" << height
                 << "actual:" << actualWidth << "x" << actualHeight;

        return actualWidth > 0 && actualHeight > 0;
    } catch (const cv::Exception& error) {
        qWarning() << "Cannot configure USB/UVC resolution:" << error.what();
        return false;
    }
}
}

Camera::Camera(QObject *parent) : QObject(parent)
{
    WebcamInstance = new cv::VideoCapture();
    industrialCaptureTimeout = new QTimer(this);
    industrialCaptureTimeout->setSingleShot(true);
    industrialCaptureTimeout->setInterval(3500);
    connect(industrialCaptureTimeout, &QTimer::timeout, this, [this]() {
        OnExternalCaptureFailed(QStringLiteral("Industrial camera capture timed out"));
    });
    monotonicClock.start();
    qRegisterMetaType<VisionFrame>("VisionFrame");
}

Camera::~Camera()
{
    if (WebcamInstance) {
        WebcamInstance->release();
        delete WebcamInstance;
        WebcamInstance = nullptr;
    }
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
        try {
            qDebug() << "OpenCV backend:"
                     << QString::fromStdString(WebcamInstance->getBackendName());
        } catch (const cv::Exception&) {
            qDebug() << "OpenCV backend name is unavailable";
        }
        Source = QStringLiteral("Webcam");
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
        try {
            qDebug() << "OpenCV backend:"
                     << QString::fromStdString(WebcamInstance->getBackendName());
        } catch (const cv::Exception&) {
            qDebug() << "OpenCV backend name is unavailable";
        }
        Source = QStringLiteral("Webcam");
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

    if (!industrialCapturePending) {
        qWarning() << "Ignoring unsolicited industrial-camera frame";
        return;
    }

    const quint64 requestId = pendingIndustrialRequestId;
    const int trackingId = pendingIndustrialTrackingId;
    industrialCaptureTimeout->stop();
    industrialCapturePending = false;
    pendingIndustrialRequestId = 0;

    if (mat.empty()) {
        failCapture(requestId, trackingId, QStringLiteral("Industrial camera returned an empty frame"));
        return;
    }

    publishFrame(mat, requestId, trackingId);
}

void Camera::OnExternalCaptureFailed(QString reason)
{
    if (!industrialCapturePending)
        return;
    const quint64 requestId = pendingIndustrialRequestId;
    const int trackingId = pendingIndustrialTrackingId;
    industrialCaptureTimeout->stop();
    industrialCapturePending = false;
    pendingIndustrialRequestId = 0;
    failCapture(requestId, trackingId,
                reason.isEmpty() ? QStringLiteral("Industrial camera capture failed") : reason);
}

void Camera::GeneralCapture()
{
    capture(0, trackingThreadId);
}

void Camera::capture(quint64 requestId, int trackingId)
{
    if (Source == "Webcam" || Source == "Video")
    {
        if (!WebcamInstance || !WebcamInstance->isOpened()) {
            failCapture(requestId, trackingId, QStringLiteral("Webcam is not open"));
            emit StopCameraRequest();
            return;
        }

        cv::Mat frame;
        try {
            if (!WebcamInstance->read(frame) || frame.empty()) {
                failCapture(requestId, trackingId, QStringLiteral("Failed to read a webcam frame"));
                return;
            }
        } catch (const cv::Exception& e) {
            failCapture(requestId, trackingId,
                        QStringLiteral("OpenCV capture error: %1").arg(QString::fromUtf8(e.what())));
            emit StopCameraRequest();
            return;
        }
        publishFrame(frame, requestId, trackingId);
        return;
    }

    if (Source == "Images")
    {
        if (CaptureImages.isEmpty()) {
            failCapture(requestId, trackingId, QStringLiteral("No test image is loaded"));
            return;
        }
        if (FrameID < 0 || FrameID >= CaptureImages.count())
            FrameID = 0;
        const cv::Mat frame = CaptureImages.at(FrameID).clone();
        FrameID = (FrameID + 1) % CaptureImages.count();
        publishFrame(frame, requestId, trackingId);
        return;
    }

    if (Source == "Industrial Camera")
    {
        if (industrialCapturePending) {
            failCapture(requestId, trackingId, QStringLiteral("Industrial camera is still processing the previous frame"));
            return;
        }
        industrialCapturePending = true;
        pendingIndustrialRequestId = requestId;
        pendingIndustrialTrackingId = trackingId;
        industrialCaptureTimeout->start();
        emit RequestCapture();
        return;
    }

    failCapture(requestId, trackingId, QStringLiteral("Unsupported camera source: %1").arg(Source));
}

void Camera::CaptureAndDetect(quint64 requestId, int trackingId)
{
    trackingThreadId = trackingId;
    capture(requestId, trackingId);
}

void Camera::SetTracking(int id)
{
    trackingThreadId = id;
}

void Camera::CaptureWebcam()
{
    capture(0, trackingThreadId);
}

void Camera::SetSource(QString source)
{
    Source = source.trimmed();
}

void Camera::SetImages(QList<cv::Mat> images)
{
    CaptureImages.clear();
    for (const cv::Mat& image : images) {
        if (!image.empty())
            CaptureImages.append(image.clone());
    }
    FrameID = CaptureImages.isEmpty() ? -1 : 0;
    CaptureImage = CaptureImages.isEmpty() ? cv::Mat() : CaptureImages.first().clone();
    Source = QStringLiteral("Images");
}

bool Camera::OpenVideoFile(QString path, int requestedWidth, int requestedHeight)
{
    if (!WebcamInstance || path.trimmed().isEmpty())
        return false;
    WebcamInstance->release();
    if (!WebcamInstance->open(path.toStdString()))
        return false;
    if (requestedWidth > 0)
        WebcamInstance->set(cv::CAP_PROP_FRAME_WIDTH, requestedWidth);
    if (requestedHeight > 0)
        WebcamInstance->set(cv::CAP_PROP_FRAME_HEIGHT, requestedHeight);
    Width = static_cast<int>(WebcamInstance->get(cv::CAP_PROP_FRAME_WIDTH));
    Height = static_cast<int>(WebcamInstance->get(cv::CAP_PROP_FRAME_HEIGHT));
    RunningCamera = -2; // A valid non-device VideoCapture source.
    Source = QStringLiteral("Video");
    return true;
}

void Camera::publishFrame(const cv::Mat& image, quint64 requestId, int trackingId)
{
    if (image.empty()) {
        failCapture(requestId, trackingId, QStringLiteral("Capture produced an empty frame"));
        return;
    }

    VisionFrame frame;
    frame.frameId = nextFrameId++;
    frame.requestId = requestId;
    frame.trackingId = trackingId;
    frame.capturedAtMonotonicNs = monotonicClock.nsecsElapsed();
    frame.source = Source;
    frame.image = image.clone();

    CaptureImage = frame.image.clone();
    OriginWidth = frame.image.cols;
    OriginHeight = frame.image.rows;

    // The blocking receiver creates the matching encoder snapshot before any
    // detector can observe this exact frame.
    emit StartedCapture(trackingId, frame.frameId, requestId);
    emit FrameCaptured(frame);
    emit GotImage(frame.image);
}

void Camera::failCapture(quint64 requestId, int trackingId, const QString& reason)
{
    qWarning() << "Camera capture failed:" << reason
               << "tracking" << trackingId << "request" << requestId;
    emit CaptureFailed(trackingId, requestId, reason);
}

void Camera::ReleaseCamera()
{
    industrialCaptureTimeout->stop();
    industrialCapturePending = false;
    pendingIndustrialRequestId = 0;
    if (WebcamInstance && WebcamInstance->isOpened())
        WebcamInstance->release();
    RunningCamera = -1;
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
