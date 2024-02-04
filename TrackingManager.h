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

class VirtualEncoder : public QObject {
    Q_OBJECT
private:
    QTimer timer;
    qint64 lastUpdateTime;
    float velocity;  // Đơn vị: mm/giây
    float currentPosition;  // Đơn vị: mm

public:
    VirtualEncoder(float initialPosition = 0.0, float velocity = 0.0, QObject* parent = nullptr);

    void setVelocity(float newVelocity);
    float readPosition();
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

    QList<ObjectInfo> TrackedObjects;
    QList<ObjectInfo> DetectedObjects;

    float displacement = 0;
    float SimilarityThreshold =20;
    int nextID = 0;

    QVector3D VelocityVector;
    QString VectorName = "#Vector1";

    QString EncoderName = "encoder0";
    QString EncoderType = "Encoder X";
    bool IsReverse = false;
    QString ListName = "#Objects";

    VirtualEncoder VirEncoder;

    float lastEncoderPositionAtCapture = 0.0;
    float lastEncoderPositionAtMapping = 0.0;

    int ID = 0;
    QString ReadPurpose = "Update";
    float X_max = 1200, X_min = -300, Y_max = 400, Y_min = -400; // Boundary coordinates


signals:
    void DistanceMoved(QPointF offset);
    void SendGcodeRequest(QString deviceName, QString gcode);

public slots:
    void OnReceivceEncoderPosition(float value);
    void ChangeObjectInfo(QString cmd);
    void GetVirtualEncoderPosition();
    void ReadEncoder();
    void SetEncoderReverse(bool isReverse);
    void SaveCapturePosition();
    void SaveDetectPosition();

    void UpdateTrackedObjects(QList<ObjectInfo> detectedObjects, QString objectListName);

    void updatePositions(double displacement);
    void ClearTrackedObjects();
    void RemoveTrackedObjects(int id);
private:
    QVector3D calculateMoved(float distance);
    double similarity(ObjectInfo& obj1, ObjectInfo& obj2, double displacement);
    float lastPosition = 0;
    float capturePosition = 0;
    float detectPosition = 0;
    float currentPosition = 0;
    bool first = true;

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
