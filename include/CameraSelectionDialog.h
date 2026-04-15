#ifndef CAMERASELECTIONDIALOG_H
#define CAMERASELECTIONDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>
#include <QGraphicsDropShadowEffect>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QCameraDevice>
#include <QMediaDevices>
using CameraInfoType = QCameraDevice;
#else
#include <QCameraInfo>
using CameraInfoType = QCameraInfo;
#endif

class CameraSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraSelectionDialog(QWidget* parent = nullptr);
    ~CameraSelectionDialog();

    static int getCameraID(QWidget* parent, bool* ok = nullptr);
    
    void loadAvailableCameras();
    int getSelectedCameraID() const;

private slots:
    void onOkClicked();
    void onCancelClicked();
    void onCameraItemClicked(QListWidgetItem* item);
    void onCameraItemDoubleClicked(QListWidgetItem* item);

private:
    void setupUI();
    void applyDarkTheme();
    void createTitleBar();
    void createContent();
    void createButtons();
    
    // UI Components
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;
    QListWidget* m_cameraList;
    QPushButton* m_okButton;
    QPushButton* m_cancelButton;
    QLabel* m_statusLabel;
    
    // State
    int m_selectedCameraID;
    QList<CameraInfoType> m_availableCameras;
};

#endif // CAMERASELECTIONDIALOG_H 
