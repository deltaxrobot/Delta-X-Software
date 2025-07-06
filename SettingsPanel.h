#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QGroupBox>
#include <QSlider>
#include <QScrollArea>
#include <QMessageBox>
#include <QApplication>
#include "SettingsManager.h"

class SettingsPanel : public QObject
{
    Q_OBJECT

public:
    explicit SettingsPanel(QTabWidget* tabWidget, QObject* parent = nullptr);
    ~SettingsPanel();

    // Initialize the settings panel
    void initializePanel();
    
    // Update UI from settings
    void loadSettingsToUI();
    
    // Save UI values to settings
    void saveUIToSettings();
    
    // Auto-save settings when needed (thread-safe)
    void autoSaveSettings();
    
    // Reset to defaults
    void resetToDefaults();

public slots:
    void onSaveSettings();
    void onResetSettings();
    void onBackupSettings();
    void onRestoreSettings();
    void onSettingsChanged();

signals:
    void settingsUpdated();
    void settingsError(const QString& error);

private:
    // UI Creation methods
    void createGeneralSettingsTab();
    void createDeviceSettingsTab();
    void createCameraSettingsTab();
    void createEditorSettingsTab();
    void createAdvancedSettingsTab();
    void createAuthoritySettingsTab();
    
    // Helper methods
    QWidget* createSettingsGroup(const QString& title, QWidget* parent);
    QHBoxLayout* createLabeledControl(const QString& label, QWidget* control, QWidget* parent);
    void addSettingsRow(QFormLayout* layout, const QString& label, QWidget* control, const QString& tooltip = "");
    void connectSettingsSignals();
    void validateAndShowErrors();
    
    // Font and color selection
    void selectFont();
    void selectColor(QColor& color, QPushButton* button);
    void updateColorButton(QPushButton* button, const QColor& color);
    
    // File/Path selection
    void selectPythonPath();
    void selectSaveImagePath();
    void selectCustomConfigPath();

private:
    SettingsManager* m_settingsManager;
    QTabWidget* m_tabWidget;
    
    // Tab widgets
    QWidget* m_generalTab;
    QWidget* m_deviceTab;
    QWidget* m_cameraTab;
    QWidget* m_editorTab;
    QWidget* m_advancedTab;
    QWidget* m_authorityTab;
    
    // General Settings Controls
    QComboBox* m_cbLanguage;
    QComboBox* m_cbTheme;
    QCheckBox* m_chkStartupTip;
    QCheckBox* m_chkAutoSaveProject;
    QSpinBox* m_spAutoSaveInterval;
    QCheckBox* m_chkCheckUpdates;
    QLineEdit* m_lePythonPath;
    QPushButton* m_pbSelectPythonPath;
    QSpinBox* m_spMaxRecentFiles;
    
    // Device Settings Controls
    QLineEdit* m_leDefaultComPort;
    QSpinBox* m_spDefaultBaudrate;
    QSpinBox* m_spConnectionTimeout;
    QSpinBox* m_spReadTimeout;
    QCheckBox* m_chkAutoReconnect;
    QSpinBox* m_spMaxRetries;
    QCheckBox* m_chkEnableDeviceLogging;
    
    // Camera Settings Controls
    QComboBox* m_cbDefaultImageSource;
    QSpinBox* m_spDefaultWidth;
    QSpinBox* m_spDefaultHeight;
    QSpinBox* m_spCaptureInterval;
    QComboBox* m_cbDefaultAlgorithm;
    QCheckBox* m_chkEnableImageProcessing;
    QSlider* m_slImageQuality;
    QLabel* m_lbImageQuality;
    QLineEdit* m_leSaveImagePath;
    QPushButton* m_pbSelectImagePath;
    QCheckBox* m_chkEnableContinuousCapture;
    
    // Editor Settings Controls
    QPushButton* m_pbSelectFont;
    QLabel* m_lbFontPreview;
    QFont m_selectedFont;
    QCheckBox* m_chkSyntaxHighlighting;
    QCheckBox* m_chkLineNumbers;
    QCheckBox* m_chkAutoIndent;
    QCheckBox* m_chkWordWrap;
    QPushButton* m_pbBackgroundColor;
    QPushButton* m_pbTextColor;
    QPushButton* m_pbKeywordColor;
    QPushButton* m_pbCommentColor;
    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_keywordColor;
    QColor m_commentColor;
    QSpinBox* m_spTabSize;
    QCheckBox* m_chkSpacesForTabs;
    
    // Advanced Settings Controls
    QCheckBox* m_chkDebugMode;
    QComboBox* m_cbLogLevel;
    QCheckBox* m_chkEnablePerformanceMonitoring;
    QSpinBox* m_spMaxLogFileSize;
    QCheckBox* m_chkEnableCrashReporting;
    QLineEdit* m_leCustomConfigPath;
    QPushButton* m_pbSelectConfigPath;
    QCheckBox* m_chkEnableExperimentalFeatures;
    QSpinBox* m_spThreadPoolSize;
    
    // Authority Settings Controls
    QLineEdit* m_leAdminPassword;
    QLineEdit* m_leOperatorDisplayWidgets;
    QLineEdit* m_leOperatorDisplayVariables;
    QLineEdit* m_leOperatorRobotGcodePrograms;
    QCheckBox* m_chkEnableOperatorMode;
    QSpinBox* m_spSessionTimeout;
};

#endif // SETTINGSPANEL_H 