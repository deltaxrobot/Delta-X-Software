//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: The IPylonGigEDevice interface
*/

#include "PylonGigE.h"


#ifndef __PYLON_PYLONGIGEDEVICE__H__
#define __PYLON_PYLONGIGEDEVICE__H__

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/Device.h>
#include "PylonGigE.h"

namespace Pylon
{

    /**
    \ingroup Pylon_LowLevelApi
    \interface IPylonGigEDevice
    \brief Low Level API: The interface for Basler GigE camera devices

    This interface extends the IPylonDevice interface.
    */


    interface PUBLIC_INTERFACE IPylonGigEDevice : public IPylonDevice
    {
        //! Enables/disables use of persistent IP address and DHCP usage
        virtual void ChangeIpConfiguration( bool EnablePersistentIp, bool EnableDhcp ) = 0;

        //! Reads the persistent IP address from the device
        virtual void GetPersistentIpAddress( String_t& IpAddress, String_t& SubnetMask, String_t& DefaultGateway ) = 0;

        //! Writes a persistent IP address to the device.
        /** Writing the persistent IP address does not change the IP configuration.
            Use the ChangeIpConfiguration() method to enable the usage of persistent IP addresses.
         */
        virtual void SetPersistentIpAddress( const String_t& IpAddress,
                                             const String_t& SubnetMask,
                                             const String_t& DefaultGateway ) = 0;

    };


}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* __PYLON_PYLONGIGEDEVICE__H__ */
