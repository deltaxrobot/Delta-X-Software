#include "FilterWindow.h"
#include "ui_FilterWindow.h"

FilterWindow::FilterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterWindow)
{
    ui->setupUi(this);

	InitVariables();
	InitEvents();
}

FilterWindow::~FilterWindow()
{
    FilterJob->thread()->quit();
    FilterJob->thread()->wait();

    delete ui;
}

void FilterWindow::InitVariables()
{
	sPara[0] = ui->hsminH;
	sPara[1] = ui->hsmaxH;
	sPara[2] = ui->hsminS;
	sPara[3] = ui->hsmaxS;
	sPara[4] = ui->hsminV;
	sPara[5] = ui->hsmaxV;

	lbPara[0] = ui->lbminH;
	lbPara[1] = ui->lbmaxH;
	lbPara[2] = ui->lbminS;
	lbPara[3] = ui->lbmaxS;
	lbPara[4] = ui->lbminV;
	lbPara[5] = ui->lbmaxV;

	lbOriginImage = ui->lbOriginImage;
    lbProcessImage = ui->lbProcessImage;

    FilterJob = new FilterWork();
    FilterJob->moveToThread(new QThread(this));

    FilterJob->thread()->start();
}



void FilterWindow::InitEvents()
{
    for (int i = 0; i < 6; i++)
    {
        connect(sPara[i], &QAbstractSlider::sliderReleased, this, &FilterWindow::UpdateSliderValueToLabel);
    }

    connect(ui->hsThreshold, &QAbstractSlider::sliderReleased, this, &FilterWindow::UpdateSliderValueToLabel);

    qRegisterMetaType< cv::Mat >("cv::Mat");

    connect(FilterJob->thread(), SIGNAL(finished()), FilterJob->thread(), SLOT(deleteLater()));
    connect(this, &FilterWindow::requestThresholdFilter, FilterJob, &FilterWork::DoThresholdFilter);
    connect(this, &FilterWindow::requestHSVFilter, FilterJob, &FilterWork::DoHSVFilter);
    connect(ui->cbInvert, &QCheckBox::toggled, FilterJob, &FilterWork::InvertImage);

    connect(FilterJob, &FilterWork::FinishedFilter, ui->lbProcessImage, &QLabel::setPixmap);

}

void FilterWindow::SaveSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    SaveSetting(&settings);
}

void FilterWindow::SaveSetting(QSettings *setting)
{
    setting->setValue("minH", sPara[0]->value());
    setting->setValue("maxH", sPara[1]->value());
    setting->setValue("minS", sPara[2]->value());
    setting->setValue("maxS", sPara[3]->value());
    setting->setValue("minV", sPara[4]->value());
    setting->setValue("maxV", sPara[5]->value());

    setting->setValue("thresV", ui->hsThreshold->value());

    setting->setValue("invert", ui->cbInvert->isChecked());
}

void FilterWindow::LoadSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    LoadSetting(&settings);
}

void FilterWindow::LoadSetting(QSettings *setting)
{
    sPara[0]->setValue(setting->value("minH", 0).toInt());
    sPara[1]->setValue(setting->value("maxH", 255).toInt());
    sPara[0]->setValue(setting->value("minS", 0).toInt());
    sPara[1]->setValue(setting->value("maxS", 255).toInt());
    sPara[0]->setValue(setting->value("minV", 0).toInt());
    sPara[1]->setValue(setting->value("maxV", 255).toInt());

    ui->hsThreshold->setValue(setting->value("thresV", 100).toInt());
    ui->lbThreshold->setText(QString::number(ui->hsThreshold->value()));


    for (int i = 0; i < 6; i++)
    {
        lbPara[i]->setText(QString::number(sPara[i]->value()));
    }

    ui->cbInvert->setChecked(setting->value("invert", false).toBool());
}

void FilterWindow::SetImage(cv::Mat mat)
{
    OriginMat = mat;

    ui->lbOriginImage->setPixmap(ImageTool::cvMatToQPixmap(mat));
}

bool FilterWindow::IsInvertBinary()
{
	return ui->cbInvert->isChecked();
}

void FilterWindow::UpdateSliderValueToLabel()
{
    ui->lbOriginImage->setPixmap(ImageTool::cvMatToQPixmap(OriginMat));

    int paras[6];
	for (int i = 0; i < 6; i++)
	{
        int value = sPara[i]->value();
        lbPara[i]->setText(QString::number(value));
        paras[i] = value;
	}

	QSlider*  senderSlide = qobject_cast<QSlider*>(sender());

	if (senderSlide->objectName() == "hsThreshold")
	{
        int value = ui->hsThreshold->value();
        //emit ValueChanged(value);
        ui->lbThreshold->setText(QString::number(ui->hsThreshold->value()));

        emit requestThresholdFilter(OriginMat.clone(), value);
    }
	else
	{
        //emit ValueChanged(sPara[0]->value(), sPara[1]->value(), sPara[2]->value(), sPara[3]->value(), sPara[4]->value(), sPara[5]->value());

        emit requestHSVFilter(OriginMat.clone(), paras[0], paras[1], paras[2], paras[3], paras[4], paras[5]);
	}
}
