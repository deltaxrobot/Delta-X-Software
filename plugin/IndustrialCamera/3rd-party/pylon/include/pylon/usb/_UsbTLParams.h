

//-----------------------------------------------------------------------------
//  Copyright (c) 2004-2021 Basler AG
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Interface to the USB transport layer specific parameters.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_UsbTLParams_PARAMS_H
#define Basler_UsbTLParams_PARAMS_H

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
namespace Basler_UsbTLParams
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************


    //! Interface to the USB transport layer specific parameters.
    class CUsbTLParams_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS

            //! Constructor
        CUsbTLParams_Params( void );

        //! Destructor
        ~CUsbTLParams_Params( void );

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

    //! \name Root - Transport layer-specific parameters.
    //@{
    /*!
        \brief Enables mapping of certain SFNC 1.x node names to SFNC 2.x node names.



        \b Visibility = Guru

    */
        GENAPI_NAMESPACE::IBoolean& MigrationModeEnable;

        //@}


        //! \name Statistic - Statistical data.
        //@{
        /*!
            \brief Number of read pipe resets.



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& Statistic_Read_Pipe_Reset_Count;

        //@}


        //! \name Statistic - Statistical data.
        //@{
        /*!
            \brief Number of write pipe resets.



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& Statistic_Write_Pipe_Reset_Count;

        //@}


        //! \name Statistic - Statistical data.
        //@{
        /*!
            \brief Number of failed read operations.



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& Statistic_Read_Operations_Failed_Count;

        //@}


        //! \name Statistic - Statistical data.
        //@{
        /*!
            \brief Number of failed write operations.



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& Statistic_Write_Operations_Failed_Count;

        //@}


        //! \name Statistic - Statistical data.
        //@{
        /*!
            \brief Last error status of a read or write operation.



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& Statistic_Last_Error_Status;

        //@}


        //! \name Statistic - Statistical data.
        //@{
        /*!
            \brief Last error status of a read or write operation.



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IString& Statistic_Last_Error_Status_Text;

        //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
        CUsbTLParams_Params( CUsbTLParams_Params& );

        //! not implemented assignment operator
        CUsbTLParams_Params& operator=( CUsbTLParams_Params& );

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CUsbTLParams_Params::CUsbTLParams_Params( void )
        : MigrationModeEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , Statistic_Read_Pipe_Reset_Count( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Statistic_Write_Pipe_Reset_Count( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Statistic_Read_Operations_Failed_Count( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Statistic_Write_Operations_Failed_Count( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Statistic_Last_Error_Status( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Statistic_Last_Error_Status_Text( *new GENAPI_NAMESPACE::CStringRef() )

    {
    }

    inline CUsbTLParams_Params::~CUsbTLParams_Params( void )
    {
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&MigrationModeEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Read_Pipe_Reset_Count);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Write_Pipe_Reset_Count);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Read_Operations_Failed_Count);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Write_Operations_Failed_Count);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Last_Error_Status);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&Statistic_Last_Error_Status_Text);

    }

    inline void CUsbTLParams_Params::_Initialize( GENAPI_NAMESPACE::INodeMap* _Ptr )
    {
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&MigrationModeEnable)->SetReference( _Ptr->GetNode( "MigrationModeEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Read_Pipe_Reset_Count)->SetReference( _Ptr->GetNode( "Statistic_Read_Pipe_Reset_Count" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Write_Pipe_Reset_Count)->SetReference( _Ptr->GetNode( "Statistic_Write_Pipe_Reset_Count" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Read_Operations_Failed_Count)->SetReference( _Ptr->GetNode( "Statistic_Read_Operations_Failed_Count" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Write_Operations_Failed_Count)->SetReference( _Ptr->GetNode( "Statistic_Write_Operations_Failed_Count" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Statistic_Last_Error_Status)->SetReference( _Ptr->GetNode( "Statistic_Last_Error_Status" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&Statistic_Last_Error_Status_Text)->SetReference( _Ptr->GetNode( "Statistic_Last_Error_Status_Text" ) );

    }

    inline const char* CUsbTLParams_Params::_GetVendorName( void )
    {
        return "Basler";
    }

    inline const char* CUsbTLParams_Params::_GetModelName( void )
    {
        return "UsbTLParams";
    }

    //! \endcond

} // namespace Basler_UsbTLParams

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_UsbTLParams_PARAMS_H
