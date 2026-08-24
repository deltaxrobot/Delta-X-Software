#ifndef BLOCKPROGRAMMINGPANEL_H
#define BLOCKPROGRAMMINGPANEL_H

#include "BlockProgram.h"

#include <QJsonObject>
#include <QWidget>

class DeltaXHostContext;
class QComboBox;
class QFormLayout;
class QLabel;
class QPlainTextEdit;
class QPushButton;
class QTimer;
class QTreeWidget;
class QTreeWidgetItem;

class BlockProgrammingPanel final : public QWidget
{
    Q_OBJECT

public:
    explicit BlockProgrammingPanel(DeltaXHostContext* context,
                                   QWidget* parent = nullptr);

    QJsonObject workspaceDocument() const;
    bool loadWorkspaceDocument(const QJsonObject& document,
                               QString* error = nullptr);
    int selectedWorkerIndex() const;
    void setSelectedWorkerIndex(int index);

private:
    enum ItemRole {
        BlockTypeRole = Qt::UserRole + 1,
        BlockFieldsRole
    };

    void buildUi();
    void populatePalette();
    void refreshWorkers();
    void addBlock(const QString& type);
    void deleteSelectedBlock();
    void duplicateSelectedBlock();
    void moveSelectedBlock(int offset);
    void indentSelectedBlock();
    void outdentSelectedBlock();
    void showProperties(QTreeWidgetItem* item);
    void clearProperties();
    void updateItemAppearance(QTreeWidgetItem* item);
    void scheduleRefresh();
    void refreshPreview();
    void showDiagnostics(const QVariantList& diagnostics);
    void newProgram();
    void applyTemplate();
    void openProgram();
    void saveProgram();
    void exportGScript();
    void copyGScript();
    void loadIntoEditor();
    void runProgram();
    void stopProgram();
    void setStatus(const QString& text, bool error = false);

    static DeltaXBlockProgramming::BlockNode itemToNode(
        const QTreeWidgetItem* item);
    static QTreeWidgetItem* nodeToItem(
        const DeltaXBlockProgramming::BlockNode& node);

    DeltaXHostContext* m_context = nullptr;
    QTreeWidget* m_palette = nullptr;
    QTreeWidget* m_workspace = nullptr;
    QFormLayout* m_properties = nullptr;
    QPlainTextEdit* m_preview = nullptr;
    QTreeWidget* m_diagnostics = nullptr;
    QComboBox* m_template = nullptr;
    QComboBox* m_worker = nullptr;
    QLabel* m_status = nullptr;
    QPushButton* m_loadButton = nullptr;
    QPushButton* m_runButton = nullptr;
    QPushButton* m_stopButton = nullptr;
    QTimer* m_refreshTimer = nullptr;
    QString m_currentPath;
    bool m_hasErrors = true;
};

#endif // BLOCKPROGRAMMINGPANEL_H
