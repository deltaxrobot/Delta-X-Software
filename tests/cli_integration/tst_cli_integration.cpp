#include <QtTest>
#include <QTemporaryDir>
#include <QLocalSocket>
#include <QUuid>
#include <QScopeGuard>
#include <stdexcept>
#include "RobotWindow.h"
#include "ProjectManager.h"
#include "GScriptCliBridge.h"
#include "CliProtocol.h"
#include "ui_RobotWindow.h"
#include "PluginExtensionRegistry.h"
#include "DeltaXGScriptProvider.h"
#include "VariableManager.h"
#include "DeviceCommandBroker.h"

class FailingCliPrimitive final : public QObject, public DeltaXGScriptProvider
{
public:
    QVariantList gscriptPrimitives() const override
    {
        return {QVariantMap{{"name", "clitestfailure"}, {"signature", "M98 PcliTestFailure()"},
                             {"description", "Integration failure fixture"},
                             {"minArgs", 0}, {"maxArgs", 0}}};
    }
    bool executeGScriptPrimitive(const QString&, const QVariantList&, QVariant*, QString* error) override
    {
        calledOnOwnerThread = QThread::currentThread() == thread();
        if (throwException) throw std::runtime_error("integration provider exception");
        if (error) *error = "integration provider rejection";
        return false;
    }
    bool throwException = false;
    bool calledOnOwnerThread = false;
};

class CliIntegrationTest : public QObject
{
    Q_OBJECT
private slots:
    void realEditorRuntimeAndCli()
    {
        QTemporaryDir settings;
        QVERIFY(settings.isValid());
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settings.path());
        QCoreApplication::setOrganizationName("DeltaXCliTest");
        QCoreApplication::setApplicationName("cli-integration");
        const auto originalDirectory = QDir::currentPath();
        QVERIFY(QDir::setCurrent(settings.path()));
        // MainWindow normally supplies the shared software log widget.
        QTextEdit log;
        teSoftwareLog = &log;
        const auto restoreGlobals = qScopeGuard([&]() {
            teSoftwareLog = nullptr;
            QDir::setCurrent(originalDirectory);
        });
        ProjectManager projects;
        RobotWindow window(nullptr, "cli_test");
        // This fixture exercises local IPC, not the unrelated web-control
        // endpoints. Close them before processing incoming desktop traffic.
        auto* connections = window.ConnectionManager;
        QMetaObject::invokeMethod(connections, [connections] {
            if (connections->Server) connections->Server->close();
            if (connections->WebServer) connections->WebServer->close();
            if (connections->BlocklyServer) connections->BlocklyServer->close();
        }, Qt::BlockingQueuedConnection);
        projects.RobotWindows.append(&window);
        const QString endpoint = "deltax-test-" + QUuid::createUuid().toString(QUuid::WithoutBraces);
        GScriptCliBridge bridge(&projects, nullptr, endpoint);
        auto* worker = window.GcodeScripts.first();
        QVERIFY(worker->thread() != QThread::currentThread());
        QSignalSpy hardware(worker, &GcodeScript::SendGcodeToDevice);
        const auto readEvent = [](QLocalSocket& client) {
            QElapsedTimer wait;
            wait.start();
            while (!client.canReadLine() && wait.elapsed() < 5000) QTest::qWait(5);
            return QJsonDocument::fromJson(client.readLine()).object();
        };
        const auto request = [&](QLocalSocket& client, QJsonObject message) {
            client.connectToServer(endpoint);
            QVERIFY(client.waitForConnected(1000));
            message.insert("version", 1);
            client.write(CliProtocol::encode(message));
        };
        const auto runRequest = [](const QString& source) {
            return QJsonObject{{"command", "run"}, {"project", "cli_test"},
                               {"thread", 0}, {"source", source}};
        };
        QLocalSocket run;
        request(run, runRequest("#CliTest.Value = 6 * 7\nM98 Pdelay(50)\nM98 Passert(#CliTest.Value == 42, \"calculation failed\")"));
        QCOMPARE(readEvent(run).value("event").toString(), "accepted");
        QJsonObject result;
        do { result = readEvent(run); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY2(result.value("success").toBool(), qPrintable(QJsonDocument(result).toJson()));
        QCOMPARE(hardware.count(), 0);

        // A real worker thread must yield even when there are no device/timer
        // waits, and old queued continuations must not advance the next run.
        QLocalSocket cpuLoop;
        request(cpuLoop, runRequest("WHILE 1\n#CliTest.Loop = 1\nENDWHILE"));
        const auto cpuAccepted = readEvent(cpuLoop);
        QCOMPARE(cpuAccepted.value("event").toString(), "accepted");
        QTRY_VERIFY(worker->IsRunning());
        QLocalSocket cpuStop;
        request(cpuStop, {{"command", "stop"}, {"runId", cpuAccepted.value("runId")}});
        QCOMPARE(readEvent(cpuStop).value("event").toString(), "stop-requested");
        do { result = readEvent(cpuLoop); } while (!result.isEmpty() && result.value("event") != "finished");
        QCOMPARE(result.value("event").toString(), "finished");
        QVERIFY(!result.value("success").toBool());
        QTRY_VERIFY(!worker->IsRunning());
        QLocalSocket afterCpu;
        request(afterCpu, runRequest("M98 Pdelay(150)\n#CliTest.AfterCpu = 1"));
        QCOMPARE(readEvent(afterCpu).value("event").toString(), "accepted");
        QTRY_COMPARE(worker->State(), GcodeScript::ExecutionState::WaitingForTimer);
        QTest::qWait(50);
        QVERIFY(worker->IsRunning());
        QVERIFY(!VariableManager::instance().containsFullKeyScoped("cli_test", "CliTest.AfterCpu"));
        do { result = readEvent(afterCpu); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());

        // Camera timer signals originate on the worker, but start/stop and UI
        // reads must run on the window thread. No camera is opened in this test.
        window.ui->leCaptureInterval->setText("60000");
        QSignalSpy resumed(worker, &GcodeScript::ResumeCamera);
        QLocalSocket resumeCamera;
        request(resumeCamera, runRequest("M98 PresumeCamera()\nM98 Pdelay(50)"));
        QCOMPARE(readEvent(resumeCamera).value("event").toString(), "accepted");
        do { result = readEvent(resumeCamera); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());
        QCOMPARE(resumed.size(), 1);
        QTRY_VERIFY(window.CameraTimer.isActive());
        QLocalSocket pauseCamera;
        request(pauseCamera, runRequest("M98 PpauseCamera()"));
        QCOMPARE(readEvent(pauseCamera).value("event").toString(), "accepted");
        do { result = readEvent(pauseCamera); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());
        QTRY_VERIFY(!window.CameraTimer.isActive());

        // Two real workers communicate through project-scoped variables. A
        // similarly named variable from another project must remain untouched.
        window.AddScriptThread();
        auto* secondWorker = window.GcodeScripts.at(1);
        QVERIFY(secondWorker->thread() != worker->thread());
        VariableManager::instance().updateVarScoped("cli_test", "CliTest.Shared", 0);
        VariableManager::instance().updateVarScoped("other_project", "CliTest.Shared", 99);
        QLocalSocket reader;
        auto readerRequest = runRequest("M98 PwaitUntil(#CliTest.Shared == 42, 2000, 10, \"shared timeout\")\n#CliTest.Reader = 1");
        readerRequest.insert("thread", 1);
        request(reader, readerRequest);
        QCOMPARE(readEvent(reader).value("event").toString(), "accepted");
        QTRY_COMPARE(secondWorker->State(), GcodeScript::ExecutionState::WaitingForCondition);
        QLocalSocket writer;
        request(writer, runRequest("#CliTest.Shared = 42"));
        QCOMPARE(readEvent(writer).value("event").toString(), "accepted");
        do { result = readEvent(writer); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());
        do { result = readEvent(reader); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());
        QCOMPARE(VariableManager::instance().getVarScoped("cli_test", "CliTest.Reader").toInt(), 1);
        QCOMPARE(VariableManager::instance().getVarScoped("other_project", "CliTest.Shared").toInt(), 99);

        // Model delayed camera callbacks without opening a physical camera.
        // A result from the stopped run must not finish the restarted run.
        disconnect(worker, &GcodeScript::CaptureAndDetectRequest,
                   window.CameraInstance, &Camera::CaptureAndDetect);
        QSignalSpy captures(worker, &GcodeScript::CaptureAndDetectRequest);
        QLocalSocket oldVision;
        request(oldVision, runRequest("M98 PcaptureAndDetect(0)"));
        const auto oldVisionAccepted = readEvent(oldVision);
        QCOMPARE(oldVisionAccepted.value("event").toString(), "accepted");
        QTRY_COMPARE(captures.size(), 1);
        const quint64 oldVisionId = captures.first().at(0).toULongLong();
        QLocalSocket stopVision;
        request(stopVision, {{"command", "stop"}, {"runId", oldVisionAccepted.value("runId")}});
        QCOMPARE(readEvent(stopVision).value("event").toString(), "stop-requested");
        do { result = readEvent(oldVision); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(!result.value("success").toBool());
        QLocalSocket freshVision;
        request(freshVision, runRequest("M98 PcaptureAndDetect(0)\n#CliTest.FreshVision = 1"));
        QCOMPARE(readEvent(freshVision).value("event").toString(), "accepted");
        QTRY_COMPARE(captures.size(), 2);
        const quint64 freshVisionId = captures.last().at(0).toULongLong();
        QVERIFY(freshVisionId != oldVisionId);
        QMetaObject::invokeMethod(worker, "GetResponse", Qt::QueuedConnection,
                                  Q_ARG(QString, QStringLiteral("vision0")),
                                  Q_ARG(QString, QString("FrameReady:%1").arg(oldVisionId)));
        QTest::qWait(50);
        QVERIFY(worker->IsRunning());
        QVERIFY(!VariableManager::instance().containsFullKeyScoped("cli_test", "CliTest.FreshVision"));
        QMetaObject::invokeMethod(worker, "GetResponse", Qt::QueuedConnection,
                                  Q_ARG(QString, QStringLiteral("vision0")),
                                  Q_ARG(QString, QString("FrameReady:%1").arg(freshVisionId)));
        do { result = readEvent(freshVision); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());
        QCOMPARE(VariableManager::instance().getVarScoped("cli_test", "CliTest.FreshVision").toInt(), 1);

        disconnect(worker, &GcodeScript::ClaimObjectCorrelatedRequest,
                   window.TrackingManagerInstance, &TrackingManager::ClaimObjectCorrelated);
        QSignalSpy claims(worker, &GcodeScript::ClaimObjectCorrelatedRequest);
        const QString claimSource = "M98 PclaimObject(0, #CliTest.Target, \"robot0\", -100, 100, -100, 100)";
        VariableManager::instance().updateVarScoped("cli_test", "CliTest.Target.UID", 999);
        QLocalSocket oldClaim;
        request(oldClaim, runRequest(claimSource));
        const auto oldClaimAccepted = readEvent(oldClaim);
        QCOMPARE(oldClaimAccepted.value("event").toString(), "accepted");
        QTRY_COMPARE(claims.size(), 1);
        const quint64 oldClaimId = claims.first().at(0).toULongLong();
        QLocalSocket stopClaim;
        request(stopClaim, {{"command", "stop"}, {"runId", oldClaimAccepted.value("runId")}});
        QCOMPARE(readEvent(stopClaim).value("event").toString(), "stop-requested");
        do { result = readEvent(oldClaim); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(!result.value("success").toBool());
        QLocalSocket freshClaim;
        request(freshClaim, runRequest(claimSource));
        QCOMPARE(readEvent(freshClaim).value("event").toString(), "accepted");
        QTRY_COMPARE(claims.size(), 2);
        const quint64 freshClaimId = claims.last().at(0).toULongLong();
        QVERIFY(freshClaimId != oldClaimId);
        const QVariantMap oldClaimResult{{"Found", true}, {"UID", 111}, {"ClaimOwner", "robot0"}};
        QMetaObject::invokeMethod(worker, "GetTrackingResponse", Qt::QueuedConnection,
                                  Q_ARG(quint64, oldClaimId), Q_ARG(QString, QStringLiteral("tracking0:robot0")),
                                  Q_ARG(QString, QStringLiteral("Claimed")), Q_ARG(QVariantMap, oldClaimResult));
        // Legacy broadcasts must also be ignored during a correlated wait.
        QMetaObject::invokeMethod(worker, "GetResponse", Qt::QueuedConnection,
                                  Q_ARG(QString, QStringLiteral("tracking0:robot0")),
                                  Q_ARG(QString, QStringLiteral("Claimed")));
        QTest::qWait(50);
        QVERIFY(worker->IsRunning());
        QCOMPARE(VariableManager::instance().getVarScoped("cli_test", "CliTest.Target.UID").toInt(), 999);
        const QVariantMap freshClaimResult{{"Found", true}, {"UID", 222}, {"ClaimOwner", "robot0"}};
        QMetaObject::invokeMethod(worker, "GetTrackingResponse", Qt::QueuedConnection,
                                  Q_ARG(quint64, freshClaimId), Q_ARG(QString, QStringLiteral("tracking0:robot0")),
                                  Q_ARG(QString, QStringLiteral("Claimed")), Q_ARG(QVariantMap, freshClaimResult));
        do { result = readEvent(freshClaim); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());
        QCOMPARE(VariableManager::instance().getVarScoped("cli_test", "CliTest.Target.UID").toInt(), 222);

        disconnect(worker, &GcodeScript::GetObjectsCorrelatedRequest,
                   window.TrackingManagerInstance, &TrackingManager::GetObjectsInAreaCorrelated);
        QSignalSpy areaQueries(worker, &GcodeScript::GetObjectsCorrelatedRequest);
        const QString areaSource = "#CliTest.Area = #GetObjectInArea(0, X_MIN=-100, X_MAX=100)";
        VariableManager::instance().updateVarScoped("cli_test", "CliTest.Area.Count", 999);
        VariableManager::instance().updateVarScoped("cli_test", "CliTest.Area.1.UID", 999);
        QLocalSocket oldArea;
        request(oldArea, runRequest(areaSource));
        const auto oldAreaAccepted = readEvent(oldArea);
        QCOMPARE(oldAreaAccepted.value("event").toString(), "accepted");
        QTRY_COMPARE(areaQueries.size(), 1);
        const quint64 oldAreaId = areaQueries.first().at(0).toULongLong();
        QLocalSocket stopArea;
        request(stopArea, {{"command", "stop"}, {"runId", oldAreaAccepted.value("runId")}});
        QCOMPARE(readEvent(stopArea).value("event").toString(), "stop-requested");
        do { result = readEvent(oldArea); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(!result.value("success").toBool());
        QLocalSocket freshArea;
        request(freshArea, runRequest(areaSource));
        QCOMPARE(readEvent(freshArea).value("event").toString(), "accepted");
        QTRY_COMPARE(areaQueries.size(), 2);
        const quint64 freshAreaId = areaQueries.last().at(0).toULongLong();
        QVERIFY(freshAreaId != oldAreaId);
        const QVariantMap oldAreaResult{{"Count", 1}, {"0.UID", 111},
            {"__Objects", QVariant::fromValue(QVector<ObjectInfo>{ObjectInfo(111, 1, QVector3D(), 1, 1, 0)})}};
        QMetaObject::invokeMethod(worker, "GetTrackingResponse", Qt::QueuedConnection,
                                  Q_ARG(quint64, oldAreaId), Q_ARG(QString, QStringLiteral("tracking0")),
                                  Q_ARG(QString, QStringLiteral("Done")), Q_ARG(QVariantMap, oldAreaResult));
        QTest::qWait(50);
        QVERIFY(worker->IsRunning());
        QCOMPARE(VariableManager::instance().getVarScoped("cli_test", "CliTest.Area.Count").toInt(), 999);
        const QVariantMap freshAreaResult{{"Count", 0}, {"__Objects", QVariant::fromValue(QVector<ObjectInfo>{})}};
        QMetaObject::invokeMethod(worker, "GetTrackingResponse", Qt::QueuedConnection,
                                  Q_ARG(quint64, freshAreaId), Q_ARG(QString, QStringLiteral("tracking0")),
                                  Q_ARG(QString, QStringLiteral("Done")), Q_ARG(QVariantMap, freshAreaResult));
        do { result = readEvent(freshArea); } while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());
        QCOMPARE(VariableManager::instance().getVarScoped("cli_test", "CliTest.Area.Count").toInt(), 0);
        QVERIFY(!VariableManager::instance().containsFullKeyScoped("cli_test", "CliTest.Area.1.UID"));
        QVERIFY(!VariableManager::instance().containsFullKeyScoped("cli_test", "CliTest.Area.__Objects"));

        // Execute the exact operator examples through the real CLI bridge and
        // editor/worker composition, not a duplicate source string.
        const QString tour = QFINDTESTDATA("../../script-example/gscript-command-tour");
        QVERIFY(!tour.isEmpty());
        for (const QString& name : {QString("00-language.gcode"), QString("01-math.gcode")}) {
            QFile file(tour + '/' + name);
            QVERIFY(file.open(QIODevice::ReadOnly));
            QLocalSocket example;
            request(example, runRequest(QString::fromUtf8(file.readAll())));
            QCOMPARE(readEvent(example).value("event").toString(), "accepted");
            do { result = readEvent(example); } while (!result.isEmpty() && result.value("event") != "finished");
            QVERIFY2(result.value("success").toBool(), qPrintable(QJsonDocument(result).toJson()));
            QCOMPARE(hardware.count(), 0);
        }

        // Formatting alone must not block a second CLI run on the same editor.
        window.changeFontSize(2);
        QLocalSocket longRun;
        request(longRun, runRequest("M98 Pdelay(10000)"));
        const auto accepted = readEvent(longRun);
        QCOMPARE(accepted.value("event").toString(), "accepted");
        QLocalSocket duplicate;
        request(duplicate, runRequest("#CliTest.Value = 0"));
        QCOMPARE(readEvent(duplicate).value("event").toString(), "error");
        QLocalSocket stop;
        request(stop, {{"command", "stop"}, {"runId", accepted.value("runId")}});
        QCOMPARE(readEvent(stop).value("event").toString(), "stop-requested");
        do { result = readEvent(longRun); } while (!result.isEmpty() && result.value("event") != "finished");
        QCOMPARE(result.value("event").toString(), "finished");
        QVERIFY(!result.value("success").toBool());
        QTRY_VERIFY(!worker->IsRunning());

        // Losing the controlling connection stops only its own run.
        QLocalSocket lost;
        request(lost, runRequest("M98 Pdelay(10000)"));
        QCOMPARE(readEvent(lost).value("event").toString(), "accepted");
        QTRY_VERIFY(worker->IsRunning());
        lost.abort();
        QTRY_VERIFY(!worker->IsRunning());
        QTest::qWait(20);

        QLocalSocket invalid;
        request(invalid, runRequest("M98 PthisDoesNotExist()"));
        QCOMPARE(readEvent(invalid).value("event").toString(), "error");
        QCOMPARE(hardware.count(), 0);

        const QString clean = window.ui->pteGcodeArea->toPlainText();
        window.ui->pteGcodeArea->insertPlainText("; unsaved edit\n");
        const QString draft = window.ui->pteGcodeArea->toPlainText();
        QLocalSocket dirty;
        request(dirty, runRequest("#CliTest.Value = 0"));
        const auto rejected = readEvent(dirty);
        QCOMPARE(rejected.value("event").toString(), "error");
        QVERIFY(rejected.value("message").toString().contains("unsaved"));
        QCOMPARE(window.ui->pteGcodeArea->toPlainText(), draft);
        QCOMPARE(hardware.count(), 0);

        window.ui->pteGcodeArea->setPlainText(clean);
        QLocalSocket fault;
        request(fault, runRequest("M98 Passert(0, \"intentional test failure\")"));
        QCOMPARE(readEvent(fault).value("event").toString(), "accepted");
        do { result = readEvent(fault); } while (!result.isEmpty() && result.value("event") != "finished");
        QCOMPARE(result.value("event").toString(), "finished");
        QVERIFY(!result.value("success").toBool());
        QLocalSocket faultedCell;
        request(faultedCell, runRequest("#CliTest.Value = 0"));
        const auto blocked = readEvent(faultedCell);
        QCOMPARE(blocked.value("event").toString(), "error");
        QVERIFY(blocked.value("message").toString().contains("cell"));
        QCOMPARE(hardware.count(), 0);

        QLocalSocket unsafeReset;
        request(unsafeReset, {{"command", "reset-fault"}, {"project", "cli_test"}});
        const auto unsafeResetResult = readEvent(unsafeReset);
        QCOMPARE(unsafeResetResult.value("event").toString(), "error");
        QVERIFY(unsafeResetResult.value("message").toString().contains("confirm-safe"));

        QLocalSocket reset;
        request(reset, {{"command", "reset-fault"}, {"project", "cli_test"},
                        {"confirmSafe", true}});
        QCOMPARE(readEvent(reset).value("event").toString(), "fault-reset");
        QTRY_COMPARE(window.cellStateName(), QStringLiteral("Ready"));

        QLocalSocket recovered;
        request(recovered, runRequest("#CliTest.Recovered = 1"));
        QCOMPARE(readEvent(recovered).value("event").toString(), "accepted");
        do { result = readEvent(recovered); }
        while (!result.isEmpty() && result.value("event") != "finished");
        QVERIFY(result.value("success").toBool());

        FailingCliPrimitive provider;
        QString registrationError;
        QVERIFY2(PluginExtensionRegistry::instance().registerGScriptProvider(
                     "test.cli-failure", &provider, &provider, &registrationError), qPrintable(registrationError));
        const auto unregisterProvider = qScopeGuard([] {
            PluginExtensionRegistry::instance().unregisterPlugin("test.cli-failure");
        });
        for (const bool throwing : {false, true}) {
            provider.throwException = throwing;
            provider.calledOnOwnerThread = false;
            QLocalSocket pluginFailure;
            request(pluginFailure, runRequest("M98 PcliTestFailure()\n#CliTest.AfterFailure = 1"));
            QCOMPARE(readEvent(pluginFailure).value("event").toString(), "accepted");
            do { result = readEvent(pluginFailure); }
            while (!result.isEmpty() && result.value("event") != "finished");
            QCOMPARE(result.value("event").toString(), "finished");
            QVERIFY(!result.value("success").toBool());
            QVERIFY(result.value("message").toString().contains(
                throwing ? "integration provider exception" : "integration provider rejection"));
            QVERIFY(provider.calledOnOwnerThread);
            QVERIFY(!VariableManager::instance().containsFullKeyScoped("cli_test", "CliTest.AfterFailure"));
            QTRY_COMPARE(window.cellStateName(), QStringLiteral("Faulted"));
            QLocalSocket resetPluginFault;
            request(resetPluginFault, {{"command", "reset-fault"}, {"project", "cli_test"}, {"confirmSafe", true}});
            QCOMPARE(readEvent(resetPluginFault).value("event").toString(), "fault-reset");
            QTRY_COMPARE(window.cellStateName(), QStringLiteral("Ready"));
        }
        // A GetInfo refresh for an already open transport is not a reconnect.
        auto* broker = window.findChild<DeviceCommandBroker*>();
        QVERIFY(broker);
        const auto encoderInfo = [](const QString& state) {
            return QString::fromUtf8(QJsonDocument(QJsonObject{
                {"device", "encoder"}, {"id", 0}, {"state", state},
                {"com_name", "test-transport"}}).toJson(QJsonDocument::Compact));
        };
        window.GetDeviceInfo(encoderInfo("open"));
        broker->HandleDeviceUnavailable("encoder0", "test interrupted transport");
        window.GetDeviceInfo(encoderInfo("open"));
        QVERIFY(!broker->acquireManualControl("test/recovery", "encoder0"));
        window.GetDeviceInfo(encoderInfo("close"));
        window.GetDeviceInfo(encoderInfo("open"));
        QVERIFY(broker->acquireManualControl("test/recovery", "encoder0"));
        broker->releaseManualControl("test/recovery", "encoder0");
        // Simulate a transport closing while a request is in flight. Disconnect
        // the physical dispatch adapter: no serial port is used by this case.
        disconnect(broker, &DeviceCommandBroker::DispatchCommand, &window, nullptr);
        QVERIFY(broker->Submit("test/recovery", "encoder0", "M317",
                                DeviceCommandBroker::Origin::Tracking) > 0);
        QVERIFY(broker->hasActiveCommand("encoder0"));
        window.GetDeviceInfo(encoderInfo("close"));
        QCOMPARE(broker->pendingCommandCount("encoder0"), 0);
        broker->HandleDeviceResponse("encoder0", "999");
        window.GetDeviceInfo(encoderInfo("open"));
        QVERIFY(broker->acquireManualControl("test/recovery", "encoder0"));
        broker->releaseManualControl("test/recovery", "encoder0");
        projects.RobotWindows.clear();
        QVERIFY(QDir::setCurrent(originalDirectory));
    }
};
QTEST_MAIN(CliIntegrationTest)
#include "tst_cli_integration.moc"
