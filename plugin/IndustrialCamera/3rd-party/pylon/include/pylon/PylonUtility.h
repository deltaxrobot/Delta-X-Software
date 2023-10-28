//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*  AH: intentionally omitted for doxygen documentation
\file
\brief Defines for the pylon utility library.
*/
#ifndef PYLONUTILITY_H
#define PYLONUTILITY_H


#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */



#ifdef PYLONUTILITY_EXPORTS
#  define PYLONUTILITY_API APIEXPORT
#else
#  define PYLONUTILITY_API APIIMPORT
#endif

#if defined(PYLON_UTILITY_3_0_NO_DEPRECATE)
#   define PYLON_UTILITY_3_0_DEPRECATED(message)
#else
#   define PYLON_UTILITY_3_0_DEPRECATED(message) PYLON_DEPRECATED(message)
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif

