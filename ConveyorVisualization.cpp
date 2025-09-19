#include "ConveyorVisualization.h"
#include <QPaintEvent>
#include <QDebug>
#include <QtMath>
#include <QSizePolicy>

ConveyorVisualization::ConveyorVisualization(QWidget *parent)
    : QWidget(parent)
    , m_updateTimer(new QTimer(this))
{
    // Optimal size that fits well in UI container
    setMinimumSize(600, 350);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_OpaquePaintEvent);
    
    // Enable mouse tracking for future interactivity
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    
    // Setup update timer for animation
    connect(m_updateTimer, &QTimer::timeout, this, [this]() {
        // Animate conveyor belt pattern (moving horizontally = Y-axis direction)
        m_conveyorOffset += m_animationSpeed;
        if (m_conveyorOffset > 20) m_conveyorOffset = 0; // Reset for pattern
        update();
    });
    
    setUpdateInterval(50); // 20 FPS
}

ConveyorVisualization::~ConveyorVisualization()
{
}

void ConveyorVisualization::setConveyorBounds(float xMin, float xMax, float yMin, float yMax)
{
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;
    update();
}

void ConveyorVisualization::setUpdateInterval(int msec)
{
    m_updateTimer->setInterval(msec);
    if (!m_updateTimer->isActive()) {
        m_updateTimer->start();
    }
}

void ConveyorVisualization::updateObjects(const QVector<ObjectInfo>& objects)
{
    m_objects = objects;
    update(); // Trigger repaint
}

void ConveyorVisualization::clearObjects()
{
    m_objects.clear();
    update();
}

void ConveyorVisualization::setConveyorDirection(const QVector3D& direction)
{
    m_conveyorDirection = direction.normalized();
    update();
}

void ConveyorVisualization::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    
    // Enable high-quality rendering
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    
    // Fill background with dark theme matching UI
    painter.fillRect(rect(), QColor(42, 42, 44));
    
    // Only draw if bounds are properly set
    if (m_xMax > m_xMin && m_yMax > m_yMin) {
        drawConveyorBelt(painter);
        drawGrid(painter);
        drawBoundaries(painter);
        drawObjects(painter);
    }
    
    drawLegend(painter);
    drawStatusInfo(painter);
}

void ConveyorVisualization::drawConveyorBelt(QPainter &painter)
{
    // Draw conveyor belt background
    painter.fillRect(rect(), m_conveyorColor);
    
    // Draw animated conveyor pattern (horizontal lines moving along Y-axis)
    painter.setPen(QPen(QColor(100, 100, 100), 1));
    
    int spacing = 20;
    // Horizontal lines across the width, animated horizontally (Y-axis movement)
    for (int i = -width(); i < width() * 2; i += spacing) {
        int x = i + int(m_conveyorOffset);
        painter.drawLine(x, 0, x, height());
    }
    
    // Draw conveyor direction arrows pointing in Y+ direction (rightward)
    painter.setPen(QPen(QColor(150, 150, 150), 2));
    int arrowSpacing = 80;
    for (int y = 60; y < height() - 60; y += arrowSpacing) {
        int x = width() / 2 + (int(m_conveyorOffset) % 40) - 20;
        // Arrow pointing in positive Y direction (rightward)
        painter.drawLine(x, y, x + 15, y);
        painter.drawLine(x + 15, y, x + 10, y - 5);
        painter.drawLine(x + 15, y, x + 10, y + 5);
    }
}

void ConveyorVisualization::drawGrid(QPainter &painter)
{
    // Use adaptive grid spacing based on zoom level
    float xRange = m_xMax - m_xMin;
    float yRange = m_yMax - m_yMin;
    float gridSpacing = 100; // Default 100mm
    
    if (xRange > 2000 || yRange > 2000) {
        gridSpacing = 200; // Larger spacing for wide views
    } else if (xRange < 500 && yRange < 500) {
        gridSpacing = 50;  // Smaller spacing for detailed views
    }
    
    // Draw fine grid lines
    painter.setPen(QPen(QColor(60, 60, 60), 1, Qt::DotLine));
    
    // Vertical grid lines (X-axis values)
    for (float x = m_xMin; x <= m_xMax; x += gridSpacing) {
        if (qAbs(x) < 1) continue; // Skip center line
        QPointF screenPos = realToScreen(x, m_yMin);
        QPointF screenEnd = realToScreen(x, m_yMax);
        painter.drawLine(screenPos, screenEnd);
    }
    
    // Horizontal grid lines (Y-axis values)
    for (float y = m_yMin; y <= m_yMax; y += gridSpacing) {
        if (qAbs(y) < 1) continue; // Skip center line
        QPointF screenPos = realToScreen(m_xMin, y);
        QPointF screenEnd = realToScreen(m_xMax, y);
        painter.drawLine(screenPos, screenEnd);
    }
    
    // Draw center axes with thicker lines
    painter.setPen(QPen(QColor(120, 120, 120), 2));
    
    // X=0 axis (vertical line on screen - X is vertical in real world)
    QPointF xAxisStart = realToScreen(0, m_yMin);
    QPointF xAxisEnd = realToScreen(0, m_yMax);
    painter.drawLine(xAxisStart, xAxisEnd);
    
    // Y=0 axis (horizontal line on screen - Y is horizontal in real world)
    QPointF yAxisStart = realToScreen(m_xMin, 0);
    QPointF yAxisEnd = realToScreen(m_xMax, 0);
    painter.drawLine(yAxisStart, yAxisEnd);
    
    // Draw origin marker (0,0)
    painter.setPen(QPen(QColor(255, 80, 80), 3));
    painter.setBrush(QBrush(QColor(255, 80, 80)));
    QPointF origin = realToScreen(0, 0);
    painter.drawEllipse(origin - QPointF(4, 4), 8, 8);
    
    // Draw origin label
    painter.setPen(QColor(255, 255, 255));
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(origin + QPointF(8, -8), "(0,0)");
    
    // Draw axis direction indicators
    painter.setPen(QColor(200, 200, 200));
    font.setBold(false);
    font.setPointSize(10);
    painter.setFont(font);
    
    painter.drawText(realToScreen(m_xMax * 0.9f, 0) + QPointF(5, -5), "X+");
    painter.drawText(realToScreen(m_xMin * 0.9f, 0) + QPointF(5, 15), "X-");
    painter.drawText(realToScreen(0, m_yMax * 0.9f) + QPointF(8, 3), "Y+");
    painter.drawText(realToScreen(0, m_yMin * 0.9f) + QPointF(-25, 3), "Y-");
}

void ConveyorVisualization::drawBoundaries(QPainter &painter)
{
    // Draw tracking boundaries
    painter.setPen(QPen(m_boundaryColor, 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    
    QPointF topLeft = realToScreen(m_xMin, m_yMax);
    QPointF bottomRight = realToScreen(m_xMax, m_yMin);
    QRectF boundaryRect(topLeft, bottomRight);
    
    painter.drawRect(boundaryRect);
    
    // Label
    painter.setPen(m_boundaryColor);
    painter.drawText(topLeft + QPointF(5, 15), "Tracking Area");
}

void ConveyorVisualization::drawObjects(QPainter &painter)
{
    for (const auto& obj : m_objects) {
        // Choose color based on picked status
        QColor objectColor = obj.isPicked ? m_pickedObjectColor : m_unpickedObjectColor;
        
        painter.setPen(QPen(objectColor, 2));
        painter.setBrush(QBrush(objectColor));
        
        // Convert real coordinates to screen coordinates
        QPointF center = realToScreen(obj.center.x(), obj.center.y());
        QSizeF size = realToScreenSize(obj.width, obj.height);
        
        // Ensure minimum visible size
        float minSize = 12.0f;
        if (size.width() < minSize) size.setWidth(minSize);
        if (size.height() < minSize) size.setHeight(minSize);
        
        // Draw object with enhanced visuals
        QRectF objectRect(center.x() - size.width()/2, 
                         center.y() - size.height()/2,
                         size.width(), size.height());
        
        // Draw shadow for depth
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(0, 0, 0, 60)));
        painter.drawRoundedRect(objectRect.translated(2, 2), 4, 4);
        
        // Draw main object with border
        painter.setPen(QPen(objectColor.darker(150), 2));
        painter.setBrush(QBrush(objectColor));
        painter.drawRoundedRect(objectRect, 4, 4);
        
        // Draw UID label with background
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(0, 0, 0, 200)));
        QRectF labelRect(center.x() - 15, center.y() - 8, 30, 16);
        painter.drawRoundedRect(labelRect, 3, 3);
        
        painter.setPen(QColor(255, 255, 255));
        QFont font = painter.font();
        font.setBold(true);
        font.setPointSize(9);
        painter.setFont(font);
        painter.drawText(labelRect, Qt::AlignCenter, QString::number(obj.uid));
        
        // Draw status indicator
        if (obj.isPicked) {
            // Draw checkmark for picked objects
            painter.setPen(QPen(QColor(0, 255, 0), 3));
            QPointF checkStart = center + QPointF(size.width()/2 - 8, -2);
            QPointF checkMid = center + QPointF(size.width()/2 - 5, 1);
            QPointF checkEnd = center + QPointF(size.width()/2 - 2, -4);
            
            painter.drawLine(checkStart, checkMid);
            painter.drawLine(checkMid, checkEnd);
        } else {
            // Draw movement arrow for unpicked objects
            painter.setPen(QPen(QColor(255, 215, 0), 2));
            QPointF arrowStart = center + QPointF(size.width()/2 + 5, 0);
            QPointF arrowEnd = arrowStart + QPointF(15, 0); // Y+ direction (rightward)
            
            painter.drawLine(arrowStart, arrowEnd);
            painter.drawLine(arrowEnd, arrowEnd + QPointF(-5, -3));
            painter.drawLine(arrowEnd, arrowEnd + QPointF(-5, 3));
        }
    }
}

void ConveyorVisualization::drawLegend(QPainter &painter)
{
    // Draw legend in top-right corner
    int legendX = width() - 150;
    int legendY = 10;
    
    painter.fillRect(legendX - 5, legendY - 5, 140, 70, QColor(0, 0, 0, 150));
    
    // Unpicked objects
    painter.setPen(QPen(m_unpickedObjectColor, 2));
    painter.setBrush(QBrush(m_unpickedObjectColor));
    painter.drawRect(legendX, legendY, 15, 10);
    painter.setPen(m_textColor);
    painter.drawText(legendX + 20, legendY + 8, "Unpicked");
    
    // Picked objects  
    legendY += 20;
    painter.setPen(QPen(m_pickedObjectColor, 2));
    painter.setBrush(QBrush(m_pickedObjectColor));
    painter.drawRect(legendX, legendY, 15, 10);
    painter.setPen(m_textColor);
    painter.drawText(legendX + 20, legendY + 8, "Picked");
    
    // Object count
    legendY += 20;
    painter.setPen(m_textColor);
    painter.drawText(legendX, legendY + 8, QString("Total: %1").arg(m_objects.size()));
}

void ConveyorVisualization::drawStatusInfo(QPainter &painter)
{
    // Draw status information at bottom-right
    painter.setPen(QColor(180, 180, 180));
    QFont font = painter.font();
    font.setPointSize(9);
    painter.setFont(font);
    
    int statusX = width() - 200;
    int statusY = height() - 60;
    
    // Coordinate system info
    painter.drawText(statusX, statusY, QString("Coordinate System:"));
    painter.drawText(statusX, statusY + 15, QString("X: ±%1mm (Vertical)").arg(qMax(qAbs(m_xMin), qAbs(m_xMax))));
    painter.drawText(statusX, statusY + 30, QString("Y: ±%1mm (Horizontal)").arg(qMax(qAbs(m_yMin), qAbs(m_yMax))));
    painter.drawText(statusX, statusY + 45, QString("Objects: %1 active").arg(m_objects.size()));
}

QPointF ConveyorVisualization::realToScreen(float x, float y) const
{
    // Convert real world coordinates (mm) to screen coordinates (pixels)
    // Origin (0,0) at center of widget
    // SWAPPED: X is vertical (up/down), Y is horizontal (left/right)
    
    float scaleX = (height() - 40) / (m_xMax - m_xMin);  // X maps to screen height
    float scaleY = (width() - 40) / (m_yMax - m_yMin);   // Y maps to screen width
    
    // Use smaller scale to maintain aspect ratio
    float scale = qMin(scaleX, scaleY);
    
    // Center coordinate system: (0,0) at widget center
    float centerX = width() / 2.0f;
    float centerY = height() / 2.0f;
    
    // COORDINATE MAPPING:
    // Real X (vertical) → Screen Y (up/down)
    // Real Y (horizontal) → Screen X (left/right)
    float screenX = centerX + y * scale;  // Y maps to horizontal screen position
    float screenY = centerY - x * scale;  // X maps to vertical screen position (flipped)
    
    return QPointF(screenX, screenY);
}

QSizeF ConveyorVisualization::realToScreenSize(float width, float height) const
{
    float scaleX = (this->height() - 40) / (m_xMax - m_xMin);  // X maps to screen height
    float scaleY = (this->width() - 40) / (m_yMax - m_yMin);   // Y maps to screen width
    float scale = qMin(scaleX, scaleY);
    
    // SWAPPED: width/height mapping follows coordinate swap
    return QSizeF(height * scale, width * scale);  // Swap width/height
}
