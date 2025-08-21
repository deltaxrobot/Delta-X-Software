//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2024 Basler AG
//  http://www.baslerweb.com
//  Author: AH
//-----------------------------------------------------------------------------
/*!
\file
\brief  Definition of byte buffer class with smart pointer semantics.
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <pylon/PylonBase.h>

namespace Pylon
{
    ///////////////////////////////////////////////////////////////////////
    /// \brief Byte buffer with smart pointer semantics. Not thread safe.
    ///
    /// \ingroup Pylon_LowLevelApi
    class PYLONBASE_API CSharedByteBuffer
    {
    public:


        ///////////////////////////////////////////////////////////////////////
        /// \brief default constructer for shared buffer
        ///
        /// \ingroup Pylon_LowLevelApi
        CSharedByteBuffer();


        ///////////////////////////////////////////////////////////////////////
        /// \brief constructer for shared buffer form buffer size
        ///
        /// \ingroup Pylon_LowLevelApi
        explicit CSharedByteBuffer(size_t nBytes);


        ///////////////////////////////////////////////////////////////////////
        /// \brief copy constructor
        ///
        /// \ingroup Pylon_LowLevelApi
        CSharedByteBuffer(const CSharedByteBuffer & other);


        ///////////////////////////////////////////////////////////////////////
        /// \brief destructor
        ///
        /// \ingroup Pylon_LowLevelApi
        ~CSharedByteBuffer();


        ///////////////////////////////////////////////////////////////////////
        /// \brief copy assignment operator
        ///
        /// \ingroup Pylon_LowLevelApi
        CSharedByteBuffer & operator=(const CSharedByteBuffer & rhs);


        ///////////////////////////////////////////////////////////////////////
        /// \brief pointer like test if nullptr
        ///
        /// \ingroup Pylon_LowLevelApi
        explicit operator bool() const;


        ///////////////////////////////////////////////////////////////////////
        /// \brief release the referenz on buffer and memory if last referenzing object.
        ///
        /// \ingroup Pylon_LowLevelApi
        void Release();


        ///////////////////////////////////////////////////////////////////////
        /// \brief return size of buffer in bytes
        ///
        /// \ingroup Pylon_LowLevelApi
        size_t GetSize() const;


        ///////////////////////////////////////////////////////////////////////
        /// \brief get pointer to buffer memory
        /// \returns nullptr if buffer references no memory
        /// \ingroup Pylon_LowLevelApi
        uint8_t* GetBuffer();


        ///////////////////////////////////////////////////////////////////////
        /// \brief get pointer to buffer memory
        /// \returns nullptr if buffer references no memory
        /// \ingroup Pylon_LowLevelApi
        const uint8_t* GetBuffer() const;

        ///////////////////////////////////////////////////////////////////////
        /// \brief test if buffer references memory
        ///
        /// \ingroup Pylon_LowLevelApi
        bool IsNull() const;

    private:
        class CSharedByteBufferImpl* m_pImpl;
    };
}