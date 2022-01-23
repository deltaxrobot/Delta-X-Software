#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QMutex>
#include <QReadWriteLock>
#include <QSemaphore>
#include <QWaitCondition>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/dnn.hpp"
#include <QLineEdit>

#include <QTimer>

class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = nullptr);

    QList<cv::RotatedRect> RectangleObjects;
    std::vector<cv::Vec3f> CircleObjects;

    QTimer* Timer;

signals:
    void inDisplay(QPixmap pixmap);
    void captureImage(cv::Mat mat);
    void outDisplay(QPixmap pixmap);
    void cameraClosed();
    void readImageFailed();
    void startingOpenCamera();
    void finishingOpenCamera();

public slots:
    void getCamera(cv::VideoCapture* cam);
    void getCamera(cv::VideoCapture* cam, int id, QLineEdit* w, QLineEdit* h);
    void putInfoOnImage(cv::Mat& mat, QList<cv::RotatedRect> objects, cv::Scalar color);
    void startVideo();
    void stopVideo();
    void CloseLoop();
    void TimerFunction();
private:
    bool loopRunning = true;
    cv::VideoCapture* camera = NULL;
};

#endif // VIDEOPROCESSOR_H
