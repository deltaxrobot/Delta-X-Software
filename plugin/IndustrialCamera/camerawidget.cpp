#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QLabel(parent)
{
    lastCursorPosition = QCursor::pos();
}

void CameraWidget::SelectTool(int id)
{
    CurrentTool = id;
}

void CameraWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton)
    {
        CurrentTool = NO_TOOL;
        setCursor(Qt::ArrowCursor);
    }

    if (event->buttons() == Qt::LeftButton)
    {
        if (CurrentTool == CALIB_POINT_TOOL)
        {
            QPoint curPosInWidget = mapFromGlobal(QCursor::pos());

            emit CalibPointSelected(curPosInWidget.x(), curPosInWidget.y());
        }
        if (CurrentTool == POINT_TOOL)
        {
            QPoint curPosInWidget = mapFromGlobal(QCursor::pos());

            emit MappingPointSelected(curPosInWidget.x(), curPosInWidget.y());
        }
    }


}

void CameraWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void CameraWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void CameraWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPoint curPosInWidget = mapFromGlobal(QCursor::pos());

    if (QCursor::pos().x() != lastCursorPosition.x() || QCursor::pos().y() != lastCursorPosition.y())
    {
        emit MousePositionChanged(curPosInWidget.x(), curPosInWidget.y());
        lastCursorPosition = QCursor::pos();
    }

    //------ Display cursor center -----------

    drawPoint(curPosInWidget.x(), curPosInWidget.y());

    update();
}

void CameraWidget::drawPoint(int x, int y)
{
    //------ Display cursor center -----------

    const QPixmap* curPix = this->pixmap();

    if (curPix == NULL)
        return;

    QPixmap pix = *curPix;

    QPainter tempPainter(&pix);

    tempPainter.setPen(QPen(Qt::red, 5));
    tempPainter.drawPoint(x, y);

    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, pix);
    painter.end();
    //-------------

    update();
}

void CameraWidget::ChangeToolIconInArea(QIcon icon)
{
    QPixmap pm = icon.pixmap(40, 40);
    QPixmap pm2 = QPixmap(40, 40);
    pm2.fill(Qt::transparent);

    QPainter painter(&pm2);
    painter.drawPixmap(0, 0, pm);

    QCursor cursorTarget = QCursor(pm2);
    setCursor(cursorTarget);
}

void CameraWidget::slot_function()
{

}
