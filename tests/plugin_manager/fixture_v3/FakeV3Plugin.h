#ifndef FAKEV3PLUGIN_H
#define FAKEV3PLUGIN_H

#include "DeltaXCommandProvider.h"
#include "DeltaXDeviceProvider.h"
#include "DeltaXGScriptProvider.h"
#include "DeltaXPluginV3.h"
#include "DeltaXServiceProvider.h"

#include <QObject>

class DeltaXHostContext;

class FakeV3Plugin final : public QObject,
                           public DeltaXPluginV3,
                           public DeltaXCommandProvider,
                           public DeltaXGScriptProvider,
                           public DeltaXDeviceProvider,
                           public DeltaXServiceProvider
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV3_iid FILE "FakeV3Plugin.json")
    Q_INTERFACES(DeltaXPluginV2 DeltaXPluginV3 DeltaXCommandProvider
                 DeltaXGScriptProvider DeltaXDeviceProvider
                 DeltaXServiceProvider)

public:
    QString id() const override;
    QString displayName() const override;
    QString version() const override;
    QStringList capabilities() const override;
    void loadSettings(QSettings& settings) override;
    void saveSettings(QSettings& settings) const override;

    bool initialize(DeltaXHostContext* context, QString* error) override;
    bool start(QString* error) override;
    void stop() override;

    bool executeCommand(const QString& command, const QVariantMap& arguments,
                        QVariantMap* result, QString* error) override;
    QVariantList gscriptPrimitives() const override;
    bool executeGScriptPrimitive(const QString& name,
                                 const QVariantList& arguments,
                                 QVariant* result, QString* error) override;
    QStringList deviceIds() const override;
    bool submitDeviceCommand(const QString& deviceId, const QString& command,
                             quint64 requestId, QString* error) override;
    QVariantList services() const override;
    bool invokeService(const QString& serviceId, const QString& method,
                       const QVariantMap& request, QVariantMap* response,
                       QString* error) override;

private:
    DeltaXHostContext* m_context = nullptr;
    int m_value = 0;
    bool m_started = false;
};

#endif // FAKEV3PLUGIN_H
