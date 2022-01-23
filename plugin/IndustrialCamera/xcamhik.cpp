#include "xcamhik.h"

XCamHIK::XCamHIK()
{

}

XCamHIK::XCamHIK(void *cameraHandle)
{
    Camera = cameraHandle;
}

XCamHIK::~XCamHIK()
{
    MV_CC_StopGrabbing(Camera);
    MV_CC_CloseDevice(Camera);
}

bool XCamHIK::Connect()
{
    int nRet = -1;

    unsigned int nAccessMode = MV_ACCESS_Exclusive;
    unsigned short nSwitchoverKey = 0;
    nRet = MV_CC_OpenDevice(Camera, nAccessMode, nSwitchoverKey);

    if (nRet != 0)
    {
        return false;
    }

    nRet = MV_CC_StartGrabbing(Camera);

    return true;
}

bool XCamHIK::Disconnect()
{
    MV_CC_CloseDevice(Camera);
    return true;
}

bool XCamHIK::IsOpen()
{
    if (Camera == NULL)
        return false;

    return MV_CC_IsDeviceConnected(Camera);
}


unsigned char *XCamHIK::Capture()
{
    if (Camera == NULL)
        return NULL;

    if (data != NULL)
        free(data);

    int nBufSize = 3 * 1920 * 1200;
    data = (unsigned char*)std::malloc(sizeof(unsigned char) * (nBufSize));


    MV_FRAME_OUT_INFO_EX stInfo;
    memset(&stInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));

    int nRet = -1;
    nRet = MV_CC_GetImageForBGR(Camera, data, nBufSize, &stInfo, 1000);

    if (nRet != 0)
        return NULL;

    width = stInfo.nWidth;
    height = stInfo.nHeight;

    return data;
}

void XCamHIK::SetExposureTime(int value)
{

}

int XCamHIK::GetExposureTime()
{
    return 0;
}
