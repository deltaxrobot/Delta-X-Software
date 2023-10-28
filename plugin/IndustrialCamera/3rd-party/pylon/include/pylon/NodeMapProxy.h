//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Pylon generic node map interface declaration

\ingroup PYLON_INTERNAL
*/


#ifndef __PYLON_NODEMAPROXY__H__
#define __PYLON_NODEMAPROXY__H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <Base/GCException.h>
#include <GenApi/INodeMap.h>
#include <GenApi/INode.h>

//! Macro to define a custom Node map proxy
#define PYLON_DEFINE_NODEMAP(ClassName, BaseClass) \
    class ClassName : public BaseClass \
    { \
    public: \
        /** \name Construction */ \
        /*@{*/ \
        /** \brief \copybrief Pylon::CNodeMapProxyT::CNodeMapProxyT()
        \copydetails Pylon::CNodeMapProxyT::CNodeMapProxyT()
        */ \
            ClassName() \
        { \
        } \
            /** \brief \copybrief Pylon::CNodeMapProxyT::CNodeMapProxyT(GenApi::INodeMap*)
            \copydetails Pylon::CNodeMapProxyT::CNodeMapProxyT(GenApi::INodeMap*)
            */ \
            ClassName( GENAPI_NAMESPACE::INodeMap* pNodeMap ) : BaseClass( pNodeMap ) \
        { \
        } \
            /*@}*/ \
    };


    namespace Pylon
    {
        //**************************************************************************************************
        //! Implementation Detail: This class wraps programming interfaces that are generated from %GenICam parameter description files to provide native parameter access.
        /**
        \see \ref configuringcameras

        \tparam TParams  The specific parameter class (auto generated from the parameter xml file)
        \ingroup PYLON_INTERNAL
        */
        //**************************************************************************************************
        template<class TParams>
        class CNodeMapProxyT : public TParams
        {
        public:
            //! \name Construction
            // \{

            //! Creates a CNodeMapProxyT object that is not attached to a node map. Use the Attach() method to attach the pylon node map.
            CNodeMapProxyT();

            //! Creates a CNodeMapProxyT object and attaches it to a pylon node map.
            CNodeMapProxyT( GENAPI_NAMESPACE::INodeMap* );

            //! Destructor
            virtual ~CNodeMapProxyT();

            //\}


        private:
            //! \name Assignment and copying is not supported
            // \{
            CNodeMapProxyT( const CNodeMapProxyT& );
            CNodeMapProxyT& operator=( const CNodeMapProxyT& );
            // \}


        public:
            //! \name Some smart pointer functionality
            // \{

            //! Attach a pylon node map
            virtual void Attach( GENAPI_NAMESPACE::INodeMap*, bool replace = false );

            //! Checks if a pylon node map is attached
            virtual bool IsAttached() const;

            //! Returns the pylon node map interface pointer
            virtual GENAPI_NAMESPACE::INodeMap* GetNodeMap() const;

            // \}


        public:
            //! \name Partial implementation of the INodeMap interface
            //! See GENAPI_NAMESPACE::INodeMap for more details
            // \{
            /** \brief \copybrief GenApi::INodeMap::GetNodes()

                \copydetails GenApi::INodeMap::GetNodes()
            */
            void GetNodes( GENAPI_NAMESPACE::NodeList_t& Nodes ) const
            {
                CheckNodeMapPtr();
                return m_pNodeMap->GetNodes( Nodes );
            }

            /** \brief \copybrief GenApi::INodeMap::GetNode()

            \copydetails GenApi::INodeMap::GetNode()
            */
            GENAPI_NAMESPACE::INode* GetNode( const GENICAM_NAMESPACE::gcstring& Name ) const
            {
                CheckNodeMapPtr();
                return m_pNodeMap->GetNode( Name );
            }

            /** \brief \copybrief GenApi::INodeMap::InvalidateNodes()

            \copydetails GenApi::INodeMap::InvalidateNodes()
            */
            void InvalidateNodes() const
            {
                CheckNodeMapPtr();
                m_pNodeMap->InvalidateNodes();
            }

            /** \brief \copybrief GenApi::INodeMap::Poll()

            \copydetails GenApi::INodeMap::Poll()
            */
            void Poll( int64_t ElapsedTime )
            {
                CheckNodeMapPtr();
                m_pNodeMap->Poll( ElapsedTime );
            }

            // \}


        protected:
            void CheckNodeMapPtr() const
            {
                if (NULL == m_pNodeMap)
                {
                    throw LOGICAL_ERROR_EXCEPTION( "The object is not attached to a NodeMap" );
                }
            }

            GENAPI_NAMESPACE::INodeMap* m_pNodeMap;
        };


        //**************************************************************************************************
        // CPylonDeviceProxyT implementation
        //**************************************************************************************************


        template<class TParams>
        inline CNodeMapProxyT<TParams>::CNodeMapProxyT()
            : m_pNodeMap( NULL )
        {
        }

        template<class TParams>
        inline CNodeMapProxyT<TParams>::CNodeMapProxyT( GENAPI_NAMESPACE::INodeMap* pNodeMap )
            : m_pNodeMap( NULL )
        {
            Attach( pNodeMap );
        }

        template<class TParams>
        inline CNodeMapProxyT<TParams>::~CNodeMapProxyT( void )
        {
        }

        template<class TParams>
        inline void CNodeMapProxyT<TParams>::Attach( GENAPI_NAMESPACE::INodeMap* pNodeMap, bool replace )
        {
            if (IsAttached() && !replace)
            {
                throw LOGICAL_ERROR_EXCEPTION( "Object is already attached to a node map" );
            }

            if (NULL == pNodeMap)
            {
                throw LOGICAL_ERROR_EXCEPTION( "Tried to attach a NULL pointer as node map" );
            }

            TParams::_Initialize( pNodeMap );
            m_pNodeMap = pNodeMap;
        }

        template<class TParams>
        inline bool CNodeMapProxyT<TParams>::IsAttached() const
        {
            return NULL != m_pNodeMap;
        }

        template<class TParams>
        inline GENAPI_NAMESPACE::INodeMap* CNodeMapProxyT<TParams>::GetNodeMap() const
        {
            return m_pNodeMap;
        }
    }


#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // __PYLON_NODEMAPROXY__H__
