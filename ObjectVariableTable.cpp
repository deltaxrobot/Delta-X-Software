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
	// create more widget
	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		if (i > ObjectVariableWidgetList->size() - 1)
		{
			ObjectVariable* ov = new ObjectVariable(i);

			ObjectVariableWidgetList->push_back(ov);

			ov->AddLayout(gridLayout, i);

			/*gridLayout->addWidget(ov->name, i, 0);
			gridLayout->addWidget(ov->xVar, i, 1);
			gridLayout->addWidget(ov->xValue, i, 2);
			gridLayout->addWidget(ov->yVar, i, 3);
			gridLayout->addWidget(ov->yValue, i, 4);
			gridLayout->addWidget(ov->aVar, i, 5);
			gridLayout->addWidget(ov->aValue, i, 6);*/
		}
	}

	for (int i = 0; i < ObjectContainer.size(); i++)
	{
		ObjectVariableWidgetList->at(i)->xValue->setText(QString::number(ObjectContainer.at(i).center.x));
		ObjectVariableWidgetList->at(i)->yValue->setText(QString::number(ObjectContainer.at(i).center.y));

		int angle = ObjectContainer.at(i).angle + 180;

		if (ObjectContainer.at(i).size.width > ObjectContainer.at(i).size.height)
		{
			angle = ObjectContainer.at(i).angle + 90;
		}

		ObjectVariableWidgetList->at(i)->aValue->setText(QString::number(angle));
	}

	/*if (ObjectContainer.size() < ObjectVariableWidgetList->size())
	{
		for (int i = ObjectContainer.size(); i < ObjectVariableWidgetList->size(); i++)
		{
			ObjectVariableWidgetList->at(i)->xValue->setText("NULL");
			ObjectVariableWidgetList->at(i)->yValue->setText("NULL");
			ObjectVariableWidgetList->at(i)->aValue->setText("NULL");
		}

		
	}*/

	while (ObjectContainer.size() < ObjectVariableWidgetList->size())
	{
		/*gridLayout->removeWidget(ObjectVariableWidgetList->last()->name);
		gridLayout->removeWidget(ObjectVariableWidgetList->last()->xVar);
		gridLayout->removeWidget(ObjectVariableWidgetList->last()->xValue);
		gridLayout->removeWidget(ObjectVariableWidgetList->last()->yVar);
		gridLayout->removeWidget(ObjectVariableWidgetList->last()->yValue);
		gridLayout->removeWidget(ObjectVariableWidgetList->last()->aVar);
		gridLayout->removeWidget(ObjectVariableWidgetList->last()->aValue);*/

		delete ObjectVariableWidgetList->last();
		ObjectVariableWidgetList->removeLast();

		/*if (ObjectVariableWidgetList->size() == 0)
		{
			QLayoutItem *child;
			while ((gridLayout->takeAt(0)) != 0) 
			{
				delete child;
			}
		}*/
	}
}

void ObjectVariableTable::DisplayDialog()
{
	dialog->show();
}
