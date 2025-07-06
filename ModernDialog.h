#ifndef MODERNDIALOG_H
#define MODERNDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QStringList>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsDropShadowEffect>

class ModernDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModernDialog(QWidget* parent = nullptr);
    ~ModernDialog();

    // Static methods for common dialogs
    static QString getItem(QWidget* parent, const QString& title, const QString& label, 
                          const QStringList& items, int current = 0, bool* ok = nullptr);
    
    static QString getText(QWidget* parent, const QString& title, const QString& label, 
                          const QString& text = QString(), bool* ok = nullptr);

    // Instance methods for customization
    void setTitle(const QString& title);
    void setLabel(const QString& label);
    void setItems(const QStringList& items);
    void setCurrentItem(int index);
    void setText(const QString& text);
    QString getSelectedText() const;
    QString getInputText() const;

private slots:
    void onOkClicked();
    void onCancelClicked();
    void onItemSelectionChanged();

private:
    void setupUI();
    void applyDarkTheme();
    void createTitleBar();
    void createContent();
    void createButtons();
    
    // UI Components
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;
    QLabel* m_contentLabel;
    QListWidget* m_listWidget;
    QLineEdit* m_lineEdit;
    QPushButton* m_okButton;
    QPushButton* m_cancelButton;
    
    // State
    QString m_selectedText;
    QString m_inputText;
    bool m_isTextInput;
    bool m_accepted;
};

#endif // MODERNDIALOG_H 