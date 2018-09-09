#include "hsvwindow.h"
#include "ui_hsvwindow.h"

HSVWindow::HSVWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HSVWindow)
{
    ui->setupUi(this);
}

HSVWindow::~HSVWindow()
{
    delete ui;
}
