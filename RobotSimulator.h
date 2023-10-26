#ifndef ROBOTSIMULATOR_H
#define ROBOTSIMULATOR_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>

class RobotSimulator : public QGraphicsView
{
    Q_OBJECT

public:
    RobotSimulator(QWidget *parent = nullptr);
    void moveTo(float targetX, float targetY, float targetV, float targetA);

public slots:
    void updatePosition();

private:
    float x, y;  // Current coordinates
    float vx, vy; // Current velocities
    float ax, ay; // Current accelerations
    float targetX, targetY; // Target coordinates
    float targetV, targetA; // Target velocity and acceleration
    QGraphicsEllipseItem *endEffector; // GUI representation of the end effector
    QGraphicsScene *scene; // The scene containing the end effector
    QTimer *timer; // Timer for updates
};

#endif // ROBOTSIMULATOR_H
