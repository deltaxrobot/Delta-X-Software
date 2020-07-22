#include "renderwidget.h"

RenderWidget::RenderWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setMouseTracking(true);
}

RenderWidget::~RenderWidget()
{
    mRenderer.cleanUp();
}

void RenderWidget::initializeGL()
{
    makeCurrent();

    mRenderer.setActiveScene(mScene);
    mRenderer.prepare();
}

void RenderWidget::paintGL()
{
    mRenderer.render();
}

void RenderWidget::resizeGL(int w, int h)
{
    mRenderer.resize(w,h);
}

Qt::MouseButton clickedButton = Qt::NoButton;
int clickX = -1;
int clickY = -1;

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    clickedButton = event->button();
    clickX = event->x();
    clickY = event->y();
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    clickedButton = Qt::NoButton;
    clickX = -1;
    clickY = -1;
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    float sensitivity = 0.6f;
    // left click
    if (clickedButton == Qt::LeftButton) {
        float xoffset = event->x() - clickX;
        clickX = event->x();

        xoffset *= sensitivity;

        mScene.mainModel.rotateHorizontally(xoffset);
        update();
    }
    // right click
    else if (clickedButton == Qt::RightButton) {
        float yoffset = clickY - event->y();
        float xoffset = event->x() - clickX;
        clickY = event->y();
        clickX = event->x();

        float speed = 0.01f;
        xoffset *= sensitivity * speed;
        yoffset *= sensitivity * speed;

        if (xoffset > 0) {
          mScene.mainCamera.move(RIGHTWARD, xoffset);
        } else if (xoffset < 0){
          mScene.mainCamera.move(LEFTWARD, -xoffset);
        }

        if (yoffset > 0) {
          mScene.mainCamera.move(UPWARD, yoffset);
        } else if (yoffset < 0){
          mScene.mainCamera.move(DOWNWARD, -yoffset);
        }
        update();
    }

    // middle click
    else if (clickedButton == Qt::MidButton) {
        float yoffset = clickY - event->y();
        clickY = event->y();

        yoffset *= sensitivity;

        mScene.mainModel.rotateVertically(yoffset);
        update();
    }


}

void RenderWidget::wheelEvent(QWheelEvent *event)
{
    float speed = event->delta() / 1000.0;
    if (speed >= 0) {
        mScene.mainCamera.move(FORWARD, speed);
    } else {
        mScene.mainCamera.move(BACKWARD, -speed);
    }

    update();
}
