//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2012-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief USB Specific Instant Camera class for Basler USB devices.
*/

#ifndef INCLUDED_BASLERUSBINSTANTCAMERA_H_6872827
#define INCLUDED_BASLERUSBINSTANTCAMERA_H_6872827

#include <pylon/usb/_BaslerUsbCameraParams.h>
#include <pylon/usb/BaslerUsbDeviceInfo.h>
#include <pylon/usb/BaslerUsbConfigurationEventHandler.h>
#include <pylon/usb/BaslerUsbImageEventHandler.h>
#include <pylon/usb/BaslerUsbCameraEventHandler.h>
#include <pylon/usb/BaslerUsbGrabResultPtr.h>
#include <pylon/private/DeviceSpecificInstantCamera.h>
#include <pylon/DeviceClass.h>
#include <pylon/NodeMapProxy.h>
#include <pylon/usb/_UsbStreamParams.h>
#include <pylon/usb/_UsbEventParams.h>
#include <pylon/usb/_UsbTLParams.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiUsb
     * @{
     */

    class CBaslerUsbInstantCamera;

    /// Lists all the types used by the Device Specific Instant Camera class for USB.
    struct CBaslerUsbInstantCameraTraits
    {
        /// The type of the final camera class.
        typedef CBaslerUsbInstantCamera InstantCamera_t;
        /// \copybrief Basler_UsbCameraParams::CUsbCameraParams_Params
        typedef Basler_UsbCameraParams::CUsbCameraParams_Params CameraParams_t;
        /// \copybrief Pylon::IPylonDevice
        typedef IPylonDevice IPylonDevice_t;
        /// \copybrief Pylon::CBaslerUsbDeviceInfo
        typedef Pylon::CBaslerUsbDeviceInfo DeviceInfo_t;
        /// The parameters of the USB transport layer.
        typedef CNodeMapProxyT<Basler_UsbTLParams::CUsbTLParams_Params> TlParams_t;
        /// The parameters of the USB stream grabber.
        typedef CNodeMapProxyT<Basler_UsbStreamParams::CUsbStreamParams_Params> StreamGrabberParams_t;
        /// The parameters of the USB event grabber.
        typedef CNodeMapProxyT<Basler_UsbEventParams::CUsbEventParams_Params> EventGrabberParams_t;
        /// The USB specific configuration event handler class.
        typedef CBaslerUsbConfigurationEventHandler ConfigurationEventHandler_t;
        /// The USB specific image event handler class.
        typedef CBaslerUsbImageEventHandler ImageEventHandler_t;
        /// The USB specific camera event handler class.
        typedef CBaslerUsbCameraEventHandler CameraEventHandler_t;
        /// The USB specific grab result data.
        typedef CBaslerUsbGrabResultData GrabResultData_t;
        /// The USB specific grab result smart pointer.
        typedef CBaslerUsbGrabResultPtr GrabResultPtr_t;

        //! Can be used to check whether the DeviceClass() can be used for enumeration.
        static bool HasSpecificDeviceClass()
        {
            return true;
        }
 //! The name of this device class. Use this one for enumeration.
        static String_t DeviceClass()
        {
            return BaslerUsbDeviceClass;
        }
    };


    /*!
    \class  CBaslerUsbInstantCamera
    \brief  Extends the CInstantCamera by USB specific parameter interface classes.
    */
    PYLON_DEFINE_INSTANT_CAMERA( CBaslerUsbInstantCamera, CDeviceSpecificInstantCameraT<CBaslerUsbInstantCameraTraits> )

    /**
     * @}
     */
} // namespace Pylon

#endif /* INCLUDED_BASLERUSBINSTANTCAMERA_H_6872827 */
