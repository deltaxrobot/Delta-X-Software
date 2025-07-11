#ifndef POINTCALCULATOR_H
#define POINTCALCULATOR_H

#include <QPointF>
#include <QVector3D>
#include <QTransform>
#include <QMatrix>
#include <QPolygonF>
#include <opencv2/opencv.hpp>
#include <stdexcept>

/**
 * @brief Business logic class for Point Tool calculations
 * 
 * This class handles all mathematical operations and transformations
 * used in the Point Tool, separated from UI concerns.
 */
class PointCalculator
{
public:
    /**
     * @brief Result structure for transformation calculations
     */
    struct TransformResult {
        QTransform transform;
        QMatrix matrix;
        QString displayText;
        bool isValid = false;
        QString errorMessage;
    };

    /**
     * @brief Result structure for vector calculations
     */
    struct VectorResult {
        QVector3D vector;
        QString displayText;
        bool isValid = false;
        QString errorMessage;
    };

    /**
     * @brief Result structure for matrix calculations
     */
    struct MatrixResult {
        cv::Mat matrix;
        QTransform qtTransform;
        QString displayText;
        bool isValid = false;
        QString errorMessage;
    };

    /**
     * @brief Result structure for point transformation
     */
    struct PointTransformResult {
        QPointF transformedPoint;
        bool isValid = false;
        QString errorMessage;
    };

public:
    PointCalculator() = default;
    ~PointCalculator() = default;

    /**
     * @brief Calculates 2D transformation matrix from two point pairs
     * @param sourcePoint1 First source point
     * @param sourcePoint2 Second source point
     * @param targetPoint1 First target point
     * @param targetPoint2 Second target point
     * @return TransformResult containing transformation matrix and display text
     */
    TransformResult calculateMappingTransform(const QPointF& sourcePoint1, const QPointF& sourcePoint2,
                                            const QPointF& targetPoint1, const QPointF& targetPoint2);

    /**
     * @brief Calculates perspective transformation matrix from 4 point pairs
     * @param sourcePoints Array of 4 source points
     * @param targetPoints Array of 4 target points
     * @return MatrixResult containing OpenCV matrix and display text
     */
    MatrixResult calculatePerspectiveMatrix(const QPointF sourcePoints[4], const QPointF targetPoints[4]);

    /**
     * @brief Calculates 3D vector from two points and magnitude
     * @param point1 First 3D point
     * @param point2 Second 3D point
     * @param magnitude Desired magnitude of the result vector
     * @return VectorResult containing calculated vector and display text
     */
    VectorResult calculateVector(const QVector3D& point1, const QVector3D& point2, float magnitude);

    /**
     * @brief Transforms a 2D point using given transformation matrix
     * @param point Point to transform
     * @param transform Transformation matrix
     * @return PointTransformResult containing transformed point
     */
    PointTransformResult transformPoint(const QPointF& point, const QTransform& transform);

    /**
     * @brief Updates a 3D point position based on vector and distance
     * @param initialPoint Starting point
     * @param direction Direction vector
     * @param distance Distance to move
     * @return QVector3D New position
     */
    QVector3D updatePointPosition(const QVector3D& initialPoint, const QVector3D& direction, float distance);

    /**
     * @brief Calculates affine transformation matrix
     * @param sourcePoints Source point array
     * @param targetPoints Target point array
     * @param pointCount Number of points (minimum 3)
     * @return MatrixResult containing affine transformation matrix
     */
    MatrixResult calculateAffineTransform(const QPointF sourcePoints[], const QPointF targetPoints[], int pointCount);

    /**
     * @brief Gets center point of a polygon
     * @param polygon Input polygon
     * @return QPointF Center point
     */
    QPointF getCenterOfPolygon(const QPolygonF& polygon);

    /**
     * @brief Validates if points are suitable for transformation
     * @param sourcePoints Source point array
     * @param targetPoints Target point array
     * @param pointCount Number of points
     * @return true if points are valid for transformation
     */
    bool validatePointsForTransformation(const QPointF sourcePoints[], const QPointF targetPoints[], int pointCount);

private:
    /**
     * @brief Internal method for 2D transform calculation using QTransform
     * @param p1 First source point
     * @param p2 Second source point
     * @param p1_prime First target point
     * @param p2_prime Second target point
     * @return QTransform Calculated transformation matrix
     */
    QTransform calculateTransform(const QPointF& p1, const QPointF& p2, const QPointF& p1_prime, const QPointF& p2_prime);

    /**
     * @brief Internal method for 2D transform calculation using QMatrix
     * @param p1 First source point
     * @param p2 Second source point
     * @param p1_prime First target point
     * @param p2_prime Second target point
     * @return QMatrix Calculated transformation matrix
     */
    QMatrix calculateTransformMatrix(const QPointF& p1, const QPointF& p2, const QPointF& p1_prime, const QPointF& p2_prime);

    /**
     * @brief Converts QTransform to display string
     * @param transform QTransform matrix
     * @return QString Formatted display string
     */
    QString transformToDisplayString(const QTransform& transform);

    /**
     * @brief Converts OpenCV matrix to display string
     * @param matrix OpenCV matrix
     * @return QString Formatted display string
     */
    QString matrixToDisplayString(const cv::Mat& matrix);

    /**
     * @brief Converts QVector3D to display string
     * @param vector 3D vector
     * @return QString Formatted display string
     */
    QString vectorToDisplayString(const QVector3D& vector);
};

#endif // POINTCALCULATOR_H 