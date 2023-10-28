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

#ifndef INCLUDED_BASLERUNIVERSALGRABRESULTDATA_H
#define INCLUDED_BASLERUNIVERSALGRABRESULTDATA_H

#pragma once

#include <pylon/_BaslerUniversalChunkDataParams.h>
#include <pylon/GrabResultData.h>

namespace Pylon
{
     /** \addtogroup Pylon_InstantCameraApiUniversal
     * @{
     */

    /// The Universal grab result data.
    class CBaslerUniversalGrabResultData : public CGrabResultData, public Basler_UniversalChunkDataParams::CUniversalChunkDataParams_Params
    {
    protected:
        // Internal use only. The grab result data class should only be created by the instant camera class.
        friend class CBaslerUniversalInstantCamera;
        CBaslerUniversalGrabResultData()
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
} // namespace Pylon

#endif /* INCLUDED_BASLERUNIVERSALGRABRESULTDATA_H */
