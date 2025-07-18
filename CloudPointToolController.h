#ifndef CLOUDPOINTTOOLCONTROLLER_H
#define CLOUDPOINTTOOLCONTROLLER_H

#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QProgressBar>
#include <QTextEdit>
#include <QTimer>
#include <QClipboard>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CloudPointMapper.h"
#include "InputValidator.h"

// Forward declarations
class RobotWindow;

/**
 * @brief Controller class for Cloud Point Tool UI operations
 * 
 * This class manages the advanced cloud point mapping interface,
 * providing multi-point calibration and sophisticated interpolation
 * methods for high-precision robot positioning.
 */
class CloudPointToolController : public QObject
{
    Q_OBJECT

public:
    explicit CloudPointToolController(RobotWindow* parent = nullptr);
    ~CloudPointToolController();

    /**
     * @brief Sets the parent RobotWindow instance
     * @param parent Pointer to RobotWindow
     */
    void setParent(RobotWindow* parent);

    /**
     * @brief Initialize the cloud point mapping UI
     * @param parentWidget Parent widget to add controls to
     */
    void initializeUI(QWidget* parentWidget);

    /**
     * @brief Get the cloud point mapper instance
     * @return CloudPointMapper pointer
     */
    CloudPointMapper* getMapper() const;

    /**
     * @brief Update the calibration points table
     */
    void updateCalibrationTable();

    /**
     * @brief Update the mapping statistics display
     */
    void updateStatsDisplay();

    /**
     * @brief Enable/disable UI based on mapping state
     * @param enabled UI state
     */
    void setUIEnabled(bool enabled);

public slots:
    /**
     * @brief Add a new calibration point
     */
    void addCalibrationPoint();

    /**
     * @brief Remove selected calibration point
     */
    void removeCalibrationPoint();

    /**
     * @brief Update selected calibration point
     */
    void updateCalibrationPoint();

    /**
     * @brief Clear all calibration points
     */
    void clearAllPoints();

    /**
     * @brief Build the mapping grid
     */
    void buildMappingGrid();

    /**
     * @brief Validate mapping accuracy
     */
    void validateMapping();

    /**
     * @brief Transform test point using cloud mapping
     */
    void transformTestPoint();

    /**
     * @brief Save mapping to file
     */
    void saveMapping();

    /**
     * @brief Load mapping from file
     */
    void loadMapping();

    /**
     * @brief Export mapping to VariableManager
     */
    void exportToVariableManager();

    /**
     * @brief Import mapping from VariableManager
     */
    void importFromVariableManager();

    /**
     * @brief Handle interpolation method change
     * @param method New interpolation method
     */
    void onInterpolationMethodChanged(int method);

    /**
     * @brief Handle grid resolution change
     * @param resolution New grid resolution
     */
    void onGridResolutionChanged(double resolution);

    /**
     * @brief Handle auto-rebuild toggle
     * @param enabled Auto-rebuild flag
     */
    void onAutoRebuildToggled(bool enabled);

    /**
     * @brief Handle table selection change
     */
    void onTableSelectionChanged();

    /**
     * @brief Handle double-click on table item
     * @param item Clicked table item
     */
    void onTableItemDoubleClicked(QTableWidgetItem* item);

    /**
     * @brief Paste coordinates from clipboard
     */
    void pasteCoordinates();

    /**
     * @brief Get current robot position
     */
    void getCurrentRobotPosition();

    /**
     * @brief Get current image position from viewer
     */
    void getCurrentImagePosition();

    /**
     * @brief Auto-collect calibration points
     */
    void autoCollectPoints();

    /**
     * @brief Generate grid visualization
     */
    void generateGridVisualization();

    /**
     * @brief Show mapping statistics dialog
     */
    void showMappingStats();

    /**
     * @brief Handle mapping update signal
     */
    void onMappingUpdated();

    /**
     * @brief Handle validation complete signal
     * @param stats Validation statistics
     */
    void onValidationComplete(const CloudPointMapper::MappingStats& stats);

    /**
     * @brief Handle error signal
     * @param error Error message
     */
    void onErrorOccurred(const QString& error);

private slots:
    /**
     * @brief Update validation progress
     */
    void updateValidationProgress();

private:
    RobotWindow* m_parent;                          ///< Parent window
    CloudPointMapper* m_mapper;                     ///< Cloud point mapper instance
    QClipboard* m_clipboard;                        ///< System clipboard
    QTimer* m_validationTimer;                      ///< Validation progress timer
    
    // UI Components
    QGroupBox* m_mainGroupBox;                      ///< Main group box
    QTableWidget* m_calibrationTable;               ///< Calibration points table
    QComboBox* m_interpolationMethodCombo;          ///< Interpolation method selection
    QDoubleSpinBox* m_gridResolutionSpinBox;        ///< Grid resolution input
    QCheckBox* m_autoRebuildCheckBox;               ///< Auto-rebuild checkbox
    QProgressBar* m_validationProgressBar;          ///< Validation progress bar
    QTextEdit* m_statsTextEdit;                     ///< Statistics display
    
    // Input controls
    QLineEdit* m_imageXEdit;                        ///< Image X coordinate input
    QLineEdit* m_imageYEdit;                        ///< Image Y coordinate input
    QLineEdit* m_imageZEdit;                        ///< Image Z coordinate input
    QLineEdit* m_realXEdit;                         ///< Real X coordinate input
    QLineEdit* m_realYEdit;                         ///< Real Y coordinate input
    QLineEdit* m_realZEdit;                         ///< Real Z coordinate input
    QDoubleSpinBox* m_confidenceSpinBox;            ///< Confidence input
    QLineEdit* m_labelEdit;                         ///< Label input
    
    // Test point controls
    QLineEdit* m_testImageXEdit;                    ///< Test image X coordinate
    QLineEdit* m_testImageYEdit;                    ///< Test image Y coordinate
    QLineEdit* m_testImageZEdit;                    ///< Test image Z coordinate
    QLineEdit* m_testRealXEdit;                     ///< Test real X coordinate (result)
    QLineEdit* m_testRealYEdit;                     ///< Test real Y coordinate (result)
    QLineEdit* m_testRealZEdit;                     ///< Test real Z coordinate (result)
    QLabel* m_testConfidenceLabel;                  ///< Test confidence display
    QLabel* m_testErrorLabel;                       ///< Test error display
    
    // Buttons
    QPushButton* m_addPointButton;                  ///< Add point button
    QPushButton* m_removePointButton;               ///< Remove point button
    QPushButton* m_updatePointButton;               ///< Update point button
    QPushButton* m_clearAllButton;                  ///< Clear all button
    QPushButton* m_buildGridButton;                 ///< Build grid button
    QPushButton* m_validateButton;                  ///< Validate button
    QPushButton* m_transformTestButton;             ///< Transform test button
    QPushButton* m_saveButton;                      ///< Save button
    QPushButton* m_loadButton;                      ///< Load button
    QPushButton* m_exportButton;                    ///< Export button
    QPushButton* m_importButton;                    ///< Import button
    QPushButton* m_pasteButton;                     ///< Paste button
    QPushButton* m_getRobotPosButton;               ///< Get robot position button
    QPushButton* m_getImagePosButton;               ///< Get image position button
    QPushButton* m_autoCollectButton;               ///< Auto-collect button
    QPushButton* m_visualizeButton;                 ///< Visualize button
    QPushButton* m_statsButton;                     ///< Statistics button
    
    // Variable manager controls
    QLineEdit* m_variableNameEdit;                  ///< Variable name input
    
    // Auto-collect settings
    QSpinBox* m_autoCollectCountSpinBox;            ///< Auto-collect count
    QSpinBox* m_autoCollectIntervalSpinBox;         ///< Auto-collect interval
    QCheckBox* m_autoCollectRandomCheckBox;         ///< Auto-collect random positions
    
    // Private methods
    void createUI();
    QGroupBox* createCalibrationPointsGroup();
    QGroupBox* createMappingSettingsGroup();
    QGroupBox* createTestPointGroup();
    QGroupBox* createControlButtonsGroup();
    QGroupBox* createStatsGroup();
    QGroupBox* createVariableManagerGroup();
    QGroupBox* createAutoCollectGroup();
    
    void connectSignals();
    void setupCalibrationTable();
    void setupInterpolationMethodCombo();
    void updateButtonStates();
    void updateMappingInfo();
    void clearInputs();
    void loadInputsFromTableSelection();
    void validateInputs();
    void showError(const QString& message);
    void showSuccess(const QString& message);
    void showInfo(const QString& message);
    
    // Validation helpers
    bool validateCoordinateInput(QLineEdit* edit, const QString& fieldName);
    bool validateAllInputs();
    void setFormattedValue(QLineEdit* edit, float value);
    float getFloatValue(QLineEdit* edit);
    
    // File I/O helpers
    QString getDefaultMappingPath();
    QString getDefaultVariableName();
    
    // Auto-collect helpers
    void generateRandomTestPoints(int count);
    void collectPointsInGrid(int gridSize);
    void collectPointsAroundPerimeter(int count);
    
    // Constants
    static const int COLUMN_COUNT = 8;
    static const int COL_INDEX = 0;
    static const int COL_IMAGE_X = 1;
    static const int COL_IMAGE_Y = 2;
    static const int COL_IMAGE_Z = 3;
    static const int COL_REAL_X = 4;
    static const int COL_REAL_Y = 5;
    static const int COL_REAL_Z = 6;
    static const int COL_CONFIDENCE = 7;
    static const int COL_LABEL = 8;
    static const int COL_ERROR = 9;
    static const int COL_TIMESTAMP = 10;
    static const int ACTUAL_COLUMN_COUNT = 11;
};

#endif // CLOUDPOINTTOOLCONTROLLER_H 