//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2024 Basler AG
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
        BslChunkAutoBrightnessStatus_Disabled,  //!< Target brightness adjustments are disabled, i e , Gain Auto and Exposure Auto are set to Off   - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB and dart USB
        BslChunkAutoBrightnessStatus_TargetNotReached,  //!< Target brightness adjustments are enabled, but the target brightness value has not been reached - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB and dart USB
        BslChunkAutoBrightnessStatus_TargetReached  //!< Target brightness adjustments are enabled, and the target brightness value has been reached - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB and dart USB
    };

    //! Valid values for BslChunkTimestampSelector
    enum BslChunkTimestampSelectorEnums
    {
        BslChunkTimestampSelector_ExposureEnd,  //!< The Chunk Timestamp Value parameter indicates when exposure of the current image ended - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB and dart USB
        BslChunkTimestampSelector_ExposureStart,  //!< The Chunk Timestamp Value parameter indicates when exposure of the current image started - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB and dart USB
        BslChunkTimestampSelector_FrameStart  //!< The Chunk Timestamp Value parameter indicates when acquisition of the current image started - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE
    };

    //! Valid values for ChunkComponentID
    enum ChunkComponentIDEnums
    {
        ChunkComponentID_Confidence,  //!< The image data is the confidence map component - Applies to: Stereo ace
        ChunkComponentID_Disparity,  //!< The image data is the disparity component - Applies to: Stereo ace
        ChunkComponentID_Error,  //!< The image data is the error map component - Applies to: Stereo ace
        ChunkComponentID_Intensity,  //!< The image data is the intensity component - Applies to: Stereo ace
        ChunkComponentID_IntensityCombined  //!< Intensity images of left and right camera combined - Applies to: Stereo ace
    };

    //! Valid values for ChunkComponentSelector
    enum ChunkComponentSelectorEnums
    {
        ChunkComponentSelector_Calibration,  //!< Annotated left and right images for calibration - Applies to: Stereo ace
        ChunkComponentSelector_Confidence,  //!< The image data is the confidence map component - Applies to: Stereo ace
        ChunkComponentSelector_Disparity,  //!< The image data is the disparity component - Applies to: Stereo ace
        ChunkComponentSelector_Error,  //!< The image data is the error map component - Applies to: Stereo ace
        ChunkComponentSelector_Intensity,  //!< The image data is the intensity component - Applies to: Stereo ace
        ChunkComponentSelector_IntensityCombined,  //!< Intensity images of left and right camera combined - Applies to: Stereo ace
        ChunkComponentSelector_RawCombined  //!< Unrectified intensity images of left and right camera combined - Applies to: Stereo ace
    };

    //! Valid values for ChunkCounterSelector
    enum ChunkCounterSelectorEnums
    {
        ChunkCounterSelector_Counter1,  //!< Chunk data can be retrieved from counter 1 - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE
        ChunkCounterSelector_Counter2,  //!< Chunk data can be retrieved from counter 2 - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE
        ChunkCounterSelector_Counter3,  //!< Chunk data can be retrieved from counter 3 - Applies to: racer 2S 5GigE and racer 2S GigE
        ChunkCounterSelector_Counter4  //!< Chunk data can be retrieved from counter 4 - Applies to: racer 2S 5GigE and racer 2S GigE
    };

    //! Valid values for ChunkExposureTimeSelector
    enum ChunkExposureTimeSelectorEnums
    {
        ChunkExposureTimeSelector_Common,  //!< Chunk data can be retrieved from the common exposure time - Applies to: ace 2 GigE, ace 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE
        ChunkExposureTimeSelector_Stage1,  //!< Chunk data can be retrieved from the Stage 1 exposure time - Applies to: ace 2 GigE and ace 2 USB
        ChunkExposureTimeSelector_Stage2  //!< Chunk data can be retrieved from the Stage 2 exposure time - Applies to: ace 2 GigE and ace 2 USB
    };

    //! Valid values for ChunkGainSelector
    enum ChunkGainSelectorEnums
    {
        ChunkGainSelector_All  //!< Chunk data can be retrieved from all gain channels - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart USB, racer 2S 5GigE and racer 2S GigE
    };

    //! Valid values for ChunkLineSelector
    enum ChunkLineSelectorEnums
    {
        ChunkLineSelector_In1,  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
        ChunkLineSelector_In2,  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
        ChunkLineSelector_In3,  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
        ChunkLineSelector_In4,  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
        ChunkLineSelector_Out1,  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
        ChunkLineSelector_Out2,  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
        ChunkLineSelector_Out3,  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
        ChunkLineSelector_Out4  //!< Index of the physical line and associated I/O control block to use - Applies to: Stereo ace
    };

    //! Valid values for ChunkLineSource
    enum ChunkLineSourceEnums
    {
        ChunkLineSource_ExposureActive,  //!< Output is high during the exposure of a Frame - Applies to: Stereo ace
        ChunkLineSource_ExposureAlternateActive,  //!< Output is high during the exposure of every second Frame - Applies to: Stereo ace
        ChunkLineSource_High,  //!< The output is always High - Applies to: Stereo ace
        ChunkLineSource_Low  //!< The output is always Low - Applies to: Stereo ace
    };

    //! Valid values for ChunkPixelFormat
    enum ChunkPixelFormatEnums
    {
        ChunkPixelFormat_BGR10Packed,  //!< The pixel data in the acquired image is in the BGR 10 Packed format - Applies to: GigE
        ChunkPixelFormat_BGR12Packed,  //!< The pixel data in the acquired image is in the BGR 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BGR8,  //!< The pixel format is set to BGR 8 - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BGR8Packed,  //!< The pixel data in the acquired image is in the BGR 8 Packed format - Applies to: GigE
        ChunkPixelFormat_BGRA8Packed,  //!< The pixel data in the acquired image is in the BGRA 8 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerBG10,  //!< The pixel data in the acquired image is in the Bayer BG 10 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerBG10p,  //!< The pixel data in the acquired image is in the Bayer BG 10p format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerBG12,  //!< The pixel data in the acquired image is in the Bayer BG 12 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerBG12Packed,  //!< The pixel data in the acquired image is in the Bayer BG 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerBG12p,  //!< The pixel format is set to Bayer BG 12p - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerBG16,  //!< The pixel data in the acquired image is in the Bayer BG 16 format - Applies to: GigE
        ChunkPixelFormat_BayerBG8,  //!< The pixel data in the acquired image is in the Bayer BG 8 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGB10,  //!< The pixel data in the acquired image is in the Bayer GB 10 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGB10p,  //!< The pixel data in the acquired image is in the Bayer GB 10p format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGB12,  //!< The pixel data in the acquired image is in the Bayer GB 12 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGB12Packed,  //!< The pixel data in the acquired image is in the Bayer GB 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerGB12p,  //!< The pixel format is set to Bayer GB 12p - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGB16,  //!< The pixel data in the acquired image is in the Bayer GB 16 format - Applies to: GigE
        ChunkPixelFormat_BayerGB8,  //!< The pixel data in the acquired image is in the Bayer GB 8 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGR10,  //!< The pixel data in the acquired image is in the Bayer GR 10 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGR10p,  //!< The pixel data in the acquired image is in the Bayer GR 10p format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGR12,  //!< The pixel data in the acquired image is in the Bayer GR 12 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGR12Packed,  //!< The pixel data in the acquired image is in the Bayer GR 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerGR12p,  //!< The pixel format is set to Bayer GR 12p - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerGR16,  //!< The pixel data in the acquired image is in the Bayer GR 16 format - Applies to: GigE
        ChunkPixelFormat_BayerGR8,  //!< The pixel data in the acquired image is in the Bayer GR 8 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerRG10,  //!< The pixel data in the acquired image is in the Bayer RG 10 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerRG10p,  //!< The pixel data in the acquired image is in the Bayer RG 10p format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerRG12,  //!< The pixel data in the acquired image is in the Bayer RG 12 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerRG12Packed,  //!< The pixel data in the acquired image is in the Bayer RG 12 Packed format - Applies to: GigE
        ChunkPixelFormat_BayerRG12p,  //!< The pixel format is set to Bayer RG 12p - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BayerRG16,  //!< The pixel data in the acquired image is in the Bayer RG 16 format - Applies to: GigE
        ChunkPixelFormat_BayerRG8,  //!< The pixel data in the acquired image is in the Bayer RG 8 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_Confidence8,  //!< Confidence 8-bit - Applies to: Stereo ace
        ChunkPixelFormat_Coord3D_C16,  //!< 3D coordinate, third component 16 bit - Applies to: Stereo ace
        ChunkPixelFormat_Error8,  //!< Error 8-bit - Applies to: Stereo ace
        ChunkPixelFormat_Mono10,  //!< The pixel data in the acquired image is in the Mono 10 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_Mono10Packed,  //!< The pixel data in the acquired image is in the Mono 10 Packed format - Applies to: GigE
        ChunkPixelFormat_Mono10p,  //!< The pixel data in the acquired image is in the Mono 10p format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_Mono12,  //!< The pixel data in the acquired image is in the Mono 12 format - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_Mono12Packed,  //!< The pixel data in the acquired image is in the Mono 12 Packed format - Applies to: GigE
        ChunkPixelFormat_Mono12p,  //!< The pixel format is set to Mono 12p - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_Mono16,  //!< The pixel data in the acquired image is in the Mono 16 format - Applies to: GigE and Stereo ace
        ChunkPixelFormat_Mono8,  //!< The pixel data in the acquired image is in the Mono 8 format - Applies to: GigE, Stereo ace, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_Mono8Signed,  //!< The pixel data in the acquired image is in the Mono 8 Signed format - Applies to: GigE
        ChunkPixelFormat_RGB10Packed,  //!< The pixel data in the acquired image is in the RGB 10 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB10Planar,  //!< The pixel data in the acquired image is in the RGB 10 Planar format - Applies to: GigE
        ChunkPixelFormat_RGB10V1Packed,  //!< The pixel data in the acquired image is in the RGB 10V1 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB10V2Packed,  //!< The pixel data in the acquired image is in the RGB 10V2 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB12Packed,  //!< The pixel data in the acquired image is in the RGB 12 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB12Planar,  //!< The pixel data in the acquired image is in the RGB 12 Planar format - Applies to: GigE
        ChunkPixelFormat_RGB12V1Packed,  //!< The pixel data in the acquired image is in RGB 12 V1 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB16Planar,  //!< The pixel data in the acquired image is in the RGB 16 Planar format - Applies to: GigE
        ChunkPixelFormat_RGB8,  //!< The pixel format is set to RGB 8 - Applies to: Stereo ace, ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_RGB8Packed,  //!< The pixel data in the acquired image is in the RGB 8 Packed format - Applies to: GigE
        ChunkPixelFormat_RGB8Planar,  //!< The pixel data in the acquired image is in the RGB 8 Planar format - Applies to: GigE
        ChunkPixelFormat_RGBA8Packed,  //!< The pixel data in the acquired image is in the RGBA 8 Packed format - Applies to: GigE
        ChunkPixelFormat_YCbCr422_8,  //!< The pixel format is set to YCbCr 422 - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_YUV411Packed,  //!< The pixel data in the acquired image is in the YUV 411 Packed format - Applies to: GigE
        ChunkPixelFormat_YUV422Packed,  //!< The pixel data in the acquired image is in the YUV 422 Packed format - Applies to: GigE
        ChunkPixelFormat_YUV422_8,  //!< The pixel format is set to YUV 4:2:2 8 bit packed - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_YUV422_YUYV_Packed,  //!< The pixel data in the acquired image is in the YUV 422 (YUYV) Packed format - Applies to: GigE
        ChunkPixelFormat_YUV444Packed,  //!< The pixel data in the acquired image is in the YUV 444 Packed format - Applies to: GigE
        ChunkPixelFormat_BiColorBGRG8,  //!< The pixel data in the acquired image is in the BiColor BGRG 8 format - Applies to: racer 2S 5GigE and racer 2S GigE
        ChunkPixelFormat_BiColorRGBG8  //!< The pixel data in the acquired image is in the BiColor RGBG 8 format - Applies to: racer 2S 5GigE and racer 2S GigE
    };

    //! Valid values for ChunkScan3dCoordinateSelector
    enum ChunkScan3dCoordinateSelectorEnums
    {
        ChunkScan3dCoordinateSelector_CoordinateC  //!< The third (Z) coordinate - Applies to: Stereo ace
    };

    //! Valid values for ChunkScan3dDistanceUnit
    enum ChunkScan3dDistanceUnitEnums
    {
        ChunkScan3dDistanceUnit_Pixel  //!< Distance values reflect pixel positions on the Sensor Array - Applies to: Stereo ace
    };

    //! Valid values for ChunkScan3dOutputMode
    enum ChunkScan3dOutputModeEnums
    {
        ChunkScan3dOutputMode_DisparityC  //!< Disparity 2 5D Depth map - Applies to: Stereo ace
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalChunkDataParams_Params_v9_0_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for chunk data of Basler camera devices

    The parameter class is used by the \link Pylon::CBaslerUniversalGrabResultPtr \c CBaslerUniversalGrabResultPtr \endlink class.
    More information can be found in the code of the \ref sample_Grab_ChunkImage sample.
    */
    class PYLONBASE_API CUniversalChunkDataParams_Params_v9_0_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalChunkDataParams_Params_v9_0_0( void );

        //! Destructor
        ~CUniversalChunkDataParams_Params_v9_0_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalChunkDataParams_Params_v9_0_0_Data;
        CUniversalChunkDataParams_Params_v9_0_0_Data* m_pCUniversalChunkDataParams_Params_v9_0_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: Root
        //@{
        /*!
            \brief Indicates the status of the target brightness adjustments performed by the Exposure Auto and Gain Auto auto functions - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB and dart USB


            Visibility: Expert

        */
        Pylon::IEnumParameterT<BslChunkAutoBrightnessStatusEnums>& BslChunkAutoBrightnessStatus;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets which information should be included in the Chunk Timestamp Value chunk - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


            Visibility: Expert

            Selecting Parameters: BslChunkTimestampValue

        */
        Pylon::IEnumParameterT<BslChunkTimestampSelectorEnums>& BslChunkTimestampSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


            Visibility: Expert

            Selected by: BslChunkTimestampSelector

        */
        Pylon::IIntegerEx& BslChunkTimestampValue;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the exposure ratio of the selected output line - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkLineSelector

        */
        Pylon::IFloatEx& ChunkBslLineRatio;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum depth that was used - Applies to: Stereo ace


            Visibility: Expert

        */
        Pylon::IFloatEx& ChunkBslMaxDepth;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Minimum depth that was used - Applies to: Stereo ace

            Minimum depth that was used. This can be higher than anticipated due to camera or memory requirements.

            Visibility: Expert

        */
        Pylon::IFloatEx& ChunkBslMinDepth;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the noise of the image - Applies to: Stereo ace


            Visibility: Expert

        */
        Pylon::IFloatEx& ChunkBslNoise;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Signals if the depth range had to be reduced due to memory limits - Applies to: Stereo ace


            Visibility: Expert

        */
        Pylon::IBooleanEx& ChunkBslReducedDepthRange;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the component of the payload image - Applies to: Stereo ace

            Returns the component of the payload image. This can be used to identify the image component of a generic part in a multi-part transfer.

            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IEnumParameterT<ChunkComponentIDEnums>& ChunkComponentID;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns a unique Identifier value that corresponds to the selected chunk component - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IIntegerEx& ChunkComponentIDValue;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Selects the Component from which to retreive data from - Applies to: Stereo ace


            Visibility: Expert

            Selecting Parameters: ChunkComponentID, ChunkComponentIDValue, ChunkDecimationHorizontal, ChunkDecimationVertical, ChunkHeight, ChunkOffsetX, ChunkOffsetY, ChunkPartIndex, ChunkPixelFormat, ChunkScan3dFocalLength, ChunkScan3dPrincipalPointU, ChunkScan3dPrincipalPointV and ChunkWidth

        */
        Pylon::IEnumParameterT<ChunkComponentSelectorEnums>& ChunkComponentSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the bitmask of components contained in this block - Applies to: Stereo ace


            Visibility: Expert

        */
        Pylon::IIntegerEx& ChunkComponents;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets which counter to retrieve chunk data from - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


            Visibility: Expert

            Selecting Parameters: ChunkCounterValue

        */
        Pylon::IEnumParameterT<ChunkCounterSelectorEnums>& ChunkCounterSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the selected chunk counter - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

            Selected by: ChunkCounterSelector

        */
        Pylon::IIntegerEx& ChunkCounterValue;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Horizontal sub-sampling of the image - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IIntegerEx& ChunkDecimationHorizontal;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Vertical sub-sampling of the image - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IIntegerEx& ChunkDecimationVertical;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum possible pixel value in the acquired image - Applies to: GigE and ace 2 GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkDynamicRangeMax;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Minimum possible pixel value in the acquired image - Applies to: GigE and ace 2 GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkDynamicRangeMin;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Exposure time used to acquire the image - Applies to: GigE, Stereo ace, ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

            Selected by: ChunkExposureTimeSelector

        */
        Pylon::IFloatEx& ChunkExposureTime;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets which exposure time to retrieve chunk data from - Applies to: ace 2 GigE, ace 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


            Visibility: Expert

            Selecting Parameters: ChunkExposureTime

        */
        Pylon::IEnumParameterT<ChunkExposureTimeSelectorEnums>& ChunkExposureTimeSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Unique identifier of the current frame - Applies to: Stereo ace, ace 2 GigE, ace 2 USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE

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
            \brief Gain used during image acquisition - Applies to: Stereo ace, ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


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
            \brief Sets which gain channel to retrieve chunk data from - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart USB, racer 2S 5GigE and racer 2S GigE


            Visibility: Expert

            Selecting Parameters: ChunkGain

        */
        Pylon::IEnumParameterT<ChunkGainSelectorEnums>& ChunkGainSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief AOI height of the acquired image - Applies to: GigE, Stereo ace, ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

            Selected by: ChunkComponentSelector

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
            \brief Selects the output for which to read the LineSource - Applies to: Stereo ace


            Visibility: Expert

            Selecting Parameters: ChunkBslLineRatio, ChunkLineSource and ChunkLineStatus

        */
        Pylon::IEnumParameterT<ChunkLineSelectorEnums>& ChunkLineSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Line source for selected line - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkLineSelector

        */
        Pylon::IEnumParameterT<ChunkLineSourceEnums>& ChunkLineSource;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the current status of the selected input or output Line - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkLineSelector

        */
        Pylon::IBooleanEx& ChunkLineStatus;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Bit field that indicates the status of all of the camera's input and output lines when the image was acquired - Applies to: GigE, Stereo ace, ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE


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
            \brief X offset of the AOI of the acquired image - Applies to: GigE, Stereo ace, ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

            Selected by: ChunkComponentSelector

        */
        Pylon::IIntegerEx& ChunkOffsetX;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Y offset of the AOI of the acquired image - Applies to: GigE, Stereo ace, ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

            Selected by: ChunkComponentSelector

        */
        Pylon::IIntegerEx& ChunkOffsetY;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns index of the image part in this block depending on selected component - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IIntegerEx& ChunkPartIndex;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief CRC checksum of the acquired image - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB, racer 2S 5GigE and racer 2S GigE

            CRC checksum of the acquired image. The checksum is calculated using all of the image data and all of the appended chunks except for the checksum itself.

            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkPayloadCRC16;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum possible pixel value in the acquired image - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Expert

        */
        Pylon::IIntegerEx& ChunkPixelDynamicRangeMax;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Minimum possible pixel value in the acquired image - Applies to: ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Expert

        */
        Pylon::IIntegerEx& ChunkPixelDynamicRangeMin;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Indicates the pixel format of the acquired image - Applies to: GigE, Stereo ace, ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

            Selected by: ChunkComponentSelector

        */
        Pylon::IEnumParameterT<ChunkPixelFormatEnums>& ChunkPixelFormat;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Baseline of the stereo cameras - Applies to: Stereo ace

            Baseline of the stereo cameras in m.

            Visibility: Expert

        */
        Pylon::IFloatEx& ChunkScan3dBaseline;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the offset when transforming a pixel from relative coordinates to world coordinates - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkScan3dCoordinateSelector

        */
        Pylon::IFloatEx& ChunkScan3dCoordinateOffset;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the scale factor when transforming a pixel from relative coordinates to world coordinates - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkScan3dCoordinateSelector

        */
        Pylon::IFloatEx& ChunkScan3dCoordinateScale;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Selects which Coordinate to retrieve data from - Applies to: Stereo ace


            Visibility: Expert

            Selecting Parameters: ChunkScan3dCoordinateOffset, ChunkScan3dCoordinateScale, ChunkScan3dInvalidDataFlag and ChunkScan3dInvalidDataValue

        */
        Pylon::IEnumParameterT<ChunkScan3dCoordinateSelectorEnums>& ChunkScan3dCoordinateSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the Distance Unit of the payload image - Applies to: Stereo ace


            Visibility: Expert

        */
        Pylon::IEnumParameterT<ChunkScan3dDistanceUnitEnums>& ChunkScan3dDistanceUnit;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Focal length - Applies to: Stereo ace

            Focal length of the camera in pixels.

            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IFloatEx& ChunkScan3dFocalLength;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns if a specific non-valid data flag is used in the payload image - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkScan3dCoordinateSelector

        */
        Pylon::IBooleanEx& ChunkScan3dInvalidDataFlag;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the value which identifies a non-valid pixel - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkScan3dCoordinateSelector

        */
        Pylon::IFloatEx& ChunkScan3dInvalidDataValue;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Returns the Calibrated Mode of the payload image - Applies to: Stereo ace


            Visibility: Expert

        */
        Pylon::IEnumParameterT<ChunkScan3dOutputModeEnums>& ChunkScan3dOutputMode;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Horizontal position of the principal point - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IFloatEx& ChunkScan3dPrincipalPointU;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Vertical position of the principal point - Applies to: Stereo ace


            Visibility: Expert

            Selected by: ChunkComponentSelector

        */
        Pylon::IFloatEx& ChunkScan3dPrincipalPointV;

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
            \brief Index of the active sequencer set - Applies to: ace 2 GigE, ace 2 USB and ace USB


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
            \brief Number of bytes of data between the beginning of one line in the acquired image and the beginning of the next line in the acquired image - Applies to: GigE, ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

        */
        Pylon::IIntegerEx& ChunkStride;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired - Applies to: GigE, Stereo ace and ace USB


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
            \brief Width of the AOI of the acquired image - Applies to: GigE, Stereo ace, ace 2 GigE, racer 2S 5GigE and racer 2S GigE


            Visibility: Beginner

            Selected by: ChunkComponentSelector

        */
        Pylon::IIntegerEx& ChunkWidth;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalChunkDataParams_Params_v9_0_0(CUniversalChunkDataParams_Params_v9_0_0&);

        //! not implemented assignment operator
        CUniversalChunkDataParams_Params_v9_0_0& operator=(CUniversalChunkDataParams_Params_v9_0_0&);

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class CUniversalChunkDataParams_Params_v9_1_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for chunk data of Basler camera devices

    The parameter class is used by the \link Pylon::CBaslerUniversalGrabResultPtr \c CBaslerUniversalGrabResultPtr \endlink class.
    More information can be found in the code of the \ref sample_Grab_ChunkImage sample.
    */
    class PYLONBASE_API CUniversalChunkDataParams_Params_v9_1_0 : public CUniversalChunkDataParams_Params_v9_0_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalChunkDataParams_Params_v9_1_0( void );

        //! Destructor
        ~CUniversalChunkDataParams_Params_v9_1_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalChunkDataParams_Params_v9_1_0_Data;
        CUniversalChunkDataParams_Params_v9_1_0_Data* m_pCUniversalChunkDataParams_Params_v9_1_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for chunk data of Basler camera devices

    The parameter class is used by the \link Pylon::CBaslerUniversalGrabResultPtr \c CBaslerUniversalGrabResultPtr \endlink class.
    More information can be found in the code of the \ref sample_Grab_ChunkImage sample.
    */
    class CUniversalChunkDataParams_Params : public CUniversalChunkDataParams_Params_v9_1_0
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
            CUniversalChunkDataParams_Params_v9_1_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalChunkDataParams

#endif // BASLER_PYLON_UNIVERSALCHUNKDATAPARAMS_H
