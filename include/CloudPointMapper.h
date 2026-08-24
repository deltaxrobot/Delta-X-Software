#ifndef CLOUDPOINTMAPPER_H
#define CLOUDPOINTMAPPER_H

#include <QObject>
#include <QVector3D>
#include <QPointF>
#include <QVector>
#include <QMap>
#include <QMatrix4x4>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>

/**
 * @brief Advanced Cloud Point Mapping system for high-precision robot positioning
 * 
 * This class implements sophisticated multi-point calibration using:
 * - Grid-based interpolation for smooth coordinate transformation
 * - Statistical error correction and validation
 * - 3D point cloud support for complex workspaces
 * - Adaptive mesh refinement for critical areas
 * - Real-time accuracy assessment
 */
class CloudPointMapper : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Calibration point structure
     */
    struct CalibrationPoint {
        QVector3D imageCoord;      ///< Image/pixel coordinates (x,y,z)
        QVector3D realCoord;       ///< Real-world coordinates (x,y,z)
        float confidence = 1.0f;   ///< Confidence level (0.0-1.0)
        QDateTime timestamp;       ///< When this point was calibrated
        float error = 0.0f;        ///< Measured error from validation
        QString label;            ///< Optional label for identification
        bool isKeyPoint = false;   ///< Whether this is a key calibration point
    };

    /**
     * @brief Mapping grid cell for interpolation
     */
    struct GridCell {
        QVector3D center;         ///< Grid cell center
        QVector3D transform;      ///< Local transformation vector
        float confidence;         ///< Interpolation confidence
        QVector<int> pointIndices; ///< Indices of contributing points
        QMatrix4x4 localMatrix;   ///< Local transformation matrix
    };

    /**
     * @brief Mapping statistics and quality metrics
     */
    struct MappingStats {
        int totalPoints = 0;       ///< Total calibration points
        float averageError = 0.0f; ///< Average mapping error (mm)
        float maxError = 0.0f;     ///< Maximum error found
        float minError = 0.0f;     ///< Minimum error found
        float stdDeviation = 0.0f; ///< Standard deviation of errors
        float coverage = 0.0f;     ///< Spatial distribution score (0-100%)
        QVector3D workspaceMin;   ///< Minimum workspace bounds
        QVector3D workspaceMax;   ///< Maximum workspace bounds
        bool hasBeenValidated = false; ///< Whether leave-one-out validation was run
        bool isValid = false;      ///< Whether mapping is valid for use
    };

    /**
     * @brief Interpolation methods
     */
    enum InterpolationMethod {
        LINEAR = 0,               ///< Linear interpolation
        BILINEAR = 1,             ///< Inverse-distance weighting (legacy name)
        CUBIC_SPLINE = 2,         ///< Reserved; rejected until implemented
        RADIAL_BASIS = 3,         ///< Thin-plate radial basis interpolation
        KRIGING = 4               ///< Reserved; rejected until implemented
    };

    /**
     * @brief Mapping result structure
     */
    struct MappingResult {
        QVector3D transformedPoint;  ///< Transformed coordinates
        float confidence = 0.0f;     ///< Transformation confidence
        float estimatedError = 0.0f; ///< Estimated error in mm
        QString errorMessage;        ///< Error description if failed
        bool isValid = false;         ///< Whether transformation succeeded
        InterpolationMethod method = BILINEAR; ///< Method used for interpolation
    };

public:
    explicit CloudPointMapper(QObject *parent = nullptr);
    ~CloudPointMapper();

    /**
     * @brief Add a calibration point to the cloud
     * @param imageCoord Image coordinates
     * @param realCoord Real-world coordinates
     * @param confidence Confidence level (0.0-1.0)
     * @param label Optional label
     * @return Point index, or -1 if failed
     */
    int addCalibrationPoint(const QVector3D& imageCoord, const QVector3D& realCoord, 
                           float confidence = 1.0f, const QString& label = "");

    /**
     * @brief Remove a calibration point
     * @param index Point index to remove
     * @return true if successful
     */
    bool removeCalibrationPoint(int index);

    /**
     * @brief Update an existing calibration point
     * @param index Point index
     * @param imageCoord New image coordinates
     * @param realCoord New real coordinates
     * @param confidence New confidence level
     * @return true if successful
     */
    bool updateCalibrationPoint(int index, const QVector3D& imageCoord,
                               const QVector3D& realCoord, float confidence = 1.0f,
                               const QString& label = QString());

    /**
     * @brief Transform image coordinates to real-world coordinates
     * @param imageCoord Image coordinates to transform
     * @param method Interpolation method to use
     * @return MappingResult with transformed coordinates and confidence
     */
    MappingResult transformImageToReal(const QVector3D& imageCoord, 
                                      InterpolationMethod method = BILINEAR);

    /**
     * @brief Transform real-world coordinates to image coordinates
     * @param realCoord Real coordinates to transform
     * @param method Interpolation method to use
     * @return MappingResult with transformed coordinates and confidence
     */
    MappingResult transformRealToImage(const QVector3D& realCoord, 
                                      InterpolationMethod method = BILINEAR);

    /**
     * @brief Build/rebuild the mapping grid
     * @param gridResolution Grid resolution (cells per unit)
     * @return true if successful
     */
    bool buildMappingGrid(float gridResolution = 10.0f);

    /**
     * @brief Validate mapping accuracy using cross-validation
     * @param validationRatio Percentage of points to use for validation
     * @return MappingStats with validation results
     */
    MappingStats validateMapping(float validationRatio = 0.2f);

    /**
     * @brief Get current mapping statistics
     * @return MappingStats structure
     */
    MappingStats getMappingStats() const;

    /**
     * @brief Save mapping data to JSON
     * @param fileName File path to save
     * @return true if successful
     */
    bool saveToFile(const QString& fileName) const;

    /**
     * @brief Load mapping data from JSON
     * @param fileName File path to load
     * @return true if successful
     */
    bool loadFromFile(const QString& fileName);

    /**
     * @brief Export mapping data to VariableManager
     * @param variableName Base variable name
     * @return true if successful
     */
    bool exportToVariableManager(const QString& variableName) const;

    /**
     * @brief Import mapping data from VariableManager
     * @param variableName Base variable name
     * @return true if successful
     */
    bool importFromVariableManager(const QString& variableName);

    /**
     * @brief Clear all calibration points
     */
    void clearMapping();

    /**
     * @brief Get all calibration points
     * @return Vector of calibration points
     */
    const QVector<CalibrationPoint>& getCalibrationPoints() const;

    /**
     * @brief Get calibration point by index
     * @param index Point index
     * @return CalibrationPoint reference
     */
    const CalibrationPoint& getCalibrationPoint(int index) const;

    /**
     * @brief Get number of calibration points
     * @return Point count
     */
    int getPointCount() const;

    /**
     * @brief Set grid resolution for interpolation
     * @param resolution Grid resolution (cells per unit)
     */
    void setGridResolution(float resolution);

    /**
     * @brief Get current grid resolution
     * @return Grid resolution
     */
    float getGridResolution() const;

    /**
     * @brief Enable/disable automatic grid rebuilding
     * @param enabled Auto-rebuild flag
     */
    void setAutoRebuild(bool enabled);

    /**
     * @brief Check if auto-rebuild is enabled
     * @return Auto-rebuild status
     */
    bool isAutoRebuildEnabled() const;

    void setDefaultInterpolationMethod(InterpolationMethod method);
    InterpolationMethod defaultInterpolationMethod() const;
    static bool isMethodSupported(InterpolationMethod method);
    void setValidationThresholds(float maximumAverageError, float maximumPointError);

signals:
    /**
     * @brief Emitted when mapping is updated
     */
    void mappingUpdated();

    /**
     * @brief Emitted when validation is complete
     * @param stats Validation statistics
     */
    void validationComplete(const MappingStats& stats);

    /**
     * @brief Emitted when an error occurs
     * @param error Error message
     */
    void errorOccurred(const QString& error);

private:
    // Core data structures
    QVector<CalibrationPoint> m_calibrationPoints;  ///< All calibration points
    QVector<QVector<GridCell>> m_mappingGrid;       ///< 2D interpolation grid
    MappingStats m_currentStats;                    ///< Current mapping statistics
    
    // Configuration
    float m_gridResolution;                         ///< Grid cells per unit
    bool m_autoRebuild;                            ///< Auto-rebuild grid flag
    InterpolationMethod m_defaultMethod;           ///< Default interpolation method
    float m_maximumAverageError;                   ///< Validation threshold in real units
    float m_maximumPointError;                     ///< Validation threshold in real units
    
    // Workspace bounds
    QVector3D m_workspaceMin;                      ///< Minimum workspace bounds
    QVector3D m_workspaceMax;                      ///< Maximum workspace bounds
    
    // Grid dimensions
    int m_gridWidth;                               ///< Grid width in cells
    int m_gridHeight;                              ///< Grid height in cells
    
    // Private methods
    void updateWorkspaceBounds();
    void calculateGridDimensions();
    GridCell calculateGridCell(int gridX, int gridY);
    QVector<int> findNearestPoints(const QVector3D& point, int maxPoints = 8,
                                   bool reverse = false, int excludedIndex = -1) const;
    QVector<int> findNearestPointsGlobal(const QVector3D& point, int maxPoints,
                                         bool reverse, int excludedIndex) const;
    float calculateDistance(const QVector3D& p1, const QVector3D& p2);
    MappingResult transformInternal(const QVector3D& point, InterpolationMethod method,
                                    bool reverse, int excludedIndex = -1) const;
    bool interpolateLocalAffine(const QVector3D& point, const QVector<int>& nearestPoints,
                                bool reverse, QVector3D& result) const;
    bool interpolateInverseDistance(const QVector3D& point, const QVector<int>& nearestPoints,
                                    bool reverse, QVector3D& result) const;
    bool interpolateRadialBasis(const QVector3D& point, bool reverse, int excludedIndex,
                                QVector3D& result) const;
    float calculateCoverage() const;
    float characteristicSpacing(bool reverse = false, int excludedIndex = -1) const;
    void calculateMappingStatistics();
    QJsonObject mappingToJson() const;
    bool parseMappingJson(const QByteArray& data, QVector<CalibrationPoint>& points,
                          float& resolution, InterpolationMethod& method,
                          float& maximumAverageError, float& maximumPointError,
                          QString& error) const;
    void commitLoadedMapping(const QVector<CalibrationPoint>& points, float resolution,
                             InterpolationMethod method, float maximumAverageError,
                             float maximumPointError);
    QJsonObject pointToJson(const CalibrationPoint& point) const;
    CalibrationPoint pointFromJson(const QJsonObject& json) const;
    bool validatePoint(const CalibrationPoint& point) const;
    void optimizeGrid();
    float calculatePointError(int pointIndex, InterpolationMethod method);
};

Q_DECLARE_METATYPE(CloudPointMapper::MappingStats)

#endif // CLOUDPOINTMAPPER_H
