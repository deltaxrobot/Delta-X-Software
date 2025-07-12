#include "ChessboardConfigDialog.h"

ChessboardConfigDialog::ChessboardConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    applyDarkTheme();
    setWindowTitle(tr("Chessboard Configuration"));
    setFixedSize(320, 170);
}

void ChessboardConfigDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    
    // Title label
    titleLabel = new QLabel(tr("Select chessboard size:"));
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel);
    
    // Combo box with preset values
    comboBox = new QComboBox();
    comboBox->setObjectName("comboBox");
    comboBox->setEditable(false);
    comboBox->addItems({
        "3x3",
        "4x4", 
        "5x5",
        "6x6",
        "7x7",
        "8x8",
        "9x9",
        "10x10",
        "Custom"
    });
    comboBox->setCurrentText("7x7"); // Default value
    comboBox->setFixedHeight(32);
    
    mainLayout->addWidget(comboBox);
    
    // Line edit for custom input (initially hidden)
    lineEdit = new QLineEdit();
    lineEdit->setObjectName("lineEdit");
    lineEdit->setPlaceholderText("e.g., 12x8");
    lineEdit->setVisible(false);
    lineEdit->setFixedHeight(32);
    mainLayout->addWidget(lineEdit);
    
    // Add some spacing
    mainLayout->addSpacing(10);
    
    // Button box
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setObjectName("buttonBox");
    
    // Set button sizes explicitly
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    QPushButton *cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
    
    if (okButton) {
        okButton->setFixedSize(100, 36);
        okButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        okButton->setText("OK");
    }
    if (cancelButton) {
        cancelButton->setFixedSize(100, 36);
        cancelButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        cancelButton->setText("Cancel");
    }
    
    mainLayout->addWidget(buttonBox);
    
    // Connections
    connect(comboBox, &QComboBox::currentTextChanged, this, &ChessboardConfigDialog::onComboBoxChanged);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void ChessboardConfigDialog::applyDarkTheme()
{
    setStyleSheet(R"(
        QDialog {
            background-color: #2b2b2b;
            border: 1px solid #404040;
            border-radius: 8px;
            color: #ffffff;
        }
        
        QLabel#titleLabel {
            color: #ffffff;
            background: transparent;
            font-size: 11pt;
            font-weight: bold;
            padding: 4px 0;
        }
        
        QComboBox#comboBox {
            background-color: rgb(60, 60, 65);
            border: 1px solid rgb(90, 90, 90);
            border-radius: 5px;
            padding: 6px 10px;
            color: rgb(255, 255, 255);
            font-size: 10pt;
            height: 32px;
        }
        
        QComboBox#comboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 18px;
            border-left: 1px solid rgb(90, 90, 90);
            background: rgb(80, 80, 85);
            border-top-right-radius: 5px;
            border-bottom-right-radius: 5px;
        }
        
        QComboBox#comboBox::down-arrow {
            image: url(:/icon/Arrow Pointing Down_16px.png);
            width: 10px;
            height: 10px;
        }
        
        QComboBox#comboBox QAbstractItemView {
            background-color: rgb(60, 60, 65);
            border: 1px solid rgb(90, 90, 90);
            border-radius: 5px;
            selection-background-color: #007cd6;
            selection-color: #ffffff;
            color: rgb(255, 255, 255);
            padding: 4px;
        }
        
        QComboBox#comboBox QAbstractItemView::item {
            min-height: 22px;
            padding: 2px 6px;
            border-radius: 3px;
        }
        
        QComboBox#comboBox QAbstractItemView::item:hover {
            background-color: #404040;
        }
        
        QComboBox#comboBox QAbstractItemView::item:selected {
            background-color: #007cd6;
            color: #ffffff;
        }
        
        QLineEdit#lineEdit {
            background-color: rgb(60, 60, 65);
            border: 1px solid rgb(90, 90, 90);
            border-radius: 5px;
            padding: 6px 10px;
            color: rgb(255, 255, 255);
            font-size: 10pt;
            height: 32px;
        }
        
        QLineEdit#lineEdit:focus {
            border: 2px solid #007cd6;
        }
        
        QLineEdit#lineEdit::placeholder {
            color: rgb(150, 150, 150);
        }
        
        QDialogButtonBox#buttonBox {
            background: transparent;
        }
        
        QDialogButtonBox#buttonBox QPushButton {
            background-color: #4A4A4F;
            border: 1px solid rgb(90, 90, 90);
            border-radius: 5px;
            padding: 8px 20px;
            color: rgb(255, 255, 255);
            font-size: 10pt;
            font-weight: bold;
            min-width: 90px;
            height: 36px;
        }
        
        QDialogButtonBox#buttonBox QPushButton:hover {
            background-color: rgb(111, 111, 111);
            border-color: #007cd6;
        }
        
        QDialogButtonBox#buttonBox QPushButton:pressed {
            background-color: #007cd6;
            border-color: #007cd6;
        }
        
        QDialogButtonBox#buttonBox QPushButton:default {
            background-color: #007cd6;
            border-color: #007cd6;
        }
        
        QDialogButtonBox#buttonBox QPushButton:default:hover {
            background-color: #106ebe;
            border-color: #106ebe;
        }
        
        QDialogButtonBox#buttonBox QPushButton:default:pressed {
            background-color: #005a9e;
            border-color: #005a9e;
        }
    )");
}

void ChessboardConfigDialog::onComboBoxChanged(const QString &text)
{
    if (text == "Custom") {
        lineEdit->setVisible(true);
        lineEdit->setFocus();
        lineEdit->setText("7x7"); // Default when switching to custom
    } else {
        lineEdit->setVisible(false);
    }
    
    // Adjust dialog height with smooth animation
    if (text == "Custom") {
        setFixedSize(320, 210);
    } else {
        setFixedSize(320, 170);
    }
}

QString ChessboardConfigDialog::getChessboardSize() const
{
    if (comboBox->currentText() == "Custom") {
        return lineEdit->text().trimmed();
    } else {
        return comboBox->currentText();
    }
} 