#ifndef DELTAXPLUGINV2_H
#define DELTAXPLUGINV2_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QtPlugin>

#include "DeltaXPluginMetadata.h"

// Stable, dependency-light base contract for all new plugins. A plugin opts
// into UI, commands or other features through separate capability interfaces.
class DeltaXPluginV2
{
public:
    virtual ~DeltaXPluginV2() = default;

    virtual QString id() const = 0;
    virtual QString displayName() const = 0;
    virtual QString version() const = 0;
    virtual QStringList capabilities() const = 0;
    virtual void loadSettings(QSettings& settings) = 0;
    virtual void saveSettings(QSettings& settings) const = 0;
};

#define DeltaXPluginV2_iid DELTA_X_PLUGIN_V2_IID
Q_DECLARE_INTERFACE(DeltaXPluginV2, DeltaXPluginV2_iid)

#endif // DELTAXPLUGINV2_H
