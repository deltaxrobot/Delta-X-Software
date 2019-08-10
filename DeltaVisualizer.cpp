#include "DeltaVisualizer.h"

static const char *vertexShaderSource =
	"#version 130\n"

	"uniform mat4 mvpMatrix;\n"

	"in vec4 vertex;\n"

	"void main(void)\n"
	"{\n"
		"gl_Position = mvpMatrix * vertex;\n"
	"}\n";

static const char *fragmentShaderSource =
	"#version 130\n"

	"uniform vec4 color;\n"

	"out vec4 fragColor;\n"

	"void main(void)\n"
	"{\n"
		"fragColor = color;\n"
	"}\n";

DeltaVisualizer::DeltaVisualizer(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	setFormat(format);
}

DeltaVisualizer::~DeltaVisualizer()
{
}

void DeltaVisualizer::MoveToHome()
{
	emit Moved(XHome, YHome, ZHome, WHome);
	emit FinishMoving();
}

QSize DeltaVisualizer::minimumSizeHint()
{
	return QSize(50, 50);
}

QSize DeltaVisualizer::sizeHint()
{
	return QSize(400, 400);
}

void DeltaVisualizer::ChangeXY(int x, int y)
{
	float h = qSqrt(ePara * ePara * (1.0f - 1.0f / 4));
	float scale = 2.0f / width();
	vertices.clear();
	float xA, yA, xB, yB, xC, yC;
	xA = x * scale;
	yA = (y + h * 2.0 / 3.0) * scale;
	xB = (x - ePara / 2) * scale;
	yB = (y - h * 1.0f / 3) * scale;
	xC = ( x + ePara / 2) * scale;
	yC = (y - h * 1.0f / 3) * scale;
	vertices << QVector3D(xA, yA, -0.01) << QVector3D(xB, yB, -0.01) << QVector3D(xC, yC, -0.01);
	
	update();

	X = x;
	Y = y;
}

void DeltaVisualizer::initializeGL()
{
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.9, 0.9, 0.9, 1);

	shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	shaderProgram.link();

	vertices << QVector3D(1, 0, -0.01) << QVector3D(0, 1, -0.01) << QVector3D(-1, 0, -0.01);

	ChangeXY(0, 0);
}
void DeltaVisualizer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	QMatrix4x4 mMatrix;
	QMatrix4x4 vMatrix;

	shaderProgram.bind();

	shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

	shaderProgram.setUniformValue("color", QColor(Qt::green));

	shaderProgram.setAttributeArray("vertex", vertices.constData());
	shaderProgram.enableAttributeArray("vertex");

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	shaderProgram.disableAttributeArray("vertex");

	shaderProgram.release();
}
void DeltaVisualizer::resizeGL(int width, int height)
{
	if (height == 0) {
		height = 1;
	}

	pMatrix.setToIdentity();
	pMatrix.perspective(0, (float)width / (float)height, 0.001, 1000);

	glViewport(0, 0, width, height);
}
void DeltaVisualizer::mousePressEvent(QMouseEvent *event)
{
	int x = event->pos().x() - width() / 2;
	int y = -event->pos().y() + height() / 2;

	ChangeXY(x, y);

	emit Moved(X, Y, Z, W);
}

void DeltaVisualizer::mouseReleaseEvent(QMouseEvent *event)
{
	emit FinishMoving();
}

void DeltaVisualizer::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) 
	{
		int x = event->pos().x() - width() / 2;
		int y = -event->pos().y() + height() / 2;

		ChangeXY(x, y);

		emit Moved(X, Y, Z, W);
	}
}

void DeltaVisualizer::wheelEvent(QWheelEvent *e)
{
	int n = 1;

	if (timer.isValid() == false)
	{
		timer.start();
	}
	else
	{
		n = 200 - timer.elapsed();

		if (n < 0)
		{
			n = 1;
		}

		n = log2(n) + 1;		
	}

	int delta = e->delta();
	
	Z -= (delta / abs(delta)) * n;

	if (Z > ZHome)
	{
		Z = ZHome;
	}

	if (timer.elapsed() < 30)
		return;

	timer.restart();

	emit Moved(X, Y, Z, W);
	emit FinishMoving();
}
