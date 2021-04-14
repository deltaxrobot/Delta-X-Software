#include "ProjectWindow.h"
#include "MainWindow.h"
#include "qdesktopwidget.h"
#include <QApplication>
#include "AccountWindow.h"

#define NEW_WINDOW

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
	QApplication a(argc, argv);
#ifdef NEW_WINDOW
    MainWindow w;
#else
    ProjectWindow w;
#endif
	w.show();		

	return a.exec();
}
