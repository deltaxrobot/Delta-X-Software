#include "DrawingWidget.h"

DrawingWidget::DrawingWidget(QWidget *parent)
	: QLabel(parent)
{
    InitGrid();
}


DrawingWidget::~DrawingWidget()
{

}


void DrawingWidget::InitGrid()
{
	int h = height() * (1.0f / PRECISION);
	QPixmap pi = QPixmap(h, h);
	pi.fill(QColor(0, 0, 0, 0));

    QString currentPaint = QCoreApplication::applicationDirPath();

    QPixmap pix = QPixmap(currentPaint + "/icon/Circle-limit.png");
    QPixmap pix1 = QPixmap(currentPaint + "/icon/grid-10-pixel.png");
    QPixmap pix2 = QPixmap(currentPaint + "/icon/grid-axis.png");
		
	QPainter p(&pi);
	
	p.begin(this);
	p.drawPixmap(0, 0, h ,h, pix);
	p.drawPixmap(0, 0, h, h, pix1);
	p.drawPixmap(0, 0, h, h, pix2);
	p.end();
		
	setPixmap(pi);
	setScaledContents(true);

	update();
}

void DrawingWidget::AddImage(int x, int y, int w, int h, QPixmap pix, float space, QString type, QString conversion)
{
	Image image;
	image.Pixmap = new QPixmap(pix);
	image.Size.setX(w);
	image.Size.setY(h);
	image.Position.setX(x);
	image.Position.setY(y);
	image.LineSpace = space;
	image.ToolType = type;
	image.Conversion = conversion;

    Images.push_back(image);

	InitGrid();

	QPixmap currentPix = *pixmap();
	
	float ratio = (float)currentPix.height() / height();
	int hS = pix.height() * ratio;

	x = x * ratio;
	y = y * ratio;
	w = w * ratio;
	h = h * ratio;

	QPixmap scalePix = pix.scaledToHeight(hS);
	QPainter p(&currentPix);

	p.begin(this);
	p.drawPixmap(x, y, w, h, pix);
	p.end();

	setPixmap(currentPix);

	update();	
}

void DrawingWidget::AddLineToStack(QPoint p1, QPoint p2)
{
	QLine l;
	l.setPoints(p1, p2);       

    if (lines.count() > 0)
    {
        QLine lastLine = lines.at(lines.count() - 1);

        if (l.p1() == lastLine.p1() && l.p2() == lastLine.p2())
            return;
    }

	lines.push_back(l);

//	QPixmap pix = *pixmap();
//    //cv::Mat matPix = ImageTool::QPixmapToCvMat(pix);

//	float ratio = (float)pix.height() / height();

//	QLine line;

//	int xOffset = height() / 2;
//	int yOffset = width() / 2;

//	line.setP1(QPoint((p1.x() + xOffset) * ratio, (p1.y() + yOffset) * ratio));
//	line.setP2(QPoint((p2.x() + xOffset) * ratio, (p2.y() + yOffset) * ratio));

//	QPainter p(&pix);

//	p.begin(this);
//	p.drawLine(line);
//	p.end();

//    //matPix = ImageTool::QPixmapToCvMat(pix);
//	setPixmap(pix);

    //	update();
}

void DrawingWidget::DrawLineFromStack()
{
    QPixmap pix = *pixmap();
    //cv::Mat matPix = ImageTool::QPixmapToCvMat(pix);

    float ratio = (float)pix.height() / height();
    int xOffset = height() / 2;
    int yOffset = width() / 2;

    QPainter p(&pix);

    p.begin(this);

    foreach(QLine l, lines)
    {
        QLine line;


        line.setP1(QPoint((l.x1() + xOffset) * ratio, (l.y1()) + yOffset) * ratio);
        line.setP2(QPoint((l.x2() + xOffset) * ratio, (l.y2() + yOffset) * ratio));


        p.drawLine(line);
    }
    p.end();

    //matPix = ImageTool::QPixmapToCvMat(pix);
    setPixmap(pix);

    update();
}

void DrawingWidget::AddRectangle(QRect rec)
{
	QRect rect;

	rect = rec;

	QPixmap pix = *pixmap();

	QPainter p(&pix);

	p.begin(this);
	p.drawRect(rect);
	p.end();

	setPixmap(pix);

	update();

	rectangles.push_back(rect);
}

void DrawingWidget::ClearShape()
{
	lines.clear();
}

void DrawingWidget::ClearImage()
{
    for (int i = 0; i < Images.size(); i++)
	{
        delete Images[i].Pixmap;
	}

    Images.clear();
}

void DrawingWidget::SelectZoomInTool()
{
	tool = ZOOM_IN;

	changeToolIconInArea(ZOOM_IN_ICON);
}

void DrawingWidget::SelectZoomOutTool()
{
	tool = ZOOM_OUT;

	changeToolIconInArea(ZOOM_OUT_ICON);
}

void DrawingWidget::SelectLineTool()
{
	tool = LINE;
	changeToolIconInArea(LINE_ICON);
}

void DrawingWidget::SelectRectangleTool()
{
	tool = RECTANGLE;
	changeToolIconInArea(RECTANGLE_ICON);
}

void DrawingWidget::SelectCircleTool()
{
	tool = CIRCLE;
	changeToolIconInArea(CIRCLE_ICON);
}

void DrawingWidget::SelectArcTool()
{
	tool = ARC;
	changeToolIconInArea(ARC_ICON);
}

void DrawingWidget::SelectCursor()
{
	tool = CURSOR;
	changeToolIconInArea(CURSOR_ICON);
}

void DrawingWidget::mousePressEvent(QMouseEvent * event)
{

}

void DrawingWidget::mouseMoveEvent(QMouseEvent * event)
{

}

void DrawingWidget::mouseReleaseEvent(QMouseEvent * event)
{

}

void DrawingWidget::paintEvent(QPaintEvent * event)
{
	QLabel::paintEvent(event);
}

void DrawingWidget::changeToolIconInArea(QString filePath)
{
	QCursor cursorTarget = QCursor(QPixmap(filePath));
	setCursor(cursorTarget);
}
