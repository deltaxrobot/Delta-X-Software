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
        //ElapsedTimer.start();
        updateObjectVariable(object, ObjectContainer.size() - 1);
        //qDebug() << ElapsedTimer.elapsed();
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

        QString cmd = "";
        cmd += QString("#O%1_X=%2;").arg(i).arg(obj.center.x);
        cmd += QString("#O%1_Y=%2;").arg(i).arg(obj.center.y);
        cmd += QString("#O%1_A=%2").arg(i).arg(obj.angle);
        emit NewUpdateObjectPosition(cmd);
    }

    QString cmd = "";
    cmd += QString("#O%1_X=%2;").arg(ObjectContainer.size() - 1).arg(NULL_NUMBER);
    cmd += QString("#O%1_Y=%2;").arg(ObjectContainer.size() - 1).arg(NULL_NUMBER);
    cmd += QString("#O%1_A=%2").arg(ObjectContainer.size() - 1).arg(NULL_NUMBER);
    emit NewUpdateObjectPosition(cmd);

	ObjectContainer.erase(ObjectContainer.begin());
}

void BlobManager::RemoveAllDetectObjects()
{
	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		cv::RotatedRect obj = ObjectContainer.at(i);

        QString cmd = "";
        cmd += QString("#O%1_X=%2;").arg(i).arg(NULL_NUMBER);
        cmd += QString("#O%1_Y=%2;").arg(i).arg(NULL_NUMBER);
        cmd += QString("#O%1_A=%2").arg(i).arg(NULL_NUMBER);
        emit NewUpdateObjectPosition(cmd);
	}

    ObjectContainer.clear();
}

void BlobManager::AddNewObject(float x, float y, float w, float h)
{
    cv::RotatedRect object(cv::Point2f(x, y), cv::Size(w, h), 0);

    AddNewObject(object);
}

void BlobManager::UpdateTrackingError()
{
    QLineEdit* le = qobject_cast<QLineEdit*>(sender());

    if (le == NULL)
        return;

    TrackingError = le->text().toFloat();
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

        if (IntersectionArea > 0)
        {
            int abc = 1;
        }

        int ObjectArea = oldObj.size.height * oldObj.size.width;

        if (IntersectionArea > ObjectArea * TrackingError)
		{
//            ObjectContainer.at(i).center.x = object.center.x;
//            ObjectContainer.at(i).center.y = object.center.y;
			return false;
		}
	}
    return result;
}

void BlobManager::updateObjectVariable(cv::RotatedRect object, int id)
{
    QString cmd = "";
    cmd += QString("#O%1_X=%2;").arg(id).arg(object.center.x);
    cmd += QString("#O%1_Y=%2;").arg(id).arg(object.center.y);
    cmd += QString("#O%1_A=%2;").arg(id).arg(object.angle);
    cmd += QString("#O%1_W=%2;").arg(id).arg(object.size.width);
    cmd += QString("#O%1_H=%2;").arg(id).arg(object.size.height);
    emit NewUpdateObjectPosition(cmd);
}

void BlobManager::UpdateNewObjectMoving(float deltaX, float deltaY)
{
	if (ObjectContainer.size() == 0)
		return;

	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		ObjectContainer.at(i).center.x += deltaX;
		ObjectContainer.at(i).center.y += deltaY;
    }
	
	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		cv::RotatedRect obj = ObjectContainer.at(i);

        QString cmd = "";
        cmd += QString("#O%1_X=%2;").arg(i).arg(obj.center.x);
        cmd += QString("#O%1_Y=%2;").arg(i).arg(obj.center.y);

        emit NewUpdateObjectPosition(cmd);
	}	
}
