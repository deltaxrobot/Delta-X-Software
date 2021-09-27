#ifndef VIDEODISPLAY_H
#define VIDEODISPLAY_H

#include <QObject>
#include <ImageUnity.h>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class VideoDisplay : public QObject
{
    Q_OBJECT
public:
    explicit VideoDisplay(QObject *parent = nullptr);

public slots:
    void Loop();
    void UpdateLabelImage(cv::Mat mat, QLabel* label);
    void UpdateLabelImage2(QLabel* label);
signals:
private:
    bool updateSignal = false;
    cv::Mat matDisplay;
    QLabel* lbDisplay;
};

#endif // VIDEODISPLAY_H
