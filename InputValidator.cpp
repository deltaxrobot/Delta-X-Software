#include "InputValidator.h"
#include <QRegularExpression>
#include <cmath>

#ifdef _WIN32
#include <float.h>
#define isnan _isnan
#define isinf !_finite
#endif

bool InputValidator::validateFloat(const QString& text, float& result, const QString& fieldName)
{
    if (isEmpty(text)) {
        return false;
    }
    
    bool ok;
    result = text.toFloat(&ok);
    
    if (!ok) {
        return false;
    }
    
    // Check for valid numeric range
    if (isnan(result) || isinf(result)) {
        return false;
    }
    
    return true;
}

bool InputValidator::validatePoint2D(const QString& xText, const QString& yText, QPointF& point, const QString& pointName)
{
    float x, y;
    
    if (!validateFloat(xText, x, pointName + " X")) {
        return false;
    }
    
    if (!validateFloat(yText, y, pointName + " Y")) {
        return false;
    }
    
    point = QPointF(x, y);
    return true;
}

bool InputValidator::validatePoint3D(const QString& xText, const QString& yText, const QString& zText, QVector3D& point, const QString& pointName)
{
    float x, y, z;
    
    if (!validateFloat(xText, x, pointName + " X")) {
        return false;
    }
    
    if (!validateFloat(yText, y, pointName + " Y")) {
        return false;
    }
    
    if (!validateFloat(zText, z, pointName + " Z")) {
        return false;
    }
    
    point = QVector3D(x, y, z);
    return true;
}

bool InputValidator::validateLineEditFloat(QLineEdit* lineEdit, float& result, const QString& fieldName)
{
    if (!lineEdit) {
        return false;
    }
    
    return validateFloat(lineEdit->text().trimmed(), result, fieldName);
}

bool InputValidator::validateLineEditPoint2D(QLineEdit* xLineEdit, QLineEdit* yLineEdit, QPointF& point, const QString& pointName)
{
    if (!xLineEdit || !yLineEdit) {
        return false;
    }
    
    return validatePoint2D(xLineEdit->text().trimmed(), yLineEdit->text().trimmed(), point, pointName);
}

bool InputValidator::validateLineEditPoint3D(QLineEdit* xLineEdit, QLineEdit* yLineEdit, QLineEdit* zLineEdit, QVector3D& point, const QString& pointName)
{
    if (!xLineEdit || !yLineEdit || !zLineEdit) {
        return false;
    }
    
    return validatePoint3D(xLineEdit->text().trimmed(), yLineEdit->text().trimmed(), zLineEdit->text().trimmed(), point, pointName);
}

bool InputValidator::isEmpty(const QString& text)
{
    return text.trimmed().isEmpty();
}

void InputValidator::showError(QWidget* parent, const QString& message, const QString& title)
{
    QMessageBox::warning(parent, title, message);
}

void InputValidator::showValidationError(QWidget* parent, const QString& fieldName, const QString& expectedType)
{
    QString message;
    if (fieldName.isEmpty()) {
        message = QString("Please enter a valid %1.").arg(expectedType);
    } else {
        message = QString("Invalid input for '%1'. Please enter a valid %2.").arg(fieldName, expectedType);
    }
    
    showError(parent, message, "Input Validation Error");
} 