//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Contains an adapter adapting a grab result to Pylon::IImage.
*/

#pragma once

#ifndef INCLUDED_RESULTIMAGE_H_0326044
#define INCLUDED_RESULTIMAGE_H_0326044

#include <pylon/Image.h>

namespace Pylon
{
    /*!
    \brief Low Level API: Adapts grab result to Pylon::IImage.

    \ingroup  Pylon_LowLevelApi
    */
    template <typename GrabResultT>
    class CGrabResultImageT : public IImage
    {
    public:
        /*!
        \brief Creates a grab result image object.

        \param[in] grabResult A grab result.
        \param[in] isUnique User provided info whether the buffer is referenced only by this grab result.

        \error
            Does not throw C++ exceptions.
        */
        CGrabResultImageT( GrabResultT grabResult, bool isUnique )
            : m_grabResult( grabResult )
            , m_isUnique( isUnique )
        {
        }

        /// Destroys a grab result image object.
        virtual ~CGrabResultImageT()
        {
        }

        // Implements Pylon::IImage.
        virtual bool IsValid() const
        {
            return IsValidImpl();
        }

        // Implements Pylon::IImage.
        virtual EPixelType GetPixelType() const
        {
            return IsValidImpl() ? m_grabResult.GetPixelType() : PixelType_Undefined;
        }

        // Implements Pylon::IImage.
        virtual uint32_t GetWidth() const
        {
            return IsValidImpl() ? static_cast<uint32_t>(m_grabResult.GetSizeX()) : 0;
        }

        // Implements Pylon::IImage.
        virtual uint32_t GetHeight() const
        {
            return IsValidImpl() ? static_cast<uint32_t>(m_grabResult.GetSizeY()) : 0;
        }

        // Implements Pylon::IImage.
        virtual size_t GetPaddingX() const
        {
            return IsValidImpl() ? m_grabResult.GetPaddingX() : 0;
        }

        // Implements Pylon::IImage.
        virtual EImageOrientation GetOrientation() const
        {
            return ImageOrientation_TopDown;
        }

        // Implements Pylon::IImage.
        virtual void* GetBuffer()
        {
            return IsValidImpl() ? m_grabResult.Buffer() : NULL;
        }

        // Implements Pylon::IImage.
        virtual const void* GetBuffer() const
        {
            return IsValidImpl() ? m_grabResult.Buffer() : NULL;
        }

        // Implements Pylon::IImage.
        virtual size_t GetImageSize() const
        {
            return IsValidImpl() ? ComputeBufferSize( m_grabResult.GetPixelType(), static_cast<uint32_t>(m_grabResult.GetSizeX()), static_cast<uint32_t>(m_grabResult.GetSizeY()), m_grabResult.GetPaddingX() ) : 0;
        }

        // Implements Pylon::IImage.
        virtual bool IsUnique() const
        {
            return m_isUnique;
        }

        // Implements Pylon::IImage.
        virtual bool GetStride( size_t& strideBytes ) const
        {
            return IsValidImpl() ? ComputeStride( strideBytes, m_grabResult.GetPixelType(), static_cast<uint32_t>(m_grabResult.GetSizeX()), m_grabResult.GetPaddingX() ) : false;
        }

    protected:
        // Check whether the grab result is valid.
        bool IsValidImpl() const
        {
            return
                m_grabResult.Succeeded()
                && m_grabResult.GetPixelType() != PixelType_Undefined
                && m_grabResult.GetSizeX() >= 0
                && m_grabResult.GetSizeY() >= 0
                && m_grabResult.GetPaddingX() >= 0;
        }

        GrabResultT m_grabResult; ///< The grab result that is adapted to IImage.
        bool m_isUnique; ///< User provided info whether the buffer is referenced only by this adapter.
    };
} // namespace Pylon

#endif /* INCLUDED_RESULTIMAGE_H_0326044 */
