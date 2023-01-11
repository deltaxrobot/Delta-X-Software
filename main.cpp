#include "RobotWindow.h"
#include "MainWindow.h"
#include "qdesktopwidget.h"
#include <QApplication>
#include "AccountWindow.h"
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>


#define NEW_WINDOW
#define JOY_STICK

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    QApplication a(argc, argv);

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef NEW_WINDOW
    MainWindow w;
#else
    RobotWindow w;
#endif
    w.show();

    return a.exec();//
}
