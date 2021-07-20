#include "CameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
	QLabel(parent)
{	
	overPix.fill(Qt::white);

	//set everything to false as nothing has started yet
	mousePressed = false;
	drawStarted = false;

	selectedTool = 0;

	painter.setPen(Qt::red);
	painter.setBrush(Qt::Dense2Pattern);

	InitParameter();
}

void CameraWidget::InitParameter()
{
	mLine.setP1(QPoint(100, 80));
	mLine.setP2(QPoint(250, 80));

	mRect.setTopLeft(QPoint(0, 0));
	mRect.setBottomRight(QPoint(57, 127));

	mPoint.setX(150);
	mPoint.setY(230);

	transformPoints[0] = QPoint(100, 100);
	transformPoints[1] = QPoint(100, 200);
	transformPoints[2] = QPoint(200, 200);
	transformPoints[3] = QPoint(200, 100);

	PselectedRectangle.setTopLeft(QPoint(40, 40));
	PselectedRectangle.setBottomRight(QPoint(300, 250));

	emit FinishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
	emit FinishSelectCalibPoint(mPoint.x(), mPoint.y());
	emit FinishDrawObject(mRect.x(), mRect.y(), mRect.height(), mRect.width());
	emit FinishSelectPerspectivePoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
	emit FinishSelectProcessRectangle(PselectedRectangle);
	emit FinishSelectCalibLine(mLine.p1(), mLine.p2());

	update();
}

void CameraWidget::ChangeSize(int w, int h)
{
	float ratio = (float)w / geometry().width();

	// Update new values for calib points
	mLine.setLine(mLine.x1() * ratio, mLine.y1() * ratio, mLine.x2() * ratio, mLine.y2() * ratio);

	mPoint = mPoint * ratio;

	PselectedRectangle.setRect(PselectedRectangle.x() * ratio, PselectedRectangle.y() * ratio, PselectedRectangle.width() * ratio, PselectedRectangle.height() * ratio);

	mRect.setRect(mRect.x() * ratio, mRect.y() * ratio, mRect.width() * ratio, mRect.height() * ratio);
	
	transformPoints[0] = transformPoints[0] * ratio;
	transformPoints[1] = transformPoints[1] * ratio;
	transformPoints[2] = transformPoints[2] * ratio;
	transformPoints[3] = transformPoints[3] * ratio;

	// 
	QRect size = geometry();
	size.setWidth(w);
	size.setHeight(h);
	setGeometry(size);

	QRect parrentSize = parentWidget()->geometry();
	parrentSize.setWidth(w);
	parrentSize.setHeight(h);
	parentWidget()->setGeometry(parrentSize);

	emit SizeChanged();

	emit FinishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
	emit FinishSelectCalibPoint(mPoint.x(), mPoint.y());
	emit FinishDrawObject(mRect.x(), mRect.y(), mRect.height(), mRect.width());
	emit FinishSelectPerspectivePoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
	emit FinishSelectProcessRectangle(PselectedRectangle);
	emit FinishSelectCalibLine(mLine.p1(), mLine.p2());
}

void CameraWidget::mousePressEvent(QMouseEvent* event) 
{	
	if (event->buttons() == Qt::RightButton)
	{
		selectedTool = 0;
		setCursor(Qt::ArrowCursor);
	}

	mousePressed = true;

	// ---------Catch event: adjusting transform points -------------
	if (IsPerspectiveEnable == false)
	{
		transPointOrder = -1;
		for (int i = 0; i < 4; i++)
		{
			if (abs(transformPoints[i].x() - event->pos().x()) < 5 && abs(transformPoints[i].y() - event->pos().y()) < 5)
			{
				transPointOrder = i;
				lastSelectedTool = selectedTool;
				lastCursorIcon = cursor().pixmap();

				selectPerspectiveRectangle();

				break;
			}
		}
	}

	// -----------Catch event: adjusting proessing rectangle -------------
	processPointOrder = -1;
	if (abs(PselectedRectangle.topLeft().x() - event->pos().x()) < 5 && abs(PselectedRectangle.topLeft().y() - event->pos().y()) < 5)
	{
		processPointOrder = 1;
		
		lastSelectedTool = selectedTool;
		lastCursorIcon = cursor().pixmap();

		selectProcessRectangle();
	}

	if (abs(PselectedRectangle.bottomRight().x() - event->pos().x()) < 5 && abs(PselectedRectangle.bottomRight().y() - event->pos().y()) < 5)
	{
		processPointOrder = 2;
		lastSelectedTool = selectedTool;
		lastCursorIcon = cursor().pixmap();

		selectProcessRectangle();
	}

	//------------------------	
	if (selectedTool == 1)
	{
		mRect.setTopLeft(event->pos());
		mRect.setBottomRight(event->pos());
	}
	if (IsMeasureDisplayEnable == true)
	{
		if (selectedTool == 2)
		{
			mLine.setP1(event->pos());
			mLine.setP2(event->pos());

			emit FinishSelectCalibLine(mLine.p1(), mLine.p2());
		}
		if (selectedTool == 3)
		{
			mPoint = event->pos();

			emit FinishSelectCalibPoint(mPoint.x(), mPoint.y());
		}
	}	
}

void CameraWidget::mouseMoveEvent(QMouseEvent* event) 
{		
	if (event->type() == QEvent::MouseMove) 
	{	
		if (selectedTool == 1) 
		{
			mRect.setBottomRight(event->pos());
		}
		if (IsMeasureDisplayEnable == true)
		{
			if (selectedTool == 2)
			{
				mLine.setP2(event->pos());
				emit FinishSelectCalibLine(mLine.p1(), mLine.p2());
			}

			if (selectedTool == 3)
			{
				mPoint = event->pos();
			}
		}
		
		if (selectedTool == 4)
		{
			if (transPointOrder > -1)
			{
				transformPoints[transPointOrder] = event->pos();
				emit FinishSelectPerspectivePoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
			}
		}

		if (selectedTool == 5)
		{
			if (processPointOrder == 1)
			{
				PselectedRectangle.setTopLeft(QPoint(event->pos()));
			}
			else if (processPointOrder == 2)
			{
				PselectedRectangle.setBottomRight(QPoint(event->pos()));
			}

			FinishSelectProcessRectangle(PselectedRectangle);
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
	if (IsMeasureDisplayEnable == true)
	{
		if (selectedTool == 2)
			emit FinishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
	}
	
	if (selectedTool == 4)
	{
		selectedTool = lastSelectedTool;
		setCursor(QCursor(lastCursorIcon));
	}
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

	//------ Display cursor center -----------

	tempPainter.setPen(QPen(Qt::red, 5));

	curPosInWidget = mapFromGlobal(QCursor::pos());
	tempPainter.drawPoint(curPosInWidget);

	//

	painter.drawPixmap(0, 0, mPix);

	tempPainter.setPen(QPen(Qt::red, 1));

	if (mousePressed) 
	{				
		if (selectedTool == 1)
		{
			tempPainter.drawRect(mRect);
		}

		painter.drawPixmap(0, 0, mPix);

		drawStarted = true;
	}

	painter.end();	
}

CameraWidget::~CameraWidget()
{

}

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

void CameraWidget::selectPerspectiveRectangle()
{
	selectedTool = 4;

	setCursor(Qt::ArrowCursor);
}

void CameraWidget::selectProcessRectangle()
{
	selectedTool = 5;

	setCursor(Qt::ArrowCursor);
}

void CameraWidget::noTool()
{
	selectedTool = 0;

	setCursor(Qt::ArrowCursor);
}

void CameraWidget::SaveSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
	
	settings.setValue("line", mLine);
	settings.setValue("object", mRect);
	settings.setValue("point", mPoint);
	settings.setValue("transpoint1", transformPoints[0]);
	settings.setValue("transpoint2", transformPoints[1]);
	settings.setValue("transpoint3", transformPoints[2]);
	settings.setValue("transpoint4", transformPoints[3]);

	settings.setValue("rect", PselectedRectangle);
}

void CameraWidget::LoadSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

	mLine = settings.value("line").toLine();

	mRect = settings.value("object").toRect();

	mPoint = settings.value("point").toPoint();

	transformPoints[0] = settings.value("transpoint1").toPoint();
	transformPoints[1] = settings.value("transpoint2").toPoint();
	transformPoints[2] = settings.value("transpoint3").toPoint();
	transformPoints[3] = settings.value("transpoint4").toPoint();

	PselectedRectangle = settings.value("rect").toRect();

	emit FinishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
	emit FinishSelectCalibPoint(mPoint.x(), mPoint.y());
	emit FinishDrawObject(mRect.x(), mRect.y(), mRect.height(), mRect.width());
	emit FinishSelectPerspectivePoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
	emit FinishSelectProcessRectangle(PselectedRectangle);
	emit FinishSelectCalibLine(mLine.p1(), mLine.p2());
}

void CameraWidget::ChangeCalibPoint()
{
    emit FinishSelectCalibPoint(mPoint.x(), mPoint.y());
}

void CameraWidget::ChangeCalibLine()
{
    emit FinishSelectCalibLine(mLine.p1(), mLine.p2());
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
	QPixmap pm2 = QPixmap(40, 40);
	pm2.fill(Qt::transparent);

	QPainter painter(&pm2);
	painter.drawPixmap(20, 20, pm);

	QCursor cursorTarget = QCursor(pm2);
	setCursor(cursorTarget);
}

void CameraWidget::rectObject()
{
	selectedTool = 1;

    QToolButton* bt = qobject_cast<QToolButton*>(sender());
	changeToolIconInArea(bt->icon());
}
