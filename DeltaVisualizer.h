#ifndef DELTAVISUALIZER_H
#define DELTAVISUALIZER_H

#include <qslider.h>
#include <qmath.h>
#include <qevent.h>
#include <QElapsedTimer>
#include <qcombobox.h>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>

#define MOVING_BASE_SIZE 50

class DeltaVisualizer : public QLabel
{
	Q_OBJECT

public:
	DeltaVisualizer(QWidget *parent = 0);
	~DeltaVisualizer();
	void InitGrid();
	void MoveToHome();

	QSize minimumSizeHint();
	QSize sizeHint();	
	void SetDivisionComboBox(QComboBox* division);

	float XHome = 0;
	float YHome = 0;
	float ZHome = -200;
	float WHome = 0;
	float FDefault = 200;
	float ADefault = 1200;

	float X = XHome;
	float Y = YHome;
	float Z = ZHome;
	float W = WHome;
	float F = FDefault;
	float A = ADefault;

public slots:
	void ChangeXY(int x, int y);
	void MoveUp();
	void MoveDown();
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
signals:
	void Moved(float x, float y, float z, float w);
	void CursorMoved(int x, int y);
	void FinishMoving();

	void up_arrow();
	void down_arrow();
	void left_arrow();
	void right_arrow();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *e);
	bool eventFilter(QObject *dist, QEvent *event);

private:
	QElapsedTimer timer;

	QComboBox* cbDivision;

    QLabel* lbParent;

	float fPara;
	float rfPara;
	float rePara;
	float ePara = 50;
	float bPara;
};

#endif // DELTAVISUALIZER_H
