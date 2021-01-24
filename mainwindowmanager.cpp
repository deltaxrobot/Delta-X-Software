#include "mainwindowmanager.h"
#include "ui_mainwindowmanager.h"

MainWindowManager::MainWindowManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowManager)
{
    ui->setupUi(this);
}

MainWindowManager::~MainWindowManager()
{
    delete ui;
}
