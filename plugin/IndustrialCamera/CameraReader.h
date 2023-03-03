#ifndef CAMERAREADER_H
#define CAMERAREADER_H

#include <QObject>
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

class CameraReader : public QObject
{
    Q_OBJECT
public:
    explicit CameraReader(QObject *parent = nullptr);
    ~CameraReader();

    XCamManager* IndustryCamera;

    cv::Mat* openCvImage = NULL;

    int ResizeWidth = -1;
    int ResizeHeight = 500;

    int Height = 0;
    int Width = 0;

public slots:
    void ConnectCamera(int id);
    void DisconnectCamera();
    void ShotImage();
    void ScanCameras();
    void GetResizeImageWidth(int width);

signals:
    void StartedCapture();
    void CapturedImage(cv::Mat mat);
    void FinishReadingImage(QPixmap pixmap);
    void UpdatedRatio(QString ratio);
    void HadConnectingResult(bool);
    void HadCameraList(QStringList list);
};

#endif // CAMERAREADER_H
