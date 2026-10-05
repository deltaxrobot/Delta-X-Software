#ifndef DELTAXPLUGINMETADATA_H
#define DELTAXPLUGINMETADATA_H

#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>
#include <QSet>
#include <QString>
#include <QStringList>

#include "DeltaXPermissions.h"

// API v1/v2 are retained as compatibility interfaces. New plugins use v3.
#define DELTA_X_PLUGIN_V1_IID "org.imwi.deltaxstudio"
#define DELTA_X_PLUGIN_V2_IID "org.deltaxrobot.DeltaXPlugin/2.0"
#define DELTA_X_PLUGIN_V3_IID "org.deltaxrobot.DeltaXPlugin/3.0"
#define DELTA_X_PLUGIN_IID DELTA_X_PLUGIN_V1_IID
#define DELTA_X_PLUGIN_API_VERSION 3

namespace DeltaXPluginContract
{
inline constexpr int SupportedApiVersion = DELTA_X_PLUGIN_API_VERSION;
inline constexpr int LegacyApiVersion = 1;
inline constexpr int VersionedApiVersion = 2;

inline QJsonObject pluginMetadata(const QJsonObject& loaderMetadata)
{
    return loaderMetadata.value(QStringLiteral("MetaData")).toObject();
}

// Plugins created before the versioned contract did not declare apiVersion.
// They are treated as API v1 so existing third-party plugins keep working.
inline int declaredApiVersion(const QJsonObject& loaderMetadata)
{
    const QJsonValue value =
        pluginMetadata(loaderMetadata).value(QStringLiteral("apiVersion"));
    if (value.isUndefined() || value.isNull())
        return LegacyApiVersion;
    if (!value.isDouble())
        return -1;

    const double rawVersion = value.toDouble();
    const int version = static_cast<int>(rawVersion);
    return rawVersion == version && version > 0 ? version : -1;
}

inline QString pluginId(const QJsonObject& loaderMetadata)
{
    return pluginMetadata(loaderMetadata)
        .value(QStringLiteral("name"))
        .toString()
        .trimmed()
        .toLower();
}

inline QString pluginVersion(const QJsonObject& loaderMetadata)
{
    return pluginMetadata(loaderMetadata)
        .value(QStringLiteral("pluginVersion"))
        .toString()
        .trimmed();
}

inline QString pluginDisplayName(const QJsonObject& loaderMetadata)
{
    return pluginMetadata(loaderMetadata)
        .value(QStringLiteral("displayName"))
        .toString()
        .trimmed();
}

inline QString stability(const QJsonObject& loaderMetadata)
{
    const QString value = pluginMetadata(loaderMetadata)
                              .value(QStringLiteral("stability"))
                              .toString()
                              .trimmed()
                              .toLower();
    return value.isEmpty() ? QStringLiteral("stable") : value;
}

inline bool defaultEnabled(const QJsonObject& loaderMetadata)
{
    const QJsonValue value = pluginMetadata(loaderMetadata)
                                 .value(QStringLiteral("defaultEnabled"));
    return value.isUndefined() ? true : value.toBool(true);
}

inline QStringList capabilities(const QJsonObject& loaderMetadata)
{
    QStringList result;
    const QJsonArray values = pluginMetadata(loaderMetadata)
                                  .value(QStringLiteral("capabilities"))
                                  .toArray();
    for (const QJsonValue& value : values) {
        const QString capability = value.toString().trimmed().toLower();
        if (!capability.isEmpty() && !result.contains(capability))
            result.append(capability);
    }
    return result;
}

inline QStringList requestedPermissions(const QJsonObject& loaderMetadata)
{
    QStringList result;
    const QJsonArray values = pluginMetadata(loaderMetadata)
                                  .value(QStringLiteral("permissions"))
                                  .toArray();
    for (const QJsonValue& value : values) {
        const QString permission = value.toString().trimmed().toLower();
        if (!permission.isEmpty() && !result.contains(permission))
            result.append(permission);
    }
    result.sort();
    return result;
}

inline bool isSemanticVersion(const QString& version)
{
    static const QRegularExpression expression(
        QStringLiteral("^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)\\.(0|[1-9]\\d*)"
                       "(?:-[0-9A-Za-z.-]+)?(?:\\+[0-9A-Za-z.-]+)?$"));
    return expression.match(version).hasMatch();
}

inline QString compatibilityError(const QJsonObject& loaderMetadata)
{
    const int version = declaredApiVersion(loaderMetadata);
    if (version < 1)
        return QStringLiteral("metadata field 'apiVersion' must be a positive integer");
    if (version > SupportedApiVersion) {
        return QStringLiteral("plugin API v%1 is newer than host API v%2")
            .arg(version)
            .arg(SupportedApiVersion);
    }
    if (version != LegacyApiVersion && version != VersionedApiVersion &&
        version != SupportedApiVersion) {
        return QStringLiteral("plugin API v%1 is not supported by this host")
            .arg(version);
    }

    const QString iid = loaderMetadata.value(QStringLiteral("IID")).toString();
    const QString expectedIid = version == LegacyApiVersion
        ? QStringLiteral(DELTA_X_PLUGIN_V1_IID)
        : version == VersionedApiVersion
            ? QStringLiteral(DELTA_X_PLUGIN_V2_IID)
            : QStringLiteral(DELTA_X_PLUGIN_V3_IID);
    if ((version != LegacyApiVersion && iid != expectedIid) ||
        (version == LegacyApiVersion && !iid.isEmpty() && iid != expectedIid)) {
        return QStringLiteral("unsupported interface '%1'; expected '%2'")
            .arg(iid, expectedIid);
    }

    // V1 metadata was intentionally permissive. V2+ make identity, version and
    // capabilities explicit; v3 also requires an explicit permission list.
    if (version == VersionedApiVersion || version == SupportedApiVersion) {
        const QJsonObject metadata = pluginMetadata(loaderMetadata);
        const QString rawId =
            metadata.value(QStringLiteral("name")).toString().trimmed();
        const QString id = pluginId(loaderMetadata);
        static const QRegularExpression idExpression(
            QStringLiteral("^[a-z][a-z0-9]*(?:[._-][a-z0-9]+)*$"));
        if (rawId != id || !idExpression.match(id).hasMatch()) {
            return QStringLiteral(
                "metadata field 'name' must be a stable lowercase plugin id");
        }
        const QString ownVersion = pluginVersion(loaderMetadata);
        if (!isSemanticVersion(ownVersion)) {
            return QStringLiteral(
                "metadata field 'pluginVersion' must use semantic versioning");
        }
        const QJsonValue rawDisplayName =
            metadata.value(QStringLiteral("displayName"));
        if (!rawDisplayName.isUndefined() &&
            (!rawDisplayName.isString() ||
             rawDisplayName.toString().trimmed().isEmpty())) {
            return QStringLiteral(
                "metadata field 'displayName' must be a non-empty string");
        }
        const QJsonValue rawStability = metadata.value(QStringLiteral("stability"));
        if (!rawStability.isUndefined() &&
            (!rawStability.isString() ||
             !QSet<QString>{QStringLiteral("stable"), QStringLiteral("beta"),
                            QStringLiteral("experimental")}
                  .contains(rawStability.toString().trimmed().toLower()))) {
            return QStringLiteral(
                "metadata field 'stability' must be stable, beta, or experimental");
        }
        const QJsonValue rawDefaultEnabled =
            metadata.value(QStringLiteral("defaultEnabled"));
        if (!rawDefaultEnabled.isUndefined() && !rawDefaultEnabled.isBool()) {
            return QStringLiteral(
                "metadata field 'defaultEnabled' must be a boolean");
        }
        const QJsonValue rawCapabilities =
            metadata.value(QStringLiteral("capabilities"));
        if (!rawCapabilities.isArray()) {
            return QStringLiteral("metadata field 'capabilities' must be an array");
        }
        QSet<QString> uniqueCapabilities;
        for (const QJsonValue& value : rawCapabilities.toArray()) {
            const QString rawCapability = value.toString().trimmed();
            const QString capability = rawCapability.toLower();
            if (!value.isString() || rawCapability != capability ||
                !idExpression.match(capability).hasMatch()) {
                return QStringLiteral(
                    "metadata capabilities must be stable lowercase identifiers");
            }
            if (uniqueCapabilities.contains(capability))
                return QStringLiteral("metadata capabilities must be unique");
            uniqueCapabilities.insert(capability);
        }

        if (version == SupportedApiVersion) {
            const QJsonValue rawPermissions =
                metadata.value(QStringLiteral("permissions"));
            if (!rawPermissions.isArray()) {
                return QStringLiteral(
                    "metadata field 'permissions' must be an array");
            }
            QSet<QString> uniquePermissions;
            for (const QJsonValue& value : rawPermissions.toArray()) {
                const QString rawPermission = value.toString().trimmed();
                const QString permission = rawPermission.toLower();
                if (!value.isString() || rawPermission != permission ||
                    !DeltaXPermissions::isKnown(permission)) {
                    return QStringLiteral(
                        "metadata permissions must be known lowercase identifiers");
                }
                if (uniquePermissions.contains(permission))
                    return QStringLiteral("metadata permissions must be unique");
                uniquePermissions.insert(permission);
            }
        }
    }
    return {};
}

inline bool isKnownPermission(const QString& permission)
{
    return DeltaXPermissions::isKnown(permission);
}
}

#endif // DELTAXPLUGINMETADATA_H
