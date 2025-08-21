//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains an enumeration that lists the built-in variant container types.
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
            Lists the built-in variant container types.
        **/
        enum EVariantContainerType
        {
            VariantContainerType_None           = 0,    //!< A basic data object without any container.
            VariantContainerType_Array          = 1,    //!< An array that may contain basic data objects.
            VariantContainerType_Unsupported    = 2     //!< A container type that is not supported natively by this SDK yet.
        };
    }
}
