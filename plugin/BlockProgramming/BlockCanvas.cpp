#include "BlockCanvas.h"

#include "BlockProgram.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLineF>
#include <QMimeData>
#include <QPainter>
#include <QPainterPath>
#include <QScrollBar>
#include <QTreeWidget>
#include <QWheelEvent>

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>

using namespace DeltaXBlockProgramming;

namespace
{
constexpr int BlockTypeRole = Qt::UserRole + 1;
constexpr int BlockFieldsRole = Qt::UserRole + 2;
constexpr qreal HeaderHeight = 46.0;
constexpr qreal LeafHeight = 50.0;
constexpr qreal ChildIndent = 32.0;
constexpr qreal StackGap = 1.0;
const char* BlockMimeType = "application/x-deltax-block-type";

QColor readableText(const QColor& color)
{
    const int luminance = (299 * color.red() + 587 * color.green() +
                           114 * color.blue()) / 1000;
    return luminance >= 155 ? QColor(QStringLiteral("#111827"))
                            : QColor(QStringLiteral("#ffffff"));
}

QString fieldSummary(const BlockDefinition& definition,
                     const QVariantMap& fields)
{
    QStringList parts;
    for (const FieldDefinition& field : definition.fields) {
        QString value = fields.value(field.key, field.defaultValue)
                            .toString().simplified();
        if (value.isEmpty())
            continue;
        if (value.size() > 28)
            value = value.left(25) + QStringLiteral("...");
        parts.append(value);
        if (parts.size() == 2)
            break;
    }
    return parts.join(QStringLiteral("  •  "));
}

QPainterPath stackPath(const QRectF& rect)
{
    const qreal left = rect.left();
    const qreal right = rect.right();
    const qreal top = rect.top();
    const qreal bottom = rect.bottom();
    QPainterPath path;
    path.moveTo(left + 8.0, top);
    path.lineTo(left + 25.0, top);
    path.lineTo(left + 30.0, top + 5.0);
    path.lineTo(left + 44.0, top + 5.0);
    path.lineTo(left + 49.0, top);
    path.lineTo(right - 8.0, top);
    path.quadTo(right, top, right, top + 8.0);
    path.lineTo(right, bottom - 8.0);
    path.quadTo(right, bottom, right - 8.0, bottom);
    path.lineTo(left + 49.0, bottom);
    path.lineTo(left + 44.0, bottom + 5.0);
    path.lineTo(left + 30.0, bottom + 5.0);
    path.lineTo(left + 25.0, bottom);
    path.lineTo(left + 8.0, bottom);
    path.quadTo(left, bottom, left, bottom - 8.0);
    path.lineTo(left, top + 8.0);
    path.quadTo(left, top, left + 8.0, top);
    path.closeSubpath();
    return path;
}
}

class BlockCanvas::VisualItem final : public QGraphicsItem
{
public:
    VisualItem(BlockCanvas* canvas, QTreeWidgetItem* workspaceItem,
               const BlockDefinition* definition, const QRectF& geometry,
               int depth)
        : m_canvas(canvas)
        , m_workspaceItem(workspaceItem)
        , m_definition(definition)
        , m_geometry(QRectF(QPointF(0, 0), geometry.size()))
        , m_depth(depth)
        , m_originalPosition(geometry.topLeft())
    {
        setPos(m_originalPosition);
        setAcceptHoverEvents(true);
        setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsMovable |
                 QGraphicsItem::ItemSendsGeometryChanges);
        setCursor(Qt::OpenHandCursor);
        setZValue(depth * 10.0 + 1.0);
        const QVariantMap fields = workspaceItem
            ? workspaceItem->data(0, BlockFieldsRole).toMap() : QVariantMap{};
        if (definition)
            m_details = fieldSummary(*definition, fields);
    }

    QRectF boundingRect() const override
    {
        return m_geometry.adjusted(-3.0, -3.0, 6.0, 8.0);
    }

    QTreeWidgetItem* workspaceItem() const
    {
        return m_workspaceItem;
    }

    QPointF centerInScene() const
    {
        return mapToScene(m_geometry.center());
    }

    void setDropTarget(bool value)
    {
        if (m_dropTarget == value)
            return;
        m_dropTarget = value;
        update();
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*,
               QWidget*) override
    {
        if (!m_definition)
            return;

        painter->setRenderHint(QPainter::Antialiasing, true);
        QColor base(m_definition->color);
        if (m_hovered)
            base = base.lighter(112);
        const QColor textColor = readableText(base);
        QPen outline(isSelected() ? QColor(QStringLiteral("#f8fafc"))
                                  : base.darker(145));
        outline.setWidthF(isSelected() ? 2.4 : 1.0);
        if (m_dropTarget) {
            outline.setColor(QColor(QStringLiteral("#facc15")));
            outline.setWidthF(3.0);
        }
        painter->setPen(outline);
        painter->setBrush(base);

        if (m_definition->container) {
            const QRectF header(0, 0, m_geometry.width(), HeaderHeight);
            painter->drawRoundedRect(header, 8.0, 8.0);
            const QRectF spine(0, HeaderHeight - 3.0, 16.0,
                               qMax(18.0, m_geometry.height() - HeaderHeight));
            painter->drawRoundedRect(spine, 7.0, 7.0);
            const QRectF cap(0, m_geometry.height() - 17.0,
                             m_geometry.width(), 17.0);
            painter->drawRoundedRect(cap, 7.0, 7.0);
            painter->setPen(QPen(base.lighter(135), 1.0, Qt::DashLine));
            painter->setBrush(Qt::NoBrush);
            painter->drawRoundedRect(
                QRectF(22.0, HeaderHeight + 5.0,
                       m_geometry.width() - 30.0,
                       qMax(12.0, m_geometry.height() - HeaderHeight - 28.0)),
                7.0, 7.0);
        } else {
            painter->drawPath(stackPath(
                QRectF(0, 0, m_geometry.width(), LeafHeight - 5.0)));
        }

        painter->setPen(textColor);
        QFont titleFont = painter->font();
        titleFont.setBold(true);
        titleFont.setPointSizeF(qMax(9.0, titleFont.pointSizeF()));
        painter->setFont(titleFont);
        painter->drawText(QRectF(17.0, 8.0, m_geometry.width() - 34.0, 18.0),
                          Qt::AlignLeft | Qt::AlignVCenter,
                          m_definition->label);

        if (!m_details.isEmpty()) {
            QFont detailFont = titleFont;
            detailFont.setBold(false);
            detailFont.setPointSizeF(qMax(8.0, detailFont.pointSizeF() - 1.0));
            painter->setFont(detailFont);
            QColor detailColor = textColor;
            detailColor.setAlpha(210);
            painter->setPen(detailColor);
            painter->drawText(
                QRectF(17.0, 25.0, m_geometry.width() - 34.0, 16.0),
                Qt::AlignLeft | Qt::AlignVCenter,
                painter->fontMetrics().elidedText(
                    m_details, Qt::ElideRight,
                    static_cast<int>(m_geometry.width() - 34.0)));
        }

        if (m_definition->container) {
            painter->setPen(QColor(255, 255, 255, 190));
            QFont marker = painter->font();
            marker.setBold(true);
            painter->setFont(marker);
            painter->drawText(
                QRectF(m_geometry.width() - 82.0, 7.0, 66.0, 20.0),
                Qt::AlignRight | Qt::AlignVCenter,
                QStringLiteral("DO"));
        }
    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override
    {
        m_hovered = true;
        setCursor(Qt::OpenHandCursor);
        update();
        QGraphicsItem::hoverEnterEvent(event);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override
    {
        m_hovered = false;
        update();
        QGraphicsItem::hoverLeaveEvent(event);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        setCursor(Qt::ClosedHandCursor);
        m_dragStart = pos();
        setZValue(10000.0);
        if (m_canvas && m_canvas->m_selectionHandler)
            m_canvas->m_selectionHandler(m_workspaceItem);
        QGraphicsItem::mousePressEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override
    {
        setCursor(Qt::OpenHandCursor);
        const bool moved = QLineF(m_dragStart, pos()).length() > 3.0;
        QGraphicsItem::mouseReleaseEvent(event);
        if (moved && m_canvas && m_canvas->m_moveHandler)
            m_canvas->m_moveHandler(m_workspaceItem, centerInScene());
        else
            setZValue(m_depth * 10.0 + 1.0);
    }

private:
    BlockCanvas* m_canvas = nullptr;
    QTreeWidgetItem* m_workspaceItem = nullptr;
    const BlockDefinition* m_definition = nullptr;
    QRectF m_geometry;
    int m_depth = 0;
    QPointF m_originalPosition;
    QPointF m_dragStart;
    QString m_details;
    bool m_hovered = false;
    bool m_dropTarget = false;
};

BlockCanvas::BlockCanvas(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    setAcceptDrops(true);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setRenderHint(QPainter::Antialiasing, true);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setFrameShape(QFrame::NoFrame);
    setBackgroundBrush(QColor(QStringLiteral("#17171a")));
    setFocusPolicy(Qt::StrongFocus);
    setToolTip(tr("Drag blocks from the toolbox. Drag existing blocks to reorder or nest them."));
}

void BlockCanvas::setWorkspaceModel(QTreeWidget* workspace)
{
    m_workspace = workspace;
    rebuild();
}

qreal BlockCanvas::subtreeHeight(QTreeWidgetItem* item) const
{
    if (!item)
        return LeafHeight;
    const BlockDefinition* definition = BlockProgram::definition(
        item->data(0, BlockTypeRole).toString());
    if (!definition || !definition->container)
        return LeafHeight;

    qreal childrenHeight = 0.0;
    for (int index = 0; index < item->childCount(); ++index) {
        childrenHeight += subtreeHeight(item->child(index));
        if (index + 1 < item->childCount())
            childrenHeight += StackGap;
    }
    return HeaderHeight + qMax(28.0, childrenHeight) + 23.0;
}

qreal BlockCanvas::layoutItem(QTreeWidgetItem* item, int depth, qreal y,
                              qreal availableWidth)
{
    if (!item)
        return y;
    const BlockDefinition* definition = BlockProgram::definition(
        item->data(0, BlockTypeRole).toString());
    const qreal height = subtreeHeight(item);
    const qreal x = 32.0 + depth * ChildIndent;
    const qreal width = qMax(250.0, availableWidth - depth * ChildIndent);
    auto* visual = new VisualItem(this, item, definition,
                                  QRectF(x, y, width, height), depth);
    scene()->addItem(visual);
    m_visualItems.append(visual);
    if (item == (m_workspace ? m_workspace->currentItem() : nullptr))
        visual->setSelected(true);

    if (definition && definition->container) {
        qreal childY = y + HeaderHeight + 8.0;
        for (int index = 0; index < item->childCount(); ++index) {
            childY = layoutItem(item->child(index), depth + 1, childY,
                                availableWidth);
            childY += StackGap;
        }
    }
    return y + height;
}

void BlockCanvas::rebuild()
{
    QTreeWidgetItem* selected = m_workspace ? m_workspace->currentItem() : nullptr;
    clearDropTarget();
    m_visualItems.clear();
    scene()->clear();

    const qreal canvasWidth = qMax(
        560.0, viewport()->width() / qMax(0.1, m_zoom) - 46.0);
    qreal y = 35.0;
    if (m_workspace) {
        for (int index = 0; index < m_workspace->topLevelItemCount(); ++index) {
            y = layoutItem(m_workspace->topLevelItem(index), 0, y,
                           canvasWidth - 74.0);
            y += StackGap + 3.0;
        }
    }

    if (m_visualItems.isEmpty()) {
        auto* title = scene()->addText(tr("Drag a block here to start"));
        QFont titleFont = title->font();
        titleFont.setPointSizeF(14.0);
        titleFont.setBold(true);
        title->setFont(titleFont);
        title->setDefaultTextColor(QColor(QStringLiteral("#cbd5e1")));
        title->setPos(72.0, 105.0);
        auto* hint = scene()->addText(
            tr("Use the toolbox on the left, then connect blocks into a program stack."));
        hint->setDefaultTextColor(QColor(QStringLiteral("#7c8798")));
        hint->setPos(72.0, 142.0);
        y = 230.0;
    }

    scene()->setSceneRect(0, 0, canvasWidth, qMax(y + 55.0, 360.0));
    if (selected)
        selectWorkspaceItem(selected);
}

void BlockCanvas::selectWorkspaceItem(QTreeWidgetItem* item)
{
    for (VisualItem* visual : std::as_const(m_visualItems))
        visual->setSelected(visual->workspaceItem() == item);
    if (VisualItem* visual = visualFor(item))
        ensureVisible(visual, 40, 40);
}

BlockCanvas::VisualItem* BlockCanvas::visualFor(QTreeWidgetItem* item) const
{
    const auto found = std::find_if(
        m_visualItems.cbegin(), m_visualItems.cend(),
        [item](VisualItem* visual) {
            return visual && visual->workspaceItem() == item;
        });
    return found == m_visualItems.cend() ? nullptr : *found;
}

BlockCanvas::VisualItem* BlockCanvas::visualAt(
    const QPointF& scenePosition, QTreeWidgetItem* excluded) const
{
    VisualItem* contained = nullptr;
    VisualItem* nearest = nullptr;
    qreal nearestDistance = std::numeric_limits<qreal>::max();
    for (VisualItem* visual : m_visualItems) {
        if (!visual || visual->workspaceItem() == excluded)
            continue;
        if (visual->contains(visual->mapFromScene(scenePosition)) &&
            (!contained || visual->zValue() > contained->zValue())) {
            contained = visual;
        }
        const qreal distance = QLineF(scenePosition,
                                      visual->centerInScene()).length();
        if (distance < nearestDistance) {
            nearestDistance = distance;
            nearest = visual;
        }
    }
    if (contained)
        return contained;
    return nearestDistance <= 95.0 ? nearest : nullptr;
}

QTreeWidgetItem* BlockCanvas::workspaceItemAt(
    const QPointF& scenePosition, QTreeWidgetItem* excluded) const
{
    VisualItem* visual = visualAt(scenePosition, excluded);
    return visual ? visual->workspaceItem() : nullptr;
}

void BlockCanvas::setSelectionHandler(SelectionHandler handler)
{
    m_selectionHandler = std::move(handler);
}

void BlockCanvas::setDropHandler(DropHandler handler)
{
    m_dropHandler = std::move(handler);
}

void BlockCanvas::setMoveHandler(MoveHandler handler)
{
    m_moveHandler = std::move(handler);
}

void BlockCanvas::setDeleteHandler(DeleteHandler handler)
{
    m_deleteHandler = std::move(handler);
}

void BlockCanvas::clearDropTarget()
{
    if (m_dropTarget)
        m_dropTarget->setDropTarget(false);
    m_dropTarget = nullptr;
}

void BlockCanvas::updateDropTarget(const QPointF& scenePosition)
{
    VisualItem* target = visualAt(scenePosition);
    if (target == m_dropTarget)
        return;
    clearDropTarget();
    m_dropTarget = target;
    if (m_dropTarget)
        m_dropTarget->setDropTarget(true);
}

void BlockCanvas::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat(QLatin1String(BlockMimeType))) {
        event->acceptProposedAction();
        return;
    }
    QGraphicsView::dragEnterEvent(event);
}

void BlockCanvas::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->mimeData()->hasFormat(QLatin1String(BlockMimeType))) {
        updateDropTarget(mapToScene(event->position().toPoint()));
        event->acceptProposedAction();
        return;
    }
    QGraphicsView::dragMoveEvent(event);
}

void BlockCanvas::dragLeaveEvent(QDragLeaveEvent* event)
{
    clearDropTarget();
    QGraphicsView::dragLeaveEvent(event);
}

void BlockCanvas::dropEvent(QDropEvent* event)
{
    if (!event->mimeData()->hasFormat(QLatin1String(BlockMimeType))) {
        QGraphicsView::dropEvent(event);
        return;
    }
    const QString type = QString::fromUtf8(
        event->mimeData()->data(QLatin1String(BlockMimeType))).trimmed();
    const QPointF scenePosition = mapToScene(event->position().toPoint());
    clearDropTarget();
    if (!type.isEmpty() && m_dropHandler)
        m_dropHandler(type, scenePosition);
    event->acceptProposedAction();
}

void BlockCanvas::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        event->angleDelta().y() > 0 ? zoomIn() : zoomOut();
        event->accept();
        return;
    }
    QGraphicsView::wheelEvent(event);
}

void BlockCanvas::keyPressEvent(QKeyEvent* event)
{
    if ((event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) &&
        m_workspace && m_workspace->currentItem() && m_deleteHandler) {
        m_deleteHandler(m_workspace->currentItem());
        event->accept();
        return;
    }
    if (event->matches(QKeySequence::ZoomIn)) {
        zoomIn();
        event->accept();
        return;
    }
    if (event->matches(QKeySequence::ZoomOut)) {
        zoomOut();
        event->accept();
        return;
    }
    QGraphicsView::keyPressEvent(event);
}

void BlockCanvas::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->fillRect(rect, QColor(QStringLiteral("#17171a")));
    const qreal grid = 24.0;
    const qreal left = std::floor(rect.left() / grid) * grid;
    const qreal top = std::floor(rect.top() / grid) * grid;
    painter->setPen(QPen(QColor(255, 255, 255, 18), 1.0));
    for (qreal x = left; x < rect.right(); x += grid) {
        for (qreal y = top; y < rect.bottom(); y += grid)
            painter->drawPoint(QPointF(x, y));
    }
}

void BlockCanvas::clampZoom(qreal requestedScale)
{
    const qreal clamped = qBound(0.55, requestedScale, 1.85);
    const qreal factor = clamped / m_zoom;
    m_zoom = clamped;
    scale(factor, factor);
}

void BlockCanvas::zoomIn()
{
    clampZoom(m_zoom * 1.15);
}

void BlockCanvas::zoomOut()
{
    clampZoom(m_zoom / 1.15);
}

void BlockCanvas::resetZoom()
{
    resetTransform();
    m_zoom = 1.0;
}

void BlockCanvas::fitWorkspace()
{
    if (!scene() || scene()->items().isEmpty())
        return;
    fitInView(scene()->itemsBoundingRect().adjusted(-24, -24, 24, 24),
              Qt::KeepAspectRatio);
    m_zoom = transform().m11();
}
