#include "MouseJogController.h"
#include <QUuid>
#include <cmath>

MouseJogController::MouseJogController(DeviceCommandBroker* broker, QString device, QObject* parent)
    : QObject(parent), m_broker(broker), m_device(device.trimmed().toLower()),
      m_owner(QStringLiteral("manual/mouse/") + QUuid::createUuid().toString())
{
    m_timer.setInterval(16);
    connect(&m_timer, &QTimer::timeout, this, &MouseJogController::tick);
    connect(broker, &DeviceCommandBroker::ResponseForOwner, this,
            [this](const QString& owner, const QString&, const QString& text, quint64) {
        if (owner == m_owner && m_leased) response(text);
    });
    connect(broker, &DeviceCommandBroker::CommandRejected, this,
            [this](const QString& owner, const QString&, const QString&, const QString& reason) {
        if (owner == m_owner && !m_stream) fail(reason);
    });
    connect(broker, &DeviceCommandBroker::CommandDispatched, this,
            [this](quint64, const QString& owner, const QString& deviceId,
                   const QString&, DeviceCommandBroker::Origin) {
        if (m_leased && deviceId == m_device && owner != m_owner)
            fail(tr("Another command interrupted mouse control. Close and reopen to resume."));
    });
}
MouseJogController::~MouseJogController() { shutdown(); }

bool MouseJogController::start()
{
    if (m_leased || m_stream || !m_broker->acquireManualControl(m_owner, m_device)) {
        emit statusChanged(tr("Robot is busy, the stream needs recovery, or the cell is not Ready."));
        return false;
    }
    m_leased = true;
    emit statusChanged(tr("Reading controller position..."));
    m_timer.start();
    send(Request::StopJog, QStringLiteral("jogging (0, 0, 0)"));
    return m_leased || m_ready;
}
void MouseJogController::send(Request request, const QString& command)
{
    m_request = request;
    m_broker->Submit(m_owner, m_device, command, DeviceCommandBroker::Origin::Manual, true, 3000);
}
void MouseJogController::response(const QString& text)
{
    const Request completed = m_request;
    m_request = Request::None;
    if (completed == Request::Position) {
        const auto axes = text.trimmed().split(',');
        QVector3D position;
        if (axes.size() < 3) { fail(tr("Invalid position response. Mouse control stopped.")); return; }
        for (int i = 0; i < 3; ++i) {
            bool ok = false;
            position[i] = axes[i].trimmed().toFloat(&ok);
            if (!ok || !std::isfinite(position[i]) || std::abs(position[i]) > 100000) {
                fail(tr("Invalid position response. Mouse control stopped.")); return;
            }
        }
        m_position = m_target = position;
        // The stream retains this lease through a closing dialog's braking tail.
        m_leased = false;
        m_stream = new GcodeMotionStream(m_broker, m_owner, m_device, position);
        m_stream->setSpeed(int(m_speed));
        connect(m_stream, &GcodeMotionStream::progress, this,
            [this](QVector3D completed, QVector3D target, int pending, double seconds) {
                m_position = completed;
                if (!m_held) m_target = target;
                emit remainingDistanceChanged((target - completed).length());
                emit streamMetricsChanged(pending, seconds);
            });
        connect(m_stream, &GcodeMotionStream::failed, this, &MouseJogController::fail);
        emit remainingDistanceChanged(0);
        m_ready = true;
        emit statusChanged(tr("Ready. Hold the left button inside the pad to move."));
        return;
    }
    if (text.trimmed().compare(QStringLiteral("Ok"), Qt::CaseInsensitive) != 0) {
        fail(tr("Mouse control stopped: %1").arg(text)); return;
    }
    if (completed == Request::StopJog) send(Request::Absolute, QStringLiteral("G90"));
    else if (completed == Request::Absolute) send(Request::Position, QStringLiteral("PositionOffset"));
}
bool MouseJogController::beginHold()
{
    if (!m_ready || !m_stream || !m_stream->idle() || m_broker->cellState() != QStringLiteral("Ready"))
        return false;
    m_target = m_position;
    m_held = true;
    emit remainingDistanceChanged(0);
    emit statusChanged(tr("Following mouse: right = +X, up = +Y, wheel up = +Z."));
    return true;
}
void MouseJogController::addInput(float x, float y, float z)
{
    if (!m_held || !std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) return;
    m_target += QVector3D(x, y, z);
    if (!m_stream || !m_stream->setTarget(m_target))
        fail(tr("Mouse target is out of range. Mouse control stopped."));
}
void MouseJogController::endHold()
{
    if (!m_held) return;
    m_held = false;
    if (m_stream) m_stream->stop();
    if (m_ready) emit statusChanged(tr("Released. Finishing committed moves and the braking tail."));
}
void MouseJogController::setSpeed(float speed)
{
    if (std::isfinite(speed)) {
        m_speed = qBound(10.0f, speed, 150.0f);
        if (m_stream) m_stream->setSpeed(int(m_speed));
    }
}
void MouseJogController::tick()
{
    if (m_broker->cellState() != QStringLiteral("Ready"))
        fail(tr("Cell left Ready state. Mouse control stopped."));
}
void MouseJogController::fail(const QString& reason)
{
    shutdown();
    emit statusChanged(reason);
}
void MouseJogController::shutdown()
{
    m_ready = m_held = false;
    m_timer.stop();
    if (m_stream) {
        m_stream->close();
        m_stream = nullptr;
    }
    if (m_leased) {
        m_leased = false;
        m_broker->releaseManualControl(m_owner, m_device);
    }
}
