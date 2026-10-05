#include <QtTest>
#include <QLabel>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include "RelativeMouseCapture.h"
#include <limits>
#include <cmath>
#include "MouseJogController.h"
#include "MouseJogDialog.h"
#include "GcodeMotionPlanner.h"

using namespace GcodeMotion;
namespace {
class FakeMouseCapture : public RelativeMouseCapture {
public:
    bool available() const override { return true; }
    bool start(QWidget*) override { m_active = canStart; return m_active; }
    void stop() override { m_active = false; }
    void move(QPoint counts) { if (m_active) emit moved(counts); }
    bool canStart = true;
};
double value(const QString& command, QChar key)
{
    for (const auto& token : command.split(' '))
        if (token.startsWith(key)) return token.mid(1).toDouble();
    return 0;
}
QVector3D endpoint(const QString& command)
{
    return {float(value(command, 'X')), float(value(command, 'Y')), float(value(command, 'Z'))};
}
// The emulated controller starts its next queued move without a host round trip.
// Time estimates only model the protocol; these tests do not prove real motion.
class RobotEmulator : public QObject {
public:
    explicit RobotEmulator(DeviceCommandBroker& broker) : broker(broker) {
        connect(&broker, &DeviceCommandBroker::DispatchCommand, this,
            [this](const QString& device, const QString& command) {
                if (device == "robot1" && command == "M205 S0") {
                    QTimer::singleShot(1, this, [this]() { this->broker.HandleDeviceResponse("robot1", "Ok"); });
                    return;
                }
                if (device != "robot1" || !command.startsWith("G01 ")) return;
                commands.append(command);
                if (queue.isEmpty() && value(command, 'S') != 0) restartedFromRest = false;
                Limits limits;
                limits.speed = int(value(command, 'F'));
                limits.acceleration = int(value(command, 'A'));
                limits.jerk = int(value(command, 'J'));
                const auto dest = endpoint(command);
                const double seconds = duration((dest - tail).length(), int(value(command, 'S')),
                                                int(value(command, 'E')), limits);
                finite = finite && std::isfinite(seconds);
                queue.append({dest, std::isfinite(seconds) ? qMax(1, qCeil(seconds * 1000)) : 1});
                tail = dest;
                maxDepth = qMax(maxDepth, queue.size());
                if (queue.size() == 1) next();
            });
    }
    void next() {
        if (queue.isEmpty()) return;
        QTimer::singleShot(queue.first().second, this, [this]() {
            position = queue.takeFirst().first;
            next();
            QTimer::singleShot(ackDelayMs, this, [this]() { broker.HandleDeviceResponse("robot1", "Ok"); });
        });
    }
    DeviceCommandBroker& broker;
    QVector<QPair<QVector3D, int>> queue;
    QStringList commands;
    QVector3D position{10, 20, -300}, tail{position};
    qsizetype maxDepth = 0;
    bool finite = true;
    int ackDelayMs = 0;
    bool restartedFromRest = true;
};
}

class MouseJogTest : public QObject
{
    Q_OBJECT
    static void initialize(DeviceCommandBroker& broker, MouseJogController& control) {
        QVERIFY(control.start());
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "10,20,-300");
        QVERIFY(control.ready());
    }
private slots:
    void targetVelocityIsBoundedAndExpires() {
        LiveTargetTracker tracker;
        tracker.reset({}, 0);
        for (int i = 1; i <= 10; ++i) tracker.observe({float(i), 0, 0}, i * 10);
        QCOMPARE(tracker.velocity(100, 150), QVector3D(100, 0, 0));
        QCOMPARE(tracker.velocity(100, 50), QVector3D(50, 0, 0));
        QCOMPARE(tracker.velocity(160, 150), QVector3D(50, 0, 0));
        QVERIFY(tracker.velocity(180, 150).isNull());
        tracker.observe({9, 0, 0}, 110);
        QVERIFY(tracker.velocity(110, 150).isNull());
        tracker.observe({8, 0, 0}, 120);
        QCOMPARE(tracker.velocity(120, 150), QVector3D(-100, 0, 0));
        tracker.observe({200, 0, 0}, 1000);
        QVERIFY(tracker.velocity(1000, 150).isNull());
        tracker.reset({}, 0);
        for (int i = 0; i < 100; ++i) tracker.observe({float(i), 0, 0}, 0);
        QVERIFY(tracker.velocity(0, 150).isNull());
    }
    void livePlanPredictionAndLimits() {
        Limits limits;
        limits.segmentLength = 8;
        QString error;
        auto moves = follow({{}, {}, 0}, {10, 0, 0}, {100, 0, 0}, 0.1, limits, &error);
        QVERIFY2(error.isEmpty(), qPrintable(error));
        QVERIFY(!moves.isEmpty());
        QCOMPARE(moves.last().end, QVector3D(13, 0, 0));
        QVERIFY((moves.first().end - moves.first().start).length() > 2);
        for (const auto& move : moves) {
            QVERIFY(std::isfinite(move.seconds));
            QVERIFY(move.feed <= limits.speed);
            QCOMPARE(move.acceleration, limits.acceleration);
            QCOMPARE(move.jerk, limits.jerk);
        }
        moves = follow({{}, {}, 0}, {10, 0, 0}, {}, 0.1, limits, &error);
        QCOMPARE(moves.last().end, QVector3D(10, 0, 0));
        QCOMPARE(moves.last().exit, 0);
        moves = follow({{}, {1, 0, 0}, 60}, {-10, 0, 0}, {-100, 0, 0}, 0, limits, &error);
        QVERIFY(error.isEmpty());
        QCOMPARE(moves.size(), 1);
        QVERIFY(moves.first().end.x() > 0);
        QCOMPARE(moves.first().exit, 0);
        moves = follow({{124.285f, 0, 0}, {1, 0, 0}, 78}, {130, 0, 0}, {}, 0, limits, &error);
        QVERIFY2(error.isEmpty(), qPrintable(error));
        QCOMPARE(moves.size(), 1);
        QCOMPARE(moves.first().end, QVector3D(130, 0, 0));
        QCOMPARE(moves.first().exit, 0);
        limits.jerk = 0;
        QVERIFY(follow({{}, {}, 0}, {10, 0, 0}, {}, 0, limits, &error).isEmpty());
        QVERIFY(!error.isEmpty());
    }
    void liveTrackingLatency_data() {
        QTest::addColumn<bool>("curved");
        QTest::newRow("straight") << false;
        QTest::newRow("curved") << true;
    }
    void stationaryFollowerHonorsMinimumCorrection() {
        const Limits limits;
        const State start{{10, 20, -300}, {}, 0};
        QString error;
        for (const float residual : {-0.2f, -0.1f, -0.02f, 0.02f, 0.1f, 0.2f}) {
            const auto moves = follow(start, start.position + QVector3D(residual, 0, 0),
                                      {}, 0, limits, &error);
            QVERIFY2(error.isEmpty(), qPrintable(error));
            QVERIFY(moves.isEmpty());
        }
        const auto target = start.position + QVector3D(0.25f, 0, 0);
        const auto moves = follow(start, target, {}, 0, limits, &error);
        QVERIFY2(error.isEmpty(), qPrintable(error));
        QVERIFY(!moves.isEmpty());
        QCOMPARE(moves.last().end, target);
        QCOMPARE(moves.last().exit, 0);
    }
    void liveTrackingLatency() {
        QFETCH(bool, curved);
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QVERIFY(control.beginHold());
        const auto origin = robot.position;
        QVector3D last;
        QElapsedTimer clock;
        clock.start();
        double lag = 0;
        int samples = 0;
        while (clock.elapsed() < 1500) {
            const double seconds = clock.elapsed() / 1000.0;
            const QVector3D target(float((curved ? 45 : 80) * seconds),
                                   curved ? float(6 * std::sin(4 * seconds)) : 0, 0);
            const auto delta = target - last;
            control.addInput(delta.x(), delta.y(), 0);
            last = target;
            if (seconds > 0.3) {
                lag += (origin + target - robot.position).length();
                ++samples;
            }
            QTest::qWait(10);
        }
        qInfo() << "Live tracking mean acknowledged-endpoint lag (mm):" << lag / samples
                << "commands:" << robot.commands.size();
        QVERIFY2(lag / samples < (curved ? 13.0 : 30.0), "Live following lag regressed toward the fixed-2-mm baseline");
        // Prediction can leave a residue smaller than the controller's minimum
        // move. Require the documented correction resolution, not 0.02 mm that
        // the firmware cannot represent. Exact fixed-path tests remain separate.
        const auto finalError = [&]() { return (robot.position - origin - last).length(); };
        QTRY_VERIFY2_WITH_TIMEOUT(finalError() < Limits{}.minimumLength,
            qPrintable(QString("Final tracking error: %1 mm; ready: %2")
                .arg(finalError()).arg(control.ready())), 6000);
        QTRY_COMPARE_WITH_TIMEOUT(broker.pendingCommandCount("robot1"), 0, 2000);
        QTest::qWait(150); // The prediction window is 80 ms.
        const auto settled = robot.position;
        const auto commandCount = robot.commands.size();
        QTest::qWait(150);
        QCOMPARE(robot.position, settled);
        QCOMPARE(robot.commands.size(), commandCount);
        QVERIFY(finalError() < Limits{}.minimumLength);
        QVERIFY(control.ready());
        QVERIFY(robot.finite);
        QVERIFY(robot.maxDepth <= 2);
        control.endHold();
    }
    void plannerContinuousStraightPath() {
        Limits limits;
        QString error;
        const auto moves = plan({{0, 0, -300}, {}, 0}, {{20, 0, -300}, {60, 0, -300}}, limits, &error);
        QVERIFY2(error.isEmpty(), qPrintable(error));
        QVERIFY(moves.size() > 2);
        QCOMPARE(moves.first().entry, 0);
        QCOMPARE(moves.last().exit, 0);
        double seconds = 0, stoppedSeconds = 0;
        for (int i = 0; i < moves.size(); ++i) {
            const auto& move = moves[i];
            if (i) {
                QCOMPARE(move.entry, moves[i - 1].exit);
                QVERIFY(move.entry > 0);
            }
            QVERIFY(move.entry <= move.feed - 2 && move.exit <= move.feed - 2);
            QVERIFY(transitionDistance(move.entry, move.exit, limits) <= (move.end - move.start).length() + 0.001);
            QVERIFY(std::isfinite(move.seconds));
            QVERIFY(move.gcode().size() <= 79);
            seconds += move.seconds;
            stoppedSeconds += duration((move.end - move.start).length(), 0, 0, limits);
        }
        QCOMPARE(moves.last().end, QVector3D(60, 0, -300));
        QVERIFY(seconds < stoppedSeconds * 0.6);
    }
    void plannerCornersAndInvalidPaths() {
        Limits limits;
        QString error;
        auto moves = plan({{}, {}, 0}, {{10, 0, 0}, {10, 10, 0}, {10, 0, 0}}, limits, &error);
        QVERIFY2(error.isEmpty(), qPrintable(error));
        for (const auto& move : moves)
            if (move.end == QVector3D(10, 0, 0) || move.end == QVector3D(10, 10, 0)) QCOMPARE(move.exit, 0);
        moves = plan({{}, {}, 0}, {{10, 0, 0}, {20, 1, 0}}, limits, &error);
        QVERIFY(error.isEmpty());
        bool smoothJunction = false;
        for (const auto& move : moves)
            if (move.end == QVector3D(10, 0, 0)) smoothJunction = move.exit > 0;
        QVERIFY(smoothJunction);
        QVERIFY(plan({{}, {}, 0}, {{0.1f, 0, 0}, {0.1f, 1, 0}}, limits, &error).isEmpty());
        QVERIFY(!error.isEmpty());
        limits.jerk = 0;
        QVERIFY(plan({{}, {}, 0}, {{10, 0, 0}}, limits, &error).isEmpty());
        limits.jerk = 15000;
        QVERIFY(plan({{}, {}, 0}, {{std::numeric_limits<float>::infinity(), 0, 0}}, limits, &error).isEmpty());
        QVERIFY(plan({{}, {1, 0, 0}, 40}, {{-10, 0, 0}}, limits, &error).isEmpty());
        const auto stopping = brake({{}, {1, 0, 0}, 40}, limits);
        QCOMPARE(stopping.exit, 0);
        QVERIFY(stopping.end.x() >= transitionDistance(40, 0, limits));
        QVERIFY(std::isfinite(stopping.seconds));
    }
    void brokerFifoAndTelemetry() {
        DeviceCommandBroker broker;
        QVERIFY(broker.acquireManualControl("stream", "robot1"));
        QSignalSpy sent(&broker, &DeviceCommandBroker::DispatchCommand);
        QSignalSpy replies(&broker, &DeviceCommandBroker::ResponseForOwner);
        const auto a = broker.SubmitMotion("stream", "robot1", "G01 X1 S0 E10");
        const auto b = broker.SubmitMotion("stream", "robot1", "G01 X2 S10 E0");
        QVERIFY(a && b);
        QCOMPARE(sent.size(), 2);
        QVERIFY(!broker.SubmitMotion("stream", "robot1", "G01 X3"));
        broker.HandleDeviceResponse("robot1", "I0 V1");
        QCOMPARE(replies.size(), 0);
        QCOMPARE(broker.pendingCommandCount("robot1"), 2);
        broker.HandleDeviceResponse("robot1", "Ok");
        QCOMPARE(replies[0][3].toULongLong(), a);
        broker.releaseManualControl("stream", "robot1");
        QVERIFY(!broker.Submit("plugin", "robot1", "G28", DeviceCommandBroker::Origin::Plugin));
        broker.HandleDeviceResponse("robot1", "Ok");
        QCOMPARE(replies[1][3].toULongLong(), b);
        QVERIFY(broker.acquireManualControl("other", "robot1"));
    }
    void brokerFaultQuarantinesLateReplies_data() {
        QTest::addColumn<QString>("kind");
        QTest::newRow("error") << QString("error");
        QTest::newRow("timeout") << QString("timeout");
        QTest::newRow("disconnect") << QString("disconnect");
        QTest::newRow("safety") << QString("safety");
    }
    void brokerFaultQuarantinesLateReplies() {
        QFETCH(QString, kind);
        DeviceCommandBroker broker;
        QSignalSpy replies(&broker, &DeviceCommandBroker::ResponseForOwner);
        QVERIFY(broker.acquireManualControl("stream", "robot1"));
        QVERIFY(broker.SubmitMotion("stream", "robot1", "G01 X1", kind == "timeout" ? 20 : 3000));
        QVERIFY(broker.SubmitMotion("stream", "robot1", "G01 X2"));
        if (kind == "error") broker.HandleDeviceResponse("robot1", "Unknown:Position");
        if (kind == "disconnect") broker.HandleDeviceUnavailable("robot1", "Disconnected");
        if (kind == "safety") broker.Submit("safety", "robot1", "M84", DeviceCommandBroker::Origin::Safety, false);
        QTRY_COMPARE_WITH_TIMEOUT(replies.size(), 2, 500);
        broker.releaseManualControl("stream", "robot1");
        QVERIFY(!broker.acquireManualControl("new", "robot1"));
        QVERIFY(!broker.Submit("new", "robot1", "Position", DeviceCommandBroker::Origin::Manual));
        broker.HandleDeviceResponse("robot1", "Ok");
        QCOMPARE(replies.size(), 2);
    }
    void startupAndLease() {
        DeviceCommandBroker broker;
        QSignalSpy sent(&broker, &DeviceCommandBroker::DispatchCommand);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QCOMPARE(sent.count(), 3);
        QCOMPARE(sent[0][1].toString(), QString("jogging (0, 0, 0)"));
        QCOMPARE(sent[1][1].toString(), QString("G90"));
        QCOMPARE(sent[2][1].toString(), QString("PositionOffset"));
        QVERIFY(!broker.Submit("script", "robot1", "G28", DeviceCommandBroker::Origin::GScript));
        control.addInput(10, 10, 10);
        QTest::qWait(40);
        QCOMPARE(sent.count(), 3);
    }
    void mouseDisplacement_data() {
        QTest::addColumn<int>("events");
        QTest::newRow("one-fast-event") << 1;
        QTest::newRow("many-small-events") << 100;
    }
    void mouseDisplacement() {
        QFETCH(int, events);
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QVERIFY(control.beginHold());
        for (int i = 0; i < events; ++i) control.addInput(15.0f / events, -6.0f / events, 3.0f / events);
        QTRY_VERIFY_WITH_TIMEOUT((robot.position - QVector3D(25, 14, -297)).length() < 0.01f, 5000);
        QVERIFY(robot.maxDepth == 2);
        QVERIFY(robot.finite);
        bool sawNonzeroJoin = false;
        for (int i = 1; i < robot.commands.size(); ++i)
            sawNonzeroJoin |= value(robot.commands[i], 'S') > 0 &&
                             value(robot.commands[i], 'S') == value(robot.commands[i - 1], 'E');
        QVERIFY(sawNonzeroJoin);
        QCOMPARE(value(robot.commands.last(), 'E'), 0.0);
        control.endHold();
    }
    void subThresholdAccumulates() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QVERIFY(control.beginHold());
        control.addInput(0.1f, 0, 0);
        QTest::qWait(50);
        QVERIFY(robot.commands.isEmpty());
        control.addInput(0.2f, 0, 0);
        QTRY_VERIFY((robot.position - QVector3D(10.3f, 20, -300)).length() < 0.001f);
    }
    void stoppedInputSettlesWithoutReleasing() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QVERIFY(control.beginHold());
        for (int i = 0; i < 40; ++i) {
            control.addInput(0.2f, 0, 0);
            QTest::qWait(10);
        }
        QTRY_VERIFY_WITH_TIMEOUT((robot.position - QVector3D(18, 20, -300)).length() < 0.201f, 3000);
        QTRY_COMPARE_WITH_TIMEOUT(broker.pendingCommandCount("robot1"), 0, 2000);
        QTest::qWait(150);
        const auto sent = robot.commands.size();
        const auto settled = robot.position;
        QTest::qWait(150);
        QCOMPARE(robot.commands.size(), sent);
        QCOMPARE(robot.position, settled);
        QVERIFY(control.ready());
        control.endHold();
    }
    void releaseCancelsPrediction() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QVERIFY(control.beginHold());
        for (int i = 0; i < 10; ++i) {
            control.addInput(1, 0, 0);
            QTest::qWait(10);
        }
        QVERIFY(!robot.commands.isEmpty());
        const auto committed = robot.commands.size();
        control.endHold();
        QTRY_COMPARE_WITH_TIMEOUT(broker.pendingCommandCount("robot1"), 0, 2000);
        QTest::qWait(150);
        QVERIFY(robot.commands.size() <= committed + 1);
        QCOMPARE(value(robot.commands.last(), 'E'), 0.0);
        const auto stopped = robot.position;
        QTest::qWait(100);
        QCOMPARE(robot.position, stopped);
        QVERIFY(robot.finite);
    }
    void reversalAndReleaseBrake() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QVERIFY(control.beginHold());
        control.addInput(30, 0, 0);
        QTRY_VERIFY(robot.commands.size() >= 2);
        control.addInput(-40, 0, 0);
        QTRY_VERIFY2_WITH_TIMEOUT((robot.position - QVector3D(0, 20, -300)).length() < 0.01f,
            qPrintable(QString("x=%1; ready=%2; %3").arg(robot.position.x()).arg(control.ready()).arg(robot.commands.mid(qMax(0, robot.commands.size() - 6)).join("; "))), 6000);
        const auto before = robot.commands.size();
        control.addInput(100, 0, 0);
        QTRY_VERIFY(robot.commands.size() >= before + 2);
        const auto committed = robot.commands.size();
        control.endHold();
        QTRY_COMPARE_WITH_TIMEOUT(broker.pendingCommandCount("robot1"), 0, 2000);
        QTest::qWait(40);
        QVERIFY(robot.commands.size() <= committed + 1);
        QCOMPARE(value(robot.commands.last(), 'E'), 0.0);
        QVERIFY(robot.position.x() < 15);
        QVERIFY(robot.finite);
        QVERIFY(control.beginHold());
    }
    void fixedPathRetainsCorners() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        QVERIFY(broker.acquireManualControl("path", "robot1"));
        auto* stream = new GcodeMotionStream(&broker, "path", "robot1", robot.position);
        QString error;
        QVERIFY2(stream->setPath({{15, 20, -300}, {15, 25, -300}, {10, 25, -300}}, &error), qPrintable(error));
        QTRY_VERIFY_WITH_TIMEOUT((robot.position - QVector3D(10, 25, -300)).length() < 0.01f, 5000);
        bool cornerA = false, cornerB = false;
        for (const auto& command : robot.commands) {
            cornerA |= endpoint(command) == QVector3D(15, 20, -300) && value(command, 'E') == 0;
            cornerB |= endpoint(command) == QVector3D(15, 25, -300) && value(command, 'E') == 0;
        }
        QVERIFY(cornerA && cornerB);
        stream->close();
    }
    void delayedAcknowledgementsDrainBeforeRestarting() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        robot.ackDelayMs = 200;
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        QVERIFY(control.beginHold());
        control.addInput(8, 0, 0);
        QTRY_VERIFY_WITH_TIMEOUT((robot.position - QVector3D(18, 20, -300)).length() < 0.01f, 6000);
        QVERIFY(robot.restartedFromRest);
        QVERIFY(robot.maxDepth <= 2);
        control.endHold();
    }
    void lowFeedFitsLiveBudget() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        control.setSpeed(10);
        QSignalSpy metrics(&control, &MouseJogController::streamMetricsChanged);
        QVERIFY(control.beginHold());
        control.addInput(3, 0, 0);
        QTRY_VERIFY_WITH_TIMEOUT((robot.position - QVector3D(13, 20, -300)).length() < 0.01f, 4000);
        for (const auto& row : metrics) {
            QVERIFY(row[0].toInt() <= 2);
            QVERIFY(row[1].toDouble() <= 0.255);
        }
        QVERIFY(robot.finite);
    }
    void closeKeepsBrakingTailAndOwnership() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        auto* control = new MouseJogController(&broker, "robot1");
        initialize(broker, *control);
        QVERIFY(control->beginHold());
        control->addInput(30, 0, 0);
        QTRY_VERIFY(robot.commands.size() >= 2);
        delete control;
        QVERIFY(!broker.acquireManualControl("other", "robot1"));
        QTRY_COMPARE_WITH_TIMEOUT(broker.pendingCommandCount("robot1"), 0, 2000);
        QTRY_VERIFY(broker.findChildren<GcodeMotionStream*>().isEmpty());
        QVERIFY(broker.acquireManualControl("other", "robot1"));
        QCOMPARE(value(robot.commands.last(), 'E'), 0.0);
    }
    void invalidPositionAndMissingReply() {
        DeviceCommandBroker broker;
        MouseJogController control(&broker, "robot1");
        QVERIFY(control.start());
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "nan,0,0");
        QVERIFY(!control.ready());
        initialize(broker, control);
        QVERIFY(control.beginHold());
        control.addInput(20, 0, 0);
        QTRY_VERIFY(broker.hasActiveCommand("robot1"));
        QTRY_VERIFY_WITH_TIMEOUT(!control.ready(), 4000);
        QVERIFY(!control.start());
    }
    void cellStateAndSafetyPreempt() {
        DeviceCommandBroker broker;
        MouseJogController control(&broker, "robot1");
        initialize(broker, control);
        broker.SetCellState("AutoRunning");
        QTRY_VERIFY(!control.ready());
        broker.SetCellState("Ready");
        initialize(broker, control);
        QVERIFY(broker.Submit("safety", "robot1", "M112", DeviceCommandBroker::Origin::Safety, false));
        QVERIFY(!control.ready());
    }
    void dialogMouseWheelFocusAndEsc() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        MouseJogDialog dialog(&broker, "robot1");
        dialog.show();
        QTRY_VERIFY(broker.hasActiveCommand("robot1"));
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "10,20,-300");
        auto* pad = dialog.findChild<QLabel*>("mouseJogPad");
        QVERIFY(pad);
        QTest::mousePress(pad, Qt::LeftButton, Qt::NoModifier, QPoint(60, 80));
        QMouseEvent move(QEvent::MouseMove, QPointF(70, 60), QPointF(70, 60), Qt::NoButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(pad, &move);
        // Native Windows capture can deliver wheel with NoButton even though
        // the left-button hold is still active.
        QWheelEvent wheel(QPointF(70, 60), QPointF(70, 60), QPoint(), QPoint(0, 120), Qt::NoButton,
                          Qt::NoModifier, Qt::NoScrollPhase, false);
        QApplication::sendEvent(pad, &wheel);
        QTRY_VERIFY(!robot.commands.isEmpty());
        QVERIFY(value(robot.commands.first(), 'X') > 10);
        QVERIFY(value(robot.commands.first(), 'Y') > 20);
        QVERIFY(value(robot.commands.first(), 'Z') > -300);
        QEvent deactivate(QEvent::WindowDeactivate);
        QApplication::sendEvent(&dialog, &deactivate);
        QTRY_COMPARE_WITH_TIMEOUT(broker.pendingCommandCount("robot1"), 0, 2000);
        QTest::keyClick(&dialog, Qt::Key_Escape);
        QVERIFY(!dialog.isVisible());
        QTRY_VERIFY(broker.findChildren<GcodeMotionStream*>().isEmpty());
        QVERIFY(broker.acquireManualControl("other", "robot1"));
    }
    void immediateCloseDoesNotAcquireRobot() {
        DeviceCommandBroker broker;
        QSignalSpy sent(&broker, &DeviceCommandBroker::DispatchCommand);
        MouseJogDialog dialog(&broker, "robot1");
        dialog.show();
        dialog.reject();
        QTest::qWait(20);
        QCOMPARE(sent.count(), 0);
    }
    void continuousCaptureExceedsPadAndPlanningHorizon() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        auto* capture = new FakeMouseCapture;
        MouseJogDialog dialog(&broker, "robot1", nullptr, capture);
        dialog.show();
        QTRY_VERIFY(broker.hasActiveCommand("robot1"));
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "10,20,-300");
        auto* pad = dialog.findChild<QLabel*>("mouseJogPad");
        QVERIFY(dialog.findChild<QCheckBox*>("mouseJogContinuous")->isChecked());
        QVERIFY(dialog.findChild<QDoubleSpinBox*>("mouseJogSensitivity")->suffix().contains("count"));
        QTest::mousePress(pad, Qt::LeftButton, Qt::NoModifier, QPoint(60, 80));
        QVERIFY(capture->active());
        QEvent leave(QEvent::Leave);
        QApplication::sendEvent(pad, &leave);
        QVERIFY(capture->active());
        QMouseEvent legacy(QEvent::MouseMove, QPointF(999, 999), QPointF(999, 999),
                           Qt::NoButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(pad, &legacy);
        // Four long strokes, without releasing or returning the cursor to the pad.
        for (int i = 0; i < 4; ++i) capture->move(QPoint(200, 0));
        QTRY_VERIFY2_WITH_TIMEOUT((robot.position - QVector3D(130, 20, -300)).length() < 0.01f,
            qPrintable(QString("x=%1; %2; %3").arg(robot.position.x()).arg(dialog.findChild<QLabel*>("mouseJogStatus")->text()).arg(robot.commands.mid(qMax(0, robot.commands.size() - 6)).join("; "))), 8000);
        QVERIFY(capture->active());
        QVERIFY(robot.finite);
        QVERIFY(robot.maxDepth <= 2);
        QTest::mouseRelease(pad, Qt::LeftButton, Qt::NoModifier, QPoint(60, 80));
        QVERIFY(!capture->active());
        const auto sent = robot.commands.size();
        capture->move(QPoint(200, 0));
        QTest::qWait(50);
        QCOMPARE(robot.commands.size(), sent);
        dialog.reject();
    }
    void continuousCaptureStopsOnDeactivateAndEsc() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        auto* capture = new FakeMouseCapture;
        MouseJogDialog dialog(&broker, "robot1", nullptr, capture);
        dialog.show();
        QTRY_VERIFY(broker.hasActiveCommand("robot1"));
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "10,20,-300");
        auto* pad = dialog.findChild<QLabel*>("mouseJogPad");
        QTest::mousePress(pad, Qt::LeftButton, Qt::NoModifier, QPoint(60, 80));
        QVERIFY(capture->active());
        QEvent deactivate(QEvent::WindowDeactivate);
        QApplication::sendEvent(&dialog, &deactivate);
        QVERIFY(!capture->active());
        capture->move(QPoint(100, 0));
        QTest::qWait(40);
        QVERIFY(robot.commands.isEmpty());
        QTest::mouseRelease(pad, Qt::LeftButton);
        QTest::mousePress(pad, Qt::LeftButton, Qt::NoModifier, QPoint(60, 80));
        QVERIFY(capture->active());
        QTest::keyClick(&dialog, Qt::Key_Escape);
        QVERIFY(!capture->active());
        QVERIFY(!dialog.isVisible());
    }
    void continuousCaptureFailureDoesNotMoveRobot() {
        DeviceCommandBroker broker;
        RobotEmulator robot(broker);
        auto* capture = new FakeMouseCapture;
        capture->canStart = false;
        MouseJogDialog dialog(&broker, "robot1", nullptr, capture);
        dialog.show();
        QTRY_VERIFY(broker.hasActiveCommand("robot1"));
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "Ok");
        broker.HandleDeviceResponse("robot1", "10,20,-300");
        auto* pad = dialog.findChild<QLabel*>("mouseJogPad");
        QTest::mousePress(pad, Qt::LeftButton, Qt::NoModifier, QPoint(60, 80));
        capture->move(QPoint(100, 0));
        QTest::qWait(40);
        QVERIFY(!capture->active());
        QVERIFY(robot.commands.isEmpty());
        QVERIFY(dialog.findChild<QLabel*>("mouseJogStatus")->text().contains("Could not capture"));
        dialog.reject();
    }
};
QTEST_MAIN(MouseJogTest)
#include "tst_mouse_jog.moc"
