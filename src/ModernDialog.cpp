#include "ModernDialog.h"
#include "UiTheme.h"
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
    applyTheme();
    
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
    titleBar->setMinimumHeight(50);
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
    buttonWidget->setMinimumHeight(60);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(20, 10, 20, 10);
    buttonLayout->setSpacing(10);
    
    buttonLayout->addStretch();
    
    // Cancel button
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setObjectName("cancelButton");
    m_cancelButton->setMinimumSize(100, 35);
    connect(m_cancelButton, &QPushButton::clicked, this, &ModernDialog::onCancelClicked);
    buttonLayout->addWidget(m_cancelButton);
    
    // OK button
    m_okButton = new QPushButton("OK");
    m_okButton->setObjectName("okButton");
    m_okButton->setMinimumSize(100, 35);
    m_okButton->setDefault(true);
    connect(m_okButton, &QPushButton::clicked, this, &ModernDialog::onOkClicked);
    buttonLayout->addWidget(m_okButton);
    
    m_mainLayout->addWidget(buttonWidget);
}

void ModernDialog::applyTheme()
{
    setProperty("deltaDialog", true);
    setStyleSheet(QString());
    UiTheme::polishWidgetTree(this);
    
    // Add shadow effect
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 100));
    shadowEffect->setOffset(0, 5);
    setGraphicsEffect(shadowEffect);
}
