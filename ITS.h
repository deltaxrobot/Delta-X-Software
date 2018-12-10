#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <conio.h>           
#include <string>
#include <opencv2/core/utils/trace.hpp>
#include <opencv2/dnn.hpp>/*
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>*/

#include "Blob.h"

#define ESC_KEY			27

#define SCALAR_BLACK	cv::Scalar(0.0, 0.0, 0.0)
#define SCALAR_WHITE	cv::Scalar(255.0, 255.0, 255.0)
#define SCALAR_BLUE		cv::Scalar(255.0, 0.0, 0.0)
#define SCALAR_GREEN	cv::Scalar(0.0, 200.0, 0.0)
#define SCALAR_RED		cv::Scalar(0.0, 0.0, 255.0)

enum VideoState
{
	NOT_OPEN,
	PLAYING,
	END,
	ERROR,
	LABELING,
	TRACKING,
};

using namespace cv::dnn;

class ITS
{
public:	

	ITS();
	~ITS();
	
	bool IsCountingCar = true;
	bool IsDisplayDifferenceWindow = false;
	bool IsDisplayThesholdDifferenceWindow = false;
	bool IsDisplayConvexHullWindow = false;
	bool IsDisplayInfoWindow = true;
	int ThresholdValue = 45;
	int ProccessAreaX = 0;
	int ProccessAreaY = 0;
	int ProcessAreaWidth = 880;
	int ProcessAreaHeigh = 880;
	int VideoStep = 1;
	std::string TrackingLabel = "";

	bool SetVideo(cv::VideoCapture analysisVideo);
	bool SetVideo(std::string videoName);
	void Start();
	bool IsStart();
	VideoState ITS::GetNextResultFrame(cv::Mat& outputMat);
	cv::Mat* GetTrackingRoi();

private:
	cv::VideoCapture analysisVideo = 0;
	cv::Mat currentFrame;
	cv::Mat lastFrame;
	cv::Mat infoImage;
	cv::Mat* trackingRoi = nullptr;

	bool isDetectedNewCar = false;
	int countedCarNumber = 0;
	std::vector<Blob> appearedBlobs;

	char inputKey = 0;
	bool isFirstFrame = true;
	int frameOrder = 1;

	bool isStart = false;
	std::string videoName = "";
	cv::Rect processArea;

	VideoState videoState;

	std::vector<Blob> currentFrameBlobs;

	cv::Mat lastFrameCopy;
	cv::Mat currentFrameCopy;
	cv::Mat diffImage;
	cv::Mat thresDiffImage;
	cv::Mat thresholdDiffImageCopy;
	cv::Mat questionableHullImages;

	void initProcessWindows();
	void displayProcessWindows();
	void dilateWhiteSpots(cv::Mat& thresImage, int zoomIndex);
	void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
	void updateAppearedBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
	void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
	double getDistance(cv::Point point1, cv::Point point2);
	bool isBlobsCrossedTheLine(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount);
	void drawCarDetectionSignal(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy, int &carCount, int frameCount);
	void drawCountedCarDigit(int &carCount, cv::Mat &imgFrame2Copy);
	bool isNotCollision(Blob currentBlob, std::vector<Blob> blobs);
	int getCarNumber(std::vector<Blob> &blobs);
	double round(double d);
};