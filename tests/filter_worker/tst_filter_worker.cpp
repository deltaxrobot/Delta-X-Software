#include <QtTest>

#include "FilterWork.h"

class FilterWorkerTest : public QObject
{
    Q_OBJECT

private slots:
    void thresholdProducesBinaryImage();
    void hsvProducesMask();
    void evenBlurSizeIsNormalized();
    void invalidParametersReportFailure();
    void emptyImageProducesNoOutput();
};

void FilterWorkerTest::thresholdProducesBinaryImage()
{
    FilterWork worker;
    cv::Mat output;
    QString error;
    connect(&worker, &FilterWork::FinishedFilter, this,
            [&output](const cv::Mat& result) { output = result.clone(); });
    connect(&worker, &FilterWork::FilterFailed, this,
            [&error](const QString& message) { error = message; });

    cv::Mat input(1, 2, CV_8UC3);
    input.at<cv::Vec3b>(0, 0) = cv::Vec3b(0, 0, 0);
    input.at<cv::Vec3b>(0, 1) = cv::Vec3b(255, 255, 255);
    worker.DoFilter(input, {127}, false, 1);

    QVERIFY2(error.isEmpty(), qPrintable(error));
    QCOMPARE(output.type(), CV_8UC1);
    QCOMPARE(output.at<uchar>(0, 0), uchar(0));
    QCOMPARE(output.at<uchar>(0, 1), uchar(255));
}

void FilterWorkerTest::hsvProducesMask()
{
    FilterWork worker;
    cv::Mat output;
    connect(&worker, &FilterWork::FinishedFilter, this,
            [&output](const cv::Mat& result) { output = result.clone(); });

    const cv::Mat redPixel(1, 1, CV_8UC3, cv::Scalar(0, 0, 255));
    worker.DoFilter(redPixel, {0, 10, 200, 255, 200, 255}, false, 1);

    QCOMPARE(output.type(), CV_8UC1);
    QCOMPARE(output.at<uchar>(0, 0), uchar(255));
}

void FilterWorkerTest::evenBlurSizeIsNormalized()
{
    FilterWork worker;
    int outputs = 0;
    QString error;
    connect(&worker, &FilterWork::FinishedFilter, this,
            [&outputs](const cv::Mat&) { ++outputs; });
    connect(&worker, &FilterWork::FilterFailed, this,
            [&error](const QString& message) { error = message; });

    worker.DoFilter(cv::Mat::zeros(5, 5, CV_8UC3), {127}, false, 2);

    QVERIFY2(error.isEmpty(), qPrintable(error));
    QCOMPARE(outputs, 1);
}

void FilterWorkerTest::invalidParametersReportFailure()
{
    FilterWork worker;
    int outputs = 0;
    QString error;
    connect(&worker, &FilterWork::FinishedFilter, this,
            [&outputs](const cv::Mat&) { ++outputs; });
    connect(&worker, &FilterWork::FilterFailed, this,
            [&error](const QString& message) { error = message; });

    worker.DoFilter(cv::Mat::zeros(2, 2, CV_8UC3), {1, 2}, false, 1);

    QCOMPARE(outputs, 0);
    QVERIFY(error.contains(QStringLiteral("parameter count")));
}

void FilterWorkerTest::emptyImageProducesNoOutput()
{
    FilterWork worker;
    int outputs = 0;
    int failures = 0;
    connect(&worker, &FilterWork::FinishedFilter, this,
            [&outputs](const cv::Mat&) { ++outputs; });
    connect(&worker, &FilterWork::FilterFailed, this,
            [&failures](const QString&) { ++failures; });

    worker.DoFilter({}, {127}, false, 1);

    QCOMPARE(outputs, 0);
    QCOMPARE(failures, 0);
}

QTEST_MAIN(FilterWorkerTest)
#include "tst_filter_worker.moc"
