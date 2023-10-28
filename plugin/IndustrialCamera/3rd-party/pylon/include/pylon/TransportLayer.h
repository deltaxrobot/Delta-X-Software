//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definiton of Transportlayer interface and the common Transportlayer base class
*/

#ifndef __TRANSPORTLAYER__
#define __TRANSPORTLAYER__

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenICamFwd.h>
#include <pylon/stdinclude.h>
#include <pylon/PylonBase.h>
#include <pylon/DeviceFactory.h>
#include <pylon/TlInfo.h>
#include <pylon/Interface.h>


namespace Pylon
{


    /*!
    \ingroup Pylon_TransportLayer
    \interface ITransportLayer
    \brief The interface of Transport Layer objects

    Transport Layer objects are used for enumerating and creating devices accessible
    by a specific transport layer (like the Pylon1394 or the PylonGigE transport layer).
    */
    interface PUBLIC_INTERFACE ITransportLayer : public IDeviceFactory
    {
        /*!
        \brief Returns a CTlInfo object holding information about the transport layer.

        \return Returns a CTlInfo object holding information about the transport layer.
        */
        virtual CTlInfo GetTlInfo() const = 0;


        /*!
        \brief Creates and returns an 'empty' Device Info object appropriate for the transport layer.

        Device Info objects returned by the CreateDeviceInfo() method are used to create
        devices from device info objects that are not the result of a device enumeration process but are
        provided by the user. The user is responsible for
        filling in the fields of the Device Info object that are needed to identify and create a device.

        Example: To open a GigE device for which the IP address is known, the user lets the Transport Layer object
        create a Device Info object, specifies the IP address and passes the device info object to the
        CreateDevice() method.
        */
        virtual CDeviceInfo CreateDeviceInfo() = 0;


        /*! \brief Returns the GenApi node map used for accessing parameters provided by the transport layer.

        \return NULL, if the transport layer doesn't provide parameters, a pointer to the parameter node map otherwise.
        */
        virtual GENAPI_NAMESPACE::INodeMap* GetNodeMap() = 0;


        /*! \brief Retrieves a list of available interfaces. An interface may represent a frame grabber board, a network card, etc.

        \note Currently, this method is used mainly for the pylon GenTL Consumer transport layer, which is used for CoaXPress, for example.
              All other pylon transport layers return one default interface. The default interface will forward
              all IDeviceFactory methods to the transport layer that created the interface object. The default interface does not provide a node map.

        \param[out] list The list to be filled with interface info objects. The list contains Pylon::CInterfaceInfo objects used for the interface
                         creation. It is ordered by device class and interface ID using the operator Pylon::CInterfaceInfo::operator<().
        \param[in] addToList If true, devices found will be added to the list instead of clearing the list.
                             By default, the list passed in will be cleared.
        \return Number of interfaces provided by the transport layer.

        \threading
            This method is thread-safe.

        \error
            Can throw C++ exceptions.
        */
        virtual int EnumerateInterfaces( InterfaceInfoList_t& list, bool addToList = false ) = 0;


        /*! \brief Creates an interface object from an interface info object.


        \param[in] interfaceInfo The Interface info object. You can pass an interface info object returned by EnumerateInterfaces()
                                 or a user-provided interface info object.
                                 User-provided interface info objects can be preset with properties required for an interface, e.g.
                                 the interface ID. The implementation tries to find a matching interface.
        \return Returns the pointer to the interface created.

        \post The interface created must be freed by calling DestroyInterface(). The transport layer is not destroyed as long as the interface is not destroyed.
              Never try to delete a pointer to an interface object by calling free or delete. Always use the DestroyInterface() method.

        \error
             Throws an exception if creating the interface fails.

        \threading
            This method is thread-safe.
        */
        virtual IInterface* CreateInterface( const CInterfaceInfo& interfaceInfo ) = 0;


        /*! \brief Destroys an interface.

        \param[in] pInterface The pointer to an interface created by this transport layer.

        \pre The interface has been created by this transport layer using CreateInterface() and has not been destroyed using DestroyInterface() yet.
        \post The interface is deleted and must not be used any longer.

        \error
            Throws a C++ exception if the preconditions are not met.

        \threading
            This method is thread-safe.
        */
        virtual void DestroyInterface( IInterface* pInterface ) = 0;
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* __TRANSPORTLAYER__ */
