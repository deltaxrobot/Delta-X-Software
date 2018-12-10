#include "Blob.h"

Blob::Blob(std::vector<cv::Point> _contour)
{

    CurrentContour = _contour;

	CurrentBoundingRect = boundingRect(CurrentContour);

	cv::Point currentCenter;

	currentCenter.x = (CurrentBoundingRect.x + CurrentBoundingRect.x + CurrentBoundingRect.width) / 2;
	currentCenter.y = (CurrentBoundingRect.y + CurrentBoundingRect.y + CurrentBoundingRect.height) / 2;

	CenterPositions.push_back(currentCenter);

	CurrentDiagonalSize = sqrt(pow(CurrentBoundingRect.width, 2) + pow(CurrentBoundingRect.height, 2));

	CurrentAspectRatio = (float)CurrentBoundingRect.width / (float)CurrentBoundingRect.height;

	IsBeingTracked = true;
	IsNotNewBlob = true;

	NonMatchFrameNumber = 0;
}

void Blob::PredictNextPosition(void) 
{

    int numPositions = (int)CenterPositions.size();

    if (numPositions == 1) 
	{
        PredictedNextPosition.x = CenterPositions.back().x;
        PredictedNextPosition.y = CenterPositions.back().y;
    }
    else if (numPositions == 2) 
	{
        int deltaX = CenterPositions[1].x - CenterPositions[0].x;
        int deltaY = CenterPositions[1].y - CenterPositions[0].y;

        PredictedNextPosition.x = CenterPositions.back().x + deltaX;
        PredictedNextPosition.y = CenterPositions.back().y + deltaY;
    }
    else if (numPositions == 3)
	{
        int sumOfXChanges = ((CenterPositions[2].x - CenterPositions[1].x) * 2) +
            ((CenterPositions[1].x - CenterPositions[0].x) * 1);

        int deltaX = (int)round((float)sumOfXChanges / 3.0);

        int sumOfYChanges = ((CenterPositions[2].y - CenterPositions[1].y) * 2) +
            ((CenterPositions[1].y - CenterPositions[0].y) * 1);

        int deltaY = (int)round((float)sumOfYChanges / 3.0);

        PredictedNextPosition.x = CenterPositions.back().x + deltaX;
        PredictedNextPosition.y = CenterPositions.back().y + deltaY;
    }
    else if (numPositions == 4) 
	{
        int sumOfXChanges = ((CenterPositions[3].x - CenterPositions[2].x) * 3) +
            ((CenterPositions[2].x - CenterPositions[1].x) * 2) +
            ((CenterPositions[1].x - CenterPositions[0].x) * 1);

        int deltaX = (int)round((float)sumOfXChanges / 6.0);

        int sumOfYChanges = ((CenterPositions[3].y - CenterPositions[2].y) * 3) +
            ((CenterPositions[2].y - CenterPositions[1].y) * 2) +
            ((CenterPositions[1].y - CenterPositions[0].y) * 1);

        int deltaY = (int)round((float)sumOfYChanges / 6.0);

        PredictedNextPosition.x = CenterPositions.back().x + deltaX;
        PredictedNextPosition.y = CenterPositions.back().y + deltaY;
    }
    else if (numPositions >= 5) 
	{

        int sumOfXChanges = ((CenterPositions[numPositions - 1].x - CenterPositions[numPositions - 2].x) * 4) +
			((CenterPositions[numPositions - 2].x - CenterPositions[numPositions - 3].x) * 3) +
			((CenterPositions[numPositions - 3].x - CenterPositions[numPositions - 4].x) * 2) +
			((CenterPositions[numPositions - 4].x - CenterPositions[numPositions - 5].x) * 1);

        int deltaX = (int)round((float)sumOfXChanges / 10.0);

        int sumOfYChanges = ((CenterPositions[numPositions - 1].y - CenterPositions[numPositions - 2].y) * 4) +
            ((CenterPositions[numPositions - 2].y - CenterPositions[numPositions - 3].y) * 3) +
            ((CenterPositions[numPositions - 3].y - CenterPositions[numPositions - 4].y) * 2) +
            ((CenterPositions[numPositions - 4].y - CenterPositions[numPositions - 5].y) * 1);

        int deltaY = (int)round((float)sumOfYChanges / 10.0);

        PredictedNextPosition.x = CenterPositions.back().x + deltaX;
        PredictedNextPosition.y = CenterPositions.back().y + deltaY;
    }
    else 
	{
        
    }
}

double Blob::Round(double d)
{
	return floor(d + 0.5);
}

bool Blob::IsEqual(Blob b) {
	if (this->CurrentDiagonalSize == b.CurrentDiagonalSize && this->CurrentAspectRatio == b.CurrentAspectRatio)
		return true;
	else
		return false;
}