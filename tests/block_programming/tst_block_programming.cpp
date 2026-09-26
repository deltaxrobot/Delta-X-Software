#include <QtTest>

#include "BlockProgram.h"
#include "GScriptAnalyzer.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include <algorithm>

using namespace DeltaXBlockProgramming;

class BlockProgrammingTest : public QObject
{
    Q_OBJECT

private slots:
    void catalogHasUniqueDefinitionsAndDefaults();
    void templatesCompileToValidGScript();
    void softwareSelfTestFixtureMatchesTemplate();
    void robotMotionFixtureCompiles();
    void robotCycleFixtureCompiles();
    void serializationRoundTripsNestedPrograms();
    void rejectsInvalidDocumentsAndStructures();
    void validatesProcessValuesAndDeviceIdentifiers();
    void emitsOnlyRuntimeCompatibleTextLiterals();
    void rawBlocksRequireReview();
};

void BlockProgrammingTest::catalogHasUniqueDefinitionsAndDefaults()
{
    const QVector<BlockDefinition> definitions = BlockProgram::definitions();
    QVERIFY(definitions.size() >= 20);
    QSet<QString> ids;
    for (const BlockDefinition& definition : definitions) {
        QVERIFY(!definition.id.isEmpty());
        QVERIFY(!definition.label.isEmpty());
        QVERIFY(!definition.category.isEmpty());
        QVERIFY(!ids.contains(definition.id));
        ids.insert(definition.id);
        const QVariantMap defaults = BlockProgram::defaultFields(definition.id);
        QCOMPARE(defaults.size(), definition.fields.size());
    }
}

void BlockProgrammingTest::templatesCompileToValidGScript()
{
    for (const QString& name : BlockProgram::templateNames()) {
        if (name == QStringLiteral("Empty"))
            continue;
        const CompileResult compiled = BlockProgram::compile(
            BlockProgram::createTemplate(name));
        QVERIFY2(!compiled.hasErrors(), qPrintable(name));
        if (name == QStringLiteral("Robot conveyor pick worker")) {
            QVERIFY(compiled.script.contains(QStringLiteral("X[#Target.X]")));
            QVERIFY(!compiled.script.contains(QStringLiteral("X#Target.X")));
        }
        const GScriptAnalysisResult analysis =
            GScriptAnalyzer::analyze(compiled.script);
        if (analysis.hasErrors()) {
            QStringList messages;
            for (const GScriptDiagnostic& diagnostic : analysis.diagnostics) {
                if (diagnostic.severity == GScriptDiagnostic::Error)
                    messages.append(QStringLiteral("%1: %2")
                                        .arg(diagnostic.code, diagnostic.message));
            }
            QFAIL(qPrintable(name + QStringLiteral("\n") + compiled.script +
                             messages.join(QLatin1Char('\n'))));
        }
    }
}

void BlockProgrammingTest::softwareSelfTestFixtureMatchesTemplate()
{
    const QString fixtureRoot = QFINDTESTDATA("../../script-example/block-programming");
    QVERIFY(!fixtureRoot.isEmpty());
    QFile documentFile(fixtureRoot + QStringLiteral("/Software Self Test.dxblocks"));
    QVERIFY(documentFile.open(QIODevice::ReadOnly));
    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(documentFile.readAll(), &parseError);
    QCOMPARE(parseError.error, QJsonParseError::NoError);
    QVERIFY(document.isObject());
    QVector<BlockNode> blocks;
    QString error;
    QVERIFY2(BlockProgram::fromJson(document.object(), &blocks, &error), qPrintable(error));
    QCOMPARE(BlockProgram::toJson(blocks),
             BlockProgram::toJson(BlockProgram::createTemplate(
                 QStringLiteral("Software self-test"))));
    const CompileResult compiled = BlockProgram::compile(blocks);
    QVERIFY(!compiled.hasErrors());
    QFile scriptFile(fixtureRoot + QStringLiteral("/Software Self Test.gcode"));
    QVERIFY(scriptFile.open(QIODevice::ReadOnly));
    QCOMPARE(compiled.script, QString::fromUtf8(scriptFile.readAll()));
    QVERIFY(!GScriptAnalyzer::analyze(compiled.script).hasErrors());
}

void BlockProgrammingTest::robotMotionFixtureCompiles()
{
    const QString fixtureRoot = QFINDTESTDATA("../../script-example/block-programming");
    QVERIFY(!fixtureRoot.isEmpty());
    QFile documentFile(fixtureRoot + QStringLiteral("/Robot 10mm Z Test.dxblocks"));
    QVERIFY(documentFile.open(QIODevice::ReadOnly));
    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(documentFile.readAll(), &parseError);
    QCOMPARE(parseError.error, QJsonParseError::NoError);
    QVector<BlockNode> blocks;
    QString error;
    QVERIFY2(BlockProgram::fromJson(document.object(), &blocks, &error), qPrintable(error));
    const CompileResult compiled = BlockProgram::compile(blocks);
    QVERIFY2(!compiled.hasErrors(), qPrintable(error));
    QFile scriptFile(fixtureRoot + QStringLiteral("/Robot 10mm Z Test.gcode"));
    QVERIFY(scriptFile.open(QIODevice::ReadOnly));
    QCOMPARE(compiled.script, QString::fromUtf8(scriptFile.readAll()));
    QVERIFY(compiled.script.contains(QStringLiteral("Z[#Motion.Start.Z - 10]")));
    QVERIFY(!GScriptAnalyzer::analyze(compiled.script).hasErrors());
}

void BlockProgrammingTest::robotCycleFixtureCompiles()
{
    const QString fixtureRoot = QFINDTESTDATA("../../script-example/block-programming");
    QVERIFY(!fixtureRoot.isEmpty());
    QFile documentFile(fixtureRoot + QStringLiteral("/Delta X 50 Cycle Example.dxblocks"));
    QVERIFY(documentFile.open(QIODevice::ReadOnly));
    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(documentFile.readAll(), &parseError);
    QCOMPARE(parseError.error, QJsonParseError::NoError);
    QVector<BlockNode> blocks;
    QString error;
    QVERIFY2(BlockProgram::fromJson(document.object(), &blocks, &error), qPrintable(error));
    const CompileResult compiled = BlockProgram::compile(blocks);
    QVERIFY2(!compiled.hasErrors(), qPrintable(error));
    QFile scriptFile(fixtureRoot + QStringLiteral("/Delta X 50 Cycle Example.gcode"));
    QVERIFY(scriptFile.open(QIODevice::ReadOnly));
    QCOMPARE(compiled.script, QString::fromUtf8(scriptFile.readAll()));
    QVERIFY(compiled.script.contains(QStringLiteral("FOR #BlockLoop1 = 1 TO 50 STEP 1")));
    QVERIFY(compiled.script.contains(QStringLiteral("F[2000] A[20000]")));
    QVERIFY(!GScriptAnalyzer::analyze(compiled.script).hasErrors());
}

void BlockProgrammingTest::serializationRoundTripsNestedPrograms()
{
    const QVector<BlockNode> original = BlockProgram::createTemplate(
        QStringLiteral("Robot conveyor pick worker"));
    const QJsonObject document = BlockProgram::toJson(original);
    QCOMPARE(document.value(QStringLiteral("format")).toString(),
             QStringLiteral("deltax-block-program"));

    QVector<BlockNode> parsed;
    QString error;
    QVERIFY(BlockProgram::fromJson(document, &parsed, &error));
    QCOMPARE(parsed.size(), original.size());
    QCOMPARE(BlockProgram::toJson(parsed), document);
    QCOMPARE(BlockProgram::compile(parsed).script,
             BlockProgram::compile(original).script);
}

void BlockProgrammingTest::rejectsInvalidDocumentsAndStructures()
{
    QVector<BlockNode> parsed;
    QString error;
    QVERIFY(!BlockProgram::fromJson(
        {{QStringLiteral("format"), QStringLiteral("other")},
         {QStringLiteral("version"), 1},
         {QStringLiteral("blocks"), QJsonArray{}}},
        &parsed, &error));
    QVERIFY(error.contains(QStringLiteral("unsupported")));

    QVERIFY(!BlockProgram::fromJson(
        {{QStringLiteral("format"), QStringLiteral("deltax-block-program")},
         {QStringLiteral("version"), 1},
         {QStringLiteral("blocks"),
          QJsonArray{QJsonObject{{QStringLiteral("type"),
                                  QStringLiteral("delay")}}}}},
        &parsed, &error));
    QVERIFY(error.contains(QStringLiteral("type, fields and children")));

    const CompileResult orphanElse = BlockProgram::compile({
        {QStringLiteral("else"), {},
         {{QStringLiteral("delay"), {{QStringLiteral("milliseconds"), 1}}, {}}}},
    });
    QVERIFY(orphanElse.hasErrors());
    QVERIFY(std::any_of(orphanElse.diagnostics.cbegin(),
                        orphanElse.diagnostics.cend(),
                        [](const BlockDiagnostic& diagnostic) {
        return diagnostic.code == QStringLiteral("BP1103");
    }));

    const CompileResult childOnLeaf = BlockProgram::compile({
        {QStringLiteral("delay"), {{QStringLiteral("milliseconds"), 1}},
         {{QStringLiteral("comment"), {{QStringLiteral("text"), "bad"}}, {}}}},
    });
    QVERIFY(childOnLeaf.hasErrors());
}

void BlockProgrammingTest::validatesProcessValuesAndDeviceIdentifiers()
{
    const CompileResult result = BlockProgram::compile({
        {QStringLiteral("delay"),
         {{QStringLiteral("milliseconds"), -1}}, {}},
        {QStringLiteral("move"),
         {{QStringLiteral("robot"), QStringLiteral("bad target")},
          {QStringLiteral("x"), QStringLiteral("0")},
          {QStringLiteral("y"), QStringLiteral("0")},
          {QStringLiteral("z"), QStringLiteral("-300")},
          {QStringLiteral("w"), QStringLiteral("0")},
          {QStringLiteral("speed"), QStringLiteral("500")},
          {QStringLiteral("acceleration"), QStringLiteral("1000")}}, {}},
    });
    QVERIFY(result.hasErrors());
    QVERIFY(std::any_of(result.diagnostics.cbegin(), result.diagnostics.cend(),
                        [](const BlockDiagnostic& diagnostic) {
        return diagnostic.code == QStringLiteral("BP1107");
    }));
    QVERIFY(std::any_of(result.diagnostics.cbegin(), result.diagnostics.cend(),
                        [](const BlockDiagnostic& diagnostic) {
        return diagnostic.code == QStringLiteral("BP1108");
    }));
}

void BlockProgrammingTest::emitsOnlyRuntimeCompatibleTextLiterals()
{
    const CompileResult compatible = BlockProgram::compile({
        {QStringLiteral("log"),
         {{QStringLiteral("message"),
           QStringLiteral("C:\\cell\\job \"A,B\"")}}, {}},
    });
    QVERIFY(!compatible.hasErrors());
    QVERIFY(compatible.script.contains(
        QStringLiteral("PlogMessage('C:\\cell\\job \"A,B\"')")));
    QVERIFY(!GScriptAnalyzer::analyze(compatible.script).hasErrors());

    const CompileResult unsupported = BlockProgram::compile({
        {QStringLiteral("assert"),
         {{QStringLiteral("condition"), QStringLiteral("0")},
          {QStringLiteral("message"),
           QStringLiteral("Robot's \"home\" check failed")}}, {}},
    });
    QVERIFY(unsupported.hasErrors());
    QVERIFY(std::any_of(unsupported.diagnostics.cbegin(),
                        unsupported.diagnostics.cend(),
                        [](const BlockDiagnostic& diagnostic) {
        return diagnostic.code == QStringLiteral("BP1109");
    }));
}

void BlockProgrammingTest::rawBlocksRequireReview()
{
    const CompileResult result = BlockProgram::compile({
        {QStringLiteral("raw"),
         {{QStringLiteral("code"), QStringLiteral("robot0 G28")}}, {}},
    });
    QVERIFY(!result.hasErrors());
    QVERIFY(std::any_of(result.diagnostics.cbegin(), result.diagnostics.cend(),
                        [](const BlockDiagnostic& diagnostic) {
        return diagnostic.code == QStringLiteral("BP1202") &&
               diagnostic.severity == BlockDiagnostic::Severity::Warning;
    }));
}

QTEST_MAIN(BlockProgrammingTest)
#include "tst_block_programming.moc"
