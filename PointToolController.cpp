#include "PointToolController.h"
#include <QRegularExpression>
#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include "VariableManager.h"
#include <QMessageBox>

PointToolController::PointToolController(RobotWindow* parent)
    : QObject(parent)
    , m_parent(parent)
    , m_calculator(new PointCalculator())
    , m_cloudPointController(new CloudPointToolController(parent))
    , m_clipboard(QApplication::clipboard())
    , m_useCloudMapping(false)
    , m_defaultCloudMappingVariable("CloudMapping")
{
    // Register cv::Mat as Qt metatype
    qRegisterMetaType<cv::Mat>("cv::Mat");
    
    // Connect cloud point controller signals
    connect(m_cloudPointController, &CloudPointToolController::onMappingUpdated, 
            this, &PointToolController::onCloudMappingUpdated);
    
    setupCloudMappingIntegration();
}

void PointToolController::setParent(RobotWindow* parent)
{
    m_parent = parent;
    QObject::setParent(parent);
    
    if (m_cloudPointController) {
        m_cloudPointController->setParent(parent);
    }
}

void PointToolController::initializeUI(QWidget* parentWidget)
{
    if (!parentWidget || !m_cloudPointController) {
        showError("Invalid parent widget or cloud point controller");
        return;
    }
    
    // Initialize cloud point mapping UI
    m_cloudPointController->initializeUI(parentWidget);
    
    // Don't auto-import during initialization to avoid unnecessary error messages  
    // User can manually import when needed via UI buttons
    // if (!importCloudMappingFromVariables(m_defaultCloudMappingVariable)) {
    //     qDebug() << "No existing cloud mapping found in variables";
    // }
}

CloudPointToolController* PointToolController::getCloudPointController() const
{
    return m_cloudPointController;
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

    // Store in VariableManager
    VariableManager::instance().updateVar("MappingTransform", QVariant::fromValue(result.transform));
    VariableManager::instance().updateVar("MappingMatrix", QVariant::fromValue(result.matrix));

    // Update display
    updateDisplayLabel(m_parent->ui->lbMatrixDisplay, result.displayText);
    
    // Also add these points to cloud mapping if enabled
    if (m_useCloudMapping && m_cloudPointController) {
        CloudPointMapper* mapper = m_cloudPointController->getMapper();
        if (mapper) {
            // Add source point 1
            mapper->addCalibrationPoint(
                QVector3D(sourcePoint1.x(), sourcePoint1.y(), 0.0f),
                QVector3D(targetPoint1.x(), targetPoint1.y(), 0.0f),
                1.0f,
                "Matrix Source 1"
            );
            
            // Add source point 2
            mapper->addCalibrationPoint(
                QVector3D(sourcePoint2.x(), sourcePoint2.y(), 0.0f),
                QVector3D(targetPoint2.x(), targetPoint2.y(), 0.0f),
                1.0f,
                "Matrix Source 2"
            );
            
            // Export to variables
            exportCloudMappingToVariables(m_defaultCloudMappingVariable);
        }
    }
    
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

    // Store in VariableManager
    VariableManager::instance().updateVar("PerspectiveMatrix", QVariant::fromValue(result.matrix));

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
    
    // Also add these points to cloud mapping if enabled
    if (m_useCloudMapping && m_cloudPointController) {
        CloudPointMapper* mapper = m_cloudPointController->getMapper();
        if (mapper) {
            for (int i = 0; i < 4; ++i) {
                mapper->addCalibrationPoint(
                    QVector3D(sourcePoints[i].x(), sourcePoints[i].y(), 0.0f),
                    QVector3D(targetPoints[i].x(), targetPoints[i].y(), 0.0f),
                    1.0f,
                    QString("Perspective Point %1").arg(i + 1)
                );
            }
            
            // Export to variables
            exportCloudMappingToVariables(m_defaultCloudMappingVariable);
        }
    }
    
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

    // Store in VariableManager
    QString vectorName = m_parent->ui->leVectorName->text().trimmed();
    if (!vectorName.isEmpty()) {
        VariableManager::instance().updateVar(vectorName, QVariant::fromValue(result.vector));
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
    QPointF testPoint;
    
    if (!validateAndExtractPoint2D(m_parent->ui->leTestPointX, m_parent->ui->leTestPointY, testPoint, "Test Point")) {
        return false;
    }

    QVector3D testPoint3D(testPoint.x(), testPoint.y(), 0.0f);
    QVector3D resultPoint;
    
    // Try cloud mapping first if available
    if (shouldUseCloudMapping()) {
        resultPoint = transformPointUsingCloudMapping(testPoint3D);
        
        if (!resultPoint.isNull()) {
            // Update UI with result
            setFormattedValue(m_parent->ui->leTargetTestPointX, resultPoint.x());
            setFormattedValue(m_parent->ui->leTargetTestPointY, resultPoint.y());
            
            showSuccess("Test point calculated using Cloud Point Mapping");
            return true;
        }
    }
    
    // Fallback to traditional matrix approach
    if (matrixName.isEmpty()) {
        showError("Please enter a matrix name or use Cloud Point Mapping");
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

QVector3D PointToolController::transformPointUsingCloudMapping(const QVector3D& imageCoord, int method)
{
    if (!m_cloudPointController) {
        return QVector3D();
    }
    
    CloudPointMapper* mapper = m_cloudPointController->getMapper();
    if (!mapper || mapper->getPointCount() < 3) {
        return QVector3D();
    }
    
    CloudPointMapper::InterpolationMethod interpMethod = static_cast<CloudPointMapper::InterpolationMethod>(method);
    CloudPointMapper::MappingResult result = mapper->transformImageToReal(imageCoord, interpMethod);
    
    if (result.isValid) {
        return result.transformedPoint;
    }
    
    return QVector3D();
}

bool PointToolController::isCloudMappingAvailable() const
{
    if (!m_cloudPointController) {
        return false;
    }
    
    CloudPointMapper* mapper = m_cloudPointController->getMapper();
    if (!mapper) {
        return false;
    }
    
    CloudPointMapper::MappingStats stats = mapper->getMappingStats();
    return stats.isValid && mapper->getPointCount() >= 3;
}

QString PointToolController::getCloudMappingStats() const
{
    if (!m_cloudPointController) {
        return "Cloud mapping not available";
    }
    
    CloudPointMapper* mapper = m_cloudPointController->getMapper();
    if (!mapper) {
        return "Cloud mapping not initialized";
    }
    
    CloudPointMapper::MappingStats stats = mapper->getMappingStats();
    
    QString statsText;
    statsText += QString("Points: %1, ").arg(stats.totalPoints);
    statsText += QString("Avg Error: %1mm, ").arg(stats.averageError, 0, 'f', 2);
    statsText += QString("Coverage: %1%, ").arg(stats.coverage, 0, 'f', 1);
    statsText += QString("Valid: %1").arg(stats.isValid ? "Yes" : "No");
    
    return statsText;
}

bool PointToolController::exportCloudMappingToVariables(const QString& variableName)
{
    if (!m_cloudPointController) {
        return false;
    }
    
    CloudPointMapper* mapper = m_cloudPointController->getMapper();
    if (!mapper) {
        return false;
    }
    
    return mapper->exportToVariableManager(variableName);
}

bool PointToolController::importCloudMappingFromVariables(const QString& variableName)
{
    if (!m_cloudPointController) {
        return false;
    }
    
    CloudPointMapper* mapper = m_cloudPointController->getMapper();
    if (!mapper) {
        return false;
    }
    
    return mapper->importFromVariableManager(variableName);
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

// Private methods implementation

void PointToolController::setupCloudMappingIntegration()
{
    // Set up default cloud mapping settings
    m_useCloudMapping = true;
    m_defaultCloudMappingVariable = "CloudMapping";
    
    // Connect to cloud mapping updates
    if (m_cloudPointController) {
        CloudPointMapper* mapper = m_cloudPointController->getMapper();
        if (mapper) {
            connect(mapper, &CloudPointMapper::mappingUpdated, this, &PointToolController::onCloudMappingUpdated);
        }
    }
}

bool PointToolController::shouldUseCloudMapping() const
{
    return m_useCloudMapping && isCloudMappingAvailable();
}

QVector3D PointToolController::fallbackToTraditionalMapping(const QVector3D& imageCoord)
{
    // This would use the traditional matrix-based approach
    // For now, return null to indicate fallback failed
    return QVector3D();
}

void PointToolController::onCloudMappingUpdated()
{
    // Automatically export to variables when cloud mapping is updated
    if (m_useCloudMapping && m_cloudPointController) {
        exportCloudMappingToVariables(m_defaultCloudMappingVariable);
    }
}

void PointToolController::onCalculationCompleted()
{
    // This slot can be used for future async operations
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

// Private helper methods

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

bool PointToolController::parseClipboardPoint(const QString& clipboardText, float& x, float& y, float& z)
{
    // Try to parse different formats
    QStringList parts = clipboardText.split(QRegularExpression("[,\\s]+"), Qt::SkipEmptyParts);
    
    if (parts.size() >= 2) {
        bool okX, okY, okZ = true;
        x = parts[0].toFloat(&okX);
        y = parts[1].toFloat(&okY);
        
        if (parts.size() >= 3) {
            z = parts[2].toFloat(&okZ);
        } else {
            z = 0.0f;
        }
        
        return okX && okY && okZ;
    }
    
    return false;
}

void PointToolController::setFormattedValue(QLineEdit* edit, float value)
{
    if (edit) {
        edit->setText(QString::number(value, 'f', 6));
    }
} 
