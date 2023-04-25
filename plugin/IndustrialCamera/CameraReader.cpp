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

    QMutex mux;
    mux.lock();
    uint8_t* imageData = IndustryCamera->Capture();
    mux.unlock();
    if (imageData == NULL)
        return;

    Height = IndustryCamera->Height();
    Width = IndustryCamera->Width();

    cv::Mat openCvImage = cv::Mat(Height, Width, CV_8UC3, imageData);

    if (ResizeWidth > 0)
    {
        ResizeHeight = Height * ((float)ResizeWidth/ Width);

        resize(openCvImage, openCvImage, cv::Size(ResizeWidth, ResizeHeight), cv::INTER_NEAREST);
    }

    emit CapturedImage(openCvImage.clone());
    openCvImage.release();

    emit FinishReadingImage(ImageTool::cvMatToQPixmap(openCvImage));
}

void CameraReader::ScanCameras()
{
    emit HadCameraList(IndustryCamera->FindCameraList());
}

void CameraReader::GetResizeImageWidth(int width)
{
    ResizeWidth = width;
}
