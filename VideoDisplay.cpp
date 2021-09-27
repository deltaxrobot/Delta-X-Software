#include "VideoDisplay.h"

VideoDisplay::VideoDisplay(QObject *parent) : QObject(parent)
{

}

void VideoDisplay::Loop()
{
    while (true)
    {
        if (updateSignal == false)
            continue;

        QImage img = ImageTool::cvMatToQImage(matDisplay);
        lbDisplay->setPixmap(QPixmap::fromImage(img).scaledToHeight(lbDisplay->size().height()));

        updateSignal = false;
    }
}

void VideoDisplay::UpdateLabelImage(cv::Mat mat, QLabel *label)
{
    matDisplay = mat;
    lbDisplay = label;
    updateSignal = true;
}

void VideoDisplay::UpdateLabelImage2(QLabel *label)
{
    int i = 0;
    i += 1;
}
