#include <QtTest>

#include "PluginManager.h"
#include "PluginExtensionRegistry.h"
#include "PluginHostContext.h"
#include "DeltaXPanelProvider.h"
#include "DeltaXDeviceProvider.h"
#include "DeltaXGScriptProvider.h"
#include "DeltaXPermissions.h"
#include "DeltaXServiceProvider.h"

#include <QDir>
#include <QFile>
#include <QComboBox>
#include <QGraphicsView>
#include <QLibrary>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTemporaryDir>
#include <QTreeWidget>

#include <algorithm>

class ContextExtensionProvider final : public QObject,
                                       public DeltaXDeviceProvider,
                                       public DeltaXGScriptProvider,
                                       public DeltaXServiceProvider
{
public:
    QVariantList gscriptPrimitives() const override
    {
        return {QVariantMap{
            {QStringLiteral("name"), QStringLiteral("contextecho")},
            {QStringLiteral("signature"),
             QStringLiteral("M98 PcontextEcho(value)")},
            {QStringLiteral("description"), QStringLiteral("Echo a value")},
            {QStringLiteral("minArgs"), 1},
            {QStringLiteral("maxArgs"), 1},
        }};
    }
    bool executeGScriptPrimitive(const QString&, const QVariantList& arguments,
                                 QVariant* result, QString*) override
    {
        if (result && !arguments.isEmpty())
            *result = arguments.first();
        return true;
    }
    QStringList deviceIds() const override
    {
        return {QStringLiteral("context.device0")};
    }
    bool submitDeviceCommand(const QString&, const QString&, quint64,
                             QString*) override
    {
        return true;
    }
    QVariantList services() const override
    {
        return {QVariantMap{
            {QStringLiteral("id"), QStringLiteral("context.echo")},
            {QStringLiteral("version"), QStringLiteral("1.0.0")},
            {QStringLiteral("methods"), QStringList{QStringLiteral("echo")}},
        }};
    }
    bool invokeService(const QString&, const QString&,
                       const QVariantMap& request, QVariantMap* response,
                       QString*) override
    {
        if (response)
            *response = request;
        return true;
    }
};

class InvalidExtensionProvider final : public QObject,
                                       public DeltaXDeviceProvider,
                                       public DeltaXGScriptProvider,
                                       public DeltaXServiceProvider
{
public:
    QVariantList gscriptPrimitives() const override
    {
        return {QVariantMap{
            {QStringLiteral("name"), QStringLiteral("invalid-name")},
            {QStringLiteral("signature"), QStringLiteral("M98 PinvalidName()")},
            {QStringLiteral("minArgs"), 0},
            {QStringLiteral("maxArgs"), 0},
        }};
    }
    bool executeGScriptPrimitive(const QString&, const QVariantList&,
                                 QVariant*, QString*) override
    {
        return true;
    }
    QStringList deviceIds() const override
    {
        return {QStringLiteral("Duplicate.Device0"),
                QStringLiteral("duplicate.device0")};
    }
    bool submitDeviceCommand(const QString&, const QString&, quint64,
                             QString*) override
    {
        return true;
    }
    QVariantList services() const override
    {
        return {QVariantMap{
            {QStringLiteral("id"), QStringLiteral("invalid.service")},
            {QStringLiteral("version"), QStringLiteral("1.0.0")},
            {QStringLiteral("methods"),
             QStringList{QStringLiteral("Echo"), QStringLiteral("echo")}},
        }};
    }
    bool invokeService(const QString&, const QString&, const QVariantMap&,
                       QVariantMap*, QString*) override
    {
        return true;
    }
};

class PluginManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanup();
    void loadsCapabilitiesCommandsAndSettings();
    void activatesV3WithPermissionCheckedExtensions();
    void loadsBundledBlockProgrammingPlugin();
    void deniesV3ExtensionsWithoutGrants();
    void hostContextRoutesAndEnforcesPermissions();
    void rejectsExtensionCollisions();
    void rejectsInvalidExtensionDescriptors();
    void rejectsV3WhenSettingsCannotLoad();
    void rejectsDuplicateIds();
    void honorsDisabledIds();
    void ignoresMissingDirectories();

private:
    QString fixtureLibrary() const;
    QString m_fixtureDirectory;
    QString m_v3FixtureDirectory;
    QString m_blockPluginDirectory;
};

void PluginManagerTest::initTestCase()
{
    m_fixtureDirectory = qEnvironmentVariable("DELTA_X_TEST_PLUGIN_DIR");
    m_v3FixtureDirectory = qEnvironmentVariable("DELTA_X_TEST_PLUGIN_V3_DIR");
    m_blockPluginDirectory = qEnvironmentVariable("DELTA_X_BLOCK_PLUGIN_DIR");
    QVERIFY2(!m_fixtureDirectory.isEmpty(),
             "DELTA_X_TEST_PLUGIN_DIR was not provided by the test runner");
    QVERIFY2(!fixtureLibrary().isEmpty(), "The fake plugin library was not built");
    QVERIFY2(!m_v3FixtureDirectory.isEmpty(),
             "DELTA_X_TEST_PLUGIN_V3_DIR was not provided by the test runner");
    QVERIFY2(QDir(m_v3FixtureDirectory).exists(),
             "The v3 fake plugin directory was not built");
    QVERIFY2(!m_blockPluginDirectory.isEmpty(),
             "DELTA_X_BLOCK_PLUGIN_DIR was not provided by the test runner");
    QVERIFY2(QDir(m_blockPluginDirectory).exists(),
             "The Block Programming plugin directory was not built");
}

void PluginManagerTest::cleanup()
{
    PluginExtensionRegistry::instance().clearForTests();
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

void PluginManagerTest::activatesV3WithPermissionCheckedExtensions()
{
    QHash<QString, QVariant> variables;
    QString completedDevice;
    QString completedResponse;
    QString healthState;
    QStringList registeredDevices;

    PluginHostServices services;
    services.projectScope = QStringLiteral("project-v3");
    services.readVariable = [&variables](const QString& key,
                                         const QVariant& fallback) {
        return variables.value(key, fallback);
    };
    services.writeVariable = [&variables](const QString& key,
                                          const QVariant& value, bool,
                                          QString*) {
        variables.insert(key, value);
        return true;
    };
    services.removeVariable = [&variables](const QString& key, QString*) {
        variables.remove(key);
        return true;
    };
    services.completeDeviceCommand =
        [&completedDevice, &completedResponse](const QString& device,
                                               const QString& response,
                                               QString*) {
        completedDevice = device;
        completedResponse = response;
        return true;
    };
    services.registerDevice = [&registeredDevices](const QString& device) {
        registeredDevices.append(device);
    };
    services.reportHealth =
        [&healthState](const QString&, const QString& state, const QString&,
                       const QVariantMap&, QString*) {
        healthState = state;
        return true;
    };

    const QSet<QString> permissions = {
        DeltaXPermissions::DevicesProvide,
        DeltaXPermissions::EventsPublish,
        DeltaXPermissions::GScriptRegister,
        DeltaXPermissions::HealthReport,
        DeltaXPermissions::ServicesProvide,
        DeltaXPermissions::VariablesWriteRuntime,
    };

    PluginManager manager;
    manager.setHostServices(services);
    manager.setGrantedPermissions(
        {{QStringLiteral("test.fixture.v3"), permissions}});
    manager.loadFromDirectories({m_v3FixtureDirectory});
    QCOMPARE(manager.loadedPluginIds(),
             QStringList{QStringLiteral("test.fixture.v3")});
    QCOMPARE(manager.descriptors().first().apiVersion, 3);
    QVERIFY(!manager.descriptors().first().active);

    QTemporaryDir settingsDirectory;
    QVERIFY(settingsDirectory.isValid());
    QSettings settings(settingsDirectory.filePath(QStringLiteral("v3.ini")),
                       QSettings::IniFormat);
    manager.loadSettings(settings, QStringLiteral("project-v3"));

    const PluginDescriptor descriptor = manager.descriptors().first();
    QCOMPARE(descriptor.state, PluginDescriptor::State::Loaded);
    QVERIFY(descriptor.active);
    QCOMPARE(descriptor.grantedPermissions.size(), permissions.size());
    QVERIFY(descriptor.missingPermissions.isEmpty());
    QCOMPARE(variables.value(QStringLiteral("Fixture.Started")).toBool(), true);
    QCOMPARE(healthState, QStringLiteral("ready"));
    QCOMPARE(registeredDevices,
             QStringList{QStringLiteral("fixture.device0")});

    PluginExtensionRegistry& registry = PluginExtensionRegistry::instance();
    QVERIFY(registry.hasGScriptPrimitive(QStringLiteral("fixturemultiply")));
    QVariant primitiveResult;
    QString error;
    QVERIFY(registry.executeGScriptPrimitive(
        QStringLiteral("fixturemultiply"), {6.0, 7.0}, &primitiveResult, &error));
    QCOMPARE(primitiveResult.toDouble(), 42.0);

    QVERIFY(registry.hasDevice(QStringLiteral("fixture.device0")));
    QVERIFY(registry.dispatchDeviceCommand(
        QStringLiteral("fixture.device0"), QStringLiteral("PING"), 9, &error));
    QCOMPARE(completedDevice, QStringLiteral("fixture.device0"));
    QCOMPARE(completedResponse, QStringLiteral("ok:PING"));

    QVariantMap serviceResult;
    QVERIFY(registry.invokeService(
        QStringLiteral("fixture.echo"), QStringLiteral("echo"),
        {{QStringLiteral("value"), 42}}, &serviceResult, &error));
    QCOMPARE(serviceResult.value(QStringLiteral("value")).toInt(), 42);

    QVariantMap commandResult;
    QVERIFY(manager.executeCommand(QStringLiteral("test.fixture.v3"),
                                   QStringLiteral("publish-event"),
                                   {{QStringLiteral("value"), 5}},
                                   &commandResult, &error));
    const QVariantList events = registry.eventsSince(0);
    QCOMPARE(events.size(), 1);
    QCOMPARE(events.first().toMap().value(QStringLiteral("topic")).toString(),
             QStringLiteral("fixture.changed"));

    QVERIFY(manager.shutdown());
    QCOMPARE(variables.value(QStringLiteral("Fixture.Stopped")).toBool(), true);
    QVERIFY(!registry.hasDevice(QStringLiteral("fixture.device0")));
    QVERIFY(!registry.hasGScriptPrimitive(QStringLiteral("fixturemultiply")));
}

void PluginManagerTest::loadsBundledBlockProgrammingPlugin()
{
    PluginManager disabledByDefault;
    disabledByDefault.loadFromDirectories({m_blockPluginDirectory});
    QVERIFY(disabledByDefault.loadedPluginIds().isEmpty());
    QCOMPARE(disabledByDefault.descriptors().size(), 1);
    const PluginDescriptor defaultDescriptor =
        disabledByDefault.descriptors().first();
    QCOMPARE(defaultDescriptor.state, PluginDescriptor::State::Disabled);
    QVERIFY(defaultDescriptor.experimental);
    QVERIFY(!defaultDescriptor.defaultEnabled);

    bool sourceLoaded = false;
    bool sourceRun = false;
    bool workerStopped = false;
    QString healthState;

    PluginHostServices services;
    services.projectScope = QStringLiteral("block-plugin-project");
    services.gscriptWorkers = [](QString*) {
        return QVariantList{QVariantMap{
            {QStringLiteral("index"), 0},
            {QStringLiteral("id"), QStringLiteral("thread0")},
            {QStringLiteral("state"), QStringLiteral("Idle")},
            {QStringLiteral("running"), false},
            {QStringLiteral("sourceLength"), 0},
        }};
    };
    services.validateGScript = [](const QString&, QString*) {
        return QVariantList{};
    };
    services.loadGScript = [&sourceLoaded](int, const QString&, QString*) {
        sourceLoaded = true;
        return true;
    };
    services.runGScript = [&sourceRun](int, const QString&, QString*) {
        sourceRun = true;
        return true;
    };
    services.stopGScript = [&workerStopped](int, QString*) {
        workerStopped = true;
        return true;
    };
    services.reportHealth = [&healthState](const QString&, const QString& state,
                                            const QString&, const QVariantMap&,
                                            QString*) {
        healthState = state;
        return true;
    };

    const QSet<QString> permissions = {
        DeltaXPermissions::GScriptRead,
        DeltaXPermissions::GScriptEdit,
        DeltaXPermissions::GScriptRun,
        DeltaXPermissions::HealthReport,
    };
    PluginManager manager;
    manager.setEnabledPluginIds(
        {QStringLiteral("deltax.block-programming")});
    manager.setHostServices(services);
    manager.setGrantedPermissions(
        {{QStringLiteral("deltax.block-programming"), permissions}});
    manager.loadFromDirectories({m_blockPluginDirectory});
    QCOMPARE(manager.loadedPluginIds(),
             QStringList{QStringLiteral("deltax.block-programming")});

    QTemporaryDir settingsDirectory;
    QVERIFY(settingsDirectory.isValid());
    QSettings settings(settingsDirectory.filePath(QStringLiteral("blocks.ini")),
                       QSettings::IniFormat);
    manager.loadSettings(settings, QStringLiteral("block-plugin-project"));

    const PluginDescriptor descriptor = manager.descriptors().first();
    QVERIFY(descriptor.active);
    QCOMPARE(descriptor.apiVersion, 3);
    QCOMPARE(descriptor.version, QStringLiteral("2.0.0"));
    QCOMPARE(descriptor.grantedPermissions.size(), permissions.size());
    QCOMPARE(healthState, QStringLiteral("ready"));
    QVERIFY(manager.panelProvider(descriptor.id));
    QWidget* panel = manager.panelProvider(descriptor.id)->panel();
    QVERIFY(panel);
    panel->resize(550, 620);
    panel->show();
    QCoreApplication::processEvents();
    auto* palette = panel->findChild<QTreeWidget*>(
        QStringLiteral("blockPalette"));
    auto* paletteSearch = panel->findChild<QLineEdit*>(
        QStringLiteral("blockPaletteSearch"));
    auto* canvas = panel->findChild<QGraphicsView*>(
        QStringLiteral("blockCanvas"));
    auto* inspector = panel->findChild<QTabWidget*>(
        QStringLiteral("blockInspectorTabs"));
    QVERIFY(palette);
    QVERIFY(paletteSearch);
    QVERIFY(canvas);
    QVERIFY(canvas->scene());
    QVERIFY(canvas->sceneRect().width() >= 500.0);
    QVERIFY(inspector);
    QVERIFY2(palette->width() >= 120,
             "The palette collapsed at the supported narrow module width");
    QVERIFY2(canvas->width() >= 220,
             "The block canvas collapsed at the supported narrow module width");
    QVERIFY2(inspector->height() >= 100,
             "The responsive inspector is not usable at the supported height");

    QString error;
    QVariantMap catalog;
    QVERIFY(manager.executeCommand(descriptor.id, QStringLiteral("catalog"),
                                   {}, &catalog, &error));
    QVERIFY(catalog.value(QStringLiteral("blocks")).toList().size() >= 20);
    QVERIFY(catalog.value(QStringLiteral("templates")).toStringList().contains(
        QStringLiteral("Robot conveyor pick worker")));
    QVERIFY(catalog.value(QStringLiteral("templates")).toStringList().contains(
        QStringLiteral("Software self-test")));

    auto* templateCombo = panel->findChild<QComboBox*>(
        QStringLiteral("blockTemplateCombo"));
    auto* workspace = panel->findChild<QTreeWidget*>(
        QStringLiteral("blockWorkspace"));
    auto* preview = panel->findChild<QPlainTextEdit*>(
        QStringLiteral("blockPreview"));
    auto* diagnostics = panel->findChild<QTreeWidget*>(
        QStringLiteral("blockDiagnostics"));
    auto* loadButton = panel->findChild<QPushButton*>(
        QStringLiteral("blockLoadButton"));
    auto* runButton = panel->findChild<QPushButton*>(
        QStringLiteral("blockRunButton"));
    QVERIFY(templateCombo && workspace && preview && diagnostics &&
            loadButton && runButton);
    const int selfTestIndex = templateCombo->findText(
        QStringLiteral("Software self-test"));
    QVERIFY(selfTestIndex >= 0);
    templateCombo->setCurrentIndex(selfTestIndex);
    QVERIFY(QMetaObject::invokeMethod(templateCombo, "activated",
                                      Qt::DirectConnection,
                                      Q_ARG(int, selfTestIndex)));
    QTRY_VERIFY(workspace->topLevelItemCount() > 0);
    QTRY_VERIFY(preview->toPlainText().contains(
        QStringLiteral("PASS block programming")));
    QCOMPARE(diagnostics->topLevelItemCount(), 0);
    QVERIFY(loadButton->isEnabled());
    QVERIFY(runButton->isEnabled());

    QVariantMap generated;
    QVERIFY(manager.executeCommand(
        descriptor.id, QStringLiteral("template"),
        {{QStringLiteral("name"),
          QStringLiteral("Robot conveyor pick worker")}},
        &generated, &error));
    QVERIFY(generated.value(QStringLiteral("valid")).toBool());
    QVERIFY(generated.value(QStringLiteral("script")).toString().contains(
        QStringLiteral("PclaimObject")));

    QVariantMap recompiled;
    QVERIFY(manager.executeCommand(
        descriptor.id, QStringLiteral("compile"),
        {{QStringLiteral("document"),
          generated.value(QStringLiteral("document"))}},
        &recompiled, &error));
    QVERIFY(recompiled.value(QStringLiteral("valid")).toBool());
    QCOMPARE(recompiled.value(QStringLiteral("script")),
             generated.value(QStringLiteral("script")));

    manager.saveSettings(settings, QStringLiteral("block-plugin-project"));
    QVERIFY(!sourceLoaded);
    QVERIFY(!sourceRun);
    QVERIFY(!workerStopped);
    QVERIFY(manager.shutdown());
    QCOMPARE(healthState, QStringLiteral("stopped"));
}

void PluginManagerTest::deniesV3ExtensionsWithoutGrants()
{
    PluginManager manager;
    PluginHostServices services;
    services.projectScope = QStringLiteral("project-denied");
    manager.setHostServices(services);
    manager.loadFromDirectories({m_v3FixtureDirectory});

    QTemporaryDir settingsDirectory;
    QVERIFY(settingsDirectory.isValid());
    QSettings settings(settingsDirectory.filePath(QStringLiteral("denied.ini")),
                       QSettings::IniFormat);
    manager.loadSettings(settings, QStringLiteral("project-denied"));

    const PluginDescriptor descriptor = manager.descriptors().first();
    QVERIFY(descriptor.active);
    QVERIFY(descriptor.grantedPermissions.isEmpty());
    QCOMPARE(descriptor.missingPermissions.size(), 6);
    QVERIFY(!PluginExtensionRegistry::instance().hasGScriptPrimitive(
        QStringLiteral("fixturemultiply")));
    QVERIFY(!PluginExtensionRegistry::instance().hasDevice(
        QStringLiteral("fixture.device0")));

    QString error;
    QVERIFY(!manager.executeCommand(
        descriptor.id, QStringLiteral("publish-event"), {}, nullptr, &error));
    QVERIFY(error.contains(QStringLiteral("permission 'events.publish'")));
}

void PluginManagerTest::hostContextRoutesAndEnforcesPermissions()
{
    QVariant storedValue;
    bool persistentWrite = false;
    bool removed = false;
    QString submittedOwner;
    QString completedResponse;
    bool detectionsSubmitted = false;
    bool released = false;
    bool completed = false;
    QString claimedOwner;
    QString releasedOwner;
    QString completedOwner;
    int loadedWorker = -1;
    int runningWorker = -1;
    int stoppedWorker = -1;
    QString reportedHealth;
    QString telemetryMetric;
    QString stopReason;
    QString logMessage;

    PluginHostServices services;
    services.projectScope = QStringLiteral("context-project");
    services.readVariable = [](const QString&, const QVariant&) {
        return QVariant(42);
    };
    services.writeVariable = [&storedValue, &persistentWrite](
        const QString&, const QVariant& value, bool persistent, QString*) {
        storedValue = value;
        persistentWrite = persistent;
        return true;
    };
    services.removeVariable = [&removed](const QString&, QString*) {
        removed = true;
        return true;
    };
    services.submitDeviceCommand = [&submittedOwner](
        const QString& owner, const QString&, const QString&, bool, int,
        QString*) {
        submittedOwner = owner;
        return quint64(77);
    };
    services.completeDeviceCommand = [&completedResponse](
        const QString&, const QString& response, QString*) {
        completedResponse = response;
        return true;
    };
    services.submitDetections = [&detectionsSubmitted](const QVariantMap&,
                                                       QString*) {
        detectionsSubmitted = true;
        return true;
    };
    services.trackingSnapshot = [](int, QString*) {
        return QVariantList{QVariantMap{{QStringLiteral("uid"), 12}}};
    };
    services.claimObject = [&claimedOwner](int, const QVariantMap& request,
                                           QString*) {
        claimedOwner = request.value(QStringLiteral("owner")).toString();
        return QVariantMap{{QStringLiteral("Found"), 1},
                           {QStringLiteral("UID"), 12}};
    };
    services.releaseObject = [&released, &releasedOwner](
        int, int, const QString& owner, QString*) {
        released = true;
        releasedOwner = owner;
        return true;
    };
    services.completeObject = [&completed, &completedOwner](
        int, int, const QString& owner, QString*) {
        completed = true;
        completedOwner = owner;
        return true;
    };
    services.gscriptWorkers = [](QString*) {
        return QVariantList{QVariantMap{
            {QStringLiteral("index"), 0},
            {QStringLiteral("id"), QStringLiteral("thread0")},
        }};
    };
    services.validateGScript = [](const QString& source, QString*) {
        if (source.contains(QStringLiteral("invalid"))) {
            return QVariantList{QVariantMap{
                {QStringLiteral("severity"), QStringLiteral("Error")},
                {QStringLiteral("code"), QStringLiteral("TEST")},
            }};
        }
        return QVariantList{};
    };
    services.loadGScript = [&loadedWorker](int worker, const QString&,
                                           QString*) {
        loadedWorker = worker;
        return true;
    };
    services.runGScript = [&runningWorker](int worker, const QString&,
                                           QString*) {
        runningWorker = worker;
        return true;
    };
    services.stopGScript = [&stoppedWorker](int worker, QString*) {
        stoppedWorker = worker;
        return true;
    };
    services.reportHealth = [&reportedHealth](
        const QString&, const QString& state, const QString&,
        const QVariantMap&, QString*) {
        reportedHealth = state;
        return true;
    };
    services.publishTelemetry = [&telemetryMetric](
        const QString&, const QString& metric, const QVariant&,
        const QVariantMap&, QString*) {
        telemetryMetric = metric;
        return true;
    };
    services.requestControlledStop = [&stopReason](const QString& reason,
                                                   QString*) {
        stopReason = reason;
        return true;
    };
    services.log = [&logMessage](const QString&, const QString&,
                                 const QString& message) {
        logMessage = message;
    };

    const QStringList requested = DeltaXPermissions::all();
    const QSet<QString> grants(requested.cbegin(), requested.cend());
    PluginHostContext context(QStringLiteral("test.context"), requested,
                              grants, services);
    QCOMPARE(context.projectScope(), QStringLiteral("context-project"));
    QCOMPARE(context.readVariable(QStringLiteral("A"), 0).toInt(), 42);

    QString error;
    QVERIFY(context.writeVariable(QStringLiteral("A"), 9, true, &error));
    QCOMPARE(storedValue.toInt(), 9);
    QVERIFY(persistentWrite);
    QVERIFY(context.removeVariable(QStringLiteral("A"), &error));
    QVERIFY(removed);

    const quint64 eventSequence = context.publishEvent(
        QStringLiteral("context.changed"), {{QStringLiteral("value"), 1}},
        &error);
    QVERIFY(eventSequence > 0);
    QCOMPARE(context.eventsSince(0, QStringLiteral("context.changed"), 10,
                                 &error).size(),
             1);

    QCOMPARE(context.submitDeviceCommand(QStringLiteral("robot0"),
                                         QStringLiteral("M84"), false, 100,
                                         &error),
             quint64(77));
    QCOMPARE(submittedOwner, QStringLiteral("plugin/test.context"));

    ContextExtensionProvider provider;
    PluginExtensionRegistry& registry = PluginExtensionRegistry::instance();
    QVERIFY(registry.registerDeviceProvider(QStringLiteral("test.context"),
                                            &provider, &provider, &error));
    QVERIFY(registry.registerServiceProvider(QStringLiteral("test.context"),
                                             &provider, &provider, &error));
    QVERIFY(context.completeDeviceCommand(QStringLiteral("context.device0"),
                                          QStringLiteral("ok"), &error));
    QCOMPARE(completedResponse, QStringLiteral("ok"));

    QVERIFY(context.submitDetections(
        {{QStringLiteral("frameId"), 1}}, &error));
    QVERIFY(detectionsSubmitted);
    QCOMPARE(context.trackingSnapshot(0, &error).first().toMap()
                 .value(QStringLiteral("uid")).toInt(),
             12);
    QCOMPARE(context.claimObject(0, {{QStringLiteral("owner"),
                                      QStringLiteral("worker")}}, &error)
                 .value(QStringLiteral("Found")).toInt(),
             1);
    QCOMPARE(claimedOwner, QStringLiteral("plugin/test.context/worker"));
    QVERIFY(context.releaseObject(0, 12, QStringLiteral("worker"), &error));
    QVERIFY(context.completeObject(0, 12, QStringLiteral("worker"), &error));
    QVERIFY(released);
    QVERIFY(completed);
    QCOMPARE(releasedOwner, QStringLiteral("plugin/test.context/worker"));
    QCOMPARE(completedOwner, QStringLiteral("plugin/test.context/worker"));

    QCOMPARE(context.gscriptWorkers(&error).first().toMap()
                 .value(QStringLiteral("id")).toString(),
             QStringLiteral("thread0"));
    QVERIFY(context.validateGScript(QStringLiteral("robot0 G28"), &error)
                .isEmpty());
    QCOMPARE(context.validateGScript(QStringLiteral("invalid"), &error).size(),
             1);
    QVERIFY(context.loadGScript(1, QStringLiteral("robot0 G28"), &error));
    QVERIFY(context.runGScript(2, QStringLiteral("robot0 G28"), &error));
    QVERIFY(context.stopGScript(3, &error));
    QCOMPARE(loadedWorker, 1);
    QCOMPARE(runningWorker, 2);
    QCOMPARE(stoppedWorker, 3);

    QVariantMap response;
    const QVariantList catalog = context.serviceCatalog(&error);
    QCOMPARE(catalog.size(), 1);
    QCOMPARE(catalog.first().toMap().value(QStringLiteral("version")).toString(),
             QStringLiteral("1.0.0"));
    QVERIFY(context.invokeService(
        QStringLiteral("context.echo"), QStringLiteral("echo"),
        {{QStringLiteral("value"), 5}}, &response, &error));
    QCOMPARE(response.value(QStringLiteral("value")).toInt(), 5);
    QVERIFY(context.reportHealth(QStringLiteral("ready"), {}, {}, &error));
    QCOMPARE(reportedHealth, QStringLiteral("ready"));
    QVERIFY(context.publishTelemetry(QStringLiteral("latency"), 4, {}, &error));
    QCOMPARE(telemetryMetric, QStringLiteral("latency"));
    QVERIFY(context.requestControlledStop(QStringLiteral("test stop"), &error));
    QCOMPARE(stopReason, QStringLiteral("test stop"));
    context.log(QStringLiteral("info"), QStringLiteral("hello"));
    QCOMPARE(logMessage, QStringLiteral("hello"));

    context.invalidate();
    QVERIFY(!context.writeVariable(QStringLiteral("A"), 1, false, &error));
    QVERIFY(error.contains(QStringLiteral("no longer active")));

    PluginHostContext denied(QStringLiteral("test.denied"), requested, {}, services);
    QCOMPARE(denied.readVariable(QStringLiteral("A"), 7).toInt(), 7);
    QVERIFY(denied.gscriptWorkers(&error).isEmpty());
    QVERIFY(error.contains(DeltaXPermissions::GScriptRead));
    QVERIFY(!denied.loadGScript(4, QStringLiteral("robot0 G28"), &error));
    QVERIFY(error.contains(DeltaXPermissions::GScriptEdit));
    QVERIFY(!denied.runGScript(4, QStringLiteral("robot0 G28"), &error));
    QVERIFY(error.contains(DeltaXPermissions::GScriptRun));
    QVERIFY(!denied.stopGScript(4, &error));
    QVERIFY(error.contains(DeltaXPermissions::GScriptRun));
    QCOMPARE(loadedWorker, 1);
    QCOMPARE(runningWorker, 2);
    QCOMPARE(stoppedWorker, 3);
    QVERIFY(!denied.requestControlledStop(QStringLiteral("denied"), &error));
    QVERIFY(error.contains(DeltaXPermissions::CellControl));
}

void PluginManagerTest::rejectsV3WhenSettingsCannotLoad()
{
    PluginManager manager;
    PluginHostServices services;
    services.projectScope = QStringLiteral("project-failure");
    manager.setHostServices(services);
    manager.loadFromDirectories({m_v3FixtureDirectory});

    QTemporaryDir settingsDirectory;
    QVERIFY(settingsDirectory.isValid());
    QSettings settings(settingsDirectory.filePath(QStringLiteral("failure.ini")),
                       QSettings::IniFormat);
    settings.setValue(
        QStringLiteral("PluginSystem/Projects/project-failure/test.fixture.v3/failLoad"),
        true);
    manager.loadSettings(settings, QStringLiteral("project-failure"));

    const PluginDescriptor descriptor = manager.descriptors().first();
    QCOMPARE(descriptor.state, PluginDescriptor::State::Rejected);
    QVERIFY(!descriptor.active);
    QVERIFY(descriptor.error.contains(QStringLiteral("settings failure")));
    QVERIFY(!PluginExtensionRegistry::instance().hasGScriptPrimitive(
        QStringLiteral("fixturemultiply")));
    QString error;
    QVERIFY(!manager.executeCommand(descriptor.id, QStringLiteral("status"),
                                    {}, nullptr, &error));
    QVERIFY(error.contains(QStringLiteral("not active")));
}

void PluginManagerTest::rejectsExtensionCollisions()
{
    ContextExtensionProvider first;
    ContextExtensionProvider second;
    PluginExtensionRegistry& registry = PluginExtensionRegistry::instance();
    QString error;

    QVERIFY(registry.registerGScriptProvider(
        QStringLiteral("test.first"), &first, &first, &error));
    QVERIFY(registry.registerDeviceProvider(
        QStringLiteral("test.first"), &first, &first, &error));
    QVERIFY(registry.registerServiceProvider(
        QStringLiteral("test.first"), &first, &first, &error));

    QVERIFY(!registry.registerGScriptProvider(
        QStringLiteral("test.second"), &second, &second, &error));
    QVERIFY(error.contains(QStringLiteral("already registered")));
    QVERIFY(!registry.registerDeviceProvider(
        QStringLiteral("test.second"), &second, &second, &error));
    QVERIFY(error.contains(QStringLiteral("already registered")));
    QVERIFY(!registry.registerServiceProvider(
        QStringLiteral("test.second"), &second, &second, &error));
    QVERIFY(error.contains(QStringLiteral("already registered")));

    QCOMPARE(registry.gscriptPrimitives().first().pluginId,
             QStringLiteral("test.first"));
    QVERIFY(registry.ownsDevice(QStringLiteral("test.first"),
                               QStringLiteral("context.device0")));
}

void PluginManagerTest::rejectsInvalidExtensionDescriptors()
{
    InvalidExtensionProvider provider;
    PluginExtensionRegistry& registry = PluginExtensionRegistry::instance();
    QString error;

    QVERIFY(!registry.registerGScriptProvider(
        QStringLiteral("test.invalid"), &provider, &provider, &error));
    QVERIFY(error.contains(QStringLiteral("invalid or reserved")));
    QVERIFY(!registry.registerDeviceProvider(
        QStringLiteral("test.invalid"), &provider, &provider, &error));
    QVERIFY(error.contains(QStringLiteral("duplicate plugin device")));
    QVERIFY(!registry.registerServiceProvider(
        QStringLiteral("test.invalid"), &provider, &provider, &error));
    QVERIFY(error.contains(QStringLiteral("methods must be unique")));
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
