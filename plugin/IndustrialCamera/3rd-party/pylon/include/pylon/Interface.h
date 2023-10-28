//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  DV
//-----------------------------------------------------------------------------
/*!
\file
\brief Definiton of Interface interface
*/

#ifndef PYLON_INTERFACE_H__
#define PYLON_INTERFACE_H__

#pragma once

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenICamFwd.h>
#include <pylon/stdinclude.h>
#include <pylon/DeviceFactory.h>
#include <pylon/InterfaceInfo.h>


namespace Pylon
{
    /*!
    \ingroup Pylon_TransportLayer
    \interface IInterface
    \brief An interface is used to represent a frame grabber board, a network card, etc.

    Currently, this object type is mainly used for the pylon GenTL Consumer Transport Layer, e.g., for CoaXPress.
    All other pylon transport layers currently return one default interface.

    The 'open' status of an interface instance won't change even if an attached camera is used, e.g., opened or closed.
    */
    interface PUBLIC_INTERFACE IInterface : public IDeviceFactory
    {
        /*!
        \brief Opens an interface to be able access it's parameters via GetNodeMap().

        \note You can use the methods provided by IDeviceFactory regardless of whether the interface is opened or closed.

        \post
            <ul>
            <li> The interface is open.
            <li> The node map can be accessed via GetNodeMap().
            </ul>


        \threading
            This method is thread-safe.

        \error
            Throws a C++ exception if opening the interface fails.
        */
        virtual void Open() = 0;


        /*!
        \brief Closes an interface.

        \threading
            This method is thread-safe.

        \post
            <ul>
            <li> The interface is closed.
            <li> Any previously acquired node map using GetNodeMap() has been deleted and must not be used any longer.
            </ul>

        \error
            Does not throw C++ exceptions.
        */
        virtual void Close() = 0;


        /*!
        \brief Checks if the interface is open.

        \note The 'open' status of an interface instance won't change even if an attached camera is used, e.g., opened or closed.

        \return Returns true if when the interface is open.

        \threading
            This method is thread-safe.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsOpen() const = 0;


        /*! \brief Returns the interface info object storing information like the Interface ID property.

        This information is available at all times regardless of whether the interface is open or closed.

        \return A reference to the interface info object.

        \threading
            This method is thread-safe.

        \error
            Does not throw C++ exceptions.
        */
        virtual const CInterfaceInfo& GetInterfaceInfo() const = 0;


        /*!
        \brief Returns the GenApi node map used for accessing parameters provided by the interface.

        \note The default interface object does not provide a node map.

        \return Returns the GenApi node map used for accessing parameters provided by the interface.
                If no parameters are available, NULL is returned.

        \threading
            This method is thread-safe.

        \error
            Can throw C++ exceptions.
        */
        virtual GENAPI_NAMESPACE::INodeMap* GetNodeMap() = 0;

    protected:
        virtual ~IInterface() = 0;
    };

    // Note: the C++ standard >= 11 prohibit pure virtual destructors with a function body
    // in the declaration. Consequently gcc 4.0 and newer reject an inline implementation
    // in the class.
    inline IInterface::~IInterface()
    {
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* PYLON_INTERFACE_H__ */
