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


    size_t size = height * width * 3;
    unsigned char* data = (unsigned char*)std::malloc(size);

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
