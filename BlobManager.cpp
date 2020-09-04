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

		float errX = abs(oldObj.center.x - object.center.x);
		float errY = abs(oldObj.center.y - object.center.y);
		float errA = abs(oldObj.angle - object.angle);
		
		if (errX < (approValue.x) && errY < (approValue.y))
		{
			oldObj.angle = object.angle;
			oldObj.center = object.center;
			oldObj.size = object.size;

			result = false;
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
