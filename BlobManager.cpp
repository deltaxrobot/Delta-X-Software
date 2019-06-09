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
}

bool BlobManager::isNewObject(cv::RotatedRect object)
{
	for each (cv::RotatedRect oldObj in ObjectContainer)
	{
		float errX = abs(oldObj.center.x - object.center.x);
		float errY = abs(oldObj.center.y - object.center.y);
		float errA = abs(oldObj.angle - object.angle);
		
		if (errX < approValue.x * 4 && errY < approValue.y * 4 && errA < approValue.z * 4)
		{
			return false;
		}
	}
	return true;
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

	emit NewUpdateObjectPosition(QString("#1010"), oldestObj.center.x);
	emit NewUpdateObjectPosition(QString("#1011"), oldestObj.center.y);
	emit NewUpdateObjectPosition(QString("#1012"), oldestObj.angle);
}
