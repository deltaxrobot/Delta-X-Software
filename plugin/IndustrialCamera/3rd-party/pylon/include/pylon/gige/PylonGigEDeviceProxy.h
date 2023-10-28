//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Pylon generic GigEVision device interface declaration
*/

#ifndef __PYLON_PYLONGIGEDEVICEPROXY__H__
#define __PYLON_PYLONGIGEDEVICEPROXY__H__

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include "PylonGigEDevice.h"
#include "../PylonDeviceProxy.h"


namespace Pylon
{
    //**************************************************************************************************
    /// Low Level API: The camera class for GigE Vision camera devices
    /**
    \ingroup Pylon_LowLevelApi

    Extends the Pylon::CPylonDeviceProxyT class by GigE Vision specific functionality.

    \tparam TCameraParams  The camera specific parameter class (auto generated from camera xml file)
    */
    //**************************************************************************************************
    template<class TCameraParams>
    class CPylonGigEDeviceProxyT : public CPylonDeviceProxyT<TCameraParams>
    {
    public:
        //! \name Construction
        // \{

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()

        \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()
        */
        CPylonGigEDeviceProxyT();

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)

        \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)
        */
        CPylonGigEDeviceProxyT( IPylonDevice*, bool takeOwnership = true );

        //! Destructor
        virtual ~CPylonGigEDeviceProxyT();

        //\}


    private:
        //! \name Assignment and copying is not supported
        // \{
        CPylonGigEDeviceProxyT( const CPylonGigEDeviceProxyT& );
        CPylonGigEDeviceProxyT& operator=( const CPylonGigEDeviceProxyT& );
        // \}


    public:
        //! \name Some smart pointer functionality
        // \{

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::Attach()

        \copydetails Pylon::CPylonDeviceProxyT::Attach()
        */
        virtual void Attach( IPylonDevice*, bool takeOwnership = true );

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::IsAttached()

        \copydetails Pylon::CPylonDeviceProxyT::IsAttached()
        */
        virtual bool IsAttached() const;

        // \}

    public:
        //! \name Implementation of the IPylonGigEDevice interface.
        //! See Pylon::IPylonGigEDevice for more details.
        // \{

        /** \brief \copybrief Pylon::IPylonGigEDevice::ChangeIpConfiguration()

        \copydetails Pylon::IPylonGigEDevice::ChangeIpConfiguration()
        */
        void ChangeIpConfiguration( bool EnablePersistentIp, bool EnableDhcp )
        {
            CheckGigEDevicePtr();
            m_pGigEDevice->ChangeIpConfiguration( EnablePersistentIp, EnableDhcp );
        }

        /** \brief \copybrief Pylon::IPylonGigEDevice::GetPersistentIpAddress()

        \copydetails Pylon::IPylonGigEDevice::GetPersistentIpAddress()
        */
        void GetPersistentIpAddress( String_t& IpAddress, String_t& SubnetMask, String_t& DefaultGateway )
        {
            CheckGigEDevicePtr();
            m_pGigEDevice->GetPersistentIpAddress( IpAddress, SubnetMask, DefaultGateway );
        }

        /** \brief \copybrief Pylon::IPylonGigEDevice::SetPersistentIpAddress()

        \copydetails Pylon::IPylonGigEDevice::SetPersistentIpAddress()
        */
        void SetPersistentIpAddress( const String_t& IpAddress,
                                     const String_t& SubnetMask,
                                     const String_t& DefaultGateway )

        {
            CheckGigEDevicePtr();
            m_pGigEDevice->SetPersistentIpAddress( IpAddress, SubnetMask, DefaultGateway );
        }

        // \}

    protected:
        void CheckGigEDevicePtr() const
        {
            if (NULL == m_pGigEDevice)
            {
                throw LOGICAL_ERROR_EXCEPTION( "The camera class is not attached to an IPylonGigEDevice" );
            }
        }

        IPylonGigEDevice* m_pGigEDevice;
    };


    //**************************************************************************************************
    // CPylonGigEDeviceProxyT implementation
    //**************************************************************************************************

    template<class TCameraParams>
    inline CPylonGigEDeviceProxyT<TCameraParams>::CPylonGigEDeviceProxyT()
        : CPylonDeviceProxyT<TCameraParams>()
        , m_pGigEDevice( NULL )
    {
    }

    template<class TCameraParams>
    inline CPylonGigEDeviceProxyT<TCameraParams>::CPylonGigEDeviceProxyT( IPylonDevice* pDevice, bool takeOwnership )
        : CPylonDeviceProxyT<TCameraParams>()
        , m_pGigEDevice( NULL )
    {
        Attach( pDevice, takeOwnership );
    }

    template<class TCameraParams>
    inline CPylonGigEDeviceProxyT<TCameraParams>::~CPylonGigEDeviceProxyT()
    {
    }

    template<class TCameraParams>
    inline void CPylonGigEDeviceProxyT<TCameraParams>::Attach( IPylonDevice* pDevice, bool takeOwnership )
    {
        IPylonGigEDevice* pGigEDevice = dynamic_cast<IPylonGigEDevice*>(pDevice);
        if (!pGigEDevice)
        {
            throw LOGICAL_ERROR_EXCEPTION( "The attached Pylon Device is not of type IPylonGigEDevice!" );
        }

        CPylonDeviceProxyT<TCameraParams>::Attach( pDevice, takeOwnership );
        m_pGigEDevice = pGigEDevice;
    }

    template<class TCameraParams>
    inline bool CPylonGigEDeviceProxyT<TCameraParams>::IsAttached() const
    {
        return NULL != m_pGigEDevice;
    }

} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif
