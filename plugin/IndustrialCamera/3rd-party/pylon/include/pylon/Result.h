//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief    Low Level API: Definition of classes that contain grabbed data.
*/
#pragma once

#ifndef RESULT_H__
#define RESULT_H__


#include <limits.h>
#include <memory.h> // for memset
#include <Base/GCTypes.h>
#include <Base/GCException.h>

#include <pylon/Platform.h>
#include <pylon/StreamGrabber.h>
#include <pylon/PixelType.h>
#include <pylon/PayloadType.h>
#include <pylon/ResultImage.h>

#pragma pack(push, PYLON_PACKING)

// Microsoft Visual Studio defines SIZE_MAX (see limits.h)
// But VS 2003 does not define SIZE_MAX. In this case, we have to define SIZE_MAX
// Because of this, the following lines must be AFTER #include limits.h
#ifndef SIZE_MAX
#define SIZE_MAX UINT_MAX
#endif

namespace Pylon
{
    // Forward declaration
    class CPylonDataContainer;
    class CPylonDataComponent;
    class GrabResult;
    typedef CGrabResultImageT<const GrabResult&> CGrabResultImageRef;

    ///////////////////////////////////////////////////////////////////////
    /// \brief Low Level API: Possible grab status values
    ///
    /// \ingroup Pylon_LowLevelApi
    enum EGrabStatus
    {
        GrabStatus_Undefined = -1,
        _UndefinedGrabStatus = GrabStatus_Undefined, // Consider using GrabStatus_Undefined instead.

        GrabStatus_Idle,                //!< Currently not used.
        Idle = GrabStatus_Idle,         //!< Currently not used. For backward compatibility only.

        GrabStatus_Queued,              //!< Grab request is in the input queue.
        Queued = GrabStatus_Queued,     //!< Grab request is in the input queue. For backward compatibility only. Consider using GrabStatus_Queued instead.

        GrabStatus_Grabbed,             //!< Grab request terminated successfully. Buffer is filled with data.
        Grabbed = GrabStatus_Grabbed,   //!< Grab request terminated successfully. Buffer is filled with data. For backward compatibility only. Consider using GrabStatus_Grabbed instead.

        GrabStatus_Canceled,            //!< Grab request was canceled. Buffer doesn't contain valid data.
        Canceled = GrabStatus_Canceled, //!< Grab request was canceled. Buffer doesn't contain valid data. For backward compatibility only. Consider using GrabStatus_Canceled instead.

        GrabStatus_Failed,              //!< Grab request failed. Buffer doesn't contain valid data.
        Failed = GrabStatus_Failed      //!< Grab request failed. Buffer doesn't contain valid data. For backward compatibility only. Consider using GrabStatus_Queued instead.
    };

    /// Retrieve the number of bits per pixel for a given pixel type
#define BIT_PER_PIXEL( pixelType ) ( ( (pixelType) >> 16 ) & 0xff )


    ///////////////////////////////////////////////////////////////////////
    /// \brief Low Level API: A grab result that combines the used image buffer and status information.
    ///
    /// Note that depending on the used interface technology, the specific camera and
    /// the situation some of the attributes are not meaningful, e. g. timestamp in case
    /// of an canceled grab.
    ///
    /// \ingroup  Pylon_LowLevelApi
    class PYLONBASE_API GrabResult
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        //
        GrabResult()
            : m_pContext( NULL )
            , m_hBuffer( NULL )
            , m_pBuffer( NULL )
            , m_BufferSize( 0 )
            , m_Status( GrabStatus_Undefined )
            , m_PayloadType( PayloadType_Undefined )
            , m_PixelType( PixelType_Undefined )
            , m_TimeStamp( 0 )
            , m_SizeX( -1 )
            , m_SizeY( -1 )
            , m_OffsetX( -1 )
            , m_OffsetY( -1 )
            , m_PaddingX( -1 )
            , m_PaddingY( -1 )
            , m_PayloadSize( (uint64_t) -1 )
            , m_ErrorCode( 0 )
            , m_ErrorDescription( "" )
            , m_BlockID( GC_UINT64_MAX )
        {
        }


        ///////////////////////////////////////////////////////////////////////
        //
        ~GrabResult()
        {
        }


        ///////////////////////////////////////////////////////////////////////
        /// True if status is grabbed.
        bool Succeeded() const
        {
            return m_Status == GrabStatus_Grabbed;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the buffer handle.
        StreamBufferHandle Handle() const
        {
            return m_hBuffer;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the pointer to the buffer.
        void* Buffer() const
        {
            return const_cast<void*>(m_pBuffer);
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the grab status.
        EGrabStatus Status() const
        {
            return m_Status;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the pointer the user provided context.
        const void* Context() const
        {
            return m_pContext;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the actual payload type.
        EPayloadType GetPayloadType() const
        {
            return m_PayloadType;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the actual pixel type. This is only defined in case of image data.
        EPixelType GetPixelType() const
        {
            return m_PixelType;
        }


        ///////////////////////////////////////////////////////////////////////
        /// \brief Get the camera specific tick count.
        ///
        /// In case of GigE-Vision this describes when the image exposure was started.
        /// Cameras that do not support this feature return zero. If supported this
        /// may be used to determine which ROIs were acquired simultaneously.
        uint64_t GetTimeStamp() const
        {
            return m_TimeStamp;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the actual number of columns in pixel. This is only defined in case of image data.
        int32_t GetSizeX() const
        {
            return m_SizeX;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the actual number of rows in pixel. This is only defined in case of image data.
        int32_t GetSizeY() const
        {
            return m_SizeY;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the actual starting column. This is only defined in case of image data.
        int32_t GetOffsetX() const
        {
            return m_OffsetX;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the actual starting row. This is only defined in case of image data.
        int32_t GetOffsetY() const
        {
            return m_OffsetY;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the number of extra data at the end of each row in bytes. This is only defined in case of image data.
        int32_t GetPaddingX() const
        {
            return m_PaddingX;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the number of extra data at the end of the image data in bytes. This is only defined in case of image data.
        int32_t GetPaddingY() const
        {
            return m_PaddingY;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the number of valid bytes in the buffer returned by Buffer().
        int64_t GetPayloadSize() const
        {
            return m_PayloadSize;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the number of valid bytes in the buffer returned by Buffer() as size_t.
        size_t GetPayloadSize_t() const
        {
#if SIZE_MAX >= 0xffffffffffffffffULL
            return static_cast<size_t>(GetPayloadSize());
#else
            if (m_PayloadSize > SIZE_MAX)
            {
                throw OUT_OF_RANGE_EXCEPTION( "PayloadSize too big" );
            }
            return static_cast<size_t>(m_PayloadSize & SIZE_MAX);
#endif
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get a description of the current error.
        String_t GetErrorDescription() const
        {
            return m_ErrorDescription;
        }


        ///////////////////////////////////////////////////////////////////////
        /// Get the current error code.
        uint32_t GetErrorCode() const
        {
            return m_ErrorCode;
        }


        ///////////////////////////////////////////////////////////////////////
        /// \brief Provides an adapter from the grab result to Pylon::IImage interface.
        ///
        /// This returned adapter allows passing the grab result to saving functions or image format converter.
        ///
        /// \attention The returned reference is only valid as long the grab result is not destroyed.
        CGrabResultImageRef GetImage() const
        {
            return CGrabResultImageRef( *this, false );
        }


        ///////////////////////////////////////////////////////////////////////
        /// \brief Get the block ID of the grabbed frame (camera device specific).
        ///
        /// \par IEEE 1394 Camera Devices
        /// The value of block ID is always UINT64_MAX.
        ///
        /// \par GigE Camera Devices
        /// The sequence number starts with 1 and
        /// wraps at 65535. The value 0 has a special meaning and indicates
        /// that this feature is not supported by the camera.
        ///
        /// \par USB Camera Devices
        /// The sequence number starts with 0 and uses the full 64 Bit range.
        ///
        /// \attention A block ID of value UINT64_MAX indicates that the Block ID is invalid and must not be used.
        uint64_t GetBlockID() const
        {
            return m_BlockID;
        }


        ///////////////////////////////////////////////////////////////////////////////
        /// \copydoc Pylon::CGrabResultData::GetDataContainer()
        CPylonDataContainer GetDataContainer() const;


        ///////////////////////////////////////////////////////////////////////////////
        /// \copydoc Pylon::CPylonDataContainer::GetDataComponentCount()
        size_t GetDataComponentCount() const;


        ///////////////////////////////////////////////////////////////////////////////
        /// \copydoc Pylon::CPylonDataContainer::GetDataComponent()
        CPylonDataComponent GetDataComponent( size_t index );


        ///////////////////////////////////////////////////////////////////////
        /// Get the size of the buffer returned by Buffer().
        size_t GetBufferSize() const
        {
            return m_BufferSize;
        }

    protected:
        const void* m_pContext;
        StreamBufferHandle m_hBuffer;
        const void* m_pBuffer;
        size_t m_BufferSize;

        EGrabStatus m_Status;
        EPayloadType m_PayloadType;
        EPixelType m_PixelType;
        uint64_t m_TimeStamp;
        int32_t m_SizeX;
        int32_t m_SizeY;
        int32_t m_OffsetX;
        int32_t m_OffsetY;
        int32_t m_PaddingX;
        int32_t m_PaddingY;
        uint64_t m_PayloadSize;
        uint32_t m_ErrorCode;
        String_t m_ErrorDescription;
        uint64_t m_BlockID;
    };


    ///////////////////////////////////////////////////////////////////////
    /// \brief Low Level API: An event result
    /// \ingroup Pylon_LowLevelApi
    class EventResult
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        //
        EventResult()
            : m_ReturnCode( 0 )
            , m_Message()
        {
            // prevent uninitialized member warning
            memset( Buffer, 0, sizeof( Buffer ) );
        }


        ///////////////////////////////////////////////////////////////////////
        //
        ~EventResult()
        {
        }


        ///////////////////////////////////////////////////////////////////////
        //
        bool Succeeded() const
        {
            return 0 == m_ReturnCode;
        }


        ///////////////////////////////////////////////////////////////////////
        //
        String_t ErrorDescription() const
        {
            return m_Message;
        }


        ///////////////////////////////////////////////////////////////////////
        //
        unsigned long ErrorCode() const
        {
            return m_ReturnCode;
        }

    protected:
        unsigned long m_ReturnCode;
        String_t m_Message;

    public:
        unsigned char Buffer[576];
    };

    ///////////////////////////////////////////////////////////////////////
    /// \brief Low Level API: Adapts a copy of a grab result to pylon image.
    ///
    /// \attention The referenced grab result must not be destroyed and the result's buffer must not be queued for grabbing again during the lifetime of this object.
    ///
    /// \ingroup  Pylon_LowLevelApi
    typedef CGrabResultImageT<GrabResult> CGrabResultImage;
}

#pragma pack(pop)

#endif // RESULT_H__
