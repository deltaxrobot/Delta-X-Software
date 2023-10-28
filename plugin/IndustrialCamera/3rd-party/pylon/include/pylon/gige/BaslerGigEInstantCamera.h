//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Pylon GigE specific instant camera class.
*/

#ifndef INCLUDED_BASLERGIGEINSTANTCAMERA_H_7164973
#define INCLUDED_BASLERGIGEINSTANTCAMERA_H_7164973

#include <pylon/gige/_BaslerGigECameraParams.h>
namespace Basler_GigECameraParams = Basler_GigECamera;
#include <pylon/gige/_GigEStreamParams.h>
#include <pylon/gige/_GigEEventParams.h>
#include <pylon/gige/_GigETLParams.h>
#include <pylon/gige/BaslerGigEDeviceInfo.h>
#include <pylon/gige/PylonGigEDevice.h>
#include <pylon/gige/BaslerGigEConfigurationEventHandler.h>
#include <pylon/gige/BaslerGigEImageEventHandler.h>
#include <pylon/gige/BaslerGigECameraEventHandler.h>
#include <pylon/gige/BaslerGigEGrabResultPtr.h>
#include <pylon/private/DeviceSpecificInstantCamera.h>
#include <pylon/DeviceClass.h>
#include <pylon/NodeMapProxy.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGigE
     * @{
     */

    class CBaslerGigEInstantCamera;

    /// Lists all the types used by the GigE device specific instant camera class.
    struct CBaslerGigEInstantCameraTraits
    {
        /// The type of the final camera class.
        typedef CBaslerGigEInstantCamera InstantCamera_t;
        /// \copybrief Basler_GigECamera::CGigECamera_Params
        typedef Basler_GigECamera::CGigECamera_Params CameraParams_t;
        /// \copybrief Pylon::IPylonGigEDevice
        typedef IPylonGigEDevice IPylonDevice_t;
        /// \copybrief Pylon::CBaslerGigEDeviceInfo
        typedef Pylon::CBaslerGigEDeviceInfo DeviceInfo_t;
        /// \copybrief Pylon::CPylonGigETLParams
        typedef CNodeMapProxyT<Basler_GigETLParams::CGigETLParams_Params> TlParams_t;
        /// The parameters of the GigE streamgrabber.
        typedef CNodeMapProxyT<Basler_GigEStreamParams::CGigEStreamParams_Params> StreamGrabberParams_t;
        /// The parameters of the GigE eventgrabber.
        typedef CNodeMapProxyT<Basler_GigEEventParams::CGigEEventParams_Params> EventGrabberParams_t;
        /// The GigE specific configuration event handler class.
        typedef CBaslerGigEConfigurationEventHandler ConfigurationEventHandler_t;
        /// The GigE specific image event handler class.
        typedef CBaslerGigEImageEventHandler ImageEventHandler_t;
        /// The GigE specific camera event handler class.
        typedef CBaslerGigECameraEventHandler CameraEventHandler_t;
        /// The GigE specific grab result data.
        typedef CBaslerGigEGrabResultData GrabResultData_t;
        /// The GigE specific grab result smart pointer.
        typedef CBaslerGigEGrabResultPtr GrabResultPtr_t;

        //! Can be used to check whether the DeviceClass() can be used for enumeration.
        static bool HasSpecificDeviceClass()
        {
            return true;
        }
 //! The name of this device class. Use this one for enumeration.
        static String_t DeviceClass()
        {
            return BaslerGigEDeviceClass;
        }
    };
    /*!
    \class  CBaslerGigEInstantCamera
    \brief  Extends the CInstantCamera by GigE specific parameter interface classes and GigE specific methods.
    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCamera instead.
    */
    PYLON_6_0_DEPRECATED( "Use CBaslerUniversalInstantCamera" )
        class CBaslerGigEInstantCamera : public CDeviceSpecificInstantCameraT<CBaslerGigEInstantCameraTraits>
    {
    public:
        /*!
            \copybrief CInstantCamera::CInstantCamera()
            \copydetails CInstantCamera::CInstantCamera
        */
        CBaslerGigEInstantCamera()
        {
        }

        /*!
            \copybrief CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
            \copydetails CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
        */
        CBaslerGigEInstantCamera( IPylonDevice* pDevice, ECleanup cleanupProcedure = Cleanup_Delete )
            : CDeviceSpecificInstantCameraT<CBaslerGigEInstantCameraTraits>( pDevice, cleanupProcedure )
        {
        }

        /*!
            \copybrief CInstantCamera::~CInstantCamera
            \copydetails CInstantCamera::~CInstantCamera
        */
        ~CBaslerGigEInstantCamera()
        {
            Attach( NULL );
            InternalShutdownEventHandlers();
        }

        /*!
        \brief Enables/disables use of persistent IP address and DHCP usage of the attached %Pylon Device.

        See Pylon::IPylonGigEDevice::ChangeIpConfiguration()

        \pre
        <ul>
        <li> A %Pylon Device is attached.
        <li> The %Pylon Device is open.
        </ul>

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        void ChangeIpConfiguration( bool EnablePersistentIp, bool EnableDhcp )
        {
            AutoLock lock( CInstantCamera::GetLock() );
            GetDevice()->ChangeIpConfiguration( EnablePersistentIp, EnableDhcp );
        }

        /*!
        \brief Reads the persistent IP address from the attached %Pylon Device.

        See Pylon::IPylonGigEDevice::GetPersistentIpAddress()

        \pre
        <ul>
        <li> A %Pylon Device is attached.
        <li> The %Pylon Device is open.
        </ul>
        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        void GetPersistentIpAddress( String_t& IpAddress, String_t& SubnetMask, String_t& DefaultGateway )
        {
            AutoLock lock( CInstantCamera::GetLock() );
            GetDevice()->GetPersistentIpAddress( IpAddress, SubnetMask, DefaultGateway );
        }

        /*!
        \brief Writes a persistent IP address to the attached %Pylon Device.

        See Pylon::IPylonGigEDevice::SetPersistentIpAddress()

        \pre
        <ul>
        <li> A %Pylon Device is attached.
        <li> The %Pylon Device is open.
        </ul>
        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        void SetPersistentIpAddress( const String_t& IpAddress,
                                     const String_t& SubnetMask,
                                     const String_t& DefaultGateway )

        {
            AutoLock lock( CInstantCamera::GetLock() );
            GetDevice()->SetPersistentIpAddress( IpAddress, SubnetMask, DefaultGateway );
        }

    protected:
        //Get the pointer for the GigE device.
        virtual IPylonGigEDevice* GetDevice()
        {
            IPylonDevice* pDevice = CInstantCamera::GetDevice();
            IPylonGigEDevice* pGigEDevice = dynamic_cast<IPylonGigEDevice*>(pDevice);

            // Check whether device type matches camera type.
            if (!pGigEDevice)
            {
                throw LOGICAL_ERROR_EXCEPTION( "The attached pylon device type must be a GigE device." );
            }

            return pGigEDevice;
        }

        //Create device specific grab result data. Is subject to change without notice.
        virtual CGrabResultData* CreateDeviceSpecificGrabResultData()
        {
            return new GrabResultData_t();
        }
    };

    /**
     * @}
     */

} // namespace Pylon

#endif /* INCLUDED_BASLERGIGEINSTANTCAMERA_H_7164973 */
