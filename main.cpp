#include "RobotWindow.h"
#include "MainWindow.h"
#include <QApplication>
#include "AccountWindow.h"
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>
#include "testwindow.h"
#include <QFile>
#include <QtDebug>

#define NEW_WINDOW
#define JOY_STICK
// #define TEST

using namespace std;
using namespace cv;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Open the log file
    QFile outFile("mylog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    // Write the message to the log file
    QTextStream ts(&outFile);
    switch (type) {
    case QtDebugMsg:
        ts << "Debug: " << msg << Qt::endl;
        break;
    case QtWarningMsg:
        ts << "Warning: " << msg << Qt::endl;
        break;
    case QtCriticalMsg:
        ts << "Critical: " << msg << Qt::endl;
        break;
    case QtFatalMsg:
        ts << "Fatal: " << msg << Qt::endl;
        abort();
    }

    // Close the log file
    outFile.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    // QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

    QCoreApplication::setOrganizationName(QStringLiteral("DeltaXRobotics"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("deltaxrobotics.com"));
    QCoreApplication::setApplicationName(QStringLiteral("DeltaRobotSoftware"));

    QApplication a(argc, argv);
#ifdef QT_DEBUG

#else
    qInstallMessageHandler(myMessageOutput);
#endif

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
