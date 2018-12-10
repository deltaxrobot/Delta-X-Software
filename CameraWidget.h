#pragma once

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>


class CameraWidget : public QLabel
{
	Q_OBJECT

public:
	//the constructor is marked explicit so that we don't get any 
	// implicit conversion by passing the wrong parameter
	explicit CameraWidget(QWidget *parent = 0); //also it has a default null pointer value, so a linewidget can be created with null parameter (i.e when we don't specify the constructor parenthesis at all!)
	bool mousePressed;
	bool drawStarted;
	int selectedTool;
	//destructor is needed when we construct a object on the heap instead of stack
	// for efficient memory management
	~CameraWidget();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

public slots:
	void rectObject();
	void lineObject();

private:
	QPainter painter;
	QPainter painter2;
	QPixmap overPix;
	QPixmap mPix;
	QLine mLine;
	QRect mRect;

	QPixmap mergePixmap(QPixmap p1, QPixmap p2);
};
