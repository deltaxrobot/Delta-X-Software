//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Contains an adapter class for device specific camera event handlers.
*/

#ifndef INCLUDED_DEVICESPECIFICCAMERAEVENTHANDLERTIE_H_4759899
#define INCLUDED_DEVICESPECIFICCAMERAEVENTHANDLERTIE_H_4759899

#include <pylon/CameraEventHandler.h>
#include <pylon/stdinclude.h>

namespace Pylon
{
    /*!
    \class  CDeviceSpecificCameraEventHandlerTie
    \brief  Implementation Detail: Adapter for device specific camera event handlers.
    */
    template <typename DeviceSpecificCameraT, typename InterfaceT>
    class CDeviceSpecificCameraEventHandlerTie : public CCameraEventHandler
    {
    public:
        CDeviceSpecificCameraEventHandlerTie( InterfaceT* ptr, bool isCleanupDelete )
            : m_ptr( ptr )
            , m_isCleanupDelete( isCleanupDelete )
        {
        }

        ~CDeviceSpecificCameraEventHandlerTie()
        {
        }

        virtual void OnCameraEvent( CInstantCamera& camera, intptr_t userProvidedId, GENAPI_NAMESPACE::INode* pNode )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnCameraEvent( static_cast<DeviceSpecificCameraT&>(camera), userProvidedId, pNode );
        }

        virtual void OnCameraEventHandlerRegistered( CInstantCamera& camera, const String_t& nodeName, intptr_t userProvidedId )
        {
            PYLON_ASSERT2( dynamic_cast<DeviceSpecificCameraT*>(&camera) != NULL, "Unexpected camera type passed." );
            m_ptr->OnCameraEventHandlerRegistered( static_cast<DeviceSpecificCameraT&>(camera), nodeName, userProvidedId );
        }

        virtual void OnCameraEventHandlerDeregistered( CInstantCamera& camera, const String_t& nodeName, intptr_t userProvidedId )
        {
            m_ptr->OnCameraEventHandlerDeregistered( static_cast<DeviceSpecificCameraT&>(camera), nodeName, userProvidedId );
        }

        virtual void DestroyCameraEventHandler()
        {
            try
            {
                // destroy only when demanded
                if (m_isCleanupDelete)
                {
                    m_ptr->DestroyCameraEventHandler();
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

#endif /* INCLUDED_DEVICESPECIFICCAMERAEVENTHANDLERTIE_H_4759899 */
