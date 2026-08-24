#include <QtTest>

#include <QDir>
#include <QPluginLoader>
#include <QPushButton>
#include <QComboBox>

#include "DeltaXPlugin.h"

class IndustrialCameraOptionalRuntimeTest : public QObject
{
    Q_OBJECT

private slots:
    void pluginLoadsWithoutMakingVendorSdkMandatory();
};

void IndustrialCameraOptionalRuntimeTest::pluginLoadsWithoutMakingVendorSdkMandatory()
{
    QString pluginPath = qEnvironmentVariable("DELTA_X_INDUSTRIAL_PLUGIN");
    if (pluginPath.isEmpty()) {
        pluginPath = QFINDTESTDATA("../../plugin/IndustrialCameraPlugin.dll");
    }

    QVERIFY2(QFileInfo::exists(pluginPath), qPrintable(pluginPath));
    QPluginLoader loader(pluginPath);
    QVERIFY2(loader.load(), qPrintable(loader.errorString()));

    QObject* instance = loader.instance();
    QVERIFY2(instance, qPrintable(loader.errorString()));
    DeltaXPlugin* plugin = qobject_cast<DeltaXPlugin*>(instance);
    QVERIFY(plugin);
    QCOMPARE(plugin->GetName(), QStringLiteral("industrialcamera"));

    QWidget* interfaceWidget = plugin->GetUI();
    QVERIFY(interfaceWidget);
    QVERIFY(plugin->property("cameraBackendAvailable").isValid());
    QVERIFY(!plugin->property("cameraBackendStatus").toString().isEmpty());

    QPushButton* refreshButton =
        interfaceWidget->findChild<QPushButton*>(QStringLiteral("pbRefresh"));
    QVERIFY(refreshButton);
    refreshButton->click();
    QTest::qWait(500); // Allow the worker-thread enumeration to finish.

    if (qEnvironmentVariableIntValue("DELTA_X_EXPECT_NO_VENDOR") == 1) {
        QVERIFY(!plugin->property("cameraBackendAvailable").toBool());
        QComboBox* cameraList =
            interfaceWidget->findChild<QComboBox*>(QStringLiteral("cbCameraList"));
        QVERIFY(cameraList);
        QCOMPARE(cameraList->count(), 0);
    }

    interfaceWidget->close();
    QVERIFY(loader.unload());
}

QTEST_MAIN(IndustrialCameraOptionalRuntimeTest)
#include "tst_industrial_camera_optional_runtime.moc"
