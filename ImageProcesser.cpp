#include "ImageProcesser.h"

ImageProcesser::ImageProcesser(MainWindow *parent)
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

	objectRec.width = DEFAULT_OBJECT_WIDTH;
	objectRec.height = DEFAULT_OBJECT_HEIGHT;
	minObjectArea = MIN_OBJECT_AREA;
	maxObjectArea = MAX_OBJECT_AREA;

	changeAxisDirection();

	ObjectManager = new BlobManager(parent);
	ObjectManager->SetApproximateValue(cv::Point3d(10, 10, 10));

	ObjectMovingCalculaterTimer = new QTimer(this);
	connect(ObjectMovingCalculaterTimer, SIGNAL(timeout()), this, SLOT(UpdateObjectPositionOnConveyor()));

	ObjectMovingCalculaterTimer->start(CONVEYOR_TIMER_INTERVAL);
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
	QPushButton* loadBt = qobject_cast<QPushButton*>(sender());
	if (loadBt->isChecked())
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("Open Camera"), tr("ID: "), QLineEdit::Normal, "0", &ok);

		if (ok && !text.isEmpty())
		{
			RunningCamera = text.toInt();

			if (mParent->DeltaXMainWindows != NULL)
			{
				for (int i = 0; i < mParent->DeltaXMainWindows->size(); i++)
				{
					if (mParent->DeltaXMainWindows->at(i)->DeltaImageProcesser->RunningCamera == RunningCamera)
					{
						Camera = mParent->DeltaXMainWindows->at(i)->DeltaImageProcesser->Camera;
						IsCameraPause = false;
						return;
					}
				}
			}


			Camera->open(text.toInt());
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
		Camera->release();
		RunningCamera = -1;
		IsCameraPause = false;
		return;
	}
}

void ImageProcesser::CaptureCamera()
{
	if (!Camera->isOpened())
		return;
	
	Camera->read(captureImage);
}

void ImageProcesser::PauseCamera()
{
	IsCameraPause = true;
}

void ImageProcesser::ResumeCamera()
{
	IsCameraPause = false;
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

	
	cv::resize(captureImage, resizeImage, cv::Size(lbResultImage->width(), lbResultImage->height()));


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

	processImage();
}

void ImageProcesser::SaveFPS()
{
	CameraFPS = leFPS->text().toInt();
	CameraTimerInterval = 1000 / CameraFPS;

	if (CameraFPS > 0)
		updateScreenTimer->setInterval(CameraTimerInterval);
}

void ImageProcesser::SetDetectParameterPointer(QLineEdit * xRec, QLineEdit * yRec, QLineEdit * distance, QLineEdit * xCoor, QLineEdit * yCoor)
{
	leWRec = xRec;
	leLRec = yRec;
	leDistance = distance;
	leXCoor = xCoor;
	leYCoor = yCoor;
}

void ImageProcesser::SetResultScreenPointer(CameraWidget * resultImage)
{
	lbResultImage = resultImage;

	//DisplayAndProcessRatio = (float)DEFAULT_PROCESSING_SIZE / lbResultImage->width();
	DisplayAndProcessRatio = (float)lbResultImage->width() / lbResultImage->width();
}

void ImageProcesser::SetObjectScreenPointer(QLabel * objectImage)
{
	lbObjectImage = objectImage;
}

void ImageProcesser::SetFPSInputBox(QLineEdit * fps)
{
	leFPS = fps;
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
	objectRec.x = x;
	objectRec.y = y;

	GetObjectInfo(l, w);
	
	leWRec->setText(QString::number((int)(w * DisplayAndRealRatio)));
	leLRec->setText(QString::number((int)(l * DisplayAndRealRatio)));
}

void ImageProcesser::GetObjectInfo(int l, int w)
{
	if (lbResultImage->pixmap() == NULL)
		return;

	//float ratio = (float)DEFAULT_PROCESSING_SIZE / lbResultImage->width();
	float ratio = (float)lbResultImage->width() / lbResultImage->width();

	// Update information about the object to be identified
	
	objectRec.width = w * ratio;
	objectRec.height = l * ratio;

	minObjectArea = (objectRec.width - APPROXIMATE_RANGE) * (objectRec.height - APPROXIMATE_RANGE);
	maxObjectArea = (objectRec.width + APPROXIMATE_RANGE) * (objectRec.height + APPROXIMATE_RANGE);

	ObjectManager->SetApproximateValue(cv::Point3d((float)l * 0.8f, (float)w * 0.8f, 60));

	//Display ROI is cut from widget
	QPixmap regionPixmap = lbResultImage->pixmap()->copy(objectRec.x, objectRec.y, w, l);

	if (w > l)
		regionPixmap = regionPixmap.scaledToWidth(lbObjectImage->width());
	else
		regionPixmap = regionPixmap.scaledToHeight(lbObjectImage->height());

	lbObjectImage->setPixmap(regionPixmap);
}

void ImageProcesser::GetProcessRegion(QPoint a, QPoint b, QPoint c, QPoint d)
{
	//float ratio = (float)DEFAULT_PROCESSING_SIZE / lbResultImage->width();
	float ratio = (float)resizeImage.cols / lbResultImage->width();

	processRegionPoints.clear();
	processRegionPoints.push_back(cv::Point(a.x() * ratio, a.y() * ratio));
	processRegionPoints.push_back(cv::Point(b.x() * ratio, b.y() * ratio));
	processRegionPoints.push_back(cv::Point(c.x() * ratio, c.y() * ratio));
	processRegionPoints.push_back(cv::Point(d.x() * ratio, d.y() * ratio));
}

void ImageProcesser::GetCalibLine(QPoint p1, QPoint p2)
{
	float ratio = (float)lbResultImage->width() / lbResultImage->width();

	calibLinePoint1 = cv::Point(p1.x() * ratio, p1.y() * ratio);
	calibLinePoint2 = cv::Point(p2.x() * ratio, p2.y() * ratio);
}

void ImageProcesser::GetDistance(int distance)
{
	float displayWidth = lbResultImage->width();
	float realWidth = leDistance->text().toInt();
	ProcessAndRealRatio = (displayWidth * realWidth) / (distance * DEFAULT_PROCESSING_SIZE);
	DisplayAndRealRatio = (float)leDistance->text().toInt() / distance;
}

void ImageProcesser::GetCalibPoint(int x, int y)
{
	xWidgetCalibPoint = x;
	yWidgetCalibPoint = y;

	//float ratio = 

	if (leXCoor == NULL)
		return;

	float xCalib = leXCoor->text().toInt();
	float yCalib = leYCoor->text().toInt();

	xRealCamOri = xCalib - y * DisplayAndRealRatio;
	yRealCamOri = yCalib - x * DisplayAndRealRatio;

	if (axisDirection == X_AXIS_RIGHT)
	{
		xRealCamOri = -xCalib + x * DisplayAndRealRatio;
		yRealCamOri = yCalib + y * DisplayAndRealRatio;
	}

	if (axisDirection == X_AXIS_UP)
	{
		xRealCamOri = xCalib + y * DisplayAndRealRatio;
		yRealCamOri = yCalib + x * DisplayAndRealRatio;
	}
}

void ImageProcesser::SwitchLayer()
{
	cameraLayer++;
	if (cameraLayer > 3)
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
	if (axisDirection == X_AXIS_UP)
	{
		if (leXCoor != NULL)
		{
			int newX = 0 - leXCoor->text().toInt();
			int newY = 0 - leYCoor->text().toInt();
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

	GetCalibPoint(xWidgetCalibPoint, yWidgetCalibPoint);	
}

void ImageProcesser::UpdateObjectPositionOnConveyor()
{
	float distance = conveyorVel / (1000.0f / CONVEYOR_TIMER_INTERVAL);

	if (dirName == "X")
	{
		ObjectManager->UpdateNewPositionObjects(distance, 0);
	}
	else
	{
		ObjectManager->UpdateNewPositionObjects(0, distance);
	}

	emit ObjectValueChanged(ObjectManager->ObjectContainer);
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
	conveyorVel = val;
	dirName = dir;
}

void ImageProcesser::drawXAxis()
{
	drawBlackWhiteLine(resultImage, cv::Point(xAxis.p1().x(), xAxis.p1().y()), cv::Point(xAxis.p2().x(), xAxis.p2().y()), 1);
	drawBlackWhiteLine(resultImage, cv::Point(arrow1.p1().x(), arrow1.p1().y()), cv::Point(arrow1.p2().x(), arrow1.p2().y()), 1);
	drawBlackWhiteLine(resultImage, cv::Point(arrow2.p1().x(), arrow2.p1().y()), cv::Point(arrow2.p2().x(), arrow2.p2().y()), 1);
	
	if (axisDirection == X_AXIS_DOWN)
	{
		putText(resultImage, "+x", cv::Point(xAxis.p2().x() - 10, xAxis.p2().y() + 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultImage, "+x", cv::Point(xAxis.p2().x() - 11, xAxis.p2().y() + 21), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else if (axisDirection == X_AXIS_RIGHT)
	{
		putText(resultImage, "+x", cv::Point(xAxis.p2().x() + 20, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultImage, "+x", cv::Point(xAxis.p2().x() + 21, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else
	{
		putText(resultImage, "+x", cv::Point(xAxis.p2().x() + 10, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultImage, "+x", cv::Point(xAxis.p2().x() + 11, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1); 
	}
}

void ImageProcesser::SelectProcessRegion(cv::Mat processMat)
{
	if (processRegionPoints.size() == 0)
		return;

	transformPerspective(processMat, processRegionPoints, transformImage);

	cv::Mat filterMat(cv::Size(processMat.cols, processMat.rows), CV_8UC1, BLACK_COLOR);
	cv::fillConvexPoly(filterMat, processRegionPoints, WHITE_COLOR);

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

	outputQuad[0] = cv::Point(0, 0);
	outputQuad[1] = cv::Point(0, processMat.rows - 1);
	outputQuad[2] = cv::Point(processMat.cols - 1, processMat.rows - 1);
	outputQuad[3] = cv::Point(processMat.cols - 1, 0);

	cv:: Mat lambda = cv::Mat::zeros(processMat.rows, processMat.cols, processMat.type());

	lambda = cv::getPerspectiveTransform(inputQuad, outputQuad);

	warpPerspective(processMat, transMat, lambda, transMat.size());
}

void ImageProcesser::MakeBrightProcessRegion(cv::Mat resultsMat)
{
	if (processRegionPoints.size() == 0)
		return;

	int darkValue = 60;

	cv::Mat filterMat(cv::Size(resultsMat.cols, resultsMat.rows), CV_8UC1, BLACK_COLOR);

	cv::fillConvexPoly(filterMat, processRegionPoints, WHITE_COLOR);

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

	//cv::bitwise_and(filterMat, resultsMat, resultsMat);
}

void ImageProcesser::postProcessing(cv::Mat processMat)
{
	// Invert binary image
	if (ParameterPanel->IsInvertBinary())
		cv::bitwise_not(processMat, processMat);


	SelectProcessRegion(processMat);

	resizeImage.copyTo(resultImage);

	MakeBrightProcessRegion(resultImage);

	// Detect objects in image and manage them
	detectObjects(processMat, resultImage, RED_COLOR);

	UpdateTrackingInfo();

	// Display info to screen widget
	drawXAxis();

	if (cameraLayer == ORIGIN)
	{
		putText(resizeImage, "origin", cv::Point(resizeImage.cols - 70, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, RED_COLOR, 1);
		UpdateLabelImage(resizeImage, lbResultImage);
	}
	else if (cameraLayer == PROCESSING)
	{
		putText(processMat, "processing", cv::Point(resizeImage.cols - 100, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, RED_COLOR, 1);
		UpdateLabelImage(processMat, lbResultImage);
	}
	else if (cameraLayer == RESULT)
	{
		DisplayAdditionalInfo(resultImage);
		putText(resultImage, "result", cv::Point(resizeImage.cols - 70, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, RED_COLOR, 1);
		UpdateLabelImage(resultImage, lbResultImage);
	}
	else if (cameraLayer == TRANSFORM)
	{
		putText(transformImage, "transform", cv::Point(resizeImage.cols - 100, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, RED_COLOR, 1);
		UpdateLabelImage(transformImage, lbResultImage);
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
		float ratio = h / w;
		float s = w * h;

		if (w > h)
		{
			float t = h;
			h = w;
			w = t;
		}

		float obHei = objectRec.height;
		float obWid = objectRec.width;

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


	// Calculate real position of object
	int xRealObject = xRealCamOri + minRec.center.y * ProcessAndRealRatio;
	int yRealObject = yRealCamOri + minRec.center.x * ProcessAndRealRatio;

	if (axisDirection == X_AXIS_RIGHT)
	{
		xRealObject = -xRealCamOri + minRec.center.x * ProcessAndRealRatio;
		yRealObject = yRealCamOri - minRec.center.y * ProcessAndRealRatio;
	}

	if (axisDirection == X_AXIS_UP)
	{
		xRealObject = xRealCamOri - minRec.center.y * ProcessAndRealRatio;
		yRealObject = yRealCamOri - minRec.center.x * ProcessAndRealRatio;
	}

	cv::RotatedRect realObject = minRec;

	realObject.center.x = xRealObject;
	realObject.center.y = yRealObject;
	realObject.size.height = minRec.size.height * ProcessAndRealRatio;
	realObject.size.width = minRec.size.width * ProcessAndRealRatio;

	int angle = realObject.angle + 180;

	if (realObject.size.width > realObject.size.height)
	{
		angle = realObject.angle + 90;
	}

	// Add object to object list if it is new object
	ObjectManager->AddNewObject(realObject);

	// Add object info to screen
	putText(mat, std::to_string((int)xRealObject) + "," + std::to_string((int)yRealObject) + "," + std::to_string((int)angle), cv::Point(minRec.center.x - 40, minRec.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLUE_COLOR, 2);

	return minRec.angle;
}

void ImageProcesser::UpdateTrackingInfo()
{
	lbTrackingObjectNumber->setText(QString::number(ObjectManager->ObjectContainer.size()));
	lbVisibleObjectNumber->setText(QString::number(ObjectManager->VisibleObjectNumber));
}

void ImageProcesser::DisplayAdditionalInfo(cv::Mat & displayMat)
{
	// Draw calib line
	drawBlackWhiteLine(displayMat, calibLinePoint1, calibLinePoint2, 1);

	int xText = (calibLinePoint1.x + calibLinePoint2.x) / 2;
	int yText = (calibLinePoint1.y + calibLinePoint1.y) / 2 - 10;

	cv::putText(displayMat, leDistance->text().toStdString() + " mm", cv::Point(xText, yText), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
	cv::putText(displayMat, leDistance->text().toStdString() + " mm", cv::Point(xText + 1, yText + 1), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);

	// Draw process region
	if (processRegionPoints.size() == 0)
		return;

	int offset = 1;
	int thin = 1;
	
	for (int i = 0; i < 3; i++)
	{
		cv::line(displayMat, processRegionPoints[i], processRegionPoints[i + 1], BLACK_COLOR, thin);
		cv::rectangle(displayMat, cv::Rect(cv::Point(processRegionPoints[i].x - 4, processRegionPoints[i].y - 4), cv::Size(10, 10)), BLACK_COLOR, thin);
	}

	cv::line(displayMat, processRegionPoints[3], processRegionPoints[0], BLACK_COLOR, thin);
	cv::rectangle(displayMat, cv::Rect(cv::Point(processRegionPoints[3].x - 4, processRegionPoints[3].y - 4), cv::Size(10, 10)), BLACK_COLOR, thin);
	
	for (int i = 0; i < 3; i++)
	{
		cv::line(displayMat, cv::Point(processRegionPoints[i].x + offset, processRegionPoints[i].y + offset), cv::Point(processRegionPoints[i + 1].x + offset, processRegionPoints[i + 1].y + offset), WHITE_COLOR, thin);
		cv::rectangle(displayMat, cv::Rect(cv::Point(processRegionPoints[i].x - 4, processRegionPoints[i].y - 4), cv::Size(10, 10)), WHITE_COLOR, thin);
	}
	cv::line(displayMat, cv::Point(processRegionPoints[3].x + offset, processRegionPoints[3].y + offset), cv::Point(processRegionPoints[0].x + offset, processRegionPoints[0].y + offset), WHITE_COLOR, thin);
	cv::rectangle(displayMat, cv::Rect(cv::Point(processRegionPoints[3].x - 4, processRegionPoints[3].y - 4), cv::Size(10, 10)), WHITE_COLOR, thin);
}

void ImageProcesser::drawBlackWhiteLine(cv::Mat& displayMat, cv::Point p1, cv::Point p2, int thin = 1)
{
	cv::line(displayMat, p1, p2, BLACK_COLOR, thin);
	cv::line(displayMat, cv::Point(p1.x + 1, p1.y + 1), cv::Point(p2.x + 1, p2.y + 1), WHITE_COLOR, thin);
}

void ImageProcesser::drawBlackWhiteLines(cv::Mat& displayMat, std::vector<cv::Point> points, int thin = 1)
{
	cv::polylines(displayMat, points, true, BLACK_COLOR, thin);
	cv::polylines(displayMat, points, true, WHITE_COLOR, thin);
}
