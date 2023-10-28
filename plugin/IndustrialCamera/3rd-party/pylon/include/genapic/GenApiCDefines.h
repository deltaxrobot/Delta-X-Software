/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2012-2021 Basler AG
    http://www.baslerweb.com
-----------------------------------------------------------------------------*/
/**
    \file
    \brief    Platform-dependent macro definitions.
 */
#ifndef GenApiCDefines_h__
#define GenApiCDefines_h__

#if defined (_MSC_VER) || defined (__BORLANDC__) || defined (__MINGW32__)
#   define GENAPIC_WIN_BUILD        /**< Will be set when building for windows platforms. */
#elif  (defined(__GNUC__) && (defined(__linux__)) || defined(__APPLE__))
#   define GENAPIC_LINUX_BUILD      /**< Will be set when building for linux platforms. */
#else
#   error Unsupported platform
#endif

#if defined (GENAPIC_WIN_BUILD)
#   if defined (GENAPIC_EXPORTS) && defined (__cplusplus)
#       define GENAPIC_API __declspec(dllexport)
#   else
#       define GENAPIC_API __declspec(dllimport)
#   endif
#   define GENAPIC_CC __stdcall
#   define GENAPIC_PACKING 8
#elif defined (GENAPIC_LINUX_BUILD)
#   if defined (GENAPIC_EXPORTS) && defined (__cplusplus)
#       define GENAPIC_API __attribute__((visibility("default")))
#   else
#       define GENAPIC_API
#   endif
#   define GENAPIC_CC
#   define GENAPIC_PACKING 8
#else
#   error Unsupported platform
#endif

#ifndef _HRESULT_DEFINED
#   define _HRESULT_DEFINED
    typedef long HRESULT;
#endif /* !_HRESULT_DEFINED */

#endif /* GenApiCDefines_h__ */
