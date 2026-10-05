#include "CameraReader.h"

CameraReader::CameraReader(QObject *parent)
    : QObject{parent}
{
    IndustryCamera = new XCamManager(this);
}

CameraReader::~CameraReader()
{
    // IndustryCamera is a QObject child and is destroyed in this worker thread.
}

bool CameraReader::HasAvailableBackend() const
{
    return IndustryCamera && IndustryCamera->HasAnyBackend();
}

QString CameraReader::BackendStatus() const
{
    return IndustryCamera
        ? IndustryCamera->RuntimeStatus()
        : QStringLiteral("Industrial camera manager is unavailable");
}

void CameraReader::ConnectCamera(int id)
{
    const bool result = IndustryCamera && IndustryCamera->HasAnyBackend() &&
                        IndustryCamera->ConnectCamera(id);

    emit HadConnectingResult(result);
}

void CameraReader::DisconnectCamera()
{
    if (IndustryCamera->IsOpen())
    {
        IndustryCamera->DisconnectCamera();
    }
}

void CameraReader::ShotImage()
{
    QMutexLocker locker(&captureMutex);
    
    if (!IndustryCamera || !IndustryCamera->HasAnyBackend()) {
        qWarning() << "Industrial camera backend unavailable:" << BackendStatus();
        emit CaptureFailed(BackendStatus());
        return;
    }

    emit StartedCapture();
    
    uint8_t* imageData = IndustryCamera->Capture();
    if (imageData == nullptr) {
        qWarning() << "Failed to capture image data";
        emit CaptureFailed("Industrial camera did not return image data");
        return;
    }

    Height = IndustryCamera->Height();
    Width = IndustryCamera->Width();
    
    // Validate dimensions
    if (Height <= 0 || Width <= 0) {
        qWarning() << "Invalid image dimensions:" << Width << "x" << Height;
        emit CaptureFailed("Industrial camera returned invalid image dimensions");
        return;
    }
    
    // Create OpenCV Mat safely
    cv::Mat openCvImage;
    try {
        openCvImage = cv::Mat(Height, Width, CV_8UC3, imageData).clone();  // Clone immediately for safety
    } catch (const cv::Exception& e) {
        qWarning() << "OpenCV error creating Mat:" << e.what();
        emit CaptureFailed(QString("Cannot copy industrial frame: %1").arg(e.what()));
        return;
    }
    
    // Release mutex before heavy processing
    locker.unlock();

    // Process resizing if needed
    if (ResizeWidth > 0 && !openCvImage.empty()) {
        ResizeHeight = Height * (static_cast<float>(ResizeWidth) / Width);
        try {
            cv::resize(openCvImage, openCvImage, cv::Size(ResizeWidth, ResizeHeight), 0, 0, cv::INTER_LINEAR);
        } catch (const cv::Exception& e) {
            qWarning() << "OpenCV error during resize:" << e.what();
            emit CaptureFailed(QString("Cannot resize industrial frame: %1").arg(e.what()));
            return;
        }
    }

    // Emit signals with safe data
    if (!openCvImage.empty()) {
        emit CapturedImage(openCvImage.clone());
        
        // Create QPixmap for display (before releasing openCvImage)
        QPixmap displayPixmap = ImageTool::cvMatToQPixmap(openCvImage);
        emit FinishReadingImage(displayPixmap);
    }
}

void CameraReader::ScanCameras()
{
    emit HadCameraList(IndustryCamera ? IndustryCamera->FindCameraList()
                                     : QStringList());
}

void CameraReader::GetResizeImageWidth(int width)
{
    ResizeWidth = width;
}

void CameraReader::SetExposureTime(int exposureUs)
{
    if (IndustryCamera)
        IndustryCamera->SetExposureTime(exposureUs);
}
