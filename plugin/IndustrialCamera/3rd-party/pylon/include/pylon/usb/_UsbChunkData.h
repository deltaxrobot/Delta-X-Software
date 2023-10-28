

//-----------------------------------------------------------------------------
//  Copyright (c) 2004-2021 Basler AG
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Basler USB3Vision camera interface
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_UsbChunkData_PARAMS_H
#define Basler_UsbChunkData_PARAMS_H

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
namespace Basler_UsbChunkData
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    //! Valid values for ChunkGainSelector
    enum ChunkGainSelectorEnums
    {
        ChunkGainSelector_All   //!<Chunk data can be retrieved from all gain channels.

    };

    //! Valid values for ChunkCounterSelector
    enum ChunkCounterSelectorEnums
    {
        ChunkCounterSelector_Counter1,  //!<Chunk data can be retrieved from counter 1.
        ChunkCounterSelector_Counter2   //!<Chunk data can be retrieved from counter 2.

    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************


    //! Basler USB3Vision camera interface
    class CUsbChunkData_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS

            //! Constructor
        CUsbChunkData_Params( void );

        //! Destructor
        ~CUsbChunkData_Params( void );

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

    //! \name ChunkData - Contains parameters to append chunk data to the image data.
    //@{
    /*!
        \brief Sets which gain channel to retrieve chunk data from. Applies to: ace

        Sets which gain channel to retrieve chunk data from.

        \b Visibility = Expert

    */
        GENAPI_NAMESPACE::IEnumerationT<ChunkGainSelectorEnums >& ChunkGainSelector;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief Gain used to acquire the image. Applies to: ace

            Gain used to acquire the image.

            \b Visibility = Beginner


            \b Selected by : ChunkGainSelector

        */
        GENAPI_NAMESPACE::IFloat& ChunkGain;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief Exposure time used to acquire the image. Applies to: ace

            Exposure time used to acquire the image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ChunkExposureTime;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired. Applies to: ace

            Value of the timestamp when the image was acquired.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkTimestamp;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief A bit field that indicates the status of all of the camera's input and output lines when the image was acquired. Applies to: ace

            A bit field that indicates the status of all of the camera's input and output lines when the image was acquired

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkLineStatusAll;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief Sets which counter to retrieve chunk data from. Applies to: ace

            Sets which counter to retrieve chunk data from.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ChunkCounterSelectorEnums >& ChunkCounterSelector;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief Value of the selected chunk counter. Applies to: ace

            Value of the selected chunk counter.

            \b Visibility = Beginner


            \b Selected by : ChunkCounterSelector

        */
        GENAPI_NAMESPACE::IInteger& ChunkCounterValue;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief Index of the active sequencer set. Applies to: ace

            Index of the active sequencer set.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkSequencerSetActive;

        //@}


        //! \name ChunkData - Contains parameters to append chunk data to the image data.
        //@{
        /*!
            \brief CRC checksum of the acquired image. Applies to: ace

            CRC checksum of the acquired image. The checksum is calculated using all of the image data and all of the appended chunks except for the checksum itself.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkPayloadCRC16;

        //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
        CUsbChunkData_Params( CUsbChunkData_Params& );

        //! not implemented assignment operator
        CUsbChunkData_Params& operator=( CUsbChunkData_Params& );

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CUsbChunkData_Params::CUsbChunkData_Params( void )
        : ChunkGainSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ChunkGainSelectorEnums>() )
        , ChunkGain( *new GENAPI_NAMESPACE::CFloatRef() )
        , ChunkExposureTime( *new GENAPI_NAMESPACE::CFloatRef() )
        , ChunkTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkLineStatusAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkCounterSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>() )
        , ChunkCounterValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkSequencerSetActive( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkPayloadCRC16( *new GENAPI_NAMESPACE::CIntegerRef() )

    {
    }

    inline CUsbChunkData_Params::~CUsbChunkData_Params( void )
    {
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ChunkGainSelectorEnums>*> (&ChunkGainSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ChunkGain);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ChunkExposureTime);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineStatusAll);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>*> (&ChunkCounterSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkCounterValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkSequencerSetActive);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkPayloadCRC16);

    }

    inline void CUsbChunkData_Params::_Initialize( GENAPI_NAMESPACE::INodeMap* _Ptr )
    {
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkGainSelectorEnums>*> (&ChunkGainSelector)->SetReference( _Ptr->GetNode( "ChunkGainSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkGainSelectorEnums>*> (&ChunkGainSelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkGainSelectorEnums>*> (&ChunkGainSelector)->SetEnumReference( ChunkGainSelector_All, "All" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ChunkGain)->SetReference( _Ptr->GetNode( "ChunkGain" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ChunkExposureTime)->SetReference( _Ptr->GetNode( "ChunkExposureTime" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkTimestamp)->SetReference( _Ptr->GetNode( "ChunkTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineStatusAll)->SetReference( _Ptr->GetNode( "ChunkLineStatusAll" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>*> (&ChunkCounterSelector)->SetReference( _Ptr->GetNode( "ChunkCounterSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>*> (&ChunkCounterSelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>*> (&ChunkCounterSelector)->SetEnumReference( ChunkCounterSelector_Counter1, "Counter1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>*> (&ChunkCounterSelector)->SetEnumReference( ChunkCounterSelector_Counter2, "Counter2" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkCounterValue)->SetReference( _Ptr->GetNode( "ChunkCounterValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkSequencerSetActive)->SetReference( _Ptr->GetNode( "ChunkSequencerSetActive" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkPayloadCRC16)->SetReference( _Ptr->GetNode( "ChunkPayloadCRC16" ) );

    }

    inline const char* CUsbChunkData_Params::_GetVendorName( void )
    {
        return "Basler";
    }

    inline const char* CUsbChunkData_Params::_GetModelName( void )
    {
        return "UsbChunkData";
    }

    //! \endcond

} // namespace Basler_UsbChunkData

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_UsbChunkData_PARAMS_H
