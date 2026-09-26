#pragma once

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QLockFile>
#include <QJsonObject>
#include <memory>

// Local, same-user transport. One request per connection; a run streams replies.
class CliServer : public QObject
{
    Q_OBJECT
public:
    explicit CliServer(QObject* parent = nullptr);
    ~CliServer() override;
    bool listen(const QString& name, QString* error);
    static void reply(QLocalSocket* socket, const QJsonObject& message, bool final = false);
signals:
    void requestReceived(QLocalSocket* socket, QJsonObject request);
private:
    QLocalServer m_server;
    std::unique_ptr<QLockFile> m_lock;
    int m_connections = 0;
};
