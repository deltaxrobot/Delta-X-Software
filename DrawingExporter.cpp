#include "DrawingExporter.h"

DrawingExporter::DrawingExporter(QWidget *parent)
	: QWidget(parent)
{

}

void DrawingExporter::SetDrawingParameterPointer(QLabel *imageForDrawing, QLabel * wImage, QLabel * hImage, QLineEdit * heightScale, QLineEdit * widthScale, QLineEdit * space, QLineEdit *drawingThresValue, QSlider* drawingThresSlider, QCheckBox* inverse,QComboBox * drawMethod, QComboBox* conversionTool)
{
	lbImageForDrawing = imageForDrawing;
	lbWImage = wImage;
	lbHImage = hImage;
	leHeightScale = heightScale;
	leWidthScale = widthScale;
	leSpace = space;
	leDrawingThreshold = drawingThresValue;
	hsDrawingThreshold = drawingThresSlider;
    cbInverse = inverse;
	cbDrawMethod = drawMethod;
	cbConversion = conversionTool;

	lbImageForDrawing->setScaledContents(true);

    initEnvent();
}

void DrawingExporter::SetGcodeExportParameterPointer(QLineEdit *safeZHeight, QLineEdit *travelSpeed, QLineEdit *drawingSpeed, QLineEdit *drawingAcceleration)
{
    leSafeZHeight = safeZHeight;
    leTravelSpeed = travelSpeed;
    leDrawingSpeed = drawingSpeed;
    leDrawingAcceleration = drawingAcceleration;
}

void DrawingExporter::SetDrawingPointInPlane(QLineEdit *point1, QLineEdit *point2, QLineEdit *point3)
{
    lePoint1 = point1;
    lePoint2 = point2;
    lePoint3 = point3;
}

void DrawingExporter::SetDrawingAreaWidget(DrawingWidget * drawingWidget)
{
    drawingArea = drawingWidget;
}

void DrawingExporter::SetGcodeEditor(QTextEdit *gcodeEditor)
{
    pteGcodeEditor = gcodeEditor;
}

void DrawingExporter::SetEffector(QComboBox *drawingEffector)
{
    cbDrawingEffector = drawingEffector;
}

DrawingExporter::~DrawingExporter()
{
}

void DrawingExporter::OpenImage()
{
	QString imageName;
    imageName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.svg)"));

	if (imageName == "")
		return;

    if (imageName.contains(".svg"))
    {
        ConvertSVGToArea(imageName);
    }
    else
    {
        originPixmap = new QPixmap(imageName);
        effectPixmap = new QPixmap(imageName);

        ApplyConversion();
    }

}

void DrawingExporter::ConvertToDrawingArea()
{
	if (effectPixmap == nullptr)
		return;

	drawingArea->ClearShape();
	drawingArea->ClearImage();
	drawingArea->InitGrid();

    drawingArea->Vectors.clear();

	if (cbConversion->currentText() == "Vectorize")
	{
		std::vector<std::vector<cv::Point> > contoursContainer;
		findContours(mat, contoursContainer, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

		cv::Mat matClone = mat.clone();
		matClone = cv::Scalar(255, 255, 255, 255);

		float ratio = (float)effectPixmap->width() / effectPixmap->height();
        float hS = leHeightScale->text().toInt();
        float wS = hS * ratio;

		float scale = (float)hS / mat.rows;

        float xOffset = wS / 2;
        float yOffset = hS / 2;

		for (int i = 0; i < contoursContainer.size(); i++)
		{
			double arclen = cv::arcLength(contoursContainer[i], true);
            double eps = 0.001f;
			double epsilon = arclen * eps;

			std::vector<cv::Point> approx;
			cv::approxPolyDP(contoursContainer[i], approx, epsilon, true);

            QVector<QPointF> points;

			for (int j = 0; j < approx.size() - 1; j++)
			{
                float x1 = approx[j].x * scale - xOffset;
                float y1 = approx[j].y * scale - yOffset;
                float x2 = approx[j + 1].x * scale - xOffset;
                float y2 = approx[j + 1].y * scale - yOffset;

                drawingArea->AddLineToStack(QPoint(x1, y1), QPoint(x2, y2));

                points.append(QPointF(x1, y1));
			}



			//cv::polylines(matClone, approx, true, cv::Scalar(0, 0, 0, 255));

            float x1 = approx[approx.size() - 1].x * scale - xOffset;
            float y1 = approx[approx.size() - 1].y * scale - yOffset;
            float x2 = approx[0].x * scale - xOffset;
            float y2 = approx[0].y * scale - yOffset;

            points.append(QPointF(x1, y1));
            points.append(QPointF(x2, y2));

            drawingArea->Vectors.append(points);

            drawingArea->AddLineToStack(QPoint(x1, y1), QPoint(x2, y2));
		}

        drawingArea->DrawLineFromStack();
	}
	else
	{
		float ratio = (float)effectPixmap->width() / effectPixmap->height();

		int hS = leHeightScale->text().toInt();
		int wS = hS * ratio;

		int x = (drawingArea->width() - wS) / 2;
		int y = (drawingArea->height() - leHeightScale->text().toInt()) / 2;

		drawingArea->AddImage(x, y, wS, hS, *effectPixmap, leSpace->text().toFloat(), cbDrawMethod->currentText(), cbConversion->currentText());
    }
}

void DrawingExporter::ConvertSVGToArea(QString fileName)
{
    // Load file SVG
    svgWidget.load(fileName);

    // Hiển thị widget
    svgWidget.show();
}

void DrawingExporter::ExportGcodes()
{
    // Lấy giá trị từ QLineEdit và phân tích tọa độ
    QStringList point1 = lePoint1->text().split(",");
    QStringList point2 = lePoint2->text().split(",");
    QStringList point3 = lePoint3->text().split(",");

    if (point1.size() < 3 || point2.size() < 3 || point3.size() < 3) {
        qDebug(nullptr, "Error", "Invalid coordinates for points A, B, or C.");
        return;
    }

    float xA = point1[0].toFloat();
    float yA = point1[1].toFloat();
    float zA = point1[2].toFloat();

    float xB = point2[0].toFloat();
    float yB = point2[1].toFloat();
    float zB = point2[2].toFloat();

    float xC = point3[0].toFloat();
    float yC = point3[1].toFloat();
    float zC = point3[2].toFloat();

    // Tính vector pháp tuyến của mặt phẳng
    QVector3D v1(xB - xA, yB - yA, zB - zA);
    QVector3D v2(xC - xA, yC - yA, zC - zA);
    QVector3D normal = QVector3D::crossProduct(v1, v2);

    float A = normal.x();
    float B = normal.y();
    float C = normal.z();
    float D = -(A * xA + B * yA + C * zA);

    // Hàm tính toán giá trị Z trên mặt phẳng
    auto calculateZ = [&](float x, float y) -> float {
        if (C == 0.0f) return zA; // Trường hợp mặt phẳng không hợp lệ
        return -(A * x + B * y + D) / C;
    };

    pteGcodeEditor->setPlainText("");

    float downZ = leSafeZHeight->text().toFloat();
    float upZ = downZ + 10;
    float safeZ = downZ + 50;
    int travelSpeed = leTravelSpeed->text().toInt();
    int drawingSpeed = leDrawingSpeed->text().toInt();
    int drawingAcceleration = leDrawingAcceleration->text().toInt();

    QString gcodes = "G28\n";

    if (cbDrawingEffector->currentText() == "Laser")
    {
        gcodes += ";Select laser head\n";
        gcodes += "M360 E3\n";
        gcodes += ";Turn off laser head\n";
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

    pteGcodeEditor->append(gcodes);
    gcodes = "";

    if (cbDrawingEffector->currentText() == "Laser")
    {
        startDrawing = laserOn;
        finishDrawing = laserOff;
    }

    if (drawingArea->Vectors.empty() == false)
    {
        foreach(QVector<QPointF> points, drawingArea->Vectors)
        {
            gcodes += finishDrawing;

            int index = 0;
            int begin = 0;
            int end = points.count() - 1;

            foreach(QPointF point, points)
            {
                float curXf = point.x();
                float curYf = -point.y();
                float curZf = calculateZ(curXf, curYf); // Tính Z dựa trên mặt phẳng

                gcodes += QString("G01") +
                          " X" + QString::number(curXf, 'f', 1) +
                          " Y" + QString::number(curYf, 'f', 1) +
                          " Z" + QString::number(curZf, 'f', 1) + "\n";

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

            pteGcodeEditor->append(gcodes);
            gcodes = "";
        }
    }

    else if (drawingArea->Images.size() > 0)
    {
        Image lastImage = drawingArea->Images.back();
        lastImage.LineSpace = leSpace->text().toFloat();
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

                if (cbConversion->currentText() == "Threshold")
                {
                    if (cbDrawMethod->currentText() == "Line")
                    {
                        // Black point
                        if (red == 0 && green == 0 && blue == 0 && alpha == 255)
                        {
                            binaries += "0";

                            if (isWhite == true || realX == 0)
                            {
                                float zPos = calculateZ(xPos, yPos); // Tính Z dựa trên mặt phẳng

                                gcodes += QString("G01") +
                                          " X" + QString::number(xPos, 'f', 1) +
                                          " Y" + QString::number(yPos, 'f', 1) +
                                          " Z" + QString::number(zPos, 'f', 1) + "\n";
                                gcodes += startDrawing + "\n";
                                isWhite = false;
                            }
                        }
                        else
                        {
                            binaries += "1";

                            if (isWhite == false)
                            {                                
                                float zPos = calculateZ(lastX, yPos); // Tính Z dựa trên mặt phẳng

                                gcodes += QString("G01") +
                                          " X" + QString::number(lastX, 'f', 1) +
                                          " Y" + QString::number(yPos, 'f', 1) +
                                          " Z" + QString::number(zPos, 'f', 1) + "\n";
                                gcodes += finishDrawing + "\n";
                                isWhite = true;
                            }
                        }
                    }
                    else if (cbDrawMethod->currentText() == "Dot")
                    {
                        if (cbConversion->currentText() == "Gray")
                        if (distance < lastImage.LineSpace)
                            continue;

                        // Black point
                        if (red == 0 && green == 0 && blue == 0 && alpha == 255)
                        {
                            float zPos = calculateZ(xPos, yPos); // Tính Z dựa trên mặt phẳng
                            gcodes += QString("G01") +
                                      " X" + QString::number(xPos, 'f', 1) +
                                      " Y" + QString::number(yPos, 'f', 1) +
                                      " Z" + QString::number(zPos, 'f', 1) + "\n";

                            gcodes += startDrawing + "\n";
                            gcodes += finishDrawing + "\n";
                        }
                    }
                }
                else if (cbConversion->currentText() == "Gray")
                {
                    if (distance < lastImage.LineSpace)
                        continue;
                    float zPos = calculateZ(xPos, yPos); // Tính Z dựa trên mặt phẳng
                    gcodes += QString("G01") +
                              " X" + QString::number(xPos, 'f', 1) +
                              " Y" + QString::number(yPos, 'f', 1) +
                              " Z" + QString::number(zPos, 'f', 1) + "\n";
                    gcodes += "#100 = " + QString::number(colorValue.black()) + "\n";
                    gcodes += startDrawing + "\n";

                }

                lastX = xPos;
                lastY = yPos;

                j = realX;

                pteGcodeEditor->append(gcodes);
                gcodes = "";
            }
            binaries += "\n";
        }
    }
    pteGcodeEditor->append(finishDrawing + "\n");
}

void DrawingExporter::ApplyConversion()
{
	if (originPixmap == nullptr)
		return;

	QImage image = originPixmap->toImage();
	image = image.convertToFormat(QImage::Format_ARGB32);

	int thresh = hsDrawingThreshold->value();

	if (leDrawingThreshold->text().toInt() < 0)
	{
		leDrawingThreshold->setText(QString("-") + QString::number(thresh));
	}
	else
	{
		leDrawingThreshold->setText(QString::number(thresh));
	}

	// transparent pixel to white pixel

	for (int i = 0; i < image.width(); ++i)
	{
		for (int j = 0; j < image.height(); ++j)
		{
			QColor color = image.pixelColor(QPoint(i, j));

			if (color.alpha() == 0)
				image.setPixel(i, j, qRgba(255, 255, 255, 255));
		}
	}

	if (cbConversion->currentText() == "Gray")
	{
		mat = ImageTool::QImageToCvMat(image);
		cv::cvtColor(mat, mat, CV_BGR2GRAY);

		image = ImageTool::cvMatToQImage(mat);
		image = image.convertToFormat(QImage::Format_ARGB32);
	}
	else if (cbConversion->currentText() == "Vectorize")
	{
		mat = ImageTool::QImageToCvMat(image);
		result = mat.clone();
		result = cv::Scalar(255, 255, 255, 255);
		
		cv::cvtColor(mat, mat, CV_BGR2GRAY);

        if (cbInverse->isChecked())
		{
			cv::threshold(mat, mat, thresh, 255, CV_THRESH_BINARY_INV);
		}
		else
		{
			cv::threshold(mat, mat, thresh, 255, CV_THRESH_BINARY);
		}

		/*cv::Mat edges;

		cv::Canny(mat, edges, 50, 200);*/

		std::vector<std::vector<cv::Point> > contoursContainer;
		findContours(mat, contoursContainer, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < contoursContainer.size(); i++)
		{
			double arclen = cv::arcLength(contoursContainer[i], true);
			double eps = 0.0005f;
			double epsilon = arclen * eps;

			std::vector<cv::Point> approx;
			cv::approxPolyDP(contoursContainer[i], approx, epsilon, true);

			/*for (int j = 0; j < approx.size(); j++)
			{
				cv::circle(result, approx[j], 7, cv::Scalar(0, 255, 0, 255), -1);
			}*/
			cv::polylines(result, approx, true, cv::Scalar(0, 0, 0, 255));
		}		

		image = ImageTool::cvMatToQImage(result);
		image = image.convertToFormat(QImage::Format_ARGB32);

		for (int i = 0; i < image.width(); ++i)
		{
			for (int j = 0; j < image.height(); ++j)
			{
				QColor color = image.pixelColor(QPoint(i, j));

				if (color.black() == 0)
                    image.setPixel(i, j, qRgba(255, 255, 255, 255));
			}
		}
	}

	else
	{
		for (int i = 0; i < image.width(); ++i)
		{
			for (int j = 0; j < image.height(); ++j)
			{
				QColor color = image.pixelColor(QPoint(i, j));
				int grayValue = color.black();
                int value;

                if (!cbInverse->isChecked())
                {
                    value = grayValue > thresh ? 0 : 255;
                }
                else
                {
                    value = grayValue > thresh ? 255 : 0;
                }

//				int alpha = 255 - value;

//				if (color.alpha() == 0)
//				{
//					value = 255;
//					alpha = 0;
//				}

                image.setPixel(i, j, qRgba(value, value, value, 255));
			}
		}
	}
	
		
	*effectPixmap = effectPixmap->fromImage(image);

	float ratio = (float)effectPixmap->width() / effectPixmap->height();
    int h = lbImageForDrawing->height();

    lbImageForDrawing->setMaximumWidth(h * ratio);

	lbWImage->setText(QString("W: ") + QString::number(originPixmap->width()));
	lbHImage->setText(QString("H: ") + QString::number(originPixmap->height()));

	lbImageForDrawing->setPixmap(*effectPixmap);
}

void DrawingExporter::ChangeSize()
{

}

void DrawingExporter::ScaleEffectImage()
{

}

void DrawingExporter::initEnvent()
{
    connect(hsDrawingThreshold, SIGNAL(sliderReleased()), this, SLOT(ApplyConversion()));
	connect(leWidthScale, SIGNAL(textChanged(const QString &)), this, SLOT(ApplyConversion()));
	connect(leHeightScale, SIGNAL(textChanged(const QString &)), this, SLOT(ApplyConversion()));
	connect(cbConversion, SIGNAL(currentTextChanged(const QString &)), this, SLOT(ApplyConversion()));
    connect(cbInverse, SIGNAL(stateChanged(int)), this, SLOT(ApplyConversion()));
}
