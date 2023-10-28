//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief pylon universal instant camera class.
*/

#ifndef INCLUDED_BASLERUNIVERSALINSTANTCAMERA_H
#define INCLUDED_BASLERUNIVERSALINSTANTCAMERA_H

#pragma once

#include <pylon/_BaslerUniversalCameraParams.h>
#include <pylon/_BaslerUniversalStreamParams.h>
#include <pylon/_BaslerUniversalEventParams.h>
#include <pylon/_BaslerUniversalTLParams.h>
#include <pylon/BaslerUniversalConfigurationEventHandler.h>
#include <pylon/BaslerUniversalImageEventHandler.h>
#include <pylon/BaslerUniversalCameraEventHandler.h>
#include <pylon/BaslerUniversalGrabResultPtr.h>
#include <pylon/private/DeviceSpecificInstantCamera.h>
#include <pylon/gige/PylonGigEDevice.h>
#include <pylon/DeviceClass.h>
#include <pylon/NodeMapProxy.h>
#include <Base/GCException.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiUniversal
     * @{
     */

    class CBaslerUniversalInstantCamera;

    /// Lists all the types used by the universal instant camera class.
    struct CBaslerUniversalInstantCameraTraits
    {
        /// The type of the final camera class.
        typedef CBaslerUniversalInstantCamera InstantCamera_t;
        /// \copybrief Basler_UniversalCameraParams::CUniversalCameraParams_Params
        typedef Basler_UniversalCameraParams::CUniversalCameraParams_Params CameraParams_t;
        /// \copybrief Pylon::IPylonDevice
        typedef IPylonDevice IPylonDevice_t;
        /// \copybrief Pylon::CDeviceInfo
        typedef Pylon::CDeviceInfo DeviceInfo_t;
        /// \copybrief Basler_UniversalTLParams::CUniversalTLParams_Params
        typedef CNodeMapProxyT<Basler_UniversalTLParams::CUniversalTLParams_Params> TlParams_t;
        /// The parameters of the universal stream grabber.
        typedef CNodeMapProxyT<Basler_UniversalStreamParams::CUniversalStreamParams_Params> StreamGrabberParams_t;
        /// The parameters of the universal event grabber.
        typedef CNodeMapProxyT<Basler_UniversalEventParams::CUniversalEventParams_Params> EventGrabberParams_t;
        /// The universal configuration event handler class.
        typedef CBaslerUniversalConfigurationEventHandler ConfigurationEventHandler_t;
        /// The universal image event handler class.
        typedef CBaslerUniversalImageEventHandler ImageEventHandler_t;
        /// The universal camera event handler class.
        typedef CBaslerUniversalCameraEventHandler CameraEventHandler_t;
        /// The universal grab result data.
        typedef CBaslerUniversalGrabResultData GrabResultData_t;
        /// The universal grab result smart pointer.
        typedef CBaslerUniversalGrabResultPtr GrabResultPtr_t;

        //! Can be used to check whether the DeviceClass() can be used for enumeration.
        static bool HasSpecificDeviceClass()
        {
            return false;
        }
//! The name of this device class. Use this one for enumeration.
        static String_t DeviceClass()
        {
            throw LOGICAL_ERROR_EXCEPTION( "The CBaslerUniversalInstantCamera has no specific device class. The method DeviceClass() cannot be used." );
        }

    };
    /*!
    \class  CBaslerUniversalInstantCamera
    \brief  Extends the CInstantCamera by universal parameter interface classes combining all interface types.
    */
    class CBaslerUniversalInstantCamera : public CDeviceSpecificInstantCameraT<CBaslerUniversalInstantCameraTraits>
    {
    public:
        /*!
            \copybrief CInstantCamera::CInstantCamera()
            \copydetails CInstantCamera::CInstantCamera
        */
        CBaslerUniversalInstantCamera()
        {
        }

        /*!
            \copybrief CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
            \copydetails CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
        */
        CBaslerUniversalInstantCamera( IPylonDevice* pDevice, ECleanup cleanupProcedure = Cleanup_Delete )
            : CDeviceSpecificInstantCameraT<CBaslerUniversalInstantCameraTraits>( pDevice, cleanupProcedure )
        {
        }

        /*!
            \copybrief CInstantCamera::~CInstantCamera
            \copydetails CInstantCamera::~CInstantCamera
        */
        ~CBaslerUniversalInstantCamera()
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
            GetGigEDevice()->ChangeIpConfiguration( EnablePersistentIp, EnableDhcp );
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
            GetGigEDevice()->GetPersistentIpAddress( IpAddress, SubnetMask, DefaultGateway );
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
            GetGigEDevice()->SetPersistentIpAddress( IpAddress, SubnetMask, DefaultGateway );
        }

    protected:
        //Get the pointer for the Universal device.
        virtual IPylonGigEDevice* GetGigEDevice()
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

        //Create device grab result data. Is subject to change without notice.
        virtual CGrabResultData* CreateDeviceSpecificGrabResultData()
        {
            return new GrabResultData_t();
        }
    };

    /**
     * @}
     */

} // namespace Pylon

#endif /* INCLUDED_BASLERUNIVERSALINSTANTCAMERA_H */
