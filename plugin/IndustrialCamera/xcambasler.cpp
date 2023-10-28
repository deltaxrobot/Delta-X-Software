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
        Camera->StopGrabbing();
        Camera->Close();
        delete Camera;
    }

    PylonTerminate();
}

bool XCamBasler::Connect()
{
    Pylon::PylonInitialize();

    if (Camera == NULL)
        return false;

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

    // Đọc thông số Gain
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

    // Đọc thông số Gamma
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
}

bool XCamBasler::Disconnect()
{
    Camera->Close();
    return true;
}

bool XCamBasler::IsOpen()
{
    if (Camera == NULL)
        return false;

    return Camera->IsOpen();
}

unsigned char *XCamBasler::Capture()
{
    if (Camera == NULL)
            return NULL;

    if (Camera->IsOpen() == false)
        return NULL;

    Pylon::PylonInitialize();

    if (data != NULL)
        free(data);

    size_t size = height * width * 3;
    data = (unsigned char*)std::malloc(size);

    CImageFormatConverter formatConverter;
    formatConverter.OutputPixelFormat = PixelType_BGR8packed;

    CPylonImage pylonImage;

    static CGrabResultPtr ptrGrabResult;
    Camera->GrabOne(5000, ptrGrabResult);

    if (ptrGrabResult->GrabSucceeded())
    {
        formatConverter.Convert(pylonImage, ptrGrabResult);

        memcpy(data, (uint8_t*) pylonImage.GetBuffer(), size);
    }

    return data;
}

void XCamBasler::SetExposureTime(int value)
{
//    GenApi::INodeMap& nodemap = Camera->GetNodeMap();
//    GenApi::CIntegerPtr ExposureTimeRaw(nodemap.GetNode("ExposureTimeRaw"));
//    ExposureTimeRaw->SetValue(value);
}

int XCamBasler::GetExposureTime()
{
//    GenApi::INodeMap& nodemap = Camera->GetNodeMap();
//    GenApi::CIntegerPtr ExposureTimeRaw(nodemap.GetNode("ExposureTimeRaw"));

//    if(ExposureTimeRaw.IsValid())
//    {
//        return ExposureTimeRaw->GetValue();
//    }

    return 0;
}
