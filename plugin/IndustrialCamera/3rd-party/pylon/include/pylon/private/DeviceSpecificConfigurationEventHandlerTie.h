//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Contains an adapter class for device specific configuration event handlers.
*/

#ifndef INCLUDED_DEVICESPECIFICCONFIGURATIONEVENTHANDLERTIE_H_5249532
#define INCLUDED_DEVICESPECIFICCONFIGURATIONEVENTHANDLERTIE_H_5249532

#include <pylon/ConfigurationEventHandler.h>
#include <pylon/stdinclude.h>

namespace Pylon
{
    /*!
    \class  CDeviceSpecificConfigurationEventHandlerTie
    \brief  Implementation Detail: Adapter for device specific configuration event handlers.
    */
    template <typename DeviceSpecificCameraT, typename InterfaceT>
    class CDeviceSpecificConfigurationEventHandlerTie : public CConfigurationEventHandler
    {
    public:
        CDeviceSpecificConfigurationEventHandlerTie( InterfaceT* ptr, bool isCleanupDelete )
            : m_ptr( ptr )
            , m_isCleanupDelete( isCleanupDelete )
        {
        }

        ~CDeviceSpecificConfigurationEventHandlerTie()
        {
        }


        void OnAttach( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnAttach( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnAttached( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnAttached( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnOpen( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnOpen( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnOpened( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnOpened( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnGrabStart( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnGrabStart( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnGrabStarted( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnGrabStarted( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnGrabStop( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnGrabStop( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnGrabStopped( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnGrabStopped( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnClose( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnClose( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnClosed( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnClosed( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnDestroy( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnDestroy( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnDestroyed( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnDestroyed( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnDetach( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnDetach( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnDetached( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnDetached( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        void OnGrabError( CInstantCamera& camera, const char* errorMessage )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnGrabError( dynamic_cast<DeviceSpecificCameraT&>(camera), errorMessage );
        }

        void OnCameraDeviceRemoved( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnCameraDeviceRemoved( dynamic_cast<DeviceSpecificCameraT&>(camera) );
        }

        virtual void OnConfigurationRegistered( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnConfigurationRegistered( static_cast<DeviceSpecificCameraT&>(camera) );
        }

        virtual void OnConfigurationDeregistered( CInstantCamera& camera )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnConfigurationDeregistered( static_cast<DeviceSpecificCameraT&>(camera) );
        }

        virtual void DestroyConfiguration()
        {
            try
            {
                // destroy only when demanded
                if (m_isCleanupDelete)
                {
                    m_ptr->DestroyConfiguration();
                }
                m_ptr = NULL;
            }
            catch (...)
            {
                delete this;
                m_ptr = NULL;
                throw;
            }
            delete this;
        }

    private:
        InterfaceT* m_ptr;
        bool m_isCleanupDelete;
    };
}

#endif /* INCLUDED_DEVICESPECIFICCONFIGURATIONEVENTHANDLERTIE_H_5249532 */
