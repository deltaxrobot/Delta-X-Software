#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#define GLEW_STATIC
//#include <GL/glew.h>

#include "rengine/renderer.h"

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Ui {
class RenderWidget;
}

class RenderWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = 0);
    ~RenderWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);


    Renderer mRenderer = Renderer::getInstance();
    Scene mScene;

private:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

};

#endif // RENDERWIDGET_H
