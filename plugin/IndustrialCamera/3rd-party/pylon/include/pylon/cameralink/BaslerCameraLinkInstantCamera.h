//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Camera Link Specific Instant Camera class for Basler Camera Link devices.
*/

#ifndef INCLUDED_BASLERCAMERALINKINSTANTCAMERA_H_6872827
#define INCLUDED_BASLERCAMERALINKINSTANTCAMERA_H_6872827

#include <pylon/cameralink/_BaslerCameraLinkCameraParams.h>
#include <pylon/cameralink/PylonCLSerDeviceInfo.h>
#include <pylon/cameralink/BaslerCameraLinkConfigurationEventHandler.h>
#include <pylon/cameralink/BaslerCameraLinkImageEventHandler.h>
#include <pylon/cameralink/BaslerCameraLinkCameraEventHandler.h>
#include <pylon/cameralink/BaslerCameraLinkGrabResultPtr.h>
#include <pylon/private/DeviceSpecificInstantCamera.h>
#include <pylon/DeviceClass.h>
#include <pylon/NodeMapProxy.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiCameraLink
     * @{
     */

    // This dummy implementation is used by the Device Specific Instant Camera for Camera Link
    // because the Camera Link Transport Layer does not support some features.
    class CCameraLinkDummyParams_Params
    {
    public:
        void _Initialize( GENAPI_NAMESPACE::INodeMap* )
        {
        }
    };

    class CBaslerCameraLinkInstantCamera;

    /// Lists all the types used by the Device Specific Instant Camera class for Camera Link.
    struct CBaslerCameraLinkInstantCameraTraits
    {
        /// The type of the final camera class.
        typedef CBaslerCameraLinkInstantCamera InstantCamera_t;
        /// \copybrief Basler_CLCameraParams::CCLCameraParams_Params
        typedef Basler_CLCameraParams::CCLCameraParams_Params CameraParams_t;
        /// \copybrief Pylon::IPylonDevice
        typedef IPylonDevice IPylonDevice_t;
        /// \copybrief Pylon::CBaslerCameraLinkDeviceInfo
        typedef Pylon::CBaslerCameraLinkDeviceInfo DeviceInfo_t;
        /// Not supported by Camera Link transport layer.
        typedef CNodeMapProxyT<CCameraLinkDummyParams_Params> TlParams_t;
        /// Not supported by Camera Link transport layer.
        typedef CNodeMapProxyT<CCameraLinkDummyParams_Params> StreamGrabberParams_t;
        /// Not supported by Camera Link transport layer.
        typedef CNodeMapProxyT<CCameraLinkDummyParams_Params> EventGrabberParams_t;
        /// The Camera Link specific configuration event handler class.
        typedef CBaslerCameraLinkConfigurationEventHandler ConfigurationEventHandler_t;
        /// The Camera Link specific image event handler class.
        typedef CBaslerCameraLinkImageEventHandler ImageEventHandler_t;
        /// The Camera Link specific camera event handler class.
        typedef CBaslerCameraLinkCameraEventHandler CameraEventHandler_t;
        /// The Camera Link specific grab result data.
        typedef CBaslerCameraLinkGrabResultData GrabResultData_t;
        /// The Camera Link specific grab result smart pointer.
        typedef CBaslerCameraLinkGrabResultPtr GrabResultPtr_t;

        //! Can be used to check whether the DeviceClass() can be used for enumeration.
        static bool HasSpecificDeviceClass()
        {
            return true;
        }
 //! The name of this device class. Use this one for enumeration.
        static String_t DeviceClass()
        {
            return BaslerCameraLinkDeviceClass;
        }
    };


    /*!
    \class  CBaslerCameraLinkInstantCamera
    \brief  Extends the CInstantCamera by Camera Link specific parameter interface classes.
    */
    PYLON_DEFINE_INSTANT_CAMERA( CBaslerCameraLinkInstantCamera, CDeviceSpecificInstantCameraT<CBaslerCameraLinkInstantCameraTraits> )

    /**
     * @}
     */
} // namespace Pylon

#endif /* INCLUDED_BASLERCAMERALINKINSTANTCAMERA_H_6872827 */
