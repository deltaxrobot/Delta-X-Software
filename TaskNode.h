#ifndef TASK_NODE
#define TASK_NODE

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>
#include <QPixmap>
#include <QMap>
#include <qmath.h>
#include "Object.h"
#include <QMutexLocker>

#define RED_COLOR       cv::Scalar(0, 0, 255)
#define GREEN_COLOR     cv::Scalar(0, 255, 0)
#define BLUE_COLOR      cv::Scalar(255, 0, 0)
#define YELLOW_COLOR    cv::Scalar(0, 255, 255)
#define BLACK_COLOR    cv::Scalar(0, 0, 0)
#define WHITE_COLOR    cv::Scalar(255, 255, 255)

struct Range
{
    float Min;
    float Max;
};

class TaskNode : public QObject
{
    Q_OBJECT
public:
    TaskNode(QString name, int type);
    ~TaskNode();

    enum
    {
        GET_IMAGE_NODE = 0,
        RESIZE_IMAGE_NODE,
        FIND_CHESSBOARD_NODE,
        GET_PERSPECTIVE_NODE,
        WARP_IMAGE_NODE,
        CROP_IMAGE_NODE,
        DISPLAY_IMAGE_NODE,
        COLOR_FILTER_NODE,
        MAPPING_MATRIX_NODE,
        GET_OBJECTS_NODE,
        VISIBLE_OBJECTS_NODE,
        TRACKING_OBJECTS_NODE
    };

    enum
    {
        THRESHOLD = 10,
        HSV = 11
    };

    void SetNextNode(TaskNode* next);
    void SetPreviousNode(TaskNode* previous);
    void ClearInputConnections();
    void RemoveInputConnection(TaskNode* previous);
    void ClearOutputConnections();
    QSize GetImageSize();
    QMatrix GetMatrix();
    cv::Mat GetOutputImage();
    Object GetInputObject();
    QPointF *GetInputPointPointer();
    bool ClearVariable(QString name);

    QList<QMetaObject::Connection> InputConnections;

public slots:
    void Input(cv::Size size);
    void Input(cv::Mat mat);
    void Input2(cv::Mat mat);
    void Input(QList<Object*>* objects);
    void Input(QList<int> paras);
    void Input(int para);
    void Input(bool value);
    void Input(float para);
    void Input(QString name, Range range);
    void Input(QMatrix matrix);
    void Input(QPointF point);
    void Input(cv::Point2f points[]);
    void Input(QPolygonF poly);
    void Input(QRectF rect);
    void Input(Object obj);

    void DoWork();

signals:
    void HadOutput(cv::Mat mat);
    void HadOutput(cv::Point2f outputPoints[]);
    void HadOutput(QPolygonF poly);
    void HadOutput(QPixmap pixmap);
    void HadOutput(QPixmap pixmap, QList<Object*>* objects);
    void HadOutput(QList<Object*>* objects);
    void HadOutput(QMatrix matrix);

private:
    QString name;
    int type;

    cv::Size size;
    cv::Mat outputMat;
    cv::Mat inputMat;
    cv::Mat inputMat2;
    QList<Object*>* inputObjects = NULL;

    cv::Point2f inputPoints[4];
    cv::Point2f outputPoints[4];

    QPolygonF inputPoly;
    QPolygonF outputPoly;
    QRectF inputRect;

    QList<Object*>* outputObjects = NULL;
    QList<int> intParas;
    int intPara;
    float floatPara;
    bool boolPara;
    QPointF inputPoint;
    QMatrix inputMatrix;
    QMatrix outputMatrix;

    Object inputObject;

    QMap<QString, Range> ranges;

    QList<TaskNode*> previousTaskNodes;
    QList<TaskNode*> nextTaskNodes;


    void connectInOutNode(TaskNode* previous, TaskNode *next);

    void doGetImageWork();
    void doResizeWork();
    void doFindChessboardWork();
    void doGetPerspectiveWork();
    void doWarpWork();
    void doCropWork();
    void doDisplayImageWork();
    void doColorFilterWork();
    void doMappingMatrixWork();
    void doGetObjectsWork();
    void doVisibleObjectsWork();
    void doTrackingObjectsWork();

    void clear(QList<Object*>* objs);
};

#endif
