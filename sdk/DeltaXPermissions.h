#ifndef DELTAXPERMISSIONS_H
#define DELTAXPERMISSIONS_H

#include <QSet>
#include <QString>
#include <QStringList>

namespace DeltaXPermissions
{
inline const QString VariablesRead = QStringLiteral("variables.read");
inline const QString VariablesWriteRuntime =
    QStringLiteral("variables.write.runtime");
inline const QString VariablesWritePersistent =
    QStringLiteral("variables.write.persistent");
inline const QString EventsRead = QStringLiteral("events.read");
inline const QString EventsPublish = QStringLiteral("events.publish");
inline const QString DevicesCommand = QStringLiteral("devices.command");
inline const QString DevicesProvide = QStringLiteral("devices.provide");
inline const QString VisionSubmit = QStringLiteral("vision.submit");
inline const QString TrackingRead = QStringLiteral("tracking.read");
inline const QString TrackingClaim = QStringLiteral("tracking.claim");
inline const QString GScriptRead = QStringLiteral("gscript.read");
inline const QString GScriptEdit = QStringLiteral("gscript.edit");
inline const QString GScriptRun = QStringLiteral("gscript.run");
inline const QString GScriptRegister = QStringLiteral("gscript.register");
inline const QString ServicesProvide = QStringLiteral("services.provide");
inline const QString ServicesConsume = QStringLiteral("services.consume");
inline const QString HealthReport = QStringLiteral("health.report");
inline const QString TelemetryPublish = QStringLiteral("telemetry.publish");
inline const QString CellControl = QStringLiteral("cell.control");

inline QStringList all()
{
    return {
        VariablesRead,
        VariablesWriteRuntime,
        VariablesWritePersistent,
        EventsRead,
        EventsPublish,
        DevicesCommand,
        DevicesProvide,
        VisionSubmit,
        TrackingRead,
        TrackingClaim,
        GScriptRead,
        GScriptEdit,
        GScriptRun,
        GScriptRegister,
        ServicesProvide,
        ServicesConsume,
        HealthReport,
        TelemetryPublish,
        CellControl,
    };
}

inline bool isKnown(const QString& permission)
{
    static const QStringList values = all();
    static const QSet<QString> known(values.cbegin(), values.cend());
    return known.contains(permission.trimmed().toLower());
}
}

#endif // DELTAXPERMISSIONS_H
