#include "CameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
	QLabel(parent)
{	
	overPix.fill(Qt::white);

	//set everything to false as nothing has started yet
	mousePressed = false;
	drawStarted = false;

    selectedTool = NO_TOOL;

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

    mPoint.setX(25);
    mPoint.setY(250);

    mPoint2.setX(250);
    mPoint2.setY(250);

//    realPointValue.setX(100);
//    realPointValue.setY(100);

//    realPoint2Value.setX(200);
//    realPoint2Value.setX(100);

    mQuadrangle[0] = QPoint(100, 100);
    mQuadrangle[1] = QPoint(100, 200);
    mQuadrangle[2] = QPoint(200, 200);
    mQuadrangle[3] = QPoint(200, 100);

    mArea.setTopLeft(QPoint(40, 40));
    mArea.setBottomRight(QPoint(300, 250));

    emit DistanceChanged(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit PointChanged(mPoint, mPoint2);
    emit ObjectChanged(mRect.x(), mRect.y(), mRect.height(), mRect.width());
    emit QuadrangleChanged(mQuadrangle[0], mQuadrangle[1], mQuadrangle[2], mQuadrangle[3]);
    emit AreaChanged(mArea);
    //emit LineChanged(mLine.p1(), mLine.p2());

	update();
}

void CameraWidget::ChangeSize(int w, int h)
{
	float ratio = (float)w / geometry().width();

	// Update new values for calib points
	mLine.setLine(mLine.x1() * ratio, mLine.y1() * ratio, mLine.x2() * ratio, mLine.y2() * ratio);

	mPoint = mPoint * ratio;
    mPoint2 = mPoint2 * ratio;

	mRect.setRect(mRect.x() * ratio, mRect.y() * ratio, mRect.width() * ratio, mRect.height() * ratio);
	
    mQuadrangle[0] = mQuadrangle[0] * ratio;
    mQuadrangle[1] = mQuadrangle[1] * ratio;
    mQuadrangle[2] = mQuadrangle[2] * ratio;
    mQuadrangle[3] = mQuadrangle[3] * ratio;

	// 
	QRect size = geometry();
	size.setWidth(w);
	size.setHeight(h);
	setGeometry(size);

	QRect parrentSize = parentWidget()->geometry();
	parrentSize.setWidth(w);
	parrentSize.setHeight(h);
	parentWidget()->setGeometry(parrentSize);

    mArea.setRect(mArea.x() * ratio, mArea.y() * ratio, mArea.width() * ratio, mArea.height() * ratio);

	emit SizeChanged();

    emit DistanceChanged(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit PointChanged(mPoint, mPoint2);
    emit ObjectChanged(mRect.x(), mRect.y(), mRect.height(), mRect.width());
    emit QuadrangleChanged(mQuadrangle[0], mQuadrangle[1], mQuadrangle[2], mQuadrangle[3]);
    emit AreaChanged(mArea);
    //emit LineChanged(mLine.p1(), mLine.p2());
}

void CameraWidget::mousePressEvent(QMouseEvent* event) 
{	
	if (event->buttons() == Qt::RightButton)
	{
        if (selectedTool == POINT_TOOL)
        {
            if (selectedPoint == 0)
                selectedPoint = 1;
            else
            {
                selectedPoint = 0;
                selectedTool = NO_TOOL;
                setCursor(Qt::ArrowCursor);
            }
        }
        else
        {
            selectedTool = NO_TOOL;
            setCursor(Qt::ArrowCursor);
        }
	}


    if (event->buttons() != Qt::LeftButton)
        return;    

    mousePressed = true;

	// ---------Catch event: adjusting transform points -------------
    if (IsQuadrangleEnable == false)
	{
		transPointOrder = -1;
		for (int i = 0; i < 4; i++)
		{
            if (abs(mQuadrangle[i].x() - event->pos().x()) < 5 && abs(mQuadrangle[i].y() - event->pos().y()) < 5)
			{
				transPointOrder = i;
				lastSelectedTool = selectedTool;
				lastCursorIcon = cursor().pixmap();

                SelectQuadrangleTool();

				break;
			}
		}
	}

	// -----------Catch event: adjusting proessing rectangle -------------
	processPointOrder = -1;
    if (abs(mArea.topLeft().x() - event->pos().x()) < 5 && abs(mArea.topLeft().y() - event->pos().y()) < 5)
	{
		processPointOrder = 1;
		
		lastSelectedTool = selectedTool;
		lastCursorIcon = cursor().pixmap();

        SelectAreaTool();
	}

    if (abs(mArea.bottomRight().x() - event->pos().x()) < 5 && abs(mArea.bottomRight().y() - event->pos().y()) < 5)
	{
		processPointOrder = 2;
		lastSelectedTool = selectedTool;
		lastCursorIcon = cursor().pixmap();

        SelectAreaTool();
    }

	//------------------------	
    if (selectedTool == OBJECT_TOOL)
	{
		mRect.setTopLeft(event->pos());
		mRect.setBottomRight(event->pos());
	}
    if (IsCalibVisible == true)
	{
        if (selectedTool == LINE_TOOL)
		{
			mLine.setP1(event->pos());
			mLine.setP2(event->pos());

            //emit LineChanged(mLine.p1(), mLine.p2());
            DistanceChanged(mLine.length());
		}
        if (selectedTool == POINT_TOOL)
		{
            if (selectedPoint == 0)
            {
                mPoint = event->pos();
                //emit PointChanged(mPoint.x(), mPoint.y());

                selectedPoint = 1;
            }
            else
            {
                mPoint2 = event->pos();
                //emit PointChanged(mPoint2.x(), mPoint2.y());

                selectedPoint = 0;
                selectedTool = NO_TOOL;
            }

            emit PointChanged(mPoint, mPoint2);
            emit RequestUpdate();
		}
    }

    // ----- MAPPING TOOL -----
    if (selectedTool == MAPPING_TOOL)
    {
        mMappingPoint = event->pos();

        emit MappingPointChanged(mMappingPoint);
    }
}

void CameraWidget::mouseMoveEvent(QMouseEvent* event) 
{		
	if (event->type() == QEvent::MouseMove) 
	{	
        if (selectedTool == OBJECT_TOOL)
		{
			mRect.setBottomRight(event->pos());
		}
        if (IsCalibVisible == true)
		{
            if (selectedTool == LINE_TOOL)
			{
				mLine.setP2(event->pos());
                //emit LineChanged(mLine.p1(), mLine.p2());
                emit DistanceChanged(mLine.length());
			}

            if (selectedTool == POINT_TOOL)
			{
				mPoint = event->pos();
			}
		}
		
        if (selectedTool == QUADRANGLE_TOOL)
		{
			if (transPointOrder > -1)
			{
                mQuadrangle[transPointOrder] = event->pos();
                emit QuadrangleChanged(mQuadrangle[0], mQuadrangle[1], mQuadrangle[2], mQuadrangle[3]);
			}
		}

        if (selectedTool == AREA_TOOL)
		{
			if (processPointOrder == 1)
			{
                mArea.setTopLeft(QPoint(event->pos()));
			}
			else if (processPointOrder == 2)
			{
                mArea.setBottomRight(QPoint(event->pos()));
			}

            emit AreaChanged(mArea);
		}
	}	

	//it calls the paintEven() function continuously
	update();
}

void CameraWidget::mouseReleaseEvent(QMouseEvent *event) {

	//When mouse is released update for the one last time
	mousePressed = false;
    if (selectedTool == OBJECT_TOOL)
        emit ObjectChanged(mRect.x(), mRect.y(), mRect.height(), mRect.width());
    if (IsCalibVisible == true)
	{
        if (selectedTool == LINE_TOOL)
            emit DistanceChanged(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
	}
	
    if (selectedTool == QUADRANGLE_TOOL)
	{
		selectedTool = lastSelectedTool;
		setCursor(QCursor(lastCursorIcon));
	}
	update();
}

void CameraWidget::paintEvent(QPaintEvent *event) 
{
    try
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

        tempPainter.setPen(QPen(Qt::red, 1));

        if (mousePressed)
        {
            if (selectedTool == OBJECT_TOOL)
            {
                tempPainter.drawRect(mRect);
            }

            painter.drawPixmap(0, 0, mPix);

            drawStarted = true;
        }

        // ---- Draw info ----
        drawQuadrangle(&tempPainter);
        drawArea(&tempPainter);
        drawLine(&tempPainter);
        drawPoint(&tempPainter);
        drawMappingPoint(&tempPainter);

        // ---- Draw Axis ----
        drawAxisSymbol(&tempPainter);

        painter.drawPixmap(0, 0, mPix);

        painter.end();
    }
    catch(...)
    {

    }

}

CameraWidget::~CameraWidget()
{

}

void CameraWidget::SelectLineTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = LINE_TOOL;

	QPushButton* bt = qobject_cast<QPushButton*>(sender());
	changeToolIconInArea(bt->icon());
}

void CameraWidget::SelectPointTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = POINT_TOOL;

	QPushButton* bt = qobject_cast<QPushButton*>(sender());
	changeToolIconInArea(bt->icon());
}

void CameraWidget::SelectQuadrangleTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = QUADRANGLE_TOOL;

	setCursor(Qt::ArrowCursor);
}

void CameraWidget::SelectAreaTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = AREA_TOOL;

    setCursor(Qt::ArrowCursor);
}

void CameraWidget::SelectMappingTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = MAPPING_TOOL;

    QPushButton* bt = qobject_cast<QPushButton*>(sender());
    changeToolIconInArea(bt->icon());
}

void CameraWidget::SelectNoTool()
{
    selectedTool = NO_TOOL;

	setCursor(Qt::ArrowCursor);
}

void CameraWidget::SaveSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
	
    SaveSetting(&settings);
}

void CameraWidget::SaveSetting(QSettings *setting)
{
    setting->setValue("line", mLine);
    setting->setValue("object", mRect);
    setting->setValue("point", mPoint);
    setting->setValue("point2", mPoint2);
    setting->setValue("transpoint1", mQuadrangle[0]);
    setting->setValue("transpoint2", mQuadrangle[1]);
    setting->setValue("transpoint3", mQuadrangle[2]);
    setting->setValue("transpoint4", mQuadrangle[3]);

    setting->setValue("rect", mArea);
}

void CameraWidget::LoadSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    LoadSetting(&settings);
}

void CameraWidget::LoadSetting(QSettings *setting)
{
    mLine = setting->value("line").toLine();

    mRect = setting->value("object").toRect();

    mPoint = setting->value("point").toPoint();
    mPoint2 = setting->value("point2").toPoint();

    mQuadrangle[0] = setting->value("transpoint1").toPoint();
    mQuadrangle[1] = setting->value("transpoint2").toPoint();
    mQuadrangle[2] = setting->value("transpoint3").toPoint();
    mQuadrangle[3] = setting->value("transpoint4").toPoint();

    mArea = setting->value("rect").toRect();

    emit DistanceChanged(mLine.length());
    emit PointChanged(mPoint, mPoint2);
    emit ObjectChanged(mRect.x(), mRect.y(), mRect.height(), mRect.width());
    emit QuadrangleChanged(mQuadrangle[0], mQuadrangle[1], mQuadrangle[2], mQuadrangle[3]);
    emit AreaChanged(mArea);
    //emit LineChanged(mLine.p1(), mLine.p2());

    update();
}

//void CameraWidget::ChangePoint()
//{
//    emit PointChanged(mPoint.x(), mPoint.y());
//}

void CameraWidget::ChangeLine()
{
    QLineEdit* le = qobject_cast<QLineEdit*>(sender());
    realLineValue = le->text().toFloat();
}

void CameraWidget::ChangeQuadrangle(QPoint p1, QPoint p2, QPoint p3, QPoint p4)
{
    mQuadrangle[0] = p1;
    mQuadrangle[1] = p2;
    mQuadrangle[2] = p3;
    mQuadrangle[3] = p4;
}

void CameraWidget::ChangeQuadrangle(QVector<QPointF> quads)
{
    for (int i = 0; i < 4; i++)
    {
        mQuadrangle[i].setX(quads[i].x() * width());
        mQuadrangle[i].setY(quads[i].y() * height());
    }
}

void CameraWidget::ChangeXDirection(float angle)
{
    xAxisAngle = angle;
}

void CameraWidget::ChangeRealLineValue(float value)
{
    realLineValue = value;
}

void CameraWidget::ChangeImageLineValue(float value)
{
    float length = mLine.length();

    float sub = value - length;

    QPointF newP2 = mLine.p1() + QPointF(sub, 0);

    mLine.setP2(newP2);
}

void CameraWidget::ChangeImagePointValue(QPoint value)
{
    mPoint = value;
}

void CameraWidget::ChangeImagePoint2Value(QPoint value)
{
    mPoint2 = value;
}

void CameraWidget::ChangeRealPointValue(QPoint value)
{
    realPointValue = value;
}

void CameraWidget::ChangeRealPoint2Value(QPoint value)
{
    realPoint2Value = value;
}

void CameraWidget::ChangeRealMappingValue(QPointF value)
{
    realMappingValue = value;
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
    QPixmap pm = icon.pixmap(20, 20);
    QPixmap pm2 = QPixmap(20, 20);
    pm2.fill(Qt::transparent);

	QPainter painter(&pm2);
    painter.drawPixmap(0, 0, pm);

	QCursor cursorTarget = QCursor(pm2);
    setCursor(cursorTarget);
}

void CameraWidget::drawQuadrangle(QPainter *painter)
{
    if (IsCalibVisible == false)
        return;

    if (IsQuadrangleEnable == true)
        return;

    for (int i = 0; i < 3; i++)
    {
        drawStrokeLine(painter, QLine(mQuadrangle[i], mQuadrangle[i + 1]));
        drawStrokeRect(painter, QRect(mQuadrangle[i] - QPoint(5, 5), mQuadrangle[i] + QPoint(5, 5)));
    }
    drawStrokeLine(painter, QLine(mQuadrangle[3], mQuadrangle[0]));
    drawStrokeRect(painter, QRect(mQuadrangle[3] - QPoint(4, 4), mQuadrangle[3] + QPoint(4, 4)));
}

void CameraWidget::drawArea(QPainter *painter)
{
    if (IsCalibVisible == false)
        return;

    painter->setOpacity(0.5f);
    drawStrokeRect(painter, mArea);
    drawStrokeRect(painter, QRect(mArea.topLeft() - QPoint(4, 4), mArea.topLeft() + QPoint(4, 4)));
    drawStrokeRect(painter, QRect(mArea.bottomRight() - QPoint(4, 4), mArea.bottomRight() + QPoint(4, 4)));

    drawSolidColor(painter, QRect(QPoint(0, 0), QPoint(width(), mArea.topLeft().y())), 0.5f);
    drawSolidColor(painter, QRect(QPoint(0, mArea.topLeft().y()), QPoint(mArea.topLeft().x(), height())), 0.5f);
    drawSolidColor(painter, QRect(QPoint(mArea.bottomRight().x(), mArea.topLeft().y()), QPoint(width(), height())), 0.5f);
    drawSolidColor(painter, QRect(QPoint(mArea.topLeft().x(), mArea.bottomRight().y()), QPoint(mArea.bottomRight().x(), height())), 0.5f);

    painter->setOpacity(1);
}

void CameraWidget::drawLine(QPainter *painter)
{
    if (IsCalibVisible == false)
        return;

    drawStrokeLine(painter, mLine);
    QString text = QString("%1 mm").arg(realLineValue);

    QPoint pos = QPoint(mLine.center().x(), mLine.center().y() - 10);
    drawStrokeText(painter, text, pos);
}

void CameraWidget::drawPoint(QPainter *painter)
{
    if (IsCalibVisible == false)
        return;

    painter->setPen(QPen(Qt::black, 5));
    painter->drawPoint(mPoint);
    painter->setPen(QPen(Qt::white, 3));
    painter->drawPoint(mPoint);

    QString text = QString("P1: x=%1, y=%2").arg(realPointValue.x()).arg(realPointValue.y());
    QPoint pos = mPoint + QPoint(5, -5);
    drawStrokeText(painter, text, pos);

    painter->setPen(QPen(Qt::black, 5));
    painter->drawPoint(mPoint2);
    painter->setPen(QPen(Qt::white, 3));
    painter->drawPoint(mPoint2);

    QString text2 = QString("P2: x=%1, y=%2").arg(realPoint2Value.x()).arg(realPoint2Value.y());
    QPoint pos2 = mPoint2 + QPoint(5, -5);
    drawStrokeText(painter, text2, pos2);


    if (selectedTool == POINT_TOOL)
    {
        painter->setPen(QPen(Qt::red, 1));

        QPoint curPosInWidget = mapFromGlobal(QCursor::pos());
        painter->drawText(curPosInWidget.x() + 10, curPosInWidget.y() - 10, QString("P%1").arg(QString::number(selectedPoint + 1)));
    }

}

void CameraWidget::drawMappingPoint(QPainter *painter)
{
    if (selectedTool != MAPPING_TOOL)
        return;

    painter->setPen(QPen(Qt::black, 5));
    painter->drawPoint(mMappingPoint);
    painter->setPen(QPen(Qt::white, 3));
    painter->drawPoint(mMappingPoint);

    QString text = QString("x=%1, y=%2").arg(realMappingValue.x()).arg(realMappingValue.y());
    QPoint pos = mMappingPoint + QPoint(5, -5);
    drawStrokeText(painter, text, pos);
}

void CameraWidget::drawStrokeLine(QPainter *painter, QLineF line)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->drawLine(line);
    painter->setPen(QPen(Qt::white, 1));
    painter->drawLine(line.p1() + QPoint(1, 1), line.p2() + QPoint(1, 1));
}

void CameraWidget::drawStrokeRect(QPainter* painter, QRect rect)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRect(rect);
    painter->setPen(QPen(Qt::white, 1));
    painter->drawRect(QRect(rect.x()- 1, rect.y() - 1, rect.width() + 2, rect.height() + 2));
}

void CameraWidget::drawStrokeText(QPainter *painter, QString text, QPoint pos)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->drawText(pos, text);
    painter->setPen(QPen(Qt::white, 1));
    painter->drawText(pos + QPoint(1, 1), text);
}

void CameraWidget::drawSolidColor(QPainter *painter, QRect rect, float alpha)
{
    QPixmap pix(rect.width(), rect.height());
    pix.fill(QColor("black"));
    painter->setOpacity(alpha);
    painter->drawPixmap(rect, pix);
    painter->setOpacity(1);
}

void CameraWidget::drawAxisSymbol(QPainter *painter)
{
    if (IsCalibVisible == false)
        return;

    QPixmap pix = QPixmap(":/icon/Axis_64px.png");
    QMatrix rm;
    rm.rotate(-xAxisAngle);
    rm.scale(xAxisScale, xAxisScale);
    pix = pix.transformed(rm);
    painter->drawPixmap(xAxisPosition, pix);
}

void CameraWidget::SelectObjectTool()
{
    selectedTool = OBJECT_TOOL;

    QToolButton* bt = qobject_cast<QToolButton*>(sender());
	changeToolIconInArea(bt->icon());
}
