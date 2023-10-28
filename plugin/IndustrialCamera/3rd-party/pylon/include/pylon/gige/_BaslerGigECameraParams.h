

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



#ifndef Basler_GigECamera_PARAMS_H
#define Basler_GigECamera_PARAMS_H

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
namespace Basler_GigECamera
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    //! Valid values for SequenceConfigurationMode
    enum SequenceConfigurationModeEnums
    {
        SequenceConfigurationMode_Off,  //!<Disables the sequencer for configuration
        SequenceConfigurationMode_On   //!<Enables the sequencer for configuration

    };

    //! Valid values for SequenceAdvanceMode
    enum SequenceAdvanceModeEnums
    {
        SequenceAdvanceMode_Auto,  //!<Automatic sequence set advance
        SequenceAdvanceMode_Controlled,  //!<Sequence set advance controlled by settable source
        SequenceAdvanceMode_FreeSelection   //!<The sequence sets are selected according to the states of the input lines

    };

    //! Valid values for SequenceControlSelector
    enum SequenceControlSelectorEnums
    {
        SequenceControlSelector_Restart,  //!<Selects controls for sequence restart
        SequenceControlSelector_Advance   //!<Selects controls for sequence set advance

    };

    //! Valid values for SequenceControlSource
    enum SequenceControlSourceEnums
    {
        SequenceControlSource_Disabled,  //!<Advance via asynchronous advance only
        SequenceControlSource_AlwaysActive,  //!<Automatic sequence set advance. The sequence repeat starts with sequence set index number 1
        SequenceControlSource_Line1,  //!<The source for sequence restart or sequence set advance is line 1
        SequenceControlSource_Line2,  //!<The source for sequence restart or sequence set advance is line 2
        SequenceControlSource_Line3,  //!<The source for sequence restart or sequence set advance is line 3
        SequenceControlSource_Line4,  //!<The source for sequence restart or sequence set advance is line 4
        SequenceControlSource_Line5,  //!<The source for sequence restart or sequence set advance is line 5
        SequenceControlSource_Line6,  //!<The source for sequence restart or sequence set advance is line 6
        SequenceControlSource_Line7,  //!<The source for sequence restart or sequence set advance is line 7
        SequenceControlSource_Line8,  //!<The source for sequence restart or sequence set advance is line 8
        SequenceControlSource_CC1,  //!<The source for sequence restart or sequence set advance is CC1
        SequenceControlSource_CC2,  //!<The source for sequence restart or sequence set advance is CC2
        SequenceControlSource_CC3,  //!<The source for sequence restart or sequence set advance is CC3
        SequenceControlSource_CC4,  //!<The source for sequence restart or sequence set advance is CC4
        SequenceControlSource_VInput1,  //!<The source for sequence restart or sequence set advance is Virtual Input 1
        SequenceControlSource_VInput2,  //!<The source for sequence restart or sequence set advance is Virtual Input 2
        SequenceControlSource_VInput3,  //!<The source for sequence restart or sequence set advance is Virtual Input 3
        SequenceControlSource_VInput4,  //!<The source for sequence restart or sequence set advance is Virtual Input 4
        SequenceControlSource_VInputDecActive   //!<The source for sequence restart or sequence set advance is Virtual Input Decoder Active

    };

    //! Valid values for SequenceAddressBitSelector
    enum SequenceAddressBitSelectorEnums
    {
        SequenceAddressBitSelector_Bit0,  //!<Selects bit 0 of the sequence set address
        SequenceAddressBitSelector_Bit1,  //!<Selects bit 1 of the sequence set address
        SequenceAddressBitSelector_Bit2,  //!<Selects bit 2 of the sequence set address
        SequenceAddressBitSelector_Bit3   //!<Selects bit 3 of the sequence set address

    };

    //! Valid values for SequenceAddressBitSource
    enum SequenceAddressBitSourceEnums
    {
        SequenceAddressBitSource_Line1,  //!<Selects line 1 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_Line2,  //!<Selects line 2 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_Line3,  //!<Selects line 3 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_Line4,  //!<Selects line 4 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_Line5,  //!<Selects line 5 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_Line6,  //!<Selects line 6 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_Line7,  //!<Selects line 7 as the source for the selected bit of the sequence set address.
        SequenceAddressBitSource_Line8,  //!<Selects line 8 as the source for the selected bit of the sequence set address.
        SequenceAddressBitSource_CC1,  //!<Selects CC1 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_CC2,  //!<Selects CC2 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_CC3,  //!<Selects CC3 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_CC4,  //!<Selects CC4 as the source for the selected bit of the sequence set address.
        SequenceAddressBitSource_VInput1,  //!<Selects Virtual Input 1 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_VInput2,  //!<Selects Virtual Input 2 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_VInput3,  //!<Selects Virtual Input 3 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_VInput4,  //!<Selects Virtual Input 4 as the source for the selected bit of the sequence set address
        SequenceAddressBitSource_VInputDecActive   //!<Selects Virtual Input Decoder Active as the source for the selected bit of the sequence set address

    };

    //! Valid values for GainAuto
    enum GainAutoEnums
    {
        GainAuto_Off,  //!<Disables the Gain Auto function.
        GainAuto_Once,  //!<Sets operation mode to 'once'.
        GainAuto_Continuous   //!<Sets operation mode to 'continuous'.

    };

    //! Valid values for GainSelector
    enum GainSelectorEnums
    {
        GainSelector_All,  //!<Selects all gain controls for adjustment
        GainSelector_AnalogAll,  //!<Selects all analog gain controls for adjustment
        GainSelector_DigitalAll,  //!<Selects all digital gain controls for adjustment
        GainSelector_Tap1,  //!<Selects the tap 1 gain control for adjustment
        GainSelector_Tap2,  //!<Selects the tap 2 gain control for adjustment
        GainSelector_Tap3,  //!<Selects the tap 3 gain control for adjustment
        GainSelector_Tap4,  //!<Selects the tap 4 gain control for adjustment
        GainSelector_Red,  //!<Selects the red gain control for adjustment
        GainSelector_Green,  //!<Selects the green gain control for adjustment
        GainSelector_Blue   //!<Selects the blue gain control for adjustment

    };

    //! Valid values for BlackLevelSelector
    enum BlackLevelSelectorEnums
    {
        BlackLevelSelector_All,  //!<Selects all black level controls for adjustment
        BlackLevelSelector_AnalogAll,  //!<Selects all analog black level controls for adjustment
        BlackLevelSelector_DigitalAll,  //!<Selects all digital black level controls for adjustment
        BlackLevelSelector_Tap1,  //!<Selects the tap 1 black level control for adjustment
        BlackLevelSelector_Tap2,  //!<Selects the tap 2 black level control for adjustment
        BlackLevelSelector_Tap3,  //!<Selects the tap 3 black level control for adjustment
        BlackLevelSelector_Tap4,  //!<Selects the tap 4 black level control for adjustment
        BlackLevelSelector_Red,  //!<Selects the red black level control for adjustment
        BlackLevelSelector_Green,  //!<Selects the green black level control for adjustment
        BlackLevelSelector_Blue   //!<Selects the blue black level control for adjustment

    };

    //! Valid values for GammaSelector
    enum GammaSelectorEnums
    {
        GammaSelector_User,  //!<Sets gamma to user defined curve
        GammaSelector_sRGB   //!<Sets gamma to fixed sRGB curve.

    };

    //! Valid values for SensorBitDepth
    enum SensorBitDepthEnums
    {
        SensorBitDepth_BitDepth8,  //!<
        SensorBitDepth_BitDepth10,  //!<
        SensorBitDepth_BitDepth12,  //!<
        SensorBitDepth_BitDepth14,  //!<
        SensorBitDepth_BitDepth16   //!<

    };

    //! Valid values for SensorDigitizationTaps
    enum SensorDigitizationTapsEnums
    {
        SensorDigitizationTaps_One,  //!<
        SensorDigitizationTaps_Two,  //!<
        SensorDigitizationTaps_Three,  //!<
        SensorDigitizationTaps_Four   //!<

    };

    //! Valid values for PixelFormat
    enum PixelFormatEnums
    {
        PixelFormat_Mono8,  //!<Sets the pixel format to Mono 8
        PixelFormat_Mono10,  //!<Sets the pixel format to Mono 10
        PixelFormat_Mono10Packed,  //!<Sets the pixel format to Mono 10 Packed
        PixelFormat_Mono10p,  //!<Sets the pixel format to Mono 10p
        PixelFormat_Mono12,  //!<Sets the pixel format to Mono 12
        PixelFormat_Mono12Packed,  //!<Sets the pixel format to Mono 12 Packed
        PixelFormat_Mono16,  //!<Sets the pixel format to Mono 16
        PixelFormat_BayerGR8,  //!<Sets the pixel format to Bayer GR 8
        PixelFormat_BayerRG8,  //!<Sets the pixel format to Bayer RG 8
        PixelFormat_BayerGB8,  //!<Sets the pixel format to Bayer GB 8
        PixelFormat_BayerBG8,  //!<Sets the pixel format to Bayer BG 8
        PixelFormat_BayerGR10,  //!<Sets the pixel format to Bayer GR 10
        PixelFormat_BayerRG10,  //!<Sets the pixel format to Bayer RG 10
        PixelFormat_BayerGB10,  //!<Sets the pixel format to Bayer GB 10
        PixelFormat_BayerBG10,  //!<Sets the pixel format to Bayer BG 10
        PixelFormat_BayerGR12,  //!<Sets the pixel format to Bayer GR 12
        PixelFormat_BayerRG12,  //!<Sets the pixel format to Bayer RG 12
        PixelFormat_BayerGB12,  //!<Sets the pixel format to Bayer GB 12
        PixelFormat_BayerBG12,  //!<Sets the pixel format to Bayer BG 12
        PixelFormat_RGB8Packed,  //!<Sets the pixel format to RGB 8 Packed
        PixelFormat_BGR8Packed,  //!<Sets the pixel format to BGR 8 Packed
        PixelFormat_RGBA8Packed,  //!<Sets the pixel format to RGBA 8 Packed
        PixelFormat_BGRA8Packed,  //!<Sets the pixel format to BGRA 8 Packed
        PixelFormat_RGB10Packed,  //!<Sets the pixel format to RGB 10 Packed
        PixelFormat_BGR10Packed,  //!<Sets the pixel format to BGR 10 Packed
        PixelFormat_RGB12Packed,  //!<Sets the pixel format to RGB 12 Packed
        PixelFormat_BGR12Packed,  //!<Sets the pixel format to BGR 12 Packed
        PixelFormat_RGB10V1Packed,  //!<Sets the pixel format to RGB 10V1 Packed
        PixelFormat_RGB10V2Packed,  //!<Sets the pixel format to RGB 10V2 Packed
        PixelFormat_YUV411Packed,  //!<Sets the pixel format to YUV 411 Packed
        PixelFormat_YUV422Packed,  //!<Sets the pixel format to YUV 422 Packed
        PixelFormat_YUV444Packed,  //!<Sets the pixel format to YUV 444 Packed
        PixelFormat_RGB8Planar,  //!<Sets the pixel format to RGB 8 Planar
        PixelFormat_RGB10Planar,  //!<Sets the pixel format to RGB 10 Planar
        PixelFormat_RGB12Planar,  //!<Sets the pixel format to RGB 12 Planar
        PixelFormat_RGB16Planar,  //!<Sets the pixel format to RGB 16 Planar
        PixelFormat_YUV422_YUYV_Packed,  //!<Sets the pixel format to YUV 422 (YUYV) Packed
        PixelFormat_BayerGB12Packed,  //!<Sets the pixel format to Bayer GB 12 Packed
        PixelFormat_BayerGR12Packed,  //!<Sets the pixel format to Bayer GR 12 Packed
        PixelFormat_BayerRG12Packed,  //!<Sets the pixel format to Bayer RG 12 Packed
        PixelFormat_BayerBG12Packed,  //!<Sets the pixel format to Bayer BG 12 Packed
        PixelFormat_BayerGR16,  //!<Sets the pixel format to Bayer GR 16
        PixelFormat_BayerRG16,  //!<Sets the pixel format to Bayer RG 16
        PixelFormat_BayerGB16,  //!<Sets the pixel format to Bayer GB 16
        PixelFormat_BayerBG16,  //!<Sets the pixel format to Bayer BG 16
        PixelFormat_RGB12V1Packed,  //!<Sets the pixel format to RGB 12 Packed
        PixelFormat_Mono8Signed,  //!<Sets the pixel format to Mono 8 Signed
        PixelFormat_BayerGR10p,  //!<The pixel format is set to Bayer GR 10p.
        PixelFormat_BayerRG10p,  //!<The pixel format is set to Bayer RG 10p.
        PixelFormat_BayerGB10p,  //!<The pixel format is set to Bayer GB 10p.
        PixelFormat_BayerBG10p   //!<The pixel format is set to Bayer BG 10p.

    };

    //! Valid values for PixelCoding
    enum PixelCodingEnums
    {
        PixelCoding_Mono8,  //!<
        PixelCoding_Mono8Signed,  //!<
        PixelCoding_Mono16,  //!<
        PixelCoding_Mono10Packed,  //!<
        PixelCoding_Mono12Packed,  //!<
        PixelCoding_Raw8,  //!<
        PixelCoding_Raw16,  //!<
        PixelCoding_RGB8,  //!<
        PixelCoding_BGR8,  //!<
        PixelCoding_RGBA8,  //!<
        PixelCoding_BGRA8,  //!<
        PixelCoding_RGB16,  //!<
        PixelCoding_BGR16,  //!<
        PixelCoding_RGB10V1Packed,  //!<
        PixelCoding_RGB10V2Packed,  //!<
        PixelCoding_YUV411,  //!<
        PixelCoding_YUV422,  //!<
        PixelCoding_YUV444,  //!<
        PixelCoding_RGB8Planar,  //!<
        PixelCoding_RGB16Planar,  //!<
        PixelCoding_BayerGR10p,  //!<Sets the pixel format to Bayer GR 10p
        PixelCoding_BayerRG10p,  //!<Sets the pixel format to Bayer RG 10p
        PixelCoding_BayerGB10p,  //!<Sets the pixel format to Bayer GB 10p
        PixelCoding_BayerBG10p   //!<Sets the pixel format to Bayer BG 10p

    };

    //! Valid values for PixelSize
    enum PixelSizeEnums
    {
        PixelSize_Bpp1,  //!<Indicates that the depth of the pixel values in the acquired images is 1 bits per pixel
        PixelSize_Bpp2,  //!<Indicates that the depth of the pixel values in the acquired images is 2 bits per pixel
        PixelSize_Bpp4,  //!<Indicates that the depth of the pixel values in the acquired images is 4 bits per pixel
        PixelSize_Bpp8,  //!<Indicates that the depth of the pixel values in the acquired images is 8 bits per pixel
        PixelSize_Bpp10,  //!<Indicates that the depth of the pixel values in the acquired images is 10 bits per pixel
        PixelSize_Bpp12,  //!<Indicates that the depth of the pixel values in the acquired images is 12 bits per pixel
        PixelSize_Bpp14,  //!<Indicates that the depth of the pixel values in the acquired images is 12 bits per pixel
        PixelSize_Bpp16,  //!<Indicates that the depth of the pixel values in the acquired images is 16 bits per pixel
        PixelSize_Bpp24,  //!<Indicates that the depth of the pixel values in the acquired images is 24 bits per pixel
        PixelSize_Bpp32,  //!<Indicates that the depth of the pixel values in the acquired images is 32 bits per pixel
        PixelSize_Bpp36,  //!<Indicates that the depth of the pixel values in the acquired images is 36 bits per pixel
        PixelSize_Bpp48,  //!<Indicates that the depth of the pixel values in the acquired images is 48 bits per pixel
        PixelSize_Bpp64   //!<Indicates that the depth of the pixel values in the acquired images is 64 bits per pixel

    };

    //! Valid values for PixelColorFilter
    enum PixelColorFilterEnums
    {
        PixelColorFilter_Bayer_RG,  //!<Indicates that the Bayer filter has an RG/GB alignment to the pixels in the acquired images
        PixelColorFilter_Bayer_GB,  //!<Indicates that the Bayer filter has a GB/RG alignment to the pixels in the acquired images
        PixelColorFilter_Bayer_GR,  //!<Indicates that the Bayer filter has a GR/BG alignment to the pixels in the acquired images
        PixelColorFilter_Bayer_BG,  //!<Indicates that the Bayer filter has a BG/GR alignment to the pixels in the acquired images
        PixelColorFilter_None   //!<Indicates that no Bayer filter is present on the camera

    };

    //! Valid values for SpatialCorrectionStartingLine
    enum SpatialCorrectionStartingLineEnums
    {
        SpatialCorrectionStartingLine_LineRed,  //!<
        SpatialCorrectionStartingLine_LineGreen,  //!<
        SpatialCorrectionStartingLine_LineBlue   //!<

    };

    //! Valid values for FieldOutputMode
    enum FieldOutputModeEnums
    {
        FieldOutputMode_Field0,  //!<Sets the mode to only output field 0.
        FieldOutputMode_Field1,  //!<Sets the mode to only output field 1.
        FieldOutputMode_Field0First,  //!<Sets the mode to only output field 0 and field 1 in single frames. Starting with field 0.
        FieldOutputMode_ConcatenatedNewFields,  //!<Sets the mode to output a frame consisting of field 0 in the upper half and field 1 in the lower half of the frame.
        FieldOutputMode_DeinterlacedNewFields   //!<Sets the mode to output a frame generated by deinterlacing field 0 and field 1 using the deinterlacer selected by feature Deinterlacer.

    };

    //! Valid values for TestImageSelector
    enum TestImageSelectorEnums
    {
        TestImageSelector_Off,  //!<Sets the camera's test image generation capability to disabled
        TestImageSelector_Black,  //!<Sets the camera to generate and transmit black test images
        TestImageSelector_White,  //!<Sets the camera to generate and transmit white test images
        TestImageSelector_GreyHorizontalRamp,  //!<Sets the camera to generate and transmit test images with a fixed horizontal gray gradient pattern
        TestImageSelector_GreyVerticalRamp,  //!<Sets the camera to generate and transmit test images with a fixed vertical gray gradient pattern
        TestImageSelector_GreyHorizontalRampMoving,  //!<Sets the camera to generate and transmit test images with a moving horizontal gray gradient pattern
        TestImageSelector_GreyVerticalRampMoving,  //!<Sets the camera to generate and transmit test images with a moving vertical gray gradient pattern
        TestImageSelector_HorzontalLineMoving,  //!<Sets the camera to generate and transmit test images with a moving horizontal line pattern
        TestImageSelector_VerticalLineMoving,  //!<Sets the camera to generate and transmit test images with a moving vertical line pattern
        TestImageSelector_ColorBar,  //!<Sets the camera to generate and transmit test images with a color bar pattern
        TestImageSelector_FrameCounter,  //!<Sets the camera to generate and transmit test images with a frame counter pattern
        TestImageSelector_DeviceSpecific,  //!<Sets the camera to generate and transmit test images with a camera specific pattern
        TestImageSelector_FixedDiagonalGrayGradient_8Bit,  //!<Sets the camera to generate and transmit test images with an 8 bit fixed diagonal gray gradient pattern
        TestImageSelector_MovingDiagonalGrayGradient_8Bit,  //!<Sets the camera to generate and transmit test images with an 8 bit moving diagonal gray gradient pattern
        TestImageSelector_MovingDiagonalGrayGradient_12Bit,  //!<Sets the camera to generate and transmit test images with a 12 bit moving diagonal gray gradient pattern
        TestImageSelector_MovingDiagonalGrayGradientFeatureTest_8Bit,  //!<Sets the camera to generate and transmit test images with an 8 bit moving diagonal gray gradient feature test pattern
        TestImageSelector_MovingDiagonalGrayGradientFeatureTest_12Bit,  //!<Sets the camera to generate and transmit test images with a 12 bit moving diagonal gray gradient feature test pattern
        TestImageSelector_MovingDiagonalColorGradient,  //!<Sets the camera to generate and transmit test images with a moving diagonal color gradient pattern
        TestImageSelector_Testimage1,  //!<Sets the camera to generate and transmit test images with a test image 1 pattern
        TestImageSelector_Testimage2,  //!<Sets the camera to generate and transmit test images with a test image 2 pattern
        TestImageSelector_Testimage3,  //!<Sets the camera to generate and transmit test images with a test image 3 pattern
        TestImageSelector_Testimage4,  //!<Sets the camera to generate and transmit test images with a test image 4 pattern
        TestImageSelector_Testimage5,  //!<Sets the camera to generate and transmit test images with a test image 5 pattern
        TestImageSelector_Testimage6,  //!<Sets the camera to generate and transmit test images with a test image 6 pattern
        TestImageSelector_Testimage7   //!<Sets the camera to generate and transmit test images with a test image 7 pattern

    };

    //! Valid values for LightSourceSelector
    enum LightSourceSelectorEnums
    {
        LightSourceSelector_Off,  //!<No matrix color transformation for specific light source is performed.
        LightSourceSelector_Custom,  //!<Allows using a custom defined color transformation matrix.
        LightSourceSelector_Daylight,  //!<The matrix is optimized for image acquisition with daylight of 5000 K.
        LightSourceSelector_Tungsten,  //!<The matrix is optimized for image acquisition with tungsten incandescent light (3100 K).
        LightSourceSelector_MicroscopeLED4500K,  //!<The light source preset for image acquisitions with microscope LED illumination of 4500 K is set.
        LightSourceSelector_MicroscopeLED5500K,  //!<The light source preset for image acquisitions with microscope LED illumination of 5500 K is set.
        LightSourceSelector_MicroscopeLED6000K,  //!<The light source preset for image acquisitions with microscope LED illumination of 6000 K is set.
        LightSourceSelector_Daylight6500K,  //!<The matrix is optimized for image acquisition with daylight of 6500 K.
        LightSourceSelector_LightSource0,  //!<
        LightSourceSelector_LightSource1   //!<

    };

    //! Valid values for BalanceWhiteAuto
    enum BalanceWhiteAutoEnums
    {
        BalanceWhiteAuto_Off,  //!<Disables the Balance White Auto function.
        BalanceWhiteAuto_Once,  //!<Sets operation mode to 'once'.
        BalanceWhiteAuto_Continuous   //!<Sets operation mode to 'continuous'.

    };

    //! Valid values for BalanceRatioSelector
    enum BalanceRatioSelectorEnums
    {
        BalanceRatioSelector_Red,  //!<Selects the red balance ratio control for adjustment
        BalanceRatioSelector_Green,  //!<Selects the green balance ratio control for adjustment
        BalanceRatioSelector_Blue   //!<Selects the blue balance ratio control for adjustment

    };

    //! Valid values for ColorTransformationSelector
    enum ColorTransformationSelectorEnums
    {
        ColorTransformationSelector_RGBtoRGB,  //!<Matrix color transformation from RGB to RGB.
        ColorTransformationSelector_RGBtoYUV,  //!<Matrix color transformation from YUV to RGB.
        ColorTransformationSelector_YUVtoRGB   //!<Matrix color transformation from RGB to YUV.

    };

    //! Valid values for ColorTransformationValueSelector
    enum ColorTransformationValueSelectorEnums
    {
        ColorTransformationValueSelector_Gain00,  //!<Element in row 0 and column 0 of the color transformation matrix.
        ColorTransformationValueSelector_Gain01,  //!<Element in row 0 and column 1 of the color transformation matrix.
        ColorTransformationValueSelector_Gain02,  //!<Element in row 0 and column 2 of the color transformation matrix.
        ColorTransformationValueSelector_Gain10,  //!<Element in row 1 and column 0 of the color transformation matrix.
        ColorTransformationValueSelector_Gain11,  //!<Element in row 1 and column 1 of the color transformation matrix
        ColorTransformationValueSelector_Gain12,  //!<Element in row 1 and column 2 of the color transformation matrix.
        ColorTransformationValueSelector_Gain20,  //!<Element in row 2 and column 0 of the color transformation matrix.
        ColorTransformationValueSelector_Gain21,  //!<Element in row 2 and column 1 of the color transformation matrix.
        ColorTransformationValueSelector_Gain22   //!<Element in row 2 and column 2 of the color transformation matrix.

    };

    //! Valid values for ColorAdjustmentSelector
    enum ColorAdjustmentSelectorEnums
    {
        ColorAdjustmentSelector_Red,  //!<Selects red for the adjustment of colors with predominant red.
        ColorAdjustmentSelector_Yellow,  //!<Selects yellow for the adjustment of colors with predominant yellow.
        ColorAdjustmentSelector_Green,  //!<Selects green the adjustment of colors with predominant green.
        ColorAdjustmentSelector_Cyan,  //!<Selects cyan for the adjustment of colors with predominant cyan.
        ColorAdjustmentSelector_Blue,  //!<Selects blue for the adjustment of colors with predominant blue.
        ColorAdjustmentSelector_Magenta   //!<Selects magenta for the adjustment of colors with predominant magenta.

    };

    //! Valid values for BslContrastMode
    enum BslContrastModeEnums
    {
        BslContrastMode_Linear,  //!<Contrast adjustment using a linear tone curve.
        BslContrastMode_SCurve   //!<Contrast adjustment using an s-type tone curve.

    };

    //! Valid values for DemosaicingMode
    enum DemosaicingModeEnums
    {
        DemosaicingMode_Simple,  //!<Demosaicing is performed using a simple demosaicing algorithm.
        DemosaicingMode_BaslerPGI   //!<Demosaicing is performed using the Basler PGI algorithm.

    };

    //! Valid values for PgiMode
    enum PgiModeEnums
    {
        PgiMode_Off,  //!<Basler PGI image optimizations are disabled.
        PgiMode_On   //!<Basler PGI image optimizations are enabled.

    };

    //! Valid values for ColorTransformationMode
    enum ColorTransformationModeEnums
    {
        ColorTransformationMode_Off,  //!<
        ColorTransformationMode_Custom,  //!<
        ColorTransformationMode_Daylight,  //!<
        ColorTransformationMode_Tungsten,  //!<
        ColorTransformationMode_Daylight_6500K,  //!<
        ColorTransformationMode_Daylight6500K   //!<

    };

    //! Valid values for TonalRangeEnable
    enum TonalRangeEnableEnums
    {
        TonalRangeEnable_Off,  //!<Tonal range adjustment is disabled.
        TonalRangeEnable_On   //!<Tonal range adjustment is enabled.

    };

    //! Valid values for TonalRangeAuto
    enum TonalRangeAutoEnums
    {
        TonalRangeAuto_Off,  //!<Automatic tonal range adjustment is disabled.
        TonalRangeAuto_Once   //!<Automatic tonal range adjustment is enabled.

    };

    //! Valid values for TonalRangeSelector
    enum TonalRangeSelectorEnums
    {
        TonalRangeSelector_Sum,  //!<The summed RGB pixel values are used for tonal range adjustments.
        TonalRangeSelector_Red,  //!<Only the red pixel values are used for tonal range adjustments.
        TonalRangeSelector_Green,  //!<Only the green pixel values are used for tonal range adjustments.
        TonalRangeSelector_Blue   //!<Only the blue pixel values are used for tonal range adjustments.

    };

    //! Valid values for LegacyBinningVertical
    enum LegacyBinningVerticalEnums
    {
        LegacyBinningVertical_Off,  //!<Sets vertical binning to disabled
        LegacyBinningVertical_Two_Rows   //!<Sets vertical binning to 2 rows

    };

    //! Valid values for BinningHorizontalMode
    enum BinningHorizontalModeEnums
    {
        BinningHorizontalMode_Sum,  //!<Sets the binning mode to sum.
        BinningHorizontalMode_Average   //!<Sets the binning mode to average.

    };

    //! Valid values for BinningModeHorizontal
    enum BinningModeHorizontalEnums
    {
        BinningModeHorizontal_Summing,  //!<Sets the binning mode to summing
        BinningModeHorizontal_Averaging   //!<Sets the binning mode to averaging

    };

    //! Valid values for BinningVerticalMode
    enum BinningVerticalModeEnums
    {
        BinningVerticalMode_Sum,  //!<Sets the binning mode to sum.
        BinningVerticalMode_Average   //!<Sets the binning mode to average.

    };

    //! Valid values for BinningModeVertical
    enum BinningModeVerticalEnums
    {
        BinningModeVertical_Summing,  //!<Sets the binning mode to summing
        BinningModeVertical_Averaging   //!<Sets the binning mode to averaging

    };

    //! Valid values for ROIZoneSelector
    enum ROIZoneSelectorEnums
    {
        ROIZoneSelector_Zone0,  //!<Sets vertical ROI zone 0
        ROIZoneSelector_Zone1,  //!<Sets vertical ROI zone 1
        ROIZoneSelector_Zone2,  //!<Sets vertical ROI zone 2
        ROIZoneSelector_Zone3,  //!<Sets vertical ROI zone 3
        ROIZoneSelector_Zone4,  //!<Sets vertical ROI zone 4
        ROIZoneSelector_Zone5,  //!<Sets vertical ROI zone 5
        ROIZoneSelector_Zone6,  //!<Sets vertical ROI zone 6
        ROIZoneSelector_Zone7   //!<Sets vertical ROI zone 7

    };

    //! Valid values for ROIZoneMode
    enum ROIZoneModeEnums
    {
        ROIZoneMode_Off,  //!<Disables a ROI zone.
        ROIZoneMode_On   //!<Enables a ROI zone.

    };

    //! Valid values for AcquisitionMode
    enum AcquisitionModeEnums
    {
        AcquisitionMode_SingleFrame,  //!<Sets the acquisition mode to single frame
        AcquisitionMode_MultiFrame,  //!<Sets the acquisition mode to multi frame
        AcquisitionMode_Continuous   //!<Sets the acquisition mode to continuous

    };

    //! Valid values for TriggerControlImplementation
    enum TriggerControlImplementationEnums
    {
        TriggerControlImplementation_Legacy,  //!<
        TriggerControlImplementation_Standard   //!<

    };

    //! Valid values for TriggerSelector
    enum TriggerSelectorEnums
    {
        TriggerSelector_AcquisitionStart,  //!<Selects the acquisition start trigger for configuration
        TriggerSelector_AcquisitionEnd,  //!<Selects the acquisition end trigger for configuration
        TriggerSelector_AcquisitionActive,  //!<Selects the acquisition active trigger for configuration
        TriggerSelector_FrameStart,  //!<Selects the frame start trigger for configuration
        TriggerSelector_FrameEnd,  //!<Selects the frame end trigger for configuration
        TriggerSelector_FrameActive,  //!<Selects the frame active trigger for configuration
        TriggerSelector_LineStart,  //!<Selects the line start trigger for configuration
        TriggerSelector_ExposureStart,  //!<Selects the exposure start trigger for configuration
        TriggerSelector_ExposureEnd,  //!<Selects the exposure end trigger for configuration
        TriggerSelector_ExposureActive   //!<Selects the exposure active trigger for configuration

    };

    //! Valid values for TriggerMode
    enum TriggerModeEnums
    {
        TriggerMode_Off,  //!<Sets the mode for the selected trigger to off
        TriggerMode_On   //!<Sets the mode for the selected trigger to on

    };

    //! Valid values for TriggerSource
    enum TriggerSourceEnums
    {
        TriggerSource_Software,  //!<Sets the software trigger as the signal source for the selected trigger
        TriggerSource_Line1,  //!<Sets the signal source for the selected trigger to line 1
        TriggerSource_Line2,  //!<Sets the signal source for the selected trigger to line 2
        TriggerSource_Line3,  //!<Sets the signal source for the selected trigger to line 3
        TriggerSource_Line4,  //!<Sets the signal source for the selected trigger to line 4
        TriggerSource_Line5,  //!<Sets the signal source for the selected trigger to line 5
        TriggerSource_Line6,  //!<Sets the signal source for the selected trigger to line 6
        TriggerSource_Line7,  //!<Sets the signal source for the selected trigger to line 7
        TriggerSource_Line8,  //!<Sets the signal source for the selected trigger to line 8
        TriggerSource_CC1,  //!<Sets the signal source for the selected trigger to CC1
        TriggerSource_CC2,  //!<Sets the signal source for the selected trigger to CC2
        TriggerSource_CC3,  //!<Sets the signal source for the selected trigger to CC3
        TriggerSource_CC4,  //!<Sets the signal source for the selected trigger to CC4
        TriggerSource_ShaftEncoderModuleOut,  //!<Sets the signal source for the selected trigger to the shaft encoder module.
        TriggerSource_FrequencyConverter,  //!<Sets the signal source for the selected trigger to the frequency converter module.
        TriggerSource_Timer1Start,  //!<Sets the signal source for the selected trigger to timer 1 start
        TriggerSource_Timer1End,  //!<Sets the signal source for the selected trigger to timer 1 end
        TriggerSource_Counter1Start,  //!<Sets the signal source for the selected trigger to counter 1 start
        TriggerSource_Counter1End,  //!<Sets the signal source for the selected trigger to counter 1 end
        TriggerSource_UserOutput1,  //!<Sets the signal source for the selected trigger to user output 1
        TriggerSource_UserOutput2,  //!<Sets the signal source for the selected trigger to user output 2
        TriggerSource_Action1,  //!<Sets the signal source for the selected trigger to action command signal 1
        TriggerSource_Action2,  //!<Sets the signal source for the selected trigger to action command signal 2
        TriggerSource_Action3,  //!<Sets the signal source for the selected trigger to action command signal 3
        TriggerSource_Action4,  //!<Sets the signal source for the selected trigger to action command signal 4
        TriggerSource_VInput1,  //!<Sets the signal source for the selected trigger to Virtual Input 1
        TriggerSource_VInput2,  //!<Sets the signal source for the selected trigger to Virtual Input 2
        TriggerSource_VInput3,  //!<Sets the signal source for the selected trigger to Virtual Input 3
        TriggerSource_VInput4,  //!<Sets the signal source for the selected trigger to Virtual Input 4
        TriggerSource_VInputDecActive   //!<Sets the signal source for the selected trigger to Virtual Input Decoder Active

    };

    //! Valid values for TriggerActivation
    enum TriggerActivationEnums
    {
        TriggerActivation_RisingEdge,  //!<Sets the selected trigger to become active on the rising edge of the source signal
        TriggerActivation_FallingEdge,  //!<Sets the selected trigger to become active on the falling edge of the source signal
        TriggerActivation_AnyEdge,  //!<Sets the selected trigger to become active on the falling or rising edge of the source signal
        TriggerActivation_LevelHigh,  //!<Sets the selected trigger to become active when  the source signal is high
        TriggerActivation_LevelLow   //!<Sets the selected trigger to become active when  the source signal is low

    };

    //! Valid values for TriggerDelaySource
    enum TriggerDelaySourceEnums
    {
        TriggerDelaySource_Time_us,  //!<Selects the trigger delay to be expressed as a time interval (in microseconds).
        TriggerDelaySource_LineTrigger   //!<Selects the trigger delay to be expressed as a number of line triggers.

    };

    //! Valid values for ExposureMode
    enum ExposureModeEnums
    {
        ExposureMode_Off,  //!<Sets the exposure mode to off
        ExposureMode_Timed,  //!<Sets the exposure mode to timed
        ExposureMode_TriggerWidth,  //!<Sets the exposure mode to trigger width
        ExposureMode_TriggerControlled   //!<Sets the exposure mode to trigger controlled

    };

    //! Valid values for InterlacedIntegrationMode
    enum InterlacedIntegrationModeEnums
    {
        InterlacedIntegrationMode_FieldIntegration,  //!<Sets the integration mode to field integration
        InterlacedIntegrationMode_FrameIntegration   //!<Sets the integration mode to frame integration

    };

    //! Valid values for ExposureAuto
    enum ExposureAutoEnums
    {
        ExposureAuto_Off,  //!<Disables the Exposure Auto function.
        ExposureAuto_Once,  //!<Sets operation mode to 'once'.
        ExposureAuto_Continuous   //!<Sets operation mode to 'continuous'.

    };

    //! Valid values for ExposureTimeMode
    enum ExposureTimeModeEnums
    {
        ExposureTimeMode_Standard,  //!<The exposure time mode is set to Standard.
        ExposureTimeMode_UltraShort   //!<The exposure time mode is set to Ultra Short.

    };

    //! Valid values for ExposureOverlapTimeMode
    enum ExposureOverlapTimeModeEnums
    {
        ExposureOverlapTimeMode_Manual,  //!<Manually sets the ExposureOverlapTimeMax parameter value.
        ExposureOverlapTimeMode_Automatic   //!<Automatic control of the overlap between image acquisitions.

    };

    //! Valid values for ShutterMode
    enum ShutterModeEnums
    {
        ShutterMode_Global,  //!<Sets the shutter mode to global shutter
        ShutterMode_Rolling,  //!<Sets the shutter mode to rolling shutter
        ShutterMode_GlobalResetRelease   //!<Sets the shutter mode to global reset release shutter

    };

    //! Valid values for SensorReadoutMode
    enum SensorReadoutModeEnums
    {
        SensorReadoutMode_Normal,  //!<
        SensorReadoutMode_Fast   //!<

    };

    //! Valid values for AcquisitionStatusSelector
    enum AcquisitionStatusSelectorEnums
    {
        AcquisitionStatusSelector_AcquisitionTriggerWait,  //!<Device is currently waiting for a trigger for the capture of one or many frames.
        AcquisitionStatusSelector_AcquisitionActive,  //!<Device is currently doing an acquisition of one or many frames.
        AcquisitionStatusSelector_AcquisitionTransfer,  //!<Device is currently transferring an acquisition of one or many frames.
        AcquisitionStatusSelector_FrameTriggerWait,  //!<Device is currently waiting for a Frame trigger.
        AcquisitionStatusSelector_FrameActive,  //!<Device is currently doing the capture of a frame.
        AcquisitionStatusSelector_FrameTransfer,  //!<Device is currently transferring a frame.
        AcquisitionStatusSelector_ExposureActive,  //!<Device is doing the exposure of a frame.
        AcquisitionStatusSelector_LineTriggerWait,  //!<Device is currently waiting for a line trigger.
        AcquisitionStatusSelector_AcquisitionIdle   //!<

    };

    //! Valid values for LineSelector
    enum LineSelectorEnums
    {
        LineSelector_Line1,  //!<Selects line 1 for configuration
        LineSelector_Line2,  //!<Selects line 2 for configuration
        LineSelector_Line3,  //!<Selects line 3 for configuration
        LineSelector_Line4,  //!<Selects line 4 for configuration
        LineSelector_Out1,  //!<Selects output line 1 for configuration
        LineSelector_Out2,  //!<Selects output line 2 for configuration
        LineSelector_Out3,  //!<Selects output line 3 for configuration
        LineSelector_Out4   //!<Selects output line 4 for configuration

    };

    //! Valid values for LineMode
    enum LineModeEnums
    {
        LineMode_Input,  //!<Sets the mode for the selected line to input
        LineMode_Output   //!<Sets the mode for the selected line to output

    };

    //! Valid values for LineLogic
    enum LineLogicEnums
    {
        LineLogic_Positive,  //!<
        LineLogic_Negative   //!<

    };

    //! Valid values for LineFormat
    enum LineFormatEnums
    {
        LineFormat_NoConnect,  //!<Sets the electrical configuration of the selected line to not connected
        LineFormat_TriState,  //!<Sets the electrical configuration of the selected line to tri-state
        LineFormat_TTL,  //!<Sets the electrical configuration of the selected line to TTL
        LineFormat_LVDS,  //!<Sets the electrical configuration of the selected line to LVDS
        LineFormat_RS422,  //!<Sets the electrical configuration of the selected line to RS-422
        LineFormat_OptoCoupled   //!<Sets the electrical configuration of the selected line to opto-coupled

    };

    //! Valid values for LineSource
    enum LineSourceEnums
    {
        LineSource_Off,  //!<Sets the source signal for the selected output line to off
        LineSource_ExposureActive,  //!<Sets the source signal for the selected output line to exposure active
        LineSource_FrameTriggerWait,  //!<Associates the Frame Trigger Wait status with the selected output line.
        LineSource_LineTriggerWait,  //!<Associates the Line Trigger Wait status with the selected output line.
        LineSource_Timer1Active,  //!<Sets the source signal for the selected output line to timer 1 active
        LineSource_Timer2Active,  //!<Sets the source signal for the selected output line to timer 2 active
        LineSource_Timer3Active,  //!<Sets the source signal for the selected output line to timer 3 active
        LineSource_Timer4Active,  //!<Sets the source signal for the selected output line to timer 4 active
        LineSource_TimerActive,  //!<
        LineSource_UserOutput1,  //!<Sets the source signal for the selected output line to user settable output signal 1
        LineSource_UserOutput2,  //!<Sets the source signal for the selected output line to user settable output signal 2
        LineSource_UserOutput3,  //!<Sets the source signal for the selected output line to user settable output signal 3
        LineSource_UserOutput4,  //!<Sets the source signal for the selected output line to user settable output signal 4
        LineSource_UserOutput,  //!<
        LineSource_TriggerReady,  //!<
        LineSource_SerialTx,  //!<
        LineSource_AcquisitionTriggerWait,  //!<Associates the Acquisition Trigger Wait status with the selected output line.
        LineSource_ShaftEncoderModuleOut,  //!<Associates the output of the shaft encoder module with the selected output line.
        LineSource_FrequencyConverter,  //!<Associates the output of the frequency converter module with the selected output line.
        LineSource_PatternGenerator1,  //!<
        LineSource_PatternGenerator2,  //!<
        LineSource_PatternGenerator3,  //!<
        LineSource_PatternGenerator4,  //!<
        LineSource_AcquisitionTriggerReady,  //!<
        LineSource_FlashWindow,  //!<
        LineSource_FrameCycle,  //!<This signal is rising with frame trigger wait and falling with exposure active
        LineSource_SyncUserOutput,  //!<
        LineSource_UserOutput0,  //!<Sets the source signal for the selected output line to user settable output signal 0
        LineSource_SyncUserOutput0,  //!<The source signal for the currently selected line is set to the sync user settable signal 0.
        LineSource_SyncUserOutput1,  //!<The source signal for the currently selected line is set to the sync user settable signal 1.
        LineSource_SyncUserOutput2,  //!<The source signal for the currently selected line is set to the sync user settable signal 2.
        LineSource_SyncUserOutput3   //!<The source signal for the currently selected line is set to the sync user settable signal 3.

    };

    //! Valid values for UserOutputSelector
    enum UserOutputSelectorEnums
    {
        UserOutputSelector_UserOutput1,  //!<Selects user settable output signal 1 for configuration
        UserOutputSelector_UserOutput2,  //!<Selects user settable output signal 2 for configuration
        UserOutputSelector_UserOutput3,  //!<Selects user settable output signal 3 for configuration
        UserOutputSelector_UserOutput4,  //!<Selects user settable output signal 4 for configuration
        UserOutputSelector_UserOutput5,  //!<Selects user settable output signal 5 for configuration
        UserOutputSelector_UserOutput6,  //!<Selects user settable output signal 6 for configuration
        UserOutputSelector_UserOutput7,  //!<Selects user settable output signal 7 for configuration
        UserOutputSelector_UserOutput8   //!<Selects user settable output signal 8 for configuration

    };

    //! Valid values for SyncUserOutputSelector
    enum SyncUserOutputSelectorEnums
    {
        SyncUserOutputSelector_SyncUserOutput1,  //!<Selects user settable synchronous output signal 1 for configuration
        SyncUserOutputSelector_SyncUserOutput2,  //!<Selects user settable synchronous output signal 2 for configuration
        SyncUserOutputSelector_SyncUserOutput3,  //!<Selects user settable synchronous output signal 3 for configuration
        SyncUserOutputSelector_SyncUserOutput4,  //!<Selects user settable synchronous output signal 4 for configuration
        SyncUserOutputSelector_SyncUserOutput5,  //!<Selects user settable synchronous output signal 5 for configuration
        SyncUserOutputSelector_SyncUserOutput6,  //!<Selects user settable synchronous output signal 6 for configuration
        SyncUserOutputSelector_SyncUserOutput7,  //!<Selects user settable synchronous output signal 7 for configuration
        SyncUserOutputSelector_SyncUserOutput8   //!<Selects user settable synchronous output signal 8 for configuration

    };

    //! Valid values for VInpSignalSource
    enum VInpSignalSourceEnums
    {
        VInpSignalSource_Line1,  //!<TODO
        VInpSignalSource_Line2,  //!<TODO
        VInpSignalSource_Line3,  //!<TODO
        VInpSignalSource_Line4,  //!<TODO
        VInpSignalSource_Line5,  //!<TODO
        VInpSignalSource_Line6,  //!<TODO
        VInpSignalSource_Line7,  //!<TODO
        VInpSignalSource_Line8,  //!<TODO
        VInpSignalSource_CC1,  //!<TODO
        VInpSignalSource_CC2,  //!<TODO
        VInpSignalSource_CC3,  //!<TODO
        VInpSignalSource_CC4   //!<TODO

    };

    //! Valid values for VInpSignalReadoutActivation
    enum VInpSignalReadoutActivationEnums
    {
        VInpSignalReadoutActivation_RisingEdge,  //!<Sets the type of signal change necessary to start the signal evaluation
        VInpSignalReadoutActivation_FallingEdge   //!<Sets the type of signal change necessary to start the signal evaluation

    };

    //! Valid values for ShaftEncoderModuleLineSelector
    enum ShaftEncoderModuleLineSelectorEnums
    {
        ShaftEncoderModuleLineSelector_PhaseA,  //!<Selects phase A of the shaft encoder.
        ShaftEncoderModuleLineSelector_PhaseB   //!<Selects phase B of the shaft encoder.

    };

    //! Valid values for ShaftEncoderModuleLineSource
    enum ShaftEncoderModuleLineSourceEnums
    {
        ShaftEncoderModuleLineSource_Line1,  //!<Selects input line 1 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_Line2,  //!<Selects input line 2 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_Line3,  //!<Selects input line 3 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_Line4,  //!<Selects input line 4 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_Line5,  //!<Selects input line 5 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_Line6,  //!<Selects input line 6 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_Line7,  //!<Selects input line 7 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_Line8,  //!<Selects input line 8 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_CC1,  //!<Selects CC1 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_CC2,  //!<Selects CC2 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_CC3,  //!<Selects CC3 as signal source for the shaft encoder module.
        ShaftEncoderModuleLineSource_CC4   //!<Selects CC4 as signal source for the shaft encoder module.

    };

    //! Valid values for ShaftEncoderModuleMode
    enum ShaftEncoderModuleModeEnums
    {
        ShaftEncoderModuleMode_AnyDirection,  //!<Output of trigger signals for forward and reverse ticks provided the reverse counter is not counting.
        ShaftEncoderModuleMode_ForwardOnly   //!<Output of trigger signals for forward ticks only provided the reverse counter is not decrementing.

    };

    //! Valid values for ShaftEncoderModuleCounterMode
    enum ShaftEncoderModuleCounterModeEnums
    {
        ShaftEncoderModuleCounterMode_FollowDirection,  //!<Tick counter increments for forward ticks and decrements for reverse ticks.
        ShaftEncoderModuleCounterMode_IgnoreDirection   //!<Tick counter increments for forward ticks and for reverse ticks.

    };

    //! Valid values for FrequencyConverterInputSource
    enum FrequencyConverterInputSourceEnums
    {
        FrequencyConverterInputSource_Line1,  //!<Selects line 1 as the input source.
        FrequencyConverterInputSource_Line2,  //!<Selects line 2 as the input source.
        FrequencyConverterInputSource_Line3,  //!<Selects line 3 as the input source.
        FrequencyConverterInputSource_Line4,  //!<Selects line 4 as the input source.
        FrequencyConverterInputSource_Line5,  //!<Selects line 5 as the input source.
        FrequencyConverterInputSource_Line6,  //!<Selects line 6 as the input source.
        FrequencyConverterInputSource_Line7,  //!<Selects line 7 as the input source.
        FrequencyConverterInputSource_Line8,  //!<Selects line 8 as the input source.
        FrequencyConverterInputSource_CC1,  //!<Selects CC1 as the input source.
        FrequencyConverterInputSource_CC2,  //!<Selects CC2 as the input source.
        FrequencyConverterInputSource_CC3,  //!<Selects CC3 as the input source.
        FrequencyConverterInputSource_CC4,  //!<Selects CC4 as the input source.
        FrequencyConverterInputSource_ShaftEncoderModuleOut   //!<Selects the output of the shaft encoder module as the input source.

    };

    //! Valid values for FrequencyConverterSignalAlignment
    enum FrequencyConverterSignalAlignmentEnums
    {
        FrequencyConverterSignalAlignment_RisingEdge,  //!<For the rising edge of each received signal a rising edge of a generated signal is provided.
        FrequencyConverterSignalAlignment_FallingEdge   //!<For the falling edge of each received signal a falling edge of a generated signal is provided.

    };

    //! Valid values for TimerSelector
    enum TimerSelectorEnums
    {
        TimerSelector_Timer1,  //!<Selects timer 1 for configuration
        TimerSelector_Timer2,  //!<Selects timer 2 for configuration
        TimerSelector_Timer3,  //!<Selects timer 3 for configuration
        TimerSelector_Timer4   //!<Selects timer 4 for configuration

    };

    //! Valid values for TimerTriggerSource
    enum TimerTriggerSourceEnums
    {
        TimerTriggerSource_Off,  //!<Sets the source signal for the selected timer to off
        TimerTriggerSource_ExposureStart,  //!<Sets the source signal for the selected timer to exposure active
        TimerTriggerSource_FlashWindowStart   //!<Starts with the reception of the flash window start.

    };

    //! Valid values for TimerTriggerActivation
    enum TimerTriggerActivationEnums
    {
        TimerTriggerActivation_RisingEdge,  //!<Sets the type of signal change that will start the timer to rising edge
        TimerTriggerActivation_FallingEdge,  //!<Sets the type of signal change that will start the timer to falling edge
        TimerTriggerActivation_LevelHigh,  //!<
        TimerTriggerActivation_LevelLow   //!<

    };

    //! Valid values for CounterSelector
    enum CounterSelectorEnums
    {
        CounterSelector_Counter1,  //!<Selects counter 1 for configuration
        CounterSelector_Counter2,  //!<Selects counter 2 for configuration
        CounterSelector_Counter3,  //!<Selects counter 3 for configuration
        CounterSelector_Counter4   //!<Selects counter 4 for configuration

    };

    //! Valid values for CounterEventSource
    enum CounterEventSourceEnums
    {
        CounterEventSource_Off,  //!<Counter is stopped
        CounterEventSource_AcquisitionTrigger,  //!<Counts the number of Acquisition Trigger
        CounterEventSource_AcquisitionStart,  //!<Counts the number of Acquisition Start
        CounterEventSource_AcquisitionEnd,  //!<Counts the number of Acquisition End
        CounterEventSource_FrameTrigger,  //!<Counts the number of Frame Trigger
        CounterEventSource_FrameStart,  //!<Counts the number of Frame Start
        CounterEventSource_FrameEnd,  //!<Counts the number of Frame End
        CounterEventSource_LineTrigger,  //!<Counts the number of Line Trigger
        CounterEventSource_LineStart,  //!<Counts the number of Line Start
        CounterEventSource_LineEnd,  //!<Counts the number of Line End
        CounterEventSource_ExposureStart,  //!<Counts the number of Exposure Start
        CounterEventSource_ExposureEnd   //!<Counts the number of Exposure End

    };

    //! Valid values for CounterResetSource
    enum CounterResetSourceEnums
    {
        CounterResetSource_Off,  //!<Disables counter reset
        CounterResetSource_Software,  //!<Selects software command as the source for counter reset
        CounterResetSource_Line1,  //!<Selects line 1 as the source for counter reset
        CounterResetSource_Line2,  //!<Selects line 2 as the source for counter reset
        CounterResetSource_Line3,  //!<Selects line 3 as the source for counter reset
        CounterResetSource_Line4,  //!<Selects line 4 as the source for counter reset
        CounterResetSource_Line5,  //!<Selects line 5 as the source for counter reset
        CounterResetSource_Line6,  //!<Selects line 6 as the source for counter reset
        CounterResetSource_Line7,  //!<Selects line 7 as the source for counter reset
        CounterResetSource_Line8,  //!<Selects line 8 as the source for counter reset
        CounterResetSource_CC1,  //!<Selects CC1 as the source for counter reset
        CounterResetSource_CC2,  //!<Selects CC2 as the source for counter reset
        CounterResetSource_CC3,  //!<Selects CC3 as the source for counter reset
        CounterResetSource_CC4,  //!<Selects CC4 as the source for counter reset
        CounterResetSource_VInput1,  //!<Selects Virtual Input 1 as the source for counter reset
        CounterResetSource_VInput2,  //!<Selects Virtual Input 2 as the source for counter reset
        CounterResetSource_VInput3,  //!<Selects Virtual Input 3 as the source for counter reset
        CounterResetSource_VInput4,  //!<Selects Virtual Input 4 as the source for counter reset
        CounterResetSource_VInputDecActive   //!<Selects Virtual Input Decoder Active as the source for counter reset

    };

    //! Valid values for TimerSequenceEntrySelector
    enum TimerSequenceEntrySelectorEnums
    {
        TimerSequenceEntrySelector_Entry1,  //!<
        TimerSequenceEntrySelector_Entry2,  //!<
        TimerSequenceEntrySelector_Entry3,  //!<
        TimerSequenceEntrySelector_Entry4,  //!<
        TimerSequenceEntrySelector_Entry5,  //!<
        TimerSequenceEntrySelector_Entry6,  //!<
        TimerSequenceEntrySelector_Entry7,  //!<
        TimerSequenceEntrySelector_Entry8,  //!<
        TimerSequenceEntrySelector_Entry9,  //!<
        TimerSequenceEntrySelector_Entry10,  //!<
        TimerSequenceEntrySelector_Entry11,  //!<
        TimerSequenceEntrySelector_Entry12,  //!<
        TimerSequenceEntrySelector_Entry13,  //!<
        TimerSequenceEntrySelector_Entry14,  //!<
        TimerSequenceEntrySelector_Entry15,  //!<
        TimerSequenceEntrySelector_Entry16   //!<

    };

    //! Valid values for TimerSequenceTimerSelector
    enum TimerSequenceTimerSelectorEnums
    {
        TimerSequenceTimerSelector_Timer1,  //!<
        TimerSequenceTimerSelector_Timer2,  //!<
        TimerSequenceTimerSelector_Timer3,  //!<
        TimerSequenceTimerSelector_Timer4   //!<

    };

    //! Valid values for LUTSelector
    enum LUTSelectorEnums
    {
        LUTSelector_Luminance   //!<Selects the luminance LUT for configuration

    };

    //! Valid values for GevInterfaceSelector
    enum GevInterfaceSelectorEnums
    {
        GevInterfaceSelector_NetworkInterface0   //!<Selects network interface 0 for configuration

    };

    //! Valid values for GevGVSPExtendedIDMode
    enum GevGVSPExtendedIDModeEnums
    {
        GevGVSPExtendedIDMode_Off,  //!<Off
        GevGVSPExtendedIDMode_On   //!<On

    };

    //! Valid values for GevCCP
    enum GevCCPEnums
    {
        GevCCP_Exclusive,  //!<Sets the control channel privilege feature to exclusive
        GevCCP_Control,  //!<Sets the control channel privilege feature to control
        GevCCP_ExclusiveControl   //!<Sets the control channel privilege feature to exclusive control

    };

    //! Valid values for GevStreamChannelSelector
    enum GevStreamChannelSelectorEnums
    {
        GevStreamChannelSelector_StreamChannel0   //!<Selects stream channel 0 for configuration

    };

    //! Valid values for GevIEEE1588Status
    enum GevIEEE1588StatusEnums
    {
        GevIEEE1588Status_Undefined,  //!<Undefined
        GevIEEE1588Status_Initializing,  //!<Initializing
        GevIEEE1588Status_Faulty,  //!<Faulty
        GevIEEE1588Status_Disabled,  //!<Disabled
        GevIEEE1588Status_Listening,  //!<Listening
        GevIEEE1588Status_PreMaster,  //!<PreMaster
        GevIEEE1588Status_Master,  //!<Master
        GevIEEE1588Status_Passive,  //!<Passive
        GevIEEE1588Status_Uncalibrated,  //!<Uncalibrated
        GevIEEE1588Status_Slave   //!<Slave

    };

    //! Valid values for GevIEEE1588StatusLatched
    enum GevIEEE1588StatusLatchedEnums
    {
        GevIEEE1588StatusLatched_Undefined,  //!<Undefined
        GevIEEE1588StatusLatched_Initializing,  //!<Initializing
        GevIEEE1588StatusLatched_Faulty,  //!<Faulty
        GevIEEE1588StatusLatched_Disabled,  //!<Disabled
        GevIEEE1588StatusLatched_Listening,  //!<Listening
        GevIEEE1588StatusLatched_PreMaster,  //!<PreMaster
        GevIEEE1588StatusLatched_Master,  //!<Master
        GevIEEE1588StatusLatched_Passive,  //!<Passive
        GevIEEE1588StatusLatched_Uncalibrated,  //!<Uncalibrated
        GevIEEE1588StatusLatched_Slave   //!<Slave

    };

    //! Valid values for UserSetSelector
    enum UserSetSelectorEnums
    {
        UserSetSelector_Default,  //!<Selects the default configuration set
        UserSetSelector_HighGain,  //!<High gain factory set
        UserSetSelector_AutoFunctions,  //!<Factory set using auto functions
        UserSetSelector_Color,  //!<Factory set enabling color adjustments
        UserSetSelector_ColorRaw,  //!<Factory set disabling color adjustments
        UserSetSelector_Custom0,  //!<Factory set enabling custom 0 settings
        UserSetSelector_Custom1,  //!<Factory set enabling custom 1 settings
        UserSetSelector_UserSet1,  //!<Selects user set 1
        UserSetSelector_UserSet2,  //!<Selects user set 2
        UserSetSelector_UserSet3,  //!<Selects user set 3
        UserSetSelector_LightMicroscopy   //!<The Light Microscopy factory set can be loaded.

    };

    //! Valid values for UserSetDefaultSelector
    enum UserSetDefaultSelectorEnums
    {
        UserSetDefaultSelector_Default,  //!<Selects the default user set as the default startup set
        UserSetDefaultSelector_HighGain,  //!<Selects the high gain user set as the default startup set.
        UserSetDefaultSelector_AutoFunctions,  //!<Selects the auto function user set as the default startup set.
        UserSetDefaultSelector_Color,  //!<Selects the color user set as the default startup set.
        UserSetDefaultSelector_ColorRaw,  //!<Selects the raw color user set as the default startup set.
        UserSetDefaultSelector_Custom0,  //!<Selects the custom 0 user set as the default startup set.
        UserSetDefaultSelector_Custom1,  //!<Selects the custom 1 user set as the default startup set.
        UserSetDefaultSelector_UserSet1,  //!<Selects user set 1 as the default startup set
        UserSetDefaultSelector_UserSet2,  //!<Selects user set 2 as the default startup set
        UserSetDefaultSelector_UserSet3,  //!<Selects user set 3 as the default startup set
        UserSetDefaultSelector_LightMicroscopy   //!<The Light Microscopy factory set is set as the default startup set.

    };

    //! Valid values for DefaultSetSelector
    enum DefaultSetSelectorEnums
    {
        DefaultSetSelector_Standard,  //!<Standard factory set
        DefaultSetSelector_HighGain,  //!<High gain factory set
        DefaultSetSelector_AutoFunctions,  //!<Factory set using auto functions
        DefaultSetSelector_Color,  //!<Factory set enabling color adjustments
        DefaultSetSelector_ColorRaw,  //!<Factory set disabling color adjustments
        DefaultSetSelector_Custom0,  //!<customer factory set 0
        DefaultSetSelector_Custom1,  //!<customer factory set 1
        DefaultSetSelector_LightMicroscopy   //!<The Light Microscopy factory set is set as the default startup set.

    };

    //! Valid values for AutoFunctionProfile
    enum AutoFunctionProfileEnums
    {
        AutoFunctionProfile_GainMinimum,  //!<Keep gain at minimum
        AutoFunctionProfile_ExposureMinimum,  //!<Exposure Time at minimum
        AutoFunctionProfile_GainMinimumQuick,  //!<Gain time is kept as low as possible and is adjusted quickly.
        AutoFunctionProfile_ExposureMinimumQuick   //!<Exposure time is kept as low as possible and is adjusted quickly.

    };

    //! Valid values for AutoFunctionAOISelector
    enum AutoFunctionAOISelectorEnums
    {
        AutoFunctionAOISelector_AOI1,  //!<Selects Auto Function AOI 1
        AutoFunctionAOISelector_AOI2,  //!<Selects Auto Function AOI 2
        AutoFunctionAOISelector_AOI3,  //!<
        AutoFunctionAOISelector_AOI4,  //!<
        AutoFunctionAOISelector_AOI5,  //!<
        AutoFunctionAOISelector_AOI6,  //!<
        AutoFunctionAOISelector_AOI7,  //!<
        AutoFunctionAOISelector_AOI8   //!<

    };

    //! Valid values for AutoTonalRangeModeSelector
    enum AutoTonalRangeModeSelectorEnums
    {
        AutoTonalRangeModeSelector_ColorAndContrast,  //!<Color and contrast are adjusted.
        AutoTonalRangeModeSelector_Color,  //!<Only color is adjusted.
        AutoTonalRangeModeSelector_Contrast   //!<Only contrast is adjusted.

    };

    //! Valid values for AutoTonalRangeAdjustmentSelector
    enum AutoTonalRangeAdjustmentSelectorEnums
    {
        AutoTonalRangeAdjustmentSelector_DarkAndBright,  //!<The dark and bright end of the tonal range can be adjusted.
        AutoTonalRangeAdjustmentSelector_Bright,  //!<Only the bright end of the tonal range can be adjusted.
        AutoTonalRangeAdjustmentSelector_Dark   //!<Only the dark end of the tonal range can be adjusted.

    };

    //! Valid values for ColorOverexposureCompensationAOISelector
    enum ColorOverexposureCompensationAOISelectorEnums
    {
        ColorOverexposureCompensationAOISelector_AOI1   //!<Selects Color Overexposure Compensation AOI 1

    };

    //! Valid values for ShadingSelector
    enum ShadingSelectorEnums
    {
        ShadingSelector_OffsetShading,  //!<Selects offset shading correction.
        ShadingSelector_GainShading   //!<Selects gain shading correction.

    };

    //! Valid values for ShadingStatus
    enum ShadingStatusEnums
    {
        ShadingStatus_NoError,  //!<Indicates that the latest operation related to shading correction was successful.
        ShadingStatus_StartupSetError,  //!<Indicates that a problem related to the startup shading set occurred.
        ShadingStatus_ActivateError,  //!<Indicates that the selected shading set could not be loaded.
        ShadingStatus_CreateError   //!<Indicates that a problem related to creating a shading set occurred.

    };

    //! Valid values for ShadingSetDefaultSelector
    enum ShadingSetDefaultSelectorEnums
    {
        ShadingSetDefaultSelector_DefaultShadingSet,  //!<Selects the default shading set as the bootup shading set.
        ShadingSetDefaultSelector_UserShadingSet1,  //!<Selects the User Shading Set 1 as the bootup shading set.
        ShadingSetDefaultSelector_UserShadingSet2   //!<Selects the User Shading Set 2 as the bootup shading set.

    };

    //! Valid values for ShadingSetSelector
    enum ShadingSetSelectorEnums
    {
        ShadingSetSelector_DefaultShadingSet,  //!<Selects the default shading set for activation by the activate command.
        ShadingSetSelector_UserShadingSet1,  //!<Selects the User shading Set 1 for activation by the activate command.
        ShadingSetSelector_UserShadingSet2   //!<Selects the User shading Set 2 for activation by the activate command.

    };

    //! Valid values for ShadingSetCreate
    enum ShadingSetCreateEnums
    {
        ShadingSetCreate_Off,  //!<
        ShadingSetCreate_Once   //!<

    };

    //! Valid values for UserDefinedValueSelector
    enum UserDefinedValueSelectorEnums
    {
        UserDefinedValueSelector_Value1,  //!<
        UserDefinedValueSelector_Value2,  //!<
        UserDefinedValueSelector_Value3,  //!<
        UserDefinedValueSelector_Value4,  //!<
        UserDefinedValueSelector_Value5   //!<

    };

    //! Valid values for FeatureSet
    enum FeatureSetEnums
    {
        FeatureSet_Full,  //!<The 'Full' camera description file provides all features.
        FeatureSet_Basic   //!<The 'Basic' camera description file provides nearly all features.

    };

    //! Valid values for DeviceScanType
    enum DeviceScanTypeEnums
    {
        DeviceScanType_Areascan,  //!<Indicates that the device has an area scan type of sensor
        DeviceScanType_Linescan   //!<Indicates that the device has an Line scan type of sensor

    };

    //! Valid values for TemperatureSelector
    enum TemperatureSelectorEnums
    {
        TemperatureSelector_Sensorboard,  //!<Temperature on sensor board
        TemperatureSelector_Coreboard,  //!<Temperature on core board
        TemperatureSelector_Framegrabberboard,  //!<Temperature on framegrabber board
        TemperatureSelector_Case   //!<Temperature on the camera case

    };

    //! Valid values for TemperatureState
    enum TemperatureStateEnums
    {
        TemperatureState_Ok,  //!<Ok
        TemperatureState_Critical,  //!<Critical
        TemperatureState_Error   //!<Error

    };

    //! Valid values for LastError
    enum LastErrorEnums
    {
        LastError_NoError,  //!<Indicates that no error was detected
        LastError_Overtrigger,  //!<Indicates that the camera was overtriggered
        LastError_Userset,  //!<Indicates an error was detected while loading a userset
        LastError_InvalidParameter,  //!<Indicates that a parameter was set to an invalid value
        LastError_OverTemperature,  //!<The over temperature state has been detected
        LastError_PowerFailure,  //!<Indicates that the power supply is not sufficient
        LastError_InsufficientTriggerWidth,  //!<The trigger width was too short.
        LastError_UserDefPixFailure   //!<Indicates an user defect pixel failure

    };

    //! Valid values for ParameterSelector
    enum ParameterSelectorEnums
    {
        ParameterSelector_Gain,  //!<Selects the gain limits for configuration
        ParameterSelector_Brightness,  //!<Selects the brightness limits for configuration
        ParameterSelector_BlackLevel,  //!<Selects the blacklevel limits for configuration
        ParameterSelector_ExposureTime,  //!<Selects the exposure time limits for configuration
        ParameterSelector_Framerate,  //!<Selects the framerate limits for configuration
        ParameterSelector_AutoTargetValue,  //!<Selects the target gray value for atuofunc
        ParameterSelector_ExposureOverhead,  //!<Selects the exposure overhead limits for configuration
        ParameterSelector_ExposureOverlapMax   //!<Selects the exposure overlap time max limit for configuration

    };

    //! Valid values for ExpertFeatureAccessSelector
    enum ExpertFeatureAccessSelectorEnums
    {
        ExpertFeatureAccessSelector_ExpertFeature1_Legacy,  //!<Selects the Expert Feature 1 for configuration
        ExpertFeatureAccessSelector_ExpertFeature1,  //!<Selects the Expert Feature 1 for configuration
        ExpertFeatureAccessSelector_ExpertFeature2,  //!<Selects the Expert Feature 2 for configuration
        ExpertFeatureAccessSelector_ExpertFeature3,  //!<Selects the Expert Feature 3 for configuration
        ExpertFeatureAccessSelector_ExpertFeature4,  //!<Selects the Expert Feature 4 for configuration
        ExpertFeatureAccessSelector_ExpertFeature5,  //!<Selects the Expert Feature 5 for configuration
        ExpertFeatureAccessSelector_ExpertFeature6,  //!<Selects the Expert Feature 6 for configuration
        ExpertFeatureAccessSelector_ExpertFeature7,  //!<Selects the Expert Feature 7 for configuration
        ExpertFeatureAccessSelector_ExpertFeature8,  //!<Expert feature 8 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature9,  //!<Expert feature 9 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature10   //!<Expert feature 10 can be configured.

    };

    //! Valid values for ChunkSelector
    enum ChunkSelectorEnums
    {
        ChunkSelector_Image,  //!<Selects the image chunk for enabling.
        ChunkSelector_OffsetX,  //!<Selects the X offset chunk for enabling.
        ChunkSelector_OffsetY,  //!<Selects the Y offset chunk for enabling.
        ChunkSelector_Width,  //!<Selects the width chunk for enabling.
        ChunkSelector_Height,  //!<Selects the height chunk for enabling.
        ChunkSelector_PixelFormat,  //!<Selects the pixel format chunk for enabling.
        ChunkSelector_DynamicRangeMax,  //!<Selects the dynamic range max chunk for enabling.
        ChunkSelector_DynamicRangeMin,  //!<Selects the dynamic range min chunk for enabling.
        ChunkSelector_Timestamp,  //!<Selects the timestamp chunk for enabling.
        ChunkSelector_LineStatusAll,  //!<Selects the line status all chunk for enabling.
        ChunkSelector_Framecounter,  //!<Selects the frame counter chunk for enabling.
        ChunkSelector_Triggerinputcounter,  //!<Selects the trigger input counter chunk for enabling.
        ChunkSelector_LineTriggerIgnoredCounter,  //!<Selects the line trigger ignored counter chunk for enabling.
        ChunkSelector_FrameTriggerIgnoredCounter,  //!<Selects the frame trigger ignored counter chunk for enabling.
        ChunkSelector_LineTriggerEndToEndCounter,  //!<Selects the line trigger end to end counter chunk for enabling.
        ChunkSelector_FrameTriggerCounter,  //!<Selects the frame trigger counter chunk for enabling.
        ChunkSelector_FramesPerTriggerCounter,  //!<Selects the frame per trigger counter chunk for enabling.
        ChunkSelector_InputStatusAtLineTrigger,  //!<Selects the input status at line trigger chunk for enabling.
        ChunkSelector_ShaftEncoderCounter,  //!<Selects the shaft encoder counter chunk for enabling.
        ChunkSelector_PayloadCRC16,  //!<Selects the CRC checksum chunk for configuration
        ChunkSelector_Stride,  //!<Selects the stride chunk for enabling.
        ChunkSelector_SequenceSetIndex,  //!<Selects the sequence set index chunk for enabling
        ChunkSelector_ExposureTime,  //!<
        ChunkSelector_GainAll,  //!<
        ChunkSelector_BrightPixel,  //!<
        ChunkSelector_VirtLineStatusAll,  //!<Selects the virtual line status all chunk for enabling.
        ChunkSelector_LineTriggerCounter   //!<Selects the Line Trigger Counter chunk for enabling.

    };

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

    //! Valid values for EventSelector
    enum EventSelectorEnums
    {
        EventSelector_ExposureEnd,  //!<Selects the end of exposure event for enabling.
        EventSelector_LineStartOvertrigger,  //!<Selects the line start overtrigger event for enabling.
        EventSelector_FrameStartOvertrigger,  //!<Selects the frame start overtrigger event for enabling.
        EventSelector_AcquisitionStartOvertrigger,  //!<Selects the acquisition start overtrigger event for enabling.
        EventSelector_FrameTimeout,  //!<Selects the frame timeout event for enabling.
        EventSelector_FrameStart,  //!<Selects the frame start trigger event for enabling.
        EventSelector_AcquisitionStart,  //!<Selects the acquisition start trigger event for enabling.
        EventSelector_CriticalTemperature,  //!<Selects the critical temperature event for enabling.
        EventSelector_OverTemperature,  //!<Selects the over temperature event for enabling.
        EventSelector_ActionLate,  //!<TODO
        EventSelector_Line1RisingEdge,  //!<
        EventSelector_Line2RisingEdge,  //!<
        EventSelector_Line3RisingEdge,  //!<
        EventSelector_Line4RisingEdge,  //!<
        EventSelector_VirtualLine1RisingEdge,  //!<
        EventSelector_VirtualLine2RisingEdge,  //!<
        EventSelector_VirtualLine3RisingEdge,  //!<
        EventSelector_VirtualLine4RisingEdge,  //!<
        EventSelector_FrameWait,  //!<Selects the frame wait trigger event for enabling.
        EventSelector_AcquisitionWait,  //!<Selects the acquisition wait trigger event for enabling.
        EventSelector_FrameStartWait,  //!<Event notifications for the frame start wait event can be enabled.
        EventSelector_AcquisitionStartWait,  //!<Event notifications for the acquisition start wait event can be enabled.
        EventSelector_EventOverrun   //!<Selects the event overrun event for enabling.

    };

    //! Valid values for EventNotification
    enum EventNotificationEnums
    {
        EventNotification_Off,  //!<Sets event notification to off
        EventNotification_GenICamEvent,  //!<Sets the event notification type to GenICam event
        EventNotification_On   //!<Sets the enables the event notification.

    };

    //! Valid values for FileSelector
    enum FileSelectorEnums
    {
        FileSelector_UserData,  //!<Selects the file 'User Data'
        FileSelector_UserSet1,  //!<Selects the file 'User Set 1'
        FileSelector_UserSet2,  //!<Selects the file 'User Set 2'
        FileSelector_UserSet3,  //!<Selects the file 'User Set 3'
        FileSelector_UserGainShading1,  //!<Selects the file 'User Gain Shading 1'
        FileSelector_UserGainShading2,  //!<Selects the file 'User Gain Shading 2'
        FileSelector_UserOffsetShading1,  //!<Selects the file 'User Offset Shading 1'
        FileSelector_UserOffsetShading2,  //!<Selects the file 'User Offset Shading 2'
        FileSelector_ExpertFeature7File   //!<Selects the file 'Expert Feature 7 File'

    };

    //! Valid values for FileOperationSelector
    enum FileOperationSelectorEnums
    {
        FileOperationSelector_Open,  //!<Opens the file selected by FileSelector
        FileOperationSelector_Close,  //!<Closes the file selected by FileSelector
        FileOperationSelector_Read,  //!<Reads data from the selected file
        FileOperationSelector_Write   //!<Writes data to the selected file

    };

    //! Valid values for FileOpenMode
    enum FileOpenModeEnums
    {
        FileOpenMode_Read,  //!<Selects read-only open mode
        FileOpenMode_Write   //!<Selects write-only open mode

    };

    //! Valid values for FileOperationStatus
    enum FileOperationStatusEnums
    {
        FileOperationStatus_Success,  //!<Successful file operation
        FileOperationStatus_Failure   //!<Failing file operation

    };

    //! Valid values for ServiceBoardIdSelector
    enum ServiceBoardIdSelectorEnums
    {
        ServiceBoardIdSelector_Coreboard,  //!<
        ServiceBoardIdSelector_Sensorboard,  //!<
        ServiceBoardIdSelector_Framegrabberboard,  //!<
        ServiceBoardIdSelector_Global   //!<

    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************


    //! Basler generic GigEVision camera interface
    class CGigECamera_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS

            //! Constructor
        CGigECamera_Params( void );

        //! Destructor
        ~CGigECamera_Params( void );

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

    //! \name SequenceControl - This category includes items that control the sequencer feature
    //@{
    /*!
        \brief Enables the sequencer

        Enables the existing sequence sets for image acquisition.

        \b Visibility = Expert

    */
        GENAPI_NAMESPACE::IBoolean& SequenceEnable;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Current sequence set

            Indicates the current sequence set.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SequenceCurrentSet;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Enables or disables the sequencer for configuration

            Enables or disables the sequencer for configuration.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<SequenceConfigurationModeEnums >& SequenceConfigurationMode;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Allows asynchronous restart of the sequence of sequence sets

            Allows to restart the sequence of sequence sets to image acquisition, starting with the sequence set of lowest index number. The restart is asynchronous to the cameras's frame trigger. Only available in Auto and Controlled sequence advance mode.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& SequenceAsyncRestart;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Allows asynchronous advance from one sequence set to the next

            Allows to advance from the current sequence set to the next one. The advance is asynchronous to the cameras's frame trigger. Only available in Controlled sequence advance mode.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& SequenceAsyncAdvance;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Total number of sequence sets

            Sets the total number of sequence sets in the sequence.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SequenceSetTotalNumber;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Selects the index number of a sequence set

            Selects the index number of a sequence set.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SequenceSetIndex;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Stores the current sequence set

            Stores the current sequence set as one of the sequence sets of the sequence. Note: Storing the current sequence set will overwrite any already existing sequence set bearing the same index number. Note: The sequence set is stored in the volatile memory and will therefore be lost if the camera is reset or if power is switched off.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& SequenceSetStore;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Loads a sequence set

            Loads an existing sequence set to make it the current sequence set.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& SequenceSetLoad;

        //@}


        //! \name SequenceControl - This category includes items that control the sequencer feature
        //@{
        /*!
            \brief Sets the number of sequence set executions

            Sets the number of consecutive executions per sequence cycle for the selected sequence set. Only available in Auto sequence advance mode.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& SequenceSetExecutions;

        //@}


        //! \name SequenceControlConfiguration - This category includes items that control the sequence set advance
        //@{
        /*!
            \brief Selects the sequence set advance mode

            Selects the sequence set advance mode. Possible values: Auto - automatic sequence set advance as images are acquired. Controlled - sequence set advance controlled by settable source. Free selection - the sequence sets are selected according to the states of the input lines.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<SequenceAdvanceModeEnums >& SequenceAdvanceMode;

        //@}


        //! \name SequenceControlConfiguration - This category includes items that control the sequence set advance
        //@{
        /*!
            \brief Selects between sequence restart or sequence set advance

            Selects between controls for sequence restart or sequence set advance.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<SequenceControlSelectorEnums >& SequenceControlSelector;

        //@}


        //! \name SequenceControlConfiguration - This category includes items that control the sequence set advance
        //@{
        /*!
            \brief Selects the source for sequence control

            Selects the source for sequence control. Possible values: Disabled - advance via asynchronous advance. Always Active - automatic sequence set advance. The sequence repeat starts with sequence set index number 1. Line N - the source for sequence restart or sequence set advance is line N. CCN - the source for sequence restart or sequence set advance is CCN.

            \b Visibility = Guru

            \b Selected by : SequenceControlSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<SequenceControlSourceEnums >& SequenceControlSource;

        //@}


        //! \name SequenceControlConfiguration - This category includes items that control the sequence set advance
        //@{
        /*!
            \brief Selects a bit of the sequence set address

            Selects a bit of the sequence set address.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<SequenceAddressBitSelectorEnums >& SequenceAddressBitSelector;

        //@}


        //! \name SequenceControlConfiguration - This category includes items that control the sequence set advance
        //@{
        /*!
            \brief Selects the source for the selected bit of the sequence set address

            Selects the source for setting the selected bit of the sequence set address.

            \b Visibility = Guru

            \b Selected by : SequenceAddressBitSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<SequenceAddressBitSourceEnums >& SequenceAddressBitSource;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Gain Auto is the 'automatic' counterpart of the manual gain feature.

            The gain auto function automatically adjusts the Auto Gain Raw parameter value within set limits, until a target average gray value for the pixel data from Auto Function AOI1 is reached.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<GainAutoEnums >& GainAuto;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Selects the gain control to configure. Once a gain control has been selected, all changes to the gain settings will be applied to the selected control.

            This enumeration selects the gain control to configure. Once a gain control has been selected, all changes to the gain settings will be applied to the selected control.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<GainSelectorEnums >& GainSelector;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief This is an integer value that sets the selected gain control in device specific units

            Sets the 'raw' value of the selected gain control. The 'raw' value is an integer value that sets the selected gain control in units specific to the camera.

            \b Visibility = Beginner


            \b Selected by : GainSelector

        */
        GENAPI_NAMESPACE::IInteger& GainRaw;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief This is a float value that sets the selected gain control in dB

            Sets the 'absolute' value of the selected gain control. The 'absolute' value is a float value that sets the selected gain control in dB.

            \b Visibility = Beginner


            \b Selected by : GainSelector

        */
        GENAPI_NAMESPACE::IFloat& GainAbs;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Selcts a black level control to configure. Once a black level control has been selected, all changes to the black level settings will be applied to the selected control.

            This enumeration selects the black level control to configure. Once a black level control has been selected, all changes to the black level settings will be applied to the selected control.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BlackLevelSelectorEnums >& BlackLevelSelector;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Sets the value of the selected black level control as an integer

            This value sets the selected black level control as an integer.

            \b Visibility = Beginner


            \b Selected by : BlackLevelSelector

        */
        GENAPI_NAMESPACE::IInteger& BlackLevelRaw;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Sets the value of the selected black level control as a float

            This value sets the selected black level control as a float value.

            \b Visibility = Beginner


            \b Selected by : BlackLevelSelector

        */
        GENAPI_NAMESPACE::IFloat& BlackLevelAbs;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Enables the gamma correction

            This boolean value enables the gamma correction.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& GammaEnable;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief

            This enumeration selects the type of gamma to apply.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<GammaSelectorEnums >& GammaSelector;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief This feature is used to perform gamma correction of pixel intensity.

            This feature is used to perform gamma correction of pixel  intensity. This is typically used to compensate for non-linearity of the display system (such as CRT).

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& Gamma;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Sets the value of the selected digital shift control

            This value sets the selected digital shift control

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& DigitalShift;

        //@}


        //! \name AnalogControls - This category includes items that control the analog characteristics of the video signal
        //@{
        /*!
            \brief Sets the substrate voltage

            This value sets the substrate voltage

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SubstrateVoltage;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief This feature selects the amount of data bits the sensor produces for one sample.

            This feature selects the amount of data bits the sensor produces for one sample.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<SensorBitDepthEnums >& SensorBitDepth;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief This feature represents the number of digitized samples outputted simultaneously by the camera A/D conversion stage.

            This feature represents the number of digitized samples output simultaneously by the camera A/D conversion stage.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<SensorDigitizationTapsEnums >& SensorDigitizationTaps;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Sets the format of the pixel data transmitted for acquired images

            This enumeration sets the format of the pixel data transmitted for acquired images.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<PixelFormatEnums >& PixelFormat;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Sets the color coding of the pixels in the acquired images



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<PixelCodingEnums >& PixelCoding;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Indicates the depth of the pixel values in the image in bits per pixel

            This is a read only feature. This enumeration provides a list of values that indicate the depth of the pixel values in the acquired images in bits per pixel. This value will always be coherent with the pixel format setting.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<PixelSizeEnums >& PixelSize;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Indicates the alignment of the camera's Bayer filter to the pixels in the acquired images

             This is a read only feature. This enumeration provides a list of values that indicate the alignment of the camera's Bayer filter to the pixels in the acquired images.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<PixelColorFilterEnums >& PixelColorFilter;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Enables color improved RGB raw output

            Enables color improvement of RGB data and provides for their output as RGB raw data. Only available for cameras with an RGB Bayer filter.
    Note: Make sure to also select a suitable raw pixel data output format.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& ProcessedRawEnable;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Indicates the minimum possible pixel value that could be transferred from the camera

            This a read only feature. It indicates the minimum possible pixel value that could be transferred from the camera.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& PixelDynamicRangeMin;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Indicates the maximum possible pixel value that could be transferred from the camera

            This a read only feature. It indicates the maximum possible pixel value that could be transferred from the camera.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& PixelDynamicRangeMax;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Specifies the direction of imaging and the separation (consecutive numbers) of related line captures.

            Specifies the direction of imaging and the separation (consecutive numbers) of related line captures. Related line captures will be combined.

    Positive integer: The object will pass the top sensor line first.

    Negative integer: The object will pass the bottom sensor line first.

    In color cameras, the top sensor line is the green line, and the bottom sensor line is the blue line.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SpatialCorrection;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief



            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& SpatialCorrectionAmount;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief



            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IEnumerationT<SpatialCorrectionStartingLineEnums >& SpatialCorrectionStartingLine;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Enables the horizontal flipping of the image.

            This feature is used to flip horizontally the image sent by the device. The AOI is applied after the flipping.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& ReverseX;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Enables the vertical flipping of the image.

            This feature is used to flip vertically the image sent by the device. The AOI is applied after the flipping.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& ReverseY;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Selects the mode to output the fields.

            Selects the mode to output the fields.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<FieldOutputModeEnums >& FieldOutputMode;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Selecting a test image from the list will enable the test image

            This enumeration provides a list of the available test images. Selecting a test image from the list will enable the test image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TestImageSelectorEnums >& TestImageSelector;

        //@}


        //! \name ImageFormat - This category includes items that control the size of the acquired image and the format of the transferred pixel data
        //@{
        /*!
            \brief Holds all moving test images at their starting position.

            Holds all moving test images at their starting position. All test images will be displayed at their starting positions and will stay fixed.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& TestImageResetAndHold;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the width of the camera's sensor in pixels

            This is a read only element. It is an integer that indicates the actual width of the camera's sensor in pixels.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SensorWidth;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the height of the camera's sensor in pixels.

            This is a read only element. It is an integer that indicates the actual height of the camera's sensor in pixels.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SensorHeight;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the maximum allowed width of the image in pixels

            This is a read only element. It is an integer that indicates maximum allowed width of the image in pixels taking into account any function that may limit the allowed width.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& WidthMax;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the maximum allowed height of the image in pixels

            This is a read only element. It is an integer that indicates maximum allowed height of the image in pixels taking into account any function that may limit the allowed height.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& HeightMax;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Selects the type of light source to be considered for matrix color transformation

            Selects the color transformation mode to select the type of light source to be considered for matrix color transformation.

            \b Visibility = Expert

            \b Selected by : ColorTransformationSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LightSourceSelectorEnums >& LightSourceSelector;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Allows returning to previous settings

            Allows returning to the color adjustment settings extant before the latest changes of the settings.
    This allows you undoing the latest unwanted changes of the color adjustment settings and returning to the preceding settings.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& BalanceWhiteReset;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Balance White Auto is the 'automatic' counterpart of the manual white balance feature.

            The automatic white balance is a two-step process: First, the Balance Ratio Abs parameter values for red, green, and blue are each set to 1.5. Then, assuming a 'grey world' model, the Balance Ratio Abs parameter values are adjusted such that the average gray values for the 'red' and 'blue' pixels match the average gray value for the 'green' pixels.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BalanceWhiteAutoEnums >& BalanceWhiteAuto;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Selects a balance ratio to configure. Once a balance ratio control has been selected, all changes to the balance ratio settings will be applied to the selected control.

            This enumeration selects a balance ratio control to configuration. Once a balance ratio control has been selected, all changes to the balance ratio settings will be applied to the selected control.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BalanceRatioSelectorEnums >& BalanceRatioSelector;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Sets the value of the selected balance ratio control as a float

            This value sets the selected balance ratio control as a float value.

            \b Visibility = Beginner


            \b Selected by : BalanceRatioSelector

        */
        GENAPI_NAMESPACE::IFloat& BalanceRatioAbs;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Sets the value of the selected balance ratio control as an integer

            This value sets the selected balance ratio control as an integer.

            \b Visibility = Beginner


            \b Selected by : BalanceRatioSelector

        */
        GENAPI_NAMESPACE::IInteger& BalanceRatioRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Selects the matrix color transformation between color spaces

            Selects the matrix color transformation between color spaces.
    Generally, the related color spaces are used for internal processing: The color signals provided by the sensor are transformed to the RGB color space to allow further transformations (to account for the type of light source, for color adjustment, for white balance, etc.).
    The color transformation selected here does not refer to the color space selected for the transmission of image data out of the camera.


            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<ColorTransformationSelectorEnums >& ColorTransformationSelector;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Selects the element to be entered in the color transformation matrix.

            Selects the element to be entered in the 3 x 3 color transformation matrix for custom matrix color transformation.
    Note: Depending on the camera model, some elements in the color transformation matrix may be preset and can not be changed.


            \b Visibility = Guru

            \b Selected by : ColorTransformationSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ColorTransformationValueSelectorEnums >& ColorTransformationValueSelector;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Sets a floating point value for the selected element in the color transformation matrix

            Sets a floating point value for the selected element in the color transformation matrix.

            \b Visibility = Guru

            \b Selected by : ColorTransformationSelector, ColorTransformationValueSelector

        */
        GENAPI_NAMESPACE::IFloat& ColorTransformationValue;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Sets an integer value for the selected element in the color transformation matrix

            Sets an integer value for the selected element in the color transformation matrix.

            \b Visibility = Guru

            \b Selected by : ColorTransformationValueSelector

        */
        GENAPI_NAMESPACE::IInteger& ColorTransformationValueRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Defines the extent to which the selected light source will be considered (float)

            Sets a floating point value to define the extent to which the selected light source will be considered in color matrix transformation.
    If the value is set to 1 the selected light source will be fully considered. If the value is set to 0 the selected light source will not be considered.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IFloat& ColorTransformationMatrixFactor;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Defines the extent to which the selected light source will be considered (integer)

            Sets an integer value to define the extent to which the selected light source will be considered in color matrix transformation. If the value is set to 65536 the selected light source will be fully considered. If the value is set to 0 the selected light source will not be considered.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& ColorTransformationMatrixFactorRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Enables color adjustment

            Enables color adjustment.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& ColorAdjustmentEnable;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Allows returning to previous settings

            Allows returning to the color adjustment settings extant before the latest changes of the settings.
    This allows you undoing the latest unwanted changes of the color adjustment settings and returning to the preceding settings.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& ColorAdjustmentReset;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Selects the color for color adjustment

            Selects the color for color adjustment.
    Those colors in the image will be adjusted where the selected color predominates.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ColorAdjustmentSelectorEnums >& ColorAdjustmentSelector;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Adjustment of hue of the selected color (float)

            Sets a floating point value for the adjustment of hue of the selected color.

            \b Visibility = Expert

            \b Selected by : ColorAdjustmentSelector

        */
        GENAPI_NAMESPACE::IFloat& ColorAdjustmentHue;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Adjustment of hue of the selected color (integer)

            Sets an integer value for the adjustment of hue of the selected color.

            \b Visibility = Expert

            \b Selected by : ColorAdjustmentSelector

        */
        GENAPI_NAMESPACE::IInteger& ColorAdjustmentHueRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Adjustment of saturation of the selected color (float)

            Sets a floating point value for the adjustment of saturation of the selected color.

            \b Visibility = Expert

            \b Selected by : ColorAdjustmentSelector

        */
        GENAPI_NAMESPACE::IFloat& ColorAdjustmentSaturation;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Adjustment of saturation of the selected color (integer)

            Sets an integer value for the adjustment of saturation of the selected color.

            \b Visibility = Expert

            \b Selected by : ColorAdjustmentSelector

        */
        GENAPI_NAMESPACE::IInteger& ColorAdjustmentSaturationRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Hue shift to be applied.

            Adjusting the hue shifts the colors of the image. This can be useful, e.g., for correcting minor color shifts or creating false-color images.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& BslHue;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Hue shift to be applied.

            Adjusting the hue shifts the colors of the image. This can be useful, e.g., for correcting minor color shifts or creating false-color images.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& BslHueRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Saturation to be applied.

            Adjusting the saturation changes the intensity of the colors. A higher saturation, for example, makes colors easier to distinguish.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& BslSaturation;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Saturation to be applied.

            Adjusting the saturation changes the intensity of the colors. A higher saturation, for example, makes colors easier to distinguish.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& BslSaturationRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Brightness to be applied.

            Adjusting the brightness lightens or darkens the entire image.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& BslBrightness;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Brightness to be applied.

            Adjusting the brightness lightens or darkens the entire image.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& BslBrightnessRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Contrast to be applied.

            Adjusting the contrast increases the difference between light and dark areas in the image.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& BslContrast;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Contrast to be applied.

            Adjusting the contrast increases the difference between light and dark areas in the image.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& BslContrastRaw;

        //@}


        //! \name ImageQualityControl - This category includes items that control image quality.
        //@{
        /*!
            \brief Sets the Contrast Mode.

            Sets the Contrast Mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BslContrastModeEnums >& BslContrastMode;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm.
        //@{
        /*!
            \brief Sets the demosaicing mode.

            Sets the demosaicing mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<DemosaicingModeEnums >& DemosaicingMode;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm.
        //@{
        /*!
            \brief Enables Basler PGI image optimizations.

            Enables Basler PGI image optimizations.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<PgiModeEnums >& PgiMode;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm.
        //@{
        /*!
            \brief Amount of noise reduction to apply.

            Amount of noise reduction to apply. The higher the value, the less chroma noise will be visible in your images. However, too high values may result in image information loss. To enable this feature, the DemosaicingMode parameter must be set to BaslerPGI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& NoiseReductionAbs;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm.
        //@{
        /*!
            \brief Amount of noise reduction to apply.

            Amount of noise reduction to apply. The higher the value, the less chroma noise will be visible in your images. However, too high values may result in image information loss. To enable this feature, the DemosaicingMode parameter must be set to BaslerPGI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& NoiseReductionRaw;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm.
        //@{
        /*!
            \brief Amount of sharpening to apply.

            Amount of sharpening to apply. The higher the sharpness, the more distinct the image subject's contours will be. However, too high values may result in image information loss. To enable this feature, the DemosaicingMode parameter must be set to BaslerPGI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& SharpnessEnhancementAbs;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm.
        //@{
        /*!
            \brief Amount of sharpening to apply.

            Amount of sharpening to apply. The higher the sharpness, the more distinct the image subject's contours will be. However, too high values may result in image information loss. To enable this feature, the DemosaicingMode parameter must be set to BaslerPGI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SharpnessEnhancementRaw;

        //@}


        //! \name TonalRangeControl - Contains parameters for tonal range adjustments.
        //@{
        /*!
            \brief Sets whether tonal range adjustment is used.

            Sets whether tonal range adjustment is used.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TonalRangeEnableEnums >& TonalRangeEnable;

        //@}


        //! \name TonalRangeControl - Contains parameters for tonal range adjustments.
        //@{
        /*!
            \brief Sets the operation mode of the Tonal Range Auto auto function.

            Sets the operation mode of the Tonal Range Auto auto function.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TonalRangeAutoEnums >& TonalRangeAuto;

        //@}


        //! \name TonalRangeControl - Contains parameters for tonal range adjustments.
        //@{
        /*!
            \brief Sets which pixel values are used for tonal range adjustments.

            Sets which pixel values are used for tonal range adjustments.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<TonalRangeSelectorEnums >& TonalRangeSelector;

        //@}


        //! \name TonalRangeControl - Contains parameters for tonal range adjustments.
        //@{
        /*!
            \brief Source value for tonal range adjustments at the bright end of the tonal range.

            Source value for tonal range adjustments at the bright end of the tonal range. When tonal range adjustments are enabled, the source and target values are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeSourceBright;

        //@}


        //! \name TonalRangeControl - Contains parameters for tonal range adjustments.
        //@{
        /*!
            \brief Source value for tonal range adjustments at the dark end of the tonal range.

            Source value for tonal range adjustments at the dark end of the tonal range. When tonal range adjustments are enabled, the source and target values are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeSourceDark;

        //@}


        //! \name TonalRangeControl - Contains parameters for tonal range adjustments.
        //@{
        /*!
            \brief Target value at the dark end of the tonal range to which pixel values should be mapped during tonal range adjustments.

            Target value at the dark end of the tonal range to which pixel values should be mapped during tonal range adjustments. When tonal range adjuments are enabled, the source and target values at the bright end are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeTargetBright;

        //@}


        //! \name TonalRangeControl - Contains parameters for tonal range adjustments.
        //@{
        /*!
            \brief Target value at the bright end of the tonal range to which pixel values should be mapped during tonal range adjustments.

            Target value at the bright end of the tonal range to which pixel values should be mapped during tonal range adjustments. When tonal range adjustments are enabled, the source and target values at the dark end are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeTargetDark;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the width of the area of interest in pixels

            This value sets the width of the area of interest in pixels.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Width;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the height of the area of interest in pixels

            This value sets the height of the area of interest in pixels.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Height;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the X offset (left offset) of the area of interest in pixels

            This value sets the X offset (left offset) for the area of interest in pixels, i.e., the distance in pixels between the left side of the sensor and the left side of the image area.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& OffsetX;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the Y offset (top offset) for the area of interest in pixels

            This value sets the Y offset (top offset) for the area of interest, i.e., the distance in pixels between the top of the sensor and the top of the image area.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& OffsetY;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Enables the horizontal centering of the image.

            This feature is used to center the image horizontally.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& CenterX;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Enables the vertical centering of the image.

            This feature is used to center the image vertically.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& CenterY;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the vertical binning feature

            This enumeration sets the vertical binning feature.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<LegacyBinningVerticalEnums >& LegacyBinningVertical;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the horizontal binning mode.

            This enumeration sets the horizontal binning mode.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<BinningHorizontalModeEnums >& BinningHorizontalMode;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the horizontal binning mode

            This enumeration sets the horizontal binning mode.

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IEnumerationT<BinningModeHorizontalEnums >& BinningModeHorizontal;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the number of adjacent horizontal pixes to be summed

            Sets the number of binned adjacent horizontal pixels. Their charges will be summed and reported out of the camera as a single pixel.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& BinningHorizontal;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the vertical binning mode.

            This enumeration sets the vertical binning mode.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<BinningVerticalModeEnums >& BinningVerticalMode;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the vertical binning mode

            This enumeration sets the vertical binning mode.

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IEnumerationT<BinningModeVerticalEnums >& BinningModeVertical;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets the number of adjacent vertical pixes to be summed

            Sets the number of binned adjacent vertical pixels. Their charges will be summed and reported out of the camera as a single pixel.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& BinningVertical;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets horizontal sub-sampling

            Horizontal sub-sampling of the image. This has the net effect of reducing the horizontal resolution (width) of the image by the specified horizontal decimation factor. A value of 1 indicates that the camera performs no horizontal decimation.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& DecimationHorizontal;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets vertical sub-sampling

            Vertical sub-sampling of the image. This has the net effect of reducing the vertical resolution (height) of the image by the specified vertical decimation factor. A value of 1 indicates that the camera performs no vertical decimation.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& DecimationVertical;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets vertical scaling factor

            This is a float value that sets the vertical scaling factor of the image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ScalingHorizontalAbs;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets vertical scaling factor

            This is a float value that sets the vertical scaling factor of the image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ScalingVerticalAbs;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets a ROI zone

            Sets a ROI zone to be enabled, configured, and assembled with other ROI zones.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ROIZoneSelectorEnums >& ROIZoneSelector;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Provides for enabling/disabling a ROI zone.

            Provides for enabling/disabling the previously set ROI zone.

            \b Visibility = Expert

            \b Selected by : ROIZoneSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ROIZoneModeEnums >& ROIZoneMode;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets a ROI zone size

            Sets the ROI zone 'thickness' (pixels, in direction of assembly) for the previously enabled ROI zone. Equivalent to Height for vertical zones.

            \b Visibility = Expert

            \b Selected by : ROIZoneSelector

        */
        GENAPI_NAMESPACE::IInteger& ROIZoneSize;

        //@}


        //! \name AOI - This category includes items used to set the size and position of the area of interest
        //@{
        /*!
            \brief Sets a ROI zone offset

            Sets the ROI zone offset (pixels, in direction of assembly) for the previously enabled ROI zone. Equivalent to OffsetY for vertical zones.

            \b Visibility = Expert

            \b Selected by : ROIZoneSelector

        */
        GENAPI_NAMESPACE::IInteger& ROIZoneOffset;

        //@}


        //! \name StackedZoneImaging -
        //@{
        /*!
            \brief Enables the stacked zone imaging feature.

            Enables the stacked zone imaging feature.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& StackedZoneImagingEnable;

        //@}


        //! \name StackedZoneImaging -
        //@{
        /*!
            \brief This value sets the zone to access.

            This value sets the zone to access.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& StackedZoneImagingIndex;

        //@}


        //! \name StackedZoneImaging -
        //@{
        /*!
            \brief Enables the selected zone.

            Enables the selected zone.

            \b Visibility = Beginner


            \b Selected by : StackedZoneImagingIndex

        */
        GENAPI_NAMESPACE::IBoolean& StackedZoneImagingZoneEnable;

        //@}


        //! \name StackedZoneImaging -
        //@{
        /*!
            \brief Sets the Y offset (top offset) for the selected zone.

            Sets the Y offset (top offset) for the selected zone.

            \b Visibility = Beginner


            \b Selected by : StackedZoneImagingIndex

        */
        GENAPI_NAMESPACE::IInteger& StackedZoneImagingZoneOffsetY;

        //@}


        //! \name StackedZoneImaging -
        //@{
        /*!
            \brief Sets the height for the selected zone.

            Sets the height for the selected zone.

            \b Visibility = Beginner


            \b Selected by : StackedZoneImagingIndex

        */
        GENAPI_NAMESPACE::IInteger& StackedZoneImagingZoneHeight;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief When enabled, the maximum frame rate does not depend on the image transfer rate out of the camera.

            When enabled, the maximum frame rate onyl depends on sensor timing and timing of the trigger sequence, and not on the image transfer rate out of the camera.

    Note: The maximum number of triggers within a burst sequence is limited. If the maximum number is exceeded, images may be damaged or lost.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& EnableBurstAcquisition;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the image acquisition mode

            This enumeration sets the image acquisition mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<AcquisitionModeEnums >& AcquisitionMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Starts the acquisition of images

            This command starts the acquisition of images. If the camera is set for single frame acquisition, it will start acquisition of one frame. If the camera is set for continuous frame acquisition, it will start continuous acquisition of frames.

            \b Visibility = Beginner


            \b Selected by : AcquisitionMode

        */
        GENAPI_NAMESPACE::ICommand& AcquisitionStart;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Stops the acquisition of images

            If the camera is set for continuous image acquisition and acquisition has been started, this command stops the acquisition of images.

            \b Visibility = Beginner


            \b Selected by : AcquisitionMode

        */
        GENAPI_NAMESPACE::ICommand& AcquisitionStop;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Immediately aborts the acquisition of images

            This command will immediately abort any image acquisition process that is currently in progress.

            \b Visibility = Beginner


            \b Selected by : AcquisitionMode

        */
        GENAPI_NAMESPACE::ICommand& AcquisitionAbort;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the number of frames acquired in the multiframe acquisition mode

            This value sets the number of frames acquired in the multiframe acquisition mode

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionFrameCount;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerControlImplementationEnums >& TriggerControlImplementation;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Selects the trigger type to configure. Once a trigger type has been selected, all changes to the trigger settings will be applied to the selected trigger.

            This enumeration selects the trigger type to configure. Once a trigger type has been selected, all changes to the trigger settings will be applied to the selected trigger.

            \b Visibility = Beginner


            \b Selected by : TriggerControlImplementation

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerSelectorEnums >& TriggerSelector;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the mode for the selected trigger

            This enumeration sets the trigger mode for the selected trigger.

            \b Visibility = Beginner


            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerModeEnums >& TriggerMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Generates a software trigger signal that is used when the trigger source is set to 'software'

            This command generates a software trigger signal. The software trigger signal will be used if the trigger source is set to 'software'.

            \b Visibility = Beginner


            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::ICommand& TriggerSoftware;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the signal source for the selected trigger

            This enumeration sets the signal source for the selected trigger.

            \b Visibility = Beginner


            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerSourceEnums >& TriggerSource;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the signal transition needed to activate the selected trigger

            This enumeration sets the signal transition needed to activate the selected trigger.

            \b Visibility = Beginner


            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerActivationEnums >& TriggerActivation;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Determines whether a partial or complete frame is transmitted when the frame start trigger prematurely transitions.

            This feature determines whether a partial or a complete frame is transmitted when the frame start trigger is used with Level High or Level Low and when the frame start trigger signal transitions while the frame is still being acquired.

            \b Visibility = Expert

            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IBoolean& TriggerPartialClosingFrame;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Selects the kind of trigger delay.

            Selects wheter trigger delay is defined as a time interval or as a number of consecutive line triggers.

            \b Visibility = Expert

            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerDelaySourceEnums >& TriggerDelaySource;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the trigger delay time in microseconds.

            This float value sets the absolute trigger delay in microseconds to apply after the trigger reception before effectively activating it.

            \b Visibility = Expert

            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IFloat& TriggerDelayAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the trigger delay expressed as number of line triggers.

            This integer value sets the trigger delay expressed as a number of consecutive line triggers to apply after the trigger reception before effectively activating it.

            \b Visibility = Expert

            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IInteger& TriggerDelayLineTriggerCount;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ExposureStartDelayAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ExposureStartDelayRaw;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the exposure mode

            This enumeration sets the exposure mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureModeEnums >& ExposureMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Selects the Interlaced Integration Mode.

            Selects the Interlaced Integration Mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<InterlacedIntegrationModeEnums >& InterlacedIntegrationMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Exposure Auto is the 'automatic' counterpart to manually setting an 'absolute' exposure time.

            The exposure auto function automatically adjusts the Auto Exposure Time Abs parameter value within set limits, until a target average gray value for the pixel data of the related Auto Function AOI is reached.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureAutoEnums >& ExposureAuto;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the exposure time mode.

            Sets the exposure time mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureTimeModeEnums >& ExposureTimeMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Directly sets the camera's exposure time in microseconds

            This float value sets the camera's exposure time in microseconds.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ExposureTimeAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the time base (in microseconds) that is used when the exposure time is set with the 'exposure time raw' setting

            This float value sets the time base (in microseconds) that is used when the exposure time is set with the 'raw' setting.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ExposureTimeBaseAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Enables the use of the exposure time base

            This value enables the use of the exposure time base.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& ExposureTimeBaseAbsEnable;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the 'raw' exposure time.  Actual exposure time = raw exposure setting  x  exposure time base abs setting

            This value sets an integer that will be used as a multiplier for the exposure timebase. The actual exposure time equals the current exposure time raw setting times the current exposure time base abs setting.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ExposureTimeRaw;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Indicates the sensor readout time given the current settings.

            Indicates the sensor readout time given the current settings.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& ReadoutTimeAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Selects the Exposure Overlap Time Mode.

            Selects the manual or automatic control of the maximum overlap between immediately succeeding image acquisitions.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureOverlapTimeModeEnums >& ExposureOverlapTimeMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the maximum overlap of the sensor exposure with sensor readout in TriggerWidth exposure mode in microseconds

            This float value sets the maximum overlap time (in microseconds) of the sensor exposure with sensor readout in TriggerWidth exposure mode.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IFloat& ExposureOverlapTimeMaxAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the maximum overlap of the sensor exposure with the sensor readout in TriggerWidth exposure mode in raw units.

            This integer value sets the maximum overlap time (in raw units) of the sensor exposure with sensor readout in TriggerWidth exposure mode.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& ExposureOverlapTimeMaxRaw;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Enable the Global Reset Release Mode



            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IBoolean& GlobalResetReleaseModeEnable;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the shutter mode

            This enumeration sets the shutter mode.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ShutterModeEnums >& ShutterMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the readout mode of the device

            Sets the readout mode of the device

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<SensorReadoutModeEnums >& SensorReadoutMode;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the camera's acquisition line rate in lines per second

            Sets the 'absolute' value of the acquisition line rate. The 'absolute' value is a float value that sets the acquisition line rate in lines per second.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AcquisitionLineRateAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Indicates the minimum allowed line acquisition period (in microseconds) given the current settings for the area of interest, exposure time, and bandwidth

            Indicates the 'absolute' value of the minimum allowed acquisition line period. The 'absolute' value is a float value that indicates the minimum allowed acquisition line period in microseconds given the current settings for the area of interest, exposure time, and bandwidth.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IFloat& ResultingLinePeriodAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Indicates the maximum allowed line acquisition rate (in lines per second) given the current settings for the area of interest, exposure time, and bandwidth

            Indicates the 'absolute' value of the maximum allowed acquisition line rate. The 'absolute' value is a float value that indicates the maximum allowed acquisition line rate in lines per second given the current settings for the area of interest, exposure time, and bandwidth.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ResultingLineRateAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Enables setting the camera's acquisition frame rate to a specified value

            This boolean value enables setting  the camera's acquisition frame rate to a specified value.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& AcquisitionFrameRateEnable;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief If the acquisition frame rate feature is enabled, this value sets the camera's acquisition frame rate in frames per second

            Sets the 'absolute' value of the acquisition frame rate. The 'absolute' value is a float value that sets the acquisition frame rate in frames per second.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AcquisitionFrameRateAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Indicates the minimum allowed frame acquisition period (in microseconds) given the current settings for the area of interest, exposure time, and bandwidth

            Indicates the 'absolute' value of the minimum allowed acquisition frame period. The 'absolute' value is a float value that indicates the minimum allowed acquisition frame period in microseconds given the current settings for the area of interest, exposure time, and bandwidth.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IFloat& ResultingFramePeriodAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Indicates the maximum allowed frame acquisition rate (in frames per second) given the current settings for the area of interest, exposure time, and bandwidth

            Indicates the 'absolute' value of the maximum allowed acquisition frame rate. The 'absolute' value is a float value that indicates the maximum allowed acquisition frame rate in frames per second given the current settings for the area of interest, exposure time, and bandwidth.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ResultingFrameRateAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief This enumeration is used to select which internal acquisition signal to read using AcquisitionStatus.

            This enumeration is used to select which internal acquisition signal to read using AcquisitionStatus.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<AcquisitionStatusSelectorEnums >& AcquisitionStatusSelector;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Reads the selected acquisition status

            This feature is used to read the state (True or False) of the internal acquisition signal selected using AcquisitionStatusSelector.

            \b Visibility = Expert

            \b Selected by : AcquisitionStatusSelector

        */
        GENAPI_NAMESPACE::IBoolean& AcquisitionStatus;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Enables the frame timeout

            This boolean value enables the frame timeout.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& FrameTimeoutEnable;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Sets the frame timeout in microseconds.

            Sets the frame timeout in microseconds. When the timeout expires before a frame acquisition is complete, a partial frame will be delivered.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& FrameTimeoutAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Enables the synchronous free run mode

            When enabled the camera triggers with the specified frame rate derived from the synchronized clock.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& SyncFreeRunTimerEnable;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Synchronous free run trigger start time (low 32 bits)

            Low 32 bits of the synchronous free run trigger start time.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SyncFreeRunTimerStartTimeLow;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Synchronous free run trigger start time (high 32 bits)

            High 32 bits of the synchronous free run trigger start time.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SyncFreeRunTimerStartTimeHigh;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Synchronous free run trigger rate

            Trigger rate for the clock synchronous trigger.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& SyncFreeRunTimerTriggerRateAbs;

        //@}


        //! \name AcquisitionTrigger - This category includes items used to set the image acquisition parameters and to start and stop acquisition
        //@{
        /*!
            \brief Activates the synchronous free run trigger settings

            Activates changed settings for the synchronous free run.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::ICommand& SyncFreeRunTimerUpdate;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Selects the I/O line to configure. Once a line has been selected, all changes to the line settings will be applied to the selected line.

            This enumeration selects the I/O line to configure. Once a line has been selected, all changes to the line settings will be applied to the selected line.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<LineSelectorEnums >& LineSelector;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the mode for the selected line

            This feature controls whether the physical Line is used to Input or Output a signal. When a Line supports input and output mode, the default state is Input to avoid possible electrical contention. Line Mode can take any of the following values: Input: The selected physical line is used to input an electrical signal. Output: The selected physical line is used to output an electrical signal.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LineModeEnums >& LineMode;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<LineLogicEnums >& LineLogic;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the electrical configuration of the selected line

            This feature controls the current electrical format of the selected physical input or output Line. Line Format can take any of the following values: No Connect: The Line is not connected. Tri-state: The Line is currently in Tri-state mode (Not driven). TTL: The Line is currently accepting or sending TTL level signals. LVDS: The Line is currently accepting or sending LVDS level signals. RS-422: The Line is currently accepting or sending RS-422 level signals. Opto-coupled: The Line is Opto-coupled.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LineFormatEnums >& LineFormat;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the source signal for the selected line (if the selected line is an output)

            This enumeration selects the internally generated camera signal (source signal) for the selected line when the selected line is an output.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LineSourceEnums >& LineSource;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Enables the signal inverter function for the selected input or output line.

            This boolean value enables the signal inverter function for the selected input or output line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IBoolean& LineInverter;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Enables the termination resistor for the selected input line.

            This boolean value enables the termination resistor for the selected input line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IBoolean& LineTermination;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the absolute value of the selected line debouncer time in microseconds

            Sets the absolute value of the selected line debouncer time in microseconds

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IFloat& LineDebouncerTimeAbs;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the raw value of the selected line debouncer time

            Sets the raw value of the selected line debouncer time

            \b Visibility = Invisible

            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IInteger& LineDebouncerTimeRaw;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the raw value for the minimum signal width of an output signal.

            This integer value sets the raw value  for the minimum signal width of a signal that is received from the frequency converter or from the shaft encoder module and that is associated with a digital output line.

            \b Visibility = Invisible

            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IInteger& MinOutPulseWidthRaw;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the absolute value (in microseconds) for the minimum signal width of an output signal.

            This float value sets the absolute value (in microseconds) for the minimum signal width of a signal that is received from the frequency converter or from the shaft encoder module and that is associated with a digital output line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IFloat& MinOutPulseWidthAbs;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Indicates the current logical state for the selected line

            This boolean value indicates the current logical state for the selected line at the time of polling.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IBoolean& LineStatus;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief A single bitfield indicating the current logical state of all available line signals at time of polling

            This integer value is a single bitfield that indicates the current logical state of all available lines at time of polling.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& LineStatusAll;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Selects the user settable output signal to configure. Once a user settable output signal has been selected, all changes to the user settable output signal settings will be applied to the selected user settable output signal.

            This enumeration selects the user settable output signal to configure. Once a user settable output signal has been selected, all changes to the user settable output signal settings will be applied to the selected user settable output signal.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<UserOutputSelectorEnums >& UserOutputSelector;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the state of the selected user settable output signal

            This boolean value sets the state of the selected user settable output signal.

            \b Visibility = Beginner


            \b Selected by : UserOutputSelector

        */
        GENAPI_NAMESPACE::IBoolean& UserOutputValue;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief A single bitfield that sets the state of all user settable output signals in one access

            This integer value is a single bitfield that sets the state of all user settable output signals in one access.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& UserOutputValueAll;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Defines a mask that is used when the User Output Value All setting is used to set all of the user settable output signals in one access

            This integer value defines a mask that is used when the User Output Value All setting is used to set all of the user settable output signals in one access.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& UserOutputValueAllMask;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<SyncUserOutputSelectorEnums >& SyncUserOutputSelector;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief Sets the state of the selected user settable synchronous output signal

            This boolean value sets the state of the selected user settable synchronous output signal.

            \b Visibility = Beginner


            \b Selected by : SyncUserOutputSelector

        */
        GENAPI_NAMESPACE::IBoolean& SyncUserOutputValue;

        //@}


        //! \name DigitalIO - This category includes items used to control the operation of the camera's digital I/O lines
        //@{
        /*!
            \brief A single bitfield that sets the state of all user settable synchronous output signals in one access

            This integer value is a single bitfield that sets the state of all user settable synchronous output signals in one access.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& SyncUserOutputValueAll;

        //@}


        //! \name VirtualInput - This category includes items used to control the operation of the camera's virtual input I/O lines
        //@{
        /*!
            \brief Sets the I/O line on which the camera receives the virtual input signal

            This enumeration selects the I/O line on which the camera receives the virtual input signal.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<VInpSignalSourceEnums >& VInpSignalSource;

        //@}


        //! \name VirtualInput - This category includes items used to control the operation of the camera's virtual input I/O lines
        //@{
        /*!
            \brief Sets the length of the input bit

            This integer value sets the length of the input bit in microseconds. It applies to all bits in the signal.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VInpBitLength;

        //@}


        //! \name VirtualInput - This category includes items used to control the operation of the camera's virtual input I/O lines
        //@{
        /*!
            \brief Time span between the beginning of the input bit and the time when the high/low status is evaluated

            This integer value sets the time in microseconds that elapses between the beginning of the input bit and the time when the high/low status of the bit is evaluated. It applies to all bits.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VInpSamplingPoint;

        //@}


        //! \name VirtualInput - This category includes items used to control the operation of the camera's virtual input I/O lines
        //@{
        /*!
            \brief Selects when to start the signal evaluation

            This enumeration selects when to start the signal evaluation. The camera waits for a rising/falling edge on the input line. When the appropriate signal has been received, the camera starts evaluating the incoming bit patterns. When one bit pattern is finished, the camera waits for the next rising/falling edge to read out the next incoming bit pattern. The camera stops listening once three bits have been received.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<VInpSignalReadoutActivationEnums >& VInpSignalReadoutActivation;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Selects the phase of the shaft encoder.

            Selects the phase of the shaft encoder as input for the shaft encoder module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ShaftEncoderModuleLineSelectorEnums >& ShaftEncoderModuleLineSelector;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Selects the input line as signal source for the shaft encoder module.

            Selects the input line as signal source for the shaft encoder module.

            \b Visibility = Expert

            \b Selected by : ShaftEncoderModuleLineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ShaftEncoderModuleLineSourceEnums >& ShaftEncoderModuleLineSource;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Selects the circumstances for the shaft encoder module to output trigger signals.

            This enumeration value selects the circumstances for the shaft encoder module to output trigger signals.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ShaftEncoderModuleModeEnums >& ShaftEncoderModuleMode;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Selects the counting mode of the tick counter.

            Selects the counting mode of the tick counter of the shaft encoder module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ShaftEncoderModuleCounterModeEnums >& ShaftEncoderModuleCounterMode;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Indicates the current value of the tick counter.

            This integer value (read only) indicates the current value of the tick counter of the shaft encoder module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& ShaftEncoderModuleCounter;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Sets the maximum value for the tick counter.

            This integer value sets the maximum value for the tick counter of the shaft encoder module (range: 0 to 32767). If the tick counter is incrementing and it reaches the set maximum, it willl roll over to 0. If the tick counter is decrementing and it reaches 0, it willl roll back to the set maximum.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& ShaftEncoderModuleCounterMax;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Resets the tick counter to 0.

            This command resets the tick counter count of the shaft encoder module to 0.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& ShaftEncoderModuleCounterReset;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Sets the maximum value for the reverse counter.

            This integer value sets the maximum value for the reverse counter of the shaft encoder module (range: 0 to 32767).

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& ShaftEncoderModuleReverseCounterMax;

        //@}


        //! \name ShaftEncoderModule - This category provides controls for operating the camera's shaft encoder module.
        //@{
        /*!
            \brief Resets the reverse counter to 0.

            This command resets the reverse counter of the shaft encoder module to 0 and informs the module that the current direction of conveyor movement is forward. Reset must be carried out before the first conveyor movement in the forward direction.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& ShaftEncoderModuleReverseCounterReset;

        //@}


        //! \name FrequencyConverter - This category includes items used to control the operation of the camera's frequency converter module
        //@{
        /*!
            \brief Selects the input source.

            Selects the input source for the frequency converter module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<FrequencyConverterInputSourceEnums >& FrequencyConverterInputSource;

        //@}


        //! \name FrequencyConverter - This category includes items used to control the operation of the camera's frequency converter module
        //@{
        /*!
            \brief Selects the signal transition relationships between received and generated signals.

            Selects the signal transition relationships between the signals received from the pre-divider sub-module and the signals generated by the multiplier sub-module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<FrequencyConverterSignalAlignmentEnums >& FrequencyConverterSignalAlignment;

        //@}


        //! \name FrequencyConverter - This category includes items used to control the operation of the camera's frequency converter module
        //@{
        /*!
            \brief Sets the pre-divider value for the pre-divider sub-module.

            Sets an integer value as the pre-divider for the pre-divider sub-module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& FrequencyConverterPreDivider;

        //@}


        //! \name FrequencyConverter - This category includes items used to control the operation of the camera's frequency converter module
        //@{
        /*!
            \brief Sets the multiplier value for the multiplier sub-module.

            Sets an integer value as the multiplier for the multiplier sub-module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& FrequencyConverterMultiplier;

        //@}


        //! \name FrequencyConverter - This category includes items used to control the operation of the camera's frequency converter module
        //@{
        /*!
            \brief Sets the post-divider value for the post-divider sub-module.

            Sets an integer value as the post-divider for the post-divider sub-module.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& FrequencyConverterPostDivider;

        //@}


        //! \name FrequencyConverter - This category includes items used to control the operation of the camera's frequency converter module
        //@{
        /*!
            \brief Enables overtriggering protection.

            This feature ensures that the multiplier sub-module does not provide a generated signal at a too high frequency that would cause camera overtriggering.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& FrequencyConverterPreventOvertrigger;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Sets the time base (in microseconds) that is used when a timer delay is set with the 'timer delay raw' setting

            This float value sets the time base (in microseconds) that is used when a timer delay is set with the 'raw' setting.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& TimerDelayTimebaseAbs;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Sets the time base (in microseconds) that is used when a timer duration is set with the 'timer duration raw' setting

            This float value sets the time base (in microseconds) that is used when a timer duration is set with the 'raw' setting.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& TimerDurationTimebaseAbs;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Selects the timer to configure.  Once a timer has been selected, all changes to the timer settings will be applied to the selected timer.

            This enumeration selects the timer to configure. . Once a timer has been selected, all changes to the timer settings will be applied to the selected timer.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TimerSelectorEnums >& TimerSelector;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Directly sets the delay for the selected timer in microseconds

            This float value sets the delay for the selected timer in microseconds.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IFloat& TimerDelayAbs;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Sets the 'raw' delay for the selected timer.  Actual delay = raw timer delay setting  x  timer delay time base abs setting

            This value sets an integer that will be used as a multiplier for the timer delay timebase. The actual delay time equals the current timer delay raw setting times the current timer delay time base abs setting.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IInteger& TimerDelayRaw;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Directly sets the duration for the selected timer in microseconds

            This float value sets the duration for the selected timer in microseconds.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IFloat& TimerDurationAbs;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Sets the 'raw' duration for the selected timer.  Actual duration = raw timer duration setting  x  timer duration time base abs setting

            This value sets an integer that will be used as a multiplier for the timer duration timebase. The actual duration time equals the current timer duration raw setting times the current timer duration time base abs setting.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IInteger& TimerDurationRaw;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Sets the internal camera signal used to trigger the selected timer

            This enumeration sets the internal camera signal used to trigger the selected timer.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TimerTriggerSourceEnums >& TimerTriggerSource;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Sets the type of signal transistion that will start the timer

            This enumeration sets the type of signal transistion that will start the timer.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TimerTriggerActivationEnums >& TimerTriggerActivation;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Selects the counter to configure.  Once a counter has been selected, all changes to the counter settings will be applied to the selected counter.

            This enumeration selects the counter to configure. Once a counter has been selected, all changes to the counter settings will be applied to the selected counter.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<CounterSelectorEnums >& CounterSelector;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Selects the event that will be the source to increment the counter

            This enumeration selects the event that will be the source to increment the counter.

            \b Visibility = Expert

            \b Selected by : CounterSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<CounterEventSourceEnums >& CounterEventSource;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Selects the source of the reset for the selected counter.

            This enumeration selects the source of the reset for the selected counter.

            \b Visibility = Expert

            \b Selected by : CounterSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<CounterResetSourceEnums >& CounterResetSource;

        //@}


        //! \name TimerControls - This category includes items used to control the operation of the camera's timers
        //@{
        /*!
            \brief Immediately resets the selected counter

            This command will immediately reset the selected counter. Note that the counter starts counting immediately after the reset.

            \b Visibility = Expert

            \b Selected by : CounterSelector

        */
        GENAPI_NAMESPACE::ICommand& CounterReset;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& TimerSequenceEnable;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& TimerSequenceLastEntryIndex;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& TimerSequenceCurrentEntryIndex;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<TimerSequenceEntrySelectorEnums >& TimerSequenceEntrySelector;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : TimerSequenceEntrySelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TimerSequenceTimerSelectorEnums >& TimerSequenceTimerSelector;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : TimerSequenceTimerSelector

        */
        GENAPI_NAMESPACE::IBoolean& TimerSequenceTimerEnable;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : TimerSequenceTimerSelector

        */
        GENAPI_NAMESPACE::IBoolean& TimerSequenceTimerInverter;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : TimerSequenceTimerSelector

        */
        GENAPI_NAMESPACE::IInteger& TimerSequenceTimerDelayRaw;

        //@}


        //! \name TimerSequence -
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : TimerSequenceTimerSelector

        */
        GENAPI_NAMESPACE::IInteger& TimerSequenceTimerDurationRaw;

        //@}


        //! \name LUTControls - This category includes items used to control the operation of the camera's lookup table (LUT)
        //@{
        /*!
            \brief Selects the lookup table (LUT) to configure. Once a LUT has been selected, all changes to the LUT settings will be applied to the selected LUT.

            This enumeration the lookup table (LUT) to configure. Once a LUT has been selected, all changes to the LUT settings will be applied to the selected LUT.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<LUTSelectorEnums >& LUTSelector;

        //@}


        //! \name LUTControls - This category includes items used to control the operation of the camera's lookup table (LUT)
        //@{
        /*!
            \brief Enables the selected LUT

            This boolean value enables the selected LUT.

            \b Visibility = Beginner


            \b Selected by : LUTSelector

        */
        GENAPI_NAMESPACE::IBoolean& LUTEnable;

        //@}


        //! \name LUTControls - This category includes items used to control the operation of the camera's lookup table (LUT)
        //@{
        /*!
            \brief Sets the LUT element to access

            This value sets the LUT element to access. This value is used to index into a LUT array.

            \b Visibility = Beginner


            \b Selected by : LUTSelector

        */
        GENAPI_NAMESPACE::IInteger& LUTIndex;

        //@}


        //! \name LUTControls - This category includes items used to control the operation of the camera's lookup table (LUT)
        //@{
        /*!
            \brief Sets the value of the LUT element at the LUT index

            This value sets the value of the LUT element at the LUT index.

            \b Visibility = Beginner


            \b Selected by : LUTSelector, LUTIndex

        */
        GENAPI_NAMESPACE::IInteger& LUTValue;

        //@}


        //! \name LUTControls - This category includes items used to control the operation of the camera's lookup table (LUT)
        //@{
        /*!
            \brief Accesses the entire content of the selected LUT in one chunk access



            \b Visibility = Beginner


            \b Selected by : LUTSelector

        */
        GENAPI_NAMESPACE::IRegister& LUTValueAll;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Size of the payload in bytes

            Size of the payload in bytes. This is the total number of bytes sent in the payload. Image data + chunk data if present. No packet headers.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& PayloadSize;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the packet size in bytes for the selected stream channel

            This value sets the packet size in bytes for the selected stream channel. Excludes data leader and data trailer. (The last packet may be smaller because the packet size is not necessarily a multiple of the block size for the stream channel.)

            \b Visibility = Beginner

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCPSPacketSize;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the inter-packet delay (in ticks) for the selected stream channel

            This value sets a delay between the transmission of each packet for the selected stream channel. The delay is measured in ticks.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCPD;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the frame transfer start delay (in ticks) for the selected stream channel

            This value sets the frame transfer delay for the selected stream channel. This value sets a delay betweem when the camera would normally begin transmitted an acquired image (frame) and when it actually begins transmitting the acquired image.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCFTD;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets a percentage of the Ethernet bandwidth assigned to the camera to be held in reserve. The reserve is used for packet resends and control data transmissions.

            This value reserves a portion of Ethernet bandwidth assigned to the camera for packet resends and for the transmission of control data between the camera and the host PC. The setting is expressed as a percentage of the bandwidth assigned parameter. For example, if the Bandwidth Assigned parameter indicates that 30 MBytes/s have been assigned to the camera and the Bandwidth Reserve parameter is set to 5%, then the bandwidth reserve will be 1.5 MBytes/s.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCBWR;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets a multiplier for the Bandwidth Reserve parameter. The multiplier is used to establish an extra pool of reserved bandwidth that can be used if an unusually large burst of packet resends is needed.

            This value sets a multiplier for the Bandwidth Reserve parameter. The multiplier is used to establish an extra pool of reserved bandwidth that can be used if an unusually large burst of packet resends is needed.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCBWRA;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the bandwidth (in bytes per second) that will be used by the camera to transmit image and chunk feature data and to handle resends and control data transmissions.

            This value indicates the base bandwidth in bytes per second that will be used by the camera to transmit image and chunk feature data and to handle resends and control data transmissions. This parameter represents a combination of the packet size and the inter-packet delay.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCBWA;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the maximum amount of data (in bytes per second) that the camera could generate given its current settings and ideal conditions, i.e., unlimited bandwidth and no packet resends

            This value indicates the maximum amount of data (in bytes per second) that the camera could generate given its current settings and ideal conditions, i.e., unlimited bandwidth and no packet resends.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCDMT;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data given the current AOI settings, chunk feature settings, and the pixel format setting

            This value indicates the actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data given the current AOI settings, chunk feature settings, and the pixel format setting.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCDCT;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the maximum time (in ticks) that the next frame transmission could be delayed due to a burst of resends

            If the Bandwidth Reserve Accumulation parameter is set to a high value, the camera can experience periods where there is a large burst of data resends. This burst of resends will delay the start of transmission of the next acquired image. The Frame Max Jitter parameter indicates the maximum time in ticks that the next frame transmission could be delayed due to a burst of resends.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCFJM;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the major version number of the GigE Vision specification supported by this device.

            This is a read only element. It indicates the major version number of the GigE Vision specification supported by this device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevVersionMajor;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the minor version number of the GigE Vision specification supported by this device.

            This is a read only element. It indicates the minor version number of the GigE Vision specification supported by this device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevVersionMinor;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the endianess of the bootstrap registers.

            This is a read only element. It indicates the endianess of the bootstrap registers. True = big endian.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& GevDeviceModeIsBigEndian;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indictes the character set.

            This is a read only element. Its value indicates the character set. 1 = UTF8

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevDeviceModeCharacterSet;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Selects the physical network interface to configure. Once a network interface has been selected, all changes to the network interface settings will be applied to the selected interface.

            This selects the physical network interface to configure. Once a network interface has been selected, all changes to the network interface settings will be applied to the selected interface.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<GevInterfaceSelectorEnums >& GevInterfaceSelector;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the MAC address for the selected network interface

            This is a read only element. It indicates the MAC address for the selected network interface.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevMACAddress;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Enable the extended ID mode for GVSP

            Enable extended ID mode for GVSP (64 bit block_id64, 32 bit packet_id32). This bit cannot be reset if the stream channels do not support the standard ID mode.

            \b Visibility = Expert

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<GevGVSPExtendedIDModeEnums >& GevGVSPExtendedIDMode;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether the selected network interface supports auto IP addressing (also known as LLA)

            This is a read only element. It indicates whether the selected network interface supports auto IP addressing (also known as LLA).

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedIPConfigurationLLA;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether the selected network interface supports DHCP IP addressing

            This is a read only element. It indicates whether the selected network interface supports DHCP IP addressing.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedIPConfigurationDHCP;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether the selected network interface supports fixed IP addressing (also known as persistent IP addressing)

            This is a read only element. It indicates whether the selected network interface supports fixed IP addressing (also known as persistent IP addressing).

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedIPConfigurationPersistentIP;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the current IP configuration of the selected network interface

            This value sets the IP configuration of the selected network interface, i.e., fixed IP, DHCP, auto IP.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevCurrentIPConfiguration;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the current IP address for the selected network interface

            This is a read only element. It indicates the current IP address for the selected network interface.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevCurrentIPAddress;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the current subnet mask for the selected network interface

            This is a read only element. It indicates the current subnet mask for the selected network interface.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevCurrentSubnetMask;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the current default gateway for the selected network interface

            This is a read only element. It indicates the current default gateway for the selected network interface.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevCurrentDefaultGateway;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief If fixed (persistent) IP addressing is supported by the device and enabled, sets the fixed IP address for the selected network interface

            This value sets the fixed IP address for the selected network interface (if fixed IP addressing is supported by the device and enabled).

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevPersistentIPAddress;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief If fixed (persistent) IP addressing is supported by the device and enabled, sets the fixed subnet mask for the selected network interface

            This value sets the fixed subnet mask for the selected network interface (if fixed IP addressing is supported by the device and enabled).

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevPersistentSubnetMask;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief If fixed (persistent) IP addressing is supported by the device and enabled, sets the fixed default gateway for the selected network interface

            This value sets the fixed default gateway for the selected network interface (if fixed IP addressing is supported by the device and enabled).

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevPersistentDefaultGateway;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the connection speed in Mbps for the selected network interface

            This is a read only element. It indicates the connection speed in Mbps for the selected network interface.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IInteger& GevLinkSpeed;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether the selected network interface is the clock master.

            This is a read only element. It indicates whether the selected network interface is the clock master.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevLinkMaster;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether the selected network interface operates in full-duplex mode.

            This is a read only element. It indicates whether the selected network interface operates in full-duplex mode.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevLinkFullDuplex;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the state of medium-dependent interface crossover (MDIX) for the selected network interface.

            This is a read only element. It indicates the state of medium-dependent interface crossover (MDIX) for the selected network interface.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevLinkCrossover;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the first URL to the XML device description file

            This is a read only element. It indicates the first URL to the XML device description file.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IString& GevFirstURL;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the second URL to the XML device description file

            This is a read only element. It indicates the second URL to the XML device description file.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IString& GevSecondURL;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the number of network interfaces on the device

            This is a read only element. It indicates the number of network interfaces on the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevNumberOfInterfaces;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the number of message channels supported by the device

            This is a read only element. It indicates the number of message channels supported by the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevMessageChannelCount;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the number of stream channels supported by the device

            This is a read only element. It indicates the number of stream channels supported by the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevStreamChannelCount;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether this GVSP transmitter or receiver can support 16-bit block_id

            This is a read only element. It indicates whether this GVSP transmitter or rceiver can support 16-bit block_id.

            \b Visibility = Guru

            \b Selected by : GevInterfaceSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedOptionalLegacy16BitBlockID;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether IEEE 1588 (PTP) is supported

            This is a read only element. It indicates whether whether IEEE 1588 (PTP) is supported.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedIEEE1588;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether EVENTDATA_CMD and EVENTDATA_ACK are supported

            This is a read only element. It indicates whether EVENTDATA_CMD and EVENTDATA_ACK are supported.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedOptionalCommandsEVENTDATA;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether EVENT_CMD and EVENT_ACK are supported

            This is a read only element. It indicates whether EVENT_CMD and EVENT_ACK are supported.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedOptionalCommandsEVENT;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether PACKETRESEND_CMD is supported

            This is a read only element. It indicates whether PACKETRESEND_CMD is supported.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedOptionalCommandsPACKETRESEND;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether WRITEMEM_CMD and WRITEMEM_ACK are supported

            This is a read only element. It indicates whether WRITEMEM_CMD and WRITEMEM_ACK are supported

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedOptionalCommandsWRITEMEM;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates whether multiple operations in a single message are supported

            This is a read only element. It indicates whether multiple operations in a single message are supported.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IBoolean& GevSupportedOptionalCommandsConcatenation;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the heartbeat timeout in milliseconds

            This value sets the heartbeat timeout in milliseconds.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevHeartbeatTimeout;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the number of timestamp clock ticks in 1 second

            This is a read only element. It indicates the number of timestamp clock ticks in 1 second.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevTimestampTickFrequency;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Latches the current timestamp value of the device

            This command latches the current timestamp value of the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& GevTimestampControlLatch;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Resets the timestamp value for the device

            This command resets the timestamp value for the device

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& GevTimestampControlReset;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Resets the timestamp control latch

            This command resets the timestamp control latch.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& GevTimestampControlLatchReset;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the latched value of the timestamp.  (The timestamp must first be latched using the Timestamp Control Latch command.)

            This is a read only element. It indicates the latched value of the timestamp.  (The timestamp must first be latched using the Timestamp Control Latch command.)

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevTimestampValue;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the control channel privilege feature

            This enumeration sets the control channel privilege feature.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<GevCCPEnums >& GevCCP;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Selects the stream channel to configure. Once a stream channel has been selected, all changes to the stream channel settings will be applied to the selected stream channel.

            This enumeration selects the stream channels to configure. Once a stream channel has been selected, all changes to the stream channel settings will be applied to the selected stream channel.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<GevStreamChannelSelectorEnums >& GevStreamChannelSelector;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the index of the network interface to use

            This value sets the index of the network interface to use.

            \b Visibility = Guru

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCPInterfaceIndex;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the stream channel destination IPv4 address for the selected stream channel

            This value sets the stream channel destination IPv4 address for the selected stream channel. The destination can be a unicast or a multicast.

            \b Visibility = Guru

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCDA;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Sets the port to which the device must send data streams

            This value sets the port to which the device must send data streams.

            \b Visibility = Guru

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IInteger& GevSCPHostPort;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::ICommand& GevSCPSFireTestPacket;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevSCPSDoNotFragment;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : GevStreamChannelSelector

        */
        GENAPI_NAMESPACE::IBoolean& GevSCPSBigEndian;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief  Indicates whether a live grab is under way



            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& TLParamsLocked;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Select legacy pixel format encoding

            This switch selects a legacy GVSP pixel format encoding, for compatibility with older camera models.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& PixelFormatLegacy;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Enable usage of the IEEE 1588 V2 Precision Time Protocol to source the timestamp register. Only available when the IEEE1588_support bit of the GVCP Capability register is set. When PTP is enabled, the Timestamp Control register cannot be used to reset the timestamp. Factory default is devicespecific. When PTP is enabled or disabled, the value of Timestamp Tick Frequency and Timestamp Value registers might change to reflect the new time domain.

            This value indicates whether IEEE 1588 V2 (PTP) is enabled.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& GevIEEE1588;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Provides the state of the IEEE 1588 clock

            Provides the state of the IEEE 1588 clock. Values of this field must match the IEEE 1588 PTP port state enumeration (INITIALIZING, FAULTY, DISABLED, LISTENING, PRE_MASTER, MASTER, PASSIVE, UNCALIBRATED, SLAVE). Please refer to IEEE 1588 for additional information.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<GevIEEE1588StatusEnums >& GevIEEE1588Status;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Latches the current IEEE 1588 related values of the device

            This command latches the current IEEE 1588 related values of the device.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::ICommand& GevIEEE1588DataSetLatch;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the latched state of the IEEE 1588 clock

            This is a read only element. It indicates the latched state of the IEEE 1588 clock. (The state must first be latched using the IEEE 1588 Latch command.) The state is indicated by values 1 to 9, corresponding to the states INITIALIZING, FAULTY, DISABLED, LISTENING, PRE_MASTER, MASTER, PASSIVE, UNCALIBRATED, and SLAVE. Refer to the IEEE 1588 specification for additional information.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<GevIEEE1588StatusLatchedEnums >& GevIEEE1588StatusLatched;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. It indicates the latched offset from the IEEE 1588 master clock in nanoseconds. (The offset must first be latched using the IEEE 1588 Latch command.)

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevIEEE1588OffsetFromMaster;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. It is the low part of the 1588 clock ID

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& GevIEEE1588ClockIdLow;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. It is the high part of the 1588 clock ID

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& GevIEEE1588ClockIdHigh;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the latched clock ID of the IEEE 1588 device.

            This is a read only element. It indicates the latched clock ID of the IEEE 1588 device. (The clock ID must first be latched using the IEEE 1588 Latch command.) The clock ID is an array of eight octets which is displayed as hexadecimal number. Leading zeros are omitted.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevIEEE1588ClockId;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. It is the low part of the 1588 parent clock ID

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& GevIEEE1588ParentClockIdLow;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. It is the high part of the 1588 parent clock ID

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& GevIEEE1588ParentClockIdHigh;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief Indicates the latched parent clock ID of the IEEE 1588 device.

            This is a read only element. It indicates the latched parent clock ID of the IEEE 1588 device. (The parent clock ID must first be latched using the IEEE 1588 Latch command.) The parent clock ID is the clock ID of the current master clock. A clock ID is an array of eight octets which is displayed as hexadecimal number. Leading zeros are omitted.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevIEEE1588ParentClockId;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. Maximum number of elements in RX event message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevPTPDiagnosticsQueueRxEvntMaxNumElements;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. Maximum number of elements in RX general message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevPTPDiagnosticsQueueRxGnrlMaxNumElements;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. Number of push failures in RX event message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevPTPDiagnosticsQueueRxEvntPushNumFailure;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. Number of push failures in RX general message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevPTPDiagnosticsQueueRxGnrlPushNumFailure;

        //@}


        //! \name TransportLayer - This category includes items related to the GigE Vision transport layer
        //@{
        /*!
            \brief

            This is a read only element. Number of send failures. (The value must first be latched using the IEEE 1588 Latch command.)

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& GevPTPDiagnosticsQueueSendNumFailure;

        //@}


        //! \name ActionControl - This category includes items that control the action control feature
        //@{
        /*!
            \brief Number of separate action signals supported by the device.

            Number of separate action signals supported by the device. Determines how many action signals the device can handle in parallel, i.e. how many different action commands can be set up for the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& NumberOfActionSignals;

        //@}


        //! \name ActionControl - This category includes items that control the action control feature
        //@{
        /*!
            \brief Number of action command interfaces

            Available number of action command interfaces on the camera device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& ActionCommandCount;

        //@}


        //! \name ActionControl - This category includes items that control the action control feature
        //@{
        /*!
            \brief Authorization key

            Key to authorize the action for the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& ActionDeviceKey;

        //@}


        //! \name ActionControl - This category includes items that control the action control feature
        //@{
        /*!
            \brief Selects the action command to configure. Once an action command has been selected, all changes to the action command settings will be applied to the selected action command.

            This enumeration selects the action command to configure. Once an action command has been selected, all changes to the action command settings will be applied to the selected action command.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ActionSelector;

        //@}


        //! \name ActionControl - This category includes items that control the action control feature
        //@{
        /*!
            \brief Defines a group of devices

            Used to define a group of devices on which actions can be executed.

            \b Visibility = Guru

            \b Selected by : ActionSelector

        */
        GENAPI_NAMESPACE::IInteger& ActionGroupKey;

        //@}


        //! \name ActionControl - This category includes items that control the action control feature
        //@{
        /*!
            \brief Filters out particular devices from its group

            Used to filter out some particular devices from the group of devices defined by the action group key.

            \b Visibility = Guru

            \b Selected by : ActionSelector

        */
        GENAPI_NAMESPACE::IInteger& ActionGroupMask;

        //@}


        //! \name DeviceControl -
        //@{
        /*!
            \brief Prepare the device for registers streaming

            StartFeatureStreaming

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& DeviceRegistersStreamingStart;

        //@}


        //! \name DeviceControl -
        //@{
        /*!
            \brief Announce the end of registers streaming

            StopFeatureStreaming

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& DeviceRegistersStreamingEnd;

        //@}


        //! \name UserSets - This category includes items that control the configuration sets feature that is used to save sets of parameters in the camera
        //@{
        /*!
            \brief Selects the configuration set to load, save, or configure. Once a configuration set has been selected, all changes to the configuration set settings will be applied to the selected configuration set.

            This enumeration selects the configuration set to load, save or configure. Possible values for the User Set Selector are: Default: Selects a configuration set that contains factory settings. User Set 1: Selects the first user set. When the Default configuration set is selected and loaded using User Set Load, the device must be in default factory settings state and must make sure the mandatory continuous acquisition use case works directly. Default User Set is read-only and cannot be modified.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<UserSetSelectorEnums >& UserSetSelector;

        //@}


        //! \name UserSets - This category includes items that control the configuration sets feature that is used to save sets of parameters in the camera
        //@{
        /*!
            \brief Loads the selected configuration into the camera's volatile memory and makes it the active configuration set. Once the selected set is loaded, the parameters in the selected set will control the camera.

            This command loads the selected configuration set from the non-volatile memory in the camera to the volatile memory and makes the selected set the active configuration set. Once the selected set is loaded, the parameters in the selected set will control the camera.

            \b Visibility = Beginner


            \b Selected by : UserSetSelector

        */
        GENAPI_NAMESPACE::ICommand& UserSetLoad;

        //@}


        //! \name UserSets - This category includes items that control the configuration sets feature that is used to save sets of parameters in the camera
        //@{
        /*!
            \brief Saves the current active configuration set into the selected user set.

            This command copies the parameters in the current active configuration set into the selected user set in the camera's non-volatile memory.

            \b Visibility = Beginner


            \b Selected by : UserSetSelector

        */
        GENAPI_NAMESPACE::ICommand& UserSetSave;

        //@}


        //! \name UserSets - This category includes items that control the configuration sets feature that is used to save sets of parameters in the camera
        //@{
        /*!
            \brief Sets the configuration set to be used as the default startup set. The configuration set that has been selected as the default startup set will be loaded as the active set whenever the camera is powered on or reset.

            This enumeration sets the configuration set to be used as the default startup set. The configuration set that has been selected as the default startup set will be loaded as the active set whenever the camera is powered on or reset.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<UserSetDefaultSelectorEnums >& UserSetDefaultSelector;

        //@}


        //! \name UserSets - This category includes items that control the configuration sets feature that is used to save sets of parameters in the camera
        //@{
        /*!
            \brief Selects the which factory setting will be used as default set.

            Selects the which factory setting will be used as default set.

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IEnumerationT<DefaultSetSelectorEnums >& DefaultSetSelector;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Target average grey value for Gain Auto and Exposure Auto

            The target average grey value may range from nearly black to nearly white. Note that this range of gray values applies to 8 bit and to 16 bit (12 bit effective) output modes. Accordingly, also for 16 bit output modes, black is represented by 0 and white by 255.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AutoTargetValue;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Gray value adjustment damping for Gain Auto and Exposure Auto

            The gray value adjustment damping parameter controls the rate by which pixel gray values are changed when Exposure Auto and/or Gain Auto are enabled.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& GrayValueAdjustmentDampingAbs;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Gray value adjustment damping for Gain Auto and Exposure Auto

            The gray value adjustment damping parameter controls the rate by which pixel gray values are changed when Exposure Auto and/or Gain Auto are enabled.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& GrayValueAdjustmentDampingRaw;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Balance White adjustment damping for Balance White Auto

            The Balance White adjustment damping parameter controls the rate by which the color components are changed when Balance White Auto is enabled.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& BalanceWhiteAdjustmentDampingAbs;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Balance White adjustment damping for Balance White Auto

            The Balance White adjustment damping parameter controls the rate by which the color components are changed when Balance White Auto is enabled.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& BalanceWhiteAdjustmentDampingRaw;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Lower limit of the Auto Gain (Raw) parameter

            Lower limit of the Auto Gain (Raw) parameter

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AutoGainRawLowerLimit;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Upper limit of the Auto Gain (Raw) parameter

            Upper limit of the Auto Gain (Raw) parameter

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AutoGainRawUpperLimit;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Lower limit of the Auto Exposure Time (Abs) [us] parameter

            Lower limit of the Auto Exposure Time (Abs) [us] parameter

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoExposureTimeAbsLowerLimit;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Upper limit of the Auto Exposure Time (Abs) [us] parameter

            Upper limit of the Auto Exposure Time (Abs) [us] parameter

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoExposureTimeAbsUpperLimit;

        //@}


        //! \name AutoFunctions - This category includes items that parameterize the Auto Functions
        //@{
        /*!
            \brief Selects the strategy for controlling gain and shutter simultaneously.

            Selects the profile for controlling gain and shutter simultaneously.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<AutoFunctionProfileEnums >& AutoFunctionProfile;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief Selects the Auto Function AOI.

            Selects the Auto Function AOI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<AutoFunctionAOISelectorEnums >& AutoFunctionAOISelector;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief Sets the width of the auto function area of interest in pixels

            This value sets the width of the auto function area of interest in pixels.

            \b Visibility = Beginner


            \b Selected by : AutoFunctionAOISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionAOIWidth;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief Sets the height of the auto function area of interest in pixels

            This value sets the height of the auto function area of interest in pixels.

            \b Visibility = Beginner


            \b Selected by : AutoFunctionAOISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionAOIHeight;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief Sets the starting column of the auto function area of interest in pixels

            This value sets the starting column of the auto function area of interest in pixels.

            \b Visibility = Beginner


            \b Selected by : AutoFunctionAOISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionAOIOffsetX;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief Sets the starting line of the auto function area of interest in pixels

            This value sets the starting line of the auto function area of interest in pixels.

            \b Visibility = Beginner


            \b Selected by : AutoFunctionAOISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionAOIOffsetY;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief



            \b Visibility = Beginner


            \b Selected by : AutoFunctionAOISelector

        */
        GENAPI_NAMESPACE::IBoolean& AutoFunctionAOIUsageIntensity;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief



            \b Visibility = Beginner


            \b Selected by : AutoFunctionAOISelector

        */
        GENAPI_NAMESPACE::IBoolean& AutoFunctionAOIUsageWhiteBalance;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief



            \b Visibility = Beginner


            \b Selected by : AutoFunctionAOISelector

        */
        GENAPI_NAMESPACE::IBoolean& AutoFunctionAOIUsageRedLightCorrection;

        //@}


        //! \name AutoFunctionAOIs - Portion of the sensor array used for auto function control
        //@{
        /*!
            \brief Assigns the Tonal Range Auto auto function to the currently selected auto function AOI.

            Assigns the Tonal Range Auto auto function to the currently selected auto function AOI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& AutoFunctionAOIUsageTonalRange;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Sets the kind of tonal range auto adjustment.

            Sets the kind of tonal range auto adjustment.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<AutoTonalRangeModeSelectorEnums >& AutoTonalRangeModeSelector;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Sets which parts of the tonal range can be adjusted.

            Sets which parts of the tonal range can be adjusted.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<AutoTonalRangeAdjustmentSelectorEnums >& AutoTonalRangeAdjustmentSelector;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Threshold value from which the TonalRangeSourceDark parameter value is calculated during automatic tonal range adjustments.

            Threshold value from which the TonalRangeSourceDark parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned Auto Function ROI. Example: Assume you set the AutoTonalRangeThresholdDark parameter to 0.2 and enable the Tonal Range Auto auto function. Now assume that 0.2 % of the pixels in the assigned Auto Function ROI have a pixel value lower than or equal to 30. The camera automatically detects this, sets the TonalRangeSourceDark parameter to 30, and starts tonal range adjustments.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoTonalRangeThresholdDark;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Threshold value from which the TonalRangeSourceDark parameter value is calculated during automatic tonal range adjustments (raw value).

            Threshold value from which the TonalRangeSourceDark parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned Auto Function ROI. Example: Assume you set the AutoTonalRangeThresholdDark parameter to 0.2 and enable the Tonal Range Auto auto function. Now assume that 0.2 % of the pixels in the assigned Auto Function ROI have a pixel value lower than or equal to 30. The camera automatically detects this, sets the TonalRangeSourceDark parameter to 30, and starts tonal range adjustments.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AutoTonalRangeThresholdDarkRaw;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Threshold value from which the TonalRangeSourceBright parameter value is calculated during automatic tonal range adjustments.

            Threshold value from which the TonalRangeSourceBright parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned Auto Function ROI. Example: Assume you set the AutoTonalRangeThresholdBright parameter to 0.1 and enable the Tonal Range Auto auto function. Now assume that 0.1 % of the pixels in the assigned Auto Function ROI have a pixel value greater than or equal to 240. The camera automatically detects this, sets the TonalRangeSourceBright parameter to 240, and starts tonal range adjustments.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoTonalRangeThresholdBright;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Threshold value from which the TonalRangeSourceBright parameter value is calculated during automatic tonal range adjustments (raw value).

            Threshold value from which the TonalRangeSourceBright parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned Auto Function ROI. Example: Assume you set the AutoTonalRangeThresholdBright parameter to 0.1 and enable the Tonal Range Auto auto function. Now assume that 0.1 % of the pixels in the assigned Auto Function ROI have a pixel value greater than or equal to 240. The camera automatically detects this, sets the TonalRangeSourceBright parameter to 240, and starts tonal range adjustments.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AutoTonalRangeThresholdBrightRaw;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Dark target value to be used during automatic tonal range adjustments.

            Dark target value to be used during automatic tonal range adjustments. When you enable the Tonal Range Auto auto function, the camera sets the TonalRangeTargetDark parameter to this value. Not available if the AutoTonalRangeModeSelector parameter is set to Color.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& AutoTonalRangeTargetDark;

        //@}


        //! \name AutoTonalRangeControl - Contains parameters for configuring the Tonal Range Auto auto function.
        //@{
        /*!
            \brief Bright target value to be used during automatic tonal range adjustments.

            Bright target value to be used during automatic tonal range adjustments. When you enable the Tonal Range Auto auto function, the camera sets the TonalRangeTargetBright parameter to this value. Not available if the AutoTonalRangeModeSelector parameter is set to Color.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& AutoTonalRangeTargetBright;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Selcts the AOI for color overexposure compensation

            Selcts the area of interest where color overexposure compensation will be performed.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<ColorOverexposureCompensationAOISelectorEnums >& ColorOverexposureCompensationAOISelector;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Enables color overexposure compensation

            Enables color overexposure compensation.

            \b Visibility = Beginner


            \b Selected by : ColorOverexposureCompensationAOISelector

        */
        GENAPI_NAMESPACE::IBoolean& ColorOverexposureCompensationAOIEnable;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Sets the color overexposure compensation factor for the selected C.O.C. AOI

            Sets the color overexposure compensation factor controlling the extent of compensation for the selected C.O.C. AOI.

            \b Visibility = Guru

            \b Selected by : ColorOverexposureCompensationAOISelector

        */
        GENAPI_NAMESPACE::IFloat& ColorOverexposureCompensationAOIFactor;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Sets the raw value for the color overexposure compensation factor

            Sets the raw value for the color overexposure compensation factor.

            \b Visibility = Guru

            \b Selected by : ColorOverexposureCompensationAOISelector

        */
        GENAPI_NAMESPACE::IInteger& ColorOverexposureCompensationAOIFactorRaw;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Sets the width for the selected C.O.C. AOI

            Sets the width for the selected Color Overexposure Compensation AOI.

            \b Visibility = Guru

            \b Selected by : ColorOverexposureCompensationAOISelector

        */
        GENAPI_NAMESPACE::IInteger& ColorOverexposureCompensationAOIWidth;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Sets the height for the selected C.O.C. AOI

            Sets the height for the selected Color Overexposure Compensation AOI.

            \b Visibility = Guru

            \b Selected by : ColorOverexposureCompensationAOISelector

        */
        GENAPI_NAMESPACE::IInteger& ColorOverexposureCompensationAOIHeight;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Sets the X offset for the selected C.O.C. AOI

            Sets the horizontal offset for the selected Color Overexposure Compensation AOI.

            \b Visibility = Guru

            \b Selected by : ColorOverexposureCompensationAOISelector

        */
        GENAPI_NAMESPACE::IInteger& ColorOverexposureCompensationAOIOffsetX;

        //@}


        //! \name ColorOverexposureCompensation - Compensates for deviations of hue resulting from overexposure
        //@{
        /*!
            \brief Sets the Y offset for the selected C.O.C. AOI

            Sets the vertical offset for the selected Color Overexposure Compensation AOI.

            \b Visibility = Guru

            \b Selected by : ColorOverexposureCompensationAOISelector

        */
        GENAPI_NAMESPACE::IInteger& ColorOverexposureCompensationAOIOffsetY;

        //@}


        //! \name Shading - Includes items used to control the operation of the camera's shading correction.
        //@{
        /*!
            \brief Selects the kind of shading correction.

            This enumeration selects the kind of shading correction.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ShadingSelectorEnums >& ShadingSelector;

        //@}


        //! \name Shading - Includes items used to control the operation of the camera's shading correction.
        //@{
        /*!
            \brief Enables the selected kind of shading correction.

            This boolean value enables the selected kind of shading correction.

            \b Visibility = Beginner


            \b Selected by : ShadingSelector

        */
        GENAPI_NAMESPACE::IBoolean& ShadingEnable;

        //@}


        //! \name Shading - Includes items used to control the operation of the camera's shading correction.
        //@{
        /*!
            \brief Indicates error statuses related to shading correction.

            This enumeratuion indicates error statuses related to shading correction.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ShadingStatusEnums >& ShadingStatus;

        //@}


        //! \name Shading - Includes items used to control the operation of the camera's shading correction.
        //@{
        /*!
            \brief Selects the bootup shading set.

            This enumeration selects the shading set that will be loaded into the volatile memory during camera bootup.

            \b Visibility = Expert

            \b Selected by : ShadingSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ShadingSetDefaultSelectorEnums >& ShadingSetDefaultSelector;

        //@}


        //! \name Shading - Includes items used to control the operation of the camera's shading correction.
        //@{
        /*!
            \brief Selects the shading set to which the activate command will be applied.

            This enumeration selects the shading set to which the activate command will be applied.

            \b Visibility = Expert

            \b Selected by : ShadingSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ShadingSetSelectorEnums >& ShadingSetSelector;

        //@}


        //! \name Shading - Includes items used to control the operation of the camera's shading correction.
        //@{
        /*!
            \brief Activates the selected shading set.

            This command copies the selected shading set from the camera's non-volatile memory into the volatile memory. Shading correction is performed using the shading set in the volatile memory.

            \b Visibility = Expert

            \b Selected by : ShadingSetSelector

        */
        GENAPI_NAMESPACE::ICommand& ShadingSetActivate;

        //@}


        //! \name Shading - Includes items used to control the operation of the camera's shading correction.
        //@{
        /*!
            \brief Creates a shading set.

            ShadingSetCreate

            \b Visibility = Expert

            \b Selected by : ShadingSetSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ShadingSetCreateEnums >& ShadingSetCreate;

        //@}


        //! \name UserDefinedValues -
        //@{
        /*!
            \brief



            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<UserDefinedValueSelectorEnums >& UserDefinedValueSelector;

        //@}


        //! \name UserDefinedValues -
        //@{
        /*!
            \brief



            \b Visibility = Guru

            \b Selected by : UserDefinedValueSelector

        */
        GENAPI_NAMESPACE::IInteger& UserDefinedValue;

        //@}


        //! \name FeatureSets -
        //@{
        /*!
            \brief Select default genicam XML file

            If the camera contains multiple GenICam XML files, this parameter determines which of them is accessible to non-manifest-aware software accessing register address 0x0200 (first url).

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& GenicamXmlFileDefault;

        //@}


        //! \name FeatureSets -
        //@{
        /*!
            \brief Select a camera description file

            Selects a feature set description file.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<FeatureSetEnums >& FeatureSet;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the name of the device's vendor

            This is a read only element. It is a text description that indicates the name of the device's vendor.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IString& DeviceVendorName;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the model name of the device

            This is a read only element. It is a text description that indicates the model name of the device.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IString& DeviceModelName;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Provides additional information from the vendor about the device

            This is a read only element. It is a string that provides additional information from the vendor about the camera.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IString& DeviceManufacturerInfo;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the version of the device

            This is a read only element. It is a string that indicates the version of the device.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IString& DeviceVersion;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the version of the device's firmware and software

            This is a read only element. It is a string that indicates the version of the device's firmware and software.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IString& DeviceFirmwareVersion;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief A unique identifier for the device such as a serial number or a GUID

            This is a read only element. It is a string that provides a unique identifier for the device such as a serial number or a GUID.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IString& DeviceID;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief A device ID that is user programmable

            This is a read/write element. It is a user programmable string.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IString& DeviceUserID;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the scan type of the device's sensor

            This enumeration lists the possible scan types for the sensor in the device.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<DeviceScanTypeEnums >& DeviceScanType;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Immediately resets and reboots the device

            This is a command that immediately resets and reboots the device.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::ICommand& DeviceReset;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Lists the temperature sources available for readout

            Lists the temperature sources available for readout

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<TemperatureSelectorEnums >& TemperatureSelector;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Shows the current temperature of the selected target in degrees centigrade

            Shows the current temperature of the selected target in degrees centigrade

            \b Visibility = Expert

            \b Selected by : TemperatureSelector

        */
        GENAPI_NAMESPACE::IFloat& TemperatureAbs;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Temperature State

            Temperature State

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<TemperatureStateEnums >& TemperatureState;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Shows the over temperature state of the selected target

            Shows the over temperature state of the selected target

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& CriticalTemperature;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Shows the over temperature state of the selected target

            Shows the over temperature state of the selected target

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& OverTemperature;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Indicates the error that was detected last

            Indicates the error that was detected last.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<LastErrorEnums >& LastError;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Erases the last error and possibly reveals a previous error

            Erases the last error and possibly reveals a previous error.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& ClearLastError;

        //@}


        //! \name DeviceInformation - This category includes items that describe the device and its sensor
        //@{
        /*!
            \brief Version of the color modifications applied to images.

            Version of the color modifications applied to images.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& DeviceColorPipelineVersion;

        //@}


        //! \name RemoveParamLimits - This category includes items that allow removing the limits of camera parameters
        //@{
        /*!
            \brief Selects the parameter to configure. Once a parameter has been selected, all changes made using the Remove Limits feature will be applied to the selected parameter

            This enumeration selects the parameter to configure. Selects the parameter to configure. Once a parameter has been selected, all changes made using the Remove Limits feature will be applied to the selected parameter

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<ParameterSelectorEnums >& ParameterSelector;

        //@}


        //! \name RemoveParamLimits - This category includes items that allow removing the limits of camera parameters
        //@{
        /*!
            \brief Removes the factory-set limits of the selected parameter.

            Removes the factory-set limits of the selected parameter. Having removed the factory-set limits you may set the parameter within extended limits. These are only defined by technical restrictions. Note:  Inferior image quality may result.

            \b Visibility = Guru

            \b Selected by : ParameterSelector

        */
        GENAPI_NAMESPACE::IBoolean& RemoveLimits;

        //@}


        //! \name RemoveParamLimits - This category includes items that allow removing the limits of camera parameters
        //@{
        /*!
            \brief Sets the number of prelines

            This value sets the number of prelines.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& Prelines;

        //@}


        //! \name ExpertFeatureAccess -
        //@{
        /*!
            \brief Selects the feature to configure. Once a feature has been selected, all changes made using the feature enable feature will be applied to the selected feature

            Selects the feature to configure. Once a feature has been selected, all changes made using the feature enable feature will be applied to the selected feature

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<ExpertFeatureAccessSelectorEnums >& ExpertFeatureAccessSelector;

        //@}


        //! \name ExpertFeatureAccess -
        //@{
        /*!
            \brief Sets the key to access the selected feature

            Sets the key to access the selected feature

            \b Visibility = Guru

            \b Selected by : ExpertFeatureAccessSelector

        */
        GENAPI_NAMESPACE::IInteger& ExpertFeatureAccessKey;

        //@}


        //! \name ExpertFeatureAccess -
        //@{
        /*!
            \brief Enable the selected Feature

            Enable the selected Feature

            \b Visibility = Guru

            \b Selected by : ExpertFeatureAccessSelector

        */
        GENAPI_NAMESPACE::IBoolean& ExpertFeatureEnable;

        //@}


        //! \name ChunkDataStreams - This category includes items that control the chunk features available on the camera.
        //@{
        /*!
            \brief Enables the chunk mode

            This boolean value enables the camera's chunk mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& ChunkModeActive;

        //@}


        //! \name ChunkDataStreams - This category includes items that control the chunk features available on the camera.
        //@{
        /*!
            \brief Selects chunks for enabling.

            This enumeration selects chunks for enabling.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ChunkSelectorEnums >& ChunkSelector;

        //@}


        //! \name ChunkDataStreams - This category includes items that control the chunk features available on the camera.
        //@{
        /*!
            \brief Enables the inclusion of the selected chunk in the payload data

            This boolean value enables the inclusion of the selected chunk in the payload data.

            \b Visibility = Beginner


            \b Selected by : ChunkSelector

        */
        GENAPI_NAMESPACE::IBoolean& ChunkEnable;

        //@}


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


        //! \name EventsGeneration - This category includes items that control event generation by the camera.
        //@{
        /*!
            \brief Selects the type of event for enabling.

            This enumeration selects the type of event for enabling.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<EventSelectorEnums >& EventSelector;

        //@}


        //! \name EventsGeneration - This category includes items that control event generation by the camera.
        //@{
        /*!
            \brief Sets the notification type that will be sent to the host application for the selected event

            This enumeration sets the notification type that will be sent to the host application for the selected event.

            \b Visibility = Beginner


            \b Selected by : EventSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<EventNotificationEnums >& EventNotification;

        //@}


        //! \name ExposureEndEventData - This category includes items available for an exposure end event
        //@{
        /*!
            \brief Indicates the stream channel index for an exposure end event

            This enumeration value indicates the stream channel index for an exposure end event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ExposureEndEventStreamChannelIndex;

        //@}


        //! \name ExposureEndEventData - This category includes items available for an exposure end event
        //@{
        /*!
            \brief Indicates the frame ID for an exposure end event

            This enumeration value indicates the frame ID for an exposure end event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ExposureEndEventFrameID;

        //@}


        //! \name ExposureEndEventData - This category includes items available for an exposure end event
        //@{
        /*!
            \brief Indicates the time stamp for an exposure end event

            This enumeration value indicates the time stamp for an exposure end event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ExposureEndEventTimestamp;

        //@}


        //! \name LineStartOvertriggerEventData - This category includes items available for an line start overtrigger event
        //@{
        /*!
            \brief Indicates the stream channel index for an line start overtrigger event

            This enumeration Indicates the stream channel index for an line start overtrigger event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& LineStartOvertriggerEventStreamChannelIndex;

        //@}


        //! \name LineStartOvertriggerEventData - This category includes items available for an line start overtrigger event
        //@{
        /*!
            \brief Indicates the time stamp for an line start overtrigger event

            This enumeration value indicates the time stamp for an line start overtrigger event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& LineStartOvertriggerEventTimestamp;

        //@}


        //! \name FrameStartOvertriggerEventData - This category includes items available for an frame start overtrigger event
        //@{
        /*!
            \brief Indicates the stream channel index for an frame start overtrigger event

            This enumeration Indicates the stream channel index for an frame start overtrigger event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameStartOvertriggerEventStreamChannelIndex;

        //@}


        //! \name FrameStartOvertriggerEventData - This category includes items available for an frame start overtrigger event
        //@{
        /*!
            \brief Indicates the time stamp for an frame start overtrigger event

            This enumeration value indicates the time stamp for an frame start overtrigger event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameStartOvertriggerEventTimestamp;

        //@}


        //! \name FrameStartEventData - This category includes items available for an frame start  event
        //@{
        /*!
            \brief Indicates the stream channel index for an frame start  event

            This enumeration Indicates the stream channel index for an frame start  event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameStartEventStreamChannelIndex;

        //@}


        //! \name FrameStartEventData - This category includes items available for an frame start  event
        //@{
        /*!
            \brief Indicates the time stamp for an frame start  event

            This enumeration value indicates the time stamp for an frame start  event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameStartEventTimestamp;

        //@}


        //! \name AcquisitionStartEventData - This category includes items available for an acquisition start  event
        //@{
        /*!
            \brief Indicates the stream channel index for an acquisition start  event

            This enumeration Indicates the stream channel index for an acquisition start  event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionStartEventStreamChannelIndex;

        //@}


        //! \name AcquisitionStartEventData - This category includes items available for an acquisition start  event
        //@{
        /*!
            \brief Indicates the time stamp for an acquisition start  event

            This enumeration value indicates the time stamp for an acquisition start  event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionStartEventTimestamp;

        //@}


        //! \name AcquisitionStartOvertriggerEventData - This category includes items available for an acquisition start overtrigger event
        //@{
        /*!
            \brief Indicates the stream channel index for an acquisition start overtrigger event

            This enumeration Indicates the stream channel index for an acquisition start overtrigger event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionStartOvertriggerEventStreamChannelIndex;

        //@}


        //! \name AcquisitionStartOvertriggerEventData - This category includes items available for an acquisition start overtrigger event
        //@{
        /*!
            \brief Indicates the time stamp for an Acquisition start overtrigger event

            This enumeration value indicates the time stamp for an Acquisition start overtrigger event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionStartOvertriggerEventTimestamp;

        //@}


        //! \name FrameTimeoutEventData - This category includes items available for an frame timeout event
        //@{
        /*!
            \brief Indicates the stream channel index for an frame timeout event

            This enumeration Indicates the stream channel index for an frame timeout event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameTimeoutEventStreamChannelIndex;

        //@}


        //! \name FrameTimeoutEventData - This category includes items available for an frame timeout event
        //@{
        /*!
            \brief Indicates the time stamp for an frame timeout event

            This enumeration value indicates the time stamp for an frame timeout event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameTimeoutEventTimestamp;

        //@}


        //! \name EventOverrunEventData - This category includes items available for an event overrun event
        //@{
        /*!
            \brief Indicates the stream channel index for an event overrun event

            This enumeration value indicates the stream channel index for an event overrun event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventOverrunEventStreamChannelIndex;

        //@}


        //! \name EventOverrunEventData - This category includes items available for an event overrun event
        //@{
        /*!
            \brief Indicates the frame ID for an event overrun event

            This enumeration value indicates the frame ID for an event overrun event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventOverrunEventFrameID;

        //@}


        //! \name EventOverrunEventData - This category includes items available for an event overrun event
        //@{
        /*!
            \brief Indicates the time stamp for an event overrun event

            This enumeration value indicates the time stamp for an event overrun event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventOverrunEventTimestamp;

        //@}


        //! \name CriticalTemperatureEventData - This category includes items available for a critical temperature event
        //@{
        /*!
            \brief Indicates the stream channel index for a critical temperature event

            This enumeration Indicates the stream channel index for a critical temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& CriticalTemperatureEventStreamChannelIndex;

        //@}


        //! \name CriticalTemperatureEventData - This category includes items available for a critical temperature event
        //@{
        /*!
            \brief Indicates the time stamp for a critical temperature event

            This enumeration value indicates the time stamp for a critical temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& CriticalTemperatureEventTimestamp;

        //@}


        //! \name OverTemperatureEventData - This category includes items available for an over temperature event
        //@{
        /*!
            \brief Indicates the stream channel index for an over temperature event

            This enumeration Indicates the stream channel index for an over temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& OverTemperatureEventStreamChannelIndex;

        //@}


        //! \name OverTemperatureEventData - This category includes items available for an over temperature event
        //@{
        /*!
            \brief Indicates the time stamp for an over temperature event

            This enumeration value indicates the time stamp for an over temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& OverTemperatureEventTimestamp;

        //@}


        //! \name ActionLateEventData - Contains parameters available for a action late event.
        //@{
        /*!
            \brief Stream channel index of the action late event.

            Stream channel index of the action late event. A action late event is raised when a scheduled action command with a timestamp in the past is received.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ActionLateEventStreamChannelIndex;

        //@}


        //! \name ActionLateEventData - Contains parameters available for a action late event.
        //@{
        /*!
            \brief Time stamp of the action late event.

            Time stamp of the action late event. A action late event is raised when a scheduled action command with a timestamp in the past is received.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ActionLateEventTimestamp;

        //@}


        //! \name LateActionEventData - TODO
        //@{
        /*!
            \brief Indicates the stream channel index for a critical temperature event

            This enumeration Indicates the stream channel index for a critical temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& LateActionEventStreamChannelIndex;

        //@}


        //! \name LateActionEventData - TODO
        //@{
        /*!
            \brief Indicates the time stamp for a critical temperature event

            This enumeration value indicates the time stamp for a critical temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& LateActionEventTimestamp;

        //@}


        //! \name Line1RisingEdgeEventData - This category includes items available for an io line 1 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io line 1 rising edge event

            This enumeration Indicates the stream channel index for an io line 1 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line1RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Line1RisingEdgeEventData - This category includes items available for an io line 1 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a line 1 rising edge event

            This enumeration value indicates the time stamp for an io line 1 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line1RisingEdgeEventTimestamp;

        //@}


        //! \name Line2RisingEdgeEventData - This category includes items available for an io line 2 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io line 2 rising edge event

            This enumeration Indicates the stream channel index for an io line 2 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line2RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Line2RisingEdgeEventData - This category includes items available for an io line 2 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a line 2 rising edge event

            This enumeration value indicates the time stamp for an io line 2 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line2RisingEdgeEventTimestamp;

        //@}


        //! \name Line3RisingEdgeEventData - This category includes items available for an io line 3 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io line 3 rising edge event

            This enumeration Indicates the stream channel index for an io line 3 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line3RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Line3RisingEdgeEventData - This category includes items available for an io line 3 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a line 3 rising edge event

            This enumeration value indicates the time stamp for an io line 3 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line3RisingEdgeEventTimestamp;

        //@}


        //! \name Line4RisingEdgeEventData - This category includes items available for an io line 4 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io line 4 rising edge event

            This enumeration Indicates the stream channel index for an io line 4 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line4RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Line4RisingEdgeEventData - This category includes items available for an io line 4 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a line 4 rising edge event

            This enumeration value indicates the time stamp for an io line 4 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& Line4RisingEdgeEventTimestamp;

        //@}


        //! \name VirtualLine1RisingEdgeEventData - This category includes items available for an io virtual line 1 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io virtual line 1 rising edge event

            This enumeration Indicates the stream channel index for an io virtual line 1 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine1RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name VirtualLine1RisingEdgeEventData - This category includes items available for an io virtual line 1 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a virtual line 1 rising edge event

            This enumeration value indicates the time stamp for an io virtual line 1 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine1RisingEdgeEventTimestamp;

        //@}


        //! \name VirtualLine2RisingEdgeEventData - This category includes items available for an io virtual line 2 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io virtual line 2 rising edge event

            This enumeration Indicates the stream channel index for an io virtual line 2 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine2RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name VirtualLine2RisingEdgeEventData - This category includes items available for an io virtual line 2 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a virtual line 2 rising edge event

            This enumeration value indicates the time stamp for an io virtual line 2 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine2RisingEdgeEventTimestamp;

        //@}


        //! \name VirtualLine3RisingEdgeEventData - This category includes items available for an io virtual line 3 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io virtual line 3 rising edge event

            This enumeration Indicates the stream channel index for an io virtual line 3 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine3RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name VirtualLine3RisingEdgeEventData - This category includes items available for an io virtual line 3 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a virtual line 3 rising edge event

            This enumeration value indicates the time stamp for an io virtual line 3 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine3RisingEdgeEventTimestamp;

        //@}


        //! \name VirtualLine4RisingEdgeEventData - This category includes items available for an io virtual line 4 rising edge event
        //@{
        /*!
            \brief Indicates the stream channel index for an io virtual line 4 rising edge event

            This enumeration Indicates the stream channel index for an io virtual line 4 rising edge event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine4RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name VirtualLine4RisingEdgeEventData - This category includes items available for an io virtual line 4 rising edge event
        //@{
        /*!
            \brief Indicates the time stamp for a virtual line 4 rising edge event

            This enumeration value indicates the time stamp for an io virtual line 4 rising edge event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& VirtualLine4RisingEdgeEventTimestamp;

        //@}


        //! \name FrameWaitEventData - This category includes items available for an frame wait event
        //@{
        /*!
            \brief Indicates the stream channel index for an frame wait event

            This enumeration Indicates the stream channel index for an frame wait event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameWaitEventStreamChannelIndex;

        //@}


        //! \name FrameWaitEventData - This category includes items available for an frame wait event
        //@{
        /*!
            \brief Indicates the time stamp for an frame wait event

            This enumeration value indicates the time stamp for an frame wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameWaitEventTimestamp;

        //@}


        //! \name AcquisitionWaitEventData - This category includes items available for an acquisition wait event
        //@{
        /*!
            \brief Indicates the stream channel index for an acquisition wait event

            This enumeration Indicates the stream channel index for an acquisition wait event

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionWaitEventStreamChannelIndex;

        //@}


        //! \name AcquisitionWaitEventData - This category includes items available for an acquisition wait event
        //@{
        /*!
            \brief Indicates the time stamp for an acquisition wait event

            This enumeration value indicates the time stamp for an acquisition wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionWaitEventTimestamp;

        //@}


        //! \name FrameStartWaitEventData - Contains parameters available for a frame start wait event.
        //@{
        /*!
            \brief Stream channel index of the frame start wait event.

            Stream channel index of the frame start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameStartWaitEventStreamChannelIndex;

        //@}


        //! \name FrameStartWaitEventData - Contains parameters available for a frame start wait event.
        //@{
        /*!
            \brief Time stamp of the frame start wait event.

            Time stamp of the frame start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& FrameStartWaitEventTimestamp;

        //@}


        //! \name AcquisitionStartWaitEventData - Contains parameters available for an acquisition start wait event.
        //@{
        /*!
            \brief Stream channel index of the acquisition start wait event.

            Stream channel index of the acquisition start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionStartWaitEventStreamChannelIndex;

        //@}


        //! \name AcquisitionStartWaitEventData - Contains parameters available for an acquisition start wait event.
        //@{
        /*!
            \brief Time stamp of the acquisition start wait event.

            Time stamp of the acquisition start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionStartWaitEventTimestamp;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief This feature selects the target file in the device

            The File Selector feature selects the target file in the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<FileSelectorEnums >& FileSelector;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Selects the target operation for the selected file

            The File Operation Selector feature selects the target operation for the selected file in the device. This Operation is executed when the FileOperationExecute feature is called.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<FileOperationSelectorEnums >& FileOperationSelector;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Selects the access mode in which a file is opened

            The File Open Mode feature selects the access mode in which a file is opened in the device.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<FileOpenModeEnums >& FileOpenMode;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Defines the intermediate access buffer

            The File Access Buffer feature defines the intermediate access buffer that allows the exchange of data between the device file storage and the application.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IRegister& FileAccessBuffer;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Controls the mapping between the device file storage and the FileAccessBuffer

            This feature controls the mapping between the device file storage and the FileAccessBuffer.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IInteger& FileAccessOffset;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Controls the mapping between the device file storage and the FileAccessBuffer

            This feature controls the mapping between the device file storage and the FileAccessBuffer.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IInteger& FileAccessLength;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Represents the file operation execution status

            The File Operation Status feature represents the file operation execution status.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<FileOperationStatusEnums >& FileOperationStatus;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Represents the file operation result

            The File Operation Result feature represents the file operation result. For Read or Write operations, the number of successfully read/written bytes is returned.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IInteger& FileOperationResult;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Represents the size of the selected file

            The File Size feature represents the size of the selected file in bytes.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IInteger& FileSize;

        //@}


        //! \name FileAccessControl - This category includes items used to conduct file operations
        //@{
        /*!
            \brief Executes the selected operation

            The File Operation Execute feature is the command that executes the operation selected by FileOperationSelector on the selected file.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::ICommand& FileOperationExecute;

        //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
        CGigECamera_Params( CGigECamera_Params& );

        //! not implemented assignment operator
        CGigECamera_Params& operator=( CGigECamera_Params& );

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CGigECamera_Params::CGigECamera_Params( void )
        : SequenceEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , SequenceCurrentSet( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequenceConfigurationMode( *new GENAPI_NAMESPACE::CEnumerationTRef<SequenceConfigurationModeEnums>() )
        , SequenceAsyncRestart( *new GENAPI_NAMESPACE::CCommandRef() )
        , SequenceAsyncAdvance( *new GENAPI_NAMESPACE::CCommandRef() )
        , SequenceSetTotalNumber( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequenceSetIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequenceSetStore( *new GENAPI_NAMESPACE::CCommandRef() )
        , SequenceSetLoad( *new GENAPI_NAMESPACE::CCommandRef() )
        , SequenceSetExecutions( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequenceAdvanceMode( *new GENAPI_NAMESPACE::CEnumerationTRef<SequenceAdvanceModeEnums>() )
        , SequenceControlSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSelectorEnums>() )
        , SequenceControlSource( *new GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>() )
        , SequenceAddressBitSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>() )
        , SequenceAddressBitSource( *new GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>() )
        , GainAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>() )
        , GainSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>() )
        , GainRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GainAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , BlackLevelSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>() )
        , BlackLevelRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BlackLevelAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , GammaEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GammaSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<GammaSelectorEnums>() )
        , Gamma( *new GENAPI_NAMESPACE::CFloatRef() )
        , DigitalShift( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SubstrateVoltage( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SensorBitDepth( *new GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>() )
        , SensorDigitizationTaps( *new GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>() )
        , PixelFormat( *new GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>() )
        , PixelCoding( *new GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>() )
        , PixelSize( *new GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>() )
        , PixelColorFilter( *new GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>() )
        , ProcessedRawEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , PixelDynamicRangeMin( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PixelDynamicRangeMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SpatialCorrection( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SpatialCorrectionAmount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SpatialCorrectionStartingLine( *new GENAPI_NAMESPACE::CEnumerationTRef<SpatialCorrectionStartingLineEnums>() )
        , ReverseX( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ReverseY( *new GENAPI_NAMESPACE::CBooleanRef() )
        , FieldOutputMode( *new GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>() )
        , TestImageSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>() )
        , TestImageResetAndHold( *new GENAPI_NAMESPACE::CBooleanRef() )
        , SensorWidth( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SensorHeight( *new GENAPI_NAMESPACE::CIntegerRef() )
        , WidthMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , HeightMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LightSourceSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>() )
        , BalanceWhiteReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , BalanceWhiteAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>() )
        , BalanceRatioSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>() )
        , BalanceRatioAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , BalanceRatioRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorTransformationSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>() )
        , ColorTransformationValueSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>() )
        , ColorTransformationValue( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorTransformationValueRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorTransformationMatrixFactor( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorTransformationMatrixFactorRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorAdjustmentEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ColorAdjustmentReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , ColorAdjustmentSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>() )
        , ColorAdjustmentHue( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorAdjustmentHueRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorAdjustmentSaturation( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorAdjustmentSaturationRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslHue( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslHueRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslSaturation( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslSaturationRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslBrightness( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslBrightnessRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslContrast( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslContrastRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslContrastMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>() )
        , DemosaicingMode( *new GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>() )
        , PgiMode( *new GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>() )
        , NoiseReductionAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , NoiseReductionRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SharpnessEnhancementAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , SharpnessEnhancementRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TonalRangeEnable( *new GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>() )
        , TonalRangeAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>() )
        , TonalRangeSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>() )
        , TonalRangeSourceBright( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TonalRangeSourceDark( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TonalRangeTargetBright( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TonalRangeTargetDark( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Width( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Height( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OffsetX( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )
        , CenterX( *new GENAPI_NAMESPACE::CBooleanRef() )
        , CenterY( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LegacyBinningVertical( *new GENAPI_NAMESPACE::CEnumerationTRef<LegacyBinningVerticalEnums>() )
        , BinningHorizontalMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>() )
        , BinningModeHorizontal( *new GENAPI_NAMESPACE::CEnumerationTRef<BinningModeHorizontalEnums>() )
        , BinningHorizontal( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BinningVerticalMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>() )
        , BinningModeVertical( *new GENAPI_NAMESPACE::CEnumerationTRef<BinningModeVerticalEnums>() )
        , BinningVertical( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DecimationHorizontal( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DecimationVertical( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ScalingHorizontalAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ScalingVerticalAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ROIZoneSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>() )
        , ROIZoneMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>() )
        , ROIZoneSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ROIZoneOffset( *new GENAPI_NAMESPACE::CIntegerRef() )
        , StackedZoneImagingEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , StackedZoneImagingIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , StackedZoneImagingZoneEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , StackedZoneImagingZoneOffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )
        , StackedZoneImagingZoneHeight( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EnableBurstAcquisition( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AcquisitionMode( *new GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>() )
        , AcquisitionStart( *new GENAPI_NAMESPACE::CCommandRef() )
        , AcquisitionStop( *new GENAPI_NAMESPACE::CCommandRef() )
        , AcquisitionAbort( *new GENAPI_NAMESPACE::CCommandRef() )
        , AcquisitionFrameCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TriggerControlImplementation( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerControlImplementationEnums>() )
        , TriggerSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>() )
        , TriggerMode( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>() )
        , TriggerSoftware( *new GENAPI_NAMESPACE::CCommandRef() )
        , TriggerSource( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>() )
        , TriggerActivation( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>() )
        , TriggerPartialClosingFrame( *new GENAPI_NAMESPACE::CBooleanRef() )
        , TriggerDelaySource( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerDelaySourceEnums>() )
        , TriggerDelayAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , TriggerDelayLineTriggerCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ExposureStartDelayAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ExposureStartDelayRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ExposureMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>() )
        , InterlacedIntegrationMode( *new GENAPI_NAMESPACE::CEnumerationTRef<InterlacedIntegrationModeEnums>() )
        , ExposureAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>() )
        , ExposureTimeMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>() )
        , ExposureTimeAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ExposureTimeBaseAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ExposureTimeBaseAbsEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ExposureTimeRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ReadoutTimeAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ExposureOverlapTimeMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>() )
        , ExposureOverlapTimeMaxAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ExposureOverlapTimeMaxRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GlobalResetReleaseModeEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ShutterMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>() )
        , SensorReadoutMode( *new GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>() )
        , AcquisitionLineRateAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ResultingLinePeriodAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ResultingLineRateAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , AcquisitionFrameRateEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AcquisitionFrameRateAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ResultingFramePeriodAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , ResultingFrameRateAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , AcquisitionStatusSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>() )
        , AcquisitionStatus( *new GENAPI_NAMESPACE::CBooleanRef() )
        , FrameTimeoutEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , FrameTimeoutAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , SyncFreeRunTimerEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , SyncFreeRunTimerStartTimeLow( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SyncFreeRunTimerStartTimeHigh( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SyncFreeRunTimerTriggerRateAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , SyncFreeRunTimerUpdate( *new GENAPI_NAMESPACE::CCommandRef() )
        , LineSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>() )
        , LineMode( *new GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>() )
        , LineLogic( *new GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>() )
        , LineFormat( *new GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>() )
        , LineSource( *new GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>() )
        , LineInverter( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LineTermination( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LineDebouncerTimeAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , LineDebouncerTimeRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , MinOutPulseWidthRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , MinOutPulseWidthAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , LineStatus( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LineStatusAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , UserOutputSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>() )
        , UserOutputValue( *new GENAPI_NAMESPACE::CBooleanRef() )
        , UserOutputValueAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , UserOutputValueAllMask( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SyncUserOutputSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>() )
        , SyncUserOutputValue( *new GENAPI_NAMESPACE::CBooleanRef() )
        , SyncUserOutputValueAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VInpSignalSource( *new GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>() )
        , VInpBitLength( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VInpSamplingPoint( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VInpSignalReadoutActivation( *new GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalReadoutActivationEnums>() )
        , ShaftEncoderModuleLineSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSelectorEnums>() )
        , ShaftEncoderModuleLineSource( *new GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>() )
        , ShaftEncoderModuleMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleModeEnums>() )
        , ShaftEncoderModuleCounterMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleCounterModeEnums>() )
        , ShaftEncoderModuleCounter( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ShaftEncoderModuleCounterMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ShaftEncoderModuleCounterReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , ShaftEncoderModuleReverseCounterMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ShaftEncoderModuleReverseCounterReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , FrequencyConverterInputSource( *new GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>() )
        , FrequencyConverterSignalAlignment( *new GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterSignalAlignmentEnums>() )
        , FrequencyConverterPreDivider( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrequencyConverterMultiplier( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrequencyConverterPostDivider( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrequencyConverterPreventOvertrigger( *new GENAPI_NAMESPACE::CBooleanRef() )
        , TimerDelayTimebaseAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , TimerDurationTimebaseAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , TimerSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>() )
        , TimerDelayAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , TimerDelayRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TimerDurationAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , TimerDurationRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TimerTriggerSource( *new GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>() )
        , TimerTriggerActivation( *new GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>() )
        , CounterSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>() )
        , CounterEventSource( *new GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>() )
        , CounterResetSource( *new GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>() )
        , CounterReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , TimerSequenceEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , TimerSequenceLastEntryIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TimerSequenceCurrentEntryIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TimerSequenceEntrySelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>() )
        , TimerSequenceTimerSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>() )
        , TimerSequenceTimerEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , TimerSequenceTimerInverter( *new GENAPI_NAMESPACE::CBooleanRef() )
        , TimerSequenceTimerDelayRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TimerSequenceTimerDurationRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LUTSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>() )
        , LUTEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LUTIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LUTValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LUTValueAll( *new GENAPI_NAMESPACE::CRegisterRef() )
        , PayloadSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCPSPacketSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCPD( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCFTD( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCBWR( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCBWRA( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCBWA( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCDMT( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCDCT( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCFJM( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevVersionMajor( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevVersionMinor( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevDeviceModeIsBigEndian( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevDeviceModeCharacterSet( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevInterfaceSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<GevInterfaceSelectorEnums>() )
        , GevMACAddress( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevGVSPExtendedIDMode( *new GENAPI_NAMESPACE::CEnumerationTRef<GevGVSPExtendedIDModeEnums>() )
        , GevSupportedIPConfigurationLLA( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedIPConfigurationDHCP( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedIPConfigurationPersistentIP( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevCurrentIPConfiguration( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevCurrentIPAddress( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevCurrentSubnetMask( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevCurrentDefaultGateway( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPersistentIPAddress( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPersistentSubnetMask( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPersistentDefaultGateway( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevLinkSpeed( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevLinkMaster( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevLinkFullDuplex( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevLinkCrossover( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevFirstURL( *new GENAPI_NAMESPACE::CStringRef() )
        , GevSecondURL( *new GENAPI_NAMESPACE::CStringRef() )
        , GevNumberOfInterfaces( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevMessageChannelCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevStreamChannelCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSupportedOptionalLegacy16BitBlockID( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedIEEE1588( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedOptionalCommandsEVENTDATA( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedOptionalCommandsEVENT( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedOptionalCommandsPACKETRESEND( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedOptionalCommandsWRITEMEM( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSupportedOptionalCommandsConcatenation( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevHeartbeatTimeout( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevTimestampTickFrequency( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevTimestampControlLatch( *new GENAPI_NAMESPACE::CCommandRef() )
        , GevTimestampControlReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , GevTimestampControlLatchReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , GevTimestampValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevCCP( *new GENAPI_NAMESPACE::CEnumerationTRef<GevCCPEnums>() )
        , GevStreamChannelSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<GevStreamChannelSelectorEnums>() )
        , GevSCPInterfaceIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCDA( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCPHostPort( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevSCPSFireTestPacket( *new GENAPI_NAMESPACE::CCommandRef() )
        , GevSCPSDoNotFragment( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevSCPSBigEndian( *new GENAPI_NAMESPACE::CBooleanRef() )
        , TLParamsLocked( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PixelFormatLegacy( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevIEEE1588( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GevIEEE1588Status( *new GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>() )
        , GevIEEE1588DataSetLatch( *new GENAPI_NAMESPACE::CCommandRef() )
        , GevIEEE1588StatusLatched( *new GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>() )
        , GevIEEE1588OffsetFromMaster( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevIEEE1588ClockIdLow( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevIEEE1588ClockIdHigh( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevIEEE1588ClockId( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevIEEE1588ParentClockIdLow( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevIEEE1588ParentClockIdHigh( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevIEEE1588ParentClockId( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPTPDiagnosticsQueueRxEvntMaxNumElements( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPTPDiagnosticsQueueRxGnrlMaxNumElements( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPTPDiagnosticsQueueRxEvntPushNumFailure( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPTPDiagnosticsQueueRxGnrlPushNumFailure( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GevPTPDiagnosticsQueueSendNumFailure( *new GENAPI_NAMESPACE::CIntegerRef() )
        , NumberOfActionSignals( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ActionCommandCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ActionDeviceKey( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ActionSelector( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ActionGroupKey( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ActionGroupMask( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceRegistersStreamingStart( *new GENAPI_NAMESPACE::CCommandRef() )
        , DeviceRegistersStreamingEnd( *new GENAPI_NAMESPACE::CCommandRef() )
        , UserSetSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>() )
        , UserSetLoad( *new GENAPI_NAMESPACE::CCommandRef() )
        , UserSetSave( *new GENAPI_NAMESPACE::CCommandRef() )
        , UserSetDefaultSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>() )
        , DefaultSetSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>() )
        , AutoTargetValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GrayValueAdjustmentDampingAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , GrayValueAdjustmentDampingRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BalanceWhiteAdjustmentDampingAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , BalanceWhiteAdjustmentDampingRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoGainRawLowerLimit( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoGainRawUpperLimit( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoExposureTimeAbsLowerLimit( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoExposureTimeAbsUpperLimit( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoFunctionProfile( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>() )
        , AutoFunctionAOISelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>() )
        , AutoFunctionAOIWidth( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionAOIHeight( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionAOIOffsetX( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionAOIOffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionAOIUsageIntensity( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AutoFunctionAOIUsageWhiteBalance( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AutoFunctionAOIUsageRedLightCorrection( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AutoFunctionAOIUsageTonalRange( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AutoTonalRangeModeSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>() )
        , AutoTonalRangeAdjustmentSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>() )
        , AutoTonalRangeThresholdDark( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoTonalRangeThresholdDarkRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoTonalRangeThresholdBright( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoTonalRangeThresholdBrightRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoTonalRangeTargetDark( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoTonalRangeTargetBright( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorOverexposureCompensationAOISelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorOverexposureCompensationAOISelectorEnums>() )
        , ColorOverexposureCompensationAOIEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ColorOverexposureCompensationAOIFactor( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorOverexposureCompensationAOIFactorRaw( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorOverexposureCompensationAOIWidth( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorOverexposureCompensationAOIHeight( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorOverexposureCompensationAOIOffsetX( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ColorOverexposureCompensationAOIOffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ShadingSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ShadingSelectorEnums>() )
        , ShadingEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ShadingStatus( *new GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>() )
        , ShadingSetDefaultSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetDefaultSelectorEnums>() )
        , ShadingSetSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetSelectorEnums>() )
        , ShadingSetActivate( *new GENAPI_NAMESPACE::CCommandRef() )
        , ShadingSetCreate( *new GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetCreateEnums>() )
        , UserDefinedValueSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>() )
        , UserDefinedValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GenicamXmlFileDefault( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FeatureSet( *new GENAPI_NAMESPACE::CEnumerationTRef<FeatureSetEnums>() )
        , DeviceVendorName( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceModelName( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceManufacturerInfo( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceVersion( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceFirmwareVersion( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceID( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceUserID( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceScanType( *new GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>() )
        , DeviceReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , TemperatureSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>() )
        , TemperatureAbs( *new GENAPI_NAMESPACE::CFloatRef() )
        , TemperatureState( *new GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>() )
        , CriticalTemperature( *new GENAPI_NAMESPACE::CBooleanRef() )
        , OverTemperature( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LastError( *new GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>() )
        , ClearLastError( *new GENAPI_NAMESPACE::CCommandRef() )
        , DeviceColorPipelineVersion( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ParameterSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>() )
        , RemoveLimits( *new GENAPI_NAMESPACE::CBooleanRef() )
        , Prelines( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ExpertFeatureAccessSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>() )
        , ExpertFeatureAccessKey( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ExpertFeatureEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ChunkModeActive( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ChunkSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>() )
        , ChunkEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ChunkStride( *new GENAPI_NAMESPACE::CIntegerRef() )
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
        , EventSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>() )
        , EventNotification( *new GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>() )
        , ExposureEndEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ExposureEndEventFrameID( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ExposureEndEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LineStartOvertriggerEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LineStartOvertriggerEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameStartOvertriggerEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameStartOvertriggerEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameStartEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameStartEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionStartEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionStartEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionStartOvertriggerEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionStartOvertriggerEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameTimeoutEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameTimeoutEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventOverrunEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventOverrunEventFrameID( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventOverrunEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , CriticalTemperatureEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , CriticalTemperatureEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OverTemperatureEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OverTemperatureEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ActionLateEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ActionLateEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LateActionEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LateActionEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line1RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line1RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line2RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line2RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line3RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line3RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line4RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Line4RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine1RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine1RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine2RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine2RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine3RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine3RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine4RisingEdgeEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , VirtualLine4RisingEdgeEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameWaitEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameWaitEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionWaitEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionWaitEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameStartWaitEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameStartWaitEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionStartWaitEventStreamChannelIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AcquisitionStartWaitEventTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FileSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>() )
        , FileOperationSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>() )
        , FileOpenMode( *new GENAPI_NAMESPACE::CEnumerationTRef<FileOpenModeEnums>() )
        , FileAccessBuffer( *new GENAPI_NAMESPACE::CRegisterRef() )
        , FileAccessOffset( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FileAccessLength( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FileOperationStatus( *new GENAPI_NAMESPACE::CEnumerationTRef<FileOperationStatusEnums>() )
        , FileOperationResult( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FileSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FileOperationExecute( *new GENAPI_NAMESPACE::CCommandRef() )

    {
    }

    inline CGigECamera_Params::~CGigECamera_Params( void )
    {
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&SequenceEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequenceCurrentSet);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequenceConfigurationModeEnums>*> (&SequenceConfigurationMode);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SequenceAsyncRestart);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SequenceAsyncAdvance);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequenceSetTotalNumber);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequenceSetIndex);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SequenceSetStore);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SequenceSetLoad);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequenceSetExecutions);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequenceAdvanceModeEnums>*> (&SequenceAdvanceMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSelectorEnums>*> (&SequenceControlSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>*> (&SequenceAddressBitSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GainRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&GainAbs);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BlackLevelRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BlackLevelAbs);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GammaEnable);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GammaSelectorEnums>*> (&GammaSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&Gamma);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DigitalShift);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SubstrateVoltage);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>*> (&SensorDigitizationTaps);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ProcessedRawEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMin);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMax);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SpatialCorrection);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SpatialCorrectionAmount);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SpatialCorrectionStartingLineEnums>*> (&SpatialCorrectionStartingLine);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ReverseX);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ReverseY);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&TestImageResetAndHold);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SensorWidth);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SensorHeight);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&WidthMax);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&HeightMax);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&BalanceWhiteReset);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BalanceRatioAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BalanceRatioRaw);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorTransformationValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorTransformationValueRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorTransformationMatrixFactor);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorTransformationMatrixFactorRaw);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ColorAdjustmentEnable);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&ColorAdjustmentReset);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentHue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorAdjustmentHueRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentSaturation);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorAdjustmentSaturationRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslHue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BslHueRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslSaturation);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BslSaturationRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslBrightness);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BslBrightnessRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslContrast);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BslContrastRaw);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&NoiseReductionAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&NoiseReductionRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&SharpnessEnhancementAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SharpnessEnhancementRaw);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>*> (&TonalRangeEnable);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>*> (&TonalRangeAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeSourceBright);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeSourceDark);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeTargetBright);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeTargetDark);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Width);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Height);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&OffsetX);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&OffsetY);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&CenterX);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&CenterY);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LegacyBinningVerticalEnums>*> (&LegacyBinningVertical);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BinningModeHorizontalEnums>*> (&BinningModeHorizontal);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BinningHorizontal);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BinningModeVerticalEnums>*> (&BinningModeVertical);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BinningVertical);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DecimationHorizontal);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DecimationVertical);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ScalingHorizontalAbs);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ScalingVerticalAbs);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneSize);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneOffset);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&StackedZoneImagingEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&StackedZoneImagingIndex);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&StackedZoneImagingZoneEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&StackedZoneImagingZoneOffsetY);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&StackedZoneImagingZoneHeight);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&EnableBurstAcquisition);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStart);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStop);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionAbort);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionFrameCount);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerControlImplementationEnums>*> (&TriggerControlImplementation);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&TriggerSoftware);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&TriggerPartialClosingFrame);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerDelaySourceEnums>*> (&TriggerDelaySource);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TriggerDelayAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TriggerDelayLineTriggerCount);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ExposureStartDelayAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExposureStartDelayRaw);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<InterlacedIntegrationModeEnums>*> (&InterlacedIntegrationMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ExposureTimeAbs);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ExposureTimeBaseAbs);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ExposureTimeBaseAbsEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExposureTimeRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ReadoutTimeAbs);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ExposureOverlapTimeMaxAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExposureOverlapTimeMaxRaw);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GlobalResetReleaseModeEnable);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AcquisitionLineRateAbs);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ResultingLinePeriodAbs);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ResultingLineRateAbs);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionFrameRateEnable);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AcquisitionFrameRateAbs);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ResultingFramePeriodAbs);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ResultingFrameRateAbs);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionStatus);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&FrameTimeoutEnable);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&FrameTimeoutAbs);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&SyncFreeRunTimerEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SyncFreeRunTimerStartTimeLow);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SyncFreeRunTimerStartTimeHigh);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&SyncFreeRunTimerTriggerRateAbs);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SyncFreeRunTimerUpdate);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LineInverter);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LineTermination);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&LineDebouncerTimeAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LineDebouncerTimeRaw);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&MinOutPulseWidthRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&MinOutPulseWidthAbs);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LineStatus);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LineStatusAll);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&UserOutputValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&UserOutputValueAll);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&UserOutputValueAllMask);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&SyncUserOutputValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SyncUserOutputValueAll);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VInpBitLength);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VInpSamplingPoint);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalReadoutActivationEnums>*> (&VInpSignalReadoutActivation);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSelectorEnums>*> (&ShaftEncoderModuleLineSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleModeEnums>*> (&ShaftEncoderModuleMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleCounterModeEnums>*> (&ShaftEncoderModuleCounterMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ShaftEncoderModuleCounter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ShaftEncoderModuleCounterMax);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&ShaftEncoderModuleCounterReset);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ShaftEncoderModuleReverseCounterMax);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&ShaftEncoderModuleReverseCounterReset);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterSignalAlignmentEnums>*> (&FrequencyConverterSignalAlignment);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrequencyConverterPreDivider);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrequencyConverterMultiplier);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrequencyConverterPostDivider);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&FrequencyConverterPreventOvertrigger);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TimerDelayTimebaseAbs);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TimerDurationTimebaseAbs);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TimerDelayAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TimerDelayRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TimerDurationAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TimerDurationRaw);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>*> (&TimerTriggerActivation);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&CounterReset);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&TimerSequenceEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceLastEntryIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceCurrentEntryIndex);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>*> (&TimerSequenceTimerSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&TimerSequenceTimerEnable);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&TimerSequenceTimerInverter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceTimerDelayRaw);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceTimerDurationRaw);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LUTEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LUTIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LUTValue);
        delete static_cast <GENAPI_NAMESPACE::CRegisterRef*> (&LUTValueAll);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PayloadSize);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPSPacketSize);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPD);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCFTD);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCBWR);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCBWRA);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCBWA);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCDMT);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCDCT);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCFJM);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevVersionMajor);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevVersionMinor);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevDeviceModeIsBigEndian);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevDeviceModeCharacterSet);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GevInterfaceSelectorEnums>*> (&GevInterfaceSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevMACAddress);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GevGVSPExtendedIDModeEnums>*> (&GevGVSPExtendedIDMode);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIPConfigurationLLA);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIPConfigurationDHCP);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIPConfigurationPersistentIP);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentIPConfiguration);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentIPAddress);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentSubnetMask);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentDefaultGateway);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPersistentIPAddress);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPersistentSubnetMask);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPersistentDefaultGateway);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevLinkSpeed);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevLinkMaster);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevLinkFullDuplex);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevLinkCrossover);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&GevFirstURL);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&GevSecondURL);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevNumberOfInterfaces);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevMessageChannelCount);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevStreamChannelCount);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalLegacy16BitBlockID);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIEEE1588);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsEVENTDATA);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsEVENT);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsPACKETRESEND);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsWRITEMEM);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsConcatenation);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevHeartbeatTimeout);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevTimestampTickFrequency);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&GevTimestampControlLatch);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&GevTimestampControlReset);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&GevTimestampControlLatchReset);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevTimestampValue);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GevCCPEnums>*> (&GevCCP);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GevStreamChannelSelectorEnums>*> (&GevStreamChannelSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPInterfaceIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCDA);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPHostPort);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&GevSCPSFireTestPacket);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSCPSDoNotFragment);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevSCPSBigEndian);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TLParamsLocked);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&PixelFormatLegacy);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&GevIEEE1588);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&GevIEEE1588DataSetLatch);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588OffsetFromMaster);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ClockIdLow);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ClockIdHigh);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ClockId);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ParentClockIdLow);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ParentClockIdHigh);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ParentClockId);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxEvntMaxNumElements);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxGnrlMaxNumElements);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxEvntPushNumFailure);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxGnrlPushNumFailure);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueSendNumFailure);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&NumberOfActionSignals);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ActionCommandCount);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ActionDeviceKey);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ActionSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ActionGroupKey);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ActionGroupMask);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingStart);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingEnd);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&UserSetLoad);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&UserSetSave);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoTargetValue);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&GrayValueAdjustmentDampingAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GrayValueAdjustmentDampingRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BalanceWhiteAdjustmentDampingAbs);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BalanceWhiteAdjustmentDampingRaw);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoGainRawLowerLimit);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoGainRawUpperLimit);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeAbsLowerLimit);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeAbsUpperLimit);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIWidth);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIHeight);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetX);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetY);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageIntensity);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageWhiteBalance);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageRedLightCorrection);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageTonalRange);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdDark);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeThresholdDarkRaw);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdBright);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeThresholdBrightRaw);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetDark);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetBright);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorOverexposureCompensationAOISelectorEnums>*> (&ColorOverexposureCompensationAOISelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ColorOverexposureCompensationAOIEnable);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorOverexposureCompensationAOIFactor);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIFactorRaw);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIWidth);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIHeight);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIOffsetX);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIOffsetY);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShadingSelectorEnums>*> (&ShadingSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ShadingEnable);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>*> (&ShadingStatus);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetDefaultSelectorEnums>*> (&ShadingSetDefaultSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetSelectorEnums>*> (&ShadingSetSelector);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&ShadingSetActivate);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetCreateEnums>*> (&ShadingSetCreate);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&UserDefinedValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&GenicamXmlFileDefault);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FeatureSetEnums>*> (&FeatureSet);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceVendorName);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceModelName);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceManufacturerInfo);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceVersion);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceFirmwareVersion);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceID);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceUserID);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&DeviceReset);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>*> (&TemperatureSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TemperatureAbs);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&CriticalTemperature);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&OverTemperature);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&ClearLastError);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceColorPipelineVersion);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&RemoveLimits);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Prelines);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExpertFeatureAccessKey);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ExpertFeatureEnable);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ChunkModeActive);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ChunkEnable);
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
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExposureEndEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExposureEndEventFrameID);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExposureEndEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LineStartOvertriggerEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LineStartOvertriggerEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartOvertriggerEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartOvertriggerEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartOvertriggerEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartOvertriggerEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameTimeoutEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameTimeoutEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventOverrunEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventOverrunEventFrameID);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventOverrunEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&CriticalTemperatureEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&CriticalTemperatureEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&OverTemperatureEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&OverTemperatureEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ActionLateEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ActionLateEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LateActionEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LateActionEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line1RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line1RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line2RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line2RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line3RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line3RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line4RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Line4RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine1RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine1RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine2RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine2RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine3RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine3RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine4RisingEdgeEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine4RisingEdgeEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameWaitEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameWaitEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionWaitEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionWaitEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartWaitEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartWaitEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartWaitEventStreamChannelIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartWaitEventTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>*> (&FileOperationSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FileOpenModeEnums>*> (&FileOpenMode);
        delete static_cast <GENAPI_NAMESPACE::CRegisterRef*> (&FileAccessBuffer);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FileAccessOffset);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FileAccessLength);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<FileOperationStatusEnums>*> (&FileOperationStatus);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FileOperationResult);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&FileSize);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&FileOperationExecute);

    }

    inline void CGigECamera_Params::_Initialize( GENAPI_NAMESPACE::INodeMap* _Ptr )
    {
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&SequenceEnable)->SetReference( _Ptr->GetNode( "SequenceEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequenceCurrentSet)->SetReference( _Ptr->GetNode( "SequenceCurrentSet" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceConfigurationModeEnums>*> (&SequenceConfigurationMode)->SetReference( _Ptr->GetNode( "SequenceConfigurationMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceConfigurationModeEnums>*> (&SequenceConfigurationMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceConfigurationModeEnums>*> (&SequenceConfigurationMode)->SetEnumReference( SequenceConfigurationMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceConfigurationModeEnums>*> (&SequenceConfigurationMode)->SetEnumReference( SequenceConfigurationMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SequenceAsyncRestart)->SetReference( _Ptr->GetNode( "SequenceAsyncRestart" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SequenceAsyncAdvance)->SetReference( _Ptr->GetNode( "SequenceAsyncAdvance" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequenceSetTotalNumber)->SetReference( _Ptr->GetNode( "SequenceSetTotalNumber" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequenceSetIndex)->SetReference( _Ptr->GetNode( "SequenceSetIndex" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SequenceSetStore)->SetReference( _Ptr->GetNode( "SequenceSetStore" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SequenceSetLoad)->SetReference( _Ptr->GetNode( "SequenceSetLoad" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequenceSetExecutions)->SetReference( _Ptr->GetNode( "SequenceSetExecutions" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAdvanceModeEnums>*> (&SequenceAdvanceMode)->SetReference( _Ptr->GetNode( "SequenceAdvanceMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAdvanceModeEnums>*> (&SequenceAdvanceMode)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAdvanceModeEnums>*> (&SequenceAdvanceMode)->SetEnumReference( SequenceAdvanceMode_Auto, "Auto" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAdvanceModeEnums>*> (&SequenceAdvanceMode)->SetEnumReference( SequenceAdvanceMode_Controlled, "Controlled" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAdvanceModeEnums>*> (&SequenceAdvanceMode)->SetEnumReference( SequenceAdvanceMode_FreeSelection, "FreeSelection" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSelectorEnums>*> (&SequenceControlSelector)->SetReference( _Ptr->GetNode( "SequenceControlSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSelectorEnums>*> (&SequenceControlSelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSelectorEnums>*> (&SequenceControlSelector)->SetEnumReference( SequenceControlSelector_Restart, "Restart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSelectorEnums>*> (&SequenceControlSelector)->SetEnumReference( SequenceControlSelector_Advance, "Advance" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetReference( _Ptr->GetNode( "SequenceControlSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetNumEnums( 19 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Disabled, "Disabled" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_AlwaysActive, "AlwaysActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line5, "Line5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line6, "Line6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line7, "Line7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_Line8, "Line8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_CC1, "CC1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_CC2, "CC2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_CC3, "CC3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_CC4, "CC4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_VInput1, "VInput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_VInput2, "VInput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_VInput3, "VInput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_VInput4, "VInput4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceControlSourceEnums>*> (&SequenceControlSource)->SetEnumReference( SequenceControlSource_VInputDecActive, "VInputDecActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>*> (&SequenceAddressBitSelector)->SetReference( _Ptr->GetNode( "SequenceAddressBitSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>*> (&SequenceAddressBitSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>*> (&SequenceAddressBitSelector)->SetEnumReference( SequenceAddressBitSelector_Bit0, "Bit0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>*> (&SequenceAddressBitSelector)->SetEnumReference( SequenceAddressBitSelector_Bit1, "Bit1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>*> (&SequenceAddressBitSelector)->SetEnumReference( SequenceAddressBitSelector_Bit2, "Bit2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSelectorEnums>*> (&SequenceAddressBitSelector)->SetEnumReference( SequenceAddressBitSelector_Bit3, "Bit3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetReference( _Ptr->GetNode( "SequenceAddressBitSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetNumEnums( 17 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line5, "Line5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line6, "Line6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line7, "Line7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_Line8, "Line8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_CC1, "CC1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_CC2, "CC2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_CC3, "CC3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_CC4, "CC4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_VInput1, "VInput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_VInput2, "VInput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_VInput3, "VInput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_VInput4, "VInput4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequenceAddressBitSourceEnums>*> (&SequenceAddressBitSource)->SetEnumReference( SequenceAddressBitSource_VInputDecActive, "VInputDecActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetReference( _Ptr->GetNode( "GainAuto" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetEnumReference( GainAuto_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetEnumReference( GainAuto_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetEnumReference( GainAuto_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetReference( _Ptr->GetNode( "GainSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_All, "All" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_AnalogAll, "AnalogAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_DigitalAll, "DigitalAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_Tap1, "Tap1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_Tap2, "Tap2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_Tap3, "Tap3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_Tap4, "Tap4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_Red, "Red" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_Green, "Green" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_Blue, "Blue" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GainRaw)->SetReference( _Ptr->GetNode( "GainRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&GainAbs)->SetReference( _Ptr->GetNode( "GainAbs" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetReference( _Ptr->GetNode( "BlackLevelSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_All, "All" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_AnalogAll, "AnalogAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_DigitalAll, "DigitalAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_Tap1, "Tap1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_Tap2, "Tap2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_Tap3, "Tap3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_Tap4, "Tap4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_Red, "Red" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_Green, "Green" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_Blue, "Blue" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BlackLevelRaw)->SetReference( _Ptr->GetNode( "BlackLevelRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BlackLevelAbs)->SetReference( _Ptr->GetNode( "BlackLevelAbs" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GammaEnable)->SetReference( _Ptr->GetNode( "GammaEnable" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GammaSelectorEnums>*> (&GammaSelector)->SetReference( _Ptr->GetNode( "GammaSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GammaSelectorEnums>*> (&GammaSelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GammaSelectorEnums>*> (&GammaSelector)->SetEnumReference( GammaSelector_User, "User" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GammaSelectorEnums>*> (&GammaSelector)->SetEnumReference( GammaSelector_sRGB, "sRGB" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&Gamma)->SetReference( _Ptr->GetNode( "Gamma" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DigitalShift)->SetReference( _Ptr->GetNode( "DigitalShift" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SubstrateVoltage)->SetReference( _Ptr->GetNode( "SubstrateVoltage" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth)->SetReference( _Ptr->GetNode( "SensorBitDepth" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth)->SetEnumReference( SensorBitDepth_BitDepth8, "BitDepth8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth)->SetEnumReference( SensorBitDepth_BitDepth10, "BitDepth10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth)->SetEnumReference( SensorBitDepth_BitDepth12, "BitDepth12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth)->SetEnumReference( SensorBitDepth_BitDepth14, "BitDepth14" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorBitDepthEnums>*> (&SensorBitDepth)->SetEnumReference( SensorBitDepth_BitDepth16, "BitDepth16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>*> (&SensorDigitizationTaps)->SetReference( _Ptr->GetNode( "SensorDigitizationTaps" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>*> (&SensorDigitizationTaps)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>*> (&SensorDigitizationTaps)->SetEnumReference( SensorDigitizationTaps_One, "One" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>*> (&SensorDigitizationTaps)->SetEnumReference( SensorDigitizationTaps_Two, "Two" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>*> (&SensorDigitizationTaps)->SetEnumReference( SensorDigitizationTaps_Three, "Three" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorDigitizationTapsEnums>*> (&SensorDigitizationTaps)->SetEnumReference( SensorDigitizationTaps_Four, "Four" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetReference( _Ptr->GetNode( "PixelFormat" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetNumEnums( 51 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono8, "Mono8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono10, "Mono10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono10Packed, "Mono10Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono10p, "Mono10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono12, "Mono12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono12Packed, "Mono12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono16, "Mono16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR8, "BayerGR8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG8, "BayerRG8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB8, "BayerGB8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG8, "BayerBG8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR10, "BayerGR10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG10, "BayerRG10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB10, "BayerGB10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG10, "BayerBG10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR12, "BayerGR12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG12, "BayerRG12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB12, "BayerGB12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG12, "BayerBG12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB8Packed, "RGB8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BGR8Packed, "BGR8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGBA8Packed, "RGBA8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BGRA8Packed, "BGRA8Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB10Packed, "RGB10Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BGR10Packed, "BGR10Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB12Packed, "RGB12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BGR12Packed, "BGR12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB10V1Packed, "RGB10V1Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB10V2Packed, "RGB10V2Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_YUV411Packed, "YUV411Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_YUV422Packed, "YUV422Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_YUV444Packed, "YUV444Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB8Planar, "RGB8Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB10Planar, "RGB10Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB12Planar, "RGB12Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB16Planar, "RGB16Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_YUV422_YUYV_Packed, "YUV422_YUYV_Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB12Packed, "BayerGB12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR12Packed, "BayerGR12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG12Packed, "BayerRG12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG12Packed, "BayerBG12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR16, "BayerGR16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG16, "BayerRG16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB16, "BayerGB16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG16, "BayerBG16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB12V1Packed, "RGB12V1Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono8Signed, "Mono8Signed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR10p, "BayerGR10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG10p, "BayerRG10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB10p, "BayerGB10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG10p, "BayerBG10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetReference( _Ptr->GetNode( "PixelCoding" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetNumEnums( 24 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_Mono8, "Mono8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_Mono8Signed, "Mono8Signed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_Mono16, "Mono16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_Mono10Packed, "Mono10Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_Mono12Packed, "Mono12Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_Raw8, "Raw8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_Raw16, "Raw16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_RGB8, "RGB8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_BGR8, "BGR8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_RGBA8, "RGBA8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_BGRA8, "BGRA8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_RGB16, "RGB16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_BGR16, "BGR16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_RGB10V1Packed, "RGB10V1Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_RGB10V2Packed, "RGB10V2Packed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_YUV411, "YUV411" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_YUV422, "YUV422" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_YUV444, "YUV444" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_RGB8Planar, "RGB8Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_RGB16Planar, "RGB16Planar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_BayerGR10p, "BayerGR10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_BayerRG10p, "BayerRG10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_BayerGB10p, "BayerGB10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelCodingEnums>*> (&PixelCoding)->SetEnumReference( PixelCoding_BayerBG10p, "BayerBG10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetReference( _Ptr->GetNode( "PixelSize" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetNumEnums( 13 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp1, "Bpp1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp2, "Bpp2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp4, "Bpp4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp8, "Bpp8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp10, "Bpp10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp12, "Bpp12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp14, "Bpp14" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp16, "Bpp16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp24, "Bpp24" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp32, "Bpp32" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp36, "Bpp36" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp48, "Bpp48" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp64, "Bpp64" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetReference( _Ptr->GetNode( "PixelColorFilter" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_Bayer_RG, "Bayer_RG" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_Bayer_GB, "Bayer_GB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_Bayer_GR, "Bayer_GR" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_Bayer_BG, "Bayer_BG" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_None, "None" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ProcessedRawEnable)->SetReference( _Ptr->GetNode( "ProcessedRawEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMin)->SetReference( _Ptr->GetNode( "PixelDynamicRangeMin" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMax)->SetReference( _Ptr->GetNode( "PixelDynamicRangeMax" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SpatialCorrection)->SetReference( _Ptr->GetNode( "SpatialCorrection" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SpatialCorrectionAmount)->SetReference( _Ptr->GetNode( "SpatialCorrectionAmount" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SpatialCorrectionStartingLineEnums>*> (&SpatialCorrectionStartingLine)->SetReference( _Ptr->GetNode( "SpatialCorrectionStartingLine" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SpatialCorrectionStartingLineEnums>*> (&SpatialCorrectionStartingLine)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SpatialCorrectionStartingLineEnums>*> (&SpatialCorrectionStartingLine)->SetEnumReference( SpatialCorrectionStartingLine_LineRed, "LineRed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SpatialCorrectionStartingLineEnums>*> (&SpatialCorrectionStartingLine)->SetEnumReference( SpatialCorrectionStartingLine_LineGreen, "LineGreen" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SpatialCorrectionStartingLineEnums>*> (&SpatialCorrectionStartingLine)->SetEnumReference( SpatialCorrectionStartingLine_LineBlue, "LineBlue" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ReverseX)->SetReference( _Ptr->GetNode( "ReverseX" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ReverseY)->SetReference( _Ptr->GetNode( "ReverseY" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode)->SetReference( _Ptr->GetNode( "FieldOutputMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode)->SetEnumReference( FieldOutputMode_Field0, "Field0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode)->SetEnumReference( FieldOutputMode_Field1, "Field1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode)->SetEnumReference( FieldOutputMode_Field0First, "Field0First" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode)->SetEnumReference( FieldOutputMode_ConcatenatedNewFields, "ConcatenatedNewFields" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FieldOutputModeEnums>*> (&FieldOutputMode)->SetEnumReference( FieldOutputMode_DeinterlacedNewFields, "DeinterlacedNewFields" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetReference( _Ptr->GetNode( "TestImageSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetNumEnums( 25 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Black, "Black" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_White, "White" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_GreyHorizontalRamp, "GreyHorizontalRamp" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_GreyVerticalRamp, "GreyVerticalRamp" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_GreyHorizontalRampMoving, "GreyHorizontalRampMoving" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_GreyVerticalRampMoving, "GreyVerticalRampMoving" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_HorzontalLineMoving, "HorzontalLineMoving" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_VerticalLineMoving, "VerticalLineMoving" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_ColorBar, "ColorBar" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_FrameCounter, "FrameCounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_DeviceSpecific, "DeviceSpecific" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_FixedDiagonalGrayGradient_8Bit, "FixedDiagonalGrayGradient_8Bit" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_MovingDiagonalGrayGradient_8Bit, "MovingDiagonalGrayGradient_8Bit" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_MovingDiagonalGrayGradient_12Bit, "MovingDiagonalGrayGradient_12Bit" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_MovingDiagonalGrayGradientFeatureTest_8Bit, "MovingDiagonalGrayGradientFeatureTest_8Bit" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_MovingDiagonalGrayGradientFeatureTest_12Bit, "MovingDiagonalGrayGradientFeatureTest_12Bit" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_MovingDiagonalColorGradient, "MovingDiagonalColorGradient" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage1, "Testimage1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage2, "Testimage2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage3, "Testimage3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage4, "Testimage4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage5, "Testimage5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage6, "Testimage6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage7, "Testimage7" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&TestImageResetAndHold)->SetReference( _Ptr->GetNode( "TestImageResetAndHold" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SensorWidth)->SetReference( _Ptr->GetNode( "SensorWidth" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SensorHeight)->SetReference( _Ptr->GetNode( "SensorHeight" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&WidthMax)->SetReference( _Ptr->GetNode( "WidthMax" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&HeightMax)->SetReference( _Ptr->GetNode( "HeightMax" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetReference( _Ptr->GetNode( "LightSourceSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_Custom, "Custom" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_Daylight, "Daylight" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_Tungsten, "Tungsten" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_MicroscopeLED4500K, "MicroscopeLED4500K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_MicroscopeLED5500K, "MicroscopeLED5500K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_MicroscopeLED6000K, "MicroscopeLED6000K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_Daylight6500K, "Daylight6500K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_LightSource0, "LightSource0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourceSelectorEnums>*> (&LightSourceSelector)->SetEnumReference( LightSourceSelector_LightSource1, "LightSource1" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&BalanceWhiteReset)->SetReference( _Ptr->GetNode( "BalanceWhiteReset" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetReference( _Ptr->GetNode( "BalanceWhiteAuto" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetEnumReference( BalanceWhiteAuto_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetEnumReference( BalanceWhiteAuto_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetEnumReference( BalanceWhiteAuto_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetReference( _Ptr->GetNode( "BalanceRatioSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetEnumReference( BalanceRatioSelector_Red, "Red" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetEnumReference( BalanceRatioSelector_Green, "Green" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetEnumReference( BalanceRatioSelector_Blue, "Blue" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BalanceRatioAbs)->SetReference( _Ptr->GetNode( "BalanceRatioAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BalanceRatioRaw)->SetReference( _Ptr->GetNode( "BalanceRatioRaw" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetReference( _Ptr->GetNode( "ColorTransformationSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetEnumReference( ColorTransformationSelector_RGBtoRGB, "RGBtoRGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetEnumReference( ColorTransformationSelector_RGBtoYUV, "RGBtoYUV" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetEnumReference( ColorTransformationSelector_YUVtoRGB, "YUVtoRGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetReference( _Ptr->GetNode( "ColorTransformationValueSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetNumEnums( 9 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain00, "Gain00" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain01, "Gain01" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain02, "Gain02" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain10, "Gain10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain11, "Gain11" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain12, "Gain12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain20, "Gain20" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain21, "Gain21" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain22, "Gain22" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorTransformationValue)->SetReference( _Ptr->GetNode( "ColorTransformationValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorTransformationValueRaw)->SetReference( _Ptr->GetNode( "ColorTransformationValueRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorTransformationMatrixFactor)->SetReference( _Ptr->GetNode( "ColorTransformationMatrixFactor" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorTransformationMatrixFactorRaw)->SetReference( _Ptr->GetNode( "ColorTransformationMatrixFactorRaw" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ColorAdjustmentEnable)->SetReference( _Ptr->GetNode( "ColorAdjustmentEnable" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&ColorAdjustmentReset)->SetReference( _Ptr->GetNode( "ColorAdjustmentReset" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetReference( _Ptr->GetNode( "ColorAdjustmentSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetNumEnums( 6 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Red, "Red" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Yellow, "Yellow" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Green, "Green" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Cyan, "Cyan" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Blue, "Blue" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Magenta, "Magenta" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentHue)->SetReference( _Ptr->GetNode( "ColorAdjustmentHue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorAdjustmentHueRaw)->SetReference( _Ptr->GetNode( "ColorAdjustmentHueRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentSaturation)->SetReference( _Ptr->GetNode( "ColorAdjustmentSaturation" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorAdjustmentSaturationRaw)->SetReference( _Ptr->GetNode( "ColorAdjustmentSaturationRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslHue)->SetReference( _Ptr->GetNode( "BslHue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BslHueRaw)->SetReference( _Ptr->GetNode( "BslHueRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslSaturation)->SetReference( _Ptr->GetNode( "BslSaturation" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BslSaturationRaw)->SetReference( _Ptr->GetNode( "BslSaturationRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslBrightness)->SetReference( _Ptr->GetNode( "BslBrightness" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BslBrightnessRaw)->SetReference( _Ptr->GetNode( "BslBrightnessRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslContrast)->SetReference( _Ptr->GetNode( "BslContrast" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BslContrastRaw)->SetReference( _Ptr->GetNode( "BslContrastRaw" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetReference( _Ptr->GetNode( "BslContrastMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetEnumReference( BslContrastMode_Linear, "Linear" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetEnumReference( BslContrastMode_SCurve, "SCurve" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetReference( _Ptr->GetNode( "DemosaicingMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetEnumReference( DemosaicingMode_Simple, "Simple" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetEnumReference( DemosaicingMode_BaslerPGI, "BaslerPGI" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetReference( _Ptr->GetNode( "PgiMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetEnumReference( PgiMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetEnumReference( PgiMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&NoiseReductionAbs)->SetReference( _Ptr->GetNode( "NoiseReductionAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&NoiseReductionRaw)->SetReference( _Ptr->GetNode( "NoiseReductionRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&SharpnessEnhancementAbs)->SetReference( _Ptr->GetNode( "SharpnessEnhancementAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SharpnessEnhancementRaw)->SetReference( _Ptr->GetNode( "SharpnessEnhancementRaw" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>*> (&TonalRangeEnable)->SetReference( _Ptr->GetNode( "TonalRangeEnable" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>*> (&TonalRangeEnable)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>*> (&TonalRangeEnable)->SetEnumReference( TonalRangeEnable_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>*> (&TonalRangeEnable)->SetEnumReference( TonalRangeEnable_On, "On" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>*> (&TonalRangeAuto)->SetReference( _Ptr->GetNode( "TonalRangeAuto" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>*> (&TonalRangeAuto)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>*> (&TonalRangeAuto)->SetEnumReference( TonalRangeAuto_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>*> (&TonalRangeAuto)->SetEnumReference( TonalRangeAuto_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector)->SetReference( _Ptr->GetNode( "TonalRangeSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector)->SetEnumReference( TonalRangeSelector_Sum, "Sum" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector)->SetEnumReference( TonalRangeSelector_Red, "Red" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector)->SetEnumReference( TonalRangeSelector_Green, "Green" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector)->SetEnumReference( TonalRangeSelector_Blue, "Blue" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeSourceBright)->SetReference( _Ptr->GetNode( "TonalRangeSourceBright" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeSourceDark)->SetReference( _Ptr->GetNode( "TonalRangeSourceDark" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeTargetBright)->SetReference( _Ptr->GetNode( "TonalRangeTargetBright" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeTargetDark)->SetReference( _Ptr->GetNode( "TonalRangeTargetDark" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Width)->SetReference( _Ptr->GetNode( "Width" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Height)->SetReference( _Ptr->GetNode( "Height" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OffsetX)->SetReference( _Ptr->GetNode( "OffsetX" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OffsetY)->SetReference( _Ptr->GetNode( "OffsetY" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&CenterX)->SetReference( _Ptr->GetNode( "CenterX" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&CenterY)->SetReference( _Ptr->GetNode( "CenterY" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LegacyBinningVerticalEnums>*> (&LegacyBinningVertical)->SetReference( _Ptr->GetNode( "LegacyBinningVertical" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LegacyBinningVerticalEnums>*> (&LegacyBinningVertical)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LegacyBinningVerticalEnums>*> (&LegacyBinningVertical)->SetEnumReference( LegacyBinningVertical_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LegacyBinningVerticalEnums>*> (&LegacyBinningVertical)->SetEnumReference( LegacyBinningVertical_Two_Rows, "Two_Rows" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetReference( _Ptr->GetNode( "BinningHorizontalMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetEnumReference( BinningHorizontalMode_Sum, "Sum" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetEnumReference( BinningHorizontalMode_Average, "Average" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeHorizontalEnums>*> (&BinningModeHorizontal)->SetReference( _Ptr->GetNode( "BinningModeHorizontal" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeHorizontalEnums>*> (&BinningModeHorizontal)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeHorizontalEnums>*> (&BinningModeHorizontal)->SetEnumReference( BinningModeHorizontal_Summing, "Summing" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeHorizontalEnums>*> (&BinningModeHorizontal)->SetEnumReference( BinningModeHorizontal_Averaging, "Averaging" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BinningHorizontal)->SetReference( _Ptr->GetNode( "BinningHorizontal" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetReference( _Ptr->GetNode( "BinningVerticalMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetEnumReference( BinningVerticalMode_Sum, "Sum" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetEnumReference( BinningVerticalMode_Average, "Average" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeVerticalEnums>*> (&BinningModeVertical)->SetReference( _Ptr->GetNode( "BinningModeVertical" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeVerticalEnums>*> (&BinningModeVertical)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeVerticalEnums>*> (&BinningModeVertical)->SetEnumReference( BinningModeVertical_Summing, "Summing" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningModeVerticalEnums>*> (&BinningModeVertical)->SetEnumReference( BinningModeVertical_Averaging, "Averaging" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BinningVertical)->SetReference( _Ptr->GetNode( "BinningVertical" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DecimationHorizontal)->SetReference( _Ptr->GetNode( "DecimationHorizontal" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DecimationVertical)->SetReference( _Ptr->GetNode( "DecimationVertical" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ScalingHorizontalAbs)->SetReference( _Ptr->GetNode( "ScalingHorizontalAbs" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ScalingVerticalAbs)->SetReference( _Ptr->GetNode( "ScalingVerticalAbs" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetReference( _Ptr->GetNode( "ROIZoneSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone0, "Zone0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone1, "Zone1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone2, "Zone2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone3, "Zone3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone4, "Zone4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone5, "Zone5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone6, "Zone6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone7, "Zone7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetReference( _Ptr->GetNode( "ROIZoneMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetEnumReference( ROIZoneMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetEnumReference( ROIZoneMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneSize)->SetReference( _Ptr->GetNode( "ROIZoneSize" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneOffset)->SetReference( _Ptr->GetNode( "ROIZoneOffset" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&StackedZoneImagingEnable)->SetReference( _Ptr->GetNode( "StackedZoneImagingEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&StackedZoneImagingIndex)->SetReference( _Ptr->GetNode( "StackedZoneImagingIndex" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&StackedZoneImagingZoneEnable)->SetReference( _Ptr->GetNode( "StackedZoneImagingZoneEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&StackedZoneImagingZoneOffsetY)->SetReference( _Ptr->GetNode( "StackedZoneImagingZoneOffsetY" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&StackedZoneImagingZoneHeight)->SetReference( _Ptr->GetNode( "StackedZoneImagingZoneHeight" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&EnableBurstAcquisition)->SetReference( _Ptr->GetNode( "EnableBurstAcquisition" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetReference( _Ptr->GetNode( "AcquisitionMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetEnumReference( AcquisitionMode_SingleFrame, "SingleFrame" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetEnumReference( AcquisitionMode_MultiFrame, "MultiFrame" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetEnumReference( AcquisitionMode_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStart)->SetReference( _Ptr->GetNode( "AcquisitionStart" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStop)->SetReference( _Ptr->GetNode( "AcquisitionStop" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionAbort)->SetReference( _Ptr->GetNode( "AcquisitionAbort" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionFrameCount)->SetReference( _Ptr->GetNode( "AcquisitionFrameCount" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerControlImplementationEnums>*> (&TriggerControlImplementation)->SetReference( _Ptr->GetNode( "TriggerControlImplementation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerControlImplementationEnums>*> (&TriggerControlImplementation)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerControlImplementationEnums>*> (&TriggerControlImplementation)->SetEnumReference( TriggerControlImplementation_Legacy, "Legacy" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerControlImplementationEnums>*> (&TriggerControlImplementation)->SetEnumReference( TriggerControlImplementation_Standard, "Standard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetReference( _Ptr->GetNode( "TriggerSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_AcquisitionStart, "AcquisitionStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_AcquisitionEnd, "AcquisitionEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_AcquisitionActive, "AcquisitionActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_FrameStart, "FrameStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_FrameEnd, "FrameEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_FrameActive, "FrameActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_LineStart, "LineStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_ExposureStart, "ExposureStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_ExposureEnd, "ExposureEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_ExposureActive, "ExposureActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetReference( _Ptr->GetNode( "TriggerMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetEnumReference( TriggerMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetEnumReference( TriggerMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&TriggerSoftware)->SetReference( _Ptr->GetNode( "TriggerSoftware" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetReference( _Ptr->GetNode( "TriggerSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetNumEnums( 30 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Software, "Software" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line5, "Line5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line6, "Line6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line7, "Line7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line8, "Line8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_CC1, "CC1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_CC2, "CC2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_CC3, "CC3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_CC4, "CC4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_ShaftEncoderModuleOut, "ShaftEncoderModuleOut" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_FrequencyConverter, "FrequencyConverter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Timer1Start, "Timer1Start" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Timer1End, "Timer1End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Counter1Start, "Counter1Start" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Counter1End, "Counter1End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_UserOutput1, "UserOutput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_UserOutput2, "UserOutput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Action1, "Action1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Action2, "Action2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Action3, "Action3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Action4, "Action4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_VInput1, "VInput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_VInput2, "VInput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_VInput3, "VInput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_VInput4, "VInput4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_VInputDecActive, "VInputDecActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetReference( _Ptr->GetNode( "TriggerActivation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_RisingEdge, "RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_FallingEdge, "FallingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_AnyEdge, "AnyEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_LevelHigh, "LevelHigh" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_LevelLow, "LevelLow" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&TriggerPartialClosingFrame)->SetReference( _Ptr->GetNode( "TriggerPartialClosingFrame" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerDelaySourceEnums>*> (&TriggerDelaySource)->SetReference( _Ptr->GetNode( "TriggerDelaySource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerDelaySourceEnums>*> (&TriggerDelaySource)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerDelaySourceEnums>*> (&TriggerDelaySource)->SetEnumReference( TriggerDelaySource_Time_us, "Time_us" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerDelaySourceEnums>*> (&TriggerDelaySource)->SetEnumReference( TriggerDelaySource_LineTrigger, "LineTrigger" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TriggerDelayAbs)->SetReference( _Ptr->GetNode( "TriggerDelayAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TriggerDelayLineTriggerCount)->SetReference( _Ptr->GetNode( "TriggerDelayLineTriggerCount" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ExposureStartDelayAbs)->SetReference( _Ptr->GetNode( "ExposureStartDelayAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExposureStartDelayRaw)->SetReference( _Ptr->GetNode( "ExposureStartDelayRaw" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetReference( _Ptr->GetNode( "ExposureMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetEnumReference( ExposureMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetEnumReference( ExposureMode_Timed, "Timed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetEnumReference( ExposureMode_TriggerWidth, "TriggerWidth" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetEnumReference( ExposureMode_TriggerControlled, "TriggerControlled" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InterlacedIntegrationModeEnums>*> (&InterlacedIntegrationMode)->SetReference( _Ptr->GetNode( "InterlacedIntegrationMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InterlacedIntegrationModeEnums>*> (&InterlacedIntegrationMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InterlacedIntegrationModeEnums>*> (&InterlacedIntegrationMode)->SetEnumReference( InterlacedIntegrationMode_FieldIntegration, "FieldIntegration" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InterlacedIntegrationModeEnums>*> (&InterlacedIntegrationMode)->SetEnumReference( InterlacedIntegrationMode_FrameIntegration, "FrameIntegration" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetReference( _Ptr->GetNode( "ExposureAuto" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetEnumReference( ExposureAuto_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetEnumReference( ExposureAuto_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetEnumReference( ExposureAuto_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetReference( _Ptr->GetNode( "ExposureTimeMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetEnumReference( ExposureTimeMode_Standard, "Standard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetEnumReference( ExposureTimeMode_UltraShort, "UltraShort" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ExposureTimeAbs)->SetReference( _Ptr->GetNode( "ExposureTimeAbs" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ExposureTimeBaseAbs)->SetReference( _Ptr->GetNode( "ExposureTimeBaseAbs" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ExposureTimeBaseAbsEnable)->SetReference( _Ptr->GetNode( "ExposureTimeBaseAbsEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExposureTimeRaw)->SetReference( _Ptr->GetNode( "ExposureTimeRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ReadoutTimeAbs)->SetReference( _Ptr->GetNode( "ReadoutTimeAbs" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetReference( _Ptr->GetNode( "ExposureOverlapTimeMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetEnumReference( ExposureOverlapTimeMode_Manual, "Manual" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetEnumReference( ExposureOverlapTimeMode_Automatic, "Automatic" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ExposureOverlapTimeMaxAbs)->SetReference( _Ptr->GetNode( "ExposureOverlapTimeMaxAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExposureOverlapTimeMaxRaw)->SetReference( _Ptr->GetNode( "ExposureOverlapTimeMaxRaw" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GlobalResetReleaseModeEnable)->SetReference( _Ptr->GetNode( "GlobalResetReleaseModeEnable" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetReference( _Ptr->GetNode( "ShutterMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetEnumReference( ShutterMode_Global, "Global" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetEnumReference( ShutterMode_Rolling, "Rolling" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetEnumReference( ShutterMode_GlobalResetRelease, "GlobalResetRelease" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetReference( _Ptr->GetNode( "SensorReadoutMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetEnumReference( SensorReadoutMode_Normal, "Normal" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetEnumReference( SensorReadoutMode_Fast, "Fast" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AcquisitionLineRateAbs)->SetReference( _Ptr->GetNode( "AcquisitionLineRateAbs" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ResultingLinePeriodAbs)->SetReference( _Ptr->GetNode( "ResultingLinePeriodAbs" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ResultingLineRateAbs)->SetReference( _Ptr->GetNode( "ResultingLineRateAbs" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionFrameRateEnable)->SetReference( _Ptr->GetNode( "AcquisitionFrameRateEnable" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AcquisitionFrameRateAbs)->SetReference( _Ptr->GetNode( "AcquisitionFrameRateAbs" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ResultingFramePeriodAbs)->SetReference( _Ptr->GetNode( "ResultingFramePeriodAbs" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ResultingFrameRateAbs)->SetReference( _Ptr->GetNode( "ResultingFrameRateAbs" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetReference( _Ptr->GetNode( "AcquisitionStatusSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetNumEnums( 9 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_AcquisitionTriggerWait, "AcquisitionTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_AcquisitionActive, "AcquisitionActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_AcquisitionTransfer, "AcquisitionTransfer" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameTriggerWait, "FrameTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameActive, "FrameActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameTransfer, "FrameTransfer" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_ExposureActive, "ExposureActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_LineTriggerWait, "LineTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_AcquisitionIdle, "AcquisitionIdle" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionStatus)->SetReference( _Ptr->GetNode( "AcquisitionStatus" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&FrameTimeoutEnable)->SetReference( _Ptr->GetNode( "FrameTimeoutEnable" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&FrameTimeoutAbs)->SetReference( _Ptr->GetNode( "FrameTimeoutAbs" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&SyncFreeRunTimerEnable)->SetReference( _Ptr->GetNode( "SyncFreeRunTimerEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SyncFreeRunTimerStartTimeLow)->SetReference( _Ptr->GetNode( "SyncFreeRunTimerStartTimeLow" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SyncFreeRunTimerStartTimeHigh)->SetReference( _Ptr->GetNode( "SyncFreeRunTimerStartTimeHigh" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&SyncFreeRunTimerTriggerRateAbs)->SetReference( _Ptr->GetNode( "SyncFreeRunTimerTriggerRateAbs" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SyncFreeRunTimerUpdate)->SetReference( _Ptr->GetNode( "SyncFreeRunTimerUpdate" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetReference( _Ptr->GetNode( "LineSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Out1, "Out1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Out2, "Out2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Out3, "Out3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Out4, "Out4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetReference( _Ptr->GetNode( "LineMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetEnumReference( LineMode_Input, "Input" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetEnumReference( LineMode_Output, "Output" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetReference( _Ptr->GetNode( "LineLogic" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetEnumReference( LineLogic_Positive, "Positive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetEnumReference( LineLogic_Negative, "Negative" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetReference( _Ptr->GetNode( "LineFormat" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetNumEnums( 6 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_NoConnect, "NoConnect" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_TriState, "TriState" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_TTL, "TTL" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_LVDS, "LVDS" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_RS422, "RS422" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_OptoCoupled, "OptoCoupled" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetReference( _Ptr->GetNode( "LineSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetNumEnums( 32 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_ExposureActive, "ExposureActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_FrameTriggerWait, "FrameTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_LineTriggerWait, "LineTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_Timer1Active, "Timer1Active" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_Timer2Active, "Timer2Active" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_Timer3Active, "Timer3Active" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_Timer4Active, "Timer4Active" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_TimerActive, "TimerActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput1, "UserOutput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput2, "UserOutput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput3, "UserOutput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput4, "UserOutput4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput, "UserOutput" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_TriggerReady, "TriggerReady" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_SerialTx, "SerialTx" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_AcquisitionTriggerWait, "AcquisitionTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_ShaftEncoderModuleOut, "ShaftEncoderModuleOut" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_FrequencyConverter, "FrequencyConverter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_PatternGenerator1, "PatternGenerator1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_PatternGenerator2, "PatternGenerator2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_PatternGenerator3, "PatternGenerator3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_PatternGenerator4, "PatternGenerator4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_AcquisitionTriggerReady, "AcquisitionTriggerReady" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_FlashWindow, "FlashWindow" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_FrameCycle, "FrameCycle" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_SyncUserOutput, "SyncUserOutput" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput0, "UserOutput0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_SyncUserOutput0, "SyncUserOutput0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_SyncUserOutput1, "SyncUserOutput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_SyncUserOutput2, "SyncUserOutput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_SyncUserOutput3, "SyncUserOutput3" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LineInverter)->SetReference( _Ptr->GetNode( "LineInverter" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LineTermination)->SetReference( _Ptr->GetNode( "LineTermination" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&LineDebouncerTimeAbs)->SetReference( _Ptr->GetNode( "LineDebouncerTimeAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LineDebouncerTimeRaw)->SetReference( _Ptr->GetNode( "LineDebouncerTimeRaw" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&MinOutPulseWidthRaw)->SetReference( _Ptr->GetNode( "MinOutPulseWidthRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&MinOutPulseWidthAbs)->SetReference( _Ptr->GetNode( "MinOutPulseWidthAbs" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LineStatus)->SetReference( _Ptr->GetNode( "LineStatus" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LineStatusAll)->SetReference( _Ptr->GetNode( "LineStatusAll" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetReference( _Ptr->GetNode( "UserOutputSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput1, "UserOutput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput2, "UserOutput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput3, "UserOutput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput4, "UserOutput4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput5, "UserOutput5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput6, "UserOutput6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput7, "UserOutput7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput8, "UserOutput8" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&UserOutputValue)->SetReference( _Ptr->GetNode( "UserOutputValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&UserOutputValueAll)->SetReference( _Ptr->GetNode( "UserOutputValueAll" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&UserOutputValueAllMask)->SetReference( _Ptr->GetNode( "UserOutputValueAllMask" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetReference( _Ptr->GetNode( "SyncUserOutputSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput1, "SyncUserOutput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput2, "SyncUserOutput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput3, "SyncUserOutput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput4, "SyncUserOutput4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput5, "SyncUserOutput5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput6, "SyncUserOutput6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput7, "SyncUserOutput7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SyncUserOutputSelectorEnums>*> (&SyncUserOutputSelector)->SetEnumReference( SyncUserOutputSelector_SyncUserOutput8, "SyncUserOutput8" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&SyncUserOutputValue)->SetReference( _Ptr->GetNode( "SyncUserOutputValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SyncUserOutputValueAll)->SetReference( _Ptr->GetNode( "SyncUserOutputValueAll" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetReference( _Ptr->GetNode( "VInpSignalSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetNumEnums( 12 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line5, "Line5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line6, "Line6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line7, "Line7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_Line8, "Line8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_CC1, "CC1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_CC2, "CC2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_CC3, "CC3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalSourceEnums>*> (&VInpSignalSource)->SetEnumReference( VInpSignalSource_CC4, "CC4" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VInpBitLength)->SetReference( _Ptr->GetNode( "VInpBitLength" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VInpSamplingPoint)->SetReference( _Ptr->GetNode( "VInpSamplingPoint" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalReadoutActivationEnums>*> (&VInpSignalReadoutActivation)->SetReference( _Ptr->GetNode( "VInpSignalReadoutActivation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalReadoutActivationEnums>*> (&VInpSignalReadoutActivation)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalReadoutActivationEnums>*> (&VInpSignalReadoutActivation)->SetEnumReference( VInpSignalReadoutActivation_RisingEdge, "RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<VInpSignalReadoutActivationEnums>*> (&VInpSignalReadoutActivation)->SetEnumReference( VInpSignalReadoutActivation_FallingEdge, "FallingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSelectorEnums>*> (&ShaftEncoderModuleLineSelector)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleLineSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSelectorEnums>*> (&ShaftEncoderModuleLineSelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSelectorEnums>*> (&ShaftEncoderModuleLineSelector)->SetEnumReference( ShaftEncoderModuleLineSelector_PhaseA, "PhaseA" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSelectorEnums>*> (&ShaftEncoderModuleLineSelector)->SetEnumReference( ShaftEncoderModuleLineSelector_PhaseB, "PhaseB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleLineSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetNumEnums( 12 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line5, "Line5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line6, "Line6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line7, "Line7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_Line8, "Line8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_CC1, "CC1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_CC2, "CC2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_CC3, "CC3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleLineSourceEnums>*> (&ShaftEncoderModuleLineSource)->SetEnumReference( ShaftEncoderModuleLineSource_CC4, "CC4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleModeEnums>*> (&ShaftEncoderModuleMode)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleModeEnums>*> (&ShaftEncoderModuleMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleModeEnums>*> (&ShaftEncoderModuleMode)->SetEnumReference( ShaftEncoderModuleMode_AnyDirection, "AnyDirection" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleModeEnums>*> (&ShaftEncoderModuleMode)->SetEnumReference( ShaftEncoderModuleMode_ForwardOnly, "ForwardOnly" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleCounterModeEnums>*> (&ShaftEncoderModuleCounterMode)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleCounterMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleCounterModeEnums>*> (&ShaftEncoderModuleCounterMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleCounterModeEnums>*> (&ShaftEncoderModuleCounterMode)->SetEnumReference( ShaftEncoderModuleCounterMode_FollowDirection, "FollowDirection" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShaftEncoderModuleCounterModeEnums>*> (&ShaftEncoderModuleCounterMode)->SetEnumReference( ShaftEncoderModuleCounterMode_IgnoreDirection, "IgnoreDirection" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ShaftEncoderModuleCounter)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleCounter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ShaftEncoderModuleCounterMax)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleCounterMax" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&ShaftEncoderModuleCounterReset)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleCounterReset" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ShaftEncoderModuleReverseCounterMax)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleReverseCounterMax" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&ShaftEncoderModuleReverseCounterReset)->SetReference( _Ptr->GetNode( "ShaftEncoderModuleReverseCounterReset" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetReference( _Ptr->GetNode( "FrequencyConverterInputSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetNumEnums( 13 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line5, "Line5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line6, "Line6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line7, "Line7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_Line8, "Line8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_CC1, "CC1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_CC2, "CC2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_CC3, "CC3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_CC4, "CC4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterInputSourceEnums>*> (&FrequencyConverterInputSource)->SetEnumReference( FrequencyConverterInputSource_ShaftEncoderModuleOut, "ShaftEncoderModuleOut" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterSignalAlignmentEnums>*> (&FrequencyConverterSignalAlignment)->SetReference( _Ptr->GetNode( "FrequencyConverterSignalAlignment" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterSignalAlignmentEnums>*> (&FrequencyConverterSignalAlignment)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterSignalAlignmentEnums>*> (&FrequencyConverterSignalAlignment)->SetEnumReference( FrequencyConverterSignalAlignment_RisingEdge, "RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FrequencyConverterSignalAlignmentEnums>*> (&FrequencyConverterSignalAlignment)->SetEnumReference( FrequencyConverterSignalAlignment_FallingEdge, "FallingEdge" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrequencyConverterPreDivider)->SetReference( _Ptr->GetNode( "FrequencyConverterPreDivider" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrequencyConverterMultiplier)->SetReference( _Ptr->GetNode( "FrequencyConverterMultiplier" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrequencyConverterPostDivider)->SetReference( _Ptr->GetNode( "FrequencyConverterPostDivider" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&FrequencyConverterPreventOvertrigger)->SetReference( _Ptr->GetNode( "FrequencyConverterPreventOvertrigger" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TimerDelayTimebaseAbs)->SetReference( _Ptr->GetNode( "TimerDelayTimebaseAbs" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TimerDurationTimebaseAbs)->SetReference( _Ptr->GetNode( "TimerDurationTimebaseAbs" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetReference( _Ptr->GetNode( "TimerSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetEnumReference( TimerSelector_Timer1, "Timer1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetEnumReference( TimerSelector_Timer2, "Timer2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetEnumReference( TimerSelector_Timer3, "Timer3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetEnumReference( TimerSelector_Timer4, "Timer4" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TimerDelayAbs)->SetReference( _Ptr->GetNode( "TimerDelayAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TimerDelayRaw)->SetReference( _Ptr->GetNode( "TimerDelayRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TimerDurationAbs)->SetReference( _Ptr->GetNode( "TimerDurationAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TimerDurationRaw)->SetReference( _Ptr->GetNode( "TimerDurationRaw" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetReference( _Ptr->GetNode( "TimerTriggerSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetEnumReference( TimerTriggerSource_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetEnumReference( TimerTriggerSource_ExposureStart, "ExposureStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetEnumReference( TimerTriggerSource_FlashWindowStart, "FlashWindowStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>*> (&TimerTriggerActivation)->SetReference( _Ptr->GetNode( "TimerTriggerActivation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>*> (&TimerTriggerActivation)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>*> (&TimerTriggerActivation)->SetEnumReference( TimerTriggerActivation_RisingEdge, "RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>*> (&TimerTriggerActivation)->SetEnumReference( TimerTriggerActivation_FallingEdge, "FallingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>*> (&TimerTriggerActivation)->SetEnumReference( TimerTriggerActivation_LevelHigh, "LevelHigh" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerActivationEnums>*> (&TimerTriggerActivation)->SetEnumReference( TimerTriggerActivation_LevelLow, "LevelLow" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetReference( _Ptr->GetNode( "CounterSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetEnumReference( CounterSelector_Counter1, "Counter1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetEnumReference( CounterSelector_Counter2, "Counter2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetEnumReference( CounterSelector_Counter3, "Counter3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetEnumReference( CounterSelector_Counter4, "Counter4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetReference( _Ptr->GetNode( "CounterEventSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetNumEnums( 12 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_AcquisitionTrigger, "AcquisitionTrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_AcquisitionStart, "AcquisitionStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_AcquisitionEnd, "AcquisitionEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_FrameTrigger, "FrameTrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_FrameStart, "FrameStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_FrameEnd, "FrameEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_LineTrigger, "LineTrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_LineStart, "LineStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_LineEnd, "LineEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_ExposureStart, "ExposureStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_ExposureEnd, "ExposureEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetReference( _Ptr->GetNode( "CounterResetSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetNumEnums( 19 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Software, "Software" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line5, "Line5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line6, "Line6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line7, "Line7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line8, "Line8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_CC1, "CC1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_CC2, "CC2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_CC3, "CC3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_CC4, "CC4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_VInput1, "VInput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_VInput2, "VInput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_VInput3, "VInput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_VInput4, "VInput4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_VInputDecActive, "VInputDecActive" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&CounterReset)->SetReference( _Ptr->GetNode( "CounterReset" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&TimerSequenceEnable)->SetReference( _Ptr->GetNode( "TimerSequenceEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceLastEntryIndex)->SetReference( _Ptr->GetNode( "TimerSequenceLastEntryIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceCurrentEntryIndex)->SetReference( _Ptr->GetNode( "TimerSequenceCurrentEntryIndex" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetReference( _Ptr->GetNode( "TimerSequenceEntrySelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetNumEnums( 16 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry1, "Entry1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry2, "Entry2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry3, "Entry3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry4, "Entry4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry5, "Entry5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry6, "Entry6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry7, "Entry7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry8, "Entry8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry9, "Entry9" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry10, "Entry10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry11, "Entry11" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry12, "Entry12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry13, "Entry13" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry14, "Entry14" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry15, "Entry15" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceEntrySelectorEnums>*> (&TimerSequenceEntrySelector)->SetEnumReference( TimerSequenceEntrySelector_Entry16, "Entry16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>*> (&TimerSequenceTimerSelector)->SetReference( _Ptr->GetNode( "TimerSequenceTimerSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>*> (&TimerSequenceTimerSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>*> (&TimerSequenceTimerSelector)->SetEnumReference( TimerSequenceTimerSelector_Timer1, "Timer1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>*> (&TimerSequenceTimerSelector)->SetEnumReference( TimerSequenceTimerSelector_Timer2, "Timer2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>*> (&TimerSequenceTimerSelector)->SetEnumReference( TimerSequenceTimerSelector_Timer3, "Timer3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSequenceTimerSelectorEnums>*> (&TimerSequenceTimerSelector)->SetEnumReference( TimerSequenceTimerSelector_Timer4, "Timer4" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&TimerSequenceTimerEnable)->SetReference( _Ptr->GetNode( "TimerSequenceTimerEnable" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&TimerSequenceTimerInverter)->SetReference( _Ptr->GetNode( "TimerSequenceTimerInverter" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceTimerDelayRaw)->SetReference( _Ptr->GetNode( "TimerSequenceTimerDelayRaw" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TimerSequenceTimerDurationRaw)->SetReference( _Ptr->GetNode( "TimerSequenceTimerDurationRaw" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector)->SetReference( _Ptr->GetNode( "LUTSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector)->SetEnumReference( LUTSelector_Luminance, "Luminance" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LUTEnable)->SetReference( _Ptr->GetNode( "LUTEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LUTIndex)->SetReference( _Ptr->GetNode( "LUTIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LUTValue)->SetReference( _Ptr->GetNode( "LUTValue" ) );
        static_cast<GENAPI_NAMESPACE::CRegisterRef*> (&LUTValueAll)->SetReference( _Ptr->GetNode( "LUTValueAll" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PayloadSize)->SetReference( _Ptr->GetNode( "PayloadSize" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPSPacketSize)->SetReference( _Ptr->GetNode( "GevSCPSPacketSize" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPD)->SetReference( _Ptr->GetNode( "GevSCPD" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCFTD)->SetReference( _Ptr->GetNode( "GevSCFTD" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCBWR)->SetReference( _Ptr->GetNode( "GevSCBWR" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCBWRA)->SetReference( _Ptr->GetNode( "GevSCBWRA" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCBWA)->SetReference( _Ptr->GetNode( "GevSCBWA" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCDMT)->SetReference( _Ptr->GetNode( "GevSCDMT" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCDCT)->SetReference( _Ptr->GetNode( "GevSCDCT" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCFJM)->SetReference( _Ptr->GetNode( "GevSCFJM" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevVersionMajor)->SetReference( _Ptr->GetNode( "GevVersionMajor" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevVersionMinor)->SetReference( _Ptr->GetNode( "GevVersionMinor" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevDeviceModeIsBigEndian)->SetReference( _Ptr->GetNode( "GevDeviceModeIsBigEndian" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevDeviceModeCharacterSet)->SetReference( _Ptr->GetNode( "GevDeviceModeCharacterSet" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevInterfaceSelectorEnums>*> (&GevInterfaceSelector)->SetReference( _Ptr->GetNode( "GevInterfaceSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevInterfaceSelectorEnums>*> (&GevInterfaceSelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevInterfaceSelectorEnums>*> (&GevInterfaceSelector)->SetEnumReference( GevInterfaceSelector_NetworkInterface0, "NetworkInterface0" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevMACAddress)->SetReference( _Ptr->GetNode( "GevMACAddress" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevGVSPExtendedIDModeEnums>*> (&GevGVSPExtendedIDMode)->SetReference( _Ptr->GetNode( "GevGVSPExtendedIDMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevGVSPExtendedIDModeEnums>*> (&GevGVSPExtendedIDMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevGVSPExtendedIDModeEnums>*> (&GevGVSPExtendedIDMode)->SetEnumReference( GevGVSPExtendedIDMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevGVSPExtendedIDModeEnums>*> (&GevGVSPExtendedIDMode)->SetEnumReference( GevGVSPExtendedIDMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIPConfigurationLLA)->SetReference( _Ptr->GetNode( "GevSupportedIPConfigurationLLA" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIPConfigurationDHCP)->SetReference( _Ptr->GetNode( "GevSupportedIPConfigurationDHCP" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIPConfigurationPersistentIP)->SetReference( _Ptr->GetNode( "GevSupportedIPConfigurationPersistentIP" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentIPConfiguration)->SetReference( _Ptr->GetNode( "GevCurrentIPConfiguration" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentIPAddress)->SetReference( _Ptr->GetNode( "GevCurrentIPAddress" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentSubnetMask)->SetReference( _Ptr->GetNode( "GevCurrentSubnetMask" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevCurrentDefaultGateway)->SetReference( _Ptr->GetNode( "GevCurrentDefaultGateway" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPersistentIPAddress)->SetReference( _Ptr->GetNode( "GevPersistentIPAddress" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPersistentSubnetMask)->SetReference( _Ptr->GetNode( "GevPersistentSubnetMask" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPersistentDefaultGateway)->SetReference( _Ptr->GetNode( "GevPersistentDefaultGateway" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevLinkSpeed)->SetReference( _Ptr->GetNode( "GevLinkSpeed" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevLinkMaster)->SetReference( _Ptr->GetNode( "GevLinkMaster" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevLinkFullDuplex)->SetReference( _Ptr->GetNode( "GevLinkFullDuplex" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevLinkCrossover)->SetReference( _Ptr->GetNode( "GevLinkCrossover" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&GevFirstURL)->SetReference( _Ptr->GetNode( "GevFirstURL" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&GevSecondURL)->SetReference( _Ptr->GetNode( "GevSecondURL" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevNumberOfInterfaces)->SetReference( _Ptr->GetNode( "GevNumberOfInterfaces" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevMessageChannelCount)->SetReference( _Ptr->GetNode( "GevMessageChannelCount" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevStreamChannelCount)->SetReference( _Ptr->GetNode( "GevStreamChannelCount" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalLegacy16BitBlockID)->SetReference( _Ptr->GetNode( "GevSupportedOptionalLegacy16BitBlockID" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedIEEE1588)->SetReference( _Ptr->GetNode( "GevSupportedIEEE1588" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsEVENTDATA)->SetReference( _Ptr->GetNode( "GevSupportedOptionalCommandsEVENTDATA" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsEVENT)->SetReference( _Ptr->GetNode( "GevSupportedOptionalCommandsEVENT" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsPACKETRESEND)->SetReference( _Ptr->GetNode( "GevSupportedOptionalCommandsPACKETRESEND" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsWRITEMEM)->SetReference( _Ptr->GetNode( "GevSupportedOptionalCommandsWRITEMEM" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSupportedOptionalCommandsConcatenation)->SetReference( _Ptr->GetNode( "GevSupportedOptionalCommandsConcatenation" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevHeartbeatTimeout)->SetReference( _Ptr->GetNode( "GevHeartbeatTimeout" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevTimestampTickFrequency)->SetReference( _Ptr->GetNode( "GevTimestampTickFrequency" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&GevTimestampControlLatch)->SetReference( _Ptr->GetNode( "GevTimestampControlLatch" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&GevTimestampControlReset)->SetReference( _Ptr->GetNode( "GevTimestampControlReset" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&GevTimestampControlLatchReset)->SetReference( _Ptr->GetNode( "GevTimestampControlLatchReset" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevTimestampValue)->SetReference( _Ptr->GetNode( "GevTimestampValue" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevCCPEnums>*> (&GevCCP)->SetReference( _Ptr->GetNode( "GevCCP" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevCCPEnums>*> (&GevCCP)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevCCPEnums>*> (&GevCCP)->SetEnumReference( GevCCP_Exclusive, "Exclusive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevCCPEnums>*> (&GevCCP)->SetEnumReference( GevCCP_Control, "Control" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevCCPEnums>*> (&GevCCP)->SetEnumReference( GevCCP_ExclusiveControl, "ExclusiveControl" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevStreamChannelSelectorEnums>*> (&GevStreamChannelSelector)->SetReference( _Ptr->GetNode( "GevStreamChannelSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevStreamChannelSelectorEnums>*> (&GevStreamChannelSelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevStreamChannelSelectorEnums>*> (&GevStreamChannelSelector)->SetEnumReference( GevStreamChannelSelector_StreamChannel0, "StreamChannel0" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPInterfaceIndex)->SetReference( _Ptr->GetNode( "GevSCPInterfaceIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCDA)->SetReference( _Ptr->GetNode( "GevSCDA" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevSCPHostPort)->SetReference( _Ptr->GetNode( "GevSCPHostPort" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&GevSCPSFireTestPacket)->SetReference( _Ptr->GetNode( "GevSCPSFireTestPacket" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSCPSDoNotFragment)->SetReference( _Ptr->GetNode( "GevSCPSDoNotFragment" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevSCPSBigEndian)->SetReference( _Ptr->GetNode( "GevSCPSBigEndian" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TLParamsLocked)->SetReference( _Ptr->GetNode( "TLParamsLocked" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&PixelFormatLegacy)->SetReference( _Ptr->GetNode( "PixelFormatLegacy" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GevIEEE1588)->SetReference( _Ptr->GetNode( "GevIEEE1588" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetReference( _Ptr->GetNode( "GevIEEE1588Status" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Undefined, "Undefined" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Initializing, "Initializing" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Faulty, "Faulty" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Disabled, "Disabled" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Listening, "Listening" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_PreMaster, "PreMaster" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Master, "Master" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Passive, "Passive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Uncalibrated, "Uncalibrated" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusEnums>*> (&GevIEEE1588Status)->SetEnumReference( GevIEEE1588Status_Slave, "Slave" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&GevIEEE1588DataSetLatch)->SetReference( _Ptr->GetNode( "GevIEEE1588DataSetLatch" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetReference( _Ptr->GetNode( "GevIEEE1588StatusLatched" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Undefined, "Undefined" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Initializing, "Initializing" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Faulty, "Faulty" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Disabled, "Disabled" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Listening, "Listening" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_PreMaster, "PreMaster" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Master, "Master" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Passive, "Passive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Uncalibrated, "Uncalibrated" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GevIEEE1588StatusLatchedEnums>*> (&GevIEEE1588StatusLatched)->SetEnumReference( GevIEEE1588StatusLatched_Slave, "Slave" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588OffsetFromMaster)->SetReference( _Ptr->GetNode( "GevIEEE1588OffsetFromMaster" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ClockIdLow)->SetReference( _Ptr->GetNode( "GevIEEE1588ClockIdLow" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ClockIdHigh)->SetReference( _Ptr->GetNode( "GevIEEE1588ClockIdHigh" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ClockId)->SetReference( _Ptr->GetNode( "GevIEEE1588ClockId" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ParentClockIdLow)->SetReference( _Ptr->GetNode( "GevIEEE1588ParentClockIdLow" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ParentClockIdHigh)->SetReference( _Ptr->GetNode( "GevIEEE1588ParentClockIdHigh" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevIEEE1588ParentClockId)->SetReference( _Ptr->GetNode( "GevIEEE1588ParentClockId" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxEvntMaxNumElements)->SetReference( _Ptr->GetNode( "GevPTPDiagnosticsQueueRxEvntMaxNumElements" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxGnrlMaxNumElements)->SetReference( _Ptr->GetNode( "GevPTPDiagnosticsQueueRxGnrlMaxNumElements" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxEvntPushNumFailure)->SetReference( _Ptr->GetNode( "GevPTPDiagnosticsQueueRxEvntPushNumFailure" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueRxGnrlPushNumFailure)->SetReference( _Ptr->GetNode( "GevPTPDiagnosticsQueueRxGnrlPushNumFailure" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GevPTPDiagnosticsQueueSendNumFailure)->SetReference( _Ptr->GetNode( "GevPTPDiagnosticsQueueSendNumFailure" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&NumberOfActionSignals)->SetReference( _Ptr->GetNode( "NumberOfActionSignals" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ActionCommandCount)->SetReference( _Ptr->GetNode( "ActionCommandCount" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ActionDeviceKey)->SetReference( _Ptr->GetNode( "ActionDeviceKey" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ActionSelector)->SetReference( _Ptr->GetNode( "ActionSelector" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ActionGroupKey)->SetReference( _Ptr->GetNode( "ActionGroupKey" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ActionGroupMask)->SetReference( _Ptr->GetNode( "ActionGroupMask" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingStart)->SetReference( _Ptr->GetNode( "DeviceRegistersStreamingStart" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingEnd)->SetReference( _Ptr->GetNode( "DeviceRegistersStreamingEnd" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetReference( _Ptr->GetNode( "UserSetSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetNumEnums( 11 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_Default, "Default" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_HighGain, "HighGain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_AutoFunctions, "AutoFunctions" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_Color, "Color" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_ColorRaw, "ColorRaw" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_Custom0, "Custom0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_Custom1, "Custom1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_UserSet1, "UserSet1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_UserSet2, "UserSet2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_UserSet3, "UserSet3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_LightMicroscopy, "LightMicroscopy" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&UserSetLoad)->SetReference( _Ptr->GetNode( "UserSetLoad" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&UserSetSave)->SetReference( _Ptr->GetNode( "UserSetSave" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetReference( _Ptr->GetNode( "UserSetDefaultSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetNumEnums( 11 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_Default, "Default" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_HighGain, "HighGain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_AutoFunctions, "AutoFunctions" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_Color, "Color" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_ColorRaw, "ColorRaw" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_Custom0, "Custom0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_Custom1, "Custom1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_UserSet1, "UserSet1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_UserSet2, "UserSet2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_UserSet3, "UserSet3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultSelectorEnums>*> (&UserSetDefaultSelector)->SetEnumReference( UserSetDefaultSelector_LightMicroscopy, "LightMicroscopy" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetReference( _Ptr->GetNode( "DefaultSetSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_Standard, "Standard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_HighGain, "HighGain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_AutoFunctions, "AutoFunctions" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_Color, "Color" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_ColorRaw, "ColorRaw" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_Custom0, "Custom0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_Custom1, "Custom1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefaultSetSelectorEnums>*> (&DefaultSetSelector)->SetEnumReference( DefaultSetSelector_LightMicroscopy, "LightMicroscopy" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoTargetValue)->SetReference( _Ptr->GetNode( "AutoTargetValue" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&GrayValueAdjustmentDampingAbs)->SetReference( _Ptr->GetNode( "GrayValueAdjustmentDampingAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GrayValueAdjustmentDampingRaw)->SetReference( _Ptr->GetNode( "GrayValueAdjustmentDampingRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BalanceWhiteAdjustmentDampingAbs)->SetReference( _Ptr->GetNode( "BalanceWhiteAdjustmentDampingAbs" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BalanceWhiteAdjustmentDampingRaw)->SetReference( _Ptr->GetNode( "BalanceWhiteAdjustmentDampingRaw" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoGainRawLowerLimit)->SetReference( _Ptr->GetNode( "AutoGainRawLowerLimit" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoGainRawUpperLimit)->SetReference( _Ptr->GetNode( "AutoGainRawUpperLimit" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeAbsLowerLimit)->SetReference( _Ptr->GetNode( "AutoExposureTimeAbsLowerLimit" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeAbsUpperLimit)->SetReference( _Ptr->GetNode( "AutoExposureTimeAbsUpperLimit" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetReference( _Ptr->GetNode( "AutoFunctionProfile" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_GainMinimum, "GainMinimum" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_ExposureMinimum, "ExposureMinimum" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_GainMinimumQuick, "GainMinimumQuick" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_ExposureMinimumQuick, "ExposureMinimumQuick" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetReference( _Ptr->GetNode( "AutoFunctionAOISelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI1, "AOI1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI2, "AOI2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI3, "AOI3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI4, "AOI4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI5, "AOI5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI6, "AOI6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI7, "AOI7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI8, "AOI8" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIWidth)->SetReference( _Ptr->GetNode( "AutoFunctionAOIWidth" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIHeight)->SetReference( _Ptr->GetNode( "AutoFunctionAOIHeight" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetX)->SetReference( _Ptr->GetNode( "AutoFunctionAOIOffsetX" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetY)->SetReference( _Ptr->GetNode( "AutoFunctionAOIOffsetY" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageIntensity)->SetReference( _Ptr->GetNode( "AutoFunctionAOIUsageIntensity" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageWhiteBalance)->SetReference( _Ptr->GetNode( "AutoFunctionAOIUsageWhiteBalance" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageRedLightCorrection)->SetReference( _Ptr->GetNode( "AutoFunctionAOIUsageRedLightCorrection" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUsageTonalRange)->SetReference( _Ptr->GetNode( "AutoFunctionAOIUsageTonalRange" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetReference( _Ptr->GetNode( "AutoTonalRangeModeSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetEnumReference( AutoTonalRangeModeSelector_ColorAndContrast, "ColorAndContrast" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetEnumReference( AutoTonalRangeModeSelector_Color, "Color" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetEnumReference( AutoTonalRangeModeSelector_Contrast, "Contrast" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetReference( _Ptr->GetNode( "AutoTonalRangeAdjustmentSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetEnumReference( AutoTonalRangeAdjustmentSelector_DarkAndBright, "DarkAndBright" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetEnumReference( AutoTonalRangeAdjustmentSelector_Bright, "Bright" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetEnumReference( AutoTonalRangeAdjustmentSelector_Dark, "Dark" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdDark)->SetReference( _Ptr->GetNode( "AutoTonalRangeThresholdDark" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeThresholdDarkRaw)->SetReference( _Ptr->GetNode( "AutoTonalRangeThresholdDarkRaw" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdBright)->SetReference( _Ptr->GetNode( "AutoTonalRangeThresholdBright" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeThresholdBrightRaw)->SetReference( _Ptr->GetNode( "AutoTonalRangeThresholdBrightRaw" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetDark)->SetReference( _Ptr->GetNode( "AutoTonalRangeTargetDark" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetBright)->SetReference( _Ptr->GetNode( "AutoTonalRangeTargetBright" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorOverexposureCompensationAOISelectorEnums>*> (&ColorOverexposureCompensationAOISelector)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOISelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorOverexposureCompensationAOISelectorEnums>*> (&ColorOverexposureCompensationAOISelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorOverexposureCompensationAOISelectorEnums>*> (&ColorOverexposureCompensationAOISelector)->SetEnumReference( ColorOverexposureCompensationAOISelector_AOI1, "AOI1" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ColorOverexposureCompensationAOIEnable)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOIEnable" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorOverexposureCompensationAOIFactor)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOIFactor" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIFactorRaw)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOIFactorRaw" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIWidth)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOIWidth" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIHeight)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOIHeight" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIOffsetX)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOIOffsetX" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ColorOverexposureCompensationAOIOffsetY)->SetReference( _Ptr->GetNode( "ColorOverexposureCompensationAOIOffsetY" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSelectorEnums>*> (&ShadingSelector)->SetReference( _Ptr->GetNode( "ShadingSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSelectorEnums>*> (&ShadingSelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSelectorEnums>*> (&ShadingSelector)->SetEnumReference( ShadingSelector_OffsetShading, "OffsetShading" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSelectorEnums>*> (&ShadingSelector)->SetEnumReference( ShadingSelector_GainShading, "GainShading" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ShadingEnable)->SetReference( _Ptr->GetNode( "ShadingEnable" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>*> (&ShadingStatus)->SetReference( _Ptr->GetNode( "ShadingStatus" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>*> (&ShadingStatus)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>*> (&ShadingStatus)->SetEnumReference( ShadingStatus_NoError, "NoError" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>*> (&ShadingStatus)->SetEnumReference( ShadingStatus_StartupSetError, "StartupSetError" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>*> (&ShadingStatus)->SetEnumReference( ShadingStatus_ActivateError, "ActivateError" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingStatusEnums>*> (&ShadingStatus)->SetEnumReference( ShadingStatus_CreateError, "CreateError" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetDefaultSelectorEnums>*> (&ShadingSetDefaultSelector)->SetReference( _Ptr->GetNode( "ShadingSetDefaultSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetDefaultSelectorEnums>*> (&ShadingSetDefaultSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetDefaultSelectorEnums>*> (&ShadingSetDefaultSelector)->SetEnumReference( ShadingSetDefaultSelector_DefaultShadingSet, "DefaultShadingSet" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetDefaultSelectorEnums>*> (&ShadingSetDefaultSelector)->SetEnumReference( ShadingSetDefaultSelector_UserShadingSet1, "UserShadingSet1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetDefaultSelectorEnums>*> (&ShadingSetDefaultSelector)->SetEnumReference( ShadingSetDefaultSelector_UserShadingSet2, "UserShadingSet2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetSelectorEnums>*> (&ShadingSetSelector)->SetReference( _Ptr->GetNode( "ShadingSetSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetSelectorEnums>*> (&ShadingSetSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetSelectorEnums>*> (&ShadingSetSelector)->SetEnumReference( ShadingSetSelector_DefaultShadingSet, "DefaultShadingSet" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetSelectorEnums>*> (&ShadingSetSelector)->SetEnumReference( ShadingSetSelector_UserShadingSet1, "UserShadingSet1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetSelectorEnums>*> (&ShadingSetSelector)->SetEnumReference( ShadingSetSelector_UserShadingSet2, "UserShadingSet2" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&ShadingSetActivate)->SetReference( _Ptr->GetNode( "ShadingSetActivate" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetCreateEnums>*> (&ShadingSetCreate)->SetReference( _Ptr->GetNode( "ShadingSetCreate" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetCreateEnums>*> (&ShadingSetCreate)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetCreateEnums>*> (&ShadingSetCreate)->SetEnumReference( ShadingSetCreate_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShadingSetCreateEnums>*> (&ShadingSetCreate)->SetEnumReference( ShadingSetCreate_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetReference( _Ptr->GetNode( "UserDefinedValueSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value1, "Value1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value2, "Value2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value3, "Value3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value4, "Value4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value5, "Value5" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&UserDefinedValue)->SetReference( _Ptr->GetNode( "UserDefinedValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GenicamXmlFileDefault)->SetReference( _Ptr->GetNode( "GenicamXmlFileDefault" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FeatureSetEnums>*> (&FeatureSet)->SetReference( _Ptr->GetNode( "FeatureSet" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FeatureSetEnums>*> (&FeatureSet)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FeatureSetEnums>*> (&FeatureSet)->SetEnumReference( FeatureSet_Full, "Full" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FeatureSetEnums>*> (&FeatureSet)->SetEnumReference( FeatureSet_Basic, "Basic" );        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceVendorName)->SetReference( _Ptr->GetNode( "DeviceVendorName" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceModelName)->SetReference( _Ptr->GetNode( "DeviceModelName" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceManufacturerInfo)->SetReference( _Ptr->GetNode( "DeviceManufacturerInfo" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceVersion)->SetReference( _Ptr->GetNode( "DeviceVersion" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceFirmwareVersion)->SetReference( _Ptr->GetNode( "DeviceFirmwareVersion" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceID)->SetReference( _Ptr->GetNode( "DeviceID" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceUserID)->SetReference( _Ptr->GetNode( "DeviceUserID" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetReference( _Ptr->GetNode( "DeviceScanType" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetEnumReference( DeviceScanType_Areascan, "Areascan" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetEnumReference( DeviceScanType_Linescan, "Linescan" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&DeviceReset)->SetReference( _Ptr->GetNode( "DeviceReset" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>*> (&TemperatureSelector)->SetReference( _Ptr->GetNode( "TemperatureSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>*> (&TemperatureSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>*> (&TemperatureSelector)->SetEnumReference( TemperatureSelector_Sensorboard, "Sensorboard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>*> (&TemperatureSelector)->SetEnumReference( TemperatureSelector_Coreboard, "Coreboard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>*> (&TemperatureSelector)->SetEnumReference( TemperatureSelector_Framegrabberboard, "Framegrabberboard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureSelectorEnums>*> (&TemperatureSelector)->SetEnumReference( TemperatureSelector_Case, "Case" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TemperatureAbs)->SetReference( _Ptr->GetNode( "TemperatureAbs" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetReference( _Ptr->GetNode( "TemperatureState" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetEnumReference( TemperatureState_Ok, "Ok" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetEnumReference( TemperatureState_Critical, "Critical" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetEnumReference( TemperatureState_Error, "Error" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&CriticalTemperature)->SetReference( _Ptr->GetNode( "CriticalTemperature" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&OverTemperature)->SetReference( _Ptr->GetNode( "OverTemperature" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetReference( _Ptr->GetNode( "LastError" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_NoError, "NoError" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_Overtrigger, "Overtrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_Userset, "Userset" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_InvalidParameter, "InvalidParameter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_OverTemperature, "OverTemperature" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_PowerFailure, "PowerFailure" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_InsufficientTriggerWidth, "InsufficientTriggerWidth" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LastErrorEnums>*> (&LastError)->SetEnumReference( LastError_UserDefPixFailure, "UserDefPixFailure" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&ClearLastError)->SetReference( _Ptr->GetNode( "ClearLastError" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceColorPipelineVersion)->SetReference( _Ptr->GetNode( "DeviceColorPipelineVersion" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetReference( _Ptr->GetNode( "ParameterSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_Gain, "Gain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_Brightness, "Brightness" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_BlackLevel, "BlackLevel" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_ExposureTime, "ExposureTime" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_Framerate, "Framerate" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_AutoTargetValue, "AutoTargetValue" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_ExposureOverhead, "ExposureOverhead" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ParameterSelectorEnums>*> (&ParameterSelector)->SetEnumReference( ParameterSelector_ExposureOverlapMax, "ExposureOverlapMax" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&RemoveLimits)->SetReference( _Ptr->GetNode( "RemoveLimits" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Prelines)->SetReference( _Ptr->GetNode( "Prelines" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetReference( _Ptr->GetNode( "ExpertFeatureAccessSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetNumEnums( 11 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature1_Legacy, "ExpertFeature1_Legacy" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature1, "ExpertFeature1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature2, "ExpertFeature2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature3, "ExpertFeature3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature4, "ExpertFeature4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature5, "ExpertFeature5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature6, "ExpertFeature6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature7, "ExpertFeature7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature8, "ExpertFeature8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature9, "ExpertFeature9" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature10, "ExpertFeature10" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExpertFeatureAccessKey)->SetReference( _Ptr->GetNode( "ExpertFeatureAccessKey" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ExpertFeatureEnable)->SetReference( _Ptr->GetNode( "ExpertFeatureEnable" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ChunkModeActive)->SetReference( _Ptr->GetNode( "ChunkModeActive" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetReference( _Ptr->GetNode( "ChunkSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetNumEnums( 27 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Image, "Image" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_OffsetX, "OffsetX" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_OffsetY, "OffsetY" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Width, "Width" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Height, "Height" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_PixelFormat, "PixelFormat" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_DynamicRangeMax, "DynamicRangeMax" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_DynamicRangeMin, "DynamicRangeMin" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Timestamp, "Timestamp" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_LineStatusAll, "LineStatusAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Framecounter, "Framecounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Triggerinputcounter, "Triggerinputcounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_LineTriggerIgnoredCounter, "LineTriggerIgnoredCounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_FrameTriggerIgnoredCounter, "FrameTriggerIgnoredCounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_LineTriggerEndToEndCounter, "LineTriggerEndToEndCounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_FrameTriggerCounter, "FrameTriggerCounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_FramesPerTriggerCounter, "FramesPerTriggerCounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_InputStatusAtLineTrigger, "InputStatusAtLineTrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_ShaftEncoderCounter, "ShaftEncoderCounter" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_PayloadCRC16, "PayloadCRC16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Stride, "Stride" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_SequenceSetIndex, "SequenceSetIndex" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_ExposureTime, "ExposureTime" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_GainAll, "GainAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_BrightPixel, "BrightPixel" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_VirtLineStatusAll, "VirtLineStatusAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_LineTriggerCounter, "LineTriggerCounter" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ChunkEnable)->SetReference( _Ptr->GetNode( "ChunkEnable" ) );
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
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetReference( _Ptr->GetNode( "EventSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetNumEnums( 23 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_ExposureEnd, "ExposureEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_LineStartOvertrigger, "LineStartOvertrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameStartOvertrigger, "FrameStartOvertrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_AcquisitionStartOvertrigger, "AcquisitionStartOvertrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameTimeout, "FrameTimeout" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameStart, "FrameStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_AcquisitionStart, "AcquisitionStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_CriticalTemperature, "CriticalTemperature" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_OverTemperature, "OverTemperature" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_ActionLate, "ActionLate" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_Line1RisingEdge, "Line1RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_Line2RisingEdge, "Line2RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_Line3RisingEdge, "Line3RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_Line4RisingEdge, "Line4RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_VirtualLine1RisingEdge, "VirtualLine1RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_VirtualLine2RisingEdge, "VirtualLine2RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_VirtualLine3RisingEdge, "VirtualLine3RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_VirtualLine4RisingEdge, "VirtualLine4RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameWait, "FrameWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_AcquisitionWait, "AcquisitionWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameStartWait, "FrameStartWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_AcquisitionStartWait, "AcquisitionStartWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_EventOverrun, "EventOverrun" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetReference( _Ptr->GetNode( "EventNotification" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetEnumReference( EventNotification_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetEnumReference( EventNotification_GenICamEvent, "GenICamEvent" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetEnumReference( EventNotification_On, "On" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExposureEndEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "ExposureEndEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExposureEndEventFrameID)->SetReference( _Ptr->GetNode( "ExposureEndEventFrameID" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExposureEndEventTimestamp)->SetReference( _Ptr->GetNode( "ExposureEndEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LineStartOvertriggerEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "LineStartOvertriggerEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LineStartOvertriggerEventTimestamp)->SetReference( _Ptr->GetNode( "LineStartOvertriggerEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartOvertriggerEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "FrameStartOvertriggerEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartOvertriggerEventTimestamp)->SetReference( _Ptr->GetNode( "FrameStartOvertriggerEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "FrameStartEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartEventTimestamp)->SetReference( _Ptr->GetNode( "FrameStartEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "AcquisitionStartEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartEventTimestamp)->SetReference( _Ptr->GetNode( "AcquisitionStartEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartOvertriggerEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "AcquisitionStartOvertriggerEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartOvertriggerEventTimestamp)->SetReference( _Ptr->GetNode( "AcquisitionStartOvertriggerEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameTimeoutEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "FrameTimeoutEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameTimeoutEventTimestamp)->SetReference( _Ptr->GetNode( "FrameTimeoutEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventOverrunEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "EventOverrunEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventOverrunEventFrameID)->SetReference( _Ptr->GetNode( "EventOverrunEventFrameID" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventOverrunEventTimestamp)->SetReference( _Ptr->GetNode( "EventOverrunEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&CriticalTemperatureEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "CriticalTemperatureEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&CriticalTemperatureEventTimestamp)->SetReference( _Ptr->GetNode( "CriticalTemperatureEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OverTemperatureEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "OverTemperatureEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OverTemperatureEventTimestamp)->SetReference( _Ptr->GetNode( "OverTemperatureEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ActionLateEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "ActionLateEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ActionLateEventTimestamp)->SetReference( _Ptr->GetNode( "ActionLateEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LateActionEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "LateActionEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LateActionEventTimestamp)->SetReference( _Ptr->GetNode( "LateActionEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line1RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "Line1RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line1RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "Line1RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line2RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "Line2RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line2RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "Line2RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line3RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "Line3RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line3RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "Line3RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line4RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "Line4RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Line4RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "Line4RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine1RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "VirtualLine1RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine1RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "VirtualLine1RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine2RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "VirtualLine2RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine2RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "VirtualLine2RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine3RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "VirtualLine3RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine3RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "VirtualLine3RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine4RisingEdgeEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "VirtualLine4RisingEdgeEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&VirtualLine4RisingEdgeEventTimestamp)->SetReference( _Ptr->GetNode( "VirtualLine4RisingEdgeEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameWaitEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "FrameWaitEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameWaitEventTimestamp)->SetReference( _Ptr->GetNode( "FrameWaitEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionWaitEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "AcquisitionWaitEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionWaitEventTimestamp)->SetReference( _Ptr->GetNode( "AcquisitionWaitEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartWaitEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "FrameStartWaitEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameStartWaitEventTimestamp)->SetReference( _Ptr->GetNode( "FrameStartWaitEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartWaitEventStreamChannelIndex)->SetReference( _Ptr->GetNode( "AcquisitionStartWaitEventStreamChannelIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionStartWaitEventTimestamp)->SetReference( _Ptr->GetNode( "AcquisitionStartWaitEventTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetReference( _Ptr->GetNode( "FileSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetNumEnums( 9 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserData, "UserData" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserSet1, "UserSet1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserSet2, "UserSet2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserSet3, "UserSet3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserGainShading1, "UserGainShading1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserGainShading2, "UserGainShading2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserOffsetShading1, "UserOffsetShading1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_UserOffsetShading2, "UserOffsetShading2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileSelectorEnums>*> (&FileSelector)->SetEnumReference( FileSelector_ExpertFeature7File, "ExpertFeature7File" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>*> (&FileOperationSelector)->SetReference( _Ptr->GetNode( "FileOperationSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>*> (&FileOperationSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>*> (&FileOperationSelector)->SetEnumReference( FileOperationSelector_Open, "Open" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>*> (&FileOperationSelector)->SetEnumReference( FileOperationSelector_Close, "Close" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>*> (&FileOperationSelector)->SetEnumReference( FileOperationSelector_Read, "Read" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationSelectorEnums>*> (&FileOperationSelector)->SetEnumReference( FileOperationSelector_Write, "Write" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOpenModeEnums>*> (&FileOpenMode)->SetReference( _Ptr->GetNode( "FileOpenMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOpenModeEnums>*> (&FileOpenMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOpenModeEnums>*> (&FileOpenMode)->SetEnumReference( FileOpenMode_Read, "Read" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOpenModeEnums>*> (&FileOpenMode)->SetEnumReference( FileOpenMode_Write, "Write" );        static_cast<GENAPI_NAMESPACE::CRegisterRef*> (&FileAccessBuffer)->SetReference( _Ptr->GetNode( "FileAccessBuffer" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FileAccessOffset)->SetReference( _Ptr->GetNode( "FileAccessOffset" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FileAccessLength)->SetReference( _Ptr->GetNode( "FileAccessLength" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationStatusEnums>*> (&FileOperationStatus)->SetReference( _Ptr->GetNode( "FileOperationStatus" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationStatusEnums>*> (&FileOperationStatus)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationStatusEnums>*> (&FileOperationStatus)->SetEnumReference( FileOperationStatus_Success, "Success" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<FileOperationStatusEnums>*> (&FileOperationStatus)->SetEnumReference( FileOperationStatus_Failure, "Failure" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FileOperationResult)->SetReference( _Ptr->GetNode( "FileOperationResult" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FileSize)->SetReference( _Ptr->GetNode( "FileSize" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&FileOperationExecute)->SetReference( _Ptr->GetNode( "FileOperationExecute" ) );

    }

    inline const char* CGigECamera_Params::_GetVendorName( void )
    {
        return "Basler";
    }

    inline const char* CGigECamera_Params::_GetModelName( void )
    {
        return "GigECamera";
    }

    //! \endcond

} // namespace Basler_GigECamera

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_GigECamera_PARAMS_H
