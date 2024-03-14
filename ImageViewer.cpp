#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent) :
    QGraphicsView(parent)
{
    ViewerScene = new CustomScene();
    setScene(ViewerScene);

    ImageItem = new QGraphicsPixmapItem();
    ImageItem->setZValue(-1);

    ViewerScene->addItem(ImageItem);

    cLine.SetScene(scene());
    cRect.SetScene(scene());
    cPoint.SetScene(scene());
    cPoint2.SetScene(scene());
    cMappingPoint.SetScene(scene());
    cQuadangle.SetScene(scene());
    cArea.SetScene(scene());
    cMappingPoint.SetScene(scene());

    SelectNoTool();

    setMoveHand(true);

    for (int i = 0; i < MAX_DRAWING_OBJECT_NUMBER; i++)
    {
        QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();
        polygonItems.append(polygonItem);
        polygonItem->setVisible(false);
        polygonItem->setPen(QPen(Qt::red, 2));

        QGraphicsTextItem* textItem = new QGraphicsTextItem();
        textItems.append(textItem);
        textItem->setVisible(false);
        textItem->setDefaultTextColor(Qt::red);

        ViewerScene->addItem(polygonItem);
        ViewerScene->addItem(textItem);
    }

    LoadSetting(Prefix);
}

ImageViewer::~ImageViewer()
{
    for(int i = 0; i < rectItems.count(); i++)
    {
        delete rectItems[i];
    }

    rectItems.clear();

    for(int i = 0; i < polygonItems.count(); i++)
    {
        delete polygonItems[i];
    }

    polygonItems.clear();

    for(int i = 0; i < textItems.count(); i++)
    {
        delete textItems[i];
    }

    textItems.clear();
}

void ImageViewer::InitParameter()
{
    if (ImageItem == NULL)
        return;

    imgWidth = ImageItem->pixmap().width();
    imgHeight = ImageItem->pixmap().height();

    int quadangleOffset = imgHeight / 4;
    int areaOffset = 25;

    if (cQuadangle.GetPolygon().count() == 0)
    {
        QPolygonF poly;
        poly.append(QPointF(imgWidth / 2 - quadangleOffset, imgHeight / 2 - quadangleOffset));
        poly.append(QPointF(imgWidth / 2 - quadangleOffset, imgHeight / 2 + quadangleOffset));
        poly.append(QPointF(imgWidth / 2 + quadangleOffset, imgHeight / 2 + quadangleOffset));
        poly.append(QPointF(imgWidth / 2 + quadangleOffset, imgHeight / 2 - quadangleOffset));

        cQuadangle.SetPolygon(poly);

        VariableManager::instance().updateVar(Prefix + "Quadangle", cQuadangle.GetPolygon());

        emit changedQuadrangle(poly);
    }

    if (cArea.GetValue() == QRectF(0, 0, 0, 0))
    {
        cArea.SetTopLeft(QPointF(areaOffset, areaOffset));
        cArea.SetBottomRight(QPointF(imgWidth - areaOffset, imgHeight - areaOffset));

        VariableManager::instance().updateVar(Prefix + "Area", cArea.GetValue());

        emit changedArea(cArea.GetValue());
    }

    if (cRect.GetValue() == QRectF(0, 0, 0, 0))
    {
        cRect.SetValue(QRectF(200, 200, 30, 15));

        VariableManager::instance().updateVar(Prefix + "Rectangle", cRect.GetValue());

        emit changedRect(cRect.GetValue());
    }
}

void ImageViewer::SaveSetting(QSettings *setting)
{
    QPointF p1 = cPoint.GetValue();
    QPointF p2 = cPoint2.GetValue();

    VariableManager::instance().Prefix = ProjectName;

    VariableManager::instance().updateVar(Prefix + "Point1", p1);
    VariableManager::instance().updateVar(Prefix + "Point2", p2);
    VariableManager::instance().updateVar(Prefix + "Quadangle", cQuadangle.GetPolygon());
    VariableManager::instance().updateVar(Prefix + "Area", cArea.GetValue());
    VariableManager::instance().updateVar(Prefix + "Rectangle", cRect.GetValue());
}

void ImageViewer::LoadSetting(QString prefix = "detect0.")
{
    Prefix = prefix;
    VariableManager::instance().Prefix = ProjectName;

    cPoint.SetValue(VariableManager::instance().getVar(prefix + "Point1").toPointF());
    cPoint2.SetValue(VariableManager::instance().getVar(prefix + "Point2").toPointF());

    cQuadangle.SetPolygon(VariableManager::instance().getVar(prefix + "Quadangle").value<QPolygonF>());
    cArea.SetValue(VariableManager::instance().getVar(prefix + "Area").toRectF());
    cRect.SetValue(VariableManager::instance().getVar(prefix + "Rectangle").toRectF());

    emit changedPoints(cPoint.GetValue(), cPoint2.GetValue());
    emit changedQuadrangle(cQuadangle.GetPolygon());
    emit changedArea(cArea.GetValue());
    emit changedRect(cRect.GetValue());
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

void ImageViewer::SetImage(QPixmap pixmap)
{
    ImageItem->setPixmap(pixmap);

    if (isFirstLoad == true)
    {
        isFirstLoad = false;
        InitParameter();
    }

    if (pixmap.width() != imgWidth || pixmap.height() != imgHeight)
    {
//        updateScale(float(pixmap.width()) / imgWidth);

        imgWidth = pixmap.width();
        imgHeight = pixmap.height();
    }

    update();
}

void ImageViewer::SetQuadrangle(QPolygonF poly)
{
    if (poly.count() < 4)
        return;

    if (isInRange(poly))
    {
        for (int i = 0; i < 4; i++)
        {
            QPointF p = poly.at(i);
            p.setX(p.x() * imgWidth);
            p.setY(p.y() * imgHeight);
            cQuadangle.SetPoint(p, i);
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            cQuadangle.SetPoint(poly.at(i), i);
        }
    }

    VariableManager::instance().updateVar(Prefix + "Quadangle", cQuadangle.GetPolygon());

    SelectQuadrangleTool();
}

void ImageViewer::DrawObjects(QList<QPolygonF> polygons) {
    QList<QPolygonF> pls;
    QMap<QString, QPointF> texts;

    int count = qMin(polygons.size(), 100); // Chỉ xử lý tối đa 100 phần tử

    for(int i = 0; i < count; ++i) {
        const QPolygonF& poly = polygons[i];
        pls.append(poly);

        // Tìm tâm của poly
        QPointF center = PointTool::GetCenterOfPolygon(poly);
        texts.insert(QString::number(i), QPointF(center.x(), center.y()));
    }

    DrawPolygons(pls);
    DrawTexts(texts);
}

void ImageViewer::DrawRecangles(QList<QRect> rects)
{
    for(int i = 0; i < rectItems.count(); i++)
    {
        if (i < rects.count())
        {
            rectItems.at(i)->setRect(rects.at(i));
            rectItems.at(i)->setVisible(true);
            continue;
        }

        rectItems.at(i)->setVisible(false);
    }
}

void ImageViewer::DrawPolygons(QList<QPolygonF> polygons)
{
    visiblePolygon = polygons.count();
    for(int i = 0; i < polygonItems.count(); i++)
    {
        if (i < visiblePolygon)
        {
            polygonItems.at(i)->setPolygon(polygons.at(i));
            polygonItems.at(i)->setVisible(true);
            continue;
        }

        polygonItems.at(i)->setVisible(false);
    }
}

void ImageViewer::DrawTexts(QMap<QString, QPointF> texts)
{
    visibleText = texts.count();
    for (int i = 0; i < textItems.count(); i++)
    {
        if (i < visibleText)
        {
            textItems.at(i)->setPlainText(texts.keys().at(i));
            textItems.at(i)->setPos(texts.values().at(i));
            textItems.at(i)->setVisible(true);
            continue;
        }

        textItems.at(i)->setVisible(false);
    }
}

void ImageViewer::TurnOnTool(bool value)
{
    cLine.SetVisible(value);
    cRect.SetVisible(value);
    cPoint.SetVisible(value);
    cPoint2.SetVisible(value);
    cMappingPoint.SetVisible(value);
    cQuadangle.SetVisible(value);
    cArea.SetVisible(value);
}

void ImageViewer::TurnOnObjects(bool value)
{
    for( int i = 0; i < MAX_DRAWING_OBJECT_NUMBER; i++)
    {
        if (i < visiblePolygon)
            polygonItems.at(i)->setVisible(value);

        if (i < visibleText)
            textItems.at(i)->setVisible(value);
    }
}

void ImageViewer::SetPointTitles(QString p1Text, QString p2Text)
{
    cPoint.SetText(p1Text);
    cPoint2.SetText(p2Text);
}

void ImageViewer::SetMappingPointTitle(QString text)
{
    cMappingPoint.SetText(text);
}

QPointF ImageViewer::GetPoint1()
{
    return cPoint.GetValue();
}

QPointF ImageViewer::GetPoint2()
{
    return cPoint2.GetValue();
}

QSize ImageViewer::GetImageSize()
{
    return QSize(imgWidth, imgHeight);
}

float ImageViewer::GetRatio()
{
    return CurrentZoom;
}

void ImageViewer::SelectRectTool()
{
    selectedTool = RECTANGLE_TOOL;

    setMoveHand(false);

    TurnOnTool(false);

    cRect.SetVisible(true);
}

void ImageViewer::SelectLineTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = LINE_TOOL;

    setMoveHand(false);

    TurnOnTool(false);

    cLine.SetVisible(true);
}

void ImageViewer::SelectPointTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = POINT_TOOL;

    selectedPoint = 0;

    setMoveHand(false);

    TurnOnTool(false);

    cPoint.SetVisible(true);
    cPoint2.SetVisible(true);
}

void ImageViewer::SelectQuadrangleTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = QUADRANGLE_TOOL;

    setCursor(Qt::ArrowCursor);

    setMoveHand(false);

    TurnOnTool(false);

    cQuadangle.SetVisible(true);
}

void ImageViewer::SelectAreaTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = AREA_TOOL;

    setCursor(Qt::ArrowCursor);

    TurnOnTool(false);

    cArea.SetVisible(true);

    setMoveHand(false);
}

void ImageViewer::SelectMappingTool()
{
    if (IsCalibVisible == false)
        return;

    selectedTool = MAPPING_TOOL;

    TurnOnTool(false);

    setMoveHand(false);

    cMappingPoint.SetVisible(true);
}

void ImageViewer::SelectNoTool()
{
    selectedTool = NO_TOOL;

//    setCursor(Qt::OpenHandCursor);

    setMoveHand(true);
    TurnOnTool(false);

    emit selectedNoTool();
}


void ImageViewer::wheelEvent(QWheelEvent *e)
{
//    setCursor(Qt::ClosedHandCursor);

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
//    if (event->buttons() == Qt::MiddleButton)
//    {
//        setDragMode(QGraphicsView::RubberBandDrag);
//        setInteractive(true);

//        QGraphicsView::mouseMoveEvent(event);

//        return;
//    }
//    else
//    {
//        setDragMode(QGraphicsView::ScrollHandDrag);
//        setInteractive(false);
//    }

//    if (event->buttons() == Qt::LeftButton)
//    {

//    }

    QPointF mousePosOnScene = mapToScene(event->pos());

    if (mousePressed == false)
        return;

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
    VariableManager::instance().Prefix = ProjectName;

    if (selectedTool == RECTANGLE_TOOL)
    {
        VariableManager::instance().updateVar(Prefix + "Rectangle", cRect.GetValue());
        emit changedRect(cRect.GetValue());
    }

    if (selectedTool == LINE_TOOL && IsCalibVisible == true)
    {
        emit changedLine(cLine.GetValue());
    }

    if (selectedTool == QUADRANGLE_TOOL)
    {
        VariableManager::instance().updateVar(Prefix + "Quadangle", cQuadangle.GetPolygon());
        emit changedQuadrangle(cQuadangle.GetPolygon());
    }

    if (selectedTool == AREA_TOOL)
    {
        VariableManager::instance().updateVar(Prefix + "Area", cArea.GetValue());
        emit changedArea(cArea.GetValue());

//        SoftwareLog(QString("Crop top left: x = %1, y = %2").arg(cArea.GetValue().topLeft().x()).arg(cArea.GetValue().topLeft().y()));
//        SoftwareLog(QString("Crop bottom right: x = %1, y = %2").arg(cArea.GetValue().bottomRight().x()).arg(cArea.GetValue().bottomRight().y()));

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

void ImageViewer::setMoveHand(bool value)
{
    if (value == false)
    {
        setDragMode(QGraphicsView::NoDrag);
        QApplication::restoreOverrideCursor();
//        setInteractive(true);
    }
    else
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
//        setInteractive(false);
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
            SelectNoTool();
        }
    }
    else
    {
        SelectNoTool();
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
//                lastSelectedTool = selectedTool;
//                lastCursorIcon = cursor().pixmap();

//                SelectQuadrangleTool();

                break;
            }
        }
    }
}

void ImageViewer::processAreaPressEvent(QPoint mousePos)
{
    processPointOrder = cArea.OverPoint(mousePos);

//    if (processPointOrder > -1)
//    {
//        lastSelectedTool = selectedTool;
//        lastCursorIcon = cursor().pixmap();

//        SelectAreaTool();
//    }
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

            selectedPoint = 1;
        }
        else
        {
            cPoint2.SetValue(mousePos);

            selectedPoint = 0;
        }

        VariableManager::instance().updateVar("Point1", cPoint.GetValue());
        VariableManager::instance().updateVar("Point2", cPoint2.GetValue());
        emit changedPoints(cPoint.GetValue(), cPoint2.GetValue());
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

        emit changedMappingPoint(cMappingPoint.GetValue());
    }
}

void ImageViewer::drawStrokeLine(QLineF line)
{

}

bool ImageViewer::isInRange(QPolygonF poly)
{
    foreach(QPointF p, poly)
    {
        if (p.x() > 1 || p.y() > 1)
            return false;
    }

    return true;
}

void ImageViewer::updateScale(float scale)
{
    cPoint.Scale(scale);
    cRect.Scale(scale);
    cQuadangle.Scale(scale);
    cArea.Scale(scale);
}
