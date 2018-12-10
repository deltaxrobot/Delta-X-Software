
#ifndef MY_BLOB
#define MY_BLOB

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class Blob 
{
public:
	std::string Name = "";

    std::vector<cv::Point> CurrentContour;

    cv::Rect CurrentBoundingRect;

	std::vector<cv::Point> CenterPositions;

    double CurrentDiagonalSize;
    double CurrentAspectRatio;

    bool IsNotNewBlob;

    bool IsBeingTracked;
	bool IsACar;
	int countMatch;



    int NonMatchFrameNumber;
	cv::String BlobType;
	cv::Point PredictedNextPosition;

    Blob(std::vector<cv::Point> _contour);
    void PredictNextPosition(void);

	double Round(double d);
	bool IsEqual(Blob b);
};

#endif    // MY_BLOB
