#include "CloudPointMapper.h"
#include <QRandomGenerator>
#include "VariableManager.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QtMath>
#include <QMetaType>
#include <algorithm>
#include <numeric>

CloudPointMapper::CloudPointMapper(QObject *parent)
    : QObject(parent)
    , m_gridResolution(10.0f)
    , m_autoRebuild(true)
    , m_defaultMethod(BILINEAR)
    , m_gridWidth(0)
    , m_gridHeight(0)
{
    // Register meta types
    qRegisterMetaType<CloudPointMapper::MappingStats>("CloudPointMapper::MappingStats");
    
    // Initialize workspace bounds
    m_workspaceMin = QVector3D(0, 0, 0);
    m_workspaceMax = QVector3D(1000, 1000, 200);
    
    // Initialize stats
    m_currentStats.totalPoints = 0;
    m_currentStats.averageError = 0.0f;
    m_currentStats.maxError = 0.0f;
    m_currentStats.minError = 0.0f;
    m_currentStats.stdDeviation = 0.0f;
    m_currentStats.coverage = 0.0f;
    m_currentStats.isValid = false;
    
    qDebug() << "CloudPointMapper initialized with grid resolution:" << m_gridResolution;
}

CloudPointMapper::~CloudPointMapper()
{
    clearMapping();
}

int CloudPointMapper::addCalibrationPoint(const QVector3D& imageCoord, const QVector3D& realCoord, 
                                         float confidence, const QString& label)
{
    // Validate input
    if (confidence < 0.0f || confidence > 1.0f) {
        emit errorOccurred("Invalid confidence value. Must be between 0.0 and 1.0");
        return -1;
    }
    
    // Create new calibration point
    CalibrationPoint point;
    point.imageCoord = imageCoord;
    point.realCoord = realCoord;
    point.confidence = confidence;
    point.timestamp = QDateTime::currentDateTime();
    point.error = 0.0f;
    point.label = label;
    point.isKeyPoint = false;
    
    // Validate point
    if (!validatePoint(point)) {
        emit errorOccurred("Invalid calibration point coordinates");
        return -1;
    }
    
    // Add to collection
    m_calibrationPoints.append(point);
    int pointIndex = m_calibrationPoints.size() - 1;
    
    // Update workspace bounds
    updateWorkspaceBounds();
    
    // Rebuild grid if auto-rebuild is enabled
    if (m_autoRebuild && m_calibrationPoints.size() >= 3) {
        buildMappingGrid(m_gridResolution);
    }
    
    emit mappingUpdated();
    
    qDebug() << "Added calibration point" << pointIndex << ":" << imageCoord << "->" << realCoord;
    return pointIndex;
}

bool CloudPointMapper::removeCalibrationPoint(int index)
{
    if (index < 0 || index >= m_calibrationPoints.size()) {
        emit errorOccurred("Invalid point index");
        return false;
    }
    
    m_calibrationPoints.removeAt(index);
    
    // Update workspace bounds
    updateWorkspaceBounds();
    
    // Rebuild grid if auto-rebuild is enabled
    if (m_autoRebuild && m_calibrationPoints.size() >= 3) {
        buildMappingGrid(m_gridResolution);
    }
    
    emit mappingUpdated();
    return true;
}

bool CloudPointMapper::updateCalibrationPoint(int index, const QVector3D& imageCoord, 
                                             const QVector3D& realCoord, float confidence)
{
    if (index < 0 || index >= m_calibrationPoints.size()) {
        emit errorOccurred("Invalid point index");
        return false;
    }
    
    if (confidence < 0.0f || confidence > 1.0f) {
        emit errorOccurred("Invalid confidence value");
        return false;
    }
    
    // Update point
    m_calibrationPoints[index].imageCoord = imageCoord;
    m_calibrationPoints[index].realCoord = realCoord;
    m_calibrationPoints[index].confidence = confidence;
    m_calibrationPoints[index].timestamp = QDateTime::currentDateTime();
    
    // Validate updated point
    if (!validatePoint(m_calibrationPoints[index])) {
        emit errorOccurred("Invalid updated point coordinates");
        return false;
    }
    
    // Update workspace bounds
    updateWorkspaceBounds();
    
    // Rebuild grid if auto-rebuild is enabled
    if (m_autoRebuild && m_calibrationPoints.size() >= 3) {
        buildMappingGrid(m_gridResolution);
    }
    
    emit mappingUpdated();
    return true;
}

CloudPointMapper::MappingResult CloudPointMapper::transformImageToReal(const QVector3D& imageCoord, 
                                                                       InterpolationMethod method)
{
    MappingResult result;
    result.isValid = false;
    result.confidence = 0.0f;
    result.estimatedError = 999.0f;
    result.method = method;
    
    // Check if we have enough calibration points
    if (m_calibrationPoints.size() < 3) {
        result.errorMessage = "Need at least 3 calibration points for transformation";
        return result;
    }
    
    try {
        // Find nearest calibration points
        QVector<int> nearestPoints = findNearestPoints(imageCoord, 4);
        
        if (nearestPoints.isEmpty()) {
            result.errorMessage = "No suitable calibration points found";
            return result;
        }
        
        // Perform interpolation based on method
        QVector3D transformedPoint;
        switch (method) {
            case LINEAR:
                transformedPoint = interpolateLinear(imageCoord, nearestPoints);
                break;
            case BILINEAR:
                transformedPoint = interpolateBilinear(imageCoord, nearestPoints);
                break;
            case CUBIC_SPLINE:
                transformedPoint = interpolateCubicSpline(imageCoord, nearestPoints);
                break;
            case RADIAL_BASIS:
                transformedPoint = interpolateRadialBasis(imageCoord, nearestPoints);
                break;
            case KRIGING:
                transformedPoint = interpolateKriging(imageCoord, nearestPoints);
                break;
            default:
                transformedPoint = interpolateBilinear(imageCoord, nearestPoints);
        }
        
        // Calculate confidence based on distance to nearest points
        float totalDistance = 0.0f;
        float totalConfidence = 0.0f;
        
        for (int idx : nearestPoints) {
            float distance = calculateDistance(imageCoord, m_calibrationPoints[idx].imageCoord);
            float weight = 1.0f / (distance + 1.0f); // Avoid division by zero
            totalDistance += distance * weight;
            totalConfidence += m_calibrationPoints[idx].confidence * weight;
        }
        
        result.transformedPoint = transformedPoint;
        result.confidence = totalConfidence / nearestPoints.size();
        result.estimatedError = totalDistance / nearestPoints.size();
        result.isValid = true;
        
        qDebug() << "Transformed" << imageCoord << "to" << transformedPoint << "with confidence" << result.confidence;
        
    } catch (const std::exception& e) {
        result.errorMessage = QString("Transformation failed: %1").arg(e.what());
        emit errorOccurred(result.errorMessage);
    }
    
    return result;
}

CloudPointMapper::MappingResult CloudPointMapper::transformRealToImage(const QVector3D& realCoord, 
                                                                       InterpolationMethod method)
{
    MappingResult result;
    result.isValid = false;
    result.confidence = 0.0f;
    result.estimatedError = 999.0f;
    result.method = method;
    
    // Check if we have enough calibration points
    if (m_calibrationPoints.size() < 3) {
        result.errorMessage = "Need at least 3 calibration points for transformation";
        return result;
    }
    
    try {
        // Find nearest calibration points in real space
        QVector<int> nearestPoints;
        QVector<float> distances;
        
        for (int i = 0; i < m_calibrationPoints.size(); ++i) {
            float distance = calculateDistance(realCoord, m_calibrationPoints[i].realCoord);
            distances.append(distance);
        }
        
        // Sort by distance and take closest points
        QVector<int> sortedIndices;
        for (int i = 0; i < distances.size(); ++i) {
            sortedIndices.append(i);
        }
        
        std::sort(sortedIndices.begin(), sortedIndices.end(), [&](int a, int b) {
            return distances[a] < distances[b];
        });
        
        int maxPoints = qMin(4, sortedIndices.size());
        for (int i = 0; i < maxPoints; ++i) {
            nearestPoints.append(sortedIndices[i]);
        }
        
        // Perform reverse interpolation (real to image)
        QVector3D transformedPoint;
        
        // Use inverse distance weighting for reverse transformation
        QVector3D weightedSum(0, 0, 0);
        float totalWeight = 0.0f;
        
        for (int idx : nearestPoints) {
            float distance = calculateDistance(realCoord, m_calibrationPoints[idx].realCoord);
            float weight = 1.0f / (distance + 0.1f); // Small epsilon to avoid division by zero
            
            weightedSum += m_calibrationPoints[idx].imageCoord * weight;
            totalWeight += weight;
        }
        
        if (totalWeight > 0.0f) {
            transformedPoint = weightedSum / totalWeight;
        } else {
            result.errorMessage = "Could not compute reverse transformation";
            return result;
        }
        
        // Calculate confidence
        float totalDistance = 0.0f;
        float totalConfidence = 0.0f;
        
        for (int idx : nearestPoints) {
            float distance = calculateDistance(realCoord, m_calibrationPoints[idx].realCoord);
            float weight = 1.0f / (distance + 1.0f);
            totalDistance += distance * weight;
            totalConfidence += m_calibrationPoints[idx].confidence * weight;
        }
        
        result.transformedPoint = transformedPoint;
        result.confidence = totalConfidence / nearestPoints.size();
        result.estimatedError = totalDistance / nearestPoints.size();
        result.isValid = true;
        
    } catch (const std::exception& e) {
        result.errorMessage = QString("Reverse transformation failed: %1").arg(e.what());
        emit errorOccurred(result.errorMessage);
    }
    
    return result;
}

bool CloudPointMapper::buildMappingGrid(float gridResolution)
{
    if (m_calibrationPoints.size() < 3) {
        emit errorOccurred("Need at least 3 calibration points to build grid");
        return false;
    }
    
    m_gridResolution = gridResolution;
    
    // Update workspace bounds
    updateWorkspaceBounds();
    
    // Calculate grid dimensions
    calculateGridDimensions();
    
    // Clear existing grid
    m_mappingGrid.clear();
    m_mappingGrid.resize(m_gridHeight);
    
    // Build grid
    for (int y = 0; y < m_gridHeight; ++y) {
        m_mappingGrid[y].resize(m_gridWidth);
        for (int x = 0; x < m_gridWidth; ++x) {
            m_mappingGrid[y][x] = calculateGridCell(x, y);
        }
    }
    
    // Calculate statistics
    calculateMappingStatistics();
    
    qDebug() << "Built mapping grid:" << m_gridWidth << "x" << m_gridHeight << "cells";
    return true;
}

CloudPointMapper::MappingStats CloudPointMapper::validateMapping(float validationRatio)
{
    MappingStats stats;
    stats.totalPoints = m_calibrationPoints.size();
    stats.isValid = false;
    
    if (m_calibrationPoints.size() < 5) {
        stats.averageError = 999.0f;
        stats.maxError = 999.0f;
        stats.minError = 999.0f;
        stats.stdDeviation = 999.0f;
        stats.coverage = 0.0f;
        return stats;
    }
    
    // Randomly select points for validation
    int validationCount = qMax(1, (int)(m_calibrationPoints.size() * validationRatio));
    QVector<int> validationIndices;
    
    // Simple random selection
    for (int i = 0; i < validationCount; ++i) {
        int randomIndex = QRandomGenerator::global()->bounded(m_calibrationPoints.size());
        if (!validationIndices.contains(randomIndex)) {
            validationIndices.append(randomIndex);
        }
    }
    
    // Calculate errors for validation points
    QVector<float> errors;
    
    for (int idx : validationIndices) {
        float error = calculatePointError(idx, m_defaultMethod);
        errors.append(error);
    }
    
    if (!errors.isEmpty()) {
        // Calculate statistics
        stats.averageError = std::accumulate(errors.begin(), errors.end(), 0.0f) / errors.size();
        stats.maxError = *std::max_element(errors.begin(), errors.end());
        stats.minError = *std::min_element(errors.begin(), errors.end());
        
        // Calculate standard deviation
        float variance = 0.0f;
        for (float error : errors) {
            variance += qPow(error - stats.averageError, 2);
        }
        stats.stdDeviation = qSqrt(variance / errors.size());
        
        // Calculate coverage (simplified)
        stats.coverage = qMin(100.0f, (float)m_calibrationPoints.size() / 10.0f * 100.0f); // Simplified coverage calculation
        
        stats.workspaceMin = m_workspaceMin;
        stats.workspaceMax = m_workspaceMax;
        
        // Mapping is valid if average error is reasonable
        stats.isValid = (stats.averageError < 5.0f && stats.maxError < 20.0f);
    }
    
    m_currentStats = stats;
    emit validationComplete(stats);
    
    return stats;
}

bool CloudPointMapper::exportToVariableManager(const QString& variableName) const
{
    try {
        // Export calibration points
        QJsonArray pointsArray;
        for (const CalibrationPoint& point : m_calibrationPoints) {
            pointsArray.append(pointToJson(point));
        }
        
        QJsonObject mappingData;
        mappingData["points"] = pointsArray;
        mappingData["gridResolution"] = m_gridResolution;
        mappingData["workspaceMin"] = QJsonArray{m_workspaceMin.x(), m_workspaceMin.y(), m_workspaceMin.z()};
        mappingData["workspaceMax"] = QJsonArray{m_workspaceMax.x(), m_workspaceMax.y(), m_workspaceMax.z()};
        mappingData["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        
        // Store in VariableManager
        QJsonDocument doc(mappingData);
        QString jsonString = doc.toJson(QJsonDocument::Compact);
        
        VariableManager::instance().updateVar(variableName + "_mapping", jsonString);
        VariableManager::instance().updateVar(variableName + "_stats", QVariant::fromValue(m_currentStats));
        
        qDebug() << "Exported cloud point mapping to VariableManager:" << variableName;
        return true;
        
    } catch (const std::exception& e) {
        qDebug() << "Failed to export to VariableManager:" << e.what();
        return false;
    }
}

bool CloudPointMapper::importFromVariableManager(const QString& variableName)
{
    try {
        QVariant mappingVar = VariableManager::instance().getVar(variableName + "_mapping");
        if (!mappingVar.isValid()) {
            emit errorOccurred("No mapping data found in VariableManager");
            return false;
        }
        
        QString jsonString = mappingVar.toString();
        QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
        QJsonObject mappingData = doc.object();
        
        // Clear existing data
        clearMapping();
        
        // Import calibration points
        QJsonArray pointsArray = mappingData["points"].toArray();
        for (const QJsonValue& pointValue : pointsArray) {
            CalibrationPoint point = pointFromJson(pointValue.toObject());
            m_calibrationPoints.append(point);
        }
        
        // Import settings
        m_gridResolution = mappingData["gridResolution"].toDouble(10.0f);
        
        QJsonArray minArray = mappingData["workspaceMin"].toArray();
        if (minArray.size() >= 3) {
            m_workspaceMin = QVector3D(minArray[0].toDouble(), minArray[1].toDouble(), minArray[2].toDouble());
        }
        
        QJsonArray maxArray = mappingData["workspaceMax"].toArray();
        if (maxArray.size() >= 3) {
            m_workspaceMax = QVector3D(maxArray[0].toDouble(), maxArray[1].toDouble(), maxArray[2].toDouble());
        }
        
        // Rebuild grid
        if (m_calibrationPoints.size() >= 3) {
            buildMappingGrid(m_gridResolution);
        }
        
        emit mappingUpdated();
        
        qDebug() << "Imported cloud point mapping from VariableManager:" << variableName;
        qDebug() << "Loaded" << m_calibrationPoints.size() << "calibration points";
        
        return true;
        
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Failed to import from VariableManager: %1").arg(e.what()));
        return false;
    }
}

void CloudPointMapper::clearMapping()
{
    m_calibrationPoints.clear();
    m_mappingGrid.clear();
    
    // Reset stats
    m_currentStats.totalPoints = 0;
    m_currentStats.averageError = 0.0f;
    m_currentStats.maxError = 0.0f;
    m_currentStats.minError = 0.0f;
    m_currentStats.stdDeviation = 0.0f;
    m_currentStats.coverage = 0.0f;
    m_currentStats.isValid = false;
    
    emit mappingUpdated();
}

// Private methods implementation

void CloudPointMapper::updateWorkspaceBounds()
{
    if (m_calibrationPoints.isEmpty()) {
        return;
    }
    
    m_workspaceMin = m_calibrationPoints[0].imageCoord;
    m_workspaceMax = m_calibrationPoints[0].imageCoord;
    
    for (const CalibrationPoint& point : m_calibrationPoints) {
        // Update image coordinate bounds
        m_workspaceMin.setX(qMin(m_workspaceMin.x(), point.imageCoord.x()));
        m_workspaceMin.setY(qMin(m_workspaceMin.y(), point.imageCoord.y()));
        m_workspaceMin.setZ(qMin(m_workspaceMin.z(), point.imageCoord.z()));
        
        m_workspaceMax.setX(qMax(m_workspaceMax.x(), point.imageCoord.x()));
        m_workspaceMax.setY(qMax(m_workspaceMax.y(), point.imageCoord.y()));
        m_workspaceMax.setZ(qMax(m_workspaceMax.z(), point.imageCoord.z()));
    }
}

void CloudPointMapper::calculateGridDimensions()
{
    float width = m_workspaceMax.x() - m_workspaceMin.x();
    float height = m_workspaceMax.y() - m_workspaceMin.y();
    
    m_gridWidth = qMax(1, (int)(width / m_gridResolution)) + 1;
    m_gridHeight = qMax(1, (int)(height / m_gridResolution)) + 1;
}

QVector<int> CloudPointMapper::findNearestPoints(const QVector3D& point, int maxPoints)
{
    QVector<QPair<float, int>> distances;
    
    for (int i = 0; i < m_calibrationPoints.size(); ++i) {
        float distance = calculateDistance(point, m_calibrationPoints[i].imageCoord);
        distances.append(qMakePair(distance, i));
    }
    
    // Sort by distance
    std::sort(distances.begin(), distances.end());
    
    QVector<int> nearest;
    int count = qMin(maxPoints, distances.size());
    for (int i = 0; i < count; ++i) {
        nearest.append(distances[i].second);
    }
    
    return nearest;
}

float CloudPointMapper::calculateDistance(const QVector3D& p1, const QVector3D& p2)
{
    return (p1 - p2).length();
}

QVector3D CloudPointMapper::interpolateLinear(const QVector3D& point, const QVector<int>& nearestPoints)
{
    if (nearestPoints.size() < 2) {
        return QVector3D(0, 0, 0);
    }
    
    // Simple linear interpolation between two nearest points
    int idx1 = nearestPoints[0];
    int idx2 = nearestPoints[1];
    
    const CalibrationPoint& p1 = m_calibrationPoints[idx1];
    const CalibrationPoint& p2 = m_calibrationPoints[idx2];
    
    float d1 = calculateDistance(point, p1.imageCoord);
    float d2 = calculateDistance(point, p2.imageCoord);
    
    if (d1 + d2 == 0) {
        return p1.realCoord;
    }
    
    float w1 = d2 / (d1 + d2);
    float w2 = d1 / (d1 + d2);
    
    return p1.realCoord * w1 + p2.realCoord * w2;
}

QVector3D CloudPointMapper::interpolateBilinear(const QVector3D& point, const QVector<int>& nearestPoints)
{
    if (nearestPoints.size() < 3) {
        return interpolateLinear(point, nearestPoints);
    }
    
    // Inverse distance weighting
    QVector3D result(0, 0, 0);
    float totalWeight = 0.0f;
    
    for (int idx : nearestPoints) {
        float distance = calculateDistance(point, m_calibrationPoints[idx].imageCoord);
        float weight = 1.0f / (distance + 0.1f); // Small epsilon to avoid division by zero
        
        result += m_calibrationPoints[idx].realCoord * weight;
        totalWeight += weight;
    }
    
    if (totalWeight > 0.0f) {
        result /= totalWeight;
    }
    
    return result;
}

QVector3D CloudPointMapper::interpolateCubicSpline(const QVector3D& point, const QVector<int>& nearestPoints)
{
    // Simplified cubic spline - fallback to bilinear for now
    return interpolateBilinear(point, nearestPoints);
}

QVector3D CloudPointMapper::interpolateRadialBasis(const QVector3D& point, const QVector<int>& nearestPoints)
{
    // Simplified radial basis function - fallback to bilinear for now
    return interpolateBilinear(point, nearestPoints);
}

QVector3D CloudPointMapper::interpolateKriging(const QVector3D& point, const QVector<int>& nearestPoints)
{
    // Simplified Kriging - fallback to bilinear for now
    return interpolateBilinear(point, nearestPoints);
}

void CloudPointMapper::calculateMappingStatistics()
{
    m_currentStats.totalPoints = m_calibrationPoints.size();
    m_currentStats.workspaceMin = m_workspaceMin;
    m_currentStats.workspaceMax = m_workspaceMax;
    
    if (m_calibrationPoints.size() < 3) {
        m_currentStats.isValid = false;
        return;
    }
    
    // Calculate coverage based on workspace area
    float workspaceArea = (m_workspaceMax.x() - m_workspaceMin.x()) * (m_workspaceMax.y() - m_workspaceMin.y());
    float pointDensity = m_calibrationPoints.size() / workspaceArea;
    m_currentStats.coverage = qMin(100.0f, pointDensity * 1000.0f); // Simplified coverage calculation
    
    // Basic validation
    m_currentStats.isValid = (m_calibrationPoints.size() >= 3 && m_currentStats.coverage > 10.0f);
    
    // Calculate basic error estimates
    if (m_calibrationPoints.size() >= 4) {
        validateMapping(0.25f); // Use 25% for validation
    }
}

QJsonObject CloudPointMapper::pointToJson(const CalibrationPoint& point) const
{
    QJsonObject json;
    json["imageCoord"] = QJsonArray{point.imageCoord.x(), point.imageCoord.y(), point.imageCoord.z()};
    json["realCoord"] = QJsonArray{point.realCoord.x(), point.realCoord.y(), point.realCoord.z()};
    json["confidence"] = point.confidence;
    json["timestamp"] = point.timestamp.toString(Qt::ISODate);
    json["error"] = point.error;
    json["label"] = point.label;
    json["isKeyPoint"] = point.isKeyPoint;
    return json;
}

CloudPointMapper::CalibrationPoint CloudPointMapper::pointFromJson(const QJsonObject& json) const
{
    CalibrationPoint point;
    
    QJsonArray imageArray = json["imageCoord"].toArray();
    if (imageArray.size() >= 3) {
        point.imageCoord = QVector3D(imageArray[0].toDouble(), imageArray[1].toDouble(), imageArray[2].toDouble());
    }
    
    QJsonArray realArray = json["realCoord"].toArray();
    if (realArray.size() >= 3) {
        point.realCoord = QVector3D(realArray[0].toDouble(), realArray[1].toDouble(), realArray[2].toDouble());
    }
    
    point.confidence = json["confidence"].toDouble(1.0f);
    point.timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
    point.error = json["error"].toDouble(0.0f);
    point.label = json["label"].toString();
    point.isKeyPoint = json["isKeyPoint"].toBool(false);
    
    return point;
}

bool CloudPointMapper::validatePoint(const CalibrationPoint& point) const
{
    // Accept (0,0[,0]) as valid coordinates. Validate finiteness and reasonable ranges instead.
    auto finite = [](float v) { return qIsFinite(v); };
    if (!finite(point.imageCoord.x()) || !finite(point.imageCoord.y()) || !finite(point.imageCoord.z())) {
        return false;
    }
    if (!finite(point.realCoord.x()) || !finite(point.realCoord.y()) || !finite(point.realCoord.z())) {
        return false;
    }

    // Check for reasonable coordinate ranges (expandable per project)
    auto inRange = [](float v) { return qAbs(v) <= 1000000.0f; };
    if (!inRange(point.imageCoord.x()) || !inRange(point.imageCoord.y())) {
        return false;
    }
    if (!inRange(point.realCoord.x()) || !inRange(point.realCoord.y())) {
        return false;
    }

    return true;
}

float CloudPointMapper::calculatePointError(int pointIndex, InterpolationMethod method)
{
    if (pointIndex < 0 || pointIndex >= m_calibrationPoints.size()) {
        return 999.0f;
    }
    
    // Create a temporary mapper without this point
    QVector<CalibrationPoint> tempPoints = m_calibrationPoints;
    tempPoints.removeAt(pointIndex);
    
    // Find nearest points to this one
    QVector<int> nearestPoints;
    QVector<float> distances;
    
    for (int i = 0; i < tempPoints.size(); ++i) {
        float distance = calculateDistance(m_calibrationPoints[pointIndex].imageCoord, tempPoints[i].imageCoord);
        distances.append(distance);
        nearestPoints.append(i);
    }
    
    // Sort by distance
    for (int i = 0; i < distances.size() - 1; ++i) {
        for (int j = i + 1; j < distances.size(); ++j) {
            if (distances[i] > distances[j]) {
                distances.swapItemsAt(i, j);
                nearestPoints.swapItemsAt(i, j);
            }
        }
    }
    
    // Take up to 4 nearest points
    int maxPoints = qMin(4, nearestPoints.size());
    QVector<int> selectedPoints;
    for (int i = 0; i < maxPoints; ++i) {
        selectedPoints.append(nearestPoints[i]);
    }
    
    if (selectedPoints.size() < 2) {
        return 999.0f;
    }
    
    // Perform interpolation with remaining points
    QVector3D interpolatedReal(0, 0, 0);
    float totalWeight = 0.0f;
    
    for (int idx : selectedPoints) {
        float distance = calculateDistance(m_calibrationPoints[pointIndex].imageCoord, tempPoints[idx].imageCoord);
        float weight = 1.0f / (distance + 0.1f);
        
        interpolatedReal += tempPoints[idx].realCoord * weight;
        totalWeight += weight;
    }
    
    if (totalWeight > 0.0f) {
        interpolatedReal /= totalWeight;
    }
    
    // Calculate error
    float error = calculateDistance(interpolatedReal, m_calibrationPoints[pointIndex].realCoord);
    return error;
}

// Accessor methods
const QVector<CloudPointMapper::CalibrationPoint>& CloudPointMapper::getCalibrationPoints() const
{
    return m_calibrationPoints;
}

const CloudPointMapper::CalibrationPoint& CloudPointMapper::getCalibrationPoint(int index) const
{
    static CalibrationPoint emptyPoint;
    if (index >= 0 && index < m_calibrationPoints.size()) {
        return m_calibrationPoints[index];
    }
    return emptyPoint;
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
    m_gridResolution = resolution;
    if (m_autoRebuild && m_calibrationPoints.size() >= 3) {
        buildMappingGrid(resolution);
    }
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

CloudPointMapper::GridCell CloudPointMapper::calculateGridCell(int gridX, int gridY)
{
    GridCell cell;
    
    // Calculate cell center in image coordinates
    float cellX = m_workspaceMin.x() + (gridX + 0.5f) * m_gridResolution;
    float cellY = m_workspaceMin.y() + (gridY + 0.5f) * m_gridResolution;
    cell.center = QVector3D(cellX, cellY, 0);
    
    // Find nearest calibration points
    QVector<int> nearestPoints = findNearestPoints(cell.center, 4);
    cell.pointIndices = nearestPoints;
    
    if (!nearestPoints.isEmpty()) {
        // Calculate local transformation
        cell.transform = interpolateBilinear(cell.center, nearestPoints);
        
        // Calculate confidence based on distance to nearest points
        float totalDistance = 0.0f;
        for (int idx : nearestPoints) {
            totalDistance += calculateDistance(cell.center, m_calibrationPoints[idx].imageCoord);
        }
        cell.confidence = 1.0f / (totalDistance / nearestPoints.size() + 1.0f);
    } else {
        cell.transform = QVector3D(0, 0, 0);
        cell.confidence = 0.0f;
    }
    
    return cell;
}

void CloudPointMapper::optimizeGrid()
{
    // Future implementation for grid optimization
    // This could include adaptive mesh refinement, error-based grid density adjustment, etc.
}

bool CloudPointMapper::saveToFile(const QString& fileName) const
{
    try {
        QJsonArray pointsArray;
        for (const CalibrationPoint& point : m_calibrationPoints) {
            pointsArray.append(pointToJson(point));
        }
        
        QJsonObject mappingData;
        mappingData["points"] = pointsArray;
        mappingData["gridResolution"] = m_gridResolution;
        mappingData["workspaceMin"] = QJsonArray{m_workspaceMin.x(), m_workspaceMin.y(), m_workspaceMin.z()};
        mappingData["workspaceMax"] = QJsonArray{m_workspaceMax.x(), m_workspaceMax.y(), m_workspaceMax.z()};
        mappingData["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        mappingData["version"] = "1.0";
        
        QJsonDocument doc(mappingData);
        
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
            return true;
        }
        
    } catch (const std::exception& e) {
        qDebug() << "Failed to save mapping to file:" << e.what();
    }
    
    return false;
}

bool CloudPointMapper::loadFromFile(const QString& fileName)
{
    try {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            emit errorOccurred("Could not open file for reading");
            return false;
        }
        
        QByteArray data = file.readAll();
        file.close();
        
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject mappingData = doc.object();
        
        // Clear existing data
        clearMapping();
        
        // Load calibration points
        QJsonArray pointsArray = mappingData["points"].toArray();
        for (const QJsonValue& pointValue : pointsArray) {
            CalibrationPoint point = pointFromJson(pointValue.toObject());
            m_calibrationPoints.append(point);
        }
        
        // Load settings
        m_gridResolution = mappingData["gridResolution"].toDouble(10.0f);
        
        QJsonArray minArray = mappingData["workspaceMin"].toArray();
        if (minArray.size() >= 3) {
            m_workspaceMin = QVector3D(minArray[0].toDouble(), minArray[1].toDouble(), minArray[2].toDouble());
        }
        
        QJsonArray maxArray = mappingData["workspaceMax"].toArray();
        if (maxArray.size() >= 3) {
            m_workspaceMax = QVector3D(maxArray[0].toDouble(), maxArray[1].toDouble(), maxArray[2].toDouble());
        }
        
        // Rebuild grid
        if (m_calibrationPoints.size() >= 3) {
            buildMappingGrid(m_gridResolution);
        }
        
        emit mappingUpdated();
        
        qDebug() << "Loaded cloud point mapping from file:" << fileName;
        qDebug() << "Loaded" << m_calibrationPoints.size() << "calibration points";
        
        return true;
        
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Failed to load from file: %1").arg(e.what()));
        return false;
    }
} 
