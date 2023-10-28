//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Template for device specific instant camera class.
*/

#ifndef INCLUDED_DEVICESPECIFICINSTANTCAMERA_H_4510266
#define INCLUDED_DEVICESPECIFICINSTANTCAMERA_H_4510266

#include <pylon/stdinclude.h>
#include <pylon/InstantCamera.h>
#include <pylon/private/DeviceSpecificConfigurationEventHandlerTie.h>
#include <pylon/private/DeviceSpecificImageEventHandlerTie.h>
#include <pylon/private/DeviceSpecificCameraEventHandlerTie.h>
#include <pylon/Platform.h>


//! Macro for defining a custom instant camera class.
#define PYLON_DEFINE_INSTANT_CAMERA(ClassName, BaseClass) \
    PYLON_6_0_DEPRECATED("Use CBaslerUniversalInstantCamera") \
    class ClassName : public BaseClass \
    { \
    public: \
        /*! \copybrief CInstantCamera::CInstantCamera()
            \copydetails CInstantCamera::CInstantCamera()
        */ \
            ClassName() \
        { \
        } \
        /*! \copybrief CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
            \copydetails CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
        */ \
            ClassName( IPylonDevice* pDevice, ECleanup cleanupProcedure = Cleanup_Delete ) : BaseClass( pDevice, cleanupProcedure ) \
        { \
        } \
        /*! \copybrief CInstantCamera::~CInstantCamera
            \copydetails CInstantCamera::~CInstantCamera
        */ \
            ~ClassName() \
        { \
            Attach( NULL ); \
            InternalShutdownEventHandlers(); \
        } \
    protected: \
            /* Create device specific grab result data. This is subject to change without notice */ \
            virtual CGrabResultData* CreateDeviceSpecificGrabResultData() \
        { \
            return new GrabResultData_t(); \
        } \
    };

    namespace Pylon
    {
        /*!
        \class  CDeviceSpecificInstantCameraT
        \brief  Implementation Detail: Header only implementation class for creating device specific Instant Camera classes.
        */

        template <typename CameraTraitsT>
        class CDeviceSpecificInstantCameraT : public CInstantCamera, public CameraTraitsT::CameraParams_t, public CameraTraitsT
        {
        public:
            /*!
                \copybrief Pylon::CInstantCamera::CInstantCamera()
                \copydetails Pylon::CInstantCamera::CInstantCamera()
            */
            CDeviceSpecificInstantCameraT();

            /*!
                \copybrief Pylon::CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
                \copydetails Pylon::CInstantCamera::CInstantCamera( IPylonDevice* , ECleanup )
            */
            CDeviceSpecificInstantCameraT( IPylonDevice* pDevice, ECleanup cleanupProcedure = Cleanup_Delete );

            /*!
                \copybrief Pylon::CInstantCamera::~CInstantCamera()
                \copydetails Pylon::CInstantCamera::~CInstantCamera()
            */
            virtual ~CDeviceSpecificInstantCameraT();

            /*
                \copybrief Pylon::CInstantCamera::Attach
                \copydetails Pylon::CInstantCamera::Attach
            */
            virtual void Attach( IPylonDevice* pDevice, ECleanup cleanupProcedure = Cleanup_Delete );

            /*
                \copybrief Pylon::CInstantCamera::DestroyDevice
                \copydetails Pylon::CInstantCamera::DestroyDevice
            */
            virtual void DestroyDevice();

            /*
                \copybrief Pylon::CInstantCamera::DetachDevice
                \copydetails Pylon::CInstantCamera::DetachDevice
            */
            virtual IPylonDevice* DetachDevice();



            /*
                \copybrief Pylon::CInstantCamera::Open
                \copydetails Pylon::CInstantCamera::Open
            */
            virtual void Open();

            /*
                \copybrief Pylon::CInstantCamera::Close
                \copydetails Pylon::CInstantCamera::Close
            */
            virtual void Close();



            /*!
                \copybrief Pylon::CInstantCamera::RetrieveResult
                \copydetails Pylon::CInstantCamera::RetrieveResult
            */
            virtual bool RetrieveResult( unsigned int timeoutMs, typename CameraTraitsT::GrabResultPtr_t& grabResult, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException );

            // Also available
            using CInstantCamera::RetrieveResult;

            /*!
                \copybrief Pylon::CInstantCamera::GrabOne
                \copydetails Pylon::CInstantCamera::GrabOne
            */
            virtual bool GrabOne( unsigned int timeoutMs, typename CameraTraitsT::GrabResultPtr_t& grabResult, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException );

            // Also available
            using CInstantCamera::GrabOne;



            /*!
                \copybrief Pylon::CInstantCamera::RegisterConfiguration( CConfigurationEventHandler*, ERegistrationMode, ECleanup)
                \copydetails Pylon::CInstantCamera::RegisterConfiguration( CConfigurationEventHandler*, ERegistrationMode, ECleanup)
            */
            virtual void RegisterConfiguration( typename CameraTraitsT::ConfigurationEventHandler_t* pConfigurator, ERegistrationMode mode, ECleanup cleanupProcedure );

            // Also available
            using CInstantCamera::RegisterConfiguration;

            /*!
                \copybrief Pylon::CInstantCamera::DeregisterConfiguration( CConfigurationEventHandler*)
                \copydetails Pylon::CInstantCamera::DeregisterConfiguration( CConfigurationEventHandler*)
            */
            virtual bool DeregisterConfiguration( typename CameraTraitsT::ConfigurationEventHandler_t* configurator );

            // Also available
            using CInstantCamera::DeregisterConfiguration;



            /*!
                \copybrief Pylon::CInstantCamera::RegisterImageEventHandler( CImageEventHandler*, ERegistrationMode, ECleanup)
                \copydetails Pylon::CInstantCamera::RegisterImageEventHandler( CImageEventHandler*, ERegistrationMode, ECleanup)
            */
            virtual void RegisterImageEventHandler( typename CameraTraitsT::ImageEventHandler_t* pImageEventHandler, ERegistrationMode mode, ECleanup cleanupProcedure );

            // Also available
            using CInstantCamera::RegisterImageEventHandler;

            /*!
                \copybrief Pylon::CInstantCamera::DeregisterImageEventHandler( CImageEventHandler*)
                \copydetails Pylon::CInstantCamera::DeregisterImageEventHandler( CImageEventHandler*)
            */
            virtual bool DeregisterImageEventHandler( typename CameraTraitsT::ImageEventHandler_t* imageEventHandler );

            // Also available
            using CInstantCamera::DeregisterImageEventHandler;



            /*!
                \copybrief Pylon::CInstantCamera::RegisterCameraEventHandler( CCameraEventHandler*, const String_t&, intptr_t, ERegistrationMode, ECleanup, ECameraEventAvailability)
                \copydetails Pylon::CInstantCamera::RegisterCameraEventHandler( CCameraEventHandler*, const String_t&, intptr_t, ERegistrationMode, ECleanup, ECameraEventAvailability)
            */
            virtual void RegisterCameraEventHandler( typename CameraTraitsT::CameraEventHandler_t* pCameraEventHandler, const String_t& nodeName, intptr_t userProvidedId, ERegistrationMode mode, ECleanup cleanupProcedure, ECameraEventAvailability availability = CameraEventAvailability_Mandatory );

            // Also available
            using CInstantCamera::RegisterCameraEventHandler;

            /*!
                \copybrief Pylon::CInstantCamera::DeregisterCameraEventHandler( CCameraEventHandler*, const String_t&)
                \copydetails Pylon::CInstantCamera::DeregisterCameraEventHandler( CCameraEventHandler*, const String_t&)
            */
            virtual bool DeregisterCameraEventHandler( typename CameraTraitsT::CameraEventHandler_t* cameraEventHandler, const String_t& nodeName );

            // Also available
            using CInstantCamera::DeregisterCameraEventHandler;



            /*!
                \copybrief Pylon::CInstantCamera::GetDeviceInfo
                \copydetails Pylon::CInstantCamera::GetDeviceInfo
            */
            virtual const typename CameraTraitsT::DeviceInfo_t& GetDeviceInfo() const;


            /*!
            \brief Provides access to the transport layer parameters of the attached %Pylon Device.
            \return Reference to the transport layer parameters.
            \pre A %Pylon Device is attached.
            \error
                The Instant Camera object is still valid after error.
            \threading
                This method is synchronized using the lock provided by GetLock().
            */
            virtual typename CameraTraitsT::TlParams_t& GetTLParams();


            /*!
            \brief Provides access to the stream grabber parameters of the attached %Pylon Device.
            \return Reference to the stream grabber parameters.
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
            virtual typename CameraTraitsT::StreamGrabberParams_t& GetStreamGrabberParams();


            /*!
            \brief Provides access to the event grabber parameters of the attached %Pylon Device.
            \return Reference to the event grabber parameters.
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
            virtual typename CameraTraitsT::EventGrabberParams_t& GetEventGrabberParams();

            // Types used by camera--------------------------------------------------

            // Overload CInstantCamera type definitions
            typedef typename CameraTraitsT::InstantCamera_t InstantCamera_t;
            typedef typename CameraTraitsT::IPylonDevice_t IPylonDevice_t;
            typedef typename CameraTraitsT::DeviceInfo_t DeviceInfo_t;
            typedef typename CameraTraitsT::ConfigurationEventHandler_t ConfigurationEventHandler_t;
            typedef typename CameraTraitsT::ImageEventHandler_t ImageEventHandler_t;
            typedef typename CameraTraitsT::CameraEventHandler_t CameraEventHandler_t;
            typedef typename CameraTraitsT::GrabResultData_t GrabResultData_t;
            typedef typename CameraTraitsT::GrabResultPtr_t GrabResultPtr_t;

        protected:
            typename CameraTraitsT::TlParams_t* m_pTlParams;
            typename CameraTraitsT::StreamGrabberParams_t* m_pStreamGrabberParams;
            typename CameraTraitsT::EventGrabberParams_t* m_pEventGrabberParams;
        };






        // Implementation ----------------------------------------------------------

        template <typename CameraTraitsT>
        CDeviceSpecificInstantCameraT<CameraTraitsT>::CDeviceSpecificInstantCameraT()
            : m_pTlParams( new typename CameraTraitsT::TlParams_t() )
            , m_pStreamGrabberParams( new typename CameraTraitsT::StreamGrabberParams_t() )
            , m_pEventGrabberParams( new typename CameraTraitsT::EventGrabberParams_t() )
        {
        }


        template <typename CameraTraitsT>
        CDeviceSpecificInstantCameraT<CameraTraitsT>::CDeviceSpecificInstantCameraT( IPylonDevice* pDevice, ECleanup cleanupProcedure )
            : m_pTlParams( new typename CameraTraitsT::TlParams_t() )
            , m_pStreamGrabberParams( new typename CameraTraitsT::StreamGrabberParams_t() )
            , m_pEventGrabberParams( new typename CameraTraitsT::EventGrabberParams_t() )
        {
            this->Attach( pDevice, cleanupProcedure );
        }

        template <typename CameraTraitsT>
        CDeviceSpecificInstantCameraT<CameraTraitsT>::~CDeviceSpecificInstantCameraT()
        {
            delete m_pTlParams;
            m_pTlParams = NULL;
            delete m_pStreamGrabberParams;
            m_pStreamGrabberParams = NULL;
            delete m_pEventGrabberParams;
            m_pEventGrabberParams = NULL;
        }

        template <typename CameraTraitsT>
        void CDeviceSpecificInstantCameraT<CameraTraitsT>::Attach( IPylonDevice* pDevice, ECleanup cleanupProcedure )
        {
            // Check whether device type matches camera type.
            if (pDevice)
            {
                if ( (dynamic_cast<typename CameraTraitsT::IPylonDevice_t*>(pDevice) == NULL)
                     || (this->HasSpecificDeviceClass() && (pDevice->GetDeviceInfo().GetDeviceClass() != this->DeviceClass()))
                     )
                {
                    throw LOGICAL_ERROR_EXCEPTION( "The attached pylon device type cannot be used with this type of camera class." );
                }
            }

            AutoLock lock( CInstantCamera::GetLock() );
            // Attach the device.
            CInstantCamera::Attach( pDevice, cleanupProcedure );

            // Update camera parameters.
            if (CInstantCamera::IsPylonDeviceAttached())
            {
                // Set camera parameters.
                CameraTraitsT::CameraParams_t::_Initialize( pDevice->GetNodeMap() );
                // Set TL parameters.
                m_pTlParams->Attach( &CInstantCamera::GetTLNodeMap(), true );
            }
            else
            {
                // Reset camera parameters.
                CameraTraitsT::CameraParams_t::_Initialize( &CInstantCamera::GetEmptyNodeMap() );
                // Reset TL parameters.
                m_pTlParams->Attach( &CInstantCamera::GetEmptyNodeMap(), true );
            }
        }

        template <typename CameraTraitsT>
        void CDeviceSpecificInstantCameraT<CameraTraitsT>::DestroyDevice()
        {
            AutoLock lock( CInstantCamera::GetLock() );

            // If a device is attached
            if (CInstantCamera::IsPylonDeviceAttached())
            {
                // Reset camera parameters.
                CameraTraitsT::CameraParams_t::_Initialize( &CInstantCamera::GetEmptyNodeMap() );
                // Reset TL parameters.
                m_pTlParams->Attach( &CInstantCamera::GetEmptyNodeMap(), true );
                // Perform destroy operation.
                CInstantCamera::DestroyDevice();
            }
        }

        template <typename CameraTraitsT>
        IPylonDevice* CDeviceSpecificInstantCameraT<CameraTraitsT>::DetachDevice()
        {
            AutoLock lock( CInstantCamera::GetLock() );
            IPylonDevice* pDevice = NULL;

            // If a device is attached
            if (CInstantCamera::IsPylonDeviceAttached())
            {
                // Reset camera parameters.
                CameraTraitsT::CameraParams_t::_Initialize( &CInstantCamera::GetEmptyNodeMap() );
                // Reset TL parameters.
                m_pTlParams->Attach( &CInstantCamera::GetEmptyNodeMap(), true );
                // Perform detach operation.
                pDevice = CInstantCamera::DetachDevice();
            }
            return pDevice;
        }

        template <typename CameraTraitsT>
        void CDeviceSpecificInstantCameraT<CameraTraitsT>::Open()
        {
            AutoLock lock( CInstantCamera::GetLock() );
            // Perform open operation.
            CInstantCamera::Open();
            // Set stream grabber parameters.
            m_pStreamGrabberParams->Attach( &CInstantCamera::GetStreamGrabberNodeMap(), true );
            // Set event grabber parameters.
            m_pEventGrabberParams->Attach( &CInstantCamera::GetEventGrabberNodeMap(), true );
        }

        template <typename CameraTraitsT>
        void CDeviceSpecificInstantCameraT<CameraTraitsT>::Close()
        {
            AutoLock lock( CInstantCamera::GetLock() );
            // Reset stream grabber parameters.
            m_pStreamGrabberParams->Attach( &CInstantCamera::GetEmptyNodeMap(), true );
            // Reset event grabber parameters.
            m_pEventGrabberParams->Attach( &CInstantCamera::GetEmptyNodeMap(), true );
            // Perform close operation.
            CInstantCamera::Close();
        }



        template <typename CameraTraitsT>
        bool CDeviceSpecificInstantCameraT<CameraTraitsT>::RetrieveResult( unsigned int timeoutMs, typename CameraTraitsT::GrabResultPtr_t& grabResult, ETimeoutHandling timeoutHandling )
        {
            //Release the grab result
            grabResult.Release();
            // Use basic grab result.
            CGrabResultPtr grabResultLocal;
            // Call basic RetrieveResult.
            CInstantCamera::RetrieveResult( timeoutMs, grabResultLocal, timeoutHandling );
            // Convert.
            grabResult = grabResultLocal;
            // Returns true if grabResultLocal is valid and the conversion to the device specific grab result type has been successful.
            return grabResult.IsValid();
        }


        template <typename CameraTraitsT>
        bool CDeviceSpecificInstantCameraT<CameraTraitsT>::GrabOne( unsigned int timeoutMs, typename CameraTraitsT::GrabResultPtr_t& grabResult, ETimeoutHandling timeoutHandling )
        {
            //Release the grab result
            grabResult.Release();
            // Use basic grab result.
            CGrabResultPtr grabResultLocal;
            // Call basic GrabOne.
            CInstantCamera::GrabOne( timeoutMs, grabResultLocal, timeoutHandling );
            // Convert.
            grabResult = grabResultLocal;
            // Returns true if grabResultLocal is valid and the conversion to the device specific grab result type has been successful.
            return grabResult.IsValid();
        }



        template <typename CameraTraitsT>
        void CDeviceSpecificInstantCameraT<CameraTraitsT>::RegisterConfiguration( typename CameraTraitsT::ConfigurationEventHandler_t* pConfigurator, ERegistrationMode mode, ECleanup cleanupProcedure )
        {
            typedef CDeviceSpecificConfigurationEventHandlerTie< typename CameraTraitsT::InstantCamera_t, typename CameraTraitsT::ConfigurationEventHandler_t> TieT;
            InternalRegisterConfiguration(
                pConfigurator ? new TieT( pConfigurator, cleanupProcedure == Cleanup_Delete ) : NULL,
                mode,
                Cleanup_Delete, // demand deletion of TieT
                pConfigurator ? &pConfigurator->DebugGetEventHandlerRegistrationCount() : NULL );
        }

        template <typename CameraTraitsT>
        bool CDeviceSpecificInstantCameraT<CameraTraitsT>::DeregisterConfiguration( typename CameraTraitsT::ConfigurationEventHandler_t* pConfigurator )
        {
            return InternalDeregisterConfiguration( pConfigurator ? &pConfigurator->DebugGetEventHandlerRegistrationCount() : NULL );
        }


        template <typename CameraTraitsT>
        void CDeviceSpecificInstantCameraT<CameraTraitsT>::RegisterImageEventHandler( typename CameraTraitsT::ImageEventHandler_t* pImageEventHandler, ERegistrationMode mode, ECleanup cleanupProcedure )
        {
            typedef CDeviceSpecificImageEventHandlerTie< typename CameraTraitsT::InstantCamera_t, typename CameraTraitsT::ImageEventHandler_t> TieT;
            InternalRegisterImageEventHandler(
                pImageEventHandler ? new TieT( pImageEventHandler, cleanupProcedure == Cleanup_Delete ) : NULL,
                mode,
                Cleanup_Delete, // demand deletion of TieT
                pImageEventHandler ? &pImageEventHandler->DebugGetEventHandlerRegistrationCount() : NULL );
        }

        template <typename CameraTraitsT>
        bool CDeviceSpecificInstantCameraT<CameraTraitsT>::DeregisterImageEventHandler( typename CameraTraitsT::ImageEventHandler_t* pImageEventHandler )
        {
            return InternalDeregisterImageEventHandler( pImageEventHandler ? &pImageEventHandler->DebugGetEventHandlerRegistrationCount() : NULL );
        }


        template <typename CameraTraitsT>
        void CDeviceSpecificInstantCameraT<CameraTraitsT>::RegisterCameraEventHandler(
            typename CameraTraitsT::CameraEventHandler_t* pCameraEventHandler,
            const String_t& nodeName,
            intptr_t userProvidedId,
            ERegistrationMode mode,
            ECleanup cleanupProcedure,
            ECameraEventAvailability availability )
        {
            typedef CDeviceSpecificCameraEventHandlerTie< typename CameraTraitsT::InstantCamera_t, typename CameraTraitsT::CameraEventHandler_t> TieT;
            InternalRegisterCameraEventHandler(
                pCameraEventHandler ? new TieT( pCameraEventHandler, cleanupProcedure == Cleanup_Delete ) : NULL,
                nodeName, userProvidedId, mode,
                Cleanup_Delete, // demand deletion of TieT
                availability,
                pCameraEventHandler ? &pCameraEventHandler->DebugGetEventHandlerRegistrationCount() : NULL );
        }

        template <typename CameraTraitsT>
        bool CDeviceSpecificInstantCameraT<CameraTraitsT>::DeregisterCameraEventHandler( typename CameraTraitsT::CameraEventHandler_t* pCameraEventHandler, const String_t& nodeName )
        {
            return InternalDeregisterCameraEventHandler( pCameraEventHandler ? &pCameraEventHandler->DebugGetEventHandlerRegistrationCount() : NULL, nodeName );
        }


        template <typename CameraTraitsT>
        const typename CameraTraitsT::DeviceInfo_t& CDeviceSpecificInstantCameraT<CameraTraitsT>::GetDeviceInfo() const
        {
            return static_cast<const typename CameraTraitsT::DeviceInfo_t&>(CInstantCamera::GetDeviceInfo());
        }

        template <typename CameraTraitsT>
        typename CameraTraitsT::TlParams_t& CDeviceSpecificInstantCameraT<CameraTraitsT>::GetTLParams()
        {
            AutoLock lock( CInstantCamera::GetLock() );
            // Enforce preconditions.
            CInstantCamera::GetTLNodeMap();
            return *m_pTlParams;
        }

        template <typename CameraTraitsT>
        typename CameraTraitsT::StreamGrabberParams_t& CDeviceSpecificInstantCameraT<CameraTraitsT>::GetStreamGrabberParams()
        {
            AutoLock lock( CInstantCamera::GetLock() );
            // Enforce preconditions.
            CInstantCamera::GetStreamGrabberNodeMap();
            return *m_pStreamGrabberParams;
        }

        template <typename CameraTraitsT>
        typename CameraTraitsT::EventGrabberParams_t& CDeviceSpecificInstantCameraT<CameraTraitsT>::GetEventGrabberParams()
        {
            AutoLock lock( CInstantCamera::GetLock() );
            // Enforce preconditions.
            CInstantCamera::GetEventGrabberNodeMap();
            return *m_pEventGrabberParams;
        }

    } // namespace Pylon

#endif /* INCLUDED_DEVICESPECIFICINSTANTCAMERA_H_4510266 */
