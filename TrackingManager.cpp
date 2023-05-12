#include "TrackingManager.h"

Tracking::Tracking(QObject *parent)
    : QObject{parent}
{
    VirtualEncoderTimer = new QTimer(this);
    connect(VirtualEncoderTimer, SIGNAL(timeout()), this, SLOT(GetVirtualEncoderPosition()));
//    VirtualEncoderTimer->start(1000);
}

void Tracking::OnReceivceEncoderPosition(float value)
{
    if (std::isnan(value))
    {
        emit GotCaptureDetectOffset(QPointF(0, 0));
        return;
    }

    if (IsReverse == true)
    {
        value = value * - 1;
    }

    currentPosition = value;
    if (first == true)
    {
        first = false;
        lastPosition = value;
        return;
    }

    float distance = value - lastPosition;
    lastPosition = value;

    QPointF offset = calculateMoved(distance);
    emit DistanceMoved(offset);

    if (ReadPurpose == "Capture")
    {
        capturePosition = currentPosition;
        ReadPurpose = "Update";
    }
    else if (ReadPurpose == "Detect")
    {
        detectPosition = currentPosition;
        ReadPurpose = "Update";
        QPointF offset = calculateMoved(currentPosition - capturePosition);
        emit GotCaptureDetectOffset(offset);
    }
}

void Tracking::GetVirtualEncoderPosition()
{
    static QElapsedTimer timeForUpdate;

    float distance = VirtualEncoderVelocity * float(timeForUpdate.elapsed())/1000;

    VirtualEncoderPosition += distance;

    timeForUpdate.start();

    OnReceivceEncoderPosition(VirtualEncoderPosition);
}

void Tracking::ReadEncoder()
{
    QString encoderName = "encoder";
    encoderName = encoderName + QString::number(EncoderID);
    if (EncoderType == "Encoder X")
    {
        emit SendGcodeRequest(encoderName, "M317");
    }
    else if (EncoderType == "Sub Encoder")
    {
        emit SendGcodeRequest(encoderName, QString("M422 C%1").arg(EncoderID + 1));
    }
    else if (EncoderType == "Virtual Encoder")
    {

    }
}

void Tracking::SetEncoderReverse(bool isReverse)
{
    IsReverse = isReverse;
}

void Tracking::SaveCapturePosition()
{
    ReadPurpose = "Capture";
    ReadEncoder();
}

void Tracking::SaveDetectPosition()
{
    ReadPurpose = "Detect";
    ReadEncoder();
}

QPointF Tracking::calculateMoved(float distance)
{
    QPointF point3(0, 0);

    QLineF line;
    line.setP1(point3);
    line.setAngle(DeviationAngle);

    if (distance == 0)
    {
        return point3;
    }

    line.setLength(distance);

    float cosa = qCos(qDegreesToRadians(360 - DeviationAngle));
    float sina = qSin(qDegreesToRadians(360 - DeviationAngle));

    line.setP2(QPointF(distance * cosa, distance * sina));

    float p2X = ((float)((int)(line.p2().x() * 100))) / 100;
    float p2Y = ((float)((int)(line.p2().y() * 100))) / 100;

    return QPointF(p2X, p2Y);
}

TrackingObject::TrackingObject(int id, float x, float y, float w, float l, float angle, float startPos, float overlay)
{
    ID = id;
    StartX = X = x;
    StartY = Y = y;
    Width = w;
    Length = l;
    Angle = angle;
    CurrentEncoderPosition = StartEncoderPosition = startPos;
    Overlay = overlay;
}

bool TrackingObject::IsSame(TrackingObject other)
{
        if (abs(this->X - other.X) > this->Length * this->Overlay) {
            return false;
        }

        if (abs(this->Y - other.Y) > this->Length * this->Overlay) {
            return false;
        }

        return true;
}

TrackingManager::TrackingManager(QObject *parent)
{

}

void TrackingManager::SaveCapturePosition(int id)
{
    QMetaObject::invokeMethod(Trackings.at(id), "SaveCapturePosition", Qt::QueuedConnection);
}

void TrackingManager::SaveDetectPosition(int id)
{
    QMetaObject::invokeMethod(Trackings.at(id), "SaveDetectPosition", Qt::QueuedConnection);
}

void TrackingManager::UpdateTracking(int id)
{
    currentTrackingRequest = id;
    QMetaObject::invokeMethod(Trackings.at(id), "ReadEncoder", Qt::QueuedConnection);
}

void TrackingManager::SetEncoderPosition(int id, float value)
{
    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->EncoderID == id)
        {
            QMetaObject::invokeMethod(Trackings.at(i), "OnReceivceEncoderPosition", Qt::QueuedConnection, Q_ARG(float, value));
        }
    }
}

void TrackingManager::ReadEncoderWhenSensorActive(int id)
{

}

void TrackingManager::OnDoneUpdateTracking()
{
    emit GotResponse(QString("tracking") + QString::number(currentTrackingRequest), "Done");
}
