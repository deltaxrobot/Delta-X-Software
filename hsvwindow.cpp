#include "hsvwindow.h"
#include "ui_hsvwindow.h"

HSVWindow::HSVWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HSVWindow)
{
    ui->setupUi(this);

	InitVariables();
	InitEvents();
}

HSVWindow::~HSVWindow()
{
    delete ui;
}

void HSVWindow::InitVariables()
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
}

void HSVWindow::SaveSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    SaveSetting(&settings);
}

void HSVWindow::SaveSetting(QSettings *setting)
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

void HSVWindow::LoadSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    LoadSetting(&settings);
}

void HSVWindow::LoadSetting(QSettings *setting)
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

bool HSVWindow::IsInvertBinary()
{
	return ui->cbInvert->isChecked();
}

void HSVWindow::InitEvents()
{
	for (int i = 0; i < 6; i++)
	{
        connect(sPara[i], &QAbstractSlider::sliderReleased, this, &HSVWindow::UpdateSliderValueToLabel);
	}

    connect(ui->hsThreshold, &QAbstractSlider::sliderReleased, this, &HSVWindow::UpdateSliderValueToLabel);
}

void HSVWindow::UpdateSliderValueToLabel()
{
	for (int i = 0; i < 6; i++)
	{
		lbPara[i]->setText(QString::number(sPara[i]->value()));
	}

	QSlider*  senderSlide = qobject_cast<QSlider*>(sender());

	if (senderSlide->objectName() == "hsThreshold")
	{
		emit ValueChanged(ui->hsThreshold->value());
        ui->lbThreshold->setText(QString::number(ui->hsThreshold->value()));
	}
	else
	{
		emit ValueChanged(sPara[0]->value(), sPara[1]->value(), sPara[2]->value(), sPara[3]->value(), sPara[4]->value(), sPara[5]->value());
	}
}
