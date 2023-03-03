#include "testcode.h"

Camera::Camera(QObject *parent)
{

}

void Camera::run()
{
    int counter = 0;
    while(1)
    {
        qDebug() << counter;
        counter++;
        QThread::msleep(1000);
    }
}
