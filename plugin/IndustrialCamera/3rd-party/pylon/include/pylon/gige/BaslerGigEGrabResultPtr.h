//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Pylon GigE specific grab result data class.
*/

#ifndef INCLUDED_BASLERGIGEGRABRESULTPTR_H_4564157
#define INCLUDED_BASLERGIGEGRABRESULTPTR_H_4564157

#include <pylon/gige/BaslerGigEGrabResultData.h>
#include <pylon/private/DeviceSpecificGrabResultPtr.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGigE
     * @{
     */

    /// The GigE specific grab result smart pointer.
    PYLON_DEFINE_DEVICE_SPECIFIC_GRAB_RESULT_PTR( CBaslerGigEGrabResultPtr, CBaslerGigEGrabResultData )

    /**
     * @}
     */
} // namespace Pylon

#endif /* INCLUDED_BASLERGIGEGRABRESULTPTR_H_4564157 */
