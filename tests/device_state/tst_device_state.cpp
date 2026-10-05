#include <QtTest>

#include <future>
#include <vector>

#include "device/conveyor.h"
#include "device/device.h"
#include "device/encoder.h"

class DeviceStateTest : public QObject
{
    Q_OBJECT

private slots:
    void disconnectedQueryHasNoIoSideEffect();
    void encoderSnapshotIsThreadSafe();
    void conveyorPublishesParsedPosition();
};

void DeviceStateTest::disconnectedQueryHasNoIoSideEffect()
{
    Device device(QStringLiteral("unused"), 115200, QString(), QString(), false);
    QCOMPARE(device.GetPort(), nullptr);

    std::vector<std::future<bool>> readers;
    for (int reader = 0; reader < 8; ++reader) {
        readers.push_back(std::async(std::launch::async, [&device]() {
            for (int iteration = 0; iteration < 1000; ++iteration) {
                if (device.IsOpen())
                    return false;
            }
            return true;
        }));
    }
    for (auto& reader : readers)
        QVERIFY(reader.get());

    QCOMPARE(device.GetPort(), nullptr);
}

void DeviceStateTest::encoderSnapshotIsThreadSafe()
{
    Encoder encoder(QStringLiteral("unused"), 115200, false);
    encoder.SetLinkedConveyor(2);
    encoder.ProcessResponse(QStringLiteral("encoder0"), QStringLiteral("P12.5"));

    QCOMPARE(encoder.LinkedConveyorId(), 2);
    QCOMPARE(encoder.CurrentPosition(), 12.5f);
}

void DeviceStateTest::conveyorPublishesParsedPosition()
{
    Conveyor conveyor(QStringLiteral("unused"), 115200, false);
    QSignalSpy positionSpy(&conveyor, &Conveyor::GotEncoderPosition);
    conveyor.ProcessResponse(QStringLiteral("conveyor0"), QStringLiteral("P1:42.5"));

    QCOMPARE(conveyor.CurrentPosition(), 42.5f);
    QCOMPARE(positionSpy.size(), 1);
    QCOMPARE(positionSpy.first().at(0).toInt(), 0);
    QCOMPARE(positionSpy.first().at(1).toFloat(), 42.5f);
}

QTEST_MAIN(DeviceStateTest)
#include "tst_device_state.moc"
