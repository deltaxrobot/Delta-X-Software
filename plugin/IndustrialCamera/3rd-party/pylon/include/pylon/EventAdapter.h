//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  HN
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Definition of the IEventAdapter interface
*/
#ifndef __PYLON_EVENT_ADAPTER_H__
#define __PYLON_EVENT_ADAPTER_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


#include <pylon/stdinclude.h>

namespace Pylon
{
    /*!
        \interface IEventAdapter
        \brief Low Level API: IEventAdapter delivers event messages to ports
        \ingroup Pylon_LowLevelApi
    */
    interface PUBLIC_INTERFACE IEventAdapter
    {
        //! Deliver message
        virtual void DeliverMessage( const uint8_t msg[], uint32_t numBytes ) = 0;
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__PYLON_EVENT_ADAPTER_H__
