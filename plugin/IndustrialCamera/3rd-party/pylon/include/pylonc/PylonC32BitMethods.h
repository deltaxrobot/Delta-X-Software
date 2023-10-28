/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2009-2021 Basler AG
    http://www.baslerweb.com
    Author:  AH, TK
-----------------------------------------------------------------------------*/

#ifndef PylonC32BitMethods_h__
#define PylonC32BitMethods_h__

#include <genapic/GenApiCDefines.h>
#include <genapic/GenApiCTypes.h>

#include <pylonc/PylonCDefines.h>
#pragma pack(push, PYLONC_PACKING)

#include <pylonc/PylonC.h>

/**
    \file
    \brief pylon C bindings - 32 bit functions.
*/


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /*
    * ----------------------------------------------------------------------------
    * Functions doing an implicit cast to 32-bit values
    * ----------------------------------------------------------------------------
    */
    PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceSetIntegerFeatureInt32( PYLON_DEVICE_HANDLE dev, const char* name, int32_t value );
    PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceGetIntegerFeatureInt32( PYLON_DEVICE_HANDLE dev, const char* name, int32_t* value );
    PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceGetIntegerFeatureMinInt32( PYLON_DEVICE_HANDLE dev, const char* name, int32_t* value );
    PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceGetIntegerFeatureMaxInt32( PYLON_DEVICE_HANDLE dev, const char* name, int32_t* value );
    PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceGetIntegerFeatureIncInt32( PYLON_DEVICE_HANDLE dev, const char* name, int32_t* value );

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#pragma pack(pop)

#endif /* PylonC32BitMethods_h__ */
