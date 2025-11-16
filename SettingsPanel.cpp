#include "SettingsPanel.h"
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>

SettingsPanel::SettingsPanel(QTabWidget* tabWidget, QObject* parent)
    : QObject(parent)
    , m_settingsManager(&SettingsManager::instance())
    , m_tabWidget(tabWidget)
{
    initializePanel();
    connectSettingsSignals();
    loadSettingsToUI();
}

SettingsPanel::~SettingsPanel()
{
    // Don't save UI settings in destructor as widgets may already be destroyed
    // Settings should be saved when user clicks Save or when closing the settings dialog
}

void SettingsPanel::initializePanel()
{
    // Create all settings tabs
    createGeneralSettingsTab();
    createDeviceSettingsTab();
    createCameraSettingsTab();
    createEditorSettingsTab();
    createAdvancedSettingsTab();
    createAuthoritySettingsTab();
}

void SettingsPanel::createGeneralSettingsTab()
{
    m_generalTab = m_tabWidget->findChild<QWidget*>("tabGeneral");
    if (!m_generalTab) return;
    
    QScrollArea* scrollArea = m_generalTab->findChild<QScrollArea*>("saGeneral");
    if (!scrollArea) return;
    
    QWidget* contentWidget = scrollArea->widget();
    QVBoxLayout* contentLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!contentLayout) return;
    
    // Language Settings Group
    QWidget* languageGroup = createSettingsGroup("Language & Appearance", contentWidget);
    QFormLayout* languageLayout = new QFormLayout(languageGroup);
    
    m_cbLanguage = new QComboBox();
    m_cbLanguage->addItems({"English", "Vietnamese", "Chinese", "Japanese"});
    addSettingsRow(languageLayout, "Language:", m_cbLanguage, "Select the application language");
    
    m_cbTheme = new QComboBox();
    m_cbTheme->addItems({"Dark", "Light", "Auto"});
    addSettingsRow(languageLayout, "Theme:", m_cbTheme, "Select the application theme");
    
    contentLayout->addWidget(languageGroup);
    
    // Startup Settings Group
    QWidget* startupGroup = createSettingsGroup("Startup", contentWidget);
    QFormLayout* startupLayout = new QFormLayout(startupGroup);
    
    m_chkStartupTip = new QCheckBox();
    addSettingsRow(startupLayout, "Show startup tips:", m_chkStartupTip, "Show helpful tips when starting the application");
    
    m_chkCheckUpdates = new QCheckBox();
    addSettingsRow(startupLayout, "Check for updates:", m_chkCheckUpdates, "Automatically check for software updates");
    
    contentLayout->addWidget(startupGroup);
    
    // Auto-save Settings Group
    QWidget* autosaveGroup = createSettingsGroup("Auto-save", contentWidget);
    QFormLayout* autosaveLayout = new QFormLayout(autosaveGroup);
    
    m_chkAutoSaveProject = new QCheckBox();
    addSettingsRow(autosaveLayout, "Enable auto-save:", m_chkAutoSaveProject, "Automatically save project changes");
    
    m_spAutoSaveInterval = new QSpinBox();
    m_spAutoSaveInterval->setRange(1000, 60000);
    m_spAutoSaveInterval->setSuffix(" ms");
    m_spAutoSaveInterval->setSingleStep(1000);
    addSettingsRow(autosaveLayout, "Auto-save interval:", m_spAutoSaveInterval, "Time interval between auto-saves");
    
    contentLayout->addWidget(autosaveGroup);
    
    // Python Settings Group
    QWidget* pythonGroup = createSettingsGroup("Python Environment", contentWidget);
    QFormLayout* pythonLayout = new QFormLayout(pythonGroup);
    
    QHBoxLayout* pythonPathLayout = new QHBoxLayout();
    m_lePythonPath = new QLineEdit();
    m_pbSelectPythonPath = new QPushButton("Browse...");
    pythonPathLayout->addWidget(m_lePythonPath, 1);
    pythonPathLayout->addWidget(m_pbSelectPythonPath);
    
    QWidget* pythonPathWidget = new QWidget();
    pythonPathWidget->setLayout(pythonPathLayout);
    addSettingsRow(pythonLayout, "Python path:", pythonPathWidget, "Path to Python executable for scripts");
    
    contentLayout->addWidget(pythonGroup);
    
    // File Management Group
    QWidget* fileGroup = createSettingsGroup("File Management", contentWidget);
    QFormLayout* fileLayout = new QFormLayout(fileGroup);
    
    m_spMaxRecentFiles = new QSpinBox();
    m_spMaxRecentFiles->setRange(0, 50);
    addSettingsRow(fileLayout, "Max recent files:", m_spMaxRecentFiles, "Maximum number of recent files to remember");
    
    contentLayout->addWidget(fileGroup);
    
    // Add spacer
    contentLayout->addStretch();
}

void SettingsPanel::createDeviceSettingsTab()
{
    m_deviceTab = m_tabWidget->findChild<QWidget*>("tabDevice");
    if (!m_deviceTab) return;
    
    QScrollArea* scrollArea = m_deviceTab->findChild<QScrollArea*>("saDevice");
    if (!scrollArea) return;
    
    QWidget* contentWidget = scrollArea->widget();
    QVBoxLayout* contentLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!contentLayout) return;
    
    // Default Connection Settings Group
    QWidget* connectionGroup = createSettingsGroup("Default Connection Settings", contentWidget);
    QFormLayout* connectionLayout = new QFormLayout(connectionGroup);
    
    m_leDefaultComPort = new QLineEdit();
    m_leDefaultComPort->setPlaceholderText("e.g., COM1, /dev/ttyUSB0");
    addSettingsRow(connectionLayout, "Default COM port:", m_leDefaultComPort, "Default serial port for device connections");
    
    m_spDefaultBaudrate = new QSpinBox();
    m_spDefaultBaudrate->setRange(9600, 921600);
    m_spDefaultBaudrate->setValue(115200);
    QList<int> baudrates = {9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
    connect(m_spDefaultBaudrate, QOverload<int>::of(&QSpinBox::valueChanged), [this, baudrates](int value) {
        // Snap to nearest standard baudrate
        int nearest = baudrates[0];
        int minDiff = qAbs(value - nearest);
        for (int rate : baudrates) {
            int diff = qAbs(value - rate);
            if (diff < minDiff) {
                minDiff = diff;
                nearest = rate;
            }
        }
        if (value != nearest) {
            m_spDefaultBaudrate->setValue(nearest);
        }
    });
    addSettingsRow(connectionLayout, "Default baudrate:", m_spDefaultBaudrate, "Default serial communication speed");
    
    contentLayout->addWidget(connectionGroup);
    
    // Timeout Settings Group
    QWidget* timeoutGroup = createSettingsGroup("Timeout Settings", contentWidget);
    QFormLayout* timeoutLayout = new QFormLayout(timeoutGroup);
    
    m_spConnectionTimeout = new QSpinBox();
    m_spConnectionTimeout->setRange(1000, 30000);
    m_spConnectionTimeout->setSuffix(" ms");
    m_spConnectionTimeout->setSingleStep(1000);
    addSettingsRow(timeoutLayout, "Connection timeout:", m_spConnectionTimeout, "Maximum time to wait for device connection");
    
    m_spReadTimeout = new QSpinBox();
    m_spReadTimeout->setRange(100, 10000);
    m_spReadTimeout->setSuffix(" ms");
    m_spReadTimeout->setSingleStep(100);
    addSettingsRow(timeoutLayout, "Read timeout:", m_spReadTimeout, "Maximum time to wait for device response");
    
    contentLayout->addWidget(timeoutGroup);
    
    // Reliability Settings Group
    QWidget* reliabilityGroup = createSettingsGroup("Reliability", contentWidget);
    QFormLayout* reliabilityLayout = new QFormLayout(reliabilityGroup);
    
    m_chkAutoReconnect = new QCheckBox();
    addSettingsRow(reliabilityLayout, "Auto-reconnect:", m_chkAutoReconnect, "Automatically reconnect if connection is lost");
    
    m_spMaxRetries = new QSpinBox();
    m_spMaxRetries->setRange(1, 10);
    addSettingsRow(reliabilityLayout, "Max retries:", m_spMaxRetries, "Maximum number of connection retry attempts");
    
    m_chkEnableDeviceLogging = new QCheckBox();
    addSettingsRow(reliabilityLayout, "Enable device logging:", m_chkEnableDeviceLogging, "Log all device communication for debugging");
    
    contentLayout->addWidget(reliabilityGroup);
    
    // Add spacer
    contentLayout->addStretch();
}

void SettingsPanel::createCameraSettingsTab()
{
    m_cameraTab = m_tabWidget->findChild<QWidget*>("tabCamera");
    if (!m_cameraTab) return;
    
    QScrollArea* scrollArea = m_cameraTab->findChild<QScrollArea*>("saCamera");
    if (!scrollArea) return;
    
    QWidget* contentWidget = scrollArea->widget();
    QVBoxLayout* contentLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!contentLayout) return;
    
    // Default Settings Group
    QWidget* defaultGroup = createSettingsGroup("Default Camera Settings", contentWidget);
    QFormLayout* defaultLayout = new QFormLayout(defaultGroup);
    
    m_cbDefaultImageSource = new QComboBox();
    m_cbDefaultImageSource->addItems({"Webcam", "Industrial Camera", "IP Camera", "File Source"});
    addSettingsRow(defaultLayout, "Default image source:", m_cbDefaultImageSource, "Default camera/image source to use");
    
    m_spDefaultWidth = new QSpinBox();
    m_spDefaultWidth->setRange(320, 4096);
    m_spDefaultWidth->setSingleStep(160);
    addSettingsRow(defaultLayout, "Default width:", m_spDefaultWidth, "Default image capture width in pixels");
    
    m_spDefaultHeight = new QSpinBox();
    m_spDefaultHeight->setRange(240, 3072);
    m_spDefaultHeight->setSingleStep(120);
    addSettingsRow(defaultLayout, "Default height:", m_spDefaultHeight, "Default image capture height in pixels");
    
    contentLayout->addWidget(defaultGroup);
    
    // Capture Settings Group
    QWidget* captureGroup = createSettingsGroup("Capture Settings", contentWidget);
    QFormLayout* captureLayout = new QFormLayout(captureGroup);
    
    m_spCaptureInterval = new QSpinBox();
    m_spCaptureInterval->setRange(10, 5000);
    m_spCaptureInterval->setSuffix(" ms");
    addSettingsRow(captureLayout, "Capture interval:", m_spCaptureInterval, "Time interval between image captures");
    
    m_chkEnableContinuousCapture = new QCheckBox();
    addSettingsRow(captureLayout, "Continuous capture:", m_chkEnableContinuousCapture, "Enable continuous image capture mode");
    
    contentLayout->addWidget(captureGroup);
    
    // Processing Settings Group
    QWidget* processingGroup = createSettingsGroup("Image Processing", contentWidget);
    QFormLayout* processingLayout = new QFormLayout(processingGroup);
    
    m_cbDefaultAlgorithm = new QComboBox();
    m_cbDefaultAlgorithm->addItems({"Find Blobs", "Edge Detection", "Template Matching", "Deep Learning"});
    addSettingsRow(processingLayout, "Default algorithm:", m_cbDefaultAlgorithm, "Default image processing algorithm");
    
    m_chkEnableImageProcessing = new QCheckBox();
    addSettingsRow(processingLayout, "Enable processing:", m_chkEnableImageProcessing, "Enable real-time image processing");
    
    // Image Quality Slider
    QHBoxLayout* qualityLayout = new QHBoxLayout();
    m_slImageQuality = new QSlider(Qt::Horizontal);
    m_slImageQuality->setRange(1, 100);
    m_lbImageQuality = new QLabel("85%");
    qualityLayout->addWidget(m_slImageQuality, 1);
    qualityLayout->addWidget(m_lbImageQuality);
    
    QWidget* qualityWidget = new QWidget();
    qualityWidget->setLayout(qualityLayout);
    addSettingsRow(processingLayout, "Image quality:", qualityWidget, "JPEG compression quality for saved images");
    
    connect(m_slImageQuality, &QSlider::valueChanged, [this](int value) {
        m_lbImageQuality->setText(QString("%1%").arg(value));
    });
    
    contentLayout->addWidget(processingGroup);
    
    // Save Settings Group
    QWidget* saveGroup = createSettingsGroup("Save Settings", contentWidget);
    QFormLayout* saveLayout = new QFormLayout(saveGroup);
    
    QHBoxLayout* savePathLayout = new QHBoxLayout();
    m_leSaveImagePath = new QLineEdit();
    m_pbSelectImagePath = new QPushButton("Browse...");
    savePathLayout->addWidget(m_leSaveImagePath, 1);
    savePathLayout->addWidget(m_pbSelectImagePath);
    
    QWidget* savePathWidget = new QWidget();
    savePathWidget->setLayout(savePathLayout);
    addSettingsRow(saveLayout, "Save path:", savePathWidget, "Directory to save captured images");
    
    contentLayout->addWidget(saveGroup);
    
    // Add spacer
    contentLayout->addStretch();
}

QWidget* SettingsPanel::createSettingsGroup(const QString& title, QWidget* parent)
{
    QGroupBox* groupBox = new QGroupBox(title, parent);
    groupBox->setStyleSheet(
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #555555;"
        "    border-radius: 5px;"
        "    margin-top: 1ex;"
        "    padding-top: 10px;"
        "    color: rgb(255, 255, 255);"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "}"
    );
    return groupBox;
}

void SettingsPanel::addSettingsRow(QFormLayout* layout, const QString& label, QWidget* control, const QString& tooltip)
{
    QLabel* labelWidget = new QLabel(label);
    labelWidget->setStyleSheet("color: rgb(200, 200, 200); font-weight: normal;");
    
    if (!tooltip.isEmpty()) {
        labelWidget->setToolTip(tooltip);
        control->setToolTip(tooltip);
    }
    
    control->setStyleSheet(
        "QLineEdit, QSpinBox, QComboBox, QCheckBox {"
        "    background-color: rgb(60, 60, 62);"
        "    border: 1px solid rgb(90, 90, 90);"
        "    border-radius: 3px;"
        "    padding: 5px;"
        "    color: rgb(255, 255, 255);"
        "}"
        "QLineEdit:focus, QSpinBox:focus, QComboBox:focus {"
        "    border: 2px solid #007ACC;"
        "}"
        "QPushButton {"
        "    background-color: rgb(70, 70, 72);"
        "    border: 1px solid rgb(90, 90, 90);"
        "    border-radius: 3px;"
        "    padding: 5px 10px;"
        "    color: rgb(255, 255, 255);"
        "}"
        "QPushButton:hover {"
        "    background-color: rgb(80, 80, 82);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgb(60, 60, 62);"
        "}"
    );
    
    layout->addRow(labelWidget, control);
}

void SettingsPanel::createEditorSettingsTab()
{
    m_editorTab = m_tabWidget->findChild<QWidget*>("tabEditor");
    if (!m_editorTab) return;
    
    QScrollArea* scrollArea = m_editorTab->findChild<QScrollArea*>("saEditor");
    if (!scrollArea) return;
    
    QWidget* contentWidget = scrollArea->widget();
    QVBoxLayout* contentLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!contentLayout) return;
    
    // Font Settings Group
    QWidget* fontGroup = createSettingsGroup("Font & Display", contentWidget);
    QFormLayout* fontLayout = new QFormLayout(fontGroup);
    
    QHBoxLayout* fontSelectLayout = new QHBoxLayout();
    m_pbSelectFont = new QPushButton("Select Font...");
    m_lbFontPreview = new QLabel("Font Preview");
    m_lbFontPreview->setStyleSheet("color: rgb(200, 200, 200); padding: 5px; border: 1px solid rgb(90, 90, 90);");
    fontSelectLayout->addWidget(m_pbSelectFont);
    fontSelectLayout->addWidget(m_lbFontPreview, 1);
    
    QWidget* fontWidget = new QWidget();
    fontWidget->setLayout(fontSelectLayout);
    addSettingsRow(fontLayout, "Editor font:", fontWidget, "Select font for code editor");
    
    contentLayout->addWidget(fontGroup);
    
    // Editor Features Group
    QWidget* featuresGroup = createSettingsGroup("Editor Features", contentWidget);
    QFormLayout* featuresLayout = new QFormLayout(featuresGroup);
    
    m_chkSyntaxHighlighting = new QCheckBox();
    addSettingsRow(featuresLayout, "Syntax highlighting:", m_chkSyntaxHighlighting, "Enable syntax highlighting for code");
    
    m_chkLineNumbers = new QCheckBox();
    addSettingsRow(featuresLayout, "Line numbers:", m_chkLineNumbers, "Show line numbers in editor");
    
    m_chkAutoIndent = new QCheckBox();
    addSettingsRow(featuresLayout, "Auto-indent:", m_chkAutoIndent, "Automatically indent new lines");
    
    m_chkWordWrap = new QCheckBox();
    addSettingsRow(featuresLayout, "Word wrap:", m_chkWordWrap, "Wrap long lines in editor");
    
    contentLayout->addWidget(featuresGroup);
    
    // Color Settings Group
    QWidget* colorGroup = createSettingsGroup("Color Scheme", contentWidget);
    QFormLayout* colorLayout = new QFormLayout(colorGroup);
    
    m_pbBackgroundColor = new QPushButton("Background Color");
    m_pbTextColor = new QPushButton("Text Color");
    m_pbKeywordColor = new QPushButton("Keyword Color");
    m_pbCommentColor = new QPushButton("Comment Color");
    
    addSettingsRow(colorLayout, "Background:", m_pbBackgroundColor, "Editor background color");
    addSettingsRow(colorLayout, "Text:", m_pbTextColor, "Default text color");
    addSettingsRow(colorLayout, "Keywords:", m_pbKeywordColor, "Color for language keywords");
    addSettingsRow(colorLayout, "Comments:", m_pbCommentColor, "Color for comments");
    
    contentLayout->addWidget(colorGroup);
    
    // Tab Settings Group
    QWidget* tabGroup = createSettingsGroup("Tab Settings", contentWidget);
    QFormLayout* tabLayout = new QFormLayout(tabGroup);
    
    m_spTabSize = new QSpinBox();
    m_spTabSize->setRange(2, 8);
    addSettingsRow(tabLayout, "Tab size:", m_spTabSize, "Number of spaces per tab");
    
    m_chkSpacesForTabs = new QCheckBox();
    addSettingsRow(tabLayout, "Use spaces for tabs:", m_chkSpacesForTabs, "Use spaces instead of tab characters");
    
    contentLayout->addWidget(tabGroup);
    
    // Add spacer
    contentLayout->addStretch();
}

void SettingsPanel::createAdvancedSettingsTab()
{
    m_advancedTab = m_tabWidget->findChild<QWidget*>("tabAdvanced");
    if (!m_advancedTab) return;
    
    QScrollArea* scrollArea = m_advancedTab->findChild<QScrollArea*>("saAdvanced");
    if (!scrollArea) return;
    
    QWidget* contentWidget = scrollArea->widget();
    QVBoxLayout* contentLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!contentLayout) return;
    
    // Debug Settings Group
    QWidget* debugGroup = createSettingsGroup("Debug & Logging", contentWidget);
    QFormLayout* debugLayout = new QFormLayout(debugGroup);
    
    m_chkDebugMode = new QCheckBox();
    addSettingsRow(debugLayout, "Debug mode:", m_chkDebugMode, "Enable debug mode with extra logging");
    
    m_cbLogLevel = new QComboBox();
    m_cbLogLevel->addItems({"Debug", "Info", "Warning", "Error", "Critical"});
    addSettingsRow(debugLayout, "Log level:", m_cbLogLevel, "Minimum log level to display");
    
    m_spMaxLogFileSize = new QSpinBox();
    m_spMaxLogFileSize->setRange(1, 100);
    m_spMaxLogFileSize->setSuffix(" MB");
    addSettingsRow(debugLayout, "Max log file size:", m_spMaxLogFileSize, "Maximum size of log files");
    
    contentLayout->addWidget(debugGroup);
    
    // Performance Settings Group
    QWidget* performanceGroup = createSettingsGroup("Performance", contentWidget);
    QFormLayout* performanceLayout = new QFormLayout(performanceGroup);
    
    m_chkEnablePerformanceMonitoring = new QCheckBox();
    addSettingsRow(performanceLayout, "Performance monitoring:", m_chkEnablePerformanceMonitoring, "Monitor application performance");
    
    m_spThreadPoolSize = new QSpinBox();
    m_spThreadPoolSize->setRange(1, 16);
    addSettingsRow(performanceLayout, "Thread pool size:", m_spThreadPoolSize, "Number of threads in thread pool");
    
    contentLayout->addWidget(performanceGroup);
    
    // Experimental Settings Group
    QWidget* experimentalGroup = createSettingsGroup("Experimental", contentWidget);
    QFormLayout* experimentalLayout = new QFormLayout(experimentalGroup);
    
    m_chkEnableExperimentalFeatures = new QCheckBox();
    addSettingsRow(experimentalLayout, "Experimental features:", m_chkEnableExperimentalFeatures, "Enable experimental/beta features");
    
    m_chkEnableCrashReporting = new QCheckBox();
    addSettingsRow(experimentalLayout, "Crash reporting:", m_chkEnableCrashReporting, "Send crash reports to developers");
    
    contentLayout->addWidget(experimentalGroup);
    
    // Custom Config Group
    QWidget* configGroup = createSettingsGroup("Custom Configuration", contentWidget);
    QFormLayout* configLayout = new QFormLayout(configGroup);
    
    QHBoxLayout* configPathLayout = new QHBoxLayout();
    m_leCustomConfigPath = new QLineEdit();
    m_pbSelectConfigPath = new QPushButton("Browse...");
    configPathLayout->addWidget(m_leCustomConfigPath, 1);
    configPathLayout->addWidget(m_pbSelectConfigPath);
    
    QWidget* configPathWidget = new QWidget();
    configPathWidget->setLayout(configPathLayout);
    addSettingsRow(configLayout, "Custom config path:", configPathWidget, "Path to custom configuration file");
    
    contentLayout->addWidget(configGroup);
    
    // Add spacer
    contentLayout->addStretch();
}

void SettingsPanel::createAuthoritySettingsTab()
{
    m_authorityTab = m_tabWidget->findChild<QWidget*>("tabAuthority");
    if (!m_authorityTab) return;
    
    QScrollArea* scrollArea = m_authorityTab->findChild<QScrollArea*>("saAuthority");
    if (!scrollArea) return;
    
    QWidget* contentWidget = scrollArea->widget();
    QVBoxLayout* contentLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!contentLayout) return;
    
    // Admin Settings Group
    QWidget* adminGroup = createSettingsGroup("Administrator Settings", contentWidget);
    QFormLayout* adminLayout = new QFormLayout(adminGroup);
    
    m_leAdminPassword = new QLineEdit();
    m_leAdminPassword->setEchoMode(QLineEdit::Password);
    addSettingsRow(adminLayout, "Admin password:", m_leAdminPassword, "Password for administrator access");
    
    contentLayout->addWidget(adminGroup);
    
    // Operator Settings Group
    QWidget* operatorGroup = createSettingsGroup("Operator Permissions", contentWidget);
    QFormLayout* operatorLayout = new QFormLayout(operatorGroup);
    
    m_chkEnableOperatorMode = new QCheckBox();
    addSettingsRow(operatorLayout, "Enable operator mode:", m_chkEnableOperatorMode, "Enable restricted operator mode");
    
    m_leOperatorDisplayWidgets = new QLineEdit();
    addSettingsRow(operatorLayout, "Display widgets:", m_leOperatorDisplayWidgets, "Comma-separated list of allowed widgets");
    
    m_leOperatorDisplayVariables = new QLineEdit();
    addSettingsRow(operatorLayout, "Display variables:", m_leOperatorDisplayVariables, "Comma-separated list of allowed variables");
    
    m_leOperatorRobotGcodePrograms = new QLineEdit();
    addSettingsRow(operatorLayout, "G-code programs:", m_leOperatorRobotGcodePrograms, "Comma-separated list of allowed G-code programs");
    
    m_spSessionTimeout = new QSpinBox();
    m_spSessionTimeout->setRange(1, 180);
    m_spSessionTimeout->setSuffix(" min");
    addSettingsRow(operatorLayout, "Session timeout:", m_spSessionTimeout, "Operator session timeout in minutes");
    
    contentLayout->addWidget(operatorGroup);
    
    // Add spacer
    contentLayout->addStretch();
}

void SettingsPanel::connectSettingsSignals()
{
    // Connect browse buttons
    if (m_pbSelectPythonPath) {
        connect(m_pbSelectPythonPath, &QPushButton::clicked, this, &SettingsPanel::selectPythonPath);
    }
    if (m_pbSelectImagePath) {
        connect(m_pbSelectImagePath, &QPushButton::clicked, this, &SettingsPanel::selectSaveImagePath);
    }
    if (m_pbSelectConfigPath) {
        connect(m_pbSelectConfigPath, &QPushButton::clicked, this, &SettingsPanel::selectCustomConfigPath);
    }
    if (m_pbSelectFont) {
        connect(m_pbSelectFont, &QPushButton::clicked, this, &SettingsPanel::selectFont);
    }
    
    // Connect color buttons
    if (m_pbBackgroundColor) {
        connect(m_pbBackgroundColor, &QPushButton::clicked, [this]() { selectColor(m_backgroundColor, m_pbBackgroundColor); });
    }
    if (m_pbTextColor) {
        connect(m_pbTextColor, &QPushButton::clicked, [this]() { selectColor(m_textColor, m_pbTextColor); });
    }
    if (m_pbKeywordColor) {
        connect(m_pbKeywordColor, &QPushButton::clicked, [this]() { selectColor(m_keywordColor, m_pbKeywordColor); });
    }
    if (m_pbCommentColor) {
        connect(m_pbCommentColor, &QPushButton::clicked, [this]() { selectColor(m_commentColor, m_pbCommentColor); });
    }
    
    // Connect all settings changes to onSettingsChanged
    // General settings
    if (m_cbLanguage) connect(m_cbLanguage, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_cbTheme) connect(m_cbTheme, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_chkStartupTip) connect(m_chkStartupTip, &QCheckBox::toggled, this, &SettingsPanel::onSettingsChanged);
    if (m_chkAutoSaveProject) connect(m_chkAutoSaveProject, &QCheckBox::toggled, this, &SettingsPanel::onSettingsChanged);
    if (m_spAutoSaveInterval) connect(m_spAutoSaveInterval, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_chkCheckUpdates) connect(m_chkCheckUpdates, &QCheckBox::toggled, this, &SettingsPanel::onSettingsChanged);
    if (m_lePythonPath) connect(m_lePythonPath, &QLineEdit::textChanged, this, &SettingsPanel::onSettingsChanged);
    if (m_spMaxRecentFiles) connect(m_spMaxRecentFiles, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    
    // Device settings
    if (m_leDefaultComPort) connect(m_leDefaultComPort, &QLineEdit::textChanged, this, &SettingsPanel::onSettingsChanged);
    if (m_spDefaultBaudrate) connect(m_spDefaultBaudrate, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_spConnectionTimeout) connect(m_spConnectionTimeout, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_spReadTimeout) connect(m_spReadTimeout, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_chkAutoReconnect) connect(m_chkAutoReconnect, &QCheckBox::toggled, this, &SettingsPanel::onSettingsChanged);
    if (m_spMaxRetries) connect(m_spMaxRetries, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_chkEnableDeviceLogging) connect(m_chkEnableDeviceLogging, &QCheckBox::toggled, this, &SettingsPanel::onSettingsChanged);
    
    // Camera settings
    if (m_cbDefaultImageSource) connect(m_cbDefaultImageSource, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_spDefaultWidth) connect(m_spDefaultWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_spDefaultHeight) connect(m_spDefaultHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_spCaptureInterval) connect(m_spCaptureInterval, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_cbDefaultAlgorithm) connect(m_cbDefaultAlgorithm, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsPanel::onSettingsChanged);
    if (m_chkEnableImageProcessing) connect(m_chkEnableImageProcessing, &QCheckBox::toggled, this, &SettingsPanel::onSettingsChanged);
    if (m_slImageQuality) connect(m_slImageQuality, &QSlider::valueChanged, this, &SettingsPanel::onSettingsChanged);
    if (m_leSaveImagePath) connect(m_leSaveImagePath, &QLineEdit::textChanged, this, &SettingsPanel::onSettingsChanged);
    if (m_chkEnableContinuousCapture) connect(m_chkEnableContinuousCapture, &QCheckBox::toggled, this, &SettingsPanel::onSettingsChanged);
}

void SettingsPanel::loadSettingsToUI()
{
    if (!m_settingsManager) return;
    
    // Load General Settings
    auto generalSettings = m_settingsManager->getGeneralSettings();
    if (m_cbLanguage) m_cbLanguage->setCurrentText(generalSettings.language);
    if (m_cbTheme) m_cbTheme->setCurrentText(generalSettings.theme);
    if (m_chkStartupTip) m_chkStartupTip->setChecked(generalSettings.startupTip);
    if (m_chkAutoSaveProject) m_chkAutoSaveProject->setChecked(generalSettings.autoSaveProject);
    if (m_spAutoSaveInterval) m_spAutoSaveInterval->setValue(generalSettings.autoSaveInterval);
    if (m_chkCheckUpdates) m_chkCheckUpdates->setChecked(generalSettings.checkUpdates);
    if (m_lePythonPath) m_lePythonPath->setText(generalSettings.pythonPath);
    if (m_spMaxRecentFiles) m_spMaxRecentFiles->setValue(generalSettings.maxRecentFiles);
    
    // Load Device Settings
    auto deviceSettings = m_settingsManager->getDeviceSettings();
    if (m_leDefaultComPort) m_leDefaultComPort->setText(deviceSettings.defaultComPort);
    if (m_spDefaultBaudrate) m_spDefaultBaudrate->setValue(deviceSettings.defaultBaudrate);
    if (m_spConnectionTimeout) m_spConnectionTimeout->setValue(deviceSettings.connectionTimeout);
    if (m_spReadTimeout) m_spReadTimeout->setValue(deviceSettings.readTimeout);
    if (m_chkAutoReconnect) m_chkAutoReconnect->setChecked(deviceSettings.autoReconnect);
    if (m_spMaxRetries) m_spMaxRetries->setValue(deviceSettings.maxRetries);
    if (m_chkEnableDeviceLogging) m_chkEnableDeviceLogging->setChecked(deviceSettings.enableDeviceLogging);
    
    // Load Camera Settings
    auto cameraSettings = m_settingsManager->getCameraSettings();
    if (m_cbDefaultImageSource) m_cbDefaultImageSource->setCurrentText(cameraSettings.defaultImageSource);
    if (m_spDefaultWidth) m_spDefaultWidth->setValue(cameraSettings.defaultWidth);
    if (m_spDefaultHeight) m_spDefaultHeight->setValue(cameraSettings.defaultHeight);
    if (m_spCaptureInterval) m_spCaptureInterval->setValue(cameraSettings.captureInterval);
    if (m_cbDefaultAlgorithm) m_cbDefaultAlgorithm->setCurrentText(cameraSettings.defaultAlgorithm);
    if (m_chkEnableImageProcessing) m_chkEnableImageProcessing->setChecked(cameraSettings.enableImageProcessing);
    if (m_slImageQuality) m_slImageQuality->setValue(cameraSettings.imageQuality);
    if (m_leSaveImagePath) m_leSaveImagePath->setText(cameraSettings.saveImagePath);
    if (m_chkEnableContinuousCapture) m_chkEnableContinuousCapture->setChecked(cameraSettings.enableContinuousCapture);
    
    // Load Editor Settings
    auto editorSettings = m_settingsManager->getEditorSettings();
    if (m_lbFontPreview) {
        m_selectedFont = editorSettings.font;
        m_lbFontPreview->setFont(m_selectedFont);
        m_lbFontPreview->setText(QString("%1, %2pt").arg(m_selectedFont.family()).arg(m_selectedFont.pointSize()));
    }
    if (m_chkSyntaxHighlighting) m_chkSyntaxHighlighting->setChecked(editorSettings.syntaxHighlighting);
    if (m_chkLineNumbers) m_chkLineNumbers->setChecked(editorSettings.lineNumbers);
    if (m_chkAutoIndent) m_chkAutoIndent->setChecked(editorSettings.autoIndent);
    if (m_chkWordWrap) m_chkWordWrap->setChecked(editorSettings.wordWrap);
    if (m_spTabSize) m_spTabSize->setValue(editorSettings.tabSize);
    if (m_chkSpacesForTabs) m_chkSpacesForTabs->setChecked(editorSettings.spacesForTabs);
    
    // Load colors
    m_backgroundColor = editorSettings.backgroundColor;
    m_textColor = editorSettings.textColor;
    m_keywordColor = editorSettings.keywordColor;
    m_commentColor = editorSettings.commentColor;
    
    if (m_pbBackgroundColor) updateColorButton(m_pbBackgroundColor, m_backgroundColor);
    if (m_pbTextColor) updateColorButton(m_pbTextColor, m_textColor);
    if (m_pbKeywordColor) updateColorButton(m_pbKeywordColor, m_keywordColor);
    if (m_pbCommentColor) updateColorButton(m_pbCommentColor, m_commentColor);
    
    // Load Advanced Settings
    auto advancedSettings = m_settingsManager->getAdvancedSettings();
    if (m_chkDebugMode) m_chkDebugMode->setChecked(advancedSettings.debugMode);
    if (m_cbLogLevel) {
        QStringList logLevels = {"Error", "Warning", "Info", "Debug"};
        if (advancedSettings.logLevel < logLevels.size()) {
            m_cbLogLevel->setCurrentText(logLevels[advancedSettings.logLevel]);
        }
    }
    if (m_chkEnablePerformanceMonitoring) m_chkEnablePerformanceMonitoring->setChecked(advancedSettings.enablePerformanceMonitoring);
    if (m_spMaxLogFileSize) m_spMaxLogFileSize->setValue(advancedSettings.maxLogFileSize);
    if (m_chkEnableCrashReporting) m_chkEnableCrashReporting->setChecked(advancedSettings.enableCrashReporting);
    if (m_leCustomConfigPath) m_leCustomConfigPath->setText(advancedSettings.customConfigPath);
    if (m_chkEnableExperimentalFeatures) m_chkEnableExperimentalFeatures->setChecked(advancedSettings.enableExperimentalFeatures);
    if (m_spThreadPoolSize) m_spThreadPoolSize->setValue(advancedSettings.threadPoolSize);
    
    // Load Authority Settings
    auto authoritySettings = m_settingsManager->getAuthoritySettings();
    if (m_leAdminPassword) m_leAdminPassword->setText(authoritySettings.adminPassword);
    if (m_leOperatorDisplayWidgets) m_leOperatorDisplayWidgets->setText(authoritySettings.operatorDisplayWidgets.join(", "));
    if (m_leOperatorDisplayVariables) m_leOperatorDisplayVariables->setText(authoritySettings.operatorDisplayVariables.join(", "));
    if (m_leOperatorRobotGcodePrograms) m_leOperatorRobotGcodePrograms->setText(authoritySettings.operatorRobotGcodePrograms.join(", "));
    if (m_chkEnableOperatorMode) m_chkEnableOperatorMode->setChecked(authoritySettings.enableOperatorMode);
    if (m_spSessionTimeout) m_spSessionTimeout->setValue(authoritySettings.sessionTimeout);
}

void SettingsPanel::saveUIToSettings()
{
    if (!m_settingsManager) return;
    
    try {
        // Save General Settings
        auto generalSettings = m_settingsManager->getGeneralSettings();
        if (m_cbLanguage) generalSettings.language = m_cbLanguage->currentText();
        if (m_cbTheme) generalSettings.theme = m_cbTheme->currentText();
        if (m_chkStartupTip) generalSettings.startupTip = m_chkStartupTip->isChecked();
        if (m_chkAutoSaveProject) generalSettings.autoSaveProject = m_chkAutoSaveProject->isChecked();
        if (m_spAutoSaveInterval) generalSettings.autoSaveInterval = m_spAutoSaveInterval->value();
        if (m_chkCheckUpdates) generalSettings.checkUpdates = m_chkCheckUpdates->isChecked();
        if (m_lePythonPath) generalSettings.pythonPath = m_lePythonPath->text();
        if (m_spMaxRecentFiles) generalSettings.maxRecentFiles = m_spMaxRecentFiles->value();
    m_settingsManager->setGeneralSettings(generalSettings);
    
        // Save Device Settings
        auto deviceSettings = m_settingsManager->getDeviceSettings();
        if (m_leDefaultComPort) deviceSettings.defaultComPort = m_leDefaultComPort->text();
        if (m_spDefaultBaudrate) deviceSettings.defaultBaudrate = m_spDefaultBaudrate->value();
        if (m_spConnectionTimeout) deviceSettings.connectionTimeout = m_spConnectionTimeout->value();
        if (m_spReadTimeout) deviceSettings.readTimeout = m_spReadTimeout->value();
        if (m_chkAutoReconnect) deviceSettings.autoReconnect = m_chkAutoReconnect->isChecked();
        if (m_spMaxRetries) deviceSettings.maxRetries = m_spMaxRetries->value();
        if (m_chkEnableDeviceLogging) deviceSettings.enableDeviceLogging = m_chkEnableDeviceLogging->isChecked();
        m_settingsManager->setDeviceSettings(deviceSettings);
        
        // Save Camera Settings
        auto cameraSettings = m_settingsManager->getCameraSettings();
        if (m_cbDefaultImageSource) cameraSettings.defaultImageSource = m_cbDefaultImageSource->currentText();
        if (m_spDefaultWidth) cameraSettings.defaultWidth = m_spDefaultWidth->value();
        if (m_spDefaultHeight) cameraSettings.defaultHeight = m_spDefaultHeight->value();
        if (m_spCaptureInterval) cameraSettings.captureInterval = m_spCaptureInterval->value();
        if (m_cbDefaultAlgorithm) cameraSettings.defaultAlgorithm = m_cbDefaultAlgorithm->currentText();
        if (m_chkEnableImageProcessing) cameraSettings.enableImageProcessing = m_chkEnableImageProcessing->isChecked();
        if (m_slImageQuality) cameraSettings.imageQuality = m_slImageQuality->value();
        if (m_leSaveImagePath) cameraSettings.saveImagePath = m_leSaveImagePath->text();
        if (m_chkEnableContinuousCapture) cameraSettings.enableContinuousCapture = m_chkEnableContinuousCapture->isChecked();
        m_settingsManager->setCameraSettings(cameraSettings);
    
        // Save Editor Settings
        auto editorSettings = m_settingsManager->getEditorSettings();
        editorSettings.font = m_selectedFont;
        if (m_chkSyntaxHighlighting) editorSettings.syntaxHighlighting = m_chkSyntaxHighlighting->isChecked();
        if (m_chkLineNumbers) editorSettings.lineNumbers = m_chkLineNumbers->isChecked();
        if (m_chkAutoIndent) editorSettings.autoIndent = m_chkAutoIndent->isChecked();
        if (m_chkWordWrap) editorSettings.wordWrap = m_chkWordWrap->isChecked();
        if (m_spTabSize) editorSettings.tabSize = m_spTabSize->value();
        if (m_chkSpacesForTabs) editorSettings.spacesForTabs = m_chkSpacesForTabs->isChecked();
        
        editorSettings.backgroundColor = m_backgroundColor;
        editorSettings.textColor = m_textColor;
        editorSettings.keywordColor = m_keywordColor;
        editorSettings.commentColor = m_commentColor;
        m_settingsManager->setEditorSettings(editorSettings);
        
        // Save Advanced Settings
        auto advancedSettings = m_settingsManager->getAdvancedSettings();
        if (m_chkDebugMode) advancedSettings.debugMode = m_chkDebugMode->isChecked();
        if (m_cbLogLevel) {
            QStringList logLevels = {"Error", "Warning", "Info", "Debug"};
            advancedSettings.logLevel = logLevels.indexOf(m_cbLogLevel->currentText());
            if (advancedSettings.logLevel == -1) advancedSettings.logLevel = 2; // Default to Info
        }
        if (m_chkEnablePerformanceMonitoring) advancedSettings.enablePerformanceMonitoring = m_chkEnablePerformanceMonitoring->isChecked();
        if (m_spMaxLogFileSize) advancedSettings.maxLogFileSize = m_spMaxLogFileSize->value();
        if (m_chkEnableCrashReporting) advancedSettings.enableCrashReporting = m_chkEnableCrashReporting->isChecked();
        if (m_leCustomConfigPath) advancedSettings.customConfigPath = m_leCustomConfigPath->text();
        if (m_chkEnableExperimentalFeatures) advancedSettings.enableExperimentalFeatures = m_chkEnableExperimentalFeatures->isChecked();
        if (m_spThreadPoolSize) advancedSettings.threadPoolSize = m_spThreadPoolSize->value();
        m_settingsManager->setAdvancedSettings(advancedSettings);
        
        // Save Authority Settings
        auto authoritySettings = m_settingsManager->getAuthoritySettings();
        if (m_leAdminPassword) authoritySettings.adminPassword = m_leAdminPassword->text();
        if (m_leOperatorDisplayWidgets) authoritySettings.operatorDisplayWidgets = m_leOperatorDisplayWidgets->text().split(", ", Qt::SkipEmptyParts);
        if (m_leOperatorDisplayVariables) authoritySettings.operatorDisplayVariables = m_leOperatorDisplayVariables->text().split(", ", Qt::SkipEmptyParts);
        if (m_leOperatorRobotGcodePrograms) authoritySettings.operatorRobotGcodePrograms = m_leOperatorRobotGcodePrograms->text().split(", ", Qt::SkipEmptyParts);
        if (m_chkEnableOperatorMode) authoritySettings.enableOperatorMode = m_chkEnableOperatorMode->isChecked();
        if (m_spSessionTimeout) authoritySettings.sessionTimeout = m_spSessionTimeout->value();
        m_settingsManager->setAuthoritySettings(authoritySettings);
        
        // Save all settings to file
        m_settingsManager->saveSettings();
        
    } catch (...) {
        // Silently ignore any errors when saving settings during destruction
        // This prevents crashes when widgets have been destroyed
    }
}

void SettingsPanel::autoSaveSettings()
{
    // This method can be called safely even during destruction
    // It only saves if all widgets are still valid
    if (m_settingsManager) {
        try {
            saveUIToSettings();
        } catch (...) {
            // Ignore errors during auto-save (widgets may be destroyed)
        }
    }
}

void SettingsPanel::onSaveSettings()
{
    saveUIToSettings();
    emit settingsUpdated();
}

void SettingsPanel::onResetSettings()
{
    int ret = QMessageBox::question(nullptr, "Reset Settings", 
        "Are you sure you want to reset all settings to defaults?\nThis action cannot be undone.",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        resetToDefaults();
        loadSettingsToUI();
        emit settingsUpdated();
    }
}

void SettingsPanel::resetToDefaults()
{
    if (m_settingsManager) {
        m_settingsManager->resetToDefaults();
    }
}

void SettingsPanel::onBackupSettings()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, 
        "Backup Settings", 
        QString("settings_backup_%1.json").arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss")),
        "JSON Files (*.json)");
    
    if (!fileName.isEmpty()) {
        try {
            m_settingsManager->backupSettings(fileName);
            QMessageBox::information(nullptr, "Backup Complete", 
                QString("Settings backed up to:\n%1").arg(fileName));
        } catch (...) {
            QMessageBox::warning(nullptr, "Backup Failed", 
                "Failed to backup settings. Please check file permissions.");
        }
    }
}

void SettingsPanel::onRestoreSettings()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, 
        "Restore Settings", 
        "", 
        "JSON Files (*.json)");
    
    if (!fileName.isEmpty()) {
        int ret = QMessageBox::question(nullptr, "Restore Settings", 
            "Are you sure you want to restore settings from backup?\nThis will overwrite current settings.",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        
        if (ret == QMessageBox::Yes) {
            try {
                m_settingsManager->restoreSettings(fileName);
                loadSettingsToUI();
                emit settingsUpdated();
                QMessageBox::information(nullptr, "Restore Complete", 
                    "Settings restored successfully.");
            } catch (...) {
                QMessageBox::warning(nullptr, "Restore Failed", 
                    "Failed to restore settings. Please check the backup file.");
            }
        }
    }
}

void SettingsPanel::onSettingsChanged()
{
    emit settingsUpdated();
}

void SettingsPanel::selectFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, m_selectedFont, nullptr, "Select Editor Font");
    if (ok) {
        m_selectedFont = font;
        if (m_lbFontPreview) {
            m_lbFontPreview->setFont(font);
            m_lbFontPreview->setText(QString("%1, %2pt").arg(font.family()).arg(font.pointSize()));
        }
        onSettingsChanged();
    }
}

void SettingsPanel::selectColor(QColor& color, QPushButton* button)
{
    QColor newColor = QColorDialog::getColor(color, nullptr, "Select Color");
    if (newColor.isValid()) {
        color = newColor;
        updateColorButton(button, color);
        onSettingsChanged();
    }
}

void SettingsPanel::updateColorButton(QPushButton* button, const QColor& color)
{
    if (button) {
        button->setStyleSheet(QString(
            "QPushButton { "
            "    background-color: %1; "
            "    border: 1px solid rgb(90, 90, 90); "
            "    border-radius: 3px; "
            "    padding: 5px 10px; "
            "    color: %2; "
            "}"
            "QPushButton:hover { "
            "    border: 2px solid #007ACC; "
            "}"
        ).arg(color.name(), 
             (color.lightness() > 128) ? "black" : "white"));
    }
}

void SettingsPanel::selectPythonPath()
{
    QString filter;
#ifdef Q_OS_WIN
    filter = tr("Executables (*.exe *.bat *.cmd);;All Files (*)");
#else
    filter = tr("Executables (*.app *.command *.sh *.py python*);;All Files (*)");
#endif

    QString fileName = QFileDialog::getOpenFileName(nullptr,
        tr("Select Python Executable"),
        m_lePythonPath ? m_lePythonPath->text() : "",
        filter);
    
    if (!fileName.isEmpty() && m_lePythonPath) {
        m_lePythonPath->setText(fileName);
        onSettingsChanged();
    }
}

void SettingsPanel::selectSaveImagePath()
{
    QString dirName = QFileDialog::getExistingDirectory(nullptr, 
        "Select Image Save Directory", 
        m_leSaveImagePath ? m_leSaveImagePath->text() : "");
    
    if (!dirName.isEmpty() && m_leSaveImagePath) {
        m_leSaveImagePath->setText(dirName);
        onSettingsChanged();
    }
}

void SettingsPanel::selectCustomConfigPath()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, 
        "Select Custom Config File", 
        m_leCustomConfigPath ? m_leCustomConfigPath->text() : "", 
        "Config Files (*.ini *.cfg *.json);;All Files (*)");
    
    if (!fileName.isEmpty() && m_leCustomConfigPath) {
        m_leCustomConfigPath->setText(fileName);
        onSettingsChanged();
    }
}
