#ifndef CAMERAPROCESSOR_H
#define CAMERAPROCESSOR_H

#include <QObject>
#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigECamera.h>

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

#include <MvCameraControl.h>

#include "xcammanager.h"
#include <QLabel>
#include "ImageUnity.h"
#include <qtimer.h>
#include <QTimer>
#include <QElapsedTimer>
#include <QRunnable>
#include <QMutex>

class CameraProcessor : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit CameraProcessor(QObject *parent = nullptr);

    void run() override;

    void UpdateLabelImage(cv::Mat mat, QLabel* label);

    QTimer* Timer;

    XCamManager* IndustryCamera;
    cv::Mat* openCvImage = NULL;

    int MatWidth = 800;
    int MatHeight = 600;

    int CameraInterval = 50;

    bool IsLoopRunning = true;
    bool IsStream = false;

    int Height = 0;
    int Width = 0;

    QLabel* cameraWidget = NULL;
    QLabel* lbRatio = NULL;


    bool CaptureSignal = false;

    QElapsedTimer elapseTime;
public slots:
    void ShotImage();
signals:
    void StartedCapture();
    void CapturedImage(cv::Mat mat);
    void FinishReadingImage(QPixmap pixmap);
    void UpdatedRatio(QString ratio);
    void FinishJob(bool state);

private:

};

#endif // CAMERAPROCESSOR_H
