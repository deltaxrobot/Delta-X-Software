#ifndef DELTAVISUALIZER_H
#define DELTAVISUALIZER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <qopengl.h>
#include <qopenglshaderprogram.h>
#include <qslider.h>
#include <qmath.h>
#include <qevent.h>
#include <QElapsedTimer>
#include <qcombobox.h>

class DeltaVisualizer : public QOpenGLWidget, QOpenGLFunctions
{
	Q_OBJECT

public:
	DeltaVisualizer(QWidget *parent = 0);
	~DeltaVisualizer();
	void MoveToHome();

	QSize minimumSizeHint();
	QSize sizeHint();	
	void SetDivisionComboBox(QComboBox* division);

	float XHome = 0;
	float YHome = 0;
	float ZHome = -290;
	float WHome = 0;

	float X = XHome;
	float Y = YHome;
	float Z = ZHome;
	float W = WHome;

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
	void FinishMoving();

	void up_arrow();
	void down_arrow();
	void left_arrow();
	void right_arrow();

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;
	bool eventFilter(QObject *dist, QEvent *event) Q_DECL_OVERRIDE;

private:
	QMatrix4x4 pMatrix;
	QOpenGLShaderProgram shaderProgram;
	QVector<QVector3D> vertices;

	QElapsedTimer timer;

	QComboBox* cbDivision;

	float fPara;
	float rfPara;
	float rePara;
	float ePara = 50;
	float bPara;
};

#endif // DELTAVISUALIZER_H
