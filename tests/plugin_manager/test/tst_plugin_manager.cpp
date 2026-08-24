#include <QtTest>

#include "PluginManager.h"
#include "DeltaXPanelProvider.h"

#include <QDir>
#include <QFile>
#include <QLibrary>
#include <QTemporaryDir>

#include <algorithm>

class PluginManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void loadsCapabilitiesCommandsAndSettings();
    void rejectsDuplicateIds();
    void honorsDisabledIds();
    void ignoresMissingDirectories();

private:
    QString fixtureLibrary() const;
    QString m_fixtureDirectory;
};

void PluginManagerTest::initTestCase()
{
    m_fixtureDirectory = qEnvironmentVariable("DELTA_X_TEST_PLUGIN_DIR");
    QVERIFY2(!m_fixtureDirectory.isEmpty(),
             "DELTA_X_TEST_PLUGIN_DIR was not provided by the test runner");
    QVERIFY2(!fixtureLibrary().isEmpty(), "The fake plugin library was not built");
}

QString PluginManagerTest::fixtureLibrary() const
{
    const QDir directory(m_fixtureDirectory);
    const QFileInfoList files = directory.entryInfoList(
        QDir::Files | QDir::Readable, QDir::Name | QDir::IgnoreCase);
    for (const QFileInfo& file : files) {
        if (QLibrary::isLibrary(file.fileName()))
            return file.absoluteFilePath();
    }
    return {};
}

void PluginManagerTest::loadsCapabilitiesCommandsAndSettings()
{
    PluginManager manager;
    manager.loadFromDirectories({m_fixtureDirectory});

    QCOMPARE(manager.loadedPluginIds(), QStringList{QStringLiteral("test.fixture")});
    QCOMPARE(manager.descriptors().size(), 1);
    const PluginDescriptor descriptor = manager.descriptors().first();
    QCOMPARE(descriptor.apiVersion, 2);
    QCOMPARE(descriptor.state, PluginDescriptor::State::Loaded);
    QVERIFY(descriptor.hasCapability(QStringLiteral("commands")));
    QVERIFY(manager.panelProvider(descriptor.id));
    QVERIFY(manager.panelProvider(descriptor.id)->panel());

    QTemporaryDir settingsDirectory;
    QVERIFY(settingsDirectory.isValid());
    QSettings settings(settingsDirectory.filePath(QStringLiteral("settings.ini")),
                       QSettings::IniFormat);

    QString error;
    QVERIFY(manager.executeCommand(
        descriptor.id, QStringLiteral("set-value"),
        {{QStringLiteral("value"), 42}}, nullptr, &error));
    manager.saveSettings(settings, QStringLiteral("project-a"));
    QVERIFY(manager.executeCommand(
        descriptor.id, QStringLiteral("set-value"),
        {{QStringLiteral("value"), 7}}, nullptr, &error));
    manager.loadSettings(settings, QStringLiteral("project-a"));

    QVariantMap result;
    QVERIFY(manager.executeCommand(descriptor.id, QStringLiteral("get-value"),
                                   {}, &result, &error));
    QCOMPARE(result.value(QStringLiteral("value")).toInt(), 42);
    QVERIFY(manager.shutdown());
    QVERIFY(manager.loadedPluginIds().isEmpty());
    QCOMPARE(manager.descriptors().first().state,
             PluginDescriptor::State::Unloaded);
}

void PluginManagerTest::rejectsDuplicateIds()
{
    QTemporaryDir directory;
    QVERIFY(directory.isValid());
    const QString source = fixtureLibrary();
    const QString suffix = QStringLiteral(".") + QFileInfo(source).suffix();
    QVERIFY(QFile::copy(source, directory.filePath(QStringLiteral("a") + suffix)));
    QVERIFY(QFile::copy(source, directory.filePath(QStringLiteral("b") + suffix)));

    PluginManager manager;
    manager.loadFromDirectories({directory.path()});
    QCOMPARE(manager.loadedPluginIds().size(), 1);
    const QVector<PluginDescriptor> descriptors = manager.descriptors();
    QCOMPARE(descriptors.size(), 2);
    QCOMPARE(std::count_if(descriptors.cbegin(),
                           descriptors.cend(),
                           [](const PluginDescriptor& descriptor) {
                               return descriptor.state ==
                                   PluginDescriptor::State::Rejected &&
                                   descriptor.error.contains(
                                       QStringLiteral("duplicate plugin id"));
                           }),
             1);
}

void PluginManagerTest::honorsDisabledIds()
{
    PluginManager manager;
    manager.setDisabledPluginIds({QStringLiteral("TEST.FIXTURE")});
    manager.loadFromDirectories({m_fixtureDirectory});
    QVERIFY(manager.loadedPluginIds().isEmpty());
    QCOMPARE(manager.descriptors().size(), 1);
    QCOMPARE(manager.descriptors().first().state,
             PluginDescriptor::State::Disabled);
}

void PluginManagerTest::ignoresMissingDirectories()
{
    PluginManager manager;
    manager.loadFromDirectories(
        {QDir(m_fixtureDirectory).filePath(QStringLiteral("does-not-exist"))});
    QVERIFY(manager.loadedPluginIds().isEmpty());
    QVERIFY(manager.descriptors().isEmpty());
}

QTEST_MAIN(PluginManagerTest)
#include "tst_plugin_manager.moc"
