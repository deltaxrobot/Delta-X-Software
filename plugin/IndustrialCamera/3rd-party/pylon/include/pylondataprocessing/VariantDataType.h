//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains an enumeration that lists the built-in variant data types.
*/

#pragma once

#include <pylondataprocessing/PylonDataProcessing.h>

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
         /*!
         \brief
            Lists the built-in variant data types consisting of basic data types and composite data types.

            Basic data types are used to build composite data types.
            Composite data types are defined by the vTools used in a recipe connected to inputs and outputs of the recipe.
        **/
        enum EVariantDataType
        {
            // Basic types
            VariantDataType_Int64 = 1,                  //!< Corresponds to C++ data type int64_t. Default value = 0
            VariantDataType_UInt64 = 2,                 //!< Corresponds to C++ data type uint64_t. Default value = 0
            VariantDataType_Boolean = 3,                //!< Corresponds to C++ data type bool. Default value = false
                                                        //!< For CVariant::SetArrayDataValues() and CVariant::SetArrayDataValues() use bool8_t.
            VariantDataType_String = 4,                 //!< Corresponds to C++ data type Pylon::String_t. The character encoding is UTF8. Default value = Pylon::String_t()
            VariantDataType_Float = 5,                  //!< Corresponds to C++ data type double. Default value = 0.0
            VariantDataType_PylonImage = 6,             //!< Corresponds to C++ data type Pylon::CPylonImage. Default value = CPylonImage()
            VariantDataType_Region = 8,                 //!< Corresponds to C++ data type Pylon::DataProcessing::CRegion. Default value = CRegion()
            VariantDataType_TransformationData = 9,     //!< Corresponds to C++ data type Pylon::DataProcessing::CTransformationData. Default value = CTransformationData()

            // Composite type
            VariantDataType_Composite = 7,              //!< A composite struct of basic types, e.g., Thresholds { UInt8 lowerThreshold, UInt8 upperThreshold}.
                                                        //!< Structs can be nested.
                                                        //!< See the documentation of the vTools connected to inputs and outputs of the recipe
                                                        //!< for more information about composite data types in case composite data types are used.
                                                        //!< This value is reported if a type other than a built-in composite type is queried for its type.

            // Built-in composite types
            VariantDataType_PointF2D = 10,              //!< pylon provides the data struct Pylon::DataProcessing::SPointF2D for this data type. Default value = SPointF2D()
            VariantDataType_LineF2D = 11,               //!< pylon provides the data struct Pylon::DataProcessing::SLineF2D for this data type. Default value = SLineF2D()
            VariantDataType_RectangleF = 12,            //!< pylon provides the data struct Pylon::DataProcessing::SRectangleF for this data type. Default value = SRectangleF()
            VariantDataType_CircleF = 13,               //!< pylon provides the data struct Pylon::DataProcessing::SCircleF for this data type. Default value = SCircleF()
            VariantDataType_EllipseF = 14,              //!< pylon provides the data struct Pylon::DataProcessing::SEllipseF for this data type. Default value = SEllipseF()

            //special
            VariantDataType_None = 0,                   //!< Corresponds to C++ data type void. No data is held.
            VariantDataType_Generic = 15,               //!< A generic data type that is not supported natively by this SDK yet.
            VariantDataType_Unsupported = 16            //!< A data type that is not supported natively by this SDK yet.
        };
    }
}
