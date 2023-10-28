//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of the IDeviceFactory interface
*/

#ifndef __DEVICEFACTORY_H__
#define __DEVICEFACTORY_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/DeviceInfo.h>
#include <pylon/Container.h>
#include <pylon/DeviceAccessMode.h>

namespace Pylon
{
    interface IPylonDevice;


    // --------------------------------------------------------------------------
    // enum EDeviceAccessiblityInfo
    // --------------------------------------------------------------------------
    /// Information about the accessibility of a device
    /*!
        \ingroup Pylon_TransportLayer
    */
    enum EDeviceAccessiblityInfo
    {
        Accessibility_Unknown = 0,           //!< The accessibility could not be determined. The state of accessibility is unknown.
        Accessibility_Ok = 1,                //!< The device could be opened.
        Accessibility_Opened = 2,            //!< The device is reachable, but can be opened in read only mode only.
        Accessibility_OpenedExclusively = 3, //!< The device is reachable, but currently opened exclusively by another application.
        Accessibility_NotReachable = 4,      //!< The device could not be reached or does not exist. No connection to the device is possible.
    };


    /*!
    \interface IDeviceFactory
    \brief Interface to be implemented by device factories used to create devices.

    Each transport layer object is a device factory. These device factories must implement
    the IDeviceFactory interface.

    \ingroup Pylon_TransportLayer
    */

    interface PUBLIC_INTERFACE IDeviceFactory
    {
        /// Retrieves a list of available devices.
        /**
        The list contains Pylon::CDeviceInfo objects used for the device creation and is ordered by device class and serial number using the operator Pylon::CDeviceInfo::operator<().
        By default, the list will be cleared before the device discovery is started.

        \param list List to be filled with device info objects.
        \param addToList If true, the devices found will be appended to the list instead of deleting the list. Only newly discovered devices are sorted and not the entire list.
        \return Number of devices found.
        */
        virtual int EnumerateDevices( DeviceInfoList_t& list, bool addToList = false ) = 0;

        /// Retrieves a list of available devices filtered by given properties, usable for looking for specific devices.
        /**
        The list contains Pylon::CDeviceInfo objects used for the device creation and is ordered by device class and serial number using the operator Pylon::CDeviceInfo::operator<().
        By default, the list will be cleared before the device discovery is started.
        The filter list can contain a list of device info objects containing properties a device must have, e.g.,
        the user-provided name or the serial number. A device is returned if it matches the properties of any of the
        device info objects on the filter list.
        If the device class property is set in the filter device info objects, the search is
        limited to the required transport layers.

        \param list List to be filled with device info objects.
        \param filter A list of device info objects with user-provided properties that a device can match.
        \param addToList If true, the devices found will be appended to the list instead of deleting the list. Only newly discovered devices are sorted and not the entire list.
        \return Number of devices found.
        */
        virtual int EnumerateDevices( DeviceInfoList_t& list, const DeviceInfoList_t& filter, bool addToList = false ) = 0;

        /// Creates a camera object from a device info object.
        /**
            This method accepts either a device info object from a device enumeration or a user-provided device info object.
            User-provided device info objects can be preset with properties required for a device, e.g.
            the user-provided name or the serial number. The implementation tries to find a matching camera by using device
            enumeration.
            When the device class property is set, the search is limited to the required transport layer.

            If the device creation fails, a GenApi::GenericException will be thrown.
            \param di Device info object containing all information needed to identify exactly one device.
        */
        virtual IPylonDevice* CreateDevice( const CDeviceInfo& di ) = 0;

        /// If multiple devices match the provided properties, the first device found is created.
        /// The order in which the devices are found can vary from call to call.
        virtual IPylonDevice* CreateFirstDevice( const CDeviceInfo& di = CDeviceInfo() ) = 0;

        /// Creates a camera object from a device info object, injecting additional GenICam XML definition strings.
        /// Currently only one injected xml string is supported.
        virtual IPylonDevice* CreateDevice( const CDeviceInfo& di, const StringList_t& InjectedXmlStrings ) = 0;

        /// Creates the first found camera device matching the provided properties, injecting additional GenICam XML definition strings.
        /// Currently only one injected xml string is supported.
        virtual IPylonDevice* CreateFirstDevice( const CDeviceInfo& di, const StringList_t& InjectedXmlStrings ) = 0;

        /// This method is deprecated. Use CreateDevice and pass a CDeviceInfo object containing the full name as a property.
        /// Example: IPylonDevice* device = TlFactory.CreateDevice( CDeviceInfo().SetFullName( fullname));
        /// creates a device that matches its full name (i.e., as returned by CDeviceInfo::GetFullName).
        virtual IPylonDevice* CreateDevice( const String_t& ) = 0;

        /// Destroys a device.
        /** \note Never try to delete a pointer to a camera device by calling free or delete.
            Always use the DestroyDevice method.
        */
        virtual void DestroyDevice( IPylonDevice* ) = 0;

        /*!
        \brief This method can be used to check if a camera device can be created and opened.

        This method accepts either a device info object from a device enumeration or a user-provided device info object.
        User-provided device info objects can be preset with properties required for a device, e.g.
        the user-provided name or the serial number. The implementation tries to find a matching camera by using device
        enumeration. When the device class property is set, see \ref DeviceClass.h header file, the search is limited to the required transport layer.
         For more information, see \ref UsingEnumeraionWithFilter "Applying a Filter when Enumerating Cameras".


        \param[in]  deviceInfo         Properties to find/identify the camera device to check.
        \param[in]  mode               Used for defining how a device is accessed.
                                       The use of the mode information is transport layer-specific.
                                       - For \ref Pylon::BaslerBconDeviceClass "BCON", \ref Pylon::BaslerCameraLinkDeviceClass "CameraLink",
                                       and \ref Pylon::BaslerUsbDeviceClass "USB" devices, the mode information is ignored.
                                       - For \ref Pylon::BaslerGigEDeviceClass "GigE" devices, the \c Exclusive and \c Control flags are used for defining how a device is accessed. Other mode information is ignored.
                                       - For devices of any type that are accessed via the \ref Pylon::BaslerGenTlDeviceClassPrefix "GenICam GenTL" transport layer, the mode is ignored.
        \param[out]  pAccessibilityInfo Optional parameter that provides more information about whether a device is accessible or not.
        \return True if device can be opened with provided access mode.

        \pre The \c deviceInfo object properties specify exactly one device.
             This is the case when the device info object has been obtained using device enumeration.

        \error
             Throws a C++ exception, if the preconditions are not met.
        */
        virtual bool IsDeviceAccessible( const CDeviceInfo& deviceInfo, AccessModeSet mode = Control, EDeviceAccessiblityInfo* pAccessibilityInfo = NULL ) = 0;
    };







} // namespace PYLON

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif
