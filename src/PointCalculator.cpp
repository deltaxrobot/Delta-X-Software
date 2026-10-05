#include "PointCalculator.h"
#include "CalibrationMath.h"
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
        
        const CalibrationMath::SimilarityResult calculated = CalibrationMath::calculateSimilarity(
            sourcePoint1, sourcePoint2, targetPoint1, targetPoint2);
        if (!calculated.isValid) {
            result.errorMessage = calculated.errorMessage;
            return result;
        }

        result.transform = calculated.transform;
        result.matrix = calculated.matrix;
        result.rmsError = calculated.rmsError;
        result.maxError = calculated.maxError;
        result.scale = calculated.scale;
        result.rotationRadians = calculated.rotationRadians;
        
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
        
        QVector<QPointF> srcPoints;
        QVector<QPointF> dstPoints;
        for (int i = 0; i < 4; ++i) {
            srcPoints.append(sourcePoints[i]);
            dstPoints.append(targetPoints[i]);
        }

        const CalibrationMath::HomographyResult calculated =
            CalibrationMath::calculateHomography(srcPoints, dstPoints);
        if (!calculated.isValid) {
            result.errorMessage = calculated.errorMessage;
            return result;
        }
        result.matrix = calculated.matrix;
        result.qtTransform = calculated.transform;
        result.rmsError = calculated.rmsError;
        result.maxError = calculated.maxError;
        result.conditionNumber = calculated.conditionNumber;
        
        // Generate display text
        result.displayText = matrixToDisplayString(result.matrix)
            + QString("RMS: %1, Max: %2, Condition: %3")
                  .arg(result.rmsError, 0, 'f', 6)
                  .arg(result.maxError, 0, 'f', 6)
                  .arg(result.conditionNumber, 0, 'g', 6);
        
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
    
    // Check for finite and duplicate points
    for (int i = 0; i < pointCount - 1; ++i) {
        if (!qIsFinite(sourcePoints[i].x()) || !qIsFinite(sourcePoints[i].y()) ||
            !qIsFinite(targetPoints[i].x()) || !qIsFinite(targetPoints[i].y())) {
            return false;
        }
        for (int j = i + 1; j < pointCount; ++j) {
            if (sourcePoints[i] == sourcePoints[j] || targetPoints[i] == targetPoints[j]) {
                return false;
            }
        }
    }

    const int last = pointCount - 1;
    if (!qIsFinite(sourcePoints[last].x()) || !qIsFinite(sourcePoints[last].y()) ||
        !qIsFinite(targetPoints[last].x()) || !qIsFinite(targetPoints[last].y())) {
        return false;
    }

    if (pointCount >= 3) {
        auto hasArea = [pointCount](const QPointF points[]) {
            for (int i = 1; i < pointCount - 1; ++i) {
                const QPointF a = points[i] - points[0];
                for (int j = i + 1; j < pointCount; ++j) {
                    const QPointF b = points[j] - points[0];
                    if (qAbs(a.x() * b.y() - a.y() * b.x()) > 1.0e-9)
                        return true;
                }
            }
            return false;
        };
        if (!hasArea(sourcePoints) || !hasArea(targetPoints))
            return false;
    }
    
    return true;
}

// Private methods implementation

QTransform PointCalculator::calculateTransform(const QPointF& p1, const QPointF& p2, const QPointF& p1_prime, const QPointF& p2_prime)
{
    return CalibrationMath::calculateSimilarity(p1, p2, p1_prime, p2_prime).transform;
}

QMatrix PointCalculator::calculateTransformMatrix(const QPointF& p1, const QPointF& p2, const QPointF& p1_prime, const QPointF& p2_prime)
{
    return CalibrationMath::calculateSimilarity(p1, p2, p1_prime, p2_prime).matrix;
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
