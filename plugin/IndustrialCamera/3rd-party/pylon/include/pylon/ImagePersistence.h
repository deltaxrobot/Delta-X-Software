//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains an image loading and saving support class.
*/
#ifndef INCLUDED_IMAGEPERSISTENCE_H_3336145
#define INCLUDED_IMAGEPERSISTENCE_H_3336145

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/ReusableImage.h>

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

#if defined(PYLON_WIN_BUILD)
    /// Lists the available file formats
    enum EImageFileFormat
    {
        ImageFileFormat_Bmp  = 0,       //!< Windows Bitmap, no compression.
        ImageFileFormat_Tiff = 1,       //!< Tagged Image File Format, no compression, supports mono images with more than 8 bit bit depth.
        ImageFileFormat_Jpeg = 2,       //!< Joint Photographic Experts Group, lossy data compression.
        ImageFileFormat_Png  = 3,       //!< Portable Network Graphics, lossless data compression.
        ImageFileFormat_Raw  = 4,       //!< Saves the raw image buffer data. Packed image formats are unpacked. See GetPixelTypesForUnpacking() for more information.
                                        //!< In the format used for saving, the data cannot be loaded using CImagePersistence::Load().
        ImageFileFormat_Dng  = 5        //!< Saves Bayer pattern images in DNG/TIFF format. Packed image formats are unpacked. See GetPixelTypesForUnpacking() for more information.
                                        //!< In the format used for saving, the data cannot be loaded using CImagePersistence::Load().
    };
#elif defined(PYLON_UNIX_BUILD)
    /// Lists the available file formats
    enum EImageFileFormat
    {
        ImageFileFormat_Tiff = 1,       //!< Tagged Image File Format, no compression, supports mono images with more than 8 bit bit depth.
        ImageFileFormat_Png  = 3,       //!< Portable Network Graphics, lossless data compression.
        ImageFileFormat_Raw  = 4,       //!< Saves the raw image buffer data. Packed image formats are unpacked. See GetPixelTypesForUnpacking() for more information.
                                        //!< This format cannot be loaded unsing CImagePersistence::Load().
        ImageFileFormat_Dng  = 5        //!< Saves Bayer pattern images in DNG/TIFF format. Packed image formats are unpacked. See GetPixelTypesForUnpacking() for more information.
                                        //!< In the format used for saving, the data cannot be loaded using CImagePersistence::Load().
    };
#else
#   error unsupported platform
#endif


    /// Used to pass options to CImagePersistence methods.
    class CImagePersistenceOptions
    {
    public:
        CImagePersistenceOptions()
            : m_quality( 90 )
        {
        }

        ~CImagePersistenceOptions()
        {
        }

        /// Set the image quality options. Valid quality values range from 0 to 100.
        void SetQuality( int quality )
        {
            m_quality = quality;
        }

        /// Returns the set quality level.
        int GetQuality()
        {
            return m_quality;
        }

    private:
        int m_quality; ///< Can be used to control the quality when saving JPEG images.
    };


    /*!
    \class  CImagePersistence
    \brief  Contains static functions supporting loading and saving of images.
    */
    class PYLONUTILITY_API CImagePersistence
    {
    public:
        /*!
        \brief Saves the image to disk. Converts the image to a format that can be saved if required.

        If required, the image is automatically converted to a new image and then saved. See
        CanSaveWithoutConversion() for more information.
        An image with a bit depth higher than 8 bit is stored with 16 bit bit depth
        if supported by the image file format. In this case the pixel data is MSB aligned.

        If more control over the conversion is required then the CImageFormatConverter class
        can be used to convert the input image before saving it.

        \param[in]   imageFileFormat The file format to save the image in.
        \param[in]   filename        Name and path of the image.
        \param[in]   pBuffer    The pointer to the buffer of the image.
        \param[in]   bufferSize The size of the buffer in byte.
        \param[in]   pixelType  The pixel type of the image to save.
        \param[in]   width      The number of pixels in a row of the image to save.
        \param[in]   height     The number of rows of the image to save.
        \param[in]   paddingX   The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image in the image buffer.
        \param[in]   pOptions   Additional options.

        \pre
        <ul>
        <li> The pixel type of the image to save must be a supported input format of the Pylon::CImageFormatConverter.
        <li> The \c width value must be >= 0 and < _I32_MAX.
        <li> The \c height value must be >= 0 and < _I32_MAX.
        </ul>

        \error
            Throws an exception if saving the image fails.
        */
        static void Save( EImageFileFormat imageFileFormat, const String_t& filename, const void* pBuffer, size_t bufferSize, EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, EImageOrientation orientation, CImagePersistenceOptions* pOptions = NULL );


        /*!
        \brief Saves the image to disk. Converts the image to a format that can be if required.

        If required, the image is automatically converted to a new image and then saved. See
        CanSaveWithoutConversion() for more information.
        An image with a bit depth higher than 8 bit is stored with 16 bit bit depth
        if supported by the image file format. In this case the pixel data is MSB aligned.

        If more control over the conversion is required then the CImageFormatConverter class
        can be used to convert the input image before saving it.

        \param[in]   imageFileFormat The target file format for the image to save.
        \param[in]   filename        Name and path of the image.
        \param[in]   image           The image to save, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \param[in]   pOptions        Additional options.

        \pre
            The pixel type of the image to save must be a supported input format of the Pylon::CImageFormatConverter.

        \error
            Throws an exception if saving the image fails.
        */
        static void Save( EImageFileFormat imageFileFormat, const String_t& filename, const IImage& image, CImagePersistenceOptions* pOptions = NULL );


        /*!
        \brief Can be used to check whether the given image can be saved without prior conversion.

        See the CImagePersistence::CanSaveWithoutConversion( EImageFileFormat, const IImage&) method documentation for a list of supported pixel formats.

        \param[in]   imageFileFormat The target file format for the image to save.
        \param[in]   pixelType The pixel type of the image to save.
        \param[in]   width     The number of pixels in a row of the image to save.
        \param[in]   height    The number of rows of the image to save.
        \param[in]   paddingX  The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image in the image buffer.
        \return Returns true if the image can be saved without prior conversion.

        \error
            Does not throw C++ exceptions.
        */
        static bool CanSaveWithoutConversion( EImageFileFormat imageFileFormat, EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, EImageOrientation orientation );


        /*!
        \brief Can be used to check whether the image can be saved without prior conversion.

        Supported formats for TIFF:
        <ul>
        <li> PixelType_Mono8
        <li> PixelType_Mono16
        <li> PixelType_RGB8packed
        <li> PixelType_RGB16packed
        </ul>

        Supported formats for BMP, JPEG and PNG:
        <ul>
        <li> PixelType_Mono8
        <li> PixelType_BGR8packed
        <li> PixelType_BGRA8packed
        </ul>

        Supported formats for DNG:
        <ul>
        <li> PixelType_BayerGR*
        <li> PixelType_BayerRG*
        <li> PixelType_BayerGB*
        <li> PixelType_BayerBG*
        </ul>
        With *: 8, 10, 12, 16, 10p, 12p, 12packed

        \param[in]   imageFileFormat The target file format for the image to save.
        \param[in]   image           The image to save, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \return Returns true if the image can be saved without prior conversion.

        \error
            Does not throw C++ exceptions.
        */
        static bool CanSaveWithoutConversion( EImageFileFormat imageFileFormat, const IImage& image );


        /*!
        \brief Loads an image from disk.

        The orientation of loaded images is always ImageOrientation_TopDown.

        \param[in]   filename        Name and path of the image.
        \param[in]   image           The target image object, e.g. a CPylonImage or CPylonBitmapImage object.
                                     When passing a CPylonBitmapImage object the loaded format must be supported by the CPylonBitmapImage class.

        \error
            Throws an exception if the image cannot be loaded. The image buffer content is undefined when the loading of the image fails.
        */
        static void Load( const String_t& filename, IReusableImage& image );

        /*!
        \brief Loads an image from memory.

        The orientation of loaded images is always ImageOrientation_TopDown.
        Currently BMP, JPEG & PNG images are supported.

        \param[in]   pBuffer         The pointer to the buffer of the source image.
        \param[in]   bufferSizeBytes The size of the buffer of the source image.
        \param[in]   image           The target image object, e.g. a CPylonImage or CPylonBitmapImage object.
                                     When passing a CPylonBitmapImage object the loaded format must be supported by the CPylonBitmapImage class.

        \error
            Throws an exception if the image cannot be loaded. The image buffer content is undefined when the loading of the image fails.
        */
        static void LoadFromMemory( const void* pBuffer, size_t bufferSizeBytes, IReusableImage& image );

    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_IMAGEPERSISTENCE_H_3336145 */
