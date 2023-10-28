//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/*!
\file
\brief    Defines for IPTrans.

*/

#ifndef PYLONCLSER_DEFS_H_INCLUDED
#define PYLONCLSER_DEFS_H_INCLUDED

#include <pylon/Platform.h>

// PYLONCLSER_API
#ifdef PYLONCLSER_EXPORTS
#   define PYLONCLSER_API APIEXPORT
#else
#   define PYLONCLSER_API APIIMPORT
#endif

#endif // PYLONCLSER_DEFS_H_INCLUDED
