//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains a region class.
*/

#pragma once

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylondataprocessing/RegionEntry.h>
#include <pylondataprocessing/RegionType.h>
#include <pylondataprocessing/RegionUserBufferEventHandler.h>
/*!
 * \namespace Pylon
 * \brief The Pylon namespace
 */
namespace Pylon
{
    /*!
     * \namespace Pylon::DataProcessing
     * \brief The DataProcessing namespace
     */
    namespace DataProcessing
    {
        class CVariant;

        /*!
        \class  CRegion
        \brief  Describes a region and takes care of the buffer handling and lifetime.
    
        <ul>
        <li> Automatically handles size and lifetime of the region buffer.
        <li> Allows you to connect user buffers or buffers provided by third-party software packages.
        </ul>
    
        \par Buffer Handling:
        The buffer that is automatically created by the CRegion class or is replaced by a larger buffer if Reset() is called (only if required).
        The size of the allocated buffer is never decreased.
        Referenced user buffers are never automatically replaced by a larger buffer.
        Referenced user buffers can be replaced by a new buffer if the non-const version of GetBuffer() is called.
        See the Reset() method for more details.
        The Release() method can be used to detach a user buffer or to free an allocated buffer.
    
        \threading
            The CRegion class isn't thread-safe.
        */
        class PYLONDATAPROCESSING_API CRegion
        {
        public:
            /*!
            \brief Creates an invalid region.
    
            See Release() for the properties of an invalid region.
    
            \error
                Doesn't throw C++ exceptions.
            */
            CRegion();

            /*!
            \brief Creates a region and allocates a buffer for it.

            \param[in]   regionType The type of the new region.
            \param[in]   dataSize The size of the region in bytes.
                                  For run-length encoded formats, the size in bytes defines the number of entries,
                                  e.g., 24 bytes result in 2 RLE32 entries for RegionType_RLE32.
            \param[in]   referenceWidth  The width of the source of the region if available, 0 otherwise.
            \param[in]   referenceHeight The height of the source of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftX The smallest horizontal pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftY The smallest vertical pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxWidth The width of the bounding box of the region if available, 0 otherwise.
            \param[in]   boundingBoxHeight The height of the bounding box of the region if available, 0 otherwise.

            \pre
            <ul>
            <li> The region type must be valid.
            <li> Either all bounding box values are 0, or \c boundingBoxWidth and \c boundingBoxHeight are both greater than 0.
            </ul>

            \error
                Throws an exception if the parameters are invalid.
                Throws an exception if no buffer with the required size could be allocated.
            */
            CRegion(ERegionType regionType,
                    size_t dataSize,
                    uint32_t referenceWidth = 0,
                    uint32_t referenceHeight = 0,
                    int32_t boundingBoxTopLeftX = 0,
                    int32_t boundingBoxTopLeftY = 0,
                    uint32_t boundingBoxWidth = 0,
                    uint32_t boundingBoxHeight = 0);

            /*!
            \brief  Copies the region properties and creates a reference to the buffer of the source region.
    
            \param[in] source The source region.
    
            \post
            <ul>
            <li> Another reference to the source region buffer is created.
            <li> Creates an invalid region if the source region is invalid.
            </ul>
    
            \error
                Doesn't throw C++ exceptions.
            */
            CRegion(const CRegion& source);

            /*!
            \brief  Move constructor. Constructs the region with the contents of \c source using move semantics. \c source is left invalid.

            \param[in] source The source region.

            \post
            <ul>
            <li> The new region now contains the data from \c source or is invalid if \c source was invalid.
            <li> \c source is invalid.
            </ul>

            \error
                Doesn't throw C++ exceptions.
            */
            CRegion(CRegion&& source) noexcept;

            /*!
            \brief Destroys a pylon region object.
    
            \error
                Doesn't throw C++ exceptions.
            */
            ~CRegion();

            /*!
            \brief  Copies the region properties and creates a reference to the buffer of the source region.
    
            \param[in] source The source region.
    
            \post
            <ul>
            <li> If the region is the last reference to the region data, any currently held region buffer is released.
            <li> Another reference to the source region buffer is created.
            <li> Creates an invalid region if the source region is invalid.
            </ul>
    
            \error
                Doesn't throw C++ exceptions.
            */
            CRegion& operator=(const CRegion& source);

            /*!
            \brief  Replaces the contents with those of \c source using move assignment semantics.

            \param[in] source The source region.

            \post
            <ul>
            <li> This region now contains the data from \c source or is invalid if \c source was invalid.
            <li> \c source is invalid.
            </ul>

            \error
                Doesn't throw C++ exceptions.
            */
            CRegion& operator=(CRegion&& source) noexcept;

            /*!
            \brief Copies the region data from a different region.
    
            This method is used for making a full copy of a region.
            Calls the Reset() method to set the same region properties as the source region and
            copies the region data.
    
            \param[in]   region The source region.
    
            \pre
                The preconditions of the Reset() method must be met.

            \post
            <ul>
            <li> The region contains a copy of the source region's region data.
            <li> Creates an invalid region if the source region is invalid.
            </ul>
    
            \error
                Throws an exception if no buffer with the required size could be allocated.
                Throws an exception if the preconditions of the Reset() method aren't met.
            */
            void CopyRegion(const CRegion& region);

            /*!
            \brief Copies the region data from a buffer provided.
    
            This method is used for making a full copy of a region.
            Calls the Reset() method to set the same region properties as the source region and
            copies the region data.
    
            \param[in]   pBuffer  The pointer to the buffer of the source region.
            \param[in]   dataSize The size of the region in bytes.
                                  For run-length encoded formats, the size in bytes defines the number of entries,
                                  e.g., 24 bytes result in 2 RLE32 entries for RegionType_RLE32.
            \param[in]   regionType The type of the new region.
            \param[in]   referenceWidth  The width of the source of the region if available, 0 otherwise.
            \param[in]   referenceHeight The height of the source of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftX The smallest horizontal pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftY The smallest vertical pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxWidth The width of the bounding box of the region if available, 0 otherwise.
            \param[in]   boundingBoxHeight The height of the bounding box of the region if available, 0 otherwise.
    
            \pre
            <ul>
            <li> The region type must be valid.
            <li> \c pBuffer must not be NULL.
            <li> The preconditions of the Reset() method must be met.
            <li> Either all bounding box values are 0, or \c boundingBoxWidth and \c boundingBoxHeight are both greater than 0.
            </ul>
    
            \post A copy of the source region buffer's region is made.
    
            \error
                Throws an exception if no buffer with the required size could be allocated.
                Throws an exception if the preconditions of the Reset() method aren't met.
            */
            void CopyRegion(const void* pBuffer,
                            size_t dataSize,
                            ERegionType regionType,
                            uint32_t referenceWidth = 0,
                            uint32_t referenceHeight = 0,
                            int32_t boundingBoxTopLeftX = 0,
                            int32_t boundingBoxTopLeftY = 0,
                            uint32_t boundingBoxWidth = 0,
                            uint32_t boundingBoxHeight = 0);

            /*!
            \brief Attaches a user buffer.
    
            \param[in]   pBuffer The pointer to the buffer of the source region. CRegion will never free any user buffers.
            \param[in]   bufferSize The size of the attached buffer.
            \param[in]   dataSize The size of the region in bytes.
                                  For run-length encoded formats, the size in bytes defines the number of entries,
                                  e.g., 24 bytes result in 2 RLE32 entries for RegionType_RLE32.
            \param[in]   regionType The type of the new region.
            \param[in]   referenceWidth  The width of the source of the region if available, 0 otherwise.
            \param[in]   referenceHeight The height of the source of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftX The smallest horizontal pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftY The smallest vertical pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxWidth The width of the bounding box of the region if available, 0 otherwise.
            \param[in]   boundingBoxHeight The height of the bounding box of the region if available, 0 otherwise.
            \param[in]   pEventHandler      A pointer to an optional CRegionUserBufferEventHandler-derived object
                                            called when the user-supplied buffer isn't used anymore.
                                            You can use this to free the user-supplied buffer.
                                            In case the function throws an exception, the handler will not be called.
    
            When attaching a user buffer and passing a pEventHandler, the user is responsible for ensuring the object is valid
            until CRegionUserBufferEventHandler::OnRegionUserBufferDetached() has been called.
            The user is also responsible for freeing the handler object after CRegionUserBufferEventHandler::OnRegionUserBufferDetached()
            has been called. After the function has returned, CRegion won't access the object anymore.
            See \c CRegionUserBufferEventHandler::OnRegionUserBufferDetached() for a sample.
                                       
            \pre
            <ul>
            <li> The region type must be valid.
            <li> \c pBuffer must not be NULL.
            <li> The buffer passed in \c pBuffer must not be currently attached.
            <li> Either all bounding box values are 0, or \c boundingBoxWidth and \c boundingBoxHeight are both greater than 0.
            </ul>
    
            \post
            <ul>
            <li> The region properties are taken from the parameters passed.
            <li> The user buffer is used by the region class.
            <li> The user buffer must not be freed while being attached.
            </ul>
    
            \error
                Throws an exception if the preconditions aren't met. In this case, the optional handler passed in \ pEventHandler won't be called.
            */
            void AttachUserBuffer(  void* pBuffer,
                                    size_t bufferSize,
                                    size_t dataSize,
                                    ERegionType regionType,
                                    uint32_t referenceWidth = 0,
                                    uint32_t referenceHeight = 0,
                                    int32_t boundingBoxTopLeftX = 0,
                                    int32_t boundingBoxTopLeftY = 0,
                                    uint32_t boundingBoxWidth = 0,
                                    uint32_t boundingBoxHeight = 0,
                                    CRegionUserBufferEventHandler* pEventHandler = NULL);

            /*!
            \copydoc CRegion::AttachUserBuffer()
            This overload can be used for read-only buffers.
             */
            void AttachUserBuffer(  const void* pBuffer,
                                    size_t bufferSize,
                                    size_t dataSize,
                                    ERegionType regionType,
                                    uint32_t referenceWidth = 0,
                                    uint32_t referenceHeight = 0,
                                    int32_t boundingBoxTopLeftX = 0,
                                    int32_t boundingBoxTopLeftY = 0,
                                    uint32_t boundingBoxWidth = 0,
                                    uint32_t boundingBoxHeight = 0,
                                    CRegionUserBufferEventHandler* pEventHandler = NULL);

            /*!
            \brief Can be used to check whether a region is valid.

            \return Returns false if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            bool IsValid() const;

            /*!
            \brief Can be used to check whether a region data buffer is read-only.

            \return Returns true if the region data buffer is read-only or the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            bool IsReadOnly() const;

            /*!
            \brief Get the current region type.

            \return Returns the Region type or RegionType_Undefined if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            ERegionType GetRegionType() const;

            /*!
            \brief Indicates whether a user buffer is attached.

            \return Returns true if a user buffer is attached. Returns false if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            bool IsUserBufferAttached() const;

            /*!
            \brief Returns the size of the buffer used.

            This method is useful when working with so-called user buffers.

            \return Returns the size of the buffer used in bytes or 0 if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            size_t GetAllocatedBufferSize() const;

            /*!
            \brief Get the size of the region in bytes.

            \return Returns the size of the region in bytes or 0 if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            size_t GetDataSize() const;

            /*!
            \brief Indicates whether the referenced buffer is only referenced by this region.

            \return Returns true if the referenced buffer is only referenced by this region. Returns false if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            bool IsUnique() const;

            /*!
            \brief Indicates whether reference size information is available.

            \return Returns true if reference width or height aren't equal to zero. Returns false if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            bool HasReferenceSize() const;

            /*!
            \brief Get the reference width in pixels.

            \return Returns the reference width or 0 if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            uint32_t GetReferenceWidth() const;

            /*!
            \brief Get the reference height in pixels.

            \return Returns the reference height or 0 if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            uint32_t GetReferenceHeight() const;

            /*!
            \brief Indicates whether bounding box information is available.

            \return Returns true if boundingBoxWidth and boundingBoxHeight aren't equal to zero. Returns false if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            bool HasBoundingBox() const;

            /*!
            \brief Use this method to get the smallest horizontal pixel position of the region.
            \error
              Doesn't throw C++ exceptions.
            \returns Returns the smallest horizontal pixel position of the region. Returns 0 if the region is invalid.
            */
            int32_t GetBoundingBoxTopLeftX() const;

            /*!
            \brief Use this method to get the smallest vertical pixel position of the region.
            \error
              Doesn't throw C++ exceptions.
            \returns Returns the smallest vertical pixel position of the region. Returns 0 if the region is invalid.
            */
            int32_t GetBoundingBoxTopLeftY() const;

            /*!
            \brief Use this method to get the width of the region's bounding box.
            \error
              Doesn't throw C++ exceptions.
            \returns Returns the width of the region's bounding box. Returns 0 if the region is invalid.
            */
            uint32_t GetBoundingBoxWidth() const;

            /*!
            \brief Use this method to get the height of the region's bounding box.
            \error
                Doesn't throw C++ exceptions.
            \returns Returns the height of the region's bounding box. Returns 0 if the region is invalid.
            */
            uint32_t GetBoundingBoxHeight() const;

            /*!
            \brief Get the pointer to the buffer.

            \return Returns the pointer to the buffer used or NULL if the region is invalid.

            \pre The region's buffer is not read-only. Use, e.g., GetBufferConst() in this case.
            \post This GetBuffer overload implements copy-on-write.
                  If IsUnique() returns false, a new buffer is allocated and
                  the region data is copied to the new buffer.
                  The old buffer is replaced by the new buffer.

            \error
                Throws an exception if the preconditions aren't met.
            */
            void* GetBuffer();

            /*!
            \brief Get the pointer to the buffer containing the region.

            The buffer is at least as large as the value returned by GetDataSize().

            \return Returns the pointer to the buffer used or NULL if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            const void* GetBuffer() const;

            /*!
            \brief Get the pointer to the buffer containing the region.

            The buffer is at least as large as the value returned by GetDataSize().

            \return Returns the pointer to the buffer used or NULL if the region is invalid.

            \error
                Doesn't throw C++ exceptions.
            */
            const void* GetBufferConst() const;

            /*!
            \brief Resets the region properties and allocates a new buffer if required.
    
            \param[in]   regionType The type of the new region.
            \param[in]   dataSize The size of the region in bytes.
                                  For run-length encoded formats, the size in bytes defines the number of entries,
                                  e.g., 24 bytes result in 2 RLE32 entries for RegionType_RLE32.
            \param[in]   referenceWidth  The width of the source of the region if available, 0 otherwise.
            \param[in]   referenceHeight The height of the source of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftX The smallest horizontal pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxTopLeftY The smallest vertical pixel position of the region if available, 0 otherwise.
            \param[in]   boundingBoxWidth The width of the bounding box of the region if available, 0 otherwise.
            \param[in]   boundingBoxHeight The height of the bounding box of the region if available, 0 otherwise.

            \pre
            <ul>
            <li> The region type must be valid.
            <li> If a user buffer is referenced, this buffer must not be referenced by another pylon region. See the IsUnique() and IsUserBufferAttached() methods.
            <li> If a user buffer is referenced, this buffer must be large enough to hold the destination region. See the GetAllocatedBufferSize() and IsUserBufferAttached() methods.
            <li> Either all bounding box values are 0, or \c boundingBoxWidth and \c boundingBoxHeight are both greater than 0.
            </ul>
    
            \post
            <ul>
            <li> If the previously referenced buffer is also referenced by another pylon region, a new buffer has been allocated.
            <li> If the previously referenced buffer isn't large enough to hold a region with the specified properties, a new buffer has been allocated.
            <li> If no buffer has been allocated before, a buffer has been allocated.
            </ul>
    
            \error
                Throws an exception if the preconditions aren't met.
                Throws an exception if no buffer with the required size could be allocated.
            */
            void Reset( ERegionType regionType,
                        size_t dataSize,
                        uint32_t referenceWidth = 0,
                        uint32_t referenceHeight = 0,
                        int32_t boundingBoxTopLeftX = 0,
                        int32_t boundingBoxTopLeftY = 0,
                        uint32_t boundingBoxWidth = 0,
                        uint32_t boundingBoxHeight = 0);

            /*!
            \brief Resizes the region.

            \param[in]   dataSize The size of the region in bytes.
                                  For run-length encoded formats, the size in bytes defines the number of entries,
                                  e.g., 24 bytes result in 2 RLE32 entries for RegionType_RLE32.

            \pre
            <ul>
            <li> The region must be valid.
            <li> If a user buffer is referenced, this buffer must not be referenced by another pylon region. See the IsUnique() and IsUserBufferAttached() methods.
            <li> If a user buffer is referenced, this buffer must be large enough to hold the new data size. See the GetAllocatedBufferSize() and IsUserBufferAttached() methods.
            </ul>

            \post
            <ul>
            <li> If the previously referenced buffer is also referenced by another pylon region, a new buffer has been allocated.
            <li> A new buffer is allocated if necessary.
            <li> If a new buffer is allocated, the old data (old data size bytes) is copied to the new buffer.
            <li> The data size is changed.
            </ul>
            */
            void Resize(size_t dataSize);

            /*!
            \brief Releases the region buffer and resets to an invalid region.

            \post
                <ul>
                <li> RegionType = RegionType_Undefined.
                <li> DataSize=0.
                <li> ReferenceWidth = 0.
                <li> ReferenceHeight = 0.
                <li> boundingBoxTopLeftX = 0.
                <li> boundingBoxTopLeftY = 0.
                <li> boundingBoxWidth = 0.
                <li> boundingBoxHeight = 0.
                <li> No buffer is allocated.
                </ul>

            \error
                Doesn't throw C++ exceptions.
            */
            void Release();

        private:
            friend class CVariant;

            // Internal use only.
            class Impl;

            CRegion(Impl* pImpl);

            Impl* m_pImpl;
        };
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */
