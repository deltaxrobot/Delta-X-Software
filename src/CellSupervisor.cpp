#include "CellSupervisor.h"

#include <QMetaEnum>
#include <QTimer>

CellSupervisor::CellSupervisor(QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<CellSupervisor::State>("CellSupervisor::State");
}

CellSupervisor::State CellSupervisor::state() const
{
    return m_state;
}

QString CellSupervisor::stateName() const
{
    const QMetaEnum meta = QMetaEnum::fromType<CellSupervisor::State>();
    return QString::fromLatin1(meta.valueToKey(static_cast<int>(m_state)));
}

QString CellSupervisor::faultReason() const
{
    return m_faultReason;
}

QStringList CellSupervisor::activeOwners() const
{
    QStringList owners = m_activeOwners.values();
    owners.sort();
    return owners;
}

bool CellSupervisor::automationAllowed() const
{
    return m_state != State::Faulted && m_state != State::Offline &&
           m_state != State::Recovering;
}

bool CellSupervisor::BeginAutomation(const QString& owner)
{
    const QString normalizedOwner = owner.trimmed();
    if (normalizedOwner.isEmpty())
        return false;
    if (!automationAllowed()) {
        emit AutomationRejected(normalizedOwner,
                                QStringLiteral("Cell state %1 does not allow AUTO")
                                    .arg(stateName()));
        return false;
    }

    const bool inserted = !m_activeOwners.contains(normalizedOwner);
    m_activeOwners.insert(normalizedOwner);
    if (inserted)
        emit ActiveOwnersChanged(activeOwners());
    setState(State::AutoRunning);
    return true;
}

void CellSupervisor::EndAutomation(const QString& owner)
{
    if (m_activeOwners.remove(owner.trimmed()))
        emit ActiveOwnersChanged(activeOwners());
    if (m_activeOwners.isEmpty() && m_state == State::AutoRunning)
        setState(State::Ready);
}

void CellSupervisor::ReportFault(const QString& reason)
{
    const QString fault = reason.trimmed().isEmpty()
        ? QStringLiteral("Unspecified automation fault") : reason.trimmed();
    const bool alreadyFaulted = m_state == State::Faulted;
    m_faultReason = fault;
    setState(State::Faulted, fault);
    if (!alreadyFaulted)
        emit ControlledStopRequested(fault);
}

void CellSupervisor::RequestPause(const QString& reason)
{
    if (m_state != State::AutoRunning)
        return;
    setState(State::Paused, reason.trimmed().isEmpty()
                           ? QStringLiteral("Cell paused") : reason.trimmed());
    emit ControlledStopRequested(reason.trimmed().isEmpty()
                                 ? QStringLiteral("Cell paused") : reason.trimmed());
}

void CellSupervisor::ResetFault()
{
    if (m_state != State::Faulted || !m_activeOwners.isEmpty())
        return;
    m_faultReason.clear();
    setState(State::Recovering, QStringLiteral("Operator acknowledged software fault"));
    QTimer::singleShot(0, this, [this]() {
        if (m_state == State::Recovering)
            setState(State::Ready);
    });
}

void CellSupervisor::SetManualMode()
{
    if (!m_activeOwners.isEmpty() || m_state == State::Faulted)
        return;
    setState(State::Manual);
}

void CellSupervisor::SetReady()
{
    if (!m_activeOwners.isEmpty() || m_state == State::Faulted)
        return;
    setState(State::Ready);
}

void CellSupervisor::setState(State state, const QString& reason)
{
    if (m_state == state && reason.isEmpty())
        return;
    m_state = state;
    emit StateChanged(m_state, stateName(), reason);
}
