#ifndef TRACKINGMANAGER_H
#define TRACKINGMANAGER_H

#include <QObject>
#include <QPointF>
#include <QLineF>
#include <QtMath>
#include <QElapsedTimer>
#include <QTimer>
#include <QDebug>
#include <QVector3D>
#include <QVector2D>
#include <QDateTime>
#include <VariableManager.h>
#include <ObjectInfo.h>
#include <QVector>
#include <algorithm>

class VirtualEncoder : public QObject {
    Q_OBJECT
private:
    QTimer timer;
    qint64 lastUpdateTime;
    float velocity;  // Đơn vị: mm/giây
    float currentPosition;  // Đơn vị: mm
    bool isRun = false;

public:
    VirtualEncoder(float initialPosition = 0.0, float velocity = 0.0, QObject* parent = nullptr);

    void setVelocity(float newVelocity);
    void setPosition(float newPos);
    float readPosition();
    int readInterval();
    bool IsActive();
public slots:
    void stop();
    // Phương thức để khởi động lại encoder
    void start(int interval = 100);
    void reset();
    void updatePosition();

signals:
    void positionUpdated(float newPosition);
};

class Tracking : public QObject
{
    Q_OBJECT
public:
    explicit Tracking(QObject *parent = nullptr);
    void UpdateTrackedObjectsPosition(float moved);

    QVector<ObjectInfo> TrackedObjects;

    float displacement = 0;
    float SimilarityThreshold = 20;
    float IoUThreshold = 0.3;
    float DistanceThreshold = 7;
    int nextID = 0;

    QVector3D VelocityVector = QVector3D(0, 100, 0);
    QString VectorName = "#Vector1";

    QVector3D TestPointOffset = QVector3D(0, 0, 0);
    bool IsUpateTestPoint = false;

    QString EncoderName = "encoder0";
    QString EncoderType = "X Encoder";
    bool IsReverse = false;
    QString ListName = "#Objects";

    VirtualEncoder VirEncoder;

    float lastEncoderPositionAtCapture = 0.0;
    float lastEncoderPositionAtMapping = 0.0;

    int ID = 0;
    QString ReadPurpose = "Update";
    bool clientWaiting = false;
    float X_max = 1200, X_min = -300, Y_max = 1200, Y_min = -400; // Boundary coordinates


signals:
    void DistanceMoved(QPointF offset);
    void TestPointUpdated(QVector3D testPointOffset);
    void SendGcodeRequest(QString deviceName, QString gcode);
    void UpdateTrackingDone();
    void UpdateVar(QString name, QVariant value);

public slots:
    void OnReceivceEncoderPosition(float value);
    void ChangeObjectInfo(QString cmd);
    void GetVirtualEncoderPosition();
    void ReadEncoder();
    void SetEncoderReverse(bool isReverse);
    void SaveCapturePosition();
    void SaveDetectPosition();

    void UpdateTrackedObjects(QVector<ObjectInfo> detectedObjects, QString objectListName);
    void UpdateTrackedObjectOffsets(QVector3D offset);
    void GetObjectsInArea(QString inAreaListName, float min, float max, bool isXDirection = true);

    void updatePositions(double displacement);
    void ClearTrackedObjects();
    void RemoveTrackedObjects(int id);
private:
    QVector3D calculateMoved(float distance);
    double similarity(ObjectInfo& obj1, ObjectInfo& obj2, double displacement);
    double calculateIoU(ObjectInfo& obj1, ObjectInfo& obj2);
    bool isSameObject(ObjectInfo& object1, ObjectInfo& object2);
    float lastPosition = 0;
    float capturePosition = 0;
    float detectPosition = 0;
    float currentPosition = 0;
    bool first = true;
    QList<int> updatedObjectIDList;
    QVector<ObjectInfo> DetectedObjects;

};

class TrackingManager : public QObject
{
    Q_OBJECT
public:
    explicit TrackingManager(QObject *parent = nullptr);

    QList<Tracking*> Trackings;
    int currentTrackingRequest = 0;

public slots:
    void SaveCapturePosition(int id);
    void SaveDetectPosition(int id);
    void UpdateTracking(int id);
    void GetObjectsInArea(int trackingID, QString inAreaListName, float min, float max, bool isXDirection = true);
    void UpdateVariable(QString cmd);
    void AddObject(QString listName, QList<QStringList> list);
    void ClearObjects(QString listName);
    void SetEncoderPosition(int id, float value);
    void ReadEncoderWhenSensorActive(int id);
    void OnDoneUpdateTracking();

signals:
    void GotResponse(QString deviceId, QString response);
};
#endif // TRACKINGMANAGER_H
