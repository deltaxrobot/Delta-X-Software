//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2008-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/*!
\file     PylonLinkage.h
\brief    Adds the pylon (and GenICam) libs to the linker comment record in the object file
*/

#ifndef PYLON_LINKAGE_H_INCLUDED_
#define PYLON_LINKAGE_H_INCLUDED_

#pragma once

// needed for COMPILER/COMPILER_STR
#include <pylon/Platform.h>

#if defined(PYLON_WIN_BUILD)

#define PYLON_VERSION_SUFFIX "_v6_2"

#if !defined(PYLON_BUILD_DEBUG)
#   if !defined(GENICAM_USER_ALWAYS_LINK_RELEASE)
#       define GENICAM_USER_ALWAYS_LINK_RELEASE
#   endif
#endif

// should be already included (needed for CONFIGURATION, GENICAM_COMPILER_STR)
#include <GenICamVersion.h>
#include <Base/GCLinkage.h>


//////////////////////////////////////////////////////////////////////////////
// create the Pylon suffix

// The name consists of the following parts
//    PylonBased.lib
//    [   1   ] [ 2 ] [ 3 ]
//    [module ] [ suffix  ]
//    [     lib name      ]
//    1 = module name
//    2 = configuration
//    3 = extension
#define PYLON_SUFFIX( config, extension ) config "." extension

#if (defined(_DEBUG) || defined(DEBUG)) && defined(PYLON_BUILD_DEBUG)
#   define PYLON_CONFIGURATION "d"
#else
#   define PYLON_CONFIGURATION ""
#endif

// generic
#define PYLON_LIB_SUFFIX        PYLON_SUFFIX( PYLON_VERSION_SUFFIX PYLON_CONFIGURATION, "lib" )
#define PYLON_DLL_SUFFIX        PYLON_SUFFIX( PYLON_VERSION_SUFFIX PYLON_CONFIGURATION, "dll" )

// names for Transport Layer
#define PYLON_TL_LIB_SUFFIX     PYLON_SUFFIX( PYLON_VERSION_SUFFIX PYLON_CONFIGURATION "_TL", "lib" )
#define PYLON_TL_DLL_SUFFIX     PYLON_SUFFIX( PYLON_VERSION_SUFFIX PYLON_CONFIGURATION "_TL", "dll" )


//////////////////////////////////////////////////////////////////////////////
//
#define PYLON_LIB_NAME_NAKED( module )  module PYLON_SUFFIX( PYLON_CONFIGURATION, "lib" )
#define PYLON_DLL_NAME_NAKED( module )  module PYLON_SUFFIX( PYLON_CONFIGURATION, "dll" )

#define PYLON_LIB_NAME( module )  module PYLON_SUFFIX( PYLON_VERSION_SUFFIX PYLON_CONFIGURATION, "lib" )
#define PYLON_DLL_NAME( module )  module PYLON_SUFFIX( PYLON_VERSION_SUFFIX PYLON_CONFIGURATION, "dll" )

#define PYLON_TL_LIB_NAME( module )  module PYLON_TL_LIB_SUFFIX
#define PYLON_TL_DLL_NAME( module )  module PYLON_TL_DLL_SUFFIX

#endif

#endif
