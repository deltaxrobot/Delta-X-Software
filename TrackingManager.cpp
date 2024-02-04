#include "TrackingManager.h"

Tracking::Tracking(QObject *parent)
    : QObject{parent}
{
    connect(&VirEncoder, &VirtualEncoder::positionUpdated, this, &Tracking::OnReceivceEncoderPosition);
}

void Tracking::UpdateTrackedObjectsPosition(float moved)
{
    for (ObjectInfo &object : TrackedObjects) {
        if (object.offset == QVector3D(0, 0, 0)) {
            QVector3D detectionPositionOffset = calculateMoved(detectPosition - capturePosition);
            object.offset = detectionPositionOffset;
            object.center += object.offset;
        }
        else
        {
            QVector3D conveyorPathTravelled = calculateMoved(moved);
            object.center += conveyorPathTravelled;
        }
    }
}

void Tracking::OnReceivceEncoderPosition(float value)
{
    if (IsReverse == true)
    {
        value = value * - 1;
    }

    lastPosition = currentPosition;
    currentPosition = value;

    if (ReadPurpose == "Capture")
    {
        capturePosition = detectPosition = currentPosition;
        ReadPurpose = "Update";
    }
    else if (ReadPurpose == "Detect")
    {
        detectPosition = currentPosition;
        ReadPurpose = "Update";
        UpdateTrackedObjects(DetectedObjects, ListName);
    }
    updatePositions(currentPosition - lastPosition);
//    UpdateTrackedObjectsPosition(currentPosition - lastPosition);
}

void Tracking::ChangeObjectInfo(QString cmd)
{
    QStringList paras1 = cmd.split('=');
    QStringList paras2 = paras1.at(0).trimmed().split('.');

    int i = paras1.at(1).toInt();

    if (paras2.at(2) == "IsPicked")
    {
        if (paras1.at(1).trimmed() == "True")
            TrackedObjects[i].isPicked = true;
        else
            TrackedObjects[i].isPicked = false;
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
        emit SendGcodeRequest(EncoderName, QString("M422 C%1").arg(EncoderName.mid(7).toInt() + 1));
    }
    else if (EncoderType == "Virtual Encoder")
    {
        GetVirtualEncoderPosition();
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

void Tracking::UpdateTrackedObjects(QList<ObjectInfo> detectedObjects, QString objectNameList) {

    if (objectNameList != ListName)
        return;

    if (ReadPurpose == "Detect")
    {
        // Copy detected objects vào DetectedObjects theo cách để dữ liệu không bị mất đi khi kết thúc hàm
        DetectedObjects = detectedObjects;
        return;
    }

    for (auto& detected : detectedObjects) {
        bool isTracked = false;
        double minSimilarity = 1e9;  // Initialize with a large value
        ObjectInfo* bestMatch = nullptr;

        for (auto& tracked : TrackedObjects) {
            double score = similarity(tracked, detected, displacement);

            if (score < minSimilarity) {
                minSimilarity = score;
                bestMatch = &tracked;
            }
        }

        if (minSimilarity < SimilarityThreshold /* Similarity threshold */) {
            // Update the tracked object's info
            bestMatch->center = detected.center;
            bestMatch->width = detected.width;
            bestMatch->height = detected.height;
            bestMatch->angle = detected.angle;
            isTracked = true;
        }

        if (!isTracked) {
            // This is a new object
            TrackedObjects.append(ObjectInfo(nextID, detected.center, detected.width, detected.height, detected.angle));

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
    QVector3D effectiveDisplacement = calculateMoved(displacement);

    for (auto it = TrackedObjects.begin(); it != TrackedObjects.end(); ) {
        if (!it->isPicked) {
            it->center += effectiveDisplacement;

            VariableManager::instance().updateVar((ListName + ".%1.X").arg(it->id), it->center.x());
            VariableManager::instance().updateVar((ListName + ".%1.Y").arg(it->id), it->center.y());

        }

        // Remove object if it goes out of boundary
        if (it->center.x() > X_max || it->center.x() < X_min || it->center.y() > Y_max || it->center.y() < Y_min) {
            it = TrackedObjects.erase(it);
        } else {
            ++it;
        }
    }
}

void Tracking::ClearTrackedObjects()
{
    for (int i = 0; i < TrackedObjects.count(); i++)
    {
        VariableManager::instance().removeVar((ListName + ".%1.X").arg(TrackedObjects.at(i).id));
        VariableManager::instance().removeVar((ListName + ".%1.Y").arg(TrackedObjects.at(i).id));
        VariableManager::instance().removeVar((ListName + ".%1.Z").arg(TrackedObjects.at(i).id));
        VariableManager::instance().removeVar((ListName + ".%1.W").arg(TrackedObjects.at(i).id));
        VariableManager::instance().removeVar((ListName + ".%1.L").arg(TrackedObjects.at(i).id));
        VariableManager::instance().removeVar((ListName + ".%1.A").arg(TrackedObjects.at(i).id));
        VariableManager::instance().removeVar((ListName + ".%1.IsPicked").arg(TrackedObjects.at(i).id));
    }
    VariableManager::instance().setVariable(ListName + ".Count", 0);
    TrackedObjects.clear();
    nextID = 0;


}

void Tracking::RemoveTrackedObjects(int id)
{

}

QVector3D Tracking::calculateMoved(float distance)
{
    // Normalize the VelocityVector to get the direction
    QVector3D direction = VelocityVector.normalized();

    // Calculate the effective 3D displacement vector
    QVector3D effectiveDisplacement = direction * distance;

    return effectiveDisplacement;
}


double Tracking::similarity(ObjectInfo &obj1, ObjectInfo &obj2, double displacement) {
    // Calculate effective 3D displacement based on conveyor 3D velocity
    QVector3D effectiveDisplacement = VelocityVector * displacement;

    // Predict new position of obj1 based on effective displacement
    QVector3D predictedCenter = obj1.center + effectiveDisplacement;

    // Calculate "error" based on distance from predicted position to obj2 position
    double positionError = (predictedCenter - obj2.center).length();

    double sizeDifference = std::abs(obj1.width * obj1.height - obj2.width * obj2.height);
//    double angleDifference = std::abs(obj1.angle - obj2.angle);

    // Compute a similarity score
    double score = positionError + sizeDifference;

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

void TrackingManager::UpdateVariable(QString cmd)
{
    QStringList paras1 = cmd.split('=');
    QStringList paras2 = paras1.at(0).split('.');

    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->ListName == paras2.at(0))
        {
            QMetaObject::invokeMethod(Trackings.at(i), "ChangeObjectInfo", Qt::QueuedConnection, Q_ARG(QString, cmd));
        }
    }
}

void TrackingManager::AddObject(QString listName, QList<QStringList> list)
{
    QList<ObjectInfo> objectList;
    // Duyệt qua từng phần tử của paras
    for (int i = 0; i < list.count(); i++)
    {
        QStringList paras = list.at(i);

        int id = 0;
        float x = 0;
        float y = 0;
        float z = 0;
        float w = 20;
        float l = 40;
        float a = 90;
        bool isPicked = false;

        for (int j = 0; j < paras.count(); j++)
        {
            if (j == 0)
            {
                id = paras.at(0).toInt();
            }
            else if (j == 1)
            {
                x = paras.at(1).toFloat();
            }
            else if (j == 2)
            {
                y = paras.at(2).toFloat();
            }
            else if (j == 3)
            {
                z = paras.at(3).toFloat();
            }
            else if (j == 4)
            {
                w = paras.at(4).toFloat();
            }
            else if (j == 5)
            {
                l = paras.at(5).toFloat();
            }
            else if (j == 6)
            {
                a = paras.at(6).toFloat();
            }
            else if (j == 7)
            {
                isPicked = paras.at(7).toInt();
            }
        }
        
        ObjectInfo obj(id, QVector3D(x, y, z), w, l, a, isPicked);

        objectList.append(obj);
    }

    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->ListName == listName)
        {
//            QMetaObject::invokeMethod(Trackings.at(i), "UpdateTrackedObjects", Qt::QueuedConnection, Q_ARG(QList<ObjectInfo>, objectList), Q_ARG(QString, listName));
        }
    }
}

void TrackingManager::ClearObjects(QString listName)
{
    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->ListName == listName)
        {
            QMetaObject::invokeMethod(Trackings.at(i), "ClearTrackedObjects", Qt::QueuedConnection);
        }
    }
}

void TrackingManager::SetEncoderPosition(int id, float value)
{
    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->EncoderName.mid(7).toInt() == id)
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
//    timer.start(100);  // Cập nhật vị trí mỗi 100 ms
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
