#pragma once

#include <QObject>
#include <qwidget.h>
#include <hsvwindow.h>
#include <qfiledialog.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>
#include <string>

#define RED_COLOR       cv::Scalar(0, 0, 255)
#define GREEN_COLOR     cv::Scalar(0, 255, 0)
#define BLUE_COLOR      cv::Scalar(255, 0, 0)
#define YELLOW_COLOR    cv::Scalar(0, 255, 255)

class ImageProcesser : public QWidget
{
	Q_OBJECT

public:
	ImageProcesser(QWidget *parent);
	~ImageProcesser();

	void SetProcessScreenPointer(QLabel* testImage);
	void SetResultScreenPointer(QLabel* resultImage);

	HSVWindow* HSVPanel;

public slots:
	void LoadTestImage();
	void OpenHSVPanel();
	void SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV);
	void SetThreshold(int value);
private:
	void updateProcessScreen(cv::Mat bgrMat);
	void updateResultScreen(cv::Mat bgrMat);
	void paintInfo(cv::Mat input, cv::Mat output, cv::Scalar color);
	void drawRotateRec(cv::Mat& mat, int angle, cv::Rect rec, cv::Scalar color);
	float drawMinRec(cv::Mat& mat, std::vector<cv::Point> contour, cv::Scalar color);
	cv::Mat processImageBGR;
	cv::Mat resultImageBGR;
	QLabel* lbProcessImage;
	QLabel* lbResultImage;
};
