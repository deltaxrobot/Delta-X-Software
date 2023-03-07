#include "RobotWindow.h"
#include "MainWindow.h"
#include "qdesktopwidget.h"
#include <QApplication>
#include "AccountWindow.h"
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>
#include "testwindow.h"


#define NEW_WINDOW
#define JOY_STICK
//#define TEST

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

#ifdef TEST
    TestWindow w;

#else
    #ifdef NEW_WINDOW
        MainWindow w;

    #else
        RobotWindow w;
    #endif
#endif
//    w.show();
    w.showMaximized();

    return a.exec();
}
