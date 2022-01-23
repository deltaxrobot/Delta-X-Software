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

class CameraProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CameraProcessor(QObject *parent = nullptr);

    void UpdateLabelImage(cv::Mat mat, QLabel* label);

    QTimer* Timer;

    XCamManager IndustryCamera;
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
public slots:

    void ShotImage();
    void Loop();
    void TimerFunction();
signals:
    void CapturedImage(cv::Mat mat);
private:

};

#endif // CAMERAPROCESSOR_H
