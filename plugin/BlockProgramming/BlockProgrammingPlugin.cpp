#include "BlockProgrammingPlugin.h"

#include "BlockProgram.h"
#include "BlockProgrammingPanel.h"
#include "DeltaXHostContext.h"
#include "DeltaXPermissions.h"

#include <QJsonDocument>
#include <QSettings>

using namespace DeltaXBlockProgramming;

BlockProgrammingPlugin::~BlockProgrammingPlugin()
{
    delete m_panel;
}

QString BlockProgrammingPlugin::id() const
{
    return QStringLiteral("deltax.block-programming");
}

QString BlockProgrammingPlugin::displayName() const
{
    return QStringLiteral("Block Programming");
}

QString BlockProgrammingPlugin::version() const
{
    return QStringLiteral("1.0.0");
}

QStringList BlockProgrammingPlugin::capabilities() const
{
    return {QStringLiteral("commands"), QStringLiteral("panel")};
}

void BlockProgrammingPlugin::loadSettings(QSettings& settings)
{
    m_savedWorker = qMax(0, settings.value(QStringLiteral("worker"), 0).toInt());
    const QByteArray encoded = settings.value(QStringLiteral("workspace")).toByteArray();
    if (encoded.isEmpty())
        return;

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(encoded, &parseError);
    if (parseError.error == QJsonParseError::NoError && document.isObject())
        m_savedWorkspace = document.object();
}

void BlockProgrammingPlugin::saveSettings(QSettings& settings) const
{
    QJsonObject document = m_savedWorkspace;
    int worker = m_savedWorker;
    if (m_panel) {
        document = m_panel->workspaceDocument();
        worker = m_panel->selectedWorkerIndex();
    }
    settings.setValue(QStringLiteral("worker"), qMax(0, worker));
    settings.setValue(QStringLiteral("workspace"),
                      QJsonDocument(document).toJson(QJsonDocument::Compact));
}

bool BlockProgrammingPlugin::initialize(DeltaXHostContext* context,
                                        QString* error)
{
    if (!context) {
        if (error)
            *error = QStringLiteral("host context is required");
        return false;
    }
    m_context = context;
    return true;
}

bool BlockProgrammingPlugin::start(QString* error)
{
    if (!m_context) {
        if (error)
            *error = QStringLiteral("plugin is not initialized");
        return false;
    }

    QString ignored;
    m_context->reportHealth(
        QStringLiteral("ready"),
        QStringLiteral("Block editor and G-Script compiler are ready"), {},
        &ignored);
    return true;
}

void BlockProgrammingPlugin::stop()
{
    if (!m_context)
        return;
    QString ignored;
    m_context->reportHealth(QStringLiteral("stopped"), {}, {}, &ignored);
}

QWidget* BlockProgrammingPlugin::panel()
{
    if (m_panel)
        return m_panel;

    m_panel = new BlockProgrammingPanel(m_context);
    if (!m_savedWorkspace.isEmpty()) {
        QString error;
        if (!m_panel->loadWorkspaceDocument(m_savedWorkspace, &error) && m_context)
            m_context->log(QStringLiteral("warning"), error);
    }
    m_panel->setSelectedWorkerIndex(m_savedWorker);
    return m_panel;
}

bool BlockProgrammingPlugin::executeCommand(const QString& command,
                                            const QVariantMap& arguments,
                                            QVariantMap* result,
                                            QString* error)
{
    if (command == QStringLiteral("catalog")) {
        QVariantList blocks;
        for (const BlockDefinition& definition : BlockProgram::definitions()) {
            QVariantList fields;
            for (const FieldDefinition& field : definition.fields) {
                fields.append(QVariantMap{
                    {QStringLiteral("key"), field.key},
                    {QStringLiteral("label"), field.label},
                    {QStringLiteral("default"), field.defaultValue},
                    {QStringLiteral("options"), field.options},
                    {QStringLiteral("help"), field.help},
                });
            }
            blocks.append(QVariantMap{
                {QStringLiteral("id"), definition.id},
                {QStringLiteral("category"), definition.category},
                {QStringLiteral("label"), definition.label},
                {QStringLiteral("description"), definition.description},
                {QStringLiteral("color"), definition.color},
                {QStringLiteral("container"), definition.container},
                {QStringLiteral("fields"), fields},
            });
        }
        if (result) {
            result->insert(QStringLiteral("blocks"), blocks);
            result->insert(QStringLiteral("templates"),
                           BlockProgram::templateNames());
        }
        return true;
    }

    QVector<BlockNode> blocks;
    QJsonObject document;
    if (command == QStringLiteral("template")) {
        const QString name = arguments.value(QStringLiteral("name")).toString();
        if (!BlockProgram::templateNames().contains(name) ||
            name == QStringLiteral("Empty")) {
            if (name != QStringLiteral("Empty")) {
                if (error)
                    *error = QStringLiteral("unknown block program template");
                return false;
            }
        }
        blocks = BlockProgram::createTemplate(name);
        document = BlockProgram::toJson(blocks);
    } else if (command == QStringLiteral("compile")) {
        document = QJsonObject::fromVariantMap(
            arguments.value(QStringLiteral("document")).toMap());
        if (!BlockProgram::fromJson(document, &blocks, error))
            return false;
    } else {
        if (error)
            *error = QStringLiteral("unknown command; expected catalog, template or compile");
        return false;
    }

    const CompileResult compiled = BlockProgram::compile(blocks);
    if (result) {
        result->insert(QStringLiteral("document"), document.toVariantMap());
        result->insert(QStringLiteral("script"), compiled.script);
        result->insert(QStringLiteral("diagnostics"),
                       compiled.diagnosticMaps());
        result->insert(QStringLiteral("valid"), !compiled.hasErrors());
    }
    return true;
}
