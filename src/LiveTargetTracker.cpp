#include "LiveTargetTracker.h"
#include <cmath>

void LiveTargetTracker::reset(QVector3D position, qint64 milliseconds)
{
    m_samples = {{position, milliseconds}};
    m_velocity = {};
}

void LiveTargetTracker::observe(QVector3D position, qint64 milliseconds)
{
    if (m_samples.isEmpty() || milliseconds < m_samples.last().milliseconds ||
        milliseconds - m_samples.last().milliseconds > 100) {
        reset(position, milliseconds);
        return;
    }
    const auto delta = position - m_samples.last().position;
    if (delta.isNull()) return;
    // Do not predict along the old direction after a reversal.
    if (QVector3D::dotProduct(delta, m_velocity) < 0) {
        reset(position, milliseconds);
        return;
    }
    if (milliseconds == m_samples.last().milliseconds)
        m_samples.last().position = position;
    else
        m_samples.append({position, milliseconds});
    while (m_samples.size() > 2 && milliseconds - m_samples[1].milliseconds >= 40)
        m_samples.removeFirst();
    const auto age = milliseconds - m_samples.first().milliseconds;
    if (age >= 8)
        m_velocity = (position - m_samples.first().position) * (1000.0f / age);
}

QVector3D LiveTargetTracker::velocity(qint64 milliseconds, float speedLimit) const
{
    if (m_samples.size() < 2 || !std::isfinite(speedLimit) || speedLimit <= 0) return {};
    const auto age = milliseconds - m_samples.last().milliseconds;
    if (age < 0 || age >= 80) return {};
    const float decay = age <= 40 ? 1.0f : (80 - age) / 40.0f;
    const float length = m_velocity.length();
    if (!std::isfinite(length) || length < 0.001f) return {};
    return m_velocity * (decay * qMin(1.0f, speedLimit / length));
}
