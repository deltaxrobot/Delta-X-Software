#include "CameraSelectionDialog.h"
#include <QApplication>
#include <QScreen>

CameraSelectionDialog::CameraSelectionDialog(QWidget* parent)
    : QDialog(parent)
    , m_mainLayout(nullptr)
    , m_titleLabel(nullptr)
    , m_descriptionLabel(nullptr)
    , m_cameraList(nullptr)
    , m_okButton(nullptr)
    , m_cancelButton(nullptr)
    , m_statusLabel(nullptr)
    , m_selectedCameraID(-1)
{
    setupUI();
    applyDarkTheme();
    loadAvailableCameras();
    
    // Set dialog properties
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setModal(true);
    resize(480, 400);
    
    // Center the dialog
    if (parent) {
        move(parent->geometry().center() - rect().center());
    }
}

CameraSelectionDialog::~CameraSelectionDialog()
{
}

int CameraSelectionDialog::getCameraID(QWidget* parent, bool* ok)
{
    CameraSelectionDialog dialog(parent);
    
    int result = dialog.exec();
    if (ok) *ok = (result == QDialog::Accepted);
    
    return (result == QDialog::Accepted) ? dialog.getSelectedCameraID() : -1;
}

void CameraSelectionDialog::loadAvailableCameras()
{
    m_availableCameras = QCameraInfo::availableCameras();
    m_cameraList->clear();
    
    if (m_availableCameras.isEmpty()) {
        m_statusLabel->setText("❌ No cameras found");
        m_statusLabel->setStyleSheet("color: #ff6b6b; font-weight: bold;");
        m_okButton->setEnabled(false);
        return;
    }
    
    QIcon cameraIcon = createCameraIcon();
    
    for (int i = 0; i < m_availableCameras.size(); ++i) {
        const QCameraInfo& camera = m_availableCameras[i];
        
        QListWidgetItem* item = new QListWidgetItem();
        item->setIcon(cameraIcon);
        
        // Create display text for camera info
        QString cameraName = QString("📹 Camera %1").arg(i);
        QString cameraDesc = QString("   %1").arg(camera.description());
        QString displayText = cameraName + "\n" + cameraDesc;
        
        item->setText(displayText);
        item->setData(Qt::UserRole, i); // Store camera ID
        item->setSizeHint(QSize(0, 70));
        
        // Set font for better readability
        QFont itemFont;
        itemFont.setPointSize(10);
        itemFont.setFamily("Segoe UI");
        item->setFont(itemFont);
        
        // Set tooltip with full camera info
        item->setToolTip(QString("Camera ID: %1\nDevice: %2").arg(i).arg(camera.description()));
        
        m_cameraList->addItem(item);
    }
    
    // Select first camera by default
    if (m_cameraList->count() > 0) {
        m_cameraList->setCurrentRow(0);
        m_selectedCameraID = 0;
        m_statusLabel->setText(QString("📹 %1 camera(s) available").arg(m_availableCameras.size()));
        m_statusLabel->setStyleSheet("color: #4caf50; font-weight: bold;");
        m_okButton->setEnabled(true);
    }
}

int CameraSelectionDialog::getSelectedCameraID() const
{
    return m_selectedCameraID;
}

void CameraSelectionDialog::onOkClicked()
{
    if (m_cameraList->currentItem()) {
        m_selectedCameraID = m_cameraList->currentItem()->data(Qt::UserRole).toInt();
        accept();
    }
}

void CameraSelectionDialog::onCancelClicked()
{
    m_selectedCameraID = -1;
    reject();
}

void CameraSelectionDialog::onCameraItemClicked(QListWidgetItem* item)
{
    if (item) {
        m_selectedCameraID = item->data(Qt::UserRole).toInt();
        m_okButton->setEnabled(true);
        
        // Update status with selected camera info
        const QCameraInfo& camera = m_availableCameras[m_selectedCameraID];
        m_statusLabel->setText(QString("✅ Selected: %1").arg(camera.description()));
        m_statusLabel->setStyleSheet("color: #4caf50; font-weight: bold;");
    }
}

void CameraSelectionDialog::onCameraItemDoubleClicked(QListWidgetItem* item)
{
    onCameraItemClicked(item);
    onOkClicked();
}

void CameraSelectionDialog::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    
    createTitleBar();
    createContent();
    createButtons();
    
    setLayout(m_mainLayout);
}

void CameraSelectionDialog::createTitleBar()
{
    // Title bar
    QWidget* titleBar = new QWidget();
    titleBar->setFixedHeight(60);
    titleBar->setObjectName("titleBar");
    
    QHBoxLayout* titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(20, 15, 20, 15);
    
    // Camera icon in title
    QLabel* iconLabel = new QLabel();
    iconLabel->setPixmap(createCameraIcon().pixmap(32, 32));
    titleLayout->addWidget(iconLabel);
    
    QVBoxLayout* titleTextLayout = new QVBoxLayout();
    titleTextLayout->setSpacing(2);
    
    m_titleLabel = new QLabel("Camera Selection");
    m_titleLabel->setObjectName("titleLabel");
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    
    QLabel* subtitleLabel = new QLabel("Choose a camera device for video capture");
    subtitleLabel->setObjectName("subtitleLabel");
    QFont subtitleFont = subtitleLabel->font();
    subtitleFont.setPointSize(10);
    subtitleLabel->setFont(subtitleFont);
    
    titleTextLayout->addWidget(m_titleLabel);
    titleTextLayout->addWidget(subtitleLabel);
    titleLayout->addLayout(titleTextLayout);
    titleLayout->addStretch();
    
    m_mainLayout->addWidget(titleBar);
}

void CameraSelectionDialog::createContent()
{
    // Content area
    QWidget* contentWidget = new QWidget();
    contentWidget->setObjectName("contentWidget");
    
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 20, 20, 15);
    contentLayout->setSpacing(15);
    
    // Description
    m_descriptionLabel = new QLabel("Available camera devices:");
    m_descriptionLabel->setObjectName("descriptionLabel");
    QFont labelFont = m_descriptionLabel->font();
    labelFont.setPointSize(11);
    labelFont.setBold(true);
    m_descriptionLabel->setFont(labelFont);
    contentLayout->addWidget(m_descriptionLabel);
    
    // Camera list
    m_cameraList = new QListWidget();
    m_cameraList->setObjectName("cameraList");
    m_cameraList->setAlternatingRowColors(true);
    m_cameraList->setSelectionMode(QAbstractItemView::SingleSelection);
    m_cameraList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_cameraList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    connect(m_cameraList, &QListWidget::itemClicked, 
            this, &CameraSelectionDialog::onCameraItemClicked);
    connect(m_cameraList, &QListWidget::itemDoubleClicked, 
            this, &CameraSelectionDialog::onCameraItemDoubleClicked);
    
    contentLayout->addWidget(m_cameraList);
    
    // Status label
    m_statusLabel = new QLabel("Scanning for cameras...");
    m_statusLabel->setObjectName("statusLabel");
    QFont statusFont = m_statusLabel->font();
    statusFont.setPointSize(10);
    m_statusLabel->setFont(statusFont);
    contentLayout->addWidget(m_statusLabel);
    
    m_mainLayout->addWidget(contentWidget);
}

void CameraSelectionDialog::createButtons()
{
    // Button area
    QWidget* buttonWidget = new QWidget();
    buttonWidget->setObjectName("buttonWidget");
    buttonWidget->setFixedHeight(70);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(20, 15, 20, 15);
    buttonLayout->setSpacing(10);
    
    buttonLayout->addStretch();
    
    // Cancel button
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setObjectName("cancelButton");
    m_cancelButton->setFixedSize(120, 40);
    connect(m_cancelButton, &QPushButton::clicked, this, &CameraSelectionDialog::onCancelClicked);
    buttonLayout->addWidget(m_cancelButton);
    
    // OK button
    m_okButton = new QPushButton("Connect Camera");
    m_okButton->setObjectName("okButton");
    m_okButton->setFixedSize(150, 40);
    m_okButton->setDefault(true);
    m_okButton->setEnabled(false);
    connect(m_okButton, &QPushButton::clicked, this, &CameraSelectionDialog::onOkClicked);
    buttonLayout->addWidget(m_okButton);
    
    m_mainLayout->addWidget(buttonWidget);
}

QIcon CameraSelectionDialog::createCameraIcon()
{
    // Create a simple camera icon using QPainter
    QPixmap pixmap(48, 48);
    pixmap.fill(Qt::transparent);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Camera body
    painter.setBrush(QColor("#0078d4"));
    painter.setPen(QPen(QColor("#005a9e"), 2));
    painter.drawRoundedRect(8, 16, 32, 20, 4, 4);
    
    // Camera lens
    painter.setBrush(QColor("#333333"));
    painter.setPen(QPen(QColor("#222222"), 1));
    painter.drawEllipse(14, 22, 8, 8);
    
    // Lens center
    painter.setBrush(QColor("#666666"));
    painter.drawEllipse(16, 24, 4, 4);
    
    // Flash
    painter.setBrush(QColor("#ffffff"));
    painter.drawEllipse(30, 18, 4, 4);
    
    return QIcon(pixmap);
}

void CameraSelectionDialog::applyDarkTheme()
{
    setStyleSheet(R"(
        QDialog {
            background-color: #2b2b2b;
            border: 1px solid #404040;
            border-radius: 12px;
        }
        
        QWidget#titleBar {
            background-color: #363636;
            border-top-left-radius: 12px;
            border-top-right-radius: 12px;
            border-bottom: 1px solid #404040;
        }
        
        QLabel#titleLabel {
            color: #ffffff;
            background: transparent;
        }
        
        QLabel#subtitleLabel {
            color: #cccccc;
            background: transparent;
        }
        
        QWidget#contentWidget {
            background-color: #2b2b2b;
        }
        
        QLabel#descriptionLabel {
            color: #ffffff;
            background: transparent;
        }
        
        QLabel#statusLabel {
            color: #999999;
            background: transparent;
            padding: 5px;
            border-radius: 4px;
        }
        
        QListWidget#cameraList {
            background-color: #333333;
            border: 1px solid #555555;
            border-radius: 8px;
            color: #ffffff;
            selection-background-color: #0078d4;
            selection-color: #ffffff;
            alternate-background-color: #383838;
            font-size: 11px;
            padding: 8px;
        }
        
        QListWidget#cameraList::item {
            padding: 12px 15px;
            border-radius: 6px;
            margin: 2px;
            border: 1px solid transparent;
            text-align: left;
            line-height: 1.4;
        }
        
        QListWidget#cameraList::item:hover {
            background-color: #404040;
            border: 1px solid #0078d4;
        }
        
        QListWidget#cameraList::item:selected {
            background-color: #0078d4;
            color: #ffffff;
            border: 1px solid #ffffff;
        }
        
        QWidget#buttonWidget {
            background-color: #363636;
            border-bottom-left-radius: 12px;
            border-bottom-right-radius: 12px;
            border-top: 1px solid #404040;
        }
        
        QPushButton#okButton {
            background-color: #0078d4;
            color: #ffffff;
            border: none;
            border-radius: 8px;
            font-weight: bold;
            font-size: 12px;
        }
        
        QPushButton#okButton:hover {
            background-color: #106ebe;
        }
        
        QPushButton#okButton:pressed {
            background-color: #005a9e;
        }
        
        QPushButton#okButton:disabled {
            background-color: #555555;
            color: #888888;
        }
        
        QPushButton#cancelButton {
            background-color: #404040;
            color: #ffffff;
            border: 1px solid #666666;
            border-radius: 8px;
            font-size: 12px;
        }
        
        QPushButton#cancelButton:hover {
            background-color: #4a4a4a;
            border-color: #777777;
        }
        
        QPushButton#cancelButton:pressed {
            background-color: #353535;
        }
    )");
    
    // Add shadow effect
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(25);
    shadowEffect->setColor(QColor(0, 0, 0, 120));
    shadowEffect->setOffset(0, 8);
    setGraphicsEffect(shadowEffect);
} 