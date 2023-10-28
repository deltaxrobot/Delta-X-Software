//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief  Definition of macros for import/export decorations for PylonGigE library
*/

#ifndef __PYLONGIGE_H__
#define __PYLONGIGE_H__

#if defined _MSC_VER && (_MSC_VER > 1000)
#   pragma once
#endif // _MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef PYLONGIGE_EXPORTS
#   define PYLONGIGE_API APIEXPORT
#else
#   define PYLONGIGE_API APIIMPORT
#endif


#endif // __PYLONGIGE_H__
