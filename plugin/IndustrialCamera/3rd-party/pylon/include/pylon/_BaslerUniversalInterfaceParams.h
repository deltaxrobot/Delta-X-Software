//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for pylon interfaces
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_UNIVERSALINTERFACEPARAMS_H
#define BASLER_PYLON_UNIVERSALINTERFACEPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_UniversalInterfaceParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for CxpLinkConfiguration
    enum CxpLinkConfigurationEnums
    {
        CxpLinkConfiguration_Auto,  //!< Link speed is controlled automatically
        CxpLinkConfiguration_CXP10_X1,  //!< Connection is operating at CXP-10 speed (10 0 Gbps)
        CxpLinkConfiguration_CXP12_X1,  //!< Connection is operating at CXP-12 speed (12 50 Gbps)
        CxpLinkConfiguration_CXP1_X1,  //!< Connection is operating at CXP-1 speed (1 25 Gbps)
        CxpLinkConfiguration_CXP2_X1,  //!< Connection is operating at CXP-2 speed (2 50 Gbps)
        CxpLinkConfiguration_CXP3_X1,  //!< Connection is operating at CXP-3 speed (3 125 Gbps)
        CxpLinkConfiguration_CXP5_X1,  //!< Connection is operating at CXP-5 speed (5 00 Gbps)
        CxpLinkConfiguration_CXP6_X1  //!< Connection is operating at CXP-6 speed (6 25 Gbps)
    };

    //! Valid values for CxpPoCxpStatus
    enum CxpPoCxpStatusEnums
    {
        CxpPoCxpStatus_Auto,  //!< PoCXP operation is set to automatic
        CxpPoCxpStatus_Off,  //!< PoCXP is forced off
        CxpPoCxpStatus_Tripped  //!< The link has shut down because of an over-current trip
    };

    //! Valid values for CxpPort0PowerState
    enum CxpPort0PowerStateEnums
    {
        CxpPort0PowerState_AdcFault,  //!< The PoCXP state can't be determined because of an A/D converter fault
        CxpPort0PowerState_Disabled,  //!< PoCXP is disabled
        CxpPort0PowerState_HighCurrent,  //!< PoCXP is off because of an over current trip
        CxpPort0PowerState_HighVoltage,  //!< PoCXP is off because the voltage is too high
        CxpPort0PowerState_Initializing,  //!< The PoCXP state machine is looking for devices
        CxpPort0PowerState_InvalidValue,  //!< The PoCXP state can't be determined
        CxpPort0PowerState_LowVoltage,  //!< PoCXP is off because the voltage is too low
        CxpPort0PowerState_On  //!< PoCXP is active
    };

    //! Valid values for DeviceAccessStatus
    enum DeviceAccessStatusEnums
    {
        DeviceAccessStatus_Busy,  //!< The device is already opened by another entity
        DeviceAccessStatus_NoAccess,  //!< You can't connect to the device
        DeviceAccessStatus_OpenReadOnly,  //!< The device is opened in Read-only mode by this GenTL host
        DeviceAccessStatus_OpenReadWrite,  //!< The device is opened in Read/Write mode by this GenTL host
        DeviceAccessStatus_ReadOnly,  //!< The device offers read-only access
        DeviceAccessStatus_ReadWrite,  //!< The device offers read/write access
        DeviceAccessStatus_Unknown  //!< The status is unknown
    };

    //! Valid values for InterfaceApplet
    enum InterfaceAppletEnums
    {
        InterfaceApplet_Acq_SingleCXP12x1Area,  //!< The Acq_SingleCXP12x1Area applet is used to initialize the interface
        InterfaceApplet_Acq_SingleCXP12x1Area_01,  //!< The Acq_SingleCXP12x1Area_01 applet is used to initialize the interface
        InterfaceApplet_Acq_SingleCXP12x1Area_02  //!< The Acq_SingleCXP12x1Area_02 applet is used to initialize the interface
    };

    //! Valid values for InterfaceType
    enum InterfaceTypeEnums
    {
        InterfaceType_CL,  //!< The interface uses the Camera Link transport layer
        InterfaceType_CLHS,  //!< The interface uses the Camera Link HS transport layer
        InterfaceType_CXP,  //!< The interface uses the CoaXPress transport layer
        InterfaceType_Custom,  //!< The interface uses a custom transport layer
        InterfaceType_GEV,  //!< The interface uses the GigE Vision transport layer
        InterfaceType_Mixed,  //!< Different interface modules of the GenTL Producer are of different types
        InterfaceType_U3V  //!< The interface uses the USB3 Vision transport layer
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalInterfaceParams_Params_v6_2_0
    //**************************************************************************************************
    

    //! A parameter class containing all parameters as members that are available for pylon interfaces
    class PYLONBASE_API CUniversalInterfaceParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalInterfaceParams_Params_v6_2_0( void );

        //! Destructor
        ~CUniversalInterfaceParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalInterfaceParams_Params_v6_2_0_Data;
        CUniversalInterfaceParams_Params_v6_2_0_Data* m_pCUniversalInterfaceParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: BoardSensors
        //@{
        /*!
            \brief Ambient temperature at the board


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AmbientTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& AmbientTemperature;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Sets the link configuration for the communication between the receiver and transmitter device


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpLinkConfiguration" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpLinkConfigurationEnums>& CxpLinkConfiguration;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Enables automatic control of Power over CoaXPress (PoCXP) for the port


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPoCxpAuto" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& CxpPoCxpAuto;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Returns the Power over CoaXPress (PoCXP) status of the device


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPoCxpStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpPoCxpStatusEnums>& CxpPoCxpStatus;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Resets Power over CoaXPress (PoCXP) link after an over-current trip on the device connection(s)


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPoCxpTripReset" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& CxpPoCxpTripReset;

        //@}


        //! \name Categories: TransportLayerControl
        //@{
        /*!
            \brief Disables Power over CoaXPress (PoCXP) for the port


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPoCxpTurnOff" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& CxpPoCxpTurnOff;

        //@}


        //! \name Categories: Port0Status
        //@{
        /*!
            \brief CXP port 0 current


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPort0Current" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& CxpPort0Current;

        //@}


        //! \name Categories: Port0Status
        //@{
        /*!
            \brief Number of CXP port 0 disparity errors


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPort0DisparityErrorCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpPort0DisparityErrorCount;

        //@}


        //! \name Categories: Port0Status
        //@{
        /*!
            \brief Link speed of CXP port 0


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPort0LinkSpeed" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& CxpPort0LinkSpeed;

        //@}


        //! \name Categories: Port0Status
        //@{
        /*!
            \brief Number of CXP port 0 not-in-table errors


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPort0NotInTableErrorCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& CxpPort0NotInTableErrorCount;

        //@}


        //! \name Categories: Port0Status
        //@{
        /*!
            \brief CXP port 0 power


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPort0Power" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& CxpPort0Power;

        //@}


        //! \name Categories: Port0Status
        //@{
        /*!
            \brief Returns the PoCXP (Power over CXP) state of CXP port 0


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPort0PowerState" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<CxpPort0PowerStateEnums>& CxpPort0PowerState;

        //@}


        //! \name Categories: Port0Status
        //@{
        /*!
            \brief CXP port 0 voltage


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CxpPort0Voltage" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& CxpPort0Voltage;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Returns the device's access status at the moment when the Device Update List command was last executed

            Returns the device's access status at the moment when the Device Update List command was last executed. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceAccessStatus" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<DeviceAccessStatusEnums>& DeviceAccessStatus;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Interface-wide unique ID of the selected device

            Interface-wide unique ID of the selected device. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceID;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Name of the device model

            Name of the device model. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceModelName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceModelName;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Device selected in this interface

            Device selected in this interface. This value only changes when the Device Update List command is executed. The parameter is 0-based in order to match the index of the C interface.

            Visibility: Expert

            Selecting Parameters: DeviceAccessStatus, DeviceID, DeviceModelName, DeviceSerialNumber, DeviceTLVersionMajor, DeviceTLVersionMinor, DeviceVendorName, GevDeviceIPAddress, GevDeviceMACAddress and GevDeviceSubnetMask

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSelector" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceSelector;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Serial number of the remote device

            Serial number of the remote device. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSerialNumber" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceSerialNumber;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Major version number of the transport layer specification that the remote device complies with


            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceTLVersionMajor;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Minor version number of the transport layer specification that the remote device complies with


            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceTLVersionMinor;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Updates the internal device list


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceUpdateList" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::ICommandEx& DeviceUpdateList;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Timeout for the Device Update List command


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceUpdateTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DeviceUpdateTimeout;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief User-settable ID of the remote device

            User-settable ID of the remote device. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceUserID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceUserID;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Name of the device vendor

            Name of the device vendor. This value only changes when the Device Update List command is executed.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceVendorName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DeviceVendorName;

        //@}


        //! \name Categories: BoardSensors
        //@{
        /*!
            \brief Indicates whether an external power source has been detected


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExternalPowerPresent" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ExternalPowerPresent;

        //@}


        //! \name Categories: BoardSensors
        //@{
        /*!
            \brief FPGA aux voltage


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FpgaAuxVoltage" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& FpgaAuxVoltage;

        //@}


        //! \name Categories: BoardSensors
        //@{
        /*!
            \brief FPGA BRAM voltage


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FpgaBRamVoltage" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& FpgaBRamVoltage;

        //@}


        //! \name Categories: BoardSensors
        //@{
        /*!
            \brief FPGA core temperature


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FpgaCoreTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& FpgaCoreTemperature;

        //@}


        //! \name Categories: BoardSensors
        //@{
        /*!
            \brief FPGA core voltage


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FpgaCoreVoltage" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& FpgaCoreVoltage;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Current IP address of the GVCP interface of the selected remote device

            Current IP address of the GVCP interface of the selected remote device. This value only changes on execution of the DeviceUpdateList command.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceIPAddress" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceIPAddress;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief 48-bit MAC address of the GVCP interface of the selected remote device

            48-bit MAC address of the GVCP interface of the selected remote device. This value only changes when the DeviceUpdateList command is executed.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceMACAddress" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceMACAddress;

        //@}


        //! \name Categories: DeviceEnumeration
        //@{
        /*!
            \brief Current subnet mask of the GVCP interface of the selected remote device

            Current subnet mask of the GVCP interface of the selected remote device. This value only changes on execution of the DeviceUpdateList command. This value only changes when the DeviceUpdateList command is executed.

            Visibility: Expert

            Selected by: DeviceSelector

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GevDeviceSubnetMask" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& GevDeviceSubnetMask;

        //@}


        //! \name Categories: InterfaceApplets
        //@{
        /*!
            \brief Sets the applet with which to initialize the interface

            Sets the applet with which to initialize the interface. Applets are specific DLLs used to initialize the frame grabber. Each applet has different characteristics and functionalities.

            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=InterfaceApplet" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<InterfaceAppletEnums>& InterfaceApplet;

        //@}


        //! \name Categories: InterfaceInformation
        //@{
        /*!
            \brief User-friendly name of the interface


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=InterfaceDisplayName" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& InterfaceDisplayName;

        //@}


        //! \name Categories: InterfaceInformation
        //@{
        /*!
            \brief GenTL Producer-wide unique ID of the selected interface


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=InterfaceID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& InterfaceID;

        //@}


        //! \name Categories: InterfaceInformation
        //@{
        /*!
            \brief Major version number of the transport layer specification that the GenTL Producer interface complies with

            Major version number of the transport layer specification that the GenTL Producer interface complies with. The transport layer version of the interface should match the transport layer version of the device to assure compatibility.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=InterfaceTLVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& InterfaceTLVersionMajor;

        //@}


        //! \name Categories: InterfaceInformation
        //@{
        /*!
            \brief Minor version number of the transport layer specification that the GenTL Producer interface complies with

            Minor version number of the transport layer specification that the GenTL Producer interface complies with. The transport layer version of the interface should match the transport layer version of the device to assure compatibility.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=InterfaceTLVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& InterfaceTLVersionMinor;

        //@}


        //! \name Categories: InterfaceInformation
        //@{
        /*!
            \brief Sets the transport layer of the interface


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=InterfaceType" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<InterfaceTypeEnums>& InterfaceType;

        //@}


        //! \name Categories: BoardSensors
        //@{
        /*!
            \brief Temperature of the board power supply


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PowerSupplyTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IFloatEx& PowerSupplyTemperature;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalInterfaceParams_Params_v6_2_0(CUniversalInterfaceParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CUniversalInterfaceParams_Params_v6_2_0& operator=(CUniversalInterfaceParams_Params_v6_2_0&);

    //! \endcond
    };


    //! A parameter class containing all parameters as members that are available for pylon interfaces
    class CUniversalInterfaceParams_Params : public CUniversalInterfaceParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalInterfaceParams_Params( void )
        {
        }

        //! Destructor
        ~CUniversalInterfaceParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CUniversalInterfaceParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalInterfaceParams

#endif // BASLER_PYLON_UNIVERSALINTERFACEPARAMS_H
