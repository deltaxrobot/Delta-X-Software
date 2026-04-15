#ifndef VIRTUALSERIALPORT_H
#define VIRTUALSERIALPORT_H

#include <QObject>
#include <QSocketNotifier>
#include <functional>

class VirtualSerialPort : public QObject
{
    Q_OBJECT

public:
    using ResponseSender = std::function<void(const QString &)>;
    using LineHandler = std::function<void(const QString &, ResponseSender)>;

    explicit VirtualSerialPort(const QString &deviceName, QObject *parent = nullptr);
    ~VirtualSerialPort() override;

    void setLineHandler(LineHandler handler);
    bool start();
    void stop();

    QString deviceName() const;
    QString slavePath() const;
    bool isOpen() const;

signals:
    void logMessage(const QString &message);

private slots:
    void handleReadyRead();

private:
    void sendLine(const QString &line);

    QString m_deviceName;
    QString m_slavePath;
    int m_masterFd = -1;
    int m_slaveFd = -1;
    QSocketNotifier *m_notifier = nullptr;
    QByteArray m_buffer;
    LineHandler m_handler;
};

#endif // VIRTUALSERIALPORT_H
