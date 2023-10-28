#ifndef XCAMBASLER_H
#define XCAMBASLER_H

#include "xcam.h"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigECamera.h>
#include <QDebug>

using namespace Pylon;

class XCamBasler : public XCam
{
public:
    XCamBasler();
    XCamBasler(CInstantCamera* cam);
    ~XCamBasler();

    bool Connect();
    bool Disconnect();
    bool IsOpen();
    unsigned char *Capture();

    void SetExposureTime(int value);
    int GetExposureTime();

    CInstantCamera* Camera = NULL;
    unsigned char* data = NULL;
};

#endif // XCAMBASLER_H
