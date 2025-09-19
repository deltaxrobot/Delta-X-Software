#ifndef ZPLANEVISUALIZATION_H
#define ZPLANEVISUALIZATION_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QVector3D>
#include <QPointF>

// Forward declarations
struct ZPlane;
struct ZPlanePoint;

/**
 * @brief 2D Visualization widget for Z-plane workspace limits
 * 
 * This widget provides visual feedback for workspace safety zones,
 * showing the configured Z-plane, safety margins, and current robot position.
 */
class ZPlaneVisualization : public QWidget
{
    Q_OBJECT

public:
    enum ViewMode {
        XY_PLANE = 0,  // Top view (X-Y plane)
        XZ_PLANE = 1,  // Side view (X-Z plane) 
        YZ_PLANE = 2   // Side view (Y-Z plane)
    };

    explicit ZPlaneVisualization(QWidget *parent = nullptr);
    ~ZPlaneVisualization();

    // Configuration methods
    void setZPlane(const ZPlane* zPlane);
    void setViewMode(ViewMode mode);
    void setShowSafetyZone(bool show);
    void setShowGrid(bool show);
    void setCurrentPosition(const QVector3D& position);

public slots:
    void updateVisualization();
    void onViewModeChanged(int mode);
    void onShowSafetyZoneToggled(bool show);
    void onShowGridToggled(bool show);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    // Core rendering methods
    void drawGrid(QPainter &painter);
    void drawAxes(QPainter &painter);
    void drawZPlane(QPainter &painter);
    void drawSafetyZone(QPainter &painter);
    void drawCalibrationPoints(QPainter &painter);
    void drawCurrentPosition(QPainter &painter);
    void drawLegend(QPainter &painter);
    void drawStatusInfo(QPainter &painter);
    
    // Coordinate transformation methods
    QPointF worldToScreen(const QVector3D& worldPos) const;
    QVector3D screenToWorld(const QPointF& screenPos) const;
    void updateTransform();
    
    // Utility methods
    QColor getSafetyColor(bool isSafe) const;
    QString formatCoordinate(double value) const;

private:
    // Data members
    const ZPlane* m_zPlane;           // Reference to Z-plane configuration
    ViewMode m_viewMode;              // Current view mode
    bool m_showSafetyZone;            // Show safety zone visualization
    bool m_showGrid;                  // Show coordinate grid
    QVector3D m_currentPosition;      // Current robot position
    
    // Visualization parameters
    QRectF m_worldBounds;             // World coordinate bounds
    QTransform m_worldToScreenTransform; // Coordinate transformation
    double m_scaleFactor;             // Current zoom level
    QPointF m_panOffset;              // Pan offset
    
    // Interaction state
    bool m_dragging;                  // Mouse dragging state
    QPoint m_lastMousePos;            // Last mouse position
    
    // Visual settings
    QColor m_backgroundColor;         // Background color
    QColor m_gridColor;               // Grid line color
    QColor m_axesColor;               // Axes color
    QColor m_planeColor;              // Z-plane color
    QColor m_safeZoneColor;           // Safety zone color
    QColor m_unsafeZoneColor;         // Unsafe zone color
    QColor m_currentPosColor;         // Current position color
    
    // Update timer
    QTimer* m_updateTimer;            // Refresh timer
};

#endif // ZPLANEVISUALIZATION_H
