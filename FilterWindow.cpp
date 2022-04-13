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
    qRegisterMetaType< cv::Mat >("cv::Mat");

    for (int i = 0; i < 6; i++)
    {
        connect(sPara[i], &QAbstractSlider::sliderReleased, this, &FilterWindow::ProcessValueFromUI);
    }

    connect(ui->hsThreshold, &QAbstractSlider::sliderReleased, this, &FilterWindow::ProcessValueFromUI);
    connect(ui->cbInvert, &QCheckBox::toggled, this, &FilterWindow::ProcessValueFromUI);
    connect(ui->hsBlurSize, &QAbstractSlider::sliderReleased, this, &FilterWindow::ProcessValueFromUI);

    connect(this, &FilterWindow::requestFilter, FilterJob, &FilterWork::DoFilter);

    connect(FilterJob->thread(), SIGNAL(finished()), FilterJob->thread(), SLOT(deleteLater()));
    connect(FilterJob, &FilterWork::FinishedFilter, ui->lbProcessImage, &QLabel::setPixmap);

}

void FilterWindow::SaveSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    SaveSetting(&settings);
}

void FilterWindow::SaveSetting(QSettings *setting)
{
    QList<QVariant> hsvParas;

    for(int i = 0; i < 6; i++)
    {
        hsvParas.append(sPara[i]->value());
    }

    setting->setValue("hsvV", hsvParas);

    setting->setValue("thresV", ui->hsThreshold->value());

    setting->setValue("blurV", ui->hsThreshold->value());

    setting->setValue("invert", ui->cbInvert->isChecked());
}

void FilterWindow::LoadSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    LoadSetting(&settings);
}

void FilterWindow::LoadSetting(QSettings *setting)
{
    QList<QVariant> hsvParas = setting->value("hsvV").toList();

    for(int i = 0; i < hsvParas.count(); i++)
    {
        sPara[i]->setValue(hsvParas.at(i).toInt());
        lbPara[i]->setText(QString::number(hsvParas.at(i).toInt()));
    }

    ui->hsThreshold->setValue(setting->value("thresV", 100).toInt());
    ui->lbThreshold->setText(QString::number(ui->hsThreshold->value()));

    ui->hsBlurSize->setValue(setting->value("blurV", 100).toInt());
    ui->lbBlurSize->setText(QString::number(ui->hsBlurSize->value()));

    ui->cbInvert->setChecked(setting->value("invert", false).toBool());
}

void FilterWindow::SetImage(cv::Mat mat)
{
    OriginMat.release();
    OriginMat = mat.clone();

    ui->lbOriginImage->setPixmap(ImageTool::cvMatToQPixmap(mat));
}

bool FilterWindow::IsInvertBinary()
{
	return ui->cbInvert->isChecked();
}

void FilterWindow::ProcessValueFromUI()
{
    if (OriginMat.empty())
        return;

    if (sender() == ui->hsThreshold)
	{
        intParas.clear();

        int value = ui->hsThreshold->value();
        ui->lbThreshold->setText(QString::number(value));
        intParas.append(value);
    }
    else if (sender() != ui->hsBlurSize && sender() != ui->cbInvert)
    {
        intParas.clear();

        for (int i = 0; i < 6; i++)
        {
            int value = sPara[i]->value();
            lbPara[i]->setText(QString::number(value));
            intParas.append(value);
        }
    }


    int blurSize = ui->hsBlurSize->value();
    blurSize = (blurSize / 2)  * 2 + 1;

    ui->lbBlurSize->setText(QString::number(blurSize));

//    emit ValueChanged(intParas, ui->cbInvert->isChecked(), ui->hsBlurSize->value());
    emit ColorFilterValueChanged(intParas);
    emit ColorInverted(ui->cbInvert->isChecked());
    emit BlurSizeChanged(blurSize);

    emit requestFilter(OriginMat.clone(), intParas, ui->cbInvert->isChecked(), blurSize);
}
