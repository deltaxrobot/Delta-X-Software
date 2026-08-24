#include <QtTest>
#include <QJsonArray>

#include "DeltaXPluginMetadata.h"

class PluginContractTest : public QObject
{
    Q_OBJECT

private slots:
    void acceptsCurrentAndLegacyMetadata();
    void rejectsInvalidOrIncompatibleMetadata();
};

static QJsonObject loaderMetadata(const QJsonValue& apiVersion,
                                  const QString& iid = {})
{
    QJsonObject customMetadata;
    if (!apiVersion.isUndefined())
        customMetadata.insert(QStringLiteral("apiVersion"), apiVersion);
    if (apiVersion.toInt() == DELTA_X_PLUGIN_API_VERSION) {
        customMetadata.insert(QStringLiteral("name"),
                              QStringLiteral("example.plugin"));
        customMetadata.insert(QStringLiteral("pluginVersion"),
                              QStringLiteral("1.2.3"));
        customMetadata.insert(QStringLiteral("capabilities"), QJsonArray{});
    }

    QJsonObject root;
    root.insert(QStringLiteral("IID"),
                iid.isEmpty()
                    ? (apiVersion.toInt() == DELTA_X_PLUGIN_API_VERSION
                           ? QStringLiteral(DELTA_X_PLUGIN_V2_IID)
                           : QStringLiteral(DELTA_X_PLUGIN_V1_IID))
                    : iid);
    root.insert(QStringLiteral("MetaData"), customMetadata);
    return root;
}

void PluginContractTest::acceptsCurrentAndLegacyMetadata()
{
    const QJsonObject current = loaderMetadata(DELTA_X_PLUGIN_API_VERSION);
    QCOMPARE(DeltaXPluginContract::declaredApiVersion(current), 2);
    QVERIFY(DeltaXPluginContract::compatibilityError(current).isEmpty());

    const QJsonObject legacy = loaderMetadata(QJsonValue(QJsonValue::Undefined));
    QCOMPARE(DeltaXPluginContract::declaredApiVersion(legacy), 1);
    QVERIFY(DeltaXPluginContract::compatibilityError(legacy).isEmpty());
}

void PluginContractTest::rejectsInvalidOrIncompatibleMetadata()
{
    QVERIFY(!DeltaXPluginContract::compatibilityError(loaderMetadata(3)).isEmpty());
    QVERIFY(!DeltaXPluginContract::compatibilityError(
                 loaderMetadata(QStringLiteral("1"))).isEmpty());
    QVERIFY(!DeltaXPluginContract::compatibilityError(
                 loaderMetadata(1, QStringLiteral("example.other.plugin"))).isEmpty());

    QJsonObject invalidV2 = loaderMetadata(2);
    QJsonObject customMetadata = invalidV2.value(QStringLiteral("MetaData")).toObject();
    customMetadata.insert(QStringLiteral("pluginVersion"), QStringLiteral("latest"));
    invalidV2.insert(QStringLiteral("MetaData"), customMetadata);
    QVERIFY(!DeltaXPluginContract::compatibilityError(invalidV2).isEmpty());

    invalidV2 = loaderMetadata(2);
    customMetadata = invalidV2.value(QStringLiteral("MetaData")).toObject();
    customMetadata.insert(QStringLiteral("name"), QStringLiteral("Example.Plugin"));
    invalidV2.insert(QStringLiteral("MetaData"), customMetadata);
    QVERIFY(!DeltaXPluginContract::compatibilityError(invalidV2).isEmpty());

    invalidV2 = loaderMetadata(2);
    customMetadata = invalidV2.value(QStringLiteral("MetaData")).toObject();
    customMetadata.insert(
        QStringLiteral("capabilities"),
        QJsonArray{QStringLiteral("panel"), QStringLiteral("panel")});
    invalidV2.insert(QStringLiteral("MetaData"), customMetadata);
    QVERIFY(!DeltaXPluginContract::compatibilityError(invalidV2).isEmpty());
}

QTEST_GUILESS_MAIN(PluginContractTest)
#include "tst_plugin_contract.moc"
