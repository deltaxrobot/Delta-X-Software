//-----------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/**
\file
\brief Contains the region event handler base class.
*/

#pragma once

#include <pylon/stdinclude.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

/*!
 * \namespace Pylon
 * \brief The Pylon namespace
 */
namespace Pylon
{
    /*!
     * \namespace Pylon::DataProcessing
     * \brief The DataProcessing namespace
     */
    namespace DataProcessing
    {
        /**
        \class  CRegionUserBufferEventHandler
        \brief  The CRegion user buffer event handler base class.

        You have the option of passing an object derived from this class when calling CRegion::AttachUserBuffer().
        When the CRegion doesn't need the user buffer anymore, it will call the CRegionUserBufferEventHandler::OnRegionUserBufferDetached()
        method. You can override this function to execute your custom code when the user buffer has been detached implicitly.

        The user is responsible for ensuring the object is valid until CRegionUserBufferEventHandler::OnRegionUserBufferDetached() has been called.
        */
        class CRegionUserBufferEventHandler
        {
        public:

            /**
            \brief This method is called after the region class has released its user buffer.

            This method is called after the region class releases its region buffer.
            If a user buffer has been attached using CRegion::AttachUserBuffer(), you can use this to free
            your user buffer.

            If you created the event handler on the heap using \c new, you can call <tt>delete this</tt> at the end of the function.

            \code{.cpp}
            // Sample handler to show how to delete the handler when allocating the handler on the heap.
            class MyHandler : public CRegionUserBufferEventHandler
            {
                OnRegionUserBufferDetached( void* pUserBuffer, size_t bufferSizeBytes ) override
                {
                    // Use our custom memory allocator to free the user buffer.
                    MyCustomFreeMemory( pUserBuffer );

                    // Delete the handler.
                    delete this;
                }
            };

            // Use our custom memory allocator for region data.
            void* pUserBuffer = MyCustomAllocateMemory( sizeof(SRegionEntryRLE32) * 10000 );

            // Attach user buffer using a heap-allocated event handler.
            CRegion region;
            region.AttachUserBuffer(pUserBuffer, sizeof(SRegionEntryRLE32) * 10000, RegionType_RLE32, 0, 0, 0, 0, 0, 0 , new MyHandler());
            \endcode

            The default implementation does nothing. You can override this function to execute custom code.

            \param[in] pUserBuffer Pointer to the user buffer passed if the user buffer was attached using CRegion::AttachUserBuffer().
            \param[in] bufferSizeBytes Size of the user buffer passed if the user buffer was attached using CRegion::AttachUserBuffer().

            \error
                This method must not throw any exceptions.
            */
            virtual void OnRegionUserBufferDetached(const void* pUserBuffer, size_t bufferSizeBytes)
            {
                PYLON_UNUSED(pUserBuffer);
                PYLON_UNUSED(bufferSizeBytes);
            }
        };
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */
