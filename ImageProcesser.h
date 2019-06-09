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
#include <QInputDialog>
#include <qlabel.h>
#include <qtimer.h>
#include <qpushbutton.h>
#include "Blob.h"
#include "BlobManager.h"
#include "UnityTool.h"

#define RED_COLOR       cv::Scalar(0, 0, 255)
#define GREEN_COLOR     cv::Scalar(0, 255, 0)
#define BLUE_COLOR      cv::Scalar(255, 0, 0)
#define YELLOW_COLOR    cv::Scalar(0, 255, 255)
#define BLACK_COLOR    cv::Scalar(0, 0, 0)
#define WHITE_COLOR    cv::Scalar(255, 255, 255)

#define HSV_SPACE				0
#define THRESHOLD_SPACE			1
#define GRB_SPACE				2
#define LAB_SPACE				3
#define YCRCB_SPACE				4

#define ORIGIN				0
#define RESULT				1
#define PROCESSING			2

#define DEFAULT_PROCESSING_SIZE	500
#define DEFAULT_OBJECT_WIDTH	150
#define DEFAULT_OBJECT_HEIGHT	150
#define APPROXIMATE_RANGE		20

#define MIN_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH - APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT - APPROXIMATE_RANGE)
#define MAX_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH + APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT + APPROXIMATE_RANGE)

class ImageProcesser : public QWidget
{
	Q_OBJECT

public:
	ImageProcesser(QWidget *parent);
	~ImageProcesser();
	
	void SetDetectParameterPointer(QLineEdit* xRec, QLineEdit* yRec, QLineEdit* distance, QLineEdit* xCoor, QLineEdit* yCoor);
	void SetResultScreenPointer(QLabel* resultImage);
	void SetObjectScreenPointer(QLabel* objectImage);
	void SetFPSInputBox(QLineEdit* fps);

	void UpdateLabelImage(cv::Mat mat, QLabel* label);

	HSVWindow* ParameterPanel;
	BlobManager* ConvenyorObjectManager;

public slots:
	void LoadTestImage();
	void LoadCamera();
	void UpdateCameraScreen();
	void OpenParameterPanel();
	void SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV);
	void SetThreshold(int value);
	void GetObjectInfo(int x, int y, int h, int w);
	void GetProcessRegion(QPoint a, QPoint b, QPoint c, QPoint d);
	void GetDistance(int distance);
	void GetCalibPoint(int x, int y);
	void SwitchLayer();
	void changeAxisDirection();
private:

	void drawXAxis();
	void SelectProcessRegion(cv::Mat processMat);
	void postProcessing(cv::Mat processMat);
	void paintInfo(cv::Mat input, cv::Mat output, cv::Scalar color);
	void drawRotateRec(cv::Mat& mat, int angle, cv::Rect rec, cv::Scalar color);
	float drawMinRec(cv::Mat& mat, std::vector<cv::Point> contour, cv::Scalar color);

	bool isNotCollision(Blob currentBlob, std::vector<Blob> blobs);
	void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
	void updateAppearedBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
	void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
	double getDistance(cv::Point point1, cv::Point point2);
	int getObjectNumber(std::vector<Blob> &blobs);
	void drawCountedObjectDigit(int &carCount, cv::Mat &imgFrame2Copy);

	int HSVValue[6] = {0, 100, 0, 255, 0, 255};
	int thresholdValue = 100;
	int filterMethod = THRESHOLD_SPACE;
	int cameraLayer = RESULT;

	cv::Rect objectRec;
	int minObjectArea;
	int maxObjectArea;
	std::vector<cv::Point> processRegionPoints;
	float processAndRealRatio = 1;
	float displayAndProcessRatio = 1;
	float displayAndRealRatio = 1;
	int xRealCamOri = 0;
	int yRealCamOri = 0;
	int axisDirection = 1;
	QLine xAxis;
	QLine arrow1;
	QLine arrow2;
	
	QTimer* updateScreenTimer;
	cv::VideoCapture camera;
	cv::Mat captureImage;
	cv::Mat resizeImage;
	cv::Mat resultImage;

	QLabel* lbResultImage;
	QLabel* lbObjectImage;
	QLineEdit* leFPS;

	QLineEdit* leXRec;
	QLineEdit* leYRec;
	QLineEdit* leDistance;
	QLineEdit* leXCoor;
	QLineEdit* leYCoor;

	bool isDetectedNewObject = false;
	int countedObjectNumber = 0;
	bool isFirstFrame = true;

	std::vector<Blob> appearedBlobs;
	std::vector<Blob> currentFrameBlobs;
};
