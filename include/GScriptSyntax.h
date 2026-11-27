#ifndef GSCRIPTSYNTAX_H
#define GSCRIPTSYNTAX_H

#include <QRegularExpression>
#include <QStringList>
#include <QVector>

// Shared lexical rules and immutable built-in contracts. No device or UI state.
namespace GScriptSyntax {
inline QString stripComment(const QString& input)
{
    QChar quote;
    for (int at = 0; at < input.size(); ++at) {
        const QChar ch = input.at(at);
        if (!quote.isNull()) {
            if (ch == quote) quote = QChar();
        } else if (ch == '\'' || ch == '"') {
            quote = ch;
        } else if (ch == ';') {
            return input.left(at);
        }
    }
    return input;
}

inline QString maskStringsAndComments(const QString& input)
{
    QString result = input;
    QChar quote;
    bool comment = false;
    for (int at = 0; at < input.size(); ++at) {
        const QChar ch = input.at(at);
        if (comment) {
            result[at] = ' ';
        } else if (!quote.isNull()) {
            result[at] = ' ';
            if (ch == quote) quote = QChar();
        } else if (ch == '\'' || ch == '"') {
            quote = ch;
            result[at] = ' ';
        } else if (ch == ';') {
            result[at] = ' ';
            comment = true;
        }
    }
    return result;
}

inline QString withoutLineNumber(const QString& input, int* number = nullptr)
{
    static const QRegularExpression pattern("^\\s*N(\\d+)\\b\\s*",
                                            QRegularExpression::CaseInsensitiveOption);
    const auto match = pattern.match(input);
    if (number) *number = match.hasMatch() ? match.captured(1).toInt() : -1;
    return (match.hasMatch() ? input.mid(match.capturedLength()) : input).trimmed();
}

inline QString command(const QString& statement)
{
    return withoutLineNumber(statement).section(QRegularExpression("\\s+"), 0, 0).toUpper();
}

inline QString inlineStatement(const QString& input)
{
    const QString statement = withoutLineNumber(stripComment(input));
    const QString first = command(statement);
    if (first == "ELSE") return statement.mid(4).trimmed();
    if (first != "IF" && first != "ELIF") return QString();
    const auto match = QRegularExpression("\\bTHEN\\b", QRegularExpression::CaseInsensitiveOption)
                           .match(maskStringsAndComments(statement));
    return match.hasMatch() ? statement.mid(match.capturedEnd()).trimmed() : QString();
}

inline QString effectiveStatement(const QString& input)
{
    QString result = withoutLineNumber(stripComment(input));
    // Inline IF nesting is finite because every suffix is shorter.
    for (;;) {
        const QString nested = inlineStatement(result);
        if (nested.isEmpty()) return result;
        result = nested;
    }
}

inline QStringList splitArguments(const QString& input)
{
    QStringList result;
    if (input.trimmed().isEmpty()) return result;
    const QString syntax = maskStringsAndComments(input);
    int depth = 0;
    int start = 0;
    for (int at = 0; at < syntax.size(); ++at) {
        const QChar ch = syntax.at(at);
        if (ch == '(' || ch == '[') ++depth;
        else if (ch == ')' || ch == ']') --depth;
        else if (ch == ',' && depth == 0) {
            result.append(input.mid(start, at - start).trimmed());
            start = at + 1;
        }
    }
    result.append(input.mid(start).trimmed());
    return result;
}

struct Primitive {
    QString name;
    QString completion;
    QString signature;
    QString diagnosticCode;
    int minimumArguments;
    int maximumArguments;
    bool legacyBare = false;
};

inline const QVector<Primitive>& builtInPrimitives()
{
    static const QVector<Primitive> values = {
        {"send", "Psend", "M98 Psend(deviceId, command[, responseVariable[, timeoutMs]])", "GS1913", 2, 4},
        {"sendgcode", "PsendGcode", "M98 PsendGcode(deviceId, command[, responseVariable[, timeoutMs]])", "GS1913", 2, 4},
        {"assert", "Passert", "M98 Passert(condition[, message])", "GS1914", 1, 2},
        {"waituntil", "PwaitUntil", "M98 PwaitUntil(condition, timeoutMs[, pollMs[, message]])", "GS1916", 2, 4},
        {"updatetracking", "PupdateTracking", "M98 PupdateTracking([trackingId])", "GS1915", 0, 1, true},
        {"captureanddetect", "PcaptureAndDetect", "M98 PcaptureAndDetect([trackingId])", "GS1915", 0, 1, true},
        {"claimobject", "PclaimObject", "M98 PclaimObject(trackingId, result, owner, minX, maxX, minY, maxY[, typeFilter[, leaseMs]])", "GS1910", 7, 9},
        {"releaseobject", "PreleaseObject", "M98 PreleaseObject(trackingId, uid, owner)", "GS1911", 3, 3},
        {"completeobject", "PcompleteObject", "M98 PcompleteObject(trackingId, uid, owner)", "GS1911", 3, 3},
        {"delay", "Pdelay", "M98 Pdelay(milliseconds)", "GS1912", 1, 1},
        {"addobject", "PaddObject", "M98 PaddObject(list, type, x, y, z, width, length, angle)", "GS1917", 8, 8},
        {"clearobjects", "PclearObjects", "M98 PclearObjects(list)", "GS1917", 1, 1, true},
        {"deletefirstobject", "PdeleteFirstObject", "M98 PdeleteFirstObject", "GS1917", 0, 0, true},
        {"deleteobject", "PdeleteObject", "M98 PdeleteObject(objectIndex)", "GS1917", 1, 1},
        {"pausecamera", "PpauseCamera", "M98 PpauseCamera", "GS1917", 0, 0, true},
        {"capturecamera", "PcaptureCamera", "M98 PcaptureCamera", "GS1917", 0, 0, true},
        {"resumecamera", "PresumeCamera", "M98 PresumeCamera", "GS1917", 0, 0, true},
        {"logmessage", "PlogMessage", "M98 PlogMessage(message)", "GS1917", 1, 1, true},
        {"syncconveyor", "PsyncConveyor", "M98 PsyncConveyor", "GS1917", 0, 0, true},
        {"stopsyncconveyor", "PstopSyncConveyor", "M98 PstopSyncConveyor", "GS1917", 0, 0, true}
    };
    return values;
}

inline const Primitive* findPrimitive(QString name)
{
    name.remove('_');
    name = name.toLower();
    const auto legacyTracking = QRegularExpression("^(updatetracking|captureanddetect)\\d+$")
                                    .match(name);
    if (legacyTracking.hasMatch()) name = legacyTracking.captured(1);
    for (const Primitive& primitive : builtInPrimitives())
        if (primitive.name == name) return &primitive;
    return nullptr;
}

inline QString normalizeMacroTarget(QString target)
{
    target.remove('_');
    target = target.toLower();
    // Preserve unprefixed pauseCamera while accepting PpauseCamera and aliases.
    if (!findPrimitive(target) && target.startsWith('p')) target.remove(0, 1);
    return target;
}

struct MacroCall {
    bool valid = false;
    bool parenthesized = false;
    QString target;
    QStringList arguments;
    int openParenthesis = -1;
};

inline MacroCall parseMacroCall(const QString& input)
{
    MacroCall result;
    const QString statement = effectiveStatement(input);
    static const QRegularExpression pattern("^M98\\s+([A-Za-z0-9_]+)\\s*",
                                            QRegularExpression::CaseInsensitiveOption);
    const auto match = pattern.match(maskStringsAndComments(statement));
    if (!match.hasMatch()) return result;
    result.valid = true;
    result.target = normalizeMacroTarget(match.captured(1));
    const QString tail = statement.mid(match.capturedEnd()).trimmed();
    result.parenthesized = tail.startsWith('(');
    if (result.parenthesized) {
        result.openParenthesis = statement.indexOf('(', match.capturedStart(1));
        const int close = statement.lastIndexOf(')');
        result.arguments = splitArguments(statement.mid(result.openParenthesis + 1,
                                          close - result.openParenthesis - 1));
    }
    return result;
}
} // namespace GScriptSyntax

#endif // GSCRIPTSYNTAX_H
