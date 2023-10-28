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

class ObjectInfo {
public:
    int id;
    QVector3D center;  // X, Y, Z position
    double width;
    double height;
    double angle;
    bool isPicked;  // Indicates if the object has been picked

    ObjectInfo(int id, QVector3D center, double width, double height, double angle, bool isPicked=false)
        : id(id), center(center), width(width), height(height), angle(angle), isPicked(isPicked) {}
};

class Tracking : public QObject
{
    Q_OBJECT
public:
    explicit Tracking(QObject *parent = nullptr);

    QList<ObjectInfo> trackedObjects;
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

signals:
    void DistanceMoved(QPointF offset);
    void GotCaptureDetectOffset(QPointF offset);
    void GotCapturedPosition(float value);
    void GotDetectedPosition(float value);
    void SendGcodeRequest(QString deviceName, QString gcode);

public slots:
    void OnReceivceEncoderPosition(float value);
    void GetVirtualEncoderPosition();
    void ReadEncoder();
    void SetEncoderReverse(bool isReverse);
    void SaveCapturePosition();
    void SaveDetectPosition();

    void UpdateTrackedObjects(QList<ObjectInfo> detectedObjects, double displacement);
    void updatePositions(double displacement);
private:
    QPointF calculateMoved(float distance);
    double similarity(ObjectInfo& obj1, ObjectInfo& obj2, double displacement);
    float lastPosition = 0;
    float capturePosition = 0;
    float detectPosition = 0;
    float currentPosition = 0;
    bool first = true;
    double X_max, X_min, Y_max, Y_min; // Boundary coordinates

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
    void SetEncoderPosition(int id, float value);
    void ReadEncoderWhenSensorActive(int id);
    void OnDoneUpdateTracking();

signals:
    void GotResponse(QString deviceId, QString response);
};
#endif // TRACKINGMANAGER_H
