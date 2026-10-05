#ifndef DELTAXPLUGINV3_H
#define DELTAXPLUGINV3_H

#include "DeltaXPluginV2.h"

class DeltaXHostContext;

// API v3 adds an explicit, reversible lifecycle and a permission-checked host
// context while preserving the dependency-light identity/settings contract.
class DeltaXPluginV3 : public DeltaXPluginV2
{
public:
    ~DeltaXPluginV3() override = default;

    virtual bool initialize(DeltaXHostContext* context,
                            QString* error = nullptr) = 0;
    virtual bool start(QString* error = nullptr) = 0;
    virtual void stop() = 0;
};

#define DeltaXPluginV3_iid DELTA_X_PLUGIN_V3_IID
Q_DECLARE_INTERFACE(DeltaXPluginV3, DeltaXPluginV3_iid)

#endif // DELTAXPLUGINV3_H
