#ifndef BLOCKCANVAS_H
#define BLOCKCANVAS_H

#include <QGraphicsView>
#include <QPointF>

#include <functional>

class QTreeWidget;
class QTreeWidgetItem;

class BlockCanvas final : public QGraphicsView
{
public:
    using SelectionHandler = std::function<void(QTreeWidgetItem*)>;
    using DropHandler = std::function<void(const QString&, const QPointF&)>;
    using MoveHandler = std::function<void(QTreeWidgetItem*, const QPointF&)>;
    using DeleteHandler = std::function<void(QTreeWidgetItem*)>;

    explicit BlockCanvas(QWidget* parent = nullptr);

    void setWorkspaceModel(QTreeWidget* workspace);
    void rebuild();
    void selectWorkspaceItem(QTreeWidgetItem* item);
    QTreeWidgetItem* workspaceItemAt(const QPointF& scenePosition,
                                     QTreeWidgetItem* excluded = nullptr) const;

    void setSelectionHandler(SelectionHandler handler);
    void setDropHandler(DropHandler handler);
    void setMoveHandler(MoveHandler handler);
    void setDeleteHandler(DeleteHandler handler);

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void fitWorkspace();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    class VisualItem;

    qreal subtreeHeight(QTreeWidgetItem* item) const;
    qreal layoutItem(QTreeWidgetItem* item, int depth, qreal y,
                     qreal availableWidth);
    void clearDropTarget();
    void updateDropTarget(const QPointF& scenePosition);
    VisualItem* visualFor(QTreeWidgetItem* item) const;
    VisualItem* visualAt(const QPointF& scenePosition,
                         QTreeWidgetItem* excluded = nullptr) const;
    void clampZoom(qreal requestedScale);

    QTreeWidget* m_workspace = nullptr;
    SelectionHandler m_selectionHandler;
    DropHandler m_dropHandler;
    MoveHandler m_moveHandler;
    DeleteHandler m_deleteHandler;
    QList<VisualItem*> m_visualItems;
    VisualItem* m_dropTarget = nullptr;
    qreal m_zoom = 1.0;
};

#endif // BLOCKCANVAS_H
