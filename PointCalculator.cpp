#include "PointCalculator.h"
#include <QtMath>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

PointCalculator::TransformResult PointCalculator::calculateMappingTransform(const QPointF& sourcePoint1, const QPointF& sourcePoint2,
                                                                           const QPointF& targetPoint1, const QPointF& targetPoint2)
{
    TransformResult result;
    
    try {
        // Validate input points
        if (sourcePoint1 == sourcePoint2 || targetPoint1 == targetPoint2) {
            result.errorMessage = "Source and target points must be different";
            return result;
        }
        
        // Calculate transformation using both methods
        result.transform = calculateTransform(sourcePoint1, sourcePoint2, targetPoint1, targetPoint2);
        result.matrix = calculateTransformMatrix(sourcePoint1, sourcePoint2, targetPoint1, targetPoint2);
        
        // Generate display text
        result.displayText = transformToDisplayString(result.transform);
        
        result.isValid = true;
    }
    catch (const std::exception& e) {
        result.errorMessage = QString("Transformation calculation failed: %1").arg(e.what());
        result.isValid = false;
    }
    
    return result;
}

PointCalculator::MatrixResult PointCalculator::calculatePerspectiveMatrix(const QPointF sourcePoints[4], const QPointF targetPoints[4])
{
    MatrixResult result;
    
    try {
        // Validate input points
        if (!validatePointsForTransformation(sourcePoints, targetPoints, 4)) {
            result.errorMessage = "Invalid points for perspective transformation";
            return result;
        }
        
        // Convert to OpenCV format
        std::vector<cv::Point2f> srcPoints, dstPoints;
        for (int i = 0; i < 4; ++i) {
            srcPoints.push_back(cv::Point2f(sourcePoints[i].x(), sourcePoints[i].y()));
            dstPoints.push_back(cv::Point2f(targetPoints[i].x(), targetPoints[i].y()));
        }
        
        // Calculate perspective transformation
        result.matrix = cv::getPerspectiveTransform(srcPoints, dstPoints);
        
        // Convert to QTransform for compatibility
        result.qtTransform = QTransform(
            result.matrix.at<double>(0, 0), result.matrix.at<double>(0, 1), result.matrix.at<double>(0, 2),
            result.matrix.at<double>(1, 0), result.matrix.at<double>(1, 1), result.matrix.at<double>(1, 2),
            result.matrix.at<double>(2, 0), result.matrix.at<double>(2, 1), result.matrix.at<double>(2, 2)
        );
        
        // Generate display text
        result.displayText = matrixToDisplayString(result.matrix);
        
        result.isValid = true;
    }
    catch (const std::exception& e) {
        result.errorMessage = QString("Perspective matrix calculation failed: %1").arg(e.what());
        result.isValid = false;
    }
    
    return result;
}

PointCalculator::VectorResult PointCalculator::calculateVector(const QVector3D& point1, const QVector3D& point2, float magnitude)
{
    VectorResult result;
    
    try {
        // Calculate delta position
        QVector3D deltaPosition = point2 - point1;
        
        // Calculate magnitude of delta
        float deltaMagnitude = deltaPosition.length();
        
        if (deltaMagnitude == 0.0f) {
            result.errorMessage = "Points are identical, cannot calculate direction vector";
            return result;
        }
        
        // Calculate unit vector
        QVector3D unitVector = deltaPosition / deltaMagnitude;
        
        // Calculate result vector with desired magnitude
        result.vector = unitVector * magnitude;
        
        // Generate display text
        result.displayText = vectorToDisplayString(result.vector);
        
        result.isValid = true;
    }
    catch (const std::exception& e) {
        result.errorMessage = QString("Vector calculation failed: %1").arg(e.what());
        result.isValid = false;
    }
    
    return result;
}

PointCalculator::PointTransformResult PointCalculator::transformPoint(const QPointF& point, const QTransform& transform)
{
    PointTransformResult result;
    
    try {
        result.transformedPoint = transform.map(point);
        result.isValid = true;
    }
    catch (const std::exception& e) {
        result.errorMessage = QString("Point transformation failed: %1").arg(e.what());
        result.isValid = false;
    }
    
    return result;
}

QVector3D PointCalculator::updatePointPosition(const QVector3D& initialPoint, const QVector3D& direction, float distance)
{
    QVector3D normalizedDirection = direction.normalized();
    return initialPoint + normalizedDirection * distance;
}

PointCalculator::MatrixResult PointCalculator::calculateAffineTransform(const QPointF sourcePoints[], const QPointF targetPoints[], int pointCount)
{
    MatrixResult result;
    
    try {
        if (pointCount < 3) {
            result.errorMessage = "At least 3 points required for affine transformation";
            return result;
        }
        
        // Validate input points
        if (!validatePointsForTransformation(sourcePoints, targetPoints, pointCount)) {
            result.errorMessage = "Invalid points for affine transformation";
            return result;
        }
        
        // Convert to OpenCV format
        std::vector<cv::Point2f> srcPoints, dstPoints;
        for (int i = 0; i < pointCount; ++i) {
            srcPoints.push_back(cv::Point2f(sourcePoints[i].x(), sourcePoints[i].y()));
            dstPoints.push_back(cv::Point2f(targetPoints[i].x(), targetPoints[i].y()));
        }
        
        // Calculate affine transformation
        result.matrix = cv::estimateAffine2D(srcPoints, dstPoints);
        
        if (result.matrix.empty()) {
            result.errorMessage = "Could not calculate affine transformation";
            return result;
        }
        
        // Generate display text
        result.displayText = matrixToDisplayString(result.matrix);
        
        result.isValid = true;
    }
    catch (const std::exception& e) {
        result.errorMessage = QString("Affine transformation calculation failed: %1").arg(e.what());
        result.isValid = false;
    }
    
    return result;
}

QPointF PointCalculator::getCenterOfPolygon(const QPolygonF& polygon)
{
    if (polygon.isEmpty()) {
        return QPointF();
    }
    
    QPointF center;
    for (const QPointF& point : polygon) {
        center += point;
    }
    center /= polygon.size();
    return center;
}

bool PointCalculator::validatePointsForTransformation(const QPointF sourcePoints[], const QPointF targetPoints[], int pointCount)
{
    if (pointCount < 2) {
        return false;
    }
    
    // Check for null pointers
    if (!sourcePoints || !targetPoints) {
        return false;
    }
    
    // Check for duplicate points
    for (int i = 0; i < pointCount - 1; ++i) {
        for (int j = i + 1; j < pointCount; ++j) {
            if (sourcePoints[i] == sourcePoints[j] || targetPoints[i] == targetPoints[j]) {
                return false;
            }
        }
    }
    
    return true;
}

// Private methods implementation

QTransform PointCalculator::calculateTransform(const QPointF& p1, const QPointF& p2, const QPointF& p1_prime, const QPointF& p2_prime)
{
    // Build affine transform directly via 6 parameters
    QPointF v1 = p2 - p1;
    QPointF v2 = p2_prime - p1_prime;

    qreal angle1 = std::atan2(v1.y(), v1.x());
    qreal angle2 = std::atan2(v2.y(), v2.x());
    qreal dtheta = angle2 - angle1;            // radians

    qreal len1 = QLineF(p1, p2).length();
    qreal len2 = QLineF(p1_prime, p2_prime).length();
    qreal s = (len1 == 0.0) ? 1.0 : (len2 / len1);

    qreal c = s * std::cos(dtheta);
    qreal si = s * std::sin(dtheta);

    // For affine matrix [[a b dx],[c d dy],[0 0 1]] with rotation+scale then translate,
    // mapping equations are:
    // x' =  a*x + b*y + dx
    // y' =  c*x + d*y + dy
    // For pure rotation/scale: a=c_theta*s, b=s_theta*s, c=-s_theta*s, d=c_theta*s
    qreal a =  c;
    qreal b =  si;
    qreal cc = -si;
    qreal d =  c;

    // Solve translation so that p1 -> p1'
    qreal dx = p1_prime.x() - (a * p1.x() + b * p1.y());
    qreal dy = p1_prime.y() - (cc * p1.x() + d * p1.y());

    QTransform t;
    t.setMatrix(a, b, 0,
                cc, d, 0,
                dx, dy, 1);
    return t;
}

QMatrix PointCalculator::calculateTransformMatrix(const QPointF& p1, const QPointF& p2, const QPointF& p1_prime, const QPointF& p2_prime)
{
    float sourcePoint1X = p1.x();
    float sourcePoint1Y = p1.y();
    float sourcePoint2X = p2.x();
    float sourcePoint2Y = p2.y();

    float targetPoint1X = p1_prime.x();
    float targetPoint1Y = p1_prime.y();
    float targetPoint2X = p2_prime.x();
    float targetPoint2Y = p2_prime.y();

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
    float tanTheta = (sourceVectorX * targetVectorY - sourceVectorY * targetVectorX) / (sourceVectorX * targetVectorX + sourceVectorY * targetVectorY);
    float theta = qAcos(cosTheta);

    if (cosTheta < 0) {
        if (tanTheta > 0) {
            theta = 0 - theta;
        }
    } else {
        if (tanTheta < 0) {
            theta = 0 - theta;
        }
    }

    QMatrix rotationMatrix(qCos(theta), qSin(theta), -qSin(theta), qCos(theta), 0, 0);
    QMatrix scaleMatrix(scaleFactor, 0, 0, scaleFactor, 0, 0);
    QMatrix scaleRotateMatrix = scaleMatrix * rotationMatrix;

    // Calculate translation
    float translationX = targetPoint1X - (scaleRotateMatrix.m11() * sourcePoint1X + scaleRotateMatrix.m21() * sourcePoint1Y);
    float translationY = targetPoint1Y - (scaleRotateMatrix.m12() * sourcePoint1X + scaleRotateMatrix.m22() * sourcePoint1Y);

    QMatrix matrix;
    matrix.setMatrix(scaleRotateMatrix.m11(), scaleRotateMatrix.m12(), 
                     scaleRotateMatrix.m21(), scaleRotateMatrix.m22(), translationX, translationY);

    return matrix;
}

QString PointCalculator::transformToDisplayString(const QTransform& transform)
{
    return QString("Matrix:\n"
                   "| %1, %2, %3 |\n"
                   "| %4, %5, %6 |\n"
                   "| %7, %8, %9 |")
            .arg(transform.m11(), 0, 'f', 6)
            .arg(transform.m12(), 0, 'f', 6)
            .arg(transform.m13(), 0, 'f', 6)
            .arg(transform.m21(), 0, 'f', 6)
            .arg(transform.m22(), 0, 'f', 6)
            .arg(transform.m23(), 0, 'f', 6)
            .arg(transform.m31(), 0, 'f', 6)
            .arg(transform.m32(), 0, 'f', 6)
            .arg(transform.m33(), 0, 'f', 6);
}

QString PointCalculator::matrixToDisplayString(const cv::Mat& matrix)
{
    if (matrix.empty()) {
        return "Invalid matrix";
    }
    
    QString result = "Matrix:\n";
    for (int i = 0; i < matrix.rows; ++i) {
        result += "| ";
        for (int j = 0; j < matrix.cols; ++j) {
            result += QString("%1 ").arg(matrix.at<double>(i, j), 0, 'f', 6);
        }
        result += "|\n";
    }
    
    return result;
}

QString PointCalculator::vectorToDisplayString(const QVector3D& vector)
{
    return QString("Vector: X=%1, Y=%2, Z=%3")
            .arg(vector.x(), 0, 'f', 6)
            .arg(vector.y(), 0, 'f', 6)
            .arg(vector.z(), 0, 'f', 6);
} 
