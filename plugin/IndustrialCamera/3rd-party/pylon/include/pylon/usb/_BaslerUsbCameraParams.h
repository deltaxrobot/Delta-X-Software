

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



#ifndef Basler_UsbCameraParams_PARAMS_H
#define Basler_UsbCameraParams_PARAMS_H

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
namespace Basler_UsbCameraParams
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    //! Valid values for CameraOperationMode
    enum CameraOperationModeEnums
    {
        CameraOperationMode_Standard,  //!<
        CameraOperationMode_LongExposure   //!<

    };

    //! Valid values for SequencerMode
    enum SequencerModeEnums
    {
        SequencerMode_Off,  //!<The sequencer can not be used for image acquisition.
        SequencerMode_On   //!<The sequencer can be used for image acquisition.

    };

    //! Valid values for SequencerConfigurationMode
    enum SequencerConfigurationModeEnums
    {
        SequencerConfigurationMode_Off,  //!<The sequencer can not be configured.
        SequencerConfigurationMode_On   //!<The sequencer can be configured.

    };

    //! Valid values for SequencerTriggerSource
    enum SequencerTriggerSourceEnums
    {
        SequencerTriggerSource_Line1,  //!<Line 1 is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_Line2,  //!<Line 2 is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_Line3,  //!<Line 3 is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_Line4,  //!<Line 4 is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_SoftwareSignal1,  //!<Software signal 1 is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_SoftwareSignal2,  //!<Software signal 2 is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_SoftwareSignal3,  //!<Software signal 3 is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_Counter1End,  //!<Counter 1 End is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_Counter2End,  //!<Counter 2 End is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_Counter3End,  //!<Counter 3 End is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_FrameStart,  //!<Frame Start is selected as the trigger source for sequencer set advance.
        SequencerTriggerSource_FrameEnd   //!<Frame End is selected as the trigger source for sequencer set advance.

    };

    //! Valid values for SequencerTriggerActivation
    enum SequencerTriggerActivationEnums
    {
        SequencerTriggerActivation_RisingEdge,  //!<The sequence set will advance on the rising edge of the source signal.
        SequencerTriggerActivation_FallingEdge,  //!<The sequence set will advance on the falling edge of the source signal.
        SequencerTriggerActivation_AnyEdge,  //!<The sequence set will advance on the falling or rising edge of the source signal.
        SequencerTriggerActivation_LevelHigh,  //!<The sequence set will advance when the source signal is high.
        SequencerTriggerActivation_LevelLow   //!<The sequence set will advance when the source signal is low.

    };

    //! Valid values for BinningHorizontalMode
    enum BinningHorizontalModeEnums
    {
        BinningHorizontalMode_Sum,  //!<The values of the binned pixels are summed.
        BinningHorizontalMode_Average   //!<The values of the binned pixels are averaged.

    };

    //! Valid values for BinningVerticalMode
    enum BinningVerticalModeEnums
    {
        BinningVerticalMode_Sum,  //!<The values of the binned pixels are summed.
        BinningVerticalMode_Average   //!<The values of the binned pixels are averaged.

    };

    //! Valid values for PixelFormat
    enum PixelFormatEnums
    {
        PixelFormat_Mono8,  //!<The pixel format is set to Mono 8.
        PixelFormat_Mono10,  //!<The pixel format is set to Mono 10.
        PixelFormat_Mono10p,  //!<The pixel format is set to Mono 10p.
        PixelFormat_Mono12,  //!<The pixel format is set to Mono 12.
        PixelFormat_Mono12p,  //!<The pixel format is set to Mono 12p.
        PixelFormat_BayerGR8,  //!<The pixel format is set to Bayer GR 8.
        PixelFormat_BayerRG8,  //!<The pixel format is set to Bayer RG 8.
        PixelFormat_BayerGB8,  //!<The pixel format is set to Bayer GB 8.
        PixelFormat_BayerBG8,  //!<The pixel format is set to Bayer BG 8.
        PixelFormat_BayerGR10,  //!<The pixel format is set to Bayer GR 10.
        PixelFormat_BayerGR10p,  //!<The pixel format is set to Bayer GR 10p.
        PixelFormat_BayerRG10,  //!<The pixel format is set to Bayer RG 10.
        PixelFormat_BayerRG10p,  //!<The pixel format is set to Bayer RG 10p.
        PixelFormat_BayerGB10,  //!<The pixel format is set to Bayer GB 10.
        PixelFormat_BayerGB10p,  //!<The pixel format is set to Bayer GB 10p.
        PixelFormat_BayerBG10,  //!<The pixel format is set to Bayer BG 10.
        PixelFormat_BayerBG10p,  //!<The pixel format is set to Bayer BG 10p.
        PixelFormat_BayerGR12,  //!<The pixel format is set to Bayer GR 12.
        PixelFormat_BayerGR12p,  //!<The pixel format is set to Bayer GR 12p.
        PixelFormat_BayerRG12,  //!<The pixel format is set to Bayer RG 12.
        PixelFormat_BayerRG12p,  //!<The pixel format is set to Bayer RG 12p.
        PixelFormat_BayerGB12,  //!<The pixel format is set to Bayer GB 12.
        PixelFormat_BayerGB12p,  //!<The pixel format is set to Bayer GB 12p.
        PixelFormat_BayerBG12,  //!<The pixel format is set to Bayer BG 12.
        PixelFormat_BayerBG12p,  //!<The pixel format is set to Bayer BG 12p.
        PixelFormat_RGB8,  //!<The pixel format is set to RGB 8
        PixelFormat_BGR8,  //!<The pixel format is set to BGR 8
        PixelFormat_YCbCr422_8   //!<The pixel format is set to YCbCr 422.

    };

    //! Valid values for PixelSize
    enum PixelSizeEnums
    {
        PixelSize_Bpp1,  //!<The depth of the pixel values in the acquired images is 1 bit per pixel.
        PixelSize_Bpp2,  //!<The depth of the pixel values in the acquired images is 2 bits per pixel.
        PixelSize_Bpp4,  //!<The depth of the pixel values in the acquired images is 4 bits per pixel.
        PixelSize_Bpp8,  //!<The depth of the pixel values in the acquired images is 8 bits per pixel.
        PixelSize_Bpp10,  //!<The depth of the pixel values in the acquired images is 10 bits per pixel.
        PixelSize_Bpp12,  //!<The depth of the pixel values in the acquired images is 12 bits per pixel.
        PixelSize_Bpp16,  //!<The depth of the pixel values in the acquired images is 16 bits per pixel.
        PixelSize_Bpp24   //!<The depth of the pixel values in the acquired images is 24 bits per pixel.

    };

    //! Valid values for PixelColorFilter
    enum PixelColorFilterEnums
    {
        PixelColorFilter_None,  //!<No Bayer filter is present on the camera.
        PixelColorFilter_BayerRG,  //!<The Bayer filter has an RG/GB alignment to the pixels in the acquired images.
        PixelColorFilter_BayerGB,  //!<The Bayer filter has a GB/RG alignment to the pixels in the acquired images.
        PixelColorFilter_BayerGR,  //!<The Bayer filter has a GR/BG alignment to the pixels in the acquired images.
        PixelColorFilter_BayerBG   //!<The Bayer filter has a BG/GR alignment to the pixels in the acquired images.

    };

    //! Valid values for TestImageSelector
    enum TestImageSelectorEnums
    {
        TestImageSelector_Off,  //!<The camera does not display a test image.
        TestImageSelector_Testimage1,  //!<The camera generates and displays a test image with a test image 1 pattern.
        TestImageSelector_Testimage2,  //!<The camera generates and displays a test image with a test image 2 pattern.
        TestImageSelector_Testimage3,  //!<The camera generates and displays a test image with a test image 3 pattern.
        TestImageSelector_Testimage4,  //!<The camera generates and displays a test image with a test image 4 pattern.
        TestImageSelector_Testimage5,  //!<The camera generates and displays a test image with a test image 5 pattern.
        TestImageSelector_Testimage6   //!<The camera generates and displays a test image with a test image 6 pattern.

    };

    //! Valid values for TestPattern
    enum TestPatternEnums
    {
        TestPattern_Off,  //!<No test pattern. Displays the original image.
        TestPattern_GreyDiagonalSawtooth8,  //!<
        TestPattern_ColorDiagonalSawtooth8   //!<

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

    //! Valid values for GainAuto
    enum GainAutoEnums
    {
        GainAuto_Off,  //!<The gain auto function is disabled.
        GainAuto_Once,  //!<Gain is adjusted automatically until it reaches a specific target value.
        GainAuto_Continuous   //!<Gain is adjusted repeatedly while images are acquired.

    };

    //! Valid values for GainSelector
    enum GainSelectorEnums
    {
        GainSelector_All,  //!<Gain will be applied to all channels or taps.
        GainSelector_DigitalAll,  //!<Gain will be applied to all digital channels.
        GainSelector_AnalogAll   //!<Gain will be applied to all analog channels.

    };

    //! Valid values for BlackLevelSelector
    enum BlackLevelSelectorEnums
    {
        BlackLevelSelector_All   //!<Black level will be applied to all channels or taps.

    };

    //! Valid values for ColorSpace
    enum ColorSpaceEnums
    {
        ColorSpace_RGB,  //!<Color space is set to RGB.
        ColorSpace_sRGB   //!<Color space is set to sRGB. The image brightness is optimized for display on an sRGB monitor.

    };

    //! Valid values for BslColorSpaceMode
    enum BslColorSpaceModeEnums
    {
        BslColorSpaceMode_RGB,  //!<Color space is set to RGB.
        BslColorSpaceMode_sRGB   //!<Color space is set to sRGB

    };

    //! Valid values for LightSourcePreset
    enum LightSourcePresetEnums
    {
        LightSourcePreset_Off,  //!<No color preset is set.
        LightSourcePreset_Daylight5000K,  //!<A color preset for image acquisition with daylight of 5000 K is set.
        LightSourcePreset_Daylight6500K,  //!<A color preset for image acquisition with daylight of 6500 K is set.
        LightSourcePreset_Tungsten2800K,  //!<A color preset for image acquisition with tungsten incandescent light (2800 K) is set.
        LightSourcePreset_MicroscopeLED4500K,  //!<
        LightSourcePreset_MicroscopeLED5500K,  //!<
        LightSourcePreset_MicroscopeLED6000K   //!<

    };

    //! Valid values for BalanceWhiteAuto
    enum BalanceWhiteAutoEnums
    {
        BalanceWhiteAuto_Off,  //!<The balance white auto function is disabled.
        BalanceWhiteAuto_Once,  //!<White balance is adjusted automatically until it reaches a specific target value.
        BalanceWhiteAuto_Continuous   //!<White balance is adjusted repeatedly while images are acquired.

    };

    //! Valid values for BalanceRatioSelector
    enum BalanceRatioSelectorEnums
    {
        BalanceRatioSelector_Red,  //!<Balance ratio will be applied to the red channel.
        BalanceRatioSelector_Green,  //!<Balance ratio will be applied to the green channel.
        BalanceRatioSelector_Blue   //!<Balance ratio will be applied to the blue channel.

    };

    //! Valid values for ColorAdjustmentSelector
    enum ColorAdjustmentSelectorEnums
    {
        ColorAdjustmentSelector_Red,  //!<Colors with predominant red can be adjusted.
        ColorAdjustmentSelector_Yellow,  //!<Colors with predominant yellow can be adjusted.
        ColorAdjustmentSelector_Green,  //!<Colors with predominant green can be adjusted.
        ColorAdjustmentSelector_Cyan,  //!<Colors with predominant cyan can be adjusted.
        ColorAdjustmentSelector_Blue,  //!<Colors with predominant blue can be adjusted.
        ColorAdjustmentSelector_Magenta   //!<Colors with predominant magenta can be adjusted.

    };

    //! Valid values for ColorTransformationSelector
    enum ColorTransformationSelectorEnums
    {
        ColorTransformationSelector_RGBtoRGB,  //!<A matrix color transformation from RGB to RGB is performed on the pixels.
        ColorTransformationSelector_RGBtoYUV,  //!<A matrix color transformation from RGB to YUV is performed on the pixels.
        ColorTransformationSelector_YUVtoRGB   //!<A matrix color transformation from YUV to RGB is performed on the pixels.

    };

    //! Valid values for ColorTransformationValueSelector
    enum ColorTransformationValueSelectorEnums
    {
        ColorTransformationValueSelector_Gain00,  //!<The element in row 0 and column 0 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain01,  //!<The element in row 0 and column 1 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain02,  //!<The element in row 0 and column 2 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain10,  //!<The element in row 1 and column 0 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain11,  //!<The element in row 1 and column 1 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain12,  //!<The element in row 1 and column 2 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain20,  //!<The element in row 2 and column 0 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain21,  //!<The element in row 2 and column 1 of the color transformation matrix can be entered.
        ColorTransformationValueSelector_Gain22   //!<The element in row 2 and column 2 of the color transformation matrix can be entered.

    };

    //! Valid values for BslContrastMode
    enum BslContrastModeEnums
    {
        BslContrastMode_Linear,  //!<Linear contrast enhancement is used to adjust the contrast.
        BslContrastMode_SCurve   //!<S-curve contrast enhancement is used to adjust the contrast.

    };

    //! Valid values for DefectPixelCorrectionMode
    enum DefectPixelCorrectionModeEnums
    {
        DefectPixelCorrectionMode_Off,  //!<
        DefectPixelCorrectionMode_On,  //!<
        DefectPixelCorrectionMode_StaticOnly   //!<

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

    //! Valid values for AcquisitionMode
    enum AcquisitionModeEnums
    {
        AcquisitionMode_SingleFrame,  //!<The acquisition mode is set to single frame.
        AcquisitionMode_Continuous   //!<The acquisition mode is set to continuous.

    };

    //! Valid values for ShutterMode
    enum ShutterModeEnums
    {
        ShutterMode_Global,  //!<The shutter mode is set to global shutter.
        ShutterMode_Rolling,  //!<The shutter mode is set to rolling shutter.
        ShutterMode_GlobalResetRelease   //!<The shutter mode is set to global reset release shutter.

    };

    //! Valid values for ExposureAuto
    enum ExposureAutoEnums
    {
        ExposureAuto_Off,  //!<The exposure time auto function is disabled.
        ExposureAuto_Once,  //!<Exposure time is adjusted automatically until it reaches a specific target value.
        ExposureAuto_Continuous   //!<Exposure time is adjusted repeatedly while images are acquired.

    };

    //! Valid values for ExposureTimeMode
    enum ExposureTimeModeEnums
    {
        ExposureTimeMode_Standard,  //!<
        ExposureTimeMode_UltraShort   //!<

    };

    //! Valid values for ExposureMode
    enum ExposureModeEnums
    {
        ExposureMode_Timed,  //!<The timed exposure mode is set.
        ExposureMode_TriggerWidth   //!<The trigger width exposure mode is set.

    };

    //! Valid values for ExposureOverlapTimeMode
    enum ExposureOverlapTimeModeEnums
    {
        ExposureOverlapTimeMode_Manual,  //!<The camera manually sets the overlap time for each acquisition.
        ExposureOverlapTimeMode_Automatic   //!<The camera automatically uses the optimum overlap time for each acquisition.

    };

    //! Valid values for SensorReadoutMode
    enum SensorReadoutModeEnums
    {
        SensorReadoutMode_Normal,  //!<The device operates in normal readout mode.
        SensorReadoutMode_Fast   //!<The device operates in fast readout mode.

    };

    //! Valid values for TriggerSelector
    enum TriggerSelectorEnums
    {
        TriggerSelector_FrameBurstStart,  //!<The frame burst start trigger can be configured.
        TriggerSelector_FrameStart   //!<The frame start trigger can be configured.

    };

    //! Valid values for TriggerMode
    enum TriggerModeEnums
    {
        TriggerMode_Off,  //!<The currently selected trigger is turned off.
        TriggerMode_On   //!<The currently selected trigger is turned on.

    };

    //! Valid values for TriggerSource
    enum TriggerSourceEnums
    {
        TriggerSource_Software,  //!<The signal source for the selected trigger is set to software triggering.
        TriggerSource_Line1,  //!<The signal source for the selected trigger is set to line 1.
        TriggerSource_Line2,  //!<The signal source for the selected trigger is set to line 2.
        TriggerSource_Line3,  //!<The signal source for the selected trigger is set to line 3.
        TriggerSource_Line4,  //!<The signal source for the selected trigger is set to line 4.
        TriggerSource_SoftwareSignal1,  //!<The signal source for the selected trigger is set to software signal 1.
        TriggerSource_SoftwareSignal2,  //!<The signal source for the selected trigger is set to software signal 2.
        TriggerSource_SoftwareSignal3   //!<The signal source for the selected trigger is set to software signal 3.

    };

    //! Valid values for TriggerActivation
    enum TriggerActivationEnums
    {
        TriggerActivation_RisingEdge,  //!<The selected trigger is activated on the rising edge of the source signal.
        TriggerActivation_FallingEdge,  //!<The selected trigger is activated on the falling edge of the source signal.
        TriggerActivation_AnyEdge,  //!<The selected trigger is activated on the falling or rising edge of the source signal.
        TriggerActivation_LevelHigh,  //!<The selected trigger is activated when the source signal is high.
        TriggerActivation_LevelLow   //!<The selected trigger is activated when the source signal is low.

    };

    //! Valid values for AcquisitionStatusSelector
    enum AcquisitionStatusSelectorEnums
    {
        AcquisitionStatusSelector_FrameBurstTriggerWait,  //!<A check can be performed if the device is currently waiting for a frame burst trigger.
        AcquisitionStatusSelector_FrameBurstTriggerActive,  //!<A check can be performed if the device is currently doing a frame burst of one or many frames.
        AcquisitionStatusSelector_FrameBurstTriggerTransfer,  //!<A check can be performed if the device is currently transferring a frame burst of one or many frames.
        AcquisitionStatusSelector_FrameTriggerWait,  //!<A check can be performed if the device is currently waiting for a frame trigger.
        AcquisitionStatusSelector_FrameActive,  //!<A check can be performed if the device is currently capturing a frame.
        AcquisitionStatusSelector_FrameTransfer,  //!<A check can be performed if the device is currently transferring a frame.
        AcquisitionStatusSelector_ExposureActive,  //!<A check can be performed if the device is currently exposing a frame.
        AcquisitionStatusSelector_AcquisitionIdle   //!<

    };

    //! Valid values for SensorShutterMode
    enum SensorShutterModeEnums
    {
        SensorShutterMode_Global,  //!<The shutter opens and closes at the same time for all pixels.
        SensorShutterMode_Rolling,  //!<The shutter opens and closes sequentially for groups (typically lines) of pixels.
        SensorShutterMode_GlobalReset   //!<The shutter opens at the same time for all pixels but ends in a sequential manner.

    };

    //! Valid values for OverlapMode
    enum OverlapModeEnums
    {
        OverlapMode_On,  //!<Overlapping exposure and image readout.
        OverlapMode_Off   //!<Non-overlapping exposure and image readout.

    };

    //! Valid values for BslImmediateTriggerMode
    enum BslImmediateTriggerModeEnums
    {
        BslImmediateTriggerMode_On,  //!<The immediate trigger mode is enabled.
        BslImmediateTriggerMode_Off   //!<The immediate trigger mode is disabled.

    };

    //! Valid values for AutoFunctionProfile
    enum AutoFunctionProfileEnums
    {
        AutoFunctionProfile_MinimizeGain,  //!<Gain is kept as low as possible.
        AutoFunctionProfile_MinimizeExposureTime,  //!<Exposure time is kept as low as possible.
        AutoFunctionProfile_Smart,  //!<
        AutoFunctionProfile_AntiFlicker50Hz,  //!<
        AutoFunctionProfile_AntiFlicker60Hz,  //!<
        AutoFunctionProfile_MinimizeGainQuick,  //!<Gain time is kept as low as possible and is adjusted quickly.
        AutoFunctionProfile_MinimizeExposureTimeQuick   //!<Exposure time is kept as low as possible and is adjusted quickly.

    };

    //! Valid values for AutoFunctionROISelector
    enum AutoFunctionROISelectorEnums
    {
        AutoFunctionROISelector_ROI1,  //!<Auto function ROI 1 can be adjusted.
        AutoFunctionROISelector_ROI2   //!<Auto function ROI 2 can be adjusted.

    };

    //! Valid values for AutoFunctionAOISelector
    enum AutoFunctionAOISelectorEnums
    {
        AutoFunctionAOISelector_AOI1,  //!<Auto function AOI 1 can be adjusted.
        AutoFunctionAOISelector_AOI2   //!<Auto function AOI 2 can be adjusted.

    };

    //! Valid values for AutoTonalRangeModeSelector
    enum AutoTonalRangeModeSelectorEnums
    {
        AutoTonalRangeModeSelector_ColorAndContrast,  //!<
        AutoTonalRangeModeSelector_Color,  //!<
        AutoTonalRangeModeSelector_Contrast   //!<

    };

    //! Valid values for AutoTonalRangeAdjustmentSelector
    enum AutoTonalRangeAdjustmentSelectorEnums
    {
        AutoTonalRangeAdjustmentSelector_DarkAndBright,  //!<
        AutoTonalRangeAdjustmentSelector_Bright,  //!<
        AutoTonalRangeAdjustmentSelector_Dark   //!<

    };

    //! Valid values for LUTSelector
    enum LUTSelectorEnums
    {
        LUTSelector_Luminance   //!<The luminance lookup table can be configured.

    };

    //! Valid values for LineSelector
    enum LineSelectorEnums
    {
        LineSelector_Line1,  //!<Line 1 can be configured.
        LineSelector_Line2,  //!<Line 2 can be configured.
        LineSelector_Line3,  //!<Line 3 can be configured.
        LineSelector_Line4   //!<Line 4 can be configured.

    };

    //! Valid values for LineMode
    enum LineModeEnums
    {
        LineMode_Input,  //!<The selected physical line can be used to input an electrical signal.
        LineMode_Output   //!<The selected physical line can be used to output an electrical signal.

    };

    //! Valid values for LineFormat
    enum LineFormatEnums
    {
        LineFormat_NoConnect,  //!<The line is not connected.
        LineFormat_TriState,  //!<The line is currently in tri-state mode (not driven).
        LineFormat_TTL,  //!<The line is currently accepting or sending TTL level signals.
        LineFormat_LVDS,  //!<The line is currently accepting or sending LVDS level signals.
        LineFormat_RS422,  //!<The line is currently accepting or sending RS-422 level signals.
        LineFormat_OptoCoupled,  //!<The line is opto-coupled.
        LineFormat_LVTTL   //!<The line is currently accepting or sending LVTTL level signals.

    };

    //! Valid values for LineLogic
    enum LineLogicEnums
    {
        LineLogic_Positive,  //!<The line logic of the currently selected line is positive.
        LineLogic_Negative   //!<The line logic of the currently selected line is negative.

    };

    //! Valid values for LineSource
    enum LineSourceEnums
    {
        LineSource_Off,  //!<No source signal is set for the currently selected line.
        LineSource_ExposureActive,  //!<The source signal for the currently selected line is set to the exposure active signal.
        LineSource_FrameTriggerWait,  //!<The source signal for the currently selected line is set to the frame trigger wait signal.
        LineSource_FrameBurstTriggerWait,  //!<The source signal for the currently selected line is set to the frame burst trigger wait signal.
        LineSource_Timer1Active,  //!<Sets the source signal for the selected output line to timer 1 active
        LineSource_UserOutput0,  //!<Sets the source signal for the selected output line to user settable output signal 0.
        LineSource_UserOutput1,  //!<Sets the source signal for the selected output line to user settable output signal 1.
        LineSource_UserOutput2,  //!<Sets the source signal for the selected output line to user settable output signal 2.
        LineSource_UserOutput3,  //!<Sets the source signal for the selected output line to user settable output signal 3.
        LineSource_FlashWindow,  //!<The source signal for the currently selected line is set to the flash window signal.
        LineSource_UserOutput4   //!<The User Output 4 bit state as defined by its current UserOutputValue.

    };

    //! Valid values for UserOutputSelector
    enum UserOutputSelectorEnums
    {
        UserOutputSelector_UserOutput0,  //!<User settable output signal 0 can be configured.
        UserOutputSelector_UserOutput1,  //!<User settable output signal 1 can be configured.
        UserOutputSelector_UserOutput2,  //!<User settable output signal 2 can be configured.
        UserOutputSelector_UserOutput3   //!<User settable output signal 3 can be configured.

    };

    //! Valid values for SoftwareSignalSelector
    enum SoftwareSignalSelectorEnums
    {
        SoftwareSignalSelector_SoftwareSignal1,  //!<Software signal 1 can be controlled.
        SoftwareSignalSelector_SoftwareSignal2,  //!<Software signal 2 can be controlled.
        SoftwareSignalSelector_SoftwareSignal3,  //!<Software signal 3 can be controlled.
        SoftwareSignalSelector_SoftwareSignal4   //!<Software signal 4 can be controlled.

    };

    //! Valid values for TimerSelector
    enum TimerSelectorEnums
    {
        TimerSelector_Timer1   //!<Timer 1 can be configured.

    };

    //! Valid values for TimerTriggerSource
    enum TimerTriggerSourceEnums
    {
        TimerTriggerSource_ExposureStart,  //!<The timer can be triggered by the exposure start signal.
        TimerTriggerSource_FlashWindowStart   //!<The timer can be triggered by the flash window start signal.

    };

    //! Valid values for CounterSelector
    enum CounterSelectorEnums
    {
        CounterSelector_Counter1,  //!<Counter 1 can be configured.
        CounterSelector_Counter2   //!<Counter 2 can be configured.

    };

    //! Valid values for CounterEventSource
    enum CounterEventSourceEnums
    {
        CounterEventSource_FrameTrigger,  //!<The selected counter counts the number of Frame Trigger events.
        CounterEventSource_FrameStart,  //!<The selected counter counts the number of Frame Start events.
        CounterEventSource_Counter1End,  //!<The selected counter counts the number of counter 1 end events.
        CounterEventSource_Counter2End,  //!<The selected counter counts the number of counter 2 end events.
        CounterEventSource_Counter3End   //!<The selected counter counts the number of counter 3 end events.

    };

    //! Valid values for CounterResetSource
    enum CounterResetSourceEnums
    {
        CounterResetSource_Off,  //!<The counter reset is disabled.
        CounterResetSource_Software,  //!<The selected counter can be reset by a software command.
        CounterResetSource_Line1,  //!<The selected counter can be reset by a signal applied to Line 1.
        CounterResetSource_Line2,  //!<The selected counter can be reset by a signal applied to Line 2.
        CounterResetSource_Line3,  //!<The selected counter can be reset by a signal applied to Line 3.
        CounterResetSource_Line4,  //!<The selected counter can be reset by a signal applied to Line 4.
        CounterResetSource_Counter1End,  //!<The selected counter can be reset by a counter end 1 signal.
        CounterResetSource_Counter2End,  //!<The selected counter can be reset by a counter end 2 signal.
        CounterResetSource_Counter3End,  //!<The selected counter can be reset by a counter end 3 signal.
        CounterResetSource_Counter4End   //!<The selected counter can be reset by a counter end 4 signal.

    };

    //! Valid values for CounterResetActivation
    enum CounterResetActivationEnums
    {
        CounterResetActivation_RisingEdge,  //!<The counter resets on the rising edge of the signal.
        CounterResetActivation_FallingEdge,  //!<The counter resets on the falling edge of the signal.
        CounterResetActivation_AnyEdge,  //!<The counter resets on the falling or rising edge of the selected signal.
        CounterResetActivation_LevelHigh,  //!<The counter resets as long as the selected signal level is high.
        CounterResetActivation_LevelLow   //!<The counter resets as long as the selected signal level is low.

    };

    //! Valid values for UserSetSelector
    enum UserSetSelectorEnums
    {
        UserSetSelector_Default,  //!<The default factory set can be loaded.
        UserSetSelector_HighGain,  //!<The high gain factory set can be loaded.
        UserSetSelector_AutoFunctions,  //!<The factory set enabling auto functions can be loaded.
        UserSetSelector_Color,  //!<The factory set enabling color adjustments can be loaded.
        UserSetSelector_ColorRaw,  //!<The factory set disabling color adjustments can be loaded.
        UserSetSelector_UserSet1,  //!<User set 1 can be saved, loaded, or configured.
        UserSetSelector_UserSet2,  //!<User set 2 can be saved, loaded, or configured.
        UserSetSelector_UserSet3,  //!<User set 3 can be saved, loaded, or configured.
        UserSetSelector_LightMicroscopy   //!<

    };

    //! Valid values for UserSetDefault
    enum UserSetDefaultEnums
    {
        UserSetDefault_Default,  //!<The default factory set is set as the as the startup set.
        UserSetDefault_HighGain,  //!<The high gain factory set is set as the startup set.
        UserSetDefault_AutoFunctions,  //!<The factory set enabling auto functions is set as the startup set.
        UserSetDefault_Color,  //!<The factory set enabling color adjustments is set as the startup set.
        UserSetDefault_ColorRaw,  //!<The factory set disabling color adjustments is set as the startup set.
        UserSetDefault_UserSet1,  //!<User set 1 is set as the startup set.
        UserSetDefault_UserSet2,  //!<User set 2 is set as the startup set.
        UserSetDefault_UserSet3,  //!<User set 3 is set as the startup set.
        UserSetDefault_LightMicroscopy   //!<

    };

    //! Valid values for ChunkSelector
    enum ChunkSelectorEnums
    {
        ChunkSelector_Image,  //!<The image chunk can be enabled.
        ChunkSelector_Gain,  //!<The gain chunk can be enabled.
        ChunkSelector_ExposureTime,  //!<The exposure time chunk can be enabled.
        ChunkSelector_Timestamp,  //!<The timestamp chunk can be enabled.
        ChunkSelector_LineStatusAll,  //!<The line status all chunk can be enabled.
        ChunkSelector_CounterValue,  //!<The counter value chunk can be enabled.
        ChunkSelector_SequencerSetActive,  //!<The sequencer set active chunk can be enabled.
        ChunkSelector_PayloadCRC16   //!<The CRC checksum chunk can be enabled.

    };

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

    //! Valid values for EventSelector
    enum EventSelectorEnums
    {
        EventSelector_ExposureEnd,  //!<Event notifications for the exposure end event can be enabled.
        EventSelector_FrameStart,  //!<Event notifications for the frame start event can be enabled.
        EventSelector_FrameBurstStart,  //!<Event notifications for the frame burst start event can be enabled.
        EventSelector_FrameStartOvertrigger,  //!<Event notifications for the frame start overtrigger event can be enabled.
        EventSelector_FrameBurstStartOvertrigger,  //!<Event notifications for the frame burst start overtrigger event can be enabled.
        EventSelector_CriticalTemperature,  //!<Event notifications for the critical temperature event can be enabled.
        EventSelector_OverTemperature,  //!<Event notifications for the over temperature event can be enabled.
        EventSelector_FrameStartWait,  //!<Event notifications for the frame start wait event can be enabled.
        EventSelector_FrameBurstStartWait   //!<Event notifications for the frame burst start wait event can be enabled.

    };

    //! Valid values for EventNotification
    enum EventNotificationEnums
    {
        EventNotification_Off,  //!<Event notifications are disabled.
        EventNotification_On   //!<Event notifications are enabled.

    };

    //! Valid values for BslUSBSpeedMode
    enum BslUSBSpeedModeEnums
    {
        BslUSBSpeedMode_LowSpeed,  //!<The USB port is operating at Low Speed, as specified in the USB standard.
        BslUSBSpeedMode_FullSpeed,  //!<The USB port is operating at Full Speed, as specified in the USB standard.
        BslUSBSpeedMode_HighSpeed,  //!<The USB port is operating at High Speed, as specified in the USB standard.
        BslUSBSpeedMode_SuperSpeed   //!<The USB port is operating at SuperSpeed, as specified in the USB standard.

    };

    //! Valid values for DeviceScanType
    enum DeviceScanTypeEnums
    {
        DeviceScanType_Areascan,  //!<The device has an area scan sensor.
        DeviceScanType_Linescan   //!<The device has a line scan sensor.

    };

    //! Valid values for DeviceLinkThroughputLimitMode
    enum DeviceLinkThroughputLimitModeEnums
    {
        DeviceLinkThroughputLimitMode_Off,  //!<The device link throughput limit feature is disabled.
        DeviceLinkThroughputLimitMode_On   //!<The device link throughput limit feature is enabled.

    };

    //! Valid values for DeviceTemperatureSelector
    enum DeviceTemperatureSelectorEnums
    {
        DeviceTemperatureSelector_Coreboard,  //!<The temperature is measured on the core board.
        DeviceTemperatureSelector_Sensorboard,  //!<The temperature is measured on the sensor board.
        DeviceTemperatureSelector_Framegrabberboard   //!<The temperature is measured on the frame grabber board.

    };

    //! Valid values for TemperatureState
    enum TemperatureStateEnums
    {
        TemperatureState_Ok,  //!<Temperature is normal.
        TemperatureState_Critical,  //!<Temperature is critical.
        TemperatureState_Error   //!<Temperature state could not be retrieved.

    };

    //! Valid values for DeviceIndicatorMode
    enum DeviceIndicatorModeEnums
    {
        DeviceIndicatorMode_Inactive,  //!<Indicators are inactive (off).
        DeviceIndicatorMode_Active   //!<Indicators are active showing their respective status.

    };

    //! Valid values for UserDefinedValueSelector
    enum UserDefinedValueSelectorEnums
    {
        UserDefinedValueSelector_Value1,  //!<The user-defined value 1 can be set or read.
        UserDefinedValueSelector_Value2,  //!<The user-defined value 2 can be set or read.
        UserDefinedValueSelector_Value3,  //!<The user-defined value 3 can be set or read.
        UserDefinedValueSelector_Value4,  //!<The user-defined value 4 can be set or read.
        UserDefinedValueSelector_Value5   //!<The user-defined value 5 can be set or read.

    };

    //! Valid values for RemoveParameterLimitSelector
    enum RemoveParameterLimitSelectorEnums
    {
        RemoveParameterLimitSelector_Gain,  //!<The factory limits of the Gain parameter can be removed.
        RemoveParameterLimitSelector_BlackLevel,  //!<The factory limits of the BlackLevel parameter can be removed.
        RemoveParameterLimitSelector_ExposureTime,  //!<The factory limits of the ExposureTime parameter can be removed.
        RemoveParameterLimitSelector_AutoTargetValue,  //!<The factory limits of the AutoTargetValue parameter can be removed.
        RemoveParameterLimitSelector_ExposureOverhead   //!<The factory limits of the ExposureOverhead parameter can be removed.

    };

    //! Valid values for ExpertFeatureAccessSelector
    enum ExpertFeatureAccessSelectorEnums
    {
        ExpertFeatureAccessSelector_ExpertFeature1,  //!<Expert feature 1 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature2,  //!<Expert feature 2 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature3,  //!<Expert feature 3 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature4,  //!<Expert feature 4 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature5,  //!<Expert feature 5 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature6,  //!<Expert feature 6 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature7,  //!<Expert feature 7 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature8,  //!<Expert feature 8 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature9,  //!<Expert feature 9 can be configured.
        ExpertFeatureAccessSelector_ExpertFeature10   //!<Expert feature 10 can be configured.

    };

    //! Valid values for FileSelector
    enum FileSelectorEnums
    {
        FileSelector_UserData,  //!<The 'User Data' file is set.
        FileSelector_UserSet1,  //!<The 'User Set 1' file is set.
        FileSelector_UserSet2,  //!<The 'User Set 2' file is set.
        FileSelector_UserSet3,  //!<The 'User Set 3' file is set.
        FileSelector_UserGainShading1,  //!<The 'User Gain Shading 1' file is set.
        FileSelector_UserGainShading2,  //!<The 'User Gain Shading 2' file is set.
        FileSelector_UserOffsetShading1,  //!<The 'User Offset Shading 1' file is set.
        FileSelector_UserOffsetShading2,  //!<The 'User Offset Shading 2' file is set.
        FileSelector_ExpertFeature7File   //!<The 'Expert Feature 7 File' file is set.

    };

    //! Valid values for FileOperationSelector
    enum FileOperationSelectorEnums
    {
        FileOperationSelector_Open,  //!<The currently selected file can be opened.
        FileOperationSelector_Close,  //!<The currently selected file can be closed.
        FileOperationSelector_Read,  //!<The currently selected file can be read.
        FileOperationSelector_Write   //!<The currently selected file can be written.

    };

    //! Valid values for FileOpenMode
    enum FileOpenModeEnums
    {
        FileOpenMode_Read,  //!<Files are opened in read-only mode.
        FileOpenMode_Write   //!<Files are opened in write-only mode.

    };

    //! Valid values for FileOperationStatus
    enum FileOperationStatusEnums
    {
        FileOperationStatus_Success,  //!<The file operation was successful.
        FileOperationStatus_Failure   //!<The file operation has failed.

    };

    //! Valid values for TonalRangeEnable
    enum TonalRangeEnableEnums
    {
        TonalRangeEnable_Off,  //!<
        TonalRangeEnable_On   //!<

    };

    //! Valid values for TonalRangeAuto
    enum TonalRangeAutoEnums
    {
        TonalRangeAuto_Off,  //!<
        TonalRangeAuto_Once   //!<

    };

    //! Valid values for TonalRangeSelector
    enum TonalRangeSelectorEnums
    {
        TonalRangeSelector_Sum,  //!<
        TonalRangeSelector_Red,  //!<
        TonalRangeSelector_Green,  //!<
        TonalRangeSelector_Blue   //!<

    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************


    //! Basler USB3Vision camera interface
    class CUsbCameraParams_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS

            //! Constructor
        CUsbCameraParams_Params( void );

        //! Destructor
        ~CUsbCameraParams_Params( void );

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

    //! \name CameraOperationControl -
    //@{
    /*!
        \brief



        \b Visibility = Beginner


    */
        GENAPI_NAMESPACE::IEnumerationT<CameraOperationModeEnums >& CameraOperationMode;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Sets whether the sequencer can be used for image acquisition. Applies to: ace

            Sets whether the sequencer can be used for image acquisition.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<SequencerModeEnums >& SequencerMode;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Index number of the currently active sequencer set. Applies to: ace

            Index number of the current sequencer set, i.e. of the sequencer set whose parameter values are currently present in the active set.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SequencerSetActive;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Sets whether the sequencer can be configured. Applies to: ace

            Sets whether the sequencer can be configured.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<SequencerConfigurationModeEnums >& SequencerConfigurationMode;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Sequencer set that will be used with the first frame start trigger after SequencerMode was set to On. Applies to: ace

            Sequencer set that will be used with the first frame start trigger after SequencerMode was set to On. Only sequencer set 0 is available.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SequencerSetStart;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Sets a sequencer set by its index number. Applies to: ace

            Sets a sequencer set by its index number.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SequencerSetSelector;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Loads the parameter values of a sequencer set into the active set. Applies to: ace

            Loads the parameter values of a sequencer set into the active set. The sequencer set will then be the current set.

            \b Visibility = Expert

            \b Selected by : SequencerSetSelector

        */
        GENAPI_NAMESPACE::ICommand& SequencerSetLoad;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Saves the sequencer parameter values that are currently in the active set. Applies to: ace

            Saves the sequencer parameter values that are currently in the active set. The values will be saved for the sequencer set whose sequencer set index number is currently selected.

            \b Visibility = Expert

            \b Selected by : SequencerSetSelector

        */
        GENAPI_NAMESPACE::ICommand& SequencerSetSave;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Sets the sequencer path. Applies to: ace

            Sets the sequencer path.

            \b Visibility = Expert

            \b Selected by : SequencerSetSelector

        */
        GENAPI_NAMESPACE::IInteger& SequencerPathSelector;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Next sequencer set to follow after the current one. Applies to: ace

            Next sequencer set to follow after the current one.

            \b Visibility = Expert

            \b Selected by : SequencerSetSelector, SequencerPathSelector

        */
        GENAPI_NAMESPACE::IInteger& SequencerSetNext;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Sets the trigger source for sequencer set advance. Applies to: ace

            Sets the trigger source for sequencer set advance with the currently selected path.

            \b Visibility = Expert

            \b Selected by : SequencerSetSelector, SequencerPathSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<SequencerTriggerSourceEnums >& SequencerTriggerSource;

        //@}


        //! \name SequencerControl - Contains parameters to control the sequencer. Applies to: ace
        //@{
        /*!
            \brief Sets the effective logical level for sequencer set advance. Applies to: ace

            Sets the effective logical level for sequencer set advance. Currently, only LevelHigh is available.

            \b Visibility = Expert

            \b Selected by : SequencerSetSelector, SequencerPathSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<SequencerTriggerActivationEnums >& SequencerTriggerActivation;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Width of the camera's sensor in pixels. Applies to: ace, dart, pulse

            Width of the camera's sensor in pixels.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SensorWidth;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Height of the camera's sensor in pixels. Applies to: ace, dart, pulse

            Height of the camera's sensor in pixels.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& SensorHeight;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Maximum allowed width of the region of interest in pixels. Applies to: ace, dart, pulse

            Maximum allowed width of the region of interest in pixels. value takes into account any function that may limit the maximum width.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& WidthMax;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Maximum allowed height of the region of interest in pixels. Applies to: ace, dart, pulse

            Maximum allowed height of the region of interest in pixels. value takes into account any function that may limit the maximum height.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& HeightMax;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Width of the camera's region of interest in pixels. Applies to: ace, dart, pulse

            Width of the camera's region of interest in pixels. Depending on the camera model, the parameter can be set in different increments.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& Width;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Height of the camera's region of interest in pixels. Applies to: ace, dart, pulse

            Height of the camera's region of interest in pixels. Depending on the camera model, the parameter can be set in different increments.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& Height;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Horizontal offset from the left side of the sensor to the region of interest (in pixels). Applies to: ace, dart, pulse

            Horizontal offset from the left side of the sensor to the region of interest (in pixels).

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& OffsetX;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Vertical offset from the top of the sensor to the region of interest (in pixels). Applies to: ace, dart, pulse

            Vertical offset from the top of the sensor to the region of interest (in pixels).

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& OffsetY;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Enables the line pitch feature. Applies to: ace

            Enables the line pitch feature which aligns output image data to multiples of 4 bytes.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& LinePitchEnable;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Number of bytes separating the starting pixels of two consecutive lines. Applies to: ace

            Number of bytes separating the starting pixels of two consecutive lines. This feature is used to facilitate alignment of image data.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& LinePitch;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Enables horizontal centering of the image. Applies to: ace

            Enables horizontal centering of the image.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IBoolean& CenterX;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Enables vertical centering of the image. Applies to: ace

            Enables vertical centering of the image.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IBoolean& CenterY;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the binning horizontal mode. Applies to: ace, dart, pulse

            Sets the binning horizontal mode.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<BinningHorizontalModeEnums >& BinningHorizontalMode;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Number of adjacent horizontal pixels to be summed. Applies to: ace, dart, pulse

            Number of adjacent horizontal pixels to be summed. Their charges will be summed and reported out of the camera as a single pixel.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& BinningHorizontal;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the binning vertical mode. Applies to: ace, dart, pulse

            Sets the binning vertical mode.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<BinningVerticalModeEnums >& BinningVerticalMode;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Number of adjacent vertical pixels to be summed. Applies to: ace, dart, pulse

            Number of adjacent vertical pixels to be summed. Their charges will be summed and reported out of the camera as a single pixel.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& BinningVertical;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Horizontal decimation factor. Applies to: ace

            Horizontal decimation factor. It specifies the extent of horizontal sub-sampling of the acquired frame, i.e. it defines how many pixel columns are left out of transmission. This has the net effect of reducing the horizontal resolution (width) of the image by the specified decimation factor. A value of 1 indicates that the camera performs no horizontal decimation.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& DecimationHorizontal;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Vertical decimation factor. Applies to: ace

            Vertical decimation factor. It specifies the extent of vertical sub-sampling of the acquired frame, i.e. it defines how many rows are left out of transmission. This has the net effect of reducing the vertical resolution (height) of the image by the specified decimation factor. A value of 1 indicates that the camera performs no vertical decimation.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& DecimationVertical;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Horizontal scaling factor. Applies to: ace

            Horizontal scaling factor.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ScalingHorizontal;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Vertical scaling factor. Applies to: ace

            Vertical scaling factor.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ScalingVertical;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Enables horizontal mirroring of the image. Applies to: ace, dart, pulse

            Enables horizontal mirroring of the image. The pixel values for each line in a captured image will be swapped end-for-end about the line's center. You can use the ROI feature when using the reverse X feature. Note that the position of the ROI relative to the sensor remains the same.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& ReverseX;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Enables vertical mirroring of the image. Applies to: ace, dart, pulse

            Enables vertical mirroring of the image. The pixel values for each row in a captured image will be swapped end-for-end about the row's center. You can use the ROI feature when using the reverse Y feature. Note that the position of the ROI relative to the sensor remains the same.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IBoolean& ReverseY;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the format of the pixel data transmitted by the camera. Applies to: ace, dart, pulse

            Sets the format of the pixel data transmitted by the camera. The available pixel formats depend on the camera model and whether the camera is monochrome or color.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IEnumerationT<PixelFormatEnums >& PixelFormat;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Returns the depth of the pixel values in the image (in bits per pixel). Applies to: ace, dart, pulse

            Returns the depth of the pixel values in the image (in bits per pixel). The value will always be coherent with the pixel format setting.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<PixelSizeEnums >& PixelSize;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Returns the alignment of the camera's Bayer filter to the pixels in the acquired images. Applies to: ace, dart, pulse

            Returns the alignment of the camera's Bayer filter to the pixels in the acquired images.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<PixelColorFilterEnums >& PixelColorFilter;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Minimum possible pixel value that could be transferred from the camera. Applies to: ace, dart, pulse

            Minimum possible pixel value that could be transferred from the camera.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& PixelDynamicRangeMin;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Maximum possible pixel value that could be transferred from the camera. Applies to: ace, dart, pulse

            Maximum possible pixel value that could be transferred from the camera.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& PixelDynamicRangeMax;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the test image to display. Applies to: ace

            Sets the test image to display.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TestImageSelectorEnums >& TestImageSelector;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Holds all moving test images at their starting position. Applies to: ace

            Holds all moving test images at their starting position. All test images will be displayed at their starting positions and will stay fixed.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IBoolean& TestImageResetAndHold;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Selects the type of image test pattern that is generated by the device. Applies to: dart, pulse

            Selects the type of image test pattern that is generated by the device.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TestPatternEnums >& TestPattern;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets a ROI zone

            Sets a ROI zone to be enabled, configured, and assembled with other ROI zones.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ROIZoneSelectorEnums >& ROIZoneSelector;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Provides for enabling/disabling a ROI zone.

            Provides for enabling/disabling the previously set ROI zone.

            \b Visibility = Expert

            \b Selected by : ROIZoneSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ROIZoneModeEnums >& ROIZoneMode;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets a ROI zone size

            Sets the ROI zone 'thickness' (pixels, in direction of assembly) for the previously enabled ROI zone. Equivalent to Height for vertical zones.

            \b Visibility = Expert

            \b Selected by : ROIZoneSelector

        */
        GENAPI_NAMESPACE::IInteger& ROIZoneSize;

        //@}


        //! \name ImageFormatControl - Contains parameters to control the size of the acquired image and the format of the transferred pixel data. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets a ROI zone offset

            Sets the ROI zone offset [pixels, in direction of assembly] for the previously enabled ROI zone. Equivalent to OffsetY for vertical zones.

            \b Visibility = Expert

            \b Selected by : ROIZoneSelector

        */
        GENAPI_NAMESPACE::IInteger& ROIZoneOffset;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the operation mode of the gain auto function. Applies to: ace, dart, pulse

            Sets the operation mode of the gain auto function. The gain auto function automatically adjusts the gain within set limits until a target brightness value is reached.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<GainAutoEnums >& GainAuto;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the gain channel or tap to be adjusted. Applies to: ace, dart, pulse

            Sets the gain channel or tap to be adjusted. Once a gain channel or tap has been selected, all changes to the Gain parameter will be applied to the selected channel or tap.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<GainSelectorEnums >& GainSelector;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Value of the currently selected gain control in dB. Applies to: ace, dart, pulse

            Value of the currently selected gain control in dB.

            \b Visibility = Beginner


            \b Selected by : GainSelector

        */
        GENAPI_NAMESPACE::IFloat& Gain;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the black level channel or tap to be adjusted. Applies to: ace, dart, pulse

            Sets the black level channel or tap to be adjusted. Once a black level channel or tap has been selected, all changes to the BlackLevel parameter will be applied to the selected channel or tap.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BlackLevelSelectorEnums >& BlackLevelSelector;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Value of the currently selected black level channel or tap. Applies to: ace, dart, pulse

            Value of the currently selected black level channel or tap.

            \b Visibility = Beginner


            \b Selected by : BlackLevelSelector

        */
        GENAPI_NAMESPACE::IFloat& BlackLevel;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Gamma correction value. Applies to: ace, dart, pulse

            Gamma correction value. Gamma correction lets you modify the brightness of the pixel values to account for a non-linearity in the human perception of brightness.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& Gamma;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Returns the color space set for image acquisitions. Applies to: ace

            Returns the color space set for image acquisitions.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ColorSpaceEnums >& ColorSpace;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Value set for digital shift. Applies to: ace

            Value set for digital shift. When the parameter is set to zero, digital shift will be disabled. When the parameter is set to 1, 2, 3, or 4, digital shift will be set to shift by 1, shift by 2, shift by 3, or shift by 4 respectively.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& DigitalShift;

        //@}


        //! \name AnalogControl - Contains parameters to control the analog characteristics of the video signal. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the color space for image acquisition. Applies to: dart, pulse

            Sets the color space for image acquisition. Note that perception of brightness also depends on the gamma correction value set.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BslColorSpaceModeEnums >& BslColorSpaceMode;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the light source preset. Applies to: ace, dart, pulse

            Sets the light source preset. The colors in the image will be corrected so that they are appropriate for the selected light source.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IEnumerationT<LightSourcePresetEnums >& LightSourcePreset;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the operation mode of the balance white auto function. Applies to: ace, dart, pulse

            Sets the operation mode of the balance white auto function.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BalanceWhiteAutoEnums >& BalanceWhiteAuto;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the color channel to be adjusted for manual white balance. Applies to: ace, dart, pulse

            Sets the color channel to be adjusted for manual white balance. Once a color intensity has been selected, all changes to the balance ratio parameter will be applied to the selected color intensity.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BalanceRatioSelectorEnums >& BalanceRatioSelector;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Value of the currently selected balance ratio channel or tap. Applies to: ace, dart, pulse

            Value of the currently selected balance ratio channel or tap.

            \b Visibility = Beginner


            \b Selected by : BalanceRatioSelector

        */
        GENAPI_NAMESPACE::IFloat& BalanceRatio;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the color for color adjustment. Applies to: ace

            Sets the color for color adjustment.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ColorAdjustmentSelectorEnums >& ColorAdjustmentSelector;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Hue adjustment value for the currently selected color. Applies to: ace

            Hue adjustment value for the currently selected color.

            \b Visibility = Expert

            \b Selected by : ColorAdjustmentSelector

        */
        GENAPI_NAMESPACE::IFloat& ColorAdjustmentHue;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Saturation adjustment value for the currently selected color. Applies to: ace

            Saturation adjustment value for the currently selected color.

            \b Visibility = Expert

            \b Selected by : ColorAdjustmentSelector

        */
        GENAPI_NAMESPACE::IFloat& ColorAdjustmentSaturation;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the type of color transformation that will be performed. Applies to: ace

            Sets the type of color transformation that will be performed.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<ColorTransformationSelectorEnums >& ColorTransformationSelector;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the element to be entered in the color transformation matrix. Applies to: ace

            Sets the element to be entered in the color transformation matrix for custom color transformation. Note: Depending on the camera model, some elements in the color transformation matrix may be preset and can not be changed.

            \b Visibility = Guru

            \b Selected by : ColorTransformationSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<ColorTransformationValueSelectorEnums >& ColorTransformationValueSelector;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Transformation value for the selected element in the color transformation matrix. Applies to: ace

            Transformation value for the selected element in the color transformation matrix.

            \b Visibility = Guru

            \b Selected by : ColorTransformationSelector, ColorTransformationValueSelector

        */
        GENAPI_NAMESPACE::IFloat& ColorTransformationValue;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the contrast mode. Applies to: dart, pulse

            Sets the contrast mode. This specifies which type of contrast enhancement is used to adjust the contrast.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<BslContrastModeEnums >& BslContrastMode;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Amount of brightness to be applied. Applies to: dart, pulse

            Amount of brightness to be applied. This allows you to lighten or darken the entire image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& BslBrightness;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Amount of contrast to be applied. Applies to: dart, pulse

            Amount of contrast to be applied. The more contrast you apply, the more defined the difference between light and dark areas in the image will be.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& BslContrast;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Identifies outlier pixels and adjusts their intensity value. Applies to: dart, pulse

            Identifies pixels that have a significantly greater or lesser intensity value than its neighboring pixels (outlier pixels) and adjusts their intensity value.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<DefectPixelCorrectionModeEnums >& DefectPixelCorrectionMode;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Hue shift to be applied.

            Adjusting the hue shifts the colors of the image. This can be useful, e.g., for correcting minor color shifts or creating false-color images.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& BslHue;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Hue shift to be applied. Applies to: dart, pulse

            Hue shift to be applied. Adjusting the hue shifts the colors of the image. This can be useful, e.g., for correcting minor color shifts or creating false-color images.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& BslHueValue;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Saturation to be applied.

            Adjusting the saturation changes the intensity of the colors. A higher saturation, for example, makes colors easier to distinguish.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& BslSaturation;

        //@}


        //! \name ImageQualityControl - Contains parameters to optimize the image quality. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Amount of saturation to be applied. Applies to: dart, pulse

            Amount of saturation to be applied. Adjusting the saturation changes the colorfulness (intensity) of the colors. A higher saturation, for example, will make colors easier to distinguish.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& BslSaturationValue;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm. Applies to: ace
        //@{
        /*!
            \brief Sets the demosaicing mode. Applies to: ace

            Sets the demosaicing mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<DemosaicingModeEnums >& DemosaicingMode;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm. Applies to: ace
        //@{
        /*!
            \brief Enables Basler PGI image optimizations.

            Enables Basler PGI image optimizations.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<PgiModeEnums >& PgiMode;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm. Applies to: ace
        //@{
        /*!
            \brief Amount of noise reduction to apply. Applies to: ace

            Amount of noise reduction to apply. The higher the value, the less chroma noise will be visible in your images. However, too high values may result in image information loss. To enable this feature, the DemosaicingMode parameter must be set to BaslerPGI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& NoiseReduction;

        //@}


        //! \name PGIControl - Contains parameters related to the Basler PGI image optimization algorithm. Applies to: ace
        //@{
        /*!
            \brief Amount of sharpening to apply. Applies to: ace, dart, pulse

            Amount of sharpening to apply. The higher the sharpness, the more distinct the image subject's contours will be. However, too high values may result in image information loss. To enable this feature, the DemosaicingMode parameter must be set to BaslerPGI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& SharpnessEnhancement;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the image acquisition mode. Applies to: ace, dart, pulse

            Sets the image acquisition mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<AcquisitionModeEnums >& AcquisitionMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Starts the acquisition of images. Applies to: ace, dart, pulse

            Starts the acquisition of images. If the camera is set for single frame acquisition, it will start acquisition of one frame. If the camera is set for continuous frame acquisition, it will start continuous acquisition of frames.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::ICommand& AcquisitionStart;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Stops the acquisition of images. Applies to: ace, dart, pulse

            Stops the acquisition of images if the camera is set for continuous image acquisition and acquisition has been started.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::ICommand& AcquisitionStop;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the shutter mode. Applies to: ace

            Sets the shutter mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ShutterModeEnums >& ShutterMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the operation mode of the exposure auto function. Applies to: ace, dart, pulse

            Sets the operation mode of the exposure auto function. The exposure auto function automatically adjusts the exposure time within set limits until a target brightness value is reached.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureAutoEnums >& ExposureAuto;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureTimeModeEnums >& ExposureTimeMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the exposure mode. Applies to: ace, dart, pulse

            Sets the exposure mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureModeEnums >& ExposureMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Exposure time of the camera in microseconds. Applies to: ace, dart, pulse

            Exposure time of the camera in microseconds.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ExposureTime;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the exposure overlap time mode. Applies to: ace

            Sets the exposure overlap time mode.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ExposureOverlapTimeModeEnums >& ExposureOverlapTimeMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Maximum overlap of the sensor exposure with sensor readout in TriggerWidth exposure mode (in microseconds). Applies to: ace

            Maximum overlap of the sensor exposure with sensor readout in TriggerWidth exposure mode (in microseconds).

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& ExposureOverlapTimeMax;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the sensor readout mode. Applies to: ace

            Sets the sensor readout mode.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<SensorReadoutModeEnums >& SensorReadoutMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Number of frames to acquire for each FrameBurstStart trigger. Applies to: ace

            Number of frames to acquire for each FrameBurstStart trigger.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& AcquisitionBurstFrameCount;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the trigger type to be configured. Applies to: ace, dart, pulse

            Sets the trigger type to be configured. Once a trigger type has been set, all changes to the trigger settings will be applied to the selected trigger.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerSelectorEnums >& TriggerSelector;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the mode for the currently selected trigger. Applies to: ace, dart, pulse

            Sets the mode for the currently selected trigger.

            \b Visibility = Beginner


            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerModeEnums >& TriggerMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Generates a software trigger signal. Applies to: ace, dart, pulse

            Generates a software trigger signal. The software trigger signal will be used if the TriggerSource parameter is set to Software.

            \b Visibility = Expert

            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::ICommand& TriggerSoftware;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the signal source for the selected trigger. Applies to: ace, dart, pulse

            Sets the signal source for the selected trigger.

            \b Visibility = Expert

            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerSourceEnums >& TriggerSource;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the signal transition that activates the selected trigger. Applies to: ace, dart, pulse

            Sets the signal transition that activates the selected trigger.

            \b Visibility = Expert

            \b Selected by : TriggerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TriggerActivationEnums >& TriggerActivation;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Trigger delay time in microseconds. Applies to: ace

            Trigger delay time in microseconds. The delay is applied after the trigger reception and before effectively activating the trigger.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& TriggerDelay;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Enables setting the camera's acquisition frame rate to a specified value. Applies to: ace

            Enables setting the camera's acquisition frame rate to a specified value.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IBoolean& AcquisitionFrameRateEnable;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Acquisition frame rate of the camera in frames per second. Applies to: ace, dart, pulse

            Acquisition frame rate of the camera in frames per second.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IFloat& AcquisitionFrameRate;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Maximum allowed frame acquisition rate. Applies to: ace, dart, pulse

            Maximum allowed frame acquisition rate given the current camera settings (in frames per second).

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ResultingFrameRate;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sensor readout time given the current settings. Applies to: ace

            Sensor readout time given the current settings.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IFloat& SensorReadoutTime;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the acquisition status to be checked. Applies to: ace

            Sets the acquisition status to be checked. Once a status has been set, the status can be checked by reading the AcquisitionStatus parameter value.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<AcquisitionStatusSelectorEnums >& AcquisitionStatusSelector;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Indicates the status (true or false) of the currently selected acquisition signal. Applies to: ace

            Indicates the status (true or false) of the currently selected acquisition signal. acquisition signal can be selected using AcquisitionStatusSelector.

            \b Visibility = Expert

            \b Selected by : AcquisitionStatusSelector

        */
        GENAPI_NAMESPACE::IBoolean& AcquisitionStatus;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the shutter mode of the device. Applies to: dart, pulse

            Sets the shutter mode of the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<SensorShutterModeEnums >& SensorShutterMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Configures overlapping exposure and image readout. Applies to: dart, pulse

            Configures overlapping exposure and image readout.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<OverlapModeEnums >& OverlapMode;

        //@}


        //! \name AcquisitionControl - Contains parameters to control image acquisition and triggering. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the immediate trigger mode. Applies to: dart, pulse

            Sets the immediate trigger mode. If this mode is enabled, exposure starts immediately after triggering, but changes to image parameters become effective with a short delay, i.e., after one or more images have been acquired.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<BslImmediateTriggerModeEnums >& BslImmediateTriggerMode;

        //@}


        //! \name AutoFunctionControl - Contains parameters to configure the auto functions. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Target average brightness for the gain auto function and the exposure auto function. Applies to: ace, dart, pulse

            Target average brightness for the gain auto function and the exposure auto function.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoTargetBrightness;

        //@}


        //! \name AutoFunctionControl - Contains parameters to configure the auto functions. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets how gain and exposure time will be balanced when the device is making automatic adjustments. Applies to: ace, dart, pulse

            Sets how gain and exposure time will be balanced when the device is making automatic adjustments.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<AutoFunctionProfileEnums >& AutoFunctionProfile;

        //@}


        //! \name AutoFunctionControl - Contains parameters to configure the auto functions. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Lower limit for the Gain parameter when the gain auto function is active. Applies to: ace, dart, pulse

            Lower limit for the Gain parameter when the gain auto function is active.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoGainLowerLimit;

        //@}


        //! \name AutoFunctionControl - Contains parameters to configure the auto functions. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Upper limit for the Gain parameter when the gain auto function is active. Applies to: ace, dart, pulse

            Upper limit for the Gain parameter when the gain auto function is active.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoGainUpperLimit;

        //@}


        //! \name AutoFunctionControl - Contains parameters to configure the auto functions. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Lower limit for the ExposureTime parameter when the exposure auto function is active. Applies to: ace, dart, pulse

            Lower limit for the ExposureTime parameter when the exposure auto function is active.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoExposureTimeLowerLimit;

        //@}


        //! \name AutoFunctionControl - Contains parameters to configure the auto functions. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Upper limit for the ExposureTime parameter when the exposure auto function is active. Applies to: ace, dart, pulse

            Upper limit for the ExposureTime parameter when the exposure auto function is active.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoExposureTimeUpperLimit;

        //@}


        //! \name AutoFunctionControl - Contains parameters to configure the auto functions. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the backlight compensation. Applies to: dart, pulse

            Sets the backlight compensation that allows the camera to compensate for underexposure. This is done by excluding a given percentage of the brightest pixels in the image from the target average gray value calculations.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IFloat& AutoBacklightCompensation;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets which auto function ROI can be adjusted. Applies to: ace, dart, pulse

            Sets which auto function ROI can be adjusted.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<AutoFunctionROISelectorEnums >& AutoFunctionROISelector;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Width of the auto function ROI (in pixels). Applies to: ace, dart, pulse

            Width of the auto function ROI (in pixels).

            \b Visibility = Beginner


            \b Selected by : AutoFunctionROISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionROIWidth;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Height of the auto function ROI (in pixels). Applies to: ace, dart, pulse

            Height of the auto function ROI (in pixels).

            \b Visibility = Beginner


            \b Selected by : AutoFunctionROISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionROIHeight;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Horizontal offset from the left side of the sensor to the auto function ROI (in pixels). Applies to: ace, dart, pulse

            Horizontal offset from the left side of the sensor to the auto function ROI (in pixels).

            \b Visibility = Beginner


            \b Selected by : AutoFunctionROISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionROIOffsetX;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Vertical offset from the top of the sensor to the auto function ROI (in pixels). Applies to: ace, dart, pulse

            Vertical offset from the top of the sensor to the auto function ROI (in pixels).

            \b Visibility = Beginner


            \b Selected by : AutoFunctionROISelector

        */
        GENAPI_NAMESPACE::IInteger& AutoFunctionROIOffsetY;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Assigns the Gain Auto and the Exposure Auto functions to the currently selected auto function ROI. Applies to: ace, dart, pulse

            Assigns the Gain Auto and the Exposure Auto functions to the currently selected auto function ROI. For this parameter, Gain Auto and the Exposure Auto are considered as a single "brightness" auto function.

            \b Visibility = Beginner


            \b Selected by : AutoFunctionROISelector

        */
        GENAPI_NAMESPACE::IBoolean& AutoFunctionROIUseBrightness;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Assigns the Balance White auto function to the currently selected auto function ROI. Applies to: ace, dart, pulse

            Assigns the Balance White auto function to the currently selected auto function ROI.

            \b Visibility = Beginner


            \b Selected by : AutoFunctionROISelector

        */
        GENAPI_NAMESPACE::IBoolean& AutoFunctionROIUseWhiteBalance;

        //@}


        //! \name AutoFunctionROIControl - Contains parameters to configure the auto function ROIs. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Assigns the Tonal Range Auto auto function to the currently selected auto function ROI.

            Assigns the Tonal Range Auto auto function to the currently selected auto function ROI.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& AutoFunctionROIUseTonalRange;

        //@}


        //! \name AutoFunctionAOIControl - Contains parameters to configure the auto function AOIs.
        //@{
        /*!
            \brief This feature has been \b deprecated. Sets which auto function AOI can be adjusted.

            Sets which auto function AOI can be adjusted.

            \b Visibility = Invisible

        */

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif

        GENAPI_DEPRECATED_FEATURE
            GENAPI_NAMESPACE::IEnumerationT<AutoFunctionAOISelectorEnums >& AutoFunctionAOISelector;

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

    //@}


    //! \name AutoFunctionAOIControl - Contains parameters to configure the auto function AOIs.
    //@{
    /*!
        \brief This feature has been \b deprecated. Width of the auto function AOI (in pixels).

        Width of the auto function AOI (in pixels).

        \b Visibility = Invisible

        \b Selected by : AutoFunctionAOISelector

    */

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif

        GENAPI_DEPRECATED_FEATURE
            GENAPI_NAMESPACE::IInteger& AutoFunctionAOIWidth;

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

    //@}


    //! \name AutoFunctionAOIControl - Contains parameters to configure the auto function AOIs.
    //@{
    /*!
        \brief This feature has been \b deprecated. Height of the auto function AOI (in pixels).

        Height of the auto function AOI (in pixels).

        \b Visibility = Invisible

        \b Selected by : AutoFunctionAOISelector

    */

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif

        GENAPI_DEPRECATED_FEATURE
            GENAPI_NAMESPACE::IInteger& AutoFunctionAOIHeight;

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

    //@}


    //! \name AutoFunctionAOIControl - Contains parameters to configure the auto function AOIs.
    //@{
    /*!
        \brief This feature has been \b deprecated. Horizontal offset from the left side of the sensor to the auto function AOI (in pixels).

        Horizontal offset from the left side of the sensor to the auto function AOI (in pixels).

        \b Visibility = Invisible

        \b Selected by : AutoFunctionAOISelector

    */

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif

        GENAPI_DEPRECATED_FEATURE
            GENAPI_NAMESPACE::IInteger& AutoFunctionAOIOffsetX;

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

    //@}


    //! \name AutoFunctionAOIControl - Contains parameters to configure the auto function AOIs.
    //@{
    /*!
        \brief This feature has been \b deprecated. Vertical offset from the top of the sensor to the auto function AOI (in pixels).

        Vertical offset from the top of the sensor to the auto function AOI (in pixels).

        \b Visibility = Invisible

        \b Selected by : AutoFunctionAOISelector

    */

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif

        GENAPI_DEPRECATED_FEATURE
            GENAPI_NAMESPACE::IInteger& AutoFunctionAOIOffsetY;

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

    //@}


    //! \name AutoFunctionAOIControl - Contains parameters to configure the auto function AOIs.
    //@{
    /*!
        \brief This feature has been \b deprecated. Assigns the Gain Auto and the Exposure Auto functions to the currently selected auto function AOI.

        Assigns the Gain Auto and the Exposure Auto functions to the currently selected auto function AOI. For this parameter, Gain Auto and the Exposure Auto are considered as a single "brightness" auto function.

        \b Visibility = Invisible

        \b Selected by : AutoFunctionAOISelector

    */

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif

        GENAPI_DEPRECATED_FEATURE
            GENAPI_NAMESPACE::IBoolean& AutoFunctionAOIUseBrightness;

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

    //@}


    //! \name AutoFunctionAOIControl - Contains parameters to configure the auto function AOIs.
    //@{
    /*!
        \brief This feature has been \b deprecated. Assigns the Balance White auto function to the currently selected auto function AOI.

        Assigns the Balance White auto function to the currently selected auto function AOI.

        \b Visibility = Invisible

        \b Selected by : AutoFunctionAOISelector

    */

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif

        GENAPI_DEPRECATED_FEATURE
            GENAPI_NAMESPACE::IBoolean& AutoFunctionAOIUseWhiteBalance;

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

    //@}


    //! \name AutoTonalRangeControl -
    //@{
    /*!
        \brief



        \b Visibility = Beginner


    */
        GENAPI_NAMESPACE::IEnumerationT<AutoTonalRangeModeSelectorEnums >& AutoTonalRangeModeSelector;

        //@}


        //! \name AutoTonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<AutoTonalRangeAdjustmentSelectorEnums >& AutoTonalRangeAdjustmentSelector;

        //@}


        //! \name AutoTonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoTonalRangeThresholdBright;

        //@}


        //! \name AutoTonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& AutoTonalRangeThresholdDark;

        //@}


        //! \name AutoTonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& AutoTonalRangeTargetBright;

        //@}


        //! \name AutoTonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& AutoTonalRangeTargetDark;

        //@}


        //! \name LUTControl - Contains parameters to control the operation of the camera's lookup table (LUT). Applies to: ace
        //@{
        /*!
            \brief Sets the lookup table (LUT) to be configured. Applies to: ace

            Sets the lookup table (LUT) to be configured. Once a LUT has been selected, all changes to the LUT settings will be applied to the selected LUT.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<LUTSelectorEnums >& LUTSelector;

        //@}


        //! \name LUTControl - Contains parameters to control the operation of the camera's lookup table (LUT). Applies to: ace
        //@{
        /*!
            \brief Enables the selected lookup table (LUT). Applies to: ace

            Enables the selected lookup table (LUT).

            \b Visibility = Expert

            \b Selected by : LUTSelector

        */
        GENAPI_NAMESPACE::IBoolean& LUTEnable;

        //@}


        //! \name LUTControl - Contains parameters to control the operation of the camera's lookup table (LUT). Applies to: ace
        //@{
        /*!
            \brief Index of the LUT element to access. Applies to: ace

            Index of the LUT element to access.

            \b Visibility = Guru

            \b Selected by : LUTSelector

        */
        GENAPI_NAMESPACE::IInteger& LUTIndex;

        //@}


        //! \name LUTControl - Contains parameters to control the operation of the camera's lookup table (LUT). Applies to: ace
        //@{
        /*!
            \brief Value of the LUT element at the LUT index position. Applies to: ace

            Value of the LUT element at the LUT index position.

            \b Visibility = Guru

            \b Selected by : LUTSelector, LUTIndex

        */
        GENAPI_NAMESPACE::IInteger& LUTValue;

        //@}


        //! \name LUTControl - Contains parameters to control the operation of the camera's lookup table (LUT). Applies to: ace
        //@{
        /*!
            \brief A single register that lets you access all LUT coefficients. Applies to: ace

            A single register that lets you access all LUT coefficients without the need to repeatedly use the LUTIndex parameter.

            \b Visibility = Guru

            \b Selected by : LUTSelector

        */
        GENAPI_NAMESPACE::IRegister& LUTValueAll;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Sets the I/O line to be configured. Applies to: ace, dart

            Sets the I/O line to be configured. Once a line has been set, all changes to the line settings will be applied to the selected line.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<LineSelectorEnums >& LineSelector;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Sets the mode for the selected line. Applies to: ace, dart

            Sets the mode for the selected line. This controls whether the physical line is used to input or output a signal.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LineModeEnums >& LineMode;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Returns the electrical configuration of the currently selected line. Applies to: ace, dart

            Returns the electrical configuration of the currently selected line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LineFormatEnums >& LineFormat;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Returns the line logic of the currently selected line. Applies to: ace

            Returns the line logic of the currently selected line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LineLogicEnums >& LineLogic;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Sets the source signal for the currently selected line. Applies to: ace, dart

            Sets the source signal for the currently selected line. The currently selected line must be an output line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<LineSourceEnums >& LineSource;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Enables the signal inverter function for the currently selected input or output line. Applies to: ace, dart

            Enables the signal inverter function for the currently selected input or output line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IBoolean& LineInverter;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Value of the selected line debouncer time in microseconds. Applies to: ace, dart

            Value of the selected line debouncer time in microseconds.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IFloat& LineDebouncerTime;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Value for the minimum signal width of an output signal (in microseconds) . Applies to: ace

            Value for the minimum signal width of an output signal (in microseconds) .

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IFloat& LineMinimumOutputPulseWidth;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Indicates whether an overload condition was detected on the selected line. Applies to: ace

            Indicates whether an overload condition was detected on the selected line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IBoolean& LineOverloadStatus;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Resets the overload status of the selected line. Applies to: ace

            This command resets the overload status of the selected line. If the overload condition is still fulfilled, the overload status will be set again immediately.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::ICommand& LineOverloadReset;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Indicates the current logical state of the selected line. Applies to: ace, dart

            Indicates the current logical state of the selected line.

            \b Visibility = Beginner


            \b Selected by : LineSelector

        */
        GENAPI_NAMESPACE::IBoolean& LineStatus;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief A single bit field indicating the current logical state of all available line signals at time of polling. Applies to: ace, dart

            This integer value is a single bit field that indicates the current logical state of all available lines at time of polling.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& LineStatusAll;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Sets the user settable output signal to be configured. Applies to: ace, dart

            Sets the user settable output signal to be configured. Once a user settable output signal has been set, all changes to the user settable output signal settings will be applied to the selected user settable output signal.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<UserOutputSelectorEnums >& UserOutputSelector;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief Enables the selected user settable output line. Applies to: ace, dart

            Enables the selected user settable output line.

            \b Visibility = Beginner


            \b Selected by : UserOutputSelector

        */
        GENAPI_NAMESPACE::IBoolean& UserOutputValue;

        //@}


        //! \name DigitalIOControl - Contains parameters to control the operation of the camera's digital I/O lines. Applies to: ace, dart
        //@{
        /*!
            \brief A single bit field that sets the state of all user settable output signals in one access. Applies to: ace

            A single bit field that sets the state of all user settable output signals in one access.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& UserOutputValueAll;

        //@}


        //! \name SoftwareSignalControl - Contains parameters to control the software signal that can be used as a trigger signal. Applies to: ace
        //@{
        /*!
            \brief Sets the software signal to control. Applies to: ace

            Sets the software signal to control.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IEnumerationT<SoftwareSignalSelectorEnums >& SoftwareSignalSelector;

        //@}


        //! \name SoftwareSignalControl - Contains parameters to control the software signal that can be used as a trigger signal. Applies to: ace
        //@{
        /*!
            \brief Generates a signal that can be used as a software trigger. Applies to: ace

            Generates a signal that can be used as a software trigger.

            \b Visibility = Beginner

            \b Selected by : SoftwareSignalSelector

        */
        GENAPI_NAMESPACE::ICommand& SoftwareSignalPulse;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Sets the timer to be configured. Applies to: ace

            Sets the timer to be configured.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TimerSelectorEnums >& TimerSelector;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Duration of the currently selected timer in microseconds. Applies to: ace

            Duration of the currently selected timer in microseconds.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IFloat& TimerDuration;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Delay of the currently selected timer in microseconds. Applies to: ace

            Delay of the currently selected timer in microseconds.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IFloat& TimerDelay;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Sets the internal camera signal used to trigger the selected timer. Applies to: ace

            Sets the internal camera signal used to trigger the selected timer.

            \b Visibility = Beginner


            \b Selected by : TimerSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<TimerTriggerSourceEnums >& TimerTriggerSource;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Sets the counter to be configured. Applies to: ace

            Sets the counter to be configured. Once a counter has been set, all changes to the counter settings will be applied to this counter.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<CounterSelectorEnums >& CounterSelector;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Sets the event that increments the currently selected counter. Applies to: ace

            Sets the event that increments the currently selected counter.

            \b Visibility = Beginner


            \b Selected by : CounterSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<CounterEventSourceEnums >& CounterEventSource;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Sets the source signal that can reset the currently selected counter. Applies to: ace

            Sets the source signal that can reset the currently selected counter.

            \b Visibility = Beginner


            \b Selected by : CounterSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<CounterResetSourceEnums >& CounterResetSource;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Sets the signal on which the counter will be reset. Applies to: ace

            Sets the signal on which the counter will be reset.

            \b Visibility = Beginner


            \b Selected by : CounterSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<CounterResetActivationEnums >& CounterResetActivation;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Immediately resets the selected counter. Applies to: ace

            Immediately resets the selected counter. The counter starts counting immediately after the reset.

            \b Visibility = Beginner


            \b Selected by : CounterSelector

        */
        GENAPI_NAMESPACE::ICommand& CounterReset;

        //@}


        //! \name CounterAndTimerControl - Contains parameters to control the counters and timers. Applies to: ace
        //@{
        /*!
            \brief Duration (or number of events) before the CounterEnd event is generated. Applies to: ace

            Duration (or number of events) before the CounterEnd event is generated.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& CounterDuration;

        //@}


        //! \name UserSetControl - Contains parameters to set up user sets, also known as configuration sets. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the user set or the factory set to load, save or configure. Applies to: ace, dart, pulse

            Sets the user set or the factory set to load, save or configure.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<UserSetSelectorEnums >& UserSetSelector;

        //@}


        //! \name UserSetControl - Contains parameters to set up user sets, also known as configuration sets. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Loads the selected set into the camera's volatile memory and makes it the active configuration set. Applies to: ace, dart, pulse

            Loads the selected set into the camera's volatile memory and makes it the active configuration set. Once the selected set is loaded, the parameters in the selected set will control the camera.

            \b Visibility = Beginner


            \b Selected by : UserSetSelector

        */
        GENAPI_NAMESPACE::ICommand& UserSetLoad;

        //@}


        //! \name UserSetControl - Contains parameters to set up user sets, also known as configuration sets. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Saves the current active set into the selected user set. Applies to: ace, dart, pulse

            Saves the current active set into the selected user set.

            \b Visibility = Beginner


            \b Selected by : UserSetSelector

        */
        GENAPI_NAMESPACE::ICommand& UserSetSave;

        //@}


        //! \name UserSetControl - Contains parameters to set up user sets, also known as configuration sets. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the user set or the factory set to be used as the startup set. Applies to: ace, dart, pulse

            Sets the user set or the factory set to be used as the startup set. The startup set will be loaded as the active set whenever the camera is powered on or reset.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<UserSetDefaultEnums >& UserSetDefault;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Enables the chunk mode. Applies to: ace

            Enables the chunk mode.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IBoolean& ChunkModeActive;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Sets the chunk to be enabled. Applies to: ace

            Sets the chunk to be enabled. Once a chunk has been set, the chunk can be enabled using the ChunkEnable parameter.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<ChunkSelectorEnums >& ChunkSelector;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Enables the inclusion of the currently selected chunk in the payload data. Applies to: ace

            Enables the inclusion of the currently selected chunk in the payload data.

            \b Visibility = Beginner


            \b Selected by : ChunkSelector

        */
        GENAPI_NAMESPACE::IBoolean& ChunkEnable;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Sets which gain channel to retrieve chunk data from. Applies to: ace

            Sets which gain channel to retrieve chunk data from.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ChunkGainSelectorEnums >& ChunkGainSelector;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Gain used to acquire the image. Applies to: ace

            Gain used to acquire the image.

            \b Visibility = Beginner


            \b Selected by : ChunkGainSelector

        */
        GENAPI_NAMESPACE::IFloat& ChunkGain;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Exposure time used to acquire the image. Applies to: ace

            Exposure time used to acquire the image.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IFloat& ChunkExposureTime;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired. Applies to: ace

            Value of the timestamp when the image was acquired.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkTimestamp;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief A bit field that indicates the status of all of the camera's input and output lines when the image was acquired. Applies to: ace

            A bit field that indicates the status of all of the camera's input and output lines when the image was acquired

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkLineStatusAll;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Sets which counter to retrieve chunk data from. Applies to: ace

            Sets which counter to retrieve chunk data from.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<ChunkCounterSelectorEnums >& ChunkCounterSelector;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Value of the selected chunk counter. Applies to: ace

            Value of the selected chunk counter.

            \b Visibility = Beginner


            \b Selected by : ChunkCounterSelector

        */
        GENAPI_NAMESPACE::IInteger& ChunkCounterValue;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief Index of the active sequencer set. Applies to: ace

            Index of the active sequencer set.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkSequencerSetActive;

        //@}


        //! \name ChunkDataControl - Contains parameters to configure chunk data that is appended to the image data. Applies to: ace
        //@{
        /*!
            \brief CRC checksum of the acquired image. Applies to: ace

            CRC checksum of the acquired image. The checksum is calculated using all of the image data and all of the appended chunks except for the checksum itself.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& ChunkPayloadCRC16;

        //@}


        //! \name EventControl - Contains parameters to control events generated by the camera. Applies to: ace
        //@{
        /*!
            \brief Sets the event notification to be enabled. Applies to: ace

            Sets the event notification to be enabled. Once an event notification has been set, the notification can be enabled using the EventNotification parameter.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<EventSelectorEnums >& EventSelector;

        //@}


        //! \name EventControl - Contains parameters to control events generated by the camera. Applies to: ace
        //@{
        /*!
            \brief Enables event notifications for the currently selected event. Applies to: ace

            Enables event notifications for the currently selected event. The event can selected using the EventSelector parameter.

            \b Visibility = Expert

            \b Selected by : EventSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<EventNotificationEnums >& EventNotification;

        //@}


        //! \name EventControl - Contains parameters to control events generated by the camera. Applies to: ace
        //@{
        /*!
            \brief Generates an event test signal.

            Generates an event test signal.

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::ICommand& TriggerEventTest;

        //@}


        //! \name EventExposureEndData - Contains parameters available for an exposure end event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the exposure end event. Applies to: ace

            Unique identifier of the exposure end event. This parameter can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type of event that will be received.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventExposureEnd;

        //@}


        //! \name EventExposureEndData - Contains parameters available for an exposure end event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the exposure end event. Applies to: ace

            Time stamp of the exposure end event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventExposureEndTimestamp;

        //@}


        //! \name EventExposureEndData - Contains parameters available for an exposure end event. Applies to: ace
        //@{
        /*!
            \brief Frame ID of the exposure end event. Applies to: ace

            Frame ID of the exposure end event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventExposureEndFrameID;

        //@}


        //! \name EventFrameStartData - Contains parameters available for a frame start event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the frame start event. Applies to: ace

            Unique identifier of the frame start event. This feature can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type of event that will be received.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameStart;

        //@}


        //! \name EventFrameStartData - Contains parameters available for a frame start event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the frame start event. Applies to: ace

            Time stamp of the frame start event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameStartTimestamp;

        //@}


        //! \name EventFrameStartData - Contains parameters available for a frame start event. Applies to: ace
        //@{
        /*!
            \brief Frame ID of the frame start event. Applies to: ace

            Frame ID of the frame start event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameStartFrameID;

        //@}


        //! \name EventFrameBurstStartData - Contains parameters available for a frame burst start event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the frame burst start event. Applies to: ace

            Unique identifier of the frame burst start event. This feature can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type of event that will be received.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStart;

        //@}


        //! \name EventFrameBurstStartData - Contains parameters available for a frame burst start event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the frame burst start event. Applies to: ace

            Time stamp of the frame burst start event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStartTimestamp;

        //@}


        //! \name EventFrameBurstStartData - Contains parameters available for a frame burst start event. Applies to: ace
        //@{
        /*!
            \brief Frame ID of the frame burst start event. Applies to: ace

            Frame ID of the frame burst start event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStartFrameID;

        //@}


        //! \name EventFrameStartOvertriggerData - Contains parameters available for a frame start overtrigger event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the frame start overtrigger event. Applies to: ace

            Unique identifier of the frame start overtrigger event. This feature can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type of event that will be received.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameStartOvertrigger;

        //@}


        //! \name EventFrameStartOvertriggerData - Contains parameters available for a frame start overtrigger event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the frame start overtrigger event. Applies to: ace

            Time stamp of the frame start overtrigger event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameStartOvertriggerTimestamp;

        //@}


        //! \name EventFrameStartOvertriggerData - Contains parameters available for a frame start overtrigger event. Applies to: ace
        //@{
        /*!
            \brief Frame ID of the frame start overtrigger event. Applies to: ace

            Frame ID of the frame start overtrigger event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameStartOvertriggerFrameID;

        //@}


        //! \name EventFrameBurstStartOvertriggerData - Contains parameters available for a frame burst start overtrigger event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the frame burst start overtrigger event. Applies to: ace

            Unique identifier of the frame burst start overtrigger event. This feature can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type of event that will be received.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStartOvertrigger;

        //@}


        //! \name EventFrameBurstStartOvertriggerData - Contains parameters available for a frame burst start overtrigger event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the frame burst start overtrigger event. Applies to: ace

            Time stamp of the frame burst start overtrigger event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStartOvertriggerTimestamp;

        //@}


        //! \name EventFrameBurstStartOvertriggerData - Contains parameters available for a frame burst start overtrigger event. Applies to: ace
        //@{
        /*!
            \brief Frame ID of the frame burst start overtrigger event. Applies to: ace

            Frame ID of the frame burst start overtrigger event.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStartOvertriggerFrameID;

        //@}


        //! \name EventTestData - Contains parameters available for a test event.
        //@{
        /*!
            \brief Unique identifier of the test event.

            Unique identifier of the test event.

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& EventTest;

        //@}


        //! \name EventTestData - Contains parameters available for a test event.
        //@{
        /*!
            \brief Time stamp of the test event.

            Time stamp of the test event.

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& EventTestTimestamp;

        //@}


        //! \name EventCriticalTemperatureData - Contains parameters available for a critical temperature event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the critical temperature event. Applies to: ace

            Unique identifier of the critical temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventCriticalTemperature;

        //@}


        //! \name EventCriticalTemperatureData - Contains parameters available for a critical temperature event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the crititical temperature event. Applies to: ace

            Time stamp of the crititical temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventCriticalTemperatureTimestamp;

        //@}


        //! \name EventOverTemperatureData - Contains parameters available for an over temperature event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the over temperature event. Applies to: ace

            Unique identifier of the over temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventOverTemperature;

        //@}


        //! \name EventOverTemperatureData - Contains parameters available for an over temperature event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the over temperature event. Applies to: ace

            Time stamp of the over temperature event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventOverTemperatureTimestamp;

        //@}


        //! \name EventFrameStartWaitData - Contains parameters available for a frame start event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the frame start wait event. Applies to: ace

            Unique identifier of the frame start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventFrameStartWait;

        //@}


        //! \name EventFrameStartWaitData - Contains parameters available for a frame start event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the frame start wait event. Applies to: ace

            Time stamp of the frame start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventFrameStartWaitTimestamp;

        //@}


        //! \name EventFrameBurstStartWaitData - Contains parameters available for a frame burst start wait event. Applies to: ace
        //@{
        /*!
            \brief Unique identifier of the frame burst start wait event. Applies to: ace

            Unique identifier of the frame burst start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStartWait;

        //@}


        //! \name EventFrameBurstStartWaitData - Contains parameters available for a frame burst start wait event. Applies to: ace
        //@{
        /*!
            \brief Time stamp of the frame brust start wait event. Applies to: ace

            Time stamp of the frame brust start wait event.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& EventFrameBurstStartWaitTimestamp;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Size of the payload in bytes. Applies to: ace, dart, pulse

            Size of the payload in bytes. This is the total number of bytes sent in the payload.

            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IInteger& PayloadSize;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Returns the speed mode of the USB port. Applies to: ace, dart, pulse

            Returns the speed mode of the USB port.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IEnumerationT<BslUSBSpeedModeEnums >& BslUSBSpeedMode;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Expected size of a single payload transfer. Applies to: ace

            Expected size of a single payload transfer.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& SIPayloadTransferSize;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Expected number of payload transfers. Applies to: ace

            Expected number of payload transfers.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& SIPayloadTransferCount;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Size of the first final payload transfer. Applies to: ace

            Size of the first final payload transfer.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& SIPayloadFinalTransfer1Size;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Size of the second final payload transfer. Applies to: ace

            Size of the second final payload transfer.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& SIPayloadFinalTransfer2Size;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Test pending acknowledging time in milliseconds. Applies to: dart, pulse

            Test pending acknowledging time in milliseconds. On write, the device waits for this time period before acknowledging the write. If the time period is longer than the value in the Maximum Device Response Time register, the device must use PENDING_ACK during the completion of this request. On reads, the device returns the current value without any additional wait time.

            \b Visibility = Invisible

        */
        GENAPI_NAMESPACE::IInteger& TestPendingAck;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief

            This parameter takes effect only when the sequencer mode is set to On. The parameter can only be set when the sequencer configuration mode is set to On.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& PayloadTransferBlockDelay;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Payload Transfer Size. Applies to: dart, pulse

            Payload Transfer Size

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& PayloadTransferSize;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Payload Transfer Count. Applies to: dart, pulse

            Payload Transfer Count

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& PayloadTransferCount;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Payload Final Transfer 1 Size. Applies to: dart, pulse

            Payload Final Transfer 1 Size

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& PayloadFinalTransfer1Size;

        //@}


        //! \name TransportLayerControl - Contains parameters related to the USB3 Vision transport layer. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Payload Final Transfer 2 Size. Applies to: dart, pulse

            Payload Final Transfer 2 Size

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IInteger& PayloadFinalTransfer2Size;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Name of the device's vendor. Applies to: ace, dart, pulse

            Name of the device's vendor.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IString& DeviceVendorName;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Model name of the device. Applies to: ace, dart, pulse

            Model name of the device.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IString& DeviceModelName;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Additional information from the vendor about the camera. Applies to: ace, dart, pulse

            Additional information from the vendor about the camera.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IString& DeviceManufacturerInfo;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Version of the device. Applies to: ace, dart, pulse

            Version of the device.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IString& DeviceVersion;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Version of the device's firmware. Applies to: ace, dart, pulse

            Version of the device's firmware.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IString& DeviceFirmwareVersion;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Serial number of the device. Applies to: ace, dart, pulse

            Serial number of the device.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IString& DeviceSerialNumber;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief User-settable ID of the device. Applies to: ace, dart, pulse

            User-settable ID of the device.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IString& DeviceUserID;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Returns the scan type of the device's sensor (area or line scan). Applies to: ace, dart, pulse

            Returns the scan type of the device's sensor (area or line scan).

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IEnumerationT<DeviceScanTypeEnums >& DeviceScanType;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Latches the current timestamp counter and stores its value in TimestampLatchValue. Applies to: ace

            Latches the current timestamp counter and stores its value in TimestampLatchValue.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::ICommand& TimestampLatch;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Latched value of the timestamp counter. Applies to: ace

            Latched value of the timestamp counter.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& TimestampLatchValue;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets which link of the device to control. Applies to: ace, dart, pulse

            Sets which link of the device to control.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IInteger& DeviceLinkSelector;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Speed of transmission negotiated on the selected link. Applies to: ace, dart, pulse

            Speed of transmission negotiated on the selected link.

            \b Visibility = Expert

            \b Selected by : DeviceLinkSelector

        */
        GENAPI_NAMESPACE::IInteger& DeviceLinkSpeed;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Controls if the device link throughput limit is active. Applies to: ace, dart, pulse

            Controls if the device link throughput limit is active. When disabled, lower level throughput limit specific features are expected to control the throughput. When enabled, the device link throughput limit controls the overall throughput.

            \b Visibility = Beginner


            \b Selected by : DeviceLinkSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<DeviceLinkThroughputLimitModeEnums >& DeviceLinkThroughputLimitMode;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Value set to limit the maximum bandwidth of the data that will be streamed out by the device (in bytes per second). Applies to: ace, dart, pulse

            Value set to limit the maximum bandwidth of the data that will be streamed out by the device on the currently selected link (in bytes per second).

            \b Visibility = Beginner

            \b Selected by : DeviceLinkSelector

        */
        GENAPI_NAMESPACE::IInteger& DeviceLinkThroughputLimit;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Actual bandwidth the camera will use. Applies to: ace

            Actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data given the current camera settings.

            \b Visibility = Expert

            \b Selected by : DeviceLinkSelector

        */
        GENAPI_NAMESPACE::IInteger& DeviceLinkCurrentThroughput;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Sets the location within the device where the temperature will be measured. Applies to: ace

            Sets the location within the device where the temperature will be measured. Once a location has been set, the temperature can be retrieved using the DeviceTemperature parameter.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<DeviceTemperatureSelectorEnums >& DeviceTemperatureSelector;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Temperature of the selected location within the device (in degrees centigrade). Applies to: ace

            Temperature of the selected location within the device (in degrees centigrade). The temperature is measured at the location set by DeviceTemperatureSelector.

            \b Visibility = Expert

            \b Selected by : DeviceTemperatureSelector

        */
        GENAPI_NAMESPACE::IFloat& DeviceTemperature;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Returns the temperature state. Applies to: ace

            Returns the temperature state.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<TemperatureStateEnums >& TemperatureState;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Immediately resets and reboots the device. Applies to: ace, dart, pulse

            Immediately resets and reboots the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& DeviceReset;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Major version number of the SFNC specification that the device is compatible with. Applies to: ace, dart, pulse

            Major version number of the Standard Features Naming Convention (SFNC) specification that the device is compatible with.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& DeviceSFNCVersionMajor;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Minor version number of the SFNC specification that the device is compatible with. Applies to: ace, dart, pulse

            Minor version number of the Standard Features Naming Convention (SFNC) specification that the device is compatible with.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& DeviceSFNCVersionMinor;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Subminor version number of the SFNC specification that the device is compatible with. Applies to: ace, dart, pulse

            Subminor version number of the Standard Features Naming Convention (SFNC) specification that the device is compatible with.

            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& DeviceSFNCVersionSubMinor;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Controls the behavior of the indicators (such as LEDs) showing the status of the device. Applies to: dart

            Controls the behavior of the indicators (such as LEDs) showing the status of the device.

            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<DeviceIndicatorModeEnums >& DeviceIndicatorMode;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Prepare the device for registers streaming without checking for consistency. Applies to: dart, pulse

            Prepare the device for registers streaming without checking for consistency.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& DeviceRegistersStreamingStart;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief Announce the end of registers streaming. Applies to: dart, pulse

            Announce the end of registers streaming.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::ICommand& DeviceRegistersStreamingEnd;

        //@}


        //! \name DeviceControl - Contains parameters to retrieve information about the current device or to configure the current device. Applies to: ace, dart, pulse
        //@{
        /*!
            \brief



            \b Visibility = Beginner

        */
        GENAPI_NAMESPACE::IInteger& DeviceColorPipelineVersion;

        //@}


        //! \name UserDefinedValueControl - Contains parameters to set and get user defined values. Applies to: ace
        //@{
        /*!
            \brief Sets the user-defined value to set or read. Applies to: ace

            Sets the user-defined value to set or read.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<UserDefinedValueSelectorEnums >& UserDefinedValueSelector;

        //@}


        //! \name UserDefinedValueControl - Contains parameters to set and get user defined values. Applies to: ace
        //@{
        /*!
            \brief A user defined value. Applies to: ace

            A user defined value. value can serve as storage location for the camera user. It has no impact on the operation of the camera.

            \b Visibility = Guru

            \b Selected by : UserDefinedValueSelector

        */
        GENAPI_NAMESPACE::IInteger& UserDefinedValue;

        //@}


        //! \name RemoveParameterLimitControl - Contains parameters to remove the limits of camera parameters. Applies to: ace
        //@{
        /*!
            \brief Sets the parameter whose factory limits should be removed. Applies to: ace

            Sets the parameter whose factory limits should be removed. Once a parameter has been set, the factory limits can be removed using RemoveLimits.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<RemoveParameterLimitSelectorEnums >& RemoveParameterLimitSelector;

        //@}


        //! \name RemoveParameterLimitControl - Contains parameters to remove the limits of camera parameters. Applies to: ace
        //@{
        /*!
            \brief Removes the factory limit of the selected parameter. Applies to: ace

            Removes the factory limit of the selected parameter. When the factory limit is removed, the parameter can be set within extended limits. range of the extended limit is only dictated by the physical restrictions of the camera, such as the absolute limits of the camera's variable gain control.

            \b Visibility = Guru

            \b Selected by : RemoveParameterLimitSelector

        */
        GENAPI_NAMESPACE::IBoolean& RemoveParameterLimit;

        //@}


        //! \name ExpertFeatureAccess - Contains parameters that allow access to expert features. Applies to: ace
        //@{
        /*!
            \brief Sets the expert feature to be configured. Applies to: ace

            Sets the expert feature to be configured. Once a feature has been set, all changes made using the feature enable feature will be applied to this feature.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<ExpertFeatureAccessSelectorEnums >& ExpertFeatureAccessSelector;

        //@}


        //! \name ExpertFeatureAccess - Contains parameters that allow access to expert features. Applies to: ace
        //@{
        /*!
            \brief Key to access the selected expert feature. Applies to: ace

            Key to access the selected expert feature.

            \b Visibility = Guru

            \b Selected by : ExpertFeatureAccessSelector

        */
        GENAPI_NAMESPACE::IInteger& ExpertFeatureAccessKey;

        //@}


        //! \name ExpertFeatureAccess - Contains parameters that allow access to expert features. Applies to: ace
        //@{
        /*!
            \brief Enables the currently selected expert feature. Applies to: ace

            Enables the currently selected expert feature.

            \b Visibility = Guru

            \b Selected by : ExpertFeatureAccessSelector

        */
        GENAPI_NAMESPACE::IBoolean& ExpertFeatureEnable;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief Sets the target file in the device. Applies to: ace

            Sets the target file in the device.

            \b Visibility = Guru

        */
        GENAPI_NAMESPACE::IEnumerationT<FileSelectorEnums >& FileSelector;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief Sets the target operation for the currently selected file. Applies to: ace

            Sets the target operation for the currently selected file. After an operation has been selected, the operation can be executed using the FileOperationExecute command.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<FileOperationSelectorEnums >& FileOperationSelector;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief Sets the access mode in which a file is opened in the device. Applies to: ace

            Sets the access mode in which a file is opened in the device.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<FileOpenModeEnums >& FileOpenMode;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief Access buffer for file operations. Applies to: ace

            Access buffer for file operations.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IRegister& FileAccessBuffer;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief File access offset. Applies to: ace

            File access offset. Controls the mapping between the device file storage and the FileAccessBuffer.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IInteger& FileAccessOffset;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief File access length. Applies to: ace

            File access length. Controls the mapping between the device file storage and the FileAccessBuffer.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IInteger& FileAccessLength;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief Returns the file operation execution status. Applies to: ace

            Returns the file operation execution status.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IEnumerationT<FileOperationStatusEnums >& FileOperationStatus;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief File operation result. Applies to: ace

            File operation result. For read or write operations, the number of successfully read/written bytes is returned.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::IInteger& FileOperationResult;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief Size of the currently selected file in bytes. Applies to: ace

            Size of the currently selected file in bytes.

            \b Visibility = Guru

            \b Selected by : FileSelector

        */
        GENAPI_NAMESPACE::IInteger& FileSize;

        //@}


        //! \name FileAccessControl - Contains parameters to perform file operations. Applies to: ace
        //@{
        /*!
            \brief Executes the operation selected by FileOperationSelector. Applies to: ace

            Executes the operation selected by FileOperationSelector on the selected file.

            \b Visibility = Guru

            \b Selected by : FileSelector, FileOperationSelector

        */
        GENAPI_NAMESPACE::ICommand& FileOperationExecute;

        //@}


        //! \name TonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TonalRangeEnableEnums >& TonalRangeEnable;

        //@}


        //! \name TonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Beginner


        */
        GENAPI_NAMESPACE::IEnumerationT<TonalRangeAutoEnums >& TonalRangeAuto;

        //@}


        //! \name TonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

        */
        GENAPI_NAMESPACE::IEnumerationT<TonalRangeSelectorEnums >& TonalRangeSelector;

        //@}


        //! \name TonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeSourceBright;

        //@}


        //! \name TonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeSourceDark;

        //@}


        //! \name TonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeTargetBright;

        //@}


        //! \name TonalRangeControl -
        //@{
        /*!
            \brief



            \b Visibility = Expert

            \b Selected by : TonalRangeSelector

        */
        GENAPI_NAMESPACE::IInteger& TonalRangeTargetDark;

        //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
        CUsbCameraParams_Params( CUsbCameraParams_Params& );

        //! not implemented assignment operator
        CUsbCameraParams_Params& operator=( CUsbCameraParams_Params& );

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CUsbCameraParams_Params::CUsbCameraParams_Params( void )
        : CameraOperationMode( *new GENAPI_NAMESPACE::CEnumerationTRef<CameraOperationModeEnums>() )
        , SequencerMode( *new GENAPI_NAMESPACE::CEnumerationTRef<SequencerModeEnums>() )
        , SequencerSetActive( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequencerConfigurationMode( *new GENAPI_NAMESPACE::CEnumerationTRef<SequencerConfigurationModeEnums>() )
        , SequencerSetStart( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequencerSetSelector( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequencerSetLoad( *new GENAPI_NAMESPACE::CCommandRef() )
        , SequencerSetSave( *new GENAPI_NAMESPACE::CCommandRef() )
        , SequencerPathSelector( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequencerSetNext( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SequencerTriggerSource( *new GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>() )
        , SequencerTriggerActivation( *new GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>() )
        , SensorWidth( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SensorHeight( *new GENAPI_NAMESPACE::CIntegerRef() )
        , WidthMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , HeightMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Width( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Height( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OffsetX( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LinePitchEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LinePitch( *new GENAPI_NAMESPACE::CIntegerRef() )
        , CenterX( *new GENAPI_NAMESPACE::CBooleanRef() )
        , CenterY( *new GENAPI_NAMESPACE::CBooleanRef() )
        , BinningHorizontalMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>() )
        , BinningHorizontal( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BinningVerticalMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>() )
        , BinningVertical( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DecimationHorizontal( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DecimationVertical( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ScalingHorizontal( *new GENAPI_NAMESPACE::CFloatRef() )
        , ScalingVertical( *new GENAPI_NAMESPACE::CFloatRef() )
        , ReverseX( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ReverseY( *new GENAPI_NAMESPACE::CBooleanRef() )
        , PixelFormat( *new GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>() )
        , PixelSize( *new GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>() )
        , PixelColorFilter( *new GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>() )
        , PixelDynamicRangeMin( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PixelDynamicRangeMax( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TestImageSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>() )
        , TestImageResetAndHold( *new GENAPI_NAMESPACE::CBooleanRef() )
        , TestPattern( *new GENAPI_NAMESPACE::CEnumerationTRef<TestPatternEnums>() )
        , ROIZoneSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>() )
        , ROIZoneMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>() )
        , ROIZoneSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ROIZoneOffset( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GainAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>() )
        , GainSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>() )
        , Gain( *new GENAPI_NAMESPACE::CFloatRef() )
        , BlackLevelSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>() )
        , BlackLevel( *new GENAPI_NAMESPACE::CFloatRef() )
        , Gamma( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorSpace( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorSpaceEnums>() )
        , DigitalShift( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslColorSpaceMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BslColorSpaceModeEnums>() )
        , LightSourcePreset( *new GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>() )
        , BalanceWhiteAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>() )
        , BalanceRatioSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>() )
        , BalanceRatio( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorAdjustmentSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>() )
        , ColorAdjustmentHue( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorAdjustmentSaturation( *new GENAPI_NAMESPACE::CFloatRef() )
        , ColorTransformationSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>() )
        , ColorTransformationValueSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>() )
        , ColorTransformationValue( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslContrastMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>() )
        , BslBrightness( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslContrast( *new GENAPI_NAMESPACE::CFloatRef() )
        , DefectPixelCorrectionMode( *new GENAPI_NAMESPACE::CEnumerationTRef<DefectPixelCorrectionModeEnums>() )
        , BslHue( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslHueValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslSaturation( *new GENAPI_NAMESPACE::CFloatRef() )
        , BslSaturationValue( *new GENAPI_NAMESPACE::CFloatRef() )
        , DemosaicingMode( *new GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>() )
        , PgiMode( *new GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>() )
        , NoiseReduction( *new GENAPI_NAMESPACE::CFloatRef() )
        , SharpnessEnhancement( *new GENAPI_NAMESPACE::CFloatRef() )
        , AcquisitionMode( *new GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>() )
        , AcquisitionStart( *new GENAPI_NAMESPACE::CCommandRef() )
        , AcquisitionStop( *new GENAPI_NAMESPACE::CCommandRef() )
        , ShutterMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>() )
        , ExposureAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>() )
        , ExposureTimeMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>() )
        , ExposureMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>() )
        , ExposureTime( *new GENAPI_NAMESPACE::CFloatRef() )
        , ExposureOverlapTimeMode( *new GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>() )
        , ExposureOverlapTimeMax( *new GENAPI_NAMESPACE::CFloatRef() )
        , SensorReadoutMode( *new GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>() )
        , AcquisitionBurstFrameCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TriggerSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>() )
        , TriggerMode( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>() )
        , TriggerSoftware( *new GENAPI_NAMESPACE::CCommandRef() )
        , TriggerSource( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>() )
        , TriggerActivation( *new GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>() )
        , TriggerDelay( *new GENAPI_NAMESPACE::CFloatRef() )
        , AcquisitionFrameRateEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AcquisitionFrameRate( *new GENAPI_NAMESPACE::CFloatRef() )
        , ResultingFrameRate( *new GENAPI_NAMESPACE::CFloatRef() )
        , SensorReadoutTime( *new GENAPI_NAMESPACE::CFloatRef() )
        , AcquisitionStatusSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>() )
        , AcquisitionStatus( *new GENAPI_NAMESPACE::CBooleanRef() )
        , SensorShutterMode( *new GENAPI_NAMESPACE::CEnumerationTRef<SensorShutterModeEnums>() )
        , OverlapMode( *new GENAPI_NAMESPACE::CEnumerationTRef<OverlapModeEnums>() )
        , BslImmediateTriggerMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BslImmediateTriggerModeEnums>() )
        , AutoTargetBrightness( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoFunctionProfile( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>() )
        , AutoGainLowerLimit( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoGainUpperLimit( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoExposureTimeLowerLimit( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoExposureTimeUpperLimit( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoBacklightCompensation( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoFunctionROISelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionROISelectorEnums>() )
        , AutoFunctionROIWidth( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionROIHeight( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionROIOffsetX( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionROIOffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoFunctionROIUseBrightness( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AutoFunctionROIUseWhiteBalance( *new GENAPI_NAMESPACE::CBooleanRef() )
        , AutoFunctionROIUseTonalRange( *new GENAPI_NAMESPACE::CBooleanRef() )

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        , AutoFunctionAOISelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>() )

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        , AutoFunctionAOIWidth( *new GENAPI_NAMESPACE::CIntegerRef() )

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        , AutoFunctionAOIHeight( *new GENAPI_NAMESPACE::CIntegerRef() )

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        , AutoFunctionAOIOffsetX( *new GENAPI_NAMESPACE::CIntegerRef() )

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        , AutoFunctionAOIOffsetY( *new GENAPI_NAMESPACE::CIntegerRef() )

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        , AutoFunctionAOIUseBrightness( *new GENAPI_NAMESPACE::CBooleanRef() )

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        , AutoFunctionAOIUseWhiteBalance( *new GENAPI_NAMESPACE::CBooleanRef() )

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif
        , AutoTonalRangeModeSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>() )
        , AutoTonalRangeAdjustmentSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>() )
        , AutoTonalRangeThresholdBright( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoTonalRangeThresholdDark( *new GENAPI_NAMESPACE::CFloatRef() )
        , AutoTonalRangeTargetBright( *new GENAPI_NAMESPACE::CIntegerRef() )
        , AutoTonalRangeTargetDark( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LUTSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>() )
        , LUTEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LUTIndex( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LUTValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , LUTValueAll( *new GENAPI_NAMESPACE::CRegisterRef() )
        , LineSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>() )
        , LineMode( *new GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>() )
        , LineFormat( *new GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>() )
        , LineLogic( *new GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>() )
        , LineSource( *new GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>() )
        , LineInverter( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LineDebouncerTime( *new GENAPI_NAMESPACE::CFloatRef() )
        , LineMinimumOutputPulseWidth( *new GENAPI_NAMESPACE::CFloatRef() )
        , LineOverloadStatus( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LineOverloadReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , LineStatus( *new GENAPI_NAMESPACE::CBooleanRef() )
        , LineStatusAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , UserOutputSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>() )
        , UserOutputValue( *new GENAPI_NAMESPACE::CBooleanRef() )
        , UserOutputValueAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SoftwareSignalSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>() )
        , SoftwareSignalPulse( *new GENAPI_NAMESPACE::CCommandRef() )
        , TimerSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>() )
        , TimerDuration( *new GENAPI_NAMESPACE::CFloatRef() )
        , TimerDelay( *new GENAPI_NAMESPACE::CFloatRef() )
        , TimerTriggerSource( *new GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>() )
        , CounterSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>() )
        , CounterEventSource( *new GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>() )
        , CounterResetSource( *new GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>() )
        , CounterResetActivation( *new GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>() )
        , CounterReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , CounterDuration( *new GENAPI_NAMESPACE::CIntegerRef() )
        , UserSetSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>() )
        , UserSetLoad( *new GENAPI_NAMESPACE::CCommandRef() )
        , UserSetSave( *new GENAPI_NAMESPACE::CCommandRef() )
        , UserSetDefault( *new GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>() )
        , ChunkModeActive( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ChunkSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>() )
        , ChunkEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ChunkGainSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ChunkGainSelectorEnums>() )
        , ChunkGain( *new GENAPI_NAMESPACE::CFloatRef() )
        , ChunkExposureTime( *new GENAPI_NAMESPACE::CFloatRef() )
        , ChunkTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkLineStatusAll( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkCounterSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>() )
        , ChunkCounterValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkSequencerSetActive( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkPayloadCRC16( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>() )
        , EventNotification( *new GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>() )
        , TriggerEventTest( *new GENAPI_NAMESPACE::CCommandRef() )
        , EventExposureEnd( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventExposureEndTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventExposureEndFrameID( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStart( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStartTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStartFrameID( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStart( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStartTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStartFrameID( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStartOvertrigger( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStartOvertriggerTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStartOvertriggerFrameID( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStartOvertrigger( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStartOvertriggerTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStartOvertriggerFrameID( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventTest( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventTestTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventCriticalTemperature( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventCriticalTemperatureTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventOverTemperature( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventOverTemperatureTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStartWait( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameStartWaitTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStartWait( *new GENAPI_NAMESPACE::CIntegerRef() )
        , EventFrameBurstStartWaitTimestamp( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PayloadSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BslUSBSpeedMode( *new GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>() )
        , SIPayloadTransferSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SIPayloadTransferCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SIPayloadFinalTransfer1Size( *new GENAPI_NAMESPACE::CIntegerRef() )
        , SIPayloadFinalTransfer2Size( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TestPendingAck( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PayloadTransferBlockDelay( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PayloadTransferSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PayloadTransferCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PayloadFinalTransfer1Size( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PayloadFinalTransfer2Size( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceVendorName( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceModelName( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceManufacturerInfo( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceVersion( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceFirmwareVersion( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceSerialNumber( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceUserID( *new GENAPI_NAMESPACE::CStringRef() )
        , DeviceScanType( *new GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>() )
        , TimestampLatch( *new GENAPI_NAMESPACE::CCommandRef() )
        , TimestampLatchValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceLinkSelector( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceLinkSpeed( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceLinkThroughputLimitMode( *new GENAPI_NAMESPACE::CEnumerationTRef<DeviceLinkThroughputLimitModeEnums>() )
        , DeviceLinkThroughputLimit( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceLinkCurrentThroughput( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceTemperatureSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<DeviceTemperatureSelectorEnums>() )
        , DeviceTemperature( *new GENAPI_NAMESPACE::CFloatRef() )
        , TemperatureState( *new GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>() )
        , DeviceReset( *new GENAPI_NAMESPACE::CCommandRef() )
        , DeviceSFNCVersionMajor( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceSFNCVersionMinor( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceSFNCVersionSubMinor( *new GENAPI_NAMESPACE::CIntegerRef() )
        , DeviceIndicatorMode( *new GENAPI_NAMESPACE::CEnumerationTRef<DeviceIndicatorModeEnums>() )
        , DeviceRegistersStreamingStart( *new GENAPI_NAMESPACE::CCommandRef() )
        , DeviceRegistersStreamingEnd( *new GENAPI_NAMESPACE::CCommandRef() )
        , DeviceColorPipelineVersion( *new GENAPI_NAMESPACE::CIntegerRef() )
        , UserDefinedValueSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>() )
        , UserDefinedValue( *new GENAPI_NAMESPACE::CIntegerRef() )
        , RemoveParameterLimitSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>() )
        , RemoveParameterLimit( *new GENAPI_NAMESPACE::CBooleanRef() )
        , ExpertFeatureAccessSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>() )
        , ExpertFeatureAccessKey( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ExpertFeatureEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
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
        , TonalRangeEnable( *new GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>() )
        , TonalRangeAuto( *new GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>() )
        , TonalRangeSelector( *new GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>() )
        , TonalRangeSourceBright( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TonalRangeSourceDark( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TonalRangeTargetBright( *new GENAPI_NAMESPACE::CIntegerRef() )
        , TonalRangeTargetDark( *new GENAPI_NAMESPACE::CIntegerRef() )

    {
    }

    inline CUsbCameraParams_Params::~CUsbCameraParams_Params( void )
    {
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CameraOperationModeEnums>*> (&CameraOperationMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequencerModeEnums>*> (&SequencerMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetActive);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequencerConfigurationModeEnums>*> (&SequencerConfigurationMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetStart);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetSelector);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SequencerSetLoad);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SequencerSetSave);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequencerPathSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetNext);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SensorWidth);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SensorHeight);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&WidthMax);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&HeightMax);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Width);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&Height);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&OffsetX);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&OffsetY);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LinePitchEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LinePitch);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&CenterX);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&CenterY);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BinningHorizontal);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BinningVertical);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DecimationHorizontal);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DecimationVertical);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ScalingHorizontal);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ScalingVertical);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ReverseX);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ReverseY);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMin);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMax);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&TestImageResetAndHold);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TestPatternEnums>*> (&TestPattern);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneSize);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneOffset);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&Gain);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BlackLevel);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&Gamma);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorSpaceEnums>*> (&ColorSpace);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DigitalShift);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BslColorSpaceModeEnums>*> (&BslColorSpaceMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BalanceRatio);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentHue);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentSaturation);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ColorTransformationValue);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslBrightness);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslContrast);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DefectPixelCorrectionModeEnums>*> (&DefectPixelCorrectionMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslHue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&BslHueValue);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslSaturation);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&BslSaturationValue);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&NoiseReduction);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&SharpnessEnhancement);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStart);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStop);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ExposureTime);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ExposureOverlapTimeMax);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionBurstFrameCount);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&TriggerSoftware);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TriggerDelay);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionFrameRateEnable);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AcquisitionFrameRate);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ResultingFrameRate);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&SensorReadoutTime);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionStatus);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SensorShutterModeEnums>*> (&SensorShutterMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<OverlapModeEnums>*> (&OverlapMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BslImmediateTriggerModeEnums>*> (&BslImmediateTriggerMode);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoTargetBrightness);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoGainLowerLimit);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoGainUpperLimit);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeLowerLimit);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeUpperLimit);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoBacklightCompensation);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionROISelectorEnums>*> (&AutoFunctionROISelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIWidth);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIHeight);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIOffsetX);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIOffsetY);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionROIUseBrightness);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionROIUseWhiteBalance);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionROIUseTonalRange);

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector);

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIWidth);

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIHeight);

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetX);

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetY);

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUseBrightness);

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUseWhiteBalance);

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdBright);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdDark);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetBright);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetDark);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LUTEnable);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LUTIndex);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LUTValue);
        delete static_cast <GENAPI_NAMESPACE::CRegisterRef*> (&LUTValueAll);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LineInverter);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&LineDebouncerTime);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&LineMinimumOutputPulseWidth);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LineOverloadStatus);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&LineOverloadReset);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&LineStatus);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&LineStatusAll);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&UserOutputValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&UserOutputValueAll);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>*> (&SoftwareSignalSelector);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&SoftwareSignalPulse);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TimerDuration);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&TimerDelay);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&CounterReset);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&CounterDuration);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&UserSetLoad);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&UserSetSave);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ChunkModeActive);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ChunkEnable);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ChunkGainSelectorEnums>*> (&ChunkGainSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ChunkGain);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&ChunkExposureTime);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkLineStatusAll);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ChunkCounterSelectorEnums>*> (&ChunkCounterSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkCounterValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkSequencerSetActive);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ChunkPayloadCRC16);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&TriggerEventTest);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventExposureEnd);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventExposureEndTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventExposureEndFrameID);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStart);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartFrameID);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStart);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartFrameID);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartOvertrigger);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartOvertriggerTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartOvertriggerFrameID);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartOvertrigger);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartOvertriggerTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartOvertriggerFrameID);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventTest);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventTestTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventCriticalTemperature);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventCriticalTemperatureTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventOverTemperature);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventOverTemperatureTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartWait);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartWaitTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartWait);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartWaitTimestamp);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PayloadSize);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>*> (&BslUSBSpeedMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadTransferSize);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadTransferCount);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadFinalTransfer1Size);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadFinalTransfer2Size);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TestPendingAck);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PayloadTransferBlockDelay);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PayloadTransferSize);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PayloadTransferCount);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PayloadFinalTransfer1Size);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&PayloadFinalTransfer2Size);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceVendorName);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceModelName);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceManufacturerInfo);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceVersion);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceFirmwareVersion);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceSerialNumber);
        delete static_cast <GENAPI_NAMESPACE::CStringRef*> (&DeviceUserID);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&TimestampLatch);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TimestampLatchValue);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkSpeed);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DeviceLinkThroughputLimitModeEnums>*> (&DeviceLinkThroughputLimitMode);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkThroughputLimit);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkCurrentThroughput);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DeviceTemperatureSelectorEnums>*> (&DeviceTemperatureSelector);
        delete static_cast <GENAPI_NAMESPACE::CFloatRef*> (&DeviceTemperature);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&DeviceReset);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceSFNCVersionMajor);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceSFNCVersionMinor);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceSFNCVersionSubMinor);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<DeviceIndicatorModeEnums>*> (&DeviceIndicatorMode);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingStart);
        delete static_cast <GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingEnd);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&DeviceColorPipelineVersion);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&UserDefinedValue);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&RemoveParameterLimit);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&ExpertFeatureAccessKey);
        delete static_cast <GENAPI_NAMESPACE::CBooleanRef*> (&ExpertFeatureEnable);
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
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeEnableEnums>*> (&TonalRangeEnable);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeAutoEnums>*> (&TonalRangeAuto);
        delete static_cast <GENAPI_NAMESPACE::CEnumerationTRef<TonalRangeSelectorEnums>*> (&TonalRangeSelector);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeSourceBright);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeSourceDark);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeTargetBright);
        delete static_cast <GENAPI_NAMESPACE::CIntegerRef*> (&TonalRangeTargetDark);

    }

    inline void CUsbCameraParams_Params::_Initialize( GENAPI_NAMESPACE::INodeMap* _Ptr )
    {
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CameraOperationModeEnums>*> (&CameraOperationMode)->SetReference( _Ptr->GetNode( "CameraOperationMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CameraOperationModeEnums>*> (&CameraOperationMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CameraOperationModeEnums>*> (&CameraOperationMode)->SetEnumReference( CameraOperationMode_Standard, "Standard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CameraOperationModeEnums>*> (&CameraOperationMode)->SetEnumReference( CameraOperationMode_LongExposure, "LongExposure" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerModeEnums>*> (&SequencerMode)->SetReference( _Ptr->GetNode( "SequencerMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerModeEnums>*> (&SequencerMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerModeEnums>*> (&SequencerMode)->SetEnumReference( SequencerMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerModeEnums>*> (&SequencerMode)->SetEnumReference( SequencerMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetActive)->SetReference( _Ptr->GetNode( "SequencerSetActive" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerConfigurationModeEnums>*> (&SequencerConfigurationMode)->SetReference( _Ptr->GetNode( "SequencerConfigurationMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerConfigurationModeEnums>*> (&SequencerConfigurationMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerConfigurationModeEnums>*> (&SequencerConfigurationMode)->SetEnumReference( SequencerConfigurationMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerConfigurationModeEnums>*> (&SequencerConfigurationMode)->SetEnumReference( SequencerConfigurationMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetStart)->SetReference( _Ptr->GetNode( "SequencerSetStart" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetSelector)->SetReference( _Ptr->GetNode( "SequencerSetSelector" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SequencerSetLoad)->SetReference( _Ptr->GetNode( "SequencerSetLoad" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SequencerSetSave)->SetReference( _Ptr->GetNode( "SequencerSetSave" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequencerPathSelector)->SetReference( _Ptr->GetNode( "SequencerPathSelector" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SequencerSetNext)->SetReference( _Ptr->GetNode( "SequencerSetNext" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetReference( _Ptr->GetNode( "SequencerTriggerSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetNumEnums( 12 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_SoftwareSignal1, "SoftwareSignal1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_SoftwareSignal2, "SoftwareSignal2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_SoftwareSignal3, "SoftwareSignal3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_Counter1End, "Counter1End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_Counter2End, "Counter2End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_Counter3End, "Counter3End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_FrameStart, "FrameStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerSourceEnums>*> (&SequencerTriggerSource)->SetEnumReference( SequencerTriggerSource_FrameEnd, "FrameEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation)->SetReference( _Ptr->GetNode( "SequencerTriggerActivation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation)->SetEnumReference( SequencerTriggerActivation_RisingEdge, "RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation)->SetEnumReference( SequencerTriggerActivation_FallingEdge, "FallingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation)->SetEnumReference( SequencerTriggerActivation_AnyEdge, "AnyEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation)->SetEnumReference( SequencerTriggerActivation_LevelHigh, "LevelHigh" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SequencerTriggerActivationEnums>*> (&SequencerTriggerActivation)->SetEnumReference( SequencerTriggerActivation_LevelLow, "LevelLow" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SensorWidth)->SetReference( _Ptr->GetNode( "SensorWidth" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SensorHeight)->SetReference( _Ptr->GetNode( "SensorHeight" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&WidthMax)->SetReference( _Ptr->GetNode( "WidthMax" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&HeightMax)->SetReference( _Ptr->GetNode( "HeightMax" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Width)->SetReference( _Ptr->GetNode( "Width" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Height)->SetReference( _Ptr->GetNode( "Height" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OffsetX)->SetReference( _Ptr->GetNode( "OffsetX" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OffsetY)->SetReference( _Ptr->GetNode( "OffsetY" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LinePitchEnable)->SetReference( _Ptr->GetNode( "LinePitchEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LinePitch)->SetReference( _Ptr->GetNode( "LinePitch" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&CenterX)->SetReference( _Ptr->GetNode( "CenterX" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&CenterY)->SetReference( _Ptr->GetNode( "CenterY" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetReference( _Ptr->GetNode( "BinningHorizontalMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetEnumReference( BinningHorizontalMode_Sum, "Sum" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningHorizontalModeEnums>*> (&BinningHorizontalMode)->SetEnumReference( BinningHorizontalMode_Average, "Average" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BinningHorizontal)->SetReference( _Ptr->GetNode( "BinningHorizontal" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetReference( _Ptr->GetNode( "BinningVerticalMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetEnumReference( BinningVerticalMode_Sum, "Sum" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BinningVerticalModeEnums>*> (&BinningVerticalMode)->SetEnumReference( BinningVerticalMode_Average, "Average" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BinningVertical)->SetReference( _Ptr->GetNode( "BinningVertical" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DecimationHorizontal)->SetReference( _Ptr->GetNode( "DecimationHorizontal" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DecimationVertical)->SetReference( _Ptr->GetNode( "DecimationVertical" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ScalingHorizontal)->SetReference( _Ptr->GetNode( "ScalingHorizontal" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ScalingVertical)->SetReference( _Ptr->GetNode( "ScalingVertical" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ReverseX)->SetReference( _Ptr->GetNode( "ReverseX" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ReverseY)->SetReference( _Ptr->GetNode( "ReverseY" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetReference( _Ptr->GetNode( "PixelFormat" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetNumEnums( 28 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono8, "Mono8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono10, "Mono10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono10p, "Mono10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono12, "Mono12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_Mono12p, "Mono12p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR8, "BayerGR8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG8, "BayerRG8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB8, "BayerGB8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG8, "BayerBG8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR10, "BayerGR10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR10p, "BayerGR10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG10, "BayerRG10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG10p, "BayerRG10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB10, "BayerGB10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB10p, "BayerGB10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG10, "BayerBG10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG10p, "BayerBG10p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR12, "BayerGR12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGR12p, "BayerGR12p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG12, "BayerRG12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerRG12p, "BayerRG12p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB12, "BayerGB12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerGB12p, "BayerGB12p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG12, "BayerBG12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BayerBG12p, "BayerBG12p" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_RGB8, "RGB8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_BGR8, "BGR8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelFormatEnums>*> (&PixelFormat)->SetEnumReference( PixelFormat_YCbCr422_8, "YCbCr422_8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetReference( _Ptr->GetNode( "PixelSize" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp1, "Bpp1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp2, "Bpp2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp4, "Bpp4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp8, "Bpp8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp10, "Bpp10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp12, "Bpp12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp16, "Bpp16" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelSizeEnums>*> (&PixelSize)->SetEnumReference( PixelSize_Bpp24, "Bpp24" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetReference( _Ptr->GetNode( "PixelColorFilter" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_None, "None" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_BayerRG, "BayerRG" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_BayerGB, "BayerGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_BayerGR, "BayerGR" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PixelColorFilterEnums>*> (&PixelColorFilter)->SetEnumReference( PixelColorFilter_BayerBG, "BayerBG" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMin)->SetReference( _Ptr->GetNode( "PixelDynamicRangeMin" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PixelDynamicRangeMax)->SetReference( _Ptr->GetNode( "PixelDynamicRangeMax" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetReference( _Ptr->GetNode( "TestImageSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetNumEnums( 7 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage1, "Testimage1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage2, "Testimage2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage3, "Testimage3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage4, "Testimage4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage5, "Testimage5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestImageSelectorEnums>*> (&TestImageSelector)->SetEnumReference( TestImageSelector_Testimage6, "Testimage6" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&TestImageResetAndHold)->SetReference( _Ptr->GetNode( "TestImageResetAndHold" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestPatternEnums>*> (&TestPattern)->SetReference( _Ptr->GetNode( "TestPattern" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestPatternEnums>*> (&TestPattern)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestPatternEnums>*> (&TestPattern)->SetEnumReference( TestPattern_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestPatternEnums>*> (&TestPattern)->SetEnumReference( TestPattern_GreyDiagonalSawtooth8, "GreyDiagonalSawtooth8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TestPatternEnums>*> (&TestPattern)->SetEnumReference( TestPattern_ColorDiagonalSawtooth8, "ColorDiagonalSawtooth8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetReference( _Ptr->GetNode( "ROIZoneSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone0, "Zone0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone1, "Zone1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone2, "Zone2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone3, "Zone3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone4, "Zone4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone5, "Zone5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone6, "Zone6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneSelectorEnums>*> (&ROIZoneSelector)->SetEnumReference( ROIZoneSelector_Zone7, "Zone7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetReference( _Ptr->GetNode( "ROIZoneMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetEnumReference( ROIZoneMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ROIZoneModeEnums>*> (&ROIZoneMode)->SetEnumReference( ROIZoneMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneSize)->SetReference( _Ptr->GetNode( "ROIZoneSize" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ROIZoneOffset)->SetReference( _Ptr->GetNode( "ROIZoneOffset" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetReference( _Ptr->GetNode( "GainAuto" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetEnumReference( GainAuto_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetEnumReference( GainAuto_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainAutoEnums>*> (&GainAuto)->SetEnumReference( GainAuto_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetReference( _Ptr->GetNode( "GainSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_All, "All" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_DigitalAll, "DigitalAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<GainSelectorEnums>*> (&GainSelector)->SetEnumReference( GainSelector_AnalogAll, "AnalogAll" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&Gain)->SetReference( _Ptr->GetNode( "Gain" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetReference( _Ptr->GetNode( "BlackLevelSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BlackLevelSelectorEnums>*> (&BlackLevelSelector)->SetEnumReference( BlackLevelSelector_All, "All" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BlackLevel)->SetReference( _Ptr->GetNode( "BlackLevel" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&Gamma)->SetReference( _Ptr->GetNode( "Gamma" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorSpaceEnums>*> (&ColorSpace)->SetReference( _Ptr->GetNode( "ColorSpace" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorSpaceEnums>*> (&ColorSpace)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorSpaceEnums>*> (&ColorSpace)->SetEnumReference( ColorSpace_RGB, "RGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorSpaceEnums>*> (&ColorSpace)->SetEnumReference( ColorSpace_sRGB, "sRGB" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DigitalShift)->SetReference( _Ptr->GetNode( "DigitalShift" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslColorSpaceModeEnums>*> (&BslColorSpaceMode)->SetReference( _Ptr->GetNode( "BslColorSpaceMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslColorSpaceModeEnums>*> (&BslColorSpaceMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslColorSpaceModeEnums>*> (&BslColorSpaceMode)->SetEnumReference( BslColorSpaceMode_RGB, "RGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslColorSpaceModeEnums>*> (&BslColorSpaceMode)->SetEnumReference( BslColorSpaceMode_sRGB, "sRGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetReference( _Ptr->GetNode( "LightSourcePreset" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetNumEnums( 7 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetEnumReference( LightSourcePreset_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetEnumReference( LightSourcePreset_Daylight5000K, "Daylight5000K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetEnumReference( LightSourcePreset_Daylight6500K, "Daylight6500K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetEnumReference( LightSourcePreset_Tungsten2800K, "Tungsten2800K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetEnumReference( LightSourcePreset_MicroscopeLED4500K, "MicroscopeLED4500K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetEnumReference( LightSourcePreset_MicroscopeLED5500K, "MicroscopeLED5500K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LightSourcePresetEnums>*> (&LightSourcePreset)->SetEnumReference( LightSourcePreset_MicroscopeLED6000K, "MicroscopeLED6000K" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetReference( _Ptr->GetNode( "BalanceWhiteAuto" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetEnumReference( BalanceWhiteAuto_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetEnumReference( BalanceWhiteAuto_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceWhiteAutoEnums>*> (&BalanceWhiteAuto)->SetEnumReference( BalanceWhiteAuto_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetReference( _Ptr->GetNode( "BalanceRatioSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetEnumReference( BalanceRatioSelector_Red, "Red" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetEnumReference( BalanceRatioSelector_Green, "Green" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BalanceRatioSelectorEnums>*> (&BalanceRatioSelector)->SetEnumReference( BalanceRatioSelector_Blue, "Blue" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BalanceRatio)->SetReference( _Ptr->GetNode( "BalanceRatio" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetReference( _Ptr->GetNode( "ColorAdjustmentSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetNumEnums( 6 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Red, "Red" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Yellow, "Yellow" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Green, "Green" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Cyan, "Cyan" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Blue, "Blue" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorAdjustmentSelectorEnums>*> (&ColorAdjustmentSelector)->SetEnumReference( ColorAdjustmentSelector_Magenta, "Magenta" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentHue)->SetReference( _Ptr->GetNode( "ColorAdjustmentHue" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorAdjustmentSaturation)->SetReference( _Ptr->GetNode( "ColorAdjustmentSaturation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetReference( _Ptr->GetNode( "ColorTransformationSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetEnumReference( ColorTransformationSelector_RGBtoRGB, "RGBtoRGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetEnumReference( ColorTransformationSelector_RGBtoYUV, "RGBtoYUV" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationSelectorEnums>*> (&ColorTransformationSelector)->SetEnumReference( ColorTransformationSelector_YUVtoRGB, "YUVtoRGB" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetReference( _Ptr->GetNode( "ColorTransformationValueSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetNumEnums( 9 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain00, "Gain00" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain01, "Gain01" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain02, "Gain02" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain10, "Gain10" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain11, "Gain11" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain12, "Gain12" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain20, "Gain20" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain21, "Gain21" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ColorTransformationValueSelectorEnums>*> (&ColorTransformationValueSelector)->SetEnumReference( ColorTransformationValueSelector_Gain22, "Gain22" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ColorTransformationValue)->SetReference( _Ptr->GetNode( "ColorTransformationValue" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetReference( _Ptr->GetNode( "BslContrastMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetEnumReference( BslContrastMode_Linear, "Linear" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslContrastModeEnums>*> (&BslContrastMode)->SetEnumReference( BslContrastMode_SCurve, "SCurve" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslBrightness)->SetReference( _Ptr->GetNode( "BslBrightness" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslContrast)->SetReference( _Ptr->GetNode( "BslContrast" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefectPixelCorrectionModeEnums>*> (&DefectPixelCorrectionMode)->SetReference( _Ptr->GetNode( "DefectPixelCorrectionMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefectPixelCorrectionModeEnums>*> (&DefectPixelCorrectionMode)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefectPixelCorrectionModeEnums>*> (&DefectPixelCorrectionMode)->SetEnumReference( DefectPixelCorrectionMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefectPixelCorrectionModeEnums>*> (&DefectPixelCorrectionMode)->SetEnumReference( DefectPixelCorrectionMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DefectPixelCorrectionModeEnums>*> (&DefectPixelCorrectionMode)->SetEnumReference( DefectPixelCorrectionMode_StaticOnly, "StaticOnly" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslHue)->SetReference( _Ptr->GetNode( "BslHue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BslHueValue)->SetReference( _Ptr->GetNode( "BslHueValue" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslSaturation)->SetReference( _Ptr->GetNode( "BslSaturation" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&BslSaturationValue)->SetReference( _Ptr->GetNode( "BslSaturationValue" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetReference( _Ptr->GetNode( "DemosaicingMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetEnumReference( DemosaicingMode_Simple, "Simple" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DemosaicingModeEnums>*> (&DemosaicingMode)->SetEnumReference( DemosaicingMode_BaslerPGI, "BaslerPGI" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetReference( _Ptr->GetNode( "PgiMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetEnumReference( PgiMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<PgiModeEnums>*> (&PgiMode)->SetEnumReference( PgiMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&NoiseReduction)->SetReference( _Ptr->GetNode( "NoiseReduction" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&SharpnessEnhancement)->SetReference( _Ptr->GetNode( "SharpnessEnhancement" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetReference( _Ptr->GetNode( "AcquisitionMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetEnumReference( AcquisitionMode_SingleFrame, "SingleFrame" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionModeEnums>*> (&AcquisitionMode)->SetEnumReference( AcquisitionMode_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStart)->SetReference( _Ptr->GetNode( "AcquisitionStart" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&AcquisitionStop)->SetReference( _Ptr->GetNode( "AcquisitionStop" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetReference( _Ptr->GetNode( "ShutterMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetEnumReference( ShutterMode_Global, "Global" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetEnumReference( ShutterMode_Rolling, "Rolling" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ShutterModeEnums>*> (&ShutterMode)->SetEnumReference( ShutterMode_GlobalResetRelease, "GlobalResetRelease" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetReference( _Ptr->GetNode( "ExposureAuto" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetEnumReference( ExposureAuto_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetEnumReference( ExposureAuto_Once, "Once" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureAutoEnums>*> (&ExposureAuto)->SetEnumReference( ExposureAuto_Continuous, "Continuous" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetReference( _Ptr->GetNode( "ExposureTimeMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetEnumReference( ExposureTimeMode_Standard, "Standard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureTimeModeEnums>*> (&ExposureTimeMode)->SetEnumReference( ExposureTimeMode_UltraShort, "UltraShort" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetReference( _Ptr->GetNode( "ExposureMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetEnumReference( ExposureMode_Timed, "Timed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureModeEnums>*> (&ExposureMode)->SetEnumReference( ExposureMode_TriggerWidth, "TriggerWidth" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ExposureTime)->SetReference( _Ptr->GetNode( "ExposureTime" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetReference( _Ptr->GetNode( "ExposureOverlapTimeMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetEnumReference( ExposureOverlapTimeMode_Manual, "Manual" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExposureOverlapTimeModeEnums>*> (&ExposureOverlapTimeMode)->SetEnumReference( ExposureOverlapTimeMode_Automatic, "Automatic" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ExposureOverlapTimeMax)->SetReference( _Ptr->GetNode( "ExposureOverlapTimeMax" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetReference( _Ptr->GetNode( "SensorReadoutMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetEnumReference( SensorReadoutMode_Normal, "Normal" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorReadoutModeEnums>*> (&SensorReadoutMode)->SetEnumReference( SensorReadoutMode_Fast, "Fast" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AcquisitionBurstFrameCount)->SetReference( _Ptr->GetNode( "AcquisitionBurstFrameCount" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetReference( _Ptr->GetNode( "TriggerSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_FrameBurstStart, "FrameBurstStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSelectorEnums>*> (&TriggerSelector)->SetEnumReference( TriggerSelector_FrameStart, "FrameStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetReference( _Ptr->GetNode( "TriggerMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetEnumReference( TriggerMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerModeEnums>*> (&TriggerMode)->SetEnumReference( TriggerMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&TriggerSoftware)->SetReference( _Ptr->GetNode( "TriggerSoftware" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetReference( _Ptr->GetNode( "TriggerSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Software, "Software" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_SoftwareSignal1, "SoftwareSignal1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_SoftwareSignal2, "SoftwareSignal2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerSourceEnums>*> (&TriggerSource)->SetEnumReference( TriggerSource_SoftwareSignal3, "SoftwareSignal3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetReference( _Ptr->GetNode( "TriggerActivation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_RisingEdge, "RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_FallingEdge, "FallingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_AnyEdge, "AnyEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_LevelHigh, "LevelHigh" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TriggerActivationEnums>*> (&TriggerActivation)->SetEnumReference( TriggerActivation_LevelLow, "LevelLow" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TriggerDelay)->SetReference( _Ptr->GetNode( "TriggerDelay" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionFrameRateEnable)->SetReference( _Ptr->GetNode( "AcquisitionFrameRateEnable" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AcquisitionFrameRate)->SetReference( _Ptr->GetNode( "AcquisitionFrameRate" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&ResultingFrameRate)->SetReference( _Ptr->GetNode( "ResultingFrameRate" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&SensorReadoutTime)->SetReference( _Ptr->GetNode( "SensorReadoutTime" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetReference( _Ptr->GetNode( "AcquisitionStatusSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameBurstTriggerWait, "FrameBurstTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameBurstTriggerActive, "FrameBurstTriggerActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameBurstTriggerTransfer, "FrameBurstTriggerTransfer" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameTriggerWait, "FrameTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameActive, "FrameActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_FrameTransfer, "FrameTransfer" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_ExposureActive, "ExposureActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AcquisitionStatusSelectorEnums>*> (&AcquisitionStatusSelector)->SetEnumReference( AcquisitionStatusSelector_AcquisitionIdle, "AcquisitionIdle" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AcquisitionStatus)->SetReference( _Ptr->GetNode( "AcquisitionStatus" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorShutterModeEnums>*> (&SensorShutterMode)->SetReference( _Ptr->GetNode( "SensorShutterMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorShutterModeEnums>*> (&SensorShutterMode)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorShutterModeEnums>*> (&SensorShutterMode)->SetEnumReference( SensorShutterMode_Global, "Global" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorShutterModeEnums>*> (&SensorShutterMode)->SetEnumReference( SensorShutterMode_Rolling, "Rolling" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SensorShutterModeEnums>*> (&SensorShutterMode)->SetEnumReference( SensorShutterMode_GlobalReset, "GlobalReset" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OverlapModeEnums>*> (&OverlapMode)->SetReference( _Ptr->GetNode( "OverlapMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OverlapModeEnums>*> (&OverlapMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OverlapModeEnums>*> (&OverlapMode)->SetEnumReference( OverlapMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OverlapModeEnums>*> (&OverlapMode)->SetEnumReference( OverlapMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslImmediateTriggerModeEnums>*> (&BslImmediateTriggerMode)->SetReference( _Ptr->GetNode( "BslImmediateTriggerMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslImmediateTriggerModeEnums>*> (&BslImmediateTriggerMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslImmediateTriggerModeEnums>*> (&BslImmediateTriggerMode)->SetEnumReference( BslImmediateTriggerMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslImmediateTriggerModeEnums>*> (&BslImmediateTriggerMode)->SetEnumReference( BslImmediateTriggerMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoTargetBrightness)->SetReference( _Ptr->GetNode( "AutoTargetBrightness" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetReference( _Ptr->GetNode( "AutoFunctionProfile" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetNumEnums( 7 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_MinimizeGain, "MinimizeGain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_MinimizeExposureTime, "MinimizeExposureTime" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_Smart, "Smart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_AntiFlicker50Hz, "AntiFlicker50Hz" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_AntiFlicker60Hz, "AntiFlicker60Hz" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_MinimizeGainQuick, "MinimizeGainQuick" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionProfileEnums>*> (&AutoFunctionProfile)->SetEnumReference( AutoFunctionProfile_MinimizeExposureTimeQuick, "MinimizeExposureTimeQuick" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoGainLowerLimit)->SetReference( _Ptr->GetNode( "AutoGainLowerLimit" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoGainUpperLimit)->SetReference( _Ptr->GetNode( "AutoGainUpperLimit" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeLowerLimit)->SetReference( _Ptr->GetNode( "AutoExposureTimeLowerLimit" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoExposureTimeUpperLimit)->SetReference( _Ptr->GetNode( "AutoExposureTimeUpperLimit" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoBacklightCompensation)->SetReference( _Ptr->GetNode( "AutoBacklightCompensation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionROISelectorEnums>*> (&AutoFunctionROISelector)->SetReference( _Ptr->GetNode( "AutoFunctionROISelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionROISelectorEnums>*> (&AutoFunctionROISelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionROISelectorEnums>*> (&AutoFunctionROISelector)->SetEnumReference( AutoFunctionROISelector_ROI1, "ROI1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionROISelectorEnums>*> (&AutoFunctionROISelector)->SetEnumReference( AutoFunctionROISelector_ROI2, "ROI2" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIWidth)->SetReference( _Ptr->GetNode( "AutoFunctionROIWidth" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIHeight)->SetReference( _Ptr->GetNode( "AutoFunctionROIHeight" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIOffsetX)->SetReference( _Ptr->GetNode( "AutoFunctionROIOffsetX" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionROIOffsetY)->SetReference( _Ptr->GetNode( "AutoFunctionROIOffsetY" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionROIUseBrightness)->SetReference( _Ptr->GetNode( "AutoFunctionROIUseBrightness" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionROIUseWhiteBalance)->SetReference( _Ptr->GetNode( "AutoFunctionROIUseWhiteBalance" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionROIUseTonalRange)->SetReference( _Ptr->GetNode( "AutoFunctionROIUseTonalRange" ) );

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetReference( _Ptr->GetNode( "AutoFunctionAOISelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI1, "AOI1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoFunctionAOISelectorEnums>*> (&AutoFunctionAOISelector)->SetEnumReference( AutoFunctionAOISelector_AOI2, "AOI2" );
#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIWidth)->SetReference( _Ptr->GetNode( "AutoFunctionAOIWidth" ) );

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIHeight)->SetReference( _Ptr->GetNode( "AutoFunctionAOIHeight" ) );

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetX)->SetReference( _Ptr->GetNode( "AutoFunctionAOIOffsetX" ) );

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoFunctionAOIOffsetY)->SetReference( _Ptr->GetNode( "AutoFunctionAOIOffsetY" ) );

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUseBrightness)->SetReference( _Ptr->GetNode( "AutoFunctionAOIUseBrightness" ) );

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4996) // name has been marked as deprecated
#endif
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&AutoFunctionAOIUseWhiteBalance)->SetReference( _Ptr->GetNode( "AutoFunctionAOIUseWhiteBalance" ) );

#if defined (_MSC_VER)
#   pragma warning(pop)
#endif
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetReference( _Ptr->GetNode( "AutoTonalRangeModeSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetEnumReference( AutoTonalRangeModeSelector_ColorAndContrast, "ColorAndContrast" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetEnumReference( AutoTonalRangeModeSelector_Color, "Color" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeModeSelectorEnums>*> (&AutoTonalRangeModeSelector)->SetEnumReference( AutoTonalRangeModeSelector_Contrast, "Contrast" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetReference( _Ptr->GetNode( "AutoTonalRangeAdjustmentSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetEnumReference( AutoTonalRangeAdjustmentSelector_DarkAndBright, "DarkAndBright" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetEnumReference( AutoTonalRangeAdjustmentSelector_Bright, "Bright" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<AutoTonalRangeAdjustmentSelectorEnums>*> (&AutoTonalRangeAdjustmentSelector)->SetEnumReference( AutoTonalRangeAdjustmentSelector_Dark, "Dark" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdBright)->SetReference( _Ptr->GetNode( "AutoTonalRangeThresholdBright" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&AutoTonalRangeThresholdDark)->SetReference( _Ptr->GetNode( "AutoTonalRangeThresholdDark" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetBright)->SetReference( _Ptr->GetNode( "AutoTonalRangeTargetBright" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AutoTonalRangeTargetDark)->SetReference( _Ptr->GetNode( "AutoTonalRangeTargetDark" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector)->SetReference( _Ptr->GetNode( "LUTSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LUTSelectorEnums>*> (&LUTSelector)->SetEnumReference( LUTSelector_Luminance, "Luminance" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LUTEnable)->SetReference( _Ptr->GetNode( "LUTEnable" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LUTIndex)->SetReference( _Ptr->GetNode( "LUTIndex" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LUTValue)->SetReference( _Ptr->GetNode( "LUTValue" ) );
        static_cast<GENAPI_NAMESPACE::CRegisterRef*> (&LUTValueAll)->SetReference( _Ptr->GetNode( "LUTValueAll" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetReference( _Ptr->GetNode( "LineSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSelectorEnums>*> (&LineSelector)->SetEnumReference( LineSelector_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetReference( _Ptr->GetNode( "LineMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetEnumReference( LineMode_Input, "Input" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineModeEnums>*> (&LineMode)->SetEnumReference( LineMode_Output, "Output" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetReference( _Ptr->GetNode( "LineFormat" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetNumEnums( 7 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_NoConnect, "NoConnect" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_TriState, "TriState" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_TTL, "TTL" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_LVDS, "LVDS" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_RS422, "RS422" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_OptoCoupled, "OptoCoupled" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineFormatEnums>*> (&LineFormat)->SetEnumReference( LineFormat_LVTTL, "LVTTL" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetReference( _Ptr->GetNode( "LineLogic" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetEnumReference( LineLogic_Positive, "Positive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineLogicEnums>*> (&LineLogic)->SetEnumReference( LineLogic_Negative, "Negative" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetReference( _Ptr->GetNode( "LineSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetNumEnums( 11 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_ExposureActive, "ExposureActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_FrameTriggerWait, "FrameTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_FrameBurstTriggerWait, "FrameBurstTriggerWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_Timer1Active, "Timer1Active" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput0, "UserOutput0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput1, "UserOutput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput2, "UserOutput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput3, "UserOutput3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_FlashWindow, "FlashWindow" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<LineSourceEnums>*> (&LineSource)->SetEnumReference( LineSource_UserOutput4, "UserOutput4" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LineInverter)->SetReference( _Ptr->GetNode( "LineInverter" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&LineDebouncerTime)->SetReference( _Ptr->GetNode( "LineDebouncerTime" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&LineMinimumOutputPulseWidth)->SetReference( _Ptr->GetNode( "LineMinimumOutputPulseWidth" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LineOverloadStatus)->SetReference( _Ptr->GetNode( "LineOverloadStatus" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&LineOverloadReset)->SetReference( _Ptr->GetNode( "LineOverloadReset" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&LineStatus)->SetReference( _Ptr->GetNode( "LineStatus" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&LineStatusAll)->SetReference( _Ptr->GetNode( "LineStatusAll" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetReference( _Ptr->GetNode( "UserOutputSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput0, "UserOutput0" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput1, "UserOutput1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput2, "UserOutput2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserOutputSelectorEnums>*> (&UserOutputSelector)->SetEnumReference( UserOutputSelector_UserOutput3, "UserOutput3" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&UserOutputValue)->SetReference( _Ptr->GetNode( "UserOutputValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&UserOutputValueAll)->SetReference( _Ptr->GetNode( "UserOutputValueAll" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>*> (&SoftwareSignalSelector)->SetReference( _Ptr->GetNode( "SoftwareSignalSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>*> (&SoftwareSignalSelector)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>*> (&SoftwareSignalSelector)->SetEnumReference( SoftwareSignalSelector_SoftwareSignal1, "SoftwareSignal1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>*> (&SoftwareSignalSelector)->SetEnumReference( SoftwareSignalSelector_SoftwareSignal2, "SoftwareSignal2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>*> (&SoftwareSignalSelector)->SetEnumReference( SoftwareSignalSelector_SoftwareSignal3, "SoftwareSignal3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<SoftwareSignalSelectorEnums>*> (&SoftwareSignalSelector)->SetEnumReference( SoftwareSignalSelector_SoftwareSignal4, "SoftwareSignal4" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&SoftwareSignalPulse)->SetReference( _Ptr->GetNode( "SoftwareSignalPulse" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetReference( _Ptr->GetNode( "TimerSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetNumEnums( 1 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerSelectorEnums>*> (&TimerSelector)->SetEnumReference( TimerSelector_Timer1, "Timer1" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TimerDuration)->SetReference( _Ptr->GetNode( "TimerDuration" ) );
        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&TimerDelay)->SetReference( _Ptr->GetNode( "TimerDelay" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetReference( _Ptr->GetNode( "TimerTriggerSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetEnumReference( TimerTriggerSource_ExposureStart, "ExposureStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TimerTriggerSourceEnums>*> (&TimerTriggerSource)->SetEnumReference( TimerTriggerSource_FlashWindowStart, "FlashWindowStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetReference( _Ptr->GetNode( "CounterSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetEnumReference( CounterSelector_Counter1, "Counter1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterSelectorEnums>*> (&CounterSelector)->SetEnumReference( CounterSelector_Counter2, "Counter2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetReference( _Ptr->GetNode( "CounterEventSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_FrameTrigger, "FrameTrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_FrameStart, "FrameStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_Counter1End, "Counter1End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_Counter2End, "Counter2End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterEventSourceEnums>*> (&CounterEventSource)->SetEnumReference( CounterEventSource_Counter3End, "Counter3End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetReference( _Ptr->GetNode( "CounterResetSource" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Software, "Software" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line1, "Line1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line2, "Line2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line3, "Line3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Line4, "Line4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Counter1End, "Counter1End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Counter2End, "Counter2End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Counter3End, "Counter3End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetSourceEnums>*> (&CounterResetSource)->SetEnumReference( CounterResetSource_Counter4End, "Counter4End" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation)->SetReference( _Ptr->GetNode( "CounterResetActivation" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation)->SetEnumReference( CounterResetActivation_RisingEdge, "RisingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation)->SetEnumReference( CounterResetActivation_FallingEdge, "FallingEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation)->SetEnumReference( CounterResetActivation_AnyEdge, "AnyEdge" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation)->SetEnumReference( CounterResetActivation_LevelHigh, "LevelHigh" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CounterResetActivationEnums>*> (&CounterResetActivation)->SetEnumReference( CounterResetActivation_LevelLow, "LevelLow" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&CounterReset)->SetReference( _Ptr->GetNode( "CounterReset" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&CounterDuration)->SetReference( _Ptr->GetNode( "CounterDuration" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetReference( _Ptr->GetNode( "UserSetSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetNumEnums( 9 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_Default, "Default" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_HighGain, "HighGain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_AutoFunctions, "AutoFunctions" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_Color, "Color" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_ColorRaw, "ColorRaw" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_UserSet1, "UserSet1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_UserSet2, "UserSet2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_UserSet3, "UserSet3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetSelectorEnums>*> (&UserSetSelector)->SetEnumReference( UserSetSelector_LightMicroscopy, "LightMicroscopy" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&UserSetLoad)->SetReference( _Ptr->GetNode( "UserSetLoad" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&UserSetSave)->SetReference( _Ptr->GetNode( "UserSetSave" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetReference( _Ptr->GetNode( "UserSetDefault" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetNumEnums( 9 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_Default, "Default" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_HighGain, "HighGain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_AutoFunctions, "AutoFunctions" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_Color, "Color" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_ColorRaw, "ColorRaw" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_UserSet1, "UserSet1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_UserSet2, "UserSet2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_UserSet3, "UserSet3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserSetDefaultEnums>*> (&UserSetDefault)->SetEnumReference( UserSetDefault_LightMicroscopy, "LightMicroscopy" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ChunkModeActive)->SetReference( _Ptr->GetNode( "ChunkModeActive" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetReference( _Ptr->GetNode( "ChunkSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetNumEnums( 8 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Image, "Image" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Gain, "Gain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_ExposureTime, "ExposureTime" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_Timestamp, "Timestamp" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_LineStatusAll, "LineStatusAll" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_CounterValue, "CounterValue" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_SequencerSetActive, "SequencerSetActive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ChunkSelectorEnums>*> (&ChunkSelector)->SetEnumReference( ChunkSelector_PayloadCRC16, "PayloadCRC16" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ChunkEnable)->SetReference( _Ptr->GetNode( "ChunkEnable" ) );
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
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetReference( _Ptr->GetNode( "EventSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetNumEnums( 9 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_ExposureEnd, "ExposureEnd" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameStart, "FrameStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameBurstStart, "FrameBurstStart" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameStartOvertrigger, "FrameStartOvertrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameBurstStartOvertrigger, "FrameBurstStartOvertrigger" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_CriticalTemperature, "CriticalTemperature" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_OverTemperature, "OverTemperature" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameStartWait, "FrameStartWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventSelectorEnums>*> (&EventSelector)->SetEnumReference( EventSelector_FrameBurstStartWait, "FrameBurstStartWait" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetReference( _Ptr->GetNode( "EventNotification" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetEnumReference( EventNotification_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<EventNotificationEnums>*> (&EventNotification)->SetEnumReference( EventNotification_On, "On" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&TriggerEventTest)->SetReference( _Ptr->GetNode( "TriggerEventTest" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventExposureEnd)->SetReference( _Ptr->GetNode( "EventExposureEnd" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventExposureEndTimestamp)->SetReference( _Ptr->GetNode( "EventExposureEndTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventExposureEndFrameID)->SetReference( _Ptr->GetNode( "EventExposureEndFrameID" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStart)->SetReference( _Ptr->GetNode( "EventFrameStart" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartTimestamp)->SetReference( _Ptr->GetNode( "EventFrameStartTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartFrameID)->SetReference( _Ptr->GetNode( "EventFrameStartFrameID" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStart)->SetReference( _Ptr->GetNode( "EventFrameBurstStart" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartTimestamp)->SetReference( _Ptr->GetNode( "EventFrameBurstStartTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartFrameID)->SetReference( _Ptr->GetNode( "EventFrameBurstStartFrameID" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartOvertrigger)->SetReference( _Ptr->GetNode( "EventFrameStartOvertrigger" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartOvertriggerTimestamp)->SetReference( _Ptr->GetNode( "EventFrameStartOvertriggerTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartOvertriggerFrameID)->SetReference( _Ptr->GetNode( "EventFrameStartOvertriggerFrameID" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartOvertrigger)->SetReference( _Ptr->GetNode( "EventFrameBurstStartOvertrigger" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartOvertriggerTimestamp)->SetReference( _Ptr->GetNode( "EventFrameBurstStartOvertriggerTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartOvertriggerFrameID)->SetReference( _Ptr->GetNode( "EventFrameBurstStartOvertriggerFrameID" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventTest)->SetReference( _Ptr->GetNode( "EventTest" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventTestTimestamp)->SetReference( _Ptr->GetNode( "EventTestTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventCriticalTemperature)->SetReference( _Ptr->GetNode( "EventCriticalTemperature" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventCriticalTemperatureTimestamp)->SetReference( _Ptr->GetNode( "EventCriticalTemperatureTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventOverTemperature)->SetReference( _Ptr->GetNode( "EventOverTemperature" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventOverTemperatureTimestamp)->SetReference( _Ptr->GetNode( "EventOverTemperatureTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartWait)->SetReference( _Ptr->GetNode( "EventFrameStartWait" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameStartWaitTimestamp)->SetReference( _Ptr->GetNode( "EventFrameStartWaitTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartWait)->SetReference( _Ptr->GetNode( "EventFrameBurstStartWait" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&EventFrameBurstStartWaitTimestamp)->SetReference( _Ptr->GetNode( "EventFrameBurstStartWaitTimestamp" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PayloadSize)->SetReference( _Ptr->GetNode( "PayloadSize" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>*> (&BslUSBSpeedMode)->SetReference( _Ptr->GetNode( "BslUSBSpeedMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>*> (&BslUSBSpeedMode)->SetNumEnums( 4 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>*> (&BslUSBSpeedMode)->SetEnumReference( BslUSBSpeedMode_LowSpeed, "LowSpeed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>*> (&BslUSBSpeedMode)->SetEnumReference( BslUSBSpeedMode_FullSpeed, "FullSpeed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>*> (&BslUSBSpeedMode)->SetEnumReference( BslUSBSpeedMode_HighSpeed, "HighSpeed" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<BslUSBSpeedModeEnums>*> (&BslUSBSpeedMode)->SetEnumReference( BslUSBSpeedMode_SuperSpeed, "SuperSpeed" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadTransferSize)->SetReference( _Ptr->GetNode( "SIPayloadTransferSize" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadTransferCount)->SetReference( _Ptr->GetNode( "SIPayloadTransferCount" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadFinalTransfer1Size)->SetReference( _Ptr->GetNode( "SIPayloadFinalTransfer1Size" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&SIPayloadFinalTransfer2Size)->SetReference( _Ptr->GetNode( "SIPayloadFinalTransfer2Size" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TestPendingAck)->SetReference( _Ptr->GetNode( "TestPendingAck" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PayloadTransferBlockDelay)->SetReference( _Ptr->GetNode( "PayloadTransferBlockDelay" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PayloadTransferSize)->SetReference( _Ptr->GetNode( "PayloadTransferSize" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PayloadTransferCount)->SetReference( _Ptr->GetNode( "PayloadTransferCount" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PayloadFinalTransfer1Size)->SetReference( _Ptr->GetNode( "PayloadFinalTransfer1Size" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&PayloadFinalTransfer2Size)->SetReference( _Ptr->GetNode( "PayloadFinalTransfer2Size" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceVendorName)->SetReference( _Ptr->GetNode( "DeviceVendorName" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceModelName)->SetReference( _Ptr->GetNode( "DeviceModelName" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceManufacturerInfo)->SetReference( _Ptr->GetNode( "DeviceManufacturerInfo" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceVersion)->SetReference( _Ptr->GetNode( "DeviceVersion" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceFirmwareVersion)->SetReference( _Ptr->GetNode( "DeviceFirmwareVersion" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceSerialNumber)->SetReference( _Ptr->GetNode( "DeviceSerialNumber" ) );
        static_cast<GENAPI_NAMESPACE::CStringRef*> (&DeviceUserID)->SetReference( _Ptr->GetNode( "DeviceUserID" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetReference( _Ptr->GetNode( "DeviceScanType" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetEnumReference( DeviceScanType_Areascan, "Areascan" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceScanTypeEnums>*> (&DeviceScanType)->SetEnumReference( DeviceScanType_Linescan, "Linescan" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&TimestampLatch)->SetReference( _Ptr->GetNode( "TimestampLatch" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&TimestampLatchValue)->SetReference( _Ptr->GetNode( "TimestampLatchValue" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkSelector)->SetReference( _Ptr->GetNode( "DeviceLinkSelector" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkSpeed)->SetReference( _Ptr->GetNode( "DeviceLinkSpeed" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceLinkThroughputLimitModeEnums>*> (&DeviceLinkThroughputLimitMode)->SetReference( _Ptr->GetNode( "DeviceLinkThroughputLimitMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceLinkThroughputLimitModeEnums>*> (&DeviceLinkThroughputLimitMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceLinkThroughputLimitModeEnums>*> (&DeviceLinkThroughputLimitMode)->SetEnumReference( DeviceLinkThroughputLimitMode_Off, "Off" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceLinkThroughputLimitModeEnums>*> (&DeviceLinkThroughputLimitMode)->SetEnumReference( DeviceLinkThroughputLimitMode_On, "On" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkThroughputLimit)->SetReference( _Ptr->GetNode( "DeviceLinkThroughputLimit" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceLinkCurrentThroughput)->SetReference( _Ptr->GetNode( "DeviceLinkCurrentThroughput" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceTemperatureSelectorEnums>*> (&DeviceTemperatureSelector)->SetReference( _Ptr->GetNode( "DeviceTemperatureSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceTemperatureSelectorEnums>*> (&DeviceTemperatureSelector)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceTemperatureSelectorEnums>*> (&DeviceTemperatureSelector)->SetEnumReference( DeviceTemperatureSelector_Coreboard, "Coreboard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceTemperatureSelectorEnums>*> (&DeviceTemperatureSelector)->SetEnumReference( DeviceTemperatureSelector_Sensorboard, "Sensorboard" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceTemperatureSelectorEnums>*> (&DeviceTemperatureSelector)->SetEnumReference( DeviceTemperatureSelector_Framegrabberboard, "Framegrabberboard" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&DeviceTemperature)->SetReference( _Ptr->GetNode( "DeviceTemperature" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetReference( _Ptr->GetNode( "TemperatureState" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetNumEnums( 3 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetEnumReference( TemperatureState_Ok, "Ok" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetEnumReference( TemperatureState_Critical, "Critical" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<TemperatureStateEnums>*> (&TemperatureState)->SetEnumReference( TemperatureState_Error, "Error" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&DeviceReset)->SetReference( _Ptr->GetNode( "DeviceReset" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceSFNCVersionMajor)->SetReference( _Ptr->GetNode( "DeviceSFNCVersionMajor" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceSFNCVersionMinor)->SetReference( _Ptr->GetNode( "DeviceSFNCVersionMinor" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceSFNCVersionSubMinor)->SetReference( _Ptr->GetNode( "DeviceSFNCVersionSubMinor" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceIndicatorModeEnums>*> (&DeviceIndicatorMode)->SetReference( _Ptr->GetNode( "DeviceIndicatorMode" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceIndicatorModeEnums>*> (&DeviceIndicatorMode)->SetNumEnums( 2 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceIndicatorModeEnums>*> (&DeviceIndicatorMode)->SetEnumReference( DeviceIndicatorMode_Inactive, "Inactive" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<DeviceIndicatorModeEnums>*> (&DeviceIndicatorMode)->SetEnumReference( DeviceIndicatorMode_Active, "Active" );        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingStart)->SetReference( _Ptr->GetNode( "DeviceRegistersStreamingStart" ) );
        static_cast<GENAPI_NAMESPACE::CCommandRef*> (&DeviceRegistersStreamingEnd)->SetReference( _Ptr->GetNode( "DeviceRegistersStreamingEnd" ) );
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&DeviceColorPipelineVersion)->SetReference( _Ptr->GetNode( "DeviceColorPipelineVersion" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetReference( _Ptr->GetNode( "UserDefinedValueSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value1, "Value1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value2, "Value2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value3, "Value3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value4, "Value4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<UserDefinedValueSelectorEnums>*> (&UserDefinedValueSelector)->SetEnumReference( UserDefinedValueSelector_Value5, "Value5" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&UserDefinedValue)->SetReference( _Ptr->GetNode( "UserDefinedValue" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector)->SetReference( _Ptr->GetNode( "RemoveParameterLimitSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector)->SetNumEnums( 5 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector)->SetEnumReference( RemoveParameterLimitSelector_Gain, "Gain" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector)->SetEnumReference( RemoveParameterLimitSelector_BlackLevel, "BlackLevel" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector)->SetEnumReference( RemoveParameterLimitSelector_ExposureTime, "ExposureTime" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector)->SetEnumReference( RemoveParameterLimitSelector_AutoTargetValue, "AutoTargetValue" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<RemoveParameterLimitSelectorEnums>*> (&RemoveParameterLimitSelector)->SetEnumReference( RemoveParameterLimitSelector_ExposureOverhead, "ExposureOverhead" );        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&RemoveParameterLimit)->SetReference( _Ptr->GetNode( "RemoveParameterLimit" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetReference( _Ptr->GetNode( "ExpertFeatureAccessSelector" ) );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetNumEnums( 10 );
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature1, "ExpertFeature1" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature2, "ExpertFeature2" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature3, "ExpertFeature3" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature4, "ExpertFeature4" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature5, "ExpertFeature5" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature6, "ExpertFeature6" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature7, "ExpertFeature7" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature8, "ExpertFeature8" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature9, "ExpertFeature9" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<ExpertFeatureAccessSelectorEnums>*> (&ExpertFeatureAccessSelector)->SetEnumReference( ExpertFeatureAccessSelector_ExpertFeature10, "ExpertFeature10" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ExpertFeatureAccessKey)->SetReference( _Ptr->GetNode( "ExpertFeatureAccessKey" ) );
        static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ExpertFeatureEnable)->SetReference( _Ptr->GetNode( "ExpertFeatureEnable" ) );
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

    }

    inline const char* CUsbCameraParams_Params::_GetVendorName( void )
    {
        return "Basler";
    }

    inline const char* CUsbCameraParams_Params::_GetModelName( void )
    {
        return "UsbCameraParams";
    }

    //! \endcond

} // namespace Basler_UsbCameraParams

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_UsbCameraParams_PARAMS_H
