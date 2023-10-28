//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Camera Link specific grab result data class.
*/
#ifndef INCLUDED_BASLERCAMERALINKGRABRESULTDATA_H_7474481
#define INCLUDED_BASLERCAMERALINKGRABRESULTDATA_H_7474481

#include <pylon/GrabResultData.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiCameraLink
     * @{
     */
    // This dummy implementation is used by the Device Specific Instant Camera for Camera Link
    // because the Camera Link Transport Layer does not support some features.
    class CCameraLinkDummyChunkData_Params
    {
    public:
        void _Initialize( GENAPI_NAMESPACE::INodeMap* )
        {
        }
    };

    /// The Camera Link specific grab result data class.
    class CBaslerCameraLinkGrabResultData : public CGrabResultData, public CCameraLinkDummyChunkData_Params
    {
    protected:
        // Internal use only. The grab result data class should only be created by the Instant Camera class.
        friend class CBaslerCameraLinkInstantCamera;
        CBaslerCameraLinkGrabResultData()
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

#endif /* INCLUDED_BASLERCAMERALINKGRABRESULTDATA_H_7474481 */
