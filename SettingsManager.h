#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QVariant>
#include <QHash>
#include <QStringList>
#include <QFont>
#include <QColor>
#include <QSize>
#include <QPoint>
#include <QDir>
#include <QStandardPaths>

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    // Singleton pattern
    static SettingsManager& instance();
    static QString defaultPythonPath();
    
    // Settings categories
    enum SettingsCategory {
        General,
        Device,
        Camera,
        Editor,
        Advanced,
        Authority
    };
    
    // Settings structure
    struct GeneralSettings {
        QString language = "English";
        QString theme = "Dark";
        bool startupTip = true;
        bool autoSaveProject = true;
        int autoSaveInterval = 5000; // milliseconds
        bool checkUpdates = true;
        QString pythonPath = SettingsManager::defaultPythonPath();
        int maxRecentFiles = 10;
    };
    
    struct DeviceSettings {
        QString defaultComPort = "COM1";
        int defaultBaudrate = 115200;
        int connectionTimeout = 5000;
        int readTimeout = 1000;
        bool autoReconnect = true;
        int maxRetries = 3;
        bool enableDeviceLogging = true;
    };
    
    struct CameraSettings {
        QString defaultImageSource = "Webcam";
        int defaultWidth = 800;
        int defaultHeight = 600;
        int captureInterval = 100;
        QString defaultAlgorithm = "Find Blobs";
        bool enableImageProcessing = true;
        int imageQuality = 85;
        QString saveImagePath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        bool enableContinuousCapture = false;
    };
    
    struct EditorSettings {
        QFont font = QFont("Consolas", 10);
        bool syntaxHighlighting = true;
        bool lineNumbers = true;
        bool autoIndent = true;
        bool wordWrap = false;
        QColor backgroundColor = QColor(30, 30, 32);
        QColor textColor = QColor(255, 255, 255);
        QColor keywordColor = QColor(86, 156, 214);
        QColor commentColor = QColor(106, 153, 85);
        int tabSize = 4;
        bool spacesForTabs = true;
    };
    
    struct AdvancedSettings {
        bool debugMode = false;
        int logLevel = 2; // 0=Error, 1=Warning, 2=Info, 3=Debug
        bool enablePerformanceMonitoring = false;
        int maxLogFileSize = 10; // MB
        bool enableCrashReporting = true;
        QString customConfigPath = "";
        bool enableExperimentalFeatures = false;
        int threadPoolSize = 4;
    };
    
    struct AuthoritySettings {
        QString adminPassword = "1234";
        QStringList operatorDisplayWidgets;
        QStringList operatorDisplayVariables;
        QStringList operatorRobotGcodePrograms;
        bool enableOperatorMode = false;
        int sessionTimeout = 30; // minutes
    };

public:
    // Get settings
    GeneralSettings getGeneralSettings() const;
    DeviceSettings getDeviceSettings() const;
    CameraSettings getCameraSettings() const;
    EditorSettings getEditorSettings() const;
    AdvancedSettings getAdvancedSettings() const;
    AuthoritySettings getAuthoritySettings() const;
    
    // Set settings
    void setGeneralSettings(const GeneralSettings& settings);
    void setDeviceSettings(const DeviceSettings& settings);
    void setCameraSettings(const CameraSettings& settings);
    void setEditorSettings(const EditorSettings& settings);
    void setAdvancedSettings(const AdvancedSettings& settings);
    void setAuthoritySettings(const AuthoritySettings& settings);
    
    // Individual setting access
    QVariant getSetting(const QString& category, const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setSetting(const QString& category, const QString& key, const QVariant& value);
    
    // Settings management
    void loadSettings();
    void saveSettings();
    void resetToDefaults();
    void backupSettings(const QString& backupPath = "");
    void restoreSettings(const QString& backupPath);
    
    // Utility functions
    QStringList getSettingsCategories() const;
    QHash<QString, QVariant> getCategorySettings(const QString& category) const;
    
    // Settings validation
    bool validateSettings() const;
    QStringList getSettingsErrors() const;

signals:
    void settingsChanged(const QString& category, const QString& key);
    void settingsLoaded();
    void settingsSaved();
    void settingsError(const QString& error);

private:
    explicit SettingsManager(QObject* parent = nullptr);
    ~SettingsManager();
    
    // Private methods
    void loadCategory(const QString& category);
    void saveCategory(const QString& category);
    void setDefaults();
    QString getSettingsFilePath() const;
    QString getBackupFilePath() const;
    
    // Settings storage
    QSettings* m_settings;
    QString m_settingsPath;
    
    // Settings cache
    GeneralSettings m_generalSettings;
    DeviceSettings m_deviceSettings;
    CameraSettings m_cameraSettings;
    EditorSettings m_editorSettings;
    AdvancedSettings m_advancedSettings;
    AuthoritySettings m_authoritySettings;
    
    // Error handling
    mutable QStringList m_errors;
    
    // Singleton
    static SettingsManager* s_instance;
};

#endif // SETTINGSMANAGER_H
