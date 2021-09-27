#pragma once

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <qmath.h>
#include <qpushbutton.h>
#include <QSettings>
#include <QToolButton>
#include <QVector>
#include <QCoreApplication>
#include <QLineEdit>

class CameraWidget : public QLabel
{
	Q_OBJECT

public:
	explicit CameraWidget(QWidget *parent = 0);
	void InitParameter();

    void ChangeSize(int w, int h);

    enum CameraTool
    {
        NO_TOOL = 0,
        OBJECT_TOOL,
        LINE_TOOL,
        POINT_TOOL,
        QUADRANGLE_TOOL,
        AREA_TOOL,
        MAPPING_TOOL
    };

    bool IsQuadrangleEnable = false;
    bool IsCalibVisible = true;


	~CameraWidget();

signals:
    void ObjectChanged(int x, int y, int h, int w);
    void QuadrangleChanged(QPoint a, QPoint b, QPoint c, QPoint d);
    void AreaChanged(QRect rect);
    void LineChanged(QPoint a, QPoint b);
    void DistanceChanged(int distance);
    //void PointChanged(int x, int y);
    void PointChanged(QPoint p1, QPoint p2);
	void SizeChanged();
    void RequestUpdate();
    void UpdateLineFromPoint(int realLine, int imageLine);
    void MappingPointChanged(QPoint mappingPoint);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

public slots:
    void SelectObjectTool();
    void SelectLineTool();
    void SelectPointTool();
    void SelectQuadrangleTool();
    void SelectAreaTool();
    void SelectMappingTool();
    void SelectNoTool();
    void SaveSetting(QString fileName);
    void LoadSetting(QString fileName);

    //void ChangePoint();
    void ChangeLine();
    void ChangeQuadrangle(QPoint p1, QPoint p2, QPoint p3, QPoint p4);
    void ChangeQuadrangle(QVector<QPointF> quads);
    void ChangeXDirection(float angle);
    void ChangeRealLineValue(float value);
    void ChangeImageLineValue(float value);
    void ChangeImagePointValue(QPoint value);
    void ChangeImagePoint2Value(QPoint value);
    void ChangeRealPointValue(QPoint value);
    void ChangeRealPoint2Value(QPoint value);
    void ChangeRealMappingValue(QPointF value);
private:
    QPixmap lastCursorIcon;

    QLineF mLine;
    QRect mRect;
    QPoint mPoint;
    QPoint mPoint2;
    QPoint mQuadrangle[4];
    QRect mArea;
    QPoint mMappingPoint;

    float xAxisAngle = 0;
    float xAxisScale = 1;
    QPoint xAxisPosition = QPoint(20, 20);

    float realLineValue;
    QPoint realPointValue;
    QPoint realPoint2Value;

    QPointF realMappingValue;

    bool mousePressed;
    bool drawStarted;
    int selectedTool;
    int selectedPoint = 0;
    int lastSelectedTool;

	QLine xAxis;
	QLine arrow1;
	QLine arrow2;
	QPainter painter;
	QPainter painter2;
	QPixmap overPix;
	QPixmap mPix;

	int transPointOrder = -1;
	int processPointOrder = -1;

	int calibLineRealLength = 100;
	int xCalibPoint = 150;
	int yCalibPoint = 0;

	QPoint curPosInWidget;

	QPixmap mergePixmap(QPixmap p1, QPixmap p2);

	void changeToolIconInArea(QIcon icon);
    void drawQuadrangle(QPainter* painter);
    void drawArea(QPainter* painter);
    void drawLine(QPainter* painter);
    void drawPoint(QPainter* painter);
    void drawMappingPoint(QPainter* painter);
    void drawStrokeLine(QPainter* painter, QLineF line);
    void drawStrokeRect(QPainter* painter, QRect rect);
    void drawStrokeText(QPainter* painter, QString text, QPoint pos);
    void drawSolidColor(QPainter* painter, QRect rect, float alpha);
    void drawAxisSymbol(QPainter* painter);
};
