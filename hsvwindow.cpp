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

    settings.setValue("minH", sPara[0]->value());
    settings.setValue("maxH", sPara[1]->value());
    settings.setValue("minS", sPara[2]->value());
    settings.setValue("maxS", sPara[3]->value());
    settings.setValue("minV", sPara[4]->value());
    settings.setValue("maxV", sPara[5]->value());
}

void HSVWindow::LoadSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    sPara[0]->setValue(settings.value("minH", 0).toInt());
    sPara[1]->setValue(settings.value("maxH", 255).toInt());
    sPara[0]->setValue(settings.value("minS", 0).toInt());
    sPara[1]->setValue(settings.value("maxS", 255).toInt());
    sPara[0]->setValue(settings.value("minV", 0).toInt());
    sPara[1]->setValue(settings.value("maxV", 255).toInt());

    for (int i = 0; i < 6; i++)
    {
        lbPara[i]->setText(QString::number(sPara[i]->value()));
    }
}

bool HSVWindow::IsInvertBinary()
{
	return ui->cbInvert->isChecked();
}

void HSVWindow::InitEvents()
{
	for (int i = 0; i < 6; i++)
	{
		connect(sPara[i], SIGNAL(valueChanged(int)), this, SLOT(UpdateSliderValueToLabel()));
	}

	connect(ui->hsThreshold, SIGNAL(valueChanged(int)), this, SLOT(UpdateSliderValueToLabel()));
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
	}
	else
	{
		emit ValueChanged(sPara[0]->value(), sPara[1]->value(), sPara[2]->value(), sPara[3]->value(), sPara[4]->value(), sPara[5]->value());
	}
}
