#ifndef TRACKINGMANAGER_H
#define TRACKINGMANAGER_H

#include <QObject>
#include <QPointF>
#include <QLineF>
#include <QtMath>
#include <QElapsedTimer>
#include <QTimer>
#include <QDebug>

class TrackingObject
{
public:
    TrackingObject(int id = -1, float x = 0, float y = 0, float w = 50, float l = 80, float angle = 0, float startPos = 0, float overlay = 1);
    int ID;
    float StartX;
    float StartY;
    float X;
    float Y;
    float Width;
    float Length;
    float Angle;
    float StartEncoderPosition;
    float CurrentEncoderPosition;
    float Overlay;

    bool IsSame(TrackingObject other);
};

class Tracking : public QObject
{
    Q_OBJECT
public:
    explicit Tracking(QObject *parent = nullptr);

    float DeviationAngle = 0;
    int EncoderID = 0;
    QString EncoderType = "Encoder X";
    bool IsReverse = false;
    QString ListName = "#Objects";
    QPointF* DetectDelayOffsetPoint = NULL;

    QTimer* VirtualEncoderTimer;
    float VirtualEncoderPosition = 0;
    float VirtualEncoderVelocity = 100;

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

private:
    QPointF calculateMoved(float distance);
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
    void SetEncoderPosition(int id, float value);
    void ReadEncoderWhenSensorActive(int id);
    void OnDoneUpdateTracking();

signals:
    void GotResponse(QString deviceId, QString response);
};
#endif // TRACKINGMANAGER_H
