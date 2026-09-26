#include "MouseJogDialog.h"
#include "MouseJogController.h"
#include "RelativeMouseCapture.h"
#include <QtWidgets>

MouseJogDialog::MouseJogDialog(DeviceCommandBroker* broker, const QString& device, QWidget* parent,
                               RelativeMouseCapture* capture)
    : QDialog(parent), m_controller(new MouseJogController(broker, device, this))
{
    setWindowTitle(tr("Mouse control - %1 - Adaptive follower v2").arg(device));
    setModal(true);
    resize(660, 570);
    m_capture = capture ? capture : new RelativeMouseCapture(this);
    m_capture->setParent(this);
    auto* layout = new QVBoxLayout(this);
    auto* instructions = new QLabel(tr("Hold the LEFT button in the pad and move for X/Y; scroll for Z. "
        "Continuous capture hides the cursor and removes the pad/screen-edge limit. "
        "Release, press Esc or switch windows to brake and stop."), this);
    instructions->setWordWrap(true);
    layout->addWidget(instructions);
    auto* follower = new QLabel(tr("Adaptive follower v2: velocity tracking, timed segments and just-in-time G-code."), this);
    follower->setObjectName(QStringLiteral("mouseJogAlgorithm"));
    follower->setWordWrap(true);
    layout->addWidget(follower);
    m_continuous = new QCheckBox(tr("Continuous mouse capture (no pad or screen-edge limit)"), this);
    m_continuous->setObjectName(QStringLiteral("mouseJogContinuous"));
    m_continuous->setChecked(m_capture->available());
    m_continuous->setEnabled(m_capture->available());
    if (!m_capture->available()) m_continuous->setToolTip(tr("Continuous capture is available on Windows. Pad mode remains available."));
    layout->addWidget(m_continuous);
    auto* form = new QFormLayout;
    const auto spin = [this](double low, double high, double value, const QString& suffix) {
        auto* control = new QDoubleSpinBox(this);
        control->setRange(low, high);
        control->setDecimals(2);
        control->setValue(value);
        control->setSuffix(suffix);
        return control;
    };
    m_scale = spin(0.01, 1.0, 0.15, tr(" mm/pixel"));
    m_scale->setObjectName(QStringLiteral("mouseJogSensitivity"));
    m_zStep = spin(0.25, 2.0, 1.0, tr(" mm/notch"));
    auto* speed = spin(10, 150, 100, tr(" mm/s"));
    const auto updateScaleUnits = [this]() {
        m_scale->setSuffix(m_continuous->isChecked() ? tr(" mm/count") : tr(" mm/pixel"));
        m_scale->setToolTip(m_continuous->isChecked()
            ? tr("Raw mouse counts are independent of screen edges and Windows pointer acceleration. Travel depends on your mouse DPI.")
            : tr("At 0.15 mm/pixel, 100 cursor pixels requests 15 mm. Leaving the pad stops this mode."));
    };
    updateScaleUnits();
    connect(m_continuous, &QCheckBox::toggled, this, [this, updateScaleUnits]() { endDrag(); updateScaleUnits(); });
    form->addRow(tr("XY sensitivity"), m_scale);
    form->addRow(tr("Wheel Z step"), m_zStep);
    form->addRow(tr("Speed limit"), speed);
    connect(speed, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
            [this](double value) { m_controller->setSpeed(float(value)); });
    layout->addLayout(form);
    auto* pad = new QLabel(tr("Hold + move\n\nContinuous mode: keep moving without an edge limit\n"
                             "X: left / right    Y: down / up    Z: wheel"), this);
    pad->setObjectName(QStringLiteral("mouseJogPad"));
    pad->setAlignment(Qt::AlignCenter);
    pad->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    pad->setMinimumSize(300, 180);
    pad->setFocusPolicy(Qt::StrongFocus);
    pad->setCursor(Qt::CrossCursor);
    m_pad = pad;
    m_pad->installEventFilter(this);
    connect(m_capture, &RelativeMouseCapture::moved, this, [this](QPoint delta) {
        if (m_dragging && m_capture->active())
            m_controller->addInput(float(delta.x() * m_scale->value()), float(-delta.y() * m_scale->value()), 0);
    });
    connect(m_capture, &RelativeMouseCapture::released, this, &MouseJogDialog::endDrag);
    layout->addWidget(pad, 1);
    auto* status = new QLabel(this);
    status->setObjectName(QStringLiteral("mouseJogStatus"));
    status->setWordWrap(true);
    layout->addWidget(status);
    connect(m_controller, &MouseJogController::statusChanged, status, &QLabel::setText);
    connect(m_controller, &MouseJogController::statusChanged, this, [this]() {
        if (m_dragging && !m_controller->ready()) endDrag();
    });
    connect(m_capture, &RelativeMouseCapture::failed, this, [this, status](const QString& reason) {
        endDrag();
        status->setText(reason);
    });
    auto* remaining = new QLabel(tr("Remaining to mouse target: 0.00 mm"), this);
    remaining->setObjectName(QStringLiteral("mouseJogRemaining"));
    layout->addWidget(remaining);
    connect(m_controller, &MouseJogController::remainingDistanceChanged, this,
            [remaining](float distance) {
        remaining->setText(tr("Remaining to mouse target: %1 mm").arg(distance, 0, 'f', 2));
    });
    auto* metrics = new QLabel(tr("Queued: 0/2 | Motion + braking estimate: 0 ms"), this);
    metrics->setObjectName(QStringLiteral("mouseJogStreamMetrics"));
    layout->addWidget(metrics);
    connect(m_controller, &MouseJogController::streamMetricsChanged, this,
            [metrics](int count, double seconds) {
        metrics->setText(tr("Queued: %1/2 | Motion + braking estimate: %2 ms")
                         .arg(count).arg(qRound(seconds * 1000)));
    });
    auto* note = new QLabel(tr("Uses G90 and F/A/J/S/E motion settings. Home the robot first and "
        "clear its workspace. Keep holding until the target is reached. On release, "
        "up to two committed moves and a short braking tail finish; the unsent target is cancelled. "
        "Live prediction can aim up to 3 mm ahead of the mouse target and expires after 80 ms without input; "
        "stopping or reversing may overshoot before settling. "
        "A direction reversal can briefly continue along the old direction while braking. "
        "The queue aims for 250 ms including braking; the display is an estimate, not measured latency. "
        "Tracking cannot keep up if mapped mouse speed exceeds the speed limit. "
        "This control is not an emergency stop."), this);
    note->setWordWrap(true);
    layout->addWidget(note);
    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttons);
    QTimer::singleShot(0, this, [this]() {
        if (isVisible())
            m_controller->start();
    });
}

MouseJogDialog::~MouseJogDialog() { endDrag(); }

void MouseJogDialog::endDrag()
{
    m_dragging = false;
    m_capture->stop();
    m_controller->endHold();
}

bool MouseJogDialog::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != m_pad)
        return QDialog::eventFilter(watched, event);
    if (event->type() == QEvent::MouseButtonPress) {
        auto* mouse = static_cast<QMouseEvent*>(event);
        if (mouse->button() == Qt::LeftButton) {
            m_lastPoint = mouse->position();
            m_dragging = m_controller->beginHold();
            if (m_dragging && m_continuous->isChecked() && !m_capture->start(m_pad)) {
                endDrag();
                findChild<QLabel*>(QStringLiteral("mouseJogStatus"))->setText(
                    tr("Could not capture the mouse. Uncheck continuous capture to use pad mode."));
            }
            return true;
        }
    } else if (event->type() == QEvent::MouseMove && m_dragging) {
        auto* mouse = static_cast<QMouseEvent*>(event);
        if (!(mouse->buttons() & Qt::LeftButton)) {
            endDrag();
        } else if (m_capture->active()) {
            // Raw input is authoritative; do not count the legacy move twice.
            return true;
        } else if (!m_pad->rect().contains(mouse->position().toPoint())) {
            endDrag();
        } else {
            const QPointF delta = mouse->position() - m_lastPoint;
            m_lastPoint = mouse->position();
            m_controller->addInput(float(delta.x() * m_scale->value()),
                                   float(-delta.y() * m_scale->value()), 0);
        }
        return true;
    } else if (event->type() == QEvent::Wheel) {
        auto* wheel = static_cast<QWheelEvent*>(event);
        // Windows can report NoButton for wheel events while the pad owns an
        // explicit mouse grab. m_dragging already proves that a valid hold is
        // active and is cleared on release, focus loss, Esc and capture faults.
        if (m_dragging)
            m_controller->addInput(0, 0, float(wheel->angleDelta().y() / 120.0 * m_zStep->value()));
        event->accept();
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease ||
               (event->type() == QEvent::Leave && !m_capture->active()) ||
               event->type() == QEvent::UngrabMouse) {
        endDrag();
    }
    return QDialog::eventFilter(watched, event);
}

bool MouseJogDialog::event(QEvent* event)
{
    if (event->type() == QEvent::WindowDeactivate) {
        endDrag();
    }
    return QDialog::event(event);
}

void MouseJogDialog::done(int result)
{
    endDrag();
    m_controller->shutdown();
    QDialog::done(result);
}
