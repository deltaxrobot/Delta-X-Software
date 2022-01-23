#include "xcammanager.h"

XCamManager::XCamManager()
{

}

XCamManager::~XCamManager()
{
    for (int i = 0; i < CameraList.count(); i++)
    {
        if (CameraList.at(i) != NULL)
            delete CameraList.at(i);
    }
}

QStringList XCamManager::FindCameraList()
{
    QStringList cameraList;

    cameraList += FindBaslerCameraList();
    cameraList += FindHIKCameraList();

    return cameraList;
}

QStringList XCamManager::FindBaslerCameraList()
{
    QStringList baslerDeviceQStringList;

    PylonInitialize();

    DeviceInfoList_t baslerDeviceInfoList;
    CTlFactory::GetInstance().EnumerateDevices(baslerDeviceInfoList);
    for(size_t i = 0; i < baslerDeviceInfoList.size(); i++)
    {
        baslerDeviceQStringList.append(baslerDeviceInfoList.at(i).GetModelName().c_str());

        CInstantCamera* camera = new CInstantCamera(CTlFactory::GetInstance().CreateDevice(baslerDeviceInfoList.at(i)));

        CameraList.append(new XCamBasler(camera));
    }

    return baslerDeviceQStringList;
}

QStringList XCamManager::FindHIKCameraList()
{
    QStringList HIKCameraDeviceQStringList;

    int nRet = -1;

    // enumerate all devices corresponding to the specified transport protocol in the subnet
    unsigned int nTLayerType = MV_GIGE_DEVICE;
    //unsigned int nTLayerType = MV_USB_DEVICE;
    MV_CC_DEVICE_INFO_LIST m_stDevList = { 0 };
    nRet = MV_CC_EnumDevices(nTLayerType, &m_stDevList);

    for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO m_stDevInfo = { 0 };

        memcpy(&m_stDevInfo, m_stDevList.pDeviceInfo[i], sizeof(MV_CC_DEVICE_INFO));

        QString cameraIDString;
        cameraIDString =  getStringFromUnsignedChar(m_stDevInfo.SpecialInfo.stGigEInfo.chModelName);

        HIKCameraDeviceQStringList.append(cameraIDString);

        void * cameraHandle = NULL;
        MV_CC_CreateHandle(&cameraHandle, &m_stDevInfo);

        CameraList.append(new XCamHIK(cameraHandle));
    }

    return HIKCameraDeviceQStringList;
}

int XCamManager::Height()
{
    return CurrentCamera->height;
}

int XCamManager::Width()
{
    return CurrentCamera->width;
}

bool XCamManager::ConnectCamera(int id)
{
    if (id > CameraList.length())
        return false;

    CurrentCamera = CameraList.at(id);
    return CurrentCamera->Connect();
}

bool XCamManager::DisconnectCamera()
{
    CurrentCamera->Disconnect();
    return true;
}

void XCamManager::SelectCamera(int id)
{
    CurrentCamera = CameraList.at(id);
}

bool XCamManager::IsCameraOpen(int id)
{
    return CameraList.at(id)->IsOpen();
}

bool XCamManager::IsOpen()
{
    if (CameraList.empty())
        false;

    for(int i = 0; i < CameraList.count(); i++)
    {
        if (IsCameraOpen(i))
            return true;
    }

    return false;;
}

void XCamManager::SetExposureTime(int value)
{
    CurrentCamera->SetExposureTime(value);
}

int XCamManager::GetExposureTime()
{
    return CurrentCamera->GetExposureTime();
}

unsigned char *XCamManager::Capture()
{
    return CurrentCamera->Capture();
}

QString XCamManager::getStringFromUnsignedChar(unsigned char *str)
{
    QString qString;

    for (int i = 0; i < 64; i++)
    {
        if (str[i] == '\0')
            break;

        qString += str[i];
    }

    return qString;
}
