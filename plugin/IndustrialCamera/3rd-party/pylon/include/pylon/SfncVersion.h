//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2009-2021 Basler AG
//  http://www.baslerweb.com
//  Author: Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief  Contains the support for SFNC version handling.
*/

#ifndef INCLUDED_SFNCVERSION_H_3193628
#define INCLUDED_SFNCVERSION_H_3193628

#include <pylon/Platform.h>
#include <pylon/PylonVersionInfo.h>

#ifdef PYLON_LINUX_BUILD
#   undef GCC_VERSION
#   define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#   undef GCC_DIAGNOSTIC_AWARE
#   define GCC_DIAGNOSTIC_AWARE          (GCC_VERSION >= 40200)
#   undef GCC_DIAGNOSTIC_PUSH_POP_AWARE
#   define GCC_DIAGNOSTIC_PUSH_POP_AWARE (GCC_VERSION >= 40600)
#else
#   undef GCC_DIAGNOSTIC_AWARE
#   define GCC_DIAGNOSTIC_AWARE 0
#endif

#if defined (PYLON_OSX_BUILD)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wunknown-pragmas"
#endif

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic push
#   endif
#   pragma GCC diagnostic ignored "-Wunknown-pragmas"
#   pragma GCC diagnostic ignored "-Wpragmas"   // gcc < 4.6 doesn't know the following pragma
#   pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#include <GenApi/GenApi.h>

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wunknown-pragmas"
#       pragma GCC diagnostic warning "-Wunused-but-set-variable"
#       pragma GCC diagnostic warning "-Wpragmas"   // gcc < 4.6 doesn't know the pragma
#   endif
#endif

#include <GenApi/Pointer.h>
#include <GenApi/INodeMap.h>

#if defined (PYLON_OSX_BUILD)
#   pragma clang diagnostic pop
#endif

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */
    /// Constant for undefined SFNC version.
    static const VersionInfo Sfnc_VersionUndefined( 0, 0, 0 );
    /// Constant for SFNC version 1.2.1.
    static const VersionInfo Sfnc_1_2_1( 1, 2, 1 );
    /// Constant for SFNC version 1.3.0.
    static const VersionInfo Sfnc_1_3_0( 1, 3, 0 );
    /// Constant for SFNC version 1.4.0.
    static const VersionInfo Sfnc_1_4_0( 1, 4, 0 );
    /// Constant for SFNC version 1.5.0.
    static const VersionInfo Sfnc_1_5_0( 1, 5, 0 );
    /// Constant for SFNC version 1.5.1.
    static const VersionInfo Sfnc_1_5_1( 1, 5, 1 );
    /// Constant for SFNC version 2.0.0. This version or a later version is used by USB camera devices.
    static const VersionInfo Sfnc_2_0_0( 2, 0, 0 );
    /// Constant for SFNC version 2.1.0
    static const VersionInfo Sfnc_2_1_0( 2, 1, 0 );
    /// Constant for SFNC version 2.2.0
    static const VersionInfo Sfnc_2_2_0( 2, 2, 0 );
    /// Constant for SFNC version 2.3.0
    static const VersionInfo Sfnc_2_3_0( 2, 3, 0 );
    /// Constant for SFNC version 2.4.0
    static const VersionInfo Sfnc_2_4_0( 2, 4, 0 );
    /// Constant for SFNC version 2.5.0
    static const VersionInfo Sfnc_2_5_0( 2, 5, 0 );


    /**
     * @}
     */

    /// Helper function for getting the SFNC version from the camera device node map.
    inline VersionInfo GetSfncVersion( GENAPI_NAMESPACE::INodeMap* pNodeMap )
    {
        // If pNodeMap is a valid node map.
        if (pNodeMap)
        {
            // Check to see whether node for major version exists.
            GENAPI_NAMESPACE::CIntegerPtr major = pNodeMap->GetNode( "DeviceSFNCVersionMajor" );
            if (major)
            {
                // Get further version Info.
                GENAPI_NAMESPACE::CIntegerPtr minor = pNodeMap->GetNode( "DeviceSFNCVersionMinor" );
                GENAPI_NAMESPACE::CIntegerPtr subminor = pNodeMap->GetNode( "DeviceSFNCVersionSubMinor" );

                if (!IsReadable( major ) || !IsReadable( minor ) || !IsReadable( subminor ))
                {
                    throw RUNTIME_EXCEPTION( "Failed to read SFNC version from camera device node map." );
                }

                VersionInfo v( static_cast<unsigned int>(major->GetValue()),
                               static_cast<unsigned int>(minor->GetValue()),
                               static_cast<unsigned int>(subminor->GetValue()) );
                return v;
            }
        }

        return Sfnc_VersionUndefined;
    }
}

#endif /* INCLUDED_SFNCVERSION_H_3193628 */
