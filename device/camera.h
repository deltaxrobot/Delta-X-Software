#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QPushButton>
#include <QDateTime>

#include <QThread>
#include <QCoreApplication>
#include <QDebug>



class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);

    int RunningCamera = -1;
    bool IsCameraPause = false;
    cv::VideoCapture* WebcamInstance;
    cv::Mat CaptureImage;
    QList<cv::Mat> CaptureImages;
    float CameraFPS = 2;
    float CameraTimerInterval = 500;
    int OriginWidth = 0;
    int OriginHeight = 0;
    int Width = 0;
    int Height = 0;
    QString Source = "Webcam";
    int FrameID = -1;

signals:
    void StartedCapture(int tracking);
    void GotImage(cv::Mat);
    void RequestCapture();
    void StopCameraRequest();
    void connectedResult(bool isOpen);

public slots:
    void OpenCamera(int id);
    void OpenCameraWithResolution(int id, int width, int height);
    void GetImageFromExternal(cv::Mat mat);
    void GeneralCapture();
    void CaptureWebcam();
    void CaptureAndDetect();
    void SetTracking(int id);

 private:
    cv::Size GetMaxResolution(cv::VideoCapture* cap);
    int trackingThreadId = 0;
};

#endif // CAMERA_H
