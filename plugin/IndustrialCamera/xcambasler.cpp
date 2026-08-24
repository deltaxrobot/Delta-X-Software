#include "xcambasler.h"

XCamBasler::XCamBasler()
{

}

XCamBasler::XCamBasler(CInstantCamera *cam)
{
    Camera = cam;
}

XCamBasler::~XCamBasler()
{
    if (Camera != NULL)
    {
        try {
            if (Camera->IsGrabbing())
                Camera->StopGrabbing();
            if (Camera->IsOpen())
                Camera->Close();
        } catch (const GenericException& error) {
            qWarning() << "Basler shutdown failed:" << error.what();
        } catch (...) {
            qWarning() << "Basler shutdown failed with an unknown error";
        }
        delete Camera;
        Camera = NULL;
    }
    if (data)
        std::free(data);
}

bool XCamBasler::Connect()
{
    if (Camera == NULL)
        return false;
    try {
        Camera->Open();
        Camera->MaxNumBuffer = 5;

    GenApi::INodeMap& nodemap = Camera->GetNodeMap();
    GenApi::CIntegerPtr w = nodemap.GetNode("Width");
    GenApi::CIntegerPtr h = nodemap.GetNode("Height");

    width = (int)w->GetValue();
    height = (int)h->GetValue();

    GenApi::CFloatPtr exposureTimeNode = nodemap.GetNode("ExposureTime");
    if (IsReadable(exposureTimeNode))
    {
        double exposureTimeValue = exposureTimeNode->GetValue();
        qDebug() << "Exposure Time:" << exposureTimeValue << "us";
    }
    else
    {
        qDebug() << "Exposure Time is not readable.";
    }

    // Read the gain parameter.
    GenApi::CFloatPtr gainNode = nodemap.GetNode("Gain");
    if (IsReadable(gainNode))
    {
        double gainValue = gainNode->GetValue();
        qDebug() << "Gain: " << gainValue;
    }
    else
    {
        qDebug() << "Gain is not readable.";
    }

    // Read the gamma parameter.
    GenApi::CFloatPtr gammaNode = nodemap.GetNode("Gamma");
    if (IsReadable(gammaNode))
    {
        double gammaValue = gammaNode->GetValue();
        qDebug() << "Gamma: " << gammaValue;
    }
    else
    {
        qDebug() << "Gamma is not readable.";
    }

        return true;
    } catch (const GenericException& error) {
        qWarning() << "Basler connect failed:" << error.what();
        return false;
    }
}

bool XCamBasler::Disconnect()
{
    if (!Camera)
        return false;
    try {
        if (Camera->IsGrabbing())
            Camera->StopGrabbing();
        if (Camera->IsOpen())
            Camera->Close();
        return true;
    } catch (const GenericException& error) {
        qWarning() << "Basler disconnect failed:" << error.what();
        return false;
    }
}

bool XCamBasler::IsOpen()
{
    if (Camera == NULL)
        return false;

    try {
        return Camera->IsOpen();
    } catch (const GenericException& error) {
        qWarning() << "Basler state query failed:" << error.what();
        return false;
    }
}

unsigned char *XCamBasler::Capture()
{
    if (Camera == NULL)
            return NULL;

    if (!IsOpen())
        return NULL;

    if (data != NULL)
        free(data);

    if (width <= 0 || height <= 0)
        return NULL;
    const quint64 byteCount = static_cast<quint64>(height) *
                              static_cast<quint64>(width) * 3ULL;
    if (byteCount == 0 || byteCount > 512ULL * 1024ULL * 1024ULL)
        return NULL;
    const size_t size = static_cast<size_t>(byteCount);
    data = (unsigned char*)std::malloc(size);
    if (!data)
        return NULL;

    CImageFormatConverter formatConverter;
    formatConverter.OutputPixelFormat = PixelType_BGR8packed;

    CPylonImage pylonImage;

    CGrabResultPtr ptrGrabResult;
    try {
        // Keep the SDK wait below Camera's 3.5 s correlation timeout so the
        // G-Script receives a concrete capture error before its 5 s deadline.
        Camera->GrabOne(2500, ptrGrabResult);
        if (!ptrGrabResult || !ptrGrabResult->GrabSucceeded())
            return NULL;
        formatConverter.Convert(pylonImage, ptrGrabResult);
        memcpy(data, (uint8_t*) pylonImage.GetBuffer(), size);
    } catch (const GenericException& error) {
        qWarning() << "Basler capture failed:" << error.what();
        return NULL;
    }

    return data;
}

void XCamBasler::SetExposureTime(int value)
{
    if (!Camera || !IsOpen())
        return;
    try {
        GenApi::CEnumerationPtr exposureAuto(Camera->GetNodeMap().GetNode("ExposureAuto"));
        if (IsWritable(exposureAuto)) {
            GenApi::CEnumEntryPtr off = exposureAuto->GetEntryByName("Off");
            if (IsReadable(off))
                exposureAuto->SetIntValue(off->GetValue());
        }
        GenApi::CFloatPtr exposure(Camera->GetNodeMap().GetNode("ExposureTime"));
        if (IsWritable(exposure))
            exposure->SetValue(qBound(exposure->GetMin(), static_cast<double>(value), exposure->GetMax()));
    } catch (const GenericException& error) {
        qWarning() << "Basler exposure update failed:" << error.what();
    }
}

int XCamBasler::GetExposureTime()
{
    if (!Camera || !IsOpen())
        return 0;
    try {
        GenApi::CFloatPtr exposure(Camera->GetNodeMap().GetNode("ExposureTime"));
        return IsReadable(exposure) ? static_cast<int>(exposure->GetValue()) : 0;
    } catch (const GenericException& error) {
        qWarning() << "Basler exposure read failed:" << error.what();
        return 0;
    }
}
