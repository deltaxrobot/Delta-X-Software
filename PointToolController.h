#ifndef POINTTOOLCONTROLLER_H
#define POINTTOOLCONTROLLER_H

#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QClipboard>
#include <QApplication>
#include <QRegularExpression>
#include "PointCalculator.h"
#include "InputValidator.h"

// Forward declarations
class RobotWindow;

/**
 * @brief Controller class for Point Tool UI operations
 * 
 * This class manages UI interactions and coordinates between
 * the UI components and business logic, following MVC pattern.
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
     * @brief Copies current robot position to specified controls
     * @param xEdit X coordinate line edit
     * @param yEdit Y coordinate line edit
     * @param zEdit Z coordinate line edit
     */
    void setCurrentRobotPosition(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit);

    /**
     * @brief Gets stored transformation matrix by name
     * @param matrixName Name of the stored matrix
     * @return QTransform matrix or identity if not found
     */
    QTransform getStoredMatrix(const QString& matrixName);

    /**
     * @brief Stores transformation matrix with given name
     * @param matrixName Name to store matrix under
     * @param transform Matrix to store
     */
    void storeMatrix(const QString& matrixName, const QTransform& transform);

    /**
     * @brief Gets stored vector by name
     * @param vectorName Name of the stored vector
     * @return QVector3D vector or zero vector if not found
     */
    QVector3D getStoredVector(const QString& vectorName);

    /**
     * @brief Stores vector with given name
     * @param vectorName Name to store vector under
     * @param vector Vector to store
     */
    void storeVector(const QString& vectorName, const QVector3D& vector);

private slots:
    /**
     * @brief Internal slot for handling calculation results
     */
    void onCalculationCompleted();

private:
    /**
     * @brief Shows error message to user
     * @param message Error message to display
     */
    void showError(const QString& message);

    /**
     * @brief Shows success message to user
     * @param message Success message to display
     */
    void showSuccess(const QString& message);

    /**
     * @brief Updates display label with result text
     * @param label Label to update
     * @param text Text to display
     */
    void updateDisplayLabel(QLabel* label, const QString& text);

    /**
     * @brief Validates and extracts 2D point from line edits
     * @param xEdit X coordinate line edit
     * @param yEdit Y coordinate line edit
     * @param point Output point
     * @param pointName Name for error messages
     * @return true if validation succeeded
     */
    bool validateAndExtractPoint2D(QLineEdit* xEdit, QLineEdit* yEdit, QPointF& point, const QString& pointName);

    /**
     * @brief Validates and extracts 3D point from line edits
     * @param xEdit X coordinate line edit
     * @param yEdit Y coordinate line edit
     * @param zEdit Z coordinate line edit
     * @param point Output point
     * @param pointName Name for error messages
     * @return true if validation succeeded
     */
    bool validateAndExtractPoint3D(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit, QVector3D& point, const QString& pointName);

    /**
     * @brief Validates and extracts float value from line edit
     * @param edit Line edit control
     * @param value Output value
     * @param fieldName Name for error messages
     * @return true if validation succeeded
     */
    bool validateAndExtractFloat(QLineEdit* edit, float& value, const QString& fieldName);

    /**
     * @brief Sets float value to line edit with formatting
     * @param edit Line edit control
     * @param value Value to set
     * @param precision Decimal precision
     */
    void setFormattedValue(QLineEdit* edit, float value, int precision = 6);

    /**
     * @brief Parses clipboard content for point values
     * @param text Clipboard text
     * @param x Output X value
     * @param y Output Y value
     * @param z Output Z value
     * @return true if parsing succeeded
     */
    bool parseClipboardPoint(const QString& text, float& x, float& y, float& z);

private:
    RobotWindow* m_parent;                  ///< Parent RobotWindow instance
    PointCalculator* m_calculator;          ///< Business logic calculator
    QClipboard* m_clipboard;                ///< System clipboard
    
    // Store global transformation data
    QTransform m_lastMappingTransform;      ///< Last calculated mapping transform
    QMatrix m_lastMappingMatrix;            ///< Last calculated mapping matrix
    cv::Mat m_lastPerspectiveMatrix;        ///< Last calculated perspective matrix
    QVector3D m_lastCalculatedVector;       ///< Last calculated vector
};

#endif // POINTTOOLCONTROLLER_H 