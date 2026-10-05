#ifndef INSPECTIONPLUGIN_H
#define INSPECTIONPLUGIN_H

#include "DeltaXCommandProvider.h"
#include "DeltaXGScriptProvider.h"
#include "DeltaXPanelProvider.h"
#include "DeltaXPluginV3.h"
#include "DeltaXServiceProvider.h"

#include <QObject>

class DeltaXHostContext;
class QLabel;
class QWidget;

// A production-shaped reference: lifecycle, permission-checked host access,
// an operator panel, structured commands, a G-Script primitive and a service.
class InspectionPlugin final : public QObject,
                               public DeltaXPluginV3,
                               public DeltaXPanelProvider,
                               public DeltaXCommandProvider,
                               public DeltaXGScriptProvider,
                               public DeltaXServiceProvider
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV3_iid FILE "InspectionPlugin.json")
    Q_INTERFACES(DeltaXPluginV2 DeltaXPluginV3 DeltaXPanelProvider
                 DeltaXCommandProvider DeltaXGScriptProvider
                 DeltaXServiceProvider)

public:
    ~InspectionPlugin() override;

    QString id() const override;
    QString displayName() const override;
    QString version() const override;
    QStringList capabilities() const override;
    void loadSettings(QSettings& settings) override;
    void saveSettings(QSettings& settings) const override;
    bool initialize(DeltaXHostContext* context, QString* error) override;
    bool start(QString* error) override;
    void stop() override;

    QWidget* panel() override;
    bool executeCommand(const QString& command, const QVariantMap& arguments,
                        QVariantMap* result, QString* error) override;
    QVariantList gscriptPrimitives() const override;
    bool executeGScriptPrimitive(const QString& name,
                                 const QVariantList& arguments,
                                 QVariant* result, QString* error) override;
    QVariantList services() const override;
    bool invokeService(const QString& serviceId, const QString& method,
                       const QVariantMap& request, QVariantMap* response,
                       QString* error) override;

private:
    QVariantMap evaluate(int trackingId, double minimumConfidence,
                         QString* error) const;
    void refreshPanel();

    DeltaXHostContext* m_context = nullptr;
    QWidget* m_panel = nullptr;
    QLabel* m_status = nullptr;
    double m_minimumConfidence = 0.8;
    int m_lastTrackingId = 0;
};

#endif // INSPECTIONPLUGIN_H
