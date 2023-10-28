//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Pylon generic event grabber interface declaration
*/


#ifndef __PYLON_EVENTGRABBERPROXY__H__
#define __PYLON_EVENTGRABBERPROXY__H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


#include <Base/GCException.h>
#include "EventGrabber.h"
#include "NodeMapProxy.h"


//! Low Level API: Macro to define a custom Node map proxy
#define PYLON_DEFINE_EVENTGRABBER(ClassName, BaseClass) \
    class ClassName : public BaseClass \
    { \
    public: \
        /** \name Construction */ \
        /*@{*/ \
        /** \brief \copybrief Pylon::CEventGrabberProxyT::CEventGrabberProxyT()
            \copydetails Pylon::CEventGrabberProxyT::CEventGrabberProxyT()
        */ \
            ClassName() \
        { \
        } \
        /** \brief \copybrief Pylon::CEventGrabberProxyT::CEventGrabberProxyT(Pylon::IEventGrabber*)
            \copydetails Pylon::CEventGrabberProxyT::CEventGrabberProxyT(Pylon::IEventGrabber*)
        */ \
            ClassName( Pylon::IEventGrabber* pEventGrabber ) : BaseClass( pEventGrabber ) \
        { \
        } \
            /*@}*/ \
    };


    namespace Pylon
    {
        //**************************************************************************************************
        //! Low Level API: The event grabber class with parameter access methods
        /**
        This is the base class for pylon event grabber providing access to configuration parameters.
        \see \ref configuringcameras

        \tparam TParams  The specific parameter class (auto generated from the parameter xml file)
        \ingroup Pylon_LowLevelApi
        */
        //**************************************************************************************************
        template<class TParams>
        class CEventGrabberProxyT : public CNodeMapProxyT<TParams>
        {
        public:
            //! \name Construction
            // \{

            //! Creates a CEventGrabberProxyT object that is not attached to a pylon stream grabber. Use the Attach() method to attach the pylon event grabber.
            CEventGrabberProxyT();

            //! Creates a CEventGrabberProxyT object and attaches it to a pylon event grabber.
            CEventGrabberProxyT( Pylon::IEventGrabber* );

            //! Destructor
            virtual ~CEventGrabberProxyT();

            //\}

        private:
            //! \name Assignment and copying is not supported
            // \{
            CEventGrabberProxyT( const CEventGrabberProxyT& );
            CEventGrabberProxyT& operator=( const CEventGrabberProxyT& );
            // \}


        public:
            //! \name Some smart pointer functionality
            // \{

            //! Attach a pylon event grabber
            virtual void Attach( IEventGrabber* );

            //! Checks if a pylon stream grabber is attached
            virtual bool IsAttached() const;

            //! Returns the pylon event grabber interface pointer
            virtual IEventGrabber* GetEventGrabber() const;

            // \}


        public:
            //! \name Implementation of the IEventGrabber interface
            //! See Pylon::IEventGrabber for more details.
            // \{

            /** \brief \copybrief Pylon::IEventGrabber::Open()

                \copydetails Pylon::IEventGrabber::Open()
            */
            void Open()
            {
                CheckPtr();
                m_pEventGrabber->Open();
            }

            /** \brief \copybrief Pylon::IEventGrabber::Close()

                \copydetails Pylon::IEventGrabber::Close()
            */
            void Close()
            {
                CheckPtr();
                m_pEventGrabber->Close();
            }

            /** \brief \copybrief Pylon::IEventGrabber::IsOpen()

                 \copydetails Pylon::IEventGrabber::IsOpen()
            */
            bool IsOpen() const
            {
                CheckPtr();
                return m_pEventGrabber->IsOpen();
            }


            /** \brief \copybrief Pylon::IEventGrabber::RetrieveEvent()

                \copydetails Pylon::IEventGrabber::RetrieveEvent()
            */
            bool RetrieveEvent( EventResult& Result )
            {
                CheckPtr();
                return m_pEventGrabber->RetrieveEvent( Result );
            }

            /** \brief \copybrief Pylon::IEventGrabber::GetWaitObject()

                \copydetails Pylon::IEventGrabber::GetWaitObject()
            */
            WaitObject& GetWaitObject() const
            {
                CheckPtr();
                return m_pEventGrabber->GetWaitObject();
            }

            /** \brief \copybrief Pylon::IEventGrabber::GetNodeMap()

                \copydetails Pylon::IEventGrabber::GetNodeMap()
            */
            GENAPI_NAMESPACE::INodeMap* GetNodeMap()
            {
                CheckPtr();
                return m_pEventGrabber->GetNodeMap();
            }
            // \}


        protected:
            void CheckPtr() const
            {
                if (NULL == m_pEventGrabber)
                {
                    throw LOGICAL_ERROR_EXCEPTION( "The stream grabber class is not attached to a pylon event grabber" );
                }
            }

            IEventGrabber* m_pEventGrabber;
        };


        //**************************************************************************************************
        // CEventGrabberProxyT implementation
        //**************************************************************************************************


        template<class TParams>
        inline CEventGrabberProxyT<TParams>::CEventGrabberProxyT()
            : CNodeMapProxyT<TParams>(), m_pEventGrabber( NULL )
        {
        }

        template<class TParams>
        inline CEventGrabberProxyT<TParams>::CEventGrabberProxyT( IEventGrabber* pEventGrabber )
            : CNodeMapProxyT<TParams>(), m_pEventGrabber( NULL )
        {
            Attach( pEventGrabber );
        }

        template<class TParams>
        inline CEventGrabberProxyT<TParams>::~CEventGrabberProxyT( void )
        {
        }

        template<class TParams>
        inline void CEventGrabberProxyT<TParams>::Attach( IEventGrabber* pEventGrabber )
        {
            if (IsAttached())
            {
                throw LOGICAL_ERROR_EXCEPTION( "Object is already attached to a stream grabber" );
            }

            if (NULL == pEventGrabber)
            {
                throw LOGICAL_ERROR_EXCEPTION( "Tried to attach a NULL pointer as event grabber" );
            }

            CNodeMapProxyT<TParams>::Attach( pEventGrabber->GetNodeMap() );
            m_pEventGrabber = pEventGrabber;
        }

        template<class TParams>
        inline bool CEventGrabberProxyT<TParams>::IsAttached() const
        {
            return NULL != m_pEventGrabber;
        }

        template<class TParams>
        inline IEventGrabber* CEventGrabberProxyT<TParams>::GetEventGrabber() const
        {
            return m_pEventGrabber;
        }

    } // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif
