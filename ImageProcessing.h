#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING

#include <QObject>
#include <qwidget.h>
#include <FilterWindow.h>
#include <qfiledialog.h>
#include <qscrollarea.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>
#include <string>
#include <QInputDialog>
#include <qlabel.h>
#include <qtimer.h>
#include <qpushbutton.h>
#include <QCheckBox>
#include "BlobManager.h"
#include "UnityTool.h"
#include "CameraWidget.h"
#include "RobotWindow.h"
#include <QToolButton>
#include <QRadioButton>
#include "opencv2/dnn.hpp"

#include "VideoProcessor.h"
#include <QThread>
#include "VideoDisplay.h"
#include <QTcpSocket>
#include <QProcess>
#include <QTcpServer>

#define RED_COLOR       cv::Scalar(0, 0, 255)
#define GREEN_COLOR     cv::Scalar(0, 255, 0)
#define BLUE_COLOR      cv::Scalar(255, 0, 0)
#define YELLOW_COLOR    cv::Scalar(0, 255, 255)
#define BLACK_COLOR    cv::Scalar(0, 0, 0)
#define WHITE_COLOR    cv::Scalar(255, 255, 255)

#define HSV_SPACE				0
#define THRESHOLD_SPACE			1
#define GRB_SPACE				2
#define LAB_SPACE				3
#define YCRCB_SPACE				4

#define ORIGIN				2
#define RESULT				0
#define PROCESSING			1

#define DEFAULT_PROCESSING_SIZE	640
#define DEFAULT_OBJECT_WIDTH	150
#define DEFAULT_OBJECT_HEIGHT	150
#define APPROXIMATE_RANGE		20
#define APPROXIMATE_RATIO		0.5f

#define MIN_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH - APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT - APPROXIMATE_RANGE)
#define MAX_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH + APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT + APPROXIMATE_RANGE)

#define X_AXIS_DOWN		2
#define X_AXIS_RIGHT	3
#define X_AXIS_UP		1
#define X_AXIS_LEFT		4

#define DEFAULT_FPS			15
#define DEFAULT_INTERVAL	1000/DEFAULT_FPS

#define CONVEYOR_TIMER_INTERVAL	100

class Task : public QObject
{
    Q_OBJECT
public:
    Task()
    {

    }
    ~Task()
    {

    }

    QString getName()
    {
        return name;
    }

    cv::Mat getMat(QString name)
    {

    }

    cv::Mat& getMatPointer(QString name)
    {

    }

    std::vector<cv::Point> getPoints(QString name)
    {

    }

    int* getIntArray(QString name)
    {

    }

    int getInt(QString name)
    {

    }

private:
    QString name;

};


class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    ImageProcessing()
    {
    }

    ~ImageProcessing()
    {

    }

    QList<Task*> TaskList;
    int TaskOrder = -1;

public slots:

    void CaptureCamera(cv::VideoCapture* Camera);

    void GetImage(cv::Mat mat);
    void ResizeImage(cv::Mat mat);

    void ExecuteTaskFlow();
    void FindNextTask();

};

#endif
