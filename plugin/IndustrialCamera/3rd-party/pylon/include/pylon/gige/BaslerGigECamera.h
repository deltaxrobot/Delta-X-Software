//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Pylon GigE Vision camera interface for Basler GigE Vision cameras
*/

#ifndef BASLER_GIGE_CAMERA_H
#define BASLER_GIGE_CAMERA_H

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include "PylonGigECamera.h"

#include "_BaslerGigECameraParams.h"
namespace Basler_GigECameraParams = Basler_GigECamera;


namespace Pylon
{
    //**************************************************************************************************
    //! Low Level API: The camera class for Basler GigE Vision camera devices
    /**
    Class for Basler GigE Vision cameras providing access to camera parameters.
    \see \ref configuringcameras

    \ingroup Pylon_LowLevelApi

    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCamera instead.
    */
    //**************************************************************************************************
    PYLON_DEFINE_CAMERA( CBaslerGigECamera, Pylon::CPylonGigECameraT<Basler_GigECamera::CGigECamera_Params> );

} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // BASLER_GIGE_CAMERA_H
