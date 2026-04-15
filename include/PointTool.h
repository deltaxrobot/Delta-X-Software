#ifndef POINTTOOL_H
#define POINTTOOL_H

#include <QObject>
#include <QTransform>
#include <QPointF>
#include <QMatrix4x4>
#include <cmath>
#include <QPolygonF>
#include "QtMatrixCompat.h"
#include <opencv2/opencv.hpp>
#include <qmath.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Legacy Point Tool class for geometric transformations
 * 
 * @deprecated This class is maintained for backward compatibility only.
 * New code should use PointCalculator class which provides better error handling,
 * validation, and a cleaner API.
 * 
 * This class provides static methods for calculating various geometric transformations
 * including 2D transformations, perspective matrices, affine transformations, and
 * polygon center calculations.
 */
class PointTool : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Calculates 2D transformation matrix using QTransform
     * @param sourcePoint1 First source point
     * @param sourcePoint2 Second source point  
     * @param targetPoint1 First target point
     * @param targetPoint2 Second target point
     * @return QTransform Transformation matrix including scale, rotation, and translation
     * 
     * @deprecated Use PointCalculator::calculateMappingTransform() instead for better error handling
     */
    static QTransform calculateTransform(const QPointF &sourcePoint1, const QPointF &sourcePoint2, 
                                       const QPointF &targetPoint1, const QPointF &targetPoint2);

    /**
     * @brief Calculates 2D transformation matrix using QMatrix (alternative method)
     * @param sourcePoint1 First source point
     * @param sourcePoint2 Second source point
     * @param targetPoint1 First target point  
     * @param targetPoint2 Second target point
     * @return QMatrix Transformation matrix using manual calculation approach
     * 
     * @deprecated Use PointCalculator::calculateMappingTransform() instead for better error handling
     * @note This method was previously named calculateTransform2 - renamed for clarity
     */
    static QMatrix calculateTransformMatrix(const QPointF &sourcePoint1, const QPointF &sourcePoint2,
                                          const QPointF &targetPoint1, const QPointF &targetPoint2);

    /**
     * @brief Calculates perspective transformation matrix from polygon point sets
     * @param sourcePolygon Source polygon (requires exactly 4 points)
     * @param targetPolygon Target polygon (requires exactly 4 points)
     * @return cv::Mat OpenCV perspective transformation matrix
     * @throws std::invalid_argument if polygons don't have exactly 4 points
     * 
     * @deprecated Use PointCalculator::calculatePerspectiveMatrix() instead for better validation
     */
    static cv::Mat calculateMatrix(const QPolygonF &sourcePolygon, const QPolygonF &targetPolygon);

    /**
     * @brief Calculates affine transformation matrix using least squares regression
     * @param sourcePolygon Source polygon points
     * @param targetPolygon Target polygon points  
     * @return cv::Mat OpenCV affine transformation matrix (2x3)
     * 
     * @deprecated Use PointCalculator::calculateAffineTransform() instead for better validation
     */
    static cv::Mat performAffineTransformation(const QPolygonF &sourcePolygon, const QPolygonF &targetPolygon);

    /**
     * @brief Calculates the geometric center of a polygon
     * @param polygon Input polygon
     * @return QPointF Center point (average of all vertices)
     * 
     * @deprecated Use PointCalculator::getCenterOfPolygon() instead for consistency
     */
    static QPointF getCenterOfPolygon(const QPolygonF &polygon);

    // Backward compatibility aliases
    /**
     * @deprecated Use calculateTransformMatrix() instead - this name was confusing
     */
    static QMatrix calculateTransform2(const QPointF &P1, const QPointF &P2, const QPointF &P1_prime, const QPointF &P2_prime) {
        return calculateTransformMatrix(P1, P2, P1_prime, P2_prime);
    }

    /**
     * @deprecated Use getCenterOfPolygon() instead for consistent naming convention
     */
    static QPointF GetCenterOfPolygon(const QPolygonF &polygon) {
        return getCenterOfPolygon(polygon);
    }
};

#endif // POINTTOOL_H
