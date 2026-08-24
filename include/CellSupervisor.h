#ifndef CELLSUPERVISOR_H
#define CELLSUPERVISOR_H

#include <QObject>
#include <QSet>

class CellSupervisor final : public QObject
{
    Q_OBJECT
public:
    enum class State {
        Offline,
        Manual,
        Ready,
        AutoRunning,
        Paused,
        Faulted,
        Recovering
    };
    Q_ENUM(State)

    explicit CellSupervisor(QObject* parent = nullptr);

    State state() const;
    QString stateName() const;
    QString faultReason() const;
    QStringList activeOwners() const;
    bool automationAllowed() const;

public slots:
    bool BeginAutomation(const QString& owner);
    void EndAutomation(const QString& owner);
    void ReportFault(const QString& reason);
    void RequestPause(const QString& reason = QString());
    void ResetFault();
    void SetManualMode();
    void SetReady();

signals:
    void StateChanged(CellSupervisor::State state, QString stateName, QString reason);
    void ActiveOwnersChanged(QStringList owners);
    void ControlledStopRequested(QString reason);
    void AutomationRejected(QString owner, QString reason);

private:
    void setState(State state, const QString& reason = QString());

    State m_state = State::Ready;
    QString m_faultReason;
    QSet<QString> m_activeOwners;
};

Q_DECLARE_METATYPE(CellSupervisor::State)

#endif // CELLSUPERVISOR_H
