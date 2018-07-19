#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectDeltaRobot()
{
    ui->lbStatee->setText("Hello");
}

void MainWindow::on_pbConnectonnect_clicked()
{
    ui->lbStatee->setText("Hello");
}
