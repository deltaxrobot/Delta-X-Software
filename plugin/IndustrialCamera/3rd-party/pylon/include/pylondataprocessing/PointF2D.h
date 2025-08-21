//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a data class that represents the PointF2D data type.
*/

#pragma once

#include <pylon/stdinclude.h>

#pragma pack(push, 1)

namespace Pylon
{
    namespace DataProcessing
    {
        /*! \brief The data of a CVariant object with the VariantDataType_PointF2D data type.
            PointF2D can provide image coordinates in pixels and world coordinates in meters.
            The origin (0,0) of image coordinates defined by a PointF2D is the center of the top left image pixel.
         */
        struct SPointF2D
        {
            /*! \brief Creates a point and initializes it with (0,0).
             */
            SPointF2D()
                : X(0.0)
                , Y(0.0)
            {
            }
            
            /*! \brief Creates a point and initializes it with (x,y).
             */
            SPointF2D(double x, double y)
                : X(x)
                , Y(y)
            {
            }

            double X; //!< \brief The x coordinate of the point.
            double Y; //!< \brief The y coordinate of the point.
        };
    }
}

#pragma pack(pop)
