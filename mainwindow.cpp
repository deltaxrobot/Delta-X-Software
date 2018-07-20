#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitVariables();
    InitEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitEvents()
{
    connect(ui->pbConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectDeltaRobot()));
}

void MainWindow::InitVariables()
{
    DeltaPort = new ConnectionManager(this);
    VisualArea = new GLWidget();

    QHBoxLayout *container = new QHBoxLayout;

    container->addWidget(VisualArea);

    ui->wgOpenGl->setLayout(container);
}

void MainWindow::ConnectDeltaRobot()
{
    if (DeltaPort->FindDeltaRobot() == true)
    {
        ui->lbState->setText("Delta Robot is connected !");
        ui->lbDebug->setText(DeltaPort->SerialPort->portName());
    }
}
