//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Pylon generic device interface declaration
*/


#ifndef __PYLON_PYLONDEVICEPROXY__H__
#define __PYLON_PYLONDEVICEPROXY__H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <Base/GCException.h>
#include "Device.h"
#include "TlFactory.h"


//! Macro to define a custom camera class
#define PYLON_DEFINE_CAMERA(ClassName, BaseClass) \
    PYLON_6_0_DEPRECATED("Use CBaslerUniversalInstantCamera") \
    class ClassName : public BaseClass \
    { \
    public: \
        /** \name Construction */ \
        /*@{*/ \
        /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()
            \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()
        */ \
            ClassName() \
        { \
        } \
        /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)
            \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)
        */ \
            ClassName( IPylonDevice* pDevice, bool takeOwnership = true ) : BaseClass( pDevice, takeOwnership ) \
        { \
        } \
        /** \brief \copybrief Pylon::CPylonDeviceProxyT::~CPylonDeviceProxyT()
            \copydetails Pylon::CPylonDeviceProxyT::~CPylonDeviceProxyT()
        */ \
            virtual ~ClassName() \
        { \
        } \
            /*@}*/ \
    };


    namespace Pylon
    {
        //**************************************************************************************************
        //! Low Level API: The camera class for generic camera devices
        /**
        This is the base class for pylon camera classes providing access to camera parameters.
        \see \ref configuringcameras

        \tparam TCameraParams  The camera specific parameter class (auto generated from camera xml file)
        \ingroup Pylon_LowLevelApi
        */
        //**************************************************************************************************
        template<class TCameraParams>
        class CPylonDeviceProxyT : public TCameraParams
        {
        public:
            //! \name Construction
            // \{

            //! Creates a camera object that is not attached to an pylon device. Use the Attach() method to attach the device
            CPylonDeviceProxyT();

            /** \brief Creates a camera object and attaches a camera object to a pylon device that takes the ownership over an pylon device.

            When having the ownership, the destructor of this camera object destroys the pylon device
            the camera object is attached to. Otherwise, the pylon device object remains valid when the camera
            object has been destroyed.
            */
            CPylonDeviceProxyT( IPylonDevice*, bool takeOwnership = true );

            //! Destructor
            virtual ~CPylonDeviceProxyT();

            //\}


        private:
            //! \name Assignment and copying is not supported
            // \{
            CPylonDeviceProxyT( const CPylonDeviceProxyT& );
            CPylonDeviceProxyT& operator=( const CPylonDeviceProxyT& );
            // \}


        public:
            //! \name Some smart pointer functionality
            // \{

            /** \brief Attach the camera object to a pylon device

            It is not allowed to call Attach when the camera object is already attached!

            When having the ownership, the destructor of this camera object destroys the pylon device
            the camera object is attached to. Otherwise, the pylon device object remains valid when the camera
            object has been destroyed.
            */
            virtual void Attach( IPylonDevice*, bool takeOwnership = true );

            //! Checks if a pylon device is attached to the camera object
            virtual bool IsAttached() const;

            //! Checks if the camera object has the ownership of the pylon device
            virtual bool HasOwnership() const;

            //! Returns the pylon device interface pointer
            virtual IPylonDevice* GetDevice() const;

            // \}


        public:
            //! \name Implementation of the IPylonDevice interface.
            //! See Pylon::IPylonDevice for more details.
            // \{

            /** \brief \copybrief Pylon::IPylonDevice::Open()

                \copydetails Pylon::IPylonDevice::Open()
            */
            void Open( AccessModeSet mode = (Stream | Control | Event) )
            {
                CheckDevicePtr();
                m_pDevice->Open( mode );
            }

            /** \brief \copybrief Pylon::IPylonDevice::Close()

                \copydetails Pylon::IPylonDevice::Close()
            */
            void Close( void )
            {
                CheckDevicePtr();
                m_pDevice->Close();
            }

            /** \brief \copybrief Pylon::IPylonDevice::IsOpen()

            \copydetails Pylon::IPylonDevice::IsOpen()
            */
            bool IsOpen( void ) const
            {
                CheckDevicePtr();
                return m_pDevice->IsOpen();
            }

            /** \brief \copybrief Pylon::IPylonDevice::AccessMode()

            \copydetails Pylon::IPylonDevice::AccessMode()
            */
            AccessModeSet AccessMode( void ) const
            {
                CheckDevicePtr();
                return m_pDevice->AccessMode();
            }

            /** \brief \copybrief Pylon::IPylonDevice::GetDeviceInfo()

            \copydetails Pylon::IPylonDevice::GetDeviceInfo()
            */
            const CDeviceInfo& GetDeviceInfo( void ) const
            {
                CheckDevicePtr();
                return m_pDevice->GetDeviceInfo();
            }


            /** \brief \copybrief Pylon::IPylonDevice::GetNumStreamGrabberChannels()

            \copydetails Pylon::IPylonDevice::GetNumStreamGrabberChannels()
            */
            uint32_t GetNumStreamGrabberChannels( void ) const
            {
                CheckDevicePtr();
                return m_pDevice->GetNumStreamGrabberChannels();
            }

            /** \brief \copybrief Pylon::IPylonDevice::GetStreamGrabber()

            \copydetails Pylon::IPylonDevice::GetStreamGrabber()
            */
            IStreamGrabber* GetStreamGrabber( uint32_t index )
            {
                CheckDevicePtr();
                return m_pDevice->GetStreamGrabber( index );
            }

            /** \brief \copybrief Pylon::IPylonDevice::GetEventGrabber()

            \copydetails Pylon::IPylonDevice::GetEventGrabber()
            */
            IEventGrabber* GetEventGrabber( void )
            {
                CheckDevicePtr();
                return m_pDevice->GetEventGrabber();
            }

            /** \brief \copybrief Pylon::IPylonDevice::GetNodeMap()

            \copydetails Pylon::IPylonDevice::GetNodeMap()
            */
            GENAPI_NAMESPACE::INodeMap* GetNodeMap( void )
            {
                CheckDevicePtr();
                return m_pDevice->GetNodeMap();
            }

            /** \brief \copybrief Pylon::IPylonDevice::GetTLNodeMap()

            \copydetails Pylon::IPylonDevice::GetTLNodeMap()
            */
            GENAPI_NAMESPACE::INodeMap* GetTLNodeMap( void )
            {
                CheckDevicePtr();
                return m_pDevice->GetTLNodeMap();
            }

            /** \brief \copybrief Pylon::IPylonDevice::CreateChunkParser()

            \copydetails Pylon::IPylonDevice::CreateChunkParser()
            */
            Pylon::IChunkParser* CreateChunkParser( void )
            {
                CheckDevicePtr();
                return m_pDevice->CreateChunkParser();
            }

            /** \brief \copybrief Pylon::IPylonDevice::DestroyChunkParser()

            \copydetails Pylon::IPylonDevice::DestroyChunkParser()
            */
            void DestroyChunkParser( Pylon::IChunkParser* pChunkParser )
            {
                CheckDevicePtr();
                m_pDevice->DestroyChunkParser( pChunkParser );
            }


            /** \brief \copybrief Pylon::IPylonDevice::CreateEventAdapter()

            \copydetails Pylon::IPylonDevice::CreateEventAdapter()
            */
            IEventAdapter* CreateEventAdapter( void )
            {
                CheckDevicePtr();
                return m_pDevice->CreateEventAdapter();
            }

            /** \brief \copybrief Pylon::IPylonDevice::DestroyEventAdapter()

            \copydetails Pylon::IPylonDevice::DestroyEventAdapter()
            */
            void DestroyEventAdapter( IEventAdapter* pAdapter )
            {
                CheckDevicePtr();
                m_pDevice->DestroyEventAdapter( pAdapter );
            }

            /** \brief \copybrief Pylon::IPylonDevice::CreateSelfReliantChunkParser()

            \copydetails Pylon::IPylonDevice::CreateSelfReliantChunkParser()
            */
            virtual ISelfReliantChunkParser* CreateSelfReliantChunkParser()
            {
                CheckDevicePtr();
                return m_pDevice->CreateSelfReliantChunkParser();
            }

            /** \brief \copybrief Pylon::IPylonDevice::DestroySelfReliantChunkParser()

            \copydetails Pylon::IPylonDevice::DestroySelfReliantChunkParser()
            */
            virtual void DestroySelfReliantChunkParser( ISelfReliantChunkParser* pChunkParser )
            {
                CheckDevicePtr();
                m_pDevice->DestroySelfReliantChunkParser( pChunkParser );
            }

            /** \brief \copybrief Pylon::IPylonDevice::RegisterRemovalCallback()

            \copydetails Pylon::IPylonDevice::RegisterRemovalCallback()
            */
            DeviceCallbackHandle RegisterRemovalCallback( DeviceCallback& d )
            {
                CheckDevicePtr();
                return m_pDevice->RegisterRemovalCallback( d );
            }

            /** \brief \copybrief Pylon::IPylonDevice::DeregisterRemovalCallback()

            \copydetails Pylon::IPylonDevice::DeregisterRemovalCallback()
            */
            bool DeregisterRemovalCallback( DeviceCallbackHandle h )
            {
                CheckDevicePtr();
                return m_pDevice->DeregisterRemovalCallback( h );
            }

            // \}


        protected:
            void CheckDevicePtr() const
            {
                if (NULL == m_pDevice)
                {
                    throw LOGICAL_ERROR_EXCEPTION( "The camera class is not attached to a IPylonDevice" );
                }
            }

            IPylonDevice* m_pDevice;
            bool m_hasOwnership;
        };


        //**************************************************************************************************
        // CPylonDeviceProxyT implementation
        //**************************************************************************************************

        template<class TCameraParams>
        inline CPylonDeviceProxyT<TCameraParams>::CPylonDeviceProxyT( void )
            : m_pDevice( NULL )
            , m_hasOwnership( false )
        {
        }

        template<class TCameraParams>
        inline CPylonDeviceProxyT<TCameraParams>::CPylonDeviceProxyT( IPylonDevice* pDevice, bool takeOwnership )
            : m_pDevice( NULL )
            , m_hasOwnership( false )
        {
            Attach( pDevice, takeOwnership );
        }

        template<class TCameraParams>
        inline CPylonDeviceProxyT<TCameraParams>::~CPylonDeviceProxyT( void )
        {
            if (HasOwnership() && IsAttached())
            {
                CTlFactory::GetInstance().DestroyDevice( m_pDevice );
            }
        }

        template<class TCameraParams>
        inline void CPylonDeviceProxyT<TCameraParams>::Attach( IPylonDevice* pDevice, bool takeOwnership )
        {
            if (IsAttached())
            {
                throw LOGICAL_ERROR_EXCEPTION( "Object is already attached to a pylon device" );
            }

            if (NULL == pDevice)
            {
                throw LOGICAL_ERROR_EXCEPTION( "Tried to attach a NULL pointer as device" );
            }

            TCameraParams::_Initialize( pDevice->GetNodeMap() );

            m_pDevice = pDevice;
            m_hasOwnership = takeOwnership;
        }

        template<class TCameraParams>
        inline bool CPylonDeviceProxyT<TCameraParams>::IsAttached() const
        {
            return NULL != m_pDevice;
        }

        template<class TCameraParams>
        inline bool CPylonDeviceProxyT<TCameraParams>::HasOwnership() const
        {
            return m_hasOwnership;
        }

        template<class TCameraParams>
        inline IPylonDevice* CPylonDeviceProxyT<TCameraParams>::GetDevice() const
        {
            return m_pDevice;
        }


    } // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif
