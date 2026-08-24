#include <QtTest>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>

#include "SocketConnectionManager.h"

namespace {
QByteArray framed(const QJsonObject& object)
{
    const QByteArray payload = QJsonDocument(object).toJson(QJsonDocument::Compact);
    return "DXV1 " + QByteArray::number(payload.size()) + "\n" + payload;
}

QJsonObject detections(quint64 frameId, quint64 requestId, int trackingId)
{
    QJsonObject item;
    item.insert("type", 2);
    item.insert("x", 12.5);
    item.insert("y", 31.25);
    item.insert("w", 10.0);
    item.insert("h", 20.0);
    item.insert("angle", 45.0);
    item.insert("confidence", 0.93);
    item.insert("label", "product-A");
    item.insert("externalId", "det-7");

    QJsonObject root;
    root.insert("type", "objects");
    root.insert("coordinateSpace", "image");
    root.insert("frameId", QString::number(frameId));
    root.insert("requestId", QString::number(requestId));
    root.insert("trackingId", trackingId);
    root.insert("list", QJsonArray{item});
    return root;
}
}

class SocketVisionProtocolTest : public QObject
{
    Q_OBJECT

private slots:
    void splitPrefixAndPayloadAreReassembled();
    void coalescedFramesRemainSeparate();
    void framedMessageRequiresCorrelationMetadata();
    void outgoingFrameUsesCorrelatedDxv1();
    void frameSendFailsWithoutDetector();
    void secondDetectorIsRejected();
    void legacyRemoteExecutionIsDisabledByDefault();
};

void SocketVisionProtocolTest::splitPrefixAndPayloadAreReassembled()
{
    SocketConnectionManager manager("127.0.0.1", 0);
    QVERIFY(manager.Server->isListening());
    QSignalSpy spy(&manager, &SocketConnectionManager::externalDetectionsReceived);

    QTcpSocket client;
    client.connectToHost(QHostAddress::LocalHost, manager.Server->serverPort());
    QVERIFY(client.waitForConnected(2000));
    QTRY_VERIFY(client.bytesAvailable() > 0);
    client.readAll();

    const QByteArray wire = QByteArray("ExternalScript\n") + framed(detections(41, 9001, 2));
    client.write(wire.left(3));
    QVERIFY(client.waitForBytesWritten(1000));
    QTest::qWait(10);
    QCOMPARE(spy.count(), 0);
    client.write(wire.mid(3, 11));
    QVERIFY(client.waitForBytesWritten(1000));
    client.write(wire.mid(14));
    QVERIFY(client.waitForBytesWritten(1000));

    QTRY_COMPARE_WITH_TIMEOUT(spy.count(), 1, 2000);
    const VisionDetections result = qvariant_cast<VisionDetections>(spy.takeFirst().at(0));
    QCOMPARE(result.frameId, quint64(41));
    QCOMPARE(result.requestId, quint64(9001));
    QCOMPARE(result.trackingId, 2);
    QCOMPARE(result.objects.size(), 1);
    QCOMPARE(result.objects.first().confidence, 0.93);
    QCOMPARE(result.objects.first().label, QStringLiteral("product-A"));
    QCOMPARE(result.objects.first().externalId, QStringLiteral("det-7"));
}

void SocketVisionProtocolTest::coalescedFramesRemainSeparate()
{
    SocketConnectionManager manager("127.0.0.1", 0);
    QSignalSpy spy(&manager, &SocketConnectionManager::externalDetectionsReceived);
    QTcpSocket client;
    client.connectToHost(QHostAddress::LocalHost, manager.Server->serverPort());
    QVERIFY(client.waitForConnected(2000));
    QTRY_VERIFY(client.bytesAvailable() > 0);
    client.readAll();

    client.write(framed(detections(51, 101, 0)) + framed(detections(52, 102, 0)));
    QVERIFY(client.waitForBytesWritten(1000));
    QTRY_COMPARE_WITH_TIMEOUT(spy.count(), 2, 2000);
    QCOMPARE(qvariant_cast<VisionDetections>(spy.at(0).at(0)).frameId, quint64(51));
    QCOMPARE(qvariant_cast<VisionDetections>(spy.at(1).at(0)).frameId, quint64(52));
}

void SocketVisionProtocolTest::framedMessageRequiresCorrelationMetadata()
{
    SocketConnectionManager manager("127.0.0.1", 0);
    QSignalSpy exactSpy(&manager, &SocketConnectionManager::externalDetectionsReceived);
    QSignalSpy legacySpy(&manager, &SocketConnectionManager::blobUpdated);
    QTcpSocket client;
    client.connectToHost(QHostAddress::LocalHost, manager.Server->serverPort());
    QVERIFY(client.waitForConnected(2000));
    QTRY_VERIFY(client.bytesAvailable() > 0);
    client.readAll();

    QJsonObject missingMetadata = detections(60, 200, 1);
    missingMetadata.remove("requestId");
    client.write(framed(missingMetadata));
    QVERIFY(client.waitForBytesWritten(1000));
    QTest::qWait(100);
    QCOMPARE(exactSpy.count(), 0);
    QCOMPARE(legacySpy.count(), 0);
}

void SocketVisionProtocolTest::outgoingFrameUsesCorrelatedDxv1()
{
    SocketConnectionManager manager("127.0.0.1", 0);
    QSignalSpy statusSpy(&manager, &SocketConnectionManager::externalVisionStatusChanged);
    QSignalSpy sentSpy(&manager, &SocketConnectionManager::externalVisionFrameSent);
    QTcpSocket client;
    client.connectToHost(QHostAddress::LocalHost, manager.Server->serverPort());
    QVERIFY(client.waitForConnected(2000));
    QTRY_VERIFY(client.bytesAvailable() > 0);
    client.readAll();
    client.write("ExternalVision DXV1\n");
    QVERIFY(client.waitForBytesWritten(1000));
    QTRY_COMPARE_WITH_TIMEOUT(statusSpy.count(), 1, 2000);

    VisionFrame frame;
    frame.frameId = 81;
    frame.requestId = 7001;
    frame.trackingId = 3;
    frame.source = QStringLiteral("test");
    frame.image = cv::Mat::zeros(8, 12, CV_8UC3);
    manager.sendVisionFrame(frame);

    QTRY_COMPARE_WITH_TIMEOUT(sentSpy.count(), 1, 2000);
    QTRY_VERIFY(client.bytesAvailable() > 0);
    const QByteArray wire = client.readAll();
    const int newline = wire.indexOf('\n');
    QVERIFY(newline > 5);
    QVERIFY(wire.left(newline).startsWith("DXV1 "));
    bool lengthOk = false;
    const int payloadLength = wire.mid(5, newline - 5).toInt(&lengthOk);
    QVERIFY(lengthOk);
    QCOMPARE(wire.size() - newline - 1, payloadLength);
    const QJsonObject image = QJsonDocument::fromJson(wire.mid(newline + 1)).object();
    QCOMPARE(image.value("type").toString(), QStringLiteral("image"));
    QCOMPARE(image.value("protocol").toString(), QStringLiteral("DXV1"));
    QCOMPARE(image.value("frameId").toString(), QStringLiteral("81"));
    QCOMPARE(image.value("requestId").toString(), QStringLiteral("7001"));
    QCOMPARE(image.value("trackingId").toInt(), 3);
}

void SocketVisionProtocolTest::frameSendFailsWithoutDetector()
{
    SocketConnectionManager manager("127.0.0.1", 0);
    QSignalSpy failedSpy(&manager, &SocketConnectionManager::externalVisionFrameFailed);
    VisionFrame frame;
    frame.frameId = 91;
    frame.requestId = 8001;
    frame.trackingId = 0;
    frame.image = cv::Mat::zeros(4, 4, CV_8UC3);
    manager.sendVisionFrame(frame);
    QCOMPARE(failedSpy.count(), 1);
    QVERIFY(failedSpy.takeFirst().at(3).toString().contains("not connected"));
}

void SocketVisionProtocolTest::secondDetectorIsRejected()
{
    SocketConnectionManager manager("127.0.0.1", 0);
    QSignalSpy protocolSpy(&manager, &SocketConnectionManager::externalVisionProtocolError);
    QTcpSocket first;
    first.connectToHost(QHostAddress::LocalHost, manager.Server->serverPort());
    QVERIFY(first.waitForConnected(2000));
    QTRY_VERIFY(first.bytesAvailable() > 0);
    first.readAll();
    first.write("ExternalVision DXV1\n");
    QVERIFY(first.waitForBytesWritten(1000));

    QTcpSocket second;
    second.connectToHost(QHostAddress::LocalHost, manager.Server->serverPort());
    QVERIFY(second.waitForConnected(2000));
    QTRY_VERIFY(second.bytesAvailable() > 0);
    second.readAll();
    second.write("ExternalVision DXV1\n");
    QVERIFY(second.waitForBytesWritten(1000));

    QTRY_COMPARE_WITH_TIMEOUT(protocolSpy.count(), 1, 2000);
    QTRY_VERIFY_WITH_TIMEOUT(second.state() != QAbstractSocket::ConnectedState, 2000);
    QCOMPARE(first.state(), QAbstractSocket::ConnectedState);
}

void SocketVisionProtocolTest::legacyRemoteExecutionIsDisabledByDefault()
{
    SocketConnectionManager manager("127.0.0.1", 0);
    manager.ProjectName = QStringLiteral("socket-security-test");
    QSignalSpy commandSpy(&manager, &SocketConnectionManager::gcodeReceived);
    QSignalSpy rejectedSpy(&manager, &SocketConnectionManager::remoteControlRejected);

    QTcpSocket client;
    client.connectToHost(QHostAddress::LocalHost, manager.Server->serverPort());
    QVERIFY(client.waitForConnected(2000));
    QTRY_VERIFY(client.bytesAvailable() > 0);
    client.readAll();

    client.write("GScript=robot0 G28");
    QVERIFY(client.waitForBytesWritten(1000));
    QTRY_COMPARE_WITH_TIMEOUT(rejectedSpy.count(), 1, 2000);
    QCOMPARE(commandSpy.count(), 0);
    QCOMPARE(rejectedSpy.at(0).at(0).toString(), QStringLiteral("GScript"));
}

QTEST_MAIN(SocketVisionProtocolTest)
#include "tst_socket_vision_protocol.moc"
