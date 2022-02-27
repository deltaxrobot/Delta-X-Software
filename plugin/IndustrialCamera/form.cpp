#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent), IndustryCamera(),
    ui(new Ui::Form)
{
    ui->setupUi(this);


//    CameraProcessorThread = new CameraProcessor();

//    CameraProcessorThread->lbRatio = ui->lbDisplayRatio;
//    CameraProcessorThread->cameraWidget = ui->lbCameraDisplay;

//    CameraProcessorThread->moveToThread(new QThread(this));
//    connect(CameraProcessorThread->thread(), SIGNAL(started()), CameraProcessorThread, SLOT(ShotImage()));
//    connect(CameraProcessorThread->thread(), SIGNAL(finished()), CameraProcessorThread, SLOT(deleteLater()));
//    connect(CameraProcessorThread, &CameraProcessor::FinishReadingImage, ui->lbCameraDisplay, &QLabel::setPixmap);
//    connect(CameraProcessorThread, &CameraProcessor::UpdatedRatio, ui->lbDisplayRatio, &QLabel::setText);

    CameraDisplayUpdatingTimer = new QTimer();
    CameraDisplayUpdatingTimer->setTimerType(Qt::PreciseTimer);
    connect(CameraDisplayUpdatingTimer, SIGNAL(timeout()), this, SLOT(intervalFunction()));

    QTimer::singleShot(2000, this, SLOT(on_pbRefresh_clicked()));

}

Form::~Form()
{
//    CameraProcessorThread->IsLoopRunning = false;

//    CameraProcessorThread->thread()->quit();
//    CameraProcessorThread->thread()->wait();

    delete ui;
}

void Form::LoadSettings(QSettings *setting)
{
    bool isOpen = setting->value("IsOpen", false).toBool();
    QString cameraName = setting->value("CameraName", "").toString();

    if (isOpen == true)
    {
        for (int i = 0; ui->cbCameraList->count(); i++)
        {
            if (ui->cbCameraList->itemText(i) == cameraName)
            {
                QTimer::singleShot(3000, this, SLOT(on_pbConnectCamera_clicked()));

                break;
            }
        }
    }

    int scaleWidth = setting->value("ScaleWidth", 800).toInt();
    int interval = setting->value("Interval", 500).toInt();
    bool continiousShot = setting->value("ContiniousShot", false).toBool();

    ui->leImageWidth->setText(QString::number(scaleWidth));
    ui->leInterval->setText(QString::number(interval));

    if (continiousShot == true)
    {
        QTimer::singleShot(4000, ui->pbShotVideo, SLOT(click()));
    }
}

void Form::SaveSettings(QSettings *setting)
{
    bool isOpen = IndustryCamera.IsOpen();
    QString cameraName = ui->cbCameraList->currentText();

    setting->setValue("IsOpen", isOpen);
    setting->setValue("CameraName", cameraName);
    setting->setValue("ScaleWidth", ui->leImageWidth->text());
    setting->setValue("Interval", ui->leInterval->text());
    setting->setValue("ContiniousShot", CameraDisplayUpdatingTimer->isActive());
}

void Form::GetMessageFromOtherModule(QString cmd)
{

}

void Form::GetEventFromUI()
{
    emit EmitEventFromUI("Hello");
}

void Form::GetStateLastJob(bool state)
{
    IsLastJobDone = state;
}

void Form::on_pbRefresh_clicked()
{
    ui->cbCameraList->clear();
    ui->cbCameraList->addItems(IndustryCamera.FindCameraList());
}

void Form::on_pbConnectCamera_clicked()
{
    if (ui->pbConnectCamera->text() == "Connect")
    {
        if (ui->cbCameraList->count() == 0)
        {
            QMessageBox::information(this, "Attention", "No camera to connect!");
            return;
        }

        bool result = IndustryCamera.ConnectCamera(ui->cbCameraList->currentIndex());

        if (result == true)
        {
            ui->lbCameraName->setEnabled(true);
            ui->leCameraName->setEnabled(true);
            ui->leCameraName->setEnabled(true);
            ui->pbShotImage->setEnabled(true);
            ui->pbShotVideo->setEnabled(true);
//            ui->cbStream->setEnabled(true);

            qDebug() << "Connected Industry Camera";

            intervalFunction();

//            ui->lbResolution->setText(QString("%1 x %2").arg(CameraProcessorThread->Width).arg(CameraProcessorThread->Height));

            QString exposureTime = QString::number(IndustryCamera.GetExposureTime());

            ui->pbConnectCamera->setText("Disconnect");

        }
    }
    else
    {
        ui->pbConnectCamera->setText("Connect");

        if (IndustryCamera.IsOpen())
        {
            IndustryCamera.DisconnectCamera();
        }
    }

}

void Form::on_cbStream_toggled(bool checked)
{
//    CameraProcessorThread->IsStream = checked;
}


void Form::on_pbShotImage_clicked()
{
//    CameraProcessorThread->ShotImage();
}


void Form::on_pbShotVideo_clicked()
{
    if (ui->pbShotVideo->isChecked() == true)
    {
        int inputValue = ui->leInterval->text().toInt();

        ui->lbFPS->setText(QString::number((float)1000/inputValue));

        CameraDisplayUpdatingTimer->setInterval(inputValue);
        CameraDisplayUpdatingTimer->setTimerType(Qt::PreciseTimer);
        CameraDisplayUpdatingTimer->start();
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
//    CameraProcessorThread->CaptureSignal = true;
//    CameraProcessorThread->thread()->start();
    qDebug() << "timer: " << ElapseTimer.restart();

    if (IsLastJobDone == false)
        return;

    IsLastJobDone = false;

    CameraProcessorJob = new CameraProcessor();

    CameraProcessorJob->lbRatio = ui->lbDisplayRatio;
    CameraProcessorJob->cameraWidget = ui->lbCameraDisplay;
    CameraProcessorJob->IndustryCamera = &IndustryCamera;
    if (ui->cbEnoughResize->isChecked() == true)
    {
        CameraProcessorJob->MatWidth = ui->leImageWidth->text().toInt();
    }
    else
    {

        CameraProcessorJob->MatWidth = -1;
    }
    connect(CameraProcessorJob, &CameraProcessor::FinishReadingImage, ui->lbCameraDisplay, &QLabel::setPixmap);
    connect(CameraProcessorJob, &CameraProcessor::UpdatedRatio, ui->lbDisplayRatio, &QLabel::setText);
    connect(CameraProcessorJob, &CameraProcessor::CapturedImage, this, &Form::CapturedImage);
    connect(CameraProcessorJob, &CameraProcessor::StartedCapture, this, &Form::StartedCapture);
    connect(CameraProcessorJob, &CameraProcessor::FinishJob, this, &Form::GetStateLastJob);

    QThreadPool::globalInstance()->start(CameraProcessorJob);
}

void Form::on_leExposureTime_returnPressed()
{
    int exposureTime = ui->leExposureTime->text().toInt();
    IndustryCamera.SetExposureTime(exposureTime);
}


void Form::on_leGain_returnPressed()
{
    int gain = ui->leGain->text().toInt();
}


void Form::on_leImageWidth_returnPressed()
{
    if (CameraProcessorJob != NULL)
    {
        CameraProcessorJob->MatWidth = ui->leImageWidth->text().toInt();
    }
}


void Form::on_cbEnoughResize_toggled(bool checked)
{
    if (checked == true)
    {
        ui->leImageWidth->setEnabled(true);
        ui->lbWidth->setEnabled(true);
        ui->lbWidthUnit->setEnabled(true);
    }
    else
    {
        ui->leImageWidth->setEnabled(true);
        ui->lbWidth->setEnabled(true);
        ui->lbWidthUnit->setEnabled(true);
    }
}

