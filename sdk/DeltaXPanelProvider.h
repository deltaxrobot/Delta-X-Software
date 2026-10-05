#ifndef DELTAXPANELPROVIDER_H
#define DELTAXPANELPROVIDER_H

#include <QtPlugin>

class QWidget;

class DeltaXPanelProvider
{
public:
    virtual ~DeltaXPanelProvider() = default;
    virtual QWidget* panel() = 0;
};

#define DeltaXPanelProvider_iid "org.deltaxrobot.DeltaXPanelProvider/1.0"
Q_DECLARE_INTERFACE(DeltaXPanelProvider, DeltaXPanelProvider_iid)

#endif // DELTAXPANELPROVIDER_H
