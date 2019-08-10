#pragma once

#include <QWidget>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpixmap.h>
#include <qcombobox.h>
#include <DrawingWidget.h>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>

class DrawingExporter : public QWidget
{
	Q_OBJECT

public:
	DrawingExporter(QWidget *parent);
	void SetDrawingParameterPointer(QLabel *ImageForDrawing, QLabel *wImage, QLabel *hImage, QLineEdit *heightScale, QLineEdit *widthScale, QLineEdit *scale, QLineEdit *drawingThresValue, QSlider* drawingThresSlider, QComboBox* drawMethod, QComboBox* conversionTool);
	void SetDrawingAreaWidget(DrawingWidget* drawingWidget);
	~DrawingExporter();

public slots:
	void OpenImage();
	void ConvertToDrawingArea();
	void ApplyConversion();
	void ChangeSize();
	void ScaleEffectImage();

private:
	void initEnvent();

	QLabel *lbWImage;
	QLabel *lbHImage;
	QLineEdit *leHeightScale;
	QLineEdit *leWidthScale;
	QLineEdit *leSpace;
	QLineEdit *leDrawingThreshold;
	QSlider* hsDrawingThreshold;
	QComboBox* cbDrawMethod;
	QComboBox* cbConversion;

	QLabel* lbImageForDrawing;

	QPixmap* originPixmap;
	QPixmap* effectPixmap;
	DrawingWidget* drawingArea;

	cv::Mat mat;
	cv::Mat result;
};
