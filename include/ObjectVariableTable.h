#pragma once

#include <QObject>
#include <QSpacerItem>
#include <qlabel.h>
#include <QGridLayout>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "UnityTool.h"
#include "Object.h"
#include <QScrollArea>

class ObjectVariable
{
public:
	ObjectVariable(int i)
	{
		QFont font1 = QFont();
		font1.setBold(true);

		QFont font2 = QFont();
		font2.setPointSize(10);

		QFont font3 = QFont();
		font3.setItalic(true);

        name = new QPushButton(QString("Object ") + QString::number(i) + " -");
		name->setFont(font1);
//        name->setFlat(true);


        xVar = new QLabel(QString(" #O") + QString::number(i) + "_X: ");
		xVar->setFont(font3);
		xValue = new QLabel();
		xValue->setFont(font2);
        yVar = new QLabel(QString(" #O") + QString::number(i) + "_Y: ");
		yVar->setFont(font3);
		yValue = new QLabel();
		yValue->setFont(font2);
        aVar = new QLabel(QString(" #O") + QString::number(i) + "_A: ");
		aVar->setFont(font3);
		aValue = new QLabel();
		aValue->setFont(font2);
	}

	~ObjectVariable()
	{
		delete name;
		delete xVar;
		delete xValue;
		delete yVar;
		delete yValue;
		delete aVar;
		delete aValue;
	}

	void AddLayout(QGridLayout* layout, int row)
	{
		Layout = layout;

		layout->addWidget(name, row, 0);
		layout->addWidget(xVar, row, 1);
		layout->addWidget(xValue, row, 2);
		layout->addWidget(yVar, row, 3);
		layout->addWidget(yValue, row, 4);
		layout->addWidget(aVar, row, 5);
		layout->addWidget(aValue, row, 6);
	}

    void Hidden()
    {
        IsShow = false;
        name->hide();
        xVar->hide();
        xValue->hide();
        yVar->hide();
        yValue->hide();
        aVar->hide();
        aValue->hide();
    }

    void Show()
    {
        IsShow = true;
        name->show();
        xVar->show();
        xValue->show();
        yVar->show();
        yValue->show();
        aVar->show();
        aValue->show();
    }

    bool IsShow = true;
	
	QGridLayout* Layout;

    QPushButton *name;
	QLabel *xVar;
	QLabel *xValue;
	QLabel *yVar;
	QLabel *yValue;
	QLabel *aVar;
	QLabel *aValue;
};

class ObjectVariableTable : public QObject
{
	Q_OBJECT

public:
	ObjectVariableTable(QObject *parent);
	~ObjectVariableTable();

    QList<ObjectVariable*>* ObjectVariableWidgetList;

public slots:
	void DisplayDialog();
    void UpdateTable(QList<Object> ObjectContainer);

signals:
    void TakeObjectPosition(float x, float y, float angle);


private:
	QWidget* dialog;
	QGridLayout *gridLayout;

};
