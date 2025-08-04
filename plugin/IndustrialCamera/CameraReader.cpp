#include "CameraReader.h"

CameraReader::CameraReader(QObject *parent)
    : QObject{parent}
{
    IndustryCamera = new XCamManager();
}

CameraReader::~CameraReader()
{
    delete IndustryCamera;
}

void CameraReader::ConnectCamera(int id)
{
    bool result = IndustryCamera->ConnectCamera(id);

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
    emit StartedCapture();

    // Thread-safe capture with proper scope
    QMutex mux;
    QMutexLocker locker(&mux);
    
    if (!IndustryCamera) {
        qWarning() << "IndustryCamera is null";
        return;
    }
    
    uint8_t* imageData = IndustryCamera->Capture();
    if (imageData == nullptr) {
        qWarning() << "Failed to capture image data";
        return;
    }

    Height = IndustryCamera->Height();
    Width = IndustryCamera->Width();
    
    // Validate dimensions
    if (Height <= 0 || Width <= 0) {
        qWarning() << "Invalid image dimensions:" << Width << "x" << Height;
        return;
    }
    
    // Create OpenCV Mat safely
    cv::Mat openCvImage;
    try {
        openCvImage = cv::Mat(Height, Width, CV_8UC3, imageData).clone();  // Clone immediately for safety
    } catch (const cv::Exception& e) {
        qWarning() << "OpenCV error creating Mat:" << e.what();
        return;
    }
    
    // Release mutex before heavy processing
    locker.unlock();

    // Process resizing if needed
    if (ResizeWidth > 0 && !openCvImage.empty()) {
        ResizeHeight = Height * (static_cast<float>(ResizeWidth) / Width);
        try {
            cv::resize(openCvImage, openCvImage, cv::Size(ResizeWidth, ResizeHeight), 0, 0, cv::INTER_NEAREST);
        } catch (const cv::Exception& e) {
            qWarning() << "OpenCV error during resize:" << e.what();
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
    emit HadCameraList(IndustryCamera->FindCameraList());
}

void CameraReader::GetResizeImageWidth(int width)
{
    ResizeWidth = width;
}
