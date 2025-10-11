#include "CloudPointToolController.h"
#include "RobotWindow.h"
#include "ui_RobotWindow.h"
#include <QSplitter>
#include <QScrollArea>
#include <QStyleOption>
#include <QPainter>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QTableWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QFrame>
#include <QApplication>
#include <QClipboard>
#include <QInputDialog> // Added for input dialogs
#include <QStringList>

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
    , m_pointCountLabel(nullptr)
    , m_avgErrorLabel(nullptr)
    , m_maxErrorLabel(nullptr)
    , m_coverageLabel(nullptr)
    , m_testConfidenceEdit(nullptr)
    , m_testErrorEdit(nullptr)
    , m_testImageXEdit(nullptr)
    , m_testImageYEdit(nullptr)
    , m_testImageZEdit(nullptr)
    , m_testRealXEdit(nullptr)
    , m_testRealYEdit(nullptr)
    , m_testRealZEdit(nullptr)
    , m_testConfidenceLabel(nullptr)
    , m_testErrorLabel(nullptr)
    , m_addPointButton(nullptr)
    , m_removePointButton(nullptr)
    , m_updatePointButton(nullptr)
    , m_clearAllButton(nullptr)
    , m_buildGridButton(nullptr)
    , m_validateButton(nullptr)
    , m_transformTestButton(nullptr)
    , m_saveButton(nullptr)
    , m_loadButton(nullptr)
    , m_exportButton(nullptr)
    , m_importButton(nullptr)
    , m_visualizeButton(nullptr)
    , m_statsButton(nullptr)
    , m_variableNameEdit(nullptr)
    , m_autoCollectCountSpinBox(nullptr)
    , m_autoCollectIntervalSpinBox(nullptr)
    , m_autoCollectRandomCheckBox(nullptr)
    , m_autoCollectButton(nullptr)
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
        qDebug() << "CloudPointToolController: Invalid parent widget";
        return;
    }
    
    // Cast parentWidget to RobotWindow to access UI elements
    RobotWindow* robotWindow = qobject_cast<RobotWindow*>(parentWidget->window());
    if (!robotWindow) {
        qDebug() << "CloudPointToolController: Cannot access RobotWindow UI elements";
        return;
    }
    
    // Find the existing Cloud Point Mapping group box from RobotWindow.ui
    m_mainGroupBox = robotWindow->findChild<QGroupBox*>("gbCloudPointMapping");
    if (!m_mainGroupBox) {
        qDebug() << "CloudPointToolController: Cloud Point Mapping UI elements not found in RobotWindow.ui";
        return;
    }
    
    // Instead of clearing existing UI, find and connect to existing elements from .ui file
    // Find existing UI elements from RobotWindow.ui
    
    // Settings elements
    m_interpolationMethodCombo = robotWindow->findChild<QComboBox*>("cbInterpolationMethod");
    if (m_interpolationMethodCombo) {
        // Populate interpolation method combo if found
        if (m_interpolationMethodCombo->count() == 0) {
            m_interpolationMethodCombo->addItems({
                "Linear", "Bilinear", "Cubic Spline", "Radial Basis Function", "Kriging"
            });
        }
    }
    
    m_gridResolutionSpinBox = robotWindow->findChild<QSpinBox*>("sbGridResolution");
    m_autoRebuildCheckBox = robotWindow->findChild<QCheckBox*>("cbAutoRebuild");
    
    // Calibration table and management
    m_calibrationTable = robotWindow->findChild<QTableWidget*>("tableCalibrationPoints");
    
    // Calibration point management buttons
    m_addPointButton = robotWindow->findChild<QPushButton*>("pbAddCalibrationPoint");
    m_removePointButton = robotWindow->findChild<QPushButton*>("pbRemoveCalibrationPoint");
    m_clearAllButton = robotWindow->findChild<QPushButton*>("pbClearCalibrationPoints");
    m_buildGridButton = robotWindow->findChild<QPushButton*>("pbRebuildMapping");
    m_validateButton = robotWindow->findChild<QPushButton*>("pbValidateMapping");
    
    // Test elements
    m_testImageXEdit = robotWindow->findChild<QLineEdit*>("leCloudTestInputX");
    m_testImageYEdit = robotWindow->findChild<QLineEdit*>("leCloudTestInputY");
    m_testRealXEdit = robotWindow->findChild<QLineEdit*>("leCloudTestOutputX");
    m_testRealYEdit = robotWindow->findChild<QLineEdit*>("leCloudTestOutputY");
    
    // These are readonly QLineEdit elements in the UI file - save as member variables
    m_testConfidenceEdit = robotWindow->findChild<QLineEdit*>("leCloudTestConfidence");
    m_testErrorEdit = robotWindow->findChild<QLineEdit*>("leCloudTestError");
    m_transformTestButton = robotWindow->findChild<QPushButton*>("pbTransformCloudPoint");
    
    // File operation buttons
    m_saveButton = robotWindow->findChild<QPushButton*>("pbSaveCloudMapping");
    m_loadButton = robotWindow->findChild<QPushButton*>("pbLoadCloudMapping");
    m_exportButton = robotWindow->findChild<QPushButton*>("pbExportToVariables");
    m_importButton = robotWindow->findChild<QPushButton*>("pbImportFromVariables");
    
    // Stats labels
    m_pointCountLabel = robotWindow->findChild<QLabel*>("lbPointCount");
    m_avgErrorLabel = robotWindow->findChild<QLabel*>("lbAvgError");
    m_maxErrorLabel = robotWindow->findChild<QLabel*>("lbMaxError");
    m_coverageLabel = robotWindow->findChild<QLabel*>("lbCoverage");
    
    // Find frames (for potential future use)
    QFrame* calibrationFrame = robotWindow->findChild<QFrame*>("frameCloudPointCalibration");
    QFrame* settingsFrame = robotWindow->findChild<QFrame*>("frameCloudPointSettings");
    QFrame* testFrame = robotWindow->findChild<QFrame*>("frameCloudPointTest");
    QFrame* statsFrame = robotWindow->findChild<QFrame*>("frameCloudPointStats");
    QFrame* buttonsFrame = robotWindow->findChild<QFrame*>("frameCloudPointButtons");
    QFrame* filesFrame = robotWindow->findChild<QFrame*>("frameCloudPointFiles");
    
    // Try to reuse existing validation progress bar or create one programmatically
    m_validationProgressBar = robotWindow->findChild<QProgressBar*>("pbCloudValidationProgress");
    if (!m_validationProgressBar && statsFrame) {
        if (QGridLayout* statsLayout = qobject_cast<QGridLayout*>(statsFrame->layout())) {
            m_validationProgressBar = new QProgressBar(statsFrame);
            m_validationProgressBar->setObjectName("pbCloudValidationProgress");
            m_validationProgressBar->setRange(0, 100);
            m_validationProgressBar->setValue(0);
            m_validationProgressBar->setVisible(false);
            statsLayout->addWidget(m_validationProgressBar, 1, 0, 1, 9);
        }
    } else if (m_validationProgressBar) {
        m_validationProgressBar->setRange(0, 100);
        m_validationProgressBar->setValue(0);
        m_validationProgressBar->setVisible(false);
    }
    
    // Log what we found vs what we expected
    qDebug() << "=== Cloud Point Mapping UI Elements Status ===";
    qDebug() << "Settings:";
    qDebug() << "  Interpolation combo:" << (m_interpolationMethodCombo != nullptr);
    qDebug() << "  Grid resolution spinbox:" << (m_gridResolutionSpinBox != nullptr);
    qDebug() << "  Auto rebuild checkbox:" << (m_autoRebuildCheckBox != nullptr);
    
    qDebug() << "Calibration Management:";
    qDebug() << "  Calibration table:" << (m_calibrationTable != nullptr);
    qDebug() << "  Add point button:" << (m_addPointButton != nullptr);
    qDebug() << "  Remove point button:" << (m_removePointButton != nullptr);  
    qDebug() << "  Clear all button:" << (m_clearAllButton != nullptr);
    qDebug() << "  Build grid button:" << (m_buildGridButton != nullptr);
    qDebug() << "  Validate button:" << (m_validateButton != nullptr);
    
    qDebug() << "Test Transform:";
    qDebug() << "  Test input X/Y:" << (m_testImageXEdit != nullptr) << "/" << (m_testImageYEdit != nullptr);
    qDebug() << "  Test output X/Y:" << (m_testRealXEdit != nullptr) << "/" << (m_testRealYEdit != nullptr);
    qDebug() << "  Transform button:" << (m_transformTestButton != nullptr);
    qDebug() << "  Confidence/Error displays:" << (m_testConfidenceEdit != nullptr) << "/" << (m_testErrorEdit != nullptr);
    
    qDebug() << "File Operations:";
    qDebug() << "  Save/Load buttons:" << (m_saveButton != nullptr) << "/" << (m_loadButton != nullptr);
    
    qDebug() << "Frames:";
    qDebug() << "  Settings/Calibration/Test/Stats/Buttons/Files:" << (settingsFrame != nullptr) 
             << "/" << (calibrationFrame != nullptr) << "/" << (testFrame != nullptr) 
             << "/" << (statsFrame != nullptr) << "/" << (buttonsFrame != nullptr) 
             << "/" << (filesFrame != nullptr);
    
    QStringList missingElements;
    if (!m_updatePointButton) {
        missingElements << "Calibration point update controls";
    }
    if (!m_exportButton || !m_importButton) {
        missingElements << "VariableManager export/import buttons";
    }
    if (!m_pointCountLabel || !m_avgErrorLabel || !m_maxErrorLabel || !m_coverageLabel) {
        missingElements << "Statistics display labels";
    }
    if (!m_validationProgressBar) {
        missingElements << "Validation progress bar";
    }
    if (!missingElements.isEmpty()) {
        qDebug() << "Missing Elements (need to be created dynamically or added to .ui):";
        for (const QString& item : missingElements) {
            qDebug() << "  -" << item;
        }
    }
    
    // Connect all signals to existing UI elements
    connectSignals();
    
    // Initial UI update
    updateButtonStates();
    updateStatsDisplay();
    
    qDebug() << "Cloud Point Mapping initialized successfully";
}

CloudPointMapper* CloudPointToolController::getMapper() const
{
    return m_mapper;
}

// createUI() method removed - now using existing UI elements from RobotWindow.ui

// Comment out all create*Group methods since we're using UI elements from .ui file
/*
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
    
    buttonLayout->addStretch();
    
    // Add layouts to main layout
    layout->addLayout(inputLayout);
    layout->addLayout(buttonLayout);
    
    // Add calibration table
    setupCalibrationTable();
    layout->addWidget(m_calibrationTable);
    
    return group;
}
*/ 

// All other create*Group methods are also commented out since we use .ui file elements

/*
QGroupBox* CloudPointToolController::createTestPointGroup()
{
    QGroupBox* group = new QGroupBox("Test Point");
    QGridLayout* layout = new QGridLayout(group);
    
    // Input coordinates
    layout->addWidget(new QLabel("Image X:"), 0, 0);
    m_testImageXEdit = new QLineEdit();
    m_testImageXEdit->setPlaceholderText("0.0");
    layout->addWidget(m_testImageXEdit, 0, 1);
    
    layout->addWidget(new QLabel("Image Y:"), 0, 2);
    m_testImageYEdit = new QLineEdit();
    m_testImageYEdit->setPlaceholderText("0.0");
    layout->addWidget(m_testImageYEdit, 0, 3);
    
    layout->addWidget(new QLabel("Image Z:"), 0, 4);
    m_testImageZEdit = new QLineEdit();
    m_testImageZEdit->setPlaceholderText("0.0");
    layout->addWidget(m_testImageZEdit, 0, 5);
    
    // Transform button
    m_transformTestButton = new QPushButton("Transform");
    m_transformTestButton->setIcon(QIcon("icon/Transform_16px.png"));
    layout->addWidget(m_transformTestButton, 0, 6);
    
    // Output coordinates (read-only)
    layout->addWidget(new QLabel("Real X:"), 1, 0);
    m_testRealXEdit = new QLineEdit();
    m_testRealXEdit->setReadOnly(true);
    layout->addWidget(m_testRealXEdit, 1, 1);
    
    layout->addWidget(new QLabel("Real Y:"), 1, 2);
    m_testRealYEdit = new QLineEdit();
    m_testRealYEdit->setReadOnly(true);
    layout->addWidget(m_testRealYEdit, 1, 3);
    
    layout->addWidget(new QLabel("Real Z:"), 1, 4);
    m_testRealZEdit = new QLineEdit();
    m_testRealZEdit->setReadOnly(true);
    layout->addWidget(m_testRealZEdit, 1, 5);
    
    // Confidence and error display
    layout->addWidget(new QLabel("Confidence:"), 2, 0);
    m_testConfidenceLabel = new QLabel("---");
    m_testConfidenceLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(m_testConfidenceLabel, 2, 1);
    
    layout->addWidget(new QLabel("Error:"), 2, 2);
    m_testErrorLabel = new QLabel("---");
    m_testErrorLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(m_testErrorLabel, 2, 3);
    
    return group;
}

QGroupBox* CloudPointToolController::createControlButtonsGroup()
{
    QGroupBox* group = new QGroupBox("Operations");
    QHBoxLayout* layout = new QHBoxLayout(group);
    
    m_clearAllButton = new QPushButton("Clear All");
    m_clearAllButton->setIcon(QIcon("icon/Clear_16px.png"));
    layout->addWidget(m_clearAllButton);
    
    m_visualizeButton = new QPushButton("Visualize");
    m_visualizeButton->setIcon(QIcon("icon/View_16px.png"));
    layout->addWidget(m_visualizeButton);
    
    layout->addStretch();
    
    return group;
}

QGroupBox* CloudPointToolController::createStatsGroup()
{
    QGroupBox* group = new QGroupBox("Statistics");
    QVBoxLayout* layout = new QVBoxLayout(group);
    
    m_statsButton = new QPushButton("Show Statistics");
    m_statsButton->setIcon(QIcon("icon/Stats_16px.png"));
    layout->addWidget(m_statsButton);
    
    m_statsTextEdit = new QTextEdit();
    m_statsTextEdit->setMaximumHeight(100);
    m_statsTextEdit->setReadOnly(true);
    layout->addWidget(m_statsTextEdit);
    
    return group;
}

QGroupBox* CloudPointToolController::createVariableManagerGroup()
{
    QGroupBox* group = new QGroupBox("Variable Manager");
    QGridLayout* layout = new QGridLayout(group);
    
    layout->addWidget(new QLabel("Variable Name:"), 0, 0);
    m_variableNameEdit = new QLineEdit();
    m_variableNameEdit->setText("CloudMapping");
    layout->addWidget(m_variableNameEdit, 0, 1);
    
    m_exportButton = new QPushButton("Export");
    m_exportButton->setIcon(QIcon("icon/Export_16px.png"));
    layout->addWidget(m_exportButton, 0, 2);
    
    m_importButton = new QPushButton("Import");
    m_importButton->setIcon(QIcon("icon/Import_16px.png"));
    layout->addWidget(m_importButton, 0, 3);
    
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
*/

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
    // Only connect signals for UI elements that exist in the .ui file
    
    // Transform test button (exists in UI)
    if (m_transformTestButton) {
        connect(m_transformTestButton, &QPushButton::clicked, this, &CloudPointToolController::transformTestPoint);
    }
    
    // File operations (exist in UI)
    if (m_saveButton) {
        connect(m_saveButton, &QPushButton::clicked, this, &CloudPointToolController::saveMapping);
    }
    if (m_loadButton) {
        connect(m_loadButton, &QPushButton::clicked, this, &CloudPointToolController::loadMapping);
    }
    if (m_exportButton) {
        connect(m_exportButton, &QPushButton::clicked, this, &CloudPointToolController::exportToVariableManager);
    }
    if (m_importButton) {
        connect(m_importButton, &QPushButton::clicked, this, &CloudPointToolController::importFromVariableManager);
    }
    
    // Settings (exists in UI)
    if (m_interpolationMethodCombo) {
        connect(m_interpolationMethodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
                this, &CloudPointToolController::onInterpolationMethodChanged);
    }
    if (m_gridResolutionSpinBox) {
        connect(m_gridResolutionSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
                this, &CloudPointToolController::onGridResolutionChanged);
    }
    if (m_autoRebuildCheckBox) {
        connect(m_autoRebuildCheckBox, &QCheckBox::toggled, this, &CloudPointToolController::onAutoRebuildToggled);
    }
    
    // Calibration management (exists in UI)
    if (m_addPointButton) {
        connect(m_addPointButton, &QPushButton::clicked, this, &CloudPointToolController::addCalibrationPoint);
    }
    if (m_removePointButton) {
        connect(m_removePointButton, &QPushButton::clicked, this, &CloudPointToolController::removeCalibrationPoint);
    }
    if (m_clearAllButton) {
        connect(m_clearAllButton, &QPushButton::clicked, this, &CloudPointToolController::clearAllPoints);
    }
    if (m_buildGridButton) {
        connect(m_buildGridButton, &QPushButton::clicked, this, &CloudPointToolController::buildMappingGrid);
    }
    if (m_validateButton) {
        connect(m_validateButton, &QPushButton::clicked, this, &CloudPointToolController::validateMapping);
    }
    
    // Test elements (exists in UI)
    if (m_testImageXEdit) {
        connect(m_testImageXEdit, &QLineEdit::textChanged, this, &CloudPointToolController::onTestInputChanged);
    }
    if (m_testImageYEdit) {
        connect(m_testImageYEdit, &QLineEdit::textChanged, this, &CloudPointToolController::onTestInputChanged);
    }
    if (m_testRealXEdit) {
        // m_testRealXEdit is readonly, so no textChanged signal
    }
    if (m_testRealYEdit) {
        // m_testRealYEdit is readonly, so no textChanged signal
    }
    if (m_testConfidenceEdit) {
        // m_testConfidenceEdit is readonly, so no textChanged signal
    }
    if (m_testErrorEdit) {
        // m_testErrorEdit is readonly, so no textChanged signal
    }
    
    // Calibration table (exists in UI)
    if (m_calibrationTable) {
        connect(m_calibrationTable, &QTableWidget::itemSelectionChanged, this, &CloudPointToolController::onTableSelectionChanged);
        connect(m_calibrationTable, &QTableWidget::itemDoubleClicked, this, &CloudPointToolController::onTableItemDoubleClicked);
    }
    
    qDebug() << "Connected signals for available UI elements";
}

// Public slots implementation

void CloudPointToolController::addCalibrationPoint()
{
    // Use input dialogs since UI file doesn't have input fields for calibration points
    bool ok;
    
    // Get Image coordinates
    double imageX = QInputDialog::getDouble(m_parent, "Add Calibration Point", 
                                           "Image X:", 0.0, -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double imageY = QInputDialog::getDouble(m_parent, "Add Calibration Point", 
                                           "Image Y:", 0.0, -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double imageZ = QInputDialog::getDouble(m_parent, "Add Calibration Point", 
                                           "Image Z:", 0.0, -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    // Get Real coordinates
    double realX = QInputDialog::getDouble(m_parent, "Add Calibration Point", 
                                          "Real X:", 0.0, -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double realY = QInputDialog::getDouble(m_parent, "Add Calibration Point", 
                                          "Real Y:", 0.0, -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double realZ = QInputDialog::getDouble(m_parent, "Add Calibration Point", 
                                          "Real Z:", 0.0, -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    // Get Confidence
    double confidence = QInputDialog::getDouble(m_parent, "Add Calibration Point", 
                                               "Confidence (0.0-1.0):", 1.0, 0.0, 1.0, 2, &ok);
    if (!ok) return;
    
    // Get Label (optional)
    QString label = QInputDialog::getText(m_parent, "Add Calibration Point", 
                                         "Label (optional):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    
    // Create calibration point
    QVector3D imageCoord(imageX, imageY, imageZ);
    QVector3D realCoord(realX, realY, realZ);
    
    int index = m_mapper->addCalibrationPoint(imageCoord, realCoord, confidence, label);
    
    if (index >= 0) {
        updateCalibrationTable();
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
    
    // Get current calibration point data
    const CloudPointMapper::CalibrationPoint& currentPoint = m_mapper->getCalibrationPoint(currentRow);
    
    // Use input dialogs with current values as defaults
    bool ok;
    
    // Get Image coordinates
    double imageX = QInputDialog::getDouble(m_parent, "Update Calibration Point", 
                                           "Image X:", currentPoint.imageCoord.x(), -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double imageY = QInputDialog::getDouble(m_parent, "Update Calibration Point", 
                                           "Image Y:", currentPoint.imageCoord.y(), -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double imageZ = QInputDialog::getDouble(m_parent, "Update Calibration Point", 
                                           "Image Z:", currentPoint.imageCoord.z(), -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    // Get Real coordinates
    double realX = QInputDialog::getDouble(m_parent, "Update Calibration Point", 
                                          "Real X:", currentPoint.realCoord.x(), -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double realY = QInputDialog::getDouble(m_parent, "Update Calibration Point", 
                                          "Real Y:", currentPoint.realCoord.y(), -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    double realZ = QInputDialog::getDouble(m_parent, "Update Calibration Point", 
                                          "Real Z:", currentPoint.realCoord.z(), -9999.0, 9999.0, 2, &ok);
    if (!ok) return;
    
    // Get Confidence
    double confidence = QInputDialog::getDouble(m_parent, "Update Calibration Point", 
                                               "Confidence (0.0-1.0):", currentPoint.confidence, 0.0, 1.0, 2, &ok);
    if (!ok) return;
    
    // Create updated calibration point
    QVector3D imageCoord(imageX, imageY, imageZ);
    QVector3D realCoord(realX, realY, realZ);
    
    if (m_mapper->updateCalibrationPoint(currentRow, imageCoord, realCoord, confidence)) {
        updateCalibrationTable();
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
    
    // Show progress bar if available
    if (m_validationProgressBar) {
        m_validationProgressBar->setVisible(true);
        m_validationProgressBar->setRange(0, 100);
        m_validationProgressBar->setValue(0);
    }
    
    // Start validation timer
    m_validationTimer->start();
    
    // Perform validation (this will emit validationComplete signal)
    CloudPointMapper::MappingStats stats = m_mapper->validateMapping(0.2f);
    
    // Stop timer
    m_validationTimer->stop();
    if (m_validationProgressBar) {
        m_validationProgressBar->setVisible(false);
    }
    
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
    
    // Validate test inputs - only use available inputs from .ui file
    if (!m_testImageXEdit || !m_testImageYEdit) {
        showError("Test input fields not found");
        return;
    }
    
    bool okX, okY;
    float testX = m_testImageXEdit->text().toFloat(&okX);
    float testY = m_testImageYEdit->text().toFloat(&okY);
    
    if (!okX || !okY) {
        showError("Invalid test coordinate values");
        return;
    }
    
    // Use 0 for Z since we don't have Z input in current UI
    QVector3D testPoint(testX, testY, 0.0f);
    
    CloudPointMapper::InterpolationMethod method = static_cast<CloudPointMapper::InterpolationMethod>(
        m_interpolationMethodCombo ? m_interpolationMethodCombo->currentIndex() : 0);
    
    CloudPointMapper::MappingResult result = m_mapper->transformImageToReal(testPoint, method);
    
    if (result.isValid) {
        // Update output fields if available
        if (m_testRealXEdit) {
            m_testRealXEdit->setText(QString::number(result.transformedPoint.x(), 'f', 2));
        }
        if (m_testRealYEdit) {
            m_testRealYEdit->setText(QString::number(result.transformedPoint.y(), 'f', 2));
        }
        
        // Update confidence and error displays using the local variables we found
        if (m_testConfidenceEdit) {
            m_testConfidenceEdit->setText(QString::number(result.confidence, 'f', 3));
            QString confidenceColor = result.confidence > 0.7 ? "green" : (result.confidence > 0.4 ? "orange" : "red");
            m_testConfidenceEdit->setStyleSheet(QString("color: %1; font-weight: bold;").arg(confidenceColor));
        }
        
        if (m_testErrorEdit) {
            m_testErrorEdit->setText(QString::number(result.estimatedError, 'f', 2) + " mm");
            QString errorColor = result.estimatedError < 2.0 ? "green" : (result.estimatedError < 5.0 ? "orange" : "red");
            m_testErrorEdit->setStyleSheet(QString("color: %1; font-weight: bold;").arg(errorColor));
        }
        
        qDebug() << "Test point transformed successfully - X:" << result.transformedPoint.x() << "Y:" << result.transformedPoint.y();
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
    
    QString variableName;
    if (m_variableNameEdit) {
        variableName = m_variableNameEdit->text().trimmed();
        if (variableName.isEmpty()) {
            variableName = getDefaultVariableName();
            m_variableNameEdit->setText(variableName);
        }
    } else {
        bool ok = false;
        variableName = QInputDialog::getText(
            m_parent,
            "Export Cloud Mapping",
            "Variable name:",
            QLineEdit::Normal,
            getDefaultVariableName(),
            &ok).trimmed();
        if (!ok) {
            return;
        }
        if (variableName.isEmpty()) {
            variableName = getDefaultVariableName();
        }
    }
    
    if (m_mapper->exportToVariableManager(variableName)) {
        showSuccess(QString("Exported mapping to variable: %1").arg(variableName));
    } else {
        showError("Failed to export mapping to VariableManager");
    }
}

void CloudPointToolController::importFromVariableManager()
{
    QString variableName;
    if (m_variableNameEdit) {
        variableName = m_variableNameEdit->text().trimmed();
        if (variableName.isEmpty()) {
            variableName = getDefaultVariableName();
            m_variableNameEdit->setText(variableName);
        }
    } else {
        bool ok = false;
        variableName = QInputDialog::getText(
            m_parent,
            "Import Cloud Mapping",
            "Variable name:",
            QLineEdit::Normal,
            getDefaultVariableName(),
            &ok).trimmed();
        if (!ok) {
            return;
        }
        if (variableName.isEmpty()) {
            variableName = getDefaultVariableName();
        }
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
    if (!m_mapper) {
        return;
    }
    
    CloudPointMapper::MappingStats stats = m_mapper->getMappingStats();
    
    if (m_pointCountLabel) {
        m_pointCountLabel->setText(QString::number(stats.totalPoints));
    }
    if (m_avgErrorLabel) {
        m_avgErrorLabel->setText(QString::number(stats.averageError, 'f', 2));
    }
    if (m_maxErrorLabel) {
        m_maxErrorLabel->setText(QString::number(stats.maxError, 'f', 2));
    }
    if (m_coverageLabel) {
        m_coverageLabel->setText(QString::number(stats.coverage, 'f', 1) + QLatin1String("%"));
    }
}

void CloudPointToolController::updateButtonStates()
{
    // Check if objects are still valid before updating
    if (!m_mapper || !m_calibrationTable) {
        return;
    }
    
    bool hasPoints = m_mapper->getPointCount() > 0;
    bool hasSelection = m_calibrationTable->currentRow() >= 0;
    bool hasEnoughPoints = m_mapper->getPointCount() >= 3;
    
    if (m_removePointButton) m_removePointButton->setEnabled(hasSelection);
    if (m_updatePointButton) m_updatePointButton->setEnabled(hasSelection);
    if (m_clearAllButton) m_clearAllButton->setEnabled(hasPoints);
    if (m_buildGridButton) m_buildGridButton->setEnabled(hasEnoughPoints);
    if (m_validateButton) m_validateButton->setEnabled(m_mapper->getPointCount() >= 5);
    if (m_transformTestButton) m_transformTestButton->setEnabled(hasEnoughPoints);
    if (m_saveButton) m_saveButton->setEnabled(hasPoints);
    if (m_exportButton) m_exportButton->setEnabled(hasPoints);
    if (m_importButton) m_importButton->setEnabled(true);
    if (m_visualizeButton) m_visualizeButton->setEnabled(hasEnoughPoints);
    if (m_statsButton) m_statsButton->setEnabled(hasPoints);
}

void CloudPointToolController::clearInputs()
{
    // m_imageXEdit->clear(); // These are now input dialogs
    // m_imageYEdit->clear();
    // m_imageZEdit->clear();
    // m_realXEdit->clear();
    // m_realYEdit->clear();
    // m_realZEdit->clear();
    // m_confidenceSpinBox->setValue(1.0);
    // m_labelEdit->clear();
}

bool CloudPointToolController::validateAllInputs()
{
    // These are now input dialogs, so no direct validation here
    return true;
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
    // Only show critical errors as popups, log others to debug console
    if (error.contains("failed", Qt::CaseInsensitive) || 
        error.contains("cannot", Qt::CaseInsensitive) ||
        error.contains("invalid", Qt::CaseInsensitive)) {
        showError(error);
    } else {
        // Non-critical errors like "No mapping data found" - just log to debug
        qDebug() << "CloudPointMapper:" << error;
    }
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
        
        // setFormattedValue(m_imageXEdit, point.imageCoord.x()); // These are now input dialogs
        // setFormattedValue(m_imageYEdit, point.imageCoord.y());
        // setFormattedValue(m_imageZEdit, point.imageCoord.z());
        // setFormattedValue(m_realXEdit, point.realCoord.x());
        // setFormattedValue(m_realYEdit, point.realCoord.y());
        // setFormattedValue(m_realZEdit, point.realCoord.z());
        // m_confidenceSpinBox->setValue(point.confidence);
        // m_labelEdit->setText(point.label);
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

void CloudPointToolController::onGridResolutionChanged(int resolution)
{
    m_mapper->setGridResolution(static_cast<float>(resolution));
}

void CloudPointToolController::onAutoRebuildToggled(bool enabled)
{
    if (enabled && m_mapper->getPointCount() >= 3) {
        buildMappingGrid();
    }
}

void CloudPointToolController::onTestInputChanged()
{
    // Auto-transform when test inputs change (optional feature)
    // You can disable this if you prefer manual transform only
    
    if (!m_testImageXEdit || !m_testImageYEdit) return;
    
    QString xText = m_testImageXEdit->text();
    QString yText = m_testImageYEdit->text();
    
    // Only auto-transform if both fields have valid numbers
    bool okX, okY;
    xText.toFloat(&okX);
    yText.toFloat(&okY);
    
    if (okX && okY && !xText.isEmpty() && !yText.isEmpty() && m_mapper->getPointCount() >= 3) {
        // Optional: Auto-transform on input change
        // Uncomment the next line if you want this behavior
        // transformTestPoint();
    }
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
        // m_imageXEdit->setText(parts[0]); // These are now input dialogs
        // m_imageYEdit->setText(parts[1]);
        // m_imageZEdit->setText(parts[2]);
        // m_realXEdit->setText(parts[3]);
        // m_realYEdit->setText(parts[4]);
        // m_realZEdit->setText(parts[5]);
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
        
        // Show robot position in message box since we don't have input fields
        QString message = QString("Current Robot Position:\nX: %1\nY: %2\nZ: %3")
                         .arg(robotPara.X, 0, 'f', 2)
                         .arg(robotPara.Y, 0, 'f', 2)
                         .arg(robotPara.Z, 0, 'f', 2);
        
        QMessageBox::information(m_parent, "Robot Position", message);
    } else {
        showError("No robot position available");
    }
}

void CloudPointToolController::getCurrentImagePosition()
{
    if (!m_parent) return;
    
    // Get current image position from ImageViewer
    QPointF imagePos = m_parent->ui->gvImageViewer->GetPoint1();
    
    // Show image position in message box since we don't have input fields
    QString message = QString("Current Image Position:\nX: %1\nY: %2\nZ: 0.0")
                     .arg(imagePos.x(), 0, 'f', 2)
                     .arg(imagePos.y(), 0, 'f', 2);
    
    QMessageBox::information(m_parent, "Image Position", message);
}

void CloudPointToolController::autoCollectPoints()
{
    // showInfo("Auto-collect functionality not yet implemented");
    qDebug() << "Auto-collect functionality not yet implemented";
}

void CloudPointToolController::generateGridVisualization()
{
    // showInfo("Grid visualization functionality not yet implemented");
    qDebug() << "Grid visualization functionality not yet implemented";
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
