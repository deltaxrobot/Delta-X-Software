#ifndef CONVEYORVISUALIZATION_H
#define CONVEYORVISUALIZATION_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QVector3D>
#include <QColor>
#include <QRect>
#include <ObjectInfo.h>

class ConveyorVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit ConveyorVisualization(QWidget *parent = nullptr);
    ~ConveyorVisualization();

    // Configuration
    void setConveyorBounds(float xMin, float xMax, float yMin, float yMax);
    void setUpdateInterval(int msec = 50); // 20 FPS default

public slots:
    void updateObjects(const QVector<ObjectInfo>& objects);
    void clearObjects();
    void setConveyorDirection(const QVector3D& direction);

protected:
    void paintEvent(QPaintEvent *event) override;
    void drawConveyorBelt(QPainter &painter);
    void drawObjects(QPainter &painter);
    void drawGrid(QPainter &painter);
    void drawBoundaries(QPainter &painter);
    void drawLegend(QPainter &painter);
    void drawStatusInfo(QPainter &painter);

private:
    // Coordinate conversion
    QPointF realToScreen(float x, float y) const;
    QSizeF realToScreenSize(float width, float height) const;

private:
    QTimer *m_updateTimer;
    QVector<ObjectInfo> m_objects;
    
    // Conveyor properties
    float m_xMin = -300;
    float m_xMax = 1200;
    float m_yMin = -400;
    float m_yMax = 1200;
    QVector3D m_conveyorDirection = QVector3D(0, 1, 0);
    
    // Visual properties
    QColor m_backgroundColor = QColor(42, 42, 44);
    QColor m_conveyorColor = QColor(80, 80, 80);
    QColor m_gridColor = QColor(60, 60, 60);
    QColor m_boundaryColor = QColor(255, 255, 0, 100);
    QColor m_unpickedObjectColor = QColor(0, 255, 0, 180);
    QColor m_pickedObjectColor = QColor(255, 0, 0, 180);
    QColor m_textColor = QColor(255, 255, 255);
    
    // Animation
    float m_conveyorOffset = 0;
    int m_animationSpeed = 2; // pixels per frame
};

#endif // CONVEYORVISUALIZATION_H
