#include "CloudPointToolController.h"
#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include <QSplitter>
#include <QScrollArea>
#include <QStyleOption>
#include <QPainter>
#include <QRandomGenerator>

CloudPointToolController::CloudPointToolController(RobotWindow* parent)
    : QObject(parent)
    , m_parent(parent)
    , m_mapper(new CloudPointMapper(this))
    , m_clipboard(QApplication::clipboard())
    , m_validationTimer(new QTimer(this))
    , m_mainGroupBox(nullptr)
    , m_calibrationTable(nullptr)
    , m_interpolationMethodCombo(nullptr)
    , m_gridResolutionSpinBox(nullptr)
    , m_autoRebuildCheckBox(nullptr)
    , m_validationProgressBar(nullptr)
    , m_statsTextEdit(nullptr)
{
    // Connect mapper signals
    connect(m_mapper, &CloudPointMapper::mappingUpdated, this, &CloudPointToolController::onMappingUpdated);
    connect(m_mapper, &CloudPointMapper::validationComplete, this, &CloudPointToolController::onValidationComplete);
    connect(m_mapper, &CloudPointMapper::errorOccurred, this, &CloudPointToolController::onErrorOccurred);
    
    // Setup validation timer
    m_validationTimer->setInterval(100);
    connect(m_validationTimer, &QTimer::timeout, this, &CloudPointToolController::updateValidationProgress);
    
    qDebug() << "CloudPointToolController initialized";
}

CloudPointToolController::~CloudPointToolController()
{
    // Disconnect all signals to prevent crashes during destruction
    if (m_mapper) {
        disconnect(m_mapper, nullptr, this, nullptr);
        delete m_mapper;
        m_mapper = nullptr;
    }
}

void CloudPointToolController::setParent(RobotWindow* parent)
{
    m_parent = parent;
    QObject::setParent(parent);
}

void CloudPointToolController::initializeUI(QWidget* parentWidget)
{
    if (!parentWidget) {
        showError("Invalid parent widget");
        return;
    }
    
    // Create main UI
    createUI();
    
    // Find the Point Tool area and add our controls
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(parentWidget->layout());
    if (!layout) {
        layout = new QVBoxLayout(parentWidget);
    }
    
    // Add a splitter to separate traditional and cloud point tools
    QSplitter* splitter = new QSplitter(Qt::Vertical, parentWidget);
    
    // Add our cloud point group to the splitter
    splitter->addWidget(m_mainGroupBox);
    
    // Set splitter proportions
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);
    
    // Add splitter to layout
    layout->addWidget(splitter);
    
    // Connect all signals
    connectSignals();
    
    // Initial UI update
    updateButtonStates();
    updateStatsDisplay();
    
    showInfo("Cloud Point Mapping initialized. Add calibration points to begin mapping.");
}

CloudPointMapper* CloudPointToolController::getMapper() const
{
    return m_mapper;
}

void CloudPointToolController::createUI()
{
    // Create main group box
    m_mainGroupBox = new QGroupBox("Cloud Point Mapping (Advanced)");
    m_mainGroupBox->setObjectName("gbCloudPointMapping");
    m_mainGroupBox->setStyleSheet(
        "QGroupBox { background-color: rgb(51, 51, 55); color: rgb(208, 208, 209); }"
        "QGroupBox::title { color: rgb(208, 208, 209); }"
    );
    
    // Create main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(m_mainGroupBox);
    
    // Add groups to main layout
    mainLayout->addWidget(createCalibrationPointsGroup());
    mainLayout->addWidget(createMappingSettingsGroup());
    mainLayout->addWidget(createTestPointGroup());
    mainLayout->addWidget(createControlButtonsGroup());
    mainLayout->addWidget(createStatsGroup());
    mainLayout->addWidget(createVariableManagerGroup());
    mainLayout->addWidget(createAutoCollectGroup());
    
    // Add stretch to prevent groups from expanding too much
    mainLayout->addStretch();
}

QGroupBox* CloudPointToolController::createCalibrationPointsGroup()
{
    QGroupBox* group = new QGroupBox("Calibration Points");
    QVBoxLayout* layout = new QVBoxLayout(group);
    
    // Create input controls
    QGridLayout* inputLayout = new QGridLayout();
    
    // Image coordinates
    inputLayout->addWidget(new QLabel("Image X:"), 0, 0);
    m_imageXEdit = new QLineEdit();
    m_imageXEdit->setPlaceholderText("0.0");
    inputLayout->addWidget(m_imageXEdit, 0, 1);
    
    inputLayout->addWidget(new QLabel("Image Y:"), 0, 2);
    m_imageYEdit = new QLineEdit();
    m_imageYEdit->setPlaceholderText("0.0");
    inputLayout->addWidget(m_imageYEdit, 0, 3);
    
    inputLayout->addWidget(new QLabel("Image Z:"), 0, 4);
    m_imageZEdit = new QLineEdit();
    m_imageZEdit->setPlaceholderText("0.0");
    inputLayout->addWidget(m_imageZEdit, 0, 5);
    
    // Real coordinates
    inputLayout->addWidget(new QLabel("Real X:"), 1, 0);
    m_realXEdit = new QLineEdit();
    m_realXEdit->setPlaceholderText("0.0");
    inputLayout->addWidget(m_realXEdit, 1, 1);
    
    inputLayout->addWidget(new QLabel("Real Y:"), 1, 2);
    m_realYEdit = new QLineEdit();
    m_realYEdit->setPlaceholderText("0.0");
    inputLayout->addWidget(m_realYEdit, 1, 3);
    
    inputLayout->addWidget(new QLabel("Real Z:"), 1, 4);
    m_realZEdit = new QLineEdit();
    m_realZEdit->setPlaceholderText("0.0");
    inputLayout->addWidget(m_realZEdit, 1, 5);
    
    // Confidence and label
    inputLayout->addWidget(new QLabel("Confidence:"), 2, 0);
    m_confidenceSpinBox = new QDoubleSpinBox();
    m_confidenceSpinBox->setRange(0.0, 1.0);
    m_confidenceSpinBox->setValue(1.0);
    m_confidenceSpinBox->setSingleStep(0.1);
    m_confidenceSpinBox->setDecimals(2);
    inputLayout->addWidget(m_confidenceSpinBox, 2, 1);
    
    inputLayout->addWidget(new QLabel("Label:"), 2, 2);
    m_labelEdit = new QLineEdit();
    m_labelEdit->setPlaceholderText("Point label");
    inputLayout->addWidget(m_labelEdit, 2, 3, 1, 2);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    m_addPointButton = new QPushButton("Add Point");
    m_addPointButton->setIcon(QIcon("icon/Add_16px.png"));
    buttonLayout->addWidget(m_addPointButton);
    
    m_updatePointButton = new QPushButton("Update Point");
    m_updatePointButton->setIcon(QIcon("icon/Edit_16px.png"));
    m_updatePointButton->setEnabled(false);
    buttonLayout->addWidget(m_updatePointButton);
    
    m_removePointButton = new QPushButton("Remove Point");
    m_removePointButton->setIcon(QIcon("icon/Delete_16px.png"));
    m_removePointButton->setEnabled(false);
    buttonLayout->addWidget(m_removePointButton);
    
    m_pasteButton = new QPushButton("Paste");
    m_pasteButton->setIcon(QIcon("icon/Paste_16px.png"));
    buttonLayout->addWidget(m_pasteButton);
    
    m_getRobotPosButton = new QPushButton("Get Robot Pos");
    m_getRobotPosButton->setIcon(QIcon("icon/Robot_16px.png"));
    buttonLayout->addWidget(m_getRobotPosButton);
    
    m_getImagePosButton = new QPushButton("Get Image Pos");
    m_getImagePosButton->setIcon(QIcon("icon/Camera_16px.png"));
    buttonLayout->addWidget(m_getImagePosButton);
    
    inputLayout->addLayout(buttonLayout, 3, 0, 1, 6);
    
    layout->addLayout(inputLayout);
    
    // Create calibration table
    setupCalibrationTable();
    layout->addWidget(m_calibrationTable);
    
    return group;
}

QGroupBox* CloudPointToolController::createMappingSettingsGroup()
{
    QGroupBox* group = new QGroupBox("Mapping Settings");
    QGridLayout* layout = new QGridLayout(group);
    
    // Interpolation method
    layout->addWidget(new QLabel("Interpolation Method:"), 0, 0);
    m_interpolationMethodCombo = new QComboBox();
    setupInterpolationMethodCombo();
    layout->addWidget(m_interpolationMethodCombo, 0, 1);
    
    // Grid resolution
    layout->addWidget(new QLabel("Grid Resolution:"), 0, 2);
    m_gridResolutionSpinBox = new QDoubleSpinBox();
    m_gridResolutionSpinBox->setRange(0.1, 100.0);
    m_gridResolutionSpinBox->setValue(10.0);
    m_gridResolutionSpinBox->setSingleStep(0.5);
    m_gridResolutionSpinBox->setDecimals(1);
    m_gridResolutionSpinBox->setSuffix(" px/cell");
    layout->addWidget(m_gridResolutionSpinBox, 0, 3);
    
    // Auto-rebuild checkbox
    m_autoRebuildCheckBox = new QCheckBox("Auto-rebuild Grid");
    m_autoRebuildCheckBox->setChecked(true);
    layout->addWidget(m_autoRebuildCheckBox, 0, 4);
    
    // Build grid button
    m_buildGridButton = new QPushButton("Build Grid");
    m_buildGridButton->setIcon(QIcon("icon/Grid_16px.png"));
    layout->addWidget(m_buildGridButton, 0, 5);
    
    // Validation controls
    layout->addWidget(new QLabel("Validation:"), 1, 0);
    
    m_validateButton = new QPushButton("Validate Mapping");
    m_validateButton->setIcon(QIcon("icon/Checkmark_16px.png"));
    layout->addWidget(m_validateButton, 1, 1);
    
    m_validationProgressBar = new QProgressBar();
    m_validationProgressBar->setVisible(false);
    layout->addWidget(m_validationProgressBar, 1, 2, 1, 2);
    
    m_visualizeButton = new QPushButton("Visualize");
    m_visualizeButton->setIcon(QIcon("icon/Eye_16px.png"));
    layout->addWidget(m_visualizeButton, 1, 4);
    
    m_statsButton = new QPushButton("Stats");
    m_statsButton->setIcon(QIcon("icon/Statistics_16px.png"));
    layout->addWidget(m_statsButton, 1, 5);
    
    return group;
}

QGroupBox* CloudPointToolController::createTestPointGroup()
{
    QGroupBox* group = new QGroupBox("Test Point Transformation");
    QGridLayout* layout = new QGridLayout(group);
    
    // Test input coordinates
    layout->addWidget(new QLabel("Test Image X:"), 0, 0);
    m_testImageXEdit = new QLineEdit();
    m_testImageXEdit->setPlaceholderText("0.0");
    layout->addWidget(m_testImageXEdit, 0, 1);
    
    layout->addWidget(new QLabel("Test Image Y:"), 0, 2);
    m_testImageYEdit = new QLineEdit();
    m_testImageYEdit->setPlaceholderText("0.0");
    layout->addWidget(m_testImageYEdit, 0, 3);
    
    layout->addWidget(new QLabel("Test Image Z:"), 0, 4);
    m_testImageZEdit = new QLineEdit();
    m_testImageZEdit->setPlaceholderText("0.0");
    layout->addWidget(m_testImageZEdit, 0, 5);
    
    // Transform button
    m_transformTestButton = new QPushButton("Transform");
    m_transformTestButton->setIcon(QIcon("icon/Transform_16px.png"));
    layout->addWidget(m_transformTestButton, 0, 6);
    
    // Test result coordinates
    layout->addWidget(new QLabel("Result Real X:"), 1, 0);
    m_testRealXEdit = new QLineEdit();
    m_testRealXEdit->setReadOnly(true);
    m_testRealXEdit->setStyleSheet("background-color: rgb(70, 70, 75);");
    layout->addWidget(m_testRealXEdit, 1, 1);
    
    layout->addWidget(new QLabel("Result Real Y:"), 1, 2);
    m_testRealYEdit = new QLineEdit();
    m_testRealYEdit->setReadOnly(true);
    m_testRealYEdit->setStyleSheet("background-color: rgb(70, 70, 75);");
    layout->addWidget(m_testRealYEdit, 1, 3);
    
    layout->addWidget(new QLabel("Result Real Z:"), 1, 4);
    m_testRealZEdit = new QLineEdit();
    m_testRealZEdit->setReadOnly(true);
    m_testRealZEdit->setStyleSheet("background-color: rgb(70, 70, 75);");
    layout->addWidget(m_testRealZEdit, 1, 5);
    
    // Confidence and error display
    layout->addWidget(new QLabel("Confidence:"), 2, 0);
    m_testConfidenceLabel = new QLabel("0.00");
    m_testConfidenceLabel->setStyleSheet("color: rgb(255, 255, 255); font-weight: bold;");
    layout->addWidget(m_testConfidenceLabel, 2, 1);
    
    layout->addWidget(new QLabel("Est. Error:"), 2, 2);
    m_testErrorLabel = new QLabel("0.00 mm");
    m_testErrorLabel->setStyleSheet("color: rgb(255, 255, 255); font-weight: bold;");
    layout->addWidget(m_testErrorLabel, 2, 3);
    
    return group;
}

QGroupBox* CloudPointToolController::createControlButtonsGroup()
{
    QGroupBox* group = new QGroupBox("File Operations");
    QHBoxLayout* layout = new QHBoxLayout(group);
    
    m_saveButton = new QPushButton("Save Mapping");
    m_saveButton->setIcon(QIcon("icon/Save_16px.png"));
    layout->addWidget(m_saveButton);
    
    m_loadButton = new QPushButton("Load Mapping");
    m_loadButton->setIcon(QIcon("icon/Open_16px.png"));
    layout->addWidget(m_loadButton);
    
    m_clearAllButton = new QPushButton("Clear All");
    m_clearAllButton->setIcon(QIcon("icon/Clear_16px.png"));
    layout->addWidget(m_clearAllButton);
    
    layout->addStretch();
    
    return group;
}

QGroupBox* CloudPointToolController::createStatsGroup()
{
    QGroupBox* group = new QGroupBox("Mapping Statistics");
    QVBoxLayout* layout = new QVBoxLayout(group);
    
    m_statsTextEdit = new QTextEdit();
    m_statsTextEdit->setMaximumHeight(100);
    m_statsTextEdit->setReadOnly(true);
    m_statsTextEdit->setStyleSheet("background-color: rgb(40, 40, 45); color: rgb(255, 255, 255);");
    m_statsTextEdit->setPlainText("No mapping data available. Add calibration points to begin.");
    
    layout->addWidget(m_statsTextEdit);
    
    return group;
}

QGroupBox* CloudPointToolController::createVariableManagerGroup()
{
    QGroupBox* group = new QGroupBox("Variable Manager Integration");
    QGridLayout* layout = new QGridLayout(group);
    
    layout->addWidget(new QLabel("Variable Name:"), 0, 0);
    m_variableNameEdit = new QLineEdit();
    m_variableNameEdit->setPlaceholderText("CloudMapping");
    m_variableNameEdit->setText("CloudMapping");
    layout->addWidget(m_variableNameEdit, 0, 1, 1, 2);
    
    m_exportButton = new QPushButton("Export to Variables");
    m_exportButton->setIcon(QIcon("icon/Export_16px.png"));
    layout->addWidget(m_exportButton, 0, 3);
    
    m_importButton = new QPushButton("Import from Variables");
    m_importButton->setIcon(QIcon("icon/Import_16px.png"));
    layout->addWidget(m_importButton, 0, 4);
    
    return group;
}

QGroupBox* CloudPointToolController::createAutoCollectGroup()
{
    QGroupBox* group = new QGroupBox("Auto-Collect Points");
    QGridLayout* layout = new QGridLayout(group);
    
    layout->addWidget(new QLabel("Count:"), 0, 0);
    m_autoCollectCountSpinBox = new QSpinBox();
    m_autoCollectCountSpinBox->setRange(3, 100);
    m_autoCollectCountSpinBox->setValue(9);
    layout->addWidget(m_autoCollectCountSpinBox, 0, 1);
    
    layout->addWidget(new QLabel("Interval (ms):"), 0, 2);
    m_autoCollectIntervalSpinBox = new QSpinBox();
    m_autoCollectIntervalSpinBox->setRange(500, 10000);
    m_autoCollectIntervalSpinBox->setValue(2000);
    layout->addWidget(m_autoCollectIntervalSpinBox, 0, 3);
    
    m_autoCollectRandomCheckBox = new QCheckBox("Random Positions");
    m_autoCollectRandomCheckBox->setChecked(true);
    layout->addWidget(m_autoCollectRandomCheckBox, 0, 4);
    
    m_autoCollectButton = new QPushButton("Start Auto-Collect");
    m_autoCollectButton->setIcon(QIcon("icon/Automatic_16px.png"));
    layout->addWidget(m_autoCollectButton, 0, 5);
    
    return group;
}

void CloudPointToolController::setupCalibrationTable()
{
    m_calibrationTable = new QTableWidget();
    m_calibrationTable->setColumnCount(ACTUAL_COLUMN_COUNT);
    
    // Set headers
    QStringList headers;
    headers << "Index" << "Image X" << "Image Y" << "Image Z" 
            << "Real X" << "Real Y" << "Real Z" << "Confidence" 
            << "Label" << "Error" << "Timestamp";
    m_calibrationTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    m_calibrationTable->setColumnWidth(COL_INDEX, 50);
    m_calibrationTable->setColumnWidth(COL_IMAGE_X, 80);
    m_calibrationTable->setColumnWidth(COL_IMAGE_Y, 80);
    m_calibrationTable->setColumnWidth(COL_IMAGE_Z, 80);
    m_calibrationTable->setColumnWidth(COL_REAL_X, 80);
    m_calibrationTable->setColumnWidth(COL_REAL_Y, 80);
    m_calibrationTable->setColumnWidth(COL_REAL_Z, 80);
    m_calibrationTable->setColumnWidth(COL_CONFIDENCE, 80);
    m_calibrationTable->setColumnWidth(COL_LABEL, 100);
    m_calibrationTable->setColumnWidth(COL_ERROR, 80);
    m_calibrationTable->setColumnWidth(COL_TIMESTAMP, 120);
    
    // Set properties
    m_calibrationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_calibrationTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_calibrationTable->setAlternatingRowColors(true);
    m_calibrationTable->setSortingEnabled(true);
    m_calibrationTable->setMaximumHeight(200);
    
    // Set style
    m_calibrationTable->setStyleSheet(
        "QTableWidget { background-color: rgb(40, 40, 45); color: rgb(255, 255, 255); }"
        "QTableWidget::item:selected { background-color: rgb(70, 70, 75); }"
        "QTableWidget::item:hover { background-color: rgb(60, 60, 65); }"
        "QHeaderView::section { background-color: rgb(51, 51, 55); color: rgb(208, 208, 209); }"
    );
}

void CloudPointToolController::setupInterpolationMethodCombo()
{
    m_interpolationMethodCombo->addItem("Linear", static_cast<int>(CloudPointMapper::LINEAR));
    m_interpolationMethodCombo->addItem("Bilinear", static_cast<int>(CloudPointMapper::BILINEAR));
    m_interpolationMethodCombo->addItem("Cubic Spline", static_cast<int>(CloudPointMapper::CUBIC_SPLINE));
    m_interpolationMethodCombo->addItem("Radial Basis", static_cast<int>(CloudPointMapper::RADIAL_BASIS));
    m_interpolationMethodCombo->addItem("Kriging", static_cast<int>(CloudPointMapper::KRIGING));
    
    // Set default to Bilinear
    m_interpolationMethodCombo->setCurrentIndex(1);
}

void CloudPointToolController::connectSignals()
{
    // Point management
    connect(m_addPointButton, &QPushButton::clicked, this, &CloudPointToolController::addCalibrationPoint);
    connect(m_updatePointButton, &QPushButton::clicked, this, &CloudPointToolController::updateCalibrationPoint);
    connect(m_removePointButton, &QPushButton::clicked, this, &CloudPointToolController::removeCalibrationPoint);
    connect(m_clearAllButton, &QPushButton::clicked, this, &CloudPointToolController::clearAllPoints);
    
    // Mapping operations
    connect(m_buildGridButton, &QPushButton::clicked, this, &CloudPointToolController::buildMappingGrid);
    connect(m_validateButton, &QPushButton::clicked, this, &CloudPointToolController::validateMapping);
    connect(m_transformTestButton, &QPushButton::clicked, this, &CloudPointToolController::transformTestPoint);
    
    // File operations
    connect(m_saveButton, &QPushButton::clicked, this, &CloudPointToolController::saveMapping);
    connect(m_loadButton, &QPushButton::clicked, this, &CloudPointToolController::loadMapping);
    
    // Variable Manager
    connect(m_exportButton, &QPushButton::clicked, this, &CloudPointToolController::exportToVariableManager);
    connect(m_importButton, &QPushButton::clicked, this, &CloudPointToolController::importFromVariableManager);
    
    // Utility functions
    connect(m_pasteButton, &QPushButton::clicked, this, &CloudPointToolController::pasteCoordinates);
    connect(m_getRobotPosButton, &QPushButton::clicked, this, &CloudPointToolController::getCurrentRobotPosition);
    connect(m_getImagePosButton, &QPushButton::clicked, this, &CloudPointToolController::getCurrentImagePosition);
    connect(m_autoCollectButton, &QPushButton::clicked, this, &CloudPointToolController::autoCollectPoints);
    connect(m_visualizeButton, &QPushButton::clicked, this, &CloudPointToolController::generateGridVisualization);
    connect(m_statsButton, &QPushButton::clicked, this, &CloudPointToolController::showMappingStats);
    
    // Settings
    connect(m_interpolationMethodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &CloudPointToolController::onInterpolationMethodChanged);
    connect(m_gridResolutionSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
            this, &CloudPointToolController::onGridResolutionChanged);
    connect(m_autoRebuildCheckBox, &QCheckBox::toggled, this, &CloudPointToolController::onAutoRebuildToggled);
    
    // Table events
    connect(m_calibrationTable, &QTableWidget::itemSelectionChanged, this, &CloudPointToolController::onTableSelectionChanged);
    connect(m_calibrationTable, &QTableWidget::itemDoubleClicked, this, &CloudPointToolController::onTableItemDoubleClicked);
}

// Public slots implementation

void CloudPointToolController::addCalibrationPoint()
{
    if (!validateAllInputs()) {
        return;
    }
    
    QVector3D imageCoord(getFloatValue(m_imageXEdit), getFloatValue(m_imageYEdit), getFloatValue(m_imageZEdit));
    QVector3D realCoord(getFloatValue(m_realXEdit), getFloatValue(m_realYEdit), getFloatValue(m_realZEdit));
    float confidence = m_confidenceSpinBox->value();
    QString label = m_labelEdit->text().trimmed();
    
    int index = m_mapper->addCalibrationPoint(imageCoord, realCoord, confidence, label);
    
    if (index >= 0) {
        updateCalibrationTable();
        clearInputs();
        showSuccess(QString("Added calibration point %1").arg(index));
    } else {
        showError("Failed to add calibration point");
    }
}

void CloudPointToolController::removeCalibrationPoint()
{
    int currentRow = m_calibrationTable->currentRow();
    if (currentRow < 0) {
        showError("Please select a calibration point to remove");
        return;
    }
    
    if (m_mapper->removeCalibrationPoint(currentRow)) {
        updateCalibrationTable();
        clearInputs();
        showSuccess("Removed calibration point");
    } else {
        showError("Failed to remove calibration point");
    }
}

void CloudPointToolController::updateCalibrationPoint()
{
    int currentRow = m_calibrationTable->currentRow();
    if (currentRow < 0) {
        showError("Please select a calibration point to update");
        return;
    }
    
    if (!validateAllInputs()) {
        return;
    }
    
    QVector3D imageCoord(getFloatValue(m_imageXEdit), getFloatValue(m_imageYEdit), getFloatValue(m_imageZEdit));
    QVector3D realCoord(getFloatValue(m_realXEdit), getFloatValue(m_realYEdit), getFloatValue(m_realZEdit));
    float confidence = m_confidenceSpinBox->value();
    
    if (m_mapper->updateCalibrationPoint(currentRow, imageCoord, realCoord, confidence)) {
        updateCalibrationTable();
        clearInputs();
        showSuccess("Updated calibration point");
    } else {
        showError("Failed to update calibration point");
    }
}

void CloudPointToolController::clearAllPoints()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        m_parent, 
        "Clear All Points", 
        "Are you sure you want to clear all calibration points?",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        m_mapper->clearMapping();
        updateCalibrationTable();
        clearInputs();
        showSuccess("Cleared all calibration points");
    }
}

void CloudPointToolController::buildMappingGrid()
{
    if (m_mapper->getPointCount() < 3) {
        showError("Need at least 3 calibration points to build grid");
        return;
    }
    
    float resolution = m_gridResolutionSpinBox->value();
    
    if (m_mapper->buildMappingGrid(resolution)) {
        updateStatsDisplay();
        showSuccess("Built mapping grid successfully");
    } else {
        showError("Failed to build mapping grid");
    }
}

void CloudPointToolController::validateMapping()
{
    if (m_mapper->getPointCount() < 5) {
        showError("Need at least 5 calibration points for validation");
        return;
    }
    
    // Show progress bar
    m_validationProgressBar->setVisible(true);
    m_validationProgressBar->setRange(0, 100);
    m_validationProgressBar->setValue(0);
    
    // Start validation timer
    m_validationTimer->start();
    
    // Perform validation (this will emit validationComplete signal)
    CloudPointMapper::MappingStats stats = m_mapper->validateMapping(0.2f);
    
    // Stop timer
    m_validationTimer->stop();
    m_validationProgressBar->setVisible(false);
    
    // Update display
    updateStatsDisplay();
    
    if (stats.isValid) {
        showSuccess(QString("Validation complete. Average error: %1 mm").arg(stats.averageError, 0, 'f', 2));
    } else {
        showError("Validation failed. Mapping may not be suitable for use.");
    }
}

void CloudPointToolController::transformTestPoint()
{
    if (m_mapper->getPointCount() < 3) {
        showError("Need at least 3 calibration points for transformation");
        return;
    }
    
    // Validate test inputs
    if (!validateCoordinateInput(m_testImageXEdit, "Test Image X") ||
        !validateCoordinateInput(m_testImageYEdit, "Test Image Y") ||
        !validateCoordinateInput(m_testImageZEdit, "Test Image Z")) {
        return;
    }
    
    QVector3D testPoint(getFloatValue(m_testImageXEdit), getFloatValue(m_testImageYEdit), getFloatValue(m_testImageZEdit));
    
    CloudPointMapper::InterpolationMethod method = static_cast<CloudPointMapper::InterpolationMethod>(
        m_interpolationMethodCombo->currentData().toInt());
    
    CloudPointMapper::MappingResult result = m_mapper->transformImageToReal(testPoint, method);
    
    if (result.isValid) {
        setFormattedValue(m_testRealXEdit, result.transformedPoint.x());
        setFormattedValue(m_testRealYEdit, result.transformedPoint.y());
        setFormattedValue(m_testRealZEdit, result.transformedPoint.z());
        
        m_testConfidenceLabel->setText(QString::number(result.confidence, 'f', 3));
        m_testErrorLabel->setText(QString::number(result.estimatedError, 'f', 2) + " mm");
        
        // Color-code confidence and error
        QString confidenceColor = result.confidence > 0.7 ? "green" : (result.confidence > 0.4 ? "orange" : "red");
        QString errorColor = result.estimatedError < 2.0 ? "green" : (result.estimatedError < 5.0 ? "orange" : "red");
        
        m_testConfidenceLabel->setStyleSheet(QString("color: %1; font-weight: bold;").arg(confidenceColor));
        m_testErrorLabel->setStyleSheet(QString("color: %1; font-weight: bold;").arg(errorColor));
        
        showSuccess("Test point transformed successfully");
    } else {
        showError(QString("Transformation failed: %1").arg(result.errorMessage));
    }
}

void CloudPointToolController::saveMapping()
{
    if (m_mapper->getPointCount() == 0) {
        showError("No calibration points to save");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(
        m_parent,
        "Save Cloud Point Mapping",
        getDefaultMappingPath(),
        "JSON Files (*.json);;All Files (*)"
    );
    
    if (!fileName.isEmpty()) {
        if (m_mapper->saveToFile(fileName)) {
            showSuccess("Mapping saved successfully");
        } else {
            showError("Failed to save mapping");
        }
    }
}

void CloudPointToolController::loadMapping()
{
    QString fileName = QFileDialog::getOpenFileName(
        m_parent,
        "Load Cloud Point Mapping",
        getDefaultMappingPath(),
        "JSON Files (*.json);;All Files (*)"
    );
    
    if (!fileName.isEmpty()) {
        if (m_mapper->loadFromFile(fileName)) {
            updateCalibrationTable();
            updateStatsDisplay();
            showSuccess("Mapping loaded successfully");
        } else {
            showError("Failed to load mapping");
        }
    }
}

void CloudPointToolController::exportToVariableManager()
{
    if (m_mapper->getPointCount() == 0) {
        showError("No calibration points to export");
        return;
    }
    
    QString variableName = m_variableNameEdit->text().trimmed();
    if (variableName.isEmpty()) {
        variableName = getDefaultVariableName();
        m_variableNameEdit->setText(variableName);
    }
    
    if (m_mapper->exportToVariableManager(variableName)) {
        showSuccess(QString("Exported mapping to variable: %1").arg(variableName));
    } else {
        showError("Failed to export mapping to VariableManager");
    }
}

void CloudPointToolController::importFromVariableManager()
{
    QString variableName = m_variableNameEdit->text().trimmed();
    if (variableName.isEmpty()) {
        variableName = getDefaultVariableName();
        m_variableNameEdit->setText(variableName);
    }
    
    if (m_mapper->importFromVariableManager(variableName)) {
        updateCalibrationTable();
        updateStatsDisplay();
        showSuccess(QString("Imported mapping from variable: %1").arg(variableName));
    } else {
        showError("Failed to import mapping from VariableManager");
    }
}

// Helper methods

void CloudPointToolController::updateCalibrationTable()
{
    // Check if objects are still valid before updating
    if (!m_calibrationTable || !m_mapper) {
        return;
    }
    
    m_calibrationTable->setRowCount(m_mapper->getPointCount());
    
    for (int i = 0; i < m_mapper->getPointCount(); ++i) {
        const CloudPointMapper::CalibrationPoint& point = m_mapper->getCalibrationPoint(i);
        
        m_calibrationTable->setItem(i, COL_INDEX, new QTableWidgetItem(QString::number(i)));
        m_calibrationTable->setItem(i, COL_IMAGE_X, new QTableWidgetItem(QString::number(point.imageCoord.x(), 'f', 2)));
        m_calibrationTable->setItem(i, COL_IMAGE_Y, new QTableWidgetItem(QString::number(point.imageCoord.y(), 'f', 2)));
        m_calibrationTable->setItem(i, COL_IMAGE_Z, new QTableWidgetItem(QString::number(point.imageCoord.z(), 'f', 2)));
        m_calibrationTable->setItem(i, COL_REAL_X, new QTableWidgetItem(QString::number(point.realCoord.x(), 'f', 2)));
        m_calibrationTable->setItem(i, COL_REAL_Y, new QTableWidgetItem(QString::number(point.realCoord.y(), 'f', 2)));
        m_calibrationTable->setItem(i, COL_REAL_Z, new QTableWidgetItem(QString::number(point.realCoord.z(), 'f', 2)));
        m_calibrationTable->setItem(i, COL_CONFIDENCE, new QTableWidgetItem(QString::number(point.confidence, 'f', 3)));
        m_calibrationTable->setItem(i, COL_LABEL, new QTableWidgetItem(point.label));
        m_calibrationTable->setItem(i, COL_ERROR, new QTableWidgetItem(QString::number(point.error, 'f', 2)));
        m_calibrationTable->setItem(i, COL_TIMESTAMP, new QTableWidgetItem(point.timestamp.toString("hh:mm:ss")));
    }
    
    updateButtonStates();
}

void CloudPointToolController::updateStatsDisplay()
{
    // Check if objects are still valid before updating
    if (!m_mapper || !m_statsTextEdit) {
        return;
    }
    
    CloudPointMapper::MappingStats stats = m_mapper->getMappingStats();
    
    QString statsText;
    statsText += QString("Points: %1\n").arg(stats.totalPoints);
    statsText += QString("Average Error: %1 mm\n").arg(stats.averageError, 0, 'f', 2);
    statsText += QString("Max Error: %1 mm\n").arg(stats.maxError, 0, 'f', 2);
    statsText += QString("Min Error: %1 mm\n").arg(stats.minError, 0, 'f', 2);
    statsText += QString("Std Deviation: %1 mm\n").arg(stats.stdDeviation, 0, 'f', 2);
    statsText += QString("Coverage: %1%\n").arg(stats.coverage, 0, 'f', 1);
    statsText += QString("Workspace: (%1,%2) to (%3,%4)\n")
                .arg(stats.workspaceMin.x(), 0, 'f', 1)
                .arg(stats.workspaceMin.y(), 0, 'f', 1)
                .arg(stats.workspaceMax.x(), 0, 'f', 1)
                .arg(stats.workspaceMax.y(), 0, 'f', 1);
    statsText += QString("Valid: %1").arg(stats.isValid ? "Yes" : "No");
    
    m_statsTextEdit->setPlainText(statsText);
}

void CloudPointToolController::updateButtonStates()
{
    // Check if objects are still valid before updating
    if (!m_mapper || !m_calibrationTable || !m_removePointButton || !m_updatePointButton || 
        !m_clearAllButton || !m_buildGridButton || !m_validateButton) {
        return;
    }
    
    bool hasPoints = m_mapper->getPointCount() > 0;
    bool hasSelection = m_calibrationTable->currentRow() >= 0;
    bool hasEnoughPoints = m_mapper->getPointCount() >= 3;
    
    m_removePointButton->setEnabled(hasSelection);
    m_updatePointButton->setEnabled(hasSelection);
    m_clearAllButton->setEnabled(hasPoints);
    m_buildGridButton->setEnabled(hasEnoughPoints);
    m_validateButton->setEnabled(m_mapper->getPointCount() >= 5);
    m_transformTestButton->setEnabled(hasEnoughPoints);
    m_saveButton->setEnabled(hasPoints);
    m_exportButton->setEnabled(hasPoints);
    m_visualizeButton->setEnabled(hasEnoughPoints);
    m_statsButton->setEnabled(hasPoints);
}

void CloudPointToolController::clearInputs()
{
    m_imageXEdit->clear();
    m_imageYEdit->clear();
    m_imageZEdit->clear();
    m_realXEdit->clear();
    m_realYEdit->clear();
    m_realZEdit->clear();
    m_confidenceSpinBox->setValue(1.0);
    m_labelEdit->clear();
}

bool CloudPointToolController::validateAllInputs()
{
    return validateCoordinateInput(m_imageXEdit, "Image X") &&
           validateCoordinateInput(m_imageYEdit, "Image Y") &&
           validateCoordinateInput(m_imageZEdit, "Image Z") &&
           validateCoordinateInput(m_realXEdit, "Real X") &&
           validateCoordinateInput(m_realYEdit, "Real Y") &&
           validateCoordinateInput(m_realZEdit, "Real Z");
}

bool CloudPointToolController::validateCoordinateInput(QLineEdit* edit, const QString& fieldName)
{
    if (!edit) return false;
    
    QString text = edit->text().trimmed();
    if (text.isEmpty()) {
        showError(QString("%1 cannot be empty").arg(fieldName));
        return false;
    }
    
    bool ok;
    float value = text.toFloat(&ok);
    if (!ok) {
        showError(QString("%1 must be a valid number").arg(fieldName));
        return false;
    }
    
    return true;
}

void CloudPointToolController::setFormattedValue(QLineEdit* edit, float value)
{
    if (edit) {
        edit->setText(QString::number(value, 'f', 3));
    }
}

float CloudPointToolController::getFloatValue(QLineEdit* edit)
{
    if (edit) {
        return edit->text().toFloat();
    }
    return 0.0f;
}

QString CloudPointToolController::getDefaultMappingPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/CloudPointMappings/";
}

QString CloudPointToolController::getDefaultVariableName()
{
    return "CloudMapping";
}

void CloudPointToolController::showError(const QString& message)
{
    if (m_parent) {
        QMessageBox::critical(m_parent, "Cloud Point Mapping Error", message);
    }
}

void CloudPointToolController::showSuccess(const QString& message)
{
    if (m_parent) {
        QMessageBox::information(m_parent, "Cloud Point Mapping", message);
    }
}

void CloudPointToolController::showInfo(const QString& message)
{
    if (m_parent) {
        QMessageBox::information(m_parent, "Cloud Point Mapping", message);
    }
}

// Signal handlers

void CloudPointToolController::onMappingUpdated()
{
    updateCalibrationTable();
    updateStatsDisplay();
    updateButtonStates();
}

void CloudPointToolController::onValidationComplete(const CloudPointMapper::MappingStats& stats)
{
    // Check if objects are still valid before updating
    if (!m_validationProgressBar) {
        return;
    }
    
    updateStatsDisplay();
    m_validationProgressBar->setValue(100);
}

void CloudPointToolController::onErrorOccurred(const QString& error)
{
    showError(error);
}

void CloudPointToolController::updateValidationProgress()
{
    // Check if objects are still valid before updating
    if (!m_validationProgressBar) {
        return;
    }
    
    int value = m_validationProgressBar->value();
    if (value < 90) {
        m_validationProgressBar->setValue(value + 10);
    }
}

void CloudPointToolController::onTableSelectionChanged()
{
    int currentRow = m_calibrationTable->currentRow();
    if (currentRow >= 0 && currentRow < m_mapper->getPointCount()) {
        loadInputsFromTableSelection();
    }
    updateButtonStates();
}

void CloudPointToolController::loadInputsFromTableSelection()
{
    int currentRow = m_calibrationTable->currentRow();
    if (currentRow >= 0 && currentRow < m_mapper->getPointCount()) {
        const CloudPointMapper::CalibrationPoint& point = m_mapper->getCalibrationPoint(currentRow);
        
        setFormattedValue(m_imageXEdit, point.imageCoord.x());
        setFormattedValue(m_imageYEdit, point.imageCoord.y());
        setFormattedValue(m_imageZEdit, point.imageCoord.z());
        setFormattedValue(m_realXEdit, point.realCoord.x());
        setFormattedValue(m_realYEdit, point.realCoord.y());
        setFormattedValue(m_realZEdit, point.realCoord.z());
        m_confidenceSpinBox->setValue(point.confidence);
        m_labelEdit->setText(point.label);
    }
}

void CloudPointToolController::onTableItemDoubleClicked(QTableWidgetItem* item)
{
    if (item) {
        loadInputsFromTableSelection();
    }
}

void CloudPointToolController::onInterpolationMethodChanged(int method)
{
    // Update mapper's default method if needed
    // This is handled during transform operations
}

void CloudPointToolController::onGridResolutionChanged(double resolution)
{
    m_mapper->setGridResolution(resolution);
}

void CloudPointToolController::onAutoRebuildToggled(bool enabled)
{
    m_mapper->setAutoRebuild(enabled);
}

void CloudPointToolController::pasteCoordinates()
{
    QString clipboardText = m_clipboard->text().trimmed();
    if (clipboardText.isEmpty()) {
        showError("Clipboard is empty");
        return;
    }
    
    // Try to parse clipboard text
    QStringList parts = clipboardText.split(QRegExp("[,\\s]+"));
    if (parts.size() >= 6) {
        // Assume format: imageX, imageY, imageZ, realX, realY, realZ
        m_imageXEdit->setText(parts[0]);
        m_imageYEdit->setText(parts[1]);
        m_imageZEdit->setText(parts[2]);
        m_realXEdit->setText(parts[3]);
        m_realYEdit->setText(parts[4]);
        m_realZEdit->setText(parts[5]);
        showSuccess("Coordinates pasted successfully");
    } else {
        showError("Invalid clipboard format. Expected: imageX, imageY, imageZ, realX, realY, realZ");
    }
}

void CloudPointToolController::getCurrentRobotPosition()
{
    if (!m_parent) return;
    
    // Get current robot position from RobotParameters
    int robotId = m_parent->RbID;
    if (robotId >= 0 && robotId < m_parent->RobotParameters.size()) {
        const auto& robotPara = m_parent->RobotParameters[robotId];
        setFormattedValue(m_realXEdit, robotPara.X);
        setFormattedValue(m_realYEdit, robotPara.Y);
        setFormattedValue(m_realZEdit, robotPara.Z);
        showSuccess("Got current robot position");
    } else {
        showError("No robot position available");
    }
}

void CloudPointToolController::getCurrentImagePosition()
{
    if (!m_parent) return;
    
    // Get current image position from ImageViewer
    QPointF imagePos = m_parent->ui->gvImageViewer->GetPoint1();
    setFormattedValue(m_imageXEdit, imagePos.x());
    setFormattedValue(m_imageYEdit, imagePos.y());
    setFormattedValue(m_imageZEdit, 0.0f); // Assume Z=0 for 2D image
    showSuccess("Got current image position");
}

void CloudPointToolController::autoCollectPoints()
{
    showInfo("Auto-collect functionality not yet implemented");
}

void CloudPointToolController::generateGridVisualization()
{
    showInfo("Grid visualization functionality not yet implemented");
}

void CloudPointToolController::showMappingStats()
{
    CloudPointMapper::MappingStats stats = m_mapper->getMappingStats();
    
    QString statsMessage;
    statsMessage += QString("=== Cloud Point Mapping Statistics ===\n\n");
    statsMessage += QString("Total Points: %1\n").arg(stats.totalPoints);
    statsMessage += QString("Average Error: %1 mm\n").arg(stats.averageError, 0, 'f', 3);
    statsMessage += QString("Maximum Error: %1 mm\n").arg(stats.maxError, 0, 'f', 3);
    statsMessage += QString("Minimum Error: %1 mm\n").arg(stats.minError, 0, 'f', 3);
    statsMessage += QString("Standard Deviation: %1 mm\n").arg(stats.stdDeviation, 0, 'f', 3);
    statsMessage += QString("Coverage: %1%\n").arg(stats.coverage, 0, 'f', 1);
    statsMessage += QString("\nWorkspace Bounds:\n");
    statsMessage += QString("Min: (%1, %2, %3)\n").arg(stats.workspaceMin.x(), 0, 'f', 1).arg(stats.workspaceMin.y(), 0, 'f', 1).arg(stats.workspaceMin.z(), 0, 'f', 1);
    statsMessage += QString("Max: (%1, %2, %3)\n").arg(stats.workspaceMax.x(), 0, 'f', 1).arg(stats.workspaceMax.y(), 0, 'f', 1).arg(stats.workspaceMax.z(), 0, 'f', 1);
    statsMessage += QString("\nMapping Valid: %1\n").arg(stats.isValid ? "YES" : "NO");
    
    QMessageBox::information(m_parent, "Mapping Statistics", statsMessage);
}

void CloudPointToolController::setUIEnabled(bool enabled)
{
    if (m_mainGroupBox) {
        m_mainGroupBox->setEnabled(enabled);
    }
} 