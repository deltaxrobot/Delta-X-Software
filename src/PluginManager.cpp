#include "PluginManager.h"

#include "sdk/DeltaXCommandProvider.h"
#include "sdk/DeltaXPanelProvider.h"
#include "sdk/DeltaXPlugin.h"
#include "sdk/DeltaXPluginMetadata.h"
#include "sdk/DeltaXPluginV2.h"

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
    DeltaXPanelProvider* panel = nullptr;
    DeltaXCommandProvider* commands = nullptr;
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
        descriptor.displayName = descriptor.id;
        descriptor.version =
            DeltaXPluginContract::pluginVersion(loaderMetadata);
        descriptor.capabilities =
            DeltaXPluginContract::capabilities(loaderMetadata);

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

        if (m_disabledPluginIds.contains(descriptor.id)) {
            descriptor.state = PluginDescriptor::State::Disabled;
            descriptor.error = QStringLiteral("disabled by user settings");
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
        if (descriptor.apiVersion == DeltaXPluginContract::LegacyApiVersion &&
            !legacy) {
            const QString error = QStringLiteral(
                "plugin does not implement the DeltaXPlugin v1 interface");
            loader->unload();
            reject(descriptor, error);
            continue;
        }
        if (descriptor.apiVersion == DeltaXPluginContract::SupportedApiVersion &&
            !modern) {
            const QString error = QStringLiteral(
                "plugin does not implement the DeltaXPluginV2 interface");
            loader->unload();
            reject(descriptor, error);
            continue;
        }

        DeltaXPanelProvider* panel = qobject_cast<DeltaXPanelProvider*>(root);
        DeltaXCommandProvider* commands =
            qobject_cast<DeltaXCommandProvider*>(root);

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
        auto entry = std::make_unique<Entry>();
        entry->descriptor = descriptor;
        entry->loader = std::move(loader);
        entry->root = root;
        entry->legacy = legacy;
        entry->modern = modern;
        entry->panel = panel;
        entry->commands = commands;
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
        entry->root = nullptr;
        entry->legacy = nullptr;
        entry->modern = nullptr;
        entry->panel = nullptr;
        entry->commands = nullptr;

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
    for (const auto& entry : m_entries)
        result.append(entry->descriptor.id);
    return result;
}

QObject* PluginManager::instance(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry ? entry->root : nullptr;
}

DeltaXPlugin* PluginManager::legacyPlugin(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry ? entry->legacy : nullptr;
}

DeltaXPluginV2* PluginManager::pluginV2(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry ? entry->modern : nullptr;
}

DeltaXPanelProvider* PluginManager::panelProvider(const QString& pluginId) const
{
    Entry* entry = findEntry(pluginId);
    return entry ? entry->panel : nullptr;
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
        settings.beginGroup(settingsScope(projectScope, entry->descriptor.id));
        try {
            if (entry->modern)
                entry->modern->loadSettings(settings);
            else if (entry->legacy)
                entry->legacy->LoadSettings(&settings);
        } catch (const std::exception& exception) {
            emit diagnostic(QStringLiteral("Could not load settings for '%1': %2")
                                .arg(entry->descriptor.id,
                                     QString::fromUtf8(exception.what())));
        } catch (...) {
            emit diagnostic(QStringLiteral(
                "Could not load settings for '%1': unknown exception")
                                .arg(entry->descriptor.id));
        }
        settings.endGroup();
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
