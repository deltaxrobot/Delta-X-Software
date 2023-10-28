//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for Basler camera devices

The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_UNIVERSALCAMERAPARAMS_H
#define BASLER_PYLON_UNIVERSALCAMERAPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_UniversalCameraParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for AcquisitionFrameRateEnum
    enum AcquisitionFrameRateEnumEnums
    {
        AcquisitionFrameRateEnum_FrameRate24,  //!< Applies to: CameraLink
        AcquisitionFrameRateEnum_FrameRate25,  //!< Applies to: CameraLink
        AcquisitionFrameRateEnum_FrameRate30,  //!< Applies to: CameraLink
        AcquisitionFrameRateEnum_FrameRate50,  //!< Applies to: CameraLink
        AcquisitionFrameRateEnum_FrameRate60  //!< Applies to: CameraLink
    };

    //! Valid values for AcquisitionMode
    enum AcquisitionModeEnums
    {
        AcquisitionMode_Continuous,  //!< The acquisition mode is set to Continuous - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        AcquisitionMode_MultiFrame,  //!< The acquisition mode is set to Multi Frame - Applies to: CameraLink and GigE
        AcquisitionMode_SingleFrame  //!< The acquisition mode is set to Single Frame - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for AcquisitionStatusSelector
    enum AcquisitionStatusSelectorEnums
    {
        AcquisitionStatusSelector_AcquisitionActive,  //!< A check determines whether the camera is currently acquiring one or multiple frames - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        AcquisitionStatusSelector_AcquisitionIdle,  //!< A check determines whether the camera is currently idle - Applies to: GigE
        AcquisitionStatusSelector_AcquisitionTransfer,  //!< A check determines whether the camera is currently transferring an acquisition of one or multiple frames - Applies to: CameraLink and GigE
        AcquisitionStatusSelector_AcquisitionTriggerWait,  //!< A check determines whether the camera is currently waiting for a trigger to acquire one or multiple frames - Applies to: CameraLink and GigE
        AcquisitionStatusSelector_ExposureActive,  //!< A check determines whether the camera is currently exposing a frame - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        AcquisitionStatusSelector_ExposureTriggerWait,  //!< A check determines whether the camera is currently waiting for an Exposure Start trigger signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        AcquisitionStatusSelector_FrameActive,  //!< A check determines whether the camera is currently capturing a frame - Applies to: CameraLink, GigE and ace USB
        AcquisitionStatusSelector_FrameBurstActive,  //!< A check determines whether the camera is currently doing a frame burst of one or many frames - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        AcquisitionStatusSelector_FrameBurstTriggerActive,  //!< A check can be performed if the device is currently doing a frame burst of one or many frames - Applies to: ace USB
        AcquisitionStatusSelector_FrameBurstTriggerTransfer,  //!< A check can be performed if the device is currently transferring a frame burst of one or many frames - Applies to: ace USB
        AcquisitionStatusSelector_FrameBurstTriggerWait,  //!< A check determines whether the camera is currently waiting for a frame burst trigger - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        AcquisitionStatusSelector_FrameTransfer,  //!< A check determines whether the camera is currently transferring a frame - Applies to: CameraLink, GigE and ace USB
        AcquisitionStatusSelector_FrameTriggerWait,  //!< A check determines whether the camera is currently waiting for a frame trigger - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        AcquisitionStatusSelector_LineTriggerWait  //!< A check determines whether the camera is currently waiting for a line trigger - Applies to: CameraLink and GigE
    };

    //! Valid values for AutoFunctionAOISelector
    enum AutoFunctionAOISelectorEnums
    {
        AutoFunctionAOISelector_AOI1,  //!< Auto function AOI 1 can be configured - Applies to: CameraLink and GigE
        AutoFunctionAOISelector_AOI2,  //!< Auto function AOI 2 can be configured - Applies to: CameraLink and GigE
        AutoFunctionAOISelector_AOI3,  //!< Applies to: CameraLink and GigE
        AutoFunctionAOISelector_AOI4,  //!< Applies to: CameraLink and GigE
        AutoFunctionAOISelector_AOI5,  //!< Applies to: CameraLink and GigE
        AutoFunctionAOISelector_AOI6,  //!< Applies to: CameraLink and GigE
        AutoFunctionAOISelector_AOI7,  //!< Applies to: CameraLink and GigE
        AutoFunctionAOISelector_AOI8  //!< Applies to: CameraLink and GigE
    };

    //! Valid values for AutoFunctionProfile
    enum AutoFunctionProfileEnums
    {
        AutoFunctionProfile_AntiFlicker50Hz,  //!< Gain and exposure time are optimized to reduce flickering in an environment where the lighting flickers at a 50-Hz rate (e g , Europe) - Applies to: dart BCON, dart USB and pulse USB
        AutoFunctionProfile_AntiFlicker60Hz,  //!< Gain and exposure time are optimized to reduce flickering in an environment where the lighting flickers at a 60-Hz rate (e g , North America) - Applies to: dart BCON, dart USB and pulse USB
        AutoFunctionProfile_ExposureMinimum,  //!< Exposure time is kept as low as possible - Applies to: CameraLink and GigE
        AutoFunctionProfile_ExposureMinimumQuick,  //!< Exposure time is kept as low as possible and is adjusted quickly - Applies to: GigE
        AutoFunctionProfile_GainMinimum,  //!< Gain is kept as low as possible - Applies to: CameraLink and GigE
        AutoFunctionProfile_GainMinimumQuick,  //!< Gain time is kept as low as possible and is adjusted quickly - Applies to: GigE
        AutoFunctionProfile_MinimizeExposureTime,  //!< Exposure time is kept as low as possible - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        AutoFunctionProfile_MinimizeExposureTimeQuick,  //!< Exposure time is kept as low as possible and is adjusted quickly - Applies to: ace USB
        AutoFunctionProfile_MinimizeGain,  //!< Gain is kept as low as possible - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        AutoFunctionProfile_MinimizeGainQuick,  //!< Gain is kept as low as possible and is adjusted quickly - Applies to: ace USB
        AutoFunctionProfile_Smart  //!< Gain is kept as low as possible and the frame rate is kept as high as possible during automatic adjustments   - Applies to: dart BCON, dart USB and pulse USB
    };

    //! Valid values for AutoFunctionROISelector
    enum AutoFunctionROISelectorEnums
    {
        AutoFunctionROISelector_ROI1,  //!< Auto function ROI 1 can be configured - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        AutoFunctionROISelector_ROI2  //!< Auto function ROI 2 can be configured - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for AutoTonalRangeAdjustmentSelector
    enum AutoTonalRangeAdjustmentSelectorEnums
    {
        AutoTonalRangeAdjustmentSelector_Bright,  //!< Only the bright end of the tonal range can be adjusted - Applies to: GigE and ace USB
        AutoTonalRangeAdjustmentSelector_Dark,  //!< Only the dark end of the tonal range can be adjusted - Applies to: GigE and ace USB
        AutoTonalRangeAdjustmentSelector_DarkAndBright  //!< The dark and bright end of the tonal range can be adjusted - Applies to: GigE and ace USB
    };

    //! Valid values for AutoTonalRangeModeSelector
    enum AutoTonalRangeModeSelectorEnums
    {
        AutoTonalRangeModeSelector_Color,  //!< Only color is adjusted - Applies to: GigE and ace USB
        AutoTonalRangeModeSelector_ColorAndContrast,  //!< Color and contrast are adjusted - Applies to: GigE and ace USB
        AutoTonalRangeModeSelector_Contrast  //!< Only contrast is adjusted - Applies to: GigE and ace USB
    };

    //! Valid values for BLCSerialPortBaudRate
    enum BLCSerialPortBaudRateEnums
    {
        BLCSerialPortBaudRate_Baud115200  //!< The baud rate is 115200 Bd - Applies to: GigE and ace USB
    };

    //! Valid values for BLCSerialPortParity
    enum BLCSerialPortParityEnums
    {
        BLCSerialPortParity_Even,  //!< The serial communication module uses an even parity bit - Applies to: GigE and ace USB
        BLCSerialPortParity_Odd,  //!< The serial communication module uses an odd parity bit - Applies to: GigE and ace USB
        BLCSerialPortParity_Off  //!< The serial communication module does not use a parity bit - Applies to: GigE and ace USB
    };

    //! Valid values for BLCSerialPortSource
    enum BLCSerialPortSourceEnums
    {
        BLCSerialPortSource_Line3,  //!< The signal source for the serial communication module is set to line 3 - Applies to: GigE and ace USB
        BLCSerialPortSource_Line4,  //!< The signal source for the serial communication module is set to line 4 - Applies to: GigE and ace USB
        BLCSerialPortSource_Off  //!< The signal source for the serial communication module is disabled - Applies to: GigE and ace USB
    };

    //! Valid values for BLCSerialPortStopBits
    enum BLCSerialPortStopBitsEnums
    {
        BLCSerialPortStopBits_StopBits0,  //!< The serial communication module does not use a stop bit - Applies to: GigE and ace USB
        BLCSerialPortStopBits_StopBits1  //!< The serial communication module does uses 1 stop bit - Applies to: GigE and ace USB
    };

    //! Valid values for BLCSerialReceiveQueueStatus
    enum BLCSerialReceiveQueueStatusEnums
    {
        BLCSerialReceiveQueueStatus_Empty,  //!< The receive queue is empty - Applies to: GigE and ace USB
        BLCSerialReceiveQueueStatus_Filled,  //!< The receive queue contains at least one value - Applies to: GigE and ace USB
        BLCSerialReceiveQueueStatus_Full  //!< The receive queue is full - Applies to: GigE and ace USB
    };

    //! Valid values for BLCSerialTransmitQueueStatus
    enum BLCSerialTransmitQueueStatusEnums
    {
        BLCSerialTransmitQueueStatus_Empty,  //!< The transmit queue is empty - Applies to: GigE and ace USB
        BLCSerialTransmitQueueStatus_Filled,  //!< The transmit queue contains at least one value - Applies to: GigE and ace USB
        BLCSerialTransmitQueueStatus_Full  //!< The transmit queue is full - Applies to: GigE and ace USB
    };

    //! Valid values for BalanceRatioSelector
    enum BalanceRatioSelectorEnums
    {
        BalanceRatioSelector_Blue,  //!< Balance ratio is applied to the blue channel - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        BalanceRatioSelector_Green,  //!< Balance ratio is applied to the green channel - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        BalanceRatioSelector_Red  //!< Balance ratio is applied to the red channel - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for BalanceWhiteAuto
    enum BalanceWhiteAutoEnums
    {
        BalanceWhiteAuto_Continuous,  //!< White balance is adjusted continuously while images are being acquired - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        BalanceWhiteAuto_Off,  //!< The Balance White Auto auto function is disabled - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        BalanceWhiteAuto_Once  //!< White balance is adjusted automatically to reach the specified target value - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for BandwidthReserveMode
    enum BandwidthReserveModeEnums
    {
        BandwidthReserveMode_Manual,  //!< The bandwidth reserve can be configured manually - Applies to: ace 2 GigE
        BandwidthReserveMode_Performance,  //!< The bandwidth reserve is set to 5 % - Applies to: ace 2 GigE
        BandwidthReserveMode_Standard  //!< The bandwidth reserve is set to 10 % - Applies to: ace 2 GigE
    };

    //! Valid values for BconClockFrequency
    enum BconClockFrequencyEnums
    {
        BconClockFrequency_MHz_12,  //!< The BCON clock frequency is set to 12 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_20,  //!< The BCON clock frequency is set to 20 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_28,  //!< The BCON clock frequency is set to 28 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_36,  //!< The BCON clock frequency is set to 36 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_44,  //!< The BCON clock frequency is set to 44 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_52,  //!< The BCON clock frequency is set to 52 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_60,  //!< The BCON clock frequency is set to 60 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_68,  //!< The BCON clock frequency is set to 68 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_76,  //!< The BCON clock frequency is set to 76 MHz - Applies to: dart BCON
        BconClockFrequency_MHz_84  //!< The BCON clock frequency is set to 84 MHz - Applies to: dart BCON
    };

    //! Valid values for BconPixelsPerClockCycle
    enum BconPixelsPerClockCycleEnums
    {
        BconPixelsPerClockCycle_One,  //!< During each clock cycle, data for one pixel is transmitted via the BCON interface - Applies to: dart BCON
        BconPixelsPerClockCycle_Two  //!< During each clock cycle, data for two pixels is transmitted via the BCON interface - Applies to: dart BCON
    };

    //! Valid values for BinningHorizontalMode
    enum BinningHorizontalModeEnums
    {
        BinningHorizontalMode_Average,  //!< The values of the binned pixels are averaged - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        BinningHorizontalMode_Sum  //!< The values of the binned pixels are summed - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for BinningModeHorizontal
    enum BinningModeHorizontalEnums
    {
        BinningModeHorizontal_Averaging,  //!< The values of the binned pixels are averaged - Applies to: CameraLink
        BinningModeHorizontal_Summing  //!< The values of the binned pixels are summed - Applies to: CameraLink
    };

    //! Valid values for BinningModeVertical
    enum BinningModeVerticalEnums
    {
        BinningModeVertical_Averaging,  //!< The values of the binned pixels are averaged - Applies to: CameraLink
        BinningModeVertical_Summing  //!< The values of the binned pixels are summed - Applies to: CameraLink
    };

    //! Valid values for BinningVerticalMode
    enum BinningVerticalModeEnums
    {
        BinningVerticalMode_Average,  //!< The values of the binned pixels are averaged - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        BinningVerticalMode_Sum  //!< The values of the binned pixels are summed - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for BlackLevelSelector
    enum BlackLevelSelectorEnums
    {
        BlackLevelSelector_All,  //!< The black level value is applied to all sensor taps - Applies to: CameraLink, GigE, ace USB, dart BCON, dart USB and pulse USB
        BlackLevelSelector_AnalogAll,  //!< Selects all analog black level controls for adjustment - Applies to: CameraLink and GigE
        BlackLevelSelector_Blue,  //!< Selects the blue black level control for adjustment - Applies to: CameraLink and GigE
        BlackLevelSelector_DigitalAll,  //!< Selects all digital black level controls for adjustment - Applies to: CameraLink and GigE
        BlackLevelSelector_Green,  //!< Selects the green black level control for adjustment - Applies to: CameraLink and GigE
        BlackLevelSelector_Red,  //!< Selects the red black level control for adjustment - Applies to: CameraLink and GigE
        BlackLevelSelector_Tap1,  //!< The black level value is applied to sensor tap 1 - Applies to: CameraLink and GigE
        BlackLevelSelector_Tap2,  //!< The black level value is applied to sensor tap 2 - Applies to: CameraLink and GigE
        BlackLevelSelector_Tap3,  //!< The black level value is applied to sensor tap 3 - Applies to: CameraLink and GigE
        BlackLevelSelector_Tap4  //!< The black level value is applied to sensor tap 4 - Applies to: CameraLink and GigE
    };

    //! Valid values for BslAcquisitionBurstMode
    enum BslAcquisitionBurstModeEnums
    {
        BslAcquisitionBurstMode_HighSpeed,  //!< The High Speed burst mode is enabled - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslAcquisitionBurstMode_Standard  //!< The Standard burst mode is enabled - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for BslAcquisitionStopMode
    enum BslAcquisitionStopModeEnums
    {
        BslAcquisitionStopMode_AbortExposure,  //!< Acquisition Stop commands abort exposure - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslAcquisitionStopMode_CompleteExposure  //!< Acquisition Stop commands allow the exposure to be completed - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

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

    //! Valid values for BslColorAdjustmentSelector
    enum BslColorAdjustmentSelectorEnums
    {
        BslColorAdjustmentSelector_Blue,  //!< Colors with a predominant blue component can be adjusted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslColorAdjustmentSelector_Cyan,  //!< Colors with a predominant cyan component can be adjusted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslColorAdjustmentSelector_Green,  //!< Colors with a predominant green component can be adjusted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslColorAdjustmentSelector_Magenta,  //!< Colors with a predominant magenta component can be adjusted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslColorAdjustmentSelector_Red,  //!< Colors with a predominant red component can be adjusted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslColorAdjustmentSelector_Yellow  //!< Colors with a predominant yellow component can be adjusted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslColorSpace
    enum BslColorSpaceEnums
    {
        BslColorSpace_Off,  //!< No additional gamma correction value is applied - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslColorSpace_sRgb  //!< The color space is set to sRGB - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for BslColorSpaceMode
    enum BslColorSpaceModeEnums
    {
        BslColorSpaceMode_RGB,  //!< The color space is set to RGB - Applies to: dart BCON, dart USB and pulse USB
        BslColorSpaceMode_sRGB  //!< The color space is set to sRGB - Applies to: dart BCON, dart USB and pulse USB
    };

    //! Valid values for BslContrastMode
    enum BslContrastModeEnums
    {
        BslContrastMode_Linear,  //!< The camera uses a linear function to adjust the contrast - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        BslContrastMode_SCurve  //!< The camera uses an S-curve function to adjust the contrast - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for BslDefectPixelCorrectionMode
    enum BslDefectPixelCorrectionModeEnums
    {
        BslDefectPixelCorrectionMode_Off,  //!< Defect pixel correction is disabled - Applies to: dart 2 USB
        BslDefectPixelCorrectionMode_On,  //!< Defect pixel correction is enabled - Applies to: dart 2 USB
        BslDefectPixelCorrectionMode_StaticOnly  //!< Only static defect pixel correction is enabled - Applies to: dart 2 USB
    };

    //! Valid values for BslExposureTimeMode
    enum BslExposureTimeModeEnums
    {
        BslExposureTimeMode_Standard,  //!< The exposure time mode is set to Standard - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslExposureTimeMode_UltraShort  //!< The exposure time mode is set to Ultra Short - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslImmediateTriggerMode
    enum BslImmediateTriggerModeEnums
    {
        BslImmediateTriggerMode_Off,  //!< The Immediate Trigger mode is disabled - Applies to: dart BCON, dart USB and pulse USB
        BslImmediateTriggerMode_On  //!< The Immediate Trigger mode is enabled - Applies to: dart BCON, dart USB and pulse USB
    };

    //! Valid values for BslLightControlErrorStatus
    enum BslLightControlErrorStatusEnums
    {
        BslLightControlErrorStatus_Device1,  //!< Light device 1 is experiencing problems - Applies to: GigE and ace USB
        BslLightControlErrorStatus_Device2,  //!< Light device 2 is experiencing problems - Applies to: GigE and ace USB
        BslLightControlErrorStatus_Device3,  //!< Light device 3 is experiencing problems - Applies to: GigE and ace USB
        BslLightControlErrorStatus_Device4,  //!< Light device 4 is experiencing problems - Applies to: GigE and ace USB
        BslLightControlErrorStatus_MultipleDevices,  //!< Multiple light devices are experiencing problems - Applies to: GigE and ace USB
        BslLightControlErrorStatus_NoError  //!< No error was detected - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightControlMode
    enum BslLightControlModeEnums
    {
        BslLightControlMode_Off,  //!< The light control features are disabled - Applies to: GigE and ace USB
        BslLightControlMode_On  //!< The light control features are enabled - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightControlSource
    enum BslLightControlSourceEnums
    {
        BslLightControlSource_Line3,  //!< Line 3 is used to control the light features - Applies to: GigE and ace USB
        BslLightControlSource_Line4,  //!< Line 4 is used to control the light features - Applies to: GigE and ace USB
        BslLightControlSource_Off  //!< No line is used to control the light features - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightControlStatus
    enum BslLightControlStatusEnums
    {
        BslLightControlStatus_Idle,  //!< No light device has been detected - Applies to: GigE and ace USB
        BslLightControlStatus_Off,  //!< The light control mode is disabled - Applies to: GigE and ace USB
        BslLightControlStatus_Ready,  //!< The light device is ready for use - Applies to: GigE and ace USB
        BslLightControlStatus_Searching,  //!< The controller ist searching for light devices connected to your camera - Applies to: GigE and ace USB
        BslLightControlStatus_Updating  //!< Parameters are being updated - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightDeviceChangeID
    enum BslLightDeviceChangeIDEnums
    {
        BslLightDeviceChangeID_Device1,  //!< The ID of the currently selected light device is changed to Device 1 - Applies to: GigE and ace USB
        BslLightDeviceChangeID_Device2,  //!< The ID of the currently selected light device is changed to Device 2 - Applies to: GigE and ace USB
        BslLightDeviceChangeID_Device3,  //!< The ID of the currently selected light device is changed to Device 3 - Applies to: GigE and ace USB
        BslLightDeviceChangeID_Device4  //!< The ID of the currently selected light device is changed to Device 4 - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightDeviceLastError
    enum BslLightDeviceLastErrorEnums
    {
        BslLightDeviceLastError_Communication,  //!< The data transmission between the camera and the light device is disrupted - Applies to: GigE and ace USB
        BslLightDeviceLastError_Connection,  //!< The connection between the camera and the light device is broken - Applies to: GigE and ace USB
        BslLightDeviceLastError_Hardware,  //!< The light device is experiencing a technical fault - Applies to: GigE and ace USB
        BslLightDeviceLastError_InsufficientCurrent,  //!< The light controller is unable to supply the requested current - Applies to: GigE and ace USB
        BslLightDeviceLastError_NoError,  //!< No error was detected - Applies to: GigE and ace USB
        BslLightDeviceLastError_ShortCircuit  //!< There is a short circuit at the Lighting connector of the light controller - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightDeviceOperationMode
    enum BslLightDeviceOperationModeEnums
    {
        BslLightDeviceOperationMode_Off,  //!< The currently selected light device is switched off - Applies to: GigE and ace USB
        BslLightDeviceOperationMode_On,  //!< The currently selected light device is switched on - Applies to: GigE and ace USB
        BslLightDeviceOperationMode_Strobe  //!< The currently selected light device is set to strobe mode - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightDeviceSelector
    enum BslLightDeviceSelectorEnums
    {
        BslLightDeviceSelector_Device1,  //!< Light device 1 can be configured - Applies to: GigE and ace USB
        BslLightDeviceSelector_Device2,  //!< Light device 2 can be configured - Applies to: GigE and ace USB
        BslLightDeviceSelector_Device3,  //!< Light device 3 can be configured - Applies to: GigE and ace USB
        BslLightDeviceSelector_Device4  //!< Light device 4 can be configured - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightDeviceStrobeMode
    enum BslLightDeviceStrobeModeEnums
    {
        BslLightDeviceStrobeMode_Automatic,  //!< The timing of the individual strobe pulses is determined by the Exposure Active signal - Applies to: GigE and ace USB
        BslLightDeviceStrobeMode_Manual  //!< The timing of the individual strobe pulses can be specified manually - Applies to: GigE and ace USB
    };

    //! Valid values for BslLightSourcePreset
    enum BslLightSourcePresetEnums
    {
        BslLightSourcePreset_Daylight5000K,  //!< The light source preset for image acquisitions with daylight of 5000 K is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslLightSourcePreset_Daylight6500K,  //!< The light source preset for image acquisitions with daylight of 6500 K is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslLightSourcePreset_FactoryLED6000K,  //!< The light source preset for image acquisitions with LED light is selected - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslLightSourcePreset_Off,  //!< No light source preset is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslLightSourcePreset_Tungsten  //!< The light source preset for image acquisitions with tungsten incandescent light is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for BslLightSourcePresetFeatureSelector
    enum BslLightSourcePresetFeatureSelectorEnums
    {
        BslLightSourcePresetFeatureSelector_ColorAdjustment,  //!< Adjustment of the Color Adjustment feature can be enabled or disabled - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslLightSourcePresetFeatureSelector_ColorTransformation,  //!< Adjustment of the Color Transformation feature can be enabled or disabled - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslLightSourcePresetFeatureSelector_WhiteBalance  //!< Adjustment of the Balance White feature can be enabled or disabled - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for BslMultipleROIColumnSelector
    enum BslMultipleROIColumnSelectorEnums
    {
        BslMultipleROIColumnSelector_Column1,  //!< Column 1 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIColumnSelector_Column2,  //!< Column 2 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIColumnSelector_Column3,  //!< Column 3 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIColumnSelector_Column4,  //!< Column 4 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIColumnSelector_Column5,  //!< Column 5 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIColumnSelector_Column6,  //!< Column 6 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIColumnSelector_Column7,  //!< Column 7 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIColumnSelector_Column8  //!< Column 8 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslMultipleROIRowSelector
    enum BslMultipleROIRowSelectorEnums
    {
        BslMultipleROIRowSelector_Row1,  //!< Row 1 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIRowSelector_Row2,  //!< Row 2 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIRowSelector_Row3,  //!< Row 3 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIRowSelector_Row4,  //!< Row 4 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIRowSelector_Row5,  //!< Row 5 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIRowSelector_Row6,  //!< Row 6 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIRowSelector_Row7,  //!< Row 7 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslMultipleROIRowSelector_Row8  //!< Row 8 can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslPeriodicSignalSelector
    enum BslPeriodicSignalSelectorEnums
    {
        BslPeriodicSignalSelector_PeriodicSignal1  //!< Periodic Signal 1 can be configured - Applies to: ace 2 GigE
    };

    //! Valid values for BslPeriodicSignalSource
    enum BslPeriodicSignalSourceEnums
    {
        BslPeriodicSignalSource_DeviceClock,  //!< The camera is not synchronized via Precision Time Protocol (PTP) - Applies to: ace 2 GigE
        BslPeriodicSignalSource_PtpClock  //!< The camera is synchronized via Precision Time Protocol (PTP) - Applies to: ace 2 GigE
    };

    //! Valid values for BslPtpDelayMechanism
    enum BslPtpDelayMechanismEnums
    {
        BslPtpDelayMechanism_E2E,  //!< The port is configured to use the delay request-response mechanism - Applies to: ace 2 GigE
        BslPtpDelayMechanism_P2P  //!< The port is configured to use the peer delay mechanism - Applies to: ace 2 GigE
    };

    //! Valid values for BslPtpNetworkMode
    enum BslPtpNetworkModeEnums
    {
        BslPtpNetworkMode_Hybrid,  //!< Hybrid network communication is enabled - Applies to: ace 2 GigE
        BslPtpNetworkMode_Multicast,  //!< Multicast network communication is enabled - Applies to: ace 2 GigE
        BslPtpNetworkMode_Unicast  //!< Unicast network communication is enabled - Applies to: ace 2 GigE
    };

    //! Valid values for BslPtpProfile
    enum BslPtpProfileEnums
    {
        BslPtpProfile_DelayRequestResponseDefaultProfile,  //!< The default PTP profile is set to Delay Request-Response - Applies to: ace 2 GigE
        BslPtpProfile_PeerToPeerDefaultProfile  //!< The default PTP profile is set to Peer-to-Peer - Applies to: ace 2 GigE
    };

    //! Valid values for BslSensorBitDepth
    enum BslSensorBitDepthEnums
    {
        BslSensorBitDepth_Bpp10,  //!< The sensor bit depth is set to 10 bits per pixel - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslSensorBitDepth_Bpp12,  //!< The sensor bit depth is set to 12 bits per pixel - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslSensorBitDepth_Bpp8  //!< The sensor bit depth is set to 8 bits per pixel - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for BslSensorBitDepthMode
    enum BslSensorBitDepthModeEnums
    {
        BslSensorBitDepthMode_Auto,  //!< The sensor bit depth mode is set to Auto - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        BslSensorBitDepthMode_Manual  //!< The sensor bit depth mode is set to Manual - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for BslSerialBaudRate
    enum BslSerialBaudRateEnums
    {
        BslSerialBaudRate_Baud115200,  //!< A symbol rate of 115200 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialBaudRate_Baud1200,  //!< A symbol rate of 1200 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialBaudRate_Baud19200,  //!< A symbol rate of 19200 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialBaudRate_Baud2400,  //!< A symbol rate of 2400 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialBaudRate_Baud38400,  //!< A symbol rate of 38400 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialBaudRate_Baud4800,  //!< A symbol rate of 4800 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialBaudRate_Baud57600,  //!< A symbol rate of 57600 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialBaudRate_Baud9600  //!< A symbol rate of 9600 baud is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslSerialNumberOfDataBits
    enum BslSerialNumberOfDataBitsEnums
    {
        BslSerialNumberOfDataBits_Bits7,  //!< Seven data bits per frame are used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialNumberOfDataBits_Bits8  //!< Eight data bits per frame are used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslSerialNumberOfStopBits
    enum BslSerialNumberOfStopBitsEnums
    {
        BslSerialNumberOfStopBits_Bits1,  //!< One stop bit is used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialNumberOfStopBits_Bits2  //!< Two stop bits are used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslSerialParity
    enum BslSerialParityEnums
    {
        BslSerialParity_Even,  //!< An even parity check is performed - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialParity_None,  //!< No parity check is performed - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialParity_Odd  //!< An odd parity check is performed - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslSerialRxSource
    enum BslSerialRxSourceEnums
    {
        BslSerialRxSource_Line1,  //!< The source of the Rx serial input is set to Line 1 - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialRxSource_Line2,  //!< The source of the Rx serial input is set to Line 2 - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialRxSource_Line3,  //!< The source of the Rx serial input is set to Line 3 - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialRxSource_Off,  //!< Rx input is muted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        BslSerialRxSource_SerialTx  //!< The source of the Rx serial input is set to Serial Tx - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for BslTemperatureStatus
    enum BslTemperatureStatusEnums
    {
        BslTemperatureStatus_Critical,  //!< The temperature is close to or at the allowed maximum  Provide cooling - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB
        BslTemperatureStatus_Error,  //!< The temperature is above the allowed maximum  Provide cooling immediately - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB
        BslTemperatureStatus_Ok  //!< The temperature is within the normal operating temperature range - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB
    };

    //! Valid values for BslUSBSpeedMode
    enum BslUSBSpeedModeEnums
    {
        BslUSBSpeedMode_FullSpeed,  //!< The USB port is operating at Full Speed - Applies to: ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB
        BslUSBSpeedMode_HighSpeed,  //!< The USB port is operating at High Speed - Applies to: ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB
        BslUSBSpeedMode_LowSpeed,  //!< The USB port is operating at Low Speed - Applies to: ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB
        BslUSBSpeedMode_SuperSpeed  //!< The USB port is operating at SuperSpeed - Applies to: ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB
    };

    //! Valid values for BslVignettingCorrectionMode
    enum BslVignettingCorrectionModeEnums
    {
        BslVignettingCorrectionMode_Off,  //!< The vignetting correction is disabled - Applies to: boost CoaXPress
        BslVignettingCorrectionMode_On  //!< The vignetting correction is enabled - Applies to: boost CoaXPress
    };

    //! Valid values for CameraOperationMode
    enum CameraOperationModeEnums
    {
        CameraOperationMode_LongExposure,  //!< The camera operation mode is set to Long Exposure - Applies to: ace USB
        CameraOperationMode_Standard  //!< The camera operation mode is set to Standard - Applies to: ace USB
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

    //! Valid values for ChunkSelector
    enum ChunkSelectorEnums
    {
        ChunkSelector_AutoBrightnessStatus,  //!< The Auto Brightness Status chunk can be enabled - Applies to: ace 2 GigE and ace 2 USB
        ChunkSelector_BrightPixel,  //!< Applies to: GigE
        ChunkSelector_CounterValue,  //!< The Counter Value chunk can be enabled - Applies to: ace 2 GigE, ace 2 USB and ace USB
        ChunkSelector_DynamicRangeMax,  //!< The Dynamic Range Max chunk can be enabled - Applies to: GigE
        ChunkSelector_DynamicRangeMin,  //!< The Dynamic Range Min chunk can be enabled - Applies to: GigE
        ChunkSelector_ExposureTime,  //!< The Exposure Time chunk can be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        ChunkSelector_FrameID,  //!< The Frame ID chunk can be enabled - Applies to: ace 2 GigE and ace 2 USB
        ChunkSelector_FrameTriggerCounter,  //!< The Frame Trigger Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_FrameTriggerIgnoredCounter,  //!< The Frame Trigger Ignored Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_Framecounter,  //!< The Frame Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_FramesPerTriggerCounter,  //!< The Frames Per Trigger Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_Gain,  //!< The Gain chunk can be enabled - Applies to: ace 2 GigE, ace 2 USB and ace USB
        ChunkSelector_GainAll,  //!< The Gain All chunk can be enabled - Applies to: GigE
        ChunkSelector_Height,  //!< The Height chunk can be enabled - Applies to: GigE
        ChunkSelector_Image,  //!< The Image chunk can be enabled - Applies to: GigE and ace USB
        ChunkSelector_InputStatusAtLineTrigger,  //!< The Input Status At Line Trigger chunk can be enabled - Applies to: GigE
        ChunkSelector_LineStatusAll,  //!< The Line Status All chunk can be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        ChunkSelector_LineTriggerCounter,  //!< The Line Trigger Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_LineTriggerEndToEndCounter,  //!< The Line Trigger End To End Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_LineTriggerIgnoredCounter,  //!< The Line Trigger Ignored Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_OffsetX,  //!< The X Offset chunk can be enabled - Applies to: GigE
        ChunkSelector_OffsetY,  //!< The Y Offset chunk can be enabled - Applies to: GigE
        ChunkSelector_PayloadCRC16,  //!< The CRC Checksum chunk can be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        ChunkSelector_PixelFormat,  //!< The Pixel Format chunk can be enabled - Applies to: GigE
        ChunkSelector_SequenceSetIndex,  //!< The Sequence Set Index chunk can be enabled - Applies to: GigE
        ChunkSelector_SequencerSetActive,  //!< The Sequencer Set Active chunk can be enabled - Applies to: ace USB
        ChunkSelector_ShaftEncoderCounter,  //!< The Shaft Encoder Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_Stride,  //!< The Stride chunk can be enabled - Applies to: GigE
        ChunkSelector_Timestamp,  //!< The Timestamp chunk can be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        ChunkSelector_Triggerinputcounter,  //!< The Trigger Input Counter chunk can be enabled - Applies to: GigE
        ChunkSelector_VirtLineStatusAll,  //!< Selects the virtual line status all chunk for enabling - Applies to: GigE
        ChunkSelector_Width  //!< The Width chunk can be enabled - Applies to: GigE
    };

    //! Valid values for ClConfiguration
    enum ClConfigurationEnums
    {
        ClConfiguration_Base,  //!< The Base configuration is selected - Applies to: CameraLink
        ClConfiguration_Deca,  //!< The Deca configuration is selected - Applies to: CameraLink
        ClConfiguration_DualBase,  //!< The DualBase configuration is selected - Applies to: CameraLink
        ClConfiguration_Full,  //!< The Full configuration is selected - Applies to: CameraLink
        ClConfiguration_Medium  //!< The Medium configuration is selected - Applies to: CameraLink
    };

    //! Valid values for ClPixelClock
    enum ClPixelClockEnums
    {
        ClPixelClock_PixelClock20,  //!< The pixel clock speed is set to 20 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock32_5,  //!< The pixel clock speed is set to 32 5 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock40,  //!< The pixel clock speed is set to 40 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock48,  //!< The pixel clock speed is set to 48 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock65,  //!< The pixel clock speed is set to 65 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock82,  //!< The pixel clock speed is set to 82 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock82_5,  //!< The pixel clock speed is set to 82 5 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock83,  //!< The pixel clock speed is set to 83 MHz - Applies to: CameraLink
        ClPixelClock_PixelClock83_5  //!< The pixel clock speed is set to 83 5 MHz - Applies to: CameraLink
    };

    //! Valid values for ClSerialPortBaudRate
    enum ClSerialPortBaudRateEnums
    {
        ClSerialPortBaudRate_Baud115200,  //!< The baud rate is set to 115200 baud - Applies to: CameraLink
        ClSerialPortBaudRate_Baud19200,  //!< The baud rate is set to 19200 baud - Applies to: CameraLink
        ClSerialPortBaudRate_Baud230400,  //!< The baud rate is set to 230400 baud - Applies to: CameraLink
        ClSerialPortBaudRate_Baud38400,  //!< The baud rate is set to 38400 baud - Applies to: CameraLink
        ClSerialPortBaudRate_Baud460800,  //!< The baud rate is set to 460800 baud - Applies to: CameraLink
        ClSerialPortBaudRate_Baud57600,  //!< The baud rate is set to 57600 baud - Applies to: CameraLink
        ClSerialPortBaudRate_Baud921600,  //!< The baud rate is set to 921600 baud - Applies to: CameraLink
        ClSerialPortBaudRate_Baud9600  //!< The baud rate is set to 9600 baud - Applies to: CameraLink
    };

    //! Valid values for ClTapGeometry
    enum ClTapGeometryEnums
    {
        ClTapGeometry_Geometry1X,  //!< The tap geometry is set to 1 zone in horizontal direction with one tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X10,  //!< The tap geometry is set to 1 zone in horizontal direction with ten taps - Applies to: CameraLink
        ClTapGeometry_Geometry1X10_1Y,  //!< The tap geometry is set to 1 zone in horizontal direction with ten taps and 1 zone in vertical direction with 1 tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X2,  //!< The tap geometry is set to 1 zone in horizontal direction with two taps - Applies to: CameraLink
        ClTapGeometry_Geometry1X2_1Y,  //!< The tap geometry is set to 1 zone in horizontal direction with two taps and 1 zone in vertical direction with 1 tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X3,  //!< The tap geometry is set to 1 zone in horizontal direction with three taps - Applies to: CameraLink
        ClTapGeometry_Geometry1X3_1Y,  //!< The tap geometry is set to 1 zone in horizontal direction with three taps and 1 zone in vertical direction with 1 tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X4,  //!< The tap geometry is set to 1 zone in horizontal direction with four taps - Applies to: CameraLink
        ClTapGeometry_Geometry1X4_1Y,  //!< The tap geometry is set to 1 zone in horizontal direction with four taps and 1 zone in vertical direction with 1 tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X6,  //!< The tap geometry is set to 1 zone in horizontal direction with six taps - Applies to: CameraLink
        ClTapGeometry_Geometry1X6_1Y,  //!< The tap geometry is set to 1 zone in horizontal direction with six taps and 1 zone in vertical direction with 1 tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X8,  //!< The tap geometry is set to 1 zone in horizontal direction with eight taps - Applies to: CameraLink
        ClTapGeometry_Geometry1X8_1Y,  //!< The tap geometry is set to 1 zone in horizontal direction with eight taps and 1 zone in vertical direction with 1 tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X_1Y,  //!< The tap geometry is set to 1 zone in horizontal direction with one tap and 1 zone in vertical direction with 1 tap - Applies to: CameraLink
        ClTapGeometry_Geometry1X_2YE  //!< The tap geometry is set to 1 zone in horizontal direction with one tap and 2 zones in vertical direction with 1 tap with end extraction - Applies to: CameraLink
    };

    //! Valid values for ClTimeSlots
    enum ClTimeSlotsEnums
    {
        ClTimeSlots_TimeSlots1  //!< The time slot is set to one time slot - Applies to: CameraLink
    };

    //! Valid values for ColorAdjustmentSelector
    enum ColorAdjustmentSelectorEnums
    {
        ColorAdjustmentSelector_Blue,  //!< Colors with a predominant blue component can be adjusted - Applies to: CameraLink, GigE and ace USB
        ColorAdjustmentSelector_Cyan,  //!< Colors with a predominant cyan component can be adjusted - Applies to: CameraLink, GigE and ace USB
        ColorAdjustmentSelector_Green,  //!< Colors with a predominant green component can be adjusted - Applies to: CameraLink, GigE and ace USB
        ColorAdjustmentSelector_Magenta,  //!< Colors with a predominant magenta component can be adjusted - Applies to: CameraLink, GigE and ace USB
        ColorAdjustmentSelector_Red,  //!< Colors with a predominant red component can be adjusted - Applies to: CameraLink, GigE and ace USB
        ColorAdjustmentSelector_Yellow  //!< Colors with a predominant yellow component can be adjusted - Applies to: CameraLink, GigE and ace USB
    };

    //! Valid values for ColorOverexposureCompensationAOISelector
    enum ColorOverexposureCompensationAOISelectorEnums
    {
        ColorOverexposureCompensationAOISelector_AOI1  //!< Selects Color Overexposure Compensation AOI 1 - Applies to: CameraLink and GigE
    };

    //! Valid values for ColorSpace
    enum ColorSpaceEnums
    {
        ColorSpace_RGB,  //!< The color space is set to RGB - Applies to: ace USB
        ColorSpace_sRGB  //!< The color space is set to sRGB - Applies to: ace USB
    };

    //! Valid values for ColorTransformationSelector
    enum ColorTransformationSelectorEnums
    {
        ColorTransformationSelector_RGBtoRGB,  //!< Color transformation from RGB to RGB will be performed - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationSelector_RGBtoYUV,  //!< Color transformation from RGB to YUV will be performed - Applies to: CameraLink, GigE and ace USB
        ColorTransformationSelector_YUVtoRGB  //!< Color transformation from YUV to RGB will be performed - Applies to: CameraLink, GigE and ace USB
    };

    //! Valid values for ColorTransformationValueSelector
    enum ColorTransformationValueSelectorEnums
    {
        ColorTransformationValueSelector_Gain00,  //!< The desired color transformation value can be entered at the position row 0 and column 0 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain01,  //!< The desired color transformation value can be entered at the position row 0 and column 1 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain02,  //!< The desired color transformation value can be entered at the position row 0 and column 2 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain10,  //!< The desired color transformation value can be entered at the position row 1 and column 0 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain11,  //!< The desired color transformation value can be entered at the position row 1 and column 1 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain12,  //!< The desired color transformation value can be entered at the position row 1 and column 2 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain20,  //!< The desired color transformation value can be entered at the position row 2 and column 0 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain21,  //!< The desired color transformation value can be entered at the position row 2 and column 1 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Gain22,  //!< The desired color transformation value can be entered at the position row 2 and column 2 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress
        ColorTransformationValueSelector_Offset0,  //!< The desired color transformation value can be entered in row 0 of the offset matrix - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        ColorTransformationValueSelector_Offset1,  //!< The desired color transformation value can be entered in row 1 of the offset matrix - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
        ColorTransformationValueSelector_Offset2  //!< The desired color transformation value can be entered in row 2 of the offset matrix - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress
    };

    //! Valid values for ComponentSelector
    enum ComponentSelectorEnums
    {
        ComponentSelector_Confidence,  //!< The acquisition of confidence map of the acquired image is controlled - Applies to: blaze
        ComponentSelector_Intensity,  //!< The acquisition of intensity (monochrome or color) of the visible reflected light is controlled - Applies to: blaze
        ComponentSelector_Range  //!< The acquisition of range (distance) data is controlled - Applies to: blaze
    };

    //! Valid values for CounterEventActivation
    enum CounterEventActivationEnums
    {
        CounterEventActivation_AnyEdge,  //!< Trigger on the rising or falling edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventActivation_FallingEdge,  //!< Trigger on the falling edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventActivation_LevelHigh,  //!< Trigger is active as long as the selected source signal is on a logic high level - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventActivation_LevelLow,  //!< Trigger is active as long as the selected source signal is on a logic low level - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventActivation_RisingEdge  //!< Trigger on the rising edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for CounterEventSource
    enum CounterEventSourceEnums
    {
        CounterEventSource_AcquisitionActive,  //!< The selected counter counts the number of Acquisition Active signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_AcquisitionEnd,  //!< Counts the number of Acquisition End - Applies to: CameraLink and GigE
        CounterEventSource_AcquisitionStart,  //!< Counts the number of Acquisition Start - Applies to: CameraLink and GigE
        CounterEventSource_AcquisitionTrigger,  //!< Counts the number of Acquisition Trigger - Applies to: CameraLink and GigE
        CounterEventSource_Action1,  //!< The selected counter counts the number of action commands received for action signal 1 - Applies to: ace 2 GigE
        CounterEventSource_Action2,  //!< The selected counter counts the number of action commands received for action signal 2 - Applies to: ace 2 GigE
        CounterEventSource_Counter1Active,  //!< The selected counter counts the number of Counter 1 Active signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Counter1End,  //!< The selected counter counts the number of Counter 1 End signals - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Counter1Start,  //!< The selected counter counts the number of Counter 1 Start signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Counter2Active,  //!< The selected counter counts the number of Counter 2 Active signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Counter2End,  //!< The selected counter counts the number of Counter 2 End signals - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Counter2Start,  //!< The selected counter counts the number of Counter 2 Start signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Counter3End,  //!< The selected counter counts the number of counter 3 end events - Applies to: ace USB
        CounterEventSource_CxpTrigger0,  //!< The selected counter counts the number of CXP Trigger 0 signals - Applies to: boost CoaXPress
        CounterEventSource_CxpTrigger1,  //!< The selected counter counts the number of CXP Trigger 1 signals - Applies to: boost CoaXPress
        CounterEventSource_ExposureActive,  //!< The selected counter counts the number of Exposure Active signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_ExposureEnd,  //!< Counts the number of Exposure End - Applies to: CameraLink and GigE
        CounterEventSource_ExposureStart,  //!< Counts the number of Exposure Start - Applies to: CameraLink and GigE
        CounterEventSource_ExposureTriggerWait,  //!< The selected counter counts the number of Exposure Trigger Wait signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_FrameBurstActive,  //!< The selected counter counts the number of Frame Burst Active signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_FrameBurstTriggerWait,  //!< The selected counter counts the number of Frame Burst Trigger Wait signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_FrameEnd,  //!< Counts the number of Frame End - Applies to: CameraLink and GigE
        CounterEventSource_FrameStart,  //!< The selected counter counts the number of Frame Start events - Applies to: CameraLink, GigE and ace USB
        CounterEventSource_FrameTrigger,  //!< The selected counter counts the number of Frame Trigger events - Applies to: CameraLink, GigE and ace USB
        CounterEventSource_FrameTriggerWait,  //!< The selected counter counts the number of Frame Trigger Wait signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Line1,  //!< The selected counter counts the number of Line 1 signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Line2,  //!< The selected counter counts the number of Line 2 signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Line3,  //!< The selected counter counts the number of Line 3 signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Line4,  //!< The selected counter counts the number of Line 4 signals - Applies to: dart 2 USB
        CounterEventSource_LineEnd,  //!< Counts the number of Line End - Applies to: CameraLink and GigE
        CounterEventSource_LineStart,  //!< Counts the number of Line Start - Applies to: CameraLink and GigE
        CounterEventSource_LineTrigger,  //!< The selected counter counts the number of Line Trigger events - Applies to: CameraLink and GigE
        CounterEventSource_Off,  //!< The selected counter is disabled - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_PeriodicSignal1,  //!< The selected counter counts the number of Periodic Signal 1 signals - Applies to: ace 2 GigE
        CounterEventSource_SoftwareSignal1,  //!< The selected counter counts the number of Software Signal 1 signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_SoftwareSignal2,  //!< The selected counter counts the number of Software Signal 2 signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_SoftwareSignal3,  //!< The selected counter counts the number of Software Signal 3 signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Timer1Active,  //!< The selected counter counts the number of Timer 1 Active signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Timer1End,  //!< The selected counter counts the number of Timer 1 End signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Timer2Active,  //!< The selected counter counts the number of Timer 2 Active signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterEventSource_Timer2End  //!< The selected counter counts the number of Timer 2 End signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for CounterResetActivation
    enum CounterResetActivationEnums
    {
        CounterResetActivation_AnyEdge,  //!< Trigger on the rising or falling edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetActivation_FallingEdge,  //!< Trigger on the falling edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetActivation_LevelHigh,  //!< Trigger is active as long as the selected source signal is on a logic high level - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetActivation_LevelLow,  //!< Trigger is active as long as the selected source signal is on a logic low level - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetActivation_RisingEdge  //!< The counter is reset on the rising edge of the signal - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for CounterResetSource
    enum CounterResetSourceEnums
    {
        CounterResetSource_AcquisitionActive,  //!< The selected counter can be reset by an Acquisition Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Action1,  //!< The selected counter can be reset by an action command that is defined by action signal 1 - Applies to: ace 2 GigE
        CounterResetSource_Action2,  //!< The selected counter can be reset by an action command that is defined by action signal 2 - Applies to: ace 2 GigE
        CounterResetSource_CC1,  //!< The selected counter can be reset by a CC1 signal - Applies to: CameraLink and GigE
        CounterResetSource_CC2,  //!< The selected counter can be reset by a CC2 signal - Applies to: CameraLink and GigE
        CounterResetSource_CC3,  //!< The selected counter can be reset by a CC3 signal - Applies to: CameraLink and GigE
        CounterResetSource_CC4,  //!< The selected counter can be reset by a CC4 signal - Applies to: CameraLink and GigE
        CounterResetSource_Counter1Active,  //!< The selected counter can be reset by a Counter 1 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Counter1End,  //!< The selected counter can be reset by a Counter End 1 signal - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Counter1Start,  //!< The selected counter can be reset by a Counter 1 Start signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Counter2Active,  //!< The selected counter can be reset by a Counter 2 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Counter2End,  //!< The selected counter can be reset by a Counter 1 Start event - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Counter2Start,  //!< The selected counter can be reset by a Counter 2 Start signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Counter3End,  //!< The selected counter can be reset by a counter end 3 signal - Applies to: ace USB
        CounterResetSource_Counter4End,  //!< The selected counter can be reset by a counter end 4 signal - Applies to: ace USB
        CounterResetSource_CxpTrigger0,  //!< The selected counter can be reset by a CXP Trigger 0 signal - Applies to: boost CoaXPress
        CounterResetSource_CxpTrigger1,  //!< The selected counter can be reset by a CXP Trigger 1 signal - Applies to: boost CoaXPress
        CounterResetSource_ExposureActive,  //!< The selected counter can be reset by an Exposure Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_ExposureTriggerWait,  //!< The selected counter can be reset by an Exposure Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_FrameBurstActive,  //!< The selected counter can be reset by a Frame Burst Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_FrameBurstTriggerWait,  //!< The selected counter can be reset by a Frame Burst Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_FrameTriggerWait,  //!< The selected counter can be reset by a Frame Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Line1,  //!< The selected counter can be reset by a signal applied to Line 1 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Line2,  //!< The selected counter can be reset by a signal applied to Line 2 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Line3,  //!< The selected counter can be reset by a signal applied to Line 3 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Line4,  //!< The selected counter can be reset by a signal applied to Line 4 - Applies to: CameraLink, GigE, ace USB and dart 2 USB
        CounterResetSource_Line5,  //!< The selected counter can be reset by a signal applied to Line 5 - Applies to: CameraLink and GigE
        CounterResetSource_Line6,  //!< The selected counter can be reset by a signal applied to Line 6 - Applies to: CameraLink and GigE
        CounterResetSource_Line7,  //!< The selected counter can be reset by a signal applied to Line 7 - Applies to: CameraLink and GigE
        CounterResetSource_Line8,  //!< The selected counter can be reset by a signal applied to Line 8 - Applies to: CameraLink and GigE
        CounterResetSource_Off,  //!< The counter reset is disabled - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterResetSource_PeriodicSignal1,  //!< The selected counter can be reset by a Periodic Signal 1 signal - Applies to: ace 2 GigE
        CounterResetSource_Software,  //!< The selected counter can be reset by a software command - Applies to: CameraLink, GigE and ace USB
        CounterResetSource_SoftwareSignal1,  //!< The selected counter can be reset by a Software Signal 1 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_SoftwareSignal2,  //!< The selected counter can be reset by a Software Signal 2 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_SoftwareSignal3,  //!< The selected counter can be reset by a Software Signal 3 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Timer1Active,  //!< The selected counter can be reset by a Timer 1 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Timer1End,  //!< The selected counter can be reset by a Timer 1 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Timer2Active,  //!< The selected counter can be reset by a Timer 2 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_Timer2End,  //!< The selected counter can be reset by a Timer 2 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterResetSource_VInput1,  //!< Selects Virtual Input 1 as the source for counter reset - Applies to: CameraLink and GigE
        CounterResetSource_VInput2,  //!< Selects Virtual Input 2 as the source for counter reset - Applies to: CameraLink and GigE
        CounterResetSource_VInput3,  //!< Selects Virtual Input 3 as the source for counter reset - Applies to: CameraLink and GigE
        CounterResetSource_VInput4,  //!< Selects Virtual Input 4 as the source for counter reset - Applies to: CameraLink and GigE
        CounterResetSource_VInputDecActive  //!< Selects Virtual Input Decoder Active as the source for counter reset - Applies to: CameraLink and GigE
    };

    //! Valid values for CounterSelector
    enum CounterSelectorEnums
    {
        CounterSelector_Counter1,  //!< Counter 1 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterSelector_Counter2,  //!< Counter 2 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        CounterSelector_Counter3,  //!< Counter 3 can be configured - Applies to: CameraLink and GigE
        CounterSelector_Counter4  //!< Selects counter 4 for configuration - Applies to: CameraLink and GigE
    };

    //! Valid values for CounterStatus
    enum CounterStatusEnums
    {
        CounterStatus_CounterActive,  //!< The counter is waiting to be increased by the selected event source or is currently counting - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterStatus_CounterCompleted,  //!< The counter has reached its maximum value defined by the Counter Duration parameter - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterStatus_CounterTriggerWait  //!< The counter is waiting to be started - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for CounterTriggerActivation
    enum CounterTriggerActivationEnums
    {
        CounterTriggerActivation_AnyEdge,  //!< Trigger on the rising or falling edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerActivation_FallingEdge,  //!< Trigger on the falling edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerActivation_LevelHigh,  //!< Trigger is active as long as the selected source signal is on a logic high level - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerActivation_LevelLow,  //!< Trigger is active as long as the selected source signal is on a logic low level - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerActivation_RisingEdge  //!< Trigger on the rising edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for CounterTriggerSource
    enum CounterTriggerSourceEnums
    {
        CounterTriggerSource_AcquisitionActive,  //!< The selected counter can be started by an Acquisition Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Action1,  //!< The selected counter can be started by an action command that is defined by action signal 1 - Applies to: ace 2 GigE
        CounterTriggerSource_Action2,  //!< The selected counter can be started by an action command that is defined by action signal 2 - Applies to: ace 2 GigE
        CounterTriggerSource_Counter1Active,  //!< The selected counter can be started by a Counter 1 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Counter1End,  //!< The selected counter can be started by a Counter 1 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Counter1Start,  //!< The selected counter can be started by a Counter 1 Start signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Counter2Active,  //!< The selected counter can be started by a Counter 2 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Counter2End,  //!< The selected counter can be started by a Counter 2 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Counter2Start,  //!< The selected counter can be started by a Counter 2 Start signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_CxpTrigger0,  //!< The selected counter can be started by a CXP Trigger 0 signal - Applies to: boost CoaXPress
        CounterTriggerSource_CxpTrigger1,  //!< The selected counter can be started by a CXP Trigger 1 signal - Applies to: boost CoaXPress
        CounterTriggerSource_ExposureActive,  //!< The selected counter can be started by an Exposure Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_ExposureTriggerWait,  //!< The selected counter can be started by an Exposure Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_FrameBurstActive,  //!< The selected counter can be started by a Frame Burst Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_FrameBurstTriggerWait,  //!< The selected counter can be started by a Frame Burst Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_FrameTriggerWait,  //!< The selected counter can be started by a Frame Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Line1,  //!< The selected counter can be started by a Line 1 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Line2,  //!< The selected counter can be started by a Line 2 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Line3,  //!< The selected counter can be started by a Line 3 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Line4,  //!< The selected counter can be started by a Line 4 signal - Applies to: dart 2 USB
        CounterTriggerSource_Off,  //!< The selected counter is disabled and can't be started - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_PeriodicSignal1,  //!< The selected counter can be started by a Periodic Signal 1 signal - Applies to: ace 2 GigE
        CounterTriggerSource_SoftwareSignal1,  //!< The selected counter can be started by a Software Signal 1 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_SoftwareSignal2,  //!< The selected counter can be started by a Software Signal 2 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_SoftwareSignal3,  //!< The selected counter can be started by a Software Signal 3 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Timer1Active,  //!< The selected counter can be started by a Timer 1 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Timer1End,  //!< The selected counter can be started by a Timer 1 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Timer2Active,  //!< The selected counter can be started by a Timer 2 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        CounterTriggerSource_Timer2End  //!< The selected counter can be started by a Timer 2 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for CxpConnectionTestMode
    enum CxpConnectionTestModeEnums
    {
        CxpConnectionTestMode_Mode1,  //!< Test mode is enabled - Applies to: boost CoaXPress
        CxpConnectionTestMode_Off  //!< Test mode is disabled - Applies to: boost CoaXPress
    };

    //! Valid values for CxpErrorCounterSelector
    enum CxpErrorCounterSelectorEnums
    {
        CxpErrorCounterSelector_ConnectionLockLoss,  //!< The Connection Lock Loss error counter can be read or reset - Applies to: boost CoaXPress
        CxpErrorCounterSelector_ControlPacketCrc,  //!< The Control Packet CRC error counter can be read or reset - Applies to: boost CoaXPress
        CxpErrorCounterSelector_DuplicatedCharactersUncorrected  //!< The Duplicated Characters Uncorrected error counter can be read or reset - Applies to: boost CoaXPress
    };

    //! Valid values for CxpErrorCounterStatus
    enum CxpErrorCounterStatusEnums
    {
        CxpErrorCounterStatus_CounterActive  //!< The counter is actively counting errors - Applies to: boost CoaXPress
    };

    //! Valid values for CxpLinkConfiguration
    enum CxpLinkConfigurationEnums
    {
        CxpLinkConfiguration_Auto,  //!< The link configuration is set to automatic discovery - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP10_X1,  //!< The link configuration is set to 1 connection operating at CXP-10 speed (10 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP10_X2,  //!< The link configuration is set to 2 connections operating at CXP-10 speed (10 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP12_X1,  //!< The link configuration is set to 1 connection operating at CXP-12 speed (12 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP12_X2,  //!< The link configuration is set to 2 connections operating at CXP-12 speed (12 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP2_X1,  //!< The link configuration is set to 1 connection operating at CXP-2 speed (2 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP2_X2,  //!< The link configuration is set to 2 connections operating at CXP-2 speed (2 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP3_X1,  //!< The link configuration is set to 1 connection operating at CXP-3 speed (3 125 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP3_X2,  //!< The link configuration is set to 2 connections operating at CXP-3 speed (3 125 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP5_X1,  //!< The link configuration is set to 1 connection operating at CXP-5 speed (5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP5_X2,  //!< The link configuration is set to 2 connections operating at CXP-5 speed (5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP6_X1,  //!< The link configuration is set to 1 connection operating at CXP-6 speed (6 25 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfiguration_CXP6_X2  //!< The link configuration is set to 2 connections operating at CXP-6 speed (6 25 Gbps) - Applies to: boost CoaXPress
    };

    //! Valid values for CxpLinkConfigurationPreferred
    enum CxpLinkConfigurationPreferredEnums
    {
        CxpLinkConfigurationPreferred_Auto,  //!< The link configuration is set to automatic discovery - Applies to: boost CoaXPress
        CxpLinkConfigurationPreferred_CXP10_X1,  //!< The link configuration is set to 1 connection operating at CXP-10 speed (10 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationPreferred_CXP12_X1,  //!< The link configuration is set to 1 connection operating at CXP-12 speed (12 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationPreferred_CXP2_X1,  //!< The link configuration is set to 1 connection operating at CXP-2 speed (2 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationPreferred_CXP3_X1,  //!< The link configuration is set to 1 connection operating at CXP-3 speed (3 125 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationPreferred_CXP5_X1,  //!< The link configuration is set to 1 connection operating at CXP-5 speed (5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationPreferred_CXP6_X1  //!< The link configuration is set to 1 connection operating at CXP-6 speed (6 25 Gbps) - Applies to: boost CoaXPress
    };

    //! Valid values for CxpLinkConfigurationStatus
    enum CxpLinkConfigurationStatusEnums
    {
        CxpLinkConfigurationStatus_Auto,  //!< The link configuration is set to automatic discovery - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP10_X1,  //!< The link configuration is set to 1 connection operating at CXP-10 speed (10 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP10_X2,  //!< The link configuration is set to 2 connections operating at CXP-10 speed (10 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP12_X1,  //!< The link configuration is set to 1 connection operating at CXP-12 speed (12 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP12_X2,  //!< The link configuration is set to 2 connections operating at CXP-12 speed (12 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP2_X1,  //!< The link configuration is set to 1 connection operating at CXP-2 speed (2 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP2_X2,  //!< The link configuration is set to 2 connections operating at CXP-2 speed (2 5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP3_X1,  //!< The link configuration is set to 1 connection operating at CXP-3 speed (3 125 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP3_X2,  //!< The link configuration is set to 2 connections operating at CXP-3 speed (3 125 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP5_X1,  //!< The link configuration is set to 1 connection operating at CXP-5 speed (5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP5_X2,  //!< The link configuration is set to 2 connections operating at CXP-5 speed (5 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP6_X1,  //!< The link configuration is set to 1 connection operating at CXP-6 speed (6 25 Gbps) - Applies to: boost CoaXPress
        CxpLinkConfigurationStatus_CXP6_X2  //!< The link configuration is set to 2 connections operating at CXP-6 speed (6 25 Gbps) - Applies to: boost CoaXPress
    };

    //! Valid values for CxpSendReceiveSelector
    enum CxpSendReceiveSelectorEnums
    {
        CxpSendReceiveSelector_Receive,  //!< The receive features can be configured - Applies to: boost CoaXPress
        CxpSendReceiveSelector_Send  //!< The send features can be configured - Applies to: boost CoaXPress
    };

    //! Valid values for DefectPixelCorrectionMode
    enum DefectPixelCorrectionModeEnums
    {
        DefectPixelCorrectionMode_Off,  //!< Defect pixel correction is disabled - Applies to: dart BCON, dart USB and pulse USB
        DefectPixelCorrectionMode_On,  //!< Defect pixel correction is enabled - Applies to: dart BCON, dart USB and pulse USB
        DefectPixelCorrectionMode_StaticOnly  //!< Only static defect pixel correction is enabled - Applies to: dart BCON, dart USB and pulse USB
    };

    //! Valid values for DemosaicingMode
    enum DemosaicingModeEnums
    {
        DemosaicingMode_BaslerPGI,  //!< Demosaicing is performed using the Basler PGI algorithm - Applies to: GigE and ace USB
        DemosaicingMode_Simple  //!< Demosaicing is performed using a simple demosaicing algorithm - Applies to: GigE and ace USB
    };

    //! Valid values for DeviceCharacterSet
    enum DeviceCharacterSetEnums
    {
        DeviceCharacterSet_UTF8  //!< The strings of the device's bootstrap registers use the UTF-8 character set - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for DeviceClockSelector
    enum DeviceClockSelectorEnums
    {
        DeviceClockSelector_Bcon  //!< The BCON camera clock is selected - Applies to: dart BCON
    };

    //! Valid values for DeviceIndicatorMode
    enum DeviceIndicatorModeEnums
    {
        DeviceIndicatorMode_Active,  //!< The status LED of the camera is turned on - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        DeviceIndicatorMode_ErrorStatus,  //!< The camera's status LED is inactive unless an error occurs - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        DeviceIndicatorMode_Inactive  //!< The status LED of the camera is turned off - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
    };

    //! Valid values for DeviceLinkThroughputLimitMode
    enum DeviceLinkThroughputLimitModeEnums
    {
        DeviceLinkThroughputLimitMode_Off,  //!< The Device Link Throughput Limit parameter is disabled - Applies to: ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB
        DeviceLinkThroughputLimitMode_On  //!< The Device Link Throughput Limit parameter is enabled - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB
    };

    //! Valid values for DeviceRegistersEndianness
    enum DeviceRegistersEndiannessEnums
    {
        DeviceRegistersEndianness_Big,  //!< The endianness of the device's registers is big-endian - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        DeviceRegistersEndianness_Little  //!< The endianness of the device's registers is little-endian - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for DeviceScanType
    enum DeviceScanTypeEnums
    {
        DeviceScanType_Areascan,  //!< The camera has an area scan sensor - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        DeviceScanType_Areascan3D,  //!< Device outputs 2D range image - Applies to: blaze
        DeviceScanType_Linescan,  //!< The camera has a line scan sensor - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress and dart 2 USB
        DeviceScanType_Linescan3D  //!< Device outputs 1D range image - Applies to: blaze
    };

    //! Valid values for DeviceTLType
    enum DeviceTLTypeEnums
    {
        DeviceTLType_CoaXPress,  //!< The device provides a CoaXPress transport layer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        DeviceTLType_GigEVision,  //!< The device provides a GigE Vision transport layer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        DeviceTLType_USB3Vision  //!< The device provides a USB3 Vision transport layer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for DeviceTapGeometry
    enum DeviceTapGeometryEnums
    {
        DeviceTapGeometry_Geometry_1X_1Y  //!< The tap geometry is set to 1 zone in horizontal direction with one tap and 1 zone in vertical direction with 1 tap - Applies to: boost CoaXPress
    };

    //! Valid values for DeviceTemperatureSelector
    enum DeviceTemperatureSelectorEnums
    {
        DeviceTemperatureSelector_CPU,  //!< Temperature of the device's CPU - Applies to: blaze
        DeviceTemperatureSelector_Camera,  //!< The temperature is measured on the camera housing - Applies to: boost CoaXPress
        DeviceTemperatureSelector_Coreboard,  //!< The temperature is measured on the core board - Applies to: ace 2 GigE, ace 2 USB and ace USB
        DeviceTemperatureSelector_FpgaCore,  //!< The temperature is measured on the FPGA board - Applies to: boost CoaXPress and dart 2 USB
        DeviceTemperatureSelector_Framegrabberboard,  //!< The temperature is measured on the frame grabber board - Applies to: ace USB
        DeviceTemperatureSelector_Illumination,  //!< Temperature of the device's illumination board - Applies to: blaze
        DeviceTemperatureSelector_Sensor,  //!< The temperature is measured on the image sensor - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        DeviceTemperatureSelector_Sensorboard  //!< The temperature is measured on the sensor board - Applies to: ace USB and blaze
    };

    //! Valid values for DeviceType
    enum DeviceTypeEnums
    {
        DeviceType_Peripheral,  //!< Controllable device (with no data stream handling) - Applies to: blaze
        DeviceType_Receiver,  //!< Data stream receiver device - Applies to: blaze
        DeviceType_Transceiver,  //!< Data stream receiver and transmitter device - Applies to: blaze
        DeviceType_Transmitter  //!< Data stream transmitter device - Applies to: blaze
    };

    //! Valid values for EventNotification
    enum EventNotificationEnums
    {
        EventNotification_GenICamEvent,  //!< Event notifications are enabled and the notification type is set to GenICam - Applies to: GigE
        EventNotification_Off,  //!< Event notifications are disabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        EventNotification_On,  //!< Event notifications are enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        EventNotification_Once  //!< Applies to: ace 2 GigE and ace 2 USB
    };

    //! Valid values for EventSelector
    enum EventSelectorEnums
    {
        EventSelector_AcquisitionStart,  //!< Event notifications for the Acquisition Start event can be enabled - Applies to: GigE
        EventSelector_AcquisitionStartOvertrigger,  //!< Event notifications for the Acquisition Start Overtrigger event can be enabled - Applies to: GigE
        EventSelector_AcquisitionStartWait,  //!< Event notifications for the Acquisition Start Wait event can be enabled - Applies to: GigE
        EventSelector_AcquisitionWait,  //!< Event notifications for the Acquisition Wait event can be enabled - Applies to: GigE
        EventSelector_ActionLate,  //!< Event notifications for the Action Late event can be enabled - Applies to: GigE and ace 2 GigE
        EventSelector_CriticalTemperature,  //!< Event notifications for the Critical Temperature event can be enabled - Applies to: GigE and ace USB
        EventSelector_EventOverrun,  //!< Event notifications for the Event Overrun event can be enabled - Applies to: GigE
        EventSelector_ExposureEnd,  //!< Event notifications for the Exposure End event can be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        EventSelector_FrameBufferOverrun,  //!< Event notifications for the Frame Buffer Overrun event can be enabled - Applies to: ace 2 GigE and ace 2 USB
        EventSelector_FrameBurstStart,  //!< Event notifications for the Frame Burst Start event can be enabled - Applies to: ace USB
        EventSelector_FrameBurstStartOvertrigger,  //!< Event notifications for the Frame Burst Start Overtrigger event can be enabled - Applies to: ace USB
        EventSelector_FrameBurstStartWait,  //!< Event notifications for the Frame Burst Start Wait event can be enabled - Applies to: ace USB
        EventSelector_FrameStart,  //!< Event notifications for the Frame Start event can be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB
        EventSelector_FrameStartOvertrigger,  //!< Event notifications for the Frame Start Overtrigger event can be enabled - Applies to: GigE and ace USB
        EventSelector_FrameStartWait,  //!< Event notifications for the Frame Start Wait event can be enabled - Applies to: GigE and ace USB
        EventSelector_FrameTimeout,  //!< Event notifications for the Frame Timeout event can be enabled - Applies to: GigE
        EventSelector_FrameTriggerMissed,  //!< Event notifications for the Frame Trigger Missed event can be enabled - Applies to: ace 2 GigE and ace 2 USB
        EventSelector_FrameWait,  //!< Event notifications for the Frame Wait event can be enabled - Applies to: GigE
        EventSelector_Line1RisingEdge,  //!< Applies to: GigE
        EventSelector_Line2RisingEdge,  //!< Applies to: GigE
        EventSelector_Line3RisingEdge,  //!< Applies to: GigE
        EventSelector_Line4RisingEdge,  //!< Applies to: GigE
        EventSelector_LineStartOvertrigger,  //!< Event notifications for the Line Start Overtrigger event can be enabled - Applies to: GigE
        EventSelector_OverTemperature,  //!< Event notifications for the Over Temperature event can be enabled - Applies to: GigE and ace USB
        EventSelector_Overrun,  //!< Event notifications for the Overrun event can be enabled - Applies to: ace 2 GigE and ace 2 USB
        EventSelector_TemperatureStatusChanged,  //!< Event notifications for the Temperature Status Changed event can be enabled - Applies to: ace 2 GigE and ace 2 USB
        EventSelector_Test,  //!< Event notifications for the Test event can be enabled - Applies to: ace 2 GigE and ace 2 USB
        EventSelector_VirtualLine1RisingEdge,  //!< Applies to: GigE
        EventSelector_VirtualLine2RisingEdge,  //!< Applies to: GigE
        EventSelector_VirtualLine3RisingEdge,  //!< Applies to: GigE
        EventSelector_VirtualLine4RisingEdge  //!< Applies to: GigE
    };

    //! Valid values for EventTemperatureStatusChangedStatus
    enum EventTemperatureStatusChangedStatusEnums
    {
        EventTemperatureStatusChangedStatus_Critical,  //!< The temperature status changed to Critical - Applies to: ace 2 GigE and ace 2 USB
        EventTemperatureStatusChangedStatus_Error,  //!< The temperature status changed to Error - Applies to: ace 2 GigE and ace 2 USB
        EventTemperatureStatusChangedStatus_Ok  //!< The temperature status changed to Ok - Applies to: ace 2 GigE and ace 2 USB
    };

    //! Valid values for ExpertFeatureAccessSelector
    enum ExpertFeatureAccessSelectorEnums
    {
        ExpertFeatureAccessSelector_ExpertFeature1,  //!< Expert Feature 1 can be configured - Applies to: CameraLink, GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature10,  //!< Expert Feature 10 can be configured - Applies to: GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature11,  //!< Expert feature 11 can be configured - Applies to: GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature1_Legacy,  //!< Expert Feature 1 (Legacy) can be configured - Applies to: CameraLink and GigE
        ExpertFeatureAccessSelector_ExpertFeature2,  //!< Expert Feature 2 can be configured - Applies to: CameraLink, GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature3,  //!< Expert Feature 3 can be configured - Applies to: CameraLink, GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature4,  //!< Expert Feature 4 can be configured - Applies to: CameraLink, GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature5,  //!< Expert Feature 5 can be configured - Applies to: CameraLink, GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature6,  //!< Expert Feature 6 can be configured - Applies to: CameraLink, GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature7,  //!< Expert Feature 7 can be configured - Applies to: CameraLink, GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature8,  //!< Expert Feature 8 can be configured - Applies to: GigE and ace USB
        ExpertFeatureAccessSelector_ExpertFeature9  //!< Expert Feature 9 can be configured - Applies to: GigE and ace USB
    };

    //! Valid values for ExposureAuto
    enum ExposureAutoEnums
    {
        ExposureAuto_Continuous,  //!< The exposure time is adjusted continuously while images are being acquired - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        ExposureAuto_Off,  //!< Automatic exposure time adjustment is disabled - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        ExposureAuto_Once  //!< The exposure time is adjusted automatically to reach the specified target value - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for ExposureMode
    enum ExposureModeEnums
    {
        ExposureMode_Off,  //!< Sets the exposure mode to off - Applies to: CameraLink and GigE
        ExposureMode_Timed,  //!< The exposure mode is set to Timed - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        ExposureMode_TriggerControlled,  //!< The exposure mode is set to Trigger Controlled - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        ExposureMode_TriggerWidth  //!< The exposure mode is set to Trigger Width - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
    };

    //! Valid values for ExposureOverlapTimeMode
    enum ExposureOverlapTimeModeEnums
    {
        ExposureOverlapTimeMode_Automatic,  //!< The camera automatically uses the optimum overlap time for each acquisition - Applies to: GigE and ace USB
        ExposureOverlapTimeMode_Manual  //!< The user can manually set the overlap time for each acquisition - Applies to: GigE and ace USB
    };

    //! Valid values for ExposureTimeMode
    enum ExposureTimeModeEnums
    {
        ExposureTimeMode_Standard,  //!< The exposure time mode is set to Standard - Applies to: GigE and ace USB
        ExposureTimeMode_UltraShort  //!< The exposure time mode is set to Ultra Short - Applies to: GigE and ace USB
    };

    //! Valid values for FeatureSet
    enum FeatureSetEnums
    {
        FeatureSet_Basic,  //!< The basic feature set is made available - Applies to: CameraLink and GigE
        FeatureSet_Full  //!< The full feature set is made available - Applies to: CameraLink and GigE
    };

    //! Valid values for FieldOutputMode
    enum FieldOutputModeEnums
    {
        FieldOutputMode_ConcatenatedNewFields,  //!< Sets the mode to output a frame consisting of field 0 in the upper half and field 1 in the lower half of the frame - Applies to: CameraLink and GigE
        FieldOutputMode_DeinterlacedNewFields,  //!< Sets the mode to output a frame generated by deinterlacing field 0 and field 1 using the deinterlacer selected by feature Deinterlacer   - Applies to: CameraLink and GigE
        FieldOutputMode_Field0,  //!< Sets the mode to only output field 0 - Applies to: CameraLink and GigE
        FieldOutputMode_Field0First,  //!< Sets the mode to only output field 0 and field 1 in single frames  Starting with field 0 - Applies to: CameraLink and GigE
        FieldOutputMode_Field1  //!< Sets the mode to only output field 1 - Applies to: CameraLink and GigE
    };

    //! Valid values for FileOpenMode
    enum FileOpenModeEnums
    {
        FileOpenMode_Read,  //!< Files are opened in read-only mode - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        FileOpenMode_Write  //!< Files are opened in write-only mode - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for FileOperationSelector
    enum FileOperationSelectorEnums
    {
        FileOperationSelector_Close,  //!< The currently selected file can be closed - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        FileOperationSelector_Open,  //!< The currently selected file can be opened - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        FileOperationSelector_Read,  //!< The currently selected file can be read - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        FileOperationSelector_Write  //!< The currently selected file can be written to - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for FileOperationStatus
    enum FileOperationStatusEnums
    {
        FileOperationStatus_Failure,  //!< The file operation has failed - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        FileOperationStatus_Success  //!< The file operation was successful - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for FileSelector
    enum FileSelectorEnums
    {
        FileSelector_BootUpdate,  //!< The Boot Firmware Update file is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        FileSelector_BootUpdatePackage,  //!< The Boot Firmware Update Package file is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        FileSelector_ExpertFeature7File,  //!< The Expert Feature 7 File file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_FirmwareUpdate,  //!< The Firmware Update file is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        FileSelector_FirmwareUpdatePackage,  //!< The Firmware Update Package file is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        FileSelector_None,  //!< No file is selected - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        FileSelector_UserData,  //!< The User Data file is selected - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        FileSelector_UserGainShading1,  //!< The User Gain Shading 1 file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_UserGainShading2,  //!< The User Gain Shading 2 file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_UserOffsetShading1,  //!< The User Offset Shading 1 file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_UserOffsetShading2,  //!< The User Offset Shading 2 file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_UserSet1,  //!< The User Set 1 file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_UserSet2,  //!< The User Set 2 file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_UserSet3,  //!< The User Set 3 file is selected - Applies to: CameraLink, GigE and ace USB
        FileSelector_VignettingCorrection  //!< The Vignetting Correction file is selected - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for FrequencyConverterInputSource
    enum FrequencyConverterInputSourceEnums
    {
        FrequencyConverterInputSource_CC1,  //!< CC1 is selected as the source signal for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_CC2,  //!< CC2 is selected as the source signal for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_CC3,  //!< CC3 is selected as the source signal for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_CC4,  //!< CC4 is selected as the source signal for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line1,  //!< Line 1 is selected as the input source for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line2,  //!< Line 2 is selected as the input source for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line3,  //!< Line 3 is selected as the input source for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line4,  //!< Line 4 is selected as the input source for the frequency converter module - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line5,  //!< Selects line 5 as the input source - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line6,  //!< Selects line 6 as the input source   - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line7,  //!< Selects line 7 as the input source - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_Line8,  //!< Selects line 8 as the input source - Applies to: CameraLink and GigE
        FrequencyConverterInputSource_ShaftEncoderModuleOut  //!< The output of the shaft encoder module is selected as the input source for the frequency converter module - Applies to: CameraLink and GigE
    };

    //! Valid values for FrequencyConverterSignalAlignment
    enum FrequencyConverterSignalAlignmentEnums
    {
        FrequencyConverterSignalAlignment_FallingEdge,  //!< For the falling edge of each received signal, a falling edge of a generated signal is provided - Applies to: CameraLink and GigE
        FrequencyConverterSignalAlignment_RisingEdge  //!< For the rising edge of each received signal, a rising edge of a generated signal is provided - Applies to: CameraLink and GigE
    };

    //! Valid values for GainAuto
    enum GainAutoEnums
    {
        GainAuto_Continuous,  //!< The gain is adjusted continuously while images are being acquired - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        GainAuto_Off,  //!< Automatic gain adjustment is disabled - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        GainAuto_Once  //!< The gain is adjusted automatically to reach the specifed target value - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for GainSelector
    enum GainSelectorEnums
    {
        GainSelector_All,  //!< Changes to the gain will be applied universally - Applies to: CameraLink, GigE, ace USB, dart BCON, dart USB and pulse USB
        GainSelector_AnalogAll,  //!< Changes to the gain will be applied to all analog gain parameters - Applies to: CameraLink, GigE and ace USB
        GainSelector_Blue,  //!< Selects the blue gain control for adjustment - Applies to: CameraLink and GigE
        GainSelector_DigitalAll,  //!< Changes to the gain will be applied to all digital gain parameters - Applies to: CameraLink, GigE and ace USB
        GainSelector_Green,  //!< Selects the green gain control for adjustment - Applies to: CameraLink and GigE
        GainSelector_Red,  //!< Selects the red gain control for adjustment - Applies to: CameraLink and GigE
        GainSelector_Tap1,  //!< Changes to the gain will be applied to tap 1 - Applies to: CameraLink and GigE
        GainSelector_Tap2,  //!< Changes to the gain will be applied to tap 2 - Applies to: CameraLink and GigE
        GainSelector_Tap3,  //!< Changes to the gain will be applied to tap 3 - Applies to: CameraLink and GigE
        GainSelector_Tap4  //!< Changes to the gain will be applied to tap 4 - Applies to: CameraLink and GigE
    };

    //! Valid values for GammaSelector
    enum GammaSelectorEnums
    {
        GammaSelector_User,  //!< The gamma curve can be configured by the user - Applies to: CameraLink and GigE
        GammaSelector_sRGB  //!< The gamma curve is set to a fixed sRGB curve - Applies to: CameraLink and GigE
    };

    //! Valid values for GenDCStreamingMode
    enum GenDCStreamingModeEnums
    {
        GenDCStreamingMode_Automatic,  //!< The device will automatically choose in which format it streams its data - Applies to: blaze
        GenDCStreamingMode_Off,  //!< The device will only stream data in its native format - Applies to: blaze
        GenDCStreamingMode_On  //!< The device will stream all its data in the generic GenDC format - Applies to: blaze
    };

    //! Valid values for GenDCStreamingStatus
    enum GenDCStreamingStatusEnums
    {
        GenDCStreamingStatus_Off,  //!< The device will only stream data in its native format - Applies to: blaze
        GenDCStreamingStatus_On  //!< The device will stream all its data in the generic GenDC format - Applies to: blaze
    };

    //! Valid values for GevCCP
    enum GevCCPEnums
    {
        GevCCP_Control,  //!< The control channel privilege is set to Control - Applies to: GigE
        GevCCP_Exclusive,  //!< The control channel privilege is set to Exclusive - Applies to: GigE
        GevCCP_ExclusiveControl  //!< The control channel privilege is set to Exclusive Control - Applies to: GigE
    };

    //! Valid values for GevGVSPExtendedIDMode
    enum GevGVSPExtendedIDModeEnums
    {
        GevGVSPExtendedIDMode_Off,  //!< The Extended ID mode is switched off - Applies to: GigE
        GevGVSPExtendedIDMode_On  //!< The Extended ID mode is switched on - Applies to: GigE
    };

    //! Valid values for GevIEEE1588Status
    enum GevIEEE1588StatusEnums
    {
        GevIEEE1588Status_Disabled,  //!< The port is in the Disabled state - Applies to: GigE
        GevIEEE1588Status_Faulty,  //!< The port is in the Faulty state - Applies to: GigE
        GevIEEE1588Status_Initializing,  //!< The port is in the Initializing state - Applies to: GigE
        GevIEEE1588Status_Listening,  //!< The port is in the Listening state - Applies to: GigE
        GevIEEE1588Status_Master,  //!< The port is in the Master state - Applies to: GigE
        GevIEEE1588Status_Passive,  //!< The port is in the Passive state - Applies to: GigE
        GevIEEE1588Status_PreMaster,  //!< The port is in the PreMaster state - Applies to: GigE
        GevIEEE1588Status_Slave,  //!< The port is in the Slave state - Applies to: GigE
        GevIEEE1588Status_Uncalibrated,  //!< The port is in the Uncalibrated state - Applies to: GigE
        GevIEEE1588Status_Undefined  //!< The port is in an undefined state - Applies to: GigE
    };

    //! Valid values for GevIEEE1588StatusLatched
    enum GevIEEE1588StatusLatchedEnums
    {
        GevIEEE1588StatusLatched_Disabled,  //!< The port is in the Disabled state - Applies to: GigE
        GevIEEE1588StatusLatched_Faulty,  //!< The port is in the Faulty state - Applies to: GigE
        GevIEEE1588StatusLatched_Initializing,  //!< The port is in the Initializing state - Applies to: GigE
        GevIEEE1588StatusLatched_Listening,  //!< The port is in the Listening state - Applies to: GigE
        GevIEEE1588StatusLatched_Master,  //!< The port is in the Master state - Applies to: GigE
        GevIEEE1588StatusLatched_Passive,  //!< The port is in the Passive state - Applies to: GigE
        GevIEEE1588StatusLatched_PreMaster,  //!< The port is in the PreMaster state - Applies to: GigE
        GevIEEE1588StatusLatched_Slave,  //!< The port is in the Slave state - Applies to: GigE
        GevIEEE1588StatusLatched_Uncalibrated,  //!< The port is in the Uncalibrated state - Applies to: GigE
        GevIEEE1588StatusLatched_Undefined  //!< The port is in an undefined state - Applies to: GigE
    };

    //! Valid values for GevInterfaceSelector
    enum GevInterfaceSelectorEnums
    {
        GevInterfaceSelector_NetworkInterface0  //!< Network interface 0 can be configured - Applies to: GigE
    };

    //! Valid values for GevStreamChannelSelector
    enum GevStreamChannelSelectorEnums
    {
        GevStreamChannelSelector_StreamChannel0  //!< Stream channel 0 can be configured - Applies to: GigE
    };

    //! Valid values for ImageCompressionMode
    enum ImageCompressionModeEnums
    {
        ImageCompressionMode_BaslerCompressionBeyond,  //!< Images are compressed using the Compression Beyond feature - Applies to: ace 2 GigE and ace 2 USB
        ImageCompressionMode_Off  //!< Image compression is disabled - Applies to: ace 2 GigE and ace 2 USB
    };

    //! Valid values for ImageCompressionRateOption
    enum ImageCompressionRateOptionEnums
    {
        ImageCompressionRateOption_FixRatio,  //!< The camera compresses acquired images  If lossless compression can't be achieved, image quality is reduced - Applies to: ace 2 GigE and ace 2 USB
        ImageCompressionRateOption_Lossless  //!< The camera uses lossless compression - Applies to: ace 2 GigE and ace 2 USB
    };

    //! Valid values for ImageFileMode
    enum ImageFileModeEnums
    {
        ImageFileMode_Off,  //!< Sets the mode to off - Applies to: CamEmu
        ImageFileMode_On  //!< Sets the mode to on - Applies to: CamEmu
    };

    //! Valid values for IntensityCalculation
    enum IntensityCalculationEnums
    {
        IntensityCalculation_Method1,  //!< Method 1 is used to calculate the intensity image - Applies to: blaze
        IntensityCalculation_Method2  //!< Method 2 is used to calculate the intensity image   - Applies to: blaze
    };

    //! Valid values for InterlacedIntegrationMode
    enum InterlacedIntegrationModeEnums
    {
        InterlacedIntegrationMode_FieldIntegration,  //!< Sets the integration mode to field integration - Applies to: CameraLink and GigE
        InterlacedIntegrationMode_FrameIntegration  //!< Sets the integration mode to frame integration - Applies to: CameraLink and GigE
    };

    //! Valid values for LUTSelector
    enum LUTSelectorEnums
    {
        LUTSelector_Luminance  //!< The luminance lookup table can be configured - Applies to: CameraLink, GigE and ace USB
    };

    //! Valid values for LastError
    enum LastErrorEnums
    {
        LastError_Illumination,  //!< Indicates a problem with the VCSELs - Applies to: blaze
        LastError_InsufficientTriggerWidth,  //!< The trigger width was too short - Applies to: CameraLink and GigE
        LastError_InvalidParameter,  //!< A parameter was set to an invalid value - Applies to: CameraLink and GigE
        LastError_NoError,  //!< No error was detected - Applies to: CameraLink, GigE and blaze
        LastError_OverTemperature,  //!< An over temperature state has been detected - Applies to: CameraLink, GigE and blaze
        LastError_Overtrigger,  //!< The camera was overtriggered - Applies to: CameraLink and GigE
        LastError_PowerFailure,  //!< The power supply is not sufficient - Applies to: CameraLink and GigE
        LastError_UserDefPixFailure,  //!< An error was detected while loading user defect pixel data - Applies to: CameraLink and GigE
        LastError_Userset  //!< An error was detected while loading a user set - Applies to: CameraLink and GigE
    };

    //! Valid values for LegacyBinningVertical
    enum LegacyBinningVerticalEnums
    {
        LegacyBinningVertical_Off,  //!< Vertical binning is disabled - Applies to: CameraLink and GigE
        LegacyBinningVertical_Two_Rows  //!< Vertical binning is set to 2 rows - Applies to: CameraLink and GigE
    };

    //! Valid values for LightSourcePreset
    enum LightSourcePresetEnums
    {
        LightSourcePreset_Daylight5000K,  //!< The light source preset for image acquisitions with daylight of 5000 K is selected - Applies to: ace USB, dart BCON, dart USB and pulse USB
        LightSourcePreset_Daylight6500K,  //!< The light source preset for image acquisitions with daylight of 6500 K is selected - Applies to: ace USB, dart BCON, dart USB and pulse USB
        LightSourcePreset_MicroscopeLED4500K,  //!< The light source preset for image acquisitions with microscope LED illumination of 4500 K is set - Applies to: ace USB
        LightSourcePreset_MicroscopeLED5500K,  //!< The light source preset for image acquisitions with microscope LED illumination of 5500 K is set - Applies to: ace USB
        LightSourcePreset_MicroscopeLED6000K,  //!< The light source preset for image acquisitions with microscope LED illumination of 6000 K is set - Applies to: ace USB
        LightSourcePreset_Off,  //!< No light source preset is selected - Applies to: ace USB, dart BCON, dart USB and pulse USB
        LightSourcePreset_Tungsten2800K  //!< The light source preset for image acquisitions with tungsten incandescent light (2800 K) is selected - Applies to: ace USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for LightSourceSelector
    enum LightSourceSelectorEnums
    {
        LightSourceSelector_Custom,  //!< The color transformation matrix can be customized - Applies to: CameraLink and GigE
        LightSourceSelector_Daylight,  //!< The color transformation matrix is optimized for image acquisitions with daylight of 5000 K - Applies to: CameraLink and GigE
        LightSourceSelector_Daylight6500K,  //!< The color transformation matrix is optimized for image acquisitions with daylight of 6500 K - Applies to: CameraLink and GigE
        LightSourceSelector_LightSource0,  //!< The color transformation matrix is optimized for image acquisitions with a custom light source 0 - Applies to: CameraLink and GigE
        LightSourceSelector_LightSource1,  //!< The color transformation matrix is optimized for image acquisitions with a custom light source 1 - Applies to: CameraLink and GigE
        LightSourceSelector_MicroscopeLED4500K,  //!< The light source preset for image acquisitions with microscope LED illumination of 4500 K is set - Applies to: GigE
        LightSourceSelector_MicroscopeLED5500K,  //!< The light source preset for image acquisitions with microscope LED illumination of 5500 K is set - Applies to: GigE
        LightSourceSelector_MicroscopeLED6000K,  //!< The light source preset for image acquisitions with microscope LED illumination of 6000 K is set - Applies to: GigE
        LightSourceSelector_Off,  //!< No color transformation for a specific light source is performed - Applies to: CameraLink and GigE
        LightSourceSelector_Tungsten  //!< The color transformation matrix is optimized for image acquisition with tungsten incandescent light (3100 K) - Applies to: CameraLink and GigE
    };

    //! Valid values for LineFormat
    enum LineFormatEnums
    {
        LineFormat_LVDS,  //!< The line is currently accepting or sending LVDS level signals - Applies to: CameraLink, GigE, ace USB and dart BCON
        LineFormat_LVTTL,  //!< The line is currently accepting or sending LVTTL level signals - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB and dart USB
        LineFormat_NoConnect,  //!< The line is not connected - Applies to: CameraLink, GigE and ace USB
        LineFormat_OpenDrain,  //!< The output of the line is "open drain"/"open collector" - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        LineFormat_OptoCoupled,  //!< The line is opto-coupled - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        LineFormat_RS422,  //!< The line is currently accepting or sending RS-422 level signals - Applies to: CameraLink, GigE and ace USB
        LineFormat_TTL,  //!< The line is currently accepting or sending TTL level signals - Applies to: CameraLink, GigE and ace USB
        LineFormat_TriState  //!< The line is currently in tri-state mode (not driven) - Applies to: CameraLink, GigE and ace USB
    };

    //! Valid values for LineLogic
    enum LineLogicEnums
    {
        LineLogic_Negative,  //!< The line logic of the currently selected line is negative - Applies to: CameraLink, GigE and ace USB
        LineLogic_Positive  //!< The line logic of the currently selected line is positive - Applies to: CameraLink, GigE and ace USB
    };

    //! Valid values for LineMode
    enum LineModeEnums
    {
        LineMode_Input,  //!< The selected physical line can be used to input an electrical signal - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        LineMode_Output  //!< The selected physical line can be used to output an electrical signal - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
    };

    //! Valid values for LineSelector
    enum LineSelectorEnums
    {
        LineSelector_CC1,  //!< CC1 can be configured - Applies to: CameraLink
        LineSelector_CC2,  //!< CC2 can be configured - Applies to: CameraLink
        LineSelector_CC3,  //!< CC3 can be configured - Applies to: CameraLink
        LineSelector_CC4,  //!< CC4 can be configured - Applies to: CameraLink
        LineSelector_ClSpare,  //!< The CL Spare line can be configured - Applies to: CameraLink
        LineSelector_In1,  //!< Selects input line 1 for configuration - Applies to: CameraLink
        LineSelector_In2,  //!< Selects input line 2 for configuration - Applies to: CameraLink
        LineSelector_In3,  //!< Selects input line 3 for configuration - Applies to: CameraLink
        LineSelector_In4,  //!< Selects input line 4 for configuration - Applies to: CameraLink
        LineSelector_Line1,  //!< Line 1 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        LineSelector_Line2,  //!< Line 2 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        LineSelector_Line3,  //!< Line 3 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB and dart BCON
        LineSelector_Line4,  //!< Line 4 can be configured - Applies to: CameraLink, GigE, ace USB and dart 2 USB
        LineSelector_Line5,  //!< Selects line 5 for configuration - Applies to: CameraLink
        LineSelector_Line6,  //!< Selects line 6 for configuration - Applies to: CameraLink
        LineSelector_Line7,  //!< Selects line 7 for configuration - Applies to: CameraLink
        LineSelector_Line8,  //!< Selects line 8 for configuration - Applies to: CameraLink
        LineSelector_Out1,  //!< Output Line 1 can be configured - Applies to: CameraLink and GigE
        LineSelector_Out2,  //!< Output Line 2 can be configured - Applies to: CameraLink and GigE
        LineSelector_Out3,  //!< Output Line 3 can be configured - Applies to: CameraLink and GigE
        LineSelector_Out4  //!< Output Line 4 can be configured - Applies to: CameraLink and GigE
    };

    //! Valid values for LineSource
    enum LineSourceEnums
    {
        LineSource_AcquisitionActive,  //!< The source signal for the currently selected line is set to Acquisition Active - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        LineSource_AcquisitionTriggerReady,  //!< The source signal for the currently selected line is set to Acquisition Trigger Ready - Applies to: CameraLink and GigE
        LineSource_AcquisitionTriggerWait,  //!< The source signal for the currently selected line is set to Acquisition Trigger Wait - Applies to: CameraLink and GigE
        LineSource_BslLightControl,  //!< The source signal for the currently selected line is set to Light Control - Applies to: GigE and ace USB
        LineSource_Counter1Active,  //!< The source signal for the currently selected line is set to Counter 1 Active - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        LineSource_Counter2Active,  //!< The source signal for the currently selected line is set to Counter 2 Active - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        LineSource_ExposureActive,  //!< The source signal for the currently selected line is set to Exposure Active - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        LineSource_ExposureTriggerWait,  //!< The source signal for the currently selected line is set to Exposure Trigger Wait - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        LineSource_FlashWindow,  //!< The source signal for the currently selected line is set to Flash Window - Applies to: CameraLink, GigE, ace USB, dart BCON and dart USB
        LineSource_FrameBurstActive,  //!< The source signal for the currently selected line is set to Frame Burst Active - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        LineSource_FrameBurstTriggerWait,  //!< The source signal for the currently selected line is set to Frame Burst Trigger Wait - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        LineSource_FrameCycle,  //!< The signal for the currently selected line is rising with Frame Trigger Wait and falling with Exposure Active - Applies to: CameraLink and GigE
        LineSource_FrameTriggerWait,  //!< The source signal for the currently selected line is set to Frame Trigger Wait - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        LineSource_FrequencyConverter,  //!< The signal for the currently selected line is associated with the output of the frequency converter module - Applies to: CameraLink and GigE
        LineSource_LineTriggerWait,  //!< The source signal for the currently selected line is set to Line Trigger Wait - Applies to: CameraLink and GigE
        LineSource_Off,  //!< No source signal is set for the currently selected line - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        LineSource_PatternGenerator1,  //!< Applies to: CameraLink and GigE
        LineSource_PatternGenerator2,  //!< Applies to: CameraLink and GigE
        LineSource_PatternGenerator3,  //!< Applies to: CameraLink and GigE
        LineSource_PatternGenerator4,  //!< Applies to: CameraLink and GigE
        LineSource_SerialTx,  //!< The source signal for the currently selected line is set to Serial Tx - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB and boost CoaXPress
        LineSource_ShaftEncoderModuleOut,  //!< The signal for the currently selected line is associated with the output of the shaft encoder module - Applies to: CameraLink and GigE
        LineSource_SyncUserOutput,  //!< The source signal for the currently selected line is set to Sync User Output - Applies to: CameraLink and GigE
        LineSource_SyncUserOutput0,  //!< The source signal for the currently selected line is set to Sync User Output 0 - Applies to: GigE
        LineSource_SyncUserOutput1,  //!< The source signal for the currently selected line is set to Sync User Output 1 - Applies to: GigE
        LineSource_SyncUserOutput2,  //!< The source signal for the currently selected line is set to Sync User Output 2 - Applies to: GigE
        LineSource_SyncUserOutput3,  //!< The source signal for the currently selected line is set to Sync User Output 3 - Applies to: GigE
        LineSource_Timer1Active,  //!< The source signal for the currently selected line is set to Timer 1 Active - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        LineSource_Timer2Active,  //!< The source signal for the currently selected line is set to Timer 2 Active - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        LineSource_Timer3Active,  //!< Sets the source signal for the selected output line to timer 3 active - Applies to: CameraLink and GigE
        LineSource_Timer4Active,  //!< Sets the source signal for the selected output line to timer 4 active - Applies to: CameraLink and GigE
        LineSource_TimerActive,  //!< The source signal for the currently selected line is set to Timer Active - Applies to: CameraLink and GigE
        LineSource_TriggerReady,  //!< The source signal for the currently selected line is set to Trigger Ready - Applies to: CameraLink and GigE
        LineSource_UserOutput,  //!< The source signal for the currently selected line is set to User Output - Applies to: CameraLink and GigE
        LineSource_UserOutput0,  //!< The source signal for the currently selected line is set to User Output 0 - Applies to: GigE and ace USB
        LineSource_UserOutput1,  //!< The source signal for the currently selected line is set to User Output 1 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        LineSource_UserOutput2,  //!< The source signal for the currently selected line is set to User Output 2 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        LineSource_UserOutput3,  //!< The source signal for the currently selected line is set to User Output 3 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        LineSource_UserOutput4  //!< The source signal for the currently selected line is set to User Output 4 - Applies to: CameraLink, GigE, dart 2 USB, dart BCON and dart USB
    };

    //! Valid values for OperatingMode
    enum OperatingModeEnums
    {
        OperatingMode_LongRange,  //!< The operating mode is set to Long Range - Applies to: blaze
        OperatingMode_ShortRange  //!< The operating mode is set to Short Range - Applies to: blaze
    };

    //! Valid values for OverlapMode
    enum OverlapModeEnums
    {
        OverlapMode_Off,  //!< Overlapping image acquisition is disabled - Applies to: dart BCON, dart USB and pulse USB
        OverlapMode_On  //!< Overlapping image acquisition is enabled - Applies to: dart BCON, dart USB and pulse USB
    };

    //! Valid values for ParameterSelector
    enum ParameterSelectorEnums
    {
        ParameterSelector_AutoTargetValue,  //!< The factory limits of the Auto Target Value parameter can be removed - Applies to: CameraLink and GigE
        ParameterSelector_BlackLevel,  //!< The factory limits of the Black Level parameter can be removed - Applies to: CameraLink and GigE
        ParameterSelector_Brightness,  //!< The factory limits of the Brightness parameter can be removed - Applies to: CameraLink and GigE
        ParameterSelector_ExposureOverhead,  //!< The factory limits of the Exposure Overhead parameter can be removed - Applies to: CameraLink and GigE
        ParameterSelector_ExposureOverlapMax,  //!< The factory limits of the Exposure Overlap Time Max parameter can be removed - Applies to: GigE
        ParameterSelector_ExposureTime,  //!< The factory limits of the Exposure Time parameter can be removed - Applies to: CameraLink and GigE
        ParameterSelector_Framerate,  //!< The factory limits of the Framerate parameter can be removed - Applies to: CameraLink and GigE
        ParameterSelector_Gain  //!< The factory limits of the Gain parameter can be removed - Applies to: CameraLink and GigE
    };

    //! Valid values for PgiMode
    enum PgiModeEnums
    {
        PgiMode_Off,  //!< Basler PGI image optimizations are disabled - Applies to: GigE and ace USB
        PgiMode_On  //!< Basler PGI image optimizations are enabled - Applies to: GigE and ace USB
    };

    //! Valid values for PixelCoding
    enum PixelCodingEnums
    {
        PixelCoding_BGR16,  //!< Applies to: CameraLink and GigE
        PixelCoding_BGR8,  //!< Applies to: CameraLink and GigE
        PixelCoding_BGRA8,  //!< Applies to: CameraLink and GigE
        PixelCoding_BayerBG10p,  //!< Sets the pixel format to Bayer BG 10p - Applies to: GigE
        PixelCoding_BayerGB10p,  //!< Sets the pixel format to Bayer GB 10p - Applies to: GigE
        PixelCoding_BayerGR10p,  //!< Sets the pixel format to Bayer GR 10p - Applies to: GigE
        PixelCoding_BayerRG10p,  //!< Sets the pixel format to Bayer RG 10p - Applies to: GigE
        PixelCoding_Mono10Packed,  //!< Applies to: CameraLink and GigE
        PixelCoding_Mono12Packed,  //!< Applies to: CameraLink and GigE
        PixelCoding_Mono16,  //!< Applies to: CameraLink and GigE
        PixelCoding_Mono8,  //!< Applies to: CameraLink and GigE
        PixelCoding_Mono8Signed,  //!< Applies to: CameraLink and GigE
        PixelCoding_RGB10V1Packed,  //!< Applies to: CameraLink and GigE
        PixelCoding_RGB10V2Packed,  //!< Applies to: CameraLink and GigE
        PixelCoding_RGB16,  //!< Applies to: CameraLink and GigE
        PixelCoding_RGB16Planar,  //!< Applies to: CameraLink and GigE
        PixelCoding_RGB8,  //!< Applies to: CameraLink and GigE
        PixelCoding_RGB8Planar,  //!< Applies to: CameraLink and GigE
        PixelCoding_RGBA8,  //!< Applies to: CameraLink and GigE
        PixelCoding_Raw16,  //!< Applies to: CameraLink and GigE
        PixelCoding_Raw8,  //!< Applies to: CameraLink and GigE
        PixelCoding_YUV411,  //!< Applies to: CameraLink and GigE
        PixelCoding_YUV422,  //!< Applies to: CameraLink and GigE
        PixelCoding_YUV444  //!< Applies to: CameraLink and GigE
    };

    //! Valid values for PixelColorFilter
    enum PixelColorFilterEnums
    {
        PixelColorFilter_BayerBG,  //!< The Bayer filter has a BG/GR alignment to the pixels in the acquired images - Applies to: ace USB, dart BCON, dart USB and pulse USB
        PixelColorFilter_BayerGB,  //!< The Bayer filter has a GB/RG alignment to the pixels in the acquired images - Applies to: ace USB, dart BCON, dart USB and pulse USB
        PixelColorFilter_BayerGR,  //!< The Bayer filter has a GR/BG alignment to the pixels in the acquired images - Applies to: ace USB, dart BCON, dart USB and pulse USB
        PixelColorFilter_BayerRG,  //!< The Bayer filter has an RG/GB alignment to the pixels in the acquired images - Applies to: ace USB, dart BCON, dart USB and pulse USB
        PixelColorFilter_Bayer_BG,  //!< The Bayer filter has a BG/GR alignment to the pixels in the acquired images - Applies to: CameraLink and GigE
        PixelColorFilter_Bayer_GB,  //!< The Bayer filter has a GB/RG alignment to the pixels in the acquired images - Applies to: CameraLink and GigE
        PixelColorFilter_Bayer_GR,  //!< The Bayer filter has a GR/BG alignment to the pixels in the acquired images - Applies to: CameraLink and GigE
        PixelColorFilter_Bayer_RG,  //!< The Bayer filter has an RG/GB alignment to the pixels in the acquired images - Applies to: CameraLink and GigE
        PixelColorFilter_None  //!< The camera doesn't have a Bayer filter - Applies to: CameraLink, GigE, ace USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for PixelFormat
    enum PixelFormatEnums
    {
        PixelFormat_BGR10Packed,  //!< The pixel format is set to BGR 10 Packed - Applies to: CameraLink and GigE
        PixelFormat_BGR12Packed,  //!< The pixel format is set to BGR 12 Packed - Applies to: CameraLink and GigE
        PixelFormat_BGR8,  //!< The pixel format is set to BGR 8 - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BGR8Packed,  //!< The pixel format is set to BGR 8 Packed - Applies to: CamEmu, CameraLink and GigE
        PixelFormat_BGRA8Packed,  //!< The pixel format is set to BGRA 8 Packed - Applies to: CamEmu, CameraLink and GigE
        PixelFormat_BayerBG10,  //!< The pixel format is set to Bayer BG 10 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerBG10p,  //!< The pixel format is set to Bayer BG 10p - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerBG12,  //!< The pixel format is set to Bayer BG 12 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_BayerBG12Packed,  //!< The pixel format is set to Bayer BG 12 Packed - Applies to: CameraLink and GigE
        PixelFormat_BayerBG12p,  //!< The pixel format is set to Bayer BG 12p - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerBG16,  //!< The pixel format is set to Bayer BG 16 - Applies to: CameraLink and GigE
        PixelFormat_BayerBG8,  //!< The pixel format is set to Bayer BG 8 - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_BayerGB10,  //!< The pixel format is set to Bayer GB 10 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerGB10p,  //!< The pixel format is set to Bayer GB 10p - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerGB12,  //!< The pixel format is set to Bayer GB 12 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_BayerGB12Packed,  //!< The pixel format is set to Bayer GB 12 Packed - Applies to: CameraLink and GigE
        PixelFormat_BayerGB12p,  //!< The pixel format is set to Bayer GB 12p - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerGB16,  //!< The pixel format is set to Bayer GB 16 - Applies to: CameraLink and GigE
        PixelFormat_BayerGB8,  //!< The pixel format is set to Bayer GB 8 - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_BayerGR10,  //!< The pixel format is set to Bayer GR 10 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerGR10p,  //!< The pixel format is set to Bayer GR 10p - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerGR12,  //!< The pixel format is set to Bayer GR 12 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_BayerGR12Packed,  //!< The pixel format is set to Bayer GR 12 Packed - Applies to: CameraLink and GigE
        PixelFormat_BayerGR12p,  //!< The pixel format is set to Bayer GR 12p - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerGR16,  //!< The pixel format is set to Bayer GR 16 - Applies to: CameraLink and GigE
        PixelFormat_BayerGR8,  //!< The pixel format is set to Bayer GR 8 - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_BayerRG10,  //!< The pixel format is set to Bayer RG 10 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerRG10p,  //!< The pixel format is set to Bayer RG 10p - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerRG12,  //!< The pixel format is set to Bayer RG 12 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_BayerRG12Packed,  //!< The pixel format is set to Bayer RG 12 Packed - Applies to: CameraLink and GigE
        PixelFormat_BayerRG12p,  //!< The pixel format is set to Bayer RG 12p - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_BayerRG16,  //!< The pixel format is set to Bayer RG 16 - Applies to: CameraLink and GigE
        PixelFormat_BayerRG8,  //!< The pixel format is set to Bayer RG 8 - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_Confidence16,  //!< Confidence 16-bit - Applies to: blaze
        PixelFormat_Confidence8,  //!< Confidence 8-bit - Applies to: blaze
        PixelFormat_Coord3D_ABC32f,  //!< 3D coordinate A-B-C 32-bit floating point - Applies to: blaze
        PixelFormat_Coord3D_C16,  //!< 3D coordinate C 16-bit - Applies to: blaze
        PixelFormat_Mono10,  //!< The pixel format is set to Mono 10 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_Mono10Packed,  //!< Sets the pixel format to Mono 10 Packed - Applies to: CameraLink and GigE
        PixelFormat_Mono10p,  //!< The pixel format is set to Mono 10p - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_Mono12,  //!< The pixel format is set to Mono 12 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_Mono12Packed,  //!< The pixel format is set to Mono 12 Packed - Applies to: CameraLink and GigE
        PixelFormat_Mono12p,  //!< The pixel format is set to Mono 12p - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelFormat_Mono16,  //!< The pixel format is set to Mono 16 - Applies to: CamEmu, CameraLink, GigE and blaze
        PixelFormat_Mono8,  //!< The pixel format is set to Mono 8 - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_Mono8Signed,  //!< Sets the pixel format to Mono 8 Signed - Applies to: CameraLink and GigE
        PixelFormat_RGB10Packed,  //!< The pixel format is set to RGB 10 Packed - Applies to: CameraLink and GigE
        PixelFormat_RGB10Planar,  //!< The pixel format is set to RGB 10 Planar - Applies to: CameraLink and GigE
        PixelFormat_RGB10V1Packed,  //!< The pixel format is set to RGB 10V1 Packed - Applies to: CameraLink and GigE
        PixelFormat_RGB10V2Packed,  //!< The pixel format is set to RGB 10V2 Packed - Applies to: CameraLink and GigE
        PixelFormat_RGB12Packed,  //!< The pixel format is set to RGB 12 Packed - Applies to: CameraLink and GigE
        PixelFormat_RGB12Planar,  //!< The pixel format is set to RGB 12 Planar - Applies to: CameraLink and GigE
        PixelFormat_RGB12V1Packed,  //!< The pixel format is set to RGB 12 V1 Packed - Applies to: CameraLink and GigE
        PixelFormat_RGB16Packed,  //!< Sets the pixel format to RGB 16 Packed - Applies to: CamEmu
        PixelFormat_RGB16Planar,  //!< The pixel format is set to RGB 16 Planar - Applies to: CameraLink and GigE
        PixelFormat_RGB8,  //!< The pixel format is set to RGB 8 - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_RGB8Packed,  //!< The pixel format is set to RGB 8 Packed - Applies to: CamEmu, CameraLink and GigE
        PixelFormat_RGB8Planar,  //!< The pixel format is set to RGB 8 Planar - Applies to: CameraLink and GigE
        PixelFormat_RGBA8Packed,  //!< The pixel format is set to RGBA 8 Packed - Applies to: CameraLink and GigE
        PixelFormat_YCbCr422_8,  //!< The pixel format is set to YCbCr 422 - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        PixelFormat_YUV411Packed,  //!< Sets the pixel format to YUV 411 Packed - Applies to: CameraLink and GigE
        PixelFormat_YUV422Packed,  //!< The pixel format is set to YUV 422 Packed - Applies to: CameraLink and GigE
        PixelFormat_YUV422_8,  //!< The pixel format is set to YUV 4:2:2 8 bit packed - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        PixelFormat_YUV422_YUYV_Packed,  //!< The pixel format is set to YUV 422 (YUYV) Packed - Applies to: CameraLink and GigE
        PixelFormat_YUV444Packed  //!< Sets the pixel format to YUV 444 Packed - Applies to: CameraLink and GigE
    };

    //! Valid values for PixelSize
    enum PixelSizeEnums
    {
        PixelSize_Bpp1,  //!< The pixel depth in the acquired images is 1 bit per pixel - Applies to: CameraLink, GigE and ace USB
        PixelSize_Bpp10,  //!< The pixel depth in the acquired images is 10 bits per pixel - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelSize_Bpp12,  //!< The pixel depth in the acquired images is 12 bits per pixel - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        PixelSize_Bpp14,  //!< The pixel depth in the acquired images is 14 bits per pixel - Applies to: CameraLink and GigE
        PixelSize_Bpp16,  //!< The pixel depth in the acquired images is 16 bits per pixel - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart USB and pulse USB
        PixelSize_Bpp2,  //!< The pixel depth in the acquired images is 2 bits per pixel - Applies to: CameraLink, GigE and ace USB
        PixelSize_Bpp24,  //!< The pixel depth in the acquired images is 24 bits per pixel - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart USB and pulse USB
        PixelSize_Bpp32,  //!< The pixel depth in the acquired images is 32 bits per pixel - Applies to: CamEmu, CameraLink and GigE
        PixelSize_Bpp36,  //!< The pixel depth in the acquired images is 36 bits per pixel - Applies to: CameraLink and GigE
        PixelSize_Bpp4,  //!< The pixel depth in the acquired images is 4 bits per pixel - Applies to: CameraLink, GigE and ace USB
        PixelSize_Bpp48,  //!< The pixel depth in the acquired images is 48 bits per pixel - Applies to: CamEmu, CameraLink and GigE
        PixelSize_Bpp64,  //!< The pixel depth in the acquired images is 64 bits per pixel - Applies to: CameraLink and GigE
        PixelSize_Bpp8  //!< The pixel depth in the acquired images is 8 bits per pixel - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart USB and pulse USB
    };

    //! Valid values for PtpClockAccuracy
    enum PtpClockAccuracyEnums
    {
        PtpClockAccuracy_GreaterThan10s,  //!< The expected accuracy of the PTP device clock is greater than 10 seconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Unknown,  //!< The expected accuracy of the PTP device clock is unknown - Applies to: ace 2 GigE
        PtpClockAccuracy_Within100ms,  //!< The expected accuracy of the PTP device clock is within 100 milliseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within100ns,  //!< The expected accuracy of the PTP device clock is within 100 nanoseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within100us,  //!< The expected accuracy of the PTP device clock is within 100 microseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within10ms,  //!< The expected accuracy of the PTP device clock is within 10 milliseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within10s,  //!< The expected accuracy of the PTP device clock is within 10 seconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within10us,  //!< The expected accuracy of the PTP device clock is within 10 microseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within1ms,  //!< The expected accuracy of the PTP device clock is within 1 millisecond - Applies to: ace 2 GigE
        PtpClockAccuracy_Within1s,  //!< The expected accuracy of the PTP device clock is within 1 second - Applies to: ace 2 GigE
        PtpClockAccuracy_Within1us,  //!< The expected accuracy of the PTP device clock is within 1 microsecond - Applies to: ace 2 GigE
        PtpClockAccuracy_Within250ms,  //!< The expected accuracy of the PTP device clock is within 250 milliseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within250ns,  //!< The expected accuracy of the PTP device clock is within 250 nanoseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within250us,  //!< The expected accuracy of the PTP device clock is within 250 microseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within25ms,  //!< The expected accuracy of the PTP device clock is within 25 milliseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within25ns,  //!< The expected accuracy of the PTP device clock is within 25 nanoseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within25us,  //!< The expected accuracy of the PTP device clock is within 25 microseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within2p5ms,  //!< The expected accuracy of the PTP device clock is within 2 5 milliseconds - Applies to: ace 2 GigE
        PtpClockAccuracy_Within2p5us  //!< The expected accuracy of the PTP device clock is within 2 5 microseconds - Applies to: ace 2 GigE
    };

    //! Valid values for PtpServoStatus
    enum PtpServoStatusEnums
    {
        PtpServoStatus_Locked,  //!< The clock servo is locked - Applies to: ace 2 GigE
        PtpServoStatus_Unknown  //!< The status of the clock servo is unknown - Applies to: ace 2 GigE
    };

    //! Valid values for PtpStatus
    enum PtpStatusEnums
    {
        PtpStatus_Disabled,  //!< The port is in the Disabled state - Applies to: ace 2 GigE and blaze
        PtpStatus_Faulty,  //!< The port is in the Faulty state - Applies to: ace 2 GigE and blaze
        PtpStatus_Initializing,  //!< The port is in the Initializing state - Applies to: ace 2 GigE and blaze
        PtpStatus_Listening,  //!< The port is in the Listening state - Applies to: ace 2 GigE and blaze
        PtpStatus_Master,  //!< The port is in the Master state - Applies to: ace 2 GigE and blaze
        PtpStatus_Passive,  //!< The port is in the Passive state - Applies to: ace 2 GigE and blaze
        PtpStatus_PreMaster,  //!< The port is in the PreMaster state - Applies to: ace 2 GigE and blaze
        PtpStatus_Slave,  //!< The port is in the Slave state - Applies to: ace 2 GigE and blaze
        PtpStatus_Uncalibrated  //!< The port is in the Uncalibrated state - Applies to: ace 2 GigE and blaze
    };

    //! Valid values for ROIZoneMode
    enum ROIZoneModeEnums
    {
        ROIZoneMode_Off,  //!< The currently selected ROI zone is disabled - Applies to: GigE and ace USB
        ROIZoneMode_On  //!< The currently selected ROI zone is enabled - Applies to: GigE and ace USB
    };

    //! Valid values for ROIZoneSelector
    enum ROIZoneSelectorEnums
    {
        ROIZoneSelector_Zone0,  //!< ROI zone 0 can be configured - Applies to: GigE and ace USB
        ROIZoneSelector_Zone1,  //!< ROI zone 1 can be configured - Applies to: GigE and ace USB
        ROIZoneSelector_Zone2,  //!< ROI zone 2 can be configured - Applies to: GigE and ace USB
        ROIZoneSelector_Zone3,  //!< ROI zone 3 can be configured - Applies to: GigE and ace USB
        ROIZoneSelector_Zone4,  //!< ROI zone 4 can be configured - Applies to: GigE and ace USB
        ROIZoneSelector_Zone5,  //!< ROI zone 5 can be configured - Applies to: GigE and ace USB
        ROIZoneSelector_Zone6,  //!< ROI zone 6 can be configured - Applies to: GigE and ace USB
        ROIZoneSelector_Zone7  //!< ROI zone 7 can be configured - Applies to: GigE and ace USB
    };

    //! Valid values for RemoveParameterLimitSelector
    enum RemoveParameterLimitSelectorEnums
    {
        RemoveParameterLimitSelector_AutoTargetValue,  //!< The factory limits of the AutoTargetValue parameter can be removed - Applies to: ace USB
        RemoveParameterLimitSelector_BlackLevel,  //!< The factory limits of the BlackLevel parameter can be removed - Applies to: ace USB
        RemoveParameterLimitSelector_ExposureOverhead,  //!< The factory limits of the ExposureOverhead parameter can be removed - Applies to: ace USB
        RemoveParameterLimitSelector_ExposureTime,  //!< The factory limits of the Exposure Time parameter can be removed - Applies to: ace USB
        RemoveParameterLimitSelector_Gain  //!< The factory limits of the Gain parameter can be removed - Applies to: ace USB
    };

    //! Valid values for Scan3dCoordinateSelector
    enum Scan3dCoordinateSelectorEnums
    {
        Scan3dCoordinateSelector_CoordinateA,  //!< The first (X or Theta) coordinate - Applies to: blaze
        Scan3dCoordinateSelector_CoordinateB,  //!< The second (Y or Phi) coordinate - Applies to: blaze
        Scan3dCoordinateSelector_CoordinateC  //!< The third (Z or Rho) coordinate - Applies to: blaze
    };

    //! Valid values for Scan3dCoordinateSystem
    enum Scan3dCoordinateSystemEnums
    {
        Scan3dCoordinateSystem_Cartesian  //!< Default value - Applies to: blaze
    };

    //! Valid values for Scan3dCoordinateSystemReference
    enum Scan3dCoordinateSystemReferenceEnums
    {
        Scan3dCoordinateSystemReference_Anchor  //!< Default value - Applies to: blaze
    };

    //! Valid values for Scan3dDistanceUnit
    enum Scan3dDistanceUnitEnums
    {
        Scan3dDistanceUnit_DeviceSpecific,  //!< Distance values are in device-specific units - Applies to: blaze
        Scan3dDistanceUnit_Millimeter  //!< Distance values are in millimeter units (default) - Applies to: blaze
    };

    //! Valid values for Scan3dOutputMode
    enum Scan3dOutputModeEnums
    {
        Scan3dOutputMode_CalibratedABC_Grid,  //!< 3 Coordinates in grid organization - Applies to: blaze
        Scan3dOutputMode_CalibratedC,  //!< Calibrated 2 5D Depth map - Applies to: blaze
        Scan3dOutputMode_UncalibratedC  //!< Uncalibrated 2 5D Depth map - Applies to: blaze
    };

    //! Valid values for SensorBitDepth
    enum SensorBitDepthEnums
    {
        SensorBitDepth_BitDepth10,  //!< The sensor delivers 10-bit pixels - Applies to: CameraLink and GigE
        SensorBitDepth_BitDepth12,  //!< The sensor delivers 12-bit pixels - Applies to: CameraLink and GigE
        SensorBitDepth_BitDepth14,  //!< The sensor delivers 14-bit pixels - Applies to: CameraLink and GigE
        SensorBitDepth_BitDepth16,  //!< The sensor delivers 16-bit pixels - Applies to: CameraLink and GigE
        SensorBitDepth_BitDepth8  //!< The sensor delivers 8-bit pixels - Applies to: CameraLink and GigE
    };

    //! Valid values for SensorDigitizationTaps
    enum SensorDigitizationTapsEnums
    {
        SensorDigitizationTaps_Four,  //!< Applies to: CameraLink and GigE
        SensorDigitizationTaps_One,  //!< Applies to: CameraLink and GigE
        SensorDigitizationTaps_Three,  //!< Applies to: CameraLink and GigE
        SensorDigitizationTaps_Two  //!< Applies to: CameraLink and GigE
    };

    //! Valid values for SensorReadoutMode
    enum SensorReadoutModeEnums
    {
        SensorReadoutMode_Fast,  //!< The camera operates in fast readout mode - Applies to: GigE and ace USB
        SensorReadoutMode_Normal  //!< The camera operates in normal readout mode - Applies to: GigE and ace USB
    };

    //! Valid values for SensorShutterMode
    enum SensorShutterModeEnums
    {
        SensorShutterMode_Global,  //!< The shutter opens and closes at the same time for all pixels - Applies to: dart BCON, dart USB and pulse USB
        SensorShutterMode_GlobalReset,  //!< The shutter opens at the same time for all rows but closes in a sequential manner - Applies to: dart BCON and dart USB
        SensorShutterMode_Rolling  //!< The shutter opens and closes sequentially for groups of rows - Applies to: ace 2 GigE, ace 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for SequenceAddressBitSelector
    enum SequenceAddressBitSelectorEnums
    {
        SequenceAddressBitSelector_Bit0,  //!< Bit 0 of the sequence set address can be controlled using an input line - Applies to: CameraLink and GigE
        SequenceAddressBitSelector_Bit1,  //!< Bit 1 of the sequence set address can be controlled using an input line - Applies to: CameraLink and GigE
        SequenceAddressBitSelector_Bit2,  //!< Bit 2 of the sequence set address can be controlled using an input line - Applies to: CameraLink and GigE
        SequenceAddressBitSelector_Bit3  //!< Bit 3 of the sequence set address can be controlled using an input line - Applies to: CameraLink and GigE
    };

    //! Valid values for SequenceAddressBitSource
    enum SequenceAddressBitSourceEnums
    {
        SequenceAddressBitSource_CC1,  //!< The selected bit of the sequence set address can be set using the CC1 signal - Applies to: CameraLink and GigE
        SequenceAddressBitSource_CC2,  //!< The selected bit of the sequence set address can be set using the CC2 signal - Applies to: CameraLink and GigE
        SequenceAddressBitSource_CC3,  //!< The selected bit of the sequence set address can be set using the CC3 signal - Applies to: CameraLink and GigE
        SequenceAddressBitSource_CC4,  //!< The selected bit of the sequence set address can be set using the CC4 signal - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line1,  //!< The selected bit of the sequence set address can be set using Line 1 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line2,  //!< The selected bit of the sequence set address can be set using Line 2 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line3,  //!< The selected bit of the sequence set address can be set using Line 3 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line4,  //!< The selected bit of the sequence set address can be set using Line 4 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line5,  //!< The selected bit of the sequence set address can be set using Line 5 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line6,  //!< The selected bit of the sequence set address can be set using Line 6 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line7,  //!< The selected bit of the sequence set address can be set using Line 7 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_Line8,  //!< The selected bit of the sequence set address can be set using Line 8 - Applies to: CameraLink and GigE
        SequenceAddressBitSource_VInput1,  //!< Selects Virtual Input 1 as the source for the selected bit of the sequence set address - Applies to: CameraLink and GigE
        SequenceAddressBitSource_VInput2,  //!< Selects Virtual Input 2 as the source for the selected bit of the sequence set address - Applies to: CameraLink and GigE
        SequenceAddressBitSource_VInput3,  //!< Selects Virtual Input 3 as the source for the selected bit of the sequence set address - Applies to: CameraLink and GigE
        SequenceAddressBitSource_VInput4,  //!< Selects Virtual Input 4 as the source for the selected bit of the sequence set address - Applies to: CameraLink and GigE
        SequenceAddressBitSource_VInputDecActive  //!< Selects Virtual Input Decoder Active as the source for the selected bit of the sequence set address - Applies to: CameraLink and GigE
    };

    //! Valid values for SequenceAdvanceMode
    enum SequenceAdvanceModeEnums
    {
        SequenceAdvanceMode_Auto,  //!< The Auto sequence advance mode is selected - Applies to: CameraLink and GigE
        SequenceAdvanceMode_Controlled,  //!< The Controlled sequence advance mode is selected - Applies to: CameraLink and GigE
        SequenceAdvanceMode_FreeSelection  //!< The Free Selection sequence advance mode is selected - Applies to: CameraLink and GigE
    };

    //! Valid values for SequenceConfigurationMode
    enum SequenceConfigurationModeEnums
    {
        SequenceConfigurationMode_Off,  //!< The sequencer can't be configured - Applies to: GigE
        SequenceConfigurationMode_On  //!< The sequencer can be configured - Applies to: GigE
    };

    //! Valid values for SequenceControlSelector
    enum SequenceControlSelectorEnums
    {
        SequenceControlSelector_Advance,  //!< The sequence set advance can be configured - Applies to: CameraLink and GigE
        SequenceControlSelector_Restart  //!< The sequence set restart can be configured - Applies to: CameraLink and GigE
    };

    //! Valid values for SequenceControlSource
    enum SequenceControlSourceEnums
    {
        SequenceControlSource_AlwaysActive,  //!< Sequence set advance is automatic  The sequence repeat starts with sequence set index number 1 - Applies to: CameraLink and GigE
        SequenceControlSource_CC1,  //!< Sequence restart or sequence set advance are controlled using the CC1 signal - Applies to: CameraLink and GigE
        SequenceControlSource_CC2,  //!< Sequence restart or sequence set advance are controlled using the CC2 signal - Applies to: CameraLink and GigE
        SequenceControlSource_CC3,  //!< Sequence restart or sequence set advance are controlled using the CC3 signal - Applies to: CameraLink and GigE
        SequenceControlSource_CC4,  //!< Sequence restart or sequence set advance are controlled using the CC4 signal - Applies to: CameraLink and GigE
        SequenceControlSource_Disabled,  //!< Sequence set advance will be controlled using the Async Advance command - Applies to: CameraLink and GigE
        SequenceControlSource_Line1,  //!< Sequence restart or sequence set advance are controlled using Line 1 - Applies to: CameraLink and GigE
        SequenceControlSource_Line2,  //!< Sequence restart or sequence set advance are controlled using Line 2 - Applies to: CameraLink and GigE
        SequenceControlSource_Line3,  //!< Sequence restart or sequence set advance are controlled using Line 3 - Applies to: CameraLink and GigE
        SequenceControlSource_Line4,  //!< Sequence restart or sequence set advance are controlled using Line 4 - Applies to: CameraLink and GigE
        SequenceControlSource_Line5,  //!< Sequence restart or sequence set advance are controlled using Line 5 - Applies to: CameraLink and GigE
        SequenceControlSource_Line6,  //!< Sequence restart or sequence set advance are controlled using Line 6 - Applies to: CameraLink and GigE
        SequenceControlSource_Line7,  //!< Sequence restart or sequence set advance are controlled using Line 7 - Applies to: CameraLink and GigE
        SequenceControlSource_Line8,  //!< Sequence restart or sequence set advance are controlled using Line 8 - Applies to: CameraLink and GigE
        SequenceControlSource_VInput1,  //!< The source for sequence restart or sequence set advance is Virtual Input 1 - Applies to: CameraLink and GigE
        SequenceControlSource_VInput2,  //!< The source for sequence restart or sequence set advance is Virtual Input 2 - Applies to: CameraLink and GigE
        SequenceControlSource_VInput3,  //!< The source for sequence restart or sequence set advance is Virtual Input 3 - Applies to: CameraLink and GigE
        SequenceControlSource_VInput4,  //!< The source for sequence restart or sequence set advance is Virtual Input 4 - Applies to: CameraLink and GigE
        SequenceControlSource_VInputDecActive  //!< The source for sequence restart or sequence set advance is Virtual Input Decoder Active - Applies to: CameraLink and GigE
    };

    //! Valid values for SequencerConfigurationMode
    enum SequencerConfigurationModeEnums
    {
        SequencerConfigurationMode_Off,  //!< The sequencer can't be configured - Applies to: ace USB
        SequencerConfigurationMode_On  //!< The sequencer can be configured - Applies to: ace USB
    };

    //! Valid values for SequencerMode
    enum SequencerModeEnums
    {
        SequencerMode_Off,  //!< Image acquisitions can't be controlled by the sequencer - Applies to: ace USB
        SequencerMode_On  //!< Image acquisitions will be controlled by the sequencer - Applies to: ace USB
    };

    //! Valid values for SequencerTriggerActivation
    enum SequencerTriggerActivationEnums
    {
        SequencerTriggerActivation_AnyEdge,  //!< The sequence set will advance on the falling or rising edge of the source signal - Applies to: ace USB
        SequencerTriggerActivation_FallingEdge,  //!< The sequence set will advance on the falling edge of the source signal - Applies to: ace USB
        SequencerTriggerActivation_LevelHigh,  //!< The sequence set will advance when the source signal is high - Applies to: ace USB
        SequencerTriggerActivation_LevelLow,  //!< The sequence set will advance when the source signal is low - Applies to: ace USB
        SequencerTriggerActivation_RisingEdge  //!< The sequence set will advance on the rising edge of the source signal - Applies to: ace USB
    };

    //! Valid values for SequencerTriggerSource
    enum SequencerTriggerSourceEnums
    {
        SequencerTriggerSource_Counter1End,  //!< Counter 1 End is selected as the trigger source for sequencer set advance - Applies to: ace USB
        SequencerTriggerSource_Counter2End,  //!< Sequencer set advance is controlled using Counter 2 End - Applies to: ace USB
        SequencerTriggerSource_Counter3End,  //!< Counter 3 End is selected as the trigger source for sequencer set advance - Applies to: ace USB
        SequencerTriggerSource_FrameEnd,  //!< Frame End is selected as the trigger source for sequencer set advance - Applies to: ace USB
        SequencerTriggerSource_FrameStart,  //!< Sequencer set advance is controlled using Frame Start signals - Applies to: ace USB
        SequencerTriggerSource_Line1,  //!< Sequencer set advance is controlled using Line 1 - Applies to: ace USB
        SequencerTriggerSource_Line2,  //!< Line 2 is selected as the trigger source for sequencer set advance - Applies to: ace USB
        SequencerTriggerSource_Line3,  //!< Sequencer set advance is controlled using Line 3 - Applies to: ace USB
        SequencerTriggerSource_Line4,  //!< Sequencer set advance is controlled using Line 4 - Applies to: ace USB
        SequencerTriggerSource_SoftwareSignal1,  //!< Sequencer set advance is controlled using software signal 1 - Applies to: ace USB
        SequencerTriggerSource_SoftwareSignal2,  //!< Sequencer set advance is controlled using software signal 2 - Applies to: ace USB
        SequencerTriggerSource_SoftwareSignal3  //!< Sequencer set advance is controlled using software signal 3 - Applies to: ace USB
    };

    //! Valid values for ShadingSelector
    enum ShadingSelectorEnums
    {
        ShadingSelector_GainShading,  //!< Gain Shading correction is selected - Applies to: CameraLink and GigE
        ShadingSelector_OffsetShading  //!< Offset Shading correction is selected - Applies to: CameraLink and GigE
    };

    //! Valid values for ShadingSetCreate
    enum ShadingSetCreateEnums
    {
        ShadingSetCreate_Off,  //!< Applies to: CameraLink and GigE
        ShadingSetCreate_Once  //!< Applies to: CameraLink and GigE
    };

    //! Valid values for ShadingSetDefaultSelector
    enum ShadingSetDefaultSelectorEnums
    {
        ShadingSetDefaultSelector_DefaultShadingSet,  //!< The default shading set is selected as the bootup shading set - Applies to: CameraLink and GigE
        ShadingSetDefaultSelector_UserShadingSet1,  //!< User Shading Set 1 is selected as the bootup shading set - Applies to: CameraLink and GigE
        ShadingSetDefaultSelector_UserShadingSet2  //!< User Shading Set 2 is selected as the bootup shading set - Applies to: CameraLink and GigE
    };

    //! Valid values for ShadingSetSelector
    enum ShadingSetSelectorEnums
    {
        ShadingSetSelector_DefaultShadingSet,  //!< The default shading set can be loaded using the Activate command - Applies to: CameraLink and GigE
        ShadingSetSelector_UserShadingSet1,  //!< User Shading Set 1 can be loaded using the Activate command - Applies to: CameraLink and GigE
        ShadingSetSelector_UserShadingSet2  //!< User Shading Set 2 can be loaded using the Activate command - Applies to: CameraLink and GigE
    };

    //! Valid values for ShadingStatus
    enum ShadingStatusEnums
    {
        ShadingStatus_ActivateError,  //!< The selected shading set could not be loaded - Applies to: CameraLink and GigE
        ShadingStatus_CreateError,  //!< A problem occurred while creating a shading set - Applies to: CameraLink and GigE
        ShadingStatus_NoError,  //!< The last operation related to shading correction was successful - Applies to: CameraLink and GigE
        ShadingStatus_StartupSetError  //!< A problem with the startup shading set occurred - Applies to: CameraLink and GigE
    };

    //! Valid values for ShaftEncoderModuleCounterMode
    enum ShaftEncoderModuleCounterModeEnums
    {
        ShaftEncoderModuleCounterMode_FollowDirection,  //!< The tick counter increases for forward ticks and decreases for reverse ticks - Applies to: CameraLink and GigE
        ShaftEncoderModuleCounterMode_IgnoreDirection  //!< The tick counter increases for forward ticks and for reverse ticks - Applies to: CameraLink and GigE
    };

    //! Valid values for ShaftEncoderModuleLineSelector
    enum ShaftEncoderModuleLineSelectorEnums
    {
        ShaftEncoderModuleLineSelector_PhaseA,  //!< Phase A of the shaft encoder is selected as input for the shaft encoder module - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSelector_PhaseB  //!< Phase B of the shaft encoder is selected as input for the shaft encoder module - Applies to: CameraLink and GigE
    };

    //! Valid values for ShaftEncoderModuleLineSource
    enum ShaftEncoderModuleLineSourceEnums
    {
        ShaftEncoderModuleLineSource_CC1,  //!< The source signal for the shaft encoder module is set to CC1 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_CC2,  //!< The source signal for the shaft encoder module is set to CC2 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_CC3,  //!< The source signal for the shaft encoder module is set to CC3 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_CC4,  //!< The source signal for the shaft encoder module is set to CC4 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line1,  //!< The source signal for the shaft encoder module is set to input line 1 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line2,  //!< The source signal for the shaft encoder module is set to input line 2 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line3,  //!< The source signal for the shaft encoder module is set to input line 3 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line4,  //!< The source signal for the shaft encoder module is set to input line 4 - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line5,  //!< Selects input line 5 as signal source for the shaft encoder module - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line6,  //!< Selects input line 6 as signal source for the shaft encoder module - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line7,  //!< Selects input line 7 as signal source for the shaft encoder module - Applies to: CameraLink and GigE
        ShaftEncoderModuleLineSource_Line8  //!< Selects input line 8 as signal source for the shaft encoder module - Applies to: CameraLink and GigE
    };

    //! Valid values for ShaftEncoderModuleMode
    enum ShaftEncoderModuleModeEnums
    {
        ShaftEncoderModuleMode_AnyDirection,  //!< The shaft encoder module outputs trigger signals for forward and reverse ticks, provided the reverse counter is neither increasing nor decreasing - Applies to: CameraLink and GigE
        ShaftEncoderModuleMode_ForwardOnly  //!< The shaft encoder module outputs trigger signals for forward ticks only, provided the reverse counter is neither increasing nor decreasing - Applies to: CameraLink and GigE
    };

    //! Valid values for ShutterMode
    enum ShutterModeEnums
    {
        ShutterMode_Global,  //!< The shutter opens and closes at the same time for all pixels - Applies to: CameraLink, GigE and ace USB
        ShutterMode_GlobalResetRelease,  //!< The shutter opens at the same time for all rows but closes in a sequential manner - Applies to: CameraLink, GigE and ace USB
        ShutterMode_Rolling  //!< The shutter opens and closes sequentially for groups of rows - Applies to: CameraLink, GigE and ace USB
    };

    //! Valid values for SoftwareSignalSelector
    enum SoftwareSignalSelectorEnums
    {
        SoftwareSignalSelector_SoftwareSignal1,  //!< Software signal 1 can be executed - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        SoftwareSignalSelector_SoftwareSignal2,  //!< Software signal 2 can be executed - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        SoftwareSignalSelector_SoftwareSignal3,  //!< Software signal 3 can be executed - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        SoftwareSignalSelector_SoftwareSignal4  //!< Software signal 4 can be controlled - Applies to: ace USB
    };

    //! Valid values for SyncUserOutputSelector
    enum SyncUserOutputSelectorEnums
    {
        SyncUserOutputSelector_SyncUserOutput0,  //!< User-settable synchronous output signal 0 can be configured - Applies to: GigE
        SyncUserOutputSelector_SyncUserOutput1,  //!< User-settable synchronous output signal 1 can be configured - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutput2,  //!< User-settable synchronous output signal 2 can be configured - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutput3,  //!< User-settable synchronous output signal 3 can be configured - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutput4,  //!< User-settable synchronous output signal 4 can be configured - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutput5,  //!< Selects user settable synchronous output signal 5 for configuration - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutput6,  //!< Selects user settable synchronous output signal 6 for configuration - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutput7,  //!< Selects user settable synchronous output signal 7 for configuration - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutput8,  //!< Selects user settable synchronous output signal 8 for configuration - Applies to: CameraLink and GigE
        SyncUserOutputSelector_SyncUserOutputCC1,  //!< Selects user settable synchronous output signal CC1 for configuration - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputCC2,  //!< Selects user settable synchronous output signal CC2 for configuration - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputCC3,  //!< Selects user settable synchronous output signal CC3 for configuration - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputCC4,  //!< Selects user settable synchronous output signal CC4 for configuration - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputClSpare,  //!< User-settable synchronous output signal CL Spare can be configured - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputLine1,  //!< User-settable synchronous output signal Line 1 can be configured - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputLine2,  //!< User-settable synchronous output signal Line 2 can be configured - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputLine3,  //!< User-settable synchronous output signal Line 3 can be configured - Applies to: CameraLink
        SyncUserOutputSelector_SyncUserOutputLine4  //!< User-settable synchronous output signal Line 4 can be configured - Applies to: CameraLink
    };

    //! Valid values for TemperatureSelector
    enum TemperatureSelectorEnums
    {
        TemperatureSelector_Case,  //!< The temperature is measured on the case - Applies to: CameraLink and GigE
        TemperatureSelector_Coreboard,  //!< The temperature is measured on the core board - Applies to: CameraLink and GigE
        TemperatureSelector_Framegrabberboard,  //!< The temperature is measured on the frame grabber board - Applies to: CameraLink and GigE
        TemperatureSelector_Sensorboard  //!< The temperature is measured on the sensor board - Applies to: CameraLink and GigE
    };

    //! Valid values for TemperatureState
    enum TemperatureStateEnums
    {
        TemperatureState_Critical,  //!< The temperature is close to or at the allowed maximum  Provide cooling - Applies to: CameraLink, GigE, ace USB and blaze
        TemperatureState_Error,  //!< The temperature is above the allowed maximum  Provide cooling immediately - Applies to: CameraLink, GigE, ace USB and blaze
        TemperatureState_Ok  //!< The temperature is within the normal operating temperature range - Applies to: CameraLink, GigE, ace USB and blaze
    };

    //! Valid values for TestImageSelector
    enum TestImageSelectorEnums
    {
        TestImageSelector_Black,  //!< Sets the camera to generate and transmit black test images - Applies to: CameraLink and GigE
        TestImageSelector_ColorBar,  //!< Sets the camera to generate and transmit test images with a color bar pattern - Applies to: CameraLink and GigE
        TestImageSelector_DeviceSpecific,  //!< Sets the camera to generate and transmit test images with a camera specific pattern - Applies to: CameraLink and GigE
        TestImageSelector_FixedDiagonalGrayGradient_8Bit,  //!< Sets the camera to generate and transmit test images with an 8 bit fixed diagonal gray gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_FrameCounter,  //!< Sets the camera to generate and transmit test images with a frame counter pattern - Applies to: CameraLink and GigE
        TestImageSelector_GreyHorizontalRamp,  //!< Sets the camera to generate and transmit test images with a fixed horizontal gray gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_GreyHorizontalRampMoving,  //!< Sets the camera to generate and transmit test images with a moving horizontal gray gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_GreyVerticalRamp,  //!< Sets the camera to generate and transmit test images with a fixed vertical gray gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_GreyVerticalRampMoving,  //!< Sets the camera to generate and transmit test images with a moving vertical gray gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_HorzontalLineMoving,  //!< Sets the camera to generate and transmit test images with a moving horizontal line pattern - Applies to: CameraLink and GigE
        TestImageSelector_MovingDiagonalColorGradient,  //!< Sets the camera to generate and transmit test images with a moving diagonal color gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_MovingDiagonalGrayGradientFeatureTest_12Bit,  //!< Sets the camera to generate and transmit test images with a 12 bit moving diagonal gray gradient feature test pattern - Applies to: CameraLink and GigE
        TestImageSelector_MovingDiagonalGrayGradientFeatureTest_8Bit,  //!< Sets the camera to generate and transmit test images with an 8 bit moving diagonal gray gradient feature test pattern - Applies to: CameraLink and GigE
        TestImageSelector_MovingDiagonalGrayGradient_12Bit,  //!< Sets the camera to generate and transmit test images with a 12 bit moving diagonal gray gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_MovingDiagonalGrayGradient_8Bit,  //!< Sets the camera to generate and transmit test images with an 8 bit moving diagonal gray gradient pattern - Applies to: CameraLink and GigE
        TestImageSelector_Off,  //!< The camera doesn't display a test image - Applies to: CamEmu, CameraLink, GigE and ace USB
        TestImageSelector_Testimage1,  //!< The camera generates a test image with the test image 1 pattern - Applies to: CamEmu, CameraLink, GigE and ace USB
        TestImageSelector_Testimage2,  //!< The camera generates a test image with the test image 2 pattern - Applies to: CamEmu, CameraLink, GigE and ace USB
        TestImageSelector_Testimage3,  //!< The camera generates a test image with the test image 3 pattern - Applies to: CameraLink, GigE and ace USB
        TestImageSelector_Testimage4,  //!< The camera generates a test image with the test image 4 pattern - Applies to: CameraLink, GigE and ace USB
        TestImageSelector_Testimage5,  //!< The camera generates a test image with the test image 5 pattern - Applies to: CameraLink, GigE and ace USB
        TestImageSelector_Testimage6,  //!< The camera generates a test image with the test image 6 pattern - Applies to: CameraLink, GigE and ace USB
        TestImageSelector_Testimage7,  //!< The camera generates a test image with the test image 7 pattern - Applies to: CameraLink and GigE
        TestImageSelector_VerticalLineMoving,  //!< Sets the camera to generate and transmit test images with a moving vertical line pattern - Applies to: CameraLink and GigE
        TestImageSelector_White  //!< Sets the camera to generate and transmit white test images - Applies to: CameraLink and GigE
    };

    //! Valid values for TestPattern
    enum TestPatternEnums
    {
        TestPattern_Black,  //!< The camera generates a black test pattern - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TestPattern_ColorDiagonalSawtooth8,  //!< The camera generates a test image with a color diagonal sawtooth pattern - Applies to: dart BCON, dart USB and pulse USB
        TestPattern_GreyDiagonalSawtooth8,  //!< The camera generates a test image with a gray diagonal sawtooth pattern - Applies to: dart BCON, dart USB and pulse USB
        TestPattern_Off,  //!< No test pattern is generated - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        TestPattern_Testimage1,  //!< The camera generates a test image with the test image 1 pattern - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TestPattern_Testimage2,  //!< The camera generates a test image with the test image 2 pattern - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TestPattern_Testimage3,  //!< The camera generates a test image with the test image 3 pattern - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TestPattern_Testimage6,  //!< The camera generates a test image with the test image 6 pattern - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TestPattern_White  //!< The camera generates a white test pattern - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for TimerSelector
    enum TimerSelectorEnums
    {
        TimerSelector_Timer1,  //!< Timer 1 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TimerSelector_Timer2,  //!< Timer 2 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerSelector_Timer3,  //!< Timer 3 can be configured - Applies to: CameraLink and GigE
        TimerSelector_Timer4  //!< Timer 4 can be configured - Applies to: CameraLink and GigE
    };

    //! Valid values for TimerSequenceEntrySelector
    enum TimerSequenceEntrySelectorEnums
    {
        TimerSequenceEntrySelector_Entry1,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry10,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry11,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry12,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry13,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry14,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry15,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry16,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry2,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry3,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry4,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry5,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry6,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry7,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry8,  //!< Applies to: CameraLink and GigE
        TimerSequenceEntrySelector_Entry9  //!< Applies to: CameraLink and GigE
    };

    //! Valid values for TimerSequenceTimerSelector
    enum TimerSequenceTimerSelectorEnums
    {
        TimerSequenceTimerSelector_Timer1,  //!< Applies to: CameraLink and GigE
        TimerSequenceTimerSelector_Timer2,  //!< Applies to: CameraLink and GigE
        TimerSequenceTimerSelector_Timer3,  //!< Applies to: CameraLink and GigE
        TimerSequenceTimerSelector_Timer4  //!< Applies to: CameraLink and GigE
    };

    //! Valid values for TimerStatus
    enum TimerStatusEnums
    {
        TimerStatus_TimerActive,  //!< The timer has been started - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerStatus_TimerIdle,  //!< The timer is idle - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerStatus_TimerTriggerWait  //!< The timer is waiting to be started - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for TimerTriggerActivation
    enum TimerTriggerActivationEnums
    {
        TimerTriggerActivation_AnyEdge,  //!< Trigger on the rising or falling edge of the selected source - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerActivation_FallingEdge,  //!< The timer will start at a falling edge signal change - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerActivation_LevelHigh,  //!< Trigger is active as long as the selected source signal is on a logic high level - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerActivation_LevelLow,  //!< Trigger is active as long as the selected source signal is on a logic low level - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerActivation_RisingEdge  //!< The timer will start at a rising edge signal change - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for TimerTriggerSource
    enum TimerTriggerSourceEnums
    {
        TimerTriggerSource_AcquisitionActive,  //!< The selected timer can be started by an Acquisition Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Action1,  //!< The selected timer can be started by an action signal that is defined by action signal 1 - Applies to: ace 2 GigE
        TimerTriggerSource_Action2,  //!< The selected timer can be started by an action signal that is defined by action signal 2 - Applies to: ace 2 GigE
        TimerTriggerSource_Counter1Active,  //!< The selected timer can be started by a Counter 1 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Counter1End,  //!< The selected timer can be started by a Counter 1 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Counter1Start,  //!< The selected timer can be started by a Counter 1 Start signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Counter2Active,  //!< The selected timer can be started by a Counter 2 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Counter2End,  //!< The selected timer can be started by a Counter 2 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Counter2Start,  //!< The selected timer can be started by a Counter 2 Start signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_CxpTrigger0,  //!< The selected timer can be started by a CXP Trigger 0 signal - Applies to: boost CoaXPress
        TimerTriggerSource_CxpTrigger1,  //!< The selected timer can be started by a CXP Trigger 1 signal - Applies to: boost CoaXPress
        TimerTriggerSource_ExposureActive,  //!< The selected timer can be started by an Exposure Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_ExposureStart,  //!< The selected timer can be started by an Exposure Start signal - Applies to: CameraLink, GigE and ace USB
        TimerTriggerSource_ExposureTriggerWait,  //!< The selected timer can be started by an Exposure Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_FlashWindowStart,  //!< The selected timer can be started by a Flash Window Start signal - Applies to: GigE and ace USB
        TimerTriggerSource_FrameBurstActive,  //!< The selected timer can be started by a Frame Burst Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_FrameBurstTriggerWait,  //!< The selected timer can be started by a Frame Burst Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_FrameTriggerWait,  //!< The selected timer can be started by a Frame Trigger Wait signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Line1,  //!< The selected timer can be started by a Line 1 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Line2,  //!< The selected timer can be started by a Line 2 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Line3,  //!< The selected timer can be started by a Line 3 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Line4,  //!< The selected timer can be started by a Line 4 signal - Applies to: dart 2 USB
        TimerTriggerSource_Off,  //!< The selected timer is disabled and can't be started - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_PeriodicSignal1,  //!< The selected timer can be started by a Periodic Signal 1 signal - Applies to: ace 2 GigE
        TimerTriggerSource_SoftwareSignal1,  //!< The selected timer can be started by a Software Signal 1 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_SoftwareSignal2,  //!< The selected timer can be started by a Software Signal 2 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_SoftwareSignal3,  //!< The selected timer can be started by a Software Signal 3 signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Timer1Active,  //!< The selected timer can be started by a Timer 1 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Timer1End,  //!< The selected timer can be started by a Timer 1 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Timer2Active,  //!< The selected timer can be started by a Timer 2 Active signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TimerTriggerSource_Timer2End  //!< The selected timer can be started by a Timer 2 End signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for TonalRangeAuto
    enum TonalRangeAutoEnums
    {
        TonalRangeAuto_Off,  //!< Automatic tonal range adjustment is disabled - Applies to: GigE and ace USB
        TonalRangeAuto_Once  //!< Automatic tonal range adjustment is enabled - Applies to: GigE and ace USB
    };

    //! Valid values for TonalRangeEnable
    enum TonalRangeEnableEnums
    {
        TonalRangeEnable_Off,  //!< Tonal range adjustment is disabled - Applies to: GigE and ace USB
        TonalRangeEnable_On  //!< Tonal range adjustment is enabled - Applies to: GigE and ace USB
    };

    //! Valid values for TonalRangeSelector
    enum TonalRangeSelectorEnums
    {
        TonalRangeSelector_Blue,  //!< Only the blue pixel values are used for tonal range adjustments - Applies to: GigE and ace USB
        TonalRangeSelector_Green,  //!< Only the green pixel values are used for tonal range adjustments - Applies to: GigE and ace USB
        TonalRangeSelector_Red,  //!< Only the red pixel values are used for tonal range adjustments - Applies to: GigE and ace USB
        TonalRangeSelector_Sum  //!< The summed RGB pixel values are used for tonal range adjustments - Applies to: GigE and ace USB
    };

    //! Valid values for TriggerActivation
    enum TriggerActivationEnums
    {
        TriggerActivation_AnyEdge,  //!< The selected trigger is activated by the falling or rising edge of the source signal - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TriggerActivation_FallingEdge,  //!< The selected trigger is activated by the falling edge of the source signal - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        TriggerActivation_LevelHigh,  //!< The selected trigger is activated when the source signal is high - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TriggerActivation_LevelLow,  //!< The selected trigger is activated when the source signal is low - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TriggerActivation_RisingEdge  //!< The selected trigger is activated by the rising edge of the source signal - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for TriggerControlImplementation
    enum TriggerControlImplementationEnums
    {
        TriggerControlImplementation_Legacy,  //!< The image acquisition control mode is set to Legacy - Applies to: CameraLink and GigE
        TriggerControlImplementation_Standard  //!< The image acquisition control mode is set to Standard - Applies to: CameraLink and GigE
    };

    //! Valid values for TriggerDelaySource
    enum TriggerDelaySourceEnums
    {
        TriggerDelaySource_LineTrigger,  //!< The trigger delay is expressed as a number of line triggers - Applies to: CameraLink and GigE
        TriggerDelaySource_Time_us  //!< The trigger delay is expressed as a time interval in microseconds - Applies to: CameraLink and GigE
    };

    //! Valid values for TriggerMode
    enum TriggerModeEnums
    {
        TriggerMode_Off,  //!< The currently selected trigger is turned off - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        TriggerMode_On  //!< The currently selected trigger is turned on - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for TriggerSelector
    enum TriggerSelectorEnums
    {
        TriggerSelector_AcquisitionActive,  //!< Selects the acquisition active trigger for configuration - Applies to: CameraLink and GigE
        TriggerSelector_AcquisitionEnd,  //!< Selects the acquisition end trigger for configuration - Applies to: CameraLink and GigE
        TriggerSelector_AcquisitionStart,  //!< The Acquisition Start trigger can be configured - Applies to: CamEmu, CameraLink and GigE
        TriggerSelector_ExposureActive,  //!< The Exposure Active trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSelector_ExposureEnd,  //!< The Exposure End trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSelector_ExposureStart,  //!< The Exposure Start trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSelector_FrameActive,  //!< The Frame Active trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSelector_FrameBurstActive,  //!< The Frame Burst Active trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSelector_FrameBurstEnd,  //!< The Frame Burst End trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSelector_FrameBurstStart,  //!< The Frame Burst Start trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TriggerSelector_FrameEnd,  //!< The Frame End trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSelector_FrameStart,  //!< The Frame Start trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        TriggerSelector_LineStart  //!< The Line Start trigger can be configured - Applies to: CameraLink and GigE
    };

    //! Valid values for TriggerSource
    enum TriggerSourceEnums
    {
        TriggerSource_Action1,  //!< The source signal for the selected trigger is set to action command signal 1 - Applies to: CameraLink, GigE and ace 2 GigE
        TriggerSource_Action2,  //!< The source signal for the selected trigger is set to action command signal 2 - Applies to: CameraLink, GigE and ace 2 GigE
        TriggerSource_Action3,  //!< The source signal for the selected trigger is set to action command signal 3 - Applies to: CameraLink and GigE
        TriggerSource_Action4,  //!< The source signal for the selected trigger is set to action command signal 4 - Applies to: CameraLink and GigE
        TriggerSource_CC1,  //!< The source signal for the selected trigger is set to CC1 - Applies to: CameraLink and GigE
        TriggerSource_CC2,  //!< The source signal for the selected trigger is set to CC2 - Applies to: CameraLink and GigE
        TriggerSource_CC3,  //!< The source signal for the selected trigger is set to CC3 - Applies to: CameraLink and GigE
        TriggerSource_CC4,  //!< The source signal for the selected trigger is set to CC4 - Applies to: CameraLink and GigE
        TriggerSource_Counter1Active,  //!< The Counter 1 Active trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Counter1End,  //!< The Counter 1 End trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Counter1Start,  //!< The Counter 1 Start trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Counter2Active,  //!< The Counter 2 Active trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Counter2End,  //!< The Counter 2 End trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Counter2Start,  //!< The Counter 2 Start trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_CxpTrigger0,  //!< The CXP Trigger 0 trigger can be configured - Applies to: boost CoaXPress
        TriggerSource_CxpTrigger1,  //!< The CXP Trigger 1 trigger can be configured - Applies to: boost CoaXPress
        TriggerSource_FrequencyConverter,  //!< The source signal for the selected trigger is set to the frequency converter module - Applies to: CameraLink and GigE
        TriggerSource_Line1,  //!< The source signal for the selected trigger is set to Line 1 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        TriggerSource_Line2,  //!< The source signal for the selected trigger is set to Line 2 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB and dart USB
        TriggerSource_Line3,  //!< The source signal for the selected trigger is set to Line 3 - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB and dart BCON
        TriggerSource_Line4,  //!< The source signal for the selected trigger is set to Line 4 - Applies to: CameraLink, GigE, ace USB and dart 2 USB
        TriggerSource_Line5,  //!< The source signal for the selected trigger is set to Line 5 - Applies to: CameraLink and GigE
        TriggerSource_Line6,  //!< The source signal for the selected trigger is set to Line 6 - Applies to: CameraLink and GigE
        TriggerSource_Line7,  //!< The source signal for the selected trigger is set to Line 7 - Applies to: CameraLink and GigE
        TriggerSource_Line8,  //!< The source signal for the selected trigger is set to Line 8 - Applies to: CameraLink and GigE
        TriggerSource_PeriodicSignal1,  //!< The source signal for the selected trigger is set to Periodic Signal 1 - Applies to: ace 2 GigE
        TriggerSource_ShaftEncoderModuleOut,  //!< The source signal for the selected trigger is set to the shaft encoder module - Applies to: CameraLink and GigE
        TriggerSource_Software,  //!< The source signal for the selected trigger is set to software triggering - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        TriggerSource_SoftwareSignal1,  //!< The source signal for the selected trigger is set to software signal 1 - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TriggerSource_SoftwareSignal2,  //!< The source signal for the selected trigger is set to software signal 2 - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TriggerSource_SoftwareSignal3,  //!< The source signal for the selected trigger is set to software signal 3 - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        TriggerSource_Timer1Active,  //!< The Timer 1 Active trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Timer1End,  //!< The Timer 1 End trigger can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Timer1Start,  //!< Sets the signal source for the selected trigger to timer 1 start - Applies to: CameraLink and GigE
        TriggerSource_Timer2Active,  //!< The Timer 2 Active trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_Timer2End,  //!< The Timer 2 End trigger can be configured - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB
        TriggerSource_UserOutput1,  //!< Sets the signal source for the selected trigger to user output 1 - Applies to: CameraLink and GigE
        TriggerSource_UserOutput2,  //!< Sets the signal source for the selected trigger to user output 2 - Applies to: CameraLink and GigE
        TriggerSource_VInput1,  //!< Sets the signal source for the selected trigger to Virtual Input 1 - Applies to: CameraLink and GigE
        TriggerSource_VInput2,  //!< Sets the signal source for the selected trigger to Virtual Input 2 - Applies to: CameraLink and GigE
        TriggerSource_VInput3,  //!< Sets the signal source for the selected trigger to Virtual Input 3 - Applies to: CameraLink and GigE
        TriggerSource_VInput4,  //!< Sets the signal source for the selected trigger to Virtual Input 4 - Applies to: CameraLink and GigE
        TriggerSource_VInputDecActive  //!< Sets the signal source for the selected trigger to Virtual Input Decoder Active - Applies to: CameraLink and GigE
    };

    //! Valid values for UserDefinedValueSelector
    enum UserDefinedValueSelectorEnums
    {
        UserDefinedValueSelector_Value1,  //!< The user-defined value 1 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        UserDefinedValueSelector_Value2,  //!< The user-defined value 2 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        UserDefinedValueSelector_Value3,  //!< The user-defined value 3 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        UserDefinedValueSelector_Value4,  //!< The user-defined value 4 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        UserDefinedValueSelector_Value5  //!< The user-defined value 5 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
    };

    //! Valid values for UserOutputSelector
    enum UserOutputSelectorEnums
    {
        UserOutputSelector_UserOutput0,  //!< The user-settable output signal 0 can be configured - Applies to: GigE and ace USB
        UserOutputSelector_UserOutput1,  //!< The user-settable output signal 1 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        UserOutputSelector_UserOutput2,  //!< The user-settable output signal 2 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB
        UserOutputSelector_UserOutput3,  //!< The user-settable output signal 3 can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB
        UserOutputSelector_UserOutput4,  //!< The user-settable output signal 4 can be configured - Applies to: CameraLink, GigE and dart 2 USB
        UserOutputSelector_UserOutput5,  //!< Selects user settable output signal 5 for configuration - Applies to: CameraLink and GigE
        UserOutputSelector_UserOutput6,  //!< Selects user settable output signal 6 for configuration - Applies to: CameraLink and GigE
        UserOutputSelector_UserOutput7,  //!< Selects user settable output signal 7 for configuration - Applies to: CameraLink and GigE
        UserOutputSelector_UserOutput8,  //!< Selects user settable output signal 8 for configuration - Applies to: CameraLink and GigE
        UserOutputSelector_UserOutputCC1,  //!< Selects user settable output signal CC1 for configuration - Applies to: CameraLink
        UserOutputSelector_UserOutputCC2,  //!< Selects user settable output signal CC2 for configuration - Applies to: CameraLink
        UserOutputSelector_UserOutputCC3,  //!< Selects user settable output signal CC3 for configuration - Applies to: CameraLink
        UserOutputSelector_UserOutputCC4,  //!< Selects user settable output signal CC4 for configuration - Applies to: CameraLink
        UserOutputSelector_UserOutputClSpare,  //!< The user-settable output signal CL Spare can be configured - Applies to: CameraLink
        UserOutputSelector_UserOutputLine1,  //!< User-settable output signal Line 1 can be configured - Applies to: CameraLink
        UserOutputSelector_UserOutputLine2,  //!< User-settable output signal Line 2 can be configured - Applies to: CameraLink
        UserOutputSelector_UserOutputLine3,  //!< User-settable output signal Line 3 can be configured - Applies to: CameraLink
        UserOutputSelector_UserOutputLine4  //!< User-settable output signal Line 4 can be configured - Applies to: CameraLink
    };

    //! Valid values for UserSetDefault
    enum UserSetDefaultEnums
    {
        UserSetDefault_AutoFunctions,  //!< The Auto Functions factory set is set as the default startup set - Applies to: ace USB
        UserSetDefault_Color,  //!< The factory set enabling color adjustments is set as the startup set - Applies to: ace USB
        UserSetDefault_ColorRaw,  //!< The Color Raw factory set is set as the default startup set - Applies to: ace USB
        UserSetDefault_Default,  //!< The Default User Set factory set is set as the default startup set - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        UserSetDefault_HighGain,  //!< The High Gain factory set is set as the default startup set - Applies to: ace USB
        UserSetDefault_LightMicroscopy,  //!< The Light Microscopy factory set is set as the default startup set - Applies to: ace USB
        UserSetDefault_UserSet1,  //!< User set 1 is set as the default startup set - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        UserSetDefault_UserSet2,  //!< User set 2 is set as the default startup set - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        UserSetDefault_UserSet3  //!< User set 3 is set as the default startup set - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for UserSetDefaultSelector
    enum UserSetDefaultSelectorEnums
    {
        UserSetDefaultSelector_AutoFunctions,  //!< The Auto Functions factory set is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_Color,  //!< The Color factory set is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_ColorRaw,  //!< The Color Raw factory set is set as the default startup set - Applies to: GigE
        UserSetDefaultSelector_Custom0,  //!< Custom 0 factory set is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_Custom1,  //!< Custom 1 factory set is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_Default,  //!< The Default User Set factory set is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_HighGain,  //!< The High Gain factory set is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_LightMicroscopy,  //!< The Light Microscopy factory set is set as the default startup set - Applies to: GigE
        UserSetDefaultSelector_UserSet1,  //!< User set 1 is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_UserSet2,  //!< User set 2 is set as the default startup set - Applies to: CameraLink and GigE
        UserSetDefaultSelector_UserSet3  //!< User set 3 is set as the default startup set - Applies to: CameraLink and GigE
    };

    //! Valid values for UserSetSelector
    enum UserSetSelectorEnums
    {
        UserSetSelector_AutoFunctions,  //!< The Auto Functions factory set can be loaded - Applies to: CameraLink, GigE and ace USB
        UserSetSelector_Color,  //!< The Color factory set can be loaded - Applies to: CameraLink, GigE and ace USB
        UserSetSelector_ColorRaw,  //!< The Color Raw factory set can be loaded - Applies to: GigE and ace USB
        UserSetSelector_Custom0,  //!< The Custom 0 factory set can be loaded - Applies to: CameraLink and GigE
        UserSetSelector_Custom1,  //!< The Custom 1 factory set can be loaded - Applies to: CameraLink and GigE
        UserSetSelector_Default,  //!< The Default User Set factory set can be loaded - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        UserSetSelector_HighGain,  //!< The High Gain factory set can be loaded - Applies to: CameraLink, GigE and ace USB
        UserSetSelector_LightMicroscopy,  //!< The Light Microscopy factory set can be loaded - Applies to: GigE and ace USB
        UserSetSelector_UserSet1,  //!< User set 1 can be saved, loaded, or configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        UserSetSelector_UserSet2,  //!< User set 2 can be saved, loaded, or configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
        UserSetSelector_UserSet3  //!< User set 3 can be saved, loaded, or configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB
    };

    //! Valid values for VInpSignalReadoutActivation
    enum VInpSignalReadoutActivationEnums
    {
        VInpSignalReadoutActivation_FallingEdge,  //!< Sets the type of signal change necessary to start the signal evaluation - Applies to: CameraLink and GigE
        VInpSignalReadoutActivation_RisingEdge  //!< Sets the type of signal change necessary to start the signal evaluation - Applies to: CameraLink and GigE
    };

    //! Valid values for VInpSignalSource
    enum VInpSignalSourceEnums
    {
        VInpSignalSource_CC1,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_CC2,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_CC3,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_CC4,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line1,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line2,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line3,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line4,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line5,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line6,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line7,  //!< TODO - Applies to: CameraLink and GigE
        VInpSignalSource_Line8  //!< TODO - Applies to: CameraLink and GigE
    };

    //! Valid values for VignettingCorrectionMode
    enum VignettingCorrectionModeEnums
    {
        VignettingCorrectionMode_Off,  //!< The vignetting correction is disabled - Applies to: GigE and ace USB
        VignettingCorrectionMode_On  //!< The vignetting correction is enabled - Applies to: GigE and ace USB
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalCameraParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for Basler camera devices

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class PYLONBASE_API CUniversalCameraParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalCameraParams_Params_v6_2_0( void );

        //! Destructor
        ~CUniversalCameraParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalCameraParams_Params_v6_2_0_Data;
        CUniversalCameraParams_Params_v6_2_0_Data* m_pCUniversalCameraParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Aborts the acquisition of images - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Aborts the acquisition of images. If the camera is currently exposing a frame, the camera stops exposing immediately. The readout process, if already started, is aborted. The current frame will be incomplete. Afterwards, image acquisition is switched off.

            Visibility: Beginner

            Selected by: AcquisitionMode

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionAbort" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& AcquisitionAbort;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Number of frames to acquire for each Frame Burst Start trigger - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionBurstFrameCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionBurstFrameCount;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Number of frames to acquire for each Acquisition Start trigger - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionFrameCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionFrameCount;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Acquisition frame rate of the camera in frames per second - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionFrameRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AcquisitionFrameRate;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Acquisition frame rate of the camera in frames per second - Applies to: CamEmu, CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionFrameRateAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AcquisitionFrameRateAbs;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Enables setting the camera's acquisition frame rate to a specified value - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionFrameRateEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AcquisitionFrameRateEnable;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief  Applies to: CameraLink


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionFrameRateEnum" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AcquisitionFrameRateEnumEnums>& AcquisitionFrameRateEnum;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief A check determines whether the camera is currently idle - Applies to: GigE and ace USB

            A check determines whether the camera is currently idle, i.e., not acquiring images.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionIdle" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AcquisitionIdle;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Acquisition line rate of the camera in lines per second - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionLineRateAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AcquisitionLineRateAbs;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the image acquisition mode - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selecting Parameters: AcquisitionAbort, AcquisitionStart and AcquisitionStop

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AcquisitionModeEnums>& AcquisitionMode;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Starts the acquisition of images - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Starts the acquisition of images. If the camera is configured for single frame acquisition, it will start the acquisition of one frame. If the camera is configured for continuous frame acquisition, it will start the continuous acquisition of frames.

            Visibility: Beginner

            Selected by: AcquisitionMode

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStart" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& AcquisitionStart;

        //@}


        //! \name Categories: AcquisitionStartEventData
        //@{
        /*!
            \brief Stream channel index of the Acquisition Start event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStartEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionStartEventStreamChannelIndex;

        //@}


        //! \name Categories: AcquisitionStartEventData
        //@{
        /*!
            \brief Timestamp of the Acquisition Start event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStartEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionStartEventTimestamp;

        //@}


        //! \name Categories: AcquisitionStartOvertriggerEventData
        //@{
        /*!
            \brief Stream channel index of the Acquisition Start Overtrigger event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStartOvertriggerEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionStartOvertriggerEventStreamChannelIndex;

        //@}


        //! \name Categories: AcquisitionStartOvertriggerEventData
        //@{
        /*!
            \brief Timestamp of the Acquisition Start Overtrigger event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStartOvertriggerEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionStartOvertriggerEventTimestamp;

        //@}


        //! \name Categories: AcquisitionStartWaitEventData
        //@{
        /*!
            \brief Stream channel index of the Acquisition Start Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStartWaitEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionStartWaitEventStreamChannelIndex;

        //@}


        //! \name Categories: AcquisitionStartWaitEventData
        //@{
        /*!
            \brief Timestamp of the Acquisition Start Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStartWaitEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionStartWaitEventTimestamp;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Indicates whether the camera is waiting for trigger signals - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Indicates whether the camera is waiting for trigger signals. You should only use this feature if the camera is configured for software triggering. If the camera is configured for hardware triggering, monitor the camera's Trigger Wait signals instead.

            Visibility: Expert

            Selected by: AcquisitionStatusSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AcquisitionStatus;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the signal whose status you want to check - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Sets the signal whose status you want to check. Its status can be checked by reading the Acquisition Status parameter value.

            Visibility: Expert

            Selecting Parameters: AcquisitionStatus

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStatusSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AcquisitionStatusSelectorEnums>& AcquisitionStatusSelector;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Stops the acquisition of images - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Stops the acquisition of images if a continuous image acquisition is in progress.

            Visibility: Beginner

            Selected by: AcquisitionMode

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStop" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& AcquisitionStop;

        //@}


        //! \name Categories: AcquisitionWaitEventData
        //@{
        /*!
            \brief Stream channel index of the Acquisition Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionWaitEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionWaitEventStreamChannelIndex;

        //@}


        //! \name Categories: AcquisitionWaitEventData
        //@{
        /*!
            \brief Timestamp of an Acquisition Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionWaitEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AcquisitionWaitEventTimestamp;

        //@}


        //! \name Categories: ActionControl
        //@{
        /*!
            \brief Number of separate action signals supported by the camera - Applies to: GigE

            Number of separate action signals supported by the camera. Determines how many action signals the camera can handle in parallel, i.e., how many different action commands can be configured on the camera.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionCommandCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionCommandCount;

        //@}


        //! \name Categories: ActionControl
        //@{
        /*!
            \brief Device key used for action commands - Applies to: GigE and ace 2 GigE

            Device key used to authorize the execution of an action command. If the action device key in the camera and the action device key in the protocol message are identical, the camera will execute the corresponding action.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionDeviceKey" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionDeviceKey;

        //@}


        //! \name Categories: ActionControl
        //@{
        /*!
            \brief Group key used for action commands - Applies to: GigE and ace 2 GigE

            Group key used to define a group of cameras on which action commands can be executed.

            Visibility: Beginner

            Selected by: ActionSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionGroupKey" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionGroupKey;

        //@}


        //! \name Categories: ActionControl
        //@{
        /*!
            \brief Group mask used for action commands - Applies to: GigE and ace 2 GigE

            Group mask used to filter out a sub-group of cameras belonging to a group of cameras. The cameras belonging to a sub-group execute an action at the same time. The filtering is done using a logical bitwise AND operation on the group mask number of the action command and the group mask number of a camera. If both binary numbers have at least one common bit set to 1 (i.e., the result of the AND operation is non-zero), the corresponding camera belongs to the sub-group.

            Visibility: Beginner

            Selected by: ActionSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionGroupMask" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionGroupMask;

        //@}


        //! \name Categories: ActionLateEventData
        //@{
        /*!
            \brief Stream channel index of the Action Late event - Applies to: GigE

            Stream channel index of the Action Late event. An Action Late event is raised when a scheduled action command with a timestamp in the past is received.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionLateEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionLateEventStreamChannelIndex;

        //@}


        //! \name Categories: ActionLateEventData
        //@{
        /*!
            \brief Timestamp of the Action Late event - Applies to: GigE

            Timestamp of the Action Late event. An Action Late event is raised when a scheduled action command with a timestamp in the past is received.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionLateEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionLateEventTimestamp;

        //@}


        //! \name Categories: ActionControl
        //@{
        /*!
            \brief Number of action commands that can be queued by the camera - Applies to: ace 2 GigE

            Number of action commands that can be queued by the camera. The camera will execute them in ascending order of action time. If the queue is full, additional commands will be ignored.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionQueueSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionQueueSize;

        //@}


        //! \name Categories: ActionControl
        //@{
        /*!
            \brief Action command to be configured   - Applies to: GigE and ace 2 GigE


            Visibility: Beginner

            Selecting Parameters: ActionGroupKey and ActionGroupMask

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ActionSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ActionSelector;

        //@}


        //! \name Categories: AutoFunctionControl
        //@{
        /*!
            \brief Backlight compensation to be applied - Applies to: dart BCON, dart USB and pulse USB

            Backlight compensation factor that allows the camera to compensate for underexposure. This is done by excluding a certain percentage of the brightest pixels in the image from the target average gray value calculations.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoBacklightCompensation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoBacklightCompensation;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Lower limit of the Exposure Time parameter when the Exposure Auto auto function is active - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeAbsLowerLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoExposureTimeAbsLowerLimit;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Upper limit of the Exposure Time parameter when the Exposure Auto auto function is active - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeAbsUpperLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoExposureTimeAbsUpperLimit;

        //@}


        //! \name Categories: AcquisitionControl and AutoFunctionControl
        //@{
        /*!
            \brief Lower limit of the Exposure Time parameter when the Exposure Auto auto function is active - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeLowerLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoExposureTimeLowerLimit;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Lower limit of the Exposure Time parameter when the Exposure Auto auto function is active (raw value) - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeLowerLimitRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoExposureTimeLowerLimitRaw;

        //@}


        //! \name Categories: AcquisitionControl and AutoFunctionControl
        //@{
        /*!
            \brief Upper limit of the Exposure Time parameter when the Exposure Auto auto function is active - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeUpperLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoExposureTimeUpperLimit;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Upper limit of the Exposure Time parameter when the Exposure Auto auto function is active (raw value) - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeUpperLimitRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoExposureTimeUpperLimitRaw;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Height of the auto function AOI (in pixels) - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIHeight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionAOIHeight;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Horizontal offset of the auto function AOI from the left side of the sensor (in pixels) - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIOffsetX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionAOIOffsetX;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Vertical offset from the top of the sensor to the auto function AOI (in pixels) - Applies to: CameraLink and GigE

            Vertical offset of the auto function AOI from the top of the sensor (in pixels).

            Visibility: Beginner

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIOffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionAOIOffsetY;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Sets which auto function AOI can be configured - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selecting Parameters: AutoFunctionAOIHeight, AutoFunctionAOIOffsetX, AutoFunctionAOIOffsetY, AutoFunctionAOIUsageIntensity, AutoFunctionAOIUsageRedLightCorrection, AutoFunctionAOIUsageWhiteBalance and AutoFunctionAOIWidth

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOISelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AutoFunctionAOISelectorEnums>& AutoFunctionAOISelector;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function AOI - Applies to: CameraLink and GigE

            Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function AOI. For this parameter, Gain Auto and Exposure Auto are considered as a single auto function named 'Intensity'.

            Visibility: Beginner

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIUsageIntensity" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionAOIUsageIntensity;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Assigns the Red Light Correction auto function to the currently selected auto function AOI - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIUsageRedLightCorrection" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionAOIUsageRedLightCorrection;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Assigns the Tonal Range Auto auto function to the currently selected auto function AOI - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIUsageTonalRange" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionAOIUsageTonalRange;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Assigns the Balance White Auto auto function to the currently selected auto function AOI - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIUsageWhiteBalance" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionAOIUsageWhiteBalance;

        //@}


        //! \name Categories: AutoFunctionAOIControl
        //@{
        /*!
            \brief Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function AOI - Applies to: ace USB

            Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function AOI. For this parameter, Gain Auto and Exposure Auto are considered as a single auto function named 'Brightness'.

            Visibility: Invisible

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIUseBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionAOIUseBrightness;

        //@}


        //! \name Categories: AutoFunctionAOIControl
        //@{
        /*!
            \brief Assigns the Balance White auto function to the currently selected auto function AOI - Applies to: ace USB


            Visibility: Invisible

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIUseWhiteBalance" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionAOIUseWhiteBalance;

        //@}


        //! \name Categories: AutoFunctionAOIs
        //@{
        /*!
            \brief Width of the auto function AOI (in pixels) - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: AutoFunctionAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionAOIWidth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionAOIWidth;

        //@}


        //! \name Categories: AutoFunctionControl and AutoFunctions
        //@{
        /*!
            \brief Sets how gain and exposure time will be balanced when the camera is making automatic adjustments - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionProfile" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AutoFunctionProfileEnums>& AutoFunctionProfile;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Height of the auto function ROI (in pixels) - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIHeight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionROIHeight;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Highlights the current auto function ROI in the image window - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Highlights the current auto function ROI in the image window. Areas that do not belong to the current ROI appear darker.

            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIHighlight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionROIHighlight;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Horizontal offset of the auto function ROI from the left side of the sensor (in pixels) - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIOffsetX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionROIOffsetX;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Vertical offset from the top of the sensor to the auto function ROI (in pixels) - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Vertical offset of the auto function ROI from the top of the sensor (in pixels).

            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIOffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionROIOffsetY;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Sets which auto function ROI can be configured - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selecting Parameters: AutoFunctionROIHeight, AutoFunctionROIHighlight, AutoFunctionROIOffsetX, AutoFunctionROIOffsetY, AutoFunctionROIUseBrightness, AutoFunctionROIUseTonalRange, AutoFunctionROIUseWhiteBalance and AutoFunctionROIWidth

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROISelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AutoFunctionROISelectorEnums>& AutoFunctionROISelector;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function ROI - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function ROI. For this parameter, Gain Auto and Exposure Auto are considered as a single auto function named 'Brightness'.

            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIUseBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionROIUseBrightness;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Assigns the Tonal Range Auto auto function to the currently selected auto function ROI - Applies to: ace USB


            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIUseTonalRange" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionROIUseTonalRange;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Assigns the Balance White Auto auto function to the currently selected auto function ROI - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIUseWhiteBalance" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoFunctionROIUseWhiteBalance;

        //@}


        //! \name Categories: AutoFunctionROIControl
        //@{
        /*!
            \brief Width of the auto function ROI (in pixels) - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: AutoFunctionROISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIWidth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoFunctionROIWidth;

        //@}


        //! \name Categories: AnalogControl and AutoFunctionControl
        //@{
        /*!
            \brief Lower limit of the Gain parameter when the Gain Auto auto function is active - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: GainSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoGainLowerLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoGainLowerLimit;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Lower limit of the Gain parameter when the Gain Auto auto function is active (raw value) - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoGainRawLowerLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoGainRawLowerLimit;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Upper limit of the Gain parameter when the Gain Auto auto function is active (raw value) - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoGainRawUpperLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoGainRawUpperLimit;

        //@}


        //! \name Categories: AnalogControl and AutoFunctionControl
        //@{
        /*!
            \brief Upper limit of the Gain parameter when the Gain Auto auto function is active - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: GainSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoGainUpperLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoGainUpperLimit;

        //@}


        //! \name Categories: AutoFunctionControl
        //@{
        /*!
            \brief Target brightness for the Gain Auto and the Exposure Auto auto functions - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTargetBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoTargetBrightness;

        //@}


        //! \name Categories: AutoFunctionControl
        //@{
        /*!
            \brief Brightness adjustment damping factor to be applied   - Applies to: dart BCON, dart USB and pulse USB

            Brightness adjustment damping factor to be applied. This controls the speed with which pixel gray values are changed when Exposure Auto, Gain Auto, or both are enabled. The lower the damping factor, the faster the target brightness value is reached.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTargetBrightnessDamping" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoTargetBrightnessDamping;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Target brightness for the Gain Auto and the Exposure Auto auto functions - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTargetValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoTargetValue;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Sets which parts of the tonal range can be adjusted - Applies to: GigE and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeAdjustmentSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AutoTonalRangeAdjustmentSelectorEnums>& AutoTonalRangeAdjustmentSelector;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Sets the kind of tonal range auto adjustment - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeModeSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AutoTonalRangeModeSelectorEnums>& AutoTonalRangeModeSelector;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Bright target value to be used during automatic tonal range adjustments - Applies to: GigE and ace USB

            Bright target value to be used during automatic tonal range adjustments. When you enable the Tonal Range Auto auto function, the camera sets the Tonal Range Target Bright parameter to this value. Not available if the Auto Tonal Range Mode parameter is set to Color.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeTargetBright" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoTonalRangeTargetBright;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Dark target value to be used during automatic tonal range adjustments - Applies to: GigE and ace USB

            Dark target value to be used during automatic tonal range adjustments. When you enable the Tonal Range Auto auto function, the camera sets the Tonal Range Target Dark parameter to this value. Not available if the Auto Tonal Range Mode parameter is set to Color.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeTargetDark" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoTonalRangeTargetDark;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Threshold value from which the Tonal Range Source Bright parameter value is calculated during automatic tonal range adjustments - Applies to: GigE and ace USB

            Threshold value from which the Tonal Range Source Bright parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned auto function ROI. Example: Assume you set the Auto Tonal Range Threshold Bright parameter to 0.1 and enable the Tonal Range Auto auto function. Now assume that 0.1 % of the pixels in the assigned auto function ROI have a pixel value greater than or equal to 240. The camera automatically detects this, sets the Tonal Range Source Bright parameter to 240, and starts tonal range adjustments.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeThresholdBright" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoTonalRangeThresholdBright;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Threshold value from which the Tonal Range Source Bright parameter value is calculated during automatic tonal range adjustments (raw value) - Applies to: GigE

            Threshold value from which the Tonal Range Source Bright parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned auto function ROI. Example: Assume you set the Auto Tonal Range Threshold Bright parameter to 0.1 and enable the Tonal Range Auto auto function. Now assume that 0.1 % of the pixels in the assigned auto function ROI have a pixel value greater than or equal to 240. The camera automatically detects this, sets the Tonal Range Source Bright parameter to 240, and starts tonal range adjustments.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeThresholdBrightRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoTonalRangeThresholdBrightRaw;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Threshold value from which the Tonal Range Source Dark parameter value is calculated during automatic tonal range adjustments - Applies to: GigE and ace USB

            Threshold value from which the Tonal Range Source Dark parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned auto function ROI. Example: Assume you set the Auto Tonal Range Threshold Dark parameter to 0.2 and enable the Tonal Range Auto auto function. Now assume that 0.2 % of the pixels in the assigned auto function ROI have a pixel value lower than or equal to 30. The camera automatically detects this, sets the Tonal Range Source Dark parameter to 30, and starts tonal range adjustments.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeThresholdDark" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AutoTonalRangeThresholdDark;

        //@}


        //! \name Categories: AutoTonalRangeControl
        //@{
        /*!
            \brief Threshold value from which the Tonal Range Source Dark parameter value is calculated during automatic tonal range adjustments (raw value) - Applies to: GigE

            Threshold value from which the Tonal Range Source Dark parameter value is calculated during automatic tonal range adjustments. The parameter is expressed as a percentage of all pixels in the assigned auto function ROI. Example: Assume you set the Auto Tonal Range Threshold Dark parameter to 0.2 and enable the Tonal Range Auto auto function. Now assume that 0.2 % of the pixels in the assigned auto function ROI have a pixel value lower than or equal to 30. The camera automatically detects this, sets the Tonal Range Source Dark parameter to 30, and starts tonal range adjustments.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTonalRangeThresholdDarkRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AutoTonalRangeThresholdDarkRaw;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief A serial framing error occurred on reception - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialFramingError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BLCSerialFramingError;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief A serial parity error occurred on reception - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialParityError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BLCSerialParityError;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Reports the baud rate of the serial communication module - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortBaudRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BLCSerialPortBaudRateEnums>& BLCSerialPortBaudRate;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Clears the error flags of the serial communication module - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortClearErrors" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BLCSerialPortClearErrors;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Reports the parity bit configuration of the serial communication module - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortParity" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BLCSerialPortParityEnums>& BLCSerialPortParity;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Reads and removes the front byte value from the serial communication receive queue - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortReceiveCmd" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BLCSerialPortReceiveCmd;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Last byte value read from the serial communication receive queue - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortReceiveValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BLCSerialPortReceiveValue;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Sets the signal source for the serial communication module - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BLCSerialPortSourceEnums>& BLCSerialPortSource;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Reports the number of stop bits used by the serial communication module - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortStopBits" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BLCSerialPortStopBitsEnums>& BLCSerialPortStopBits;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Writes the current byte value to the transmit queue - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortTransmitCmd" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BLCSerialPortTransmitCmd;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Byte value to be written to the transmit queue - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialPortTransmitValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BLCSerialPortTransmitValue;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Reports the status of the serial communication receive queue - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialReceiveQueueStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BLCSerialReceiveQueueStatusEnums>& BLCSerialReceiveQueueStatus;

        //@}


        //! \name Categories: BLCSerialPortControl
        //@{
        /*!
            \brief Reports the status of the serial communication transmit queue - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BLCSerialTransmitQueueStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BLCSerialTransmitQueueStatusEnums>& BLCSerialTransmitQueueStatus;

        //@}


        //! \name Categories: ImageQualityControl and WhiteBalanceControl
        //@{
        /*!
            \brief Balance Ratio value to be applied to the currently selected channel - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: BalanceRatioSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceRatio" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BalanceRatio;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Balance Ratio value to be applied to the currently selected channel - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: BalanceRatioSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceRatioAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BalanceRatioAbs;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Balance Ratio value to be applied to the currently selected channel (raw value) - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: BalanceRatioSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceRatioRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BalanceRatioRaw;

        //@}


        //! \name Categories: ColorImprovementsControl, ImageQualityControl and WhiteBalanceControl
        //@{
        /*!
            \brief Sets which color channel can be adjusted when performing manual white balance - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Sets which color channel can be adjusted when performing manual white balance. All changes to the Balance Ratio parameter will be applied to the selected color channel.

            Visibility: Beginner

            Selecting Parameters: BalanceRatio, BalanceRatioAbs and BalanceRatioRaw

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceRatioSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BalanceRatioSelectorEnums>& BalanceRatioSelector;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Balance White adjustment damping factor to be applied - Applies to: CameraLink and GigE

            Balance White adjustment damping factor to be applied. This controls the speed with which the camera adjusts colors when the Balance White Auto auto function is enabled. This can be useful, for example, when objects move into the camera's field of view and the light conditions are changing gradually due to the moving objects.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceWhiteAdjustmentDampingAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BalanceWhiteAdjustmentDampingAbs;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Balance White adjustment damping factor to be applied (raw value) - Applies to: CameraLink and GigE

            Balance White adjustment damping factor to be applied (raw value). This controls the speed with which the camera adjusts colors when the Balance White Auto auto function is enabled. This can be useful, for example, when objects move into the camera's field of view and the light conditions are changing gradually due to the moving objects.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceWhiteAdjustmentDampingRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BalanceWhiteAdjustmentDampingRaw;

        //@}


        //! \name Categories: ColorImprovementsControl, ImageQualityControl and WhiteBalanceControl
        //@{
        /*!
            \brief Sets the operation mode of the Balance White Auto auto function - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceWhiteAuto" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BalanceWhiteAutoEnums>& BalanceWhiteAuto;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Resets all white balance adjustments - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceWhiteReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BalanceWhiteReset;

        //@}


        //! \name Categories: GigEVision
        //@{
        /*!
            \brief Sets a predefined bandwidth reserve or enables manual configuration of the bandwidth reserve - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BandwidthReserveMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BandwidthReserveModeEnums>& BandwidthReserveMode;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Sets the clock frequency for the BCON transport layer - Applies to: dart BCON


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BconClockFrequency" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BconClockFrequencyEnums>& BconClockFrequency;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Sets the number of pixels transmitted per clock cycle via the BCON interface - Applies to: dart BCON


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BconPixelsPerClockCycle" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BconPixelsPerClockCycleEnums>& BconPixelsPerClockCycle;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Number of adjacent horizontal pixels to be summed - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Number of adjacent horizontal pixels to be summed. Their charges will be summed and reported out of the camera as a single pixel.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BinningHorizontal" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BinningHorizontal;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Sets the binning mode for horizontal binning - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BinningHorizontalMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BinningHorizontalModeEnums>& BinningHorizontalMode;

        //@}


        //! \name Categories: AOI
        //@{
        /*!
            \brief Sets the binning mode for horizontal binning - Applies to: CameraLink


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BinningModeHorizontal" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BinningModeHorizontalEnums>& BinningModeHorizontal;

        //@}


        //! \name Categories: AOI
        //@{
        /*!
            \brief Sets the binning mode for vertical binning - Applies to: CameraLink


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BinningModeVertical" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BinningModeVerticalEnums>& BinningModeVertical;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Number of adjacent vertical pixels to be summed - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Number of adjacent vertical pixels to be summed. Their charges will be summed and reported out of the camera as a single pixel.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BinningVertical" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BinningVertical;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Sets the binning mode for vertical binning - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BinningVerticalMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BinningVerticalModeEnums>& BinningVerticalMode;

        //@}


        //! \name Categories: AnalogControl
        //@{
        /*!
            \brief Black level value to be applied to the currently selected sensor tap - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: BlackLevelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BlackLevel" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BlackLevel;

        //@}


        //! \name Categories: AnalogControls
        //@{
        /*!
            \brief Sets the value of the selected black level control as a float - Applies to: CameraLink and GigE

            This value sets the selected black level control as a float value.

            Visibility: Beginner

            Selected by: BlackLevelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BlackLevelAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BlackLevelAbs;

        //@}


        //! \name Categories: AnalogControls
        //@{
        /*!
            \brief Black level value to be applied to the currently selected sensor tap (raw value) - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: BlackLevelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BlackLevelRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BlackLevelRaw;

        //@}


        //! \name Categories: AnalogControl and AnalogControls
        //@{
        /*!
            \brief Sets which sensor tap can be configured - Applies to: CameraLink, GigE, ace USB, dart BCON, dart USB and pulse USB

            Sets which sensor tap can be configured. All changes to the Black Level parameter will be applied to the selected sensor tap.

            Visibility: Beginner

            Selecting Parameters: BlackLevel, BlackLevelAbs and BlackLevelRaw

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BlackLevelSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BlackLevelSelectorEnums>& BlackLevelSelector;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Sets the burst mode - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslAcquisitionBurstMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslAcquisitionBurstModeEnums>& BslAcquisitionBurstMode;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Sets whether Acquisition Stop commands abort exposure - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslAcquisitionStopMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslAcquisitionStopModeEnums>& BslAcquisitionStopMode;

        //@}


        //! \name Categories: ImageProcessingControl and ImageQualityControl
        //@{
        /*!
            \brief Brightness value to be applied - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Adjusting the brightness lightens or darkens the entire image.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslBrightness;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Brightness value to be applied (raw value) - Applies to: GigE

            Adjusting the brightness lightens or darkens the entire image.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslBrightnessRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslBrightnessRaw;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Centers the image horizontally - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslCenterX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslCenterX;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Centers the image vertically - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslCenterY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslCenterY;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Indicates the status of the target brightness adjustments performed by the Exposure Auto and Gain Auto auto functions - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslChunkAutoBrightnessStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslChunkAutoBrightnessStatusEnums>& BslChunkAutoBrightnessStatus;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Sets which information should be included in the Chunk Timestamp Value chunk - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            Selecting Parameters: BslChunkTimestampValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslChunkTimestampSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslChunkTimestampSelectorEnums>& BslChunkTimestampSelector;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            Selected by: BslChunkTimestampSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslChunkTimestampValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslChunkTimestampValue;

        //@}


        //! \name Categories: ColorAdjustmentControl
        //@{
        /*!
            \brief Enables color adjustment - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslColorAdjustmentEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslColorAdjustmentEnable;

        //@}


        //! \name Categories: ColorAdjustmentControl
        //@{
        /*!
            \brief Hue adjustment value to be applied to the currently selected color channel - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selected by: BslColorAdjustmentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslColorAdjustmentHue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslColorAdjustmentHue;

        //@}


        //! \name Categories: ColorAdjustmentControl
        //@{
        /*!
            \brief Saturation adjustment value to be applied to the currently selected color channel - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selected by: BslColorAdjustmentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslColorAdjustmentSaturation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslColorAdjustmentSaturation;

        //@}


        //! \name Categories: ColorAdjustmentControl
        //@{
        /*!
            \brief Sets which color in your images will be adjusted - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selecting Parameters: BslColorAdjustmentHue and BslColorAdjustmentSaturation

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslColorAdjustmentSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslColorAdjustmentSelectorEnums>& BslColorAdjustmentSelector;

        //@}


        //! \name Categories: AnalogControl and ImageProcessingControl
        //@{
        /*!
            \brief Sets the color space for image acquisitions - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Sets the color space for image acquisitions. Note that the gamma correction value also influences the perception of brightness in the resulting images.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslColorSpace" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslColorSpaceEnums>& BslColorSpace;

        //@}


        //! \name Categories: AnalogControl
        //@{
        /*!
            \brief Sets the color space for image acquisitions - Applies to: dart BCON, dart USB and pulse USB

            Sets the color space for image acquisitions. Note that the gamma correction value also influences the perception of brightness in the resulting images.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslColorSpaceMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslColorSpaceModeEnums>& BslColorSpaceMode;

        //@}


        //! \name Categories: ImageProcessingControl and ImageQualityControl
        //@{
        /*!
            \brief Contrast value to be applied - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Adjusting the contrast increases the difference between light and dark areas in the image.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslContrast" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslContrast;

        //@}


        //! \name Categories: ImageProcessingControl and ImageQualityControl
        //@{
        /*!
            \brief Sets the contrast mode - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslContrastMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslContrastModeEnums>& BslContrastMode;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Contrast value to be applied (raw value) - Applies to: GigE

            Adjusting the contrast increases the difference between light and dark areas in the image.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslContrastRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslContrastRaw;

        //@}


        //! \name Categories: ImageProcessingControl
        //@{
        /*!
            \brief Identifies outlier pixels and adjusts their intensity value - Applies to: dart 2 USB

            Pixels that have a significantly higher or lower intensity value than the neighboring pixels are called outlier pixels. This feature identifies them and adjusts their intensity value.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslDefectPixelCorrectionMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslDefectPixelCorrectionModeEnums>& BslDefectPixelCorrectionMode;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Actual bandwidth the camera will use - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data with the current camera settings.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslDeviceLinkCurrentThroughput" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslDeviceLinkCurrentThroughput;

        //@}


        //! \name Categories: ErrorReportControl
        //@{
        /*!
            \brief Indicates whether an internal error occured on the device - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Indicates whether an internal error occured on the device. If an error occured, you can use the Error Report Next command to determine the error code.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslErrorPresent" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslErrorPresent;

        //@}


        //! \name Categories: ErrorReportControl
        //@{
        /*!
            \brief Retrieves the next error code from the device - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Retrieves the next error code from the device. To check the error code, get the value of the Error Report Value parameter.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslErrorReportNext" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslErrorReportNext;

        //@}


        //! \name Categories: ErrorReportControl
        //@{
        /*!
            \brief Error code indicating the cause of the internal error - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Error code indicating the cause of the internal error. If there are multiple errors, execute the Error Report Next command to retrieve the next error code. A parameter value of 0 means that there are no more error codes to retrieve.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslErrorReportValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslErrorReportValue;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Sets the exposure time mode - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslExposureTimeMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslExposureTimeModeEnums>& BslExposureTimeMode;

        //@}


        //! \name Categories: ImageProcessingControl and ImageQualityControl
        //@{
        /*!
            \brief Hue shift value to be applied - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Adjusting the hue shifts the colors of the image. This can be useful, e.g., to correct minor color shifts or to create false-color images.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslHue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslHue;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Hue shift value to be applied (raw value) - Applies to: GigE

            Adjusting the hue shifts the colors of the image. This can be useful, e.g., to correct minor color shifts or to create false-color images.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslHueRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslHueRaw;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Hue shift value to be applied - Applies to: dart BCON, dart USB and pulse USB

            Adjusting the hue shifts the colors of the image. This can be useful, e.g., to correct minor color shifts or to create false-color images.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslHueValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslHueValue;

        //@}


        //! \name Categories: ImageCompression
        //@{
        /*!
            \brief Ratio between the compressed payload size and the uncompressed payload size of the last acquired image - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslImageCompressionLastRatio" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslImageCompressionLastRatio;

        //@}


        //! \name Categories: ImageCompression
        //@{
        /*!
            \brief Compressed payload size of the last acquired image in bytes - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslImageCompressionLastSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslImageCompressionLastSize;

        //@}


        //! \name Categories: ImageCompression
        //@{
        /*!
            \brief Maximum ratio between the payload size of compressed and uncompressed images - Applies to: ace 2 GigE and ace 2 USB

            Maximum ratio between the payload size of compressed and uncompressed images. For example, if you set this parameter to 70, the camera will try to compress the payload of images to 70 % or less of the original size. Note that if the camera can't achieve compression with the specified Image Compression Ratio and Image Compression Rate Option settings, frames will be skipped.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslImageCompressionRatio" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslImageCompressionRatio;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Enables the Immediate Trigger mode - Applies to: dart BCON, dart USB and pulse USB

            Enables the Immediate Trigger mode. If this mode is enabled, exposure starts immediately after triggering, but changes to image parameters become effective with a short delay, i.e., after one or more images have been acquired.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslImmediateTriggerMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslImmediateTriggerModeEnums>& BslImmediateTriggerMode;

        //@}


        //! \name Categories: DigitalIOControl
        //@{
        /*!
            \brief Time period in which the camera evaluates all changes and durations of logical states of the input signal   - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Time period in which the camera evaluates all changes and durations of logical states of the input signal. During evaluation, the camera calculates the mean value over time and applies a threshold function to the result to reconstruct the digital signal. This removes noise, interference, etc. as well as signal pulses shorter than the filter time.

            Visibility: Expert

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslInputFilterTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslInputFilterTime;

        //@}


        //! \name Categories: DigitalIOControl
        //@{
        /*!
            \brief Time period in which the camera doesn't accept any further trigger signals or signal changes after receiving an input trigger signal - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Time period in which the camera doesn't accept any further trigger signals or signal changes after receiving an input trigger signal. This is useful if you want to avoid false triggering caused by multiple trigger signals arriving in quick succession (contact bounce).

            Visibility: Expert

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslInputHoldOffTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslInputHoldOffTime;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Searches for light devices connected to your camera - Applies to: GigE and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightControlEnumerateDevices" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslLightControlEnumerateDevices;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Indicates whether any of the light devices are currently experiencing problems - Applies to: GigE and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightControlErrorStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightControlErrorStatusEnums>& BslLightControlErrorStatus;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Enables/disables the light control features - Applies to: GigE and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightControlMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightControlModeEnums>& BslLightControlMode;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Sets which line is used to control the light features - Applies to: GigE and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightControlSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightControlSourceEnums>& BslLightControlSource;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Indicates the current state of the light control mode - Applies to: GigE and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightControlStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightControlStatusEnums>& BslLightControlStatus;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Brightness of the light in percent of total brightness available - Applies to: GigE and ace USB

            Brightness of the light in percent of total brightness available. Setting this parameter to 100 % means that the light device draws the maximum current as specified by the Light Device Max Current parameter.

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslLightDeviceBrightness;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Brightness of the light in percent of total brightness available (raw value) - Applies to: GigE

            Brightness of the light in percent of total brightness available (raw value). Setting this parameter to 100 % means that the light device draws the maximum current as specified by the the Light Device Max Current parameter.

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceBrightnessRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslLightDeviceBrightnessRaw;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Changes the ID of the currently selected light device - Applies to: GigE and ace USB

            Changes the ID of the currently selected light device. The new ID will be assigned immediately.

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceChangeID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightDeviceChangeIDEnums>& BslLightDeviceChangeID;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Clears the last light device error - Applies to: GigE and ace USB


            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceClearLastError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslLightDeviceClearLastError;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Version of the light device's firmware - Applies to: GigE and ace USB


            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceFirmwareVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& BslLightDeviceFirmwareVersion;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Indicates the last light device error - Applies to: GigE and ace USB


            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceLastError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightDeviceLastErrorEnums>& BslLightDeviceLastError;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Maximum current that the light device is going to use - Applies to: GigE and ace USB

            Maximum current that the light device is going to use. The value should not exceed the power rating of the device. To change the setting, the Light Device Operation Mode parameter must be set to Off.

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceMaxCurrent" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslLightDeviceMaxCurrent;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Maximum current that the light device is going to use (raw value) - Applies to: GigE

            Maximum current that the light device is going to use (raw value). The value should not exceed the power rating of the device. To change the setting, the Light Device Operation Mode parameter must be set to Off.

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceMaxCurrentRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslLightDeviceMaxCurrentRaw;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Sets the operation mode of the light device - Applies to: GigE and ace USB

            Sets the operation mode of the light device. 

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceOperationMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightDeviceOperationModeEnums>& BslLightDeviceOperationMode;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Sets which light device can be configured - Applies to: GigE and ace USB

            Sets which light device can be configured. To populate the list, use the Light Control Enumerate Devices command first. All subsequent parameter changes in this category will be applied to the device selected here.

            Visibility: Expert

            Selecting Parameters: BslLightDeviceBrightness, BslLightDeviceBrightnessRaw, BslLightDeviceChangeID, BslLightDeviceClearLastError, BslLightDeviceFirmwareVersion, BslLightDeviceLastError, BslLightDeviceMaxCurrent, BslLightDeviceMaxCurrentRaw, BslLightDeviceOperationMode, BslLightDeviceStrobeDuration, BslLightDeviceStrobeDurationRaw and BslLightDeviceStrobeMode

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightDeviceSelectorEnums>& BslLightDeviceSelector;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Duration of the individual strobe pulses - Applies to: GigE and ace USB

            Duration of the individual strobe pulses. The maximum value is 655 350 microseconds.

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceStrobeDuration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslLightDeviceStrobeDuration;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Duration of the individual strobe pulses (raw value) - Applies to: GigE

            Duration of the individual strobe pulses (raw value). The maximum value is 655 350 microseconds.

            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceStrobeDurationRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslLightDeviceStrobeDurationRaw;

        //@}


        //! \name Categories: BslLightControl
        //@{
        /*!
            \brief Sets the strobe mode of the light device - Applies to: GigE and ace USB


            Visibility: Expert

            Selected by: BslLightDeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightDeviceStrobeMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightDeviceStrobeModeEnums>& BslLightDeviceStrobeMode;

        //@}


        //! \name Categories: ImageProcessingControl
        //@{
        /*!
            \brief Sets the light source preset - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Sets the light source preset. The colors in the image will be corrected so that they are appropriate for the selected light source.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightSourcePreset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightSourcePresetEnums>& BslLightSourcePreset;

        //@}


        //! \name Categories: ImageProcessingControl
        //@{
        /*!
            \brief Enables adjustment of the selected feature - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Enables adjustment of the feature specified by the Light Source Preset Feature Selector parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightSourcePresetFeatureEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslLightSourcePresetFeatureEnable;

        //@}


        //! \name Categories: ImageProcessingControl
        //@{
        /*!
            \brief Sets which features the camera adjusts when you select a light source preset - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Sets which features the camera adjusts when you select a light source preset. By default, the camera adjust all features.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightSourcePresetFeatureSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslLightSourcePresetFeatureSelectorEnums>& BslLightSourcePresetFeatureSelector;

        //@}


        //! \name Categories: DigitalIOControl
        //@{
        /*!
            \brief Indicates whether a GPIO line is overloaded, i e , not powered correctly - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Indicates whether a GPIO line is overloaded, i.e., not powered correctly. A value of true (1) means that the GPIO line is overloaded. 

            Visibility: Expert

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLineOverloadStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslLineOverloadStatus;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Horizontal offset of the currently selected column - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selected by: BslMultipleROIColumnSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIColumnOffset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslMultipleROIColumnOffset;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Sets which column can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selecting Parameters: BslMultipleROIColumnOffset and BslMultipleROIColumnSize

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIColumnSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslMultipleROIColumnSelectorEnums>& BslMultipleROIColumnSelector;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Width of the currently selected column - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selected by: BslMultipleROIColumnSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIColumnSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslMultipleROIColumnSize;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Enables or disables the ability to define multiple regions in horizontal direction - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Enables or disables the ability to define multiple regions in horizontal direction. When disabled, the width and horizontal offset of all regions is defined by the Width and OffsetX parameters, and the BslMultipleROIColumnOffset and BslMultipleROIColumnSize parameter values are ignored.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIColumnsEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslMultipleROIColumnsEnable;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Vertical offset of the currently selected row - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selected by: BslMultipleROIRowSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIRowOffset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslMultipleROIRowOffset;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Sets which row can be configured - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selecting Parameters: BslMultipleROIRowOffset and BslMultipleROIRowSize

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIRowSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslMultipleROIRowSelectorEnums>& BslMultipleROIRowSelector;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Height of the currently selected row - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selected by: BslMultipleROIRowSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIRowSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslMultipleROIRowSize;

        //@}


        //! \name Categories: MultipleROI
        //@{
        /*!
            \brief Enables or disables the ability to define multiple regions in vertical direction - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Enables or disables the ability to define multiple regions in vertical direction. When disabled, the height and vertical offset of all regions is defined by the Height and OffsetY parameters, and the BslMultipleROIRowOffset and BslMultipleROIRowSize parameter values are ignored.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslMultipleROIRowsEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslMultipleROIRowsEnable;

        //@}


        //! \name Categories: BslPGIControl and PGIControl
        //@{
        /*!
            \brief Amount of noise reduction to be applied - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB

            Amount of noise reduction to be applied. The higher the value, the less chroma noise will be visible in your images. However, very high values may result in image information loss.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslNoiseReduction" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslNoiseReduction;

        //@}


        //! \name Categories: BslPeriodicSignalControl
        //@{
        /*!
            \brief Delay to be applied to the periodic signal in microseconds - Applies to: ace 2 GigE


            Visibility: Expert

            Selected by: BslPeriodicSignalSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPeriodicSignalDelay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslPeriodicSignalDelay;

        //@}


        //! \name Categories: BslPeriodicSignalControl
        //@{
        /*!
            \brief Length of the periodic signal in microseconds - Applies to: ace 2 GigE


            Visibility: Expert

            Selected by: BslPeriodicSignalSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPeriodicSignalPeriod" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslPeriodicSignalPeriod;

        //@}


        //! \name Categories: BslPeriodicSignalControl
        //@{
        /*!
            \brief Sets the periodic signal channel to be configured - Applies to: ace 2 GigE


            Visibility: Expert

            Selecting Parameters: BslPeriodicSignalDelay, BslPeriodicSignalPeriod and BslPeriodicSignalSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPeriodicSignalSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslPeriodicSignalSelectorEnums>& BslPeriodicSignalSelector;

        //@}


        //! \name Categories: BslPeriodicSignalControl
        //@{
        /*!
            \brief Indicates whether the camera is synchronized via Precision Time Protocol (PTP) - Applies to: ace 2 GigE


            Visibility: Expert

            Selected by: BslPeriodicSignalSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPeriodicSignalSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslPeriodicSignalSourceEnums>& BslPeriodicSignalSource;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Indicates the PTP delay mechanism - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpDelayMechanism" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslPtpDelayMechanismEnums>& BslPtpDelayMechanism;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Enables PTP management - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpManagementEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslPtpManagementEnable;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Sets the mode for PTP network communication - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpNetworkMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslPtpNetworkModeEnums>& BslPtpNetworkMode;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Value indicating the priority of the device when determining the master clock - Applies to: ace 2 GigE

            Value indicating the priority of the device when determining the master clock.  The network device with the lowest Priority 1 setting is the master clock.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpPriority1" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslPtpPriority1;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Sets the default PTP profile - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpProfile" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslPtpProfileEnums>& BslPtpProfile;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Configures a two-step clock if enabled or a one-step clock if disabled - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpTwoStep" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslPtpTwoStep;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Unicast port address - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpUcPortAddr" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslPtpUcPortAddr;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Unicast port address index - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslPtpUcPortAddrIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslPtpUcPortAddrIndex;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Maximum number of frames that can be acquired per second with current camera settings - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Maximum number of frames that can be acquired per second with current camera settings. In High Speed burst mode, this value is usually higher than the Resulting Transfer Frame Rate parameter value.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslResultingAcquisitionFrameRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslResultingAcquisitionFrameRate;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Maximum number of bursts per second with current camera settings - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslResultingFrameBurstRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslResultingFrameBurstRate;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Maximum number of frames that can be transferred per second with current camera settings - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Maximum number of frames that can be transferred per second with current camera settings. This value indicates the peak frame rate to be expected at the camera's output. In High Speed burst mode, this value is usually lower than the Resulting Acquisition Frame Rate parameter value.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslResultingTransferFrameRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslResultingTransferFrameRate;

        //@}


        //! \name Categories: ImageProcessingControl and ImageQualityControl
        //@{
        /*!
            \brief Saturation value to be applied - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Adjusting the saturation changes the colorfulness (intensity) of the colors. A higher saturation, for example, makes colors easier to distinguish.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSaturation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslSaturation;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Saturation value to be applied (raw value) - Applies to: GigE

            Adjusting the saturation changes the colorfulness (intensity) of the colors. A higher saturation, for example, makes colors easier to distinguish.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSaturationRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslSaturationRaw;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Saturation value to be applied - Applies to: dart BCON, dart USB and pulse USB

            Adjusting the saturation changes the colorfulness (intensity) of the colors. A higher saturation, for example, makes colors easier to distinguish.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSaturationValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslSaturationValue;

        //@}


        //! \name Categories: ImageProcessingControl
        //@{
        /*!
            \brief Scaling factor to be applied to all images - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB

            Scaling factor to be applied to all images. Scaling is performed using the Pixel Beyond feature.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslScalingFactor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslScalingFactor;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Sets the bit depth of the image sensor's data output - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Sets the bit depth of the image sensor's data output. You can set the sensor bit depth independently of the pixel format used if the Sensor Bit Depth Mode parameter is set to Manual. If that parameter is set to Auto, the sensor bit depth is adjusted automatically depending on the pixel format used.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorBitDepth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslSensorBitDepthEnums>& BslSensorBitDepth;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Sets the sensor bit depth mode - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorBitDepthMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslSensorBitDepthModeEnums>& BslSensorBitDepthMode;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Sets the baud rate used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialBaudRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslSerialBaudRateEnums>& BslSerialBaudRate;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Sets the number of data bits used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialNumberOfDataBits" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslSerialNumberOfDataBitsEnums>& BslSerialNumberOfDataBits;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Sets the number of stop bits used in serial communication - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialNumberOfStopBits" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslSerialNumberOfStopBitsEnums>& BslSerialNumberOfStopBits;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Sets which kind of parity check is performed - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialParity" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslSerialParityEnums>& BslSerialParity;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Initiates a receiving transaction from the serial input buffer - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Initiates a receiving transaction from the serial input buffer. When the transaction has been completed, the Serial Transfer Length parameter indicates the number of valid data units received.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialReceive" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslSerialReceive;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Indicates the incoming break signal status - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialRxBreak" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslSerialRxBreak;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Resets the incoming break status - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialRxBreakReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslSerialRxBreakReset;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Indicates the overflow status of the receiving FIFO - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialRxFifoOverflow" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslSerialRxFifoOverflow;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Indicates the parity error status of the receiving FIFO - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialRxParityError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslSerialRxParityError;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Sets the source of the Rx serial input - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialRxSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslSerialRxSourceEnums>& BslSerialRxSource;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Indicates the stop bit error status of the receiving FIFO - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialRxStopBitError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslSerialRxStopBitError;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Buffer that holds Rx or Tx transfer data in the controller domain   - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Buffer that holds Rx or Tx transfer data in the controller domain. Data is displayed in hexadecimal notation. Transfer starts with the leftmost data.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialTransferBuffer" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IRegisterEx& BslSerialTransferBuffer;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Effective number of serial frames in a Rx or Tx data transfer - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Effective number of serial frames in a Rx or Tx data transfer. The maximum number of data frames is 16.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialTransferLength" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslSerialTransferLength;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Initiates a transmitting transaction to the serial output buffer - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Initiates a transmitting transaction to the serial output buffer. Set the correct transfer length before you issue a transmit command.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialTransmit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslSerialTransmit;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Signals a break to a receiver connected to the camera, or terminates the break - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress

            Signals a break to a receiver connected to the camera, or terminates the break. If this parameter is set to true, a serial break is signaled by setting the serial output to low level (space). If this parameter is set to false, the serial output is reset to high (mark).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialTxBreak" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslSerialTxBreak;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Indicates the empty status of the transmitting FIFO - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialTxFifoEmpty" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslSerialTxFifoEmpty;

        //@}


        //! \name Categories: SerialCommunicationControl
        //@{
        /*!
            \brief Indicates the overflow status of the transmitting FIFO - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSerialTxFifoOverflow" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& BslSerialTxFifoOverflow;

        //@}


        //! \name Categories: BslPGIControl and PGIControl
        //@{
        /*!
            \brief Sharpening value to be applied - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB

            Sharpening value to be applied. The higher the sharpness, the more distinct the image subject's contours will be. However, very high values may result in image information loss.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSharpnessEnhancement" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslSharpnessEnhancement;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Indicates the maximum temperature the camera reached during operation - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTemperatureMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& BslTemperatureMax;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Indicates the temperature state - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTemperatureStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslTemperatureStatusEnums>& BslTemperatureStatus;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Indicates how often the temperature state changed to Error - Applies to: ace 2 GigE, ace 2 USB and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTemperatureStatusErrorCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& BslTemperatureStatusErrorCount;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Indicates the speed mode of the USB port - Applies to: ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslUSBSpeedMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslUSBSpeedModeEnums>& BslUSBSpeedMode;

        //@}


        //! \name Categories: VignettingCorrection
        //@{
        /*!
            \brief Loads the vignetting correction data from the camera's file system - Applies to: boost CoaXPress

            Loads the vignetting correction data from the camera's file system and applies them to the camera.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslVignettingCorrectionLoad" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& BslVignettingCorrectionLoad;

        //@}


        //! \name Categories: VignettingCorrection
        //@{
        /*!
            \brief Enables the vignetting correction - Applies to: boost CoaXPress

            Enables the vignetting correction. This feature allows you to remove vignetting artifacts from your images. To do this, you first have to create vignetting correction data. For more information, see the Basler Product Documentation.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslVignettingCorrectionMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BslVignettingCorrectionModeEnums>& BslVignettingCorrectionMode;

        //@}


        //! \name Categories: CameraOperationControl
        //@{
        /*!
            \brief Sets the camera operation mode - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CameraOperationMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CameraOperationModeEnums>& CameraOperationMode;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Centers the image horizontally - Applies to: CameraLink, GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CenterX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& CenterX;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Centers the image vertically - Applies to: CameraLink, GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CenterY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& CenterY;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Sets which counter to retrieve chunk data from - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Expert

            Selecting Parameters: ChunkCounterValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkCounterSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ChunkCounterSelectorEnums>& ChunkCounterSelector;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Value of the selected chunk counter - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            Selected by: ChunkCounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkCounterValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkCounterValue;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Maximum possible pixel value in the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkDynamicRangeMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkDynamicRangeMax;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Minimum possible pixel value in the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkDynamicRangeMin" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkDynamicRangeMin;

        //@}


        //! \name Categories: ChunkDataControl and ChunkDataStreams
        //@{
        /*!
            \brief Includes the currently selected chunk in the payload data - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            Selected by: ChunkSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ChunkEnable;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Exposure time used to acquire the image - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkExposureTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ChunkExposureTime;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Unique identifier of the current frame - Applies to: ace 2 GigE and ace 2 USB

            Unique identifier of the current frame. The frame ID starts at 0 and keeps incrementing by 1 for each exposed image until the camera is powered off. The maximum value is 2^48.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkFrameID;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Frame Trigger counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkFrameTriggerCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkFrameTriggerCounter;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Frame Trigger Ignored counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkFrameTriggerIgnoredCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkFrameTriggerIgnoredCounter;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Frame counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkFramecounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkFramecounter;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Frames per Trigger counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkFramesPerTriggerCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkFramesPerTriggerCounter;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Gain used during image acquisition - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            Selected by: ChunkGainSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkGain" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ChunkGain;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Gain All value of the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkGainAll" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkGainAll;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Sets which gain channel to retrieve chunk data from - Applies to: ace USB


            Visibility: Expert

            Selecting Parameters: ChunkGain

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkGainSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ChunkGainSelectorEnums>& ChunkGainSelector;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief AOI height of the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkHeight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkHeight;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Number of bits per line used for the Input Status At Line Trigger parameter - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkInputStatusAtLineTriggerBitsPerLine" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkInputStatusAtLineTriggerBitsPerLine;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Index number used for the Input Status At Line Trigger parameter - Applies to: GigE

            Index number used for the Input Status At Line Trigger parameter. The index number can be used to get the state of the camera's input lines when a specific line was acquired. For example, if you want to know the state of the camera's input lines when line 30 was acquired, set the index to 30, then retrieve the value of Status Index parameter.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkInputStatusAtLineTriggerIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkInputStatusAtLineTriggerIndex;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value indicating the status of the camera's input lines when a specific line was acquired - Applies to: GigE

            Value indicating the status of the camera's input lines when a specific line was acquired. The information is stored in a 4-bit value (bit 0 = input line 1 state, bit 1 = input line 2 state etc.). For more information, see the Status Index parameter documentation.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkInputStatusAtLineTriggerValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkInputStatusAtLineTriggerValue;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Bit field that indicates the status of all of the camera's input and output lines when the image was acquired - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkLineStatusAll" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkLineStatusAll;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Line Trigger counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkLineTriggerCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkLineTriggerCounter;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Line Trigger End to End counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkLineTriggerEndToEndCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkLineTriggerEndToEndCounter;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Line Trigger Ignored counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkLineTriggerIgnoredCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkLineTriggerIgnoredCounter;

        //@}


        //! \name Categories: ChunkDataControl and ChunkDataStreams
        //@{
        /*!
            \brief Enables the chunk mode - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkModeActive" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ChunkModeActive;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief X offset of the AOI of the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkOffsetX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkOffsetX;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Y offset of the AOI of the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkOffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkOffsetY;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief CRC checksum of the acquired image - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB

            CRC checksum of the acquired image. The checksum is calculated using all of the image data and all of the appended chunks except for the checksum itself.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkPayloadCRC16" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkPayloadCRC16;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Indicates the pixel format of the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkPixelFormat" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ChunkPixelFormatEnums>& ChunkPixelFormat;

        //@}


        //! \name Categories: ChunkDataControl and ChunkDataStreams
        //@{
        /*!
            \brief Sets which chunk can be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB

            Sets which chunk can be enabled. The chunk can be enabled using the Chunk Enable parameter.

            Visibility: Beginner

            Selecting Parameters: ChunkEnable

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ChunkSelectorEnums>& ChunkSelector;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Sequence set index number related to the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkSequenceSetIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkSequenceSetIndex;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Index of the active sequencer set - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkSequencerSetActive" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkSequencerSetActive;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Shaft Encoder counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkShaftEncoderCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkShaftEncoderCounter;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Number of bytes of data between the beginning of one line in the acquired image and the beginning of the next line in the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkStride" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkStride;

        //@}


        //! \name Categories: ChunkData and ChunkDataControl
        //@{
        /*!
            \brief Value of the timestamp when the image was acquired - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkTimestamp;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Value of the Trigger Input counter when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkTriggerinputcounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkTriggerinputcounter;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Status of all of the camera's virtual input and output lines when the image was acquired - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkVirtLineStatusAll" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkVirtLineStatusAll;

        //@}


        //! \name Categories: ChunkData
        //@{
        /*!
            \brief Width of the AOI of the acquired image - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkWidth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ChunkWidth;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the configuration type - Applies to: CameraLink

            Sets the configuration type. The configuration type determines the amount of data that can be transmitted.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClConfiguration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ClConfigurationEnums>& ClConfiguration;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Delay between end of transmission and start of transmission of consecutive lines - Applies to: CameraLink

            Delay (in microseconds) between the end of transmission of one line and the start of transmission of the next line. This value will be adjusted automatically to the nearest multiple of the currently selected pixel clock. The line valid signal (LVAL) remains low while the delay is in force. 	The default value of the parameter is the minimum inter-line delay.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClInterLineDelayAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ClInterLineDelayAbs;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Delay between end of transmission and start of transmission of consecutive lines (raw value) - Applies to: CameraLink

            Delay between the end of transmission of one line and the start of transmission of the next line (raw value). This value will be adjusted automatically to the nearest multiple of the currently selected pixel clock. The line valid signal (LVAL) remains low while the delay is in force. 	The default value of the parameter is the minimum inter-line delay.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClInterLineDelayRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ClInterLineDelayRaw;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the pixel clock used in the communication with the frame grabber - Applies to: CameraLink

            Sets the pixel clock used in the communication with the frame grabber. The pixel clock speed determines the rate at which pixel data will be transmitted from the camera to the frame grabber.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClPixelClock" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ClPixelClockEnums>& ClPixelClock;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Pixel clock used in the communication with the frame grabber in Hz - Applies to: CameraLink


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClPixelClockAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ClPixelClockAbs;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the serial port baud rate - Applies to: CameraLink


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClSerialPortBaudRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ClSerialPortBaudRateEnums>& ClSerialPortBaudRate;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the tap geometry - Applies to: CameraLink

            Sets the tap geometry. The tap geometry uniquely describes the geometrical properties characterizing the different taps of a multi-tap camera.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClTapGeometry" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ClTapGeometryEnums>& ClTapGeometry;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the number of time slots - Applies to: CameraLink


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClTimeSlots" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ClTimeSlotsEnums>& ClTimeSlots;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Clears the last error   - Applies to: CameraLink, GigE and blaze

            Clears the last error. If a previous error exists, the previous error can still be retrieved.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClearLastError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& ClearLastError;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Enables color adjustment - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorAdjustmentEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ColorAdjustmentEnable;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Hue adjustment value to be applied to the currently selected color channel - Applies to: CameraLink, GigE and ace USB


            Visibility: Expert

            Selected by: ColorAdjustmentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorAdjustmentHue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ColorAdjustmentHue;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Hue adjustment value to be applied to the currently selected color channel (raw value) - Applies to: CameraLink and GigE


            Visibility: Expert

            Selected by: ColorAdjustmentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorAdjustmentHueRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorAdjustmentHueRaw;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Allows you to restore previous color adjustment settings - Applies to: CameraLink and GigE

            Allows you to restore the color adjustment settings that were in force before the settings were last changed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorAdjustmentReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& ColorAdjustmentReset;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Saturation adjustment value to be applied to the currently selected color channel - Applies to: CameraLink, GigE and ace USB

            Saturation adjustment value  to be applied to the currently selected color channel.

            Visibility: Expert

            Selected by: ColorAdjustmentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorAdjustmentSaturation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ColorAdjustmentSaturation;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Saturation adjustment value to be applied to the currently selected color channel (raw value) - Applies to: CameraLink and GigE


            Visibility: Expert

            Selected by: ColorAdjustmentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorAdjustmentSaturationRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorAdjustmentSaturationRaw;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Sets which color in your images will be adjusted - Applies to: CameraLink, GigE and ace USB


            Visibility: Expert

            Selecting Parameters: ColorAdjustmentHue, ColorAdjustmentHueRaw, ColorAdjustmentSaturation and ColorAdjustmentSaturationRaw

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorAdjustmentSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ColorAdjustmentSelectorEnums>& ColorAdjustmentSelector;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Enables color overexposure compensation - Applies to: CameraLink and GigE

            Enables color overexposure compensation.

            Visibility: Beginner

            Selected by: ColorOverexposureCompensationAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOIEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ColorOverexposureCompensationAOIEnable;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Sets the color overexposure compensation factor for the selected C O C  AOI - Applies to: CameraLink and GigE

            Sets the color overexposure compensation factor controlling the extent of compensation for the selected C.O.C. AOI.

            Visibility: Guru

            Selected by: ColorOverexposureCompensationAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOIFactor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ColorOverexposureCompensationAOIFactor;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Sets the raw value for the color overexposure compensation factor - Applies to: CameraLink and GigE

            Sets the raw value for the color overexposure compensation factor.

            Visibility: Guru

            Selected by: ColorOverexposureCompensationAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOIFactorRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorOverexposureCompensationAOIFactorRaw;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Sets the height for the selected C O C  AOI - Applies to: CameraLink and GigE

            Sets the height for the selected Color Overexposure Compensation AOI.

            Visibility: Guru

            Selected by: ColorOverexposureCompensationAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOIHeight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorOverexposureCompensationAOIHeight;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Sets the X offset for the selected C O C  AOI - Applies to: CameraLink and GigE

            Sets the horizontal offset for the selected Color Overexposure Compensation AOI.

            Visibility: Guru

            Selected by: ColorOverexposureCompensationAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOIOffsetX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorOverexposureCompensationAOIOffsetX;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Sets the Y offset for the selected C O C  AOI - Applies to: CameraLink and GigE

            Sets the vertical offset for the selected Color Overexposure Compensation AOI.

            Visibility: Guru

            Selected by: ColorOverexposureCompensationAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOIOffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorOverexposureCompensationAOIOffsetY;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Selcts the AOI for color overexposure compensation - Applies to: CameraLink and GigE

            Selcts the area of interest where color overexposure compensation will be performed. 

            Visibility: Guru

            Selecting Parameters: ColorOverexposureCompensationAOIEnable, ColorOverexposureCompensationAOIFactor, ColorOverexposureCompensationAOIFactorRaw, ColorOverexposureCompensationAOIHeight, ColorOverexposureCompensationAOIOffsetX, ColorOverexposureCompensationAOIOffsetY and ColorOverexposureCompensationAOIWidth

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOISelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ColorOverexposureCompensationAOISelectorEnums>& ColorOverexposureCompensationAOISelector;

        //@}


        //! \name Categories: ColorOverexposureCompensation
        //@{
        /*!
            \brief Sets the width for the selected C O C  AOI - Applies to: CameraLink and GigE

            Sets the width for the selected Color Overexposure Compensation AOI.

            Visibility: Guru

            Selected by: ColorOverexposureCompensationAOISelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorOverexposureCompensationAOIWidth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorOverexposureCompensationAOIWidth;

        //@}


        //! \name Categories: AnalogControl and ImageQualityControl
        //@{
        /*!
            \brief Sets the color space for image acquisitions - Applies to: ace USB

            Sets the color space for image acquisitions. Note that the gamma correction value also influences the perception of brightness in the resulting images.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorSpace" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ColorSpaceEnums>& ColorSpace;

        //@}


        //! \name Categories: ColorTransformationControl
        //@{
        /*!
            \brief Enables color transformation - Applies to: ace 2 GigE, ace 2 USB and boost CoaXPress


            Visibility: Expert

            Selected by: ColorTransformationSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorTransformationEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ColorTransformationEnable;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Extent to which the color matrix influences the color values - Applies to: CameraLink and GigE

            Extent to which the color matrix influences the color values. If set to 0, the matrix is effectively disabled.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorTransformationMatrixFactor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ColorTransformationMatrixFactor;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Extent to which the color matrix influences the color values (raw value) - Applies to: CameraLink and GigE

            Extent to which the color matrix influences the color values (raw value). If set to 0, the matrix is effectively disabled.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorTransformationMatrixFactorRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorTransformationMatrixFactorRaw;

        //@}


        //! \name Categories: ColorImprovementsControl, ColorTransformationControl and ImageQualityControl
        //@{
        /*!
            \brief Sets which type of color transformation will be performed - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress


            Visibility: Expert

            Selecting Parameters: ColorTransformationEnable, ColorTransformationValue, ColorTransformationValueSelector and LightSourceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorTransformationSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ColorTransformationSelectorEnums>& ColorTransformationSelector;

        //@}


        //! \name Categories: ColorImprovementsControl, ColorTransformationControl and ImageQualityControl
        //@{
        /*!
            \brief Transformation value for the selected element in the color transformation matrix - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress


            Visibility: Expert

            Selected by: ColorTransformationSelector and ColorTransformationValueSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorTransformationValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ColorTransformationValue;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Transformation value for the selected element in the color transformation matrix (raw value) - Applies to: CameraLink and GigE


            Visibility: Guru

            Selected by: ColorTransformationValueSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorTransformationValueRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ColorTransformationValueRaw;

        //@}


        //! \name Categories: ColorImprovementsControl, ColorTransformationControl and ImageQualityControl
        //@{
        /*!
            \brief Sets which element will be entered in the color transformation matrix - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress

            Sets which element will be entered in the color transformation matrix. Depending on the camera model, some elements in the color transformation matrix may be preset and can't be changed.

            Visibility: Expert

            Selected by: ColorTransformationSelector

            Selecting Parameters: ColorTransformationValue and ColorTransformationValueRaw

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ColorTransformationValueSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ColorTransformationValueSelectorEnums>& ColorTransformationValueSelector;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Controls if the selected component streaming is active - Applies to: blaze


            Visibility: Beginner

            Selected by: ComponentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ComponentEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ComponentEnable;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Selects a component to activate/deactivate its data streaming - Applies to: blaze


            Visibility: Beginner

            Selecting Parameters: ComponentEnable and PixelFormat

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ComponentSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ComponentSelectorEnums>& ComponentSelector;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Confidence threshold for pixels - Applies to: blaze

            Pixels have to exceed the confidence value specified here in order to be taken into account for the distance measurement. The threshold value is based on the gray values of the confidence map.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ConfidenceThreshold" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ConfidenceThreshold;

        //@}


        //! \name Categories: CounterAndTimerControl and CounterControl
        //@{
        /*!
            \brief Number of times a sequencer set is used before the Counter End event is generated - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterDuration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CounterDuration;

        //@}


        //! \name Categories: CounterControl
        //@{
        /*!
            \brief Sets the type of signal transition that the counter will count - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterEventActivation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterEventActivationEnums>& CounterEventActivation;

        //@}


        //! \name Categories: CounterAndTimerControl, CounterControl and TimerControls
        //@{
        /*!
            \brief Sets which event increases the currently selected counter - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterEventSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterEventSourceEnums>& CounterEventSource;

        //@}


        //! \name Categories: CounterAndTimerControl, CounterControl and TimerControls
        //@{
        /*!
            \brief Immediately resets the selected counter - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Immediately resets the selected counter. The counter starts counting again immediately after the reset.

            Visibility: Beginner

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& CounterReset;

        //@}


        //! \name Categories: CounterAndTimerControl and CounterControl
        //@{
        /*!
            \brief Sets which type of signal transition will reset the counter - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterResetActivation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterResetActivationEnums>& CounterResetActivation;

        //@}


        //! \name Categories: CounterAndTimerControl, CounterControl and TimerControls
        //@{
        /*!
            \brief Sets which source signal will reset the currently selected counter - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterResetSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterResetSourceEnums>& CounterResetSource;

        //@}


        //! \name Categories: CounterAndTimerControl, CounterControl and TimerControls
        //@{
        /*!
            \brief Sets which counter can be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Sets which counter can be configured. All changes to the counter settings will be applied to the selected counter.

            Visibility: Beginner

            Selecting Parameters: CounterDuration, CounterEventActivation, CounterEventSource, CounterReset, CounterResetActivation, CounterResetSource, CounterStatus, CounterTriggerActivation, CounterTriggerSource and CounterValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterSelectorEnums>& CounterSelector;

        //@}


        //! \name Categories: CounterControl
        //@{
        /*!
            \brief Returns the current status of the counter - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterStatusEnums>& CounterStatus;

        //@}


        //! \name Categories: CounterControl
        //@{
        /*!
            \brief Sets the type of signal transition that will start the counter - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterTriggerActivation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterTriggerActivationEnums>& CounterTriggerActivation;

        //@}


        //! \name Categories: CounterControl
        //@{
        /*!
            \brief Sets the signal used to start the selected counter - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Sets the signal used to start the selected counter. If you start a counter, it will not necessarily start counting. If and when the counter counts, depends on the Counter Event Source parameter value.

            Visibility: Expert

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterTriggerSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CounterTriggerSourceEnums>& CounterTriggerSource;

        //@}


        //! \name Categories: CounterControl
        //@{
        /*!
            \brief Current value of the counter - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            Selected by: CounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CounterValue;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Indicates whether the critical temperature has been reached - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CriticalTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& CriticalTemperature;

        //@}


        //! \name Categories: CriticalTemperatureEventData
        //@{
        /*!
            \brief Stream channel index of the Critical Temperature event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CriticalTemperatureEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CriticalTemperatureEventStreamChannelIndex;

        //@}


        //! \name Categories: CriticalTemperatureEventData
        //@{
        /*!
            \brief Timestamp of the Critical Temperature event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CriticalTemperatureEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CriticalTemperatureEventTimestamp;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets the CoaXPress physical connection to control - Applies to: boost CoaXPress


            Visibility: Expert

            Selecting Parameters: CxpConnectionTestErrorCount, CxpConnectionTestMode, CxpErrorCounterSelector and CxpSendReceiveSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpConnectionSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpConnectionSelector;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of test packet connection errors received by the device on the connection selected by the Connection Selector parameter - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpConnectionSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpConnectionTestErrorCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpConnectionTestErrorCount;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets the test mode for an individual physical connection of the device - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpConnectionSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpConnectionTestMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpConnectionTestModeEnums>& CxpConnectionTestMode;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of test packets received by the device on the connection selected by the Cxp Connection Selector parameter - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpSendReceiveSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpConnectionTestPacketCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpConnectionTestPacketCount;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Resets the selected CoaXPress error counter - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpErrorCounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCounterReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& CxpErrorCounterReset;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets which CoaXPress error counter to read or reset - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpConnectionSelector

            Selecting Parameters: CxpErrorCounterReset, CxpErrorCounterStatus and CxpErrorCounterValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCounterSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpErrorCounterSelectorEnums>& CxpErrorCounterSelector;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Indicates the current status of the selected CoaXPress error counter - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpErrorCounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCounterStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpErrorCounterStatusEnums>& CxpErrorCounterStatus;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Current value of the selected CoaXPress error counter - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpErrorCounterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCounterValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCounterValue;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets the link configuration - Applies to: boost CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkConfiguration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkConfigurationEnums>& CxpLinkConfiguration;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets the link configuration that allows the device to operate in its default mode - Applies to: boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkConfigurationPreferred" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkConfigurationPreferredEnums>& CxpLinkConfigurationPreferred;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Indicates the link configuration used by the device - Applies to: boost CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkConfigurationStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkConfigurationStatusEnums>& CxpLinkConfigurationStatus;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets whether the send or the receive features can be configured - Applies to: boost CoaXPress


            Visibility: Expert

            Selected by: CxpConnectionSelector

            Selecting Parameters: CxpConnectionTestPacketCount

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpSendReceiveSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpSendReceiveSelectorEnums>& CxpSendReceiveSelector;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Horizontal decimation factor - Applies to: CameraLink, GigE and ace USB

            Horizontal decimation factor. This specifies the extent of horizontal sub-sampling of the acquired frame, i.e., it defines how many pixel columns are left out of transmission. This has the net effect of reducing the horizontal resolution (width) of the image by the specified decimation factor. A value of 1 means that the camera performs no horizontal decimation.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DecimationHorizontal" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DecimationHorizontal;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Vertical decimation factor - Applies to: CameraLink, GigE and ace USB

            Vertical decimation factor. This specifies the extent of vertical sub-sampling of the acquired frame, i.e., it defines how many rows are left out of transmission. This has the net effect of reducing the vertical resolution (height) of the image by the specified decimation factor. A value of 1 means that the camera performs no vertical decimation.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DecimationVertical" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DecimationVertical;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Identifies outlier pixels and adjusts their intensity value - Applies to: dart BCON, dart USB and pulse USB

            Pixels that have a significantly higher or lower intensity value than the neighboring pixels are called outlier pixels. This feature identifies them and adjusts their intensity value.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DefectPixelCorrectionMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DefectPixelCorrectionModeEnums>& DefectPixelCorrectionMode;

        //@}


        //! \name Categories: PGIControl
        //@{
        /*!
            \brief Sets the demosaicing mode - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DemosaicingMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DemosaicingModeEnums>& DemosaicingMode;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief End of the three-dimensional ROI - Applies to: blaze

            The Minimum Depth and the Maximum Depth parameters together define the desired three-dimensional ROI. In the point cloud display, points outside the ROI will be ignored. When using the Mono16 or RGB8 pixel formats, points in front of the ROI receive the minimum distance value, while points beyond the ROI receive the maximum distance value.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DepthMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DepthMax;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Start of the three-dimensional ROI - Applies to: blaze

            The Minimum Depth and the Maximum Depth parameters together define the desired three-dimensional ROI. In the point cloud display, points outside the ROI will be ignored. When using the Mono16 or RGB8 pixel formats, points in front of the ROI receive the minimum distance value, while points beyond the ROI receive the maximum distance value.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DepthMin" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DepthMin;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Indicates the character set used by the strings of the device's bootstrap registers - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceCharacterSet" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceCharacterSetEnums>& DeviceCharacterSet;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Clock frequency used - Applies to: dart BCON


            Visibility: Expert

            Selected by: DeviceClockSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceClockFrequency" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& DeviceClockFrequency;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Sets the clock of the camera - Applies to: dart BCON

            Sets the clock of the camera. When a clock has been set, the clock frequency can be read using the Device Clock Frequency parameter.

            Visibility: Expert

            Selecting Parameters: DeviceClockFrequency

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceClockSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceClockSelectorEnums>& DeviceClockSelector;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Version of the color modifications applied to images - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceColorPipelineVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceColorPipelineVersion;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Indicates the number of event channels supported by the device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceEventChannelCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceEventChannelCount;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Identifier of the product family of the device - Applies to: ace 2 GigE, ace 2 USB, blaze, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFamilyName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceFamilyName;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Disables feature streaming on the device - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Disables feature streaming on the device. Feature streaming allows you to save camera settings outside of the device.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFeaturePersistenceEnd" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& DeviceFeaturePersistenceEnd;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Enables feature streaming on the device - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Enables feature streaming on the device. Feature streaming allows you to save camera settings outside of the device.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFeaturePersistenceStart" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& DeviceFeaturePersistenceStart;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Version of the camera's firmware - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFirmwareVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceFirmwareVersion;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Major version of the GenCP protocol supported by the device - Applies to: ace 2 USB and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceGenCPVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceGenCPVersionMajor;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Minor version of the GenCP protocol supported by the device - Applies to: ace 2 USB and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceGenCPVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceGenCPVersionMinor;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief ID of the camera - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceID;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Sets the behavior of the camera's status LED - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceIndicatorMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceIndicatorModeEnums>& DeviceIndicatorMode;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Returns the number of physical connection of the device used by a particular Link - Applies to: blaze


            Visibility: Beginner

            Selected by: DeviceLinkSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkConnectionCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceLinkConnectionCount;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Actual bandwidth the camera will use - Applies to: ace USB

            Actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data with the current camera settings.

            Visibility: Expert

            Selected by: DeviceLinkSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkCurrentThroughput" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceLinkCurrentThroughput;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Device link to be configured - Applies to: ace USB, blaze, dart USB and pulse USB


            Visibility: Beginner

            Selecting Parameters: DeviceLinkConnectionCount, DeviceLinkCurrentThroughput, DeviceLinkSpeed, DeviceLinkThroughputLimit and DeviceLinkThroughputLimitMode

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceLinkSelector;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Speed of transmission negotiated on the selected link - Applies to: ace USB, dart USB and pulse USB


            Visibility: Expert

            Selected by: DeviceLinkSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkSpeed" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceLinkSpeed;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Bandwidth limit for data transmission (in bytes per second) - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB


            Visibility: Beginner

            Selected by: DeviceLinkSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkThroughputLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceLinkThroughputLimit;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Enables/disables the device link throughput limit - Applies to: ace 2 GigE, ace 2 USB, ace USB, dart 2 USB, dart USB and pulse USB

            Enables/disables the device link throughput limit. If disabled, the bandwidth used is determined by the settings of various other parameters, e.g., exposure time or frame rate.

            Visibility: Beginner

            Selected by: DeviceLinkSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkThroughputLimitMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceLinkThroughputLimitModeEnums>& DeviceLinkThroughputLimitMode;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief First URL to the GenICam XML device description file of the selected manifest entry - Applies to: ace 2 GigE and boost CoaXPress


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestPrimaryURL" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceManifestPrimaryURL;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Major version number of the schema file of the selected manifest entry - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestSchemaMajorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceManifestSchemaMajorVersion;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Minor version number of the schema file of the selected manifest entry - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestSchemaMinorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceManifestSchemaMinorVersion;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Major version number of the GenICam XML file of the selected manifest entry - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestXMLMajorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceManifestXMLMajorVersion;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Minor version number of the GenICam XML file of the selected manifest entry - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestXMLMinorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceManifestXMLMinorVersion;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Subminor version number of the GenICam XML file of the selected manifest entry - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestXMLSubMinorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceManifestXMLSubMinorVersion;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Additional information from the vendor about the camera - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Endianness of the registers of the device.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManufacturerInfo" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceManufacturerInfo;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Name of the camera model - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceModelName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceModelName;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Endianness of the registers of the device - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceRegistersEndianness" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceRegistersEndiannessEnums>& DeviceRegistersEndianness;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Announces the end of feature streaming - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceRegistersStreamingEnd" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& DeviceRegistersStreamingEnd;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Prepares the camera for feature streaming - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceRegistersStreamingStart" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& DeviceRegistersStreamingStart;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Immediately resets and restarts the camera - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& DeviceReset;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Major version number of the SFNC specification that the camera is compatible with - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Major version number of the Standard Features Naming Convention (SFNC) specification that the camera is compatible with.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSFNCVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceSFNCVersionMajor;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Minor version number of the SFNC specification that the camera is compatible with - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Minor version number of the Standard Features Naming Convention (SFNC) specification that the camera is compatible with.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSFNCVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceSFNCVersionMinor;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Subminor version number of the SFNC specification that the camera is compatible with - Applies to: GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Subminor version number of the Standard Features Naming Convention (SFNC) specification that the camera is compatible with.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSFNCVersionSubMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceSFNCVersionSubMinor;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Indicates the scan type of the camera's sensor (area or line scan) - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceScanType" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceScanTypeEnums>& DeviceScanType;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Serial number of the camera - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSerialNumber" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceSerialNumber;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Indicates the number of streaming channels supported by the device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceStreamChannelCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceStreamChannelCount;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Indicates the type of the device's transport layer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLType" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceTLTypeEnums>& DeviceTLType;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Major version number of the device's transport layer - Applies to: ace 2 GigE, ace 2 USB, blaze, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceTLVersionMajor;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Minor version number of the device's transport layer - Applies to: ace 2 GigE, ace 2 USB, blaze, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceTLVersionMinor;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Subminor version number of the device's transport layer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionSubMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceTLVersionSubMinor;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Sets the tap geometry - Applies to: boost CoaXPress

            Sets the tap geometry. The tap geometry uniquely describes the geometrical properties characterizing the different taps of a multi-tap camera.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTapGeometry" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceTapGeometryEnums>& DeviceTapGeometry;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Temperature at the selected location in the camera (in degrees centigrade) - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress and dart 2 USB

            Temperature at the selected location in the camera (in degrees centigrade). The temperature is measured at the location specified by the Device Temperature Selector parameter.

            Visibility: Expert

            Selected by: DeviceTemperatureSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& DeviceTemperature;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Sets the location in the camera where the temperature will be measured - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress and dart 2 USB

            Sets the location in the camera where the temperature will be measured. The temperature can be retrieved using the Device Temperature parameter.

            Visibility: Expert

            Selecting Parameters: DeviceTemperature

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTemperatureSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceTemperatureSelectorEnums>& DeviceTemperatureSelector;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Returns the device type - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceType" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceTypeEnums>& DeviceType;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief User-settable ID of the camera - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceUserID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceUserID;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Name of the camera vendor - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceVendorName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceVendorName;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Version of the camera - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceVersion;

        //@}


        //! \name Categories: AnalogControl and AnalogControls
        //@{
        /*!
            \brief Digital shift to be applied - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress

            Digital shift allows you to multiply the pixel values in an image. This increases the brightness of the image. If the parameter is set to zero, digital shift is disabled.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DigitalShift" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DigitalShift;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Enables Burst Acquisition - Applies to: CameraLink and GigE

            Enables Burst Acquisition. If enabled, the maximum frame rate only depends on the sensor timing and the timing of the trigger sequence. The image transfer rate out of the camera has no influence on the frame rate.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EnableBurstAcquisition" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EnableBurstAcquisition;

        //@}


        //! \name Categories: EventActionLateData
        //@{
        /*!
            \brief Unique identifier of the Action Late event - Applies to: ace 2 GigE

            Unique identifier of the Action Late event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventActionLate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventActionLate;

        //@}


        //! \name Categories: EventActionLateData
        //@{
        /*!
            \brief Timestamp of the Action Late event - Applies to: ace 2 GigE

            Timestamp of the Action Late event. An Action Late event is raised when a scheduled action command with a timestamp in the past is received.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventActionLateTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventActionLateTimestamp;

        //@}


        //! \name Categories: EventCriticalTemperatureData
        //@{
        /*!
            \brief Unique identifier of the Critical Temperature event - Applies to: ace USB

            Unique identifier of the Critical Temperature event. Use this parameter to get notified when the event occurs.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCriticalTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCriticalTemperature;

        //@}


        //! \name Categories: EventCriticalTemperatureData
        //@{
        /*!
            \brief Timestamp of the Critical Temperature event - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCriticalTemperatureTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCriticalTemperatureTimestamp;

        //@}


        //! \name Categories: EventExposureEndData
        //@{
        /*!
            \brief Unique identifier of the Exposure End event - Applies to: ace 2 GigE, ace 2 USB and ace USB

            Unique identifier of the Exposure End event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventExposureEnd" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventExposureEnd;

        //@}


        //! \name Categories: EventExposureEndData
        //@{
        /*!
            \brief Frame ID of the Exposure End event - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventExposureEndFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventExposureEndFrameID;

        //@}


        //! \name Categories: EventExposureEndData
        //@{
        /*!
            \brief Timestamp of the Exposure End event - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventExposureEndTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventExposureEndTimestamp;

        //@}


        //! \name Categories: EventFrameBufferOverrunData
        //@{
        /*!
            \brief Unique identifier of the Frame Buffer Overrun event - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBufferOverrun" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBufferOverrun;

        //@}


        //! \name Categories: EventFrameBufferOverrunData
        //@{
        /*!
            \brief Timestamp of the Frame Buffer Overrun event - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBufferOverrunTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBufferOverrunTimestamp;

        //@}


        //! \name Categories: EventFrameBurstStartData
        //@{
        /*!
            \brief Unique identifier of the Frame Burst Start event - Applies to: ace USB

            Unique identifier of the Frame Burst Start event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStart" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStart;

        //@}


        //! \name Categories: EventFrameBurstStartData
        //@{
        /*!
            \brief Frame ID of the Frame Burst Start event - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStartFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStartFrameID;

        //@}


        //! \name Categories: EventFrameBurstStartOvertriggerData
        //@{
        /*!
            \brief Unique identifier of the Frame Burst Start Overtrigger event - Applies to: ace USB

            Unique identifier of the Frame Burst Start Overtrigger event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStartOvertrigger" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStartOvertrigger;

        //@}


        //! \name Categories: EventFrameBurstStartOvertriggerData
        //@{
        /*!
            \brief Frame ID of the Frame Burst Start Overtrigger event - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStartOvertriggerFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStartOvertriggerFrameID;

        //@}


        //! \name Categories: EventFrameBurstStartOvertriggerData
        //@{
        /*!
            \brief Timestamp of the Frame Burst Start Overtrigger event - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStartOvertriggerTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStartOvertriggerTimestamp;

        //@}


        //! \name Categories: EventFrameBurstStartData
        //@{
        /*!
            \brief Timestamp of the Frame Burst Start event - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStartTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStartTimestamp;

        //@}


        //! \name Categories: EventFrameBurstStartWaitData
        //@{
        /*!
            \brief Unique identifier of the Frame Burst Start Wait event - Applies to: ace USB

            Unique identifier of the Frame Burst Start Wait event. Use this parameter to get notified when the event occurs.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStartWait" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStartWait;

        //@}


        //! \name Categories: EventFrameBurstStartWaitData
        //@{
        /*!
            \brief Timestamp of the Frame Burst Start Wait event - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameBurstStartWaitTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameBurstStartWaitTimestamp;

        //@}


        //! \name Categories: EventFrameStartData
        //@{
        /*!
            \brief Unique identifier of the Frame Start event - Applies to: ace 2 GigE, ace 2 USB and ace USB

            Unique identifier of the Frame Start event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStart" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStart;

        //@}


        //! \name Categories: EventFrameStartData
        //@{
        /*!
            \brief Frame ID of the Frame Start event - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStartFrameID;

        //@}


        //! \name Categories: EventFrameStartOvertriggerData
        //@{
        /*!
            \brief Unique identifier of the Frame Start Overtrigger event - Applies to: ace USB

            Unique identifier of the Frame Start Overtrigger event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartOvertrigger" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStartOvertrigger;

        //@}


        //! \name Categories: EventFrameStartOvertriggerData
        //@{
        /*!
            \brief Frame ID of the Frame Start Overtrigger event - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartOvertriggerFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStartOvertriggerFrameID;

        //@}


        //! \name Categories: EventFrameStartOvertriggerData
        //@{
        /*!
            \brief Timestamp of the Frame Start Overtrigger event - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartOvertriggerTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStartOvertriggerTimestamp;

        //@}


        //! \name Categories: EventFrameStartData
        //@{
        /*!
            \brief Timestamp of the Frame Start event - Applies to: ace 2 GigE, ace 2 USB and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStartTimestamp;

        //@}


        //! \name Categories: EventFrameStartWaitData
        //@{
        /*!
            \brief Unique identifier of the Frame Start Wait event - Applies to: ace USB

            Unique identifier of the Frame Start Wait event. Use this parameter to get notified when the event occurs.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartWait" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStartWait;

        //@}


        //! \name Categories: EventFrameStartWaitData
        //@{
        /*!
            \brief Timestamp of the Frame Start Wait event - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartWaitTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameStartWaitTimestamp;

        //@}


        //! \name Categories: EventFrameTriggerMissedData
        //@{
        /*!
            \brief Unique identifier of the Frame Trigger Missed event - Applies to: ace 2 GigE and ace 2 USB

            Unique identifier of the Frame Trigger Missed event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTriggerMissed" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTriggerMissed;

        //@}


        //! \name Categories: EventFrameTriggerMissedData
        //@{
        /*!
            \brief Timestamp of the Frame Trigger Missed event - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTriggerMissedTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTriggerMissedTimestamp;

        //@}


        //! \name Categories: EventControl and EventsGeneration
        //@{
        /*!
            \brief Enables event notifications for the currently selected event - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB

            Enables event notifications for the currently selected event. The event can selected using the Event Selector parameter.

            Visibility: Beginner

            Selected by: EventSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventNotification" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<EventNotificationEnums>& EventNotification;

        //@}


        //! \name Categories: EventOverTemperatureData
        //@{
        /*!
            \brief Unique identifier of the Over Temperature event - Applies to: ace USB

            Unique identifier of the Over Temperature event. Use this parameter to get notified when the event occurs.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverTemperature;

        //@}


        //! \name Categories: EventOverTemperatureData
        //@{
        /*!
            \brief Timestamp of the Over Temperature event - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverTemperatureTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverTemperatureTimestamp;

        //@}


        //! \name Categories: EventOverrunData
        //@{
        /*!
            \brief Unique identifier of the Overrun event  Use this parameter to get notified when the event occurs - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverrun" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverrun;

        //@}


        //! \name Categories: EventOverrunEventData
        //@{
        /*!
            \brief Frame ID of the Event Overrun event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverrunEventFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverrunEventFrameID;

        //@}


        //! \name Categories: EventOverrunEventData
        //@{
        /*!
            \brief Stream channel index of the Event Overrun event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverrunEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverrunEventStreamChannelIndex;

        //@}


        //! \name Categories: EventOverrunEventData
        //@{
        /*!
            \brief Timestamp of the Event Overrun event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverrunEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverrunEventTimestamp;

        //@}


        //! \name Categories: EventOverrunData
        //@{
        /*!
            \brief Timestamp of the Event Overrun event - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverrunTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverrunTimestamp;

        //@}


        //! \name Categories: EventControl and EventsGeneration
        //@{
        /*!
            \brief Sets the event notification to be enabled - Applies to: GigE, ace 2 GigE, ace 2 USB and ace USB

            Sets the event notification to be enabled. The notification can be enabled using the Event Notification parameter.

            Visibility: Beginner

            Selecting Parameters: EventNotification

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<EventSelectorEnums>& EventSelector;

        //@}


        //! \name Categories: EventTemperatureStatusChangedData
        //@{
        /*!
            \brief Unique identifier of the Temperature Status Changed event - Applies to: ace 2 GigE and ace 2 USB

            Unique identifier of the Temperature Status Changed event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTemperatureStatusChanged" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTemperatureStatusChanged;

        //@}


        //! \name Categories: EventTemperatureStatusChangedData
        //@{
        /*!
            \brief New temperature status that applies after the Temperature Status Changed event was raised - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTemperatureStatusChangedStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<EventTemperatureStatusChangedStatusEnums>& EventTemperatureStatusChangedStatus;

        //@}


        //! \name Categories: EventTemperatureStatusChangedData
        //@{
        /*!
            \brief Timestamp of the Temperature Status Changed event - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTemperatureStatusChangedTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTemperatureStatusChangedTimestamp;

        //@}


        //! \name Categories: EventTestData
        //@{
        /*!
            \brief Unique identifier of the Test event - Applies to: ace 2 GigE and ace 2 USB

            Unique identifier of the Test event. Use this parameter to get notified when the event occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTest" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTest;

        //@}


        //! \name Categories: EventTestData
        //@{
        /*!
            \brief Timestamp of the test event - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTestTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTestTimestamp;

        //@}


        //! \name Categories: ExpertFeatureAccess
        //@{
        /*!
            \brief Key for making the selected expert feature available - Applies to: CameraLink, GigE and ace USB


            Visibility: Guru

            Selected by: ExpertFeatureAccessSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExpertFeatureAccessKey" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ExpertFeatureAccessKey;

        //@}


        //! \name Categories: ExpertFeatureAccess
        //@{
        /*!
            \brief Sets the expert feature to be made available - Applies to: CameraLink, GigE and ace USB

            Sets the expert feature to be made available. All changes will be applied to the selected feature.

            Visibility: Guru

            Selecting Parameters: ExpertFeatureAccessKey and ExpertFeatureEnable

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExpertFeatureAccessSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExpertFeatureAccessSelectorEnums>& ExpertFeatureAccessSelector;

        //@}


        //! \name Categories: ExpertFeatureAccess
        //@{
        /*!
            \brief Enables the currently selected expert feature - Applies to: CameraLink, GigE and ace USB


            Visibility: Guru

            Selected by: ExpertFeatureAccessSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExpertFeatureEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ExpertFeatureEnable;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the operation mode of the Exposure Auto auto function - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Sets the operation mode of the Exposure Auto auto function. The Exposure Auto auto function automatically adjusts the exposure time within set limits until a target brightness value has been reached.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureAuto" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExposureAutoEnums>& ExposureAuto;

        //@}


        //! \name Categories: ExposureEndEventData
        //@{
        /*!
            \brief Frame ID of the Exposure End event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureEndEventFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ExposureEndEventFrameID;

        //@}


        //! \name Categories: ExposureEndEventData
        //@{
        /*!
            \brief Stream channel index of the Exposure End event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureEndEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ExposureEndEventStreamChannelIndex;

        //@}


        //! \name Categories: ExposureEndEventData
        //@{
        /*!
            \brief Timestamp of the Exposure End event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureEndEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ExposureEndEventTimestamp;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the exposure mode - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExposureModeEnums>& ExposureMode;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Maximum overlap of the sensor exposure with sensor readout in Trigger Width exposure mode (in microseconds) - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureOverlapTimeMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ExposureOverlapTimeMax;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Maximum overlap of the sensor exposure with sensor readout in Trigger Width exposure mode (in microseconds) - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureOverlapTimeMaxAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ExposureOverlapTimeMaxAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Maximum overlap of the sensor exposure with sensor readout in Trigger Width exposure mode (raw value) - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureOverlapTimeMaxRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ExposureOverlapTimeMaxRaw;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the exposure overlap time mode - Applies to: GigE and ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureOverlapTimeMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExposureOverlapTimeModeEnums>& ExposureOverlapTimeMode;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureStartDelayAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ExposureStartDelayAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureStartDelayRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ExposureStartDelayRaw;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Exposure time of the camera in microseconds - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ExposureTime;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Exposure time of the camera in microseconds - Applies to: CamEmu, CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureTimeAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ExposureTimeAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Timebase (in microseconds) that the camera uses when the exposure time is specified using the Exposure Time (Raw) parameter - Applies to: CamEmu, CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureTimeBaseAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ExposureTimeBaseAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Enables the use of the exposure timebase - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureTimeBaseAbsEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ExposureTimeBaseAbsEnable;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the exposure time mode - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureTimeMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExposureTimeModeEnums>& ExposureTimeMode;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Exposure time of the camera (raw value) - Applies to: CamEmu, CameraLink and GigE

            Exposure time of the camera (raw value). The actual exposure time equals the current Exposure Time (Raw) value multiplied with the current Exposure Timebase value.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureTimeRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ExposureTimeRaw;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Enables the fast mode - Applies to: blaze

            The fast mode can be used to achieve the maximum frame rate, but this reduces image quality and measurement accuracy. 

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FastMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& FastMode;

        //@}


        //! \name Categories: FeatureSets
        //@{
        /*!
            \brief Sets the default GenICam XML file - Applies to: CameraLink and GigE

            Sets the default GenICam XML file. If the camera has multiple GenICam XML files, this parameter determines which of them is accessible to non-manifest-aware software.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FeatureSet" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FeatureSetEnums>& FeatureSet;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief Selects the mode to output the fields - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FieldOutputMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FieldOutputModeEnums>& FieldOutputMode;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Access buffer for file operations - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileAccessBuffer" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IRegisterEx& FileAccessBuffer;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Number of bytes read from the file into the file access buffer or written to the file from the file access buffer - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileOperationSelector and FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileAccessLength" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FileAccessLength;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Number of bytes after which FileAccessLength bytes are read from the file into the file access buffer or are written to the file from the file access buffer - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileOperationSelector and FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileAccessOffset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FileAccessOffset;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Sets the access mode in which a file is opened in the camera - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Beginner

            Selected by: FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOpenMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FileOpenModeEnums>& FileOpenMode;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Executes the operation selected by File Operation Selector parameter - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileOperationSelector and FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationExecute" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& FileOperationExecute;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief File operation result - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileOperationSelector and FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationResult" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FileOperationResult;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Sets the target operation for the currently selected file - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileSelector

            Selecting Parameters: FileAccessLength, FileAccessOffset, FileOperationExecute, FileOperationResult and FileOperationStatus

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FileOperationSelectorEnums>& FileOperationSelector;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Indicates the file operation execution status - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileOperationSelector and FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FileOperationStatusEnums>& FileOperationStatus;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Sets the target file in the camera - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selecting Parameters: FileAccessBuffer, FileAccessLength, FileAccessOffset, FileOpenMode, FileOperationExecute, FileOperationResult, FileOperationSelector, FileOperationStatus and FileSize

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FileSelectorEnums>& FileSelector;

        //@}


        //! \name Categories: FileAccessControl
        //@{
        /*!
            \brief Size of the currently selected file in bytes - Applies to: CameraLink, GigE and ace USB

            Basler advises against using this parameter. Use the appropriate feature for file access operations instead.

            Visibility: Guru

            Selected by: FileSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FileSize;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Enables the spatial noise filter - Applies to: blaze

            The spatial noise filter uses the values of neighboring pixels to filter out noise in an image. It is based on the raw data of the image.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FilterSpatial" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& FilterSpatial;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Strength of the temporal filter - Applies to: blaze

            Strength of the temporal filter. The higher the value, the further back the memory of the filter reaches. High values can cause motion artifacts, while low values reduce the efficacy of the filter.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FilterStrength" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FilterStrength;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Enables the temporal noise filter - Applies to: blaze

            The temporal noise filter uses the values of the same pixel at different points in time to filter out noise in an image. It is based on the depth data of the image.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FilterTemporal" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& FilterTemporal;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Marks the next buffer as failed - Applies to: CamEmu

            Marks the next buffer as a failed buffer.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ForceFailedBuffer" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& ForceFailedBuffer;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Number of failed buffers to generate - Applies to: CamEmu


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ForceFailedBufferCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ForceFailedBufferCount;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Total time required for exposing and reading out all subframes from the sensor - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameDuration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameDuration;

        //@}


        //! \name Categories: FrameStartEventData
        //@{
        /*!
            \brief Stream channel index of the Frame Start event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameStartEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameStartEventStreamChannelIndex;

        //@}


        //! \name Categories: FrameStartEventData
        //@{
        /*!
            \brief Timestamp of the Frame Start event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameStartEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameStartEventTimestamp;

        //@}


        //! \name Categories: FrameStartOvertriggerEventData
        //@{
        /*!
            \brief Stream channel index of the Frame Start Overtrigger event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameStartOvertriggerEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameStartOvertriggerEventStreamChannelIndex;

        //@}


        //! \name Categories: FrameStartOvertriggerEventData
        //@{
        /*!
            \brief Timestamp of the Frame Start Overtrigger event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameStartOvertriggerEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameStartOvertriggerEventTimestamp;

        //@}


        //! \name Categories: FrameStartWaitEventData
        //@{
        /*!
            \brief Stream channel index of the Frame Start Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameStartWaitEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameStartWaitEventStreamChannelIndex;

        //@}


        //! \name Categories: FrameStartWaitEventData
        //@{
        /*!
            \brief Timestamp of the Frame Start Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameStartWaitEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameStartWaitEventTimestamp;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Frame timeout in microseconds - Applies to: CameraLink and GigE

            Frame timeout in microseconds. If the timeout expires before a frame acquisition is complete, a partial frame will be delivered.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameTimeoutAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& FrameTimeoutAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Enables the frame timeout - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameTimeoutEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& FrameTimeoutEnable;

        //@}


        //! \name Categories: FrameTimeoutEventData
        //@{
        /*!
            \brief Stream channel index of the Frame Timeout event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameTimeoutEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameTimeoutEventStreamChannelIndex;

        //@}


        //! \name Categories: FrameTimeoutEventData
        //@{
        /*!
            \brief Timestamp of the Frame Timeout event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameTimeoutEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameTimeoutEventTimestamp;

        //@}


        //! \name Categories: FrameWaitEventData
        //@{
        /*!
            \brief Stream channel index of the Frame Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameWaitEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameWaitEventStreamChannelIndex;

        //@}


        //! \name Categories: FrameWaitEventData
        //@{
        /*!
            \brief Timestamp of the Frame Wait event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameWaitEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameWaitEventTimestamp;

        //@}


        //! \name Categories: FrequencyConverter
        //@{
        /*!
            \brief Sets the input source - Applies to: CameraLink and GigE

            Sets the input source for the frequency converter module.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrequencyConverterInputSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FrequencyConverterInputSourceEnums>& FrequencyConverterInputSource;

        //@}


        //! \name Categories: FrequencyConverter
        //@{
        /*!
            \brief Multiplication factor to be applied to the input signal frequency - Applies to: CameraLink and GigE

            Multiplication factor to be applied to the input signal frequency. The multiplication factor allows the generation of signals at higher frequencies.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrequencyConverterMultiplier" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrequencyConverterMultiplier;

        //@}


        //! \name Categories: FrequencyConverter
        //@{
        /*!
            \brief Post-divider value to decrease input signal frequency - Applies to: CameraLink and GigE

            Post-divider value to decrease input signal frequency. Determines the frequency with which input signals received from the multiplier sub-module are passed on.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrequencyConverterPostDivider" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrequencyConverterPostDivider;

        //@}


        //! \name Categories: FrequencyConverter
        //@{
        /*!
            \brief Pre-divider value to decrease signal frequency - Applies to: CameraLink and GigE

            Pre-divider value to decrease signal frequency. Determines the frequency with which input signals are passed to the multiplier sub-module.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrequencyConverterPreDivider" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrequencyConverterPreDivider;

        //@}


        //! \name Categories: FrequencyConverter
        //@{
        /*!
            \brief Enables overtriggering protection - Applies to: CameraLink and GigE

            Enables overtriggering protection. This ensures that the multiplier sub-module doesn't generate too many signals within a certain amount of time.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrequencyConverterPreventOvertrigger" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& FrequencyConverterPreventOvertrigger;

        //@}


        //! \name Categories: FrequencyConverter
        //@{
        /*!
            \brief Sets the signal transition relationships between received and generated signals - Applies to: CameraLink and GigE

            Sets the signal transition relationships between the signals received from the pre-divider sub-module and the signals generated by the multiplier sub-module.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrequencyConverterSignalAlignment" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FrequencyConverterSignalAlignmentEnums>& FrequencyConverterSignalAlignment;

        //@}


        //! \name Categories: AnalogControl
        //@{
        /*!
            \brief Value of the currently selected gain in dB - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: GainSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Gain" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Gain;

        //@}


        //! \name Categories: AnalogControls
        //@{
        /*!
            \brief This is a float value that sets the selected gain control in dB - Applies to: CameraLink and GigE

            Sets the 'absolute' value of the selected gain control. The 'absolute' value is a float value that sets the selected gain control in dB.

            Visibility: Beginner

            Selected by: GainSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GainAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& GainAbs;

        //@}


        //! \name Categories: AnalogControl and AnalogControls
        //@{
        /*!
            \brief Sets the operation mode of the Gain Auto auto function - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Sets the operation mode of the Gain Auto auto function. The Gain Auto auto function automatically adjusts the gain within set limits until a target brightness value has been reached.

            Visibility: Beginner

            Selected by: GainSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GainAuto" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GainAutoEnums>& GainAuto;

        //@}


        //! \name Categories: AnalogControls
        //@{
        /*!
            \brief Value of the currently selected gain (raw value) - Applies to: CamEmu, CameraLink and GigE


            Visibility: Beginner

            Selected by: GainSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GainRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GainRaw;

        //@}


        //! \name Categories: AnalogControl and AnalogControls
        //@{
        /*!
            \brief Sets the gain type to be adjusted - Applies to: CameraLink, GigE, ace USB, dart BCON, dart USB and pulse USB

            Sets the gain type to be adjusted. All changes to the Gain parameter will be applied to the selected gain type.

            Visibility: Beginner

            Selecting Parameters: AutoGainLowerLimit, AutoGainUpperLimit, Gain, GainAbs, GainAuto and GainRaw

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GainSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GainSelectorEnums>& GainSelector;

        //@}


        //! \name Categories: AnalogControl and AnalogControls
        //@{
        /*!
            \brief Gamma correction to be applied - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Gamma correction to be applied. Gamma correction allows you to optimize the brightness of acquired images for display on a monitor.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Gamma" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Gamma;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Enables gamma correction on the intensity image - Applies to: blaze

            A nonlinear operation to lighten the dark regions of the image.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GammaCorrection" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GammaCorrection;

        //@}


        //! \name Categories: AnalogControls
        //@{
        /*!
            \brief Enables gamma correction - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GammaEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GammaEnable;

        //@}


        //! \name Categories: AnalogControls
        //@{
        /*!
            \brief Sets the type of gamma to be applied - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GammaSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GammaSelectorEnums>& GammaSelector;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Controls the device's streaming format - Applies to: blaze


            Visibility: Invisible

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GenDCStreamingMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GenDCStreamingModeEnums>& GenDCStreamingMode;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Returns whether the current device data streaming format is GenDC - Applies to: blaze

            Returns whether the current device data streaming format is GenDC. This value is conditioned by the GenDCStreamingMode.

            Visibility: Invisible

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GenDCStreamingStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GenDCStreamingStatusEnums>& GenDCStreamingStatus;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the control channel privilege - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCCP" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GevCCPEnums>& GevCCP;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Current default gateway of the selected network interface - Applies to: GigE and blaze


            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCurrentDefaultGateway" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevCurrentDefaultGateway;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Current IP address of the selected network interface - Applies to: GigE and blaze


            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCurrentIPAddress" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevCurrentIPAddress;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Current IP configuration of the selected network interface - Applies to: GigE

            Current IP configuration of the selected network interface, e.g., fixed IP, DHCP, or auto IP.

            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCurrentIPConfiguration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevCurrentIPConfiguration;

        //@}


        //! \name Categories: GigEVision
        //@{
        /*!
            \brief Controls whether the DHCP IP configuration scheme is activated on the given logical link - Applies to: blaze


            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCurrentIPConfigurationDHCP" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevCurrentIPConfigurationDHCP;

        //@}


        //! \name Categories: GigEVision
        //@{
        /*!
            \brief Controls whether the Link Local Address IP configuration scheme is activated on the given logical link - Applies to: blaze


            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCurrentIPConfigurationLLA" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevCurrentIPConfigurationLLA;

        //@}


        //! \name Categories: GigEVision
        //@{
        /*!
            \brief Controls whether the PersistentIP configuration scheme is activated on the given logical link - Applies to: blaze


            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCurrentIPConfigurationPersistentIP" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevCurrentIPConfigurationPersistentIP;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Current subnet mask of the selected network interface - Applies to: GigE and blaze


            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevCurrentSubnetMask" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevCurrentSubnetMask;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Character set used by all strings of the bootstrap registers - Applies to: GigE

            Character set used by all strings of the bootstrap registers (1 = UTF8).

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceModeCharacterSet" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceModeCharacterSet;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether the bootstrap register is in big-endian format - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceModeIsBigEndian" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevDeviceModeIsBigEndian;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief First URL reference to the GenICam XML file   - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevFirstURL" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& GevFirstURL;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the Extended ID mode for GVSP - Applies to: GigE

            Sets the Extended ID mode for GVSP (64-bit block ID, 32-bit packet ID). This bit can't be reset if the stream channels do not support the standard ID mode.

            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevGVSPExtendedIDMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GevGVSPExtendedIDModeEnums>& GevGVSPExtendedIDMode;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Heartbeat timeout in milliseconds - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevHeartbeatTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevHeartbeatTimeout;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Enables the IEEE 1588 V2 Precision Time Protocol for the timestamp register - Applies to: GigE

            Enables the IEEE 1588 V2 Precision Time Protocol for the timestamp register. Only available if the IEEE1588_support bit of the GVCP Capability register is set. When PTP is enabled, the Timestamp Control register can't be used to reset the timestamp. When PTP is enabled or disabled, the value of Timestamp Tick Frequency and Timestamp Value registers may change to reflect the new time domain.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevIEEE1588" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevIEEE1588;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Latched IEEE 1588 clock ID of the camera - Applies to: GigE

            Latched IEEE 1588 clock ID of the camera. (The clock ID must first be latched using the IEEE 1588 Latch command.) The clock ID is an array of eight octets which is displayed as a hexadecimal number. Leading zeros are omitted.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevIEEE1588ClockId" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevIEEE1588ClockId;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Latches the current IEEE 1588-related values of the camera - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevIEEE1588DataSetLatch" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& GevIEEE1588DataSetLatch;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Latched offset from the IEEE 1588 master clock in nanoseconds   - Applies to: GigE

            Latched offset from the IEEE 1588 master clock in nanoseconds. (The offset must first be latched using the IEEE 1588 Latch command.)

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevIEEE1588OffsetFromMaster" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevIEEE1588OffsetFromMaster;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Latched IEEE 1588 parent clock ID of the camera - Applies to: GigE

            Latched IEEE 1588 parent clock ID of the camera. (The parent clock ID must first be latched using the IEEE 1588 Latch command.) The parent clock ID is the clock ID of the current master clock. A clock ID is an array of eight octets which is displayed as a hexadecimal number. Leading zeros are omitted.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevIEEE1588ParentClockId" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevIEEE1588ParentClockId;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates the state of the IEEE 1588 clock - Applies to: GigE

            Indicates the state of the IEEE 1588 clock. Values of this field must match the IEEE 1588 PTP port state enumeration (INITIALIZING, FAULTY, DISABLED, LISTENING, PRE_MASTER, MASTER, PASSIVE, UNCALIBRATED, SLAVE).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevIEEE1588Status" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GevIEEE1588StatusEnums>& GevIEEE1588Status;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates the latched state of the IEEE 1588 clock - Applies to: GigE

            Indicates the latched state of the IEEE 1588 clock. (The state must first be latched using the IEEE 1588 Latch command.) The state is indicated by values 1 to 9, corresponding to the states INITIALIZING, FAULTY, DISABLED, LISTENING, PRE_MASTER, MASTER, PASSIVE, UNCALIBRATED, and SLAVE.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevIEEE1588StatusLatched" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GevIEEE1588StatusLatchedEnums>& GevIEEE1588StatusLatched;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the physical network interface to be configured - Applies to: GigE

            Sets the physical network interface to be configured. All changes to the network interface settings will be applied to the selected interface.

            Visibility: Guru

            Selecting Parameters: GevCurrentDefaultGateway, GevCurrentIPAddress, GevCurrentIPConfiguration, GevCurrentSubnetMask, GevLinkCrossover, GevLinkFullDuplex, GevLinkMaster, GevLinkSpeed, GevMACAddress, GevPersistentDefaultGateway, GevPersistentIPAddress, GevPersistentSubnetMask, GevSupportedIPConfigurationDHCP, GevSupportedIPConfigurationLLA, GevSupportedIPConfigurationPersistentIP and GevSupportedOptionalLegacy16BitBlockID

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevInterfaceSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GevInterfaceSelectorEnums>& GevInterfaceSelector;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates the state of medium-dependent interface crossover (MDIX) for the selected network interface - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevLinkCrossover" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevLinkCrossover;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether the selected network interface operates in full-duplex mode - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevLinkFullDuplex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevLinkFullDuplex;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether the selected network interface is the clock master - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevLinkMaster" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevLinkMaster;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Connection speed in Mbps of the selected network interface - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevLinkSpeed" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevLinkSpeed;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief MAC address of the selected network interface - Applies to: GigE and blaze


            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevMACAddress" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevMACAddress;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Number of message channels supported by the camera - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevMessageChannelCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevMessageChannelCount;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Number of network interfaces of the camera - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevNumberOfInterfaces" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevNumberOfInterfaces;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief  Applies to: GigE

            This is a read only element. Maximum number of elements in RX event message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPTPDiagnosticsQueueRxEvntMaxNumElements" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPTPDiagnosticsQueueRxEvntMaxNumElements;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief  Applies to: GigE

            This is a read only element. Number of push failures in RX event message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPTPDiagnosticsQueueRxEvntPushNumFailure" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPTPDiagnosticsQueueRxEvntPushNumFailure;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief  Applies to: GigE

            This is a read only element. Maximum number of elements in RX general message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPTPDiagnosticsQueueRxGnrlMaxNumElements" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPTPDiagnosticsQueueRxGnrlMaxNumElements;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief  Applies to: GigE

            This is a read only element. Number of push failures in RX general message queue. (The value must first be latched using the IEEE 1588 Latch command.)

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPTPDiagnosticsQueueRxGnrlPushNumFailure" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPTPDiagnosticsQueueRxGnrlPushNumFailure;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief  Applies to: GigE

            This is a read only element. Number of send failures. (The value must first be latched using the IEEE 1588 Latch command.)

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPTPDiagnosticsQueueSendNumFailure" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPTPDiagnosticsQueueSendNumFailure;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Fixed default gateway of the selected network interface - Applies to: GigE and blaze

            Fixed default gateway of the selected network interface (if fixed IP addressing is supported by the camera and enabled).

            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPersistentDefaultGateway" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPersistentDefaultGateway;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Fixed IP address of the selected network interface - Applies to: GigE and blaze

            Fixed IP address of the selected network interface (if fixed IP addressing is supported by the camera and enabled).

            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPersistentIPAddress" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPersistentIPAddress;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Fixed subnet mask of the selected network interface - Applies to: GigE and blaze

            Fixed subnet mask of the selected network interface (if fixed IP addressing is supported by the camera and enabled).

            Visibility: Beginner

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevPersistentSubnetMask" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevPersistentSubnetMask;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Base bandwidth in bytes per second that will be used by the camera to transmit image and chunk feature data and to handle resends and control data transmissions - Applies to: GigE


            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCBWA" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCBWA;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Percentage of the Ethernet bandwidth assigned to the camera to be held in reserve - Applies to: GigE and ace 2 GigE

            Percentage of the Ethernet bandwidth assigned to the camera to be held in reserve for packet resends and for the transmission of control data between the camera and the host computer. The setting is expressed as a percentage of the Bandwidth Assigned parameter. For example, if the Bandwidth Assigned parameter indicates that 30 MBytes/s have been assigned to the camera and the Bandwidth Reserve parameter is set to 5 %, the bandwidth reserve will be 1.5 MBytes/s.

            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCBWR" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCBWR;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Multiplier for the Bandwidth Reserve parameter   - Applies to: GigE and ace 2 GigE

            Multiplier for the Bandwidth Reserve parameter. The multiplier is used to establish an extra pool of reserved bandwidth that can be used if an unusually large burst of packet resends is needed.

            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCBWRA" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCBWRA;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Destination address of the selected stream channel - Applies to: GigE

            Destination address of the selected stream channel. The destination can be a unicast or a multicast address.

            Visibility: Guru

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCDA" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCDA;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data - Applies to: GigE

            Actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data with the current settings for AOI, chunk features, and pixel format.

            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCDCT" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCDCT;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Maximum amount of data (in bytes per second) that the camera can generate - Applies to: GigE

            Maximum amount of data (in bytes per second) that the camera can generate with its current settings under ideal conditions, i.e., unlimited bandwidth and no packet resends.

            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCDMT" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCDMT;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Maximum amount of time (in ticks) that the next frame transmission could be delayed due to a burst of resends   - Applies to: GigE

            Maximum amount of time (in ticks) that the next frame transmission could be delayed due to a burst of resends. If the Bandwidth Reserve Accumulation parameter is set to a high value, the camera can experience periods where there is a large burst of data resends. This burst of resends will delay the start of transmission of the next acquired image. 

            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCFJM" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCFJM;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Frame transmission delay on the selected stream channel - Applies to: GigE and ace 2 GigE

            Frame transmission delay on the selected stream channel (in ticks). This value sets a delay before transmitting the acquired image.

            Visibility: Expert

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCFTD" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCFTD;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Delay between the transmission of each packet on the selected stream channel - Applies to: GigE and ace 2 GigE

            Delay between the transmission of each packet on the selected stream channel. The delay is measured in ticks.

            Visibility: Beginner

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCPD" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCPD;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Destination port of the selected stream channel - Applies to: GigE


            Visibility: Guru

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCPHostPort" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCPHostPort;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Index of the network interface to be used - Applies to: GigE


            Visibility: Guru

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCPInterfaceIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCPInterfaceIndex;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates the endianness of multi-byte pixel data for this stream - Applies to: GigE

            Indicates the endianness of multi-byte pixel data for this stream. True equals big-endian.

            Visibility: Guru

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCPSBigEndian" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSCPSBigEndian;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Disables IP fragmentation of packets on the stream channel - Applies to: GigE

            Disables IP fragmentation of packets on the stream channel. This bit is copied into the 'do not fragment' bit of the IP header of each stream packet.

            Visibility: Guru

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCPSDoNotFragment" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSCPSDoNotFragment;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sends a GigE Vision streaming test packet - Applies to: GigE

            Sends a GigE Vision streaming test packet. If this bit is set and the stream channel is a transmitter, the transmitter will send one test packet of the size specified by the Packet Size parameter. The 'do not fragment' bit of the IP header must be set for this test packet (see the SCPS Do Not Fragment parameter documentation).

            Visibility: Guru

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCPSFireTestPacket" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& GevSCPSFireTestPacket;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Packet size in bytes on the selected stream channel  Excludes data leader and data trailer - Applies to: GigE, ace 2 GigE and blaze

            Packet size in bytes on the selected stream channel. Excludes data leader and data trailer. (The last packet may be smaller because the packet size is not necessarily a multiple of the block size of the stream channel.)

            Visibility: Beginner

            Selected by: GevStreamChannelSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSCPSPacketSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevSCPSPacketSize;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Second URL reference to the GenICam XML file   - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSecondURL" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& GevSecondURL;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Number of stream channels supported by the camera - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevStreamChannelCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevStreamChannelCount;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Sets the stream channel to be configured - Applies to: GigE

            Sets the stream channels to be configured. All changes to the stream channel settings will be applied to the selected stream channel.

            Visibility: Guru

            Selecting Parameters: GevGVSPExtendedIDMode, GevSCBWA, GevSCBWR, GevSCBWRA, GevSCDA, GevSCDCT, GevSCDMT, GevSCFJM, GevSCFTD, GevSCPD, GevSCPHostPort, GevSCPInterfaceIndex, GevSCPSBigEndian, GevSCPSDoNotFragment, GevSCPSFireTestPacket and GevSCPSPacketSize

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevStreamChannelSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<GevStreamChannelSelectorEnums>& GevStreamChannelSelector;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether the IEEE 1588 V2 Precision Time Protocol (PTP) is supported - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedIEEE1588" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedIEEE1588;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether the selected network interface supports DHCP IP addressing - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedIPConfigurationDHCP" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedIPConfigurationDHCP;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether the selected network interface supports auto IP addressing (also known as LLA) - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedIPConfigurationLLA" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedIPConfigurationLLA;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether the selected network interface supports fixed IP addressing (also known as persistent IP addressing) - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedIPConfigurationPersistentIP" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedIPConfigurationPersistentIP;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether multiple operations in a single message are supported - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedOptionalCommandsConcatenation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedOptionalCommandsConcatenation;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether EVENT_CMD and EVENT_ACK are supported - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedOptionalCommandsEVENT" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedOptionalCommandsEVENT;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether EVENTDATA_CMD and EVENTDATA_ACK are supported - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedOptionalCommandsEVENTDATA" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedOptionalCommandsEVENTDATA;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether PACKETRESEND_CMD is supported - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedOptionalCommandsPACKETRESEND" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedOptionalCommandsPACKETRESEND;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether WRITEMEM_CMD and WRITEMEM_ACK are supported - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedOptionalCommandsWRITEMEM" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedOptionalCommandsWRITEMEM;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Indicates whether this GVSP transmitter or receiver can support a 16-bit block ID - Applies to: GigE


            Visibility: Guru

            Selected by: GevInterfaceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevSupportedOptionalLegacy16BitBlockID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& GevSupportedOptionalLegacy16BitBlockID;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Latches the current timestamp value of the camera - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevTimestampControlLatch" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& GevTimestampControlLatch;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Resets the timestamp control latch - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevTimestampControlLatchReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& GevTimestampControlLatchReset;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Resets the timestamp value of the camera - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevTimestampControlReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& GevTimestampControlReset;

        //@}


        //! \name Categories: GigEVision and TransportLayer
        //@{
        /*!
            \brief Number of timestamp clock ticks in 1 second - Applies to: GigE, ace 2 GigE and blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevTimestampTickFrequency" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevTimestampTickFrequency;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Latched value of the timestamp - Applies to: GigE

            Latched value of the timestamp. (The timestamp must first be latched using the Timestamp Control Latch command.)

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevTimestampValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevTimestampValue;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Major version number of the GigE Vision specification supported by this camera - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevVersionMajor;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Minor version number of the GigE Vision specification supported by this camera - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevVersionMinor;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Gray value adjustment damping factor to be applied - Applies to: CameraLink and GigE

            Gray value adjustment damping factor to be applied. This controls the speed with which pixel gray values are changed when Exposure Auto, Gain Auto, or both are enabled. This can be useful, for example, when objects move into the camera's field of view and the light conditions are changing gradually due to the moving objects.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GrayValueAdjustmentDampingAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& GrayValueAdjustmentDampingAbs;

        //@}


        //! \name Categories: AutoFunctions
        //@{
        /*!
            \brief Gray value adjustment damping factor (raw value) to be applied - Applies to: CameraLink and GigE

            Gray value adjustment damping factor (raw value) to be applied. This controls the speed with which pixel gray values are changed when Exposure Auto, Gain Auto, or both are enabled. This can be useful, for example, when objects move into the camera's field of view and the light conditions are changing gradually due to the moving objects.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GrayValueAdjustmentDampingRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GrayValueAdjustmentDampingRaw;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Height of the camera's region of interest (area of interest) in pixels - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Height of the camera's region of interest (area of interest) in pixels. Depending on the camera model, the parameter can be set in different increments.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Height" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Height;

        //@}


        //! \name Categories: AOI, DeviceInformation and ImageFormatControl
        //@{
        /*!
            \brief Maximum height of the region of interest (area of interest) in pixels - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Maximum height of the region of interest (area of interest) in pixels. The value takes into account any features that may limit the maximum height, e.g., binning.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=HeightMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& HeightMax;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Stream ID of the first image stream - Applies to: boost CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Image1StreamID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Image1StreamID;

        //@}


        //! \name Categories: ImageCompression
        //@{
        /*!
            \brief Sets the compression mode of the camera - Applies to: ace 2 GigE and ace 2 USB

            Sets the image compression mode of the camera. The available image compression modes depend on the selected pixel format.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageCompressionMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageCompressionModeEnums>& ImageCompressionMode;

        //@}


        //! \name Categories: ImageCompression
        //@{
        /*!
            \brief Configures the selected compression mechanism - Applies to: ace 2 GigE and ace 2 USB

            Configures the selected compression mechanism. The available options depend on the selected pixel format and the image compression mode.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageCompressionRateOption" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageCompressionRateOptionEnums>& ImageCompressionRateOption;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief Enables loading files from disk for image acquisition - Applies to: CamEmu


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageFileMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageFileModeEnums>& ImageFileMode;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief Enter the name of an image filename or a path to a directory containing image files - Applies to: CamEmu

            Enter the name of an image filename in a format supported by pylon or the path to a directory containing image files.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageFilename" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& ImageFilename;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Sets the method for calculating the intensity data - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=IntensityCalculation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<IntensityCalculationEnums>& IntensityCalculation;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Selects the Interlaced Integration Mode - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=InterlacedIntegrationMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<InterlacedIntegrationModeEnums>& InterlacedIntegrationMode;

        //@}


        //! \name Categories: LUTControl and LUTControls
        //@{
        /*!
            \brief Enables the selected lookup table (LUT) - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress


            Visibility: Beginner

            Selected by: LUTSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LUTEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& LUTEnable;

        //@}


        //! \name Categories: LUTControl and LUTControls
        //@{
        /*!
            \brief Pixel value to be replaced with the LUT Value pixel value - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress


            Visibility: Beginner

            Selected by: LUTSelector

            Selecting Parameters: LUTValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LUTIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LUTIndex;

        //@}


        //! \name Categories: LUTControl and LUTControls
        //@{
        /*!
            \brief Sets the lookup table (LUT) to be configured - Applies to: CameraLink, GigE and ace USB

            Sets the lookup table (LUT) to be configured. All changes to the LUT settings will be applied to the selected LUT.

            Visibility: Beginner

            Selecting Parameters: LUTEnable, LUTIndex, LUTValue and LUTValueAll

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LUTSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LUTSelectorEnums>& LUTSelector;

        //@}


        //! \name Categories: LUTControl and LUTControls
        //@{
        /*!
            \brief New pixel value to replace the LUT Index pixel value - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress


            Visibility: Beginner

            Selected by: LUTIndex and LUTSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LUTValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LUTValue;

        //@}


        //! \name Categories: LUTControl and LUTControls
        //@{
        /*!
            \brief A single register that lets you access all LUT entries - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB and boost CoaXPress

            A single register that lets you access all LUT entries. In many cases, this is faster than repeatedly changing individual entries in the LUT.

            Visibility: Beginner

            Selected by: LUTSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LUTValueAll" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IRegisterEx& LUTValueAll;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Indicates the last error code in the memory - Applies to: CameraLink, GigE and blaze

            Indicates the last error code in the memory. To delete the last error code from the list of error codes, use the Clear Last Error command.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LastError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LastErrorEnums>& LastError;

        //@}


        //! \name Categories: LateActionEventData
        //@{
        /*!
            \brief Stream channel index of the Action Late event - Applies to: GigE

            Stream channel index of the Action Late event. An Action Late event is raised when a scheduled action command with a timestamp in the past is received.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LateActionEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LateActionEventStreamChannelIndex;

        //@}


        //! \name Categories: LateActionEventData
        //@{
        /*!
            \brief Timestamp of the Action Late event - Applies to: GigE

            Timestamp of the Action Late event. An Action Late event is raised when a scheduled action command with a timestamp in the past is received.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LateActionEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LateActionEventTimestamp;

        //@}


        //! \name Categories: AOI
        //@{
        /*!
            \brief Sets whether vertical binning is used - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LegacyBinningVertical" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LegacyBinningVerticalEnums>& LegacyBinningVertical;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Sets the light source preset - Applies to: ace USB, dart BCON, dart USB and pulse USB

            Sets the light source preset. The colors in the image will be corrected so that they are appropriate for the selected light source.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LightSourcePreset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LightSourcePresetEnums>& LightSourcePreset;

        //@}


        //! \name Categories: ColorImprovementsControl and ImageQualityControl
        //@{
        /*!
            \brief Sets the type of light source for which color transformation will be performed - Applies to: CameraLink and GigE


            Visibility: Expert

            Selected by: ColorTransformationSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LightSourceSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LightSourceSelectorEnums>& LightSourceSelector;

        //@}


        //! \name Categories: Line1RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Line 1 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line1RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line1RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: Line1RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Line 1 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line1RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line1RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: Line2RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Line 2 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line2RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line2RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: Line2RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Line 2 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line2RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line2RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: Line3RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Line 3 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line3RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line3RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: Line3RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Line 3 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line3RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line3RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: Line4RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Line 4 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line4RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line4RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: Line4RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Line 4 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Line4RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Line4RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: DigitalIOControl
        //@{
        /*!
            \brief Line debouncer time in microseconds - Applies to: ace USB, dart BCON and dart USB

            Line debouncer time in microseconds. The Line Debouncer allows you to filter out invalid hardware signals by specifying a minimum signal length.

            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineDebouncerTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LineDebouncerTime;

        //@}


        //! \name Categories: DigitalIO
        //@{
        /*!
            \brief Line debouncer time in microseconds - Applies to: CameraLink and GigE

            Line debouncer time in microseconds. The Line Debouncer allows you to filter out invalid hardware signals by specifying a minimum signal length.

            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineDebouncerTimeAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LineDebouncerTimeAbs;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Indicates the electrical configuration of the currently selected line - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineFormat" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineFormatEnums>& LineFormat;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Enables the signal inverter function for the currently selected input or output line - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineInverter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& LineInverter;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Indicates the line logic of the currently selected line - Applies to: CameraLink, GigE and ace USB


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineLogic" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineLogicEnums>& LineLogic;

        //@}


        //! \name Categories: DigitalIOControl
        //@{
        /*!
            \brief Minimum signal width of an output signal (in microseconds) - Applies to: ace USB


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineMinimumOutputPulseWidth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LineMinimumOutputPulseWidth;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Sets the mode for the selected line - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB

            Sets the mode for the selected line. This controls whether the physical line is used to input or output a signal.

            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineModeEnums>& LineMode;

        //@}


        //! \name Categories: DigitalIOControl
        //@{
        /*!
            \brief Resets the overload status of the selected line - Applies to: ace USB

            This command resets the overload status of the selected line. If the overload condition is still fulfilled, the overload status will be set again immediately.

            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineOverloadReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& LineOverloadReset;

        //@}


        //! \name Categories: DigitalIOControl
        //@{
        /*!
            \brief Indicates whether an overload condition has been detected on the selected line - Applies to: ace USB


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineOverloadStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& LineOverloadStatus;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Number of bytes separating the starting pixels of two consecutive lines - Applies to: ace USB

            Number of bytes separating the starting pixels of two consecutive lines. This feature is useful if you want to align your image data to fixed-size groups of digits, e.g., to 4-byte (32-bit) or 8-byte (64-bit) words. Data alignment can improve performance.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LinePitch" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LinePitch;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Enables the alignment of output image data to multiples of 4 bytes - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LinePitchEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& LinePitchEnable;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Sets the I/O line to be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB

            Sets the I/O line to be configured. All changes to the line settings will be applied to the selected line.

            Visibility: Beginner

            Selecting Parameters: BslInputFilterTime, BslInputHoldOffTime, BslLineOverloadStatus, LineDebouncerTime, LineDebouncerTimeAbs, LineFormat, LineInverter, LineLogic, LineMinimumOutputPulseWidth, LineMode, LineOverloadReset, LineOverloadStatus, LineSource, LineStatus, LineTermination and MinOutPulseWidthAbs

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineSelectorEnums>& LineSelector;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Sets the source signal for the currently selected line - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB

            Sets the source signal for the currently selected line. The currently selected line must be an output line.

            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineSourceEnums>& LineSource;

        //@}


        //! \name Categories: LineStartOvertriggerEventData
        //@{
        /*!
            \brief Stream channel index of the Line Start Overtrigger event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineStartOvertriggerEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LineStartOvertriggerEventStreamChannelIndex;

        //@}


        //! \name Categories: LineStartOvertriggerEventData
        //@{
        /*!
            \brief Timestamp of the Line Start Overtrigger event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineStartOvertriggerEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LineStartOvertriggerEventTimestamp;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Indicates the current logical state of the selected line - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& LineStatus;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Single bit field indicating the current logical state of all available line signals at time of polling - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineStatusAll" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LineStatusAll;

        //@}


        //! \name Categories: DigitalIO
        //@{
        /*!
            \brief Enables the termination resistor of the selected input line - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineTermination" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& LineTermination;

        //@}


        //! \name Categories: DigitalIO
        //@{
        /*!
            \brief Minimum signal width of an output signal (in microseconds) - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: LineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MinOutPulseWidthAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& MinOutPulseWidthAbs;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Operating channel of the camera - Applies to: blaze

            Operating channel of the camera. In multi-camera setups, use a different channel on each camera. This ensures that the cameras are operating at different frequencies and their light sources will not interfere with the other cameras' light sources.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MultiCameraChannel" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MultiCameraChannel;

        //@}


        //! \name Categories: PGIControl
        //@{
        /*!
            \brief Amount of noise reduction to be applied - Applies to: ace USB

            Amount of noise reduction to be applied. The higher the value, the less chroma noise will be visible in your images. However, excessively high values may result in image information loss.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=NoiseReduction" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& NoiseReduction;

        //@}


        //! \name Categories: PGIControl
        //@{
        /*!
            \brief Amount of noise reduction to be applied - Applies to: GigE

            Amount of noise reduction to be applied. The higher the value, the less chroma noise will be visible in your images. However, excessively high values may result in image information loss.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=NoiseReductionAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& NoiseReductionAbs;

        //@}


        //! \name Categories: PGIControl
        //@{
        /*!
            \brief Amount of noise reduction to be applied (raw value) - Applies to: GigE

            Amount of noise reduction to be applied (raw value). The higher the value, the less chroma noise will be visible in your images. However, excessively high values may result in image information loss.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=NoiseReductionRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& NoiseReductionRaw;

        //@}


        //! \name Categories: ActionControl
        //@{
        /*!
            \brief Number of separate action signals supported by the camera - Applies to: GigE

            Number of separate action signals supported by the camera. Determines how many action signals the camera can handle in parallel, i.e., how many different action commands can be configured on the camera.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=NumberOfActionSignals" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& NumberOfActionSignals;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Horizontal offset of the region of interest (area of interest) from the left side of the sensor (in pixels) - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Horizontal offset from the left side of the sensor to the region of interest (area of interest) (in pixels).

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OffsetX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& OffsetX;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Vertical offset of the region of interest (area of interest) from the top of the sensor (in pixels) - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Vertical offset from the top of the sensor to the region of interest (area of interest) (in pixels).

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& OffsetY;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Sets the operating mode of the camera - Applies to: blaze

            Sets the operating mode of the camera. The choice you make here, affects the working range of the camera, i.e., the Minimum Working Range and Maximum Working Range parameters. If the operating mode is changed, the exposure time is set to the recommended default value.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OperatingMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<OperatingModeEnums>& OperatingMode;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Enables the outlier removal - Applies to: blaze

            Removes pixels that differ significantly from their local environment.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OutlierRemoval" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& OutlierRemoval;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Indicates whether an over temperature state has been detected - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& OverTemperature;

        //@}


        //! \name Categories: OverTemperatureEventData
        //@{
        /*!
            \brief Stream channel index of the Over Temperature event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverTemperatureEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& OverTemperatureEventStreamChannelIndex;

        //@}


        //! \name Categories: OverTemperatureEventData
        //@{
        /*!
            \brief Timestamp of the Over Temperature event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverTemperatureEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& OverTemperatureEventTimestamp;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Configures overlapping exposure and image readout - Applies to: dart BCON, dart USB and pulse USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverlapMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<OverlapModeEnums>& OverlapMode;

        //@}


        //! \name Categories: RemoveParamLimits
        //@{
        /*!
            \brief Sets the parameter whose factory limits can be removed - Applies to: CameraLink and GigE

            Sets the parameter whose factory limits can be removed. The factory limits can be removed using the Remove Limits parameter.

            Visibility: Guru

            Selecting Parameters: RemoveLimits

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ParameterSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ParameterSelectorEnums>& ParameterSelector;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: dart USB and pulse USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadFinalTransfer1Size" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PayloadFinalTransfer1Size;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: dart USB and pulse USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadFinalTransfer2Size" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PayloadFinalTransfer2Size;

        //@}


        //! \name Categories: TransportLayer and TransportLayerControl
        //@{
        /*!
            \brief Size of the payload in bytes - Applies to: CamEmu, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart USB and pulse USB

            Size of the payload in bytes. This is the total number of bytes sent in the payload.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PayloadSize;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief This parameter is required when using the sequencer - Applies to: ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadTransferBlockDelay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PayloadTransferBlockDelay;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: dart USB and pulse USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadTransferCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PayloadTransferCount;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: dart USB and pulse USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadTransferSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PayloadTransferSize;

        //@}


        //! \name Categories: PGIControl
        //@{
        /*!
            \brief Enables Basler PGI image optimizations - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PgiMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PgiModeEnums>& PgiMode;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief Sets the color coding of the pixels in the acquired images - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelCoding" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PixelCodingEnums>& PixelCoding;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Indicates the alignment of the camera's Bayer filter to the pixels in the acquired images - Applies to: CameraLink, GigE, ace USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelColorFilter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PixelColorFilterEnums>& PixelColorFilter;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Maximum possible pixel value that can be transferred from the camera - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelDynamicRangeMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PixelDynamicRangeMax;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Minimum possible pixel value that can be transferred from the camera - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelDynamicRangeMin" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PixelDynamicRangeMin;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Sets the format of the pixel data transmitted by the camera - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Sets the format of the pixel data transmitted by the camera. The available pixel formats depend on the camera model and whether the camera is monochrome or color.

            Visibility: Beginner

            Selected by: ComponentSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelFormat" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PixelFormatEnums>& PixelFormat;

        //@}


        //! \name Categories: TransportLayer
        //@{
        /*!
            \brief Enables legacy pixel format encoding - Applies to: GigE

            Enables legacy GVSP pixel format encoding to ensure compatibility with older camera models.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelFormatLegacy" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& PixelFormatLegacy;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Indicates the depth of the pixel values in the image (in bits per pixel) - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart USB and pulse USB

            Indicates the depth of the pixel values in the image (in bits per pixel). The potential values depend on the pixel format setting.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PixelSizeEnums>& PixelSize;

        //@}


        //! \name Categories: RemoveParamLimits
        //@{
        /*!
            \brief Sets the number of prelines - Applies to: CameraLink and GigE

            This value sets the number of prelines.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Prelines" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Prelines;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief Enables the output of color-improved raw image data - Applies to: CameraLink and GigE

            Enables the output of color-improved raw image data. If enabled, color transformation and color adjustment will be applied to Bayer pixel formats.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ProcessedRawEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ProcessedRawEnable;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Indicates the expected accuracy of the PTP device clock when it is or becomes the grandmaster - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpClockAccuracy" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PtpClockAccuracyEnums>& PtpClockAccuracy;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Returns the latched clock ID of the PTP device - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpClockID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PtpClockID;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Latches the current values from the device's PTP clock data set - Applies to: ace 2 GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpDataSetLatch" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& PtpDataSetLatch;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Enables the Precision Time Protocol (PTP) - Applies to: ace 2 GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& PtpEnable;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Returns the latched grandmaster clock ID of the PTP device - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpGrandmasterClockID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PtpGrandmasterClockID;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Returns the latched offset from the PTP master clock in nanoseconds - Applies to: ace 2 GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpOffsetFromMaster" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PtpOffsetFromMaster;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Returns the latched parent clock ID of the PTP device - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpParentClockID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PtpParentClockID;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Returns the latched state of the clock servo - Applies to: ace 2 GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpServoStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PtpServoStatusEnums>& PtpServoStatus;

        //@}


        //! \name Categories: PtpControl
        //@{
        /*!
            \brief Returns the latched state of the PTP clock - Applies to: ace 2 GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PtpStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PtpStatusEnums>& PtpStatus;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Enables or disables the currently selected ROI zone - Applies to: GigE and ace USB


            Visibility: Expert

            Selected by: ROIZoneSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ROIZoneMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ROIZoneModeEnums>& ROIZoneMode;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Vertical offset of the currently selected ROI zone - Applies to: GigE and ace USB


            Visibility: Expert

            Selected by: ROIZoneSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ROIZoneOffset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ROIZoneOffset;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Sets the ROI zone that can be configured - Applies to: GigE and ace USB


            Visibility: Expert

            Selecting Parameters: ROIZoneMode, ROIZoneOffset and ROIZoneSize

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ROIZoneSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ROIZoneSelectorEnums>& ROIZoneSelector;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Height of the currently selected ROI zone - Applies to: GigE and ace USB


            Visibility: Expert

            Selected by: ROIZoneSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ROIZoneSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ROIZoneSize;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Time required for reading out each subframe from the sensor - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReadoutTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ReadoutTime;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Sensor readout time with current settings - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReadoutTimeAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ReadoutTimeAbs;

        //@}


        //! \name Categories: RemoveParamLimits
        //@{
        /*!
            \brief Removes the factory-set limit of the selected parameter - Applies to: CameraLink and GigE

            Removes the factory-set limit of the selected parameter. If the factory limits are removed, a wider range of parameter values is available and only subect to technical restrictions. Choosing parameter values outside of the factory limits may affect image quality.

            Visibility: Guru

            Selected by: ParameterSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=RemoveLimits" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& RemoveLimits;

        //@}


        //! \name Categories: RemoveParameterLimitControl
        //@{
        /*!
            \brief Removes the factory-set limit of the selected parameter - Applies to: ace USB

            Removes the factory-set limit of the selected parameter. If the factory limits are removed, a wider range of parameter values is available and only subect to technical restrictions. Choosing parameter values outside of the factory limits may affect image quality.

            Visibility: Guru

            Selected by: RemoveParameterLimitSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=RemoveParameterLimit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& RemoveParameterLimit;

        //@}


        //! \name Categories: RemoveParameterLimitControl
        //@{
        /*!
            \brief Sets the parameter whose factory limits can be removed - Applies to: ace USB

            Sets the parameter whose factory limits can be removed. The factory limits can be removed using the Remove Limits parameter.

            Visibility: Guru

            Selecting Parameters: RemoveParameterLimit

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=RemoveParameterLimitSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<RemoveParameterLimitSelectorEnums>& RemoveParameterLimitSelector;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Time during which the sensor is reset before the next subframe is acquired - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResetTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ResetTime;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Maximum frame acquisition period with current camera settings - Applies to: CameraLink and GigE

            Maximum frame acquisition period with current camera settings (in microseconds).

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResultingFramePeriodAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ResultingFramePeriodAbs;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Maximum frame acquisition rate with current camera settings - Applies to: ace USB, boost CoaXPress, dart BCON, dart USB and pulse USB

            Maximum frame acquisition rate with current camera settings (in frames per second).

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResultingFrameRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ResultingFrameRate;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Maximum frame acquisition rate with current camera settings - Applies to: CamEmu, CameraLink and GigE

            Maximum frame acquisition rate with current camera settings (in frames per second).

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResultingFrameRateAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ResultingFrameRateAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Maximum line acquisition period with current camera settings - Applies to: CameraLink and GigE

            Maximum line acquisition period with current camera settings (in microseconds).

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResultingLinePeriodAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ResultingLinePeriodAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Maximum line acquisition rate with current camera settings - Applies to: CameraLink and GigE

            Maximum line acquisition rate with current camera settings (in frames per second).

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResultingLineRateAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ResultingLineRateAbs;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Enables horizontal mirroring of the image - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Enables horizontal mirroring of the image. The pixel values of every line in a captured image will be swapped along the line's center. You can use the ROI feature when using the Reverse X feature. The position of the ROI relative to the sensor remains the same.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReverseX" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ReverseX;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Enables vertical mirroring of the image - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Enables vertical mirroring of the image. The pixel values of every column in a captured image will be swapped along the column's center. You can use the ROI feature when using the Reverse Y feature. The position of the ROI relative to the sensor remains the same.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReverseY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ReverseY;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: ace 2 USB, ace USB and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadFinalTransfer1Size" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SIPayloadFinalTransfer1Size;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: ace 2 USB, ace USB and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadFinalTransfer2Size" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SIPayloadFinalTransfer2Size;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: ace 2 USB, ace USB and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadTransferCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SIPayloadTransferCount;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief For information only  May be required when contacting Basler support - Applies to: ace 2 USB, ace USB and dart 2 USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadTransferSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SIPayloadTransferSize;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Horizontal scaling factor - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ScalingHorizontal" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ScalingHorizontal;

        //@}


        //! \name Categories: AOI
        //@{
        /*!
            \brief Horizontal scaling factor - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ScalingHorizontalAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ScalingHorizontalAbs;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Vertical scaling factor - Applies to: ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ScalingVertical" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ScalingVertical;

        //@}


        //! \name Categories: AOI
        //@{
        /*!
            \brief Vertical scaling factor - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ScalingVerticalAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ScalingVerticalAbs;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Maximum valid transmitted coordinate value of the selected Axis - Applies to: blaze


            Visibility: Expert

            Selected by: Scan3dCoordinateSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dAxisMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dAxisMax;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Minimum valid transmitted coordinate value of the selected Axis - Applies to: blaze


            Visibility: Expert

            Selected by: Scan3dCoordinateSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dAxisMin" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dAxisMin;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Adds an offset to the measured distance - Applies to: blaze

            This parameter allows you to adjust
  the internal camera calibration.
  The offset specified by Scan3dCalibrationOffset is added to the radial 
  distances the camera measures.
  The camera transforms the radial distances into x, y, z coordinates in a 
  Cartesian coordinate system whose origin lies in the camera's optical center.
  The Scan3dCalibrationOffset parameter can be used to manually correct a
  temperature-dependent drift.
  Note: Since Scan3dCalibrationOffset is added to the radial distances, it can't
  be used to translate the origin of the coordinate system, i.e., it can't be
  used to add a constant offset to the z coordinate.
  Specifically, you should not use it in an attempt to shift the origin of the
  camera's coordinate system from the optical center to
  the front of the camera housing. Trying to do so will result in measurement
  errors causing planar surfaces to appear curved.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dCalibrationOffset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dCalibrationOffset;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Offset when transforming a pixel from relative coordinates to world coordinates - Applies to: blaze


            Visibility: Expert

            Selected by: Scan3dCoordinateSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dCoordinateOffset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dCoordinateOffset;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Scale factor when transforming a pixel from relative coordinates to world coordinates - Applies to: blaze


            Visibility: Expert

            Selected by: Scan3dCoordinateSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dCoordinateScale" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dCoordinateScale;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Selects the individual coordinates in the vectors for 3D information/transformation - Applies to: blaze


            Visibility: Expert

            Selecting Parameters: Scan3dAxisMax, Scan3dAxisMin, Scan3dCoordinateOffset, Scan3dCoordinateScale, Scan3dInvalidDataFlag and Scan3dInvalidDataValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dCoordinateSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<Scan3dCoordinateSelectorEnums>& Scan3dCoordinateSelector;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Specifies the Coordinate system to use for the device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dCoordinateSystem" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<Scan3dCoordinateSystemEnums>& Scan3dCoordinateSystem;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Defines coordinate system reference location - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dCoordinateSystemReference" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<Scan3dCoordinateSystemReferenceEnums>& Scan3dCoordinateSystemReference;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Specifies the unit used when delivering (calibrated) distance data - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dDistanceUnit" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<Scan3dDistanceUnitEnums>& Scan3dDistanceUnit;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Returns the focal length of the camera in pixel - Applies to: blaze

            Returns the focal length of the camera in pixel. The focal length depends on the selected region. The value of this feature takes into account horizontal binning, decimation, or any other function changing the image resolution.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dFocalLength" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dFocalLength;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Enables the definition of a non-valid flag value in the data stream - Applies to: blaze

            Enables the definition of a non-valid flag value in the data stream. Note that the confidence output is an alternate recommended way to identify non-valid pixels. Using an Scan3dInvalidDataValue may give processing penalties due to special handling.

            Visibility: Expert

            Selected by: Scan3dCoordinateSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dInvalidDataFlag" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& Scan3dInvalidDataFlag;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Value which identifies a non-valid pixel if Scan3dInvalidDataFlag is enabled - Applies to: blaze


            Visibility: Expert

            Selected by: Scan3dCoordinateSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dInvalidDataValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dInvalidDataValue;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Controls the Calibration and data organization of the device and the coordinates transmitted - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dOutputMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<Scan3dOutputModeEnums>& Scan3dOutputMode;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Returns the value of the horizontal position of the principal point, relative to the region origin, i e - Applies to: blaze

            Returns the value of the horizontal position of the principal point, relative to the region origin, i.e. OffsetX. The value of this feature takes into account horizontal binning, decimation, or any other function changing the image resolution.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dPrincipalPointU" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dPrincipalPointU;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Returns the value of the vertical position of the principal point, relative to the region origin, i e - Applies to: blaze

            Returns the value of the vertical position of the principal point, relative to the region origin, i.e. OffsetY. The value of this feature takes into account vertical binning, decimation, or any other function changing the image resolution.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Scan3dPrincipalPointV" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& Scan3dPrincipalPointV;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief Amount of data bits the sensor produces for one sample - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorBitDepth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SensorBitDepthEnums>& SensorBitDepth;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief This feature represents the number of digitized samples outputted simultaneously by the camera A/D conversion stage - Applies to: CameraLink and GigE

            This feature represents the number of digitized samples output simultaneously by the camera A/D conversion stage.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorDigitizationTaps" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SensorDigitizationTapsEnums>& SensorDigitizationTaps;

        //@}


        //! \name Categories: AOI, DeviceInformation and ImageFormatControl
        //@{
        /*!
            \brief Height of the camera's sensor in pixels - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorHeight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SensorHeight;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Physical size (pitch) in the y direction of a photo sensitive pixel unit - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorPixelHeight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SensorPixelHeight;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Physical size (pitch) in the x direction of a photo sensitive pixel unit - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorPixelWidth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SensorPixelWidth;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Distance between the sensor plane and the front of the housing - Applies to: blaze

            Distance between the sensor plane and the front of the housing. This value can be used to calculate the distance between the optical center and the front of the housing.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorPosition" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SensorPosition;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the sensor readout mode - Applies to: GigE and ace USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorReadoutMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SensorReadoutModeEnums>& SensorReadoutMode;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Sensor readout time with current settings - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorReadoutTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SensorReadoutTime;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Sets the shutter mode of the camera - Applies to: ace 2 GigE, ace 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorShutterMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SensorShutterModeEnums>& SensorShutterMode;

        //@}


        //! \name Categories: AOI, DeviceInformation and ImageFormatControl
        //@{
        /*!
            \brief Width of the camera's sensor in pixels - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorWidth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SensorWidth;

        //@}


        //! \name Categories: SequenceControlConfiguration
        //@{
        /*!
            \brief Sets which bit of the sequence set address can be assigned to an input line - Applies to: CameraLink and GigE

            Sets which bit of the sequence set address can be assigned to an input line. An input line can be set as the control source for this bit using the Address Bit Source parameter.

            Visibility: Guru

            Selecting Parameters: SequenceAddressBitSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceAddressBitSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequenceAddressBitSelectorEnums>& SequenceAddressBitSelector;

        //@}


        //! \name Categories: SequenceControlConfiguration
        //@{
        /*!
            \brief Sets an input line as the control source for the currently selected sequence set address bit - Applies to: CameraLink and GigE

            Sets an input line as the control source for the currently selected sequence set address bit. The bit can be selected using the Address Bit Selector parameter.

            Visibility: Guru

            Selected by: SequenceAddressBitSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceAddressBitSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequenceAddressBitSourceEnums>& SequenceAddressBitSource;

        //@}


        //! \name Categories: SequenceControlConfiguration
        //@{
        /*!
            \brief Sets the sequence set advance mode - Applies to: CameraLink and GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceAdvanceMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequenceAdvanceModeEnums>& SequenceAdvanceMode;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Enables asynchronous advance from one sequence set to the next - Applies to: CameraLink and GigE

            Enables asynchronous advance from one sequence set to the next. The advance is asynchronous to the camera's frame trigger. Only available in Controlled sequence advance mode.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceAsyncAdvance" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SequenceAsyncAdvance;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Enables asynchronous restart of the sequence set sequence - Applies to: CameraLink and GigE

            Enables asynchronous restart of the sequence set sequence, starting with the sequence set that has the lowest index number. The restart is asynchronous to the camera's frame trigger. Only available in Auto and Controlled sequence advance mode.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceAsyncRestart" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SequenceAsyncRestart;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Sets whether the sequencer can be configured - Applies to: GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceConfigurationMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequenceConfigurationModeEnums>& SequenceConfigurationMode;

        //@}


        //! \name Categories: SequenceControlConfiguration
        //@{
        /*!
            \brief Sets whether sequence advance or sequence restart can be configured - Applies to: CameraLink and GigE

            Sets whether sequence advance or sequence restart can be configured. A control source must be chosen using the Sequence Control Source parameter.

            Visibility: Guru

            Selecting Parameters: SequenceControlSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceControlSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequenceControlSelectorEnums>& SequenceControlSelector;

        //@}


        //! \name Categories: SequenceControlConfiguration
        //@{
        /*!
            \brief Sets the source for sequence control - Applies to: CameraLink and GigE


            Visibility: Guru

            Selected by: SequenceControlSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceControlSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequenceControlSourceEnums>& SequenceControlSource;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Current sequence set - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceCurrentSet" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequenceCurrentSet;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Enables the sequencer - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& SequenceEnable;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Number of sequence set executions - Applies to: CameraLink and GigE

            Number of consecutive executions per sequence cycle of the selected sequence set. Only available in Auto sequence advance mode.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceSetExecutions" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequenceSetExecutions;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Index number of a sequence set - Applies to: CameraLink and GigE

            This number uniquely identifies a sequence set.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceSetIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequenceSetIndex;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Loads a sequence set - Applies to: CameraLink and GigE

            Loads an existing sequence set to make it the current sequence set.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceSetLoad" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SequenceSetLoad;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Stores the current sequence set - Applies to: CameraLink and GigE

            Stores the current sequence set. Storing the current sequence set will overwrite any existing sequence set with the same index number. The sequence set is stored in the volatile memory and will therefore be lost if the camera is reset or if power is switched off.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceSetStore" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SequenceSetStore;

        //@}


        //! \name Categories: SequenceControl
        //@{
        /*!
            \brief Total number of sequence sets in the sequence - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequenceSetTotalNumber" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequenceSetTotalNumber;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Sets whether the sequencer can be configured - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerConfigurationMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequencerConfigurationModeEnums>& SequencerConfigurationMode;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Sets whether the sequencer can be used for image acquisition - Applies to: ace USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequencerModeEnums>& SequencerMode;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Sequencer path to be used - Applies to: ace USB


            Visibility: Expert

            Selected by: SequencerSetSelector

            Selecting Parameters: SequencerSetNext, SequencerTriggerActivation and SequencerTriggerSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerPathSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequencerPathSelector;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Index number of the currently active sequencer set - Applies to: ace USB

            Index number of the current sequencer set, i.e., of the sequencer set whose parameter values are currently in the active set.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerSetActive" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequencerSetActive;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Loads the parameter values of a sequencer set into the active set - Applies to: ace USB

            Loads the parameter values of a sequencer set into the active set. The sequencer set will then be the current set.

            Visibility: Expert

            Selected by: SequencerSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerSetLoad" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SequencerSetLoad;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Sequencer set that follows the current sequence set - Applies to: ace USB


            Visibility: Expert

            Selected by: SequencerPathSelector and SequencerSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerSetNext" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequencerSetNext;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Saves the sequencer parameter values that are currently in the active set - Applies to: ace USB

            Saves the sequencer parameter values that are currently in the active set. The values will be saved in the sequencer set whose sequencer set index number is currently selected.

            Visibility: Expert

            Selected by: SequencerSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerSetSave" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SequencerSetSave;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief The sequencer set to be configured - Applies to: ace USB

            The sequencer set to be configured. Sequencer sets are identified by their sequencer set index numbers.

            Visibility: Expert

            Selecting Parameters: SequencerPathSelector, SequencerSetLoad, SequencerSetNext, SequencerSetSave, SequencerTriggerActivation and SequencerTriggerSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerSetSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequencerSetSelector;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Sequencer set that will be used with the first Frame Start trigger after the Sequencer Mode parameter was set to On - Applies to: ace USB

            Sequencer set that will be used with the first Frame Start trigger after the Sequencer Mode parameter was set to On. Only sequencer set 0 is available.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerSetStart" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SequencerSetStart;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Sets the logical state that makes the sequencer advance to the next - Applies to: ace USB

            Sets the logical state that makes the sequencer advance to the next. Currently, only High is available.

            Visibility: Expert

            Selected by: SequencerPathSelector and SequencerSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerTriggerActivation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequencerTriggerActivationEnums>& SequencerTriggerActivation;

        //@}


        //! \name Categories: SequencerControl
        //@{
        /*!
            \brief Sets the trigger source for sequencer set advance - Applies to: ace USB

            Sets the trigger source for sequencer set advance with the currently selected path.

            Visibility: Expert

            Selected by: SequencerPathSelector and SequencerSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SequencerTriggerSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SequencerTriggerSourceEnums>& SequencerTriggerSource;

        //@}


        //! \name Categories: Shading
        //@{
        /*!
            \brief Enables the selected shading correction type - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: ShadingSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShadingEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ShadingEnable;

        //@}


        //! \name Categories: Shading
        //@{
        /*!
            \brief Sets the kind of shading correction - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selecting Parameters: ShadingEnable, ShadingSetDefaultSelector and ShadingSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShadingSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShadingSelectorEnums>& ShadingSelector;

        //@}


        //! \name Categories: Shading
        //@{
        /*!
            \brief Loads the selected shading set - Applies to: CameraLink and GigE

            This command copies the selected shading set from the camera's non-volatile memory into the volatile memory. If shading correction is enabled, it will be performed using the shading set in the volatile memory.

            Visibility: Expert

            Selected by: ShadingSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShadingSetActivate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& ShadingSetActivate;

        //@}


        //! \name Categories: Shading
        //@{
        /*!
            \brief Enables/disables shading set creation - Applies to: CameraLink and GigE


            Visibility: Expert

            Selected by: ShadingSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShadingSetCreate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShadingSetCreateEnums>& ShadingSetCreate;

        //@}


        //! \name Categories: Shading
        //@{
        /*!
            \brief Sets the bootup shading set - Applies to: CameraLink and GigE

            Sets the shading set that will be loaded into the volatile memory during camera start.

            Visibility: Expert

            Selected by: ShadingSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShadingSetDefaultSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShadingSetDefaultSelectorEnums>& ShadingSetDefaultSelector;

        //@}


        //! \name Categories: Shading
        //@{
        /*!
            \brief Sets which shading set can be enabled or created - Applies to: CameraLink and GigE


            Visibility: Expert

            Selected by: ShadingSelector

            Selecting Parameters: ShadingSetActivate and ShadingSetCreate

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShadingSetSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShadingSetSelectorEnums>& ShadingSetSelector;

        //@}


        //! \name Categories: Shading
        //@{
        /*!
            \brief Indicates error statuses related to shading correction - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShadingStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShadingStatusEnums>& ShadingStatus;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Current value of the tick counter - Applies to: CameraLink and GigE

            Current value of the tick counter of the shaft encoder module.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleCounter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ShaftEncoderModuleCounter;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Maximum value of the tick counter - Applies to: CameraLink and GigE

            Maximum value of the tick counter of the shaft encoder module. If the tick counter is incrementing and reaches the maximum, it will roll over to 0. If the tick counter is decrementing and reaches 0, it will roll back to the specified maximum value.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleCounterMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ShaftEncoderModuleCounterMax;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Sets the counting mode of the tick counter - Applies to: CameraLink and GigE

            Sets the counting mode of the tick counter of the shaft encoder module.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleCounterMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderModuleCounterModeEnums>& ShaftEncoderModuleCounterMode;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Resets the tick counter to 0 - Applies to: CameraLink and GigE

            Resets the tick counter of the shaft encoder module to 0.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleCounterReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& ShaftEncoderModuleCounterReset;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Sets the phase of the shaft encoder - Applies to: CameraLink and GigE

            Sets the phase of the shaft encoder as input for the shaft encoder module.

            Visibility: Expert

            Selecting Parameters: ShaftEncoderModuleLineSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleLineSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderModuleLineSelectorEnums>& ShaftEncoderModuleLineSelector;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Sets the line source for the shaft encoder module - Applies to: CameraLink and GigE


            Visibility: Expert

            Selected by: ShaftEncoderModuleLineSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleLineSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderModuleLineSourceEnums>& ShaftEncoderModuleLineSource;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Sets how the shaft encoder module outputs trigger signals - Applies to: CameraLink and GigE


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderModuleModeEnums>& ShaftEncoderModuleMode;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Maximum value of the reverse counter - Applies to: CameraLink and GigE

            Maximum value of the reverse counter of the shaft encoder module (range: 0 to 32767).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleReverseCounterMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ShaftEncoderModuleReverseCounterMax;

        //@}


        //! \name Categories: ShaftEncoderModule
        //@{
        /*!
            \brief Resets the reverse counter of the shaft encoder module - Applies to: CameraLink and GigE

            Resets the reverse counter of the shaft encoder module to 0 and informs the module that the current direction of conveyor movement is forward. Reset must be carried out before the first conveyor movement in the forward direction.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderModuleReverseCounterReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& ShaftEncoderModuleReverseCounterReset;

        //@}


        //! \name Categories: ImageQualityControl and PGIControl
        //@{
        /*!
            \brief Sharpening value to be applied - Applies to: ace USB, dart BCON, dart USB and pulse USB

            Sharpening value to be applied. The higher the sharpness, the more distinct the image subject's contours will be. However, excessively high values may result in image information loss.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SharpnessEnhancement" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SharpnessEnhancement;

        //@}


        //! \name Categories: PGIControl
        //@{
        /*!
            \brief Sharpening value to be applied - Applies to: GigE

            Sharpening value to be applied. The higher the sharpness, the more distinct the image subject's contours will be. However, excessively high values may result in image information loss.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SharpnessEnhancementAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SharpnessEnhancementAbs;

        //@}


        //! \name Categories: PGIControl
        //@{
        /*!
            \brief Sharpening value to be applied (raw value) - Applies to: GigE

            Sharpening value to be applied (raw value). The higher the sharpness, the more distinct the image subject's contours will be. However, excessively high values may result in image information loss.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SharpnessEnhancementRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SharpnessEnhancementRaw;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the shutter mode of the camera - Applies to: CameraLink, GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShutterMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShutterModeEnums>& ShutterMode;

        //@}


        //! \name Categories: SoftwareSignalControl
        //@{
        /*!
            \brief Executes the selected software signal - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: SoftwareSignalSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareSignalPulse" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SoftwareSignalPulse;

        //@}


        //! \name Categories: SoftwareSignalControl
        //@{
        /*!
            \brief Sets the software signal to be executed - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selecting Parameters: SoftwareSignalPulse

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareSignalSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SoftwareSignalSelectorEnums>& SoftwareSignalSelector;

        //@}


        //! \name Categories: ImageFormat
        //@{
        /*!
            \brief Correction factor to account for the gaps between the sensor's lines - Applies to: CameraLink and GigE

            Correction factor to account for the gaps between the sensor's lines. Related line captures will be combined. Positive values: The object will pass the top sensor line first. Negative values: The object will pass the bottom sensor line first. In color cameras, the top sensor line is the green line, and the bottom sensor line is the blue line.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SpatialCorrection" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SpatialCorrection;

        //@}


        //! \name Categories: StackedZoneImaging
        //@{
        /*!
            \brief Enables the Stacked Zone Imaging feature - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StackedZoneImagingEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& StackedZoneImagingEnable;

        //@}


        //! \name Categories: StackedZoneImaging
        //@{
        /*!
            \brief Index number of the zone to configure - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selecting Parameters: StackedZoneImagingZoneEnable, StackedZoneImagingZoneHeight and StackedZoneImagingZoneOffsetY

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StackedZoneImagingIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StackedZoneImagingIndex;

        //@}


        //! \name Categories: StackedZoneImaging
        //@{
        /*!
            \brief Enables the selected zone - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: StackedZoneImagingIndex

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StackedZoneImagingZoneEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& StackedZoneImagingZoneEnable;

        //@}


        //! \name Categories: StackedZoneImaging
        //@{
        /*!
            \brief Height of the selected zone - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: StackedZoneImagingIndex

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StackedZoneImagingZoneHeight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StackedZoneImagingZoneHeight;

        //@}


        //! \name Categories: StackedZoneImaging
        //@{
        /*!
            \brief Vertical offset (top offset) of the selected zone - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: StackedZoneImagingIndex

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StackedZoneImagingZoneOffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StackedZoneImagingZoneOffsetY;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Time that passes between triggering the camera and exposure starting - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StartupTime" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StartupTime;

        //@}


        //! \name Categories: AnalogControls
        //@{
        /*!
            \brief Substrate voltage - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SubstrateVoltage" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SubstrateVoltage;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Enables the synchronous free run mode - Applies to: GigE and blaze

            Enables the synchronous free run mode. If enabled, the camera will generate all required frame start or line start trigger signals internally. You don't need to apply frame start or line start trigger signals to the camera.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncFreeRunTimerEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& SyncFreeRunTimerEnable;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief High 32 bits of the synchronous free run trigger start time - Applies to: GigE and blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncFreeRunTimerStartTimeHigh" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SyncFreeRunTimerStartTimeHigh;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Low 32 bits of the synchronous free run trigger start time - Applies to: GigE and blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncFreeRunTimerStartTimeLow" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SyncFreeRunTimerStartTimeLow;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Synchronous free run trigger rate - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncFreeRunTimerTriggerRateAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SyncFreeRunTimerTriggerRateAbs;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Updates synchronous free run settings - Applies to: GigE and blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncFreeRunTimerUpdate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SyncFreeRunTimerUpdate;

        //@}


        //! \name Categories: DigitalIO
        //@{
        /*!
            \brief Sets the user-settable synchronous output signal to be configured - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selecting Parameters: SyncUserOutputValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncUserOutputSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SyncUserOutputSelectorEnums>& SyncUserOutputSelector;

        //@}


        //! \name Categories: DigitalIO
        //@{
        /*!
            \brief Enables the selected user-settable synchronous output line - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: SyncUserOutputSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncUserOutputValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& SyncUserOutputValue;

        //@}


        //! \name Categories: DigitalIO
        //@{
        /*!
            \brief Single bit field that sets the state of all user-settable synchronous output signals in one access - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SyncUserOutputValueAll" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SyncUserOutputValueAll;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Temperature at the selected location in the camera (in degrees centigrade) - Applies to: CameraLink and GigE

            Temperature at the selected location in the camera (in degrees centigrade). The temperature is measured at the location specified by the Temperature Selector parameter.

            Visibility: Expert

            Selected by: TemperatureSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TemperatureAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TemperatureAbs;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Sets the location in the camera where the temperature will be measured - Applies to: CameraLink and GigE


            Visibility: Expert

            Selecting Parameters: TemperatureAbs

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TemperatureSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TemperatureSelectorEnums>& TemperatureSelector;

        //@}


        //! \name Categories: DeviceControl and DeviceInformation
        //@{
        /*!
            \brief Indicates the temperature state - Applies to: CameraLink, GigE, ace USB and blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TemperatureState" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TemperatureStateEnums>& TemperatureState;

        //@}


        //! \name Categories: TestControl
        //@{
        /*!
            \brief Generates a Test event that can be used for testing event notification - Applies to: ace 2 GigE and ace 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestEventGenerate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TestEventGenerate;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Allows you to turn a moving test image into a fixed one - Applies to: GigE and ace USB

            Allows you to turn a moving test image into a fixed one. The test image will be displayed at its starting position and will stay fixed.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestImageResetAndHold" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& TestImageResetAndHold;

        //@}


        //! \name Categories: ImageFormat and ImageFormatControl
        //@{
        /*!
            \brief Sets the test image to display - Applies to: CamEmu, CameraLink, GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestImageSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TestImageSelectorEnums>& TestImageSelector;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Sets the test pattern to display - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestPattern" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TestPatternEnums>& TestPattern;

        //@}


        //! \name Categories: TestControl
        //@{
        /*!
            \brief Test pending acknowledge time in milliseconds - Applies to: ace 2 GigE, ace 2 USB, dart 2 USB, dart BCON, dart USB and pulse USB

            Test pending acknowledge time in milliseconds. On write, the camera waits for this time period before acknowledging the write. If the time period is longer than the value in the Maximum Device Response Time register, the camera must use PENDING_ACK during the completion of this request. On reads, the camera returns the current value without any additional wait time.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestPendingAck" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TestPendingAck;

        //@}


        //! \name Categories: ImageQualityControl
        //@{
        /*!
            \brief Enables the thermal drift correction - Applies to: blaze

            Activates the correction of the thermal drift.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ThermalDriftCorrection" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ThermalDriftCorrection;

        //@}


        //! \name Categories: CounterAndTimerControl and TimerControl
        //@{
        /*!
            \brief Delay of the currently selected timer in microseconds - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDelay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TimerDelay;

        //@}


        //! \name Categories: TimerControls
        //@{
        /*!
            \brief Delay of the currently selected timer in microseconds - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDelayAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TimerDelayAbs;

        //@}


        //! \name Categories: TimerControls
        //@{
        /*!
            \brief Delay of the selected timer (raw value) - Applies to: CameraLink and GigE

            Delay of the selected timer (raw value). This value will be used as a multiplier for the timer delay timebase. The actual delay time equals the current Timer Delay Raw value multiplied with the current Timer Delay Timebase value.

            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDelayRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TimerDelayRaw;

        //@}


        //! \name Categories: TimerControls
        //@{
        /*!
            \brief Timebase (in microseconds) that is used when a timer delay is specified using the Timer Delay Raw parameter - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDelayTimebaseAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TimerDelayTimebaseAbs;

        //@}


        //! \name Categories: CounterAndTimerControl and TimerControl
        //@{
        /*!
            \brief Duration of the currently selected timer in microseconds - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDuration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TimerDuration;

        //@}


        //! \name Categories: TimerControls
        //@{
        /*!
            \brief Duration of the currently selected timer in microseconds - Applies to: CameraLink and GigE


            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDurationAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TimerDurationAbs;

        //@}


        //! \name Categories: TimerControls
        //@{
        /*!
            \brief Duration of the selected timer (raw value) - Applies to: CameraLink and GigE

            Duration of the selected timer (raw value). This value will be used as a multiplier for the timer duration timebase. The actual duration time equals the current Timer Duration Raw value multiplied with the current Timer Duration Timebase value.

            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDurationRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TimerDurationRaw;

        //@}


        //! \name Categories: TimerControls
        //@{
        /*!
            \brief Timebase (in microseconds) that is used when a timer duration is specified using the Timer Duration Raw parameter - Applies to: CameraLink and GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDurationTimebaseAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TimerDurationTimebaseAbs;

        //@}


        //! \name Categories: TimerControl
        //@{
        /*!
            \brief Resets the selected timer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TimerReset;

        //@}


        //! \name Categories: CounterAndTimerControl, TimerControl and TimerControls
        //@{
        /*!
            \brief Sets the timer to be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selecting Parameters: TimerDelay, TimerDelayAbs, TimerDelayRaw, TimerDuration, TimerDurationAbs, TimerDurationRaw, TimerReset, TimerStatus, TimerTriggerActivation, TimerTriggerArmDelay and TimerTriggerSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TimerSelectorEnums>& TimerSelector;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceCurrentEntryIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TimerSequenceCurrentEntryIndex;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& TimerSequenceEnable;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            Selecting Parameters: TimerSequenceTimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceEntrySelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TimerSequenceEntrySelectorEnums>& TimerSequenceEntrySelector;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceLastEntryIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TimerSequenceLastEntryIndex;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            Selected by: TimerSequenceTimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceTimerDelayRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TimerSequenceTimerDelayRaw;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            Selected by: TimerSequenceTimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceTimerDurationRaw" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TimerSequenceTimerDurationRaw;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            Selected by: TimerSequenceTimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceTimerEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& TimerSequenceTimerEnable;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            Selected by: TimerSequenceTimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceTimerInverter" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& TimerSequenceTimerInverter;

        //@}


        //! \name Categories: TimerSequence
        //@{
        /*!
            \brief  Applies to: CameraLink and GigE


            Visibility: Guru

            Selected by: TimerSequenceEntrySelector

            Selecting Parameters: TimerSequenceTimerDelayRaw, TimerSequenceTimerDurationRaw, TimerSequenceTimerEnable and TimerSequenceTimerInverter

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSequenceTimerSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TimerSequenceTimerSelectorEnums>& TimerSequenceTimerSelector;

        //@}


        //! \name Categories: TimerControl
        //@{
        /*!
            \brief Indicates the status of the currently selected timer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Expert

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TimerStatusEnums>& TimerStatus;

        //@}


        //! \name Categories: TimerControl and TimerControls
        //@{
        /*!
            \brief Sets the type of signal transition that will start the timer - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerTriggerActivation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TimerTriggerActivationEnums>& TimerTriggerActivation;

        //@}


        //! \name Categories: TimerControl
        //@{
        /*!
            \brief Arm delay of the currently selected timer - Applies to: ace 2 GigE, ace 2 USB, boost CoaXPress and dart 2 USB

            Arm delay of the currently selected timer. If an arm delay is set and the timer is triggered, the camera accepts the trigger signal and stops accepting any further timer trigger signals until the arm delay has elapsed.

            Visibility: Expert

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerTriggerArmDelay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TimerTriggerArmDelay;

        //@}


        //! \name Categories: CounterAndTimerControl, TimerControl and TimerControls
        //@{
        /*!
            \brief Sets the internal camera signal used to trigger the selected timer - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            Selected by: TimerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerTriggerSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TimerTriggerSourceEnums>& TimerTriggerSource;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Latches the current timestamp counter and stores its value in TimestampLatchValue - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze and dart 2 USB

            Latches the current timestamp counter and stores its value in the Timestamp Latch Value parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimestampLatch" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TimestampLatch;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Latched value of the timestamp counter - Applies to: ace 2 GigE, ace 2 USB, ace USB, blaze and dart 2 USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimestampLatchValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TimestampLatchValue;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Resets the current timestamp counter - Applies to: ace 2 GigE

            Resets the current timestamp counter. After executing this command, the counter restarts automatically.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimestampReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TimestampReset;

        //@}


        //! \name Categories: TonalRangeControl
        //@{
        /*!
            \brief Sets the operation mode of the Tonal Range Auto auto function - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TonalRangeAuto" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TonalRangeAutoEnums>& TonalRangeAuto;

        //@}


        //! \name Categories: TonalRangeControl
        //@{
        /*!
            \brief Sets whether tonal range adjustment is used - Applies to: GigE and ace USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TonalRangeEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TonalRangeEnableEnums>& TonalRangeEnable;

        //@}


        //! \name Categories: TonalRangeControl
        //@{
        /*!
            \brief Sets which pixel values are used for tonal range adjustments - Applies to: GigE and ace USB


            Visibility: Expert

            Selecting Parameters: TonalRangeSourceBright, TonalRangeSourceDark, TonalRangeTargetBright and TonalRangeTargetDark

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TonalRangeSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TonalRangeSelectorEnums>& TonalRangeSelector;

        //@}


        //! \name Categories: TonalRangeControl
        //@{
        /*!
            \brief Source value for tonal range adjustments at the bright end of the tonal range - Applies to: GigE and ace USB

            Source value for tonal range adjustments at the bright end of the tonal range. When tonal range adjustments are enabled, the source and target values are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            Visibility: Expert

            Selected by: TonalRangeSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TonalRangeSourceBright" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TonalRangeSourceBright;

        //@}


        //! \name Categories: TonalRangeControl
        //@{
        /*!
            \brief Source value for tonal range adjustments at the dark end of the tonal range - Applies to: GigE and ace USB

            Source value for tonal range adjustments at the dark end of the tonal range. When tonal range adjustments are enabled, the source and target values are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            Visibility: Expert

            Selected by: TonalRangeSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TonalRangeSourceDark" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TonalRangeSourceDark;

        //@}


        //! \name Categories: TonalRangeControl
        //@{
        /*!
            \brief Target value at the bright end of the tonal range to which pixel values should be mapped during tonal range adjustments - Applies to: GigE and ace USB

            Target value at the bright end of the tonal range to which pixel values should be mapped during tonal range adjustments. When tonal range adjustments are enabled, the source and target values at the bright end are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            Visibility: Expert

            Selected by: TonalRangeSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TonalRangeTargetBright" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TonalRangeTargetBright;

        //@}


        //! \name Categories: TonalRangeControl
        //@{
        /*!
            \brief Target value at the dark end of the tonal range to which pixel values should be mapped during tonal range adjustments - Applies to: GigE and ace USB

            Target value at the dark end of the tonal range to which pixel values should be mapped during tonal range adjustments. When tonal range adjustments are enabled, the source and target values at the dark end are compared and the tonal range is adjusted accordingly. The kind of adjustment depends on whether you want to adjust color or contrast or both, whether you want to adjust all pixel values or, e.g., only the red pixel values, and so on.

            Visibility: Expert

            Selected by: TonalRangeSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TonalRangeTargetDark" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TonalRangeTargetDark;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the type of signal transition that will activate the selected trigger - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerActivation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerActivationEnums>& TriggerActivation;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Sets the image acquisition control mode - Applies to: CameraLink and GigE

            Sets the image acquisition control mode. For more information, see your camera's product documentation.

            Visibility: Expert

            Selecting Parameters: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerControlImplementation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerControlImplementationEnums>& TriggerControlImplementation;

        //@}


        //! \name Categories: AcquisitionControl
        //@{
        /*!
            \brief Trigger delay time in microseconds - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            Trigger delay time in microseconds. The delay is applied after the trigger has been received and before effectively activating the trigger.

            Visibility: Expert

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerDelay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerDelay;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Trigger delay time in microseconds - Applies to: CameraLink and GigE

            Trigger delay time in microseconds. The delay is applied after the trigger has been received and before effectively activating the trigger.

            Visibility: Expert

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerDelayAbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerDelayAbs;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Trigger delay as number of line triggers - Applies to: CameraLink and GigE

            Trigger delay as a number of consecutive line triggers that are allowed between trigger having been received and before effectively activating the trigger.

            Visibility: Expert

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerDelayLineTriggerCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerDelayLineTriggerCount;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Sets the kind of trigger delay - Applies to: CameraLink and GigE

            Sets whether trigger delay is defined as a time interval or as a number of consecutive line triggers.

            Visibility: Expert

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerDelaySource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerDelaySourceEnums>& TriggerDelaySource;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the mode for the currently selected trigger - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerModeEnums>& TriggerMode;

        //@}


        //! \name Categories: AcquisitionTrigger
        //@{
        /*!
            \brief Determines whether a partial or a complete frame is transmitted when the Frame Start trigger signal transitions prematurely - Applies to: CameraLink and GigE

            Determines whether a partial or a complete frame is transmitted when the Frame Start trigger is used with High or Low states and the trigger signal transitions prematurely.

            Visibility: Expert

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPartialClosingFrame" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& TriggerPartialClosingFrame;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the trigger type to be configured - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Sets the trigger type to be configured. All changes to the trigger settings will be applied to the selected trigger.

            Visibility: Beginner

            Selected by: TriggerControlImplementation

            Selecting Parameters: TriggerActivation, TriggerDelay, TriggerDelayAbs, TriggerDelayLineTriggerCount, TriggerDelaySource, TriggerMode, TriggerPartialClosingFrame, TriggerSoftware and TriggerSource

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerSelectorEnums>& TriggerSelector;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Generates a software trigger signal - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Generates a software trigger signal. The software trigger signal will be used if the Trigger Source parameter is set to Trigger Software.

            Visibility: Beginner

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerSoftware" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TriggerSoftware;

        //@}


        //! \name Categories: AcquisitionControl and AcquisitionTrigger
        //@{
        /*!
            \brief Sets the source signal for the selected trigger - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: TriggerSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerSourceEnums>& TriggerSource;

        //@}


        //! \name Categories: UserDefinedValueControl and UserDefinedValues
        //@{
        /*!
            \brief User-defined value - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB

            User-defined value. The value can serve as storage location for the camera user. It has no impact on the operation of the camera.

            Visibility: Guru

            Selected by: UserDefinedValueSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserDefinedValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& UserDefinedValue;

        //@}


        //! \name Categories: UserDefinedValueControl and UserDefinedValues
        //@{
        /*!
            \brief Sets the user-defined value to set or read - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Guru

            Selecting Parameters: UserDefinedValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserDefinedValueSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<UserDefinedValueSelectorEnums>& UserDefinedValueSelector;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Sets the user-settable output signal to be configured - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB

            Sets the user-settable output signal to be configured. All changes to the user-settable output signal settings will be applied to the selected user-settable output signal.

            Visibility: Beginner

            Selecting Parameters: UserOutputValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserOutputSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<UserOutputSelectorEnums>& UserOutputSelector;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Enables the selected user-settable output line - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON and dart USB


            Visibility: Beginner

            Selected by: UserOutputSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserOutputValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& UserOutputValue;

        //@}


        //! \name Categories: DigitalIO and DigitalIOControl
        //@{
        /*!
            \brief Single bit field that sets the state of all user-settable output signals in one access - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress and dart 2 USB


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserOutputValueAll" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& UserOutputValueAll;

        //@}


        //! \name Categories: DigitalIO
        //@{
        /*!
            \brief Defines a mask that is used when the User Output Value All setting is used to set all of the user settable output signals in one access - Applies to: CameraLink and GigE

            This integer value defines a mask that is used when the User Output Value All setting is used to set all of the user settable output signals in one access.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserOutputValueAllMask" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& UserOutputValueAllMask;

        //@}


        //! \name Categories: UserSetControl
        //@{
        /*!
            \brief Sets the user set or the factory set to be used as the startup set - Applies to: ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Sets the user set or the factory set to be used as the startup set. The startup set will be loaded as the active set whenever the camera is powered on or reset.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetDefault" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<UserSetDefaultEnums>& UserSetDefault;

        //@}


        //! \name Categories: UserSets
        //@{
        /*!
            \brief Sets the user set or the factory set to be used as the startup set - Applies to: CameraLink and GigE

            Sets the user set or the factory set to be used as the startup set. The default startup set will be loaded as the active set whenever the camera is powered on or reset.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetDefaultSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<UserSetDefaultSelectorEnums>& UserSetDefaultSelector;

        //@}


        //! \name Categories: UserSetControl and UserSets
        //@{
        /*!
            \brief Loads the selected set into the camera's volatile memory and makes it the active configuration set - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Loads the selected set into the camera's volatile memory and makes it the active configuration set. After the selected set has been loaded, the parameters in that set will control the camera.

            Visibility: Beginner

            Selected by: UserSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetLoad" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& UserSetLoad;

        //@}


        //! \name Categories: UserSetControl and UserSets
        //@{
        /*!
            \brief Saves the current active set as the selected user set - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selected by: UserSetSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetSave" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& UserSetSave;

        //@}


        //! \name Categories: UserSetControl and UserSets
        //@{
        /*!
            \brief Sets the user set or the factory set to load, save, or configure - Applies to: CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB


            Visibility: Beginner

            Selecting Parameters: UserSetLoad and UserSetSave

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<UserSetSelectorEnums>& UserSetSelector;

        //@}


        //! \name Categories: VirtualInput
        //@{
        /*!
            \brief Sets the length of the input bit - Applies to: CameraLink and GigE

            This integer value sets the length of the input bit in microseconds. It applies to all bits in the signal.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VInpBitLength" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VInpBitLength;

        //@}


        //! \name Categories: VirtualInput
        //@{
        /*!
            \brief Time span between the beginning of the input bit and the time when the high/low status is evaluated - Applies to: CameraLink and GigE

            This integer value sets the time in microseconds that elapses between the beginning of the input bit and the time when the high/low status of the bit is evaluated. It applies to all bits.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VInpSamplingPoint" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VInpSamplingPoint;

        //@}


        //! \name Categories: VirtualInput
        //@{
        /*!
            \brief Selects when to start the signal evaluation - Applies to: CameraLink and GigE

            This enumeration selects when to start the signal evaluation. The camera waits for a rising/falling edge on the input line. When the appropriate signal has been received, the camera starts evaluating the incoming bit patterns. When one bit pattern is finished, the camera waits for the next rising/falling edge to read out the next incoming bit pattern. The camera stops listening once three bits have been received.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VInpSignalReadoutActivation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<VInpSignalReadoutActivationEnums>& VInpSignalReadoutActivation;

        //@}


        //! \name Categories: VirtualInput
        //@{
        /*!
            \brief Sets the I/O line on which the camera receives the virtual input signal - Applies to: CameraLink and GigE

            This enumeration selects the I/O line on which the camera receives the virtual input signal.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VInpSignalSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<VInpSignalSourceEnums>& VInpSignalSource;

        //@}


        //! \name Categories: VignettingCorrectionControl
        //@{
        /*!
            \brief Loads the vignetting correction data - Applies to: GigE and ace USB

            Loads the vignetting correction data into the camera.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VignettingCorrectionLoad" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& VignettingCorrectionLoad;

        //@}


        //! \name Categories: VignettingCorrectionControl
        //@{
        /*!
            \brief Enables/disables the vignetting correction - Applies to: GigE and ace USB

            The Vignetting Correction feature allows you to remove vignetting artifacts from your images. To do this, you first have to create vignetting correction data. For more information, see the Basler Product Documentation.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VignettingCorrectionMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<VignettingCorrectionModeEnums>& VignettingCorrectionMode;

        //@}


        //! \name Categories: VirtualLine1RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Virtual Line 1 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine1RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine1RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: VirtualLine1RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Virtual Line 1 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine1RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine1RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: VirtualLine2RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Virtual Line 2 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine2RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine2RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: VirtualLine2RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Virtual Line 2 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine2RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine2RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: VirtualLine3RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Virtual Line 3 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine3RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine3RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: VirtualLine3RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Virtual Line 3 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine3RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine3RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: VirtualLine4RisingEdgeEventData
        //@{
        /*!
            \brief Stream channel index of the Virtual Line 4 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine4RisingEdgeEventStreamChannelIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine4RisingEdgeEventStreamChannelIndex;

        //@}


        //! \name Categories: VirtualLine4RisingEdgeEventData
        //@{
        /*!
            \brief Timestamp of the Virtual Line 4 Rising Edge event - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VirtualLine4RisingEdgeEventTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VirtualLine4RisingEdgeEventTimestamp;

        //@}


        //! \name Categories: VolatileRowColumnOffset
        //@{
        /*!
            \brief  Applies to: CameraLink


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VolatileColumnOffsetEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& VolatileColumnOffsetEnable;

        //@}


        //! \name Categories: VolatileRowColumnOffset
        //@{
        /*!
            \brief  Applies to: CameraLink


            Visibility: Beginner

            Selecting Parameters: VolatileColumnOffsetValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VolatileColumnOffsetIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VolatileColumnOffsetIndex;

        //@}


        //! \name Categories: VolatileRowColumnOffset
        //@{
        /*!
            \brief  Applies to: CameraLink


            Visibility: Beginner

            Selected by: VolatileColumnOffsetIndex

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VolatileColumnOffsetValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VolatileColumnOffsetValue;

        //@}


        //! \name Categories: VolatileRowColumnOffset
        //@{
        /*!
            \brief  Applies to: CameraLink


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VolatileRowOffsetEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& VolatileRowOffsetEnable;

        //@}


        //! \name Categories: VolatileRowColumnOffset
        //@{
        /*!
            \brief  Applies to: CameraLink


            Visibility: Beginner

            Selecting Parameters: VolatileRowOffsetValue

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VolatileRowOffsetIndex" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VolatileRowOffsetIndex;

        //@}


        //! \name Categories: VolatileRowColumnOffset
        //@{
        /*!
            \brief  Applies to: CameraLink


            Visibility: Beginner

            Selected by: VolatileRowOffsetIndex

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VolatileRowOffsetValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& VolatileRowOffsetValue;

        //@}


        //! \name Categories: AOI and ImageFormatControl
        //@{
        /*!
            \brief Width of the camera's region of interest (area of interest) in pixels - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Width of the camera's region of interest (area of interest) in pixels. Depending on the camera model, the parameter can be set in different increments.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Width" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Width;

        //@}


        //! \name Categories: AOI, DeviceInformation and ImageFormatControl
        //@{
        /*!
            \brief Maximum width of the region of interest (area of interest) in pixels - Applies to: CamEmu, CameraLink, GigE, ace 2 GigE, ace 2 USB, ace USB, blaze, boost CoaXPress, dart 2 USB, dart BCON, dart USB and pulse USB

            Maximum width of the region of interest (area of interest) in pixels. The value takes into account any function that may limit the maximum width.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=WidthMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& WidthMax;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Maximum working range of the camera - Applies to: blaze

            Maximum working range of the camera. Beyond this, results will be ambguous.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=WorkingRangeMax" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& WorkingRangeMax;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Minimum working range of the camera - Applies to: blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=WorkingRangeMin" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& WorkingRangeMin;

        //@}


        //! \name Categories: Scan3dControl
        //@{
        /*!
            \brief Distance between the origin of the z axis to the front of the camera housing - Applies to: blaze

            Distance between the origin of the z axis to the front of the camera housing. Due to mechanical tolerances, this offset is device-specific and needs to be taken into account when measuring absolute distances.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ZOffsetOriginToCameraFront" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ZOffsetOriginToCameraFront;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalCameraParams_Params_v6_2_0(CUniversalCameraParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CUniversalCameraParams_Params_v6_2_0& operator=(CUniversalCameraParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for Basler camera devices

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class CUniversalCameraParams_Params : public CUniversalCameraParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalCameraParams_Params( void )
        {
        }

        //! Destructor
        ~CUniversalCameraParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CUniversalCameraParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalCameraParams

#endif // BASLER_PYLON_UNIVERSALCAMERAPARAMS_H
