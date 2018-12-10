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

class DeltaVisualizer : public QOpenGLWidget, QOpenGLFunctions
{
	Q_OBJECT

public:
	DeltaVisualizer(QWidget *parent = 0);
	~DeltaVisualizer();

	QSize minimumSizeHint();
	QSize sizeHint();	

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
signals:
	void Moved(float x, float y, float z);
	void FinishMoving();

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	QMatrix4x4 pMatrix;
	QOpenGLShaderProgram shaderProgram;
	QVector<QVector3D> vertices;

	float fPara;
	float rfPara;
	float rePara;
	float ePara = 50;
	float bPara;
};

#endif // DELTAVISUALIZER_H
