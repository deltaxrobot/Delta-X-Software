#ifndef DEVICECOMMANDBROKER_H
#define DEVICECOMMANDBROKER_H

#include <QObject>
#include <QHash>
#include <QQueue>
#include <QSet>
#include <QTimer>

class DeviceCommandBroker final : public QObject
{
    Q_OBJECT
public:
    enum class Origin {
        Manual,
        GScript,
        Tracking,
        Plugin,
        Remote,
        Safety
    };
    Q_ENUM(Origin)

    explicit DeviceCommandBroker(QObject* parent = nullptr);

    QString cellState() const;
    int pendingCommandCount(const QString& deviceId = QString()) const;
    bool hasActiveCommand(const QString& deviceId) const;

public slots:
    quint64 Submit(const QString& owner, const QString& deviceId,
                   const QString& command, DeviceCommandBroker::Origin origin,
                   bool waitForResponse = true, int timeoutMs = 120000);
    void HandleDeviceResponse(const QString& deviceId, const QString& response);
    void CancelOwner(const QString& owner, const QString& reason = QString());
    void SetCellState(const QString& state);
    void RegisterDevice(const QString& deviceId);
    void RequestControlledStop(const QString& reason);

signals:
    void DispatchCommand(QString deviceId, QString command);
    void ResponseForOwner(QString owner, QString deviceId, QString response,
                          quint64 requestId);
    void CommandRejected(QString owner, QString deviceId, QString command,
                         QString reason);
    void CommandDispatched(quint64 requestId, QString owner, QString deviceId,
                           QString command, DeviceCommandBroker::Origin origin);
    void CommandTimedOut(quint64 requestId, QString owner, QString deviceId,
                         QString command);
    void UnsolicitedResponse(QString deviceId, QString response);
    void QueueDepthChanged(QString deviceId, int depth);

private:
    struct PendingCommand {
        quint64 requestId = 0;
        QString owner;
        QString deviceId;
        QString command;
        Origin origin = Origin::Manual;
        bool waitForResponse = true;
        qint64 deadlineMs = 0;
    };

    QString normalizeDevice(const QString& deviceId) const;
    bool canSubmit(const PendingCommand& command, QString& reason) const;
    bool isStopCommand(const QString& deviceId, const QString& command) const;
    void submitSafetyCommand(PendingCommand command);
    void dispatchNext(const QString& deviceId);
    void rejectCommand(const PendingCommand& command, const QString& reason);
    void expireCommands();
    QStringList safeStopCommands(const QString& deviceId) const;

    QHash<QString, QQueue<PendingCommand>> m_queues;
    QHash<QString, PendingCommand> m_activeCommands;
    QSet<QString> m_knownDevices;
    QTimer m_timeoutTimer;
    QString m_cellState = QStringLiteral("Ready");
    quint64 m_nextRequestId = 1;
};

Q_DECLARE_METATYPE(DeviceCommandBroker::Origin)

#endif // DEVICECOMMANDBROKER_H
