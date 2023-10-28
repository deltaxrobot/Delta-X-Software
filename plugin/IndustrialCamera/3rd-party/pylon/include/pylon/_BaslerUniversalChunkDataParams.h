//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for chunk data of Basler camera devices

The parameter class is used by the \link Pylon::CBaslerUniversalGrabResultPtr \c CBaslerUniversalGrabResultPtr \endlink class.
More information can be found in the code of the \ref sample_Grab_ChunkImage sample.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_UNIVERSALCHUNKDATAPARAMS_H
#define BASLER_PYLON_UNIVERSALCHUNKDATAPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_UniversalChunkDataParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for BslChunkAutoBrightnessStatus
    enum BslChunkAutoBrightnessStatusEnums
    {
        BslChunkAutoBrightnessStatus_Disabled,  //!< Target brightness adjustments are disabled, i e , Gain Auto and Exposure Auto are set to Off   - Applies to: ace 2 GigE and ace 2 USB
        BslChunkAutoBrightnessStatus_TargetNotReached,  //!< Target brightness adjustments are enabled, but the target brightness value has not been reached - Applies to: ace 2 GigE and ace 2 USB
        BslChunkAutoBrightnessStatus_TargetReached  //!< Target brightness adjustments are enabled, and the target brightness value has been reached - Applies to: ace 2 GigE and ace 2 USB
    };

    //! Valid values for BslChunkTimestampSelector
    enum BslChunkTimestampSelectorEnums
    {
        BslChunkTimestampSelector_ExposureEnd,  //!< The Chunk Timestamp Value parameter indicates when exposure of the current image ended - Applies to: ace 2 GigE and ace 2 USB
        BslChunkTimestampSelector_ExposureStart,  //!< The Chunk Timestamp Value parameter indicates when exposure of the current image started - Applies to: ace 2 GigE and ace 2 USB
        BslChunkTimestampSelector_FrameStart  //!< The Chunk Timestamp Value parameter indicates when acquisition of the current image started - Applies to: ace 2 GigE and ace 2 USB
    };

    //! Valid values for ChunkCounterSelector
    enum ChunkCounterSelectorEnums
    {
        ChunkCounterSelector_Counter1,  //!< Chunk data can be retrieved from counter 1 - Applies to: ace 2 GigE, ace 2 USB and ace USB
        ChunkCounterSelector_Counter2  //!< Chunk data can be retrieved from counter 2 - Applies to: ace 2 GigE, ace 2 USB and ace USB
    };

    //! Valid values for ChunkGainSelector
    enum ChunkGainSelectorEnums
    {
        ChunkGainSelector_All  //!< Chunk data can be retrieved from all gain channels - Applies to: ace USB
    };

    //! Valid values for ChunkPixelFormat
    enum ChunkPixelFormatEnums
    {
        ChunkPixelFormat_BGR10Packed,  //!< The pixel data in the acquired image is in the BGR 10 Packed format - Applies to: GigE
        ChunkPixelFormat_BGR12Packed,  //!< The pixel data in the acquired image is in the BGR 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BGR8Packed,  //!< The pixel data in the acquired image is in the BGR 8 Packed format - Applies to: GigE
        ChunkPixelFormat_BGRA8Packed,  //!< The pixel data in the acquired image is in the BGRA 8 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerBG10,  //!< The pixel data in the acquired image is in the Bayer BG 10 format - Applies to: GigE
        ChunkPixelFormat_BayerBG10p,  //!< The pixel data in the acquired image is in the Bayer BG 10p format - Applies to: GigE
        ChunkPixelFormat_BayerBG12,  //!< The pixel data in the acquired image is in the Bayer BG 12 format - Applies to: GigE
        ChunkPixelFormat_BayerBG12Packed,  //!< The pixel data in the acquired image is in the Bayer BG 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerBG16,  //!< The pixel data in the acquired image is in the Bayer BG 16 format - Applies to: GigE
        ChunkPixelFormat_BayerBG8,  //!< The pixel data in the acquired image is in the Bayer BG 8 format - Applies to: GigE
        ChunkPixelFormat_BayerGB10,  //!< The pixel data in the acquired image is in the Bayer GB 10 format - Applies to: GigE
        ChunkPixelFormat_BayerGB10p,  //!< The pixel data in the acquired image is in the Bayer GB 10p format - Applies to: GigE
        ChunkPixelFormat_BayerGB12,  //!< The pixel data in the acquired image is in the Bayer GB 12 format - Applies to: GigE
        ChunkPixelFormat_BayerGB12Packed,  //!< The pixel data in the acquired image is in the Bayer GB 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerGB16,  //!< The pixel data in the acquired image is in the Bayer GB 16 format - Applies to: GigE
        ChunkPixelFormat_BayerGB8,  //!< The pixel data in the acquired image is in the Bayer GB 8 format - Applies to: GigE
        ChunkPixelFormat_BayerGR10,  //!< The pixel data in the acquired image is in the Bayer GR 10 format - Applies to: GigE
        ChunkPixelFormat_BayerGR10p,  //!< The pixel data in the acquired image is in the Bayer GR 10p format - Applies to: GigE
        ChunkPixelFormat_BayerGR12,  //!< The pixel data in the acquired image is in the Bayer GR 12 format - Applies to: GigE
        ChunkPixelFormat_BayerGR12Packed,  //!< The pixel data in the acquired image is in the Bayer GR 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerGR16,  //!< The pixel data in the acquired image is in the Bayer GR 16 format - Applies to: GigE
        ChunkPixelFormat_BayerGR8,  //!< The pixel data in the acquired image is in the Bayer GR 8 format - Applies to: GigE
        ChunkPixelFormat_BayerRG10,  //!< The pixel data in the acquired image is in the Bayer RG 10 format - Applies to: GigE
        ChunkPixelFormat_BayerRG10p,  //!< The pixel data in the acquired image is in the Bayer RG 10p format - Applies to: GigE
        ChunkPixelFormat_BayerRG12,  //!< The pixel data in the acquired image is in the Bayer RG 12 format - Applies to: GigE
        ChunkPixelFormat_BayerRG12Packed,  //!< The pixel data in the acquired image is in the Bayer RG 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerRG16,  //!< The pixel data in the acquired image is in the Bayer RG 16 format - Applies to: GigE
        ChunkPixelFormat_BayerRG8,  //!< The pixel data in the acquired image is in the Bayer RG 8 format - Applies to: GigE
        ChunkPixelFormat_Mono10,  //!< The pixel data in the acquired image is in the Mono 10 format - Applies to: GigE
        ChunkPixelFormat_Mono10Packed,  //!< The pixel data in the acquired image is in the Mono 10 Packed format - Applies to: GigE
        ChunkPixelFormat_Mono10p,  //!< The pixel data in the acquired image is in the Mono 10p format - Applies to: GigE
        ChunkPixelFormat_Mono12,  //!< The pixel data in the acquired image is in the Mono 12 format - Applies to: GigE
        ChunkPixelFormat_Mono12Packed,  //!< The pixel data in the acquired image is in the Mono 12 Packed format - Applies to: GigE
        ChunkPixelFormat_Mono16,  //!< The pixel data in the acquired image is in the Mono 16 format - Applies to: GigE
        ChunkPixelFormat_Mono8,  //!< The pixel data in the acquired image is in the Mono 8 format - Applies to: GigE
        ChunkPixelFormat_Mono8Signed,  //!< The pixel data in the acquired image is in the Mono 8 Signed format - Applies to: GigE
        ChunkPixelFormat_RGB10Packed,  //!< The pixel data in the acquired image is in the RGB 10 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB10Planar,  //!< The pixel data in the acquired image is in the RGB 10 Planar format - Applies to: GigE
        ChunkPixelFormat_RGB10V1Packed,  //!< The pixel data in the acquired image is in the RGB 10V1 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB10V2Packed,  //!< The pixel data in the acquired image is in the RGB 10V2 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB12Packed,  //!< The pixel data in the acquired image is in the RGB 12 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB12Planar,  //!< The pixel data in the acquired image is in the RGB 12 Planar format - Applies to: GigE
        ChunkPixelFormat_RGB12V1Packed,  //!< The pixel data in the acquired image is in RGB 12 V1 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB16Planar,  //!< The pixel data in the acquired image is in the RGB 16 Planar format - Applies to: GigE
        ChunkPixelFormat_RGB8Packed,  //!< The pixel data in the acquired image is in the RGB 8 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB8Planar,  //!< The pixel data in the acquired image is in the RGB 8 Planar format - Applies to: GigE
        ChunkPixelFormat_RGBA8Packed,  //!< The pixel data in the acquired image is in the RGBA 8 Packed format - Applies to: GigE
        ChunkPixelFormat_YUV411Packed,  //!< The pixel data in the acquired image is in the YUV 411 Packed format - Applies to: GigE
        ChunkPixelFormat_YUV422Packed,  //!< The pixel data in the acquired image is in the YUV 422 Packed format - Applies to: GigE
        ChunkPixelFormat_YUV422_YUYV_Packed,  //!< The pixel data in the acquired image is in the YUV 422 (YUYV) Packed format - Applies to: GigE
        ChunkPixelFormat_YUV444Packed  //!< The pixel data in the acquired image is in the YUV 444 Packed format - Applies to: GigE
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalChunkDataParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for chunk data of Basler camera devices

    The parameter class is used by the \link Pylon::CBaslerUniversalGrabResultPtr \c CBaslerUniversalGrabResultPtr \endlink class.
    More information can be found in the code of the \ref sample_Grab_ChunkImage sample.
    */
    class PYLONBASE_API CUniversalChunkDataParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalChunkDataParams_Params_v6_2_0( void );

        //! Destructor
        ~CUniversalChunkDataParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalChunkDataParams_Params_v6_2_0_Data;
        CUniversalChunkDataParams_Params_v6_2_0_Data* m_pCUniversalChunkDataParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: Root
        //@{
        /*!
            \brief Indicates the status of the target brightness adjustments performed by the Exposure Auto and Gain Auto auto functions - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

        */
        Pylon::IEnumParameterT<BslChunkAutoBrightnessStatusEnums>& BslChunkAutoBrightnessStatus;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets which information should be included in the Chunk Timestamp Value chunk - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            Selecting Parameters: BslChunkTimestampValue

        */
        Pylon::IEnumParameterT<BslChunkTimestampSelectorEnums>& BslChunkTimestampSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            Selected by: BslChunkTimestampSelector

        */
        Pylon::IIntegerEx& BslChunkTimestampValue;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets which counter to retrieve chunk data from - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Expert

            Selecting Parameters: ChunkCounterValue

        */
        Pylon::IEnumParameterT<ChunkCounterSelectorEnums>& ChunkCounterSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the selected chunk counter - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            Selected by: ChunkCounterSelector

        */
        Pylon::IIntegerEx& ChunkCounterValue;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum possible pixel value in the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkDynamicRangeMax;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Minimum possible pixel value in the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkDynamicRangeMin;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Exposure time used to acquire the image - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

        */
        Pylon::IFloatEx& ChunkExposureTime;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Unique identifier of the current frame - Applies to: ace 2 GigE and ace 2 USB

            Unique identifier of the current frame. The frame ID starts at 0 and keeps incrementing by 1 for each exposed image until the camera is powered off. The maximum value is 2^48.

            Visibility: Expert

        */
        Pylon::IIntegerEx& ChunkFrameID;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Frame Trigger counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkFrameTriggerCounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Frame Trigger Ignored counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkFrameTriggerIgnoredCounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Frame counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkFramecounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Frames per Trigger counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkFramesPerTriggerCounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Gain used during image acquisition - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            Selected by: ChunkGainSelector

        */
        Pylon::IFloatEx& ChunkGain;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Gain All value of the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkGainAll;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets which gain channel to retrieve chunk data from - Applies to: ace USB


            Visibility: Expert

            Selecting Parameters: ChunkGain

        */
        Pylon::IEnumParameterT<ChunkGainSelectorEnums>& ChunkGainSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief AOI height of the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkHeight;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Number of bits per line used for the Input Status At Line Trigger parameter - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkInputStatusAtLineTriggerBitsPerLine;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Index number used for the Input Status At Line Trigger parameter - Applies to: GigE

            Index number used for the Input Status At Line Trigger parameter. The index number can be used to get the state of the camera's input lines when a specific line was acquired. For example, if you want to know the state of the camera's input lines when line 30 was acquired, set the index to 30, then retrieve the value of Status Index parameter.

            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkInputStatusAtLineTriggerIndex;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value indicating the status of the camera's input lines when a specific line was acquired - Applies to: GigE

            Value indicating the status of the camera's input lines when a specific line was acquired. The information is stored in a 4-bit value (bit 0 = input line 1 state, bit 1 = input line 2 state etc.). For more information, see the Status Index parameter documentation.

            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkInputStatusAtLineTriggerValue;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Bit field that indicates the status of all of the camera's input and output lines when the image was acquired - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkLineStatusAll;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Line Trigger counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkLineTriggerCounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Line Trigger End to End counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkLineTriggerEndToEndCounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Line Trigger Ignored counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkLineTriggerIgnoredCounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief X offset of the AOI of the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkOffsetX;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Y offset of the AOI of the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkOffsetY;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief CRC checksum of the acquired image - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB

            CRC checksum of the acquired image. The checksum is calculated using all of the image data and all of the appended chunks except for the checksum itself.

            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkPayloadCRC16;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Indicates the pixel format of the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IEnumParameterT<ChunkPixelFormatEnums>& ChunkPixelFormat;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sequence set index number related to the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkSequenceSetIndex;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Index of the active sequencer set - Applies to: ace USB


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkSequencerSetActive;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Shaft Encoder counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkShaftEncoderCounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Number of bytes of data between the beginning of one line in the acquired image and the beginning of the next line in the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkStride;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired - Applies to: GigE and ace USB


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkTimestamp;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the Trigger Input counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkTriggerinputcounter;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Status of all of the camera's virtual input and output lines when the image was acquired - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkVirtLineStatusAll;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Width of the AOI of the acquired image - Applies to: GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkWidth;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalChunkDataParams_Params_v6_2_0(CUniversalChunkDataParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CUniversalChunkDataParams_Params_v6_2_0& operator=(CUniversalChunkDataParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for chunk data of Basler camera devices

    The parameter class is used by the \link Pylon::CBaslerUniversalGrabResultPtr \c CBaslerUniversalGrabResultPtr \endlink class.
    More information can be found in the code of the \ref sample_Grab_ChunkImage sample.
    */
    class CUniversalChunkDataParams_Params : public CUniversalChunkDataParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalChunkDataParams_Params( void )
        {
        }

        //! Destructor
        ~CUniversalChunkDataParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CUniversalChunkDataParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalChunkDataParams

#endif // BASLER_PYLON_UNIVERSALCHUNKDATAPARAMS_H
