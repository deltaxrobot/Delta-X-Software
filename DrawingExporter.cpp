#include "DrawingExporter.h"

DrawingExporter::DrawingExporter(QWidget *parent)
	: QWidget(parent)
{

}

void DrawingExporter::SetDrawingParameterPointer(QLabel *imageForDrawing, QLabel * wImage, QLabel * hImage, QLineEdit * heightScale, QLineEdit * widthScale, QLineEdit * space, QLineEdit *drawingThresValue, QSlider* drawingThresSlider,QComboBox * drawMethod, QComboBox* conversionTool)
{
	lbImageForDrawing = imageForDrawing;
	lbWImage = wImage;
	lbHImage = hImage;
	leHeightScale = heightScale;
	leWidthScale = widthScale;
	leSpace = space;
	leDrawingThreshold = drawingThresValue;
	hsDrawingThreshold = drawingThresSlider;
	cbDrawMethod = drawMethod;
	cbConversion = conversionTool;

	lbImageForDrawing->setScaledContents(true);

	initEnvent();
}

void DrawingExporter::SetDrawingAreaWidget(DrawingWidget * drawingWidget)
{
	drawingArea = drawingWidget;
}

DrawingExporter::~DrawingExporter()
{
}

void DrawingExporter::OpenImage()
{
	QString imageName;
	imageName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

	if (imageName == "")
		return;

	originPixmap = new QPixmap(imageName);
	effectPixmap = new QPixmap(imageName);

	ApplyConversion();
}

void DrawingExporter::ConvertToDrawingArea()
{
	if (effectPixmap == nullptr)
		return;

	drawingArea->ClearShape();
	drawingArea->ClearImage();
	drawingArea->InitGrid();

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
            double eps = 0.00025f;
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

            drawingArea->Vectors.append(points);

			//cv::polylines(matClone, approx, true, cv::Scalar(0, 0, 0, 255));

            float x1 = approx[approx.size() - 1].x * scale - xOffset;
            float y1 = approx[approx.size() - 1].y * scale - yOffset;
            float x2 = approx[0].x * scale - xOffset;
            float y2 = approx[0].y * scale - yOffset;

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

		if (leDrawingThreshold->text().toInt() < 0)
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
					image.setPixel(i, j, qRgba(255, 255, 255, 0));
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
				int value = grayValue > thresh ? 0 : 255;

				int alpha = 255 - value;

				if (color.alpha() == 0)
				{
					value = 255;
					alpha = 0;
				}

				image.setPixel(i, j, qRgba(value, value, value, alpha));
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
}
