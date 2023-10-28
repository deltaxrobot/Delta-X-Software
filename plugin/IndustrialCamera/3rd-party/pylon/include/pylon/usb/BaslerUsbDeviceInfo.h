//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief    Definition of the CBaslerUsbDeviceInfo class
*/

#ifndef INCLUDED_BASLERUSBDEVICEINFO_H_8532831
#define INCLUDED_BASLERUSBDEVICEINFO_H_8532831

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/DeviceInfo.h>

namespace Pylon
{
    /*!
    \ingroup Pylon_TransportLayer
    \class CBaslerUsbDeviceInfo
    \brief PylonUsb specific Device Info object.
    */
    class PYLONBASE_API CBaslerUsbDeviceInfo : public Pylon::CDeviceInfo
    {
    public:
        CBaslerUsbDeviceInfo();
        CBaslerUsbDeviceInfo( const CDeviceInfo& di );
        virtual ~CBaslerUsbDeviceInfo();
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_BASLERUSBDEVICEINFO_H_8532831 */
