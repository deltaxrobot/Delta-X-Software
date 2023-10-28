//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains the pylon image base class.
*/

#ifndef INCLUDED_PYLONIMAGEBASE_H_6835095
#define INCLUDED_PYLONIMAGEBASE_H_6835095

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/ReusableImage.h>
#include <pylon/ImagePersistence.h>
#include <pylon/PixelData.h>

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    /*!
    \class  CPylonImageBase
    \brief  Provides basic functionality for pylon image classes.
    */
    class PYLONUTILITY_API CPylonImageBase : public IReusableImage
    {
    public:

        /*!
        \brief Saves the image to disk. Converts the image to a format that can be saved if required.

        This is a convenience method that calls CImagePersistence::Save().

        If required, the image is automatically converted into a new image and saved afterwards. See
        CImagePersistence::CanSaveWithoutConversion() for more information.
        An image with a bit depth higher than 8 bit is stored with 16 bit bit depth,
        if supported by the image file format. In this case the pixel data is MSB aligned.

        If more control over the conversion is required, the CImageFormatConverter class
        can be used to convert the input image before saving it.

        \param[in]   imageFileFormat File format to save the image in.
        \param[in]   filename        Name and path of the image.
        \param[in]   pOptions        Additional options.

        \pre
            The pixel type of the image to be saved must be a supported input format of the Pylon::CImageFormatConverter.

        \error
            Throws an exception if the saving of the image fails.
        */
        virtual void Save( EImageFileFormat imageFileFormat, const String_t& filename, CImagePersistenceOptions* pOptions = NULL ) const;


        /*!
        \brief Loads an image from a disk.

        This is a convenience method that calls CImagePersistence::Load()

        \param[in]   filename Name and path of the image.

        \pre
            The image object must be able to hold the image format of the loaded image.

        \error
            Throws an exception if the image cannot be loaded. The image buffer content is undefined when the loading of the image fails.
        */
        virtual void Load( const String_t& filename );


        /*!
        \brief Can be used to check whether the image can be saved without prior conversion.

         This is a convenience method that calls CImagePersistence::CanSaveWithoutConversion().

        \param[in]   imageFileFormat Target file format for the image to be saved.
        \return Returns true, if the image can be saved without prior conversion.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool CanSaveWithoutConversion( EImageFileFormat imageFileFormat ) const;

        /*!
        \brief Retrieves the data of a pixel.

        \note This method is relativly slow. Do not use it for image processing tasks.

        \param[in]   posX Horizontal position of the pixel. The first column has position 0.
        \param[in]   posY Vertical position of the pixel. The first row has position 0.
        \return Returns the data of a pixel for supported pixel types. For unsupported pixel types pixel data of the SPixelData::PixelDataType_Unknown type is returned.

        \pre
        <ul>
        <li> The image must be valid.
        <li> The pixel position defined by \c posX and \c posY must be located inside the image area.
        </ul>

        Supported pixel types:
        <ul>
        <li> PixelType_Mono1packed
        <li> PixelType_Mono2packed
        <li> PixelType_Mono4packed
        <li> PixelType_Mono8
        <li> PixelType_Mono8signed
        <li> PixelType_Mono10
        <li> PixelType_Mono10packed
        <li> PixelType_Mono10p
        <li> PixelType_Mono12
        <li> PixelType_Mono12packed
        <li> PixelType_Mono12p
        <li> PixelType_Mono16
        </ul>
        <ul>
        <li> PixelType_BayerGR8
        <li> PixelType_BayerRG8
        <li> PixelType_BayerGB8
        <li> PixelType_BayerBG8
        <li> PixelType_BayerGR10
        <li> PixelType_BayerRG10
        <li> PixelType_BayerGB10
        <li> PixelType_BayerBG10
        <li> PixelType_BayerGR12
        <li> PixelType_BayerRG12
        <li> PixelType_BayerGB12
        <li> PixelType_BayerBG12
        <li> PixelType_BayerGR12Packed
        <li> PixelType_BayerRG12Packed
        <li> PixelType_BayerGB12Packed
        <li> PixelType_BayerBG12Packed
        <li> PixelType_BayerGR10p
        <li> PixelType_BayerRG10p
        <li> PixelType_BayerGB10p
        <li> PixelType_BayerBG10p
        <li> PixelType_BayerGR12p
        <li> PixelType_BayerRG12p
        <li> PixelType_BayerGB12p
        <li> PixelType_BayerBG12p
        <li> PixelType_BayerGR16
        <li> PixelType_BayerRG16
        <li> PixelType_BayerGB16
        <li> PixelType_BayerBG16
        </ul>
        <ul>
        <li> PixelType_RGB8packed
        <li> PixelType_BGR8packed
        <li> PixelType_RGBA8packed
        <li> PixelType_BGRA8packed
        <li> PixelType_RGB10packed
        <li> PixelType_BGR10packed
        <li> PixelType_RGB12packed
        <li> PixelType_BGR12packed
        <li> PixelType_RGB12V1packed
        <li> PixelType_RGB16packed
        <li> PixelType_RGB8planar
        <li> PixelType_RGB10planar
        <li> PixelType_RGB12planar
        <li> PixelType_RGB16planar
        </ul>
        <ul>
        <li> PixelType_YUV422packed
        <li> PixelType_YUV422_YUYV_Packed
        </ul>

        \error
            Throws an exception, if the preconditions are not met.
        */
        virtual SPixelData GetPixelData( uint32_t posX, uint32_t posY ) const;

    };

 /**
  * @}
  */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PYLONIMAGEBASE_H_6835095 */
