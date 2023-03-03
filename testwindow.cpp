#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    Init();
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::Init()
{
    Camera *myObject = new Camera;

    QThread *thread = new QThread;
    myObject->moveToThread(thread);

    connect(thread, &QThread::started, myObject, &Camera::run);

    thread->start();
}
