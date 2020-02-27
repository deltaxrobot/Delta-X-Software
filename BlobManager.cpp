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
		ConvenyorString = QString("O") + ConvenyorString;
		Debug(ConvenyorString);
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
	ObjectContainer.clear();
	emit NewUpdateObjectPosition(QString("#1010"), NULL_NUMBER);
	emit NewUpdateObjectPosition(QString("#1011"), NULL_NUMBER);
	emit NewUpdateObjectPosition(QString("#1012"), NULL_NUMBER);
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
		else
		{
			cv::RotatedRect newObj = object;
		}
	}

	if (result == true)
	{
		cv::RotatedRect newObj = object;
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
		ConvenyorString = QString(".") + ConvenyorString;
		Debug(ConvenyorString);
	}

	cv::RotatedRect oldestObj = ObjectContainer.at(0);

	int angle = oldestObj.angle + 180;

	if (oldestObj.size.width > oldestObj.size.height)
	{
		angle = oldestObj.angle + 90;
	}
	emit NewUpdateObjectPosition(QString("#1010"), oldestObj.center.x);
	emit NewUpdateObjectPosition(QString("#1011"), oldestObj.center.y);
	emit NewUpdateObjectPosition(QString("#1012"), angle);
}
