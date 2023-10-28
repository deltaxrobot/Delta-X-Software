//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Pylon CameraLink camera interface for Basler CameraLink cameras
*/

#ifndef BASLER_CAMERALINK_CAMERA_H
#define BASLER_CAMERALINK_CAMERA_H

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


#include "PylonCameraLinkCamera.h"

#include "_BaslerCameraLinkCameraParams.h"
namespace Basler_CameraLinkParams = Basler_CLCameraParams; // Pylon 2.0 compatibility


namespace Pylon
{
    //**************************************************************************************************
    //! Low Level API: The camera class for Basler CameraLink camera devices
    /**
    Class for Basler CameraLink cameras providing access to camera parameters.
    \see \ref configuringcameras

    \ingroup Pylon_LowLevelApi

    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCamera instead.
    */
    //**************************************************************************************************
    PYLON_DEFINE_CAMERA( CBaslerCameraLinkCamera, Pylon::CPylonCameraLinkCameraT<Basler_CLCameraParams::CCLCameraParams_Params> );

} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // BASLER_CAMERALINK_CAMERA_H
