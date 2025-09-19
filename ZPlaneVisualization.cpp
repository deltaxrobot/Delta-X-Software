#include "ZPlaneVisualization.h"
#include "RobotWindow.h" // For ZPlane struct
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QtMath>
#include <cmath>        // For std::sqrt, std::isnan, std::isinf

ZPlaneVisualization::ZPlaneVisualization(QWidget *parent)
    : QWidget(parent)
    , m_zPlane(nullptr)
    , m_viewMode(XY_PLANE)
    , m_showSafetyZone(true)
    , m_showGrid(true)
    , m_currentPosition(0, 0, 0)
    , m_worldBounds(-200, -200, 400, 400)
    , m_scaleFactor(1.0)
    , m_panOffset(0, 0)
    , m_dragging(false)
    , m_backgroundColor(QColor(40, 40, 40))
    , m_gridColor(QColor(80, 80, 80))
    , m_axesColor(QColor(120, 120, 120))
    , m_planeColor(QColor(100, 150, 255, 120))
    , m_safeZoneColor(QColor(100, 255, 100, 80))
    , m_unsafeZoneColor(QColor(255, 100, 100, 80))
    , m_currentPosColor(QColor(255, 255, 100))
{
    setMinimumSize(400, 150);
    setMouseTracking(true);
    
    // Setup update timer
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, QOverload<>::of(&ZPlaneVisualization::update));
    m_updateTimer->start(100); // 10 FPS
    
    updateTransform();
}

ZPlaneVisualization::~ZPlaneVisualization()
{
}

void ZPlaneVisualization::setZPlane(const ZPlane* zPlane)
{
    m_zPlane = zPlane;
    update();
}

void ZPlaneVisualization::setViewMode(ViewMode mode)
{
    m_viewMode = mode;
    updateTransform();
    update();
}

void ZPlaneVisualization::setShowSafetyZone(bool show)
{
    m_showSafetyZone = show;
    update();
}

void ZPlaneVisualization::setShowGrid(bool show)
{
    m_showGrid = show;
    update();
}

void ZPlaneVisualization::setCurrentPosition(const QVector3D& position)
{
    // Safety check: Ensure position is valid
    if (std::isnan(position.x()) || std::isnan(position.y()) || std::isnan(position.z()) ||
        std::isinf(position.x()) || std::isinf(position.y()) || std::isinf(position.z())) {
        return; // Skip invalid positions
    }
    
    m_currentPosition = position;
    update();
}

void ZPlaneVisualization::updateVisualization()
{
    update();
}

void ZPlaneVisualization::onViewModeChanged(int mode)
{
    setViewMode(static_cast<ViewMode>(mode));
}

void ZPlaneVisualization::onShowSafetyZoneToggled(bool show)
{
    setShowSafetyZone(show);
}

void ZPlaneVisualization::onShowGridToggled(bool show)
{
    setShowGrid(show);
}

void ZPlaneVisualization::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    
    // Clear background
    painter.fillRect(rect(), m_backgroundColor);
    
    // Apply world-to-screen transformation
    painter.setTransform(m_worldToScreenTransform);
    
    // Draw components in order
    if (m_showGrid) {
        drawGrid(painter);
    }
    
    drawAxes(painter);
    
    if (m_zPlane && m_zPlane->isValid) {
        if (m_showSafetyZone) {
            drawSafetyZone(painter);
        }
        drawZPlane(painter);
        drawCalibrationPoints(painter);
    }
    
    drawCurrentPosition(painter);
    
    // Reset transform for screen-space drawing
    painter.resetTransform();
    
    // Draw screen-space elements
    drawLegend(painter);
    drawStatusInfo(painter);
}

void ZPlaneVisualization::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    updateTransform();
}

void ZPlaneVisualization::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_lastMousePos = event->pos();
    }
}

void ZPlaneVisualization::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_panOffset += QPointF(delta.x() / m_scaleFactor, delta.y() / m_scaleFactor);
        m_lastMousePos = event->pos();
        updateTransform();
        update();
    }
}

void ZPlaneVisualization::drawGrid(QPainter &painter)
{
    painter.setPen(QPen(m_gridColor, 0)); // 0 = cosmetic pen (always 1 pixel)
    
    double gridSpacing = 50.0; // 50mm grid
    
    // Adjust grid spacing based on scale
    while (gridSpacing * m_scaleFactor < 20) gridSpacing *= 2;
    while (gridSpacing * m_scaleFactor > 100) gridSpacing /= 2;
    
    // Draw vertical lines
    double startX = qFloor(m_worldBounds.left() / gridSpacing) * gridSpacing;
    for (double x = startX; x <= m_worldBounds.right(); x += gridSpacing) {
        painter.drawLine(QPointF(x, m_worldBounds.top()), 
                        QPointF(x, m_worldBounds.bottom()));
    }
    
    // Draw horizontal lines
    double startY = qFloor(m_worldBounds.top() / gridSpacing) * gridSpacing;
    for (double y = startY; y <= m_worldBounds.bottom(); y += gridSpacing) {
        painter.drawLine(QPointF(m_worldBounds.left(), y), 
                        QPointF(m_worldBounds.right(), y));
    }
}

void ZPlaneVisualization::drawAxes(QPainter &painter)
{
    painter.setPen(QPen(m_axesColor, 0, Qt::SolidLine));
    
    // Draw X axis
    painter.drawLine(QPointF(m_worldBounds.left(), 0), 
                    QPointF(m_worldBounds.right(), 0));
    
    // Draw Y axis
    painter.drawLine(QPointF(0, m_worldBounds.top()), 
                    QPointF(0, m_worldBounds.bottom()));
    
    // Draw axis labels (in screen space)
    painter.save();
    painter.resetTransform();
    
    QPointF origin = worldToScreen(QVector3D(0, 0, 0));
    painter.setPen(QPen(m_axesColor, 1));
    painter.setFont(QFont("Arial", 8));
    
    QString xLabel, yLabel;
    switch (m_viewMode) {
        case XY_PLANE:
            xLabel = "X+"; yLabel = "Y+";
            break;
        case XZ_PLANE:
            xLabel = "X+"; yLabel = "Z+";
            break;
        case YZ_PLANE:
            xLabel = "Y+"; yLabel = "Z+";
            break;
    }
    
    painter.drawText(origin + QPointF(20, 5), xLabel);
    painter.drawText(origin + QPointF(5, -20), yLabel);
    
    painter.restore();
}

void ZPlaneVisualization::drawZPlane(QPainter &painter)
{
    if (!m_zPlane || !m_zPlane->isValid) return;
    
    painter.setPen(QPen(m_planeColor, 0));
    painter.setBrush(QBrush(m_planeColor));
    
    // Draw triangle formed by 3 calibration points
    QVector<QPointF> points;
    
    switch (m_viewMode) {
        case XY_PLANE:
            points << QPointF(m_zPlane->p1.x, m_zPlane->p1.y)
                   << QPointF(m_zPlane->p2.x, m_zPlane->p2.y)
                   << QPointF(m_zPlane->p3.x, m_zPlane->p3.y);
            break;
        case XZ_PLANE:
            points << QPointF(m_zPlane->p1.x, m_zPlane->p1.z)
                   << QPointF(m_zPlane->p2.x, m_zPlane->p2.z)
                   << QPointF(m_zPlane->p3.x, m_zPlane->p3.z);
            break;
        case YZ_PLANE:
            points << QPointF(m_zPlane->p1.y, m_zPlane->p1.z)
                   << QPointF(m_zPlane->p2.y, m_zPlane->p2.z)
                   << QPointF(m_zPlane->p3.y, m_zPlane->p3.z);
            break;
    }
    
    if (points.size() == 3) {
        painter.drawPolygon(points.data(), 3);
    }
}

void ZPlaneVisualization::drawSafetyZone(QPainter &painter)
{
    if (!m_zPlane || !m_zPlane->isValid) return;
    
    // For XY view, show safety zone as area above/below the Z-plane
    if (m_viewMode == XY_PLANE) {
        painter.setPen(QPen(m_safeZoneColor, 0, Qt::DashLine));
        painter.setBrush(QBrush(m_safeZoneColor));
        
        // Draw expanded triangle to represent safety margin
        QVector<QPointF> safetyPoints;
        
        // Calculate center of triangle
        QPointF center((m_zPlane->p1.x + m_zPlane->p2.x + m_zPlane->p3.x) / 3.0,
                      (m_zPlane->p1.y + m_zPlane->p2.y + m_zPlane->p3.y) / 3.0);
        
        // Expand each point away from center by safety margin
        double expansion = m_zPlane->safetyMargin * 0.1; // Visual scaling
        
        // Helper lambda for QPointF normalization
        auto normalizePoint = [](const QPointF& p) -> QPointF {
            double length = std::sqrt(p.x() * p.x() + p.y() * p.y());
            if (length < 1e-10) return QPointF(0, 0);
            return QPointF(p.x() / length, p.y() / length);
        };
        
        QPointF dir1 = normalizePoint(QPointF(m_zPlane->p1.x, m_zPlane->p1.y) - center);
        QPointF dir2 = normalizePoint(QPointF(m_zPlane->p2.x, m_zPlane->p2.y) - center);
        QPointF dir3 = normalizePoint(QPointF(m_zPlane->p3.x, m_zPlane->p3.y) - center);
        
        safetyPoints << QPointF(m_zPlane->p1.x, m_zPlane->p1.y) + dir1 * expansion;
        safetyPoints << QPointF(m_zPlane->p2.x, m_zPlane->p2.y) + dir2 * expansion;
        safetyPoints << QPointF(m_zPlane->p3.x, m_zPlane->p3.y) + dir3 * expansion;
        
        painter.drawPolygon(safetyPoints.data(), 3);
    }
}

void ZPlaneVisualization::drawCalibrationPoints(QPainter &painter)
{
    if (!m_zPlane || !m_zPlane->isValid) return;
    
    painter.setPen(QPen(Qt::white, 0));
    painter.setBrush(QBrush(Qt::red));
    
    double pointSize = 6.0 / m_scaleFactor; // Keep constant screen size
    
    QVector<QPointF> points;
    switch (m_viewMode) {
        case XY_PLANE:
            points << QPointF(m_zPlane->p1.x, m_zPlane->p1.y)
                   << QPointF(m_zPlane->p2.x, m_zPlane->p2.y)
                   << QPointF(m_zPlane->p3.x, m_zPlane->p3.y);
            break;
        case XZ_PLANE:
            points << QPointF(m_zPlane->p1.x, m_zPlane->p1.z)
                   << QPointF(m_zPlane->p2.x, m_zPlane->p2.z)
                   << QPointF(m_zPlane->p3.x, m_zPlane->p3.z);
            break;
        case YZ_PLANE:
            points << QPointF(m_zPlane->p1.y, m_zPlane->p1.z)
                   << QPointF(m_zPlane->p2.y, m_zPlane->p2.z)
                   << QPointF(m_zPlane->p3.y, m_zPlane->p3.z);
            break;
    }
    
    for (int i = 0; i < points.size(); ++i) {
        painter.drawEllipse(points[i], pointSize, pointSize);
        
        // Draw point labels
        painter.save();
        painter.resetTransform();
        QPointF screenPos = worldToScreen(QVector3D(points[i].x(), points[i].y(), 0));
        painter.setPen(QPen(Qt::white, 1));
        painter.setFont(QFont("Arial", 8, QFont::Bold));
        painter.drawText(screenPos + QPointF(10, -5), QString("P%1").arg(i + 1));
        painter.restore();
    }
}

void ZPlaneVisualization::drawCurrentPosition(QPainter &painter)
{
    painter.setPen(QPen(m_currentPosColor, 0));
    painter.setBrush(QBrush(m_currentPosColor));
    
    QPointF currentPos;
    switch (m_viewMode) {
        case XY_PLANE:
            currentPos = QPointF(m_currentPosition.x(), m_currentPosition.y());
            break;
        case XZ_PLANE:
            currentPos = QPointF(m_currentPosition.x(), m_currentPosition.z());
            break;
        case YZ_PLANE:
            currentPos = QPointF(m_currentPosition.y(), m_currentPosition.z());
            break;
    }
    
    double size = 4.0 / m_scaleFactor;
    painter.drawEllipse(currentPos, size, size);
    
    // Draw crosshair
    painter.setPen(QPen(m_currentPosColor, 0, Qt::SolidLine));
    painter.drawLine(currentPos + QPointF(-size*2, 0), currentPos + QPointF(size*2, 0));
    painter.drawLine(currentPos + QPointF(0, -size*2), currentPos + QPointF(0, size*2));
}

void ZPlaneVisualization::drawLegend(QPainter &painter)
{
    painter.setPen(QPen(Qt::white, 1));
    painter.setFont(QFont("Arial", 8));
    
    int y = 15;
    int lineHeight = 15;
    
    // View mode
    QString viewText;
    switch (m_viewMode) {
        case XY_PLANE: viewText = "Top View (XY)"; break;
        case XZ_PLANE: viewText = "Side View (XZ)"; break;
        case YZ_PLANE: viewText = "Side View (YZ)"; break;
    }
    painter.drawText(10, y, viewText);
    y += lineHeight;
    
    // Legend items
    if (m_zPlane && m_zPlane->isValid) {
        painter.setBrush(QBrush(m_planeColor));
        painter.drawRect(10, y, 10, 10);
        painter.drawText(25, y + 8, "Z-Plane");
        y += lineHeight;
        
        if (m_showSafetyZone) {
            painter.setBrush(QBrush(m_safeZoneColor));
            painter.drawRect(10, y, 10, 10);
            painter.drawText(25, y + 8, QString("Safety Zone (%1mm)").arg(m_zPlane->safetyMargin, 0, 'f', 1));
            y += lineHeight;
        }
    }
    
    // Current position
    painter.setBrush(QBrush(m_currentPosColor));
    painter.drawEllipse(10, y, 10, 10);
    painter.drawText(25, y + 8, "Current Position");
}

void ZPlaneVisualization::drawStatusInfo(QPainter &painter)
{
    if (!m_zPlane) return;
    
    painter.setPen(QPen(Qt::white, 1));
    painter.setFont(QFont("Arial", 8));
    
    QStringList statusLines;
    
    if (m_zPlane->isValid) {
        // Check if current position is safe
        bool isSafe = m_zPlane->isPointSafe(m_currentPosition.x(), 
                                           m_currentPosition.y(), 
                                           m_currentPosition.z());
        
        QString safetyStatus = isSafe ? "SAFE" : "UNSAFE";
        QColor statusColor = isSafe ? Qt::green : Qt::red;
        
        statusLines << QString("Status: %1").arg(safetyStatus);
        statusLines << QString("Position: (%1, %2, %3)")
                      .arg(m_currentPosition.x(), 0, 'f', 1)
                      .arg(m_currentPosition.y(), 0, 'f', 1)
                      .arg(m_currentPosition.z(), 0, 'f', 1);
        
        if (!isSafe) {
            double safeZ = m_zPlane->calculateSafeZ(m_currentPosition.x(), m_currentPosition.y());
            statusLines << QString("Safe Z: %1").arg(safeZ, 0, 'f', 1);
        }
        
        painter.setPen(QPen(statusColor, 1));
        painter.drawText(width() - 150, 15, statusLines[0]);
        
        painter.setPen(QPen(Qt::white, 1));
        for (int i = 1; i < statusLines.size(); ++i) {
            painter.drawText(width() - 150, 15 + i * 15, statusLines[i]);
        }
    } else {
        painter.setPen(QPen(Qt::yellow, 1));
        painter.drawText(width() - 150, 15, "No Z-Plane Configured");
    }
}

QPointF ZPlaneVisualization::worldToScreen(const QVector3D& worldPos) const
{
    QPointF point2D;
    switch (m_viewMode) {
        case XY_PLANE:
            point2D = QPointF(worldPos.x(), worldPos.y());
            break;
        case XZ_PLANE:
            point2D = QPointF(worldPos.x(), worldPos.z());
            break;
        case YZ_PLANE:
            point2D = QPointF(worldPos.y(), worldPos.z());
            break;
    }
    
    return m_worldToScreenTransform.map(point2D);
}

QVector3D ZPlaneVisualization::screenToWorld(const QPointF& screenPos) const
{
    QPointF worldPoint2D = m_worldToScreenTransform.inverted().map(screenPos);
    
    QVector3D worldPos;
    switch (m_viewMode) {
        case XY_PLANE:
            worldPos = QVector3D(worldPoint2D.x(), worldPoint2D.y(), 0);
            break;
        case XZ_PLANE:
            worldPos = QVector3D(worldPoint2D.x(), 0, worldPoint2D.y());
            break;
        case YZ_PLANE:
            worldPos = QVector3D(0, worldPoint2D.x(), worldPoint2D.y());
            break;
    }
    
    return worldPos;
}

void ZPlaneVisualization::updateTransform()
{
    // Calculate scale to fit world bounds in widget
    double scaleX = width() / m_worldBounds.width();
    double scaleY = height() / m_worldBounds.height();
    m_scaleFactor = qMin(scaleX, scaleY) * 0.8; // Leave some margin
    
    // Calculate translation to center the view
    double centerX = width() * 0.5;
    double centerY = height() * 0.5;
    
    m_worldToScreenTransform = QTransform();
    m_worldToScreenTransform.translate(centerX + m_panOffset.x(), centerY + m_panOffset.y());
    m_worldToScreenTransform.scale(m_scaleFactor, -m_scaleFactor); // Flip Y for standard coordinates
    m_worldToScreenTransform.translate(-m_worldBounds.center().x(), -m_worldBounds.center().y());
}

QColor ZPlaneVisualization::getSafetyColor(bool isSafe) const
{
    return isSafe ? m_safeZoneColor : m_unsafeZoneColor;
}

QString ZPlaneVisualization::formatCoordinate(double value) const
{
    return QString::number(value, 'f', 1);
}
