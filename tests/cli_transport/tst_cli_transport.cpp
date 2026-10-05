#include <QtTest>
#include <QUuid>
#include "CliServer.h"
#include "CliProtocol.h"

class CliTransportTest : public QObject
{
    Q_OBJECT
private slots:
    void fragmentedRequestAndStreamingReplies()
    {
        CliServer server;
        const QString name = "deltax-test-" + QUuid::createUuid().toString(QUuid::WithoutBraces);
        QString error;
        QVERIFY2(server.listen(name, &error), qPrintable(error));
        int dispatched = 0;
        connect(&server, &CliServer::requestReceived, &server,
                [&](QLocalSocket* peer, QJsonObject request) {
            ++dispatched;
            QCOMPARE(request.value("source").toString(), QString("#a = 1\n#a = #a + 1"));
            CliServer::reply(peer, {{"event", "accepted"}});
            CliServer::reply(peer, {{"event", "finished"}, {"success", true}}, true);
        });
        QLocalSocket client;
        client.connectToServer(name);
        QTRY_COMPARE(client.state(), QLocalSocket::ConnectedState);
        const QByteArray wire = CliProtocol::encode({{"version", 1}, {"command", "run"},
                                                     {"source", "#a = 1\n#a = #a + 1"}});
        client.write(wire.left(10));
        QTest::qWait(20);
        QCOMPARE(dispatched, 0);
        client.write(wire.mid(10));
        QTRY_COMPARE(dispatched, 1);
        QTRY_VERIFY(client.canReadLine());
        QCOMPARE(QJsonDocument::fromJson(client.readLine()).object().value("event").toString(), "accepted");
        QTRY_VERIFY(client.canReadLine());
        QVERIFY(QJsonDocument::fromJson(client.readLine()).object().value("success").toBool());
    }
    void invalidRequestsNeverDispatch_data()
    {
        QTest::addColumn<QByteArray>("wire");
        QTest::newRow("malformed") << QByteArray("not json\n");
        QTest::newRow("version") << QByteArray("{\"version\":2}\n");
        QTest::newRow("batch") << QByteArray("{\"version\":1}\n{\"version\":1}\n");
        QTest::newRow("too-large") << QByteArray(CliProtocol::MaxMessageBytes + 1, 'x');
    }
    void invalidRequestsNeverDispatch()
    {
        QFETCH(QByteArray, wire);
        CliServer server;
        const QString name = "deltax-test-" + QUuid::createUuid().toString(QUuid::WithoutBraces);
        QString error;
        QVERIFY(server.listen(name, &error));
        int dispatched = 0;
        connect(&server, &CliServer::requestReceived, &server, [&]() { ++dispatched; });
        QLocalSocket client;
        client.connectToServer(name);
        QTRY_COMPARE(client.state(), QLocalSocket::ConnectedState);
        client.write(wire);
        QTRY_VERIFY(client.canReadLine());
        QCOMPARE(QJsonDocument::fromJson(client.readLine()).object().value("event").toString(), "error");
        QCOMPARE(dispatched, 0);
    }
    void secondInstanceCannotReplaceFirst()
    {
        const QString name = "deltax-test-" + QUuid::createUuid().toString(QUuid::WithoutBraces);
        QString error;
        {
            CliServer first, second;
            QVERIFY(first.listen(name, &error));
            QVERIFY(!second.listen(name, &error));
            QLocalSocket client;
            client.connectToServer(name);
            QTRY_COMPARE(client.state(), QLocalSocket::ConnectedState);
        }
        CliServer restarted;
        QVERIFY2(restarted.listen(name, &error), qPrintable(error));
    }
};
QTEST_GUILESS_MAIN(CliTransportTest)
#include "tst_cli_transport.moc"
