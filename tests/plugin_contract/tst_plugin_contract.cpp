#include <QtTest>

#include "DeltaXPluginMetadata.h"

class PluginContractTest : public QObject
{
    Q_OBJECT

private slots:
    void acceptsCurrentAndLegacyMetadata();
    void rejectsInvalidOrIncompatibleMetadata();
};

static QJsonObject loaderMetadata(const QJsonValue& apiVersion,
                                  const QString& iid =
                                      QStringLiteral(DELTA_X_PLUGIN_IID))
{
    QJsonObject customMetadata;
    if (!apiVersion.isUndefined())
        customMetadata.insert(QStringLiteral("apiVersion"), apiVersion);

    QJsonObject root;
    root.insert(QStringLiteral("IID"), iid);
    root.insert(QStringLiteral("MetaData"), customMetadata);
    return root;
}

void PluginContractTest::acceptsCurrentAndLegacyMetadata()
{
    const QJsonObject current = loaderMetadata(DELTA_X_PLUGIN_API_VERSION);
    QCOMPARE(DeltaXPluginContract::declaredApiVersion(current), 1);
    QVERIFY(DeltaXPluginContract::compatibilityError(current).isEmpty());

    const QJsonObject legacy = loaderMetadata(QJsonValue(QJsonValue::Undefined));
    QCOMPARE(DeltaXPluginContract::declaredApiVersion(legacy), 1);
    QVERIFY(DeltaXPluginContract::compatibilityError(legacy).isEmpty());
}

void PluginContractTest::rejectsInvalidOrIncompatibleMetadata()
{
    QVERIFY(!DeltaXPluginContract::compatibilityError(loaderMetadata(2)).isEmpty());
    QVERIFY(!DeltaXPluginContract::compatibilityError(
                 loaderMetadata(QStringLiteral("1"))).isEmpty());
    QVERIFY(!DeltaXPluginContract::compatibilityError(
                 loaderMetadata(1, QStringLiteral("example.other.plugin"))).isEmpty());
}

QTEST_GUILESS_MAIN(PluginContractTest)
#include "tst_plugin_contract.moc"
