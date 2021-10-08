#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QIcon>
#include <QPushButton>
#include <QMouseEvent>

class CameraWidget : public QLabel
{
    Q_OBJECT
public:
    CameraWidget(QWidget *parent = 0);
    void SelectTool(int id);
    void ChangeToolIconInArea(QIcon icon);

    int CurrentTool = NO_TOOL;

    enum
    {
        NO_TOOL = 0,
        CALIB_POINT_TOOL,
        LINE_TOOL,
        POINT_TOOL
    };

public slots:
    void slot_function();

        signals:
    void MousePositionChanged(int x, int y);
    void CalibPointSelected(int x, int y);
    void MappingPointSelected(int x, int y);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QPoint lastCursorPosition;

    void drawPoint(int x, int y);

};

#endif // CAMERAWIDGET_H
