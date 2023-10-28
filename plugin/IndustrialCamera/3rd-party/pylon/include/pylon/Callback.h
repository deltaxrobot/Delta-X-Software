//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  HN, AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of callback objects.

Helper functions used for managing callbacks. Callback objects are used
to encapsulate C-style functions or C++ member functions as
callbacks.

Based on the ideas of Paul Jakubik.
*/

#ifndef __PYLON_CALLBACK_H__
#define __PYLON_CALLBACK_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <cassert>
#include <cstddef>

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{

    /*
    \brief Abstract callback container.

    This helper class is used to manage device removal callbacks.

    \see RegisterRemovalCallback()
    \see IPylonDevice::RegisterRemovalCallback()
    */
    template <class P1>
    class Base_Callback1Body
    {
    public:
        //! destructor
        virtual ~Base_Callback1Body<P1>( void )
        {
        };

       //! do operation with P1 as argument
        virtual void operator()( P1 ) const = 0;

        //! deep copy
        virtual Base_Callback1Body<P1>* clone( void ) const = 0;
    };

    /*
    \brief Callback object with one parameter P1

    This helper class is used to manage device removal callbacks.

    \see RegisterRemovalCallback()
    \see IPylonDevice::RegisterRemovalCallback()
    */
    template<class P1>
    class Callback1
    {
    public:

        //! constructor, taking lifetime control of body
        Callback1( Base_Callback1Body<P1>* pBody ) :
            m_pBody( pBody )
        {
        }

        //! copy constructor doing deep copy
        Callback1( const Callback1<P1>& callback ) :
            m_pBody( callback.m_pBody ? callback.m_pBody->clone() : NULL )
        {
        }

        //! destructor, destroying body
        ~Callback1( void )
        {
            delete m_pBody;
            m_pBody = NULL;
        }

        //! assignment operator
        Callback1<P1>& operator=( const Callback1<P1>& callback )
        {
            if (this != &callback)
            {
                delete m_pBody;
                m_pBody = callback.m_pBody ? callback.m_pBody->clone() : NULL;
            }
            return *this;
        }

        //! do operation defined in body
        void operator()( P1 p1 )
        {
            if (m_pBody)
                (*m_pBody)(p1);
            else
                assert( false && "Callback1:Empty body" );
        }

    private:
        Base_Callback1Body<P1>* m_pBody;
    };


    /***************************************************************************/
    // C Functions as callbacks
    /***************************************************************************/

    /*
    \brief Container for a function pointer

    This helper class is used to manage device removal callbacks.

    \see RegisterRemovalCallback()
    \see IPylonDevice::RegisterRemovalCallback()
    */
    template <class Function, class P>
    class Function_CallbackBody : public Base_Callback1Body<P>
    {
    public:
        //! Constructor
        Function_CallbackBody( const Function& function ) :
            m_pFunction( function )
        {
        }

       //! execute operation: call the function
        void operator()( P p ) const
        {
            if (m_pFunction)
                m_pFunction( p );
        }

        //! virtual copy constructor
        Function_CallbackBody<Function, P>* clone( void ) const
        {
            return new Function_CallbackBody<Function, P>( *this );
        }
    private:
        //! the callback function
        const Function m_pFunction;

        //! no assignment operator
        Function_CallbackBody& operator=( Function_CallbackBody& );
    };


    /*
    \brief Make a new callback object for C functions

    This helper function is used to manage device removal callbacks.

    Use one of the the Pylon::RegisterRemovalCallback() functions to
    register a callback that is fired in case of a device removal.

    \see IPylonDevice::RegisterRemovalCallback()
    \see RegisterRemovalCallback()
    */
    template <class Function, class Callback, class P>
    Callback make_FunctionCallback( Function function )
    {
        return new Function_CallbackBody<Function, P>( function );
    }


    /*-----------------------------------------------------------------------------*/


    /***************************************************************************/
    // C++ Member functions as callbacks
    /***************************************************************************/

    /*
    \brief Container for a member function pointer

    This helper class is used to manage device removal callbacks.

    \see RegisterRemovalCallback()
    \see IPylonDevice::RegisterRemovalCallback()
    */
    template <class Client, class Member, class P>
    class Member_CallbackBody : public Base_Callback1Body<P>
    {
    public:
        //! Member function type
        typedef void (Client::* PMEMBERFUNC)(P);

        //! Constructor
        Member_CallbackBody( Client& client, Member member ) :
            m_Client( client ),
            m_pMemberFunc( member )
        {
        }

       //! execute operation
        void operator()( P pP ) const
        {
            if (m_pMemberFunc)
                (m_Client.*m_pMemberFunc)(pP);
        }

        //! virtual copy constructor
        Member_CallbackBody<Client, Member, P>* clone() const
        {
            return new Member_CallbackBody<Client, Member, P>( m_Client, m_pMemberFunc );
        }

    private:
        //! The object the method function belongs to
        Client& m_Client;

        //! The method to call
        PMEMBERFUNC m_pMemberFunc;

        //! no assignment operator
        Member_CallbackBody& operator=( Member_CallbackBody& );

        //! no copy constructor
        Member_CallbackBody( const Member_CallbackBody& );
    };

    /*-----------------------------------------------------------------------------*/

    /*
    \brief Make a new callback object for member functions

    \brief Make a new callback object for C functions

    This helper function is used to manage device removal callbacks.

    Use one of the the Pylon::RegisterRemovalCallback() functions to
    register a callback that is fired in case of a device removal.

    \see RegisterRemovalCallback()
    \see IPylonDevice::RegisterRemovalCallback()
    */

    template <class Client, class Member, class Callback, class P>
    Callback make_MemberFunctionCallback( Client& client, Member member )
    {
        return Callback( static_cast<Base_Callback1Body<P>*>(new Member_CallbackBody<Client, Member, P>( client, member )) );
    }




}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif
