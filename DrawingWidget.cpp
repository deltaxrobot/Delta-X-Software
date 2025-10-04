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


        line.setP1(QPoint((l.x1() + xOffset) * ratio, (l.y1() + yOffset) * ratio));
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
	rectangles.clear();
	circles.clear();
	arcs.clear();
	Vectors.clear();
	update(); // Trigger repaint to clear the display
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

void DrawingWidget::EraserAll()
{
    ClearShape();
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
    if (event->button() == Qt::LeftButton) {
        switch (tool) {
            case LINE:
                // Start drawing line
                if (lines.isEmpty() || lines.last().p2() != QPoint(-1, -1)) {
                    QLine newLine;
                    newLine.setP1(event->pos());
                    newLine.setP2(QPoint(-1, -1)); // Temporary end point
                    lines.append(newLine);
                }
                break;
                
            case RECTANGLE:
                // Start drawing rectangle
                if (rectangles.isEmpty() || rectangles.last().width() > 0) {
                    QRect newRect;
                    newRect.setTopLeft(event->pos());
                    newRect.setBottomRight(event->pos());
                    rectangles.append(newRect);
                }
                break;
                
            case CIRCLE:
                // Start drawing circle
                if (circles.isEmpty() || circles.last().z() > 0) {
                    QVector3D newCircle;
                    newCircle.setX(event->pos().x());
                    newCircle.setY(event->pos().y());
                    newCircle.setZ(0); // Radius will be set in mouse move
                    circles.append(newCircle);
                }
                break;
                
            default:
                break;
        }
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent * event)
{
    switch (tool) {
        case LINE:
            // Update current line end point
            if (!lines.isEmpty() && lines.last().p2() == QPoint(-1, -1)) {
                lines.last().setP2(event->pos());
                update(); // Trigger repaint
            }
            break;
            
        case RECTANGLE:
            // Update current rectangle
            if (!rectangles.isEmpty() && rectangles.last().width() == 0) {
                rectangles.last().setBottomRight(event->pos());
                update(); // Trigger repaint
            }
            break;
            
        case CIRCLE:
            // Update current circle radius
            if (!circles.isEmpty() && circles.last().z() == 0) {
                QVector3D& circle = circles.last();
                float radius = sqrt(pow(event->pos().x() - circle.x(), 2) + 
                                  pow(event->pos().y() - circle.y(), 2));
                circle.setZ(radius);
                update(); // Trigger repaint
            }
            break;
            
        default:
            break;
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        switch (tool) {
            case LINE:
                // Finalize current line
                if (!lines.isEmpty() && lines.last().p2() == QPoint(-1, -1)) {
                    lines.last().setP2(event->pos());
                    
                    // Add line to vectors for G-code export
                    QVector<QPointF> linePoints;
                    linePoints.append(lines.last().p1());
                    linePoints.append(lines.last().p2());
                    Vectors.append(linePoints);
                }
                break;
                
            case RECTANGLE:
                // Finalize current rectangle
                if (!rectangles.isEmpty()) {
                    QRect& rect = rectangles.last();
                    rect.setBottomRight(event->pos());
                    
                    // Add rectangle as connected lines to vectors
                    QVector<QPointF> rectPoints;
                    rectPoints.append(rect.topLeft());
                    rectPoints.append(rect.topRight());
                    rectPoints.append(rect.bottomRight());
                    rectPoints.append(rect.bottomLeft());
                    rectPoints.append(rect.topLeft()); // Close the rectangle
                    Vectors.append(rectPoints);
                }
                break;
                
            case CIRCLE:
                // Finalize current circle
                if (!circles.isEmpty()) {
                    QVector3D& circle = circles.last();
                    float radius = sqrt(pow(event->pos().x() - circle.x(), 2) + 
                                      pow(event->pos().y() - circle.y(), 2));
                    circle.setZ(radius);
                    
                    // Add circle as connected points to vectors
                    QVector<QPointF> circlePoints;
                    int segments = 36; // 36 segments for smooth circle
                    for (int i = 0; i <= segments; i++) {
                        float angle = (i * 2 * M_PI) / segments;
                        float x = circle.x() + radius * cos(angle);
                        float y = circle.y() + radius * sin(angle);
                        circlePoints.append(QPointF(x, y));
                    }
                    Vectors.append(circlePoints);
                }
                break;
                
            default:
                break;
        }
        
        update(); // Final repaint
    }
}

void DrawingWidget::paintEvent(QPaintEvent * event)
{
	QLabel::paintEvent(event);
	
	// Draw all shapes on top of the background
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	
	// Set pen for drawing
	QPen pen(Qt::red, 2);
	painter.setPen(pen);
	
	// Draw lines
	foreach(const QLine& line, lines) {
		if (line.p2() != QPoint(-1, -1)) { // Only draw complete lines
			painter.drawLine(line);
		}
	}
	
	// Draw rectangles
	foreach(const QRect& rect, rectangles) {
		if (rect.width() > 0 && rect.height() > 0) { // Only draw valid rectangles
			painter.drawRect(rect);
		}
	}
	
	// Draw circles
	foreach(const QVector3D& circle, circles) {
		if (circle.z() > 0) { // Only draw circles with valid radius
			int radius = (int)circle.z();
			painter.drawEllipse(QPoint((int)circle.x(), (int)circle.y()), radius, radius);
		}
	}
}

void DrawingWidget::changeToolIconInArea(QString filePath)
{
	QCursor cursorTarget = QCursor(QPixmap(filePath));
	setCursor(cursorTarget);
}
