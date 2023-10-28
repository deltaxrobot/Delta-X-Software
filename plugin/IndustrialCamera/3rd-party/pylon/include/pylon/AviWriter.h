//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains support for writing files in the Audio Video Interleave (AVI) format.
*/
#ifndef INCLUDED_AVIWRITER_H_9434931
#define INCLUDED_AVIWRITER_H_9434931

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/Image.h>

namespace Pylon
{
    /// Exception thrown if a fatal error occurs (e.g. access violations, ...) when accessing an AVI video file
    class AviWriterFatalException : public GenericException
    {
    public:
        /** \brief \copybrief GenericException::GenericException() */
        AviWriterFatalException( const char* pDescription, const char* pSourceFileName, int SourceLine );
        AviWriterFatalException( const char* pDescription, const char* pSourceFileName, int SourceLine, const char* pExceptionType );
        AviWriterFatalException( const char* pDescription, const char* pSourceFileName, int SourceLine, const char* pEntryPoint, const char* pErrorNodeName, const char* pExceptionType );
    };

    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    /// Forward reference for compression options, requires additional include of AviCompressionOptions.h
    struct SAviCompressionOptions;

    /// List the possibilities for selecting a key frame when using compression.
    enum EKeyFrameSelection
    {
        KeyFrameSelection_NoKeyFrame, //!< Indicates that an image is not a key frame.
        KeyFrameSelection_KeyFrame,   //!< Indicates that an image is a key frame.
        KeyFrameSelection_Auto        //!< Every nth frame is a key frame. The value of n is specified by passing its value in the SAviCompressionOptions in the autoKeyFrameInsertionRate member when opening the AVI Writer.
    };

    /*!
    \class  CAviWriter
    \brief  Supports writing AVI files.
    */
    class PYLONUTILITY_API CAviWriter
    {
    public:
        /*!
        \brief Creates an AVI writer object.

        \error
            Does not throw C++ exceptions.
        */
        CAviWriter();

        /*!
        \brief Destroys the AVI writer object.

        \error
            Does not throw C++ exceptions.
        */
        virtual ~CAviWriter();


        /*!
        \brief Opens an AVI file for writing.

        If a file with the same \c filename already exists, it will be overwritten.

        \param[in]   filename  Name and path of the image.
        \param[in]   framesPerSecondPlayback The frame rate of the AVI file when shown in a media player.
        \param[in]   pixelType The pixel type of the image in the AVI file.
        \param[in]   width     The number of pixels in a row.
        \param[in]   height    The number of rows of the image.
        \param[in]   orientation The vertical orientation of the image data in the AVI file.
        \param[in,out]   pCompressionOptions Compression can be enabled by passing compression options. See SAviCompressionOptions.

        \pre
        <ul>
        <li> The AVI file is closed.
        <li> The pixelType is either PixelType_Mono8, PixelType_BGR8packed or PixelType_BGRA8packed
        <li> The \c width value must be > 0 and < _I32_MAX.
        <li> The \c height value must be > 0 and < _I32_MAX.
        </ul>

        \error
            Throws an exception if the AVI file cannot be opened.
            Throws an exception if the preconditions are not met.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void Open(
            const String_t& filename,
            double framesPerSecondPlayback,
            EPixelType pixelType,
            uint32_t width, uint32_t height,
            EImageOrientation orientation = ImageOrientation_BottomUp,
            SAviCompressionOptions* pCompressionOptions = NULL
            );

       /*!
        \brief Returns the open state of the AVI file.

        \return Returns true if open.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsOpen();


        /*!
        \brief Closes the AVI file.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void Close();


        /*!
        \brief Adds the image to the AVI file. Converts the image to the correct format if required.

        The image is automatically converted to the format passed when opening the file if needed.
        The image is also converted if the stride of the passed image is not aligned to 4 byte.
        The image is also converted if the orientation of the passed image does mot match the value passed when opening the AVI file.

        If more control over the conversion is required, the CImageFormatConverter class
        can be used to convert other images with a CPylonBitmapImage object as target.
        The CPylonBitmapImage object can then be added to the AVI file.

        \param[in]   image The image to add, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \param[in]   keyFrameSelection Can be used to control key frame selection for compressed images if needed.

        \pre
        <ul>
        <li> The file is open.
        <li> The image added is valid.
        <li> The pixel type of the image to add is a supported input format of the Pylon::CImageFormatConverter.
        <li> The width and height of the \c image match the values passed when opening the AVI file.
        <li> The total size of the AVI file must not exceed 2 GB. See CAviWriter::GetImageDataBytesWritten().
        </ul>

        \error
            Throws an exception if the image cannot be added.

        \threading
            This method is synchronized using the lock provided by GetLock().

        */
        virtual void Add( const IImage& image, EKeyFrameSelection keyFrameSelection = KeyFrameSelection_Auto );


        /*!
        \brief Adds the image to the AVI file. Converts the image to the correct format if required.

        See Add( const Image&) for more details.

        \param[in]   pBuffer     The pointer to the buffer of the image.
        \param[in]   bufferSize The size of the buffer in byte.
        \param[in]   pixelType The pixel type of the image to save.
        \param[in]   width     The number of pixels in a row of the image to save.
        \param[in]   height    The number of rows of the image to save.
        \param[in]   paddingX  The number of extra data bytes at the end of each line.
        \param[in]   orientation The vertical orientation of the image in the image buffer.
        \param[in]   keyFrameSelection Can be used to control key frame selection for compressed images if needed.

        \pre
        <ul>
        <li> The file is open.
        <li> The image added is valid.
        <li> The pixel type of the image to add is a supported input format of the Pylon::CImageFormatConverter.
        <li> The width and height of the \c image match the values passed when opening the AVI file.
        <li> The total size of the AVI file must not exceed 2 GB. See CAviWriter::GetImageDataBytesWritten().
        </ul>

        \error
            Throws an exception if the image cannot be added.

        \threading
            This method is synchronized using the lock provided by GetLock().

        */
        virtual void Add( const void* pBuffer, size_t bufferSize, EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, EImageOrientation orientation, EKeyFrameSelection keyFrameSelection = KeyFrameSelection_Auto );


        /*!
        \brief Can be used to check whether the given image is added to the AVI file without prior conversion when Add() is called.

        \param[in]   pixelType The pixel type of the image to save.
        \param[in]   width     The number of pixels in a row of the image to save.
        \param[in]   height    The number of rows of the image to save.
        \param[in]   paddingX  The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image data in the AVI file.

        \return Returns true if the image is added to the AVI stream without prior conversion when Add() is called.
                Returns false if the image is automatically converted when Add() is called.
                Returns false if the image cannot be added at all. See the preconditions of Add() for more information.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool CanAddWithoutConversion( EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, EImageOrientation orientation );


        /*!
        \brief Can be used to check whether the given image is added to the AVI file without prior conversion when Add() is called.

        \param[in]   image  The image to save, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \return Returns true if the image is added to the AVI stream without prior conversion when Add() is called.
                Returns false if the image is automatically converted when Add() is called.
                Returns false if the image cannot be added at all. See the preconditions of Add() for more information.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool CanAddWithoutConversion( const IImage& image );

        /*!
        \brief Provides access to the number of images that have been added to the AVI file.

        \return Returns the number of images that have been added to the AVI file.
                Returns 0 if no AVI file has been written yet.
        \error
            Does not throw C++ exceptions.
        */
        virtual size_t GetCountOfAddedImages() const;

        /*!
        \brief Provides access to the number of image data bytes written to the AVI file.

        This value is updated with each call to AviWriter::Add().

        Depending on the used image format and codec, about
        5 KB of header information and padding bytes are written to the AVI file.
        Furthermore, 24 additional bytes are needed per image for chunk header and index entry data.

        \return Returns the number of image data bytes that have been written to the AVI file.
                Returns 0 if no AVI File has been written yet.
                This size does not include the sizes of the AVI file header and AVI file index.

        \error
            Does not throw C++ exceptions.
        */
        virtual size_t GetImageDataBytesWritten() const;

    protected:

        /*!
        \brief Provides access to the lock used for synchronizing the access to the AVI writer.

        \error
            Does not throw C++ exceptions.
        */
        CLock& GetLock();


    private:
        // The object can not be copied.
        CAviWriter( const CAviWriter& );
        // The object can not be copied.
        void operator = ( const CAviWriter& );

        // Internal use only.
        class CAviWriterImpl;
        CAviWriterImpl* m_pImpl;
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_AVIWRITER_H_9434931 */
