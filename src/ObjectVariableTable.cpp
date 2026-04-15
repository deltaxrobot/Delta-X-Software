#include "ObjectVariableTable.h"

ObjectVariableTable::ObjectVariableTable(QObject *parent)
	: QObject(parent)
{
	ObjectVariableWidgetList = new QList<ObjectVariable*>();
    dialog = new QWidget();
    dialog->setWindowTitle("Object Variables");

    // Tạo QGridLayout và đưa nó vào QScrollArea
    QScrollArea *scrollArea = new QScrollArea();
    QGridLayout *gridLayout = new QGridLayout(scrollArea->viewport());
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(new QWidget());
    scrollArea->widget()->setLayout(gridLayout);

    // Đưa QScrollArea vào cửa sổ
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(scrollArea);
    dialog->setLayout(layout);

	dialog->setWindowFlags(Qt::WindowStaysOnTopHint);

    for (int i = 0; i < 100; i++)
    {
        ObjectVariable* ov = new ObjectVariable(i);
        ov->name->setText(QString::number(i));

        ObjectVariableWidgetList->push_back(ov);

        ov->AddLayout(gridLayout, i);

        connect(ov->name, &QPushButton::clicked, [=](){emit TakeObjectPosition(ov->xValue->text().toFloat(), ov->yValue->text().toFloat(), ov->aValue->text().toFloat());});
    }

    QSpacerItem* space = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(space, 101, 0);

}

ObjectVariableTable::~ObjectVariableTable()
{


}

void ObjectVariableTable::UpdateTable(QList<Object> ObjectContainer)
{
    for (int i = 0; i < ObjectContainer.size(); i++)
    {
        if (i > ObjectVariableWidgetList->size() - 1)
            break;

        if (ObjectVariableWidgetList->at(i)->IsShow == false)
            ObjectVariableWidgetList->at(i)->Show();
    }

    for (int i = 0; i < ObjectContainer.size(); i++)
    {
        if (i > ObjectVariableWidgetList->size() - 1)
            break;

        ObjectVariableWidgetList->at(i)->xValue->setText(QString::number(ObjectContainer[i].X.Real));
        ObjectVariableWidgetList->at(i)->yValue->setText(QString::number(ObjectContainer[i].Y.Real));

//		int angle = ObjectContainer.at(i).angle + 180;

//		if (ObjectContainer.at(i).size.width > ObjectContainer.at(i).size.height)
//		{
//			angle = ObjectContainer.at(i).angle + 90;``
//		}

        ObjectVariableWidgetList->at(i)->aValue->setText(QString::number(ObjectContainer[i].Angle.Real));
    }

    for (int i = ObjectContainer.size(); i < ObjectVariableWidgetList->size(); i++)
    {
        if (i > ObjectVariableWidgetList->size() - 1)
            break;

        ObjectVariableWidgetList->at(i)->Hidden();
    }
}

void ObjectVariableTable::DisplayDialog()
{
	dialog->show();
}
