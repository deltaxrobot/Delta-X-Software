#pragma once
#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QPoint>
#include <memory>

class QWidget;

// Owns a foreground-only Windows raw mouse registration for the held gesture.
class RelativeMouseCapture : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit RelativeMouseCapture(QObject* parent = nullptr);
    ~RelativeMouseCapture() override;
    virtual bool available() const;
    virtual bool start(QWidget* pad);
    virtual void stop();
    bool active() const { return m_active; }
    bool nativeEventFilter(const QByteArray& type, void* message, qintptr* result) override;
signals:
    void moved(QPoint counts);
    void released();
    void failed(QString reason);
protected:
    bool m_active = false;
private:
    struct NativeState;
    std::unique_ptr<NativeState> m_native;
};
