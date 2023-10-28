#include "TrackingManager.h"

Tracking::Tracking(QObject *parent)
    : QObject{parent}
{
    connect(&VirEncoder, &VirtualEncoder::positionUpdated, this, &Tracking::OnReceivceEncoderPosition);
}

void Tracking::OnReceivceEncoderPosition(float value)
{
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

    float distance = currentPosition - lastPosition;
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
    }
}

void Tracking::GetVirtualEncoderPosition()
{
    OnReceivceEncoderPosition(VirEncoder.readPosition());
}

void Tracking::ReadEncoder()
{
    if (EncoderType == "Encoder X")
    {
        emit SendGcodeRequest(EncoderName, "M317");
    }
    else if (EncoderType == "Sub Encoder")
    {
        emit SendGcodeRequest(EncoderName, QString("M422 C%1").arg(EncoderName.replace("encoder", "").toInt() + 1));
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

void Tracking::UpdateTrackedObjects(QList<ObjectInfo> detectedObjects, double displacement) {
    for (auto& detected : detectedObjects) {
        bool isTracked = false;
        double minSimilarity = 1e9;  // Initialize with a large value
        ObjectInfo* bestMatch = nullptr;

        for (auto& tracked : trackedObjects) {
            double score = similarity(tracked, detected, displacement);

            if (score < minSimilarity) {
                minSimilarity = score;
                bestMatch = &tracked;
            }
        }

        if (minSimilarity < 50 /* Similarity threshold */) {
            // Update the tracked object's info
            bestMatch->center = detected.center;
            bestMatch->width = detected.width;
            bestMatch->height = detected.height;
            bestMatch->angle = detected.angle;
            isTracked = true;
        }

        if (!isTracked) {
            // This is a new object
            trackedObjects.append(ObjectInfo(nextID, detected.center, detected.width, detected.height, detected.angle));

            VariableManager::instance().addVar((ListName + ".%1.X").arg(nextID), detected.center.x());
            VariableManager::instance().addVar((ListName + ".%1.Y").arg(nextID), detected.center.y());
            VariableManager::instance().addVar((ListName + ".%1.Z").arg(nextID), detected.center.z());
            VariableManager::instance().addVar((ListName + ".%1.W").arg(nextID), detected.width);
            VariableManager::instance().addVar((ListName + ".%1.L").arg(nextID), detected.height);
            VariableManager::instance().addVar((ListName + ".%1.A").arg(nextID), detected.angle);
            VariableManager::instance().addVar((ListName + ".%1.IsPicked").arg(nextID), detected.isPicked);

            ++nextID;

            VariableManager::instance().addVar(ListName + ".Count", nextID);
        }
    }
}

void Tracking::updatePositions(double displacement) {
    QVector3D effectiveDisplacement = VelocityVector * displacement;

    for (auto it = trackedObjects.begin(); it != trackedObjects.end(); ) {
        if (!it->isPicked) {
            it->center += effectiveDisplacement;
        }

        // Remove object if it goes out of boundary
        if (it->center.x() > X_max || it->center.x() < X_min || it->center.y() > Y_max || it->center.y() < Y_min) {
            it = trackedObjects.erase(it);
        } else {
            ++it;
        }
    }
}

QPointF Tracking::calculateMoved(float distance)
{
    QVector2D direction = QVector2D(VelocityVector.x(), VelocityVector.y()).normalized();

    // Calculate the effective 2D displacement vector
    QVector2D effectiveDisplacement = direction * distance;

    return effectiveDisplacement.toPointF();
}

double Tracking::similarity(ObjectInfo &obj1, ObjectInfo &obj2, double displacement) {
    // Calculate effective 3D displacement based on conveyor 3D velocity
    QVector3D effectiveDisplacement = VelocityVector * displacement;

    // Predict new position of obj1 based on effective displacement
    QVector3D predictedCenter = obj1.center + effectiveDisplacement;

    // Calculate "error" based on distance from predicted position to obj2 position
    double positionError = (predictedCenter - obj2.center).length();

    double sizeDifference = std::abs(obj1.width * obj1.height - obj2.width * obj2.height);
    double angleDifference = std::abs(obj1.angle - obj2.angle);

    // Compute a similarity score
    double score = positionError + sizeDifference + angleDifference;

    return score;
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
        if (Trackings.at(i)->EncoderName.replace("encoder", "").toInt() == id)
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

VirtualEncoder::VirtualEncoder(float initialPosition, float velocity, QObject *parent)
    : QObject(parent), currentPosition(initialPosition), velocity(velocity) {
    lastUpdateTime = QDateTime::currentMSecsSinceEpoch();

    connect(&timer, &QTimer::timeout, this, &VirtualEncoder::updatePosition);
    timer.start(100);  // Cập nhật vị trí mỗi 100 ms
}

void VirtualEncoder::setVelocity(float newVelocity) {
    velocity = newVelocity;
}

void VirtualEncoder::stop() {
    timer.stop();
}

void VirtualEncoder::start(int interval) {
    lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
    timer.start(interval);
}

void VirtualEncoder::reset()
{
    lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
    currentPosition = 0;
    emit positionUpdated(currentPosition);
}

void VirtualEncoder::updatePosition() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 deltaTime = currentTime - lastUpdateTime;  // Đơn vị: ms
    lastUpdateTime = currentTime;

    // Cập nhật vị trí dựa trên vận tốc và thời gian đã trôi qua
    currentPosition += velocity * (deltaTime / 1000.0);

    emit positionUpdated(currentPosition);
}

float VirtualEncoder::readPosition() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 deltaTime = currentTime - lastUpdateTime;  // Đơn vị: ms
    lastUpdateTime = currentTime;

    // Cập nhật vị trí dựa trên vận tốc và thời gian đã trôi qua
    currentPosition += velocity * (deltaTime / 1000.0);

    return currentPosition;
}
