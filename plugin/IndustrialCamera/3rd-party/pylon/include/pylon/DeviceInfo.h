//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung, AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of CDeviceInfo class
*/

#ifndef __DEVICEINFO_H__
#define __DEVICEINFO_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/stdinclude.h>
#include <pylon/Info.h>

namespace Pylon
{

    ///This namespace contains keys for accessing the properties of pylon info objects
    namespace Key
    {
        //General
        ///Identifies the serial number if it supported by the underlying implementation
        const char* const SerialNumberKey = "SerialNumber";
        ///Identifies the user-defined name if present.
        const char* const UserDefinedNameKey = "UserDefinedName";
        ///Identifies the model name of the device.
        const char* const ModelNameKey = "ModelName";
        ///Identifies the version string of the device.
        const char* const DeviceVersionKey = "DeviceVersion";
        ///Identifies the identifier for the transport layer able to create this device.
        const char* const DeviceFactoryKey = "DeviceFactory";
        ///Identifies the source of the XML used to create the node map of this device.
        const char* const XMLSourceKey = "XMLSource";
        ///Identifies the manufacturer info.
        const char* const ManufacturerInfoKey = "ManufacturerInfo";
        ///Identifies the device ID (e.g., used by Camera Link and GenTL Consumer).
        const char* const DeviceIDKey = "DeviceID";

        //GigE
        ///Identifies the IP address of the device IP address in a human-readable representation including the port number.
        const char* const AddressKey = "Address";
        ///Identifies the IP address of the device IP address in a human-readable representation.
        const char* const IpAddressKey = "IpAddress";
        ///Identifies the default gateway of the device IP address in a human-readable representation.
        const char* const DefaultGatewayKey = "DefaultGateway";
        ///Identifies the subnet mask of the device IP address in a human-readable representation.
        const char* const SubnetMaskKey = "SubnetMask";
        ///Identifies the subnet address of the device in a human-readable representation.
        const char* const SubnetAddressKey = "SubnetAddress";
        ///Identifies the port number used.
        const char* const PortNrKey = "PortNr";
        ///Identifies the MAC address of the device of the device IP address in a human-readable representation.
        const char* const MacAddressKey = "MacAddress";
        ///Identifies the address of the network interface the device is connected.
        const char* const InterfaceKey = "Interface";
        ///Identifies the persistent IP configuration options.
        const char* const IpConfigOptionsKey = "IpConfigOptions";
        ///Identifies the current IP configuration of the device.
        const char* const IpConfigCurrentKey = "IpConfigCurrent";

        //USB
        const char* const DeviceGUIDKey = "DeviceGUID";
        const char* const VendorIdKey = "VendorId";
        const char* const ProductIdKey = "ProductId";
        const char* const DriverKeyNameKey = "DriverKeyName";
        const char* const UsbDriverTypeKey = "UsbDriverTypeName";
        // Internal use only
        const char* const UsbPortVersionBcdKey = "UsbPortVersionBcd";
        // Internal use only
        const char* const SpeedSupportBitmaskKey = "SpeedSupportBitmask";
        // Internal use only
        const char* const TransferModeKey = "TransferModeKey";

        //1394
        ///Identifies the name of the device used by the underlying device driver. Internal use only.
        const char* const InternalNameKey = "InternalName";

        //BCON
        ///Identifies the name of BCON adapter library including extension without path information.
        const char* const BconAdapterLibraryNameKey = "BconAdapterLibraryName";
        ///Identifies the version of the externally provided BCON adapter library. The format is:v{major}.{minor}
        const char* const BconAdapterLibraryVersionKey = "BconAdapterLibraryVersion";
        ///Identifies the version of the BCON Adapter API the BCON adapter library has been implemented for. The format is:v{major}.{minor}
        const char* const BconAdapterLibraryApiVersionKey = "BconAdapterLibraryApiVersion";
        ///Identifies the version of the BCON Adapter API currently supported by pylon. The format is:v{major}.{minor}
        const char* const SupportedBconAdapterApiVersionKey = "SupportedBconAdapterApiVersion";


        //CameraLink
        ///Identifies the ID of the serial port the device is connected to.
        const char* const PortIDKey = "PortID";
        ///Identifies the initial baud rate of the serial port the device is connected to.
        const char* const InitialBaudRateKey = "InitialBaudRate";
        ///Identifies the device xml file override used. Internal use only.
        const char* const DeviceXMLFileOverrideKey = "DeviceXMLFileOverride";
        ///Identifies the device specific string. Internal use only.
        const char* const DeviceSpecificStringKey = "DeviceSpecificString";
        ///Identifies the port specific string of the device. Internal use only.
        const char* const PortSpecificStringKey = "PortSpecificString";


        // Internal use only
        const char* const DeviceIdxKey = "DeviceIdx";
    }

    /// Holds information about an enumerated device.
    /*!
        The device enumeration process creates a list of CDeviceInfo objects
        (Pylon::DeviceInfoList_t). Each CDeviceInfo objects stores information
        about a device. The information is retrieved during the device enumeration process (ITransportLayer::EnumerateDevices resp.
        CTlFactory::EnumerateDevices)

        \ingroup Pylon_TransportLayer
    */
    class PYLONBASE_API CDeviceInfo : public CInfoBase
    {
    public:

        CDeviceInfo();
        CDeviceInfo( const CDeviceInfo& );
        virtual ~CDeviceInfo()
        {
        }

             /*!
             \brief Compares CDeviceInfo objects by device class and serial number.
             \param[in]  rhs The right-hand side object of the comparison.
             \return Returns true according to this rule: USB < GigE < CameraLink < 1394 < Bcon < Less than compare of device class text < CamEmu.
                     CDeviceInfo objects of the same transport layer are compared by serial number. Numeric serial numbers are less than alphanumeric
                     serial numbers. Two alphanumeric serial numbers return the result of a less than text comparison.
             \error
             Does not throw C++ exceptions.
             */
        bool operator<( const CDeviceInfo& rhs ) const;

        /* The underlying implementation does not need to support all the listed properties.
        The properties that are not supported always have the value "N/A" which is the value of CInfoBase::PropertyNotAvailable */

        ///Retrieves the serial number if it supported by the underlying implementation
        ///This property is identified by Key::SerialNumberKey.
        String_t GetSerialNumber() const;
        ///Sets the above property.
        CDeviceInfo& SetSerialNumber( const String_t& SerialNumberValue );
        ///Returns true if the above property is available.
        bool IsSerialNumberAvailable() const;

        ///Retrieves the user-defined name if present.
        ///This property is identified by Key::UserDefinedNameKey.
        String_t GetUserDefinedName() const;
        ///Sets the above property.
        CDeviceInfo& SetUserDefinedName( const String_t& UserDefinedNameValue );
        ///Returns true if the above property is available.
        bool IsUserDefinedNameAvailable() const;

        ///Retrieves the model name of the device.
        ///This property is identified by Key::ModelNameKey.
        String_t GetModelName() const;
        ///Sets the above property.
        CDeviceInfo& SetModelName( const String_t& ModelNameValue );
        ///Returns true if the above property is available.
        bool IsModelNameAvailable() const;

        ///Retrieves the version string of the device.
        ///This property is identified by Key::DeviceVersionKey.
        String_t GetDeviceVersion() const;
        ///Sets the above property.
        CDeviceInfo& SetDeviceVersion( const String_t& DeviceVersionValue );
        ///Returns true if the above property is available.
        bool IsDeviceVersionAvailable() const;

        ///Retrieves the identifier for the transport layer able to create this device.
        ///This property is identified by Key::DeviceFactoryKey.
        String_t GetDeviceFactory() const;
        ///Sets the above property.
        CDeviceInfo& SetDeviceFactory( const String_t& DeviceFactoryValue );
        ///Returns true if the above property is available.
        bool IsDeviceFactoryAvailable() const;

        ///Retrieves the location where the XML file was loaded from.
        ///This property is identified by Key::XMLSourceKey.
        ///You must use the DeviceInfo of an opened IPylonDevice to retrieve this property.
        String_t GetXMLSource() const;
        ///Sets the above property.
        CDeviceInfo& SetXMLSource( const String_t& XMLSource );
        ///Returns true if the above property is available.
        bool IsXMLSourceAvailable() const;

        ///Sets the display friendly name of the device.
        ///This property is identified by Key::FriendlyNameKey.
        ///This method overrides a method of a base class returning a reference to CDeviceInfo
        CDeviceInfo& SetFriendlyName( const String_t& FriendlyNameValue );

        ///Sets the full name identifying the device.
        ///This property is identified by Key::FullNameKey.
        ///This method overrides a method of a base class returning a reference to CDeviceInfo
        CDeviceInfo& SetFullName( const String_t& FullNameValue );

        ///Sets the vendor name of the device.
        ///This property is identified by Key::VendorNameKey.
        ///This method overrides a method of a base class returning a reference to CDeviceInfo
        CDeviceInfo& SetVendorName( const String_t& VendorNameValue );

        ///Sets the device class device, e.g. Basler1394.
        ///This property is identified by Key::DeviceClassKey.
        ///This method overrides a method of a base class returning a reference to CDeviceInfo
        CDeviceInfo& SetDeviceClass( const String_t& DeviceClassValue );

        ///Retrieves the ID of the interface that the device is connected to.
        ///This property is identified by Key::InterfaceIDKey.
        String_t GetInterfaceID() const;
        ///Sets the above property.
        CDeviceInfo& SetInterfaceID( const String_t& InterfaceIDValue );
        ///Returns true if the above property is available.
        bool IsInterfaceIDAvailable() const;


        ///Retrieves the IP address the device IP address in a human-readable representation including the port number.
        ///This property is identified by Key::AddressKey.
        ///Applies to: GigE
        String_t GetAddress() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetAddress( const String_t& AddressValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsAddressAvailable() const;

        ///Retrieves the IP address the device IP address in a human-readable representation.
        ///This property is identified by Key::IpAddressKey.
        ///Applies to: GigE
        String_t GetIpAddress() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetIpAddress( const String_t& IpAddressValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsIpAddressAvailable() const;

        ///Retrieves the IP address of the subnet.
        /// This property is identified by Key::SubnetAddressKey
        ///Applies to: GigE
        String_t GetSubnetAddress() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetSubnetAddress( const String_t& SubnetAddressValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsSubnetAddressAvailable() const;

        ///Retrieves the default gateway the device IP address in a human-readable representation.
        ///This property is identified by Key::DefaultGatewayKey.
        ///Applies to: GigE
        String_t GetDefaultGateway() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetDefaultGateway( const String_t& DefaultGatewayValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsDefaultGatewayAvailable() const;

        ///Retrieves the subnet mask the device IP address in a human-readable representation.
        ///This property is identified by Key::SubnetMaskKey.
        ///Applies to: GigE
        String_t GetSubnetMask() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetSubnetMask( const String_t& SubnetMaskValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsSubnetMaskAvailable() const;

        ///Retrieves the port number used.
        ///This property is identified by Key::PortNrKey.
        ///Applies to: GigE
        String_t GetPortNr() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetPortNr( const String_t& PortNrValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsPortNrAvailable() const;

        ///Retrieves the MAC address of the device the device IP address in a human-readable representation.
        ///This property is identified by Key::MacAddressKey.
        ///Applies to: GigE
        String_t GetMacAddress() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetMacAddress( const String_t& MacAddressValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsMacAddressAvailable() const;

        ///Retrieves the address of the network interface the device is connected.
        ///This property is identified by Key::InterfaceKey.
        ///Applies to: GigE
        String_t GetInterface() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetInterface( const String_t& InterfaceValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsInterfaceAvailable() const;

        ///Retrieves the persistent IP configuration options.
        ///This property is identified by Key::IpConfigOptionsKey.
        ///Applies to: GigE
        String_t GetIpConfigOptions() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetIpConfigOptions( const String_t& IpConfigOptionsValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsIpConfigOptionsAvailable() const;

        ///Retrieves the current IP configuration of the device.
        ///This property is identified by Key::IpConfigCurrentKey.
        ///Applies to: GigE
        String_t GetIpConfigCurrent() const;
        ///Sets the above property.
        ///Applies to: GigE
        CDeviceInfo& SetIpConfigCurrent( const String_t& IpConfigCurrentValue );
        ///Returns true if the above property is available.
        ///Applies to: GigE
        bool IsIpConfigCurrentAvailable() const;


        ///Retrieves the device GUID.
        ///This property is identified by Key::DeviceGUIDKey.
        ///Applies to: Usb
        String_t GetDeviceGUID() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb
        bool IsDeviceGUIDAvailable() const;

        ///Retrieves the manufacturer info.
        ///This property is identified by Key::ManufacturerInfoKey.
        ///Applies to: Usb and BCON
        String_t GetManufacturerInfo() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb and BCON
        bool IsManufacturerInfoAvailable() const;

        ///Retrieves the device index. For internal use only.
        ///This property is identified by Key::DeviceIdxKey.
        ///Applies to: Usb and BCON
        String_t GetDeviceIdx() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb and BCON
        bool IsDeviceIdxAvailable() const;

        ///Retrieves the product ID. For internal use only.
        ///This property is identified by Key::ProductIdKey.
        ///Applies to: Usb
        String_t GetProductId() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb
        bool IsProductIdAvailable() const;

        ///Retrieves the vendor ID. For internal use only.
        ///This property is identified by Key::VendorIdKey.
        ///Applies to: Usb
        String_t GetVendorId() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb
        bool IsVendorIdAvailable() const;

        ///Retrieves the driver key name. For internal use only.
        ///This property is identified by Key::DriverKeyNameKey.
        ///Applies to: Usb
        String_t GetDriverKeyName() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb
        bool IsDriverKeyNameAvailable() const;

        ///Retrieves the usb driver type. For internal use only.
        ///This property is identified by Key::UsbDriverTypeKey.
        ///Applies to: Usb
        String_t GetUsbDriverType() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb
        bool IsUsbDriverTypeAvailable() const;

        ///Retrieves the transfer mode. For internal use only.
        ///This property is identified by Key::TransferModeKey
        // Returns either dtx or btx (direct vs. buffered transfer)
        ///Applies to: Usb
        String_t GetTransferMode() const;
        ///Returns true if the above property is available.
        ///Applies to: Usb
        bool IsTransferModeAvailable() const;


        ///Retrieves the name of the device used by the underlying device driver. Internal use only.
        ///This property is identified by Key::InternalNameKey.
        ///Applies to: 1394
        String_t GetInternalName() const;
        ///Sets the above property.
        ///Applies to: 1394
        CDeviceInfo& SetInternalName( const String_t& InternalNameValue );
        ///Returns true if the above property is available.
        ///Applies to: 1394
        bool IsInternalNameAvailable() const;


        ///Retrieves the name of BCON adapter library including extension without path information.
        ///This property is identified by Key::BconAdapterLibraryNameKey.
        ///Applies to: BCON
        String_t GetBconAdapterLibraryName() const;
        ///Sets the above property.
        ///Applies to: BCON
        CDeviceInfo& SetBconAdapterLibraryName( const String_t& BconAdapterLibraryNameValue );
        ///Returns true if the above property is available.
        ///Applies to: BCON
        bool IsBconAdapterLibraryNameAvailable() const;

        ///Retrieves the version of the externally provided BCON adapter library. The format is:v{major}.{minor}
        ///This property is identified by Key::BconAdapterLibraryVersionKey.
        ///Applies to: BCON
        String_t GetBconAdapterLibraryVersion() const;
        ///Sets the above property.
        ///Applies to: BCON
        CDeviceInfo& SetBconAdapterLibraryVersion( const String_t& BconAdapterLibraryVersionValue );
        ///Returns true if the above property is available.
        ///Applies to: BCON
        bool IsBconAdapterLibraryVersionAvailable() const;

        ///Retrieves the version of the BCON Adapter API the BCON adapter library has been implemented for. The format is:v{major}.{minor}
        ///This property is identified by Key::BconAdapterLibraryApiVersionKey.
        ///Applies to: BCON
        String_t GetBconAdapterLibraryApiVersion() const;
        ///Sets the above property.
        ///Applies to: BCON
        CDeviceInfo& SetBconAdapterLibraryApiVersion( const String_t& BconAdapterLibraryApiVersionValue );
        ///Returns true if the above property is available.
        ///Applies to: BCON
        bool IsBconAdapterLibraryApiVersionAvailable() const;

        ///Retrieves the version of the BCON Adapter API currently supported by pylon. The format is:v{major}.{minor}
        ///This property is identified by Key::SupportedBconAdapterApiVersionKey.
        ///Applies to: BCON
        String_t GetSupportedBconAdapterApiVersion() const;
        ///Sets the above property.
        ///Applies to: BCON
        CDeviceInfo& SetSupportedBconAdapterApiVersion( const String_t& SupportedBconAdapterApiVersionValue );
        ///Returns true if the above property is available.
        ///Applies to: BCON
        bool IsSupportedBconAdapterApiVersionAvailable() const;


        ///Retrieves the ID of the serial port the device is connected to.
        ///This property is identified by Key::PortIDKey.
        ///Applies to: CameraLink
        String_t GetPortID() const;
        ///Sets the above property.
        ///Applies to: CameraLink
        CDeviceInfo& SetPortID( const String_t& PortIDValue );
        ///Returns true if the above property is available.
        ///Applies to: CameraLink
        bool IsPortIDAvailable() const;

        ///Retrieves the device ID.
        ///This property is identified by Key::DeviceIDKey.
        ///Applies to: CameraLink
        String_t GetDeviceID() const;
        ///Sets the above property.
        ///Applies to: CameraLink
        CDeviceInfo& SetDeviceID( const String_t& DeviceIDValue );
        ///Returns true if the above property is available.
        ///Applies to: CameraLink
        bool IsDeviceIDAvailable() const;

        ///Retrieves the initial baud rate of the serial port the device is connected to.
        ///This property is identified by Key::InitialBaudRateKey.
        ///Applies to: CameraLink
        String_t GetInitialBaudRate() const;
        ///Sets the above property.
        ///Applies to: CameraLink
        CDeviceInfo& SetInitialBaudRate( const String_t& InitialBaudRateValue );
        ///Returns true if the above property is available.
        ///Applies to: CameraLink
        bool IsInitialBaudRateAvailable() const;

        ///Retrieves the device xml file override used. Internal use only.
        ///This property is identified by Key::DeviceXMLFileOverrideKey.
        ///Applies to: CameraLink
        String_t GetDeviceXMLFileOverride() const;
        ///Sets the above property.
        ///Applies to: CameraLink
        CDeviceInfo& SetDeviceXMLFileOverride( const String_t& DeviceXMLFileOverrideValue );
        ///Returns true if the above property is available.
        ///Applies to: CameraLink
        bool IsDeviceXMLFileOverrideAvailable() const;

        ///Retrieves the device specific string. Internal use only.
        ///This property is identified by Key::DeviceSpecificStringKey.
        ///Applies to: CameraLink
        String_t GetDeviceSpecificString() const;
        ///Sets the above property.
        ///Applies to: CameraLink
        CDeviceInfo& SetDeviceSpecificString( const String_t& DeviceSpecificStringValue );
        ///Returns true if the above property is available.
        ///Applies to: CameraLink
        bool IsDeviceSpecificStringAvailable() const;

        ///Retrieves the port specific string of the device. Internal use only.
        ///This property is identified by Key::PortSpecificStringKey.
        ///Applies to: CameraLink
        String_t GetPortSpecificString() const;
        ///Sets the above property.
        ///Applies to: CameraLink
        CDeviceInfo& SetPortSpecificString( const String_t& PortSpecificStringValue );
        ///Returns true if the above property is available.
        ///Applies to: CameraLink
        bool IsPortSpecificStringAvailable() const;

        /// Modifies a property value
        ///This method overrides a method of a base class returning a reference to CDeviceInfo
        virtual CDeviceInfo& SetPropertyValue( const String_t& Name, const String_t& Value )
        {
            CInfoBase::SetPropertyValue( Name, Value );
            return *this;
        }

    public:
        //! \brief Returns true when the device is configured for a persistent IP address
        bool IsPersistentIpActive( void ) const;

        //! \brief Returns true when the device is configured for using DHCP
        bool IsDhcpActive( void ) const;

        //! \brief Returns true when the device is configured for using Auto IP (aka LLA)
        bool IsAutoIpActive( void ) const;

        //! \brief Returns true when the device supports configuring a persistent IP address
        bool IsPersistentIpSupported( void ) const;

        //! \brief Returns true when the device supports DHCP
        bool IsDhcpSupported( void ) const;

        //! \brief Returns true when the device supports Auto IP (aka LLA)
        bool IsAutoIpSupported( void ) const;

        //! \brief Returns true when subset, applies special knowledge on how to compare GigE specific values
        virtual bool IsSubset( const IProperties& Subset ) const;

    protected:
        CDeviceInfo& SetDeviceGUID( const String_t& );
        CDeviceInfo& SetManufacturerInfo( const String_t& );
        CDeviceInfo& SetDeviceIdx( const String_t& );
        CDeviceInfo& SetProductId( const String_t& );
        CDeviceInfo& SetVendorId( const String_t& );
        CDeviceInfo& SetDriverKeyName( const String_t& );
        CDeviceInfo& SetUsbDriverType( const String_t& );
        CDeviceInfo& SetTransferMode( const String_t& );
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__DEVICEINFO_H__
