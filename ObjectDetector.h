#pragma once

#include <QObject>
#include <qwidget.h>
#include <FilterWindow.h>
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
#include <QCheckBox>
#include "ObjectManager.h"
#include "UnityTool.h"
#include "CameraWidget.h"
#include "RobotWindow.h"
#include <QToolButton>
#include <QRadioButton>
#include "opencv2/dnn.hpp"

#include <QThread>
#include <QTcpSocket>
#include <QProcess>
#include <QTcpServer>
#include "Encoder.h"
#include "ImageProcessing.h"

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
#define APPROXIMATE_RATIO		0.5f

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

class ObjectFilter
{
public:
    int HSVValue[6] = {0, 100, 0, 255, 0, 255};
    int ThresholdValue = 150;
    int FilterMethod = THRESHOLD_SPACE;

    cv::Rect PobjectRec;
    int MinObjectArea;
    int MaxObjectArea;
};

class ObjectDetector : public QWidget
{
	Q_OBJECT

public:
    ObjectDetector(RobotWindow *parent);
    ~ObjectDetector();
	
    // ---- Init UI pointer ----
    void SetObjectSizePointer(QLineEdit* wRec, QLineEdit* lRec, QLineEdit* hRec);//, QLineEdit* distance, QLineEdit* xCoor, QLineEdit* yCoor);
    void SetObjectErrorPointer(QLineEdit* objectErrorSize, QLineEdit* trackingError);
    void SetCalibLinePointer(QLineEdit* realityLine, QLineEdit* imageLine);
    void SetScaleRoateEnablePointer(QCheckBox* lineEnable);
    void SetRealityCalibPointPointer(QLineEdit* realityPoint1X, QLineEdit* realityPoint1Y, QLineEdit* realityPoint2X, QLineEdit* realityPoint2Y);
    void SetImageCalibPointPointer(QLineEdit* imagePoint1X, QLineEdit* imagePoint1Y, QLineEdit* imagePoint2X, QLineEdit* imagePoint2Y);
	void SetResultScreenPointer(CameraWidget* resultImage);
	void SetObjectScreenPointer(QLabel* objectImage);
    void SetCameraInfoWidget(QLineEdit* fps, QLabel* state, QToolButton* playBt, QToolButton* loadBt);
	void SetTrackingWidgetPointer(QLabel* lbTracking, QLabel* lbVisible);
    void SetResolutionWidget(QLineEdit* w, QLineEdit* h);
    void SetDisplayInfoWidget(QLabel* scale, QLabel* size);
    void SetChessboardWidget(QLineEdit* chessW, QLineEdit* chessH, QLineEdit* chesSquareSize, QLineEdit* chessPoints[4][2]);
    void SetXAngleWidget(QLineEdit* xAngle);
    void SetObjectFilterWidget(QRadioButton* blobFilter, QRadioButton* externalFilter, QRadioButton* circleFilter);
    void SetFilterParaWidget(QLineEdit* pythonUrl);

    // ---- Display Value ----
	void UpdateLabelImage(cv::Mat mat, QLabel* label);
	void SetConvenyorVelocity(float val, QString dir);

    void ProcessDisplayAfterReceivingObjectData();

    // ----- Encoder + Conveyor -----
    void UpdatePointPositionOnConveyor(QLineEdit* x, QLineEdit* y, float angle, float distance);
    void UpdatePointPositionOnConveyor(float& x, float& y, float angle, float distance);

    // Thread
//    VideoProcessor* VideoProcessorThread;

//    VideoDisplay* VideoDisplayThread;
    QTcpSocket* PythonTcpClient = NULL;

    QProcess *ExternalScriptProcess;

//    ImageProcessing* ImageProcessingThread;

    // ---- Table ----
	FilterWindow* ParameterPanel;
    ObjectManager* ObjectManager1;

    // ---- Timer ----
    QTimer* ObjectMovingCalculaterTimer;
    QTimer* ProcessingImageTimer;

    // ----- State ----
	int RunningCamera = -1;
	bool IsCameraPause = false;

    // ---- Camera ----
	cv::VideoCapture* Camera;

    float CameraFPS = DEFAULT_FPS;
    float CameraTimerInterval = DEFAULT_INTERVAL;

    QCheckBox* cbExternalCamera = NULL;
    QComboBox* cbImageSourceForExternal = NULL;

    // ---- Calculating ----
	QMatrix D2PMatrix;
	QMatrix P2RMatrix;
	QMatrix D2RMatrix;

    float DnPRatio = 1.0;
    float PnRRatio = 1.0;
    float DnRratio = 1.0;
    float CameraRatio = 4.0/3;
    int CameraWidgetHeight = 300;

    cv:: Mat PerspectiveTransformationMatrix;

	QScrollArea* CameraScrollArea;

    bool IsPerspectiveMode = false;
    bool IsCalibInfoVisible = true;

    // ---- Conveyor ----

    float ConveyorVel = 0;
    float LastEncoderPosition = 0;
    float EncoderPosition = 0;
    float MovingDistance = 0;
    QString DirName = "X";
    bool IsEncoderEnable = false;

    float DeviationAngle = 0;

    // ------- Encoder ---------
    float EncoderPositionAtCameraCapture = 0;

    Encoder* Encoder1 = NULL;

    // ---- Object ----
    QList<cv::RotatedRect> *DisplayObjects;
    std::vector<cv::Vec3f>  CircleObjects;

    float ObjectError = 0.5f;

    cv::Rect PobjectRec;
    int minObjectArea;
    int maxObjectArea;

    // ---- FLow Processing ----

    int TaskOrder = -1;

public slots:
    // ---- FLow Processing ----
    void TaskExecute();
    void UpdateTaskList();

    // ---- Camera ----
	void LoadTestImage();
    void LoadCamera2();
	void CaptureCamera();
    void GetImage(cv::Mat mat);
	void PauseCamera();
	void PlayCamera(bool state);
	void ResumeCamera();
    void UpdateEvent();
	void SaveFPS();
    void ProcessErrorCamera();

    // ----- Filter ----
	void OpenParameterPanel();
	void SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV);
	void SetThreshold(int value);
    void OpenExternalFilterScript();

    // ----- Tool ----
	void GetObjectInfo(int x, int y, int l, int w);
	void GetObjectInfo(int l, int w);
    void GetObjectError();
	void GetPerspectivePoints(QPoint a, QPoint b, QPoint c, QPoint d);
	void GetProcessArea(QRect processArea);
	void GetCalibLine(QPoint p1, QPoint p2);
	void GetDistance(int distance);
    //void GetCalibPoint(int x, int y);
    void GetCalibPoint(QPoint p1, QPoint p2);
    void GetMappingPoint(QPoint mappingPoint);
    void changeAxisDirection();
    void TurnTransformPerspective(bool isTurnOn);
    void FindChessboard();


    void UpdateCalibLine(int realLine, int imageLine);

    // ---- Display ----
	void SwitchLayer();
    void SelectLayer(int id);
	void TurnCalibDisplay(bool state);
	void ExpandCameraWidget(bool isExpand);
    void ChangeCameraWidgetHeight(QString valueS);
	void OpenCameraWindow();
	void CloseCameraWindow();

    void UpdateToCameraWidget();
    void UpdatePixmapToLabel(QLabel* lb, QPixmap pm);

    // ---- Calib ----
    void UpdateRatios(float w, float h);
    void UpdateRatios();
    void CalculateMappingMatrix();

    // ---- Tracking ----
    void UpdateObjectPositionOnConveyor(QPointF offset);

    // ---- Setting ----

    void SaveSetting(QString fileName);
    void SaveSetting(QSettings* setting);
    void LoadSetting(QString fileName);
    void LoadSetting(QSettings* setting);

    // ---- Detecting ----
    void GetExternalScriptSocket(QTcpSocket* socket);

signals:
	void ObjectValueChanged(std::vector<cv::RotatedRect> ObjectContainer);
    void openCamera(cv::VideoCapture* cam);
    void display(cv::Mat mat, QLabel* displayWidget);
    void display2(QLabel* displayWidget);

    void RequestGetImage(cv::Mat mat);
    void RequestResizeImage(cv::Mat mat);


private:
    // ---- Camera ----
    void stopCamera();

    // ---- Image Processing ----
    void SelectProcessRegion(cv::Mat processMat);
	void processImage();
    void transformPerspective(cv::Mat processMat, std::vector<cv::Point> points, cv::Mat& transMat);
    void calculatePerspectiveTransformMatrix(std::vector<cv::Point> points);
    cv::Point2f warpPerspective(cv::Point2f p, cv::Mat matrix);
    void MakeBrightProcessRegion(cv::Mat resultsMat);
    void postProcessing();
    void detectBlobObjects(cv::Mat input);
    void detectCircleObjects(cv::Mat input);
    void sendImageToExternalScript(cv::Mat input);
    float processDetectingObjectOnCamera(cv::Mat& mat, QList<cv::RotatedRect> objects, cv::Scalar color);

    // ---- Display ----    
    void DisplayAdditionalInfo(cv:: Mat& displayMat);
    void drawXAxis(cv::Mat resultsMat);
    void drawRotateRec(cv::Mat& mat, int angle, cv::Rect rec, cv::Scalar color);
	void drawBlackWhiteLine(cv::Mat& displayMat, cv::Point p1, cv::Point p2, int thin);
	void drawBlackWhiteLine(cv::Mat& displayMat, QLine line, int thin);
	void drawBlackWhiteLines(cv::Mat& displayMat, std::vector<cv::Point> points, int thin);
	void drawBlackWhiteRect(cv::Mat& displayMat, cv::Point p, cv::Size size);
	void drawBlackWhiteRect(cv::Mat& displayMat, QRect rect);
	void drawLine(cv::Mat& displayMat, QPoint p1, QPoint p2);
	void drawCorner(cv::Mat& displayMat, QPoint p);

    void updatePerspectivePointsToUI();

    // ---- Result Display ----
    void UpdateTrackingInfo();
    void UpdateDetectingResultToWidgets();

    // ---- Parameter ----
	int HSVValue[6] = {0, 100, 0, 255, 0, 255};
	int thresholdValue = 150;
	int filterMethod = THRESHOLD_SPACE;
    int cameraLayer = RESULT;

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
    int axisDirection = X_AXIS_RIGHT;
	QLine xAxis;
	QLine arrow1;
	QLine arrow2;	

    // ---- Display ----

	cv::Mat captureImage;
    cv::Mat calibImage;
    cv::Mat filterMat;
	cv::Mat resultImage;
	cv::Mat transformImage;

    // ----- Widget Pointer ----

    CameraWidget* cameraWidget;
	QLabel* lbObjectImage;
	QLineEdit* leFPS;
	QLabel* lbCameraState;
    QToolButton* pbPlayCammera;
    QToolButton* pbLoadCamera;
	QWidget* cameraWindow;
	QWidget* cameraLayout;
	QVBoxLayout * cameraBox;
    QLabel* lbScale;
    QLabel* lbImageSize;

    QLineEdit* leWidth;
    QLineEdit* leHeight;

	QLineEdit* leWRec = NULL;
	QLineEdit* leLRec = NULL;
    QLineEdit* leHRec = NULL;

    QLineEdit* leRealityLine = NULL;
    QLineEdit* leImageLine = NULL;

    QLineEdit* leObjectErrorSize;
    QLineEdit* leTrackingError;

    QLineEdit* leRealityPoint1X = NULL;
    QLineEdit* leRealityPoint1Y = NULL;
    QLineEdit* leRealityPoint2X = NULL;
    QLineEdit* leRealityPoint2Y = NULL;

    QLineEdit* leImagePoint1X = NULL;
    QLineEdit* leImagePoint1Y = NULL;
    QLineEdit* leImagePoint2X = NULL;
    QLineEdit* leImagePoint2Y = NULL;

    QCheckBox* cbScaleRotateToolEnable = NULL;

	QLabel* lbTrackingObjectNumber;
	QLabel* lbVisibleObjectNumber;

    QLineEdit* leChessboardWidth;
    QLineEdit* leChessboardHeight;
    QLineEdit* leChessboardSquareSize;
    QLineEdit* (*leChessboardPoints)[2];

    QLineEdit* leXAxisAngle;

    QRadioButton* rbBlobFilter;
    QRadioButton* rbExternalFilter;
    QRadioButton* rbCircleFilter;
    QLineEdit* lePythonUrl;

    // ---- Configuration ----

	bool isDetectedNewObject = false;
	int countedObjectNumber = 0;
    bool isFirstFrame = true;

	bool isFirstLoad = true;
    bool isFirstRead = true;
	bool isStopCapture = false;

    // ---- Relation ----
	RobotWindow* mParent;
};
