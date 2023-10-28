//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief    standard definitions
*/
#ifndef __STDINCLUDE_H__
#define __STDINCLUDE_H__

#include <assert.h>

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


#ifdef PYLON_WIN_BUILD
#   include <objbase.h>     // for definition of type 'interface'
#endif


///////////////////////////////////////////////////////////////////////////////
// Note:
///////////////////////////////////////////////////////////////////////////////
// The PY_ macros are only for backward compatibility
// please use the PYLON_ macros instead. Thank you!
///////////////////////////////////////////////////////////////////////////////

// mark a variable as unused. This prevents unused parameter / unused local variable warnings on warning level 4.
#define PYLON_UNUSED(unused_var)    ((void)(unused_var))
#define PY_UNUSED(unused_var)       PYLON_UNUSED(unused_var)

// returns the number of elements in an array
#define PYLON_COUNTOF(arr)          (sizeof(arr)/sizeof(*arr))
#define PY_COUNTOF(arr)             PYLON_COUNTOF(arr)

// PY_ASSERT works like normal assertion
#define PYLON_ASSERT(cond)          assert(cond)
#define PY_ASSERT(cond)             PYLON_ASSERT(cond)
// PY_ASSERT2 works like a normal assertion but can be passed a descriptive text string
#define PYLON_ASSERT2(cond, tx)     assert((cond) && tx)
#define PY_ASSERT2(cond, tx)        PYLON_ASSERT2(cond, tx)

// verify macro
#ifndef NDEBUG
// assert in debug builds but do not remove in release builds
#   define PYLON_VERIFY(cond)       PYLON_ASSERT(cond)
#   define PY_VERIFY(cond)          PYLON_ASSERT(cond)
// assert in debug builds but do not remove in release builds but can be passed a descriptive text string
#   define PYLON_VERIFY2(cond, tx)  PYLON_ASSERT2(cond, tx)
#   define PY_VERIFY2(cond, tx)     PYLON_ASSERT2(cond, tx)
#else
#   define PYLON_VERIFY(cond)       ((void)(cond))
#   define PY_VERIFY(cond)          ((void)(cond))
#   define PYLON_VERIFY2(cond, tx)  PYLON_VERIFY(cond)
#   define PY_VERIFY2(cond, tx)     PYLON_VERIFY(cond)
#endif

#if defined(PYLON_WIN_BUILD)
#   if defined(PYLON_32_BUILD)
#       define PYLON_UNALIGNED
#   elif defined(PYLON_64_BUILD)
#       define PYLON_UNALIGNED __unaligned
#   endif
#elif defined(PYLON_UNIX_BUILD)
#       define PYLON_UNALIGNED
#else
#   error Invalid platform
#endif

// Attention in MSVC this is a string literal
// but under gnuc this is a local variable!
#if defined(_MSC_VER) && _MSC_VER >= 1300
    // Attention this does not behave like a string literal! Use it as a variable of type const char[]
#   define PYLON_FUNC  __FUNCTION__
#elif defined(__GNUC__)
    // Attention this does not behave like a string literal! Use it as a variable of type const char[]
#   define PYLON_FUNC  __func__
#else
    // Attention this does not behave like a string literal! Use it as a variable of type const char[]
#   define PYLON_FUNC  "sorry_funcname_na"
#endif


// namespace aliases
#include <Base/GCNamespace.h>
#include <GenApi/GenApiNamespace.h>

#include <pylon/TypeMappings.h> // for String_t, StringList_t

namespace Pylon
{
    /// Pylon's string definition
    typedef GENICAM_NAMESPACE::gcstring String_t;
    /// Pylon's string list definition
    typedef GENICAM_NAMESPACE::gcstring_vector StringList_t;
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__STDINCLUDE_H__
