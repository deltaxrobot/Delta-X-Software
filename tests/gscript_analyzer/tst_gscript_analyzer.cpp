#include <QtTest>
#include <QDir>
#include <QFile>
#include <QScopeGuard>
#include <algorithm>

#include "GScriptAnalyzer.h"
#include "GScriptEditorSupport.h"
#include "GScriptSyntax.h"
#include "PluginExtensionRegistry.h"
#include "DeltaXGScriptProvider.h"

class AnalyzerPrimitiveProvider final : public QObject, public DeltaXGScriptProvider
{
public:
    QVariantList gscriptPrimitives() const override
    {
        return {QVariantMap{{"name", "probe"}, {"signature", "M98 Pprobe(value)"},
                            {"minArgs", 1}, {"maxArgs", 1}}};
    }
    bool executeGScriptPrimitive(const QString&, const QVariantList&, QVariant*, QString*) override
    {
        return true;
    }
};

class GScriptAnalyzerTest : public QObject
{
    Q_OBJECT

private slots:
    void acceptsStructuredTrackingProgram();
    void acceptsLegacyInlineIf();
    void acceptsPlainBlockConditionUsedByBundledScripts();
    void detectsUnclosedAndUnexpectedBlocks();
    void detectsDuplicateAndMissingTargets();
    void validatesTrackingCommandArity();
    void validatesDelayArity();
    void warnsAboutBypassingClaimProtocol();
    void ignoresDelimitersAndCommentsInsideStrings();
    void acceptsStructuredControlFlowAndDeviceApi();
    void rejectsInvalidControlFlowAndDeviceApi();
    void validatesM98TargetsAndExplicitDevices();
    void bundledProductionExamplesValidate();
    void editorSupportProvidesCompletionAndSignatureHelp();
    void editorSupportExtractsOnlyCodeVariables();
    void generatedTemplatesPassPreflight();
    void rejectsScopeCrossingTransfers_data();
    void rejectsScopeCrossingTransfers();
    void acceptsSameScopeTransfersAndLegacyCalls();
    void quotedCommandsAreData();
    void primitiveCatalogDrivesValidationAndEditor();
    void rejectsInlineInvalidCommandsAndFunctionLoopEscape();
    void pluginNameStartingWithPIsNormalizedOnce();
    void subprogramBoundaryIgnoresEarlyReturns();
    void earlyReturnDoesNotEndSubprogramJumpScope();
    void requiresFinalTopLevelSubprogramReturn();
};

void GScriptAnalyzerTest::acceptsStructuredTrackingProgram()
{
    const QString source = R"(
N10 SELECT robot0
N20 #Owner = "robot0"
N30 M98 PcaptureAndDetect(0)
N40 M98 PclaimObject(0, #Target, #Owner, 0, 300, -100, 100, -1, 5000)
N50 IF [#Target.Found == 1] THEN
N60   G01 X[#Target.X] Y[#Target.Y] Z-120 F500
N70   M98 PcompleteObject(0, #Target.UID, #Owner)
N80 ELSE
N90   M98 Pdelay(20)
N100 ENDIF
N110 GOTO 30
)";

    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(source);
    QVERIFY2(!result.hasErrors(), qPrintable(result.diagnostics.isEmpty()
        ? QString() : result.diagnostics.first().message));
    QCOMPARE(result.executableLineCount, 11);
}

void GScriptAnalyzerTest::acceptsLegacyInlineIf()
{
    const QString source = "N10 #Counter = 0\n"
                           "N20 #Counter = #Counter + 1\n"
                           "N30 IF [#Counter < 5] THEN GOTO 20\n";
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(source);
    QVERIFY(!result.hasErrors());
}

void GScriptAnalyzerTest::acceptsPlainBlockConditionUsedByBundledScripts()
{
    const QString source =
        "SELECT robot0\n"
        "LABEL LOOP\n"
        "M98 PclaimObject(0,#Target,robot0,-180,180,300,450,0,30000)\n"
        "IF #Target.Found == 1\n"
        "  M98 PcompleteObject(0,#Target.UID,robot0)\n"
        "ELIF #Target.Busy == 1 THEN\n"
        "  M98 Pdelay(20)\n"
        "ELSE\n"
        "  M98 Pdelay(10)\n"
        "ENDIF\n"
        "JUMP LOOP\n";
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(source);
    QVERIFY2(!result.hasErrors(), qPrintable(result.diagnostics.isEmpty()
        ? QString() : result.diagnostics.first().message));
}

void GScriptAnalyzerTest::detectsUnclosedAndUnexpectedBlocks()
{
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(
        "N10 ENDIF\nN20 FOR #i = 0 TO 3 STEP 1\nN30 G01 X#i\n");
    QVERIFY(result.hasErrors());
    QSet<QString> codes;
    for (const GScriptDiagnostic& diagnostic : result.diagnostics)
        codes.insert(diagnostic.code);
    QVERIFY(codes.contains("GS1205"));
    QVERIFY(codes.contains("GS1004"));
}

void GScriptAnalyzerTest::detectsDuplicateAndMissingTargets()
{
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(
        "N10 LABEL retry\nN20 LABEL retry\nN30 JUMP missing\nN40 GOTO 999\n");
    QSet<QString> codes;
    for (const GScriptDiagnostic& diagnostic : result.diagnostics)
        codes.insert(diagnostic.code);
    QVERIFY(codes.contains("GS1502"));
    QVERIFY(codes.contains("GS1504"));
    QVERIFY(codes.contains("GS1602"));
}

void GScriptAnalyzerTest::validatesTrackingCommandArity()
{
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(
        "N10 M98 PclaimObject(0, #Target)\n"
        "N20 M98 PcompleteObject(0, 12)\n");
    QCOMPARE(result.errorCount(), 2);
}

void GScriptAnalyzerTest::validatesDelayArity()
{
    const GScriptAnalysisResult invalid = GScriptAnalyzer::analyze(
        "M98 Pdelay()\nM98 Pdelay(10,20)\n");
    QCOMPARE(invalid.errorCount(), 2);

    const GScriptAnalysisResult valid = GScriptAnalyzer::analyze(
        "M98 Pdelay(#CycleDelay)\n");
    QVERIFY(!valid.hasErrors());
}

void GScriptAnalyzerTest::warnsAboutBypassingClaimProtocol()
{
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(
        "N10 #Objects.0.IsPicked = 1\n");
    QVERIFY(!result.hasErrors());
    QCOMPARE(result.warningCount(), 1);
    QCOMPARE(result.diagnostics.first().code, QString("GS2901"));
}

void GScriptAnalyzerTest::ignoresDelimitersAndCommentsInsideStrings()
{
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(
        "N10 #Message = \"text ; [ ( still text\" ; real comment ]\n");
    QVERIFY(!result.hasErrors());
}

void GScriptAnalyzerTest::acceptsStructuredControlFlowAndDeviceApi()
{
    const QString source =
        "FUNCTION classify(limit)\n"
        "  LOCAL #i = 0\n"
        "  WHILE #i < #limit\n"
        "    #i = #i + 1\n"
        "    CONTINUE\n"
        "  ENDWHILE\n"
        "  SWITCH #i\n"
        "    CASE 3\n"
        "      RETURN 1\n"
        "    DEFAULT\n"
        "      RETURN 0\n"
        "  ENDSWITCH\n"
        "ENDFUNCTION\n"
        "SELECT device0\n"
        "#SafeZ = -200\n"
        "#PickZ = -300\n"
        "M98 Psend(encoder0, \"M317\", #EncoderReply, 1000)\n"
        "M98 PwaitUntil(#Vacuum.OK == 1, 500, 10, \"Vacuum timeout\")\n"
        "M98 Passert(#SafeZ > #PickZ, \"Unsafe Z configuration\")\n";
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(source);
    QVERIFY2(!result.hasErrors(), qPrintable(result.diagnostics.isEmpty()
        ? QString() : result.diagnostics.first().message));
}

void GScriptAnalyzerTest::rejectsInvalidControlFlowAndDeviceApi()
{
    const QString source =
        "LOCAL #outside = 1\n"
        "BREAK\n"
        "WHILE\n"
        "ENDSWITCH\n"
        "M98 Psend(robot0)\n"
        "M98 PwaitUntil(#Ready)\n"
        "M98 Passert()\n";
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(source);
    QVERIFY(result.hasErrors());
    QSet<QString> codes;
    for (const GScriptDiagnostic& diagnostic : result.diagnostics)
        codes.insert(diagnostic.code);
    QVERIFY(codes.contains(QStringLiteral("GS1410")));
    QVERIFY(codes.contains(QStringLiteral("GS1312")));
    QVERIFY(codes.contains(QStringLiteral("GS1310")));
    QVERIFY(codes.contains(QStringLiteral("GS1326")));
    QVERIFY(codes.contains(QStringLiteral("GS1913")));
    QVERIFY(codes.contains(QStringLiteral("GS1916")));
    QVERIFY(codes.contains(QStringLiteral("GS1914")));
}

void GScriptAnalyzerTest::validatesM98TargetsAndExplicitDevices()
{
    const QString valid =
        "M98 P2000\n"
        "O2000\n"
        "M99\n"
        "robot0 G0 X0\n";
    QVERIFY(!GScriptAnalyzer::analyze(valid).hasErrors());

    const GScriptAnalysisResult invalid = GScriptAnalyzer::analyze(
        "M98 PcalimObject(0)\n"
        "robotX G0 X0\n");
    QSet<QString> codes;
    for (const GScriptDiagnostic& diagnostic : invalid.diagnostics)
        codes.insert(diagnostic.code);
    QVERIFY(codes.contains(QStringLiteral("GS1702")));
    QVERIFY(codes.contains(QStringLiteral("GS1802")));
}

void GScriptAnalyzerTest::bundledProductionExamplesValidate()
{
    const QString exampleRoot = QFINDTESTDATA(
        "../../script-example/multi-robot-sorting");
    QVERIFY2(!exampleRoot.isEmpty(), "Cannot locate bundled production examples");
    const QStringList files = {
        QStringLiteral("00-vision-tracking.gcode"),
        QStringLiteral("10-robot0-type0.gcode"),
        QStringLiteral("11-robot1-type1.gcode")
    };

    for (const QString& fileName : files) {
        QFile file(QDir(exampleRoot).filePath(fileName));
        QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text),
                 qPrintable(QString("Cannot open bundled example: %1").arg(file.fileName())));
        const GScriptAnalysisResult result =
            GScriptAnalyzer::analyze(QString::fromUtf8(file.readAll()));
        QVERIFY2(!result.hasErrors(),
                 qPrintable(QString("%1: %2")
                                .arg(fileName,
                                     result.diagnostics.isEmpty()
                                         ? QStringLiteral("unknown analysis error")
                                         : result.diagnostics.first().message)));
    }
}

void GScriptAnalyzerTest::editorSupportProvidesCompletionAndSignatureHelp()
{
    const QStringList completions = GScriptEditorSupport::builtInCompletions();
    QVERIFY(completions.contains(QStringLiteral("PwaitUntil")));
    QVERIFY(completions.contains(QStringLiteral("PclaimObject")));
    QVERIFY(completions.contains(QStringLiteral("robot0")));

    const QString line =
        QStringLiteral("M98 PwaitUntil(#Vacuum.OK == 1, 500, 10, \"timeout\")");
    const int thirdArgumentCursor = line.indexOf(QStringLiteral("10")) + 1;
    const QString help = GScriptEditorSupport::signatureHelp(line, thirdArgumentCursor);
    QVERIFY(help.contains(QStringLiteral("PwaitUntil")));
    QVERIFY(help.contains(QStringLiteral("parameter 3")));
    QVERIFY(GScriptEditorSupport::signatureHelp(line, line.size()).isEmpty());
}

void GScriptAnalyzerTest::editorSupportExtractsOnlyCodeVariables()
{
    const QString source =
        "#Real = #Tracking.0.State\n"
        "#Mapped = #0.ConveyorToRobot0\n"
        "M98 PlogMessage(\"#NotAWatch\")\n"
        "; #CommentOnly\n"
        "M98 PwaitUntil(#Vacuum.R0.OK == 1,500)\n";
    const QStringList variables = GScriptEditorSupport::referencedVariables(source);
    QVERIFY(variables.contains(QStringLiteral("Real")));
    QVERIFY(variables.contains(QStringLiteral("Tracking.0.State")));
    QVERIFY(variables.contains(QStringLiteral("0.ConveyorToRobot0")));
    QVERIFY(variables.contains(QStringLiteral("Vacuum.R0.OK")));
    QVERIFY(!variables.contains(QStringLiteral("NotAWatch")));
    QVERIFY(!variables.contains(QStringLiteral("CommentOnly")));
    QCOMPARE(GScriptEditorSupport::normalizeWatchName(" #Objects.0.X "),
             QStringLiteral("Objects.0.X"));
    QVERIFY(GScriptEditorSupport::normalizeWatchName("bad name").isEmpty());
}

void GScriptAnalyzerTest::generatedTemplatesPassPreflight()
{
    const QString vision = GScriptEditorSupport::visionTemplate(2, 15);
    QVERIFY2(!GScriptAnalyzer::analyze(vision).hasErrors(), qPrintable(vision));
    QVERIFY(vision.contains(QStringLiteral("PcaptureAndDetect(2)")));

    GScriptRobotTemplateOptions options;
    options.trackingId = 2;
    options.robotId = 3;
    options.typeFilter = 7;
    options.minX = 100;
    options.maxX = -100;
    options.useVacuumFeedback = true;
    options.vacuumVariable = QStringLiteral("Vacuum.R3.OK");
    const QString robot = GScriptEditorSupport::robotTemplate(options);
    const GScriptAnalysisResult result = GScriptAnalyzer::analyze(robot);
    QVERIFY2(!result.hasErrors(), qPrintable(result.diagnostics.isEmpty()
        ? robot : result.diagnostics.first().message + "\n" + robot));
    QVERIFY(robot.contains(QStringLiteral("SELECT robot3")));
    QVERIFY(robot.contains(QStringLiteral("PwaitUntil(#Vacuum.R3.OK")));
    QVERIFY(robot.contains(QStringLiteral("PclaimObject(2")));
    QVERIFY(robot.contains(QStringLiteral(",-100,100,")));
}

void GScriptAnalyzerTest::rejectsScopeCrossingTransfers_data()
{
    QTest::addColumn<QString>("source");
    QTest::newRow("enter-for") << QStringLiteral(
        "JUMP INNER\nFOR #i = 1 TO 2\nLABEL INNER\n#Count = 1\nENDFOR\n");
    QTest::newRow("leave-for") << QStringLiteral(
        "LABEL OUTER\nFOR #i = 1 TO 2\nJUMP OUTER\nENDFOR\n");
    QTest::newRow("inline-enter-while") << QStringLiteral(
        "IF 1 THEN JUMP INNER\nWHILE 1\nLABEL INNER\nBREAK\nENDWHILE\n");
    QTest::newRow("numbered-inline-enter-function") << QStringLiteral(
        "N10 IF 1 THEN GOTO 30\nN20 FUNCTION F()\nN30 RETURN 1\nN40 ENDFUNCTION\n");
    QTest::newRow("leave-function") << QStringLiteral(
        "LABEL MAIN\nFUNCTION F()\nJUMP MAIN\nENDFUNCTION\n");
    QTest::newRow("between-if-branches") << QStringLiteral(
        "IF 1\nJUMP OTHER\nELSE\nLABEL OTHER\nENDIF\n");
    QTest::newRow("between-switch-cases") << QStringLiteral(
        "SWITCH 1\nCASE 1\nJUMP OTHER\nCASE 2\nLABEL OTHER\nENDSWITCH\n");
    QTest::newRow("enter-legacy-subprogram") << QStringLiteral(
        "N10 GOTO 30\nN20 O2000\nN30 #X = 1\nN40 M99\n");
    QTest::newRow("leave-legacy-subprogram") << QStringLiteral(
        "LABEL MAIN\nM98 P2000\nO2000\nJUMP MAIN\nM99\n");
}

void GScriptAnalyzerTest::rejectsScopeCrossingTransfers()
{
    QFETCH(QString, source);
    const auto analysis = GScriptAnalyzer::analyze(source);
    QVERIFY(std::any_of(analysis.diagnostics.cbegin(), analysis.diagnostics.cend(),
                       [](const GScriptDiagnostic& value) { return value.code == "GS1603"; }));
}

void GScriptAnalyzerTest::acceptsSameScopeTransfersAndLegacyCalls()
{
    const QString source =
        "N10 LABEL OUTER\n"
        "N20 IF 1 THEN GOTO 10\n"
        "N30 M98 P2000\n"
        "N40 O2000\n"
        "N50 LABEL SUB_LOOP\n"
        "N60 IF 0 THEN JUMP SUB_LOOP\n"
        "N70 M99\n"
        "N80 FOR #i = 1 TO 2\n"
        "N90 LABEL SAME_LOOP\n"
        "N100 IF 0 THEN GOTO 90\n"
        "N110 ENDFOR\n"
        "N120 FUNCTION F()\n"
        "N130 LABEL SAME_FUNCTION\n"
        "N140 IF 0 THEN JUMP SAME_FUNCTION\n"
        "N150 RETURN 1\n"
        "N160 ENDFUNCTION\n"
        "N170 JUMP OUTER\n";
    const auto analysis = GScriptAnalyzer::analyze(source);
    for (const auto& diagnostic : analysis.diagnostics)
        QVERIFY2(diagnostic.severity != GScriptDiagnostic::Error, qPrintable(diagnostic.message));
}

void GScriptAnalyzerTest::quotedCommandsAreData()
{
    const QString source =
        "#Message = \"M98 Pdelay() M98 Psend() .IsPicked\"\n"
        "M98 PlogMessage(\"M98 PclaimObject()\")\n"
        "IF #Tag == \"THEN quoted text\"\n"
        "#Result = 1\n"
        "ENDIF\n";
    const auto analysis = GScriptAnalyzer::analyze(source);
    QVERIFY(!analysis.hasErrors());
    QCOMPARE(analysis.warningCount(), 0);
    const QString quoted = "#Message = \"M98 Pdelay(";
    QVERIFY(GScriptEditorSupport::signatureHelp(quoted, quoted.size()).isEmpty());
    const QString line = "M98 PlogMessage(\"M98 Psend(\"";
    const auto help = GScriptEditorSupport::signatureHelp(line, line.size());
    QVERIFY(help.contains("PlogMessage"));
    QVERIFY(!help.contains("Psend"));
}

void GScriptAnalyzerTest::primitiveCatalogDrivesValidationAndEditor()
{
    const auto completions = GScriptEditorSupport::builtInCompletions();
    for (const auto& primitive : GScriptSyntax::builtInPrimitives()) {
        QVERIFY(completions.contains(primitive.completion));
        QStringList arguments;
        for (int at = 0; at < primitive.minimumArguments; ++at) arguments.append("0");
        const QString valid = "M98 " + primitive.completion + "(" + arguments.join(',') + ")";
        const auto analysis = GScriptAnalyzer::analyze(valid);
        QVERIFY2(!analysis.hasErrors(), qPrintable(valid));
        const QString partial = "M98 " + primitive.completion + "(";
        QVERIFY2(GScriptEditorSupport::signatureHelp(partial, partial.size())
                     .startsWith(primitive.signature), qPrintable(partial));
        while (arguments.size() <= primitive.maximumArguments) arguments.append("0");
        const auto invalid = GScriptAnalyzer::analyze(
            "M98 " + primitive.completion + "(" + arguments.join(',') + ")");
        QVERIFY2(invalid.hasErrors(), qPrintable(primitive.name));
    }
    QVERIFY(GScriptAnalyzer::analyze("m98 p_wait_until(1)\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("M98 send(robot0,,)\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("M98 PupdateTracking0(1,2)\n").hasErrors());
    QVERIFY(!GScriptAnalyzer::analyze("M98 pauseCamera\nM98 PclearObjects LegacyList\n").hasErrors());
    QCOMPARE(GScriptSyntax::splitArguments("\"a,b\", [1 + 2], max(3, 4)").size(), 3);
}

void GScriptAnalyzerTest::rejectsInlineInvalidCommandsAndFunctionLoopEscape()
{
    QVERIFY(GScriptAnalyzer::analyze("IF 1 THEN JUMP MISSING\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("IF 1 THEN M98 Punknown()\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("IF 1 THEN M98 Psend(robot0)\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("IF 1 THEN SELECT robotX\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("IF 1 THEN robotX G0 X0\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("IF 1 THEN CONTINUE\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze(
        "FOR #i = 1 TO 2\nFUNCTION F()\nBREAK\nENDFUNCTION\nENDFOR\n").hasErrors());
}

void GScriptAnalyzerTest::pluginNameStartingWithPIsNormalizedOnce()
{
    AnalyzerPrimitiveProvider provider;
    auto& registry = PluginExtensionRegistry::instance();
    QString error;
    QVERIFY2(registry.registerGScriptProvider("analyzer-probe", &provider, &provider, &error),
             qPrintable(error));
    const auto cleanup = qScopeGuard([&]() { registry.unregisterPlugin("analyzer-probe"); });
    QVERIFY(!GScriptAnalyzer::analyze("IF 1 THEN M98 Pprobe(1)\n").hasErrors());
    QVERIFY(GScriptAnalyzer::analyze("M98 Pprobe()\n").hasErrors());
    const QString partial = "M98 Pprobe(";
    QVERIFY(GScriptEditorSupport::signatureHelp(partial, partial.size()).startsWith("M98 Pprobe(value)"));
}

void GScriptAnalyzerTest::subprogramBoundaryIgnoresEarlyReturns()
{
    const QString source =
        "M98 P2000\nO2000\nIF 1 THEN M99\nFOR #i = 1 TO 2\n"
        "WHILE 1\nIF 1\nSWITCH #i\nCASE 1\nM99\nENDSWITCH\nENDIF\n"
        "ENDWHILE\nENDFOR\nN100 M99 ; definition boundary\n#Done = 1\n";
    const QStringList lines = source.split('\n');
    QCOMPARE(GScriptSyntax::findSubprogramEnd(lines, 1), 13);
    const auto analysis = GScriptAnalyzer::analyze(source);
    for (const auto& diagnostic : analysis.diagnostics)
        QVERIFY2(diagnostic.severity != GScriptDiagnostic::Error, qPrintable(diagnostic.message));
}

void GScriptAnalyzerTest::earlyReturnDoesNotEndSubprogramJumpScope()
{
    const auto analysis = GScriptAnalyzer::analyze(
        "JUMP INSIDE\nO2000\nIF 1\nM99\nENDIF\nLABEL INSIDE\nM99\n");
    QVERIFY(std::any_of(analysis.diagnostics.cbegin(), analysis.diagnostics.cend(),
                       [](const GScriptDiagnostic& value) { return value.code == "GS1603"; }));
}

void GScriptAnalyzerTest::requiresFinalTopLevelSubprogramReturn()
{
    const auto analysis = GScriptAnalyzer::analyze(
        "M98 P2000\nO2000\nIF 1\nM99\nENDIF\n");
    QVERIFY(std::any_of(analysis.diagnostics.cbegin(), analysis.diagnostics.cend(),
                       [](const GScriptDiagnostic& value) { return value.code == "GS1704"; }));
    const auto nextDefinition = GScriptAnalyzer::analyze(
        "Omissing\n#X = 1\nOother\nM99\n");
    QVERIFY(std::any_of(nextDefinition.diagnostics.cbegin(), nextDefinition.diagnostics.cend(),
                       [](const GScriptDiagnostic& value) {
                           return value.code == "GS1704" && value.line == 1;
                       }));
    QCOMPARE(GScriptSyntax::findSubprogramEnd(
                 QStringLiteral("Omissing\n#X = 1\nOother\nM99\n").split('\n'), 0), -1);
}

QTEST_MAIN(GScriptAnalyzerTest)
#include "tst_gscript_analyzer.moc"
