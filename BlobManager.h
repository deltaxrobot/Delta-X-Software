#pragma once

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "UnityTool.h"

class BlobManager : public QObject
{
	Q_OBJECT

public:
	BlobManager(QObject *parent);
	~BlobManager();

	void AddNewObject(cv::RotatedRect object);
	void SetApproximateValue(cv::Point3d approVal);
	std::vector<cv::RotatedRect> ObjectContainer;

public slots:
	void UpdateNewPositionObjects(float deltaX, float deltaY);
	void RemoveOldestObject();
	void RemoveAllDetectObjects();

signals:
	void NewUpdateObjectPosition(QString name, int value);

private:
	bool isNewObject(cv::RotatedRect object);

	cv::Point3i approValue;
};
