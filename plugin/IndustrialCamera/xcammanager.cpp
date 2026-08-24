#include "xcammanager.h"

XCamManager::XCamManager(QObject* parent)
    : QObject(parent)
{
    pylonRuntimeAvailable = loadRuntimeLibraries(
        { QStringLiteral("GCBase_MD_VC141_v3_1_Basler_pylon"),
          QStringLiteral("PylonBase_v9"),
          QStringLiteral("PylonUtility_v9") },
        pylonRuntimeLibraries, pylonRuntimeError);
    if (pylonRuntimeAvailable) {
        try {
            PylonInitialize();
            pylonInitialized = true;
        } catch (const GenericException& error) {
            pylonRuntimeAvailable = false;
            pylonRuntimeError = QString::fromLocal8Bit(error.what());
            qWarning() << "Pylon initialization failed:" << pylonRuntimeError;
        } catch (...) {
            pylonRuntimeAvailable = false;
            pylonRuntimeError = QStringLiteral("Unknown pylon initialization error");
            qWarning() << pylonRuntimeError;
        }
    }

    hikRuntimeAvailable = loadRuntimeLibraries(
        { QStringLiteral("MvCameraControl") },
        hikRuntimeLibraries, hikRuntimeError);

    qInfo() << RuntimeStatus();
}

XCamManager::~XCamManager()
{
    for (int i = 0; i < CameraList.count(); i++)
    {
        if (CameraList.at(i) != NULL)
            delete CameraList.at(i);
    }
    CameraList.clear();
    CurrentCamera = nullptr;
    if (pylonInitialized) {
        try {
            PylonTerminate();
        } catch (...) {
            qWarning() << "Pylon termination failed";
        }
    }
    unloadRuntimeLibraries(hikRuntimeLibraries);
    unloadRuntimeLibraries(pylonRuntimeLibraries);
}

QStringList XCamManager::FindCameraList()
{
    if (CurrentCamera && CurrentCamera->IsOpen())
        CurrentCamera->Disconnect();
    qDeleteAll(CameraList);
    CameraList.clear();
    CurrentCamera = nullptr;
    QStringList cameraList;

    if (pylonRuntimeAvailable && pylonInitialized)
        cameraList += FindBaslerCameraList();
    if (hikRuntimeAvailable)
        cameraList += FindHIKCameraList();

    return cameraList;
}

QStringList XCamManager::FindBaslerCameraList()
{
    QStringList baslerDeviceQStringList;

    if (!pylonRuntimeAvailable || !pylonInitialized)
        return baslerDeviceQStringList;

    DeviceInfoList_t baslerDeviceInfoList;
    try {
        CTlFactory::GetInstance().EnumerateDevices(baslerDeviceInfoList);
    } catch (const GenericException& error) {
        qWarning() << "Basler enumeration failed:" << error.what();
        return baslerDeviceQStringList;
    }
    for(size_t i = 0; i < baslerDeviceInfoList.size(); i++)
    {
        try
        {
            // Attempt to create a camera for this device.
            IPylonDevice* pDevice = CTlFactory::GetInstance().CreateDevice(baslerDeviceInfoList[i]);
            CInstantCamera* camera = new CInstantCamera(pDevice);

            // Add successfully created cameras to the list.
            const QString transport = camera->IsGigE()
                ? QStringLiteral("GigE Vision")
                : (camera->IsUsb() ? QStringLiteral("USB3 Vision")
                                   : QStringLiteral("Industrial"));
            baslerDeviceQStringList.append(
                QStringLiteral("[Basler][%1] %2")
                    .arg(transport,
                         QString::fromLocal8Bit(
                             baslerDeviceInfoList.at(i).GetModelName().c_str())));
            CameraList.append(new XCamBasler(camera));
        }
        catch (const GenericException& error)
        {
            qWarning() << "Cannot create Basler camera" << i << ":" << error.what();
            continue;
        }
    }

    return baslerDeviceQStringList;
}



QStringList XCamManager::FindHIKCameraList()
{
    QStringList HIKCameraDeviceQStringList;

    if (!hikRuntimeAvailable)
        return HIKCameraDeviceQStringList;

    int nRet = -1;

    // enumerate all devices corresponding to the specified transport protocol in the subnet
    unsigned int nTLayerType = MV_GIGE_DEVICE | MV_USB_DEVICE;
    MV_CC_DEVICE_INFO_LIST m_stDevList = { 0 };
    nRet = MV_CC_EnumDevices(nTLayerType, &m_stDevList);
    if (nRet != MV_OK) {
        qWarning() << "Hikrobot enumeration failed with code" << nRet;
        return HIKCameraDeviceQStringList;
    }

    for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO m_stDevInfo = { 0 };

        memcpy(&m_stDevInfo, m_stDevList.pDeviceInfo[i], sizeof(MV_CC_DEVICE_INFO));

        QString cameraIDString;
        QString transport;
        if (m_stDevInfo.nTLayerType == MV_GIGE_DEVICE) {
            transport = QStringLiteral("GigE Vision");
            cameraIDString = getStringFromUnsignedChar(m_stDevInfo.SpecialInfo.stGigEInfo.chModelName);
        } else {
            transport = QStringLiteral("USB3 Vision");
            cameraIDString = getStringFromUnsignedChar(m_stDevInfo.SpecialInfo.stUsb3VInfo.chModelName);
        }

        HIKCameraDeviceQStringList.append(
            QStringLiteral("[Hikrobot][%1] %2").arg(transport, cameraIDString));

        void * cameraHandle = NULL;
        if (MV_CC_CreateHandle(&cameraHandle, &m_stDevInfo) == 0 && cameraHandle) {
            CameraList.append(new XCamHIK(cameraHandle));
        } else {
            HIKCameraDeviceQStringList.removeLast();
        }
    }

    return HIKCameraDeviceQStringList;
}

int XCamManager::Height()
{
    return CurrentCamera ? CurrentCamera->height : 0;
}

int XCamManager::Width()
{
    return CurrentCamera ? CurrentCamera->width : 0;
}

bool XCamManager::ConnectCamera(int id)
{
    if (id < 0 || id >= CameraList.length())
        return false;

    if (CurrentCamera && CurrentCamera != CameraList.at(id) && CurrentCamera->IsOpen())
        CurrentCamera->Disconnect();

    CurrentCamera = CameraList.at(id);
    return CurrentCamera->Connect();
}

bool XCamManager::DisconnectCamera()
{
    if (!CurrentCamera)
        return false;
    CurrentCamera->Disconnect();
    CurrentCamera = nullptr;
    return true;
}

void XCamManager::SelectCamera(int id)
{
    CurrentCamera = (id >= 0 && id < CameraList.size()) ? CameraList.at(id) : nullptr;
}

bool XCamManager::IsCameraOpen(int id)
{
    return id >= 0 && id < CameraList.size() && CameraList.at(id) && CameraList.at(id)->IsOpen();
}

bool XCamManager::IsOpen()
{
    if (CameraList.empty())
        return false;

    for(int i = 0; i < CameraList.count(); i++)
    {
        if (IsCameraOpen(i))
            return true;
    }

    return false;;
}

void XCamManager::SetExposureTime(int value)
{
    if (CurrentCamera)
        CurrentCamera->SetExposureTime(value);
}

int XCamManager::GetExposureTime()
{
    return CurrentCamera ? CurrentCamera->GetExposureTime() : 0;
}

unsigned char *XCamManager::Capture()
{
    if (CurrentCamera == NULL)
        return NULL;

    return CurrentCamera->Capture();
}

QString XCamManager::getStringFromUnsignedChar(unsigned char *str)
{
    QString qString;

    for (int i = 0; i < 64; i++)
    {
        if (str[i] == '\0')
            break;

        qString += QChar::fromLatin1(static_cast<char>(str[i]));
    }

    return qString;
}

bool XCamManager::HasAnyBackend() const
{
    return IsBaslerBackendAvailable() || IsHikBackendAvailable();
}

bool XCamManager::IsBaslerBackendAvailable() const
{
    return pylonRuntimeAvailable && pylonInitialized;
}

bool XCamManager::IsHikBackendAvailable() const
{
    return hikRuntimeAvailable;
}

QString XCamManager::RuntimeStatus() const
{
    const QString basler = IsBaslerBackendAvailable()
        ? QStringLiteral("Basler GigE/USB3: ready")
        : QStringLiteral("Basler GigE/USB3: unavailable (%1)")
              .arg(pylonRuntimeError.isEmpty()
                       ? QStringLiteral("pylon runtime is not installed")
                       : pylonRuntimeError);
    const QString hik = IsHikBackendAvailable()
        ? QStringLiteral("Hikrobot GigE/USB3: ready")
        : QStringLiteral("Hikrobot GigE/USB3: unavailable (%1)")
              .arg(hikRuntimeError.isEmpty()
                       ? QStringLiteral("MVS runtime is not installed")
                       : hikRuntimeError);
    return basler + QStringLiteral("\n") + hik;
}

bool XCamManager::loadRuntimeLibraries(const QStringList& libraryNames,
                                       QList<QLibrary*>& loadedLibraries,
                                       QString& errorMessage)
{
    for (const QString& libraryName : libraryNames) {
        auto* library = new QLibrary(libraryName, this);
        library->setLoadHints(QLibrary::ResolveAllSymbolsHint |
                              QLibrary::PreventUnloadHint);
        if (!library->load()) {
            errorMessage = QStringLiteral("%1: %2")
                               .arg(libraryName, library->errorString());
            delete library;
            unloadRuntimeLibraries(loadedLibraries);
            return false;
        }
        loadedLibraries.append(library);
    }
    errorMessage.clear();
    return true;
}

void XCamManager::unloadRuntimeLibraries(QList<QLibrary*>& libraries)
{
    // PreventUnloadHint deliberately keeps successfully loaded SDK modules in
    // the process until shutdown. Deleting QLibrary wrappers is still safe and
    // avoids QObject ownership accumulating after camera windows are closed.
    qDeleteAll(libraries);
    libraries.clear();
}
