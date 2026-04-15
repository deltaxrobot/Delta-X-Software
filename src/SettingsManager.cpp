#include "SettingsManager.h"
#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

SettingsManager* SettingsManager::s_instance = nullptr;

SettingsManager& SettingsManager::instance()
{
    if (!s_instance) {
        s_instance = new SettingsManager();
    }
    return *s_instance;
}

QString SettingsManager::defaultPythonPath()
{
    QStringList candidates;
#ifdef Q_OS_WIN
    candidates << QStringLiteral("python.exe")
               << QStringLiteral("python3.exe")
               << QStringLiteral("py.exe");
#else
    candidates << QStringLiteral("python3")
               << QStringLiteral("/usr/bin/python3")
               << QStringLiteral("python");
#endif

    for (const QString& candidate : candidates) {
        const QString resolved = QStandardPaths::findExecutable(candidate);
        if (!resolved.isEmpty()) {
            return resolved;
        }
    }

#ifdef Q_OS_WIN
    return QStringLiteral("python.exe");
#else
    return QStringLiteral("/usr/bin/python3");
#endif
}

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent)
    , m_settings(nullptr)
{
    m_settingsPath = getSettingsFilePath();
    m_settings = new QSettings(m_settingsPath, QSettings::IniFormat, this);
    
    setDefaults();
    loadSettings();
}

SettingsManager::~SettingsManager()
{
    saveSettings();
}

QString SettingsManager::getSettingsFilePath() const
{
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath);
    return appDataPath + "/settings.ini";
}

QString SettingsManager::getBackupFilePath() const
{
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return appDataPath + "/settings_backup.ini";
}

void SettingsManager::setDefaults()
{
    // General settings defaults
    m_generalSettings = GeneralSettings();
    m_deviceSettings = DeviceSettings();
    m_cameraSettings = CameraSettings();
    m_editorSettings = EditorSettings();
    m_advancedSettings = AdvancedSettings();
    m_authoritySettings = AuthoritySettings();
}

void SettingsManager::loadSettings()
{
    try {
        loadCategory("General");
        loadCategory("Device");
        loadCategory("Camera");
        loadCategory("Editor");
        loadCategory("Advanced");
        loadCategory("Authority");
        
        emit settingsLoaded();
    }
    catch (const std::exception& e) {
        emit settingsError(QString("Failed to load settings: %1").arg(e.what()));
    }
}

void SettingsManager::saveSettings()
{
    try {
        saveCategory("General");
        saveCategory("Device");
        saveCategory("Camera");
        saveCategory("Editor");
        saveCategory("Advanced");
        saveCategory("Authority");
        
        m_settings->sync();
        emit settingsSaved();
    }
    catch (const std::exception& e) {
        emit settingsError(QString("Failed to save settings: %1").arg(e.what()));
    }
}

void SettingsManager::loadCategory(const QString& category)
{
    m_settings->beginGroup(category);
    
    if (category == "General") {
        m_generalSettings.language = m_settings->value("language", m_generalSettings.language).toString();
        m_generalSettings.theme = m_settings->value("theme", m_generalSettings.theme).toString();
        m_generalSettings.startupTip = m_settings->value("startupTip", m_generalSettings.startupTip).toBool();
        m_generalSettings.autoSaveProject = m_settings->value("autoSaveProject", m_generalSettings.autoSaveProject).toBool();
        m_generalSettings.autoSaveInterval = m_settings->value("autoSaveInterval", m_generalSettings.autoSaveInterval).toInt();
        m_generalSettings.checkUpdates = m_settings->value("checkUpdates", m_generalSettings.checkUpdates).toBool();
        m_generalSettings.pythonPath = m_settings->value("pythonPath", m_generalSettings.pythonPath).toString();
        m_generalSettings.maxRecentFiles = m_settings->value("maxRecentFiles", m_generalSettings.maxRecentFiles).toInt();
    }
    else if (category == "Device") {
        m_deviceSettings.defaultComPort = m_settings->value("defaultComPort", m_deviceSettings.defaultComPort).toString();
        m_deviceSettings.defaultBaudrate = m_settings->value("defaultBaudrate", m_deviceSettings.defaultBaudrate).toInt();
        m_deviceSettings.connectionTimeout = m_settings->value("connectionTimeout", m_deviceSettings.connectionTimeout).toInt();
        m_deviceSettings.readTimeout = m_settings->value("readTimeout", m_deviceSettings.readTimeout).toInt();
        m_deviceSettings.autoReconnect = m_settings->value("autoReconnect", m_deviceSettings.autoReconnect).toBool();
        m_deviceSettings.maxRetries = m_settings->value("maxRetries", m_deviceSettings.maxRetries).toInt();
        m_deviceSettings.enableDeviceLogging = m_settings->value("enableDeviceLogging", m_deviceSettings.enableDeviceLogging).toBool();
    }
    else if (category == "Camera") {
        m_cameraSettings.defaultImageSource = m_settings->value("defaultImageSource", m_cameraSettings.defaultImageSource).toString();
        m_cameraSettings.defaultWidth = m_settings->value("defaultWidth", m_cameraSettings.defaultWidth).toInt();
        m_cameraSettings.defaultHeight = m_settings->value("defaultHeight", m_cameraSettings.defaultHeight).toInt();
        m_cameraSettings.captureInterval = m_settings->value("captureInterval", m_cameraSettings.captureInterval).toInt();
        m_cameraSettings.defaultAlgorithm = m_settings->value("defaultAlgorithm", m_cameraSettings.defaultAlgorithm).toString();
        m_cameraSettings.enableImageProcessing = m_settings->value("enableImageProcessing", m_cameraSettings.enableImageProcessing).toBool();
        m_cameraSettings.imageQuality = m_settings->value("imageQuality", m_cameraSettings.imageQuality).toInt();
        m_cameraSettings.saveImagePath = m_settings->value("saveImagePath", m_cameraSettings.saveImagePath).toString();
        m_cameraSettings.enableContinuousCapture = m_settings->value("enableContinuousCapture", m_cameraSettings.enableContinuousCapture).toBool();
    }
    else if (category == "Editor") {
        m_editorSettings.font = m_settings->value("font", m_editorSettings.font).value<QFont>();
        m_editorSettings.syntaxHighlighting = m_settings->value("syntaxHighlighting", m_editorSettings.syntaxHighlighting).toBool();
        m_editorSettings.lineNumbers = m_settings->value("lineNumbers", m_editorSettings.lineNumbers).toBool();
        m_editorSettings.autoIndent = m_settings->value("autoIndent", m_editorSettings.autoIndent).toBool();
        m_editorSettings.wordWrap = m_settings->value("wordWrap", m_editorSettings.wordWrap).toBool();
        m_editorSettings.backgroundColor = m_settings->value("backgroundColor", m_editorSettings.backgroundColor).value<QColor>();
        m_editorSettings.textColor = m_settings->value("textColor", m_editorSettings.textColor).value<QColor>();
        m_editorSettings.keywordColor = m_settings->value("keywordColor", m_editorSettings.keywordColor).value<QColor>();
        m_editorSettings.commentColor = m_settings->value("commentColor", m_editorSettings.commentColor).value<QColor>();
        m_editorSettings.tabSize = m_settings->value("tabSize", m_editorSettings.tabSize).toInt();
        m_editorSettings.spacesForTabs = m_settings->value("spacesForTabs", m_editorSettings.spacesForTabs).toBool();
    }
    else if (category == "Advanced") {
        m_advancedSettings.debugMode = m_settings->value("debugMode", m_advancedSettings.debugMode).toBool();
        m_advancedSettings.logLevel = m_settings->value("logLevel", m_advancedSettings.logLevel).toInt();
        m_advancedSettings.enablePerformanceMonitoring = m_settings->value("enablePerformanceMonitoring", m_advancedSettings.enablePerformanceMonitoring).toBool();
        m_advancedSettings.maxLogFileSize = m_settings->value("maxLogFileSize", m_advancedSettings.maxLogFileSize).toInt();
        m_advancedSettings.enableCrashReporting = m_settings->value("enableCrashReporting", m_advancedSettings.enableCrashReporting).toBool();
        m_advancedSettings.customConfigPath = m_settings->value("customConfigPath", m_advancedSettings.customConfigPath).toString();
        m_advancedSettings.enableExperimentalFeatures = m_settings->value("enableExperimentalFeatures", m_advancedSettings.enableExperimentalFeatures).toBool();
        m_advancedSettings.threadPoolSize = m_settings->value("threadPoolSize", m_advancedSettings.threadPoolSize).toInt();
    }
    else if (category == "Authority") {
        m_authoritySettings.adminPassword = m_settings->value("adminPassword", m_authoritySettings.adminPassword).toString();
        m_authoritySettings.operatorDisplayWidgets = m_settings->value("operatorDisplayWidgets", m_authoritySettings.operatorDisplayWidgets).toStringList();
        m_authoritySettings.operatorDisplayVariables = m_settings->value("operatorDisplayVariables", m_authoritySettings.operatorDisplayVariables).toStringList();
        m_authoritySettings.operatorRobotGcodePrograms = m_settings->value("operatorRobotGcodePrograms", m_authoritySettings.operatorRobotGcodePrograms).toStringList();
        m_authoritySettings.enableOperatorMode = m_settings->value("enableOperatorMode", m_authoritySettings.enableOperatorMode).toBool();
        m_authoritySettings.sessionTimeout = m_settings->value("sessionTimeout", m_authoritySettings.sessionTimeout).toInt();
    }
    
    m_settings->endGroup();
}

void SettingsManager::saveCategory(const QString& category)
{
    m_settings->beginGroup(category);
    
    if (category == "General") {
        m_settings->setValue("language", m_generalSettings.language);
        m_settings->setValue("theme", m_generalSettings.theme);
        m_settings->setValue("startupTip", m_generalSettings.startupTip);
        m_settings->setValue("autoSaveProject", m_generalSettings.autoSaveProject);
        m_settings->setValue("autoSaveInterval", m_generalSettings.autoSaveInterval);
        m_settings->setValue("checkUpdates", m_generalSettings.checkUpdates);
        m_settings->setValue("pythonPath", m_generalSettings.pythonPath);
        m_settings->setValue("maxRecentFiles", m_generalSettings.maxRecentFiles);
    }
    else if (category == "Device") {
        m_settings->setValue("defaultComPort", m_deviceSettings.defaultComPort);
        m_settings->setValue("defaultBaudrate", m_deviceSettings.defaultBaudrate);
        m_settings->setValue("connectionTimeout", m_deviceSettings.connectionTimeout);
        m_settings->setValue("readTimeout", m_deviceSettings.readTimeout);
        m_settings->setValue("autoReconnect", m_deviceSettings.autoReconnect);
        m_settings->setValue("maxRetries", m_deviceSettings.maxRetries);
        m_settings->setValue("enableDeviceLogging", m_deviceSettings.enableDeviceLogging);
    }
    else if (category == "Camera") {
        m_settings->setValue("defaultImageSource", m_cameraSettings.defaultImageSource);
        m_settings->setValue("defaultWidth", m_cameraSettings.defaultWidth);
        m_settings->setValue("defaultHeight", m_cameraSettings.defaultHeight);
        m_settings->setValue("captureInterval", m_cameraSettings.captureInterval);
        m_settings->setValue("defaultAlgorithm", m_cameraSettings.defaultAlgorithm);
        m_settings->setValue("enableImageProcessing", m_cameraSettings.enableImageProcessing);
        m_settings->setValue("imageQuality", m_cameraSettings.imageQuality);
        m_settings->setValue("saveImagePath", m_cameraSettings.saveImagePath);
        m_settings->setValue("enableContinuousCapture", m_cameraSettings.enableContinuousCapture);
    }
    else if (category == "Editor") {
        m_settings->setValue("font", m_editorSettings.font);
        m_settings->setValue("syntaxHighlighting", m_editorSettings.syntaxHighlighting);
        m_settings->setValue("lineNumbers", m_editorSettings.lineNumbers);
        m_settings->setValue("autoIndent", m_editorSettings.autoIndent);
        m_settings->setValue("wordWrap", m_editorSettings.wordWrap);
        m_settings->setValue("backgroundColor", m_editorSettings.backgroundColor);
        m_settings->setValue("textColor", m_editorSettings.textColor);
        m_settings->setValue("keywordColor", m_editorSettings.keywordColor);
        m_settings->setValue("commentColor", m_editorSettings.commentColor);
        m_settings->setValue("tabSize", m_editorSettings.tabSize);
        m_settings->setValue("spacesForTabs", m_editorSettings.spacesForTabs);
    }
    else if (category == "Advanced") {
        m_settings->setValue("debugMode", m_advancedSettings.debugMode);
        m_settings->setValue("logLevel", m_advancedSettings.logLevel);
        m_settings->setValue("enablePerformanceMonitoring", m_advancedSettings.enablePerformanceMonitoring);
        m_settings->setValue("maxLogFileSize", m_advancedSettings.maxLogFileSize);
        m_settings->setValue("enableCrashReporting", m_advancedSettings.enableCrashReporting);
        m_settings->setValue("customConfigPath", m_advancedSettings.customConfigPath);
        m_settings->setValue("enableExperimentalFeatures", m_advancedSettings.enableExperimentalFeatures);
        m_settings->setValue("threadPoolSize", m_advancedSettings.threadPoolSize);
    }
    else if (category == "Authority") {
        m_settings->setValue("adminPassword", m_authoritySettings.adminPassword);
        m_settings->setValue("operatorDisplayWidgets", m_authoritySettings.operatorDisplayWidgets);
        m_settings->setValue("operatorDisplayVariables", m_authoritySettings.operatorDisplayVariables);
        m_settings->setValue("operatorRobotGcodePrograms", m_authoritySettings.operatorRobotGcodePrograms);
        m_settings->setValue("enableOperatorMode", m_authoritySettings.enableOperatorMode);
        m_settings->setValue("sessionTimeout", m_authoritySettings.sessionTimeout);
    }
    
    m_settings->endGroup();
}

// Getters
SettingsManager::GeneralSettings SettingsManager::getGeneralSettings() const
{
    return m_generalSettings;
}

SettingsManager::DeviceSettings SettingsManager::getDeviceSettings() const
{
    return m_deviceSettings;
}

SettingsManager::CameraSettings SettingsManager::getCameraSettings() const
{
    return m_cameraSettings;
}

SettingsManager::EditorSettings SettingsManager::getEditorSettings() const
{
    return m_editorSettings;
}

SettingsManager::AdvancedSettings SettingsManager::getAdvancedSettings() const
{
    return m_advancedSettings;
}

SettingsManager::AuthoritySettings SettingsManager::getAuthoritySettings() const
{
    return m_authoritySettings;
}

// Setters
void SettingsManager::setGeneralSettings(const GeneralSettings& settings)
{
    m_generalSettings = settings;
    emit settingsChanged("General", "all");
}

void SettingsManager::setDeviceSettings(const DeviceSettings& settings)
{
    m_deviceSettings = settings;
    emit settingsChanged("Device", "all");
}

void SettingsManager::setCameraSettings(const CameraSettings& settings)
{
    m_cameraSettings = settings;
    emit settingsChanged("Camera", "all");
}

void SettingsManager::setEditorSettings(const EditorSettings& settings)
{
    m_editorSettings = settings;
    emit settingsChanged("Editor", "all");
}

void SettingsManager::setAdvancedSettings(const AdvancedSettings& settings)
{
    m_advancedSettings = settings;
    emit settingsChanged("Advanced", "all");
}

void SettingsManager::setAuthoritySettings(const AuthoritySettings& settings)
{
    m_authoritySettings = settings;
    emit settingsChanged("Authority", "all");
}

QVariant SettingsManager::getSetting(const QString& category, const QString& key, const QVariant& defaultValue) const
{
    m_settings->beginGroup(category);
    QVariant value = m_settings->value(key, defaultValue);
    m_settings->endGroup();
    return value;
}

void SettingsManager::setSetting(const QString& category, const QString& key, const QVariant& value)
{
    m_settings->beginGroup(category);
    m_settings->setValue(key, value);
    m_settings->endGroup();
    emit settingsChanged(category, key);
}

void SettingsManager::resetToDefaults()
{
    setDefaults();
    saveSettings();
}

void SettingsManager::backupSettings(const QString& backupPath)
{
    QString targetPath = backupPath.isEmpty() ? getBackupFilePath() : backupPath;
    
    if (QFile::exists(targetPath)) {
        QFile::remove(targetPath);
    }
    
    if (!QFile::copy(m_settingsPath, targetPath)) {
        emit settingsError("Failed to backup settings");
    }
}

void SettingsManager::restoreSettings(const QString& backupPath)
{
    QString sourcePath = backupPath.isEmpty() ? getBackupFilePath() : backupPath;
    
    if (!QFile::exists(sourcePath)) {
        emit settingsError("Backup file not found");
        return;
    }
    
    if (QFile::exists(m_settingsPath)) {
        QFile::remove(m_settingsPath);
    }
    
    if (QFile::copy(sourcePath, m_settingsPath)) {
        loadSettings();
    } else {
        emit settingsError("Failed to restore settings");
    }
}

QStringList SettingsManager::getSettingsCategories() const
{
    return {"General", "Device", "Camera", "Editor", "Advanced", "Authority"};
}

QHash<QString, QVariant> SettingsManager::getCategorySettings(const QString& category) const
{
    QHash<QString, QVariant> categorySettings;
    
    m_settings->beginGroup(category);
    QStringList keys = m_settings->childKeys();
    
    for (const QString& key : keys) {
        categorySettings[key] = m_settings->value(key);
    }
    
    m_settings->endGroup();
    return categorySettings;
}

bool SettingsManager::validateSettings() const
{
    m_errors.clear();
    
    // Validate General settings
    if (m_generalSettings.autoSaveInterval < 1000) {
        m_errors << "Auto-save interval must be at least 1000ms";
    }
    
    if (m_generalSettings.maxRecentFiles < 0 || m_generalSettings.maxRecentFiles > 50) {
        m_errors << "Max recent files must be between 0 and 50";
    }
    
    // Validate Device settings
    if (m_deviceSettings.defaultBaudrate <= 0) {
        m_errors << "Default baudrate must be positive";
    }
    
    if (m_deviceSettings.connectionTimeout < 1000) {
        m_errors << "Connection timeout must be at least 1000ms";
    }
    
    // Validate Camera settings
    if (m_cameraSettings.defaultWidth <= 0 || m_cameraSettings.defaultHeight <= 0) {
        m_errors << "Camera dimensions must be positive";
    }
    
    if (m_cameraSettings.captureInterval < 10) {
        m_errors << "Capture interval must be at least 10ms";
    }
    
    if (m_cameraSettings.imageQuality < 1 || m_cameraSettings.imageQuality > 100) {
        m_errors << "Image quality must be between 1 and 100";
    }
    
    // Validate Editor settings
    if (m_editorSettings.tabSize < 1 || m_editorSettings.tabSize > 16) {
        m_errors << "Tab size must be between 1 and 16";
    }
    
    // Validate Advanced settings
    if (m_advancedSettings.logLevel < 0 || m_advancedSettings.logLevel > 3) {
        m_errors << "Log level must be between 0 and 3";
    }
    
    if (m_advancedSettings.maxLogFileSize < 1 || m_advancedSettings.maxLogFileSize > 1000) {
        m_errors << "Max log file size must be between 1 and 1000 MB";
    }
    
    if (m_advancedSettings.threadPoolSize < 1 || m_advancedSettings.threadPoolSize > 32) {
        m_errors << "Thread pool size must be between 1 and 32";
    }
    
    // Validate Authority settings
    if (m_authoritySettings.adminPassword.length() < 4) {
        m_errors << "Admin password must be at least 4 characters";
    }
    
    if (m_authoritySettings.sessionTimeout < 1 || m_authoritySettings.sessionTimeout > 1440) {
        m_errors << "Session timeout must be between 1 and 1440 minutes";
    }
    
    return m_errors.isEmpty();
}

QStringList SettingsManager::getSettingsErrors() const
{
    return m_errors;
}
