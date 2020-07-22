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

	objectRec.width = DEFAULT_OBJECT_WIDTH;
	objectRec.height = DEFAULT_OBJECT_HEIGHT;
	minObjectArea = MIN_OBJECT_AREA;
	maxObjectArea = MAX_OBJECT_AREA;

	changeAxisDirection();

	ObjectManager = new BlobManager(parent);
	ObjectManager->SetApproximateValue(cv::Point3d(10, 10, 10));

	ObjectMovingCalculaterTimer = new QTimer(this);
	connect(ObjectMovingCalculaterTimer, SIGNAL(timeout()), this, SLOT(CalConvenyorPosition()));

	ObjectMovingCalculaterTimer->setInterval(100);
	ObjectMovingCalculaterTimer->start(100);
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
		QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Camera ID:"), QLineEdit::Normal, "0", &ok);

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
						updateScreenTimer->start(DEFAULT_INTERVAL);
						return;
					}
				}
			}


			Camera->open(text.toInt());

			updateScreenTimer->start(DEFAULT_INTERVAL);

			//loadBt->setText("Stop");
		}
		else
		{
			loadBt->setChecked(false);
			RunningCamera = -1;
		}
	}
	else
	{
		//loadBt->setText("Load Camera");
		updateScreenTimer->stop();
		RunningCamera = -1;
		return;
	}
}

void ImageProcesser::CaptureAnImageFromCamera()
{
	Camera->read(captureImage);
	processImage();
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

	float ratio = (float)captureImage.size().height / captureImage.size().width;

	cv::resize(captureImage, resizeImage, cv::Size(DEFAULT_PROCESSING_SIZE, DEFAULT_PROCESSING_SIZE * ratio));

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
	if (isStopCapture == true)
		return;

	Camera->read(captureImage);
	//cv::VideoWriter video("outcpp.avi", cv:VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(Camera->si, frame_height));
	processImage();
}

void ImageProcesser::SaveFPS()
{
	int FPS = leFPS->text().toInt();

	if (FPS > 0)
		updateScreenTimer->setInterval(1000.0f / FPS);
}

void ImageProcesser::SetDetectParameterPointer(QLineEdit * xRec, QLineEdit * yRec, QLineEdit * distance, QLineEdit * xCoor, QLineEdit * yCoor)
{
	leXRec = xRec;
	leYRec = yRec;
	leDistance = distance;
	leXCoor = xCoor;
	leYCoor = yCoor;
}

void ImageProcesser::SetResultScreenPointer(CameraWidget * resultImage)
{
	lbResultImage = resultImage;

	displayAndProcessRatio = (float)DEFAULT_PROCESSING_SIZE / lbResultImage->width();
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

	postProcessing(processMat);
}

void ImageProcesser::SetThreshold(int value)
{
	thresholdValue = value;

	filterMethod = THRESHOLD_SPACE;

	if (resizeImage.empty())
		return;

	cv::Mat processMat = resizeImage.clone();

	cvtColor(resizeImage, processMat, CV_BGR2GRAY);

	cv::threshold(processMat, processMat, value, 255, CV_THRESH_BINARY);

	postProcessing(processMat);
}

void ImageProcesser::GetObjectInfo(int x, int y, int h, int w)
{
	if (lbResultImage->pixmap() == NULL)
		return;

	float ratio = (float)DEFAULT_PROCESSING_SIZE / lbResultImage->width();
	objectRec.x = x;
	objectRec.y = y;
	objectRec.width = w * ratio;
	objectRec.height = h * ratio;
	minObjectArea = (objectRec.width - APPROXIMATE_RANGE) * (objectRec.height - APPROXIMATE_RANGE);
	maxObjectArea = (objectRec.width + APPROXIMATE_RANGE) * (objectRec.height + APPROXIMATE_RANGE);

	QPixmap regionPixmap = lbResultImage->pixmap()->copy(x, y, w, h);
	
	if (w > h)
		regionPixmap = regionPixmap.scaledToWidth(lbObjectImage->width());
	else
		regionPixmap = regionPixmap.scaledToHeight(lbObjectImage->height());
	
	lbObjectImage->setPixmap(regionPixmap);


	leXRec->setText(QString::number(objectRec.width));
	leYRec->setText(QString::number(objectRec.height));

	ObjectManager->SetApproximateValue(cv::Point3d((float)h * 0.8f, (float)w * 0.8f, 60));
}

void ImageProcesser::GetProcessRegion(QPoint a, QPoint b, QPoint c, QPoint d)
{
	float ratio = (float)DEFAULT_PROCESSING_SIZE / lbResultImage->width();
	processRegionPoints.clear();
	processRegionPoints.push_back(cv::Point(a.x() * ratio, a.y() * ratio));
	processRegionPoints.push_back(cv::Point(b.x() * ratio, b.y() * ratio));
	processRegionPoints.push_back(cv::Point(c.x() * ratio, c.y() * ratio));
	processRegionPoints.push_back(cv::Point(d.x() * ratio, d.y() * ratio));
}

void ImageProcesser::GetDistance(int distance)
{
	float displayWidth = lbResultImage->width();
	float realWidth = leDistance->text().toInt();
	processAndRealRatio = (displayWidth * realWidth) / (distance * DEFAULT_PROCESSING_SIZE);
	displayAndRealRatio = (float)leDistance->text().toInt() / distance;
}

void ImageProcesser::GetCalibPoint(int x, int y)
{
	float xCalib = leXCoor->text().toInt();
	float yCalib = leYCoor->text().toInt();

	xRealCamOri = xCalib - y * displayAndRealRatio;
	yRealCamOri = yCalib - x * displayAndRealRatio;

	if (axisDirection == X_AXIS_RIGHT)
	{
		xRealCamOri = -xCalib + x * displayAndRealRatio;
		yRealCamOri = yCalib + y * displayAndRealRatio;
	}

	if (axisDirection == X_AXIS_UP)
	{
		xRealCamOri = xCalib + y * displayAndRealRatio;
		yRealCamOri = yCalib + x * displayAndRealRatio;
	}
}

void ImageProcesser::SwitchLayer()
{
	cameraLayer++;
	if (cameraLayer > 2)
	{
		cameraLayer = 0;
	}
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
		xAxis.setP1(QPoint(20, 20));
		xAxis.setP2(QPoint(20, 80));
		arrow1.setP1(QPoint(25, 70));
		arrow1.setP2(QPoint(20, 80));
		arrow2.setP1(QPoint(15, 70));
		arrow2.setP2(QPoint(20, 80));
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
		xAxis.setP1(QPoint(20, 20));
		xAxis.setP2(QPoint(80, 20));
		arrow1.setP1(QPoint(70, 25));
		arrow1.setP2(QPoint(80, 20));
		arrow2.setP1(QPoint(70, 15));
		arrow2.setP2(QPoint(80, 20));
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
		xAxis.setP1(QPoint(20, 80));
		xAxis.setP2(QPoint(20, 20));
		arrow1.setP1(QPoint(25, 30));
		arrow1.setP2(QPoint(20, 20));
		arrow2.setP1(QPoint(15, 30));
		arrow2.setP2(QPoint(20, 20));
	}
}

void ImageProcesser::CalConvenyorPosition()
{
	float distance = conveyorVel / 10;

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
	cv::line(resultImage, cv::Point(xAxis.p1().x(), xAxis.p1().y()), cv::Point(xAxis.p2().x(), xAxis.p2().y()), RED_COLOR, 2);
	cv::line(resultImage, cv::Point(arrow1.p1().x(), arrow1.p1().y()), cv::Point(arrow1.p2().x(), arrow1.p2().y()), RED_COLOR, 2);
	cv::line(resultImage, cv::Point(arrow2.p1().x(), arrow2.p1().y()), cv::Point(arrow2.p2().x(), arrow2.p2().y()), RED_COLOR, 2);
	putText(resultImage, "+x", cv::Point(xAxis.p2().x() + 5, xAxis.p2().y() + 5), cv::FONT_HERSHEY_SIMPLEX, 0.8, RED_COLOR, 2);
}

void ImageProcesser::SelectProcessRegion(cv::Mat processMat)
{
	if (processRegionPoints.size() == 0)
		return;

	cv::Mat filterMat(cv::Size(processMat.cols, processMat.rows), CV_8UC1, BLACK_COLOR);
	cv::fillConvexPoly(filterMat, processRegionPoints, WHITE_COLOR);

	cv::bitwise_and(filterMat, processMat, processMat);
}

void ImageProcesser::MakeBrightProcessRegion(cv::Mat resultsMat)
{
	if (processRegionPoints.size() == 0)
		return;

	int darkValue = 100;

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
	if (ParameterPanel->IsInvertBinary())
		cv::bitwise_not(processMat, processMat);

	SelectProcessRegion(processMat);

	resizeImage.copyTo(resultImage);

	MakeBrightProcessRegion(resultImage);

	paintInfo(processMat, resultImage, RED_COLOR);

	UpdateTrackingInfo();

	drawXAxis();

	if (cameraLayer == ORIGIN)
	{
		putText(resizeImage, "origin", cv::Point(resizeImage.cols - 80, 50), cv::FONT_HERSHEY_SIMPLEX, 0.8, RED_COLOR, 2);
		UpdateLabelImage(resizeImage, lbResultImage);
	}
	else if (cameraLayer == PROCESSING)
	{
		//putText(processMat, "filter", cv::Point(processMat.cols - 70, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, RED_COLOR, 2);
		UpdateLabelImage(processMat, lbResultImage);
	}
	else if (cameraLayer == RESULT)
	{
		putText(resultImage, "result", cv::Point(resultImage.cols - 80, 50), cv::FONT_HERSHEY_SIMPLEX, 0.8, RED_COLOR, 2);
		UpdateLabelImage(resultImage, lbResultImage);
	}

	//UpdateLabelImage(processMat, lbProcessImage);
	//UpdateLabelImage(resultImage, lbResultImage);

	UpdateLabelImage(processMat, ParameterPanel->lbProcessImage);
	UpdateLabelImage(resultImage, ParameterPanel->lbOriginImage);
}

void ImageProcesser::paintInfo(cv::Mat input, cv::Mat output, cv::Scalar color)
{	
	std::vector<std::vector<cv::Point> > contoursContainer;
	findContours(input, contoursContainer, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point> >hullsContainer(contoursContainer.size());

	for (size_t i = 0; i < contoursContainer.size(); i++)
	{
		convexHull(contoursContainer[i], hullsContainer[i]);
	}

	//------------------------

	int visibleCounter = 0;

	for (size_t i = 0; i < contoursContainer.size(); i++)
	{
		//cv::Rect rec = boundingRect(contoursContainer[i]);
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

		//cv::drawContours(output, hullsContainer, (int)i, RED_COLOR);

		if (s > minObjectArea && s < maxObjectArea && h < obHei && w < obWid && minRec.boundingRect().y > 0 && (minRec.boundingRect().y + minRec.boundingRect().height + 5) < input.rows)
		{
			drawMinRec(output, contoursContainer[i], BLUE_COLOR);
			//cv::drawContours(output, hullsContainer, (int)i, RED_COLOR);

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

float ImageProcesser::drawMinRec(cv::Mat & mat, std::vector<cv::Point> contour, cv::Scalar color)
{
	cv::RotatedRect minRec = cv::minAreaRect(cv::Mat(contour));
	cv::Point2f rectPoints[4]; 

	minRec.points(rectPoints);

	for (int j = 0; j < 4; j++)
		cv::line(mat, rectPoints[j], rectPoints[(j + 1) % 4], color, 2, 8);

	int xRealObject = xRealCamOri + minRec.center.y * processAndRealRatio;
	int yRealObject = yRealCamOri + minRec.center.x * processAndRealRatio;

	if (axisDirection == X_AXIS_RIGHT)
	{
		xRealObject = -xRealCamOri + minRec.center.x * processAndRealRatio;
		yRealObject = yRealCamOri - minRec.center.y * processAndRealRatio;
	}

	if (axisDirection == X_AXIS_UP)
	{
		xRealObject = xRealCamOri - minRec.center.y * processAndRealRatio;
		yRealObject = yRealCamOri - minRec.center.x * processAndRealRatio;
	}

	cv::RotatedRect realObject = minRec;

	realObject.center.x = xRealObject;
	realObject.center.y = yRealObject;
	realObject.size.height = minRec.size.height * processAndRealRatio;
	realObject.size.width = minRec.size.width * processAndRealRatio;

	int angle = realObject.angle + 180;

	if (realObject.size.width > realObject.size.height)
	{
		angle = realObject.angle + 90;
	}

	ObjectManager->AddNewObject(realObject);

	putText(mat, std::to_string((int)xRealObject) + "," + std::to_string((int)yRealObject) + "," + std::to_string((int)angle), cv::Point(minRec.center.x - 40, minRec.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLUE_COLOR, 2);

	return minRec.angle;
}

void ImageProcesser::UpdateTrackingInfo()
{
	lbTrackingObjectNumber->setText(QString::number(ObjectManager->ObjectContainer.size()));
	lbVisibleObjectNumber->setText(QString::number(ObjectManager->VisibleObjectNumber));


}
