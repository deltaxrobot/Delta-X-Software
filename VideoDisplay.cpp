#include "VideoDisplay.h"

VideoDisplay::VideoDisplay(QObject *parent) : QObject(parent)
{

}

void VideoDisplay::Loop()
{
    while (!isCloseLoop)
    {
        if (updateSignal == false)
            continue;

        for (int id = 0; id < MAX_DISPLAY; id++)
        {
            if (lbDisplay[id] != NULL)
            {
                QImage img = ImageTool::cvMatToQImage(matDisplay[id]);
                lbDisplay[id]->setPixmap(QPixmap::fromImage(img).scaledToHeight(lbDisplay[id]->size().height()));
            }
        }

        updateSignal = false;
    }
}

void VideoDisplay::UpdateLabelImage(cv::Mat mat, QLabel *label, int id)
{
    matDisplay[id] = mat;
    lbDisplay[id] = label;
    updateSignal = true;
}

void VideoDisplay::CloseLoop()
{
    isCloseLoop = true;
}
