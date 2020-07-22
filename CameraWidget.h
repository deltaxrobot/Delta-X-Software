#pragma once

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <qmath.h>
#include <qpushbutton.h>

class CameraWidget : public QLabel
{
	Q_OBJECT

public:
	//the constructor is marked explicit so that we don't get any 
	// implicit conversion by passing the wrong parameter
	explicit CameraWidget(QWidget *parent = 0); //also it has a default null pointer value, so a linewidget can be created with null parameter (i.e when we don't specify the constructor parenthesis at all!)
	void InitParameter(); 
	
	bool mousePressed;
	bool drawStarted;
	int selectedTool;
	//destructor is needed when we construct a object on the heap instead of stack
	// for efficient memory management
	~CameraWidget();

signals:
	void FinishDrawObject(int x, int y, int h, int w);
	void FinishSelectProcessRegion(QPoint a, QPoint b, QPoint c, QPoint d);
	void FinishMeasureSpace(int distance);
	void FinishSelectCalibPoint(int x, int y);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

public slots:
	void rectObject();
	void lineObject();
	void circleObject();
	void selectProcessRegion();

	void ChangeCalibLineRealLength(QString value);
	void ChangeXCalibPoint(QString value);
	void ChangeYCalibPoint(QString value);
private:
	int axisDirection = 1;

	QLine xAxis;
	QLine arrow1;
	QLine arrow2;
	QPainter painter;
	QPainter painter2;
	QPixmap overPix;
	QPixmap mPix;
	QLine mLine;
	QRect mRect;
	QPoint mPoint;
	QPoint mPoints[4];
	int pointOrder = 3;

	int calibLineRealLength = 120;
	int xCalibPoint = 150;
	int yCalibPoint = 0;

	QPoint curPosInWidget;

	QPixmap mergePixmap(QPixmap p1, QPixmap p2);

	void changeToolIconInArea(QIcon icon);
};
