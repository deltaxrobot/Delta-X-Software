#include "BlockProgram.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QRegularExpression>

#include <algorithm>

namespace DeltaXBlockProgramming
{
namespace
{
using Kind = FieldDefinition::Kind;

FieldDefinition field(const QString& key, const QString& label, Kind kind,
                      const QVariant& defaultValue,
                      const QStringList& options = {},
                      const QString& help = {})
{
    return {key, label, kind, defaultValue, options, help};
}

const QVector<BlockDefinition>& catalog()
{
    static const QVector<BlockDefinition> values = {
        {"comment", "Program", "Comment", "Document the generated program.",
         "#64748b", false,
         {field("text", "Text", Kind::Text, "Describe this step")}},
        {"set", "Program", "Set variable", "Assign a G-Script variable.",
         "#2563eb", false,
         {field("variable", "Variable", Kind::Text, "Value"),
          field("value", "Expression", Kind::Expression, "0")}},
        {"raw", "Program", "Raw G-Script", "Insert reviewed advanced G-Script.",
         "#475569", false,
         {field("code", "Code", Kind::Multiline, "; reviewed G-Script")}},
        {"if", "Logic", "If", "Run nested blocks when a condition is true.",
         "#7c3aed", true,
         {field("condition", "Condition", Kind::Expression, "1")}},
        {"else", "Logic", "Else", "Alternative branch following an If block.",
         "#8b5cf6", true, {}},
        {"while", "Logic", "While", "Repeat nested blocks while true.",
         "#6d28d9", true,
         {field("condition", "Condition", Kind::Expression, "1")}},
        {"repeat", "Logic", "Repeat", "Repeat nested blocks a fixed number of times.",
         "#9333ea", true,
         {field("count", "Count", Kind::Expression, "1")}},
        {"assert", "Logic", "Assert", "Fault when a safety/process condition is false.",
         "#dc2626", false,
         {field("condition", "Condition", Kind::Expression, "1"),
          field("message", "Fault message", Kind::Text, "Assertion failed")}},
        {"wait_until", "Logic", "Wait until", "Wait for a real process condition.",
         "#d97706", false,
         {field("condition", "Condition", Kind::Expression, "#Vacuum.OK == 1"),
          field("timeout", "Timeout (ms)", Kind::Integer, 500),
          field("poll", "Poll interval (ms)", Kind::Integer, 10),
          field("message", "Timeout message", Kind::Text, "Condition timeout")}},
        {"delay", "Logic", "Delay", "Non-blocking timer delay.",
         "#ca8a04", false,
         {field("milliseconds", "Milliseconds", Kind::Integer, 100)}},
        {"log", "Logic", "Log message", "Write an operator diagnostic.",
         "#0f766e", false,
         {field("message", "Message", Kind::Text, "Block program step")}},
        {"device_command", "Devices", "Device command",
         "Send a serialized command through the device broker.", "#0369a1", false,
         {field("device", "Device", Kind::Choice, "device0",
                {"robot0", "robot1", "conveyor0", "conveyor1", "encoder0",
                 "encoder1", "slider0", "device0"}),
          field("command", "Command", Kind::Text, "M42 P1"),
          field("response", "Response variable", Kind::Text, "DeviceReply"),
          field("timeout", "Timeout (ms)", Kind::Integer, 1500)}},
        {"home", "Robot", "Robot home", "Return a robot to its home position.",
         "#15803d", false,
         {field("robot", "Robot", Kind::Choice, "robot0", {"robot0", "robot1", "robot2"})}},
        {"move", "Robot", "Linear move", "Move a robot in Cartesian coordinates.",
         "#16a34a", false,
         {field("robot", "Robot", Kind::Choice, "robot0", {"robot0", "robot1", "robot2"}),
          field("x", "X", Kind::Expression, "0"),
          field("y", "Y", Kind::Expression, "0"),
          field("z", "Z", Kind::Expression, "-300"),
          field("w", "W / angle", Kind::Expression, "0"),
          field("speed", "Speed F", Kind::Expression, "500"),
          field("acceleration", "Acceleration A", Kind::Expression, "1000")}},
        {"conveyor_speed", "Conveyor", "Set conveyor speed",
         "Set a conveyor velocity through G-code.", "#0e7490", false,
         {field("conveyor", "Conveyor", Kind::Choice, "conveyor0", {"conveyor0", "conveyor1", "conveyor2"}),
          field("speed", "Speed", Kind::Expression, "100")}},
        {"conveyor_stop", "Conveyor", "Stop conveyor",
         "Stop a conveyor through G-code.", "#155e75", false,
         {field("conveyor", "Conveyor", Kind::Choice, "conveyor0", {"conveyor0", "conveyor1", "conveyor2"})}},
        {"capture_detect", "Vision & Tracking", "Capture and detect",
         "Capture a correlated image and update tracking.", "#c2410c", false,
         {field("tracking", "Tracking ID", Kind::Integer, 0)}},
        {"claim", "Vision & Tracking", "Claim object",
         "Atomically claim one object in the robot pick window.", "#ea580c", false,
         {field("tracking", "Tracking ID", Kind::Integer, 0),
          field("result", "Result variable", Kind::Text, "Target"),
          field("owner", "Owner expression", Kind::Expression, "#Owner"),
          field("minX", "Minimum X", Kind::Expression, "-180"),
          field("maxX", "Maximum X", Kind::Expression, "180"),
          field("minY", "Minimum Y", Kind::Expression, "300"),
          field("maxY", "Maximum Y", Kind::Expression, "450"),
          field("type", "Type (-1 = any)", Kind::Integer, -1),
          field("lease", "Lease (ms)", Kind::Integer, 30000)}},
        {"release", "Vision & Tracking", "Release object",
         "Release a claim when no pick was completed.", "#f97316", false,
         {field("tracking", "Tracking ID", Kind::Integer, 0),
          field("uid", "UID expression", Kind::Expression, "#Target.UID"),
          field("owner", "Owner expression", Kind::Expression, "#Owner")}},
        {"complete", "Vision & Tracking", "Complete object",
         "Mark a confirmed pick as completed.", "#fb923c", false,
         {field("tracking", "Tracking ID", Kind::Integer, 0),
          field("uid", "UID expression", Kind::Expression, "#Target.UID"),
          field("owner", "Owner expression", Kind::Expression, "#Owner")}},
        {"camera_pause", "Vision & Tracking", "Pause camera", "Pause cyclic capture.",
         "#b45309", false, {}},
        {"camera_resume", "Vision & Tracking", "Resume camera", "Resume cyclic capture.",
         "#a16207", false, {}},
    };
    return values;
}

QString quoted(QString value, bool* ok)
{
    value.replace('\r', QStringLiteral(" "));
    value.replace('\n', QStringLiteral(" "));
    if (ok)
        *ok = true;
    if (!value.contains('"'))
        return QStringLiteral("\"") + value + QStringLiteral("\"");
    if (!value.contains('\''))
        return QStringLiteral("'") + value + QStringLiteral("'");
    if (ok)
        *ok = false;
    return QStringLiteral("\"\"");
}

QString variableName(QString value)
{
    value = value.trimmed();
    if (value.startsWith('#'))
        value.remove(0, 1);
    return value;
}

bool validVariable(const QString& value)
{
    static const QRegularExpression pattern(
        QStringLiteral("^[A-Za-z_][A-Za-z0-9_.]*$"));
    return pattern.match(variableName(value)).hasMatch();
}

bool validDevice(const QString& value)
{
    static const QRegularExpression pattern(
        QStringLiteral("^(?:(?:robot|conveyor|encoder|slider|device)\\d+|[a-z][a-z0-9]*(?:[._-][a-z0-9]+)+)$"),
        QRegularExpression::CaseInsensitiveOption);
    return pattern.match(value.trimmed()).hasMatch();
}

QString expression(const BlockNode& node, const QString& key)
{
    return node.fields.value(key).toString().trimmed();
}

void diagnostic(QVector<BlockDiagnostic>& values,
                BlockDiagnostic::Severity severity, const QString& code,
                const QString& path, const QString& message)
{
    values.append({severity, code, path, message});
}

QString indent(int depth)
{
    return QString(depth * 4, QLatin1Char(' '));
}

void compileSequence(const QVector<BlockNode>& blocks, int depth,
                     const QString& parentPath, QStringList& output,
                     QVector<BlockDiagnostic>& diagnostics, int& loopCounter)
{
    for (int index = 0; index < blocks.size(); ++index) {
        const BlockNode& node = blocks.at(index);
        const QString path = parentPath.isEmpty()
            ? QString::number(index + 1)
            : parentPath + QStringLiteral(".") + QString::number(index + 1);
        const BlockDefinition* definition = BlockProgram::definition(node.type);
        if (!definition) {
            diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                       QStringLiteral("BP1001"), path,
                       QStringLiteral("Unknown block type '%1'.").arg(node.type));
            continue;
        }
        if (!definition->container && !node.children.isEmpty()) {
            diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                       QStringLiteral("BP1002"), path,
                       QStringLiteral("Block '%1' cannot contain child blocks.")
                           .arg(definition->label));
        }

        const QString lead = indent(depth);
        auto requireExpression = [&](const QString& key, const QString& label) {
            const QString value = expression(node, key);
            if (value.isEmpty()) {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                           QStringLiteral("BP1101"), path,
                           QStringLiteral("%1 is required.").arg(label));
            }
            return value.isEmpty() ? QStringLiteral("0") : value;
        };
        auto requirePositive = [&](const QString& key, const QString& label,
                                   bool allowZero = false) {
            const int value = node.fields.value(key).toInt();
            if (value < 0 || (!allowZero && value == 0)) {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                           QStringLiteral("BP1107"), path,
                           QStringLiteral("%1 must be %2.")
                               .arg(label, allowZero
                                      ? QStringLiteral("zero or greater")
                                      : QStringLiteral("greater than zero")));
            }
            return value;
        };
        auto requireDevice = [&](const QString& key, const QString& label) {
            const QString value = expression(node, key);
            if (!validDevice(value)) {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                           QStringLiteral("BP1108"), path,
                           QStringLiteral("%1 ID is invalid.").arg(label));
            }
            return value;
        };
        auto requireText = [&](const QString& key, const QString& label) {
            bool valid = false;
            const QString value = quoted(node.fields.value(key).toString(),
                                         &valid);
            if (!valid) {
                diagnostic(
                    diagnostics, BlockDiagnostic::Severity::Error,
                    QStringLiteral("BP1109"), path,
                    QStringLiteral("%1 cannot contain both single and double quotes.")
                        .arg(label));
            }
            return value;
        };

        if (node.type == QStringLiteral("comment")) {
            output.append(lead + QStringLiteral("; ") +
                          node.fields.value("text").toString().replace('\n', ' '));
        } else if (node.type == QStringLiteral("set")) {
            const QString variable = variableName(node.fields.value("variable").toString());
            if (!validVariable(variable)) {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                           QStringLiteral("BP1102"), path,
                           QStringLiteral("Variable name is invalid."));
            }
            output.append(lead + QStringLiteral("#") + variable +
                          QStringLiteral(" = ") + requireExpression("value", "Expression"));
        } else if (node.type == QStringLiteral("raw")) {
            const QString raw = node.fields.value("code").toString().trimmed();
            if (raw.isEmpty()) {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Warning,
                           QStringLiteral("BP1201"), path,
                           QStringLiteral("Raw G-Script block is empty."));
            } else {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Warning,
                           QStringLiteral("BP1202"), path,
                           QStringLiteral("Raw G-Script requires manual review."));
                for (const QString& line : raw.split('\n'))
                    output.append(lead + line.trimmed());
            }
        } else if (node.type == QStringLiteral("if")) {
            output.append(lead + QStringLiteral("IF ") +
                          requireExpression("condition", "Condition"));
            compileSequence(node.children, depth + 1, path, output, diagnostics,
                            loopCounter);
            const bool hasElse = index + 1 < blocks.size() &&
                                 blocks.at(index + 1).type == QStringLiteral("else");
            if (hasElse) {
                const BlockNode& elseNode = blocks.at(++index);
                output.append(lead + QStringLiteral("ELSE"));
                compileSequence(elseNode.children, depth + 1, path + ".else",
                                output, diagnostics, loopCounter);
            }
            output.append(lead + QStringLiteral("ENDIF"));
        } else if (node.type == QStringLiteral("else")) {
            diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                       QStringLiteral("BP1103"), path,
                       QStringLiteral("Else must immediately follow an If block."));
        } else if (node.type == QStringLiteral("while")) {
            output.append(lead + QStringLiteral("WHILE ") +
                          requireExpression("condition", "Condition"));
            compileSequence(node.children, depth + 1, path, output, diagnostics,
                            loopCounter);
            output.append(lead + QStringLiteral("ENDWHILE"));
        } else if (node.type == QStringLiteral("repeat")) {
            const QString counter = QStringLiteral("#BlockLoop%1").arg(++loopCounter);
            output.append(lead + QStringLiteral("FOR %1 = 1 TO %2 STEP 1")
                                      .arg(counter, requireExpression("count", "Count")));
            compileSequence(node.children, depth + 1, path, output, diagnostics,
                            loopCounter);
            output.append(lead + QStringLiteral("ENDFOR"));
        } else if (node.type == QStringLiteral("assert")) {
            output.append(lead + QStringLiteral("M98 Passert(%1, %2)")
                                      .arg(requireExpression("condition", "Condition"),
                                           requireText("message", "Fault message")));
        } else if (node.type == QStringLiteral("wait_until")) {
            output.append(lead + QStringLiteral("M98 PwaitUntil(%1, %2, %3, %4)")
                                      .arg(requireExpression("condition", "Condition"))
                                      .arg(requirePositive("timeout", "Timeout"))
                                      .arg(requirePositive("poll", "Poll interval"))
                                      .arg(requireText("message", "Timeout message")));
        } else if (node.type == QStringLiteral("delay")) {
            output.append(lead + QStringLiteral("M98 Pdelay(%1)")
                                      .arg(requirePositive("milliseconds", "Delay", true)));
        } else if (node.type == QStringLiteral("log")) {
            output.append(lead + QStringLiteral("M98 PlogMessage(%1)")
                                      .arg(requireText("message", "Log message")));
        } else if (node.type == QStringLiteral("device_command")) {
            const QString device = expression(node, "device");
            if (!validDevice(device)) {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                           QStringLiteral("BP1104"), path,
                           QStringLiteral("Device ID is invalid."));
            }
            const QString response = variableName(node.fields.value("response").toString());
            if (response.isEmpty()) {
                output.append(lead + QStringLiteral("M98 Psend(%1, %2)")
                                          .arg(device,
                                               requireText("command", "Device command")));
            } else {
                if (!validVariable(response)) {
                    diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                               QStringLiteral("BP1105"), path,
                               QStringLiteral("Response variable is invalid."));
                }
                output.append(lead + QStringLiteral("M98 Psend(%1, %2, #%3, %4)")
                                          .arg(device,
                                               requireText("command", "Device command"),
                                               response)
                                          .arg(requirePositive("timeout", "Timeout")));
            }
        } else if (node.type == QStringLiteral("home")) {
            output.append(lead + requireDevice("robot", "Robot") +
                          QStringLiteral(" G28"));
        } else if (node.type == QStringLiteral("move")) {
            // G-Script resolves variables/arithmetic in G-code parameters only
            // inside brackets. Always bracket block expressions, including
            // literals, so generated motion never leaks '#Name' to firmware.
            output.append(lead + QStringLiteral("%1 G01 X[%2] Y[%3] Z[%4] W[%5] F[%6] A[%7]")
                                      .arg(requireDevice("robot", "Robot"),
                                           requireExpression("x", "X"),
                                           requireExpression("y", "Y"),
                                           requireExpression("z", "Z"),
                                           requireExpression("w", "W"),
                                           requireExpression("speed", "Speed"),
                                           requireExpression("acceleration", "Acceleration")));
        } else if (node.type == QStringLiteral("conveyor_speed")) {
            output.append(lead + QStringLiteral("%1 M311 %2")
                                      .arg(requireDevice("conveyor", "Conveyor"),
                                           requireExpression("speed", "Speed")));
        } else if (node.type == QStringLiteral("conveyor_stop")) {
            output.append(lead + requireDevice("conveyor", "Conveyor") +
                          QStringLiteral(" M311 0"));
        } else if (node.type == QStringLiteral("capture_detect")) {
            output.append(lead + QStringLiteral("M98 PcaptureAndDetect(%1)")
                                      .arg(requirePositive("tracking", "Tracking ID", true)));
        } else if (node.type == QStringLiteral("claim")) {
            const QString result = variableName(node.fields.value("result").toString());
            if (!validVariable(result)) {
                diagnostic(diagnostics, BlockDiagnostic::Severity::Error,
                           QStringLiteral("BP1106"), path,
                           QStringLiteral("Claim result variable is invalid."));
            }
            output.append(
                lead + QStringLiteral("M98 PclaimObject(%1, #%2, %3, %4, %5, %6, %7, %8, %9)")
                           .arg(requirePositive("tracking", "Tracking ID", true))
                           .arg(result, requireExpression("owner", "Owner"),
                                requireExpression("minX", "Minimum X"),
                                requireExpression("maxX", "Maximum X"),
                                requireExpression("minY", "Minimum Y"),
                                requireExpression("maxY", "Maximum Y"))
                           .arg(node.fields.value("type", -1).toInt())
                           .arg(requirePositive("lease", "Claim lease")));
        } else if (node.type == QStringLiteral("release")) {
            output.append(lead + QStringLiteral("M98 PreleaseObject(%1, %2, %3)")
                                      .arg(requirePositive("tracking", "Tracking ID", true))
                                      .arg(requireExpression("uid", "UID"),
                                           requireExpression("owner", "Owner")));
        } else if (node.type == QStringLiteral("complete")) {
            output.append(lead + QStringLiteral("M98 PcompleteObject(%1, %2, %3)")
                                      .arg(requirePositive("tracking", "Tracking ID", true))
                                      .arg(requireExpression("uid", "UID"),
                                           requireExpression("owner", "Owner")));
        } else if (node.type == QStringLiteral("camera_pause")) {
            output.append(lead + QStringLiteral("M98 PpauseCamera"));
        } else if (node.type == QStringLiteral("camera_resume")) {
            output.append(lead + QStringLiteral("M98 PresumeCamera"));
        }
    }
}

QJsonObject nodeToJson(const BlockNode& node)
{
    QJsonArray children;
    for (const BlockNode& child : node.children)
        children.append(nodeToJson(child));
    return {
        {QStringLiteral("type"), node.type},
        {QStringLiteral("fields"), QJsonObject::fromVariantMap(node.fields)},
        {QStringLiteral("children"), children},
    };
}

bool nodeFromJson(const QJsonObject& object, BlockNode* node, QString* error,
                  int depth, int* total)
{
    if (!node || !total)
        return false;
    if (depth > 32 || ++(*total) > 2000) {
        if (error)
            *error = QStringLiteral("block document exceeds the nesting or size limit");
        return false;
    }
    if (!object.value(QStringLiteral("type")).isString() ||
        !object.value(QStringLiteral("fields")).isObject() ||
        !object.value(QStringLiteral("children")).isArray()) {
        if (error)
            *error = QStringLiteral("each block requires type, fields and children");
        return false;
    }
    node->type = object.value(QStringLiteral("type")).toString().trimmed();
    if (!BlockProgram::definition(node->type)) {
        if (error)
            *error = QStringLiteral("unknown block type '%1'").arg(node->type);
        return false;
    }
    node->fields = BlockProgram::defaultFields(node->type);
    const QVariantMap storedFields =
        object.value(QStringLiteral("fields")).toObject().toVariantMap();
    for (auto it = storedFields.cbegin(); it != storedFields.cend(); ++it)
        node->fields.insert(it.key(), it.value());
    const QJsonArray children = object.value(QStringLiteral("children")).toArray();
    for (const QJsonValue& value : children) {
        if (!value.isObject()) {
            if (error)
                *error = QStringLiteral("block children must be objects");
            return false;
        }
        BlockNode child;
        if (!nodeFromJson(value.toObject(), &child, error, depth + 1, total))
            return false;
        node->children.append(child);
    }
    return true;
}

BlockNode makeNode(const QString& type, const QVariantMap& fields = {},
                   const QVector<BlockNode>& children = {})
{
    QVariantMap merged = BlockProgram::defaultFields(type);
    for (auto it = fields.cbegin(); it != fields.cend(); ++it)
        merged.insert(it.key(), it.value());
    return {type, merged, children};
}
}

QVariantMap BlockDiagnostic::toVariantMap() const
{
    QString name = QStringLiteral("Info");
    if (severity == Severity::Warning)
        name = QStringLiteral("Warning");
    else if (severity == Severity::Error)
        name = QStringLiteral("Error");
    return {{QStringLiteral("severity"), name},
            {QStringLiteral("code"), code},
            {QStringLiteral("path"), path},
            {QStringLiteral("message"), message}};
}

bool CompileResult::hasErrors() const
{
    return std::any_of(diagnostics.cbegin(), diagnostics.cend(),
                       [](const BlockDiagnostic& value) {
                           return value.severity == BlockDiagnostic::Severity::Error;
                       });
}

QVariantList CompileResult::diagnosticMaps() const
{
    QVariantList result;
    for (const BlockDiagnostic& value : diagnostics)
        result.append(value.toVariantMap());
    return result;
}

QVector<BlockDefinition> BlockProgram::definitions()
{
    return catalog();
}

const BlockDefinition* BlockProgram::definition(const QString& type)
{
    const QString normalized = type.trimmed().toLower();
    const auto& values = catalog();
    const auto it = std::find_if(values.cbegin(), values.cend(),
                                 [&normalized](const BlockDefinition& value) {
                                     return value.id == normalized;
                                 });
    return it == values.cend() ? nullptr : &(*it);
}

QVariantMap BlockProgram::defaultFields(const QString& type)
{
    QVariantMap result;
    if (const BlockDefinition* value = definition(type)) {
        for (const FieldDefinition& field : value->fields)
            result.insert(field.key, field.defaultValue);
    }
    return result;
}

QString BlockProgram::summary(const BlockNode& node)
{
    const BlockDefinition* value = definition(node.type);
    if (!value)
        return node.type;
    QStringList details;
    for (const FieldDefinition& field : value->fields) {
        const QString text = node.fields.value(field.key, field.defaultValue)
                                 .toString().simplified();
        if (!text.isEmpty())
            details.append(text.left(32));
        if (details.size() >= 2)
            break;
    }
    return details.isEmpty() ? value->label
                             : QStringLiteral("%1 — %2")
                                   .arg(value->label, details.join(QStringLiteral(", ")));
}

CompileResult BlockProgram::compile(const QVector<BlockNode>& blocks)
{
    CompileResult result;
    if (blocks.isEmpty()) {
        diagnostic(result.diagnostics, BlockDiagnostic::Severity::Error,
                   QStringLiteral("BP1000"), QStringLiteral("program"),
                   QStringLiteral("Add at least one block before generating G-Script."));
        return result;
    }
    QStringList lines;
    lines.append(QStringLiteral("; Generated by Delta X Block Programming"));
    int loopCounter = 0;
    compileSequence(blocks, 0, {}, lines, result.diagnostics, loopCounter);
    result.script = lines.join(QLatin1Char('\n')) + QLatin1Char('\n');
    return result;
}

QJsonObject BlockProgram::toJson(const QVector<BlockNode>& blocks)
{
    QJsonArray values;
    for (const BlockNode& node : blocks)
        values.append(nodeToJson(node));
    return {
        {QStringLiteral("format"), QStringLiteral("deltax-block-program")},
        {QStringLiteral("version"), 1},
        {QStringLiteral("blocks"), values},
    };
}

bool BlockProgram::fromJson(const QJsonObject& document,
                            QVector<BlockNode>* blocks, QString* error)
{
    if (!blocks) {
        if (error)
            *error = QStringLiteral("output block list is required");
        return false;
    }
    if (document.value(QStringLiteral("format")).toString() !=
            QStringLiteral("deltax-block-program") ||
        document.value(QStringLiteral("version")).toInt() != 1 ||
        !document.value(QStringLiteral("blocks")).isArray()) {
        if (error)
            *error = QStringLiteral("unsupported Delta X block program document");
        return false;
    }
    QVector<BlockNode> parsed;
    int total = 0;
    for (const QJsonValue& value : document.value(QStringLiteral("blocks")).toArray()) {
        if (!value.isObject()) {
            if (error)
                *error = QStringLiteral("top-level blocks must be objects");
            return false;
        }
        BlockNode node;
        if (!nodeFromJson(value.toObject(), &node, error, 0, &total))
            return false;
        parsed.append(node);
    }
    *blocks = parsed;
    return true;
}

QStringList BlockProgram::templateNames()
{
    return {QStringLiteral("Empty"), QStringLiteral("Software self-test"),
            QStringLiteral("Vision tracking loop"),
            QStringLiteral("Robot conveyor pick worker")};
}

QVector<BlockNode> BlockProgram::createTemplate(const QString& name)
{
    if (name == QStringLiteral("Software self-test")) {
        return {
            makeNode("comment", {{"text", "Software-only self-test: no device commands"}}),
            makeNode("set", {{"variable", "Blocks.Counter"}, {"value", "0"}}),
            makeNode("repeat", {{"count", "3"}}, {
                makeNode("set", {{"variable", "Blocks.Counter"},
                                 {"value", "#Blocks.Counter + 1"}}),
                makeNode("log", {{"message", "Block iteration"}}),
            }),
            makeNode("assert", {{"condition", "#Blocks.Counter == 3"},
                                {"message", "Block loop failed"}}),
            makeNode("wait_until", {{"condition", "#Blocks.Counter == 3"},
                                    {"timeout", 200}, {"poll", 10},
                                    {"message", "Block value was not published"}}),
            makeNode("delay", {{"milliseconds", 10}}),
            makeNode("log", {{"message", "PASS block programming"}}),
        };
    }
    if (name == QStringLiteral("Vision tracking loop")) {
        return {
            makeNode("comment", {{"text", "Continuously capture correlated detections"}}),
            makeNode("while", {{"condition", "1"}}, {
                makeNode("capture_detect", {{"tracking", 0}}),
                makeNode("delay", {{"milliseconds", 20}}),
            }),
        };
    }
    if (name == QStringLiteral("Robot conveyor pick worker")) {
        return {
            makeNode("comment", {{"text", "Configure and validate every process value before production"}}),
            makeNode("set", {{"variable", "Owner"}, {"value", "\"robot0\""}}),
            makeNode("set", {{"variable", "SafeZ"}, {"value", "-250"}}),
            makeNode("set", {{"variable", "PickZ"}, {"value", "-330"}}),
            makeNode("assert", {{"condition", "#SafeZ > #PickZ"}, {"message", "Safe Z must be above pick Z"}}),
            makeNode("while", {{"condition", "1"}}, {
                makeNode("claim", {{"tracking", 0}, {"result", "Target"}, {"owner", "#Owner"}}),
                makeNode("if", {{"condition", "#Target.Found == 1"}}, {
                    makeNode("move", {{"robot", "robot0"}, {"x", "#Target.X"}, {"y", "#Target.Y"}, {"z", "#SafeZ"}, {"w", "#Target.Angle"}}),
                    makeNode("move", {{"robot", "robot0"}, {"x", "#Target.X"}, {"y", "#Target.Y"}, {"z", "#PickZ"}, {"w", "#Target.Angle"}}),
                    makeNode("device_command", {{"device", "device0"}, {"command", "M42 P1"}, {"response", "VacuumReply"}}),
                    makeNode("wait_until", {{"condition", "#Vacuum.R0.OK == 1"}, {"message", "robot0: vacuum timeout"}}),
                    makeNode("complete", {{"tracking", 0}, {"uid", "#Target.UID"}, {"owner", "#Owner"}}),
                }),
                makeNode("else", {}, {
                    makeNode("delay", {{"milliseconds", 10}}),
                }),
            }),
        };
    }
    return {};
}
}
