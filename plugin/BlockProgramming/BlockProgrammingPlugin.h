#ifndef BLOCKPROGRAMMINGPLUGIN_H
#define BLOCKPROGRAMMINGPLUGIN_H

#include "DeltaXCommandProvider.h"
#include "DeltaXPanelProvider.h"
#include "DeltaXPluginV3.h"

#include <QJsonObject>
#include <QObject>

class BlockProgrammingPanel;
class DeltaXHostContext;

class BlockProgrammingPlugin final : public QObject,
                                     public DeltaXPluginV3,
                                     public DeltaXPanelProvider,
                                     public DeltaXCommandProvider
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV3_iid FILE "BlockProgrammingPlugin.json")
    Q_INTERFACES(DeltaXPluginV2 DeltaXPluginV3 DeltaXPanelProvider
                 DeltaXCommandProvider)

public:
    static constexpr const char* PluginVersion = "1.1.0";

    ~BlockProgrammingPlugin() override;

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

private:
    DeltaXHostContext* m_context = nullptr;
    BlockProgrammingPanel* m_panel = nullptr;
    QJsonObject m_savedWorkspace;
    int m_savedWorker = 0;
};

#endif // BLOCKPROGRAMMINGPLUGIN_H
