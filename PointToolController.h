#ifndef POINTTOOLCONTROLLER_H
#define POINTTOOLCONTROLLER_H

#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QClipboard>
#include <QApplication>
#include <QRegularExpression>
#include <QMetaType>
#include <opencv2/opencv.hpp>
#include "PointCalculator.h"
#include "InputValidator.h"
#include "CloudPointToolController.h"

// Forward declarations
class RobotWindow;

// Declare cv::Mat as Qt metatype
Q_DECLARE_METATYPE(cv::Mat)

/**
 * @brief Controller class for Point Tool UI operations
 * 
 * This class manages UI interactions and coordinates between
 * the UI components and business logic, following MVC pattern.
 * Now includes integration with advanced Cloud Point Mapping.
 */
class PointToolController : public QObject
{
    Q_OBJECT

public:
    explicit PointToolController(RobotWindow* parent = nullptr);
    ~PointToolController() = default;

    /**
     * @brief Sets the parent RobotWindow instance
     * @param parent Pointer to RobotWindow
     */
    void setParent(RobotWindow* parent);

    /**
     * @brief Initialize Point Tool UI with Cloud Point Mapping
     * @param parentWidget Parent widget for UI setup
     */
    void initializeUI(QWidget* parentWidget);

    /**
     * @brief Get the cloud point tool controller
     * @return CloudPointToolController pointer
     */
    CloudPointToolController* getCloudPointController() const;

    /**
     * @brief Handles mapping matrix calculation
     * @return true if calculation succeeded
     */
    bool calculateMappingMatrix();

    /**
     * @brief Handles perspective matrix calculation  
     * @return true if calculation succeeded
     */
    bool calculatePerspectiveMatrix();

    /**
     * @brief Handles vector calculation
     * @return true if calculation succeeded
     */
    bool calculateVector();

    /**
     * @brief Handles test point calculation
     * @return true if calculation succeeded
     */
    bool calculateTestPoint();

    /**
     * @brief Updates test tracking point position
     * @param testPoint Vector to add to current position
     */
    void updateTestPoint(const QVector3D& testPoint);

    /**
     * @brief Moves test tracking point based on direction and distance
     */
    void moveTestTrackingPoint();

    /**
     * @brief Pastes clipboard values to specified point controls
     * @param xEdit X coordinate line edit
     * @param yEdit Y coordinate line edit  
     * @param zEdit Z coordinate line edit (optional)
     */
    void pastePointValues(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit = nullptr);

    /**
     * @brief Sets current robot position to specified controls
     * @param xEdit X coordinate line edit
     * @param yEdit Y coordinate line edit
     * @param zEdit Z coordinate line edit
     */
    void setCurrentRobotPosition(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit);

    /**
     * @brief Transform point using cloud point mapping
     * @param imageCoord Image coordinates
     * @param method Interpolation method
     * @return Transformed real-world coordinates
     */
    QVector3D transformPointUsingCloudMapping(const QVector3D& imageCoord, int method = 1);

    /**
     * @brief Check if cloud point mapping is available and valid
     * @return true if cloud mapping can be used
     */
    bool isCloudMappingAvailable() const;

    /**
     * @brief Get mapping statistics from cloud point mapper
     * @return Mapping statistics string
     */
    QString getCloudMappingStats() const;

    /**
     * @brief Export cloud mapping to VariableManager with specified name
     * @param variableName Variable name to use
     * @return true if successful
     */
    bool exportCloudMappingToVariables(const QString& variableName);

    /**
     * @brief Import cloud mapping from VariableManager
     * @param variableName Variable name to load from
     * @return true if successful
     */
    bool importCloudMappingFromVariables(const QString& variableName);

private slots:
    /**
     * @brief Handle cloud mapping update
     */
    void onCloudMappingUpdated();

    /**
     * @brief Handle completion of async operations
     */
    void onCalculationCompleted();

private:
    RobotWindow* m_parent;                          ///< Parent window
    PointCalculator* m_calculator;                  ///< Business logic calculator
    CloudPointToolController* m_cloudPointController; ///< Cloud point mapping controller
    QClipboard* m_clipboard;                        ///< System clipboard
    
    // Store global transformation data
    QTransform m_lastMappingTransform;              ///< Last calculated mapping transform
    QMatrix m_lastMappingMatrix;                    ///< Last calculated mapping matrix
    cv::Mat m_lastPerspectiveMatrix;                ///< Last calculated perspective matrix
    QVector3D m_lastCalculatedVector;               ///< Last calculated vector
    
    // Cloud mapping integration
    bool m_useCloudMapping;                         ///< Whether to use cloud mapping
    QString m_defaultCloudMappingVariable;          ///< Default variable name for cloud mapping
    
    // Private methods
    void showError(const QString& message);
    void showSuccess(const QString& message);
    void updateDisplayLabel(QLabel* label, const QString& text);
    bool validateAndExtractPoint2D(QLineEdit* xEdit, QLineEdit* yEdit, QPointF& point, const QString& pointName);
    bool validateAndExtractPoint3D(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit, QVector3D& point, const QString& pointName);
    bool validateAndExtractFloat(QLineEdit* edit, float& value, const QString& fieldName);
    QTransform getStoredMatrix(const QString& matrixName);
    void storeMatrix(const QString& matrixName, const QTransform& transform);
    QVector3D getStoredVector(const QString& vectorName);
    void storeVector(const QString& vectorName, const QVector3D& vector);
    bool parseClipboardPoint(const QString& clipboardText, float& x, float& y, float& z);
    void setFormattedValue(QLineEdit* edit, float value);
    
    // Cloud mapping helpers
    void setupCloudMappingIntegration();
    bool shouldUseCloudMapping() const;
    QVector3D fallbackToTraditionalMapping(const QVector3D& imageCoord);
};

#endif // POINTTOOLCONTROLLER_H 