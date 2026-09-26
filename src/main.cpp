#include "RobotWindow.h"
#include "MainWindow.h"
#include <QApplication>
#include <QCursor>
#include "AccountWindow.h"
#include "SettingsManager.h"
#include "UiTheme.h"
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>
#include <QFile>
#include <QScreen>
#include <QtDebug>
#include "sdk/DeltaXVersion.h"

#define NEW_WINDOW
#define JOY_STICK

using namespace std;
using namespace cv;

namespace {

constexpr int kComfortableWindowMaxWidth = 1920;
constexpr int kWindowMargin = 24;

void showMainWindow(QWidget& window)
{
    // Maximizing across an ultrawide display stretches the workspaces far
    // beyond their useful reading distance. Keep normal displays maximized,
    // while presenting a centered, near-full-height window on wider screens.
    window.setMaximumWidth(kComfortableWindowMaxWidth);

    QScreen* screen = QGuiApplication::screenAt(QCursor::pos());
    if (!screen)
        screen = QGuiApplication::primaryScreen();

    if (!screen) {
        window.resize(1200, 700);
        window.show();
        return;
    }

    const QRect available = screen->availableGeometry();
    // Position the native window on the chosen screen before maximizing it.
    window.move(available.topLeft());
    if (available.width() <= kComfortableWindowMaxWidth) {
        window.showMaximized();
        return;
    }

    const int targetHeight = qMax(1, available.height() - (2 * kWindowMargin) - 40);
    const QRect targetGeometry(
        available.x() + ((available.width() - kComfortableWindowMaxWidth) / 2),
        available.y() + ((available.height() - targetHeight) / 2),
        kComfortableWindowMaxWidth,
        targetHeight);

    window.setGeometry(targetGeometry);
    window.show();
    // Center the decorated frame, not just the client area. This keeps the
    // title bar reachable when Windows adds its non-client margins.
    QRect frame = window.frameGeometry();
    frame.moveCenter(available.center());
    window.move(frame.topLeft());
}

} // namespace

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
    SettingsManager& settings = SettingsManager::instance();
    UiTheme::apply(a, settings.getGeneralSettings().theme);
    QObject::connect(&settings, &SettingsManager::settingsChanged,
                     &a, [&a, &settings](const QString& category, const QString&) {
        if (category == QStringLiteral("General"))
            UiTheme::apply(a, settings.getGeneralSettings().theme);
    });
    QObject::connect(&settings, &SettingsManager::settingsLoaded,
                     &a, [&a, &settings]() {
        UiTheme::apply(a, settings.getGeneralSettings().theme);
    });
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
    qDebug() << "About to show main window";
    showMainWindow(w);
    qDebug() << "Main window shown. Visible =" << w.isVisible();

    return a.exec();
}
