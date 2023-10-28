//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2012-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief USB specific instant camera array class.
*/
#ifndef INCLUDED_BASLERUSBINSTANTCAMERAARRAY_H_5817072
#define INCLUDED_BASLERUSBINSTANTCAMERAARRAY_H_5817072

#include <pylon/usb/BaslerUsbInstantCamera.h>
#include <pylon/private/DeviceSpecificInstantCameraArray.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiUsb
     * @{
     */

    /*!
    \class  CBaslerUsbInstantCameraArray
    \brief  USB specific instant camera array

    \threading
        The CBaslerUsbInstantCameraArray class is not thread-safe.

    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCameraArray instead.
    */
    PYLON_6_0_DEPRECATED( "Use CBaslerUniversalInstantCameraArray" )
        class CBaslerUsbInstantCameraArray : public CDeviceSpecificInstantCameraArrayT<CBaslerUsbInstantCamera>
    {
    public:
        /*!
            \copybrief CInstantCameraArray::CInstantCameraArray()
            \copydetails CInstantCameraArray::CInstantCameraArray()
        */
        CBaslerUsbInstantCameraArray()
        {
        }
              /*!
                  \copybrief CInstantCameraArray::CInstantCameraArray( size_t)
                  \copydetails CInstantCameraArray::CInstantCameraArray( size_t)
              */
        CBaslerUsbInstantCameraArray( size_t numberOfCameras ) : CDeviceSpecificInstantCameraArrayT<CBaslerUsbInstantCamera>( numberOfCameras )
        {
        }
        /*!
            \copybrief CInstantCameraArray::~CInstantCameraArray()
            \copydetails CInstantCameraArray::~CInstantCameraArray()
        */
        virtual ~CBaslerUsbInstantCameraArray()
        {
        }
    };

    /**
     * @}
     */
}

#endif /* INCLUDED_BASLERUSBINSTANTCAMERAARRAY_H_5817072 */
