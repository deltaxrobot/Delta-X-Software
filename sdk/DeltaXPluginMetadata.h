#ifndef DELTAXPLUGINMETADATA_H
#define DELTAXPLUGINMETADATA_H

#include <QJsonObject>
#include <QString>

#define DELTA_X_PLUGIN_IID "org.imwi.deltaxstudio"
#define DELTA_X_PLUGIN_API_VERSION 1

namespace DeltaXPluginContract
{
inline constexpr int SupportedApiVersion = DELTA_X_PLUGIN_API_VERSION;
inline constexpr int LegacyApiVersion = 1;

// Plugins created before the versioned contract did not declare apiVersion.
// They are treated as API v1 so existing third-party plugins keep working.
inline int declaredApiVersion(const QJsonObject& loaderMetadata)
{
    const QJsonObject pluginMetadata =
        loaderMetadata.value(QStringLiteral("MetaData")).toObject();
    const QJsonValue value = pluginMetadata.value(QStringLiteral("apiVersion"));
    if (value.isUndefined() || value.isNull())
        return LegacyApiVersion;
    if (!value.isDouble())
        return -1;

    const double rawVersion = value.toDouble();
    const int version = static_cast<int>(rawVersion);
    return rawVersion == version && version > 0 ? version : -1;
}

inline QString compatibilityError(const QJsonObject& loaderMetadata)
{
    const QString iid = loaderMetadata.value(QStringLiteral("IID")).toString();
    if (!iid.isEmpty() && iid != QStringLiteral(DELTA_X_PLUGIN_IID)) {
        return QStringLiteral("unsupported interface '%1'; expected '%2'")
            .arg(iid, QStringLiteral(DELTA_X_PLUGIN_IID));
    }

    const int version = declaredApiVersion(loaderMetadata);
    if (version < 1)
        return QStringLiteral("metadata field 'apiVersion' must be a positive integer");
    if (version != SupportedApiVersion) {
        return QStringLiteral("plugin API v%1 is incompatible with host API v%2")
            .arg(version)
            .arg(SupportedApiVersion);
    }
    return {};
}
}

#endif // DELTAXPLUGINMETADATA_H
