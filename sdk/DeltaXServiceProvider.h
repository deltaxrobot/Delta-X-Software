#ifndef DELTAXSERVICEPROVIDER_H
#define DELTAXSERVICEPROVIDER_H

#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QtPlugin>

// Service descriptors are QVariantMap values with a stable lowercase id, a
// semantic version, and a string-list of methods. The registry rejects a
// duplicate service id so consumers always resolve deterministically.
class DeltaXServiceProvider
{
public:
    virtual ~DeltaXServiceProvider() = default;
    virtual QVariantList services() const = 0;
    virtual bool invokeService(const QString& serviceId,
                               const QString& method,
                               const QVariantMap& request,
                               QVariantMap* response,
                               QString* error) = 0;
};

#define DeltaXServiceProvider_iid "org.deltaxrobot.DeltaXServiceProvider/1.0"
Q_DECLARE_INTERFACE(DeltaXServiceProvider, DeltaXServiceProvider_iid)

#endif // DELTAXSERVICEPROVIDER_H
