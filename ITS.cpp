#include "ITS.h"

ITS::ITS()
{

}

ITS::~ITS()
{

}

double ITS::round(double d)
{
	return floor(d + 0.5);
}

bool ITS::SetVideo(cv::VideoCapture analysisVideo)
{
	this->videoName = "No Name";
	this->analysisVideo = cv::VideoCapture(analysisVideo);

	//system("cls");

	if (!this->analysisVideo.isOpened())
	{
		//std::cout << "\n Error reading video file \n\n";
		return false;
	}
	else
	{
		//std::cout << "\n Video can be reading \n\n";
		return true;
	}
}

bool ITS::SetVideo(std::string videoName)
{
	this->videoName = videoName;
	analysisVideo = cv::VideoCapture(videoName);

	//system("cls");

	if (!analysisVideo.isOpened())
	{
		//std::cout << "\n Error reading video file \n\n";
		return false;
	}
	else
	{
		//std::cout << "\n Video can be reading \n\n";
		return true;
	}
}

void ITS::Start()
{
	//initProcessWindows();

	analysisVideo >> lastFrame;
	analysisVideo >> currentFrame;

	processArea.x = ProccessAreaX;
	processArea.y = ProccessAreaY;
	
	processArea.width = lastFrame.size().width * 3 / 5;
	processArea.height = lastFrame.size().height;

	isStart = true;
}

bool ITS::IsStart()
{
	return isStart;
}

VideoState ITS::GetNextResultFrame(cv::Mat& outputMat  )
{
	videoState = PLAYING;

	if (this->videoName == "")
	{
		videoState = NOT_OPEN;
		return videoState;
	}

	if (isStart == false)
		Start();

	if (!analysisVideo.isOpened())
	{
		videoState = ERROR;
		return videoState;
	}

	currentFrameBlobs.clear();
	lastFrameCopy = lastFrame.clone();
	currentFrameCopy = currentFrame.clone();

	lastFrameCopy = lastFrameCopy(processArea);
	currentFrameCopy = currentFrameCopy(processArea);

	cvtColor(lastFrameCopy, lastFrameCopy, cv::COLOR_BGR2GRAY);
	cvtColor(currentFrameCopy, currentFrameCopy, cv::COLOR_BGR2GRAY);

	GaussianBlur(lastFrameCopy, lastFrameCopy, cv::Size(5, 5), 0);
	GaussianBlur(currentFrameCopy, currentFrameCopy, cv::Size(5, 5), 0);

	absdiff(lastFrameCopy, currentFrameCopy, diffImage);				// Make a difference between two frames

	threshold(diffImage, thresDiffImage, ThresholdValue, 255.0, cv::THRESH_BINARY);

	dilateWhiteSpots(thresDiffImage, 20);

	thresholdDiffImageCopy = thresDiffImage.clone();

	//-----------------------------------------------------------

	std::vector<std::vector<cv::Point>> questionableContours;

	findContours(thresholdDiffImageCopy, questionableContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> questionableHulls(questionableContours.size());

	for (unsigned int i = 0; i < questionableHulls.size(); i++)
	{
		convexHull(questionableContours[i], questionableHulls[i]);
	}

	for (auto &convexHull : questionableHulls)
	{
		Blob possibleBlob(convexHull);

		if (isNotCollision(possibleBlob, currentFrameBlobs) &&
			possibleBlob.CurrentBoundingRect.area() > 5000 &&
			possibleBlob.CurrentAspectRatio >= 0.7 &&
			possibleBlob.CurrentAspectRatio <= 2 &&
			possibleBlob.CurrentBoundingRect.width > 100 &&
			possibleBlob.CurrentBoundingRect.height > 200 &&
			possibleBlob.CurrentDiagonalSize > 60.0 &&
			(contourArea(possibleBlob.CurrentContour) / (double)possibleBlob.CurrentBoundingRect.area()) > 0.50)
		{
			currentFrameBlobs.push_back(possibleBlob);
		}
	}
	questionableHullImages = cv::Mat(thresDiffImage.size(), CV_8UC3, SCALAR_BLACK);
	questionableHulls.clear();

	for (auto &blob : currentFrameBlobs)
	{
		questionableHulls.push_back(blob.CurrentContour);
	}

	cv::drawContours(questionableHullImages, questionableHulls, -1, SCALAR_WHITE, -1);

	//-------------------------------------------

	if (isFirstFrame == true)
	{
		for (auto &currentFrameBlob : currentFrameBlobs)
		{
			appearedBlobs.push_back(currentFrameBlob);
		}
	}
	else
	{
		matchCurrentFrameBlobsToExistingBlobs(appearedBlobs, currentFrameBlobs);
	}

	infoImage = currentFrame.clone();

	//--------------------------------------------

	drawCarDetectionSignal(appearedBlobs, infoImage, countedCarNumber, frameOrder);


	countedCarNumber = getCarNumber(appearedBlobs);
	drawCountedCarDigit(countedCarNumber, infoImage);

	lastFrame = currentFrame.clone();

	//---------------------------------------

	outputMat = infoImage;
	//displayProcessWindows();

	//---------------------------------------

	if ((analysisVideo.get(cv::CAP_PROP_POS_FRAMES) + 1) < analysisVideo.get(cv::CAP_PROP_FRAME_COUNT))
	{
		analysisVideo.read(currentFrame);
	}
	else
	{
		videoState = END;
		return videoState;
	}

	isFirstFrame = false;
	frameOrder++;

	return videoState;
}

cv::Mat* ITS::GetTrackingRoi()
{
	if (trackingRoi != NULL)
		return trackingRoi;
}

void ITS::initProcessWindows()
{
	if (IsDisplayDifferenceWindow == true)
		cv::namedWindow("Difference Image", cv::WINDOW_NORMAL);

	if (IsDisplayThesholdDifferenceWindow == true)
		cv::namedWindow("Threshold Difference Image", cv::WINDOW_NORMAL);

	if (IsDisplayConvexHullWindow == true)
		cv::namedWindow("imgConvexHulls", cv::WINDOW_NORMAL);

	if (IsDisplayInfoWindow == true)
		cv::namedWindow("Current Frame", cv::WINDOW_NORMAL);
}

void ITS::displayProcessWindows()
{
	if (frameOrder % VideoStep != 0)
		return;

	if (IsDisplayDifferenceWindow == true)
		cv::imshow("Difference Image", diffImage);

	if (IsDisplayThesholdDifferenceWindow == true)
		cv::imshow("Threshold Difference Image", thresDiffImage);

	if (IsDisplayConvexHullWindow == true)
		cv::imshow("imgConvexHulls", questionableHullImages);

	if (IsDisplayInfoWindow == true)
		cv::imshow("Current Frame", infoImage);
}

void ITS::dilateWhiteSpots(cv::Mat& thresImage, int zoomIndex)
{
	for (unsigned int i = 0; i < 20; i++)
	{
		cv::dilate(thresImage, thresImage, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
	}
}

void ITS::matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs)
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

void ITS::updateAppearedBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex)
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

void ITS::addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs)
{

	currentFrameBlob.IsNotNewBlob = true;
	currentFrameBlob.IsACar = false;

	existingBlobs.push_back(currentFrameBlob);

	isDetectedNewCar = true;
}

double ITS::getDistance(cv::Point point1, cv::Point point2)
{

	int intX = abs(point1.x - point2.x);
	int intY = abs(point1.y - point2.y);

	return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

bool ITS::isBlobsCrossedTheLine(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount)
{
	bool blnAtLeastOneBlobCrossedTheLine = false;

	for (auto blob : blobs)
	{

		if (blob.IsBeingTracked == true && blob.CenterPositions.size() >= 2)
		{
			int prevFrameIndex = (int)blob.CenterPositions.size() - 2;
			int currFrameIndex = (int)blob.CenterPositions.size() - 1;

			if (blob.CenterPositions[prevFrameIndex].y > intHorizontalLinePosition && blob.CenterPositions[currFrameIndex].y <= intHorizontalLinePosition) {
				carCount++;
				blnAtLeastOneBlobCrossedTheLine = true;
			}
		}

	}

	return blnAtLeastOneBlobCrossedTheLine;
}

void ITS::drawCarDetectionSignal(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy, int &carCount, int frameCount)
{
	for (unsigned int i = 0; i < blobs.size(); i++)
	{
		if (blobs[i].IsBeingTracked == true && blobs[i].IsACar == true)
		{
			cv::Mat roi = imgFrame2Copy(blobs[i].CurrentBoundingRect);

			if (trackingRoi != nullptr)
			{
				delete trackingRoi;
			}

			trackingRoi = new cv::Mat(roi);

			if (isDetectedNewCar == true)
			{
				isDetectedNewCar = false;
				videoState = LABELING;
			}
			else
			{
				videoState = TRACKING;
			}

			rectangle(imgFrame2Copy, blobs[i].CurrentBoundingRect, cv::Scalar(0.0, 255.0, 255.0), 2);
		}
	}	
}

int ITS::getCarNumber(std::vector<Blob> &blobs) {
	int count = 0;
	for (unsigned int i = 0; i < blobs.size(); i++)
	{
		if (blobs[i].IsACar == true)
			count++;
	}
	return count;
}
void ITS::drawCountedCarDigit(int &carCount, cv::Mat &imgFrame2Copy)
{
	int intFontFace = cv::FONT_HERSHEY_SIMPLEX;
	double dblFontScale = (imgFrame2Copy.rows * imgFrame2Copy.cols) / 300000.0;
	int intFontThickness = (int)round(dblFontScale * 1.5);

	cv::Size textSize = cv::getTextSize(std::to_string(carCount), intFontFace, dblFontScale, intFontThickness, 0);

	cv::Point ptTextBottomLeftPosition;

	ptTextBottomLeftPosition.x = imgFrame2Copy.cols - 1 - (int)((double)textSize.width * 1.25);
	ptTextBottomLeftPosition.y = (int)((double)textSize.height * 1.25);

	putText(imgFrame2Copy, std::to_string(carCount), ptTextBottomLeftPosition, intFontFace, dblFontScale, cv::Scalar(0.0, 0.0, 255.0), intFontThickness);

}
bool ITS::isNotCollision(Blob currentBlob, std::vector<Blob> blobs) 
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
