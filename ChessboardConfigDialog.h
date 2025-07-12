#ifndef CHESSBOARDCONFIGDIALOG_H
#define CHESSBOARDCONFIGDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSizePolicy>

class ChessboardConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChessboardConfigDialog(QWidget *parent = nullptr);
    QString getChessboardSize() const;

private slots:
    void onComboBoxChanged(const QString &text);

private:
    void setupUI();
    void applyDarkTheme();
    
    QLabel *titleLabel;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;
};

#endif // CHESSBOARDCONFIGDIALOG_H 