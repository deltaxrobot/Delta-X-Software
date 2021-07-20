#include "ImageProcesser.h"

ImageProcesser::ImageProcesser(RobotWindow *parent)
	: QWidget(parent)
{
	ParameterPanel = new HSVWindow(parent);
	connect(ParameterPanel, SIGNAL(ValueChanged(int, int, int, int, int, int)), this, SLOT(SetHSV(int, int, int, int, int, int)));
	connect(ParameterPanel, SIGNAL(ValueChanged(int)), this, SLOT(SetThreshold(int)));

	mParent = parent;

	Camera = new cv::VideoCapture();	

	updateScreenTimer = new QTimer(this);
	connect(updateScreenTimer, SIGNAL(timeout()), this, SLOT(UpdateCameraScreen()));
	updateScreenTimer->start(CameraTimerInterval);

	PobjectRec.width = DEFAULT_OBJECT_WIDTH;
	PobjectRec.height = DEFAULT_OBJECT_HEIGHT;
	minObjectArea = MIN_OBJECT_AREA;
	maxObjectArea = MAX_OBJECT_AREA;

	changeAxisDirection();

	ObjectManager = new BlobManager(parent);

	ObjectMovingCalculaterTimer = new QTimer(this);
    connect(ObjectMovingCalculaterTimer, SIGNAL(timeout()), this, SLOT(UpdateObjectPositionOnConveyor()));
    ObjectMovingCalculaterTimer->start(CONVEYOR_TIMER_INTERVAL);

	TimerTool.start();

	cameraWindow = new QWidget();
	cameraWindow->setWindowTitle("Camera Window");
	cameraWindow->setWindowFlags(Qt::WindowStaysOnTopHint);
}

ImageProcesser::~ImageProcesser()
{

}

void ImageProcesser::LoadTestImage()
{
	QString imageName;
	imageName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

	if (imageName == "")
		return;

	cv::String imgName = imageName.toStdString();
	captureImage = cv::imread(imgName, cv::IMREAD_COLOR);
	processImage();
}

void ImageProcesser::LoadCamera()
{
    QToolButton* loadBt = qobject_cast<QToolButton*>(sender());
	if (loadBt->isChecked())
	{        
        QStringList cameraItems;

        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        for (int i = 0; i < cameras.size(); i++)
        {
            cameraItems.append(QString::number(i) + QString(" - ") + cameras[i].description());
        }

		bool ok;
        QString text = QInputDialog::getItem(this, tr("Open Camera"), tr("Camera ID: "), cameraItems, 0, false, &ok);

		if (ok && !text.isEmpty())
		{
            QString cameraIDText = text.mid(0, text.indexOf(" - "));
            int cameraID = cameraIDText.toInt();
            RunningCamera = cameraID;

			lbCameraState->setEnabled(true);
			pbPlayCammera->setChecked(true);
			lbResultImage->InitParameter();

            loadBt->setText("Stop Camera");

            bool isCameraUsingByOtherRobot = false;

            if (mParent->RobotManagerPointer != NULL)
            {
                if (mParent->RobotManagerPointer->RobotWindows.size() > 0)
                {
                    for (int i = 0; i < mParent->RobotManagerPointer->RobotWindows.size(); i++)
                    {
                        if (mParent == mParent->RobotManagerPointer->RobotWindows.at(i))
                            continue;

                        if (mParent->RobotManagerPointer->RobotWindows.at(i)->DeltaImageProcesser->RunningCamera == RunningCamera)
                        {
                            Camera = mParent->RobotManagerPointer->RobotWindows.at(i)->DeltaImageProcesser->Camera;

                            isCameraUsingByOtherRobot = true;
                        }
                    }
                }
            }

            if (isCameraUsingByOtherRobot == false)
            {
                Camera->open(cameraID);
                Camera->set(cv::CAP_PROP_FRAME_WIDTH, 800);
                Camera->set(cv::CAP_PROP_FRAME_HEIGHT, 600);
            }

			UpdateRatios();

			IsCameraPause = false;
		}
		else
		{			
			loadBt->setChecked(false);
			IsCameraPause = false;
			RunningCamera = -1;
		}
	}
	else
	{
		stopCamera();
		return;
	}
}

void ImageProcesser::CaptureCamera()
{
	if (!Camera->isOpened())
		return;	

    if (!Camera->read(captureImage))
	{
		stopCamera();
        QMessageBox::information(this, "Problem", "The camera has lost connection!");
		return;
    }

    processImage();
}

void ImageProcesser::PauseCamera()
{
	IsCameraPause = true;
	pbPlayCammera->setChecked(false);
}

void ImageProcesser::PlayCamera(bool state)
{
	if (state == true)
	{
		ResumeCamera();
	}
	else
	{
		PauseCamera();
	}
}

void ImageProcesser::ResumeCamera()
{
	IsCameraPause = false;
	pbPlayCammera->setChecked(true);
}

void ImageProcesser::stopCamera()
{
	lbCameraState->setEnabled(false);
	Camera->release();
	RunningCamera = -1;
	IsCameraPause = false;
    pbLoadCamera->setText("Load Camera");
}

void ImageProcesser::processImage()
{
	if (lbResultImage->pixmap() != nullptr && isFirstLoad == true)
	{
		lbResultImage->InitParameter();
		isFirstLoad = false;
	}

	if (!captureImage.data)
	{
		return;
	}
	
	//cv::resize(captureImage, resizeImage, cv::Size(lbResultImage->width(), lbResultImage->height()));
	resizeImage = captureImage.clone();

	if (isPerspectiveMode == true)
	{
		transformPerspective(resizeImage, PperspectivePoints, resizeImage);
	}

	if (filterMethod == HSV_SPACE)
	{
		SetHSV(HSVValue[0], HSVValue[1], HSVValue[2], HSVValue[3], HSVValue[4], HSVValue[5]);
	}

	if (filterMethod == THRESHOLD_SPACE)
	{
		SetThreshold(thresholdValue);
	}
}

void ImageProcesser::UpdateCameraScreen()
{
	if (IsCameraPause == false)
	{
		CaptureCamera();        
    }

    if (IsEncoderEnable == false)
    {
        UpdateObjectPositionOnConveyor();
    }

	if (!cameraWindow->isVisible() && lbResultImage->parentWidget() == cameraWindow)
	{
		CloseCameraWindow();
	}
}

void ImageProcesser::SaveFPS()
{
	CameraFPS = leFPS->text().toInt();
	CameraTimerInterval = 1000 / CameraFPS;

	if (CameraFPS > 0)
		updateScreenTimer->setInterval(CameraTimerInterval);
}

void ImageProcesser::SetDetectParameterPointer(QLineEdit * wRec, QLineEdit * lRec, QLineEdit * distance, QLineEdit * xCoor, QLineEdit * yCoor)
{
    leWRec = wRec;
    leLRec = lRec;
	leDistance = distance;
	leXCoor = xCoor;
	leYCoor = yCoor;
}

void ImageProcesser::SetResultScreenPointer(CameraWidget * resultImage)
{
	lbResultImage = resultImage;
	cameraLayout = lbResultImage->parentWidget();
	cameraBox = new QVBoxLayout(cameraLayout);
	cameraBox->setMargin(0);
	cameraBox->addWidget(lbResultImage);
}

void ImageProcesser::SetObjectScreenPointer(QLabel * objectImage)
{
	lbObjectImage = objectImage;
}

void ImageProcesser::SetCameraInfoWidget(QLineEdit* fps, QLabel* state, QToolButton* playBt, QToolButton* loadBt = NULL)
{
	pbPlayCammera = playBt;
	leFPS = fps;
	lbCameraState = state;
    pbLoadCamera = loadBt;
}

void ImageProcesser::SetTrackingWidgetPointer(QLabel* lbTracking, QLabel* lbVisible)
{
	lbTrackingObjectNumber = lbTracking;
	lbVisibleObjectNumber = lbVisible;
}

void ImageProcesser::SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV)
{
	// Make binary image
	HSVValue[0] = minH;
	HSVValue[1] = maxH;
	HSVValue[2] = minS;
	HSVValue[3] = maxS;
	HSVValue[4] = minV;
	HSVValue[5] = maxV;

	filterMethod = HSV_SPACE;

	if (resizeImage.empty())
		return;

	cv::Mat processMat = resizeImage.clone();

	cvtColor(processMat, processMat, CV_BGR2HSV);

	cv::Scalar minScalar(minH, minS, minV);
	cv::Scalar maxScalar(maxH, maxS, maxV);

	cv::inRange(processMat, minScalar, maxScalar, processMat);


	//----------------------
	postProcessing(processMat);
}

void ImageProcesser::SetThreshold(int value)
{
	// Make binary image
	thresholdValue = value;

	filterMethod = THRESHOLD_SPACE;

	if (resizeImage.empty())
		return;

	cv::Mat processMat = resizeImage.clone();

	cvtColor(resizeImage, processMat, CV_BGR2GRAY);

	cv::threshold(processMat, processMat, value, 255, CV_THRESH_BINARY);

	//-----------------
	postProcessing(processMat);
}

void ImageProcesser::GetObjectInfo(int x, int y, int l, int w)
{
	Dobject.setX(x);
	Dobject.setY(y);
	Dobject.setHeight(l);
	Dobject.setWidth(w);

	PobjectRec.x = x / DnPRatio;
	PobjectRec.y = y / DnPRatio;

	GetObjectInfo(l, w);
	
	leWRec->setText(QString::number((int)(w / DnRratio)));
	leLRec->setText(QString::number((int)(l / DnRratio)));
}

void ImageProcesser::GetObjectInfo(int l, int w)
{
	if (lbResultImage->pixmap() == NULL)
		return;

	Dobject.setHeight(l);
	Dobject.setWidth(w);
	// Update information about the object to be identified
	
	PobjectRec.width = w / DnPRatio;
	PobjectRec.height = l / DnPRatio;

	minObjectArea = (PobjectRec.width * ( 1.0 - APPROXIMATE_RATIO)) * (PobjectRec.height * (1.0 - APPROXIMATE_RATIO));
	maxObjectArea = (PobjectRec.width * (1.0 + APPROXIMATE_RATIO)) * (PobjectRec.height + (1.0 + APPROXIMATE_RATIO));

	//ObjectManager->SetApproximateValue(cv::Point3d((float)l * 0.8f, (float)w * 0.8f, 60));

	//Display ROI is cut from widget
	QPixmap regionPixmap = lbResultImage->pixmap()->copy(Dobject.x(), Dobject.y(), w, l);

	if (w > l)
		regionPixmap = regionPixmap.scaledToWidth(lbObjectImage->width());
	else
		regionPixmap = regionPixmap.scaledToHeight(lbObjectImage->height());

	lbObjectImage->setPixmap(regionPixmap);
}

void ImageProcesser::GetPerspectivePoints(QPoint a, QPoint b, QPoint c, QPoint d)
{
	DperspectivePoints[0] = a;
	DperspectivePoints[1] = b;
	DperspectivePoints[2] = c;
	DperspectivePoints[3] = d;

	PperspectivePoints.clear();
	PperspectivePoints.push_back(cv::Point(a.x(), a.y()) / DnPRatio);
	PperspectivePoints.push_back(cv::Point(b.x(), b.y()) / DnPRatio);
	PperspectivePoints.push_back(cv::Point(c.x(), c.y()) / DnPRatio);
	PperspectivePoints.push_back(cv::Point(d.x(), d.y()) / DnPRatio);
}

void ImageProcesser::GetProcessArea(QRect processArea)
{
	DselectedRec = processArea;

	PselectedRectangle.width = processArea.width() / DnPRatio;
	PselectedRectangle.height = processArea.height() / DnPRatio;
	PselectedRectangle.x = processArea.x() / DnPRatio;
	PselectedRectangle.y = processArea.y() / DnPRatio;
}

void ImageProcesser::GetCalibLine(QPoint p1, QPoint p2)
{
	DcalibLine.setP1(p1);
	DcalibLine.setP2(p2);

	PcalibLinePoint1 = cv::Point(p1.x() / DnPRatio, p1.y() / DnPRatio);
	PcalibLinePoint2 = cv::Point(p2.x() / DnPRatio, p2.y()) / DnPRatio;
}

void ImageProcesser::GetDistance(int distance)
{
	float realDistance = leDistance->text().toFloat();

	float processDistance = (float)distance / DnPRatio;
	PnRRatio = processDistance / realDistance;
	DnRratio = (float)distance / realDistance;
}

void ImageProcesser::GetCalibPoint(int x, int y)
{
	DcalibPoint.setX(x);
	DcalibPoint.setY(y);

	if (resizeImage.cols > 0)
	{
		PcalibPoint.x = x / DnPRatio;
		PcalibPoint.y = y / DnPRatio;
	}

	if (leXCoor == NULL)
		return;

	float xRealCalibPoint = leXCoor->text().toFloat();
	float yRealCalibPoint = leYCoor->text().toFloat();

	float theta = 0;

	if (axisDirection == X_AXIS_DOWN)
	{
		/*xRealCamOri = xRealCalibPoint - y / DnRratio;
		yRealCamOri = yRealCalibPoint - x / DnRratio;*/

		theta = -M_PI_2;
	}
	else if (axisDirection == X_AXIS_RIGHT)
	{
		/*xRealCamOri = -xRealCalibPoint + x / DnRratio;
		yRealCamOri = yRealCalibPoint + y / DnRratio;*/

		theta = 0;
	}

	else if (axisDirection == X_AXIS_LEFT)
	{
		/*xRealCamOri = -xRealCalibPoint - x / DnRratio;
		yRealCamOri = yRealCalibPoint - y / DnRratio;*/

		theta = M_PI;
	}

	else if (axisDirection == X_AXIS_UP)
	{
		/*xRealCamOri = xRealCalibPoint + y / DnRratio;
		yRealCamOri = yRealCalibPoint + x / DnRratio;*/

		theta = M_PI_2;
	}

	//  ScaleMatrix * RotateMatrix * TranslateMatrix * PPoint = RPoint
	
	QMatrix RotateMatrix(qCos(theta), -qSin(theta), qSin(theta), qCos(theta), 0, 0);
	QMatrix ScaleMatrix(1.0f / PnRRatio, 0, 0, -1.0f / PnRRatio, 0, 0);	

	QMatrix ScaleRotateMatrix = ScaleMatrix * RotateMatrix;

	// x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
	// y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

	float dx = xRealCalibPoint - (ScaleRotateMatrix.m11() * (x / DnPRatio) + ScaleRotateMatrix.m21() * (y / DnPRatio));
	float dy = yRealCalibPoint - (ScaleRotateMatrix.m12() * (x / DnPRatio) + ScaleRotateMatrix.m22() * (y / DnPRatio));

	P2RMatrix.setMatrix(ScaleRotateMatrix.m11(), ScaleRotateMatrix.m12(), ScaleRotateMatrix.m21(), ScaleRotateMatrix.m22(), dx, dy);
	
	QPoint result = P2RMatrix.map(QPoint(x / DnPRatio, y / DnPRatio));
}

void ImageProcesser::SwitchLayer()
{
	cameraLayer++;
	if (cameraLayer > 2)
	{
		cameraLayer = 0;
	}
}

void ImageProcesser::SelectLayer(int id)
{
	cameraLayer = id;
}

void ImageProcesser::changeAxisDirection()
{
	if (axisDirection == X_AXIS_LEFT)
	{
		if (leXCoor != NULL)
		{
			int newX = leYCoor->text().toInt();
			int newY = 0 - leXCoor->text().toInt();
			leXCoor->setText(QString::number(newX));
			leYCoor->setText(QString::number(newY));
		}		

		axisDirection = X_AXIS_DOWN;
		xAxis.setP1(QPoint(10, 10));
		xAxis.setP2(QPoint(10, 40));
		arrow1.setP1(QPoint(15, 35));
		arrow1.setP2(QPoint(10, 40));
		arrow2.setP1(QPoint(5, 35));
		arrow2.setP2(QPoint(10, 40));
	}
	else if (axisDirection == X_AXIS_DOWN)
	{
		if (leXCoor != NULL)
		{
			int newX = leYCoor->text().toInt();
			int newY = 0 - leXCoor->text().toInt();
			leXCoor->setText(QString::number(newX));
			leYCoor->setText(QString::number(newY));
		}
		axisDirection = X_AXIS_RIGHT;
		xAxis.setP1(QPoint(10, 10));
		xAxis.setP2(QPoint(40, 10));
		arrow1.setP1(QPoint(30, 15));
		arrow1.setP2(QPoint(40, 10));
		arrow2.setP1(QPoint(30, 5));
		arrow2.setP2(QPoint(40, 10));
	}
	else if (axisDirection == X_AXIS_RIGHT)
	{
		if (leXCoor != NULL)
		{
			int newX = leYCoor->text().toInt();
			int newY = 0 - leXCoor->text().toInt();
			leXCoor->setText(QString::number(newX));
			leYCoor->setText(QString::number(newY));
		}

		axisDirection = X_AXIS_UP;
		xAxis.setP1(QPoint(10, 40));
		xAxis.setP2(QPoint(10, 10));
		arrow1.setP1(QPoint(15, 20));
		arrow1.setP2(QPoint(10, 10));
		arrow2.setP1(QPoint(5, 20));
		arrow2.setP2(QPoint(10, 10));
	}
	else if (axisDirection == X_AXIS_UP)
	{
		if (leXCoor != NULL)
		{
			int newX = leYCoor->text().toInt();
			int newY = 0 - leXCoor->text().toInt();
			leXCoor->setText(QString::number(newX));
			leYCoor->setText(QString::number(newY));
		}

		axisDirection = X_AXIS_LEFT;
		xAxis.setP1(QPoint(10, 10));
		xAxis.setP2(QPoint(40, 10));
		arrow1.setP1(QPoint(20, 15));
		arrow1.setP2(QPoint(10, 10));
		arrow2.setP1(QPoint(20, 5));
		arrow2.setP2(QPoint(10, 10));
	}

	GetCalibPoint(DcalibPoint.x(), DcalibPoint.y());
}

void ImageProcesser::TurnTransformPerspective(bool isTurnOn)
{
	isPerspectiveMode = isTurnOn;
	lbResultImage->IsPerspectiveEnable = isTurnOn;
}

void ImageProcesser::TurnCalibDisplay(bool state)
{
	isCalibInfoVisible = state;
	lbResultImage->IsMeasureDisplayEnable = state;
}

void ImageProcesser::ExpandCameraWidget(bool isExpand)
{
	if (isExpand == true)
	{
		lbResultImage->ChangeSize(800, 600);
	}
	else
	{
		lbResultImage->ChangeSize(400, 300);
	}
}

void ImageProcesser::OpenCameraWindow()
{
	lbResultImage->setParent(cameraWindow);
	cameraWindow->show();

	lbResultImage->ChangeSize(800, 600);
}

void ImageProcesser::CloseCameraWindow()
{
	cameraBox->addWidget(lbResultImage);
	lbResultImage->ChangeSize(400, 300);
}

void ImageProcesser::UpdateObjectPositionOnConveyor()
{
    float distance = 0;

    if (IsEncoderEnable == false)
    {
        distance = ConveyorVel * ((float)CONVEYOR_TIMER_INTERVAL / 1000);
    }
    else
    {
        distance = EncoderPosition - LastEncoderPosition;
    }

    if (DirName.toLower() == "x")
	{
		ObjectManager->UpdateNewPositionObjects(distance, 0);
	}
	else
	{
		ObjectManager->UpdateNewPositionObjects(0, distance);
	}

	emit ObjectValueChanged(ObjectManager->ObjectContainer);

	//Debug(QString::number((distance)));

}

void ImageProcesser::EncoderEnabled(bool status)
{
    IsEncoderEnable = status;
}

void ImageProcesser::SaveSetting(QString fileName)
{
    ParameterPanel->SaveSetting(fileName);

    QSettings settings(fileName, QSettings::IniFormat);

    settings.setValue("ObjectWidth", PobjectRec.width);
    settings.setValue("ObjectHeight", PobjectRec.height);
    settings.setValue("MinObjectArea", minObjectArea);
    settings.setValue("MaxObjectArea", maxObjectArea);
}

void ImageProcesser::LoadSetting(QString fileName)
{
    ParameterPanel->LoadSetting(fileName);

    QSettings settings(fileName, QSettings::IniFormat);

    PobjectRec.width = settings.value("ObjectWidth", PobjectRec.width).toInt();
    PobjectRec.height = settings.value("ObjectHeight", PobjectRec.height).toInt();
    minObjectArea = settings.value("MinObjectArea", minObjectArea).toInt();
    maxObjectArea = settings.value("MaxObjectArea", maxObjectArea).toInt();
}

void ImageProcesser::OpenParameterPanel()
{	
	ParameterPanel->exec();
}

void ImageProcesser::UpdateLabelImage(cv::Mat mat, QLabel* label)
{
	QImage img = ImageTool::cvMatToQImage(mat);
	label->setPixmap(QPixmap::fromImage(img).scaledToWidth(label->size().width()));
}

void ImageProcesser::SetConvenyorVelocity(float val, QString dir)
{
    ConveyorVel = val;
    DirName = dir;
}

void ImageProcesser::drawXAxis(cv::Mat resultsMat)
{
	drawBlackWhiteLine(resultsMat, cv::Point(xAxis.p1().x(), xAxis.p1().y()), cv::Point(xAxis.p2().x(), xAxis.p2().y()), 1);
	drawBlackWhiteLine(resultsMat, cv::Point(arrow1.p1().x(), arrow1.p1().y()), cv::Point(arrow1.p2().x(), arrow1.p2().y()), 1);
	drawBlackWhiteLine(resultsMat, cv::Point(arrow2.p1().x(), arrow2.p1().y()), cv::Point(arrow2.p2().x(), arrow2.p2().y()), 1);
	
	if (axisDirection == X_AXIS_DOWN)
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() - 10, xAxis.p2().y() + 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() - 11, xAxis.p2().y() + 21), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else if (axisDirection == X_AXIS_RIGHT)
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 20, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 21, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else if (axisDirection == X_AXIS_LEFT)
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 20, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 21, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 10, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 11, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
}

void ImageProcesser::SelectProcessRegion(cv::Mat processMat)
{
	if (PperspectivePoints.size() == 0)
		return;
	
	cv::Mat filterMat(cv::Size(processMat.cols, processMat.rows), CV_8UC1, BLACK_COLOR);
	cv::rectangle(filterMat, PselectedRectangle, WHITE_COLOR, cv::FILLED);

	cv::bitwise_and(filterMat, processMat, processMat);
}

void ImageProcesser::transformPerspective(cv::Mat processMat, std::vector<cv::Point> points, cv::Mat & transMat)
{
	if (points.size() < 3)
		return;

	cv::Point2f outputQuad[4];
	cv::Point2f inputQuad[4];

	inputQuad[0] = points[0];
	inputQuad[1] = points[1];
	inputQuad[2] = points[2];
	inputQuad[3] = points[3];

	// ---------Find new position-------------------
	cv::Point2f center;
	center.x = (points[0].x + points[1].x + points[2].x + points[3].x)/4;
	center.y = (points[0].y + points[1].y + points[2].y + points[3].y) / 4;

	int maxLength = 0;
	
	for (int i = 0; i < 4; i++)
	{
		QLineF line;
		line.setP1(QPoint(inputQuad[i].x, inputQuad[i].y));
		if (i == 3)
		{
			line.setP2(QPoint(inputQuad[0].x, inputQuad[0].y));
		}
		else
		{
			line.setP2(QPoint(inputQuad[i + 1].x, inputQuad[i + 1].y));
		}		

		int len = line.length();

		if (len > maxLength)
		{
			maxLength = len;
		}
	}

	int halfLen = maxLength / 2;

	outputQuad[0] = center + cv::Point2f(-halfLen, -halfLen);
	outputQuad[1] = center + cv::Point2f(-halfLen, halfLen);
	outputQuad[2] = center + cv::Point2f(halfLen, halfLen);
	outputQuad[3] = center + cv::Point2f(halfLen, -halfLen);

	cv:: Mat lambda = cv::Mat::zeros(processMat.rows, processMat.cols, processMat.type());

	lambda = cv::getPerspectiveTransform(inputQuad, outputQuad);

	warpPerspective(processMat, transMat, lambda, transMat.size());
}

void ImageProcesser::MakeBrightProcessRegion(cv::Mat resultsMat)
{
	if (PperspectivePoints.size() == 0)
		return;

	int darkValue = 60;

	cv::Mat filterMat(cv::Size(resultsMat.cols, resultsMat.rows), CV_8UC1, BLACK_COLOR);

	cv::Rect cvRec;
	cvRec.x = DselectedRec.x();
	cvRec.y = DselectedRec.y();
	cvRec.width = DselectedRec.width();
	cvRec.height = DselectedRec.height();

	cv::rectangle(filterMat, cvRec, WHITE_COLOR, cv::FILLED);

	for (int y = 0; y < resultsMat.rows; y++) 
	{
		for (int x = 0; x < resultsMat.cols; x++) 
		{
			for (int c = 0; c < resultsMat.channels(); c++) 
			{
				int vl = resultsMat.at<cv::Vec3b>(y, x)[c] - darkValue;

				if (vl < 0)
					vl = 0;

				if (filterMat.at<uchar>(y, x) == 0)
				{
					resultsMat.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(vl);
				}
				
			}
		}
	}
}

void ImageProcesser::postProcessing(cv::Mat processMat)
{
	// Invert binary image
	if (ParameterPanel->IsInvertBinary())
		cv::bitwise_not(processMat, processMat);

	SelectProcessRegion(processMat);

	resizeImage.copyTo(resultImage);

	// Detect objects in image and manage them
	detectObjects(processMat, resultImage, RED_COLOR);

	UpdateTrackingInfo();

	float ratio = (float)resultImage.rows / resultImage.cols;

	cv::resize(resultImage, resultImage, cv::Size(lbResultImage->width(), lbResultImage->width() * ratio));

	if (cameraLayer == ORIGIN)
	{
		/*putText(resizeImage, "origin", cv::Point(120, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLACK_COLOR, 2);
		putText(resizeImage, "origin", cv::Point(120, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, WHITE_COLOR, 1);*/
		UpdateLabelImage(resizeImage, lbResultImage);
	}
	else if (cameraLayer == PROCESSING)
	{
		UpdateLabelImage(processMat, lbResultImage);
	}
	else if (cameraLayer == RESULT)
	{
		MakeBrightProcessRegion(resultImage);
		drawXAxis(resultImage);
		DisplayAdditionalInfo(resultImage);		

		/*putText(resultImage, "result", cv::Point(120, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLACK_COLOR, 2);
		putText(resultImage, "result", cv::Point(120, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, WHITE_COLOR, 1);*/
		UpdateLabelImage(resultImage, lbResultImage);
	}
	
	UpdateLabelImage(processMat, ParameterPanel->lbProcessImage);
	UpdateLabelImage(resultImage, ParameterPanel->lbOriginImage);
}

void ImageProcesser::detectObjects(cv::Mat input, cv::Mat output, cv::Scalar color)
{	
	//Find contour in image
	std::vector<std::vector<cv::Point> > contoursContainer;
	findContours(input, contoursContainer, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point> >hullsContainer(contoursContainer.size());

	for (size_t i = 0; i < contoursContainer.size(); i++)
	{
		convexHull(contoursContainer[i], hullsContainer[i]);
	}

	//Calculate size of contours

	int visibleCounter = 0;

	for (size_t i = 0; i < contoursContainer.size(); i++)
	{
		
		cv::RotatedRect minRec = cv::minAreaRect(cv::Mat(contoursContainer[i]));

		float h = minRec.size.height;
        float w = minRec.size.width;
		float s = w * h;

		if (w > h)
		{
			float t = h;
			h = w;
			w = t;
		}

		float obHei = PobjectRec.height;
		float obWid = PobjectRec.width;

		if (obWid > obHei)
		{
			float t = obHei;
			obHei = obWid;
			obWid = t;
		}

		//Find an object of equal size

		if (s > minObjectArea && s < maxObjectArea && h < obHei && w < obWid && minRec.boundingRect().y > 0 && (minRec.boundingRect().y + minRec.boundingRect().height + 5) < input.rows)
		{
			findObjectRectangle(output, contoursContainer[i], BLUE_COLOR);

			visibleCounter += 1;
		}
	}

	ObjectManager->VisibleObjectNumber = visibleCounter;
}

void ImageProcesser::drawRotateRec(cv::Mat& mat, int angle, cv::Rect rec, cv::Scalar color)
{
	cv::RotatedRect rRect = cv::RotatedRect(cv::Point2f(rec.x + rec.width / 2, rec.y + rec.height / 2), cv::Size2f(rec.width, rec.height), 30);
	cv::Point2f vertices[4];
	rRect.points(vertices);
	for (int i = 0; i < 4; i++)
		line(mat, vertices[i], vertices[(i + 1) % 4], color, 1);
}

float ImageProcesser::findObjectRectangle(cv::Mat & mat, std::vector<cv::Point> contour, cv::Scalar color)
{
	// Get object position from contour
	cv::RotatedRect minRec = cv::minAreaRect(cv::Mat(contour));

	cv::Point2f rectPoints[4];
	minRec.points(rectPoints);

	// Draw a rectangle outside the object
	for (int j = 0; j < 4; j++)
		cv::line(mat, rectPoints[j], rectPoints[(j + 1) % 4], color, 2, 8);

	int xRealObject = 0;
	int yRealObject = 0;
	
	QPoint PPoint(minRec.center.x, minRec.center.y);
	QPoint RPoint = P2RMatrix.map(PPoint);

	xRealObject = RPoint.x();
	yRealObject = RPoint.y();

	cv::RotatedRect realObject = minRec;

	realObject.center.x = xRealObject;
	realObject.center.y = yRealObject;
	realObject.size.height = minRec.size.height / PnRRatio;
	realObject.size.width = minRec.size.width / PnRRatio;

	int angle = realObject.angle + 180;

	if (realObject.size.width > realObject.size.height)
	{
		angle = realObject.angle + 90;
	}

	// Add object to object list if it is new object
	ObjectManager->AddNewObject(realObject);

	// Add object info to screen
	putText(mat, std::to_string((int)xRealObject) + "," + std::to_string((int)yRealObject) + "," + std::to_string((int)angle), cv::Point(minRec.center.x - 40, minRec.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.4, BLACK_COLOR, 2);
	putText(mat, std::to_string((int)xRealObject) + "," + std::to_string((int)yRealObject) + "," + std::to_string((int)angle), cv::Point(minRec.center.x - 40, minRec.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.4, WHITE_COLOR, 1);

	return minRec.angle;
}

void ImageProcesser::UpdateRatios()
{
	DnPRatio = (float)lbResultImage->width() / Camera->get(cv::CAP_PROP_FRAME_WIDTH);
	CameraRatio = (float)Camera->get(cv::CAP_PROP_FRAME_WIDTH) / Camera->get(cv::CAP_PROP_FRAME_HEIGHT);

	D2PMatrix.setMatrix(DnPRatio, 0, 0, DnPRatio, 0, 0);
}

void ImageProcesser::UpdateTrackingInfo()
{
	lbTrackingObjectNumber->setText(QString::number(ObjectManager->ObjectContainer.size()));
	lbVisibleObjectNumber->setText(QString::number(ObjectManager->VisibleObjectNumber));
}

void ImageProcesser::DisplayAdditionalInfo(cv::Mat & displayMat)
{
	// Draw process rectangle
	drawBlackWhiteRect(displayMat, DselectedRec);
	drawCorner(displayMat, DselectedRec.topLeft());
	drawCorner(displayMat, DselectedRec.bottomRight());
	
	// Draw perspective area
	if (!(DperspectivePoints == NULL || isPerspectiveMode == true))
	{
		for (int i = 0; i < 3; i++)
		{
			drawLine(displayMat, DperspectivePoints[i], DperspectivePoints[i + 1]);
			drawCorner(displayMat, DperspectivePoints[i]);
		}		
		drawLine(displayMat, DperspectivePoints[3], DperspectivePoints[0]);
		drawCorner(displayMat, DperspectivePoints[3]);
	}

	if (isCalibInfoVisible == true)
	{
		// Draw calib point
		cv::putText(displayMat, std::string(" x=") + leXCoor->text().toStdString() + ", y=" + leYCoor->text().toStdString() + " (mm)", cv::Point(DcalibPoint.x(), DcalibPoint.y()), cv::FONT_HERSHEY_SIMPLEX, 0.4, BLACK_COLOR, 2);
		cv::putText(displayMat, std::string(" x=") + leXCoor->text().toStdString() + ", y=" + leYCoor->text().toStdString() + " (mm)", cv::Point(DcalibPoint.x(), DcalibPoint.y()), cv::FONT_HERSHEY_SIMPLEX, 0.4, WHITE_COLOR, 1);
		cv::rectangle(displayMat, cv::Rect(DcalibPoint.x() - 2, DcalibPoint.y() - 2, 5, 5), BLACK_COLOR, cv::FILLED);
		cv::rectangle(displayMat, cv::Rect(DcalibPoint.x() - 1, DcalibPoint.y() - 1, 3, 3), WHITE_COLOR, cv::FILLED);

		// Draw calib line
		drawBlackWhiteLine(displayMat, DcalibLine, 1);

		int xText = DcalibLine.center().x();
		int yText = DcalibLine.center().y() - 10;

		cv::putText(displayMat, leDistance->text().toStdString() + " mm", cv::Point(xText, yText), cv::FONT_HERSHEY_SIMPLEX, 0.4, BLACK_COLOR, 2);
		cv::putText(displayMat, leDistance->text().toStdString() + " mm", cv::Point(xText, yText), cv::FONT_HERSHEY_SIMPLEX, 0.4, WHITE_COLOR, 1);
	}
}

void ImageProcesser::drawBlackWhiteLine(cv::Mat& displayMat, cv::Point p1, cv::Point p2, int thin = 1)
{
	cv::line(displayMat, p1, p2, BLACK_COLOR, thin);
	cv::line(displayMat, cv::Point(p1.x + 1, p1.y + 1), cv::Point(p2.x + 1, p2.y + 1), WHITE_COLOR, thin);
}

void ImageProcesser::drawBlackWhiteLine(cv::Mat & displayMat, QLine line, int thin)
{
	cv::Point p1 = cv::Point(line.x1(), line.y1());
	cv::Point p2 = cv::Point(line.x2(), line.y2());

	drawBlackWhiteLine(displayMat, p1, p2, thin);
}

void ImageProcesser::drawBlackWhiteLines(cv::Mat& displayMat, std::vector<cv::Point> points, int thin = 1)
{
	cv::polylines(displayMat, points, true, BLACK_COLOR, thin);
	cv::polylines(displayMat, points, true, WHITE_COLOR, thin);
}

void ImageProcesser::drawBlackWhiteRect(cv::Mat & displayMat, cv::Point p, cv::Size size)
{
	cv::rectangle(displayMat, cv::Rect(p, size), BLACK_COLOR, 1);
	cv::rectangle(displayMat, cv::Rect(cv::Point(p.x + 1, p.y + 1), size), WHITE_COLOR, 1);
}

void ImageProcesser::drawBlackWhiteRect(cv::Mat & displayMat, QRect rect)
{
	cv::Point pos = cv::Point(rect.x(), rect.y());
	cv::Point pos2 = cv::Point(rect.x() - 1, rect.y() - 1);
	cv::Size size = cv::Size(rect.size().width(), rect.size().height());
	cv::Size size2 = cv::Size(rect.size().width() + 2, rect.size().height() + 2);

	cv::rectangle(displayMat, cv::Rect(pos, size), BLACK_COLOR, 1);
	cv::rectangle(displayMat, cv::Rect(pos2, size2), WHITE_COLOR, 1);
}

void ImageProcesser::drawLine(cv::Mat & displayMat, QPoint p1, QPoint p2)
{
	cv::Point cvPoint1 = cv::Point(p1.x(), p1.y());
	cv::Point cvPoint2 = cv::Point(p2.x(), p2.y());
	drawBlackWhiteLine(displayMat, cvPoint1, cvPoint2, 1);
}

void ImageProcesser::drawCorner(cv::Mat & displayMat, QPoint p)
{
	cv::Point RectcvPoint1 = cv::Point(p.x() - 4, p.y() - 4);

	drawBlackWhiteRect(displayMat, RectcvPoint1, cv::Size(10, 10));
}
