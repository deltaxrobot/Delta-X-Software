//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2018-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  DV
//------------------------------------------------------------------------------
/*!
\file
\brief  Contains support for writing video files in MP4 format, provided by a supplementary software package.
*/
#ifndef INCLUDED_VIDEOWRITER_H_3842348390
#define INCLUDED_VIDEOWRITER_H_3842348390

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
#include <pylon/Image.h>
#include <pylon/_VideoWriterParams.h>
#include <GenApi/INodeMap.h>




namespace Pylon
{
    class CVideoWriterImpl;
    using namespace Basler_VideoWriterParams;

    /*!
    \class  CVideoWriter
    \brief  Supports writing video files.
    \note   Note that a supplementary software package containing additional libraries has to be installed for this.
    */
    class PYLONUTILITY_API CVideoWriter : public Basler_VideoWriterParams::CVideoWriterParams_Params
    {
    public:
        /*!
        \brief Creates a video writer object.

        \error
        Throws a RuntimeException when no memory can be allocated.
        */
        CVideoWriter();

        /*!
        \brief Destroys the video writer object.

        \error
        Does not throw C++ exceptions.
        */
        virtual ~CVideoWriter();

        /*!
        \brief Checks if video writing is supported.

        Checks if all necessary dynamic libraries of the supplementary software package are installed and can be loaded.
        This does not check if the codec for the video can be used. This is checked in Open().

        \return Returns true if video writing is supported.

        \error
        Does not throw C++ exceptions.
        */
        static bool IsSupported();

        /*!
        \brief Easy way to set parameters required for video recording.

        This is a convenient way to set all required parameters in a single function call.
        The parameters \c width, \c height, \c framesPerSecondPlaybackSpeed and \c quality are set in the nodemap.
        The parameter \c inputPixelType is checked for its convertibility to YUV420p or whether it is already YUV420p.
        Advanced parameters can be accessed using the nodemap provided by GetNodeMap().

        \param[in]   width                          The number of pixels in a row of the video file to save.
        \param[in]   height                         The number of rows of the video file to save.
        \param[in]   inputPixelType                 The pixel type of the images that will be added to the video writer. This input is used to derive the video format. Currently the output is always YUV420p.
        \param[in]   framesPerSecondPlaybackSpeed   The playback speed in frames per second.
        \param[in]   quality                        The quality setting, valid range is 1 ... 100.

        \pre The VideoWriter ist closed.

        \error
        Throws a C++ exception when a parameter is out of range, set to an invalid value or parameters cannot be changed (e.g., after calling Open()).
        */
        virtual void SetParameter(
            uint32_t width, uint32_t height,
            EPixelType inputPixelType,
            double framesPerSecondPlaybackSpeed,
            uint32_t quality
            );

            /*!
            \brief Opens a video file for writing.

            If a file with the same \c filename already exists, it will be overwritten.

            \param[in]  filename  Name and path of the video file.

            \pre
            <ul>
            <li> The VideoWriter ist closed.
            <li> The width and height parameters are larger than 1.
            </ul>

            \error
            Throws an exception if the video file cannot be opened.
            Throws an exception if the current parameters do not meet codec requirements.

            \threading
            This method is synchronized using the lock provided by GetLock().
            */
        virtual void Open( const Pylon::String_t& filename );

        /*!
        \brief Returns the open state of the video file.

        \return Returns true if open.

        \error
        Does not throw C++ exceptions.

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsOpen() const;

        /*!
        \brief Closes the video file.

        \error
        Does not throw C++ exceptions.

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual void Close();

        /*!
        \brief Adds the image to the video file. Converts the image to the correct format if required.

        The image is automatically converted to YUV420p unless the input \c pixelType is already YUV420p.
        The orientation of the image is always converted to \c ImageOrientation_TopDown unless the input\c  pixelType is
        YUV420p. In that case, the \c orientation of the image must already be \c ImageOrientation_TopDown. See preconditions.

        \param[in]   pBuffer     The pointer to the buffer of the image.
        \param[in]   bufferSize  The size of the buffer in byte.
        \param[in]   pixelType   The pixel type of the image to save.
        \param[in]   width       The number of pixels in a row of the image to save.
        \param[in]   height      The number of rows of the image to save.
        \param[in]   paddingX    The number of extra data bytes at the end of each line.
        \param[in]   orientation The vertical orientation of the image in the image buffer.

        \pre
        <ul>
        <li> The file is open.
        <li> The image added is valid.
        <li> The \c pixelType of the image to add is a supported input format of the Pylon::CImageFormatConverter or YUV420p.
        <li> If the pixelType is YUV420p the \c orientation has to be \c ImageOrientation_TopDown.
        <li> The width and height of the image match the values passed when opening the video file.
        </ul>

        \error
        Throws an exception if the image cannot be added.

        \threading
        This method is synchronized using the lock provided by GetLock().

        */
        virtual void Add( const void* pBuffer, size_t bufferSize, Pylon::EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, Pylon::EImageOrientation orientation );

        /*!
        \brief Adds the image to the video file. Converts the image to the correct format if required.

        The image is automatically converted to YUV420p unless the input \c pixelType is already YUV420p.
        The orientation of the image is always converted to \c ImageOrientation_TopDown unless the input \c pixelType is
        YUV420p. In that case, the \c orientation of the image must already be \c ImageOrientation_TopDown. See preconditions.

        \param[in]   image The image to add, e.g., a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.

        \pre
        <ul>
        <li> The file is open.
        <li> The image added is valid.
        <li> The \c pixelType of the image to add is a supported input format of the Pylon::CImageFormatConverter or YUV420p.
        <li> If the pixelType is YUV420p the \c orientation has to be \c ImageOrientation_TopDown.
        <li> The width and height of the image match the values passed when opening the video file.
        </ul>

        \error
        Throws an exception if the image cannot be added.

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual void Add( const Pylon::IImage& image );

        /*!
        \brief Can be used to check whether the given image is added to the video file without prior conversion when Add() is called.

        \param[in]   pixelType   The pixel type of the image to save.
        \param[in]   width       The number of pixels in a row of the image to save.
        \param[in]   height      The number of rows of the image to save.
        \param[in]   paddingX    The number of extra data bytes at the end of each row.
        \param[in]   orientation The vertical orientation of the image data in the video file.

        \return Returns true if the image is added to the video stream without prior conversion when Add() is called.
        Returns false if the image is automatically converted when Add() is called.
        Returns false if the image cannot be added at all. See the preconditions of Add() for more information.

        \error
        Does not throw C++ exceptions.
        */
        virtual bool CanAddWithoutConversion( Pylon::EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX, Pylon::EImageOrientation orientation );

        /*!
        \brief Can be used to check whether the given image is added to the video file without prior conversion when Add() is called.

        \param[in]   image  The image to save, e.g. a CPylonImage, CPylonBitmapImage, or Grab Result Smart Pointer object.
        \return Returns true if the image is added to the video stream without prior conversion when Add() is called.
        Returns false if the image is automatically converted when Add() is called.
        Returns false if the image cannot be added at all. See the preconditions of Add() for more information.

        \error
        Does not throw C++ exceptions.
        */
        virtual bool CanAddWithoutConversion( const Pylon::IImage& image );

        /*!
        \brief Provides access to all parameters via a nodemap.
        \error
        Does not throw C++ exceptions.
        */
        virtual GENAPI_NAMESPACE::INodeMap& GetNodeMap();

    protected:
        /*!
        \brief Provides access to the lock used for synchronizing the access to the video writer.
        \error
        Does not throw C++ exceptions.
        */
        CLock& GetLock();

    private:
        CVideoWriterImpl* m_pImpl;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // INCLUDED_VIDEOWRITER_H_3842348390
