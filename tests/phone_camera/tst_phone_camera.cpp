#include "PhoneCameraServer.h"
#include <QBuffer>
#include <QProcess>
#include <QSslSocket>
#include <QStandardPaths>
#include <QTemporaryDir>
#include <QUrl>
#include <QtTest>

class PhoneCameraTest : public QObject
{
    Q_OBJECT
    QTemporaryDir dir;
    QString cert, key;
    QByteArray exchange(PhoneCameraServer& server, QByteArray request)
    {
        QSslSocket client;
        client.setPeerVerifyMode(QSslSocket::VerifyNone);
        QEventLoop loop;
        QByteArray result;
        connect(&client, &QSslSocket::encrypted, &loop, [&] { client.write(request); });
        connect(&client, &QSslSocket::readyRead, &loop, [&] { result += client.readAll(); });
        connect(&client, &QSslSocket::disconnected, &loop, &QEventLoop::quit);
        QTimer::singleShot(6000, &loop, &QEventLoop::quit);
        client.connectToHostEncrypted("127.0.0.1", server.serverPort());
        loop.exec();
        return result;
    }
    QByteArray request(PhoneCameraServer& server, QByteArray method, QByteArray path,
                       QByteArray body = {}, QByteArray extra = {},
                       QByteArray client = "test-phone-0000001", bool auth = true)
    {
        const auto token = QUrl(server.pairingUrl()).fragment().toUtf8();
        return exchange(server,
                        method + " " + path + " HTTP/1.1\r\nHost: 127.0.0.1\r\n" +
                            (auth ? "Authorization: Bearer " + token + "\r\n" : QByteArray()) +
                            "X-Phone-Client: " + client + "\r\nContent-Length: " +
                            QByteArray::number(body.size()) + "\r\n" + extra + "\r\n" + body);
    }
    bool start(PhoneCameraServer& server)
    {
        QString error;
        bool ok = server.start(QHostAddress::LocalHost, 0, cert, key, &error);
        if (!ok)
            qWarning() << error;
        return ok;
    }
  private slots:
    void initTestCase()
    {
        QVERIFY(QSslSocket::supportsSsl());
        const auto openssl = QStandardPaths::findExecutable("openssl");
        if (openssl.isEmpty())
            QSKIP("OpenSSL executable needed to generate ephemeral TLS test credentials");
        cert = dir.filePath("test.crt");
        key = dir.filePath("test.key");
        QProcess process;
        process.start(openssl, {"req", "-x509", "-newkey", "rsa:2048", "-nodes", "-days", "1",
                                "-subj", "/CN=localhost", "-addext", "subjectAltName=IP:127.0.0.1",
                                "-keyout", key, "-out", cert});
        QVERIFY(process.waitForFinished(15000));
        QCOMPARE(process.exitCode(), 0);
    }
    void pairingAndAuthorizedPage()
    {
        PhoneCameraServer server;
        QVERIFY(start(server));
        const auto page = request(server, "GET", "/", {}, {}, "test-phone-0000001", false);
        QVERIFY(page.startsWith("HTTP/1.1 200"));
        QVERIFY(page.contains("getUserMedia"));
        QVERIFY(request(server, "POST", "/pair", {}, {}, "test-phone-0000001", false)
                    .startsWith("HTTP/1.1 401"));
        QVERIFY(!server.paired());
        QVERIFY(request(server, "POST", "/pair").startsWith("HTTP/1.1 200"));
        QVERIFY(server.paired());
        QVERIFY(request(server, "POST", "/pair", {}, {}, "another-phone-00001")
                    .startsWith("HTTP/1.1 409"));
        QVERIFY(request(server, "POST", "/stop").startsWith("HTTP/1.1 200"));
        QVERIFY(!server.paired());
    }
    void frameCorrelationAndLimits()
    {
        PhoneCameraServer server;
        QVERIFY(start(server));
        QVERIFY(request(server, "POST", "/pair").startsWith("HTTP/1.1 200"));
        QSignalSpy frames(&server, &PhoneCameraServer::frameReady);
        QVERIFY(server.requestFrame(73, 4));
        QVERIFY(!server.requestFrame(74, 5));
        QVERIFY(request(server, "GET", "/next").contains("\"sequence\":\"1\""));
        QImage image(320, 240, QImage::Format_RGB32);
        image.fill(Qt::red);
        QByteArray jpeg;
        QBuffer buffer(&jpeg);
        buffer.open(QIODevice::WriteOnly);
        QVERIFY(image.save(&buffer, "JPEG"));
        QVERIFY(request(server, "POST", "/frame", jpeg,
                        "Content-Type: image/jpeg\r\nX-Frame-Sequence: 0\r\n")
                    .startsWith("HTTP/1.1 409"));
        QCOMPARE(frames.count(), 0);
        QVERIFY(request(server, "POST", "/frame", jpeg,
                        "Content-Type: image/jpeg\r\nX-Frame-Sequence: 1\r\n")
                    .startsWith("HTTP/1.1 200"));
        QCOMPARE(frames.count(), 1);
        QCOMPARE(frames[0][1].toULongLong(), quint64(73));
        QCOMPARE(frames[0][2].toInt(), 4);
        QCOMPARE(qvariant_cast<QImage>(frames[0][0]).size(), QSize(320, 240));
        QVERIFY(request(server, "POST", "/frame", jpeg,
                        "Content-Type: image/jpeg\r\nX-Frame-Sequence: 1\r\n")
                    .startsWith("HTTP/1.1 409"));
        QVERIFY(exchange(server, "POST /frame HTTP/1.1\r\nContent-Length: 99999999\r\n\r\n")
                    .startsWith("HTTP/1.1 413"));
        QVERIFY(server.requestFrame(88, 5));
        QSignalSpy failed(&server, &PhoneCameraServer::frameFailed);
        QTRY_COMPARE_WITH_TIMEOUT(failed.count(), 1, 4500);
        QCOMPARE(failed[0][0].toULongLong(), quint64(88));
        QVERIFY(request(server, "POST", "/frame", jpeg,
                        "Content-Type: image/jpeg\r\nX-Frame-Sequence: 2\r\n")
                    .startsWith("HTTP/1.1 409"));
    }
    void heartbeatDisconnectsMissingPhone()
    {
        PhoneCameraServer server;
        QVERIFY(start(server));
        QVERIFY(request(server, "POST", "/pair").startsWith("HTTP/1.1 200"));
        QSignalSpy paired(&server, &PhoneCameraServer::pairedChanged);
        QTRY_VERIFY_WITH_TIMEOUT(!server.paired(), 7500);
        QCOMPARE(paired.count(), 1);
        QCOMPARE(paired[0][0].toBool(), false);
        QVERIFY(!server.requestFrame(1, 0));
    }
    void invalidFramesAndHeaders()
    {
        PhoneCameraServer server;
        QVERIFY(start(server));
        QVERIFY(request(server, "POST", "/pair").startsWith("HTTP/1.1 200"));
        QVERIFY(server.requestFrame(1, 0));
        QSignalSpy frames(&server, &PhoneCameraServer::frameReady);
        QVERIFY(request(server, "POST", "/frame", "not jpeg",
                        "Content-Type: image/jpeg\r\nX-Frame-Sequence: 1\r\n")
                    .startsWith("HTTP/1.1 415"));
        QImage big(1921, 2, QImage::Format_RGB32);
        big.fill(Qt::red);
        QByteArray jpeg;
        QBuffer buffer(&jpeg);
        buffer.open(QIODevice::WriteOnly);
        QVERIFY(big.save(&buffer, "JPEG"));
        QVERIFY(request(server, "POST", "/frame", jpeg,
                        "Content-Type: image/jpeg\r\nX-Frame-Sequence: 1\r\n")
                    .startsWith("HTTP/1.1 413"));
        QVERIFY(exchange(server,
                         "POST /frame HTTP/1.1\r\nContent-Length: 0\r\nContent-Length: 1\r\n\r\n")
                    .startsWith("HTTP/1.1 413"));
        QVERIFY(exchange(server, "POST /frame HTTP/1.1\r\nTransfer-Encoding: chunked\r\n\r\n")
                    .startsWith("HTTP/1.1 400"));
        QCOMPARE(frames.count(), 0);
    }
    void stopRevokesSessionAndCredentialsFailCleanly()
    {
        PhoneCameraServer server;
        QVERIFY(start(server));
        const auto oldUrl = server.pairingUrl();
        QVERIFY(request(server, "POST", "/pair").startsWith("HTTP/1.1 200"));
        QVERIFY(server.requestFrame(9, 2));
        QSignalSpy failed(&server, &PhoneCameraServer::frameFailed);
        server.stop();
        QCOMPARE(failed.count(), 1);
        QVERIFY(server.pairingUrl().isEmpty());
        QVERIFY(!server.paired());
        QVERIFY(!server.isListening());
        QVERIFY(start(server));
        QVERIFY(oldUrl != server.pairingUrl());
        QString error;
        QVERIFY(!server.start(QHostAddress::LocalHost, 0, "missing", "missing", &error));
        QVERIFY(!error.isEmpty());
        QVERIFY(!server.start(QHostAddress("192.0.2.1"), 0, cert, key, &error));
        QVERIFY(error.contains("network IP"));
    }
};
QTEST_GUILESS_MAIN(PhoneCameraTest)
#include "tst_phone_camera.moc"
