//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains an image format converter class.
*/

#ifndef INCLUDED_IMAGEFORMATCONVERTER_H_1564142
#define INCLUDED_IMAGEFORMATCONVERTER_H_1564142

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4275 ) // Class must have a dll interface to be used by clients of the class.
#endif

#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/_ImageFormatConverterParams.h>
#include <pylon/ReusableImage.h>

namespace Pylon
{
    using namespace Basler_ImageFormatConverterParams;


    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    /*!
    \class  CImageFormatConverter
    \brief  Creates new images by converting a source image to another format.

    Supported input image formats defined by the pixel type:

    <ul>
    <li> PixelType_Mono1packed
    <li> PixelType_Mono2packed
    <li> PixelType_Mono4packed
    <li> PixelType_Mono8
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
    <li> PixelType_RGB16planar
    </ul>
    <ul>
    <li> PixelType_YUV422packed
    <li> PixelType_YUV422_YUYV_Packed
    <li> PixelType_YCbCr422_8_YY_CbCr_Semiplanar
    <li> PixelType_YCbCr420_8_YY_CbCr_Semiplanar
    </ul>

    Supported output image formats defined by the pixel type:

    <ul>
    <li> PixelType_BGRA8packed - This pixel type can be used in Windows bitmaps. See Pylon::SBGRA8Pixel.
    <li> PixelType_BGR8packed - This pixel type can be used in Windows bitmaps. See Pylon::SBGR8Pixel.
    <li> PixelType_RGB8packed - See Pylon::SRGB8Pixel.
    <li> PixelType_RGB16packed - See Pylon::SRGB16Pixel.
    <li> PixelType_RGB8planar
    <li> PixelType_RGB16planar
    <li> PixelType_Mono8
    <li> PixelType_Mono16
    <li> PixelType_YUV444planar
    <li> PixelType_YUV422planar
    <li> PixelType_YUV420planar
    </ul>


    All input image formats can be converted to all output image formats.

    RGB, BGR and Bayer image formats are converted to monochrome formats by using the following formula:

    \code
            mono = (0.25 * red) + (0.625 * green) + (0.125 * blue);
    \endcode

    YUV formats are converted to 16 bit bit depth in an intermediate conversion step. This is why the output
    is always aligned at the most significant bit when converting to 16 bit color output formats like PixelType_RGB16packed.

    \par Limitations:
    The last column of a YUV input image with odd width cannot be converted.
    The last column and the last row of a Bayer input image cannot be converted.

    The default treatment of rows and columns that cannot be converted due to their location on edges,
    can be controlled using the CImageFormatConverter::InconvertibleEdgeHandling parameter.
    See also the Convert() method description.

    \threading
        The CImageFormatConverter class is not thread-safe.
    */
    class PYLONUTILITY_API CImageFormatConverter : public CImageFormatConverterParams_Params
    {
    public:

        /*!
        \brief Creates an image format converter.

        \error
            Does not throw C++ exceptions.
        */
        CImageFormatConverter();


        /*!
        \brief Destroys the image format converter.

        \error
            Does not throw C++ exceptions.
        */
        virtual ~CImageFormatConverter();


        /*!
        \brief Optionally initializes the image format converter before conversion.

        \param[in]   sourcePixelType The pixel type of the source image.

        <ul>
        <li> Depending on parameter settings and the input format, data structures required for conversion are created, e.g. lookup tables.
        <li> Initialization is done automatically when calling Convert() if needed. This may add a delay when converting the first image.
        </ul>

        \pre
            <ul>
            <li> The converter parameters are set up.
            <li> The \c pixelTypeSource must be supported by the converter.
            </ul>

        Lookup tables are created when using monochrome images as input and when
        the gamma conversion method is selected
        or when the shift conversion method is selected and the value of AdditionalLeftShift is not zero.
        The converter can be reinitialized with other settings if required.

        \error
            Throws an exception if the passed pixel type does not represent a valid input format.
            The converter object is still valid after error and can be initialized again.
        */
        virtual void Initialize( EPixelType sourcePixelType );


        /*!
        \brief  Returns information about the converter being initialized.

        \param[in]   sourcePixelType The pixel type of the source image.

        The result depends on the converter settings.

        \return True if initialized.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsInitialized( EPixelType sourcePixelType ) const;


        /*!
        \brief  Destroys data structures required for conversion.

        This function can be called to free resources held by the format converter.

        \error
            Does not throw C++ exceptions.
        */
        virtual void Uninitialize();


        /*!
        \brief Checks to see if a conversion is required or if the source image already has the desired format.

        \param[in]  sourceImage The source image, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \return  Returns true if the source image already has the desired format.

        A conversion may even be required image format does not change e.g. if the gamma conversion method is selected and the format describes a monochrome image.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool ImageHasDestinationFormat( const IImage& sourceImage ) const;


        /*!
        \brief Checks to see if a conversion is required or if the source image already has the desired format.

        \param[in]   sourcePixelType The pixel type of the source image.
        \param[in]   sourcePaddingX  The number of extra data bytes at the end of each row. The default value is usually 0.
        \param[in]   sourceOrientation The vertical orientation of the image in the image buffer. The default value is usually ImageOrientation_TopDown.

        \return  Returns true if the source image already has the desired format. This is done according to the current converter settings.

        A conversion may even be required image format does not change e.g. if the gamma conversion method is selected and the format describes a monochrome image.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool ImageHasDestinationFormat( EPixelType sourcePixelType, size_t sourcePaddingX, EImageOrientation sourceOrientation ) const;


        /*!
        \brief Computes the size of the destination image buffer in byte.

        \param[in]  sourceImage The source image, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \return  The size of the destination image when converting the given source image using current converter settings.

        \error
            Throws an exception if the destination image size for the passed input cannot be computed. The converter object is still valid after error.
        */
        virtual size_t GetBufferSizeForConversion( const IImage& sourceImage ) const;


        /*!
        \brief Computes the size of the destination image buffer in byte.

        \param[in]  sourceWidth     The number of pixels in a row in the source image.
        \param[in]  sourceHeight    The number of rows in the source image.
        \param[in]  sourcePixelType The pixel type of the source image.
        \return  The size of the destination image when converting the source image using current converter settings.

        \pre
            <ul>
            <li> The \c sourceWidth value must be >= 0 and < _I32_MAX.
            <li> The \c sourceHeight value must be >= 0 and < _I32_MAX.
            </ul>

        \error
            Throws an exception if the destination image size for the passed input cannot be computed. The converter object is still valid after error.
        */
        virtual size_t GetBufferSizeForConversion( EPixelType sourcePixelType, uint32_t sourceWidth, uint32_t sourceHeight ) const;


        /*!
        \brief Creates a new image by converting an image to a different format.

        The IReusableImage::Reset() method of the destination image is called to set the destination format.
        The image is converted to the destination image according to the current converter settings.
        The padding area of a row in the destination image is set to zero.

        The OutputPaddingX setting is ignored for images that do not support user defined padding, e.g.
        CPylonBitmapImage. See also IReusableImage::IsAdditionalPaddingSupported().

        \param[out]  destinationImage The destination image, e.g. a CPylonImage or CPylonBitmapImage object.
                                      When passing a CPylonBitmapImage object the target format must be supported by the CPylonBitmapImage class.
        \param[in]   sourceImage      The source image, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.

        \pre
            <ul>
            <li> The source and destination images must be different images.
            <li> The source image must be valid.
            <li> The format of the source image must be supported by the converter.
            <li> The destination image must support the destination format.
            <li> The destination image must be able to provide a large enough buffer to hold the image.
            </ul>

        \error
            Throws an exception if the passed parameters are not valid. The converter object is still valid after error.
        */
        virtual void Convert( IReusableImage& destinationImage, const IImage& sourceImage );


        /*!
        \brief Creates a new image by converting an image to a different format.

        The IReusableImage::Reset() method of the destination image is called to set the destination format.
        The image is converted to the destination image according to the current converter settings.
        The padding area of a row in the destination image is set to zero.

        The OutputPaddingX setting is ignored for images that do not support user defined padding, e.g.
        CPylonBitmapImage. See also IReusableImage::IsAdditionalPaddingSupported().

        \param[out]  destinationImage The destination image.
        \param[in]   pSourceBuffer The pointer to the buffer of the source image.
        \param[in]   sourceBufferSizeBytes  The size of the buffer of the source image.
        \param[in]   sourcePixelType The pixel type of the source image.
        \param[in]   sourceWidth     The number of pixels in a row in the source image.
        \param[in]   sourceHeight    The number of rows in the source image.
        \param[in]   sourcePaddingX  The number of extra data bytes at the end of each row. The default value is usually 0.
        \param[in]   sourceOrientation The vertical orientation of the source image in the image buffer. The default value is usually ImageOrientation_TopDown.

        \pre
            <ul>
            <li> The pixel type must be valid.
            <li> The \c sourceWidth value must be >= 0 and < _I32_MAX.
            <li> The \c sourceHeight value must be >= 0 and < _I32_MAX.
            <li> The pointer to the source buffer must not be NULL.
            <li> The source buffer must be large enough to hold the image described by the parameters.
            <li> The format of the input image represented by the given parameter must be supported by the converter.
            <li> The destination image must support the destination format.
            <li> The destination image must be able to provide a large enough buffer to hold the image.
            <li> The source image buffer and the destination image buffer must not be identical.
            </ul>

        \error
            Throws an exception if the passed parameters are not valid. The converter object is still valid after error.
        */
        virtual void Convert( IReusableImage& destinationImage,
                              const void* pSourceBuffer,
                              size_t sourceBufferSizeBytes,
                              EPixelType sourcePixelType,
                              uint32_t sourceWidth,
                              uint32_t sourceHeight,
                              size_t sourcePaddingX,
                              EImageOrientation sourceOrientation
                              );


                /*!
                \brief Creates a new image by converting an image to a different format.

                The image is converted to the destination image according to the current converter settings.
                The padding area of a row in the destination image is set to zero.

                \param[out]  pDestinationBuffer The pointer to the buffer of the destination image.
                \param[in]   destinationBufferSizeBytes The size of the buffer of the destination image.
                \param[in]   sourceImage      The source image, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.

                \pre
                    <ul>
                    <li> The format of the source image must be supported by the converter.
                    <li> The destination image buffer must be large enough to hold the destination image.
                    <li> The source image buffer and the destination image buffer must not be identical.
                    </ul>

                \error
                    Throws an exception if the passed parameters are not valid. The converter object is still valid after error.
                */
        virtual void Convert( void* pDestinationBuffer, size_t destinationBufferSizeBytes, const IImage& sourceImage );


        /*!
        \brief Creates a new image by converting an image to a different format.

        The image is converted to the destination image according to the current converter settings.
        The padding area of a row in the destination image is set to zero.

        \param[out]  pDestinationBuffer The pointer to the buffer of the destination image.
        \param[in]   destinationBufferSizeBytes The size of the buffer of the destination image.
        \param[in]   pSourceBuffer The pointer to the buffer of the source image.
        \param[in]   sourceBufferSizeBytes  The size of the buffer of the source image.
        \param[in]   sourcePixelType   The pixel type of the source image.
        \param[in]   sourceWidth       The number of pixels in a row in the source image.
        \param[in]   sourceHeight      The number of rows in the source image.
        \param[in]   sourcePaddingX    The number of extra data bytes at the end of each row. The default value is usually 0.
        \param[in]   sourceOrientation The vertical orientation of the source image in the image buffer. The default value is usually ImageOrientation_TopDown.

        \pre
            <ul>
            <li> The parameters regarding the source buffer must describe a valid image.
            <li> The format of the input image represented by the given parameter must be supported by the converter.
            <li> If the destination image buffer must be large enough to hold the destination image.
            <li> The the source buffer can not be equal the destination buffer.
            </ul>

        \error
            Throws an exception if the passed parameters are not valid. The converter object is still valid after error.
        */
        virtual void Convert( void* pDestinationBuffer,
                              size_t destinationBufferSizeBytes,
                              const void* pSourceBuffer,
                              size_t sourceBufferSizeBytes,
                              EPixelType sourcePixelType,
                              uint32_t sourceWidth,
                              uint32_t sourceHeight,
                              size_t sourcePaddingX,
                              EImageOrientation sourceOrientation
                              );


                /*!
                \brief Returns true if the image format defined by the given pixel type is a supported input format.

                \param[in]   sourcePixelType The pixel type of the source image.

                \error
                    Does not throw C++ exceptions.
                */
        static bool IsSupportedInputFormat( EPixelType sourcePixelType );


        /*!
        \brief Returns true if the image format defined by the given pixel type is a supported output format.

        \param[in]   destinationPixelType The pixel type of the destination image.

        \error
            Does not throw C++ exceptions.
        */
        static bool IsSupportedOutputFormat( EPixelType destinationPixelType );


        /*!
        \brief Provides access to the node map of the format converter.
        \return Reference to the node map of the format converter.

        \error
            Does not throw C++ exceptions.
        */
        virtual GENAPI_NAMESPACE::INodeMap& GetNodeMap();

    private:
        // The converter object can not be copied.
        CImageFormatConverter( const CImageFormatConverter& src );
        // The converter object can not be copied.
        CImageFormatConverter& operator=( const CImageFormatConverter& src );

        // Internal use only.
        class CImageFormatConverterImpl;
        CImageFormatConverterImpl* m_pImpl;

    public:
        // This class emulates part of the behavior of a GENAPI_NAMESPACE::IEnumerationT<T> interface used for native parameter access.
        // This allows using the EPixelType enumeration.
        class IOutputPixelFormatEnum
        {
        public:
            virtual void operator=( EPixelType outputPixelType ) = 0;
            virtual void SetValue( EPixelType outputPixelType ) = 0;

            virtual EPixelType GetValue() const = 0;
            virtual EPixelType operator()() const = 0;
        };

        /*!
            \brief The pixel data format of the output image.

            This member can be used to get and set the output pixel format using the EPixelType enumeration.
            It emulates the behavior of native parameter access.

            \pre
                The pixel format set must be a supported output pixel format. See IsSupportedOutputFormat().
            \error
                Throws an exception if the set output pixel format is not supported.
        */
        IOutputPixelFormatEnum& OutputPixelFormat;
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_IMAGEFORMATCONVERTER_H_1564142 */
