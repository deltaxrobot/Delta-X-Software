#include "ImageProcesser.h"

ImageProcesser::ImageProcesser(QWidget *parent)
	: QWidget(parent)
{
	ParameterPanel = new HSVWindow(parent);
	connect(ParameterPanel, SIGNAL(ValueChanged(int, int, int, int, int, int)), this, SLOT(SetHSV(int, int, int, int, int, int)));
	connect(ParameterPanel, SIGNAL(ValueChanged(int)), this, SLOT(SetThreshold(int)));

	updateScreenTimer = new QTimer(this);
	connect(updateScreenTimer, SIGNAL(timeout()), this, SLOT(UpdateCameraScreen()));

	objectRec.width = DEFAULT_OBJECT_WIDTH;
	objectRec.height = DEFAULT_OBJECT_HEIGHT;
	minObjectArea = MIN_OBJECT_AREA;
	maxObjectArea = MAX_OBJECT_AREA;

	changeAxisDirection();

	ConvenyorObjectManager = new BlobManager(parent);
	ConvenyorObjectManager->SetApproximateValue(cv::Point3d(10, 10, 10));
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

	if (!captureImage.data)
		return;
	
	float ratio = (float)captureImage.size().height / captureImage.size().width;
	

	cv::resize(captureImage, resizeImage, cv::Size(DEFAULT_PROCESSING_SIZE, DEFAULT_PROCESSING_SIZE * ratio));

	UpdateLabelImage(resizeImage, lbResultImage);
}

void ImageProcesser::UpdateCameraScreen()
{
	if (lbResultImage->pixmap() != nullptr && isFirstLoad == true)
	{
		lbResultImage->InitParameter();
		isFirstLoad = false;
	}

	camera.read(captureImage);

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
	if (axisDirection == 1)
	{
		axisDirection = 2;
		xAxis.setP1(QPoint(20, 20));
		xAxis.setP2(QPoint(20, 80));
		arrow1.setP1(QPoint(25, 70));
		arrow1.setP2(QPoint(20, 80));
		arrow2.setP1(QPoint(15, 70));
		arrow2.setP2(QPoint(20, 80));
	}
	else if (axisDirection == 2)
	{
		axisDirection = 1;
		xAxis.setP1(QPoint(20, 20));
		xAxis.setP2(QPoint(80, 20));
		arrow1.setP1(QPoint(70, 25));
		arrow1.setP2(QPoint(80, 20));
		arrow2.setP1(QPoint(70, 15));
		arrow2.setP2(QPoint(80, 20));
	}
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
			camera.open(text.toInt());

			updateScreenTimer->start(50);
			
			//loadBt->setText("Stop");
		}
		else
		{
			loadBt->setChecked(false);
		}
	}
	else
	{
		//loadBt->setText("Load Camera");
		updateScreenTimer->stop();
		return;
	}
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

void ImageProcesser::drawXAxis()
{
	cv::line(resultImage, cv::Point(xAxis.p1().x(), xAxis.p1().y()), cv::Point(xAxis.p2().x(), xAxis.p2().y()), RED_COLOR);
	cv::line(resultImage, cv::Point(arrow1.p1().x(), arrow1.p1().y()), cv::Point(arrow1.p2().x(), arrow1.p2().y()), RED_COLOR);
	cv::line(resultImage, cv::Point(arrow2.p1().x(), arrow2.p1().y()), cv::Point(arrow2.p2().x(), arrow2.p2().y()), RED_COLOR);
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

void ImageProcesser::postProcessing(cv::Mat processMat)
{
	if (ParameterPanel->IsInvertBinary())
		cv::bitwise_not(processMat, processMat);

	SelectProcessRegion(processMat);

	resizeImage.copyTo(resultImage);

	paintInfo(processMat, resultImage, RED_COLOR);

	drawXAxis();

	if (cameraLayer == ORIGIN)
	{
		UpdateLabelImage(resizeImage, lbResultImage);
	}
	else if (cameraLayer == PROCESSING)
	{
		UpdateLabelImage(processMat, lbResultImage);
	}
	else if (cameraLayer == RESULT)
	{
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

	//for (auto &convexHull : hullsContainer)
	//{
	//	Blob possibleBlob(convexHull);

	//	if (isNotCollision(possibleBlob, currentFrameBlobs) &&
	//		possibleBlob.CurrentBoundingRect.area() > 5000 &&
	//		possibleBlob.CurrentAspectRatio >= 0.7 &&
	//		possibleBlob.CurrentAspectRatio <= 2 &&
	//		possibleBlob.CurrentBoundingRect.width > 100 &&
	//		possibleBlob.CurrentBoundingRect.height > 200 &&
	//		possibleBlob.CurrentDiagonalSize > 60.0 &&
	//		(contourArea(possibleBlob.CurrentContour) / (double)possibleBlob.CurrentBoundingRect.area()) > 0.50)
	//	{
	//		currentFrameBlobs.push_back(possibleBlob);
	//	}
	//}

	//if (isFirstFrame == true)
	//{
	//	for (auto &currentFrameBlob : currentFrameBlobs)
	//	{
	//		appearedBlobs.push_back(currentFrameBlob);
	//	}
	//}
	//else
	//{
	//	matchCurrentFrameBlobsToExistingBlobs(appearedBlobs, currentFrameBlobs);
	//}

	//countedObjectNumber = getObjectNumber(appearedBlobs);
	//drawCountedObjectDigit(countedObjectNumber, output);

	//isFirstFrame = false;

	//------------------------
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

		cv::drawContours(output, hullsContainer, (int)i, RED_COLOR);

		if (s > minObjectArea && s < maxObjectArea && h < obHei && w < obWid && minRec.boundingRect().y > 0 && (minRec.boundingRect().y + minRec.boundingRect().height + 5) < input.rows)
		{
			//rectangle(output, rec, color, 1);
			drawMinRec(output, contoursContainer[i], BLUE_COLOR);
			cv::drawContours(output, hullsContainer, (int)i, RED_COLOR);
			//drawRotateRec(output, 30, rec, GREEN_COLOR);
			//putText(output, std::to_string((int)s), cv::Point(rec.x + 20, rec. y + 20), cv::FONT_HERSHEY_SIMPLEX, 0.25, color, 1);
		}
	}
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

	int xRealObject = xRealCamOri + minRec.center.x * processAndRealRatio;
	int yRealObject = yRealCamOri + minRec.center.y * processAndRealRatio;

	if (axisDirection == 2)
	{
		xRealObject = xRealCamOri + minRec.center.y * processAndRealRatio;
		yRealObject = yRealCamOri + minRec.center.x * processAndRealRatio;
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

	ConvenyorObjectManager->AddNewObject(realObject);

	putText(mat, std::to_string((int)xRealObject) + "," + std::to_string((int)yRealObject) + "," + std::to_string((int)angle), cv::Point(minRec.center.x - 40, minRec.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLUE_COLOR, 2);

	return minRec.angle;
}

bool ImageProcesser::isNotCollision(Blob currentBlob, std::vector<Blob> blobs)
{
	for (auto &blob : blobs)
	{
		if (!currentBlob.IsEqual(blob))
		{
			if (((currentBlob.CurrentBoundingRect & blob.CurrentBoundingRect).area() > 0))
				return false;
		}
	}
	return true;
}

void ImageProcesser::matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob>& existingBlobs, std::vector<Blob>& currentFrameBlobs)
{
	for (auto &existingBlob : existingBlobs)
	{
		existingBlob.IsNotNewBlob = false;
		existingBlob.PredictNextPosition();
	}

	for (auto &currentFrameBlob : currentFrameBlobs)
	{
		int leastDistanceOrder = 0;
		double leastDistance = 100000.0;

		for (unsigned int i = 0; i < existingBlobs.size(); i++)
		{
			if (existingBlobs[i].IsBeingTracked == true)
			{
				double distance = getDistance(currentFrameBlob.CenterPositions.back(), existingBlobs[i].PredictedNextPosition);

				if (distance < leastDistance)
				{
					leastDistance = distance;
					leastDistanceOrder = i;
				}
			}
		}

		if (leastDistance < currentFrameBlob.CurrentDiagonalSize * 0.5)
		{
			updateAppearedBlob(currentFrameBlob, existingBlobs, leastDistanceOrder);
		}
		else
		{
			addNewBlob(currentFrameBlob, existingBlobs);
		}

	}

	for (auto &existingBlob : existingBlobs)
	{
		if (existingBlob.IsNotNewBlob == false)
		{
			existingBlob.NonMatchFrameNumber++;
		}

		if (existingBlob.NonMatchFrameNumber >= 5)
		{
			existingBlob.IsBeingTracked = false;
		}
	}
}

void ImageProcesser::updateAppearedBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex)
{

	existingBlobs[intIndex].CurrentContour = currentFrameBlob.CurrentContour;
	existingBlobs[intIndex].CurrentBoundingRect = currentFrameBlob.CurrentBoundingRect;

	existingBlobs[intIndex].CenterPositions.push_back(currentFrameBlob.CenterPositions.back());

	existingBlobs[intIndex].CurrentDiagonalSize = currentFrameBlob.CurrentDiagonalSize;
	existingBlobs[intIndex].CurrentAspectRatio = currentFrameBlob.CurrentAspectRatio;
	existingBlobs[intIndex].countMatch++;

	if (existingBlobs[intIndex].countMatch >= 10)
	{
		existingBlobs[intIndex].IsACar = true;
	}

	existingBlobs[intIndex].IsBeingTracked = true;
	existingBlobs[intIndex].IsNotNewBlob = true;


}

void ImageProcesser::addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs)
{

	currentFrameBlob.IsNotNewBlob = true;
	currentFrameBlob.IsACar = false;

	existingBlobs.push_back(currentFrameBlob);

	isDetectedNewObject = true;
}

double ImageProcesser::getDistance(cv::Point point1, cv::Point point2)
{

	int intX = abs(point1.x - point2.x);
	int intY = abs(point1.y - point2.y);

	return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

int ImageProcesser::getObjectNumber(std::vector<Blob>& blobs)
{
	int count = 0;
	for (unsigned int i = 0; i < blobs.size(); i++)
	{
		if (blobs[i].IsACar == true)
			count++;
	}
	return count;
}

void ImageProcesser::drawCountedObjectDigit(int & carCount, cv::Mat & imgFrame2Copy)
{
	int intFontFace = cv::FONT_HERSHEY_COMPLEX;
	double dblFontScale = (imgFrame2Copy.rows * imgFrame2Copy.cols) / 300000.0;
	int intFontThickness = (int)round(dblFontScale * 1.5);

	cv::Size textSize = cv::getTextSize(std::to_string(carCount), intFontFace, dblFontScale, intFontThickness, 0);

	cv::Point ptTextBottomLeftPosition;

	ptTextBottomLeftPosition.x = imgFrame2Copy.cols - 1 - (int)((double)textSize.width * 1.25);
	ptTextBottomLeftPosition.y = (int)((double)textSize.height * 1.25);

	putText(imgFrame2Copy, std::to_string(carCount), ptTextBottomLeftPosition, intFontFace, dblFontScale, cv::Scalar(0.0, 0.0, 255.0), intFontThickness);

}
