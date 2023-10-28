//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains a bitmap image class for displaying images.
*/

#ifndef INCLUDED_PYLONBITMAPIMAGE_H_7767407
#define INCLUDED_PYLONBITMAPIMAGE_H_7767407

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/PylonImageBase.h>

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    /*!
    \class  CPylonBitmapImage
    \brief  This class can be used to easily create Windows bitmaps for displaying images.

    <ul>
    <li> Automatically handles the bitmap creation and lifetime.
    <li> Provides methods for loading and saving an image in different file formats.
    <li> Serves as target format for the \c CImageFormatConverter image format converter.
    </ul>

    \par Buffer Handling:
    The bitmap buffer that is automatically created by the CPylonBitmapImage class.
    The Release() method can be used to release a bitmap.

    \threading
        The CPylonBitmapImage class is not thread-safe.
    */
    class PYLONUTILITY_API CPylonBitmapImage : public CPylonImageBase
    {
    public:

        /*!
        \brief Creates an invalid image.

        See Pylon::IImage on how the properties of an invalid image are returned.

        \error
            Does not throw C++ exceptions.
        */
        CPylonBitmapImage();


        /*!
        \brief Copies the image properties and creates a reference to the bitmap of the source image.

        \param[in]   source The source image.

        \post
        <ul>
        <li> Another reference to the source bitmap is created.
        <li> Creates an invalid image if the source image is invalid.
        </ul>

        \error
            Does not throw C++ exceptions.
        */
        CPylonBitmapImage( const CPylonBitmapImage& source );


        /*!
        \brief Destroys a pylon image object.

        \attention The bitmap handle must not be currently selected into a DC. Otherwise the bitmap is not freed.

        \error
            Does not throw C++ exceptions.
        */
        virtual ~CPylonBitmapImage();


        /*!
        \brief Copies the image properties and creates a reference to the bitmap of the source image.

        \param[in] source The source image.

        \post
        <ul>
        <li> Another reference to the source bitmap is created.
        <li> Creates an invalid image if the source image is invalid.
        </ul>

        \error
            Does not throw C++ exceptions.
        */
        virtual CPylonBitmapImage& operator= ( const CPylonBitmapImage& source );


        /*!
        \brief Creates an image and a Windows bitmap for it.

        \param[in]   pixelType The pixel type of the new image.
        \param[in]   width     The number of pixels in a row in the new image.
        \param[in]   height    The number of rows in the new image.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The pixel type must be supported, see IsSupportedPixelType().
        <li> The \c width value must be > 0 and < _I32_MAX.
        <li> The \c height value must be > 0 and < _I32_MAX.
        </ul>

        \error
            Throws an exception when the parameters are invalid.
            Throws an exception when the bitmap could not be created.
        */
        static CPylonBitmapImage Create( EPixelType pixelType, uint32_t width, uint32_t height, EImageOrientation orientation = ImageOrientation_BottomUp );


        /*!
        \brief Copies the image data from a different image.

        The input image is automatically converted if needed to PixelType_Mono8
        if Pylon::IsMonoImage( pixelTypeSource) is true,
        otherwise it is converted to PixelType_BGR8packed.
        The orientation of the image is changed to bottom up.

        If more control over the conversion is required, the CImageFormatConverter class
        can be used to convert other images with a CPylonBitmapImage object as target.

        \param[in]   image The source image, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.

        \pre
            The preconditions of the Reset() method must be met.


        \post
        <ul>
        <li> The source image is automatically converted.
        <li> Creates an invalid image if the source image is invalid.
        </ul>

        \error
            Throws an exception when the bitmap could not be created.
            Throws an exception when the preconditions of the Reset() method are not met.
        */
        virtual void CopyImage( const IImage& image );

        /*!
        \brief Sets an image from a user buffer.

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

        \post
            The source image is automatically converted. See CopyImage().

        \error
            Throws an exception when when the bitmap could not be created.
            Throws an exception when the preconditions of the Reset() method are not met.
        */
        virtual void CopyImage(
            const void* pBuffer,
            size_t bufferSizeBytes,
            EPixelType pixelType,
            uint32_t width,
            uint32_t height,
            size_t paddingX,
            EImageOrientation orientation );


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
        \brief Resets the image properties and creates a new Windows bitmap if required.

        \param[in]   pixelType The pixel type of the new image.
        \param[in]   width     The number of pixels in a row in the new image.
        \param[in]   height    The number of rows in the new image.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The \c width value must be > 0 and < _I32_MAX.
        <li> The \c height value must be > 0 and < _I32_MAX.
        </ul>

        \post
        <ul>
        <li> If the previously referenced bitmap is also referenced by another pylon bitmap image, a new Windows bitmap is created.
        <li> If the previously referenced bitmap is able to hold an image with the given properties, a new Windows bitmap is created.
        <li> If no bitmap has been created before, a new Windows bitmap is created.
        </ul>

        \error
            Throws an exception when the preconditions are not met.
            Throws an exception when no buffer with the required size could be allocated.
        */
        virtual void Reset( EPixelType pixelType, uint32_t width, uint32_t height, EImageOrientation orientation = ImageOrientation_BottomUp );


        // Implements Pylon::IReusableImage.
        // attention: The bitmap handle must not be currently selected into a DC. Otherwise, the bitmap is not freed.
        virtual void Release();


        /*!
        \brief Get the handle of the windows bitmap.

        \attention The handle must not be freed using DeleteObject().
                    The handle is invalid after calling Release().
                    The handle may be invalid after calling Reset().

        \return Returns the handle of the windows bitmap or NULL if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual operator HBITMAP() const;


        /*!
        \brief Detach the windows bitmap.

        \return Returns the handle of the windows bitmap or NULL if the image is invalid.

        \pre
            IsUnique() must return true. No other image must reference the bitmap.

        \post
        <ul>
        <li> The image is invalid.
        <li> The ownership of the bitmap goes to the caller who is responsible for deleting it.
        </ul>

        \error
            Does not throw C++ exceptions.
        */
        virtual HBITMAP Detach();

    private:
        /// Not supported.
        virtual void Reset( EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, EImageOrientation orientation );

        // Internal use only.
        class CPylonBitmapImageImpl;
        CPylonBitmapImageImpl* m_pImpl;
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PYLONBITMAPIMAGE_H_7767407 */
