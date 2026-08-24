#include "CalibrationMath.h"

#include "QtMatrixCompat.h"

#include <QtMath>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

namespace
{

bool finitePoint(const QPointF& point)
{
    return qIsFinite(point.x()) && qIsFinite(point.y());
}

double squaredDistance(const QPointF& lhs, const QPointF& rhs)
{
    const double dx = lhs.x() - rhs.x();
    const double dy = lhs.y() - rhs.y();
    return dx * dx + dy * dy;
}

bool containsDuplicates(const QVector<QPointF>& points, double epsilon)
{
    const double threshold = epsilon * epsilon;
    for (int i = 0; i < points.size() - 1; ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            if (squaredDistance(points[i], points[j]) <= threshold)
                return true;
        }
    }
    return false;
}

double convexHullArea(const QVector<QPointF>& points)
{
    // OpenCV's convexHull accepts 2D points with 32-bit integer or float
    // depth, but not CV_64F points. Keep this conversion local so an otherwise
    // valid homography cannot terminate calibration with an OpenCV assertion.
    std::vector<cv::Point2f> input;
    input.reserve(static_cast<size_t>(points.size()));
    for (const QPointF& point : points)
        input.emplace_back(static_cast<float>(point.x()),
                           static_cast<float>(point.y()));

    std::vector<cv::Point2f> hull;
    cv::convexHull(input, hull);
    return hull.size() >= 3 ? qAbs(cv::contourArea(hull)) : 0.0;
}

double pointSetScale(const QVector<QPointF>& points)
{
    double minX = points.first().x();
    double maxX = minX;
    double minY = points.first().y();
    double maxY = minY;
    for (const QPointF& point : points) {
        minX = qMin(minX, point.x());
        maxX = qMax(maxX, point.x());
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }
    return qMax(1.0, (maxX - minX) * (maxY - minY));
}

void calculateErrors(const QVector<QPointF>& expected,
                     const QVector<QPointF>& actual,
                     double& rmsError,
                     double& maxError)
{
    double squaredSum = 0.0;
    maxError = 0.0;
    for (int i = 0; i < expected.size(); ++i) {
        const double error = std::sqrt(squaredDistance(expected[i], actual[i]));
        squaredSum += error * error;
        maxError = qMax(maxError, error);
    }
    rmsError = expected.isEmpty() ? 0.0 : std::sqrt(squaredSum / expected.size());
}

} // namespace

namespace CalibrationMath
{

SimilarityResult calculateSimilarity(const QPointF& sourcePoint1,
                                     const QPointF& sourcePoint2,
                                     const QPointF& targetPoint1,
                                     const QPointF& targetPoint2,
                                     double epsilon)
{
    SimilarityResult result;
    if (!finitePoint(sourcePoint1) || !finitePoint(sourcePoint2) ||
        !finitePoint(targetPoint1) || !finitePoint(targetPoint2)) {
        result.errorMessage = QStringLiteral("Calibration points must be finite");
        return result;
    }

    const double sx = sourcePoint2.x() - sourcePoint1.x();
    const double sy = sourcePoint2.y() - sourcePoint1.y();
    const double tx = targetPoint2.x() - targetPoint1.x();
    const double ty = targetPoint2.y() - targetPoint1.y();
    const double sourceLength = std::hypot(sx, sy);
    const double targetLength = std::hypot(tx, ty);
    if (sourceLength <= epsilon || targetLength <= epsilon) {
        result.errorMessage = QStringLiteral("Source and target calibration points must not coincide");
        return result;
    }

    result.scale = targetLength / sourceLength;
    result.rotationRadians = std::atan2(sx * ty - sy * tx, sx * tx + sy * ty);
    const double c = result.scale * std::cos(result.rotationRadians);
    const double s = result.scale * std::sin(result.rotationRadians);
    const double dx = targetPoint1.x() - (c * sourcePoint1.x() - s * sourcePoint1.y());
    const double dy = targetPoint1.y() - (s * sourcePoint1.x() + c * sourcePoint1.y());

    result.transform.setMatrix(c, s, 0.0,
                               -s, c, 0.0,
                               dx, dy, 1.0);
    QtMatrixCompat::setMatrix2D(result.matrix, c, s, -s, c, dx, dy);
    if (!isFiniteInvertible(result.transform, epsilon) ||
        !isFiniteInvertible(result.matrix, epsilon)) {
        result.errorMessage = QStringLiteral("Similarity calculation produced an invalid matrix");
        return result;
    }

    const QVector<QPointF> expected { targetPoint1, targetPoint2 };
    const QVector<QPointF> actual {
        result.transform.map(sourcePoint1), result.transform.map(sourcePoint2)
    };
    calculateErrors(expected, actual, result.rmsError, result.maxError);
    result.isValid = true;
    return result;
}

HomographyResult calculateHomography(const QVector<QPointF>& sourcePoints,
                                     const QVector<QPointF>& targetPoints,
                                     double epsilon)
{
    HomographyResult result;
    if (sourcePoints.size() != targetPoints.size() || sourcePoints.size() < 4) {
        result.errorMessage = QStringLiteral("At least four matching point pairs are required");
        return result;
    }
    for (int i = 0; i < sourcePoints.size(); ++i) {
        if (!finitePoint(sourcePoints[i]) || !finitePoint(targetPoints[i])) {
            result.errorMessage = QStringLiteral("Calibration points must be finite");
            return result;
        }
    }
    if (containsDuplicates(sourcePoints, epsilon) || containsDuplicates(targetPoints, epsilon)) {
        result.errorMessage = QStringLiteral("Calibration point sets contain duplicates");
        return result;
    }

    const double sourceArea = convexHullArea(sourcePoints);
    const double targetArea = convexHullArea(targetPoints);
    if (sourceArea <= epsilon * pointSetScale(sourcePoints) ||
        targetArea <= epsilon * pointSetScale(targetPoints)) {
        result.errorMessage = QStringLiteral("Calibration points are collinear or cover too little area");
        return result;
    }

    std::vector<cv::Point2d> source;
    std::vector<cv::Point2d> target;
    source.reserve(static_cast<size_t>(sourcePoints.size()));
    target.reserve(static_cast<size_t>(targetPoints.size()));
    for (int i = 0; i < sourcePoints.size(); ++i) {
        source.emplace_back(sourcePoints[i].x(), sourcePoints[i].y());
        target.emplace_back(targetPoints[i].x(), targetPoints[i].y());
    }

    try {
        if (sourcePoints.size() == 4) {
            // OpenCV 4.0's getPerspectiveTransform overload requires CV_32F
            // point vectors. Later calculations still use double precision.
            std::vector<cv::Point2f> source32;
            std::vector<cv::Point2f> target32;
            source32.reserve(4);
            target32.reserve(4);
            for (int i = 0; i < sourcePoints.size(); ++i) {
                source32.emplace_back(static_cast<float>(sourcePoints[i].x()),
                                      static_cast<float>(sourcePoints[i].y()));
                target32.emplace_back(static_cast<float>(targetPoints[i].x()),
                                      static_cast<float>(targetPoints[i].y()));
            }
            result.matrix = cv::getPerspectiveTransform(source32, target32);
        } else {
            result.matrix = cv::findHomography(source, target, 0);
        }
        if (result.matrix.empty()) {
            result.errorMessage = QStringLiteral("Could not calculate a homography");
            return result;
        }
        result.matrix.convertTo(result.matrix, CV_64F);
        if (!isFiniteInvertible(result.matrix, epsilon)) {
            result.errorMessage = QStringLiteral("Homography is singular or contains invalid values");
            return result;
        }

        cv::SVD svd(result.matrix, cv::SVD::NO_UV);
        const double largest = svd.w.at<double>(0, 0);
        const double smallest = svd.w.at<double>(svd.w.rows - 1, 0);
        result.conditionNumber = smallest <= epsilon
            ? std::numeric_limits<double>::infinity() : largest / smallest;
        if (!qIsFinite(result.conditionNumber) || result.conditionNumber > 1.0e12) {
            result.errorMessage = QStringLiteral("Homography is numerically unstable");
            return result;
        }

        std::vector<cv::Point2d> projected;
        cv::perspectiveTransform(source, projected, result.matrix);
        QVector<QPointF> actual;
        actual.reserve(static_cast<int>(projected.size()));
        for (const cv::Point2d& point : projected)
            actual.append(QPointF(point.x, point.y));
        calculateErrors(targetPoints, actual, result.rmsError, result.maxError);

        result.transform = homographyToQTransform(result.matrix);
        if (!isFiniteInvertible(result.transform, epsilon)) {
            result.errorMessage = QStringLiteral("Homography cannot be represented as a valid QTransform");
            return result;
        }
        result.isValid = true;
    } catch (const cv::Exception& error) {
        result.errorMessage = QStringLiteral("Homography calculation failed: %1")
                                  .arg(QString::fromUtf8(error.what()));
    }
    return result;
}

bool isFiniteInvertible(const QTransform& transform, double epsilon)
{
    const double values[] = { transform.m11(), transform.m12(), transform.m13(),
                              transform.m21(), transform.m22(), transform.m23(),
                              transform.m31(), transform.m32(), transform.m33() };
    for (double value : values) {
        if (!qIsFinite(value))
            return false;
    }
    return qAbs(transform.determinant()) > epsilon;
}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
bool isFiniteInvertible(const QMatrix& matrix, double epsilon)
{
    const double values[] = { matrix.m11(), matrix.m12(), matrix.m21(),
                              matrix.m22(), matrix.dx(), matrix.dy() };
    for (double value : values) {
        if (!qIsFinite(value))
            return false;
    }
    return qAbs(matrix.determinant()) > epsilon;
}
#endif

bool isFiniteInvertible(const cv::Mat& matrix, double epsilon)
{
    if (matrix.rows != 3 || matrix.cols != 3)
        return false;
    cv::Mat converted;
    matrix.convertTo(converted, CV_64F);
    for (int row = 0; row < converted.rows; ++row) {
        for (int column = 0; column < converted.cols; ++column) {
            if (!qIsFinite(converted.at<double>(row, column)))
                return false;
        }
    }
    return qAbs(cv::determinant(converted)) > epsilon;
}

QTransform homographyToQTransform(const cv::Mat& matrix)
{
    cv::Mat converted;
    matrix.convertTo(converted, CV_64F);
    return QTransform(
        converted.at<double>(0, 0), converted.at<double>(1, 0), converted.at<double>(2, 0),
        converted.at<double>(0, 1), converted.at<double>(1, 1), converted.at<double>(2, 1),
        converted.at<double>(0, 2), converted.at<double>(1, 2), converted.at<double>(2, 2));
}

} // namespace CalibrationMath
