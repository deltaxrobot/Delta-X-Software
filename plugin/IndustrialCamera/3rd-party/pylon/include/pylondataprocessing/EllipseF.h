//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a data class that represents the EllipseF data type.
*/

#pragma once

#include <pylon/stdinclude.h>
#include <pylondataprocessing/PointF2D.h>

#pragma pack(push, 1)

namespace Pylon
{
    namespace DataProcessing
    {

        /*! \brief The data of a CVariant object with the VariantDataType_EllipseF data type.
         */
        struct SEllipseF
        {
            /*! \brief Creates an ellipse and initializes it with 0.
             */
            SEllipseF()
                : Radius1(0.0)
                , Radius2(0.0)
                , Rotation(0.0)
            {
            }

            /*! \brief Creates an ellipse and initializes it.
                \param[in] centerX The x coordinate of the center of the ellipse.
                \param[in] centerY The y coordinate of the center of the ellipse.
                \param[in] radius1 The radius of the ellipse that is parallel to the x axis
                                   when the ellipse is in its original state, i.e., it hasn't been rotated.
                \param[in] radius2 The radius of the ellipse that is parallel to the y axis
                                   when the ellipse is in its original state, i.e., it hasn't been rotated.
                \param[in] rotation The rotation of the ellipse in radiant.
            */
            SEllipseF(double centerX, double centerY, double radius1, double radius2, double rotation = 0.0)
                : Center(centerX, centerY)
                , Radius1(radius1)
                , Radius2(radius2)
                , Rotation(rotation)
            {
            }

            /*! \brief Creates an ellipse and initializes it.
                \param[in] center The center of the ellipse.
                \param[in] radius1 The radius of the ellipse that is parallel to the x axis
                                   when the ellipse is in its original state, i.e., it hasn't been rotated.
                \param[in] radius2 The radius of the ellipse that is parallel to the y axis
                                   when the ellipse is in its original state, i.e., it hasn't been rotated.
                \param[in] rotation The rotation of the ellipse in radiant.
            */
            SEllipseF(SPointF2D center, double radius1, double radius2, double rotation = 0.0)
                : Center(center)
                , Radius1(radius1)
                , Radius2(radius2)
                , Rotation(rotation)
            {
            }

            SPointF2D Center; //!< \brief The center of the ellipse.
            double Radius1;   //!< \brief The radius of the ellipse that is parallel to the x axis when the ellipse is in its original state, i.e., it hasn't been rotated.
            double Radius2;   //!< \brief The radius of the ellipse that is parallel to the y axis when the ellipse is in its original state, i.e., it hasn't been rotated.
            double Rotation;  //!< \brief The rotation of the ellipse. The rotation is defined relative to the x axis and rotates
                              //!< counterclockwise in radiant. First, consider the position of the ellipse as defined by its Radius1 (x)
                              //!< and Radius2 (y) around its center. Then, the ellipse is rotated.
        };
    }
}

#pragma pack(pop)
