//-----------------------------------------------------------------------------
//  Copyright (c) 2012-2024 Basler AG
//-----------------------------------------------------------------------------
/**
 * \file
 * \brief DLL specific stuff
 */
#pragma once

#ifdef UXTOPAPI_EXPORTS
#define UX_TOPAPI __declspec(dllexport)
#else
#define UX_TOPAPI __declspec(dllimport)
#endif

#define UX_TOPCALL __cdecl

#define UX_TOPPACKING 8

#define USE_WPP_EVENT_TRACING 1
