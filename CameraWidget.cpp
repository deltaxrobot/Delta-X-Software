#include "CameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
	QLabel(parent)
{	
	overPix.fill(Qt::white);

	//set everything to false as nothing has started yet
	mousePressed = false;
	drawStarted = false;

	//default is line
	selectedTool = 2;

	painter.setPen(Qt::red);
	painter.setBrush(Qt::Dense2Pattern);
}


void CameraWidget::mousePressEvent(QMouseEvent* event) {
	//Mouse is pressed for the first time
	mousePressed = true;

	//set the initial line points, both are same
	if (selectedTool == 1) {
		mRect.setTopLeft(event->pos());
		mRect.setBottomRight(event->pos());
	}
	else if (selectedTool == 2) {
		mLine.setP1(event->pos());
		mLine.setP2(event->pos());
	}
}

void CameraWidget::mouseMoveEvent(QMouseEvent* event) {

	//As mouse is moving set the second point again and again
	// and update continuously
	if (event->type() == QEvent::MouseMove) {
		if (selectedTool == 1) {
			mRect.setBottomRight(event->pos());
		}
		else if (selectedTool == 2) {
			mLine.setP2(event->pos());
		}
	}

	//it calls the paintEven() function continuously
	update();
}

void CameraWidget::mouseReleaseEvent(QMouseEvent *event) {

	//When mouse is released update for the one last time
	mousePressed = false;
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

	if (mousePressed) 
	{
		if (overPix.size().height() < 50)
			overPix = QPixmap(this->size().width(), this->size().height());

		QPainter tempPainter(&overPix);

		if (selectedTool == 1)
			tempPainter.drawRect(mRect);
		else if (selectedTool == 2)
			tempPainter.drawLine(mLine);

		mPix = mergePixmap(mPix, overPix);

		painter.drawPixmap(0, 0, mPix);

		drawStarted = true;
	}
	else if (drawStarted) 
	{
		QPainter tempPainter(&mPix);

		if (selectedTool == 1)
			tempPainter.drawRect(mRect);
		else if (selectedTool == 2)
			tempPainter.drawLine(mLine);

		painter.drawPixmap(0, 0, mPix);
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
