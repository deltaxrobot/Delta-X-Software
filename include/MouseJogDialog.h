#pragma once
#include <QDialog>
#include <QPointF>

class DeviceCommandBroker;
class MouseJogController;
class QDoubleSpinBox;
class QCheckBox;
class RelativeMouseCapture;

class MouseJogDialog final : public QDialog
{
public:
    MouseJogDialog(DeviceCommandBroker* broker, const QString& device, QWidget* parent = nullptr,
                   RelativeMouseCapture* capture = nullptr);
    ~MouseJogDialog() override;
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    bool event(QEvent* event) override;
    void done(int result) override;
private:
    void endDrag();
    MouseJogController* m_controller;
    QWidget* m_pad;
    QDoubleSpinBox* m_scale;
    QDoubleSpinBox* m_zStep;
    QCheckBox* m_continuous;
    RelativeMouseCapture* m_capture;
    QPointF m_lastPoint;
    bool m_dragging = false;
};
