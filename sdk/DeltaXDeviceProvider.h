#ifndef DELTAXDEVICEPROVIDER_H
#define DELTAXDEVICEPROVIDER_H

#include <QString>
#include <QStringList>
#include <QtGlobal>
#include <QtPlugin>

// Device commands are accepted synchronously and may be completed
// asynchronously through DeltaXHostContext::completeDeviceCommand().
class DeltaXDeviceProvider
{
public:
    virtual ~DeltaXDeviceProvider() = default;
    virtual QStringList deviceIds() const = 0;
    virtual bool submitDeviceCommand(const QString& deviceId,
                                     const QString& command,
                                     quint64 requestId,
                                     QString* error) = 0;
};

#define DeltaXDeviceProvider_iid "org.deltaxrobot.DeltaXDeviceProvider/1.0"
Q_DECLARE_INTERFACE(DeltaXDeviceProvider, DeltaXDeviceProvider_iid)

#endif // DELTAXDEVICEPROVIDER_H
