#include "DeviceSimulatorWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("DeltaXVirtualDeviceSimulator");
    app.setOrganizationName("DeltaX");

    DeviceSimulatorWindow window;
    window.show();

    return app.exec();
}
