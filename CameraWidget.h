#pragma once

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <qmath.h>
#include <qpushbutton.h>
#include <QSettings>
#include <QToolButton>

class CameraWidget : public QLabel
{
	Q_OBJECT

public:
	explicit CameraWidget(QWidget *parent = 0);
	void InitParameter();

	void ChangeSize(int w, int h);
	
	bool mousePressed;
	bool drawStarted;
	int selectedTool;
	int lastSelectedTool;

	bool IsPerspectiveEnable = false;
	bool IsMeasureDisplayEnable = true;

	QPixmap lastCursorIcon;

    QLine mLine;
    QRect mRect;
    QPoint mPoint;
    QPoint transformPoints[4];
    QRect PselectedRectangle;

	~CameraWidget();

signals:
	void FinishDrawObject(int x, int y, int h, int w);
	void FinishSelectPerspectivePoints(QPoint a, QPoint b, QPoint c, QPoint d);
	void FinishSelectProcessRectangle(QRect rect);
	void FinishSelectCalibLine(QPoint a, QPoint b);
	void FinishMeasureSpace(int distance);
	void FinishSelectCalibPoint(int x, int y);
	void SizeChanged();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

public slots:
	void rectObject();
	void lineObject();
	void circleObject();
	void selectPerspectiveRectangle();
	void selectProcessRectangle();
	void noTool();
    void SaveSetting(QString fileName);
    void LoadSetting(QString fileName);

    void ChangeCalibPoint();
    void ChangeCalibLine();
private:
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
};
