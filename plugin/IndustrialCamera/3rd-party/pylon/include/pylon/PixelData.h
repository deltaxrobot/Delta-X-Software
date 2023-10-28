//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2012-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains a data structure describing the data of one pixel.
*/

#ifndef INCLUDED_PIXELDATA_H_9714014
#define INCLUDED_PIXELDATA_H_9714014

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

    /*!
    \class  SPixelData
    \brief  Describes the data of one pixel.
    */
    struct SPixelData
    {
        /// Construct and clear.
        SPixelData()
            : PixelDataType( PixelDataType_Unknown )
            , BitDepth( 0 )
        {
            Data.RGBA.R =
                Data.RGBA.G =
                Data.RGBA.B =
                Data.RGBA.A = 0;
        }
        ~SPixelData()
        {

        }

        /// Lists the possible pixel data types.
        /// Do not confound this enumeration with the Pylon::PixelType enumeration that lists all pixel formats.
        enum EPixelDataType
        {
            PixelDataType_Unknown,//!< Will be returned, if the pixel data cannot be determined.
            PixelDataType_Mono,   //!< Pixel data of monochrome images.
            PixelDataType_YUV,    //!< Pixel data of YUV images.
            PixelDataType_RGB,    //!< Pixel data of RGB or BGR images.
            PixelDataType_RGBA,   //!< Pixel data of RGB or BGR images with alpha channel.
            PixelDataType_BayerR, //!< Pixel data of a red pixel of bayer images.
            PixelDataType_BayerG, //!< Pixel data of a green pixel of bayer images.
            PixelDataType_BayerB  //!< Pixel data of a blue pixel of bayer images.
        };

        EPixelDataType PixelDataType; ///< The type of pixel data held.
        uint32_t BitDepth; ///< The bit depth of the data held.

        union
        {
            int Mono;   ///< Pixel data of monochrome images.
            int BayerR; ///< Pixel data of a red pixel of bayer images.
            int BayerG; ///< Pixel data of a green pixel of bayer images.
            int BayerB; ///< Pixel data of a blue pixel of bayer images.

            struct
            {
                int Y; ///< Brightness.
                int U; ///< Chroma U.
                int V; ///< Chroma V.
            }
            YUV; ///< Pixel data of YUV images.

            struct
            {
                int R; ///< Red.
                int G; ///< Green.
                int B; ///< Blue.
            }
            RGB; ///< Pixel data of RGB or BGR images.

            struct
            {
                int R; ///< Red.
                int G; ///< Green.
                int B; ///< Blue.
                int A; ///< Transparency.
            }
            RGBA; ///< Pixel data of RGB or BGR images with an alpha channel.
        }
        Data; ///< Holds all types of pixel data.

        /// Compares pixel data.
        bool operator==( const SPixelData& rhs )
        {
            if (PixelDataType != rhs.PixelDataType) return false;
            if (BitDepth != rhs.BitDepth) return false;
            switch (PixelDataType)
            {
                case PixelDataType_Unknown:
                    return true;
                case PixelDataType_Mono:
                    return Data.Mono == rhs.Data.Mono;
                case PixelDataType_YUV:
                    return Data.YUV.Y == rhs.Data.YUV.Y && Data.YUV.U == rhs.Data.YUV.U && Data.YUV.V == rhs.Data.YUV.V;
                case PixelDataType_RGB:
                    return Data.RGB.R == rhs.Data.RGB.R && Data.RGB.G == rhs.Data.RGB.G && Data.RGB.B == rhs.Data.RGB.B;
                case PixelDataType_RGBA:
                    return Data.RGB.R == rhs.Data.RGBA.R && Data.RGBA.G == rhs.Data.RGBA.G && Data.RGBA.B == rhs.Data.RGBA.B && Data.RGBA.A == rhs.Data.RGBA.A;
                case PixelDataType_BayerR:
                    return Data.BayerR == rhs.Data.BayerR;
                case PixelDataType_BayerG:
                    return Data.BayerG == rhs.Data.BayerG;
                case PixelDataType_BayerB:
                    return Data.BayerB == rhs.Data.BayerB;
                default:
                    PYLON_ASSERT2( false, "Cannot compare SPixelDataStructure. It contains unexpected data." );
            }
            return false;
        }

        /// Compares pixel data.
        bool operator!=( const SPixelData& rhs )
        {
            return !((*this) == rhs);
        }
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PIXELDATA_H_9714014 */
