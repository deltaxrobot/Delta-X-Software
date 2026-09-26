#pragma once
#include <QImage>
#include <QSslConfiguration>
#include <QTcpServer>
#include <QTimer>

// Lives on the camera worker. One paired browser, one requested frame in flight.
class PhoneCameraServer : public QTcpServer
{
    Q_OBJECT
  public:
    explicit PhoneCameraServer(QObject* parent = nullptr);
    bool start(const QHostAddress& address, quint16 port, const QString& certificate,
               const QString& key, QString* error);
    void stop();
    QString pairingUrl() const;
    bool paired() const
    {
        return !m_client.isEmpty();
    }
    bool capturePending() const
    {
        return m_pending;
    }
    bool requestFrame(quint64 request, int tracking);
  signals:
    void statusChanged(QString status);
    void pairedChanged(bool paired);
    void frameReady(QImage image, quint64 request, int tracking);
    void frameFailed(quint64 request, int tracking, QString reason);

  protected:
    void incomingConnection(qintptr descriptor) override;

  private:
    void respond(class QSslSocket* socket, int status, const QByteArray& body,
                 const QByteArray& type = "application/json");
    void handle(class QSslSocket* socket, const QByteArray& header, const QByteArray& body);
    QSslConfiguration m_tls;
    QString m_token, m_client;
    quint64 m_sequence = 0, m_request = 0;
    int m_tracking = 0, m_connections = 0;
    bool m_pending = false;
    QTimer m_timeout, m_heartbeat;
};
