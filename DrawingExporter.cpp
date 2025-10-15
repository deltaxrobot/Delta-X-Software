#include "DrawingExporter.h"

#include <QMessageBox>
#include <QtMath>
#include <algorithm>
#include <cmath>

DrawingExporter::DrawingExporter(QWidget *parent)
	: QWidget(parent),
      originPixmap(nullptr),
      effectPixmap(nullptr)
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

    initEvent();
    updateDrawingAreaScale();
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

    if (lePoint1) {
        connect(lePoint1, &QLineEdit::textChanged, this, &DrawingExporter::HandlePlanePointEdited);
    }
    if (lePoint2) {
        connect(lePoint2, &QLineEdit::textChanged, this, &DrawingExporter::HandlePlanePointEdited);
    }
    if (lePoint3) {
        connect(lePoint3, &QLineEdit::textChanged, this, &DrawingExporter::HandlePlanePointEdited);
    }

    refreshPlaneMarkers();
}

void DrawingExporter::SetDrawingAreaWidget(DrawingWidget * drawingWidget)
{
    drawingArea = drawingWidget;
    updateDrawingAreaScale();
    refreshPlaneMarkers();
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

    // Hiá»ƒn thá»‹ widget
    svgWidget.show();
}

void DrawingExporter::ExportGcodes()
{
    if (!pteGcodeEditor) {
        return;
    }

    updateDrawingAreaScale();

    auto requirePoint = [&](QLineEdit* lineEdit, const QString& label, QVector3D& outPoint) -> bool {
        if (!lineEdit) {
            showInputError(tr("Missing input for point %1.").arg(label));
            return false;
        }

        QString errorMessage;
        if (!parsePoint(lineEdit->text(), outPoint, &errorMessage)) {
            showInputError(tr("Invalid coordinates for point %1: %2").arg(label, errorMessage));
            return false;
        }

        return true;
    };

    QVector3D pointA;
    QVector3D pointB;
    QVector3D pointC;

    if (!requirePoint(lePoint1, QStringLiteral("A"), pointA) ||
        !requirePoint(lePoint2, QStringLiteral("B"), pointB) ||
        !requirePoint(lePoint3, QStringLiteral("C"), pointC)) {
        if (drawingArea) {
            drawingArea->SetPlaneMarkers({});
        }
        return;
    }

    QVector<QVector3D> planePoints{pointA, pointB, pointC};
    updatePlaneMarkers(planePoints);

    QVector3D v1 = pointB - pointA;
    QVector3D v2 = pointC - pointA;
    QVector3D normal = QVector3D::crossProduct(v1, v2);

    if (normal.lengthSquared() < 1e-6f) {
        showInputError(tr("Points A, B, and C must not be collinear."));
        return;
    }

    float A = normal.x();
    float B = normal.y();
    float C = normal.z();

    if (qFuzzyIsNull(C)) {
        showInputError(tr("Cannot compute Z because the plane normal has zero Z component."));
        return;
    }

    float D = -(A * pointA.x() + B * pointA.y() + C * pointA.z());

    auto planeZAt = [&](float x, float y) -> float {
        return -(A * x + B * y + D) / C;
    };

    bool ok = false;

    const float referencePlaneZ = (pointA.z() + pointB.z() + pointC.z()) / 3.0f;

    float drawingHeight = referencePlaneZ;
    if (leSafeZHeight) {
        drawingHeight = leSafeZHeight->text().toFloat(&ok);
        if (!ok) {
            showInputError(tr("Invalid drawing Z height."));
            return;
        }
    }

    float drawingOffset = drawingHeight - referencePlaneZ;

    int travelSpeed = 0;
    if (leTravelSpeed) {
        travelSpeed = leTravelSpeed->text().toInt(&ok);
        if (!ok || travelSpeed <= 0) {
            showInputError(tr("Invalid travel speed."));
            return;
        }
    }

    int drawingSpeed = 0;
    if (leDrawingSpeed) {
        drawingSpeed = leDrawingSpeed->text().toInt(&ok);
        if (!ok || drawingSpeed <= 0) {
            showInputError(tr("Invalid drawing speed."));
            return;
        }
    }

    int drawingAcceleration = 0;
    if (leDrawingAcceleration) {
        drawingAcceleration = leDrawingAcceleration->text().toInt(&ok);
        if (!ok || drawingAcceleration < 0) {
            showInputError(tr("Invalid drawing acceleration."));
            return;
        }
    }

    const float liftOffset = std::max(drawingOffset + 10.0f, 5.0f);
    const float safeOffset = std::max(drawingOffset + 50.0f, 15.0f);

    auto drawingZ = [&](float x, float y) -> float {
        return planeZAt(x, y) + drawingOffset;
    };

    auto liftZ = [&](float x, float y) -> float {
        return planeZAt(x, y) + liftOffset;
    };

    auto safeZAt = [&](float x, float y) -> float {
        return planeZAt(x, y) + safeOffset;
    };

    const bool laserMode = cbDrawingEffector && cbDrawingEffector->currentText() == "Laser";

    QStringList lines;
    lines << "G28";

    if (laserMode) {
        lines << ";Select laser head";
        lines << "M360 E3";
        lines << ";Ensure laser head is off";
        lines << "M03 S0";
        lines << "#OnValue = 255";
    }

    lines << QString("G01 F%1").arg(travelSpeed);

    const float globalSafeZ = std::max({
        safeZAt(pointA.x(), pointA.y()),
        safeZAt(pointB.x(), pointB.y()),
        safeZAt(pointC.x(), pointC.y())
    });

    lines << QString("G01 Z%1").arg(globalSafeZ, 0, 'f', 1);
    lines << QString("G01 F%1").arg(drawingSpeed);
    lines << QString("M204 A%1").arg(drawingAcceleration);

    auto appendLine = [&](const QString& line) {
        lines << line;
    };

    auto formatXYZ = [&](float x, float y, float z) {
        return QString("G01 X%1 Y%2 Z%3")
            .arg(x, 0, 'f', 1)
            .arg(y, 0, 'f', 1)
            .arg(z, 0, 'f', 1);
    };

    auto formatZ = [&](float z) {
        return QString("G01 Z%1").arg(z, 0, 'f', 1);
    };

    auto formatXY = [&](float x, float y) {
        return QString("G01 X%1 Y%2")
            .arg(x, 0, 'f', 1)
            .arg(y, 0, 'f', 1);
    };

    auto moveToLift = [&](float x, float y) {
        appendLine(formatZ(globalSafeZ));
        appendLine(formatXY(x, y));
        appendLine(formatZ(liftZ(x, y)));
        if (laserMode) {
            appendLine("M03 S0");
        }
    };

    auto drawTo = [&](float x, float y, bool firstPoint) {
        appendLine(formatXYZ(x, y, drawingZ(x, y)));
        if (firstPoint && laserMode) {
            appendLine("M03 S[#OnValue]");
        }
    };

    auto finishStroke = [&](float x, float y) {
        if (laserMode) {
            appendLine("M03 S0");
        }
        appendLine(formatZ(liftZ(x, y)));
    };

    if (!drawingArea) {
        showInputError(tr("Drawing area is not available."));
        return;
    }

    if (!drawingArea->Vectors.isEmpty()) {
        for (const QVector<QPointF>& path : drawingArea->Vectors) {
            if (path.isEmpty()) {
                continue;
            }

            float startX = path.first().x();
            float startY = -path.first().y();

            moveToLift(startX, startY);

            bool firstPoint = true;
            float lastX = startX;
            float lastY = startY;

            for (const QPointF& point : path) {
                float x = point.x();
                float y = -point.y();
                drawTo(x, y, firstPoint);
                firstPoint = false;
                lastX = x;
                lastY = y;
            }

            finishStroke(lastX, lastY);
        }
    } else if (!drawingArea->Images.isEmpty()) {
        Image lastImage = drawingArea->Images.back();

        if (leSpace) {
            float configuredSpacing = leSpace->text().toFloat(&ok);
            if (ok && configuredSpacing > 0.0f) {
                lastImage.LineSpace = configuredSpacing;
            }
        }

        if (lastImage.LineSpace <= 0.0f) {
            lastImage.LineSpace = 1.0f;
        }

        QImage image = lastImage.Pixmap->toImage();
        int targetHeight = static_cast<int>(lastImage.Size.y() * (1.0f / lastImage.LineSpace));
        if (targetHeight <= 0) {
            targetHeight = 1;
        }
        image = image.scaledToHeight(targetHeight);

        const int offsetX = image.width() / 2;
        const int offsetY = image.height() / 2;

        float lastX = (0 - offsetX) * lastImage.LineSpace;
        float lastY = (0 - offsetY) * lastImage.LineSpace;

        bool strokeActive = false;
        float strokeLastX = 0.0f;
        float strokeLastY = 0.0f;

        const QString drawMethod = cbDrawMethod ? cbDrawMethod->currentText() : QStringLiteral("Line");
        const QString conversionMode = cbConversion ? cbConversion->currentText() : QStringLiteral("Threshold");

        for (int i = 0; i < image.height(); ++i) {
            for (int j = 0; j < image.width(); ++j) {
                int realX = j;

                if (i % 2 == 1) {
                    j = image.width() - 1 - j;
                }

                const QColor colorValue = image.pixelColor(QPoint(j, i));
                const bool isBlackPixel = (colorValue.red() == 0 &&
                                           colorValue.green() == 0 &&
                                           colorValue.blue() == 0 &&
                                           colorValue.alpha() == 255);

                const float xPos = (j - offsetX) * lastImage.LineSpace;
                const float yPos = -(i - offsetY) * lastImage.LineSpace;

                const float distance = std::sqrt(std::pow(xPos - lastX, 2.0f) + std::pow(yPos - lastY, 2.0f));

                if (conversionMode == "Threshold" && drawMethod == "Line") {
                    if (isBlackPixel) {
                        if (!strokeActive) {
                            moveToLift(xPos, yPos);
                            drawTo(xPos, yPos, true);
                            strokeActive = true;
                            strokeLastX = xPos;
                            strokeLastY = yPos;
                        } else {
                            drawTo(xPos, yPos, false);
                            strokeLastX = xPos;
                            strokeLastY = yPos;
                        }
                    } else if (strokeActive) {
                        finishStroke(strokeLastX, strokeLastY);
                        strokeActive = false;
                    }
                } else if (conversionMode == "Threshold" && drawMethod == "Dot") {
                    if (distance < lastImage.LineSpace) {
                        j = realX;
                        continue;
                    }

                    if (isBlackPixel) {
                        moveToLift(xPos, yPos);
                        drawTo(xPos, yPos, true);
                        finishStroke(xPos, yPos);
                    }
                } else if (conversionMode == "Gray") {
                    if (distance < lastImage.LineSpace) {
                        j = realX;
                        continue;
                    }

                    moveToLift(xPos, yPos);
                    appendLine(QString("#100 = %1").arg(colorValue.black()));
                    drawTo(xPos, yPos, true);
                    finishStroke(xPos, yPos);
                }

                lastX = xPos;
                lastY = yPos;
                j = realX;
            }

            if (strokeActive) {
                finishStroke(strokeLastX, strokeLastY);
                strokeActive = false;
            }
        }
    } else {
        appendLine("; No drawing data available");
    }

    appendLine(formatZ(globalSafeZ));
    if (laserMode) {
        appendLine("M03 S0");
    }

    QString output = lines.join("\n");
    if (!output.endsWith('\n')) {
        output.append('\n');
    }
    pteGcodeEditor->setPlainText(output);
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

void DrawingExporter::initEvent()
{
    if (hsDrawingThreshold) {
        connect(hsDrawingThreshold, &QSlider::sliderReleased, this, &DrawingExporter::ApplyConversion);
    }
    if (leWidthScale) {
        connect(leWidthScale, &QLineEdit::textChanged, this, &DrawingExporter::HandleScaleChanged);
    }
    if (leHeightScale) {
        connect(leHeightScale, &QLineEdit::textChanged, this, &DrawingExporter::HandleScaleChanged);
    }
    if (cbConversion) {
        connect(cbConversion, &QComboBox::currentTextChanged, this, &DrawingExporter::ApplyConversion);
    }
    if (cbInverse) {
        connect(cbInverse, &QCheckBox::stateChanged, this, &DrawingExporter::ApplyConversion);
    }
}

void DrawingExporter::HandleScaleChanged(const QString& value)
{
    Q_UNUSED(value);
    updateDrawingAreaScale();
    ApplyConversion();
}

void DrawingExporter::HandlePlanePointEdited()
{
    refreshPlaneMarkers();
}

bool DrawingExporter::parsePoint(const QString& text, QVector3D& outPoint, QString* errorMessage) const
{
    QString trimmedText = text;
    if (trimmedText.isEmpty()) {
        if (errorMessage) {
            *errorMessage = tr("Value is empty.");
        }
        return false;
    }

    QStringList parts = trimmedText.split(',', Qt::SkipEmptyParts);
    if (parts.size() != 3) {
        if (errorMessage) {
            *errorMessage = tr("Expected three comma-separated values (x,y,z).");
        }
        return false;
    }

    bool okX = false;
    bool okY = false;
    bool okZ = false;

    float x = parts[0].trimmed().toFloat(&okX);
    float y = parts[1].trimmed().toFloat(&okY);
    float z = parts[2].trimmed().toFloat(&okZ);

    if (!okX || !okY || !okZ) {
        if (errorMessage) {
            QStringList invalidTokens;
            if (!okX) invalidTokens << parts[0].trimmed();
            if (!okY) invalidTokens << parts[1].trimmed();
            if (!okZ) invalidTokens << parts[2].trimmed();
            *errorMessage = tr("Could not convert %1 to numbers.").arg(invalidTokens.join(", "));
        }
        return false;
    }

    outPoint = QVector3D(x, y, z);
    return true;
}

void DrawingExporter::showInputError(const QString& message) const
{
    QMessageBox::warning(const_cast<DrawingExporter*>(this), tr("Invalid Input"), message);
}

void DrawingExporter::updateDrawingAreaScale()
{
    if (!drawingArea) {
        return;
    }

    bool okWidth = false;
    bool okHeight = false;

    float widthMm = 0.0f;
    float heightMm = 0.0f;

    if (leWidthScale) {
        widthMm = leWidthScale->text().toFloat(&okWidth);
    }
    if (leHeightScale) {
        heightMm = leHeightScale->text().toFloat(&okHeight);
    }

    if (!okWidth && okHeight && drawingArea->height() > 0) {
        widthMm = heightMm * static_cast<float>(drawingArea->width()) / static_cast<float>(drawingArea->height());
        okWidth = true;
    } else if (!okHeight && okWidth && drawingArea->width() > 0) {
        heightMm = widthMm * static_cast<float>(drawingArea->height()) / static_cast<float>(drawingArea->width());
        okHeight = true;
    }

    drawingArea->SetPhysicalSize(okWidth ? widthMm : 0.0f,
                                 okHeight ? heightMm : 0.0f);
}

void DrawingExporter::refreshPlaneMarkers()
{
    if (!drawingArea) {
        return;
    }

    QVector3D pointA;
    QVector3D pointB;
    QVector3D pointC;

    if (parsePoint(lePoint1 ? lePoint1->text() : QString(), pointA, nullptr) &&
        parsePoint(lePoint2 ? lePoint2->text() : QString(), pointB, nullptr) &&
        parsePoint(lePoint3 ? lePoint3->text() : QString(), pointC, nullptr)) {
        updatePlaneMarkers({pointA, pointB, pointC});
    } else {
        drawingArea->SetPlaneMarkers({});
    }
}

void DrawingExporter::updatePlaneMarkers(const QVector<QVector3D>& points)
{
    if (!drawingArea) {
        return;
    }

    QVector<QPointF> markers;
    markers.reserve(points.size());
    for (const QVector3D& point : points) {
        markers.append(QPointF(point.x(), point.y()));
    }

    drawingArea->SetPlaneMarkers(markers);
}


