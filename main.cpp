#include "mainwindow.h"
#include "RobotDashboard.h"
#include "qdesktopwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::addLibraryPath("./");
#ifdef Q_OS_WIN
	SetProcessDPIAware(); // call before the main event loop
#endif // Q_OS_WIN 

#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
	QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#else
	qputenv("QT_DEVICE_PIXEL_RATIO", QByteArray("1"));
#endif // QT_VERSION

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	/*RobotDashboard *w = new RobotDashboard();
	w->show();*/

	/////////////////////////

	/*QRect screenGeometry = QApplication::desktop()->availableGeometry();
	w->resize(screenGeometry.width(), screenGeometry.height());
	w->showNormal();*/


    return a.exec();
}
