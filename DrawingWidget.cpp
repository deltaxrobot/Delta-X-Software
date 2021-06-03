#include "DrawingWidget.h"

DrawingWidget::DrawingWidget(QWidget *parent)
	: QLabel(parent)
{

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

	images.push_back(image);

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

void DrawingWidget::SetGcodeEditor(QTextEdit * gcodeEditor)
{
	pteGcodeEditor = gcodeEditor;
}

void DrawingWidget::ClearShape()
{
	lines.clear();
}

void DrawingWidget::ClearImage()
{
	for (int i = 0; i < images.size(); i++)
	{
		delete images[i].Pixmap;
	}

	images.clear();
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

void DrawingWidget::SetEffector(QComboBox * drawingEffector)
{
    cbDrawingEffector = drawingEffector;
}

void DrawingWidget::SetGcodeExportParameterPointer(QLineEdit *safeZHeight, QLineEdit *travelSpeed, QLineEdit *drawingSpeed, QLineEdit *drawingAcceleration)
{
    leSafeZHeight = safeZHeight;
    leTravelSpeed = travelSpeed;
    leDrawingSpeed = drawingSpeed;
    leDrawingAcceleration = drawingAcceleration;
}

void DrawingWidget::ExportGcodes()
{
    float downZ = leSafeZHeight->text().toFloat();
    float upZ = downZ + 10;
    float safeZ = downZ + 50;
    int travelSpeed = leTravelSpeed->text().toInt();
    int drawingSpeed = leDrawingSpeed->text().toInt();
    int drawingAcceleration = leDrawingAcceleration->text().toInt();

    QString gcodes = "G28\n";

    if (cbDrawingEffector->currentText() == "Laser")
    {
        gcodes += ";Select laser head";
        gcodes += "M360 E3\n";
        gcodes += ";Turn off laser head";
        gcodes += "M03 S0\n";
    }

    gcodes += QString("G01 F%1\n").arg(travelSpeed);
    gcodes += QString("G01 Z%1\n").arg(safeZ);
    gcodes += QString("G01 F%1\n").arg(drawingSpeed);
    gcodes += QString("M204 A%1\n").arg(drawingAcceleration);

    gcodes += "#OnValue = 255\n";
    gcodes += QString("#UpZ = %1\n").arg(upZ);
    gcodes += QString("#DownZ = %1\n").arg(downZ);

    QString zUp = "G01 Z[#UpZ]\n";
    QString zDown = "G01 Z[#DownZ]\n";
    QString laserOn = "M03 S[#OnValue]\n";
	QString laserOff = "M03 S0\n";

	QString startDrawing = zDown;
	QString finishDrawing = zUp;

	if (cbDrawingEffector->currentText() == "Laser")
	{
		startDrawing = laserOn;
		finishDrawing = laserOff;
	}

//	int curX = 0;
//	int curY = 0;

//	if (lines.size() > 0)
//	{
//		for (int i = 0; i < lines.size(); i++)
//		{
//			if (curX != lines[i].p1().x() || curY != -lines[i].p1().y())
//			{
//                gcodes += finishDrawing;

//				curX = lines[i].p1().x();
//				curY = -lines[i].p1().y();

//                gcodes += QString("G01") + " X" + QString::number(curX) + " Y" + QString::number(curY) + "\n";
//                gcodes += startDrawing;
//			}

//            if (curX != lines[i].p2().x() || curY != -lines[i].p2().y())
//            {
//                curX = lines[i].p2().x();
//                curY = -lines[i].p2().y();

//                gcodes += QString("G01") + " X" + QString::number(curX) + " Y" + QString::number(curY) + "\n";
//            }
//		}

//		gcodes += finishDrawing;
//	}

    float curXf = 0;
    float curYf = 0;

    foreach(QVector<QPointF> points, Vectors)
    {
        gcodes += finishDrawing;

        int index = 0;
        int begin = 0;
        int end = points.count() - 1;

        foreach(QPointF point, points)
        {
            curXf = point.x();
            curYf = -point.y();

            gcodes += QString("G01") + " X" + QString::number(curXf, 'f', 1) + " Y" + QString::number(curYf, 'f', 1) + "\n";

            if (index == begin)
            {
                gcodes += startDrawing;
            }
            if (index == end)
            {
                gcodes += finishDrawing;
            }

            index++;
        }
    }

	if (images.size() > 0)
	{
		Image lastImage = images.back();
		QImage image = lastImage.Pixmap->toImage();
		int hS = lastImage.Size.y() * (1.0f / lastImage.LineSpace);

		image = image.scaledToHeight(hS);

		QString binaries;

		bool isWhite = true;
		QString gcode;

		int counter = 0;
		int realX = 0;

		int offsetX = image.width() / 2;
		int offsetY = image.height() / 2;

		float lastX = (0 - offsetX) * lastImage.LineSpace;
		float lastY = (0 - offsetY) * lastImage.LineSpace;;

		for (int i = 0; i < image.height(); i++)
		{
			for (int j = 0; j < image.width(); j++)
			{
				realX = j;

				if (i % 2 == 1)
				{
					j = image.width() - 1 - j;
				}

				QRgb pixelValue = image.pixel(j, i);

				QColor colorValue = image.pixelColor(QPoint(j, i));
				int red = colorValue.red();
				int green = colorValue.green();
				int blue = colorValue.blue();
				int alpha = colorValue.alpha();

				float xPos = (j - offsetX) * lastImage.LineSpace;
				float yPos = -(i - offsetY) * lastImage.LineSpace;

				float distance = sqrt(pow(xPos - lastX, 2) + pow(yPos - lastY, 2));

				lastX = xPos;
				lastY = yPos;

				if (lastImage.Conversion == "Threshold")
				{
					if (lastImage.ToolType == "Line")
					{
						// Black point
						if (red == 0 && green == 0 && blue == 0 && alpha == 255)
						{
							binaries += "0";

							if (isWhite == true || realX == 0)
							{
								gcodes += QString("G01") + " X" + QString::number(xPos) + " Y" + QString::number(yPos) + "\n";
								gcodes += startDrawing + "\n";
								isWhite = false;
							}
						}
						else
						{
							binaries += "1";

							if (isWhite == false)
							{
								gcodes += QString("G01") + " X" + QString::number(xPos) + " Y" + QString::number(yPos) + "\n";
								gcodes += finishDrawing + "\n";
								isWhite = true;
							}
						}
					}
					else if (lastImage.ToolType == "Dot")
					{
						if (distance < lastImage.LineSpace)
							continue;

						// Black point
						if (red == 0 && green == 0 && blue == 0 && alpha == 255)
						{
							gcodes += QString("G01") + " X" + QString::number(xPos) + " Y" + QString::number(yPos) + "\n";;
							gcodes += startDrawing + "\n";
							gcodes += finishDrawing + "\n";
						}
					}
				}
				else if (lastImage.Conversion == "Gray")
				{
					if (distance < lastImage.LineSpace)
						continue;
                    gcodes += QString("G01") + " X" + QString::number(xPos) + " Y" + QString::number(yPos) + "\n";
					gcodes += "#100 = " + QString::number(colorValue.black()) + "\n";
					gcodes += startDrawing + "\n";
				}
				
				j = realX;
			}
			binaries += "\n";
		}
	}

	gcodes += finishDrawing + "\n";
	pteGcodeEditor->setPlainText(gcodes);
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
