//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a data class that represents the CircleF data type.
*/

#pragma once

#include <pylon/stdinclude.h>
#include <pylondataprocessing/PointF2D.h>

#pragma pack(push, 1)

namespace Pylon
{
    namespace DataProcessing
    {
        /*! \brief The data of a CVariant object with the VariantDataType_CircleF data type.
         */
        struct SCircleF
        {
            /*! \brief Creates a circle and initializes it with 0.
             */
            SCircleF()
                : Radius(0.0)
            {
            }

            /*! \brief Creates a circle and initializes it.
                \param[in] centerX The x coordinate of the center of the circle.
                \param[in] centerY The y coordinate of the center of the circle.
                \param[in] radius The radius of the circle.
            */
            SCircleF(double centerX, double centerY, double radius)
                : Center(centerX, centerY)
                , Radius(radius)
            {
            }

            /*! \brief Creates a circle and initializes it.
                \param[in] center The center of the circle.
                \param[in] radius The radius of the circle.
            */
            SCircleF(SPointF2D center, double radius)
                : Center(center)
                , Radius(radius)
            {
            }

            SPointF2D Center; //!< \brief The center of the circle.
            double Radius;    //!< \brief The radius of the circle.
        };
    }
}

#pragma pack(pop)
