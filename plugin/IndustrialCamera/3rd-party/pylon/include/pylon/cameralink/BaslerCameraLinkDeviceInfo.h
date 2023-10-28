//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/*!
\file
\brief    Definition of CPylonPylonCLSerDeviceInfo
*/


#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#ifndef PYLONCLSERDEVICEINFO_H__
#define PYLONCLSERDEVICEINFO_H__

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/DeviceInfo.h>

namespace Pylon
{
    /*!
    \brief PylonCLSer specific Device Info object.
    \ingroup Pylon_TransportLayer
    */
    class PYLONBASE_API CBaslerCameraLinkDeviceInfo : public Pylon::CDeviceInfo
    {
    public:
        CBaslerCameraLinkDeviceInfo();
        CBaslerCameraLinkDeviceInfo( const CDeviceInfo& di );
        virtual ~CBaslerCameraLinkDeviceInfo();
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // PYLONCLSERDEVICEINFO_H__
