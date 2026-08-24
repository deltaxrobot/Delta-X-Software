#include "BlockProgrammingPanel.h"

#include "DeltaXHostContext.h"
#include "DeltaXPermissions.h"

#include <QAbstractItemModel>
#include <QApplication>
#include <QClipboard>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QSplitter>
#include <QTimer>
#include <QTreeWidget>
#include <QVBoxLayout>

#include <algorithm>
#include <functional>

using namespace DeltaXBlockProgramming;

namespace
{
void styleBlockItem(QTreeWidgetItem* item)
{
    if (!item)
        return;
    const BlockNode node{item->data(0, Qt::UserRole + 1).toString(),
                         item->data(0, Qt::UserRole + 2).toMap(), {}};
    const BlockDefinition* definition = BlockProgram::definition(node.type);
    item->setText(0, BlockProgram::summary(node));
    if (!definition)
        return;
    const QColor color(definition->color);
    item->setBackground(0, color);
    item->setForeground(0, QColor(Qt::white));
    item->setToolTip(0, definition->description);
    QFont font = item->font(0);
    font.setBold(true);
    item->setFont(0, font);
}

void deleteLayoutContents(QLayout* layout)
{
    if (!layout)
        return;
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QLayout* childLayout = item->layout())
            deleteLayoutContents(childLayout);
        if (QWidget* widget = item->widget())
            delete widget;
        delete item;
    }
}

QVector<BlockNode> workspaceNodes(const QTreeWidget* tree)
{
    QVector<BlockNode> result;
    if (!tree)
        return result;
    for (int index = 0; index < tree->topLevelItemCount(); ++index) {
        const QTreeWidgetItem* item = tree->topLevelItem(index);
        BlockNode node{item->data(0, Qt::UserRole + 1).toString(),
                       item->data(0, Qt::UserRole + 2).toMap(), {}};
        std::function<void(const QTreeWidgetItem*, BlockNode&)> appendChildren;
        appendChildren = [&appendChildren](const QTreeWidgetItem* parent,
                                            BlockNode& parentNode) {
            for (int childIndex = 0; childIndex < parent->childCount(); ++childIndex) {
                const QTreeWidgetItem* child = parent->child(childIndex);
                BlockNode childNode{
                    child->data(0, Qt::UserRole + 1).toString(),
                    child->data(0, Qt::UserRole + 2).toMap(), {}};
                appendChildren(child, childNode);
                parentNode.children.append(childNode);
            }
        };
        appendChildren(item, node);
        result.append(node);
    }
    return result;
}
}

BlockProgrammingPanel::BlockProgrammingPanel(DeltaXHostContext* context,
                                             QWidget* parent)
    : QWidget(parent)
    , m_context(context)
{
    buildUi();
    populatePalette();
    refreshWorkers();
    newProgram();
}

void BlockProgrammingPanel::buildUi()
{
    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(8, 8, 8, 8);
    root->setSpacing(6);

    auto* fileBar = new QHBoxLayout;
    m_template = new QComboBox(this);
    m_template->addItems(BlockProgram::templateNames());
    auto* newButton = new QPushButton(tr("New"), this);
    auto* openButton = new QPushButton(tr("Open..."), this);
    auto* saveButton = new QPushButton(tr("Save..."), this);
    auto* exportButton = new QPushButton(tr("Export G-Script..."), this);
    auto* copyButton = new QPushButton(tr("Copy G-Script"), this);
    auto* helpButton = new QPushButton(tr("Help"), this);
    fileBar->addWidget(new QLabel(tr("Template"), this));
    fileBar->addWidget(m_template, 1);
    fileBar->addWidget(newButton);
    fileBar->addWidget(openButton);
    fileBar->addWidget(saveButton);
    fileBar->addWidget(exportButton);
    fileBar->addWidget(copyButton);
    fileBar->addWidget(helpButton);
    root->addLayout(fileBar);

    auto* executionBar = new QHBoxLayout;
    m_worker = new QComboBox(this);
    auto* refreshWorkersButton = new QPushButton(tr("Refresh workers"), this);
    m_loadButton = new QPushButton(tr("Load into editor"), this);
    m_runButton = new QPushButton(tr("Run"), this);
    m_stopButton = new QPushButton(tr("Stop"), this);
    m_status = new QLabel(tr("Initializing block workspace..."), this);
    m_status->setTextInteractionFlags(Qt::TextSelectableByMouse);
    executionBar->addWidget(new QLabel(tr("G-Script worker"), this));
    executionBar->addWidget(m_worker);
    executionBar->addWidget(refreshWorkersButton);
    executionBar->addSpacing(12);
    executionBar->addWidget(m_loadButton);
    executionBar->addWidget(m_runButton);
    executionBar->addWidget(m_stopButton);
    executionBar->addWidget(m_status, 1);
    root->addLayout(executionBar);

    auto* horizontal = new QSplitter(Qt::Horizontal, this);

    auto* paletteGroup = new QGroupBox(tr("Block palette"), horizontal);
    auto* paletteLayout = new QVBoxLayout(paletteGroup);
    m_palette = new QTreeWidget(paletteGroup);
    m_palette->setHeaderHidden(true);
    m_palette->setRootIsDecorated(true);
    paletteLayout->addWidget(m_palette);
    paletteGroup->setMinimumWidth(190);
    horizontal->addWidget(paletteGroup);

    auto* workspaceGroup = new QGroupBox(tr("Program workspace"), horizontal);
    auto* workspaceLayout = new QVBoxLayout(workspaceGroup);
    auto* editBar = new QHBoxLayout;
    auto* addButton = new QPushButton(tr("Add selected"), workspaceGroup);
    auto* duplicateButton = new QPushButton(tr("Duplicate"), workspaceGroup);
    auto* deleteButton = new QPushButton(tr("Delete"), workspaceGroup);
    auto* upButton = new QPushButton(tr("Up"), workspaceGroup);
    auto* downButton = new QPushButton(tr("Down"), workspaceGroup);
    auto* indentButton = new QPushButton(tr("Indent"), workspaceGroup);
    auto* outdentButton = new QPushButton(tr("Outdent"), workspaceGroup);
    editBar->addWidget(addButton);
    editBar->addWidget(duplicateButton);
    editBar->addWidget(deleteButton);
    editBar->addStretch();
    editBar->addWidget(upButton);
    editBar->addWidget(downButton);
    editBar->addWidget(indentButton);
    editBar->addWidget(outdentButton);
    workspaceLayout->addLayout(editBar);
    m_workspace = new QTreeWidget(workspaceGroup);
    m_workspace->setHeaderLabel(tr("Blocks (drag to reorder or nest)"));
    m_workspace->setSelectionMode(QAbstractItemView::SingleSelection);
    m_workspace->setDragEnabled(true);
    m_workspace->setAcceptDrops(true);
    m_workspace->setDropIndicatorShown(true);
    m_workspace->setDragDropMode(QAbstractItemView::InternalMove);
    m_workspace->setDefaultDropAction(Qt::MoveAction);
    workspaceLayout->addWidget(m_workspace);
    workspaceGroup->setMinimumWidth(330);
    horizontal->addWidget(workspaceGroup);

    auto* right = new QSplitter(Qt::Vertical, horizontal);
    auto* propertiesGroup = new QGroupBox(tr("Block properties"), right);
    auto* propertiesOuter = new QVBoxLayout(propertiesGroup);
    auto* propertiesWidget = new QWidget(propertiesGroup);
    m_properties = new QFormLayout(propertiesWidget);
    m_properties->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    auto* propertiesScroll = new QScrollArea(propertiesGroup);
    propertiesScroll->setWidgetResizable(true);
    propertiesScroll->setWidget(propertiesWidget);
    propertiesOuter->addWidget(propertiesScroll);
    right->addWidget(propertiesGroup);

    auto* previewGroup = new QGroupBox(tr("Generated G-Script"), right);
    auto* previewLayout = new QVBoxLayout(previewGroup);
    m_preview = new QPlainTextEdit(previewGroup);
    m_preview->setReadOnly(true);
    m_preview->setLineWrapMode(QPlainTextEdit::NoWrap);
    QFont fixed = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    m_preview->setFont(fixed);
    previewLayout->addWidget(m_preview);
    m_diagnostics = new QTreeWidget(previewGroup);
    m_diagnostics->setHeaderLabels(
        {tr("Severity"), tr("Code"), tr("Location"), tr("Message")});
    m_diagnostics->setRootIsDecorated(false);
    m_diagnostics->setMaximumHeight(150);
    m_diagnostics->header()->setSectionResizeMode(3, QHeaderView::Stretch);
    previewLayout->addWidget(m_diagnostics);
    right->addWidget(previewGroup);
    right->setSizes({260, 420});
    horizontal->addWidget(right);
    horizontal->setSizes({210, 390, 520});
    root->addWidget(horizontal, 1);

    m_refreshTimer = new QTimer(this);
    m_refreshTimer->setSingleShot(true);
    m_refreshTimer->setInterval(80);

    connect(newButton, &QPushButton::clicked, this, &BlockProgrammingPanel::newProgram);
    connect(openButton, &QPushButton::clicked, this, &BlockProgrammingPanel::openProgram);
    connect(saveButton, &QPushButton::clicked, this, &BlockProgrammingPanel::saveProgram);
    connect(exportButton, &QPushButton::clicked, this, &BlockProgrammingPanel::exportGScript);
    connect(copyButton, &QPushButton::clicked, this, &BlockProgrammingPanel::copyGScript);
    connect(helpButton, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(
            this, tr("Block Programming Help"),
            tr("1. Choose a template or double-click palette blocks.\n"
               "2. Select a block and edit its properties.\n"
               "3. Drag blocks or use Indent/Outdent to create nesting.\n"
               "4. Resolve diagnostics and review the generated G-Script.\n"
               "5. Load into the editor before running on hardware.\n\n"
               "The complete guide is docs/block-programming.md. Block Programming is not a safety function."));
    });
    connect(m_template, QOverload<int>::of(&QComboBox::activated),
            this, &BlockProgrammingPanel::applyTemplate);
    connect(refreshWorkersButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::refreshWorkers);
    connect(m_worker, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this]() { scheduleRefresh(); });
    connect(m_loadButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::loadIntoEditor);
    connect(m_runButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::runProgram);
    connect(m_stopButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::stopProgram);
    connect(addButton, &QPushButton::clicked, this, [this]() {
        if (QTreeWidgetItem* item = m_palette->currentItem())
            addBlock(item->data(0, BlockTypeRole).toString());
    });
    connect(duplicateButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::duplicateSelectedBlock);
    connect(deleteButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::deleteSelectedBlock);
    connect(upButton, &QPushButton::clicked, this, [this]() { moveSelectedBlock(-1); });
    connect(downButton, &QPushButton::clicked, this, [this]() { moveSelectedBlock(1); });
    connect(indentButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::indentSelectedBlock);
    connect(outdentButton, &QPushButton::clicked,
            this, &BlockProgrammingPanel::outdentSelectedBlock);
    connect(m_palette, &QTreeWidget::itemDoubleClicked, this,
            [this](QTreeWidgetItem* item) {
                addBlock(item->data(0, BlockTypeRole).toString());
            });
    connect(m_workspace, &QTreeWidget::currentItemChanged, this,
            [this](QTreeWidgetItem* current) { showProperties(current); });
    connect(m_workspace->model(), &QAbstractItemModel::rowsInserted,
            this, [this]() { scheduleRefresh(); });
    connect(m_workspace->model(), &QAbstractItemModel::rowsRemoved,
            this, [this]() { scheduleRefresh(); });
    connect(m_workspace->model(), &QAbstractItemModel::rowsMoved,
            this, [this]() { scheduleRefresh(); });
    connect(m_refreshTimer, &QTimer::timeout,
            this, &BlockProgrammingPanel::refreshPreview);
}

void BlockProgrammingPanel::populatePalette()
{
    m_palette->clear();
    QHash<QString, QTreeWidgetItem*> categories;
    for (const BlockDefinition& definition : BlockProgram::definitions()) {
        QTreeWidgetItem* category = categories.value(definition.category);
        if (!category) {
            category = new QTreeWidgetItem(m_palette, {definition.category});
            QFont font = category->font(0);
            font.setBold(true);
            category->setFont(0, font);
            category->setFlags(category->flags() & ~Qt::ItemIsSelectable);
            categories.insert(definition.category, category);
        }
        auto* item = new QTreeWidgetItem(category, {definition.label});
        item->setData(0, BlockTypeRole, definition.id);
        item->setToolTip(0, definition.description);
        item->setForeground(0, QColor(definition.color));
    }
    m_palette->expandAll();
}

void BlockProgrammingPanel::refreshWorkers()
{
    const int previous = selectedWorkerIndex();
    m_worker->clear();
    QString error;
    if (!m_context || !m_context->hasPermission(DeltaXPermissions::GScriptRead)) {
        m_worker->addItem(tr("Permission gscript.read is required"), -1);
        m_worker->setEnabled(false);
        setStatus(tr("Grant G-Script permissions under Modules > Plugins."), true);
    } else {
        const QVariantList workers = m_context->gscriptWorkers(&error);
        for (const QVariant& value : workers) {
            const QVariantMap worker = value.toMap();
            const int comboIndex = m_worker->count();
            m_worker->addItem(
                QStringLiteral("%1 — %2")
                    .arg(worker.value("id").toString(),
                         worker.value("state").toString()),
                worker.value("index"));
            m_worker->setItemData(comboIndex, worker.value("running"),
                                  Qt::UserRole + 1);
        }
        m_worker->setEnabled(m_worker->count() > 0);
        if (!error.isEmpty())
            setStatus(error, true);
    }
    setSelectedWorkerIndex(previous);
    scheduleRefresh();
}

void BlockProgrammingPanel::addBlock(const QString& type)
{
    if (type.isEmpty() || !BlockProgram::definition(type))
        return;
    BlockNode node{type, BlockProgram::defaultFields(type), {}};
    QTreeWidgetItem* item = nodeToItem(node);
    QTreeWidgetItem* selected = m_workspace->currentItem();
    if (!selected) {
        m_workspace->addTopLevelItem(item);
    } else {
        const BlockDefinition* selectedDefinition = BlockProgram::definition(
            selected->data(0, BlockTypeRole).toString());
        if (selectedDefinition && selectedDefinition->container) {
            selected->addChild(item);
            selected->setExpanded(true);
        } else if (QTreeWidgetItem* parent = selected->parent()) {
            parent->insertChild(parent->indexOfChild(selected) + 1, item);
        } else {
            m_workspace->insertTopLevelItem(
                m_workspace->indexOfTopLevelItem(selected) + 1, item);
        }
    }
    m_workspace->setCurrentItem(item);
    scheduleRefresh();
}

void BlockProgrammingPanel::deleteSelectedBlock()
{
    QTreeWidgetItem* item = m_workspace->currentItem();
    if (!item)
        return;
    if (item->childCount() > 0 &&
        QMessageBox::question(this, tr("Delete nested block"),
                              tr("Delete this block and all nested blocks?")) !=
            QMessageBox::Yes) {
        return;
    }
    delete item;
    clearProperties();
    scheduleRefresh();
}

void BlockProgrammingPanel::duplicateSelectedBlock()
{
    QTreeWidgetItem* item = m_workspace->currentItem();
    if (!item)
        return;
    QTreeWidgetItem* copy = item->clone();
    if (QTreeWidgetItem* parent = item->parent())
        parent->insertChild(parent->indexOfChild(item) + 1, copy);
    else
        m_workspace->insertTopLevelItem(
            m_workspace->indexOfTopLevelItem(item) + 1, copy);
    m_workspace->setCurrentItem(copy);
    scheduleRefresh();
}

void BlockProgrammingPanel::moveSelectedBlock(int offset)
{
    QTreeWidgetItem* item = m_workspace->currentItem();
    if (!item || offset == 0)
        return;
    QTreeWidgetItem* parent = item->parent();
    const int index = parent ? parent->indexOfChild(item)
                             : m_workspace->indexOfTopLevelItem(item);
    const int count = parent ? parent->childCount()
                             : m_workspace->topLevelItemCount();
    const int destination = index + offset;
    if (destination < 0 || destination >= count)
        return;
    QTreeWidgetItem* moved = parent ? parent->takeChild(index)
                                    : m_workspace->takeTopLevelItem(index);
    if (parent)
        parent->insertChild(destination, moved);
    else
        m_workspace->insertTopLevelItem(destination, moved);
    m_workspace->setCurrentItem(moved);
    scheduleRefresh();
}

void BlockProgrammingPanel::indentSelectedBlock()
{
    QTreeWidgetItem* item = m_workspace->currentItem();
    if (!item)
        return;
    QTreeWidgetItem* parent = item->parent();
    const int index = parent ? parent->indexOfChild(item)
                             : m_workspace->indexOfTopLevelItem(item);
    if (index <= 0)
        return;
    QTreeWidgetItem* previous = parent ? parent->child(index - 1)
                                       : m_workspace->topLevelItem(index - 1);
    const BlockDefinition* definition = BlockProgram::definition(
        previous->data(0, BlockTypeRole).toString());
    if (!definition || !definition->container) {
        setStatus(tr("Indent requires a container block immediately above."), true);
        return;
    }
    QTreeWidgetItem* moved = parent ? parent->takeChild(index)
                                    : m_workspace->takeTopLevelItem(index);
    previous->addChild(moved);
    previous->setExpanded(true);
    m_workspace->setCurrentItem(moved);
    scheduleRefresh();
}

void BlockProgrammingPanel::outdentSelectedBlock()
{
    QTreeWidgetItem* item = m_workspace->currentItem();
    QTreeWidgetItem* parent = item ? item->parent() : nullptr;
    if (!item || !parent)
        return;
    QTreeWidgetItem* grandParent = parent->parent();
    QTreeWidgetItem* moved = parent->takeChild(parent->indexOfChild(item));
    if (grandParent)
        grandParent->insertChild(grandParent->indexOfChild(parent) + 1, moved);
    else
        m_workspace->insertTopLevelItem(
            m_workspace->indexOfTopLevelItem(parent) + 1, moved);
    m_workspace->setCurrentItem(moved);
    scheduleRefresh();
}

void BlockProgrammingPanel::showProperties(QTreeWidgetItem* item)
{
    clearProperties();
    if (!item)
        return;
    const BlockDefinition* definition = BlockProgram::definition(
        item->data(0, BlockTypeRole).toString());
    if (!definition)
        return;
    auto* description = new QLabel(definition->description, this);
    description->setWordWrap(true);
    m_properties->addRow(description);

    for (const FieldDefinition& field : definition->fields) {
        const QVariantMap currentFields = item->data(0, BlockFieldsRole).toMap();
        const QVariant current = currentFields.value(field.key, field.defaultValue);
        auto commit = [this, item, key = field.key](const QVariant& value) {
            QVariantMap fields = item->data(0, BlockFieldsRole).toMap();
            fields.insert(key, value);
            item->setData(0, BlockFieldsRole, fields);
            updateItemAppearance(item);
            scheduleRefresh();
        };

        QWidget* editor = nullptr;
        if (field.kind == FieldDefinition::Kind::Choice) {
            auto* choice = new QComboBox(this);
            choice->setEditable(true);
            choice->addItems(field.options);
            choice->setCurrentText(current.toString());
            connect(choice, &QComboBox::currentTextChanged, this,
                    [commit](const QString& value) { commit(value); });
            editor = choice;
        } else if (field.kind == FieldDefinition::Kind::Integer) {
            auto* number = new QSpinBox(this);
            number->setRange(-1000000000, 1000000000);
            number->setValue(current.toInt());
            connect(number, QOverload<int>::of(&QSpinBox::valueChanged), this,
                    [commit](int value) { commit(value); });
            editor = number;
        } else if (field.kind == FieldDefinition::Kind::Number) {
            auto* number = new QDoubleSpinBox(this);
            number->setRange(-1.0e9, 1.0e9);
            number->setDecimals(4);
            number->setValue(current.toDouble());
            connect(number, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                    this, [commit](double value) { commit(value); });
            editor = number;
        } else if (field.kind == FieldDefinition::Kind::Multiline) {
            auto* text = new QPlainTextEdit(this);
            text->setPlainText(current.toString());
            text->setMaximumHeight(100);
            connect(text, &QPlainTextEdit::textChanged, this,
                    [text, commit]() { commit(text->toPlainText()); });
            editor = text;
        } else {
            auto* text = new QLineEdit(current.toString(), this);
            connect(text, &QLineEdit::textChanged, this,
                    [commit](const QString& value) { commit(value); });
            editor = text;
        }
        editor->setToolTip(field.help);
        m_properties->addRow(field.label, editor);
    }
}

void BlockProgrammingPanel::clearProperties()
{
    deleteLayoutContents(m_properties);
}

void BlockProgrammingPanel::updateItemAppearance(QTreeWidgetItem* item)
{
    styleBlockItem(item);
}

void BlockProgrammingPanel::scheduleRefresh()
{
    if (m_refreshTimer)
        m_refreshTimer->start();
}

void BlockProgrammingPanel::refreshPreview()
{
    const CompileResult compiled = BlockProgram::compile(workspaceNodes(m_workspace));
    m_preview->setPlainText(compiled.script);
    QVariantList diagnostics = compiled.diagnosticMaps();
    if (!compiled.hasErrors() && m_context &&
        m_context->hasPermission(DeltaXPermissions::GScriptRead)) {
        QString error;
        diagnostics.append(m_context->validateGScript(compiled.script, &error));
        if (!error.isEmpty()) {
            diagnostics.append(QVariantMap{
                {QStringLiteral("severity"), QStringLiteral("Error")},
                {QStringLiteral("code"), QStringLiteral("BPHOST")},
                {QStringLiteral("message"), error},
            });
        }
    }
    showDiagnostics(diagnostics);
    m_hasErrors = std::any_of(
        diagnostics.cbegin(), diagnostics.cend(), [](const QVariant& value) {
            return value.toMap().value(QStringLiteral("severity")).toString()
                       .compare(QStringLiteral("Error"), Qt::CaseInsensitive) == 0;
        });
    const bool canRead = m_context &&
        m_context->hasPermission(DeltaXPermissions::GScriptRead);
    const bool canEdit = m_context &&
        m_context->hasPermission(DeltaXPermissions::GScriptEdit);
    const bool canRun = m_context &&
        m_context->hasPermission(DeltaXPermissions::GScriptRun);
    const bool hasWorker = selectedWorkerIndex() >= 0;
    const bool workerRunning = hasWorker &&
        m_worker->currentData(Qt::UserRole + 1).toBool();
    m_loadButton->setEnabled(!m_hasErrors && canEdit && hasWorker &&
                             !workerRunning);
    m_runButton->setEnabled(!m_hasErrors && canRun && hasWorker &&
                            !workerRunning);
    m_stopButton->setEnabled(canRun && hasWorker && workerRunning);
    if (m_hasErrors)
        setStatus(tr("Fix diagnostics before loading or running."), true);
    else if (!canRead)
        setStatus(tr("Grant G-Script permissions under Modules > Plugins."), true);
    else if (!hasWorker)
        setStatus(tr("Program is valid, but no G-Script worker is available."), true);
    else
        setStatus(tr("Program is valid. Review the generated G-Script before running."));
}

void BlockProgrammingPanel::showDiagnostics(const QVariantList& diagnostics)
{
    m_diagnostics->clear();
    for (const QVariant& value : diagnostics) {
        const QVariantMap diagnostic = value.toMap();
        QString location = diagnostic.value(QStringLiteral("path")).toString();
        if (location.isEmpty() && diagnostic.contains(QStringLiteral("line"))) {
            location = QStringLiteral("L%1:C%2")
                           .arg(diagnostic.value(QStringLiteral("line")).toInt())
                           .arg(diagnostic.value(QStringLiteral("column")).toInt());
        }
        auto* item = new QTreeWidgetItem(m_diagnostics, {
            diagnostic.value(QStringLiteral("severity")).toString(),
            diagnostic.value(QStringLiteral("code")).toString(), location,
            diagnostic.value(QStringLiteral("message")).toString(),
        });
        const QString severity = item->text(0).toLower();
        if (severity == QStringLiteral("error"))
            item->setForeground(0, QColor(QStringLiteral("#ef4444")));
        else if (severity == QStringLiteral("warning"))
            item->setForeground(0, QColor(QStringLiteral("#f59e0b")));
    }
    m_diagnostics->resizeColumnToContents(0);
    m_diagnostics->resizeColumnToContents(1);
    m_diagnostics->resizeColumnToContents(2);
}

void BlockProgrammingPanel::newProgram()
{
    if (m_workspace->topLevelItemCount() > 0 &&
        QMessageBox::question(this, tr("New block program"),
                              tr("Discard the current in-memory workspace?")) !=
            QMessageBox::Yes) {
        return;
    }
    m_workspace->clear();
    m_currentPath.clear();
    m_template->setCurrentText(QStringLiteral("Empty"));
    scheduleRefresh();
}

void BlockProgrammingPanel::applyTemplate()
{
    const QString name = m_template->currentText();
    if (name == QStringLiteral("Empty")) {
        newProgram();
        return;
    }
    if (m_workspace->topLevelItemCount() > 0 &&
        QMessageBox::question(this, tr("Load template"),
                              tr("Replace the current workspace with '%1'?").arg(name)) !=
            QMessageBox::Yes) {
        return;
    }
    m_workspace->clear();
    for (const BlockNode& node : BlockProgram::createTemplate(name))
        m_workspace->addTopLevelItem(nodeToItem(node));
    m_workspace->expandAll();
    m_currentPath.clear();
    scheduleRefresh();
}

void BlockProgrammingPanel::openProgram()
{
    const QString path = QFileDialog::getOpenFileName(
        this, tr("Open block program"), m_currentPath,
        tr("Delta X block programs (*.dxblocks);;JSON files (*.json);;All files (*)"));
    if (path.isEmpty())
        return;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        setStatus(tr("Could not open %1").arg(QFileInfo(path).fileName()), true);
        return;
    }
    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parseError);
    QString error;
    QVector<BlockNode> parsedBlocks;
    if (parseError.error != QJsonParseError::NoError || !document.isObject() ||
        !BlockProgram::fromJson(document.object(), &parsedBlocks, &error)) {
        setStatus(error.isEmpty() ? parseError.errorString() : error, true);
        return;
    }
    if (m_workspace->topLevelItemCount() > 0 &&
        QMessageBox::question(
            this, tr("Open block program"),
            tr("Replace the current in-memory workspace with '%1'?")
                .arg(QFileInfo(path).fileName())) != QMessageBox::Yes) {
        return;
    }
    if (!loadWorkspaceDocument(document.object(), &error)) {
        setStatus(error, true);
        return;
    }
    m_currentPath = path;
    setStatus(tr("Opened %1").arg(QFileInfo(path).fileName()));
}

void BlockProgrammingPanel::saveProgram()
{
    QString path = QFileDialog::getSaveFileName(
        this, tr("Save block program"), m_currentPath,
        tr("Delta X block programs (*.dxblocks)"));
    if (path.isEmpty())
        return;
    if (!path.endsWith(QStringLiteral(".dxblocks"), Qt::CaseInsensitive))
        path += QStringLiteral(".dxblocks");
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        setStatus(tr("Could not write %1").arg(QFileInfo(path).fileName()), true);
        return;
    }
    file.write(QJsonDocument(workspaceDocument()).toJson(QJsonDocument::Indented));
    m_currentPath = path;
    setStatus(tr("Saved %1").arg(QFileInfo(path).fileName()));
}

void BlockProgrammingPanel::exportGScript()
{
    refreshPreview();
    if (m_hasErrors)
        return;
    QString path = QFileDialog::getSaveFileName(
        this, tr("Export generated G-Script"), {},
        tr("G-Script files (*.gcode *.dtgc);;Text files (*.txt)"));
    if (path.isEmpty())
        return;
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        setStatus(tr("Could not export G-Script."), true);
        return;
    }
    file.write(m_preview->toPlainText().toUtf8());
    setStatus(tr("Exported %1").arg(QFileInfo(path).fileName()));
}

void BlockProgrammingPanel::copyGScript()
{
    QApplication::clipboard()->setText(m_preview->toPlainText());
    setStatus(tr("Generated G-Script copied to the clipboard."));
}

void BlockProgrammingPanel::loadIntoEditor()
{
    refreshPreview();
    if (m_hasErrors || !m_context)
        return;
    QString error;
    if (!m_context->loadGScript(selectedWorkerIndex(), m_preview->toPlainText(),
                                &error)) {
        setStatus(error, true);
        return;
    }
    setStatus(tr("Generated G-Script loaded into the selected worker editor."));
    refreshWorkers();
}

void BlockProgrammingPanel::runProgram()
{
    refreshPreview();
    if (m_hasErrors || !m_context)
        return;
    if (QMessageBox::warning(
            this, tr("Run generated block program"),
            tr("This will start real cell automation. Block Programming is not a safety function. "
               "Verify E-stop, guards, limits, calibration, tool state and the generated G-Script before continuing."),
            QMessageBox::Cancel | QMessageBox::Yes, QMessageBox::Cancel) !=
        QMessageBox::Yes) {
        return;
    }
    QString error;
    if (!m_context->runGScript(selectedWorkerIndex(), m_preview->toPlainText(),
                               &error)) {
        setStatus(error, true);
        return;
    }
    m_runButton->setEnabled(false);
    setStatus(tr("Block program was queued on the selected G-Script worker."));
    QTimer::singleShot(100, this, &BlockProgrammingPanel::refreshWorkers);
}

void BlockProgrammingPanel::stopProgram()
{
    if (!m_context)
        return;
    QString error;
    if (!m_context->stopGScript(selectedWorkerIndex(), &error)) {
        setStatus(error, true);
        return;
    }
    setStatus(tr("Stop requested for the selected G-Script worker."));
    QTimer::singleShot(100, this, &BlockProgrammingPanel::refreshWorkers);
}

void BlockProgrammingPanel::setStatus(const QString& text, bool error)
{
    m_status->setText(text);
    m_status->setStyleSheet(error ? QStringLiteral("color: #ef4444;")
                                  : QStringLiteral("color: #22c55e;"));
}

BlockNode BlockProgrammingPanel::itemToNode(const QTreeWidgetItem* item)
{
    if (!item)
        return {};
    BlockNode node{item->data(0, BlockTypeRole).toString(),
                   item->data(0, BlockFieldsRole).toMap(), {}};
    for (int index = 0; index < item->childCount(); ++index)
        node.children.append(itemToNode(item->child(index)));
    return node;
}

QTreeWidgetItem* BlockProgrammingPanel::nodeToItem(const BlockNode& node)
{
    auto* item = new QTreeWidgetItem;
    item->setData(0, BlockTypeRole, node.type);
    item->setData(0, BlockFieldsRole, node.fields);
    item->setFlags(item->flags() | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
    styleBlockItem(item);
    for (const BlockNode& child : node.children)
        item->addChild(nodeToItem(child));
    return item;
}

QJsonObject BlockProgrammingPanel::workspaceDocument() const
{
    return BlockProgram::toJson(workspaceNodes(m_workspace));
}

bool BlockProgrammingPanel::loadWorkspaceDocument(const QJsonObject& document,
                                                  QString* error)
{
    QVector<BlockNode> blocks;
    if (!BlockProgram::fromJson(document, &blocks, error))
        return false;
    m_workspace->clear();
    for (const BlockNode& node : blocks)
        m_workspace->addTopLevelItem(nodeToItem(node));
    m_workspace->expandAll();
    scheduleRefresh();
    return true;
}

int BlockProgrammingPanel::selectedWorkerIndex() const
{
    return m_worker && m_worker->currentIndex() >= 0
        ? m_worker->currentData().toInt() : -1;
}

void BlockProgrammingPanel::setSelectedWorkerIndex(int index)
{
    if (!m_worker)
        return;
    const int found = m_worker->findData(index);
    if (found >= 0)
        m_worker->setCurrentIndex(found);
    else if (m_worker->count() > 0)
        m_worker->setCurrentIndex(0);
}
