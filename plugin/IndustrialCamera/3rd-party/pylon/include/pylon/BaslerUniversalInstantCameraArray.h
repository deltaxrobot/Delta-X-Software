//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief pylon universal instant camera array class.
*/

#ifndef INCLUDED_BASLERUNIVERSALINSTANTCAMERAARRAY_H
#define INCLUDED_BASLERUNIVERSALINSTANTCAMERAARRAY_H

#pragma once

#include <pylon/BaslerUniversalInstantCamera.h>
#include <pylon/private/DeviceSpecificInstantCameraArray.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiUniversal
     * @{
     */

    /*!
    \class  CBaslerUniversalInstantCameraArray
    \brief  Universal instant camera array.

    \threading
        The CBaslerUniversalInstantCameraArray class is not thread-safe.
    */
    class CBaslerUniversalInstantCameraArray : public CDeviceSpecificInstantCameraArrayT<CBaslerUniversalInstantCamera>
    {
    public:
        /*!
            \copybrief CInstantCameraArray::CInstantCameraArray()
            \copydetails CInstantCameraArray::CInstantCameraArray()
        */
        CBaslerUniversalInstantCameraArray()
        {
        }
              /*!
                  \copybrief CInstantCameraArray::CInstantCameraArray( size_t)
                  \copydetails CInstantCameraArray::CInstantCameraArray( size_t)
              */
        CBaslerUniversalInstantCameraArray( size_t numberOfCameras ) : CDeviceSpecificInstantCameraArrayT<CBaslerUniversalInstantCamera>( numberOfCameras )
        {
        }

    };

    /**
     * @}
     */
} // namespace Pylon

#endif /* INCLUDED_BASLERUNIVERSALINSTANTCAMERAARRAY_H */
