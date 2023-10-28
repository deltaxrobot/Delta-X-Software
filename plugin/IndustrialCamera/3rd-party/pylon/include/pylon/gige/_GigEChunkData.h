

//-----------------------------------------------------------------------------
//  Copyright (c) 2004-2021 Basler AG
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Basler generic GigEVision camera interface
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_GigEChunkData_PARAMS_H
#define Basler_GigEChunkData_PARAMS_H

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
namespace Basler_GigEChunkData
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    //! Valid values for ChunkPixelFormat
    enum ChunkPixelFormatEnums
    {
        ChunkPixelFormat_Mono8,  //!<Indicates that the pixel data in the acquired image is in the Mono 8 format
        ChunkPixelFormat_Mono8Signed,  //!<Indicates that the pixel data in the acquired image is in the Mono 8 signed format
        ChunkPixelFormat_Mono10,  //!<Indicates that the pixel data in the acquired image is in the Mono 10 format
        ChunkPixelFormat_Mono10Packed,  //!<Indicates that the pixel data in the acquired image is in the Mono 10 Packed format
        ChunkPixelFormat_Mono10p,  //!<Indicates that the pixel data in the acquired image is in the Mono 10p format
        ChunkPixelFormat_Mono12,  //!<Indicates that the pixel data in the acquired image is in the Mono 12 format
        ChunkPixelFormat_Mono12Packed,  //!<Indicates that the pixel data in the acquired image is in the Mono 12 Packed format
        ChunkPixelFormat_Mono16,  //!<Indicates that the pixel data in the acquired image is in the Mono 16 format
        ChunkPixelFormat_BayerGR8,  //!<Indicates that the pixel data in the acquired image is in the Bayer GR 8 format
        ChunkPixelFormat_BayerRG8,  //!<Indicates that the pixel data in the acquired image is in the Bayer RG 8 format
        ChunkPixelFormat_BayerGB8,  //!<Indicates that the pixel data in the acquired image is in the Bayer GB 8 format
        ChunkPixelFormat_BayerBG8,  //!<Indicates that the pixel data in the acquired image is in the Bayer BG 8 format
        ChunkPixelFormat_BayerGR10,  //!<Indicates that the pixel data in the acquired image is in the Bayer GR 10 format
        ChunkPixelFormat_BayerRG10,  //!<Indicates that the pixel data in the acquired image is in the Bayer RG 10 format
        ChunkPixelFormat_BayerGB10,  //!<Indicates that the pixel data in the acquired image is in the Bayer GB 10 format
        ChunkPixelFormat_BayerBG10,  //!<Indicates that the pixel data in the acquired image is in the Bayer BG 10 format
        ChunkPixelFormat_BayerGR12,  //!<Indicates that the pixel data in the acquired image is in the Bayer GR 12 format
        ChunkPixelFormat_BayerRG12,  //!<Indicates that the pixel data in the acquired image is in the Bayer RG 12 format
        ChunkPixelFormat_BayerGB12,  //!<Indicates that the pixel data in the acquired image is in the Bayer GB 12 format
        ChunkPixelFormat_BayerBG12,  //!<Indicates that the pixel data in the acquired image is in the Bayer BG 12 format
        ChunkPixelFormat_BayerGR16,  //!<Indicates that the pixel data in the acquired image is in the Bayer GR 16 format
        ChunkPixelFormat_BayerRG16,  //!<Indicates that the pixel data in the acquired image is in the Bayer RG 16 format
        ChunkPixelFormat_BayerGB16,  //!<Indicates that the pixel data in the acquired image is in the Bayer GB 16 format
        ChunkPixelFormat_BayerBG16,  //!<Indicates that the pixel data in the acquired image is in the Bayer BG 16 format
        ChunkPixelFormat_RGB8Packed,  //!<Indicates that the pixel data in the acquired image is in the RGB 8 Packed format
        ChunkPixelFormat_BGR8Packed,  //!<Indicates that the pixel data in the acquired image is in the BGR 8 Packed format
        ChunkPixelFormat_RGBA8Packed,  //!<Indicates that the pixel data in the acquired image is in the RGBA 8 Packed format
        ChunkPixelFormat_BGRA8Packed,  //!<Indicates that the pixel data in the acquired image is in the BGRA 8 Packed format
        ChunkPixelFormat_RGB10Packed,  //!<Indicates that the pixel data in the acquired image is in the RGB 10 Packed format
        ChunkPixelFormat_BGR10Packed,  //!<Indicates that the pixel data in the acquired image is in the BGR 10 Packed format
        ChunkPixelFormat_RGB12Packed,  //!<Indicates that the pixel data in the acquired image is in the RGB 12 Packed format
        ChunkPixelFormat_BGR12Packed,  //!<Indicates that the pixel data in the acquired image is in the BGR 12 Packed format
        ChunkPixelFormat_RGB10V1Packed,  //!<Indicates that the pixel data in the acquired image is in the RGB 10V1 Packed format
        ChunkPixelFormat_RGB10V2Packed,  //!<Indicates that the pixel data in the acquired image is in the RGB 10V2 Packed format
        ChunkPixelFormat_YUV411Packed,  //!<Indicates that the pixel data in the acquired image is in the YUV 411 Packed format
        ChunkPixelFormat_YUV422Packed,  //!<Indicates that the pixel data in the acquired image is in the YUV 422 Packed format
        ChunkPixelFormat_YUV444Packed,  //!<Indicates that the pixel data in the acquired image is in the YUV 444 Packed format
        ChunkPixelFormat_RGB8Planar,  //!<Indicates that the pixel data in the acquired image is in the RGB 8 Planar format
        ChunkPixelFormat_RGB10Planar,  //!<Indicates that the pixel data in the acquired image is in the RGB 10 Planar format
        ChunkPixelFormat_RGB12Planar,  //!<Indicates that the pixel data in the acquired image is in the RGB 12 Planar format
        ChunkPixelFormat_RGB16Planar,  //!<Indicates that the pixel data in the acquired image is in the RGB 16 Planar format
        ChunkPixelFormat_YUV422_YUYV_Packed,  //!<Indicates that the pixel data in the acquired image is in the YUV 422 (YUYV) Packed format
        ChunkPixelFormat_BayerGB12Packed,  //!<Indicates that the pixel data in the acquired image is in the Bayer GB 12 Packed format
        ChunkPixelFormat_BayerGR12Packed,  //!<Indicates that the pixel data in the acquired image is in the Bayer GR 12 Packed format
        ChunkPixelFormat_BayerRG12Packed,  //!<Indicates that the pixel data in the acquired image is in the Bayer RG 12 Packed format
        ChunkPixelFormat_BayerBG12Packed,  //!<Indicates that the pixel data in the acquired image is in the Bayer BG 12 Packed format
        ChunkPixelFormat_RGB12V1Packed,  //!<Indicates that the pixel data in the acquired image is in RGB 12 Packed
        ChunkPixelFormat_BayerGB10p,  //!<Indicates that the pixel data in the acquired image is in the Bayer GB 10p format
        ChunkPixelFormat_BayerGR10p,  //!<Indicates that the pixel data in the acquired image is in the Bayer GR 10p format
        ChunkPixelFormat_BayerRG10p,  //!<Indicates that the pixel data in the acquired image is in the Bayer RG 10p format
        ChunkPixelFormat_BayerBG10p   //!<Indicates that the pixel data in the acquired image is in the Bayer BG 10p format

    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************


    //! Basler generic GigEVision camera interface
    class CGigEChunkData_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS

            //! Constructor
        CGigEChunkData_Params( void );

        //! Destructor
        ~CGigEChunkData_Params( void );

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

    //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
    //@{
    /*!
        \brief Indicates the number of bytes of data between the beginning of one line in the acquired image and the beginning of the next line in the acquired image

        This value indicates the number of bytes of data between the beginning of one line in the acquired image and the beginning of the next line in the acquired image.

        \b Visibility = Beginner


    */
        GENAPI_NAMESPACE::IInteger& ChunkStride;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the sequence set index number related to the acquired image

            This value indicates the sequence set index number related to the acquired image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkSequenceSetIndex;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the X offset of the area of interest represented in the acquired image

            This value Indicates the X offset of the area of interest represented in the acquired image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkOffsetX;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the Y offset of the area of interest represented in the acquired image

            This value Indicates the Y offset of the area of interest represented in the acquired image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkOffsetY;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the widtth of the area of interest represented in the acquired image.

            This value Indicates the width of the area of interest represented in the acquired image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkWidth;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the height of the area of interest represented in the acquired image.

            This value Indicates the height of the area of interest represented in the acquired image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkHeight;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the minimum possible pixel value in the acquired image

            This value indicates the minimum possible pixel value in the acquired image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkDynamicRangeMin;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the maximum possible pixel value in the acquired image

            This value indicates indicates the maximum possible pixel value acquired in the image

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkDynamicRangeMax;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the format of the pixel data in the acquired image

            This enumeration lists the pixel formats that can be indicated by the pixel format chunk.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ChunkPixelFormatEnums >& ChunkPixelFormat;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the value of the timestamp when the image was acquired

            This integer indicates the value of the timestamp when the image was acquired.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkTimestamp;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the value of the frame counter when the image was acquired

            This integer indicates the value of the frame counter when the image was acquired.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkFramecounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief A bit field that indicates the status of all of the camera's input and output lines when the image was acquired

            This value is a bit field that indicates the status of all of the camera's input and output lines when the image was acquired.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkLineStatusAll;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief A bit field that indicates the status of all of the camera's virtual input and output lines when the image was acquired

            This value is a bit field that indicates the status of all of the camera's virtual input and output lines when the image was acquired.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkVirtLineStatusAll;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the value of the trigger input counter when the image was acquired

            This integer indicates the value of the trigger input counter when the image was acquired.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkTriggerinputcounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkLineTriggerIgnoredCounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkFrameTriggerIgnoredCounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkFrameTriggerCounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkFramesPerTriggerCounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkLineTriggerEndToEndCounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Number of bits per status



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkInputStatusAtLineTriggerBitsPerLine;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Used to select a certain status



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkInputStatusAtLineTriggerIndex;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Value of the status selected by 'Index'



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkInputStatusAtLineTriggerValue;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Shaft encoder counter at frame trigger



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkShaftEncoderCounter;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ChunkExposureTime;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief Indicates the value of CRC checksum

            This integer indicates the value of CRC checksum.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkPayloadCRC16;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkGainAll;

        //@}


        //! \name ChunkData - This category includes items related to the chunk data that can be appended to the image data
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkLineTriggerCounter;

        //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
        CGigEChunkData_Params( CGigEChunkData_Params& );

        //! not implemented assignment operator
        CGigEChunkData_Params& operator=( CGigEChunkData_Params& );

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CGigEChunkData_Params::CGigEChunkData_Params( void )
        : ChunkStride( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkSequenceSetIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkOffsetX( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkOffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkWidth( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkHeight( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkDynamicRangeMin( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkDynamicRangeMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkPixelFormat( *new GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>() )
        , ChunkTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkFramecounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkLineStatusAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkVirtLineStatusAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkTriggerinputcounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkLineTriggerIgnoredCounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkFrameTriggerIgnoredCounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkFrameTriggerCounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkFramesPerTriggerCounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkLineTriggerEndToEndCounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkInputStatusAtLineTriggerBitsPerLine( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkInputStatusAtLineTriggerIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkInputStatusAtLineTriggerValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkShaftEncoderCounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkExposureTime( *new GENAPI_NAMESPACE::CFloatRef() )
        , ChunkPayloadCRC16( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkGainAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkLineTriggerCounter( *new GENAPI_NAMESPACE::CIntegerRef() )

    {
    }

    inline CGigEChunkData_Params::~CGigEChunkData_Params( void )
    {
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkStride);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkSequenceSetIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkOffsetX);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkOffsetY);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkWidth);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkHeight);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkDynamicRangeMin);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkDynamicRangeMax);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFramecounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineStatusAll);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkVirtLineStatusAll);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkTriggerinputcounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineTriggerIgnoredCounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFrameTriggerIgnoredCounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFrameTriggerCounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFramesPerTriggerCounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineTriggerEndToEndCounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkInputStatusAtLineTriggerBitsPerLine);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkInputStatusAtLineTriggerIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkInputStatusAtLineTriggerValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkShaftEncoderCounter);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ChunkExposureTime);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkPayloadCRC16);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkGainAll);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineTriggerCounter);

    }

    inline void CGigEChunkData_Params::_Initialize( GENAPI_NAMESPACE::INodeMap* _Ptr )
    {
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkStride)->SetReference( _Ptr->GetNode( "ChunkStride" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkSequenceSetIndex)->SetReference( _Ptr->GetNode( "ChunkSequenceSetIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkOffsetX)->SetReference( _Ptr->GetNode( "ChunkOffsetX" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkOffsetY)->SetReference( _Ptr->GetNode( "ChunkOffsetY" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkWidth)->SetReference( _Ptr->GetNode( "ChunkWidth" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkHeight)->SetReference( _Ptr->GetNode( "ChunkHeight" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkDynamicRangeMin)->SetReference( _Ptr->GetNode( "ChunkDynamicRangeMin" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkDynamicRangeMax)->SetReference( _Ptr->GetNode( "ChunkDynamicRangeMax" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetReference( _Ptr->GetNode( "ChunkPixelFormat" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetNumEnums( 51 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono8, "Mono8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono8Signed, "Mono8Signed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono10, "Mono10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono10Packed, "Mono10Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono10p, "Mono10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono12, "Mono12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono12Packed, "Mono12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_Mono16, "Mono16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGR8, "BayerGR8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerRG8, "BayerRG8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGB8, "BayerGB8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerBG8, "BayerBG8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGR10, "BayerGR10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerRG10, "BayerRG10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGB10, "BayerGB10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerBG10, "BayerBG10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGR12, "BayerGR12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerRG12, "BayerRG12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGB12, "BayerGB12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerBG12, "BayerBG12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGR16, "BayerGR16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerRG16, "BayerRG16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGB16, "BayerGB16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerBG16, "BayerBG16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB8Packed, "RGB8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BGR8Packed, "BGR8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGBA8Packed, "RGBA8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BGRA8Packed, "BGRA8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB10Packed, "RGB10Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BGR10Packed, "BGR10Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB12Packed, "RGB12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BGR12Packed, "BGR12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB10V1Packed, "RGB10V1Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB10V2Packed, "RGB10V2Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_YUV411Packed, "YUV411Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_YUV422Packed, "YUV422Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_YUV444Packed, "YUV444Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB8Planar, "RGB8Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB10Planar, "RGB10Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB12Planar, "RGB12Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB16Planar, "RGB16Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_YUV422_YUYV_Packed, "YUV422_YUYV_Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGB12Packed, "BayerGB12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGR12Packed, "BayerGR12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerRG12Packed, "BayerRG12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerBG12Packed, "BayerBG12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_RGB12V1Packed, "RGB12V1Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGB10p, "BayerGB10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerGR10p, "BayerGR10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerRG10p, "BayerRG10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkPixelFormatEnums>*> (&ChunkPixelFormat)->SetEnumReference( ChunkPixelFormat_BayerBG10p, "BayerBG10p" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkTimestamp)->SetReference( _Ptr->GetNode( "ChunkTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFramecounter)->SetReference( _Ptr->GetNode( "ChunkFramecounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineStatusAll)->SetReference( _Ptr->GetNode( "ChunkLineStatusAll" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkVirtLineStatusAll)->SetReference( _Ptr->GetNode( "ChunkVirtLineStatusAll" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkTriggerinputcounter)->SetReference( _Ptr->GetNode( "ChunkTriggerinputcounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineTriggerIgnoredCounter)->SetReference( _Ptr->GetNode( "ChunkLineTriggerIgnoredCounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFrameTriggerIgnoredCounter)->SetReference( _Ptr->GetNode( "ChunkFrameTriggerIgnoredCounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFrameTriggerCounter)->SetReference( _Ptr->GetNode( "ChunkFrameTriggerCounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkFramesPerTriggerCounter)->SetReference( _Ptr->GetNode( "ChunkFramesPerTriggerCounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineTriggerEndToEndCounter)->SetReference( _Ptr->GetNode( "ChunkLineTriggerEndToEndCounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkInputStatusAtLineTriggerBitsPerLine)->SetReference( _Ptr->GetNode( "ChunkInputStatusAtLineTriggerBitsPerLine" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkInputStatusAtLineTriggerIndex)->SetReference( _Ptr->GetNode( "ChunkInputStatusAtLineTriggerIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkInputStatusAtLineTriggerValue)->SetReference( _Ptr->GetNode( "ChunkInputStatusAtLineTriggerValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkShaftEncoderCounter)->SetReference( _Ptr->GetNode( "ChunkShaftEncoderCounter" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ChunkExposureTime)->SetReference( _Ptr->GetNode( "ChunkExposureTime" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkPayloadCRC16)->SetReference( _Ptr->GetNode( "ChunkPayloadCRC16" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkGainAll)->SetReference( _Ptr->GetNode( "ChunkGainAll" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineTriggerCounter)->SetReference( _Ptr->GetNode( "ChunkLineTriggerCounter" ) );

    }

    inline const char* CGigEChunkData_Params::_GetVendorName( void )
    {
        return "Basler";
    }

    inline const char* CGigEChunkData_Params::_GetModelName( void )
    {
        return "GigEChunkData";
    }

    //! \endcond

} // namespace Basler_GigEChunkData

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_GigEChunkData_PARAMS_H
