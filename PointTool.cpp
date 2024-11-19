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


    qreal scale = QLineF(P1_prime, P2_prime).length() / QLineF(P1, P2).length();

    QTransform transform;
    transform.scale(scale, scale);
    transform.rotate(angle);
    transform.translate(dx, dy);

//    qDebug() << transform.map(P1);

    return transform;
}

QMatrix PointTool::calculateTransform2(const QPointF &P1, const QPointF &P2, const QPointF &P1_prime, const QPointF &P2_prime)
{
    float x1 = P1.x();
    float y1 = P1.y();
    float x2 = P2.x();
    float y2 = P2.y();

    float xx1 = P1_prime.x();
    float yy1 = P1_prime.y();
    float xx2 = P2_prime.x();
    float yy2 = P2_prime.y();

    float a1 = x2 - x1;
    float b1 = y2 - y1;
    float a2 = xx2 -xx1;
    float b2 = yy2 - yy1;

    float n1n2 = a1 * a2 + b1 * b2;
    float _n1 = qSqrt(qPow(a1, 2) + qPow(b1, 2));
    float _n2 = qSqrt(qPow(a2, 2) + qPow(b2, 2));
    float ratio = _n2/_n1;

    float _n1_n2_ = _n1 * _n2;

    float cosTheta = n1n2 / _n1_n2_;
    //float cosTheta = a2 / _n2;
    float tanTheta = (a1 * b2 - b1 * a2) / (a1 * a2 + b1 * b2);
    float theta = qAcos(cosTheta);

    if (cosTheta < 0)
    {
        if (tanTheta > 0)
        {
            theta = 0 - theta;
        }
    }
    else
    {
        if (tanTheta < 0)
        {
            theta = 0 - theta;
        }
    }

    float angle = 0 - theta * (180 / M_PI);

    QMatrix RotateMatrix(qCos(theta), qSin(theta), -qSin(theta), qCos(theta), 0, 0);

    QMatrix ScaleMatrix(ratio, 0, 0, ratio, 0, 0);

    QMatrix ScaleRotateMatrix = ScaleMatrix * RotateMatrix;

    // x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
    // y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

    float dx = xx1 - (ScaleRotateMatrix.m11() * x1 + ScaleRotateMatrix.m21() * y1);
    float dy = yy1 - (ScaleRotateMatrix.m12() * x1 + ScaleRotateMatrix.m22() * y1);

    QMatrix matrix;
    matrix.setMatrix(ScaleRotateMatrix.m11(), ScaleRotateMatrix.m12(), ScaleRotateMatrix.m21(), ScaleRotateMatrix.m22(), dx, dy);

//    qDebug() << matrix.map(P1);

    return matrix;
}

cv::Mat PointTool::calculateMatrix(const QPolygonF &sourcePolygon, const QPolygonF &destPolygon)
{
    // Kiểm tra điều kiện.
    if (sourcePolygon.size() < 4 || destPolygon.size() < 4) {
        throw std::invalid_argument("Need at least 4 points in both polygons.");
    }

    // Chuyển đổi từ QPolygonF sang std::vector<cv::Point2f>.
    std::vector<cv::Point2f> srcPoints, dstPoints;
    for (int i = 0; i < sourcePolygon.size() && i < destPolygon.size(); ++i) {
        srcPoints.push_back(cv::Point2f(sourcePolygon[i].x(), sourcePolygon[i].y()));
        dstPoints.push_back(cv::Point2f(destPolygon[i].x(), destPolygon[i].y()));
    }

    // Tính toán ma trận chuyển đổi bằng OpenCV.
    cv::Mat transformMatrix = cv::getPerspectiveTransform(srcPoints, dstPoints);

    return transformMatrix;
}

cv::Mat PointTool::performAffineTransformation(const QPolygonF &sourcePolygon, const QPolygonF &destPolygon)
{
        // Convert QPolygonF to std::vector<cv::Point2f>
        std::vector<cv::Point2f> sourcePoints, targetPoints;
        for (const QPointF &point : sourcePolygon)
            sourcePoints.push_back(cv::Point2f(point.x(), point.y()));
        for (const QPointF &point : destPolygon)
            targetPoints.push_back(cv::Point2f(point.x(), point.y()));
    // Perform least squares regression
    cv::Mat transformationMatrix = cv::estimateAffine2D(sourcePoints, targetPoints);

    return transformationMatrix;
}



QPointF PointTool::GetCenterOfPolygon(const QPolygonF &polygon)
{
    QPointF center;
    for (int i = 0; i < polygon.size(); ++i)
    {
        center += polygon[i];
    }
    center /= polygon.size();
    return center;
}
