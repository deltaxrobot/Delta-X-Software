#include "PointToolController.h"
#include <QRegularExpression>
#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include "VariableManager.h"
#include <QMessageBox>
#include <QDateTime>
#include <QStatusBar>
#include <QtMath>

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
    
    // Connect interpolated multi-point mapping controller signals.
    connect(m_cloudPointController, &CloudPointToolController::onMappingUpdated, 
            this, &PointToolController::onCloudMappingUpdated);
    
    setupCloudMappingIntegration();
}

PointToolController::~PointToolController()
{
    delete m_calculator;
    m_calculator = nullptr;
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
        showError("Invalid parent widget or interpolated mapping controller");
        return;
    }
    
    // Initialize the interpolated multi-point mapping UI.
    m_cloudPointController->initializeUI(parentWidget);
    
    const QString qualifiedName = VariableManager::scopedKey(
        m_parent ? m_parent->ProjectName : QString(), m_defaultCloudMappingVariable);
    if (VariableManager::instance().containsFullKey(qualifiedName + QStringLiteral("_mapping"))) {
        m_useCloudMapping = importCloudMappingFromVariables(m_defaultCloudMappingVariable);
    }
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
    if (!validateAndExtractPoint2D(m_parent->ui->leMappingSourcePoint1X, m_parent->ui->leMappingSourcePoint1Y, sourcePoint1, "Camera-image reference 1")) {
        return false;
    }
    
    if (!validateAndExtractPoint2D(m_parent->ui->leMappingSourcePoint2X, m_parent->ui->leMappingSourcePoint2Y, sourcePoint2, "Camera-image reference 2")) {
        return false;
    }
    
    if (!validateAndExtractPoint2D(m_parent->ui->leMappingDestinationPoint1X, m_parent->ui->leMappingDestinationPoint1Y, targetPoint1, "Robot-workspace reference 1")) {
        return false;
    }
    
    if (!validateAndExtractPoint2D(m_parent->ui->leMappingDestinationPoint2X, m_parent->ui->leMappingDestinationPoint2Y, targetPoint2, "Robot-workspace reference 2")) {
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
    QHash<QString, QVariant> mappingValues;
    mappingValues.insert("MappingTransform", QVariant::fromValue(result.transform));
    mappingValues.insert("MappingMatrix", QVariant::fromValue(result.matrix));
    const QString detecting = m_parent->ui->cbSelectedDetecting->currentText().isEmpty()
        ? QStringLiteral("tracking0") : m_parent->ui->cbSelectedDetecting->currentText();
    const QString qualityPrefix = detecting + QStringLiteral(".Calibration.Mapping.");
    mappingValues.insert(qualityPrefix + QStringLiteral("IsValid"), true);
    mappingValues.insert(qualityPrefix + QStringLiteral("Method"), QStringLiteral("Two-point similarity"));
    mappingValues.insert(qualityPrefix + QStringLiteral("RmsError"), result.rmsError);
    mappingValues.insert(qualityPrefix + QStringLiteral("MaxError"), result.maxError);
    mappingValues.insert(qualityPrefix + QStringLiteral("Scale"), result.scale);
    mappingValues.insert(qualityPrefix + QStringLiteral("RotationDegrees"),
                         qRadiansToDegrees(result.rotationRadians));
    mappingValues.insert(qualityPrefix + QStringLiteral("PointCount"), 2);
    mappingValues.insert(qualityPrefix + QStringLiteral("UpdatedAt"),
                         QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    VariableManager::instance().updateBatchScoped(m_parent->ProjectName, mappingValues);

    // Update display
    updateDisplayLabel(m_parent->ui->lbMatrixDisplay, result.displayText);
    
    showSuccess(QString("Similarity transform solved: scale %1, rotation %2 deg")
                    .arg(result.scale, 0, 'f', 6)
                    .arg(qRadiansToDegrees(result.rotationRadians), 0, 'f', 3));
    return true;
}

bool PointToolController::calculatePerspectiveMatrix()
{
    if (!m_parent) {
        showError("Controller not properly initialized");
        return false;
    }

    QPointF sourcePoints[4], targetPoints[4];
    
    // Validate and extract four camera-image reference points.
    if (!validateAndExtractPoint2D(m_parent->ui->lePerspectiveSourcePoint1X, m_parent->ui->lePerspectiveSourcePoint1Y, sourcePoints[0], "Camera-image reference 1") ||
        !validateAndExtractPoint2D(m_parent->ui->lePerspectiveSourcePoint2X, m_parent->ui->lePerspectiveSourcePoint2Y, sourcePoints[1], "Camera-image reference 2") ||
        !validateAndExtractPoint2D(m_parent->ui->lePerspectiveSourcePoint3X, m_parent->ui->lePerspectiveSourcePoint3Y, sourcePoints[2], "Camera-image reference 3") ||
        !validateAndExtractPoint2D(m_parent->ui->lePerspectiveSourcePoint4X, m_parent->ui->lePerspectiveSourcePoint4Y, sourcePoints[3], "Camera-image reference 4")) {
        return false;
    }
    
    // Validate and extract four robot-workspace reference points.
    if (!validateAndExtractPoint2D(m_parent->ui->lePerspectiveDestinationPoint1X, m_parent->ui->lePerspectiveDestinationPoint1Y, targetPoints[0], "Robot-workspace reference 1") ||
        !validateAndExtractPoint2D(m_parent->ui->lePerspectiveDestinationPoint2X, m_parent->ui->lePerspectiveDestinationPoint2Y, targetPoints[1], "Robot-workspace reference 2") ||
        !validateAndExtractPoint2D(m_parent->ui->lePerspectiveDestinationPoint3X, m_parent->ui->lePerspectiveDestinationPoint3Y, targetPoints[2], "Robot-workspace reference 3") ||
        !validateAndExtractPoint2D(m_parent->ui->lePerspectiveDestinationPoint4X, m_parent->ui->lePerspectiveDestinationPoint4Y, targetPoints[3], "Robot-workspace reference 4")) {
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
    QHash<QString, QVariant> perspectiveValues;
    perspectiveValues.insert(QStringLiteral("PerspectiveMatrix"), QVariant::fromValue(result.matrix));
    perspectiveValues.insert(QStringLiteral("PerspectiveTransform"), QVariant::fromValue(result.qtTransform));
    const QString detecting = m_parent->ui->cbSelectedDetecting->currentText().isEmpty()
        ? QStringLiteral("tracking0") : m_parent->ui->cbSelectedDetecting->currentText();
    const QString qualityPrefix = detecting + QStringLiteral(".Calibration.Perspective.");
    perspectiveValues.insert(qualityPrefix + QStringLiteral("IsValid"), true);
    perspectiveValues.insert(qualityPrefix + QStringLiteral("RmsError"), result.rmsError);
    perspectiveValues.insert(qualityPrefix + QStringLiteral("MaxError"), result.maxError);
    perspectiveValues.insert(qualityPrefix + QStringLiteral("ConditionNumber"), result.conditionNumber);
    perspectiveValues.insert(qualityPrefix + QStringLiteral("PointCount"), 4);
    perspectiveValues.insert(qualityPrefix + QStringLiteral("UpdatedAt"),
                             QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    VariableManager::instance().updateBatchScoped(m_parent->ProjectName, perspectiveValues);

    // Update display
    updateDisplayLabel(m_parent->ui->lbPointMatrixDisplay, result.displayText);
    showSuccess(QString("Planar homography solved: RMS %1, condition %2")
                    .arg(result.rmsError, 0, 'f', 4)
                    .arg(result.conditionNumber, 0, 'g', 5));
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
    if (!validateAndExtractPoint3D(m_parent->ui->leVectorPoint1X, m_parent->ui->leVectorPoint1Y, m_parent->ui->leVectorPoint1Z, point1, "Start position") ||
        !validateAndExtractPoint3D(m_parent->ui->leVectorPoint2X, m_parent->ui->leVectorPoint2Y, m_parent->ui->leVectorPoint2Z, point2, "End position") ||
        !validateAndExtractFloat(m_parent->ui->leVectorValue, magnitude, "Output magnitude")) {
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
        VariableManager::instance().updateVarScoped(
            m_parent->ProjectName, vectorName, QVariant::fromValue(result.vector));
    }

    // Update UI with results
    setFormattedValue(m_parent->ui->leVectorX, result.vector.x());
    setFormattedValue(m_parent->ui->leVectorY, result.vector.y());
    setFormattedValue(m_parent->ui->leVectorZ, result.vector.z());
    
    showSuccess("Scaled direction vector calculated");
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
    
    if (!validateAndExtractPoint2D(m_parent->ui->leTestPointX, m_parent->ui->leTestPointY, testPoint, "Camera-image test point")) {
        return false;
    }

    const QVector3D testPoint3D(testPoint.x(), testPoint.y(), 0.0f);

    if (shouldUseCloudMapping()) {
        CloudPointMapper* mapper = m_cloudPointController->getMapper();
        const CloudPointMapper::MappingResult cloudResult = mapper->transformImageToReal(
            testPoint3D, mapper->defaultInterpolationMethod());
        if (cloudResult.isValid) {
            setFormattedValue(m_parent->ui->leTargetTestPointX, cloudResult.transformedPoint.x());
            setFormattedValue(m_parent->ui->leTargetTestPointY, cloudResult.transformedPoint.y());
            showSuccess(QString("Interpolated point mapped (confidence %1, estimated error %2 mm)")
                            .arg(cloudResult.confidence, 0, 'f', 3)
                            .arg(cloudResult.estimatedError, 0, 'f', 3));
            return true;
        }
    }
    
    // Fallback to traditional matrix approach
    if (matrixName.isEmpty()) {
        showError("Enter a saved transform variable or build an interpolated mapping");
        return false;
    }

    const QVariant storedMatrix = VariableManager::instance().getVarScoped(
        m_parent->ProjectName, matrixName);
    if (!storedMatrix.isValid() || !storedMatrix.canConvert<QTransform>()) {
        showError(QString("Transform variable '%1' was not found. Solve and save a transform first.").arg(matrixName));
        return false;
    }
    const QTransform matrix = storedMatrix.value<QTransform>();
    if (qFuzzyIsNull(matrix.determinant())) {
        showError(QString("Transform variable '%1' is singular and cannot be applied.").arg(matrixName));
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
    
    showSuccess("Test point transformed");
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
    statsText += QString("Reference pairs: %1, ").arg(stats.totalPoints);
    statsText += QString("Mean residual: %1 mm, ").arg(stats.averageError, 0, 'f', 2);
    statsText += QString("Image-area coverage: %1%, ").arg(stats.coverage, 0, 'f', 1);
    statsText += QString("Validation: %1").arg(stats.isValid ? "Passed" : "Not passed");
    
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
    
    const QString qualifiedName = VariableManager::scopedKey(
        m_parent ? m_parent->ProjectName : QString(), variableName);
    return mapper->exportToVariableManager(qualifiedName);
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
    
    const QString qualifiedName = VariableManager::scopedKey(
        m_parent ? m_parent->ProjectName : QString(), variableName);
    return mapper->importFromVariableManager(qualifiedName);
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
    // Cloud mapping is activated only after a validated profile is loaded.
    m_useCloudMapping = false;
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
    if (!m_cloudPointController)
        return;
    CloudPointMapper* mapper = m_cloudPointController->getMapper();
    m_useCloudMapping = mapper && mapper->getMappingStats().isValid;
    if (m_useCloudMapping) {
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

    QVariant var = VariableManager::instance().getVarScoped(
        m_parent ? m_parent->ProjectName : QString(), matrixName);
    if (var.canConvert<QTransform>()) {
        return var.value<QTransform>();
    }

    return QTransform(); // Identity matrix
}

void PointToolController::storeMatrix(const QString& matrixName, const QTransform& transform)
{
    if (!matrixName.isEmpty()) {
        VariableManager::instance().updateVarScoped(
            m_parent ? m_parent->ProjectName : QString(), matrixName,
            QVariant::fromValue(transform));
    }
}

QVector3D PointToolController::getStoredVector(const QString& vectorName)
{
    if (vectorName.isEmpty()) {
        return QVector3D();
    }

    QVariant var = VariableManager::instance().getVarScoped(
        m_parent ? m_parent->ProjectName : QString(), vectorName);
    if (var.canConvert<QVector3D>()) {
        return var.value<QVector3D>();
    }

    return QVector3D(); // Zero vector
}

void PointToolController::storeVector(const QString& vectorName, const QVector3D& vector)
{
    if (!vectorName.isEmpty()) {
        VariableManager::instance().updateVarScoped(
            m_parent ? m_parent->ProjectName : QString(), vectorName,
            QVariant::fromValue(vector));
    }
}

// Private helper methods

void PointToolController::showError(const QString& message)
{
    if (m_parent) {
        InputValidator::showError(m_parent, message, "Calibration Error");
    }
}

void PointToolController::showSuccess(const QString& message)
{
    if (m_parent && m_parent->statusBar())
        m_parent->statusBar()->showMessage(message, 6000);
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
