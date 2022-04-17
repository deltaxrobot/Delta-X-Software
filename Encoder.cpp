#include "Encoder.h"

Encoder::Encoder()
{

}

Encoder::~Encoder()
{

}

void Encoder::SetPosition(float value)
{
    float time = elapseTimer.restart();

    currentPosition = value;
    step = currentPosition - lastPosition;
    lastPosition = currentPosition;
    velocity = step / time;

    offset = CalculateOffset(step);

    if (offset != QPointF(0, 0))
        emit DistanceMoved(offset);
}

void Encoder::SetDeviationAngle(float value)
{
    deviationAngle = value;
}

void Encoder::MarkPosition()
{
    markPosition = currentPosition;
}

float Encoder::GetPosition()
{
    return currentPosition;
}

float Encoder::GetVelocity()
{
    return velocity;
}

float Encoder::GetStep()
{
    return step;
}

float Encoder::GetMeasuredDistance()
{
    measurePosition = currentPosition - markPosition;

    return measurePosition;
}

QPointF Encoder::GetOffset()
{
    return offset;
}

QPointF Encoder::CalculateOffset(float distance)
{
    QPointF point3(0, 0);

    QLineF line;
    line.setP1(point3);
    line.setAngle(deviationAngle);

    if (distance == 0)
        return point3;

    line.setLength(distance);

    float cosa = qCos(qDegreesToRadians(360 - deviationAngle));
    float sina = qSin(qDegreesToRadians(360 - deviationAngle));

    line.setP2(QPointF(distance * cosa, distance * sina));

    float p2X = ((float)((int)(line.p2().x() * 100))) / 100;
    float p2Y = ((float)((int)(line.p2().y() * 100))) / 100;

    return QPointF(p2X, p2Y);
}
