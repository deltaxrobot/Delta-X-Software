#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent), IndustryCamera(),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    CameraReaderWork = new CameraReader();
    CameraReaderWork->moveToThread(new QThread(this));
    connect(CameraReaderWork->thread(), SIGNAL(finished()), CameraReaderWork, SLOT(deleteLater()));
    connect(this, &Form::RequestImage, CameraReaderWork, &CameraReader::ShotImage);
    connect(CameraReaderWork, &CameraReader::HadConnectingResult, this, &Form::GetResultOfCameraConnecting);
    connect(this, &Form::RequestConnectCamera, CameraReaderWork, &CameraReader::ConnectCamera);
    connect(this, &Form::RequestDisconnectCamera, CameraReaderWork, &CameraReader::DisconnectCamera);
//    connect(CameraReaderWork, &CameraReader::CapturedImage, this, &Form::CapturedImage);
//    connect(CameraReaderWork, &CameraReader::StartedCapture, this, &Form::StartedCapture);
    connect(CameraReaderWork, &CameraReader::FinishReadingImage, this, &Form::GetImageToDisplay);
    connect(this, &Form::RequestCameraList, CameraReaderWork, &CameraReader::ScanCameras);
    connect(CameraReaderWork, &CameraReader::HadCameraList, this, &Form::GetCameraList);
    connect(this, &Form::UpdateResizeWidth, CameraReaderWork, &CameraReader::GetResizeImageWidth);

    CameraReaderWork->thread()->start();

    CameraDisplayUpdatingTimer = new QTimer();
    CameraDisplayUpdatingTimer->setTimerType(Qt::PreciseTimer);
    connect(CameraDisplayUpdatingTimer, SIGNAL(timeout()), this, SLOT(intervalFunction()));

    QTimer::singleShot(2000, this, SLOT(on_pbRefresh_clicked()));

}

Form::~Form()
{
//    CameraProcessorThread->IsLoopRunning = false;

    CameraReaderWork->thread()->quit();
    CameraReaderWork->thread()->wait();

//    delete CameraReaderWork;

    delete ui;
}

void Form::LoadSettings(QSettings *setting)
{
    bool isOpen = setting->value("IsOpen", false).toBool();
    cameraName = setting->value("CameraName", "").toString();

    int scaleWidth = setting->value("ScaleWidth", 800).toInt();
    int interval = setting->value("Interval", 500).toInt();
    autoPlay = setting->value("ContiniousShot", false).toBool();

    ui->leImageWidth->setText(QString::number(scaleWidth));
    ui->leInterval->setText(QString::number(interval));

    if (isOpen == true)
    {
        QTimer::singleShot(3000, this, SLOT(TryToConnectCamera()));
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

void Form::TryToConnectCamera()
{
    for (int i = 0; ui->cbCameraList->count(); i++)
    {
        if (ui->cbCameraList->itemText(i) == cameraName)
        {
            on_pbConnectCamera_clicked();
            QTimer::singleShot(3000, ui->pbShotVideo, SLOT(click()));
            break;
        }
    }
}

void Form::GetResultOfCameraConnecting(bool result)
{
    if (result == true)
    {
        ui->lbCameraName->setEnabled(true);
        ui->leCameraName->setEnabled(true);
        ui->pbShotImage->setEnabled(true);
        ui->pbShotVideo->setEnabled(true);

        ui->pbConnectCamera->setText("Disconnect");

        emit RequestImage();
    }
    else
    {

    }
}

void Form::GetImageToDisplay(QPixmap pixmap)
{
    ui->lbCameraDisplay->setPixmap(pixmap);
    ui->lbCameraDisplay->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

void Form::GetCameraList(QStringList list)
{
    ui->cbCameraList->clear();
    ui->cbCameraList->addItems(list);
}

void Form::on_pbRefresh_clicked()
{
    emit RequestCameraList();
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

        emit RequestConnectCamera(ui->cbCameraList->currentIndex());
    }
    else
    {
        ui->pbConnectCamera->setText("Connect");

        emit RequestDisconnectCamera();
    }

}

void Form::on_cbStream_toggled(bool checked)
{

}


void Form::on_pbShotImage_clicked()
{
    emit RequestImage();
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
    emit RequestImage();
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
    emit UpdateResizeWidth(ui->leImageWidth->text().toInt());
}


void Form::on_cbEnoughResize_toggled(bool checked)
{
    if (checked == true)
    {
        ui->leImageWidth->setEnabled(true);
        ui->lbWidth->setEnabled(true);
        ui->lbWidthUnit->setEnabled(true);

        emit UpdateResizeWidth(ui->lbWidth->text().toInt());
    }
    else
    {
        ui->leImageWidth->setEnabled(false);
        ui->lbWidth->setEnabled(false);
        ui->lbWidthUnit->setEnabled(false);

        emit UpdateResizeWidth(-1);
    }
}

