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
#include <QWheelEvent>

#define MOVING_BASE_SIZE 50

class DeltaVisualizer : public QLabel
{
	Q_OBJECT

public:
	DeltaVisualizer(QWidget *parent = 0);
	~DeltaVisualizer();
	void InitGrid();
	void MoveToHome();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
	void SetDivisionComboBox(QComboBox* division);
    void JumpOneStep(float* axis, float step);

	float XHome = 0;
	float YHome = 0;
	float ZHome = -200;
	float WHome = 0;
    float UHome = 0;
    float VHome = 0;
	float FDefault = 200;
	float ADefault = 1200;
    float SDefault = 12;
    float EDefault = 12;

	float X = XHome;
	float Y = YHome;
	float Z = ZHome;
	float W = WHome;
    float U = UHome;
    float V = VHome;
	float F = FDefault;
	float A = ADefault;
    float S = SDefault;
    float E = EDefault;

public slots:
    void ChangeXY(float x, float y);
	void MoveUp();
	void MoveDown();
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

    void SubW();
    void SubU();
    void SubV();
    void PlusW();
    void PlusU();
    void PlusV();

    void ChangeWorkingSize(int option);
signals:
    void Moved(float x, float y, float z, float w, float u, float v);
    void CursorMoved(float x, float y);
	void FinishMoving();

	void up_arrow();
	void down_arrow();
	void left_arrow();
	void right_arrow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;
    bool eventFilter(QObject *dist, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setWorkingSize(int width);

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
