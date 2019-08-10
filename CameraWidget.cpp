#include "CameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
	QLabel(parent)
{	
	overPix.fill(Qt::white);

	//set everything to false as nothing has started yet
	mousePressed = false;
	drawStarted = false;

	//default is line
	selectedTool = 1;

	painter.setPen(Qt::red);
	painter.setBrush(Qt::Dense2Pattern);

	//InitParameter();
}

void CameraWidget::mousePressEvent(QMouseEvent* event) {
	//Mouse is pressed for the first time
	mousePressed = true;

	//set the initial line points, both are same
	if (selectedTool == 1)
	{
		mRect.setTopLeft(event->pos());
		mRect.setBottomRight(event->pos());
		pointOrder = 0;
	}
	else if (selectedTool == 2)
	{
		mLine.setP1(event->pos());
		mLine.setP2(event->pos());
		pointOrder = 0;
	}
	else if (selectedTool == 3)
	{
		mPoint = event->pos();
		pointOrder = 0;

		emit FinishSelectCalibPoint(mPoint.x(), mPoint.y());
	}
	else if (selectedTool == 4)
	{
		pointOrder++;
		if (pointOrder > 3)
		{
			pointOrder = 0;
		}
		mPoints[pointOrder] = event->pos();

		if (pointOrder == 3)
		{
			emit FinishSelectProcessRegion(mPoints[0], mPoints[1], mPoints[2], mPoints[3]);
		}
	}
}

void CameraWidget::mouseMoveEvent(QMouseEvent* event) {

	//As mouse is moving set the second point again and again
	// and update continuously
	if (event->type() == QEvent::MouseMove) 
	{
		if (selectedTool == 1) 
		{
			mRect.setBottomRight(event->pos());
		}
		else if (selectedTool == 2) 
		{
			mLine.setP2(event->pos());
		}
		else if (selectedTool == 3)
		{
			mPoint = event->pos();
		}
	}

	//it calls the paintEven() function continuously
	update();
}

void CameraWidget::mouseReleaseEvent(QMouseEvent *event) {

	//When mouse is released update for the one last time
	mousePressed = false;
	if (selectedTool == 1)
		emit FinishDrawObject(mRect.x(), mRect.y(), mRect.height(), mRect.width());
	if (selectedTool == 2)
		emit FinishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
	update();
}

void CameraWidget::paintEvent(QPaintEvent *event) 
{
	QLabel::paintEvent(event);

	const QPixmap* curPix = this->pixmap();

	if (curPix == NULL)
		return;
	
	mPix = *curPix;

	painter.begin(this);

	QPainter tempPainter(&mPix);
	tempPainter.setPen(Qt::red);

	if (pointOrder > 0)
	{
		tempPainter.setPen(Qt::green);

		for (int i = 0; i < pointOrder; i++)
		{
			tempPainter.drawLine(mPoints[i], mPoints[i + 1]);
		}

		if (pointOrder == 3)
			tempPainter.drawLine(mPoints[3], mPoints[0]);

		tempPainter.setPen(Qt::red);
	}

	tempPainter.drawLine(mLine);
	tempPainter.setPen(QPen(Qt::red, 3));
	tempPainter.drawPoint(mPoint);
	tempPainter.drawEllipse(mPoint, 10, 10);

	painter.drawPixmap(0, 0, mPix);

	tempPainter.setPen(QPen(Qt::blue, 1));

	if (mousePressed) 
	{
		//if (overPix.size().height() < 50)
		//overPix = QPixmap(this->size().width(), this->size().height());
				
		if (selectedTool == 1)
			tempPainter.drawRect(mRect);
		else if (selectedTool == 2)
			tempPainter.drawLine(mLine);
		
		tempPainter.drawPoint(mPoint);
		tempPainter.drawEllipse(mPoint, 10, 10);
			
		//mPix = mergePixmap(mPix, overPix);

		painter.drawPixmap(0, 0, mPix);

		drawStarted = true;
	}
	else if (drawStarted)
	{
		
	}

	painter.end();	
}

CameraWidget::~CameraWidget()
{
}
//only two button is on the ui btnLine and btnRect
void CameraWidget::lineObject()
{
	selectedTool = 2;
}

void CameraWidget::circleObject()
{
	selectedTool = 3;
}

void CameraWidget::selectProcessRegion()
{
	selectedTool = 4;
}

void CameraWidget::InitParameter()
{
	mLine.setP1(QPoint(34, 6));
	mLine.setP2(QPoint(324, 8));

	mRect.setTopLeft(QPoint(0, 0));
	mRect.setBottomRight(QPoint(57, 127));

	mPoint.setX(326);
	mPoint.setY(64);

	mPoints[0] = QPoint(34, 0);
	mPoints[1] = QPoint(38, 300);
	mPoints[2] = QPoint(330, 300);
	mPoints[3] = QPoint(330, 0);

	emit FinishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
	emit FinishSelectCalibPoint(mPoint.x(), mPoint.y());
	emit FinishDrawObject(mRect.x(), mRect.y(), mRect.height(), mRect.width());
	emit FinishSelectProcessRegion(mPoints[0], mPoints[1], mPoints[2], mPoints[3]);

	update();
}

QPixmap CameraWidget::mergePixmap(QPixmap p1, QPixmap p2)
{
	QImage q1 = p1.toImage();
	QImage q2 = p2.toImage();
	QImage q3(q1.width(), q1.height(), QImage::Format_RGB888);
	QPixmap p3;

	for (int y = 0; y < q1.height(); y++)
	{
		for (int x = 0; x < q1.width(); x++)
		{
			if (q2.pixelColor(x, y) == Qt::white)
				q3.setPixelColor(x, y, q1.pixelColor(x, y));
			else
				q3.setPixelColor(x, y, q2.pixelColor(x, y));
		}
	}

	p3 = QPixmap::fromImage(q3);

	return p3;
}

void CameraWidget::rectObject()
{
	selectedTool = 1;
}
