#include "GScriptEditorSupport.h"
#include "PluginExtensionRegistry.h"

#include <QHash>
#include <QRegularExpression>
#include <QSet>

namespace {
QString uncommentedLine(const QString& line)
{
    bool singleQuoted = false;
    bool doubleQuoted = false;
    for (int i = 0; i < line.size(); ++i) {
        const QChar c = line.at(i);
        if (c == '\'' && !doubleQuoted)
            singleQuoted = !singleQuoted;
        else if (c == '"' && !singleQuoted)
            doubleQuoted = !doubleQuoted;
        else if (c == ';' && !singleQuoted && !doubleQuoted)
            return line.left(i);
    }
    return line;
}

QString codeWithoutStringsOrComment(const QString& line)
{
    QString result;
    result.reserve(line.size());
    bool singleQuoted = false;
    bool doubleQuoted = false;
    for (int i = 0; i < line.size(); ++i) {
        const QChar c = line.at(i);
        if (c == '\'' && !doubleQuoted) {
            singleQuoted = !singleQuoted;
            result.append(' ');
        } else if (c == '"' && !singleQuoted) {
            doubleQuoted = !doubleQuoted;
            result.append(' ');
        } else if (c == ';' && !singleQuoted && !doubleQuoted) {
            break;
        } else {
            result.append(singleQuoted || doubleQuoted ? QChar(' ') : c);
        }
    }
    return result;
}

int activeArgument(const QString& text, int openParenthesis)
{
    int argument = 1;
    int depth = 0;
    bool singleQuoted = false;
    bool doubleQuoted = false;
    for (int i = openParenthesis + 1; i < text.size(); ++i) {
        const QChar c = text.at(i);
        if (c == '\'' && !doubleQuoted) {
            singleQuoted = !singleQuoted;
            continue;
        }
        if (c == '"' && !singleQuoted) {
            doubleQuoted = !doubleQuoted;
            continue;
        }
        if (singleQuoted || doubleQuoted)
            continue;
        if (c == '(' || c == '[')
            ++depth;
        else if (c == ')' || c == ']') {
            if (depth == 0)
                return -1;
            --depth;
        } else if (c == ',' && depth == 0) {
            ++argument;
        }
    }
    return argument;
}

QString number(double value)
{
    return QString::number(value, 'f', 3).remove(QRegularExpression("\\.?0+$"));
}
}

QStringList GScriptEditorSupport::builtInCompletions()
{
    QStringList result = {
        "SELECT", "LOCAL", "FUNCTION", "ENDFUNCTION", "RETURN",
        "IF", "ELIF", "ELSE", "ENDIF", "THEN", "FOR", "TO", "STEP",
        "ENDFOR", "WHILE", "ENDWHILE", "SWITCH", "CASE", "DEFAULT",
        "ENDSWITCH", "BREAK", "CONTINUE", "LABEL", "JUMP", "GOTO",
        "SYNC", "G00", "G01", "G04", "G28", "M03", "M05", "M42",
        "M84", "M85", "M98", "M204", "M311", "M317",
        "Psend", "Passert", "PwaitUntil", "PupdateTracking",
        "PcaptureAndDetect", "PclaimObject", "PreleaseObject",
        "PcompleteObject", "Pdelay", "PaddObject", "PclearObjects",
        "PdeleteFirstObject", "PdeleteObject", "PpauseCamera",
        "PcaptureCamera", "PresumeCamera", "PlogMessage",
        "PsyncConveyor", "PstopSyncConveyor", "PsendGcode"
    };
    for (int i = 0; i < 8; ++i) {
        result << QString("robot%1").arg(i)
               << QString("conveyor%1").arg(i)
               << QString("encoder%1").arg(i)
               << QString("slider%1").arg(i)
               << QString("device%1").arg(i)
               << QString("tracking%1").arg(i);
    }
    for (const PluginGScriptPrimitive& primitive :
         PluginExtensionRegistry::instance().gscriptPrimitives()) {
        result << QStringLiteral("P") + primitive.name;
    }
    result.removeDuplicates();
    result.sort(Qt::CaseInsensitive);
    return result;
}

QString GScriptEditorSupport::signatureHelp(const QString& line, int cursorColumn)
{
    const QString beforeCursor = uncommentedLine(line.left(qBound(0, cursorColumn, line.size())));
    static const QRegularExpression callPattern(
        QStringLiteral("M98\\s+P([A-Za-z_][A-Za-z0-9_]*)\\s*\\("),
        QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch selected;
    auto matches = callPattern.globalMatch(beforeCursor);
    while (matches.hasNext())
        selected = matches.next();
    if (!selected.hasMatch())
        return QString();

    const int openParenthesis = selected.capturedEnd() - 1;
    const int argument = activeArgument(beforeCursor, openParenthesis);
    if (argument < 1)
        return QString();

    static const QHash<QString, QString> signatures = {
        {"send", "M98 Psend(deviceId, command[, responseVariable[, timeoutMs]])"},
        {"assert", "M98 Passert(condition[, message])"},
        {"waituntil", "M98 PwaitUntil(condition, timeoutMs[, pollMs[, message]])"},
        {"updatetracking", "M98 PupdateTracking([trackingId])"},
        {"captureanddetect", "M98 PcaptureAndDetect([trackingId])"},
        {"claimobject", "M98 PclaimObject(trackingId, result, owner, minX, maxX, minY, maxY, typeFilter, leaseMs)"},
        {"releaseobject", "M98 PreleaseObject(trackingId, uid, owner)"},
        {"completeobject", "M98 PcompleteObject(trackingId, uid, owner)"},
        {"delay", "M98 Pdelay(milliseconds)"},
        {"addobject", "M98 PaddObject(list, type, x, y, z, width, length, angle)"},
        {"clearobjects", "M98 PclearObjects(list)"},
        {"logmessage", "M98 PlogMessage(message)"},
        {"syncconveyor", "M98 PsyncConveyor(robotId, vector)"},
        {"stopsyncconveyor", "M98 PstopSyncConveyor(robotId)"}
    };
    const QString signature = signatures.value(selected.captured(1).toLower());
    if (signature.isEmpty()) {
        const QString dynamicName = selected.captured(1).toLower();
        for (const PluginGScriptPrimitive& primitive :
             PluginExtensionRegistry::instance().gscriptPrimitives()) {
            if (primitive.name == dynamicName)
                return QStringLiteral("%1 - parameter %2")
                    .arg(primitive.signature)
                    .arg(argument);
        }
        return QString();
    }
    return QStringLiteral("%1  •  parameter %2").arg(signature).arg(argument);
}

QStringList GScriptEditorSupport::referencedVariables(const QString& source)
{
    static const QRegularExpression variablePattern(
        QStringLiteral("#([A-Za-z0-9_][A-Za-z0-9_.]*)"));
    QSet<QString> unique;
    const QStringList lines = source.split('\n');
    for (const QString& rawLine : lines) {
        auto matches = variablePattern.globalMatch(codeWithoutStringsOrComment(rawLine));
        while (matches.hasNext()) {
            const QString name = normalizeWatchName(matches.next().captured(1));
            if (!name.isEmpty())
                unique.insert(name);
        }
    }
    QStringList result = unique.values();
    result.sort(Qt::CaseInsensitive);
    return result;
}

QString GScriptEditorSupport::normalizeWatchName(const QString& name)
{
    QString result = name.trimmed();
    while (result.startsWith('#'))
        result.remove(0, 1);
    while (result.startsWith('.'))
        result.remove(0, 1);
    while (result.endsWith('.'))
        result.chop(1);
    if (result.contains(QRegularExpression("\\s")))
        return QString();
    if (!QRegularExpression("^[A-Za-z0-9_][A-Za-z0-9_.]*$").match(result).hasMatch())
        return QString();
    return result;
}

QString GScriptEditorSupport::visionTemplate(int trackingId, int loopDelayMs)
{
    trackingId = qBound(0, trackingId, 999);
    loopDelayMs = qBound(0, loopDelayMs, 60000);
    return QString(
        "; Vision/tracking worker generated by Delta X Software\n"
        "; Run exactly one vision worker for tracking %1.\n\n"
        "LABEL VISION_LOOP\n"
        "M98 PcaptureAndDetect(%1)\n"
        "M98 Pdelay(%2)\n"
        "JUMP VISION_LOOP\n")
        .arg(trackingId)
        .arg(loopDelayMs);
}

QString GScriptEditorSupport::robotTemplate(const GScriptRobotTemplateOptions& rawOptions)
{
    GScriptRobotTemplateOptions options = rawOptions;
    options.trackingId = qBound(0, options.trackingId, 999);
    options.robotId = qBound(0, options.robotId, 999);
    options.typeFilter = qBound(-1, options.typeFilter, 999999);
    if (options.minX > options.maxX)
        qSwap(options.minX, options.maxX);
    if (options.minY > options.maxY)
        qSwap(options.minY, options.maxY);
    QString vacuum = normalizeWatchName(options.vacuumVariable);
    if (vacuum.isEmpty())
        vacuum = QString("Vacuum.R%1.OK").arg(options.robotId);

    const QString prefix = QString("R%1").arg(options.robotId);
    const QString feedback = options.useVacuumFeedback
        ? QString("        M98 PwaitUntil(#%1 == 1,500,10,\"robot%2: vacuum timeout\")\n")
              .arg(vacuum).arg(options.robotId)
        : QStringLiteral("        M98 Pdelay(60)\n");

    return QString(
        "; Robot worker generated by Delta X Software\n"
        "; Verify every pose, zone and safety limit before enabling motion.\n\n"
        "SELECT robot%1\n\n"
        "#%2SafeZ = -260\n"
        "#%2PickZ = -335\n"
        "#%2PlaceX = 0\n"
        "#%2PlaceY = 0\n"
        "#%2PlaceZ = -330\n"
        "#%2AngleOffset = 0\n"
        "#%2BeltVector = (0,200,0)\n"
        "#%2Owner = \"robot%1\"\n"
        "#%2MinConfidence = 0.60\n\n"
        "M98 Passert(#%2SafeZ > #%2PickZ,\"robot%1: Safe Z must be above Pick Z\")\n"
        "M05\n"
        "SYNC robot%1 #%2BeltVector\n\n"
        "LABEL %2_LOOP\n"
        "M98 PclaimObject(%3,#%2Target,#%2Owner,%4,%5,%6,%7,%8,30000)\n\n"
        "IF #%2Target.Found == 1\n"
        "    IF #%2Target.Confidence >= #%2MinConfidence\n"
        "        #%2Pick = #%3.ConveyorToRobot%1.Map(#%2Target.X,#%2Target.Y)\n"
        "        #%2PickA = #%2Target.A + #%2AngleOffset\n\n"
        "        G01 X[#%2Pick.X] Y[#%2Pick.Y] Z[#%2SafeZ] W[#%2PickA] F1200 SYNC\n"
        "        G01 X[#%2Pick.X] Y[#%2Pick.Y] Z[#%2PickZ] W[#%2PickA] F500 SYNC\n"
        "        M03\n"
        "%9"
        "        M98 PcompleteObject(%3,#%2Target.UID,#%2Owner)\n\n"
        "        G01 Z[#%2SafeZ] F700\n"
        "        G01 X[#%2PlaceX] Y[#%2PlaceY] Z[#%2SafeZ] W0 F1200\n"
        "        G01 Z[#%2PlaceZ] F500\n"
        "        M05\n"
        "        M98 Pdelay(60)\n"
        "        G01 Z[#%2SafeZ] F700\n"
        "    ELSE\n"
        "        M98 PreleaseObject(%3,#%2Target.UID,#%2Owner)\n"
        "    ENDIF\n"
        "ENDIF\n\n"
        "M98 Pdelay(20)\n"
        "JUMP %2_LOOP\n")
        .arg(options.robotId)
        .arg(prefix)
        .arg(options.trackingId)
        .arg(number(options.minX))
        .arg(number(options.maxX))
        .arg(number(options.minY))
        .arg(number(options.maxY))
        .arg(options.typeFilter)
        .arg(feedback);
}
