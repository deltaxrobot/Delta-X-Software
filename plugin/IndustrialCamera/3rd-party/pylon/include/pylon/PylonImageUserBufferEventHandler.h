//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2021-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/**
\file
\brief Contains the pylon image event handler base class.
*/

#pragma once

#ifndef INCLUDED_PYLONIMAGEUSERBUFFEREVENTHANDLER_H_
#define INCLUDED_PYLONIMAGEUSERBUFFEREVENTHANDLER_H_

#include <pylon/stdinclude.h>

#pragma pack(push, PYLON_PACKING)

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
    */

    /**
    \class  CPylonImageUserBufferEventHandler
    \brief  The CPylonImage user buffer event handler base class.

    You can optionally pass an object derived from this class when calling CPylonImage::AttachUserBuffer().
    When the CPylonImage doesn't need the user buffer anymore, it will call the CPylonImageUserBufferEventHandler::OnPylonImageUserBufferDetached()
    method. You can override this function to execute your custom code when the user buffer has been detached implicitly.

    The user is responsible for ensuring the object is valid until CPylonImageUserBufferEventHandler::OnPylonImageUserBufferDetached() has been called.
    */
    class CPylonImageUserBufferEventHandler
    {
    public:

        /**
        \brief This method is called after the image class has released its user buffer.

        This method is called after the image class releases its image buffer.
        In case a user buffer has been attached using CPylonImage::AttachUserBuffer() you can use this to free
        your user buffer.

        In case you created the event handler on the heap using \c new, you can call <tt>delete this</tt> at the end of the function.

        \code{.cpp}
        // Sample handler to show how to delete the handler when allocating the handler on the heap.
        class MyHandler : public CPylonImageUserBufferEventHandler {
            OnPylonImageUserBufferDetached( void* pUserBuffer, size_t bufferSizeBytes ) override {
                // Use our custom memory allocator to free the user buffer.
                MyCustomFreeMemory( pUserBuffer );

                // Delete the handler.
                delete this;
            }
        };

        // Use our custom memory allocator for pixel data.
        void* pUserBuffer = MyCustomAllocateMemory( 640 * 480 );
        
        // Attach user buffer using a heap-allocated event handler.
        CPylonImage image;
        image.AttachUserBuffer(pUserBuffer, (640 * 480), PixelType_Mono8, 640, 480, 0, ImageOrientation_TopDown, new MyHandler() );
        \endcode

        The default implementation does nothing. You can override this function to execute custom code.

        \param[in] pUserBuffer Pointer to the user buffer passed when the user buffer was attached using CPylonImage::AttachUserBuffer().
        \param[in] bufferSizeBytes Size of the user buffer passed when the user buffer was attached using CPylonImage::AttachUserBuffer().

        \error
            This function must not throw any exceptions.
        */
        virtual void OnPylonImageUserBufferDetached( void* pUserBuffer, size_t bufferSizeBytes )
        {
            PYLON_UNUSED( pUserBuffer );
            PYLON_UNUSED( bufferSizeBytes );
        }
    };

    /**
     * @}
     */
}

#pragma pack(pop)

#endif /* INCLUDED_PYLONIMAGEUSERBUFFEREVENTHANDLER_H_ */
