#include <QtTest>

#include "BlockProgram.h"
#include "GScriptAnalyzer.h"

#include <QJsonArray>

#include <algorithm>

using namespace DeltaXBlockProgramming;

class BlockProgrammingTest : public QObject
{
    Q_OBJECT

private slots:
    void catalogHasUniqueDefinitionsAndDefaults();
    void templatesCompileToValidGScript();
    void serializationRoundTripsNestedPrograms();
    void rejectsInvalidDocumentsAndStructures();
    void validatesProcessValuesAndDeviceIdentifiers();
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
