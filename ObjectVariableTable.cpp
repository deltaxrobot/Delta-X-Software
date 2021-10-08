#include "ObjectVariableTable.h"

ObjectVariableTable::ObjectVariableTable(QObject *parent)
	: QObject(parent)
{
	ObjectVariableWidgetList = new QList<ObjectVariable*>();

	dialog = new QWidget();
	dialog->setWindowTitle("Object Variables");
	gridLayout = new QGridLayout();
	dialog->setLayout(gridLayout);

	dialog->setWindowFlags(Qt::WindowStaysOnTopHint);
}

ObjectVariableTable::~ObjectVariableTable()
{


}

void ObjectVariableTable::UpdateTable(std::vector<cv::RotatedRect> ObjectContainer)
{
	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		if (i > ObjectVariableWidgetList->size() - 1)
		{
			ObjectVariable* ov = new ObjectVariable(i);

			ObjectVariableWidgetList->push_back(ov);

			ov->AddLayout(gridLayout, i);
		}
	}

	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		ObjectVariableWidgetList->at(i)->xValue->setText(QString::number(ObjectContainer.at(i).center.x));
		ObjectVariableWidgetList->at(i)->yValue->setText(QString::number(ObjectContainer.at(i).center.y));

//		int angle = ObjectContainer.at(i).angle + 180;

//		if (ObjectContainer.at(i).size.width > ObjectContainer.at(i).size.height)
//		{
//			angle = ObjectContainer.at(i).angle + 90;
//		}

        ObjectVariableWidgetList->at(i)->aValue->setText(QString::number(ObjectContainer.at(i).angle));
	}

	while (ObjectContainer.size() < ObjectVariableWidgetList->size())
	{
		delete ObjectVariableWidgetList->last();
		ObjectVariableWidgetList->removeLast();
	}
}

void ObjectVariableTable::DisplayDialog()
{
	dialog->show();
}
