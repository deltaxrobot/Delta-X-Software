#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QString>
#include <QPointF>
#include <QVector3D>
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>

/**
 * @brief Utility class for validating user input from UI controls
 * 
 * This class provides static methods to validate various input types
 * commonly used in Point Tool operations, with proper error handling
 * and user feedback.
 */
class InputValidator
{
public:
    /**
     * @brief Validates and parses float value from string
     * @param text Input string to validate
     * @param result Output parameter for parsed float value
     * @param fieldName Name of the field for error messages
     * @return true if valid, false otherwise
     */
    static bool validateFloat(const QString& text, float& result, const QString& fieldName = "");
    
    /**
     * @brief Validates and parses 2D point from two string inputs
     * @param xText X coordinate string
     * @param yText Y coordinate string
     * @param point Output parameter for parsed QPointF
     * @param pointName Name of the point for error messages
     * @return true if valid, false otherwise
     */
    static bool validatePoint2D(const QString& xText, const QString& yText, QPointF& point, const QString& pointName = "");
    
    /**
     * @brief Validates and parses 3D point from three string inputs
     * @param xText X coordinate string
     * @param yText Y coordinate string
     * @param zText Z coordinate string
     * @param point Output parameter for parsed QVector3D
     * @param pointName Name of the point for error messages
     * @return true if valid, false otherwise
     */
    static bool validatePoint3D(const QString& xText, const QString& yText, const QString& zText, QVector3D& point, const QString& pointName = "");
    
    /**
     * @brief Validates float input from QLineEdit
     * @param lineEdit QLineEdit control to validate
     * @param result Output parameter for parsed float value
     * @param fieldName Name of the field for error messages
     * @return true if valid, false otherwise
     */
    static bool validateLineEditFloat(QLineEdit* lineEdit, float& result, const QString& fieldName = "");
    
    /**
     * @brief Validates 2D point from QLineEdit controls
     * @param xLineEdit X coordinate QLineEdit
     * @param yLineEdit Y coordinate QLineEdit
     * @param point Output parameter for parsed QPointF
     * @param pointName Name of the point for error messages
     * @return true if valid, false otherwise
     */
    static bool validateLineEditPoint2D(QLineEdit* xLineEdit, QLineEdit* yLineEdit, QPointF& point, const QString& pointName = "");
    
    /**
     * @brief Validates 3D point from QLineEdit controls
     * @param xLineEdit X coordinate QLineEdit
     * @param yLineEdit Y coordinate QLineEdit
     * @param zLineEdit Z coordinate QLineEdit
     * @param point Output parameter for parsed QVector3D
     * @param pointName Name of the point for error messages
     * @return true if valid, false otherwise
     */
    static bool validateLineEditPoint3D(QLineEdit* xLineEdit, QLineEdit* yLineEdit, QLineEdit* zLineEdit, QVector3D& point, const QString& pointName = "");
    
    /**
     * @brief Checks if input string is empty or whitespace only
     * @param text Input string to check
     * @return true if empty or whitespace only
     */
    static bool isEmpty(const QString& text);
    
    /**
     * @brief Shows error message to user
     * @param parent Parent widget for message box
     * @param message Error message to display
     * @param title Title for message box
     */
    static void showError(QWidget* parent, const QString& message, const QString& title = "Input Error");
    
    /**
     * @brief Shows validation error for specific field
     * @param parent Parent widget for message box
     * @param fieldName Name of the field with error
     * @param expectedType Expected data type (e.g., "number", "coordinate")
     */
    static void showValidationError(QWidget* parent, const QString& fieldName, const QString& expectedType = "number");

private:
    InputValidator() = default; // Prevent instantiation
};

#endif // INPUTVALIDATOR_H 