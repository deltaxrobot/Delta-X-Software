#ifndef CALIBRATIONMATH_H
#define CALIBRATIONMATH_H

#include <QPointF>
#include <QString>
#include <QTransform>
#include <QVector>

#include "QtMatrixCompat.h"

#include <opencv2/core.hpp>

namespace CalibrationMath
{

struct SimilarityResult
{
    bool isValid = false;
    QString errorMessage;
    QTransform transform;
    QMatrix matrix;
    double scale = 0.0;
    double rotationRadians = 0.0;
    double rmsError = 0.0;
    double maxError = 0.0;
};

struct HomographyResult
{
    bool isValid = false;
    QString errorMessage;
    cv::Mat matrix;
    QTransform transform;
    double rmsError = 0.0;
    double maxError = 0.0;
    double conditionNumber = 0.0;
};

SimilarityResult calculateSimilarity(const QPointF& sourcePoint1,
                                     const QPointF& sourcePoint2,
                                     const QPointF& targetPoint1,
                                     const QPointF& targetPoint2,
                                     double epsilon = 1.0e-9);

HomographyResult calculateHomography(const QVector<QPointF>& sourcePoints,
                                     const QVector<QPointF>& targetPoints,
                                     double epsilon = 1.0e-9);

bool isFiniteInvertible(const QTransform& transform, double epsilon = 1.0e-12);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
bool isFiniteInvertible(const QMatrix& matrix, double epsilon = 1.0e-12);
#endif
bool isFiniteInvertible(const cv::Mat& matrix, double epsilon = 1.0e-12);

QTransform homographyToQTransform(const cv::Mat& matrix);

} // namespace CalibrationMath

#endif // CALIBRATIONMATH_H
