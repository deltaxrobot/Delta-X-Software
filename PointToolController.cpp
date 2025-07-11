#include "PointToolController.h"
#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include "VariableManager.h"
#include <QMessageBox>
#include <QRegularExpression>

PointToolController::PointToolController(RobotWindow* parent)
    : QObject(parent)
    , m_parent(parent)
    , m_calculator(new PointCalculator())
    , m_clipboard(QApplication::clipboard())
{
}

void PointToolController::setParent(RobotWindow* parent)
{
    m_parent = parent;
    QObject::setParent(parent);
}

bool PointToolController::calculateMappingMatrix()
{
    if (!m_parent) {
        showError("Controller not properly initialized");
        return false;
    }

    // Get UI controls (we'll need to access them through m_parent->ui)
    QPointF sourcePoint1, sourcePoint2, targetPoint1, targetPoint2;
    
    // Validate and extract points
    if (!validateAndExtractPoint2D(m_parent->ui->leSourcePoint1X, m_parent->ui->leSourcePoint1Y, sourcePoint1, "Source Point 1")) {
        return false;
    }
    
    if (!validateAndExtractPoint2D(m_parent->ui->leSourcePoint2X, m_parent->ui->leSourcePoint2Y, sourcePoint2, "Source Point 2")) {
        return false;
    }
    
    if (!validateAndExtractPoint2D(m_parent->ui->leDestinationPoint1X, m_parent->ui->leDestinationPoint1Y, targetPoint1, "Target Point 1")) {
        return false;
    }
    
    if (!validateAndExtractPoint2D(m_parent->ui->leDestinationPoint2X, m_parent->ui->leDestinationPoint2Y, targetPoint2, "Target Point 2")) {
        return false;
    }

    // Perform calculation
    auto result = m_calculator->calculateMappingTransform(sourcePoint1, sourcePoint2, targetPoint1, targetPoint2);
    
    if (!result.isValid) {
        showError(result.errorMessage);
        return false;
    }

    // Store results
    m_lastMappingTransform = result.transform;
    m_lastMappingMatrix = result.matrix;
    
    // Update global variables for compatibility
    if (m_parent) {
        m_parent->m_currentMappingTransform = result.transform;
        m_parent->m_currentMappingMatrix = result.matrix;
    }

    // Update display
    updateDisplayLabel(m_parent->ui->lbMatrixDisplay, result.displayText);
    
    showSuccess("Mapping matrix calculated successfully");
    return true;
}

bool PointToolController::calculatePerspectiveMatrix()
{
    if (!m_parent) {
        showError("Controller not properly initialized");
        return false;
    }

    QPointF sourcePoints[4], targetPoints[4];
    
    // Validate and extract 4 source points
    if (!validateAndExtractPoint2D(m_parent->ui->leSourcePoint1X, m_parent->ui->leSourcePoint1Y, sourcePoints[0], "Source Point 1") ||
        !validateAndExtractPoint2D(m_parent->ui->leSourcePoint2X, m_parent->ui->leSourcePoint2Y, sourcePoints[1], "Source Point 2") ||
        !validateAndExtractPoint2D(m_parent->ui->leSourcePoint3X, m_parent->ui->leSourcePoint3Y, sourcePoints[2], "Source Point 3") ||
        !validateAndExtractPoint2D(m_parent->ui->leSourcePoint4X, m_parent->ui->leSourcePoint4Y, sourcePoints[3], "Source Point 4")) {
        return false;
    }
    
    // Validate and extract 4 target points
    if (!validateAndExtractPoint2D(m_parent->ui->leDestinationPoint1X, m_parent->ui->leDestinationPoint1Y, targetPoints[0], "Target Point 1") ||
        !validateAndExtractPoint2D(m_parent->ui->leDestinationPoint2X, m_parent->ui->leDestinationPoint2Y, targetPoints[1], "Target Point 2") ||
        !validateAndExtractPoint2D(m_parent->ui->leDestinationPoint3X, m_parent->ui->leDestinationPoint3Y, targetPoints[2], "Target Point 3") ||
        !validateAndExtractPoint2D(m_parent->ui->leDestinationPoint4X, m_parent->ui->leDestinationPoint4Y, targetPoints[3], "Target Point 4")) {
        return false;
    }

    // Perform calculation
    auto result = m_calculator->calculatePerspectiveMatrix(sourcePoints, targetPoints);
    
    if (!result.isValid) {
        showError(result.errorMessage);
        return false;
    }

    // Store results
    m_lastPerspectiveMatrix = result.matrix;
    
    // Update global variables for compatibility
    if (m_parent) {
        m_parent->m_currentPerspectiveMatrix = result.matrix;
    }

    // Create display string for compatibility with old format
    QString matrixString = QString("m11: %1, m12: %2\nm21: %3, m22: %4\ndx: %5, dy: %6")
                          .arg(result.qtTransform.m11(), 0, 'f', 6)
                          .arg(result.qtTransform.m12(), 0, 'f', 6)
                          .arg(result.qtTransform.m21(), 0, 'f', 6)
                          .arg(result.qtTransform.m22(), 0, 'f', 6)
                          .arg(result.qtTransform.dx(), 0, 'f', 6)
                          .arg(result.qtTransform.dy(), 0, 'f', 6);

    // Update display
    updateDisplayLabel(m_parent->ui->lbPointMatrixDisplay, matrixString);
    
    showSuccess("Perspective matrix calculated successfully");
    return true;
}

bool PointToolController::calculateVector()
{
    if (!m_parent) {
        showError("Controller not properly initialized");
        return false;
    }

    QVector3D point1, point2;
    float magnitude;
    
    // Validate and extract points and magnitude
    if (!validateAndExtractPoint3D(m_parent->ui->leVectorPoint1X, m_parent->ui->leVectorPoint1Y, m_parent->ui->leVectorPoint1Z, point1, "Point 1") ||
        !validateAndExtractPoint3D(m_parent->ui->leVectorPoint2X, m_parent->ui->leVectorPoint2Y, m_parent->ui->leVectorPoint2Z, point2, "Point 2") ||
        !validateAndExtractFloat(m_parent->ui->leVectorValue, magnitude, "Vector Magnitude")) {
        return false;
    }

    // Perform calculation
    auto result = m_calculator->calculateVector(point1, point2, magnitude);
    
    if (!result.isValid) {
        showError(result.errorMessage);
        return false;
    }

    // Store result
    m_lastCalculatedVector = result.vector;
    
    // Update global variables for compatibility
    if (m_parent) {
        m_parent->m_currentCalculatedVector = result.vector;
    }

    // Update UI with results
    setFormattedValue(m_parent->ui->leVectorX, result.vector.x());
    setFormattedValue(m_parent->ui->leVectorY, result.vector.y());
    setFormattedValue(m_parent->ui->leVectorZ, result.vector.z());
    
    showSuccess("Vector calculated successfully");
    return true;
}

bool PointToolController::calculateTestPoint()
{
    if (!m_parent) {
        showError("Controller not properly initialized");
        return false;
    }

    // Get matrix name and test point
    QString matrixName = m_parent->ui->leTestMatrixName->text().trimmed();
    if (matrixName.isEmpty()) {
        showError("Please enter a matrix name");
        return false;
    }

    QPointF testPoint;
    if (!validateAndExtractPoint2D(m_parent->ui->leTestPointX, m_parent->ui->leTestPointY, testPoint, "Test Point")) {
        return false;
    }

    // Get stored matrix
    QTransform matrix = getStoredMatrix(matrixName);
    if (matrix.isIdentity()) {
        showError(QString("Matrix '%1' not found. Please calculate a matrix first.").arg(matrixName));
        return false;
    }

    // Transform point
    auto result = m_calculator->transformPoint(testPoint, matrix);
    
    if (!result.isValid) {
        showError(result.errorMessage);
        return false;
    }

    // Update UI with result
    setFormattedValue(m_parent->ui->leTargetTestPointX, result.transformedPoint.x());
    setFormattedValue(m_parent->ui->leTargetTestPointY, result.transformedPoint.y());
    
    showSuccess("Test point calculated successfully");
    return true;
}

void PointToolController::updateTestPoint(const QVector3D& testPoint)
{
    if (!m_parent || !m_parent->ui->tbAutoMove->isChecked()) {
        return;
    }

    QVector3D currentPoint;
    if (!validateAndExtractPoint3D(m_parent->ui->leTestTrackingPointX, m_parent->ui->leTestTrackingPointY, m_parent->ui->leTestTrackingPointZ, currentPoint, "Current Point")) {
        return;
    }

    QVector3D newPoint = currentPoint + testPoint;
    
    setFormattedValue(m_parent->ui->leTestTrackingPointX, newPoint.x());
    setFormattedValue(m_parent->ui->leTestTrackingPointY, newPoint.y());
    setFormattedValue(m_parent->ui->leTestTrackingPointZ, newPoint.z());
}

void PointToolController::moveTestTrackingPoint()
{
    if (!m_parent) {
        return;
    }

    QVector3D initialPoint;
    float distance;
    QString vectorName = m_parent->ui->leVelocityVector->text().trimmed();

    // Validate inputs
    if (!validateAndExtractPoint3D(m_parent->ui->leTestTrackingPointX, m_parent->ui->leTestTrackingPointY, m_parent->ui->leTestTrackingPointZ, initialPoint, "Initial Point") ||
        !validateAndExtractFloat(m_parent->ui->leMovingValue, distance, "Moving Distance")) {
        return;
    }

    if (vectorName.isEmpty()) {
        showError("Please enter a velocity vector name");
        return;
    }

    // Get stored vector
    QVector3D direction = getStoredVector(vectorName);
    if (direction.isNull()) {
        showError(QString("Vector '%1' not found. Please calculate a vector first.").arg(vectorName));
        return;
    }

    // Calculate new position
    QVector3D newPoint = m_calculator->updatePointPosition(initialPoint, direction, distance);
    
    // Update UI
    setFormattedValue(m_parent->ui->leTestTrackingPointX, newPoint.x());
    setFormattedValue(m_parent->ui->leTestTrackingPointY, newPoint.y());
    setFormattedValue(m_parent->ui->leTestTrackingPointZ, newPoint.z());
}

void PointToolController::pastePointValues(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit)
{
    if (!xEdit || !yEdit) {
        return;
    }

    QString clipboardText = m_clipboard->text().trimmed();
    if (clipboardText.isEmpty()) {
        showError("Clipboard is empty");
        return;
    }

    float x, y, z = 0.0f;
    if (!parseClipboardPoint(clipboardText, x, y, z)) {
        showError("Invalid clipboard format. Expected: 'x,y' or 'x,y,z' or 'x y z'");
        return;
    }

    // Set values
    setFormattedValue(xEdit, x);
    setFormattedValue(yEdit, y);
    if (zEdit) {
        setFormattedValue(zEdit, z);
    }
}

void PointToolController::setCurrentRobotPosition(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit)
{
    if (!m_parent || !xEdit || !yEdit || !zEdit) {
        return;
    }

    // Get current robot position from RobotParameters
    int robotId = m_parent->RbID;
    if (robotId >= 0 && robotId < m_parent->RobotParameters.size()) {
        const auto& robotPara = m_parent->RobotParameters[robotId];
        setFormattedValue(xEdit, robotPara.X);
        setFormattedValue(yEdit, robotPara.Y);
        setFormattedValue(zEdit, robotPara.Z);
    }
}

QTransform PointToolController::getStoredMatrix(const QString& matrixName)
{
    if (matrixName.isEmpty()) {
        return QTransform();
    }

    QVariant var = VariableManager::instance().getVar(matrixName);
    if (var.canConvert<QTransform>()) {
        return var.value<QTransform>();
    }

    return QTransform(); // Identity matrix
}

void PointToolController::storeMatrix(const QString& matrixName, const QTransform& transform)
{
    if (!matrixName.isEmpty()) {
        VariableManager::instance().updateVar(matrixName, QVariant::fromValue(transform));
    }
}

QVector3D PointToolController::getStoredVector(const QString& vectorName)
{
    if (vectorName.isEmpty()) {
        return QVector3D();
    }

    QVariant var = VariableManager::instance().getVar(vectorName);
    if (var.canConvert<QVector3D>()) {
        return var.value<QVector3D>();
    }

    return QVector3D(); // Zero vector
}

void PointToolController::storeVector(const QString& vectorName, const QVector3D& vector)
{
    if (!vectorName.isEmpty()) {
        VariableManager::instance().updateVar(vectorName, QVariant::fromValue(vector));
    }
}

void PointToolController::onCalculationCompleted()
{
    // This slot can be used for future async operations
}

// Private methods

void PointToolController::showError(const QString& message)
{
    if (m_parent) {
        InputValidator::showError(m_parent, message, "Point Tool Error");
    }
}

void PointToolController::showSuccess(const QString& message)
{
    // For now, we'll skip success messages to avoid too many popups
    // Could be implemented with a status bar message instead
}

void PointToolController::updateDisplayLabel(QLabel* label, const QString& text)
{
    if (label) {
        label->setText(text);
    }
}

bool PointToolController::validateAndExtractPoint2D(QLineEdit* xEdit, QLineEdit* yEdit, QPointF& point, const QString& pointName)
{
    if (!xEdit || !yEdit) {
        showError("Invalid UI controls");
        return false;
    }

    if (!InputValidator::validateLineEditPoint2D(xEdit, yEdit, point, pointName)) {
        InputValidator::showValidationError(m_parent, pointName, "coordinate");
        return false;
    }

    return true;
}

bool PointToolController::validateAndExtractPoint3D(QLineEdit* xEdit, QLineEdit* yEdit, QLineEdit* zEdit, QVector3D& point, const QString& pointName)
{
    if (!xEdit || !yEdit || !zEdit) {
        showError("Invalid UI controls");
        return false;
    }

    if (!InputValidator::validateLineEditPoint3D(xEdit, yEdit, zEdit, point, pointName)) {
        InputValidator::showValidationError(m_parent, pointName, "3D coordinate");
        return false;
    }

    return true;
}

bool PointToolController::validateAndExtractFloat(QLineEdit* edit, float& value, const QString& fieldName)
{
    if (!edit) {
        showError("Invalid UI control");
        return false;
    }

    if (!InputValidator::validateLineEditFloat(edit, value, fieldName)) {
        InputValidator::showValidationError(m_parent, fieldName, "number");
        return false;
    }

    return true;
}

void PointToolController::setFormattedValue(QLineEdit* edit, float value, int precision)
{
    if (edit) {
        edit->setText(QString::number(value, 'f', precision));
    }
}

bool PointToolController::parseClipboardPoint(const QString& text, float& x, float& y, float& z)
{
    // Try comma-separated format first: "x,y" or "x,y,z"
    QStringList parts = text.split(',');
    if (parts.size() >= 2) {
        bool okX, okY, okZ = true;
        x = parts[0].trimmed().toFloat(&okX);
        y = parts[1].trimmed().toFloat(&okY);
        
        if (parts.size() >= 3) {
            z = parts[2].trimmed().toFloat(&okZ);
        }
        
        return okX && okY && okZ;
    }

    // Try space-separated format: "x y" or "x y z"
    parts = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (parts.size() >= 2) {
        bool okX, okY, okZ = true;
        x = parts[0].toFloat(&okX);
        y = parts[1].toFloat(&okY);
        
        if (parts.size() >= 3) {
            z = parts[2].toFloat(&okZ);
        }
        
        return okX && okY && okZ;
    }

    return false;
} 