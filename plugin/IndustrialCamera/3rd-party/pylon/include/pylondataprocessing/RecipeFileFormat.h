//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2024 Basler AG
//  http://www.baslerweb.com
//  Author:  RN
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains an enumeration that lists the available recipe file formats.
*/

#pragma once

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
            Lists the available recipe file formats.
        */
        enum ERecipeFileFormat
        {
            RecipeFileFormat_JsonDefault = 1,               /*<! The default JSON format. */
            RecipeFileFormat_JsonCompressedBinaryData = 2,  /*<! JSON format with compressed binary data. This can significantly reduce the storage space required for recipes that store large amounts of binary data.
                                                                 The load and save times are significantly longer compared to using \c RecipeFileFormat_JsonDefault. */
        };
    }
}
