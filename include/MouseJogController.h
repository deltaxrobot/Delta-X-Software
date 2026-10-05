#pragma once

#include "DeviceCommandBroker.h"
#include <QVector3D>
#include <QPointer>
#include "GcodeMotionStream.h"

// Mouse input adapter; the reusable stream owns planning and transmission.
class MouseJogController final : public QObject
{
    Q_OBJECT
public:
    explicit MouseJogController(DeviceCommandBroker* broker, QString device, QObject* parent = nullptr);
    ~MouseJogController() override;
    bool start();
    bool beginHold();
    void addInput(float x, float y, float z);
    void endHold();
    void shutdown();
    bool ready() const { return m_ready; }
    void setSpeed(float speed);

signals:
    void statusChanged(QString text);
    void remainingDistanceChanged(float distance);
    void streamMetricsChanged(int pending, double seconds);

private:
    enum class Request { None, StopJog, Absolute, Position };
    void send(Request request, const QString& command);
    void response(const QString& text);
    void tick();
    void fail(const QString& reason);
    DeviceCommandBroker* m_broker;
    QString m_device;
    QString m_owner;
    QTimer m_timer;
    Request m_request = Request::None;
    QVector3D m_position, m_target;
    QPointer<GcodeMotionStream> m_stream;
    float m_speed = 100.0f;
    bool m_leased = false;
    bool m_ready = false;
    bool m_held = false;
};
