#ifndef XCAMMANAGER_H
#define XCAMMANAGER_H

#include <QObject>
#include <QWidget>
#include <QStringList>

#include <iostream>
#include <string>

#include <QList>
#include <QLibrary>
#include "xcam.h"
#include "xcambasler.h"
#include "xcamhik.h"

using namespace Pylon;

class XCamManager : public QObject
{
    Q_OBJECT
public:
    explicit XCamManager(QObject* parent = nullptr);
    ~XCamManager();

    QStringList FindCameraList();
    QStringList FindBaslerCameraList();
    QStringList FindHIKCameraList();

    bool HasAnyBackend() const;
    bool IsBaslerBackendAvailable() const;
    bool IsHikBackendAvailable() const;
    QString RuntimeStatus() const;

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
    XCam* CurrentCamera = NULL;

private:
    QString getStringFromUnsignedChar(unsigned char *str);
    bool loadRuntimeLibraries(const QStringList& libraryNames,
                              QList<QLibrary*>& loadedLibraries,
                              QString& errorMessage);
    void unloadRuntimeLibraries(QList<QLibrary*>& libraries);

    bool pylonInitialized = false;
    bool pylonRuntimeAvailable = false;
    bool hikRuntimeAvailable = false;
    QString pylonRuntimeError;
    QString hikRuntimeError;
    QList<QLibrary*> pylonRuntimeLibraries;
    QList<QLibrary*> hikRuntimeLibraries;
};

#endif // XCAMMANAGER_H
