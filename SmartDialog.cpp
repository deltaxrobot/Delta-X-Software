#include "SmartDialog.h"

SmartDialog::SmartDialog(QWidget *parent) : QWidget(parent)
{

}

void SmartDialog::SetType(int typeId)
{
    dialogType = typeId;
}

bool SmartDialog::PopUp(QString title, QString msg)
{
    QMessageBox* CloseUIBox = new QMessageBox();
    this->setStyleSheet("QPushButton{ min-width: 60px; min-height: 20px;}");
    QMessageBox::StandardButton resBtn = CloseUIBox->question(this, title, msg, QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes)
        return true;
    else
        return false;
}
