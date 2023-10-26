#include "RobotSimulator.h"
#include <QPen>
#include <cmath>

RobotSimulator::RobotSimulator(QWidget *parent) :
    QGraphicsView(parent),
    x(0), y(0),
    vx(0), vy(0),
    ax(0), ay(0),
    targetX(0), targetY(0),
    targetV(0), targetA(0)
{
    // Set up the QGraphicsView
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(-100, -100, 200, 200);  // Set scene size
    setRenderHint(QPainter::Antialiasing);

    // Create end effector
    endEffector = new QGraphicsEllipseItem(x-5, y-5, 10, 10);
    QPen pen(Qt::black);
    pen.setWidth(1);
    endEffector->setPen(pen);
    scene->addItem(endEffector);

    // Timer for regular updates
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RobotSimulator::updatePosition);
    timer->start(16); // Approximately 60 FPS
}

void RobotSimulator::moveTo(float targetX, float targetY, float targetV, float targetA)
{
    this->targetX = targetX;
    this->targetY = targetY;
    this->targetV = targetV;
    this->targetA = targetA;
}

void RobotSimulator::updatePosition()
{
    // Compute distance to target
    float dx = targetX - x;
    float dy = targetY - y;
    float distanceToTarget = std::sqrt(dx * dx + dy * dy);

    // Compute unit vector towards target
    float ux = dx / distanceToTarget;
    float uy = dy / distanceToTarget;

    // Compute acceleration components
    ax = targetA * ux;
    ay = targetA * uy;

    // Update velocity based on acceleration
    vx += ax * 0.016; // dt = 16ms = 0.016s
    vy += ay * 0.016;

    // Limit velocity to targetV
    float currentV = std::sqrt(vx * vx + vy * vy);
    if(currentV > targetV)
    {
        vx = targetV * ux;
        vy = targetV * uy;
    }

    // Update position based on velocity
    x += vx * 0.016;
    y += vy * 0.016;

    // Update the QGraphicsEllipseItem position
    endEffector->setRect(x - 5, y - 5, 10, 10);
}
