/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2009-2021 Basler AG
    http://www.baslerweb.com
    Author:  AH, TK
-----------------------------------------------------------------------------*/

/**
    \file
    \brief Error codes for pylon C bindings.
*/

#ifndef PylonCError_h__
#define PylonCError_h__

#include <genapic/GenApiCError.h>

/**
* \addtogroup errorcodes Error&nbsp;Codes
* @{
*/

#define PYLON_E_INVALID_DEVICEHANDLE        ((GENAPIC_RESULT) 0xC3000001)  /**< An invalid Device handle has been passed. */
#define PYLON_E_INVALID_DEVICEINFOHANDLE    ((GENAPIC_RESULT) 0xC3000002)  /**< An invalid DeviceInfo handle has been passed. */
#define PYLON_E_INVALID_DEVICEINFO_PROPERTY ((GENAPIC_RESULT) 0xC3000003)  /**< An invalid DeviceInfoProperty handle has been passed. */
#define PYLON_E_INVALID_STREAMGRABBERHANDLE ((GENAPIC_RESULT) 0xC3000004)  /**< An invalid StreamGrabber handle has been passed. */
#define PYLON_E_INVALID_CHUNKPARSERHANDLE   ((GENAPIC_RESULT) 0xC3000005)  /**< An invalid ChunkParser handle has been passed. */
#define PYLON_E_INVALID_WAITOBJECTHANDLE    ((GENAPIC_RESULT) 0xC3000006)  /**< An invalid WaitObject handle has been passed. */
#define PYLON_E_INVALID_EVENTGRABBERHANDLE  ((GENAPIC_RESULT) 0xC3000007)  /**< An invalid EventGrabber handle has been passed. */
#define PYLON_E_INVALID_EVENTADAPTERHANDLE  ((GENAPIC_RESULT) 0xC3000008)  /**< An invalid EventAdapter handle has been passed. */
#define PYLON_E_INVALID_CONVERTERHANDLE     ((GENAPIC_RESULT) 0xC3000009)  /**< An invalid Converter handle has been passed. */
#define PYLON_E_INVALID_WAITOBJECTSHANDLE   ((GENAPIC_RESULT) 0xC300000A)  /**< An invalid WaitObjects handle has been passed. */
#if defined(GENAPIC_WIN_BUILD)
#define PYLON_E_INVALID_AVIWRITERHANDLE     ((GENAPIC_RESULT) 0xC300000B)  /**< An invalid AVI writer handle has been passed. */
#endif
#define PYLON_E_INVALID_INTERFACEHANDLE     ((GENAPIC_RESULT) 0xC300000C)  /**< An invalid Interface handle has been passed. */
#define PYLON_E_INVALID_INTERFACEINFOHANDLE ((GENAPIC_RESULT) 0xC300000D)  /**< An invalid InterfaceInfo handle has been passed. */
#define PYLON_E_INVALID_DECOMPRESSORHANDLE  ((GENAPIC_RESULT) 0xC300000E)  /**< An invalid decompressor handle has been passed. */

/**
* @}
*/

#endif /* PylonCError_h__ */
