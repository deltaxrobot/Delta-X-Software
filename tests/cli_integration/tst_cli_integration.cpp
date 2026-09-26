#include <QtTest>
#include <QTemporaryDir>
#include <QLocalSocket>
#include <QUuid>
#include <QScopeGuard>
#include "RobotWindow.h"
#include "ProjectManager.h"
#include "GScriptCliBridge.h"
#include "CliProtocol.h"
#include "ui_RobotWindow.h"

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
        projects.RobotWindows.append(&window);
        const QString endpoint = "deltax-test-" + QUuid::createUuid().toString(QUuid::WithoutBraces);
        GScriptCliBridge bridge(&projects, nullptr, endpoint);
        auto* worker = window.GcodeScripts.first();
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
        projects.RobotWindows.clear();
        QVERIFY(QDir::setCurrent(originalDirectory));
    }
};
QTEST_MAIN(CliIntegrationTest)
#include "tst_cli_integration.moc"
