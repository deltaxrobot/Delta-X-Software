#include "PluginExtensionRegistry.h"

#include "sdk/DeltaXDeviceProvider.h"
#include "sdk/DeltaXGScriptProvider.h"
#include "sdk/DeltaXPluginMetadata.h"
#include "sdk/DeltaXServiceProvider.h"

#include <QDateTime>
#include <QMetaObject>
#include <QObject>
#include <QRegularExpression>
#include <QSet>
#include <QThread>

#include <algorithm>
#include <exception>

namespace
{
const QRegularExpression& extensionIdPattern()
{
    static const QRegularExpression pattern(
        QStringLiteral("^[a-z][a-z0-9]*(?:[._-][a-z0-9]+)*$"));
    return pattern;
}

const QRegularExpression& gscriptNamePattern()
{
    static const QRegularExpression pattern(QStringLiteral("^[a-z][a-z0-9]*$"));
    return pattern;
}

const QSet<QString>& builtInPrimitives()
{
    static const QSet<QString> values = {
        QStringLiteral("send"), QStringLiteral("assert"),
        QStringLiteral("waituntil"), QStringLiteral("updatetracking"),
        QStringLiteral("captureanddetect"), QStringLiteral("claimobject"),
        QStringLiteral("releaseobject"), QStringLiteral("completeobject"),
        QStringLiteral("delay"), QStringLiteral("addobject"),
        QStringLiteral("clearobjects"), QStringLiteral("deletefirstobject"),
        QStringLiteral("deleteobject"), QStringLiteral("pausecamera"),
        QStringLiteral("capturecamera"), QStringLiteral("resumecamera"),
        QStringLiteral("logmessage"), QStringLiteral("syncconveyor"),
        QStringLiteral("stopsyncconveyor"), QStringLiteral("sendgcode")};
    return values;
}

template <typename Callback>
void invokeOnOwner(QObject* root, Callback callback)
{
    if (!root || root->thread() == QThread::currentThread()) {
        callback();
        return;
    }
    QMetaObject::invokeMethod(root, callback, Qt::BlockingQueuedConnection);
}
}

PluginExtensionRegistry& PluginExtensionRegistry::instance()
{
    static PluginExtensionRegistry registry;
    return registry;
}

QString PluginExtensionRegistry::normalized(const QString& value)
{
    return value.trimmed().toLower();
}

bool PluginExtensionRegistry::registerGScriptProvider(
    const QString& pluginId, QObject* root, DeltaXGScriptProvider* provider,
    QString* error)
{
    if (!root || !provider) {
        if (error)
            *error = QStringLiteral("G-Script provider and root object are required");
        return false;
    }

    QVariantList declared;
    try {
        declared = provider->gscriptPrimitives();
    } catch (...) {
        if (error)
            *error = QStringLiteral("G-Script descriptor method raised an exception");
        return false;
    }
    if (declared.isEmpty()) {
        if (error)
            *error = QStringLiteral("G-Script provider declared no primitives");
        return false;
    }

    QHash<QString, GScriptRecord> candidates;
    for (const QVariant& value : declared) {
        const QVariantMap map = value.toMap();
        const QString name = normalized(map.value(QStringLiteral("name")).toString());
        const QString signature = map.value(QStringLiteral("signature")).toString().trimmed();
        const int minimum = map.value(QStringLiteral("minArgs"), 0).toInt();
        const int maximum = map.value(QStringLiteral("maxArgs"), minimum).toInt();
        const int resultArgument = map.value(QStringLiteral("resultArgument"), -1).toInt();
        if (!gscriptNamePattern().match(name).hasMatch() ||
            builtInPrimitives().contains(name)) {
            if (error)
                *error = QStringLiteral("invalid or reserved G-Script primitive '%1'").arg(name);
            return false;
        }
        if (signature.isEmpty() || minimum < 0 || maximum < minimum ||
            maximum > 32 || resultArgument >= maximum || resultArgument < -1 ||
            (resultArgument >= 0 && resultArgument >= minimum)) {
            if (error)
                *error = QStringLiteral("invalid descriptor for G-Script primitive '%1'").arg(name);
            return false;
        }
        if (candidates.contains(name)) {
            if (error)
                *error = QStringLiteral("duplicate G-Script primitive '%1'").arg(name);
            return false;
        }
        GScriptRecord record;
        record.descriptor.pluginId = normalized(pluginId);
        record.descriptor.name = name;
        record.descriptor.signature = signature;
        record.descriptor.description =
            map.value(QStringLiteral("description")).toString().trimmed();
        record.descriptor.minimumArguments = minimum;
        record.descriptor.maximumArguments = maximum;
        record.descriptor.resultArgument = resultArgument;
        record.root = root;
        record.provider = provider;
        candidates.insert(name, record);
    }

    QWriteLocker locker(&m_lock);
    for (auto it = candidates.cbegin(); it != candidates.cend(); ++it) {
        if (m_gscript.contains(it.key())) {
            if (error)
                *error = QStringLiteral("G-Script primitive '%1' is already registered")
                             .arg(it.key());
            return false;
        }
    }
    for (auto it = candidates.cbegin(); it != candidates.cend(); ++it)
        m_gscript.insert(it.key(), it.value());
    return true;
}

bool PluginExtensionRegistry::registerDeviceProvider(
    const QString& pluginId, QObject* root, DeltaXDeviceProvider* provider,
    QString* error)
{
    if (!root || !provider) {
        if (error)
            *error = QStringLiteral("device provider and root object are required");
        return false;
    }
    QStringList ids;
    try {
        ids = provider->deviceIds();
    } catch (...) {
        if (error)
            *error = QStringLiteral("device descriptor method raised an exception");
        return false;
    }
    if (ids.isEmpty()) {
        if (error)
            *error = QStringLiteral("device provider declared no devices");
        return false;
    }
    QSet<QString> uniqueIds;
    for (QString& id : ids) {
        id = normalized(id);
        if (!extensionIdPattern().match(id).hasMatch() || !id.contains('.')) {
            if (error)
                *error = QStringLiteral(
                    "plugin device '%1' must be a namespaced lowercase id")
                             .arg(id);
            return false;
        }
        if (uniqueIds.contains(id)) {
            if (error)
                *error = QStringLiteral("duplicate plugin device '%1'").arg(id);
            return false;
        }
        uniqueIds.insert(id);
    }

    QWriteLocker locker(&m_lock);
    for (const QString& id : ids) {
        if (m_devices.contains(id)) {
            if (error)
                *error = QStringLiteral("device '%1' is already registered").arg(id);
            return false;
        }
    }
    for (const QString& id : ids)
        m_devices.insert(id, {normalized(pluginId), root, provider});
    return true;
}

bool PluginExtensionRegistry::registerServiceProvider(
    const QString& pluginId, QObject* root, DeltaXServiceProvider* provider,
    QString* error)
{
    if (!root || !provider) {
        if (error)
            *error = QStringLiteral("service provider and root object are required");
        return false;
    }
    QVariantList declared;
    try {
        declared = provider->services();
    } catch (...) {
        if (error)
            *error = QStringLiteral("service descriptor method raised an exception");
        return false;
    }
    if (declared.isEmpty()) {
        if (error)
            *error = QStringLiteral("service provider declared no services");
        return false;
    }

    QHash<QString, ServiceRecord> candidates;
    for (const QVariant& value : declared) {
        const QVariantMap map = value.toMap();
        const QString id = normalized(map.value(QStringLiteral("id")).toString());
        const QString version = map.value(QStringLiteral("version")).toString().trimmed();
        QStringList methods = map.value(QStringLiteral("methods")).toStringList();
        for (QString& method : methods)
            method = normalized(method);
        if (!extensionIdPattern().match(id).hasMatch() || !id.contains('.') ||
            !DeltaXPluginContract::isSemanticVersion(version) || methods.isEmpty()) {
            if (error)
                *error = QStringLiteral("invalid service descriptor '%1'").arg(id);
            return false;
        }
        for (const QString& method : methods) {
            if (!extensionIdPattern().match(method).hasMatch()) {
                if (error)
                    *error = QStringLiteral("invalid method '%1' in service '%2'")
                                 .arg(method, id);
                return false;
            }
        }
        const QSet<QString> uniqueMethods(methods.cbegin(), methods.cend());
        if (uniqueMethods.size() != methods.size()) {
            if (error)
                *error = QStringLiteral("service '%1' methods must be unique")
                             .arg(id);
            return false;
        }
        if (candidates.contains(id)) {
            if (error)
                *error = QStringLiteral("duplicate service '%1'").arg(id);
            return false;
        }
        candidates.insert(id, {normalized(pluginId), version, methods, root, provider});
    }

    QWriteLocker locker(&m_lock);
    for (auto it = candidates.cbegin(); it != candidates.cend(); ++it) {
        if (m_services.contains(it.key())) {
            if (error)
                *error = QStringLiteral("service '%1' is already registered").arg(it.key());
            return false;
        }
    }
    for (auto it = candidates.cbegin(); it != candidates.cend(); ++it)
        m_services.insert(it.key(), it.value());
    return true;
}

void PluginExtensionRegistry::unregisterPlugin(const QString& pluginId)
{
    const QString id = normalized(pluginId);
    QWriteLocker locker(&m_lock);
    for (auto it = m_gscript.begin(); it != m_gscript.end();) {
        if (it->descriptor.pluginId == id)
            it = m_gscript.erase(it);
        else
            ++it;
    }
    for (auto it = m_devices.begin(); it != m_devices.end();) {
        if (it->pluginId == id)
            it = m_devices.erase(it);
        else
            ++it;
    }
    for (auto it = m_services.begin(); it != m_services.end();) {
        if (it->pluginId == id)
            it = m_services.erase(it);
        else
            ++it;
    }
}

void PluginExtensionRegistry::clearForTests()
{
    QWriteLocker locker(&m_lock);
    m_gscript.clear();
    m_devices.clear();
    m_services.clear();
    m_events.clear();
    m_nextEventSequence = 1;
}

QVector<PluginGScriptPrimitive> PluginExtensionRegistry::gscriptPrimitives() const
{
    QReadLocker locker(&m_lock);
    QVector<PluginGScriptPrimitive> result;
    result.reserve(m_gscript.size());
    for (const GScriptRecord& record : m_gscript)
        result.append(record.descriptor);
    std::sort(result.begin(), result.end(),
              [](const PluginGScriptPrimitive& left,
                 const PluginGScriptPrimitive& right) {
                  return left.name < right.name;
              });
    return result;
}

bool PluginExtensionRegistry::hasGScriptPrimitive(const QString& name) const
{
    QReadLocker locker(&m_lock);
    return m_gscript.contains(normalized(name));
}

bool PluginExtensionRegistry::executeGScriptPrimitive(
    const QString& name, const QVariantList& arguments, QVariant* result,
    QString* error) const
{
    GScriptRecord record;
    {
        QReadLocker locker(&m_lock);
        const auto it = m_gscript.constFind(normalized(name));
        if (it == m_gscript.cend()) {
            if (error)
                *error = QStringLiteral("G-Script primitive '%1' is not registered")
                             .arg(name);
            return false;
        }
        record = it.value();
    }
    if (!record.root || !record.provider) {
        if (error)
            *error = QStringLiteral("G-Script provider is no longer available");
        return false;
    }

    bool accepted = false;
    QString callError;
    QVariant callResult;
    invokeOnOwner(record.root, [&]() {
        try {
            accepted = record.provider->executeGScriptPrimitive(
                record.descriptor.name, arguments, &callResult, &callError);
        } catch (const std::exception& exception) {
            callError = QString::fromUtf8(exception.what());
        } catch (...) {
            callError = QStringLiteral("plugin primitive raised an unknown exception");
        }
    });
    if (result)
        *result = callResult;
    if (!accepted && error)
        *error = callError.isEmpty() ? QStringLiteral("plugin rejected the primitive")
                                     : callError;
    return accepted;
}

QStringList PluginExtensionRegistry::deviceIds() const
{
    QReadLocker locker(&m_lock);
    QStringList result = m_devices.keys();
    result.sort(Qt::CaseInsensitive);
    return result;
}

bool PluginExtensionRegistry::ownsDevice(const QString& pluginId,
                                         const QString& deviceId) const
{
    QReadLocker locker(&m_lock);
    const auto it = m_devices.constFind(normalized(deviceId));
    return it != m_devices.cend() && it->pluginId == normalized(pluginId);
}

bool PluginExtensionRegistry::hasDevice(const QString& deviceId) const
{
    QReadLocker locker(&m_lock);
    return m_devices.contains(normalized(deviceId));
}

bool PluginExtensionRegistry::dispatchDeviceCommand(
    const QString& deviceId, const QString& command, quint64 requestId,
    QString* error) const
{
    DeviceRecord record;
    {
        QReadLocker locker(&m_lock);
        const auto it = m_devices.constFind(normalized(deviceId));
        if (it == m_devices.cend()) {
            if (error)
                *error = QStringLiteral("plugin device '%1' is not registered")
                             .arg(deviceId);
            return false;
        }
        record = it.value();
    }
    if (!record.root || !record.provider) {
        if (error)
            *error = QStringLiteral("device provider is no longer available");
        return false;
    }
    bool accepted = false;
    QString callError;
    invokeOnOwner(record.root, [&]() {
        try {
            accepted = record.provider->submitDeviceCommand(
                normalized(deviceId), command, requestId, &callError);
        } catch (...) {
            callError = QStringLiteral("device provider raised an exception");
        }
    });
    if (!accepted && error)
        *error = callError.isEmpty() ? QStringLiteral("device provider rejected command")
                                     : callError;
    return accepted;
}

QStringList PluginExtensionRegistry::serviceIds() const
{
    QReadLocker locker(&m_lock);
    QStringList result = m_services.keys();
    result.sort(Qt::CaseInsensitive);
    return result;
}

QVariantList PluginExtensionRegistry::serviceDescriptors() const
{
    QVector<QVariantMap> values;
    {
        QReadLocker locker(&m_lock);
        values.reserve(m_services.size());
        for (auto it = m_services.cbegin(); it != m_services.cend(); ++it) {
            values.append({
                {QStringLiteral("id"), it.key()},
                {QStringLiteral("version"), it->version},
                {QStringLiteral("methods"), it->methods},
                {QStringLiteral("providerPluginId"), it->pluginId},
            });
        }
    }
    std::sort(values.begin(), values.end(),
              [](const QVariantMap& left, const QVariantMap& right) {
                  return left.value(QStringLiteral("id")).toString() <
                         right.value(QStringLiteral("id")).toString();
              });
    QVariantList result;
    result.reserve(values.size());
    for (const QVariantMap& value : values)
        result.append(value);
    return result;
}

bool PluginExtensionRegistry::invokeService(
    const QString& serviceId, const QString& method,
    const QVariantMap& request, QVariantMap* response, QString* error) const
{
    ServiceRecord record;
    {
        QReadLocker locker(&m_lock);
        const auto it = m_services.constFind(normalized(serviceId));
        if (it == m_services.cend()) {
            if (error)
                *error = QStringLiteral("service '%1' is not registered")
                             .arg(serviceId);
            return false;
        }
        record = it.value();
    }
    const QString normalizedMethod = normalized(method);
    if (!record.methods.contains(normalizedMethod)) {
        if (error)
            *error = QStringLiteral("service '%1' does not provide method '%2'")
                         .arg(serviceId, method);
        return false;
    }
    if (!record.root || !record.provider) {
        if (error)
            *error = QStringLiteral("service provider is no longer available");
        return false;
    }
    bool accepted = false;
    QString callError;
    QVariantMap callResponse;
    invokeOnOwner(record.root, [&]() {
        try {
            accepted = record.provider->invokeService(
                normalized(serviceId), normalizedMethod, request,
                &callResponse, &callError);
        } catch (...) {
            callError = QStringLiteral("service provider raised an exception");
        }
    });
    if (response)
        *response = callResponse;
    if (!accepted && error)
        *error = callError.isEmpty() ? QStringLiteral("service provider rejected request")
                                     : callError;
    return accepted;
}

quint64 PluginExtensionRegistry::publishEvent(
    const QString& pluginId, const QString& topic, const QVariantMap& payload,
    QString* error)
{
    const QString normalizedTopic = normalized(topic);
    if (!extensionIdPattern().match(normalizedTopic).hasMatch()) {
        if (error)
            *error = QStringLiteral("event topic must be a stable lowercase identifier");
        return 0;
    }
    QWriteLocker locker(&m_lock);
    const quint64 sequence = m_nextEventSequence++;
    m_events.append({
        {QStringLiteral("sequence"), QVariant::fromValue(sequence)},
        {QStringLiteral("pluginId"), normalized(pluginId)},
        {QStringLiteral("topic"), normalizedTopic},
        {QStringLiteral("timestamp"),
         QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs)},
        {QStringLiteral("payload"), payload},
    });
    constexpr int MaximumEvents = 1024;
    if (m_events.size() > MaximumEvents)
        m_events.remove(0, m_events.size() - MaximumEvents);
    return sequence;
}

QVariantList PluginExtensionRegistry::eventsSince(
    quint64 afterSequence, const QString& topic, int maximumCount) const
{
    const QString normalizedTopic = normalized(topic);
    const int limit = qBound(1, maximumCount, 1000);
    QVariantList result;
    QReadLocker locker(&m_lock);
    for (const QVariantMap& event : m_events) {
        if (event.value(QStringLiteral("sequence")).toULongLong() <= afterSequence)
            continue;
        if (!normalizedTopic.isEmpty() &&
            event.value(QStringLiteral("topic")).toString() != normalizedTopic)
            continue;
        result.append(event);
        if (result.size() >= limit)
            break;
    }
    return result;
}
