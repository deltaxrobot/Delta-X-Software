#include "GScriptAnalyzer.h"
#include "GScriptSyntax.h"
#include "PluginExtensionRegistry.h"

#include <algorithm>
#include <QHash>
#include <QRegularExpression>
#include <QSet>
#include <QStack>

namespace {
struct BlockEntry {
    QString type;
    int line = 1;
    bool elseSeen = false;
};

struct Reference {
    QString kind;
    QString target;
    int line = 1;
    int column = 1;
};

QString stripInlineComment(const QString& input)
{
    return GScriptSyntax::stripComment(input);
}

QString statementWithoutLineNumber(const QString& input, int* lineNumber = nullptr)
{
    return GScriptSyntax::withoutLineNumber(input, lineNumber);
}

QString firstTokenUpper(const QString& statement)
{
    return GScriptSyntax::command(statement);
}

void addDiagnostic(GScriptAnalysisResult& result,
                   GScriptDiagnostic::Severity severity,
                   const QString& code, int line, int column,
                   const QString& message, const QString& hint = QString())
{
    GScriptDiagnostic diagnostic;
    diagnostic.severity = severity;
    diagnostic.code = code;
    diagnostic.line = qMax(1, line);
    diagnostic.column = qMax(1, column);
    diagnostic.message = message;
    diagnostic.hint = hint;
    result.diagnostics.append(diagnostic);
}

void validateDelimiters(const QString& statement, int line,
                        GScriptAnalysisResult& result)
{
    QStack<QPair<QChar, int>> stack;
    bool inSingleQuote = false;
    bool inDoubleQuote = false;
    for (int i = 0; i < statement.size(); ++i) {
        const QChar character = statement.at(i);
        if (character == '\'' && !inDoubleQuote) {
            inSingleQuote = !inSingleQuote;
            continue;
        }
        if (character == '"' && !inSingleQuote) {
            inDoubleQuote = !inDoubleQuote;
            continue;
        }
        if (inSingleQuote || inDoubleQuote)
            continue;
        if (character == '(' || character == '[') {
            stack.push({character, i + 1});
        } else if (character == ')' || character == ']') {
            const QChar expected = character == ')' ? '(' : '[';
            if (stack.isEmpty() || stack.top().first != expected) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1002",
                              line, i + 1, "Unmatched closing delimiter.",
                              "Check parentheses and square brackets on this line.");
                return;
            }
            stack.pop();
        }
    }
    if (inSingleQuote || inDoubleQuote) {
        addDiagnostic(result, GScriptDiagnostic::Error, "GS1003", line,
                      statement.size(), "Unterminated string literal.",
                      "Close the quoted text before the end of the line.");
    }
    if (!stack.isEmpty()) {
        addDiagnostic(result, GScriptDiagnostic::Error, "GS1001", line,
                      stack.top().second, "Unclosed delimiter.",
                      "Add the matching closing parenthesis or square bracket.");
    }
}

QString parseNamedTarget(const QString& statement, const QString& command)
{
    const QRegularExpression expression(
        QStringLiteral("^%1\\s+([#A-Za-z_][A-Za-z0-9_]*)")
            .arg(QRegularExpression::escape(command)),
        QRegularExpression::CaseInsensitiveOption);
    const QRegularExpressionMatch match = expression.match(statement);
    if (!match.hasMatch())
        return QString();
    QString target = match.captured(1);
    target.remove('#');
    return target.toUpper();
}

bool isBuiltInM98Target(const QString& rawTarget)
{
    // MacroCall already removed the optional P prefix exactly once.
    const QString target = rawTarget;
    if (GScriptSyntax::findPrimitive(target) ||
        PluginExtensionRegistry::instance().hasGScriptPrimitive(target))
        return true;

    // Backward-compatible spellings supported by the runtime.
    return QRegularExpression("^(updatetracking|captureanddetect)\\d+$")
               .match(target).hasMatch();
}

// Jumps may reuse an existing scope, but cannot manufacture or abandon frames.
// Legacy O/M99 sections form callable domains; M98 calls are not jumps.
void validateTransferScopes(const QStringList& lines, GScriptAnalysisResult& result)
{
    struct Scope { QString type; int line; int branch = 0; };
    QVector<Scope> scopes;
    QHash<int, QStringList> ancestry;
    QHash<int, int> numbered;
    QHash<QString, int> labels;
    QList<Reference> transfers;
    QString subprogram;
    int subprogramEnd = -1;
    for (int index = 0; index < lines.size(); ++index) {
        const int line = index + 1;
        int number = -1;
        const QString statement = GScriptSyntax::withoutLineNumber(
            GScriptSyntax::stripComment(lines.at(index)), &number);
        const QString cmd = GScriptSyntax::command(statement);
        if (statement.isEmpty()) continue;
        if (QRegularExpression("^O[A-Za-z0-9_]+$", QRegularExpression::CaseInsensitiveOption)
                .match(cmd).hasMatch()) {
            subprogram = QString("O:%1").arg(line);
            subprogramEnd = GScriptSyntax::findSubprogramEnd(lines, index);
        }
        if (!scopes.isEmpty() &&
            ((scopes.last().type == "IF" && (cmd == "ELIF" || cmd == "ELSE")) ||
             (scopes.last().type == "SWITCH" && (cmd == "CASE" || cmd == "DEFAULT"))))
            ++scopes.last().branch;
        QStringList current;
        if (!subprogram.isEmpty()) current.append(subprogram);
        for (const Scope& scope : scopes)
            current.append(QString("%1:%2:%3").arg(scope.type).arg(scope.line).arg(scope.branch));
        ancestry.insert(line, current);
        if (number >= 0) numbered.insert(number, line);
        if (cmd == "LABEL") labels.insert(parseNamedTarget(statement, "LABEL"), line);
        const QString executable = GScriptSyntax::effectiveStatement(statement);
        const QString transfer = GScriptSyntax::command(executable);
        if (transfer == "JUMP")
            transfers.append({"LABEL", parseNamedTarget(executable, "JUMP"), line, 1});
        else if (transfer == "GOTO") {
            const auto target = QRegularExpression("^GOTO\\s+(\\d+)\\b",
                                  QRegularExpression::CaseInsensitiveOption).match(executable);
            if (target.hasMatch()) transfers.append({"LINE", target.captured(1), line, 1});
        }
        if ((cmd == "IF" && GScriptSyntax::inlineStatement(statement).isEmpty()) ||
            cmd == "FOR" || cmd == "WHILE" || cmd == "SWITCH" || cmd == "FUNCTION")
            scopes.append({cmd, line});
        else if (cmd == "ENDIF" || cmd == "ENDFOR" || cmd == "ENDWHILE" ||
                 cmd == "ENDSWITCH" || cmd == "ENDFUNCTION") {
            if (!scopes.isEmpty()) scopes.removeLast();
        }
        if (index == subprogramEnd) {
            subprogram.clear();
            subprogramEnd = -1;
        }
    }
    for (const Reference& transfer : transfers) {
        const int target = transfer.kind == "LABEL" ? labels.value(transfer.target, -1)
                                                   : numbered.value(transfer.target.toInt(), -1);
        // Missing targets are diagnosed by the normal reference pass.
        if (target >= 0 && ancestry.value(transfer.line) != ancestry.value(target))
            addDiagnostic(result, GScriptDiagnostic::Error, "GS1603", transfer.line, transfer.column,
                          "Jump crosses a conditional, loop, function, or subprogram scope.",
                          "Keep JUMP/GOTO in the same block and branch; use BREAK, CONTINUE, RETURN, or M98 for structured transfers.");
    }
}
}

QString GScriptDiagnostic::severityName() const
{
    switch (severity) {
    case Error: return QStringLiteral("Error");
    case Warning: return QStringLiteral("Warning");
    default: return QStringLiteral("Info");
    }
}

bool GScriptAnalysisResult::hasErrors() const
{
    return errorCount() > 0;
}

int GScriptAnalysisResult::errorCount() const
{
    return std::count_if(diagnostics.cbegin(), diagnostics.cend(),
        [](const GScriptDiagnostic& diagnostic) {
            return diagnostic.severity == GScriptDiagnostic::Error;
        });
}

int GScriptAnalysisResult::warningCount() const
{
    return std::count_if(diagnostics.cbegin(), diagnostics.cend(),
        [](const GScriptDiagnostic& diagnostic) {
            return diagnostic.severity == GScriptDiagnostic::Warning;
        });
}

QStringList GScriptAnalyzer::knownKeywords()
{
    return {"IF", "THEN", "ELIF", "ELSE", "ENDIF", "FOR", "EACH", "IN",
            "TO", "STEP", "ENDFOR", "WHILE", "ENDWHILE", "BREAK", "CONTINUE",
            "SWITCH", "CASE", "DEFAULT", "ENDSWITCH", "FUNCTION", "ENDFUNCTION",
            "RETURN", "LOCAL", "LABEL", "JUMP", "GOTO", "SELECT", "SYNC",
            "M98", "M99"};
}

GScriptAnalysisResult GScriptAnalyzer::analyze(const QString& source)
{
    GScriptAnalysisResult result;
    const QString normalized = QString(source).replace("\r\n", "\n").replace('\r', '\n');
    const QStringList lines = normalized.split('\n');
    QHash<int, int> numberedLines;
    QHash<QString, int> labels;
    QHash<QString, int> functions;
    QHash<QString, int> subprograms;
    QList<Reference> references;
    QStack<BlockEntry> blocks;
    int previousProgramLine = -1;

    for (int index = 0; index < lines.size(); ++index) {
        const int sourceLine = index + 1;
        const QString uncommented = stripInlineComment(lines.at(index));
        int programLine = -1;
        const QString statement = statementWithoutLineNumber(uncommented, &programLine);
        if (statement.isEmpty())
            continue;
        ++result.executableLineCount;

        if (programLine >= 0) {
            if (numberedLines.contains(programLine)) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1101", sourceLine, 1,
                              QString("Duplicate program line N%1.").arg(programLine),
                              QString("N%1 was already used on source line %2.")
                                  .arg(programLine).arg(numberedLines.value(programLine)));
            } else {
                numberedLines.insert(programLine, sourceLine);
            }
            if (previousProgramLine >= 0 && programLine <= previousProgramLine) {
                addDiagnostic(result, GScriptDiagnostic::Warning, "GS2101", sourceLine, 1,
                              "Program line numbers are not increasing.",
                              "Use increasing N numbers to keep GOTO behavior predictable.");
            }
            previousProgramLine = programLine;
        }

        validateDelimiters(statement, sourceLine, result);
        const QString command = firstTokenUpper(statement);

        if (command == "IF") {
            const QRegularExpression conditionPattern(
                "^IF\\s+(.+?)(?:\\s+THEN(?:\\s+.*)?)?$",
                QRegularExpression::CaseInsensitiveOption);
            const QRegularExpressionMatch conditionMatch = conditionPattern.match(statement);
            if (!conditionMatch.hasMatch() || conditionMatch.captured(1).trimmed().isEmpty())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1201", sourceLine, 1,
                              "IF has no condition.",
                              "Use IF condition, IF [condition] THEN, or IF condition THEN statement.");
            const QString inlineStatement = GScriptSyntax::inlineStatement(statement);
            if (!inlineStatement.isEmpty()) {
                // The effective statement below validates inline transfers and macros.
            } else {
                blocks.push({"IF", sourceLine, false});
            }
        } else if (command == "ELIF" || command == "ELSE") {
            if (blocks.isEmpty() || blocks.top().type != "IF") {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1202", sourceLine, 1,
                              command + " is not inside an IF block.");
            } else if (command == "ELIF" &&
                       !QRegularExpression("^ELIF\\s+.+?(?:\\s+THEN(?:\\s+.*)?)?$",
                                           QRegularExpression::CaseInsensitiveOption)
                            .match(statement).hasMatch()) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1206", sourceLine, 1,
                              "ELIF has no condition.");
            } else if (command == "ELSE") {
                if (blocks.top().elseSeen)
                    addDiagnostic(result, GScriptDiagnostic::Error, "GS1203", sourceLine, 1,
                                  "An IF block can contain only one ELSE.");
                blocks.top().elseSeen = true;
            } else if (blocks.top().elseSeen) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1204", sourceLine, 1,
                              "ELIF cannot appear after ELSE.");
            }
        } else if (command == "ENDIF") {
            if (blocks.isEmpty() || blocks.top().type != "IF")
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1205", sourceLine, 1,
                              "ENDIF has no matching IF.");
            else
                blocks.pop();
        } else if (command == "FOR") {
            const bool numeric = statement.contains(
                QRegularExpression("\\bTO\\b", QRegularExpression::CaseInsensitiveOption));
            const bool each = statement.contains(
                QRegularExpression("\\bEACH\\b.*\\bIN\\b", QRegularExpression::CaseInsensitiveOption));
            if (!numeric && !each)
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1301", sourceLine, 1,
                              "FOR syntax is incomplete.",
                              "Use FOR #i = start TO end STEP step or FOR EACH #item IN #list.");
            blocks.push({"FOR", sourceLine, false});
        } else if (command == "ENDFOR") {
            if (blocks.isEmpty() || blocks.top().type != "FOR")
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1302", sourceLine, 1,
                              "ENDFOR has no matching FOR.");
            else
                blocks.pop();
        } else if (command == "WHILE") {
            if (!QRegularExpression("^WHILE\\s+.+$", QRegularExpression::CaseInsensitiveOption)
                     .match(statement).hasMatch())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1310", sourceLine, 1,
                              "WHILE has no condition.");
            blocks.push({"WHILE", sourceLine, false});
        } else if (command == "ENDWHILE") {
            if (blocks.isEmpty() || blocks.top().type != "WHILE")
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1311", sourceLine, 1,
                              "ENDWHILE has no matching WHILE.");
            else
                blocks.pop();
        } else if (command == "BREAK" || command == "CONTINUE") {
            bool insideLoop = false;
            for (auto block = blocks.crbegin(); block != blocks.crend(); ++block) {
                if (block->type == "FUNCTION") break;
                if (block->type == "FOR" || block->type == "WHILE") {
                    insideLoop = true;
                    break;
                }
            }
            if (!insideLoop)
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1312", sourceLine, 1,
                              command + " can only be used inside FOR or WHILE.");
        } else if (command == "SWITCH") {
            if (!QRegularExpression("^SWITCH\\s+.+$", QRegularExpression::CaseInsensitiveOption)
                     .match(statement).hasMatch())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1320", sourceLine, 1,
                              "SWITCH requires a value.");
            blocks.push({"SWITCH", sourceLine, false});
        } else if (command == "CASE") {
            if (blocks.isEmpty() || blocks.top().type != "SWITCH")
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1321", sourceLine, 1,
                              "CASE is not inside a SWITCH block.");
            else if (!QRegularExpression("^CASE\\s+.+?:?$", QRegularExpression::CaseInsensitiveOption)
                          .match(statement).hasMatch())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1322", sourceLine, 1,
                              "CASE requires a value.");
            else if (blocks.top().elseSeen)
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1323", sourceLine, 1,
                              "CASE cannot appear after DEFAULT.");
        } else if (command == "DEFAULT") {
            if (blocks.isEmpty() || blocks.top().type != "SWITCH")
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1324", sourceLine, 1,
                              "DEFAULT is not inside a SWITCH block.");
            else if (blocks.top().elseSeen)
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1325", sourceLine, 1,
                              "A SWITCH block can contain only one DEFAULT.");
            else
                blocks.top().elseSeen = true;
        } else if (command == "ENDSWITCH") {
            if (blocks.isEmpty() || blocks.top().type != "SWITCH")
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1326", sourceLine, 1,
                              "ENDSWITCH has no matching SWITCH.");
            else
                blocks.pop();
        } else if (command == "FUNCTION") {
            const QString name = parseNamedTarget(statement, "FUNCTION");
            if (name.isEmpty()) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1401", sourceLine, 1,
                              "FUNCTION requires a valid name.");
            } else if (functions.contains(name)) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1402", sourceLine, 1,
                              QString("Duplicate function '%1'.").arg(name),
                              QString("First declared on source line %1.").arg(functions.value(name)));
            } else {
                functions.insert(name, sourceLine);
            }
            if (std::any_of(blocks.cbegin(), blocks.cend(), [](const BlockEntry& block) {
                    return block.type == "FUNCTION";
                }))
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1403", sourceLine, 1,
                              "Nested FUNCTION definitions are not supported.");
            blocks.push({"FUNCTION", sourceLine, false});
        } else if (command == "ENDFUNCTION") {
            if (blocks.isEmpty() || blocks.top().type != "FUNCTION")
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1404", sourceLine, 1,
                              "ENDFUNCTION has no matching FUNCTION.");
            else
                blocks.pop();
        } else if (command == "LABEL") {
            const QString name = parseNamedTarget(statement, "LABEL");
            if (name.isEmpty()) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1501", sourceLine, 1,
                              "LABEL requires a valid name.");
            } else if (labels.contains(name)) {
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1502", sourceLine, 1,
                              QString("Duplicate label '%1'.").arg(name));
            } else {
                labels.insert(name, sourceLine);
            }
        } else if (command == "JUMP") {
            const QString target = parseNamedTarget(statement, "JUMP");
            if (target.isEmpty())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1503", sourceLine, 1,
                              "JUMP requires a label name.");
            else
                references.append({"LABEL", target, sourceLine,
                                   int(statement.indexOf(target) + 1)});
        } else if (command == "GOTO") {
            const QRegularExpression gotoPattern("^GOTO\\s+(\\d+)\\b",
                                                  QRegularExpression::CaseInsensitiveOption);
            const QRegularExpressionMatch match = gotoPattern.match(statement);
            if (!match.hasMatch())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1601", sourceLine, 1,
                              "GOTO requires a numeric N target.");
            else
                references.append({"LINE", match.captured(1), sourceLine,
                                   int(match.capturedStart(1) + 1)});
        } else if (command.startsWith('O') && command.size() > 1) {
            const QString name = command.mid(1).remove('_').toUpper();
            if (subprograms.contains(name))
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1701", sourceLine, 1,
                              QString("Duplicate subprogram O%1.").arg(name));
            else
                subprograms.insert(name, sourceLine);
            if (GScriptSyntax::findSubprogramEnd(lines, index) < 0)
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1704", sourceLine, 1,
                              "Subprogram definition has no final top-level M99.",
                              "Keep an unconditional M99 after all nested blocks; an early conditional M99 does not end the definition.");
        } else if (command == "SELECT") {
            const QRegularExpression devicePattern(
                "^SELECT\\s+(robot|conveyor|encoder|slider|device)\\d+\\b",
                QRegularExpression::CaseInsensitiveOption);
            if (!devicePattern.match(statement).hasMatch())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1801", sourceLine, 1,
                              "SELECT requires a concrete device such as robot0.");
        } else if (command == "LOCAL") {
            bool insideFunction = false;
            for (const BlockEntry& block : blocks) {
                if (block.type == "FUNCTION") {
                    insideFunction = true;
                    break;
                }
            }
            if (!insideFunction)
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1410", sourceLine, 1,
                              "LOCAL can only be declared inside FUNCTION.");
            if (!QRegularExpression("^LOCAL\\s+#[A-Za-z_][A-Za-z0-9_]*(?:\\s*=.*)?$",
                                    QRegularExpression::CaseInsensitiveOption)
                     .match(statement).hasMatch())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1411", sourceLine, 1,
                              "LOCAL requires a simple variable name.",
                              "Use LOCAL #name or LOCAL #name = expression.");
        }

        const QString executable = GScriptSyntax::effectiveStatement(statement);
        const QString executableCommand = GScriptSyntax::command(executable);
        if (executable != statement && executableCommand == "SELECT" &&
            !QRegularExpression("^SELECT\\s+(robot|conveyor|encoder|slider|device)\\d+\\b",
                                QRegularExpression::CaseInsensitiveOption).match(executable).hasMatch())
            addDiagnostic(result, GScriptDiagnostic::Error, "GS1801", sourceLine, 1,
                          "SELECT requires a concrete device such as robot0.");
        const QRegularExpression explicitDevicePrefix(
            "^(ROBOT|CONVEYOR|ENCODER|SLIDER|DEVICE)",
            QRegularExpression::CaseInsensitiveOption);
        const QRegularExpression explicitDeviceToken(
            "^(ROBOT|CONVEYOR|ENCODER|SLIDER|DEVICE)\\d+$",
            QRegularExpression::CaseInsensitiveOption);
        if (explicitDevicePrefix.match(executableCommand).hasMatch() &&
            !explicitDeviceToken.match(executableCommand).hasMatch()) {
            addDiagnostic(result, GScriptDiagnostic::Error, "GS1802", sourceLine, 1,
                          QString("Invalid device target '%1'.").arg(executableCommand),
                          "Use a concrete zero-based target such as robot0 or encoder1.");
        }

        if (executable != statement && executableCommand == "JUMP") {
            const QString target = parseNamedTarget(executable, "JUMP");
            if (target.isEmpty())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1503", sourceLine, 1,
                              "JUMP requires a label name.");
            else
                references.append({"LABEL", target, sourceLine, 1});
        } else if (executable != statement && executableCommand == "GOTO") {
            const auto target = QRegularExpression("^GOTO\\s+(\\d+)\\b",
                                    QRegularExpression::CaseInsensitiveOption).match(executable);
            if (target.hasMatch()) references.append({"LINE", target.captured(1), sourceLine, 1});
            else addDiagnostic(result, GScriptDiagnostic::Error, "GS1601", sourceLine, 1,
                               "GOTO requires a numeric N target.");
        } else if (executable != statement &&
                   (executableCommand == "BREAK" || executableCommand == "CONTINUE")) {
            bool insideLoop = false;
            for (auto block = blocks.crbegin(); block != blocks.crend(); ++block) {
                if (block->type == "FUNCTION") break;
                if (block->type == "FOR" || block->type == "WHILE") {
                    insideLoop = true;
                    break;
                }
            }
            if (!insideLoop)
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1312", sourceLine, 1,
                              executableCommand + " can only be used inside FOR or WHILE.");
        }
        const GScriptSyntax::MacroCall macro = GScriptSyntax::parseMacroCall(statement);
        if (macro.valid) {
            const QString target = macro.target;
            if (!isBuiltInM98Target(target)) {
                references.append({"SUBPROGRAM", target.toUpper(), sourceLine,
                                   1});
            }
        } else if (executableCommand == "M98") {
            addDiagnostic(result, GScriptDiagnostic::Error, "GS1703", sourceLine, 1,
                          "M98 requires a macro or subprogram target.",
                          "Use M98 Psend(...) or M98 P2000.");
        }

        if (statement.startsWith('#') && statement.contains('=')) {
            const QString rhs = statement.mid(statement.indexOf('=') + 1).trimmed();
            if (rhs.isEmpty())
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1901", sourceLine,
                              statement.indexOf('=') + 1, "Variable assignment has no value.");
            if (GScriptSyntax::maskStringsAndComments(statement).contains(".IsPicked", Qt::CaseInsensitive))
                addDiagnostic(result, GScriptDiagnostic::Warning, "GS2901", sourceLine, 1,
                              "Directly changing IsPicked bypasses ownership semantics.",
                              "Use M98 PcompleteObject(...) after a confirmed pick.");
        }

        if (macro.valid) {
            const int count = macro.arguments.size();
            if (const auto* primitive = GScriptSyntax::findPrimitive(macro.target)) {
                const bool legacy = !macro.parenthesized && primitive->legacyBare;
                const bool emptyArgument = std::any_of(macro.arguments.cbegin(), macro.arguments.cend(),
                                                       [](const QString& value) { return value.isEmpty(); });
                if (!legacy && (count < primitive->minimumArguments ||
                                count > primitive->maximumArguments || emptyArgument))
                    addDiagnostic(result, GScriptDiagnostic::Error, primitive->diagnosticCode,
                                  sourceLine, 1,
                                  QString("%1 expects %2 to %3 non-empty arguments; found %4.")
                                      .arg(primitive->name).arg(primitive->minimumArguments)
                                      .arg(primitive->maximumArguments).arg(count), primitive->signature);
            }
            for (const PluginGScriptPrimitive& primitive :
                 PluginExtensionRegistry::instance().gscriptPrimitives()) {
                if (primitive.name != macro.target)
                    continue;
                if (count < primitive.minimumArguments ||
                    count > primitive.maximumArguments) {
                    addDiagnostic(
                        result, GScriptDiagnostic::Error, "GS1920", sourceLine, 1,
                        QString("Plugin primitive %1 expects %2 to %3 arguments; found %4.")
                            .arg(primitive.name)
                            .arg(primitive.minimumArguments)
                            .arg(primitive.maximumArguments)
                            .arg(count),
                        primitive.signature);
                }
                break;
            }
        }
    }

    while (!blocks.isEmpty()) {
        const BlockEntry block = blocks.pop();
        const QString expected = block.type == "IF" ? "ENDIF"
                                : block.type == "FOR" ? "ENDFOR"
                                : block.type == "WHILE" ? "ENDWHILE"
                                : block.type == "SWITCH" ? "ENDSWITCH" : "ENDFUNCTION";
        addDiagnostic(result, GScriptDiagnostic::Error, "GS1004", block.line, 1,
                      QString("%1 block is not closed.").arg(block.type),
                      QString("Add %1 for the block opened here.").arg(expected));
    }

    for (const Reference& reference : references) {
        if (reference.kind == "LABEL" && !labels.contains(reference.target)) {
            addDiagnostic(result, GScriptDiagnostic::Error, "GS1504", reference.line,
                          reference.column,
                          QString("Undefined label '%1'.").arg(reference.target));
        } else if (reference.kind == "LINE") {
            const int target = reference.target.toInt();
            if (!numberedLines.contains(target))
                addDiagnostic(result, GScriptDiagnostic::Error, "GS1602", reference.line,
                              reference.column,
                              QString("GOTO target N%1 does not exist.").arg(target));
        } else if (reference.kind == "SUBPROGRAM" &&
                   !subprograms.contains(reference.target)) {
            addDiagnostic(result, GScriptDiagnostic::Error, "GS1702", reference.line,
                          reference.column,
                          QString("Undefined M98 macro or subprogram '%1'.")
                              .arg(reference.target),
                          "Check the built-in macro name or add a matching O subprogram.");
        }
    }

    validateTransferScopes(lines, result);
    result.functionCount = functions.size();
    result.labelCount = labels.size();
    if (result.executableLineCount == 0)
        addDiagnostic(result, GScriptDiagnostic::Warning, "GS2001", 1, 1,
                      "The program contains no executable lines.");

    std::stable_sort(result.diagnostics.begin(), result.diagnostics.end(),
        [](const GScriptDiagnostic& left, const GScriptDiagnostic& right) {
            if (left.line != right.line) return left.line < right.line;
            if (left.column != right.column) return left.column < right.column;
            return left.severity > right.severity;
        });
    return result;
}
