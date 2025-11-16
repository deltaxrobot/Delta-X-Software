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

QMatrix PointTool::calculateTransformMatrix(const QPointF &P1, const QPointF &P2, const QPointF &P1_prime, const QPointF &P2_prime)
{
    float sourcePoint1X = P1.x();
    float sourcePoint1Y = P1.y();
    float sourcePoint2X = P2.x();
    float sourcePoint2Y = P2.y();

    float targetPoint1X = P1_prime.x();
    float targetPoint1Y = P1_prime.y();
    float targetPoint2X = P2_prime.x();
    float targetPoint2Y = P2_prime.y();

    float sourceVectorX = sourcePoint2X - sourcePoint1X;
    float sourceVectorY = sourcePoint2Y - sourcePoint1Y;
    float targetVectorX = targetPoint2X - targetPoint1X;
    float targetVectorY = targetPoint2Y - targetPoint1Y;

    float dotProduct = sourceVectorX * targetVectorX + sourceVectorY * targetVectorY;
    float sourceNorm = qSqrt(qPow(sourceVectorX, 2) + qPow(sourceVectorY, 2));
    float targetNorm = qSqrt(qPow(targetVectorX, 2) + qPow(targetVectorY, 2));
    float scaleFactor = targetNorm / sourceNorm;

    float normProduct = sourceNorm * targetNorm;

    float cosTheta = dotProduct / normProduct;
    //float cosTheta = targetVectorX / targetNorm;
    float tanTheta = (sourceVectorX * targetVectorY - sourceVectorY * targetVectorX) / (sourceVectorX * targetVectorX + sourceVectorY * targetVectorY);
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

    QMatrix rotationMatrix(qCos(theta), qSin(theta), -qSin(theta), qCos(theta), 0, 0);

    QMatrix scaleMatrix(scaleFactor, 0, 0, scaleFactor, 0, 0);

    QMatrix scaleRotateMatrix = scaleMatrix * rotationMatrix;

    // x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
    // y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

    float translationX = targetPoint1X - (scaleRotateMatrix.m11() * sourcePoint1X + scaleRotateMatrix.m21() * sourcePoint1Y);
    float translationY = targetPoint1Y - (scaleRotateMatrix.m12() * sourcePoint1X + scaleRotateMatrix.m22() * sourcePoint1Y);

    QMatrix matrix;
    QtMatrixCompat::setMatrix2D(matrix,
                                scaleRotateMatrix.m11(), scaleRotateMatrix.m12(),
                                scaleRotateMatrix.m21(), scaleRotateMatrix.m22(),
                                translationX, translationY);

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



QPointF PointTool::getCenterOfPolygon(const QPolygonF &polygon)
{
    if (polygon.isEmpty()) {
        return QPointF();
    }
    
    QPointF center;
    for (int i = 0; i < polygon.size(); ++i)
    {
        center += polygon[i];
    }
    center /= polygon.size();
    return center;
}
