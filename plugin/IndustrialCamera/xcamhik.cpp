#include "xcamhik.h"
#include <QDebug>
#include <cstdint>
#include <limits>

XCamHIK::XCamHIK()
{

}

XCamHIK::XCamHIK(void *cameraHandle)
{
    Camera = cameraHandle;
}

XCamHIK::~XCamHIK()
{
    if (Camera) {
        if (open) {
            MV_CC_StopGrabbing(Camera);
            MV_CC_CloseDevice(Camera);
        }
        MV_CC_DestroyHandle(Camera);
        Camera = NULL;
        open = false;
    }
    if (data)
        std::free(data);
}

bool XCamHIK::Connect()
{
    if (!Camera)
        return false;
    int nRet = -1;

    unsigned int nAccessMode = MV_ACCESS_Exclusive;
    unsigned short nSwitchoverKey = 0;
    nRet = MV_CC_OpenDevice(Camera, nAccessMode, nSwitchoverKey);

    if (nRet != 0)
    {
        qWarning() << "Hikrobot open failed with code" << nRet;
        return false;
    }

    // GigE cameras benefit from the largest packet size supported by the NIC.
    // USB3 Vision devices return an unsupported value and simply skip this.
    const int optimalPacketSize = MV_CC_GetOptimalPacketSize(Camera);
    if (optimalPacketSize > 0)
        MV_CC_SetIntValueEx(Camera, "GevSCPSPacketSize",
                           static_cast<unsigned int>(optimalPacketSize));

    // Continuous/free-run acquisition is the predictable default for the
    // request/response capture path used by Delta X Software.
    MV_CC_SetEnumValue(Camera, "TriggerMode", 0);

    nRet = MV_CC_StartGrabbing(Camera);
    if (nRet != 0) {
        qWarning() << "Hikrobot start grabbing failed with code" << nRet;
        MV_CC_CloseDevice(Camera);
        return false;
    }
    open = true;
    return true;
}

bool XCamHIK::Disconnect()
{
    if (!Camera)
        return false;
    if (open) {
        MV_CC_StopGrabbing(Camera);
        MV_CC_CloseDevice(Camera);
    }
    open = false;
    return true;
}

bool XCamHIK::IsOpen()
{
    if (Camera == NULL)
        return false;

    return open && MV_CC_IsDeviceConnected(Camera);
}


unsigned char *XCamHIK::Capture()
{
    if (Camera == NULL || !open)
        return NULL;

    MVCC_INTVALUE_EX frameWidth = { 0 };
    MVCC_INTVALUE_EX frameHeight = { 0 };
    if (MV_CC_GetIntValueEx(Camera, "Width", &frameWidth) != 0 ||
        MV_CC_GetIntValueEx(Camera, "Height", &frameHeight) != 0 ||
        frameWidth.nCurValue == 0 || frameHeight.nCurValue == 0)
        return NULL;
    // MV_CC_GetImageForBGR writes three bytes per pixel even when the camera's
    // raw PayloadSize is Mono8/Bayer and therefore much smaller.
    const std::uint64_t bgrByteCount = static_cast<std::uint64_t>(frameWidth.nCurValue) *
                                       static_cast<std::uint64_t>(frameHeight.nCurValue) * 3ULL;
    if (bgrByteCount == 0 || bgrByteCount > 512ULL * 1024ULL * 1024ULL ||
        bgrByteCount > std::numeric_limits<unsigned int>::max())
        return NULL;
    if (data != NULL)
        free(data);
    const unsigned int nBufSize = static_cast<unsigned int>(bgrByteCount);
    data = (unsigned char*)std::malloc(nBufSize);
    if (!data)
        return NULL;


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
    if (Camera && value > 0) {
        MV_CC_SetEnumValue(Camera, "ExposureAuto", 0);
        MV_CC_SetFloatValue(Camera, "ExposureTime", static_cast<float>(value));
    }
}

int XCamHIK::GetExposureTime()
{
    if (!Camera)
        return 0;
    MVCC_FLOATVALUE exposure = { 0 };
    return MV_CC_GetFloatValue(Camera, "ExposureTime", &exposure) == 0
        ? static_cast<int>(exposure.fCurValue) : 0;
}
