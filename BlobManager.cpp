#include "BlobManager.h"

BlobManager::BlobManager(QObject *parent)
	: QObject(parent)
{
}

BlobManager::~BlobManager()
{
}

void BlobManager::AddNewObject(cv::RotatedRect object)
{
	if (isNewObject(object))
	{
		ObjectContainer.push_back(object);
		ConveyorString = QString("O") + ConveyorString;
		Debug(ConveyorString);
	}
}

void BlobManager::SetApproximateValue(cv::Point3d approVal)
{
	approValue = approVal;
}

void BlobManager::RemoveOldestObject()
{
	if (ObjectContainer.size() == 0)
		return;

	for (int i = 0; i < ObjectContainer.size() - 1; i++)
	{
		cv::RotatedRect obj = ObjectContainer.at(i + 1);

		int angle = obj.angle + 180;

		if (obj.size.width > obj.size.height)
		{
			angle = obj.angle + 90;
		}

		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_X", obj.center.x);
		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_Y", obj.center.y);
		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_A", angle);
	}

	emit NewUpdateObjectPosition(QString("#O") + QString::number(ObjectContainer.size()) + "_X", NULL_NUMBER);
	emit NewUpdateObjectPosition(QString("#O") + QString::number(ObjectContainer.size()) + "_Y", NULL_NUMBER);
	emit NewUpdateObjectPosition(QString("#O") + QString::number(ObjectContainer.size()) + "_A", NULL_NUMBER);

	ObjectContainer.erase(ObjectContainer.begin());
}

void BlobManager::RemoveAllDetectObjects()
{
	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		cv::RotatedRect obj = ObjectContainer.at(i);

		int angle = obj.angle + 180;

		if (obj.size.width > obj.size.height)
		{
			angle = obj.angle + 90;
		}

		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_X", NULL_NUMBER);
		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_Y", NULL_NUMBER);
		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_A", NULL_NUMBER);
	}

	ObjectContainer.clear();
}

bool BlobManager::isNewObject(cv::RotatedRect object)
{
	bool result = true;
	for(int i = 0; i < ObjectContainer.size(); i++)
	{
		cv::RotatedRect& oldObj = ObjectContainer.at(i);

		std::vector<cv::Point2f> IntersectionVertices;

        cv::rotatedRectangleIntersection(oldObj, object, IntersectionVertices);

		int IntersectionArea = 0;

		if (IntersectionVertices.size() > 0)
		{
			IntersectionArea = cv::contourArea(IntersectionVertices);
		}

		int ObjectArea = oldObj.size.height * oldObj.size.width;

		if (IntersectionArea > ObjectArea * 0.3f)
		{
			ObjectContainer.at(i).center.x = object.center.x;
			ObjectContainer.at(i).center.y = object.center.y;
			return false;
		}
	}
	return result;
}

void BlobManager::UpdateNewPositionObjects(float deltaX, float deltaY)
{
	if (ObjectContainer.size() == 0)
		return;

	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		ObjectContainer.at(i).center.x += deltaX;
		ObjectContainer.at(i).center.y += deltaY;
	}

	if (deltaX > 0)
	{
		ConveyorString = QString(".") + ConveyorString;
		Debug(ConveyorString);
	}
	
	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		cv::RotatedRect obj = ObjectContainer.at(i);

		int angle = obj.angle + 180;

		if (obj.size.width > obj.size.height)
		{
			angle = obj.angle + 90;
		}

		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_X", obj.center.x);
		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_Y", obj.center.y);
		emit NewUpdateObjectPosition(QString("#O") + QString::number(i + 1) + "_A", angle);
	}	
}
