#pragma once

#include <QWidget>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpixmap.h>
#include <qcombobox.h>
#include <qcheckbox.h>
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
    void SetDrawingParameterPointer(QLabel *ImageForDrawing, QLabel *wImage, QLabel *hImage, QLineEdit *heightScale, QLineEdit *widthScale, QLineEdit *scale, QLineEdit *drawingThresValue, QSlider* drawingThresSlider, QCheckBox* inverse ,QComboBox* drawMethod, QComboBox* conversionTool);
    void SetGcodeExportParameterPointer(QLineEdit* safeZHeight, QLineEdit* travelSpeed, QLineEdit* drawingSpeed, QLineEdit* drawingAcceleration);

    void SetDrawingAreaWidget(DrawingWidget* drawingWidget);
    void SetGcodeEditor(QTextEdit* gcodeEditor);
    void SetEffector(QComboBox* drawingEffector);
    ~DrawingExporter();

public slots:
	void OpenImage();
	void ConvertToDrawingArea();
    void ExportGcodes();
	void ApplyConversion();
	void ChangeSize();
	void ScaleEffectImage();

private:
	void initEnvent();

    QTextEdit* pteGcodeEditor;
    QComboBox* cbDrawingEffector;

    QLineEdit* leSafeZHeight;
    QLineEdit* leTravelSpeed;
    QLineEdit* leDrawingSpeed;
    QLineEdit* leDrawingAcceleration;

	QLabel *lbWImage;
	QLabel *lbHImage;
	QLineEdit *leHeightScale;
	QLineEdit *leWidthScale;
	QLineEdit *leSpace;
	QLineEdit *leDrawingThreshold;
	QSlider* hsDrawingThreshold;
    QCheckBox* cbInverse;
	QComboBox* cbDrawMethod;
	QComboBox* cbConversion;

	QLabel* lbImageForDrawing;



	QPixmap* originPixmap;
	QPixmap* effectPixmap;
	DrawingWidget* drawingArea;

	cv::Mat mat;
	cv::Mat result;
};
