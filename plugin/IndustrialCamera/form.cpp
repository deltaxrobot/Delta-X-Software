#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);


    CameraProcessorThread = new CameraProcessor();

    CameraProcessorThread->lbRatio = ui->lbDisplayRatio;
    CameraProcessorThread->cameraWidget = ui->lbCameraDisplay;

    CameraProcessorThread->moveToThread(new QThread(this));
    connect(CameraProcessorThread->thread(), SIGNAL(started()), CameraProcessorThread, SLOT(Loop()));
    connect(CameraProcessorThread->thread(), SIGNAL(finished()), CameraProcessorThread, SLOT(deleteLater()));

    CameraProcessorThread->thread()->start();


    CameraDisplayUpdatingTimer = new QTimer();
    connect(CameraDisplayUpdatingTimer, SIGNAL(timeout()), this, SLOT(intervalFunction()));

}

Form::~Form()
{
    CameraProcessorThread->IsLoopRunning = false;

    CameraProcessorThread->thread()->quit();
    CameraProcessorThread->thread()->wait();

    delete ui;
}

void Form::GetMessageFromOtherModule(QString cmd)
{

}

void Form::GetEventFromUI()
{
    emit EmitEventFromUI("Hello");
}

void Form::on_pbRefresh_clicked()
{
    ui->cbCameraList->addItems(CameraProcessorThread->IndustryCamera.FindCameraList());
}

void Form::on_pbConnectCamera_clicked()
{
    bool result = CameraProcessorThread->IndustryCamera.ConnectCamera(ui->cbCameraList->currentIndex());

    if (result == true)
    {
        ui->lbCameraName->setEnabled(true);
        ui->leCameraName->setEnabled(true);
        ui->leCameraName->setEnabled(true);
        ui->pbShotImage->setEnabled(true);
        ui->pbShotVideo->setEnabled(true);
        ui->cbStream->setEnabled(true);

        qDebug() << "Connected Industry Camera";

        CameraProcessorThread->ShotImage();

        ui->lbResolution->setText(QString("%1 x %2").arg(CameraProcessorThread->Width).arg(CameraProcessorThread->Height));
    }
}

void Form::on_cbStream_toggled(bool checked)
{
    CameraProcessorThread->IsStream = checked;
}


void Form::on_pbShotImage_clicked()
{
    CameraProcessorThread->ShotImage();
}


void Form::on_pbShotVideo_clicked()
{
    if (ui->pbShotVideo->isChecked() == true)
    {
        int inputValue = ui->leInterval->text().toInt();
        if (inputValue > 0)
            CameraProcessorThread->CameraInterval = inputValue;

        ui->lbFPS->setText(QString::number((float)1000/CameraProcessorThread->CameraInterval));

        CameraDisplayUpdatingTimer->start(CameraProcessorThread->CameraInterval);
        ui->pbShotVideo->setText("Stop");

        ui->cbCameraList->setEnabled(false);

    }
    else
    {
        CameraDisplayUpdatingTimer->stop();
        ui->pbShotVideo->setText("Continious Shot");
        ui->cbCameraList->setEnabled(true);

        ui->lbFPS->setText("0");
    }
}

void Form::intervalFunction()
{
    CameraProcessorThread->CaptureSignal = true;
}
