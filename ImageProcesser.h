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
#include "BlobManager.h"
#include "UnityTool.h"
#include "CameraWidget.h"
#include "mainwindow.h"

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
#define TRANSFORM			3

#define DEFAULT_PROCESSING_SIZE	640
#define DEFAULT_OBJECT_WIDTH	150
#define DEFAULT_OBJECT_HEIGHT	150
#define APPROXIMATE_RANGE		20

#define MIN_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH - APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT - APPROXIMATE_RANGE)
#define MAX_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH + APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT + APPROXIMATE_RANGE)

#define X_AXIS_DOWN		2
#define X_AXIS_RIGHT	3
#define X_AXIS_UP		1

#define DEFAULT_FPS			10
#define DEFAULT_INTERVAL	1000/DEFAULT_FPS

#define CONVEYOR_TIMER_INTERVAL	100

class MainWindow;

class ImageProcesser : public QWidget
{
	Q_OBJECT

public:
	ImageProcesser(MainWindow *parent);
	~ImageProcesser();
	
	void SetDetectParameterPointer(QLineEdit* xRec, QLineEdit* yRec, QLineEdit* distance, QLineEdit* xCoor, QLineEdit* yCoor);
	void SetResultScreenPointer(CameraWidget* resultImage);
	void SetObjectScreenPointer(QLabel* objectImage);
	void SetFPSInputBox(QLineEdit* fps);
	void SetTrackingWidgetPointer(QLabel* lbTracking, QLabel* lbVisible);

	void UpdateLabelImage(cv::Mat mat, QLabel* label);

	void SetConvenyorVelocity(float val, QString dir);

	HSVWindow* ParameterPanel;
	BlobManager* ObjectManager;

	QTimer* ObjectMovingCalculaterTimer;

	int RunningCamera = -1;
	bool IsCameraPause = false;

	cv::VideoCapture* Camera;
	int CameraFPS = DEFAULT_FPS;
	int CameraTimerInterval = DEFAULT_INTERVAL;

	float ProcessAndRealRatio = 1;
	float DisplayAndProcessRatio = 1;
	float DisplayAndRealRatio = 1;

public slots:
	void LoadTestImage();
	void LoadCamera();
	void CaptureCamera();
	void PauseCamera();
	void ResumeCamera();
	void UpdateCameraScreen();
	void SaveFPS();
	void OpenParameterPanel();
	void SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV);
	void SetThreshold(int value);
	void GetObjectInfo(int x, int y, int l, int w);
	void GetObjectInfo(int l, int w);
	void GetProcessRegion(QPoint a, QPoint b, QPoint c, QPoint d);
	void GetCalibLine(QPoint p1, QPoint p2);
	void GetDistance(int distance);
	void GetCalibPoint(int x, int y);
	void SwitchLayer();
	void SelectLayer(int id);
	void changeAxisDirection();

	void UpdateObjectPositionOnConveyor();

signals:
	void ObjectValueChanged(std::vector<cv::RotatedRect> ObjectContainer);
private:
	void processImage();

	void drawXAxis();
	void SelectProcessRegion(cv::Mat processMat);
	void transformPerspective(cv::Mat processMat, std::vector<cv::Point> points, cv::Mat& transMat);
	void MakeBrightProcessRegion(cv::Mat resultsMat);
	void postProcessing(cv::Mat processMat);
	void detectObjects(cv::Mat input, cv::Mat output, cv::Scalar color);
	void drawRotateRec(cv::Mat& mat, int angle, cv::Rect rec, cv::Scalar color);
	float findObjectRectangle(cv::Mat& mat, std::vector<cv::Point> contour, cv::Scalar color);
	void UpdateTrackingInfo();
	void DisplayAdditionalInfo(cv:: Mat& displayMat);
	void drawBlackWhiteLine(cv::Mat& displayMat, cv::Point p1, cv::Point p2, int thin);
	void drawBlackWhiteLines(cv::Mat& displayMat, std::vector<cv::Point> points, int thin);

	float conveyorVel = 0;
	QString dirName = "X";

	int HSVValue[6] = {0, 100, 0, 255, 0, 255};
	int thresholdValue = 150;
	int filterMethod = THRESHOLD_SPACE;
	int cameraLayer = RESULT;

	cv::Rect objectRec;
	int minObjectArea;
	int maxObjectArea;
	std::vector<cv::Point> processRegionPoints;
	cv::Point calibLinePoint1;
	cv::Point calibLinePoint2;
	cv::Point calibPoint;
	
	int xRealCamOri = 0;
	int yRealCamOri = 0;
	int axisDirection = X_AXIS_UP;
	QLine xAxis;
	QLine arrow1;
	QLine arrow2;

	int xWidgetCalibPoint = 150;
	int yWidgetCalibPoint = 0;
	
	QTimer* updateScreenTimer;
	cv::Mat captureImage;
	cv::Mat resizeImage;
	cv::Mat resultImage;
	cv::Mat transformImage;

	CameraWidget* lbResultImage;
	QLabel* lbObjectImage;
	QLineEdit* leFPS;

	QLineEdit* leWRec = NULL;
	QLineEdit* leLRec = NULL;
	QLineEdit* leDistance = NULL;
	QLineEdit* leXCoor = NULL;
	QLineEdit* leYCoor = NULL;

	QLabel* lbTrackingObjectNumber;
	QLabel* lbVisibleObjectNumber;

	bool isDetectedNewObject = false;
	int countedObjectNumber = 0;
	bool isFirstFrame = true;

	bool isFirstLoad = true;
	bool isStopCapture = false;
	MainWindow* mParent;
};
