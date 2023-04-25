#include "FilterWindow.h"
#include "ui_FilterWindow.h"

FilterWindow::FilterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterWindow)
{
    ui->setupUi(this);

	InitVariables();
	InitEvents();
    LoadSetting();
    RequestValue();
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

    connect(ui->pbSaveFilter, &QPushButton::clicked, this, &FilterWindow::SaveSetting);

}

void FilterWindow::SaveSetting()
{
    QList<QVariant> hsvParas;

    for(int i = 0; i < 6; i++)
    {
        hsvParas.append(sPara[i]->value());
    }

    QString filterName = QString("filter%1").arg(ui->cbObjectType->currentText());

    VarManager::getInstance()->Prefix = ProjectName;

    VarManager::getInstance()->updateVar(filterName + "hsvV", hsvParas);
    VarManager::getInstance()->updateVar(filterName + "thresV", ui->hsThreshold->value());
    VarManager::getInstance()->updateVar(filterName + "blurV", ui->hsBlurSize->value());
    VarManager::getInstance()->updateVar(filterName + "invert", ui->cbInvert->isChecked());
    VarManager::getInstance()->updateVar(filterName + "algorithm", FilterJob->CurrentFilter);
}

void FilterWindow::LoadSetting()
{
    VarManager::getInstance()->Prefix = ProjectName;

    QString filterName = QString("filter%1").arg(ui->cbObjectType->currentText());
    QList<QVariant> hsvParas = VarManager::getInstance()->getVar(filterName + "hsvV").toList();

    for(int i = 0; i < hsvParas.count(); i++)
    {
        sPara[i]->setValue(hsvParas.at(i).toInt());
        lbPara[i]->setText(QString::number(hsvParas.at(i).toInt()));
    }

    ui->hsThreshold->setValue(VarManager::getInstance()->getVar(filterName + "thresV", 100).toInt());
    ui->lbThreshold->setText(QString::number(ui->hsThreshold->value()));

    ui->hsBlurSize->setValue(VarManager::getInstance()->getVar(filterName + "blurV", 1).toInt());
    ui->lbBlurSize->setText(QString::number(ui->hsBlurSize->value()));

    ui->cbInvert->setChecked(VarManager::getInstance()->getVar(filterName + "invert", false).toBool());

    FilterJob->CurrentFilter = VarManager::getInstance()->getVar(filterName + "algorithm", FilterJob->CurrentFilter).toInt();
}

void FilterWindow::SetImage(cv::Mat mat)
{
    OriginMat.release();

    QMutex mux;
    mux.lock();
    OriginMat = mat.clone();
    mux.unlock();

    ui->lbOriginImage->setPixmap(ImageTool::cvMatToQPixmap(mat));

    RequestValue();
}

void FilterWindow::RequestValue()
{
    if (FilterJob->CurrentFilter == FilterWork::HSV)
    {
        emit ui->hsminH->sliderReleased();
    }
    else
    {
        emit ui->hsThreshold->sliderReleased();
    }
}

bool FilterWindow::IsInvertBinary()
{
	return ui->cbInvert->isChecked();
}

void FilterWindow::ProcessValueFromUI()
{
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

    SaveSetting();

//    emit ValueChanged(intParas, ui->cbInvert->isChecked(), ui->hsBlurSize->value());
    emit ColorFilterValueChanged(intParas);
    emit ColorInverted(ui->cbInvert->isChecked());
    emit BlurSizeChanged(blurSize);

    if (OriginMat.empty())
        return;

    emit requestFilter(OriginMat.clone(), intParas, ui->cbInvert->isChecked(), blurSize);
}
