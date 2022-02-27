#ifndef VIDEODISPLAY_H
#define VIDEODISPLAY_H

#include <QObject>
#include <ImageUnity.h>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <QTimer>

#define MAX_DISPLAY 5

class VideoDisplay : public QObject
{
    Q_OBJECT
public:
    explicit VideoDisplay(QObject *parent = nullptr);

    QTimer* Timer;


public slots:
    void Loop();
    void UpdateLabelImage(cv::Mat mat, QLabel* label, int id);
    void CloseLoop();
    void TimerFunction();
signals:
    void neededUpdatePixmapToLabel(QLabel*, QPixmap);
private:
    bool updateSignal = false;
    bool isCloseLoop = false;
    cv::Mat matDisplay[MAX_DISPLAY];
    QLabel* lbDisplay[MAX_DISPLAY] = {NULL};
};

#endif // VIDEODISPLAY_H