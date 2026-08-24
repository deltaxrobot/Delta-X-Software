#include "FilterWindow.h"
#include "ui_FilterWindow.h"

FilterWindow::FilterWindow(QWidget *parent, QString projectName)
    : QDialog(parent), ui(new Ui::FilterWindow)
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
    if (FilterThread && FilterThread->isRunning()) {
        FilterThread->quit();
        FilterThread->wait();
    }
    FilterJob = nullptr;

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

    FilterThread = new QThread(this);
    FilterJob = new FilterWork();
    FilterJob->moveToThread(FilterThread);
    connect(FilterThread, &QThread::finished, FilterJob, &QObject::deleteLater);
    FilterThread->start();
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

    connect(FilterJob, &FilterWork::FinishedFilter, this, [this](const cv::Mat& mat)
    {
        QPixmap pixmap = ImageTool::cvMatToQPixmap(mat);
        pixmap = pixmap.scaled(lbOriginImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->lbProcessImage->setPixmap(pixmap);
    });
    connect(FilterJob, &FilterWork::FilterFailed, this, [](const QString& message) {
        qWarning() << "Image filter failed:" << message;
    });
}

void FilterWindow::SaveSetting()
{
    QList<QVariant> hsvParas;

    for (int i = 0; i < 6; i++)
    {
        hsvParas.append(sPara[i]->value());
    }

    const QString filterName = QString("%1.filter%2.")
                                   .arg(Prefix, ui->cbObjectType->currentText());
    QHash<QString, QVariant> values;
    values.insert(filterName + "hsvV", hsvParas);
    values.insert(filterName + "thresV", ui->hsThreshold->value());
    values.insert(filterName + "blurV", ui->hsBlurSize->value());
    values.insert(filterName + "invert", ui->cbInvert->isChecked());
    values.insert(filterName + "algorithm", CurrentFilter);
    VariableManager::instance().updateBatchScoped(ProjectName, values);
}

void FilterWindow::LoadSetting()
{
    const QString filterName = QString("%1.filter%2.")
                                   .arg(Prefix, ui->cbObjectType->currentText());
    QList<QVariant> hsvParas = VariableManager::instance()
                                   .getVarScoped(ProjectName, filterName + "hsvV")
                                   .toList();

    const int hsvParameterCount = qMin(6, hsvParas.count());
    for (int i = 0; i < hsvParameterCount; i++)
    {
        sPara[i]->setValue(hsvParas.at(i).toInt());
        lbPara[i]->setText(QString::number(hsvParas.at(i).toInt()));
    }

    ui->hsThreshold->setValue(VariableManager::instance().getVarScoped(ProjectName, filterName + "thresV", 100).toInt());
    ui->lbThreshold->setText(QString::number(ui->hsThreshold->value()));

    ui->hsBlurSize->setValue(VariableManager::instance().getVarScoped(ProjectName, filterName + "blurV", 1).toInt());
    ui->lbBlurSize->setText(QString::number(ui->hsBlurSize->value()));

    ui->cbInvert->setChecked(VariableManager::instance().getVarScoped(ProjectName, filterName + "invert", false).toBool());

    CurrentFilter = VariableManager::instance()
                        .getVarScoped(ProjectName, filterName + "algorithm",
                                      CurrentFilter)
                        .toInt();
    if (CurrentFilter != FilterWork::THRESHOLD && CurrentFilter != FilterWork::HSV)
        CurrentFilter = FilterWork::THRESHOLD;
}

void FilterWindow::SetImage(cv::Mat mat)
{
    OriginMat = mat.clone();

    QPixmap pixmap = ImageTool::cvMatToQPixmap(mat);

    pixmap = pixmap.scaled(lbOriginImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->lbOriginImage->setPixmap(pixmap);

    RequestValue();
}

void FilterWindow::RequestValue()
{
    if (CurrentFilter == FilterWork::HSV)
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
        CurrentFilter = FilterWork::THRESHOLD;
        intParas.clear();

        int value = ui->hsThreshold->value();
        ui->lbThreshold->setText(QString::number(value));
        intParas.append(value);
    }
    else if (sender() != ui->hsBlurSize && sender() != ui->cbInvert)
    {
        CurrentFilter = FilterWork::HSV;
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
