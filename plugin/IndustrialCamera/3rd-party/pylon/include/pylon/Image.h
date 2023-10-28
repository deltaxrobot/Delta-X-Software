//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains an interface for an image.
*/

#ifndef INCLUDED_IMAGE_H_9730799
#define INCLUDED_IMAGE_H_9730799

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/PixelType.h>

namespace Pylon
{
     /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    /// Defines the vertical orientation of an image in memory.
    enum EImageOrientation
    {
        ImageOrientation_TopDown, //!< The first row of the image is located at the start of the image buffer. This is the default for images taken by a camera.
        ImageOrientation_BottomUp //!< The last row of the image is located at the start of the image buffer.
    };

    /*!
    \interface  IImage
    \brief  Usable to access image properties and image buffer.
    */
    interface IImage
    {
    public:
        /// Ensure proper destruction by using a virtual destructor.
        // Do not add implemenation here in class as older compilers doesn't accept in-class definitions (see definition below)
        virtual ~IImage() = 0;

        //
        /*!
        \brief Can be used to check whether an image is valid.

        \return Returns false if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsValid() const = 0;


        /*!
        \brief Get the current pixel type.

        \return Returns the pixel type or PixelType_Undefined if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual EPixelType GetPixelType() const = 0;


        /*!
        \brief Get the current number of columns in pixels.

        \return Returns the current number of columns in pixels or 0 if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual uint32_t GetWidth() const = 0;


        /*!
        \brief Get the current number of rows.

        \return Returns the current number of rows or 0 if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual uint32_t GetHeight() const = 0;


        /*!
        \brief Get the number of extra data bytes at the end of each row.

        \return Returns the number of extra data bytes at the end of each row or 0 if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual size_t GetPaddingX() const = 0;


        /*!
        \brief Get the vertical orientation of the image in memory.

        \return Returns the orientation of the image or ImageOrientation_TopDown if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual EImageOrientation GetOrientation() const = 0;


        /*!
        \brief Get the pointer to the buffer.

        \return Returns the pointer to the used buffer or NULL if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual void* GetBuffer() = 0;


        /*!
        \brief Get the pointer to the buffer containing the image.

        The buffer is at least as large as the value returned by GetImageSize().

        \return Returns the pointer to the used buffer or NULL if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual const void* GetBuffer() const = 0;


        /*!
        \brief Get the size of the image in bytes.

        \return Returns the size of the image in bytes or 0 if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual size_t GetImageSize() const = 0;


        /*!
        \brief Indicates that the referenced buffer is only referenced by this image.

        \return Returns true if the referenced buffer is only referenced by this image. Returns false if the image is invalid.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsUnique() const = 0;


        /*!
        \brief Get the stride in bytes.

        The stride in bytes can not be computed for packed image format when the stride is not byte aligned. See also Pylon::IsPacked().
        The stride in bytes can not be computed if the image is invalid.

        \param[out] strideBytes  The stride in byte if it can be computed.
        \return Returns true if the stride can be computed.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool GetStride( size_t& strideBytes ) const = 0;
    };

    /**
     * @}
     */

    // Implementation required for Windows only.
    // Note: the C++ standard >= 11 prohibit pure virtual destructors with a function body
    // in the declaration. Consequently gcc 4.0 and newer reject an inline implementation
    // in the class.
    inline IImage::~IImage()
    {
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_IMAGE_H_9730799 */
