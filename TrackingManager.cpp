#include "TrackingManager.h"

Tracking::Tracking(QObject *parent)
    : QObject{parent}
{
    connect(&VirEncoder, &VirtualEncoder::positionUpdated, this, &Tracking::OnReceivceEncoderPosition);

    connect(this, &Tracking::UpdateVar, &VariableManager::instance(), &VariableManager::updateVar);
}

void Tracking::UpdateTrackedObjectsPosition(float moved)
{
    // Thread-safe update of TrackedObjects
    QMutexLocker locker(&dataMutex);
    
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
//    qDebug() << "Response: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
//    qDebug() << "Encoder: " << value;

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
        UpdateTrackedObjectOffsets(calculateMoved(detectPosition - capturePosition));
    }

    updatePositions(currentPosition - lastPosition);

    if (clientWaiting == true)
    {
        emit UpdateTrackingDone();
        clientWaiting = false;
    }
}

void Tracking::ChangeObjectInfo(QString cmd)
{
    QStringList paras1 = cmd.split('=');
    QStringList paras2 = paras1.at(0).trimmed().split('.');


    int i = paras1.at(1).toInt();

    if (paras2.count() >= 3)
    {
        if (paras2.at(2) == "IsPicked")
        {
            QString objName = paras2.at(0) + paras2.at(1);

            int i = VariableManager::instance().getVar(QString("project0.tracking0.") + objName + ".UID").toInt();

            // Thread-safe update of TrackedObjects
            {
                QMutexLocker locker(&dataMutex);
                if (i >= 0 && i < TrackedObjects.size()) {
                    if (paras1.at(1).trimmed().toLower() == "true")
                        TrackedObjects[i].isPicked = true;
                    else
                        TrackedObjects[i].isPicked = false;
                }
            }
        }
    }
}

void Tracking::GetVirtualEncoderPosition()
{
    OnReceivceEncoderPosition(VirEncoder.readPosition());
}

void Tracking::ReadEncoder()
{
    if (EncoderType == "X Encoder")
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

void Tracking::UpdateTrackedObjects(QVector<ObjectInfo> detectedObjects, QString objectNameList) {

    if (objectNameList != ListName)
        return;

    // Thread-safe update of DetectedObjects
    {
        QMutexLocker locker(&dataMutex);
        DetectedObjects = detectedObjects;
    }
    
    SaveDetectPosition();
//    qDebug() << "Detect: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

}

void Tracking::UpdateTrackedObjectOffsets(QVector3D offset)
{
    // Create working copy to avoid race conditions
    QVector<ObjectInfo> workingDetectedObjects;
    
    {
        QMutexLocker locker(&dataMutex);
        workingDetectedObjects = DetectedObjects;
    }

    for (auto& detected : workingDetectedObjects) {
        bool isSame = false;

        detected.center += offset;
        detected.offset = offset;

        for (auto& tracked : TrackedObjects) {
            isSame = isSameObject(detected, tracked);

            if (isSame == true)
                break;
        }

        if (isSame == true)
            continue;

        // This is a new object - Thread-safe append
        {
            QMutexLocker locker(&dataMutex);
            TrackedObjects.append(ObjectInfo(nextID, detected.type, detected.center, detected.width, detected.height, detected.angle));
            ++nextID;
        }

        //TODO: tim cach cap nhat vao bien nhung van dam bao toc do
//        VariableManager::instance().updateVar((ListName + ".%1.X").arg(nextID), detected.center.x());
//        VariableManager::instance().updateVar((ListName + ".%1.Y").arg(nextID), detected.center.y());
//        VariableManager::instance().updateVar((ListName + ".%1.Z").arg(nextID), detected.center.z());
//        VariableManager::instance().updateVar((ListName + ".%1.W").arg(nextID), detected.width);
//        VariableManager::instance().updateVar((ListName + ".%1.L").arg(nextID), detected.height);
//        VariableManager::instance().updateVar((ListName + ".%1.A").arg(nextID), detected.angle);
//        VariableManager::instance().updateVar((ListName + ".%1.IsPicked").arg(nextID), detected.isPicked);
//        VariableManager::instance().updateVar((ListName + ".%1.Offset").arg(nextID), detected.offset);

//        emit UpdateVar((ListName + ".%1.X").arg(nextID), detected.center.x());
//        emit UpdateVar((ListName + ".%1.Y").arg(nextID), detected.center.y());
//        emit UpdateVar((ListName + ".%1.Z").arg(nextID), detected.center.z());
//        emit UpdateVar((ListName + ".%1.W").arg(nextID), detected.width);
//        emit UpdateVar((ListName + ".%1.L").arg(nextID), detected.height);
//        emit UpdateVar((ListName + ".%1.A").arg(nextID), detected.angle);
//        emit UpdateVar((ListName + ".%1.IsPicked").arg(nextID), detected.isPicked);
//        emit UpdateVar((ListName + ".%1.Offset").arg(nextID), detected.offset);

        VariableManager::instance().updateVar(ListName + ".Count", nextID);

    }

}

void Tracking::GetObjectsInArea(QString inAreaListName, float min, float max, bool isXdirection)
{
    // Create working copy to avoid race conditions
    QVector<ObjectInfo> workingTrackedObjects;
    
    {
        QMutexLocker locker(&dataMutex);
        workingTrackedObjects = TrackedObjects;
    }

    int index = 0;
    for (auto& tracked : workingTrackedObjects)
    {
        if (isXdirection == true)
        {
            if (tracked.center.x() < min || tracked.center.x() > max)
                continue;
        }
        else
        {
            if (tracked.center.y() < min || tracked.center.y() > max)
                continue;
        }

        if (tracked.isPicked == true)
            continue;

        QString name = inAreaListName + '.' + QString::number(index);

        VariableManager::instance().updateVar(name + ".X", tracked.center.x());
        VariableManager::instance().updateVar(name + ".Y", tracked.center.y());
        VariableManager::instance().updateVar(name + ".IsPicked", tracked.isPicked);
        VariableManager::instance().updateVar(name + ".Type", tracked.type);
        VariableManager::instance().updateVar(name + ".UID", tracked.id);
        VariableManager::instance().updateVar(inAreaListName + ".Count", index + 1);
        index++;
    }
}

void Tracking::updatePositions(double displacement) {
    QVector3D effectiveDisplacement = calculateMoved(displacement);

    if (IsUpateTestPoint)
    {
        TestPointOffset = effectiveDisplacement;
        emit TestPointUpdated(TestPointOffset);
    }

    // Thread-safe update and erase with mutex protection
    {
        QMutexLocker locker(&dataMutex);
        TrackedObjects.erase(std::remove_if(TrackedObjects.begin(), TrackedObjects.end(),
            [&](auto& obj) {
                if (!obj.isPicked) {
                    obj.center += effectiveDisplacement;

    //                QString xVarName = ListName + "." + QString::number(obj.id) + ".X";
    //                QString yVarName = ListName + "." + QString::number(obj.id) + ".Y";

                    //TODO: tim cach cap nhat vao bien nhung van dam bao toc do
    //                emit UpdateVar(xVarName, obj.center.x());
    //                emit UpdateVar(yVarName, obj.center.y());
                }

                return obj.center.x() > X_max || obj.center.x() < X_min || obj.center.y() > Y_max || obj.center.y() < Y_min;
            }),
            TrackedObjects.end());
    }

//    for (auto it = TrackedObjects.begin(); it != TrackedObjects.end(); ) {
//        if (!it->isPicked) {
//            it->center += effectiveDisplacement;

//            QString xVarName = ListName + "." + QString::number(it->id) + ".X";
//            QString yVarName = ListName + "." + QString::number(it->id) + ".Y";

//            VariableManager::instance().updateVar(xVarName, it->center.x());
//            VariableManager::instance().updateVar(yVarName, it->center.y());
//        }

//        if (it->center.x() > X_max || it->center.x() < X_min || it->center.y() > Y_max || it->center.y() < Y_min) {
//            it = TrackedObjects.erase(it);
//        } else {
//            ++it;
//        }
//    }
}

void Tracking::ClearTrackedObjects()
{
//    for (int i = 0; i < TrackedObjects.count(); i++)
//    {
//        VariableManager::instance().removeVar((ListName + ".%1.X").arg(TrackedObjects.at(i).id));
//        VariableManager::instance().removeVar((ListName + ".%1.Y").arg(TrackedObjects.at(i).id));
//        VariableManager::instance().removeVar((ListName + ".%1.Z").arg(TrackedObjects.at(i).id));
//        VariableManager::instance().removeVar((ListName + ".%1.W").arg(TrackedObjects.at(i).id));
//        VariableManager::instance().removeVar((ListName + ".%1.L").arg(TrackedObjects.at(i).id));
//        VariableManager::instance().removeVar((ListName + ".%1.A").arg(TrackedObjects.at(i).id));
//        VariableManager::instance().removeVar((ListName + ".%1.IsPicked").arg(TrackedObjects.at(i).id));
//    }
    
    // Thread-safe clear
    {
        QMutexLocker locker(&dataMutex);
        TrackedObjects.clear();
        nextID = 0;
    }
    
    VariableManager::instance().updateVar(ListName + ".Count", 0);
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

double Tracking::calculateIoU(ObjectInfo &object1, ObjectInfo &object2)
{
    // 1. Calculate overlap area
    double x_overlap = std::max(0.0, std::min(object1.center.x() + object1.width / 2, object2.center.x() + object2.width / 2) -
                                      std::max(object1.center.x() - object1.width / 2, object2.center.x() - object2.width / 2));
    double y_overlap = std::max(0.0, std::min(object1.center.y() + object1.height / 2, object2.center.y() + object2.height / 2) -
                                      std::max(object1.center.y() - object1.height / 2, object2.center.y() - object2.height / 2));
    double overlapArea = x_overlap * y_overlap;

    // 2. Calculate union area
    double box1Area = object1.width * object1.height;
    double box2Area = object2.width * object2.height;
    double unionArea = box1Area + box2Area - overlapArea;

    // 3. Calculate IoU
    double iou = overlapArea / unionArea;

    return iou;
}

bool Tracking::isSameObject(ObjectInfo &object1, ObjectInfo &object2)
{
    // 1. Kiểm tra IoU
    double iou = calculateIoU(object1, object2);
    if (iou >= IoUThreshold) {
        return true;
    }

    // 2. Kiểm tra khoảng cách
    double distance = object1.center.distanceToPoint(object2.center);
    if (distance <= DistanceThreshold) {
        return true;
    }

    // 3. Kiểm tra các yếu tố khác (tùy chọn)
    // ...

    return false;
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
    Trackings.at(id)->clientWaiting = true;
    QMetaObject::invokeMethod(Trackings.at(id), "ReadEncoder", Qt::QueuedConnection);
}

void TrackingManager::GetObjectsInArea(int trackingID, QString inAreaListName, float min, float max, bool isXDirection)
{
    Trackings.at(trackingID)->GetObjectsInArea(inAreaListName, min, max, isXDirection);

    emit GotResponse(QString("tracking") + QString::number(trackingID), "Done");
}

void TrackingManager::UpdateVariable(QString cmd)
{
    QStringList paras1 = cmd.split('=');
    QStringList paras2 = paras1.at(0).split('.');

    QMetaObject::invokeMethod(Trackings.at(0), "ChangeObjectInfo", Qt::QueuedConnection, Q_ARG(QString, cmd));

//    for(int i = 0; i < Trackings.count(); i++)
//    {
//        if (Trackings.at(i)->ListName == paras2.at(0))
//        {
//            QMetaObject::invokeMethod(Trackings.at(i), "ChangeObjectInfo", Qt::QueuedConnection, Q_ARG(QString, cmd));
//        }
//    }
}

void TrackingManager::AddObject(QString listName, QList<QStringList> list)
{
    QVector<ObjectInfo> objectList;
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
        
        ObjectInfo obj(id, 0, QVector3D(x, y, z), w, l, a, isPicked);

        objectList.append(obj);
    }

    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->ListName == listName)
        {
            QMetaObject::invokeMethod(Trackings.at(i), "UpdateTrackedObjects", Qt::QueuedConnection, Q_ARG(QVector<ObjectInfo>, objectList), Q_ARG(QString, listName));
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
//            QMetaObject::invokeMethod(Trackings.at(i), "OnReceivceEncoderPosition", Qt::QueuedConnection, Q_ARG(float, value));
            Trackings.at(i)->OnReceivceEncoderPosition(value);
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

void VirtualEncoder::setPosition(float newPos)
{
    currentPosition = newPos;
}

void VirtualEncoder::stop() {
    timer.stop();
    isRun = false;
}

void VirtualEncoder::start(int interval) {
    lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
    timer.setInterval(interval);
    timer.start();
    isRun = true;
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

int VirtualEncoder::readInterval()
{
    return timer.interval();
}

bool VirtualEncoder::IsActive()
{
    return isRun;
}
