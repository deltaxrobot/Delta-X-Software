#ifndef PRINTINGPLUGIN_H
#define PRINTINGPLUGIN_H

#include "form.h"
#include "../../sdk/DeltaXPlugin.h"
#include "../../sdk/DeltaXPluginV2.h"
#include "../../sdk/DeltaXPanelProvider.h"
#include "../../sdk/DeltaXCommandProvider.h"
#include <QThread>
#include <QSettings>

class IndustrialCameraPlugin : public DeltaXPlugin,
                               public DeltaXPluginV2,
                               public DeltaXPanelProvider,
                               public DeltaXCommandProvider
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV2_iid FILE "IndustrialCameraPlugin.json")
    Q_INTERFACES(DeltaXPlugin DeltaXPluginV2 DeltaXPanelProvider
                 DeltaXCommandProvider)

public:
    ~IndustrialCameraPlugin();
    QWidget* GetUI();
    QString GetName();
    QString GetTitle();
    void LoadSettings(QSettings* setting);
    void SaveSettings(QSettings* setting);

    QString id() const override;
    QString displayName() const override;
    QString version() const override;
    QStringList capabilities() const override;
    void loadSettings(QSettings& settings) override;
    void saveSettings(QSettings& settings) const override;
    QWidget* panel() override;
    bool executeCommand(const QString& command,
                        const QVariantMap& arguments,
                        QVariantMap* result,
                        QString* error) override;

public slots:
    void ProcessCommand(QString cmd);
    void TranferEmit(QString msg);
    void StopCapture();
private:
    Form* pluginForm = nullptr;  // Initialize to prevent undefined behavior

    QString pluginName = "industrialcamera";
    QString pluginTitle = "Industrial Camera";
};

#endif // PRINTINGPLUGIN_H


