#include "ModernDialog.h"
#include <QApplication>
#include <QScreen>

ModernDialog::ModernDialog(QWidget* parent)
    : QDialog(parent)
    , m_mainLayout(nullptr)
    , m_titleLabel(nullptr)
    , m_contentLabel(nullptr)
    , m_listWidget(nullptr)
    , m_lineEdit(nullptr)
    , m_okButton(nullptr)
    , m_cancelButton(nullptr)
    , m_isTextInput(false)
    , m_accepted(false)
{
    setupUI();
    applyDarkTheme();
    
    // Set dialog properties
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setModal(true);
    resize(400, 300);
    
    // Center the dialog
    if (parent) {
        move(parent->geometry().center() - rect().center());
    }
}

ModernDialog::~ModernDialog()
{
}

QString ModernDialog::getItem(QWidget* parent, const QString& title, const QString& label, 
                             const QStringList& items, int current, bool* ok)
{
    ModernDialog dialog(parent);
    dialog.setTitle(title);
    dialog.setLabel(label);
    dialog.setItems(items);
    dialog.setCurrentItem(current);
    
    int result = dialog.exec();
    if (ok) *ok = (result == QDialog::Accepted);
    
    return (result == QDialog::Accepted) ? dialog.getSelectedText() : QString();
}

QString ModernDialog::getText(QWidget* parent, const QString& title, const QString& label, 
                             const QString& text, bool* ok)
{
    ModernDialog dialog(parent);
    dialog.setTitle(title);
    dialog.setLabel(label);
    dialog.setText(text);
    dialog.m_isTextInput = true;
    
    // Hide list widget and show line edit
    dialog.m_listWidget->hide();
    dialog.m_lineEdit->show();
    dialog.m_lineEdit->setFocus();
    
    int result = dialog.exec();
    if (ok) *ok = (result == QDialog::Accepted);
    
    return (result == QDialog::Accepted) ? dialog.getInputText() : QString();
}

void ModernDialog::setTitle(const QString& title)
{
    if (m_titleLabel) {
        m_titleLabel->setText(title);
    }
    setWindowTitle(title);
}

void ModernDialog::setLabel(const QString& label)
{
    if (m_contentLabel) {
        m_contentLabel->setText(label);
    }
}

void ModernDialog::setItems(const QStringList& items)
{
    if (m_listWidget) {
        m_listWidget->clear();
        m_listWidget->addItems(items);
        m_listWidget->show();
        m_lineEdit->hide();
        m_isTextInput = false;
    }
}

void ModernDialog::setCurrentItem(int index)
{
    if (m_listWidget && index >= 0 && index < m_listWidget->count()) {
        m_listWidget->setCurrentRow(index);
        m_selectedText = m_listWidget->currentItem()->text();
    }
}

void ModernDialog::setText(const QString& text)
{
    if (m_lineEdit) {
        m_lineEdit->setText(text);
        m_inputText = text;
    }
}

QString ModernDialog::getSelectedText() const
{
    return m_selectedText;
}

QString ModernDialog::getInputText() const
{
    return m_inputText;
}

void ModernDialog::onOkClicked()
{
    if (m_isTextInput) {
        m_inputText = m_lineEdit->text();
    } else {
        if (m_listWidget->currentItem()) {
            m_selectedText = m_listWidget->currentItem()->text();
        }
    }
    m_accepted = true;
    accept();
}

void ModernDialog::onCancelClicked()
{
    m_accepted = false;
    reject();
}

void ModernDialog::onItemSelectionChanged()
{
    if (m_listWidget->currentItem()) {
        m_selectedText = m_listWidget->currentItem()->text();
        m_okButton->setEnabled(true);
    } else {
        m_okButton->setEnabled(false);
    }
}

void ModernDialog::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    
    createTitleBar();
    createContent();
    createButtons();
    
    setLayout(m_mainLayout);
}

void ModernDialog::createTitleBar()
{
    // Title bar
    QWidget* titleBar = new QWidget();
    titleBar->setFixedHeight(50);
    titleBar->setObjectName("titleBar");
    
    QHBoxLayout* titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(20, 10, 20, 10);
    
    m_titleLabel = new QLabel("Dialog Title");
    m_titleLabel->setObjectName("titleLabel");
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    
    titleLayout->addWidget(m_titleLabel);
    titleLayout->addStretch();
    
    m_mainLayout->addWidget(titleBar);
}

void ModernDialog::createContent()
{
    // Content area
    QWidget* contentWidget = new QWidget();
    contentWidget->setObjectName("contentWidget");
    
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 20, 20, 20);
    contentLayout->setSpacing(15);
    
    // Content label
    m_contentLabel = new QLabel("Select an option:");
    m_contentLabel->setObjectName("contentLabel");
    QFont labelFont = m_contentLabel->font();
    labelFont.setPointSize(10);
    m_contentLabel->setFont(labelFont);
    contentLayout->addWidget(m_contentLabel);
    
    // List widget for items
    m_listWidget = new QListWidget();
    m_listWidget->setObjectName("itemList");
    m_listWidget->setAlternatingRowColors(true);
    m_listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(m_listWidget, &QListWidget::itemSelectionChanged, 
            this, &ModernDialog::onItemSelectionChanged);
    connect(m_listWidget, &QListWidget::itemDoubleClicked, 
            this, &ModernDialog::onOkClicked);
    contentLayout->addWidget(m_listWidget);
    
    // Line edit for text input
    m_lineEdit = new QLineEdit();
    m_lineEdit->setObjectName("textInput");
    m_lineEdit->hide();
    connect(m_lineEdit, &QLineEdit::returnPressed, this, &ModernDialog::onOkClicked);
    contentLayout->addWidget(m_lineEdit);
    
    m_mainLayout->addWidget(contentWidget);
}

void ModernDialog::createButtons()
{
    // Button area
    QWidget* buttonWidget = new QWidget();
    buttonWidget->setObjectName("buttonWidget");
    buttonWidget->setFixedHeight(60);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(20, 10, 20, 10);
    buttonLayout->setSpacing(10);
    
    buttonLayout->addStretch();
    
    // Cancel button
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setObjectName("cancelButton");
    m_cancelButton->setFixedSize(100, 35);
    connect(m_cancelButton, &QPushButton::clicked, this, &ModernDialog::onCancelClicked);
    buttonLayout->addWidget(m_cancelButton);
    
    // OK button
    m_okButton = new QPushButton("OK");
    m_okButton->setObjectName("okButton");
    m_okButton->setFixedSize(100, 35);
    m_okButton->setDefault(true);
    connect(m_okButton, &QPushButton::clicked, this, &ModernDialog::onOkClicked);
    buttonLayout->addWidget(m_okButton);
    
    m_mainLayout->addWidget(buttonWidget);
}

void ModernDialog::applyDarkTheme()
{
    setStyleSheet(R"(
        QDialog {
            background-color: #2b2b2b;
            border: 1px solid #404040;
            border-radius: 8px;
        }
        
        QWidget#titleBar {
            background-color: #363636;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
            border-bottom: 1px solid #404040;
        }
        
        QLabel#titleLabel {
            color: #ffffff;
            background: transparent;
        }
        
        QWidget#contentWidget {
            background-color: #2b2b2b;
        }
        
        QLabel#contentLabel {
            color: #cccccc;
            background: transparent;
        }
        
        QListWidget#itemList {
            background-color: #333333;
            border: 1px solid #555555;
            border-radius: 6px;
            color: #ffffff;
            selection-background-color: #0078d4;
            selection-color: #ffffff;
            alternate-background-color: #3a3a3a;
            font-size: 11px;
            padding: 5px;
        }
        
        QListWidget#itemList::item {
            padding: 8px;
            border-radius: 4px;
            margin: 1px;
        }
        
        QListWidget#itemList::item:hover {
            background-color: #404040;
        }
        
        QListWidget#itemList::item:selected {
            background-color: #0078d4;
            color: #ffffff;
        }
        
        QLineEdit#textInput {
            background-color: #333333;
            border: 1px solid #555555;
            border-radius: 6px;
            color: #ffffff;
            padding: 8px 12px;
            font-size: 11px;
        }
        
        QLineEdit#textInput:focus {
            border: 2px solid #0078d4;
        }
        
        QWidget#buttonWidget {
            background-color: #363636;
            border-bottom-left-radius: 8px;
            border-bottom-right-radius: 8px;
            border-top: 1px solid #404040;
        }
        
        QPushButton#okButton {
            background-color: #0078d4;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            font-size: 11px;
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
            border-radius: 6px;
            font-size: 11px;
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
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 100));
    shadowEffect->setOffset(0, 5);
    setGraphicsEffect(shadowEffect);
} 