//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
    \file
    \brief  Contains possible payload type values.
*/

#ifndef INCLUDED_PAYLOADTYPE_H_835705
#define INCLUDED_PAYLOADTYPE_H_835705

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{
    // -------------------------------------------------------------------------
    // enum EPayloadType
    // -------------------------------------------------------------------------
    /*!
    \brief Possible payload type values
    \ingroup Pylon_InstantCameraApiGeneric
    */
    enum EPayloadType
    {
        PayloadType_Undefined = -1,         //!< Undefined payload
        PayloadType_Image,                  //!< The buffer contains image data.
        PayloadType_RawData,                //!< The buffer contains raw data.
        PayloadType_File,                   //!< The buffer contains file data.
        PayloadType_ChunkData,              //!< The buffer contains chunk data.
        PayloadType_GenDC,                  //!< The buffer contains GenDC container.
        PayloadType_DeviceSpecific = 0x8000 //!< The buffer contains device specific data.
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PAYLOADTYPE_H_835705 */
