#pragma once

#include <QObject>
#include <qwidget.h>
#include <hsvwindow.h>
#include <qfiledialog.h>
#include <qscrollarea.h>
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
#include "RobotWindow.h"
#include <QToolButton>
#include "opencv2/dnn.hpp"

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

#define ORIGIN				2
#define RESULT				0
#define PROCESSING			1

#define DEFAULT_PROCESSING_SIZE	640
#define DEFAULT_OBJECT_WIDTH	150
#define DEFAULT_OBJECT_HEIGHT	150
#define APPROXIMATE_RANGE		20
#define APPROXIMATE_RATIO		0.4f

#define MIN_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH - APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT - APPROXIMATE_RANGE)
#define MAX_OBJECT_AREA			(DEFAULT_OBJECT_WIDTH + APPROXIMATE_RANGE)*(DEFAULT_OBJECT_HEIGHT + APPROXIMATE_RANGE)

#define X_AXIS_DOWN		2
#define X_AXIS_RIGHT	3
#define X_AXIS_UP		1
#define X_AXIS_LEFT		4

#define DEFAULT_FPS			15
#define DEFAULT_INTERVAL	1000/DEFAULT_FPS

#define CONVEYOR_TIMER_INTERVAL	100

class RobotWindow;

class ImageProcesser : public QWidget
{
	Q_OBJECT

public:
	ImageProcesser(RobotWindow *parent);
	~ImageProcesser();
	
    void SetDetectParameterPointer(QLineEdit* wRec, QLineEdit* lRec, QLineEdit* distance, QLineEdit* xCoor, QLineEdit* yCoor);
	void SetResultScreenPointer(CameraWidget* resultImage);
	void SetObjectScreenPointer(QLabel* objectImage);
    void SetCameraInfoWidget(QLineEdit* fps, QLabel* state, QToolButton* playBt, QToolButton* loadBt);
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

	QMatrix D2PMatrix;
	QMatrix P2RMatrix;
	QMatrix D2RMatrix;

	float DnPRatio;
	float PnRRatio;
	float DnRratio;
	float CameraRatio;

	QScrollArea* CameraScrollArea;

    QElapsedTimer TimerTool;

    float ConveyorVel = 0;
    float LastEncoderPosition = 0;
    float EncoderPosition = 0;
    QString DirName = "X";

    bool IsEncoderEnable = false;

public slots:
	void LoadTestImage();
	void LoadCamera();
	void CaptureCamera();
	void PauseCamera();
	void PlayCamera(bool state);
	void ResumeCamera();
	void UpdateCameraScreen();
	void SaveFPS();
	void OpenParameterPanel();
	void SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV);
	void SetThreshold(int value);
	void GetObjectInfo(int x, int y, int l, int w);
	void GetObjectInfo(int l, int w);
	void GetPerspectivePoints(QPoint a, QPoint b, QPoint c, QPoint d);
	void GetProcessArea(QRect processArea);
	void GetCalibLine(QPoint p1, QPoint p2);
	void GetDistance(int distance);
    void GetCalibPoint(int x, int y);
	void SwitchLayer();
	void SelectLayer(int id);
	void changeAxisDirection();
	void TurnTransformPerspective(bool isTurnOn);
	void TurnCalibDisplay(bool state);
	void ExpandCameraWidget(bool isExpand);
	void OpenCameraWindow();
	void CloseCameraWindow();
	void UpdateRatios();

	void UpdateObjectPositionOnConveyor();

    void EncoderEnabled(bool status);

    void SaveSetting(QString fileName);
    void LoadSetting(QString fileName);
signals:
	void ObjectValueChanged(std::vector<cv::RotatedRect> ObjectContainer);
private:
	void stopCamera();

	void processImage();

	void drawXAxis(cv::Mat resultsMat);
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
	void drawBlackWhiteLine(cv::Mat& displayMat, QLine line, int thin);
	void drawBlackWhiteLines(cv::Mat& displayMat, std::vector<cv::Point> points, int thin);
	void drawBlackWhiteRect(cv::Mat& displayMat, cv::Point p, cv::Size size);
	void drawBlackWhiteRect(cv::Mat& displayMat, QRect rect);
	void drawLine(cv::Mat& displayMat, QPoint p1, QPoint p2);
	void drawCorner(cv::Mat& displayMat, QPoint p);

	int HSVValue[6] = {0, 100, 0, 255, 0, 255};
	int thresholdValue = 150;
	int filterMethod = THRESHOLD_SPACE;
	int cameraLayer = RESULT;

	cv::Rect PobjectRec;
	int minObjectArea;
	int maxObjectArea;

	std::vector<cv::Point> PperspectivePoints;
	cv::Rect PselectedRectangle;
	cv::Point PcalibLinePoint1;
	cv::Point PcalibLinePoint2;	
	cv::Point PcalibPoint;
	cv::Rect Pobject;

	QLine DcalibLine;
	QPoint DcalibPoint;
	QRect DselectedRec;
	QPoint DperspectivePoints[4];
	QRect Dobject;
	
	int xRealCamOri = 0;
	int yRealCamOri = 0;
	int axisDirection = X_AXIS_LEFT;
	QLine xAxis;
	QLine arrow1;
	QLine arrow2;
	
	QTimer* updateScreenTimer;
	cv::Mat captureImage;
	cv::Mat resizeImage;
	cv::Mat resultImage;
	cv::Mat transformImage;

	CameraWidget* lbResultImage;
	QLabel* lbObjectImage;
	QLineEdit* leFPS;
	QLabel* lbCameraState;
    QToolButton* pbPlayCammera;
    QToolButton* pbLoadCamera;
	QWidget* cameraWindow;
	QWidget* cameraLayout;
	QVBoxLayout * cameraBox;

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
	bool isPerspectiveMode = false;
	bool isCalibInfoVisible = true;

	bool isFirstLoad = true;
	bool isStopCapture = false;
	RobotWindow* mParent;
};
