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
		pointOrder = -1;
	}
	else if (selectedTool == 2)
	{
		mLine.setP1(event->pos());
		mLine.setP2(event->pos());
		pointOrder = -1;
	}
	else if (selectedTool == 3)
	{
		mPoint = event->pos();
		pointOrder = -1;

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

void CameraWidget::mouseMoveEvent(QMouseEvent* event) 
{	
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

	tempPainter.setPen(QPen(Qt::red, 5));
	tempPainter.drawPoint(mPoints[0]);
	tempPainter.drawPoint(mPoints[1]);
	tempPainter.drawPoint(mPoints[2]);
	tempPainter.drawPoint(mPoints[3]);

	tempPainter.setPen(QPen(Qt::red, 1));

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
	
	if (pointOrder == -1)
	{
		tempPainter.setPen(Qt::green);

		for (int i = 0; i < 3; i++)
		{
			tempPainter.drawLine(mPoints[i], mPoints[i + 1]);
		}

		tempPainter.drawLine(mPoints[3], mPoints[0]);

		tempPainter.setPen(Qt::red);
	}

	tempPainter.drawLine(mLine);
	tempPainter.setPen(QPen(Qt::red, 2));

	//------ Display calib point ------------
	
	tempPainter.drawText(QPoint(mPoint.x() + 10, mPoint.y()), QString("x=") + QString::number(xCalibPoint) + ", y=" + QString::number(yCalibPoint) + " (mm)");

	tempPainter.drawPoint(mPoint);
	tempPainter.drawEllipse(mPoint, 5, 5);

	//------ Display calib length ------------

	int xText = (mLine.p1().x() + mLine.p2().x()) / 2;
	int yText = (mLine.p1().y() + mLine.p2().y()) / 2 - 10;

	tempPainter.drawText(QPoint(xText, yText), QString::number(calibLineRealLength) + " mm");

	//------ Display cursor center -----------

	tempPainter.setPen(QPen(Qt::red, 5));

	curPosInWidget = mapFromGlobal(QCursor::pos());
	tempPainter.drawPoint(curPosInWidget);

	//

	painter.drawPixmap(0, 0, mPix);

	tempPainter.setPen(QPen(Qt::red, 1));

	if (mousePressed) 
	{
		//if (overPix.size().height() < 50)
		//overPix = QPixmap(this->size().width(), this->size().height());
				
		if (selectedTool == 1)
			tempPainter.drawRect(mRect);
		else if (selectedTool == 2)
			tempPainter.drawLine(mLine);
		
		tempPainter.drawPoint(mPoint);
		tempPainter.drawEllipse(mPoint, 5, 5);
			
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

	QPushButton* bt = qobject_cast<QPushButton*>(sender());
	changeToolIconInArea(bt->icon());
}

void CameraWidget::circleObject()
{
	selectedTool = 3;

	QPushButton* bt = qobject_cast<QPushButton*>(sender());
	changeToolIconInArea(bt->icon());
}

void CameraWidget::selectProcessRegion()
{
	selectedTool = 4;

	setCursor(Qt::ArrowCursor);
}

void CameraWidget::ChangeCalibLineRealLength(QString value)
{
	calibLineRealLength = value.toInt();
}

void CameraWidget::ChangeXCalibPoint(QString value)
{
	xCalibPoint = value.toInt();
}

void CameraWidget::ChangeYCalibPoint(QString value)
{
	yCalibPoint = value.toInt();
}

void CameraWidget::InitParameter()
{
	mLine.setP1(QPoint(100, 50));
	mLine.setP2(QPoint(250, 50));

	mRect.setTopLeft(QPoint(0, 0));
	mRect.setBottomRight(QPoint(57, 127));

	mPoint.setX(166);
	mPoint.setY(245);

	mPoints[0] = QPoint(40, 20);
	mPoints[1] = QPoint(40, 280);
	mPoints[2] = QPoint(320, 280);
	mPoints[3] = QPoint(320, 20);

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

void CameraWidget::changeToolIconInArea(QIcon icon)
{
	QPixmap pm = icon.pixmap(40, 40);

	QCursor cursorTarget = QCursor(pm);
	setCursor(cursorTarget);
}

void CameraWidget::rectObject()
{
	selectedTool = 1;

	QPushButton* bt = qobject_cast<QPushButton*>(sender());
	changeToolIconInArea(bt->icon());
}
