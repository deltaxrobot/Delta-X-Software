#include <QtTest>

#include "CellSupervisor.h"
#include "DeviceCommandBroker.h"

class ControlPlaneTest : public QObject
{
    Q_OBJECT

private slots:
    void commandsAreSerializedAndResponsesReachOnlyTheirOwner();
    void manualMotionIsBlockedInAutoAndStopPreempts();
    void controlledStopCoversKnownActuators();
    void timeoutCancelsTheDeviceQueue();
    void cellFaultStopsOnceAndRequiresExplicitReset();
    void synchronousProviderResponseCompletesActiveRequest();
    void unavailableDeviceRejectsImmediatelyWithoutTimeout();
    void robotHomeWaitsForPositionBeforeCompleting();
    void robotHomeErrorCompletesImmediately_data();
    void robotHomeErrorCompletesImmediately();
};

void ControlPlaneTest::synchronousProviderResponseCompletesActiveRequest()
{
    DeviceCommandBroker broker;
    QSignalSpy responses(&broker, &DeviceCommandBroker::ResponseForOwner);
    connect(&broker, &DeviceCommandBroker::CommandDispatched, &broker,
            [&broker](quint64, const QString&, const QString& device,
                      const QString&, DeviceCommandBroker::Origin) {
        broker.HandleDeviceResponse(device, QStringLiteral("plugin-ok"));
    });

    const quint64 requestId = broker.Submit(
        QStringLiteral("plugin/example"), QStringLiteral("example.device0"),
        QStringLiteral("PING"), DeviceCommandBroker::Origin::Plugin, true, 1000);

    QVERIFY(requestId > 0);
    QCOMPARE(responses.size(), 1);
    QCOMPARE(responses.first().at(0).toString(),
             QStringLiteral("plugin/example"));
    QCOMPARE(responses.first().at(2).toString(), QStringLiteral("plugin-ok"));
    QVERIFY(!broker.hasActiveCommand(QStringLiteral("example.device0")));
}

void ControlPlaneTest::unavailableDeviceRejectsImmediatelyWithoutTimeout()
{
    DeviceCommandBroker broker;
    QSignalSpy rejected(&broker, &DeviceCommandBroker::CommandRejected);
    QSignalSpy responses(&broker, &DeviceCommandBroker::ResponseForOwner);
    QSignalSpy timedOut(&broker, &DeviceCommandBroker::CommandTimedOut);

    const quint64 requestId = broker.Submit(
        QStringLiteral("manual/ui"), QStringLiteral("robot0"),
        QStringLiteral("G28"), DeviceCommandBroker::Origin::Manual, true, 20);
    QVERIFY(requestId > 0);
    QVERIFY(broker.hasActiveCommand(QStringLiteral("robot0")));

    broker.HandleDeviceUnavailable(QStringLiteral("robot0"),
                                   QStringLiteral("Robot is not connected"));

    QCOMPARE(rejected.size(), 1);
    QCOMPARE(responses.size(), 1);
    QCOMPARE(timedOut.size(), 0);
    QVERIFY(!broker.hasActiveCommand(QStringLiteral("robot0")));
    QVERIFY(responses.first().at(2).toString().contains(
        QStringLiteral("not connected")));
    QTest::qWait(80);
    QCOMPARE(timedOut.size(), 0);
}

void ControlPlaneTest::robotHomeWaitsForPositionBeforeCompleting()
{
    DeviceCommandBroker broker;
    QSignalSpy dispatched(&broker, &DeviceCommandBroker::CommandDispatched);
    QSignalSpy responses(&broker, &DeviceCommandBroker::ResponseForOwner);
    QSignalSpy unsolicited(&broker, &DeviceCommandBroker::UnsolicitedResponse);

    const quint64 homeRequest = broker.Submit(
        QStringLiteral("gscript/thread0"), QStringLiteral("robot0"),
        QStringLiteral("G28"), DeviceCommandBroker::Origin::GScript, true, 1000);
    const quint64 moveRequest = broker.Submit(
        QStringLiteral("gscript/thread0"), QStringLiteral("robot0"),
        QStringLiteral("G01 X10"), DeviceCommandBroker::Origin::GScript, true, 1000);

    QVERIFY(homeRequest > 0);
    QVERIFY(moveRequest > homeRequest);
    QCOMPARE(dispatched.size(), 1);

    broker.HandleDeviceResponse(QStringLiteral("robot0"), QStringLiteral("Ok"));

    QVERIFY(broker.hasActiveCommand(QStringLiteral("robot0")));
    QCOMPARE(responses.size(), 0);
    QCOMPARE(dispatched.size(), 1);

    const QString position = QStringLiteral("0.0,0.0,-291.28,90.0,0.0,0.0");
    broker.HandleDeviceResponse(QStringLiteral("robot0"), position);

    QCOMPARE(responses.size(), 1);
    QCOMPARE(responses.first().at(0).toString(), QStringLiteral("gscript/thread0"));
    QCOMPARE(responses.first().at(2).toString(), position);
    QCOMPARE(responses.first().at(3).toULongLong(), homeRequest);
    QCOMPARE(unsolicited.size(), 0);
    QCOMPARE(dispatched.size(), 2);
    QCOMPARE(dispatched.at(1).at(3).toString(), QStringLiteral("G01 X10"));
}

void ControlPlaneTest::robotHomeErrorCompletesImmediately_data()
{
    QTest::addColumn<QString>("response");
    QTest::newRow("generic-error") << QStringLiteral("Error: homing switch not reached");
    QTest::newRow("firmware-unknown") << QStringLiteral("Unknown:Power lose!");
    QTest::newRow("emergency-stop") << QStringLiteral("Delta:EStop Pressing!");
    QTest::newRow("stop") << QStringLiteral("Delta:Stop");
}

void ControlPlaneTest::robotHomeErrorCompletesImmediately()
{
    QFETCH(QString, response);
    DeviceCommandBroker broker;
    QSignalSpy responses(&broker, &DeviceCommandBroker::ResponseForOwner);

    const quint64 requestId = broker.Submit(
        QStringLiteral("gscript/thread0"), QStringLiteral("robot0"),
        QStringLiteral("G28"), DeviceCommandBroker::Origin::GScript, true, 1000);
    QVERIFY(requestId > 0);

    broker.HandleDeviceResponse(QStringLiteral("robot0"), response);

    QCOMPARE(responses.size(), 1);
    QCOMPARE(responses.first().at(2).toString(), response);
    QCOMPARE(responses.first().at(3).toULongLong(), requestId);
    QVERIFY(!broker.hasActiveCommand(QStringLiteral("robot0")));
}

void ControlPlaneTest::commandsAreSerializedAndResponsesReachOnlyTheirOwner()
{
    DeviceCommandBroker broker;
    broker.SetCellState(QStringLiteral("AutoRunning"));
    QSignalSpy dispatched(&broker, &DeviceCommandBroker::CommandDispatched);
    QSignalSpy responses(&broker, &DeviceCommandBroker::ResponseForOwner);

    const quint64 first = broker.Submit(
        QStringLiteral("gscript/thread0"), QStringLiteral("robot0"),
        QStringLiteral("G01 X10"), DeviceCommandBroker::Origin::GScript, true, 1000);
    const quint64 second = broker.Submit(
        QStringLiteral("gscript/thread1"), QStringLiteral("robot0"),
        QStringLiteral("G01 X20"), DeviceCommandBroker::Origin::GScript, true, 1000);

    QVERIFY(first > 0);
    QVERIFY(second > first);
    QCOMPARE(dispatched.size(), 1);
    QCOMPARE(dispatched.at(0).at(1).toString(), QStringLiteral("gscript/thread0"));
    QCOMPARE(broker.pendingCommandCount(QStringLiteral("robot0")), 2);

    broker.HandleDeviceResponse(QStringLiteral("robot0"), QStringLiteral("Ok"));
    QCOMPARE(responses.size(), 1);
    QCOMPARE(responses.at(0).at(0).toString(), QStringLiteral("gscript/thread0"));
    QCOMPARE(dispatched.size(), 2);
    QCOMPARE(dispatched.at(1).at(1).toString(), QStringLiteral("gscript/thread1"));

    broker.HandleDeviceResponse(QStringLiteral("robot0"), QStringLiteral("Ok"));
    QCOMPARE(responses.size(), 2);
    QCOMPARE(responses.at(1).at(0).toString(), QStringLiteral("gscript/thread1"));
    QCOMPARE(broker.pendingCommandCount(QStringLiteral("robot0")), 0);
}

void ControlPlaneTest::manualMotionIsBlockedInAutoAndStopPreempts()
{
    DeviceCommandBroker broker;
    broker.SetCellState(QStringLiteral("AutoRunning"));
    QSignalSpy dispatched(&broker, &DeviceCommandBroker::CommandDispatched);
    QSignalSpy rejected(&broker, &DeviceCommandBroker::CommandRejected);
    QSignalSpy responses(&broker, &DeviceCommandBroker::ResponseForOwner);

    QCOMPARE(broker.Submit(QStringLiteral("manual/ui"), QStringLiteral("robot0"),
                           QStringLiteral("G01 X100"),
                           DeviceCommandBroker::Origin::Manual, false, 1000),
             quint64(0));
    QCOMPARE(rejected.size(), 1);
    QCOMPARE(dispatched.size(), 0);

    QVERIFY(broker.Submit(QStringLiteral("gscript/thread0"), QStringLiteral("robot0"),
                          QStringLiteral("G01 X10"),
                          DeviceCommandBroker::Origin::GScript, true, 1000) > 0);
    QCOMPARE(dispatched.size(), 1);
    QVERIFY(broker.hasActiveCommand(QStringLiteral("robot0")));

    QVERIFY(broker.Submit(QStringLiteral("manual/ui"), QStringLiteral("robot0"),
                          QStringLiteral("M84"),
                          DeviceCommandBroker::Origin::Manual, false, 1000) > 0);
    QCOMPARE(dispatched.size(), 2);
    QCOMPARE(dispatched.at(1).at(3).toString(), QStringLiteral("M84"));
    QCOMPARE(responses.size(), 1);
    QCOMPARE(responses.at(0).at(0).toString(), QStringLiteral("gscript/thread0"));
    QVERIFY(responses.at(0).at(2).toString().contains(QStringLiteral("preempted")));
    QVERIFY(!broker.hasActiveCommand(QStringLiteral("robot0")));
}

void ControlPlaneTest::controlledStopCoversKnownActuators()
{
    DeviceCommandBroker broker;
    broker.RegisterDevice(QStringLiteral("robot0"));
    broker.RegisterDevice(QStringLiteral("conveyor0"));
    broker.RegisterDevice(QStringLiteral("slider0"));
    broker.RegisterDevice(QStringLiteral("encoder0"));
    QSignalSpy dispatched(&broker, &DeviceCommandBroker::DispatchCommand);

    broker.RequestControlledStop(QStringLiteral("test fault"));

    QStringList commands;
    for (const QList<QVariant>& row : dispatched)
        commands.append(row.at(0).toString() + QStringLiteral(":") + row.at(1).toString());
    QVERIFY(commands.contains(QStringLiteral("robot0:M05")));
    QVERIFY(commands.contains(QStringLiteral("robot0:M84")));
    QVERIFY(commands.contains(QStringLiteral("conveyor0:M311 0")));
    QVERIFY(commands.contains(QStringLiteral("slider0:M323")));
    QVERIFY(std::none_of(commands.cbegin(), commands.cend(), [](const QString& command) {
        return command.startsWith(QStringLiteral("encoder0:"));
    }));
}

void ControlPlaneTest::timeoutCancelsTheDeviceQueue()
{
    DeviceCommandBroker broker;
    broker.SetCellState(QStringLiteral("AutoRunning"));
    QSignalSpy dispatched(&broker, &DeviceCommandBroker::CommandDispatched);
    QSignalSpy timedOut(&broker, &DeviceCommandBroker::CommandTimedOut);
    QSignalSpy rejected(&broker, &DeviceCommandBroker::CommandRejected);

    broker.Submit(QStringLiteral("tracking/0"), QStringLiteral("encoder0"),
                  QStringLiteral("M317"), DeviceCommandBroker::Origin::Tracking,
                  true, 20);
    broker.Submit(QStringLiteral("tracking/1"), QStringLiteral("encoder0"),
                  QStringLiteral("M317"), DeviceCommandBroker::Origin::Tracking,
                  true, 1000);

    QCOMPARE(dispatched.size(), 1);
    QTRY_COMPARE_WITH_TIMEOUT(timedOut.size(), 1, 500);
    QCOMPARE(dispatched.size(), 1);
    QCOMPARE(rejected.size(), 1);
    QCOMPARE(rejected.at(0).at(0).toString(), QStringLiteral("tracking/1"));
    QCOMPARE(broker.pendingCommandCount(QStringLiteral("encoder0")), 0);
}

void ControlPlaneTest::cellFaultStopsOnceAndRequiresExplicitReset()
{
    CellSupervisor supervisor;
    QSignalSpy stops(&supervisor, &CellSupervisor::ControlledStopRequested);

    QVERIFY(supervisor.BeginAutomation(QStringLiteral("gscript/thread0")));
    QVERIFY(supervisor.BeginAutomation(QStringLiteral("gscript/thread1")));
    QCOMPARE(supervisor.state(), CellSupervisor::State::AutoRunning);
    QCOMPARE(supervisor.activeOwners().size(), 2);

    supervisor.EndAutomation(QStringLiteral("gscript/thread0"));
    QCOMPARE(supervisor.state(), CellSupervisor::State::AutoRunning);

    supervisor.ReportFault(QStringLiteral("robot timeout"));
    QCOMPARE(supervisor.state(), CellSupervisor::State::Faulted);
    QCOMPARE(stops.size(), 1);
    QVERIFY(!supervisor.BeginAutomation(QStringLiteral("gscript/thread2")));
    supervisor.ReportFault(QStringLiteral("same fault"));
    QCOMPARE(stops.size(), 1);

    supervisor.ResetFault();
    QCOMPARE(supervisor.state(), CellSupervisor::State::Faulted);
    supervisor.EndAutomation(QStringLiteral("gscript/thread1"));
    supervisor.ResetFault();
    QTRY_COMPARE(supervisor.state(), CellSupervisor::State::Ready);
    QVERIFY(supervisor.automationAllowed());
}

QTEST_MAIN(ControlPlaneTest)
#include "tst_control_plane.moc"
