#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QDialog>
#include <qslider.h>
#include <qlabel.h>
#include <QSettings>
#include <opencv2/opencv.hpp>
#include <ImageUnity.h>
#include <QThread>

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
    bool IsInvert = false;
    cv::Mat FilterResult;

public slots:
    void DoHSVFilter(cv::Mat mat, int minH, int maxH, int minS, int maxS, int minV, int maxV )
    {
        CurrentFilter = HSV;

        cv::Scalar minScalar(minH, minS, minV);
        cv::Scalar maxScalar(maxH, maxS, maxV);

        cv::cvtColor(mat, mat, CV_BGR2HSV);
        cv::inRange(mat, minScalar, maxScalar, mat);

        FilterResult = mat.clone();

        if (IsInvert == true)
        {
            cv::bitwise_not(mat, mat);
        }

        emit FinishedFilter(ImageTool::cvMatToQPixmap(mat));
    }
    void DoThresholdFilter(cv::Mat mat, int value)
    {
        CurrentFilter = THRESHOLD;

        cvtColor(mat, mat, CV_BGR2GRAY);
        cv::threshold(mat, mat, value, 255, CV_THRESH_BINARY);

        FilterResult = mat;

        if (IsInvert == true)
        {
            cv::bitwise_not(mat, mat);
        }

        emit FinishedFilter(ImageTool::cvMatToQPixmap(mat));
    }

    void InvertImage(bool value)
    {
        IsInvert = value;

        if (IsInvert == true)
        {
            cv::bitwise_not(FilterResult, FilterResult);
        }

        emit FinishedFilter(ImageTool::cvMatToQPixmap(FilterResult));
    }

signals:
    void FinishedFilter(QPixmap pixmap);
};

class FilterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = 0);
    ~FilterWindow();

	void InitEvents();
    void InitVariables();
    void SaveSetting(QString fileName);
    void SaveSetting(QSettings* setting);
    void LoadSetting(QString fileName);
    void LoadSetting(QSettings* setting);
    void SetImage(cv::Mat mat);

	QSlider *sPara[6];
	QLabel *lbPara[6];
	QLabel *lbOriginImage;
    QLabel *lbProcessImage;

	bool IsInvertBinary();

    cv::Mat OriginMat;
    FilterWork* FilterJob;

public slots:
    void UpdateSliderValueToLabel();
signals:
	void ValueChanged(int minH, int maxH, int minS, int maxS, int minV, int maxV);
    void ValueChanged(int threshold);

    void requestThresholdFilter(cv::Mat mat, int value);
    void requestHSVFilter(cv::Mat mat, int minH, int maxH, int minS, int maxS, int minV, int maxV );


private:
    Ui::FilterWindow *ui;
};

#endif // FILTERWINDOW_H
