#include "PluginHostContext.h"

#include "PluginExtensionRegistry.h"
#include "sdk/DeltaXPermissions.h"

#include <algorithm>

PluginHostContext::PluginHostContext(
    const QString& pluginId, const QStringList& requestedPermissions,
    const QSet<QString>& grantedPermissions, const PluginHostServices& services)
    : m_pluginId(pluginId.trimmed().toLower())
    , m_projectScope(services.projectScope.trimmed().isEmpty()
                         ? QStringLiteral("default")
                         : services.projectScope.trimmed())
    , m_services(services)
{
    for (const QString& permission : requestedPermissions) {
        const QString normalized = permission.trimmed().toLower();
        if (grantedPermissions.contains(normalized))
            m_grantedPermissions.insert(normalized);
    }
}

QString PluginHostContext::pluginId() const { return m_pluginId; }
QString PluginHostContext::projectScope() const { return m_projectScope; }

QStringList PluginHostContext::grantedPermissions() const
{
    QStringList result(m_grantedPermissions.cbegin(), m_grantedPermissions.cend());
    result.sort(Qt::CaseInsensitive);
    return result;
}

bool PluginHostContext::hasPermission(const QString& permission) const
{
    return m_active.load(std::memory_order_acquire) &&
           m_grantedPermissions.contains(permission.trimmed().toLower());
}

bool PluginHostContext::requireActive(QString* error) const
{
    if (m_active.load(std::memory_order_acquire))
        return true;
    if (error)
        *error = QStringLiteral("plugin host context is no longer active");
    return false;
}

bool PluginHostContext::require(const QString& permission, QString* error) const
{
    if (!requireActive(error))
        return false;
    if (hasPermission(permission))
        return true;
    if (error)
        *error = QStringLiteral("permission '%1' was not granted").arg(permission);
    return false;
}

QString PluginHostContext::scopedOwner(const QString& owner) const
{
    const QString prefix = QStringLiteral("plugin/") + m_pluginId;
    const QString requested = owner.trimmed();
    if (requested.isEmpty() || requested == prefix)
        return prefix;
    if (requested.startsWith(prefix + QStringLiteral("/")))
        return requested;
    return prefix + QStringLiteral("/") + requested;
}

QVariant PluginHostContext::readVariable(const QString& key,
                                         const QVariant& defaultValue) const
{
    if (!require(DeltaXPermissions::VariablesRead, nullptr) ||
        !m_services.readVariable)
        return defaultValue;
    return m_services.readVariable(key, defaultValue);
}

bool PluginHostContext::writeVariable(const QString& key, const QVariant& value,
                                      bool persistent, QString* error)
{
    const QString permission = persistent
        ? DeltaXPermissions::VariablesWritePersistent
        : DeltaXPermissions::VariablesWriteRuntime;
    if (!require(permission, error))
        return false;
    if (!m_services.writeVariable) {
        if (error)
            *error = QStringLiteral("variable service is unavailable");
        return false;
    }
    return m_services.writeVariable(key, value, persistent, error);
}

bool PluginHostContext::removeVariable(const QString& key, QString* error)
{
    if (!require(DeltaXPermissions::VariablesWriteRuntime, error))
        return false;
    if (!m_services.removeVariable) {
        if (error)
            *error = QStringLiteral("variable service is unavailable");
        return false;
    }
    return m_services.removeVariable(key, error);
}

quint64 PluginHostContext::publishEvent(const QString& topic,
                                        const QVariantMap& payload,
                                        QString* error)
{
    if (!require(DeltaXPermissions::EventsPublish, error))
        return 0;
    return PluginExtensionRegistry::instance().publishEvent(
        m_pluginId, topic, payload, error);
}

QVariantList PluginHostContext::eventsSince(quint64 afterSequence,
                                            const QString& topic,
                                            int maximumCount,
                                            QString* error) const
{
    if (!require(DeltaXPermissions::EventsRead, error))
        return {};
    return PluginExtensionRegistry::instance().eventsSince(
        afterSequence, topic, maximumCount);
}

quint64 PluginHostContext::submitDeviceCommand(
    const QString& deviceId, const QString& command, bool waitForResponse,
    int timeoutMs, QString* error)
{
    if (!require(DeltaXPermissions::DevicesCommand, error))
        return 0;
    if (!m_services.submitDeviceCommand) {
        if (error)
            *error = QStringLiteral("device command service is unavailable");
        return 0;
    }
    return m_services.submitDeviceCommand(
        QStringLiteral("plugin/") + m_pluginId, deviceId, command,
        waitForResponse, timeoutMs, error);
}

bool PluginHostContext::completeDeviceCommand(
    const QString& deviceId, const QString& response, QString* error)
{
    if (!require(DeltaXPermissions::DevicesProvide, error))
        return false;
    if (!PluginExtensionRegistry::instance().ownsDevice(m_pluginId, deviceId)) {
        if (error)
            *error = QStringLiteral("plugin does not own device '%1'").arg(deviceId);
        return false;
    }
    if (!m_services.completeDeviceCommand) {
        if (error)
            *error = QStringLiteral("device response service is unavailable");
        return false;
    }
    return m_services.completeDeviceCommand(deviceId, response, error);
}

bool PluginHostContext::submitDetections(const QVariantMap& frame,
                                         QString* error)
{
    if (!require(DeltaXPermissions::VisionSubmit, error))
        return false;
    if (!m_services.submitDetections) {
        if (error)
            *error = QStringLiteral("vision submission service is unavailable");
        return false;
    }
    return m_services.submitDetections(frame, error);
}

QVariantList PluginHostContext::trackingSnapshot(int trackingId,
                                                 QString* error) const
{
    if (!require(DeltaXPermissions::TrackingRead, error))
        return {};
    if (!m_services.trackingSnapshot) {
        if (error)
            *error = QStringLiteral("tracking snapshot service is unavailable");
        return {};
    }
    return m_services.trackingSnapshot(trackingId, error);
}

QVariantMap PluginHostContext::claimObject(int trackingId,
                                           const QVariantMap& request,
                                           QString* error)
{
    if (!require(DeltaXPermissions::TrackingClaim, error))
        return {};
    if (!m_services.claimObject) {
        if (error)
            *error = QStringLiteral("tracking claim service is unavailable");
        return {};
    }
    QVariantMap scopedRequest = request;
    scopedRequest.insert(
        QStringLiteral("owner"),
        scopedOwner(request.value(QStringLiteral("owner")).toString()));
    return m_services.claimObject(trackingId, scopedRequest, error);
}

bool PluginHostContext::releaseObject(int trackingId, int uid,
                                      const QString& owner, QString* error)
{
    if (!require(DeltaXPermissions::TrackingClaim, error))
        return false;
    if (!m_services.releaseObject) {
        if (error)
            *error = QStringLiteral("tracking release service is unavailable");
        return false;
    }
    return m_services.releaseObject(
        trackingId, uid, scopedOwner(owner), error);
}

bool PluginHostContext::completeObject(int trackingId, int uid,
                                       const QString& owner, QString* error)
{
    if (!require(DeltaXPermissions::TrackingClaim, error))
        return false;
    if (!m_services.completeObject) {
        if (error)
            *error = QStringLiteral("tracking completion service is unavailable");
        return false;
    }
    return m_services.completeObject(
        trackingId, uid, scopedOwner(owner), error);
}

QVariantList PluginHostContext::serviceCatalog(QString* error) const
{
    if (!require(DeltaXPermissions::ServicesConsume, error))
        return {};
    return PluginExtensionRegistry::instance().serviceDescriptors();
}

bool PluginHostContext::invokeService(
    const QString& serviceId, const QString& method,
    const QVariantMap& request, QVariantMap* response, QString* error)
{
    if (!require(DeltaXPermissions::ServicesConsume, error))
        return false;
    return PluginExtensionRegistry::instance().invokeService(
        serviceId, method, request, response, error);
}

bool PluginHostContext::reportHealth(const QString& state,
                                     const QString& message,
                                     const QVariantMap& details,
                                     QString* error)
{
    if (!require(DeltaXPermissions::HealthReport, error))
        return false;
    if (!m_services.reportHealth) {
        if (error)
            *error = QStringLiteral("plugin health service is unavailable");
        return false;
    }
    return m_services.reportHealth(m_pluginId, state, message, details, error);
}

bool PluginHostContext::publishTelemetry(
    const QString& metric, const QVariant& value,
    const QVariantMap& attributes, QString* error)
{
    if (!require(DeltaXPermissions::TelemetryPublish, error))
        return false;
    if (!m_services.publishTelemetry) {
        if (error)
            *error = QStringLiteral("plugin telemetry service is unavailable");
        return false;
    }
    return m_services.publishTelemetry(
        m_pluginId, metric, value, attributes, error);
}

bool PluginHostContext::requestControlledStop(const QString& reason,
                                              QString* error)
{
    if (!require(DeltaXPermissions::CellControl, error))
        return false;
    if (!m_services.requestControlledStop) {
        if (error)
            *error = QStringLiteral("cell control service is unavailable");
        return false;
    }
    return m_services.requestControlledStop(reason, error);
}

void PluginHostContext::log(const QString& level, const QString& message)
{
    if (m_active.load(std::memory_order_acquire) && m_services.log)
        m_services.log(m_pluginId, level, message);
}

void PluginHostContext::invalidate()
{
    m_active.store(false, std::memory_order_release);
}
