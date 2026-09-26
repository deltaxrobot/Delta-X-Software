#include "PluginManager.h"

#include "PluginExtensionRegistry.h"
#include "PluginHostContext.h"

#include "sdk/DeltaXCommandProvider.h"
#include "sdk/DeltaXDeviceProvider.h"
#include "sdk/DeltaXGScriptProvider.h"
#include "sdk/DeltaXPanelProvider.h"
#include "sdk/DeltaXPlugin.h"
#include "sdk/DeltaXPluginMetadata.h"
#include "sdk/DeltaXPluginV2.h"
#include "sdk/DeltaXPluginV3.h"
#include "sdk/DeltaXServiceProvider.h"

#include <QDir>
#include <QFileInfo>
#include <QLibrary>
#include <QPluginLoader>
#include <QRegularExpression>

#include <algorithm>
#include <exception>

struct PluginManager::Entry
{
    PluginDescriptor descriptor;
    std::unique_ptr<QPluginLoader> loader;
    QObject* root = nullptr;
    DeltaXPlugin* legacy = nullptr;
    DeltaXPluginV2* modern = nullptr;
    DeltaXPluginV3* v3 = nullptr;
    DeltaXPanelProvider* panel = nullptr;
    DeltaXCommandProvider* commands = nullptr;
    DeltaXGScriptProvider* gscript = nullptr;
    DeltaXDeviceProvider* devices = nullptr;
    DeltaXServiceProvider* services = nullptr;
    std::unique_ptr<PluginHostContext> context;
    bool initialized = false;
    bool active = false;
};

bool PluginDescriptor::hasCapability(const QString& capability) const
{
    return capabilities.contains(capability.trimmed().toLower());
}

QString PluginDescriptor::stateName() const
{
    switch (state) {
    case State::Disabled:
        return QStringLiteral("disabled");
    case State::Rejected:
        return QStringLiteral("rejected");
    case State::Loaded:
        return QStringLiteral("loaded");
    case State::Unloaded:
        return QStringLiteral("unloaded");
    case State::UnloadFailed:
        return QStringLiteral("unload-failed");
    }
    return QStringLiteral("unknown");
}

PluginManager::PluginManager(QObject* parent)
    : QObject(parent)
{
}

PluginManager::~PluginManager()
{
    shutdown();
}

void PluginManager::setDisabledPluginIds(const QSet<QString>& pluginIds)
{
    m_disabledPluginIds.clear();
    for (const QString& id : pluginIds) {
        const QString normalized = normalizedId(id);
        if (!normalized.isEmpty())
            m_disabledPluginIds.insert(normalized);
    }
}

void PluginManager::setEnabledPluginIds(const QSet<QString>& pluginIds)
{
    m_enabledPluginIds.clear();
    for (const QString& id : pluginIds) {
        const QString normalized = normalizedId(id);
        if (!normalized.isEmpty())
            m_enabledPluginIds.insert(normalized);
    }
}

void PluginManager::setGrantedPermissions(
    const QHash<QString, QSet<QString>>& grantedPermissions)
{
    m_grantedPermissions.clear();
    for (auto it = grantedPermissions.cbegin();
         it != grantedPermissions.cend(); ++it) {
        const QString pluginId = normalizedId(it.key());
        if (pluginId.isEmpty())
            continue;
        QSet<QString> permissions;
        for (const QString& value : it.value()) {
            const QString permission = value.trimmed().toLower();
            if (DeltaXPluginContract::isKnownPermission(permission))
                permissions.insert(permission);
        }
        m_grantedPermissions.insert(pluginId, permissions);
    }
}

void PluginManager::setHostServices(const PluginHostServices& services)
{
    m_hostServices = services;
}

void PluginManager::loadFromDirectories(const QStringList& directories)
{
    shutdown();
    m_descriptors.clear();

    QStringList trustedRoots;
    for (const QString& directory : directories) {
        const QString root = canonicalDirectory(directory);
        if (!root.isEmpty() && !trustedRoots.contains(root))
            trustedRoots.append(root);
    }

    QStringList candidates;
    for (const QString& root : trustedRoots) {
        const QDir directory(root);
        const QFileInfoList files = directory.entryInfoList(
            QDir::Files | QDir::Readable | QDir::NoDotAndDotDot,
            QDir::Name | QDir::IgnoreCase);
        for (const QFileInfo& file : files) {
            if (QLibrary::isLibrary(file.fileName()) &&
                isInsideDirectory(file.canonicalFilePath(), root)) {
                candidates.append(file.canonicalFilePath());
            }
        }
    }
    candidates.removeDuplicates();
    candidates.sort(Qt::CaseInsensitive);

    QSet<QString> claimedIds;
    for (const QString& filePath : candidates) {
        auto loader = std::make_unique<QPluginLoader>(filePath);
        const QJsonObject loaderMetadata = loader->metaData();

        PluginDescriptor descriptor;
        descriptor.filePath = filePath;
        descriptor.apiVersion =
            DeltaXPluginContract::declaredApiVersion(loaderMetadata);
        descriptor.id = normalizedId(
            DeltaXPluginContract::pluginId(loaderMetadata));
        if (descriptor.id.isEmpty())
            descriptor.id = fallbackId(filePath);
        descriptor.displayName =
            DeltaXPluginContract::pluginDisplayName(loaderMetadata);
        if (descriptor.displayName.isEmpty())
            descriptor.displayName = descriptor.id;
        descriptor.version =
            DeltaXPluginContract::pluginVersion(loaderMetadata);
        descriptor.experimental =
            DeltaXPluginContract::stability(loaderMetadata) ==
            QStringLiteral("experimental");
        descriptor.defaultEnabled =
            DeltaXPluginContract::defaultEnabled(loaderMetadata);
        descriptor.capabilities =
            DeltaXPluginContract::capabilities(loaderMetadata);
        descriptor.requestedPermissions =
            DeltaXPluginContract::requestedPermissions(loaderMetadata);
        const QSet<QString> configuredGrants =
            m_grantedPermissions.value(descriptor.id);
        for (const QString& permission : descriptor.requestedPermissions) {
            if (configuredGrants.contains(permission))
                descriptor.grantedPermissions.append(permission);
            else
                descriptor.missingPermissions.append(permission);
        }

        const QString contractError =
            DeltaXPluginContract::compatibilityError(loaderMetadata);
        if (!contractError.isEmpty()) {
            reject(descriptor, contractError);
            continue;
        }
        if (descriptor.id.isEmpty()) {
            reject(descriptor, QStringLiteral("plugin id could not be determined"));
            continue;
        }
        if (claimedIds.contains(descriptor.id)) {
            reject(descriptor,
                   QStringLiteral("duplicate plugin id '%1'").arg(descriptor.id));
            continue;
        }
        claimedIds.insert(descriptor.id);

        if (m_disabledPluginIds.contains(descriptor.id) ||
            (!descriptor.defaultEnabled &&
             !m_enabledPluginIds.contains(descriptor.id))) {
            descriptor.state = PluginDescriptor::State::Disabled;
            descriptor.error = m_disabledPluginIds.contains(descriptor.id)
                ? QStringLiteral("disabled by user settings")
                : QStringLiteral("experimental plugin disabled by default");
            m_descriptors.append(descriptor);
            emit diagnostic(QStringLiteral("Plugin '%1' is disabled")
                                .arg(descriptor.id));
            continue;
        }

        if (!loader->load()) {
            reject(descriptor, loader->errorString());
            continue;
        }

        QObject* root = loader->instance();
        DeltaXPlugin* legacy = qobject_cast<DeltaXPlugin*>(root);
        DeltaXPluginV2* modern = qobject_cast<DeltaXPluginV2*>(root);
        DeltaXPluginV3* v3 = qobject_cast<DeltaXPluginV3*>(root);
        if (descriptor.apiVersion == DeltaXPluginContract::LegacyApiVersion &&
            !legacy) {
            const QString error = QStringLiteral(
                "plugin does not implement the DeltaXPlugin v1 interface");
            loader->unload();
            reject(descriptor, error);
            continue;
        }
        if (descriptor.apiVersion >= DeltaXPluginContract::VersionedApiVersion &&
            !modern) {
            const QString error = QStringLiteral(
                "plugin does not implement the DeltaXPluginV2 interface");
            loader->unload();
            reject(descriptor, error);
            continue;
        }
        if (descriptor.apiVersion == DeltaXPluginContract::SupportedApiVersion &&
            !v3) {
            const QString error = QStringLiteral(
                "plugin does not implement the DeltaXPluginV3 interface");
            loader->unload();
            reject(descriptor, error);
            continue;
        }

        DeltaXPanelProvider* panel = qobject_cast<DeltaXPanelProvider*>(root);
        DeltaXCommandProvider* commands =
            qobject_cast<DeltaXCommandProvider*>(root);
        DeltaXGScriptProvider* gscript =
            qobject_cast<DeltaXGScriptProvider*>(root);
        DeltaXDeviceProvider* devices =
            qobject_cast<DeltaXDeviceProvider*>(root);
        DeltaXServiceProvider* services =
            qobject_cast<DeltaXServiceProvider*>(root);

        QString runtimeError;
        try {
            if (modern) {
                const QString runtimeId = normalizedId(modern->id());
                QStringList runtimeCapabilities;
                for (const QString& capability : modern->capabilities()) {
                    const QString normalized = capability.trimmed().toLower();
                    if (!normalized.isEmpty() &&
                        !runtimeCapabilities.contains(normalized)) {
                        runtimeCapabilities.append(normalized);
                    }
                }
                runtimeCapabilities.sort();
                QStringList metadataCapabilities = descriptor.capabilities;
                metadataCapabilities.sort();

                if (runtimeId != descriptor.id) {
                    runtimeError = QStringLiteral(
                        "runtime id '%1' does not match metadata id '%2'")
                                       .arg(runtimeId, descriptor.id);
                } else if (modern->version().trimmed() != descriptor.version) {
                    runtimeError = QStringLiteral(
                        "runtime version does not match metadata pluginVersion");
                } else if (runtimeCapabilities != metadataCapabilities) {
                    runtimeError = QStringLiteral(
                        "runtime capabilities do not match metadata capabilities");
                } else if (descriptor.hasCapability(QStringLiteral("panel")) &&
                           !panel) {
                    runtimeError = QStringLiteral(
                        "capability 'panel' requires DeltaXPanelProvider");
                } else if (descriptor.hasCapability(QStringLiteral("commands")) &&
                           !commands) {
                    runtimeError = QStringLiteral(
                        "capability 'commands' requires DeltaXCommandProvider");
                } else if (descriptor.hasCapability(
                               QStringLiteral("gscript.primitives")) &&
                           !gscript) {
                    runtimeError = QStringLiteral(
                        "capability 'gscript.primitives' requires DeltaXGScriptProvider");
                } else if (descriptor.hasCapability(
                               QStringLiteral("devices.provider")) &&
                           !devices) {
                    runtimeError = QStringLiteral(
                        "capability 'devices.provider' requires DeltaXDeviceProvider");
                } else if (descriptor.hasCapability(
                               QStringLiteral("services.provider")) &&
                           !services) {
                    runtimeError = QStringLiteral(
                        "capability 'services.provider' requires DeltaXServiceProvider");
                }
                if (runtimeError.isEmpty() && descriptor.apiVersion ==
                        DeltaXPluginContract::SupportedApiVersion) {
                    const QHash<QString, QString> capabilityPermissions = {
                        {QStringLiteral("gscript.primitives"),
                         QStringLiteral("gscript.register")},
                        {QStringLiteral("devices.provider"),
                         QStringLiteral("devices.provide")},
                        {QStringLiteral("services.provider"),
                         QStringLiteral("services.provide")},
                    };
                    for (auto it = capabilityPermissions.cbegin();
                         it != capabilityPermissions.cend(); ++it) {
                        if (descriptor.hasCapability(it.key()) &&
                            !descriptor.requestedPermissions.contains(it.value())) {
                            runtimeError = QStringLiteral(
                                "capability '%1' must request permission '%2'")
                                               .arg(it.key(), it.value());
                            break;
                        }
                    }
                }
                descriptor.displayName = modern->displayName().trimmed();
                if (descriptor.displayName.isEmpty())
                    descriptor.displayName = descriptor.id;
            } else {
                descriptor.displayName = legacy->GetTitle().trimmed();
                if (descriptor.displayName.isEmpty())
                    descriptor.displayName = legacy->GetName().trimmed();
                if (descriptor.displayName.isEmpty())
                    descriptor.displayName = descriptor.id;
                descriptor.capabilities = {
                    QStringLiteral("legacy"), QStringLiteral("panel"),
                    QStringLiteral("commands")};
            }
        } catch (const std::exception& exception) {
            runtimeError = QStringLiteral("plugin contract method raised: %1")
                               .arg(QString::fromUtf8(exception.what()));
        } catch (...) {
            runtimeError = QStringLiteral(
                "plugin contract method raised an unknown exception");
        }
        if (!runtimeError.isEmpty()) {
            loader->unload();
            reject(descriptor, runtimeError);
            continue;
        }

        descriptor.state = PluginDescriptor::State::Loaded;
        descriptor.active = !v3;
        auto entry = std::make_unique<Entry>();
        entry->descriptor = descriptor;
        entry->loader = std::move(loader);
        entry->root = root;
        entry->legacy = legacy;
        entry->modern = modern;
        entry->v3 = v3;
        entry->panel = panel;
        entry->commands = commands;
        entry->gscript = gscript;
        entry->devices = devices;
        entry->services = services;
        entry->active = !v3;
        m_entries.push_back(std::move(entry));
        m_descriptors.append(descriptor);
        emit diagnostic(QStringLiteral("Loaded plugin '%1' v%2 (API v%3)")
                            .arg(descriptor.id,
                                 descriptor.version.isEmpty()
                                     ? QStringLiteral("legacy")
                                     : descriptor.version)
                            .arg(descriptor.apiVersion));
    }
}

bool PluginManager::shutdown()
{
    bool success = true;
    for (auto it = m_entries.rbegin(); it != m_entries.rend(); ++it) {
        Entry* entry = it->get();
        if (entry->v3 && entry->initialized) {
            try {
                if (entry->active)
                    entry->v3->stop();
            } catch (...) {
                success = false;
                emit diagnostic(QStringLiteral("Plugin '%1' stop raised an exception")
                                    .arg(entry->descriptor.id));
            }
        }
        PluginExtensionRegistry::instance().unregisterPlugin(
            entry->descriptor.id);
        if (entry->context)
            entry->context->invalidate();
        entry->root = nullptr;
        entry->legacy = nullptr;
        entry->modern = nullptr;
        entry->v3 = nullptr;
        entry->panel = nullptr;
        entry->commands = nullptr;
        entry->gscript = nullptr;
        entry->devices = nullptr;
        entry->services = nullptr;
        entry->context.reset();

        const bool unloaded = !entry->loader->isLoaded() || entry->loader->unload();
        for (PluginDescriptor& descriptor : m_descriptors) {
            if (descriptor.filePath != entry->descriptor.filePath)
                continue;
            descriptor.state = unloaded
                ? PluginDescriptor::State::Unloaded
                : PluginDescriptor::State::UnloadFailed;
            if (!unloaded)
                descriptor.error = entry->loader->errorString();
            break;
        }
        if (!unloaded) {
            success = false;
            emit diagnostic(QStringLiteral("Could not unload plugin '%1': %2")
                                .arg(entry->descriptor.id,
                                     entry->loader->errorString()));
        }
    }
    m_entries.clear();
    return success;
}

QVector<PluginDescriptor> PluginManager::descriptors() const
{
    return m_descriptors;
}

QStringList PluginManager::loadedPluginIds() const
{
    QStringList result;
    for (const auto& entry : m_entries) {
        if (entry->descriptor.state == PluginDescriptor::State::Loaded)
            result.append(entry->descriptor.id);
    }
    return result;
}

QObject* PluginManager::instance(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry && entry->descriptor.state == PluginDescriptor::State::Loaded &&
            (!entry->v3 || entry->active)
        ? entry->root : nullptr;
}

DeltaXPlugin* PluginManager::legacyPlugin(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry && entry->descriptor.state == PluginDescriptor::State::Loaded &&
            (!entry->v3 || entry->active)
        ? entry->legacy : nullptr;
}

DeltaXPluginV2* PluginManager::pluginV2(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry && entry->descriptor.state == PluginDescriptor::State::Loaded &&
            (!entry->v3 || entry->active)
        ? entry->modern : nullptr;
}

DeltaXPluginV3* PluginManager::pluginV3(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry && entry->descriptor.state == PluginDescriptor::State::Loaded &&
            (!entry->v3 || entry->active)
        ? entry->v3 : nullptr;
}

DeltaXPanelProvider* PluginManager::panelProvider(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry && entry->descriptor.state == PluginDescriptor::State::Loaded &&
            (!entry->v3 || entry->active)
        ? entry->panel : nullptr;
}

bool PluginManager::executeCommand(const QString& pluginId,
                                   const QString& command,
                                   const QVariantMap& arguments,
                                   QVariantMap* result,
                                   QString* error)
{
    Entry* entry = findEntry(pluginId);
    if (!entry) {
        if (error)
            *error = QStringLiteral("plugin '%1' is not loaded").arg(pluginId);
        return false;
    }
    if (entry->descriptor.state != PluginDescriptor::State::Loaded ||
        (entry->v3 && !entry->active)) {
        if (error)
            *error = QStringLiteral("plugin '%1' is not active").arg(pluginId);
        return false;
    }

    try {
        if (entry->commands)
            return entry->commands->executeCommand(command, arguments, result, error);
        if (entry->legacy) {
            if (!arguments.isEmpty()) {
                if (error) {
                    *error = QStringLiteral(
                        "legacy plugins do not accept structured arguments");
                }
                return false;
            }
            entry->legacy->ProcessCommand(command);
            if (result)
                result->insert(QStringLiteral("accepted"), true);
            return true;
        }
    } catch (const std::exception& exception) {
        if (error)
            *error = QString::fromUtf8(exception.what());
        return false;
    } catch (...) {
        if (error)
            *error = QStringLiteral("plugin command raised an unknown exception");
        return false;
    }

    if (error)
        *error = QStringLiteral("plugin does not provide commands");
    return false;
}

void PluginManager::loadSettings(QSettings& settings,
                                 const QString& projectScope)
{
    for (const auto& entry : m_entries) {
        QString activationError;
        settings.beginGroup(settingsScope(projectScope, entry->descriptor.id));
        try {
            if (entry->modern)
                entry->modern->loadSettings(settings);
            else if (entry->legacy)
                entry->legacy->LoadSettings(&settings);
        } catch (const std::exception& exception) {
            activationError = QString::fromUtf8(exception.what());
            emit diagnostic(QStringLiteral("Could not load settings for '%1': %2")
                                .arg(entry->descriptor.id,
                                     QString::fromUtf8(exception.what())));
        } catch (...) {
            activationError = QStringLiteral("settings method raised an unknown exception");
            emit diagnostic(QStringLiteral(
                "Could not load settings for '%1': unknown exception")
                                .arg(entry->descriptor.id));
        }
        settings.endGroup();

        if (!entry->v3 || entry->initialized)
            continue;

        const QSet<QString> grants = m_grantedPermissions.value(
            entry->descriptor.id);
        entry->context = std::make_unique<PluginHostContext>(
            entry->descriptor.id, entry->descriptor.requestedPermissions,
            grants, m_hostServices);
        if (activationError.isEmpty()) {
            try {
                entry->initialized = entry->v3->initialize(
                    entry->context.get(), &activationError);
                if (entry->initialized)
                    entry->active = entry->v3->start(&activationError);
            } catch (const std::exception& exception) {
                activationError = QString::fromUtf8(exception.what());
                entry->active = false;
            } catch (...) {
                activationError = QStringLiteral(
                    "plugin lifecycle raised an unknown exception");
                entry->active = false;
            }
        }

        if (entry->active &&
            entry->descriptor.hasCapability(QStringLiteral("gscript.primitives")) &&
            entry->gscript &&
            grants.contains(QStringLiteral("gscript.register"))) {
            entry->active = PluginExtensionRegistry::instance()
                                .registerGScriptProvider(
                                    entry->descriptor.id, entry->root,
                                    entry->gscript, &activationError);
        }
        if (entry->active &&
            entry->descriptor.hasCapability(QStringLiteral("devices.provider")) &&
            entry->devices &&
            grants.contains(QStringLiteral("devices.provide"))) {
            entry->active = PluginExtensionRegistry::instance()
                                .registerDeviceProvider(
                                    entry->descriptor.id, entry->root,
                                    entry->devices, &activationError);
            if (entry->active && m_hostServices.registerDevice) {
                try {
                    PluginExtensionRegistry& registry =
                        PluginExtensionRegistry::instance();
                    for (const QString& deviceId : registry.deviceIds()) {
                        if (registry.ownsDevice(entry->descriptor.id, deviceId))
                            m_hostServices.registerDevice(deviceId);
                    }
                } catch (...) {
                    activationError = QStringLiteral(
                        "host device registration failed during activation");
                    entry->active = false;
                }
            }
        }
        if (entry->active &&
            entry->descriptor.hasCapability(QStringLiteral("services.provider")) &&
            entry->services &&
            grants.contains(QStringLiteral("services.provide"))) {
            entry->active = PluginExtensionRegistry::instance()
                                .registerServiceProvider(
                                    entry->descriptor.id, entry->root,
                                    entry->services, &activationError);
        }

        for (PluginDescriptor& descriptor : m_descriptors) {
            if (descriptor.filePath != entry->descriptor.filePath)
                continue;
            descriptor.active = entry->active;
            entry->descriptor.active = entry->active;
            if (!entry->active) {
                descriptor.state = PluginDescriptor::State::Rejected;
                entry->descriptor.state = PluginDescriptor::State::Rejected;
                descriptor.error = activationError.isEmpty()
                    ? QStringLiteral("plugin failed to activate")
                    : activationError;
                entry->descriptor.error = descriptor.error;
            }
            break;
        }
        if (!entry->active) {
            PluginExtensionRegistry::instance().unregisterPlugin(
                entry->descriptor.id);
            if (entry->initialized) {
                try {
                    entry->v3->stop();
                } catch (...) {
                }
            }
            entry->context->invalidate();
            emit diagnostic(QStringLiteral("Plugin '%1' activation failed: %2")
                                .arg(entry->descriptor.id,
                                     entry->descriptor.error));
        } else if (!entry->descriptor.missingPermissions.isEmpty()) {
            emit diagnostic(QStringLiteral(
                "Plugin '%1' is active with denied permissions: %2")
                                .arg(entry->descriptor.id,
                                     entry->descriptor.missingPermissions.join(", ")));
        }
    }
}

void PluginManager::saveSettings(QSettings& settings,
                                 const QString& projectScope) const
{
    for (const auto& entry : m_entries) {
        settings.beginGroup(settingsScope(projectScope, entry->descriptor.id));
        try {
            if (entry->modern)
                entry->modern->saveSettings(settings);
            else if (entry->legacy)
                entry->legacy->SaveSettings(&settings);
        } catch (...) {
            // Destructors call this path; plugin exceptions must never escape.
        }
        settings.endGroup();
    }
    settings.sync();
}

PluginManager::Entry* PluginManager::findEntry(const QString& pluginId) const
{
    const QString id = normalizedId(pluginId);
    for (const auto& entry : m_entries) {
        if (entry->descriptor.id == id)
            return entry.get();
    }
    return nullptr;
}

QString PluginManager::normalizedId(const QString& value)
{
    return value.trimmed().toLower();
}

QString PluginManager::fallbackId(const QString& filePath)
{
    QString id = QFileInfo(filePath).completeBaseName().toLower();
#if defined(Q_OS_LINUX) || defined(Q_OS_MACOS)
    if (id.startsWith(QStringLiteral("lib")))
        id.remove(0, 3);
#endif
    id.replace(QRegularExpression(QStringLiteral("[^a-z0-9._-]+")),
               QStringLiteral("-"));
    return id;
}

QString PluginManager::canonicalDirectory(const QString& directory)
{
    const QFileInfo info(directory);
    if (!info.exists() || !info.isDir())
        return {};
    return QDir::cleanPath(info.canonicalFilePath());
}

bool PluginManager::isInsideDirectory(const QString& filePath,
                                      const QString& canonicalDirectory)
{
    if (filePath.isEmpty() || canonicalDirectory.isEmpty())
        return false;
    const QString file = QDir::cleanPath(filePath);
    QString root = QDir::cleanPath(canonicalDirectory);
    // QDir::cleanPath uses forward slashes even on Windows.
    if (!root.endsWith(QLatin1Char('/')))
        root += QLatin1Char('/');
#ifdef Q_OS_WIN
    return file.startsWith(root, Qt::CaseInsensitive);
#else
    return file.startsWith(root, Qt::CaseSensitive);
#endif
}

QString PluginManager::settingsScope(const QString& projectScope,
                                     const QString& pluginId)
{
    QString project = projectScope.trimmed();
    if (project.isEmpty())
        project = QStringLiteral("default");
    project.replace(QLatin1Char('/'), QLatin1Char('_'));
    project.replace(QLatin1Char('\\'), QLatin1Char('_'));
    return QStringLiteral("PluginSystem/Projects/%1/%2")
        .arg(project, pluginId);
}

void PluginManager::reject(const PluginDescriptor& candidate,
                           const QString& error)
{
    PluginDescriptor descriptor = candidate;
    descriptor.state = PluginDescriptor::State::Rejected;
    descriptor.error = error.trimmed().isEmpty()
        ? QStringLiteral("unknown plugin loader error")
        : error.trimmed();
    m_descriptors.append(descriptor);
    emit diagnostic(QStringLiteral("Rejected plugin '%1': %2")
                        .arg(descriptor.id.isEmpty()
                                 ? QFileInfo(descriptor.filePath).fileName()
                                 : descriptor.id,
                             descriptor.error));
}
