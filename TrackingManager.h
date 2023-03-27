#ifndef TRACKINGMANAGER_H
#define TRACKINGMANAGER_H

#include <QObject>

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

class TrackingManager : public QObject
{
    Q_OBJECT
public:
    explicit TrackingManager(QObject *parent = nullptr);

signals:

public slots:
    void OnReceivceEncoderPosition(int id, float value);

};

#endif // TRACKINGMANAGER_H
