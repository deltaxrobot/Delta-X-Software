//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2024 Basler AG
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
        AreaTriggerMode_Software,  //!< The trigger mode is set to Software - Applies to: CoaXPress
        AreaTriggerMode_Synchronized  //!< The trigger mode is set to Synchronized - Applies to: CoaXPress
    };

    //! Valid values for BitAlignment
    enum BitAlignmentEnums
    {
        BitAlignment_CustomBitShift,  //!< The bits are shifted by a user-defined value - Applies to: CoaXPress
        BitAlignment_LeftAligned,  //!< The bits left-aligned   - Applies to: CoaXPress
        BitAlignment_RightAligned  //!< The bits right-aligned   - Applies to: CoaXPress
    };

    //! Valid values for CustomSignalEvent0Polarity
    enum CustomSignalEvent0PolarityEnums
    {
        CustomSignalEvent0Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        CustomSignalEvent0Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for CustomSignalEvent0Source
    enum CustomSignalEvent0SourceEnums
    {
        CustomSignalEvent0Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1FrameEnd,  //!< The frame end signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1FrameStart,  //!< The frame start signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1LineEnd,  //!< The line end signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1LineStart,  //!< The line start signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2FrameEnd,  //!< The frame end signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2FrameStart,  //!< The frame start signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2LineEnd,  //!< The line end signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2LineStart,  //!< The line start signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3FrameEnd,  //!< The frame end signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3FrameStart,  //!< The frame start signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3LineEnd,  //!< The line end signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3LineStart,  //!< The line start signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4FrameEnd,  //!< The frame end signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4FrameStart,  //!< The frame start signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4LineEnd,  //!< The line end signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4LineStart,  //!< The line start signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFrameEnd,  //!< The frame end signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFrameStart,  //!< The frame start signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalLineEnd,  //!< The line end signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalLineStart,  //!< The line start signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent0Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for CustomSignalEvent1Polarity
    enum CustomSignalEvent1PolarityEnums
    {
        CustomSignalEvent1Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        CustomSignalEvent1Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for CustomSignalEvent1Source
    enum CustomSignalEvent1SourceEnums
    {
        CustomSignalEvent1Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1FrameEnd,  //!< The frame end signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1FrameStart,  //!< The frame start signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1LineEnd,  //!< The line end signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1LineStart,  //!< The line start signal of cam 1 is set as input   - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2FrameEnd,  //!< The frame end signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2FrameStart,  //!< The frame start signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2LineEnd,  //!< The line end signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2LineStart,  //!< The line start signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3FrameEnd,  //!< The frame end signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3FrameStart,  //!< The frame start signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3LineEnd,  //!< The line end signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3LineStart,  //!< The line start signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4FrameEnd,  //!< The frame end signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4FrameStart,  //!< The frame start signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4LineEnd,  //!< The line end signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4LineStart,  //!< The line start signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFrameEnd,  //!< The frame end signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFrameStart,  //!< The frame start signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalLineEnd,  //!< The line end signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalLineStart,  //!< The line start signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        CustomSignalEvent1Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for CxpCameraUnexpectedStartupDataStatus
    enum CxpCameraUnexpectedStartupDataStatusEnums
    {
        CxpCameraUnexpectedStartupDataStatus_No,  //!< The input signal frequency hasn't exceeded the maximum frequency defined by the Trigger Output Frequency parameter - Applies to: CoaXPress
        CxpCameraUnexpectedStartupDataStatus_Yes  //!< The input signal frequency has exceeded the maximum frequency defined by the Trigger Output Frequency parameter - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkConfiguration
    enum CxpLinkConfigurationEnums
    {
        CxpLinkConfiguration_Auto,  //!< Link speed is controlled automatically - Applies to: CoaXPress
        CxpLinkConfiguration_CXP10_X1,  //!< 1 connection is operating at CXP-10 speed (10 0 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP10_X2,  //!< 2 connections are operating at CXP-10 speed (10 0 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP10_X3,  //!< 3 connections are operating at CXP-10 speed (10 0 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP10_X4,  //!< 4 connections are operating at CXP-10 speed (10 0 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP12_X1,  //!< 1 connection is operating at CXP-12 speed (12 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP12_X2,  //!< 2 connections are operating at CXP-12 speed (12 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP12_X3,  //!< 3 connections are operating at CXP-12 speed (12 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP12_X4,  //!< 4 connections are operating at CXP-12 speed (12 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP1_X1,  //!< 1 connection is operating at CXP-1 speed (1 25 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP1_X2,  //!< 2 connections are operating at CXP-1 speed (1 25 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP1_X3,  //!< 3 connections are operating at CXP-1 speed (1 25 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP1_X4,  //!< 4 connections are operating at CXP-1 speed (1 25 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP2_X1,  //!< 1 connection is operating at CXP-2 speed (2 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP2_X2,  //!< 2 connections are operating at CXP-2 speed (2 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP2_X3,  //!< 3 connections are operating at CXP-2 speed (2 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP2_X4,  //!< 4 connections are operating at CXP-2 speed (2 50 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP3_X1,  //!< 1 connection is operating at CXP-3 speed (3 125 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP3_X2,  //!< 2 connections are operating at CXP-3 speed (3 125 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP3_X3,  //!< 3 connections are operating at CXP-3 speed (3 125 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP3_X4,  //!< 4 connections are operating at CXP-3 speed (3 125 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP5_X1,  //!< 1 connection is operating at CXP-5 speed (5 00 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP5_X2,  //!< 2 connections are operating at CXP-5 speed (5 00 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP5_X3,  //!< 3 connections are operating at CXP-5 speed (5 00 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP5_X4,  //!< 4 connections are operating at CXP-5 speed (5 00 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP6_X1,  //!< 1 connection is operating at CXP-6 speed (6 25 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP6_X2,  //!< 2 connections are operating at CXP-6 speed (6 25 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP6_X3,  //!< 3 connections are operating at CXP-6 speed (6 25 Gbps) - Applies to: CoaXPress
        CxpLinkConfiguration_CXP6_X4  //!< 4 connections are operating at CXP-6 speed (6 25 Gbps) - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger0Source
    enum CxpLinkTrigger0SourceEnums
    {
        CxpLinkTrigger0Source_BypassFrontGPI0FallingEdge,  //!< Bypasses the Front GPI 0 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassFrontGPI0RisingEdge,  //!< Bypasses the Front GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassFrontGPI1FallingEdge,  //!< Bypasses the Front GPI 1 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassFrontGPI1RisingEdge,  //!< Bypasses the Front GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassFrontGPI2FallingEdge,  //!< Bypasses the Front GPI 2 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassFrontGPI2RisingEdge,  //!< Bypasses the Front GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassFrontGPI3FallingEdge,  //!< Bypasses the Front GPI 3 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassFrontGPI3RisingEdge,  //!< Bypasses the Front GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI0FallingEdge,  //!< Bypasses the GPI 0 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI0RisingEdge,  //!< Bypasses the GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI1FallingEdge,  //!< Bypasses the GPI 1 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI1RisingEdge,  //!< Bypasses the GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI2FallingEdge,  //!< Bypasses the GPI 2 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI2RisingEdge,  //!< Bypasses the GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI3FallingEdge,  //!< Bypasses the GPI 3 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI3RisingEdge,  //!< Bypasses the GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI4FallingEdge,  //!< Bypasses the GPI 4 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI4RisingEdge,  //!< Bypasses the GPI 4 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI5FallingEdge,  //!< Bypasses the GPI 5 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI5RisingEdge,  //!< Bypasses the GPI 5 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI6FallingEdge,  //!< Bypasses the GPI 6 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI6RisingEdge,  //!< Bypasses the GPI 6 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI7FallingEdge,  //!< Bypasses the GPI 7 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_BypassGPI7RisingEdge,  //!< Bypasses the GPI 7 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator0FallingEdge,  //!< The output source is set to camera port A pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator0RisingEdge,  //!< The output source is set to camera port A pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator1FallingEdge,  //!< The output source is set to camera port A pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator1RisingEdge,  //!< The output source is set to camera port A pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator2FallingEdge,  //!< The output source is set to camera port A pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator2RisingEdge,  //!< The output source is set to camera port A pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator3FallingEdge,  //!< The output source is set to camera port A pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamAPulseGenerator3RisingEdge,  //!< The output source is set to camera port A pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator0FallingEdge,  //!< The output source is set to camera port B pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator0RisingEdge,  //!< The output source is set to camera port B pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator1FallingEdge,  //!< The output source is set to camera port B pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator1RisingEdge,  //!< The output source is set to camera port B pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator2FallingEdge,  //!< The output source is set to camera port B pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator2RisingEdge,  //!< The output source is set to camera port B pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator3FallingEdge,  //!< The output source is set to camera port B pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamBPulseGenerator3RisingEdge,  //!< The output source is set to camera port B pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator0FallingEdge,  //!< The output source is set to camera port C pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator0RisingEdge,  //!< The output source is set to camera port C pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator1FallingEdge,  //!< The output source is set to camera port C pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator1RisingEdge,  //!< The output source is set to camera port C pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator2FallingEdge,  //!< The output source is set to camera port C pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator2RisingEdge,  //!< The output source is set to camera port C pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator3FallingEdge,  //!< The output source is set to camera port C pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamCPulseGenerator3RisingEdge,  //!< The output source is set to camera port C pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator0FallingEdge,  //!< The output source is set to camera port D pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator0RisingEdge,  //!< The output source is set to camera port D pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator1FallingEdge,  //!< The output source is set to camera port D pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator1RisingEdge,  //!< The output source is set to camera port D pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator2FallingEdge,  //!< The output source is set to camera port D pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator2RisingEdge,  //!< The output source is set to camera port D pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator3FallingEdge,  //!< The output source is set to camera port D pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamDPulseGenerator3RisingEdge,  //!< The output source is set to camera port D pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator0FallingEdge,  //!< The output source is set to camera port E pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator0RisingEdge,  //!< The output source is set to camera port E pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator1FallingEdge,  //!< The output source is set to camera port E pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator1RisingEdge,  //!< The output source is set to camera port E pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator2FallingEdge,  //!< The output source is set to camera port E pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator2RisingEdge,  //!< The output source is set to camera port E pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator3FallingEdge,  //!< The output source is set to camera port E pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_CamEPulseGenerator3RisingEdge,  //!< The output source is set to camera port E pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGenerator0FallingEdge,  //!< The source is set to pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGenerator1FallingEdge,  //!< The source is set to pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGenerator1RisingEdge,  //!< The source is set to pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGenerator2FallingEdge,  //!< The source is set to pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGenerator2RisingEdge,  //!< The source is set to pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGenerator3FallingEdge,  //!< The source is set to pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGenerator3RisingEdge,  //!< The source is set to pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_PulseGeneratorRisingEdge,  //!< The source is set to pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger0Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger0SourceEdge
    enum CxpLinkTrigger0SourceEdgeEnums
    {
        CxpLinkTrigger0SourceEdge_FallingEdge,  //!< Falling Edge of signal - Applies to: CoaXPress
        CxpLinkTrigger0SourceEdge_RisingEdge  //!< Rising Edge of signal - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger1Source
    enum CxpLinkTrigger1SourceEnums
    {
        CxpLinkTrigger1Source_BypassFrontGPI0FallingEdge,  //!< Bypasses the Front GPI 0 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassFrontGPI0RisingEdge,  //!< Bypasses the Front GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassFrontGPI1FallingEdge,  //!< Bypasses the Front GPI 1 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassFrontGPI1RisingEdge,  //!< Bypasses the Front GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassFrontGPI2FallingEdge,  //!< Bypasses the Front GPI 2 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassFrontGPI2RisingEdge,  //!< Bypasses the Front GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassFrontGPI3FallingEdge,  //!< Bypasses the Front GPI 3 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassFrontGPI3RisingEdge,  //!< Bypasses the Front GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI0FallingEdge,  //!< Bypasses the GPI 0 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI0RisingEdge,  //!< Bypasses the GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI1FallingEdge,  //!< Bypasses the GPI 1 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI1RisingEdge,  //!< Bypasses the GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI2FallingEdge,  //!< Bypasses the GPI 2 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI2RisingEdge,  //!< Bypasses the GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI3FallingEdge,  //!< Bypasses the GPI 3 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI3RisingEdge,  //!< Bypasses the GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI4FallingEdge,  //!< Bypasses the GPI 4 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI4RisingEdge,  //!< Bypasses the GPI 4 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI5FallingEdge,  //!< Bypasses the GPI 5 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI5RisingEdge,  //!< Bypasses the GPI 5 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI6FallingEdge,  //!< Bypasses the GPI 6 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI6RisingEdge,  //!< Bypasses the GPI 6 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI7FallingEdge,  //!< Bypasses the GPI 7 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_BypassGPI7RisingEdge,  //!< Bypasses the GPI 7 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator0FallingEdge,  //!< The output source is set to camera port A pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator0RisingEdge,  //!< The output source is set to camera port A pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator1FallingEdge,  //!< The output source is set to camera port A pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator1RisingEdge,  //!< The output source is set to camera port A pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator2FallingEdge,  //!< The output source is set to camera port A pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator2RisingEdge,  //!< The output source is set to camera port A pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator3FallingEdge,  //!< The output source is set to camera port A pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamAPulseGenerator3RisingEdge,  //!< The output source is set to camera port A pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator0FallingEdge,  //!< The output source is set to camera port B pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator0RisingEdge,  //!< The output source is set to camera port B pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator1FallingEdge,  //!< The output source is set to camera port B pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator1RisingEdge,  //!< The output source is set to camera port B pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator2FallingEdge,  //!< The output source is set to camera port B pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator2RisingEdge,  //!< The output source is set to camera port B pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator3FallingEdge,  //!< The output source is set to camera port B pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamBPulseGenerator3RisingEdge,  //!< The output source is set to camera port B pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator0FallingEdge,  //!< The output source is set to camera port C pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator0RisingEdge,  //!< The output source is set to camera port C pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator1FallingEdge,  //!< The output source is set to camera port C pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator1RisingEdge,  //!< The output source is set to camera port C pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator2FallingEdge,  //!< The output source is set to camera port C pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator2RisingEdge,  //!< The output source is set to camera port C pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator3FallingEdge,  //!< The output source is set to camera port C pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamCPulseGenerator3RisingEdge,  //!< The output source is set to camera port C pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator0FallingEdge,  //!< The output source is set to camera port D pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator0RisingEdge,  //!< The output source is set to camera port D pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator1FallingEdge,  //!< The output source is set to camera port D pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator1RisingEdge,  //!< The output source is set to camera port D pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator2FallingEdge,  //!< The output source is set to camera port D pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator2RisingEdge,  //!< The output source is set to camera port D pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator3FallingEdge,  //!< The output source is set to camera port D pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamDPulseGenerator3RisingEdge,  //!< The output source is set to camera port D pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator0FallingEdge,  //!< The output source is set to camera port E pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator0RisingEdge,  //!< The output source is set to camera port E pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator1FallingEdge,  //!< The output source is set to camera port E pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator1RisingEdge,  //!< The output source is set to camera port E pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator2FallingEdge,  //!< The output source is set to camera port E pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator2RisingEdge,  //!< The output source is set to camera port E pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator3FallingEdge,  //!< The output source is set to camera port E pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_CamEPulseGenerator3RisingEdge,  //!< The output source is set to camera port E pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGenerator0FallingEdge,  //!< The source is set to pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGenerator1FallingEdge,  //!< The source is set to pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGenerator1RisingEdge,  //!< The source is set to pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGenerator2FallingEdge,  //!< The source is set to pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGenerator2RisingEdge,  //!< The source is set to pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGenerator3FallingEdge,  //!< The source is set to pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGenerator3RisingEdge,  //!< The source is set to pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_PulseGeneratorRisingEdge,  //!< The source is set to pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger1Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger1SourceEdge
    enum CxpLinkTrigger1SourceEdgeEnums
    {
        CxpLinkTrigger1SourceEdge_FallingEdge,  //!< Falling Edge of signal - Applies to: CoaXPress
        CxpLinkTrigger1SourceEdge_RisingEdge  //!< Rising Edge of signal - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger2Source
    enum CxpLinkTrigger2SourceEnums
    {
        CxpLinkTrigger2Source_BypassFrontGPI0FallingEdge,  //!< Bypasses the Front GPI 0 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassFrontGPI0RisingEdge,  //!< Bypasses the Front GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassFrontGPI1FallingEdge,  //!< Bypasses the Front GPI 1 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassFrontGPI1RisingEdge,  //!< Bypasses the Front GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassFrontGPI2FallingEdge,  //!< Bypasses the Front GPI 2 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassFrontGPI2RisingEdge,  //!< Bypasses the Front GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassFrontGPI3FallingEdge,  //!< Bypasses the Front GPI 3 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassFrontGPI3RisingEdge,  //!< Bypasses the Front GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI0FallingEdge,  //!< Bypasses the GPI 0 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI0RisingEdge,  //!< Bypasses the GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI1FallingEdge,  //!< Bypasses the GPI 1 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI1RisingEdge,  //!< Bypasses the GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI2FallingEdge,  //!< Bypasses the GPI 2 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI2RisingEdge,  //!< Bypasses the GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI3FallingEdge,  //!< Bypasses the GPI 3 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI3RisingEdge,  //!< Bypasses the GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI4FallingEdge,  //!< Bypasses the GPI 4 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI4RisingEdge,  //!< Bypasses the GPI 4 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI5FallingEdge,  //!< Bypasses the GPI 5 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI5RisingEdge,  //!< Bypasses the GPI 5 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI6FallingEdge,  //!< Bypasses the GPI 6 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI6RisingEdge,  //!< Bypasses the GPI 6 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI7FallingEdge,  //!< Bypasses the GPI 7 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_BypassGPI7RisingEdge,  //!< Bypasses the GPI 7 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator0FallingEdge,  //!< The output source is set to camera port A pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator0RisingEdge,  //!< The output source is set to camera port A pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator1FallingEdge,  //!< The output source is set to camera port A pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator1RisingEdge,  //!< The output source is set to camera port A pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator2FallingEdge,  //!< The output source is set to camera port A pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator2RisingEdge,  //!< The output source is set to camera port A pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator3FallingEdge,  //!< The output source is set to camera port A pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamAPulseGenerator3RisingEdge,  //!< The output source is set to camera port A pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator0FallingEdge,  //!< The output source is set to camera port B pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator0RisingEdge,  //!< The output source is set to camera port B pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator1FallingEdge,  //!< The output source is set to camera port B pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator1RisingEdge,  //!< The output source is set to camera port B pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator2FallingEdge,  //!< The output source is set to camera port B pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator2RisingEdge,  //!< The output source is set to camera port B pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator3FallingEdge,  //!< The output source is set to camera port B pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamBPulseGenerator3RisingEdge,  //!< The output source is set to camera port B pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator0FallingEdge,  //!< The output source is set to camera port C pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator0RisingEdge,  //!< The output source is set to camera port C pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator1FallingEdge,  //!< The output source is set to camera port C pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator1RisingEdge,  //!< The output source is set to camera port C pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator2FallingEdge,  //!< The output source is set to camera port C pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator2RisingEdge,  //!< The output source is set to camera port C pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator3FallingEdge,  //!< The output source is set to camera port C pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamCPulseGenerator3RisingEdge,  //!< The output source is set to camera port C pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator0FallingEdge,  //!< The output source is set to camera port D pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator0RisingEdge,  //!< The output source is set to camera port D pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator1FallingEdge,  //!< The output source is set to camera port D pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator1RisingEdge,  //!< The output source is set to camera port D pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator2FallingEdge,  //!< The output source is set to camera port D pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator2RisingEdge,  //!< The output source is set to camera port D pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator3FallingEdge,  //!< The output source is set to camera port D pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamDPulseGenerator3RisingEdge,  //!< The output source is set to camera port D pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator0FallingEdge,  //!< The output source is set to camera port E pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator0RisingEdge,  //!< The output source is set to camera port E pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator1FallingEdge,  //!< The output source is set to camera port E pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator1RisingEdge,  //!< The output source is set to camera port E pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator2FallingEdge,  //!< The output source is set to camera port E pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator2RisingEdge,  //!< The output source is set to camera port E pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator3FallingEdge,  //!< The output source is set to camera port E pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_CamEPulseGenerator3RisingEdge,  //!< The output source is set to camera port E pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGenerator0FallingEdge,  //!< The source is set to pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGenerator1FallingEdge,  //!< The source is set to pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGenerator1RisingEdge,  //!< The source is set to pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGenerator2FallingEdge,  //!< The source is set to pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGenerator2RisingEdge,  //!< The source is set to pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGenerator3FallingEdge,  //!< The source is set to pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGenerator3RisingEdge,  //!< The source is set to pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_PulseGeneratorRisingEdge,  //!< The source is set to pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger2Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger2SourceEdge
    enum CxpLinkTrigger2SourceEdgeEnums
    {
        CxpLinkTrigger2SourceEdge_FallingEdge,  //!< Falling Edge of signal - Applies to: CoaXPress
        CxpLinkTrigger2SourceEdge_RisingEdge  //!< Rising Edge of signal - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger3Source
    enum CxpLinkTrigger3SourceEnums
    {
        CxpLinkTrigger3Source_BypassFrontGPI0FallingEdge,  //!< Bypasses the Front GPI 0 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassFrontGPI0RisingEdge,  //!< Bypasses the Front GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassFrontGPI1FallingEdge,  //!< Bypasses the Front GPI 1 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassFrontGPI1RisingEdge,  //!< Bypasses the Front GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassFrontGPI2FallingEdge,  //!< Bypasses the Front GPI 2 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassFrontGPI2RisingEdge,  //!< Bypasses the Front GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassFrontGPI3FallingEdge,  //!< Bypasses the Front GPI 3 signal falling edge directly to the output   - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassFrontGPI3RisingEdge,  //!< Bypasses the Front GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI0FallingEdge,  //!< Bypasses the GPI 0 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI0RisingEdge,  //!< Bypasses the GPI 0 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI1FallingEdge,  //!< Bypasses the GPI 1 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI1RisingEdge,  //!< Bypasses the GPI 1 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI2FallingEdge,  //!< Bypasses the GPI 2 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI2RisingEdge,  //!< Bypasses the GPI 2 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI3FallingEdge,  //!< Bypasses the GPI 3 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI3RisingEdge,  //!< Bypasses the GPI 3 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI4FallingEdge,  //!< Bypasses the GPI 4 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI4RisingEdge,  //!< Bypasses the GPI 4 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI5FallingEdge,  //!< Bypasses the GPI 5 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI5RisingEdge,  //!< Bypasses the GPI 5 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI6FallingEdge,  //!< Bypasses the GPI 6 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI6RisingEdge,  //!< Bypasses the GPI 6 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI7FallingEdge,  //!< Bypasses the GPI 7 signal falling edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_BypassGPI7RisingEdge,  //!< Bypasses the GPI 7 signal rising edge directly to the output - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator0FallingEdge,  //!< The output source is set to camera port A pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator0RisingEdge,  //!< The output source is set to camera port A pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator1FallingEdge,  //!< The output source is set to camera port A pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator1RisingEdge,  //!< The output source is set to camera port A pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator2FallingEdge,  //!< The output source is set to camera port A pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator2RisingEdge,  //!< The output source is set to camera port A pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator3FallingEdge,  //!< The output source is set to camera port A pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamAPulseGenerator3RisingEdge,  //!< The output source is set to camera port A pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator0FallingEdge,  //!< The output source is set to camera port B pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator0RisingEdge,  //!< The output source is set to camera port B pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator1FallingEdge,  //!< The output source is set to camera port B pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator1RisingEdge,  //!< The output source is set to camera port B pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator2FallingEdge,  //!< The output source is set to camera port B pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator2RisingEdge,  //!< The output source is set to camera port B pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator3FallingEdge,  //!< The output source is set to camera port B pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamBPulseGenerator3RisingEdge,  //!< The output source is set to camera port B pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator0FallingEdge,  //!< The output source is set to camera port C pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator0RisingEdge,  //!< The output source is set to camera port C pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator1FallingEdge,  //!< The output source is set to camera port C pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator1RisingEdge,  //!< The output source is set to camera port C pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator2FallingEdge,  //!< The output source is set to camera port C pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator2RisingEdge,  //!< The output source is set to camera port C pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator3FallingEdge,  //!< The output source is set to camera port C pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamCPulseGenerator3RisingEdge,  //!< The output source is set to camera port C pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator0FallingEdge,  //!< The output source is set to camera port D pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator0RisingEdge,  //!< The output source is set to camera port D pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator1FallingEdge,  //!< The output source is set to camera port D pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator1RisingEdge,  //!< The output source is set to camera port D pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator2FallingEdge,  //!< The output source is set to camera port D pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator2RisingEdge,  //!< The output source is set to camera port D pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator3FallingEdge,  //!< The output source is set to camera port D pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamDPulseGenerator3RisingEdge,  //!< The output source is set to camera port D pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator0FallingEdge,  //!< The output source is set to camera port E pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator0RisingEdge,  //!< The output source is set to camera port E pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator1FallingEdge,  //!< The output source is set to camera port E pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator1RisingEdge,  //!< The output source is set to camera port E pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator2FallingEdge,  //!< The output source is set to camera port E pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator2RisingEdge,  //!< The output source is set to camera port E pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator3FallingEdge,  //!< The output source is set to camera port E pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_CamEPulseGenerator3RisingEdge,  //!< The output source is set to camera port E pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGenerator0FallingEdge,  //!< The source is set to pulse generator 0 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGenerator1FallingEdge,  //!< The source is set to pulse generator 1 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGenerator1RisingEdge,  //!< The source is set to pulse generator 1 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGenerator2FallingEdge,  //!< The source is set to pulse generator 2 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGenerator2RisingEdge,  //!< The source is set to pulse generator 2 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGenerator3FallingEdge,  //!< The source is set to pulse generator 3 falling edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGenerator3RisingEdge,  //!< The source is set to pulse generator 3 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_PulseGeneratorRisingEdge,  //!< The source is set to pulse generator 0 rising edge - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        CxpLinkTrigger3Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for CxpLinkTrigger3SourceEdge
    enum CxpLinkTrigger3SourceEdgeEnums
    {
        CxpLinkTrigger3SourceEdge_FallingEdge,  //!< Falling Edge of signal - Applies to: CoaXPress
        CxpLinkTrigger3SourceEdge_RisingEdge  //!< Rising Edge of signal - Applies to: CoaXPress
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
        DeviceType_CameraLink,  //!< Camera Link - Applies to: CoaXPress
        DeviceType_CameraLinkHS,  //!< Camera Link High Speed - Applies to: CoaXPress
        DeviceType_CoaXPress,  //!< CoaXPress - Applies to: CoaXPress
        DeviceType_Custom,  //!< The device uses a custom transport layer - Applies to: CoaXPress
        DeviceType_GEV,  //!< The device uses the GigE Vision transport layer - Applies to: CoaXPress
        DeviceType_GigEVision,  //!< GigE Vision - Applies to: CoaXPress
        DeviceType_Mixed,  //!< Different interface modules of the GenTL Producer are of different types - Applies to: CoaXPress
        DeviceType_U3V,  //!< The device uses the USB3 Vision transport layer - Applies to: CoaXPress
        DeviceType_USB3Vision  //!< USB3 Vision - Applies to: CoaXPress
    };

    //! Valid values for EventNotification
    enum EventNotificationEnums
    {
        EventNotification_Off,  //!< The selected event notification is disabled - Applies to: CoaXPress and blaze
        EventNotification_On,  //!< The selected event notification is enabled - Applies to: CoaXPress and blaze
        EventNotification_Once  //!< The selected event notification is enabled for one event and then returned to Off state - Applies to: CoaXPress and blaze
    };

    //! Valid values for EventSelector
    enum EventSelectorEnums
    {
        EventSelector_AcquisitionTrigger,  //!< Entry for the event AcquisitionTrigger - Applies to: CoaXPress
        EventSelector_CameraStreamStatus,  //!< Entry for the event CameraStreamStatus - Applies to: CoaXPress
        EventSelector_DeviceLost,  //!< The Device Lost event is selected - Applies to: CoaXPress and blaze
        EventSelector_FrameTransferEnd,  //!< Entry for the event FrameTransferEnd - Applies to: CoaXPress
        EventSelector_FrameTransferStart,  //!< Entry for the event FrameTransferStart - Applies to: CoaXPress
        EventSelector_FrameTriggerMissed,  //!< Entry for the event FrameTriggerMissed - Applies to: CoaXPress
        EventSelector_LineTransferEnd,  //!< Entry for the event LineTransferEnd - Applies to: CoaXPress
        EventSelector_LineTransferStart,  //!< Entry for the event LineTransferStart - Applies to: CoaXPress
        EventSelector_Overflow,  //!< Entry for the event Overflow - Applies to: CoaXPress
        EventSelector_TriggerExceededPeriodLimits,  //!< Entry for the event TriggerExceededPeriodLimits - Applies to: CoaXPress
        EventSelector_TriggerQueueFilllevelThresholdOff,  //!< Entry for the event TriggerQueueFilllevelThresholdOff - Applies to: CoaXPress
        EventSelector_TriggerQueueFilllevelThresholdOn  //!< Entry for the event TriggerQueueFilllevelThresholdOn - Applies to: CoaXPress
    };

    //! Valid values for ExSyncOn
    enum ExSyncOnEnums
    {
        ExSyncOn_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        ExSyncOn_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for ExSyncPolarity
    enum ExSyncPolarityEnums
    {
        ExSyncPolarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        ExSyncPolarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for ExtensionGPOType
    enum ExtensionGPOTypeEnums
    {
        ExtensionGPOType_GPOOpenDrain,  //!< Configure to open-drain - Applies to: CoaXPress
        ExtensionGPOType_GPOPushPull  //!< Configure to push/pull - Applies to: CoaXPress
    };

    //! Valid values for FlashOn
    enum FlashOnEnums
    {
        FlashOn_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        FlashOn_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for FlashPolarity
    enum FlashPolarityEnums
    {
        FlashPolarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        FlashPolarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for Format
    enum FormatEnums
    {
        Format_BGR10p,  //!< The pixel output format is set to BGR10p - Applies to: CoaXPress
        Format_BGR12p,  //!< The pixel output format is set to BGR12p - Applies to: CoaXPress
        Format_BGR14p,  //!< The pixel output format is set to BGR14p - Applies to: CoaXPress
        Format_BGR16,  //!< The pixel output format is set to BGR16 - Applies to: CoaXPress
        Format_BGR8,  //!< The pixel output format is set to BGR8 - Applies to: CoaXPress
        Format_BGRa8,  //!< The pixel output format is set to BGRa8 - Applies to: CoaXPress
        Format_BayerBG10p,  //!< The pixel output format is set to BayerBG10p - Applies to: CoaXPress
        Format_BayerBG12p,  //!< The pixel output format is set to BayerBG12p - Applies to: CoaXPress
        Format_BayerBG14p,  //!< The pixel output format is set to BayerBG14p - Applies to: CoaXPress
        Format_BayerBG16,  //!< The pixel output format is set to BayerBG16 - Applies to: CoaXPress
        Format_BayerBG8,  //!< The pixel output format is set to BayerBG8 - Applies to: CoaXPress
        Format_BayerGB10p,  //!< The pixel output format is set to BayerGB10p - Applies to: CoaXPress
        Format_BayerGB12p,  //!< The pixel output format is set to BayerGB12p - Applies to: CoaXPress
        Format_BayerGB14p,  //!< The pixel output format is set to BayerGB14p - Applies to: CoaXPress
        Format_BayerGB16,  //!< The pixel output format is set to BayerGB16 - Applies to: CoaXPress
        Format_BayerGB8,  //!< The pixel output format is set to BayerGB8 - Applies to: CoaXPress
        Format_BayerGR10p,  //!< The pixel output format is set to BayerGR10p - Applies to: CoaXPress
        Format_BayerGR12p,  //!< The pixel output format is set to BayerGR12p - Applies to: CoaXPress
        Format_BayerGR14p,  //!< The pixel output format is set to BayerGR14p - Applies to: CoaXPress
        Format_BayerGR16,  //!< The pixel output format is set to BayerGR16 - Applies to: CoaXPress
        Format_BayerGR8,  //!< The pixel output format is set to BayerGR8 - Applies to: CoaXPress
        Format_BayerRG10p,  //!< The pixel output format is set to BayerRG10p - Applies to: CoaXPress
        Format_BayerRG12p,  //!< The pixel output format is set to BayerRG12p - Applies to: CoaXPress
        Format_BayerRG14p,  //!< The pixel output format is set to BayerRG14p - Applies to: CoaXPress
        Format_BayerRG16,  //!< The pixel output format is set to BayerRG16 - Applies to: CoaXPress
        Format_BayerRG8,  //!< The pixel output format is set to BayerRG8 - Applies to: CoaXPress
        Format_BiColorBGRG10,  //!< The pixel format is set to Bi-color pixel Blue/Green - Red/Green 10 Bit - Applies to: CoaXPress
        Format_BiColorBGRG12,  //!< The pixel format is set to Bi-color pixel Blue/Green - Red/Green 12 Bit - Applies to: CoaXPress
        Format_BiColorBGRG8,  //!< The pixel format is set to Bi-color pixel Blue/Green - Red/Green 8 Bit - Applies to: CoaXPress
        Format_BiColorGBGR10,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        Format_BiColorGBGR12,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        Format_BiColorGBGR8,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        Format_BiColorGRGB10,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        Format_BiColorGRGB12,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        Format_BiColorGRGB8,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        Format_BiColorRGBG10,  //!< The pixel format is set to Bi-color pixel Red/Green - Blue/Green 10 Bit - Applies to: CoaXPress
        Format_BiColorRGBG12,  //!< The pixel format is set to Bi-color pixel Red/Green - Blue/Green 12 Bit - Applies to: CoaXPress
        Format_BiColorRGBG8,  //!< The pixel format is set to Bi-color pixel Red/Green - Blue/Green 8 Bit - Applies to: CoaXPress
        Format_Mono10p,  //!< The pixel output format is set to Mono10p - Applies to: CoaXPress
        Format_Mono12p,  //!< The pixel output format is set to Mono12p - Applies to: CoaXPress
        Format_Mono14p,  //!< The pixel output format is set to Mono14p - Applies to: CoaXPress
        Format_Mono16,  //!< The pixel output format is set to Mono16 - Applies to: CoaXPress
        Format_Mono8,  //!< The pixel output format is set to Mono8 - Applies to: CoaXPress
        Format_RGB10p,  //!< The pixel output format is set to RGB10p - Applies to: CoaXPress
        Format_RGB12p,  //!< The pixel output format is set to RGB12p - Applies to: CoaXPress
        Format_RGB14p,  //!< The pixel output format is set to RGB14p - Applies to: CoaXPress
        Format_RGB16,  //!< The pixel output format is set to RGB16 - Applies to: CoaXPress
        Format_RGB8,  //!< The pixel output format is set to RGB8 - Applies to: CoaXPress
        Format_RGBa8,  //!< The pixel output format is set to RGBa8 - Applies to: CoaXPress
        Format_YCbCr422_8  //!< The pixel output format is set to YCbCr422_8 - Applies to: CoaXPress
    };

    //! Valid values for FrontGPIPullControl
    enum FrontGPIPullControlEnums
    {
        FrontGPIPullControl_FrontGPIPullDown,  //!< Configure to pull-down - Applies to: CoaXPress
        FrontGPIPullControl_FrontGPIPullUp  //!< Configure to pull-up - Applies to: CoaXPress
    };

    //! Valid values for FrontGPISignalType
    enum FrontGPISignalTypeEnums
    {
        FrontGPISignalType_FrontGPIDifferential,  //!< Configure as differential - Applies to: CoaXPress
        FrontGPISignalType_FrontGPISingleEnded  //!< Configure as single-ended - Applies to: CoaXPress
    };

    //! Valid values for FrontGPOInversion
    enum FrontGPOInversionEnums
    {
        FrontGPOInversion_FrontGPOInversionOff,  //!< Disable inversion - Applies to: CoaXPress
        FrontGPOInversion_FrontGPOInversionOn  //!< Enable inversion - Applies to: CoaXPress
    };

    //! Valid values for ImageTriggerInputPolarity
    enum ImageTriggerInputPolarityEnums
    {
        ImageTriggerInputPolarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        ImageTriggerInputPolarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for ImageTriggerInputSource
    enum ImageTriggerInputSourceEnums
    {
        ImageTriggerInputSource_GPITriggerSource0,  //!< Trigger Source is set to  GPI 0 - Applies to: CoaXPress
        ImageTriggerInputSource_GPITriggerSource1,  //!< Trigger Source is set to  GPI 1 - Applies to: CoaXPress
        ImageTriggerInputSource_GPITriggerSource2,  //!< Trigger Source is set to  GPI 2 - Applies to: CoaXPress
        ImageTriggerInputSource_GPITriggerSource3,  //!< Trigger Source is set to  GPI 3 - Applies to: CoaXPress
        ImageTriggerInputSource_GPITriggerSource4,  //!< Trigger Source is set to GPI  4  Not available on LightBridge - Applies to: CoaXPress
        ImageTriggerInputSource_GPITriggerSource5,  //!< Trigger Source is set to GPI  5  Not available on LightBridge - Applies to: CoaXPress
        ImageTriggerInputSource_GPITriggerSource6,  //!< Trigger Source is set to GPI  6  Not available on LightBridge - Applies to: CoaXPress
        ImageTriggerInputSource_GPITriggerSource7,  //!< Trigger Source is set to GPI  7  Not available on LightBridge - Applies to: CoaXPress
        ImageTriggerInputSource_SoftwareTrigger,  //!< Trigger mode is set to Software - Applies to: CoaXPress
        ImageTriggerInputSource_TriggerInSourceFrontGPI0,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 0 - Applies to: CoaXPress
        ImageTriggerInputSource_TriggerInSourceFrontGPI1,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 1 - Applies to: CoaXPress
        ImageTriggerInputSource_TriggerInSourceFrontGPI2,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 2 - Applies to: CoaXPress
        ImageTriggerInputSource_TriggerInSourceFrontGPI3  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 3 - Applies to: CoaXPress
    };

    //! Valid values for ImageTriggerIsBusy
    enum ImageTriggerIsBusyEnums
    {
        ImageTriggerIsBusy_Busy,  //!< The software trigger is busy - Applies to: CoaXPress
        ImageTriggerIsBusy_NotBusy  //!< The software trigger is not busy - Applies to: CoaXPress
    };

    //! Valid values for ImageTriggerMode
    enum ImageTriggerModeEnums
    {
        ImageTriggerMode_AsyncExternalTrigger,  //!< Trigger mode is set to Async External Trigger - Applies to: CoaXPress
        ImageTriggerMode_AsyncExternalTriggerMultiframe,  //!< Trigger mode is set to Async External Trigger Multiframe - Applies to: CoaXPress
        ImageTriggerMode_AsyncGatedTrigger,  //!< Trigger mode is set to Async Gated Trigger - Applies to: CoaXPress
        ImageTriggerMode_AsyncGatedTriggerMultiframe,  //!< Trigger mode is set to Async Gated Trigger Multiframe - Applies to: CoaXPress
        ImageTriggerMode_freeRun  //!< Free run mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for ImageTriggerOn
    enum ImageTriggerOnEnums
    {
        ImageTriggerOn_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        ImageTriggerOn_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for LineTriggerInPolarity
    enum LineTriggerInPolarityEnums
    {
        LineTriggerInPolarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        LineTriggerInPolarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for LineTriggerInSource
    enum LineTriggerInSourceEnums
    {
        LineTriggerInSource_GPITriggerSource0,  //!< Trigger Source is set to  GPI 0 - Applies to: CoaXPress
        LineTriggerInSource_GPITriggerSource1,  //!< Trigger Source is set to  GPI 1 - Applies to: CoaXPress
        LineTriggerInSource_GPITriggerSource2,  //!< Trigger Source is set to  GPI 2 - Applies to: CoaXPress
        LineTriggerInSource_GPITriggerSource3,  //!< Trigger Source is set to  GPI 3 - Applies to: CoaXPress
        LineTriggerInSource_GPITriggerSource4,  //!< Trigger Source is set to GPI  4  Not available on LightBridge - Applies to: CoaXPress
        LineTriggerInSource_GPITriggerSource5,  //!< Trigger Source is set to GPI  5  Not available on LightBridge - Applies to: CoaXPress
        LineTriggerInSource_GPITriggerSource6,  //!< Trigger Source is set to GPI  6  Not available on LightBridge - Applies to: CoaXPress
        LineTriggerInSource_GPITriggerSource7,  //!< Trigger Source is set to GPI  7  Not available on LightBridge - Applies to: CoaXPress
        LineTriggerInSource_TriggerInSourceFrontGPI0,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 0 - Applies to: CoaXPress
        LineTriggerInSource_TriggerInSourceFrontGPI1,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 1 - Applies to: CoaXPress
        LineTriggerInSource_TriggerInSourceFrontGPI2,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 2 - Applies to: CoaXPress
        LineTriggerInSource_TriggerInSourceFrontGPI3  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 3 - Applies to: CoaXPress
    };

    //! Valid values for LineTriggerMode
    enum LineTriggerModeEnums
    {
        LineTriggerMode_AsyncExternalTrigger,  //!< Trigger mode is set to Async External Trigger - Applies to: CoaXPress
        LineTriggerMode_AsyncGatedTrigger,  //!< Trigger mode is set to Async Gated Trigger - Applies to: CoaXPress
        LineTriggerMode_GrabberControlled,  //!< Line trigger mode is controlled by the grabber - Applies to: CoaXPress
        LineTriggerMode_GrabberControlledGated  //!< Trigger mode is controlled by the grabber in gated mode - Applies to: CoaXPress
    };

    //! Valid values for LutEnable
    enum LutEnableEnums
    {
        LutEnable_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        LutEnable_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for LutImplementationType
    enum LutImplementationTypeEnums
    {
        LutImplementationType_FullLUT,  //!< Sets 1 value for each possible pixel value - Applies to: CoaXPress
        LutImplementationType_KneeLUT  //!< An interpolation is used for pixel values based on a set of defined values - Applies to: CoaXPress
    };

    //! Valid values for LutType
    enum LutTypeEnums
    {
        LutType_Processor,  //!< Processor - Applies to: CoaXPress
        LutType_UserFile  //!< A user file is used to configure the value - Applies to: CoaXPress
    };

    //! Valid values for MissingCameraFrameResponse
    enum MissingCameraFrameResponseEnums
    {
        MissingCameraFrameResponse_No,  //!< The camera sends a frame for each output trigger pulse - Applies to: CoaXPress
        MissingCameraFrameResponse_Yes  //!< The camera doesn't send a frame for each output trigger pulse - Applies to: CoaXPress
    };

    //! Valid values for OverflowEventSelect
    enum OverflowEventSelectEnums
    {
        OverflowEventSelect_All,  //!< Overflow event indicating frames of all states: correct, incomplete or lost - Applies to: CoaXPress
        OverflowEventSelect_Incomplete,  //!< Overflow event indicating incomplete frames - Applies to: CoaXPress
        OverflowEventSelect_IncompleteLost,  //!< Overflow event indicating incomplete and lost frames - Applies to: CoaXPress
        OverflowEventSelect_IncompleteOK,  //!< Overflow event indicating correct or incomplete frames - Applies to: CoaXPress
        OverflowEventSelect_Lost,  //!< Overflow event indicating lost frames   - Applies to: CoaXPress
        OverflowEventSelect_LostOK,  //!< Overflow event indicating correct or lost frames - Applies to: CoaXPress
        OverflowEventSelect_OK  //!< Overflow event indicating correct frames - Applies to: CoaXPress
    };

    //! Valid values for PixelFormat
    enum PixelFormatEnums
    {
        PixelFormat_BayerBG10p,  //!< The pixel format is set to BayerBG10p - Applies to: CoaXPress
        PixelFormat_BayerBG12p,  //!< The pixel format is set to BayerBG12p - Applies to: CoaXPress
        PixelFormat_BayerBG14p,  //!< The pixel format is set to BayerBG14p - Applies to: CoaXPress
        PixelFormat_BayerBG8,  //!< The pixel format is set to BayerBG8 - Applies to: CoaXPress
        PixelFormat_BayerGB10p,  //!< The pixel format is set to BayerGB10p - Applies to: CoaXPress
        PixelFormat_BayerGB12p,  //!< The pixel format is set to BayerGB12p - Applies to: CoaXPress
        PixelFormat_BayerGB14p,  //!< The pixel format is set to BayerGB14p - Applies to: CoaXPress
        PixelFormat_BayerGB8,  //!< The pixel format is set to BayerGB8 - Applies to: CoaXPress
        PixelFormat_BayerGR10p,  //!< The pixel format is set to BayerGR10p - Applies to: CoaXPress
        PixelFormat_BayerGR12p,  //!< The pixel format is set to BayerGR12p - Applies to: CoaXPress
        PixelFormat_BayerGR14p,  //!< The pixel format is set to BayerGR14p - Applies to: CoaXPress
        PixelFormat_BayerGR8,  //!< The pixel format is set to BayerGR8 - Applies to: CoaXPress
        PixelFormat_BayerRG10p,  //!< The pixel format is set to BayerRG10p - Applies to: CoaXPress
        PixelFormat_BayerRG12p,  //!< The pixel format is set to BayerRG12p - Applies to: CoaXPress
        PixelFormat_BayerRG14p,  //!< The pixel format is set to BayerRG14p - Applies to: CoaXPress
        PixelFormat_BayerRG8,  //!< The pixel format is set to BayerRG8 - Applies to: CoaXPress
        PixelFormat_BiColorBGRG10,  //!< The pixel format is set to Bi-color pixel Blue/Green - Red/Green 10 Bit - Applies to: CoaXPress
        PixelFormat_BiColorBGRG12,  //!< The pixel format is set to Bi-color pixel Blue/Green - Red/Green 12 Bit - Applies to: CoaXPress
        PixelFormat_BiColorBGRG8,  //!< The pixel format is set to Bi-color pixel Blue/Green - Red/Green 8 Bit - Applies to: CoaXPress
        PixelFormat_BiColorGBGR10,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        PixelFormat_BiColorGBGR12,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        PixelFormat_BiColorGBGR8,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        PixelFormat_BiColorGRGB10,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        PixelFormat_BiColorGRGB12,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        PixelFormat_BiColorGRGB8,  //!< Do not use / This format will be removed - Applies to: CoaXPress
        PixelFormat_BiColorRGBG10,  //!< The pixel format is set to Bi-color pixel Red/Green - Blue/Green 10 Bit - Applies to: CoaXPress
        PixelFormat_BiColorRGBG12,  //!< The pixel format is set to Bi-color pixel Red/Green - Blue/Green 12 Bit - Applies to: CoaXPress
        PixelFormat_BiColorRGBG8,  //!< The pixel format is set to Bi-color pixel Red/Green - Blue/Green 8 Bit - Applies to: CoaXPress
        PixelFormat_Mono10,  //!< The pixel format is set to Mono10 - Applies to: CoaXPress
        PixelFormat_Mono10p,  //!< The pixel output format is set to Mono 10p - Applies to: CoaXPress
        PixelFormat_Mono12,  //!< The pixel format is set to Mono12 - Applies to: CoaXPress
        PixelFormat_Mono12p,  //!< The pixel output format is set to Mono 12p - Applies to: CoaXPress
        PixelFormat_Mono14p,  //!< The pixel output format is set to Mono 14p - Applies to: CoaXPress
        PixelFormat_Mono16,  //!< The pixel format is set to Mono16 - Applies to: CoaXPress
        PixelFormat_Mono8,  //!< The pixel format is set to Mono8 - Applies to: CoaXPress
        PixelFormat_RGB10p,  //!< The pixel format is set to RGB10p - Applies to: CoaXPress
        PixelFormat_RGB12p,  //!< The pixel format is set to RGB12p - Applies to: CoaXPress
        PixelFormat_RGB14p,  //!< The pixel format is set to RGB14p - Applies to: CoaXPress
        PixelFormat_RGB16,  //!< The pixel format is set to RGB16 - Applies to: CoaXPress
        PixelFormat_RGB8,  //!< The pixel format is set to RGB8 - Applies to: CoaXPress
        PixelFormat_YCbCr422_8  //!< The pixel format is set to YCbCr422_8 - Applies to: CoaXPress
    };

    //! Valid values for ProcessingInvert
    enum ProcessingInvertEnums
    {
        ProcessingInvert_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        ProcessingInvert_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for SetSoftwareTrigger
    enum SetSoftwareTriggerEnums
    {
        SetSoftwareTrigger_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        SetSoftwareTrigger_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for ShaftEncoderCompensationEnable
    enum ShaftEncoderCompensationEnableEnums
    {
        ShaftEncoderCompensationEnable_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        ShaftEncoderCompensationEnable_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for ShaftEncoderInputSource
    enum ShaftEncoderInputSourceEnums
    {
        ShaftEncoderInputSource_GPITriggerSource0,  //!< Trigger Source is set to  GPI 0 - Applies to: CoaXPress
        ShaftEncoderInputSource_GPITriggerSource1,  //!< Trigger Source is set to  GPI 1 - Applies to: CoaXPress
        ShaftEncoderInputSource_GPITriggerSource2,  //!< Trigger Source is set to  GPI 2 - Applies to: CoaXPress
        ShaftEncoderInputSource_GPITriggerSource3,  //!< Trigger Source is set to  GPI 3 - Applies to: CoaXPress
        ShaftEncoderInputSource_GPITriggerSource4,  //!< Trigger Source is set to GPI  4  Not available on LightBridge - Applies to: CoaXPress
        ShaftEncoderInputSource_GPITriggerSource5,  //!< Trigger Source is set to GPI  5  Not available on LightBridge - Applies to: CoaXPress
        ShaftEncoderInputSource_GPITriggerSource6,  //!< Trigger Source is set to GPI  6  Not available on LightBridge - Applies to: CoaXPress
        ShaftEncoderInputSource_GPITriggerSource7,  //!< Trigger Source is set to GPI  7  Not available on LightBridge - Applies to: CoaXPress
        ShaftEncoderInputSource_TriggerInSourceFrontGPI0,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 0 - Applies to: CoaXPress
        ShaftEncoderInputSource_TriggerInSourceFrontGPI1,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 1 - Applies to: CoaXPress
        ShaftEncoderInputSource_TriggerInSourceFrontGPI2,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 2 - Applies to: CoaXPress
        ShaftEncoderInputSource_TriggerInSourceFrontGPI3  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 3 - Applies to: CoaXPress
    };

    //! Valid values for ShaftEncoderLeading
    enum ShaftEncoderLeadingEnums
    {
        ShaftEncoderLeading_SourceA,  //!< Shaft encoder leading edge is A - Applies to: CoaXPress
        ShaftEncoderLeading_SourceB  //!< Shaft encoder leading edge is B - Applies to: CoaXPress
    };

    //! Valid values for ShaftEncoderMode
    enum ShaftEncoderModeEnums
    {
        ShaftEncoderMode_FilterX1,  //!< Shaft encoder mode is set to X1   - Applies to: CoaXPress
        ShaftEncoderMode_FilterX2,  //!< Shaft encoder mode is set to X2   - Applies to: CoaXPress
        ShaftEncoderMode_FilterX4  //!< Shaft encoder mode is set to X4   - Applies to: CoaXPress
    };

    //! Valid values for ShaftEncoderOn
    enum ShaftEncoderOnEnums
    {
        ShaftEncoderOn_Off,  //!< The trigger queue mode is disabled - Applies to: CoaXPress
        ShaftEncoderOn_On  //!< The trigger queue mode is enabled - Applies to: CoaXPress
    };

    //! Valid values for SignalAnalyzer0Polarity
    enum SignalAnalyzer0PolarityEnums
    {
        SignalAnalyzer0Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        SignalAnalyzer0Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for SignalAnalyzer0Source
    enum SignalAnalyzer0SourceEnums
    {
        SignalAnalyzer0Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1FrameEnd,  //!< The frame end signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1FrameStart,  //!< The frame start signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1LineEnd,  //!< The line end signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1LineStart,  //!< The line start signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2FrameEnd,  //!< The frame end signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2FrameStart,  //!< The frame start signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2LineEnd,  //!< The line end signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2LineStart,  //!< The line start signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3FrameEnd,  //!< The frame end signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3FrameStart,  //!< The frame start signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3LineEnd,  //!< The line end signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3LineStart,  //!< The line start signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4FrameEnd,  //!< The frame end signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4FrameStart,  //!< The frame start signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4LineEnd,  //!< The line end signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4LineStart,  //!< The line start signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFrameEnd,  //!< The frame end signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFrameStart,  //!< The frame start signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalLineEnd,  //!< The line end signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalLineStart,  //!< The line start signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer0Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for SignalAnalyzer1Polarity
    enum SignalAnalyzer1PolarityEnums
    {
        SignalAnalyzer1Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        SignalAnalyzer1Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for SignalAnalyzer1Source
    enum SignalAnalyzer1SourceEnums
    {
        SignalAnalyzer1Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1FrameEnd,  //!< The frame end signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1FrameStart,  //!< The frame start signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1LineEnd,  //!< The line end signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1LineStart,  //!< The line start signal of cam 1 is set as input   - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2FrameEnd,  //!< The frame end signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2FrameStart,  //!< The frame start signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2LineEnd,  //!< The line end signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2LineStart,  //!< The line start signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3FrameEnd,  //!< The frame end signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3FrameStart,  //!< The frame start signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3LineEnd,  //!< The line end signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3LineStart,  //!< The line start signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4FrameEnd,  //!< The frame end signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4FrameStart,  //!< The frame start signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4LineEnd,  //!< The line end signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4LineStart,  //!< The line start signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFrameEnd,  //!< The frame end signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFrameStart,  //!< The frame start signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalLineEnd,  //!< The line end signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalLineStart,  //!< The line start signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        SignalAnalyzer1Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
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

    //! Valid values for TapGeometry
    enum TapGeometryEnums
    {
        TapGeometry_Geometry_1X_1Y,  //!< Geometry 1X-1Y - Applies to: CoaXPress
        TapGeometry_Geometry_1X_2YE  //!< Geometry 1X-2YE - Applies to: CoaXPress
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

    //! Valid values for TriggerExceededPeriodLimits
    enum TriggerExceededPeriodLimitsEnums
    {
        TriggerExceededPeriodLimits_No,  //!< The input signal frequency hasn't exceeded the maximum frequency defined by the Trigger Output Frequency parameter - Applies to: CoaXPress
        TriggerExceededPeriodLimits_Yes  //!< The input signal frequency has exceeded the maximum frequency defined by the Trigger Output Frequency parameter - Applies to: CoaXPress
    };

    //! Valid values for TriggerFrontOutGPO0Polarity
    enum TriggerFrontOutGPO0PolarityEnums
    {
        TriggerFrontOutGPO0Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerFrontOutGPO0Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerFrontOutGPO1Polarity
    enum TriggerFrontOutGPO1PolarityEnums
    {
        TriggerFrontOutGPO1Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerFrontOutGPO1Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerFrontOutGPO2Polarity
    enum TriggerFrontOutGPO2PolarityEnums
    {
        TriggerFrontOutGPO2Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerFrontOutGPO2Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerFrontOutGPO3Polarity
    enum TriggerFrontOutGPO3PolarityEnums
    {
        TriggerFrontOutGPO3Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerFrontOutGPO3Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
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
        TriggerInSource_GPITriggerSource0,  //!< Trigger Source is set to  GPI 0 - Applies to: CoaXPress
        TriggerInSource_GPITriggerSource1,  //!< Trigger Source is set to  GPI 1 - Applies to: CoaXPress
        TriggerInSource_GPITriggerSource2,  //!< Trigger Source is set to  GPI 2 - Applies to: CoaXPress
        TriggerInSource_GPITriggerSource3,  //!< Trigger Source is set to  GPI 3 - Applies to: CoaXPress
        TriggerInSource_GPITriggerSource4,  //!< Trigger Source is set to GPI  4  Not available on LightBridge - Applies to: CoaXPress
        TriggerInSource_GPITriggerSource5,  //!< Trigger Source is set to GPI  5  Not available on LightBridge - Applies to: CoaXPress
        TriggerInSource_GPITriggerSource6,  //!< Trigger Source is set to GPI  6  Not available on LightBridge - Applies to: CoaXPress
        TriggerInSource_GPITriggerSource7,  //!< Trigger Source is set to GPI  7  Not available on LightBridge - Applies to: CoaXPress
        TriggerInSource_TriggerInSourceFrontGPI0,  //!< The trigger input source is set to TriggerInSourceFrontGPI0 - Applies to: CoaXPress
        TriggerInSource_TriggerInSourceFrontGPI1,  //!< The trigger input source is set to TriggerInSourceFrontGPI1 - Applies to: CoaXPress
        TriggerInSource_TriggerInSourceFrontGPI2,  //!< The trigger input source is set to TriggerInSourceFrontGPI2 - Applies to: CoaXPress
        TriggerInSource_TriggerInSourceFrontGPI3  //!< The trigger input source is set to TriggerInSourceFrontGPI3 - Applies to: CoaXPress
    };

    //! Valid values for TriggerInStatisticsPolarity
    enum TriggerInStatisticsPolarityEnums
    {
        TriggerInStatisticsPolarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerInStatisticsPolarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerInStatisticsSource
    enum TriggerInStatisticsSourceEnums
    {
        TriggerInStatisticsSource_GPITriggerSource0,  //!< Trigger Source is set to  GPI 0 - Applies to: CoaXPress
        TriggerInStatisticsSource_GPITriggerSource1,  //!< Trigger Source is set to  GPI 1 - Applies to: CoaXPress
        TriggerInStatisticsSource_GPITriggerSource2,  //!< Trigger Source is set to  GPI 2 - Applies to: CoaXPress
        TriggerInStatisticsSource_GPITriggerSource3,  //!< Trigger Source is set to  GPI 3 - Applies to: CoaXPress
        TriggerInStatisticsSource_GPITriggerSource4,  //!< Trigger Source is set to GPI  4  Not available on LightBridge - Applies to: CoaXPress
        TriggerInStatisticsSource_GPITriggerSource5,  //!< Trigger Source is set to GPI  5  Not available on LightBridge - Applies to: CoaXPress
        TriggerInStatisticsSource_GPITriggerSource6,  //!< Trigger Source is set to GPI  6  Not available on LightBridge - Applies to: CoaXPress
        TriggerInStatisticsSource_GPITriggerSource7,  //!< Trigger Source is set to GPI  7  Not available on LightBridge - Applies to: CoaXPress
        TriggerInStatisticsSource_TriggerInSourceFrontGPI0,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 0 - Applies to: CoaXPress
        TriggerInStatisticsSource_TriggerInSourceFrontGPI1,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 1 - Applies to: CoaXPress
        TriggerInStatisticsSource_TriggerInSourceFrontGPI2,  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 2 - Applies to: CoaXPress
        TriggerInStatisticsSource_TriggerInSourceFrontGPI3  //!< The input source of the trigger statistics is set to Front GPI Trigger Source 3 - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutFrontGPO0Source
    enum TriggerOutFrontGPO0SourceEnums
    {
        TriggerOutFrontGPO0Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO0Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutFrontGPO1Source
    enum TriggerOutFrontGPO1SourceEnums
    {
        TriggerOutFrontGPO1Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO1Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutFrontGPO2Source
    enum TriggerOutFrontGPO2SourceEnums
    {
        TriggerOutFrontGPO2Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO2Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutFrontGPO3Source
    enum TriggerOutFrontGPO3SourceEnums
    {
        TriggerOutFrontGPO3Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutFrontGPO3Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO0Polarity
    enum TriggerOutGPO0PolarityEnums
    {
        TriggerOutGPO0Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO0Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO0Source
    enum TriggerOutGPO0SourceEnums
    {
        TriggerOutGPO0Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO0Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO1Polarity
    enum TriggerOutGPO1PolarityEnums
    {
        TriggerOutGPO1Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO1Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO1Source
    enum TriggerOutGPO1SourceEnums
    {
        TriggerOutGPO1Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO1Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO2Polarity
    enum TriggerOutGPO2PolarityEnums
    {
        TriggerOutGPO2Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO2Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO2Source
    enum TriggerOutGPO2SourceEnums
    {
        TriggerOutGPO2Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO2Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO3Polarity
    enum TriggerOutGPO3PolarityEnums
    {
        TriggerOutGPO3Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO3Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO3Source
    enum TriggerOutGPO3SourceEnums
    {
        TriggerOutGPO3Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO3Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO4Polarity
    enum TriggerOutGPO4PolarityEnums
    {
        TriggerOutGPO4Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO4Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO4Source
    enum TriggerOutGPO4SourceEnums
    {
        TriggerOutGPO4Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO4Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO5Polarity
    enum TriggerOutGPO5PolarityEnums
    {
        TriggerOutGPO5Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO5Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO5Source
    enum TriggerOutGPO5SourceEnums
    {
        TriggerOutGPO5Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO5Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO6Polarity
    enum TriggerOutGPO6PolarityEnums
    {
        TriggerOutGPO6Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO6Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO6Source
    enum TriggerOutGPO6SourceEnums
    {
        TriggerOutGPO6Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO6Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO7Polarity
    enum TriggerOutGPO7PolarityEnums
    {
        TriggerOutGPO7Polarity_HighActive,  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to High Active - Applies to: CoaXPress
        TriggerOutGPO7Polarity_LowActive  //!< The trigger polarity of the input specified by the Statistics Source parameter is set to Low Active - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutGPO7Source
    enum TriggerOutGPO7SourceEnums
    {
        TriggerOutGPO7Source_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam1Exsync,  //!< The Exsync signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam1Exsync2,  //!< The Exsync2 signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam1Flash,  //!< The flash signal of cam 1 is set  as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam1FrameValid,  //!< The frame valid signal of cam 1 is set as input   - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam1LineValid,  //!< The line valid signal of cam 1 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam2Exsync,  //!< The Exsync signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam2Exsync2,  //!< The Exsync2 signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam2Flash,  //!< The flash signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam2FrameValid,  //!< The frame valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam2LineValid,  //!< The line valid signal of cam 2 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam3Exsync,  //!< The Exsync signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam3Exsync2,  //!< The Exsync2 signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam3Flash,  //!< The flash signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam3FrameValid,  //!< The frame valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam3LineValid,  //!< The line valid signal of cam 3 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam4Exsync,  //!< The Exsync signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam4Exsync2,  //!< The Exsync2 signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam4Flash,  //!< The flash signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam4FrameValid,  //!< The frame valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalCam4LineValid,  //!< The line valid signal of cam 4 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalExsync,  //!< The Exsync signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalExsync2,  //!< The Exsync2 signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalFlash,  //!< The flash signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalFrameValid,  //!< The frame valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalFrontGPI0,  //!< The front GPI 0 signal as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalFrontGPI1,  //!< The front GPI 1 signal as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalFrontGPI2,  //!< The front GPI 2 signal as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalFrontGPI3,  //!< The front GPI 3 signal as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI0,  //!< The GPI 0 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI1,  //!< The GPI 1 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI2,  //!< The GPI 2 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI3,  //!< The GPI 3 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI4,  //!< The GPI 4 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI5,  //!< The GPI 5 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI6,  //!< The GPI 6 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalGPI7,  //!< The GPI 7 signal is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_SignalLineValid,  //!< The line valid signal of cam 0 is set as input - Applies to: CoaXPress
        TriggerOutGPO7Source_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectFrontGPO0
    enum TriggerOutSelectFrontGPO0Enums
    {
        TriggerOutSelectFrontGPO0_BypassFrontGPI0,  //!< The output source is set to BypassFrontGPI0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassFrontGPI1,  //!< The output source is set to BypassFrontGPI1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassFrontGPI2,  //!< The output source is set to BypassFrontGPI2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassFrontGPI3,  //!< The output source is set to BypassFrontGPI3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator0,  //!< The output source is set to CamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator1,  //!< The output source is set to CamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator2,  //!< The output source is set to CamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamAPulseGenerator3,  //!< The output source is set to CamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamBPulseGenerator0,  //!< The output source is set to Cam B Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamBPulseGenerator1,  //!< The output source is set to Cam B Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamBPulseGenerator2,  //!< The output source is set to Cam B Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamBPulseGenerator3,  //!< The output source is set to Cam B Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamCPulseGenerator0,  //!< The output source is set to Cam C Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamCPulseGenerator1,  //!< The output source is set to Cam C Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamCPulseGenerator2,  //!< The output source is set to Cam C Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamCPulseGenerator3,  //!< The output source is set to Cam C Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamDPulseGenerator0,  //!< The output source is set to Cam D Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamDPulseGenerator1,  //!< The output source is set to Cam D Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamDPulseGenerator2,  //!< The output source is set to Cam D Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamDPulseGenerator3,  //!< The output source is set to Cam D Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_GND,  //!< The output source is set to GND - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI0,  //!< The output source is set to NotBypassFrontGPI0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI1,  //!< The output source is set to NotBypassFrontGPI1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI2,  //!< The output source is set to NotBypassFrontGPI2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFronGPI3,  //!< The output source is set to NotBypassFrontGPI3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFrontGPI0,  //!< The output source is set to Not Bypass Front-GPI 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFrontGPI1,  //!< The output source is set to Not Bypass Front-GPI 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFrontGPI2,  //!< The output source is set to Not Bypass Front-GPI 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassFrontGPI3,  //!< The output source is set to Not Bypass Front-GPI 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator0,  //!< The output source is set to NotCamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator1,  //!< The output source is set to NotCamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator2,  //!< The output source is set to NotCamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamAPulseGenerator3,  //!< The output source is set to NotCamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamBPulseGenerator0,  //!< The output source is set to Not Cam B Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamBPulseGenerator1,  //!< The output source is set to Not Cam B Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamBPulseGenerator2,  //!< The output source is set to Not Cam B Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamBPulseGenerator3,  //!< The output source is set to Not Cam B Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamCPulseGenerator0,  //!< The output source is set to Not Cam C Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamCPulseGenerator1,  //!< The output source is set to Not Cam C Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamCPulseGenerator2,  //!< The output source is set to Not Cam C Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamCPulseGenerator3,  //!< The output source is set to Not Cam C Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamDPulseGenerator0,  //!< The output source is set to Not Cam D Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamDPulseGenerator1,  //!< The output source is set to Not Cam D Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamDPulseGenerator2,  //!< The output source is set to Not Cam D Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamDPulseGenerator3,  //!< The output source is set to Not Cam D Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO0_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
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
        TriggerOutSelectFrontGPO1_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator0,  //!< The output source is set to CamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator1,  //!< The output source is set to CamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator2,  //!< The output source is set to CamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamAPulseGenerator3,  //!< The output source is set to CamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamBPulseGenerator0,  //!< The output source is set to Cam B Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamBPulseGenerator1,  //!< The output source is set to Cam B Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamBPulseGenerator2,  //!< The output source is set to Cam B Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamBPulseGenerator3,  //!< The output source is set to Cam B Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamCPulseGenerator0,  //!< The output source is set to Cam C Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamCPulseGenerator1,  //!< The output source is set to Cam C Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamCPulseGenerator2,  //!< The output source is set to Cam C Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamCPulseGenerator3,  //!< The output source is set to Cam C Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamDPulseGenerator0,  //!< The output source is set to Cam D Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamDPulseGenerator1,  //!< The output source is set to Cam D Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamDPulseGenerator2,  //!< The output source is set to Cam D Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamDPulseGenerator3,  //!< The output source is set to Cam D Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_GND,  //!< The output source is set to GND - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI0,  //!< The output source is set to NotBypassFrontGPI0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI1,  //!< The output source is set to NotBypassFrontGPI1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI2,  //!< The output source is set to NotBypassFrontGPI2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFronGPI3,  //!< The output source is set to NotBypassFrontGPI3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFrontGPI0,  //!< The output source is set to Not Bypass Front-GPI 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFrontGPI1,  //!< The output source is set to Not Bypass Front-GPI 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFrontGPI2,  //!< The output source is set to Not Bypass Front-GPI 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassFrontGPI3,  //!< The output source is set to Not Bypass Front-GPI 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator0,  //!< The output source is set to NotCamAPulseGenerator0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator1,  //!< The output source is set to NotCamAPulseGenerator1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator2,  //!< The output source is set to NotCamAPulseGenerator2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamAPulseGenerator3,  //!< The output source is set to NotCamAPulseGenerator3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamBPulseGenerator0,  //!< The output source is set to Not Cam B Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamBPulseGenerator1,  //!< The output source is set to Not Cam B Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamBPulseGenerator2,  //!< The output source is set to Not Cam B Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamBPulseGenerator3,  //!< The output source is set to Not Cam B Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamCPulseGenerator0,  //!< The output source is set to Not Cam C Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamCPulseGenerator1,  //!< The output source is set to Not Cam C Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamCPulseGenerator2,  //!< The output source is set to Not Cam C Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamCPulseGenerator3,  //!< The output source is set to Not Cam C Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamDPulseGenerator0,  //!< The output source is set to Not Cam D Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamDPulseGenerator1,  //!< The output source is set to Not Cam D Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamDPulseGenerator2,  //!< The output source is set to Not Cam D Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamDPulseGenerator3,  //!< The output source is set to Not Cam D Pulse Generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO1_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
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

    //! Valid values for TriggerOutSelectFrontGPO2
    enum TriggerOutSelectFrontGPO2Enums
    {
        TriggerOutSelectFrontGPO2_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO2_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectFrontGPO3
    enum TriggerOutSelectFrontGPO3Enums
    {
        TriggerOutSelectFrontGPO3_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectFrontGPO3_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO0
    enum TriggerOutSelectGPO0Enums
    {
        TriggerOutSelectGPO0_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO0_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO0_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO0_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO0_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO1
    enum TriggerOutSelectGPO1Enums
    {
        TriggerOutSelectGPO1_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO1_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO1_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO1_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO1_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO2
    enum TriggerOutSelectGPO2Enums
    {
        TriggerOutSelectGPO2_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO2_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO2_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO2_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO2_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO3
    enum TriggerOutSelectGPO3Enums
    {
        TriggerOutSelectGPO3_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO3_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO3_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO3_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO3_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO4
    enum TriggerOutSelectGPO4Enums
    {
        TriggerOutSelectGPO4_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO4_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO4_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO4_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO4_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO5
    enum TriggerOutSelectGPO5Enums
    {
        TriggerOutSelectGPO5_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO5_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO5_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO5_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO5_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO6
    enum TriggerOutSelectGPO6Enums
    {
        TriggerOutSelectGPO6_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO6_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO6_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO6_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO6_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutSelectGPO7
    enum TriggerOutSelectGPO7Enums
    {
        TriggerOutSelectGPO7_BypassFrontGPI0,  //!< Bypasses the Front GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassFrontGPI1,  //!< Bypasses the Front GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassFrontGPI2,  //!< Bypasses the Front GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassFrontGPI3,  //!< Bypasses the Front GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI0,  //!< Bypasses the GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI1,  //!< Bypasses the GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI2,  //!< Bypasses the GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI3,  //!< Bypasses the GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI4,  //!< Bypasses the GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI5,  //!< Bypasses the GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI6,  //!< Bypasses the GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_BypassGPI7,  //!< Bypasses the GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamAPulseGenerator0,  //!< The output source is set to camera port A pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamAPulseGenerator1,  //!< The output source is set to camera port A pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamAPulseGenerator2,  //!< The output source is set to camera port A pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamAPulseGenerator3,  //!< The output source is set to camera port A pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamBPulseGenerator0,  //!< The output source is set to camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamBPulseGenerator1,  //!< The output source is set to camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamBPulseGenerator2,  //!< The output source is set to camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamBPulseGenerator3,  //!< The output source is set to camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamCPulseGenerator0,  //!< The output source is set to camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamCPulseGenerator1,  //!< The output source is set to camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamCPulseGenerator2,  //!< The output source is set to camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamCPulseGenerator3,  //!< The output source is set to camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamDPulseGenerator0,  //!< The output source is set to camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamDPulseGenerator1,  //!< The output source is set to camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamDPulseGenerator2,  //!< The output source is set to camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamDPulseGenerator3,  //!< The output source is set to camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamEPulseGenerator0,  //!< The output source is set to camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamEPulseGenerator1,  //!< The output source is set to camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamEPulseGenerator2,  //!< The output source is set to camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_CamEPulseGenerator3,  //!< The output source is set to camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_GND,  //!< The signal is a static zero - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassFrontGPI0,  //!< Bypasses the inverted Front GPI 0 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassFrontGPI1,  //!< Bypasses the inverted Front GPI 1 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassFrontGPI2,  //!< Bypasses the inverted Front GPI 2 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassFrontGPI3,  //!< Bypasses the inverted Front GPI 3 signal directly to the output   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI0,  //!< Bypasses the inverted GPI 0 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI1,  //!< Bypasses the inverted GPI 1 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI2,  //!< Bypasses the inverted GPI 2 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI3,  //!< Bypasses the inverted GPI 3 signal directly to the output - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI4,  //!< Bypasses the inverted GPI 4 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI5,  //!< Bypasses the inverted GPI 5 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI6,  //!< Bypasses the inverted GPI 6 signal directly to the output  Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotBypassGPI7,  //!< Bypasses the inverted GPI 7 signal directly to the output   Not available on LightBridge - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamAPulseGenerator0,  //!< The output source is set to the inverted signal of camera port A pulse generator 0   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamAPulseGenerator1,  //!< The output source is set to the inverted signal of camera port A pulse generator 1   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamAPulseGenerator2,  //!< The output source is set to the inverted signal of camera port A pulse generator 2   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamAPulseGenerator3,  //!< The output source is set to the inverted signal of camera port A pulse generator 3   - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamBPulseGenerator0,  //!< The output source is set to the inverted signal of camera port B pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamBPulseGenerator1,  //!< The output source is set to the inverted signal of camera port B pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamBPulseGenerator2,  //!< The output source is set to the inverted signal of camera port B pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamBPulseGenerator3,  //!< The output source is set to the inverted signal of camera port B pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamCPulseGenerator0,  //!< The output source is set to the inverted signal of camera port C pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamCPulseGenerator1,  //!< The output source is set to the inverted signal of camera port C pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamCPulseGenerator2,  //!< The output source is set to the inverted signal of camera port C pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamCPulseGenerator3,  //!< The output source is set to the inverted signal of camera port C pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamDPulseGenerator0,  //!< The output source is set to the inverted signal of camera port D pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamDPulseGenerator1,  //!< The output source is set to the inverted signal of camera port D pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamDPulseGenerator2,  //!< The output source is set to the inverted signal of camera port D pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamDPulseGenerator3,  //!< The output source is set to the inverted signal of camera port D pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamEPulseGenerator0,  //!< The output source is set to the inverted signal of camera port E pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamEPulseGenerator1,  //!< The output source is set to the inverted signal of camera port E pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamEPulseGenerator2,  //!< The output source is set to the inverted signal of camera port E pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotCamEPulseGenerator3,  //!< The output source is set to the inverted signal of camera port E pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotPulseGenerator0,  //!< The source for the output statistics is set to the inverted signal of pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotPulseGenerator1,  //!< The source for the output statistics is set to the inverted signal of pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotPulseGenerator2,  //!< The source for the output statistics is set to the inverted signal of pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_NotPulseGenerator3,  //!< The source for the output statistics is set to the inverted signal of pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutSelectGPO7_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutSelectGPO7_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutSelectGPO7_PulseGenerator3,  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
        TriggerOutSelectGPO7_VCC  //!< The signal is a static one - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutStatisticsSource
    enum TriggerOutStatisticsSourceEnums
    {
        TriggerOutStatisticsSource_PulseGenerator0,  //!< The source for the output statistics is set to Pulse Generator 0 - Applies to: CoaXPress
        TriggerOutStatisticsSource_PulseGenerator1,  //!< The source for the output statistics is set to Pulse Generator 1 - Applies to: CoaXPress
        TriggerOutStatisticsSource_PulseGenerator2,  //!< The source for the output statistics is set to Pulse Generator 2 - Applies to: CoaXPress
        TriggerOutStatisticsSource_PulseGenerator3  //!< The source for the output statistics is set to Pulse Generator 3 - Applies to: CoaXPress
    };

    //! Valid values for TriggerOutputEventSelect
    enum TriggerOutputEventSelectEnums
    {
        TriggerOutputEventSelect_PulseGenerator0,  //!< The source for the output statistics is set to pulse generator 0 - Applies to: CoaXPress
        TriggerOutputEventSelect_PulseGenerator1,  //!< The source for the output statistics is set to pulse generator 1 - Applies to: CoaXPress
        TriggerOutputEventSelect_PulseGenerator2,  //!< The source for the output statistics is set to pulse generator 2 - Applies to: CoaXPress
        TriggerOutputEventSelect_PulseGenerator3  //!< The source for the output statistics is set to pulse generator 3 - Applies to: CoaXPress
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

    //! Valid values for VantagePoint
    enum VantagePointEnums
    {
        VantagePoint_BottomLeft,  //!< The starting point of the image is the bottom left corner - Applies to: CoaXPress
        VantagePoint_BottomRight,  //!< The starting point of the image is the bottom right corner - Applies to: CoaXPress
        VantagePoint_TopLeft,  //!< The starting point of the image is the top left corner - Applies to: CoaXPress
        VantagePoint_TopRight  //!< The starting point of the image is the top right corner - Applies to: CoaXPress
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalTLParams_Params_v9_0_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for pylon device transport layers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class PYLONBASE_API CUniversalTLParams_Params_v9_0_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalTLParams_Params_v9_0_0( void );

        //! Destructor
        ~CUniversalTLParams_Params_v9_0_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalTLParams_Params_v9_0_0_Data;
        CUniversalTLParams_Params_v9_0_0_Data* m_pCUniversalTLParams_Params_v9_0_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: Version
        //@{
        /*!
            \brief Indicates the revision number of the applet - Applies to: CoaXPress

            Indicates the revision number of the applet. Report this value when contacting the Basler support.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AppletRevision" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AppletRevision;

        //@}


        //! \name Categories: Version
        //@{
        /*!
            \brief Indicates the version number of the applet - Applies to: CoaXPress

            Returns the applet version. Please report the version if you are requesting support.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AppletVersion" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& AppletVersion;

        //@}


        //! \name Categories: Trigger
        //@{
        /*!
            \brief Sets the trigger mode of the area trigger signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AreaTriggerMode" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AreaTriggerModeEnums>& AreaTriggerMode;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Enables/disables automatic control of the pixel format in the device - Applies to: CoaXPress

            Enables/disables automatic control of the pixel format in the device. If enabled, the frame grabber's pixel format and its dependencies are automatically updated to match the camera's pixel format setting.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutomaticFormatControl" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutomaticFormatControl;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Activates or deactivates the automatic control of the ROI in the Device - Applies to: CoaXPress

            Activates or deactivates the automatic control of the ROI in the Device. If this feature is active, the frame grabber ROI is automatically updated to the camera one.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutomaticROIControl" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutomaticROIControl;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Activates or deactivates the automatic control of the Tap Geometry in the Device - Applies to: CoaXPress

            Activates or deactivates the automatic control of the Tap Geometry in the Device. If this feature is active, the frame grabber Tap Geometry is automatically updated to the camera one.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutomaticTapGeometryControl" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutomaticTapGeometryControl;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief Sets the alignment of the bits in the output format - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BitAlignment" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<BitAlignmentEnums>& BitAlignment;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Counts the number of single-byte error corrections in CXP stream packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CameraCorrectedErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CameraCorrectedErrorCount;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief Counts the number of uncorrected errors - Applies to: CoaXPress

            Counts the number of uncorrected errors. Bit[2] indicates multiple byte errors in CXP stream packets.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CameraUncorrectedErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CameraUncorrectedErrorCount;

        //@}


        //! \name Categories: ExtendedDeviceControl and Root
        //@{
        /*!
            \brief Enables sending all commands and receiving all acknowledges twice - Applies to: GigE and blaze

            Enables sending all commands and receiving all acknowledges twice. This option should only be enabled in case of network problems.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CommandDuplicationEnable" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& CommandDuplicationEnable;

        //@}


        //! \name Categories: CompatibilityStatus
        //@{
        /*!
            \brief Automatic ROI control status of the device - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CompatibilityStatusAutomaticRoiControl" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& CompatibilityStatusAutomaticRoiControl;

        //@}


        //! \name Categories: CompatibilityStatus
        //@{
        /*!
            \brief Pixelformat status of the device - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CompatibilityStatusPixelFormat" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& CompatibilityStatusPixelFormat;

        //@}


        //! \name Categories: CompatibilityStatus
        //@{
        /*!
            \brief Tap geometry status of the device - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CompatibilityStatusTapGeometry" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& CompatibilityStatusTapGeometry;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Enables the automatic start of the PylonGigEConnectionGuard - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ConnectionGuardEnable" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ConnectionGuardEnable;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of errors corrected - Applies to: CoaXPress

            Number of errors corrected. This parameter indicates single-byte error correction in CXP stream packets.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CorrectedErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CorrectedErrorCount;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief User-defined bit shift to the right - Applies to: CoaXPress

            User-defined bit shift to the right. This allows you to shift the pixel data in the output format to the right by a value of your choice. The Alignment parameter has to be set to CustomBitShift for this.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CustomBitShiftRight" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CustomBitShiftRight;

        //@}


        //! \name Categories: EventSource
        //@{
        /*!
            \brief Select the signal polarity for the custom signal event 0 - Applies to: CoaXPress

            Select the signal polarity for the custom signal event 0

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CustomSignalEvent0Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CustomSignalEvent0PolarityEnums>& CustomSignalEvent0Polarity;

        //@}


        //! \name Categories: EventSource
        //@{
        /*!
            \brief Select the signal source for the custom signal event 0 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CustomSignalEvent0Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CustomSignalEvent0SourceEnums>& CustomSignalEvent0Source;

        //@}


        //! \name Categories: EventSource
        //@{
        /*!
            \brief Select the signal polarity for the custom signal event 1 - Applies to: CoaXPress

            Select the signal polarity for the custom signal event 1

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CustomSignalEvent1Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CustomSignalEvent1PolarityEnums>& CustomSignalEvent1Polarity;

        //@}


        //! \name Categories: EventSource
        //@{
        /*!
            \brief Select the signal source for the custom signal event 1 - Applies to: CoaXPress

            Select the signal source for the custom signal event 1

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CustomSignalEvent1Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CustomSignalEvent1SourceEnums>& CustomSignalEvent1Source;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts the corrupted frames during acquisition - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpCameraFrameCorruptCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpCameraFrameCorruptCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts the frames that were lost during acquisition and aren't sent into the applet image pipeline - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpCameraFrameLostCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpCameraFrameLostCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts how often the sequence of the CXP stream marker and the header or the line markers were incorrect - Applies to: CoaXPress

            Counts how often the sequence of the CXP stream marker and the header or the line markers were incorrect. The parameter is 13 bit wide, where the bits [11:0] represent the actual counter value and the bit [12] stands for the counter overflow. When the overflow bit is set, the counter value shall be treated as don't care.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpCameraMarkerErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpCameraMarkerErrorCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Detects the error situation in which the first data value after the operator reset was unexpected, i e  no image header has been received - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpCameraUnexpectedStartupDataStatus" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpCameraUnexpectedStartupDataStatusEnums>& CxpCameraUnexpectedStartupDataStatus;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts situations in which an incorrectly formatted acknowledgment for a control packet was received - Applies to: CoaXPress

            Counts situations in which an incorrectly formatted acknowledgment for a control packet was received. Incorrectly formatted means that e.g. the end of packet indicator is missing etc. Range 0 to 8191 (13 bit).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlAckIncompleteCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlAckIncompleteCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlAckIncompleteCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlAckIncompleteCountSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts situations in which a control packet was sent but no acknowledgment packet was received for it yet and the timeout of 200 ms is reached - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlAckLostCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlAckLostCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlAckLostCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlAckLostCountSelector;

        //@}


        //! \name Categories: CrcErrors
        //@{
        /*!
            \brief Returns information whether there were CRC errors in received control acknowledgement packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlAckPacketCrcError" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlAckPacketCrcError;

        //@}


        //! \name Categories: CrcErrors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlAckPacketCrcErrorSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlAckPacketCrcErrorSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts situations in which an acknowledgment for a control packet was received with a tag that doesn't match the expected tag sent in the corresponding request control packet - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlTagErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlTagErrorCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpControlTagErrorCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpControlTagErrorCountSelector;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Counts errors received in packet headers and trailers that were corrected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrected" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrected;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Returns the information whether errors were corrected in received stream acknowledge packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedControlAck" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedControlAck;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedControlAckSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedControlAckSelector;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Returns the information whether errors were corrected in received heartbeat packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedHeartbeat" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedHeartbeat;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedHeartbeatSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedHeartbeatSelector;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Returns the information whether errors were corrected in received link test packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedLinkTest" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedLinkTest;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedLinkTestSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedLinkTestSelector;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedSelector;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Returns the information whether errors were corrected in received stream packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedStream" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedStream;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedStreamSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedStreamSelector;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Returns the information whether errors were corrected in received trigger packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedTrigger" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedTrigger;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief Returns the information whether errors were corrected in received trigger acknowledge packets - Applies to: CoaXPress

            returns the information whether errors were corrected in received trigger acknowledge packets.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedTriggerAck" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedTriggerAck;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedTriggerAckSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedTriggerAckSelector;

        //@}


        //! \name Categories: ReceivedPacketsCorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorCorrectedTriggerSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorCorrectedTriggerSelector;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief Counts errors received in packet headers and trailers that haven't been corrected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrected" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrected;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief Returns information whether there were errors in received control acknowledgement packets that haven't been corrected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedControlAck" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedControlAck;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedControlAckSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedControlAckSelector;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief Returns information whether there were errors in received heartbeat packets that haven't been corrected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedHeartbeat" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedHeartbeat;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedHeartbeatSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedHeartbeatSelector;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief Returns information whether there were errors in received link test packets that haven't been corrected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedLinkTest" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedLinkTest;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedLinkTestSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedLinkTestSelector;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedSelector;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief Returns the information whether there were errors in received stream packets that haven't been corrected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedStream" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedStream;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedStreamSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedStreamSelector;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief Returns the information whether there were errors in received trigger packets that haven't been corrected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedTrigger" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedTrigger;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the information whether there were errors in received trigger acknowledgement packets that haven't been corrected.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedTriggerAck" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedTriggerAck;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedTriggerAckSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedTriggerAckSelector;

        //@}


        //! \name Categories: ReceivedPacketsUncorrected
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpErrorUncorrectedTriggerSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpErrorUncorrectedTriggerSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts the received heartbeat packets that are incomplete, e g  they miss the end of the packet indicator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpHeartbeatIncompleteCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpHeartbeatIncompleteCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpHeartbeatIncompleteCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpHeartbeatIncompleteCountSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts the situations in which heartbeat packets sent by the camera exceeded the timeout (100ms) - Applies to: CoaXPress

            Counts the situations in which heartbeat packets sent by the camera exceeded the timeout (100ms). Bits [11:0] count the amount of violations. Bit [12] is set when a counter overflow occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpHeartbeatMaxPeriodViolationCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpHeartbeatMaxPeriodViolationCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpHeartbeatMaxPeriodViolationCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpHeartbeatMaxPeriodViolationCountSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Returns the number of image tag errors (jumps) in the CXP headers - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpImageTagErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpImageTagErrorCount;

        //@}


        //! \name Categories: BoardStatus
        //@{
        /*!
            \brief Returns the firmware CXP channel, which is currently monitored by the module - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpInputMappedToFWPortPort" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpInputMappedToFWPortPort;

        //@}


        //! \name Categories: BoardStatus
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpInputMappedToFWPortPortSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpInputMappedToFWPortPortSelector;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Sets the link configuration for the communication between the receiver and transmitter device - Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkConfiguration" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkConfigurationEnums>& CxpLinkConfiguration;

        //@}


        //! \name Categories: CameraOutSignalMapping and CameraTriggerSource
        //@{
        /*!
            \brief Sets the output source for CXP LinkTrigger0 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger0Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger0SourceEnums>& CxpLinkTrigger0Source;

        //@}


        //! \name Categories: CameraTriggerSource
        //@{
        /*!
            \brief Selects the signal edge of the output signal on CXP LinkTrigger0 - Applies to: CoaXPress

            Selects the signal edge of the output signal on CXPLinkTrigger0.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger0SourceEdge" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger0SourceEdgeEnums>& CxpLinkTrigger0SourceEdge;

        //@}


        //! \name Categories: CameraOutSignalMapping and CameraTriggerSource
        //@{
        /*!
            \brief Sets the output source for CXP LinkTrigger1 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger1Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger1SourceEnums>& CxpLinkTrigger1Source;

        //@}


        //! \name Categories: CameraTriggerSource
        //@{
        /*!
            \brief Selects the signal edge of the output signal on CXP LinkTrigger1 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger1SourceEdge" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger1SourceEdgeEnums>& CxpLinkTrigger1SourceEdge;

        //@}


        //! \name Categories: CameraOutSignalMapping and CameraTriggerSource
        //@{
        /*!
            \brief Sets the output source for CXP LinkTrigger2 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger2Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger2SourceEnums>& CxpLinkTrigger2Source;

        //@}


        //! \name Categories: CameraTriggerSource
        //@{
        /*!
            \brief Selects the signal edge of the output signal on CXP LinkTrigger2 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger2SourceEdge" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger2SourceEdgeEnums>& CxpLinkTrigger2SourceEdge;

        //@}


        //! \name Categories: CameraOutSignalMapping and CameraTriggerSource
        //@{
        /*!
            \brief Sets the output source for CXP LinkTrigger3 - Applies to: CoaXPress

            Sets the output source CXP LinkTrigger3.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger3Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger3SourceEnums>& CxpLinkTrigger3Source;

        //@}


        //! \name Categories: CameraTriggerSource
        //@{
        /*!
            \brief Selects the signal edge of the output signal on CXP LinkTrigger3 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkTrigger3SourceEdge" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkTrigger3SourceEdgeEnums>& CxpLinkTrigger3SourceEdge;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts the trigger requests that were skipped, because the transmitter was still busy by sending the previous trigger packet - Applies to: CoaXPress

            Counts the trigger requests that were skipped, because the transmitter was still busy by sending the previous trigger packet. Bit 12 indicates an overflow.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpOvertriggerRequestPulseCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpOvertriggerRequestPulseCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpOvertriggerRequestPulseCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpOvertriggerRequestPulseCountSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts how often the received stream ID value in the stream packets mismatches the stream ID value specified in the image header - Applies to: CoaXPress

            Counts how often the received stream ID value in the stream packets mismatches the stream ID value specified in the image header. The parameter is 13 bit wide, where the bits [11:0] represent the actual counter value and the bit [12] stands for the counter overflow.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpStreamIDErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpStreamIDErrorCount;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Counts the amount of received stream packets - Applies to: CoaXPress

            Counts the amount of received stream packets. Bits [29:0] count the number of packets. Bit [30] is set when a counter overflow occurs.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpStreamPacketCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpStreamPacketCount;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpStreamPacketCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpStreamPacketCountSelector;

        //@}


        //! \name Categories: CrcErrors
        //@{
        /*!
            \brief Returns information whether there were CRC errors in received stream packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpStreamPacketCrcError" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpStreamPacketCrcError;

        //@}


        //! \name Categories: CrcErrors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpStreamPacketCrcErrorSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpStreamPacketCrcErrorSelector;

        //@}


        //! \name Categories: LengthErrors
        //@{
        /*!
            \brief Returns information whether a length error in the stream packets was detected - Applies to: CoaXPress

            Returns information whether a length error in the stream packets was detected. Range: 0 (NO) to 1 (YES).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpStreamPacketLengthError" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpStreamPacketLengthError;

        //@}


        //! \name Categories: LengthErrors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpStreamPacketLengthErrorSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpStreamPacketLengthErrorSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Counts the situations in which a trigger packet was sent, but no acknowledgment packet was received for it yet, which then led to a timeout - Applies to: CoaXPress

            Counts the situations in which a trigger packet was sent, but no acknowledgment packet was received for it yet, which then led to a timeout. Bits [11:0] count the amount of violations. Bit [12] is set when a counter overflow occurs. Range 0 to 8191 (13 bit).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpTriggerAckMissingCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpTriggerAckMissingCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpTriggerAckMissingCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpTriggerAckMissingCountSelector;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief Returns information whether an event packet was received while using a CXP standard less than 2 0 - Applies to: CoaXPress

            Returns information whether an event packet was received while using a CXP standard less than 2.0. Range: 0 (NO) to 1 (YES).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedEventReceived" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedEventReceived;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedEventReceivedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedEventReceivedSelector;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief Returns information whether a GPIO acknowledgment was received while using a CXP standard higher than 1 0 - Applies to: CoaXPress

            Returns information whether a GPIO acknowledgment was received while using a CXP standard higher than 1.0. Range: 0 (NO) to 1 (YES).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedGpioAckReceived" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedGpioAckReceived;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedGpioAckReceivedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedGpioAckReceivedSelector;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief Returns information whether a GPIO packet was received while using a CXP standard higher than 1 0 - Applies to: CoaXPress

            Returns information whether a GPIO packet was received while using a CXP standard higher than 1.0. Range: 0 (NO) to 1 (YES).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedGpioReceived" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedGpioReceived;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedGpioReceivedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedGpioReceivedSelector;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief Returns information whether a GPIO request from VisualApplets was received while using a CXP standard higher than 1 0 - Applies to: CoaXPress

            Returns information whether a GPIO request from VisualApplets was received while using a CXP standard higher than 1.0. Range: 0 (NO) to 1 (YES).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedGpioRequestReceived" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedGpioRequestReceived;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedGpioRequestReceivedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedGpioRequestReceivedSelector;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief Returns information whether a heartbeat packet was received while using a CXP standard less than 2 0 - Applies to: CoaXPress

            Returns information whether a heartbeat packet was received while using a CXP standard less than 2.0. Range: 0 (NO) to 1 (YES).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedHeartbeatReceived" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedHeartbeatReceived;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpUnsupportedHeartbeatReceivedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpUnsupportedHeartbeatReceivedSelector;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Returns the device's access status at the moment when the Device Update List command was last executed - Applies to: CoaXPress and blaze

            Returns the device's access status at the moment when the Device Update List command was last executed. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceAccessStatus" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceAccessStatusEnums>& DeviceAccessStatus;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief User-friendly name of the device - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceDisplayName" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceDisplayName;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Sets the endianness handling mode - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceEndianessMechanism" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceEndianessMechanismEnums>& DeviceEndianessMechanism;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Interface-wide unique ID of the selected device - Applies to: CoaXPress and blaze

            Interface-wide unique ID of the selected device. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceID" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceID;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Additional information about the manufacturer of the device - Applies to: blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManufacturerInfo" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceManufacturerInfo;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Name of the device model - Applies to: CoaXPress and blaze

            Name of the device model. This value only changes when the Device Update List command is executed.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceModelName" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceModelName;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Serial number of the remote device - Applies to: blaze

            Serial number of the remote device. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSerialNumber" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceSerialNumber;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Returns the transport layer of the device - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceType" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceTypeEnums>& DeviceType;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Name of the device vendor - Applies to: CoaXPress and blaze

            Name of the device vendor. This value only changes when the Device Update List command is executed.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceVendorName" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceVendorName;

        //@}


        //! \name Categories: GPIState
        //@{
        /*!
            \brief Read digital input - Applies to: CoaXPress

            Read the current state of all digital inputs. You can read the current state of these inputs using this parameter. LSB Bit 0 of the read value represents input 0, bit 1 represents input 1 and so on. Bits 0 to 7 use GPI 0 to 7. Front GPI 0 to 3 are represented by bits 8 to 11.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DigitalInput" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DigitalInput;

        //@}


        //! \name Categories: EventAcquisitionTriggerData
        //@{
        /*!
            \brief AcquisitionTrigger - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventAcquisitionTrigger" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventAcquisitionTrigger;

        //@}


        //! \name Categories: EventAcquisitionTriggerData
        //@{
        /*!
            \brief AcquisitionTrigger SoftCounter - Applies to: CoaXPress

            Software counter for event 'AcquisitionTrigger'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventAcquisitionTriggerSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventAcquisitionTriggerSoftCounter;

        //@}


        //! \name Categories: EventAcquisitionTriggerData
        //@{
        /*!
            \brief AcquisitionTrigger Timestamp - Applies to: CoaXPress

            Timestamp of event 'AcquisitionTrigger'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventAcquisitionTriggerTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventAcquisitionTriggerTimestamp;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatus" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCameraStreamStatus;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus Corrupted - Applies to: CoaXPress

            Event loss for type Corrupted occurred.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusCorrupted" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EventCameraStreamStatusCorrupted;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus EventType - Applies to: CoaXPress

            Event type (Corrupted or Lost)

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusEventType" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EventCameraStreamStatusEventType;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus FrameId - Applies to: CoaXPress

            Frame ID in which the event occurred.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusFrameId" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCameraStreamStatusFrameId;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus Lost - Applies to: CoaXPress

            Event loss for type Lost occurred.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusLost" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EventCameraStreamStatusLost;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus LostAmount - Applies to: CoaXPress

            Amount of lost Lost events.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusLostAmount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCameraStreamStatusLostAmount;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus SoftCounter - Applies to: CoaXPress

            Software counter for event 'CameraStreamStatus'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCameraStreamStatusSoftCounter;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus StreamId - Applies to: CoaXPress

            Stream ID in which the event occurred.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusStreamId" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCameraStreamStatusStreamId;

        //@}


        //! \name Categories: EventCameraStreamStatusData
        //@{
        /*!
            \brief CameraStreamStatus Timestamp - Applies to: CoaXPress

            Timestamp of event 'CameraStreamStatus'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventCameraStreamStatusTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventCameraStreamStatusTimestamp;

        //@}


        //! \name Categories: EventDeviceLostData
        //@{
        /*!
            \brief Returns the unique identifier of the Device Lost event - Applies to: CoaXPress and blaze

            Returns the unique Identifier of the Device Lost event.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventDeviceLost" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventDeviceLost;

        //@}


        //! \name Categories: EventDeviceLostData
        //@{
        /*!
            \brief DeviceLost SoftCounter - Applies to: CoaXPress

            Software counter for event 'DeviceLost'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventDeviceLostSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventDeviceLostSoftCounter;

        //@}


        //! \name Categories: EventFrameTransferEndData
        //@{
        /*!
            \brief FrameTransferEnd - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTransferEnd" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTransferEnd;

        //@}


        //! \name Categories: EventFrameTransferEndData
        //@{
        /*!
            \brief FrameTransferEnd SoftCounter - Applies to: CoaXPress

            Software counter for event 'FrameTransferEnd'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTransferEndSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTransferEndSoftCounter;

        //@}


        //! \name Categories: EventFrameTransferEndData
        //@{
        /*!
            \brief FrameTransferEnd Timestamp - Applies to: CoaXPress

            Timestamp of event 'FrameTransferEnd'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTransferEndTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTransferEndTimestamp;

        //@}


        //! \name Categories: EventFrameTransferStartData
        //@{
        /*!
            \brief FrameTransferStart - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTransferStart" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTransferStart;

        //@}


        //! \name Categories: EventFrameTransferStartData
        //@{
        /*!
            \brief FrameTransferStart SoftCounter - Applies to: CoaXPress

            Software counter for event 'FrameTransferStart'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTransferStartSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTransferStartSoftCounter;

        //@}


        //! \name Categories: EventFrameTransferStartData
        //@{
        /*!
            \brief FrameTransferStart Timestamp - Applies to: CoaXPress

            Timestamp of event 'FrameTransferStart'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTransferStartTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTransferStartTimestamp;

        //@}


        //! \name Categories: EventFrameTriggerMissedData
        //@{
        /*!
            \brief FrameTriggerMissed - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTriggerMissed" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTriggerMissed;

        //@}


        //! \name Categories: EventFrameTriggerMissedData
        //@{
        /*!
            \brief FrameTriggerMissed SoftCounter - Applies to: CoaXPress

            Software counter for event 'FrameTriggerMissed'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTriggerMissedSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTriggerMissedSoftCounter;

        //@}


        //! \name Categories: EventFrameTriggerMissedData
        //@{
        /*!
            \brief FrameTriggerMissed Timestamp - Applies to: CoaXPress

            Timestamp of event 'FrameTriggerMissed'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTriggerMissedTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventFrameTriggerMissedTimestamp;

        //@}


        //! \name Categories: EventLineTransferEndData
        //@{
        /*!
            \brief LineTransferEnd - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventLineTransferEnd" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventLineTransferEnd;

        //@}


        //! \name Categories: EventLineTransferEndData
        //@{
        /*!
            \brief LineTransferEnd SoftCounter - Applies to: CoaXPress

            Software counter for event 'LineTransferEnd'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventLineTransferEndSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventLineTransferEndSoftCounter;

        //@}


        //! \name Categories: EventLineTransferEndData
        //@{
        /*!
            \brief LineTransferEnd Timestamp - Applies to: CoaXPress

            Timestamp of event 'LineTransferEnd'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventLineTransferEndTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventLineTransferEndTimestamp;

        //@}


        //! \name Categories: EventLineTransferStartData
        //@{
        /*!
            \brief LineTransferStart - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventLineTransferStart" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventLineTransferStart;

        //@}


        //! \name Categories: EventLineTransferStartData
        //@{
        /*!
            \brief LineTransferStart SoftCounter - Applies to: CoaXPress

            Software counter for event 'LineTransferStart'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventLineTransferStartSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventLineTransferStartSoftCounter;

        //@}


        //! \name Categories: EventLineTransferStartData
        //@{
        /*!
            \brief LineTransferStart Timestamp - Applies to: CoaXPress

            Timestamp of event 'LineTransferStart'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventLineTransferStartTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventLineTransferStartTimestamp;

        //@}


        //! \name Categories: EventControl
        //@{
        /*!
            \brief Sets whether the host application is notified of the selected event - Applies to: CoaXPress and blaze


            Visibility: Expert

            Selected by: EventSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventNotification" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<EventNotificationEnums>& EventNotification;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflow" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverflow;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow FrameId - Applies to: CoaXPress

            Camera frame-ID for area scan applets or grabber frame-ID for line scan applets.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflowFrameId" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverflowFrameId;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow Is Complete - Applies to: CoaXPress

            Frame is complete.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflowIsComplete" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EventOverflowIsComplete;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow Is End of Sequence - Applies to: CoaXPress

            Marks the end of a sequence.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflowIsEndOfSequence" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EventOverflowIsEndOfSequence;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow Is Lost - Applies to: CoaXPress

            Frame is lost.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflowIsLost" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EventOverflowIsLost;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow Is Truncated - Applies to: CoaXPress

            Frame is truncated.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflowIsTruncated" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EventOverflowIsTruncated;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow SoftCounter - Applies to: CoaXPress

            Software counter for event 'Overflow'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflowSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverflowSoftCounter;

        //@}


        //! \name Categories: EventOverflowData
        //@{
        /*!
            \brief Overflow Timestamp - Applies to: CoaXPress

            Timestamp of event 'Overflow'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverflowTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventOverflowTimestamp;

        //@}


        //! \name Categories: EventControl
        //@{
        /*!
            \brief Sets which event to signal to the host application - Applies to: CoaXPress and blaze


            Visibility: Expert

            Selecting Parameters: EventNotification

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<EventSelectorEnums>& EventSelector;

        //@}


        //! \name Categories: EventTriggerExceededPeriodLimitsData
        //@{
        /*!
            \brief TriggerExceededPeriodLimits - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerExceededPeriodLimits" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerExceededPeriodLimits;

        //@}


        //! \name Categories: EventTriggerExceededPeriodLimitsData
        //@{
        /*!
            \brief TriggerExceededPeriodLimits SoftCounter - Applies to: CoaXPress

            Software counter for event 'TriggerExceededPeriodLimits'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerExceededPeriodLimitsSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerExceededPeriodLimitsSoftCounter;

        //@}


        //! \name Categories: EventTriggerExceededPeriodLimitsData
        //@{
        /*!
            \brief TriggerExceededPeriodLimits Timestamp - Applies to: CoaXPress

            Timestamp of event 'TriggerExceededPeriodLimits'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerExceededPeriodLimitsTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerExceededPeriodLimitsTimestamp;

        //@}


        //! \name Categories: EventTriggerQueueFilllevelThresholdOffData
        //@{
        /*!
            \brief TriggerQueueFilllevelThresholdOff - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerQueueFilllevelThresholdOff" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerQueueFilllevelThresholdOff;

        //@}


        //! \name Categories: EventTriggerQueueFilllevelThresholdOffData
        //@{
        /*!
            \brief TriggerQueueFilllevelThresholdOff SoftCounter - Applies to: CoaXPress

            Software counter for event 'TriggerQueueFilllevelThresholdOff'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerQueueFilllevelThresholdOffSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerQueueFilllevelThresholdOffSoftCounter;

        //@}


        //! \name Categories: EventTriggerQueueFilllevelThresholdOffData
        //@{
        /*!
            \brief TriggerQueueFilllevelThresholdOff Timestamp - Applies to: CoaXPress

            Timestamp of event 'TriggerQueueFilllevelThresholdOff'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerQueueFilllevelThresholdOffTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerQueueFilllevelThresholdOffTimestamp;

        //@}


        //! \name Categories: EventTriggerQueueFilllevelThresholdOnData
        //@{
        /*!
            \brief TriggerQueueFilllevelThresholdOn - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerQueueFilllevelThresholdOn" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerQueueFilllevelThresholdOn;

        //@}


        //! \name Categories: EventTriggerQueueFilllevelThresholdOnData
        //@{
        /*!
            \brief TriggerQueueFilllevelThresholdOn SoftCounter - Applies to: CoaXPress

            Software counter for event 'TriggerQueueFilllevelThresholdOn'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerQueueFilllevelThresholdOnSoftCounter" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerQueueFilllevelThresholdOnSoftCounter;

        //@}


        //! \name Categories: EventTriggerQueueFilllevelThresholdOnData
        //@{
        /*!
            \brief TriggerQueueFilllevelThresholdOn Timestamp - Applies to: CoaXPress

            Timestamp of event 'TriggerQueueFilllevelThresholdOn'

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTriggerQueueFilllevelThresholdOnTimestamp" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& EventTriggerQueueFilllevelThresholdOnTimestamp;

        //@}


        //! \name Categories: LineTriggerExSync
        //@{
        /*!
            \brief Enables or disables the ExSync output to the camera - Applies to: CoaXPress

            Enables or disables the ExSync output to the camera. Make sure that the camera is expecting this signal and interprets it in the expected way. The polarity of this signal is relevant for proper functionality.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExSyncOn" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExSyncOnEnums>& ExSyncOn;

        //@}


        //! \name Categories: ExSyncOutput
        //@{
        /*!
            \brief Sets the polarity of the ExSync output signal - Applies to: CoaXPress

            Sets the polarity of the ExSync output signal. Adjusts the polarity of the Exsync signal genarator to the polarity accepted by the connected camera. Use LowActive, if the camera starts exposure on a falling edge, otherwise use HighActive.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExSyncPolarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExSyncPolarityEnums>& ExSyncPolarity;

        //@}


        //! \name Categories: GpioConfiguration
        //@{
        /*!
            \brief Sets the configuration type of the extension GPIO interface - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExtensionGPOType" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ExtensionGPOTypeEnums>& ExtensionGPOType;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Current buffer fill level - Applies to: CoaXPress

            Current buffer fill level. This value allows you to check whether the average input bandwidth of the camera is too high to be processed by the applet.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FillLevel" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FillLevel;

        //@}


        //! \name Categories: ImageTriggerFlash
        //@{
        /*!
            \brief Switches the flash signal on or off - Applies to: CoaXPress

            Switches the flash signal on or off. The pulse width of the flash signal is equal to one line period. The flash gives a signal between the first and second Exsync rising edge. A single trigger is sent for a full frame.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FlashOn" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FlashOnEnums>& FlashOn;

        //@}


        //! \name Categories: Flash
        //@{
        /*!
            \brief Sets the generated flash signal polarity - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FlashPolarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FlashPolarityEnums>& FlashPolarity;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief Sets the pixel format of the image that is output to the computer - Applies to: CoaXPress

            Sets the pixel format of the image that is output to the computer. The data is converted from the internal bit width and color format to the output format selected. This setting is not related to the pixel format input from the camera sensor. For more information, see the Pixel Format parameter documentation.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Format" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FormatEnums>& Format;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Current input signal levels of all front GPI inputs (bit mask) - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrontGPI" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrontGPI;

        //@}


        //! \name Categories: GpioConfiguration
        //@{
        /*!
            \brief Sets the pull control of the front GPI - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrontGPIPullControl" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FrontGPIPullControlEnums>& FrontGPIPullControl;

        //@}


        //! \name Categories: GpioConfiguration
        //@{
        /*!
            \brief Sets the signal type of the front GPI - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrontGPISignalType" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FrontGPISignalTypeEnums>& FrontGPISignalType;

        //@}


        //! \name Categories: GpioConfiguration
        //@{
        /*!
            \brief Enables or disables the inversion of the front GPO - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrontGPOInversion" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<FrontGPOInversionEnums>& FrontGPOInversion;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief The digital input at GPI - Applies to: CoaXPress

            The current input signal levels of all GPI inputs (bitmask).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GPI" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GPI;

        //@}


        //! \name Categories: Gentl
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Ignore the FG output format and manage it internally in the GenTL producer

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GentlInfoIgnorefgformat" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& GentlInfoIgnorefgformat;

        //@}


        //! \name Categories: Gentl
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Version of the GenTL description Interface in the applet.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GentlInfoVersion" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& GentlInfoVersion;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Current gateway IP address of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceGateway" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceGateway;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Current IP address of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceIPAddress" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceIPAddress;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief 48-bit MAC address of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceMACAddress" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceMACAddress;

        //@}


        //! \name Categories: DeviceInformation
        //@{
        /*!
            \brief Current subnet mask of the GVCP interface of the remote device - Applies to: blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceSubnetMask" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceSubnetMask;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Heartbeat timeout value on the host side in milliseconds - Applies to: GigE

            Heartbeat timeout value on the host side in milliseconds. This parameter is linked with the Heartbeat Timeout camera parameter. If the camera parameter changes, the host parameter changes accordingly, and vice versa.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=HeartbeatTimeout" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& HeartbeatTimeout;

        //@}


        //! \name Categories: ROI
        //@{
        /*!
            \brief Height of the image ROI on the host side - Applies to: CoaXPress

            Height of the image ROI on the host side. This parameter is linked with the Height camera parameter. If the camera parameter changes, the host parameter changes accordingly, but not vice versa. The host parameter should not be set to a value different from the camera parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Height" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Height;

        //@}


        //! \name Categories: ImageSelector
        //@{
        /*!
            \brief Defines which image of an image sequence is grabbed - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageSelect" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ImageSelect;

        //@}


        //! \name Categories: ImageSelector
        //@{
        /*!
            \brief Selects the length of an image sequence - Applies to: CoaXPress

            Selects the length of an image sequence. Only one single image of the sequence is grabbed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageSelectPeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ImageSelectPeriod;

        //@}


        //! \name Categories: ImageTriggerFlash
        //@{
        /*!
            \brief The total image height in lines in case of multi buffer mode - Applies to: CoaXPress

            The total image height in lines in case of multi buffer mode. Only relevant if a Multibuffer image trigger mode is used.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerAsyncHeight" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ImageTriggerAsyncHeight;

        //@}


        //! \name Categories: ImageTriggerInput
        //@{
        /*!
            \brief The debouncing time of the input image trigger - Applies to: CoaXPress

            The debouncing time of the input image trigger. Signals must keep the same state during the debounce time to be detected as such. Fast signal changes within the debounce time are filtered out.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerDebouncing" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ImageTriggerDebouncing;

        //@}


        //! \name Categories: ImageTriggerInput
        //@{
        /*!
            \brief The delay of the image gate in lines with respect to ExSync - Applies to: CoaXPress

            The delay of the image gate in lines with respect to ExSync. The image trigger is delayed by a defined number of lines.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerGateDelay" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ImageTriggerGateDelay;

        //@}


        //! \name Categories: ImageTriggerInput
        //@{
        /*!
            \brief Sets the image trigger input signal polarity - Applies to: CoaXPress

            Sets the polarity of the image trigger input.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerInputPolarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageTriggerInputPolarityEnums>& ImageTriggerInputPolarity;

        //@}


        //! \name Categories: ImageTriggerInput
        //@{
        /*!
            \brief Sets the image trigger input signal source - Applies to: CoaXPress

            Sets the image trigger input signal source, which is used to trigger the image acquisition. This is only relevant if the Image Trigger Mode is set to Extern/Gate.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerInputSource" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageTriggerInputSourceEnums>& ImageTriggerInputSource;

        //@}


        //! \name Categories: ImageTriggerFlash
        //@{
        /*!
            \brief Checks whether the image trigger is busy - Applies to: CoaXPress

            With this read-only value it is possible to check whether the image trigger is busy, i.e. whether an image is currently being acquired. During this time an additional image trigger is ignored.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerIsBusy" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageTriggerIsBusyEnums>& ImageTriggerIsBusy;

        //@}


        //! \name Categories: ImageTriggerFlash
        //@{
        /*!
            \brief Sets the trigger mode for image generation - Applies to: CoaXPress

            Sets the trigger mode for the image generation. An image trigger can define the start and length of an image. FreeRun: All incoming lines received from the camera are accepted. Image size is defined by the ROI. ASync_External_Trigger: At the rising edge of an accepted image trigger input signal, a new frame is started and incoming lines are appended to an image up to ROI-Height. A new rising edge of the image trigger is only accepted after the current frame is finished. Gated_External_Trigger: In gated mode, the input signal active state Sets the height of the resulting frame. ROI-Height is the maximum height. _Multibuffer modes can handle a certain number of lines for multiple frames of ROI size.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerMode" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageTriggerModeEnums>& ImageTriggerMode;

        //@}


        //! \name Categories: ImageTriggerFlash
        //@{
        /*!
            \brief Enables or disables the image trigger module - Applies to: CoaXPress

            Enables or disables the image trigger module. The OFF state corresponds to FreeRun.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ImageTriggerOn" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ImageTriggerOnEnums>& ImageTriggerOn;

        //@}


        //! \name Categories: Downscale
        //@{
        /*!
            \brief The downscale factor of the line trigger input signal - Applies to: CoaXPress

            The downscale factor of the line trigger input signal. Specifies the number of external input trigger signals, which are needed to generate a single Exsync. This is only relevant if the TriggerMode is set to an external ASync_trigger mode.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineDownscale" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LineDownscale;

        //@}


        //! \name Categories: Downscale
        //@{
        /*!
            \brief The phase of downscaling - Applies to: CoaXPress

            The phase of the downscaling with respect to the image gate. Specifies the number of external input signals, which are needed to generate the first Exsync of a frame. Exsync is used to trigger lines. This is only relevant if the TriggerMode is set to ASync_Trigger_Gated.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineDownscaleInit" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LineDownscaleInit;

        //@}


        //! \name Categories: ExSyncOutput
        //@{
        /*!
            \brief The length of the ExSync signal pulse - Applies to: CoaXPress

            The length of the ExSync signal pulse. This parameter specifies the pulse width of the Exsync signal, which can be used by many cameras as externally defined exposure time. With this parameter it is possible to adjust the exposure time during runtime via software, even while grabbing.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineExposure" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LineExposure;

        //@}


        //! \name Categories: ExSyncOutput
        //@{
        /*!
            \brief The length of the ExSync period - Applies to: CoaXPress

            The length of the ExSync period. This parameter defines the line frequency when using the grabber controlled mode to send a trigger signal to the connected camera. The value of the line period needs to be greater than the line delay.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LinePeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LinePeriod;

        //@}


        //! \name Categories: LineTriggerInput
        //@{
        /*!
            \brief Specifies the debouncing time of the line trigger signal - Applies to: CoaXPress

            Specifies the debouncing time of the input line trigger, events, IO forwards and analyzers. The signals must keep the same state during the debounce time to be detected as such. Fast signal changes within the debounce time will be filtered out.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineTriggerDebouncing" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LineTriggerDebouncing;

        //@}


        //! \name Categories: ExSyncOutput
        //@{
        /*!
            \brief The delay of the ExSync signal with respect to the trigger input signal - Applies to: CoaXPress

            The delay of the ExSync signal with respect to the trigger input signal. Specifies the delay of the generated ExSync signal, with respect to an external trigger input. The resulting ExSync2 signal is a delayed clone of the ExSync. Polarity, period, etc. are the same as for ExSync. The line delay needs to be less than the line period even for external trigger modes where the internal line period is not used.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineTriggerDelay" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LineTriggerDelay;

        //@}


        //! \name Categories: LineTriggerInput
        //@{
        /*!
            \brief Sets the polarity of the external line trigger signal - Applies to: CoaXPress

            Sets the polarity of the external input trigger signal encoder source A and source B. When set to LowActive, the Exsync generator starts on a falling edge of the signal specified as frame trigger. Otherwise, the Exsync generation starts on a rising edge. This is only relevant if the TriggerMode is set to Extern_Trigger.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineTriggerInPolarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineTriggerInPolarityEnums>& LineTriggerInPolarity;

        //@}


        //! \name Categories: LineTriggerInput
        //@{
        /*!
            \brief Sets the line trigger input source - Applies to: CoaXPress

            Sets the trigger input signal source for the ExSync generation. This signal is also interpreted as source A when using a shaft encoder. This is only relevant, if the TriggerMode is set to ASync_Trigger.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineTriggerInSource" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineTriggerInSourceEnums>& LineTriggerInSource;

        //@}


        //! \name Categories: LineTriggerExSync
        //@{
        /*!
            \brief Sets the operation mode for the Exsync signal generation - Applies to: CoaXPress

            Sets the operation mode for the Exsync signal generation. The source for the external trigger input can be selected via the parameters SourceA and SourceB. Grabber_Controlled: Exsync is generated periodically by the internal signal generator. ASync_Trigger: Each external trigger signal from a peripheral device is used to generate an ExSync based on the defined exposure time. Grabber_Controlled_Gated: Exsync is generated periodically by the internal signal generator during the acquisition of a frame. Extern_Trigger_Gated: An external trigger signal from a peripheral device is used to generate the ExSync during the acquisition of a frame only.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineTriggerMode" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LineTriggerModeEnums>& LineTriggerMode;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Specifies maximum number of tries before failing the control channel commands - Applies to: blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LinkCommandRetryCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LinkCommandRetryCount;

        //@}


        //! \name Categories: DeviceControl
        //@{
        /*!
            \brief Specifies application timeout for the control channel communication - Applies to: blaze

            Specifies application timeout for the control channel communication. Up to DeviceLinkCommandRetryCount attempts with this timeout are made before a command fails with a timeout error.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LinkCommandTimeout" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& LinkCommandTimeout;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Filename with custom lookup table values - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutCustomFile" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& LutCustomFile;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Switch the LUT and processing functionality on or off - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutEnable" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LutEnableEnums>& LutEnable;

        //@}


        //! \name Categories: AppletProperties
        //@{
        /*!
            \brief Type of lookup table implementation - Applies to: CoaXPress

            Type of LUT implementation.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutImplementationType" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LutImplementationTypeEnums>& LutImplementationType;

        //@}


        //! \name Categories: AppletProperties
        //@{
        /*!
            \brief The pixel's bit depth at the lookup table input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutInputPixelBitDepth" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutInputPixelBitDepth;

        //@}


        //! \name Categories: AppletProperties
        //@{
        /*!
            \brief The pixel's bit depth at the lookup table output - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutOutputPixelBitDepth" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutOutputPixelBitDepth;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Save current lookup table configuration - Applies to: CoaXPress

            Save current LUT configuration.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutSaveFile" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& LutSaveFile;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Set the type of the lookup table: Custom values or applet processor - Applies to: CoaXPress

            Enables the LUT to be loaded with custom values or uses the applet's processor.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutType" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<LutTypeEnums>& LutType;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Field with lookup table values - Applies to: CoaXPress

            Field with LUT Values.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValue" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValue;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Field with blue lookup table values - Applies to: CoaXPress

            Field with blue LUT Values.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValueBlue" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValueBlue;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValueBlueSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValueBlueSelector;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Field with green looup table values - Applies to: CoaXPress

            Field with green LUT Values.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValueGreen" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValueGreen;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValueGreenSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValueGreenSelector;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief Field with red lookup table values - Applies to: CoaXPress

            Field with red LUT Values.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValueRed" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValueRed;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValueRedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValueRedSelector;

        //@}


        //! \name Categories: LookupTable
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LutValueSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& LutValueSelector;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum number of retries for read operations after a read operation has timed out - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxRetryCountRead" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaxRetryCountRead;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum number of retries for write operations after a write operation has timed out - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxRetryCountWrite" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaxRetryCountWrite;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Enables mapping of certain SFNC 1 x node names to SFNC 2 x node names - Applies to: GigE and USB

            Enables mapping of certain SFNC 1.x node names to SFNC 2.x node names. This allows you to write code for camera devices that are compatible with different SFNC (Standard Features Naming Convention) versions. Available for USB camera devices only.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MigrationModeEnable" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& MigrationModeEnable;

        //@}


        //! \name Categories: OutStatistics
        //@{
        /*!
            \brief Returns whether missing frames are reported - Applies to: CoaXPress

            Returns whether missing frames are reported. If no frame is received for a trigger pulse, the parameter is set to Yes.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MissingCameraFrameResponse" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<MissingCameraFrameResponseEnums>& MissingCameraFrameResponse;

        //@}


        //! \name Categories: OutStatistics
        //@{
        /*!
            \brief Clears the Missing Camera Frame Response parameter - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MissingCameraFrameResponseClear" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::ICommandEx& MissingCameraFrameResponseClear;

        //@}


        //! \name Categories: ROI
        //@{
        /*!
            \brief Acquisition ROI x-offset, independent of the camera ROI - Applies to: CoaXPress

            X-offset of the acquisition ROI, independent of the camera ROI.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OffsetX" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& OffsetX;

        //@}


        //! \name Categories: ROI
        //@{
        /*!
            \brief Acquisition ROI y-offset, independent of the camera ROI - Applies to: CoaXPress

            Y-offset of the acquisition ROI, independent of the camera ROI.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OffsetY" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& OffsetY;

        //@}


        //! \name Categories: ImageFormatControl
        //@{
        /*!
            \brief Automatically outputs packed formats instead of unpacked ones - Applies to: CoaXPress

            Automatically outputs packed formats instead of unpacked ones. This parameter is only available if the Automatic Format Control parameter is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OutputPackedFormats" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& OutputPackedFormats;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Indicates whether the image buffer is currently in overflow state - Applies to: CoaXPress

            Indicates whether if the image buffer is currently in overflow state. An overflow results in the loss of images. The parameter is reset at each readout cycle.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Overflow" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Overflow;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Sets the content of the overflow event - Applies to: CoaXPress

            An overflow event can be generated on each incomplete, lost or correct frame. With this enumeration, you can select which permutation of these three events is reported via overflow event.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverflowEventSelect" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<OverflowEventSelectEnums>& OverflowEventSelect;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Overflow handling will be inactive once the buffer filllevel is below this value - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverflowOffThreshold" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& OverflowOffThreshold;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Overflow handling will be active once the buffer filllevel is above this value  Frames will be interrupted - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverflowOnThreshold" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& OverflowOnThreshold;

        //@}


        //! \name Categories: BufferStatus
        //@{
        /*!
            \brief Overflow handling will be active once the buffer filllevel is above this value, after the currently active frame is completed - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OverflowSyncOnThreshold" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& OverflowSyncOnThreshold;

        //@}


        //! \name Categories: CoaXPress and Errors
        //@{
        /*!
            \brief Number of packet errors - Applies to: CoaXPress

            Number of packet errors. This parameter indicates that CXP stream packets are lost.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PacketTagErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PacketTagErrorCount;

        //@}


        //! \name Categories: OutputFormat
        //@{
        /*!
            \brief Applet-internal processing bit depth - Applies to: CoaXPress

            Applet-internal processing bit depth. This is the maximum bit depth at which pixels are processed. If you select a highter output and input bit depth, data may be truncated.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelDepth" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PixelDepth;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Sets the format of the pixel data transmitted by the camera - Applies to: CoaXPress

            Sets the format of the pixel data transmitted by the camera. This setting has to match the pixel format set in the camera.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelFormat" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PixelFormatEnums>& PixelFormat;

        //@}


        //! \name Categories: Processing
        //@{
        /*!
            \brief Gain correction value - Applies to: CoaXPress

            Gain correction value. Available when LUT functionality is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ProcessingGain" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ProcessingGain;

        //@}


        //! \name Categories: Processing
        //@{
        /*!
            \brief Gamma correction value - Applies to: CoaXPress

            Gamma correction value. Available when LUT functionality is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ProcessingGamma" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ProcessingGamma;

        //@}


        //! \name Categories: Processing
        //@{
        /*!
            \brief Invert output - Applies to: CoaXPress

            Invert output. Available when LUT functionality is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ProcessingInvert" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ProcessingInvertEnums>& ProcessingInvert;

        //@}


        //! \name Categories: Processing
        //@{
        /*!
            \brief Offset correction value - Applies to: CoaXPress

            Offset correction value. Available when LUT functionality is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ProcessingOffset" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ProcessingOffset;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Read access timeout value in milliseconds - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReadTimeout" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ReadTimeout;

        //@}


        //! \name Categories: WhiteBalance
        //@{
        /*!
            \brief The blue gain of the white balancing - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ScalingFactorBlue" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ScalingFactorBlue;

        //@}


        //! \name Categories: WhiteBalance
        //@{
        /*!
            \brief The green gain of the white balancing - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ScalingFactorGreen" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ScalingFactorGreen;

        //@}


        //! \name Categories: WhiteBalance
        //@{
        /*!
            \brief The red gain of the white balancing - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ScalingFactorRed" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& ScalingFactorRed;

        //@}


        //! \name Categories: SoftwareTrigger
        //@{
        /*!
            \brief Sends a software trigger pulse - Applies to: CoaXPress

            Sends a software trigger pulse or adds pulses to the trigger queue if it is enabled.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SendSoftwareTrigger" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SendSoftwareTrigger;

        //@}


        //! \name Categories: SensorGeometry
        //@{
        /*!
            \brief The height of the sensor - Applies to: CoaXPress

            The sensor height in selected tap geometry. The value is ignored, if vantage point = TopLeft. Available DRAM and SensorWidth limit the maximum SensorHeight.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorHeight" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SensorHeight;

        //@}


        //! \name Categories: SensorGeometry
        //@{
        /*!
            \brief The width of the sensor - Applies to: CoaXPress

            The sensor width in selected tap geometry. The value is ignored if, Vantage Point = Top-Left. Available DRAM and SensorHeight limit the maximum SensorWidth.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorWidth" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SensorWidth;

        //@}


        //! \name Categories: SoftwareTrigger
        //@{
        /*!
            \brief Turns software trigger signal on or off - Applies to: CoaXPress

            Turns software trigger signal on or off. With this parameter a software gate can be produced in case of an externally gated image trigger mode.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SetSoftwareTrigger" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SetSoftwareTriggerEnums>& SetSoftwareTrigger;

        //@}


        //! \name Categories: ShaftEncoderABFilter
        //@{
        /*!
            \brief Reads or writes the current compensation count - Applies to: CoaXPress

            Reads or writes the current compensation count. Value 0 refers to no compensation. You can reset the compensator by writing 0 to the parameter. Is based on a 20-bit counter enabling a backward movement of up to 1048576 steps.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderCompensationCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ShaftEncoderCompensationCount;

        //@}


        //! \name Categories: ShaftEncoderABFilter
        //@{
        /*!
            \brief Enables or disables the shaft encoder rollback compensation - Applies to: CoaXPress

            Enables or disables the shaft encoder rollback compensation. This parameter is relevant in case of a shaft encoder AB configuration. If switched to ON, in case of shaft encoder backward movement, the operator counts how many shaft encoder steps the shaft encoder moves backwards. When the shaft encoder moves forwards again, this number of shaft encoder steps (now forward direction) is not transmitted as external trigger signals. Only after the transportation belt is back to the place where the backward movement started, the shaft encoder steps (forward direction) are transmitted as external trigger signals again. If switched to OFF, the operator simply doesn't transmit any trigger signals as long as the transportation belt moves backwards. As soon as the transport belt starts to move forwards again, the operator transmits the shaft encoder steps (forward direction) as trigger signals.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderCompensationEnable" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderCompensationEnableEnums>& ShaftEncoderCompensationEnable;

        //@}


        //! \name Categories: ShaftEncoderABFilter
        //@{
        /*!
            \brief Sets the input signal source for the shaft encoder (source B) - Applies to: CoaXPress

            Sets the trigger input signal source for the ExSync generation. This signal is also interpreted as source B when using a shaft encoder. This is only relevant if the TriggerMode is set to ASync_Trigger.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderInputSource" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderInputSourceEnums>& ShaftEncoderInputSource;

        //@}


        //! \name Categories: ShaftEncoderABFilter
        //@{
        /*!
            \brief Sets the direction for the shaft encoder - Applies to: CoaXPress

            Sets the leading signal / direction for the shaft encoder. A foreward movement is defined by a rising edge of signal A before signal B, if the parameter is set to Signal_AB. Source_A: Forward is defined by A before B. Source_B: Forward is defined by B before A.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderLeading" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderLeadingEnums>& ShaftEncoderLeading;

        //@}


        //! \name Categories: ShaftEncoderABFilter
        //@{
        /*!
            \brief Sets the shaft encoder mode - Applies to: CoaXPress

            Sets the shaft encoder mode. Filter_x1: Exsync is generated for a forward rotation of the shaft encoder in single resolution, i.e., a trigger pulse for a rising edge of LineTrgInSourceA. Filter_x2: Exsync is generated for a forward rotation of the shaft encoder in double resolution, i.e., a trigger pulse for a rising edge of LineTrgInSourceA and a rising edge of LineTrgInSourceB. Filter_x4: Exsync is generated for a forward rotation of the shaft encoder in quad resolution, i.e., a trigger pulse for a rising and a falling edge of LineTrgInSourceA and a rising and a falling edge of LineTrgInSourceB.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderMode" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderModeEnums>& ShaftEncoderMode;

        //@}


        //! \name Categories: ShaftEncoderABFilter
        //@{
        /*!
            \brief Enables or disables the shaft encoder - Applies to: CoaXPress

            Enables or disbales the shaft encoder. Sets whether a single trigger input (off = A only) is used for the Exsync generation, or the signals A and B (on).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ShaftEncoderOn" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<ShaftEncoderOnEnums>& ShaftEncoderOn;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the current period of signal analyzer 0 - Applies to: CoaXPress

            Returns the last measured period of the selected source and polarity.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer0CurrentPeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SignalAnalyzer0CurrentPeriod;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the maximum period of signal analyzer 0 - Applies to: CoaXPress

            Returns the maximum measured period of the selected source and polarity after reset.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer0MaxPeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SignalAnalyzer0MaxPeriod;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the minimum period of signal analyzer 0 - Applies to: CoaXPress

            Returns the minimum measured period of the selected source and polarity after reset.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer0MinPeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SignalAnalyzer0MinPeriod;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Sets the signal analyzer 0 polarity - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer0Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SignalAnalyzer0PolarityEnums>& SignalAnalyzer0Polarity;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the pulse count of signal analyzer 0 - Applies to: CoaXPress

            Returns the number of rising edges e.g. pulses of the selected source and of the polarity after reset.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer0PulseCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SignalAnalyzer0PulseCount;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Sets the signal analyzer 0 source - Applies to: CoaXPress

            Sets the signal source analyzer module 0.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer0Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SignalAnalyzer0SourceEnums>& SignalAnalyzer0Source;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the current period of signal analyzer 1 - Applies to: CoaXPress

            Returns the last measured period of the selected source and polarity.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer1CurrentPeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SignalAnalyzer1CurrentPeriod;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the maximum period of signal analyzer 1 - Applies to: CoaXPress

            Returns the maximum measured period of the selected source and the polarity after reset.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer1MaxPeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SignalAnalyzer1MaxPeriod;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the minimum period of signal analyzer 1 - Applies to: CoaXPress

            Returns the minimum measured period of the selected source and the polarity after reset.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer1MinPeriod" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SignalAnalyzer1MinPeriod;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Sets the signal analyzer 1 polarity - Applies to: CoaXPress

            Sets the signal analyzer module 0 polarity.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer1Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SignalAnalyzer1PolarityEnums>& SignalAnalyzer1Polarity;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Returns the pulse count of signal analyzer 1 - Applies to: CoaXPress

            Returns the number of rising edges e.g. pulses of the selected source and polarity after reset.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer1PulseCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SignalAnalyzer1PulseCount;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Sets the signal source analyzer module 0 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzer1Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SignalAnalyzer1SourceEnums>& SignalAnalyzer1Source;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief Clears the signal analyzer results - Applies to: CoaXPress

            Clears all measurement results.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzerClear" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::ICommandEx& SignalAnalyzerClear;

        //@}


        //! \name Categories: SignalAnalyzer
        //@{
        /*!
            \brief The pulse count difference between signal analyzer 0 and 1 - Applies to: CoaXPress

            Use this read-only parameter to check the difference of the signal analyzer 0 and 1 pulse counter values (Analyzer 0 - Analyzer 1 value). This can be used to check for lost trigger signals, if analyzer 0 counts the ExSyc pulses and analyzer 1 counts the returned camera lines. In this case the difference is between 0 and 1 for single line cameras with no extra delay.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SignalAnalyzerPulseCountDifference" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SignalAnalyzerPulseCountDifference;

        //@}


        //! \name Categories: SoftwareTrigger
        //@{
        /*!
            \brief Indicates whether the software trigger is busy - Applies to: CoaXPress

            Indicates whether the software trigger is busy. This allows you to find out whether the trigger system is still processing software trigger pulses.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareTriggerIsBusy" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SoftwareTriggerIsBusyEnums>& SoftwareTriggerIsBusy;

        //@}


        //! \name Categories: SoftwareTrigger
        //@{
        /*!
            \brief Number of pulses in queue to be processed - Applies to: CoaXPress

            Number of pulses in queue to be processed. The Queue parameter needs to be enabled for this.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareTriggerQueueFillLevel" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SoftwareTriggerQueueFillLevel;

        //@}


        //! \name Categories: ExtendedDeviceControl and Root
        //@{
        /*!
            \brief Number of timeouts during read and write operations when waiting for a response from the device - Applies to: GigE and blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StatisticReadWriteTimeoutCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StatisticReadWriteTimeoutCount;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Last error status of a read or write operation - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Error_Status" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Last_Error_Status;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Last error status of a read or write operation - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Error_Status_Text" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& Statistic_Last_Error_Status_Text;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of failed read operations - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Read_Operations_Failed_Count" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Read_Operations_Failed_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of read pipe resets - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Read_Pipe_Reset_Count" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Read_Pipe_Reset_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of failed write operations - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Write_Operations_Failed_Count" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Write_Operations_Failed_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of write pipe resets - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Write_Pipe_Reset_Count" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Write_Pipe_Reset_Count;

        //@}


        //! \name Categories: StreamEnumeration
        //@{
        /*!
            \brief User-friendly name of the selected stream - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamDisplayName" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& StreamDisplayName;

        //@}


        //! \name Categories: StreamEnumeration
        //@{
        /*!
            \brief Device-wide unique ID of the data stream - Applies to: CoaXPress and blaze


            Visibility: Beginner

            Selected by: StreamSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamID" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& StreamID;

        //@}


        //! \name Categories: StreamEnumeration
        //@{
        /*!
            \brief Sets the stream channel - Applies to: CoaXPress and blaze

            Sets the stream channel. The parameter is 0-based in order to match the index of the C interface.

            Visibility: Beginner

            Selecting Parameters: StreamID

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamSelector;

        //@}


        //! \name Categories: ImageTriggerInput
        //@{
        /*!
            \brief The delay of the flash signal with respect to the image trigger input signal - Applies to: CoaXPress

            The delay of the flash signal in lines with respect to the image trigger input signal with respect to ExSync.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StrobePulseDelay" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StrobePulseDelay;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Byte Alignment 8b10b locked

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorByteAlignment8b10bLocked" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SystemmonitorByteAlignment8b10bLockedEnums>& SystemmonitorByteAlignment8b10bLocked;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorByteAlignment8b10bLockedSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorByteAlignment8b10bLockedSelector;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the Channel Current.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelCurrent" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorChannelCurrent;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelCurrentSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorChannelCurrentSelector;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the Channel Voltage.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelVoltage" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorChannelVoltage;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorChannelVoltageSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorChannelVoltageSelector;

        //@}


        //! \name Categories: BoardStatus and Miscellaneous
        //@{
        /*!
            \brief Returns the current PCIe link speed in Gigabits per second - Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorCurrentLinkSpeed" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorCurrentLinkSpeed;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief The current transfer mode used by the camera: area scan or line scan - Applies to: CoaXPress

            This parameter informs about the current transfer mode used by the camera. The transfer mode can be an area scan (= 0) or line scan (= 1) image.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorCxpImageLineMode" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorCxpImageLineMode;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Returns the version of the used CXP standard - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorCxpStandard" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorCxpStandard;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorCxpStandardSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorCxpStandardSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Link stability counter  It is incremented when the number of measured symbols received by the channel transceiver are not in 8b10b encoding or/and have wrong disparity - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorDecoder8b10bError" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorDecoder8b10bError;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorDecoder8b10bErrorSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorDecoder8b10bErrorSelector;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Disparity 8b 10b errors

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorDisparity8b10bError" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorDisparity8b10bError;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Shows the external power state of the board.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorExternalPower" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SystemmonitorExternalPowerEnums>& SystemmonitorExternalPower;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA die temperature.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaTemperature" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaTemperature;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA auxiliary Vcc.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaVccAux" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaVccAux;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA BRAM Vcc.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaVccBram" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaVccBram;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the current FPGA internal Vcc.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorFpgaVccInt" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorFpgaVccInt;

        //@}


        //! \name Categories: BoardStatus
        //@{
        /*!
            \brief Indicates the frame grabber port mapping - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorMappedToFgPort" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorMappedToFgPort;

        //@}


        //! \name Categories: BoardStatus
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorMappedToFgPortSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorMappedToFgPortSelector;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Not in table 8b 10b errors

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorNotInTable8b10bError" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorNotInTable8b10bError;

        //@}


        //! \name Categories: CoaXPress and Errors
        //@{
        /*!
            \brief Number of packet buffer overflows - Applies to: CoaXPress

            The number of overflows that occur due to a not correct package order.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPacketbufferOverflowCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorPacketbufferOverflowCount;

        //@}


        //! \name Categories: CoaXPress and Errors
        //@{
        /*!
            \brief The source of packet buffer overflows - Applies to: CoaXPress

            The port, which has overflows due to a not correct package order.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPacketbufferOverflowSource" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorPacketbufferOverflowSource;

        //@}


        //! \name Categories: BoardStatus and Miscellaneous
        //@{
        /*!
            \brief Returns the PCIe packet size that was evaluated during the training period at boot-time - Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPcieTrainedPayloadSize" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorPcieTrainedPayloadSize;

        //@}


        //! \name Categories: BoardStatus and Miscellaneous
        //@{
        /*!
            \brief Returns the size (in bytes) of the PCIe packets payload that are used for the data transmission between the frame grabber and the PCIe bridge - Applies to: CoaXPress


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPcieTrainedRequestSize" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorPcieTrainedRequestSize;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Returns the port bit rate

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPortBitRate" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& SystemmonitorPortBitRate;

        //@}


        //! \name Categories: Miscellaneous
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Shows the current power over CXP state.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorPowerOverCxpState" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<SystemmonitorPowerOverCxpStateEnums>& SystemmonitorPowerOverCxpState;

        //@}


        //! \name Categories: LengthErrors
        //@{
        /*!
            \brief Counts how often the length of a CXP packet doesn't correspond to what is specified in the header and returns the number of length errors - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxLengthErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxLengthErrorCount;

        //@}


        //! \name Categories: LengthErrors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxLengthErrorCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxLengthErrorCountSelector;

        //@}


        //! \name Categories: CrcErrors
        //@{
        /*!
            \brief Returns the number of received packet CRC errors   - Applies to: CoaXPress

            Returns the number of received packet CRC errors.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxPacketCrcErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxPacketCrcErrorCount;

        //@}


        //! \name Categories: CrcErrors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxPacketCrcErrorCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxPacketCrcErrorCountSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Returns the number of received incomplete stream counts - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxStreamIncompleteCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxStreamIncompleteCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxStreamIncompleteCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxStreamIncompleteCountSelector;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief Returns the number of received unknown data, i e  packets received that aren't defined in the CXP standard - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxUnknownDataReceivedCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxUnknownDataReceivedCount;

        //@}


        //! \name Categories: Errors
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxUnknownDataReceivedCountSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxUnknownDataReceivedCountSelector;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief Returns the number of received unsupported packets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxUnsupportedPacketUnit" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxUnsupportedPacketUnit;

        //@}


        //! \name Categories: UnsupportedPackets
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorRxUnsupportedPacketUnitSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorRxUnsupportedPacketUnitSelector;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Returns the stream packet size in bytes - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorStreamPacketSize" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorStreamPacketSize;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief  Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorStreamPacketSizeSelector" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorStreamPacketSizeSelector;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of used connections - Applies to: CoaXPress

            The currently used number of CXP ports used in this process.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SystemmonitorUsedCxpConnections" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SystemmonitorUsedCxpConnections;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief  Applies to: CoaXPress

            Select the tap geometry according to the GenICam SFNC.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TapGeometry" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TapGeometryEnums>& TapGeometry;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of trigger acknowledgement packets sent by the camera have been received by the frame grabber - Applies to: CoaXPress

            Number of trigger acknowledgement packets sent by the camera (in response to trigger edge packets sent before) have been received by the frame grabber.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerAcknowledgementCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerAcknowledgementCount;

        //@}


        //! \name Categories: CameraOutSignalMapping
        //@{
        /*!
            \brief Sets the output source to be connected to a camera signal channel - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerCameraOutSelect" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerCameraOutSelectEnums>& TriggerCameraOutSelect;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of trigger events sent to the camera - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerEventCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerEventCount;

        //@}


        //! \name Categories: OutStatistics
        //@{
        /*!
            \brief Returns whether the  input signal frequency exceeded the maximum specified - Applies to: CoaXPress

            Returns whether the  input signal frequency exceeded the maximum specified. If the parameter returns Yes, signals were dropped.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerExceededPeriodLimits" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerExceededPeriodLimitsEnums>& TriggerExceededPeriodLimits;

        //@}


        //! \name Categories: OutStatistics
        //@{
        /*!
            \brief Clears the Trigger Exceeded Period Limits parameter - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerExceededPeriodLimitsClear" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TriggerExceededPeriodLimitsClear;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 0 signal polarity - Applies to: CoaXPress

            Sets the front GPO 0 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerFrontOutGPO0Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerFrontOutGPO0PolarityEnums>& TriggerFrontOutGPO0Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 1 signal polarity - Applies to: CoaXPress

            Sets the front GPO 1 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerFrontOutGPO1Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerFrontOutGPO1PolarityEnums>& TriggerFrontOutGPO1Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 2 signal polarity - Applies to: CoaXPress

            Sets the front GPO 2 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerFrontOutGPO2Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerFrontOutGPO2PolarityEnums>& TriggerFrontOutGPO2Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 3 signal polarity - Applies to: CoaXPress

            Sets the front GPO 3 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerFrontOutGPO3Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerFrontOutGPO3PolarityEnums>& TriggerFrontOutGPO3Polarity;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Input debounce time for trigger input signals (in microseconds) - Applies to: CoaXPress

            Input debounce time for trigger input signals (in microseconds). This parameter allows you to filter out invalid signals by specifying a minimum signal length.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInDebounce" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerInDebounce;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Factor by which the trigger input signal is downscaled - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInDownscale" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerInDownscale;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInDownscalePhase" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerInDownscalePhase;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Sets the polarity of the trigger input signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInPolarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerInPolarityEnums>& TriggerInPolarity;

        //@}


        //! \name Categories: External
        //@{
        /*!
            \brief Sets the trigger input source - Applies to: CoaXPress

            Sets the trigger input source for external trigger mode.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInSource" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerInSourceEnums>& TriggerInSource;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Current frequency of the input pulses - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsFrequency" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerInStatisticsFrequency;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Maximum input frequency detected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsMaximumFrequency" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerInStatisticsMaximumFrequency;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Clears the minimum and maximum frequency values - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsMinMaxFrequencyClear" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TriggerInStatisticsMinMaxFrequencyClear;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Minimum input frequency detected - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsMinimumFrequency" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerInStatisticsMinimumFrequency;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Sets the polarity of the trigger input signal for statistics - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsPolarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerInStatisticsPolarityEnums>& TriggerInStatisticsPolarity;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Number of input pulses - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsPulseCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerInStatisticsPulseCount;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Clears the input signal pulse counter - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsPulseCountClear" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TriggerInStatisticsPulseCountClear;

        //@}


        //! \name Categories: InStatistics
        //@{
        /*!
            \brief Sets the input source for statistics - Applies to: CoaXPress

            Sets the trigger input source for statistics.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerInStatisticsSource" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerInStatisticsSourceEnums>& TriggerInStatisticsSource;

        //@}


        //! \name Categories: Sequencer
        //@{
        /*!
            \brief Upscales, i e , duplicates, the number of trigger pulses generated externally or via software with the period specified by the Trigger Output Frequency parameter - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerMultiplyPulses" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerMultiplyPulses;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 0 signal source - Applies to: CoaXPress

            Sets the signal source for the front GPO 0 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutFrontGPO0Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutFrontGPO0SourceEnums>& TriggerOutFrontGPO0Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 1 signal source - Applies to: CoaXPress

            Sets the signal source for the front GPO 1 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutFrontGPO1Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutFrontGPO1SourceEnums>& TriggerOutFrontGPO1Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 2 signal source - Applies to: CoaXPress

            Sets the signal source for the front GPO 2 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutFrontGPO2Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutFrontGPO2SourceEnums>& TriggerOutFrontGPO2Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the front GPO 3 signal source - Applies to: CoaXPress

            Sets the signal source for the front GPO 3 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutFrontGPO3Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutFrontGPO3SourceEnums>& TriggerOutFrontGPO3Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 0 signal polarity - Applies to: CoaXPress

            Sets the GPO 0 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO0Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO0PolarityEnums>& TriggerOutGPO0Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 0 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 0 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO0Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO0SourceEnums>& TriggerOutGPO0Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 1 signal polarity - Applies to: CoaXPress

            Sets the GPO 1 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO1Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO1PolarityEnums>& TriggerOutGPO1Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 1 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 1 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO1Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO1SourceEnums>& TriggerOutGPO1Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 2 signal polarity - Applies to: CoaXPress

            Sets the GPO 2 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO2Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO2PolarityEnums>& TriggerOutGPO2Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 2 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 2 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO2Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO2SourceEnums>& TriggerOutGPO2Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 3 signal polarity - Applies to: CoaXPress

            Sets the GPO 3 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO3Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO3PolarityEnums>& TriggerOutGPO3Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 3 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 3 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO3Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO3SourceEnums>& TriggerOutGPO3Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 4 signal polarity - Applies to: CoaXPress

            Sets the GPO 4 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO4Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO4PolarityEnums>& TriggerOutGPO4Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 4 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 4 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO4Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO4SourceEnums>& TriggerOutGPO4Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 5 signal polarity - Applies to: CoaXPress

            Sets the GPO 5 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO5Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO5PolarityEnums>& TriggerOutGPO5Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 5 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 5 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO5Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO5SourceEnums>& TriggerOutGPO5Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 6 signal polarity - Applies to: CoaXPress

            Sets the GPO 6 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO6Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO6PolarityEnums>& TriggerOutGPO6Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 6 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 6 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO6Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO6SourceEnums>& TriggerOutGPO6Source;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets the GPO 7 signal polarity - Applies to: CoaXPress

            Sets the GPO 7 signal polarity. This parameter is ignored if the source is VCC or GND.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO7Polarity" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO7PolarityEnums>& TriggerOutGPO7Polarity;

        //@}


        //! \name Categories: GPO
        //@{
        /*!
            \brief Sets GPO 7 signal source - Applies to: CoaXPress

            Sets the signal source for GPO 7 output.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutGPO7Source" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutGPO7SourceEnums>& TriggerOutGPO7Source;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of Front GPO 0 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectFrontGPO0" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectFrontGPO0Enums>& TriggerOutSelectFrontGPO0;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of Front GPO 1 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectFrontGPO1" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectFrontGPO1Enums>& TriggerOutSelectFrontGPO1;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of Front GPO 2 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectFrontGPO2" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectFrontGPO2Enums>& TriggerOutSelectFrontGPO2;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of Front GPO 3 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectFrontGPO3" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectFrontGPO3Enums>& TriggerOutSelectFrontGPO3;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 0 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO0" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO0Enums>& TriggerOutSelectGPO0;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 1 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO1" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO1Enums>& TriggerOutSelectGPO1;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 2 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO2" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO2Enums>& TriggerOutSelectGPO2;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 3 - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO3" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO3Enums>& TriggerOutSelectGPO3;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 4 - Applies to: CoaXPress

            Sets the output source of GPO 4.  This parameter is not available on Light Bridge.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO4" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO4Enums>& TriggerOutSelectGPO4;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 5 - Applies to: CoaXPress

            Sets the output source of GPO 5.  This parameter is not available on Light Bridge.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO5" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO5Enums>& TriggerOutSelectGPO5;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 6 - Applies to: CoaXPress

            Sets the output source of GPO 6.  This parameter is not available on Light Bridge.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO6" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO6Enums>& TriggerOutSelectGPO6;

        //@}


        //! \name Categories: DigitalOutput
        //@{
        /*!
            \brief Sets the output source of GPO 7 - Applies to: CoaXPress

            Sets the output source of GPO 7.  This parameter is not available on Light Bridge.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutSelectGPO7" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutSelectGPO7Enums>& TriggerOutSelectGPO7;

        //@}


        //! \name Categories: OutStatistics
        //@{
        /*!
            \brief Number of output pulses - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutStatisticsPulseCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerOutStatisticsPulseCount;

        //@}


        //! \name Categories: OutStatistics
        //@{
        /*!
            \brief Clears the output signal pulse counter - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutStatisticsPulseCountClear" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::ICommandEx& TriggerOutStatisticsPulseCountClear;

        //@}


        //! \name Categories: OutStatistics
        //@{
        /*!
            \brief Sets the output source for statistics - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutStatisticsSource" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutStatisticsSourceEnums>& TriggerOutStatisticsSource;

        //@}


        //! \name Categories: OutputEvents
        //@{
        /*!
            \brief Select the pulse form generator for event monitoring - Applies to: CoaXPress

            Select the pulse form generator for event monitoring.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutputEventSelect" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerOutputEventSelectEnums>& TriggerOutputEventSelect;

        //@}


        //! \name Categories: Trigger
        //@{
        /*!
            \brief Maximum trigger output frequency - Applies to: CoaXPress

            Maximum trigger output frequency. If the internal generator is used, it will use the frequency specified there. If an external source is used, this value determines the maximum allowed value. External trigger signals exceeding this value will be discarded. For more information, see the applet documentation.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerOutputFrequency" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerOutputFrequency;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0Delay" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator0Delay;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0Downscale" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator0Downscale;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0DownscalePhase" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator0DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator0
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator0Width" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator0Width;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1Delay" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator1Delay;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1Downscale" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator1Downscale;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1DownscalePhase" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator1DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator1
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator1Width" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator1Width;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2Delay" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator2Delay;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2Downscale" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator2Downscale;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2DownscalePhase" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator2DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator2
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator2Width" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator2Width;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Delay between the input and the output of the pulse form generator - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3Delay" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator3Delay;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Downscale factor at the pulse form generator input - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3Downscale" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator3Downscale;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Phase for selecting the desired pulse in the sequence - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3DownscalePhase" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerPulseFormGenerator3DownscalePhase;

        //@}


        //! \name Categories: PulseFormGenerator3
        //@{
        /*!
            \brief Width of the output signal - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerPulseFormGenerator3Width" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IFloatEx& TriggerPulseFormGenerator3Width;

        //@}


        //! \name Categories: Queue
        //@{
        /*!
            \brief Fill level of the trigger queue - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerQueueFillLevel" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerQueueFillLevel;

        //@}


        //! \name Categories: Queue
        //@{
        /*!
            \brief The threshold for turning the queue fill level off - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerQueueFillLevelEventOffThreshold" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerQueueFillLevelEventOffThreshold;

        //@}


        //! \name Categories: Queue
        //@{
        /*!
            \brief The threshold for turning the queue fill level on - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerQueueFillLevelEventOnThreshold" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerQueueFillLevelEventOnThreshold;

        //@}


        //! \name Categories: Queue
        //@{
        /*!
            \brief Enables/disable the trigger queue mode - Applies to: CoaXPress

            Enables/disable the trigger queue mode. The maximum output frequency is specified by the Trigger Output Frequency parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerQueueMode" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerQueueModeEnums>& TriggerQueueMode;

        //@}


        //! \name Categories: Trigger
        //@{
        /*!
            \brief Sets the state of the trigger system - Applies to: CoaXPress

            Sets the state of the trigger system. The state of the trigger system is related to the trigger mode. This parameter enables or disables the trigger processing.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerState" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TriggerStateEnums>& TriggerState;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Indicates a trigger frequency violation - Applies to: CoaXPress

            Indicates a distance of two trigger edges violating the minimum edge frequency.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerWaveViolation" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TriggerWaveViolation;

        //@}


        //! \name Categories: CoaXPress
        //@{
        /*!
            \brief Number of uncorrected errors - Applies to: CoaXPress

            Number of uncorrected errors. Bit[2] indicates multiple byte errors in CXP stream packets.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UncorrectedErrorCount" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& UncorrectedErrorCount;

        //@}


        //! \name Categories: SensorGeometry
        //@{
        /*!
            \brief Sets horizontal and/or vertical mirroring - Applies to: CoaXPress

            Vantage point. Use for mirroring. If VantagePoint is set to TopRight or BottomRight Width + XOffset must be smaller than SensorWidth. If VantagePoint is set to BottomLeft or BottomRight, the Height + YOffset must be smaller than SensorHeight.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VantagePoint" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<VantagePointEnums>& VantagePoint;

        //@}


        //! \name Categories: Version
        //@{
        /*!
            \brief Returns the VisualApplets version used to build the applets - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=VisualAppletsBuildVersion" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IStringEx& VisualAppletsBuildVersion;

        //@}


        //! \name Categories: ROI
        //@{
        /*!
            \brief Width of the image ROI on the host side - Applies to: CoaXPress

            Width of the image ROI on the host side. This parameter is linked with the Width camera parameter. If the camera parameter changes, the host parameter changes accordingly, but not vice versa. The host parameter should not be set to a value different from the camera parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Width" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Width;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Write access timeout in milliseconds - Applies to: GigE


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=WriteTimeout" target="_blank">feature documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& WriteTimeout;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalTLParams_Params_v9_0_0(CUniversalTLParams_Params_v9_0_0&);

        //! not implemented assignment operator
        CUniversalTLParams_Params_v9_0_0& operator=(CUniversalTLParams_Params_v9_0_0&);

    //! \endcond
    };


    //**************************************************************************************************
    // Parameter class CUniversalTLParams_Params_v9_1_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for pylon device transport layers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class PYLONBASE_API CUniversalTLParams_Params_v9_1_0 : public CUniversalTLParams_Params_v9_0_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalTLParams_Params_v9_1_0( void );

        //! Destructor
        ~CUniversalTLParams_Params_v9_1_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalTLParams_Params_v9_1_0_Data;
        CUniversalTLParams_Params_v9_1_0_Data* m_pCUniversalTLParams_Params_v9_1_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for pylon device transport layers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class CUniversalTLParams_Params : public CUniversalTLParams_Params_v9_1_0
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
            CUniversalTLParams_Params_v9_1_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalTLParams

#endif // BASLER_PYLON_UNIVERSALTLPARAMS_H
