#include "FakePlugin.h"

#include <QWidget>

FakePlugin::~FakePlugin()
{
    delete m_panel;
}

QString FakePlugin::id() const
{
    return QStringLiteral("test.fixture");
}

QString FakePlugin::displayName() const
{
    return QStringLiteral("Test Fixture");
}

QString FakePlugin::version() const
{
    return QStringLiteral("1.0.0");
}

QStringList FakePlugin::capabilities() const
{
    return {QStringLiteral("commands"), QStringLiteral("panel")};
}

void FakePlugin::loadSettings(QSettings& settings)
{
    m_value = settings.value(QStringLiteral("value"), 0).toInt();
}

void FakePlugin::saveSettings(QSettings& settings) const
{
    settings.setValue(QStringLiteral("value"), m_value);
}

QWidget* FakePlugin::panel()
{
    if (!m_panel)
        m_panel = new QWidget;
    return m_panel;
}

bool FakePlugin::executeCommand(const QString& command,
                                const QVariantMap& arguments,
                                QVariantMap* result,
                                QString* error)
{
    if (command == QStringLiteral("set-value")) {
        m_value = arguments.value(QStringLiteral("value")).toInt();
        return true;
    }
    if (command == QStringLiteral("get-value")) {
        if (result)
            result->insert(QStringLiteral("value"), m_value);
        return true;
    }
    if (error)
        *error = QStringLiteral("unknown command");
    return false;
}
