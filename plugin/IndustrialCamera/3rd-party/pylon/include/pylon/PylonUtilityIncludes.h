//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2008-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/*!
\file
\brief  Master include for the PylonUtility library
*/

#ifndef PYLONUTILITIESINCLUDES_H_INCLUDED__
#define PYLONUTILITIESINCLUDES_H_INCLUDED__

#include <pylon/Platform.h>
#include <pylon/PylonUtility.h>
#include <pylon/PylonImage.h>
#include <pylon/ImageDecompressor.h>
#include <pylon/ImageFormatConverter.h>
#include <pylon/FeaturePersistence.h>
#include <pylon/ImagePersistence.h>
#if defined(PYLON_WIN_BUILD)
// windows only headers
#    include <pylon/PylonBitmapImage.h>
#    include <pylon/AviWriter.h>
#endif
#include <pylon/VideoWriter.h>

#if defined (PYLON_WIN_BUILD) && !defined (PYLON_NO_AUTO_IMPLIB)
#    include <pylon/PylonLinkage.h>
#    pragma comment(lib, PYLON_LIB_NAME( "PylonUtility" ))
#endif

#endif
