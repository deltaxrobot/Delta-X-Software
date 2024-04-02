#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QDialog>
#include <qslider.h>
#include <qlabel.h>
#include <QSettings>
#include <opencv2/opencv.hpp>
#include <ImageUnity.h>
#include <QThread>
#include <QMutexLocker>
#include <VariableManager.h>
#include <QPushButton>

namespace Ui {
class FilterWindow;
}

class FilterWork : public QObject
{
    Q_OBJECT

public:
    FilterWork()
    {

    }
    ~FilterWork()
    {

    }

    enum
    {
        THRESHOLD = 0,
        HSV
    };

    int CurrentFilter = THRESHOLD;
    QList<int> Paras;
    bool IsInvert = false;
    int BlurSize = 1;
    cv::Mat FilterResult;

public slots:
    void DoFilter(cv::Mat mat, QList<int> paras, bool isInvert, int blurSize)
    {
        Paras = paras;

        if (paras.size() == 1)
        {
            CurrentFilter = THRESHOLD;

            cvtColor(mat, mat, CV_BGR2GRAY);
            cv::threshold(mat, mat, paras.at(0), 255, CV_THRESH_BINARY);
        }
        else if (paras.size() == 6)
        {
            CurrentFilter = HSV;

            cv::Scalar minScalar(paras.at(0), paras.at(2), paras.at(4));
            cv::Scalar maxScalar(paras.at(1), paras.at(3), paras.at(5));

            cv::cvtColor(mat, mat, CV_BGR2HSV);
            cv::inRange(mat, minScalar, maxScalar, mat);
        }

        IsInvert = isInvert;

        if (isInvert == true)
        {
            cv::bitwise_not(mat, mat);
        }

        BlurSize = blurSize;

        cv::medianBlur(mat, mat, BlurSize);

        emit FinishedFilter(mat);
    }

signals:
    void FinishedFilter(cv::Mat);
};

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
    FilterWork* FilterJob;
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

    QList<int> intParas;};

#endif // FILTERWINDOW_H
