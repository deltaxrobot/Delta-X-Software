#include "RelativeMouseCapture.h"
#include <QApplication>
#include <QPointer>
#include <QVector>
#include <QWidget>
#ifdef Q_OS_WIN
#include <qt_windows.h>
#endif

struct RelativeMouseCapture::NativeState {
    QPointer<QWidget> pad;
#ifdef Q_OS_WIN
    HWND window = nullptr;
    RECT previousClip{}, clip{};
    bool registered = false, clipped = false;
    RAWINPUTDEVICE previousRegistration{};
    bool hadRegistration = false;
#endif
};

RelativeMouseCapture::RelativeMouseCapture(QObject* parent)
    : QObject(parent), m_native(std::make_unique<NativeState>()) {}
RelativeMouseCapture::~RelativeMouseCapture() { stop(); }

bool RelativeMouseCapture::available() const
{
#ifdef Q_OS_WIN
    return QApplication::platformName() == QStringLiteral("windows");
#else
    return false;
#endif
}
bool RelativeMouseCapture::start(QWidget* pad)
{
    if (!available() || !pad || !pad->isVisible()) return false;
    stop();
#ifdef Q_OS_WIN
    auto& state = *m_native;
    state.window = reinterpret_cast<HWND>(pad->window()->winId());
    if (GetForegroundWindow() != state.window) return false;
    UINT count = 0;
    if (GetRegisteredRawInputDevices(nullptr, &count, sizeof(RAWINPUTDEVICE)) == UINT(-1)) return false;
    QVector<RAWINPUTDEVICE> registrations(count);
    if (count && GetRegisteredRawInputDevices(registrations.data(), &count, sizeof(RAWINPUTDEVICE)) == UINT(-1))
        return false;
    state.hadRegistration = false;
    for (const auto& device : registrations) {
        if (device.usUsagePage == 1 && device.usUsage == 2) {
            state.previousRegistration = device;
            state.hadRegistration = true;
        }
    }
    if (!GetClipCursor(&state.previousClip)) return false;
    const RAWINPUTDEVICE mouse{1, 2, 0, state.window}; // Foreground only; retain Qt button/wheel events.
    if (!RegisterRawInputDevices(&mouse, 1, sizeof(mouse))) return false;
    state.registered = true;
    state.pad = pad;
    // Use native screen coordinates, independent of Qt's high-DPI scaling.
    POINT center;
    if (!GetCursorPos(&center)) { stop(); return false; }
    state.clip = {center.x, center.y, center.x + 1, center.y + 1};
    if (!ClipCursor(&state.clip)) { stop(); return false; }
    state.clipped = true;
    m_active = true;
    qApp->installNativeEventFilter(this);
    pad->grabMouse(Qt::BlankCursor);
    if (QWidget::mouseGrabber() != pad) { stop(); return false; }
    return true;
#else
    return false;
#endif
}
void RelativeMouseCapture::stop()
{
    m_active = false;
    if (qApp) qApp->removeNativeEventFilter(this);
#ifdef Q_OS_WIN
    auto& state = *m_native;
    if (state.registered) {
        RAWINPUTDEVICE device = state.hadRegistration ? state.previousRegistration : RAWINPUTDEVICE{1, 2, RIDEV_REMOVE, nullptr};
        RegisterRawInputDevices(&device, 1, sizeof(device));
        state.registered = false;
    }
    if (state.clipped) {
        RECT current;
        if (GetClipCursor(&current) && EqualRect(&current, &state.clip))
            if (!ClipCursor(&state.previousClip)) ClipCursor(nullptr);
        state.clipped = false;
    }
    const auto pad = state.pad;
    state.pad = nullptr;
    state.window = nullptr;
    if (pad && QWidget::mouseGrabber() == pad) pad->releaseMouse();
#endif
}
bool RelativeMouseCapture::nativeEventFilter(const QByteArray& type, void* message, qintptr*)
{
#ifdef Q_OS_WIN
    if (!m_active || (type != "windows_generic_MSG" && type != "windows_dispatcher_MSG")) return false;
    auto* msg = static_cast<MSG*>(message);
    if (msg->message != WM_INPUT || msg->hwnd != m_native->window) return false;
    if (GetForegroundWindow() != m_native->window || !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
        stop();
        emit released();
        return false;
    }
    RAWINPUT input{};
    UINT bytes = sizeof(input);
    const UINT read = GetRawInputData(reinterpret_cast<HRAWINPUT>(msg->lParam), RID_INPUT,
                                     &input, &bytes, sizeof(RAWINPUTHEADER));
    if (read == UINT(-1) || read < sizeof(RAWINPUTHEADER) + sizeof(RAWMOUSE) || input.header.dwType != RIM_TYPEMOUSE)
        return false;
    if (input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) {
        stop(); emit released();
    } else if (input.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) {
        stop(); emit failed(tr("This pointer uses absolute coordinates. Turn off continuous capture to use pad mode."));
    } else if (input.data.mouse.lLastX || input.data.mouse.lLastY) {
        emit moved(QPoint(input.data.mouse.lLastX, input.data.mouse.lLastY));
    }
    // Let Qt/DefWindowProc perform WM_INPUT cleanup and deliver legacy buttons.
#else
    Q_UNUSED(type)
    Q_UNUSED(message)
#endif
    return false;
}
