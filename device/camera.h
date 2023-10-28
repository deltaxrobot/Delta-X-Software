#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QPushButton>
#include <QCameraInfo>


class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);

    int RunningCamera = -1;
    bool IsCameraPause = false;
    cv::VideoCapture* WebcamInstance;
    cv::Mat CaptureImage;
    float CameraFPS = 2;
    float CameraTimerInterval = 500;
    QString Source = "Webcam";
signals:
    void StartedCapture(int tracking);
    void GotImage(cv::Mat);
    void RequestCapture();
    void StopCameraRequest();

public slots:
    void GetImageFromExternal(cv::Mat mat);
    void GeneralCapture();
    void CaptureWebcam();
    void CaptureAndDetect();
    void SetTracking(int id);

 private:

    int trackingThreadId = 0;
};

#endif // CAMERA_H
