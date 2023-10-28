//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains an interface for a buffer factory.
*/

#ifndef INCLUDED_BUFFERFACTORY_H_264599
#define INCLUDED_BUFFERFACTORY_H_264599

#include <pylon/stdinclude.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


namespace Pylon
{
    /*!
    \class  IBufferFactory
    \brief  Usable to create a custom buffer factory when needed.
    \ingroup Pylon_InstantCameraApiGeneric
    */
    interface IBufferFactory
    {
    public:
        /// Ensure proper destruction by using a virtual destructor.
        virtual ~IBufferFactory() = 0;

        /*!
        \brief Allocates a buffer and provides additional context information.


        \param[in] bufferSize      The size of the buffer that has to be allocated.
        \param[out] pCreatedBuffer Return the pointer to the allocated buffer. May return NULL if the allocation fails.
        \param[out] bufferContext  Context information that belongs to the buffer.
                                   This context information is provided when FreeBuffer() is called.
                                   The value can be left unchanged if not needed.

        \threading
        This method can be run by different threads. It is called from threads that
        call Pylon::CInstantCamera::StartGrabbing() and it can be called by the internal
        grab engine thread.

        \error
            May throw an exception if the allocation fails.
        */
        virtual void AllocateBuffer( size_t bufferSize, void** pCreatedBuffer, intptr_t& bufferContext ) = 0;


        /*!
        \brief Frees a previously allocated buffer.

        \param[in] pCreatedBuffer The pointer to the allocated buffer. Created by this factory.
        \param[in] bufferContext  Context information of the buffer returned by AllocateBuffer().

        \error
            Does not throw C++ exceptions.
        */
        virtual void FreeBuffer( void* pCreatedBuffer, intptr_t bufferContext ) = 0;


        /*!
        \brief Destroys the buffer factory.

        This method is called when the buffer factory is not needed any longer.
        The object implementing IBufferFactory can be deleted by calling: delete this.

        \threading
        This method can be run by different threads. It is called from threads that are running the
        destructor of a Pylon::CGrabResultPtr or call Pylon::CInstantCamera::StopGrabbing().

        \error
            C++ exceptions from this call will be caught and ignored.
        */
        virtual void DestroyBufferFactory() = 0;
    };

    // Implementation required for Windows only.
    // Note: the C++ standards >= C11 prohibit pure virtual destructors with a function body
    // in the declaration. Consequently GCC 4.0 and newer GCC versions reject an inline implementation
    // in the class.
    inline IBufferFactory::~IBufferFactory()
    {
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_BUFFERFACTORY_H_264599 */
