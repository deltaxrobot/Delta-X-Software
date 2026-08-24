#include "PluginManagerWidget.h"

#include "PluginManager.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QCheckBox>
#include <QDesktopServices>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileInfo>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QStandardPaths>
#include <QTableWidget>
#include <QUrl>
#include <QVBoxLayout>

namespace
{
constexpr int PluginIdRole = Qt::UserRole + 1;
}

PluginManagerWidget::PluginManagerWidget(PluginManager* manager,
                                         const QString& builtInDirectory,
                                         QWidget* parent)
    : QWidget(parent)
    , m_manager(manager)
    , m_builtInDirectory(QDir::cleanPath(builtInDirectory))
{
    auto* layout = new QVBoxLayout(this);

    auto* title = new QLabel(tr("Plugin Manager"), this);
    QFont titleFont = title->font();
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 2);
    title->setFont(titleFont);
    layout->addWidget(title);

    auto* explanation = new QLabel(
        tr("Only plugins from the built-in directory and explicitly enabled "
           "directories are discovered. Changes to plugin availability apply "
           "after the application restarts."),
        this);
    explanation->setWordWrap(true);
    layout->addWidget(explanation);

    m_summaryLabel = new QLabel(this);
    layout->addWidget(m_summaryLabel);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(8);
    m_table->setHorizontalHeaderLabels(
        {tr("Enabled"), tr("Plugin"), tr("Version"), tr("API"),
         tr("Capabilities"), tr("Permissions"), tr("State"), tr("Details")});
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setAlternatingRowColors(true);
    m_table->verticalHeader()->setVisible(false);
    m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    layout->addWidget(m_table, 1);

    auto* controls = new QHBoxLayout;
    m_enableUserDirectory = new QCheckBox(
        tr("Enable per-user plugin directory"), this);
    m_enableUserDirectory->setChecked(
        QSettings().value(QStringLiteral("PluginSystem/EnableUserPluginDirectory"),
                          false)
            .toBool());
    controls->addWidget(m_enableUserDirectory);

    auto* builtInButton = new QPushButton(tr("Open Built-in Folder"), this);
    auto* userButton = new QPushButton(tr("Open User Folder"), this);
    auto* documentationButton = new QPushButton(tr("Documentation"), this);
    auto* permissionsButton = new QPushButton(tr("Permissions..."), this);
    controls->addStretch();
    controls->addWidget(permissionsButton);
    controls->addWidget(builtInButton);
    controls->addWidget(userButton);
    controls->addWidget(documentationButton);
    layout->addLayout(controls);

    m_restartLabel = new QLabel(this);
    m_restartLabel->setWordWrap(true);
    m_restartLabel->setStyleSheet(QStringLiteral("color: #e6a700;"));
    layout->addWidget(m_restartLabel);

    connect(m_table, &QTableWidget::cellChanged,
            this, &PluginManagerWidget::updateDisabledPlugin);
    connect(m_enableUserDirectory, &QCheckBox::toggled,
            this, &PluginManagerWidget::updateUserDirectorySetting);
    connect(builtInButton, &QPushButton::clicked,
            this, &PluginManagerWidget::openBuiltInDirectory);
    connect(userButton, &QPushButton::clicked,
            this, &PluginManagerWidget::openUserDirectory);
    connect(documentationButton, &QPushButton::clicked,
            this, &PluginManagerWidget::openDocumentation);
    connect(permissionsButton, &QPushButton::clicked,
            this, &PluginManagerWidget::configurePermissions);

    refresh();
}

void PluginManagerWidget::refresh()
{
    if (!m_manager)
        return;

    m_refreshing = true;
    const QVector<PluginDescriptor> descriptors = m_manager->descriptors();
    m_table->setRowCount(descriptors.size());

    int loaded = 0;
    int disabled = 0;
    int rejected = 0;
    for (int row = 0; row < descriptors.size(); ++row) {
        const PluginDescriptor& descriptor = descriptors.at(row);
        if (descriptor.state == PluginDescriptor::State::Loaded)
            ++loaded;
        else if (descriptor.state == PluginDescriptor::State::Disabled)
            ++disabled;
        else if (descriptor.state == PluginDescriptor::State::Rejected)
            ++rejected;

        auto* enabledItem = new QTableWidgetItem;
        enabledItem->setData(PluginIdRole, descriptor.id);
        enabledItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable |
                              Qt::ItemIsUserCheckable);
        enabledItem->setCheckState(
            descriptor.state == PluginDescriptor::State::Disabled
                ? Qt::Unchecked
                : Qt::Checked);
        m_table->setItem(row, 0, enabledItem);

        auto setText = [this, row](int column, const QString& value) {
            auto* item = new QTableWidgetItem(value);
            item->setToolTip(value);
            m_table->setItem(row, column, item);
        };
        setText(1, descriptor.displayName.isEmpty()
                       ? descriptor.id
                       : descriptor.displayName);
        setText(2, descriptor.version.isEmpty()
                       ? tr("Legacy")
                       : descriptor.version);
        setText(3, QString::number(descriptor.apiVersion));
        setText(4, descriptor.capabilities.join(QStringLiteral(", ")));
        QString permissionText;
        if (!descriptor.requestedPermissions.isEmpty()) {
            permissionText = tr("%1 granted").arg(
                descriptor.grantedPermissions.size());
            if (!descriptor.missingPermissions.isEmpty()) {
                permissionText += tr("; denied: %1")
                                      .arg(descriptor.missingPermissions.join(", "));
            }
        } else {
            permissionText = descriptor.apiVersion >= 3
                ? tr("None requested") : tr("Legacy contract");
        }
        setText(5, permissionText);
        setText(6, descriptor.stateName());
        setText(7, descriptor.error.isEmpty()
                       ? descriptor.filePath
                       : descriptor.error + QStringLiteral(" — ") +
                             descriptor.filePath);
    }
    m_summaryLabel->setText(
        tr("%1 loaded · %2 disabled · %3 rejected")
            .arg(loaded)
            .arg(disabled)
            .arg(rejected));
    m_refreshing = false;
}

void PluginManagerWidget::updateDisabledPlugin(int row, int column)
{
    if (m_refreshing || column != 0)
        return;
    QTableWidgetItem* item = m_table->item(row, column);
    if (!item)
        return;

    const QString pluginId = item->data(PluginIdRole).toString();
    if (pluginId.isEmpty())
        return;
    QSettings settings;
    QSet<QString> disabled;
    const QStringList configured =
        settings.value(QStringLiteral("PluginSystem/DisabledPluginIds"))
            .toStringList();
    for (const QString& id : configured)
        disabled.insert(id.trimmed().toLower());

    if (item->checkState() == Qt::Checked)
        disabled.remove(pluginId.toLower());
    else
        disabled.insert(pluginId.toLower());

    QStringList values(disabled.cbegin(), disabled.cend());
    values.sort(Qt::CaseInsensitive);
    settings.setValue(QStringLiteral("PluginSystem/DisabledPluginIds"), values);
    settings.sync();
    markRestartRequired();
}

void PluginManagerWidget::updateUserDirectorySetting(bool enabled)
{
    QSettings settings;
    settings.setValue(QStringLiteral("PluginSystem/EnableUserPluginDirectory"),
                      enabled);
    settings.sync();
    markRestartRequired();
}

void PluginManagerWidget::openBuiltInDirectory()
{
    QDir().mkpath(m_builtInDirectory);
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_builtInDirectory));
}

void PluginManagerWidget::openUserDirectory()
{
    const QString directory = userPluginDirectory();
    QDir().mkpath(directory);
    QDesktopServices::openUrl(QUrl::fromLocalFile(directory));
}

void PluginManagerWidget::openDocumentation()
{
    const QString path = documentationPath();
    if (path.isEmpty()) {
        QMessageBox::warning(
            this, tr("Documentation Not Found"),
            tr("plugin-system.md was not found in the installed documentation."));
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void PluginManagerWidget::configurePermissions()
{
    if (!m_manager)
        return;
    const int row = m_table->currentRow();
    if (row < 0 || !m_table->item(row, 0)) {
        QMessageBox::information(this, tr("Plugin Permissions"),
                                 tr("Select a plugin first."));
        return;
    }
    const QString pluginId =
        m_table->item(row, 0)->data(PluginIdRole).toString();
    PluginDescriptor descriptor;
    bool found = false;
    for (const PluginDescriptor& candidate : m_manager->descriptors()) {
        if (candidate.id == pluginId) {
            descriptor = candidate;
            found = true;
            break;
        }
    }
    if (!found || descriptor.apiVersion < 3) {
        QMessageBox::information(
            this, tr("Plugin Permissions"),
            tr("Only API v3 plugins use host permissions."));
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle(tr("Permissions - %1").arg(
        descriptor.displayName.isEmpty() ? descriptor.id
                                         : descriptor.displayName));
    dialog.resize(620, 420);
    auto* layout = new QVBoxLayout(&dialog);
    auto* warning = new QLabel(
        tr("Grant only permissions required for this plugin's documented "
           "purpose. Native plugins still execute in the application process. "
           "Permission changes apply after restart."),
        &dialog);
    warning->setWordWrap(true);
    layout->addWidget(warning);

    auto* list = new QListWidget(&dialog);
    for (const QString& permission : descriptor.requestedPermissions) {
        auto* item = new QListWidgetItem(permission, list);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(descriptor.grantedPermissions.contains(permission)
                                ? Qt::Checked
                                : Qt::Unchecked);
    }
    if (descriptor.requestedPermissions.isEmpty()) {
        auto* item = new QListWidgetItem(
            tr("This plugin requests no permissions."), list);
        item->setFlags(Qt::NoItemFlags);
    }
    layout->addWidget(list, 1);

    auto* buttons = new QDialogButtonBox(
        QDialogButtonBox::Save | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttons);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QStringList granted;
    for (int index = 0; index < list->count(); ++index) {
        QListWidgetItem* item = list->item(index);
        if (item->checkState() == Qt::Checked)
            granted.append(item->text());
    }
    granted.sort(Qt::CaseInsensitive);
    QSettings settings;
    settings.setValue(
        QStringLiteral("PluginSystem/GrantedPermissions/%1").arg(pluginId),
        granted);
    settings.sync();
    markRestartRequired();
}

QString PluginManagerWidget::userPluginDirectory() const
{
    return QDir(QStandardPaths::writableLocation(
                    QStandardPaths::AppLocalDataLocation))
        .filePath(QStringLiteral("plugins"));
}

QString PluginManagerWidget::documentationPath() const
{
    const QDir applicationDirectory(QApplication::applicationDirPath());
    const QStringList candidates = {
        applicationDirectory.filePath(QStringLiteral("docs/plugin-system.md")),
        applicationDirectory.filePath(QStringLiteral("../docs/plugin-system.md")),
        applicationDirectory.filePath(
            QStringLiteral("../share/DeltaXSoftware/docs/plugin-system.md")),
        applicationDirectory.filePath(QStringLiteral("../../docs/plugin-system.md"))};
    for (const QString& candidate : candidates) {
        const QFileInfo info(candidate);
        if (info.isFile())
            return info.canonicalFilePath();
    }
    return {};
}

void PluginManagerWidget::markRestartRequired()
{
    m_restartLabel->setText(
        tr("Plugin configuration changed. Restart Delta X Software to apply it."));
}
