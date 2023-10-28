//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for pylon device transport layers

The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_UNIVERSALTLPARAMS_H
#define BASLER_PYLON_UNIVERSALTLPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_UniversalTLParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for AreaTriggerMode
    enum AreaTriggerModeEnums
    {
        AreaTriggerMode_External,  //!< The trigger mode is set to External - Applies to: CoaXPress
        AreaTriggerMode_Generator,  //!< The trigger mode is set to Generator - Applies to: CoaXPress
        AreaTriggerMode_Software  //!< The trigger mode is set to Software - Applies to: CoaXPress
    };

    //! Valid values for BitAlignment
    enum BitAlignmentEnums
    {
        BitAlignment_CustomBitShift,  //!< The bits are shifted by a user-defined value - Applies to: CoaXPress
        BitAlignment_LeftAligned,  //!< The bits left-aligned   - Applies to: CoaXPress
        BitAlignment_RightAligned  //!< The bits right-aligned   - Applies to: CoaXPress
    };

    //! Valid values for DeviceAccessStatus
    enum DeviceAccessStatusEnums
    {
        DeviceAccessStatus_Busy,  //!< The device is already opened by another entity - Applies to: CoaXPress and blaze
        DeviceAccessStatus_NoAccess,  //!< You can't connect to the device - Applies to: CoaXPress and blaze
        DeviceAccessStatus_OpenReadOnly,  //!< The device is opened in Read-only mode by this GenTL host - Applies to: CoaXPress and blaze
        DeviceAccessStatus_OpenReadWrite,  //!< The device is opened in Read/Write mode by this GenTL host - Applies to: CoaXPress and blaze
        DeviceAccessStatus_ReadOnly,  //!< The device offers read-only access - Applies to: CoaXPress and blaze
        DeviceAccessStatus_ReadWrite,  //!< The device offers read/write access - Applies to: CoaXPress and blaze
        DeviceAccessStatus_Unknown  //!< The status is unknown - Applies to: CoaXPress and blaze
    };

    //! Valid values for DeviceEndianessMechanism
    enum DeviceEndianessMechanismEnums
    {
        DeviceEndianessMechanism_Legacy,  //!< The device endianness is handled according to GenICam Schema 1 0 - Applies to: blaze
        DeviceEndianessMechanism_Standard  //!< The device endianness is handled according to GenICam Schema 1 1 and later - Applies to: blaze
    };

    //! Valid values for DeviceType
    enum DeviceTypeEnums
    {
        DeviceType_CL,  //!< The device uses the Camera Link transport layer - Applies to: CoaXPress
        DeviceType_CLHS,  //!< The device uses the Camera Link HS transport layer - Applies to: CoaXPress
        DeviceType_CXP,  //!< The device uses the CoaXPress transport layer - Applies to: CoaXPress
        DeviceType_Custom,  //!< The device uses a custom transport layer - Applies to: CoaXPress
        DeviceType_GEV,  //!< The device uses the GigE Vision transport layer - Applies to: CoaXPress
        DeviceType_Mixed,  //!< Different interface modules of the GenTL Producer are of different types - Applies to: CoaXPress
        DeviceType_U3V  //!< The device uses the USB3 Vision transport layer - Applies to: CoaXPress
    };

    //! Valid values for EventNotification
    enum EventNotificationEnums
    {
        EventNotification_Off,  //!< The selected Event notification is disabled - Applies to: CoaXPress and blaze
        EventNotification_On,  //!< The selected Event notification is enabled - Applies to: CoaXPress and blaze
        EventNotification_Once  //!< The selected Event notification is enabled for one event then return to Off state - Applies to: CoaXPress and blaze
    };

    //! Valid values for EventSelector
    enum EventSelectorEnums
    {
        EventSelector_DeviceLost  //!< Selects the Device Lost Event - Applies to: CoaXPress and blaze
    };

    //! Valid values for Format
    enum FormatEnums
    {
        Format_BGR10p,  //!< The pixel output format is set to BGR10p - Applies to: CoaXPress
        Format_BGR12p,  //!< The pixel output format is set to BGR12p - Applies to: CoaXPress
        Format_BGR16,  //!< The pixel output format is set to BGR16 - Applies to: CoaXPress
        Format_BGR8,  //!< The pixel output format is set to BGR8 - Applies to: CoaXPress
        Format_BayerBG10p,  //!< The pixel output format is set to BayerBG10p - Applies to: CoaXPress
        Format_BayerBG12p,  //!< The pixel output format is set to BayerBG12p - Applies to: CoaXPress
        Format_BayerBG16,  //!< The pixel output format is set to BayerBG16 - Applies to: CoaXPress
        Format_BayerBG8,  //!< The pixel output format is set to BayerBG8 - Applies to: CoaXPress
        Format_BayerGB10p,  //!< The pixel output format is set to BayerGB10p - Applies to: CoaXPress
        Format_BayerGB12p,  //!< The pixel output format is set to BayerGB12p - Applies to: CoaXPress
        Format_BayerGB16,  //!< The pixel output format is set to BayerGB16 - Applies to: CoaXPress
        Format_BayerGB8,  //!< The pixel output format is set to BayerGB8 - Applies to: CoaXPress
        Format_BayerGR10p,  //!< The pixel output format is set to BayerGR10p - Applies to: CoaXPress
        Format_BayerGR12p,  //!< The pixel output format is set to BayerGR12p - Applies to: CoaXPress
        Format_BayerGR16,  //!< The pixel output format is set to BayerGR16 - Applies to: CoaXPress
        Format_BayerGR8,  //!< The pixel output format is set to BayerGR8 - Applies to: CoaXPress
        Format_BayerRG10p,  //!< The pixel output format is set to BayerRG10p - Applies to: CoaXPress
        Format_BayerRG12p,  //!< The pixel output format is set to BayerRG12p - Applies to: CoaXPress
        Format_BayerRG16,  //!< The pixel output format is set to BayerRG16 - Applies to: CoaXPress
        Format_BayerRG8,  //!< The pixel output format is set to BayerRG8 - Applies to: CoaXPress
        Format_Mono10p,  //!< The pixel output format is set to Mono10p - Applies to: CoaXPress
        Format_Mono12p,  //!< The pixel output format is set to Mono12p - Applies to: CoaXPress
        Format_Mono16,  //!< The pixel output format is set to Mono16 - Applies to: CoaXPress
        Format_Mono8,  //!< The pixel output format is set to Mono8 - Applies to: CoaXPress
        Format_YCbCr422_8  //!< The pixel output format is set to YCbCr422_8 - Applies to: CoaXPress
    };

    //! Valid values for PixelFormat
    enum PixelFormatEnums
    {
        PixelFormat_BayerBG10p,  //!< The pixel format is set to BayerBG10 - Applies to: CoaXPress
        PixelFormat_BayerBG12p,  //!< The pixel format is set to BayerBG12 - Applies to: CoaXPress
        PixelFormat_BayerBG8,  //!< The pixel format is set to BayerBG8 - Applies to: CoaXPress
        PixelFormat_BayerGB10p,  //!< The pixel format is set to BayerGB10 - Applies to: CoaXPress
        PixelFormat_BayerGB12p,  //!< The pixel format is set to BayerGB12 - Applies to: CoaXPress
        PixelFormat_BayerGB8,  //!< The pixel format is set to BayerGB8 - Applies to: CoaXPress
        PixelFormat_BayerGR10p,  //!< The pixel format is set to BayerGR10 - Applies to: CoaXPress
        PixelFormat_BayerGR12p,  //!< The pixel format is set to BayerGR12 - Applies to: CoaXPress
        PixelFormat_BayerGR8,  //!< The pixel format is set to BayerGR8 - Applies to: CoaXPress
        PixelFormat_BayerRG10p,  //!< The pixel format is set to BayerRG10 - Applies to: CoaXPress
        PixelFormat_BayerRG12p,  //!< The pixel format is set to BayerRG12 - Applies to: CoaXPress
        PixelFormat_BayerRG8,  //!< The pixel format is set to BayerRG8 - Applies to: CoaXPress
        PixelFormat_Mono10,  //!< The pixel format is set to Mono10 - Applies to: CoaXPress
        PixelFormat_Mono12,  //!< The pixel format is set to Mono12 - Applies to: CoaXPress
        PixelFormat_Mono8,  //!< The pixel format is set to Mono8 - Applies to: CoaXPress
        PixelFormat_RGB10p,  //!< The pixel format is set to RGB10 - Applies to: CoaXPress
        PixelFormat_RGB12p,  //!< The pixel format is set to RGB12 - Applies to: CoaXPress
        PixelFormat_RGB8,  //!< The pixel format is set to RGB8 - Applies to: CoaXPress
        PixelFormat_YCbCr422_8  //!< The pixel format is set to YCbCr422_8 - Applies to: CoaXPress
    };

    //! Valid values for SoftwareTriggerIsBusy
    enum SoftwareTriggerIsBusyEnums
    {
        SoftwareTriggerIsBusy_Busy,  //!< The software trigger is busy - Applies to: CoaXPress
        SoftwareTriggerIsBusy_NotBusy  //!< The software trigger is not busy - Applies to: CoaXPress
    };

    //! Valid values for SystemmonitorByteAlignment8b10bLocked
    enum SystemmonitorByteAlignment8b10bLockedEnums
    {
        SystemmonitorByteAlignment8b10bLocked_No,  //!< No - Applies to: CoaXPress
        SystemmonitorByteAlignment8b10bLocked_Yes  //!< Yes - Applies to: CoaXPress
    };

    //! Valid values for SystemmonitorExternalPower
    enum SystemmonitorExternalPowerEnums
    {
        SystemmonitorExternalPower_NoPower,  //!< No power - Applies to: CoaXPress
        SystemmonitorExternalPower_PowerGood  //!< Power is ok - Applies to: CoaXPress
    };

    //! Valid values for SystemmonitorPowerOverCxpState
    enum SystemmonitorPowerOverCxpStateEnums
    {
        SystemmonitorPowerOverCxpState_PoCXPADCChipError,  //!< ADC Chip Error - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPBooting,  //!< Booting, not initalized - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPDisabled,  //!< No Power over CXP - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPLowVolt,  //!< Low voltage - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPMaxCurrent,  //!< Maximum current - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPMinCurrent,  //!< Minimum current - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPNotConnected,  //!< No cable connected - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPOK,  //!< Power over CXP OK - Applies to: CoaXPress
        SystemmonitorPowerOverCxpState_PoCXPOverVolt  //!< Over voltage - Applies to: CoaXPress
    };

    //! Valid values for TriggerCameraOutSelect
    enum TriggerCameraOutSelectEnums
    {
        TriggerCameraOutSelect_BypassFrontGPI0,  //!< The output source is set to BypassFrontGPI0 - Applies to: CoaXPress
        TriggerCameraOutSelect_BypassFrontGPI1,  //!< The output source is set to BypassFrontGPI1 - Applies to: CoaXPress
        TriggerCameraOutSelect_BypassFrontGPI2,  //!< The output source is set to BypassFrontGPI2 - Applies to: CoaXPress
        TriggerCameraOutSelect_BypassFrontGPI3,  //!< The output source is set to BypassFrontGPI3 - Applies to: CoaXPress
        TriggerCameraOutSelect_CamAPulseGenerator0,  //!< The output source is set to CamAPulseGenerator0 - Applies to: CoaXPress
        TriggerCameraOutSelect_CamAPulseGenerator1,  //!< The output source is set to CamAPulseGenerator1 - Applies to: CoaXPress
        TriggerCameraOutSelect_CamAPulseGenerator2,  //!< The output source is set to CamAPulseGenerator2 - Applies to: CoaXPress
        TriggerCameraOutSelect_CamAPulseGenerator3,  //!< The output source is set to CamAPulseGenerator3 - Applies to: CoaXPress
        TriggerCameraOutSelect_GND,  //!< The output source is set to GND - Applies to: CoaXPress
        TriggerCameraOutSelect_NotBypassFronGPI0,  //!< The output source is set to NotBypassFrontGPI0 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotBypassFronGPI1,  //!< The output source is set to NotBypassFrontGPI1 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotBypassFronGPI2,  //!< The output source is set to NotBypassFrontGPI2 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotBypassFronGPI3,  //!< The output source is set to NotBypassFrontGPI3 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotCamAPulseGenerator0,  //!< The output source is set to NotCamAPulseGenerator0 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotCamAPulseGenerator1,  //!< The output source is set to NotCamAPulseGenerator1 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotCamAPulseGenerator2,  //!< The output source is set to NotCamAPulseGenerator2 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotCamAPulseGenerator3,  //!< The output source is set to NotCamAPulseGenerator3 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotPulseGenerator0,  //!< The output source is set to NotPulseGenerator0 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotPulseGenerator1,  //!< The output source is set to NotPulseGenerator1 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotPulseGenerator2,  //!< The output source is set to NotPulseGenerator2 - Applies to: CoaXPress
        TriggerCameraOutSelect_NotPulseGenerator3,  //!< The output source is set to NotPulseGenerator3 - Applies to: CoaXPress
        TriggerCameraOutSelect_PulseGenerator0,  //!< The output source is set to PulseGenerator0 - Applies to: CoaXPress
        TriggerCameraOutSelect_PulseGenerator1,  //!< The output source is set to PulseGenerator1 - Applies to: CoaXPress
        TriggerCameraOutSelect_PulseGenerator2,  //!< The output source is set to PulseGenerator2 - Applies to: CoaXPress
        TriggerCameraOutSelect_PulseGenerator3,  //!< The output source is set to PulseGenerator3 - Applies to: CoaXPress
        TriggerCameraOutSelect_VCC  //!< The output source is set to VCC - Applies to: CoaXPress
    };

    //! Valid values for TriggerInPolarity
    enum TriggerInPolarityEnums
    {
        TriggerInPolarity_HighActive,  //!< The polarity is set to HighActive - Applies to: CoaXPress
        TriggerInPolarity_LowActive  //!< The polarity is set to LowActive - Applies to: CoaXPress
    };

    //! Valid values for TriggerInSource
    enum TriggerInSourceEnums
    {
        TriggerInSource_TriggerInSourceFrontGPI0,  //!< The trigger input source is set to TriggerInSourceFrontGPI0 - Applies to: CoaXPress
        TriggerInSource_TriggerInSourceFrontGPI1,  //!< The trigger input source is set to TriggerInSourceFrontGPI1 - Applies to: CoaXPress
        TriggerInSource_TriggerInSourceFrontGPI2,  //!< The trigger input source is set to TriggerInSourceFrontGPI2 - Applies to: CoaXPress
        TriggerInSource_TriggerInSourceFrontGPI3  //!< The trigger input source is set to TriggerInSourceFrontGPI3 - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectFrontGPO0
    enum TriggerOutSelectFrontGPO0Enums
    {
        TriggerOutSelectFrontGPO0_BypassFrontGPI0,  //!< The output source is set to BypassFrontGPI0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassFrontGPI1,  //!< The output source is set to BypassFrontGPI1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassFrontGPI2,  //!< The output source is set to BypassFrontGPI2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassFrontGPI3,  //!< The output source is set to BypassFrontGPI3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator0,  //!< The output source is set to CamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator1,  //!< The output source is set to CamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator2,  //!< The output source is set to CamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator3,  //!< The output source is set to CamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_GND,  //!< The output source is set to GND - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI0,  //!< The output source is set to NotBypassFrontGPI0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI1,  //!< The output source is set to NotBypassFrontGPI1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI2,  //!< The output source is set to NotBypassFrontGPI2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI3,  //!< The output source is set to NotBypassFrontGPI3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator0,  //!< The output source is set to NotCamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator1,  //!< The output source is set to NotCamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator2,  //!< The output source is set to NotCamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator3,  //!< The output source is set to NotCamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotPulseGenerator0,  //!< The output source is set to NotPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotPulseGenerator1,  //!< The output source is set to NotPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotPulseGenerator2,  //!< The output source is set to NotPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotPulseGenerator3,  //!< The output source is set to NotPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_PulseGenerator0,  //!< The output source is set to PulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_PulseGenerator1,  //!< The output source is set to PulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_PulseGenerator2,  //!< The output source is set to PulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_PulseGenerator3,  //!< The output source is set to PulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_VCC  //!< The output source is set to VCC - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectFrontGPO1
    enum TriggerOutSelectFrontGPO1Enums
    {
        TriggerOutSelectFrontGPO1_BypassFrontGPI0,  //!< The output source is set to BypassFrontGPI0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassFrontGPI1,  //!< The output source is set to BypassFrontGPI1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassFrontGPI2,  //!< The output source is set to BypassFrontGPI2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassFrontGPI3,  //!< The output source is set to BypassFrontGPI3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator0,  //!< The output source is set to CamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator1,  //!< The output source is set to CamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator2,  //!< The output source is set to CamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator3,  //!< The output source is set to CamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_GND,  //!< The output source is set to GND - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI0,  //!< The output source is set to NotBypassFrontGPI0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI1,  //!< The output source is set to NotBypassFrontGPI1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI2,  //!< The output source is set to NotBypassFrontGPI2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI3,  //!< The output source is set to NotBypassFrontGPI3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator0,  //!< The output source is set to NotCamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator1,  //!< The output source is set to NotCamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator2,  //!< The output source is set to NotCamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator3,  //!< The output source is set to NotCamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotPulseGenerator0,  //!< The output source is set to NotPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotPulseGenerator1,  //!< The output source is set to NotPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotPulseGenerator2,  //!< The output source is set to NotPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotPulseGenerator3,  //!< The output source is set to NotPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_PulseGenerator0,  //!< The output source is set to PulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_PulseGenerator1,  //!< The output source is set to PulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_PulseGenerator2,  //!< The output source is set to PulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_PulseGenerator3,  //!< The output source is set to PulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_VCC  //!< The output source is set to VCC - Applies to: CoaXPress
    };

    //! Valid values for TriggerQueueMode
    enum TriggerQueueModeEnums
    {
        TriggerQueueMode_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        TriggerQueueMode_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for TriggerState
    enum TriggerStateEnums
    {
        TriggerState_Active,  //!< The trigger state is set to Active - Applies to: CoaXPress
        TriggerState_AsyncStop,  //!< The trigger state is set to AsyncStop - Applies to: CoaXPress
        TriggerState_SyncStop  //!< The trigger state is set to SyncStop - Applies to: CoaXPress
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalTLParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for pylon device transport layers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class PYLONBASE_API CUniversalTLParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalTLParams_Params_v6_2_0( void );

        //! Destructor
        ~CUniversalTLParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalTLParams_Params_v6_2_0_Data;
        CUniversalTLParams_Params_v6_2_0_Data* m_pCUniversalTLParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: Trigger
        //@{
        /*!
            \brief Sets the trigger mode of the area trigger signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AreaTriggerMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AreaTriggerModeEnums>& AreaTriggerMode;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Enables/disables automatic control of the pixel format in the device - Applies to: CoaXPress

            Enables/disables automatic control of the pixel format in the device. If enabled, the frame grabber's pixel format and its dependencies are automatically updated to match the camera's pixel format setting.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutomaticFormatControl" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutomaticFormatControl;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief Sets the alignment of the bits in the output format - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BitAlignment" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BitAlignmentEnums>& BitAlignment;

        //@}


        //! \name Categories: ExtendedDeviceControl and Root
        //@{
        /*!
            \brief Enables sending all commands and receiving all acknowledges twice - Applies to: GigE and blaze

            Enables sending all commands and receiving all acknowledges twice. This option should only be enabled in case of network problems.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CommandDuplicationEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& CommandDuplicationEnable;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief User-defined bit shift to the right - Applies to: CoaXPress

            User-defined bit shift to the right. This allows you to shift the pixel data in the output format to the right by a value of your choice. The Alignment parameter has to be set to CustomBitShift for this.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CustomBitShiftRight" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CustomBitShiftRight;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Returns the device's access status at the moment when the Device Update List command was last executed - Applies to: CoaXPress and blaze

            Returns the device's access status at the moment when the Device Update List command was last executed. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceAccessStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceAccessStatusEnums>& DeviceAccessStatus;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief User-friendly name of the device - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceDisplayName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceDisplayName;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Sets the endianness handling mode - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceEndianessMechanism" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceEndianessMechanismEnums>& DeviceEndianessMechanism;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Interface-wide unique ID of the selected device - Applies to: CoaXPress and blaze

            Interface-wide unique ID of the selected device. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceID;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Additional information about the manufacturer of the device - Applies to: blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManufacturerInfo" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceManufacturerInfo;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Name of the device model - Applies to: CoaXPress and blaze

            Name of the device model. This value only changes when the Device Update List command is executed.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceModelName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceModelName;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Serial number of the remote device - Applies to: blaze

            Serial number of the remote device. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSerialNumber" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceSerialNumber;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Returns the transport layer of the device - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceType" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceTypeEnums>& DeviceType;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Name of the device vendor - Applies to: CoaXPress and blaze

            Name of the device vendor. This value only changes when the Device Update List command is executed.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceVendorName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceVendorName;

        //@}


        //! \name Categories: EventDeviceLostData
        //@{
        /*!
            \brief Returns the unique Identifier of the Device Lost type of Event - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventDeviceLost" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventDeviceLost;

        //@}


        //! \name Categories: EventControl
        //@{
        /*!
            \brief Activate or deactivate the notification to the host application of the occurrence of the selected Event - Applies to: CoaXPress and blaze


            Visibility: Expert

            Selected by: EventSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventNotification" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<EventNotificationEnums>& EventNotification;

        //@}


        //! \name Categories: EventControl
        //@{
        /*!
            \brief Selects which Event to signal to the host application - Applies to: CoaXPress and blaze


            Visibility: Expert

            Selecting Parameters: EventNotification

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<EventSelectorEnums>& EventSelector;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Current buffer fill level - Applies to: CoaXPress

            Current buffer fill level. This value allows you to check whether the average input bandwidth of the camera is too high to be processed by the applet.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FillLevel" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FillLevel;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief Sets the pixel format of the image that is output to the computer - Applies to: CoaXPress

            Sets the pixel format of the image that is output to the computer. The data is converted from the internal bit width and color format to the output format selected. This setting is not related to the pixel format input from the camera sensor. For more information, see the Pixel Format parameter documentation.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Format" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FormatEnums>& Format;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Current input signal levels of all front GPI inputs (bit mask) - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrontGPI" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrontGPI;

        //@}


        //! \name Categories: Gentl
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Ignore the FG output format and manage it internally in the GenTL producer

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GentlInfoIgnorefgformat" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& GentlInfoIgnorefgformat;

        //@}


        //! \name Categories: Gentl
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Version of the GenTL description Interface in the applet.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GentlInfoVersion" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& GentlInfoVersion;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Current gateway IP address of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceGateway" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceGateway;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Current IP address of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceIPAddress" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceIPAddress;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief 48-bit MAC address of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceMACAddress" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceMACAddress;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Current subnet mask of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceSubnetMask" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceSubnetMask;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Heartbeat timeout value on the host side in milliseconds - Applies to: GigE

            Heartbeat timeout value on the host side in milliseconds. This parameter is linked with the Heartbeat Timeout camera parameter. If the camera parameter changes, the host parameter changes accordingly, and vice versa.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=HeartbeatTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& HeartbeatTimeout;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Specifies maximum number of tries before failing the control channel commands - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LinkCommandRetryCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LinkCommandRetryCount;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Specifies application timeout for the control channel communication - Applies to: blaze

            Specifies application timeout for the control channel communication. Up to DeviceLinkCommandRetryCount attempts with this timeout are made before a command fails with a timeout error.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LinkCommandTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LinkCommandTimeout;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum number of retries for read operations after a read operation has timed out - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxRetryCountRead" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaxRetryCountRead;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum number of retries for write operations after a write operation has timed out - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxRetryCountWrite" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaxRetryCountWrite;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Enables mapping of certain SFNC 1 x node names to SFNC 2 x node names - Applies to: GigE and USB

            Enables mapping of certain SFNC 1.x node names to SFNC 2.x node names. This allows you to write code for camera devices that are compatible with different SFNC (Standard Features Naming Convention) versions. Available for USB camera devices only.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MigrationModeEnable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& MigrationModeEnable;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Automatically outputs packed formats instead of unpacked ones - Applies to: CoaXPress

            Automatically outputs packed formats instead of unpacked ones. This parameter is only available if the Automatic Format Control parameter is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OutputPackedFormats" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& OutputPackedFormats;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Indicates whether the image buffer is currently in overflow state - Applies to: CoaXPress

            Indicates whether if the image buffer is currently in overflow state. An overflow results in the loss of images. The parameter is reset at each readout cycle.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Overflow" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Overflow;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief Applet-internal processing bit depth - Applies to: CoaXPress

            Applet-internal processing bit depth. This is the maximum bit depth at which pixels are processed. If you select a highter output and input bit depth, data may be truncated.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelDepth" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PixelDepth;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets the format of the pixel data transmitted by the camera - Applies to: CoaXPress

            Sets the format of the pixel data transmitted by the camera. This setting has to match the pixel format set in the camera.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelFormat" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PixelFormatEnums>& PixelFormat;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Read access timeout value in milliseconds - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReadTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ReadTimeout;

        //@}


        //! \name Categories: SoftwareTrigger
        //@{
        /*!
            \brief Sends a software trigger pulse - Applies to: CoaXPress

            Sends a software trigger pulse or adds pulses to the trigger queue if it is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SendSoftwareTrigger" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SendSoftwareTrigger;

        //@}


        //! \name Categories: SoftwareTrigger
        //@{
        /*!
            \brief Indicates whether the software trigger is busy - Applies to: CoaXPress

            Indicates whether the software trigger is busy. This allows you to find out whether the trigger system is still processing software trigger pulses.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareTriggerIsBusy" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SoftwareTriggerIsBusyEnums>& SoftwareTriggerIsBusy;

        //@}


        //! \name Categories: SoftwareTrigger
        //@{
        /*!
            \brief Number of pulses in queue to be processed - Applies to: CoaXPress

            Number of pulses in queue to be processed. The Queue parameter needs to be enabled for this.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareTriggerQueueFillLevel" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SoftwareTriggerQueueFillLevel;

        //@}


        //! \name Categories: ExtendedDeviceControl and Root
        //@{
        /*!
            \brief Number of timeouts during read and write operations when waiting for a response from the device - Applies to: GigE and blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StatisticReadWriteTimeoutCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StatisticReadWriteTimeoutCount;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Last error status of a read or write operation - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Error_Status" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Last_Error_Status;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Last error status of a read or write operation - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Error_Status_Text" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& Statistic_Last_Error_Status_Text;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of failed read operations - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Read_Operations_Failed_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Read_Operations_Failed_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of read pipe resets - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Read_Pipe_Reset_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Read_Pipe_Reset_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of failed write operations - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Write_Operations_Failed_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Write_Operations_Failed_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of write pipe resets - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Write_Pipe_Reset_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Write_Pipe_Reset_Count;

        //@}


        //! \name Categories: StreamEnumeration
        //@{
        /*!
            \brief User-friendly name of the selected stream - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamDisplayName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& StreamDisplayName;

        //@}


        //! \name Categories: StreamEnumeration
        //@{
        /*!
            \brief Device-wide unique ID of the data stream - Applies to: CoaXPress and blaze


            Visibility: Beginner

            Selected by: StreamSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& StreamID;

        //@}


        //! \name Categories: StreamEnumeration
        //@{
        /*!
            \brief Sets the stream channel - Applies to: CoaXPress and blaze

            Sets the stream channel. The selector is 0-based in order to match the index of the C interface.

            Visibility: Beginner

            Selecting Parameters: StreamID

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamSelector;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Byte Alignment 8b10b locked

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorByteAlignment8b10bLocked" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SystemmonitorByteAlignment8b10bLockedEnums>& SystemmonitorByteAlignment8b10bLocked;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the Channel Current.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelCurrent" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorChannelCurrent;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelCurrentSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorChannelCurrentSelector;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the Channel Voltage.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelVoltage" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorChannelVoltage;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelVoltageSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorChannelVoltageSelector;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current PCIe link speed in Gibibyte (2^30 byte).

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorCurrentLinkSpeed" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorCurrentLinkSpeed;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Disparity 8b 10b errors

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorDisparity8b10bError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorDisparity8b10bError;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Shows the external power state of the board.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorExternalPower" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SystemmonitorExternalPowerEnums>& SystemmonitorExternalPower;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA die temperature.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaTemperature;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA auxiliary Vcc.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaVccAux" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaVccAux;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA BRAM Vcc.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaVccBram" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaVccBram;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA internal Vcc.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaVccInt" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaVccInt;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Not in table 8b 10b errors

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorNotInTable8b10bError" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorNotInTable8b10bError;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the PCIe trained payload size.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPcieTrainedPayloadSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorPcieTrainedPayloadSize;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the PCIe trained request size.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPcieTrainedRequestSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorPcieTrainedRequestSize;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the port bit rate

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPortBitRate" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorPortBitRate;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Shows the current power over CXP state.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPowerOverCxpState" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SystemmonitorPowerOverCxpStateEnums>& SystemmonitorPowerOverCxpState;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of trigger acknowledgement packets sent by the camera have been received by the frame grabber - Applies to: CoaXPress

            Number of trigger acknowledgement packets sent by the camera (in response to trigger edge packets sent before) have been received by the frame grabber.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerAcknowledgementCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerAcknowledgementCount;

        //@}


        //! \name Categories: CameraOutSignalMapping
        //@{
        /*!
            \brief Sets the output source to be connected to a camera signal channel - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerCameraOutSelect" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerCameraOutSelectEnums>& TriggerCameraOutSelect;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of trigger events sent to the camera - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerEventCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerEventCount;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Input debounce time for trigger input signals (in microseconds) - Applies to: CoaXPress

            Input debounce time for trigger input signals (in microseconds). This parameter allows you to filter out invalid signals by specifying a minimum signal length.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInDebounce" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerInDebounce;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Factor by which the trigger input signal is downscaled - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInDownscale" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerInDownscale;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInDownscalePhase" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerInDownscalePhase;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Sets the polarity of the trigger input signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInPolarity" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerInPolarityEnums>& TriggerInPolarity;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Sets the trigger input source - Applies to: CoaXPress

            Sets the trigger input source for external trigger mode.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInSource" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerInSourceEnums>& TriggerInSource;

        //@}


        //! \name Categories: Sequencer
        //@{
        /*!
            \brief Upscales, i e , duplicates, the number of trigger pulses generated externally or via software with the period specified by the Trigger Output Frequency parameter - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerMultiplyPulses" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerMultiplyPulses;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of Front GPO 0 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectFrontGPO0" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectFrontGPO0Enums>& TriggerOutSelectFrontGPO0;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of front GPO 1 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectFrontGPO1" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectFrontGPO1Enums>& TriggerOutSelectFrontGPO1;

        //@}


        //! \name Categories: Trigger
        //@{
        /*!
            \brief Maximum trigger output frequency - Applies to: CoaXPress

            Maximum trigger output frequency. If the internal generator is used, it will use the frequency specified there. If an external source is used, this value determines the maximum allowed value. External trigger signals exceeding this value will be discarded. For more information, see the applet documentation.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutputFrequency" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerOutputFrequency;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0Delay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator0Delay;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0Downscale" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator0Downscale;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0DownscalePhase" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator0DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0Width" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator0Width;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1Delay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator1Delay;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1Downscale" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator1Downscale;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1DownscalePhase" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator1DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1Width" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator1Width;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2Delay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator2Delay;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2Downscale" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator2Downscale;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2DownscalePhase" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator2DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2Width" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator2Width;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3Delay" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator3Delay;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3Downscale" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator3Downscale;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3DownscalePhase" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator3DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3Width" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator3Width;

        //@}


        //! \name Categories: Queue
        //@{
        /*!
            \brief Fill level of the trigger queue - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerQueueFillLevel" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerQueueFillLevel;

        //@}


        //! \name Categories: Queue
        //@{
        /*!
            \brief Enables/disable the trigger queue mode - Applies to: CoaXPress

            Enables/disable the trigger queue mode. The maximum output frequenc is specified by the Trigger Output Frequency parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerQueueMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerQueueModeEnums>& TriggerQueueMode;

        //@}


        //! \name Categories: Trigger
        //@{
        /*!
            \brief Sets the state of the trigger system - Applies to: CoaXPress

            Sets the state of the trigger system. The state of the trigger system is related to the trigger mode. This parameter enables or disables the trigger processing.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerState" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerStateEnums>& TriggerState;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Indicates a trigger frequency violation - Applies to: CoaXPress

            Indicates a distance of two trigger edges violating the minimum edge frequency.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerWaveViolation" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerWaveViolation;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Write access timeout in milliseconds - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=WriteTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& WriteTimeout;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalTLParams_Params_v6_2_0(CUniversalTLParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CUniversalTLParams_Params_v6_2_0& operator=(CUniversalTLParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for pylon device transport layers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class CUniversalTLParams_Params : public CUniversalTLParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalTLParams_Params( void )
        {
        }

        //! Destructor
        ~CUniversalTLParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CUniversalTLParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalTLParams

#endif // BASLER_PYLON_UNIVERSALTLPARAMS_H
