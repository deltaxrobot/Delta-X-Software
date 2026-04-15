#include "FilterWindow.h"
#include "ui_FilterWindow.h"

FilterWindow::FilterWindow(QWidget *parent, QString projectName) : QDialog(parent),
                                              ui(new Ui::FilterWindow)
{
    ui->setupUi(this);

    ProjectName = projectName;

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
    qRegisterMetaType<cv::Mat>("cv::Mat");

    for (int i = 0; i < 6; i++)
    {
        connect(sPara[i], &QAbstractSlider::sliderReleased, this, &FilterWindow::ProcessValueFromUI);
    }

    connect(ui->hsThreshold, &QAbstractSlider::sliderReleased, this, &FilterWindow::ProcessValueFromUI);
    connect(ui->cbInvert, &QCheckBox::toggled, this, &FilterWindow::ProcessValueFromUI);
    connect(ui->hsBlurSize, &QAbstractSlider::sliderReleased, this, &FilterWindow::ProcessValueFromUI);

    connect(this, &FilterWindow::requestFilter, FilterJob, &FilterWork::DoFilter);

    connect(FilterJob->thread(), SIGNAL(finished()), FilterJob->thread(), SLOT(deleteLater()));
    connect(FilterJob, &FilterWork::FinishedFilter, [=](cv::Mat mat)
    {
        QPixmap pixmap = ImageTool::cvMatToQPixmap(mat);
        pixmap = pixmap.scaled(lbOriginImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->lbProcessImage->setPixmap(pixmap);
    });
}

void FilterWindow::SaveSetting()
{
    QList<QVariant> hsvParas;

    for (int i = 0; i < 6; i++)
    {
        hsvParas.append(sPara[i]->value());
    }

    QString filterName = QString(".filter%1.").arg(ui->cbObjectType->currentText());

    VariableManager::instance().Prefix = ProjectName;

    VariableManager::instance().updateVar(Prefix + filterName + "hsvV", hsvParas);
    VariableManager::instance().updateVar(Prefix + filterName + "thresV", ui->hsThreshold->value());
    VariableManager::instance().updateVar(Prefix + filterName + "blurV", ui->hsBlurSize->value());
    VariableManager::instance().updateVar(Prefix + filterName + "invert", ui->cbInvert->isChecked());
    VariableManager::instance().updateVar(Prefix + filterName + "algorithm", FilterJob->CurrentFilter);
}

void FilterWindow::LoadSetting()
{
    VariableManager::instance().Prefix = ProjectName;

    QString filterName = QString(".filter%1.").arg(ui->cbObjectType->currentText());
    QList<QVariant> hsvParas = VariableManager::instance().getVar(Prefix + filterName + "hsvV").toList();

    for (int i = 0; i < hsvParas.count(); i++)
    {
        sPara[i]->setValue(hsvParas.at(i).toInt());
        lbPara[i]->setText(QString::number(hsvParas.at(i).toInt()));
    }

    ui->hsThreshold->setValue(VariableManager::instance().getVar(Prefix + filterName + "thresV", 100).toInt());
    ui->lbThreshold->setText(QString::number(ui->hsThreshold->value()));

    ui->hsBlurSize->setValue(VariableManager::instance().getVar(Prefix + filterName + "blurV", 1).toInt());
    ui->lbBlurSize->setText(QString::number(ui->hsBlurSize->value()));

    ui->cbInvert->setChecked(VariableManager::instance().getVar(Prefix + filterName + "invert", false).toBool());

    FilterJob->CurrentFilter = VariableManager::instance().getVar(Prefix + filterName + "algorithm", FilterJob->CurrentFilter).toInt();
}

void FilterWindow::SetImage(cv::Mat mat)
{
    OriginMat.release();

    QMutex mux;
    mux.lock();
    OriginMat = mat.clone();
    mux.unlock();

    QPixmap pixmap = ImageTool::cvMatToQPixmap(mat);

    pixmap = pixmap.scaled(lbOriginImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->lbOriginImage->setPixmap(pixmap);

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
    blurSize = (blurSize / 2) * 2 + 1;

    ui->lbBlurSize->setText(QString::number(blurSize));

    SaveSetting();

    emit ColorFilterValueChanged(intParas);
    emit ColorInverted(ui->cbInvert->isChecked());
    emit BlurSizeChanged(blurSize);

    if (OriginMat.empty())
        return;

    emit requestFilter(OriginMat.clone(), intParas, ui->cbInvert->isChecked(), blurSize);
}
