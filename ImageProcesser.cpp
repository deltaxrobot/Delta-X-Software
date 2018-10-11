#include "ImageProcesser.h"

ImageProcesser::ImageProcesser(QWidget *parent)
	: QWidget(parent)
{
	HSVPanel = new HSVWindow(parent);
	connect(HSVPanel, SIGNAL(ValueChanged(int, int, int, int, int, int)), this, SLOT(SetHSV(int, int, int, int, int, int)));
	connect(HSVPanel, SIGNAL(ValueChanged(int)), this, SLOT(SetThreshold(int)));
}

ImageProcesser::~ImageProcesser()
{
}

void ImageProcesser::SetProcessScreenPointer(QLabel * testImage)
{
	lbProcessImage = testImage;
}

void ImageProcesser::SetResultScreenPointer(QLabel * resultImage)
{
	lbResultImage = resultImage;
}

void ImageProcesser::SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV)
{
	cv::Mat processMat = processImageBGR.clone();

	cvtColor(processImageBGR, processMat, CV_BGR2HSV);

	cv::Scalar minScalar(minH, minS, minV);
	cv::Scalar maxScalar(maxH, maxS, maxV);

	cv::inRange(processMat, minScalar, maxScalar, processMat);

	if (HSVPanel->IsInvertBinary())
		cv::bitwise_not(processMat, processMat);

	updateProcessScreen(processMat);

	processImageBGR.copyTo(resultImageBGR);

	paintInfo(processMat, resultImageBGR, RED_COLOR);

	updateResultScreen(resultImageBGR);
}

void ImageProcesser::SetThreshold(int value)
{
	cv::Mat processMat = processImageBGR.clone();

	cvtColor(processImageBGR, processMat, CV_BGR2GRAY);

	cv::threshold(processMat, processMat, value, 255, CV_THRESH_BINARY);

	if (HSVPanel->IsInvertBinary())
		cv::bitwise_not(processMat, processMat);

	updateProcessScreen(processMat);


	processImageBGR.copyTo(resultImageBGR);

	paintInfo(processMat, resultImageBGR, RED_COLOR);

	updateResultScreen(resultImageBGR);
}

void ImageProcesser::OpenHSVPanel()
{	
	HSVPanel->exec();
}

void ImageProcesser::updateProcessScreen(cv::Mat bgrMat)
{
	QImage img = ImageTool::cvMatToQImage(bgrMat);
	lbProcessImage->setPixmap(QPixmap::fromImage(img));
}

void ImageProcesser::updateResultScreen(cv::Mat bgrMat)
{
	QImage img = ImageTool::cvMatToQImage(bgrMat);
	lbResultImage->setPixmap(QPixmap::fromImage(img));
}

void ImageProcesser::paintInfo(cv::Mat input, cv::Mat output, cv::Scalar color)
{
	std::vector<std::vector<cv::Point> > contoursContainer;
	findContours(input, contoursContainer, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	for (size_t i = 0; i < contoursContainer.size(); i++)
	{
		cv::Rect rec = boundingRect(contoursContainer[i]);
		float h = rec.height;
		float w = rec.width;
		float ratio = h / w;
		float s = w * h;

		if (s > 3000 && s < 12000)
		{
			//rectangle(output, rec, color, 1);
			drawMinRec(output, contoursContainer[i], BLUE_COLOR);
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

	return minRec.angle;
}

void ImageProcesser::LoadTestImage()
{
	QString imageName;
	imageName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

	if (imageName == "")
		return;

	processImageBGR = cv::imread(imageName.toStdString(), CV_LOAD_IMAGE_COLOR);		
	cv::resize(processImageBGR, processImageBGR, cv::Size(368, 207));

	updateProcessScreen(processImageBGR);
}

