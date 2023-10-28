//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief pylon universal grab result data class.
*/

#ifndef INCLUDED_BASLERUNIVERSALGRABRESULTPTR_H
#define INCLUDED_BASLERUNIVERSALGRABRESULTPTR_H

#pragma once

#include <pylon/BaslerUniversalGrabResultData.h>
#include <pylon/private/DeviceSpecificGrabResultPtr.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiUniversal
     * @{
     */

    /// The Universal grab result smart pointer.
    PYLON_DEFINE_DEVICE_SPECIFIC_GRAB_RESULT_PTR( CBaslerUniversalGrabResultPtr, CBaslerUniversalGrabResultData )

    /**
     * @}
     */
} // namespace Pylon

#endif /* INCLUDED_BASLERUNIVERSALGRABRESULTPTR_H */
