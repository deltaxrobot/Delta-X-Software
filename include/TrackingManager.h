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
#include <QVector>
#include <algorithm>
#include <QMutex>
#include <QMutexLocker>
#include <QMetaType>
#include <QVariantMap>
#include <QThread>
#include <QSet>
#include <QQueue>
#include <QHash>
#include "VisionDetections.h"

class VirtualEncoder : public QObject {
    Q_OBJECT
private:
    QTimer timer;
    qint64 lastUpdateTime;
    float velocity;  // Unit: mm/s
    float currentPosition;  // Unit: mm
    bool isRun = false;
    int intervalMs = 100;
    mutable QMutex stateMutex;

public:
    VirtualEncoder(float initialPosition = 0.0, float velocity = 0.0, QObject* parent = nullptr);

    void MoveToThread(QThread* thread);
    void setVelocity(float newVelocity);
    void setPosition(float newPos);
    float readPosition();
    int readInterval();
    bool IsActive();
public slots:
    void stop();
    // Restart the virtual encoder.
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
    void MoveToThread(QThread* thread);
    void UpdateTrackedObjectsPosition(float moved);
    QString GetListName() const;
    QString GetEncoderName() const;
    QString GetVectorName() const;
    float GetIoUThreshold() const;
    float GetDistanceThreshold() const;

    QVector<ObjectInfo> TrackedObjects;

    float displacement = 0;
    float SimilarityThreshold = 20;
    float IoUThreshold = 0.3f;
    float DistanceThreshold = 7;
    int nextID = 0;

    QVector3D VelocityVector = QVector3D(0, 100, 0);
    QString VectorName = "#Vector1";

    QVector3D TestPointOffset = QVector3D(0, 0, 0);
    bool IsUpateTestPoint = false;

    QString EncoderName = "encoder0";
    QString EncoderType = "X Encoder";
    QString ProjectName = "project0";
    bool IsReverse = false;
    QString ListName = "#Objects";

    VirtualEncoder VirEncoder;
    QElapsedTimer lastDetectionTimer;
    QElapsedTimer lastEncoderTimer;
    int detectionStaleTimeoutMs = 2000;
    int encoderStaleTimeoutMs = 2000;
    int frameTimeoutMs = 3000;
    int publishIntervalMs = 50;
    int maxPendingFrames = 8;
    int maxPendingEncoderReads = 24;

    // Track lifecycle and association tuning.
    int minConfirmationHits = 2;
    int maxMissedFrames = 5;
    int maxTentativeMissedFrames = 1;
    int typeSwitchConfirmationHits = 3;
    float typeMismatchDistanceFactor = 0.6f;

    float lastEncoderPositionAtCapture = 0.0;
    float lastEncoderPositionAtMapping = 0.0;

    int ID = 0;
    QString ReadPurpose = "Update";
    bool clientWaiting = false;
    float X_max = 1200, X_min = -300, Y_max = 1200, Y_min = -400; // Boundary coordinates


signals:
    void DistanceMoved(QPointF offset);
    void TestPointUpdated(QVector3D testPointOffset);
    void SendGcodeRequest(QString deviceName, QString gcode);
    void UpdateTrackingDone();
    void UpdateTrackingDone(int id);
    void DetectionFrameCommitted(int id, quint64 frameId, quint64 requestId);
    void DetectionFrameRejected(int id, quint64 frameId, quint64 requestId, QString reason);
    void SnapshotPublished(int id, QVector<ObjectInfo> objects);
    void VirtualEncoderPositionUpdated(int id, float position);

public slots:
    void OnReceivceEncoderPosition(float value);
    // Alias with correct spelling for clarity; keeps backward compatibility
    void OnReceiveEncoderPosition(float value);
    void ChangeObjectInfo(QString cmd);
    void GetVirtualEncoderPosition();
    void ReadEncoder();
    void SetEncoderReverse(bool isReverse);
    void SetAssociationThresholds(float iouThreshold, float distanceThreshold);
    void SetTrackingBounds(float minX, float maxX, float minY, float maxY);
    void SetListName(QString listName);
    void SetEncoderName(QString encoderName);
    void SetVectorName(QString vectorName);
    void SetEncoderSourceType(QString encoderType);
    void StartVirtualEncoder(int interval = 100);
    void StopVirtualEncoder();
    void ResetVirtualEncoder();
    void SetVirtualEncoderVelocity(float velocity);
    void SetVirtualEncoderPosition(float position);
    void SaveCapturePosition();
    void SaveCapturePosition(quint64 frameId, quint64 requestId);
    void SaveDetectPosition();
    void UpdateTrackedObjectsForFrame(QVector<ObjectInfo> detectedObjects,
                                      quint64 frameId, quint64 requestId);
    void RejectPendingFrame(quint64 frameId, quint64 requestId, QString reason);
    void SetClientWaiting(bool waiting) { clientWaiting = waiting; }
    void SetUpdateTestPoint(bool enabled);

    void UpdateTrackedObjects(QVector<ObjectInfo> detectedObjects, QString objectListName);
    void UpdateTrackedObjectOffsets(QVector3D offset);
    void GetObjectsInArea(QString inAreaListName, float min, float max, bool isXDirection = true);

    void updatePositions(double displacement);
    void ClearTrackedObjects();
    void RemoveTrackedObjects(int id);
    void SetObjectPickedByUID(int uid);
    void AddObjectDirectly(const ObjectInfo& obj);
    QVector<ObjectInfo> getTrackedObjectsCopy() const;
    QVariantMap RealtimeSnapshot() const;
    void ConfigureRealtime(int publishMs, int visionStaleMs, int encoderStaleMs,
                           int pendingFrameTimeoutMs, int pendingFrameLimit,
                           int pendingEncoderLimit);
    void StartRealtimeMonitor();
    void PublishNow();

    // Atomically reserve one downstream-most object in a robot work area.
    // The returned map contains Found, UID, Type, X/Y/Z, W/L/A and lease data.
    QVariantMap ClaimObject(const QString& owner, float minX, float maxX,
                            float minY, float maxY, int typeFilter = -1,
                            int leaseMs = 30000);
    bool ReleaseObject(int uid, const QString& owner);
    bool CompleteObject(int uid, const QString& owner);
    QString HealthStatus() const;
    quint64 LastCommittedFrameId() const;
private:
    QVector3D calculateMoved(float distance);
    double similarity(ObjectInfo& obj1, ObjectInfo& obj2, double displacement);
    double calculateIoU(const ObjectInfo& obj1, const ObjectInfo& obj2) const;
    bool isSameObject(const ObjectInfo& object1, const ObjectInfo& object2) const;
    float lastPosition = 0;
    float capturePosition = 0;
    float detectPosition = 0;
    float currentPosition = 0;
    bool first = true;
    QList<int> updatedObjectIDList;
    QVector<ObjectInfo> DetectedObjects;
    
    // Thread safety
    mutable QMutex dataMutex;
    QMutex publicationMutex;

    enum class EncoderReadPurpose { Capture, Detect, Update };
    struct PendingEncoderRead {
        EncoderReadPurpose purpose = EncoderReadPurpose::Update;
        quint64 frameId = 0;
        bool notifyClient = false;
    };
    struct PendingFrame {
        quint64 id = 0;
        quint64 requestId = 0;
        qint64 createdAtMonotonicMs = 0;
        bool hasCapturePosition = false;
        float capturePosition = 0.0f;
        bool hasDetections = false;
        QVector<ObjectInfo> detections;
        bool detectReadRequested = false;
        bool hasDetectPosition = false;
        float detectPosition = 0.0f;
    };

    QElapsedTimer monotonicClock;
    qint64 lastDetectionAtMonotonicMs = -1;
    qint64 lastEncoderAtMonotonicMs = -1;
    quint64 nextFrameId = 1;
    quint64 lastCommittedFrameId = 0;
    QQueue<PendingEncoderRead> pendingEncoderReads;
    QQueue<PendingFrame> pendingFrames;

    QElapsedTimer lastPublicationTimer;
    QTimer* realtimeMonitorTimer = nullptr;
    quint64 framesCaptured = 0;
    quint64 framesCommitted = 0;
    quint64 framesRejected = 0;
    quint64 framesExpired = 0;
    quint64 frameQueueOverflows = 0;
    quint64 encoderQueueOverflows = 0;
    quint64 encoderSamples = 0;
    quint64 publicationCount = 0;
    quint64 publicationSuppressed = 0;
    qint64 lastCommitLatencyMs = 0;
    qint64 maxCommitLatencyMs = 0;
    qint64 lastPublishDurationUs = 0;
    qint64 maxPublishDurationUs = 0;
    QString lastRealtimeFault;

    bool requestEncoderRead(EncoderReadPurpose purpose, quint64 frameId = 0,
                            bool notifyClient = false);
    void tryCommitFrames();
    void commitDetectionFrame(PendingFrame frame);
    void associateDetectionsLocked(QVector<ObjectInfo> detectedObjects,
                                   const QVector3D& offset,
                                   qint64 nowEpochMs,
                                   qint64 nowMonotonicMs);
    QVector<int> solveGlobalAssignmentLocked(const QVector<ObjectInfo>& detections) const;
    double associationCostLocked(const ObjectInfo& detection,
                                 const ObjectInfo& track) const;
    QVector<PendingFrame> purgeExpiredFramesLocked(qint64 nowMonotonicMs);
    void expireClaimsLocked(qint64 nowEpochMs, qint64 nowMonotonicMs);
    QString healthStatusLocked(qint64 nowMonotonicMs) const;
    QString trackStateLocked(const ObjectInfo& object) const;
    QVariantMap objectToResult(const ObjectInfo& object) const;
    void publishTrackedObjectsSnapshot(bool force = true);
    QVariantMap realtimeSnapshotLocked(qint64 nowMonotonicMs) const;
    void emitRejectedFrames(const QVector<PendingFrame>& frames, const QString& reason);
    int publishedObjectCount = 0;

};

class TrackingManager : public QObject
{
    Q_OBJECT
public:
    explicit TrackingManager(QObject *parent = nullptr);

    QList<Tracking*> Trackings;
    int currentTrackingRequest = 0;

public slots:
    void SaveCapturePosition(int id, quint64 frameId, quint64 requestId);
    void SaveDetectPosition(int id);
    void UpdateTracking(int id);
    void GetObjectsInArea(int trackingID, QString inAreaListName, float min, float max, bool isXDirection = true);
    void UpdateVariable(QString cmd);
    void AddObject(QString listName, QList<QStringList> list);
    void ClearObjects(QString listName);
    void SetObjectPickedByUID(QString listName, int uid);
    void AddObjectToTracking(QString listName, const ObjectInfo& obj);
    void SetEncoderPosition(int id, float value);
    void ReloadEncoderCalibration(int id);
    void ClaimObject(int trackingID, QString resultName, QString owner,
                     float minX, float maxX, float minY, float maxY,
                     int typeFilter = -1, int leaseMs = 30000);
    void ReleaseObject(int trackingID, int uid, QString owner);
    void CompleteObject(int trackingID, int uid, QString owner);
    void ReadEncoderWhenSensorActive(int id);
    void OnDoneUpdateTracking(int id);
    void OnDoneUpdateTracking();
    void SubmitDetections(VisionDetections detections);
    void RejectVisionFrame(int trackingId, quint64 frameId, quint64 requestId, QString reason);
    void OnCaptureFailed(int trackingId, quint64 requestId, QString reason);
    void OnDetectionFrameCommitted(int id, quint64 frameId, quint64 requestId);
    void OnDetectionFrameRejected(int id, quint64 frameId, quint64 requestId, QString reason);

signals:
    void GotResponse(QString deviceId, QString response);

public:
    QString ProjectName = "project0";

private:
    struct EncoderCalibrationProfile {
        bool loaded = false;
        bool isValid = false;
        float scale = 1.0f;
        float rawReference = 0.0f;
        float worldReference = 0.0f;
    };

    float calibratedEncoderPosition(int id, float rawValue);
    QHash<int, EncoderCalibrationProfile> encoderCalibrationProfiles;
    QString qualifyResultName(const QString& resultName) const;
    void publishClaimResult(const QString& resultName, const QVariantMap& result);

};
#endif // TRACKINGMANAGER_H
