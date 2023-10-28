//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains an interface for a reusable image.
*/

#ifndef INCLUDED_REUSABLEIMAGE_H_1558802
#define INCLUDED_REUSABLEIMAGE_H_1558802

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/Image.h>

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    /*!
    \interface  IReusableImage
    \brief  Extends the IImage interface to be able to reuse the image's resources to represent a different image.
    */
    interface IReusableImage : public IImage
    {
    public:
        /// Ensure proper destruction by using a virtual destructor.
        // implementation must be out of class or older compilers will throw an error (see below)
        virtual ~IReusableImage() = 0;


        /*!
        \brief Can be used to check whether the pixel type is supported.

        \return Returns true if the pixel type is supported.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsSupportedPixelType( EPixelType pixelType ) const = 0;


        /*!
        \brief Can be used to check whether the value of PaddingX can be defined by the user.

        \return Returns true if the value of PaddingX can be defined by the user.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsAdditionalPaddingSupported() const = 0;


        /*!
        \brief Resets the image properties and provides a buffer to hold the image.

        \param[in]   pixelType   The pixel type of the new image.
        \param[in]   width       The number of pixels in a row in the new image.
        \param[in]   height      The number of rows in the new image.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The IsSupportedPixelType() method returns true.
        <li> The \c width value must be >= 0 and < _I32_MAX.
        <li> The \c height value must be >= 0 and < _I32_MAX.
        </ul>

        \post
        <ul>
        <li> The properties of the image are changed.
        <li> A buffer large enough to hold the image is provided.
        </ul>

        \error
            Throws an exception when the preconditions are not met.
            Throws an exception when no buffer with the required size can be provided, e.g. by allocation.
            The original representation is preserved on error.
        */
        virtual void Reset( EPixelType pixelType, uint32_t width, uint32_t height, EImageOrientation orientation = ImageOrientation_TopDown ) = 0;


        /*!
        \brief Resets the image properties including user defined PaddingX and provides a buffer to hold the image.

        Extends the Reset(EPixelType, uint32_t, uint32_t) method with user provided padding.

        \param[in]   pixelType The pixel type of the new image.
        \param[in]   width     The number of pixels in a row in the new image.
        \param[in]   height    The number of rows in the new image.
        \param[in]   paddingX  The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The preconditions of the Reset() method without paddingX parameter apply.
        <li> The IsAdditionalPaddingSupported() method returns true.
        </ul>
        */
        virtual void Reset( EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, EImageOrientation orientation = ImageOrientation_TopDown ) = 0;


        /*!
        \brief Releases the image buffer and resets to an invalid image.

        \post
            <ul>
            <li> PixelType = PixelType_Undefined.
            <li> Width = 0.
            <li> Height = 0.
            <li> PaddingX = 0.
            <li> No buffer is allocated.
            </ul>

        \error
            Does not throw C++ exceptions.
        */
        virtual void Release() = 0;
    };

    /**
     * @}
     */

     // implementation for d'tor must be out of class
    inline IReusableImage::~IReusableImage()
    {
    }

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_REUSABLEIMAGE_H_1558802 */
