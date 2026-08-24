#include "RobotWindow.h"
#include "MainWindow.h"
#include <QApplication>
#include "AccountWindow.h"
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>
#include <QFile>
#include <QtDebug>
#include "sdk/DeltaXVersion.h"

#define NEW_WINDOW
#define JOY_STICK

using namespace std;
using namespace cv;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Open the log file
    QFile outFile("mylog.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Append))
        return;

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
    QCoreApplication::setApplicationVersion(
        QString::fromLatin1(DeltaXVersion::Application));

    QApplication a(argc, argv);
    QObject::connect(&a, &QGuiApplication::lastWindowClosed, []() {
        qDebug() << "QGuiApplication::lastWindowClosed emitted";
    });
    QObject::connect(&a, &QCoreApplication::aboutToQuit, []() {
        qDebug() << "QCoreApplication::aboutToQuit emitted";
    });
    QObject::connect(&a, &QGuiApplication::applicationStateChanged, [](Qt::ApplicationState state) {
        qDebug() << "Application state changed to" << state;
    });
#ifdef QT_DEBUG

#else
    qInstallMessageHandler(myMessageOutput);
#endif

    #ifdef NEW_WINDOW
        MainWindow w;

    #else
        RobotWindow w;
    #endif
//    w.show();
    qDebug() << "About to show main window";
    w.showMaximized();
    qDebug() << "Main window shown. Visible =" << w.isVisible();

    return a.exec();
}
