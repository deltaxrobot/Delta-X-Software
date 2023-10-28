//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Generic pylon USB3 Vision camera interface
*/

#ifndef BASLER_USB3VISION_CAMERA_H
#define BASLER_USB3VISION_CAMERA_H

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


#include "PylonUsbCamera.h"

#include "_BaslerUsbCameraParams.h"


namespace Pylon
{
    //**************************************************************************************************
    //! Low Level API: The camera class for Basler USB3 Vision camera devices
    /**
    Class for Basler USB3 Vision cameras providing access to camera parameters.
    \see \ref configuringcameras

    \ingroup Pylon_LowLevelApi

    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCamera instead.
    */
    //**************************************************************************************************
    PYLON_DEFINE_CAMERA( CBaslerUsbCamera, Pylon::CPylonUsbCameraT<Basler_UsbCameraParams::CUsbCameraParams_Params> );

} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // BASLER_USB3VISION_CAMERA_H
