#include <QtTest>

#include "CalibrationMath.h"
#include "CameraCalibration.h"
#include "CloudPointMapper.h"
#include "PointCalculator.h"
#include "VariableManager.h"

class CalibrationCoreTest : public QObject
{
    Q_OBJECT

private slots:
    void similarityHandlesAllRotationQuadrants();
    void homographyUsesQtCoefficientConvention();
    void homographyRejectsCollinearPoints();
    void cloudMappingIsExactAndDeterministic();
    void cloudImportIsTransactional();
    void cameraProfileRoundTripsAndUndistorts();
};

void CalibrationCoreTest::similarityHandlesAllRotationQuadrants()
{
    const QList<double> angles { -M_PI, -M_PI_2, -0.7, 0.0, M_PI_2, M_PI - 0.1 };
    for (double angle : angles) {
        const double scale = 2.25;
        const QPointF source1(12.0, -8.0);
        const QPointF source2(45.0, 17.0);
        const auto mapExpected = [angle, scale](const QPointF& point) {
            const double c = scale * std::cos(angle);
            const double s = scale * std::sin(angle);
            return QPointF(c * point.x() - s * point.y() + 90.0,
                           s * point.x() + c * point.y() - 35.0);
        };
        const CalibrationMath::SimilarityResult result = CalibrationMath::calculateSimilarity(
            source1, source2, mapExpected(source1), mapExpected(source2));
        QVERIFY2(result.isValid, qPrintable(result.errorMessage));
        const QPointF actual = result.transform.map(QPointF(-4.0, 29.0));
        const QPointF expected = mapExpected(QPointF(-4.0, 29.0));
        QVERIFY(QLineF(actual, expected).length() < 1.0e-8);
        QVERIFY(result.rmsError < 1.0e-8);
    }
}

void CalibrationCoreTest::homographyUsesQtCoefficientConvention()
{
    const QVector<QPointF> source {
        QPointF(0, 0), QPointF(200, 0), QPointF(200, 120), QPointF(0, 120)
    };
    const QVector<QPointF> target {
        QPointF(20, 10), QPointF(250, 30), QPointF(215, 180), QPointF(-15, 145)
    };
    const CalibrationMath::HomographyResult result =
        CalibrationMath::calculateHomography(source, target);
    QVERIFY2(result.isValid, qPrintable(result.errorMessage));

    std::vector<cv::Point2d> cvInput { cv::Point2d(63.5, 44.25) };
    std::vector<cv::Point2d> cvOutput;
    cv::perspectiveTransform(cvInput, cvOutput, result.matrix);
    const QPointF qtOutput = result.transform.map(QPointF(cvInput[0].x, cvInput[0].y));
    QVERIFY(std::hypot(qtOutput.x() - cvOutput[0].x,
                       qtOutput.y() - cvOutput[0].y) < 1.0e-8);
}

void CalibrationCoreTest::homographyRejectsCollinearPoints()
{
    const QVector<QPointF> source {
        QPointF(0, 0), QPointF(10, 0), QPointF(20, 0), QPointF(30, 0)
    };
    const QVector<QPointF> target {
        QPointF(0, 0), QPointF(10, 10), QPointF(20, 20), QPointF(30, 30)
    };
    QVERIFY(!CalibrationMath::calculateHomography(source, target).isValid);
}

void CalibrationCoreTest::cloudMappingIsExactAndDeterministic()
{
    CloudPointMapper mapper;
    const QList<QPointF> points {
        QPointF(0, 0), QPointF(100, 0), QPointF(100, 100),
        QPointF(0, 100), QPointF(50, 50)
    };
    for (const QPointF& point : points) {
        QCOMPARE(mapper.addCalibrationPoint(
                     QVector3D(point.x(), point.y(), 0),
                     QVector3D(point.x(), point.y(), 0)),
                 points.indexOf(point));
    }

    const CloudPointMapper::MappingResult zero = mapper.transformImageToReal(
        QVector3D(0, 0, 0), CloudPointMapper::BILINEAR);
    QVERIFY(zero.isValid);
    QCOMPARE(zero.transformedPoint, QVector3D(0, 0, 0));
    QVERIFY(zero.confidence > 0.99f);

    const CloudPointMapper::MappingResult unsupported = mapper.transformImageToReal(
        QVector3D(20, 20, 0), CloudPointMapper::CUBIC_SPLINE);
    QVERIFY(!unsupported.isValid);

    mapper.setDefaultInterpolationMethod(CloudPointMapper::LINEAR);
    const CloudPointMapper::MappingStats first = mapper.validateMapping(0.2f);
    const CloudPointMapper::MappingStats second = mapper.validateMapping(0.2f);
    QVERIFY(first.hasBeenValidated);
    QVERIFY(first.isValid);
    QCOMPARE(first.averageError, second.averageError);
    QCOMPARE(first.maxError, second.maxError);
}

void CalibrationCoreTest::cloudImportIsTransactional()
{
    CloudPointMapper mapper;
    mapper.addCalibrationPoint(QVector3D(0, 0, 0), QVector3D(0, 0, 0));
    mapper.addCalibrationPoint(QVector3D(100, 0, 0), QVector3D(100, 0, 0));
    mapper.addCalibrationPoint(QVector3D(0, 100, 0), QVector3D(0, 100, 0));
    const int originalCount = mapper.getPointCount();
    const QString variableName = QStringLiteral("CalibrationCoreTest.Invalid.%1")
                                     .arg(QDateTime::currentMSecsSinceEpoch());
    VariableManager::instance().updateVar(variableName + QStringLiteral("_mapping"),
                                          QStringLiteral("{broken json"));
    QVERIFY(!mapper.importFromVariableManager(variableName));
    QCOMPARE(mapper.getPointCount(), originalCount);
}

void CalibrationCoreTest::cameraProfileRoundTripsAndUndistorts()
{
    CameraCalibration::Profile profile;
    profile.isValid = true;
    profile.cameraMatrix = (cv::Mat_<double>(3, 3) <<
        800.0, 0.0, 320.0,
        0.0, 800.0, 240.0,
        0.0, 0.0, 1.0);
    profile.distortionCoefficients = cv::Mat::zeros(1, 8, CV_64F);
    profile.imageSize = QSize(640, 480);
    profile.boardSize = QSize(9, 6);
    profile.squareSizeMm = 25.0;
    profile.rmsErrorPx = 0.2;
    profile.maximumViewErrorPx = 0.4;
    profile.sampleCount = 12;
    profile.calibratedAt = QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs);

    const QString project = QStringLiteral("CalibrationCoreTest.%1")
                                .arg(QDateTime::currentMSecsSinceEpoch());
    QVERIFY(CameraCalibration::saveToVariables(project, QStringLiteral("Camera.Intrinsic"), profile));
    CameraCalibration::Profile loaded;
    QString error;
    QVERIFY2(CameraCalibration::loadFromVariables(
                 project, QStringLiteral("Camera.Intrinsic"), loaded, &error),
             qPrintable(error));
    QCOMPARE(loaded.imageSize, profile.imageSize);
    QCOMPARE(loaded.sampleCount, profile.sampleCount);

    cv::Mat source(480, 640, CV_8UC1, cv::Scalar(73));
    cv::Mat corrected;
    QVERIFY(CameraCalibration::undistort(loaded, source, corrected, &error));
    QCOMPARE(corrected.size(), source.size());
    QVERIFY(cv::norm(source, corrected, cv::NORM_INF) == 0.0);
}

QTEST_GUILESS_MAIN(CalibrationCoreTest)
#include "tst_calibration_core.moc"
