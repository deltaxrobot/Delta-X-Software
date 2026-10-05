#include "TrackingManager.h"
#include <QMetaType>
#include <limits>
#include <cmath>

Tracking::Tracking(QObject *parent)
    : QObject{parent}
{
    // Ensure ObjectInfo types are registered for queued connections
    qRegisterMetaType<ObjectInfo>("ObjectInfo");
    qRegisterMetaType<QVector<ObjectInfo>>("QVector<ObjectInfo>");
    connect(&VirEncoder, &VirtualEncoder::positionUpdated, this, &Tracking::OnReceivceEncoderPosition);

    monotonicClock.start();
    lastDetectionTimer.invalidate();
    lastEncoderTimer.invalidate();
    lastPublicationTimer.invalidate();
    realtimeMonitorTimer = new QTimer(this);
    realtimeMonitorTimer->setTimerType(Qt::PreciseTimer);
    connect(realtimeMonitorTimer, &QTimer::timeout, this, [this]() {
        publishTrackedObjectsSnapshot(false);
    });
}

void Tracking::MoveToThread(QThread* targetThread)
{
    if (!targetThread || thread() == targetThread)
        return;
    VirEncoder.MoveToThread(targetThread);
    QObject::moveToThread(targetThread);
}

QString Tracking::GetListName() const
{
    QMutexLocker locker(&dataMutex);
    return ListName;
}

QString Tracking::GetEncoderName() const
{
    QMutexLocker locker(&dataMutex);
    return EncoderName;
}

QString Tracking::GetVectorName() const
{
    QMutexLocker locker(&dataMutex);
    return VectorName;
}

float Tracking::GetIoUThreshold() const
{
    QMutexLocker locker(&dataMutex);
    return IoUThreshold;
}

float Tracking::GetDistanceThreshold() const
{
    QMutexLocker locker(&dataMutex);
    return DistanceThreshold;
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

    PendingEncoderRead completedRead;
    bool hasCompletedRead = false;
    float positionDelta = 0.0f;
    bool isVirtualEncoder = false;
    {
        QMutexLocker locker(&dataMutex);
        if (IsReverse)
            value = -value;
        isVirtualEncoder = EncoderType == QStringLiteral("Virtual Encoder");
        lastEncoderTimer.restart();
        lastEncoderAtMonotonicMs = monotonicClock.elapsed();
        encoderSamples++;

        lastPosition = currentPosition;
        currentPosition = value;
        positionDelta = currentPosition - lastPosition;

        if (!pendingEncoderReads.isEmpty()) {
            completedRead = pendingEncoderReads.dequeue();
            hasCompletedRead = true;
        }

        if (hasCompletedRead && completedRead.frameId != 0) {
            for (PendingFrame& frame : pendingFrames) {
                if (frame.id != completedRead.frameId)
                    continue;

                if (completedRead.purpose == EncoderReadPurpose::Capture) {
                    frame.capturePosition = currentPosition;
                    frame.hasCapturePosition = true;
                } else if (completedRead.purpose == EncoderReadPurpose::Detect) {
                    frame.detectPosition = currentPosition;
                    frame.hasDetectPosition = true;
                }
                break;
            }
        }
    }

    // Encoder movement remains authoritative even when vision is stale. Claims
    // are blocked by health status, but live tracks must not freeze and later
    // duplicate when the camera recovers.
    updatePositions(positionDelta);
    tryCommitFrames();

    if (isVirtualEncoder)
        emit VirtualEncoderPositionUpdated(ID, value);

    if (hasCompletedRead && completedRead.notifyClient) {
        emit UpdateTrackingDone(ID);
        emit UpdateTrackingDone();
        clientWaiting = false;
    }
}

// Wrapper with correct spelling; delegates to existing implementation
void Tracking::OnReceiveEncoderPosition(float value)
{
    OnReceivceEncoderPosition(value);
}

void Tracking::ChangeObjectInfo(QString cmd)
{
    QStringList paras1 = cmd.split('=');
    QStringList paras2 = paras1.at(0).trimmed().split('.');

    if (paras2.count() >= 3)
    {
        if (paras2.at(2) == "IsPicked")
        {
            // Resolve UID by using the current list name and index from the command instead of hardcoded project path
            QString listName = paras2.at(0);
            QString indexStr = paras2.at(1);
            int uidValue = VariableManager::instance().getVarScoped(
                               ProjectName, listName + "." + indexStr + ".UID").toInt();

            // Thread-safe update of TrackedObjects
            {
                QMutexLocker locker(&dataMutex);
                QString val = paras1.at(1).trimmed().toLower();
                bool picked = (val == "true" || val == "1");
                for (auto &obj : TrackedObjects) {
                    if (obj.uid == uidValue) {
                        obj.isPicked = picked;
                        break;
                    }
                }
            }
            publishTrackedObjectsSnapshot();
        }
    }
}

void Tracking::GetVirtualEncoderPosition()
{
    OnReceivceEncoderPosition(VirEncoder.readPosition());
}

void Tracking::ReadEncoder()
{
    if (requestEncoderRead(EncoderReadPurpose::Update, 0, clientWaiting))
        return;

    if (clientWaiting) {
        emit UpdateTrackingDone(ID);
        emit UpdateTrackingDone();
        clientWaiting = false;
    }
}

bool Tracking::requestEncoderRead(EncoderReadPurpose purpose, quint64 frameId,
                                  bool notifyClient)
{
    QString encoderType;
    QString encoderName;
    {
        QMutexLocker locker(&dataMutex);
        if (pendingEncoderReads.size() >= maxPendingEncoderReads) {
            encoderQueueOverflows++;
            lastRealtimeFault = QStringLiteral("ENCODER_QUEUE_OVERFLOW");
            return false;
        }
        PendingEncoderRead request;
        request.purpose = purpose;
        request.frameId = frameId;
        request.notifyClient = notifyClient;
        pendingEncoderReads.enqueue(request);
        encoderType = EncoderType;
        encoderName = EncoderName;
    }

    if (encoderType == "X Encoder")
    {
        emit SendGcodeRequest(encoderName, "M317");
    }
    else if (encoderType == "Sub Encoder")
    {
        emit SendGcodeRequest(encoderName,
                              QString("M422 C%1").arg(encoderName.mid(7).toInt() + 1));
    }
    else if (encoderType == "Virtual Encoder")
    {
        GetVirtualEncoderPosition();
    }
    return true;
}

void Tracking::SetEncoderReverse(bool isReverse)
{
    QMutexLocker locker(&dataMutex);
    IsReverse = isReverse;
}

void Tracking::SetAssociationThresholds(float iouThreshold, float distanceThreshold)
{
    QMutexLocker locker(&dataMutex);
    IoUThreshold = qBound(0.0f, iouThreshold, 1.0f);
    DistanceThreshold = qMax(0.0f, distanceThreshold);
}

void Tracking::SetTrackingBounds(float minX, float maxX, float minY, float maxY)
{
    QMutexLocker locker(&dataMutex);
    X_min = qMin(minX, maxX);
    X_max = qMax(minX, maxX);
    Y_min = qMin(minY, maxY);
    Y_max = qMax(minY, maxY);
}

void Tracking::SetListName(QString listName)
{
    listName = listName.trimmed();
    if (listName.isEmpty())
        return;
    QMutexLocker locker(&dataMutex);
    ListName = listName;
}

void Tracking::SetEncoderName(QString encoderName)
{
    encoderName = encoderName.trimmed();
    if (encoderName.isEmpty())
        return;
    QMutexLocker locker(&dataMutex);
    EncoderName = encoderName;
}

void Tracking::SetVectorName(QString vectorName)
{
    vectorName = vectorName.trimmed();
    if (vectorName.isEmpty())
        return;
    QMutexLocker locker(&dataMutex);
    VectorName = vectorName;
}

void Tracking::SetEncoderSourceType(QString encoderType)
{
    encoderType = encoderType.trimmed();
    {
        QMutexLocker locker(&dataMutex);
        EncoderType = encoderType;
    }
    if (encoderType == QStringLiteral("Virtual Encoder"))
        VirEncoder.start();
    else
        VirEncoder.stop();
}

void Tracking::StartVirtualEncoder(int interval)
{
    VirEncoder.start(qMax(1, interval));
}

void Tracking::StopVirtualEncoder()
{
    VirEncoder.stop();
}

void Tracking::ResetVirtualEncoder()
{
    VirEncoder.reset();
}

void Tracking::SetVirtualEncoderVelocity(float velocity)
{
    if (qIsFinite(velocity))
        VirEncoder.setVelocity(velocity);
}

void Tracking::SetVirtualEncoderPosition(float position)
{
    if (qIsFinite(position))
        VirEncoder.setPosition(position);
}

void Tracking::SetUpdateTestPoint(bool enabled)
{
    QMutexLocker locker(&dataMutex);
    IsUpateTestPoint = enabled;
}

void Tracking::SaveCapturePosition()
{
    SaveCapturePosition(0, 0);
}

void Tracking::SaveCapturePosition(quint64 frameId, quint64 requestId)
{
    QVector<PendingFrame> expiredFrames;
    QString rejection;
    {
        QMutexLocker locker(&dataMutex);
        expiredFrames = purgeExpiredFramesLocked(monotonicClock.elapsed());

        if (pendingFrames.size() >= maxPendingFrames) {
            frameQueueOverflows++;
            framesRejected++;
            lastRealtimeFault = QStringLiteral("FRAME_QUEUE_OVERFLOW");
            rejection = QStringLiteral("Tracking frame queue is full");
        } else if (pendingEncoderReads.size() >= maxPendingEncoderReads) {
            encoderQueueOverflows++;
            framesRejected++;
            lastRealtimeFault = QStringLiteral("ENCODER_QUEUE_OVERFLOW");
            rejection = QStringLiteral("Tracking encoder request queue is full");
        }

        if (!rejection.isEmpty())
            frameId = frameId == 0 ? nextFrameId++ : frameId;

        if (rejection.isEmpty()) {
            PendingFrame frame;
            frame.id = frameId == 0 ? nextFrameId++ : frameId;
            frame.requestId = requestId;
            nextFrameId = std::max(nextFrameId, frame.id + 1);
            frame.createdAtMonotonicMs = monotonicClock.elapsed();
            frameId = frame.id;
            pendingFrames.enqueue(frame);
            framesCaptured++;
        }
    }
    emitRejectedFrames(expiredFrames, QStringLiteral("Tracking frame timed out"));
    if (!rejection.isEmpty()) {
        emit DetectionFrameRejected(ID, frameId, requestId, rejection);
        publishTrackedObjectsSnapshot(true);
        return;
    }
    if (!requestEncoderRead(EncoderReadPurpose::Capture, frameId)) {
        RejectPendingFrame(frameId, requestId,
                           QStringLiteral("Tracking encoder request queue is full"));
    }
}

void Tracking::SaveDetectPosition()
{
    quint64 frameId = 0;
    {
        QMutexLocker locker(&dataMutex);
        for (PendingFrame& frame : pendingFrames) {
            if (frame.hasDetections && !frame.detectReadRequested) {
                frame.detectReadRequested = true;
                frameId = frame.id;
                break;
            }
        }
    }
    if (frameId != 0 &&
        !requestEncoderRead(EncoderReadPurpose::Detect, frameId)) {
        RejectPendingFrame(frameId, 0,
                           QStringLiteral("Tracking encoder request queue is full"));
    }
}

void Tracking::UpdateTrackedObjects(QVector<ObjectInfo> detectedObjects, QString objectNameList) {

    if (objectNameList != ListName)
        return;

    bool pairedWithCapture = false;
    QVector<PendingFrame> expiredFrames;
    {
        QMutexLocker locker(&dataMutex);
        DetectedObjects = detectedObjects;
        expiredFrames = purgeExpiredFramesLocked(monotonicClock.elapsed());

        for (PendingFrame& frame : pendingFrames) {
            if (!frame.hasDetections) {
                frame.detections = detectedObjects;
                frame.hasDetections = true;
                pairedWithCapture = true;
                break;
            }
        }
    }
    emitRejectedFrames(expiredFrames, QStringLiteral("Tracking frame timed out"));

    if (pairedWithCapture) {
        SaveDetectPosition();
        tryCommitFrames();
        return;
    }

    // External conveyor-space detections and unit-test injections do not have
    // a camera capture event. They are already expressed at the current belt
    // position, so commit them with zero capture-to-detect offset.
    PendingFrame immediateFrame;
    {
        QMutexLocker locker(&dataMutex);
        immediateFrame.id = nextFrameId++;
        immediateFrame.createdAtMonotonicMs = monotonicClock.elapsed();
        immediateFrame.hasCapturePosition = true;
        immediateFrame.capturePosition = currentPosition;
        immediateFrame.hasDetections = true;
        immediateFrame.detections = detectedObjects;
        immediateFrame.detectReadRequested = true;
        immediateFrame.hasDetectPosition = true;
        immediateFrame.detectPosition = currentPosition;
    }
    commitDetectionFrame(immediateFrame);
}

void Tracking::UpdateTrackedObjectsForFrame(QVector<ObjectInfo> detectedObjects,
                                            quint64 frameId, quint64 requestId)
{
    bool found = false;
    QVector<PendingFrame> expiredFrames;
    {
        QMutexLocker locker(&dataMutex);
        expiredFrames = purgeExpiredFramesLocked(monotonicClock.elapsed());
        for (PendingFrame& frame : pendingFrames) {
            if (frame.id != frameId || frame.requestId != requestId)
                continue;
            if (frame.hasDetections)
                break;
            frame.detections = detectedObjects;
            frame.hasDetections = true;
            frame.detectReadRequested = true;
            DetectedObjects = detectedObjects;
            found = true;
            break;
        }
        if (!found) {
            framesRejected++;
            lastRealtimeFault = QStringLiteral("UNMATCHED_VISION_FRAME");
        }
    }
    emitRejectedFrames(expiredFrames, QStringLiteral("Tracking frame timed out"));

    if (!found) {
        emit DetectionFrameRejected(ID, frameId, requestId,
                                    QStringLiteral("No matching pending capture frame"));
        return;
    }

    if (!requestEncoderRead(EncoderReadPurpose::Detect, frameId)) {
        RejectPendingFrame(frameId, requestId,
                           QStringLiteral("Tracking encoder request queue is full"));
        return;
    }
    tryCommitFrames();
}

void Tracking::RejectPendingFrame(quint64 frameId, quint64 requestId, QString reason)
{
    bool removed = false;
    {
        QMutexLocker locker(&dataMutex);
        for (int index = 0; index < pendingFrames.size(); ++index) {
            const PendingFrame& frame = pendingFrames.at(index);
            if (frame.id == frameId && frame.requestId == requestId) {
                pendingFrames.removeAt(index);
                removed = true;
                framesRejected++;
                break;
            }
        }
        // Keep already-issued encoder reads as FIFO tombstones. Removing one
        // would make the next physical encoder response attach to a later frame.
    }
    if (removed || requestId != 0)
        emit DetectionFrameRejected(ID, frameId, requestId, reason);
}

void Tracking::UpdateTrackedObjectOffsets(QVector3D offset)
{
    const qint64 nowEpochMs = QDateTime::currentMSecsSinceEpoch();
    const qint64 nowMonotonicMs = monotonicClock.elapsed();
    {
        QMutexLocker locker(&dataMutex);
        associateDetectionsLocked(DetectedObjects, offset, nowEpochMs, nowMonotonicMs);
        lastDetectionAtMonotonicMs = nowMonotonicMs;
        lastDetectionTimer.restart();
    }

    publishTrackedObjectsSnapshot(true);
}

void Tracking::publishTrackedObjectsSnapshot(bool force)
{
    QMutexLocker publicationLocker(&publicationMutex);
    int intervalMs = 0;
    {
        QMutexLocker locker(&dataMutex);
        intervalMs = publishIntervalMs;
    }
    if (!force && intervalMs > 0 && lastPublicationTimer.isValid() &&
        lastPublicationTimer.elapsed() < intervalMs) {
        QMutexLocker locker(&dataMutex);
        publicationSuppressed++;
        return;
    }

    QElapsedTimer publishDuration;
    publishDuration.start();
    QVector<ObjectInfo> objects;
    QVariantMap realtime;
    {
        QMutexLocker locker(&dataMutex);
        objects = TrackedObjects;
        publicationCount++;
        realtime = realtimeSnapshotLocked(monotonicClock.elapsed());
    }

    VariableManager& variables = VariableManager::instance();
    variables.updateObjectSnapshot(ProjectName, ListName, objects);

    for (int i = objects.size(); i < publishedObjectCount; ++i)
        variables.removeVarScoped(ProjectName, ListName + '.' + QString::number(i));

    QHash<QString, QVariant> values;
    values.reserve(objects.size() * 21 + 1);
    for (int i = 0; i < objects.size(); ++i) {
        const ObjectInfo& object = objects.at(i);
        const QString name = ListName + '.' + QString::number(i) + '.';
        values.insert(name + "X", object.center.x());
        values.insert(name + "Y", object.center.y());
        values.insert(name + "Z", object.center.z());
        values.insert(name + "W", object.width);
        values.insert(name + "L", object.height);
        values.insert(name + "A", object.angle);
        values.insert(name + "UID", object.uid);
        values.insert(name + "Type", object.type);
        values.insert(name + "Confidence", object.confidence);
        values.insert(name + "Label", object.label);
        values.insert(name + "ExternalId", object.externalId);
        values.insert(name + "IsPicked", object.isPicked);
        values.insert(name + "Offset", object.offset);
        values.insert(name + "ClaimOwner", object.claimOwner);
        values.insert(name + "ClaimExpiresAt", object.claimExpiresAtMs);
        values.insert(name + "IsClaimed", !object.claimOwner.isEmpty());
        values.insert(name + "State", trackStateLocked(object));
        values.insert(name + "Confirmed", object.confirmed);
        values.insert(name + "HitCount", object.hitCount);
        values.insert(name + "MissedFrames", object.missedFrames);
        values.insert(name + "LastSeenAt", object.lastSeenAtMs);
    }
    values.insert(ListName + ".Count", objects.size());
    const QString telemetryPrefix = QString("Tracking.%1.").arg(ID);
    for (auto it = realtime.cbegin(); it != realtime.cend(); ++it)
        values.insert(telemetryPrefix + it.key(), it.value());
    variables.updateBatchScoped(ProjectName, values,
                                VariableManager::Persistence::Runtime);
    publishedObjectCount = objects.size();
    lastPublicationTimer.restart();

    const qint64 durationUs = publishDuration.nsecsElapsed() / 1000;
    {
        QMutexLocker locker(&dataMutex);
        lastPublishDurationUs = durationUs;
        maxPublishDurationUs = qMax(maxPublishDurationUs, durationUs);
    }
    emit SnapshotPublished(ID, objects);
}

QVariantMap Tracking::realtimeSnapshotLocked(qint64 nowMonotonicMs) const
{
    QVariantMap result;
    result.insert(QStringLiteral("State"), healthStatusLocked(nowMonotonicMs));
    result.insert(QStringLiteral("LastFault"), lastRealtimeFault);
    result.insert(QStringLiteral("ObjectCount"), TrackedObjects.size());
    result.insert(QStringLiteral("PendingFrames"), pendingFrames.size());
    result.insert(QStringLiteral("PendingEncoderReads"), pendingEncoderReads.size());
    result.insert(QStringLiteral("EncoderAgeMs"),
                  lastEncoderAtMonotonicMs < 0 ? -1
                      : qMax<qint64>(0, nowMonotonicMs - lastEncoderAtMonotonicMs));
    result.insert(QStringLiteral("VisionAgeMs"),
                  lastDetectionAtMonotonicMs < 0 ? -1
                      : qMax<qint64>(0, nowMonotonicMs - lastDetectionAtMonotonicMs));
    result.insert(QStringLiteral("FramesCaptured"), QVariant::fromValue<qulonglong>(framesCaptured));
    result.insert(QStringLiteral("FramesCommitted"), QVariant::fromValue<qulonglong>(framesCommitted));
    result.insert(QStringLiteral("FramesRejected"), QVariant::fromValue<qulonglong>(framesRejected));
    result.insert(QStringLiteral("FramesExpired"), QVariant::fromValue<qulonglong>(framesExpired));
    result.insert(QStringLiteral("FrameQueueOverflows"),
                  QVariant::fromValue<qulonglong>(frameQueueOverflows));
    result.insert(QStringLiteral("EncoderQueueOverflows"),
                  QVariant::fromValue<qulonglong>(encoderQueueOverflows));
    result.insert(QStringLiteral("EncoderSamples"), QVariant::fromValue<qulonglong>(encoderSamples));
    result.insert(QStringLiteral("Publications"), QVariant::fromValue<qulonglong>(publicationCount));
    result.insert(QStringLiteral("PublicationsSuppressed"),
                  QVariant::fromValue<qulonglong>(publicationSuppressed));
    result.insert(QStringLiteral("LastCommitLatencyMs"), lastCommitLatencyMs);
    result.insert(QStringLiteral("MaxCommitLatencyMs"), maxCommitLatencyMs);
    result.insert(QStringLiteral("LastPublishDurationUs"), lastPublishDurationUs);
    result.insert(QStringLiteral("MaxPublishDurationUs"), maxPublishDurationUs);
    result.insert(QStringLiteral("LastCommittedFrameId"),
                  QVariant::fromValue<qulonglong>(lastCommittedFrameId));
    result.insert(QStringLiteral("Config.PublishIntervalMs"), publishIntervalMs);
    result.insert(QStringLiteral("Config.VisionStaleMs"), detectionStaleTimeoutMs);
    result.insert(QStringLiteral("Config.EncoderStaleMs"), encoderStaleTimeoutMs);
    result.insert(QStringLiteral("Config.FrameTimeoutMs"), frameTimeoutMs);
    result.insert(QStringLiteral("Config.MaxPendingFrames"), maxPendingFrames);
    result.insert(QStringLiteral("Config.MaxPendingEncoderReads"), maxPendingEncoderReads);
    return result;
}

QVariantMap Tracking::RealtimeSnapshot() const
{
    QMutexLocker locker(&dataMutex);
    return realtimeSnapshotLocked(monotonicClock.elapsed());
}

void Tracking::ConfigureRealtime(int publishMs, int visionStaleMs,
                                 int encoderStaleMs, int pendingFrameTimeoutMs,
                                 int pendingFrameLimit, int pendingEncoderLimit)
{
    {
        QMutexLocker locker(&dataMutex);
        publishIntervalMs = qBound(0, publishMs, 5000);
        detectionStaleTimeoutMs = qBound(50, visionStaleMs, 120000);
        encoderStaleTimeoutMs = qBound(50, encoderStaleMs, 120000);
        frameTimeoutMs = qBound(100, pendingFrameTimeoutMs, 120000);
        maxPendingFrames = qBound(1, pendingFrameLimit, 1024);
        maxPendingEncoderReads = qBound(2, pendingEncoderLimit, 4096);
    }
    if (realtimeMonitorTimer && realtimeMonitorTimer->isActive())
        realtimeMonitorTimer->setInterval(qBound(20, publishIntervalMs > 0
                                                       ? publishIntervalMs : 100,
                                                  1000));
    publishTrackedObjectsSnapshot(true);
}

void Tracking::StartRealtimeMonitor()
{
    if (!realtimeMonitorTimer)
        return;
    realtimeMonitorTimer->setInterval(qBound(20, publishIntervalMs > 0
                                                   ? publishIntervalMs : 100,
                                              1000));
    realtimeMonitorTimer->start();
    publishTrackedObjectsSnapshot(true);
}

void Tracking::PublishNow()
{
    publishTrackedObjectsSnapshot(true);
}

void Tracking::tryCommitFrames()
{
    while (true) {
        PendingFrame frame;
        QVector<PendingFrame> expiredFrames;
        bool ready = false;
        {
            QMutexLocker locker(&dataMutex);
            expiredFrames = purgeExpiredFramesLocked(monotonicClock.elapsed());
            if (!pendingFrames.isEmpty()) {
                const PendingFrame& firstFrame = pendingFrames.head();
                ready = firstFrame.hasCapturePosition && firstFrame.hasDetections &&
                        firstFrame.hasDetectPosition;
                if (ready)
                    frame = pendingFrames.dequeue();
            }
        }
        emitRejectedFrames(expiredFrames, QStringLiteral("Tracking frame timed out"));
        if (!ready)
            return;
        commitDetectionFrame(frame);
    }
}

void Tracking::commitDetectionFrame(PendingFrame frame)
{
    {
        QMutexLocker locker(&dataMutex);
        DetectedObjects = frame.detections;
    }

    const QVector3D offset = calculateMoved(frame.detectPosition - frame.capturePosition);
    UpdateTrackedObjectOffsets(offset);

    {
        QMutexLocker locker(&dataMutex);
        lastCommittedFrameId = frame.id;
        framesCommitted++;
        lastCommitLatencyMs = qMax<qint64>(
            0, monotonicClock.elapsed() - frame.createdAtMonotonicMs);
        maxCommitLatencyMs = qMax(maxCommitLatencyMs, lastCommitLatencyMs);
        if (lastRealtimeFault == QStringLiteral("UNMATCHED_VISION_FRAME"))
            lastRealtimeFault.clear();
    }
    emit DetectionFrameCommitted(ID, frame.id, frame.requestId);
}

double Tracking::associationCostLocked(const ObjectInfo& detection,
                                       const ObjectInfo& track) const
{
    const double distance = detection.center.distanceToPoint(track.center);
    const double iou = calculateIoU(detection, track);
    const double distanceGate = std::max(1.0, static_cast<double>(DistanceThreshold));
    const bool iouEnabled = IoUThreshold > 0.0f;
    const bool geometryMatches = distance <= distanceGate ||
                                 (iouEnabled && iou >= IoUThreshold);
    if (!geometryMatches)
        return 1.0e9;

    const bool typeMatches = detection.type == track.type;
    if (!typeMatches && track.claimOwner.isEmpty()) {
        const double mismatchGate = distanceGate *
                                    std::clamp(static_cast<double>(typeMismatchDistanceFactor),
                                               0.1, 1.0);
        const bool strongOverlap = iouEnabled && iou >= std::max(0.5, static_cast<double>(IoUThreshold));
        if (distance > mismatchGate && !strongOverlap)
            return 1.0e9;
    }

    const double sizeScale = std::max(1.0, std::max(track.width, track.height));
    const double sizePenalty =
        (std::abs(detection.width - track.width) +
         std::abs(detection.height - track.height)) / sizeScale;
    const double typePenalty = typeMatches ? 0.0 : distanceGate * 0.4;
    const double overlapReward = iouEnabled ? iou * distanceGate * 0.25 : 0.0;
    return std::max(0.0, distance + sizePenalty + typePenalty - overlapReward);
}

QVector<int> Tracking::solveGlobalAssignmentLocked(const QVector<ObjectInfo>& detections) const
{
    QVector<int> result(detections.size(), -1);
    if (detections.isEmpty() || TrackedObjects.isEmpty())
        return result;

    QVector<int> trackIndices;
    for (int i = 0; i < TrackedObjects.size(); ++i) {
        trackIndices.append(i);
    }
    if (trackIndices.isEmpty())
        return result;

    const int detectionCount = detections.size();
    const int trackCount = trackIndices.size();
    const int size = detectionCount + trackCount;
    const double invalidCost = 1.0e9;
    const double unmatchedCost = std::max(10.0,
        static_cast<double>(DistanceThreshold) * 2.0 + 10.0);

    QVector<QVector<double>> cost(size, QVector<double>(size, 0.0));
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if (row < detectionCount && column < trackCount) {
                cost[row][column] = associationCostLocked(
                    detections.at(row), TrackedObjects.at(trackIndices.at(column)));
            } else if (row < detectionCount || column < trackCount) {
                cost[row][column] = unmatchedCost;
            }
        }
    }

    // Hungarian algorithm on a square matrix. Dummy rows and columns make
    // unmatched detections/tracks explicit, so the result maximizes valid
    // one-to-one matches before minimizing their geometric cost.
    QVector<double> u(size + 1, 0.0), v(size + 1, 0.0);
    QVector<int> p(size + 1, 0), way(size + 1, 0);
    for (int row = 1; row <= size; ++row) {
        p[0] = row;
        int column0 = 0;
        QVector<double> minValue(size + 1, invalidCost);
        QVector<bool> used(size + 1, false);
        do {
            used[column0] = true;
            const int row0 = p[column0];
            double delta = invalidCost;
            int column1 = 0;
            for (int column = 1; column <= size; ++column) {
                if (used[column])
                    continue;
                const double current = cost[row0 - 1][column - 1] - u[row0] - v[column];
                if (current < minValue[column]) {
                    minValue[column] = current;
                    way[column] = column0;
                }
                if (minValue[column] < delta) {
                    delta = minValue[column];
                    column1 = column;
                }
            }
            for (int column = 0; column <= size; ++column) {
                if (used[column]) {
                    u[p[column]] += delta;
                    v[column] -= delta;
                } else {
                    minValue[column] -= delta;
                }
            }
            column0 = column1;
        } while (p[column0] != 0);

        do {
            const int column1 = way[column0];
            p[column0] = p[column1];
            column0 = column1;
        } while (column0 != 0);
    }

    QVector<int> rowToColumn(size, -1);
    for (int column = 1; column <= size; ++column) {
        if (p[column] > 0)
            rowToColumn[p[column] - 1] = column - 1;
    }
    for (int row = 0; row < detectionCount; ++row) {
        const int column = rowToColumn.at(row);
        if (column >= 0 && column < trackCount &&
            cost[row][column] < invalidCost * 0.5)
            result[row] = trackIndices.at(column);
    }
    return result;
}

void Tracking::associateDetectionsLocked(QVector<ObjectInfo> detectedObjects,
                                         const QVector3D& offset,
                                         qint64 nowEpochMs,
                                         qint64 nowMonotonicMs)
{
    expireClaimsLocked(nowEpochMs, nowMonotonicMs);

    // A long vision outage ends the identity session for unclaimed belt
    // objects. Keeping their frozen identities would create duplicates after
    // the camera reconnects. In-flight claims and completed objects remain.
    if (lastDetectionAtMonotonicMs >= 0 &&
        nowMonotonicMs - lastDetectionAtMonotonicMs > detectionStaleTimeoutMs) {
        TrackedObjects.erase(std::remove_if(TrackedObjects.begin(), TrackedObjects.end(),
            [](const ObjectInfo& object) {
                return object.claimOwner.isEmpty() && !object.isPicked;
            }), TrackedObjects.end());
    }

    for (ObjectInfo& detection : detectedObjects) {
        detection.center += offset;
        detection.offset = offset;
    }

    const QVector<int> assignment = solveGlobalAssignmentLocked(detectedObjects);
    QSet<int> matchedTrackIndices;

    for (int detectionIndex = 0; detectionIndex < detectedObjects.size(); ++detectionIndex) {
        const ObjectInfo& detection = detectedObjects.at(detectionIndex);
        const int trackIndex = assignment.value(detectionIndex, -1);
        if (trackIndex < 0 || trackIndex >= TrackedObjects.size())
            continue;

        ObjectInfo& track = TrackedObjects[trackIndex];
        matchedTrackIndices.insert(trackIndex);
        track.center = detection.center;
        track.width = detection.width;
        track.height = detection.height;
        track.offset = detection.offset;
        track.confidence = detection.confidence;
        track.externalId = detection.externalId;
        track.isPicked = track.isPicked || detection.isPicked;
        track.hitCount++;
        track.missedFrames = 0;
        track.lastSeenAtMs = nowEpochMs;
        if (track.hitCount >= std::max(1, minConfirmationHits))
            track.confirmed = true;

        // Object orientation is periodic over 180 degrees for a parallel-jaw
        // or vacuum pick. Preserve continuity around 0/180 instead of allowing
        // a detector representation change to rotate the robot unnecessarily.
        double angleDelta = std::fmod(detection.angle - track.angle + 270.0, 180.0) - 90.0;
        track.angle = std::fmod(track.angle + angleDelta + 180.0, 180.0);

        if (detection.type == track.type) {
            track.label = detection.label;
            track.candidateType = -1;
            track.candidateTypeHits = 0;
        } else if (track.claimOwner.isEmpty()) {
            if (track.candidateType == detection.type) {
                track.candidateTypeHits++;
            } else {
                track.candidateType = detection.type;
                track.candidateTypeHits = 1;
            }
            if (track.candidateTypeHits >= std::max(1, typeSwitchConfirmationHits)) {
                track.type = track.candidateType;
                track.label = detection.label;
                track.candidateType = -1;
                track.candidateTypeHits = 0;
            }
        }
    }

    for (int trackIndex = 0; trackIndex < TrackedObjects.size(); ++trackIndex) {
        if (!matchedTrackIndices.contains(trackIndex) && !TrackedObjects[trackIndex].isPicked)
            TrackedObjects[trackIndex].missedFrames++;
    }

    for (int detectionIndex = 0; detectionIndex < detectedObjects.size(); ++detectionIndex) {
        if (assignment.value(detectionIndex, -1) >= 0)
            continue;

        ObjectInfo newTrack = detectedObjects.at(detectionIndex);
        newTrack.uid = nextID++;
        newTrack.claimOwner.clear();
        newTrack.claimExpiresAtMs = 0;
        newTrack.claimExpiresAtMonotonicMs = 0;
        newTrack.hitCount = 1;
        newTrack.missedFrames = 0;
        newTrack.lastSeenAtMs = nowEpochMs;
        newTrack.confirmed = minConfirmationHits <= 1;
        newTrack.candidateType = -1;
        newTrack.candidateTypeHits = 0;
        TrackedObjects.append(newTrack);
    }

    TrackedObjects.erase(std::remove_if(TrackedObjects.begin(), TrackedObjects.end(),
        [&](const ObjectInfo& object) {
            if (object.isPicked || !object.claimOwner.isEmpty())
                return false;
            const int missLimit = object.confirmed ? maxMissedFrames : maxTentativeMissedFrames;
            return object.missedFrames > std::max(0, missLimit);
        }), TrackedObjects.end());
}

QVector<Tracking::PendingFrame> Tracking::purgeExpiredFramesLocked(qint64 nowMonotonicMs)
{
    QVector<PendingFrame> expiredFrames;
    for (int index = pendingFrames.size() - 1; index >= 0; --index) {
        if (nowMonotonicMs - pendingFrames.at(index).createdAtMonotonicMs <= frameTimeoutMs)
            continue;
        expiredFrames.append(pendingFrames.at(index));
        pendingFrames.removeAt(index);
    }
    if (!expiredFrames.isEmpty()) {
        framesExpired += static_cast<quint64>(expiredFrames.size());
        framesRejected += static_cast<quint64>(expiredFrames.size());
        lastRealtimeFault = QStringLiteral("FRAME_TIMEOUT");
    }

    // Encoder requests are already on the device wire. Keep their queue entries
    // so late replies are consumed without shifting onto a different frame.
    return expiredFrames;
}

void Tracking::emitRejectedFrames(const QVector<PendingFrame>& frames,
                                  const QString& reason)
{
    for (const PendingFrame& frame : frames)
        emit DetectionFrameRejected(ID, frame.id, frame.requestId, reason);
    if (!frames.isEmpty())
        publishTrackedObjectsSnapshot(true);
}

QString Tracking::trackStateLocked(const ObjectInfo& object) const
{
    if (object.isPicked)
        return "PICKED";
    if (!object.claimOwner.isEmpty())
        return "CLAIMED";
    if (object.missedFrames > 0)
        return "LOST";
    return object.confirmed ? "CONFIRMED" : "TENTATIVE";
}

void Tracking::GetObjectsInArea(QString inAreaListName, float min, float max, bool isXdirection)
{
    // Create working copy to avoid race conditions
    QVector<ObjectInfo> workingTrackedObjects;
    
    {
        QMutexLocker locker(&dataMutex);
        expireClaimsLocked(QDateTime::currentMSecsSinceEpoch(), monotonicClock.elapsed());
        workingTrackedObjects = TrackedObjects;
    }
    publishTrackedObjectsSnapshot(true);

    QVector<ObjectInfo> selectedObjects;
    QHash<QString, QVariant> values;
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
        if (!tracked.confirmed)
            continue;
        if (!tracked.claimOwner.isEmpty())
            continue;

        const QString name = inAreaListName + '.' + QString::number(index) + '.';
        values.insert(name + "X", tracked.center.x());
        values.insert(name + "Y", tracked.center.y());
        values.insert(name + "Z", tracked.center.z());
        values.insert(name + "W", tracked.width);
        values.insert(name + "L", tracked.height);
        values.insert(name + "A", tracked.angle);
        values.insert(name + "IsPicked", tracked.isPicked);
        values.insert(name + "IsClaimed", false);
        values.insert(name + "Type", tracked.type);
        values.insert(name + "UID", tracked.uid);
        selectedObjects.append(tracked);
        index++;
    }

    VariableManager& variables = VariableManager::instance();
    variables.removeVarScoped(ProjectName, inAreaListName);
    variables.updateObjectSnapshot(ProjectName, inAreaListName, selectedObjects);
    values.insert(inAreaListName + ".Count", index);
    variables.updateBatchScoped(ProjectName, values,
                                VariableManager::Persistence::Runtime);
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

        // Update positions of ALL objects (picked and unpicked)
        for (auto &obj : TrackedObjects) {
            obj.center += effectiveDisplacement;  // Move every tracked object.
        }

        // Remove objects that moved out of bounds (picked and unpicked)
        TrackedObjects.erase(std::remove_if(TrackedObjects.begin(), TrackedObjects.end(),
            [&](const auto& obj) {
                return obj.center.x() > X_max || obj.center.x() < X_min ||
                       obj.center.y() > Y_max || obj.center.y() < Y_min;
            }), TrackedObjects.end());
    }

    publishTrackedObjectsSnapshot(false);

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
        pendingFrames.clear();
        pendingEncoderReads.clear();
        lastDetectionAtMonotonicMs = -1;
        lastDetectionTimer.invalidate();
    }
    
    publishTrackedObjectsSnapshot();
}

void Tracking::RemoveTrackedObjects(int id)
{

}

void Tracking::SetObjectPickedByUID(int uid)
{
    QMutexLocker locker(&dataMutex);
    for (auto &obj : TrackedObjects) {
        if (obj.uid == uid) {
            obj.isPicked = true;  // Mark as picked without deleting the track.
            obj.claimOwner.clear();
            obj.claimExpiresAtMs = 0;
            obj.claimExpiresAtMonotonicMs = 0;
            qDebug() << "Object with UID" << uid << "marked as picked - will continue moving with conveyor until out of bounds";
            break;
        }
    }
    locker.unlock();
    publishTrackedObjectsSnapshot();
}

void Tracking::AddObjectDirectly(const ObjectInfo& obj)
{
    QMutexLocker locker(&dataMutex);
    
    // Create new object with proper UID
    ObjectInfo newObj = obj;
    newObj.uid = nextID++;  // Assign unique ID
    newObj.claimOwner.clear();
    newObj.claimExpiresAtMs = 0;
    newObj.claimExpiresAtMonotonicMs = 0;
    newObj.confirmed = true;
    newObj.hitCount = std::max(newObj.hitCount, std::max(1, minConfirmationHits));
    newObj.missedFrames = 0;
    newObj.lastSeenAtMs = QDateTime::currentMSecsSinceEpoch();
    
    // Add directly to TrackedObjects
    TrackedObjects.append(newObj);
    lastDetectionTimer.restart();
    lastEncoderTimer.restart();
    lastDetectionAtMonotonicMs = monotonicClock.elapsed();
    lastEncoderAtMonotonicMs = monotonicClock.elapsed();
    
    qDebug() << "Object added directly with UID" << newObj.uid << "at position (" 
             << newObj.center.x() << "," << newObj.center.y() << "," << newObj.center.z() << ")";
    locker.unlock();
    publishTrackedObjectsSnapshot();
}

QVector<ObjectInfo> Tracking::getTrackedObjectsCopy() const
{
    QMutexLocker locker(&dataMutex);
    return TrackedObjects;  // Thread-safe copy
}

void Tracking::expireClaimsLocked(qint64 nowEpochMs, qint64 nowMonotonicMs)
{
    for (ObjectInfo& object : TrackedObjects) {
        const bool monotonicExpired = object.claimExpiresAtMonotonicMs > 0 &&
                                      object.claimExpiresAtMonotonicMs <= nowMonotonicMs;
        const bool legacyEpochExpired = object.claimExpiresAtMonotonicMs <= 0 &&
                                        object.claimExpiresAtMs > 0 &&
                                        object.claimExpiresAtMs <= nowEpochMs;
        if (!object.claimOwner.isEmpty() && (monotonicExpired || legacyEpochExpired)) {
            object.claimOwner.clear();
            object.claimExpiresAtMs = 0;
            object.claimExpiresAtMonotonicMs = 0;
        }
    }
}

QString Tracking::healthStatusLocked(qint64 nowMonotonicMs) const
{
    if (lastDetectionAtMonotonicMs < 0)
        return "VISION_NOT_READY";
    if (nowMonotonicMs - lastDetectionAtMonotonicMs > detectionStaleTimeoutMs)
        return "VISION_STALE";
    if (lastEncoderAtMonotonicMs < 0)
        return "ENCODER_NOT_READY";
    if (nowMonotonicMs - lastEncoderAtMonotonicMs > encoderStaleTimeoutMs)
        return "ENCODER_STALE";
    return "READY";
}

QString Tracking::HealthStatus() const
{
    QMutexLocker locker(&dataMutex);
    return healthStatusLocked(monotonicClock.elapsed());
}

quint64 Tracking::LastCommittedFrameId() const
{
    QMutexLocker locker(&dataMutex);
    return lastCommittedFrameId;
}

QVariantMap Tracking::objectToResult(const ObjectInfo& object) const
{
    QVariantMap result;
    result.insert("Found", true);
    result.insert("UID", object.uid);
    result.insert("Type", object.type);
    result.insert("Confidence", object.confidence);
    result.insert("Label", object.label);
    result.insert("ExternalId", object.externalId);
    result.insert("X", object.center.x());
    result.insert("Y", object.center.y());
    result.insert("Z", object.center.z());
    result.insert("W", object.width);
    result.insert("L", object.height);
    result.insert("A", object.angle);
    result.insert("ClaimOwner", object.claimOwner);
    result.insert("ClaimExpiresAt", object.claimExpiresAtMs);
    result.insert("Status", "READY");
    result.insert("TrackState", trackStateLocked(object));
    result.insert("FrameId", QVariant::fromValue<qulonglong>(lastCommittedFrameId));
    return result;
}

QVariantMap Tracking::ClaimObject(const QString& owner, float minX, float maxX,
                                  float minY, float maxY, int typeFilter,
                                  int leaseMs)
{
    QVariantMap notFound;
    notFound.insert("Found", false);
    notFound.insert("UID", -1);
    notFound.insert("Type", -1);
    notFound.insert("Confidence", 0.0);
    notFound.insert("Label", QString());
    notFound.insert("ExternalId", QString());
    notFound.insert("X", 0.0);
    notFound.insert("Y", 0.0);
    notFound.insert("Z", 0.0);
    notFound.insert("W", 0.0);
    notFound.insert("L", 0.0);
    notFound.insert("A", 0.0);
    notFound.insert("ClaimOwner", QString());
    notFound.insert("ClaimExpiresAt", qint64(0));
    notFound.insert("Status", "READY");
    notFound.insert("TrackState", QString());
    notFound.insert("FrameId", QVariant::fromValue<qulonglong>(0));

    const QString normalizedOwner = owner.trimmed();
    if (normalizedOwner.isEmpty())
        return notFound;

    if (minX > maxX) std::swap(minX, maxX);
    if (minY > maxY) std::swap(minY, maxY);
    leaseMs = qMax(1000, leaseMs);

    const qint64 nowEpochMs = QDateTime::currentMSecsSinceEpoch();
    const qint64 nowMonotonicMs = monotonicClock.elapsed();
    QMutexLocker locker(&dataMutex);
    expireClaimsLocked(nowEpochMs, nowMonotonicMs);

    const QString health = healthStatusLocked(nowMonotonicMs);
    notFound["Status"] = health;
    notFound["FrameId"] = QVariant::fromValue<qulonglong>(lastCommittedFrameId);
    if (health != "READY") {
        locker.unlock();
        publishTrackedObjectsSnapshot();
        return notFound;
    }

    auto isEligible = [&](const ObjectInfo& object) {
        return object.confirmed && !object.isPicked &&
               object.center.x() >= minX && object.center.x() <= maxX &&
               object.center.y() >= minY && object.center.y() <= maxY &&
               (typeFilter < 0 || object.type == typeFilter);
    };

    // Retrying the same request renews the lease. A worker may own at most
    // one live object, even if it asks for a different work area meanwhile.
    bool ownerAlreadyHasClaim = false;
    for (ObjectInfo& object : TrackedObjects) {
        if (object.claimOwner != normalizedOwner)
            continue;

        ownerAlreadyHasClaim = true;
        if (!isEligible(object))
            continue;

        object.claimExpiresAtMs = nowEpochMs + leaseMs;
        object.claimExpiresAtMonotonicMs = nowMonotonicMs + leaseMs;
        const QVariantMap result = objectToResult(object);
        locker.unlock();
        publishTrackedObjectsSnapshot();
        return result;
    }
    if (ownerAlreadyHasClaim) {
        locker.unlock();
        publishTrackedObjectsSnapshot();
        return notFound;
    }

    QVector3D direction = VelocityVector;
    if (direction.lengthSquared() < 1e-9f)
        direction = QVector3D(1.0f, 0.0f, 0.0f);
    direction.normalize();

    ObjectInfo* selected = nullptr;
    float bestProgress = -std::numeric_limits<float>::infinity();
    for (ObjectInfo& object : TrackedObjects) {
        if (!isEligible(object) || !object.claimOwner.isEmpty())
            continue;

        // Prioritize the object nearest the downstream edge of the work area.
        const float progress = QVector3D::dotProduct(object.center, direction);
        if (!selected || progress > bestProgress) {
            selected = &object;
            bestProgress = progress;
        }
    }

    if (!selected) {
        locker.unlock();
        publishTrackedObjectsSnapshot();
        return notFound;
    }

    selected->claimOwner = normalizedOwner;
    selected->claimExpiresAtMs = nowEpochMs + leaseMs;
    selected->claimExpiresAtMonotonicMs = nowMonotonicMs + leaseMs;
    const QVariantMap result = objectToResult(*selected);
    locker.unlock();
    publishTrackedObjectsSnapshot();
    return result;
}

bool Tracking::ReleaseObject(int uid, const QString& owner)
{
    QMutexLocker locker(&dataMutex);
    expireClaimsLocked(QDateTime::currentMSecsSinceEpoch(), monotonicClock.elapsed());
    for (ObjectInfo& object : TrackedObjects) {
        if (object.uid == uid && !object.isPicked && object.claimOwner == owner.trimmed()) {
            object.claimOwner.clear();
            object.claimExpiresAtMs = 0;
            object.claimExpiresAtMonotonicMs = 0;
            locker.unlock();
            publishTrackedObjectsSnapshot();
            return true;
        }
    }
    locker.unlock();
    publishTrackedObjectsSnapshot();
    return false;
}

bool Tracking::CompleteObject(int uid, const QString& owner)
{
    QMutexLocker locker(&dataMutex);
    expireClaimsLocked(QDateTime::currentMSecsSinceEpoch(), monotonicClock.elapsed());
    for (ObjectInfo& object : TrackedObjects) {
        if (object.uid == uid && !object.isPicked && object.claimOwner == owner.trimmed()) {
            object.isPicked = true;
            object.claimOwner.clear();
            object.claimExpiresAtMs = 0;
            object.claimExpiresAtMonotonicMs = 0;
            locker.unlock();
            publishTrackedObjectsSnapshot();
            return true;
        }
    }
    locker.unlock();
    publishTrackedObjectsSnapshot();
    return false;
}

QVector3D Tracking::calculateMoved(float distance)
{
    // Normalize the VelocityVector to get the direction
    QVector3D direction = VelocityVector.length() > 0 ? VelocityVector.normalized() : QVector3D(1, 0, 0);

    // Calculate the effective 3D displacement vector (distance already encodes magnitude)
    return direction * distance;
}


double Tracking::similarity(ObjectInfo &obj1, ObjectInfo &obj2, double displacement) {
    // Calculate effective 3D displacement based on normalized velocity and scalar displacement
    QVector3D effectiveDisplacement = calculateMoved(static_cast<float>(displacement));

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

double Tracking::calculateIoU(const ObjectInfo &object1, const ObjectInfo &object2) const
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

    // 3. Calculate IoU with guard
    if (unionArea <= 0.0) {
        return 0.0;
    }
    double iou = overlapArea / unionArea;
    return iou;
}

bool Tracking::isSameObject(const ObjectInfo &object1, const ObjectInfo &object2) const
{
    if (object1.type != object2.type)
        return false;

    // 1. Check intersection over union.
    double iou = calculateIoU(object1, object2);
    if (iou >= IoUThreshold) {
        return true;
    }

    // 2. Check centre distance.
    double distance = object1.center.distanceToPoint(object2.center);
    if (distance <= DistanceThreshold) {
        return true;
    }

    // 3. Check optional association factors.
    // ...

    return false;
}

TrackingManager::TrackingManager(QObject *parent)
    : QObject(parent)
{
}

void TrackingManager::SaveCapturePosition(int id, quint64 frameId, quint64 requestId)
{
    if (id < 0 || id >= Trackings.count())
        return;
    Tracking* tracking = Trackings.at(id);
    const Qt::ConnectionType type = tracking->thread() == QThread::currentThread()
        ? Qt::DirectConnection : Qt::BlockingQueuedConnection;
    QMetaObject::invokeMethod(tracking, [tracking, frameId, requestId]() {
        tracking->SaveCapturePosition(frameId, requestId);
    }, type);
}

void TrackingManager::SubmitDetections(VisionDetections detections)
{
    if (detections.trackingId < 0 || detections.trackingId >= Trackings.count()) {
        if (detections.requestId != 0)
            emit GotResponse(QString("vision%1").arg(detections.trackingId),
                             QString("VisionError:%1:Invalid tracking id")
                                 .arg(detections.requestId));
        return;
    }

    Tracking* tracking = Trackings.at(detections.trackingId);
    QMetaObject::invokeMethod(tracking, [tracking, detections]() {
        tracking->UpdateTrackedObjectsForFrame(detections.objects,
                                               detections.frameId,
                                               detections.requestId);
    }, Qt::QueuedConnection);
}

void TrackingManager::RejectVisionFrame(int trackingId, quint64 frameId,
                                        quint64 requestId, QString reason)
{
    if (trackingId < 0 || trackingId >= Trackings.count()) {
        if (requestId != 0)
            emit GotResponse(QString("vision%1").arg(trackingId),
                             QString("VisionError:%1:%2").arg(requestId).arg(reason));
        return;
    }
    Tracking* tracking = Trackings.at(trackingId);
    QMetaObject::invokeMethod(tracking, [tracking, frameId, requestId, reason]() {
        tracking->RejectPendingFrame(frameId, requestId, reason);
    }, Qt::QueuedConnection);
}

void TrackingManager::OnCaptureFailed(int trackingId, quint64 requestId, QString reason)
{
    if (requestId == 0)
        return;
    emit GotResponse(QString("vision%1").arg(trackingId),
                     QString("VisionError:%1:%2").arg(requestId).arg(reason));
}

void TrackingManager::SaveDetectPosition(int id)
{
    if (id < 0 || id >= Trackings.count())
        return;
    QMetaObject::invokeMethod(Trackings.at(id), "SaveDetectPosition", Qt::QueuedConnection);
}

void TrackingManager::UpdateTracking(int id)
{
    // Bounds check to avoid crash and avoid hanging GScript
    if (id < 0 || id >= Trackings.count())
    {
        emit GotResponse(QString("tracking") + QString::number(id), "Done");
        return;
    }
    currentTrackingRequest = id;
    QMetaObject::invokeMethod(Trackings.at(id), "SetClientWaiting", Qt::QueuedConnection, Q_ARG(bool, true));
    QMetaObject::invokeMethod(Trackings.at(id), "ReadEncoder", Qt::QueuedConnection);
}

void TrackingManager::GetObjectsInArea(int trackingID, QString inAreaListName, float min, float max, bool isXDirection)
{
    if (trackingID < 0 || trackingID >= Trackings.count()) {
        emit GotResponse(QString("tracking") + QString::number(trackingID), "Done");
        return;
    }

    Tracking* tracking = Trackings.at(trackingID);
    if (tracking->thread() == QThread::currentThread()) {
        tracking->GetObjectsInArea(inAreaListName, min, max, isXDirection);
    } else {
        QMetaObject::invokeMethod(tracking, "GetObjectsInArea", Qt::BlockingQueuedConnection,
                                  Q_ARG(QString, inAreaListName),
                                  Q_ARG(float, min), Q_ARG(float, max),
                                  Q_ARG(bool, isXDirection));
    }

    emit GotResponse(QString("tracking") + QString::number(trackingID), "Done");
}

void TrackingManager::UpdateVariable(QString cmd)
{
    // Handle new UID-based command
    if (cmd.startsWith("SetObjectPickedByUID=")) {
        QStringList parts = cmd.split('=')[1].split(',');
        if (parts.size() >= 2) {
            QString listName = parts[0];
            int uid = parts[1].toInt();
            SetObjectPickedByUID(listName, uid);
        }
        return;
    }
    
    // Original implementation
    QStringList paras1 = cmd.split('=');
    QStringList paras2 = paras1.at(0).split('.');

    // Route to the correct tracking instance based on list name
    if (paras2.size() >= 1) {
        QString listName = paras2.at(0);
        for (int i = 0; i < Trackings.count(); i++)
        {
            if (Trackings.at(i)->GetListName() == listName)
            {
                QMetaObject::invokeMethod(Trackings.at(i), "ChangeObjectInfo", Qt::QueuedConnection, Q_ARG(QString, cmd));
                break;
            }
        }
    }

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
    // Process each parameter.
    for (int i = 0; i < list.count(); i++)
    {
        QStringList paras = list.at(i);

        // Legacy detector/JSON payload: type,x,y,width,length,angle.
        if (paras.size() == 6) {
            objectList.append(ObjectInfo(-1,
                                         paras.at(0).toInt(),
                                         QVector3D(paras.at(1).toFloat(),
                                                   paras.at(2).toFloat(),
                                                   0.0f),
                                         paras.at(3).toFloat(),
                                         paras.at(4).toFloat(),
                                         paras.at(5).toFloat()));
            continue;
        }

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
                QString pickedStr = paras.at(7).trimmed().toLower();
                if (pickedStr == "true" || pickedStr == "1") isPicked = true;
                else if (pickedStr == "false" || pickedStr == "0") isPicked = false;
                else isPicked = paras.at(7).toInt();
            }
        }
        
        // Canonical payload: type,x,y,z,width,length,angle,isPicked.
        // Tracking assigns the stable UID after matching detections.
        ObjectInfo obj(-1, id, QVector3D(x, y, z), w, l, a, isPicked);

        objectList.append(obj);
    }

    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->GetListName() == listName)
        {
            QMetaObject::invokeMethod(Trackings.at(i), "UpdateTrackedObjects", Qt::QueuedConnection, Q_ARG(QVector<ObjectInfo>, objectList), Q_ARG(QString, listName));
        }
    }
}

void TrackingManager::ClearObjects(QString listName)
{
    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->GetListName() == listName)
        {
            QMetaObject::invokeMethod(Trackings.at(i), "ClearTrackedObjects", Qt::QueuedConnection);
        }
    }
}

void TrackingManager::SetObjectPickedByUID(QString listName, int uid)
{
    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->GetListName() == listName)
        {
            QMetaObject::invokeMethod(Trackings.at(i), "SetObjectPickedByUID", Qt::QueuedConnection, Q_ARG(int, uid));
            break;
        }
    }
}

void TrackingManager::AddObjectToTracking(QString listName, const ObjectInfo& obj)
{
    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->GetListName() == listName)
        {
            QMetaObject::invokeMethod(Trackings.at(i), "AddObjectDirectly", Qt::QueuedConnection, Q_ARG(ObjectInfo, obj));
            break;
        }
    }
}

QString TrackingManager::qualifyResultName(const QString& resultName) const
{
    QString key = resultName.trimmed();
    key.remove('#');
    if (!ProjectName.isEmpty() && !key.startsWith(ProjectName + '.'))
        key.prepend(ProjectName + '.');
    return key;
}

void TrackingManager::publishClaimResult(const QString& resultName, const QVariantMap& result)
{
    const QString prefix = qualifyResultName(resultName);
    static const QStringList fields = {
        "Found", "UID", "Type", "Confidence", "Label", "ExternalId",
        "X", "Y", "Z", "W", "L", "A",
        "ClaimOwner", "ClaimExpiresAt", "Status", "TrackState", "FrameId"
    };

    QHash<QString, QVariant> values;
    for (const QString& field : fields)
        values.insert(prefix + '.' + field, result.value(field));
    VariableManager::instance().updateBatchAbsolute(
        values, VariableManager::Persistence::Runtime);
}

void TrackingManager::ClaimObject(int trackingID, QString resultName, QString owner,
                                  float minX, float maxX, float minY, float maxY,
                                  int typeFilter, int leaseMs)
{
    QVariantMap result;
    result.insert("Found", false);
    result.insert("UID", -1);
    result.insert("Type", -1);
    result.insert("Confidence", 0.0);
    result.insert("Label", QString());
    result.insert("ExternalId", QString());
    result.insert("X", 0.0);
    result.insert("Y", 0.0);
    result.insert("Z", 0.0);
    result.insert("W", 0.0);
    result.insert("L", 0.0);
    result.insert("A", 0.0);
    result.insert("ClaimOwner", QString());
    result.insert("ClaimExpiresAt", qint64(0));
    result.insert("Status", "TRACKING_NOT_FOUND");
    result.insert("TrackState", QString());
    result.insert("FrameId", QVariant::fromValue<qulonglong>(0));

    if (trackingID >= 0 && trackingID < Trackings.size()) {
        Tracking* tracking = Trackings.at(trackingID);
        if (tracking->thread() == QThread::currentThread()) {
            result = tracking->ClaimObject(owner, minX, maxX, minY, maxY,
                                           typeFilter, leaseMs);
        } else {
            QMetaObject::invokeMethod(tracking, "ClaimObject", Qt::BlockingQueuedConnection,
                                      Q_RETURN_ARG(QVariantMap, result),
                                      Q_ARG(QString, owner),
                                      Q_ARG(float, minX), Q_ARG(float, maxX),
                                      Q_ARG(float, minY), Q_ARG(float, maxY),
                                      Q_ARG(int, typeFilter), Q_ARG(int, leaseMs));
        }
    }

    publishClaimResult(resultName, result);
    QString response = "None";
    if (result.value("Found").toBool()) {
        response = "Claimed";
    } else {
        const QString status = result.value("Status").toString();
        if (status == "VISION_STALE" || status == "ENCODER_STALE" ||
            status == "TRACKING_NOT_FOUND")
            response = "TrackingFault:" + status;
        else if (status != "READY")
            response = "TrackingNotReady:" + status;
    }
    emit GotResponse(QString("tracking%1:%2").arg(trackingID).arg(owner.trimmed()), response);
}

void TrackingManager::ReleaseObject(int trackingID, int uid, QString owner)
{
    bool released = false;
    if (trackingID >= 0 && trackingID < Trackings.size()) {
        Tracking* tracking = Trackings.at(trackingID);
        if (tracking->thread() == QThread::currentThread()) {
            released = tracking->ReleaseObject(uid, owner);
        } else {
            QMetaObject::invokeMethod(tracking, "ReleaseObject", Qt::BlockingQueuedConnection,
                                      Q_RETURN_ARG(bool, released),
                                      Q_ARG(int, uid), Q_ARG(QString, owner));
        }
    }
    emit GotResponse(QString("tracking%1:%2").arg(trackingID).arg(owner.trimmed()),
                     released ? "Released" : "ReleaseRejected");
}

void TrackingManager::CompleteObject(int trackingID, int uid, QString owner)
{
    bool completed = false;
    if (trackingID >= 0 && trackingID < Trackings.size()) {
        Tracking* tracking = Trackings.at(trackingID);
        if (tracking->thread() == QThread::currentThread()) {
            completed = tracking->CompleteObject(uid, owner);
        } else {
            QMetaObject::invokeMethod(tracking, "CompleteObject", Qt::BlockingQueuedConnection,
                                      Q_RETURN_ARG(bool, completed),
                                      Q_ARG(int, uid), Q_ARG(QString, owner));
        }
    }
    emit GotResponse(QString("tracking%1:%2").arg(trackingID).arg(owner.trimmed()),
                     completed ? "Completed" : "CompleteRejected");
}

void TrackingManager::SetEncoderPosition(int id, float value)
{
    const float calibratedValue = calibratedEncoderPosition(id, value);
    for(int i = 0; i < Trackings.count(); i++)
    {
        if (Trackings.at(i)->GetEncoderName().mid(7).toInt() == id)
        {
            // Ensure thread-safe cross-thread call to the tracking instance
            QMetaObject::invokeMethod(Trackings.at(i), "OnReceiveEncoderPosition", Qt::QueuedConnection,
                                      Q_ARG(float, calibratedValue));
        }
    }
}

void TrackingManager::ReloadEncoderCalibration(int id)
{
    EncoderCalibrationProfile profile;
    const QString prefix = QStringLiteral("encoder%1.Calibration.").arg(id);
    profile.loaded = true;
    profile.isValid = VariableManager::instance()
                          .getVarScoped(ProjectName, prefix + QStringLiteral("IsValid"), false).toBool();
    profile.scale = VariableManager::instance()
                        .getVarScoped(ProjectName, prefix + QStringLiteral("Scale"), 1.0f).toFloat();
    profile.rawReference = VariableManager::instance()
                               .getVarScoped(ProjectName, prefix + QStringLiteral("RawReference"), 0.0f).toFloat();
    profile.worldReference = VariableManager::instance()
                                 .getVarScoped(ProjectName, prefix + QStringLiteral("WorldReference"), 0.0f).toFloat();
    if (!qIsFinite(profile.scale) || qFuzzyIsNull(profile.scale) ||
        !qIsFinite(profile.rawReference) || !qIsFinite(profile.worldReference)) {
        profile.isValid = false;
        profile.scale = 1.0f;
        profile.rawReference = 0.0f;
        profile.worldReference = 0.0f;
    }
    encoderCalibrationProfiles.insert(id, profile);
}

float TrackingManager::calibratedEncoderPosition(int id, float rawValue)
{
    if (!encoderCalibrationProfiles.contains(id) || !encoderCalibrationProfiles[id].loaded)
        ReloadEncoderCalibration(id);
    const EncoderCalibrationProfile profile = encoderCalibrationProfiles.value(id);
    if (!profile.isValid)
        return rawValue;
    return (rawValue - profile.rawReference) * profile.scale + profile.worldReference;
}

void TrackingManager::ReadEncoderWhenSensorActive(int id)
{

}

void TrackingManager::OnDoneUpdateTracking(int id)
{
    emit GotResponse(QString("tracking") + QString::number(id), "Done");
}

void TrackingManager::OnDoneUpdateTracking()
{
    // Derive tracking id from sender to avoid global state races
    QObject* s = sender();
    auto tracking = qobject_cast<Tracking*>(s);
    if (tracking)
    {
        emit GotResponse(QString("tracking") + QString::number(tracking->ID), "Done");
    }
}

void TrackingManager::OnDetectionFrameCommitted(int id, quint64 frameId, quint64 requestId)
{
    if (requestId == 0)
        return;
    emit GotResponse(QString("vision") + QString::number(id),
                     QString("FrameReady:%1:%2").arg(requestId).arg(frameId));
}

void TrackingManager::OnDetectionFrameRejected(int id, quint64 frameId,
                                                quint64 requestId, QString reason)
{
    Q_UNUSED(frameId)
    if (requestId == 0)
        return;
    emit GotResponse(QString("vision") + QString::number(id),
                     QString("VisionError:%1:%2").arg(requestId).arg(reason));
}

VirtualEncoder::VirtualEncoder(float initialPosition, float velocity, QObject *parent)
    : QObject(parent), currentPosition(initialPosition), velocity(velocity) {
    lastUpdateTime = QDateTime::currentMSecsSinceEpoch();

    connect(&timer, &QTimer::timeout, this, &VirtualEncoder::updatePosition);
//    timer.start(100);  // Update position every 100 ms.
}

void VirtualEncoder::MoveToThread(QThread* targetThread)
{
    if (!targetThread || thread() == targetThread)
        return;
    timer.moveToThread(targetThread);
    QObject::moveToThread(targetThread);
}

void VirtualEncoder::setVelocity(float newVelocity) {
    QMutexLocker locker(&stateMutex);
    velocity = newVelocity;
}

void VirtualEncoder::setPosition(float newPos)
{
    QMutexLocker locker(&stateMutex);
    currentPosition = newPos;
}

void VirtualEncoder::stop() {
    timer.stop();
    QMutexLocker locker(&stateMutex);
    isRun = false;
}

void VirtualEncoder::start(int interval) {
    const int safeInterval = qMax(1, interval);
    {
        QMutexLocker locker(&stateMutex);
        lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
        intervalMs = safeInterval;
        isRun = true;
    }
    timer.setInterval(safeInterval);
    timer.start();
}

void VirtualEncoder::reset()
{
    {
        QMutexLocker locker(&stateMutex);
        lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
        currentPosition = 0;
    }
    emit positionUpdated(0.0f);
}

void VirtualEncoder::updatePosition() {
    QMutexLocker locker(&stateMutex);
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 deltaTime = currentTime - lastUpdateTime;  // Unit: ms
    lastUpdateTime = currentTime;

    // Integrate position from velocity and elapsed time.
    currentPosition += velocity * (deltaTime / 1000.0);

    const float updatedPosition = currentPosition;
    locker.unlock();
    emit positionUpdated(updatedPosition);
}

float VirtualEncoder::readPosition() {
    QMutexLocker locker(&stateMutex);
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 deltaTime = currentTime - lastUpdateTime;  // Unit: ms
    lastUpdateTime = currentTime;

    // Integrate position from velocity and elapsed time.
    currentPosition += velocity * (deltaTime / 1000.0);

    return currentPosition;
}

int VirtualEncoder::readInterval()
{
    QMutexLocker locker(&stateMutex);
    return intervalMs;
}

bool VirtualEncoder::IsActive()
{
    QMutexLocker locker(&stateMutex);
    return isRun;
}
