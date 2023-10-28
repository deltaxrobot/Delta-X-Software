/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2009-2021 Basler AG
    http://www.baslerweb.com
    Author:  AH, TK
-----------------------------------------------------------------------------*/

/**
 *  \file
 *  \brief    Platform-dependent type definitions.
 *  Define a subset of the types and macros that are provided by the
 *  stdint.h header on systems that comply with the C99 standard. This
 *  is meant to aid in portability.
**/

#ifndef GENAPIC_TYPES_H
#define GENAPIC_TYPES_H

#if __STDC_VERSION__ >= 199901L

/* Compiler is c99-compliant. */
#   if !defined(__STDC_LIMIT_MACROS)
#       define  __STDC_LIMIT_MACROS
#   endif
#   if !defined(__STDC_CONSTANT_MACROS)
#       define  __STDC_CONSTANT_MACROS
#   endif
#   include <inttypes.h>
#   include <stdint.h>

#elif defined (_WIN32)

#   if defined(_MSC_VER) && _MSC_VER >= 1600
// VS2010 provides stdint.h
#       include <stdint.h>
#   else
#       ifndef _STDINT // only define if not already done

            /*! Portable 8 bit-wide signed integer type. */
typedef __int8 int8_t;
/*! Portable 8 bit-wide unsigned integer type. */
typedef unsigned __int8 uint8_t;

/*! Portable 16 bit-wide signed integer type. */
typedef __int16 int16_t;
/*! Portable 16 bit-wide unsigned integer type. */
typedef unsigned __int16 uint16_t;

/*! Portable 32 bit-wide signed integer type. */
typedef __int32 int32_t;
/*! Portable 32 bit-wide unsigned integer type. */
typedef unsigned __int32 uint32_t;

/*! Portable 64 bit-wide signed integer type. */
typedef __int64 int64_t;
/*! Portable 64 bit-wide unsigned integer type. */
typedef unsigned __int64 uint64_t;

#           if defined(_WIN64)
                /*! Portable signed integer type capable of holding a pointer. */
typedef __int64 intptr_t;
/*! Portable unsigned integer type capable of holding a pointer. */
typedef unsigned __int64 uintptr_t;
#           else
                /*! Portable signed integer type capable of holding a pointer. */
typedef __int32 intptr_t;
/*! Portable unsigned integer type capable of holding a pointer. */
typedef unsigned __int32 uintptr_t;
#           endif
#       endif // _STDINT
#   endif // _MSC_VER >= 1600


/*! Mimic c99 built-in _Bool type. */
#if defined(__cplusplus)
    /* for C++ builds use the same typedef as in <yvals.h> */
typedef bool _Bool;
#   if defined(_MSC_VER)
#       define _Bool ::_Bool
#       define PYLONC_BOOL_DEFINED
#   endif
#else
    /* for VC Version >= 1800 : _Bool is now a proper type and you can't create identifiers with that name */
    /* for embarcadero C++ Builder >= 2009 : _Bool is now a proper type and you can't create identifiers with that name */
#   if (defined(_MSC_VER) && _MSC_VER <= 1700) || (defined(__BORLANDC__) && __BORLANDC__ < 0x0610 )
typedef unsigned char _Bool;
#   endif
#endif


#elif (defined(__GNUC__) && (defined(__linux__)) || defined(__APPLE__))
#   include <stdint.h>

    /* Mimic c99 built-in _Bool type. */
#   if defined(__cplusplus)
typedef bool _Bool;
#   else
        /* gcc has built-in _Bool type for C, even for older standard than c99 */
        /*typedef unsigned char _Bool;*/
#   endif

#else
#   error No platform-specific type definitions
#endif /* __STDC_VERSION__ >= 199901L */



#ifndef INT64_MAX
#   define INT64_MAX   0x7fffffffffffffffLL    /* Maximum signed int64 value. */
#endif

#ifndef INT64_MIN
#   define INT64_MIN   0x8000000000000000LL    /* Minimum signed int64 value. */
#endif

#ifndef UINT64_MAX
#   define UINT64_MAX  0xffffffffffffffffULL   /* Maximum unsigned int64 value. */
#endif

#ifndef INT32_MAX
#   define INT32_MAX   0x000000007fffffffLL    /* Maximum signed int32 value. */
#endif

#ifndef INT32_MIN
#   define INT32_MIN   0xffffffff80000000LL    /* Minimum signed int32 value. */
#endif

#ifndef UINT32_MAX
#   define UINT32_MAX  0x00000000ffffffffULL   /* Maximum unsigned int32 value. */
#endif

#ifndef INT8_MAX
#   define INT8_MAX    0x000000000000007fLL    /* Maximum signed int8 value. */
#endif

#ifndef INT8_MIN
#   define INT8_MIN    0xffffffffffffff80LL    /* Minimum signed int8 value. */
#endif

#ifndef UINT8_MAX
#   define UINT8_MAX   0x00000000000000ffULL   /* Maximum unsigned int8 value. */
#endif

#ifdef PYLONC_BOOL_DEFINED
#   undef _Bool
#   undef PYLONC_BOOL_DEFINED
#endif


#endif /* GENAPIC_TYPES_H */
