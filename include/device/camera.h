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
#include <QElapsedTimer>
#include <QTimer>

#include "VisionTypes.h"
#include "PhoneCameraServer.h"



class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    ~Camera() override;

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
    QString ProjectName = "project0";
    int FrameID = -1;
    PhoneCameraServer* phoneServer = nullptr;

signals:
    void StartedCapture(int tracking, quint64 frameId, quint64 requestId);
    void FrameCaptured(VisionFrame frame);
    void GotImage(cv::Mat);
    void RequestCapture();
    void StopCameraRequest();
    void connectedResult(bool isOpen, int requestId);
    void CaptureFailed(int trackingId, quint64 requestId, QString reason);

public slots:
    void OpenCamera(int id, int requestId = 0);
    void OpenCameraWithResolution(int id, int width, int height, int requestId = 0);
    void GetImageFromExternal(cv::Mat mat);
    void OnExternalCaptureFailed(QString reason);
    void GeneralCapture();
    void CaptureWebcam();
    void CaptureAndDetect(quint64 requestId, int trackingId);
    void SetTracking(int id);
    void SetSource(QString source);
    void SetImages(QList<cv::Mat> images);
    bool OpenVideoFile(QString path, int requestedWidth, int requestedHeight);
    void ReleaseCamera();

 private:
    bool configureOpenedCameraResolution();
    cv::Size GetMaxResolution(cv::VideoCapture* cap);
    void capture(quint64 requestId, int trackingId);
    void publishFrame(const cv::Mat& image, quint64 requestId, int trackingId);
    void failCapture(quint64 requestId, int trackingId, const QString& reason);
    int trackingThreadId = 0;
    quint64 nextFrameId = 1;
    bool industrialCapturePending = false;
    quint64 pendingIndustrialRequestId = 0;
    int pendingIndustrialTrackingId = 0;
    QTimer* industrialCaptureTimeout = nullptr;
    QElapsedTimer monotonicClock;
};

#endif // CAMERA_H
