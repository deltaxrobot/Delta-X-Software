#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <qmath.h>
#include <qvector4d.h>
#include <qvector3d.h>
#include <qvector2d.h>
#include <qvector.h>
#include <qplaintextedit.h>
#include <qcombobox.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageUnity.h>

#include <QDir>
#include <QCoreApplication>

#define ZOOM_IN_ICON		"icon/Zoom In_16px.png"
#define ZOOM_OUT_ICON		"icon/Zoom Out_16px.png"
#define CIRCLE_ICON			"icon/Circle_16px.png"
#define ARC_ICON			"icon/Circled Notch_16px.png"
#define RECTANGLE_ICON		"icon/Rectangle_16px.png"
#define LINE_ICON			"icon/Line_16px.png"
#define CURSOR_ICON			"icon/Cursor_16px.png"

#define PRECISION			1.0f

enum Tool
{
	CURSOR = 0,
	LINE,
	RECTANGLE,
	ARC,
	CIRCLE,
	ZOOM_IN,
	ZOOM_OUT
};

class Image
{
public:
	QPixmap* Pixmap;
	QPoint Size;
	QPoint Position;
	QString ToolType = "line";
	QString Conversion = "threshold";
	float LineSpace = 1;
};

class DrawingWidget : public QLabel
{
	Q_OBJECT

public:
	DrawingWidget(QWidget *parent);
	~DrawingWidget();

	void InitGrid();
	void AddImage(int x, int y, int w, int h, QPixmap pix, float space, QString type, QString conversion);
    void AddLineToStack(QPoint p1, QPoint p2);
    void DrawLineFromStack();
	void AddRectangle(QRect rec);

	void ClearShape();
	void ClearImage();

    QVector<QVector<QPointF>> Vectors;

    QVector<Image> Images;

public slots:
	void SelectZoomInTool();
	void SelectZoomOutTool();
	void SelectLineTool();
	void SelectRectangleTool();
	void SelectCircleTool();
	void SelectArcTool();
	void SelectCursor();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

private:
    QPixmap topLayer;

	QVector<QLine> lines;

	QVector<QRect> rectangles;
	QVector<QVector3D> circles;
	QVector<QVector4D> arcs;
	Tool tool = CURSOR;
	void changeToolIconInArea(QString filePath);
};
