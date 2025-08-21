//-----------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  BR
//-----------------------------------------------------------------------------
/*
 \file

 \brief
    Defines for the pylon Data Processing library.
*/

#pragma once

#include <pylon/Platform.h>
#include <pylon/PylonLinkage.h>

#include <pylondataprocessing/PylonDataProcessingVersion.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#if defined(PYLON_DATAPROCESSING_API_STATIC)
#  define PYLONDATAPROCESSING_API
#else
#  ifdef PYLONDATAPROCESSING_LIBRARY
#    define PYLONDATAPROCESSING_API APIEXPORT
#  else
#    define PYLONDATAPROCESSING_API APIIMPORT
#  endif
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

//////////////////////////////////////////////////////////////////////////////
// Add the pylon data processing import library
#if defined(PYLON_WIN_BUILD)
#  define PYLON_DATAPROCESSING_LIB_NAME( module )  module PYLON_SUFFIX( PYLON_DATAPROCESSING_VERSION_SUFFIX "", "lib" )
#  ifndef PYLON_DATAPROCESSING_NO_AUTO_IMPLIB
#    pragma comment(lib, PYLON_DATAPROCESSING_LIB_NAME( "PylonDataProcessing" ))
#  endif
#endif
