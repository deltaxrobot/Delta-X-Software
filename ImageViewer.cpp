#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent) :
    QGraphicsView(parent)
{
    ViewerScene = new CustomScene();
    setScene(ViewerScene);

    cLine.SetScene(scene());
    cRect.SetScene(scene());
    cPoint.SetScene(scene());
    cPoint2.SetScene(scene());
    cMappingPoint.SetScene(scene());
    cQuadangle.SetScene(scene());
    cMappingPoint.SetScene(scene());
}

void ImageViewer::InitParameter()
{
    if (ImageItem == NULL)
        return;

    int quadangleOffset = 200;
    int areaOffset = 50;

    int imgWidth = ImageItem->pixmap().width();
    int imgHeight = ImageItem->pixmap().height();

    cQuadangle.SetPoint(QPointF(quadangleOffset, quadangleOffset), 0);
    cQuadangle.SetPoint(QPointF(quadangleOffset, imgHeight - quadangleOffset), 1);
    cQuadangle.SetPoint(QPointF(imgWidth - quadangleOffset, imgHeight - quadangleOffset), 2);
    cQuadangle.SetPoint(QPointF(imgWidth - quadangleOffset, quadangleOffset), 3);

    cArea.SetTopLeft(QPointF(areaOffset, areaOffset));
    cArea.SetBottomRight(QPointF(imgWidth - quadangleOffset, imgHeight - quadangleOffset));
}

void ImageViewer::ZoomIn(qreal value)
{
    CurrentZoom *= value;
    Zoom(CurrentZoom);
}

void ImageViewer::ZoomOut(qreal value)
{
    CurrentZoom /= value;
    Zoom(CurrentZoom);
}

void ImageViewer::Zoom(qreal value)
{
    cLine.SetThin(1.0f/value);
    cRect.SetThin(1.0f/value);
    cPoint.SetThin(1.0f/value);
    cPoint2.SetThin(1.0f/value);
    cMappingPoint.SetThin(1.0f/value);
    cQuadangle.SetThin(1.0f/value);
    cArea.SetThin(1.0f/value);

    QTransform matrix;
    matrix.scale(value, value);

    setTransform(matrix);
}

void ImageViewer::SelectRectTool()
{
    selectedTool = RECTANGLE_TOOL;

//    QToolButton* bt = qobject_cast<QToolButton*>(sender());
//    if (bt != NULL)
//        changeToolIconInArea(bt->icon());
}

void ImageViewer::SelectLineTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = LINE_TOOL;

//    QPushButton* bt = qobject_cast<QPushButton*>(sender());

//    if (bt != NULL)
//        changeToolIconInArea(bt->icon());
}

void ImageViewer::SelectPointTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = POINT_TOOL;

//    QPushButton* bt = qobject_cast<QPushButton*>(sender());
//    if (bt != NULL)
//        changeToolIconInArea(bt->icon());
}

void ImageViewer::SelectQuadrangleTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = QUADRANGLE_TOOL;

    setCursor(Qt::ArrowCursor);
}

void ImageViewer::SelectAreaTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = AREA_TOOL;

    setCursor(Qt::ArrowCursor);
}

void ImageViewer::SelectMappingTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = MAPPING_TOOL;

    QPushButton* bt = qobject_cast<QPushButton*>(sender());
    changeToolIconInArea(bt->icon());
}

void ImageViewer::SelectNoTool()
{
    selectedTool = NO_TOOL;

    setCursor(Qt::ArrowCursor);
}

void ImageViewer::DrawingAllShape()
{

}

void ImageViewer::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->angleDelta().y() > 0)
            ZoomIn(2);
        else
            ZoomOut(2);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if (event->buttons() == Qt::RightButton)
    {
        processRightPressEvent();
    }

    if (event->buttons() != Qt::LeftButton)
        return;

    mousePressed = true;

    QPoint mousePosOnImage = getMousePositionOnImage(event);
    QPointF mousePosOnScene = mapToScene(event->pos());

    processQuadanglePressEvent(mousePosOnImage);

    processAreaPressEvent(mousePosOnImage);

    processRectPressEvent(mousePosOnImage);

    processLinePressEvent(mousePosOnScene);

    processPointPressEvent(mousePosOnImage);

    processMappingPressEvent(mousePosOnImage);
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{


    if (event->buttons() == Qt::MiddleButton)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(true);

        QGraphicsView::mouseMoveEvent(event);

        return;
    }
    else
    {
        setDragMode(QGraphicsView::NoDrag);
        setInteractive(false);
    }

    if (mousePressed == false)
        return;

    QPointF mousePosOnScene = mapToScene(event->pos());

    if (event->type() == QEvent::MouseMove)
    {
        if (selectedTool == RECTANGLE_TOOL)
        {
            cRect.SetPoint2(mousePosOnScene);
//            mRect.setBottomRight(event->pos());
        }

        if (selectedTool == LINE_TOOL && IsCalibVisible == true)
        {
            cLine.SetPoint2(mousePosOnScene);
            //emit LineChanged(mLine.p1(), mLine.p2());
//                emit DistanceChanged(mLine.length());
        }

        if (selectedTool == POINT_TOOL && IsCalibVisible == true)
        {
//            mPoint = event->pos();
        }

        if (selectedTool == QUADRANGLE_TOOL)
        {
            if (transPointOrder > -1)
            {
                cQuadangle.SetPoint(mousePosOnScene, transPointOrder);
//                mQuadrangle[transPointOrder] = event->pos();
//                emit QuadrangleChanged(mQuadrangle[0], mQuadrangle[1], mQuadrangle[2], mQuadrangle[3]);
            }
        }

        if (selectedTool == AREA_TOOL)
        {
            if (processPointOrder == 1)
            {
                cArea.SetTopLeft(mousePosOnScene);
//                mArea.setTopLeft(QPoint(event->pos()));
            }
            else if (processPointOrder == 2)
            {
                cArea.SetBottomRight(mousePosOnScene);
//                mArea.setBottomRight(QPoint(event->pos()));
            }

//            emit AreaChanged(mArea);
        }
    }

    QGraphicsView::mouseMoveEvent(event);
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    mousePressed = false;

    if (selectedTool == RECTANGLE_TOOL)
    {
//        emit ObjectChanged(mRect.x(), mRect.y(), mRect.height(), mRect.width());
    }

    if (selectedTool == LINE_TOOL && IsCalibVisible == true)
    {
//            emit DistanceChanged(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    }

    if (selectedTool == QUADRANGLE_TOOL)
    {
        selectedTool = lastSelectedTool;
        setCursor(QCursor(lastCursorIcon));
    }
    update();
}

void ImageViewer::changeToolIconInArea(QIcon icon)
{
    QPixmap pm = icon.pixmap(20, 20);
    QPixmap pm2 = QPixmap(20, 20);
    pm2.fill(Qt::transparent);

    QPainter painter(&pm2);
    painter.drawPixmap(0, 0, pm);

    QCursor cursorTarget = QCursor(pm2);
    setCursor(cursorTarget);
}

QPoint ImageViewer::getMousePositionOnImage(QMouseEvent *event)
{
//    if (QGraphicsPixmapItem *item = qgraphicsitem_cast<QGraphicsPixmapItem *>(itemAt(event->pos())))
    if (ImageItem != NULL)
    {
        QPointF p = ImageItem->mapFromScene(mapToScene(event->pos()));
        QPoint pixel_pos = p.toPoint();
        return pixel_pos;
    }
    else
    {
        return QPoint(-1, -1);
    }
}

void ImageViewer::processRightPressEvent()
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

void ImageViewer::processQuadanglePressEvent(QPoint mousePos)
{
    if (IsQuadrangleEnable == false)
    {
        transPointOrder = -1;
        for (int i = 0; i < 4; i++)
        {
            if (cQuadangle.IsOverPoint(mousePos, i))
            {
                transPointOrder = i;
                lastSelectedTool = selectedTool;
                lastCursorIcon = cursor().pixmap();

                SelectQuadrangleTool();

                break;
            }
        }
    }
}

void ImageViewer::processAreaPressEvent(QPoint mousePos)
{
    processPointOrder = cArea.OverPoint(mousePos);

    if (processPointOrder > -1)
    {
        lastSelectedTool = selectedTool;
        lastCursorIcon = cursor().pixmap();

        SelectAreaTool();
    }
}

void ImageViewer::processRectPressEvent(QPoint mousePos)
{
    if (selectedTool == RECTANGLE_TOOL)
    {
//        mRect.setTopLeft(mousePos);
//        mRect.setBottomRight(mousePos);
        cRect.SetPoint1(mousePos);
        cRect.SetPoint2(mousePos);
    }
}

void ImageViewer::processPointPressEvent(QPoint mousePos)
{
    if (selectedTool == POINT_TOOL && IsCalibVisible == true)
    {
        if (selectedPoint == 0)
        {
            cPoint.SetValue(mousePos);
//            mPoint = mousePos;
            //emit PointChanged(mPoint.x(), mPoint.y());

            selectedPoint = 1;
        }
        else
        {
            cPoint2.SetValue(mousePos);
//            mPoint2 = mousePos;
            //emit PointChanged(mPoint2.x(), mPoint2.y());

            selectedPoint = 0;
            selectedTool = NO_TOOL;
        }

//        emit PointChanged(mPoint, mPoint2);
//        emit RequestUpdate();
    }
}

void ImageViewer::processLinePressEvent(QPointF mousePos)
{
    if (selectedTool == LINE_TOOL && IsCalibVisible == true)
    {
        cLine.SetPoint1(mousePos);
        cLine.SetPoint2(mousePos);

        //emit LineChanged(mLine.p1(), mLine.p2());
//        DistanceChanged(mLine.length());
    }
}

void ImageViewer::processMappingPressEvent(QPoint mousePos)
{
    if (selectedTool == MAPPING_TOOL)
    {
        cMappingPoint.SetValue(mousePos);

//        emit MappingPointChanged(mMappingPoint);
    }
}

void ImageViewer::drawStrokeLine(QLineF line)
{

}
