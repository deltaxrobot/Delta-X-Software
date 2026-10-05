#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QDialog>
#include <qslider.h>
#include <qlabel.h>
#include <QSettings>
#include <opencv2/opencv.hpp>
#include <FilterWork.h>
#include <ImageUnity.h>
#include <QThread>
#include <VariableManager.h>
#include <QPushButton>

namespace Ui {
class FilterWindow;
}

class FilterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = 0, QString projectName = "project0");
    ~FilterWindow();

	void InitEvents();
    void InitVariables();
    void SaveSetting();
    void LoadSetting();
    void SetImage(cv::Mat mat);
    void RequestValue();

	QSlider *sPara[6];
	QLabel *lbPara[6];
	QLabel *lbOriginImage;
    QLabel *lbProcessImage;

	bool IsInvertBinary();

    cv::Mat OriginMat;
    FilterWork* FilterJob = nullptr;
    QThread* FilterThread = nullptr;
    QString ProjectName = "project0";

    QString Prefix = "detect0";

public slots:
    void ProcessValueFromUI();
signals:
    void ValueChanged(QList<int> paras, bool isInvert, int blurSize);
    void ColorFilterValueChanged(QList<int> values);
    void ColorInverted(bool isInvert);
    void BlurSizeChanged(int size);

    void requestFilter(cv::Mat mat, QList<int> paras, bool isInvert, int blurSize);

private:
    Ui::FilterWindow *ui;

    QList<int> intParas;
    int CurrentFilter = FilterWork::THRESHOLD;
};

#endif // FILTERWINDOW_H
