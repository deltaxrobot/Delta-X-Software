//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Contains a class that makes the data for one grabbed buffer available.
*/

#ifndef INCLUDED_GRABRESULTDATA_H_1758952
#define INCLUDED_GRABRESULTDATA_H_1758952

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/PixelType.h>
#include <pylon/PayloadType.h>
#include <GenApi/GenApiDll.h> // [temporary] namespace alias
#include <GenICamFwd.h>

namespace Pylon
{
    // Forward declaration
    class CPylonDataContainer;
    class CPylonDataComponent;

    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

    /*!
    \class  CGrabResultData
    \brief  Makes the data for one grabbed buffer available.
    */
    class PYLONBASE_API CGrabResultData
    {
    public:
        /// Returns true if an image has been grabbed successfully and false in the case of an error.
        bool GrabSucceeded() const;


        /// This method returns a description of the error if GrabSucceeded() returns false due to an error.
        String_t GetErrorDescription() const;


        /// This method returns the error code if GrabSucceeded() returns false due to an error.
        uint32_t GetErrorCode() const;


        /// Get the current payload type.
        EPayloadType GetPayloadType() const;


        /// Get the current pixel type.
        EPixelType GetPixelType() const;


        /// Get the current number of columns.
        uint32_t GetWidth() const;


        /// Get the current number of rows expressed as number of pixels.
        uint32_t GetHeight() const;


        /// Get the current starting column.
        uint32_t GetOffsetX() const;


        /// Get the current starting row.
        uint32_t GetOffsetY() const;


        /// Get the number of extra data at the end of each row in bytes.
        uint32_t GetPaddingX() const;


        /// Get the number of extra data at the end of the image data in bytes.
        uint32_t GetPaddingY() const;


        /// Get the pointer to the buffer.
        /*!
        If the chunk data feature is activated for the device, chunk data is appended to the image data.
        When writing past the image section while performing image processing, the chunk data will be corrupted.
        */
        void* GetBuffer() const;


        /// Get the current payload size in bytes.
        size_t GetPayloadSize() const;

        /// Get the size of the buffer returned by GetBuffer() in bytes.
        size_t GetBufferSize() const;


        /// Get the block ID of the grabbed frame (camera device specific).
        /*!
        \par IEEE 1394 Camera Devices
        The value of Block ID is always UINT64_MAX.

        \par GigE Camera Devices
        The sequence number starts with 1 and
        wraps at 65535. The value 0 has a special meaning and indicates
        that this feature is not supported by the camera.

        \par USB Camera Devices
        The sequence number starts with 0 and uses the full 64 Bit range.

        \attention A block ID with the value UINT64_MAX indicates that the block ID is invalid and must not be used.
        */
        uint64_t GetBlockID() const;

        /// Get the camera specific tick count (camera device specific).
        /*!
        This describes when the image exposure was started.
        Cameras that do not support this feature return zero. If supported, this
        can be used to determine which image AOIs were acquired simultaneously.
        */
        uint64_t GetTimeStamp() const;


        /// Get the stride in bytes.
        /*
            Uses Pylon::ComputeStride to compute the stride from the result data.

        \return The stride in byte.

        \pre The preconditions of Pylon::ComputeStride must be met.

        \error
            Throws an exception if the stride value cannot be computed from the result data.
        */
        bool GetStride( size_t& strideBytes ) const;


        /// Get the size of the image in byte.
        /*
            Uses Pylon::ComputeBufferSize to compute the stride from the result data.
            PaddingY is not taken into account.

        \return The buffer size in byte.

        \pre The preconditions of Pylon::ComputeBufferSize must be met.

        \error
            Throws an exception if the buffer size cannot be computed from the result data.
        */
        size_t GetImageSize() const;


        /// Get the context value assigned to the camera object. The context is attached to the result when it is retrieved.
        intptr_t GetCameraContext() const;


        /// Get the ID of the grabbed image.
        /*! Always returns a number larger than 0. The counting starts with 1 and is never reset during the lifetime of the Instant Camera object. */
        int64_t GetID() const;


        /// Get the number of the image. This number is incremented when an image is retrieved using CInstantCamera::RetrieveResult().
        /*! Always returns a number larger than 0. The counting starts with 1 and is reset with every call to CInstantCamera::StartGrabbing(). */
        int64_t GetImageNumber() const;


        /// Get the number of skipped images before this image.
        /*!
        This value can be larger than 0 if EGrabStrategy_LatestImageOnly grab strategy or GrabStrategy_LatestImages grab strategy is used.
        Always returns a number larger than or equal 0. This number does not include the number of images lost in case of a buffer underrun in the driver.
        */
        int64_t GetNumberOfSkippedImages() const;


        /// Returns true if chunk data is available.
        /*!
        This is the case if the chunk mode is enabled for the camera device.
        The parameter CInstantCamera::ChunkNodeMapsEnable of the used Instant Camera object is set to true (default setting).
        Chunk data node maps are supported by the Transport Layer of the camera device.
        */
        bool IsChunkDataAvailable() const;


        /// Get the reference to the chunk data node map connected to the result.
        /*! An empty node map is returned when the device does not support this feature or when chunks are disabled. */
        GENAPI_NAMESPACE::INodeMap& GetChunkDataNodeMap() const;


        /// Checks if buffer has a CRC attached. This needs not be activated for the device. See the PayloadCRC16 chunk.
        /* The chunk feature must be supported and activated, otherwise false is returned. */
        bool HasCRC() const;


        /// Checks CRC sum of buffer, returns true if CRC sum is OK.
        /*
        \error
            Throws an exception if GetHasCRC() is false and chunks are activated.
        */
        bool CheckCRC() const;

        /// Get the context value assigned to the buffer. The context is set when CInstamtCamera is using a custom buffer factory.
        intptr_t GetBufferContext() const;

        /// Returns the grab result as a CPylonDataContainer.
        CPylonDataContainer GetDataContainer() const;

        /// \copydoc Pylon::CPylonDataContainer::GetDataComponentCount()
        size_t GetDataComponentCount() const;

        /// \copydoc Pylon::CPylonDataContainer::GetDataComponent()
        CPylonDataComponent GetDataComponent( size_t index );

        /// Internal use only.
        class CGrabResultDataImpl;
        CGrabResultDataImpl* GetGrabResultDataImpl();
        virtual ~CGrabResultData();

    private:
        ///The grab result data object can not be copied.
        CGrabResultData( const CGrabResultData& );
        ///The grab result data object can not be copied.
        void operator = ( const CGrabResultData& );
    protected:

        /// Internal use only. The grab result data class should only be created by the instant camera class.
        friend class CInstantCamera;
        CGrabResultData();

    private:
        virtual void Destroy();
        virtual void Initialize();

        // Internal use only. Subject to change without notice.
        friend class CGrabResultDataFactory;
        CGrabResultDataImpl* m_pImpl;

        // The grab result data
        const void*& m_pBuffer;
        size_t& m_bufferSize;
        bool& m_grabSucceeded;
        EPayloadType& m_payloadType;
        EPixelType& m_pixelType;
        uint64_t& m_timeStamp;
        uint32_t& m_width;
        uint32_t& m_height;
        uint32_t& m_offsetX;
        uint32_t& m_offsetY;
        uint32_t& m_paddingX;
        uint32_t& m_paddingY;
        uint64_t& m_payloadSize;
        uint32_t& m_errorCode;
        String_t& m_errorDescription;
        intptr_t& m_cameraContext;
        int64_t& m_ID;
        int64_t& m_imageNumber;
        int64_t& m_skippedImageCount;
        intptr_t& m_bufferContext;
        uint64_t& m_blockId;
    };

    /**
     * @}
     */

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_GRABRESULTDATA_H_1758952 */
