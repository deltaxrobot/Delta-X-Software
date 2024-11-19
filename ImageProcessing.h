#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING

#include <QObject>
#include <qwidget.h>
#include <qfiledialog.h>
#include <qscrollarea.h>

#include <ImageUnity.h>
#include <QInputDialog>
#include <qlabel.h>
#include <qtimer.h>
#include <qpushbutton.h>
#include <QCheckBox>

#include "UnityTool.h"
#include <QToolButton>
#include <QRadioButton>

#include "opencv2/dnn.hpp"

#include <QThread>
#include <QTcpSocket>
#include <QProcess>
#include <QTcpServer>
#include <QMap>

#include "TaskNode.h"
#include "ObjectInfo.h"
#include <QSharedPointer>


class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    ImageProcessing();
    ~ImageProcessing();
    QString ProjectName = "project0";

    TaskNode *CreatTaskNode(QString name, int type, QString previousTasks = "");
    TaskNode* GetNode(QString name);

    QString ObjectsName = "#Objects";

public slots:
    void GotVisibleObjects(QVector<Object> objects);
    void GotImage(cv::Mat mat);
    void GotResizeValue(cv::Size size);
    void GotPerspectiveMatrix(cv::Mat matrix);

signals:
    void mappedDetectedObjects(QVector<ObjectInfo> detectedObjects, QString objectListName);

private:
    QMap<QString, TaskNode*> taskNodeList;
    QVector<ObjectInfo> objectInfos;

    cv::Size resizeValue;
    cv::Mat perspectiveMatrix;
};

#endif
