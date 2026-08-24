#include <QtTest>

#include "TaskNode.h"
#include "VisionTypes.h"

class VisionPipelineTest : public QObject
{
    Q_OBJECT

private slots:
    void detachedFrameOwnsPixels();
    void cropAcceptsImageBoundary();
    void mappingRejectsCoincidentPoints();
    void identityMappingIsAValidCalibration();
};

void VisionPipelineTest::detachedFrameOwnsPixels()
{
    VisionFrame source;
    source.frameId = 1;
    source.image = cv::Mat::zeros(4, 4, CV_8UC1);
    VisionFrame detached = source.detached();
    source.image.setTo(255);
    QCOMPARE(detached.image.at<uchar>(0, 0), uchar(0));
}

void VisionPipelineTest::cropAcceptsImageBoundary()
{
    TaskNode crop("crop", TaskNode::CROP_IMAGE_NODE);
    crop.SetPassThrough(false);
    cv::Mat received;
    auto imageSignal = static_cast<void (TaskNode::*)(cv::Mat)>(&TaskNode::HadOutput);
    connect(&crop, imageSignal, this, [&received](cv::Mat image) {
        received = image.clone();
    });

    crop.Input(QRectF(2, 2, 8, 8));
    crop.Input(cv::Mat::ones(10, 10, CV_8UC1));
    QCOMPARE(received.cols, 8);
    QCOMPARE(received.rows, 8);
}

void VisionPipelineTest::mappingRejectsCoincidentPoints()
{
    TaskNode mapping("mapping", TaskNode::MAPPING_MATRIX_NODE);
    int outputs = 0;
    auto matrixSignal = static_cast<void (TaskNode::*)(QMatrix)>(&TaskNode::HadOutput);
    connect(&mapping, matrixSignal, this, [&outputs](QMatrix) { ++outputs; });
    mapping.Input(QPolygonF({ QPointF(2, 2), QPointF(2, 2),
                              QPointF(0, 0), QPointF(10, 0) }));
    QCOMPARE(outputs, 0);
}

void VisionPipelineTest::identityMappingIsAValidCalibration()
{
    TaskNode mapping("mapping", TaskNode::MAPPING_MATRIX_NODE);
    QMatrix result;
    int outputs = 0;
    auto matrixSignal = static_cast<void (TaskNode::*)(QMatrix)>(&TaskNode::HadOutput);
    connect(&mapping, matrixSignal, this, [&result, &outputs](QMatrix matrix) {
        result = matrix;
        ++outputs;
    });
    mapping.Input(QPolygonF({ QPointF(0, 0), QPointF(10, 0),
                              QPointF(0, 0), QPointF(10, 0) }));
    QCOMPARE(outputs, 1);
    QVERIFY(result.isIdentity());
    QVERIFY(!qFuzzyIsNull(result.determinant()));
}

QTEST_MAIN(VisionPipelineTest)
#include "tst_vision_pipeline.moc"
