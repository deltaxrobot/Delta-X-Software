#ifndef XCAMHIK_H
#define XCAMHIK_H

#include "xcam.h"
#include <MvCameraControl.h>

class XCamHIK : public XCam
{
public:
    XCamHIK();
    XCamHIK(void* cameraHandle);
    ~XCamHIK();

    bool Connect();
    bool Disconnect();
    bool IsOpen();
    unsigned char *Capture();

    void SetExposureTime(int value);
    int GetExposureTime();

    void* Camera;
    unsigned char* data = NULL;
};

#endif // XCAMHIK_H
