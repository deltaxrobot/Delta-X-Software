//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains an image class.
*/

#ifndef INCLUDED_PYLONIMAGE_H_6241114
#define INCLUDED_PYLONIMAGE_H_6241114

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/PylonImageBase.h>
#include <pylon/PylonImageUserBufferEventHandler.h>

namespace Pylon
{
    // Forward references.
    class CGrabResultPtr;

    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    /*!
    \class  CPylonImage
    \brief  Describes an image.

    <ul>
    <li> Automatically handles size and lifetime of the image buffer.
    <li> Allows to take over a buffer of grab result which is preventing its reuse as long as required.
    <li> Allows to connect user buffers or buffers provided by third party software packages.
    <li> Provides methods for loading and saving an image in different file formats.
    <li> Serves as the main target format for the image format converter \c CImageFormatConverter.
    <li> Eases working with planar images.
    <li> Eases extraction of AOIs, e.g. for thumbnail images of defects.
    </ul>

    \par Buffer Handling:
    The buffer that is automatically created by the CPylonImage class or a hosted grab result buffer are replaced by a larger buffer if required.
    The size of the allocated buffer is never decreased.
    Referenced user buffers are never automatically replaced by a larger buffer.
    Referenced grab result buffers are never reused. See the Reset() method for more details.
    The Release() method can be used to detach a user buffer, release a hosted grab result buffer or to free an allocated buffer.

    \threading
        The CPylonImage class is not thread-safe.
    */
    class PYLONUTILITY_API CPylonImage : public CPylonImageBase
    {
    public:
        typedef void (*DeleteNotifyFunction_t) (void*);

    public:

        /*!
        \brief Creates an invalid image.

        See Pylon::IImage on how the properties of an invalid image are returned.

        \error
            Does not throw C++ exceptions.
        */
        CPylonImage();


        /*!
        \brief  Copies the image properties and creates a reference to the buffer of the source image.

        \param[in] source The source image.

        \post
        <ul>
        <li> Another reference to the source image buffer is created.
        <li> Creates an invalid image if the source image is invalid.
        </ul>

        \error
            Does not throw C++ exceptions.
        */
        CPylonImage( const CPylonImage& source );


        /*!
        \brief Destroys a pylon image object.

        \error
            Does not throw C++ exceptions.
        */
        virtual ~CPylonImage();


        /*!
        \brief  Copies the image properties and creates a reference to the buffer of the source image.

        \param[in] source The source image.

        \post
        <ul>
        <li> Another reference to the source image buffer is created.
        <li> Creates an invalid image if the source image is invalid.
        </ul>

        \error
            Does not throw C++ exceptions.
        */
        virtual CPylonImage& operator= ( const CPylonImage& source );


        /*!
        \brief Creates an image and allocates a buffer for it.

        \param[in]   pixelType The pixel type of the new image.
        \param[in]   width     The number of pixels in a row in the new image.
        \param[in]   height    The number of rows in the new image.
        \param[in]   paddingX  The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The pixel type must be valid.
        <li> The \c width value must be >= 0 and < _I32_MAX.
        <li> The \c height value must be >= 0 and < _I32_MAX.
        </ul>

        \error
            Throws an exception when the parameters are invalid.
            Throws an exception when no buffer with the required size could be allocated.
        */
        static CPylonImage Create( EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX = 0, EImageOrientation orientation = ImageOrientation_TopDown );


        /*!
        \brief Copies the image data from a different image.

        This method is used for making a full copy of an image.
        Calls the Reset() method to set the same image properties as the source image and
        copies the image data.

        \param[in]   image The source image, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.

        \pre
            The preconditions of the Reset() method must be met.


        \post
        <ul>
        <li> The image contains a copy of the image data contained by the source image.
        <li> Creates an invalid image if the source image is invalid.
        </ul>

        \error
            Throws an exception when no buffer with the required size could be allocated.
            Throws an exception when the preconditions of the Reset() method are not met.
        */
        virtual void CopyImage( const IImage& image );


        /*!
        \brief Copies the image data from a different image and changes the padding while copying.

        This method is used for making a full copy of an image except for changing the padding.
        Calls the Reset() method to set the same image properties as the source image and
        copies the image data.
        This method is useful in combination with the GetAoi() method.

        \param[in]   image The source image, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \param[in]   newPaddingX The number of extra data bytes at the end of each row.

        \pre
        <ul>
        <li> The preconditions of the Reset() method must be met.
        <li> The rows of the source image must be byte aligned. This may not be the case for packed pixel types. See Pylon::IsPacked().
        <li> The rows of the newly created image must be byte aligned. This may not be the case for packed pixel types. See Pylon::IsPacked().
        </ul>

        \post
        <ul>
        <li> The image contains a copy of the image data contained by the source image.
        <li> The line padding is adjusted.
        <li> The byte aligned row padding area is set to zero.
        <li> Creates an invalid image if the source image is invalid.
        </ul>

        \error
            Throws an exception when no buffer with the required size could be allocated.
            Throws an exception when the preconditions of the Reset() method are not met.
        */
        virtual void CopyImage( const IImage& image, size_t newPaddingX );


        /*!
        \brief Copies the image data from a provided buffer.

        This method is used for making a full copy of an image.
        Calls the Reset() method to set the same image properties as the source image and
        copies the image data.

        \param[in]   pBuffer          The pointer to the buffer of the source image.
        \param[in]   bufferSizeBytes  The size of the buffer of the source image.
        \param[in]   pixelType The pixel type of the source image.
        \param[in]   width     The number of pixels in a row in the source image.
        \param[in]   height    The number of rows in the source image.
        \param[in]   paddingX  The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The pixel type must be valid.
        <li> The \c width value must be >= 0 and < _I32_MAX.
        <li> The \c height value must be >= 0 and < _I32_MAX.
        <li> The pointer to the source buffer must not be NULL.
        <li> The source buffer must be large enough to hold the image described by the parameters.
        <li> The preconditions of the Reset() method must be met.
        </ul>

        \post A copy of the image contained by the source image buffer is made.

        \error
            Throws an exception when no buffer with the required size could be allocated.
            Throws an exception when the preconditions of the Reset() method are not met.
        */
        virtual void CopyImage(
            void* pBuffer,
            size_t bufferSizeBytes,
            EPixelType pixelType,
            uint32_t width,
            uint32_t height,
            size_t paddingX,
            EImageOrientation orientation = ImageOrientation_TopDown );

        /*!
        \brief Attaches a grab result buffer using additional hints.

        This allows to display grabbed data in a user-defined way.

        \param[in]   grabResult The source buffer.
        \param[in]   pixelType The pixel type of the source image.
        \param[in]   width     The number of pixels in a row in the source image.
        \param[in]   height    The number of rows in the source image.
        \param[in]   paddingX  The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The \c grabResult must be valid.
        <li> The \c pixelType must be valid.
        <li> The \c width value must be >= 0 and < _I32_MAX.
        <li> The \c height value must be >= 0 and < _I32_MAX.
        </ul>

        \post
        <ul>
        <li> The image properties are taken from the \c width, \c height, \c pixelType, \c paddingX and \c orientation parameters.
        <li> The grab result buffer is used by the image class.
        <li> Another reference to the grab result buffer is created. This prevents the buffer's reuse for grabbing.
        </ul>

        \error
             Throws an exception if the preconditions are not met.
             Throws an exception if the buffer size of the grabresult is too small for an image with the given parameters.
        */
        virtual void AttachGrabResultBufferWithUserHints(
            const CGrabResultPtr& grabResult,
            EPixelType pixelType,
            uint32_t width,
            uint32_t height,
            size_t paddingX,
            EImageOrientation orientation = ImageOrientation_TopDown );

        /*!
        \brief Attaches a grab result buffer.

        \param[in]   grabResult The source image represented by a grab result.

        \post
        <ul>
        <li> The image properties are taken from the grab result.
        <li> The grab result buffer is used by the image class.
        <li> Another reference to the grab result buffer is created. This prevents the buffer's reuse for grabbing.
        <li> Creates an invalid image if the \c grabResult is invalid.
        <li> Creates an invalid image if the grab was not successful. See CGrabResultData::GrabSucceeded().
        </ul>

        \error
            Throws an exception when no buffer with the required size could be allocated.
            Throws an exception when the preconditions of the Reset() method are not met.
        */
        virtual void AttachGrabResultBuffer( const CGrabResultPtr& grabResult );


        /*!
        \brief Attaches a user buffer.

        \param[in]   pBuffer            The pointer to the buffer of the source image. CPylonImage will never free any user buffers.
        \param[in]   bufferSizeBytes    The size of the buffer of the source image.
        \param[in]   pixelType          The pixel type of the source image.
        \param[in]   width              The number of pixels in a row in the source image.
        \param[in]   height             The number of rows in the source image.
        \param[in]   paddingX           The number of extra data bytes at the end of each row.
        \param[in]   orientation        The vertical orientation of the image in the image buffer.
        \param[in]   pEventHandler      A pointer to an optional CPylonImageUserBufferEventHandler-derived object
                                        called when the user-supplied buffer is not used anymore.
                                        You can use this to free the user-supplied buffer.
                                        In case the function throws an exception, the handler will not be called.

        When attaching a user buffer and passing a pEventHandler, the user is responsible for ensuring the object is valid
        until CPylonImageUserBufferEventHandler::OnPylonImageUserBufferDetached() has been called.
        The user is also responsible to free the handler object after CPylonImageUserBufferEventHandler::OnPylonImageUserBufferDetached()
        has been called. After the function has returned, CPylonImage won't access the object anymore.
        See \c CPylonImageUserBufferEventHandler::OnPylonImageUserBufferDetached() for a sample.
                                   
        \pre
        <ul>
        <li> The pixel type must be valid.
        <li> The \c width value must be >= 0 and < _I32_MAX.
        <li> The \c height value must be >= 0 and < _I32_MAX.
        <li> The pointer to the source buffer must not be NULL.
        <li> The source buffer must be large enough to hold the image described by the parameters.
        <li> The buffer passed in \c pBuffer must not be currently attached.
        </ul>

        \post
        <ul>
        <li> The image properties are taken from the parameters passed.
        <li> The user buffer is used by the image class.
        <li> The user buffer must not be freed while being attached.
        </ul>

        \error
            Throws an exception if the preconditions are not met. In this case the an optional handler passed in \ pEventHandler will not be called.
        */
        virtual void AttachUserBuffer(
            void* pBuffer,
            size_t bufferSizeBytes,
            EPixelType pixelType,
            uint32_t width,
            uint32_t height,
            size_t paddingX,
            EImageOrientation orientation = ImageOrientation_TopDown,
            CPylonImageUserBufferEventHandler* pEventHandler = NULL);


        // Implements Pylon::IImage.
        virtual bool IsValid() const;

        // Implements Pylon::IImage.
        virtual EPixelType GetPixelType() const;

        // Implements Pylon::IImage.
        virtual uint32_t GetWidth() const;

        // Implements Pylon::IImage.
        virtual uint32_t GetHeight() const;

        // Implements Pylon::IImage.
        virtual size_t GetPaddingX() const;

        // Implements Pylon::IImage.
        virtual EImageOrientation GetOrientation() const;

        // Implements Pylon::IImage.
        virtual void* GetBuffer();

        // Implements Pylon::IImage.
        virtual const void* GetBuffer() const;

        // Implements Pylon::IImage.
        virtual size_t GetImageSize() const;

        // Implements Pylon::IImage.
        virtual bool IsUnique() const;

        // Implements Pylon::IImage.
        virtual bool GetStride( size_t& strideBytes ) const;

        // Implements Pylon::IReusableImage.
        virtual bool IsSupportedPixelType( EPixelType pixelType ) const;

        // Implements Pylon::IReusableImage, always returns true.
        virtual bool IsAdditionalPaddingSupported() const;


        //Implements Pylon::IReusableImage
        /*!
        \brief Resets the image properties and allocates a new buffer if required.

        \param[in]   pixelType The pixel type of the new image.
        \param[in]   width     The number of pixels in a row in the new image.
        \param[in]   height    The number of rows in the new image.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The \c width value must be >= 0 and < _I32_MAX.
        <li> The \c height value must be >= 0 and < _I32_MAX.
        <li> If a user buffer is referenced then this buffer must not be referenced by another pylon image. See the IsUnique() and IsUserBufferAttached() methods.
        <li> If a user buffer is referenced then this buffer must be large enough to hold the destination image. See the GetAllocatedBufferSize() and IsUserBufferAttached() methods.
        </ul>

        \post
        <ul>
        <li> If the previously referenced buffer is a grab result buffer, a new buffer has been allocated.
        <li> If the previously referenced buffer is also referenced by another pylon image, a new buffer has been allocated.
        <li> If the previously referenced buffer is not large enough to hold an image with the given properties, a new buffer has been allocated.
        <li> If no buffer has been allocated before, a buffer has been allocated.
        </ul>

        \error
            Throws an exception when the preconditions are not met.
            Throws an exception when no buffer with the required size could be allocated.
        */
        virtual void Reset( EPixelType pixelType, uint32_t width, uint32_t height, EImageOrientation orientation = ImageOrientation_TopDown );


        // Implements Pylon::IReusableImage, user defined padding is always supported.
        /*!
            \brief Extends the Reset( EPixelType, uint32_t, uint32_t, EImageOrientation) method by settable paddingX.
            \copydetails Reset( EPixelType, uint32_t, uint32_t, EImageOrientation)
            \param[in]   paddingX  The number of extra data bytes at the end of each row.
        */
        virtual void Reset( EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, EImageOrientation orientation = ImageOrientation_TopDown );

        // Implements Pylon::IReusableImage.
        virtual void Release();

        /// Returns true if the referenced buffer has been provided by the user.
        virtual bool IsUserBufferAttached() const;

        /// Returns true if the referenced buffer has been provided by a grab result.
        virtual bool IsGrabResultBufferAttached() const;

        /*!
        \brief Returns the size of the used buffer.

        This method is useful when working with so-called user buffers.

        \error
            Does not throw C++ exceptions.
        */
        virtual size_t GetAllocatedBufferSize() const;

        /*!
        \brief Changes the pixel type of the image.

        \param[in]   pixelType The new pixel type.

        \pre
        <ul>
        <li> Pylon::SamplesPerPixel( oldPixelType) == Pylon::SamplesPerPixel( newPixelType)
        <li> Pylon::BitPerPixel( oldPixelType) == Pylon::BitPerPixel( newPixelType)
        </ul>

        \error
            Throws an exception when the new pixel type properties do not match the existing ones.
        */
        virtual void ChangePixelType( EPixelType pixelType );


        /*!
        \brief Creates a new pylon image for a plane of the image. No image data is copied.

        Use CopyImage( const IImage& image) to create a full copy.

        \code
            copiedPlane.CopyImage( planarImage.GetPlane( 2));
        \endcode

        \param[in]   planeIndex The zero based index of the plane.
        \return A pylon image referencing a plane of the image.

        \pre
            The value of planeIndex < Pylon::PlaneCount( GetPixelType()).

        \post
        <ul>
        <li> A reference to the same buffer is created. No image data is copied.
        <li> The returned image has the Pylon::GetPlanePixelType( GetPixelType()) pixel type.
        <li> If the image is not planar only index 0 is allowed. A call passing index 0 returns a copy of the image. No image data is copied.
        </ul>

        \error
            Throws an exception when the plane index is out of range.
        */
        virtual CPylonImage GetPlane( size_t planeIndex ) const;


        /*!
        \brief Creates a new pylon image for an image area of interest (Image AOI) derived from the image. No image data is copied.

        Use CopyImage( const IImage& image, size_t newPaddingX) to create a full copy and to remove the additional padding.

        \code
            copiedAoi.CopyImage( image.GetAoi( 80, 90, 100, 100), 0);
        \endcode

        \param[in]   topLeftX The x-coordinate of the top left corner of the image AOI in pixels.
        \param[in]   topLeftY The y-coordinate of the top left corner of the image AOI in pixels.
        \param[in]   width The width of the image AOI in pixels.
        \param[in]   height The height of the image AOI in pixels.

        \return A pylon image referencing an image AOI of the image.

        \pre
        <ul>
        <li> The image must be valid.
        <li> The image AOI is located inside the image.
        <li> The image is not in a planar format, see Pylon::IsPlanar(). Use GetPlane() first in this case.
        <li> The rows of the image must be byte aligned. This may not be the case for packed pixel types. See Pylon::IsPacked().
        <li> The x-coordinate must be byte aligned. This may not be the case for packed pixel types. See Pylon::IsPacked().
        <li> The \c topLeftX parameter must be divisible by the return value of Pylon::GetPixelIncrementX() for the image's pixel type.
        <li> The \c topLeftY parameter must be divisible by the return value of Pylon::GetPixelIncrementY() for the image's pixel type.
        </ul>

        \post
        <ul>
        <li> A reference to the same buffer is created. The image data is not copied.
        <li> The returned image uses the paddingX property to skip over image content outside of the image AOI.
        </ul>

        \error
            Throws an exception when the preconditions are not met.
        */
        virtual CPylonImage GetAoi( uint32_t topLeftX, uint32_t topLeftY, uint32_t width, uint32_t height ) const;

    private:
        // Internal use only.
        class CPylonImageImpl;
        CPylonImageImpl* m_pImpl;
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PYLONIMAGE_H_6241114 */
