#include "FakeV3Plugin.h"

#include "DeltaXHostContext.h"

#include <stdexcept>

QString FakeV3Plugin::id() const { return QStringLiteral("test.fixture.v3"); }
QString FakeV3Plugin::displayName() const { return QStringLiteral("Test Fixture V3"); }
QString FakeV3Plugin::version() const { return QStringLiteral("3.0.0"); }

QStringList FakeV3Plugin::capabilities() const
{
    return {QStringLiteral("commands"), QStringLiteral("devices.provider"),
            QStringLiteral("gscript.primitives"),
            QStringLiteral("services.provider")};
}

void FakeV3Plugin::loadSettings(QSettings& settings)
{
    if (settings.value(QStringLiteral("failLoad"), false).toBool())
        throw std::runtime_error("requested settings failure");
    m_value = settings.value(QStringLiteral("value"), 0).toInt();
}

void FakeV3Plugin::saveSettings(QSettings& settings) const
{
    settings.setValue(QStringLiteral("value"), m_value);
}

bool FakeV3Plugin::initialize(DeltaXHostContext* context, QString* error)
{
    if (!context) {
        if (error)
            *error = QStringLiteral("context is required");
        return false;
    }
    m_context = context;
    return true;
}

bool FakeV3Plugin::start(QString*)
{
    m_started = true;
    if (m_context) {
        QString ignored;
        m_context->writeVariable(QStringLiteral("Fixture.Started"), true,
                                 false, &ignored);
        m_context->reportHealth(QStringLiteral("ready"), {}, {}, &ignored);
    }
    return true;
}

void FakeV3Plugin::stop()
{
    m_started = false;
    if (m_context) {
        QString ignored;
        m_context->writeVariable(QStringLiteral("Fixture.Stopped"), true,
                                 false, &ignored);
    }
}

bool FakeV3Plugin::executeCommand(const QString& command,
                                  const QVariantMap& arguments,
                                  QVariantMap* result, QString* error)
{
    if (command == QStringLiteral("status")) {
        if (result) {
            result->insert(QStringLiteral("started"), m_started);
            result->insert(QStringLiteral("project"),
                           m_context ? m_context->projectScope() : QString());
            result->insert(QStringLiteral("permissions"),
                           m_context ? m_context->grantedPermissions()
                                     : QStringList());
        }
        return true;
    }
    if (command == QStringLiteral("publish-event") && m_context) {
        return m_context->publishEvent(
                   QStringLiteral("fixture.changed"), arguments, error) != 0;
    }
    if (error)
        *error = QStringLiteral("unknown command");
    return false;
}

QVariantList FakeV3Plugin::gscriptPrimitives() const
{
    return {QVariantMap{
        {QStringLiteral("name"), QStringLiteral("fixturemultiply")},
        {QStringLiteral("signature"),
         QStringLiteral("M98 PfixtureMultiply(result, left, right)")},
        {QStringLiteral("description"), QStringLiteral("Multiply two values")},
        {QStringLiteral("minArgs"), 3},
        {QStringLiteral("maxArgs"), 3},
        {QStringLiteral("resultArgument"), 0},
    }};
}

bool FakeV3Plugin::executeGScriptPrimitive(const QString& name,
                                           const QVariantList& arguments,
                                           QVariant* result, QString* error)
{
    if (name != QStringLiteral("fixturemultiply") || arguments.size() != 2) {
        if (error)
            *error = QStringLiteral("invalid primitive call");
        return false;
    }
    if (result)
        *result = arguments.at(0).toDouble() * arguments.at(1).toDouble();
    return true;
}

QStringList FakeV3Plugin::deviceIds() const
{
    return {QStringLiteral("fixture.device0")};
}

bool FakeV3Plugin::submitDeviceCommand(const QString& deviceId,
                                       const QString& command,
                                       quint64, QString* error)
{
    if (!m_context || deviceId != QStringLiteral("fixture.device0")) {
        if (error)
            *error = QStringLiteral("unknown fixture device");
        return false;
    }
    return m_context->completeDeviceCommand(
        deviceId, QStringLiteral("ok:%1").arg(command), error);
}

QVariantList FakeV3Plugin::services() const
{
    return {QVariantMap{
        {QStringLiteral("id"), QStringLiteral("fixture.echo")},
        {QStringLiteral("version"), QStringLiteral("1.0.0")},
        {QStringLiteral("methods"), QStringList{QStringLiteral("echo")}},
    }};
}

bool FakeV3Plugin::invokeService(const QString& serviceId,
                                 const QString& method,
                                 const QVariantMap& request,
                                 QVariantMap* response, QString* error)
{
    if (serviceId != QStringLiteral("fixture.echo") ||
        method != QStringLiteral("echo")) {
        if (error)
            *error = QStringLiteral("unknown fixture service method");
        return false;
    }
    if (response)
        *response = request;
    return true;
}
