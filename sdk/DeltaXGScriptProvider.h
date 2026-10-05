#ifndef DELTAXGSCRIPTPROVIDER_H
#define DELTAXGSCRIPTPROVIDER_H

#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QtPlugin>

// Primitive descriptors are QVariantMap values with: name, signature,
// description, minArgs, maxArgs and optional resultArgument (zero based).
// The host validates the result argument as a variable target and omits it
// from the evaluated argument list passed to executeGScriptPrimitive().
class DeltaXGScriptProvider
{
public:
    virtual ~DeltaXGScriptProvider() = default;
    virtual QVariantList gscriptPrimitives() const = 0;
    virtual bool executeGScriptPrimitive(const QString& name,
                                         const QVariantList& arguments,
                                         QVariant* result,
                                         QString* error) = 0;
};

#define DeltaXGScriptProvider_iid "org.deltaxrobot.DeltaXGScriptProvider/1.0"
Q_DECLARE_INTERFACE(DeltaXGScriptProvider, DeltaXGScriptProvider_iid)

#endif // DELTAXGSCRIPTPROVIDER_H
