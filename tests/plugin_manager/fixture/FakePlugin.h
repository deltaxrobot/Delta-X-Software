#ifndef FAKEPLUGIN_H
#define FAKEPLUGIN_H

#include "DeltaXCommandProvider.h"
#include "DeltaXPanelProvider.h"
#include "DeltaXPluginV2.h"

#include <QObject>

class FakePlugin final : public QObject,
                         public DeltaXPluginV2,
                         public DeltaXPanelProvider,
                         public DeltaXCommandProvider
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV2_iid FILE "FakePlugin.json")
    Q_INTERFACES(DeltaXPluginV2 DeltaXPanelProvider DeltaXCommandProvider)

public:
    ~FakePlugin() override;

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

private:
    QWidget* m_panel = nullptr;
    int m_value = 0;
};

#endif // FAKEPLUGIN_H
