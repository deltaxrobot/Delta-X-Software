#include "GcodeMotionStream.h"
#include <cmath>
#include <utility>

using namespace GcodeMotion;

GcodeMotionStream::GcodeMotionStream(DeviceCommandBroker* broker, QString owner, QString device,
                                   QVector3D position)
    : QObject(broker), m_broker(broker), m_owner(std::move(owner)), m_device(std::move(device)),
      m_completed{position, {}, 0}, m_target(position)
{
    m_inputClock.start();
    m_tracker.reset(position, 0);
    m_timer.setInterval(8);
    m_timer.setTimerType(Qt::PreciseTimer);
    connect(&m_timer, &QTimer::timeout, this, &GcodeMotionStream::pump);
    connect(broker, &DeviceCommandBroker::ResponseForOwner, this,
        [this](const QString& owner, const QString&, const QString& text, quint64) {
            if (owner == m_owner && !m_failed) response(text);
        });
    connect(broker, &DeviceCommandBroker::CommandRejected, this,
        [this](const QString& owner, const QString&, const QString&, const QString& reason) {
            if (owner == m_owner) fail(reason);
        });
    connect(broker, &DeviceCommandBroker::CommandDispatched, this,
        [this](quint64, const QString& owner, const QString& device, const QString&, DeviceCommandBroker::Origin) {
            if (device == m_device && owner != m_owner) fail(tr("Motion interrupted by another command."));
        });
    m_timer.start();
}

bool GcodeMotionStream::setTarget(QVector3D target)
{
    if (m_failed || m_closing) return false;
    for (int i = 0; i < 3; ++i)
        if (!std::isfinite(target[i]) || std::abs(target[i]) > 100000) return false;
    m_target = target;
    if (!m_following || m_stopping || m_pathMode)
        m_tracker.reset(target, m_inputClock.elapsed());
    else
        m_tracker.observe(target, m_inputClock.elapsed());
    m_pathMode = m_stopping = false;
    m_path.clear();
    m_following = true;
    return true;
}
bool GcodeMotionStream::setPath(const QVector<QVector3D>& path, QString* error)
{
    if (error) error->clear();
    if (!idle() || m_failed || m_closing) {
        if (error) *error = tr("A path may only start while the stream is idle.");
        return false;
    }
    QString why;
    const auto planned = plan(m_completed, path, m_limits, &why);
    if (!why.isEmpty()) { if (error) *error = why; return false; }
    m_path = planned;
    m_tracker.reset(m_completed.position, m_inputClock.elapsed());
    m_pathMode = m_following = !m_path.isEmpty();
    m_stopping = false;
    if (!path.isEmpty()) m_target = path.last();
    return true;
}
void GcodeMotionStream::setSpeed(int speed)
{
    // A fixed path is already planned; live targets can be replanned from the
    // committed boundary, braking first if a lower speed is requested.
    if (!m_pathMode) m_limits.speed = qBound(10, speed, 150);
}
State GcodeMotionStream::boundary() const
{
    return m_inflight.isEmpty() ? m_completed : m_inflight.last().endState();
}
double GcodeMotionStream::remainingSeconds() const
{
    double seconds = 0;
    for (const auto& move : m_inflight) seconds += move.seconds + m_commandOverhead;
    if (!m_inflight.isEmpty() && m_headAge.isValid())
        seconds -= qMin(m_headAge.elapsed() / 1000.0, m_inflight.first().seconds);
    return qMax(0.0, seconds);
}
QVector<Segment> GcodeMotionStream::nextPlan(const Limits& limits, QString* error) const
{
    const State start = boundary();
    if (m_stopping) return start.speed ? QVector<Segment>{brake(start, limits)} : QVector<Segment>{};
    if (m_pathMode) return m_path;
    return follow(start, m_target, m_tracker.velocity(m_inputClock.elapsed(), float(limits.speed)),
                  remainingSeconds(), limits, error);
}
void GcodeMotionStream::pump()
{
    if (m_failed || m_pumping) return;
    if (m_broker->cellState() != QStringLiteral("Ready")) {
        fail(tr("Cell left Ready state."));
        return;
    }
    m_pumping = true;
    int dispatched = 0;
    while (!m_failed && m_following && m_inflight.size() < 2 && dispatched < 2 &&
           !(m_drainAfterDelay && !m_inflight.isEmpty())) {
        // Keep the second slot replaceable on the host until near completion.
        // Filling it immediately would commit a stale short target/brake before
        // the next mouse samples arrive. Never send nonzero S after a known gap.
        if (!m_pathMode && !m_stopping && !m_inflight.isEmpty()) {
            const double refillLead = qBound(0.025, 0.020 + m_commandOverhead, 0.050);
            if (remainingSeconds() > refillLead) break;
            if (m_headAge.elapsed() / 1000.0 >= m_inflight.first().seconds + m_commandOverhead) break;
        }
        QString error;
        auto limits = m_limits;
        if (!m_pathMode) limits.segmentLength = 8.0;
        auto planned = nextPlan(limits, &error);
        if (!error.isEmpty()) { fail(error); break; }
        if (planned.isEmpty()) {
            // Revisit after prediction expires, even with no further input.
            m_following = !m_stopping && !m_pathMode &&
                          !m_tracker.velocity(m_inputClock.elapsed(), float(m_limits.speed)).isNull();
            break;
        }
        auto move = planned.first();
        auto committedTime = [&]() {
            const double braking = move.exit ? brake(move.endState(), limits).seconds : 0;
            return remainingSeconds() + move.seconds + m_commandOverhead + braking;
        };
        // Small commands can still take a long time at low feed. Reduce the
        // live segment length until its profile fits the response budget.
        while (!m_pathMode && !m_stopping &&
               committedTime() > limits.queuedSeconds && limits.segmentLength > 2 * limits.minimumLength) {
            limits.segmentLength = qMax(2 * limits.minimumLength, limits.segmentLength * 0.8);
            planned = nextPlan(limits, &error);
            if (!error.isEmpty() || planned.isEmpty()) break;
            move = planned.first();
        }
        if (!error.isEmpty()) { fail(error); break; }
        if (planned.isEmpty()) break;
        if (committedTime() > m_limits.queuedSeconds && !m_inflight.isEmpty()) break;
        if (!std::isfinite(move.seconds) || move.gcode().size() > 79) {
            fail(tr("Cannot generate a finite controller motion.")); break;
        }
        // One indivisible profile may exceed the nominal budget (e.g. a fixed
        // path at low speed). Report its actual estimate instead of deadlocking.
        if (m_pathMode) m_path.removeFirst();
        if (m_inflight.isEmpty()) m_headAge.restart();
        m_inflight.append(move); // Providers may complete synchronously.
        ++dispatched;
        if (!m_broker->SubmitMotion(m_owner, m_device, move.gcode())) {
            fail(tr("Motion stream rejected the next segment.")); break;
        }
    }
    m_pumping = false;
    publish();
    finishClose();
}
void GcodeMotionStream::response(const QString& text)
{
    if (text.trimmed().compare(QStringLiteral("Ok"), Qt::CaseInsensitive) != 0) {
        fail(text); return;
    }
    if (m_resetPending) {
        m_resetPending = false;
        m_resetDone = true;
        finishClose();
        return;
    }
    if (m_inflight.isEmpty()) { fail(tr("Unexpected motion acknowledgement.")); return; }
    double queuedDuration = 0;
    for (const auto& move : m_inflight) queuedDuration += move.seconds + m_commandOverhead;
    if (m_inflight.size() > 1 && m_headAge.elapsed() / 1000.0 > queuedDuration + 0.02)
        m_drainAfterDelay = true;
    const auto completed = m_inflight.takeFirst();
    if (m_headAge.isValid()) {
        const double excess = qBound(0.0, m_headAge.elapsed() / 1000.0 - completed.seconds, 0.1);
        m_commandOverhead = 0.8 * m_commandOverhead + 0.2 * excess;
    }
    m_completed = completed.endState();
    m_headAge.restart();
    if (m_inflight.isEmpty()) m_drainAfterDelay = false;
    if (m_inflight.isEmpty() && m_completed.speed) {
        // A starved controller has stopped emitting steps. Do not claim the
        // previous nonzero exit speed survived an empty physical queue.
        m_completed.speed = 0;
        if (m_pathMode && !m_path.isEmpty()) {
            QVector<QVector3D> points;
            for (const auto& move : m_path) points.append(move.end);
            QString error;
            m_path = plan(m_completed, points, m_limits, &error);
            if (!error.isEmpty()) { fail(error); return; }
        }
    }
    publish();
    QTimer::singleShot(0, this, &GcodeMotionStream::pump);
}
void GcodeMotionStream::stop()
{
    if (m_failed) return;
    m_path.clear();
    m_pathMode = false;
    m_stopping = m_following = true;
    const auto state = boundary();
    m_target = state.speed ? brake(state, m_limits).end : state.position;
    m_tracker.reset(m_target, m_inputClock.elapsed());
    pump();
}
void GcodeMotionStream::close()
{
    if (m_closing) return;
    m_closing = true;
    stop();
    finishClose();
}
void GcodeMotionStream::finishClose()
{
    if (m_closing && (m_failed || (m_inflight.isEmpty() && !m_following))) {
        if (!m_failed && !m_resetDone) {
            if (!m_resetPending) {
                m_resetPending = true;
                // Do not leave nonzero modal S for the next manual/program move.
                if (!m_broker->SubmitMotion(m_owner, m_device, QStringLiteral("M205 S0")))
                    fail(tr("Could not reset the motion edge speeds."));
            }
            return;
        }
        m_timer.stop();
        m_broker->releaseManualControl(m_owner, m_device);
        deleteLater();
    }
}
void GcodeMotionStream::fail(const QString& reason)
{
    if (m_failed) return;
    m_failed = true;
    m_following = false;
    m_timer.stop();
    m_path.clear();
    m_broker->CancelOwner(m_owner, reason);
    emit failed(reason);
    finishClose();
}
void GcodeMotionStream::publish()
{
    const auto state = boundary();
    const double stopTime = state.speed ? brake(state, m_limits).seconds : 0;
    emit progress(m_completed.position, m_target, m_inflight.size(), remainingSeconds() + stopTime);
}
