#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QSet>
#include <QSettings>
#include <QStringList>
#include <QVariantMap>
#include <QVector>

#include <memory>
#include <vector>

class DeltaXCommandProvider;
class DeltaXPanelProvider;
class DeltaXPlugin;
class DeltaXPluginV2;

struct PluginDescriptor
{
    enum class State {
        Disabled,
        Rejected,
        Loaded,
        Unloaded,
        UnloadFailed
    };

    QString id;
    QString displayName;
    QString version;
    int apiVersion = 0;
    QStringList capabilities;
    QString filePath;
    State state = State::Rejected;
    QString error;

    bool hasCapability(const QString& capability) const;
    QString stateName() const;
};

class PluginManager final : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject* parent = nullptr);
    ~PluginManager() override;

    void setDisabledPluginIds(const QSet<QString>& pluginIds);
    void loadFromDirectories(const QStringList& directories);
    bool shutdown();

    QVector<PluginDescriptor> descriptors() const;
    QStringList loadedPluginIds() const;
    QObject* instance(const QString& pluginId) const;
    DeltaXPlugin* legacyPlugin(const QString& pluginId) const;
    DeltaXPluginV2* pluginV2(const QString& pluginId) const;
    DeltaXPanelProvider* panelProvider(const QString& pluginId) const;

    bool executeCommand(const QString& pluginId,
                        const QString& command,
                        const QVariantMap& arguments = {},
                        QVariantMap* result = nullptr,
                        QString* error = nullptr);

    void loadSettings(QSettings& settings, const QString& projectScope);
    void saveSettings(QSettings& settings, const QString& projectScope) const;

signals:
    void diagnostic(const QString& message);

private:
    struct Entry;

    Entry* findEntry(const QString& pluginId) const;
    static QString normalizedId(const QString& value);
    static QString fallbackId(const QString& filePath);
    static QString canonicalDirectory(const QString& directory);
    static bool isInsideDirectory(const QString& filePath,
                                  const QString& canonicalDirectory);
    static QString settingsScope(const QString& projectScope,
                                 const QString& pluginId);
    void reject(const PluginDescriptor& descriptor, const QString& error);

    QSet<QString> m_disabledPluginIds;
    QVector<PluginDescriptor> m_descriptors;
    std::vector<std::unique_ptr<Entry>> m_entries;
};

#endif // PLUGINMANAGER_H
