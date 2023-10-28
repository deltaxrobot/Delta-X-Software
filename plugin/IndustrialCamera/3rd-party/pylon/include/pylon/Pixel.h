//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
    \file
    \brief  Contains structs describing pixel layouts.
*/

#ifndef INCLUDED_PIXEL_H_9632837
#define INCLUDED_PIXEL_H_9632837

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */
#pragma pack(push, 1)

    //-----------------------------------------------------------------------
    //  Structs needed for BGR and RGB formats
    //-----------------------------------------------------------------------

    /// Describes the memory layout of a BGRA8 pixel. This pixel is used in Windows bitmaps.
    struct SBGRA8Pixel
    {
        uint8_t B;    ///<  Blue
        uint8_t G;    ///<  Green
        uint8_t R;    ///<  Red
        uint8_t A;    ///<  Transparency
    };

    /// Describes the memory layout of a BGR8 pixel. This pixel is used in Windows bitmaps.
    struct SBGR8Pixel
    {
        uint8_t B;    ///<  Blue
        uint8_t G;    ///<  Green
        uint8_t R;    ///<  Red
    };

    /// Describes the memory layout of a RGB8 pixel.
    struct SRGB8Pixel
    {
        uint8_t R;    ///<  Red
        uint8_t G;    ///<  Green
        uint8_t B;    ///<  Blue
    };

    /// Describes the memory layout of a RGB16 pixel.
    struct SRGB16Pixel
    {
        uint16_t R;    ///<  Red
        uint16_t G;    ///<  Green
        uint16_t B;    ///<  Blue
    };

    //-----------------------------------------------------------------------
    //  Structs needed for variants of YUV422 formats
    //-----------------------------------------------------------------------

    /// Describes the memory layout of a YUV422_UYVY pixel with information about brightness and chroma for two pixels.
    struct SYUV422_UYVY //  DCAM Variant
    {
        uint8_t U;  ///< chroma U (both pixels)
        uint8_t Y1; ///< brightness Pixel 1
        uint8_t V;  ///< chroma V (both pixels)
        uint8_t Y2; ///< brightness Pixel 2
        typedef uint8_t value_type;
    };

    /// Describes the memory layout of a YUV422_YUYV pixel with information about brightness and chroma for two pixels.
    struct SYUV422_YUYV //  Microsoft preferred variant
    {
        uint8_t Y1; ///< brightness Pixel 1
        uint8_t U;  ///< chroma U (both pixels)
        uint8_t Y2; ///< brightness Pixel 2
        uint8_t V;  ///< chroma V (both pixels)
        typedef uint8_t value_type;
    };

#pragma pack(pop)

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PIXEL_H_9632837 */
