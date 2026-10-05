#ifndef BLOCKPROGRAM_H
#define BLOCKPROGRAM_H

#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>

namespace DeltaXBlockProgramming
{
struct FieldDefinition
{
    enum class Kind {
        Text,
        Expression,
        Integer,
        Number,
        Choice,
        Multiline
    };

    QString key;
    QString label;
    Kind kind = Kind::Text;
    QVariant defaultValue;
    QStringList options;
    QString help;
};

struct BlockDefinition
{
    QString id;
    QString category;
    QString label;
    QString description;
    QString color;
    bool container = false;
    QVector<FieldDefinition> fields;
};

struct BlockNode
{
    QString type;
    QVariantMap fields;
    QVector<BlockNode> children;
};

struct BlockDiagnostic
{
    enum class Severity { Info, Warning, Error };

    Severity severity = Severity::Info;
    QString code;
    QString path;
    QString message;

    QVariantMap toVariantMap() const;
};

struct CompileResult
{
    QString script;
    QVector<BlockDiagnostic> diagnostics;

    bool hasErrors() const;
    QVariantList diagnosticMaps() const;
};

class BlockProgram final
{
public:
    static QVector<BlockDefinition> definitions();
    static const BlockDefinition* definition(const QString& type);
    static QVariantMap defaultFields(const QString& type);
    static QString summary(const BlockNode& node);

    static CompileResult compile(const QVector<BlockNode>& blocks);
    static QJsonObject toJson(const QVector<BlockNode>& blocks);
    static bool fromJson(const QJsonObject& document, QVector<BlockNode>* blocks,
                         QString* error = nullptr);

    static QStringList templateNames();
    static QVector<BlockNode> createTemplate(const QString& name);

private:
    BlockProgram() = delete;
};
}

#endif // BLOCKPROGRAM_H
