#include "VirtualSerialPort.h"

#include <QDebug>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <util.h>

VirtualSerialPort::VirtualSerialPort(const QString &deviceName, QObject *parent)
    : QObject(parent)
    , m_deviceName(deviceName)
{
}

VirtualSerialPort::~VirtualSerialPort()
{
    stop();
}

void VirtualSerialPort::setLineHandler(LineHandler handler)
{
    m_handler = std::move(handler);
}

bool VirtualSerialPort::start()
{
    if (isOpen())
        return true;

    char slaveNameBuffer[256] = {0};
    if (openpty(&m_masterFd, &m_slaveFd, slaveNameBuffer, nullptr, nullptr) != 0) {
        emit logMessage(QString("[%1][serial] failed to create PTY pair").arg(m_deviceName));
        m_masterFd = -1;
        m_slaveFd = -1;
        return false;
    }

    termios options;
    if (tcgetattr(m_slaveFd, &options) == 0) {
        cfmakeraw(&options);
        tcsetattr(m_slaveFd, TCSANOW, &options);
    }

    const int flags = fcntl(m_masterFd, F_GETFL, 0);
    if (flags >= 0)
        fcntl(m_masterFd, F_SETFL, flags | O_NONBLOCK);

    m_slavePath = QString::fromLocal8Bit(slaveNameBuffer);
    m_notifier = new QSocketNotifier(m_masterFd, QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated, this, &VirtualSerialPort::handleReadyRead);

    emit logMessage(QString("[%1][serial] ready at %2").arg(m_deviceName, m_slavePath));
    return true;
}

void VirtualSerialPort::stop()
{
    if (m_notifier) {
        m_notifier->deleteLater();
        m_notifier = nullptr;
    }

    if (m_masterFd >= 0) {
        ::close(m_masterFd);
        m_masterFd = -1;
    }

    if (m_slaveFd >= 0) {
        ::close(m_slaveFd);
        m_slaveFd = -1;
    }

    if (!m_slavePath.isEmpty()) {
        emit logMessage(QString("[%1][serial] stopped (%2)").arg(m_deviceName, m_slavePath));
        m_slavePath.clear();
    }

    m_buffer.clear();
}

QString VirtualSerialPort::deviceName() const
{
    return m_deviceName;
}

QString VirtualSerialPort::slavePath() const
{
    return m_slavePath;
}

bool VirtualSerialPort::isOpen() const
{
    return m_masterFd >= 0 && m_slaveFd >= 0 && !m_slavePath.isEmpty();
}

void VirtualSerialPort::handleReadyRead()
{
    if (m_masterFd < 0)
        return;

    char buffer[1024];
    const ssize_t bytesRead = ::read(m_masterFd, buffer, sizeof(buffer));
    if (bytesRead <= 0)
        return;

    m_buffer.append(buffer, static_cast<int>(bytesRead));

    int newlineIndex = -1;
    while ((newlineIndex = m_buffer.indexOf('\n')) != -1) {
        QByteArray rawLine = m_buffer.left(newlineIndex);
        m_buffer.remove(0, newlineIndex + 1);

        QString line = QString::fromUtf8(rawLine).trimmed();
        if (line.isEmpty())
            continue;

        emit logMessage(QString("[%1][serial] <= %2").arg(m_deviceName, line));
        const ResponseSender respond = [this](const QString &response) {
            if (response.isEmpty())
                return;
            sendLine(response);
        };
        if (m_handler) {
            m_handler(line, respond);
        } else {
            respond(QStringLiteral("Ok"));
        }
    }
}

void VirtualSerialPort::sendLine(const QString &line)
{
    if (m_masterFd < 0)
        return;

    QByteArray payload = line.toUtf8();
    payload.append('\n');
    ::write(m_masterFd, payload.constData(), static_cast<size_t>(payload.size()));
    emit logMessage(QString("[%1][serial] => %2").arg(m_deviceName, line));
}
