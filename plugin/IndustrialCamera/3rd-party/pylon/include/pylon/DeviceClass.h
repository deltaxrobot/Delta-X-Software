//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2008-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Thomas Koeller
//-----------------------------------------------------------------------------
/*!
\file
\brief Device class definitions
*/

#ifndef __DEVICE_CLASS_H__
#define __DEVICE_CLASS_H__

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>


namespace Pylon
{
    /** \addtogroup Pylon_TransportLayer
     * @{
     */
    // PYLON_WIN_BUILD only controls whether the DeviceClass is listed in the API reference guide
    const char* const Basler1394DeviceClass = "Basler1394"; ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerGigEDeviceClass = "BaslerGigE"; ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerCamEmuDeviceClass = "BaslerCamEmu"; ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerIpCamDeviceClass = "BaslerIPCam"; ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerCameraLinkDeviceClass = "BaslerCameraLink"; ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerGenTlDeviceClassPrefix = "BaslerGTC";    ///< The actual device class string is made up of this prefix + '/' + [TL Vendor] + '/' + [TL Model].
    const char* const BaslerGenTlGevDeviceClass = "BaslerGTC/Basler/GEV";
    const char* const BaslerGenTlU3vDeviceClass = "BaslerGTC/Basler/U3V";
    const char* const BaslerGenTlCxpDeviceClass = "BaslerGTC/Basler/CXP"; ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerGenTlBlazeDeviceClass = "BaslerGTC/Basler/GenTL_Producer_for_Basler_blaze_101_cameras"; ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerUsbDeviceClass = "BaslerUsb";            ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    const char* const BaslerBconDeviceClass = "BaslerBcon";          ///< This device class can be used to create the corresponding Transport Layer object or when creating Devices with the Transport Layer Factory.
    /**
     * @}
     */
}
#endif
