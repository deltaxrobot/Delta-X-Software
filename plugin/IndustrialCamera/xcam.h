#ifndef XCAM_H
#define XCAM_H

#include <iostream>

class XCam
{
public:
    XCam();
    virtual ~XCam();

    virtual bool Connect() = 0;
    virtual bool IsOpen() = 0;
    virtual unsigned char* Capture() = 0;

    int height;
    int width;
};

#endif // XCAM_H
