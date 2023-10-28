//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2012-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief USB specific grab result data class.
*/
#ifndef INCLUDED_BASLERUSBGRABRESULTDATA_H_7474481
#define INCLUDED_BASLERUSBGRABRESULTDATA_H_7474481

#include <pylon/usb/_UsbChunkData.h>
#include <pylon/GrabResultData.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiUsb
     * @{
     */

    /// The USB specific grab result data class.
    class CBaslerUsbGrabResultData : public CGrabResultData, public Basler_UsbChunkData::CUsbChunkData_Params
    {
    protected:
        // Internal use only. The grab result data class should only be created by the Instant Camera class.
        friend class CBaslerUsbInstantCamera;
        CBaslerUsbGrabResultData()
        {
        }

        // Internal use only.
        virtual void Destroy()
        {
            delete this;
        }

        // Internal use only.
        virtual void Initialize()
        {
            _Initialize( &GetChunkDataNodeMap() );
        }
    };

    /**
     * @}
     */
}

#endif /* INCLUDED_BASLERUSBGRABRESULTDATA_H_7474481 */
