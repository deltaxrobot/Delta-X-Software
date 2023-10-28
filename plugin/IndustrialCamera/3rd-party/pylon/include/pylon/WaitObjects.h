//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Urs Helmig
//-----------------------------------------------------------------------------
/*!
\file
\brief    Declaration of WaitObjects class
*/
#ifndef __WAITOBJECTS_H__
#define __WAITOBJECTS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/WaitObject.h>

namespace Pylon
{
    class WaitObject;
    enum EWaitExResult;
    namespace PylonPrivate
    {
        struct WaitObjectsImpl;
    }

    // -------------------------------------------------------------------------
    // class WaitObjects
    // ----------------------------------------------------------------------
    /*!
    \brief A set of wait objects
    \ingroup PYLON_PUBLIC
    */
    // ----------------------------------------------------------------------
    class PYLONBASE_API WaitObjects
    {
    public:
        /// Creates an empty wait object set
        WaitObjects();
        /// destructor
        ~WaitObjects();
        /// copy constructor
        WaitObjects( const WaitObjects& );
        /// assignment operator
        WaitObjects& operator=( const WaitObjects& );

    public:
        /// Add an object to wait on and return the index of the added object
        /*!
            Calling Add from another thread during wait operations will cause undefined behaviour.
        */
        unsigned Add( const WaitObject& o );

        /// Removes all added wait objects
        /*!
            Calling RemoveAll from another thread during wait operations will cause undefined behaviour.
        */
        void RemoveAll( void );

        /// Wait for all objects to get signaled
        /*!
            \param timeout maximum wait period in milliseconds
            \return true if all objects were signaled
        */
        bool WaitForAll( unsigned timeout ) const;

        /// Wait for any one object to get signaled
        /*!
            \param timeout maximum wait period in milliseconds
            \param *pIndex (optional) pointer to buffer taking the index of
            the signaled object
            \return true if any object was signaled.
        */
        bool WaitForAny( unsigned timeout, unsigned* pIndex = NULL ) const;

        /// Wait for all objects to get signaled
        /*!
        \param bAlertable If true, the wait operation can be interrupted (Windows: APC; UNIX: signal)
        \param timeout maximum wait period in milliseconds
        */
        EWaitExResult WaitForAllEx( unsigned timeout, bool bAlertable ) const;


        /// Wait for any one object to get signaled
        /*!
        \param timeout maximum wait period in milliseconds
        \param bAlertable If true, the wait operation can be interrupted (Windows: APC; UNIX: signal)
        \param *pIndex (optional) pointer to buffer taking the index of
        the signaled object
        */
        EWaitExResult WaitForAnyEx( unsigned timeout, bool bAlertable, unsigned* pIndex = NULL ) const;

    private:
        PylonPrivate::WaitObjectsImpl* m_pImpl;
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__WAITOBJECTS_H__
