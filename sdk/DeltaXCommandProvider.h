#ifndef DELTAXCOMMANDPROVIDER_H
#define DELTAXCOMMANDPROVIDER_H

#include <QString>
#include <QVariantMap>
#include <QtPlugin>

class DeltaXCommandProvider
{
public:
    virtual ~DeltaXCommandProvider() = default;
    virtual bool executeCommand(const QString& command,
                                const QVariantMap& arguments,
                                QVariantMap* result,
                                QString* error) = 0;
};

#define DeltaXCommandProvider_iid "org.deltaxrobot.DeltaXCommandProvider/1.0"
Q_DECLARE_INTERFACE(DeltaXCommandProvider, DeltaXCommandProvider_iid)

#endif // DELTAXCOMMANDPROVIDER_H
