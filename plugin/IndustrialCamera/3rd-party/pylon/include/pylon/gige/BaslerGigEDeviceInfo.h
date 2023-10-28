//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung, AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of CGigEDeviceInfo class

This file contains the CBaslerGigEDeviceInfo class and  additional key values
that are used in the CBaslerGigEDeviceInfo class.
*/


#ifndef __BASLERGIGEDEVICEINFO_H__
#define __BASLERGIGEDEVICEINFO_H__

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/DeviceInfo.h>
#include <pylon/gige/PylonGigE.h>

namespace Pylon
{
    /*!
    \ingroup Pylon_TransportLayer
    \class CBaslerGigEDeviceInfo
    \brief Implementation of the GiGE specific device info object
    */
    class PYLONBASE_API CBaslerGigEDeviceInfo : public CDeviceInfo
    {
    public:

        CBaslerGigEDeviceInfo();
        CBaslerGigEDeviceInfo( const CDeviceInfo& );
        virtual ~CBaslerGigEDeviceInfo();
    };

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* __BASLERGIGEDEVICEINFO_H__ */
