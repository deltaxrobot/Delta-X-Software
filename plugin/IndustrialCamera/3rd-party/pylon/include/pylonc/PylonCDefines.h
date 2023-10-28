/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2012-2021 Basler AG
    http://www.baslerweb.com
 ------------------------------------------------------------------------------*/
#ifndef PylonCDefines_h__
#define PylonCDefines_h__

/**
    \file
    \brief pylon C bindings - macro definitions.
*/


#include <genapic/GenApiCDefines.h>

#ifdef GENAPIC_WIN_BUILD
#   ifdef PYLONC_EXPORTS
#       define PYLONC_API __declspec(dllexport)
#   else
#       define PYLONC_API __declspec(dllimport)
#   endif
#   define PYLONC_CC _stdcall
#   define PYLONC_PACKING 8
#elif defined GENAPIC_LINUX_BUILD
#   ifdef PYLONC_EXPORTS
#       define PYLONC_API __attribute__((visibility("default")))
#   else
#       define PYLONC_API
#   endif
#   define PYLONC_CC
#   define PYLONC_PACKING 8
#else
#   error Unsupported platform
#endif

#define PYLON_DEVINFO_FULL_NAME_KEY "FullName"                //!< The full name identifying the device.
#define PYLON_DEVINFO_FRIENDLY_NAME_KEY "FriendlyName"        //!< The human readable name of the device.
#define PYLON_DEVINFO_VENDOR_NAME_KEY "VendorName"            //!< The vendor name of the device.
#define PYLON_DEVINFO_DEVICE_CLASS_KEY "DeviceClass"          //!< The device class device, e.g. Basler1394.
#define PYLON_DEVINFO_SERIAL_NUMBER_KEY "SerialNumber"        //!< The serial number if it supported by the underlying implementation
#define PYLON_DEVINFO_USER_DEFINED_NAME_KEY "UserDefinedName" //!< The user-defined name if present.
#define PYLON_DEVINFO_MODEL_NAME_KEY "ModelName"              //!< The model name of the device.
#define PYLON_DEVINFO_DEVICE_FACTORY_KEY "DeviceFactory"      //!< The identifier for the transport layer able to create this device.
#define PYLON_DEVINFO_DEVICE_VERSION_KEY "DeviceVersion"      //!< The version string of the device.
#define PYLON_DEVINFO_TL_TYPE_KEY "TLType"                    //!< The transport layer type of the device.
#define PYLON_DEVINFO_INTERFACE_ID_KEY "InterfaceID"          //!< The ID of the interface that the device is connected to.
#define PYLON_DEVINFO_DEVICE_ID_KEY "DeviceID"                //!< The device ID (e.g., used by Camera Link and GenTL Consumer).
#define PYLON_DEVINFO_ADDRESS_KEY "Address"                   //!< GigE Device: The IP address of the device IP address in a human-readable representation including the port number.
#define PYLON_DEVINFO_IP_ADDRESS_KEY "IpAddress"              //!< GigE Device: The IP address of the device IP address in a human-readable representation.
#define PYLON_DEVINFO_DEFAULT_GATEWAY_KEY "DefaultGateway"    //!< GigE Device: The default gateway of the device IP address in a human-readable representation.
#define PYLON_DEVINFO_SUBNET_MASK_KEY "SubnetMask"            //!< GigE Device: The subnet mask of the device IP address in a human-readable representation.
#define PYLON_DEVINFO_PORT_NR_KEY "PortNr"                    //!< GigE Device: The port number used.
#define PYLON_DEVINFO_MAC_ADDRESS_KEY "MacAddress"            //!< GigE Device: The MAC address of the device of the device IP address in a human-readable representation.
#define PYLON_DEVINFO_INTERFACE_KEY "Interface"               //!< GigE Device: The address of the network interface the device is connected to.
#define PYLON_DEVINFO_IP_CONFIG_OPTIONS_KEY "IpConfigOptions" //!< GigE Device: The persistent IP configuration options.
#define PYLON_DEVINFO_IP_CONFIG_CURRENT_KEY "IpConfigCurrent" //!< GigE Device: The current IP configuration of the device.
#define PYLON_DEVINFO_SUBNET_ADDRESS_KEY "SubnetAddress"      //!< GigE Device: The IP address of the subnet the device belongs to.
#define PYLON_DEVINFO_PORT_ID_KEY "PortID"                    //!< Camera Link Device: The ID of the serial port the device is connected to.
#define PYLON_DEVINFO_INITIAL_BAUD_RATE_KEY "InitialBaudRate" //!< Camera Link Device: The initial baud rate of the serial port the device is connected to.
#define PYLON_DEVINFO_DEVICE_GUID_KEY "DeviceGUID"            //!< USB Device: The device GUID.
#define PYLON_DEVINFO_MANUFACTURER_INFO_KEY "ManufacturerInfo"//!< USB Device: The manufacturer info.

#define PYLON_IMAGE_WINDOW_USEDEFAULT 0x80000000

#endif /* PylonCDefines_h__ */
