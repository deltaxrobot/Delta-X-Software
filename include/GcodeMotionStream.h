#pragma once
#include "DeviceCommandBroker.h"
#include "GcodeMotionPlanner.h"
#include "LiveTargetTracker.h"
#include <QElapsedTimer>

// Lives under the broker, so a closing dialog can leave its braking tail alive.
class GcodeMotionStream final : public QObject
{
    Q_OBJECT
public:
    GcodeMotionStream(DeviceCommandBroker* broker, QString owner, QString device,
                      QVector3D position);
    bool setTarget(QVector3D target);
    bool setPath(const QVector<QVector3D>& path, QString* error = nullptr);
    void setSpeed(int speed);
    void stop();
    void close();
    bool idle() const { return m_inflight.isEmpty() && !m_following; }
    QVector3D position() const { return m_completed.position; }
signals:
    void progress(QVector3D completed, QVector3D target, int pending, double committedSeconds);
    void failed(QString reason);
private:
    void pump();
    void response(const QString& text);
    void fail(const QString& reason);
    void finishClose();
    GcodeMotion::State boundary() const;
    QVector<GcodeMotion::Segment> nextPlan(const GcodeMotion::Limits& limits, QString* error) const;
    double remainingSeconds() const;
    void publish();
    DeviceCommandBroker* m_broker;
    QString m_owner, m_device;
    GcodeMotion::Limits m_limits;
    GcodeMotion::State m_completed;
    QVector3D m_target;
    QVector<GcodeMotion::Segment> m_inflight, m_path;
    QElapsedTimer m_headAge;
    QElapsedTimer m_inputClock;
    LiveTargetTracker m_tracker;
    QTimer m_timer;
    double m_commandOverhead = 0.002;
    bool m_following = false, m_stopping = false, m_closing = false;
    bool m_failed = false, m_pumping = false, m_pathMode = false;
    bool m_resetPending = false, m_resetDone = false;
    bool m_drainAfterDelay = false;
};
