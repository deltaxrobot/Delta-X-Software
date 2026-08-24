#include "CloudPointMapper.h"

#include "VariableManager.h"

#include <QDebug>
#include <QFile>
#include <QJsonParseError>
#include <QMetaType>
#include <QSaveFile>
#include <QtMath>

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>

namespace
{
constexpr float kCoordinateLimit = 1000000.0f;
constexpr float kDuplicateEpsilon = 1.0e-4f;
constexpr int kMaximumGridCells = 250000;
constexpr int kMaximumStoredPoints = 100000;

bool finiteVector(const QVector3D& value)
{
    return qIsFinite(value.x()) && qIsFinite(value.y()) && qIsFinite(value.z());
}

float vectorDistance(const QVector3D& lhs, const QVector3D& rhs)
{
    return (lhs - rhs).length();
}

QVector3D sourceCoordinate(const CloudPointMapper::CalibrationPoint& point, bool reverse)
{
    return reverse ? point.realCoord : point.imageCoord;
}

QVector3D targetCoordinate(const CloudPointMapper::CalibrationPoint& point, bool reverse)
{
    return reverse ? point.imageCoord : point.realCoord;
}

double radialBasis(double squaredRadius)
{
    if (squaredRadius <= 1.0e-18)
        return 0.0;
    return squaredRadius * std::log(std::sqrt(squaredRadius));
}

bool finiteJsonNumber(const QJsonValue& value)
{
    return value.isDouble() && qIsFinite(value.toDouble());
}
} // namespace

CloudPointMapper::CloudPointMapper(QObject *parent)
    : QObject(parent)
    , m_gridResolution(10.0f)
    , m_autoRebuild(true)
    , m_defaultMethod(BILINEAR)
    , m_maximumAverageError(2.0f)
    , m_maximumPointError(5.0f)
    , m_workspaceMin(0, 0, 0)
    , m_workspaceMax(0, 0, 0)
    , m_gridWidth(0)
    , m_gridHeight(0)
{
    qRegisterMetaType<CloudPointMapper::MappingStats>("CloudPointMapper::MappingStats");
}

CloudPointMapper::~CloudPointMapper() = default;

int CloudPointMapper::addCalibrationPoint(const QVector3D& imageCoord,
                                          const QVector3D& realCoord,
                                          float confidence,
                                          const QString& label)
{
    CalibrationPoint point;
    point.imageCoord = imageCoord;
    point.realCoord = realCoord;
    point.confidence = confidence;
    point.timestamp = QDateTime::currentDateTimeUtc();
    point.label = label.trimmed();

    if (!validatePoint(point)) {
        emit errorOccurred(QStringLiteral("Invalid calibration point or confidence"));
        return -1;
    }
    for (const CalibrationPoint& existing : m_calibrationPoints) {
        if (vectorDistance(existing.imageCoord, imageCoord) <= kDuplicateEpsilon) {
            emit errorOccurred(QStringLiteral("A calibration point already exists at this image coordinate"));
            return -1;
        }
    }

    m_calibrationPoints.append(point);
    updateWorkspaceBounds();
    if (m_autoRebuild && m_calibrationPoints.size() >= 3)
        buildMappingGrid(m_gridResolution);
    else
        calculateMappingStatistics();
    emit mappingUpdated();
    return m_calibrationPoints.size() - 1;
}

bool CloudPointMapper::removeCalibrationPoint(int index)
{
    if (index < 0 || index >= m_calibrationPoints.size()) {
        emit errorOccurred(QStringLiteral("Invalid point index"));
        return false;
    }

    m_calibrationPoints.removeAt(index);
    updateWorkspaceBounds();
    if (m_autoRebuild && m_calibrationPoints.size() >= 3) {
        buildMappingGrid(m_gridResolution);
    } else {
        m_mappingGrid.clear();
        m_gridWidth = 0;
        m_gridHeight = 0;
        calculateMappingStatistics();
    }
    emit mappingUpdated();
    return true;
}

bool CloudPointMapper::updateCalibrationPoint(int index,
                                             const QVector3D& imageCoord,
                                             const QVector3D& realCoord,
                                             float confidence,
                                             const QString& label)
{
    if (index < 0 || index >= m_calibrationPoints.size()) {
        emit errorOccurred(QStringLiteral("Invalid point index"));
        return false;
    }

    CalibrationPoint candidate = m_calibrationPoints[index];
    candidate.imageCoord = imageCoord;
    candidate.realCoord = realCoord;
    candidate.confidence = confidence;
    candidate.label = label.trimmed();
    candidate.timestamp = QDateTime::currentDateTimeUtc();
    candidate.error = 0.0f;
    if (!validatePoint(candidate)) {
        emit errorOccurred(QStringLiteral("Invalid updated point or confidence"));
        return false;
    }
    for (int i = 0; i < m_calibrationPoints.size(); ++i) {
        if (i != index && vectorDistance(m_calibrationPoints[i].imageCoord, imageCoord) <= kDuplicateEpsilon) {
            emit errorOccurred(QStringLiteral("Another calibration point already uses this image coordinate"));
            return false;
        }
    }

    m_calibrationPoints[index] = candidate;
    updateWorkspaceBounds();
    if (m_autoRebuild && m_calibrationPoints.size() >= 3)
        buildMappingGrid(m_gridResolution);
    else
        calculateMappingStatistics();
    emit mappingUpdated();
    return true;
}

CloudPointMapper::MappingResult CloudPointMapper::transformImageToReal(
    const QVector3D& imageCoord, InterpolationMethod method)
{
    return transformInternal(imageCoord, method, false);
}

CloudPointMapper::MappingResult CloudPointMapper::transformRealToImage(
    const QVector3D& realCoord, InterpolationMethod method)
{
    return transformInternal(realCoord, method, true);
}

CloudPointMapper::MappingResult CloudPointMapper::transformInternal(
    const QVector3D& point, InterpolationMethod method, bool reverse, int excludedIndex) const
{
    MappingResult result;
    result.method = method;
    if (!finiteVector(point)) {
        result.errorMessage = QStringLiteral("Input coordinate contains an invalid value");
        return result;
    }
    if (!isMethodSupported(method)) {
        result.errorMessage = QStringLiteral("The selected interpolation method is not implemented");
        return result;
    }

    const int usableCount = m_calibrationPoints.size() - (excludedIndex >= 0 ? 1 : 0);
    if (usableCount < 3) {
        result.errorMessage = QStringLiteral("At least 3 calibration points are required");
        return result;
    }

    const QVector<int> nearest = findNearestPoints(point, qMin(12, usableCount), reverse, excludedIndex);
    if (nearest.size() < 3) {
        result.errorMessage = QStringLiteral("Not enough usable calibration points were found");
        return result;
    }

    for (int index : nearest) {
        const float distance = vectorDistance(point, sourceCoordinate(m_calibrationPoints[index], reverse));
        if (distance <= kDuplicateEpsilon) {
            result.transformedPoint = targetCoordinate(m_calibrationPoints[index], reverse);
            result.confidence = m_calibrationPoints[index].confidence;
            result.estimatedError = m_calibrationPoints[index].error;
            result.isValid = true;
            return result;
        }
    }

    bool interpolated = false;
    switch (method) {
    case LINEAR:
        interpolated = interpolateLocalAffine(point, nearest, reverse, result.transformedPoint);
        break;
    case BILINEAR:
        interpolated = interpolateInverseDistance(point, nearest, reverse, result.transformedPoint);
        break;
    case RADIAL_BASIS:
        interpolated = interpolateRadialBasis(point, reverse, excludedIndex, result.transformedPoint);
        break;
    default:
        break;
    }
    if (!interpolated || !finiteVector(result.transformedPoint)) {
        result.errorMessage = QStringLiteral("Interpolation failed; check point coverage and geometry");
        return result;
    }

    double totalWeight = 0.0;
    double weightedConfidence = 0.0;
    double weightedResidual = 0.0;
    double localScaleSum = 0.0;
    int localScaleCount = 0;
    const float spacing = characteristicSpacing(reverse, excludedIndex);
    float nearestDistance = std::numeric_limits<float>::max();
    const QVector3D firstSource = sourceCoordinate(m_calibrationPoints[nearest.first()], reverse);
    const QVector3D firstTarget = targetCoordinate(m_calibrationPoints[nearest.first()], reverse);
    for (int index : nearest) {
        const CalibrationPoint& calibrationPoint = m_calibrationPoints[index];
        const QVector3D source = sourceCoordinate(calibrationPoint, reverse);
        const double distance = vectorDistance(point, source);
        nearestDistance = qMin(nearestDistance, static_cast<float>(distance));
        const double weight = qMax(0.01f, calibrationPoint.confidence) /
                              (distance * distance + 1.0e-6);
        totalWeight += weight;
        weightedConfidence += weight * calibrationPoint.confidence;
        weightedResidual += weight * calibrationPoint.error;

        const double sourceDelta = vectorDistance(source, firstSource);
        if (sourceDelta > kDuplicateEpsilon) {
            localScaleSum += vectorDistance(targetCoordinate(calibrationPoint, reverse), firstTarget) / sourceDelta;
            ++localScaleCount;
        }
    }

    const double dataConfidence = totalWeight > 0.0 ? weightedConfidence / totalWeight : 0.0;
    const double geometryConfidence = 1.0 / (1.0 + nearestDistance / qMax(1.0f, spacing));
    result.confidence = static_cast<float>(qBound(0.0, dataConfidence * geometryConfidence, 1.0));
    const double residual = totalWeight > 0.0 ? weightedResidual / totalWeight : 0.0;
    const double localScale = localScaleCount > 0 ? localScaleSum / localScaleCount : 1.0;
    const double geometryError = nearestDistance * localScale * (1.0 - geometryConfidence) * 0.1;
    result.estimatedError = static_cast<float>(qMax(0.0, residual + geometryError));
    result.isValid = true;
    return result;
}

bool CloudPointMapper::interpolateLocalAffine(const QVector3D& point,
                                              const QVector<int>& nearestPoints,
                                              bool reverse,
                                              QVector3D& result) const
{
    if (nearestPoints.size() < 3)
        return false;

    cv::Mat design(nearestPoints.size(), 3, CV_64F);
    cv::Mat targets(nearestPoints.size(), 3, CV_64F);
    const float spacing = characteristicSpacing(reverse);
    for (int row = 0; row < nearestPoints.size(); ++row) {
        const CalibrationPoint& calibrationPoint = m_calibrationPoints[nearestPoints[row]];
        const QVector3D source = sourceCoordinate(calibrationPoint, reverse);
        const QVector3D target = targetCoordinate(calibrationPoint, reverse);
        const double distance = vectorDistance(point, source);
        const double weight = std::sqrt(qMax(0.01f, calibrationPoint.confidence) /
                                        (1.0 + distance / qMax(1.0f, spacing)));
        design.at<double>(row, 0) = source.x() * weight;
        design.at<double>(row, 1) = source.y() * weight;
        design.at<double>(row, 2) = weight;
        targets.at<double>(row, 0) = target.x() * weight;
        targets.at<double>(row, 1) = target.y() * weight;
        targets.at<double>(row, 2) = target.z() * weight;
    }

    cv::Mat coefficients;
    if (!cv::solve(design, targets, coefficients, cv::DECOMP_SVD) || coefficients.rows != 3)
        return false;

    cv::Mat query = (cv::Mat_<double>(1, 3) << point.x(), point.y(), 1.0);
    const cv::Mat mapped = query * coefficients;
    result = QVector3D(mapped.at<double>(0, 0), mapped.at<double>(0, 1), mapped.at<double>(0, 2));
    return finiteVector(result);
}

bool CloudPointMapper::interpolateInverseDistance(const QVector3D& point,
                                                  const QVector<int>& nearestPoints,
                                                  bool reverse,
                                                  QVector3D& result) const
{
    QVector3D weightedSum;
    double totalWeight = 0.0;
    for (int index : nearestPoints) {
        const CalibrationPoint& calibrationPoint = m_calibrationPoints[index];
        const double distance = vectorDistance(point, sourceCoordinate(calibrationPoint, reverse));
        const double weight = qMax(0.01f, calibrationPoint.confidence) /
                              (distance * distance + 1.0e-6);
        weightedSum += targetCoordinate(calibrationPoint, reverse) * static_cast<float>(weight);
        totalWeight += weight;
    }
    if (totalWeight <= 0.0)
        return false;
    result = weightedSum / static_cast<float>(totalWeight);
    return finiteVector(result);
}

bool CloudPointMapper::interpolateRadialBasis(const QVector3D& point,
                                              bool reverse,
                                              int excludedIndex,
                                              QVector3D& result) const
{
    QVector<int> indices;
    for (int i = 0; i < m_calibrationPoints.size(); ++i) {
        if (i != excludedIndex)
            indices.append(i);
    }
    if (indices.size() < 3)
        return false;

    QVector3D minimum = sourceCoordinate(m_calibrationPoints[indices.first()], reverse);
    QVector3D maximum = minimum;
    for (int index : indices) {
        const QVector3D value = sourceCoordinate(m_calibrationPoints[index], reverse);
        minimum.setX(qMin(minimum.x(), value.x()));
        minimum.setY(qMin(minimum.y(), value.y()));
        maximum.setX(qMax(maximum.x(), value.x()));
        maximum.setY(qMax(maximum.y(), value.y()));
    }
    const double normalization = qMax(1.0, std::hypot(maximum.x() - minimum.x(),
                                                     maximum.y() - minimum.y()));
    const int pointCount = indices.size();
    cv::Mat system = cv::Mat::zeros(pointCount + 3, pointCount + 3, CV_64F);
    cv::Mat targets = cv::Mat::zeros(pointCount + 3, 3, CV_64F);
    QVector<QPointF> normalized;
    normalized.reserve(pointCount);
    for (int row = 0; row < pointCount; ++row) {
        const CalibrationPoint& calibrationPoint = m_calibrationPoints[indices[row]];
        const QVector3D source = sourceCoordinate(calibrationPoint, reverse);
        const QVector3D target = targetCoordinate(calibrationPoint, reverse);
        const QPointF value((source.x() - minimum.x()) / normalization,
                            (source.y() - minimum.y()) / normalization);
        normalized.append(value);
        system.at<double>(row, pointCount) = 1.0;
        system.at<double>(row, pointCount + 1) = value.x();
        system.at<double>(row, pointCount + 2) = value.y();
        system.at<double>(pointCount, row) = 1.0;
        system.at<double>(pointCount + 1, row) = value.x();
        system.at<double>(pointCount + 2, row) = value.y();
        system.at<double>(row, row) = 1.0e-9;
        targets.at<double>(row, 0) = target.x();
        targets.at<double>(row, 1) = target.y();
        targets.at<double>(row, 2) = target.z();
    }
    for (int row = 0; row < pointCount; ++row) {
        for (int column = row + 1; column < pointCount; ++column) {
            const double dx = normalized[row].x() - normalized[column].x();
            const double dy = normalized[row].y() - normalized[column].y();
            const double value = radialBasis(dx * dx + dy * dy);
            system.at<double>(row, column) = value;
            system.at<double>(column, row) = value;
        }
    }

    cv::Mat coefficients;
    if (!cv::solve(system, targets, coefficients, cv::DECOMP_SVD))
        return false;
    const QPointF query((point.x() - minimum.x()) / normalization,
                        (point.y() - minimum.y()) / normalization);
    cv::Mat basis = cv::Mat::zeros(1, pointCount + 3, CV_64F);
    for (int column = 0; column < pointCount; ++column) {
        const double dx = query.x() - normalized[column].x();
        const double dy = query.y() - normalized[column].y();
        basis.at<double>(0, column) = radialBasis(dx * dx + dy * dy);
    }
    basis.at<double>(0, pointCount) = 1.0;
    basis.at<double>(0, pointCount + 1) = query.x();
    basis.at<double>(0, pointCount + 2) = query.y();
    const cv::Mat mapped = basis * coefficients;
    result = QVector3D(mapped.at<double>(0, 0), mapped.at<double>(0, 1), mapped.at<double>(0, 2));
    return finiteVector(result);
}

QVector<int> CloudPointMapper::findNearestPoints(const QVector3D& point,
                                                 int maxPoints,
                                                 bool reverse,
                                                 int excludedIndex) const
{
    if (!reverse && excludedIndex < 0 && !m_mappingGrid.isEmpty() && m_gridResolution > 0.0f &&
        point.x() >= m_workspaceMin.x() && point.x() <= m_workspaceMax.x() &&
        point.y() >= m_workspaceMin.y() && point.y() <= m_workspaceMax.y()) {
        const int x = qBound(0, static_cast<int>((point.x() - m_workspaceMin.x()) / m_gridResolution),
                             m_gridWidth - 1);
        const int y = qBound(0, static_cast<int>((point.y() - m_workspaceMin.y()) / m_gridResolution),
                             m_gridHeight - 1);
        QVector<int> cached = m_mappingGrid[y][x].pointIndices;
        std::sort(cached.begin(), cached.end(), [this, &point](int lhs, int rhs) {
            return vectorDistance(point, m_calibrationPoints[lhs].imageCoord) <
                   vectorDistance(point, m_calibrationPoints[rhs].imageCoord);
        });
        if (cached.size() > maxPoints)
            cached.resize(maxPoints);
        if (cached.size() >= qMin(3, maxPoints))
            return cached;
    }
    return findNearestPointsGlobal(point, maxPoints, reverse, excludedIndex);
}

QVector<int> CloudPointMapper::findNearestPointsGlobal(const QVector3D& point,
                                                       int maxPoints,
                                                       bool reverse,
                                                       int excludedIndex) const
{
    QVector<int> indices;
    indices.reserve(m_calibrationPoints.size());
    for (int i = 0; i < m_calibrationPoints.size(); ++i) {
        if (i != excludedIndex)
            indices.append(i);
    }
    std::sort(indices.begin(), indices.end(), [this, &point, reverse](int lhs, int rhs) {
        return vectorDistance(point, sourceCoordinate(m_calibrationPoints[lhs], reverse)) <
               vectorDistance(point, sourceCoordinate(m_calibrationPoints[rhs], reverse));
    });
    if (indices.size() > maxPoints)
        indices.resize(maxPoints);
    return indices;
}

float CloudPointMapper::characteristicSpacing(bool reverse, int excludedIndex) const
{
    QVector<float> nearestDistances;
    for (int i = 0; i < m_calibrationPoints.size(); ++i) {
        if (i == excludedIndex)
            continue;
        float nearest = std::numeric_limits<float>::max();
        const QVector3D source = sourceCoordinate(m_calibrationPoints[i], reverse);
        for (int j = 0; j < m_calibrationPoints.size(); ++j) {
            if (j == i || j == excludedIndex)
                continue;
            nearest = qMin(nearest, vectorDistance(source, sourceCoordinate(m_calibrationPoints[j], reverse)));
        }
        if (qIsFinite(nearest) && nearest < std::numeric_limits<float>::max())
            nearestDistances.append(nearest);
    }
    if (nearestDistances.isEmpty())
        return 1.0f;
    std::sort(nearestDistances.begin(), nearestDistances.end());
    return qMax(1.0e-3f, nearestDistances[nearestDistances.size() / 2]);
}

bool CloudPointMapper::buildMappingGrid(float gridResolution)
{
    if (m_calibrationPoints.size() < 3) {
        emit errorOccurred(QStringLiteral("At least 3 calibration points are required to build the grid"));
        return false;
    }
    if (!qIsFinite(gridResolution) || gridResolution <= 0.0f) {
        emit errorOccurred(QStringLiteral("Grid cell size must be greater than zero"));
        return false;
    }

    updateWorkspaceBounds();
    const int width = qMax(1, static_cast<int>(qCeil((m_workspaceMax.x() - m_workspaceMin.x()) /
                                                     gridResolution)) + 1);
    const int height = qMax(1, static_cast<int>(qCeil((m_workspaceMax.y() - m_workspaceMin.y()) /
                                                      gridResolution)) + 1);
    if (static_cast<qint64>(width) * height > kMaximumGridCells) {
        emit errorOccurred(QStringLiteral("Grid is too large; increase the grid cell size"));
        return false;
    }

    m_gridResolution = gridResolution;
    m_gridWidth = width;
    m_gridHeight = height;
    m_mappingGrid.clear();
    m_mappingGrid.resize(m_gridHeight);
    for (int y = 0; y < m_gridHeight; ++y) {
        m_mappingGrid[y].resize(m_gridWidth);
        for (int x = 0; x < m_gridWidth; ++x)
            m_mappingGrid[y][x] = calculateGridCell(x, y);
    }
    calculateMappingStatistics();
    return true;
}

CloudPointMapper::GridCell CloudPointMapper::calculateGridCell(int gridX, int gridY)
{
    GridCell cell;
    cell.center = QVector3D(m_workspaceMin.x() + (gridX + 0.5f) * m_gridResolution,
                            m_workspaceMin.y() + (gridY + 0.5f) * m_gridResolution,
                            0.0f);
    cell.pointIndices = findNearestPointsGlobal(cell.center, 12, false, -1);
    QVector3D mapped;
    if (interpolateInverseDistance(cell.center, cell.pointIndices, false, mapped)) {
        cell.transform = mapped;
        const float nearest = vectorDistance(cell.center,
                                             m_calibrationPoints[cell.pointIndices.first()].imageCoord);
        cell.confidence = 1.0f / (1.0f + nearest / characteristicSpacing());
    } else {
        cell.confidence = 0.0f;
    }
    return cell;
}

void CloudPointMapper::calculateGridDimensions()
{
    m_gridWidth = qMax(1, static_cast<int>(qCeil((m_workspaceMax.x() - m_workspaceMin.x()) /
                                                 qMax(1.0e-3f, m_gridResolution))) + 1);
    m_gridHeight = qMax(1, static_cast<int>(qCeil((m_workspaceMax.y() - m_workspaceMin.y()) /
                                                  qMax(1.0e-3f, m_gridResolution))) + 1);
}

float CloudPointMapper::calculateCoverage() const
{
    if (m_calibrationPoints.size() < 3)
        return 0.0f;
    const float width = m_workspaceMax.x() - m_workspaceMin.x();
    const float height = m_workspaceMax.y() - m_workspaceMin.y();
    if (width <= kDuplicateEpsilon || height <= kDuplicateEpsilon)
        return 0.0f;

    constexpr int bins = 4;
    bool occupied[bins][bins] = {};
    int occupiedCount = 0;
    for (const CalibrationPoint& point : m_calibrationPoints) {
        const int x = qBound(0, static_cast<int>((point.imageCoord.x() - m_workspaceMin.x()) /
                                                 width * bins), bins - 1);
        const int y = qBound(0, static_cast<int>((point.imageCoord.y() - m_workspaceMin.y()) /
                                                 height * bins), bins - 1);
        if (!occupied[y][x]) {
            occupied[y][x] = true;
            ++occupiedCount;
        }
    }
    return 100.0f * occupiedCount / static_cast<float>(bins * bins);
}

CloudPointMapper::MappingStats CloudPointMapper::validateMapping(float validationRatio)
{
    MappingStats stats;
    stats.hasBeenValidated = true;
    stats.totalPoints = m_calibrationPoints.size();
    stats.workspaceMin = m_workspaceMin;
    stats.workspaceMax = m_workspaceMax;
    stats.coverage = calculateCoverage();
    if (m_calibrationPoints.size() < 4) {
        stats.averageError = stats.maxError = stats.minError = stats.stdDeviation = 999.0f;
        m_currentStats = stats;
        emit validationComplete(stats);
        return stats;
    }

    const int pointCount = m_calibrationPoints.size();
    int validationCount = pointCount;
    if (pointCount > 200) {
        const float boundedRatio = qBound(0.05f, validationRatio, 1.0f);
        validationCount = qBound(4, static_cast<int>(qCeil(pointCount * boundedRatio)), pointCount);
    }

    QVector<int> validationIndices;
    validationIndices.reserve(validationCount);
    if (validationCount == pointCount) {
        for (int i = 0; i < pointCount; ++i)
            validationIndices.append(i);
    } else {
        for (int i = 0; i < validationCount; ++i) {
            const int index = qRound(i * (pointCount - 1.0) / (validationCount - 1.0));
            if (!validationIndices.contains(index))
                validationIndices.append(index);
        }
    }

    QVector<float> errors;
    errors.reserve(validationIndices.size());
    for (int index : validationIndices) {
        const float error = calculatePointError(index, m_defaultMethod);
        if (qIsFinite(error)) {
            errors.append(error);
            m_calibrationPoints[index].error = error;
        }
    }
    if (errors.size() != validationIndices.size() || errors.isEmpty()) {
        stats.averageError = stats.maxError = stats.minError = stats.stdDeviation = 999.0f;
        m_currentStats = stats;
        emit validationComplete(stats);
        return stats;
    }

    stats.averageError = std::accumulate(errors.cbegin(), errors.cend(), 0.0f) / errors.size();
    stats.maxError = *std::max_element(errors.cbegin(), errors.cend());
    stats.minError = *std::min_element(errors.cbegin(), errors.cend());
    float variance = 0.0f;
    for (float error : errors)
        variance += (error - stats.averageError) * (error - stats.averageError);
    stats.stdDeviation = std::sqrt(variance / errors.size());
    stats.isValid = stats.averageError <= m_maximumAverageError &&
                    stats.maxError <= m_maximumPointError && stats.coverage >= 20.0f;
    m_currentStats = stats;
    emit validationComplete(stats);
    emit mappingUpdated();
    return stats;
}

float CloudPointMapper::calculatePointError(int pointIndex, InterpolationMethod method)
{
    if (pointIndex < 0 || pointIndex >= m_calibrationPoints.size())
        return std::numeric_limits<float>::infinity();
    const MappingResult mapped = transformInternal(m_calibrationPoints[pointIndex].imageCoord,
                                                   method, false, pointIndex);
    if (!mapped.isValid)
        return std::numeric_limits<float>::infinity();
    return vectorDistance(mapped.transformedPoint, m_calibrationPoints[pointIndex].realCoord);
}

void CloudPointMapper::calculateMappingStatistics()
{
    m_currentStats = MappingStats();
    m_currentStats.totalPoints = m_calibrationPoints.size();
    m_currentStats.workspaceMin = m_workspaceMin;
    m_currentStats.workspaceMax = m_workspaceMax;
    m_currentStats.coverage = calculateCoverage();
}

QJsonObject CloudPointMapper::pointToJson(const CalibrationPoint& point) const
{
    QJsonObject json;
    json[QStringLiteral("imageCoord")] = QJsonArray{point.imageCoord.x(), point.imageCoord.y(), point.imageCoord.z()};
    json[QStringLiteral("realCoord")] = QJsonArray{point.realCoord.x(), point.realCoord.y(), point.realCoord.z()};
    json[QStringLiteral("confidence")] = point.confidence;
    json[QStringLiteral("timestamp")] = point.timestamp.toUTC().toString(Qt::ISODateWithMs);
    json[QStringLiteral("error")] = point.error;
    json[QStringLiteral("label")] = point.label;
    json[QStringLiteral("isKeyPoint")] = point.isKeyPoint;
    return json;
}

CloudPointMapper::CalibrationPoint CloudPointMapper::pointFromJson(const QJsonObject& json) const
{
    CalibrationPoint point;
    const QJsonArray image = json.value(QStringLiteral("imageCoord")).toArray();
    const QJsonArray real = json.value(QStringLiteral("realCoord")).toArray();
    if (image.size() >= 3)
        point.imageCoord = QVector3D(image[0].toDouble(), image[1].toDouble(), image[2].toDouble());
    if (real.size() >= 3)
        point.realCoord = QVector3D(real[0].toDouble(), real[1].toDouble(), real[2].toDouble());
    point.confidence = static_cast<float>(json.value(QStringLiteral("confidence")).toDouble(1.0));
    point.timestamp = QDateTime::fromString(json.value(QStringLiteral("timestamp")).toString(), Qt::ISODate);
    if (!point.timestamp.isValid())
        point.timestamp = QDateTime::currentDateTimeUtc();
    point.error = static_cast<float>(json.value(QStringLiteral("error")).toDouble(0.0));
    point.label = json.value(QStringLiteral("label")).toString();
    point.isKeyPoint = json.value(QStringLiteral("isKeyPoint")).toBool(false);
    return point;
}

QJsonObject CloudPointMapper::mappingToJson() const
{
    QJsonArray points;
    for (const CalibrationPoint& point : m_calibrationPoints)
        points.append(pointToJson(point));
    QJsonObject json;
    json[QStringLiteral("schemaVersion")] = 2;
    json[QStringLiteral("points")] = points;
    json[QStringLiteral("gridResolution")] = m_gridResolution;
    json[QStringLiteral("interpolationMethod")] = static_cast<int>(m_defaultMethod);
    json[QStringLiteral("maximumAverageError")] = m_maximumAverageError;
    json[QStringLiteral("maximumPointError")] = m_maximumPointError;
    json[QStringLiteral("workspaceMin")] = QJsonArray{m_workspaceMin.x(), m_workspaceMin.y(), m_workspaceMin.z()};
    json[QStringLiteral("workspaceMax")] = QJsonArray{m_workspaceMax.x(), m_workspaceMax.y(), m_workspaceMax.z()};
    json[QStringLiteral("timestamp")] = QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs);
    return json;
}

bool CloudPointMapper::parseMappingJson(const QByteArray& data,
                                        QVector<CalibrationPoint>& points,
                                        float& resolution,
                                        InterpolationMethod& method,
                                        float& maximumAverageError,
                                        float& maximumPointError,
                                        QString& error) const
{
    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        error = QStringLiteral("Invalid JSON: %1").arg(parseError.errorString());
        return false;
    }
    const QJsonObject root = document.object();
    const int schemaVersion = root.value(QStringLiteral("schemaVersion")).toInt(1);
    if (schemaVersion < 1 || schemaVersion > 2) {
        error = QStringLiteral("Unsupported mapping schema version: %1").arg(schemaVersion);
        return false;
    }
    if (!root.value(QStringLiteral("points")).isArray()) {
        error = QStringLiteral("Mapping JSON does not contain a points array");
        return false;
    }
    const QJsonArray array = root.value(QStringLiteral("points")).toArray();
    if (array.size() > kMaximumStoredPoints) {
        error = QStringLiteral("Mapping contains too many calibration points");
        return false;
    }

    QVector<CalibrationPoint> parsed;
    parsed.reserve(array.size());
    for (int i = 0; i < array.size(); ++i) {
        if (!array[i].isObject()) {
            error = QStringLiteral("Calibration point %1 is not an object").arg(i + 1);
            return false;
        }
        const QJsonObject object = array[i].toObject();
        const QJsonArray image = object.value(QStringLiteral("imageCoord")).toArray();
        const QJsonArray real = object.value(QStringLiteral("realCoord")).toArray();
        if (image.size() < 3 || real.size() < 3 ||
            !finiteJsonNumber(image[0]) || !finiteJsonNumber(image[1]) || !finiteJsonNumber(image[2]) ||
            !finiteJsonNumber(real[0]) || !finiteJsonNumber(real[1]) || !finiteJsonNumber(real[2])) {
            error = QStringLiteral("Calibration point %1 has invalid coordinates").arg(i + 1);
            return false;
        }
        CalibrationPoint point = pointFromJson(object);
        if (!validatePoint(point)) {
            error = QStringLiteral("Calibration point %1 is outside accepted limits").arg(i + 1);
            return false;
        }
        for (const CalibrationPoint& existing : parsed) {
            if (vectorDistance(existing.imageCoord, point.imageCoord) <= kDuplicateEpsilon) {
                error = QStringLiteral("Calibration point %1 duplicates an image coordinate").arg(i + 1);
                return false;
            }
        }
        parsed.append(point);
    }

    const double parsedResolution = root.value(QStringLiteral("gridResolution")).toDouble(10.0);
    const int parsedMethod = root.value(QStringLiteral("interpolationMethod")).toInt(BILINEAR);
    const double parsedAverageThreshold = root.value(QStringLiteral("maximumAverageError")).toDouble(2.0);
    const double parsedPointThreshold = root.value(QStringLiteral("maximumPointError")).toDouble(5.0);
    if (!qIsFinite(parsedResolution) || parsedResolution <= 0.0 || parsedResolution > kCoordinateLimit ||
        !qIsFinite(parsedAverageThreshold) || parsedAverageThreshold <= 0.0 ||
        !qIsFinite(parsedPointThreshold) || parsedPointThreshold <= 0.0) {
        error = QStringLiteral("Mapping settings contain invalid values");
        return false;
    }
    const InterpolationMethod parsedInterpolation = static_cast<InterpolationMethod>(parsedMethod);
    if (!isMethodSupported(parsedInterpolation)) {
        error = QStringLiteral("Mapping uses an unsupported interpolation method");
        return false;
    }

    points = parsed;
    resolution = static_cast<float>(parsedResolution);
    method = parsedInterpolation;
    maximumAverageError = static_cast<float>(parsedAverageThreshold);
    maximumPointError = static_cast<float>(parsedPointThreshold);
    return true;
}

void CloudPointMapper::commitLoadedMapping(const QVector<CalibrationPoint>& points,
                                           float resolution,
                                           InterpolationMethod method,
                                           float maximumAverageError,
                                           float maximumPointError)
{
    m_calibrationPoints = points;
    m_gridResolution = resolution;
    m_defaultMethod = method;
    m_maximumAverageError = maximumAverageError;
    m_maximumPointError = maximumPointError;
    m_mappingGrid.clear();
    m_gridWidth = 0;
    m_gridHeight = 0;
    updateWorkspaceBounds();
    if (m_calibrationPoints.size() >= 3)
        buildMappingGrid(m_gridResolution);
    else
        calculateMappingStatistics();
    emit mappingUpdated();
}

bool CloudPointMapper::saveToFile(const QString& fileName) const
{
    QSaveFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    file.write(QJsonDocument(mappingToJson()).toJson(QJsonDocument::Indented));
    return file.commit();
}

bool CloudPointMapper::loadFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        emit errorOccurred(QStringLiteral("Could not open mapping file for reading"));
        return false;
    }
    QVector<CalibrationPoint> points;
    float resolution = 10.0f;
    float averageThreshold = 2.0f;
    float pointThreshold = 5.0f;
    InterpolationMethod method = BILINEAR;
    QString error;
    if (!parseMappingJson(file.readAll(), points, resolution, method,
                          averageThreshold, pointThreshold, error)) {
        emit errorOccurred(error);
        return false;
    }
    commitLoadedMapping(points, resolution, method, averageThreshold, pointThreshold);
    return true;
}

bool CloudPointMapper::exportToVariableManager(const QString& variableName) const
{
    if (variableName.trimmed().isEmpty())
        return false;
    const QString json = QString::fromUtf8(QJsonDocument(mappingToJson()).toJson(QJsonDocument::Compact));
    VariableManager::instance().updateVar(variableName + QStringLiteral("_mapping"), json);
    VariableManager::instance().updateVar(variableName + QStringLiteral("_stats"),
                                          QVariant::fromValue(m_currentStats));
    return true;
}

bool CloudPointMapper::importFromVariableManager(const QString& variableName)
{
    const QVariant stored = VariableManager::instance().getVar(variableName + QStringLiteral("_mapping"));
    if (!stored.isValid() || stored.toString().trimmed().isEmpty()) {
        emit errorOccurred(QStringLiteral("No mapping data found in VariableManager"));
        return false;
    }
    QVector<CalibrationPoint> points;
    float resolution = 10.0f;
    float averageThreshold = 2.0f;
    float pointThreshold = 5.0f;
    InterpolationMethod method = BILINEAR;
    QString error;
    if (!parseMappingJson(stored.toString().toUtf8(), points, resolution, method,
                          averageThreshold, pointThreshold, error)) {
        emit errorOccurred(error);
        return false;
    }
    commitLoadedMapping(points, resolution, method, averageThreshold, pointThreshold);
    return true;
}

void CloudPointMapper::clearMapping()
{
    m_calibrationPoints.clear();
    m_mappingGrid.clear();
    m_gridWidth = 0;
    m_gridHeight = 0;
    m_workspaceMin = QVector3D();
    m_workspaceMax = QVector3D();
    m_currentStats = MappingStats();
    emit mappingUpdated();
}

void CloudPointMapper::updateWorkspaceBounds()
{
    if (m_calibrationPoints.isEmpty()) {
        m_workspaceMin = QVector3D();
        m_workspaceMax = QVector3D();
        return;
    }
    m_workspaceMin = m_calibrationPoints.first().imageCoord;
    m_workspaceMax = m_workspaceMin;
    for (const CalibrationPoint& point : m_calibrationPoints) {
        m_workspaceMin.setX(qMin(m_workspaceMin.x(), point.imageCoord.x()));
        m_workspaceMin.setY(qMin(m_workspaceMin.y(), point.imageCoord.y()));
        m_workspaceMin.setZ(qMin(m_workspaceMin.z(), point.imageCoord.z()));
        m_workspaceMax.setX(qMax(m_workspaceMax.x(), point.imageCoord.x()));
        m_workspaceMax.setY(qMax(m_workspaceMax.y(), point.imageCoord.y()));
        m_workspaceMax.setZ(qMax(m_workspaceMax.z(), point.imageCoord.z()));
    }
}

bool CloudPointMapper::validatePoint(const CalibrationPoint& point) const
{
    if (!finiteVector(point.imageCoord) || !finiteVector(point.realCoord) ||
        !qIsFinite(point.confidence) || point.confidence < 0.0f || point.confidence > 1.0f)
        return false;
    const auto inRange = [](float value) { return qAbs(value) <= kCoordinateLimit; };
    return inRange(point.imageCoord.x()) && inRange(point.imageCoord.y()) && inRange(point.imageCoord.z()) &&
           inRange(point.realCoord.x()) && inRange(point.realCoord.y()) && inRange(point.realCoord.z());
}

float CloudPointMapper::calculateDistance(const QVector3D& p1, const QVector3D& p2)
{
    return vectorDistance(p1, p2);
}

void CloudPointMapper::optimizeGrid()
{
}

const QVector<CloudPointMapper::CalibrationPoint>& CloudPointMapper::getCalibrationPoints() const
{
    return m_calibrationPoints;
}

const CloudPointMapper::CalibrationPoint& CloudPointMapper::getCalibrationPoint(int index) const
{
    static const CalibrationPoint emptyPoint;
    return index >= 0 && index < m_calibrationPoints.size() ? m_calibrationPoints[index] : emptyPoint;
}

int CloudPointMapper::getPointCount() const
{
    return m_calibrationPoints.size();
}

CloudPointMapper::MappingStats CloudPointMapper::getMappingStats() const
{
    return m_currentStats;
}

void CloudPointMapper::setGridResolution(float resolution)
{
    if (!qIsFinite(resolution) || resolution <= 0.0f) {
        emit errorOccurred(QStringLiteral("Grid cell size must be greater than zero"));
        return;
    }
    m_gridResolution = resolution;
    if (m_autoRebuild && m_calibrationPoints.size() >= 3)
        buildMappingGrid(resolution);
}

float CloudPointMapper::getGridResolution() const
{
    return m_gridResolution;
}

void CloudPointMapper::setAutoRebuild(bool enabled)
{
    m_autoRebuild = enabled;
}

bool CloudPointMapper::isAutoRebuildEnabled() const
{
    return m_autoRebuild;
}

void CloudPointMapper::setDefaultInterpolationMethod(InterpolationMethod method)
{
    if (isMethodSupported(method))
        m_defaultMethod = method;
    else
        emit errorOccurred(QStringLiteral("The selected interpolation method is not implemented"));
    calculateMappingStatistics();
}

CloudPointMapper::InterpolationMethod CloudPointMapper::defaultInterpolationMethod() const
{
    return m_defaultMethod;
}

bool CloudPointMapper::isMethodSupported(InterpolationMethod method)
{
    return method == LINEAR || method == BILINEAR || method == RADIAL_BASIS;
}

void CloudPointMapper::setValidationThresholds(float maximumAverageError, float maximumPointError)
{
    if (!qIsFinite(maximumAverageError) || !qIsFinite(maximumPointError) ||
        maximumAverageError <= 0.0f || maximumPointError <= 0.0f) {
        emit errorOccurred(QStringLiteral("Validation thresholds must be greater than zero"));
        return;
    }
    m_maximumAverageError = maximumAverageError;
    m_maximumPointError = maximumPointError;
    calculateMappingStatistics();
}
