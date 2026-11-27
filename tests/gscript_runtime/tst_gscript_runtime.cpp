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
#include "GScriptSyntax.h"
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
    void inlineStatementsAdvanceExactlyOnce_data();
    void inlineStatementsAdvanceExactlyOnce();
    void quotedPayloadsRemainLiteral();
    void bracketedWaitUntilReevaluatesCondition_data();
    void bracketedWaitUntilReevaluatesCondition();
    void localLoopAllowsQueuedStopAndCleanRestart();
    void stoppedSubprogramDoesNotLeakReturnAddress();
    void earlyFunctionReturnRestoresCallerBlocks();
    void mixedLoopTransfersUnwindCrossedBlocks_data();
    void mixedLoopTransfersUnwindCrossedBlocks();
    void invalidExpressionsAndParametersFaultBeforeDevice_data();
    void invalidExpressionsAndParametersFaultBeforeDevice();
    void strictMathAndExpressionForRemainCompatible();
    void runtimeFaultIncludesCallContext();
    void parenthesizedZeroArgumentPrimitives();
    void correlatedTrackingRejectsStoppedRunResults();
    void synchronousProvidersCompleteWithoutReentryFault();
    void correlatedAreaQueryRejectsStoppedRunSnapshot();

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

void GScriptRuntimeTest::mixedLoopTransfersUnwindCrossedBlocks_data()
{
    QTest::addColumn<QString>("outerOpen");
    QTest::addColumn<QString>("outerClose");
    QTest::addColumn<QString>("innerOpen");
    QTest::addColumn<QString>("innerClose");
    QTest::newRow("for-while") << QStringLiteral("FOR #i = 1 TO 3") << QStringLiteral("ENDFOR")
        << QStringLiteral("WHILE #j < 3\n#j = #j + 1") << QStringLiteral("ENDWHILE");
    QTest::newRow("while-for") << QStringLiteral("WHILE #Outer < 3") << QStringLiteral("ENDWHILE")
        << QStringLiteral("FOR #j = 1 TO 3") << QStringLiteral("ENDFOR");
}

void GScriptRuntimeTest::mixedLoopTransfersUnwindCrossedBlocks()
{
    QFETCH(QString, outerOpen);
    QFETCH(QString, outerClose);
    QFETCH(QString, innerOpen);
    QFETCH(QString, innerClose);
    const QString worker = QStringLiteral(
        "FUNCTION Work()\nLOCAL #j = 0\n%1\n#Visits = #Visits + 1\n"
        "SWITCH #j\nCASE 1\nIF 1\nCONTINUE\nENDIF\nDEFAULT\nIF 1\nBREAK\nENDIF\n"
        "ENDSWITCH\n%2\nRETURN 1\nENDFUNCTION\n").arg(innerOpen, innerClose);
    const QString source = worker + QStringLiteral(
        "#Visits = 0\n#Outer = 0\n%1\nIF 1\n#Result = #Work()\n"
        "#Outer = #Outer + 1\nENDIF\n%2\n#Done = 1\n").arg(outerOpen, outerClose);
    QVERIFY(!GScriptAnalyzer::analyze(source).hasErrors());
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "mixed_transfer";
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Visits").toInt(), 6);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Outer").toInt(), 3);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Done").toInt(), 1);

    // The same crossed blocks must unwind when both loop kinds are in one frame.
    const QString nested = QStringLiteral(
        "#Visits = 0\n#Outer = 0\n%1\n#j = 0\n%2\n#Visits = #Visits + 1\n"
        "SWITCH #j\nCASE 1\nIF 1\nCONTINUE\nENDIF\nDEFAULT\nIF 1\nBREAK\nENDIF\n"
        "ENDSWITCH\n%3\n#Outer = #Outer + 1\n%4\n").arg(outerOpen, innerOpen, innerClose, outerClose);
    script.ExecuteGcode(nested, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Visits").toInt(), 6);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Outer").toInt(), 3);
}

void GScriptRuntimeTest::invalidExpressionsAndParametersFaultBeforeDevice_data()
{
    QTest::addColumn<QString>("statement");
    const auto row = [](const char* name, const char* source) {
        QTest::newRow(name) << QString::fromLatin1(source);
    };
    row("division-zero", "#X = 1 / 0");
    row("modulo-zero", "#X = 3 % 0");
    row("missing-operand", "#X = 1 +");
    row("malformed-literal", "#X = 1.2.3");
    row("overflow-literal", "#X = 1e999");
    row("overflow-product", "#X = 1e300 * 1e300");
    row("undefined-numeric", "#X = #Missing + 1");
    row("undefined-gcode-coordinate", "robot0 G01 X[#Missing]");
    row("undefined-inline-gcode-coordinate", "IF 1 THEN robot0 G01 X[#Missing]");
    row("invalid-root", "#X = #sqrt(-1)");
    row("invalid-log", "#X = #log(0)");
    row("builtin-arity", "#X = #atan2(1)");
    row("cloud-arity", "#X = #cloudPointAddCalibration(1)");
    row("function-unknown", "#X = #notAMathFunction(1)");
    row("invalid-timeout", "M98 Psend(device0, \"M42 P1\", #Reply, \"bad\")");
    row("overflow-timeout", "M98 Psend(device0, \"M42 P1\", #Reply, 1e40)");
    row("negative-delay", "M98 Pdelay(-1)");
    row("fractional-delay", "M98 Pdelay(0.5)");
    row("invalid-wait-condition", "M98 PwaitUntil(#Missing, 100, 5)");
    row("invalid-claim-zone", "M98 PclaimObject(0, #Target, \"r0\", 100, 0, 0, 100)");
    row("invalid-tracking-id", "M98 PcaptureAndDetect(-1)");
    row("zero-for-step", "FOR #i = 1 TO 2 STEP 0\nENDFOR");
    row("invalid-for-step", "FOR #i = 1 TO 2 STEP \"bad\"\nENDFOR");
    row("macro-arity", "M98 PaddObject()");
    row("empty-macro-argument", "M98 Psend(device0, \"M42 P1\", #Reply,)");
    row("missing-area-arguments", "#Area = #GetObjectInArea(0)");
    row("mismatched-area-axis", "#Area = #GetObjectInArea(0, X_MIN=0, Y_MAX=100)");
    row("invalid-area-number", "#Area = #GetObjectInArea(0, X_MIN=\"bad\", X_MAX=100)");
}

void GScriptRuntimeTest::invalidExpressionsAndParametersFaultBeforeDevice()
{
    QFETCH(QString, statement);
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "invalid_expression";
    QSignalSpy device(&script, &GcodeScript::SendGcodeToDevice);
    QSignalSpy capture(&script, &GcodeScript::CaptureAndDetectRequest);
    QSignalSpy claim(&script, &GcodeScript::ClaimObjectRequest);
    QSignalSpy area(&script, &GcodeScript::GetObjectsRequest);
    script.ExecuteGcode(statement + "\nrobot0 G01 X100\n#ShouldNotRun = 1\n", GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
    QCOMPARE(device.count(), 0);
    QCOMPARE(capture.count(), 0);
    QCOMPARE(claim.count(), 0);
    QCOMPARE(area.count(), 0);
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, "ShouldNotRun"));
    QVERIFY(!VariableManager::instance().getVarScoped(
        scope, "GScript.invalid_expression.LastError").toString().isEmpty());
}

void GScriptRuntimeTest::strictMathAndExpressionForRemainCompatible()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "strict_math";
    const QString source = QStringLiteral(
        "#Sum = 0\nFOR #i = 1 + 1 TO 2 * 3 STEP 1 + 1\n#Sum = #Sum + #i\nENDFOR\n"
        "M98 Passert(#Sum == 12)\nM98 Passert(2 ^ 3 ^ 2 == 512)\nM98 Passert(2 ^ -2 == 0.25)\n"
        "M98 Passert(1 OR 1 / 0)\nM98 Passert((0 AND 1 / 0) == 0)\n"
        "#Tag = \"THEN quoted text\"\nIF #Tag == \"THEN quoted text\"\n#Matched = 1\nENDIF\n"
        "#Literal = #UnknownName\n#Quoted = \"1 / 0\"\n");
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Literal").toString(), "UnknownName");
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Quoted").toString(), "1 / 0");
}

void GScriptRuntimeTest::runtimeFaultIncludesCallContext()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "fault_context";
    QSignalSpy diagnostics(&script, &GcodeScript::DiagnosticsReady);
    const QString source = QStringLiteral(
        "FUNCTION Fail()\nRETURN 1 / 0\nENDFUNCTION\n"
        "M98 P2000\nO2000\n#R = #Fail()\nM99\n");
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
    const QString error = VariableManager::instance().getVarScoped(
        scope, "GScript.fault_context.LastError").toString();
    QVERIFY2(error.contains("Line 2:"), qPrintable(error));
    QVERIFY2(error.contains("FAIL") && error.contains("P2000"), qPrintable(error));
    QCOMPARE(VariableManager::instance().getVarScoped(
        scope, "GScript.fault_context.Failure.Source").toString(), "RETURN 1 / 0");
    QVERIFY(!diagnostics.isEmpty());
    script.ExecuteGcode(QStringLiteral("#Clean = 1\n"), GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(
        scope, "GScript.fault_context.Failure.Line").toInt(), 0);
    QVERIFY(VariableManager::instance().getVarScoped(
        scope, "GScript.fault_context.Failure.CallStack").toStringList().isEmpty());
}

void GScriptRuntimeTest::correlatedTrackingRejectsStoppedRunResults()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "tracking_correlation";
    QList<quint64> requests;
    QSignalSpy hardware(&script, &GcodeScript::SendGcodeToDevice);
    connect(&script, &GcodeScript::ClaimObjectCorrelatedRequest, &script,
            [&requests](quint64 id, int, const QString&, const QString&,
                        float, float, float, float, int, int) { requests.append(id); });
    const QString source = QStringLiteral(
        "M98 PclaimObject(0, #Target, \"robot0\", 0, 100, 0, 100)\n#Done = 1\n");
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(requests.size(), 1);
    script.Stop();
    QCOMPARE(hardware.count(), 0);
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(requests.size(), 2);
    QVERIFY(requests[0] != requests[1]);
    const QVariantMap oldResult{{"Found", true}, {"UID", 100}};
    script.GetTrackingResponse(requests[0], "tracking0:robot0", "Claimed", oldResult);
    script.GetResponse("tracking0:robot0", "Claimed");
    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForDevice);
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, "Target.UID"));
    script.GetTrackingResponse(requests[1], "tracking0:robot0", "Claimed",
                               QVariantMap{{"Found", true}, {"UID", 200}});
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Target.UID").toInt(), 200);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Done").toInt(), 1);
    script.GetTrackingResponse(requests[0], "tracking0:robot0", "Claimed", oldResult);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Target.UID").toInt(), 200);
}

void GScriptRuntimeTest::synchronousProvidersCompleteWithoutReentryFault()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "synchronous_providers";
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&script](const QString& device, const QString&) { script.GetResponse(device, "ok"); });
    connect(&script, &GcodeScript::CaptureAndDetectRequest, &script,
            [&script](quint64 id, int tracking) {
        script.GetResponse(QString("vision%1").arg(tracking), QString("FrameReady:%1").arg(id));
    });
    connect(&script, &GcodeScript::UpdateTrackingCorrelatedRequest, &script,
            [&script](quint64 id, int tracking) {
        script.GetTrackingResponse(id, QString("tracking%1").arg(tracking), "ok", {});
    });
    connect(&script, &GcodeScript::ClaimObjectCorrelatedRequest, &script,
            [&script](quint64 id, int tracking, const QString&, const QString& owner,
                      float, float, float, float, int, int) {
        script.GetTrackingResponse(id, QString("tracking%1:%2").arg(tracking).arg(owner), "Claimed",
                                   QVariantMap{{"Found", true}, {"UID", 12}});
    });
    connect(&script, &GcodeScript::ReleaseObjectCorrelatedRequest, &script,
            [&script](quint64 id, int tracking, int, const QString& owner) {
        script.GetTrackingResponse(id, QString("tracking%1:%2").arg(tracking).arg(owner), "Released", {});
    });
    connect(&script, &GcodeScript::CompleteObjectCorrelatedRequest, &script,
            [&script](quint64 id, int tracking, int, const QString& owner) {
        script.GetTrackingResponse(id, QString("tracking%1:%2").arg(tracking).arg(owner), "Completed", {});
    });
    const QString source = QStringLiteral(
        "M98 Psend(device0, \"M42 P1\")\nM98 PcaptureAndDetect(0)\nM98 PupdateTracking(0)\n"
        "M98 PclaimObject(0, #Target, \"robot0\", 0, 100, 0, 100)\n"
        "M98 PreleaseObject(0, 12, \"robot0\")\nM98 PcompleteObject(0, 12, \"robot0\")\n"
        "M98 Pdelay(30)\n#Done = 1\n");
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForTimer);
    script.GetResponse("tracking0:robot0", "Completed"); // duplicate must not skip the timer
    script.GetResponse("device0", "I0 V1"); // unrelated reply must not mutate variables
    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForTimer);
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, "I0"));
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, "Done"));
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Done").toInt(), 1);
}

void GScriptRuntimeTest::parenthesizedZeroArgumentPrimitives()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "zero_arity";
    QSignalSpy pause(&script, &GcodeScript::PauseCamera);
    QSignalSpy capture(&script, &GcodeScript::CaptureCamera);
    QSignalSpy resume(&script, &GcodeScript::ResumeCamera);
    QSignalSpy remove(&script, &GcodeScript::DeleteObject);
    script.ExecuteGcode(QStringLiteral(
        "M98 PpauseCamera()\nM98 PcaptureCamera()\nM98 PresumeCamera()\n"
        "M98 PdeleteFirstObject()\nM98 PsyncConveyor()\nM98 PstopSyncConveyor()\n"), GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(pause.count(), 1);
    QCOMPARE(capture.count(), 1);
    QCOMPARE(resume.count(), 1);
    QCOMPARE(remove.count(), 1);
}

void GScriptRuntimeTest::correlatedAreaQueryRejectsStoppedRunSnapshot()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = "area_correlation";
    QList<quint64> requests;
    connect(&script, &GcodeScript::GetObjectsCorrelatedRequest, &script,
            [&requests](quint64 id, int, const QString&, float, float, bool) {
        requests.append(id);
    });
    const QString source = QStringLiteral("#Area = #GetObjectInArea(0, X_MIN=0, X_MAX=100)\n");
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(requests.size(), 1);
    script.Stop();
    VariableManager::instance().updateVarScoped(scope, "Area.Count", 999);
    VariableManager::instance().updateVarScoped(scope, "Area.4.UID", 444);
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(requests.size(), 2);
    const QVariantMap stale{{"Count", 1}, {"0.UID", 100}};
    script.GetTrackingResponse(requests[0], "tracking0", "Ok", stale);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Area.Count").toInt(), 999);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForDevice);
    const QVector<ObjectInfo> objects{ObjectInfo(200, 0, QVector3D(10, 20, 0), 1, 1, 0)};
    const QVariantMap current{{"Count", 1}, {"0.UID", 200}, {"__Objects", QVariant::fromValue(objects)}};
    script.GetTrackingResponse(requests[1], "tracking0", "Ok", current);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Area.Count").toInt(), 1);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Area.0.UID").toInt(), 200);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, "Area.0.X").toFloat(), 10.0f);
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, "Area.4.UID"));
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, "Area.__Objects"));
}

void GScriptRuntimeTest::inlineStatementsAdvanceExactlyOnce_data()
{
    QTest::addColumn<QString>("source");
    QTest::newRow("assignment") << QStringLiteral(
        "#X = 0\nIF 1 THEN #X = 1\n#Next = 2\n");
    QTest::newRow("false-if") << QStringLiteral(
        "#X = 1\nIF 0 THEN #X = 0\n#Next = 2\n");
    QTest::newRow("elif") << QStringLiteral(
        "IF 0\n#X = 0\nELIF 1 THEN #X = 1\n#Next = 2\nENDIF\n");
    QTest::newRow("else") << QStringLiteral(
        "IF 0\n#X = 0\nELSE #X = 1\n#Next = 2\nENDIF\n");
    QTest::newRow("delay") << QStringLiteral(
        "#X = 1\nIF 1 THEN M98 Pdelay(5)\n#Next = 2\n");
    QTest::newRow("device") << QStringLiteral(
        "#X = 1\nIF 1 THEN device0 M42 P1\n#Next = 2\n");
    QTest::newRow("function-return") << QStringLiteral(
        "FUNCTION Value()\nRETURN 1\nENDFUNCTION\n"
        "IF 1 THEN #X = #Value()\n#Next = 2\n");
    QTest::newRow("legacy-return") << QStringLiteral(
        "IF 1 THEN M98 P2000\n#Next = 2\nO2000\n#X = 1\nM99\n");
    QTest::newRow("lowercase-legacy-return") << QStringLiteral(
        "if 1 then m98 p2000\n#Next = 2\no2000\n#X = 1\nm99\n");
    QTest::newRow("unprefixed-legacy-return") << QStringLiteral(
        "IF 1 THEN M98 2000\n#Next = 2\nO2000\n#X = 1\nM99\n");
    QTest::newRow("macro-like-subprogram-name") << QStringLiteral(
        "IF 1 THEN M98 PsendTask\n#Next = 2\nOsendTask\n#X = 1\nM99\n");
}

void GScriptRuntimeTest::inlineStatementsAdvanceExactlyOnce()
{
    QFETCH(QString, source);
    QVERIFY(!GScriptAnalyzer::analyze(source).hasErrors());
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("inline_statement");
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&script](const QString& device, const QString&) {
        QTimer::singleShot(0, &script, [&script, device]() {
            script.GetResponse(device, QStringLiteral("ok"));
        });
    });
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("X")).toInt(), 1);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Next")).toInt(), 2);
}

void GScriptRuntimeTest::quotedPayloadsRemainLiteral()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("literal_payloads");
    QSignalSpy logs(&script, &GcodeScript::LogMessage);
    QString sent;
    connect(&script, &GcodeScript::SendGcodeToDevice, &script,
            [&script, &sent](const QString& device, const QString& command) {
        sent = command;
        QTimer::singleShot(0, &script, [&script, device]() {
            script.GetResponse(device, QStringLiteral("ok"));
        });
    });
    const QString source = QStringLiteral(
        "#Message = \"https://host/a+b  c[42]\"\n"
        "#Compact=\"unchanged / +  value[\"\n"
        "#Unmatched = 'literal[; text'\n"
        "M98 PlogMessage(\"[1+2]\")\n"
        "M98 Psend(device0, \"M42 P1; a/b+c  [42]\", #Reply, 1000)\n"
        "#Coordinate = [1 + 2]\n");
    QVERIFY(!GScriptAnalyzer::analyze(source).hasErrors());
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Message")).toString(),
             QStringLiteral("https://host/a+b  c[42]"));
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Unmatched")).toString(),
             QStringLiteral("literal[; text"));
    QCOMPARE(sent, QStringLiteral("M42 P1; a/b+c  [42]"));
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Compact")).toString(),
             QStringLiteral("unchanged / +  value["));
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Coordinate")).toInt(), 3);
    QVERIFY(std::any_of(logs.cbegin(), logs.cend(), [](const QList<QVariant>& event) {
        return event.first().toString() == QStringLiteral("[1+2]");
    }));
}

void GScriptRuntimeTest::bracketedWaitUntilReevaluatesCondition_data()
{
    QTest::addColumn<QString>("call");
    QTest::newRow("canonical") << QStringLiteral("M98 PwaitUntil");
    QTest::newRow("lowercase") << QStringLiteral("m98 pwaituntil");
    QTest::newRow("underscore-alias") << QStringLiteral("M98 Pwait_until");
    QTest::newRow("without-prefix") << QStringLiteral("M98 waitUntil");
}

void GScriptRuntimeTest::bracketedWaitUntilReevaluatesCondition()
{
    QFETCH(QString, call);
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("bracketed_wait");
    VariableManager::instance().updateVarScoped(scope, QStringLiteral("Ready"), 0);
    QTimer::singleShot(20, &script, [this]() {
        VariableManager::instance().updateVarScoped(scope, QStringLiteral("Ready"), 1);
    });
    const QString source = call + QStringLiteral("([#Ready == 1], 500, 5)\n#Done = 1\n");
    QVERIFY(!GScriptAnalyzer::analyze(source).hasErrors());
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForCondition);
    QCOMPARE(VariableManager::instance().getVarScoped(
                 scope, QStringLiteral("GScript.bracketed_wait.ActiveCondition")).toString(),
             QStringLiteral("[#Ready == 1]"));
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Done")).toInt(), 1);
}

void GScriptRuntimeTest::localLoopAllowsQueuedStopAndCleanRestart()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("local_loop");
    QSignalSpy finished(&script, &GcodeScript::ExecutionFinished);
    // Leave an old batch continuation queued, then restart in a timer wait.
    script.ExecuteGcode(QStringLiteral("LABEL LOOP\nJUMP LOOP\n"), GcodeScript::BEGIN);
    QVERIFY(script.IsRunning());
    script.Stop();
    script.ExecuteGcode(QStringLiteral("M98 Pdelay(30)\n#Restarted = 1\n"), GcodeScript::BEGIN);
    QTest::qWait(5);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForTimer);
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, QStringLiteral("Restarted")));
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(finished.count(), 2);

    bool stopped = false;
    QTimer::singleShot(15, &script, [&script, &stopped]() {
        script.Stop();
        stopped = true;
    });
    script.ExecuteGcode(QStringLiteral("#Counter = 0\nWHILE 1\n#Counter = #Counter + 1\nENDWHILE\n"),
                        GcodeScript::BEGIN);
    QTRY_VERIFY_WITH_TIMEOUT(stopped, 500);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::Idle);
    QVERIFY(VariableManager::instance().getVarScoped(scope, QStringLiteral("Counter")).toInt() > 0);
    QCOMPARE(finished.count(), 3);
}

void GScriptRuntimeTest::stoppedSubprogramDoesNotLeakReturnAddress()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("legacy_restart");
    script.ExecuteGcode(QStringLiteral(
        "M98 P2000\nO2000\nM98 Pdelay(1000)\nM99\n"), GcodeScript::BEGIN);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::WaitingForTimer);
    script.Stop();
    script.ExecuteGcode(QStringLiteral("M99\n#ShouldNotRun = 1\n"), GcodeScript::BEGIN);
    QCOMPARE(script.State(), GcodeScript::ExecutionState::Faulted);
    QVERIFY(VariableManager::instance().getVarScoped(
                scope, QStringLiteral("GScript.legacy_restart.LastError"))
                .toString().contains(QStringLiteral("no active subprogram")));
    QVERIFY(!VariableManager::instance().containsFullKeyScoped(scope, QStringLiteral("ShouldNotRun")));
}

void GScriptRuntimeTest::earlyFunctionReturnRestoresCallerBlocks()
{
    GcodeScript script;
    script.ProjectName = scope;
    script.ID = QStringLiteral("function_unwind");
    const QString source = QStringLiteral(
        "FUNCTION First()\nFOR #j = 1 TO 3\nWHILE 1\nIF 1\n"
        "SWITCH #j\nCASE 1\nRETURN #j\nENDSWITCH\nENDIF\nENDWHILE\n"
        "ENDFOR\nENDFUNCTION\n"
        "#Calls = 0\nFOR #i = 1 TO 2\nIF 1\nWHILE #Calls < #i\n"
        "SWITCH #i\nCASE 1\n#R = #First()\nDEFAULT\n#R = #First()\nENDSWITCH\n"
        "#Calls = #Calls + 1\nENDWHILE\nENDIF\nENDFOR\n");
    QVERIFY(!GScriptAnalyzer::analyze(source).hasErrors());
    script.ExecuteGcode(source, GcodeScript::BEGIN);
    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("Calls")).toInt(), 2);
    QCOMPARE(VariableManager::instance().getVarScoped(scope, QStringLiteral("R")).toInt(), 1);
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

    QTRY_COMPARE(script.State(), GcodeScript::ExecutionState::Completed);
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
    int primitiveCount = 0;
    for (const auto& primitive : GScriptSyntax::builtInPrimitives()) {
        const auto name = primitive.name;
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
