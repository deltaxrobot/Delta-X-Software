

//-----------------------------------------------------------------------------
//  Copyright (c) 2004-2021 Basler AG
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Interface to the GigE transport layer specific parameters
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_GigETLParams_PARAMS_H
#define Basler_GigETLParams_PARAMS_H

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
namespace Basler_GigETLParams
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************


    //! Interface to the GigE transport layer specific parameters
    class CGigETLParams_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS

            //! Constructor
        CGigETLParams_Params( void );

        //! Destructor
        ~CGigETLParams_Params( void );

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

    //! \name Root - Transport layer-specific parameter
    //@{
    /*!
        \brief Read access timeout value in milliseconds.



        \b Visibility = Beginner


    */
        GENAPI_NAMESPACE::IInteger& ReadTimeout;

        //@}


        //! \name Root - Transport layer-specific parameter
        //@{
        /*!
            \brief Write access timeout in milliseconds.



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& WriteTimeout;

        //@}


        //! \name Root - Transport layer-specific parameter
        //@{
        /*!
            \brief Maximum number of retries for read operations after a read operation has timed out.



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& MaxRetryCountRead;

        //@}


        //! \name Root - Transport layer-specific parameter
        //@{
        /*!
            \brief Maximum number of retries for write operations after a write operation has timed out.



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& MaxRetryCountWrite;

        //@}


        //! \name Root - Transport layer-specific parameter
        //@{
        /*!
            \brief Heartbeat timeout value on the host side in milliseconds.



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& HeartbeatTimeout;

        //@}


        //! \name Root - Transport layer-specific parameter
        //@{
        /*!
            \brief Enables sending all commands and receiving all acknowledges twice.

            Enables sending all commands and receiving all acknowledges twice. This option should only be enabled in case of network problems.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& CommandDuplicationEnable;

        //@}


        //! \name Root - Transport layer-specific parameter
        //@{
        /*!
            \brief Number of timeouts during read and write operations when waiting for a response from the device.



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& StatisticReadWriteTimeoutCount;

        //@}


        //! \name Root - Transport layer-specific parameter
        //@{
        /*!
            \brief Migration Mode Enable

            Enables mapping of certain SFNC 1.x node names to SFNC 2.x node names

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& MigrationModeEnable;

        //@}


    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
        CGigETLParams_Params( CGigETLParams_Params& );

        //! not implemented assignment operator
        CGigETLParams_Params& operator=( CGigETLParams_Params& );

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CGigETLParams_Params::CGigETLParams_Params( void )
        : ReadTimeout( *new GENAPI_NAMESPACE::CIntegerRef() )
        , WriteTimeout( *new GENAPI_NAMESPACE::CIntegerRef() )
        , MaxRetryCountRead( *new GENAPI_NAMESPACE::CIntegerRef() )
        , MaxRetryCountWrite( *new GENAPI_NAMESPACE::CIntegerRef() )
        , HeartbeatTimeout( *new GENAPI_NAMESPACE::CIntegerRef() )
        , CommandDuplicationEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , StatisticReadWriteTimeoutCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , MigrationModeEnable( *new GENAPI_NAMESPACE::CBooleanRef() )

    {
    }

    inline CGigETLParams_Params::~CGigETLParams_Params( void )
    {
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ReadTimeout);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&WriteTimeout);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&MaxRetryCountRead);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&MaxRetryCountWrite);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&HeartbeatTimeout);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&CommandDuplicationEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&StatisticReadWriteTimeoutCount);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&MigrationModeEnable);
    }

    inline void CGigETLParams_Params::_Initialize( GENAPI_NAMESPACE::INodeMap* _Ptr )
    {
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ReadTimeout)->SetReference( _Ptr->GetNode( "ReadTimeout" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&WriteTimeout)->SetReference( _Ptr->GetNode( "WriteTimeout" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&MaxRetryCountRead)->SetReference( _Ptr->GetNode( "MaxRetryCountRead" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&MaxRetryCountWrite)->SetReference( _Ptr->GetNode( "MaxRetryCountWrite" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&HeartbeatTimeout)->SetReference( _Ptr->GetNode( "HeartbeatTimeout" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&CommandDuplicationEnable)->SetReference( _Ptr->GetNode( "CommandDuplicationEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&StatisticReadWriteTimeoutCount)->SetReference( _Ptr->GetNode( "StatisticReadWriteTimeoutCount" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&MigrationModeEnable)->SetReference( _Ptr->GetNode( "MigrationModeEnable" ) );
    }

    inline const char* CGigETLParams_Params::_GetVendorName( void )
    {
        return "Basler";
    }

    inline const char* CGigETLParams_Params::_GetModelName( void )
    {
        return "GigETLParams";
    }

    //! \endcond

} // namespace Basler_GigETLParams

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_GigETLParams_PARAMS_H
