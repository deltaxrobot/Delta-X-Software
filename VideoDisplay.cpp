#include "VideoDisplay.h"

VideoDisplay::VideoDisplay(QObject *parent) : QObject(parent)
{
    Timer = new QTimer(NULL);
    Timer->connect(Timer, SIGNAL(timeout()), this, SLOT(TimerFunction()));
    Timer->start(10);
}

void VideoDisplay::Loop()
{
    return;
    while (!isCloseLoop)
    {
        continue;
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

void VideoDisplay::TimerFunction()
{
    try
    {
        if (!isCloseLoop)
        {
            if (updateSignal == false)
                return;

            for (int id = 0; id < MAX_DISPLAY; id++)
            {
                if (lbDisplay[id] != NULL)
                {
                    QImage img = ImageTool::cvMatToQImage(matDisplay[id]);
                    try
                    {
                        emit neededUpdatePixmapToLabel(lbDisplay[id], QPixmap::fromImage(img).scaledToHeight(lbDisplay[id]->size().height()));


                    }
                    catch (...)
                    {

                    }
                 }
            }

            updateSignal = false;
        }
        else
        {
            Timer->stop();
        }
    }
    catch (...)
    {

    }
}
