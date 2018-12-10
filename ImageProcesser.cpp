#include "ImageProcesser.h"

ImageProcesser::ImageProcesser(QWidget *parent)
	: QWidget(parent)
{
	ParameterPanel = new HSVWindow(parent);
	connect(ParameterPanel, SIGNAL(ValueChanged(int, int, int, int, int, int)), this, SLOT(SetHSV(int, int, int, int, int, int)));
	connect(ParameterPanel, SIGNAL(ValueChanged(int)), this, SLOT(SetThreshold(int)));

	updateScreenTimer = new QTimer(this);
	connect(updateScreenTimer, SIGNAL(timeout()), this, SLOT(UpdateCameraScreen()));
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

	captureImage = cv::imread(imageName.toStdString(), cv::IMREAD_COLOR);
	
	cv::resize(captureImage, resizeImage, cv::Size(368, 207));

	UpdateLabelImage(resizeImage, lbProcessImage);
	UpdateLabelImage(resizeImage, lbResultImage);
}

void ImageProcesser::UpdateCameraScreen()
{
	camera.read(captureImage);

	float ratio = (float)captureImage.size().width / captureImage.size().height;

	cv::resize(captureImage, resizeImage, cv::Size((float)lbResultImage->size().height() * ratio, lbResultImage->size().height()));

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

void ImageProcesser::SetProcessScreenPointer(QLabel * testImage)
{
	lbProcessImage = testImage;
}

void ImageProcesser::SetResultScreenPointer(QLabel * resultImage)
{
	lbResultImage = resultImage;
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
	label->setPixmap(QPixmap::fromImage(img));
}

void ImageProcesser::postProcessing(cv::Mat processMat)
{
	if (ParameterPanel->IsInvertBinary())
		cv::bitwise_not(processMat, processMat);	

	resizeImage.copyTo(resultImage);

	paintInfo(processMat, resultImage, RED_COLOR);

	UpdateLabelImage(processMat, lbProcessImage);
	UpdateLabelImage(resultImage, lbResultImage);

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
		cv::Rect rec = boundingRect(contoursContainer[i]);
		float h = rec.height;
		float w = rec.width;
		float ratio = h / w;
		float s = w * h;

		if (s > 2000 && s < 12000 && h < 200)
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

	putText(mat, std::to_string((int)minRec.center.x) + ", " + std::to_string((int)minRec.center.y) + ", " + std::to_string((int)minRec.angle), cv::Point(minRec.center.x - 20, minRec.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.5, GREEN_COLOR, 1);

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
