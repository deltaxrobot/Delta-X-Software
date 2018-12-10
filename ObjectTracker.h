#pragma once

#include <QObject>

class ObjectTracker : public QObject
{
	Q_OBJECT

public:
	ObjectTracker(QObject *parent);
	~ObjectTracker();
};
