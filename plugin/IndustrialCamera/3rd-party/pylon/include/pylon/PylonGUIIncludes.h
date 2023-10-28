//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  NN
//-----------------------------------------------------------------------------
/*!
\file
\brief  Master include for Pylon GUI.
If you intend to use the GUI classes and functions you must include this file explicitly.
This file will \e not be included automatically when you include pylon/PylonIncludes.h.

\sa \link Pylon::CPylonImageWindow CPylonImageWindow \endlink
\sa \link Pylon::DisplayImage DisplayImage \endlink
*/

#ifndef PYLON_GUI_INCLUDEDS_H_INCLUDED__
#define PYLON_GUI_INCLUDEDS_H_INCLUDED__

#include <pylon/Platform.h>
#include <pylon/PylonLinkage.h>

#include <pylon/PylonGUI.h>

// Add the lib to the linkers input libraries.
#if defined(_MSC_VER) && defined(PYLON_WIN_BUILD)
#   ifndef PYLON_NO_AUTO_IMPLIB
#       pragma comment(lib, PYLON_LIB_NAME( "PylonGUI" ))
#   endif
#endif

#endif // PYLON_GUI_INCLUDEDS_H_INCLUDED__
