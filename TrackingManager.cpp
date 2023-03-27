#include "TrackingManager.h"

TrackingManager::TrackingManager(QObject *parent)
    : QObject{parent}
{

}

void TrackingManager::OnReceivceEncoderPosition(int id, float value)
{

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
