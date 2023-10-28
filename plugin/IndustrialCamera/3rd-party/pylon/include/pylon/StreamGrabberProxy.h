//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Pylon generic stream grabber interface declaration
*/


#ifndef __PYLON_STREAMGRABBERPROXY__H__
#define __PYLON_STREAMGRABBERPROXY__H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <Base/GCException.h>
#include <pylon/StreamGrabber.h>
#include "NodeMapProxy.h"


//! Macro to define a custom Node map proxy
#define PYLON_DEFINE_STREAMGRABBER(ClassName, BaseClass) \
    class ClassName : public BaseClass \
    { \
    public: \
        /** \name Construction */ \
        /*@{*/ \
        /** \brief \copybrief Pylon::CStreamGrabberProxyT::CStreamGrabberProxyT()
            \copydetails Pylon::CStreamGrabberProxyT::CStreamGrabberProxyT()
        */ \
            ClassName() \
        { \
        } \
              /** \brief \copybrief Pylon::CStreamGrabberProxyT::CStreamGrabberProxyT(Pylon::IStreamGrabber*)
              \copydetails Pylon::CStreamGrabberProxyT::CStreamGrabberProxyT(Pylon::IStreamGrabber*)
              */ \
            ClassName( IStreamGrabber* pStreamGrabber ) : BaseClass( pStreamGrabber ) \
        { \
        } \
            /*@}*/ \
    };


    namespace Pylon
    {
        //**************************************************************************************************
        //! Low Level API: The stream grabber class with parameter access methods
        /**
        This is the base class for pylon stream grabber providing access to configuration parameters.
        \see \ref configuringcameras

        \tparam TParams  The specific parameter class (auto generated from the parameter xml file)
        \ingroup Pylon_LowLevelApi
        */
        //**************************************************************************************************
        template<class TParams>
        class CStreamGrabberProxyT : public CNodeMapProxyT<TParams>
        {
        public:
            //! \name Construction
            // \{

            //! Creates a CStreamGrabberProxyT object that is not attached to a pylon stream grabber. Use the Attach() method to attach the pylon stream grabber.
            CStreamGrabberProxyT();

            //! Creates a CStreamGrabberProxyT object and attaches it to a pylon stream grabber.
            CStreamGrabberProxyT( Pylon::IStreamGrabber* );

            //! Destructor
            virtual ~CStreamGrabberProxyT();

            //\}


        private:
            //! \name Assignment and copying is not supported
            // \{
            CStreamGrabberProxyT( const CStreamGrabberProxyT& );
            CStreamGrabberProxyT& operator=( const CStreamGrabberProxyT& );
            // \}


        public:
            //! \name Some smart pointer functionality
            // \{

            //! Attach a pylon stream grabber
            virtual void Attach( IStreamGrabber* );

            //! Checks if a pylon stream grabber is attached
            virtual bool IsAttached() const;

            //! Returns the pylon stream grabber interface pointer
            virtual IStreamGrabber* GetStreamGrabber() const;

            // \}


        public:
            //! \name Implementation of the IStreamGrabber interface
            //! See Pylon::IStreamGrabber for more details.
            // \{

            /** \brief \copybrief Pylon::IStreamGrabber::Open()

                \copydetails Pylon::IStreamGrabber::Open()
            */
            void Open()
            {
                CheckPtr();
                m_pStreamGrabber->Open();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::Close()

                \copydetails Pylon::IStreamGrabber::Close()
            */
            void Close()
            {
                CheckPtr();
                m_pStreamGrabber->Close();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::IsOpen()

                \copydetails Pylon::IStreamGrabber::IsOpen()
            */
            bool IsOpen() const
            {
                CheckPtr();
                return m_pStreamGrabber->IsOpen();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::RegisterBuffer()

                \copydetails Pylon::IStreamGrabber::RegisterBuffer()
            */
            StreamBufferHandle RegisterBuffer( void* pBuffer, size_t bufferSize )
            {
                CheckPtr();
                return m_pStreamGrabber->RegisterBuffer( pBuffer, bufferSize );
            }

            /** \brief \copybrief Pylon::IStreamGrabber::DeregisterBuffer()

                \copydetails Pylon::IStreamGrabber::DeregisterBuffer()
            */
            const void* DeregisterBuffer( StreamBufferHandle hStreamBuffer )
            {
                CheckPtr();
                return m_pStreamGrabber->DeregisterBuffer( hStreamBuffer );
            }

            /** \brief \copybrief Pylon::IStreamGrabber::PrepareGrab()

                \copydetails Pylon::IStreamGrabber::PrepareGrab()
            */
            void PrepareGrab()
            {
                CheckPtr();
                m_pStreamGrabber->PrepareGrab();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::IsStartAndStopStreamingMandatory()

                \copydetails Pylon::IStreamGrabber::IsStartAndStopStreamingMandatory()
            */
            bool IsStartAndStopStreamingMandatory()
            {
                CheckPtr();
                return m_pStreamGrabber->IsStartAndStopStreamingMandatory();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::StartStreamingIfMandatory()

                \copydetails Pylon::IStreamGrabber::StartStreamingIfMandatory()
            */
            void StartStreamingIfMandatory()
            {
                CheckPtr();
                m_pStreamGrabber->StartStreamingIfMandatory();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::StopStreamingIfMandatory()

                \copydetails Pylon::IStreamGrabber::StopStreamingIfMandatory()
            */
            void StopStreamingIfMandatory()
            {
                CheckPtr();
                m_pStreamGrabber->StopStreamingIfMandatory();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::FinishGrab()

                \copydetails Pylon::IStreamGrabber::FinishGrab()
            */
            void FinishGrab()
            {
                CheckPtr();
                m_pStreamGrabber->FinishGrab();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::QueueBuffer()

                \copydetails Pylon::IStreamGrabber::QueueBuffer()
            */
            void QueueBuffer( StreamBufferHandle hStreamBuffer, const void* pContext = NULL )
            {
                CheckPtr();
                m_pStreamGrabber->QueueBuffer( hStreamBuffer, pContext );
            }

            /** \brief \copybrief Pylon::IStreamGrabber::FlushBuffersToOutput()

                \copydetails Pylon::IStreamGrabber::FlushBuffersToOutput()
            */
            void FlushBuffersToOutput()
            {
                CheckPtr();
                m_pStreamGrabber->FlushBuffersToOutput();
            }

            // undocumented, deprecated
            void CancelGrab()
            {
                CheckPtr();
                m_pStreamGrabber->FlushBuffersToOutput();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::RetrieveResult()

                \copydetails Pylon::IStreamGrabber::RetrieveResult()
            */
            bool RetrieveResult( GrabResult& Result )
            {
                CheckPtr();
                return m_pStreamGrabber->RetrieveResult( Result );
            }

            /** \brief \copybrief Pylon::IStreamGrabber::GetWaitObject()

                \copydetails Pylon::IStreamGrabber::GetWaitObject()
            */
            WaitObject& GetWaitObject() const
            {
                CheckPtr();
                return m_pStreamGrabber->GetWaitObject();
            }

            /** \brief \copybrief Pylon::IStreamGrabber::GetNodeMap()

            \copydetails Pylon::IStreamGrabber::GetNodeMap()
            */
            GENAPI_NAMESPACE::INodeMap* GetNodeMap()
            {
                CheckPtr();
                return m_pStreamGrabber->GetNodeMap();
            }

            // \}


        protected:
            void CheckPtr() const
            {
                if (NULL == m_pStreamGrabber)
                {
                    throw LOGICAL_ERROR_EXCEPTION( "The stream grabber class is not attached to a pylon stream grabber" );
                }
            }

            IStreamGrabber* m_pStreamGrabber;
        };


        //**************************************************************************************************
        // CStreamGrabberProxyT implementation
        //**************************************************************************************************

        template<class TParams>
        inline CStreamGrabberProxyT<TParams>::CStreamGrabberProxyT()
            : CNodeMapProxyT<TParams>(), m_pStreamGrabber( NULL )
        {
        }

        template<class TParams>
        inline CStreamGrabberProxyT<TParams>::CStreamGrabberProxyT( IStreamGrabber* pStreamGrabber )
            : CNodeMapProxyT<TParams>(), m_pStreamGrabber( NULL )
        {
            Attach( pStreamGrabber );
        }

        template<class TParams>
        inline CStreamGrabberProxyT<TParams>::~CStreamGrabberProxyT( void )
        {
        }

        template<class TParams>
        inline void CStreamGrabberProxyT<TParams>::Attach( IStreamGrabber* pStreamGrabber )
        {
            if (IsAttached())
            {
                throw LOGICAL_ERROR_EXCEPTION( "Object is already attached to a stream grabber" );
            }

            if (NULL == pStreamGrabber)
            {
                throw LOGICAL_ERROR_EXCEPTION( "Tried to attach a NULL pointer as stream grabber" );
            }

            CNodeMapProxyT<TParams>::Attach( pStreamGrabber->GetNodeMap() );
            m_pStreamGrabber = pStreamGrabber;
        }

        template<class TParams>
        inline bool CStreamGrabberProxyT<TParams>::IsAttached() const
        {
            return NULL != m_pStreamGrabber;
        }

        template<class TParams>
        inline IStreamGrabber* CStreamGrabberProxyT<TParams>::GetStreamGrabber() const
        {
            return m_pStreamGrabber;
        }

    } // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif
