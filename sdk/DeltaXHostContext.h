#ifndef DELTAXHOSTCONTEXT_H
#define DELTAXHOSTCONTEXT_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QtGlobal>

// A capability-checked gateway into host services. The host owns this object;
// plugins must not delete it or keep using it after stop() returns.
class DeltaXHostContext
{
public:
    virtual ~DeltaXHostContext() = default;

    virtual QString pluginId() const = 0;
    virtual QString projectScope() const = 0;
    virtual QStringList grantedPermissions() const = 0;
    virtual bool hasPermission(const QString& permission) const = 0;

    virtual QVariant readVariable(const QString& key,
                                  const QVariant& defaultValue = {}) const = 0;
    virtual bool writeVariable(const QString& key, const QVariant& value,
                               bool persistent, QString* error = nullptr) = 0;
    virtual bool removeVariable(const QString& key,
                                QString* error = nullptr) = 0;

    virtual quint64 publishEvent(const QString& topic,
                                 const QVariantMap& payload,
                                 QString* error = nullptr) = 0;
    virtual QVariantList eventsSince(quint64 afterSequence,
                                     const QString& topic = {},
                                     int maximumCount = 100,
                                     QString* error = nullptr) const = 0;

    virtual quint64 submitDeviceCommand(const QString& deviceId,
                                        const QString& command,
                                        bool waitForResponse = true,
                                        int timeoutMs = 120000,
                                        QString* error = nullptr) = 0;
    virtual bool completeDeviceCommand(const QString& deviceId,
                                       const QString& response,
                                       QString* error = nullptr) = 0;

    // frame keys: frameId, requestId, trackingId, coordinateSpace, objects.
    // Each object is a map with type, x, y, z, width, height, angle and
    // optional confidence, label and externalId values.
    virtual bool submitDetections(const QVariantMap& frame,
                                  QString* error = nullptr) = 0;

    virtual QVariantList trackingSnapshot(int trackingId,
                                          QString* error = nullptr) const = 0;
    virtual QVariantMap claimObject(int trackingId,
                                    const QVariantMap& request,
                                    QString* error = nullptr) = 0;
    virtual bool releaseObject(int trackingId, int uid,
                               const QString& owner,
                               QString* error = nullptr) = 0;
    virtual bool completeObject(int trackingId, int uid,
                                const QString& owner,
                                QString* error = nullptr) = 0;

    // Worker entries contain index, id, state, running and sourceLength.
    // Diagnostic entries contain severity, code, line, column, message and hint.
    virtual QVariantList gscriptWorkers(QString* error = nullptr) const = 0;
    virtual QVariantList validateGScript(const QString& source,
                                         QString* error = nullptr) const = 0;
    virtual bool loadGScript(int workerIndex, const QString& source,
                             QString* error = nullptr) = 0;
    virtual bool runGScript(int workerIndex, const QString& source,
                            QString* error = nullptr) = 0;
    virtual bool stopGScript(int workerIndex,
                             QString* error = nullptr) = 0;

    // Each catalog entry contains id, version, methods and providerPluginId.
    virtual QVariantList serviceCatalog(QString* error = nullptr) const = 0;
    virtual bool invokeService(const QString& serviceId,
                               const QString& method,
                               const QVariantMap& request,
                               QVariantMap* response,
                               QString* error = nullptr) = 0;

    virtual bool reportHealth(const QString& state,
                              const QString& message = {},
                              const QVariantMap& details = {},
                              QString* error = nullptr) = 0;
    virtual bool publishTelemetry(const QString& metric,
                                  const QVariant& value,
                                  const QVariantMap& attributes = {},
                                  QString* error = nullptr) = 0;
    virtual bool requestControlledStop(const QString& reason,
                                       QString* error = nullptr) = 0;
    virtual void log(const QString& level, const QString& message) = 0;
};

#endif // DELTAXHOSTCONTEXT_H
