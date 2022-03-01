#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include <QElapsedTimer>
#include <QPoint>
#include <QLine>
#include <QtMath>

class Encoder : public QObject
{
    Q_OBJECT
public:
    Encoder();
    ~Encoder();

    void SetPosition(float value);
    void SetDeviationAngle(float value);
    float GetPosition();
    float GetVelocity();
    float GetStep();
    float GetMeasuredDistance();
    QPointF GetOffset();
    QPointF CalculateOffset(float distance);

public slots:
    void MarkPosition();

private:
    QElapsedTimer elapseTimer;
    float currentPosition = 0;
    float velocity = 0;
    float lastPosition = 0;
    float step;
    float markPosition = 0;
    float measurePosition = 0;
    float deviationAngle = 0;
    QPointF offset;
};

#endif
