#pragma once

#include <QWidget>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpixmap.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <DrawingWidget.h>
#include <QSvgWidget>


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
    void SetDrawingPointInPlane(QLineEdit* point1, QLineEdit* point2, QLineEdit* point3);

    void SetDrawingAreaWidget(DrawingWidget* drawingWidget);
    void SetGcodeEditor(QTextEdit* gcodeEditor);
    void SetEffector(QComboBox* drawingEffector);
    ~DrawingExporter();

public slots:
	void OpenImage();
	void ConvertToDrawingArea();
    void ConvertSVGToArea(QString fileName);
    void ExportGcodes();
	void ApplyConversion();
	void ChangeSize();
	void ScaleEffectImage();

private slots:
    void HandleScaleChanged(const QString& value);
    void HandlePlanePointEdited();

private:
	void initEvent();
    bool parsePoint(const QString& text, QVector3D& outPoint, QString* errorMessage = nullptr) const;
    void showInputError(const QString& message) const;
    void updateDrawingAreaScale();
    void refreshPlaneMarkers();
    void updatePlaneMarkers(const QVector<QVector3D>& points);

    QSvgWidget svgWidget;
    QTextEdit* pteGcodeEditor = nullptr;
    QComboBox* cbDrawingEffector = nullptr;

    QLineEdit* leSafeZHeight = nullptr;
    QLineEdit* leTravelSpeed = nullptr;
    QLineEdit* leDrawingSpeed = nullptr;
    QLineEdit* leDrawingAcceleration = nullptr;

    QLineEdit* lePoint1 = nullptr;
    QLineEdit* lePoint2 = nullptr;
    QLineEdit* lePoint3 = nullptr;

	QLabel *lbWImage = nullptr;
	QLabel *lbHImage = nullptr;
	QLineEdit *leHeightScale = nullptr;
	QLineEdit *leWidthScale = nullptr;
	QLineEdit *leSpace = nullptr;
	QLineEdit *leDrawingThreshold = nullptr;
	QSlider* hsDrawingThreshold = nullptr;
    QCheckBox* cbInverse = nullptr;
	QComboBox* cbDrawMethod = nullptr;
	QComboBox* cbConversion = nullptr;

	QLabel* lbImageForDrawing = nullptr;



	QPixmap* originPixmap = nullptr;
	QPixmap* effectPixmap = nullptr;
	DrawingWidget* drawingArea = nullptr;

	cv::Mat mat;
	cv::Mat result;
};
