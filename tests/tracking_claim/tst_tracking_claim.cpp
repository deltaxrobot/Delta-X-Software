#include <QtTest>
#include <future>

#include "TrackingManager.h"

class TrackingClaimTest : public QObject
{
    Q_OBJECT

private slots:
    void claimsDownstreamObjectMatchingType();
    void concurrentWorkersCannotClaimSameObject();
    void detectionRefreshPreservesClaimAndPickedState();
    void nearbyDetectionsKeepDistinctUIDs();
    void managerClaimsAcrossTrackingThreadAndPublishesResult();
    void staleTrackingDoesNotIssueNewClaim();
    void staleEncoderDoesNotIssueNewClaim();
    void newTracksRequireConfirmation();
    void globalAssignmentIsIndependentOfDetectionOrder();
    void labelJitterPreservesUidAndUsesTypeHysteresis();
    void missedFramesExpireOnlyUnclaimedTracks();
    void staleRecoveryDropsUnclaimedGhosts();
    void expiredLeaseRejectsCompletion();
    void frameCommitUsesMatchingEncoderSamples();
    void encoderKeepsTracksMovingWhileVisionIsStale();
    void exactFrameMetadataCannotCrossPair();
    void wrongVisionRequestIsRejected();
    void realtimePublicationIsThrottledWithoutStaleInternalPose();
    void boundedFrameQueueRejectsOverload();
    void syntheticEncoderStressKeepsPublicationBounded();
    void virtualEncoderFollowsTrackingThread();
};

void TrackingClaimTest::claimsDownstreamObjectMatchingType()
{
    Tracking tracking;
    tracking.VelocityVector = QVector3D(1, 0, 0);
    tracking.AddObjectDirectly(ObjectInfo(-1, 1, QVector3D(20, 5, 0), 10, 20, 0));
    tracking.AddObjectDirectly(ObjectInfo(-1, 2, QVector3D(80, 5, 0), 10, 20, 0));
    tracking.AddObjectDirectly(ObjectInfo(-1, 1, QVector3D(60, 5, 0), 10, 20, 0));

    const QVariantMap first = tracking.ClaimObject("robot0", 0, 100, 0, 10, 1, 5000);
    QVERIFY(first.value("Found").toBool());
    QCOMPARE(first.value("UID").toInt(), 2);
    QCOMPARE(first.value("Type").toInt(), 1);

    const QVariantMap second = tracking.ClaimObject("robot1", 0, 100, 0, 10, 1, 5000);
    QVERIFY(second.value("Found").toBool());
    QCOMPARE(second.value("UID").toInt(), 0);

    const QVariantMap retry = tracking.ClaimObject("robot0", 0, 100, 0, 10, 1, 5000);
    QCOMPARE(retry.value("UID").toInt(), 2);

    const QVariantMap secondClaimForSameOwner =
        tracking.ClaimObject("robot0", 0, 30, 0, 10, 1, 5000);
    QVERIFY(!secondClaimForSameOwner.value("Found").toBool());
}

void TrackingClaimTest::concurrentWorkersCannotClaimSameObject()
{
    Tracking tracking;
    tracking.AddObjectDirectly(ObjectInfo(-1, 7, QVector3D(50, 5, 0), 10, 20, 0));

    std::promise<void> startPromise;
    std::shared_future<void> start = startPromise.get_future().share();
    auto claim = [&tracking, start](const QString& owner) {
        start.wait();
        return tracking.ClaimObject(owner, 0, 100, 0, 10, -1, 5000);
    };

    auto robot0 = std::async(std::launch::async, claim, QString("robot0"));
    auto robot1 = std::async(std::launch::async, claim, QString("robot1"));
    startPromise.set_value();

    const QVariantMap result0 = robot0.get();
    const QVariantMap result1 = robot1.get();
    QCOMPARE(result0.value("Found").toBool() + result1.value("Found").toBool(), 1);
}

void TrackingClaimTest::detectionRefreshPreservesClaimAndPickedState()
{
    Tracking tracking;
    tracking.DistanceThreshold = 20;
    tracking.AddObjectDirectly(ObjectInfo(-1, 3, QVector3D(10, 10, 0), 10, 20, 5));

    QVariantMap claimed = tracking.ClaimObject("robot0", 0, 100, 0, 100, -1, 5000);
    QVERIFY(claimed.value("Found").toBool());
    const int uid = claimed.value("UID").toInt();

    QVector<ObjectInfo> refreshed;
    refreshed.append(ObjectInfo(-1, 3, QVector3D(11, 10, 0), 10, 20, 6));
    tracking.UpdateTrackedObjects(refreshed, tracking.ListName);
    tracking.UpdateTrackedObjectOffsets(QVector3D());

    QVector<ObjectInfo> snapshot = tracking.getTrackedObjectsCopy();
    QCOMPARE(snapshot.size(), 1);
    QCOMPARE(snapshot.first().claimOwner, QString("robot0"));
    QVERIFY(!snapshot.first().isPicked);

    QVERIFY(tracking.CompleteObject(uid, "robot0"));
    tracking.UpdateTrackedObjects(refreshed, tracking.ListName);
    tracking.UpdateTrackedObjectOffsets(QVector3D());

    snapshot = tracking.getTrackedObjectsCopy();
    QCOMPARE(snapshot.size(), 1);
    QVERIFY(snapshot.first().isPicked);
    QVERIFY(snapshot.first().claimOwner.isEmpty());
}

void TrackingClaimTest::nearbyDetectionsKeepDistinctUIDs()
{
    Tracking tracking;
    tracking.IoUThreshold = 0;
    tracking.DistanceThreshold = 20;
    tracking.AddObjectDirectly(ObjectInfo(-1, 4, QVector3D(0, 0, 0), 10, 10, 0));
    tracking.AddObjectDirectly(ObjectInfo(-1, 4, QVector3D(8, 0, 0), 10, 10, 0));

    QVector<ObjectInfo> refreshed;
    refreshed.append(ObjectInfo(-1, 4, QVector3D(1, 0, 0), 10, 10, 0));
    refreshed.append(ObjectInfo(-1, 4, QVector3D(9, 0, 0), 10, 10, 0));
    tracking.UpdateTrackedObjects(refreshed, tracking.ListName);
    tracking.UpdateTrackedObjectOffsets(QVector3D());

    const QVector<ObjectInfo> snapshot = tracking.getTrackedObjectsCopy();
    QCOMPARE(snapshot.size(), 2);
    QCOMPARE(snapshot.at(0).center.x(), 1.0f);
    QCOMPARE(snapshot.at(1).center.x(), 9.0f);
}

void TrackingClaimTest::managerClaimsAcrossTrackingThreadAndPublishesResult()
{
    TrackingManager manager;
    manager.ProjectName = "claim_test_project";
    QSignalSpy responseSpy(&manager, &TrackingManager::GotResponse);

    QThread trackingThread;
    Tracking* tracking = new Tracking;
    ObjectInfo detected(-1, 9, QVector3D(25, 25, 0), 10, 10, 0);
    detected.confidence = 0.91;
    detected.label = QStringLiteral("part-a");
    detected.externalId = QStringLiteral("camera-42");
    tracking->AddObjectDirectly(detected);
    tracking->MoveToThread(&trackingThread);
    manager.Trackings.append(tracking);
    trackingThread.start();

    manager.ClaimObject(0, "Target", "robot0", 0, 50, 0, 50, 9, 5000);

    QCOMPARE(responseSpy.size(), 1);
    QCOMPARE(responseSpy.first().at(0).toString(), QString("tracking0:robot0"));
    QCOMPARE(responseSpy.first().at(1).toString(), QString("Claimed"));

    QVERIFY(VariableManager::instance().getVar("claim_test_project.Target.Found").toBool());
    QCOMPARE(VariableManager::instance().getVar("claim_test_project.Target.UID").toInt(), 0);
    QCOMPARE(VariableManager::instance().getVar("claim_test_project.Target.Type").toInt(), 9);
    QCOMPARE(VariableManager::instance().getVar("claim_test_project.Target.Confidence").toDouble(), 0.91);
    QCOMPARE(VariableManager::instance().getVar("claim_test_project.Target.Label").toString(),
             QStringLiteral("part-a"));
    QCOMPARE(VariableManager::instance().getVar("claim_test_project.Target.ExternalId").toString(),
             QStringLiteral("camera-42"));

    QMetaObject::invokeMethod(tracking, "deleteLater", Qt::QueuedConnection);
    trackingThread.quit();
    QVERIFY(trackingThread.wait(2000));
}

void TrackingClaimTest::virtualEncoderFollowsTrackingThread()
{
    QThread trackingThread;
    Tracking* tracking = new Tracking;
    tracking->ID = 8;
    tracking->MoveToThread(&trackingThread);

    QCOMPARE(tracking->thread(), &trackingThread);
    QCOMPARE(tracking->VirEncoder.thread(), &trackingThread);

    int updates = 0;
    QThread* callbackThread = nullptr;
    connect(tracking, &Tracking::VirtualEncoderPositionUpdated, this,
            [&updates, &callbackThread](int id, float) {
        QCOMPARE(id, 8);
        ++updates;
        callbackThread = QThread::currentThread();
    });

    trackingThread.start();
    QVERIFY(QMetaObject::invokeMethod(
        tracking, "SetEncoderSourceType", Qt::QueuedConnection,
        Q_ARG(QString, QStringLiteral("Virtual Encoder"))));
    QVERIFY(QMetaObject::invokeMethod(
        tracking, "SetVirtualEncoderVelocity", Qt::QueuedConnection,
        Q_ARG(float, 100.0f)));
    QVERIFY(QMetaObject::invokeMethod(
        tracking, "StartVirtualEncoder", Qt::QueuedConnection, Q_ARG(int, 10)));

    QTRY_VERIFY_WITH_TIMEOUT(updates >= 2, 1000);
    QCOMPARE(callbackThread, QThread::currentThread());

    QVERIFY(QMetaObject::invokeMethod(
        tracking, [tracking]() { delete tracking; }, Qt::BlockingQueuedConnection));
    trackingThread.quit();
    QVERIFY(trackingThread.wait(2000));
}

void TrackingClaimTest::staleTrackingDoesNotIssueNewClaim()
{
    Tracking tracking;
    tracking.detectionStaleTimeoutMs = 1;
    tracking.AddObjectDirectly(ObjectInfo(-1, 5, QVector3D(10, 10, 0), 10, 10, 0));
    QTest::qWait(5);

    const QVariantMap result = tracking.ClaimObject("robot0", 0, 20, 0, 20, -1, 5000);
    QVERIFY(!result.value("Found").toBool());
}

void TrackingClaimTest::staleEncoderDoesNotIssueNewClaim()
{
    Tracking tracking;
    tracking.detectionStaleTimeoutMs = 1000;
    tracking.encoderStaleTimeoutMs = 1;
    tracking.AddObjectDirectly(ObjectInfo(-1, 5, QVector3D(10, 10, 0), 10, 10, 0));
    QTest::qWait(5);

    const QVariantMap result = tracking.ClaimObject("robot0", 0, 20, 0, 20, -1, 5000);
    QVERIFY(!result.value("Found").toBool());
}

void TrackingClaimTest::newTracksRequireConfirmation()
{
    Tracking tracking;
    tracking.minConfirmationHits = 2;
    tracking.OnReceiveEncoderPosition(0.0f);

    QVector<ObjectInfo> detections;
    detections.append(ObjectInfo(-1, 2, QVector3D(10, 10, 0), 10, 10, 0));
    tracking.UpdateTrackedObjects(detections, tracking.ListName);

    QVariantMap firstClaim = tracking.ClaimObject("robot0", 0, 20, 0, 20, 2, 5000);
    QVERIFY(!firstClaim.value("Found").toBool());
    QCOMPARE(firstClaim.value("Status").toString(), QString("READY"));
    QCOMPARE(tracking.getTrackedObjectsCopy().first().confirmed, false);

    tracking.UpdateTrackedObjects(detections, tracking.ListName);
    QVariantMap secondClaim = tracking.ClaimObject("robot0", 0, 20, 0, 20, 2, 5000);
    QVERIFY(secondClaim.value("Found").toBool());
    QCOMPARE(tracking.getTrackedObjectsCopy().first().confirmed, true);
}

void TrackingClaimTest::globalAssignmentIsIndependentOfDetectionOrder()
{
    Tracking tracking;
    tracking.IoUThreshold = 0;
    tracking.DistanceThreshold = 20;
    tracking.AddObjectDirectly(ObjectInfo(-1, 1, QVector3D(0, 0, 0), 10, 10, 0));
    tracking.AddObjectDirectly(ObjectInfo(-1, 1, QVector3D(10, 0, 0), 10, 10, 0));

    QVector<ObjectInfo> detections;
    detections.append(ObjectInfo(-1, 1, QVector3D(6, 0, 0), 10, 10, 0));
    detections.append(ObjectInfo(-1, 1, QVector3D(11, 0, 0), 10, 10, 0));
    tracking.UpdateTrackedObjects(detections, tracking.ListName);

    const QVector<ObjectInfo> snapshot = tracking.getTrackedObjectsCopy();
    QCOMPARE(snapshot.size(), 2);
    QCOMPARE(snapshot.at(0).uid, 0);
    QCOMPARE(snapshot.at(0).center.x(), 6.0f);
    QCOMPARE(snapshot.at(1).uid, 1);
    QCOMPARE(snapshot.at(1).center.x(), 11.0f);
}

void TrackingClaimTest::labelJitterPreservesUidAndUsesTypeHysteresis()
{
    Tracking tracking;
    tracking.DistanceThreshold = 10;
    tracking.typeSwitchConfirmationHits = 3;
    tracking.AddObjectDirectly(ObjectInfo(-1, 0, QVector3D(10, 10, 0), 10, 10, 0));

    for (int frame = 0; frame < 2; ++frame) {
        QVector<ObjectInfo> detections;
        detections.append(ObjectInfo(-1, 1, QVector3D(11 + frame, 10, 0), 10, 10, 0));
        tracking.UpdateTrackedObjects(detections, tracking.ListName);
        const QVector<ObjectInfo> snapshot = tracking.getTrackedObjectsCopy();
        QCOMPARE(snapshot.size(), 1);
        QCOMPARE(snapshot.first().uid, 0);
        QCOMPARE(snapshot.first().type, 0);
    }

    QVector<ObjectInfo> thirdDetection;
    thirdDetection.append(ObjectInfo(-1, 1, QVector3D(13, 10, 0), 10, 10, 0));
    tracking.UpdateTrackedObjects(thirdDetection, tracking.ListName);
    const QVector<ObjectInfo> snapshot = tracking.getTrackedObjectsCopy();
    QCOMPARE(snapshot.size(), 1);
    QCOMPARE(snapshot.first().uid, 0);
    QCOMPARE(snapshot.first().type, 1);
}

void TrackingClaimTest::missedFramesExpireOnlyUnclaimedTracks()
{
    Tracking tracking;
    tracking.maxMissedFrames = 2;
    tracking.AddObjectDirectly(ObjectInfo(-1, 0, QVector3D(10, 10, 0), 10, 10, 0));
    const QVariantMap claim = tracking.ClaimObject("robot0", 0, 20, 0, 20, -1, 5000);
    QVERIFY(claim.value("Found").toBool());

    for (int frame = 0; frame < 3; ++frame)
        tracking.UpdateTrackedObjects({}, tracking.ListName);
    QCOMPARE(tracking.getTrackedObjectsCopy().size(), 1);

    QVERIFY(tracking.ReleaseObject(claim.value("UID").toInt(), "robot0"));
    tracking.UpdateTrackedObjects({}, tracking.ListName);
    QCOMPARE(tracking.getTrackedObjectsCopy().size(), 0);
}

void TrackingClaimTest::staleRecoveryDropsUnclaimedGhosts()
{
    Tracking tracking;
    tracking.detectionStaleTimeoutMs = 1;
    tracking.AddObjectDirectly(ObjectInfo(-1, 0, QVector3D(0, 0, 0), 10, 10, 0));
    QTest::qWait(5);

    QVector<ObjectInfo> recoveredDetection;
    recoveredDetection.append(ObjectInfo(-1, 0, QVector3D(100, 0, 0), 10, 10, 0));
    tracking.UpdateTrackedObjects(recoveredDetection, tracking.ListName);

    const QVector<ObjectInfo> snapshot = tracking.getTrackedObjectsCopy();
    QCOMPARE(snapshot.size(), 1);
    QVERIFY(snapshot.first().uid != 0);
    QCOMPARE(snapshot.first().center.x(), 100.0f);
}

void TrackingClaimTest::expiredLeaseRejectsCompletion()
{
    Tracking tracking;
    tracking.AddObjectDirectly(ObjectInfo(-1, 0, QVector3D(10, 10, 0), 10, 10, 0));
    const QVariantMap claim = tracking.ClaimObject("robot0", 0, 20, 0, 20, -1, 1000);
    QVERIFY(claim.value("Found").toBool());
    QTest::qWait(1050);

    QVERIFY(!tracking.CompleteObject(claim.value("UID").toInt(), "robot0"));
    QVERIFY(tracking.getTrackedObjectsCopy().first().claimOwner.isEmpty());
}

void TrackingClaimTest::frameCommitUsesMatchingEncoderSamples()
{
    Tracking tracking;
    tracking.EncoderType = "Virtual Encoder";
    tracking.minConfirmationHits = 1;
    QSignalSpy frameSpy(&tracking, &Tracking::DetectionFrameCommitted);

    tracking.VirEncoder.setPosition(100.0f);
    tracking.SaveCapturePosition();
    tracking.VirEncoder.setPosition(108.0f);

    QVector<ObjectInfo> detections;
    detections.append(ObjectInfo(-1, 0, QVector3D(50, 20, 0), 10, 10, 0));
    tracking.UpdateTrackedObjects(detections, tracking.ListName);

    QCOMPARE(frameSpy.size(), 1);
    QCOMPARE(tracking.LastCommittedFrameId(), quint64(1));
    const QVector<ObjectInfo> snapshot = tracking.getTrackedObjectsCopy();
    QCOMPARE(snapshot.size(), 1);
    QCOMPARE(snapshot.first().center.x(), 50.0f);
    QCOMPARE(snapshot.first().center.y(), 28.0f);
}

void TrackingClaimTest::encoderKeepsTracksMovingWhileVisionIsStale()
{
    Tracking tracking;
    tracking.VelocityVector = QVector3D(1, 0, 0);
    tracking.detectionStaleTimeoutMs = 1;
    tracking.AddObjectDirectly(ObjectInfo(-1, 0, QVector3D(0, 0, 0), 10, 10, 0));
    QTest::qWait(5);

    tracking.OnReceiveEncoderPosition(12.0f);
    QCOMPARE(tracking.getTrackedObjectsCopy().first().center.x(), 12.0f);
    QCOMPARE(tracking.HealthStatus(), QString("VISION_STALE"));
}

void TrackingClaimTest::exactFrameMetadataCannotCrossPair()
{
    Tracking tracking;
    tracking.EncoderType = "Virtual Encoder";
    tracking.minConfirmationHits = 1;
    QSignalSpy committed(&tracking, &Tracking::DetectionFrameCommitted);

    tracking.VirEncoder.setPosition(10.0f);
    tracking.SaveCapturePosition(41, 1001);
    tracking.VirEncoder.setPosition(20.0f);
    tracking.SaveCapturePosition(42, 1002);

    QVector<ObjectInfo> second;
    second.append(ObjectInfo(-1, 2, QVector3D(200, 0, 0), 10, 10, 0));
    tracking.VirEncoder.setPosition(25.0f);
    tracking.UpdateTrackedObjectsForFrame(second, 42, 1002);
    QCOMPARE(committed.size(), 0); // Frame 41 remains the ordered commit barrier.

    QVector<ObjectInfo> first;
    first.append(ObjectInfo(-1, 1, QVector3D(100, 0, 0), 10, 10, 0));
    tracking.VirEncoder.setPosition(30.0f);
    tracking.UpdateTrackedObjectsForFrame(first, 41, 1001);

    QCOMPARE(committed.size(), 2);
    QCOMPARE(committed.at(0).at(1).toULongLong(), quint64(41));
    QCOMPARE(committed.at(0).at(2).toULongLong(), quint64(1001));
    QCOMPARE(committed.at(1).at(1).toULongLong(), quint64(42));
    QCOMPARE(committed.at(1).at(2).toULongLong(), quint64(1002));
}

void TrackingClaimTest::wrongVisionRequestIsRejected()
{
    Tracking tracking;
    tracking.EncoderType = "Virtual Encoder";
    QSignalSpy committed(&tracking, &Tracking::DetectionFrameCommitted);
    QSignalSpy rejected(&tracking, &Tracking::DetectionFrameRejected);

    tracking.SaveCapturePosition(77, 9001);
    tracking.UpdateTrackedObjectsForFrame({}, 77, 9002);

    QCOMPARE(committed.size(), 0);
    QCOMPARE(rejected.size(), 1);
    QCOMPARE(rejected.first().at(1).toULongLong(), quint64(77));
    QCOMPARE(rejected.first().at(2).toULongLong(), quint64(9002));
}

void TrackingClaimTest::realtimePublicationIsThrottledWithoutStaleInternalPose()
{
    const QString scope = QStringLiteral("tracking_realtime_throttle_test");
    VariableManager::instance().removeVarScoped(scope, QString());

    Tracking tracking;
    tracking.ProjectName = scope;
    tracking.ID = 3;
    tracking.VelocityVector = QVector3D(1, 0, 0);
    tracking.ConfigureRealtime(5000, 2000, 2000, 3000, 8, 24);
    tracking.AddObjectDirectly(ObjectInfo(-1, 0, QVector3D(0, 0, 0), 10, 10, 0));

    const qulonglong publishedBefore =
        tracking.RealtimeSnapshot().value(QStringLiteral("Publications")).toULongLong();
    tracking.OnReceiveEncoderPosition(10.0f);

    QCOMPARE(tracking.getTrackedObjectsCopy().first().center.x(), 10.0f);
    QCOMPARE(VariableManager::instance()
                 .getVarScoped(scope, QStringLiteral("Objects.0.X")).toFloat(), 0.0f);
    QCOMPARE(tracking.RealtimeSnapshot().value(QStringLiteral("Publications")).toULongLong(),
             publishedBefore);
    QVERIFY(tracking.RealtimeSnapshot()
                .value(QStringLiteral("PublicationsSuppressed")).toULongLong() >= 1);

    tracking.PublishNow();
    QCOMPARE(VariableManager::instance()
                 .getVarScoped(scope, QStringLiteral("Objects.0.X")).toFloat(), 10.0f);
    QCOMPARE(VariableManager::instance()
                 .getVarScoped(scope, QStringLiteral("Tracking.3.PendingFrames")).toInt(), 0);
    VariableManager::instance().removeVarScoped(scope, QString());
}

void TrackingClaimTest::boundedFrameQueueRejectsOverload()
{
    Tracking tracking;
    tracking.ID = 4;
    tracking.EncoderType = QStringLiteral("X Encoder");
    tracking.ConfigureRealtime(50, 2000, 2000, 3000, 2, 8);
    QSignalSpy rejected(&tracking, &Tracking::DetectionFrameRejected);

    tracking.SaveCapturePosition(1, 101);
    tracking.SaveCapturePosition(2, 102);
    tracking.SaveCapturePosition(3, 103);

    QCOMPARE(rejected.size(), 1);
    QCOMPARE(rejected.first().at(1).toULongLong(), quint64(3));
    QCOMPARE(rejected.first().at(2).toULongLong(), quint64(103));
    const QVariantMap telemetry = tracking.RealtimeSnapshot();
    QCOMPARE(telemetry.value(QStringLiteral("PendingFrames")).toInt(), 2);
    QCOMPARE(telemetry.value(QStringLiteral("FrameQueueOverflows")).toULongLong(),
             qulonglong(1));
    QCOMPARE(telemetry.value(QStringLiteral("LastFault")).toString(),
             QStringLiteral("FRAME_QUEUE_OVERFLOW"));
}

void TrackingClaimTest::syntheticEncoderStressKeepsPublicationBounded()
{
    const QString scope = QStringLiteral("tracking_realtime_stress_test");
    VariableManager::instance().removeVarScoped(scope, QString());

    Tracking tracking;
    tracking.ProjectName = scope;
    tracking.VelocityVector = QVector3D(1, 0, 0);
    tracking.X_min = -10000;
    tracking.X_max = 10000;
    tracking.Y_min = -10000;
    tracking.Y_max = 10000;
    tracking.minConfirmationHits = 1;
    tracking.ConfigureRealtime(5000, 10000, 10000, 3000, 8, 24);

    QVector<ObjectInfo> detections;
    detections.reserve(100);
    for (int i = 0; i < 100; ++i)
        detections.append(ObjectInfo(-1, i % 4, QVector3D(i * 2, i, 0), 10, 10, 0));
    tracking.UpdateTrackedObjects(detections, tracking.ListName);

    QElapsedTimer timer;
    timer.start();
    for (int sample = 0; sample < 1000; ++sample)
        tracking.OnReceiveEncoderPosition(static_cast<float>(sample));

    const QVector<ObjectInfo> objects = tracking.getTrackedObjectsCopy();
    QCOMPARE(objects.size(), 100);
    QCOMPARE(objects.first().center.x(), 999.0f);
    QVERIFY2(timer.elapsed() < 5000,
             qPrintable(QString("Synthetic tracking stress took %1 ms").arg(timer.elapsed())));
    const QVariantMap telemetry = tracking.RealtimeSnapshot();
    QVERIFY(telemetry.value(QStringLiteral("PublicationsSuppressed")).toULongLong() >= 900);
    QVERIFY(telemetry.value(QStringLiteral("Publications")).toULongLong() < 10);
    VariableManager::instance().removeVarScoped(scope, QString());
}

QTEST_MAIN(TrackingClaimTest)
#include "tst_tracking_claim.moc"
