#ifndef PLUGINHOSTSERVICES_H
#define PLUGINHOSTSERVICES_H

#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QtGlobal>

#include <functional>

// Internal adapters keep the public SDK independent from application classes.
// Every callback must be safe to invoke from a plugin's owning thread.
struct PluginHostServices
{
    QString projectScope;

    std::function<QVariant(const QString&, const QVariant&)> readVariable;
    std::function<bool(const QString&, const QVariant&, bool, QString*)>
        writeVariable;
    std::function<bool(const QString&, QString*)> removeVariable;

    std::function<quint64(const QString&, const QString&, const QString&, bool,
                          int, QString*)>
        submitDeviceCommand;
    std::function<bool(const QString&, const QString&, QString*)>
        completeDeviceCommand;
    std::function<void(const QString&)> registerDevice;

    std::function<bool(const QVariantMap&, QString*)> submitDetections;
    std::function<QVariantList(int, QString*)> trackingSnapshot;
    std::function<QVariantMap(int, const QVariantMap&, QString*)> claimObject;
    std::function<bool(int, int, const QString&, QString*)> releaseObject;
    std::function<bool(int, int, const QString&, QString*)> completeObject;

    std::function<bool(const QString&, const QString&, const QString&,
                       const QVariantMap&, QString*)>
        reportHealth;
    std::function<bool(const QString&, const QString&, const QVariant&,
                       const QVariantMap&, QString*)>
        publishTelemetry;
    std::function<bool(const QString&, QString*)> requestControlledStop;
    std::function<void(const QString&, const QString&, const QString&)> log;
};

#endif // PLUGINHOSTSERVICES_H
