//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a data class that represents the RectangleF data type.
*/

#pragma once

#include <pylon/stdinclude.h>
#include <pylondataprocessing/PointF2D.h>

#pragma pack(push, 1)

namespace Pylon
{
    namespace DataProcessing
    {
        /*! \brief The data of a CVariant object with the VariantDataType_RectangleF data type.
         */
        struct SRectangleF
        {
            /*! \brief Creates a rectangle and initializes it with 0.
             */
            SRectangleF()
            : Width(0.0)
            , Height(0.0)
            , Rotation(0.0)
            {
            }

            /*! \brief Creates a rectangle and initializes it.
                \param[in] centerX The x coordinate of the center of the rectangle.
                \param[in] centerY The y coordinate of the center of the rectangle.
                \param[in] width The width of the rectangle.
                \param[in] height The height of the rectangle.
                \param[in] rotation The rotation of the rectangle in radiant.
            */
            SRectangleF(double centerX, double centerY, double width, double height, double rotation = 0.0)
                : Center(centerX, centerY)
                , Width(width)
                , Height(height)
                , Rotation(rotation)
            {
            }

            /*! \brief Creates a rectangle and initializes it.
                \param[in] center The center of the rectangle.
                \param[in] width The width of the rectangle.
                \param[in] height The height of the rectangle.
                \param[in] rotation The rotation of the rectangle in radiant.
            */
            SRectangleF(SPointF2D center, double width, double height, double rotation = 0.0)
                : Center(center)
                , Width(width)
                , Height(height)
                , Rotation(rotation)
            {
            }

            SPointF2D Center; //!< \brief The center of the rectangle.
            double Width;     //!< \brief The width of the rectangle.
            double Height;    //!< \brief The height of the rectangle.
            double Rotation;  //!< \brief The rotation of the rectangle. The rotation is defined relative to the x axis and rotates
                              //!< counterclockwise in radiant. First, consider the position of the rectangle as defined by its width (x)
                              //!< and height (y) around its center. Then, the rectangle is rotated.
        };
    }
}

#pragma pack(pop)
