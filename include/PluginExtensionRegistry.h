#ifndef PLUGINEXTENSIONREGISTRY_H
#define PLUGINEXTENSIONREGISTRY_H

#include <QHash>
#include <QPointer>
#include <QReadWriteLock>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>

class DeltaXDeviceProvider;
class DeltaXGScriptProvider;
class DeltaXServiceProvider;
class QObject;

struct PluginGScriptPrimitive
{
    QString pluginId;
    QString name;
    QString signature;
    QString description;
    int minimumArguments = 0;
    int maximumArguments = 0;
    int resultArgument = -1;
};

class PluginExtensionRegistry final
{
public:
    static PluginExtensionRegistry& instance();

    bool registerGScriptProvider(const QString& pluginId, QObject* root,
                                 DeltaXGScriptProvider* provider,
                                 QString* error = nullptr);
    bool registerDeviceProvider(const QString& pluginId, QObject* root,
                                DeltaXDeviceProvider* provider,
                                QString* error = nullptr);
    bool registerServiceProvider(const QString& pluginId, QObject* root,
                                 DeltaXServiceProvider* provider,
                                 QString* error = nullptr);
    void unregisterPlugin(const QString& pluginId);
    void clearForTests();

    QVector<PluginGScriptPrimitive> gscriptPrimitives() const;
    bool hasGScriptPrimitive(const QString& name) const;
    bool executeGScriptPrimitive(const QString& name,
                                 const QVariantList& arguments,
                                 QVariant* result,
                                 QString* error = nullptr) const;

    QStringList deviceIds() const;
    bool ownsDevice(const QString& pluginId, const QString& deviceId) const;
    bool hasDevice(const QString& deviceId) const;
    bool dispatchDeviceCommand(const QString& deviceId,
                               const QString& command,
                               quint64 requestId,
                               QString* error = nullptr) const;

    QStringList serviceIds() const;
    QVariantList serviceDescriptors() const;
    bool invokeService(const QString& serviceId, const QString& method,
                       const QVariantMap& request, QVariantMap* response,
                       QString* error = nullptr) const;

    quint64 publishEvent(const QString& pluginId, const QString& topic,
                         const QVariantMap& payload,
                         QString* error = nullptr);
    QVariantList eventsSince(quint64 afterSequence,
                             const QString& topic = {},
                             int maximumCount = 100) const;

private:
    PluginExtensionRegistry() = default;

    struct GScriptRecord {
        PluginGScriptPrimitive descriptor;
        QPointer<QObject> root;
        DeltaXGScriptProvider* provider = nullptr;
    };
    struct DeviceRecord {
        QString pluginId;
        QPointer<QObject> root;
        DeltaXDeviceProvider* provider = nullptr;
    };
    struct ServiceRecord {
        QString pluginId;
        QString version;
        QStringList methods;
        QPointer<QObject> root;
        DeltaXServiceProvider* provider = nullptr;
    };

    static QString normalized(const QString& value);

    mutable QReadWriteLock m_lock;
    QHash<QString, GScriptRecord> m_gscript;
    QHash<QString, DeviceRecord> m_devices;
    QHash<QString, ServiceRecord> m_services;
    QVector<QVariantMap> m_events;
    quint64 m_nextEventSequence = 1;
};

#endif // PLUGINEXTENSIONREGISTRY_H
