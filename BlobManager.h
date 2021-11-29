#pragma once

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "UnityTool.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLineEdit>

class BlobManager : public QObject
{
	Q_OBJECT

public:
	BlobManager(QObject *parent);
	~BlobManager();

	void AddNewObject(cv::RotatedRect object);
	void SetApproximateValue(cv::Point3d approVal);

	int VisibleObjectNumber = 0;
	std::vector<cv::RotatedRect> ObjectContainer;

    float TrackingError = 0.3;

public slots:
    void UpdateNewObjectMoving(float deltaX, float deltaY);
	void RemoveOldestObject();
	void RemoveAllDetectObjects();
    void AddNewObject(float x, float y, float w, float h);
    void UpdateTrackingError();

signals:
	void NewUpdateObjectPosition(QString name, float value);
    void NewUpdateObjectPosition(QString cmd);
private:
	bool isNewObject(cv::RotatedRect object);
    void updateObjectVariable(cv::RotatedRect object, int id);

	cv::Point3i approValue;
};
