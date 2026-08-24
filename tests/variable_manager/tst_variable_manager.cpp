#include <QtTest>

#include <atomic>
#include <future>

#include "VariableManager.h"

class VariableManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void scopesAreIndependent();
    void removalRespectsKeyBoundaries();
    void runtimeValuesAreExcludedFromPersistenceSnapshot();
    void emitsAfterReleasingWriteLock();
    void objectSnapshotsAreCopiedAndScoped();
    void batchSnapshotsRemainAtomicUnderConcurrentAccess();
    void nonNumericCommaStringRemainsAString();
    void geometryPersistenceUsesExplicitTypeMetadata();

private:
    const QString scopeA = "vm_test_a";
    const QString scopeB = "vm_test_b";
};

void VariableManagerTest::init()
{
    VariableManager::instance().removeVar(scopeA);
    VariableManager::instance().removeVar(scopeB);
}

void VariableManagerTest::cleanup()
{
    VariableManager::instance().removeVar(scopeA);
    VariableManager::instance().removeVar(scopeB);
    VariableManager::instance().removeObjectSnapshot(scopeA, "Objects");
    VariableManager::instance().removeObjectSnapshot(scopeB, "Objects");
    VariableManager::instance().saveToQSettings();
}

void VariableManagerTest::scopesAreIndependent()
{
    VariableManager& variables = VariableManager::instance();
    variables.updateVarScoped(scopeA, "Robot.Speed", 125);
    variables.updateVarScoped(scopeB, "Robot.Speed", 450);

    QCOMPARE(variables.getVarScoped(scopeA, "Robot.Speed").toInt(), 125);
    QCOMPARE(variables.getVarScoped(scopeB, "Robot.Speed").toInt(), 450);
    QCOMPARE(variables.scopedKey(scopeA, "#Robot.Speed"),
             scopeA + ".Robot.Speed");
    QCOMPARE(variables.scopedKey(scopeA, scopeA + ".Robot.Speed"),
             scopeA + ".Robot.Speed");
}

void VariableManagerTest::removalRespectsKeyBoundaries()
{
    VariableManager& variables = VariableManager::instance();
    variables.updateVar("vm_test_a.Value", 1);
    variables.updateVar("vm_test_ab.Value", 2);

    variables.removeVar(scopeA);

    QVERIFY(!variables.containsSubKey(scopeA));
    QCOMPARE(variables.getVar("vm_test_ab.Value").toInt(), 2);
    variables.removeVar("vm_test_ab");
}

void VariableManagerTest::runtimeValuesAreExcludedFromPersistenceSnapshot()
{
    VariableManager& variables = VariableManager::instance();
    variables.updateVarScoped(scopeA, "Calibration.Scale", 2.5,
                              VariableManager::Persistence::Persistent);
    variables.updateVarScoped(scopeA, "Objects.Count", 3,
                              VariableManager::Persistence::Runtime);

    const QHash<QString, QVariant> persistent = variables.snapshot(false);
    QVERIFY(persistent.contains(scopeA + ".Calibration.Scale"));
    QVERIFY(!persistent.contains(scopeA + ".Objects.Count"));
    QCOMPARE(variables.getVarScoped(scopeA, "Objects.Count").toInt(), 3);
}

void VariableManagerTest::emitsAfterReleasingWriteLock()
{
    VariableManager& variables = VariableManager::instance();
    bool callbackReadSucceeded = false;
    const QMetaObject::Connection connection = connect(
        &variables, &VariableManager::varUpdated, &variables,
        [&](const QString& key, const QVariant&) {
            if (key == scopeA + ".LockProbe")
                callbackReadSucceeded = variables.getVar(key).toInt() == 99;
        }, Qt::DirectConnection);

    variables.updateVarScoped(scopeA, "LockProbe", 99);
    disconnect(connection);
    QVERIFY(callbackReadSucceeded);
}

void VariableManagerTest::objectSnapshotsAreCopiedAndScoped()
{
    VariableManager& variables = VariableManager::instance();
    ObjectInfo object(42, 7, QVector3D(10, 20, 30), 40, 50, 60);
    object.confirmed = true;
    object.claimOwner = "robot0";
    QVector<ObjectInfo> source{object};

    variables.updateObjectSnapshot(scopeA, "#Objects", source);
    source[0].center.setX(999);
    source[0].claimOwner.clear();

    QCOMPARE(variables.getVarScoped(scopeA, "Objects.0.X").toFloat(), 10.0f);
    QCOMPARE(variables.getVarScoped(scopeA, "Objects.0.UID").toInt(), 42);
    QCOMPARE(variables.getVarScoped(scopeA, "Objects.0.State").toString(),
             QString("CLAIMED"));
    QVERIFY(!variables.getVarScoped(scopeB, "Objects.0.X").isValid());
}

void VariableManagerTest::batchSnapshotsRemainAtomicUnderConcurrentAccess()
{
    VariableManager& variables = VariableManager::instance();
    std::atomic_bool start{false};
    std::atomic_bool mismatch{false};

    auto writer = std::async(std::launch::async, [&]() {
        while (!start.load(std::memory_order_acquire)) {}
        for (int version = 1; version <= 2000; ++version) {
            variables.updateBatchScoped(
                scopeA, {{"Batch.Left", version}, {"Batch.Right", version}},
                VariableManager::Persistence::Runtime, false);
        }
    });
    auto reader = std::async(std::launch::async, [&]() {
        start.store(true, std::memory_order_release);
        for (int i = 0; i < 5000; ++i) {
            const QHash<QString, QVariant> values = variables.snapshot();
            const QVariant left = values.value(scopeA + ".Batch.Left");
            const QVariant right = values.value(scopeA + ".Batch.Right");
            if (left.isValid() != right.isValid() ||
                (left.isValid() && left.toInt() != right.toInt())) {
                mismatch.store(true, std::memory_order_release);
                break;
            }
        }
    });

    writer.get();
    reader.get();
    QVERIFY(!mismatch.load(std::memory_order_acquire));
    QCOMPARE(variables.getVarScoped(scopeA, "Batch.Left").toInt(), 2000);
    QCOMPARE(variables.getVarScoped(scopeA, "Batch.Right").toInt(), 2000);
}

void VariableManagerTest::nonNumericCommaStringRemainsAString()
{
    VariableManager& variables = VariableManager::instance();
    variables.updateVarScoped(scopeA, "Recipe.Sku", "SKU,RED");
    const QVariant value = variables.getVarScoped(scopeA, "Recipe.Sku");
    QCOMPARE(value.metaType().id(), int(QMetaType::QString));
    QCOMPARE(value.toString(), QString("SKU,RED"));
}

void VariableManagerTest::geometryPersistenceUsesExplicitTypeMetadata()
{
    VariableManager& variables = VariableManager::instance();
    QPolygonF polygon;
    polygon << QPointF(1.25, 2.5) << QPointF(10.0, 20.0);
    variables.updateVarScoped(scopeA, "Vision.Area", QRectF(3, 4, 50, 60));
    variables.updateVarScoped(scopeA, "Vision.Warp", polygon);
    variables.saveToQSettings();

    QSettings* settings = variables.getSettings();
    QCOMPARE(settings->value("__variable_types/" + scopeA + ".Vision.Area").toString(),
             QString("QRectF"));
    QCOMPARE(settings->value("__variable_types/" + scopeA + ".Vision.Warp").toString(),
             QString("QPolygonF"));
}

QTEST_MAIN(VariableManagerTest)
#include "tst_variable_manager.moc"
