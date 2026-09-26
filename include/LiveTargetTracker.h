#pragma once
#include <QVector>
#include <QVector3D>

// Timestamped intent only, not encoder feedback. Never drops target displacement.
class LiveTargetTracker {
public:
    void reset(QVector3D position, qint64 milliseconds);
    void observe(QVector3D position, qint64 milliseconds);
    QVector3D velocity(qint64 milliseconds, float speedLimit) const;
private:
    struct Sample { QVector3D position; qint64 milliseconds; };
    QVector<Sample> m_samples;
    QVector3D m_velocity;
};
