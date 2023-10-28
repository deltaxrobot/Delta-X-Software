//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Lutz Koschorreck
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Definition of the IChunkParser interface.
*/

#pragma once

#ifndef CHUNKPARSER_H__
#define CHUNKPARSER_H__

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenICamFwd.h>
#include <pylon/stdinclude.h>
#include <pylon/PylonBase.h>

// additional forwards
namespace GENAPI_NAMESPACE
{
    class CChunkAdapter;
    struct AttachStatistics_t;
}

namespace Pylon
{
    /*! \interface IChunkParser
        \brief  Low Level API: The interface for chunk parsers analyzing a data stream consisting of chunks

        When chunk data is enabled in the camera the stream sends additional data along with
        the image. This data needs to be extracted with help of a chunk parser.
        These are created using the camera's member function IPylonDevice::CreateChunkParser().

        When an image buffer containing chunked data is passed to a chunk parser,
        the camera's chunk related parameters are updated. After changing the data
        layout either by changing the AOI or enabling/disabling chunk features the
        parser needs to be reinitialized by calling IChunkParser::AttachBuffer().
        Thereafter buffers with the same layout are processed with the
        IChunkParser::UpdateBuffer() method. Chunk related properties remain unchanged
        until a new buffer is passed in.

        After usage return the chunk parser with a call of the camera's
        IPylonDevice::DestroyChunkParser() member function.

        The code snippet below demonstrates the usage of a chunk parser. A
        complete program is found in the sample AcquireSingleFrame_ChunkImage.

        \note Check the payload type of the GrabResult_t before attaching or
        updating the buffer.

        \ingroup Pylon_LowLevelApi

        \code
            IChunkParser &ChunkParser = *Camera.CreateChunkParser();

            // enable Frame Counter chunk
            Camera.ChunkModeActive.SetValue( true );
            Camera.ChunkSelector.SetValue( ChunkSelector_Framecounter );
            Camera.ChunkEnable.SetValue( true );

            // retrieve data from the chunk
            GrabResult Result;
            if (StreamGrabber.RetrieveResult( Result ) &&
                Result.Succeeded() &&
                Result.PayloadType() == PayloadType_ChunkData)
            {
                ChunkParser.AttachBuffer( Result.Buffer(), Result.GetPayloadSize() );
                int64_t frameCounter = Camera.ChunkFramecounter.GetValue();
            }
        \endcode

    */
    interface PUBLIC_INTERFACE IChunkParser
    {
    public:
        /// Pass in a buffer and let the chunk parser analyze it.
        /*! Corresponding parameters of the camera object reflecting the chunked data
            will be updated.
            \param pBuffer Pointer to the new buffer
            \param BufferLength Size of the new buffer in bytes
            \param pAttachStatistics (optional) Pointer to a record taking statistic
            data of the analyzed buffer
         */
        virtual void AttachBuffer( const void* pBuffer, int64_t BufferLength, GENAPI_NAMESPACE::AttachStatistics_t* pAttachStatistics = NULL ) = 0;

        /// \brief Detaches a buffer from the chunk parser. The buffer will no longer accessed by the chunk parser
        /*!
        //  An attached buffer must be detached before freeing it. When attaching a new buffer, the previous
        //  one gets detached automatically.
        */
        virtual void DetachBuffer() = 0;

        /// \brief Pass in a buffer and let the chunk parser update the camera object's parameters.
        /*!
            This method can be used when the layout of the chunk data hasn't changed since a previous buffer
            has been attached to the chunk parser. In this case UpdateBuffer is slightly faster than AttachBuffer,
            because the buffer's layout is reused.
            If you call UpdateBuffer without having called AttachBuffer first, a LogicalErrorException is raised.
            \param pBaseAddress Pointer to the new buffer
        */
        virtual void UpdateBuffer( const void* pBaseAddress ) = 0;
       /// Checks if buffer has a CRC attached
        /*!
            \return true if the buffer contains CRC value.
        */
        virtual bool HasCRC() const = 0;

        /// Checks CRC sum of buffer
        /*!
            \return true if the contained CRC equals the computed value.
        */
        virtual bool CheckCRC() const = 0;
    };

    /*!
        \interface ISelfReliantChunkParser
        \brief Low Level API: Interface for chunk parsers with an own chunk data node map attached.
        This type of chunk parser updates the an own node map containing
        only the chunk data nodes instead of updating the devices node map.
        This is useful for attaching the chunk data to a grab result.

        \ingroup Pylon_LowLevelApi
    */
    interface ISelfReliantChunkParser : public IChunkParser
    {
        /// Provides access to the chunk data node map that the parser updates.
        /*!
            \return The chunk data node map of the parser
        */
        virtual GENAPI_NAMESPACE::INodeMap* GetChunkDataNodeMap() = 0;

        /// Makes the object to destroy itself.
        /*!
            This is an alternative to destroying it via the IPylonDevice interface.
            It is used when the device has been destroyed already.
        */
        virtual void Destroy() = 0;
    };

    /// Low Level API: Base class for chunk parsers returned by camera objects
    /*!
        Part implementation of chunk parser of common functionality.

        \ingroup Pylon_LowLevelApi
    */
    class PYLONBASE_API CChunkParser : public ISelfReliantChunkParser
    {
    public:
        // \name IChunkParser implementation
        // \{
        void AttachBuffer( const void* pBuffer, int64_t BufferLength, GENAPI_NAMESPACE::AttachStatistics_t* pAttachStatistics = NULL );
        void DetachBuffer();
        void UpdateBuffer( const void* pBaseAddress );
        GENAPI_NAMESPACE::INodeMap* GetChunkDataNodeMap();
        void Destroy();
        // \}

    protected:
        /// default constructor - make it protected to prevent this class from instantiation
        explicit CChunkParser( GENAPI_NAMESPACE::CChunkAdapter* pParser );
        /// destructor
        virtual ~CChunkParser();

    protected:
        /// Pointer to the GenApi workhorse.
        GENAPI_NAMESPACE::CChunkAdapter* m_pParser;

        class PYLONBASE_API CBuffer
        {
        public:
            CBuffer( const void* pBuffer, int64_t BufferSize_by );
            ~CBuffer();
            operator bool() const;
            int64_t GetSize() const;
            const void* operator&() const;

        private:
            const void* m_pBuffer;
            int64_t m_BufferLength_by;

        } m_AttachedBuffer;

        bool m_IsBufferAttached;
    };

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // __CHUNKPARSER_H__
