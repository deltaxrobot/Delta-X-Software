#include <QtTest>
#include <QSignalSpy>
#include <QTimer>
#include <QTemporaryDir>
#include <QScopeGuard>
#include <QDir>
#include <QFile>
#include <algorithm>
#include <future>
#include <vector>

#include "GcodeScript.h"
#include "GScriptAnalyzer.h"
#include "PluginExtensionRegistry.h"
#include "SoftwareManager.h"
#include "VariableManager.h"
#include "DeltaXGScriptProvider.h"

class RuntimePrimitiveProvider final : public QObject,
                                       public DeltaXGScriptProvider
{
public:
    QVariantList gscriptPrimitives() const override
    {
        return {QVariantMap{
            {QStringLiteral("name"), QStringLiteral("testruntime")},
            {QStringLiteral("signature"),
             QStringLiteral("M98 PtestRuntime(result, left, right)")},
            {QStringLiteral("description"), QStringLiteral("Runtime test")},
            {QStringLiteral("minArgs"), 3},
            {QStringLiteral("maxArgs"), 3},
            {QStringLiteral("resultArgument"), 0},
        }};
    }

    bool executeGScriptPrimitive(const QString& name,
                                 const QVariantList& arguments,
                                 QVariant* result, QString* error) override
    {
        if (name != QStringLiteral("testruntime") || arguments.size() != 2) {
            if (error)
                *error = QStringLiteral("invalid test call");
            return false;
        }
        if (result)
            *result = arguments.at(0).toDouble() * arguments.at(1).toDouble();
        return true;
    }
};

class GScriptRuntimeTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void explicitDeviceAndPsendRouteDeterministically();
    void selectDeviceRoutesGenericCommands();
    void claimResolvesOwnerValueAndResultIdentifier();
    void localWhileAndSwitchStayInsideFunction();
    void concurrentUseOfOnePhysicalDeviceFaultsSecondThread();
    void deviceErrorFaultsImmediately_data();
    void deviceErrorFaultsImmediately();
    void unknownM98FaultsWithoutSendingToDevice();
    void waitUntilObservesRuntimeVariable();
    void waitUntilFaultsOnTimeout();
    void finalAsyncInstructionWaitsForCompletion_data();
    void finalAsyncInstructionWaitsForCompletion();
    void windowsLineEndingsResolveSubprograms();
    void commandTour_data();
    void commandTour();
    void commandTourCoverage();
    void globalScriptCounterIsAtomic();
    void pluginPrimitiveIsAnalyzedExecutedAndStored();
    void inlineCommentsRespectQuotedSemicolons();
    void macroAliasesDoNotModifyArgumentIdentifiers();

private:
    const QString scope = QStringLiteral("gscript_runtime_test");
};

void GScriptRuntimeTest::init()
{
    PluginExtensionRegistry::instance().clearForTests();
    VariableManager::instance().removeVarScoped(scope, QString());
}

void GScriptRuntimeTest::cleanup()
{
    PluginExtensionRegistry::instance().clearForTests();
    VariableManager::instance().removeVarScoped(scope, QString());
}

void GScriptRuntimeTest::inlineCommentsRespectQuotedSemicolons()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("quoted_semicolon");
    QSignalSpy finished(&script, &GcodeScript::ExecutionFinished);
    QSignalSpy logs(&script, &GcodeScript::LogMessage);

    const QString source = QStringLiteral(
        "M98 Passert(1, \"safe; message\") ; actual inline comment\n"
        "M98 PlogMessage(\"PASS; runtime\")\n");
    QVERIFY(!GScriptAnalyzer::analyze(source).hasErrors());
    script.ExecuteGcode(source, GcodeScript::BEGIN);

    QTRY_COMPARE_WITH_TIMEOUT(finished.count(), 1, 1000);
    QVERIFY(finished.first().first().toBool());
    QCOMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QVERIFY(std::any_of(logs.cbegin(), logs.cend(), [](const QList<QVariant>& event) {
        return event.first().toString() == QStringLiteral("PASS; runtime");
    }));
}

void GScriptRuntimeTest::macroAliasesDoNotModifyArgumentIdentifiers()
{
    VariableManager::instance().updateVarScoped(
        scope, QStringLiteral("robot0.HOME_Z"), -291.28,
        VariableManager::Persistence::Runtime);
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("macro_identifier");
    QSignalSpy finished(&script, &GcodeScript::ExecutionFinished);

    const QString source = QStringLiteral(
        "M98 Passert(#robot0.HOME_Z < -260, \"HOME_Z was modified\")\n");
    QVERIFY(!GScriptAnalyzer::analyze(source).hasErrors());
    script.ExecuteGcode(source, GcodeScript::BEGIN);

    QTRY_COMPARE_WITH_TIMEOUT(finished.count(), 1, 1000);
    QVERIFY2(finished.first().first().toBool(),
             qPrintable(finished.first().at(1).toString()));
    QCOMPARE(script.State(), GcodeScript::ExecutionState::Completed);
}

void GScriptRuntimeTest::pluginPrimitiveIsAnalyzedExecutedAndStored()
{
    RuntimePrimitiveProvider provider;
    QString error;
    QVERIFY(PluginExtensionRegistry::instance().registerGScriptProvider(
        QStringLiteral("test.runtime"), &provider, &provider, &error));

    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("plugin_primitive");
    const QString source = QStringLiteral(
        "M98 PtestRuntime(#Product, 6, 7)\n");
    const QList<GScriptDiagnostic> validDiagnostics = script.Validate(source);
    QVERIFY(std::none_of(validDiagnostics.cbegin(), validDiagnostics.cend(),
                         [](const GScriptDiagnostic& diagnostic) {
        return diagnostic.severity == GScriptDiagnostic::Error;
    }));

    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance()
                 .getVarScoped(scope, QStringLiteral("Product"))
                 .toDouble(),
             42.0);

    const QList<GScriptDiagnostic> invalid = script.Validate(
        QStringLiteral("M98 PtestRuntime(#Product, 6)\n"));
    QVERIFY(std::any_of(invalid.cbegin(), invalid.cend(),
                        [](const GScriptDiagnostic& diagnostic) {
        return diagnostic.code == QStringLiteral("GS1920");
    }));
}

void GScriptRuntimeTest::globalScriptCounterIsAtomic()
{
    SoftwareManager* manager = SoftwareManager::GetInstance();
    const int initialCount = manager->RunningScriptCount();
    std::vector<std::future<void>> workers;
    for (int worker = 0; worker < 8; ++worker) {
        workers.push_back(std::async(std::launch::async, [manager]() {
            for (int iteration = 0; iteration < 2000; ++iteration)
                manager->ScriptStarted();
            for (int iteration = 0; iteration < 2000; ++iteration)
                manager->ScriptFinished();
        }));
    }
    for (auto& worker : workers)
        worker.get();
    QCOMPARE(manager->RunningScriptCount(), initialCount);
}

void GScriptRuntimeTest::explicitDeviceAndPsendRouteDeterministically()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("route");
    QStringList devices;
    QStringList commands;
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&](const QString& device, const QString& command) {
        devices.append(device);
        commands.append(command);
        QTimer::singleShot(0, &script, [&script, device]() {
            script.GetResponse(device, QStringLiteral("P123.5"));
        });
    });

    script.ExecuteGcode(
        QStringLiteral("encoder1 M317\n"
                       "M98 Psend(device2, \"M42 P1\", #IoReply, 1000)\n"),
        GcodeScript::BEGIN);

    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(devices, QStringList({QStringLiteral("encoder1"), QStringLiteral("device2")}));
    QCOMPARE(commands, QStringList({QStringLiteral("M317"), QStringLiteral("M42 P1")}));
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("IoReply")).toString(),
             QStringLiteral("P123.5"));
}

void GScriptRuntimeTest::selectDeviceRoutesGenericCommands()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("select");
    QString routedDevice;
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&](const QString& device, const QString&) {
        routedDevice = device;
        QTimer::singleShot(0, &script, [&script, device]() {
            script.GetResponse(device, QStringLiteral("ok"));
        });
    });

    script.ExecuteGcode(QStringLiteral("SELECT device3\nM42 P1\n"), GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(routedDevice, QStringLiteral("device3"));
}

void GScriptRuntimeTest::claimResolvesOwnerValueAndResultIdentifier()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("claim");
    QString capturedResult;
    QString capturedOwner;
    connect(&script, &GcodeScript::ClaimObjectRequest, &script,
            [&](int trackingId, const QString& resultName, const QString& owner,
                float, float, float, float, int, int) {
        QCOMPARE(trackingId, 0);
        capturedResult = resultName;
        capturedOwner = owner;
        QTimer::singleShot(0, &script, [&script, owner]() {
            script.GetResponse(QStringLiteral("tracking0:") + owner, QStringLiteral("None"));
        });
    });

    script.ExecuteGcode(
        QStringLiteral("#Owner = \"robot7\"\n"
                       "M98 PclaimObject(0, #Target, #Owner, 0, 100, 0, 100, -1, 5000)\n"),
        GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(capturedResult, QStringLiteral("Target"));
    QCOMPARE(capturedOwner, QStringLiteral("robot7"));
}

void GScriptRuntimeTest::localWhileAndSwitchStayInsideFunction()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("language");
    const QString source = QStringLiteral(
        "FUNCTION Sum(limit)\n"
        "  LOCAL #i = 0\n"
        "  LOCAL #sum = 0\n"
        "  WHILE #i < #limit\n"
        "    #sum = #sum + #i\n"
        "    #i = #i + 1\n"
        "  ENDWHILE\n"
        "  SWITCH #sum\n"
        "    CASE 3\n"
        "      RETURN #sum\n"
        "    DEFAULT\n"
        "      RETURN -1\n"
        "  ENDSWITCH\n"
        "ENDFUNCTION\n"
        "#Result = #Sum(3)\n");

    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Result")).toDouble(), 3.0);
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, QStringLiteral("i")));
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, QStringLiteral("sum")));
}

void GScriptRuntimeTest::concurrentUseOfOnePhysicalDeviceFaultsSecondThread()
{
    GcodeScript first;
    GcodeScript second;
    first.ProjectName = scope;
    second.ProjectName = scope;
    first.ID = QStringLiteral("owner");
    second.ID = QStringLiteral("contender");

    first.ExecuteGcode(QStringLiteral("robot0 G01 X1\n"), GcodeScript::BEGIN);
    QCOMPARE(first.State(), GcodeScript::ExecutionState::WaitingForDevice);

    second.ExecuteGcode(QStringLiteral("robot0 G01 X2\n"), GcodeScript::BEGIN);
    QCOMPARE(second.State(), GcodeScript::ExecutionState::Faulted);
    QVERIFY(VariableManager::instance()
                .getVarScoped(scope, QStringLiteral("GScript.contender.LastError"))
                .toString().contains(QStringLiteral("busy"), Qt::CaseInsensitive));

    first.Stop();
    QCOMPARE(first.State(), GcodeScript::ExecutionState::Idle);
}

void GScriptRuntimeTest::deviceErrorFaultsImmediately_data()
{
    QTest::addColumn<QString>("response");
    QTest::addColumn<QString>("expected");
    QTest::newRow("generic-error") << QStringLiteral("error: limit reached")
                                    << QStringLiteral("limit reached");
    QTest::newRow("firmware-unknown") << QStringLiteral("Unknown:DesiredPoint is outside the moving area!")
                                      << QStringLiteral("DesiredPoint");
    QTest::newRow("emergency-stop") << QStringLiteral("Delta:EStop Pressing!")
                                    << QStringLiteral("EStop");
    QTest::newRow("stop") << QStringLiteral("Delta:Stop")
                           << QStringLiteral("Delta:Stop");
}

void GScriptRuntimeTest::deviceErrorFaultsImmediately()
{
    QFETCH(QString, response);
    QFETCH(QString, expected);
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("error");
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&](const QString& device, const QString&) {
        QTimer::singleShot(0, &script, [&script, device, response]() {
            script.GetResponse(device, response);
        });
    });

    script.ExecuteGcode(QStringLiteral("robot4 G01 X999\n"), GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
    QVERIFY(VariableManager::instance()
                .getVarScoped(scope, QStringLiteral("GScript.error.LastError"))
                .toString().contains(expected));
}

void GScriptRuntimeTest::unknownM98FaultsWithoutSendingToDevice()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("unknown_macro");
    QSignalSpy deviceSpy(&script, &GcodeScript::SendGcodeToDevice);

    script.ExecuteGcode(QStringLiteral("M98 PcalimObject(0)\n"), GcodeScript::BEGIN);

    QCOMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
    QCOMPARE(deviceSpy.count(), 0);
    QVERIFY(VariableManager::instance()
                .getVarScoped(scope, QStringLiteral("GScript.unknown_macro.LastError"))
                .toString().contains(QStringLiteral("Undefined M98")));
}

void GScriptRuntimeTest::waitUntilObservesRuntimeVariable()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("wait_success");
    VariableManager::instance().updateVarScoped(scope, QStringLiteral("Vacuum.OK"), 0,
                                                VariableManager::Persistence::Runtime);
    QTimer::singleShot(20, &script, [this]() {
        VariableManager::instance().updateVarScoped(
            scope, QStringLiteral("Vacuum.OK"), 1,
            VariableManager::Persistence::Runtime);
    });

    script.ExecuteGcode(
        QStringLiteral("M98 PwaitUntil(#Vacuum.OK == 1, 500, 5, \"Vacuum not reached\")\n"
                       "#PickConfirmed = 1\n"),
        GcodeScript::BEGIN);

    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForCondition);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance()
                 .getVarScoped(scope, QStringLiteral("PickConfirmed")).toInt(), 1);
}

void GScriptRuntimeTest::finalAsyncInstructionWaitsForCompletion_data()
{
    QTest::addColumn<QString>("source");
    QTest::addColumn<int>("waitingState");
    QTest::newRow("delay") << QStringLiteral("M98 Pdelay(100)")
        << int(GcodeScript::ExecutionState::WaitingForTimer);
    QTest::newRow("device") << QStringLiteral("device4 M42 P1")
        << int(GcodeScript::ExecutionState::WaitingForDevice);
    QTest::newRow("send") << QStringLiteral("M98 Psend(device4, \"M42 P1\", #Reply, 1000)")
        << int(GcodeScript::ExecutionState::WaitingForDevice);
    QTest::newRow("condition") << QStringLiteral("M98 PwaitUntil(#Ready == 1, 1000, 5)")
        << int(GcodeScript::ExecutionState::WaitingForCondition);
}

void GScriptRuntimeTest::windowsLineEndingsResolveSubprograms()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("crlf_subprogram");
    const QString source = QStringLiteral(
        "#Counter = 0\r\n"
        "M98 P2000\r\n"
        "GOTO 100\r\n"
        "O2000\r\n"
        "#Counter = #Counter + 1\r\n"
        "M99\r\n"
        "N100 M98 Passert(#Counter == 1, \"CRLF subprogram failed\")\r\n");

    script.ExecuteGcode(source, GcodeScript::BEGIN);

    QCOMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance()
                 .getVarScoped(scope, QStringLiteral("Counter")).toInt(), 1);
}

void GScriptRuntimeTest::finalAsyncInstructionWaitsForCompletion()
{
    QFETCH(QString, source);
    QFETCH(int, waitingState);
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("last_async");
    VariableManager::instance().updateVarScoped(scope, QStringLiteral("Ready"), 0,
                                                VariableManager::Persistence::Runtime);
    QSignalSpy finished(&script, &GcodeScript::ExecutionFinished);
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(int(script.State()), waitingState);
    QVERIFY(script.IsRunning());
    QCOMPARE(finished.count(), 0);
    QTest::qWait(20);
    QCOMPARE(finished.count(), 0);
    if (waitingState == int(GcodeScript::ExecutionState::WaitingForDevice))
        script.GetResponse(QStringLiteral("device4"), QStringLiteral("ok"));
    else if (waitingState == int(GcodeScript::ExecutionState::WaitingForCondition))
        VariableManager::instance().updateVarScoped(scope, QStringLiteral("Ready"), 1,
                                                    VariableManager::Persistence::Runtime);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(finished.count(), 1);
}

void GScriptRuntimeTest::waitUntilFaultsOnTimeout()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("wait_timeout");
    VariableManager::instance().updateVarScoped(scope, QStringLiteral("Vacuum.OK"), 0,
                                                VariableManager::Persistence::Runtime);

    script.ExecuteGcode(
        QStringLiteral("M98 PwaitUntil(#Vacuum.OK == 1, 30, 5, \"Vacuum timeout\")\n"),
        GcodeScript::BEGIN);

    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
    QVERIFY(VariableManager::instance()
                .getVarScoped(scope, QStringLiteral("GScript.wait_timeout.LastError"))
                .toString().contains(QStringLiteral("Vacuum timeout")));
}

void GScriptRuntimeTest::commandTourCoverage()
{
    const QString root = QFINDTESTDATA("../../script-example/gscript-command-tour");
    QVERIFY(!root.isEmpty());
    QString examples;
    for (const auto& name : QDir(root).entryList({"*.gcode"}, QDir::Files)) {
        QFile file(root + '/' + name);
        QVERIFY(file.open(QIODevice::ReadOnly));
        for (const auto& line : QString::fromUtf8(file.readAll()).split('\n'))
            examples += line.section(';', 0, 0) + '\n';
    }
    for (const auto& keyword : GScriptAnalyzer::knownKeywords()) {
        const QRegularExpression pattern("\\b" + keyword + "\\b");
        QVERIFY2(pattern.match(examples).hasMatch(), qPrintable("Missing keyword example: " + keyword));
    }
    // Keep the tour inventory tied to registered built-ins, not a second list.
    QFile runtime(QFINDTESTDATA("../../src/GcodeScript.cpp"));
    QVERIFY(runtime.open(QIODevice::ReadOnly));
    const QString runtimeSource = QString::fromUtf8(runtime.readAll());
    const QRegularExpression functions(R"rx(if \(fname == "([a-z0-9]+)")rx");
    auto calls = functions.globalMatch(runtimeSource);
    int functionCount = 0;
    while (calls.hasNext()) {
        const auto name = calls.next().captured(1);
        ++functionCount;
        const QRegularExpression pattern("#" + name + "\\s*\\(", QRegularExpression::CaseInsensitiveOption);
        QVERIFY2(pattern.match(examples).hasMatch(), qPrintable("Missing function example: " + name));
    }
    QVERIFY(functionCount > 0);
    QFile analyzer(QFINDTESTDATA("../../src/GScriptAnalyzer.cpp"));
    QVERIFY(analyzer.open(QIODevice::ReadOnly));
    const QString analyzerSource = QString::fromUtf8(analyzer.readAll());
    const auto inventory = QRegularExpression("exactTargets = \\{([^}]+)\\}").match(analyzerSource);
    QVERIFY(inventory.hasMatch());
    auto names = QRegularExpression("\"([a-z]+)\"").globalMatch(inventory.captured(1));
    int primitiveCount = 0;
    while (names.hasNext()) {
        const auto name = names.next().captured(1);
        ++primitiveCount;
        const QRegularExpression pattern("\\bM98\\s+P" + name + "\\b", QRegularExpression::CaseInsensitiveOption);
        QVERIFY2(pattern.match(examples).hasMatch(), qPrintable("Missing primitive example: " + name));
    }
    QVERIFY(primitiveCount > 0);
}

void GScriptRuntimeTest::commandTour_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("completionVariable");
    QTest::newRow("language") << "00-language.gcode" << "LanguagePassed";
    QTest::newRow("math") << "01-math.gcode" << "MathPassed";
    QTest::newRow("cloud") << "02-cloud-mapping.gcode" << "CloudPassed";
    QTest::newRow("points") << "03-points-and-map.gcode" << "PointsPassed";
    QTest::newRow("routing") << "10-device-routing.gcode" << "RoutingPassed";
    QTest::newRow("vision") << "11-vision-tracking.gcode" << "VisionPassed";
    QTest::newRow("objects") << "12-object-primitives.gcode" << "ObjectsPassed";
    QTest::newRow("plugin") << "13-plugin.gcode" << "PluginPassed";
    QTest::newRow("legacy-area") << "14-legacy-area-query.gcode" << "AreaPassed";
    QTest::newRow("robot-queries-mock") << "20-robot-readonly.gcode" << "RobotQueriesPassed";
    QTest::newRow("expected-assert-failure") << "90-expected-assert-failure.gcode" << "";
    QTest::newRow("expected-wait-timeout") << "91-expected-wait-timeout.gcode" << "";
}

void GScriptRuntimeTest::commandTour()
{
    QFETCH(QString, fileName);
    QFETCH(QString, completionVariable);
    const QString root = QFINDTESTDATA("../../script-example/gscript-command-tour");
    QVERIFY(!root.isEmpty());
    QFile sourceFile(root + '/' + fileName);
    QVERIFY(sourceFile.open(QIODevice::ReadOnly));
    const QString source = QString::fromUtf8(sourceFile.readAll());
    QTemporaryDir temporary;
    QVERIFY(temporary.isValid());
    const QString previousDirectory = QDir::currentPath();
    QVERIFY(QDir::setCurrent(temporary.path()));
    const auto restoreDirectory = qScopeGuard([&]() { QDir::setCurrent(previousDirectory); });
    RuntimePrimitiveProvider provider;
    QString registrationError;
    QVERIFY(PluginExtensionRegistry::instance().registerGScriptProvider(
        "test.runtime", &provider, &provider, &registrationError));
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "tour";
    auto& variables = VariableManager::instance();
    variables.updateVarScoped(scope, "Examples.Isolated", 1, VariableManager::Persistence::Runtime);
    QSignalSpy logs(&script, &GcodeScript::LogMessage);
    QSignalSpy finished(&script, &GcodeScript::ExecutionFinished);
    QStringList dispatched;
    // No DeviceManager, serial port or socket is constructed in this fixture.
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&](const QString& device, const QString& command) {
        dispatched.append(device + ':' + command);
        QTimer::singleShot(1, &script, [&script, device, command]() {
            QString reply = "Ok";
            if (command == "G28" || command == "Position") reply = "0,0,-300";
            if (command == "ROBOTMODEL") reply = "MODEL:Simulated";
            if (command == "FirmwareVersion") reply = "FirmwareVersion:simulated";
            script.GetResponse(device, reply);
        });
    });
    int captures = 0, updates = 0, claims = 0, releases = 0, completions = 0;
    int areaQueries = 0;
    connect(&script, &GcodeScript::GetObjectsRequest, &script,
            [&](int tracking, const QString& result, float minimum, float maximum, bool xDirection) {
        QCOMPARE(tracking, 0); QCOMPARE(result, "#Examples.Area");
        QCOMPARE(minimum, -100.0f); QCOMPARE(maximum, 100.0f);
        QCOMPARE(xDirection, areaQueries == 0);
        ++areaQueries;
        QTimer::singleShot(1, &script, [&script]() { script.GetResponse("tracking0", "Ok"); });
    });
    connect(&script, &GcodeScript::CaptureAndDetectRequest, &script,
            [&](quint64 id, int tracking) {
        QCOMPARE(tracking, 0);
        ++captures;
        QTimer::singleShot(1, &script, [&script, id, tracking]() {
            script.GetResponse(QString("vision%1").arg(tracking), QString("FrameReady:%1").arg(id));
        });
    });
    connect(&script, &GcodeScript::UpdateTrackingRequest, &script, [&](int tracking) {
        QCOMPARE(tracking, 0);
        ++updates;
        QTimer::singleShot(1, &script, [&script, tracking]() {
            script.GetResponse(QString("tracking%1").arg(tracking), "Ok");
        });
    });
    connect(&script, &GcodeScript::ClaimObjectRequest, &script,
            [&](int tracking, const QString& result, const QString& owner,
                float minX, float maxX, float minY, float maxY, int type, int lease) {
        QCOMPARE(tracking, 0); QCOMPARE(owner, "robot0");
        QCOMPARE(minX, -100.0f); QCOMPARE(maxX, 100.0f);
        QCOMPARE(minY, -100.0f); QCOMPARE(maxY, 100.0f);
        QCOMPARE(type, -1); QCOMPARE(lease, 5000);
        ++claims;
        variables.updateVarScoped(scope, result + ".Found", 1, VariableManager::Persistence::Runtime);
        variables.updateVarScoped(scope, result + ".UID", 42, VariableManager::Persistence::Runtime);
        QTimer::singleShot(1, &script, [&script, owner]() {
            script.GetResponse("tracking0:" + owner, "Claimed");
        });
    });
    connect(&script, &GcodeScript::ReleaseObjectRequest, &script,
            [&](int tracking, int uid, const QString& owner) {
        QCOMPARE(tracking, 0); QCOMPARE(uid, 42); QCOMPARE(owner, "robot0");
        ++releases;
        QTimer::singleShot(1, &script, [&script, owner]() { script.GetResponse("tracking0:" + owner, "Released"); });
    });
    connect(&script, &GcodeScript::CompleteObjectRequest, &script,
            [&](int tracking, int uid, const QString& owner) {
        QCOMPARE(tracking, 0); QCOMPARE(uid, 42); QCOMPARE(owner, "robot0");
        ++completions;
        QTimer::singleShot(1, &script, [&script, owner]() { script.GetResponse("tracking0:" + owner, "Completed"); });
    });
    QSignalSpy added(&script, &GcodeScript::AddObject);
    QSignalSpy cleared(&script, qOverload<QString>(&GcodeScript::DeleteAllObjects));
    QSignalSpy deleted(&script, &GcodeScript::DeleteObject);
    QSignalSpy pause(&script, &GcodeScript::PauseCamera);
    QSignalSpy capture(&script, &GcodeScript::CaptureCamera);
    QSignalSpy resume(&script, &GcodeScript::ResumeCamera);
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE_WITH_TIMEOUT(finished.count(), 1, 10000);
    if (completionVariable.isEmpty()) {
        QCOMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
        QVERIFY(!finished.first().first().toBool());
        QVERIFY(finished.first().at(1).toString().contains("EXPECTED"));
        QVERIFY(!variables.containsFullKeyScoped(scope, "Examples.Unreachable"));
    } else {
        QVERIFY2(finished.first().first().toBool(), qPrintable(finished.first().at(1).toString()));
        QCOMPARE(script.State(), GcodeScript::ExecutionState::Completed);
        QCOMPARE(variables.getVarScoped(scope, "Examples." + completionVariable).toInt(), 1);
    }
    if (fileName == "10-device-routing.gcode") {
        QCOMPARE(dispatched.size(), 12);
        QVERIFY(dispatched.contains("robot0:G01 X15 F200"));
        QVERIFY(dispatched.contains("robot1:G01 X20"));
        QVERIFY(dispatched.contains("conveyor0:M311 S10"));
        QVERIFY(dispatched.contains("encoder0:M317"));
        QVERIFY(dispatched.contains("slider0:M320"));
        QVERIFY(dispatched.contains("device0:M42 P0"));
        QVERIFY(dispatched.contains("robot0:SYNC (10,0,0)"));
    } else if (fileName == "20-robot-readonly.gcode") {
        QCOMPARE(dispatched, QStringList({"robot0:Position", "robot0:ROBOTMODEL"}));
        const QStringList messages = [&logs]() {
            QStringList values;
            for (const auto& event : logs)
                values.append(event.first().toString());
            return values;
        }();
        QVERIFY(messages.contains("0"));
        QVERIFY(messages.contains("-300"));
        QVERIFY(messages.contains("MODEL:Simulated"));
    } else {
        // Fault cleanup may emit a stop request; no other physical commands allowed.
        for (const QString& command : dispatched)
            QVERIFY2(command.endsWith(":M84"), qPrintable(command));
    }
    if (fileName == "00-language.gcode") {
        QVERIFY(std::any_of(logs.cbegin(), logs.cend(), [](const QList<QVariant>& event) {
            return event.first().toString() == QStringLiteral("PASS language");
        }));
    }
    if (fileName == "11-vision-tracking.gcode") {
        QCOMPARE(captures, 1); QCOMPARE(updates, 1); QCOMPARE(claims, 2);
        QCOMPARE(releases, 1); QCOMPARE(completions, 1);
        QCOMPARE(pause.count(), 1); QCOMPARE(capture.count(), 1); QCOMPARE(resume.count(), 1);
    }
    if (fileName == "12-object-primitives.gcode") {
        QCOMPARE(added.count(), 1); QCOMPARE(cleared.count(), 1);
        QCOMPARE(added.first().at(0).toString(), "Examples.Parts");
        QCOMPARE(cleared.first().at(0).toString(), "Examples.Parts");
        QCOMPARE(deleted.count(), 2);
        QCOMPARE(deleted.at(0).at(0).toInt(), 0);
        QCOMPARE(deleted.at(1).at(0).toInt(), 3);
    }
    if (fileName == "14-legacy-area-query.gcode")
        QCOMPARE(areaQueries, 2);
}

QTEST_MAIN(GScriptRuntimeTest)
#include "tst_gscript_runtime.moc"
