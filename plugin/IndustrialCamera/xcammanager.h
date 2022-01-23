#ifndef XCAMMANAGER_H
#define XCAMMANAGER_H

#include <QObject>
#include <QWidget>
#include <QStringList>

#include <iostream>
#include <string>

#include <QList>
#include "xcam.h"
#include "xcambasler.h"
#include "xcamhik.h"

using namespace Pylon;

class XCamManager : public QObject
{
    Q_OBJECT
public:
    XCamManager();
    ~XCamManager();

    QStringList FindCameraList();
    QStringList FindBaslerCameraList();
    QStringList FindHIKCameraList();

    int Height();
    int Width();

    bool ConnectCamera(int id);
    bool DisconnectCamera();
    void SelectCamera(int id);
    bool IsCameraOpen(int id);
    bool IsOpen();

    void SetExposureTime(int value);
    int GetExposureTime();

    unsigned char *Capture();

    QList<XCam*> CameraList;
    XCam* CurrentCamera;

private:
    QString getStringFromUnsignedChar(unsigned char *str);
};

#endif // XCAMMANAGER_H
