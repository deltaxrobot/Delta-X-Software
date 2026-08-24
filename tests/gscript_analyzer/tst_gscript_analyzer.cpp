#include <QtTest>
#include <QDir>
#include <QFile>

#include "GScriptAnalyzer.h"
#include "GScriptEditorSupport.h"

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

QTEST_MAIN(GScriptAnalyzerTest)
#include "tst_gscript_analyzer.moc"
