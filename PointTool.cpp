#include "PointTool.h"

QTransform PointTool::calculateTransform(const QPointF &P1, const QPointF &P2, const QPointF &P1_prime, const QPointF &P2_prime) {
    qreal dx = P1_prime.x() - P1.x();
    qreal dy = P1_prime.y() - P1.y();

    QPointF vec1 = P2 - P1;
    QPointF vec2 = P2_prime - P1_prime;

    qreal angle1 = std::atan2(vec1.y(), vec1.x());
    qreal angle2 = std::atan2(vec2.y(), vec2.x());

    qreal angle = angle2 - angle1;
    angle = angle * 180.0 / M_PI;  // Convert to degrees

    QTransform transform;
    transform.translate(dx, dy);
    transform.rotate(angle);

    return transform;
}

QMatrix PointTool::calculateTransformMatrix(const QPolygonF &sourcePolygon, const QPolygonF &destPolygon)
{
    // Kiểm tra điều kiện.
    if (sourcePolygon.size() < 4 || destPolygon.size() < 4) {
        throw std::invalid_argument("Need at least 4 points in both polygons.");
    }

    // Chuyển đổi từ QPolygonF sang std::vector<cv::Point2f>.
    std::vector<cv::Point2f> srcPoints, dstPoints;
    for (int i = 0; i < 4; ++i) {
        srcPoints.push_back(cv::Point2f(sourcePolygon[i].x(), sourcePolygon[i].y()));
        dstPoints.push_back(cv::Point2f(destPolygon[i].x(), destPolygon[i].y()));
    }

    // Tính toán ma trận chuyển đổi bằng OpenCV.
    cv::Mat transformMatrix = cv::getPerspectiveTransform(srcPoints, dstPoints);

    // Chuyển đổi ma trận từ OpenCV sang QMatrix.
    QMatrix qtMatrix(
                transformMatrix.at<double>(0, 0), transformMatrix.at<double>(0, 1),
                transformMatrix.at<double>(1, 0), transformMatrix.at<double>(1, 1),
                transformMatrix.at<double>(0, 2), transformMatrix.at<double>(1, 2)
                );

    return qtMatrix;
}
