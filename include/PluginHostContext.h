#ifndef PLUGINHOSTCONTEXT_H
#define PLUGINHOSTCONTEXT_H

#include "PluginHostServices.h"
#include "sdk/DeltaXHostContext.h"

#include <QSet>

#include <atomic>

class PluginHostContext final : public DeltaXHostContext
{
public:
    PluginHostContext(const QString& pluginId,
                      const QStringList& requestedPermissions,
                      const QSet<QString>& grantedPermissions,
                      const PluginHostServices& services);

    QString pluginId() const override;
    QString projectScope() const override;
    QStringList grantedPermissions() const override;
    bool hasPermission(const QString& permission) const override;

    QVariant readVariable(const QString& key,
                          const QVariant& defaultValue = {}) const override;
    bool writeVariable(const QString& key, const QVariant& value,
                       bool persistent, QString* error = nullptr) override;
    bool removeVariable(const QString& key, QString* error = nullptr) override;
    quint64 publishEvent(const QString& topic, const QVariantMap& payload,
                         QString* error = nullptr) override;
    QVariantList eventsSince(quint64 afterSequence, const QString& topic = {},
                             int maximumCount = 100,
                             QString* error = nullptr) const override;
    quint64 submitDeviceCommand(const QString& deviceId, const QString& command,
                                bool waitForResponse = true,
                                int timeoutMs = 120000,
                                QString* error = nullptr) override;
    bool completeDeviceCommand(const QString& deviceId, const QString& response,
                               QString* error = nullptr) override;
    bool submitDetections(const QVariantMap& frame,
                          QString* error = nullptr) override;
    QVariantList trackingSnapshot(int trackingId,
                                  QString* error = nullptr) const override;
    QVariantMap claimObject(int trackingId, const QVariantMap& request,
                            QString* error = nullptr) override;
    bool releaseObject(int trackingId, int uid, const QString& owner,
                       QString* error = nullptr) override;
    bool completeObject(int trackingId, int uid, const QString& owner,
                        QString* error = nullptr) override;
    QVariantList serviceCatalog(QString* error = nullptr) const override;
    bool invokeService(const QString& serviceId, const QString& method,
                       const QVariantMap& request, QVariantMap* response,
                       QString* error = nullptr) override;
    bool reportHealth(const QString& state, const QString& message = {},
                      const QVariantMap& details = {},
                      QString* error = nullptr) override;
    bool publishTelemetry(const QString& metric, const QVariant& value,
                          const QVariantMap& attributes = {},
                          QString* error = nullptr) override;
    bool requestControlledStop(const QString& reason,
                               QString* error = nullptr) override;
    void log(const QString& level, const QString& message) override;

    void invalidate();

private:
    bool require(const QString& permission, QString* error) const;
    bool requireActive(QString* error) const;
    QString scopedOwner(const QString& owner) const;

    QString m_pluginId;
    QString m_projectScope;
    QSet<QString> m_grantedPermissions;
    PluginHostServices m_services;
    std::atomic_bool m_active{true};
};

#endif // PLUGINHOSTCONTEXT_H
