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

	QPixmap pix = QPixmap(QString::fromUtf8("icon/Circle-limit.png"));
	QPixmap pix1 = QPixmap(QString::fromUtf8("icon/grid-10-pixel.png"));
	QPixmap pix2 = QPixmap(QString::fromUtf8("icon/grid-axis.png"));
		
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

void DrawingWidget::AddLine(QPoint p1, QPoint p2)
{
	QLine l;
	l.setPoints(p1, p2);
	lines.push_back(l);

	QPixmap pix = *pixmap();
	cv::Mat matPix = ImageTool::QPixmapToCvMat(pix);

	float ratio = (float)pix.height() / height();

	QLine line;

	int xOffset = height() / 2;
	int yOffset = width() / 2;

	line.setP1(QPoint((p1.x() + xOffset) * ratio, (p1.y() + yOffset) * ratio));
	line.setP2(QPoint((p2.x() + xOffset) * ratio, (p2.y() + yOffset) * ratio));

	QPainter p(&pix);

	p.begin(this);
	p.drawLine(line);
	p.end();

	matPix = ImageTool::QPixmapToCvMat(pix);
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

void DrawingWidget::ExportGcodes()
{
	QString gcodes = "G28\n";
	gcodes += "M360 E3\n";
	gcodes += "G01 F200\n";
	gcodes += "G01 Z-295\n";
	gcodes += "G01 F15\n";
	gcodes += "M204 A800\n";
	gcodes += "M03 S0\n";
	gcodes += "#100 = 255\n";
	gcodes += "#200 = -300\n";
	gcodes += "#201 = -310\n";

	QString zUp = "G01 Z[#200]\n";
	QString zDown = "G01 Z[#201]\n";
	QString laserOn = "M03 S[#100]\n";
	QString laserOff = "M03 S0\n";

	QString startDrawing = zDown;
	QString finishDrawing = zUp;

	if (cbDrawingEffector->currentText() == "Laser")
	{
		startDrawing = laserOn;
		finishDrawing = laserOff;
	}

	int curX = 0;
	int curY = 0;

	if (lines.size() > 0)
	{
		for (int i = 0; i < lines.size(); i++)
		{
			if (curX != lines[i].p1().x() || curY != -lines[i].p1().y())
			{
				gcodes += finishDrawing;

				curX = lines[i].p1().x();
				curY = -lines[i].p1().y();

				gcodes += QString("G01") + " X" + QString::number(curX) + " Y" + QString::number(curY) + "\n";
				gcodes += startDrawing;
			}

			curX = lines[i].p2().x();
			curY = -lines[i].p2().y();

			gcodes += QString("G01") + " X" + QString::number(curX) + " Y" + QString::number(curY) + "\n";
		}

		gcodes += finishDrawing;
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

		/*gcodes += QString("#200 = -290") + "\n";
		gcodes += QString("#201 = -300") + "\n\n";*/

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

				//QColor colorValue(pixelValue);
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

							//-----------------
							/*gcodes += zUp + "\n";
							gcodes += QString("G01") + " X" + QString::number(i) + " Y" + QString::number(j) + "\n";
							gcodes += zDown + "\n";*/
							//-----------------

							//gcode = QString("G01") + " X" + QString::number(i - offsetX) + " Y" + QString::number(j - offsetY) + "\n";

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
					//gcodes += "#100 = " + QString::number(colorValue.black() < 100 ? 100: colorValue.black()) + "\n";
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
