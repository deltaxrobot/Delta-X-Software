#include <QtTest>
#include <QSignalSpy>
#include <QTimer>
#include <algorithm>
#include <future>
#include <vector>

#include "GcodeScript.h"
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
    void deviceErrorFaultsImmediately();
    void unknownM98FaultsWithoutSendingToDevice();
    void waitUntilObservesRuntimeVariable();
    void waitUntilFaultsOnTimeout();
    void globalScriptCounterIsAtomic();
    void pluginPrimitiveIsAnalyzedExecutedAndStored();

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

void GScriptRuntimeTest::deviceErrorFaultsImmediately()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("error");
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&](const QString& device, const QString&) {
        QTimer::singleShot(0, &script, [&script, device]() {
            script.GetResponse(device, QStringLiteral("error: limit reached"));
        });
    });

    script.ExecuteGcode(QStringLiteral("robot4 G01 X999\n"), GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
    QVERIFY(VariableManager::instance()
                .getVarScoped(scope, QStringLiteral("GScript.error.LastError"))
                .toString().contains(QStringLiteral("limit reached")));
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

QTEST_MAIN(GScriptRuntimeTest)
#include "tst_gscript_runtime.moc"
