//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a data class that represents the LineF2D data type.
*/

#pragma once

#include <pylon/stdinclude.h>
#include <pylondataprocessing/PointF2D.h>

#pragma pack(push, 1)

namespace Pylon
{
    namespace DataProcessing
    {
        /*! \brief The data of a CVariant object with the VariantDataType_LineF2D data type.
         */
        struct SLineF2D
        {
            /*! \brief Creates a line and initializes it with 0.
             */
            SLineF2D()
            {
            }

            /*! \brief Creates a line and initializes it.
                \param[in] pointAX The x coordinate of point A of the line.
                \param[in] pointAY The y coordinate of point A of the line.
                \param[in] pointBX The x coordinate of point B of the line.
                \param[in] pointBY The y coordinate of point B of the line.
            */
            SLineF2D(double pointAX, double pointAY, double pointBX, double pointBY)
                : PointA(pointAX, pointAY)
                , PointB(pointBX, pointBY)
            {
            }

            /*! \brief Creates a line and initializes it.
                \param[in] pointA Point A of the line.
                \param[in] pointB Point B of the line.
            */
            SLineF2D(SPointF2D pointA, SPointF2D pointB)
                : PointA(pointA)
                , PointB(pointB)
            {
            }

            SPointF2D PointA; //!< \brief Point A of the line.
            SPointF2D PointB; //!< \brief Point B of the line.
        };
    }
}

#pragma pack(pop)
