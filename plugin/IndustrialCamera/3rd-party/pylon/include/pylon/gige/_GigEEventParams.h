

//-----------------------------------------------------------------------------
//  Copyright (c) 2004-2021 Basler AG
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Interface to the PylonGigE Event Grabber parameters
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_GigEEventParams_PARAMS_H
#define Basler_GigEEventParams_PARAMS_H

#include <GenApi/IEnumerationT.h>
#include <GenApi/NodeMapRef.h>
#include <GenApi/DLLLoad.h>

// common node types
#include <GenApi/IBoolean.h>
#include <GenApi/ICategory.h>
#include <GenApi/ICommand.h>
#include <GenApi/IEnumeration.h>
#include <GenApi/IEnumEntry.h>
#include <GenApi/IFloat.h>
#include <GenApi/IInteger.h>
#include <GenApi/IString.h>
#include <GenApi/IRegister.h>

#ifdef __GNUC__
#   undef GCC_VERSION
#   define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#   undef GCC_DIAGNOSTIC_AWARE
#   define GCC_DIAGNOSTIC_AWARE          (GCC_VERSION >= 40200)
#   undef GCC_DIAGNOSTIC_PUSH_POP_AWARE
#   define GCC_DIAGNOSTIC_PUSH_POP_AWARE (GCC_VERSION >= 40600)
#else
#   undef GCC_DIAGNOSTIC_AWARE
#   define GCC_DIAGNOSTIC_AWARE 0
#endif

#ifdef __GNUC__
    // GCC_DIAGNOSTIC_AWARE ensures that the internal deprecated warnings can be ignored by gcc.
    // As a result older gcc will not generate warnings about really used deprecated features.
#   if GCC_DIAGNOSTIC_AWARE
#       define GENAPI_DEPRECATED_FEATURE __attribute__((deprecated))
#   else
#       define GENAPI_DEPRECATED_FEATURE
#   endif
#elif defined(_MSC_VER)
#   define GENAPI_DEPRECATED_FEATURE __declspec(deprecated)
#else
#   define GENAPI_DEPRECATED_FEATURE
#endif

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic push
#   endif
#   pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif


//! The namespace containing the device's control interface and related enumeration types
namespace Basler_GigEEventParams
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    //! Valid values for Status
    enum StatusEnums
    {
        Status_Closed,  //!<The low level event grabber is closed.
        Status_Open   //!<The low level event grabber is open.

    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************


    //! Interface to the PylonGigE Event Grabber parameters
    class CGigEEventParams_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS

            //! Constructor
        CGigEEventParams_Params( void );

        //! Destructor
        ~CGigEEventParams_Params( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

        //! Return the vendor of the camera
        const char* _GetVendorName( void );

        //! Returns the camera model name
        const char* _GetModelName( void );

    //! \endcond

//----------------------------------------------------------------------------------------------------------------
// References to features
//----------------------------------------------------------------------------------------------------------------
    public:

    //! \name Root - GigE event parameters
    //@{
    /*!
        \brief Number of buffers to be used.

        Number of Buffers that are going to be used receiving events. .

        \b Visibility = Expert

    */
        GENAPI_NAMESPACE::IInteger& NumBuffer;

        //@}


        //! \name Root - GigE event parameters
        //@{
        /*!
            \brief Acknowledge timeout in milliseconds.

            Time to wait by the camera if an acknowledge request is configured (RetryCount != 0) to wait until the acknowledge arrives before resending the event message on its own.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& Timeout;

        //@}


        //! \name Root - GigE event parameters
        //@{
        /*!
            \brief Maximum number of retries.

            Number retry attempts by the camera to get an acknowledge for a sent event message.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& RetryCount;

        //@}


        //! \name Debug - For internal use only.
        //@{
        /*!
            \brief For internal use only.



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<StatusEnums >& Status;

        //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
        CGigEEventParams_Params( CGigEEventParams_Params& );

        //! not implemented assignment operator
        CGigEEventParams_Params& operator=( CGigEEventParams_Params& );

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CGigEEventParams_Params::CGigEEventParams_Params( void )
        : NumBuffer( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Timeout( *new GENAPI_NAMESPACE::CIntegerRef() )
        , RetryCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Status( *new GENAPI_NAMESPACE::CEnumerationTRef<StatusEnums>() )

    {
    }

    inline CGigEEventParams_Params::~CGigEEventParams_Params( void )
    {
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&NumBuffer);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Timeout);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&RetryCount);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<StatusEnums>*> (&Status);

    }

    inline void CGigEEventParams_Params::_Initialize( GENAPI_NAMESPACE::INodeMap* _Ptr )
    {
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&NumBuffer)->SetReference( _Ptr->GetNode( "NumBuffer" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Timeout)->SetReference( _Ptr->GetNode( "Timeout" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&RetryCount)->SetReference( _Ptr->GetNode( "RetryCount" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<StatusEnums>*> (&Status)->SetReference( _Ptr->GetNode( "Status" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<StatusEnums>*> (&Status)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<StatusEnums>*> (&Status)->SetEnumReference( Status_Closed, "Closed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<StatusEnums>*> (&Status)->SetEnumReference( Status_Open, "Open" );
    }

    inline const char* CGigEEventParams_Params::_GetVendorName( void )
    {
        return "Basler";
    }

    inline const char* CGigEEventParams_Params::_GetModelName( void )
    {
        return "GigEEventParams";
    }

    //! \endcond

} // namespace Basler_GigEEventParams

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_GigEEventParams_PARAMS_H
