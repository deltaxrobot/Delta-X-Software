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

#ifndef INCLUDED_BASLERGIGEGRABRESULTDATA_H_4046292
#define INCLUDED_BASLERGIGEGRABRESULTDATA_H_4046292

#include <pylon/gige/_GigEChunkData.h>
#include <pylon/GrabResultData.h>

namespace Pylon
{
     /** \addtogroup Pylon_InstantCameraApiGigE
     * @{
     */

    /// The GigE specific grab result data.
    class CBaslerGigEGrabResultData : public CGrabResultData, public Basler_GigEChunkData::CGigEChunkData_Params
    {
    protected:
        // Internal use only. The grab result data class should only be created by the instant camera class.
        friend class CBaslerGigEInstantCamera;
        CBaslerGigEGrabResultData()
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

#endif /* INCLUDED_BASLERGIGEGRABRESULTDATA_H_4046292 */
