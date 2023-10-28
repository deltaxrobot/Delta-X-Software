//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Contains the Camera Link specific grab result ptr class.
*/

#ifndef INCLUDED_BASLERCAMERALINKGRABRESULTPTR_H_03519839
#define INCLUDED_BASLERCAMERALINKGRABRESULTPTR_H_03519839

#include <pylon/cameralink/BaslerCameraLinkGrabResultData.h>
#include <pylon/private/DeviceSpecificGrabResultPtr.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiCameraLink
     * @{
     */

    /// The Camera Link specific grab result smart pointer.
    PYLON_DEFINE_DEVICE_SPECIFIC_GRAB_RESULT_PTR( CBaslerCameraLinkGrabResultPtr, CBaslerCameraLinkGrabResultData )

     /**
     * @}
     */
}

#endif /* INCLUDED_BASLERCAMERALINKGRABRESULTPTR_H_03519839 */
