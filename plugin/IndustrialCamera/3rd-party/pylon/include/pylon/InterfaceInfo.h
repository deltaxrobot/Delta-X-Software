//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Declaration of the interface information class.
*/

#ifndef __INTERFACE_INFO_H__
#define __INTERFACE_INFO_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/stdinclude.h>
#include <pylon/Info.h>

namespace Pylon
{

    /**
    \ingroup PYLON_PUBLIC

    \brief Class used for storing information about an interface object provided by a transport layer.

    Enumerating the available Transport Layer Interface objects returns a list of
    CInterface objects (Pylon::InterfaceInfoList_t). A CInterfaceInfo object holds information
    about the enumerated interface.
    */
    class PYLONBASE_API CInterfaceInfo : public CInfoBase
    {
    public:
        /*!
        \brief Compares CInterfaceInfo objects by device class and interface ID.
        \param[in]  rhs The right-hand side object of the comparison.
        \return Returns true according to this rule: USB < GigE < CameraLink < 1394 < Bcon < Less than compare of device class text < CamEmu.
                CInterfaceInfo objects of the same transport layer are compared by interface ID using less than text comparison.
        \error
        Does not throw C++ exceptions.
        */
        bool operator<( const CInterfaceInfo& rhs ) const;

        ///Retrieves the interface ID identifying the interface.
        ///This property is identified by Key::InterfaceIDKey.
        String_t GetInterfaceID() const;
        ///Sets the above property.
        CInterfaceInfo& SetInterfaceID( const String_t& InterfaceIDValue );
        ///Returns true if the above property is available.
        bool IsInterfaceIDAvailable() const;
    };

}

#endif
