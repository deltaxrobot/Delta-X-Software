//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung, Edgar Katzer, AG
//-----------------------------------------------------------------------------
/*!
\file
\brief    Definition of types of helper functions concerning image format and pixel type.
\ingroup  PYLON_PUBLIC
*/

#ifndef INCLUDED_PIXELTYPE_H_1534845
#define INCLUDED_PIXELTYPE_H_1534845

#if _MSC_VER > 1000
#pragma once
#endif

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

    // Bitmask value of the monochrome type. Internal use only.
#define PIXEL_MONO  (0x01000000)
    // Bitmask value of the color pixel type. Internal use only.
#define PIXEL_COLOR (0x02000000)
    // Pixel type is not standard
#define PIXEL_CUSTOMTYPE (0x80000000)
    // Sets the bit count of pixel type. Internal use only.
#define PIXEL_BIT_COUNT(n) ((n) << 16)

    /*!
    \brief Lists the available pixel types.

    These pixel types are returned by a grab result and are used by the Image Handling Support classes.

    The camera parameter interface classes define additional pixel format enumerations. These pixel format enumerations
    are different from the enumeration EPixelType pylon uses, e.g. the pylon pixel type PixelType_Mono1packed
    corresponds to PixelFormat_Mono1packed or PixelFormat_Mono1p. See
    the documentation of the parameter interface classes for more information.

    The camera User's Manual provides more information on pixel formats and the memory layout of the image data.
    */
    enum EPixelType
    {
        PixelType_Undefined = -1, //!< Undefined pixel type.
        PixelType_Mono1packed = PIXEL_CUSTOMTYPE | PIXEL_MONO | PIXEL_BIT_COUNT( 1 ) | 0x000c,  //!< alias PixelFormat_Mono1Packed or PixelFormat_Mono1p
        PixelType_Mono2packed = PIXEL_CUSTOMTYPE | PIXEL_MONO | PIXEL_BIT_COUNT( 2 ) | 0x000d,  //!< alias PixelFormat_Mono2Packed or PixelFormat_Mono2p
        PixelType_Mono4packed = PIXEL_CUSTOMTYPE | PIXEL_MONO | PIXEL_BIT_COUNT( 4 ) | 0x000e,  //!< alias PixelFormat_Mono4Packed or PixelFormat_Mono4p

        PixelType_Mono8 = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x0001,           //!< alias PixelFormat_Mono8
        PixelType_Mono8signed = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x0002,     //!< alias PixelFormat_Mono8signed or PixelFormat_Mono8s
        PixelType_Mono10 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0003,         //!< alias PixelFormat_Mono10
        PixelType_Mono10packed = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x0004,   //!< alias PixelFormat_Mono10Packed. The memory layouts of PixelType_Mono10packed and PixelType_Mono10p are different.
        PixelType_Mono10p = PIXEL_MONO | PIXEL_BIT_COUNT( 10 ) | 0x0046,        //!< alias PixelFormat_Mono10p. The memory layouts of PixelType_Mono10packed and PixelType_Mono10p are different.
        PixelType_Mono12 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0005,         //!< alias PixelFormat_Mono12
        PixelType_Mono12packed = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x0006,   //!< alias PixelFormat_Mono12Packed. The memory layouts of PixelType_Mono12packed and PixelType_Mono12p are different.
        PixelType_Mono12p = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x0047,        //!< alias PixelFormat_Mono12p. The memory layouts of PixelType_Mono12packed and PixelType_Mono12p are different.
        PixelType_Mono16 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0007,         //!< alias PixelFormat_Mono16

        PixelType_BayerGR8 = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x0008,  //!< alias PixelFormat_BayerGR8
        PixelType_BayerRG8 = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x0009,  //!< alias PixelFormat_BayerRG8
        PixelType_BayerGB8 = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x000a,  //!< alias PixelFormat_BayerGB8
        PixelType_BayerBG8 = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x000b,  //!< alias PixelFormat_BayerBG8

        PixelType_BayerGR10 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x000c,  //!< alias PixelFormat_BayerGR10
        PixelType_BayerRG10 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x000d,  //!< alias PixelFormat_BayerRG10
        PixelType_BayerGB10 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x000e,  //!< alias PixelFormat_BayerGB10
        PixelType_BayerBG10 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x000f,  //!< alias PixelFormat_BayerBG10

        PixelType_BayerGR12 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0010,  //!< alias PixelFormat_BayerGR12
        PixelType_BayerRG12 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0011,  //!< alias PixelFormat_BayerRG12
        PixelType_BayerGB12 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0012,  //!< alias PixelFormat_BayerGB12
        PixelType_BayerBG12 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0013,  //!< alias PixelFormat_BayerBG12

        PixelType_RGB8packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 24 ) | 0x0014,  //!< alias PixelFormat_RGB8Packed or PixelFormat_RGB8
        PixelType_BGR8packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 24 ) | 0x0015,  //!< alias PixelFormat_BGR8Packed or PixelFormat_BGR8

        PixelType_RGBA8packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 32 ) | 0x0016,  //!< alias PixelFormat_RGBA8Packed or PixelFormat_RGBa8
        PixelType_BGRA8packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 32 ) | 0x0017,  //!< alias PixelFormat_BGRA8Packed or PixelFormat_BGRa8

        PixelType_RGB10packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x0018,  //!< alias PixelFormat_RGB10Packed or PixelFormat_RGB10
        PixelType_BGR10packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x0019,  //!< alias PixelFormat_BGR10Packed or PixelFormat_BGR10

        PixelType_RGB12packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x001a,  //!< alias PixelFormat_RGB12Packed or PixelFormat_RGB12
        PixelType_BGR12packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x001b,  //!< alias PixelFormat_BGR12Packed or PixelFormat_BGR12

        PixelType_RGB16packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x0033,  //!< alias PixelFormat_RGB16Packed or PixelFormat_RGB16

        PixelType_BGR10V1packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 32 ) | 0x001c,  //!< alias PixelFormat_BGR10V1Packed
        PixelType_BGR10V2packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 32 ) | 0x001d,  //!< alias PixelFormat_BGR10V2Packed

        PixelType_YUV411packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 12 ) | 0x001e,  //!< alias PixelFormat_YUV411Packed or PixelFormat_YCbCr411_8
        PixelType_YUV422packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 16 ) | 0x001f,  //!< alias PixelFormat_YUV422Packed
        PixelType_YUV444packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 24 ) | 0x0020,  //!< alias PixelFormat_YUV444Packed or PixelFormat_YCbCr8

        PixelType_RGB8planar = PIXEL_COLOR | PIXEL_BIT_COUNT( 24 ) | 0x0021,   //!< alias PixelFormat_RGB8Planar or PixelFormat_RGB8_Planar
        PixelType_RGB10planar = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x0022,  //!< alias PixelFormat_RGB10Planar or PixelFormat_RGB10_Planar
        PixelType_RGB12planar = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x0023,  //!< alias PixelFormat_RGB12Planar or PixelFormat_RGB12_Planar
        PixelType_RGB16planar = PIXEL_COLOR | PIXEL_BIT_COUNT( 48 ) | 0x0024,  //!< alias PixelFormat_RGB16Planar or PixelFormat_RGB16_Planar

        PixelType_YUV422_YUYV_Packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 16 ) | 0x0032,                //!< alias PixelFormat_YUV422_YUYV_Packed or PixelFormat_YCbCr422_8
        PixelType_YUV444planar = PIXEL_CUSTOMTYPE | PIXEL_COLOR | PIXEL_BIT_COUNT( 24 ) | 0x0044,   //!< 8 bit / channel YUV 444 planar YY YY UU UU VV VV
        PixelType_YUV422planar = PIXEL_CUSTOMTYPE | PIXEL_COLOR | PIXEL_BIT_COUNT( 16 ) | 0x0042,   //!< 8 bit / channel YUV 422 planar YY YY U  U  V  V
        PixelType_YUV420planar = PIXEL_CUSTOMTYPE | PIXEL_COLOR | PIXEL_BIT_COUNT( 12 ) | 0x0040,   //!< 8 bit / channel YUV 420 planar YY YY U     V

        PixelType_YCbCr422_8_YY_CbCr_Semiplanar = PIXEL_COLOR | PIXEL_BIT_COUNT( 16 ) | 0x0113,   //!< 8 bit / channel YUV 422 semiplanar YY YY UV   UV   also known as PixelType_YUV422_NV16 4:2:2 image with a plane of 8 bit Y samples followed by an interleaved U/V plane
        PixelType_YCbCr420_8_YY_CbCr_Semiplanar = PIXEL_COLOR | PIXEL_BIT_COUNT( 12 ) | 0x0112,   //!< 8 bit / channel YUV 420 semiplanar YY YY UV        also known as PixelType_YUV420_NV12 4:2:0 image with a plane of 8 bit Y samples followed by an interleaved U/V plane

        PixelType_BayerGR12Packed = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x002A,  //!< alias PixelFormat_BayerGR12Packed. The memory layouts of PixelType_BayerGR12Packed and PixelType_BayerGR12p are different.
        PixelType_BayerRG12Packed = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x002B,  //!< alias PixelFormat_BayerRG12Packed. The memory layouts of PixelType_BayerRG12Packed and PixelType_BayerRG12p are different.
        PixelType_BayerGB12Packed = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x002C,  //!< alias PixelFormat_BayerGB12Packed. The memory layouts of PixelType_BayerGB12Packed and PixelType_BayerGB12p are different.
        PixelType_BayerBG12Packed = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x002D,  //!< alias PixelFormat_BayerBG12Packed. The memory layouts of PixelType_BayerBG12Packed and PixelType_BayerBG12p are different.

        PixelType_BayerGR10p = PIXEL_MONO | PIXEL_BIT_COUNT( 10 ) | 0x0056,  //!< alias PixelFormat_BayerGR10p.
        PixelType_BayerRG10p = PIXEL_MONO | PIXEL_BIT_COUNT( 10 ) | 0x0058,  //!< alias PixelFormat_BayerRG10p.
        PixelType_BayerGB10p = PIXEL_MONO | PIXEL_BIT_COUNT( 10 ) | 0x0054,  //!< alias PixelFormat_BayerGB10p.
        PixelType_BayerBG10p = PIXEL_MONO | PIXEL_BIT_COUNT( 10 ) | 0x0052,  //!< alias PixelFormat_BayerBG10p.

        PixelType_BayerGR12p = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x0057,  //!< alias PixelFormat_BayerGR12p. The memory layouts of PixelType_BayerGR12Packed and PixelType_BayerGR12p are different.
        PixelType_BayerRG12p = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x0059,  //!< alias PixelFormat_BayerRG12p. The memory layouts of PixelType_BayerRG12Packed and PixelType_BayerRG12p are different.
        PixelType_BayerGB12p = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x0055,  //!< alias PixelFormat_BayerGB12p. The memory layouts of PixelType_BayerGB12Packed and PixelType_BayerGB12p are different.
        PixelType_BayerBG12p = PIXEL_MONO | PIXEL_BIT_COUNT( 12 ) | 0x0053,  //!< alias PixelFormat_BayerBG12p. The memory layouts of PixelType_BayerBG12Packed and PixelType_BayerBG12p are different.

        PixelType_BayerGR16 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x002E,  //!< alias PixelFormat_BayerGR16
        PixelType_BayerRG16 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x002F,  //!< alias PixelFormat_BayerRG16
        PixelType_BayerGB16 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0030,  //!< alias PixelFormat_BayerGB16
        PixelType_BayerBG16 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x0031,  //!< alias PixelFormat_BayerBG16

        PixelType_RGB12V1packed = PIXEL_COLOR | PIXEL_BIT_COUNT( 36 ) | 0x0034,  //!< alias PixelFormat_RGB12V1Packed

        PixelType_Double = PIXEL_CUSTOMTYPE | PIXEL_MONO | PIXEL_BIT_COUNT( 64 ) | 0x100,  //!< alias PixelFormat_Double

        // For ToF
        PixelType_Confidence8 = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x00C6,       //!< Confidence 8-bit
        PixelType_Confidence16 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x00C7,     //!< Confidence 16-bit
        PixelType_Coord3D_C8 = PIXEL_MONO | PIXEL_BIT_COUNT( 8 ) | 0x00B1,        //!< 3D coordinate C 8-bit
        PixelType_Coord3D_C16 = PIXEL_MONO | PIXEL_BIT_COUNT( 16 ) | 0x00B8,      //!< 3D coordinate C 16-bit
        PixelType_Coord3D_ABC32f = PIXEL_COLOR | PIXEL_BIT_COUNT( 96 ) | 0x00C0,  //!< 3D coordinate A-B-C 32-bit floating point

        // Floating point
        PixelType_Data32f = PIXEL_MONO |  PIXEL_BIT_COUNT( 32 ) | 0x011C,   //!< 32 bit IEC 60559:1989 conform little endian floating point data
    };

    /// Returns true if the pixel type is Mono and the pixel values are not byte aligned.
    inline bool IsMonoPacked( EPixelType pixelType )
    {
        if (PixelType_Mono1packed == pixelType)   return true;
        if (PixelType_Mono2packed == pixelType)   return true;
        if (PixelType_Mono4packed == pixelType)   return true;
        if (PixelType_Mono10packed == pixelType)   return true;
        if (PixelType_Mono10p == pixelType)   return true;
        if (PixelType_Mono12packed == pixelType)   return true;
        if (PixelType_Mono12p == pixelType)   return true;

        return false;
    }

    /// Returns true if the pixel type is Bayer and the pixel values are not byte aligned.
    inline bool IsBayerPacked( EPixelType pixelType )
    {
        if (PixelType_BayerGB12Packed == pixelType)   return true;
        if (PixelType_BayerGR12Packed == pixelType)   return true;
        if (PixelType_BayerRG12Packed == pixelType)   return true;
        if (PixelType_BayerBG12Packed == pixelType)   return true;
        if (PixelType_BayerGB10p == pixelType)   return true;
        if (PixelType_BayerGR10p == pixelType)   return true;
        if (PixelType_BayerRG10p == pixelType)   return true;
        if (PixelType_BayerBG10p == pixelType)   return true;
        if (PixelType_BayerGB12p == pixelType)   return true;
        if (PixelType_BayerGR12p == pixelType)   return true;
        if (PixelType_BayerRG12p == pixelType)   return true;
        if (PixelType_BayerBG12p == pixelType)   return true;

        return false;
    }

    /// Returns true if the pixel type is RGB and the pixel values are not byte aligned.
    inline bool IsRGBPacked( EPixelType pixelType )
    {
        if (PixelType_RGB12V1packed == pixelType) return true;

        return false;
    }

    /// Returns true if the pixel type is BGR and the pixel values are not byte aligned.
    inline bool IsBGRPacked( EPixelType pixelType )
    {
        if (PixelType_BGR10V1packed == pixelType) return true;
        if (PixelType_BGR10V2packed == pixelType) return true;

        return false;
    }

    /// Returns true if the pixels of the given pixel type are not byte aligned.
    inline bool IsPacked( EPixelType pixelType )
    {
        return (IsMonoPacked( pixelType ) || IsBayerPacked( pixelType ) || IsRGBPacked( pixelType ) || IsBGRPacked( pixelType ));
    }

    /// Returns true if the pixel type is packed in lsb packed format.
    /// For lsb packed format, the data is filled lsb first in the lowest address byte (byte 0) starting with the first pixel
    /// and continued in the lsb of byte 1 (and so on).
    /// See the camera User's Manual or the Pixel Format Naming Convention (PFNC) of the GenICam standard group for more information.
    inline bool IsPackedInLsbFormat( EPixelType pixelType )
    {
        if (PixelType_Mono1packed == pixelType)   return true;
        if (PixelType_Mono2packed == pixelType)   return true;
        if (PixelType_Mono4packed == pixelType)   return true;
        if (PixelType_Mono10p == pixelType)   return true;
        if (PixelType_BayerGB10p == pixelType)   return true;
        if (PixelType_BayerGR10p == pixelType)   return true;
        if (PixelType_BayerRG10p == pixelType)   return true;
        if (PixelType_BayerBG10p == pixelType)   return true;
        if (PixelType_BayerGB12p == pixelType)   return true;
        if (PixelType_BayerGR12p == pixelType)   return true;
        if (PixelType_BayerRG12p == pixelType)   return true;
        if (PixelType_BayerBG12p == pixelType)   return true;
        if (PixelType_Mono12p == pixelType)   return true;

        return false;
    }

    /// Returns number of planes in the image composed of the pixel type.
    inline uint32_t PlaneCount( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_RGB8planar:
            case PixelType_RGB10planar:
            case PixelType_RGB12planar:
            case PixelType_RGB16planar:
            case PixelType_YUV444planar:
            case PixelType_YUV422planar:
            case PixelType_YUV420planar:
                return 3;
            default:
                return 1;
        }
    }

    /// Returns the pixel type of a plane.
    inline EPixelType GetPlanePixelType( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_RGB8planar:
            case PixelType_YUV444planar:
            case PixelType_YUV422planar:
            case PixelType_YUV420planar:
                return PixelType_Mono8;
            case PixelType_RGB10planar:
                return PixelType_Mono10;
            case PixelType_RGB12planar:
                return PixelType_Mono12;
            case PixelType_RGB16planar:
                return PixelType_Mono16;
            default:
                return pixelType;
        }
    }

    /// Returns true if images of the pixel type are divided into multiple planes.
    inline bool IsPlanar( EPixelType pixelType )
    {
        return PlaneCount( pixelType ) > 1;
    }

    /// Lists the Bayer color filter types.
    enum EPixelColorFilter
    {
        PCF_BayerRG,    //!< red green
        PCF_BayerGB,    //!< green blue
        PCF_BayerGR,    //!< green red
        PCF_BayerBG,    //!< blue green
        PCF_Undefined   //!< undefined color filter or not applicable
    };

    /// Returns the Bayer color filter type.
    inline EPixelColorFilter GetPixelColorFilter( EPixelType pixelType )
    {
        if (PixelType_BayerGR8 == pixelType)   return PCF_BayerGR;
        if (PixelType_BayerRG8 == pixelType)   return PCF_BayerRG;
        if (PixelType_BayerGB8 == pixelType)   return PCF_BayerGB;
        if (PixelType_BayerBG8 == pixelType)   return PCF_BayerBG;

        if (PixelType_BayerGR10 == pixelType)   return PCF_BayerGR;
        if (PixelType_BayerRG10 == pixelType)   return PCF_BayerRG;
        if (PixelType_BayerGB10 == pixelType)   return PCF_BayerGB;
        if (PixelType_BayerBG10 == pixelType)   return PCF_BayerBG;

        if (PixelType_BayerGR12 == pixelType)   return PCF_BayerGR;
        if (PixelType_BayerRG12 == pixelType)   return PCF_BayerRG;
        if (PixelType_BayerGB12 == pixelType)   return PCF_BayerGB;
        if (PixelType_BayerBG12 == pixelType)   return PCF_BayerBG;

        if (PixelType_BayerGR12Packed == pixelType)   return PCF_BayerGR;
        if (PixelType_BayerRG12Packed == pixelType)   return PCF_BayerRG;
        if (PixelType_BayerGB12Packed == pixelType)   return PCF_BayerGB;
        if (PixelType_BayerBG12Packed == pixelType)   return PCF_BayerBG;

        if (PixelType_BayerGR10p == pixelType)   return PCF_BayerGR;
        if (PixelType_BayerRG10p == pixelType)   return PCF_BayerRG;
        if (PixelType_BayerGB10p == pixelType)   return PCF_BayerGB;
        if (PixelType_BayerBG10p == pixelType)   return PCF_BayerBG;

        if (PixelType_BayerGR12p == pixelType)   return PCF_BayerGR;
        if (PixelType_BayerRG12p == pixelType)   return PCF_BayerRG;
        if (PixelType_BayerGB12p == pixelType)   return PCF_BayerGB;
        if (PixelType_BayerBG12p == pixelType)   return PCF_BayerBG;

        if (PixelType_BayerGR16 == pixelType)   return PCF_BayerGR;
        if (PixelType_BayerRG16 == pixelType)   return PCF_BayerRG;
        if (PixelType_BayerGB16 == pixelType)   return PCF_BayerGB;
        if (PixelType_BayerBG16 == pixelType)   return PCF_BayerBG;

        return PCF_Undefined;
    }

    /*!
    \brief Returns the bits needed to store a pixel.

    BitPerPixel(PixelType_Mono12) returns 16 and BitPerPixel(PixelType_Mono12packed)
    returns 12 for example.

    \param[in] pixelType The pixel type.
    \pre The pixel type must be defined.

    \error
        Throws an exception when the pixel type is undefined.
    */
    PYLONBASE_API uint32_t BitPerPixel( EPixelType pixelType );

    /*!
    \brief Returns the number of measured values per pixel.

    SamplesPerPixel(PixelType_Mono8) returns 1 and SamplesPerPixel(PixelType_RGB8packed)
    returns 3 for example.

    \param[in] pixelType The pixel type.
    \pre The pixel type must be defined. The pixel type is not PixelType_YUV411packed.

    \error
        Throws an exception when the pixel type is undefined.
    */
    PYLONBASE_API uint32_t SamplesPerPixel( EPixelType pixelType );

    /// Returns true when the pixel type represents a YUV format.
    inline bool IsYUV( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_YUV411packed:
            case PixelType_YUV422_YUYV_Packed:
            case PixelType_YUV422packed:
            case PixelType_YUV444packed:
            case PixelType_YUV444planar:
            case PixelType_YUV422planar:
            case PixelType_YUV420planar:
                return true;
            default:
                return false;
        }
    }

    /// Returns true when the pixel type represents an RGBA format.
    inline bool IsRGBA( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_RGBA8packed:
                return true;
            default:
                return false;
        }
    }

    /// Returns true when the pixel type represents an RGB or RGBA format.
    inline bool IsRGB( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_RGB8packed:
            case PixelType_RGB10packed:
            case PixelType_RGB12packed:
            case PixelType_RGB16packed:
            case PixelType_RGB8planar:
            case PixelType_RGB10planar:
            case PixelType_RGB12planar:
            case PixelType_RGB16planar:
            case PixelType_RGB12V1packed:
                return true;
            default:
                return IsRGBA( pixelType );
        }
    }

    /// Returns true when the pixel type represents a BGRA format.
    inline bool IsBGRA( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_BGRA8packed:
                return true;
            default:
                return false;
        }

    }

    /// Returns true when the pixel type represents a BGR or BGRA format.
    inline bool IsBGR( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_BGR8packed:
            case PixelType_BGR10packed:
            case PixelType_BGR12packed:
            case PixelType_BGR10V1packed:
            case PixelType_BGR10V2packed:
                return true;
            default:
                return IsBGRA( pixelType );
        }
    }

    /// Returns true when the pixel type represents a Bayer format.
    inline bool IsBayer( EPixelType pixelType )
    {
        return GetPixelColorFilter( pixelType ) != PCF_Undefined;
    }

    /// Returns true when a given pixel is monochrome, e.g. PixelType_Mono8 or PixelType_BayerGR8.
    inline bool IsMono( EPixelType pixelType )
    {
        return (pixelType != PixelType_Undefined) && (PIXEL_MONO == (pixelType & PIXEL_MONO));
    }

    /// Returns true when an image using the given pixel type is monochrome, e.g. PixelType_Mono8.
    inline bool IsMonoImage( EPixelType pixelType )
    {
        return IsMono( pixelType ) && !IsBayer( pixelType );
    }

    /// Returns true when an image using the given pixel type is a color image (RGB/BGR/RGBA/BGRA/ etc or Bayer.
    inline bool IsColorImage( EPixelType pixelType )
    {
        bool res = (pixelType != PixelType_Undefined) && (IsBayer( pixelType ) || ((pixelType & PIXEL_COLOR) != 0));
        return res;
    }

    /// Returns true when an the image using the given pixel type has an alpha channel.
    inline bool HasAlpha( EPixelType pixelType )
    {
        switch (pixelType)
        {
            case PixelType_RGBA8packed:
            case PixelType_BGRA8packed:
                return true;
            default:
                return false;
        }
    }

    /// Returns true if a given pixel type represents a floating point number.
    inline bool IsFloatingPoint( EPixelType pixelType )
    {
        bool res = (pixelType == PixelType_Double) || (pixelType == PixelType_Coord3D_ABC32f) || (pixelType == PixelType_Data32f);
        return res;
    }

    /// Returns the minimum step size expressed in pixels for extracting an AOI.
    inline uint32_t GetPixelIncrementX( EPixelType pixelType )
    {
        if (IsBayer( pixelType ))
        {
            return 2;
        }

        switch (pixelType)
        {
            case PixelType_YUV422packed:
                return 2;
            case PixelType_YUV422_YUYV_Packed:
                return 2;
            case PixelType_YUV411packed:
                return 4;
            default:
                return 1;
        }
    }

    /// Returns the minimum step size expressed in pixels for extracting an AOI.
    inline uint32_t GetPixelIncrementY( EPixelType pixelType )
    {
        if (IsBayer( pixelType ))
        {
            return 2;
        }
        return 1;
    }

    /*!
    \brief Returns the bit depth of a value of the pixel in bits.

    This may be less than the size needed to store the pixel.
    BitDepth(PixelType_Mono12) returns 12, BitDepth(PixelType_Mono12packed)
    returns 12, and  BitDepth(PixelType_RGB8packed) returns 8 for example.

    \param[in] pixelType The pixel type.

    \pre The pixel type must be valid.

    \error
        Throws an exception when the pixel type is undefined.
    */
    PYLONBASE_API uint32_t BitDepth( EPixelType pixelType );

    /*!
    \brief Computes the stride in byte.

    The stride indicates the number of bytes between the beginning of one row
    in an image and the beginning of the next row.
    For planar pixel types the returned value represents the stride of a plane.

    The stride in bytes cannot be computed for packed image format when the stride is not byte aligned and paddingX == 0.
    If paddingX is larger than zero and the stride without padding is not byte aligned then the rest of the partially
    filled byte is considered as padding, e.g. pixelType = PixelType_Mono12packed, width = 5, paddingX = 10 results
    in a stride of 18 Bytes (stride without padding is 5 * BitPerPixel( PixelType_Mono12packed) = 5 * 12 = 60 Bits = 7.5 Bytes).

    The stride can also be not computed for planar YUV422 and YUV420 image formats.

    See also Pylon::IsPacked().

    \param[out] strideBytes  The stride in byte if it can be computed.
    \param[in] pixelType The pixel type.
    \param[in] width     The number of pixels in a row.
    \param[in] paddingX  The number of additional bytes at the end of a row (byte aligned).

    \return Returns true if the stride can be computed.

    \pre
            The \c width value must be >= 0 and <= _I32_MAX.

    \error
        Throws an exception when the preconditions are not met.
    */
    PYLONBASE_API bool ComputeStride( size_t& strideBytes, EPixelType pixelType, uint32_t width, size_t paddingX = 0 );

    /*!
    \brief Computes the padding value from row stride in byte.

    \param[out] strideBytes  The stride in byte.
    \param[in] pixelType The pixel type.
    \param[in] width     The number of pixels in a row.

    \return Returns the paddingX value for the given stride value (byte aligned).

    \pre
        <ul>
        <li> The value of \c strideBytes must be large enough to contain a line described by \c pixelType and \c width.
        <li> The pixel type must be valid.
        <li> The \c width value must be >= 0 and <= _I32_MAX.
        </ul>

    \error
        Throws an exception when the preconditions are not met.
    */
    PYLONBASE_API size_t ComputePaddingX( size_t strideBytes, EPixelType pixelType, uint32_t width );

    /*!
    \brief Computes the buffer size in byte.

    \param[in] pixelType The pixel type.
    \param[in] width     The number of pixels in a row.
    \param[in] height    The number of rows in an image.
    \param[in] paddingX  The number of extra data bytes at the end of each row (byte aligned).
    \return The buffer size in byte.

    \pre
        <ul>
        <li> The pixel type must be valid.
        <li> The \c width value must be >= 0 and <= _I32_MAX.
        <li> The \c height value must be >= 0 and <= _I32_MAX.
        </ul>

    \error
        Throws an exception when the preconditions are not met.
    */
    PYLONBASE_API size_t ComputeBufferSize( EPixelType pixelType, uint32_t width, uint32_t height, size_t paddingX = 0 );

    /*!
    \brief Returns the pixel types needed for conversion from packed to unpacked image formats using the CImageFormatConverter class.

    The following pixel types are supported:
    <ul>
    <li> source: PixelType_Mono1packed   target: PixelType_Mono8
    <li> source: PixelType_Mono2packed   target: PixelType_Mono8
    <li> source: PixelType_Mono4packed   target: PixelType_Mono8
    <li> source: PixelType_Mono10packed  target: PixelType_Mono16
    <li> source: PixelType_Mono10p  target: PixelType_Mono16
    <li> source: PixelType_Mono12packed  target: PixelType_Mono16
    <li> source: PixelType_Mono12p  target: PixelType_Mono16
    <li> source: PixelType_BayerGB12Packed  imposed: PixelType_Mono12packed  target: PixelType_Mono16
    <li> source: PixelType_BayerGR12Packed  imposed: PixelType_Mono12packed  target: PixelType_Mono16
    <li> source: PixelType_BayerRG12Packed  imposed: PixelType_Mono12packed  target: PixelType_Mono16
    <li> source: PixelType_BayerBG12Packed  imposed: PixelType_Mono12packed  target: PixelType_Mono16
    <li> source: PixelType_BayerGB10p  imposed: PixelType_Mono10p  target: PixelType_Mono16
    <li> source: PixelType_BayerGR10p  imposed: PixelType_Mono10p  target: PixelType_Mono16
    <li> source: PixelType_BayerRG10p  imposed: PixelType_Mono10p  target: PixelType_Mono16
    <li> source: PixelType_BayerBG10p  imposed: PixelType_Mono10p  target: PixelType_Mono16
    <li> source: PixelType_BayerGB12p  imposed: PixelType_Mono12p  target: PixelType_Mono16
    <li> source: PixelType_BayerGR12p  imposed: PixelType_Mono12p  target: PixelType_Mono16
    <li> source: PixelType_BayerRG12p  imposed: PixelType_Mono12p  target: PixelType_Mono16
    <li> source: PixelType_BayerBG12p  imposed: PixelType_Mono12p  target: PixelType_Mono16
    </ul>

    \param[in] pixelTypeSource The source pixel type.
    \param[out] pixelTypeToImpose The pixel type that is used for conversion instead of the source pixel type.
                                  Returns \c pixelTypeSource if changing the source pixel type is not needed.
                                  Returns PixelType_Undefined if no unpacking is needed.
    \param[out] pixelTypeTarget The pixel type to which the image pixel data are converted.
                                Returns PixelType_Undefined if no unpacking is needed.

    \return Returns true if the source \c pixelTypeSource is in packed image format and a conversion is possible.
    */
    inline bool GetPixelTypesForUnpacking( EPixelType pixelTypeSource, EPixelType& pixelTypeToImpose, EPixelType& pixelTypeTarget )
    {
        pixelTypeToImpose = pixelTypeSource;
        pixelTypeTarget = PixelType_Undefined;

        if (PixelType_Mono1packed == pixelTypeSource)
        {
            pixelTypeTarget = PixelType_Mono8;
        }
        else if (PixelType_Mono2packed == pixelTypeSource)
        {
            pixelTypeTarget = PixelType_Mono8;
        }
        else if (PixelType_Mono4packed == pixelTypeSource)
        {
            pixelTypeTarget = PixelType_Mono8;
        }
        else if (PixelType_Mono10packed == pixelTypeSource)
        {
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_Mono10p == pixelTypeSource)
        {
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_Mono12packed == pixelTypeSource)
        {
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_Mono12p == pixelTypeSource)
        {
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerGB12Packed == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12packed;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerGR12Packed == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12packed;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerRG12Packed == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12packed;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerBG12Packed == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12packed;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerGB10p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono10p;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerGR10p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono10p;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerRG10p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono10p;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerBG10p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono10p;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerGB12p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12p;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerGR12p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12p;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerRG12p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12p;
            pixelTypeTarget = PixelType_Mono16;
        }
        else if (PixelType_BayerBG12p == pixelTypeSource)
        {
            pixelTypeToImpose = PixelType_Mono12p;
            pixelTypeTarget = PixelType_Mono16;
        }

        return pixelTypeTarget != PixelType_Undefined;
    }


    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PIXELTYPE_H_1534845 */
