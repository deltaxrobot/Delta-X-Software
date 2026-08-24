#include "DeviceCommandBroker.h"

#include <QDateTime>
#include <QRegularExpression>

DeviceCommandBroker::DeviceCommandBroker(QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<DeviceCommandBroker::Origin>("DeviceCommandBroker::Origin");
    m_timeoutTimer.setInterval(50);
    m_timeoutTimer.setTimerType(Qt::CoarseTimer);
    connect(&m_timeoutTimer, &QTimer::timeout,
            this, &DeviceCommandBroker::expireCommands);
    m_timeoutTimer.start();
}

QString DeviceCommandBroker::cellState() const
{
    return m_cellState;
}

int DeviceCommandBroker::pendingCommandCount(const QString& deviceId) const
{
    if (!deviceId.trimmed().isEmpty()) {
        const QString device = normalizeDevice(deviceId);
        return m_queues.value(device).size() + (m_activeCommands.contains(device) ? 1 : 0);
    }

    int count = m_activeCommands.size();
    for (auto it = m_queues.cbegin(); it != m_queues.cend(); ++it)
        count += it.value().size();
    return count;
}

bool DeviceCommandBroker::hasActiveCommand(const QString& deviceId) const
{
    return m_activeCommands.contains(normalizeDevice(deviceId));
}

QString DeviceCommandBroker::normalizeDevice(const QString& deviceId) const
{
    return deviceId.trimmed().toLower();
}

bool DeviceCommandBroker::isStopCommand(const QString& deviceId,
                                        const QString& command) const
{
    const QString device = normalizeDevice(deviceId);
    const QString text = command.simplified().toUpper();
    if (device.startsWith(QStringLiteral("robot")))
        return text == QStringLiteral("M84") || text == QStringLiteral("M112") ||
               text == QStringLiteral("M410");
    if (device.startsWith(QStringLiteral("slider")))
        return text == QStringLiteral("M323");
    if (device.startsWith(QStringLiteral("conveyor"))) {
        static const QRegularExpression stopPattern(
            QStringLiteral("^M(311|313)\\s+[-+]?0(?:\\.0+)?$|^M40[12]\\s+C\\d+:0(?:\\.0+)?$"),
            QRegularExpression::CaseInsensitiveOption);
        return stopPattern.match(text).hasMatch();
    }
    return false;
}

bool DeviceCommandBroker::canSubmit(const PendingCommand& command,
                                    QString& reason) const
{
    if (command.deviceId.isEmpty() || command.command.trimmed().isEmpty()) {
        reason = QStringLiteral("Device and command are required");
        return false;
    }

    if (command.origin == Origin::Safety)
        return true;

    if (m_cellState.compare(QStringLiteral("Faulted"), Qt::CaseInsensitive) == 0) {
        reason = QStringLiteral("Cell is Faulted; only safety commands are accepted");
        return false;
    }

    const bool automationActive =
        m_cellState.compare(QStringLiteral("AutoRunning"), Qt::CaseInsensitive) == 0 ||
        m_cellState.compare(QStringLiteral("Paused"), Qt::CaseInsensitive) == 0;
    if (automationActive &&
        (command.origin == Origin::Manual || command.origin == Origin::Remote)) {
        reason = QStringLiteral("Manual/remote commands are blocked while the cell is in AUTO");
        return false;
    }

    if ((command.origin == Origin::Manual || command.origin == Origin::Remote) &&
        (m_activeCommands.contains(command.deviceId) ||
         !m_queues.value(command.deviceId).isEmpty())) {
        reason = QStringLiteral("Device is reserved by an automation command");
        return false;
    }

    return true;
}

quint64 DeviceCommandBroker::Submit(const QString& owner, const QString& deviceId,
                                    const QString& command, Origin origin,
                                    bool waitForResponse, int timeoutMs)
{
    PendingCommand pending;
    pending.requestId = m_nextRequestId++;
    pending.owner = owner.trimmed();
    pending.deviceId = normalizeDevice(deviceId);
    pending.command = command.trimmed();
    pending.origin = origin;
    pending.waitForResponse = waitForResponse;
    pending.deadlineMs = QDateTime::currentMSecsSinceEpoch() + qBound(10, timeoutMs, 86400000);

    // A stop emitted by the current automation owner is a preemptive safety
    // operation, not another command to place behind the motion being stopped.
    if (isStopCommand(pending.deviceId, pending.command)) {
        const auto active = m_activeCommands.constFind(pending.deviceId);
        if (origin == Origin::Safety || origin == Origin::Manual ||
            (active != m_activeCommands.cend() && active->owner == pending.owner)) {
            pending.origin = Origin::Safety;
            pending.waitForResponse = false;
        }
    }

    QString rejectionReason;
    if (!canSubmit(pending, rejectionReason)) {
        rejectCommand(pending, rejectionReason);
        return 0;
    }

    m_knownDevices.insert(pending.deviceId);
    if (pending.origin == Origin::Safety) {
        submitSafetyCommand(pending);
        return pending.requestId;
    }

    m_queues[pending.deviceId].enqueue(pending);
    emit QueueDepthChanged(pending.deviceId, pendingCommandCount(pending.deviceId));
    dispatchNext(pending.deviceId);
    return pending.requestId;
}

void DeviceCommandBroker::submitSafetyCommand(PendingCommand command)
{
    const QString device = command.deviceId;
    if (m_activeCommands.contains(device)) {
        const PendingCommand interrupted = m_activeCommands.take(device);
        emit ResponseForOwner(interrupted.owner, interrupted.deviceId,
                              QStringLiteral("error: command preempted by safety stop"),
                              interrupted.requestId);
    }

    QQueue<PendingCommand>& queue = m_queues[device];
    while (!queue.isEmpty())
        rejectCommand(queue.dequeue(), QStringLiteral("Cancelled by safety stop"));

    emit DispatchCommand(device, command.command);
    emit CommandDispatched(command.requestId, command.owner, device,
                           command.command, command.origin);
    emit QueueDepthChanged(device, 0);
}

void DeviceCommandBroker::dispatchNext(const QString& deviceId)
{
    const QString device = normalizeDevice(deviceId);
    if (m_activeCommands.contains(device))
        return;

    QQueue<PendingCommand>& queue = m_queues[device];
    while (!queue.isEmpty()) {
        PendingCommand command = queue.dequeue();
        QString reason;
        if (!canSubmit(command, reason)) {
            rejectCommand(command, reason);
            continue;
        }

        emit DispatchCommand(device, command.command);
        emit CommandDispatched(command.requestId, command.owner, device,
                               command.command, command.origin);
        if (command.waitForResponse) {
            m_activeCommands.insert(device, command);
            emit QueueDepthChanged(device, pendingCommandCount(device));
            return;
        }
    }
    emit QueueDepthChanged(device, 0);
}

void DeviceCommandBroker::HandleDeviceResponse(const QString& deviceId,
                                               const QString& response)
{
    const QString device = normalizeDevice(deviceId);
    const auto active = m_activeCommands.find(device);
    if (active == m_activeCommands.end()) {
        emit UnsolicitedResponse(device, response);
        return;
    }

    const PendingCommand completed = active.value();
    m_activeCommands.erase(active);
    emit ResponseForOwner(completed.owner, device, response, completed.requestId);
    dispatchNext(device);
}

void DeviceCommandBroker::CancelOwner(const QString& owner, const QString& reason)
{
    const QString normalizedOwner = owner.trimmed();
    if (normalizedOwner.isEmpty())
        return;

    const QString rejection = reason.trimmed().isEmpty()
        ? QStringLiteral("Command owner stopped") : reason.trimmed();
    QStringList affectedDevices;

    for (auto it = m_activeCommands.begin(); it != m_activeCommands.end();) {
        if (it->owner == normalizedOwner) {
            affectedDevices.append(it.key());
            it = m_activeCommands.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = m_queues.begin(); it != m_queues.end(); ++it) {
        QQueue<PendingCommand> retained;
        while (!it.value().isEmpty()) {
            const PendingCommand command = it.value().dequeue();
            if (command.owner == normalizedOwner)
                rejectCommand(command, rejection);
            else
                retained.enqueue(command);
        }
        it.value() = retained;
        affectedDevices.append(it.key());
    }

    affectedDevices.removeDuplicates();
    for (const QString& device : affectedDevices)
        dispatchNext(device);
}

void DeviceCommandBroker::SetCellState(const QString& state)
{
    m_cellState = state.trimmed().isEmpty() ? QStringLiteral("Ready") : state.trimmed();
}

void DeviceCommandBroker::RegisterDevice(const QString& deviceId)
{
    const QString device = normalizeDevice(deviceId);
    if (!device.isEmpty())
        m_knownDevices.insert(device);
}

QStringList DeviceCommandBroker::safeStopCommands(const QString& deviceId) const
{
    if (deviceId.startsWith(QStringLiteral("robot")))
        return {QStringLiteral("M05"), QStringLiteral("M84")};
    if (deviceId.startsWith(QStringLiteral("conveyor")))
        return {QStringLiteral("M311 0"), QStringLiteral("M313 0"),
                QStringLiteral("M401 C1:0"), QStringLiteral("M401 C2:0"),
                QStringLiteral("M401 C3:0")};
    if (deviceId.startsWith(QStringLiteral("slider")))
        return {QStringLiteral("M323")};
    return {};
}

void DeviceCommandBroker::RequestControlledStop(const QString& reason)
{
    const QString stopReason = reason.trimmed().isEmpty()
        ? QStringLiteral("Controlled cell stop") : reason.trimmed();

    for (auto it = m_activeCommands.cbegin(); it != m_activeCommands.cend(); ++it) {
        emit ResponseForOwner(it->owner, it->deviceId,
                              QStringLiteral("error: %1").arg(stopReason),
                              it->requestId);
    }
    m_activeCommands.clear();

    for (auto it = m_queues.begin(); it != m_queues.end(); ++it) {
        while (!it.value().isEmpty())
            rejectCommand(it.value().dequeue(), stopReason);
        emit QueueDepthChanged(it.key(), 0);
    }

    QStringList devices = m_knownDevices.values();
    devices.sort();
    for (const QString& device : devices) {
        for (const QString& stopCommand : safeStopCommands(device)) {
            emit DispatchCommand(device, stopCommand);
            emit CommandDispatched(m_nextRequestId++, QStringLiteral("safety/cell"),
                                   device, stopCommand, Origin::Safety);
        }
    }
}

void DeviceCommandBroker::rejectCommand(const PendingCommand& command,
                                        const QString& reason)
{
    emit CommandRejected(command.owner, command.deviceId, command.command, reason);
}

void DeviceCommandBroker::expireCommands()
{
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    QStringList expiredDevices;
    for (auto it = m_activeCommands.begin(); it != m_activeCommands.end();) {
        if (it->deadlineMs <= now) {
            const PendingCommand command = it.value();
            expiredDevices.append(it.key());
            it = m_activeCommands.erase(it);
            emit CommandTimedOut(command.requestId, command.owner, command.deviceId,
                                 command.command);
            emit ResponseForOwner(command.owner, command.deviceId,
                                  QStringLiteral("error: command broker timeout"),
                                  command.requestId);
        } else {
            ++it;
        }
    }
    for (const QString& device : expiredDevices) {
        QQueue<PendingCommand>& queue = m_queues[device];
        while (!queue.isEmpty())
            rejectCommand(queue.dequeue(), QStringLiteral("Cancelled after device timeout"));
        emit QueueDepthChanged(device, 0);
    }
}
